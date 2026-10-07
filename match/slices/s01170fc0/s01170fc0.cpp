// Slice s01170fc0: rw::audio::core::CMpegBase::PolySynth, PC MMX fixed-point build (RenderWare audio MPEG decoder).
//
// The MPEG audio poly-phase synthesis step: rotate the per-channel history phase, let the 32-point DCT write one
// column of each history bank, then window the bank into 32 PCM samples (16-bit fixed point) and widen them to f32.
// The original's windowing is a hand-scheduled MMX __asm block; it is written here with the MMX intrinsics that
// compute the same lanes (pmaddwd / pmulhw / paddd / psrlq / psrad / packssdw), so it is complete but not
// byte-exact. Member names follow the BurnoutDecomp reconstruction (work/ext/gh_b5 .../CMpegBase.h), whose X360
// float build has the same algorithm with different offsets and element types.
// Flags: /O2 /MD /Gy /TP /arch:SSE (cvtsi2ss/movss for the final int -> f32 conversion).
#include "types.h"
#include <mmintrin.h>

typedef int16_t s16;
typedef int32_t s32;
typedef uint8_t u8;
typedef float f32;

// Poly-phase window in Q13-ish fixed point, rows of 32 s16 (two row sets: bank-forward rows 0..16 start 0x200 s16
// in, bank-reverse rows 1..15 start at the base). Indexed backwards by the odd column, as in the float build.
extern const s16 KAS_PolySynthWindowMmx[];   // 0x014dc348

// The MMX 32-point DCT (0x01170630): writes 17 + 16 s16 into the two history columns.
void MmxDct32(s16* pColumnA, s16* pColumnB, const f32* pInSamples);   // 0x01170630 (cdecl)

namespace rw { namespace audio { namespace core {

class CMpegBase
{
public:
	void PolySynth(s32 iChannel, f32* pOutSamples, const f32* pInSamples);

	u8 mPad00[0x2c];
	u8 mucPolySynthPhase[2];   // +0x2c (per channel)
	u8 mPad2e[0x16];
	s16* mpPolySynthWork;      // +0x44 (per channel: 2 banks x 18 rows x 16 columns of s16)
};

}}}

// sum of the 16 products of one window row and one history row, (>> 13) and saturated to s16
static __forceinline s16 PolySynthTap16(const __m64* pWin, const __m64* pBank)
{
	__m64 a = _m_paddd(_m_paddd(_m_paddd(_m_pmaddwd(pBank[0], pWin[0]), _m_pmaddwd(pWin[1], pBank[1])),
		_m_pmaddwd(pWin[2], pBank[2])), _m_pmaddwd(pWin[3], pBank[3]));
	a = _m_paddd(a, _m_psrlqi(a, 32));
	a = _m_psradi(a, 13);
	a = _m_packssdw(a, a);
	return (s16)_m_to_int(a);
}

// @ 0x01170fc0
void rw::audio::core::CMpegBase::PolySynth(s32 iChannel, f32* pOutSamples, const f32* pInSamples)
{
	u8 uPhase = (u8)((mucPolySynthPhase[iChannel] - 1) & 0xf);
	mucPolySynthPhase[iChannel] = uPhase;
	s32 iPhase = uPhase;
	s32 iOdd = iPhase & 1;
	s32 iEven = iOdd ^ 1;
	s32 iOddColumn = iPhase + iEven;   // always odd, 1 .. 15

	s16* pHistory = mpPolySynthWork + 576 * iChannel;
	s16* pBank = pHistory + 288 * iEven;

	MmxDct32(pHistory + 288 * iOdd + ((iPhase + iOdd) & 0xf), pBank + iOddColumn, pInSamples);

	s16 asSamples[32];
	const __m64* pRow = (const __m64*)pBank;   // 16 s16 = 4 qwords per row

	// out[0 .. 15]: bank rows 0 .. 15 against the forward window rows (32 s16 = 8 qwords per window row)
	const __m64* pWin = (const __m64*)(KAS_PolySynthWindowMmx + 0x200 - iOddColumn);
	asSamples[0] = PolySynthTap16(pWin + 0, pRow + 0);
	asSamples[1] = PolySynthTap16(pWin + 8, pRow + 4);
	asSamples[2] = PolySynthTap16(pWin + 16, pRow + 8);
	asSamples[3] = PolySynthTap16(pWin + 24, pRow + 12);
	asSamples[4] = PolySynthTap16(pWin + 32, pRow + 16);
	asSamples[5] = PolySynthTap16(pWin + 40, pRow + 20);
	asSamples[6] = PolySynthTap16(pWin + 48, pRow + 24);
	asSamples[7] = PolySynthTap16(pWin + 56, pRow + 28);
	asSamples[8] = PolySynthTap16(pWin + 64, pRow + 32);
	asSamples[9] = PolySynthTap16(pWin + 72, pRow + 36);
	asSamples[10] = PolySynthTap16(pWin + 80, pRow + 40);
	asSamples[11] = PolySynthTap16(pWin + 88, pRow + 44);
	asSamples[12] = PolySynthTap16(pWin + 96, pRow + 48);
	asSamples[13] = PolySynthTap16(pWin + 104, pRow + 52);
	asSamples[14] = PolySynthTap16(pWin + 112, pRow + 56);
	asSamples[15] = PolySynthTap16(pWin + 120, pRow + 60);

	// out[16]: the centre sample, bank row 16
	// (the high halves of the even-indexed products only: pmulhw, then << 16 per dword)
	{
		const __m64* w = pWin + 128;
		const __m64* h = pRow + 64;
		__m64 a = _m_paddd(_m_paddd(_m_paddd(_m_pslldi(_m_pmulhw(w[0], h[0]), 16), _m_pslldi(_m_pmulhw(w[1], h[1]), 16)),
			_m_pslldi(_m_pmulhw(w[2], h[2]), 16)), _m_pslldi(_m_pmulhw(w[3], h[3]), 16));
		a = _m_paddd(a, _m_psrlqi(a, 32));
		a = _m_psradi(a, 13);
		a = _m_packssdw(a, a);
		asSamples[16] = (s16)_m_to_int(a);
	}

	// out[17 .. 31]: bank rows 15 .. 1 against the mirrored window rows
	const __m64* pWinRev = (const __m64*)(KAS_PolySynthWindowMmx - iOddColumn);
	asSamples[17] = PolySynthTap16(pWinRev + 0, pRow + 60);
	asSamples[18] = PolySynthTap16(pWinRev + 8, pRow + 56);
	asSamples[19] = PolySynthTap16(pWinRev + 16, pRow + 52);
	asSamples[20] = PolySynthTap16(pWinRev + 24, pRow + 48);
	asSamples[21] = PolySynthTap16(pWinRev + 32, pRow + 44);
	asSamples[22] = PolySynthTap16(pWinRev + 40, pRow + 40);
	asSamples[23] = PolySynthTap16(pWinRev + 48, pRow + 36);
	asSamples[24] = PolySynthTap16(pWinRev + 56, pRow + 32);
	asSamples[25] = PolySynthTap16(pWinRev + 64, pRow + 28);
	asSamples[26] = PolySynthTap16(pWinRev + 72, pRow + 24);
	asSamples[27] = PolySynthTap16(pWinRev + 80, pRow + 20);
	asSamples[28] = PolySynthTap16(pWinRev + 88, pRow + 16);
	asSamples[29] = PolySynthTap16(pWinRev + 96, pRow + 12);
	asSamples[30] = PolySynthTap16(pWinRev + 104, pRow + 8);
	asSamples[31] = PolySynthTap16(pWinRev + 112, pRow + 4);

	_m_empty();

	for (s32 i = 0; i < 32; i += 8)
	{
		pOutSamples[i + 0] = (f32)asSamples[i + 0];
		pOutSamples[i + 1] = (f32)asSamples[i + 1];
		pOutSamples[i + 2] = (f32)asSamples[i + 2];
		pOutSamples[i + 3] = (f32)asSamples[i + 3];
		pOutSamples[i + 4] = (f32)asSamples[i + 4];
		pOutSamples[i + 5] = (f32)asSamples[i + 5];
		pOutSamples[i + 6] = (f32)asSamples[i + 6];
		pOutSamples[i + 7] = (f32)asSamples[i + 7];
	}
}
