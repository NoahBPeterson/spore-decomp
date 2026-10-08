// Slice s0115b540: second copy of the MPEG layer III scalefactor reader (ISO 11172-3
// "III_get_scale_factors") in the rw::audio::core decoder; the other copy is
// HELPER_CEALayer3::GetScaleFactors (slice s01159630).  This copy sits in another decoder class
// (side info at +0x150, granule info at +0x154, scalefactors at +0x1b4, bit reader at
// 0x01134a60).  Same source shape as the sibling.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

namespace rw { namespace audio { namespace core {

// slen1 / slen2 for each scalefac_compress value (ISO slen[2][16] tables)
extern const signed char kSlen1B[16];    // 0x014cb344
extern const signed char kSlen2B[16];    // 0x014cb354

struct GrInfo {                         // 0x18 bytes, one per [channel][granule]
    uint32_t part2_3_length;            // +0x00 (unused here)
    uint16_t scalefac_compress;         // +0x04
    uint8_t pad06;
    uint8_t window_switching_flag;      // +0x07
    uint8_t block_type;                 // +0x08
    uint8_t mixed_block_flag;           // +0x09
    uint8_t rest[0x0e];
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

inline uint16_t GetBitsZB(MpegBitReaderB* b, int n) { return n == 0 ? 0 : b->GetBitsB(n); }

class HELPER_CMpegLayer3B : public MpegBitReaderB {
public:
    char pad00[0x150];
    SideInfo* mSideInfo;                // +0x150
    GrInfo mGrInfo[2][2];               // +0x154
    ScaleFac mScaleFac[2];              // +0x1b4
    void GetScaleFactors(int ch, int gr);   // 0x0115b910 (ret 8)
};

// @ 0x0115b910
void HELPER_CMpegLayer3B::GetScaleFactors(int ch, int gr) {
    GrInfo* g = &mGrInfo[ch][gr];
    int slen1 = kSlen1B[g->scalefac_compress];
    int slen2 = kSlen2B[g->scalefac_compress];
    ScaleFac* sf = &mScaleFac[ch];
    if (g->window_switching_flag && g->block_type == 2) {
        if (g->mixed_block_flag) {
            for (int sfb = 0; sfb < 8; sfb++)
                sf->l[sfb] = GetBitsZB(this, slen1);
            for (int sfb = 3; sfb < 6; sfb++)
                for (int w = 0; w < 3; w++)
                    sf->s[w][sfb] = GetBitsZB(this, slen1);
            for (int sfb = 6; sfb < 12; sfb++)
                for (int w = 0; w < 3; w++)
                    sf->s[w][sfb] = GetBitsZB(this, slen2);
        } else {
            sf->s[0][0] = GetBitsZB(this, slen1);
            sf->s[1][0] = GetBitsZB(this, slen1);
            sf->s[2][0] = GetBitsZB(this, slen1);
            sf->s[0][1] = GetBitsZB(this, slen1);
            sf->s[1][1] = GetBitsZB(this, slen1);
            sf->s[2][1] = GetBitsZB(this, slen1);
            sf->s[0][2] = GetBitsZB(this, slen1);
            sf->s[1][2] = GetBitsZB(this, slen1);
            sf->s[2][2] = GetBitsZB(this, slen1);
            sf->s[0][3] = GetBitsZB(this, slen1);
            sf->s[1][3] = GetBitsZB(this, slen1);
            sf->s[2][3] = GetBitsZB(this, slen1);
            sf->s[0][4] = GetBitsZB(this, slen1);
            sf->s[1][4] = GetBitsZB(this, slen1);
            sf->s[2][4] = GetBitsZB(this, slen1);
            sf->s[0][5] = GetBitsZB(this, slen1);
            sf->s[1][5] = GetBitsZB(this, slen1);
            sf->s[2][5] = GetBitsZB(this, slen1);
            sf->s[0][6] = GetBitsZB(this, slen2);
            sf->s[1][6] = GetBitsZB(this, slen2);
            sf->s[2][6] = GetBitsZB(this, slen2);
            sf->s[0][7] = GetBitsZB(this, slen2);
            sf->s[1][7] = GetBitsZB(this, slen2);
            sf->s[2][7] = GetBitsZB(this, slen2);
            sf->s[0][8] = GetBitsZB(this, slen2);
            sf->s[1][8] = GetBitsZB(this, slen2);
            sf->s[2][8] = GetBitsZB(this, slen2);
            sf->s[0][9] = GetBitsZB(this, slen2);
            sf->s[1][9] = GetBitsZB(this, slen2);
            sf->s[2][9] = GetBitsZB(this, slen2);
            sf->s[0][10] = GetBitsZB(this, slen2);
            sf->s[1][10] = GetBitsZB(this, slen2);
            sf->s[2][10] = GetBitsZB(this, slen2);
            sf->s[0][11] = GetBitsZB(this, slen2);
            sf->s[1][11] = GetBitsZB(this, slen2);
            sf->s[2][11] = GetBitsZB(this, slen2);
        }
        sf->s[0][12] = 0;
        sf->s[1][12] = 0;
        sf->s[2][12] = 0;
    } else {
        const uint8_t* scfsi = mSideInfo->scfsi[ch];
        if (!scfsi[0] || gr == 0) {
            sf->l[0] = GetBitsZB(this, slen1);
            sf->l[1] = GetBitsZB(this, slen1);
            sf->l[2] = GetBitsZB(this, slen1);
            sf->l[3] = GetBitsZB(this, slen1);
            sf->l[4] = GetBitsZB(this, slen1);
            sf->l[5] = GetBitsZB(this, slen1);
        }
        if (!scfsi[1] || gr == 0) {
            sf->l[6] = GetBitsZB(this, slen1);
            sf->l[7] = GetBitsZB(this, slen1);
            sf->l[8] = GetBitsZB(this, slen1);
            sf->l[9] = GetBitsZB(this, slen1);
            sf->l[10] = GetBitsZB(this, slen1);
        }
        if (!scfsi[2] || gr == 0) {
            sf->l[11] = GetBitsZB(this, slen2);
            sf->l[12] = GetBitsZB(this, slen2);
            sf->l[13] = GetBitsZB(this, slen2);
            sf->l[14] = GetBitsZB(this, slen2);
            sf->l[15] = GetBitsZB(this, slen2);
        }
        if (!scfsi[3] || gr == 0) {
            sf->l[16] = GetBitsZB(this, slen2);
            sf->l[17] = GetBitsZB(this, slen2);
            sf->l[18] = GetBitsZB(this, slen2);
            sf->l[19] = GetBitsZB(this, slen2);
            sf->l[20] = GetBitsZB(this, slen2);
        }
        sf->l[21] = 0;
        sf->l[22] = 0;
    }
}

}}}  // namespace rw::audio::core
