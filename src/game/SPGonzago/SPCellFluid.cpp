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
extern int   g_16b39a8;        // 0x016b39a8
extern int   g_16b39ac;        // 0x016b39ac
extern int   g_16b39b0;        // 0x016b39b0
static int floor_f(float x)
{
    int v = _mm_cvtss_si32(_mm_set_ss(x));
    if (x < (float)v)
        v = v - 1;
    return v;
}
// ---- items of slice s00e4d920 end

// ---- items of slice s00e4e8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_15a7b94_hex;         // 0x015a7b94
extern float g_16b39d0;             // 0x016b39d0
void* operator_new__(void* dst, int v, int n);          // 0x011e073e (operator new[])
void  FUN_00e4dde0(void* a, void* b, int n);            // 0x00e4dde0
void  FUN_00e4e8d0(void* p);                            // 0x00e4e8d0
void  FUN_00e4def0(void* p);                            // 0x00e4def0
void  FUN_00e4e660(void* p, int i);                     // 0x00e4e660
int   SP_sPartitionGetNeighbors(int* a, int* b);        // 0x00e4e340
// ---- items of slice s00e4e8d0 end

// @ 0x00e4dbc0
int __cdecl FUN_00e4dbc0(void* selfv, int* pa, int* pb, int a4, int a5)
{
    char* self = (char*)selfv;
    int A = *(int*)(self + 0x1bd54);
    int v = A + 1;
    if (v == 0x5dc)
        return -1;
    int B = *(int*)(self + 0x1bd58);
    *(int*)(self + 0x1bd54) = v;
    int idx;
    if (A == B) {
        *(int*)(self + 0x1bd58) = B + 1;
        idx = v;
    } else {
        idx = *(int*)(self + 0x1bd5c);
        *(int*)(self + 0x1bd5c) = *(int*)(self + idx * 4 + 0x1a5e4);
    }
    int off = idx + idx * 2;
    *(int*)(self + off * 4 + 0x04) = pa[0];
    *(int*)(self + off * 4 + 0x08) = pa[1];
    *(int*)(self + off * 4 + 0x0c) = pa[2];
    *(int*)(self + off * 4 + 0x4654) = pb[0];
    *(int*)(self + off * 4 + 0x4658) = pb[1];
    *(int*)(self + off * 4 + 0x465c) = pb[2];
    *(int*)(self + off * 4 + 0xd2f4) = g_16b39a8;
    *(int*)(self + off * 4 + 0xd2f8) = g_16b39ac;
    *(int*)(self + off * 4 + 0xd2fc) = g_16b39b0;
    *(int*)(self + idx * 4 + 0x18e74) = a5;
    return idx;
}

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

// @ 0x00e4e8d0
void FUN_00e4e8d0(int param_1)
{
    char* dst = (char*)(param_1 + 0x15f94);
    operator_new__(dst, 0, 6000);
    float* pf = (float*)(param_1 + 4);
    int outer = 0x5dc;
    do {
        int nb[9], counts[9];
        int cnt = SP_sPartitionGetNeighbors(nb, counts);
        float radius = *(float*)&g_15a7b94_hex;
        for (int j = 0; j < cnt; ++j) {
            int k = counts[j];
            int done = 0;
            if (k > 3) {
                float* a = (float*)(nb[j] + 8);
                float* b = (float*)(nb[j] + 0x28);
                int groups = ((unsigned)(k - 4) >> 2) + 1;
                done = groups * 4;
                for (int g = 0; g < groups; ++g) {
                    for (int t = 0; t < 4; ++t) {
                        float* pa = a + t * 0x20 / 4;
                        float dx = pf[0] - pa[-2], dy = pf[1] - pa[-1], dz = pf[2] - pa[0];
                        float d = dx*dx + dy*dy + dz*dz;
                        if (d <= radius) { float e = radius - d; *(float*)dst += e*e*e; }
                    }
                    a += 0x20; b += 0x20;
                }
            }
            if (done < k) {
                float* q = (float*)(nb[j] + done * 0x20);
                for (int t = done; t < k; ++t) {
                    float dx = pf[0] - q[0], dy = pf[1] - q[1], dz = pf[2] - q[2];
                    float d = dx*dx + dy*dy + dz*dz;
                    if (d <= radius) { float e = radius - d; *(float*)dst += e*e*e; }
                    q += 8;
                }
            }
        }
        float v = *(float*)dst * g_16b39d0;
        *(float*)dst = v;
        ((float*)dst)[0x5dc] = v * 0.5f;
        *(float*)dst = 1.0f / (*(float*)dst + 1.5258789e-05f);
        dst += 4;
        pf += 3;
        --outer;
    } while (outer != 0);
    for (int i = 0; i < 0x5dc; ++i) FUN_00e4e660((void*)param_1, i);
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
