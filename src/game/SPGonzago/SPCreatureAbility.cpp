// src/game/SPGonzago/SPCreatureAbility.cpp -- migrated from slice(s) s00d1df40 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureAbility.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCommunity.h"
#include "SP/cCity.h"
#include "SP/cSPCreatureBase.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern const float  gRealOne;          // 0x01485720 (_HK_REAL_ONE)
#include <math.h>
#include <wchar.h>

// ---- items of slice s00d1df40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct IVtbl {
    PV PV                                        // 0x00, 0x04
    virtual int   Slot8(int a);                  // 0x08
    virtual void* SlotC();                       // 0x0c
    PV8 PV4 PV2 PV                               // 0x10..0x48
    virtual int   Slot4c();                      // 0x4c
    PV16 PV8                                     // 0x50..0xac
    virtual int   SlotB0();                      // 0xb0  (count)
    virtual int   SlotB4(int i);                 // 0xb4  (element i)
    PV4 PV2 PV                                   // 0xb8..0xd0
    virtual char  SlotD4();                      // 0xd4
};
struct Elem {
    uint8_t pad00[4];
    float   mValue;                                    // +0x04
    uint8_t pad08[8];
};
struct FlagSetObj {
    uint8_t  pad00[0xbf8];
    uint32_t mFlags[12];                               // +0xbf8
    Elem*    mpElems;                                  // +0xc28
};
struct BabyRec {
    int32_t  mId;                                      // +0x00 (object +0x168)
    uint8_t  pad04[0x70 - 4];
    uint32_t mTag;                                     // +0x70 (object +0x1d8)
    uint32_t mIndex;                                   // +0x74 (object +0x1dc)
    uint8_t  pad78[0xac - 0x78];
};
struct TrainData {
    uint8_t pad00[0x168];
    BabyRec mRecs[1];                                  // +0x168 (stride 0xac)
};
struct TrainObj {
    uint8_t  pad00[0x14];
    void*    mpAgent;                                  // +0x14
    uint8_t  pad18[0x6c - 0x18];
    uint32_t mFlags6c;                                 // +0x6c
};
struct AgentLink {
    uint8_t pad00[0xb4c];
    void*   mpData;                                    // +0xb4c
};
void* __cdecl FUN_00d51660();                       // 0x00d51660
extern const float  gRealOne;          // 0x01485720 (_HK_REAL_ONE)
// ---- items of slice s00d1df40 end

// @ 0x00d1e5c0
int __cdecl FUN_00d1e5c0(IVtbl* param_1, int param_2)
{
    int i = param_1->SlotB0() - 1;
    while (i >= 0) {
        if (param_1->SlotB4(i) == param_2)
            return i;
        --i;
    }
    return -1;
}

// @ 0x00d1e6c0
namespace SP {
bool AbilityIsBeingTaughtToBaby(int param_1)
{
    if (param_1 == -1)
        return false;
    TrainObj* o = (TrainObj*)FUN_00d51660();
    if (((o->mFlags6c >> 4) & 1u) == 0)
        return false;
    o = (TrainObj*)FUN_00d51660();
    AgentLink* a = (AgentLink*)o->mpAgent;
    if (a == 0)
        return false;
    TrainData* d = (TrainData*)a->mpData;
    if (d->mRecs[0].mTag != 0xb413edc5)
        return false;
    unsigned idx = d->mRecs[0].mIndex;
    return param_1 == d->mRecs[idx].mId;
}
}  // namespace SP

// @ 0x00d1e7f0
float __cdecl FUN_00d1e7f0(FlagSetObj* param_1, int param_2)
{
    int i = FUN_00d1e5c0((IVtbl*)param_1, param_2);
    int n = ((IVtbl*)param_1)->SlotB0();
    if (i >= 0 && i < n)
        return param_1->mpElems[i].mValue;
    return 0.0f;
}

// @ 0x00d1e8d0
bool __cdecl FUN_00d1e8d0(FlagSetObj* param_1, uint param_2)
{
    float f = param_1->mpElems[param_2].mValue;
    if (f == gRealOne)
        return false;
    if (param_2 >= 0x58)
        return false;
    uint mask = 1u << (param_2 & 0x1f);
    bool b = (param_1->mFlags[param_2 >> 5] & mask) != 0;
    if (b)
        return true;
    return false;
}
