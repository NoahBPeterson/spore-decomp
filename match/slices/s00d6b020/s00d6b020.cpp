// Slice s00d6b020 -- SP::FLEE_Tick (0x00d6b020, ~6703 bytes, /O2, __cdecl).
// The creature "flee" behaviour tick: 8 args (creature, 5 scalars/flags, an int* state
// block, and a float), returns int. ~785 decompiled lines organised as a state switch
// on *param_6 (which is written back at the end of each arm).
//
// PARTIAL: the entry guards and the first two state arms are reconstructed; the large
// movement/planet-position arms and the final message dispatch are omitted.
//
// Card: work/match/scratch_s00d0e170_card_0x00d6b020.txt
#include "types.h"

namespace SP {
class cSPCreatureBase;
int FLEE_Tick(cSPCreatureBase* param_1, int param_2, int param_3,
              unsigned param_4, unsigned param_5, int* param_6,
              int param_7, float param_8);
}

extern void* FUN_00c0ee60();
extern void* cSPCreatureBase_GetTargetAsCreature(void* self);
extern int   FUN_00d99470(void* target);
extern char  FUN_00c0c130();
extern void  FUN_00bc97f0(int a, int b, float c, void* target);
extern void  FUN_00d51660(int v);
extern char  cSPDramaManager_IsDramaEventActive();
extern void  FUN_00c0d0c0(int v, int* state);

namespace {
template <class T> T& at(void* p, unsigned off) { return *reinterpret_cast<T*>(reinterpret_cast<char*>(p) + off); }
}

// @ 0x00d6b020
int SP::FLEE_Tick(SP::cSPCreatureBase* param_1, int param_2, int param_3,
                  unsigned param_4, unsigned param_5, int* param_6,
                  int param_7, float param_8)
{
    (void)param_2; (void)param_3; (void)param_4; (void)param_7; (void)param_8;
    int* self = (int*)FUN_00c0ee60();
    if (self == 0)
        return 0;

    int* target = (int*)cSPCreatureBase_GetTargetAsCreature(param_1);
    if (target != 0) {
        if (FUN_00d99470(target) == 0)
            return 0;
        if (FUN_00c0c130() != 0) {
            FUN_00bc97f0(0x1000000, 0, 10.0f, target);
            return 0;
        }
    }

    float dramaFlag = (float)(param_5 & 1);
    if (dramaFlag != 0.0f) {
        FUN_00d51660(3);
        if (cSPDramaManager_IsDramaEventActive() == 0)
            return 0;
    }

    // ... omitted: state switch on *param_6 (arms 0..6) with the creature movement /
    //     planet-surface projection, plus the trailing FUN_00c0d0c0(2,state) dispatch.
    FUN_00c0d0c0(2, param_6);
    return 1;
}
