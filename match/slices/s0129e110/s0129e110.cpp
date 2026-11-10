// Slice s0129e110: compiler-generated dynamic initializer for a file-scope
// float4 at 0x016f39a0: zero, zero, 1.0f, zero (built /arch:SSE, so the zero
// lanes share one xorps'd xmm and 1.0f comes from __real@3f800000 0x01485720).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern const float kOne;                // 0x01485720  1.0f
extern float g_float4_15f39a0[4];       // 0x016f39a0

// @ 0x0129e110
void init_float4_15f39a0()
{
    g_float4_15f39a0[0] = 0.0f;
    g_float4_15f39a0[1] = 0.0f;
    g_float4_15f39a0[2] = kOne;
    g_float4_15f39a0[3] = 0.0f;
}
