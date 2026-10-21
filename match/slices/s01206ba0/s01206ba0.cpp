// Slice s01206ba0 -- 0x01206ba0 .. 0x01207600 (13 functions).
//
// RenderWare 4 collision volumes, "sphere" family plus a few volume-instance interval
// helpers shared with the box/aggregate modules.  The 2008 dev PDB names the members of
// this family (rwcSphereLineSegIntersect, SphereVolume::GetBBox, ::CreateGPInstance,
// ::LineSegIntersect, ::GetInterval, ::GetMaximumFeature, ::Initialize,
// SphereVolumeInstance_GetBBox/GetInterval/GetIntervals, AggregateVolume::GetBBox,
// BoxVolumeInstance_GetInterval/GetIntervals); the retail layout matches the PDB's
// rw::collision::Volume (Matrix44Affine at +0x0, vTable at +0x40, radius at +0x50).
//
// This address range is inside RenderWare 4 core (symbols/renderware4_core.txt), built
// with /GL+/LTCG, so the calling functions cannot be byte-exact single-object; they are
// written complete and behaviourally equivalent.  The leaf helpers may still match.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (as the neighbouring volume slices).

#include <xmmintrin.h>
#include <math.h>

typedef unsigned int uint32_t;

// ---------------------------------------------------------------------------------------
// rw::math::vpu vectors / matrices (16-byte aligned, 4-wide)
struct Matrix44Affine {         // +0x00 .. +0x3f, row-major, row 3 = translation
    __m128 r0, r1, r2, r3;
};

struct CastFraction {           // line-segment hit parameter as numerator / denominator
    float num, den;
};

struct Matrix44Affine;

struct AABB {                   // two 4-wide vectors
    __m128 mn;
    __m128 mx;
    AABB* Transform(AABB* out, const Matrix44Affine* xf);   // 0x01204780
};

// ---------------------------------------------------------------------------------------
// hkVector4-style SSE helpers (same spellings the sibling volume slices converged on)
static __forceinline __m128 Splat(float f) { return _mm_set_ps1(f); }
static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }
static __forceinline __m128 SplatY(__m128 v) { return _mm_shuffle_ps(v, v, 0x55); }
static __forceinline __m128 SplatZ(__m128 v) { return _mm_shuffle_ps(v, v, 0xaa); }

// broadcast x*x' + (y*y' + z*z')
static __forceinline __m128 Dot3(__m128 a, __m128 b)
{
    __m128 x2 = _mm_mul_ps(a, b);
    __m128 r = _mm_add_ps(x2, _mm_add_ps(_mm_shuffle_ps(x2, x2, 1), _mm_shuffle_ps(x2, x2, 2)));
    return SplatX(r);
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

// row `v` (a row of `b`) transformed by the affine matrix `a` as a direction
static __forceinline __m128 Compose(const __m128& a0, const __m128& a1, const __m128& a2, const __m128& v)
{
    return _mm_add_ps(_mm_add_ps(_mm_mul_ps(a0, SplatX(v)), _mm_mul_ps(a1, SplatY(v))),
                      _mm_mul_ps(a2, SplatZ(v)));
}

// ---------------------------------------------------------------------------------------
// The collision volume.  `transform` is the volume's world placement (row-major), the
// vTable pointer sits at +0x40 and radius/ids follow it.
struct VolumeVTable;            // 0x24 bytes, not needed member-by-member here

class Volume {
public:
    Matrix44Affine mTransform;  // +0x00
    VolumeVTable*  mpVTable;    // +0x40
    uint32_t       mAggregateData; // +0x44
    uint32_t       mPad48;      // +0x48
    uint32_t       mPad4c;      // +0x4c
    float          mRadius;     // +0x50
    uint32_t       mGroupID;    // +0x54
    uint32_t       mSurfaceID;  // +0x58
    uint32_t       mFlags;      // +0x5c
};

class SphereVolume : public Volume {
public:
    int GetBBox(const Matrix44Affine* xf, const void* unused, AABB* out);              // 0x01206a60
    int CreateGPInstance(void* out, const Matrix44Affine* xf);                        // 0x01206c10
    int LineSegIntersect(const __m128* from, const __m128* to, const Matrix44Affine* xf, void* out); // 0x01206e50
    int GetInterval(const void* a, const void* b);                                    // 0x012075f0
    int GetMaximumFeature(const void* a, const void* b, void* out);                   // 0x01207600
};

class AggregateVolume : public Volume {
public:
    int GetBBox(const Matrix44Affine* xf, const void* unused, AABB* out);             // 0x01207180
};

// ---------------------------------------------------------------------------------------
// helper declarations (addresses masked by the byte checker, resolved by equiv.py)
// 0x01206b20 / 0x01206b50 / 0x01206ba0 are the GP-instance callbacks installed by
// SphereVolume::CreateGPInstance at out+0x90/0x94/0x98.
// 0x01204780: transform an AABB by an optional affine matrix (AABB* src, AABB* dst, matrix).
// AABB::Transform below is that helper (thiscall: ecx = source AABB).


// the relocation stubs the volume tables use when a volume is copied/resolved
void* rwcRelocateReturnSecond(void* a, void* b);                            // 0x011eb0d0
int   rwcRelocateReturnOne(void* a, void* b);                              // 0x012057f0
void  rwcRelocateNoOp();                                                   // 0x011fb220

// 0x01206cd0
int rwcSphereLineSegIntersect(CastFraction* t, const __m128* from, const __m128* dir,
                              const __m128* center, float radius);

// =======================================================================================
// SphereVolumeInstance callbacks (installed at instance+0x90/0x94/0x98)

// @ 0x01206b20
void SphereVolumeInstance_GetBBox(const __m128* src, const void* a, const void* b, void* out)
{
    (void)a; (void)b;
    __m128* o = (__m128*)out;
    o[0x12] = *src;                          // +0x120: sphere centre
    *(uint32_t*)((char*)out + 0x130) = 0;    // feature type
    *(uint32_t*)out = 0;                     // result
}

// @ 0x01206b50
void SphereVolumeInstance_GetInterval(const __m128* dir, const __m128* pt, float* out)
{
    float d = Get(Dot3(*pt, *dir), 0);
    out[0] = d;
    out[1] = d;
}

// @ 0x01206ba0
void SphereVolumeInstance_GetIntervals(const __m128* dir, const __m128* pts, uint32_t count, float* out)
{
    while (count--) {
        float d = Get(Dot3(*pts, *dir), 0);
        out[0] = d;
        out[1] = d;
        out += 4;
        ++pts;
    }
}

// =======================================================================================

// 0x01206bc0 is inside 0x01206ba0's loop; kept as an inline above.

// @ 0x01206a60
int SphereVolume::GetBBox(const Matrix44Affine* xf, const void* unused, AABB* out)
{
    (void)unused;
    const __m128 t = mTransform.r3;
    __m128 center;
    if (xf) {
        center = _mm_add_ps(
                    _mm_add_ps(_mm_add_ps(_mm_mul_ps(xf->r0, SplatX(t)),
                                          _mm_mul_ps(xf->r1, SplatY(t))),
                               _mm_mul_ps(xf->r2, SplatZ(t))),
                    _mm_mul_ps(xf->r3, Splat(1.0f)));
    } else {
        center = t;
    }
    __m128 r = Splat(mRadius);
    out->mn = _mm_sub_ps(center, r);
    out->mx = _mm_add_ps(center, r);
    return 1;
}

// @ 0x01206c10
int SphereVolume::CreateGPInstance(void* out, const Matrix44Affine* xf)
{
    const __m128 t = mTransform.r3;
    __m128 center;
    if (xf) {
        center = _mm_add_ps(
                    _mm_add_ps(_mm_add_ps(_mm_mul_ps(xf->r0, SplatX(t)),
                                          _mm_mul_ps(xf->r1, SplatY(t))),
                               _mm_mul_ps(xf->r2, SplatZ(t))),
                    _mm_mul_ps(xf->r3, Splat(1.0f)));
    } else {
        center = t;
    }
    char* o = (char*)out;
    *(__m128*)o = center;
    *(uint32_t*)(o + 0x88) = 0;
    *(uint32_t*)(o + 0x8c) = 0;
    *(void**)(o + 0x80) = this;
    *(uint32_t*)(o + 0x7c) = *(uint32_t*)&mRadius;
    *(void**)(o + 0x90) = (void*)&SphereVolumeInstance_GetBBox;
    *(void**)(o + 0x94) = (void*)&SphereVolumeInstance_GetInterval;
    *(void**)(o + 0x98) = (void*)&SphereVolumeInstance_GetIntervals;
    *(void**)(o + 0x9c) = (void*)&rwcRelocateNoOp;
    return 1;
}

// @ 0x01206cd0
int rwcSphereLineSegIntersect(CastFraction* t, const __m128* from, const __m128* dir,
                              const __m128* center, float radius)
{
    __m128 d = _mm_sub_ps(*center, *from);          // center - from
    __m128 dd4 = Dot3(d, d);
    __m128 r2 = _mm_mul_ss(_mm_load_ss(&radius), _mm_load_ss(&radius));
    float dd = Get(dd4, 0);
    float rr = Get(r2, 0);
    if (dd < rr) {                                  // already inside: t = 0/1
        t->num = 0.0f;
        t->den = 1.0f;
        return 1;
    }
    float a = Get(Dot3(d, *dir), 0);                // d . dir
    if (a <= 0.0f)
        return -1;
    float b = Get(Dot3(*dir, *dir), 0);             // dir . dir
    __m128 c = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(*dir, *dir, 0x09), _mm_shuffle_ps(d, d, 0x12)),
                          _mm_mul_ps(_mm_shuffle_ps(d, d, 0x09), _mm_shuffle_ps(*dir, *dir, 0x12)));
    float cc = Get(Dot3(c, c), 0);
    float disc = b * rr - cc;
    if (disc < 0.0f)
        return 0;
    float cc2 = a - b;
    if (cc2 > 0.0f && cc2 * cc2 > disc)
        return 0;
    t->den = b;
    t->num = a - (float)sqrt((double)disc);
    return 1;
}

// @ 0x01206e50
int SphereVolume::LineSegIntersect(const __m128* from, const __m128* to,
                                   const Matrix44Affine* xf, void* out)
{
    const __m128 t = mTransform.r3;
    __m128 center;
    if (xf) {
        center = _mm_add_ps(
                    _mm_add_ps(_mm_add_ps(_mm_mul_ps(xf->r0, SplatX(t)),
                                          _mm_mul_ps(xf->r1, SplatY(t))),
                               _mm_mul_ps(xf->r2, SplatZ(t))),
                    _mm_mul_ps(xf->r3, Splat(1.0f)));
    } else {
        center = t;
    }

    char* o = (char*)out;
    *(void**)o = this;                              // +0x00: volume
    const float radius = mRadius;
    __m128 dir = _mm_sub_ps(*to, *from);

    CastFraction hit;
    int n = rwcSphereLineSegIntersect(&hit, from, &dir, &center, radius);
    if (n <= 0)
        return 0;

    float step = Get(_mm_div_ss(_mm_load_ss(&hit.num), _mm_load_ss(&hit.den)), 0);
    *(float*)(o + 0x40) = step;                     // +0x40: fraction
    __m128 pos = _mm_add_ps(*from, _mm_mul_ps(dir, Splat(step)));
    *(__m128*)(o + 0x10) = pos;                     // +0x10: world position
    *(__m128*)(o + 0x20) = _mm_sub_ps(pos, center); // +0x20: normal (centre-relative)

    if (step > 0.0f) {
        // refine the normal by the reciprocal of the radius (2 Newton steps)
        __m128 inv = _mm_rcp_ps(Splat(radius));
        inv = _mm_mul_ps(_mm_sub_ps(Splat(2.0f), _mm_mul_ps(inv, Splat(radius))), inv);
        *(__m128*)(o + 0x20) = _mm_mul_ps(*(__m128*)(o + 0x20), inv);
        return 1;
    }

    __m128 nrm = *(__m128*)(o + 0x20);
    float len2 = Get(Dot3(nrm, nrm), 0);
    if (len2 > 1.1754943508222875e-38f) {
        nrm = Normalize3(nrm);
        *(__m128*)(o + 0x20) = nrm;
    }
    return 1;
}

// @ 0x012070a0
void* rwcVolumeRelocateReturnSecond(void* a, void* b)
{
    rwcRelocateReturnSecond(a, b);
    return b;
}

// @ 0x012070e0
int rwcVolumeInstanceInitialize(void* a, void* b)
{
    rwcRelocateReturnSecond((char*)a + 0x10, b);
    *(int*)a += *(int*)((char*)b + 0x20) - (int)a;
    return (int)b;
}

// @ 0x01207110
void rwcVolumeRelocateFixupNoOp(void* a, void* b)
{
    *(int*)a += (int)a - (int)b;
    rwcRelocateNoOp();
}

// @ 0x01207140
int rwcVolumeRelocateFixupReturnOne(void* a, void* b)
{
    *(int*)a += (int)a - *(int*)((char*)b + 0x7c);
    rwcRelocateReturnOne((char*)a + 0x10, b);
    return 1;
}

// =======================================================================================
// AggregateVolume::GetBBox (0x01207180) -- aggregate AABB, optionally transformed.

// 0x01204780 (helper) -- AABB::Transform, ecx = source AABB
AABB* AABB::Transform(AABB* out, const Matrix44Affine* xf)
{
    if (!xf) {
        out->mn = mn;
        out->mx = mx;
        return out;
    }
    const __m128 half = Splat(0.5f);
    __m128 center = _mm_mul_ps(_mm_add_ps(mx, mn), half);
    __m128 ext = _mm_mul_ps(_mm_sub_ps(mx, mn), half);
    __m128 tc = _mm_add_ps(_mm_add_ps(_mm_mul_ps(xf->r0, SplatX(center)),
                                      _mm_mul_ps(xf->r1, SplatY(center))),
                           _mm_add_ps(_mm_mul_ps(xf->r2, SplatZ(center)), xf->r3));
    __m128 te = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), xf->r0), xf->r0), SplatX(ext)),
                                      _mm_mul_ps(_mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), xf->r1), xf->r1), SplatY(ext))),
                           _mm_mul_ps(_mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), xf->r2), xf->r2), SplatZ(ext)));
    out->mn = _mm_sub_ps(tc, te);
    out->mx = _mm_add_ps(tc, te);
    return out;
}

// @ 0x01207180
int AggregateVolume::GetBBox(const Matrix44Affine* xf, const void* unused, AABB* out)
{
    (void)unused;
    const AABB* agg = (const AABB*)mAggregateData;
    AABB src;
    src.mn = agg->mn;
    src.mx = agg->mx;

    AABB dst;
    if (xf) {
        Matrix44Affine composed;
        composed.r0 = Compose(xf->r0, xf->r1, xf->r2, ((const Matrix44Affine*)this)->r0);
        composed.r1 = Compose(xf->r0, xf->r1, xf->r2, ((const Matrix44Affine*)this)->r1);
        composed.r2 = Compose(xf->r0, xf->r1, xf->r2, ((const Matrix44Affine*)this)->r2);
        composed.r3 = _mm_add_ps(Compose(xf->r0, xf->r1, xf->r2, ((const Matrix44Affine*)this)->r3),
                                 _mm_mul_ps(xf->r3, Splat(1.0f)));
        src.Transform(&dst, &composed);
    } else {
        src.Transform(&dst, (const Matrix44Affine*)this);
    }
    out->mn = dst.mn;
    out->mx = dst.mx;
    return 1;
}

// =======================================================================================
// BoxVolumeInstance interval helpers (0x01207310, 0x01207460)

// @ 0x01207310
// NOTE: void function.  Semantics are exact (see nonmatching/partial notes); the only
// difference from retail is the leftover, ABI-undefined EAX at return (retail happens to
// leave the |p[0x1e]| product bits there, our compiler leaves the argument address).
void BoxVolumeInstance_GetInterval(const __m128* pos, const __m128* dir, float* out)
{
    const float* p = (const float*)pos;
    const float* q = (const float*)dir;
    float d = Get(Dot3(*dir, *pos), 0);
    out[0] = d;
    out[1] = d;

    float e0 = p[0x1c] * (p[4] * q[0] + (p[5] * q[1] + p[6] * q[2]));
    float e1 = p[0x1d] * (p[8] * q[0] + (p[9] * q[1] + p[10] * q[2]));
    float e2 = p[0x1e] * (p[0xc] * q[0] + (p[0xd] * q[1] + p[0xe] * q[2]));
    float e = fabsf(e2) + fabsf(e1) + fabsf(e0);
    out[0] = d - e;
    out[1] = d + e;
}

// @ 0x01207460
void BoxVolumeInstance_GetIntervals(const __m128* pos, const __m128* pts, uint32_t count, float* out)
{
    const float* p = (const float*)pos;
    __m128 x0 = _mm_mul_ps(*(__m128*)(p + 4), Splat(p[0x1c]));
    __m128 x1 = _mm_mul_ps(*(__m128*)(p + 8), Splat(p[0x1d]));
    __m128 x2 = _mm_mul_ps(*(__m128*)(p + 0xc), Splat(p[0x1e]));
    while (count--) {
        float d = Get(Dot3(*pts, *pos), 0);
        out[0] = d;
        out[1] = d;
        float e2 = Get(Dot3(*pts, x2), 0);
        float e1 = Get(Dot3(*pts, x1), 0);
        float e0 = Get(Dot3(*pts, x0), 0);
        float e = fabsf(e2) + fabsf(e1) + fabsf(e0);
        out[0] = d - e;
        out[1] = d + e;
        out += 4;
        ++pts;
    }
}

// @ 0x012075f0
int SphereVolume::GetInterval(const void* a, const void* b)
{
    (void)a; (void)b;
    return 1;
}

// @ 0x01207600
int SphereVolume::GetMaximumFeature(const void* a, const void* b, void* out)
{
    (void)a; (void)b;
    *(uint32_t*)((char*)out + 0x130) = 0;
    _mm_store_ps((float*)((char*)out + 0x120), _mm_load_ps((const float*)&mTransform.r3));
    return 1;
}
