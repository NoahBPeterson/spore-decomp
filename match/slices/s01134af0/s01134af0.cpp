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

// ---------------------------------------------------------------------------------------------
// The raw bit reservoir the side-information reader pulls from. It is a 0x800-byte ring buffer:
// a 32-bit cache of the next bits (left aligned), the count still valid, the read cursor and the
// byte storage. (The reader object handed to it sits at owner+0x34; its own GetBits models the
// same idea with a linear pointer.)
// ---------------------------------------------------------------------------------------------
struct BitReservoir {
    char pad00[4];
    uint32_t mBitPos;            // +0x04
    int mBitsInCache;            // +0x08
    uint32_t mCache;             // +0x0c
    uint8_t mData[0x800];        // +0x10
    uint32_t GetBits(unsigned n);
};

// @ 0x01134af0
uint32_t BitReservoir::GetBits(unsigned n)
{
    uint32_t result = 0;
    if (n > 0) {
        while (true) {
            if (mBitsInCache == 0) {
                mCache = (uint32_t)mData[mBitPos & 0x7ff] << 24;
                mBitPos++;
                mBitsInCache = 8;
            }
            int avail = mBitsInCache;
            if (n < (unsigned)avail) {
                result = (mCache >> (32 - n)) | (result << n);
                mCache <<= n;
                mBitsInCache -= (int)n;
                break;
            }
            result = (result << avail) | (mCache >> (32 - avail));
            mBitsInCache = 0;
            n -= (unsigned)avail;
            if (n == 0)
                break;
        }
    }
    return result;
}

// ---------------------------------------------------------------------------------------------
// Scalefactor reader (ISO 11172-3 "III_get_scalefactors") on the same decoder object: side info
// at +0x184, the per-[channel][granule] gr info at +0x188, the 62-short scalefactor band array
// per channel at +0x1e8 and the bit reservoir at +0x2710. slen1/slen2 come from the
// scalefac_compress-indexed tables at 0x014cb344 / 0x014cb354.
// ---------------------------------------------------------------------------------------------
extern const signed char DAT_014cb344[];    // slen1 table (0x014cb344)
extern const signed char DAT_014cb354[];    // slen2 table (0x014cb354)
extern const unsigned char DAT_014cb368[];  // scalefactor-band count table (0x014cb368)
extern "C" void* __cdecl MemZero(void* p, int v, unsigned n);   // 0x011e073e

struct MpegScalefacDecoder {
    char pad00[0x184];
    SideInfo* mSideInfo;            // +0x184
    GrInfo mGrInfo[2][2];           // +0x188
    int16_t mScalefac[2][0x3e];     // +0x1e8 (0x7c bytes per channel)
    char pad2e0[0x2710 - 0x2e0];
    BitReservoir mReservoir;        // +0x2710
    int mUberBits;                  // +0x2714 (bit offset into the frame)

    void ReadScalefactors(int ch, int gr);        // 0x01135350
    void ReadScalefactorsInto(int ch, int gr, uint8_t* dst);  // 0x011357f0
};

// @ 0x01135350
void MpegScalefacDecoder::ReadScalefactors(int ch, int gr)
{
    GrInfo* gi = &mGrInfo[ch][gr];
    int slen1 = DAT_014cb344[gi->scalefac_compress];
    int slen2 = DAT_014cb354[gi->scalefac_compress];
    int16_t* sf = mScalefac[ch];
    BitReservoir* br = &mReservoir;

    if (gi->window_switching_flag && gi->block_type == 2) {
        if (gi->mixed_block_flag) {
            for (int i = 0; i < 8; i++)
                sf[i] = (int16_t)br->GetBits(slen1);
            int16_t* p0 = sf + 0x1a;
            for (int j = 0; j < 3; j++) {
                int16_t* p1 = p0;
                for (int k = 0; k < 3; k++) {
                    *p1 = (int16_t)br->GetBits(slen1);
                    p1 += 13;
                }
                p0 += 1;
            }
            int16_t* p2 = sf + 0x1d;
            for (int j = 0; j < 6; j++) {
                int16_t* p1 = p2;
                for (int k = 0; k < 3; k++) {
                    *p1 = (int16_t)br->GetBits(slen2);
                    p1 += 13;
                }
                p2 += 1;
            }
            int16_t* p3 = sf + 0x23;
            for (int k = 0; k < 3; k++) {
                *p3 = 0;
                p3 += 13;
            }
        } else {
            int16_t* p0 = sf + 0x17;
            for (int j = 0; j < 6; j++) {
                int16_t* p1 = p0;
                for (int k = 0; k < 3; k++) {
                    *p1 = (int16_t)br->GetBits(slen1);
                    p1 += 13;
                }
                p0 += 1;
            }
            int16_t* p2 = sf + 0x1d;
            for (int j = 0; j < 6; j++) {
                int16_t* p1 = p2;
                for (int k = 0; k < 3; k++) {
                    *p1 = (int16_t)br->GetBits(slen2);
                    p1 += 13;
                }
                p2 += 1;
            }
            int16_t* p3 = sf + 0x23;
            for (int k = 0; k < 3; k++) {
                *p3 = 0;
                p3 += 13;
            }
        }
    } else {
        if (mSideInfo->scfsi[ch][0] == 0 || gr == 0) {
            sf[0] = (int16_t)br->GetBits(slen1);
            sf[1] = (int16_t)br->GetBits(slen1);
            sf[2] = (int16_t)br->GetBits(slen1);
            sf[3] = (int16_t)br->GetBits(slen1);
            sf[4] = (int16_t)br->GetBits(slen1);
            sf[5] = (int16_t)br->GetBits(slen1);
        }
        if (mSideInfo->scfsi[ch][1] == 0 || gr == 0) {
            sf[6] = (int16_t)br->GetBits(slen1);
            sf[7] = (int16_t)br->GetBits(slen1);
            sf[8] = (int16_t)br->GetBits(slen1);
            sf[9] = (int16_t)br->GetBits(slen1);
            sf[10] = (int16_t)br->GetBits(slen1);
        }
        if (mSideInfo->scfsi[ch][2] == 0 || gr == 0) {
            sf[11] = (int16_t)br->GetBits(slen2);
            sf[12] = (int16_t)br->GetBits(slen2);
            sf[13] = (int16_t)br->GetBits(slen2);
            sf[14] = (int16_t)br->GetBits(slen2);
            sf[15] = (int16_t)br->GetBits(slen2);
        }
        if (mSideInfo->scfsi[ch][3] == 0 || gr == 0) {
            sf[16] = (int16_t)br->GetBits(slen2);
            sf[17] = (int16_t)br->GetBits(slen2);
            sf[18] = (int16_t)br->GetBits(slen2);
            sf[19] = (int16_t)br->GetBits(slen2);
            sf[20] = (int16_t)br->GetBits(slen2);
        }
        sf[0x15] = 0;
        sf[0x16] = 0;
    }
}

// @ 0x011357f0
void MpegScalefacDecoder::ReadScalefactorsInto(int ch, int gr, uint8_t* dst)
{
    int blockType = mGrInfo[ch][gr].block_type;
    uint32_t compress = *(uint16_t*)((char*)&mGrInfo[ch][gr] + 4);
    int sel = 0;
    uint32_t part[4];
    part[0] = 0;
    part[1] = 0;
    part[2] = 0;
    part[3] = 0;

    if (mGrInfo[ch][gr].block_type == 2) {
        if (mGrInfo[ch][gr].mixed_block_flag == 0)
            gr = 1;
        else
            gr = (mGrInfo[ch][gr].mixed_block_flag != 1) - 1 & 2;
    } else {
        gr = 0;
    }

    if (!((blockType == 1 || blockType == 3) && ch == 1)) {
        if (compress < 400) {
            part[0] = (compress >> 4) / 5;
            part[1] = (compress >> 4) % 5;
            mGrInfo[ch][gr].preflag = 0;
            part[2] = compress >> 2 & 3;
            part[3] = compress & 3;
            sel = 0;
        } else if (compress < 500) {
            part[1] = (compress - 400) >> 2;
            part[0] = part[1] / 5;
            part[1] = part[1] % 5;
            mGrInfo[ch][gr].preflag = 0;
            sel = 1;
            part[2] = compress & 3;
            part[3] = 0;
        } else if (compress <= 0x1ff) {
            part[0] = (compress - 500) / 3;
            part[1] = (compress - 500) % 3;
            part[2] = 0;
            mGrInfo[ch][gr].preflag = 1;
            sel = 2;
            part[3] = 0;
        }
    }

    if ((blockType == 1 || blockType == 3) && ch == 1) {
        compress >>= 1;
        if (compress < 0xb4) {
            part[0] = compress / 0x24;
            part[1] = (compress % 0x24) / 6;
            part[2] = (compress % 0x24) % 6;
            sel = 3;
        } else if (compress < 0xf4) {
            part[0] = (compress + 0xc) >> 4 & 3;
            part[1] = (compress - 4) >> 2 & 3;
            part[2] = compress & 3;
            sel = 4;
        } else if (compress <= 0xfe) {
            part[0] = (compress - 0xf4) / 3;
            part[1] = (compress - 0xf4) % 3;
            part[2] = 0;
            sel = 5;
        }
        part[3] = 0;
        mGrInfo[ch][gr].preflag = 0;
    }

    MemZero(dst, 0, 0x2d);

    const uint8_t* bands = &DAT_014cb368[(gr + sel * 3) * 4];
    int n = 0;
    for (int i = 0; i < 4; i++) {
        unsigned cnt = bands[i];
        for (unsigned k = 0; k < cnt; k++) {
            uint8_t v = 0;
            if (part[i] != 0)
                v = (uint8_t)mReservoir.GetBits(part[i]);
            dst[n] = v;
            n++;
        }
    }
}

}}}  // namespace rw::audio::core
