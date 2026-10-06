// Slice s0077a160: rw::graphics::ActiveState shader-constant setters that upload the inverse of the
// active 4x4 matrix (6826 bytes of SSE in the original = two adjacent functions, 0x77a160 and 0x77af70).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Both functions are __cdecl (reg, count, isVS) and finish with
//   isVS ? IDirect3DDevice9::SetVertexShaderConstantF(reg, data, count)   (vtable slot 94, +0x178)
//        : IDirect3DDevice9::SetPixelShaderConstantF (reg, data, count)   (vtable slot 109, +0x1b4)
// where data is a 4x4 block of floats.
//   0x77a160: data = transpose( inverse(M) * Binv ), Binv = ActiveState::m_inverseTransform (built lazily
//             from m_transform with Matrix4_invert and cached in the scratch matrix at 0x1632c90).
//   0x77af70: data = transpose( inverse(M) ).
// M is the 4x4 float matrix at 0x16f8be0 (row-major, 16-byte aligned).  inverse() is a cofactor/determinant
// inverse whose reciprocal of the determinant is rcpps refined by two Newton steps; if det == 0 the
// original leaves the inverse uninitialised (stack garbage), here it is zero.
#include "types.h"
#include <xmmintrin.h>

// ---- globals (rw::graphics::ActiveState and friends) --------------------------------------------
extern float*       g_transform;           // 0x16f85ac  ActiveState::m_transform (Matrix44Affine*)
extern int          g_transformType;       // 0x16f8b50  ActiveState::m_transformType (MatrixType)
extern const float* g_inverseTransform;    // 0x16f9120  ActiveState::m_inverseTransform (lazily built)
extern float        g_invScratch[16];      // 0x1632c90  storage for the cached inverse transform
extern float        g_M[16];               // 0x16f8be0  the 4x4 matrix that is inverted
extern void*        g_pDevice;             // 0x16f89d0  ActiveState::m_d3d9Device

// rw::math Matrix4 invert (slice s00778060): returns a pointer to the inverse (out or the input).
float* __cdecl Matrix4_invert(float* out, const float* m, int type);   // @ 0x778060

struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))

// 3x3 minor of the 4x4 matrix m (row-major) with row r and column c removed.
static float Minor3(const float* m, int r, int c) {
    float a[9];
    int k = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == r) continue;
        for (int j = 0; j < 4; ++j) {
            if (j == c) continue;
            a[k++] = m[i * 4 + j];
        }
    }
    return a[0] * (a[4] * a[8] - a[5] * a[7])
         - a[1] * (a[3] * a[8] - a[5] * a[6])
         + a[2] * (a[3] * a[7] - a[4] * a[6]);
}

// 1/det with the rcpps estimate refined by two Newton steps, as in the original.
static float RcpRefined(float d) {
    __m128 x = _mm_set1_ps(d);
    __m128 two = _mm_set1_ps(2.0f);
    __m128 r = _mm_rcp_ps(x);
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), _mm_rcp_ps(x));
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), r);
    return _mm_cvtss_f32(r);
}

// n = inverse(m) (row-major).  Leaves n zeroed when the determinant is 0.
static void Inverse44(const float* m, float* n) {
    float c[16];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            c[i * 4 + j] = (((i + j) & 1) ? -1.0f : 1.0f) * Minor3(m, i, j);   // cofactor C(i,j)
    float det = ((c[0] * m[0] + c[1] * m[1]) + c[2] * m[2]) + c[3] * m[3];     // expansion along row 0
    for (int k = 0; k < 16; ++k) n[k] = 0.0f;
    if (det != 0.0f) {
        float r = RcpRefined(det);
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                n[i * 4 + j] = c[j * 4 + i] * r;                                // adj = cofactor^T
    }
}

// Upload data[0..15] = transpose(v) (v row-major) to the vertex or pixel shader constant registers.
static void UploadTransposed(const float* v, unsigned reg, unsigned count, int isVS) {
    float data[16];
    for (int j = 0; j < 4; ++j)
        for (int k = 0; k < 4; ++k)
            data[j * 4 + k] = v[k * 4 + j];
    if (isVS) SETVS(g_pDevice, reg, data, count);
    else      SETPS(g_pDevice, reg, data, count);
}

// @ 0x0077a160  rw::graphics::RWShader_SetShConst_transformBlock
void __cdecl FUN_0077a160(unsigned reg, unsigned count, int isVS) {
    if (g_inverseTransform == 0) {                       // build and cache the inverse of m_transform
        for (int i = 0; i < 16; ++i) g_invScratch[i] = g_transform[i];
        float tmp[19];
        const float* inv = Matrix4_invert(tmp, g_invScratch, g_transformType);
        for (int i = 0; i < 16; ++i) g_invScratch[i] = inv[i];
        g_inverseTransform = g_invScratch;
    }
    const float* B = g_inverseTransform;
    float n[16];
    Inverse44(g_M, n);
    float v[16];                                         // v = n * B (row k = n.row(k) * B)
    for (int k = 0; k < 4; ++k) {
        for (int j = 0; j < 4; ++j) {
            v[k * 4 + j] = B[12 + j] * n[k * 4 + 3]
                         + (n[k * 4 + 2] * B[8 + j]
                         + (B[4 + j] * n[k * 4 + 1] + B[j] * n[k * 4 + 0]));
        }
    }
    UploadTransposed(v, reg, count, isVS);
}

// @ 0x0077af70  (second routine inside the 6826-byte region: uploads transpose(inverse(M)))
void __cdecl FUN_0077af70(unsigned reg, unsigned count, int isVS) {
    float n[16];
    Inverse44(g_M, n);
    UploadTransposed(n, reg, count, isVS);
}
