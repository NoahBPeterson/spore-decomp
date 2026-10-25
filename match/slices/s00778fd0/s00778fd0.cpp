// Slice s00778fd0: rw::graphics shader-constant setters (region 0x778fd0-0x779c10).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <math.h>
#include <intrin.h>

// ---- D3D9 device (IDirect3DDevice9) ------------------------------------------------------
extern void* g_pDevice;  // 0x16f89d0
struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))

extern float g_one;   // 0x1485720 = 1.0f
extern float g_1539ef8;   // 0x1539ef8: degrees-per-radian constant used by the projector angle
extern float g_1470f1c;   // 0x1470f1c = 2.0f

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
struct __declspec(align(16)) Vec4f { float x, y, z, w; };
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
#pragma intrinsic(sqrt)
void FUN_007795a0(unsigned reg, unsigned count, int isVS) {
    __m128 a = *(const __m128*)((const char*)g_17a5b8 + 0x30);
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
    Vec4f v;
    v.x = (float)sqrt((double)((a.m128_f32[2] - b2) * (a.m128_f32[2] - b2) + (a.m128_f32[1] - b1) * (a.m128_f32[1] - b1) + (a.m128_f32[0] - b0) * (a.m128_f32[0] - b0)));
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 1.0f;
    if (isVS)
        SETVS(g_pDevice, reg, &v.x, count);
    else
        SETPS(g_pDevice, reg, &v.x, count);
}

// @ 0x007799f0  projector / texture-scale constants
// v = { texW, texH, 1/texW, 1/texH,                     // render-target size block
//       projW, projH, 1/projW, 1/projH,                 // (count > 1 only)
//       obj+0x70, obj+0x74, angle*360/kDegPerRad, 1.0 } // (count > 1 only)
// When FUN_011f1120() has no active texture object the block is filled from the four
// 0x01632c08.. globals (v[0] is left untouched, exactly as in the original).
// (0-3 only; declared before the marker so the marker binds to the function definition)
namespace rw { namespace graphics {
void RWShader_SetShConst_projector(unsigned reg, unsigned count, int isVS);   // 0x007799f0
} }
void rw::graphics::RWShader_SetShConst_projector(unsigned reg, unsigned count, int isVS) {
    float v[12];
    int obj = (int)FUN_011f1120();
    if (obj != 0) {
        int tex = *(int*)(obj + 0x40);
        float w = (float)*(unsigned short*)(tex + 0xc);
        float h = (float)*(unsigned short*)(tex + 0xe);
        v[0] = w;   v[1] = h;   v[2] = 1.0f / w; v[3] = 1.0f / h;
        if (count > 1) {
            float pw = (float)*(unsigned short*)(obj + 0x80);
            float ph = (float)*(unsigned short*)(obj + 0x84);
            float angle = (float)atan2(*(float*)(obj + 0x5c), 1.0f);
            v[4] = pw;
            v[5] = ph;
            v[6] = 1.0f / pw;
            v[7] = 1.0f / ph;
            v[8] = *(float*)(obj + 0x70);
            v[9] = *(float*)(obj + 0x74);
            v[10] = (360.0f / g_1539ef8) * angle;
        }
        v[11] = 1.0f;
    } else {
        v[1] = g_1632c08;  v[2] = g_1632c0c;  v[3] = g_1632c10;
        v[4] = g_1632c14;
        v[5] = g_1632c08;  v[6] = g_1632c0c;  v[7] = g_1632c10;
        v[8] = g_1632c14;
        v[9] = g_1632c08;  v[10] = g_1632c0c; v[11] = g_1632c10;
    }
    if (isVS)
        SETVS(g_pDevice, reg, v, count);
    else
        SETPS(g_pDevice, reg, v, count);
}

// Support layout for 0x00779c10's transform read (declared before the marker so the marker
// binds to the function definition and not to this type).
struct __declspec(align(16)) Transform3030 { float mOrigin[4]; };
struct LightParams {
    float m0;   // +0x00
    float m1;   // +0x04
    float m2;   // +0x08
    float m3;   // +0x0c  radius
    float m4;   // +0x10  enabled/interest (<= 0 disables the disc solve)
    float m5;   // +0x14
    float m6;   // +0x18
    float m7;   // +0x1c
    float m8;   // +0x20
    float m9;   // +0x24  x-axis weight
    float m10;  // +0x28  y-axis weight
    float m11;  // +0x2c  z-axis weight
    float m12;  // +0x30  falloff start
};

// @ 0x00779c10  camera-relative light vector.
// Reads the active transform's origin (g_17a5b8+0x30) and a focus point (g_16f6e40 or the
// 0x16f85ac transform), computes the eye->focus distance and a clamped attenuation ratio from
// the light parameters at g_16f6e38, and uploads a single float4 to the current shader.
namespace rw { namespace graphics {
void RWShader_SetShConst_cameraLight(unsigned reg, unsigned p2, int isVS);   // 0x00779c10
} }
void rw::graphics::RWShader_SetShConst_cameraLight(unsigned reg, unsigned p2, int isVS) {
    if (g_17a5b8 == 0)
        return;

    __declspec(align(16)) float out[4];
    if (g_16f6e38 == 0) {
        out[0] = g_1632c08;
        out[1] = g_1632c0c;
        out[2] = g_1632c10;
        out[3] = g_1632c14;
    } else {
        const Transform3030* xform = (const Transform3030*)((const char*)g_17a5b8 + 0x30);
        const float a0 = xform->mOrigin[0];
        const float a1 = xform->mOrigin[1];
        const float a2 = xform->mOrigin[2];

        float b0, b1, b2;
        if (g_16f6e40) {
            b0 = g_16f6e40[0]; b1 = g_16f6e40[1]; b2 = g_16f6e40[2];
        } else {
            b0 = *(float*)(g_16f85ac + 0x30);
            b1 = *(float*)(g_16f85ac + 0x34);
            b2 = *(float*)(g_16f85ac + 0x38);
        }

        const float d0 = a0 - b0;
        const float d1 = a1 - b1;
        const float d2 = a2 - b2;
        const float len = (float)sqrt((double)(d2 * d2 + (d1 * d1 + d0 * d0)));
        const float inv = 1.0f / len;

        LightParams* lp = (LightParams*)g_16f6e38;

        // Distance along the light direction to the sphere's near intersection, clamped to
        // [0, len]; falls back to len when the parameters are disabled.
        float reach;
        if (0.0f < lp->m4) {
            const float n = -((d2 * inv) * a2 + ((d1 * inv) * a1 + (d0 * inv) * a0));
            float disc = n * n - ((a2 * a2 + (a1 * a1 + a0 * a0)) - lp->m3 * lp->m3);
            if (disc > 0.0f) {
                float t = (float)sqrt((double)disc) - n;
                if (t < 0.0f)
                    t = 0.0f;
                reach = (t <= len) ? t : len;
            } else {
                reach = 0.0f;
            }
        } else {
            reach = len;
        }

        // Normalised focus direction dotted with the light's axis weights.
        const float r = 1.0f / (float)sqrt((double)(b2 * b2 + (b1 * b1 + b0 * b0) + 1e-08f));
        const float fVar3 = lp->m11 * (a2 * r) + (lp->m10 * (a1 * r) + (r * a0) * lp->m9);

        float falloff = fVar3 + 0.95f;
        if (falloff < 0.0f)
            falloff = 0.0f;
        if (falloff > 1.0f)
            falloff = 1.0f;

        float ratio = 1.0f;
        if (fVar3 <= lp->m12) {
            float start = fVar3 + lp->m12;
            if (start < 0.001f)
                start = 0.001f;
            ratio = start / (lp->m12 * g_1470f1c);
        }

        out[0] = (len - reach) + lp->m0;
        out[1] = lp->m1;
        out[2] = ratio;
        out[3] = falloff;
    }

    if (isVS)
        SETVS(g_pDevice, reg, out, 1);
    else
        SETPS(g_pDevice, reg, out, 1);
}
