// src/game/SPGonzago/SPMissionColonize.cpp -- migrated from slice(s) s00c4dbf0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionColonize.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int   __cdecl FUN_0041e920();
extern "C" int   __cdecl FUN_0041ea00();
#pragma warning(disable : 4100)

// ---- items of slice s00c4dbf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
extern "C" int   __cdecl FUN_0041e920();
extern "C" int   __cdecl FUN_0041ea00();
// ---- items of slice s00c4dbf0 end

// @ 0x00c4e390
void __fastcall FUN_00c4e390(void* ecx_this, void* edx, u8* pb, u32* pu, int* pflag)
{
    // pb = *this+0x1f4? no: caller passes (this+0x1f4, &local, this+0x1f5) reversed; here pb/pu/pflag
    // map to the three property reads in order.
    void* pl = *(void**)((char*)ecx_this + 0x180);
    if (pl) {
        void* prop = 0;
        char ok = (*(char(__thiscall**)(void*, u32, void**))(*(char**)pl + 0x24))(pl, 0x36758b07u, &prop);
        if (ok && *(short*)((char*)prop + 0x12) == 1) {
            u8* v = (u8*)FUN_0041e920();
            *pb = *v;
        }
    }
    pl = *(void**)((char*)ecx_this + 0x180);
    if (pl) {
        void* prop = 0;
        char ok = (*(char(__thiscall**)(void*, u32, void**))(*(char**)pl + 0x24))(pl, 0x1f707861u, &prop);
        if (ok && *(short*)((char*)prop + 0x12) == 10) {
            u32* v = (u32*)FUN_0041ea00();
            *pu = *v;
        }
    }
    pl = *(void**)((char*)ecx_this + 0x180);
    if (pl) {
        void* prop = 0;
        char ok = (*(char(__thiscall**)(void*, u32, void**))(*(char**)pl + 0x24))(pl, 0xf924ebf9u, &prop);
        if (ok && *(short*)((char*)prop + 0x12) == 1) {
            u8* v = (u8*)FUN_0041e920();
            *pflag = *v;
        }
    }
}
