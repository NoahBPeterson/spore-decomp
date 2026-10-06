// Slice s012080d0 — 0x012080d0, 3976 bytes.
//
// BoxVolume linear cast (slot 4 of the "BoxVolume" entry of the collision-volume type table at
// 0x015d0b04: { type 4, 0x01209060, 0x012075f0, 0x01207600, 0x01207f30, 0x012080d0, 0x011fb220,
// "BoxVolume" }).  The sibling tables are "CapsuleVolume", "SphereVolume" and "AggregateVolume";
// the sphere's slot 4 (0x01206e50) has the same signature and output layout.
//
// Casts the segment from -> to (world space; optionally through the volume's parent transform
// `xf`) against a box with half extents mHalfExtents rounded by mRadius.  The segment is moved
// into box space (inverse of xf*box), each axis is classified (below / inside / above its slab),
// and then up to six steps walk the rounded box features: a vertex (ray vs sphere, 0x01206cd0),
// an edge (ray vs capsule, 0x01205a30) or a face (slab planes).  On a hit `out` receives the
// world position (+0x10), world normal (+0x20), the feature region (+0x30, w = x) and the
// accumulated fraction (+0x40); out->mpVolume = this.  Returns 1 on a hit, 0 otherwise.
//
// All vector math is 4-wide SSE (w lanes are carried but never reach an output except through
// the documented 4-wide transforms); the scalar compares are written so NaN takes the same
// branch as the original comiss/ucomiss tests.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (scalar SSE math, no cookie, no EH).
//
// @ 0x012080d0

#include <xmmintrin.h>

typedef unsigned int uint32_t;

extern float gVolumeCastTolerance;      // 0x0171e6f4 (.bss, set at runtime)

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

class BoxVolume;
struct VolumeCastResult {
    const BoxVolume* mpVolume;      // +0x00
    uint32_t pad[3];
    __m128 mPosition;               // +0x10 (world)
    __m128 mNormal;                 // +0x20 (world)
    __m128 mFeature;                // +0x30 (box-space region, -1/0/+1 per axis, w = x)
    float mFraction;                // +0x40
};

// ray from+dir*t vs sphere(center, radius); returns <0 on error, else #roots (cdecl)
int RaySphereCast(CastFraction* t, const __m128* from, const __m128* dir, const __m128* center, Real radius);   // 0x01206cd0
// ray vs capsule/cylinder around `point` along `axis` (cdecl)
int RayCapsuleCast(CastFraction* t, const __m128* from, const __m128* dir, const __m128* point, const __m128* axis, Real axisScale, Real radius, int a, int b);   // 0x01205a30

// ---------------------------------------------------------------------------------------
// small SSE helpers
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
static __forceinline __m128 WithComponent(__m128 v, int i, float f)
{
    Vec4Access a;
    a.v = v;
    a.f[i] = f;
    return a.v;
}
static __forceinline __m128 Vector3W(float x, float y, float z)   // (x, y, z, x)
{
    Vec4Access a;
    a.f[0] = x;
    a.f[1] = y;
    a.f[2] = z;
    a.f[3] = x;
    return a.v;
}

// r = M.c0*v.x + M.c1*v.y + M.c2*v.z  (grouped as ((c0*x + c1*y) + c2*z))
static __forceinline __m128 RotateBy(const __m128& c0, const __m128& c1, const __m128& c2, const __m128& v)
{
    __m128 r = _mm_add_ps(_mm_mul_ps(c0, SplatX(v)), _mm_mul_ps(c1, SplatY(v)));
    return _mm_add_ps(r, _mm_mul_ps(c2, SplatZ(v)));
}

// two Newton-Raphson steps of rsqrt, then d * (1/|d|)
static __forceinline __m128 Normalize3(__m128 d)
{
    const __m128 half = Splat(0.5f);
    const __m128 one = Splat(1.0f);
    __m128 sq = _mm_mul_ps(d, d);
    __m128 len2 = _mm_add_ps(sq, _mm_add_ps(_mm_shuffle_ps(sq, sq, 1), _mm_shuffle_ps(sq, sq, 2)));
    len2 = SplatX(len2);
    __m128 r = _mm_rsqrt_ps(len2);
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(len2, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(len2, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    return _mm_mul_ps(d, r);
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

static __forceinline int NextAxis(int i) { return (1 << i) & 3; }

// ---------------------------------------------------------------------------------------
class BoxVolume {
public:
    Transform4 mTransform;          // +0x00
    float mField40;                 // +0x40
    float mHalfExtents[3];          // +0x44
    float mRadius;                  // +0x50

    int LinearCast(const __m128* from, const __m128* to, const Transform4* xf, VolumeCastResult* out);
};

// 0x012080d0
int BoxVolume::LinearCast(const __m128* from, const __m128* to, const Transform4* xf, VolumeCastResult* out)
{
    float bestSep = -3.402823466e+38F;
    int bestAxis = 0;
    float bestSign = 1.0f;
    float halfExt[3];
    halfExt[0] = mHalfExtents[0];
    halfExt[1] = mHalfExtents[1];
    halfExt[2] = mHalfExtents[2];
    int numInside = 0;
    int axis = 0;
    int iterations = 6;

    // world transform of the box
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

    // inverse: transposed rotation, translation -(R^T t)
    __m128 r0 = _mm_shuffle_ps(_mm_shuffle_ps(c0, c1, 0x00), c2, 0x08);
    __m128 r1 = _mm_shuffle_ps(_mm_shuffle_ps(c0, c1, 0x11), c2, 0x18);
    __m128 r2 = _mm_shuffle_ps(_mm_shuffle_ps(c0, c1, 0x22), c2, 0x28);
    __m128 zero = _mm_setzero_ps();
    __m128 tx = SplatX(t), ty = SplatY(t), tz = SplatZ(t);
    __m128 invT = zero;
    invT = SetX(invT, _mm_sub_ps(zero, _mm_add_ps(_mm_add_ps(_mm_mul_ps(tx, SplatX(c0)), _mm_mul_ps(ty, SplatY(c0))), _mm_mul_ps(tz, SplatZ(c0)))));
    invT = SetY(invT, _mm_sub_ps(zero, _mm_add_ps(_mm_add_ps(_mm_mul_ps(tx, SplatX(c1)), _mm_mul_ps(ty, SplatY(c1))), _mm_mul_ps(tz, SplatZ(c1)))));
    invT = SetZ(invT, _mm_sub_ps(zero, _mm_add_ps(_mm_add_ps(_mm_mul_ps(tx, SplatX(c2)), _mm_mul_ps(ty, SplatY(c2))), _mm_mul_ps(tz, SplatZ(c2)))));

    __m128 localFrom = _mm_add_ps(RotateBy(r0, r1, r2, *from), invT);
    __m128 localTo = _mm_add_ps(RotateBy(r0, r1, r2, *to), invT);
    __m128 dir = _mm_sub_ps(localTo, localFrom);

    // classify the start point against the three slabs
    float sign[3];
    float region[3];
    for (int i = 0; i < 3; i++) {
        float d = Get(dir, i);
        float p = Get(localFrom, i);
        sign[i] = d >= 0.0f ? 1.0f : -1.0f;
        float lo = 0.0f - halfExt[i];
        float sepLo = lo - p;
        if (sepLo > bestSep) {
            bestSep = sepLo;
            bestAxis = i;
            bestSign = -1.0f;
        }
        float sepHi = p - halfExt[i];
        if (sepHi > bestSep) {
            bestSep = sepHi;
            bestAxis = i;
            bestSign = 1.0f;
        }
        if (lo > p) {
            region[i] = -1.0f;
        } else if (p > halfExt[i]) {
            region[i] = 1.0f;
        } else {
            numInside++;
            if (numInside == 1)
                axis = i;
            else if (numInside == 2)
                axis = (3 - i) - axis;
            region[i] = 0.0f;
        }
    }

    out->mpVolume = this;
    out->mFraction = 0.0f;

    CastFraction hit;
    __m128 normal;
    for (;;) {
        if (numInside & 2) {
            if (numInside != 2) {
                // start point inside the box: push out along the axis of least penetration
                normal = WithComponent(zero, bestAxis, bestSign);
                break;
            }
            // two axes inside: only the face of `axis` can be hit
            float r = region[axis];
            float a = Get(localFrom, axis) * r - (halfExt[axis] + mRadius);
            int hitAxis = axis;
            if (0.0f >= a) {
                normal = WithComponent(zero, axis, region[axis]);
                break;
            }
            float b = 0.0f - Get(dir, axis) * r;
            hit.num = a;
            hit.den = b;
            if (gVolumeCastTolerance > b)
                return 0;
            if (a * gVolumeCastTolerance > b)
                return 0;
            int found = b > a ? 1 : 0;
            for (int j = NextAxis(axis); j != axis; j = NextAxis(j)) {
                if (sign[j] != 0.0f) {
                    float ns = 0.0f - sign[j];
                    float a2 = Get(localFrom, j) * ns - (0.0f - halfExt[j]);
                    float cn, cd;
                    if (0.0f >= a2) {
                        cn = 0.0f;
                        cd = 1.0f;
                    } else {
                        float b2 = 0.0f - Get(dir, j) * ns;
                        cn = a2;
                        cd = b2;
                        if (gVolumeCastTolerance > b2)
                            continue;
                        if (a2 * gVolumeCastTolerance > b2)
                            continue;
                        if (!(b2 > a2))
                            continue;
                    }
                    if (found > 0 && cn * hit.den > cd * hit.num)
                        continue;
                    hit.num = cn;
                    hit.den = cd;
                    hitAxis = j;
                    found = 1;
                }
            }
            if (found <= 0)
                return 0;
            if (hitAxis == axis) {
                normal = WithComponent(zero, axis, region[axis]);
                float step = hit.num / hit.den;
                out->mFraction = step + out->mFraction;
                localFrom = _mm_add_ps(localFrom, _mm_mul_ps(dir, Splat(step)));
                break;
            }
            region[hitAxis] = sign[hitAxis];
            axis = 3 - hitAxis - axis;
            numInside = 1;
        } else {
            __m128 feature = Vector3W(region[0] * halfExt[0], region[1] * halfExt[1], region[2] * halfExt[2]);
            if (numInside == 0) {
                // vertex region: rounded corner (sphere) or one of the three face slabs
                int n = RaySphereCast(&hit, &localFrom, &dir, &feature, mRadius);
                if (n < 0)
                    return 0;
                if (0.0f >= mRadius) {
                    n = 0;
                } else if (n > 0 && hit.num == 0.0f) {
                    normal = Normalize3(_mm_sub_ps(localFrom, feature));
                    break;
                }
                int crossed = -1;
                for (int i = 0; i < 3; i++) {
                    if (0.0f > sign[i] * region[i]) {
                        float r = region[i];
                        float a = Get(localFrom, i) * r - halfExt[i];
                        float cn, cd;
                        if (0.0f >= a) {
                            cn = 0.0f;
                            cd = 1.0f;
                        } else {
                            float b = 0.0f - Get(dir, i) * r;
                            cn = a;
                            cd = b;
                            if (gVolumeCastTolerance > b)
                                continue;
                            if (a * gVolumeCastTolerance > b)
                                continue;
                            if (!(b > a))
                                continue;
                        }
                        if (n > 0 && cn * hit.den > cd * hit.num)
                            continue;
                        hit.num = cn;
                        hit.den = cd;
                        crossed = i;
                        n = 1;
                    }
                }
                if (n <= 0)
                    return 0;
                if (crossed < 0) {
                    // hit the rounded corner
                    float step = hit.num / hit.den;
                    out->mFraction = step + out->mFraction;
                    localFrom = _mm_add_ps(localFrom, _mm_mul_ps(dir, Splat(step)));
                    normal = _mm_mul_ps(_mm_sub_ps(localFrom, feature), Reciprocal(mRadius));
                    break;
                }
                region[crossed] = 0.0f;
                axis = crossed;
                numInside = 1;
            } else {
                // edge region along `axis`: rounded edge (capsule) or the slabs of the other axes
                __m128 edgeAxis = Vector3W((float)(axis == 0), (float)(axis == 1), (float)(axis == 2));
                int m = RayCapsuleCast(&hit, &localFrom, &dir, &feature, &edgeAxis, 1.0f, mRadius, 0, 0);
                int hitAxis = axis;
                if (m < 0)
                    return 0;
                if (0.0f >= mRadius) {
                    m = 0;
                } else if (m > 0 && hit.num == 0.0f) {
                    normal = Normalize3(WithComponent(_mm_sub_ps(localFrom, feature), axis, 0.0f));
                    break;
                }
                float s = Get(dir, axis) > 0.0f ? 1.0f : -1.0f;
                float edgeNum = halfExt[axis] - Get(localFrom, axis) * s;
                float edgeDen = Get(dir, axis) * s;
                if (1.175494351e-38F > edgeDen)
                    edgeDen = 1.0f;
                int found = edgeDen >= edgeNum ? 1 : 0;
                for (int j = NextAxis(axis); j != axis; j = NextAxis(j)) {
                    if (0.0f > sign[j] * region[j]) {
                        float r = region[j];
                        float a = Get(localFrom, j) * r - halfExt[j];
                        float cn, cd;
                        if (0.0f >= a) {
                            cn = 0.0f;
                            cd = 1.0f;
                        } else {
                            float b = 0.0f - Get(dir, j) * r;
                            cn = a;
                            cd = b;
                            if (gVolumeCastTolerance > b)
                                continue;
                            if (a * gVolumeCastTolerance > b)
                                continue;
                            if (!(b > a))
                                continue;
                        }
                        if (found > 0 && edgeDen * cn > cd * edgeNum)
                            continue;
                        edgeNum = cn;
                        edgeDen = cd;
                        hitAxis = j;
                        found = 1;
                    }
                }
                if (m > 0 && (found <= 0 || !(edgeDen * hit.num > edgeNum * hit.den))) {
                    // hit the rounded edge
                    float step = hit.num / hit.den;
                    out->mFraction = step + out->mFraction;
                    localFrom = _mm_add_ps(localFrom, _mm_mul_ps(dir, Splat(step)));
                    __m128 d = WithComponent(_mm_sub_ps(localFrom, feature), axis, 0.0f);
                    normal = _mm_mul_ps(d, Reciprocal(mRadius));
                    break;
                }
                if (found <= 0)
                    return 0;
                if (hitAxis == axis) {
                    region[hitAxis] = sign[hitAxis];
                    numInside = 0;
                } else {
                    region[hitAxis] = 0.0f;
                    axis = 3 - hitAxis - axis;
                    numInside = 2;
                }
                hit.num = edgeNum;
                hit.den = edgeDen;
            }
        }

        // advance to the next feature
        float step = hit.num / hit.den;
        out->mFraction = step + out->mFraction;
        localFrom = _mm_add_ps(localFrom, _mm_mul_ps(dir, Splat(step)));
        dir = _mm_sub_ps(localTo, localFrom);
        if (--iterations == 0)
            return 0;
    }

    // back to world space
    if (xf) {
        out->mPosition = _mm_add_ps(RotateBy(world.c0, world.c1, world.c2, localFrom), world.t);
        out->mNormal = RotateBy(world.c0, world.c1, world.c2, normal);
    } else {
        out->mPosition = _mm_add_ps(RotateBy(mTransform.c0, mTransform.c1, mTransform.c2, localFrom), mTransform.t);
        out->mNormal = RotateBy(mTransform.c0, mTransform.c1, mTransform.c2, normal);
    }
    out->mFeature = Vector3W(region[0], region[1], region[2]);
    return 1;
}
