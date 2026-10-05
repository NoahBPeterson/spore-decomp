// Slice s00778fd0: rw::graphics shader-constant setters (region 0x778fd0-0x779c10).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <math.h>

// ---- D3D9 device (IDirect3DDevice9) ------------------------------------------------------
extern void* g_pDevice;  // 0x16f89d0
struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))

extern float g_one;   // 0x1485720 = 1.0f

// ---- constants sources -------------------------------------------------------------------
extern int*   g_178fd0;   // 0x16f6e68
extern float* g_179030;   // 0x16f6e6c
extern char*  g_1790a0;   // 0x16f6de8
extern float* g_179130;   // 0x16f6e94
extern float* g_179560;   // 0x16f6e0c
extern float* g_179670;   // 0x16f6dbc
extern float* g_179670b;  // 0x16f6ec8
extern float* g_179b60;   // 0x16f6e34
extern int    g_flag_1632f44;          // 0x1632f44
extern unsigned char g_buf_1632ea0[];  // 0x1632ea0

// lights / camera (complex functions)
struct LightRow { char pad[0x10]; float px, py, pz; float cx, cy, cz, cw; };
extern int     g_lightsCount;   // 0x16f8910
extern LightRow* g_lights[];    // 0x16f8914
extern void*   g_17a5b8;        // 0x16fa5b8
extern float*  g_16f6e40;       // 0x16f6e40
extern char*   g_16f85ac;       // 0x16f85ac
extern float*  g_16f6e38;       // 0x16f6e38
extern float   g_1632c08, g_1632c0c, g_1632c10, g_1632c14;  // 0x1632c08
extern void*   FUN_011fca60(void* out, const void* in);
extern void*   FUN_011f1120();
extern void*   FUN_0067dd50();

// @ 0x00778fd0
void FUN_00778fd0(unsigned reg, unsigned p2, int isVS) {
    int* p = g_178fd0;
    if (p) {
        float v[4] = { (float)p[0], 0.0f, 0.0f, 0.0f };
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x00779030
void FUN_00779030(unsigned reg, unsigned p2, int isVS) {
    float* p = g_179030;
    if (p) {
        float v[4] = { p[0], p[1], p[2], 0.0f };
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x007790a0
void FUN_007790a0(unsigned reg, unsigned p2, int isVS) {
    char* p = g_1790a0;
    if (p) {
        float v[4];
        v[0] = *(float*)(p + 4);
        v[1] = *(float*)(p + 8);
        v[2] = *(float*)(p + 0xc);
        v[3] = g_one;
        if (p[1] == '\\' && p[2] == 'D' && p[3] == '&')
            v[3] = *(float*)(p + 0x10);
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x00779130
void FUN_00779130(unsigned reg, unsigned p2, int isVS) {
    float* p = g_179130;
    float v[32];
    if (p) {
        for (int k = 0; k < 8; ++k) {
            v[k * 4 + 0] = p[k * 2];
            v[k * 4 + 1] = p[k * 2 + 1];
            v[k * 4 + 2] = p[0x10 + k];
        }
    }
    if (isVS)
        SETVS(g_pDevice, reg, v, 8);
    else
        SETPS(g_pDevice, reg, v, 8);
}

// @ 0x00779560
void FUN_00779560(unsigned reg, unsigned count, int isVS) {
    float* p = g_179560;
    if (p) {
        if (isVS)
            SETVS(g_pDevice, reg, p + 1, count);
        else
            SETPS(g_pDevice, reg, p + 1, count);
    }
}

// @ 0x00779670
void FUN_00779670(unsigned reg, unsigned p2, int isVS) {
    float* p = g_179670;
    if (p) {
        float v[4] = { p[4] * g_179670b[0], 0.0f, 0.0f, 0.0f };
        if (isVS) {
            SETVS(g_pDevice, reg, p, 1);
            SETVS(g_pDevice, reg + 1, v, 1);
        } else {
            SETPS(g_pDevice, reg, p, 1);
            SETPS(g_pDevice, reg + 1, v, 1);
        }
    }
}

// @ 0x00779710
void FUN_00779710(unsigned reg, unsigned p2, int isVS) {
    void* p = FUN_0067dd50();
    int* q = (int*)((int*(__thiscall*)(void*))((*(void***)p)[0x1c / 4]))(p);
    float v[4];
    v[0] = (float)q[2];
    v[1] = (float)q[3];
    v[2] = (float)q[2] / (float)q[0];
    v[3] = (float)q[3] / (float)q[1];
    if (isVS)
        SETVS(g_pDevice, reg, v, 1);
    else
        SETPS(g_pDevice, reg, v, 1);
}

// @ 0x00779b60
void FUN_00779b60(unsigned reg, unsigned count, int isVS) {
    float* p = g_179b60;
    if (p) {
        if (isVS)
            SETVS(g_pDevice, reg, p + 1, count);
        else
            SETPS(g_pDevice, reg, p + 1, count);
        return;
    }
    if (!(g_flag_1632f44 & 1)) {
        g_flag_1632f44 |= 1;
        memset(g_buf_1632ea0, 0, 0xa4);
    }
    float* data = (float*)(g_buf_1632ea0 + 4);
    if (isVS)
        SETVS(g_pDevice, reg, data, count);
    else
        SETPS(g_pDevice, reg, data, count);
}

// @ 0x00779290  upload light rows (world-space position + negated colour) as shader constants
void FUN_00779290(unsigned reg, unsigned count, int isVS) {
    int target = (int)((count + 1) >> 1);
    int n = g_lightsCount;
    if (target < n)
        n = target;
    float buf[256];
    for (int i = 0; i < n; ++i) {
        LightRow* L = g_lights[i];
        float* o = buf + i * 8;
        o[0] = -L->cx;
        o[1] = -L->cy;
        o[2] = -L->cz;
        o[3] = 0.0f;
        o[4] = L->px;
        o[5] = L->py;
        o[6] = L->pz;
        o[7] = 1.0f;
    }
    if (n < target)
        memset(buf + n * 8, 0, (target - n) * 0x20);
    if (isVS)
        SETVS(g_pDevice, reg, buf, count);
    else
        SETPS(g_pDevice, reg, buf, count);
}

// @ 0x007793e0  light rows transformed by a matrix
void FUN_007793e0(unsigned reg, unsigned count, int isVS) {
    int target = (int)((count + 1) >> 1);
    int n = g_lightsCount;
    if (target < n)
        n = target;
    float buf[256];
    for (int i = 0; i < n; ++i) {
        LightRow* L = g_lights[i];
        float lp[4] = { L->cx, L->cy, L->cz, L->cw };
        float t[4];
        FUN_011fca60(t, lp);
        float* o = buf + i * 8;
        o[0] = -t[0];
        o[1] = -t[1];
        o[2] = -t[2];
        o[3] = 0.0f;
        o[4] = L->px;
        o[5] = L->py;
        o[6] = L->pz;
        o[7] = 1.0f;
    }
    if (n < target)
        memset(buf + n * 8, 0, (target - n) * 0x20);
    if (isVS)
        SETVS(g_pDevice, reg, buf, count);
    else
        SETPS(g_pDevice, reg, buf, count);
}

// @ 0x007795a0  distance between the current transform origin and a focus point
void FUN_007795a0(unsigned reg, unsigned count, int isVS) {
    float a0 = *(float*)((char*)g_17a5b8 + 0x30);
    float a1 = *(float*)((char*)g_17a5b8 + 0x34);
    float a2 = *(float*)((char*)g_17a5b8 + 0x38);
    float b0, b1, b2;
    if (g_16f6e40) {
        b0 = g_16f6e40[0];
        b1 = g_16f6e40[1];
        b2 = g_16f6e40[2];
    } else {
        b0 = *(float*)(g_16f85ac + 0x30);
        b1 = *(float*)(g_16f85ac + 0x34);
        b2 = *(float*)(g_16f85ac + 0x38);
    }
    float v[4];
    v[0] = (float)sqrt((a2 - b2) * (a2 - b2) + (a1 - b1) * (a1 - b1) + (a0 - b0) * (a0 - b0));
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    if (isVS)
        SETVS(g_pDevice, reg, v, count);
    else
        SETPS(g_pDevice, reg, v, count);
}

// @ 0x007799f0  projector / texture-scale constants
void FUN_007799f0(unsigned reg, unsigned count, int isVS) {
    int obj = (int)FUN_011f1120();
    float v[12];
    if (obj == 0) {
        v[0] = g_1632c08;  v[1] = g_1632c0c;  v[2] = g_1632c10;  v[3] = g_1632c14;
        v[4] = g_1632c08;  v[5] = g_1632c0c;  v[6] = g_1632c10;  v[7] = g_1632c14;
        v[8] = g_1632c08;  v[9] = g_1632c0c;  v[10] = g_1632c10; v[11] = g_1632c14;
    } else {
        int tex = *(int*)(obj + 0x40);
        float w = (float)*(unsigned short*)(tex + 0xc);
        float h = (float)*(unsigned short*)(tex + 0xe);
        v[0] = w;   v[1] = h;   v[2] = 1.0f / w; v[3] = 1.0f / h;
        v[4] = 0.0f; v[5] = 0.0f; v[6] = 0.0f; v[7] = 0.0f;
        v[8] = 0.0f; v[9] = 0.0f; v[10] = 1.0f; v[11] = 1.0f;
        if (count > 1) {
            float angle = (float)atan2(*(float*)(obj + 0x5c), 1.0f);
            float pw = (float)*(unsigned short*)(obj + 0x80);
            float ph = (float)*(unsigned short*)(obj + 0x84);
            v[4] = pw;
            v[5] = ph;
            v[6] = 1.0f / pw;
            v[7] = 1.0f / ph;
            v[8] = *(float*)(obj + 0x70);
            v[9] = *(float*)(obj + 0x74);
            v[10] = angle;
            v[11] = 1.0f;
        }
    }
    if (isVS)
        SETVS(g_pDevice, reg, v, count);
    else
        SETPS(g_pDevice, reg, v, count);
}

// @ 0x00779c10  (partial) camera-relative light vector; only the fallback path is exact
void FUN_00779c10(unsigned reg, unsigned p2, int isVS) {
    if (g_17a5b8 == 0)
        return;
    float v[4];
    if (g_16f6e38 == 0) {
        v[0] = g_1632c08;
        v[1] = g_1632c0c;
        v[2] = g_1632c10;
        v[3] = g_1632c14;
    } else {
        // simplified: direction from the transform origin toward the focus point
        float a0 = *(float*)((char*)g_17a5b8 + 0x30);
        float a1 = *(float*)((char*)g_17a5b8 + 0x34);
        float a2 = *(float*)((char*)g_17a5b8 + 0x38);
        float b0, b1, b2;
        if (g_16f6e40) {
            b0 = g_16f6e40[0]; b1 = g_16f6e40[1]; b2 = g_16f6e40[2];
        } else {
            b0 = *(float*)(g_16f85ac + 0x30);
            b1 = *(float*)(g_16f85ac + 0x34);
            b2 = *(float*)(g_16f85ac + 0x38);
        }
        float d0 = b0 - a0, d1 = b1 - a1, d2 = b2 - a2;
        float len = (float)sqrt(d0 * d0 + d1 * d1 + d2 * d2);
        v[0] = len;
        v[1] = g_16f6e38[1];
        v[2] = 0.0f;
        v[3] = 1.0f;
    }
    if (isVS)
        SETVS(g_pDevice, reg, v, 1);
    else
        SETPS(g_pDevice, reg, v, 1);
}
