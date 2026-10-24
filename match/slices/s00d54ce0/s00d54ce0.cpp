// s00d54ce0 - SP::cBehaviorSpaceTurret (gold6 worker 36)
#include <math.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

// ---------------------------------------------------------------------------
// Foreign objects referenced from this translation unit
// ---------------------------------------------------------------------------
class cCombatant {
public:
    int GetDamageState();                                       // 0x008e7f80
    bool IsHostileAlive();                                      // 0x00bfc600
};

class cSPTimer {
public:
    void Stop();                                                // 0x00bc3110
};

class cInteractionAgent {
public:
    void* mpVtable;                                             // 0x00
};

extern void* gInteractionAgentTypeInfo;                         // 0x013f94d4
extern cSPTimer gsAirRaidTimer;                                 // 0x0169ebc0
extern void* gsAirRaidEffect;                                   // 0x0169ebe0
extern float gsSpaceHelixStep;                                  // 0x0169ebf0

struct cVector3Array {
    float* mpBegin;                                             // 0x00
    float* mpEnd;                                               // 0x04
    float* mpCapacity;                                          // 0x08

    void Clear() { mpEnd = mpBegin; }
};

void Vector3_Push(cVector3Array*, const float*);                // 0x004b5ad0
void Vector3Array_Reserve(uint32_t nCount);                     // 0x00473890
int  GetDetailLevelCount();                                     // 0x011e0810

// ---------------------------------------------------------------------------
// spstl slot vector (cInteraction::mAgentList): a deque of 128-entry blocks.
// The block array starts at +0x00, the free-chain head is at +0x14 and the
// current slot index at +0x18.
// ---------------------------------------------------------------------------
struct cSlotEntry {
    void* mpObject;                                             // 0x00 AutoRefCount payload
    uint32_t mnFlags;                                           // 0x04
};

struct cSlotBlock {
    uint32_t mnHeader;                                          // 0x00
    cSlotEntry mEntries[128];                                   // 0x04
};

struct cSlotIterator {
    uint8_t* mpBase;                                            // 0x00 container address
    uint32_t mnIndex;                                           // 0x04

    void Increment();                                           // 0x00abe9b0
    bool operator!=(const cSlotIterator& other) const
    {
        return mpBase + mnIndex != other.mpBase + other.mnIndex;
    }
};

struct cAgentSlotVector {
    cSlotBlock** mpBlocks;                                      // 0x00
    cSlotBlock** mpEnd;                                         // 0x04
    uint32_t mnUnk08;                                           // 0x08
    uint32_t mnUnk0c;                                           // 0x0c
    uint32_t mnUnk10;                                           // 0x10
    uint32_t mnFreeChain;                                       // 0x14
    uint32_t mnIndex;                                           // 0x18

    uint32_t EndIndex() const
    {
        return ((int)((char*)mpEnd - (char*)mpBlocks) >> 2) * 128 - 127
               + mnFreeChain;
    }

    cSlotIterator Begin() const
    {
        cSlotIterator it;
        it.mpBase = (uint8_t*)this;
        it.mnIndex = mnIndex;
        if (it.mnIndex >= 0x3fffffff)
            it.mnIndex = EndIndex();
        return it;
    }

    cSlotIterator End() const
    {
        cSlotIterator it;
        it.mpBase = (uint8_t*)this;
        it.mnIndex = EndIndex();
        return it;
    }
};

// ---------------------------------------------------------------------------
// Shared helper objects
// ---------------------------------------------------------------------------
struct cGonzagoTimerData {
    float mfElapsedTime;                                        // 0x00
    float mfDuration;                                           // 0x04
    uint32_t mnFlags;                                           // 0x08
    uint32_t mnUnk0c;                                           // 0x0c
    uint32_t mnUnk10;                                           // 0x10
    uint32_t mnUnk14;                                           // 0x14
    uint32_t mnUnk18;                                           // 0x18
    uint32_t mnUnk1c;                                           // 0x1c
    uint32_t mnUnk20;                                           // 0x20
    uint32_t mnUnk24;                                           // 0x24

    void Construct();                                           // 0x00b63890
    void Destruct();                                            // 0x00b638b0
};

struct cRBNodeBase {
    cRBNodeBase* mpNodeRight;                                   // 0x00
    cRBNodeBase* mpNodeLeft;                                    // 0x04
    cRBNodeBase* mpNodeParent;                                  // 0x08
    uint8_t mnColor;                                            // 0x0c
    uint8_t mPad0d[3];                                          // 0x0d
};

// cInteractionAgent* -> cSpaceTurretStateInfo map: eastl rbtree, anchor at +4.
struct cTurretStateTree {
    uint32_t mnUnk00;                                           // 0x00
    cRBNodeBase mAnchor;                                        // 0x04
    uint32_t mnSize;                                            // 0x14
    uint32_t mnUnk18;                                           // 0x18

    void NukeSubtree(cRBNodeBase* pNode);                       // 0x00d54ac0
};

// ---------------------------------------------------------------------------
// Base behaviour object (layout up to the agent list is owned by cInteraction)
// ---------------------------------------------------------------------------
class cInteraction {
public:
    cInteraction();                                             // 0x00abf320
    ~cInteraction();                                            // 0x00abf190

    void* mpVtable;                                             // 0x00 vtbl_Simulator::cBehaviorSpaceTurret
    void* mpRefCountVtable;                                     // 0x04
    uint32_t mUnk08[9];                                         // 0x08
    cAgentSlotVector mAgentList;                                // 0x2c
};

class cBehaviorSpaceTurret : public cInteraction {
public:
    cBehaviorSpaceTurret();                                     // 0x00d54fa0
    ~cBehaviorSpaceTurret();                                    // 0x00d54e50
    int GetActiveTurretCount();                                 // 0x00d54ce0
    int CountAttackableTurrets();                               // 0x00d54d90

    uint32_t mUnk48[11];                                        // 0x48
    cTurretStateTree mStateTree;                                // 0x74
    cGonzagoTimerData mLifeTimer;                               // 0x90
    uint32_t mnUnkB8;                                           // 0xb8
    uint32_t mnUnkBc;                                           // 0xbc
    uint32_t mnUnkC0;                                           // 0xc0
    uint32_t mnUnkC4;                                           // 0xc4
    uint32_t mnSdrBeamLifetime;                                 // 0xc8
    uint32_t mnUnkCc;                                           // 0xcc
    uint32_t mnUnkD0;                                           // 0xd0
    uint32_t mnUnkD4;                                           // 0xd4
    uint8_t mbAirRaidDone;                                      // 0xd8
    uint8_t mUnkD9[7];                                          // 0xd9
    cGonzagoTimerData mAirRaidTimer;                            // 0xe0
};

// ---------------------------------------------------------------------------
// 0x00d54ce0  cBehaviorSpaceTurret::GetActiveTurretCount
// ---------------------------------------------------------------------------
// @ 0x00d54ce0
int cBehaviorSpaceTurret::GetActiveTurretCount()
{
    int nCount = 0;
    for (cSlotIterator it = mAgentList.Begin(); it != mAgentList.End();
         it.Increment()) {
        cSlotEntry* pEntry =
            &((cAgentSlotVector*)it.mpBase)->mpBlocks[it.mnIndex >> 7]
                 ->mEntries[it.mnIndex & 0x7f];
        cInteractionAgent* pAgent = (cInteractionAgent*)pEntry->mpObject;
        cCombatant* pCombatant;
        if (pAgent != 0)
            pCombatant = ((cCombatant* (__thiscall*)(cInteractionAgent*, void*))
                              ((void**)pAgent->mpVtable)[0x08 / 4])(
                pAgent, &gInteractionAgentTypeInfo);
        else
            pCombatant = 0;
        if (pCombatant->GetDamageState() != 2)
            ++nCount;
    }
    return nCount;
}

// ---------------------------------------------------------------------------
// 0x00d54d90  cBehaviorSpaceTurret::CountAttackableTurrets
// ---------------------------------------------------------------------------
// @ 0x00d54d90
int cBehaviorSpaceTurret::CountAttackableTurrets()
{
    int nCount = 0;
    for (cSlotIterator it = mAgentList.Begin(); it != mAgentList.End();
         it.Increment()) {
        cSlotEntry* pEntry =
            &((cAgentSlotVector*)it.mpBase)->mpBlocks[it.mnIndex >> 7]
                 ->mEntries[it.mnIndex & 0x7f];
        cInteractionAgent* pAgent = (cInteractionAgent*)pEntry->mpObject;
        cCombatant* pCombatant;
        if (pAgent != 0)
            pCombatant = ((cCombatant* (__thiscall*)(cInteractionAgent*, void*))
                              ((void**)pAgent->mpVtable)[0x08 / 4])(
                pAgent, &gInteractionAgentTypeInfo);
        else
            pCombatant = 0;
        if (pCombatant->GetDamageState() != 2) {
            if (pCombatant->IsHostileAlive())
                ++nCount;
        }
    }
    return nCount;
}

// ---------------------------------------------------------------------------
// 0x00d54e50  cBehaviorSpaceTurret::~cBehaviorSpaceTurret
// ---------------------------------------------------------------------------
// @ 0x00d54e50
cBehaviorSpaceTurret::~cBehaviorSpaceTurret()
{
    mpVtable = (void*)0x147b900;
    mpRefCountVtable = (void*)0x147b8ec;
    if (mbAirRaidDone == 0) {
        gsAirRaidTimer.Stop();
        void* pEffect = gsAirRaidEffect;
        if (pEffect != 0) {
            void** ppVtable = *(void***)pEffect;
            ((void (__thiscall*)(void*, int))ppVtable[0x0c / 4])(pEffect, 0);
        }
    }
    mAirRaidTimer.Destruct();
    mLifeTimer.Destruct();
    cRBNodeBase* pRoot = mStateTree.mAnchor.mpNodeParent;
    cTurretStateTree* pTree = &mStateTree;
    pTree->NukeSubtree(pRoot);
}

// ---------------------------------------------------------------------------
// 0x00d54fa0  cBehaviorSpaceTurret::cBehaviorSpaceTurret
// ---------------------------------------------------------------------------
// @ 0x00d54fa0
cBehaviorSpaceTurret::cBehaviorSpaceTurret()
{
    mpVtable = (void*)0x147b900;
    mpRefCountVtable = (void*)0x147b8ec;
    // eastl rbtree reset: anchor first cleared, then re-linked to itself.
    mStateTree.mAnchor.mpNodeLeft = 0;
    mStateTree.mAnchor.mpNodeParent = 0;
    mStateTree.mAnchor.mnColor = 0;
    mStateTree.mAnchor.mpNodeRight = &mStateTree.mAnchor;
    mStateTree.mAnchor.mpNodeLeft = &mStateTree.mAnchor;
    mStateTree.mAnchor.mpNodeParent = 0;
    mStateTree.mAnchor.mnColor = 0;
    mStateTree.mnSize = 0;
    mLifeTimer.Construct();
    mnUnkB8 = 0;
    mAirRaidTimer.Construct();
    mbAirRaidDone = 0;
    mnSdrBeamLifetime = 8;
}

// ---------------------------------------------------------------------------
// 0x00d55060  helix sampler
// ---------------------------------------------------------------------------
// @ 0x00d55060
void SpaceTurret_SampleHelix(int nSamples, cVector3Array* pVertices, float fArg3,
                             float fArg4, float fArg5, float fArg6, float fArg7,
                             float fArg8, float fArg9, float fArg10,
                             float fArg11, float fArg12)
{
    pVertices->Clear();
    Vector3Array_Reserve(nSamples);
    float fStep = gsSpaceHelixStep / (float)nSamples;
    for (int i = 0; i < nSamples; ++i) {
        float fHalf = (float)i * 0.5f;
        float fSin = (float)sin(fHalf);
        float fCos = (float)cos(fHalf);
        float v[3];
        v[0] = fArg6 * fSin + fArg3;
        v[1] = fArg7 * fSin + fArg4;
        v[2] = fArg8 * fCos + fArg5;
        Vector3_Push(pVertices, v);
        fHalf = fStep;
    }
}

// ---------------------------------------------------------------------------
// 0x00d552c0  grid sampler
// ---------------------------------------------------------------------------
// @ 0x00d552c0
void SpaceTurret_SampleGrid(int nSamples, cVector3Array* pVertices, float fArg3,
                            float fArg4, float fArg5, float fArg6, float fArg7,
                            float fArg8, float fArg9, float fArg10, float fArg11,
                            float fArg12)
{
    int nCount = GetDetailLevelCount();
    if (nCount < 1)
        nCount = 1;
    pVertices->Clear();
    Vector3Array_Reserve((uint32_t)(nCount * nCount) / 2);
    float fStep = (fArg12 / (float)nCount) * 2.0f;
    for (int i = 0; i < nCount; ++i) {
        for (int j = 0; j < nCount; ++j) {
            if (((i & 1) == 0) && ((j & 1) == 0))
                continue;
            float v[3];
            v[0] = fArg3 + (float)j * fStep - fArg12;
            v[1] = fArg4;
            v[2] = fArg5 + (float)i * fStep - fArg12;
            Vector3_Push(pVertices, v);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00d554f0  four-corner sampler
// ---------------------------------------------------------------------------
// @ 0x00d554f0
void SpaceTurret_SampleCorners(uint32_t nCount, cVector3Array* pVertices,
                               float fArg3, float fArg4, float fArg5, float fArg6,
                               float fArg7, float fArg8, float fArg9, float fArg10,
                               float fArg11, float fArg12)
{
    pVertices->Clear();
    float v[3];
    v[0] = fArg3;
    v[1] = fArg4;
    v[2] = fArg5;
    Vector3_Push(pVertices, v);
    if ((int)nCount < 4)
        return;
    v[0] = fArg3 + fArg9;
    v[1] = fArg4 + fArg10;
    v[2] = fArg5 + fArg11;
    Vector3_Push(pVertices, v);
    v[0] = fArg3 + fArg12;
    v[1] = fArg4 + fArg12;
    v[2] = fArg5 + fArg12;
    Vector3_Push(pVertices, v);
    v[0] = fArg6;
    v[1] = fArg7;
    v[2] = fArg8;
    Vector3_Push(pVertices, v);
}
