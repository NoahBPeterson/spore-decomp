// Slice s00fd0d20: 0x00FD0F10, 8x8 inverse DCT on 16-bit words, MMX fixed-point (AP-922 style).
// Flags: /O2 /MD /Gy /TP (the original is hand-written MMX assembly, so the flags do not matter).
//
// void __cdecl Idct8x8(const short* in, const short* quant, short* out):
//   1. out[i] = in[i] * quant[i] (low 16 bits) for the 64 coefficients.
//   2. Column pass (8-point 1-D IDCT, saturating 16-bit arithmetic, pmulhw by the constant table
//      at 0x016d91a0) on two 4-word-wide halves of `out`; each result is transposed in 4x4 word
//      blocks (punpck) on the way back to memory.
//   3. Row pass: the same 1-D IDCT on the transposed data with the rounding constant (table
//      entry 0x58) added to the difference terms, then an arithmetic shift right by 4.
// The original reads six words of `out` first (cache touch) and returns without EMMS (the caller
// executes it).
//
// NAMING NOTE: no symbol is known for 0x00FD0F10. The table is filled at run time (it lives in
// .bss); its layout is taken from the uses: qword entries 4..10 are the pmulhw constants, 11 is the
// rounding term. Names are Claude-coined.
#include "types.h"
#include <string.h>
#include <crtdefs.h>
#undef _CRT_ALIGN
#define _CRT_ALIGN(x)
#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma function(memset)

#define G_IDCT_TABLE ((__m64*)0x016d91a0)  // runtime IDCT constants; entries 4..11 used

#define K(i) G_IDCT_TABLE[i]

// One 8-point 1-D IDCT over eight 4-word vectors. kFinal adds the rounding constant and shifts the
// results right by 4 (second pass); otherwise the results are raw (first pass).
template <bool kFinal>
static __forceinline void Idct1D(const __m64& x0, const __m64& x1, const __m64& x2, const __m64& x3,
                                 const __m64& x4, const __m64& x5, const __m64& x6, const __m64& x7,
                                 __m64* y)
{
    // odd part
    __m64 a6 = _mm_add_pi16(_mm_mulhi_pi16(x6, K(6)), x6);
    __m64 a3 = _mm_add_pi16(_mm_mulhi_pi16(K(6), x3), x3);
    __m64 b6 = _mm_add_pi16(x6, _mm_mulhi_pi16(K(8), x6));
    __m64 b3 = _mm_add_pi16(x3, _mm_mulhi_pi16(K(8), x3));
    __m64 s10 = _mm_adds_pi16(a6, b3);
    __m64 s12 = _mm_subs_pi16(a3, b6);

    __m64 a2 = _mm_add_pi16(_mm_mulhi_pi16(K(4), x2), x2);
    __m64 a7 = _mm_add_pi16(_mm_mulhi_pi16(K(4), x7), x7);
    __m64 m2 = _mm_mulhi_pi16(x2, K(10));
    __m64 m7 = _mm_mulhi_pi16(K(10), x7);
    __m64 s18 = _mm_subs_pi16(m2, a7);
    __m64 s19 = _mm_adds_pi16(a2, m7);
    __m64 s20 = _mm_subs_pi16(s19, s10);

    __m64 a4 = _mm_add_pi16(_mm_mulhi_pi16(x4, K(5)), x4);
    __m64 a5 = _mm_add_pi16(_mm_mulhi_pi16(x5, K(5)), x5);
    __m64 m4 = _mm_mulhi_pi16(x4, K(9));
    __m64 m5 = _mm_mulhi_pi16(x5, K(9));
    __m64 s31 = _mm_subs_pi16(m4, a5);
    __m64 s33 = _mm_adds_pi16(m5, a4);

    __m64 s25 = _mm_adds_pi16(_mm_adds_pi16(s10, s10), s20);
    __m64 s26 = _mm_subs_pi16(s18, s12);
    __m64 s30 = _mm_adds_pi16(_mm_adds_pi16(s12, s12), s26);
    __m64 a26 = _mm_add_pi16(s26, _mm_mulhi_pi16(s26, K(7)));
    __m64 s36 = _mm_subs_pi16(a26, s31);
    __m64 a20 = _mm_add_pi16(s20, _mm_mulhi_pi16(s20, K(7)));

    // even part
    __m64 s38 = _mm_subs_pi16(x0, x1);
    __m64 m38 = _mm_mulhi_pi16(s38, K(7));
    __m64 s42 = _mm_adds_pi16(_mm_adds_pi16(x1, x1), s38);
    __m64 s43 = _mm_adds_pi16(_mm_adds_pi16(s31, s31), s36);
    __m64 s45 = _mm_adds_pi16(m38, s38);
    __m64 s46 = _mm_subs_pi16(s45, a20);
    __m64 s48 = _mm_adds_pi16(_mm_adds_pi16(a20, a20), s46);
    __m64 a42 = _mm_add_pi16(_mm_mulhi_pi16(K(7), s42), s42);

    // butterflies (difference d = a - b, sum s = 2 * b + d)
    __m64 d50 = _mm_subs_pi16(s48, s43);
    __m64 d51 = _mm_subs_pi16(a42, s33);
    __m64 sum55 = _mm_adds_pi16(_mm_adds_pi16(s33, s33), d51);
    __m64 d56 = _mm_subs_pi16(d51, s30);
    __m64 d58 = _mm_subs_pi16(s46, s36);
    __m64 d62 = _mm_subs_pi16(sum55, s25);
    if (kFinal) {
        d50 = _mm_adds_pi16(d50, K(11));
        d56 = _mm_adds_pi16(d56, K(11));
        d58 = _mm_adds_pi16(d58, K(11));
        d62 = _mm_adds_pi16(d62, K(11));
    }
    __m64 sum54 = _mm_adds_pi16(_mm_adds_pi16(s43, s43), d50);
    __m64 sum60 = _mm_adds_pi16(_mm_adds_pi16(s30, s30), d56);
    __m64 sum61 = _mm_adds_pi16(_mm_adds_pi16(s36, s36), d58);
    __m64 sum64 = _mm_adds_pi16(_mm_adds_pi16(s25, s25), d62);
    if (kFinal) {
        d50 = _mm_srai_pi16(d50, 4);
        sum54 = _mm_srai_pi16(sum54, 4);
        d56 = _mm_srai_pi16(d56, 4);
        sum60 = _mm_srai_pi16(sum60, 4);
        d58 = _mm_srai_pi16(d58, 4);
        sum61 = _mm_srai_pi16(sum61, 4);
        d62 = _mm_srai_pi16(d62, 4);
        sum64 = _mm_srai_pi16(sum64, 4);
    }
    y[0] = sum64;
    y[1] = d56;
    y[2] = sum54;
    y[3] = sum61;
    y[4] = d50;
    y[5] = d58;
    y[6] = sum60;
    y[7] = d62;
}

// Column pass over eight qwords p[0..7]; the results are transposed in two 4x4 word blocks.
static __forceinline void ColumnPass(__m64* p)
{
    __m64 y[8];
    Idct1D<false>(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], y);

    __m64 lo13 = _mm_unpacklo_pi16(y[1], y[3]);
    __m64 hi13 = _mm_unpackhi_pi16(y[1], y[3]);
    __m64 lo57 = _mm_unpacklo_pi16(y[5], y[7]);
    __m64 hi57 = _mm_unpackhi_pi16(y[5], y[7]);
    p[1] = _mm_unpacklo_pi32(lo13, lo57);
    p[3] = _mm_unpackhi_pi32(lo13, lo57);
    p[7] = _mm_unpackhi_pi32(hi13, hi57);
    p[5] = _mm_unpacklo_pi32(hi13, hi57);

    __m64 lo02 = _mm_unpacklo_pi16(y[0], y[2]);
    __m64 hi02 = _mm_unpackhi_pi16(y[0], y[2]);
    __m64 lo46 = _mm_unpacklo_pi16(y[4], y[6]);
    __m64 hi46 = _mm_unpackhi_pi16(y[4], y[6]);
    p[0] = _mm_unpacklo_pi32(lo02, lo46);
    p[2] = _mm_unpackhi_pi32(lo02, lo46);
    p[6] = _mm_unpackhi_pi32(hi02, hi46);
    p[4] = _mm_unpacklo_pi32(hi02, hi46);
}

// Row pass over the eight qwords at p[0], p[8], p[2], p[10], p[4], p[12], p[6], p[14] (qword units
// of 8 bytes: 0x00, 0x40, 0x10, 0x50, 0x20, 0x60, 0x30, 0x70); results go back to the same places.
static __forceinline void RowPass(__m64* p)
{
    __m64 y[8];
    Idct1D<true>(p[0], p[8], p[2], p[10], p[4], p[12], p[6], p[14], y);
    p[0] = y[0];
    p[8] = y[1];
    p[2] = y[2];
    p[10] = y[3];
    p[4] = y[4];
    p[12] = y[5];
    p[6] = y[6];
    p[14] = y[7];
}

// @ 0x00fd0f10
// The original is hand-written MMX: it loads `in` into eax at entry and never overwrites it, so
// eax holds `in` at the ret.  Declare the result so cl keeps the pointer live and returns it.
const short* __cdecl Idct8x8(const short* in, const short* quant, short* out)
{
    // cache touch of the output block (no other effect)
    volatile int touch;
    touch = ((volatile int*)out)[0];
    touch = ((volatile int*)out)[7];
    touch = ((volatile int*)out)[14];
    touch = ((volatile int*)out)[21];
    touch = ((volatile int*)out)[28];
    touch = ((volatile int*)out)[31];

    const __m64* src = (const __m64*)in;
    const __m64* mul = (const __m64*)quant;
    __m64* dst = (__m64*)out;
    for (int i = 0; i < 16; i++)
        dst[i] = _mm_mullo_pi16(src[i], mul[i]);

    for (int half = 0; half < 2; half++)
        ColumnPass(dst + 8 * half);
    for (int col = 0; col < 2; col++)
        RowPass((__m64*)((char*)dst + 8 * col));
    return in;
}

// ---------------------------------------------------------------------------
// The remaining functions in this slice are the MMX/SSE2 VP6 kernels selected by
// vp6_setup_tables (0x00fd1c60), plus the CPU-feature query and their global tables.
// ---------------------------------------------------------------------------
#define G_IDCT_WORDS ((short*)0x016d91a0)                 // word view of the IDCT table
#define G_IDCT_SOURCE ((const short*)0x015b3660)          // source words for the table
#define G_VP6_DITHER (*(__m64*)0x015b3680)                // 8-byte dither mask
#define G_VP6_TILE_PACKED ((unsigned char*)0x015b3460)    // 0x40-byte packed tiles
#define G_VP6_TILE_UNPACKED ((unsigned char*)0x015b3360)  // 0x20-byte unpacked tiles
extern int gVp6IndexTable[0x40];        // 0x015b3788
extern int gVp6TableA[];                // 0x015b3888
extern int gVp6TableB[];                // 0x015b3988

int WillametteNewInstructionHWSupport(void);

// Row-blit helpers in the packed (0x40-byte) / unpacked (0x20-byte) tile tables.
void FUN_00fd0a00(int, unsigned char*, int, int, int, int, const unsigned char*);
void FUN_00fd0aa0(int, unsigned char*, int, int, int, int, const unsigned char*);
void FUN_00fd0cc0(int, unsigned char*, int, const unsigned char*, const unsigned char*);
void FUN_00fd0c00(int, unsigned char*, int, int, int, int, const unsigned char*);
void FUN_00fd0c60(int, unsigned char*, int, int, int, int, const unsigned char*);
void FUN_00fd0b40(int, unsigned char*, int, const unsigned char*, const unsigned char*);

// @ 0x00fd0d20
// Seven-argument cdecl: (a, b, out[8][16], n, tileA, tileB, packed).  The original
// builds an 8x8 tile slice in a 256-byte stack buffer, then either writes it packed
// (8 bytes per row, expanded here to 16 bytes with zero interleaving) or already
// unpacked (16 bytes per row).
void __cdecl FUN_00fd0d20(int a, int b, unsigned char (*out)[16], int n, int tileA,
                          int tileB, int packed)
{
    unsigned char tmp[0x100];
    int len = b - a;
    if (len < 0) {
        len = a - b;
        a = b;
    }
    if (len == 0)
        return;

    if (packed) {
        if (len == 1) {
            FUN_00fd0a00(a, tmp, n, 1, 8, 8, G_VP6_TILE_PACKED + tileA * 0x40);
        } else if (len == n) {
            FUN_00fd0aa0(a, tmp, n, n, 8, 8, G_VP6_TILE_PACKED + tileB * 0x40);
        } else {
            if (len == n - 1)
                --a;
            else if (len != n + 1)
                goto unpack;
            FUN_00fd0cc0(a, tmp, n, G_VP6_TILE_PACKED + tileA * 0x40,
                         G_VP6_TILE_PACKED + tileB * 0x40);
        }
unpack:
        {
            __m128i zero = _mm_setzero_si128();
            for (int i = 0; i < 8; i++) {
                __m128i v = _mm_loadu_si128((const __m128i*)(tmp + i * 8));
                v = _mm_unpacklo_epi8(v, zero);
                _mm_storeu_si128((__m128i*)out[i], v);
            }
        }
        return;
    }

    if (len == 1) {
        FUN_00fd0c00(a, (unsigned char*)out, n, 1, 8, 0x10,
                     G_VP6_TILE_UNPACKED + tileA * 0x20);
        return;
    }
    if (len == n) {
        FUN_00fd0c60(a, (unsigned char*)out, n, n, 8, 0x10,
                     G_VP6_TILE_UNPACKED + tileB * 0x20);
        return;
    }
    if (len == n - 1)
        --a;
    else if (len != n + 1)
        return;
    FUN_00fd0b40(a, (unsigned char*)out, n, G_VP6_TILE_UNPACKED + tileA * 0x20,
                 G_VP6_TILE_UNPACKED + tileB * 0x20);
}

// @ 0x00fd0eb0
// DC-only prediction fill.  The source word pair gives one 16-bit DC value, which
// is broadcast into all 32 dwords of the block; a zero coefficient clears it.
void __cdecl FUN_00fd0eb0(short* a, short* b, unsigned* out)
{
    unsigned short ua = *(unsigned short*)a;
    if (ua != 0) {
        int v = (((int)*b * (short)ua + 15) >> 5 & 0xffff) * 0x10001;
        for (int i = 0; i < 8; i++) {
            out[0] = v;
            out[1] = v;
            out[2] = v;
            out[3] = v;
            out += 4;
        }
    } else {
        memset(out, 0, 0x80);
    }
}

// Sparse column pass for the 4-tap path: only x0,x2,x4,x6 are non-zero, so the
// compiler can fold the odd inputs away.  The result is transposed exactly like
// ColumnPass above.
static __forceinline void ColumnPassSparse(__m64* p)
{
    __m64 zero = _mm_setzero_si64();
    __m64 y[8];
    Idct1D<false>(p[0], zero, p[2], zero, p[4], zero, p[6], zero, y);

    __m64 lo13 = _mm_unpacklo_pi16(y[1], y[3]);
    __m64 hi13 = _mm_unpackhi_pi16(y[1], y[3]);
    __m64 lo57 = _mm_unpacklo_pi16(y[5], y[7]);
    __m64 hi57 = _mm_unpackhi_pi16(y[5], y[7]);
    p[1] = _mm_unpacklo_pi32(lo13, lo57);
    p[3] = _mm_unpackhi_pi32(lo13, lo57);
    p[7] = _mm_unpackhi_pi32(hi13, hi57);
    p[5] = _mm_unpacklo_pi32(hi13, hi57);

    __m64 lo02 = _mm_unpacklo_pi16(y[0], y[2]);
    __m64 hi02 = _mm_unpackhi_pi16(y[0], y[2]);
    __m64 lo46 = _mm_unpacklo_pi16(y[4], y[6]);
    __m64 hi46 = _mm_unpackhi_pi16(y[4], y[6]);
    p[0] = _mm_unpacklo_pi32(lo02, lo46);
    p[2] = _mm_unpackhi_pi32(lo02, lo46);
    p[6] = _mm_unpackhi_pi32(hi02, hi46);
    p[4] = _mm_unpacklo_pi32(hi02, hi46);
}

// Sparse row pass: the odd-index inputs are zero after the sparse column pass, so
// only the even ones are read.  `odd` selects the low or high qword of each pair.
static __forceinline void RowPassSparse(__m64* p, int odd)
{
    __m64 zero = _mm_setzero_si64();
    __m64 y[8];
    Idct1D<true>(p[odd], zero, p[odd + 2], zero, p[odd + 4], zero,
                 p[odd + 6], zero, y);
    p[odd] = y[0];
    p[odd + 8] = y[1];
    p[odd + 2] = y[2];
    p[odd + 10] = y[3];
    p[odd + 4] = y[4];
    p[odd + 12] = y[5];
    p[odd + 6] = y[6];
    p[odd + 14] = y[7];
}

// @ 0x00fd1610
// The 4-tap MMX filter: dequantise the four non-zero coefficient rows, run the
// sparse column pass once, then the two sparse row passes over the low/high qword
// of each output pair.  eax still holds `in` at the original ret, as in Idct8x8.
const short* __cdecl FUN_00fd1610(const short* in, const short* quant, short* out)
{
    volatile int touch;
    touch = ((volatile int*)out)[0];
    touch = ((volatile int*)out)[7];
    touch = ((volatile int*)out)[14];
    touch = ((volatile int*)out)[21];
    touch = ((volatile int*)out)[28];
    touch = ((volatile int*)out)[31];

    const __m64* src = (const __m64*)in;
    const __m64* mul = (const __m64*)quant;
    __m64* dst = (__m64*)out;
    __m64 zero = _mm_setzero_si64();
    for (int i = 0; i < 4; i++) {
        dst[2 * i] = _mm_mullo_pi16(src[2 * i], mul[2 * i]);
        dst[2 * i + 1] = zero;
    }
    for (int i = 8; i < 16; i++)
        dst[i] = zero;

    ColumnPassSparse(dst);
    RowPassSparse(dst, 0);
    RowPassSparse(dst, 1);
    return in;
}

// @ 0x00fd1a20
// Expand an 8x8 byte block: pack eight 16-bit samples per row to bytes, XOR the
// dither mask, and write each row with the caller's stride.
void __cdecl FUN_00fd1a20(int unused, unsigned char* out, const unsigned char* in, int stride)
{
    __m64 mask = G_VP6_DITHER;
    mask = _mm_or_si64(mask, mask);
    const unsigned char* end = in + 0x80;
    do {
        __m64 v = _mm_packs_pi16(*(const __m64*)in, *(const __m64*)(in + 8));
        v = _mm_xor_si64(v, mask);
        *(__m64*)out = v;
        in += 0x10;
        out += stride;
    } while (in < end);
}

// @ 0x00fd1a60
// Add a 16-bit prediction block to an 8-bit-residual block with unsigned
// saturation: unpack the residual bytes to words, add, pack back to bytes.
unsigned char* __cdecl FUN_00fd1a60(int unused, unsigned char* out, const unsigned char* in,
                                    const short* add, int stride)
{
    __m64 zero = _mm_setzero_si64();
    const short* end = add + 0x40;
    do {
        __m64 v = *(__m64*)in;
        __m64 lo = _mm_unpacklo_pi8(v, zero);
        __m64 hi = _mm_unpackhi_pi8(v, zero);
        lo = _mm_adds_pi16(lo, *(__m64*)add);
        hi = _mm_adds_pi16(hi, *(__m64*)(add + 4));
        *(__m64*)out = _mm_packs_pu16(lo, hi);
        in += stride;
        out += stride;
        add += 8;
    } while (add < end);
    return out;
}

// Object whose +0x0c field points at an edge table and whose +0x10 bytes are
// filled by the two initialisers below.
struct Vp6EdgeTable {
    char mPad00[0xc];
    int* mpTable;                // +0x0c
    unsigned char mEdges[0x40];  // +0x10
};

// @ 0x00fd1ab0
void __cdecl FUN_00fd1ab0(Vp6EdgeTable* p)
{
    p->mpTable = gVp6TableA;
    for (int i = 0; i < 0x40; i++)
        p->mEdges[gVp6TableA[gVp6IndexTable[i]]] = (unsigned char)i;
}

// @ 0x00fd1ae0
void __cdecl FUN_00fd1ae0(Vp6EdgeTable* p)
{
    p->mpTable = gVp6TableB;
    for (int i = 0; i < 0x40; i++)
        p->mEdges[gVp6TableB[gVp6IndexTable[i]]] = (unsigned char)i;
}

// @ 0x00fd1b10
// Fill the runtime IDCT table: four 0xffff sentinels, seven coefficient words
// replicated four times each, and the final rounding vector 8.
void __cdecl FUN_00fd1b10(void)
{
    short* p = G_IDCT_WORDS + 0x10;   // 0x016d91c0
    do {
        p -= 1;
        *p = 0;
    } while (p != G_IDCT_WORDS);

    short ffff = -1;
    G_IDCT_WORDS[0x0f] = ffff;   // 0x016d91be
    G_IDCT_WORDS[0x0a] = ffff;   // 0x016d91b4
    G_IDCT_WORDS[0x00] = ffff;   // 0x016d91a0
    G_IDCT_WORDS[0x05] = ffff;   // 0x016d91aa

    short* dst = G_IDCT_WORDS + 0x12;   // 0x016d91c4
    const short* src = G_IDCT_SOURCE;
    short* end = G_IDCT_WORDS + 0x2a;   // 0x016d91f4
    do {
        short w = *src++;
        dst[1] = w;
        dst[0] = w;
        dst[-1] = w;
        dst[-2] = w;
        dst += 4;
    } while (dst <= end);

    short eight = 8;
    G_IDCT_WORDS[0x2f] = eight;   // 0x016d91fe
    G_IDCT_WORDS[0x2e] = eight;   // 0x016d91fc
    G_IDCT_WORDS[0x2d] = eight;   // 0x016d91fa
    G_IDCT_WORDS[0x2c] = eight;   // 0x016d91f8
}

// @ 0x00fd1ba0
// Map the CPU feature level to the three capability flags consumed by
// vp6_setup_tables: (MMX, 3DNow!, SSE2).
void __cdecl FUN_00fd1ba0(int* a, int* b, int* c)
{
    int level = 1;
    if (WillametteNewInstructionHWSupport())
        level = 12;
    switch (level) {
    case 1:
    case 3:
    case 6:
    case 7:
        *a = 1;
        *b = 0;
        *c = 0;
        break;
    case 11:
        *a = 1;
        *b = 1;
        *c = 0;
        break;
    case 12:
        *a = 1;
        *b = 1;
        *c = 1;
        break;
    default:
        *a = 0;
        *b = 0;
        *c = 0;
        break;
    }
}
