// src/game/SPGonzago/SPCellFluid.cpp -- migrated from slice(s) s00e4e8d0, s00e4d920 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCellFluid.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float g_cellX;          // 0x016b3c88
extern float g_cellY;          // 0x016b3c8c
extern float g_15a7b90, g_15a7b94, g_15a7b8c, g_15a7b9c, g_15a7ba0;
extern float g_1483ba4, g_1483ba8, g_1483bac, g_1483bb4, g_1483bb8, g_1483bbc;
#include <intrin.h>
#include <xmmintrin.h>
#include "SP/cSPFluidParticles.h"

// ---- items of slice s00e4d920 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_cellX;          // 0x016b3c88
extern float g_cellY;          // 0x016b3c8c
extern float g_15a7b90, g_15a7b94, g_15a7b8c, g_15a7b9c, g_15a7ba0;
extern float g_1483ba4, g_1483ba8, g_1483bac, g_1483bb4, g_1483bb8, g_1483bbc;
static int floor_f(float x)
{
    int v = _mm_cvtss_si32(_mm_set_ss(x));
    if (x < (float)v)
        v = v - 1;
    return v;
}
// ---- items of slice s00e4d920 end

// ---- items of slice s00e4e8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  FUN_00e4dde0(void* a, void* b, int n);            // 0x00e4dde0
void  FUN_00e4e8d0(void* p);                            // 0x00e4e8d0
void  FUN_00e4def0(void* p);                            // 0x00e4def0
// ---- items of slice s00e4e8d0 end

// @ 0x00e4dc90
int __fastcall SP_sPositionToCellIndex(float* p)
{
    int x = floor_f((p[0] - g_cellX) * g_15a7b9c);
    int y = floor_f((p[1] - g_cellY) * g_15a7ba0);
    if (x < 0x14 && y < 0xf)
        return y * 0x14 + x;
    return -1;
}

// @ 0x00e4dd20
void __fastcall FUN_00e4dd20(float* in, float* out)
{
    out[0] = (in[0] - g_cellX) * g_15a7b9c;
    out[1] = (in[1] - g_cellY) * g_15a7ba0;
    if (out[0] <= 0.0f) out[0] = 0.0f;
    if (g_1483bbc <= out[0]) out[0] = g_1483bbc;
    if (out[1] <= 0.0f) out[1] = 0.0f;
    if (g_1483bb8 <= out[1]) out[1] = g_1483bb8;
}

// @ 0x00e4e170
void __cdecl FUN_00e4e170(float param_1, int param_2, int param_3, int* param_4, float* param_5, float* param_6, int* param_7)
{
    int v = _mm_cvtss_si32(_mm_set_ss(param_1));
    if (param_1 < (float)v)
        v = v - 1;
    *param_4 = v;
    float frac = param_1 - (float)v;
    *param_5 = 0.0f;
    *param_6 = 0.0f;
    *param_7 = 0;
    if (frac >= 0.5f) {
        *param_5 = 1.5f - frac;
        if (*param_4 < param_3 - 1)
            *param_7 = 1;
    } else {
        *param_5 = frac + 0.5f;
        if (param_2 < *param_4) {
            *param_7 = -1;
            *param_6 = 1.0f - *param_5;
            return;
        }
    }
    *param_6 = 1.0f - *param_5;
}

// @ 0x00e4ebe0
namespace SP {
void FluidParticlesUpdate(cSPFluidParticles * p, float a2)
{
    FUN_00e4dde0((char*)p + 0x4654, (char*)p + 0x15f94, 0x5dc);
    FUN_00e4e8d0(p);
    FUN_00e4def0((char*)p + 0x1d4d0);
}
}  // namespace SP
