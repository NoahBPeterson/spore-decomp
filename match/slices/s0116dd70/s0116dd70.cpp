// Slice s0116dd70: rw::audio::core MPEG Layer III short-block stage of HELPER_CMpegLayer3Base
// (ISO 11172-3 / 13818-3).  Same class as slice s0116c170; the neighbouring 0x01145d10 object
// holds the byte-identical logic for the older CMpegLayer3Base, so both functions here are
// duplicated code from the same source, compiled against this class's member layout.
//
// 0x0116dd70  HELPER_CMpegLayer3Base::Reorder    short-block 3-window reordering
// 0x0116e250  HELPER_CMpegLayer3Base::Antialias  cs/ca alias-reduction butterflies
//
// Layout confirmed against the 0x0116c330 ctor / 0x0116c3c0 accesses in s0116c170.
// The object was built by VC .NET 2003 (cl 13.10) with /GL + /LTCG, so it is equivalence-only.
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ------------------------------------------------------------------ externals
// MPEG Layer III scale-factor band boundaries (0x3c bytes per sampling frequency: 23 longs then
// the 14 short-block boundaries; the short table is what both functions index).
struct SFBandIndex_s0116dd70 {
    short l[23];      // +0x00
    u8    s[14];      // +0x2e
};
extern "C" SFBandIndex_s0116dd70 sfBandIndexLSF_14da570[3];   // 0x014da570

// Short-band widths of the ten reordered bands, ten bytes per sampling frequency.
extern "C" const u8 g_reorderWidths_14cba10[];                // 0x014cba10

// Alias-reduction coefficients: the cosine table, the (negative) cosine-of-angle table, and a
// third table holding the negated values in reverse order (which is the form the original reads).
extern "C" const float g_antialiasCs_14da818[8];              // 0x014da818
extern "C" const float g_antialiasCa_14da838[8];              // 0x014da838
extern "C" const float g_antialiasCaPos_14cba4c[8];           // 0x014cba4c

// ------------------------------------------------------------------ granule info
// III_gr_info as read by this code (0x18 bytes; indexed by ch + 2 * gr).
struct III_gr_info_s0116dd70 {
    u8  pad00[0x07];            // +0x00
    u8  windowSwitchingFlag;    // +0x07
    u8  blockType;              // +0x08
    u8  mixedBlockFlag;         // +0x09
    u8  pad0a[0x0e];
};

// ------------------------------------------------------------------ the class
class HELPER_CMpegLayer3Base_s0116dd70 {
public:
    void Reorder(int gr, int ch, float* src, float* dst);       // 0x0116dd70
    void Antialias(int gr, int ch, float* xr);                  // 0x0116e250

    u8     mBaseHead[0x30];                 // +0x00 .. +0x2f  (vftable + base state)
    u8     samplingFrequency;               // +0x30
    u8     mBaseTail[0x17];                 // +0x31 .. +0x47
    u8     pad48[0x28];                     // +0x48 .. +0x6f
    III_gr_info_s0116dd70 gr_info[4];       // +0x70
};

// ------------------------------------------------------------------ 0x0116dd70
// Reorders the dequantised spectrum of a short (window-switching, block type 2) granule from the
// per-window order produced by the dequantiser into the interleaved line order the IMDCT wants.
// Pure short blocks first transpose the three low bands 4x3, mixed blocks copy the 36 long lines
// unchanged; both then walk the ten short bands, turning each band's [window][line] run into
// [line][window].  `src` and `dst` are 576-float spectra.  (The original spells the two band loops
// out with explicit 4-wide and 2-wide unrollings; the plain loops below are the same algorithm.)
// @ 0x0116dd70
void HELPER_CMpegLayer3Base_s0116dd70::Reorder(int gr, int ch, float* src, float* dst)
{
    III_gr_info_s0116dd70* gi = &gr_info[ch + 2 * gr];
    if (!(gi->windowSwitchingFlag && gi->blockType == 2))
        return;

    if (gi->mixedBlockFlag) {
        for (int i = 0; i < 36; i++)
            dst[i] = src[i];

        const u8* sfb = sfBandIndexLSF_14da570[samplingFrequency].s;
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
        for (int s = 0; s < 10; s++) {
            int width = g_reorderWidths_14cba10[samplingFrequency * 10 + s];
            if (width <= 0)
                continue;
            for (int j = 0; j < width; j++)
                for (int win = 0; win < 3; win++)
                    dst[base + 3 * j + win] = src[base + win * width + j];
            base += 3 * width;
        }
    }
}

// ------------------------------------------------------------------ 0x0116e250
// Reduces the aliasing introduced by the adjacent subband filters: every 18-line boundary is
// crossed by eight butterflies that rotate each (line, line+1) pair by the cs/ca tables.  Short
// blocks only have one such boundary (mixed blocks only the long part; pure short blocks none).
// @ 0x0116e250
void HELPER_CMpegLayer3Base_s0116dd70::Antialias(int gr, int ch, float* xr)
{
    III_gr_info_s0116dd70* gi = &gr_info[ch + 2 * gr];

    float* end;
    if (gi->windowSwitchingFlag && gi->blockType == 2) {
        if (!gi->mixedBlockFlag)
            return;
        end = xr + 18;
    } else {
        end = xr + 558;
    }

    for (float* p = xr + 18; p <= end; p += 18) {
        for (int ss = 0; ss < 8; ss++) {
            float u = p[-1 - ss];
            float v = p[ss];
            p[-1 - ss] = u * g_antialiasCs_14da818[ss] - v * g_antialiasCa_14da838[ss];
            p[ss]      = v * g_antialiasCs_14da818[ss] - u * g_antialiasCaPos_14cba4c[7 - ss];
        }
    }
}
