// src/game/SPGonzago/_at_01320000.cpp -- migrated from slice(s) s0132ea70 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01320000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s0132ea70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef int                i32;
struct cRbtreeSentinel;
void __cdecl atexit_external(void* fn);  // 0x011e07ef
struct cRbtreeSentinel {
    void* mpSelf;                       // 0x00
    void* mpNext;                       // 0x04
    u32   mField08;                     // 0x08
    union {
        u32 mField0c;                   // 0x0c
        u8  mField0cB;                  // 0x0c
    };
    void* mpField10;                    // 0x10
    u8    mPad14[0x1c - 0x14];          // 0x14
};
// ---- items of slice s0132ea70 end

// @ 0x0132ff90
void __cdecl InitRbtreeSentinels()
{
    cRbtreeSentinel* node = (cRbtreeSentinel*)0x0168caf4;
    i32 i = 2;
    do {
        node->mField0c = 0;
        node->mpSelf = node;
        node->mpNext = node;
        node->mField08 = 0;
        node->mField0cB = 0;
        node->mpField10 = 0;
        node += 1;
    } while (--i >= 0);
    atexit_external((void*)0x013c33a0);
}
