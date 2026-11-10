// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// Play-fight callback. Returns false when the locomotive at +0xc0 is near its goal,
// or when stimulus 0x400 names a creature. Otherwise returns true.
#include "types.h"

class cLocomotiveObject {
public:
    bool IsNearGoal() const; // 0x00c42e20
};

struct cStimulusContext;

struct behavior_stimuli {
    cStimulusContext* Play(unsigned int lo, unsigned int hi); // 0x00bc96a0
};

struct cBehaviorTreeData {
    char mPad00[8];
    behavior_stimuli mStimuli; // +0x08
};

class cSPCreatureBase;

struct Creature {
    char mPad00[0xc0];
    cLocomotiveObject mLoco;              // +0xc0
    char mPadC1[0xb4c - 0xc1];
    cBehaviorTreeData* mpBTree;           // +0xb4c
};

cSPCreatureBase* GetStimulusCreature(cStimulusContext* context); // 0x00d99a10

// @ 0x00d6de50
bool __cdecl FUN_00d6de50(Creature* creature)
{
    if (creature->mLoco.IsNearGoal())
        return false;
    cStimulusContext* block = creature->mpBTree->mStimuli.Play(0x400, 0);
    if (block && GetStimulusCreature(block))
        return false;
    return true;
}
