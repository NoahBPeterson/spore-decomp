// @ 0x0116c750   MPEG audio Layer III joint-stereo processing, MPEG-2 LSF variant (5653 bytes)
//
// This is NOT a terrain brush (the old guess). Evidence:
//   * 576 (0x240) = SBLIMIT*SSLIMIT = 32*18 spectral lines per granule; xr[1] lives at xr+0x900.
//   * DAT_014da570 is the MPEG-2 LSF sfBandIndex table, 3 entries of 60 bytes:
//       short l[23] = {0,6,12,18,24,30,36,44,54,66,80,96,116,...,576}, u8 s[14] = {0,4,8,...,192}.
//   * DAT_014da6d8 = tan(is_pos * PI/12) for is_pos 0..15 (the MPEG-1 intensity ratio table).
//   * DAT_014da718 = io^n for io = 2^-1/4 and 2^-1/2 (LSF intensity k-value table, [2][32]).
//   * 0.70710677 = 1/sqrt(2) (MS stereo).
// The code is the ISO "dist10" III_stereo() with its LSF extension (i_stereo_k_values),
// using float spectra, table lookups for tan()/pow(), working in place on xr (lr == xr),
// and with the ms-only case split out into a separate (SSE) routine, FUN_0116c600.
// FUN_01164200 is the MPEG-1 twin of this function (same source, different header layout).
//
// The original's FUN_0116c600 is a same-TU static helper that receives xr in EAX; here it is
// declared extern (cdecl), so the call site pushes instead.

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;

enum { SBLIMIT = 32, SSLIMIT = 18, kLines = SBLIMIT * SSLIMIT };

// MPEG-2 LSF scale-factor band boundaries (one entry per sampling frequency).
struct SFBandIndex {
    short l[23];
    u8    s[14];
};

extern "C" SFBandIndex sfBandIndexLSF[3];   // 0x014da570
extern "C" float       isRatioTable[16];    // 0x014da6d8  tan(is_pos * PI / 12)
extern "C" float       ioPowTable[2][32];   // 0x014da718  io^n, io = 2^-0.25 / 2^-0.5

extern void III_ms_stereo(float* xr);       // 0x0116c600 (static, EAX = xr, in the original)

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

// dist10 i_stereo_k_values(): the LSF intensity factors for one line (pow() -> table).
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
