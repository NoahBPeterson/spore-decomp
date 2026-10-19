// src/game/SPTerrain/SPTerrainSystem.cpp -- migrated from slice(s) s00fc10d0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00fc10d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl SP_ModelManager();
char  __cdecl FUN_0075e620_dummy();
void  __cdecl FUN_00f67ff0_dummy();
void  __cdecl FUN_00f7be60();
void  __cdecl FUN_00f580f0();
void  __cdecl FUN_00f61a70();
void  __cdecl FUN_00f52b70(int, const char*);
void  __cdecl FUN_00f58230(int, void*);
void  __cdecl FUN_00aa7fa0(int, void*);
void __cdecl FUN_00fc5480();
void __cdecl FUN_00f4b690();
// ---- items of slice s00fc10d0 end

// @ 0x00fc19a0
int __cdecl FUN_00fc19a0(void)
{
    FUN_00f7be60();
    FUN_00f580f0();
    FUN_00f61a70();
    FUN_00f52b70(3, "coriolis");
    FUN_00f58230(3, (void*)FUN_00fc5480);
    FUN_00aa7fa0(6, (void*)FUN_00f4b690);
    return 1;
}

// @ 0x00fc1ba0
void __fastcall FUN_00fc1ba0(int self)
{
    if (FUN_0075e620_dummy()) {
        if (SP_ModelManager()) {
            int* m = (int*)SP_ModelManager();
            int* r = (int*)(*(int(__cdecl**)(void*, int))(*(void**)((char*)*(void**)m + 0x1c)))(m, 0x3fbae24);
            (*(void(__cdecl**)(void*, int))(*(void**)((char*)*(void**)r + 0x154)))(r, *(int*)(self + 0x18));
        }
    }
    if (*(int*)(self + 0xc) != 0) FUN_00f67ff0_dummy();
}

// @ 0x00fc1c70
int __fastcall FUN_00fc1c70(int self)
{
    (void)self;
    return 1;
}

// @ 0x00fc1e40
int __fastcall FUN_00fc1e40(int self)
{
    (void)self;
    return 1;
}
