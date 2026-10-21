// Slice s00f2f830 -- AreaRect, which needs /fp:fast to match the retail codegen.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

// --- data -------------------------------------------------------------------
extern float g_15b0120;              // 0x015B0120
extern float g_15b00c4;              // 0x015B00C4
extern float g_15b00c8;              // 0x015B00C8

// @ 0x00f301e0
float __cdecl AreaRect(float a, float b)
{
    if (a > g_15b0120 && b > g_15b00c4)
        return (g_15b00c8 * a) * b;
    return 0.0f;
}
