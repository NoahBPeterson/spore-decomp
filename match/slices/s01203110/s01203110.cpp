// Slice s01203110: one function
//   0x01203110  swept sphere vs triangle (TriangleVolume linear cast with radius), 3524 bytes
//
// Static helper of the "TriangleVolume" collision volume (same module as the BoxVolume cast in
// slice s012080d0).  Its only caller is TriangleVolume::LinearCast (0x01203ee0, written below so
// that cl sees the call site): when the volume has a radius it first writes the triangle's world
// normal to out->mNormal (0x01202020), then calls this with the world-space start point, the
// sweep direction (to - from), the three world-space vertices and the radius.
//
// The original is a cl "static" function with a register ABI: `from` in ecx, `out` in esi, the
// other arguments on the stack (caller pops); it calls two other static helpers of the same TU
// with register arguments (0x012030c0: L1 norm of a vector, arg in eax, result in xmm0;
// 0x01201c70: closest point on the triangle, vertices in ecx/eax/edx).
//
// Algorithm (Moller-Trumbore with the sphere radius as tolerance):
//   1. reject when the start is more than `radius` behind the plane, or the ray misses the
//      triangle grown by radius * |edge cross|_1;
//   2. face: cast the plane shifted by the radius; a hit inside the triangle returns feature
//      (u, v, 0, u) and the plane normal; otherwise the start is advanced to the plane;
//   3. closest point to the start: if the sphere already overlaps the triangle, return the
//      penetration (normal = start - closest, normalized);
//   4. up to 5 steps walking the triangle's vertices (ray vs sphere, 0x01206cd0) and edges
//      (ray vs capsule, 0x01205a30), moving to a neighbouring feature when the sweep leaves
//      the current one.  Features: 0..2 vertices, 3 = v0v1, 4 = v0v2, 5 = v1v2, 6 = face.
// out: +0x10 position, +0x20 normal, +0x30 feature coordinates, +0x40 fraction.
//
// All vector math is 4-wide SSE written as in Havok 3.1's hkVector4 (dot3 via two shuffles,
// cross via yzx/zxy shuffles, 2-step Newton-Raphson rcp/rsqrt).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (as s012080d0).

#include <xmmintrin.h>

typedef unsigned int uint32_t;

extern float gVolumeCastEpsilon;        // 0x0171e520 (.bss, set at runtime)

struct Real {           // float passed by value as a 4-byte struct (integer push)
    float f;
};
static __forceinline Real MakeReal(float x) { Real r; r.f = x; return r; }

struct CastFraction {   // hit parameter as numerator / denominator
    float num, den;
};

class TriangleVolume;
struct VolumeCastResult {
    const TriangleVolume* mpVolume;  // +0x00
    uint32_t pad[3];
    __m128 mPosition;               // +0x10
    __m128 mNormal;                 // +0x20
    __m128 mFeature;                // +0x30
    float mFraction;                // +0x40
};

// ray from+dir*t vs sphere(center, radius); returns <0 on error, else #roots (cdecl)
int RaySphereCast(CastFraction* t, const __m128* from, const __m128* dir, const __m128* center, Real radius);   // 0x01206cd0
// ray vs capsule around the segment point + s*axis (cdecl)
int RayCapsuleCast(CastFraction* t, const __m128* from, const __m128* dir, const __m128* point, const __m128* axis, Real axisLength2, Real radius, int a, int b);   // 0x01205a30
// closest point of triangle (v0, v1, v2) to p; returns the feature (0..2 vertex, 3..5 edge, 6 face)
// and the barycentric coordinates (u along v1-v0, v (along v2-v0)) (static, register ABI in the original)
int ClosestPointOnTriangle(const __m128& v0, const __m128& v1, const __m128& v2, __m128* closest, float* u, float* v, const __m128& p);   // 0x01201c70
// ray vs triangle without radius (cdecl)
int RayTriangleCast(VolumeCastResult* out, const __m128* from, const __m128* dir, const __m128* v0, const __m128* v1, const __m128* v2);   // 0x01201a20

// ---------------------------------------------------------------------------------------
// hkVector4-style SSE helpers
static __forceinline __m128 Splat(float f) { return _mm_set_ps1(f); }
static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }

union Vec4Access {
    __m128 v;
    float f[4];
};
static __forceinline float Get(__m128 v, int i)
{
    Vec4Access a;
    a.v = v;
    return a.f[i];
}
static __forceinline __m128 Vector4(float x, float y, float z, float w)
{
    Vec4Access a;
    a.f[0] = x;
    a.f[1] = y;
    a.f[2] = z;
    a.f[3] = w;
    return a.v;
}

// broadcast x*x' + (y*y' + z*z')
static __forceinline __m128 Dot3(__m128 a, __m128 b)
{
    __m128 x2 = _mm_mul_ps(a, b);
    __m128 r = _mm_add_ps(x2, _mm_add_ps(_mm_shuffle_ps(x2, x2, 1), _mm_shuffle_ps(x2, x2, 2)));
    return SplatX(r);
}

// a x b = a.yzx * b.zxy - b.yzx * a.zxy
static __forceinline __m128 Cross(__m128 a, __m128 b)
{
    __m128 c0 = _mm_mul_ps(_mm_shuffle_ps(b, b, 0x09), _mm_shuffle_ps(a, a, 0x12));
    __m128 c1 = _mm_mul_ps(_mm_shuffle_ps(a, a, 0x09), _mm_shuffle_ps(b, b, 0x12));
    return _mm_sub_ps(c1, c0);
}

// two Newton-Raphson steps of rcp
static __forceinline __m128 Reciprocal(float f)
{
    const __m128 two = Splat(2.0f);
    __m128 x = Splat(f);
    __m128 r = _mm_rcp_ps(x);
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), r);
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), r);
    return r;
}

// two Newton-Raphson steps of rsqrt, then d * (1/|d|)
static __forceinline __m128 Normalize3(__m128 d)
{
    const __m128 half = Splat(0.5f);
    const __m128 one = Splat(1.0f);
    __m128 len2 = Dot3(d, d);
    __m128 r = _mm_rsqrt_ps(len2);
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(len2, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(len2, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    return _mm_mul_ps(d, r);
}

// |x| + |y| + |z| summed as (|z| + |y|) + |x|
static __forceinline float AbsSum3Inline(const __m128& v)
{
    __m128 a = _mm_max_ps(_mm_mul_ps(Splat(-1.0f), v), v);
    return Get(a, 0) + Get(a, 1) + Get(a, 2);   // cl /fp:fast emits (z + y) + x, as the original
}
// 0x012030c0: the same helper out of line (the original inlines it at its first use only)
static __declspec(noinline) float AbsSum3(const __m128& v)
{
    return AbsSum3Inline(v);
}

// ---------------------------------------------------------------------------------------
// @ 0x01203110
static int SphereTriangleLinearCast(const __m128& from, VolumeCastResult* out, const __m128& sweep,
                                    const __m128& v0, const __m128& v1, const __m128& v2, Real radiusArg)
{
    const float radius = radiusArg.f;
    out->mFraction = 0.0f;
    __m128 e1 = _mm_sub_ps(v1, v0);
    __m128 e2 = _mm_sub_ps(v2, v0);
    __m128 start = _mm_sub_ps(from, v0);
    __m128 dir = sweep;

    // determinant and side of the triangle
    __m128 p = Cross(dir, e2);
    float det = Get(Dot3(e1, p), 0);
    float sign = 1.0f;
    int iterations = 5;
    if (0.0f > det) {
        sign = -1.0f;
        det = 0.0f - det;
    }

    // start more than radius behind the plane
    __m128 normal = out->mNormal;
    if (0.0f - radius > Get(Dot3(normal, start), 0) * sign)
        return 0;

    // barycentric bounds grown by the radius
    float u = Get(Dot3(start, p), 0) * sign;
    float uTolerance = AbsSum3Inline(p) * radius;
    if (0.0f - uTolerance > u)
        return 0;
    if (u > uTolerance + det)
        return 0;
    __m128 q = Cross(e1, dir);
    float v = Get(Dot3(start, q), 0) * sign;
    float vTolerance = AbsSum3(q) * radius;
    if (0.0f - vTolerance > v)
        return 0;
    if (v > vTolerance + det)
        return 0;
    if (v + u > (uTolerance + vTolerance) + det)
        return 0;

    // face: the plane moved towards the start by the radius
    if (det > gVolumeCastEpsilon) {
        __m128 shifted = _mm_sub_ps(start, _mm_mul_ps(normal, Splat(sign * radius)));
        __m128 n = Cross(e2, e1);
        float tNum = 0.0f - Get(Dot3(shifted, n), 0) * sign;
        if (tNum > det)
            return 0;
        if (tNum >= 0.0f) {
            float invDet = Get(Reciprocal(det), 0);
            float t = invDet * tNum;
            out->mFraction = t;
            float fu = Get(Dot3(shifted, p), 0) * sign;
            if (fu >= 0.0f && det >= fu) {
                float fv = Get(Dot3(shifted, q), 0) * sign;
                if (fv >= 0.0f && det >= fv + fu) {
                    out->mPosition = _mm_add_ps(from, _mm_mul_ps(dir, Splat(t)));
                    out->mNormal = _mm_mul_ps(out->mNormal, Splat(sign));
                    out->mFeature = Vector4(invDet * fu, invDet * fv, 0.0f, invDet * fu);
                    return 1;
                }
            }
            start = _mm_add_ps(start, _mm_mul_ps(dir, Splat(t)));
            dir = _mm_mul_ps(dir, Splat(1.0f - t));
        }
    }

    // closest feature to the (advanced) start
    __m128 pos = _mm_add_ps(start, v0);
    __m128 closest;
    float cu, cv;
    int feature = ClosestPointOnTriangle(v0, v1, v2, &closest, &cu, &cv, pos);
    __m128 d = _mm_sub_ps(pos, closest);
    float penetration = radius * radius - Get(Dot3(d, d), 0);
    if (penetration > 0.0f) {
        out->mPosition = pos;
        out->mNormal = d;
        out->mNormal = Normalize3(out->mNormal);
        out->mFeature = Vector4(cu, cv, penetration, cu);
        return 1;
    }
    if (feature == 6) {
        out->mPosition = pos;
        if (0.0f > det)
            out->mNormal = _mm_mul_ps(out->mNormal, Splat(-1.0f));
        out->mFeature = Vector4(cu, cv, 0.0f, cu);
        return 1;
    }

    // walk vertices and edges
    CastFraction hit;
    __m128 edgeAxis;
    do {
        iterations--;
        if (feature <= 2) {
            int r = RaySphereCast(&hit, &pos, &dir, &closest, radiusArg);
            if (r < 0)
                return 0;
            __m128 base, a, b;
            if (feature == 0) {
                base = v0;
                a = v1;
                b = v2;
            } else if (feature == 1) {
                a = v0;
                base = v1;
                b = v2;
            } else {
                a = v0;
                base = v2;
                b = v1;
            }
            a = _mm_sub_ps(a, base);
            b = _mm_sub_ps(b, base);
            float dA = Get(Dot3(dir, a), 0);
            if (dA > gVolumeCastEpsilon) {
                float sA = Get(Dot3(_mm_sub_ps(closest, pos), a), 0);
                if (sA > 0.0f && (r == 0 || sA * hit.den <= dA * hit.num)) {
                    hit.num = sA;
                    hit.den = dA;
                    r = (feature + 6) / 2;
                }
            }
            float dB = Get(Dot3(dir, b), 0);
            if (dB > gVolumeCastEpsilon) {
                float sB = Get(Dot3(_mm_sub_ps(closest, pos), b), 0);
                if (sB > 0.0f && (r == 0 || sB * hit.den <= dB * hit.num)) {
                    hit.den = dB;
                    hit.num = sB;
                    r = (feature + 9) / 2;
                }
            }
            if (r == 0)
                return 0;
            if (r <= 2) {
                // hit the vertex sphere
                float t = hit.num / hit.den;
                out->mFraction = t + out->mFraction;
                out->mPosition = _mm_add_ps(pos, _mm_mul_ps(dir, Splat(t)));
                out->mNormal = _mm_sub_ps(out->mPosition, closest);
                out->mNormal = _mm_mul_ps(out->mNormal, Reciprocal(radius));
                out->mFeature = Vector4((float)(feature == 1), (float)(feature == 2), 0.0f, (float)(feature == 1));
                return 1;
            }
            feature = r;
        } else {
            __m128 a, b;
            if (feature == 3) {
                a = v0;
                b = v1;
            } else if (feature == 4) {
                a = v0;
                b = v2;
            } else {
                a = v1;
                b = v2;
            }
            closest = a;
            edgeAxis = _mm_sub_ps(b, a);
            int r = RayCapsuleCast(&hit, &pos, &dir, &closest, &edgeAxis, MakeReal(Get(Dot3(edgeAxis, edgeAxis), 0)), radiusArg, 0, 0);
            if (r < 0)
                return 0;
            float dA = Get(Dot3(dir, edgeAxis), 0);
            if (dA > gVolumeCastEpsilon) {
                __m128 end = _mm_add_ps(closest, edgeAxis);
                float sB = Get(Dot3(_mm_sub_ps(end, pos), edgeAxis), 0);
                if (sB > 0.0f && (r == 0 || sB * hit.den <= dA * hit.num)) {
                    feature = feature / 2;
                    hit.num = sB;
                    hit.den = dA;
                    closest = end;
                    goto moved;
                }
            }
            {
                float nA = dA * -1.0f;
                if (nA > gVolumeCastEpsilon) {
                    float sA = Get(Dot3(_mm_sub_ps(pos, closest), edgeAxis), 0);
                    if (sA > 0.0f && (r == 0 || sA * hit.den <= hit.num * nA)) {
                        feature = (feature - 3) / 2;
                        hit.num = sA;
                        hit.den = nA;
                        goto moved;
                    }
                }
            }
            if (r == 0)
                return 0;
moved:
            if (feature > 2) {
                // hit the edge capsule
                float t = hit.num / hit.den;
                out->mFraction = t + out->mFraction;
                pos = _mm_add_ps(pos, _mm_mul_ps(dir, Splat(t)));
                __m128 inv = Reciprocal(Get(Dot3(edgeAxis, edgeAxis), 0));
                float s = Get(_mm_mul_ps(Dot3(_mm_sub_ps(pos, closest), edgeAxis), inv), 0);
                out->mNormal = _mm_sub_ps(pos, _mm_add_ps(closest, _mm_mul_ps(edgeAxis, Splat(s))));
                out->mNormal = _mm_mul_ps(out->mNormal, Reciprocal(radius));
                out->mPosition = pos;
                if (feature == 3) {
                    out->mFeature = Vector4(s, 0.0f, 0.0f, s);
                    return 1;
                }
                if (feature == 4) {
                    out->mFeature = Vector4(0.0f, s, 0.0f, 0.0f);
                    return 1;
                }
                out->mFeature = Vector4(1.0f - s, s, 0.0f, 1.0f - s);
                return 1;
            }
        }

        // moved onto a neighbouring feature: advance to the transition point
        float t = hit.num / hit.den;
        out->mFraction = (1.0f - out->mFraction) * t + out->mFraction;
        pos = _mm_add_ps(pos, _mm_mul_ps(dir, Splat(t)));
        dir = _mm_mul_ps(dir, Splat(1.0f - t));
        if (t > 1.0f)
            return 0;
    } while (iterations != 0);
    return 1;
}

// ---------------------------------------------------------------------------------------
// 0x01203ee0 (caller, not part of this slice): TriangleVolume::LinearCast
class TriangleVolume {
public:
    void GetWorldVertices(__m128* v0, __m128* v1, __m128* v2, const void* xf) const;   // 0x01202160
    void GetWorldNormal(__m128* normal, const void* xf) const;                       // 0x01202020
    int LinearCast(const __m128* from, const __m128* to, const void* xf, VolumeCastResult* out) const;

    __m128 mVertices[3];
    __m128 mNormal;
    float mField40[4];
    Real mRadius;                   // +0x50
};

int TriangleVolume::LinearCast(const __m128* from, const __m128* to, const void* xf, VolumeCastResult* out) const
{
    __m128 v0, v1, v2;
    GetWorldVertices(&v0, &v1, &v2, xf);
    out->mpVolume = this;
    if (mRadius.f == 0.0f) {
        __m128 dir = _mm_sub_ps(*to, *from);
        int hit = RayTriangleCast(out, from, &dir, &v0, &v1, &v2);
        if (hit)
            GetWorldNormal(&out->mNormal, xf);
        return hit;
    }
    GetWorldNormal(&out->mNormal, xf);
    __m128 dir = _mm_sub_ps(*to, *from);
    return SphereTriangleLinearCast(*from, out, dir, v0, v1, v2, mRadius);
}
