// src/game/UTFSpore_Win32/EAVariant.cpp -- migrated from slice(s) s0093d740 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAVariant.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"

// ---- items of slice s0093d740 begin (TODO(rewrite): local stubs, replace by canonical classes)
using EA::Variant;
// ---- items of slice s0093d740 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void* g_fn154eb48;                       // Variant value destructor/callback

// @ 0x0093db80
void EA::Variant::Destruct(bool bFree)
{
    if (mFlags & 4) {
        ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0);
    }
    if (bFree != 0 && (mFlags & 2) == 0) {
        mTypeId = 0;
        mFlags = 0;
    }
}
