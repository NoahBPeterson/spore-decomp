// Slice s011fba40 - graphics::rw ActiveState render-state helpers (vpu_math matrix / light block).
//
//   011fba40  FUN_011fba40        - normal length helper (rsqrtps + 2 Newton iterations)
//   011fbce0  FUN_011fbce0        - bind inverse transform (lazy rw math invert)
//   011fbda0  FUN_011fbda0        - bind transposed inverse transform
//   011fbea0  FUN_011fbea0        - bind transformed light position (+0x30)
//   011fbf50  FUN_011fbf50        - bind light position transformed by the fixed 4x4
//   011fc040  FUN_011fc040        - bind light vector (+0x20) by the fixed 3x3
//   011fc120  FUN_011fc120        - bind light range scalar as a float4
//   011fc200  FUN_011fc200        - bind light direction dot-length scalar
//   011fc3d0  FUN_011fc3d0        - bind transformed translation of a matrix
//   011fc470  FUN_011fc470        - bind CalcLightRange result
//
// Toolchain: VS2008 SP1 (cl 15.00) Spore game code; flags /O2 /MD /Gy /EHsc /TP /arch:SSE.
// All ten functions tail into the D3D9 device's vtable (COM __stdcall, `this` as first stack
// argument): slot 0x178 when the caller's third argument is non-zero, slot 0x1b4 otherwise.
// The per-function constant addresses are the retail rw::math globals (versions of the active
// transform, the lazily built inverse, the unit-normal cache and the fixed light basis matrix).
#include "types.h"
#include <math.h>

// ---- fixed retail globals (addressed directly, as the original does) -------------------------
//  0x016f8b50 int   active matrix type          (3,4 == ortho/screen: no transform)
//  0x016f9120 void* lazily built inverse matrix (cache pointer, 0 == not built)
//  0x016f85ac void* active Matrix44Affine       (source of the inverse)
//  0x016f89d0 void* IDirect3DDevice9            (device whose vtable we call)
//  0x016fa5b8 void* Matrix44                    (source matrix of the translation helper)
//  0x016f656c void* lights[8]                   (first non-null entry is used)
//  0x016f8b10 float fixedLightBasis[4][4]       (rows at +0x00,+0x10,+0x20,+0x30)
//  0x01718a60 float inverseMatrix[16]           (storage behind 0x016f9120)
//  0x017189e0 u32/x2 normal-cache flags
//  0x017189d0 float normal[4]    0x017189c0 float transformedNormal[4]
//  0x017189f0 float normal2[4]   0x01718a00 u32 normal2 flags
//  0x01471064 float 0.5f   0x01485720 float 1.0f
//  0x014f8148 float 0.5773502588f           0x014f811c float FLT_MAX

typedef uint32_t u32;

struct __declspec(align(16)) Vec4 { float x, y, z, w; };
struct __declspec(align(16)) Mat4 { float m[16]; };

// ---- external engine helpers ----------------------------------------------------------------
void  __cdecl FUN_011fb230(float* out);                        // 0x011fb230  CalcLightRange
void  __cdecl FUN_011fb950(float* out, const float* in);       // 0x011fb950  TransformPoint
void* __cdecl FUN_011fb310(void* out, const void* in);         // 0x011fb310  Matrix44Invert
void  __cdecl rw_Matrix4_invert(void* out, const void* in, int type);  // 0x00778060
void  __stdcall D3DXMatrixTranspose(void* out, const void* in);// 0x011e1fec

// ---- D3D9 device vtable (raw slots 0x178 / 0x1b4; __stdcall with `this` on the stack) --------
struct RwDevice;
typedef void (__stdcall *RwDevFn)(RwDevice* dev, u32 a, void* data, u32 count);
struct RwDeviceVtbl {
    void*   m_pad178[0x178 / 4];
    RwDevFn m_fn178;                       // 0x178
    void*   m_pad1b4[(0x1b4 - 0x17c) / 4];
    RwDevFn m_fn1b4;                       // 0x1b4
};
struct RwDevice { RwDeviceVtbl* lpVtbl; };

// Dispatch a prepared constant to the device: non-zero flag selects the 0x178 method.
static __forceinline void RwDevBind(u32 a, void* data, u32 count, int flag)
{
    RwDevice* dev = *(RwDevice**)0x016f89d0;
    if (flag != 0)
        dev->lpVtbl->m_fn178(dev, a, data, count);
    else
        dev->lpVtbl->m_fn1b4(dev, a, data, count);
}

// Lazily build the inverse of the active transform into 0x01718a60 and publish it in 0x016f9120.
static __forceinline void* RwEnsureInverse()
{
    void* inv = *(void**)0x016f9120;
    if (inv == 0) {
        Mat4 tmp;
        *(Mat4*)0x01718a60 = *(const Mat4*)*(void**)0x016f85ac;
        rw_Matrix4_invert(tmp.m, (const void*)0x01718a60, *(int*)0x016f8b50);
        *(Mat4*)0x01718a60 = tmp;
        inv = (void*)0x01718a60;
        *(void**)0x016f9120 = inv;
    }
    return inv;
}

// First non-null entry of the light array (0x016f656c), or null when all eight are empty.
static __forceinline void* RwFirstLight()
{
    int i = 0;
    if (((void**)0x016f656c)[0] == 0) {
        do { ++i; } while (((void**)0x016f656c)[i] == 0);
    }
    return (i < 8) ? ((void**)0x016f656c)[i] : (void*)0;
}

// ---------------------------------------------------------------------------
// 0x011fba40  normal length helper: out = s / |transformedNormal|
// ---------------------------------------------------------------------------
// @ 0x011fba40
void FUN_011fba40(float* out, float s)
{
    if (*(int*)0x016f8b50 == 3 || *(int*)0x016f8b50 == 4) {
        *out = s;
        return;
    }

    if (*(void**)0x016f9120 == 0) {
        Mat4 tmp;
        FUN_011fb310(tmp.m, *(void**)0x016f85ac);
        *(Mat4*)0x01718a60 = tmp;
        *(void**)0x016f9120 = (void*)0x01718a60;
    }

    if ((*(u32*)0x017189e0 & 1) == 0) {
        *(u32*)0x017189e0 |= 1;
        float v = *(float*)0x014f8148;                 // 0.5773502588
        ((float*)0x017189d0)[0] = v;
        ((float*)0x017189d0)[1] = v;
        ((float*)0x017189d0)[2] = v;
        ((float*)0x017189d0)[3] = v;
    }
    if ((*(u32*)0x017189e0 & 2) == 0) {
        *(u32*)0x017189e0 |= 2;
        const float* m = (const float*)0x01718a60;
        const float* n = (const float*)0x017189d0;
        float* c = (float*)0x017189c0;
        c[0] = m[0] * n[0] + m[4] * n[1] + m[8]  * n[2];
        c[1] = m[1] * n[0] + m[5] * n[1] + m[9]  * n[2];
        c[2] = m[2] * n[0] + m[6] * n[1] + m[10] * n[2];
        c[3] = m[3] * n[0] + m[7] * n[1] + m[11] * n[2];
    }

    const float* c = (const float*)0x017189c0;
    float len2 = c[0] * c[0] + c[1] * c[1] + c[2] * c[2];

    // retail: rsqrtps + two Newton-Raphson refinements
    float inv = 1.0f / sqrtf(len2);
    inv = inv + (*(float*)0x01485720 - len2 * (inv * inv)) * (inv * (*(float*)0x01471064));
    inv = inv + (*(float*)0x01485720 - len2 * (inv * inv)) * (inv * (*(float*)0x01471064));

    *out = inv * s;
}

// ---------------------------------------------------------------------------
// 0x011fbce0  bind the (lazily inverted) active transform
// ---------------------------------------------------------------------------
// @ 0x011fbce0
void FUN_011fbce0(u32 a, u32 b, int flag)
{
    RwDevBind(a, RwEnsureInverse(), b, flag);
}

// ---------------------------------------------------------------------------
// 0x011fbda0  bind the transpose of the inverse active transform
// ---------------------------------------------------------------------------
// @ 0x011fbda0
void FUN_011fbda0(u32 a, u32 b, int flag)
{
    void* inv = RwEnsureInverse();
    float m[16];
    D3DXMatrixTranspose(m, inv);
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = *(float*)0x01485720;                       // 1.0
    RwDevBind(a, m, b, flag);
}

// ---------------------------------------------------------------------------
// 0x011fbea0  bind TransformPoint of the first light's position (light + 0x30)
// ---------------------------------------------------------------------------
// @ 0x011fbea0
void FUN_011fbea0(u32 a, u32 b, int flag)
{
    void* p = RwFirstLight();
    Vec4 local;
    local.x = 0.0f; local.y = 0.0f; local.z = 0.0f; local.w = 0.0f;
    if (p != 0 && *(int*)p != 0 && *(int*)p != 4)
        FUN_011fb950((float*)&local, (const float*)((char*)p + 0x30));
    RwDevBind(a, &local, 1, flag);
}

// ---------------------------------------------------------------------------
// 0x011fbf50  bind the fixed 4x4 applied to the first light's position (light + 0x30)
// ---------------------------------------------------------------------------
// @ 0x011fbf50
void FUN_011fbf50(u32 a, u32 b, int flag)
{
    void* p = RwFirstLight();
    Vec4 local;
    local.x = 0.0f; local.y = 0.0f; local.z = 0.0f; local.w = 0.0f;
    if (p != 0 && *(int*)p != 0 && *(int*)p != 4) {
        const float* pos = (const float*)((char*)p + 0x30);
        const float* m = (const float*)0x016f8b10;
        local.x = m[0] * pos[0] + m[4] * pos[1] + m[8]  * pos[2] + m[12];
        local.y = m[1] * pos[0] + m[5] * pos[1] + m[9]  * pos[2] + m[13];
        local.z = m[2] * pos[0] + m[6] * pos[1] + m[10] * pos[2] + m[14];
        local.w = m[3] * pos[0] + m[7] * pos[1] + m[11] * pos[2] + m[15];
    }
    RwDevBind(a, &local, 1, flag);
}

// ---------------------------------------------------------------------------
// 0x011fc040  bind the fixed 3x3 applied to the first light's vector (light + 0x20)
// ---------------------------------------------------------------------------
// @ 0x011fc040
void FUN_011fc040(u32 a, u32 b, int flag)
{
    void* p = RwFirstLight();
    Vec4 local;
    local.x = 0.0f; local.y = 0.0f; local.z = 0.0f; local.w = 0.0f;
    if (p != 0 && *(int*)p != 1 && *(int*)p != 3) {
        const float* pos = (const float*)((char*)p + 0x20);
        const float* m = (const float*)0x016f8b10;
        local.x = m[0] * pos[0] + m[4] * pos[1] + m[8]  * pos[2];
        local.y = m[1] * pos[0] + m[5] * pos[1] + m[9]  * pos[2];
        local.z = m[2] * pos[0] + m[6] * pos[1] + m[10] * pos[2];
        local.w = m[3] * pos[0] + m[7] * pos[1] + m[11] * pos[2];
    }
    RwDevBind(a, &local, 1, flag);
}

// ---------------------------------------------------------------------------
// 0x011fc120  bind { lightRange, 0, 0, 1 } (FLT_MAX when no light)
// ---------------------------------------------------------------------------
// @ 0x011fc120
void FUN_011fc120(u32 a, u32 b, int flag)
{
    void* p = RwFirstLight();
    Vec4 local;
    local.y = 0.0f;
    local.z = 0.0f;
    local.w = *(float*)0x01485720;                     // 1.0
    if (p == 0 || *(int*)p == 0 || *(int*)p == 4)
        local.x = *(float*)0x014f811c;                 // FLT_MAX
    else
        FUN_011fba40(&local.x, *(float*)((char*)p + 4));
    RwDevBind(a, &local, 1, flag);
}

// ---------------------------------------------------------------------------
// 0x011fc200  bind { light[1] / |basis^T * normal|, 0, 0, 1 }
// ---------------------------------------------------------------------------
// @ 0x011fc200
void FUN_011fc200(u32 a, u32 b, int flag)
{
    void* p = RwFirstLight();
    Vec4 local;
    local.y = 0.0f;
    local.z = 0.0f;
    local.w = *(float*)0x01485720;                     // 1.0
    if (p == 0 || *(int*)p == 0 || *(int*)p == 4) {
        local.x = *(float*)0x014f811c;                 // FLT_MAX
    } else {
        if ((*(u32*)0x01718a00 & 1) == 0) {
            *(u32*)0x01718a00 |= 1;
            float v = *(float*)0x014f8148;             // 0.5773502588
            ((float*)0x017189f0)[0] = v;
            ((float*)0x017189f0)[1] = v;
            ((float*)0x017189f0)[2] = v;
            ((float*)0x017189f0)[3] = v;
        }
        const float* m = (const float*)0x016f8b10;
        const float* n = (const float*)0x017189f0;
        float dx = m[0] * n[0] + m[4] * n[1] + m[8]  * n[2];
        float dy = m[1] * n[0] + m[5] * n[1] + m[9]  * n[2];
        float dz = m[2] * n[0] + m[6] * n[1] + m[10] * n[2];
        float len2 = dx * dx + dy * dy + dz * dz;
        float inv = 1.0f / sqrtf(len2);
        inv = inv + (*(float*)0x01485720 - len2 * (inv * inv)) * (inv * (*(float*)0x01471064));
        inv = inv + (*(float*)0x01485720 - len2 * (inv * inv)) * (inv * (*(float*)0x01471064));
        local.x = *(float*)((char*)p + 4) * inv;
    }
    RwDevBind(a, &local, 1, flag);
}

// ---------------------------------------------------------------------------
// 0x011fc3d0  bind TransformPoint of the translation row of a Matrix44
// ---------------------------------------------------------------------------
// @ 0x011fc3d0
void FUN_011fc3d0(u32 a, u32 b, int flag)
{
    const float* src = (const float*)*(void**)0x016fa5b8;
    Mat4 mat;
    mat = *(const Mat4*)src;
    Vec4 local;
    FUN_011fb950((float*)&local, &mat.m[12]);
    local.w = *(float*)0x01485720;                     // 1.0
    RwDevBind(a, &local, 1, flag);
}

// ---------------------------------------------------------------------------
// 0x011fc470  bind the CalcLightRange result
// ---------------------------------------------------------------------------
// @ 0x011fc470
void FUN_011fc470(u32 a, u32 b, int flag)
{
    Vec4 local;
    FUN_011fb230((float*)&local);
    RwDevBind(a, &local, 1, flag);
}
