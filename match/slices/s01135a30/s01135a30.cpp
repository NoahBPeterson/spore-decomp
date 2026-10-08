// Slice s01135a30 -- MP3 layer-III Huffman decoding  @ 0x01135ba0  (2234 bytes).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
//
// ISO dist10 III_huffman_decode(): for one granule/channel it decodes the big_values pairs
// (region0/1/2 table selects, linbits escapes, sign bits), scales every value by |x|^(4/3)
// and the global gain, then decodes the count1 quadruples, rewinds any bits read past the
// end of the part2_3 data, skips the stuffing and zero-fills the rest of the 576 lines.
#include "../../include/types.h"
#include <string.h>

extern "C" const int16_t g_sfBandIndex[];       // 0x014cb4e0: 30 shorts (0x3c bytes) per sample-rate index
extern "C" const float g_pow43[32];             // 0x014cb460  i^(4/3), i < 32
extern "C" const uint8_t g_linbits[];           // 0x014cbcd0  per table_select
extern "C" const float g_gainEnd[];             // 0x014cc17c  gain scale, indexed negatively

struct Count1Table {                            // 0x015c0004, 8 bytes each
    const uint8_t* mTable;                      // (flags, length) byte pairs
    uint16_t mBits;                             // address bits of the table
    uint16_t pad;
};
extern "C" const Count1Table g_count1Tables[];  // 0x015c0004

struct BitReader {                              // bit stream with a 2 KB ring buffer
    int pad0;
    unsigned int mPos;                          // +0x04  next byte
    unsigned int mBitsLeft;                     // +0x08  bits left in the cache
    unsigned int mCache;                        // +0x0c  MSB-aligned
    uint8_t mBuf[0x800];                        // +0x10

    unsigned int ReadBits(unsigned int n);      // 0x01134af0 (thiscall, ret 4)

    __forceinline unsigned int Bit()
    {
        if (mBitsLeft == 0) {
            unsigned int p = mPos;
            mCache = (unsigned int)mBuf[p & 0x7ff] << 24;
            mPos = p + 1;
            mBitsLeft = 8;
        }
        unsigned int c = mCache;
        mBitsLeft--;
        unsigned int bit = c >> 31;
        mCache = c + c;
        return bit;
    }
    __forceinline int BitPos() const { return (int)mPos * 8 - (int)mBitsLeft; }
    // un-read bits so the stream position is `nbits` bits earlier than the cache implies
    __forceinline void SetPos(unsigned int bitsLeftTotal)
    {
        mPos -= bitsLeftTotal >> 3;
        mBitsLeft = bitsLeftTotal & 7;
        if (mBitsLeft)
            mCache = (unsigned int)mBuf[(mPos - 1) & 0x7ff] << (0x20 - mBitsLeft);
    }
};

struct Pow43Calc {
    void Compute(int n, const int16_t* vals, float* out);   // 0x01143e70 (thiscall, ret 0xc)
};

struct HuffTable { const int16_t* mTree; int pad; };         // 8 bytes, tree is NULL for unused tables

struct GrInfo {                                              // 0x18 bytes
    uint16_t part2_3_length;                                 // +0x00
    uint16_t big_values;                                     // +0x02
    char pad4[2];
    uint8_t gainIdx;                                         // +0x06
    uint8_t window_switching_flag;                           // +0x07
    uint8_t block_type;                                      // +0x08
    char pad9;
    uint8_t region0_count;                                   // +0x0a
    uint8_t region1_count;                                   // +0x0b
    uint8_t table_select[3];                                 // +0x0c
    uint8_t count1table_select;                              // +0x0f
    char pad10[0x18 - 0x10];
};

struct Layer3Decoder {
    char pad0[0x34];
    Pow43Calc mPow43;                                        // +0x34
    char pad35[0x70 - 0x35];
    uint8_t sfreq;                                           // +0x70
    char pad71[0x88 - 0x71];
    HuffTable mHuff[32];                                     // +0x88
    GrInfo mGr[1];                                           // +0x188 (stride 0x18)
    char pad1a0[0x2710 - 0x1a0];
    BitReader mBits;                                         // +0x2710

    void HuffmanDecode(int gr, int ch, float* xr, int extraBits);
};

// out[idx[k]] *= pow43(val[k]) for the escape values collected so far
static __forceinline void ApplyEscapes(Pow43Calc* calc, int n, const int16_t* vals, const int16_t* idx,
                                       float* tmp, float* xr)
{
    calc->Compute(n, vals, tmp);
    for (int k = 0; k < n; k++)
        xr[idx[k]] = tmp[k] * xr[idx[k]];
}

// @ 0x01135ba0
void Layer3Decoder::HuffmanDecode(int gr, int ch, float* xr, int extraBits)
{
    int n = 0;
    GrInfo* g = &mGr[ch + gr * 2];
    const int endBit = g->part2_3_length + extraBits;
    int region1Start, region2Start;
    if (g->window_switching_flag && g->block_type == 2) {
        region1Start = 36;
        region2Start = 576;
    } else {
        const int base = sfreq * 30;
        region1Start = g_sfBandIndex[base + g->region0_count + 1];
        region2Start = g_sfBandIndex[base + g->region0_count + g->region1_count + 2];
    }

    const float gain = g_gainEnd[-(int)g->gainIdx];
    const float ngain = -gain;
    const float zero = 0.0f;
    short s = 0;
    int16_t idx[32];
    __declspec(align(16)) float tmp[32];
    int16_t vals[32];

    const int count = g->big_values * 2;
    for (int i = 0; i < count; i += 2, s += 2) {
        int sel;
        if (i < region1Start)
            sel = g->table_select[0];
        else if (i < region2Start)
            sel = g->table_select[1];
        else
            sel = g->table_select[2];
        const int linbits = g_linbits[sel];
        const int16_t* p = mHuff[sel].mTree;
        if (p == 0) {
            xr[s] = zero;
            xr[s + 1] = zero;
            continue;
        }
        int v = *p;
        while (v < 0) {
            p++;
            if (mBits.Bit())
                p += -v;
            v = *p;
        }
        int x = v >> 4;
        int y = v & 0xf;
        if (x == 15 && linbits)
            x = mBits.ReadBits(linbits) + 15;
        if (x != 0) {
            if (mBits.Bit()) xr[s] = ngain; else xr[s] = gain;
            if (x < 32) {
                xr[s] = g_pow43[x] * xr[s];
            } else {
                idx[n] = s;
                vals[n] = (int16_t)x;
                n++;
                if (n >= 32) {
                    ApplyEscapes(&mPow43, n, vals, idx, tmp, xr);
                    n = 0;
                }
            }
        } else {
            xr[s] = zero;
        }
        if (y == 15 && linbits)
            y = mBits.ReadBits(linbits) + 15;
        if (y != 0) {
            if (mBits.Bit()) xr[s + 1] = ngain; else xr[s + 1] = gain;
            if (y < 32) {
                xr[s + 1] = g_pow43[y] * xr[s + 1];
            } else {
                idx[n] = s + 1;
                vals[n] = (int16_t)y;
                n++;
                if (n >= 32) {
                    ApplyEscapes(&mPow43, n, vals, idx, tmp, xr);
                    n = 0;
                }
            }
        } else {
            xr[s + 1] = zero;
        }
    }
    ApplyEscapes(&mPow43, n, vals, idx, tmp, xr);

    // count1 region
    const Count1Table* t = &g_count1Tables[g->count1table_select];
    int pos = mBits.BitPos();
    while (pos < endBit && s < 0x240) {
        const unsigned int code = mBits.ReadBits(t->mBits);
        const uint8_t* e = t->mTable + code * 2;
        mBits.mBitsLeft += t->mBits - e[1];
        mBits.SetPos(mBits.mBitsLeft);
        const unsigned int flags = e[0];
        if (flags & 8) { if (mBits.Bit()) xr[s] = ngain; else xr[s] = gain; } else xr[s] = zero;
        if (flags & 4) { if (mBits.Bit()) xr[s + 1] = ngain; else xr[s + 1] = gain; } else xr[s + 1] = zero;
        if (flags & 2) { if (mBits.Bit()) xr[s + 2] = ngain; else xr[s + 2] = gain; } else xr[s + 2] = zero;
        if (flags & 1) { if (mBits.Bit()) xr[s + 3] = ngain; else xr[s + 3] = gain; } else xr[s + 3] = zero;
        s += 4;
        pos = mBits.BitPos();
    }
    if (pos > endBit) {
        mBits.SetPos(pos + (mBits.mBitsLeft - endBit));
        s -= 4;
    }
    pos = mBits.BitPos();
    if (pos < endBit)
        mBits.ReadBits(endBit - pos);
    if (s < 0x240)
        memset(&xr[s], 0, (0x240 - s) * 4);
}
