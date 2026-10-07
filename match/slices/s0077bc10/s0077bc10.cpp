// Slice s0077bc10: rw::graphics shader-constant setter that uploads transpose(inverse(M)) for the
// 4x4 matrix M at 0x16f90d0 (rows at 0x16f90d0/0x16f90e0/0x16f90f0/0x16f9100, 16-byte aligned).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-  (__m128 locals would otherwise get a /GS cookie)
//
// Same shape as 0x77af70 (slice s0077a160), which does this for the matrix at 0x16f8be0: an inlined
// SSE cofactor inverse where every scalar is a splat vector, the reciprocal of the determinant is
// rcpps refined by two Newton steps, and when every lane of the determinant is 0 the inverse is not
// written (the uploaded block is then the uninitialised local, as in the original). The result is
// transposed with _MM_TRANSPOSE4_PS and handed to
//   isVS ? IDirect3DDevice9::SetVertexShaderConstantF(reg, data, count)   (vtable slot 94, +0x178)
//        : IDirect3DDevice9::SetPixelShaderConstantF (reg, data, count)   (vtable slot 109, +0x1b4)
// The cofactor and determinant expressions keep the original's operand association (read off the
// asm lane by lane), so the float results are bit-identical.
#include "types.h"
#include <xmmintrin.h>

struct Mat4 { __m128 r0, r1, r2, r3; };   // named rows (no array, so no /GS cookie)

extern Mat4  g_shConstMatrix;   // 0x16f90d0
extern void* g_pDevice;         // 0x16f89d0  rw::graphics::ActiveState::m_d3d9Device

struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))

static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }
static __forceinline __m128 SplatY(__m128 v) { return _mm_shuffle_ps(v, v, 0x55); }
static __forceinline __m128 SplatZ(__m128 v) { return _mm_shuffle_ps(v, v, 0xaa); }
static __forceinline __m128 SplatW(__m128 v) { return _mm_shuffle_ps(v, v, 0xff); }

#define MUL _mm_mul_ps
#define SUB _mm_sub_ps
#define ADD _mm_add_ps

// out = inverse(m) when the determinant is non-zero; returns false (out untouched) otherwise.
static __forceinline bool Invert(Mat4& out, const Mat4& m)
{
    const __m128 m00 = SplatX(m.r0), m01 = SplatY(m.r0), m02 = SplatZ(m.r0), m03 = SplatW(m.r0);
    const __m128 m10 = SplatX(m.r1), m11 = SplatY(m.r1), m12 = SplatZ(m.r1), m13 = SplatW(m.r1);
    const __m128 m20 = SplatX(m.r2), m21 = SplatY(m.r2), m22 = SplatZ(m.r2), m23 = SplatW(m.r2);
    const __m128 m30 = SplatX(m.r3), m31 = SplatY(m.r3), m32 = SplatZ(m.r3), m33 = SplatW(m.r3);

    __m128 d0 = ADD(ADD(MUL(SUB(MUL(m22, m33), MUL(m23, m32)), m11),
                        MUL(SUB(MUL(m31, m23), MUL(m21, m33)), m12)),
                    MUL(SUB(MUL(m21, m32), MUL(m31, m22)), m13));
    __m128 d1 = ADD(ADD(MUL(SUB(MUL(m23, m32), MUL(m22, m33)), m10),
                        MUL(SUB(MUL(m33, m20), MUL(m23, m30)), m12)),
                    MUL(m13, SUB(MUL(m30, m22), MUL(m20, m32))));
    __m128 d2 = ADD(ADD(MUL(m10, SUB(MUL(m33, m21), MUL(m23, m31))),
                        MUL(m11, SUB(MUL(m23, m30), MUL(m33, m20)))),
                    MUL(m13, SUB(MUL(m31, m20), MUL(m21, m30))));
    __m128 c30 = ADD(ADD(MUL(m10, SUB(MUL(m22, m31), MUL(m32, m21))),
                         MUL(m11, SUB(MUL(m32, m20), MUL(m22, m30)))),
                     MUL(m12, SUB(MUL(m21, m30), MUL(m31, m20))));
    __m128 det = ADD(ADD(ADD(MUL(d0, m00), MUL(m01, d1)), MUL(m02, d2)), MUL(m03, c30));

    if (_mm_movemask_ps(_mm_cmpeq_ps(_mm_set1_ps(0.0f), det)) == 0xf)
        return false;

    const __m128 two = _mm_set1_ps(2.0f);
    __m128 rcp = MUL(SUB(two, MUL(_mm_rcp_ps(det), det)), _mm_rcp_ps(det));
    rcp = MUL(SUB(two, MUL(rcp, det)), rcp);

    __m128 c00 = ADD(ADD(MUL(m11, SUB(MUL(m33, m22), MUL(m32, m23))),
                         MUL(m12, SUB(MUL(m23, m31), MUL(m33, m21)))),
                     MUL(m13, SUB(MUL(m32, m21), MUL(m22, m31))));
    __m128 c01 = ADD(ADD(MUL(SUB(MUL(m02, m33), MUL(m03, m32)), m21),
                         MUL(SUB(MUL(m03, m31), MUL(m01, m33)), m22)),
                     MUL(SUB(MUL(m01, m32), MUL(m02, m31)), m23));
    __m128 c02 = ADD(ADD(MUL(SUB(MUL(m02, m13), MUL(m03, m12)), m31),
                         MUL(SUB(MUL(m03, m11), MUL(m01, m13)), m32)),
                     MUL(SUB(MUL(m01, m12), MUL(m02, m11)), m33));
    __m128 c03 = ADD(ADD(MUL(SUB(MUL(m13, m22), MUL(m12, m23)), m01),
                         MUL(SUB(MUL(m11, m23), MUL(m13, m21)), m02)),
                     MUL(SUB(MUL(m12, m21), MUL(m11, m22)), m03));

    __m128 c10 = ADD(ADD(MUL(SUB(MUL(m20, m33), MUL(m30, m23)), m12),
                         MUL(SUB(MUL(m30, m22), MUL(m20, m32)), m13)),
                     MUL(SUB(MUL(m23, m32), MUL(m33, m22)), m10));
    __m128 c11 = ADD(ADD(MUL(SUB(MUL(m33, m00), MUL(m03, m30)), m22),
                         MUL(m23, SUB(MUL(m02, m30), MUL(m32, m00)))),
                     MUL(m20, SUB(MUL(m32, m03), MUL(m33, m02))));
    __m128 c12 = ADD(ADD(MUL(m32, SUB(MUL(m13, m00), MUL(m03, m10))),
                         MUL(m33, SUB(MUL(m02, m10), MUL(m12, m00)))),
                     MUL(m30, SUB(MUL(m12, m03), MUL(m13, m02))));
    __m128 c13 = ADD(ADD(MUL(m02, SUB(MUL(m13, m20), MUL(m23, m10))),
                         MUL(m03, SUB(MUL(m22, m10), MUL(m12, m20)))),
                     MUL(m00, SUB(MUL(m23, m12), MUL(m22, m13))));

    __m128 c20 = ADD(ADD(MUL(m13, SUB(MUL(m31, m20), MUL(m21, m30))),
                         MUL(m10, SUB(MUL(m33, m21), MUL(m23, m31)))),
                     MUL(m11, SUB(MUL(m23, m30), MUL(m33, m20))));
    __m128 c21 = ADD(ADD(MUL(m23, SUB(MUL(m31, m00), MUL(m01, m30))),
                         MUL(m20, SUB(MUL(m33, m01), MUL(m31, m03)))),
                     MUL(m21, SUB(MUL(m03, m30), MUL(m33, m00))));
    __m128 c22 = ADD(ADD(MUL(m33, SUB(MUL(m11, m00), MUL(m01, m10))),
                         MUL(m30, SUB(MUL(m13, m01), MUL(m11, m03)))),
                     MUL(m31, SUB(MUL(m03, m10), MUL(m13, m00))));
    __m128 c23 = ADD(ADD(MUL(m03, SUB(MUL(m11, m20), MUL(m21, m10))),
                         MUL(m00, SUB(MUL(m21, m13), MUL(m23, m11)))),
                     MUL(m01, SUB(MUL(m23, m10), MUL(m13, m20))));

    __m128 c31 = ADD(ADD(MUL(m20, SUB(MUL(m31, m02), MUL(m32, m01))),
                         MUL(m21, SUB(MUL(m32, m00), MUL(m02, m30)))),
                     MUL(m22, SUB(MUL(m01, m30), MUL(m31, m00))));
    __m128 c32 = ADD(ADD(MUL(m30, SUB(MUL(m02, m11), MUL(m01, m12))),
                         MUL(SUB(MUL(m00, m12), MUL(m10, m02)), m31)),
                     MUL(SUB(MUL(m10, m01), MUL(m00, m11)), m32));
    __m128 c33 = ADD(ADD(MUL(SUB(MUL(m11, m22), MUL(m12, m21)), m00),
                         MUL(SUB(MUL(m20, m12), MUL(m10, m22)), m01)),
                     MUL(SUB(MUL(m10, m21), MUL(m20, m11)), m02));

    out.r0 = _mm_setr_ps(_mm_cvtss_f32(MUL(c00, rcp)), _mm_cvtss_f32(MUL(c01, rcp)),
                           _mm_cvtss_f32(MUL(c02, rcp)), _mm_cvtss_f32(MUL(c03, rcp)));
    out.r1 = _mm_setr_ps(_mm_cvtss_f32(MUL(c10, rcp)), _mm_cvtss_f32(MUL(c11, rcp)),
                           _mm_cvtss_f32(MUL(c12, rcp)), _mm_cvtss_f32(MUL(c13, rcp)));
    out.r2 = _mm_setr_ps(_mm_cvtss_f32(MUL(c20, rcp)), _mm_cvtss_f32(MUL(c21, rcp)),
                           _mm_cvtss_f32(MUL(c22, rcp)), _mm_cvtss_f32(MUL(c23, rcp)));
    out.r3 = _mm_setr_ps(_mm_cvtss_f32(MUL(c30, rcp)), _mm_cvtss_f32(MUL(c31, rcp)),
                           _mm_cvtss_f32(MUL(c32, rcp)), _mm_cvtss_f32(MUL(c33, rcp)));
    return true;
}

#undef MUL
#undef SUB
#undef ADD

// @ 0x0077bc10  rw::graphics::RWShader_SetShConst_lightBlock (uploads transpose(inverse(M)))
void __cdecl FUN_0077bc10(unsigned reg, unsigned count, int isVS)
{
    Mat4 inv;
    Invert(inv, g_shConstMatrix);
    _MM_TRANSPOSE4_PS(inv.r0, inv.r1, inv.r2, inv.r3);
    if (isVS)
        SETVS(g_pDevice, reg, (const float*)&inv, count);
    else
        SETPS(g_pDevice, reg, (const float*)&inv, count);
}
