// src/game/UTFSpore_Win32/ImmediateModeEx.cpp -- migrated from slice(s) s00962ff0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ImmediateModeEx.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_011f5010(int*, int, int, int, int, int);  // 0x11f5010
extern void* g_pfnIndexBuffer;                                         // 0x16f4ae4

// ---- items of slice s00962ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResDesc { int a, b, c, d, e; };
extern "C" void __cdecl  FUN_011f51d0(ResDesc*, int, int, int, int);   // GetResourceDescriptor 0x11f51d0
extern "C" void* __cdecl FUN_011f5010(int*, int, int, int, int, int);  // 0x11f5010
extern void* g_pfnIndexBuffer;                                         // 0x16f4ae4
// ---- items of slice s00962ff0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void __cdecl  FUN_011f51d0(ResDesc*, int, int, int, int);   // GetResourceDescriptor 0x11f51d0

// @ 0x00963060
int __cdecl FUN_00963060(int p1, int p2, int p3, int p4, int p5, int p6)
{
    ResDesc desc;
    FUN_011f51d0(&desc, p2, p3, p4, p5);
    (void)p6;
    int r = ((int (__cdecl*)(int, int))g_pfnIndexBuffer)(desc.b, desc.c);
    if (r != 0) {
        int local[4];
        local[0] = r;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        return (int)FUN_011f5010(local, p2, p3, p4, p5, p6);
    }
    return 0;
}
