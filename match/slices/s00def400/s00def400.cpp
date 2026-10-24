// Slice s00def400 -- galaxy game-entry UI state machine plus the eastl hash-table find used to
// look up localisation keys by their UTF-16 FNV-1a hash.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace eastl {

// Node of an open-addressing-chained hash table; +0x14 links to the next node in the bucket.
struct cHashNode {
    uint8_t     pad000[0x14];                            // +0x00 .. +0x13
    cHashNode*  mpNext;                                  // +0x14
};

struct cHashIterator {
    cHashNode*  mpNode;                                  // +0x00
    cHashNode** mppBucket;                               // +0x04
};

// Locale comparison used while probing a bucket (0 = equal).
int __cdecl Locale_CompareKeys(const wchar_t* pKey, cHashNode* pNode); // 0x0087d9a0

class cHashTable {
public:
    uint8_t     pad000[4];                               // +0x00
    cHashNode** mppBuckets;                              // +0x04
    uint32_t    mBucketCount;                            // +0x08

    cHashIterator FUN_00def5f0(const wchar_t** ppKey);
};

} // namespace eastl

using namespace eastl;

namespace SP {

class cGalaxyGameEntryUIStateMachine {
public:
    void FUN_00def400();
    void FUN_00def690();
    void FUN_00def750(uint32_t id, uint32_t value);
    void FUN_00def7c0();
    void UpdateNavigationControls();
    void FUN_00defc00();
    void MakeRandomName();
    void SetStateSummaryText();
    void SelectTheme();
    void FillComboBoxes();
    void UpdateSpecialitySummaryText();
};

} // namespace SP

using namespace SP;

// @ 0xdef400 SP::cGalaxyGameEntryUIStateMachine::FUN_00def400
void __thiscall cGalaxyGameEntryUIStateMachine::FUN_00def400()
{
}

// @ 0xdef5f0 eastl::cHashTable::FUN_00def5f0
cHashIterator __thiscall cHashTable::FUN_00def5f0(const wchar_t** ppKey)
{
    const wchar_t* pKey = *ppKey;
    uint32_t hash = 2166136261u;
    uint32_t ch = (uint32_t)*pKey;
    if (ch != 0) {
        do {
            hash *= 16777619u;
            ++pKey;
            hash ^= ch;
            ch = (uint32_t)*pKey;
        } while (ch != 0);
    }

    cHashIterator it;
    cHashNode** pBucket = &mppBuckets[hash % mBucketCount];
    cHashNode* pNode = *pBucket;
    while (pNode) {
        if (Locale_CompareKeys(*ppKey, pNode))
            break;
        pNode = pNode->mpNext;
    }
    if (pNode) {
        it.mpNode = pNode;
        it.mppBucket = pBucket;
    } else {
        it.mpNode = mppBuckets[mBucketCount];
        it.mppBucket = &mppBuckets[mBucketCount];
    }
    return it;
}

namespace SP {

// @ 0xdef690 SP::cGalaxyGameEntryUIStateMachine::FUN_00def690
void __thiscall cGalaxyGameEntryUIStateMachine::FUN_00def690()
{
}

// @ 0xdef750 SP::cGalaxyGameEntryUIStateMachine::FUN_00def750
void __thiscall cGalaxyGameEntryUIStateMachine::FUN_00def750(uint32_t id, uint32_t value)
{
    (void)id;
    (void)value;
}

// @ 0xdef7c0 SP::cGalaxyGameEntryUIStateMachine::FUN_00def7c0
void __thiscall cGalaxyGameEntryUIStateMachine::FUN_00def7c0()
{
}

// @ 0xdef8c0 SP::cGalaxyGameEntryUIStateMachine::UpdateNavigationControls
void __thiscall cGalaxyGameEntryUIStateMachine::UpdateNavigationControls()
{
}

// @ 0xdefc00 SP::cGalaxyGameEntryUIStateMachine::FUN_00defc00
void __thiscall cGalaxyGameEntryUIStateMachine::FUN_00defc00()
{
}

// @ 0xdefc80 SP::cGalaxyGameEntryUIStateMachine::MakeRandomName
void __thiscall cGalaxyGameEntryUIStateMachine::MakeRandomName()
{
}

// @ 0xdefd10 SP::cGalaxyGameEntryUIStateMachine::SetStateSummaryText
void __thiscall cGalaxyGameEntryUIStateMachine::SetStateSummaryText()
{
}

// @ 0xdefdd0 SP::cGalaxyGameEntryUIStateMachine::SelectTheme
void __thiscall cGalaxyGameEntryUIStateMachine::SelectTheme()
{
}

// @ 0xdf00b0 SP::cGalaxyGameEntryUIStateMachine::FillComboBoxes
void __thiscall cGalaxyGameEntryUIStateMachine::FillComboBoxes()
{
}

// @ 0xdf0190 SP::cGalaxyGameEntryUIStateMachine::UpdateSpecialitySummaryText
void __thiscall cGalaxyGameEntryUIStateMachine::UpdateSpecialitySummaryText()
{
}

} // namespace SP
