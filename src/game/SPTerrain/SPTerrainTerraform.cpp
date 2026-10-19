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

// @ 0x00fc2040
float __cdecl FUN_00fc2040(float x, float y)
{
    float f = 1.0f - sqrtf((y - 0.5f) * (y - 0.5f) + (x - 0.5f) * (x - 0.5f)) * 1.4142135f;
    float r = 0.0f;
    if (0.0f <= f) r = f;
    return r;
}
