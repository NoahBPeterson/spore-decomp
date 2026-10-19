// src/game/ealayer31/mpegl3base.cpp.cpp -- migrated from slice(s) s01146ca0, s01145d10 by tools/migrate/rewrite.py
// Object file: ealayer31/mpegl3base.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <malloc.h>
#include "rw/audio/core/System.h"

// ---- items of slice s01145d10 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s01145d10 end

// ---- items of slice s01146ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
class System_s0114_6ca0 {
public:
    void* Alloc(int size, const char* name, int align, int flags);  // 0x0112c820
    void  Free(void* p, int flags);                                 // 0x0112c850
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0114_6ca0* g_audioSystem;                   // 0x016e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
void operator_delete__(void* p);                // 0x00f47380
}
}
}
namespace rw {
namespace audio {
namespace core {
class CMpegBase {                               // size 0x50
public:
    void* vftable;                              // +0x00
    uint8_t pad04[0x50 - 4];
    CMpegBase();                                // 0x01148cd0
    ~CMpegBase();                               // 0x01148d40
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class CMpegLayer3Base_s0114_6ca0 : public CMpegBase {      // size 0x2dc
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

    CMpegLayer3Base_s0114_6ca0();                          // 0x01146ca0
    ~CMpegLayer3Base_s0114_6ca0();                         // 0x01146cf0
    int  AllocateHybrid(int n);                 // 0x01146d20
    void* ScalarDeletingDtor(unsigned int flags);// 0x01146d70
    void InitHuffTables();                      // 0x01146a90
};
}
}
}
// ---- items of slice s01146ca0 end

// @ 0x01146a90
namespace rw { namespace audio { namespace core {
void CMpegLayer3Base::InitHuffTables()
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
    vftable = (void*)0x14cc180;
    mpTwoToNegativeQuarterPower = (float*)0x14cbd80;
    mTwoToNegativeQuarterPowerTableSize = 0x400;
    mpLoadedTwoToNegativeQuarterPower = 0;
    InitHuffTables();
    mpLoadedTableSelect[0] = 0;
    mpLoadedTableSelect[1] = 0;
    mpLoadedTableSelect[2] = 0;
}
}}}  // namespace rw::audio::core

// @ 0x01146cf0
namespace rw { namespace audio { namespace core {
CMpegLayer3Base_s0114_6ca0::~CMpegLayer3Base_s0114_6ca0()
{
    float* old = *(float* volatile*)&mpPrevBlockX4;
    *(void* volatile*)&vftable = (void*)0x14cc180;
    if (old)
        g_audioSystem->Free(old, 0);
}
}}}  // namespace rw::audio::core

// @ 0x01146d70
namespace rw { namespace audio { namespace core {
void* CMpegLayer3Base_s0114_6ca0::ScalarDeletingDtor(unsigned int flags)
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
}}}  // namespace rw::audio::core
