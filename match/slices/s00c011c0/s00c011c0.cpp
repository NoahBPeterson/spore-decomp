// Slice s00c011c0: 0x00c011c0..0x00c011ba (1 function, 250 bytes).
//
//   0x00c011c0  SP::cCommunity::cCommunity   (250 B)
//
// The class is the 0x120-byte primary prefix of Simulator::cCity; slice
// s00be6310 declares its constructor as cCityPrefix() @ 0x00c011c0.  Retail
// places its members 8 bytes higher than the generated cCommunity.h layout
// (SP::cGameData is 0x34 bytes in retail, not 0x2c); its vectors are 20 bytes
// (three pointers + 8-byte allocator state) and its strings 16 bytes.
//
// Toolchain: cl 15.00.30729.01 (VS2008 SP1), /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>   // _ReadWriteBarrier (scheduling barrier, emits no code)

// ---------------------------------------------------------------- callee ABI

// SP::cGameData, the leading base sub-object.  Only its size (0x34) and its
// constructor entry point matter here.
struct cGameData {
    void* mpVtbl0;                                           // +0x000
    void* mpVtbl1;                                           // +0x004
    unsigned char mRaw008[0x34 - 0x08];                      // +0x008..+0x033
    cGameData();                                             // 0x00b18660
};

// Interface base at +0x34 (cISPEditorNameProvider).
struct cISPEditorNameProvider {
    void* mpVtbl;                                            // +0x034
};

// 20-byte eastl vector header: begin / end / capacity + 8-byte allocator state.
struct cVector {
    void*          mpBegin;                                  // +0x00
    void*          mpEnd;                                    // +0x04
    void*          mpCapacity;                               // +0x08
    unsigned char  mAllocator[8];                            // +0x0c
};

// 16-byte 16-bit eastl::basic_string: three pointers + allocator state.
struct cStr16 {
    void*          mpBegin;                                  // +0x00
    void*          mpEnd;                                    // +0x04
    void*          mpCapacity;                               // +0x08
    unsigned char  mAllocator[4];                            // +0x0c
};

// SP::cGonzagoTimer (0x20 bytes), ctor 0x00b63890, Restart 0x00bc3130.
struct cTimer {
    unsigned char mRaw[0x20];
    void Construct();
    void Restart();
};

// ---------------------------------------------------------------- class

#pragma pack(push, 4)
struct cCommunity : cGameData, cISPEditorNameProvider {
    int            mCommunitySize;                           // +0x038
    cVector        mStructureLines;                          // +0x03c
    float          mInnerWallRadius;                         // +0x050
    float          mOuterWallRadius;                         // +0x054
    cVector        mGateInfo;                                // +0x058
    bool           mbNeedsNavigationUpdate;                  // +0x06c
    unsigned char  mPad06d[3];                               // +0x06d
    cVector        mAssemblyBubbles;                         // +0x070
    cVector        mLanes;                                   // +0x084
    unsigned __int64 mLastAttack[3];                         // +0x098
    cTimer         mPlayerWarningTimer;                      // +0x0b0
    cVector        mStructures;                              // +0x0d0
    cVector        mInhabitants;                             // +0x0e4
    cStr16         mName;                                    // +0x0f8
    cStr16         mDescription;                             // +0x108
    unsigned int   mGODPoliticalID;                          // +0x118
    void*          mpLeader;                                 // +0x11c

    cCommunity();
};
#pragma pack(pop)

// Empty eastl containers point at the shared .rdata empty buffer:
// 0x01667bac is the empty wchar_t buffer, 0x01667bae is one past it.

// @ 0x00c011c0
//
// The `_ReadWriteBarrier()` calls are compiler fences (they emit no code): retail
// schedules this constructor as a chain of small regions, and each fence pins the
// address computation that follows it at the region start, exactly where the
// original puts it.
cCommunity::cCommunity()
{
    // The interface sub-object's base vftable is installed first, then the two
    // primary vftables, then the community's own interface vftable.
    mpVtbl   = (void*)0x13ef63c;                             // +0x034
    _ReadWriteBarrier();   // retail keeps this base vftable store, dead as it is
    mpVtbl0  = (void*)0x1469ce8;                             // +0x000
    mpVtbl1  = (void*)0x1469cd8;                             // +0x004
    mpVtbl   = (void*)0x1469cc0;                             // +0x034

    mCommunitySize = 0;                                      // +0x038
    mStructureLines.mpBegin = 0;                             // +0x03c
    mStructureLines.mpEnd = 0;                               // +0x040
    mStructureLines.mpCapacity = 0;                          // +0x044

    mGateInfo.mpBegin = 0;                                   // +0x058
    mGateInfo.mpEnd = 0;                                     // +0x05c
    mGateInfo.mpCapacity = 0;                                // +0x060

    mbNeedsNavigationUpdate = false;                         // +0x06c

    mAssemblyBubbles.mpBegin = 0;                            // +0x070
    mAssemblyBubbles.mpEnd = 0;                              // +0x074
    mAssemblyBubbles.mpCapacity = 0;                         // +0x078

    _ReadWriteBarrier();   // pins the timer's `lea edi,[esi+0xb0]` below these stores
    mLanes.mpBegin = 0;                                      // +0x084
    mLanes.mpEnd = 0;                                        // +0x088
    mLanes.mpCapacity = 0;                                   // +0x08c

    mPlayerWarningTimer.Construct();                         // +0x0b0

    mStructures.mpBegin = 0;                                 // +0x0d0
    mStructures.mpEnd = 0;                                   // +0x0d4
    mStructures.mpCapacity = 0;                              // +0x0d8

    mInhabitants.mpBegin = 0;                                // +0x0e4
    mInhabitants.mpEnd = 0;                                  // +0x0e8
    mInhabitants.mpCapacity = 0;                             // +0x0ec

    // Empty strings: begin == end == the shared empty buffer at 0x01667bac and
    // capacity == one past it, 0x01667bae.
    _ReadWriteBarrier();
    mName.mpBegin = (void*)0x1667bac;                            // +0x0f8
    mName.mpEnd = (void*)0x1667bac;                              // +0x0fc
    _ReadWriteBarrier();   // the two capacities are materialised below 0x1667bac's stores
    mName.mpCapacity = (void*)0x1667bae;                         // +0x100
    mDescription.mpCapacity = (void*)0x1667bae;                  // +0x110
    mDescription.mpBegin = (void*)0x1667bac;                     // +0x108
    mDescription.mpEnd = (void*)0x1667bac;                       // +0x10c

    mGODPoliticalID = 0xffffffff;                            // +0x118
    mpLeader = 0;                                            // +0x11c

    _ReadWriteBarrier();   // pins the second `mov ecx,edi` after +0x11c
    mLastAttack[0] = 0;                                      // +0x098
    mLastAttack[1] = 0;                                      // +0x0a0
    mLastAttack[2] = 0;                                      // +0x0a8

    mPlayerWarningTimer.Restart();                           // +0x0b0
}
