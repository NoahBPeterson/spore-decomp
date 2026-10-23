// Slice s01201080 -- 0x01201080..0x01201c70.
//
// Spore/Havok-style SSE vector & segment math (the same family as the neighbouring
// slices s01207630 / s01200010: dot3 built from two shuffles, cross from the yzx/zxy
// shuffles, rsqrt/rcp + Newton-Raphson refinement, 4-wide float vectors).
//
//   * 01201080  pointer-rebase helper: *p += (char*)p - *(char**)(obj + 0x7c)
//   * 012010e0  large per-frame box/skinning matrix builder (see partial.txt)
//   * 012015f0  Segment/volume sizing: lays out the sub-buffer pointers from the
//               three grid dimensions (a, b, c) into one contiguous block
//   * 01201660  same block layout for a smaller/other element set, plus header init
//   * 012016d0  thin forwarder into 012015f0 (returns 0 when the flag word is clear)
//   * 012016f0  SP::Segment::Segment(a,b): pos = a, dir = normalize(b-a), length
//   * 01201810  this->v20 = normalize(cross(this->v10, b))
//   * 012018f0  run 01201810 over every element of the array at this+0x10
//               (with the direction negated when the flip flag is zero)
//   * 01201980  identity-frame + volume-class init (table 0x0171e598)
//   * 01201a20  ray/segment-triangle intersection (see partial.txt)
//   * 01201c70  closest-point-on-triangle (register-argument ABI, see partial.txt)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast  (as the neighbouring volume-cast slices).
//
// Toolchain: 012016d0 reproduces byte-exactly under the VC9 (/O2) flags above.  01201080
// does NOT: VC9 always fuses `*p = *p + (p-obj->off)` into a read-modify-write
// (`sub ecx,[edx+7c]; add [eax],ecx`), while the retail body keeps `off` in a callee-saved
// register (`push esi`) and loads/stores `*p` separately - the VC7.1 shape (verified: VC7.1
// /O2 produces it byte-exactly, VC9 /O2 /Os /O1 /Ob0 all do not).  Its manifest row therefore
// carries a /vc71 override; see the papercut note.  The SSE-heavy functions in this slice
// (012015f0 01201660 012016f0 01201810 012018f0 01201980) are complete and behaviourally
// correct but their xmm/integer allocation is not reproducible under /O2 + /c.
#include <xmmintrin.h>

typedef unsigned int uint32_t;

// ---- shared SSE helpers (Havok hkVector4 idiom) -------------------------------

static __forceinline __m128 Splat(float f) { return _mm_set_ps1(f); }
static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }

union Vec4Access {
    __m128 v;
    float f[4];
    uint32_t u[4];
};
static __forceinline float Get0(__m128 v)
{
    Vec4Access a;
    a.v = v;
    return a.f[0];
}

// ((x*x' + y*y') + z*z'), splatted into every lane
static __forceinline __m128 Dot3(__m128 a, __m128 b)
{
    __m128 m = _mm_mul_ps(a, b);
    return SplatX(_mm_add_ps(m, _mm_add_ps(_mm_shuffle_ps(m, m, 2), _mm_shuffle_ps(m, m, 1))));
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
    __m128 half = Splat(0.5f);
    __m128 one = Splat(1.0f);
    __m128 r = _mm_rsqrt_ps(x);
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(x, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(x, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    return r;
}

// two Newton-Raphson steps of rcp
static __forceinline __m128 Rcp2(__m128 x)
{
    __m128 two = Splat(2.0f);
    __m128 r = _mm_rcp_ps(x);
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), r);
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), r);
    return r;
}

// ---- 0x01201080 ---------------------------------------------------------------
// @ 0x01201080
int __cdecl FUN_01201080(int *p, int obj)
{
    int off = *(int *)(obj + 0x7c);
    int v = *p;
    *p = v + ((int)p - off);
    return 1;
}

// ---- 0x012010e0 (placeholder; see partial.txt) --------------------------------
// @ 0x012010e0
int __cdecl FUN_012010e0(int *a, int *b, int c, int *d)
{
    (void)a; (void)b; (void)c; (void)d;
    return 1;
}

// ---- the grid volume this whole range operates on -----------------------------
// 16-byte aligned frame at +0x00 (four rows), the volume type word at +0x40, the
// grid dimensions at +0xd4.., the element array (0x40 bytes each) at +0x10 and its
// element count at +0x130.
struct SegVolume {
    unsigned char m[0x140];
    SegVolume *Setup(int a, int b, int c);
    void SetCross(const __m128 *b);
    void ApplyAll(int flip, const __m128 *v);
    SegVolume *Init(int idx);      // retail leaves `this` in eax on return (see equiv note)
};

// ---- 0x012015f0 ---------------------------------------------------------------
// @ 0x012015f0
SegVolume *SegVolume::Setup(int a, int b, int c)
{
    char *base = (char *)m;
    char *p = base + 0x110;
    *(int *)(base + 0xd4) = a;
    *(int *)(base + 0xe0) = b;
    char *q = (char *)(a * 0x80) + (int)p;
    *(int *)(base + 0xd8) = (int)q;
    q += b * 0x80;
    *(int *)(base + 0x1c) = c;
    *(int *)(base + 0xec) = c;
    *(int *)(base + 0xe4) = (int)q;
    q += c * 0x60;
    *(int *)(base + 0x40) = (int)p;
    *(int *)(base + 0x10) = (int)q;
    *(int *)(base + 0xf4) = c * 0xd0 + (int)q;
    return this;
}

// ---- 0x01201660 ---------------------------------------------------------------
// @ 0x01201660
void __cdecl FUN_01201660(int *p, int b, int c)
{
    char *addr = (char *)(c * 0x1b0 + b * 0x80 + 0x110);
    p[1] = 1;                       // +0x04
    p[3] = 1;                       // +0x0c
    p[0] = 0;                       // +0x00
    p[2] = 0;                       // +0x08
    p[5] = 1;                       // +0x14
    p[4] = 0;                       // +0x10
    p[7] = 1;                       // +0x1c
    p[6] = 0;                       // +0x18
    *(int *)p = (int)(addr + 0x2880);
    p[1] = 0x10;
}

// ---- 0x012016d0 ---------------------------------------------------------------
// @ 0x012016d0
int __cdecl FUN_012016d0(int *flag, int a, int b)
{
    if (*flag != 0)
        return (int)((SegVolume *)*flag)->Setup(a, b, b);
    return 0;
}

// ---- 0x012016f0  SP::Segment::Segment(a, b) -----------------------------------
struct SPSegment {
    __m128 pos;         // +0x00
    __m128 dir;         // +0x10
    __m128 v20;         // +0x20
    float length;       // +0x30
    int pad[3];
    SPSegment(const __m128 &a, const __m128 &b);
};

// @ 0x012016f0
SPSegment::SPSegment(const __m128 &a, const __m128 &b)
{
    pos = a;
    __m128 d = _mm_sub_ps(b, a);
    __m128 len2 = Dot3(d, d);
    float l2 = Get0(len2);
    if (l2 > 1.1920929e-07f)
    {
        __m128 len = _mm_mul_ps(Splat(l2), Rsqrt2(Splat(l2)));
        len = _mm_andnot_ps(_mm_cmpeq_ps(Splat(l2), _mm_setzero_ps()), len);
        float L = Get0(len);
        length = L;
        dir = _mm_mul_ps(d, Rcp2(Splat(L)));
    }
}

// ---- 0x01201810 ---------------------------------------------------------------
// @ 0x01201810
void SegVolume::SetCross(const __m128 *b)
{
    char *base = (char *)m;
    __m128 c = Cross(*(const __m128 *)(base + 0x10), *b);
    *(__m128 *)(base + 0x20) = c;
    __m128 len2 = Dot3(*(const __m128 *)(base + 0x20), *(__m128 *)(base + 0x20));
    if (Get0(len2) > 1.1920929e-07f)
        *(__m128 *)(base + 0x20) = _mm_mul_ps(*(__m128 *)(base + 0x20), Rsqrt2(Splat(Get0(len2))));
}

// ---- 0x012018f0 ---------------------------------------------------------------
// The original negates the direction per element by subtracting it from a zero vector it keeps
// in a stack slot ([esp+0x10]): it never puts that zero in a register, and it never writes xmm7
// (an LTCG caller may keep a live value there - the equivalence run flags an extra xmm7 clobber).
// A plain `_mm_setzero_ps()` local lets cl hoist the zero into xmm7 across the SetCross call, so
// the zero is spelled as the bitwise identity `_mm_andnot_ps(x, x)`: `~x & x` is +0.0f in every
// lane for every input (bitwise, so even NaN/Inf lanes give +0.0f), it is recomputed from the
// reloaded *v each iteration, and it needs only xmm0/xmm1 - the two registers the original's
// branch writes.  Cost: one extra `movaps xmm1, xmm0; andnps xmm1, xmm0` per element instead of
// the original's `movaps xmm1, [esp+0x10]`.
// @ 0x012018f0
void SegVolume::ApplyAll(int flip, const __m128 *v)
{
    if (flip != 0)
    {
        for (int i = 0; i < *(int *)(m + 0x130); i++)
            ((SegVolume *)(m + 0x10 + 0x40 * i))->SetCross(v);
    }
    else
    {
        __m128 nv;
        for (int i = 0; i < *(int *)(m + 0x130); i++)
        {
            __m128 bits = *v;
            __m128 zero = _mm_andnot_ps(bits, bits);
            nv = _mm_sub_ps(zero, *v);
            ((SegVolume *)(m + 0x10 + 0x40 * i))->SetCross(&nv);
        }
    }
}

// ---- 0x01201980 ---------------------------------------------------------------
// Identity frame + volume-class init.  The retail body keeps `this` in eax throughout and
// returns it (equiv run: the only observable mismatch of a void form was the return eax).
// @ 0x01201980
SegVolume *SegVolume::Init(int idx)
{
    char *base = (char *)m;
    union { float f[4]; __m128 v; } u;
    int t = ((int *)0x171e598)[idx];
    u.f[0] = 1.0f; u.f[1] = 0.0f; u.f[2] = 0.0f; u.f[3] = 0.0f;
    __m128 r0 = u.v;
    u.f[1] = 1.0f; u.f[0] = 0.0f; u.f[2] = 0.0f; u.f[3] = 0.0f;
    __m128 r1 = u.v;
    u.f[2] = 1.0f; u.f[0] = 0.0f; u.f[1] = 0.0f; u.f[3] = 0.0f;
    __m128 r2 = u.v;
    *(float *)(base + 0x50) = 0.0f;
    *(int *)(base + 0x40) = t;
    *(int *)(base + 0x54) = 0;
    *(int *)(base + 0x58) = 0;
    *(int *)(base + 0x5c) = 1;
    *(__m128 *)(base + 0x00) = r0;
    *(__m128 *)(base + 0x10) = r1;
    *(__m128 *)(base + 0x20) = r2;
    *(__m128 *)(base + 0x30) = _mm_setzero_ps();
    return this;
}

// ---- 0x01201a20 (placeholder; see partial.txt) --------------------------------
// @ 0x01201a20
int __cdecl FUN_01201a20(int a, float *b, float *c, float *d, float *e, float *f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return 0;
}

// ---- 0x01201c70 (placeholder; see partial.txt) --------------------------------
// @ 0x01201c70
int __cdecl FUN_01201c70(float *a, float *b, float *c, float *d, float *e, float *f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return 0;
}
