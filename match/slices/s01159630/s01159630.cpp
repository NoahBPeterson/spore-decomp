// Slice s01159630: rw::audio::core::HELPER_CEALayer3 scalefactor reader (ISO 11172-3 "III_get_scale_factors").
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

namespace rw { namespace audio { namespace core {

// slen1 / slen2 for each scalefac_compress value (ISO slen[2][16] tables)
extern const signed char kSlen1[16];    // 0x014d9fd4
extern const signed char kSlen2[16];    // 0x014d9fe4

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

class HELPER_CMpegBase {
public:
    uint16_t GetBits(int n);            // 0x011598a0 (thiscall, ret 4)
};

inline uint16_t GetBitsZ(HELPER_CMpegBase* b, int n) { return n == 0 ? 0 : b->GetBits(n); }

class HELPER_CEALayer3 : public HELPER_CMpegBase {
public:
    char pad00[0x6c];
    SideInfo* mSideInfo;                // +0x6c
    GrInfo mGrInfo[2][2];               // +0x70
    ScaleFac mScaleFac[2];              // +0xd0
    void GetScaleFactors(int ch, int gr);   // 0x01159cc0 (ret 8)
};

// @ 0x01159cc0
void HELPER_CEALayer3::GetScaleFactors(int ch, int gr) {
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
