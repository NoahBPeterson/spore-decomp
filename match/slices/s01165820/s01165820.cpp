// Slice s01165820 -- EATech/EAX subband-decoder granule helpers.
//   01165820  Reorder    (ISO 11172-3 III_reorder for the short-block spectra of one granule)
//   01165D00  Antialias  (ISO III_antialias cs/ca butterflies on every 18-line boundary)
//   01165FA0  Deinterleave4 (gather four 18-line planes at stride 0x120 into 4-wide slots)
//   011661B0  rw::audio::core::HELPER_Imdct12X1 (12-point IMDCT, one lane)
//
// 01165820 and 01165D00 are byte-identical instruction streams to the 0x0116DD70 / 0x0116E250
// Reorder/Antialias reconstructed in slice s0116dd70 (verified with a capstone-aligned diff): the
// two objects hold the same source compiled against different class layouts.  Only the granule-info
// base (+0x58 here, +0x70 there), the sampling frequency (+0x3c vs +0x30) and the per-object static
// constant tables differ.  01165FA0 has no twin and is shared by both caller families
// (0x011587B3 and 0x0115B0B3 call it after 0x01165D00 / 0x0116E250 respectively).
//
// Callers are in the same object (slice s011586f0, 0x01158796/0x011587AC call ours); its byte-exact
// rows prove the object was built by the VS2008 x86 compiler, so the flag set below is used.  The
// original is /GL + /LTCG however: 011661B0 takes `out` in EAX and `in` on the stack with
// caller-cleanup, which only /GL emits and which has no C spelling.  The body is therefore
// reproduced with a plain (in, out) argument list; see nonmatching.txt.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// Data tables, per-TU statics of the original translation unit.
extern "C" const uint8_t g_sfbShortTable[];      // 0x014d6ffe  short-band boundaries, 60 bytes per sfreq
extern "C" const uint8_t g_reorderWidths[];      // 0x014d75c8  ten short-band widths per sfreq
extern "C" const float   g_antialiasCs[];        // 0x014d7330  cs[8]
extern "C" const float   g_antialiasCa[];        // 0x014d7350  ca[8] (negative)
extern "C" const float   g_antialiasCaPos[];     // 0x014cba4c  the same ca, negated, in reverse order

struct SubbandEntry {                            // 0x18 bytes, mEntries[ch + 2*gr]
    uint16_t w00;
    uint16_t w02;
    uint16_t w04;
    uint8_t  b06;
    uint8_t  windowSwitchingFlag;                // +0x07
    uint8_t  blockType;                          // +0x08
    uint8_t  mixedBlockFlag;                     // +0x09
    uint8_t  pad0a[0x18 - 0x0a];
};

class CSubbandDecoder {
public:
    uint8_t  pad00[0x3c];
    uint8_t  samplingFrequency;                  // +0x3c
    uint8_t  pad3d[0x58 - 0x3d];
    SubbandEntry mEntries[16];                   // +0x58

    void   Reorder(int gr, int ch, float* src, float* dst);   // @ 0x01165820
    void   Antialias(int gr, int ch, float* xr);              // @ 0x01165d00
};

// @ 0x01165820
void CSubbandDecoder::Reorder(int gr, int ch, float* src, float* dst)
{
    SubbandEntry* entry = &mEntries[ch + 2 * gr];
    if (!(entry->windowSwitchingFlag && entry->blockType == 2))
        return;

    if (entry->mixedBlockFlag) {
        for (int i = 0; i < 36; i++)
            dst[i] = src[i];

        const uint8_t* sfb = g_sfbShortTable + samplingFrequency * 60;
        for (int b = 3; b < 13; b++) {
            int start = sfb[b];
            int width = sfb[b + 1] - start;
            int base = 3 * start;
            for (int j = 0; j < width; j++)
                for (int win = 0; win < 3; win++)
                    dst[base + 3 * j + win] = src[base + win * width + j];
        }
    } else {
        for (int b = 0; b < 3; b++)
            for (int j = 0; j < 4; j++)
                for (int win = 0; win < 3; win++)
                    dst[12 * b + 3 * j + win] = src[12 * b + 4 * win + j];

        int base = 36;
        const uint8_t* widths = g_reorderWidths + samplingFrequency * 10;
        for (int s = 0; s < 10; s++) {
            int width = widths[s];
            if (width <= 0)
                continue;
            for (int j = 0; j < width; j++)
                for (int win = 0; win < 3; win++)
                    dst[base + 3 * j + win] = src[base + win * width + j];
            base += 3 * width;
        }
    }
}

// @ 0x01165d00
// The original is void: on the butterfly path the return register ends up holding the low half of
// the loop-count magic multiply (`mov eax,0x38E38E39; mul edx`), so no meaningful value is returned
// and the caller (0x011587AC) discards it.
void CSubbandDecoder::Antialias(int gr, int ch, float* xr)
{
    SubbandEntry* entry = &mEntries[ch + 2 * gr];
    float* end;

    if (entry->windowSwitchingFlag) {
        if (entry->blockType == 2 && entry->mixedBlockFlag == 0)
            return;
        if (entry->windowSwitchingFlag && entry->mixedBlockFlag && entry->blockType == 2) {
            end = xr + 0x12;
            goto loop;
        }
    }
    end = xr + 0x22e;

loop:
    for (float* p = xr + 0x12; p <= end; p += 0x12) {
        for (int ss = 0; ss < 8; ss++) {
            float u = p[-1 - ss];
            float v = p[ss];
            p[-1 - ss] = u * g_antialiasCs[ss] - v * g_antialiasCa[ss];
            p[ss]      = v * g_antialiasCs[ss] - u * g_antialiasCaPos[7 - ss];
        }
    }
}

// @ 0x01165fa0
// The dequantiser leaves the four short windows of each of the eight 72-line blocks stacked as a
// 4x18 matrix (four 18-line planes at stride 0x120 bytes); the IMDCT wants them as 18 four-wide
// slots, so every block is transposed.  (The original spells the outer 18-trip loop out with the
// eight inner groups fully unrolled; the plain loops below are the same permutation.)
void Deinterleave4(float* src, float* dst)
{
    for (int i = 0; i < 18; i++)
        for (int k = 0; k < 8; k++)
            for (int j = 0; j < 4; j++)
                dst[72 * k + 4 * i + j] = src[72 * k + 18 * j + i];
}

namespace rw { namespace audio { namespace core {

// @ 0x011661b0  HELPER_Imdct12X1
void HELPER_Imdct12X1(float* in, float* out)
{
    for (int k = 0; k < 36; k++)
        out[4 * k] = 0.0f;

    for (int w = 0; w < 3; w++) {
        float* p = in + 4 * w;
        float A = p[0x00];
        float B = p[0x0c];
        float C = p[0x18];
        float D = p[0x24];
        float E = p[0x30];
        float F = p[0x3c];

        // in-place prefix sums (the original re-reads the slots it has already overwritten)
        p[0x0c] = A + B;
        p[0x18] = C + B;
        p[0x3c] = E + F;
        p[0x30] = E + D;
        p[0x24] = (A + B) + (C + D);
        float u5 = (C + D) + (E + F);
        p[0x3c] = u5;

        float v26 = (E + D) * 0.5f + A;
        float v14 = (C + B) * 0.8660254f;
        float t33 = v26 - v14;
        float t34 = v26 + v14;
        float W   = u5 * 0.5f + (A + B);
        float vX  = ((A + B) - u5) * 0.70710677f;
        float t44 = ((A + B) + (C + D)) * 0.8660254f;
        float t46 = W - t44;
        float t47 = W + t44;
        float t48 = t46 * 1.9318516f;
        float t49 = t47 * 0.5176381f;
        float t53 = t34 - t49;
        float t58 = (t49 + t34) * 0.50431448f;
        float t56 = t53 * 3.8306489f;
        float t61 = (vX + (A - (E + D))) * 0.54119611f;
        float t64 = ((A - (E + D)) - vX) * 1.306563f;
        float t68 = (t48 + t33) * 0.63023621f;
        float t81 = (t33 - t48) * 0.82133979f;

        float* o = out + 0x18 + 0x18 * w;
        o[0x00] += t81 * 0.13052619f;
        o[0x04] += t64 * 0.38268343f;
        o[0x08] += t56 * 0.60876143f;
        o[0x0c] += t56 * -0.79335332f;
        o[0x10] += t64 * -0.92387950f;
        o[0x14] += t81 * -0.99144489f;
        o[0x18] += t68 * -0.99144489f;
        o[0x1c] += t61 * -0.92387950f;
        o[0x20] += t58 * -0.79335332f;
        o[0x24] += t58 * -0.60876143f;
        o[0x28] += t61 * -0.38268343f;
        o[0x2c] += t68 * -0.13052619f;
    }
}

} } }
