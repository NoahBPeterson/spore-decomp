// src/game/ealayer30/helper_mpegl3base.cpp.cpp -- migrated from slice(s) s0116dd70, s01169f50, s01168520, s011675c0, s011666d0, s01165820, s0116efb0, s0116e4f0, s0116c750, s01145d10 by tools/migrate/rewrite.py
// Object file: ealayer30/helper_mpegl3base.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" const float    g_imdct12Coef[];     // 0x014cbab0 IMDCT12 constants
extern "C" const float    g_imdct36Win[];      // 0x014cb7d0 IMDCT36 windows / tfcos
#include <string.h>
#include <malloc.h>
#include <xmmintrin.h>
#include <mmintrin.h>
#include <intrin.h>
#include "rw/audio/core/System.h"
#include <malloc.h>     // _alloca

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

// ---- items of slice s011666d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kImdctWindows[4][36];  // 0x014d7370
extern "C" void* __cdecl memset(void* pDst, int nValue, unsigned int nBytes);
void HELPER_Imdct12X1(float* pOut, float* pIn);
extern void* (*const g_pfnAudioAlloc)(unsigned int nBytes);
struct BandState
{
    unsigned char mPad00[7];         // +0x00
    bool          mbLeftWindow;      // +0x07 the previous block overlaps this one
    unsigned char mnWindowSequence;  // +0x08 2 = eight short windows (12-point IMDCTs)
    bool          mbRightWindow;     // +0x09 this block overlaps the next one
    unsigned char mPad0a[0x0e];      // +0x0a
};
class HELPER_Imdct12X4Implementation
{
public:
    void Transform(unsigned int nChannel, unsigned int nBlock, float* pOutput);  // 0x011673e0

    unsigned char mPad000[0x48];   // +0x000
    unsigned char mnChannelCount;  // +0x048
    unsigned char mPad049[0x0f];   // +0x049
    BandState     mBands[14];      // +0x058 entry = nBlock + 2 * nChannel
    unsigned char mPad1a8[8];      // +0x1a8
    void*         mpWorkBuffer;    // +0x1b0 mnChannelCount * 0x900 bytes (8 blocks of 72 floats)
};
#define ADD(k)  pOut[lane + (k)] = pIn[lane + (k)] + pHistory[lane + (k)]
#define ROT(k)  pHistory[lane + (k)] = pIn[lane + (k) + 72]
// ---- items of slice s011666d0 end

// ---- items of slice s011675c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Cell { float f[8]; };
struct Row { Cell c[9]; };
#define NEGATE_CELL(i) r->c[i].f[5] *= -1.0f; r->c[i].f[7] *= -1.0f;
static __forceinline short ToFixed14(float value)
{
    return (short)_mm_cvtss_si32(_mm_set_ss(value));
}
#define PACK_ROW(r) \
    out[(r) * 4 + 0] = ToFixed14(src[(r) * 72 + 0]); \
    out[(r) * 4 + 1] = ToFixed14(src[(r) * 72 + 1]); \
    out[(r) * 4 + 2] = ToFixed14(src[(r) * 72 + 2]); \
    out[(r) * 4 + 3] = ToFixed14(src[(r) * 72 + 3]);
// ---- items of slice s011675c0 end

// ---- items of slice s01168520 begin (TODO(rewrite): local stubs, replace by canonical classes)
static const int16_t KS_DctMatrix[512] = {
    16364, 16207, 15893, 15426, 14811, 14053, 13160, 12140, 11003, 9760, 8423, 7005, 5520, 3981, 2404, 804,
    16207, 14811, 12140, 8423, 3981, -803, -5519, -9759, -13159, -15425, -16363, -15892, -14052, -11002, -7004, -2403,
    15893, 12140, 5520, -2403, -9759, -14810, -16363, -14052, -8422, -803, 7005, 13160, 16207, 15426, 11003, 3981,
    15426, 8423, -2403, -12139, -16363, -13159, -3980, 7005, 14811, 15893, 9760, -803, -11002, -16206, -14052, -5519,
    14811, 3981, -9759, -16363, -11002, 2404, 14053, 15426, 5520, -8422, -16206, -12139, 804, 13160, 15893, 7005,
    14053, -803, -14810, -13159, 2404, 15426, 12140, -3980, -15892, -11002, 5520, 16207, 9760, -7004, -16363, -8422,
    13160, -5519, -16363, -3980, 14053, 12140, -7004, -16206, -2403, 14811, 11003, -8422, -15892, -803, 15426, 9760,
    12140, -9759, -14052, 7005, 15426, -3980, -16206, 804, 16364, 2404, -15892, -5519, 14811, 8423, -13159, -11002,
    11003, -13159, -8422, 14811, 5520, -15892, -2403, 16364, -803, -16206, 3981, 15426, -7004, -14052, 9760, 12140,
    9760, -15425, -803, 15893, -8422, -11002, 14811, 2404, -16206, 7005, 12140, -14052, -3980, 16364, -5519, -13159,
    8423, -16363, 7005, 9760, -16206, 5520, 11003, -15892, 3981, 12140, -15425, 2404, 13160, -14810, 804, 14053,
    7005, -15892, 13160, -803, -12139, 16207, -8422, -5519, 15426, -14052, 2404, 11003, -16363, 9760, 3981, -14810,
    5520, -14052, 16207, -11002, 804, 9760, -15892, 14811, -7004, -3980, 13160, -16363, 12140, -2403, -8422, 15426,
    3981, -11002, 15426, -16206, 13160, -7004, -803, 8423, -14052, 16364, -14810, 9760, -2403, -5519, 12140, -15892,
    2404, -7004, 11003, -14052, 15893, -16363, 15426, -13159, 9760, -5519, 804, 3981, -8422, 12140, -14810, 16207,
    804, -2403, 3981, -5519, 7005, -8422, 9760, -11002, 12140, -13159, 14053, -14810, 15426, -15892, 16207, -16363,
    16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384,
    16305, 15679, 14449, 12665, 10394, 7723, 4756, 1606, -1605, -4755, -7722, -10393, -12664, -14448, -15678, -16304,
    16069, 13623, 9102, 3196, -3195, -9101, -13622, -16068, -16068, -13622, -9101, -3195, 3196, 9102, 13623, 16069,
    15679, 10394, 1606, -7722, -14448, -16304, -12664, -4755, 4756, 12665, 16305, 14449, 7723, -1605, -10393, -15678,
    15137, 6270, -6269, -15136, -15136, -6269, 6270, 15137, 15137, 6270, -6269, -15136, -15136, -6269, 6270, 15137,
    14449, 1606, -12664, -15678, -4755, 10394, 16305, 7723, -7722, -16304, -10393, 4756, 15679, 12665, -1605, -14448,
    13623, -3195, -16068, -9101, 9102, 16069, 3196, -13622, -13622, 3196, 16069, 9102, -9101, -16068, -3195, 13623,
    12665, -7722, -15678, 1606, 16305, 4756, -14448, -10393, 10394, 14449, -4755, -16304, -1605, 15679, 7723, -12664,
    11585, -11584, -11584, 11585, 11585, -11584, -11584, 11585, 11585, -11584, -11584, 11585, 11585, -11584, -11584, 11585,
    10394, -14448, -4755, 16305, -1605, -15678, 7723, 12665, -12664, -7722, 15679, 1606, -16304, 4756, 14449, -10393,
    9102, -16068, 3196, 13623, -13622, -3195, 16069, -9101, -9101, 16069, -3195, -13622, 13623, 3196, -16068, 9102,
    7723, -16304, 10394, 4756, -15678, 12665, 1606, -14448, 14449, -1605, -12664, 15679, -4755, -10393, 16305, -7722,
    6270, -15136, 15137, -6269, -6269, 15137, -15136, 6270, 6270, -15136, 15137, -6269, -6269, 15137, -15136, 6270,
    4756, -12664, 16305, -14448, 7723, 1606, -10393, 15679, -15678, 10394, -1605, -7722, 14449, -16304, 12665, -4755,
    3196, -9101, 13623, -16068, 16069, -13622, 9102, -3195, -3195, 9102, -13622, 16069, -16068, 13623, -9101, 3196,
    1606, -4755, 7723, -10393, 12665, -14448, 15679, -16304, 16305, -15678, 14449, -12664, 10394, -7722, 4756, -1605
};
namespace Snd {
static __forceinline __m64 ReverseWords(__m64 q)
{
    const __m64 hi = _mm_srli_si64(_mm_unpackhi_pi32(q, q), 16); // [w3,w2,w3,0]
    const __m64 lo = _mm_srli_si64(_mm_unpacklo_pi32(q, q), 16); // [w1,w0,w1,0]
    return _mm_unpacklo_pi32(hi, lo);                             // [w3,w2,w1,w0]
}
}
namespace Snd {
static __forceinline int16_t DctTap(const __m64* row, const __m64* s)
{
    __m64 t = _mm_add_pi32(_mm_madd_pi16(row[0], s[0]), _mm_madd_pi16(row[1], s[1]));
    t = _mm_add_pi32(t, _mm_madd_pi16(row[2], s[2]));
    t = _mm_add_pi32(t, _mm_madd_pi16(row[3], s[3]));
    t = _mm_add_pi32(t, _mm_srli_si64(t, 32));
    t = _mm_srai_pi32(t, 14);
    return (int16_t)_mm_cvtsi64_si32(t);
}
}
namespace Snd {
struct Resampler;
}
namespace Snd {
struct SndSource {
    int (*read)(SndSource* self, int count, float* dst0, float* dst1, char fmt);
};
}
namespace Snd {
typedef int (*SndResampleFn)(int count, float* dst, float* src, int* num, int* frac,
                             int stepHi, int stepLo);
}
namespace Snd {
union Fixed16 {
    int value;
    struct { short frac; short whole; }; // +0x00 / +0x02
};
}
namespace Snd {
struct Resampler {
    int (*process)(Resampler* self, int count, float* out0, float* out1); // 0x00 entry point
    int            field_04;   // 0x04
    SndSource*     source;     // 0x08
    int            field_0c;   // 0x0c
    int            field_10;   // 0x10
    int            field_14;   // 0x14
    short          field_18;   // 0x18
    char           fmt;        // 0x1a
    char           field_1b;   // 0x1b
    union { int step; float step_f; }; // 0x1c fixed-point step (1.0 == 0x10000)
    Fixed16        acc;        // 0x20 fractional accumulator
    SndResampleFn  resample;   // 0x24
    short          flag_28;    // 0x28 priming flag
    short          nOffset;    // 0x2a filter offset
    float          hist[4];    // 0x2c previous output samples
    char           pad_3c[0x14]; // 0x3c..0x4f
    float          ratio;      // 0x50
};
}
namespace Snd {
void FUN_01173100(void* state);                                        // 0x01173100
}
namespace Snd {
void FUN_01173130(void* state, int count, float* out0, float* out1);   // 0x01173130
}
namespace Snd {
void FUN_01173460(void* state, int mode);                              // 0x01173460
}
namespace Snd {
void FUN_01173730(void* state, int count, float* out0, float* out1);   // 0x01173730
}
namespace Snd {
int  FUN_01173770(int count, float* dst, float* src, int* num, int* frac, int hi, int lo); // 0x01173770
}
namespace Snd {
int  FUN_01173c10(int count, float* dst, float* src, int* num, int* frac, int hi, int lo); // 0x01173c10
}
namespace Snd {
int  FUN_01173eb0(int count, float* dst, float* src, int* num, int* frac, int hi, int lo); // 0x01173eb0
}
namespace Snd {
int  FUN_01173fa0(int count, float* dst, float* src, int* num, int* frac, int hi, int lo); // 0x01173fa0
}
namespace Snd {
struct SndPitchState {
    char  pad_00[0x20];
    float field_20;   // 0x20
    float field_24;   // 0x24
};
}
// ---- items of slice s01168520 end

// ---- items of slice s01169f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
float g[0x40];   // 0x016f1740
// ---- items of slice s01169f50 end

// ---- items of slice s0116dd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const float g_antialiasCs_14da818[8];              // 0x014da818
extern "C" const float g_antialiasCa_14da838[8];              // 0x014da838
extern "C" const float g_antialiasCaPos_14cba4c[8];           // 0x014cba4c
struct SFBandIndex_s0116dd70 {
    short l[23];      // +0x00
    u8    s[14];      // +0x2e
};
extern "C" SFBandIndex_s0116dd70 sfBandIndexLSF_14da570[3];   // 0x014da570
extern "C" const u8 g_reorderWidths_14cba10[];                // 0x014cba10
struct III_gr_info_s0116dd70 {
    u8  pad00[0x07];            // +0x00
    u8  windowSwitchingFlag;    // +0x07
    u8  blockType;              // +0x08
    u8  mixedBlockFlag;         // +0x09
    u8  pad0a[0x0e];
};
class HELPER_CMpegLayer3Base_s0116dd70 {
public:
    void Reorder(int gr, int ch, float* src, float* dst);       // 0x0116dd70
    void Antialias(int gr, int ch, float* xr);                  // 0x0116e250

    u8     mBaseHead[0x30];                 // +0x00 .. +0x2f  (vftable + base state)
    u8     samplingFrequency;               // +0x30
    u8     mBaseTail[0x17];                 // +0x31 .. +0x47
    u8     pad48[0x28];                     // +0x48 .. +0x6f
    III_gr_info_s0116dd70 gr_info[4];       // +0x70
};
// ---- items of slice s0116dd70 end

// ---- items of slice s0116efb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const float g_imdct36WinHybrid[];      // 0x014da860 IMDCT36 windows (hybrid stage)
namespace rw {
namespace audio {
namespace core {
class System_s0116_efb0 {
public:
    void* Alloc(int size, const char* name, int align, int flags);  // 0x0112c820
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0116_efb0* g_audioSystem;                    // 0x016e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
void* AudioMemset(void* dst, int c, unsigned n); // 0x011e073e memset
}
}
}
namespace rw {
namespace audio {
namespace core {
static void CallImdct36X1(const float* win, float* out, float* in)
{
    _alloca(4);
    HELPER_Imdct36X1(win, out, in);
}
}
}
}
namespace rw {
namespace audio {
namespace core {
struct cMpegHybridDecoder {
    uint8_t     pad00[0x3c];                    // +0x000
    uint8_t     mChannels;                      // +0x03c  hybrid planes allocated
    uint8_t     pad3d[0x70 - 0x3d];             // +0x03d
    GranuleInfo mGranules[4];                   // +0x070  [2*granule + channel]
    uint8_t     padD0[0x1c8 - 0xd0];            // +0x0d0
    float*      mpHybridHistory;                // +0x1c8  one 0x900-byte plane per granule

    void Hybrid(int gr, int ch, float* buf);    // 0x0116fc20
};
}
}
}
// ---- items of slice s0116efb0 end

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

// @ 0x011661b0
namespace rw { namespace audio { namespace core {
void HELPER_Imdct12X1(float* in, float* out)
{
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

        // in-place prefix sums (the original re-reads the slots it has already overwritten)
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
}}}  // namespace rw::audio::core

// @ 0x011666d0
static void Imdct36(float* in, float* out, const float* win)
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

// @ 0x01167190
void FUN_01167190(float* pOut, const float* pIn, float* pHistory)
{
    for (unsigned int lane = 0; lane < 4; ++lane)
    {
        ADD(0);  ADD(4);  ADD(8);  ADD(12); ADD(16); ADD(20);
        ADD(24); ADD(28); ADD(32); ADD(36); ADD(40); ADD(44);
        ADD(48); ADD(52); ADD(56); ADD(60); ADD(64); ADD(68);

        ROT(0);  ROT(4);  ROT(8);  ROT(12); ROT(16); ROT(20);
        ROT(24); ROT(28); ROT(32); ROT(36); ROT(40); ROT(44);
        ROT(48); ROT(52); ROT(56); ROT(60); ROT(64); ROT(68);
    }
}

// @ 0x011673e0
void HELPER_Imdct12X4Implementation::Transform(unsigned int nChannel, unsigned int nBlock, float* pOutput)
{
    if (mpWorkBuffer == 0)
    {
        unsigned int nBytes = (unsigned int)mnChannelCount * 0x900;
        mpWorkBuffer = g_pfnAudioAlloc(nBytes);
        if (mpWorkBuffer == 0)
            pOutput[0] = 0.0f;
        else
            memset(mpWorkBuffer, 0, nBytes);
    }

    unsigned int nBand = nBlock + 2 * nChannel;
    float* pWork = (float*)((char*)mpWorkBuffer + nChannel * 0x900);
    float sTime[144];
    unsigned int nDone = 0;

    if (mBands[nBand].mbLeftWindow && mBands[nBand].mbRightWindow)
    {
        Imdct36(pOutput + 0, sTime + 0, kImdctWindows[0]);
        Imdct36(pOutput + 1, sTime + 1, kImdctWindows[0]);
        HELPER_Imdct12X1(sTime + 2, pOutput + 2);
        HELPER_Imdct12X1(sTime + 3, pOutput + 3);
        FUN_01167190(pOutput, sTime, pWork);
        nDone = 1;
    }

    if (mBands[nBand].mnWindowSequence == 2)
    {
        if (nDone < 8)
        {
            float* pBlock = pOutput + nDone * 72;
            unsigned int nLeft = 8 - nDone;
            do
            {
                HELPER_Imdct12X1(sTime + 0, pBlock + 0);
                HELPER_Imdct12X1(sTime + 1, pBlock + 1);
                HELPER_Imdct12X1(sTime + 2, pBlock + 2);
                HELPER_Imdct12X1(sTime + 3, pBlock + 3);
                FUN_01167190(pBlock, sTime, pWork);
                pBlock += 72;
                pWork += 72;
            } while (--nLeft != 0);
        }
    }
    else if (nDone < 8)
    {
        const float* pWindow = kImdctWindows[mBands[nBand].mnWindowSequence];
        float* pBlock = pOutput + nDone * 72;
        unsigned int nLeft = 8 - nDone;
        do
        {
            for (unsigned int j = 0; j < 4; ++j)
                Imdct36(pBlock + j, sTime + j, pWindow);
            FUN_01167190(pBlock, sTime, pWork);
            pBlock += 72;
            pWork += 72;
        } while (--nLeft != 0);
    }
}

// @ 0x011675c0
void NegateRows(Row* rows)
{
    Row* end = (Row*)((char*)rows + 0x900);
    for (Row* r = rows; r < end; ++r)
    {
        NEGATE_CELL(0) NEGATE_CELL(1) NEGATE_CELL(2)
        NEGATE_CELL(3) NEGATE_CELL(4) NEGATE_CELL(5)
        NEGATE_CELL(6) NEGATE_CELL(7) NEGATE_CELL(8)
    }
}

// @ 0x01167cf0
void PackHeightBlock(const float* src, short* dst)
{
    short* end = dst + 576;
    for (short* out = dst; out < end; out += 32, src += 4) {
        PACK_ROW(0)
        PACK_ROW(1)
        PACK_ROW(2)
        PACK_ROW(3)
        PACK_ROW(4)
        PACK_ROW(5)
        PACK_ROW(6)
        PACK_ROW(7)
    }
}

// @ 0x011684c0
int ReadBigEndian(const unsigned char* data, int count)
{
    int value = 0;
    int n = count;
    const unsigned char* p = data;
    while (count != 0) {
        --count;
        value = (value << 8) + *p;
        ++p;
    }
    if (n == 1) {
        if (value > 0x7f)
            value -= 0x100;
    } else if (n == 2) {
        if (value > 0x7fff)
            value -= 0x10000;
    } else if (n == 3 && value > 0x7fffff) {
        value -= 0x1000000;
    }
    return value;
}

// @ 0x01168520
namespace Snd {
int FUN_01168520(Resampler* self, int count, float* out0, float* out1)
{
    if (self->source != 0) {
        count = self->source->read(self->source, count, out1, out0, self->fmt);
        if (count <= 0)
            return count;
    }
    FUN_01173130(&self->step, count, out0, out1);
    return count;
}
}  // namespace Snd

// @ 0x01168580
namespace Snd {
int FUN_01168580(Resampler* self)
{
    self->source = 0;
    self->field_0c = 0;
    self->field_10 = 0;
    self->field_14 = 0;
    self->field_1b = 0;
    self->field_04 = 0;
    self->process = FUN_01168520;
    FUN_01173100(&self->step);
    return 0;
}
}  // namespace Snd

// @ 0x011685b0
namespace Snd {
void FUN_011685b0(Resampler* self, int* values)
{
    self->ratio = (float)(values[0] >> 7) / (float)(values[1] >> 8);
    FUN_01173460(&self->step, 3);
}
}  // namespace Snd

// @ 0x011685f0
namespace Snd {
int FUN_011685f0(Resampler* self, int count, float* out0, float* out1)
{
    if (self->source != 0) {
        int result = self->source->read(self->source, count, out1, out0, self->fmt);
        if (result <= 0)
            return result;
    }
    FUN_01173730(&self->step, count, out0, out1);
    return count;
}
}  // namespace Snd

// @ 0x01168640
namespace Snd {
int FUN_01168640(Resampler* self)
{
    self->source = 0;
    self->field_0c = 0;
    self->field_10 = 0;
    self->field_14 = 0;
    self->field_1b = 0;
    self->field_04 = 0;
    self->process = FUN_011685f0;
    self->step_f = 0.0f;
    return 0;
}
}  // namespace Snd

// @ 0x01168670
namespace Snd {
void FUN_01168670(SndPitchState* self, int* values)
{
    float* out = &self->field_20;
    float r = ((float)values[0] * 2.0f) / (float)values[1];
    out[0] = 1.0f - r;
    _ReadWriteBarrier();
    out[1] = r;
    out[1] = (float)values[2] * r * 0.00390625f;
    out[0] = (float)values[2] * out[0] * 0.00390625f;
}
}  // namespace Snd

// @ 0x011686e0
namespace Snd {
unsigned int FUN_011686e0()
{
    unsigned int flags = __readeflags();
    __writeeflags(flags ^ 0x200000);
    unsigned int after = __readeflags();
    __writeeflags(flags);
    return after ^ flags;
}
}  // namespace Snd

// @ 0x011686fd
namespace Snd {
void FUN_011686fd(unsigned int* out, int leaf)
{
    int regs[4];
    __cpuid(regs, leaf);
    out[0] = (unsigned int)regs[0];
    out[1] = (unsigned int)regs[1];
    out[2] = (unsigned int)regs[2];
    out[3] = (unsigned int)regs[3];
}
}  // namespace Snd

// @ 0x01168730
namespace Snd {
void FUN_01168730(Resampler* self, int pitch)
{
    self->step = pitch;
}
}  // namespace Snd

// @ 0x01168740
namespace Snd {
int FUN_01168740(Resampler* self, int count, float* out0, float* out1)
{
    int n = count;
    float* tail = out1;
    float* dst = out0;
    int result = count;
    int frac;
    int num;
    if (self->step == 0x10000) {
        int readCount;
        if (self->flag_28 == 0) {
            readCount = n - self->nOffset + 4;
        } else {
            readCount = n;
            for (int i = 0; i < 4 - self->nOffset; ++i)
                *tail++ = self->hist[self->nOffset + i];
        }
        if (self->source != 0)
            result = self->source->read(self->source, readCount, dst, tail, self->fmt);
        if (result <= 0) {
            if (self->flag_28 == 0)
                self->flag_28 = 1;
            self->hist[0] = 0.0f;
            self->hist[1] = 0.0f;
            self->hist[2] = 0.0f;
            self->hist[3] = 0.0f;
            return result;
        }
        if (self->flag_28 == 0) {
            self->flag_28 = 1;
            tail += n - self->nOffset;
        } else {
            tail += n - 4;
        }
        self->hist[0] = tail[0];
        self->hist[1] = tail[1];
        self->hist[2] = tail[2];
        self->hist[3] = tail[3];
        return n;
    } else {
        int readCount = (int)((unsigned)(self->step * n + self->acc.value) >> 16);
        if (self->flag_28 == 0) {
            readCount += 4 - self->nOffset;
            for (int i = 0; i < self->nOffset; ++i)
                *dst++ = 0.0f;
        } else {
            dst[0] = self->hist[0];
            dst[1] = self->hist[1];
            dst[2] = self->hist[2];
            dst[3] = self->hist[3];
            dst += 4;
        }
        if (readCount <= 0 || self->source == 0 ||
            (result = self->source->read(self->source, readCount, out1, dst, self->fmt)) > 0) {
            if (self->flag_28 != 0)
                dst += self->nOffset - 4;
            else
                self->flag_28 = 1;
            int frac;
            int num;
            num = 0;
            frac = self->acc.value << 16;
            self->resample(n, dst, out1, &num, &frac, (unsigned)self->step >> 16, self->step << 16);
            int acc = (num << 16) | ((unsigned)frac >> 16);
            self->acc.value = acc;
            dst += (int)((unsigned)acc >> 16) - self->nOffset;
            self->hist[0] = dst[0];
            self->hist[1] = dst[1];
            self->hist[2] = dst[2];
            self->hist[3] = dst[3];
            self->acc.whole = 0;
            return n;
        }
        if (self->flag_28 == 0)
            self->flag_28 = 1;
        self->hist[0] = 0.0f;
        self->hist[1] = 0.0f;
        self->hist[2] = 0.0f;
        self->hist[3] = 0.0f;
        return result;
    }
}
}  // namespace Snd

// @ 0x01168960
namespace Snd {
void FUN_01168960(Resampler* self, unsigned char flags, int half)
{
    self->process = FUN_01168740;
    self->field_04 = 0;
    self->acc.value = 0;
    self->flag_28 = 0;
    self->nOffset = 0;
    if (half == 0) {
        if ((flags & 2) != 0)
            self->resample = FUN_01173fa0;
        else
            self->resample = FUN_01173eb0;
    } else {
        self->nOffset = 1;
        if ((flags & 2) != 0)
            self->resample = FUN_01173c10;
        else
            self->resample = FUN_01173770;
    }
    self->hist[0] = 0.0f;
    self->hist[1] = 0.0f;
    self->hist[2] = 0.0f;
    self->hist[3] = 0.0f;
}
}  // namespace Snd

// @ 0x011689e0
namespace Snd {
void Dct32(int16_t* pColumnA, int16_t* pColumnB, const int16_t* pIn)
{
    const __m64* const x = (const __m64*)pIn;
    const __m64* const mat = (const __m64*)KS_DctMatrix;

    // Butterfly: x[i] +/- x[31-i], with x[31-i] taken from the reversed qwords 7..4.
    const __m64 r7 = ReverseWords(x[7]); // [x31,x30,x29,x28]
    const __m64 r6 = ReverseWords(x[6]); // [x27,x26,x25,x24]
    const __m64 r5 = ReverseWords(x[5]); // [x23,x22,x21,x20]
    const __m64 r4 = ReverseWords(x[4]); // [x19,x18,x17,x16]

    const __m64 sv[4] = {
        _mm_add_pi16(x[0], r7), _mm_add_pi16(x[1], r6), _mm_add_pi16(x[2], r5), _mm_add_pi16(x[3], r4),
    };
    const __m64 dv[4] = {
        _mm_sub_pi16(x[0], r7), _mm_sub_pi16(x[1], r6), _mm_sub_pi16(x[2], r5), _mm_sub_pi16(x[3], r4),
    };

    // Even outputs Y[2j] from the sums, with the even matrix (rows 16..31 = qwords 64..127).
    int16_t y;
    y = DctTap(mat + 64, sv); pColumnA[256] = y;
    y = DctTap(mat + 68, sv); pColumnA[224] = y;
    y = DctTap(mat + 72, sv); pColumnA[192] = y;
    y = DctTap(mat + 76, sv); pColumnA[160] = y;
    y = DctTap(mat + 80, sv); pColumnA[128] = y;
    y = DctTap(mat + 84, sv); pColumnA[96] = y;
    y = DctTap(mat + 88, sv); pColumnA[64] = y;
    y = DctTap(mat + 92, sv); pColumnA[32] = y;
    y = DctTap(mat + 96, sv); pColumnA[0] = y; pColumnB[0] = y;
    y = DctTap(mat + 100, sv); pColumnB[32] = y;
    y = DctTap(mat + 104, sv); pColumnB[64] = y;
    y = DctTap(mat + 108, sv); pColumnB[96] = y;
    y = DctTap(mat + 112, sv); pColumnB[128] = y;
    y = DctTap(mat + 116, sv); pColumnB[160] = y;
    y = DctTap(mat + 120, sv); pColumnB[192] = y;
    y = DctTap(mat + 124, sv); pColumnB[224] = y;

    // Odd outputs Y[2k+1] from the differences, with the odd matrix (rows 0..15 = qwords 0..63).
    y = DctTap(mat + 0, dv);  pColumnA[240] = y;
    y = DctTap(mat + 4, dv);  pColumnA[208] = y;
    y = DctTap(mat + 8, dv);  pColumnA[176] = y;
    y = DctTap(mat + 12, dv); pColumnA[144] = y;
    y = DctTap(mat + 16, dv); pColumnA[112] = y;
    y = DctTap(mat + 20, dv); pColumnA[80] = y;
    y = DctTap(mat + 24, dv); pColumnA[48] = y;
    y = DctTap(mat + 28, dv); pColumnA[16] = y;
    y = DctTap(mat + 32, dv); pColumnB[16] = y;
    y = DctTap(mat + 36, dv); pColumnB[48] = y;
    y = DctTap(mat + 40, dv); pColumnB[80] = y;
    y = DctTap(mat + 44, dv); pColumnB[112] = y;
    y = DctTap(mat + 48, dv); pColumnB[144] = y;
    y = DctTap(mat + 52, dv); pColumnB[176] = y;
    y = DctTap(mat + 56, dv); pColumnB[208] = y;
    y = DctTap(mat + 60, dv); pColumnB[240] = y;
}
}  // namespace Snd

// @ 0x01169f50
void Dct32(float *in, float *param_1, float *param_2)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;

  fVar1 = (*in - in[0x1f]) * 0.500603;
  fVar2 = (in[1] - in[0x1e]) * 0.50547093;
  fVar3 = (in[2] - in[0x1d]) * 0.5154473;
  fVar4 = (in[3] - in[0x1c]) * 0.5310426;
  fVar5 = (in[4] - in[0x1b]) * 0.5531039;
  fVar7 = (in[5] - in[0x1a]) * 0.582935;
  fVar18 = (in[6] - in[0x19]) * 0.6225041;
  fVar19 = (in[7] - in[0x18]) * 0.6748083;
  fVar20 = (in[8] - in[0x17]) * 0.7445363;
  fVar21 = (in[9] - in[0x16]) * 0.8393496;
  fVar22 = (in[10] - in[0x15]) * 0.9725682;
  fVar23 = (in[0xb] - in[0x14]) * 1.1694399;
  fVar24 = (in[0xc] - in[0x13]) * 1.4841646;
  fVar25 = (in[0xd] - in[0x12]) * 2.057781;
  fVar26 = (in[0xe] - in[0x11]) * 3.4076085;
  fVar27 = (in[0xf] - in[0x10]) * 10.190008;
  fVar28 = (in[0xf] + in[0x10]) + (*in + in[0x1f]);
  fVar9 = ((*in + in[0x1f]) - (in[0xf] + in[0x10])) * 0.5024193;
  fVar29 = (in[0x11] + in[0xe]) + (in[1] + in[0x1e]);
  fVar10 = ((in[1] + in[0x1e]) - (in[0x11] + in[0xe])) * 0.5224986;
  fVar30 = (in[0xd] + in[0x12]) + (in[0x1d] + in[2]);
  fVar11 = ((in[0x1d] + in[2]) - (in[0xd] + in[0x12])) * 0.56694406;
  fVar31 = (in[0x13] + in[0xc]) + (in[3] + in[0x1c]);
  fVar12 = ((in[3] + in[0x1c]) - (in[0x13] + in[0xc])) * 0.6468218;
  fVar32 = (in[0xb] + in[0x14]) + (in[0x1b] + in[4]);
  fVar13 = ((in[0x1b] + in[4]) - (in[0xb] + in[0x14])) * 0.7881546;
  fVar33 = (in[0x15] + in[10]) + (in[5] + in[0x1a]);
  fVar14 = ((in[5] + in[0x1a]) - (in[0x15] + in[10])) * 1.0606776;
  fVar34 = (in[9] + in[0x16]) + (in[0x19] + in[6]);
  fVar15 = ((in[0x19] + in[6]) - (in[9] + in[0x16])) * 1.7224472;
  fVar35 = (in[0x17] + in[8]) + (in[7] + in[0x18]);
  fVar16 = ((in[7] + in[0x18]) - (in[0x17] + in[8])) * 5.1011486;
  fVar17 = fVar27 + fVar1;
  fVar1 = (fVar1 - fVar27) * 0.5024193;
  fVar36 = fVar26 + fVar2;
  fVar26 = (fVar2 - fVar26) * 0.5224986;
  fVar2 = fVar25 + fVar3;
  fVar27 = (fVar3 - fVar25) * 0.56694406;
  fVar25 = fVar24 + fVar4;
  fVar24 = (fVar4 - fVar24) * 0.6468218;
  fVar4 = fVar23 + fVar5;
  fVar6 = (fVar5 - fVar23) * 0.7881546;
  fVar3 = fVar22 + fVar7;
  fVar8 = (fVar7 - fVar22) * 1.0606776;
  fVar5 = fVar21 + fVar18;
  fVar7 = (fVar18 - fVar21) * 1.7224472;
  fVar21 = fVar20 + fVar19;
  fVar18 = (fVar19 - fVar20) * 5.1011486;
  fVar19 = fVar35 + fVar28;
  fVar20 = (fVar28 - fVar35) * 0.5097956;
  fVar35 = fVar34 + fVar29;
  fVar22 = (fVar29 - fVar34) * 0.6013449;
  fVar29 = fVar33 + fVar30;
  fVar23 = (fVar30 - fVar33) * 0.8999762;
  fVar30 = fVar32 + fVar31;
  fVar28 = (fVar31 - fVar32) * 2.5629156;
  fVar31 = fVar16 + fVar9;
  fVar9 = (fVar9 - fVar16) * 0.5097956;
  fVar16 = fVar15 + fVar10;
  fVar10 = (fVar10 - fVar15) * 0.6013449;
  fVar15 = fVar14 + fVar11;
  fVar11 = (fVar11 - fVar14) * 0.8999762;
  fVar14 = fVar13 + fVar12;
  fVar12 = (fVar12 - fVar13) * 2.5629156;
  g[48] = fVar21 + fVar17;
  fVar13 = (fVar17 - fVar21) * 0.5097956;
  fVar17 = fVar5 + fVar36;
  fVar32 = (fVar36 - fVar5) * 0.6013449;
  fVar21 = fVar3 + fVar2;
  fVar2 = (fVar2 - fVar3) * 0.8999762;
  fVar3 = fVar4 + fVar25;
  fVar4 = (fVar25 - fVar4) * 2.5629156;
  fVar5 = fVar18 + fVar1;
  fVar1 = (fVar1 - fVar18) * 0.5097956;
  fVar25 = fVar7 + fVar26;
  fVar26 = (fVar26 - fVar7) * 0.6013449;
  fVar18 = fVar8 + fVar27;
  fVar27 = (fVar27 - fVar8) * 0.8999762;
  fVar8 = fVar6 + fVar24;
  fVar7 = (fVar24 - fVar6) * 2.5629156;
  g[32] = fVar30 + fVar19;
  g[35] = (fVar19 - fVar30) * 0.5411961;
  g[33] = fVar29 + fVar35;
  g[34] = (fVar35 - fVar29) * 1.306563;
  g[36] = fVar20 + fVar28;
  g[39] = (fVar20 - fVar28) * 0.5411961;
  g[37] = fVar22 + fVar23;
  g[38] = (fVar22 - fVar23) * 1.306563;
  g[40] = fVar14 + fVar31;
  g[43] = (fVar31 - fVar14) * 0.5411961;
  g[41] = fVar15 + fVar16;
  g[42] = (fVar16 - fVar15) * 1.306563;
  g[44] = fVar9 + fVar12;
  g[47] = (fVar9 - fVar12) * 0.5411961;
  g[45] = fVar10 + fVar11;
  g[46] = (fVar10 - fVar11) * 1.306563;
  g[51] = (g[48] - fVar3) * 0.5411961;
  g[48] = g[48] + fVar3;
  g[50] = (fVar17 - fVar21) * 1.306563;
  g[49] = fVar17 + fVar21;
  g[52] = fVar4 + fVar13;
  g[55] = (fVar13 - fVar4) * 0.5411961;
  g[53] = fVar2 + fVar32;
  g[54] = (fVar32 - fVar2) * 1.306563;
  g[56] = fVar5 + fVar8;
  g[59] = (fVar5 - fVar8) * 0.5411961;
  g[58] = (fVar25 - fVar18) * 1.306563;
  g[57] = fVar25 + fVar18;
  g[60] = fVar7 + fVar1;
  g[63] = (fVar1 - fVar7) * 0.5411961;
  g[61] = fVar27 + fVar26;
  g[62] = (fVar26 - fVar27) * 1.306563;
  g[0] = g[33] + g[32];
  g[1] = (g[32] - g[33]) * 0.70710677;
  g[3] = (g[35] - g[34]) * 0.70710677;
  g[2] = g[3] + (g[35] + g[34]);
  fVar1 = (g[36] - g[37]) * 0.70710677;
  g[7] = (g[39] - g[38]) * 0.70710677;
  fVar2 = g[7] + (g[39] + g[38]);
  g[4] = fVar2 + (g[37] + g[36]);
  g[6] = fVar2 + fVar1;
  g[5] = g[7] + fVar1;
  g[9] = (g[40] - g[41]) * 0.70710677;
  g[8] = g[40] + g[41];
  g[11] = (g[43] - g[42]) * 0.70710677;
  g[10] = g[11] + (g[42] + g[43]);
  fVar1 = (g[44] - g[45]) * 0.70710677;
  g[15] = (g[47] - g[46]) * 0.70710677;
  fVar2 = g[15] + (g[46] + g[47]);
  g[12] = fVar2 + (g[44] + g[45]);
  g[14] = fVar2 + fVar1;
  g[13] = g[15] + fVar1;
  g[16] = g[49] + g[48];
  g[17] = (g[48] - g[49]) * 0.70710677;
  g[19] = (g[51] - g[50]) * 0.70710677;
  g[18] = (g[51] + g[50]) + g[19];
  g[23] = (g[55] - g[54]) * 0.70710677;
  fVar2 = (g[55] + g[54]) + g[23];
  g[20] = (g[53] + g[52]) + fVar2;
  fVar1 = (g[52] - g[53]) * 0.70710677;
  g[22] = fVar1 + fVar2;
  g[21] = fVar1 + g[23];
  g[24] = g[56] + g[57];
  g[25] = (g[56] - g[57]) * 0.70710677;
  g[27] = (g[59] - g[58]) * 0.70710677;
  g[26] = (g[58] + g[59]) + g[27];
  fVar1 = (g[60] - g[61]) * 0.70710677;
  g[31] = (g[63] - g[62]) * 0.70710677;
  fVar2 = (g[62] + g[63]) + g[31];
  g[30] = fVar1 + fVar2;
  g[28] = (g[60] + g[61]) + fVar2;
  g[29] = fVar1 + g[31];
  param_1[0x100] = g[0];
  param_1[0xc0] = g[4];
  param_1[0x80] = g[2];
  param_1[0x40] = g[6];
  *param_1 = g[1];
  *param_2 = g[1];
  param_2[0x40] = g[5];
  param_2[0x80] = g[3];
  param_2[0xc0] = g[7];
  g[8] = g[12] + g[8];
  param_1[0xe0] = g[8];
  g[12] = g[12] + g[10];
  param_1[0xa0] = g[12];
  g[10] = g[14] + g[10];
  param_1[0x60] = g[10];
  g[14] = g[14] + g[9];
  param_1[0x20] = g[14];
  g[9] = g[13] + g[9];
  param_2[0x20] = g[9];
  g[13] = g[13] + g[11];
  param_2[0x60] = g[13];
  g[11] = g[15] + g[11];
  param_2[0xa0] = g[11];
  param_2[0xe0] = g[15];
  g[24] = g[24] + g[28];
  param_1[0xf0] = g[16] + g[24];
  param_1[0xd0] = g[20] + g[24];
  g[28] = g[26] + g[28];
  param_1[0xb0] = g[20] + g[28];
  param_1[0x90] = g[18] + g[28];
  g[26] = g[26] + g[30];
  param_1[0x70] = g[18] + g[26];
  param_1[0x50] = g[22] + g[26];
  g[30] = g[25] + g[30];
  param_1[0x30] = g[22] + g[30];
  param_1[0x10] = g[17] + g[30];
  g[25] = g[25] + g[29];
  param_2[0x10] = g[17] + g[25];
  param_2[0x30] = g[21] + g[25];
  g[29] = g[27] + g[29];
  param_2[0x50] = g[21] + g[29];
  param_2[0x70] = g[19] + g[29];
  g[27] = g[27] + g[31];
  param_2[0x90] = g[19] + g[27];
  param_2[0xb0] = g[23] + g[27];
  param_2[0xd0] = g[23] + g[31];
  param_2[0xf0] = g[31];
  return;
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

// @ 0x0116dd70
void HELPER_CMpegLayer3Base_s0116dd70::Reorder(int gr, int ch, float* src, float* dst)
{
    III_gr_info_s0116dd70* gi = &gr_info[ch + 2 * gr];
    if (!(gi->windowSwitchingFlag && gi->blockType == 2))
        return;

    if (gi->mixedBlockFlag) {
        for (int i = 0; i < 36; i++)
            dst[i] = src[i];

        const u8* sfb = sfBandIndexLSF_14da570[samplingFrequency].s;
        for (int b = 3; b < 13; b++) {
            int start = sfb[b];
            int width = sfb[b + 1] - start;
            int base = 3 * start;
            for (int j = 0; j < width; j++)
                for (int win = 0; win < 3; win++)
                    dst[base + 3 * j + win] = src[base + win * width + j];
        }
    } else {
        for (int b = 0; b < 3; b++)
            for (int j = 0; j < 4; j++)
                for (int win = 0; win < 3; win++)
                    dst[12 * b + 3 * j + win] = src[12 * b + 4 * win + j];

        int base = 36;
        for (int s = 0; s < 10; s++) {
            int width = g_reorderWidths_14cba10[samplingFrequency * 10 + s];
            if (width <= 0)
                continue;
            for (int j = 0; j < width; j++)
                for (int win = 0; win < 3; win++)
                    dst[base + 3 * j + win] = src[base + win * width + j];
            base += 3 * width;
        }
    }
}

// @ 0x0116e250
void HELPER_CMpegLayer3Base_s0116dd70::Antialias(int gr, int ch, float* xr)
{
    III_gr_info_s0116dd70* gi = &gr_info[ch + 2 * gr];

    float* end;
    if (gi->windowSwitchingFlag && gi->blockType == 2) {
        if (!gi->mixedBlockFlag)
            return;
        end = xr + 18;
    } else {
        end = xr + 558;
    }

    for (float* p = xr + 18; p <= end; p += 18) {
        for (int ss = 0; ss < 8; ss++) {
            float u = p[-1 - ss];
            float v = p[ss];
            p[-1 - ss] = u * g_antialiasCs_14da818[ss] - v * g_antialiasCa_14da838[ss];
            p[ss]      = v * g_antialiasCs_14da818[ss] - u * g_antialiasCaPos_14cba4c[7 - ss];
        }
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

// @ 0x0116fc20
namespace rw { namespace audio { namespace core {
void cMpegHybridDecoder::Hybrid(int gr, int ch, float* buf)
{
    __declspec(align(16)) float tmp[0x240 / 4];

    if (mpHybridHistory == 0) {
        mpHybridHistory = (float*)g_audioSystem->Alloc(mChannels * 0x900, "MP3HybridHistory", 0x10, 0);
        if (mpHybridHistory == 0) {
            // The original stores a zero dword here (the Alloc result was already 0 in EAX);
            // an integer store keeps the same bytes without touching XMM.
            *(unsigned int*)buf = 0;
            return;
        }
        AudioMemset(mpHybridHistory, 0, mChannels * 0x900);
    }
    GranuleInfo* gi = &mGranules[gr * 2 + ch];
    float* hist = (float*)((uint8_t*)mpHybridHistory + gr * 0x900);
    int flag = 0;
    if (gi->windowSwitchingFlag && gi->mixedBlockFlag) {
        uint8_t* t = (uint8_t*)tmp;
        uint8_t* in = (uint8_t*)buf;
        CallImdct36X1(g_imdct36WinHybrid, (float*)(t + 0), (float*)(in + 0));
        CallImdct36X1(g_imdct36WinHybrid, (float*)(t + 4), (float*)(in + 4));
        Imdct12X1Local((float*)(in + 8), (float*)(t + 8));
        Imdct12X1Local((float*)(in + 0xc), (float*)(t + 0xc));
        HELPER_OverlapAddX4(buf, tmp, hist);
        flag = 1;
    }
    if (gi->blockType == 2) {
        for (; flag < 8; flag++) {
            float* p = buf + flag * 0x48;       // 0x120 bytes of four interleaved lanes
            HELPER_Imdct12X4(p, tmp);
            HELPER_OverlapAddX4(p, tmp, hist + flag * 0x48);
        }
    } else {
        const float* tbl = (const float*)((const uint8_t*)g_imdct36WinHybrid + gi->blockType * 0x90);
        for (; flag < 8; flag++) {
            float* p = buf + flag * 0x48;
            HELPER_Imdct36X4Implementation(p, tmp, tbl);
            HELPER_OverlapAddX4(p, tmp, hist + flag * 0x48);
        }
    }
}
}}}  // namespace rw::audio::core

// @ 0x0116fdc0
namespace rw { namespace audio { namespace core {
void FUN_0116fdc0(const float* src, int16_t* dst)
{
    const __m128 scale = _mm_set1_ps(16384.0f);
    const float* s = src;
    int16_t* d = dst;
    for (int i = 0; i < 18; i++) {
        // The original unrolls the eight planes in four two-plane blocks (the pair shares the
        // multiply/conversion pipeline before the two streaming stores).
#define HYBRID_PAIR(g)                                                          \
        {                                                                       \
            const float* q = s + (g) * 0x48;                                    \
            __m128 x0 = _mm_loadl_pi(_mm_setzero_ps(), (const __m64*)(q + 0));  \
            __m128 x1 = _mm_loadl_pi(_mm_setzero_ps(), (const __m64*)(q + 2));  \
            __m128 y0 = _mm_loadl_pi(_mm_setzero_ps(), (const __m64*)(q + 0x48)); \
            __m128 y1 = _mm_loadl_pi(_mm_setzero_ps(), (const __m64*)(q + 0x4a)); \
            __m64 m0 = _mm_packs_pi32(_mm_cvtps_pi32(_mm_mul_ps(x0, scale)),    \
                                      _mm_cvtps_pi32(_mm_mul_ps(x1, scale)));   \
            __m64 m1 = _mm_packs_pi32(_mm_cvtps_pi32(_mm_mul_ps(y0, scale)),    \
                                      _mm_cvtps_pi32(_mm_mul_ps(y1, scale)));   \
            _mm_stream_pi((__m64*)(d + (g) * 4), m0);                           \
            _mm_stream_pi((__m64*)(d + (g) * 4 + 4), m1);                       \
        }
        HYBRID_PAIR(0);
        HYBRID_PAIR(2);
        HYBRID_PAIR(4);
        HYBRID_PAIR(6);
#undef HYBRID_PAIR
        s += 4;
        d += 32;
    }
    _mm_empty();
    // The original's loop counter is the *destination* end pointer and it is still in EAX at the
    // epilogue; a volatile keep-read reproduces that hidden void return value.
    int16_t* volatile done = d;
    (void)done;
}
}}}  // namespace rw::audio::core
