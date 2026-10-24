// Slice s01159630: rw::audio::core::HELPER_CEALayer3 scalefactor reader (ISO 11172-3 "III_get_scale_factors").
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

namespace rw { namespace audio { namespace core {

// slen1 / slen2 for each scalefac_compress value (ISO slen[2][16] tables)
extern const signed char kSlen1[16];    // 0x014d9fd4
extern const signed char kSlen2[16];    // 0x014d9fe4

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

struct SideInfo {
    uint32_t pad00;
    uint8_t scfsi[2][4];                // +0x04
};

struct ScaleFac {                       // 0x7c bytes, one per channel
    uint16_t l[23];                     // +0x00
    uint16_t s[3][13];                  // +0x2e
};

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

inline uint16_t GetBitsZ(HELPER_CMpegBase* b, int n) { return n == 0 ? 0 : b->GetBits(n); }

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

// ==================================================================
// gold7 batch "s01159630": the rest of the MPEG-1 Layer III helper cluster
//
//   01159630  decoder-state Init (cdecl, object pointer first)
//   011596d0  ordered intrusive-list insert by ushort key
//   01159710  ordered intrusive-list unlink
//   01159760  reader-table init #1
//   011597d0  reader-table init #2
//   01159810  reader-table init #3
//   01159850  install the global DoInsertValue (0x015c3848)
//   01159860  HELPER_CMpegBase::LoadBitRegister
//   011598a0  HELPER_CMpegBase::GetBits
//   01159920  HELPER_CEALayer3::~HELPER_CEALayer3
//   01159950  HELPER_CEALayer3::GetSideInfo
//   0115a380  HELPER_CEALayer3::Huffman_UnpackTableSet
// ==================================================================

// ---- ordered intrusive list node: +0x08 child (next in key order),
//      +0x10 parent/prev, +0x18 unsigned short key.
struct MpegListNode {
    char          pad00[8];
    MpegListNode* child;        // +0x08
    char          pad0c[4];
    MpegListNode* parent;       // +0x10
    char          pad14[4];
    uint16_t      key;          // +0x18
    char          pad1a[2];
};

// ---- decoder-state view used by the Init function (0x01159630) ------------
// The stores reach +0x1830, past HELPER_CEALayer3 (0x1d4), so the retail type
// is a larger decoder object; slots are named for the role Init gives them.
struct MpegDecoderState {
    void**   vftable;          // +0x0000
    void**   vftableAlt;       // +0x0004
    char     pad08[0x14];
    uint8_t* mBufPtrBase;      // +0x001c
    uint8_t* mBufPtrNext;      // +0x0020
    float    mGain;            // +0x0024  (1.0f)
    float    mZero28;          // +0x0028  (0.0f)
    uint32_t mBandOffset;      // +0x002c  (header byte * 2)
    uint32_t mSampleTag30;     // +0x0030  (result of FUN_011684c0)
    uint32_t mReserved34;      // +0x0034
    uint32_t mReserved38;      // +0x0038
    uint32_t mReserved3c;      // +0x003c
    char     pad40[0x1828 - 0x40];
    uint32_t mReserved1828;    // +0x1828
    uint32_t mReserved182c;    // +0x182c
    uint32_t mSyncWord;        // +0x1830
};

// ---- externs --------------------------------------------------------------

extern "C" void* memset(void*, int, unsigned);

// System allocator: Free is a this-call member of the heap object.
struct SystemHeap {
    void Free(void* p, int flag);   // 0x0112c850
};
extern SystemHeap* g_pHeap;         // 0x016e61a8

int        FUN_01140a00(int v);              // 0x01140a00
void*      FindStream(int idx);              // 0x01158b90
uint32_t   FUN_011684c0(void* p, int n);     // 0x011684c0

// vtable slots installed by Init
extern void* g_vtbl_CMpegBase_slot0;         // 0x01159500
extern void* g_vtbl_CMpegBase_slot1;         // 0x011595f0
extern void* g_vtbl_EALayer3;                // 0x014ce8a0

// reader-table init entry points (their addresses are stored as immediates)
typedef void (*ReaderInitFn)(void);
extern "C" void Reader_Init_116b7c0();       // 0x0116b7c0
extern "C" void Reader_Init_116b6c0();       // 0x0116b6c0
extern "C" void Reader_Init_116b920();       // 0x0116b920
extern "C" void Reader_Init_116bed0();       // 0x0116bed0
extern "C" void Reader_Init_116bdb0();       // 0x0116bdb0
extern "C" void Reader_Init_116bb20();       // 0x0116bb20
extern "C" void Reader_Init_116c0c0();       // 0x0116c0c0
extern "C" void Reader_Init_116c010();       // 0x0116c010
extern "C" void Reader_Init_116c170();       // 0x0116c170

// Huffman table-set group lengths (0x014d9ff8)
extern const uint8_t g_huffGroupLen[];

// ------------------------------------------------------------------ @ 0x01159630

// @ 0x01159630
// Initialise the decoder state: install the vtable slots, resolve the stream
// from the source index (or mark it stream-less), then seed the fixed fields.
// The object pointer is the first stack argument (plain cdecl).
void* MpegBase_Init(MpegDecoderState* st, int srcData, int srcIdx)
{
    st->vftable    = &g_vtbl_CMpegBase_slot0;
    st->vftableAlt = &g_vtbl_CMpegBase_slot1;

    if (srcIdx >= 0)
        st->mBufPtrNext = (uint8_t*)FindStream(FUN_01140a00(srcIdx));
    else
        st->mBufPtrNext = (uint8_t*)-1;

    st->mBufPtrBase   = (uint8_t*)(srcData + 6);
    st->mGain         = 1.0f;
    st->mZero28       = 0.0f;
    st->mBandOffset   = (uint32_t)((uint8_t)((uint8_t*)srcData)[1] * 2);
    uint32_t tag      = FUN_011684c0((void*)(srcData + 2), 4);
    st->mReserved34   = 0;
    st->mReserved38   = 0;
    st->mReserved3c   = 0;
    st->mReserved1828 = 0;
    st->mReserved182c = 0;
    st->mSampleTag30  = tag;
    st->mSyncWord     = 0x10bc;
    return 0;
}

// ------------------------------------------------------------------ @ 0x011596d0

// @ 0x011596d0
// Ordered insert: nodes stay sorted by their unsigned short key at +0x18; the
// walk stops at the first node whose key is not less than the new key.
void MpegList_Insert(void** head, MpegListNode* node)
{
    MpegListNode* cur = (MpegListNode*)*head;
    MpegListNode* prev = 0;
    while (cur != 0 && cur->key < node->key) {
        prev = cur;
        cur = cur->child;
    }
    node->child = cur;
    if (cur != 0)
        cur->parent = node;
    if (prev == 0)
        *head = node;
    else {
        prev->child = node;
        node->parent = prev;
    }
}

// ------------------------------------------------------------------ @ 0x01159710

// @ 0x01159710
void MpegList_Unlink(void** head, MpegListNode* node)
{
    MpegListNode* cur = (MpegListNode*)*head;
    if (node == cur) {
        *head = cur->child;
        return;
    }
    while (cur->child != 0 && cur->child != node)
        cur = cur->child;
    if (cur->child != 0 && cur->child == node) {
        if (cur->child->child != 0)
            cur->child->child->parent = cur;
        cur->child = cur->child->child;
    }
}

// ------------------------------------------------------------------ @ 0x01159760

// @ 0x01159760
void ReaderTable_Init1()
{
    *(ReaderInitFn*)0x016e80a0 = &Reader_Init_116b7c0;
    *(unsigned*)0x016e80e8      = 0x2c;
    *(ReaderInitFn*)0x016e80a8 = &Reader_Init_116b6c0;
    *(unsigned*)0x016e80f0      = 0x3c;
    *(ReaderInitFn*)0x016e80a4 = &Reader_Init_116b920;
    *(unsigned*)0x016e80ec      = 0x30;
    *(ReaderInitFn*)0x016e80ac = &Reader_Init_116b7c0;
    *(unsigned*)0x016e80f4      = 0x2c;
    *(ReaderInitFn*)0x016e80b4 = &Reader_Init_116b6c0;
    *(unsigned*)0x016e80fc      = 0x3c;
    *(ReaderInitFn*)0x016e80b0 = &Reader_Init_116b920;
    *(unsigned*)0x016e80f8      = 0x30;
}

// ------------------------------------------------------------------ @ 0x011597d0

// @ 0x011597d0
void ReaderTable_Init2()
{
    *(ReaderInitFn*)0x016e8094 = &Reader_Init_116bed0;
    *(unsigned*)0x016e80dc      = 0x2c;
    *(unsigned*)0x016e80e0      = 0x54;
    *(ReaderInitFn*)0x016e8098 = &Reader_Init_116bdb0;
    *(ReaderInitFn*)0x016e809c = &Reader_Init_116bb20;
    *(unsigned*)0x016e80e4      = 0x3c;
}

// ------------------------------------------------------------------ @ 0x01159810

// @ 0x01159810
void ReaderTable_Init3()
{
    *(ReaderInitFn*)0x016e8088 = &Reader_Init_116c170;
    *(unsigned*)0x016e80d0      = 0x28;
    *(ReaderInitFn*)0x016e808c = &Reader_Init_116c0c0;
    *(unsigned*)0x016e80d4      = 0x2c;
    *(ReaderInitFn*)0x016e8090 = &Reader_Init_116c010;
    *(unsigned*)0x016e80d8      = 0x34;
}

// ------------------------------------------------------------------ @ 0x01159850

// @ 0x01159850
int InstallDoInsertValue(void* fn)
{
    *(void**)0x015c3848 = fn;
    return 0;
}

// ------------------------------------------------------------------ @ 0x01159860

// @ 0x01159860
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

// ------------------------------------------------------------------ @ 0x011598a0

// @ 0x011598a0
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

// ------------------------------------------------------------------ @ 0x01159920

// @ 0x01159920
HELPER_CEALayer3::~HELPER_CEALayer3()
{
    float* pf = mpDecodedFrame;
    vftable = &g_vtbl_EALayer3;
    if (pf != 0)
        g_pHeap->Free(pf, 0);
    // epilogue: the compiler tail-jumps into ~HELPER_CMpegBase (0x0116c390)
}

// ------------------------------------------------------------------ @ 0x01159950

// @ 0x01159950
// Reads the Layer III side info for granule gr: scfsi bits for the second
// granule, then part2_3_length and the per-channel granule fields.
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

// ------------------------------------------------------------------ @ 0x0115a380

// @ 0x0115a380
// Huffman table-set bit unpacker. Picks a group layout from the granule's sfb
// band index (mode/sample-rate dependent), derives the four per-section bit
// widths, zero-fills the 0x2d-byte output, then reads the sections.
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
