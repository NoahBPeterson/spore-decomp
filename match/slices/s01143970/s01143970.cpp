// Slice s01143970 -- rw::audio::core MPEG layer III dequantisation helpers.
//   01143970 / 01143B40 : packed 24-bit integer samples -> float (two byte orders)
//   01143D10            : packed 16-bit integer samples -> float
//   01143E70            : x^(4/3) approximation (the "pow43" escape table)
//   01144020            : CMpegLayer3Base::Dequantize (ISO 11172-3 III_dequantize_sample)
//   01144270            : in-place (a+b)/sqrt2 , (a-b)/sqrt2 butterfly over two 576-blocks
// The three unpackers share a "current chunk" walker over a table of 0x14-byte descriptors.
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// Data tables (C linkage so the equivalence checker's annotation matcher sees them).
extern "C" const float g_pow43Cubic[];       // 0x014cb3d0
extern "C" const int16_t g_sfbBandIndex[];   // 0x014cb4e0
extern "C" const signed char g_pretab[];     // 0x014cb3b0

namespace rw { namespace audio { namespace core {

// ---------------------------------------------------------------------------
// Sample stream / chunk walker used by the three unpackers.
// ---------------------------------------------------------------------------

struct SampleChunk {                    // 0x14 bytes
    uint8_t* pData;                     // +0x00
    uint32_t pad04;
    uint32_t pad08;
    int32_t  size;                      // +0x0c
    uint8_t  flag;                      // +0x10
    uint8_t  pad11[3];
};

struct UnpackState {
    uint8_t  pad00[0x24];
    int32_t  mChunkOffset;              // +0x24  self-relative offset of the descriptor array
    uint8_t  pad28[6];
    uint8_t  mChannels;                 // +0x2e
    uint8_t  pad2f;
    uint8_t  mChunkIndex;               // +0x30
    uint8_t  pad31;
    uint8_t  mChunkCount;               // +0x32
    uint8_t  pad33;
    uint8_t* mData;                     // +0x34  current read pointer
    int32_t  mRemain;                   // +0x38  bytes left in the current chunk
};

struct DstBuffer {
    uint32_t pad00;
    float*   mData;                     // +0x04
    uint8_t  pad08[6];
    uint16_t mStride;                   // +0x0e  destination elements per channel
};

// Advance to the next descriptor when the current chunk is exhausted.
static __forceinline uint8_t* BeginChunk(UnpackState* st)
{
    if (st->mRemain <= 0) {
        SampleChunk* c = (SampleChunk*)((uint8_t*)st + st->mChunkOffset + st->mChunkIndex * 0x14);
        if (c->size == 0) {
            c = 0;
        } else {
            st->mChunkIndex++;
            if (st->mChunkCount <= st->mChunkIndex)
                st->mChunkIndex = 0;
        }
        if (c->flag == 0) {
            st->mData = 0;
            st->mRemain = 0;
        }
        st->mData = c->pData;
        st->mRemain = c->size;
    }
    return st->mData;
}

// @ 0x01143970
void Unpack24LE(UnpackState* st, DstBuffer* buf, int n)
{
    uint8_t* base = BeginChunk(st);
    uint8_t* src = base;
    int field = st->mChannels;
    for (int ch = 0; ch < field; ch++) {
        float* out = (float*)((uint8_t*)buf->mData + buf->mStride * ch * 4);
        uint8_t* s = src;
        for (int i = 0; i < n; i++) {
            uint32_t v = ((uint32_t)s[2] << 16) | ((uint32_t)s[1] << 8) | s[0];
            out[i] = (float)(int32_t)(v << 8) * 4.656612873077393e-10f;
            s += 3;
        }
        src += 3;
    }
    st->mData += field * n * 3;
    st->mRemain -= n;
}

// @ 0x01143b40
void Unpack24BE(UnpackState* st, DstBuffer* buf, int n)
{
    uint8_t* base = BeginChunk(st);
    uint8_t* src = base;
    int field = st->mChannels;
    for (int ch = 0; ch < field; ch++) {
        float* out = (float*)((uint8_t*)buf->mData + buf->mStride * ch * 4);
        uint8_t* s = src;
        for (int i = 0; i < n; i++) {
            uint32_t v = ((uint32_t)s[0] << 16) | ((uint32_t)s[1] << 8) | s[2];
            out[i] = (float)(int32_t)(v << 8) * 4.656612873077393e-10f;
            s += 3;
        }
        src += 3;
    }
    st->mData += field * n * 3;
    st->mRemain -= n;
}

// @ 0x01143d10
int Unpack16(UnpackState* st, DstBuffer* buf, int n)
{
    uint8_t* base = BeginChunk(st);
    int16_t* src = (int16_t*)base;
    int field = st->mChannels;
    for (int ch = 0; ch < field; ch++) {
        float* out = (float*)((uint8_t*)buf->mData + buf->mStride * ch * 4);
        int16_t* s = src;
        for (int i = 0; i < n; i++) {
            out[i] = (float)(int)s[i * field] * 3.0518509447574615e-05f;
        }
        src += 1;
    }
    st->mData = (uint8_t*)((int16_t*)st->mData + field * n);
    st->mRemain -= n;
    return n;
}

// ---------------------------------------------------------------------------
// x^(4/3) approximation, 9 cubic segments indexed by the leading-bit position.
// Table 0x014cb3d0: 9 * 4 floats (c0, c1, c2, c3).
// ---------------------------------------------------------------------------

class HELPER_CMpegLayer3B {
public:
    void ComputePow43(int n, const int16_t* in, float* out);   // 0x01143e70 (ret 0xc)
};

static __forceinline const float* Pow43Coeffs(int v)
{
    int msb = 0;                        // bsr leaves the destination unchanged for a zero source
    if (v != 0) {
        unsigned u = (unsigned)v;
        msb = 31;
        while (!(u & (1u << msb)))
            msb--;
    }
    int seg = 13 - msb;
    if (seg > 8)
        seg = 8;
    return &g_pow43Cubic[seg * 4];
}

// @ 0x01143e70
void HELPER_CMpegLayer3B::ComputePow43(int n, const int16_t* in, float* out)
{
    unsigned un = (unsigned)n;
    int i = 0;
    int n4 = (int)(un & ~3u);
    for (; i < n4; i += 4) {            // the original's 4-wide block, evaluated as the SSE path does
        for (int j = 0; j < 4; j++) {
            const float* c = Pow43Coeffs(in[i + j]);
            float x = (float)in[i + j];
            float x2 = x * x;
            float x3 = x * x2;
            out[i + j] = (c[0] + c[1] * x) + (c[2] * x2 + c[3] * x3);
        }
    }
    int rem = (int)(un & 3u);           // n - (n & ~3), valid even for a negative n
    for (; rem > 0; rem--, i++) {       // remainder: the original's scalar x87 ordering
        const float* c = Pow43Coeffs(in[i]);
        float x = (float)in[i];
        float x2 = x * x;
        float x3 = x * x2;
        out[i] = ((c[0] + c[3] * x3) + c[2] * x2) + c[1] * x;
    }
}

// ---------------------------------------------------------------------------
// Layer III dequantisation.
// ---------------------------------------------------------------------------

struct GranuleInfo {                    // size 0x18
    uint16_t part2And3Length;           // +0x00
    uint16_t bigValues;                 // +0x02
    uint16_t scaleFacCompress;          // +0x04
    uint8_t  globalGain;                // +0x06
    uint8_t  windowSwitchingFlag;       // +0x07
    uint8_t  blockType;                 // +0x08
    uint8_t  mixedBlockFlag;            // +0x09
    uint8_t  region0Count;              // +0x0a
    uint8_t  region1Count;              // +0x0b
    uint8_t  tableSelect[3];            // +0x0c
    uint8_t  count1TableSelect;         // +0x0f
    uint8_t  subBlockGain[3];           // +0x10
    uint8_t  preFlag;                   // +0x13
    uint32_t scaleFacScale;             // +0x14
};

struct Layer3ScaleFactors {             // size 0x7c
    int16_t longBlock[23];              // +0x00
    int16_t shortBlock[3][13];          // +0x2e
};

void ScaleSamples(float* p, float gain, int count);   // 0x01148da0

class CMpegLayer3Base {
public:
    uint8_t  pad00[0x3c];
    uint8_t  sfreq;                             // +0x3c
    uint8_t  pad3d[0x154 - 0x3d];
    GranuleInfo mGranuleInfo[2][2];             // +0x154
    Layer3ScaleFactors mScaleFactors[2];        // +0x1b4
    float*   mpTwoToNegativeQuarterPower;       // +0x2ac
    float*   mpLoadedTwoToNegativeQuarterPower; // +0x2b0

    void Dequantize(int gr, int ch, float* xr); // 0x01144020
};

// @ 0x01144020
void CMpegLayer3Base::Dequantize(int gr, int ch, float* xr)
{
    GranuleInfo* gi = &mGranuleInfo[gr][ch];
    int16_t* sf = mScaleFactors[gr].longBlock;
    float* gainTable = (float*)((uint8_t*)mpLoadedTwoToNegativeQuarterPower + 0xb4);
    const uint8_t* sfb = (const uint8_t*)(g_sfbBandIndex + sfreq * 30);

    int nlong;
    if (!gi->windowSwitchingFlag || gi->blockType != 2)
        nlong = 22;
    else if (!gi->mixedBlockFlag)
        nlong = 0;
    else
        nlong = (sfreq < 3) ? 6 : 8;

    for (int k = 0; k < nlong; k++) {
        int v = sf[k];
        if (gi->preFlag)
            v += g_pretab[k];
        float g = *(float*)((uint8_t*)gainTable + (v << gi->scaleFacScale) * 8);
        if (g != 1.0f) {
            int start = g_sfbBandIndex[sfreq * 30 + k];
            int end = g_sfbBandIndex[sfreq * 30 + k + 1];
            ScaleSamples(xr + start, g, end - start);
        }
    }

    int nshort = (nlong == 22) ? 13 : (nlong == 0 ? 0 : 3);
    if (nshort < 13) {
        const uint8_t* p = sfb + 0x2e;
        int16_t (*sb)[13] = mScaleFactors[gr].shortBlock;
        for (int k = nshort; k < 13; k++) {
            int a = p[k];
            int len = p[k + 1] - a;
            int idx0 = (int)sb[0][k] << gi->scaleFacScale;
            float g0 = *(float*)((uint8_t*)gainTable + (idx0 + gi->subBlockGain[0] * 4) * 8);
            if (g0 != 1.0f)
                ScaleSamples(xr + a * 3, g0, len);
            int idx1 = (int)sb[1][k] << gi->scaleFacScale;
            float g1 = *(float*)((uint8_t*)gainTable + (idx1 + gi->subBlockGain[1] * 4) * 8);
            if (g1 != 1.0f)
                ScaleSamples(xr + a * 3 + len, g1, len);
            int idx2 = (int)sb[2][k] << gi->scaleFacScale;
            float g2 = *(float*)((uint8_t*)gainTable + (idx2 + gi->subBlockGain[2] * 4) * 8);
            if (g2 != 1.0f)
                ScaleSamples(xr + a * 3 + 2 * len, g2, len);
        }
    }
}

// ---------------------------------------------------------------------------
// (a+b)*1/sqrt2 , (a-b)*1/sqrt2 over the two 576-float halves (MS stereo).
// @ 0x01144270
// ---------------------------------------------------------------------------
void Butterfly576(float* p);

// @ 0x01144270
void Butterfly576(float* p)
{
    for (int i = 0; i < 576; i++) {
        float a = p[i];
        float b = p[i + 576];
        p[i] = (a + b) * 0.7071067690849304f;
        p[i + 576] = (a - b) * 0.7071067690849304f;
    }
}

} } }
