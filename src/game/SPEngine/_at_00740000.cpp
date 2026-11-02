// src/game/SPEngine/_at_00740000.cpp -- migrated from slice(s) s00742b30 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00740000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cModelInstance.h"
#include "rw/graphics/EmbeddedState.h"
#include <intrin.h>
#include <new>
#include <math.h>

// @ 0x00743910
uint8_t __cdecl FlagsNotBit0(int param_1)
{
    uint8_t v = *(uint8_t*)(param_1 + 4);
    return (uint8_t)(~v) & 1;
}

// @ 0x00743920
int __cdecl CompareFloatAt10(int param_1, int param_2)
{
    return *(float*)(param_1 + 0x10) > *(float*)(param_2 + 0x10);
}
