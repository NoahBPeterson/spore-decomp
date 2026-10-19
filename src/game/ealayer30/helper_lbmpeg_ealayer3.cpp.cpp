// src/game/ealayer30/helper_lbmpeg_ealayer3.cpp.cpp -- migrated from slice(s) s0115a5b0, s01159630 by tools/migrate/rewrite.py
// Object file: ealayer30/helper_lbmpeg_ealayer3.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s01159630 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
extern const signed char kSlen1[16];    // 0x014d9fd4
}
}
}
namespace rw {
namespace audio {
namespace core {
extern const signed char kSlen2[16];    // 0x014d9fe4
}
}
}
namespace rw {
namespace audio {
namespace core {
struct GrInfo {                         // 0x18 bytes, one per [channel][granule]
    uint32_t part2_3_length;            // +0x00 (unused here)
    uint16_t scalefac_compress;         // +0x04
    uint8_t pad06;
    uint8_t window_switching_flag;      // +0x07
    uint8_t block_type;                 // +0x08
    uint8_t mixed_block_flag;           // +0x09
    uint8_t rest[0x0e];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct SideInfo {
    uint32_t pad00;
    uint8_t scfsi[2][4];                // +0x04
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct ScaleFac {                       // 0x7c bytes, one per channel
    uint16_t l[23];                     // +0x00
    uint16_t s[3][13];                  // +0x2e
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CMpegBase {
public:
    uint16_t GetBits(int n);            // 0x011598a0 (thiscall, ret 4)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
inline uint16_t GetBitsZ(HELPER_CMpegBase* b, int n) { return n == 0 ? 0 : b->GetBits(n); }
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CEALayer3 : public HELPER_CMpegBase {
public:
    char pad00[0x6c];
    SideInfo* mSideInfo;                // +0x6c
    GrInfo mGrInfo[2][2];               // +0x70
    ScaleFac mScaleFac[2];              // +0xd0
    void GetScaleFactors(int ch, int gr);   // 0x01159cc0 (ret 8)
};
}
}
}
// ---- items of slice s01159630 end

// ---- items of slice s0115a5b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
extern const float  kGainTable[];       // 0x014da454 (indexed by -global_gain)
}
}
}
namespace rw {
namespace audio {
namespace core {
extern const short  kSfbBounds[];       // 0x014da570 (sfreq*30 + region index)
}
}
}
namespace rw {
namespace audio {
namespace core {
extern const float  kPow43Small[32];    // 0x014da4f0
}
}
}
namespace rw {
namespace audio {
namespace core {
extern const short* const kHuffTables[];// 0x014dc190 (null = table with no codes)
}
}
}
namespace rw {
namespace audio {
namespace core {
extern const uint8_t kLinbits[];        // 0x014dc210
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Count1Table {                    // 8 bytes, at 0x014dc2d0
    const uint8_t* entries;             // +0 pairs of (flags, length)
    uint16_t pad4;
    uint8_t shift;                      // +6
    uint8_t pad7;
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern const Count1Table kCount1[];
}
}
}
namespace rw {
namespace audio {
namespace core {
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
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CMpegBase_s0115_a5b0 {
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
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CMpegLayer3Base : public HELPER_CMpegBase_s0115_a5b0 {
public:
    void SToPowerOf4over3(int n, short* in, float* out);   // 0x0116c1a0 (thiscall, ret 0xc)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CEALayer3_s0115_a5b0 : public HELPER_CMpegLayer3Base {
public:
    GranuleInfo mGranuleInfo[2][2];     // +0x70
    void DecodeHuffman(int a, int b, float* out, int endBit);   // 0x0115a710 (ret 0x10)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
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
}
}
}
// ---- items of slice s0115a5b0 end

// @ 0x01159cc0
namespace rw { namespace audio { namespace core {
void HELPER_CEALayer3::GetScaleFactors(int ch, int gr)
{
    GrInfo* g = &mGrInfo[ch][gr];
    int slen1 = kSlen1[g->scalefac_compress];
    int slen2 = kSlen2[g->scalefac_compress];
    ScaleFac* sf = &mScaleFac[ch];
    if (g->window_switching_flag && g->block_type == 2) {
        if (g->mixed_block_flag) {
            for (int sfb = 0; sfb < 8; sfb++)
                sf->l[sfb] = GetBitsZ(this, slen1);
            for (int sfb = 3; sfb < 6; sfb++)
                for (int w = 0; w < 3; w++)
                    sf->s[w][sfb] = GetBitsZ(this, slen1);
            for (int sfb = 6; sfb < 12; sfb++)
                for (int w = 0; w < 3; w++)
                    sf->s[w][sfb] = GetBitsZ(this, slen2);
        } else {
            sf->s[0][0] = GetBitsZ(this, slen1);
            sf->s[1][0] = GetBitsZ(this, slen1);
            sf->s[2][0] = GetBitsZ(this, slen1);
            sf->s[0][1] = GetBitsZ(this, slen1);
            sf->s[1][1] = GetBitsZ(this, slen1);
            sf->s[2][1] = GetBitsZ(this, slen1);
            sf->s[0][2] = GetBitsZ(this, slen1);
            sf->s[1][2] = GetBitsZ(this, slen1);
            sf->s[2][2] = GetBitsZ(this, slen1);
            sf->s[0][3] = GetBitsZ(this, slen1);
            sf->s[1][3] = GetBitsZ(this, slen1);
            sf->s[2][3] = GetBitsZ(this, slen1);
            sf->s[0][4] = GetBitsZ(this, slen1);
            sf->s[1][4] = GetBitsZ(this, slen1);
            sf->s[2][4] = GetBitsZ(this, slen1);
            sf->s[0][5] = GetBitsZ(this, slen1);
            sf->s[1][5] = GetBitsZ(this, slen1);
            sf->s[2][5] = GetBitsZ(this, slen1);
            sf->s[0][6] = GetBitsZ(this, slen2);
            sf->s[1][6] = GetBitsZ(this, slen2);
            sf->s[2][6] = GetBitsZ(this, slen2);
            sf->s[0][7] = GetBitsZ(this, slen2);
            sf->s[1][7] = GetBitsZ(this, slen2);
            sf->s[2][7] = GetBitsZ(this, slen2);
            sf->s[0][8] = GetBitsZ(this, slen2);
            sf->s[1][8] = GetBitsZ(this, slen2);
            sf->s[2][8] = GetBitsZ(this, slen2);
            sf->s[0][9] = GetBitsZ(this, slen2);
            sf->s[1][9] = GetBitsZ(this, slen2);
            sf->s[2][9] = GetBitsZ(this, slen2);
            sf->s[0][10] = GetBitsZ(this, slen2);
            sf->s[1][10] = GetBitsZ(this, slen2);
            sf->s[2][10] = GetBitsZ(this, slen2);
            sf->s[0][11] = GetBitsZ(this, slen2);
            sf->s[1][11] = GetBitsZ(this, slen2);
            sf->s[2][11] = GetBitsZ(this, slen2);
        }
        sf->s[0][12] = 0;
        sf->s[1][12] = 0;
        sf->s[2][12] = 0;
    } else {
        const uint8_t* scfsi = mSideInfo->scfsi[ch];
        if (!scfsi[0] || gr == 0) {
            sf->l[0] = GetBitsZ(this, slen1);
            sf->l[1] = GetBitsZ(this, slen1);
            sf->l[2] = GetBitsZ(this, slen1);
            sf->l[3] = GetBitsZ(this, slen1);
            sf->l[4] = GetBitsZ(this, slen1);
            sf->l[5] = GetBitsZ(this, slen1);
        }
        if (!scfsi[1] || gr == 0) {
            sf->l[6] = GetBitsZ(this, slen1);
            sf->l[7] = GetBitsZ(this, slen1);
            sf->l[8] = GetBitsZ(this, slen1);
            sf->l[9] = GetBitsZ(this, slen1);
            sf->l[10] = GetBitsZ(this, slen1);
        }
        if (!scfsi[2] || gr == 0) {
            sf->l[11] = GetBitsZ(this, slen2);
            sf->l[12] = GetBitsZ(this, slen2);
            sf->l[13] = GetBitsZ(this, slen2);
            sf->l[14] = GetBitsZ(this, slen2);
            sf->l[15] = GetBitsZ(this, slen2);
        }
        if (!scfsi[3] || gr == 0) {
            sf->l[16] = GetBitsZ(this, slen2);
            sf->l[17] = GetBitsZ(this, slen2);
            sf->l[18] = GetBitsZ(this, slen2);
            sf->l[19] = GetBitsZ(this, slen2);
            sf->l[20] = GetBitsZ(this, slen2);
        }
        sf->l[21] = 0;
        sf->l[22] = 0;
    }
}
}}}  // namespace rw::audio::core

// @ 0x0115a710
namespace rw { namespace audio { namespace core {
void HELPER_CEALayer3_s0115_a5b0::DecodeHuffman(int a, int b, float* out, int endBit)
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
                *(int*)&out[idx] = 0;
            }
            if (e[0] & 4) {
                out[idx + 1] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                *(int*)&out[idx + 1] = 0;
            }
            if (e[0] & 2) {
                out[idx + 2] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                *(int*)&out[idx + 2] = 0;
            }
            if (e[0] & 1) {
                out[idx + 3] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                *(int*)&out[idx + 3] = 0;
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
}}}  // namespace rw::audio::core
