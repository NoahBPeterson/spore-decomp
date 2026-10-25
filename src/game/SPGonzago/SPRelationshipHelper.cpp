// src/game/SPGonzago/SPRelationshipHelper.cpp -- migrated from slice(s) s00ff4d50 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPRelationshipHelper.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlayer.h"
#include "SP/cTribe.h"
#include "SP/cDataSerializationInfo.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPropertyList.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s00ff4d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void* (__thiscall *FnVp1i)(void*, int);
typedef int   (__thiscall *FnVp0i)(void*);
struct CNounManagerA {
    int __thiscall GetPlayerEmpireOrMinus1();   // 0x00b1f9d0
};
void* __cdecl FUN_00b3d300();                   // 0x00b3d300  SP::NounManager
struct CObjBef8e0 { void* __thiscall AsReference(); };   // 0x00bef8e0
struct CObjC8e7e0 { void* __thiscall AsReference(); };   // 0x00c8e7e0
struct CObjBD9BF0 { void* __thiscall GetCivilization(); }; // 0x00bd9bf0
// ---- items of slice s00ff4d50 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl FUN_00ff51f0(void* param_1, float param_2, float param_3);  // 0x00ff51f0 (stays in the slice: not this object's)

// @ 0x00ff5270
void __cdecl SP_DoCommunityReaction(int* param_1, float param_2, float param_3)
{
    CNounManagerA* mgr = (CNounManagerA*)FUN_00b3d300();
    int empire = mgr->GetPlayerEmpireOrMinus1();
    if (((FnVp0i)((VObj*)param_1)->vt[0x4c / 4])(param_1) == empire)
        return;

    CObjBef8e0* a = (CObjBef8e0*)((FnVp1i)((VObj*)param_1)->vt[0x0c / 4])(param_1, 0x901f1362);
    CObjC8e7e0* b = (CObjC8e7e0*)((FnVp1i)((VObj*)param_1)->vt[0x0c / 4])(param_1, 0x4f396a66);
    CObjBD9BF0* c = (CObjBD9BF0*)((FnVp1i)((VObj*)param_1)->vt[0x0c / 4])(param_1, 0xee9b2232);

    void* r = 0;   // kept in ecx
    if (a != 0)
        r = a->AsReference();
    if (b != 0)
        r = b->AsReference();
    if (c != 0)
        r = ((CObjBef8e0*)c->GetCivilization())->AsReference();

    if (param_2 != 0.0f)
        FUN_00ff51f0(r, param_2, param_3);
}
