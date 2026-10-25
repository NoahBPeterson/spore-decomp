// src/game/SPGonzago/SPCityCivAttackBehaviors.cpp -- migrated from slice(s) s00d54ce0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityCivAttackBehaviors.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCombatant.h"
#include "SP/cInteraction.h"
#include "SP/cInteractionAgent.h"
#include "SP/cSPTimer.h"

// unnamed retail callees and globals (address in the comment)
extern float gsSpaceHelixStep;                                  // 0x0169ebf0
#include <math.h>

// ---- items of slice s00d54ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gsSpaceHelixStep;                                  // 0x0169ebf0
struct cVector3Array {
    float* mpBegin;                                             // 0x00
    float* mpEnd;                                               // 0x04
    float* mpCapacity;                                          // 0x08

    void Clear() { mpEnd = mpBegin; }
};
void Vector3_Push(cVector3Array*, const float*);                // 0x004b5ad0
void Vector3Array_Reserve(uint32_t nCount);                     // 0x00473890
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
struct cTurretStateTree {
    uint32_t mnUnk00;                                           // 0x00
    cRBNodeBase mAnchor;                                        // 0x04
    uint32_t mnSize;                                            // 0x14
    uint32_t mnUnk18;                                           // 0x18

    void NukeSubtree(cRBNodeBase* pNode);                       // 0x00d54ac0
};
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
// ---- items of slice s00d54ce0 end

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

// @ 0x00d55060
void SpaceTurret_SampleHelix(int nSamples, cVector3Array* pVertices, float fArg3, float fArg4, float fArg5, float fArg6, float fArg7, float fArg8, float fArg9, float fArg10, float fArg11, float fArg12)
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

// @ 0x00d554f0
void SpaceTurret_SampleCorners(uint32_t nCount, cVector3Array* pVertices, float fArg3, float fArg4, float fArg5, float fArg6, float fArg7, float fArg8, float fArg9, float fArg10, float fArg11, float fArg12)
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
