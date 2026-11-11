// Slice s0129e2e0 -- identity matrix build (diagonal from one constant, zero
// elsewhere) copied to a global.
// MSVC 2008 /O2 with /arch:SSE2; cl 13.10 here (the movss fill order and the
// 'mov ecx,9; rep movsd' copy are cl 13.10 shapes).

#include "game/types.h"
#include <string.h>

// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /Isrc/game/include /arch:SSE2

struct Mat3 {
    float m[9];
};

float g_15f3be0;                // 0x015f3be0  the diagonal constant (1.0f)
unsigned g_15f3be4words[9];     // 0x015f3be4  destination matrix

// @ 0x0129e2e0
void FUN_0129e2e0()
{
    float  scale = g_15f3be0;
    Mat3   m;
    m.m[0] = scale;
    m.m[1] = 0.0f;
    m.m[2] = 0.0f;
    m.m[3] = 0.0f;
    m.m[4] = scale;
    m.m[5] = 0.0f;
    m.m[6] = 0.0f;
    m.m[7] = 0.0f;
    m.m[8] = scale;
    memcpy(g_15f3be4words, &m, 36);
}
