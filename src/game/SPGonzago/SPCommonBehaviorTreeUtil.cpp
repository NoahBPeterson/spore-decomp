// src/game/SPGonzago/SPCommonBehaviorTreeUtil.cpp -- migrated from slice(s) s00d990a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCommonBehaviorTreeUtil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPVector3.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cActionCircle.h"
#include "SP/cAnimState.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpatialObject.h"
#include <math.h>

// ---- items of slice s00d990a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
struct Vector3 {
    float x, y, z;
};
class cCreatureStatus {
public:
    uint8_t mOpaque[0x75];
    bool mIsAlive;                                                    // +0x75
};
class cCreatureOwner {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual bool IsUnavailable();                                     // +0x2c
};
class cLocomotiveObject {
public:
    bool IsNearGoal();                                                // 0x00c42e20
    uint8_t mOpaque[0x60];
};
class cCombatant {
public:
    int32_t GetDamageState();                                         // 0x008e7f80 (reads +0x34)
    uint8_t mOpaque[0x15];                                            // +0x00 .. +0x14
};
class cAnimState {
public:
    uint8_t mPad00[8];
    float mfProgress;                                                 // +0x08
};
class cAnimationPlayer {
public:
    cAnimState* Play(uint32_t nAnimID, uint32_t nFlags);              // 0x00bc96a0
};
class cAnimation {
public:
    uint8_t mPad00[8];
    cAnimationPlayer mPlayer;                                         // +0x08
};
class cActionSlot {
public:
    uint32_t mField00;                                                // +0x00
    void* mpField04;                                                  // +0x04
    uint8_t mPad08[4];
    Vector3 mPos;                                                     // +0x0c
};
class cActionCircle {
public:
    uint8_t mPad00[0x14];
    Vector3 mPos;                                                     // +0x14
    uint8_t mPad20[0x30];                                             // +0x20 .. +0x4f
    cActionSlot* mpBegin;                                             // +0x50
    cActionSlot* mpEnd;                                               // +0x54
    uint8_t mPad58[0x0c];                                             // +0x58 .. +0x63
    cActionSlot* SlotAt(uint32_t nIndex);                             // 0x00af9ff0
};
class cCreatureTree {
public:
    uint8_t mPad000[0x220];
    cActionCircle* mpCircles;                                         // +0x220
};
class cSPCreatureBase {
public:
    VSLOT(0) VSLOT(1)
    virtual cCreatureStatus* GetStatus();                             // +0x08
    virtual cCreatureOwner* GetOwner();                               // +0x0c
    VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual uint32_t GetTypeID();                                     // +0x20
    VSLOT(9) VSLOT(10)
    virtual bool IsUnavailable();                                     // +0x2c

    int32_t GetDamageState();                                         // 0x008e7f80 (reads +0x34)
    bool AnimationFinished(int32_t nFlags);                           // 0x00c123f0
    void PlayAnimation(uint32_t nAnimID, int32_t nLoops, int32_t nFlags);  // 0x00c12190

    uint8_t mPad04[0x30];                                             // +0x04 .. +0x33
    int32_t mnDamageState;                                            // +0x34
    float mf38;                                                       // +0x38
    uint8_t mPad3c[0x84];                                             // +0x3c .. +0xbf
    cLocomotiveObject mLocomotive;                                    // +0xc0
    cCombatant mCombatant;                                            // +0x120
    bool mB135;                                                       // +0x135
    uint8_t mPad136[0x472];                                           // +0x136 .. +0x5a7
    uint8_t mB5a8;                                                    // +0x5a8
    uint8_t mPad5a9[0x5a3];                                           // +0x5a9 .. +0xb4b
    cAnimation* mB4c;                                                 // +0xb4c
    uint8_t mPadB50[8];                                               // +0xb50 .. +0xb57
    uint8_t mB58;                                                     // +0xb58 (flags)
    uint8_t mPadB59[5];                                               // +0xb59 .. +0xb5d
    bool mB5e;                                                        // +0xb5e
    uint8_t mPadB5f[0x459];                                           // +0xb5f .. +0xfb7
    cCreatureTree* mFB8;                                              // +0xfb8
};
class cStimulusSource {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual cSPCreatureBase* FindObject(uint32_t nStimulusID);        // +0x0c
};
struct cStimulusContext {
    uint8_t mPad00[0x2c];
    cStimulusSource* mpSource;                                        // +0x2c
};
// ---- items of slice s00d990a0 end

// @ 0x00d998d0
int32_t QueryStimulus(cStimulusContext* pContext, uint32_t nStimulusID)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0)
            return (int32_t)pSource->FindObject(nStimulusID);
    }
    return 0;
}

// @ 0x00d99980
cSPCreatureBase* GetAnimalFromStimulus(cStimulusContext* pContext)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0) {
            cSPCreatureBase* pCreature = pSource->FindObject(0xd0036e08);
            if (pCreature != 0) {
                if (pCreature->mB135 && !pCreature->IsUnavailable() &&
                    (pCreature->mB58 & 4) == 0)
                    return pCreature;
            }
        }
    }
    return 0;
}

// @ 0x00d999d0
cSPCreatureBase* WatchMemoryBlock(cStimulusContext* pContext)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0) {
            cSPCreatureBase* pCreature = pSource->FindObject(0xce9f6639);
            if (pCreature != 0) {
                if (pCreature->mB135 && !pCreature->IsUnavailable())
                    return pCreature;
            }
        }
    }
    return 0;
}
