// src/game/SPEngine/SPGraphicsArenaUtils.cpp -- migrated from slice(s) s006c1cd0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsArenaUtils.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s006c1cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
struct PropertyList {
    void* vtbl;              // +0x00
    u32   field04;           // +0x04
    u32   f08, f0c, f10, f14, f18; // +0x08
    void* field1c;           // +0x1c
    PropertyList(void* p);
};
// ---- items of slice s006c1cd0 end

// @ 0x006c2240
PropertyList::PropertyList(void* p)
{
    vtbl = (void*)0x13ebcdc;
    field04 = 0;
    f08 = 0; f0c = 0; f10 = 0; f14 = 0; f18 = 0;
    vtbl = (void*)0x140a5bc;
    field1c = p;
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
    f18 = 0;
}

// @ 0x006c22b0
void* BakeResourceCtor(void* self, void* a, void* b, void* key, void* name)
{
    (void)a; (void)b; (void)key; (void)name;
    return self;
}
