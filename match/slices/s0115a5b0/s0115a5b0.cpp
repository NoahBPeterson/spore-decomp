// Slice s0115a5b0: rw::audio::core::HELPER_CEALayer3::DecodeHuffman (ISO 11172-3 "III_hufman_decode"):
// big_values pairs through the Huffman tables (with linbits escapes, batched x^(4/3) via SToPowerOf4over3),
// then the count1 quadruples, then bit-position fix-up and zero fill of the remaining lines.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <string.h>

namespace rw { namespace audio { namespace core {

extern const float  kGainTable[];       // 0x014da454 (indexed by -global_gain)
extern const short  kSfbBounds[];       // 0x014da570 (sfreq*30 + region index)
extern const float  kPow43Small[32];    // 0x014da4f0
extern const short* const kHuffTables[];// 0x014dc190 (null = table with no codes)
extern const uint8_t kLinbits[];        // 0x014dc210

struct Count1Table {                    // 8 bytes, at 0x014dc2d0
    const uint8_t* entries;             // +0 pairs of (flags, length)
    uint16_t pad4;
    uint8_t shift;                      // +6
    uint8_t pad7;
};
extern const Count1Table kCount1[];

struct GranuleInfo {                    // 0x18 bytes
    uint16_t part2And3Length;           // +0
    uint16_t bigValues;                 // +2
    uint16_t pad4;
    uint8_t globalGain;                 // +6
    uint8_t windowSwitchingFlag;        // +7
    uint8_t blockType;                  // +8
    uint8_t pad9;
    uint8_t region0Count;               // +0xa
    uint8_t region1Count;               // +0xb
    uint8_t tableSelect[3];             // +0xc
    uint8_t count1TableSelect;          // +0xf
    uint8_t rest[8];
};

class HELPER_CMpegBase {
public:
    uint32_t pad00[6];
    const uint8_t* mBufPtr;             // +0x18
    const uint8_t* mBufPtrBase;         // +0x1c
    uint32_t pad20;
    int mShiftReg;                      // +0x24
    int mShiftRegBits;                  // +0x28
    uint32_t pad2c;
    uint8_t sfreq;                      // +0x30
    uint8_t pad31[3];
    uint32_t pad34[15];                 // to +0x70
    uint16_t GetBits(int n);            // 0x011598a0 (thiscall, ret 4)
};

class HELPER_CMpegLayer3Base : public HELPER_CMpegBase {
public:
    void SToPowerOf4over3(int n, short* in, float* out);   // 0x0116c1a0 (thiscall, ret 0xc)
};

class HELPER_CEALayer3 : public HELPER_CMpegLayer3Base {
public:
    GranuleInfo mGranuleInfo[2][2];     // +0x70
    void DecodeHuffman(int a, int b, float* out, int endBit);   // 0x0115a710 (ret 0x10)
};

static __forceinline void ScaleBatch(float* out, const short* xi, const float* xp, int cnt)
{
    int k = 0;
    if (cnt >= 4) {
        do {
            out[xi[k]] = xp[k] * out[xi[k]];
            out[xi[k + 1]] = xp[k + 1] * out[xi[k + 1]];
            out[xi[k + 2]] = xp[k + 2] * out[xi[k + 2]];
            out[xi[k + 3]] = xp[k + 3] * out[xi[k + 3]];
            k += 4;
        } while (k < cnt - 3);
    }
    for (; k < cnt; k++)
        out[xi[k]] = xp[k] * out[xi[k]];
}

// @ 0x0115a710
void HELPER_CEALayer3::DecodeHuffman(int a, int b, float* out, int endBit)
{
    const GranuleInfo* g = &mGranuleInfo[a][b];
    endBit += g->part2And3Length;
    int n = 0;
    int region1Start, region2Start;
    if (g->windowSwitchingFlag && g->blockType == 2) {
        region1Start = 36;
        region2Start = 576;
    } else {
        int base = sfreq * 30 + g->region0Count;
        region1Start = kSfbBounds[base + 1];
        region2Start = kSfbBounds[base + g->region1Count + 2];
    }
    int bigValues = g->bigValues;
    const float gain = *(kGainTable - g->globalGain);
    const float negGain = -gain;
    short idx = 0;
    short xi[32];
    __declspec(align(16)) float xp[32];
    short xv[32];
    int i = 0;
    if (bigValues * 2 > 0) {
        do {
            int tbl;
            if (i < region1Start)
                tbl = g->tableSelect[0];
            else if (i < region2Start)
                tbl = g->tableSelect[1];
            else
                tbl = g->tableSelect[2];
            int linbits = kLinbits[tbl];
            if (kHuffTables[tbl]) {
                int pos = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
                while (mShiftRegBits < 24 && pos + mShiftRegBits < endBit) {
                    mShiftReg |= (uint32_t)*mBufPtr++ << (24 - mShiftRegBits);
                    mShiftRegBits += 8;
                }
                const short* t = kHuffTables[tbl];
                int v = *t;
                while (v < 0) {
                    t++;
                    if (mShiftReg < 0)
                        t -= v;
                    mShiftRegBits += -1;
                    mShiftReg <<= 1;
                    v = *t;
                }
                int x = v >> 4;
                int y = v & 15;
                if (x == 15 && linbits)
                    x = GetBits(linbits) + 15;
                float* o = out + idx;
                if (x) {
                    *o = mShiftReg < 0 ? negGain : gain;
                    if (x < 32) {
                        *o = kPow43Small[x] * *o;
                    } else {
                        xi[n] = idx;
                        xv[n] = (short)x;
                        n++;
                        if (n >= 32) {
                            int cnt = n;
                            SToPowerOf4over3(cnt, xv, xp);
                            ScaleBatch(out, xi, xp, cnt);
                            n = 0;
                        }
                    }
                    mShiftRegBits--;
                    mShiftReg <<= 1;
                } else {
                    *o = 0.0f;
                }
                if (y == 15 && linbits)
                    y = GetBits(linbits) + 15;
                if (y) {
                    o[1] = mShiftReg < 0 ? negGain : gain;
                    if (y < 32) {
                        o[1] = kPow43Small[y] * o[1];
                    } else {
                        xi[n] = idx + 1;
                        xv[n] = (short)y;
                        n++;
                        if (n >= 32) {
                            int cnt = n;
                            SToPowerOf4over3(cnt, xv, xp);
                            ScaleBatch(out, xi, xp, cnt);
                            n = 0;
                        }
                    }
                    mShiftRegBits--;
                    mShiftReg <<= 1;
                } else {
                    o[1] = 0.0f;
                }
            } else {
                float* o = out + idx;
                o[0] = 0.0f;
                o[1] = 0.0f;
            }
            idx += 2;
            i += 2;
        } while (i < bigValues * 2);
    }
    {
        int cnt = n;
        SToPowerOf4over3(cnt, xv, xp);
        ScaleBatch(out, xi, xp, cnt);
    }
    const Count1Table* ct = &kCount1[g->count1TableSelect];
    int pos = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
    if (pos < endBit) {
        do {
            if (idx >= 0x240)
                break;
            while (mShiftRegBits < 24 && mShiftRegBits + pos < endBit) {
                mShiftReg |= (uint32_t)*mBufPtr++ << (24 - mShiftRegBits);
                mShiftRegBits += 8;
            }
            const uint8_t* e = ct->entries + ((uint32_t)mShiftReg >> ct->shift) * 2;
            mShiftRegBits -= e[1];
            mShiftReg <<= e[1];
            if (e[0] & 8) {
                out[idx] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                out[idx] = 0.0f;
            }
            if (e[0] & 4) {
                out[idx + 1] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                out[idx + 1] = 0.0f;
            }
            if (e[0] & 2) {
                out[idx + 2] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                out[idx + 2] = 0.0f;
            }
            if (e[0] & 1) {
                out[idx + 3] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                out[idx + 3] = 0.0f;
            }
            idx += 4;
            pos = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
        } while (pos < endBit);
    }
    if (pos > endBit) {
        uint32_t u = pos + (mShiftRegBits - endBit);
        mBufPtr -= u >> 3;
        mShiftRegBits = u & 7;
        if (mShiftRegBits)
            mShiftReg = mBufPtr[-1] << (32 - mShiftRegBits);
        idx -= 4;
    }
    pos = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
    if (pos < endBit)
        GetBits(endBit - pos);
    if (idx < 0x240)
        memset(out + idx, 0, (0x240 - idx) * 4);
}

}}}
