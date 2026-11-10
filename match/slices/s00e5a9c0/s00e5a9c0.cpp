// Slice s00e5a9c0 -- SP cell-game marker helper: box-size multiplier squared times the height blend
// of the marker's three heights against that multiplier.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#define kBoxScale 0.85f
#define kHeightScale 2.25f

struct cMarker {          // 0x4c-stride spawn marker record
    unsigned char pad00[0x2c];
    float f2c;            // +0x2c
    float f30;            // +0x30
    float f34;            // +0x34
    float f38;            // +0x38
};

float sGetBoxSizeMultiplier2(int level, int flags);   // 0x00e51ff0, cdecl, float in st0
float HeightBlend(float h, float low, float high, float seaLevel);   // 0x00e5a910

// @ 0x00e5a9c0
float FUN_00e5a9c0(cMarker* m, int level, int flags)
{
    float mul = sGetBoxSizeMultiplier2(level, flags) * kBoxScale;
    float r = HeightBlend(m->f2c, m->f30, m->f34, m->f38);
    return r * (mul * mul * kHeightScale);
}
