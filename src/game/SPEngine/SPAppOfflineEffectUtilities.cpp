// src/game/SPEngine/SPAppOfflineEffectUtilities.cpp -- migrated from slice(s) s007da2d0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppOfflineEffectUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Swarm/cTransform.h"

// ---- items of slice s007da2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RandomLinearCongruential {
    void SetSeed(int);                       // 0x00936090
    uint32_t RandomUint32Uniform();          // 0x009360b0
};
// ---- items of slice s007da2d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern RandomLinearCongruential g_sRandom;

// @ 0x007dade0
namespace SP {
void SetEffectSeed(unsigned int seed)
{
    if (seed == 0 || seed == -1)
        seed = 0xdeadbeef;
    g_sRandom.SetSeed(seed);
    g_sRandom.RandomUint32Uniform();
    g_sRandom.RandomUint32Uniform();
    g_sRandom.RandomUint32Uniform();
}
}  // namespace SP
