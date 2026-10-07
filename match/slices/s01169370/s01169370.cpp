// Slice s01169370: Snd::CMpegBase::PolySynth (EATech MPEG audio decoder, PC MMX build).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// One poly-phase synthesis stage of the MPEG layer-3 decoder: rotate the channel's
// history phase, run the 32-point matrixing DCT into the two history columns the new
// phase selects, then window 32 samples out of the bank the odd column landed in.
// Names follow the BurnoutDecomp reconstruction of the X360 float version
// (work/ext/gh_b5/src/SDKs/EATech/include/snd/CMpegBase_wO_01.cpp). The PC build keeps
// the history as int16 (576 shorts = 0x480 bytes per channel) and does the windowing
// with MMX (pmaddwd over a pre-negated int16 window, >> 13, saturated to int16).
//
// The original windowing is a hand-scheduled inline __asm block. It is written here with
// the equivalent MMX intrinsics (same operations, same rounding/saturation), so the
// function is behaviorally complete but not byte-exact.
#include "types.h"
#include <mmintrin.h>

namespace Snd {

// 0x014d8e90: int16 synthesis window, rows of 32 shorts (pre-negated for pmaddwd).
// Rows 0..14 (from 0x014d8e90) serve the mirrored half, rows 16..32 (from 0x014d9290)
// the first half and the centre sample.
extern const short KS_SynthWindowMMX[]; // 0x014d8e90

// 0x011689e0: 32-point matrixing DCT writing one column into each history bank.
void Dct32(short* apColumnA, short* apColumnB, const float* apInSamples); // 0x011689e0

class CMpegBase
{
public:
    void PolySynth(int aiChannel, float* apOutSamples, const float* apInSamples);

    uint32_t pad00[0x38 / 4];
    uint8_t  mucSynthPhase[2];      // +0x38 (mucSynthPhase0 / mucSynthPhase1)
    uint8_t  pad3a[0x50 - 0x3a];
    short*   mpPolySynthHistory;    // +0x50
};

// Sum of 16 int16 products (4 x pmaddwd), folded to one dword, >> 13, saturated.
static __forceinline short WindowTaps(const __m64* w, const __m64* b)
{
    __m64 s = _mm_madd_pi16(w[0], b[0]);
    s = _mm_add_pi32(s, _mm_madd_pi16(w[1], b[1]));
    s = _mm_add_pi32(s, _mm_madd_pi16(w[2], b[2]));
    s = _mm_add_pi32(s, _mm_madd_pi16(w[3], b[3]));
    s = _mm_add_pi32(s, _mm_srli_si64(s, 32));
    s = _mm_srai_pi32(s, 13);
    s = _mm_packs_pi32(s, s);
    return (short)_mm_cvtsi64_si32(s);
}

// Centre sample: only the even taps (high word of each product, placed in the high
// half of its dword by pslld 16; the odd taps are shifted out).
static __forceinline short WindowCentre(const __m64* w, const __m64* b)
{
    __m64 s = _mm_slli_pi32(_mm_mulhi_pi16(w[0], b[0]), 16);
    s = _mm_add_pi32(s, _mm_slli_pi32(_mm_mulhi_pi16(w[1], b[1]), 16));
    s = _mm_add_pi32(s, _mm_slli_pi32(_mm_mulhi_pi16(w[2], b[2]), 16));
    s = _mm_add_pi32(s, _mm_slli_pi32(_mm_mulhi_pi16(w[3], b[3]), 16));
    s = _mm_add_pi32(s, _mm_srli_si64(s, 32));
    s = _mm_srai_pi32(s, 13);
    s = _mm_packs_pi32(s, s);
    return (short)_mm_cvtsi64_si32(s);
}

#define TAP(o, wr, br) lasOut[o] = WindowTaps((const __m64*)(lpWindow + 32 * (wr)), (const __m64*)(lpBank + 16 * (br)))
#define TAPR(o, wr, br) lasOut[o] = WindowTaps((const __m64*)(lpWindowRev + 32 * (wr)), (const __m64*)(lpBank + 16 * (br)))

// @ 0x01169370
void CMpegBase::PolySynth(int aiChannel, float* apOutSamples, const float* apInSamples)
{
    short lasOut[32];

    const unsigned liPhase = (uint8_t)(mucSynthPhase[aiChannel] - 1) & 0xf;
    mucSynthPhase[aiChannel] = (uint8_t)liPhase;

    const unsigned liOdd = liPhase & 1;
    const int liOddColumn = liPhase + (liOdd ^ 1);

    short* const lpHistory = mpPolySynthHistory + 576 * aiChannel;
    short* const lpBank = lpHistory + 288 * (liOdd ^ 1);

    Dct32(lpHistory + 288 * liOdd + ((liPhase + liOdd) & 0xf), lpBank + liOddColumn, apInSamples);

    // out[0..15]: window rows 16..31, bank rows 0..15; out[16]: centre (row 32 / bank 16).
    const short* const lpWindow = KS_SynthWindowMMX + 512 - liOddColumn;
    TAP(0, 0, 0);   TAP(1, 1, 1);   TAP(2, 2, 2);   TAP(3, 3, 3);
    TAP(4, 4, 4);   TAP(5, 5, 5);   TAP(6, 6, 6);   TAP(7, 7, 7);
    TAP(8, 8, 8);   TAP(9, 9, 9);   TAP(10, 10, 10); TAP(11, 11, 11);
    TAP(12, 12, 12); TAP(13, 13, 13); TAP(14, 14, 14); TAP(15, 15, 15);
    lasOut[16] = WindowCentre((const __m64*)(lpWindow + 32 * 16), (const __m64*)(lpBank + 16 * 16));

    // out[17..31]: the mirrored half, window rows 0..14 against bank rows 15..1.
    const short* const lpWindowRev = KS_SynthWindowMMX - liOddColumn;
    TAPR(17, 0, 15); TAPR(18, 1, 14); TAPR(19, 2, 13); TAPR(20, 3, 12);
    TAPR(21, 4, 11); TAPR(22, 5, 10); TAPR(23, 6, 9);  TAPR(24, 7, 8);
    TAPR(25, 8, 7);  TAPR(26, 9, 6);  TAPR(27, 10, 5); TAPR(28, 11, 4);
    TAPR(29, 12, 3); TAPR(30, 13, 2); TAPR(31, 14, 1);
    _mm_empty();

    for (int i = 0; i < 32; ++i)
        apOutSamples[i] = (float)lasOut[i];
}

#undef TAP
#undef TAPR

} // namespace Snd
