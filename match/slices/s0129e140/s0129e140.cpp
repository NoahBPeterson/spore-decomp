// Slice s0129e140: dynamic initializer for a file-scope float4 at 0x016f387c
// (three zero lanes written first, the 1.0f lane loaded from 0x01485720 afterwards).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern const float kOne;                // 0x01485720  1.0f
extern float g_float4_15f387c[4];       // 0x016f387c

// @ 0x0129e140
void init_float4_15f387c()
{
    g_float4_15f387c[0] = 0.0f;
    g_float4_15f387c[1] = 0.0f;
    g_float4_15f387c[2] = 0.0f;
    g_float4_15f387c[3] = kOne;
}
