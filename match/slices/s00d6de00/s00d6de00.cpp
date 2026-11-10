// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// Play-fight callback. Walks to the noun from Get() at standard speed, then clears stimulus 0x400.
#include "types.h"

struct Vec3 {
    float x, y, z;
};

struct cNearNoun {
    const Vec3* GetPosition(); // 0x00c6acc0
};

struct behavior_stimuli {
    void ClearAll(unsigned int lo, unsigned int hi); // 0x00bc98f0
};

struct cBehaviorTreeData {
    char mPad00[8];
    behavior_stimuli mStimuli; // +0x08
};

// kStandardSpeed is cSPCreatureBase::eSpeedState value 2.
class cSPCreatureBase {
public:
    cNearNoun* Get(); // 0x00c04590
    void MoveToPointAtSpeed(int speed, const Vec3* pPos, float radius, float arrival); // 0x00c1c1d0

    char mPad00[0xb4c];
    cBehaviorTreeData* mpBTree; // +0xb4c
};

extern const float g_1470f1c; // 0x01470f1c, 2.0f

// @ 0x00d6de00
bool __cdecl FUN_00d6de00(cSPCreatureBase* creature)
{
    creature->MoveToPointAtSpeed(2, creature->Get()->GetPosition(), 1.0f, g_1470f1c);
    creature->mpBTree->mStimuli.ClearAll(0x400, 0);
    return true;
}
