// src/game/SPGonzago/SPBehaviorTreeHelpers.cpp -- migrated from slice(s) s00d990a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPBehaviorTreeHelpers.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
struct Vector3 {
    float x, y, z;
};
extern Vector3 gStimulusDefaultVec;
struct behavior_stimuli {
    int32_t mStimulusID;                                              // +0x00
    int32_t mField04;                                                 // +0x04
    int32_t mDuration;                                                // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24

    behavior_stimuli& GetAny();                                       // 0x00d997e0
};
// ---- items of slice s00d990a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vector3 gStimulusDefaultVec;

// @ 0x00d997e0
behavior_stimuli& behavior_stimuli::GetAny()
{
    mStimulusID = 0;
    mField04 = 0;
    mDuration = 0;
    mOffset.x = gStimulusDefaultVec.x;
    mOffset.y = gStimulusDefaultVec.y;
    mOffset.z = gStimulusDefaultVec.z;
    mField18 = 0;
    mField1c = 0;
    mField20 = 0;
    mf24 = 0.0f;
    return *this;
}
