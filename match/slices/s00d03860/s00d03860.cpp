// Slice s00d03860 -- relationship manager internals: mutual-relation flags, the relationship
// maps (tree_map / vector_map) and the subtree release used when a relationship bucket dies.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

// ---- eastl-ish containers kept as opaque sub-objects -----------------------

// tree_map<unsigned int, unsigned int> bucket: insert(key) yields the value slot.
struct tTreeMap {
    uint8_t pad000[0x18];                               // +0x00 .. +0x17

    uint32_t* Insert(const uint32_t& key);               // 0x00f41aa0
};

// vector_map<unsigned int, unsigned int>: operator[] yields the value slot.
struct tVectorMap {
    uint8_t pad000[0x18];                               // +0x00 .. +0x17

    uint32_t* Index(const uint32_t& key);                // 0x00564a10
};

// map used for the pairwise relationship table (member of the manager at +0x60).
struct tRelMap {
    uint8_t pad000[0x18];                               // +0x00 .. +0x17

    __declspec(noinline) void FUN_00d03e00(uint32_t first, uint32_t second);
};

// ---- relationship entries -------------------------------------------------

struct tRelNode;

// The payload sub-object that sits at tRelEntry+0x04.
struct tRelSub {
    uint32_t   mSecond;                                 // +0x00 (entry +0x04)
    uint8_t    pad004[0x04];                            // +0x04 .. +0x07
    uint32_t   mValue;                                  // +0x08 (entry +0x0c)
    tRelNode*  mpNode;                                  // +0x0c (entry +0x10)

    void FUN_00d03b10(tRelNode* pNode);
};

// 0x20-byte node of the relationship vector.
struct tRelEntry {
    uint32_t mId;                                       // +0x00
    tRelSub  mSub;                                      // +0x04
    uint32_t mPad014;                                   // +0x14
    uint32_t mPad018;                                   // +0x18
    uint32_t mPad01c;                                   // +0x1c
};

struct tRelChild {
    uint32_t   mId;                                     // +0x00
    tRelChild* mpNext;                                  // +0x04
};

// Nuke sub-object of a relationship node.
struct tRelChainSub {
    uint8_t pad000[0x0c];                               // +0x00 .. +0x0b

    void DoNukeSubtree(uint32_t id);                     // 0x009a9600
};

// 0x30-byte relationship node released by FUN_00d03b10.
struct tRelNode {
    tRelNode*     mpFirst;                              // +0x00
    tRelNode*     mpNext;                               // +0x04
    uint8_t       pad008[0x18];                         // +0x08 .. +0x1f
    tRelChainSub  mSub;                                 // +0x20
    tRelChild*    mpChildList;                          // +0x2c
};

// ---- relationship manager -------------------------------------------------

class cRelationshipManager {
public:
    uint8_t      pad000[0x2c];                          // +0x000 .. +0x02b
    uint32_t     mField02c;                             // +0x02c
    uint8_t      pad030[0x10];                          // +0x030 .. +0x03f
    uint32_t     mField040;                             // +0x040
    uint32_t     mField044;                             // +0x044
    uint8_t      pad048[0x18];                          // +0x048 .. +0x05f
    tRelMap      mRelations;                            // +0x060
    uint8_t      pad078[0x24];                          // +0x078 .. +0x09b
    tRelEntry*   mpEntryBegin;                          // +0x09c
    tRelEntry*   mpEntryEnd;                            // +0x0a0
    uint8_t      pad0a4[0x10];                          // +0x0a4 .. +0x0b3
    tTreeMap     mTreeMap;                              // +0x0b4
    tVectorMap   mVectorMap;                            // +0x0cc

    tRelSub* FUN_00d01ab0(uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4); // 0x00d01ab0
    void*    FUN_00d01410(tRelSub* pSub);               // 0x00d01410

    void FUN_00d03860(uint32_t a1, uint32_t a2, bool enabled);
    unsigned char FUN_00d038a0(uint32_t a1, uint32_t a2);
    void StartPeace(uint32_t civilizationA, uint32_t civilizationB);
    void FUN_00d039a0(uint32_t a1);
    void FUN_00d03a40(uint32_t a1);
    void FUN_00d03c40();
    void CalculateRelationshipEvent(uint32_t a1, uint32_t a2);
    void FUN_00d03f60();
    void FUN_00d03fd0();
    void FUN_00d04080(tRelEntry* pEntry);
    void FUN_00d040a0(uint32_t a1);
    void FUN_00d04210();
    void FUN_00d04290(uint32_t a1);
    void CalculateRelationshipCityProximity(uint32_t a1, uint32_t a2);
    void FUN_00d04670(uint32_t a1);
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xd03860 FUN_00d03860
void __thiscall cRelationshipManager::FUN_00d03860(uint32_t a1, uint32_t a2, bool enabled)
{
    tRelSub* pSub = FUN_00d01ab0(a1, a2, a1, a2);
    uint32_t* pFlags = (uint32_t*)FUN_00d01410(pSub);
    if (pFlags) {
        if (enabled)
            pFlags[1] |= 8;
        else
            pFlags[1] &= ~8u;
    }
}

// @ 0xd038a0 FUN_00d038a0
unsigned char __thiscall cRelationshipManager::FUN_00d038a0(uint32_t a1, uint32_t a2)
{
    tRelSub* pSub = FUN_00d01ab0(a1, a2, a1, a2);
    uint32_t* pFlags = (uint32_t*)FUN_00d01410(pSub);
    if (pFlags)
        return (pFlags[1] >> 3) & 1;
    return false;
}

// @ 0xd038e0 cRelationshipManager::StartPeace
void __thiscall cRelationshipManager::StartPeace(uint32_t civilizationA, uint32_t civilizationB)
{
    (void)civilizationA;
    (void)civilizationB;
}

// @ 0xd039a0 FUN_00d039a0
void __fastcall FUN_00d039a0(cRelationshipManager* this_, int unused, uint32_t a1)
{
    (void)this_;
    (void)a1;
}

// @ 0xd03a40 FUN_00d03a40
void __fastcall FUN_00d03a40(cRelationshipManager* this_, int unused, uint32_t a1)
{
    (void)this_;
    (void)a1;
}

// @ 0xd03b10 FUN_00d03b10
void __thiscall tRelSub::FUN_00d03b10(tRelNode* pNode)
{
    while (pNode) {
        FUN_00d03b10(pNode->mpFirst);
        tRelChild* pChild = pNode->mpChildList;
        tRelNode* pNext = pNode->mpNext;
        while (pChild) {
            pNode->mSub.DoNukeSubtree(pChild->mId);
            tRelChild* pChildNext = pChild->mpNext;
            delete[] pChild;
            pChild = pChildNext;
        }
        delete[] pNode;
        pNode = pNext;
    }
}

// @ 0xd03b80 SP::GetPropertyListForPersonality
void __cdecl GetPropertyListForPersonality(uint32_t personalityId, void* pOut)
{
    (void)personalityId;
    (void)pOut;
}

// @ 0xd03c40 FUN_00d03c40
void __fastcall FUN_00d03c40(cRelationshipManager* this_, int unused)
{
    (void)this_;
}

// @ 0xd03d70 cRelationshipManager::CalculateRelationshipEvent
void __thiscall cRelationshipManager::CalculateRelationshipEvent(uint32_t a1, uint32_t a2)
{
    (void)a1;
    (void)a2;
}

// @ 0xd03e00 FUN_00d03e00
__declspec(noinline) void __thiscall tRelMap::FUN_00d03e00(uint32_t first, uint32_t second)
{
    // Body not reconstructed; the arguments are consumed so callers keep the call.
    volatile uint32_t sink = first ^ second;
    (void)sink;
}

// @ 0xd03e90 FUN_00d03e90
void* __fastcall FUN_00d03e90(tRelMap* this_, int unused, const void* pValue)
{
    (void)this_;
    (void)pValue;
    return 0;
}

// @ 0xd03ef0 FUN_00d03ef0
void __fastcall FUN_00d03ef0(tRelMap* this_, int unused, const void* pKey, void* pOut, bool sideKnown)
{
    (void)this_;
    (void)pKey;
    (void)pOut;
    (void)sideKnown;
}

// @ 0xd03f60 FUN_00d03f60
void __thiscall cRelationshipManager::FUN_00d03f60()
{
    mField040 = mField02c;
    mField044 = 0;

    for (tRelEntry* pEntry = mpEntryBegin; pEntry != mpEntryEnd; ++pEntry) {
        uint32_t key = pEntry->mId;
        uint32_t value = pEntry->mSub.mValue;
        *mTreeMap.Insert(key) = value;
        *mVectorMap.Index(key) = 0;
    }
}

// @ 0xd03fd0 FUN_00d03fd0
void __fastcall FUN_00d03fd0(cRelationshipManager* this_, int unused)
{
    (void)this_;
}

// @ 0xd04080 FUN_00d04080
void __thiscall cRelationshipManager::FUN_00d04080(tRelEntry* pEntry)
{
    mRelations.FUN_00d03e00(pEntry->mId, pEntry->mSub.mSecond);
}

// @ 0xd040a0 FUN_00d040a0
void __fastcall FUN_00d040a0(cRelationshipManager* this_, int unused, uint32_t a1)
{
    (void)this_;
    (void)a1;
}

// @ 0xd041d0 FUN_00d041d0
tRelEntry* __cdecl FUN_00d041d0(tRelEntry* pFirst, tRelEntry* pLast, tRelEntry* pDest)
{
    if (pFirst == pLast)
        return pDest;

    tRelEntry* pOut = pDest;
    do {
        pFirst->mSub.FUN_00d03b10(pFirst->mSub.mpNode);
        ++pFirst;
        ++pOut;
    } while (pFirst != pLast);
    return pOut;
}

// @ 0xd04210 FUN_00d04210
void __fastcall FUN_00d04210(cRelationshipManager* this_, int unused)
{
    (void)this_;
}

// @ 0xd04290 FUN_00d04290
void __fastcall FUN_00d04290(cRelationshipManager* this_, int unused, uint32_t a1)
{
    (void)this_;
    (void)a1;
}

// @ 0xd04320 cRelationshipManager::CalculateRelationshipCityProximity
void __thiscall cRelationshipManager::CalculateRelationshipCityProximity(uint32_t a1, uint32_t a2)
{
    (void)a1;
    (void)a2;
}

// @ 0xd04670 FUN_00d04670
void __fastcall FUN_00d04670(cRelationshipManager* this_, int unused, uint32_t a1)
{
    (void)this_;
    (void)a1;
}

} // namespace SP

