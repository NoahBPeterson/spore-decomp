// Slice s00d6ddd0: creature "leave MATE_LEAD" helper -- notifies the entity
// through vtable slot 0x84 and then clears the behaviour tree state.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct Obj_00d6ddd0;
struct Bt_00d6ddd0;

struct Vtbl_00d6ddd0 {
    char pad_00[0x84];                          // +0x00 .. +0x83
    void (__thiscall* fn_84)(Obj_00d6ddd0*, int, int, int);   // +0x84
};

struct Obj_00d6ddd0 {
    Vtbl_00d6ddd0*  vtbl;                       // +0x000
    char            pad_04[0xb4c - 0x04];       // +0x004 .. +0xb4b
    Bt_00d6ddd0*    mBehavior;                  // +0xb4c
};

struct Bt_00d6ddd0 {
    void FUN_00bcb430();                        // 0x00bcb430
};

// @ 0x00d6ddd0
void __cdecl FUN_00d6ddd0(Obj_00d6ddd0* obj)
{
    obj->vtbl->fn_84(obj, 0, 0, 0);
    obj->mBehavior->FUN_00bcb430();
}