// src/game/SPGonzago/SPAdjectives.cpp -- migrated from slice(s) s005718f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAdjectives.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s005718f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x932e80
// ---- items of slice s005718f0 end

// @ 0x00571cf0
unsigned int SPIDFromName(char const * name)
{
    return FNVHash(name, 0x811c9dc5, 1);
}
