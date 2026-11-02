// src/game/SPCreatureAnim/_at_009e0000.cpp -- migrated from slice(s) s009e5070 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/_at_009e0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/gait_record_static_data.h"

// @ 0x009e5c00
float FastInvSqrt(float x)
{
    float y = (float)(0x5f375a86 - (*(int*)&x >> 1));
    return (float)((double)y * (1.5 - (double)x * 0.5 * (double)y * (double)y));
}
