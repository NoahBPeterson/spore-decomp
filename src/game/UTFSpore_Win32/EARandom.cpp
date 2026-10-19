// src/game/UTFSpore_Win32/EARandom.cpp -- migrated from slice(s) s00a68140, s00936090 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EARandom.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Thread/Mutex.h"
#include "EA/SharedLibrary.h"
#include "EA/SharedLibraryRegistry.h"

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" unsigned __int64 __rdtsc(void);

// @ 0x00936090
void EA::Random::RandomLinearCongruential::SetSeed(unsigned int seed)
{
    if (seed == 0xffffffff || seed == 0)
        seed = (uint32_t)__rdtsc();
    mnSeed = seed;
}

// @ 0x009360b0
unsigned int EA::Random::RandomLinearCongruential::RandomUint32Uniform()
{
    uint64_t v = (uint64_t)mnSeed * 0x41c64e6d + 0x3039;
    mnSeed = (uint32_t)v;
    return v >> 16;
}

// @ 0x009360d0
double EA::Random::RandomLinearCongruential::RandomDoubleUniform()
{
    if (mnSeed == 0)
        mnSeed = (uint32_t)__rdtsc();
    uint32_t v = mnSeed * 0x278dde6d;
    mnSeed = v;
    float f = (float)(int)v * 2.3283064e-10f + 0.5f;
    if (f >= 1.0f)
        return 0.0f;
    return f;
}

// @ 0x00a68fb0
unsigned int EA::Random::RandomLinearCongruential::RandomUint32Uniform(unsigned int range)
{
    uint64_t l = (uint64_t)mnSeed * 0x41c64e6dULL + 0x3039;
    mnSeed = (uint32_t)l;
    uint32_t u = (uint32_t)(l >> 16);
    return (uint32_t)(((uint64_t)u * range) >> 32);
}
