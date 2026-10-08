// Slice s01134af0: MPEG layer III side-information reader (ISO 11172-3 "III_get_side_info") in the
// rw::audio::core decoder whose bit reader sits at +0x34 (granule info at +0x188; same sub-object layout
// as HELPER_CMpegLayer3B in slice s0115b540, whose side info is at +0x150).
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

namespace rw { namespace audio { namespace core {

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
    uint8_t count1table_select;         // +0x0f
    uint8_t subblock_gain[3];           // +0x10
    uint8_t preflag;                    // +0x13
    uint32_t scalefac_scale;            // +0x14
};

struct SideInfo {
    uint32_t main_data_begin;           // +0x00
    uint8_t scfsi[2][4];                // +0x04
};

// MSB-first bit reader: the cache holds the next bits left-aligned (same body as 0x01134a60).
// Offsets are relative to the reader, which sits at +0x34 in the owning decoder.
class MpegBitReader {
public:
    char pad00[0x18];
    uint8_t mNumChannels;               // +0x18 (owner +0x4c)
    char pad19[7];
    const uint8_t* mpData;              // +0x20
    char pad24[8];
    uint32_t mCache;                    // +0x2c
    int mBitsInCache;                   // +0x30
    char pad34[7];
    uint8_t mLsf;                       // +0x3b (owner +0x6f): MPEG-2 LSF frame
    char pad3c[0x150 - 0x3c];
    SideInfo* mSideInfo;                // +0x150 (owner +0x184)
    GrInfo mGrInfo[2][2];               // +0x154 (owner +0x188), indexed [channel][granule]

    uint32_t GetBits(int n)
    {
        while (mBitsInCache < n) {
            mCache |= (uint32_t)(*mpData++) << (24 - mBitsInCache);
            mBitsInCache += 8;
        }
        uint32_t v = mCache >> (32 - n);
        mBitsInCache -= n;
        mCache <<= n;
        return v;
    }
};

struct DecoderHeader { char pad00[0x34]; };

class MpegLayer3Owner : public DecoderHeader, public MpegBitReader {
public:
    bool ReadSideInfo();                // 0x01134b70 (thiscall)
};

// @ 0x01134b70
bool MpegLayer3Owner::ReadSideInfo()
{
    if (!mLsf) {
        mSideInfo->main_data_begin = GetBits(9);
        if (mNumChannels == 1) GetBits(5);
        else GetBits(3);
        for (int ch = 0; ch < mNumChannels; ch++) {
            mSideInfo->scfsi[ch][0] = (uint8_t)GetBits(1);
            mSideInfo->scfsi[ch][1] = (uint8_t)GetBits(1);
            mSideInfo->scfsi[ch][2] = (uint8_t)GetBits(1);
            mSideInfo->scfsi[ch][3] = (uint8_t)GetBits(1);
        }
        for (int gr = 0; gr < 2; gr++) {
            for (int ch = 0; ch < mNumChannels; ch++) {
                GrInfo* g = &mGrInfo[ch][gr];
                g->part2_3_length = (uint16_t)GetBits(12);
                g->big_values = (uint16_t)GetBits(9);
                g->global_gain = (uint8_t)GetBits(8);
                g->scalefac_compress = (uint16_t)GetBits(4);
                g->window_switching_flag = (uint8_t)GetBits(1);
                uint8_t region1;
                if (g->window_switching_flag) {
                    g->block_type = (uint8_t)GetBits(2);
                    g->mixed_block_flag = (uint8_t)GetBits(1);
                    g->table_select[0] = (uint8_t)GetBits(5);
                    g->table_select[1] = (uint8_t)GetBits(5);
                    g->subblock_gain[0] = (uint8_t)GetBits(3);
                    g->subblock_gain[1] = (uint8_t)GetBits(3);
                    g->subblock_gain[2] = (uint8_t)GetBits(3);
                    if (g->block_type == 0) return false;
                    if (g->block_type == 2 && g->mixed_block_flag == 0)
                        g->region0_count = 8;
                    else
                        g->region0_count = 7;
                    region1 = (uint8_t)(20 - g->region0_count);
                } else {
                    g->table_select[0] = (uint8_t)GetBits(5);
                    g->table_select[1] = (uint8_t)GetBits(5);
                    g->table_select[2] = (uint8_t)GetBits(5);
                    g->region0_count = (uint8_t)GetBits(4);
                    region1 = (uint8_t)GetBits(3);
                    g->block_type = 0;
                    g->mixed_block_flag = 0;
                }
                g->region1_count = region1;
                g->preflag = (uint8_t)GetBits(1);
                g->scalefac_scale = GetBits(1);
                g->count1table_select = (uint8_t)GetBits(1);
            }
        }
        return true;
    }

    // MPEG-2 LSF: a single granule per channel
    mSideInfo->main_data_begin = GetBits(8);
    if (mNumChannels == 1) GetBits(1);
    else GetBits(2);
    for (int ch = 0; ch < mNumChannels; ch++) {
        GrInfo* g = &mGrInfo[ch][0];
        g->part2_3_length = (uint16_t)GetBits(12);
        g->big_values = (uint16_t)GetBits(9);
        g->global_gain = (uint8_t)GetBits(8);
        g->scalefac_compress = (uint16_t)GetBits(9);
        g->window_switching_flag = (uint8_t)GetBits(1);
        if (g->window_switching_flag) {
            g->block_type = (uint8_t)GetBits(2);
            g->mixed_block_flag = (uint8_t)GetBits(1);
            g->table_select[0] = (uint8_t)GetBits(5);
            g->table_select[1] = (uint8_t)GetBits(5);
            g->subblock_gain[0] = (uint8_t)GetBits(3);
            g->subblock_gain[1] = (uint8_t)GetBits(3);
            g->subblock_gain[2] = (uint8_t)GetBits(3);
            if (g->block_type == 0) return false;
            if (g->block_type == 2 && g->mixed_block_flag == 0) {
                g->region0_count = 8;
            } else {
                g->region0_count = 7;
                g->region1_count = 13;
            }
        } else {
            g->table_select[0] = (uint8_t)GetBits(5);
            g->table_select[1] = (uint8_t)GetBits(5);
            g->table_select[2] = (uint8_t)GetBits(5);
            g->region0_count = (uint8_t)GetBits(4);
            g->region1_count = (uint8_t)GetBits(3);
            g->block_type = 0;
            g->mixed_block_flag = 0;
        }
        g->scalefac_scale = GetBits(1);
        g->count1table_select = (uint8_t)GetBits(1);
    }
    return true;
}

}}}  // namespace rw::audio::core
