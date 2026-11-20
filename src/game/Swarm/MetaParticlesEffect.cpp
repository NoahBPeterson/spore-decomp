// src/game/Swarm/MetaParticlesEffect.cpp -- migrated from slice(s) s01300280 by tools/migrate/rewrite.py
// Object file: Swarm/MetaParticlesEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1679034[];

#include "../include/game/types.h"
#include <intrin.h>

// ---- items of slice s01300280 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct TwoInts { int a, b; };
// ---- items of slice s01300280 end

// @ 0x0130fcc0
void init_1679034()
{
    TwoInts s;
    s.b = 0;
    _ReadWriteBarrier();
    s.a = 0x2903000;
    *(TwoInts*)g_1679034 = s;
}
