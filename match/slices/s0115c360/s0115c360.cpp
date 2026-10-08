// Slice s0115c360 -- MPEG layer III Huffman decoding, second copy (0x0115C360, 2116 bytes).
// The first copy is Layer3Decoder::HuffmanDecode (slice s01135a30); this one sits in the decoder class that also
// holds the scalefactor reader of slice s0115b540 (granule info at +0x154, bit reader state inline at +0x20).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
//
// ISO dist10 III_huffman_decode(): for one granule/channel it decodes the big_values pairs in three regions
// (region0/1/2 boundaries from the sfb tables, the Huffman tree per region, linbits escapes, sign bits), scales
// every value by |x|^(4/3) and the global gain, then decodes the count1 quadruples, rewinds any bits read past the
// end of the part2_3 data, skips the rest and zero-fills up to line 576.  The bit reader is inlined: a 32-bit cache
// (MSB first) that is topped up from the byte stream while no more than 24 bits are cached.
#include "types.h"
#include <string.h>

namespace rw { namespace audio { namespace core {

extern "C" const int16_t g_sfBandIndex[];       // 0x014cb4e0: 30 shorts per sample-rate index
extern "C" const float g_pow43[32];             // 0x014cb460  i^(4/3), i < 32
extern "C" const uint8_t g_linbits[];           // 0x014cbcd0  per table_select

struct Count1Table {                            // 0x015c0004, 8 bytes each
    const uint8_t* mTable;                      // +0  (flags, length) byte pairs
    uint16_t mBits;                             // +4
    uint8_t mShift;                             // +6  32 - mBits
    uint8_t pad7;
};
extern "C" const Count1Table g_count1Tables[];  // 0x015c0004

struct GrInfo {                                 // 0x18 bytes, one per [granule][channel]
    uint16_t part2_3_length;                    // +0x00
    uint16_t big_values;                        // +0x02
    char pad4[2];
    uint8_t gainIdx;                            // +0x06
    uint8_t window_switching_flag;              // +0x07
    uint8_t block_type;                         // +0x08
    char pad9;
    uint8_t region0_count;                      // +0x0a
    uint8_t region1_count;                      // +0x0b
    uint8_t table_select[3];                    // +0x0c
    uint8_t count1table_select;                 // +0x0f
    char pad10[0x18 - 0x10];
};

class HELPER_CMpegLayer3B {
public:
    // |x|^(4/3) for the escape values
    void ComputePow43(int n, const int16_t* vals, float* out);       // 0x01143E70 (thiscall, ret 0xc)
    uint16_t GetBitsB(int n);                                        // 0x01134A60 (thiscall, ret 4)

    uint32_t pad00[0x20 / 4];
    const uint8_t* mPtr;                        // +0x20  next stream byte
    const uint8_t* mBase;                       // +0x24
    uint32_t pad28;
    uint32_t mCache;                            // +0x2c  MSB-aligned bits
    int mCount;                                 // +0x30  bits in the cache
    uint32_t pad34[2];
    uint8_t sfreq;                              // +0x3c
    uint8_t pad3d[0x154 - 0x3d];
    GrInfo mGr[4];                              // +0x154
    uint32_t pad1b4[(0x2b0 - 0x1b4) / 4];
    const float* mGainTable;                    // +0x2b0
    const int16_t* mTrees[3];                   // +0x2b4  Huffman tree per region

    int BitPos() const { return (int)(mPtr - mBase) * 8 - mCount; }
    __forceinline void Fill(int endBit)
    {
        int pos = BitPos();
        while (mCount <= 24 && mCount + pos < endBit) {
            unsigned int b = *mPtr;
            mCache |= b << (24 - mCount);
            mPtr++;
            mCount += 8;
        }
    }

    void HuffmanDecode(int gr, int ch, float* xr, int extraBits);    // 0x0115C360 (ret 0x10)
};

// out[idx[k]] *= pow43(val[k]) for the escape values collected so far
static __forceinline void ApplyEscapes(HELPER_CMpegLayer3B* d, int n, const int16_t* vals, const int16_t* idx,
                                       float* tmp, float* xr)
{
    d->ComputePow43(n, vals, tmp);
    for (int k = 0; k < n; k++)
        xr[idx[k]] = tmp[k] * xr[idx[k]];
}

// @ 0x0115C360
void HELPER_CMpegLayer3B::HuffmanDecode(int gr, int ch, float* xr, int extraBits)
{
    GrInfo* g = &mGr[ch + gr * 2];
    const int endBit = g->part2_3_length + extraBits;
    int n = 0;
    int lim[3];
    const int16_t* tree;
    if (g->window_switching_flag && g->block_type == 2) {
        lim[0] = 36;
        lim[1] = 576;
    } else {
        const int base = sfreq * 30;
        lim[0] = g_sfBandIndex[base + g->region0_count + 1];
        lim[1] = g_sfBandIndex[base + g->region0_count + g->region1_count + 2];
    }
    lim[2] = g->big_values * 2;
    short s = 0;
    if (lim[0] >= lim[2]) lim[0] = lim[2];
    if (lim[1] >= lim[2]) lim[1] = lim[2];

    const float gain = mGainTable[0xff - g->gainIdx];
    const float ngain = -gain;
    const float zero = 0.0f;
    int16_t idx[32];
    __declspec(align(16)) float tmp[32];
    int16_t vals[32];

    for (int r = 0; r < 3; r++) {
        const int linbits = g_linbits[g->table_select[r]];
        tree = mTrees[r];
        if (tree == 0) {
            memset(&xr[s], 0, (lim[r] - s) * 4);
            s = (short)lim[r];
            continue;
        }
        for (; s < lim[r]; s += 2) {
            Fill(endBit);
            int16_t e = tree[*((const uint8_t*)&mCache + 3)];
            int v;
            if (e >= 0) {
                int len = e >> 8;
                mCount -= len;
                v = e & 0xff;
                mCache <<= len;
            } else {
                mCount -= 8;
                mCache <<= 8;
                const int16_t* p = tree - e;
                v = *p;
                while (v < 0) {
                    p++;
                    if ((int)mCache < 0)
                        p += -v;
                    mCount--;
                    mCache <<= 1;
                    v = *p;
                }
            }
            int x = v >> 4;
            int y = v & 0xf;
            if (x == 15 && linbits) {
                x = (mCache >> (32 - linbits)) + 15;
                mCache <<= linbits;
                mCount -= linbits;
            }
            if (x != 0) {
                xr[s] = ((int)mCache < 0) ? ngain : gain;
                if (x < 32) {
                    xr[s] = g_pow43[x] * xr[s];
                } else {
                    idx[n] = s;
                    vals[n] = (int16_t)x;
                    n++;
                    if (n >= 32) {
                        ApplyEscapes(this, n, vals, idx, tmp, xr);
                        n = 0;
                    }
                }
                mCount--;
                mCache <<= 1;
            } else {
                xr[s] = zero;
            }
            Fill(endBit);
            if (y == 15 && linbits) {
                y = (mCache >> (32 - linbits)) + 15;
                mCache <<= linbits;
                mCount -= linbits;
            }
            if (y != 0) {
                xr[s + 1] = ((int)mCache < 0) ? ngain : gain;
                if (y < 32) {
                    xr[s + 1] = g_pow43[y] * xr[s + 1];
                } else {
                    idx[n] = s + 1;
                    vals[n] = (int16_t)y;
                    n++;
                    if (n >= 32) {
                        ApplyEscapes(this, n, vals, idx, tmp, xr);
                        n = 0;
                    }
                }
                mCount--;
                mCache <<= 1;
            } else {
                xr[s + 1] = zero;
            }
        }
    }
    ApplyEscapes(this, n, vals, idx, tmp, xr);

    // count1 region
    const Count1Table* t = &g_count1Tables[g->count1table_select];
    int pos = BitPos();
    while (pos < endBit && s < 0x240) {
        Fill(endBit);
        const uint8_t* e = t->mTable + (mCache >> t->mShift) * 2;
        mCount -= e[1];
        mCache <<= e[1];
        const unsigned int flags = e[0];
        if (flags & 8) { xr[s] = ((int)mCache < 0) ? ngain : gain; mCache <<= 1; mCount--; } else xr[s] = zero;
        if (flags & 4) { xr[s + 1] = ((int)mCache < 0) ? ngain : gain; mCache <<= 1; mCount--; } else xr[s + 1] = zero;
        if (flags & 2) { xr[s + 2] = ((int)mCache < 0) ? ngain : gain; mCache <<= 1; mCount--; } else xr[s + 2] = zero;
        if (flags & 1) { xr[s + 3] = ((int)mCache < 0) ? ngain : gain; mCache <<= 1; mCount--; } else xr[s + 3] = zero;
        s += 4;
        pos = BitPos();
    }
    if (pos > endBit) {
        int total = pos + (mCount - endBit);
        mPtr -= total >> 3;
        mCount = total & 7;
        if (mCount)
            mCache = (unsigned int)mPtr[-1] << (32 - mCount);
        s -= 4;
    }
    pos = BitPos();
    if (pos < endBit)
        GetBitsB(endBit - pos);
    if (s < 0x240)
        memset(&xr[s], 0, (0x240 - s) * 4);
}

} } }
