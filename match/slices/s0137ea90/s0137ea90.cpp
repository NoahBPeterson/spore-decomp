// @ 0x0137ea90
// Compiler-generated dynamic initializer for a float global: g_16b39d0 = g_140f32c /
// (g_16b39cc * g_15a7b88 * g_140f334). All operands are extern const floats defined in other TUs,
// so cl evaluates this at startup with SSE scalar ops.
#include "types.h"

extern const float g_16b39cc;   // 0x016b39cc
extern const float g_15a7b88;   // 0x015a7b88
extern const float g_140f334;   // 0x0140f334
extern const float g_140f32c;   // 0x0140f32c
extern float g_16b39d0;         // 0x016b39d0

void FUN_0137ea90()
{
    g_16b39d0 = g_140f32c / (g_16b39cc * g_15a7b88 * g_140f334);
}
