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

// ---- 0x012010e0 ---------------------------------------------------------------
// Per-frame transform builder.  For every frame i < count (ctl+0x14) it builds the
// local 4x4 R from the frame's quaternion + translation, composes M = R * state,
// emits the upper three rows (12 floats) and then updates the state:
//   mode 0: state = M      mode 1: pop state      mode 2: push state, state = M
//   mode 3: state unchanged
// The frame comes from Ctl::FrameAt (011fda50); the per-frame input matrix is the
// 0x40-byte block at *a + i*0x40, *b is the per-frame mode-word array, and *d is
// the 12-floats-per-frame output cursor.  The state stack is the retail 1007-float
// frame buffer.
// @ 0x012010e0
int __cdecl FUN_012010e0(int **a, int **b, void *ctl, int **out)
{
    // Ctl::FrameAt is __thiscall (this in ecx, ret 4).  VC7.1 reserves __thiscall in a
    // function-pointer typedef (C4234, an error in this configuration); that compiler is
    // only used for the /vc71 01201080 row, which never reaches this body, so a plain
    // pointer typedef keeps the TU buildable there.
#if _MSC_VER >= 1400
    typedef float *(__thiscall *FrameAtFn)(void *, int);
#else
    typedef float *(__cdecl *FrameAtFn)(void *, int);
#endif
    const float kSqrt2 = 1.4142135381698608f;
    // The retail body keeps the 4x4 state (rows at +0x30..+0x60), the 0.5/zero/sqrt2
    // constant vectors (+0x90/+0x120/+0x130) and the push stack (base +0x220, growing up)
    // in one 0x11d4-byte frame.  Mode 1 pops *below* the stack base, so an unbalanced mode
    // stream reads whatever that frame holds: the 0xCC stack fill for the first levels,
    // then the per-iteration Vw/v2 temporaries at +0x190/+0x1c0.  Model the frame
    // byte-for-byte (extra 0xCC guard past the top) so those retail reads reproduce.
    unsigned char frame[0x3200];
    // Fill with the harness/original stack poison (0xCC bytes).  A plain memset would
    // become a CRT import call the original never makes, so splat it with SSE stores.
    {
        union { uint32_t u; float f; } cc;
        cc.u = 0xCCCCCCCCu;
        __m128 fill = _mm_set1_ps(cc.f);
        for (int k = 0; k < (int)sizeof(frame); k += 16)
            _mm_storeu_ps((float *)(frame + k), fill);
    }
    float *S = (float *)(frame + 0x30);
    _mm_storeu_ps((float *)(frame + 0x90), _mm_set1_ps(0.5f));
    _mm_storeu_ps((float *)(frame + 0x120), _mm_setzero_ps());
    _mm_storeu_ps((float *)(frame + 0x130), _mm_set1_ps(kSqrt2));
    float *sp = (float *)(frame + 0x220);
    for (int k = 0; k < 16; ++k)
        S[k] = (k == 0 || k == 5 || k == 10) ? 1.0f : 0.0f;
    float *dst = (float *)*out;
    unsigned count = *(unsigned *)((char *)ctl + 0x14);

    for (unsigned i = 0; i < count; ++i)
    {
        const float *f = ((FrameAtFn)0x11fda50)(ctl, (int)i);
        // The retail body computes (0 - q*)*q* + 0.5 with a real `subps 0, q`; under /fp:fast
        // cl rewrites the scalar `0.0f - qx` into a sign-bit negate, which flips the sign of an
        // input NaN (the frame stride is caller-controlled and may be misaligned, so q can be
        // any bit pattern).  Subtract from a volatile zero so a real subtraction is emitted and
        // the NaN result keeps the operand's sign, exactly like the original.
        volatile float vzero = 0.0f;
        float qx = f[0] * kSqrt2;
        float qy = f[1] * kSqrt2;
        float qz = f[2] * kSqrt2;
        float qw = f[3] * kSqrt2;
        float tx = f[4], ty = f[5], tz = f[6];
        float xx = (vzero - qx) * qx + 0.5f;
        float yy = (vzero - qy) * qy + 0.5f;
        float zz = (vzero - qz) * qz + 0.5f;
        float xyp = qx * qy + qw * qz;
        float yzp = qy * qz + qw * qx;
        float zxp = qz * qx + qw * qy;
        float xym = qx * qy - qw * qz;
        float yzm = qy * qz - qw * qx;
        float zxm = qz * qx - qw * qy;
        float d0 = xx + yy;
        float d1 = yy + zz;
        float d2 = zz + xx;

        float M[16];
        for (int j = 0; j < 4; ++j)
        {
            float s0 = S[j], s1 = S[4 + j], s2 = S[8 + j], s3 = S[12 + j];
            M[0 + j]  = s2 * zxm + (s1 * xyp + s0 * d1);
            M[4 + j]  = s2 * yzp + (s1 * d2  + s0 * xym);
            M[8 + j]  = s2 * d0  + (s1 * yzm + s0 * zxp);
            M[12 + j] = s3 + (s2 * tz + (s1 * ty + s0 * tx));
        }

        const float *P = (const float *)((const char *)*a + i * 0x40);
        float p0 = P[0], p1 = P[1], p2 = P[2];
        float p4 = P[4], p5 = P[5], p6 = P[6];
        float p8 = P[8], p9 = P[9], p10 = P[10];
        float p12 = P[12], p13 = P[13], p14 = P[14];
        for (int j = 0; j < 3; ++j)
        {
            float m0 = M[0 + j], m1 = M[4 + j], m2 = M[8 + j], m3 = M[12 + j];
            dst[4 * j + 0] = m2 * p2 + (m1 * p1 + m0 * p0);
            dst[4 * j + 1] = m2 * p6 + (m1 * p5 + m0 * p4);
            dst[4 * j + 2] = m2 * p10 + (m1 * p9 + m0 * p8);
            dst[4 * j + 3] = m3 + (m2 * p14 + (m1 * p13 + m0 * p12));
        }

        // Retail caches the four packed column products v0..v3 and Vw in the frame; a
        // pop below the stack base can land on any of those slots.
        float v0[4], v1[4], v2[4], v3[4];
        for (int j = 0; j < 4; ++j)
        {
            float m0 = M[0 + j], m1 = M[4 + j], m2 = M[8 + j], m3 = M[12 + j];
            v0[j] = m2 * p2 + (m1 * p1 + m0 * p0);
            v1[j] = m2 * p6 + (m1 * p5 + m0 * p4);
            v2[j] = m2 * p10 + (m1 * p9 + m0 * p8);
            v3[j] = m3 + (m2 * p14 + (m1 * p13 + m0 * p12));
        }
        _mm_storeu_ps((float *)(frame + 0x190), _mm_loadu_ps(&M[12]));
        _mm_storeu_ps((float *)(frame + 0x1c0), _mm_loadu_ps(v2));
        _mm_storeu_ps((float *)(frame + 0x140), _mm_loadu_ps(v0));
        _mm_storeu_ps((float *)(frame + 0x110), _mm_loadu_ps(v0));
        _mm_storeu_ps((float *)(frame + 0x0b0), _mm_loadu_ps(v0));
        _mm_storeu_ps((float *)(frame + 0x150), _mm_loadu_ps(v2));
        _mm_storeu_ps((float *)(frame + 0x080), _mm_loadu_ps(v2));
        _mm_storeu_ps((float *)(frame + 0x0a0), _mm_loadu_ps(v2));
        _mm_storeu_ps((float *)(frame + 0x0d0), _mm_loadu_ps(v1));
        _mm_storeu_ps((float *)(frame + 0x0f0), _mm_loadu_ps(v1));
        _mm_storeu_ps((float *)(frame + 0x070), _mm_loadu_ps(v1));
        _mm_storeu_ps((float *)(frame + 0x0c0), _mm_loadu_ps(v3));
        _mm_storeu_ps((float *)(frame + 0x0e0), _mm_loadu_ps(v3));
        _mm_storeu_ps((float *)(frame + 0x100), _mm_loadu_ps(v3));

        unsigned mode = (*(const unsigned **)b)[i] & 3u;
        if (mode == 1)
        {
            sp -= 16;
            __m128 t0 = _mm_loadu_ps(sp);
            __m128 t1 = _mm_loadu_ps(sp + 4);
            __m128 t2 = _mm_loadu_ps(sp + 8);
            __m128 t3 = _mm_loadu_ps(sp + 12);
            _mm_storeu_ps(S, t0);
            _mm_storeu_ps(S + 4, t1);
            _mm_storeu_ps(S + 8, t2);
            _mm_storeu_ps(S + 12, t3);
        }
        else
        {
            if (mode == 2)
            {
                __m128 t0 = _mm_loadu_ps(S);
                __m128 t1 = _mm_loadu_ps(S + 4);
                __m128 t2 = _mm_loadu_ps(S + 8);
                __m128 t3 = _mm_loadu_ps(S + 12);
                _mm_storeu_ps(sp, t0);
                _mm_storeu_ps(sp + 4, t1);
                _mm_storeu_ps(sp + 8, t2);
                _mm_storeu_ps(sp + 12, t3);
                sp += 16;
            }
            if (mode != 3)
            {
                __m128 t0 = _mm_loadu_ps(M);
                __m128 t1 = _mm_loadu_ps(M + 4);
                __m128 t2 = _mm_loadu_ps(M + 8);
                __m128 t3 = _mm_loadu_ps(M + 12);
                _mm_storeu_ps(S, t0);
                _mm_storeu_ps(S + 4, t1);
                _mm_storeu_ps(S + 8, t2);
                _mm_storeu_ps(S + 12, t3);
            }
        }
        dst += 12;
    }
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

// ---- 0x01201a20 ---------------------------------------------------------------
// Ray/segment vs triangle (P + s*D against triangle V0,A,B).
//   c1  = cross(D, B - V0),  det = (A - V0).c1
//   t1  = (P - V0).c1       t2 = D.cross(P - V0, A - V0)     t3 = (B - V0).cross(P - V0, A - V0)
// The det/t1/t2 range tests run on the unnormalised barycentrics; the surviving hits are
// divided by det.  Note out+0x40 receives the raw t3 *before* its range test (so a failed
// t3 test still leaves the raw value in the record).  ^0x30 = {t1,t2,0,t1}/det,
// ^0x10 = P + D*(t3/det), ^0x40 = t3/det.
// @ 0x01201a20
int __cdecl FUN_01201a20(void *out, float *P, float *D, float *V0, float *A, float *B)
{
    char *o = (char *)out;
    __m128 v0 = _mm_loadu_ps(V0);
    __m128 dv = _mm_loadu_ps(D);
    __m128 bv = _mm_sub_ps(_mm_loadu_ps(B), v0);        // xmm3 = B - V0
    __m128 c1 = Cross(dv, bv);                          // xmm1
    __m128 av = _mm_sub_ps(_mm_loadu_ps(A), v0);        // xmm4 = A - V0
    float det = Get0(Dot3(av, c1));
    if (!(det > 9.99999993922529e-09f))
        return 0;

    float lo = det * -9.999999747378752e-06f;
    float hi = det - lo;

    __m128 rv = _mm_sub_ps(_mm_loadu_ps(P), v0);        // xmm2 = P - V0
    float t1 = Get0(Dot3(rv, c1));
    if (!(t1 >= lo) || !(hi >= t1))
        return 0;

    __m128 c2 = Cross(rv, av);                          // xmm1 = cross(P-V0, A-V0)
    float t2 = Get0(Dot3(dv, c2));
    if (!(t2 >= lo) || !(hi >= t2 + t1))
        return 0;

    float t3 = Get0(Dot3(bv, c2));                      // (B-V0).c2
    *(float *)(o + 0x40) = t3;                          // stored before the t3 test
    if (!(t3 >= lo) || !(hi >= t3))
        return 0;

    float r = Get0(Rcp2(_mm_set1_ps(det)));
    float q = r * t3;
    *(float *)(o + 0x40) = q;
    _mm_storeu_ps((float *)(o + 0x10),
                  _mm_add_ps(_mm_loadu_ps(P), _mm_mul_ps(dv, _mm_set1_ps(q))));

    float a1 = r * t1;
    float a2 = r * t2;
    float quad[4];
    quad[0] = a1;
    quad[1] = a2;
    quad[2] = 0.0f;
    quad[3] = a1;
    _mm_storeu_ps((float *)(o + 0x30), _mm_loadu_ps(quad));
    return 1;
}

// ---- 0x01201c70 ---------------------------------------------------------------
// Closest point on triangle (V0, V1, V2) to point P; returns the Voronoi-region code
// (0..6) and writes the barycentric weights to *outS / *outT and V0 + s*(V1-V0) + t*(V2-V0)
// to outVec[0..3].
//
// ABI note: retail passes V0/V1/V2 in ecx/eax/edx (custom LTCG register convention);
// an eax argument cannot be expressed in C++, so this portable form takes all seven
// pointers as ordinary arguments in that same logical order.  The arithmetic and the
// region/Voronoi decision tree below are a literal translation of the retail body.
// @ 0x01201c70
int __cdecl FUN_01201c70(float *v0, float *v1, float *v2,
                         float *outVec, float *outS, float *outT, float *P)
{
    float v00 = v0[0], v01 = v0[1], v02 = v0[2], v03 = v0[3];
    float v10 = v1[0], v11 = v1[1], v12 = v1[2], v13 = v1[3];
    float v20 = v2[0], v21 = v2[1], v22 = v2[2], v23 = v2[3];

    float d1x = v10 - v00, d1y = v11 - v01, d1z = v12 - v02;
    float d2x = v20 - v00, d2y = v21 - v01, d2z = v22 - v02;
    float px = v00 - P[0], py = v01 - P[1], pz = v02 - P[2];

    float a = d1x * d1x + (d1y * d1y + d1z * d1z);
    float b = d1x * d2x + (d1y * d2y + d1z * d2z);
    float c = d2x * d2x + (d2y * d2y + d2z * d2z);
    float d = d1x * px + (d1y * py + d1z * pz);
    float e = d2x * px + (d2y * py + d2z * pz);

    float det = c * a - b * b;
    float sdet = e * b - d * c;
    float tdet = d * b - e * a;

    float s = 0.0f, t = 0.0f;
    unsigned code;

    if (det >= 0.37547844648361206f)
    {
        if (tdet + sdet <= det)
        {
            if (0.0f <= sdet)
            {
                if (0.0f <= tdet)
                {
                    code = 3;
                    goto region_done;
                }
                if (0.0f < 0.0f - d)
                {
                    code = 0;
                    goto region_done;
                }
            }
            else if (0.0f - e <= 0.0f)
            {
                code = 0;
                goto region_done;
            }
            code = 1;
        }
        else
        {
            if (0.0f <= sdet)
            {
                if (tdet < 0.0f)
                {
                    if (e + b <= d + a)
                    {
                        code = 2;
                        goto region_done;
                    }
                    code = 0;
                    goto region_done;
                }
            }
            else
            {
                if (e + c < d + b)
                {
                    code = 1;
                    goto region_done;
                }
            }
            code = 2;
        }
    }
    else
    {
        float v = (a - b * 2.0f) + c;
        if (a <= c)
        {
            if (c <= v)
            {
                code = 2;
                goto region_done;
            }
            code = 1;
        }
        else
        {
            if (a <= v)
            {
                code = 2;
                goto region_done;
            }
            code = 0;
        }
    }

region_done:
    if (code == 0)
    {
        if (d < 0.0f)
        {
            if (a <= 0.0f - d)
            {
                s = 1.0f;
                code = 1;
            }
            else
            {
                s = 0.0f - d / a;
                code = 3;
            }
        }
        else
        {
            code = 0;
        }
        t = 0.0f;
    }
    else if (code == 1)
    {
        if (0.0f <= e)
        {
            code = 0;
            t = 0.0f;
        }
        else if (0.0f - e < c)
        {
            t = 0.0f - e / c;
            code = 4;
        }
        else
        {
            t = 1.0f;
            code = 2;
        }
    }
    else if (code == 2)
    {
        float x = ((e + c) - b) - d;
        if (0.0f < x)
        {
            float v = (a - b * 2.0f) + c;
            if (x < v)
            {
                s = x / v;
                t = 1.0f - s;
                code = 5;
            }
            else
            {
                s = 1.0f;
                t = 0.0f;
                code = 1;
            }
        }
        else
        {
            t = 1.0f;
            code = 2;
        }
    }
    else
    {
        float r = Get0(Rcp2(_mm_set1_ps(det)));
        s = r * sdet;
        t = r * tdet;
        code = 6;
    }

    *outS = s;
    *outT = t;
    outVec[0] = (v0[0] + d1x * s) + d2x * t;
    outVec[1] = (v0[1] + d1y * s) + d2y * t;
    outVec[2] = (v0[2] + d1z * s) + d2z * t;
    outVec[3] = (v03 + (v13 - v03) * s) + (v23 - v03) * t;
    return (int)code;
}
