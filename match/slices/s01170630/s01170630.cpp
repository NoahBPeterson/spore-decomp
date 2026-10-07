// Slice s01170630: MmxDct32 (0x01170630), the 32-point integer matrixing DCT of the PC MMX build
// (called from the RenderWare audio PolySynth and, identically, from the Snd PolySynth via 0x011689e0).
//
// Input: 32 int16 samples (eight qwords). Output: 17 s16 written to pColumnA (stride 16 s16) and 16 s16 to
// pColumnB (stride 16 s16), i.e. the 32 DCT outputs laid out as a transposed pair of history columns.
//
// Algorithm (even/odd partial butterfly, all lane arithmetic wraps in 16 or 32 bits):
//   s[i] = x[i] + x[31-i], d[i] = x[i] - x[31-i]              (i = 0..15, psubw/paddw)
//   Y[2j]   = (sum_i E[j][i] * s[i]) >> 14                    (E = KS_DctMatrix rows 16..31)
//   Y[2j+1] = (sum_i O[j][i] * d[i]) >> 14                    (O = KS_DctMatrix rows 0..15)
// Each sum is 16 products folded with pmaddwd, then psrad 14, then the low word is stored.
//
// The original does no emms (the caller ends the MMX section) and reads all input before any store.
// Flags: /O2 /MD /Gy /TP /GS- (intrinsic-only MMX; the original has no stack cookie).
#include "types.h"
#include <mmintrin.h>

// 0x015c4638: 512 s16 Q14 DCT coefficients. Rows 0..15 (offset 0x000) are the odd-output matrix O,
// rows 16..31 (offset 0x200, VA 0x015c4838) the even-output matrix E. Each row is 16 s16 (32 bytes).
static const int16_t KS_DctMatrix[512] = {
    16364, 16207, 15893, 15426, 14811, 14053, 13160, 12140, 11003, 9760, 8423, 7005, 5520, 3981, 2404, 804,
    16207, 14811, 12140, 8423, 3981, -803, -5519, -9759, -13159, -15425, -16363, -15892, -14052, -11002, -7004, -2403,
    15893, 12140, 5520, -2403, -9759, -14810, -16363, -14052, -8422, -803, 7005, 13160, 16207, 15426, 11003, 3981,
    15426, 8423, -2403, -12139, -16363, -13159, -3980, 7005, 14811, 15893, 9760, -803, -11002, -16206, -14052, -5519,
    14811, 3981, -9759, -16363, -11002, 2404, 14053, 15426, 5520, -8422, -16206, -12139, 804, 13160, 15893, 7005,
    14053, -803, -14810, -13159, 2404, 15426, 12140, -3980, -15892, -11002, 5520, 16207, 9760, -7004, -16363, -8422,
    13160, -5519, -16363, -3980, 14053, 12140, -7004, -16206, -2403, 14811, 11003, -8422, -15892, -803, 15426, 9760,
    12140, -9759, -14052, 7005, 15426, -3980, -16206, 804, 16364, 2404, -15892, -5519, 14811, 8423, -13159, -11002,
    11003, -13159, -8422, 14811, 5520, -15892, -2403, 16364, -803, -16206, 3981, 15426, -7004, -14052, 9760, 12140,
    9760, -15425, -803, 15893, -8422, -11002, 14811, 2404, -16206, 7005, 12140, -14052, -3980, 16364, -5519, -13159,
    8423, -16363, 7005, 9760, -16206, 5520, 11003, -15892, 3981, 12140, -15425, 2404, 13160, -14810, 804, 14053,
    7005, -15892, 13160, -803, -12139, 16207, -8422, -5519, 15426, -14052, 2404, 11003, -16363, 9760, 3981, -14810,
    5520, -14052, 16207, -11002, 804, 9760, -15892, 14811, -7004, -3980, 13160, -16363, 12140, -2403, -8422, 15426,
    3981, -11002, 15426, -16206, 13160, -7004, -803, 8423, -14052, 16364, -14810, 9760, -2403, -5519, 12140, -15892,
    2404, -7004, 11003, -14052, 15893, -16363, 15426, -13159, 9760, -5519, 804, 3981, -8422, 12140, -14810, 16207,
    804, -2403, 3981, -5519, 7005, -8422, 9760, -11002, 12140, -13159, 14053, -14810, 15426, -15892, 16207, -16363,
    16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384,
    16305, 15679, 14449, 12665, 10394, 7723, 4756, 1606, -1605, -4755, -7722, -10393, -12664, -14448, -15678, -16304,
    16069, 13623, 9102, 3196, -3195, -9101, -13622, -16068, -16068, -13622, -9101, -3195, 3196, 9102, 13623, 16069,
    15679, 10394, 1606, -7722, -14448, -16304, -12664, -4755, 4756, 12665, 16305, 14449, 7723, -1605, -10393, -15678,
    15137, 6270, -6269, -15136, -15136, -6269, 6270, 15137, 15137, 6270, -6269, -15136, -15136, -6269, 6270, 15137,
    14449, 1606, -12664, -15678, -4755, 10394, 16305, 7723, -7722, -16304, -10393, 4756, 15679, 12665, -1605, -14448,
    13623, -3195, -16068, -9101, 9102, 16069, 3196, -13622, -13622, 3196, 16069, 9102, -9101, -16068, -3195, 13623,
    12665, -7722, -15678, 1606, 16305, 4756, -14448, -10393, 10394, 14449, -4755, -16304, -1605, 15679, 7723, -12664,
    11585, -11584, -11584, 11585, 11585, -11584, -11584, 11585, 11585, -11584, -11584, 11585, 11585, -11584, -11584, 11585,
    10394, -14448, -4755, 16305, -1605, -15678, 7723, 12665, -12664, -7722, 15679, 1606, -16304, 4756, 14449, -10393,
    9102, -16068, 3196, 13623, -13622, -3195, 16069, -9101, -9101, 16069, -3195, -13622, 13623, 3196, -16068, 9102,
    7723, -16304, 10394, 4756, -15678, 12665, 1606, -14448, 14449, -1605, -12664, 15679, -4755, -10393, 16305, -7722,
    6270, -15136, 15137, -6269, -6269, 15137, -15136, 6270, 6270, -15136, 15137, -6269, -6269, 15137, -15136, 6270,
    4756, -12664, 16305, -14448, 7723, 1606, -10393, 15679, -15678, 10394, -1605, -7722, 14449, -16304, 12665, -4755,
    3196, -9101, 13623, -16068, 16069, -13622, 9102, -3195, -3195, 9102, -13622, 16069, -16068, 13623, -9101, 3196,
    1606, -4755, 7723, -10393, 12665, -14448, 15679, -16304, 16305, -15678, 14449, -12664, 10394, -7722, 4756, -1605
};

// Word-reverse one qword: [w0,w1,w2,w3] -> [w3,w2,w1,w0], with the original's punpck/psrlq sequence.
static __forceinline __m64 ReverseWords(__m64 q)
{
    const __m64 hi = _mm_srli_si64(_mm_unpackhi_pi32(q, q), 16); // [w3,w2,w3,0]
    const __m64 lo = _mm_srli_si64(_mm_unpacklo_pi32(q, q), 16); // [w1,w0,w1,0]
    return _mm_unpacklo_pi32(hi, lo);                             // [w3,w2,w1,w0]
}

// One output sample: 16 products (four pmaddwd taps against the four qwords of s), folded to one dword,
// arithmetic >> 14, low word. Returns the s16 that the original stores with mov word ptr.
static __forceinline int16_t DctTap(const __m64* row, const __m64* s)
{
    __m64 t = _mm_add_pi32(_mm_madd_pi16(row[0], s[0]), _mm_madd_pi16(row[1], s[1]));
    t = _mm_add_pi32(t, _mm_madd_pi16(row[2], s[2]));
    t = _mm_add_pi32(t, _mm_madd_pi16(row[3], s[3]));
    t = _mm_add_pi32(t, _mm_srli_si64(t, 32));
    t = _mm_srai_pi32(t, 14);
    return (int16_t)_mm_cvtsi64_si32(t);
}

// 0x01170630. cdecl, three stack arguments; no return value, no emms.
// pColumnA receives Y[0..16] at stride -16 s16 (Y[n] at pColumnA[256 - 16n]), pColumnB receives Y[16..31]
// at stride 16 s16 (Y[n] at pColumnB[16 * (n - 16)]); Y[16] goes to both.
void MmxDct32(int16_t* pColumnA, int16_t* pColumnB, const int16_t* pIn)
{
    const __m64* const x = (const __m64*)pIn;
    const __m64* const mat = (const __m64*)KS_DctMatrix;

    // Butterfly: x[i] +/- x[31-i], with x[31-i] taken from the reversed qwords 7..4.
    const __m64 r7 = ReverseWords(x[7]); // [x31,x30,x29,x28]
    const __m64 r6 = ReverseWords(x[6]); // [x27,x26,x25,x24]
    const __m64 r5 = ReverseWords(x[5]); // [x23,x22,x21,x20]
    const __m64 r4 = ReverseWords(x[4]); // [x19,x18,x17,x16]

    const __m64 sv[4] = {
        _mm_add_pi16(x[0], r7), _mm_add_pi16(x[1], r6), _mm_add_pi16(x[2], r5), _mm_add_pi16(x[3], r4),
    };
    const __m64 dv[4] = {
        _mm_sub_pi16(x[0], r7), _mm_sub_pi16(x[1], r6), _mm_sub_pi16(x[2], r5), _mm_sub_pi16(x[3], r4),
    };

    // Even outputs Y[2j] from the sums, with the even matrix (rows 16..31 = qwords 64..127).
    int16_t y;
    y = DctTap(mat + 64, sv); pColumnA[256] = y;
    y = DctTap(mat + 68, sv); pColumnA[224] = y;
    y = DctTap(mat + 72, sv); pColumnA[192] = y;
    y = DctTap(mat + 76, sv); pColumnA[160] = y;
    y = DctTap(mat + 80, sv); pColumnA[128] = y;
    y = DctTap(mat + 84, sv); pColumnA[96] = y;
    y = DctTap(mat + 88, sv); pColumnA[64] = y;
    y = DctTap(mat + 92, sv); pColumnA[32] = y;
    y = DctTap(mat + 96, sv); pColumnA[0] = y; pColumnB[0] = y;
    y = DctTap(mat + 100, sv); pColumnB[32] = y;
    y = DctTap(mat + 104, sv); pColumnB[64] = y;
    y = DctTap(mat + 108, sv); pColumnB[96] = y;
    y = DctTap(mat + 112, sv); pColumnB[128] = y;
    y = DctTap(mat + 116, sv); pColumnB[160] = y;
    y = DctTap(mat + 120, sv); pColumnB[192] = y;
    y = DctTap(mat + 124, sv); pColumnB[224] = y;

    // Odd outputs Y[2k+1] from the differences, with the odd matrix (rows 0..15 = qwords 0..63).
    y = DctTap(mat + 0, dv);  pColumnA[240] = y;
    y = DctTap(mat + 4, dv);  pColumnA[208] = y;
    y = DctTap(mat + 8, dv);  pColumnA[176] = y;
    y = DctTap(mat + 12, dv); pColumnA[144] = y;
    y = DctTap(mat + 16, dv); pColumnA[112] = y;
    y = DctTap(mat + 20, dv); pColumnA[80] = y;
    y = DctTap(mat + 24, dv); pColumnA[48] = y;
    y = DctTap(mat + 28, dv); pColumnA[16] = y;
    y = DctTap(mat + 32, dv); pColumnB[16] = y;
    y = DctTap(mat + 36, dv); pColumnB[48] = y;
    y = DctTap(mat + 40, dv); pColumnB[80] = y;
    y = DctTap(mat + 44, dv); pColumnB[112] = y;
    y = DctTap(mat + 48, dv); pColumnB[144] = y;
    y = DctTap(mat + 52, dv); pColumnB[176] = y;
    y = DctTap(mat + 56, dv); pColumnB[208] = y;
    y = DctTap(mat + 60, dv); pColumnB[240] = y;
}
