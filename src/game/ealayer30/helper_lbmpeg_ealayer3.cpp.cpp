// src/game/ealayer30/helper_lbmpeg_ealayer3.cpp.cpp -- migrated from slice(s) s0115a5b0, s01159630 by tools/migrate/rewrite.py
// Object file: ealayer30/helper_lbmpeg_ealayer3.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include "rw/audio/core/System.h"

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
    uint16_t part2_3_length;            // +0x00 (unused here)
    uint16_t big_values;                // +0x02
    uint16_t scalefac_compress;         // +0x04
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
class HELPER_CMpegBase {                // PDB size 0x48
public:
    void** vftable;                     // +0x00
    int    Real_mSampFreq;              // +0x04
    int    mSampFreq;                   // +0x08
    int    mBitRate;                    // +0x0c
    int    cFrameSize;                  // +0x10
    uint16_t mFrameSamples;             // +0x14
    uint8_t  mLayer;                    // +0x16
    uint8_t* mBufPtr;                   // +0x18
    uint8_t* mBufPtrBase;               // +0x1c
    uint8_t* mBufPtrNext;               // +0x20
    uint32_t mShiftReg;                 // +0x24
    int      mShiftRegBits;             // +0x28
    uint8_t  mBandOffset[2];            // +0x2c
    uint8_t  mMPEG25;                   // +0x2e
    uint8_t  mLSF;                      // +0x2f
    uint8_t  sfreq;                     // +0x30
    uint8_t  max_gr;                    // +0x31
    uint8_t  mVersion;                  // +0x32
    uint8_t  mErrorProt;                // +0x33
    uint8_t  mBitRateIdx;               // +0x34
    uint8_t  mSampFreqIdx;              // +0x35
    uint8_t  mPadding;                  // +0x36
    uint8_t  mMode;                     // +0x37
    uint8_t  mModeExt;                  // +0x38
    uint8_t  mCopyright;                // +0x39
    uint8_t  mOriginal;                 // +0x3a
    uint8_t  mOpened;                   // +0x3b
    uint8_t  mChannels;                 // +0x3c
    uint32_t mHeader;                   // +0x40
    void*    mpPolySynthHistory;        // +0x44

    uint16_t GetBits(int n);            // 0x011598a0 (thiscall, ret 4)
    void LoadBitRegister();             // 0x01159860
    ~HELPER_CMpegBase();                // 0x0116c390 (layer3 base dtor in retail)
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
    char pad48[0x24];                   // +0x48 (base ends at 0x48)
    SideInfo* mSideInfo;                // +0x6c
    GrInfo mGrInfo[2][2];               // +0x70
    ScaleFac mScaleFac[2];              // +0xd0
    void* mpPrevBlockX4;                // +0x1c8
    int   mFrameStart;                  // +0x1cc
    float* mpDecodedFrame;              // +0x1d0
    void GetScaleFactors(int ch, int gr);   // 0x01159cc0 (ret 8)
    bool GetSideInfo(int gr);           // 0x01159950 (ret 4, result in al)
    void Huffman_UnpackTableSet(int ch, unsigned gr, void* out);  // 0x0115a380
    ~HELPER_CEALayer3();                // 0x01159920
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern "C" void* memset(void*, int, unsigned);
}
}
}
namespace rw {
namespace audio {
namespace core {
struct SystemHeap {
    void Free(void* p, int flag);   // 0x0112c850
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern SystemHeap* g_pHeap;         // 0x016e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
extern void* g_vtbl_EALayer3;                // 0x014ce8a0
}
}
}
namespace rw {
namespace audio {
namespace core {
extern const uint8_t g_huffGroupLen[];
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
    uint16_t scaleFacCompress;          // +4
    uint8_t globalGain;                 // +6
    uint8_t windowSwitchingFlag;        // +7
    uint8_t blockType;                  // +8
    uint8_t mixedBlockFlag;             // +9
    uint8_t region0Count;               // +0xa
    uint8_t region1Count;               // +0xb
    uint8_t tableSelect[3];             // +0xc
    uint8_t count1TableSelect;          // +0xf
    uint8_t subBlockGain[3];            // +0x10
    uint8_t preFlag;                    // +0x13
    uint8_t scaleFacScale;              // +0x14
    uint8_t pad15[3];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Layer3Temp {                     // 0xc bytes
    uint32_t mGranule;                  // +0
    uint8_t  mScfsi[2][4];              // +4, +8
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0115_a5b0;
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CMpegBase_s0115_a5b0 {
public:
    void** vftable;                     // +0x00
    uint32_t mSampFreq;                 // +0x04
    uint32_t Real_mSampFreq;            // +0x08
    uint32_t pad0c;                     // +0x0c
    uint32_t cFrameSize;                // +0x10
    uint16_t mFrameSamples;             // +0x14
    uint8_t mLayer;                     // +0x16
    uint8_t pad17;                      // +0x17
    const uint8_t* mBufPtr;             // +0x18
    const uint8_t* mBufPtrBase;         // +0x1c
    const uint8_t* mBufSave;            // +0x20
    int mShiftReg;                      // +0x24
    int mShiftRegBits;                  // +0x28
    uint8_t mSynthState[2];             // +0x2c
    uint8_t mMPEG25;                    // +0x2e
    uint8_t mLSF;                       // +0x2f
    uint8_t sfreq;                      // +0x30
    uint8_t pad31;                      // +0x31
    uint8_t mVersion;                   // +0x32
    uint8_t pad33;                      // +0x33
    uint8_t pad34;                      // +0x34
    uint8_t mSampFreqIdx;               // +0x35
    uint8_t pad36;                      // +0x36
    uint8_t mMode;                      // +0x37
    uint8_t mModeExt;                   // +0x38
    uint8_t pad39;                      // +0x39
    uint8_t pad3a;                      // +0x3a
    uint8_t mOpened;                    // +0x3b
    uint8_t mChannels;                  // +0x3c
    uint8_t pad3d[3];                   // +0x3d..+0x3f
    uint32_t pad40;                     // +0x40
    void* mpSynthHistory;               // +0x44
    uint32_t pad48[9];                  // +0x48..+0x6b
    void* mpTemp;                       // +0x6c
    int GetBits(int n);                 // 0x011598a0 (thiscall, ret 4)
    void FUN_01170500();                // 0x01170500 (thiscall, ret 0)
    void FUN_01170510();                // 0x01170510 (thiscall, ret 0)
    int  FUN_01170230();                // 0x01170230 (thiscall, ret 0)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CMpegLayer3Base : public HELPER_CMpegBase_s0115_a5b0 {
public:
    ~HELPER_CMpegLayer3Base();          // 0x0116c390 (thiscall, ret 0)
    void SToPowerOf4over3(int n, short* in, float* out);   // 0x0116c1a0 (thiscall, ret 0xc)
    void Dequantize(int ch, int gr, float* out);           // 0x0116c3c0 (thiscall, ret 0xc)
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
    uint16_t mBandOffset[2][62];        // +0xd0 (stride 0x7c)
    uint32_t pad1c8[2];                 // +0x1c8
    float* mpDecodedFrame;              // +0x1d0

    void DecodeHuffman(int a, int b, float* out, int endBit);   // 0x0115a710 (ret 0x10)
    void UnpackTableSet(int channel, int granule);              // 0x0115a5b0 (ret 8)
    void Huffman_UnpackTableSet(int channel, int granule, uint8_t* out); // 0x0115a380 (ret 0xc)
    void GetSideInfo(int granule);                              // 0x01159950 (ret 4)
    void GetScaleFactors(int channel, int granule);             // 0x01159cc0 (ret 8)
    uint32_t ProcessHeader(uint32_t header);                    // 0x0115aeb0 (ret 4)
    int Open(const void* data, unsigned size);                  // 0x0115af60 (ret 8)
    int DecodeMono(float* out);                                 // 0x0115aff0 (ret 4)
    int DecodeStereo(float* out);                               // 0x0115b180 (ret 4)
    void Decode();                                              // 0x0115b3b0 (ret 0)
    void* Destroy(unsigned flags);                              // 0x0115b400 (ret 4)
    void FUN_0116dd70(int ch, int gr, float* in, float* out);   // 0x0116dd70 (ret 0x10)
    void FUN_0116e250(int ch, int gr, float* p);                // 0x0116e250 (ret 0xc)
    void FUN_0116fc20(int ch, int gr, float* p);                // 0x0116fc20 (ret 0xc)
    void FUN_01172e10(int ch, float* out, float* p);            // 0x01172e10 (ret 0xc)
    void FUN_01170fc0(int ch, float* out, float* p);            // 0x01170fc0 (ret 0xc)
    void III_stereo(int gr, float* p);                          // 0x0116c750 (ret 8)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0115_a5b0 {
public:
    void* Alloc(unsigned size, const char* name, unsigned align, unsigned flags); // 0x0112c820
    void  Free(void* p, unsigned flags);                                          // 0x0112c850
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0115_a5b0* g_pSystem;               // 0x016e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
extern int g_floatPath;                 // 0x016f1840
}
}
}
namespace rw {
namespace audio {
namespace core {
extern void* g_vtblEALayer3[];          // 0x014ce8a0
}
}
}
namespace rw {
namespace audio {
namespace core {
extern const uint16_t kSampleRates[];   // 0x014dab04
}
}
}
namespace rw {
namespace audio {
namespace core {
void __cdecl FUN_01165fa0(float* a, float* b);   // 0x01165fa0
}
}
}
namespace rw {
namespace audio {
namespace core {
void __cdecl NegateRows(float* p);               // 0x011675c0
}
}
}
namespace rw {
namespace audio {
namespace core {
void __cdecl FUN_0116ff30(float* a, float* b);   // 0x0116ff30
}
}
}
namespace rw {
namespace audio {
namespace core {
void __cdecl FUN_0116fdc0(float* a, float* b);   // 0x0116fdc0
}
}
}
namespace rw {
namespace audio {
namespace core {
void __cdecl GameDelete(void* p);                // 0x00f47380
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

// @ 0x01159860
namespace rw { namespace audio { namespace core {
void HELPER_CMpegBase::LoadBitRegister()
{
    int bits = mShiftRegBits;
    while (bits < 0x18) {
        unsigned int b = *mBufPtr;
        bits = mShiftRegBits + 8;
        mBufPtr = mBufPtr + 1;
        mShiftReg = mShiftReg | (b << (0x18u - (unsigned int)mShiftRegBits));
        mShiftRegBits = bits;
    }
}
}}}  // namespace rw::audio::core

// @ 0x011598a0
namespace rw { namespace audio { namespace core {
uint16_t HELPER_CMpegBase::GetBits(int n)
{
    int bits = mShiftRegBits;
    while (bits < n) {
        unsigned int b = *mBufPtr;
        bits = mShiftRegBits + 8;
        mBufPtr = mBufPtr + 1;
        mShiftReg = mShiftReg | (b << (0x18u - (unsigned int)mShiftRegBits));
        mShiftRegBits = bits;
    }
    uint32_t v = mShiftReg;
    mShiftRegBits = mShiftRegBits - n;
    uint32_t result = v >> (0x20u - (unsigned int)n);
    mShiftReg = v << (unsigned int)n;
    return (uint16_t)result;
}
}}}  // namespace rw::audio::core

// @ 0x01159920
namespace rw { namespace audio { namespace core {
HELPER_CEALayer3::~HELPER_CEALayer3()
{
    float* pf = mpDecodedFrame;
    vftable = &g_vtbl_EALayer3;
    if (pf != 0)
        g_pHeap->Free(pf, 0);
    // epilogue: the compiler tail-jumps into ~HELPER_CMpegBase (0x0116c390)
}
}}}  // namespace rw::audio::core

// @ 0x01159950
namespace rw { namespace audio { namespace core {
bool HELPER_CEALayer3::GetSideInfo(int gr)
{
    if (mLSF == 0) {
        if (gr == 1) {
            LoadBitRegister();
            for (int ch = 0; ch < mChannels; ch++) {
                uint8_t* scfsi = mSideInfo->scfsi[ch];
                scfsi[0] = (uint8_t)(mShiftReg >> 0x1f);
                scfsi[1] = (uint8_t)((mShiftReg >> 0x1e) & 1);
                scfsi[2] = (uint8_t)((mShiftReg >> 0x1d) & 1);
                scfsi[3] = (uint8_t)((mShiftReg >> 0x1c) & 1);
                mShiftReg <<= 4;
                mShiftRegBits -= 4;
            }
        }
        int ch = 0;
        if (mChannels == 0)
            return true;
        GrInfo* gi = &mGrInfo[0][gr];
        do {
            gi->part2_3_length = (uint16_t)GetBits(0xc);
            LoadBitRegister();
            gi->big_values = (uint16_t)(mShiftReg >> 0x17);
            gi->global_gain = (uint8_t)(mShiftReg >> 0xf);
            gi->scalefac_compress = (uint16_t)((mShiftReg >> 0xb) & 0xf);
            gi->window_switching_flag = (uint8_t)((mShiftReg >> 10) & 1);
            mShiftReg <<= 0x16;
            mShiftRegBits -= 0x16;
            LoadBitRegister();
            if (gi->window_switching_flag == 0) {
                gi->table_select[0] = (uint8_t)(mShiftReg >> 0x1b);
                gi->table_select[1] = (uint8_t)((mShiftReg >> 0x16) & 0x1f);
                gi->table_select[2] = (uint8_t)((mShiftReg >> 0x11) & 0x1f);
                gi->region0_count = (uint8_t)((mShiftReg >> 0xd) & 0xf);
                gi->region1_count = (uint8_t)((mShiftReg >> 10) & 7);
                gi->block_type = 0;
            } else {
                gi->block_type = (uint8_t)(mShiftReg >> 0x1e);
                gi->mixed_block_flag = (uint8_t)((mShiftReg >> 0x1d) & 1);
                gi->table_select[0] = (uint8_t)((mShiftReg >> 0x18) & 0x1f);
                gi->table_select[1] = (uint8_t)((mShiftReg >> 0x13) & 0x1f);
                gi->sub_block_gain[0] = (uint8_t)((mShiftReg >> 0x10) & 7);
                gi->sub_block_gain[1] = (uint8_t)((mShiftReg >> 0xd) & 7);
                gi->sub_block_gain[2] = (uint8_t)((mShiftReg >> 10) & 7);
                if (gi->block_type == 0)
                    return false;
                if (gi->block_type == 2 && gi->mixed_block_flag == 0) {
                    gi->region0_count = 8;
                    gi->region1_count = (uint8_t)(0x14 - gi->region0_count);
                } else {
                    gi->region0_count = 7;
                    gi->region1_count = (uint8_t)(0x14 - gi->region0_count);
                }
            }
            gi->pre_flag = (uint8_t)((mShiftReg >> 9) & 1);
            gi->scale_fac_scale = (mShiftReg >> 8) & 1;
            gi->count1_table_select = (uint8_t)((mShiftReg >> 7) & 1);
            mShiftReg <<= 0x19;
            mShiftRegBits -= 0x19;
            ch++;
            gi += 2;                 // channel stride is 0x30 (mGrInfo[ch][gr])
        } while (ch < mChannels);
        return true;
    } else {
        int ch = 0;
        if (mChannels == 0)
            return true;
        GrInfo* gi = &mGrInfo[0][0];       // LSF side info has a single granule
        do {
            gi->part2_3_length = (uint16_t)GetBits(0xc);
            gi->big_values = (uint16_t)GetBits(9);
            gi->global_gain = (uint8_t)GetBits(8);
            gi->scalefac_compress = (uint16_t)GetBits(9);
            gi->window_switching_flag = (uint8_t)GetBits(1);
            if (gi->window_switching_flag != 0) {
                gi->block_type = (uint8_t)GetBits(2);
                gi->mixed_block_flag = (uint8_t)GetBits(1);
                gi->table_select[0] = (uint8_t)GetBits(5);
                gi->table_select[1] = (uint8_t)GetBits(5);
                gi->sub_block_gain[0] = (uint8_t)GetBits(3);
                gi->sub_block_gain[1] = (uint8_t)GetBits(3);
                gi->sub_block_gain[2] = (uint8_t)GetBits(3);
                if (gi->block_type == 0)
                    return false;
                if (gi->block_type == 2 && gi->mixed_block_flag == 0)
                    gi->region0_count = 8;
                else {
                    gi->region0_count = 7;
                    gi->region1_count = 13;
                }
            } else {
                gi->table_select[0] = (uint8_t)GetBits(5);
                gi->table_select[1] = (uint8_t)GetBits(5);
                gi->table_select[2] = (uint8_t)GetBits(5);
                gi->region0_count = (uint8_t)GetBits(4);
                gi->region1_count = (uint8_t)GetBits(3);
                gi->block_type = 0;
            }
            gi->scale_fac_scale = (uint32_t)GetBits(1);
            gi->count1_table_select = (uint8_t)GetBits(1);
            ch++;
            gi += 2;                 // channel stride is 0x30 (mGrInfo[ch][gr])
        } while (ch < mChannels);
        return true;
    }
}
}}}  // namespace rw::audio::core

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

// @ 0x0115a380
namespace rw { namespace audio { namespace core {
void HELPER_CEALayer3::Huffman_UnpackTableSet(int ch, unsigned gr, void* out)
{
    unsigned int widths[4];              // bit width of each of the four sections
    uint8_t modeExt = mModeExt;

    widths[0] = 0;
    widths[1] = 0;
    widths[2] = 0;
    widths[3] = 0;

    GrInfo* g = &mGrInfo[ch][gr];
    unsigned int band = g->scalefac_compress;   // sfb band index for this granule

    int groupSet;
    int layout = 0;

    if (g->block_type == 2) {
        if (g->mixed_block_flag == 0)
            groupSet = 1;
        else
            groupSet = ((g->mixed_block_flag != 1) - 1) & 2;
    } else {
        groupSet = 0;
    }

    // long-block / non-"mixed" granules: derive widths from the band index
    if ((modeExt != 1 && modeExt != 3) || ch != 1) {
        if (band < 400) {
            widths[0] = (band >> 4) / 5;
            widths[1] = (band >> 4) % 5;
            g->pre_flag = 0;
            widths[2] = (band >> 2) & 3;
            widths[3] = band & 3;
            layout = 0;
        } else if (band < 500) {
            widths[1] = (band - 400) >> 2;
            widths[0] = widths[1] / 5;
            widths[1] = widths[1] % 5;
            g->pre_flag = 0;
            layout = 1;
            widths[2] = band & 3;
            widths[3] = 0;
        } else if (band <= 0x1ff) {
            widths[0] = (band - 500) / 3;
            widths[1] = (band - 500) % 3;
            widths[2] = 0;
            g->pre_flag = 1;
            layout = 2;
            widths[3] = 0;
        }
    }

    // joint-stereo second channel of the second granule uses the alt scale
    if ((modeExt == 1 || modeExt == 3) && ch == 1) {
        unsigned int b = band >> 1;
        if (b < 0xb4) {
            widths[0] = b / 0x24;
            widths[1] = (b % 0x24) / 6;
            widths[2] = (b % 0x24) % 6;
            layout = 3;
            widths[3] = 0;
            g->pre_flag = 0;
        } else if (b < 0xf4) {
            widths[0] = ((b + 0xc) >> 4) & 3;
            widths[1] = ((b - 4) >> 2) & 3;
            widths[2] = b & 3;
            layout = 4;
            widths[3] = 0;
            g->pre_flag = 0;
        } else if (b <= 0xfe) {
            widths[0] = (b - 0xf4) / 3;
            widths[1] = (b - 0xf4) % 3;
            widths[2] = 0;
            layout = 5;
            widths[3] = 0;
            g->pre_flag = 0;
        }
    }

    memset(out, 0, 0x2d);

    const uint8_t* glen = g_huffGroupLen + (groupSet + layout * 3) * 4;
    int pos = 0;
    for (unsigned int s = 0; s < 4; s++) {
        uint8_t n = glen[s];
        for (unsigned int k = 0; k < n; k++) {
            uint8_t v = 0;
            if (widths[s] != 0)
                v = (uint8_t)GetBits((int)widths[s]);
            ((uint8_t*)out)[pos] = v;
            pos++;
        }
    }
}
}}}  // namespace rw::audio::core

// @ 0x0115a5b0
namespace rw { namespace audio { namespace core {
void HELPER_CEALayer3_s0115_a5b0::UnpackTableSet(int channel, int granule)
{
    GranuleInfo* g = &mGranuleInfo[channel][granule];
    uint16_t* sfb = mBandOffset[channel];
    uint8_t local[0x38];

    Huffman_UnpackTableSet(channel, granule, local);
    if (g->windowSwitchingFlag && g->blockType == 2) {
        if (g->mixedBlockFlag) {
            for (int i = 0; i < 8; i++)
                sfb[i] = local[i];
            const uint8_t* p = local + 8;
            for (int i = 0; i < 9; i++) {
                sfb[0x1a + i] = p[0];
                sfb[0x27 + i] = p[1];
                sfb[0x34 + i] = p[2];
                p += 3;
            }
            sfb[0x23] = 0;
            sfb[0x30] = 0;
            sfb[0x3d] = 0;
            return;
        }
        const uint8_t* p = local;
        for (int i = 0; i < 12; i++) {
            sfb[0x17 + i] = p[0];
            sfb[0x24 + i] = p[1];
            sfb[0x31 + i] = p[2];
            p += 3;
        }
        sfb[0x23] = 0;
        sfb[0x30] = 0;
        sfb[0x3d] = 0;
        return;
    }
    for (int i = 0; i < 0x15; i++)
        sfb[i] = local[i];
    sfb[0x15] = 0;
    sfb[0x16] = 0;
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

// @ 0x0115aeb0
namespace rw { namespace audio { namespace core {
uint32_t HELPER_CEALayer3_s0115_a5b0::ProcessHeader(uint32_t header)
{
    uint32_t version = (header >> 6) & 3;
    uint32_t sfreqIndex = (header >> 4) & 3;
    uint32_t mode = (header >> 2) & 3;

    mModeExt = (uint8_t)(header & 3);
    mVersion = (uint8_t)(version & 1);
    mLSF = (version != 3);
    mMPEG25 = (version == 0);
    mMode = (uint8_t)mode;
    mLayer = 3;
    if (mMPEG25) {
        mSampFreqIdx = (uint8_t)(sfreqIndex + 6);
    } else {
        mSampFreqIdx = (uint8_t)(mLSF * 3 + sfreqIndex);
        sfreq = (uint8_t)(((mLSF - 1) & 3) + sfreqIndex);
    }
    mChannels = (uint8_t)((mode != 3) + 1);
    uint32_t rate = kSampleRates[mSampFreqIdx];
    Real_mSampFreq = rate;
    mSampFreq = rate;
    return 0;
}
}}}  // namespace rw::audio::core

// @ 0x0115af60
namespace rw { namespace audio { namespace core {
int HELPER_CEALayer3_s0115_a5b0::Open(const void* data, unsigned size)
{
    if (mOpened)
        FUN_01170510();
    void** vt = vftable;
    typedef int (__thiscall* OpenFn)(void*, unsigned);
    OpenFn fn = (OpenFn)vt[1];
    mOpened = 1;
    mBufPtr = (const uint8_t*)data;
    mBufPtrBase = (const uint8_t*)data;
    int r = fn(this, *(const uint8_t*)data);
    if (r == -1)
        return -1;
    r = FUN_01170230();
    if (r < 0)
        return -1;
    if (mpDecodedFrame == 0) {
        mFrameSamples = 0x240;
        unsigned bytes = (unsigned)mChannels * 0x900;
        mpDecodedFrame = (float*)g_pSystem->Alloc(bytes, "EaLayer3DecodedFrame", 0x10, 0);
        if (mpDecodedFrame == 0)
            return -1;
    }
    mSynthState[0] = 1;
    mSynthState[1] = 1;
    FUN_01170500();
    return 0;
}
}}}  // namespace rw::audio::core

// @ 0x0115aff0
namespace rw { namespace audio { namespace core {
int HELPER_CEALayer3_s0115_a5b0::DecodeMono(float* out)
{
    Layer3Temp temp;
    __declspec(align(16)) float bufA[576];
    __declspec(align(16)) float bufB[576];

    mpTemp = &temp;
    int granule = GetBits(1);
    GetSideInfo(granule);
    int endBit = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
    if (mVersion == 1)
        GetScaleFactors(0, granule);
    else
        UnpackTableSet(0, granule);
    DecodeHuffman(0, granule, bufA, endBit);
    Dequantize(0, granule, bufA);
    float* p = bufA;
    float* q = bufB;
    if (mGranuleInfo[0][granule].windowSwitchingFlag &&
        mGranuleInfo[0][granule].blockType == 2) {
        FUN_0116dd70(0, granule, bufA, bufB);
        p = bufB;
        q = bufA;
    }
    FUN_0116e250(0, granule, p);
    FUN_01165fa0(p, q);
    FUN_0116fc20(0, granule, q);
    NegateRows(q);
    if (g_floatPath == 0) {
        FUN_0116ff30(q, p);
        for (int i = 0; i < 0x12; i++) {
            FUN_01172e10(0, out, p);
            out += 0x20;
            p += 0x20;
        }
    } else {
        FUN_0116fdc0(q, p);
        for (int i = 0; i < 0x12; i++) {
            FUN_01170fc0(0, out, p);
            out += 0x20;
            p += 0x10;
        }
    }
    unsigned pad = (unsigned)(-mShiftRegBits) & 7;
    if (pad)
        GetBits(8 - pad);
    cFrameSize = (unsigned)((int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits) >> 3;
    return 0;
}
}}}  // namespace rw::audio::core

// @ 0x0115b180
namespace rw { namespace audio { namespace core {
int HELPER_CEALayer3_s0115_a5b0::DecodeStereo(float* out)
{
    Layer3Temp temp;
    __declspec(align(16)) float buf0[576];
    __declspec(align(16)) float buf1[576];
    __declspec(align(16)) float buf2[576];
    float* bufs[3] = { buf0, buf1, buf2 };

    mpTemp = &temp;
    int granule = GetBits(1);
    GetSideInfo(granule);
    for (unsigned ch = 0; ch < mChannels; ch++) {
        int endBit = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
        if (mVersion == 1)
            GetScaleFactors(ch, granule);
        else
            UnpackTableSet(ch, granule);
        DecodeHuffman(ch, granule, bufs[ch], endBit);
        Dequantize(ch, granule, bufs[ch]);
    }
    III_stereo(granule, buf0);
    for (unsigned ch = 0; ch < mChannels; ch++) {
        const GranuleInfo* g = &mGranuleInfo[ch][granule];
        if (!g->windowSwitchingFlag || g->blockType != 2) {
            float* t = bufs[ch];
            bufs[ch] = bufs[2];
            bufs[2] = t;
        } else {
            FUN_0116dd70(ch, granule, bufs[ch], bufs[2]);
        }
        FUN_0116e250(ch, granule, bufs[2]);
        FUN_01165fa0(bufs[2], bufs[ch]);
        FUN_0116fc20(ch, granule, bufs[ch]);
        NegateRows(bufs[ch]);
        if (g_floatPath == 0) {
            FUN_0116ff30(bufs[ch], bufs[2]);
            float* t = bufs[2];
            for (int i = 0; i < 0x12; i++) {
                FUN_01172e10(ch, out, t);
                t += 0x20;
                out += 0x20;
            }
        } else {
            FUN_0116fdc0(bufs[ch], bufs[2]);
            float* t = bufs[2];
            for (int i = 0; i < 0x12; i++) {
                FUN_01170fc0(ch, out, t);
                t += 0x10;
                out += 0x20;
            }
        }
    }
    unsigned pad = (unsigned)(-mShiftRegBits) & 7;
    if (pad)
        GetBits(8 - pad);
    cFrameSize = (unsigned)((int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits) >> 3;
    return 0;
}
}}}  // namespace rw::audio::core

// @ 0x0115b3b0
namespace rw { namespace audio { namespace core {
void HELPER_CEALayer3_s0115_a5b0::Decode()
{
    void** vt = vftable;
    mBufPtrBase = mBufPtr;
    typedef void (__thiscall* HeaderFn)(void*, int);
    ((HeaderFn)vt[1])(this, GetBits(8));
    if (mChannels == 1)
        DecodeMono(mpDecodedFrame);
    else
        DecodeStereo(mpDecodedFrame);
}
}}}  // namespace rw::audio::core

// @ 0x0115b400
namespace rw { namespace audio { namespace core {
void* HELPER_CEALayer3_s0115_a5b0::Destroy(unsigned flags)
{
    float* p = mpDecodedFrame;
    vftable = g_vtblEALayer3;
    if (p != 0)
        g_pSystem->Free(p, 0);
    this->HELPER_CMpegLayer3Base::~HELPER_CMpegLayer3Base();
    if (flags & 1)
        GameDelete(this);
    return this;
}
}}}  // namespace rw::audio::core
