// src/game/SPTerrain/SPTerrainTerraform.cpp -- migrated from slice(s) s00fc10d0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainTerraform.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// unnamed retail callees and globals that name local stubs (address in the comment)
extern float kLavaThreshold;

// @ 0x00fc1fd0
namespace SP {
unsigned int GetTerraformPlanetType(float f)
{
    if (f < 0.1f) return 2;
    if (f >= 0.1f && f < 0.4f) return 3;
    if (f >= 0.4f && f < 0.6f) return 1;
    if (f < 0.6f || kLavaThreshold <= f) return 4;
    return 5;
}
}  // namespace SP

// The original computes the whole falloff in x87 and takes the root with an inline fsqrt.
// cl only inlines sqrt under /fp:fast, which this module's flags do not use, so do the root
// with x87 directly (double keeps enough precision that the float result matches).
static inline double SqrtX87(double v)
{
    __asm fld v
    __asm fsqrt
    __asm fstp v
    return v;
}
// @ 0x00fc2040
float __cdecl FUN_00fc2040(float x, float y)
{
    double dx = (double)x - 0.5;
    double dy = (double)y - 0.5;
    float f = (float)(1.0 - SqrtX87(dy * dy + dx * dx) * (double)1.4142135f);
    float r = 0.0f;
    if (0.0f <= f) r = f;
    return r;
}
