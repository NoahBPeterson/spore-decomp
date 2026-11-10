// Slice s00e5a910: SP cell-game height clamp helper. /O2, SSE (/arch:SSE /fp:fast).
#include "game/types.h"

extern float kFloorLevel;   // @ 0x013eb1bc
extern int* gspCellGame;    // @ 0x016b3c04
struct cCellGame {
    char pad00[0x7c];
    int mHeightMode;        // +0x7c
};

// @ 0x00e5a910
// Behavioural reconstruction of the guard ladder and the three-way mode switch:
//   a2/a3/a4 (xmm1/xmm3/xmm2) each "!=" kFloorLevel (unordered counts as different),
//   and a1 (xmm4) tested the same way, loading a1 only on the two paths that need it.
//   all four equal -> 1.0f; otherwise a1 == kFloorLevel is stored back as 0.0f, then
//   mHeightMode picks: 0 -> a2 (else a1), 1 -> a3 (else a1), 2 -> a4 (else a1), else a1.
// Bytes differ: retail holds the arguments in xmm1..xmm4 with ucomiss/lahf/test ah,0x44,
// while this TU's float arguments stay in x87. See nonmatching.txt.
float HeightBlend(float a1, float a2, float a3, float a4)
{
    const float floorLevel = kFloorLevel;
    if (a2 != floorLevel && a3 != floorLevel && a4 != floorLevel) {
        if (a1 == floorLevel)
            return 1.0f;
    } else if (a1 == floorLevel) {
        a1 = 0.0f;
    }

    switch (((cCellGame*)(gspCellGame + 0x5190 / 4))->mHeightMode) {
    case 0:  return (a2 == floorLevel) ? a1 : a2;
    case 1:  return (a3 == floorLevel) ? a1 : a3;
    case 2:  return (a4 == floorLevel) ? a1 : a4;
    default: return a1;
    }
}
