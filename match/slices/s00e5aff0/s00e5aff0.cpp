// Slice s00e5aff0 -- SPGonzago cell-game direction helper (float, cdecl).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" double __cdecl sin(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sin, sqrt)

// ---- globals ---------------------------------------------------------------
extern float g_16b3c28;                        // 0x016b3c28
extern float g_16b3c2c;                        // 0x016b3c2c
extern float g_16b3c30;                        // 0x016b3c30
extern float g_15a7c20;                        // 0x015a7c20 (half pi threshold)
extern float g_15a7c24;                        // 0x015a7c24 (half pi)

// @ 0x00e5aff0
void __cdecl FUN_00e5aff0(float* out, float angle)
{
    out[0] = g_16b3c28;
    out[1] = g_16b3c2c;
    out[2] = g_16b3c30;

    if (angle > g_15a7c20) {
        double s = sin((double)g_15a7c24 - angle);
        out[0] = (float)s;
        out[1] = (float)-sqrt(1.0 - s * s);
    } else if (angle < -g_15a7c20) {
        double s = -sin((double)angle - g_15a7c24);
        out[0] = (float)s;
        out[2] = 0.0f;
        out[1] = (float)-sqrt(1.0 - s * s);
    } else {
        out[2] = 0.0f;
        double s = sin((double)angle);
        out[0] = (float)s;
        out[1] = (float)-sqrt(1.0 - s * s);
    }
}
