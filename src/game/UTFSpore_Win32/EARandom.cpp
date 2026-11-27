#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"

extern "C" unsigned __int64 __rdtsc(void);

// Linear congruential generator parameters (descriptive names; the values are
// the ones the original code uses).
static const uint32_t kSeedMultiplier = 0x41c64e6d;
static const uint32_t kSeedIncrement = 0x3039;
static const uint32_t kInvalidSeed = 0xffffffff;

// @ 0x00936090
void EA::Random::RandomLinearCongruential::SetSeed(unsigned int seed)
{
    if (seed == kInvalidSeed || seed == 0)
        seed = (uint32_t)__rdtsc();
    mnSeed = seed;
}

// @ 0x009360b0
unsigned int EA::Random::RandomLinearCongruential::RandomUint32Uniform()
{
    uint64_t product = (uint64_t)mnSeed * kSeedMultiplier + kSeedIncrement;
    mnSeed = (uint32_t)product;
    return product >> 16;
}

// @ 0x009360d0
double EA::Random::RandomLinearCongruential::RandomDoubleUniform()
{    extern const float g_143e8d4;
    extern const float g_1471064;
    if (mnSeed == 0)
        mnSeed = (uint32_t)__rdtsc();
    uint32_t v = mnSeed * 0x278dde6d;
    mnSeed = v;
    double d = (int)v;
    d *= g_143e8d4;
    d += g_1471064;
    if (d >= 1.0)
        return 0.0;
    return d;
}

// @ 0x00a68fb0
unsigned int EA::Random::RandomLinearCongruential::RandomUint32Uniform(unsigned int range)
{
    uint64_t product = (uint64_t)mnSeed * kSeedMultiplier + kSeedIncrement;
    mnSeed = (uint32_t)product;
    uint32_t high = (uint32_t)(product >> 16);
    return (uint32_t)(((uint64_t)high * range) >> 32);
}
