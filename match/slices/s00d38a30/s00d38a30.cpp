// @ 0x00d38a30
// match/slices/s00d38a30/s00d38a30.cpp
// Object file: SPGonzago/SPCreatureBase.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
//
// 0x00d38a30 takes a mode (0..9) and a creature, reads the creature's
// forage-radius source (getter 0x00c0c1a0 = [this+0xe84]), takes the float at
// source+0x358, clamps it to at least 0 (falling back to _HK_REAL_ONE), then
// scales it by one of the small global factor table entries at
// 0x01582e90..0x01582eac.  Mode 0..2 return the radius unchanged, mode 9
// returns the flat 20.0f factor, anything else returns 1.0f.

#include "game/types.h"

// ---- float globals read from absolute addresses (no symbols in the image) ----
extern float g_1485720;   // 0x01485720  _HK_REAL_ONE = 1.0f
extern float g_1582e90;   // 0x01582e90  10.0f
extern float g_1582e94;   // 0x01582e94  50.0f
extern float g_1582e98;   // 0x01582e98  10.0f
extern float g_1582e9c;   // 0x01582e9c   1.0f
extern float g_1582ea0;   // 0x01582ea0   1.5f
extern float g_1582ea4;   // 0x01582ea4   3.0f
extern float g_1582eac;   // 0x01582eac  20.0f

// Local stub for the forage-radius source object: only the float the retail
// code reads at +0x358 is needed.
struct cForageRadiusSource {
    char  mPad_0000[0x358];
    float mRadius;                                        // +0x358
};

// Local stub for the creature side: 0x00c0c1a0 is the plain (non-virtual)
// getter returning the source pointer stored at +0xe84.
struct cSPCreatureBase {
    char mPad_0000[0xe84];
    cForageRadiusSource* GetForageRadiusSource();          // 0x00c0c1a0
};

float __cdecl FUN_00d38a30(int mode, cSPCreatureBase* creature)
{
    float radius = g_1485720;

    if (creature->GetForageRadiusSource() != 0) {
        radius = creature->GetForageRadiusSource()->mRadius;
        if (radius < 0.0f)
            radius = g_1485720;
    }

    switch (mode) {
    case 0:
    case 1:
    case 2:
        return radius;
    case 3:
        return g_1582e90 * radius;
    case 4:
        return g_1582e94 * radius;
    case 5:
        return g_1582e98 * radius;
    case 6:
        return g_1582e9c * radius;
    case 7:
        return g_1582ea0 * radius;
    case 8:
        return g_1582ea4 * radius;
    case 9:
        return g_1582eac;
    default:
        return 1.0f;
    }
}
