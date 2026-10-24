// Slice s010146c0 -- simulator universe grob-shock timer purge and the
// event/action vector insert helper.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

// Timer shared by the simulation record (external definitions).
class cGonzagoTimer {
public:
    ~cGonzagoTimer();                                    // 0x00b638b0
};

class cSPTimer : public cGonzagoTimer {
public:
    ~cSPTimer();
    uint64_t GetElapsedTime();                           // 0x00bc3190
};

namespace eastl {

// Element copy helper instantiated for the grob-shock record.
void __cdecl copy_impl_grob_shock(void* pFirst, void* pLast, void* pDest); // 0x1010bb0

} // namespace eastl

namespace SP {

// One grob-shock record: a timer plus the rest of the payload (0x28 bytes).
struct tGrobShockData {
    uint32_t  mField0;                                   // +0x00
    uint32_t  mField4;                                   // +0x04
    cSPTimer  mTimer;                                    // +0x08
    uint8_t   mPayload[0x1f];                            // +0x09 .. +0x27
};

// Allocator instance carried by the action list (8 bytes).
struct tActionAllocator {
    void* mpPool;                                        // +0x00
    void* mpOwner;                                       // +0x04
};

// Action list stored for one universe event (20 bytes inside the pair).
struct tUniverseActionVector {
    void*             mpBegin;                           // +0x00
    void*             mpEnd;                             // +0x04
    void*             mpCapacity;                        // +0x08
    tActionAllocator  mAllocator;                        // +0x0c
};

// eastl::pair<UniverseEvent*, vector<UniverseAction*>> (0x18 bytes).
struct tUniversePair {
    void*                 mpEvent;                       // +0x00
    tUniverseActionVector mActions;                      // +0x08

    void Construct(const tUniversePair& value);          // 0x1012f30
};

// growable vector of the event/action pairs.
class cUniversePairVector {
public:
    tUniversePair* Insert(tUniversePair* pPosition, const tUniversePair& value);
    tUniversePair* DoInsertValue(tUniversePair* pPosition, const tUniversePair& value); // 0x1015250

    tUniversePair* mpBegin;                              // +0x00
    tUniversePair* mpEnd;                                // +0x04
    tUniversePair* mpCapacity;                           // +0x08
};

class cSimulatorUniverse {
public:
    void FUN_010146c0();
    void FUN_01014870();
    void UpdateGrobShock(int32_t a1, int32_t a2);
    void AdjustAwareness();
    void FUN_01015130();
    void OnTick();

    uint8_t            pad000[0x11c];                    // +0x000 .. +0x11b
    uint32_t           mShockThreshold;                  // +0x11c
    uint8_t            pad120[8];                        // +0x120 .. +0x127
    tGrobShockData*    mGrobShockBegin;                  // +0x128
    tGrobShockData*    mGrobShockEnd;                    // +0x12c
};

} // namespace SP

using namespace SP;

// @ 0x10146c0 FUN_010146c0
void __cdecl FUN_010146c0()
{
}

// @ 0x1014870 FUN_01014870
void __cdecl FUN_01014870()
{
}

namespace SP {

// @ 0x1014a00 SP::cSimulatorUniverse::UpdateGrobShock
void __thiscall cSimulatorUniverse::UpdateGrobShock(int32_t a1, int32_t a2)
{
    (void)a1;
    (void)a2;
    tGrobShockData* pStart = mGrobShockBegin;
    if (pStart == mGrobShockEnd)
        return;
    for (tGrobShockData* p = pStart; p != mGrobShockEnd; ) {
        if (p->mTimer.GetElapsedTime() < mShockThreshold)
            break;
        tGrobShockData* pNext = p + 1;
        if (pNext < mGrobShockEnd)
            eastl::copy_impl_grob_shock(pNext, mGrobShockEnd, p);
        mGrobShockEnd -= 1;
        mGrobShockEnd->mTimer.~cSPTimer();
    }
}

// @ 0x1014a80 SP::cSimulatorUniverse::AdjustAwareness
void __thiscall cSimulatorUniverse::AdjustAwareness()
{
}

// @ 0x1014db0 eastl::quick_sort_grob_shock
void __cdecl quick_sort_grob_shock()
{
}

// @ 0x1014e30 SP::cSimulatorUniverse::OnTick
void __thiscall cSimulatorUniverse::OnTick()
{
}

// @ 0x1015130 SP::cSimulatorUniverse::FUN_01015130
void __thiscall cSimulatorUniverse::FUN_01015130()
{
}

} // namespace SP

// @ 0x10151a0 FUN_010151a0
void __cdecl FUN_010151a0()
{
}

// @ 0x1015250 SP::cUniversePairVector::DoInsertValue
tUniversePair* __thiscall cUniversePairVector::DoInsertValue(tUniversePair* pPosition, const tUniversePair& value)
{
    return 0;
}

// @ 0x10153a0 SP::cUniversePairVector::Insert
tUniversePair* __thiscall cUniversePairVector::Insert(tUniversePair* pPosition, const tUniversePair& value)
{
    uint32_t index = (uint32_t)(pPosition - mpBegin);
    if (pPosition == mpEnd && mpEnd != mpCapacity) {
        tUniversePair* pSlot = mpEnd;
        mpEnd = pSlot + 1;
        if (pSlot)
            pSlot->Construct(value);
        return mpBegin + index;
    }
    DoInsertValue(pPosition, value);
    return mpBegin + index;
}

// @ 0x1015410 SP::UniverseEventMapIndex
void __cdecl UniverseEventMapIndex()
{
}
