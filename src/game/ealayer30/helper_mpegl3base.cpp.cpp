// src/game/ealayer30/helper_mpegl3base.cpp.cpp -- migrated from slice(s) s0116efb0, s0116e4f0, s0116c750, s01145d10 by tools/migrate/rewrite.py
// Object file: ealayer30/helper_mpegl3base.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" const float    g_imdct12Coef[];     // 0x014cbab0 IMDCT12 constants
extern "C" const float    g_imdct36Win[];      // 0x014cb7d0 IMDCT36 windows / tfcos
#include <string.h>
#include <malloc.h>
#include <xmmintrin.h>

// ---- items of slice s01145d10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const float    g_imdct12Coef[];     // 0x014cbab0 IMDCT12 constants
extern "C" const float    g_imdct36Win[];      // 0x014cb7d0 IMDCT36 windows / tfcos
namespace rw {
namespace audio {
namespace core {
struct GranuleInfo {                            // size 0x18
    uint16_t part2And3Length;                   // +0x00
    uint16_t bigValues;                         // +0x02
    uint16_t scaleFacCompress;                  // +0x04
    uint8_t  globalGain;                        // +0x06
    uint8_t  windowSwitchingFlag;               // +0x07
    uint8_t  blockType;                         // +0x08
    uint8_t  mixedBlockFlag;                    // +0x09
    uint8_t  region0Count;                      // +0x0a
    uint8_t  region1Count;                      // +0x0b
    uint8_t  tableSelect[3];                    // +0x0c
    uint8_t  count1TableSelect;                 // +0x0f
    uint8_t  subBlockGain[3];                   // +0x10
    uint8_t  preFlag;                           // +0x13
    uint32_t scaleFacScale;                     // +0x14
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct HuffTable {                              // size 8
    uint16_t tableSize;                         // +0x0
    uint16_t pad02;
    int16_t* pEntries;                          // +0x4
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class CMpegLayer3Base {
public:
    uint8_t  pad00[0x3c];
    uint8_t  sfreq;                             // +0x3c
    uint8_t  pad3d[0x50 - 0x3d];
    HuffTable mHuffTables[32];                  // +0x50 .. +0x14f
    uint8_t  pad150[4];
    GranuleInfo mGranuleInfo[2][2];             // +0x154
    uint8_t  pad1b4[0x2c4 - 0x1b4];
    float*   mpLoadedPrevBlockX4;               // +0x2c4

    void Reorder(int gr, int ch, float* src, float* dst);   // 0x01145d10
    void Antialias(int gr, int ch, float* xr);              // 0x01146200
    void Imdct36X4(int gr, int ch, float* xr);              // 0x011467f0
    void InitHuffTables();                                  // 0x01146a90
};
}
}
}
namespace rw {
namespace audio {
namespace core {
void Imdct12X1Local(float* in, float* out);                                 // local body copy
}
}
}
namespace rw {
namespace audio {
namespace core {
void __fastcall HELPER_Imdct36X1(const float* win, float* out, float* in);  // 0x0116e4f0
}
}
}
namespace rw {
namespace audio {
namespace core {
void HELPER_Imdct36X4Implementation(float* in, float* out, const float* tbl);// 0x0116efb0
}
}
}
namespace rw {
namespace audio {
namespace core {
void HELPER_Imdct12X4(float* in, float* out);                               // 0x011464a0
}
}
}
namespace rw {
namespace audio {
namespace core {
void HELPER_OverlapAddX4(float* in, float* tmp, float* out);                // 0x0116f960
}
}
}
namespace rw {
namespace audio {
namespace core {
void Imdct12X1Local(float* in, float* out)
{
    // Zero only this lane's slots: 36 floats at stride 4 (the original's strided zero loop).
    for (int k = 0; k < 36; k++)
        out[4 * k] = 0.0f;
    for (int w = 0; w < 3; w++) {
        float* p = in + 4 * w;
        float A = p[0x00];
        float B = p[0x0c];
        float C = p[0x18];
        float D = p[0x24];
        float E = p[0x30];
        float F = p[0x3c];
        // in-place prefix sums (no re-read of the overwritten slots)
        p[0x0c] = A + B;
        p[0x18] = C + B;
        p[0x3c] = E + F;
        p[0x30] = E + D;
        p[0x24] = (A + B) + (C + D);
        float u5 = (C + D) + (E + F);
        p[0x3c] = u5;

        float v26 = (E + D) * 0.5f + A;
        float v14 = (C + B) * 0.8660254f;
        float t33 = v26 - v14;
        float t34 = v26 + v14;
        float W   = u5 * 0.5f + (A + B);
        float vX  = ((A + B) - u5) * 0.70710677f;
        float t44 = ((A + B) + (C + D)) * 0.8660254f;
        float t46 = W - t44;
        float t47 = W + t44;
        float t48 = t46 * 1.9318516f;
        float t49 = t47 * 0.5176381f;
        float t53 = t34 - t49;
        float t58 = (t49 + t34) * 0.50431448f;
        float t56 = t53 * 3.8306489f;
        float t61 = (vX + (A - (E + D))) * 0.54119611f;
        float t64 = ((A - (E + D)) - vX) * 1.306563f;
        float t68 = (t48 + t33) * 0.63023621f;
        float t81 = (t33 - t48) * 0.82133979f;
        float* o = out + 0x18 + 0x18 * w;
        o[0x00] += t81 * 0.13052619f;
        o[0x04] += t64 * 0.38268343f;
        o[0x08] += t56 * 0.60876143f;
        o[0x0c] += t56 * -0.79335332f;
        o[0x10] += t64 * -0.92387950f;
        o[0x14] += t81 * -0.99144489f;
        o[0x18] += t68 * -0.99144489f;
        o[0x1c] += t61 * -0.92387950f;
        o[0x20] += t58 * -0.79335332f;
        o[0x24] += t58 * -0.60876143f;
        o[0x28] += t61 * -0.38268343f;
        o[0x2c] += t68 * -0.13052619f;
    }
}
}
}
}
// ---- items of slice s01145d10 end

// ---- items of slice s0116c750 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float       isRatioTable[16];    // 0x014da6d8  tan(is_pos * PI / 12)
extern "C" float       ioPowTable[2][32];   // 0x014da718  io^n, io = 2^-0.25 / 2^-0.5
extern void III_ms_stereo(float* xr);       // 0x0116c600 (static, EAX = xr, in the original)
typedef unsigned char  u8;
typedef unsigned short u16;
enum { SBLIMIT = 32, SSLIMIT = 18, kLines = SBLIMIT * SSLIMIT };
struct SFBandIndex {
    short l[23];
    u8    s[14];
};
extern "C" SFBandIndex sfBandIndexLSF[3];   // 0x014da570
struct III_gr_info {                         // 0x18 bytes
    u16  part2_3_length;                     // +0x00 (unused here)
    u16  big_values;                         // +0x02 (unused here)
    u16  scalefac_compress;                  // +0x04
    u8   global_gain;                        // +0x06 (unused here)
    char window_switching_flag;              // +0x07
    char block_type;                         // +0x08
    char mixed_block_flag;                   // +0x09
    u8   pad[0x18 - 0x0a];
};
struct III_scalefac {
    short l[23];                             // +0x00
    short s[3][13];                          // +0x2e
};
class Layer3DecoderLSF {
public:
    void III_stereo(int gr, float xr[2][kLines]);

    u8           pad0[0x2f];
    char         lsf;                        // +0x2f
    u8           sampling_frequency;         // +0x30
    u8           pad31[0x37 - 0x31];
    char         mode;                       // +0x37  (1 = joint stereo)
    u8           mode_ext;                   // +0x38
    u8           pad39[0x70 - 0x39];
    III_gr_info  gr_info[11];                // +0x70
    III_scalefac scalefac;                   // +0x14c (right channel)
};
static __forceinline void i_stereo_k_values(float k[2][kLines], unsigned int is_pos, int io, int i)
{
    if (is_pos == 0) {
        k[0][i] = 1.0f;
        k[1][i] = 1.0f;
    } else if (is_pos & 1) {
        k[0][i] = ioPowTable[io][(is_pos + 1) >> 1];
        k[1][i] = 1.0f;
    } else {
        k[0][i] = 1.0f;
        k[1][i] = ioPowTable[io][is_pos >> 1];
    }
}
// ---- items of slice s0116c750 end

// ---- items of slice s0116e4f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define IN(i)  in[(i) * 4]
#define OUT(i) out[(i) * 4]
// ---- items of slice s0116e4f0 end

// @ 0x011464a0
namespace rw { namespace audio { namespace core {
void HELPER_Imdct12X4(float* x, float* y)
{
    if (((unsigned)x | (unsigned)y) & 0xf) {
        for (int i = 0; i < 4; i++)
            Imdct12X1Local(x + i, y);
        return;
    }
    memset(y, 0, 0x240);
    const float* c = g_imdct12Coef;
    float* xend = x + 12;
    do {
        for (int j = 0; j < 4; j++) {
            float v2 = x[0x30 + j];
            float v6 = v2 + x[0x24 + j];
            float v10 = x[0x24 + j] + x[0x18 + j];
            float v14 = x[0x18 + j] + x[0x0c + j];
            x[0x30 + j] = v6;
            float v18 = x[0x0c + j] + x[j];
            x[0x18 + j] = v14;
            v2 = (x[0x3c + j] + v2) + v10;
            x[0x0c + j] = v18;
            v10 = v10 + v18;
            x[0x3c + j] = v2;
            x[0x24 + j] = v10;
            v14 = v14 * 0.8660254f;
            float v26 = x[j] + v6 * 0.5f;
            float v27 = v26 - v14;
            v26 = v26 + v14;
            v18 = v18 + v2 * 0.5f;
            v10 = v10 * 0.8660254f;
            float v19 = (v18 - v10) * 1.9318516f;
            float v2b = (v18 + v10) * 0.5176381f;
            v18 = (x[0x0c + j] - x[0x3c + j]) * 0.70710677f;
            float v3b = (v26 + v2b) * 0.5043145f;
            v10 = ((x[j] - x[0x30 + j]) + v18) * 0.5411961f;
            float v14b = (v27 + v19) * 0.6302362f;
            v27 = (v27 - v19) * 0.8213398f;
            v18 = ((x[j] - x[0x30 + j]) - v18) * 1.306563f;
            v2b = (v26 - v2b) * 3.830649f;
            y[0x18 + j] += v27 * 0.13052619f;
            y[0x1c + j] += v18 * 0.38268343f;
            y[0x20 + j] += v2b * 0.6087614f;
            y[0x24 + j] += v2b * -0.7933533f;
            y[0x28 + j] += v18 * -0.9238795f;
            y[0x2c + j] += v27 * -0.9914449f;
            y[0x30 + j] += v14b * -0.9914449f;
            y[0x34 + j] += v10 * -0.9238795f;
            y[0x38 + j] += v3b * -0.7933533f;
            y[0x3c + j] += v3b * -0.6087614f;
            y[0x40 + j] += v10 * -0.38268343f;
            y[0x44 + j] += v14b * -0.13052619f;
        }
        x += 4;
        y += 0x60 / 4;
    } while (x != xend);
}
}}}  // namespace rw::audio::core

// @ 0x011467f0
namespace rw { namespace audio { namespace core {
void CMpegLayer3Base::Imdct36X4(int gr, int ch, float* xr)
{
    GranuleInfo* gi = &mGranuleInfo[gr][ch];
    float* hybrid = (float*)((uint8_t*)mpLoadedPrevBlockX4 + gr * 0x900);
    __declspec(align(16)) float tmp[0x240 / 4];
    _alloca(8);   // make the frame dynamic so the epilogue restores the saved regs from ebp
                  // instead of popping them off an esp the __fastcall cleanup left 8 bytes low
    int flag = 0;
    if (gi->windowSwitchingFlag && gi->mixedBlockFlag) {
        uint8_t* t = (uint8_t*)tmp;
        uint8_t* in = (uint8_t*)xr;           // the sub-block inputs are 4 bytes apart
        HELPER_Imdct36X1(g_imdct36Win, (float*)(t + 0), (float*)(in + 0));
        HELPER_Imdct36X1(g_imdct36Win, (float*)(t + 4), (float*)(in + 4));
        Imdct12X1Local((float*)(in + 8), (float*)(t + 8));
        Imdct12X1Local((float*)(in + 0xc), (float*)(t + 0xc));
        HELPER_OverlapAddX4(xr, tmp, hybrid);
        flag = 1;
    }
    if (gi->blockType == 2) {
        for (; flag < 8; flag++) {
            float* p = xr + flag * 0x120 / 4;
            HELPER_Imdct12X4(p, tmp);
            HELPER_OverlapAddX4(p, tmp, hybrid + flag * 0x120 / 4);
        }
    } else {
        const float* tbl = (const float*)((const uint8_t*)g_imdct36Win + gi->blockType * 0x90);
        for (; flag < 8; flag++) {
            float* p = xr + flag * 0x120 / 4;
            HELPER_Imdct36X4Implementation(p, tmp, tbl);
            HELPER_OverlapAddX4(p, tmp, hybrid + flag * 0x120 / 4);
        }
    }
}
}}}  // namespace rw::audio::core

// @ 0x0116c750
void Layer3DecoderLSF::III_stereo(int gr, float xr[2][kLines])
{
    bool i_stereo = (mode == 1) && (mode_ext & 1);
    bool ms_stereo = (mode == 1) && (mode_ext & 2);
    int sfb;
    int i, j, sb, ss;
    float is_ratio[kLines];
    int is_pos[kLines];
    float k[2][kLines];

    if (i_stereo) {
        III_gr_info* gr_info = &this->gr_info[gr];
        int io = gr_info->scalefac_compress & 1;

        for (i = 0; i < kLines; i++)
            is_pos[i] = 7;

        if (gr_info->window_switching_flag && (gr_info->block_type == 2)) {
            if (gr_info->mixed_block_flag) {
                int max_sfb = 0;

                for (j = 0; j < 3; j++) {
                    int sfbcnt;
                    sfbcnt = 2;
                    for (sfb = 12; sfb >= 3; sfb--) {
                        int lines;
                        lines = sfBandIndexLSF[sampling_frequency].s[sfb + 1] - sfBandIndexLSF[sampling_frequency].s[sfb];
                        i = 3 * sfBandIndexLSF[sampling_frequency].s[sfb] + (j + 1) * lines - 1;
                        while (lines > 0) {
                            if (xr[1][i] != 0.0f) {
                                sfbcnt = sfb;
                                sfb = -10;
                                lines = -10;
                            }
                            lines--;
                            i--;
                        }
                    }
                    sfb = sfbcnt + 1;

                    if (sfb > max_sfb)
                        max_sfb = sfb;

                    while (sfb < 12) {
                        sb = sfBandIndexLSF[sampling_frequency].s[sfb + 1] - sfBandIndexLSF[sampling_frequency].s[sfb];
                        i = 3 * sfBandIndexLSF[sampling_frequency].s[sfb] + j * sb;
                        for (; sb > 0; sb--) {
                            is_pos[i] = scalefac.s[j][sfb];
                            if (is_pos[i] != 7) {
                                if (lsf)
                                    i_stereo_k_values(k, is_pos[i], io, i);
                                else
                                    is_ratio[i] = isRatioTable[is_pos[i]];
                            }
                            i++;
                        }
                        sfb++;
                    }
                    sb = sfBandIndexLSF[sampling_frequency].s[11] - sfBandIndexLSF[sampling_frequency].s[10];
                    sfb = 3 * sfBandIndexLSF[sampling_frequency].s[10] + j * sb;
                    sb = sfBandIndexLSF[sampling_frequency].s[12] - sfBandIndexLSF[sampling_frequency].s[11];
                    i = 3 * sfBandIndexLSF[sampling_frequency].s[11] + j * sb;
                    for (; sb > 0; sb--) {
                        is_pos[i] = is_pos[sfb];
                        if (lsf) {
                            k[0][i] = k[0][sfb];
                            k[1][i] = k[1][sfb];
                        } else {
                            is_ratio[i] = is_ratio[sfb];
                        }
                        i++;
                    }
                }
                if (max_sfb <= 3) {
                    i = 2;
                    ss = 17;
                    sb = -1;
                    while (i >= 0) {
                        if (xr[1][i * SSLIMIT + ss] != 0.0f) {
                            sb = i * 18 + ss;
                            i = -1;
                        } else {
                            ss--;
                            if (ss < 0) {
                                i--;
                                ss = 17;
                            }
                        }
                    }
                    i = 0;
                    while (sfBandIndexLSF[sampling_frequency].l[i] <= sb)
                        i++;
                    sfb = i;
                    i = sfBandIndexLSF[sampling_frequency].l[i];
                    for (; sfb < 8; sfb++) {
                        sb = sfBandIndexLSF[sampling_frequency].l[sfb + 1] - sfBandIndexLSF[sampling_frequency].l[sfb];
                        for (; sb > 0; sb--) {
                            is_pos[i] = scalefac.l[sfb];
                            if (is_pos[i] != 7) {
                                if (lsf)
                                    i_stereo_k_values(k, is_pos[i], io, i);
                                else
                                    is_ratio[i] = isRatioTable[is_pos[i]];
                            }
                            i++;
                        }
                    }
                }
            } else {
                for (j = 0; j < 3; j++) {
                    int sfbcnt;
                    sfbcnt = -1;
                    for (sfb = 12; sfb >= 0; sfb--) {
                        int lines;
                        lines = sfBandIndexLSF[sampling_frequency].s[sfb + 1] - sfBandIndexLSF[sampling_frequency].s[sfb];
                        i = 3 * sfBandIndexLSF[sampling_frequency].s[sfb] + (j + 1) * lines - 1;
                        while (lines > 0) {
                            if (xr[1][i] != 0.0f) {
                                sfbcnt = sfb;
                                sfb = -10;
                                lines = -10;
                            }
                            lines--;
                            i--;
                        }
                    }
                    sfb = sfbcnt + 1;
                    while (sfb < 12) {
                        sb = sfBandIndexLSF[sampling_frequency].s[sfb + 1] - sfBandIndexLSF[sampling_frequency].s[sfb];
                        i = 3 * sfBandIndexLSF[sampling_frequency].s[sfb] + j * sb;
                        for (; sb > 0; sb--) {
                            is_pos[i] = scalefac.s[j][sfb];
                            if (is_pos[i] != 7) {
                                if (lsf)
                                    i_stereo_k_values(k, is_pos[i], io, i);
                                else
                                    is_ratio[i] = isRatioTable[is_pos[i]];
                            }
                            i++;
                        }
                        sfb++;
                    }

                    sb = sfBandIndexLSF[sampling_frequency].s[11] - sfBandIndexLSF[sampling_frequency].s[10];
                    sfb = 3 * sfBandIndexLSF[sampling_frequency].s[10] + j * sb;
                    sb = sfBandIndexLSF[sampling_frequency].s[12] - sfBandIndexLSF[sampling_frequency].s[11];
                    i = 3 * sfBandIndexLSF[sampling_frequency].s[11] + j * sb;
                    for (; sb > 0; sb--) {
                        is_pos[i] = is_pos[sfb];
                        if (lsf) {
                            k[0][i] = k[0][sfb];
                            k[1][i] = k[1][sfb];
                        } else {
                            is_ratio[i] = is_ratio[sfb];
                        }
                        i++;
                    }
                }
            }
        } else {
            i = 31;
            ss = 17;
            sb = 0;
            while (i >= 0) {
                if (xr[1][i * SSLIMIT + ss] != 0.0f) {
                    sb = i * 18 + ss;
                    i = -1;
                } else {
                    ss--;
                    if (ss < 0) {
                        i--;
                        ss = 17;
                    }
                }
            }
            i = 0;
            while (sfBandIndexLSF[sampling_frequency].l[i] <= sb)
                i++;
            sfb = i;
            i = sfBandIndexLSF[sampling_frequency].l[i];
            for (; sfb < 21; sfb++) {
                sb = sfBandIndexLSF[sampling_frequency].l[sfb + 1] - sfBandIndexLSF[sampling_frequency].l[sfb];
                for (; sb > 0; sb--) {
                    is_pos[i] = scalefac.l[sfb];
                    if (is_pos[i] != 7) {
                        if (lsf)
                            i_stereo_k_values(k, is_pos[i], io, i);
                        else
                            is_ratio[i] = isRatioTable[is_pos[i]];
                    }
                    i++;
                }
            }
            sfb = sfBandIndexLSF[sampling_frequency].l[20];
            for (sb = kLines - sfBandIndexLSF[sampling_frequency].l[21]; sb > 0 && i < kLines; sb--) {
                is_pos[i] = is_pos[sfb];
                if (lsf) {
                    k[0][i] = k[0][sfb];
                    k[1][i] = k[1][sfb];
                } else {
                    is_ratio[i] = is_ratio[sfb];
                }
                i++;
            }
        }

        // Apply the stereo processing in place (lr == xr).
        for (sb = 0; sb < SBLIMIT; sb++) {
            for (ss = 0; ss < SSLIMIT; ss++) {
                i = (sb * 18) + ss;
                if (is_pos[i] == 7) {
                    if (ms_stereo) {
                        float l = xr[0][sb * SSLIMIT + ss];
                        float r = xr[1][sb * SSLIMIT + ss];
                        xr[1][sb * SSLIMIT + ss] = (l - r) * 0.70710677f;
                        xr[0][sb * SSLIMIT + ss] = (r + l) * 0.70710677f;
                    }
                } else if (lsf) {
                    float l = xr[0][sb * SSLIMIT + ss];
                    xr[0][sb * SSLIMIT + ss] = k[0][i] * l;
                    xr[1][sb * SSLIMIT + ss] = k[1][i] * l;
                } else {
                    xr[1][sb * SSLIMIT + ss] = xr[0][sb * SSLIMIT + ss] / (1.0f + is_ratio[i]);
                    xr[0][sb * SSLIMIT + ss] = xr[1][sb * SSLIMIT + ss] * is_ratio[i];
                }
            }
        }
    } else if (ms_stereo) {
        III_ms_stereo(xr[0]);
    }
}

// @ 0x0116e4f0
namespace rw { namespace audio { namespace core {
void __fastcall HELPER_Imdct36X1(const float* win, float* out, float* in)
{
    IN(17) += IN(16); IN(16) += IN(15); IN(15) += IN(14); IN(14) += IN(13);
    IN(13) += IN(12); IN(12) += IN(11); IN(11) += IN(10); IN(10) += IN(9);
    IN(9)  += IN(8);  IN(8)  += IN(7);  IN(7)  += IN(6);  IN(6)  += IN(5);
    IN(5)  += IN(4);  IN(4)  += IN(3);  IN(3)  += IN(2);  IN(2)  += IN(1);
    IN(1)  += IN(0);

    IN(17) += IN(15); IN(15) += IN(13); IN(13) += IN(11); IN(11) += IN(9);
    IN(9)  += IN(7);  IN(7)  += IN(5);  IN(5)  += IN(3);  IN(3)  += IN(1);

    // even half, even samples (2*cos(k*pi/18): c1 1.9696, c2 1.8794, c4 1.5321, c5 1.2856, c7 0.6840, c8 0.3473)
    float t  = IN(12) + IN(0) * 2.0f;
    float e1 = IN(4) * 1.8793852f + IN(8) * 1.5320889f + IN(16) * 0.34729636f + t;
    float e2 = IN(4) + IN(0) * 2.0f - IN(8) - IN(12) - IN(12) - IN(16);
    float e3 = t - IN(4) * 0.34729636f - IN(8) * 1.8793852f + IN(16) * 1.5320889f;
    float e4 = t - IN(4) * 1.5320889f + IN(8) * 0.34729636f - IN(16) * 1.8793852f;
    float e5 = IN(0) - IN(4) + IN(8) - IN(12) + IN(16);

    // even half, odd samples
    float s6 = IN(6) * 1.7320508f;
    float o1 = IN(2) * 1.9696155f + s6 + IN(10) * 1.2855753f + IN(14) * 0.6840403f;
    float o2 = (IN(2) - IN(10) - IN(14)) * 1.7320508f;
    float o3 = IN(2) * 1.2855753f - s6 - IN(10) * 0.6840403f + IN(14) * 1.9696155f;
    float o4 = IN(2) * 0.6840403f - s6 + IN(10) * 1.9696155f - IN(14) * 1.2855753f;

    // odd half, even samples
    float u  = IN(13) + IN(1) * 2.0f;
    float f1 = IN(5) * 1.8793852f + IN(9) * 1.5320889f + IN(17) * 0.34729636f + u;
    float f2 = IN(5) + IN(1) * 2.0f - IN(9) - IN(13) - IN(13) - IN(17);
    float f3 = u - IN(5) * 0.34729636f - IN(9) * 1.8793852f + IN(17) * 1.5320889f;
    float f4 = u - IN(5) * 1.5320889f + IN(9) * 0.34729636f - IN(17) * 1.8793852f;
    float f5 = (IN(1) - IN(5) + IN(9) - IN(13) + IN(17)) * 0.70710677f;

    // odd half, odd samples
    float s7 = IN(7) * 1.7320508f;
    float g1 = IN(3) * 1.9696155f + s7 + IN(11) * 1.2855753f + IN(15) * 0.6840403f;
    float g2 = (IN(3) - IN(11) - IN(15)) * 1.7320508f;
    float g3 = IN(3) * 1.2855753f - s7 - IN(11) * 0.6840403f + IN(15) * 1.9696155f;
    float g4 = IN(3) * 0.6840403f - s7 + IN(11) * 1.9696155f - IN(15) * 1.2855753f;

    // tfcos36 butterflies: sum0 + sum1 -> out[26-v], out[27+v];
    //                      sum0 - sum1 -> out[8-v],  out[9+v]
    float sum0, sum1;
    float tmp[18];  // tmp[v] = sum (v = 0..8), tmp[17 - v] = difference
    sum0 = o1 + e1; sum1 = (g1 + f1) * 0.5019099f;  tmp[0] = sum1 + sum0; tmp[17] = sum0 - sum1;
    sum0 = o2 + e2; sum1 = (g2 + f2) * 0.51763809f; tmp[1] = sum1 + sum0; tmp[16] = sum0 - sum1;
    sum0 = o3 + e3; sum1 = (g3 + f3) * 0.55168897f; tmp[2] = sum1 + sum0; tmp[15] = sum0 - sum1;
    sum0 = o4 + e4; sum1 = (g4 + f4) * 0.61038727f; tmp[3] = sum1 + sum0; tmp[14] = sum0 - sum1;
    sum0 = e5;      sum1 = f5;                       tmp[4] = sum1 + sum0; tmp[13] = sum0 - sum1;
    sum0 = e4 - o4; sum1 = (f4 - g4) * 0.8717234f;  tmp[5] = sum1 + sum0; tmp[12] = sum0 - sum1;
    sum0 = e3 - o3; sum1 = (f3 - g3) * 1.1831008f;  tmp[6] = sum1 + sum0; tmp[11] = sum0 - sum1;
    sum0 = e2 - o2; sum1 = (f2 - g2) * 1.9318516f;  tmp[7] = sum1 + sum0; tmp[10] = sum0 - sum1;
    sum0 = e1 - o1; sum1 = (f1 - g1) * 5.7368565f;  tmp[8] = sum1 + sum0; tmp[9] = sum0 - sum1;

    OUT(0)  = tmp[9] * win[0];
    OUT(1)  = win[1]  * tmp[10];
    OUT(2)  = win[2]  * tmp[11];
    OUT(3)  = win[3]  * tmp[12];
    OUT(4)  = win[4]  * tmp[13];
    OUT(5)  = win[5]  * tmp[14];
    OUT(6)  = win[6]  * tmp[15];
    OUT(7)  = win[7]  * tmp[16];
    OUT(8)  = win[8]  * tmp[17];
    OUT(9)  = win[9]  * tmp[17];
    OUT(10) = win[10] * tmp[16];
    OUT(11) = win[11] * tmp[15];
    OUT(12) = win[12] * tmp[14];
    OUT(13) = win[13] * tmp[13];
    OUT(14) = win[14] * tmp[12];
    OUT(15) = win[15] * tmp[11];
    OUT(16) = win[16] * tmp[10];
    OUT(17) = win[17] * tmp[9];
    OUT(18) = win[18] * tmp[8];
    OUT(19) = win[19] * tmp[7];
    OUT(20) = win[20] * tmp[6];
    OUT(21) = win[21] * tmp[5];
    OUT(22) = win[22] * tmp[4];
    OUT(23) = win[23] * tmp[3];
    OUT(24) = win[24] * tmp[2];
    OUT(25) = win[25] * tmp[1];
    OUT(26) = win[26] * tmp[0];
    OUT(27) = win[27] * tmp[0];
    OUT(28) = win[28] * tmp[1];
    OUT(29) = win[29] * tmp[2];
    OUT(30) = win[30] * tmp[3];
    OUT(31) = win[31] * tmp[4];
    OUT(32) = win[32] * tmp[5];
    OUT(33) = win[33] * tmp[6];
    OUT(34) = win[34] * tmp[7];
    OUT(35) = win[35] * tmp[8];
}
}}}  // namespace rw::audio::core

// @ 0x0116efb0
namespace rw { namespace audio { namespace core {
void HELPER_Imdct36X4Implementation(float* param_1, float* param_2, float* param_3)
{
    struct F4 {
        __m128 v;
        F4() {}
        F4(__m128 x) : v(x) {}
        F4 operator+(const F4& b) const { return _mm_add_ps(v, b.v); }
        F4 operator-(const F4& b) const { return _mm_sub_ps(v, b.v); }
        F4 operator*(float c) const { return _mm_mul_ps(v, _mm_set1_ps(c)); }
    };
    if ((((unsigned int)param_1 | (unsigned int)param_2 | (unsigned int)param_3) & 0xf) == 0) {
        F4* P = (F4*)param_1;
#define V(f) P[(f) >> 2]

        // Stage 1: butterflies in place on the input vectors.
        F4 f50 = V(0x3c) + V(0x38);
        F4 f54 = V(0x34) + V(0x30);
        F4 f66 = V(0x2c) + V(0x28);
        V(0x44) = (V(0x44) + V(0x40)) + f50;
        V(0x40) = V(0x40) + V(0x3c);
        V(0x3c) = f50 + f54;
        V(0x38) = V(0x38) + V(0x34);
        V(0x34) = f54 + f66;
        V(0x30) = V(0x30) + V(0x2c);

        F4 g50 = V(0x24) + V(0x20);
        F4 g54 = V(0x1c) + V(0x18);
        F4 g55 = V(0x14) + V(0x10);
        V(0x2c) = f66 + g50;
        V(0x28) = V(0x28) + V(0x24);
        V(0x24) = g50 + g54;
        V(0x20) = V(0x20) + V(0x1c);
        V(0x1c) = g54 + g55;
        V(0x18) = V(0x18) + V(0x14);

        F4 h54 = V(0xc) + V(0x8);
        F4 h50 = V(0x4) + V(0x0);
        V(0x14) = g55 + h54;
        V(0x10) = V(0x10) + V(0xc);
        V(0xc) = h54 + h50;
        V(0x8) = V(0x8) + V(0x4);
        V(0x4) = h50;

        // Stage 2: two passes (i = 0, 1) over the block at vector i; results go to two-vector arrays.
        F4 A120[2], A100[2], A140[2], Ae0[2], Aa0[2], Ac0[2], A80[2], A60[2], A40[2];
        for (int i = 0; i < 2; ++i) {
            F4* b = P + i;
            F4 t0 = b[0] + b[0];
            F4 a56 = b[12] + t0;
            A120[i] = ((b[4] * 1.8793852f + a56) + b[8] * 1.5320889f) + b[16] * 0.34729636f;
            A40[i] = (((b[4] + t0) - b[8]) - (b[12] + b[12])) - b[16];
            A100[i] = ((b[16] * 1.5320889f + a56) - b[4] * 0.34729636f) - b[8] * 1.8793852f;
            A140[i] = ((b[8] * 0.34729636f + a56) - b[4] * 1.5320889f) - b[16] * 1.8793852f;
            F4 t5 = ((b[0] - b[4]) - b[12]) + (b[8] + b[16]);
            if (i != 0) t5 = t5 * 0.70710677f;
            Ae0[i] = t5;
            F4 t6 = b[6] * 1.7320508f;
            Aa0[i] = (b[2] * 1.9696155f + t6) + (b[10] * 1.2855753f + b[14] * 0.6840403f);
            A60[i] = ((b[2] - b[10]) - b[14]) * 1.7320508f;
            Ac0[i] = (b[2] * 1.2855753f + b[14] * 1.9696155f) - (b[10] * 0.6840403f + t6);
            A80[i] = (b[2] * 0.6840403f + b[10] * 1.9696155f) - (b[14] * 1.2855753f + t6);
        }

        // Stage 3: combine the two passes (sum/difference groups, each scaled by its cosine constant).
        F4 t18 = (A120[1] + Aa0[1]) * 0.5019099f;
        F4 s18 = A120[0] + Aa0[0];
        F4 f54b = s18 + t18;
        F4 d18 = s18 - t18;
        F4 t19 = (A40[1] + A60[1]) * 0.5176381f;
        F4 s19 = A40[0] + A60[0];
        F4 f57 = s19 + t19;
        F4 d19 = s19 - t19;
        F4 t20 = (A100[1] + Ac0[1]) * 0.55168897f;
        F4 s20 = A100[0] + Ac0[0];
        F4 f60 = s20 + t20;
        F4 d20 = s20 - t20;
        F4 t21 = (A140[1] + A80[1]) * 0.61038727f;
        F4 s21 = A140[0] + A80[0];
        F4 f63 = s21 + t21;
        F4 d21 = s21 - t21;
        F4 t22 = (A140[1] - A80[1]) * 0.8717234f;
        F4 s22 = A140[0] - A80[0];
        F4 f55 = s22 + t22;
        F4 d22 = s22 - t22;
        F4 t23 = (A100[1] - Ac0[1]) * 1.1831008f;
        F4 s23 = A100[0] - Ac0[0];
        F4 f58 = s23 + t23;
        F4 d23 = s23 - t23;
        F4 t24 = (A40[1] - A60[1]) * 1.9318516f;
        F4 s24 = A40[0] - A60[0];
        F4 f61 = s24 + t24;
        F4 d24 = s24 - t24;
        F4 t25 = (A120[1] - Aa0[1]) * 5.7368565f;
        F4 s25 = A120[0] - Aa0[0];
        F4 f64 = s25 + t25;
        F4 d25 = s25 - t25;
        F4 e4 = Ae0[0] - Ae0[1];
        F4 e8 = Ae0[0] + Ae0[1];

        // Stage 4: window each output vector by its scalar window value (broadcast).
        F4* O = (F4*)param_2;
        O[0] = d25 * param_3[0];
        O[1] = d24 * param_3[1];
        O[2] = d23 * param_3[2];
        O[3] = d22 * param_3[3];
        O[4] = e4 * param_3[4];
        O[5] = d21 * param_3[5];
        O[6] = d20 * param_3[6];
        O[7] = d19 * param_3[7];
        O[8] = d18 * param_3[8];
        O[9] = d18 * param_3[9];
        O[10] = d19 * param_3[10];
        O[11] = d20 * param_3[11];
        O[12] = d21 * param_3[12];
        O[13] = e4 * param_3[13];
        O[14] = d22 * param_3[14];
        O[15] = d23 * param_3[15];
        O[16] = d24 * param_3[16];
        O[17] = d25 * param_3[17];
        O[18] = f64 * param_3[18];
        O[19] = f61 * param_3[19];
        O[20] = f58 * param_3[20];
        O[21] = f55 * param_3[21];
        O[22] = e8 * param_3[22];
        O[23] = f63 * param_3[23];
        O[24] = f60 * param_3[24];
        O[25] = f57 * param_3[25];
        O[26] = f54b * param_3[26];
        O[27] = f54b * param_3[27];
        O[28] = f57 * param_3[28];
        O[29] = f60 * param_3[29];
        O[30] = f63 * param_3[30];
        O[31] = e8 * param_3[31];
        O[32] = f55 * param_3[32];
        O[33] = f58 * param_3[33];
        O[34] = f61 * param_3[34];
        O[35] = f64 * param_3[35];
#undef V
        return;
    }

    // Unaligned: one scalar 36-point IMDCT per lane.
    for (int k = 0; k < 4; ++k)
        HELPER_Imdct36X1(param_3, param_2 + k, param_1 + k);
}
}}}  // namespace rw::audio::core
