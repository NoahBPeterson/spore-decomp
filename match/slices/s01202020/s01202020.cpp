// Slice s01202020 -- 0x01202020 .. 0x01202af0 (7 functions).
//
// RenderWare 4 core (symbols/renderware4_core.txt): TriangleVolume.  The world-space normal,
// the three world-space vertices, the triangle's AABB and the axis-selection / plane-record
// builder that emits three 0x40-byte plane records into a grid volume and then re-derives their
// cross axes through the volume's ApplyAll (0x012018f0).
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE  (cl 13.10 -- the RenderWare 4 core was built with
// the VC .NET 2003 toolset, see symbols/renderware4_core.txt).  The leaf functions are byte-exact;
// 01202260 / 012023f0 make calls and are recorded as complete + equivalence-checked.

#include <xmmintrin.h>
typedef unsigned int uint32_t;

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
static __forceinline float Get0(__m128 v)
{
    Vec4Access a;
    a.v = v;
    return a.f[0];
}
static __forceinline __m128 Splat(float f) { return _mm_set_ps1(f); }
static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }

// four identical lanes built through the stack (the retail splats the triangle radius this way)
static __forceinline __m128 Splat4(float f)
{
    Vec4Access a;
    a.f[0] = f; a.f[1] = f; a.f[2] = f; a.f[3] = f;
    return a.v;
}

// ((x*x' + y*y') + z*z'), splatted into every lane
static __forceinline __m128 Dot3(__m128 a, __m128 b)
{
    __m128 m = _mm_mul_ps(a, b);
    return SplatX(_mm_add_ps(m, _mm_add_ps(_mm_shuffle_ps(m, m, 1), _mm_shuffle_ps(m, m, 2))));
}

// cross(a, b)
static __forceinline __m128 Cross(__m128 a, __m128 b)
{
    return _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(a, a, 9), _mm_shuffle_ps(b, b, 0x12)),
                      _mm_mul_ps(_mm_shuffle_ps(a, a, 0x12), _mm_shuffle_ps(b, b, 9)));
}

// two Newton-Raphson steps of rsqrt
static __forceinline __m128 Rsqrt2(__m128 x)
{
    const __m128 half = Splat(0.5f);
    const __m128 one = Splat(1.0f);
    __m128 r = _mm_rsqrt_ps(x);
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(x, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(x, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    return r;
}

// The retail lowers the float min/max used by the interval builders to a branchless sign-mask
// select (subss / sar 31 / not / and / or): the result is `a` when the sign bit of (a-b) is set,
// else `b`.  A C ternary lowers differently and on a +/-0 tie selects the wrong zero.
static __forceinline float SignMaskMin(float a, float b)
{
    float d = a - b;
    unsigned m = (unsigned)(*(int *)&d >> 31);
    unsigned ua = *(const unsigned *)&a;
    unsigned ub = *(const unsigned *)&b;
    unsigned r = (m & ua) | (~m & ub);
    return *(const float *)&r;
}
static __forceinline float SignMaskMax(float a, float b)
{
    float d = a - b;
    unsigned m = (unsigned)(*(int *)&d >> 31);
    unsigned ua = *(const unsigned *)&a;
    unsigned ub = *(const unsigned *)&b;
    unsigned r = (~m & ua) | (m & ub);
    return *(const float *)&r;
}
static __forceinline float AbsF(float x)
{
    unsigned u = *(const unsigned *)&x & 0x7fffffffu;
    return *(const float *)&u;
}

// affine point transform: ((m0*x + m1*y) + m2*z) + m3, splatting each component straight out of
// memory the way the retail does (movss [mem] ; shufps x,x,0)
static __forceinline __m128 TransformPoint(const __m128 *m, const float *p)
{
    return _mm_add_ps(_mm_add_ps(_mm_add_ps(
        _mm_mul_ps(m[0], _mm_set_ps1(p[0])),
        _mm_mul_ps(m[1], _mm_set_ps1(p[1]))),
        _mm_mul_ps(m[2], _mm_set_ps1(p[2]))), m[3]);
}

// the 3x3 (no translation) variant
static __forceinline __m128 RotatePoint3(const __m128 *m, const float *p)
{
    return _mm_add_ps(_mm_add_ps(_mm_mul_ps(m[0], _mm_set_ps1(p[0])),
                                 _mm_mul_ps(m[1], _mm_set_ps1(p[1]))),
                      _mm_mul_ps(m[2], _mm_set_ps1(p[2])));
}

struct AABB {
    __m128 mn;   // +0x00
    __m128 mx;   // +0x10
};

// The grid volume the plane records are written into; ApplyAll re-derives every element's third
// vector as cross(element+0x10, v).  Count at +0x130, elements at +0x10 + 0x40*i.
struct GridVolume {
    unsigned char m[0x140];
    void m012018f0(int flip, const __m128 *v);   // 0x012018f0
};

// The triangle volume.  +0x00/+0x10/+0x20 vertices, +0x30 normal, +0x40 type word, +0x44 word,
// +0x50 radius, +0x5c flags (bit 1 = normal dirty).
class TriangleVolume {
public:
    unsigned char m[0x60];
    void m01201980(int idx);                                                          // 0x01201980
    void GetWorldNormal(__m128 *normal, const void *xf) const;                        // 0x01202020
    void GetWorldVertices(__m128 *v0, __m128 *v1, __m128 *v2, const void *xf) const;  // 0x01202160
    int  GetAABB(const void *xf, int unused, AABB *out) const;                        // 0x012022b0
};

// ==========================================================================================
// 0x01202020 -- TriangleVolume::GetWorldNormal
// Recompute the (untransformed) face normal from the three vertices when the dirty bit is set,
// then hand the normal to the caller, optionally rotated by the 3x3 part of `xf`.

// @ 0x01202020
void TriangleVolume::GetWorldNormal(__m128 *normal, const void *xf) const
{
    char *base = (char *)m;
    if (*(unsigned char *)(base + 0x5c) & 2)
    {
        __m128 v0 = *(__m128 *)(base + 0x00);
        __m128 e1 = _mm_sub_ps(*(__m128 *)(base + 0x10), v0);
        __m128 e2 = _mm_sub_ps(*(__m128 *)(base + 0x20), v0);
        *(__m128 *)(base + 0x30) = Cross(e1, e2);
        float len2 = Get0(Dot3(*(__m128 *)(base + 0x30), *(__m128 *)(base + 0x30)));
        if (len2 > 1.1754944e-38f)
        {
            __m128 s = Rsqrt2(Splat(len2));
            *(__m128 *)(base + 0x30) = _mm_mul_ps(*(__m128 *)(base + 0x30), s);
        }
        *(unsigned int *)(base + 0x5c) &= ~2u;
    }
    *normal = *(__m128 *)(base + 0x30);
    if (xf)
        *normal = RotatePoint3((const __m128 *)xf, (const float *)normal);
}

// ==========================================================================================
// 0x01202160 -- TriangleVolume::GetWorldVertices
// The three vertices, transformed by the full 4x4 affine `xf` when one is given.

// @ 0x01202160
void TriangleVolume::GetWorldVertices(__m128 *v0, __m128 *v1, __m128 *v2, const void *xf) const
{
    char *base = (char *)m;
    if (xf)
    {
        const __m128 *mm = (const __m128 *)xf;
        *v0 = TransformPoint(mm, (const float *)(base + 0x00));
        *v1 = TransformPoint(mm, (const float *)(base + 0x10));
        *v2 = TransformPoint(mm, (const float *)(base + 0x20));
    }
    else
    {
        *v0 = *(__m128 *)(base + 0x00);
        *v1 = *(__m128 *)(base + 0x10);
        *v2 = *(__m128 *)(base + 0x20);
    }
}

// ==========================================================================================
// 0x01202260 -- create a triangle volume in place
// `*pp` must already point at storage: init it as a 3-vertex volume, store the three vertices,
// zero the radius, set the type word to 0xf and mark the normal dirty.

// @ 0x01202260
TriangleVolume *FUN_01202260(TriangleVolume **pp, const __m128 *a, const __m128 *b, const __m128 *c)
{
    TriangleVolume *t = *pp;
    if (t)
    {
        t->m01201980(3);
        *(float *)(t->m + 0x50) = 0.0f;
        *(int *)(t->m + 0x44) = 0xf;
        *(__m128 *)(t->m + 0x00) = *a;
        *(__m128 *)(t->m + 0x10) = *b;
        *(__m128 *)(t->m + 0x20) = *c;
        *(unsigned int *)(t->m + 0x5c) |= 2;
        return t;
    }
    return 0;
}

// ==========================================================================================
// 0x012022b0 -- TriangleVolume::GetAABB
// AABB of the (optionally transformed) triangle, inflated by the volume radius.  The middle
// argument is never read by the retail body.

// @ 0x012022b0
int TriangleVolume::GetAABB(const void *xf, int unused, AABB *out) const
{
    (void)unused;
    char *base = (char *)m;
    __m128 p0, p1, p2;
    if (xf)
    {
        const __m128 *mm = (const __m128 *)xf;
        p0 = TransformPoint(mm, (const float *)(base + 0x00));
        p1 = TransformPoint(mm, (const float *)(base + 0x10));
        p2 = TransformPoint(mm, (const float *)(base + 0x20));
    }
    else
    {
        p0 = *(__m128 *)(base + 0x00);
        p1 = *(__m128 *)(base + 0x10);
        p2 = *(__m128 *)(base + 0x20);
    }
    out->mn = _mm_min_ps(p0, _mm_min_ps(p1, p2));
    out->mx = _mm_max_ps(p0, _mm_max_ps(p1, p2));
    __m128 r = Splat4(*(const float *)(base + 0x50));
    out->mn = _mm_sub_ps(out->mn, r);
    out->mx = _mm_add_ps(out->mx, r);
    return 1;
}

// ==========================================================================================
// 0x01202960 -- interval of one point against a row set
// Project `p` onto the three rows at +0x00 / +0x20 / +0x30 of `m` and return [min, min(max, d2)].

// @ 0x01202960
void FUN_01202960(const float *m, const float *p, unsigned int *out)
{
    __m128 v = *(__m128 *)p;
    float d0 = Get0(Dot3(v, *(__m128 *)(m + 0)));
    float d1 = Get0(Dot3(v, *(__m128 *)(m + 8)));
    float d2 = Get0(Dot3(v, *(__m128 *)(m + 0xc)));
    float mn = SignMaskMin(d0, d1);
    float lo = SignMaskMin(mn, d2);
    out[0] = *(unsigned int *)&lo;
    float mx = SignMaskMax(d0, d1);
    float hi = SignMaskMax(mx, d2);
    out[1] = *(unsigned int *)&hi;
}

// ==========================================================================================
// 0x01202af0 -- the same interval, run over `count` points striding 0x10 bytes, writing two
// floats per point 0x10 bytes apart.

// @ 0x01202af0
void FUN_01202af0(const float *m, const float *p, unsigned int count, const float *out)
{
    if (count > 0)
    {
        int d = (int)out - (int)p;
        unsigned int n = count;
        do
        {
            __m128 v = *(__m128 *)p;
            float d0 = Get0(Dot3(v, *(__m128 *)(m + 0)));
            float d1 = Get0(Dot3(v, *(__m128 *)(m + 8)));
            float d2 = Get0(Dot3(v, *(__m128 *)(m + 0xc)));
            float mn = SignMaskMin(d0, d1);
            float lo = SignMaskMin(mn, d2);
            *(unsigned int *)(d + (int)p) = *(unsigned int *)&lo;
            float mx = SignMaskMax(d0, d1);
            float hi = SignMaskMax(mx, d2);
            *(unsigned int *)(d + (int)p + 4) = *(unsigned int *)&hi;
            p += 4;
        } while (--n);
    }
}

// ==========================================================================================
// 0x012023f0 -- build the three plane records for a triangle from a direction
// `param_1` is the 8x16-byte triangle record, `param_2` a sign selector, `param_3` the direction
// and `param_4` the grid volume.  Emits up to three 0x40-byte records, sets the volume's result
// word, header vector and count, then lets ApplyAll re-derive every record's cross vector.

// @ 0x012023f0
void FUN_012023f0(const float *param_1, unsigned int param_2, const float *param_3, GridVolume *param_4)
{
    char *out = (char *)param_4->m;
    __m128 n = *(__m128 *)param_3;
    __m128 zero = _mm_setzero_ps();
    float d = Get0(Dot3(n, *(__m128 *)(param_1 + 4)));
    if (AbsF(d) > 0.95f)
    {
        if ((d < 0.0f) == param_2)
        {
            *(__m128 *)(out + 0x10) = *(__m128 *)(param_1 + 0);
            *(__m128 *)(out + 0x20) = *(__m128 *)(param_1 + 0x10);
            *(__m128 *)(out + 0x30) = zero;
            *(float *)(out + 0x40) = param_1[0x1c];
            *(__m128 *)(out + 0x50) = *(__m128 *)(param_1 + 8);
            *(__m128 *)(out + 0x60) = *(__m128 *)(param_1 + 0x14);
            *(__m128 *)(out + 0x70) = zero;
            *(float *)(out + 0x80) = param_1[0x1d];
            *(__m128 *)(out + 0x90) = *(__m128 *)(param_1 + 0xc);
            *(__m128 *)(out + 0xa0) = *(__m128 *)(param_1 + 0x18);
            *(__m128 *)(out + 0xb0) = zero;
            *(float *)(out + 0xc0) = param_1[0x1e];
            *(int *)(out + 0x00) = 8;
        }
        else
        {
            *(__m128 *)(out + 0x10) = *(__m128 *)(param_1 + 0);
            *(__m128 *)(out + 0x20) = _mm_sub_ps(zero, *(__m128 *)(param_1 + 0x18));
            *(__m128 *)(out + 0x30) = zero;
            *(float *)(out + 0x40) = param_1[0x1e];
            *(__m128 *)(out + 0x50) = *(__m128 *)(param_1 + 0xc);
            *(__m128 *)(out + 0x60) = _mm_sub_ps(zero, *(__m128 *)(param_1 + 0x14));
            *(__m128 *)(out + 0x70) = zero;
            *(float *)(out + 0x80) = param_1[0x1d];
            *(__m128 *)(out + 0x90) = *(__m128 *)(param_1 + 8);
            *(__m128 *)(out + 0xa0) = _mm_sub_ps(zero, *(__m128 *)(param_1 + 0x10));
            *(__m128 *)(out + 0xb0) = zero;
            *(float *)(out + 0xc0) = param_1[0x1c];
            *(int *)(out + 0x00) = 0;
        }
        *(__m128 *)(out + 0x110) = *(__m128 *)(param_1 + 4);
        *(int *)(out + 0x130) = 3;
        param_4->m012018f0((int)param_2, (const __m128 *)param_3);
        return;
    }

    bool found = false;
    unsigned int idx = 0;
    for (unsigned int i = 0; i < 3; i++)
    {
        if (AbsF(Get0(Dot3(n, *(__m128 *)(param_1 + 0x10 + 4 * i)))) < 0.05f)
        {
            found = true;
            idx = i;
        }
    }
    if (found)
    {
        if (idx == 0)
        {
            if (Get0(Dot3(*(__m128 *)(param_1 + 0), n)) > Get0(Dot3(*(__m128 *)(param_1 + 0xc), n)))
            {
                *(__m128 *)(out + 0x10) = *(__m128 *)(param_1 + 0);
                *(__m128 *)(out + 0x20) = *(__m128 *)(param_1 + 0x10);
                *(__m128 *)(out + 0x30) = zero;
                *(float *)(out + 0x40) = param_1[0x1c];
                *(int *)(out + 0x130) = 1;
                *(int *)(out + 0x00) = 6;
                param_4->m012018f0((int)param_2, (const __m128 *)param_3);
                return;
            }
            *(int *)(out + 0x130) = 0;
            *(__m128 *)(out + 0x120) = *(__m128 *)(param_1 + 0xc);
            *(int *)(out + 0x00) = 3;
            param_4->m012018f0((int)param_2, (const __m128 *)param_3);
            return;
        }
        if (idx == 1)
        {
            if (Get0(Dot3(*(__m128 *)(param_1 + 8), n)) > Get0(Dot3(*(__m128 *)(param_1 + 0), n)))
            {
                *(__m128 *)(out + 0x10) = *(__m128 *)(param_1 + 8);
                *(__m128 *)(out + 0x20) = *(__m128 *)(param_1 + 0x14);
                *(__m128 *)(out + 0x30) = zero;
                *(float *)(out + 0x40) = param_1[0x1d];
                *(int *)(out + 0x130) = 1;
                *(int *)(out + 0x00) = 4;
                param_4->m012018f0((int)param_2, (const __m128 *)param_3);
                return;
            }
            *(int *)(out + 0x130) = 0;
            *(__m128 *)(out + 0x120) = *(__m128 *)(param_1 + 0);
            *(int *)(out + 0x00) = 1;
            param_4->m012018f0((int)param_2, (const __m128 *)param_3);
            return;
        }
        if (Get0(Dot3(*(__m128 *)(param_1 + 0xc), n)) > Get0(Dot3(*(__m128 *)(param_1 + 8), n)))
        {
            *(__m128 *)(out + 0x10) = *(__m128 *)(param_1 + 0xc);
            *(__m128 *)(out + 0x20) = *(__m128 *)(param_1 + 0x18);
            *(__m128 *)(out + 0x30) = zero;
            *(float *)(out + 0x40) = param_1[0x1e];
            *(int *)(out + 0x130) = 1;
            *(int *)(out + 0x00) = 2;
            param_4->m012018f0((int)param_2, (const __m128 *)param_3);
            return;
        }
        *(int *)(out + 0x130) = 0;
        *(__m128 *)(out + 0x120) = *(__m128 *)(param_1 + 8);
        *(int *)(out + 0x00) = 5;
        param_4->m012018f0((int)param_2, (const __m128 *)param_3);
        return;
    }

    *(int *)(out + 0x130) = 0;
    *(__m128 *)(out + 0x120) = *(__m128 *)(param_1 + 0);
    *(int *)(out + 0x00) = 1;
    float best = Get0(Dot3(*(__m128 *)(param_1 + 0), n));
    float d2 = Get0(Dot3(*(__m128 *)(param_1 + 8), n));
    if (best < d2)
    {
        *(__m128 *)(out + 0x120) = *(__m128 *)(param_1 + 8);
        *(int *)(out + 0x00) = 5;
        best = d2;
    }
    if (best < Get0(Dot3(*(__m128 *)(param_1 + 0xc), n)))
    {
        *(__m128 *)(out + 0x120) = *(__m128 *)(param_1 + 0xc);
        *(int *)(out + 0x00) = 3;
    }
    param_4->m012018f0((int)param_2, (const __m128 *)param_3);
}
