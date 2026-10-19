// src/game/SPEngine/blendshape.cpp -- migrated from slice(s) s006c0db0 by tools/migrate/rewrite.py
// Object file: SPEngine/blendshape.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s006c0db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
extern void* sub_11e22c0(u32);                             // ArenaTypeRegGetType
// ---- items of slice s006c0db0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void* sub_11e22c0(u32);                             // ArenaTypeRegGetType

// @ 0x006c12a0
void RegisterArenaReadCallbacks()
{
    u32* t = (u32*)sub_11e22c0(0x200af);
    t[1] = 0;
    t[2] = 0;
    t[3] = 0x6c1180;
    t[4] = 0;
}
