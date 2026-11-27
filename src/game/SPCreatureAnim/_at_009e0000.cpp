// src/game/SPCreatureAnim/_at_009e0000.cpp -- migrated from slice(s) s009e5070 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/_at_009e0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/gait_record_static_data.h"

// @ 0x009e5c00
float FastInvSqrt(float x)
{    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf * x * x);
    return x;
}
