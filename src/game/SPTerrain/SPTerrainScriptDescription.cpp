// src/game/SPTerrain/SPTerrainScriptDescription.cpp -- migrated from slice(s) s00f94660 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainScriptDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __fastcall FUN_0083c800(void*);        // 0x0083c800  cCommandBase ctor (thiscall)

// ---- items of slice s00f94660 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void  (__thiscall *FnVVV)(void*, void*, void*);
extern "C" void* FUN_00f473a0(uint32_t, const char*, int, int, int, int); // 0x00f473a0  EAAllocate
extern "C" void* __fastcall FUN_0083c800(void*);        // 0x0083c800  cCommandBase ctor (thiscall)
// ---- items of slice s00f94660 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* FUN_00f473a0(uint32_t, const char*, int, int, int, int); // 0x00f473a0  EAAllocate

// @ 0x00f94d00
extern "C" char g_14902a0[];     // 0x014902a0  vtable of the terrain-script command
extern "C" void* g_15b0fec;      // 0x015b0fec  command name key
struct Parser_s00f94d00 {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14();
    virtual void AddCommand(void* key, void* cmd);
};
extern "C" void FUN_00f94d00(void* script)
{
    void* cmd = FUN_00f473a0(0x10, "ArgScript/GroupTerrainScript", 0, 0, 0, 0);
    if (cmd) {
        FUN_0083c800(cmd);
        *(void**)cmd = g_14902a0;
    } else {
        cmd = 0;
    }
    ((Parser_s00f94d00*)script)->AddCommand(g_15b0fec, cmd);
}
