// Slice s011ff090 -- RenderWare 4 core, VC .NET 2003 (cl 13.10) /GL+/LTCG.
// 0x011ff090-0x0120000b: keyframe-array interpolation / quaternion-slerp kernels of the
// rw animation format-blend code, plus the small registration / format-stride helpers.
//
// POLICY (symbols/renderware4_core.txt): RenderWare 4 core is equivalence-only -- the
// functions that make calls cannot reproduce the original single-object bytes, because the
// original was built with /GL+/LTCG and its register allocation spans call boundaries.  The
// leaf functions (no calls) below are written to the original shape and may be byte-exact
// under /vc71; the callers are complete, behaviourally equivalent reconstructions.  See
// nonmatching.txt.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <intrin.h>
#include <xmmintrin.h>
#include <math.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t  i32;

// The original keeps its constant/leaf arithmetic in SSE lanes (single precision), and only the
// transcendentals touch the x87 stack.  MSVC keeps x87 temporaries extended, so route every value
// the original rounds to a float through a 32-bit volatile slot; without this the slerp arguments
// stay 80-bit and drift a few ulp.
static __forceinline float fsingle(float x)
{
    volatile float v = x;
    return v;
}

// The original evaluates every sine/cosine with the x87 hardware instructions -- fld/fcos/fsin/fstp --
// rather than the CRT's software sinf/cosf, whose polynomial is not bit-identical to the FPU's.  The
// argument and result are the single-precision values, exactly as the original loads (fld dword) and
// stores (fstp dword) them.
static __forceinline float fsin32(float x)
{
    volatile float v = x;
    float r;
    __asm {
        fld  dword ptr [v]
        fsin
        fstp dword ptr [r]
    }
    return r;
}

static __forceinline float fcos32(float x)
{
    volatile float v = x;
    float r;
    __asm {
        fld  dword ptr [v]
        fcos
        fstp dword ptr [r]
    }
    return r;
}

// A single-precision divide that the optimiser is not allowed to rewrite as x * (1/y): the
// original emits a real SSE `divss`/`divps` for the slerp sine terms, and the reciprocal form
// rounds one ulp differently.  Going through the intrinsic pins the instruction.
static __forceinline float divss(float x, float y)
{
    union { __m128 v; float f[4]; } u;
    u.v = _mm_div_ss(_mm_set_ss(x), _mm_set_ss(y));
    return u.f[0];
}

// ---- engine entry points -------------------------------------------------------------
// 0x011e08c8 is the MSVCR90 import thunk for _CIacos: acos with its argument and result on
// the x87 stack.  The original source is `acos((double)x)`; cl emits `fld x; call _CIacos;
// fstp y`.  Call the CRT acos with a double argument to reproduce that shape.

// ---- engine globals (animation state registry) ---------------------------------------
// 0x0171e268: array of registered state pointers, 0x0171e2a8: its count.
extern void* g_stateTable_171e268[16];   // 0x0171e268
extern int   g_stateCount_171e2a8;       // 0x0171e2a8

// ---- format descriptor (the stride/compression table the helpers read) ----------------
struct FormatDesc {
    u32 mFlag_0;      // +0x00
    u32 mStride1_4;   // +0x04
    u32 mStride2_8;   // +0x08
    u32 mStride3_c;   // +0x0c
    u32 mStride4_10;  // +0x10
};

// ======================================================================================
// 0x011ff090: 2D format blend.  The low byte of countA/countC is the number of quaternion
// (4-float) elements blended with a slerp/lerp path; the high byte is the number of scalar
// elements lerped.  When the flag pointer's dword is non-zero the blend negates the second
// source (b) before interpolating.
// ======================================================================================
// @ 0x011ff090
void BlendQuatArray(float* dst, u32 count, float* srcA, u32 countA, float* srcB,
                    u32 countC, float t, const int* flagPtr)
{
    u32 nQuatMin;
    u32 nQuatRest;
    int nScalarRest;
    float* pA;

    if ((u8)countA <= (u8)countC) {
        nQuatMin = (u8)countA;
        nQuatRest = (u8)countC - nQuatMin;
    } else {
        nQuatMin = (u8)countC;
        nQuatRest = (u8)countA - nQuatMin;
    }
    {
        u32 c = (u8)count;
        if (c < nQuatMin) nQuatMin = c;
        nScalarRest = (int)(c - nQuatMin);
    }

    while (nQuatMin != 0) {
        float b0 = srcB[0], b1 = srcB[1], b2 = srcB[2], b3 = srcB[3];
        float u = fsingle(1.0f - t);
        float r0 = b0, r1 = b1, r2 = b2, r3 = b3;

        {
            float a0 = srcA[0], a1 = srcA[1], a2 = srcA[2], a3 = srcA[3];
            float w0 = t, w1 = t, w2 = t, w3 = t;
            float u0 = u, u1 = u, u2 = u, u3 = u;
            float dot;
            if (*flagPtr == 0) {
                dot = ((a0 * b0 + a1 * b1) + a2 * b2) + a3 * b3;
            } else {
                dot = ((a0 * -b0 + a1 * -b1) + a2 * -b2) + a3 * -b3;
            }
            if (dot < 0.999f) {
                // 011ff090 recomputes the shared 1/sin(theta) once (divps of the packed ones) then
                // multiplies both sine terms by it.
                float theta = fsingle((float)acos((double)dot));
                float s = fsingle(fsin32(theta));
                float invS = fsingle(1.0f / s);
                float su = fsingle(fsin32(fsingle(u * theta)) * invS);
                float st = fsingle(fsin32(fsingle(t * theta)) * invS);
                u0 = u1 = u2 = u3 = su;
                w0 = w1 = w2 = w3 = st;
            }
            if (*flagPtr == 0) {
                r0 = a0 * u0 + b0 * w0;
                r1 = a1 * u1 + b1 * w1;
                r2 = a2 * u2 + b2 * w2;
                r3 = a3 * u3 + b3 * w3;
            } else {
                // the original negates b with a packed multiply by -1.0; folding that into a
                // subtraction of the product is exact (and keeps the +0.0/-0.0 signs right).
                r0 = a0 * u0 - b0 * w0;
                r1 = a1 * u1 - b1 * w1;
                r2 = a2 * u2 - b2 * w2;
                r3 = a3 * u3 - b3 * w3;
            }
        }

        dst[0] = r0; dst[1] = r1; dst[2] = r2; dst[3] = r3;
        dst += 4; srcA += 4; srcB += 4; ++flagPtr;
        --nQuatMin;
    }

    // the loop already advanced srcA past the blended quaternions; the surplus copy and the
    // scalar tail continue from there (the original advances its `local_1d0` the same way).
    pA = srcA;

    // copy the surplus quaternion elements from the longer source, unblended.  The original writes
    // through a temporary pointer (pfVar17), so this copy does NOT advance `dst`; `dst` only moves
    // on by nScalarRest*4 for the scalar (second) dimension below, which then overwrites the tail
    // of this copied region.
    if ((u8)countA <= (u8)countC) {
        int n = (int)nQuatRest * 4;
        float* w = dst;
        while (n--) *w++ = *pA++;
    } else {
        int n = (int)nQuatRest * 4;
        float* w = dst;
        while (n--) *w++ = *srcB++;
    }

    dst += nScalarRest * 4;

    // second dimension: scalar (single-float) elements, plain lerp.
    {
        u32 nMin, nRest;
        u8 hiA = (u8)(countA >> 8);
        u8 hiC = (u8)(countC >> 8);
        if (hiA <= hiC) {
            nMin = hiA;
            nRest = hiC - nMin;
        } else {
            nMin = hiC;
            nRest = hiA - nMin;
        }
        {
            u32 c = (count >> 8) & 0xff;
            if (nMin <= c) c = nMin;
            nMin = c;
        }
        if (nMin != 0) {
            // the original writes the scalar lerps through a temporary pointer, so `dst` stays at
            // the start of this region; the tail copy below then overwrites its first nRest words.
            u32 k = nMin;
            float* w = dst;
            do {
                *w = (*srcB - *pA) * t + *pA;
                ++pA; ++srcB; ++w;
            } while (--k);
        }
        if (hiA <= hiC) srcB = pA;
        for (; nRest != 0; --nRest) *dst++ = *srcB++;
    }
}

// ======================================================================================
// One quaternion slerp/nlerp step shared by 0x011ff680 and 0x011ffb60:
//   dot = a . b ; if (dot < 0) negate a, dot = -dot;
//   if (dot <= cosBound)  slerp   r = a * sin((1-t)theta)/sin(theta) + b * sin(t*theta)/sin(theta)
//   else                  nlerp   r = normalize(a + (b -/+ a) * t)
// ======================================================================================
// The slerp/nlerp threshold each caller reads from its own image global.  These live in the
// original's .data and are pinned to their addresses by the `// 0x...` annotations, so the
// harness's image data (and any fault-repair override of that dword) reaches the comparison.
extern float g_cosBound_171e248;   // 0x0171e248 (011ff680)
extern float g_cosBound_171e2ec;   // 0x0171e2ec (011ffb60)

static void SlerpQuat4(float* r, const float* aIn, const float* bIn, float t, float cosBound)
{
    float a0 = aIn[0], a1 = aIn[1], a2 = aIn[2], a3 = aIn[3];
    float b0 = bIn[0], b1 = bIn[1], b2 = bIn[2], b3 = bIn[3];
    float dot = ((a0 * b0 + a1 * b1) + a3 * b3) + a2 * b2;

    if (dot < 0.0f) {
        // the original negates the whole a vector with a packed multiply by -1.0; a multiply (not a
        // subtraction/negation, which cl folds to 0 - a) preserves the +0.0 -> -0.0 sign flip that
        // a zero component's result then carries.
        volatile float mneg = -1.0f;
        a0 = fsingle(a0 * mneg);
        a1 = fsingle(a1 * mneg);
        a2 = fsingle(a2 * mneg);
        a3 = fsingle(a3 * mneg);
        dot = -dot;
    }
    // `comiss dot, cosBound; jbe` treats an unordered compare as "slerp" too, so the slerp branch
    // is taken whenever `dot <= cosBound` OR either operand is NaN.
    if (!(dot > cosBound)) {
        // 011ff680/011ffb60 divide each sine term by sin(theta) (divps) rather than 011ff090's
        // reciprocal-multiply; reproduce the division so the rounding matches.
        float theta = fsingle((float)acos((double)dot));
        float s = fsingle(fsin32(theta));
        float sa = divss(fsin32(fsingle((1.0f - t) * theta)), s);
        float sb = divss(fsin32(fsingle(t * theta)), s);
        r[0] = a0 * sa + b0 * sb;
        r[1] = a1 * sa + b1 * sb;
        r[2] = a2 * sa + b2 * sb;
        r[3] = a3 * sa + b3 * sb;
    } else {
        float c0, c1, c2, c3;
        float dot0 = ((a0 * b0 + a1 * b1) + a3 * b3) + a2 * b2;
        // the original uses 0.0 - t (subps from a zeroed register) rather than a sign flip, so a
        // zero t stays +0.0 and the products keep the original zero signs.
        float negT = fsingle(0.0f - t);
        if (!(dot0 > 0.0f)) {
            c0 = (b0 + a0) * negT;
            c1 = (b1 + a1) * negT;
            c2 = (b2 + a2) * negT;
            c3 = (b3 + a3) * negT;
        } else {
            c0 = (b0 - a0) * t;
            c1 = (b1 - a1) * t;
            c2 = (b2 - a2) * t;
            c3 = (b3 - a3) * t;
        }
        c0 += a0; c1 += a1; c2 += a2; c3 += a3;
        {
            float sumSq = (c0 * c0 + c2 * c2) + (c1 * c1 + c3 * c3);
            // the original seeds the reciprocal length with the SSE approximation and then
            // runs two Newton-Raphson refinements (rsqrtps; *0.5; 1 - s*x*x; ...; addps),
            // so reproduce that exact sequence rather than 1/sqrtf.
            union { __m128 v; float f[4]; } rsv;
            rsv.v = _mm_rsqrt_ss(_mm_set_ss(sumSq));
            float invLen = rsv.f[0];
            invLen = invLen + (1.0f - sumSq * (invLen * invLen)) * (invLen * 0.5f);
            invLen = invLen + (1.0f - sumSq * (invLen * invLen)) * (invLen * 0.5f);
            r[0] = c0 * invLen;
            r[1] = c1 * invLen;
            r[2] = c2 * invLen;
            r[3] = c3 * invLen;
        }
    }
}

// ======================================================================================
// 0x011ff680: blend an array of quaternions (low byte of count) then lerp the scalar tail
// (high byte of count).  dst=arg0, a=arg1, b=arg2, count=arg3, t=arg4 (float).
// ======================================================================================
// @ 0x011ff680
void BlendQuatArray2(float* dst, const float* a, const float* b, u32 count, float t)
{
    u32 n = count & 0xff;
    if (n != 0) {
        float cb = fcos32(g_cosBound_171e248);
        do {
            SlerpQuat4(dst, a, b, t, cb);
            dst += 4; a += 4; b += 4;
        } while (--n);
    }
    {
        u32 m = (count >> 8) & 0xff;
        if (m != 0) {
            do {
                *dst = (*b - *a) * t + *a;
                ++a; ++b; ++dst;
            } while (--m);
        }
    }
}

// ======================================================================================
// 0x011ffb60: keyframe blend between the two frame pointers held by *arg1, at byte offset
// arg2 inside each frame, with the frame time arg3 used to derive the blend factor
//   t = (time - a[off]) / (b[off] - a[off]).
// When *arg4 != 0 the function returns immediately.  Otherwise it advances past the count
// byte of arg5 (desc) and blends low-byte quaternions + high-byte scalars into arg0.
// ======================================================================================
// @ 0x011ffb60
void BlendKeyframeQuatArray(float* dst, void** frames, int off, float time, const int* flagPtr,
                            const u32* desc)
{
    const float* a = (const float*)frames[0];
    const float* b = (const float*)frames[1];
    float t = (time - *(const float*)((const char*)a + off)) /
              (*(const float*)((const char*)b + off) - *(const float*)((const char*)a + off));
    u32 packed = desc[2];

    if (*flagPtr == 0) {
        u32 n = packed & 0xff;
        if (n != 0) {
            float cb = fcos32(g_cosBound_171e2ec);
            do {
                SlerpQuat4(dst, a, b, t, cb);
                dst += 4; a += 4; b += 4;
            } while (--n);
        }
        packed = (packed >> 8) & 0xff;
        if (packed != 0) {
            do {
                *dst = (*b - *a) * t + *a;
                ++a; ++b; ++dst;
            } while (--packed);
        }
    }
}

// ======================================================================================
// 0x011ff9f0: register a state object pointer in the global table if not already present.
// Returns true when it was appended, false when the pointer is already registered or the
// table is full.
// ======================================================================================
// @ 0x011ff9f0
int RegisterState(void* p)
{
    int count = g_stateCount_171e2a8;
    if (count < 16) {
        int i;
        for (i = 0; i < count; ++i) {
            if (*(int*)g_stateTable_171e268[i] == *(int*)p) return 0;
        }
        g_stateTable_171e268[count] = p;
        g_stateCount_171e2a8 = count + 1;
        return 1;
    }
    return 0;
}

// ======================================================================================
// 0x011ffa40: find the registered state object whose first dword equals id.  Returns the
// pointer or 0.
// ======================================================================================
// @ 0x011ffa40
void* FindState(int id)
{
    int count = g_stateCount_171e2a8;
    int i;
    for (i = 0; i < count; ++i) {
        if (*(int*)g_stateTable_171e268[i] == id) return g_stateTable_171e268[i];
    }
    return 0;
}

// ======================================================================================
// 0x011ffa70: element size = (format >> 8 & 0xff) * 8, but only while the descriptor's
// second stride field is below 4.
// ======================================================================================
// @ 0x011ffa70
u32 FormatSize8(u32 fmt, const FormatDesc* d)
{
    u32 r = 0;
    if (d->mStride1_4 < 4) r = (u32)(u8)(fmt >> 8) << 3;
    return r;
}

// ======================================================================================
// 0x011ffa90: call the two per-element decompression callbacks over a run of elements.
// The low byte of sel drives the callback at desc+0x28 with stride desc+8; the high byte
// drives desc+0x2c with stride desc+4.  (arg1 is the base pointer, arg3 the descriptor.)
// ======================================================================================
struct FormatCallbacks {
    u32 mField_0;     // +0x00
    u32 mStride1_4;   // +0x04
    u32 mStride2_8;   // +0x08
    u32 mStride3_c;   // +0x0c
    u32 mStride4_10;  // +0x10
    u32 pad_14[5];    // +0x14 .. +0x24
    void (__cdecl* mpDecode0_28)(void*);   // +0x28
    void (__cdecl* mpDecode1_2c)(void*);   // +0x2c
};

// @ 0x011ffa90
void DecodeRun(void* base, u32 sel, FormatCallbacks* d)
{
    u32 n = sel & 0xff;
    if (n != 0) {
        do {
            d->mpDecode0_28(base);
            base = (char*)base + d->mStride2_8;
        } while (--n);
    }
    n = (sel >> 8) & 0xff;
    if (n != 0) {
        do {
            d->mpDecode1_2c(base);
            base = (char*)base + d->mStride1_4;
        } while (--n);
    }
}

// ======================================================================================
// 0x011ffae0: largest relevant stride of the descriptor, selected by the low/high byte of
// the selector.
// ======================================================================================
// @ 0x011ffae0
u32 SelectMaxStride(u32 sel, u32 /*unused*/, const FormatDesc* d)
{
    u32 r = 0;
    if ((sel & 0xff00) != 0) r = d->mStride1_4;
    if ((sel & 0xff) != 0) {
        if (r <= d->mStride2_8) r = d->mStride2_8;
    }
    return r;
}

// ======================================================================================
// 0x011ffb00: element size for a two-dimensional count, aligned up to the chosen stride
// (plus the header size 4 or 0xc selected by bit 0 of flags).
// ======================================================================================
// @ 0x011ffb00
u32 FormatSizeAligned(u32 sel, u32 flags, const FormatDesc* d)
{
    u32 align = 0;
    if ((sel & 0xff00) != 0) align = d->mStride1_4;
    if ((sel & 0xff) != 0) {
        if (align <= d->mStride2_8) align = d->mStride2_8;
    }
    u32 size = (sel >> 8 & 0xff) * d->mStride1_4 + (sel & 0xff) * d->mStride2_8;
    if (flags & 1) {
        size += 0xc;
        return (align + size - 1) & ~(align - 1);
    }
    size += 4;
    return (align + size - 1) & ~(align - 1);
}

// ======================================================================================
// 0x011fff10: element size = (format >> 8 & 0xff) * 0x18, only while the descriptor's
// second stride field is below 4.
// ======================================================================================
// @ 0x011fff10
u32 FormatSize24(u32 fmt, const FormatDesc* d)
{
    u32 r = 0;
    if (d->mStride1_4 < 4) r = ((fmt >> 8) & 0xff) * 0x18;
    return r;
}

// ======================================================================================
// 0x011fff30: run the per-element callbacks once for the first axis and three times for the
// second axis of the descriptor.
// ======================================================================================
// @ 0x011fff30
void DecodeRun3(void* base, u32 sel, FormatCallbacks* d)
{
    void* p = base;
    if ((sel & 0xff) != 0) {
        d->mpDecode0_28(p);
        p = (char*)p + d->mStride2_8;
    }
    if ((sel & 0xff00) != 0) {
        d->mpDecode1_2c(p);
        p = (char*)p + d->mStride1_4;
        d->mpDecode1_2c(p);
        d->mpDecode1_2c((char*)p + d->mStride1_4);
    }
}

// ======================================================================================
// 0x011fff80: largest relevant stride, with the header size 0x10 substituted when the
// descriptor's first field is non-null.
// ======================================================================================
// @ 0x011fff80
u32 SelectMaxStride16(u32 sel, u32 /*unused*/, const FormatDesc* d)
{
    u32 r = 0;
    if ((sel & 0xff00) != 0) {
        r = 0x10;
        if (d->mFlag_0 != 0) r = d->mStride3_c;
    }
    if ((sel & 0xff) != 0) {
        if (r <= d->mStride4_10) r = d->mStride4_10;
    }
    return r;
}

// ======================================================================================
// 0x011fffb0: element size for the 3-wide second axis, aligned up like 0x011ffb00.
// ======================================================================================
// @ 0x011fffb0
u32 FormatSizeAligned3(u32 sel, u32 flags, const FormatDesc* d)
{
    u32 align = 0;
    if ((sel & 0xff00) != 0) {
        align = 0x10;
        if (d->mFlag_0 != 0) align = d->mStride3_c;
    }
    if ((sel & 0xff) != 0) {
        if (align <= d->mStride4_10) align = d->mStride4_10;
    }
    u32 size = (sel & 0xff) * d->mStride2_8 + ((sel >> 8) & 0xff) * d->mStride1_4 * 3;
    if (flags & 1) {
        size += 0xc;
    } else {
        size += 4;
    }
    if (align > 1) size = (size + (align - 1)) & ~(align - 1);
    return size;
}

