// Slice s010104c0: 0x010104C0..0x01011350.  SP::PirateRaidEvent /
// SP::GenericDisaster / SP::ArtifactEvent mission creation plus the eastl
// sort/copy helpers instantiated over SP::cSimulatorUniverse::tGrobShockData.
//
//  0x010104c0  SP::PirateRaidEvent::TryCreateMission      (386 B)
//  0x01010650  SP::GenericDisaster::TryCreateMission      (199 B)
//  0x01010720  SP::CreateArtifact::Start wrapper          ( 13 B)
//  0x01010730  artifact roll/insert helper                (122 B)
//  0x010107b0  rbtree probe + reward-tier classify        (181 B)
//  0x01010870  tGrobShockData copy ctor                   ( 76 B)
//  0x010108c0  eastl::insertion_sort                      (298 B)
//  0x010109f0  eastl::insertion_sort_simple               (305 B)
//  0x01010b30  range copy (vtable storing)               (127 B)
//  0x01010bb0  eastl::copy_impl::do_copy                 (105 B)
//  0x01010c20  heapify                                    ( 73 B)
//  0x01010e30  range copy backward                       (107 B)
//  0x01010ea0  eastl::promote_heap                       (195 B)
//  0x01010f70  tGrobShockData::operator=                  (188 B)
//  0x01011030  reward-timer tick                          (237 B)
//  0x01011120  SP::ArtifactEvent::TryCreateMission        (346 B)
//  0x01011350  city-distance partition                    (468 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- shared types

// SP::cSPTimer sub-object (0x20 bytes), embedded in tGrobShockData at +0x08.
// Its assignment copies only the timer payload, leaving the vtable/refcount alone.
struct cSPTimer {
    void*  mVtbl;        // +0x00
    int    mRefCount;    // +0x04
    int    mElapsedLo;   // +0x08
    int    mElapsedHi;   // +0x0c
    int    mBaseLo;      // +0x10
    int    mBaseHi;      // +0x14
    char   mRunning;     // +0x18
    char   mPad19[3];
    int    mGetMs;       // +0x1c

    cSPTimer& operator=(const cSPTimer& o)
    {
        mElapsedLo = o.mElapsedLo;
        mElapsedHi = o.mElapsedHi;
        mBaseLo    = o.mBaseLo;
        mBaseHi    = o.mBaseHi;
        mRunning   = o.mRunning;
        mGetMs     = o.mGetMs;
        return *this;
    }
};

// First two dwords of tGrobShockData.
// SP::cSimulatorUniverse::tGrobShockData (0x28 bytes).
struct tGrobShockData {
    int       mField00;  // +0x00
    int       mField04;  // +0x04
    cSPTimer  mTimer;    // +0x08

    tGrobShockData* FUN_01010870(const tGrobShockData& o);   // 0x01010870
};

// Comparator used by the eastl sort helpers.
typedef bool (__cdecl *tGrobLess)(const tGrobShockData&, const tGrobShockData&);

// ---------------------------------------------------------------- externs

void __stdcall Start(int a);        // 0x0100f7c0  SP::CreateArtifact::Start
void __cdecl   dtorTimer(void* p);  // 0x00b638b0  cGonzagoTimer::~cGonzagoTimer

// ---------------------------------------------------------------- 0x010104c0

// @ 0x010104c0
void FUN_010104c0(void) {}

// ---------------------------------------------------------------- 0x01010650

// @ 0x01010650
void FUN_01010650(void) {}

// ---------------------------------------------------------------- 0x01010720

// @ 0x01010720
void __stdcall FUN_01010720(int a, int b)
{
    (void)b;
    Start(a);
}

// ---------------------------------------------------------------- 0x01010730

// @ 0x01010730
void FUN_01010730(void) {}

// ---------------------------------------------------------------- 0x010107b0

// @ 0x010107b0
void FUN_010107b0(void) {}

// ---------------------------------------------------------------- 0x01010870

// @ 0x01010870
tGrobShockData* tGrobShockData::FUN_01010870(const tGrobShockData& o)
{
    mField00 = o.mField00;
    mField04 = o.mField04;
    mTimer.mVtbl = (void*)0x01465d54;
    mTimer.mRefCount = 0;
    mTimer.mElapsedLo = o.mTimer.mElapsedLo;
    mTimer.mElapsedHi = o.mTimer.mElapsedHi;
    mTimer.mBaseLo = o.mTimer.mBaseLo;
    mTimer.mBaseHi = o.mTimer.mBaseHi;
    mTimer.mRunning = o.mTimer.mRunning;
    mTimer.mGetMs = o.mTimer.mGetMs;
    mTimer.mVtbl = (void*)0x01464450;
    return this;
}

// ---------------------------------------------------------------- 0x010108c0

// @ 0x010108c0
void FUN_010108c0(void) {}

// ---------------------------------------------------------------- 0x010109f0

// @ 0x010109f0
void FUN_010109f0(void) {}

// ---------------------------------------------------------------- 0x01010b30

// @ 0x01010b30
void FUN_01010b30(void) {}

// ---------------------------------------------------------------- 0x01010bb0

// @ 0x01010bb0
tGrobShockData* __cdecl FUN_01010bb0(tGrobShockData* first, tGrobShockData* last, tGrobShockData* result)
{
    while (first != last) {
        *result = *first;
        first++;
        result++;
    }
    return result;
}

// ---------------------------------------------------------------- 0x01010c20

// @ 0x01010c20
void FUN_01010c20(void) {}

// ---------------------------------------------------------------- 0x01010e30

// @ 0x01010e30
tGrobShockData* __cdecl FUN_01010e30(tGrobShockData* first, tGrobShockData* last, tGrobShockData* result)
{
    while (first != last) {
        last--;
        result--;
        *result = *last;
    }
    return result;
}

// ---------------------------------------------------------------- 0x01010ea0

// @ 0x01010ea0
void FUN_01010ea0(void) {}

// ---------------------------------------------------------------- 0x01010f70

// @ 0x01010f70
void FUN_01010f70(void) {}

// ---------------------------------------------------------------- 0x01011030

// @ 0x01011030
void FUN_01011030(void) {}

// ---------------------------------------------------------------- 0x01011120

// @ 0x01011120
void FUN_01011120(void) {}

// ---------------------------------------------------------------- 0x01011350

// @ 0x01011350
void FUN_01011350(void) {}