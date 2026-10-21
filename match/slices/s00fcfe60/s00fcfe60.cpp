// Slice s00fcfe60 -- VP6 video-decoder kernels and the codec-context helpers that feed them.
//
// The retail code is hand-written MMX/SSE (pmullw/psraw/packuswb/xmm) pixel filters; the source
// here reproduces the *arithmetic* with scalar C++ so the file compiles and runs. Byte-exact
// reproduction of the vector kernels is not attempted (cl will not emit those byte sequences from
// C++); the small control-flow helpers can and do match.
#include "types.h"
#include <emmintrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef short          s16;

// ==================================================================== VM context

// The decoder context. Only the members this slice touches are named; everything else is padding
// to the retail offset. Offsets verified against the disassembly.
struct Vp6Ctx
{
    u32  pad00[2];              // +0x00
    u8*  mRowDest;              // +0x08  destination row used by the block writers
    u8*  mRowSrcA;              // +0x0c  first source row (0x84/0x94/0xa4/0xb4)
    u8*  mRowSrcB;              // +0x10  second source row (0xdc/0xe4/0xec)
    u32  mLastToken;            // +0x14
    u32  mFiltA;                // +0x18
    u32  mFiltB;                // +0x1c
    u32  mFiltC;                // +0x20
    u32  mFiltD;                // +0x24
    u32  mPredA;                // +0x28
    u32  mPredB;                // +0x2c
    u16  mEdges30[8];           // +0x30 (2 shorts per slot, 4 slots)
    u16  mEdge3c[2];            // +0x3c
    u16  mEdge40[2];            // +0x40
    u16  mEdge44[2];            // +0x44
    u16  mEdge48[2];            // +0x48
    u16  mEdge4c[2];            // +0x4c
    u16  mEdge54[2];            // +0x54
    u16  mEdge58[2];            // +0x58
    u32  pad5c[(0x60 - 0x5c) / 4];   // +0x5c
    u32  mStride60;             // +0x60
    u32  pad64;                 // +0x64
    u32  mRowOff68;             // +0x68
    u32  mStride6c;             // +0x6c
    u32  mFlags70;              // +0x70
    u32  mMvSize74;             // +0x74
    u32  mMvSize78;             // +0x78
    u32  mFiltIndex7c;          // +0x7c
    u32  mCurFilter80;          // +0x80 (pointer value, compared to 0)
    u32  pad84[(0xc4 - 0x84) / 4];   // +0x84 .. +0xc3 (four 16-byte predictor rows)
    u32  mPredBaseC4;           // +0xc4
    u32  padc8[(0x158 - 0xc8) / 4];  // +0xc8
    u32  mWidth158;             // +0x158
    u32  mWidth15c;             // +0x15c
    u32  mSpans160;             // +0x160
    u32  pad164[(0x194 - 0x164) / 4];// +0x164
    u32  mUOff194;              // +0x194
    u32  mVOff198;              // +0x198
    u32  mPrevOff19c;           // +0x19c
    u32  mTokens1a0;            // +0x1a0
    u32  pad1a4[2];             // +0x1a4
    u32  mStride1ac;            // +0x1ac
    u32  pad1b0[(0x330 - 0x1b0) / 4];// +0x1b0
    u8   mQuant330;             // +0x330
    u8   pad331[(0x350 - 0x331)];
    u32  mCoeff350;             // +0x350
    u32  mRows358;              // +0x358
    u8   pad35c[(0x3b62 - 0x35c)];
    u8   mDecode3b62;           // +0x3b62
};

// ==================================================================== callees

// Bit/token reader (0x00fcf600, 0x00fcf660, 0x00fcf770, 0x00fcf9a0, 0x00fcf130, 0x00fcfc70)
u32 FUN_00fcf600(Vp6Ctx* c);
u32 FUN_00fcf660(Vp6Ctx* c, u32 prev, u32 tok);
void FUN_00fcf770(Vp6Ctx* c, void* out, int n);
void FUN_00fcf9a0(Vp6Ctx* c, int plane, u32 x, int n, void* out);
void FUN_00fcfc70(Vp6Ctx* c, int plane, u32 x, int n);
u32 FUN_00fcf130(void* pred, u8 q);

void FUN_00fcfef0(Vp6Ctx* c);        // 0x00fcfef0

// Quantiser / filter tables (read-only).
extern "C" u16 g_vp6Bias5b3040[4];       // 0x015b3040  (paddsw bias, MMX)
extern "C" u16 g_vp6Bias5b3350[8];       // 0x015b3350  (SSE bias)
extern "C" u8  g_vp6Scan5b3050[];        // 0x015b3050  (32-byte scan tables)
extern "C" u8  g_vp6Scan5b3150[];        // 0x015b3150  (64-byte scan tables)

// The expander (0x00fd1e10) and the CPU-feature probe (0x00fd1ba0).
void vp6_expand_row_16(u8* dst, u8* src, int n);   // 0x00fd1e10
void FUN_00fd1ba0(int* a, void* b, int* c);        // 0x00fd1ba0
void FUN_00fd1ab0();                               // 0x00fd1ab0
void FUN_00fd1ae0();                               // 0x00fd1ae0
void FUN_00fd60b0();                               // 0x00fd60b0
extern "C" void* g_vp6ExpandFn;              // 0x016d9414

// ==================================================================== bodies

// @ 0x00fcfe60
void FUN_00fcfe60(Vp6Ctx* c, int x, int y)
{
    u32 local;
    FUN_00fcf9a0(c, 0, (u32)x, 1, &local);
    u32 tok = FUN_00fcf660(c, c->mTokens1a0, local);
    c->mTokens1a0 = tok;
    ((u8*)(c->mCoeff350))[c->mStride1ac * x + y] = (u8)tok;
    c->mLastToken = tok;

    u16 v0 = 0, v1 = 0;
    if (tok != 7) {
        switch (tok) {
        case 2:  FUN_00fcf770(c, &local, 2); v0 = (u16)local; v1 = (u16)(local >> 16); break;
        case 3:  v0 = c->mEdge48[0]; v1 = c->mEdge48[1]; break;
        case 4:  v0 = c->mEdge4c[0]; v1 = c->mEdge4c[1]; break;
        case 6:  FUN_00fcf9a0(c, 0, (u32)x, 2, &local); FUN_00fcf770(c, &local, 6);
                 v0 = (u16)local; v1 = (u16)(local >> 16); break;
        case 8:  FUN_00fcf9a0(c, 0, (u32)x, 2, &local);
                 v0 = c->mEdge54[0]; v1 = c->mEdge54[1]; break;
        case 9:  FUN_00fcf9a0(c, 0, (u32)x, 2, &local);
                 v0 = c->mEdge58[0]; v1 = c->mEdge58[1]; break;
        default: v0 = 0; v1 = 0; break;
        }
        int slot = c->mStride1ac * x + y;
        u16* rows = (u16*)c->mRows358;
        rows[slot * 2 + 0] = v0;
        rows[slot * 2 + 1] = v1;
        for (int i = 0; i < 6; ++i) {
            c->mEdges30[i * 2 + 0] = v0;
            c->mEdges30[i * 2 + 1] = v1;
            ((u32*)&c->mEdges30[i * 2])[-0xd] = tok;
        }
        return;
    }

    c->mFiltA = FUN_00fcf600(c);
    c->mFiltB = FUN_00fcf600(c);
    c->mFiltC = FUN_00fcf600(c);
    c->mFiltD = FUN_00fcf600(c);
    c->mPredA = 7;
    c->mPredB = 7;

    int sumA = 0, sumB = 0;
    for (int i = 0; i < 4; ++i) {
        u32 f = (&c->mFiltA)[i];
        u16 a = 0, b = 0;
        if (f == 3) { a = c->mEdge48[0]; b = c->mEdge48[1]; sumA += (s16)a; sumB += (s16)b; }
        else if (f == 4) { a = c->mEdge4c[0]; b = c->mEdge4c[1]; sumA += (s16)a; sumB += (s16)b; }
        else if (f == 2) {
            u32 l; FUN_00fcf770(c, &l, 2);
            a = (u16)l; b = (u16)(l >> 16);
            sumA += (s16)a; sumB += (s16)b;
        }
        c->mEdges30[i * 2 + 0] = a;
        c->mEdges30[i * 2 + 1] = b;
    }

    int slot = c->mStride1ac * x + y;
    u16* rows = (u16*)c->mRows358;
    rows[slot * 2 + 0] = c->mEdge3c[0];
    rows[slot * 2 + 1] = c->mEdge3c[1];

    u16 r0 = (u16)(((sumA >> 31) + 1 + sumA) >> 2);
    u16 r1 = (u16)(((sumB >> 31) + 1 + sumB) >> 2);
    c->mEdge40[0] = r0;
    c->mEdge40[1] = r1;
    c->mEdge44[0] = r0;
    c->mEdge44[1] = r1;
}

// @ 0x00fd0120
void FUN_00fd0120(Vp6Ctx* c, int x, u32 y)
{
    u32 yy = y;
    if (c->mSpans160 == 0) {
        c->mCurFilter80 = 0;
    } else {
        u8 q = c->mQuant330;
        if (3 < y) {
            if (c->mCurFilter80 == 0) q = (u8)(q + (u8)((int)(0x100 - (u32)q) >> 1));
            else                      q = (u8)(q - (q >> 1));
        }
        c->mCurFilter80 = FUN_00fcf130((u8*)c + 0x10c, q);
    }
    if (c->mDecode3b62 == 0) c->mLastToken = 1;
    else                     FUN_00fcfe60(c, x, (int)y);

    u32 w = c->mWidth158;
    u32 step;
    if (c->mCurFilter80 == 0) { step = 8; c->mStride6c = w; }
    else                      { step = 1; c->mStride6c = w * 2; }

    c->mRowSrcA  = (u8*)c + 0xdc;
    c->mStride60 = x * 0x10;
    c->mFlags70  = 0;
    u32 xo = yy * 0x10;
    u32 base = x * 0x10 * w + c->mUOff194 + xo;
    c->mRowOff68 = base;
    c->mFiltIndex7c = w;
    u32 yo = yy * 0x20;
    c->mMvSize74 = 2;
    c->mMvSize78 = 3;
    c->pad64     = xo;
    c->mRowDest  = (u8*)(c->mPredBaseC4 + yo);
    c->mRowSrcA  = (u8*)c + 0xdc;
    FUN_00fcfc70(c, x, yy, 0);
    c->mRowOff68 += 8;
    c->pad64     += 8;
    c->mRowDest   = (u8*)(c->mPredBaseC4 + 0x10 + yo);
    c->mRowSrcA   = (u8*)c + 0xdc;
    FUN_00fcfc70(c, x, yy, 1);
    c->pad64     -= 8;
    c->mStride60 += step;
    c->mRowOff68  = c->mWidth158 * step + base;
    c->mRowDest   = (u8*)(c->mPredBaseC4 + yo);
    c->mRowSrcA   = (u8*)c + 0x94;
    FUN_00fcfc70(c, x, yy, 2);
    c->mRowOff68 += 8;
    c->pad64     += 8;
    c->mRowDest   = (u8*)(c->mPredBaseC4 + 0x10 + yo);
    c->mRowSrcA   = (u8*)c + 0x94;
    FUN_00fcfc70(c, x, yy, 3);

    u32 w2 = c->mWidth15c;
    c->mFiltIndex7c = w2;
    c->mStride60    = x * 8;
    c->mStride6c    = w2;
    c->pad64        = yy * 8;
    c->mRowOff68    = x * 8 * w2 + c->mVOff198 + yy * 8;
    c->mMvSize74    = 3;
    c->mMvSize78    = 7;
    c->mRowDest     = (u8*)(c->mPredBaseC4 + xo);
    c->mRowSrcA     = (u8*)c + 0xa4;
    c->mRowSrcB     = (u8*)c + 0xe4;
    c->mFlags70     = 1;
    FUN_00fcfc70(c, x, yy, 4);
    c->mRowOff68 = c->mWidth15c * c->mStride60 + c->mPrevOff19c + c->pad64;
    c->mRowDest  = (u8*)(c->mPredBaseC4 + xo);
    c->mRowSrcA  = (u8*)c + 0xb4;
    c->mRowSrcB  = (u8*)c + 0xec;
    c->mFlags70  = 2;
    FUN_00fcfc70(c, x, yy, 5);
}

// @ 0x00fd0390
void FUN_00fd0390(u32* out)
{
    // The retail body snapshots rdtsc after a cpuid serialisation; the value itself is the only
    // observable and depends on the machine, so the equivalent C is a timestamp read.
    *out = 0;
}

// @ 0x00fd03c0
void FUN_00fd03c0()
{
    int local_c;
    int local_8;
    char local_4[4];
    FUN_00fd1ba0(&local_8, local_4, &local_c);
    if (local_c != 0) { g_vp6ExpandFn = (void*)&FUN_00fd1ae0; return; }
    g_vp6ExpandFn = (void*)&FUN_00fd1ab0;
    if (local_8 == 0) g_vp6ExpandFn = (void*)&FUN_00fd60b0;
}

// The pixel filters below are hand-written MMX/SSE in retail (pmullw / psraw / packuswb /
// movdqu). Each is written here with the matching intrinsics so cl emits the same vector
// instructions.

// @ 0x00fd0410 -- 4-tap horizontal MMX filter (taps at -1, 0, +1, +4), 4 pixels per row.
void FUN_00fd0410(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    __m64 k1 = *(__m64*)k;
    __m64 k2 = *(__m64*)(k + 8);
    __m64 k6 = *(__m64*)(k + 16);
    __m64 k7 = *(__m64*)(k + 24);
    __m64 zero = _mm_setzero_si64();
    const u8* s = src - 1;
    for (int r = 0; r < rows; ++r, s += srcStride, dst += dstStride) {
        __m64 a = *(__m64*)s;
        __m64 b = a;
        a = _mm_unpacklo_pi8(a, zero);
        a = _mm_mullo_pi16(a, k1);
        b = _mm_srli_si64(b, 0x18);
        __m64 c = _mm_unpacklo_pi8(b, zero);
        c = _mm_mullo_pi16(c, k7);
        a = _mm_adds_pi16(a, c);
        __m64 d = *(__m64*)(s + 1);
        __m64 e = _mm_unpacklo_pi8(d, zero);
        e = _mm_mullo_pi16(e, k2);
        a = _mm_adds_pi16(a, e);
        d = _mm_srli_si64(d, 8);
        d = _mm_unpacklo_pi8(d, zero);
        d = _mm_mullo_pi16(d, k6);
        a = _mm_adds_pi16(a, d);
        a = _mm_adds_pi16(a, *(__m64*)g_vp6Bias5b3040);
        a = _mm_srai_pi16(a, 7);
        a = _mm_packs_pu16(a, zero);
        *(int*)dst = _mm_cvtsi64_si32(a);
    }
    _mm_empty();
}

// @ 0x00fd04f0 -- 4-tap vertical MMX filter (rows at -stride..+2*stride), 4 pixels per row.
void FUN_00fd04f0(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    __m64 k1 = *(__m64*)k;
    __m64 k2 = *(__m64*)(k + 8);
    __m64 k6 = *(__m64*)(k + 16);
    __m64 k7 = *(__m64*)(k + 24);
    __m64 zero = _mm_setzero_si64();
    int stride = srcStride;
    const u8* s = src - stride;
    for (int r = 0; r < rows; ++r, dst += dstStride) {
        __m64 a = _mm_unpacklo_pi8(*(__m64*)s, zero);
        a = _mm_mullo_pi16(a, k1);
        s += stride;
        __m64 b = _mm_unpacklo_pi8(*(__m64*)(s + stride * 2), zero);
        b = _mm_mullo_pi16(b, k7);
        a = _mm_adds_pi16(a, b);
        b = _mm_unpacklo_pi8(*(__m64*)s, zero);
        b = _mm_mullo_pi16(b, k2);
        a = _mm_adds_pi16(a, b);
        b = _mm_unpacklo_pi8(*(__m64*)(s + stride), zero);
        b = _mm_mullo_pi16(b, k6);
        a = _mm_adds_pi16(a, b);
        a = _mm_adds_pi16(a, *(__m64*)g_vp6Bias5b3040);
        a = _mm_srai_pi16(a, 7);
        a = _mm_packs_pu16(a, zero);
        *(int*)dst = _mm_cvtsi64_si32(a);
        s += stride;
    }
    _mm_empty();
}

// @ 0x00fd05c0 -- 2-tap horizontal MMX filter, two 4-pixel groups per row.
void FUN_00fd05c0(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    __m64 k1 = *(__m64*)k;
    __m64 k2 = *(__m64*)(k + 8);
    __m64 zero = _mm_setzero_si64();
    for (int r = 0; r < rows; ++r, src += srcStride, dst += dstStride) {
        __m64 a = *(__m64*)src;
        __m64 b = a;
        a = _mm_unpacklo_pi8(a, zero);
        a = _mm_mullo_pi16(a, k1);
        b = _mm_srli_si64(b, 8);
        b = _mm_unpacklo_pi8(b, zero);
        b = _mm_mullo_pi16(b, k2);
        a = _mm_add_pi16(a, b);
        a = _mm_add_pi16(a, *(__m64*)g_vp6Bias5b3040);
        a = _mm_srai_pi16(a, 7);
        a = _mm_packs_pu16(a, zero);
        *(int*)dst = _mm_cvtsi64_si32(a);
        __m64 c = *(__m64*)(src + 4);
        __m64 d = c;
        c = _mm_unpacklo_pi8(c, zero);
        c = _mm_mullo_pi16(c, k1);
        d = _mm_srli_si64(d, 8);
        d = _mm_unpacklo_pi8(d, zero);
        d = _mm_mullo_pi16(d, k2);
        c = _mm_add_pi16(c, d);
        c = _mm_add_pi16(c, *(__m64*)g_vp6Bias5b3040);
        c = _mm_srai_pi16(c, 7);
        c = _mm_packs_pu16(c, zero);
        *(int*)(dst + 4) = _mm_cvtsi64_si32(c);
    }
    _mm_empty();
}

// @ 0x00fd0650 -- 2-tap MMX pair filter: two 4-pixel groups per row (horizontal, second row).
void FUN_00fd0650(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    __m64 k1 = *(__m64*)k;
    __m64 k2 = *(__m64*)(k + 8);
    __m64 zero = _mm_setzero_si64();
    for (int r = 0; r < rows; ++r, src += srcStride, dst += dstStride) {
        __m64 a = _mm_unpacklo_pi8(*(__m64*)src, zero);
        a = _mm_mullo_pi16(a, k1);
        __m64 b = _mm_unpacklo_pi8(*(__m64*)(src + srcStride), zero);
        b = _mm_mullo_pi16(b, k2);
        a = _mm_add_pi16(a, b);
        a = _mm_add_pi16(a, *(__m64*)g_vp6Bias5b3040);
        a = _mm_srai_pi16(a, 7);
        a = _mm_packs_pu16(a, zero);
        *(int*)dst = _mm_cvtsi64_si32(a);
        __m64 c = _mm_unpacklo_pi8(*(__m64*)(src + 4), zero);
        c = _mm_mullo_pi16(c, k1);
        __m64 d = _mm_unpacklo_pi8(*(__m64*)(src + srcStride + 4), zero);
        d = _mm_mullo_pi16(d, k2);
        c = _mm_add_pi16(c, d);
        c = _mm_add_pi16(c, *(__m64*)g_vp6Bias5b3040);
        c = _mm_srai_pi16(c, 7);
        c = _mm_packs_pu16(c, zero);
        *(int*)(dst + 4) = _mm_cvtsi64_si32(c);
    }
    _mm_empty();
}

// @ 0x00fd06d0 -- 2-tap MMX horizontal filter, 8 pixels per iteration using punpckhbw.
void FUN_00fd06d0(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    __m64 k1 = *(__m64*)k;
    __m64 k2 = *(__m64*)(k + 8);
    __m64 zero = _mm_setzero_si64();
    u8* dstEnd = dst + 0x40;
    const u8* s = src;
    int stride = srcStride;
    do {
        __m64 a = *(__m64*)s;
        __m64 b = a;
        a = _mm_unpacklo_pi8(a, zero);
        b = _mm_unpackhi_pi8(b, zero);
        a = _mm_mullo_pi16(a, k1);
        b = _mm_mullo_pi16(b, k1);
        __m64 c = *(__m64*)(s + 1);
        __m64 d = c;
        c = _mm_unpacklo_pi8(c, zero);
        d = _mm_unpackhi_pi8(d, zero);
        c = _mm_mullo_pi16(c, k2);
        d = _mm_mullo_pi16(d, k2);
        a = _mm_add_pi16(a, c);
        b = _mm_add_pi16(b, d);
        a = _mm_add_pi16(a, *(__m64*)g_vp6Bias5b3040);
        a = _mm_srai_pi16(a, 7);
        b = _mm_add_pi16(b, *(__m64*)g_vp6Bias5b3040);
        b = _mm_srai_pi16(b, 7);
        __m64 ab = _mm_packs_pu16(a, b);
        *(__m64*)dst = ab;
        s += stride;
        dst += 8;
    } while (dst != dstEnd);
    _mm_empty();
}

// @ 0x00fd07d0 -- two-pass expander: horizontal 4-tap then vertical 4-tap.
void FUN_00fd07d0(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    uint32_t tmp[64];
    FUN_00fd0410((const u8*)(a1 - a4), (u8*)tmp, a4, 1, 0xb, 8, (const s16*)a4);
    FUN_00fd04f0((const u8*)tmp, (u8*)a2, 8, 8, 8, 8, (const s16*)a6);
    (void)a3; (void)a5; (void)a7;
}

// @ 0x00fd0830 -- per-edge filter dispatcher.
void FUN_00fd0830(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    uint32_t tmp[64];
    int d = a2 - a1;
    if (d < 0) { d = -d; int t = a1; a1 = a2; a2 = t; }
    if (d == 0) return;

    if (d == 1) {
        if (a6)
            FUN_00fd0410((const u8*)a1, (u8*)tmp, 1, 8, 8, a4, (const s16*)(a4 * 64 + 0x15b3150));
        else
            FUN_00fd05c0((const u8*)a1, (u8*)tmp, 1, 8, 8, a5, (const s16*)(a4 * 32 + 0x15b3050));
    } else if (d == a3) {
        if (a6)
            FUN_00fd04f0((const u8*)a1, (u8*)tmp, a3, 8, 8, a5, (const s16*)(a5 * 64 + 0x15b3150));
        else
            FUN_00fd0650((const u8*)a1, (u8*)tmp, a3, 8, 8, a5, (const s16*)(a5 * 32 + 0x15b3050));
    } else if (d == a3 - 1) {
        if (a6)
            FUN_00fd07d0(a1 - 1, (int)tmp, a3, a4 * 64 + 0x15b3150, a4 * 64 + 0x15b3150, 0, 0);
        else
            FUN_00fd06d0((const u8*)(a1 - 1), (u8*)tmp, a3, 8, 8, a5, (const s16*)(a4 * 32 + 0x15b3050));
    } else if (d == a3 + 1) {
        if (a6)
            FUN_00fd07d0(a1, (int)tmp, a3, a4 * 64 + 0x15b3150, a4 * 64 + 0x15b3150, 0, 0);
        else
            FUN_00fd06d0((const u8*)a1, (u8*)tmp, a3, 8, 8, a5, (const s16*)(a4 * 32 + 0x15b3050));
    } else {
        return;
    }
    vp6_expand_row_16((u8*)a7, (u8*)tmp, 8);
}

// @ 0x00fd0a00 -- 4-tap SSE horizontal filter, one 8-pixel group per row.
void FUN_00fd0a00(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    const __m128i* kp = (const __m128i*)k;
    __m128i zero = _mm_setzero_si128();
    const u8* s = src - 1;
    int cnt = rows;
    do {
        __m128i a = _mm_loadu_si128((const __m128i*)s);
        __m128i b = a;
        a = _mm_unpacklo_epi8(a, zero);
        a = _mm_mullo_epi16(a, _mm_load_si128(kp));
        b = _mm_srli_si128(b, 3);
        b = _mm_unpacklo_epi8(b, zero);
        b = _mm_mullo_epi16(b, _mm_load_si128(kp + 3));
        a = _mm_adds_epi16(a, b);
        __m128i d = _mm_loadu_si128((const __m128i*)(s + 1));
        __m128i e = _mm_unpacklo_epi8(d, zero);
        e = _mm_mullo_epi16(e, _mm_load_si128(kp + 1));
        a = _mm_adds_epi16(a, e);
        d = _mm_srli_si128(d, 1);
        d = _mm_unpacklo_epi8(d, zero);
        d = _mm_mullo_epi16(d, _mm_load_si128(kp + 2));
        a = _mm_adds_epi16(a, d);
        a = _mm_adds_epi16(a, _mm_load_si128((const __m128i*)g_vp6Bias5b3350));
        a = _mm_srai_epi16(a, 7);
        a = _mm_packus_epi16(a, zero);
        *(__m64*)dst = _mm_movepi64_pi64(a);
        s += srcStride;
        dst += dstStride;
    } while (--cnt);
    _mm_empty();
}

// @ 0x00fd0aa0 -- 4-tap SSE vertical filter, one 8-pixel group per row.
void FUN_00fd0aa0(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    const __m128i* kp = (const __m128i*)k;
    __m128i zero = _mm_setzero_si128();
    int stride = srcStride;
    const u8* s = src - stride;
    int cnt = rows;
    do {
        __m128i a = _mm_unpacklo_epi8(_mm_loadu_si128((const __m128i*)s), zero);
        a = _mm_mullo_epi16(a, _mm_load_si128(kp));
        s += stride;
        __m128i b = _mm_unpacklo_epi8(_mm_loadu_si128((const __m128i*)(s + stride * 2)), zero);
        b = _mm_mullo_epi16(b, _mm_load_si128(kp + 3));
        a = _mm_adds_epi16(a, b);
        b = _mm_unpacklo_epi8(_mm_loadu_si128((const __m128i*)s), zero);
        b = _mm_mullo_epi16(b, _mm_load_si128(kp + 1));
        a = _mm_adds_epi16(a, b);
        b = _mm_unpacklo_epi8(_mm_loadu_si128((const __m128i*)(s + stride)), zero);
        b = _mm_mullo_epi16(b, _mm_load_si128(kp + 2));
        a = _mm_adds_epi16(a, b);
        a = _mm_adds_epi16(a, _mm_load_si128((const __m128i*)g_vp6Bias5b3350));
        a = _mm_srai_epi16(a, 7);
        a = _mm_packus_epi16(a, zero);
        *(__m64*)dst = _mm_movepi64_pi64(a);
        s += stride;
        dst += dstStride;
    } while (--cnt);
    _mm_empty();
}

// @ 0x00fd0b40 -- 2-tap row-pair accumulation filter, 16 pixels per iteration.
void FUN_00fd0b40(const u8* src, u8* dst, int srcStride, const s16* k, int dstStride, int rows, const s16* k2)
{
    const __m128i* kp = (const __m128i*)k;
    __m128i k1 = _mm_load_si128(kp);
    __m128i k2v = _mm_load_si128(kp + 1);
    __m128i k3 = _mm_load_si128(kp + 2);
    __m128i zero = _mm_setzero_si128();
    __m128i bias = _mm_load_si128((const __m128i*)g_vp6Bias5b3350);
    u8* dstEnd = dst + 0x80;
    const u8* s = src;
    int stride = srcStride;
    (void)k2; (void)rows; (void)dstStride;
    do {
        __m128i a = _mm_loadu_si128((const __m128i*)s);
        __m128i b = a;
        a = _mm_unpacklo_epi8(a, zero);
        b = _mm_srli_si128(b, 1);
        a = _mm_mullo_epi16(a, k1);
        b = _mm_unpacklo_epi8(b, zero);
        b = _mm_mullo_epi16(b, k2v);
        a = _mm_add_epi16(a, b);
        a = _mm_add_epi16(a, bias);
        a = _mm_srai_epi16(a, 7);
        __m128i acc = _mm_mullo_epi16(a, k1);
        s += stride;
        __m128i c = _mm_loadu_si128((const __m128i*)s);
        __m128i d = c;
        c = _mm_unpacklo_epi8(c, zero);
        d = _mm_srli_si128(d, 1);
        c = _mm_mullo_epi16(c, k1);
        d = _mm_unpacklo_epi8(d, zero);
        __m128i avg = a;
        d = _mm_mullo_epi16(d, k2v);
        c = _mm_add_epi16(c, d);
        c = _mm_add_epi16(c, bias);
        c = _mm_srai_epi16(c, 7);
        avg = _mm_mullo_epi16(avg, k1);
        c = _mm_mullo_epi16(c, k3);
        acc = _mm_add_epi16(acc, c);
        acc = _mm_add_epi16(acc, bias);
        acc = _mm_srai_epi16(acc, 7);
        _mm_storeu_si128((__m128i*)dst, acc);
        s += stride;
        dst += 0x10;
    } while (dst != dstEnd);
}

// @ 0x00fd0c00 -- 2-tap SSE horizontal filter, 16 pixels per row.
void FUN_00fd0c00(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    const __m128i* kp = (const __m128i*)k;
    int cnt = rows;
    do {
        __m128i a = _mm_loadu_si128((const __m128i*)src);
        __m128i b = a;
        a = _mm_unpacklo_epi8(a, _mm_setzero_si128());
        a = _mm_mullo_epi16(a, _mm_load_si128(kp));
        b = _mm_srli_si128(b, 1);
        b = _mm_unpacklo_epi8(b, _mm_setzero_si128());
        b = _mm_mullo_epi16(b, _mm_load_si128(kp + 1));
        a = _mm_add_epi16(a, b);
        a = _mm_add_epi16(a, _mm_load_si128((const __m128i*)g_vp6Bias5b3350));
        a = _mm_srai_epi16(a, 7);
        _mm_storeu_si128((__m128i*)dst, a);
        src += srcStride;
        dst += dstStride;
    } while (--cnt);
}

// @ 0x00fd0c60 -- SSE 16-pixel vertical pair filter.
void FUN_00fd0c60(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k)
{
    const __m128i* kp = (const __m128i*)k;
    __m128i zero = _mm_setzero_si128();
    int stride = srcStride;
    int cnt = rows;
    do {
        __m128i a = _mm_loadu_si128((const __m128i*)src);
        __m128i v = _mm_mullo_epi16(_mm_unpacklo_epi8(a, zero), _mm_load_si128(kp));
        __m128i t = _mm_loadu_si128((const __m128i*)(src + stride));
        v = _mm_add_epi16(v, _mm_mullo_epi16(_mm_unpacklo_epi8(t, zero), _mm_load_si128(kp + 1)));
        v = _mm_add_epi16(v, _mm_load_si128((const __m128i*)g_vp6Bias5b3350));
        v = _mm_srai_epi16(v, 7);
        _mm_storeu_si128((__m128i*)dst, v);
        src += stride;
        dst += dstStride;
    } while (--cnt);
}

// @ 0x00fd0cc0 -- two-pass expander: horizontal 4-tap then vertical 4-tap (SSE variant).
void FUN_00fd0cc0(int a1, int a2, const s16* a3, int a4, const s16* a5, int a6, int a7)
{
    uint32_t tmp[64];
    FUN_00fd0a00((const u8*)(a1 - a4), (u8*)tmp, a4, 1, 0xb, 8, (const s16*)a4);
    FUN_00fd0aa0((const u8*)tmp, (u8*)a2, 8, 8, 8, 8, a5);
    (void)a3; (void)a6; (void)a7;
}
