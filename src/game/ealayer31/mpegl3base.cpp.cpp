// addresses retail relocates here, named so the build relocates them too
extern "C" char g_14cbd80[];
extern "C" char g_14cc180[];
extern "C" char g_14ce514[];                // CMpegBase's vtable (one virtual-dtor slot)

#include "game/types.h"
#define _WIN32_WCE 1
#include <intrin.h>
#include "rw/audio/core/System.h"

// vftable and the two float tables this layer-3 decoder points at (absolute addresses
// in the shipped image).
#define MPEGBASE_VFTABLE     ((void*)g_14ce514)
#define MPEGL3BASE_VFTABLE   ((void*)g_14cc180)
#define MPEGL3BASE_TWO_TO_NEG_QUARTER  ((float*)g_14cbd80)
#define MPEGL3BASE_TWO_TO_NEG_QUARTER_SIZE  0x400

namespace rw {
namespace audio {
namespace core {

struct HuffTable {                              // size 8
    uint16_t tableSize;                         // +0x0
    uint16_t pad02;
    int16_t* pEntries;                          // +0x4
};

extern System* g_audioSystem;                   // 0x016e61a8
void operator_delete__(void* p);                // 0x00f47380
void* AudioMemset(void* dst, int c, unsigned n); // 0x011e073e (memset import thunk)

class CMpegBase {                               // size 0x50
public:
    void* vftable;                              // +0x00 (the class vtable; retail stores it here)
    int Real_mSampFreq;                         // +0x04
    int mSampFreq;                              // +0x08
    int mBitRate;                               // +0x0c
    int cFrameSize;                             // +0x10
    unsigned short mFrameSamples;               // +0x14
    unsigned char mLayer;                       // +0x16
    unsigned char mOpened;                      // +0x17
    unsigned char mChannels;                    // +0x18
    char pad19[3];                              // +0x19
    unsigned int mHeader;                       // +0x1c
    unsigned char* mBufPtr;                     // +0x20
    unsigned char* mBufPtrBase;                 // +0x24
    unsigned char* mBufPtrNext;                 // +0x28
    unsigned int mShiftReg;                     // +0x2c
    int mShiftRegBits;                          // +0x30
    int mResetSynthRequired;                    // +0x34
    unsigned char mBandOffset[2];               // +0x38
    unsigned char mMPEG25;                      // +0x3a
    unsigned char mLSF;                         // +0x3b
    unsigned char sfreq;                        // +0x3c
    unsigned char max_gr;                       // +0x3d
    unsigned char mVersion;                     // +0x3e
    unsigned char mErrorProt;                   // +0x3f
    unsigned char mBitRateIdx;                  // +0x40
    unsigned char mSampFreqIdx;                 // +0x41
    unsigned char mPadding;                     // +0x42
    unsigned char mMode;                        // +0x43
    unsigned char mModeExt;                     // +0x44
    unsigned char mCopyright;                   // +0x45
    unsigned char mOriginal;                    // +0x46
    char pad47;                                 // +0x47
    void* mpPolySynthHistory;                   // +0x48
    void* mpLoadedPolySynthHistory;             // +0x4c

    CMpegBase();                                // 0x01148cd0
    ~CMpegBase();                               // 0x01148d40
};

class CMpegLayer3Base_s0114_6ca0 : public CMpegBase {      // size 0x2dc
public:
    HuffTable mHuffTables[32];                  // +0x50
    uint8_t   pad150[4];
    uint8_t   pad154[0x2ac - 0x154];
    float*    mpTwoToNegativeQuarterPower;      // +0x2ac
    float*    mpLoadedTwoToNegativeQuarterPower;// +0x2b0
    int16_t*  mpLoadedTableSelect[3];           // +0x2b4
    float*    mpPrevBlockX4;                    // +0x2c0
    uint8_t   pad2c4[0x2d8 - 0x2c4];
    uint16_t  mTwoToNegativeQuarterPowerTableSize; // +0x2d8

    CMpegLayer3Base_s0114_6ca0();                          // 0x01146ca0
    ~CMpegLayer3Base_s0114_6ca0();                         // 0x01146cf0
    int  AllocateHybrid(int n);                 // 0x01146d20
    void* ScalarDeletingDtor(unsigned int flags);// 0x01146d70
    void InitHuffTables();                      // 0x01146a90
};

}  // namespace core
}  // namespace audio
}  // namespace rw

// @ 0x01146a90
namespace rw { namespace audio { namespace core {
// Point mHuffTables[0..31] at the static Huffman decode tables in the image.
void CMpegLayer3Base_s0114_6ca0::InitHuffTables()
{
    mHuffTables[0].tableSize = 0;        mHuffTables[0].pEntries = 0;
    mHuffTables[1].tableSize = 0x200;    mHuffTables[1].pEntries = (int16_t*)0x15c0100;
    mHuffTables[2].tableSize = 0x200;    mHuffTables[2].pEntries = (int16_t*)0x15c0300;
    mHuffTables[3].tableSize = 0x200;    mHuffTables[3].pEntries = (int16_t*)0x15c0500;
    mHuffTables[4].tableSize = 0;        mHuffTables[4].pEntries = 0;
    mHuffTables[5].tableSize = 0x200;    mHuffTables[5].pEntries = (int16_t*)0x15c0700;
    mHuffTables[6].tableSize = 0x200;    mHuffTables[6].pEntries = (int16_t*)0x15c0900;
    mHuffTables[7].tableSize = 0x226;    mHuffTables[7].pEntries = (int16_t*)0x15c0b00;
    mHuffTables[8].tableSize = 0x22a;    mHuffTables[8].pEntries = (int16_t*)0x15c0d80;
    mHuffTables[9].tableSize = 0x20c;    mHuffTables[9].pEntries = (int16_t*)0x15c1000;
    mHuffTables[10].tableSize = 0x28a;   mHuffTables[10].pEntries = (int16_t*)0x15c1280;
    mHuffTables[11].tableSize = 0x256;   mHuffTables[11].pEntries = (int16_t*)0x15c1580;
    mHuffTables[12].tableSize = 0x22e;   mHuffTables[12].pEntries = (int16_t*)0x15c1800;
    mHuffTables[13].tableSize = 0x570;   mHuffTables[13].pEntries = (int16_t*)0x15c1a80;
    mHuffTables[14].tableSize = 0;       mHuffTables[14].pEntries = 0;
    mHuffTables[15].tableSize = 0x4d6;   mHuffTables[15].pEntries = (int16_t*)0x15c2000;
    for (int i = 16; i < 24; i++) {
        mHuffTables[i].tableSize = 0x56a;
        mHuffTables[i].pEntries = (int16_t*)0x15c2500;
    }
    for (int i = 24; i < 32; i++) {
        mHuffTables[i].tableSize = 0x46c;
        mHuffTables[i].pEntries = (int16_t*)0x15c2a80;
    }
}
}}}  // namespace rw::audio::core

// @ 0x01146ca0
namespace rw { namespace audio { namespace core {
CMpegLayer3Base_s0114_6ca0::CMpegLayer3Base_s0114_6ca0()
: CMpegBase()
{
    vftable = MPEGL3BASE_VFTABLE;
    mpTwoToNegativeQuarterPower = MPEGL3BASE_TWO_TO_NEG_QUARTER;
    mTwoToNegativeQuarterPowerTableSize = MPEGL3BASE_TWO_TO_NEG_QUARTER_SIZE;
    mpLoadedTwoToNegativeQuarterPower = 0;
    InitHuffTables();
    for (int i = 0; i < 3; i++)
        mpLoadedTableSelect[i] = 0;
}
}}}  // namespace rw::audio::core

// @ 0x01146cf0
namespace rw { namespace audio { namespace core {
CMpegLayer3Base_s0114_6ca0::~CMpegLayer3Base_s0114_6ca0()
{
    float* old = *(float* volatile*)&mpPrevBlockX4;
    *(void* volatile*)&vftable = MPEGL3BASE_VFTABLE;
    _ReadWriteBarrier();
    if (old)
        g_audioSystem->Free(old, 0);
}
}}}  // namespace rw::audio::core

// @ 0x01146d20
namespace rw { namespace audio { namespace core {
// Allocate the hybrid history block (n * 0x900 bytes) and zero it.
int CMpegLayer3Base_s0114_6ca0::AllocateHybrid(int n)
{
    void* p = g_audioSystem->Alloc(n * 0x900, "MP3HybridHistory", 0x10, 0);
    mpPrevBlockX4 = (float*)p;
    if (p == 0)
        return -1;
    AudioMemset(p, 0, n * 0x900);
    return 0;
}
}}}  // namespace rw::audio::core

// @ 0x01146d70
namespace rw { namespace audio { namespace core {
void* CMpegLayer3Base_s0114_6ca0::ScalarDeletingDtor(unsigned int flags)
{
    float* old = *(float* volatile*)&mpPrevBlockX4;
    *(void* volatile*)&vftable = MPEGL3BASE_VFTABLE;
    _ReadWriteBarrier();
    if (old)
        g_audioSystem->Free(old, 0);
    this->CMpegBase::~CMpegBase();
    if (flags & 1)
        operator_delete__(this);
    return this;
}
}}}  // namespace rw::audio::core

// @ 0x01148cd0
namespace rw { namespace audio { namespace core {
// retail calls these from the derived class; keep the calls out of line (docs/codegen.md 6.5)
__declspec(noinline) CMpegBase::CMpegBase()
{
    vftable = MPEGBASE_VFTABLE;
    mResetSynthRequired = 0;
    mOpened = 0;
    mHeader = 0;
    mpPolySynthHistory = 0;
    mpLoadedPolySynthHistory = 0;
}
}}}  // namespace rw::audio::core

// @ 0x01148d40
namespace rw { namespace audio { namespace core {
__declspec(noinline) CMpegBase::~CMpegBase()
{
    vftable = MPEGBASE_VFTABLE;
    if (mpPolySynthHistory)
        g_audioSystem->Free(mpPolySynthHistory, 0);
}
}}}  // namespace rw::audio::core
