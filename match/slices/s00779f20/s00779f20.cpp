// Slice s00779f20: build a 3x4 direction basis matrix and upload it.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern void* g_pDevice;   // 0x16f89d0
struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))

extern float* g_16f6e40;    // 0x16f6e40  direction xyz
extern int    g_16f6ed8;    // 0x16f6ed8
extern float  g_one;        // 0x1485720  = 1.0f

// 0x006983a0  SP::MatrixFromDirection(const float* dir, float* out)
void __cdecl SP_MatrixFromDirection(const float* dir, float* out);

// @ 0x00779f20
void FUN_00779f20(unsigned reg, unsigned count, int isVS) {
    float dir[3];
    dir[0] = g_16f6e40[0];
    dir[1] = g_16f6e40[1];
    dir[2] = g_16f6e40[2];
    float r[9];
    float m[12];
    if (g_16f6ed8 != 0) {
        SP_MatrixFromDirection(dir, r);
        m[0] = r[0]; m[1] = r[1]; m[2] = r[2];
        m[3] = -((r[2] * dir[2] + r[1] * dir[1]) + r[0] * dir[0]);
        m[4] = r[3]; m[5] = r[4]; m[6] = r[5];
        m[7] = -((r[5] * dir[2] + r[4] * dir[1]) + r[3] * dir[0]);
        m[8] = r[6]; m[9] = r[7]; m[10] = r[8];
        m[11] = -((r[8] * dir[2] + r[7] * dir[1]) + r[6] * dir[0]);
    } else {
        m[0] = g_one;  m[1] = 0.0f;   m[2] = 0.0f;   m[3] = -dir[0];
        m[4] = 0.0f;   m[5] = g_one;  m[6] = 0.0f;   m[7] = -dir[1];
        m[8] = 0.0f;   m[9] = 0.0f;   m[10] = g_one; m[11] = -dir[2];
    }
    if (isVS)
        SETVS(g_pDevice, reg, m, count);
    else
        SETPS(g_pDevice, reg, m, count);
}
