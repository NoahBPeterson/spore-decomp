// Slice s0137ea50: square / cube a global float into other globals.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast /GS-
#include "types.h"

extern float g_15a7b98;   // 0x015a7b98
extern float g_16b39c8;   // 0x016b39c8
extern float g_16b39cc;   // 0x016b39cc

// @ 0x0137ea50
void FUN_0137ea50()
{
    float v = g_15a7b98;
    g_16b39c8 = v * v;
}

// @ 0x0137ea70
void FUN_0137ea70()
{
    float v = g_15a7b98;
    g_16b39cc = v * v * v;
}

extern float g_15a7b88;   // 0x015a7b88
extern float g_140f334;   // 0x0140f334
extern float g_140f32c;   // 0x0140f32c
extern float g_16b39d0;   // 0x016b39d0

// @ 0x0137ea90
void FUN_0137ea90()
{
    g_16b39d0 = g_140f32c / (g_16b39cc * g_15a7b88 * g_140f334);
}
