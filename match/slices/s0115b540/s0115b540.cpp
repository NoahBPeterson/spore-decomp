// Slice s0115b540: the rw::audio::core::HELPER_CMpegLayer3B decoder cluster (MPEG-1/2 Layer III).
// It owns the side-information / bit-reservoir reader at +0x20, side info at +0x150, granule info at +0x154
// and the scalefactors at +0x1b4.  The bit reader (GetBitsB 0x01134a60 / LoadBitRegisterB 0x0115b540) is the
// same MSB-first scheme as HELPER_CEALayer3 in slice s01159630.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

namespace rw { namespace audio { namespace core {

// slen1 / slen2 for each scalefac_compress value (ISO slen[2][16] tables)
extern const signed char kSlen1B[16];    // 0x014cb344
extern const signed char kSlen2B[16];    // 0x014cb354

// Group lengths of the four Huffman-table sections for every (groupSet + layout*3)
// entry (0x014cb368): four bytes each, 0x2d bytes in total.
extern "C" const uint8_t g_huffGroupLenB[];   // 0x014cb368

extern "C" void* memset(void*, int, unsigned);

struct GrInfo {                         // 0x18 bytes, one per [channel][granule]
    uint16_t part2_3_length;            // +0x00 (12 bits)
    uint16_t big_values;                // +0x02 (9 bits)
    uint16_t scalefac_compress;         // +0x04 (4 bits, 9 in LSF)
    uint8_t global_gain;                // +0x06
    uint8_t window_switching_flag;      // +0x07
    uint8_t block_type;                 // +0x08
    uint8_t mixed_block_flag;           // +0x09
    uint8_t region0_count;              // +0x0a
    uint8_t region1_count;              // +0x0b
    uint8_t table_select[3];            // +0x0c
    uint8_t count1_table_select;        // +0x0f
    uint8_t sub_block_gain[3];          // +0x10
    uint8_t pre_flag;                   // +0x13
    uint32_t scale_fac_scale;           // +0x14
};

struct SideInfo {
    uint32_t pad00;
    uint8_t scfsi[2][4];                // +0x04
};

struct ScaleFac {                       // 0x7c bytes, one per channel
    uint16_t l[23];                     // +0x00
    uint16_t s[3][13];                  // +0x2e
};

class MpegBitReaderB {
public:
    uint16_t GetBitsB(int n);            // 0x01134a60 (thiscall, ret 4)
};

inline uint16_t GetBitsZ(MpegBitReaderB* b, int n) { return n == 0 ? 0 : b->GetBitsB(n); }

class HELPER_CMpegLayer3B : public MpegBitReaderB {
public:
    char pad00[0x18];
    uint8_t mNumChannels;               // +0x18  channel count
    char pad19[5];
    uint8_t mBandOffset[2];             // +0x1e  frame header channel mode band offset
    const uint8_t* mBufPtr2;            // +0x20  next stream byte
    char pad24[8];
    uint32_t mCache;                    // +0x2c  MSB-aligned bit cache
    int mBitCount;                      // +0x30  bits held in the cache
    char pad34[7];
    uint8_t mLsf;                       // +0x3b  MPEG-2 LSF frame
    char pad3c[4];
    uint8_t mModeExt;                   // +0x40  mode extension (joint stereo)
    char pad41[3];
    uint8_t mVersion;                   // +0x44  MPEG audio version id
    char pad45[0x150 - 0x45];
    SideInfo* mSideInfo;                // +0x150
    GrInfo mGrInfo[2][2];               // +0x154  indexed [channel][granule], stride 0x18
    ScaleFac mScaleFac[2];              // +0x1b4  indexed [channel], stride 0x7c

    inline uint16_t GetBitsZB(int n) { return n == 0 ? 0 : GetBitsB(n); }

    void LoadBitRegisterB();            // 0x0115b540 (top the cache up to 24 bits)
    bool GetSideInfo(int gr);           // 0x0115b580
    void GetScaleFactorsA(int ch, int gr, uint8_t* out);   // 0x0115bfd0 (ret 0xc)
    void GetScaleFactorsB(int ch, int gr);                 // 0x0115c200 (ret 8)
    void GetScaleFactors(int ch, int gr);                  // 0x0115b910 (ret 8)
};

// ------------------------------------------------------------------ @ 0x0115b540

// @ 0x0115b540
void HELPER_CMpegLayer3B::LoadBitRegisterB()
{
    if (mBitCount > 0x18)
        return;
    do {
        unsigned int b = *mBufPtr2;
        mCache |= b << (0x18u - (unsigned int)mBitCount);
        mBufPtr2++;
        mBitCount += 8;
    } while (mBitCount <= 0x18);
}

// ------------------------------------------------------------------ @ 0x0115b580

// @ 0x0115b580
// ISO 11172-3 "III_get_side_info": reads the side information for granule gr.
//  * MPEG-1 (mLsf == 0): for gr == 1 read scfsi[ch][0..3] first; then per channel
//    read the granule fields.  The bit reader is the inlined 32-bit cache at +0x2c.
//  * MPEG-2 LSF (mLsf != 0): a single granule per channel, every field read
//    individually with GetBitsB.
bool HELPER_CMpegLayer3B::GetSideInfo(int gr)
{
    if (mLsf == 0) {
        if (gr == 1) {
            LoadBitRegisterB();
            for (int c = 0; c < mNumChannels; c++) {
                uint8_t* scfsi = mSideInfo->scfsi[c];
                scfsi[0] = (uint8_t)(mCache >> 0x1f);
                scfsi[1] = (uint8_t)((mCache >> 0x1e) & 1);
                scfsi[2] = (uint8_t)((mCache >> 0x1d) & 1);
                scfsi[3] = (uint8_t)((mCache >> 0x1c) & 1);
                mCache <<= 4;
                mBitCount -= 4;
            }
        }
        if (mNumChannels != 0) {
            GrInfo* gi = (GrInfo*)((char*)&mGrInfo[0][0] + gr * 0x18);
            int bitsLimit = 0x18;
            for (int ch = 0; ch < mNumChannels; ch++) {
                gi->part2_3_length = (uint16_t)GetBitsB(0xc);
                if (mBitCount <= bitsLimit) {
                    int bits = bitsLimit;
                    do {
                        unsigned int b = *mBufPtr2;
                        bits = mBitCount + 8;
                        mBufPtr2 = mBufPtr2 + 1;
                        mCache = mCache | (b << (0x18u - (unsigned int)mBitCount));
                        mBitCount = bits;
                    } while (bits <= bitsLimit);
                }
                gi->big_values = (uint16_t)(mCache >> 0x17);
                gi->global_gain = (uint8_t)(mCache >> 0xf);
                gi->scalefac_compress = (uint16_t)((mCache >> 0xb) & 0xf);
                gi->window_switching_flag = (uint8_t)((mCache >> 10) & 1);
                mCache <<= 0x16;
                mBitCount -= 0x16;
                if (mBitCount <= bitsLimit) {
                    int bits = bitsLimit;
                    do {
                        unsigned int b = *mBufPtr2;
                        bits = mBitCount + 8;
                        mBufPtr2 = mBufPtr2 + 1;
                        mCache = mCache | (b << (0x18u - (unsigned int)mBitCount));
                        mBitCount = bits;
                    } while (bits <= bitsLimit);
                }
                if (gi->window_switching_flag != 0) {
                    gi->block_type = (uint8_t)(mCache >> 0x1e);
                    gi->mixed_block_flag = (uint8_t)((mCache >> 0x1d) & 1);
                    gi->table_select[0] = (mCache >> 0x18) & 0x1f;
                    gi->table_select[1] = (mCache >> 0x13) & 0x1f;
                    gi->sub_block_gain[0] = (mCache >> 0x10) & 7;
                    gi->sub_block_gain[1] = (uint8_t)((mCache >> 0xd) & 7);
                    gi->sub_block_gain[2] = (uint8_t)((mCache >> 10) & 7);
                    if (gi->block_type == 0)
                        return false;
                    if (gi->block_type == 2 && gi->mixed_block_flag == 0) {
                        gi->region0_count = 8;
                    } else {
                        gi->region0_count = 7;
                    }
                    gi->region1_count = (uint8_t)(0x14 - gi->region0_count);
                } else {
                    gi->table_select[0] = (uint8_t)(mCache >> 0x1b);
                    gi->table_select[1] = (uint8_t)((mCache >> 0x16) & 0x1f);
                    gi->table_select[2] = (uint8_t)((mCache >> 0x11) & 0x1f);
                    gi->region0_count = (uint8_t)((mCache >> 0xd) & 0xf);
                    gi->region1_count = (uint8_t)((mCache >> 10) & 7);
                    gi->block_type = 0;
                }
                gi->pre_flag = (uint8_t)((mCache >> 9) & 1);
                gi->scale_fac_scale = (mCache >> 8) & 1;
                gi->count1_table_select = (uint8_t)((mCache >> 7) & 1);
                mCache <<= 0x19;
                mBitCount -= 0x19;
                gi = (GrInfo*)((char*)gi + 0x30);    // channel stride (mGrInfo[ch][gr])
            }
        }
        return true;
    }

    // MPEG-2 LSF: a single granule per channel
    {
        uint8_t ch = 0;
        if (mNumChannels != 0) {
            GrInfo* g = &mGrInfo[0][0];
            do {
                g->part2_3_length = (uint16_t)GetBitsB(0xc);
                g->big_values = (uint16_t)GetBitsB(9);
                g->global_gain = (uint8_t)GetBitsB(8);
                g->scalefac_compress = (uint16_t)GetBitsB(9);
                g->window_switching_flag = (uint8_t)GetBitsB(1);
                if (g->window_switching_flag != 0) {
                    g->block_type = (uint8_t)GetBitsB(2);
                    g->mixed_block_flag = (uint8_t)GetBitsB(1);
                    g->table_select[0] = (uint8_t)GetBitsB(5);
                    g->table_select[1] = (uint8_t)GetBitsB(5);
                    g->sub_block_gain[0] = (uint8_t)GetBitsB(3);
                    g->sub_block_gain[1] = (uint8_t)GetBitsB(3);
                    g->sub_block_gain[2] = (uint8_t)GetBitsB(3);
                    if (g->block_type == 0)
                        return false;
                    if (g->block_type == 2 && g->mixed_block_flag == 0) {
                        g->region0_count = 8;
                        g->region1_count = 12;
                    } else {
                        g->region0_count = 7;
                        g->region1_count = 13;
                    }
                } else {
                    g->table_select[0] = (uint8_t)GetBitsB(5);
                    g->table_select[1] = (uint8_t)GetBitsB(5);
                    g->table_select[2] = (uint8_t)GetBitsB(5);
                    g->region0_count = (uint8_t)GetBitsB(4);
                    g->region1_count = (uint8_t)GetBitsB(3);
                    g->block_type = 0;
                }
                g->pre_flag = (uint8_t)GetBitsB(1);
                g->scale_fac_scale = (uint32_t)GetBitsB(1);
                g->count1_table_select = (uint8_t)GetBitsB(1);
                ch++;
                g = (GrInfo*)((char*)g + 0x30);
            } while (ch < mNumChannels);
        }
    }
    return true;
}

// ------------------------------------------------------------------ @ 0x0115bfd0

// @ 0x0115bfd0
// Derives the four per-section bit widths from the granule's sfb band index (joint
// stereo coding on the second channel of the second granule shifts the layout), zero
// fills the 0x2d-byte output array, then reads the sections.
void HELPER_CMpegLayer3B::GetScaleFactorsA(int ch, int gr, uint8_t* out)
{
    unsigned int widths[4];              // bit width of each of the four sections
    uint8_t version = mVersion;
    int groupSet;

    widths[1] = 0;
    widths[2] = 0;
    widths[3] = 0;
    widths[0] = 0;

    int idx = gr + ch * 2;
    GrInfo* g = &mGrInfo[0][0] + idx;
    unsigned int b = g->scalefac_compress;
    int layout = 0;

    if (g->block_type == 2) {
        if (g->mixed_block_flag == 0)
            groupSet = 1;
        else
            groupSet = ((g->mixed_block_flag != 1) - 1) & 2;
    } else {
        groupSet = 0;
    }

    // long blocks (or the non-joint second channel): widths from the band index
    if ((version != 1 && version != 3) || ch != 1) {
        if (b < 400) {
            unsigned int n = b >> 4;
            unsigned int d = 5;
            widths[0] = n / d;
            widths[1] = n % d;
            g->pre_flag = 0;
            widths[2] = (b >> 2) & 3;
            widths[3] = b & 3;
            layout = 0;
        } else if (b < 500) {
            unsigned int n = (b - 400) >> 2;
            unsigned int d = 5;
            widths[0] = n / d;
            widths[1] = n % d;
            g->pre_flag = 0;
            layout = 1;
            widths[2] = b & 3;
            widths[3] = 0;
        } else if (b <= 0x1ff) {
            unsigned int n = b - 500;
            unsigned int d = 3;
            widths[0] = n / d;
            widths[1] = n % d;
            widths[2] = 0;
            g->pre_flag = 1;
            layout = 2;
            widths[3] = 0;
        }
    }

    // joint stereo, second channel: alternate scalefactor layout
    if ((version == 1 || version == 3) && ch == 1) {
        b = b >> 1;
        if (b < 0xb4) {
            unsigned int d36 = 0x24;
            unsigned int d6 = 6;
            widths[0] = b / d36;
            widths[1] = (b % d36) / d6;
            widths[2] = (b % d36) % d6;
            layout = 3;
        } else if (b < 0xf4) {
            widths[0] = ((b + 0xc) >> 4) & 3;
            widths[1] = ((b - 4) >> 2) & 3;
            widths[2] = b & 3;
            layout = 4;
        } else if (b <= 0xfe) {
            unsigned int n = b - 0xf4;
            unsigned int d = 3;
            widths[0] = n / d;
            widths[1] = n % d;
            widths[2] = 0;
            layout = 5;
        }
        if (layout != 0) {
            widths[3] = 0;
            g->pre_flag = 0;
        }
    }

    memset(out, 0, 0x2d);
    const uint8_t* glen = g_huffGroupLenB + (groupSet + layout * 3) * 4;
    int pos = 0;
    for (unsigned int sec = 0; sec < 4; sec++) {
        unsigned int n = glen[sec];
        for (unsigned int k = 0; k < n; k++) {
            uint8_t v = 0;
            if (widths[sec] != 0)
                v = (uint8_t)GetBitsB(widths[sec]);
            out[pos] = v;
            pos++;
        }
    }
}

// ------------------------------------------------------------------ @ 0x0115c200

// @ 0x0115c200
// Reads the scalefactors for channel ch / granule gr into the per-channel ScaleFac
// (stride 0x7c).  The layout depends on window switching: short blocks with the
// mixed-block flag store the 4x3 short window factors, the other short-block case
// stores 12x3, and the long-block case stores 21 factors plus two zeros.
void HELPER_CMpegLayer3B::GetScaleFactorsB(int ch, int gr)
{
    GrInfo* g = &mGrInfo[ch][gr];
    uint16_t* sf = (uint16_t*)&mScaleFac[ch];      // 0x7c-byte scalefactor block

    uint8_t tmp[56];
    GetScaleFactorsA(ch, gr, tmp);

    if (g->window_switching_flag != 0 && g->block_type == 2) {
        if (g->mixed_block_flag != 0) {
            // 8 long-window factors, then 9 groups of three short-window factors
            sf[0] = tmp[0];
            sf[1] = tmp[1];
            sf[2] = tmp[2];
            sf[3] = tmp[3];
            sf[4] = tmp[4];
            sf[5] = tmp[5];
            sf[6] = tmp[6];
            sf[7] = tmp[7];
            const uint8_t* src = tmp;
            int o = 9;
            uint16_t* dst = sf + 0x27;
            int n = 9;
            do {
                uint8_t v0 = src[o - 1];
                uint8_t v1 = src[o];
                uint8_t v2 = src[o + 1];
                dst[-0xd] = v0;
                dst[0] = v1;
                dst[0xd] = v2;
                o = o + 3;
                dst = dst + 1;
                n = n - 1;
            } while (n != 0);
            uint16_t* z = sf + 0x23;
            int m = 3;
            do {
                *z = 0;
                z += 0xd;
                m--;
            } while (m != 0);
        } else {
            // 12 groups of three short-window factors
            const uint8_t* src = tmp;
            uint16_t* dst = sf + 0x24;
            int n = 0xc;
            int o = 1;
            do {
                dst[-0xd] = src[o - 1];
                dst[0] = src[o];
                dst[0xd] = src[o + 1];
                o = o + 3;
                dst = dst + 1;
                n = n - 1;
            } while (n != 0);
            sf[0x23] = 0;
            sf[0x30] = 0;
            sf[0x3d] = 0;
        }
    } else {
        // 21 long-window factors, then two zero inputs
        unsigned int k = 0;
        do {
            sf[k] = tmp[k];
            k++;
        } while (k < 0x15);
        sf[0x15] = 0;
        sf[0x16] = 0;
    }
}

// ------------------------------------------------------------------ @ 0x0115b910

// @ 0x0115b910
void HELPER_CMpegLayer3B::GetScaleFactors(int ch, int gr) {
    GrInfo* g = &mGrInfo[ch][gr];
    int slen1 = kSlen1B[g->scalefac_compress];
    int slen2 = kSlen2B[g->scalefac_compress];
    ScaleFac* sf = &mScaleFac[ch];
    if (g->window_switching_flag && g->block_type == 2) {
        if (g->mixed_block_flag) {
            for (int sfb = 0; sfb < 8; sfb++)
                sf->l[sfb] = GetBitsZB(slen1);
            for (int sfb = 3; sfb < 6; sfb++)
                for (int w = 0; w < 3; w++)
                    sf->s[w][sfb] = GetBitsZB(slen1);
            for (int sfb = 6; sfb < 12; sfb++)
                for (int w = 0; w < 3; w++)
                    sf->s[w][sfb] = GetBitsZB(slen2);
        } else {
            sf->s[0][0] = GetBitsZB(slen1);
            sf->s[1][0] = GetBitsZB(slen1);
            sf->s[2][0] = GetBitsZB(slen1);
            sf->s[0][1] = GetBitsZB(slen1);
            sf->s[1][1] = GetBitsZB(slen1);
            sf->s[2][1] = GetBitsZB(slen1);
            sf->s[0][2] = GetBitsZB(slen1);
            sf->s[1][2] = GetBitsZB(slen1);
            sf->s[2][2] = GetBitsZB(slen1);
            sf->s[0][3] = GetBitsZB(slen1);
            sf->s[1][3] = GetBitsZB(slen1);
            sf->s[2][3] = GetBitsZB(slen1);
            sf->s[0][4] = GetBitsZB(slen1);
            sf->s[1][4] = GetBitsZB(slen1);
            sf->s[2][4] = GetBitsZB(slen1);
            sf->s[0][5] = GetBitsZB(slen1);
            sf->s[1][5] = GetBitsZB(slen1);
            sf->s[2][5] = GetBitsZB(slen1);
            sf->s[0][6] = GetBitsZB(slen2);
            sf->s[1][6] = GetBitsZB(slen2);
            sf->s[2][6] = GetBitsZB(slen2);
            sf->s[0][7] = GetBitsZB(slen2);
            sf->s[1][7] = GetBitsZB(slen2);
            sf->s[2][7] = GetBitsZB(slen2);
            sf->s[0][8] = GetBitsZB(slen2);
            sf->s[1][8] = GetBitsZB(slen2);
            sf->s[2][8] = GetBitsZB(slen2);
            sf->s[0][9] = GetBitsZB(slen2);
            sf->s[1][9] = GetBitsZB(slen2);
            sf->s[2][9] = GetBitsZB(slen2);
            sf->s[0][10] = GetBitsZB(slen2);
            sf->s[1][10] = GetBitsZB(slen2);
            sf->s[2][10] = GetBitsZB(slen2);
            sf->s[0][11] = GetBitsZB(slen2);
            sf->s[1][11] = GetBitsZB(slen2);
            sf->s[2][11] = GetBitsZB(slen2);
        }
        sf->s[0][12] = 0;
        sf->s[1][12] = 0;
        sf->s[2][12] = 0;
    } else {
        const uint8_t* scfsi = mSideInfo->scfsi[ch];
        if (!scfsi[0] || gr == 0) {
            sf->l[0] = GetBitsZB(slen1);
            sf->l[1] = GetBitsZB(slen1);
            sf->l[2] = GetBitsZB(slen1);
            sf->l[3] = GetBitsZB(slen1);
            sf->l[4] = GetBitsZB(slen1);
            sf->l[5] = GetBitsZB(slen1);
        }
        if (!scfsi[1] || gr == 0) {
            sf->l[6] = GetBitsZB(slen1);
            sf->l[7] = GetBitsZB(slen1);
            sf->l[8] = GetBitsZB(slen1);
            sf->l[9] = GetBitsZB(slen1);
            sf->l[10] = GetBitsZB(slen1);
        }
        if (!scfsi[2] || gr == 0) {
            sf->l[11] = GetBitsZB(slen2);
            sf->l[12] = GetBitsZB(slen2);
            sf->l[13] = GetBitsZB(slen2);
            sf->l[14] = GetBitsZB(slen2);
            sf->l[15] = GetBitsZB(slen2);
        }
        if (!scfsi[3] || gr == 0) {
            sf->l[16] = GetBitsZB(slen2);
            sf->l[17] = GetBitsZB(slen2);
            sf->l[18] = GetBitsZB(slen2);
            sf->l[19] = GetBitsZB(slen2);
            sf->l[20] = GetBitsZB(slen2);
        }
        sf->l[21] = 0;
        sf->l[22] = 0;
    }
}

}}}  // namespace rw::audio::core
