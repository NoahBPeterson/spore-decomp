// Slice s01205c00 — 0x01205f30, 2860 bytes.
//
// CapsuleVolume linear cast (slot 4 of the "CapsuleVolume" entry of the collision-volume type
// table at 0x015d0ab4: { type 2, 0x01205c00, 0x012075f0, 0x012059b0, 0x01205e20, 0x01205f30,
// 0x011fb220, "CapsuleVolume" }).  Same signature and output layout as the BoxVolume cast
// (slice s012080d0) and the sphere cast (0x01206e50).
//
// The capsule is the segment (0,0,-h)..(0,0,+h) of the volume's local z axis (h = mHalfHeight,
// +0x44) swept by mRadius (+0x50).  The segment from -> to (world space, optionally through the
// parent transform `xf`) is moved into capsule space.  The start is classified by its z: above
// the top cap (side +1), below the bottom cap (-1) or within the cylinder slab (0).  Then up to
// three steps walk the features: a cap (ray vs sphere around (0,0,side*h), 0x01206cd0, or the
// crossing of the cap plane z = side*h, which moves to the cylinder) and the cylinder side
// (closed-form ray vs infinite cylinder of radius mRadius around the z axis, or the crossing of a
// cap plane, which moves to that cap).  On a hit `out` receives the world position (+0x10), the
// world normal (+0x20), the feature (+0x30: side, dir.z, start.z, side) and the accumulated
// fraction (+0x40); out->mpVolume = this.  Returns 1 on a hit, 0 otherwise.
//
// All vector math is 4-wide SSE written as in Havok 3.1's hkVector4 (dot3 via two shuffles,
// cross via yzx/zxy shuffles, 2-step Newton-Raphson rsqrt).  The inverse transform's w lane is
// left uninitialized, as in the original (it never reaches an output).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (as s012080d0).
//
// @ 0x01205f30

#include <xmmintrin.h>
#include <math.h>

typedef unsigned int uint32_t;

struct Transform4 {     // rotation columns + translation, 16-byte aligned
    __m128 c0, c1, c2, t;
};

struct Real {           // float passed by value as a 4-byte struct (integer push)
    float f;
    Real(float x) : f(x) {}
};

struct CastFraction {   // hit parameter as numerator / denominator
    float num, den;
};

class CapsuleVolume;
struct VolumeCastResult {
    const CapsuleVolume* mpVolume;  // +0x00
    uint32_t pad[3];
    __m128 mPosition;               // +0x10 (world)
    __m128 mNormal;                 // +0x20 (world)
    __m128 mFeature;                // +0x30 (side, dir.z, start.z, side)
    float mFraction;                // +0x40
};

// ray from+dir*t vs sphere(center, radius); returns <0 on error, else #roots (cdecl)
int RaySphereCast(CastFraction* t, const __m128* from, const __m128* dir, const __m128* center, Real radius);   // 0x01206cd0

// ---------------------------------------------------------------------------------------
// hkVector4-style SSE helpers
static __forceinline __m128 Splat(float f) { return _mm_set_ps1(f); }
static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }
static __forceinline __m128 SplatY(__m128 v) { return _mm_shuffle_ps(v, v, 0x55); }
static __forceinline __m128 SplatZ(__m128 v) { return _mm_shuffle_ps(v, v, 0xaa); }

// v.x = s.x / v.y = s.x / v.z = s.x, other lanes kept
static __forceinline __m128 SetX(__m128 v, __m128 s)
{
    __m128 r = _mm_shuffle_ps(v, s, 0x05);          // (v1, v1, s0, s0)
    return _mm_shuffle_ps(r, v, 0xe2);              // (s0, v1, v2, v3)
}
static __forceinline __m128 SetY(__m128 v, __m128 s)
{
    __m128 r = _mm_shuffle_ps(v, s, 0x00);          // (v0, v0, s0, s0)
    return _mm_shuffle_ps(r, v, 0xe8);              // (v0, s0, v2, v3)
}
static __forceinline __m128 SetZ(__m128 v, __m128 s)
{
    __m128 r = _mm_shuffle_ps(v, s, 0x0f);          // (v3, v3, s0, s0)
    return _mm_shuffle_ps(v, r, 0x24);              // (v0, v1, s0, v3)
}

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

// r = M.c0*v.x + M.c1*v.y + M.c2*v.z  (grouped as ((c0*x + c1*y) + c2*z))
static __forceinline __m128 RotateBy(const __m128& c0, const __m128& c1, const __m128& c2, const __m128& v)
{
    __m128 r = _mm_add_ps(_mm_mul_ps(c0, SplatX(v)), _mm_mul_ps(c1, SplatY(v)));
    return _mm_add_ps(r, _mm_mul_ps(c2, SplatZ(v)));
}

// the same with the components of v read from memory (movss + shufps)
static __forceinline __m128 RotateByMem(const __m128& c0, const __m128& c1, const __m128& c2, const __m128* v)
{
    const float* f = (const float*)v;
    __m128 r = _mm_add_ps(_mm_mul_ps(c0, Splat(f[0])), _mm_mul_ps(c1, Splat(f[1])));
    return _mm_add_ps(r, _mm_mul_ps(c2, Splat(f[2])));
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

// ---------------------------------------------------------------------------------------
class CapsuleVolume {
public:
    Transform4 mTransform;          // +0x00
    float mField40;                 // +0x40
    float mHalfHeight;              // +0x44
    float mField48[2];              // +0x48
    float mRadius;                  // +0x50

    int LinearCast(const __m128* from, const __m128* to, const Transform4* xf, VolumeCastResult* out);
};

// 0x01205f30
int CapsuleVolume::LinearCast(const __m128* from, const __m128* to, const Transform4* xf, VolumeCastResult* out)
{
    const __m128 base = Vector4(0.0f, 0.0f, 0.0f, 0.0f);   // capsule axis: base + s*axis
    const __m128 axis = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
    out->mpVolume = this;
    int iterations = 3;

    // world transform of the capsule
    Transform4 world;
    __m128 c0 = mTransform.c0, c1, c2, t;
    if (xf) {
        world.c0 = RotateBy(xf->c0, xf->c1, xf->c2, c0);
        world.c1 = RotateBy(xf->c0, xf->c1, xf->c2, mTransform.c1);
        world.c2 = RotateBy(xf->c0, xf->c1, xf->c2, mTransform.c2);
        world.t = _mm_add_ps(_mm_mul_ps(xf->t, Splat(1.0f)), RotateBy(xf->c0, xf->c1, xf->c2, mTransform.t));
        c0 = world.c0; c1 = world.c1; c2 = world.c2; t = world.t;
    } else {
        c1 = mTransform.c1; c2 = mTransform.c2; t = mTransform.t;
    }

    // inverse: transposed rotation, translation -(R^T t); w lane left uninitialized
    __m128 r0 = _mm_shuffle_ps(_mm_shuffle_ps(c0, c1, 0x00), c2, 0x08);
    __m128 r1 = _mm_shuffle_ps(_mm_shuffle_ps(c0, c1, 0x11), c2, 0x18);
    __m128 r2 = _mm_shuffle_ps(_mm_shuffle_ps(c0, c1, 0x22), c2, 0x28);
    __m128 zero = _mm_setzero_ps();
    __m128 tx = SplatX(t), ty = SplatY(t), tz = SplatZ(t);
    __m128 invT;
    invT = SetX(invT, _mm_sub_ps(zero, _mm_add_ps(_mm_add_ps(_mm_mul_ps(tx, SplatX(c0)), _mm_mul_ps(ty, SplatY(c0))), _mm_mul_ps(tz, SplatZ(c0)))));
    invT = SetY(invT, _mm_sub_ps(zero, _mm_add_ps(_mm_add_ps(_mm_mul_ps(tx, SplatX(c1)), _mm_mul_ps(ty, SplatY(c1))), _mm_mul_ps(tz, SplatZ(c1)))));
    invT = SetZ(invT, _mm_sub_ps(zero, _mm_add_ps(_mm_add_ps(_mm_mul_ps(tx, SplatX(c2)), _mm_mul_ps(ty, SplatY(c2))), _mm_mul_ps(tz, SplatZ(c2)))));

    __m128 localFrom = _mm_add_ps(RotateByMem(r0, r1, r2, from), invT);
    __m128 localTo = _mm_add_ps(RotateByMem(r0, r1, r2, to), invT);
    __m128 dir = _mm_sub_ps(localTo, localFrom);

    const float h = mHalfHeight;
    const float radius = mRadius;
    float startZ = Get(localFrom, 2);
    float side;
    if (startZ > h)
        side = 1.0f;
    else if (0.0f - h > startZ)
        side = -1.0f;
    else
        side = 0.0f;

    out->mPosition = localFrom;
    out->mFraction = 0.0f;

    CastFraction hit;
    for (;;) {
        float num = 0.0f;
        float den = 0.0f;
        if (side != 0.0f) {
            // cap: ray vs the sphere at the end of the segment, or the crossing of the cap plane
            __m128 center = Vector4(0.0f, 0.0f, side * h, 0.0f);
            int n = RaySphereCast(&hit, &out->mPosition, &dir, &center, radius);
            if (n > 0 && hit.num == 0.0f) {
                // already touching the cap sphere
                out->mPosition = localFrom;
                out->mNormal = Normalize3(_mm_sub_ps(out->mPosition, center));
                goto toWorld;
            }
            int crossing;
            if (0.0f > Get(dir, 2) * side) {
                __m128 p = out->mPosition;
                num = (0.0f - h) - (0.0f - Get(p, 2)) * side;
                den = 0.0f - Get(dir, 2) * side;
                if (den >= num)
                    crossing = 1;
                else
                    crossing = 0;
            } else {
                crossing = 0;
            }
            if (n > 0 && (crossing <= 0 || hit.den * num > hit.num * den)) {
                // hit the cap sphere
                float step = hit.num / hit.den;
                out->mFraction += step;
                out->mPosition = _mm_add_ps(out->mPosition, _mm_mul_ps(dir, Splat(step)));
                out->mNormal = _mm_sub_ps(out->mPosition, center);
                break;
            }
            if (crossing <= 0)
                return 0;
            side = 0.0f;
        } else {
            // cylinder side: |(p + s*d - base) x axis|^2 = radius^2
            __m128 p = out->mPosition;
            __m128 e = Cross(_mm_sub_ps(base, p), axis);
            float dist2 = Get(Dot3(e, e), 0);
            const float radius2 = radius * radius;
            if (radius2 > dist2) {
                // start inside the cylinder: radial normal
inside:
                out->mNormal = _mm_sub_ps(out->mPosition, base);
                out->mNormal = _mm_add_ps(out->mNormal, _mm_mul_ps(axis, _mm_sub_ps(zero, Dot3(out->mNormal, axis))));
                out->mNormal = Normalize3(out->mNormal);
                goto toWorld;
            }
            __m128 q = Cross(dir, axis);
            float b = Get(Dot3(e, q), 0);
            if (0.0f >= b)
                return 0;
            float a = Get(Dot3(q, q), 0);
            float disc = (b * b - dist2 * a) + radius2 * a;
            if (0.0f > disc)
                return 0;
            float bma = b - a;
            if (bma >= 0.0f && bma * bma >= disc)
                return 0;
            float s = b - sqrtf(disc);
            if (s == 0.0f)
                goto inside;
            if (Get(dir, 2) >= 0.0f)
                side = 1.0f;
            else
                side = -1.0f;
            float axial = Get(Dot3(p, axis), 0);
            num = (0.0f - axial) * side + h;
            den = Get(dir, 2) * side;
            if (!(den >= num && s * den > num * a)) {
                // hit the cylinder side
                float step = s / a;
                out->mFraction += step;
                out->mPosition = _mm_add_ps(out->mPosition, _mm_mul_ps(dir, Splat(step)));
                out->mNormal = _mm_sub_ps(out->mPosition, base);
                out->mNormal = _mm_add_ps(out->mNormal, _mm_mul_ps(axis, _mm_sub_ps(zero, Dot3(out->mNormal, axis))));
                side = 0.0f;
                break;
            }
        }

        // advance to the cap plane and continue with the next feature
        float step = num / den;
        out->mFraction += step;
        out->mPosition = _mm_add_ps(out->mPosition, _mm_mul_ps(dir, Splat(step)));
        dir = _mm_sub_ps(localTo, out->mPosition);
        if (--iterations == 0)
            return 0;
    }

    // surface hit: (position - feature) / radius
    out->mNormal = _mm_div_ps(out->mNormal, SplatX(Splat(radius)));

toWorld:
    // back to world space
    if (xf) {
        out->mPosition = _mm_add_ps(RotateByMem(world.c0, world.c1, world.c2, &out->mPosition), world.t);
        out->mNormal = RotateByMem(world.c0, world.c1, world.c2, &out->mNormal);
    } else {
        out->mPosition = _mm_add_ps(RotateByMem(mTransform.c0, mTransform.c1, mTransform.c2, &out->mPosition), mTransform.t);
        out->mNormal = RotateByMem(mTransform.c0, mTransform.c1, mTransform.c2, &out->mNormal);
    }
    out->mFeature = Vector4(side, Get(dir, 2), startZ, side);
    return 1;
}
