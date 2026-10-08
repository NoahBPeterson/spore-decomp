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
#include <mmintrin.h>

extern __m64 gIdctTable[];          // 0x016d91a0 (name guessed); entries 4..11 used

#define K(i) gIdctTable[i]

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
void __cdecl Idct8x8(const short* in, const short* quant, short* out)
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
}
