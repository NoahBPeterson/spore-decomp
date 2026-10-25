// src/game/SPGonzago/SPPosseSimulator.cpp -- migrated from slice(s) s00d522c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPosseSimulator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_00b3d300();                                 // 0xb3d300
extern "C" int*  __cdecl FUN_00b1f9c0();         // GetItemID (thiscall body)
extern "C" int*  __cdecl FUN_00b1fdb0();         // GetAvatar (thiscall body)
extern float     g_145c4ac;

// ---- items of slice s00d522c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d300();          // 0xb3d300
extern "C" int*  __cdecl FUN_00b1f9c0();         // GetItemID (thiscall body)
extern "C" int*  __cdecl FUN_00b1fdb0();         // GetAvatar (thiscall body)
extern float     g_145c4ac;
typedef char (__cdecl* Cmp)(int, int);
extern "C" void* __cdecl FUN_00b3d300();                                 // 0xb3d300
// ---- items of slice s00d522c0 end

// @ 0x00d52c90
extern "C" int __cdecl F52c90(int a, int b)
{
    return *(float*)(b + 8) > *(float*)(a + 8);
}

// @ 0x00d52cb0
void __cdecl F52cb0(int* arr, int start, int hole, int value, Cmp cmp)
{
    if (hole <= start) {
        arr[hole] = value;
        return;
    }
    int parent;
    do {
        parent = (hole - 1) >> 1;
        if (!cmp(arr[parent], value))
            break;
        arr[hole] = arr[parent];
        hole = parent;
    } while (start < parent);
    arr[hole] = value;
}

// @ 0x00d52df0
int __fastcall F52df0(void* self)
{
    void* m = FUN_00b3d300();
    int* v = ((int*(__thiscall*)(void*))FUN_00b1f9c0)(m);
    return ((v[1] - v[0]) >> 2) - *(int*)((char*)self + 0x1c);
}

// @ 0x00d52e10
int __fastcall F52e10(void* self)
{
    int result = 0;
    void* m = FUN_00b3d300();
    int r = ((int(__thiscall*)(void*))FUN_00b1fdb0)(m);
    if (r != 0) {
        int* p = (int*)((char*)self + 0x18);
        if (*(unsigned int*)((char*)self + 0x18) > 3)
            p = (int*)&g_145c4ac;
        result = *p;
    }
    return result;
}
