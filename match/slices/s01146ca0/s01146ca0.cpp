// Slice s01146ca0 -- rw::audio::core::CMpegLayer3Base construction/teardown.
//   01146CA0  CMpegLayer3Base::CMpegLayer3Base   (set vtable + two-to-negative-quarter table, InitHuffTables)
//   01146CF0  CMpegLayer3Base::~CMpegLayer3Base  (free the hybrid history, run the base dtor)
//   01146D20  CMpegLayer3Base::AllocateHybrid    (System::Alloc n*0x900 bytes, zero it)
//   01146D70  CMpegLayer3Base scalar deleting dtor (free + optional operator delete)
// The class layout comes from the 2008 dev PDB (CMpegBase 0x50, CMpegLayer3Base 0x2dc).
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <string.h>

namespace rw { namespace audio { namespace core {

struct GranuleInfo {                            // size 0x18
    uint16_t part2And3Length;
    uint16_t bigValues;
    uint16_t scaleFacCompress;
    uint8_t  globalGain;
    uint8_t  windowSwitchingFlag;
    uint8_t  blockType;
    uint8_t  mixedBlockFlag;
    uint8_t  region0Count;
    uint8_t  region1Count;
    uint8_t  tableSelect[3];
    uint8_t  count1TableSelect;
    uint8_t  subBlockGain[3];
    uint8_t  preFlag;
    uint32_t scaleFacScale;
};

struct HuffTable {                              // size 8
    uint16_t tableSize;                         // +0x0
    uint16_t pad02;
    int16_t* pEntries;                          // +0x4
};

class System {
public:
    void* Alloc(int size, const char* name, int align, int flags);  // 0x0112c820
    void  Free(void* p, int flags);                                 // 0x0112c850
};

extern System* g_audioSystem;                   // 0x016e61a8

void operator_delete__(void* p);                // 0x00f47380
void* AudioMemset(void* dst, int c, unsigned n); // 0x011e073e (memset import thunk)

class CMpegBase {                               // size 0x50
public:
    void* vftable;                              // +0x00
    uint8_t pad04[0x50 - 4];
    CMpegBase();                                // 0x01148cd0
    ~CMpegBase();                               // 0x01148d40
};

class CMpegLayer3Base : public CMpegBase {      // size 0x2dc
public:
    HuffTable mHuffTables[32];                  // +0x50
    uint8_t   pad150[4];
    GranuleInfo mGranuleInfo[2][2];             // +0x154
    uint8_t   pad1b4[0x2ac - 0x1b4];
    float*    mpTwoToNegativeQuarterPower;      // +0x2ac
    float*    mpLoadedTwoToNegativeQuarterPower;// +0x2b0
    int16_t*  mpLoadedTableSelect[3];           // +0x2b4
    float*    mpPrevBlockX4;                    // +0x2c0
    uint8_t   pad2c4[0x2d8 - 0x2c4];
    uint16_t  mTwoToNegativeQuarterPowerTableSize; // +0x2d8

    CMpegLayer3Base();                          // 0x01146ca0
    ~CMpegLayer3Base();                         // 0x01146cf0
    int  AllocateHybrid(int n);                 // 0x01146d20
    void* ScalarDeletingDtor(unsigned int flags);// 0x01146d70
    void InitHuffTables();                      // 0x01146a90
};

// @ 0x01146ca0
CMpegLayer3Base::CMpegLayer3Base() : CMpegBase()
{
    vftable = (void*)0x14cc180;
    mpTwoToNegativeQuarterPower = (float*)0x14cbd80;
    mTwoToNegativeQuarterPowerTableSize = 0x400;
    mpLoadedTwoToNegativeQuarterPower = 0;
    InitHuffTables();
    mpLoadedTableSelect[0] = 0;
    mpLoadedTableSelect[1] = 0;
    mpLoadedTableSelect[2] = 0;
}

// @ 0x01146cf0
CMpegLayer3Base::~CMpegLayer3Base()
{
    float* old = *(float* volatile*)&mpPrevBlockX4;
    *(void* volatile*)&vftable = (void*)0x14cc180;
    if (old)
        g_audioSystem->Free(old, 0);
}

// @ 0x01146d20
int CMpegLayer3Base::AllocateHybrid(int n)
{
    void* p = g_audioSystem->Alloc(n * 0x900, "MP3HybridHistory", 0x10, 0);
    mpPrevBlockX4 = (float*)p;
    if (p == 0)
        return -1;
    AudioMemset(p, 0, n * 0x900);
    return 0;
}

// @ 0x01146d70
void* CMpegLayer3Base::ScalarDeletingDtor(unsigned int flags)
{
    float* old = *(float* volatile*)&mpPrevBlockX4;
    *(void* volatile*)&vftable = (void*)0x14cc180;
    if (old)
        g_audioSystem->Free(old, 0);
    this->CMpegBase::~CMpegBase();
    if (flags & 1)
        operator_delete__(this);
    return this;
}

} } }
