// src/game/SPGonzago/InteractionTarget.cpp -- migrated from slice(s) s00ac0180 by tools/migrate/rewrite.py
// Object file: SPGonzago/InteractionTarget.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cInteractionTarget.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl operator_delete_array(void*);     // 0xf47380

// ---- items of slice s00ac0180 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete_array(void*);     // 0xf47380
#define VTBL_01459be8  ((void*)0x1459be8)
struct VecDtor {
    void dtor();                                    // 0xae6970
};
struct cInteractionTarget {
    void*  mpVftable;                               // +0x00
    void*  mpBegin;                                 // +0x04
    void*  mpEnd;                                   // +0x08
    void*  mpCapacity;                              // +0x0c

    cInteractionTarget* ctor();                     // 0xac03d0
    void   FUN_00ac0450();                          // 0xac0450
    void   FUN_00ac0520();                          // 0xac0520
    cInteractionTarget* FUN_00ac0540(char free);    // 0xac0540
};
// ---- items of slice s00ac0180 end

// @ 0x00ac0540
cInteractionTarget* cInteractionTarget::FUN_00ac0540(char free)
{
    mpVftable = VTBL_01459be8;
    FUN_00ac0450();
    ((VecDtor*)((char*)this + 4))->dtor();
    if (free & 1)
        operator_delete_array(this);
    return this;
}
