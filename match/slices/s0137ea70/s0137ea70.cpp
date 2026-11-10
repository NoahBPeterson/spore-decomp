// Slice s0137ea70: cube of a global float written into the 0x016b39cc global.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

extern float g_f_015a7b98;   // 0x015a7b98
extern float g_f_016b39cc;   // 0x016b39cc

// @ 0x0137ea70
void FUN_0137ea70()
{
    float v = g_f_015a7b98;
    g_f_016b39cc = v * v * v;
}
