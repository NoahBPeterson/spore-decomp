// MP3 layer-III intensity / mid-side stereo processing  @ 0x011443b0  (6482 bytes).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar math, ucomiss compares).
//
// This is the ISO dist10 (MPEG reference decoder) III_stereo() routine as compiled into
// Spore's MP3 decoder.  `this` is the layer-III decoder state, `gr` selects the granule
// info of the right channel and `xr` is the in-place float spectrum xr[2][32][18]
// (left at +0, right at +0x900).
//   +0x3b lsf (MPEG-2 low sampling frequency), +0x3c sfreq (sample-rate index),
//   +0x43 mode (1 = joint stereo), +0x44 mode_extension (bit0 intensity, bit1 M/S),
//   +0x154 granule info (stride 0x18), +0x230 right-channel scalefactors,
//   +0x2c8 is_pos[576], +0x2cc is_ratio[576], +0x2d0 k[2][576].
// Every 4-lane unrolled block in the binary is cl's unrolling of the simple loops below.

#include "../../include/types.h"

#define SBLIMIT 32
#define SSLIMIT 18

struct SfBandIndex {          // 0x3c bytes per sample-rate index
    int16_t l[23];            // +0x00 long-block band boundaries
    uint8_t s[14];            // +0x2e short-block band boundaries
};

extern "C" const SfBandIndex g_sfBandIndex[];   // DAT_014cb4e0
extern "C" const float g_isRatio[];             // DAT_014cb648  tan(is_pos*PI/12)
extern "C" const float g_lsfIsTable[2][32];     // DAT_014cb688  MPEG-2 intensity factors

// 0x01144270: SSE mid/side matrix over the whole granule (argument in EAX in the original,
// a static same-TU helper).
void MsStereoSSE(float* xr);

struct GrInfo {               // 0x18 bytes
    char pad0[4];
    uint16_t scalefac_compress;  // +0x04
    char pad6;
    uint8_t window_switching_flag;  // +0x07
    uint8_t block_type;          // +0x08
    uint8_t mixed_block_flag;    // +0x09
    char padA[0x18 - 0xa];
};

struct ScaleFac {             // right channel
    int16_t l[23];
    int16_t s[3][13];
};

struct Layer3Decoder {
    char pad0[0x3b];
    uint8_t lsf;              // +0x3b
    uint8_t sfreq;            // +0x3c
    char pad3d[0x43 - 0x3d];
    uint8_t mode;             // +0x43
    uint8_t mode_ext;         // +0x44
    char pad45[0x154 - 0x45];
    GrInfo grInfo[9];         // +0x154
    char pad22c[0x230 - 0x22c];
    ScaleFac scalefac;        // +0x230
    char pad2ac[0x2c8 - 0x2ac];
    int* is_pos;              // +0x2c8
    float* is_ratio;          // +0x2cc
    float* k;                 // +0x2d0  k[0][576], k[1][576]

    // dist10 i_stereo_k_values()
    __forceinline void KValues(unsigned int p, unsigned int io, int i) {
        float* kk = k;
        if (p == 0) {
            kk[i] = 1.0f;
            kk[576 + i] = 1.0f;
        } else if (p & 1) {
            kk[i] = g_lsfIsTable[io][(p + 1) >> 1];
            kk[576 + i] = 1.0f;
        } else {
            kk[i] = 1.0f;
            kk[576 + i] = g_lsfIsTable[io][p >> 1];
        }
    }

    __forceinline void SetIsPos(int i, int pos, unsigned int io) {
        is_pos[i] = pos;
        if (is_pos[i] != 7) {
            if (lsf)
                KValues((unsigned int)is_pos[i], io, i);
            else
                is_ratio[i] = g_isRatio[is_pos[i]];
        }
    }

    __forceinline void CopyIsPos(int dst, int src) {
        is_pos[dst] = is_pos[src];
        if (!lsf) {
            is_ratio[dst] = is_ratio[src];
        } else {
            k[dst] = k[src];
            k[576 + dst] = k[576 + src];
        }
    }

    // Short-block bands sfb..11 of window j (after the last non-zero band) take their
    // scalefactor as intensity position; band 11 is then extended from band 10.
    __forceinline void ShortWindow(int j, int sfb, unsigned int io) {
        for (; sfb < 12; ++sfb) {
            const SfBandIndex& u = g_sfBandIndex[sfreq];
            int sb = u.s[sfb + 1] - u.s[sfb];
            int i = 3 * u.s[sfb] + j * sb;
            for (; sb > 0; --sb) {
                SetIsPos(i, scalefac.s[j][sfb], io);
                ++i;
            }
        }
        const SfBandIndex& v = g_sfBandIndex[sfreq];
        int src = 3 * v.s[10] + j * (v.s[11] - v.s[10]);
        int sb = v.s[12] - v.s[11];
        int i = 3 * v.s[11] + j * sb;
        for (; sb > 0; --sb) {
            CopyIsPos(i, src);
            ++i;
        }
    }

    // Highest short band (above `lowest`) of window j holding a non-zero right-channel line.
    __forceinline int LastNonZeroShortBand(float (*xr)[SBLIMIT][SSLIMIT], int j, int lowest, int sfbcnt) {
        for (int sfb = 12; sfb >= lowest; --sfb) {
            const SfBandIndex& u = g_sfBandIndex[sfreq];
            int lines = u.s[sfb + 1] - u.s[sfb];
            int i = 3 * u.s[sfb] + (j + 1) * lines - 1;
            while (lines > 0) {
                if ((&xr[1][0][0])[i] != 0.0f) {
                    sfbcnt = sfb;
                    sfb = -10;
                    lines = -10;
                }
                --lines;
                --i;
            }
        }
        return sfbcnt;
    }

    void Stereo(int gr, float xr[2][SBLIMIT][SSLIMIT]);
};

typedef char check_is_pos[(int)&((Layer3Decoder*)0)->is_pos == 0x2c8 ? 1 : -1];

// @ 0x011443b0
void Layer3Decoder::Stereo(int gr, float xr[2][SBLIMIT][SSLIMIT]) {
    bool i_stereo = (mode == 1 && (mode_ext & 1)) ? true : false;
    bool ms_stereo = (mode == 1 && (mode_ext & 2)) ? true : false;

    if (i_stereo) {
        GrInfo* gi = &grInfo[gr];
        unsigned int io = gi->scalefac_compress & 1;

        for (int i = 0; i < 576; ++i)
            is_pos[i] = 7;

        if (gi->window_switching_flag && gi->block_type == 2) {
            if (gi->mixed_block_flag) {
                int max_sfb = 0;
                for (int j = 0; j < 3; ++j) {
                    int sfb = LastNonZeroShortBand(xr, j, 3, 2) + 1;
                    if (sfb > max_sfb) max_sfb = sfb;
                    ShortWindow(j, sfb, io);
                }
                if (max_sfb <= 3) {
                    int i = 2, ss = 17, sb = -1;
                    do {
                        if (xr[1][i][ss] != 0.0f) {
                            sb = i * 18 + ss;
                            break;
                        }
                        if (--ss < 0) {
                            --i;
                            ss = 17;
                        }
                    } while (i >= 0);
                    const SfBandIndex& t = g_sfBandIndex[sfreq];
                    int sfb = 0;
                    while (t.l[sfb] <= sb) ++sfb;
                    i = t.l[sfb];
                    for (; sfb < 8; ++sfb) {
                        const SfBandIndex& u = g_sfBandIndex[sfreq];
                        for (sb = u.l[sfb + 1] - u.l[sfb]; sb > 0; --sb) {
                            SetIsPos(i, scalefac.l[sfb], io);
                            ++i;
                        }
                    }
                }
            } else {
                for (int j = 0; j < 3; ++j) {
                    int sfb = LastNonZeroShortBand(xr, j, 0, -1) + 1;
                    ShortWindow(j, sfb, io);
                }
            }
        } else {
            int i = 31, ss = 17, sb = 0;
            do {
                if (xr[1][i][ss] != 0.0f) {
                    sb = i * 18 + ss;
                    break;
                }
                if (--ss < 0) {
                    --i;
                    ss = 17;
                }
            } while (i >= 0);
            const SfBandIndex& t = g_sfBandIndex[sfreq];
            int sfb = 0;
            while (t.l[sfb] <= sb) ++sfb;
            i = t.l[sfb];
            for (; sfb < 21; ++sfb) {
                const SfBandIndex& u = g_sfBandIndex[sfreq];
                for (sb = u.l[sfb + 1] - u.l[sfb]; sb > 0; --sb) {
                    SetIsPos(i, scalefac.l[sfb], io);
                    ++i;
                }
            }
            const SfBandIndex& v = g_sfBandIndex[sfreq];
            int src = v.l[20];
            for (sb = 576 - v.l[21]; sb > 0; --sb) {
                if (i >= 576) break;
                CopyIsPos(i, src);
                ++i;
            }
        }

        int i = 0;
        for (int sb = 0; sb < SBLIMIT * SSLIMIT; sb += SSLIMIT) {
            for (int ss = 0; ss < SSLIMIT; ++ss, ++i) {
                float* l = &xr[0][0][0] + sb + ss;
                float* r = &xr[1][0][0] + sb + ss;
                if (is_pos[i] == 7) {
                    if (ms_stereo) {
                        float a = *l;
                        float b = *r;
                        *l = (b + a) * 0.70710677f;
                        *r = (a - b) * 0.70710677f;
                    }
                } else if (!lsf) {
                    float t = *l / (is_ratio[i] + 1.0f);
                    *r = t;
                    *l = is_ratio[i] * t;
                } else {
                    float k1 = k[576 + i];
                    float x = *l;
                    *l = k[i] * x;
                    *r = k1 * x;
                }
            }
        }
    } else if (ms_stereo) {
        MsStereoSSE(&xr[0][0][0]);
    }
}
