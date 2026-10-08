// Slice s01145d10 -- rw::audio::core MPEG layer III hybrid/IMDCT stage.
//   01145D10  CMpegLayer3Base::Reorder    (ISO 11172-3 III_reorder, short blocks)
//   01146200  CMpegLayer3Base::Antialias  (ISO III_antialias, cs/ca butterflies)
//   011464A0  HELPER_Imdct12X4            (4-wide 12-point IMDCT + accumulate)
//   011467F0  HELPER_Imdct36X4            (4-wide 36-point IMDCT + overlap-add)
//   01146940  HELPER_SignFlip             (multiply the hybrid history by +1/-1)
//   01146A10  HELPER_GatherHistories      (gather 8 interleaved hybrid planes)
//   01146A90  CMpegLayer3Base::InitHuffTables
// The core was built with /GL + /LTCG; the Imdct helpers use custom register ABIs, so the
// calls below express the intended dataflow (in/out) rather than the raw register assignment.
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <string.h>

// Data tables (C linkage so the equivalence annotator sees them).
extern "C" const float    g_cs[8];             // 0x014cb788 antialias cosine coefficients
extern "C" const float    g_ca[8];             // 0x014cb7a8 antialias (negative) coefficients
extern "C" const int16_t  g_sfbBandIndex[];    // 0x014cb4e0 (short bands as bytes at +0x2e)
extern "C" const uint8_t  g_reorderWidths[];   // 0x014cba10 10 short-band widths per sfreq
extern "C" const float    g_imdct12Coef[];     // 0x014cbab0 IMDCT12 constants
extern "C" const float    g_imdct36Win[];      // 0x014cb7d0 IMDCT36 windows / tfcos

namespace rw { namespace audio { namespace core {

struct GranuleInfo {                            // size 0x18
    uint16_t part2And3Length;                   // +0x00
    uint16_t bigValues;                         // +0x02
    uint16_t scaleFacCompress;                  // +0x04
    uint8_t  globalGain;                        // +0x06
    uint8_t  windowSwitchingFlag;               // +0x07
    uint8_t  blockType;                         // +0x08
    uint8_t  mixedBlockFlag;                    // +0x09
    uint8_t  region0Count;                      // +0x0a
    uint8_t  region1Count;                      // +0x0b
    uint8_t  tableSelect[3];                    // +0x0c
    uint8_t  count1TableSelect;                 // +0x0f
    uint8_t  subBlockGain[3];                   // +0x10
    uint8_t  preFlag;                           // +0x13
    uint32_t scaleFacScale;                     // +0x14
};

struct HuffTable {                              // size 8
    uint16_t tableSize;                         // +0x0
    uint16_t pad02;
    int16_t* pEntries;                          // +0x4
};

class CMpegLayer3Base {
public:
    uint8_t  pad00[0x3c];
    uint8_t  sfreq;                             // +0x3c
    uint8_t  pad3d[0x50 - 0x3d];
    HuffTable mHuffTables[32];                  // +0x50 .. +0x14f
    uint8_t  pad150[4];
    GranuleInfo mGranuleInfo[2][2];             // +0x154
    uint8_t  pad1b4[0x2c4 - 0x1b4];
    float*   mpLoadedPrevBlockX4;               // +0x2c4

    void Reorder(int gr, int ch, float* src, float* dst);   // 0x01145d10
    void Antialias(int gr, int ch, float* xr);              // 0x01146200
    void Imdct36X4(int gr, int ch, float* xr);              // 0x011467f0
    void InitHuffTables();                                  // 0x01146a90
};

// --- external callees ------------------------------------------------------
void HELPER_Imdct12X1(float* in, float* out);                               // 0x011661b0
void __fastcall HELPER_Imdct36X1(const float* win, float* out, float* in);  // 0x0116e4f0
void HELPER_Imdct36X4Implementation(float* in, float* out, const float* tbl);// 0x0116efb0
void HELPER_Imdct12X4(float* in, float* out);                               // 0x011464a0
void HELPER_OverlapAddX4(float* in, float* tmp, float* out);                // 0x0116f960
void HELPER_SignFlip(float* p);                                             // 0x01146940
void HELPER_GatherHistories(float* src, float* dst);                        // 0x01146a10

// @ 0x01145d10
void CMpegLayer3Base::Reorder(int gr, int ch, float* src, float* dst)
{
    GranuleInfo* gi = &mGranuleInfo[gr][ch];
    if (!(gi->windowSwitchingFlag && gi->blockType == 2))
        return;

    if (gi->mixedBlockFlag) {
        for (int i = 0; i < 36; i++)
            dst[i] = src[i];
    } else {
        // first three bands: 4x3 transpose in 12-element chunks
        for (int b = 0; b < 3; b++)
            for (int j = 0; j < 4; j++)
                for (int win = 0; win < 3; win++)
                    dst[12 * b + 3 * j + win] = src[12 * b + 4 * win + j];
    }

    int base = 36;
    const uint8_t* sb = (const uint8_t*)(g_sfbBandIndex + sfreq * 30) + 0x2e;
    const uint8_t* widths = g_reorderWidths + sfreq * 10;
    for (int s = 0; s < 10; s++) {
        int w = gi->mixedBlockFlag ? (sb[s + 4] - sb[s + 3])
                                   : (int)widths[s];
        if (w <= 0)
            continue;
        for (int j = 0; j < w; j++)
            for (int win = 0; win < 3; win++)
                dst[base + 3 * j + win] = src[base + win * w + j];
        base += 3 * w;
    }
}

// @ 0x01146200
void CMpegLayer3Base::Antialias(int gr, int ch, float* xr)
{
    GranuleInfo* gi = &mGranuleInfo[gr][ch];
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
            p[-1 - ss] = u * g_cs[ss] - v * g_ca[ss];
            p[ss]      = v * g_cs[ss] + u * g_ca[ss];
        }
    }
}

// @ 0x011464a0
void HELPER_Imdct12X4(float* x, float* y)
{
    if (((unsigned)x | (unsigned)y) & 0xf) {
        for (int i = 0; i < 4; i++)
            HELPER_Imdct12X1(x + i, y);
        return;
    }
    memset(y, 0, 0x240);
    const float* c = g_imdct12Coef;
    float* xend = x + 12;
    do {
        for (int j = 0; j < 4; j++) {
            float v2 = x[0x30 + j];
            float v6 = v2 + x[0x24 + j];
            float v10 = x[0x24 + j] + x[0x18 + j];
            float v14 = x[0x18 + j] + x[0x0c + j];
            x[0x30 + j] = v6;
            float v18 = x[0x0c + j] + x[j];
            x[0x18 + j] = v14;
            v2 = (x[0x3c + j] + v2) + v10;
            x[0x0c + j] = v18;
            v10 = v10 + v18;
            x[0x3c + j] = v2;
            x[0x24 + j] = v10;
            v14 = v14 * 0.8660254f;
            float v26 = x[j] + v6 * 0.5f;
            float v27 = v26 - v14;
            v26 = v26 + v14;
            v18 = v18 + v2 * 0.5f;
            v10 = v10 * 0.8660254f;
            float v19 = (v18 - v10) * 1.9318516f;
            float v2b = (v18 + v10) * 0.5176381f;
            v18 = (x[0x0c + j] - x[0x3c + j]) * 0.70710677f;
            float v3b = (v26 + v2b) * 0.5043145f;
            v10 = ((x[j] - x[0x30 + j]) + v18) * 0.5411961f;
            float v14b = (v27 + v19) * 0.6302362f;
            v27 = (v27 - v19) * 0.8213398f;
            v18 = ((x[j] - x[0x30 + j]) - v18) * 1.306563f;
            v2b = (v26 - v2b) * 3.830649f;
            y[0x18 + j] += v27 * 0.13052619f;
            y[0x1c + j] += v18 * 0.38268343f;
            y[0x20 + j] += v2b * 0.6087614f;
            y[0x24 + j] += v2b * -0.7933533f;
            y[0x28 + j] += v18 * -0.9238795f;
            y[0x2c + j] += v27 * -0.9914449f;
            y[0x30 + j] += v14b * -0.9914449f;
            y[0x34 + j] += v10 * -0.9238795f;
            y[0x38 + j] += v3b * -0.7933533f;
            y[0x3c + j] += v3b * -0.6087614f;
            y[0x40 + j] += v10 * -0.38268343f;
            y[0x44 + j] += v14b * -0.13052619f;
        }
        x += 4;
        y += 0x60 / 4;
    } while (x != xend);
}

// @ 0x011467f0
void CMpegLayer3Base::Imdct36X4(int gr, int ch, float* xr)
{
    GranuleInfo* gi = &mGranuleInfo[gr][ch];
    float* hybrid = (float*)((uint8_t*)mpLoadedPrevBlockX4 + gr * 0x900);
    __declspec(align(16)) float tmp[0x240 / 4];
    int flag = 0;
    if (gi->windowSwitchingFlag && gi->mixedBlockFlag) {
        uint8_t* t = (uint8_t*)tmp;
        uint8_t* in = (uint8_t*)xr;           // the sub-block inputs are 4 bytes apart
        HELPER_Imdct36X1(g_imdct36Win, (float*)(t + 0), (float*)(in + 0));
        HELPER_Imdct36X1(g_imdct36Win, (float*)(t + 4), (float*)(in + 4));
        HELPER_Imdct12X1((float*)(in + 8), (float*)(t + 8));
        HELPER_Imdct12X1((float*)(in + 0xc), (float*)(t + 0xc));
        HELPER_OverlapAddX4(xr, tmp, hybrid);
        flag = 1;
    }
    if (gi->blockType == 2) {
        for (; flag < 8; flag++) {
            float* p = xr + flag * 0x120 / 4;
            HELPER_Imdct12X4(p, tmp);
            HELPER_OverlapAddX4(p, tmp, hybrid + flag * 0x120 / 4);
        }
    } else {
        const float* tbl = (const float*)((const uint8_t*)g_imdct36Win + gi->blockType * 0x90);
        for (; flag < 8; flag++) {
            float* p = xr + flag * 0x120 / 4;
            HELPER_Imdct36X4Implementation(p, tmp, tbl);
            HELPER_OverlapAddX4(p, tmp, hybrid + flag * 0x120 / 4);
        }
    }
}

// @ 0x01146940
void HELPER_SignFlip(float* p)
{
    for (int b = 0; b < 8; b++) {
        for (int g = 0; g < 9; g++) {
            float* q = p + (0x10 + g * 0x20) / 4;
            q[0] = q[0] * 1.0f;
            q[1] = q[1] * -1.0f;
            q[2] = q[2] * 1.0f;
            q[3] = q[3] * -1.0f;
        }
        p += 0x120 / 4;
    }
}

// @ 0x01146a10
void HELPER_GatherHistories(float* src, float* dst)
{
    for (int i = 0; i < 18; i++)
        for (int k = 0; k < 8; k++)
            for (int j = 0; j < 4; j++)
                dst[i * 32 + k * 4 + j] = src[i * 4 + k * 72 + j];
}

// @ 0x01146a90
void CMpegLayer3Base::InitHuffTables()
{
    mHuffTables[0].tableSize = 0;        mHuffTables[0].pEntries = 0;
    mHuffTables[1].tableSize = 0x200;    mHuffTables[1].pEntries = (int16_t*)0x15c0100;
    mHuffTables[2].tableSize = 0x200;    mHuffTables[2].pEntries = (int16_t*)0x15c0300;
    mHuffTables[3].tableSize = 0x200;    mHuffTables[3].pEntries = (int16_t*)0x15c0500;
    mHuffTables[4].tableSize = 0;        mHuffTables[4].pEntries = 0;
    mHuffTables[5].tableSize = 0x200;    mHuffTables[5].pEntries = (int16_t*)0x15c0700;
    mHuffTables[6].tableSize = 0x200;    mHuffTables[6].pEntries = (int16_t*)0x15c0900;
    mHuffTables[7].tableSize = 0x226;    mHuffTables[7].pEntries = (int16_t*)0x15c0b00;
    mHuffTables[8].tableSize = 0x22a;    mHuffTables[8].pEntries = (int16_t*)0x15c0d80;
    mHuffTables[9].tableSize = 0x20c;    mHuffTables[9].pEntries = (int16_t*)0x15c1000;
    mHuffTables[10].tableSize = 0x28a;   mHuffTables[10].pEntries = (int16_t*)0x15c1280;
    mHuffTables[11].tableSize = 0x256;   mHuffTables[11].pEntries = (int16_t*)0x15c1580;
    mHuffTables[12].tableSize = 0x22e;   mHuffTables[12].pEntries = (int16_t*)0x15c1800;
    mHuffTables[13].tableSize = 0x570;   mHuffTables[13].pEntries = (int16_t*)0x15c1a80;
    mHuffTables[14].tableSize = 0;       mHuffTables[14].pEntries = 0;
    mHuffTables[15].tableSize = 0x4d6;   mHuffTables[15].pEntries = (int16_t*)0x15c2000;
    for (int i = 16; i < 24; i++) {
        mHuffTables[i].tableSize = 0x56a;
        mHuffTables[i].pEntries = (int16_t*)0x15c2500;
    }
    for (int i = 24; i < 32; i++) {
        mHuffTables[i].tableSize = 0x46c;
        mHuffTables[i].pEntries = (int16_t*)0x15c2a80;
    }
}

} } }
