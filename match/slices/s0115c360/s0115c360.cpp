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
    uint16_t mShift;                            // +6  32 - mBits
};
extern "C" Count1Table g_count1Tables[];        // 0x015c0004

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

    // decoder entry points (same object; the retail class is the layer-III decoder)
    int SetGranuleInfo(unsigned v);                                  // 0x0115CBB0 (ret 4)
    int InitFrame(void* data, int unused);                           // 0x0115CC60 (ret 8)
    int DecodeFrame(int* chanOffsets);                               // 0x0115CCB0 (ret 4)

    // inherited / neighbouring member callees
    void FUN_01148cc0();                                             // 0x01148cc0
    void ParseHeader(int b);                                         // 0x01148a40
    void FUN_01148cb0();                                             // 0x01148cb0
    void GetSideInfo(int which);                                     // 0x0115b580
    void GetScaleFactors(int ch, int gr);                            // 0x0115b910
    void GetScaleFactorsB(int ch, int gr);                           // 0x0115c200
    void Dequantize(int ch, int gr, float* xr);                      // 0x01144020
    void Stereo(int gr, float* buf);                                 // 0x011443b0
    void Reorder(int ch, int gr, float* in, float* out);             // 0x01145d10
    void Antialias(int ch, int gr, float* buf);                      // 0x01146200
    void Imdct36X4(int ch, int gr, float* buf);                      // 0x011467f0
    void FUN_01148a20();                                             // 0x01148a20
    void PolySynth2(int ch, float* out, float* hist);                // 0x01148710

    uint32_t pad00;                             // +0x00
    uint32_t m04;                               // +0x04  header word A
    uint32_t m08;                               // +0x08  header word B
    int m0c;                                    // +0x0c
    int m10;                                    // +0x10  decoded byte count
    uint16_t m14;                               // +0x14  samples per frame (0x240)
    uint8_t m16;                                // +0x16  = 3
    uint8_t m17;                                // +0x17  header parsed flag
    uint8_t m18;                                // +0x18  channel count
    uint8_t pad19[7];                           // +0x19
    const uint8_t* mPtr;                        // +0x20  next stream byte
    const uint8_t* mBase;                       // +0x24
    uint32_t pad28;
    uint32_t mCache;                            // +0x2c  MSB-aligned bits
    int mCount;                                 // +0x30  bits in the cache
    int m34;                                    // +0x34  history-valid flag
    uint8_t m38;                                // +0x38
    uint8_t m39;                                // +0x39
    uint8_t m3a;                                // +0x3a  region0 == 0
    uint8_t m3b;                                // +0x3b  region0 != 3
    uint8_t sfreq;                              // +0x3c
    uint8_t pad3d;                              // +0x3d
    uint8_t m3e;                                // +0x3e  granule mode
    uint8_t pad3f;                              // +0x3f
    uint8_t pad40;                              // +0x40
    uint8_t m41;                                // +0x41  sfb index
    uint8_t pad42;                              // +0x42
    uint8_t m43;                                // +0x43
    uint8_t m44;                                // +0x44
    uint8_t pad45[3];                           // +0x45
    int m48;                                    // +0x48
    int m4c;                                    // +0x4c
    uint32_t pad50;                             // +0x50
    const void* mTables[0x3f];                  // +0x54  Huffman table pointers, stride 2 entries
    void* m150;                                 // +0x150
    GrInfo mGr[4];                              // +0x154
    uint32_t pad1b4[(0x2ac - 0x1b4) / 4];       // +0x1b4
    int m2ac;                                   // +0x2ac
    const float* mGainTable;                    // +0x2b0
    const int16_t* mTrees[3];                   // +0x2b4  Huffman tree per region
    int m2c0;                                   // +0x2c0
    int m2c4;                                   // +0x2c4
    void* m2c8;                                 // +0x2c8
    void* m2cc;                                 // +0x2cc
    void* m2d0;                                 // +0x2d0

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
    static volatile const float zero = 0.0f;   // volatile -> memory operand; keeps cl from holding 0 in xmm3
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

// ---- neighbours used by the frame decoder ---------------------------------
extern "C" const uint16_t g_sfbWidths[];        // 0x014ce43c  width table indexed by m41
extern "C" const uint8_t g_count1Table0Data[];  // 0x014cbc30
extern "C" const uint8_t g_count1Table1Data[];  // 0x014cbcb0
void FUN_01165fa0(float* dst, float* src);                              // 0x01165fa0
void HELPER_SignFlip(float* buf);                                       // 0x01146940
void HELPER_GatherHistories(float* buf, float* out);                    // 0x01146a10

struct DequantCtx {                             // 0115cfb0's first argument
    char pad0[4];
    float* mpBuf;                               // +0x04
    char pad8[6];
    uint16_t mStride;                           // +0x0e  samples between successive columns
};

// @ 0x0115CFB0
void FUN_0115cfb0(DequantCtx* d, float* in, unsigned n)
{
    for (unsigned i = 0; i < n; i++) {
        float* dst = d->mpBuf + (int)d->mStride * (int)i;
        dst[0]  += in[i] * (16.0f / 17.0f);
        dst[1]  += in[i] * (15.0f / 17.0f);
        dst[2]  += in[i] * (14.0f / 17.0f);
        dst[3]  += in[i] * (13.0f / 17.0f);
        dst[4]  += in[i] * (12.0f / 17.0f);
        dst[5]  += in[i] * (11.0f / 17.0f);
        dst[6]  += in[i] * (10.0f / 17.0f);
        dst[7]  += in[i] * (9.0f / 17.0f);
        dst[8]  += in[i] * (8.0f / 17.0f);
        dst[9]  += in[i] * (7.0f / 17.0f);
        dst[10] += in[i] * (6.0f / 17.0f);
        dst[11] += in[i] * (5.0f / 17.0f);
        dst[12] += in[i] * (4.0f / 17.0f);
        dst[13] += in[i] * (3.0f / 17.0f);
        dst[14] += in[i] * (2.0f / 17.0f);
        dst[15] += in[i] * (1.0f / 17.0f);
        in[i] = 0.0f;
    }
}

// @ 0x0115CBB0
int HELPER_CMpegLayer3B::SetGranuleInfo(unsigned v)
{
    unsigned r0 = (v >> 6) & 3;
    unsigned r1 = (v >> 4) & 3;
    unsigned char r2 = (unsigned char)((v >> 2) & 3);
    m44 = (unsigned char)(v & 3);
    m3e = (unsigned char)(r0 & 1);
    unsigned char bVar4 = (unsigned char)(r0 != 3);
    unsigned char isZero = (unsigned char)(r0 == 0);
    m43 = (unsigned char)r2;
    m16 = 3;
    m3b = bVar4;
    m3a = isZero;
    if (isZero) {
        m41 = (unsigned char)(r1 + 6);
    } else {
        unsigned char p = (unsigned char)(bVar4 * 3);
        m41 = (unsigned char)(p + r1);
        sfreq = (unsigned char)((unsigned char)((bVar4 - 1) & 3) + r1);
    }
    m18 = (unsigned char)((r2 != 3) + 1);
    uint16_t t = g_sfbWidths[m41];
    m08 = t;
    m04 = t;
    return 0;
}

// @ 0x0115CC60
int HELPER_CMpegLayer3B::InitFrame(void* data, int unused)
{
    if (m17)
        FUN_01148cc0();
    m17 = 1;
    mPtr = (const uint8_t*)data;
    mBase = (const uint8_t*)data;
    ParseHeader(*(const uint8_t*)data);
    m14 = 0x240;
    m34 = 1;
    m38 = 1;
    m39 = 1;
    FUN_01148cb0();
    return 0;
}

// @ 0x0115CCB0
int HELPER_CMpegLayer3B::DecodeFrame(int* chanOffsets)
{
    mBase = mPtr;
    unsigned hdr = GetBitsB(8);
    SetGranuleInfo(hdr);

    char small[12];
    char a10[2304];
    char a3610[4608];
    char a2410[2304];
    char a1b10[2304];
    char a1210[2304];
    char a910[2300];

    char* buf[4];
    int off[2];
    buf[1] = a1210;
    m150 = small;
    buf[0] = a1b10;
    off[0] = chanOffsets[0];
    off[1] = chanOffsets[1];
    buf[2] = a910;
    int which = GetBitsB(1);
    GetSideInfo(which);

    mGainTable = (const float*)m2ac;

    unsigned ch = 0;
    if (m18 != 0) {
        GrInfo* g = &mGr[which];
        do {
            int endBit = (int)(mPtr - mBase) * 8 - mCount;
            if (m3e == 1)
                GetScaleFactors(ch, which);
            else
                GetScaleFactorsB(ch, which);
            int cnt = (g->window_switching_flag == 0) + 2;
            if (cnt != 0) {
                const void** dst = (const void**)&mTrees[0];
                for (int k = 0; k < cnt; k++)
                    dst[k] = mTables[g->table_select[k] * 2];
            }
            g_count1Tables[0].mBits = 6;
            g_count1Tables[0].mShift = 0x1a;
            g_count1Tables[1].mShift = 0x1c;
            g_count1Tables[0].mTable = g_count1Table0Data;
            g_count1Tables[1].mTable = g_count1Table1Data;
            g_count1Tables[1].mBits = 4;
            HuffmanDecode(ch, which, (float*)buf[ch], endBit);
            Dequantize(ch, which, (float*)buf[ch]);
            g = (GrInfo*)((char*)g + 0x30);
            ch++;
        } while (ch < m18);
    }

    if (m18 > 1) {
        m2c8 = a2410;
        m2cc = a10;
        m2d0 = a3610;
        Stereo(which, (float*)a1b10);
    }

    ch = 0;
    if (m18 != 0) {
        GrInfo* g = &mGr[which];
        do {
            if (g->window_switching_flag == 0 || g->block_type != 2) {
                char* t = buf[ch];
                buf[ch] = buf[2];
                buf[2] = t;
            } else {
                Reorder(ch, which, (float*)buf[ch], (float*)buf[2]);
            }
            Antialias(ch, which, (float*)buf[2]);
            FUN_01165fa0((float*)buf[2], (float*)buf[ch]);
            m2c4 = m2c0;
            Imdct36X4(ch, which, (float*)buf[ch]);
            m4c = m48;
            if (m34 != 0) {
                FUN_01148a20();
                m34 = 0;
            }
            HELPER_SignFlip((float*)buf[ch]);
            HELPER_GatherHistories((float*)buf[ch], (float*)buf[2]);
            int o = off[ch];
            char* h = buf[2];
            int cnt = 0x12;
            do {
                PolySynth2(ch, (float*)o, (float*)h);
                h += 0x80;
                o += 0x80;
            } while (--cnt != 0);
            g = (GrInfo*)((char*)g + 0x30);
            off[ch] = o;
            ch++;
        } while (ch < m18);
    }

    unsigned rem = -mCount & 7;
    if (rem != 0)
        GetBitsB(8 - rem);
    m10 = (int)(((mPtr - mBase) * 8 - mCount) >> 3);
    return 0;
}

} } }
