// src/game/SPEngine/SPGraphicsSHUtilities.cpp -- migrated from slice(s) s00795ec0, s00794e80, s00794610, s007864c0, s00785500, s00784560, s00784420, s00783590 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsSHUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cImageData32.h"
#include "rw/math/vpu/Vector4.h"

// unnamed retail callees and globals (address in the comment)
extern float kSH_Y_00, kSH_Y_1x;
extern float kSH_Y_2_2, kSH_Y_2_1, kSH_Y_20, kSH_Y_21, kSH_Y_22;
extern float kSH_Y_3_3, kSH_Y_3_2, kSH_Y_3_1, kSH_Y_30, kSH_Y_31, kSH_Y_32, kSH_Y_33;
extern float kSH_Y_4_4, kSH_Y_4_3, kSH_Y_4_2, kSH_Y_4_1, kSH_Y_40, kSH_Y_41, kSH_Y_42, kSH_Y_43, kSH_Y_44;
extern float g_153ae10;
extern char  kBasisTriples3, kBasisTriples4, kBasisTriples5;
#include <math.h>
#include <string.h>
#include <xmmintrin.h>
#pragma intrinsic(sqrt)

// cl15 does not inline `sqrt` in this TU (the original ends each term with an x87 fsqrt);
// shSqrt gives the same single-precision result without a CRT call.
static inline float shSqrt(const float* p) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_load_ss(p))); }

// ---- items of slice s00783590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kSH_Y_00, kSH_Y_1x;
extern float kSH_Y_2_2, kSH_Y_2_1, kSH_Y_20, kSH_Y_21, kSH_Y_22;
extern float kSH_Y_3_3, kSH_Y_3_2, kSH_Y_3_1, kSH_Y_30, kSH_Y_31, kSH_Y_32, kSH_Y_33;
extern float kSH_Y_4_4, kSH_Y_4_3, kSH_Y_4_2, kSH_Y_4_1, kSH_Y_40, kSH_Y_41, kSH_Y_42, kSH_Y_43, kSH_Y_44;
extern float g_153ae10;
extern char  kBasisTriples3, kBasisTriples4, kBasisTriples5;
void SP_MultiplySH(int n, int a, int b, void* out, char* triples);
// ---- items of slice s00783590 end

// ---- items of slice s00784420 begin (TODO(rewrite): local stubs, replace by canonical classes)
void FUN_00783380(float* out);                       // build 7 SH constants
void SP_MirrorSHInZ(int n, float* data);
void SP_ApplyDiffuseReflection(int n, const float* lit, const float* diff, float* out);
void FUN_0011e073e(void* buf, int zero, unsigned int size);
// ---- items of slice s00784420 end

// ---- items of slice s00784560 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_01634104, g_016340dc, g_01634078, g_016340cc, g_016341e0, g_016341b0, g_01634150,
    g_016340b0, g_016340fc, g_0163409c, g_016341dc, g_016340d4, g_01634130, g_016340e8, g_01634074,
    g_016340ec, g_016340f8, g_0163410c, g_01634168, g_01634134, g_016340e4, g_016340a8, g_01634064,
    g_0163405c, g_0163407c;
// ---- items of slice s00784560 end

// ---- items of slice s00785500 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float k05c;  // 0x0163405c
extern float k064;  // 0x01634064
extern float k074;  // 0x01634074
    extern float k078; // 0x01634078
extern float k07c;  // 0x0163407c
extern float k09c;  // 0x0163409c
extern float k0a8;  // 0x016340a8
extern float k0b0;  // 0x016340b0
    extern float k0cc; // 0x016340cc
extern float k0d4;  // 0x016340d4
    extern float k0dc; // 0x016340dc
extern float k0e4;  // 0x016340e4
extern float k0e8;  // 0x016340e8
extern float k0ec;  // 0x016340ec
extern float k0f8;  // 0x016340f8
extern float k0fc;  // 0x016340fc
    extern float k104; // 0x01634104
extern float k10c;  // 0x0163410c
extern float k130;  // 0x01634130
extern float k134;  // 0x01634134
    extern float k150; // 0x01634150
extern float k168;  // 0x01634168
extern float k1b0;  // 0x016341b0
extern float k1dc;  // 0x016341dc
extern float k1e0;  // 0x016341e0
static inline double S(double v) { return sqrt(v); }
// ---- items of slice s00785500 end

// ---- items of slice s007864c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float k_1634054;
extern float k_163405c;
extern float k_1634064;
extern float k_1634074;
extern float k_1634078;
extern float k_163407c;
extern float k_1634080;
extern float k_1634084;
extern float k_1634094;
extern float k_1634098;
extern float k_163409c;
extern float k_16340a8;
extern float k_16340ac;
extern float k_16340b0;
extern float k_16340b4;
extern float k_16340bc;
extern float k_16340cc;
extern float k_16340d4;
extern float k_16340dc;
extern float k_16340e4;
extern float k_16340e8;
extern float k_16340ec;
extern float k_16340f8;
extern float k_16340fc;
extern float k_1634104;
extern float k_163410c;
extern float k_1634114;
extern float k_1634120;
extern float k_1634130;
extern float k_1634134;
extern float k_1634150;
extern float k_1634168;
extern float k_16341b0;
extern float k_16341dc;
extern float k_16341e0;
extern float k_16341ec;
extern float k_16341f4;
namespace rw {
namespace math {
namespace vpu {
struct __declspec(align(16)) Vector4_s0078_64c0 { float x, y, z, w; };
}
}
}
using rw::math::vpu::Vector4_s0078_64c0;
Vector4_s0078_64c0 MulRow3(const Vector4_s0078_64c0* v, const float* row);   // 0x00782c90 (equiv t3)
Vector4_s0078_64c0 WeightedSum(int n, const Vector4_s0078_64c0* v, const float* w);   // 0x00782ce0 (equiv t2)
namespace SP {
template <class T>
void RotateSH(const float* m, int order, const T* in, T* out);  // namespace SP
}
// ---- items of slice s007864c0 end

// ---- items of slice s00794e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float DAT_01634104;
extern const float DAT_016340dc;
extern const float DAT_01634078;
extern const float _DAT_016340cc;
extern const float DAT_016341e0;
extern const float DAT_016341b0;
extern const float DAT_01634150;
extern const float DAT_016340b0;
extern const float DAT_016340fc;
extern const float _DAT_0163409c;
extern const float DAT_016341dc;
extern const float DAT_016340d4;
extern const float DAT_01634130;
extern const float DAT_016340e8;
extern const float DAT_01634074;
extern const float DAT_016340ec;
extern const float DAT_016340f8;
extern const float _DAT_01634134;
extern const float _DAT_0163410c;
extern const float _DAT_01634168;
extern const float _DAT_016340e4;
extern const float _DAT_016340a8;
extern const float _DAT_01634064;
extern const float _DAT_0163405c;
extern const float _DAT_0163407c;
// ---- items of slice s00794e80 end

// ---- items of slice s00795ec0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float DAT_016340e0;
extern const float DAT_016341d8;
extern const float DAT_01634068;
extern const float DAT_01634108;
extern const float DAT_0153ae10;
extern const float DAT_0140ebdc;
extern const float DAT_0140ebd8;
extern const float DAT_0140ebd4;
extern const float DAT_0140ebd0;
extern const float DAT_0140ebcc;
extern const float DAT_0140ebc8;
extern const float DAT_0140ebc4;
extern int DAT_0140eae8[];
extern unsigned char DAT_0140eac4;
extern unsigned char DAT_0140eac5;
extern unsigned char DAT_0140eac6;
extern float __cdecl AddColourSample(float *, int, float *, int);
extern void __cdecl RotateZHToSHAddT(float *, int, float *, int);
extern float* __cdecl CalcHGPhaseZH(float, void *, int, void *);
extern float* __cdecl CalcHGPhaseZHAdd(float, void *, int, void *);
extern void __cdecl MultiplyZH(int, void *, void *, int, void *);
extern char _kBasisTriples3[];
extern char _kBasisTriples4[];
extern char _kBasisTriples5[];
// ---- items of slice s00795ec0 end

// @ 0x00783590
void ApplyNormalizationConstants(int order, float* v)
{
#define MUL4(c, o) do { float a=v[(o)+1], b=v[(o)+2], d=v[(o)+3]; v[(o)]=(c)*v[(o)]; v[(o)+1]=(c)*a; v[(o)+2]=(c)*b; v[(o)+3]=(c)*d; } while(0)
    MUL4(kSH_Y_00, 0);
    if (1 < order) {
        MUL4(kSH_Y_1x, 4);
        float y1 = kSH_Y_1x;
        v[8] = y1 * v[8]; v[9] = y1 * v[9]; v[0xa] = y1 * v[0xa]; v[0xb] = y1 * v[0xb];
        v[0xc] = y1 * v[0xc]; v[0xd] = y1 * v[0xd]; v[0xe] = y1 * v[0xe]; v[0xf] = y1 * v[0xf];
        if (2 < order) {
            MUL4(kSH_Y_2_2, 0x10);
            MUL4(kSH_Y_2_1, 0x14);
            MUL4(kSH_Y_20, 0x18);
            MUL4(kSH_Y_21, 0x1c);
            MUL4(kSH_Y_22, 0x20);
            if (3 < order) {
                MUL4(kSH_Y_3_3, 0x24);
                MUL4(kSH_Y_3_2, 0x28);
                MUL4(kSH_Y_3_1, 0x2c);
                MUL4(kSH_Y_30, 0x30);
                MUL4(kSH_Y_31, 0x34);
                MUL4(kSH_Y_32, 0x38);
                MUL4(kSH_Y_33, 0x3c);
                if (4 < order) {
                    MUL4(kSH_Y_4_4, 0x40);
                    MUL4(kSH_Y_4_3, 0x44);
                    MUL4(kSH_Y_4_2, 0x48);
                    MUL4(kSH_Y_4_1, 0x4c);
                    MUL4(kSH_Y_40, 0x50);
                    MUL4(kSH_Y_41, 0x54);
                    MUL4(kSH_Y_42, 0x58);
                    MUL4(kSH_Y_43, 0x5c);
                    MUL4(kSH_Y_44, 0x60);
                }
            }
        }
    }
#undef MUL4
}

// @ 0x00783830
void RemoveNormalizationConstants(int order, float* v)
{
#define MUL4(c, o) do { float a=1.0f/(c); v[(o)]=a*v[(o)]; v[(o)+1]=a*v[(o)+1]; v[(o)+2]=a*v[(o)+2]; v[(o)+3]=a*v[(o)+3]; } while(0)
    MUL4(kSH_Y_00, 0);
    if (1 < order) {
        float a = 1.0f / kSH_Y_1x;
        v[4] = a * v[4]; v[5] = a * v[5]; v[6] = a * v[6]; v[7] = a * v[7];
        v[8] = a * v[8]; v[9] = a * v[9]; v[0xa] = a * v[0xa]; v[0xb] = a * v[0xb];
        v[0xc] = a * v[0xc]; v[0xd] = a * v[0xd]; v[0xe] = a * v[0xe]; v[0xf] = a * v[0xf];
        if (2 < order) {
            MUL4(kSH_Y_2_2, 0x10);
            MUL4(kSH_Y_2_1, 0x14);
            MUL4(kSH_Y_20, 0x18);
            MUL4(kSH_Y_21, 0x1c);
            MUL4(kSH_Y_22, 0x20);
            if (3 < order) {
                MUL4(kSH_Y_3_3, 0x24);
                MUL4(kSH_Y_3_2, 0x28);
                MUL4(kSH_Y_3_1, 0x2c);
                MUL4(kSH_Y_30, 0x30);
                MUL4(kSH_Y_31, 0x34);
                MUL4(kSH_Y_32, 0x38);
                MUL4(kSH_Y_33, 0x3c);
                if (4 < order) {
                    MUL4(kSH_Y_4_4, 0x40);
                    MUL4(kSH_Y_4_3, 0x44);
                    MUL4(kSH_Y_4_2, 0x48);
                    MUL4(kSH_Y_4_1, 0x4c);
                    MUL4(kSH_Y_40, 0x50);
                    MUL4(kSH_Y_41, 0x54);
                    MUL4(kSH_Y_42, 0x58);
                    MUL4(kSH_Y_43, 0x5c);
                    MUL4(kSH_Y_44, 0x60);
                }
            }
        }
    }
#undef MUL4
}

// @ 0x00783b20 -- eax holds the end of the degree-6+ tail run (or the accumulator start)
float* ApplyDiffuseReflection(int order, const float* lit, const float* diff, float* out)
{
    // The original works four lanes at a time: every band factor is a packed
    // (lit * bandConstant + diff) vector, and bands 3 and 5 just scale by diff.
    float* p = out;
    float* end = out;
    _mm_store_ps(p, _mm_mul_ps(_mm_add_ps(_mm_load_ps(lit), _mm_load_ps(diff)), _mm_load_ps(p)));
    if (order < 2)
        return end;
    __m128 m = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(0.6666667f), _mm_load_ps(lit)), _mm_load_ps(diff));
    for (int i = 0; i < 3; ++i) {
        p += 4;
        _mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), m));
    }
    if (order < 3)
        return end;
    m = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(0.25f), _mm_load_ps(lit)), _mm_load_ps(diff));
    for (int i = 0; i < 5; ++i) {
        p += 4;
        _mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), m));
    }
    if (order < 4)
        return end;
    for (int i = 0; i < 7; ++i) {
        p += 4;
        _mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), _mm_load_ps(diff)));
    }
    if (order < 5)
        return end;
    m = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(-0.041666668f), _mm_load_ps(lit)), _mm_load_ps(diff));
    for (int i = 0; i < 9; ++i) {
        p += 4;
        _mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), m));
    }
    int n = order * order;
    if (order < 6 || n <= 0x19)
        return end;
    p = out + 100;
    for (int k = n - 0x19; k != 0; --k) {
        _mm_store_ps(p, _mm_mul_ps(_mm_load_ps(p), _mm_load_ps(diff)));
        p += 4;
    }
    return p;
}

// @ 0x00783c90
void MirrorSHInZ(int n, float* data)
{
    for (int i = 0; i < n; ++i) {
        for (int j = -i; j <= i; ++j) {
            if ((i + j) & 1) {
                int idx = (i + 1) * i + j;
                float* p = data + idx * 4;
                __m128 v = _mm_load_ps(p);
                __m128 neg = _mm_sub_ps(_mm_setzero_ps(), v);
                _mm_store_ps(p, neg);
            }
        }
    }
}

// Shared helpers for the sparse SH product-table multiply below.  One SH projection
// group (four coefficients) lives at base + index * 16 bytes.
static inline const float* shp(const void* base, int idx) { return (const float*)((const char*)base + idx * 16); }
static inline float* shm(void* base, int idx) { return (float*)((char*)base + idx * 16); }

// One entry of the sparse SH product table: basis indices i, j, k plus the weight.
struct SHTriple { signed char i, j, k; float w; };

// out[acc] += a[i] * b[j] * w  (the two factors share one basis function only when i == j)
static inline void shAddDiagonal(float* po, const char* pa, const char* pb, int acc, int i, int j, float wt)
{
    __m128 v = _mm_mul_ps(_mm_set1_ps(wt), _mm_load_ps(shp(pa, i)));
    v = _mm_mul_ps(v, _mm_load_ps(shp(pb, j)));
    v = _mm_add_ps(v, _mm_load_ps(shm(po, acc)));
    _mm_store_ps(shm(po, acc), v);
}

// out[acc] += (b[i] * a[j] + a[i] * b[j]) * w
static inline void shAddCross(float* po, const char* pa, const char* pb, int acc, int i, int j, float wt)
{
    __m128 v = _mm_mul_ps(_mm_load_ps(shp(pb, i)), _mm_load_ps(shp(pa, j)));
    v = _mm_add_ps(v, _mm_mul_ps(_mm_load_ps(shp(pa, i)), _mm_load_ps(shp(pb, j))));
    v = _mm_mul_ps(v, _mm_set1_ps(wt));
    v = _mm_add_ps(v, _mm_load_ps(shm(po, acc)));
    _mm_store_ps(shm(po, acc), v);
}

// @ 0x00783cf0
void SP_MultiplySH(int count, int a, int b, void* out, char* triples)
{
    const char* pa = (const char*)a;
    const char* pb = (const char*)b;
    char* po = (char*)out;
    memset(po, 0, count * 16);
    for (const char* e = triples; ((const SHTriple*)e)->i >= 0; e += 8) {
        const SHTriple* t = (const SHTriple*)e;
        if (t->i == t->j) {
            shAddDiagonal((float*)po, pa, pb, t->k, t->i, t->j, t->w);
            if (t->j == t->k)
                continue;
            shAddCross((float*)po, pa, pb, t->i, t->j, t->k, t->w);
        } else if (t->j == t->k) {
            shAddDiagonal((float*)po, pa, pb, t->i, t->j, t->j, t->w);
            shAddCross((float*)po, pa, pb, t->j, t->i, t->k, t->w);
        } else {
            shAddCross((float*)po, pa, pb, t->i, t->j, t->k, t->w);
            shAddCross((float*)po, pa, pb, t->j, t->i, t->k, t->w);
            shAddCross((float*)po, pa, pb, t->k, t->j, t->i, t->w);
        }
    }
}

// @ 0x00783f40
void FUN_00783f40(int order, int a, int b, void* out)
{
    switch (order) {
    case 3: SP_MultiplySH(9, a, b, out, &kBasisTriples3); break;
    case 4: SP_MultiplySH(0x10, a, b, out, &kBasisTriples4); break;
    case 5: SP_MultiplySH(0x19, a, b, out, &kBasisTriples5); break;
    }
}

// @ 0x00783fb0
namespace SP {
void FindSHCoeffsFromHemiEnvMap(cImageData32 const * env, int order, rw::math::vpu::Vector4 * out)
{
    int env_v = (int)env;
    int w = *(int*)(env_v + 0x1c);
    int h = *(int*)(env_v + 0x20);
    float scale = (g_153ae10 * 2.0f) / (float)w;
    for (int y = 0; y < h; ++y) {
        float ny = 1.0f - ((float)y + 0.5f + (float)y + 0.5f) / (float)h;
        for (int x = 0; x < w; ++x) {
            float nx = ((float)x + 0.5f + (float)x + 0.5f) / (float)w - 1.0f;
            float r2 = nx * nx + ny * ny;
            if (r2 <= 1.0f) {
                // omitted: texture sample, Legendre evaluation and 4-channel accumulate
                (void)scale;
                (void)order;
                (void)out;
            }
        }
    }
}
}  // namespace SP

// @ 0x00784330 -- returns the end of the written range (original leaves it in eax;
// with an empty range eax is still the source pointer it loaded the seed qword from)
float* CalcHGPhaseZH(float a, const float* src, int order, float* dst)
{
    float* p = (float*)src;
    __m128 x = _mm_load_ps(p);
    if (order > 0) {
        p = dst;
        __m128 br = _mm_set1_ps(a);
        int i = 1;
        do {
            float t = (float)((double)i * g_153ae10 * 4.0f);
            __m128 scale = _mm_set1_ps(shSqrt(&t));
            _mm_store_ps(p, _mm_mul_ps(scale, x));
            x = _mm_mul_ps(br, x);
            p += 4;
            i += 2;
            order--;
        } while (order != 0);
        return p;
    }
    return (float*)src;
}

// @ 0x007843a0 -- additive variant, returns the end of the written range (eax keeps the
// source pointer when the range is empty, as in the non-additive variant)
float* CalcHGPhaseZHAdd(float a, const float* src, int order, float* dst)
{
    float* p = (float*)src;
    __m128 x = _mm_load_ps(p);
    if (order > 0) {
        p = dst;
        __m128 br = _mm_set1_ps(a);
        int i = 1;
        do {
            float t = (float)((double)i * g_153ae10 * 4.0f);
            __m128 scale = _mm_set1_ps(shSqrt(&t));
            _mm_store_ps(p, _mm_add_ps(_mm_mul_ps(scale, x), _mm_load_ps(p)));
            x = _mm_mul_ps(br, x);
            p += 4;
            i += 2;
            order--;
        } while (order != 0);
        return p;
    }
    return (float*)src;
}

// @ 0x00784420
void SP_AddGroundBounce(int order, float* sh, const float* lit, const float* diff)
{
    int n = order * order;
    float consts[7];
    float basis[103];
    float work[100];

    FUN_00783380(consts);
    FUN_0011e073e(work, 0, (unsigned int)(n * 0x10));

    for (int i = 0; i < order; ++i) {
        int idx = (i + 1) * i;
        *(__m128*)(work + idx * 4) = _mm_set1_ps(consts[i]);
    }

    switch (order) {
    case 3: SP_MultiplySH(9, (int)sh, (int)work, basis, &kBasisTriples3); break;
    case 4: SP_MultiplySH(0x10, (int)sh, (int)work, basis, &kBasisTriples4); break;
    case 5: SP_MultiplySH(0x19, (int)sh, (int)work, basis, &kBasisTriples5); break;
    }

    if (0 < n) {
        float* dst = sh;
        float* src = basis;
        for (int i = n * 4; i != 0; --i)
            *dst++ = *src++;
    }

    SP_MirrorSHInZ(order, sh);
    SP_ApplyDiffuseReflection(order, lit, diff, sh);

    if (0 < n) {
        float* d = sh;
        float* s = basis;
        for (int i = n; i != 0; --i) {
            _mm_store_ps(d, _mm_add_ps(_mm_load_ps(s), _mm_load_ps(d)));
            d += 4;
            s += 4;
        }
    }
}

// @ 0x00784560
void SHEvalBands(const float* param_1, int param_2, const __m128* c, __m128* out)
{
  float A[16];
  float B[16];
  float x, y, z;
  __m128 cv;
  int oi;
  out[0] = c[0];
  if (1 < param_2) {
    y = param_1[1];
    z = param_1[2];
    x = param_1[0];
    cv = c[1];
    out[1] = _mm_mul_ps(_mm_set1_ps(y), cv);
    out[2] = _mm_mul_ps(_mm_set1_ps(z), cv);
    out[3] = _mm_mul_ps(_mm_set1_ps(x), cv);
    if (2 < param_2) {
      A[0] = ((x * y) * 2.0f) * g_01634104;
      A[1] = ((z * y) * 2.0f) * g_01634104;
      A[2] = z * z - (y * y + x * x) * g_016340dc;
      oi = 4;
      A[3] = ((x * z) * 2.0f) * g_01634104;
      A[4] = (x * x - y * y) * g_01634104;
      cv = c[2];
      for (int i = 0; i < 5; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(A[i]), cv);
      if (3 < param_2) {
        B[0] = (A[4] * y + A[0] * x) * g_01634078;
        B[1] = ((A[1] * x + A[3] * y) + A[0] * z) *
                      g_016340cc;
        B[2] = ((g_016341e0 * A[1]) * z -
                      (A[0] * x - A[4] * y) * g_016341b0) +
                      (g_01634150 * A[2]) * y;
        B[3] = A[2] * z -
                      (A[1] * y + A[3] * x) * g_016340b0;
        B[4] = ((g_01634150 * A[2]) * x -
                      (A[0] * y + A[4] * x) * g_016341b0) +
                      (g_016341e0 * A[3]) * z;
        B[5] = ((A[3] * x - A[1] * y) + A[4] * z) *
                      g_016340cc;
        B[6] = (A[4] * x - A[0] * y) * g_01634078;
        oi = 9;
        cv = c[3];
        for (int i = 0; i < 7; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(B[i]), cv);
        if (4 < param_2) {
          A[0] = (B[6] * y + B[0] * x) * g_016340fc;
          A[1] = (B[5] * y + B[1] * x) * g_0163409c +
                         (g_016341dc * B[0]) * z;
          A[2] = ((B[2] * x + B[4] * y) * g_016340d4 -
                         (B[0] * x - B[6] * y) * g_01634130) +
                         (g_01634104 * B[1]) * z;
          A[3] = ((g_016340e8 * B[2]) * z -
                         (B[1] * x - B[5] * y) * g_01634074) +
                         (g_016340ec * B[3]) * y;
          A[4] = B[3] * z -
                         (B[2] * y + B[4] * x) * g_016340f8;
          A[5] = ((g_016340ec * B[3]) * x -
                         (B[1] * y + B[5] * x) * g_01634074) +
                         (g_016340e8 * B[4]) * z;
          oi = 16;
          A[6] = ((B[4] * x - B[2] * y) * g_016340d4 -
                         (B[0] * y + B[6] * x) * g_01634130) +
                         (g_01634104 * B[5]) * z;
          A[7] = (B[5] * x - B[1] * y) * g_0163409c +
                         (g_016341dc * B[6]) * z;
          cv = c[4];
          A[8] = (B[6] * x - B[0] * y) * g_016340fc;
          for (int i = 0; i < 9; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(A[i]), cv);
          if (5 < param_2) {
            oi = 25;
            B[0] = (A[8] * y + A[0] * x) * sqrt(9.0/10.0);
            B[1] = (z * A[0]) * sqrt(9.0/25.0) +
                          (A[7] * y + A[1] * x) * g_01634134;
            B[2] = (A[1] * z) * sqrt(16.0/25.0) +
                          ((A[6] * y + A[2] * x) * g_0163410c -
                          (A[0] * x - A[8] * y) * g_01634168);
            B[3] = (A[2] * z) * sqrt(21.0/25.0) +
                          ((A[5] * y + A[3] * x) * g_016340e4 -
                          (A[1] * x - A[7] * y) * g_016340a8);
            B[4] = (A[3] * z) * sqrt(24.0/25.0) +
                          ((A[4] * g_01634064) * y -
                          (A[2] * x - A[6] * y) * g_0163405c);
            B[5] = A[4] * z -
                          (A[3] * y + A[5] * x) * sqrt(2.0/5.0);
            B[6] = (A[5] * z) * sqrt(24.0/25.0) +
                          ((A[4] * g_01634064) * x -
                          (A[2] * y + A[6] * x) * g_0163405c);
            B[7] = (A[6] * z) * sqrt(21.0/25.0) +
                          ((A[5] * x - A[3] * y) * g_016340e4 -
                          (A[1] * y + A[7] * x) * g_016340a8);
            B[8] = (A[7] * z) * sqrt(16.0/25.0) +
                          ((A[6] * x - A[2] * y) * g_0163410c -
                          (A[0] * y + A[8] * x) * g_01634168);
            cv = c[5];
            B[9] = (A[8] * z) * sqrt(9.0/25.0) +
                          (A[7] * x - A[1] * y) * g_01634134;
            B[10] = (A[8] * x - A[0] * y) * sqrt(9.0/10.0);
            for (int i = 0; i < 11; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(B[i]), cv);
            if (param_2 < 7) {
              return;
            }
            oi = 36;
            A[0] = (B[0] * x + B[10] * y) * sqrt(11.0/12.0);
            A[1] = (B[0] * z) * sqrt(11.0/36.0) +
                           (B[9] * y + B[1] * x) * sqrt(55.0/72.0);
            A[2] = ((B[1] * g_016340cc) * z +
                           (B[8] * y + B[2] * x) * g_016340ec) -
                           (B[0] * x - B[10] * y) * sqrt(1.0/72.0);
            A[3] = (B[2] * g_01634104) * z +
                           ((B[3] * x + B[7] * y) * sqrt(1.0/2.0) -
                           (B[1] * x - B[9] * y) * sqrt(1.0/24.0));
            A[4] = (B[3] * g_016341e0) * z +
                           ((B[6] * y + B[4] * x) * sqrt(7.0/18.0) -
                           (B[2] * x - B[8] * y) * g_0163407c);
            A[5] = y * (B[5] * sqrt(7.0/12.0)) +
                           ((B[4] * z) * sqrt(35.0/36.0) -
                           (B[3] * x - B[7] * y) * sqrt(5.0/36.0));
            A[6] = B[5] * z -
                           (B[4] * y + B[6] * x) * sqrt(5.0/12.0);
            A[7] = (B[6] * z) * sqrt(35.0/36.0) +
                           (x * (B[5] * sqrt(7.0/12.0)) -
                           (B[3] * y + B[7] * x) * sqrt(5.0/36.0));
            cv = c[6];
            A[8] = (B[7] * g_016341e0) * z +
                           ((B[6] * x - B[4] * y) * sqrt(7.0/18.0) -
                           (B[2] * y + B[8] * x) * g_0163407c);
            A[9] = (B[8] * g_01634104) * z +
                           ((B[7] * x - B[3] * y) * sqrt(1.0/2.0) -
                           (B[1] * y + B[9] * x) * sqrt(1.0/24.0));
            A[10] =
                 ((B[9] * g_016340cc) * z +
                 (B[8] * x - B[2] * y) * g_016340ec) -
                 (B[0] * y + B[10] * x) * sqrt(1.0/72.0);
            A[0xb] =
                 (B[10] * z) * sqrt(11.0/36.0) +
                 (B[9] * x - B[1] * y) * sqrt(55.0/72.0);
            A[0xc] = (B[10] * x - B[0] * y) * sqrt(11.0/12.0);
            for (int i = 0; i < 13; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(A[i]), cv);
            if (7 < param_2) {
              oi = 49;
              B[0] = (A[0] * x + A[0xc] * y) * sqrt(13.0/14.0);
              B[1] = (A[0] * z) * sqrt(13.0/49.0) +
                            (A[1] * x + A[0xb] * y) * sqrt(39.0/49.0);
              B[2] = (A[1] * z) * sqrt(24.0/49.0) +
                            ((A[2] * x + A[10] * y) * sqrt(33.0/49.0) -
                            (A[0] * x - A[0xc] * y) * sqrt(1.0/98.0));
              B[3] = (A[2] * z) * sqrt(33.0/49.0) +
                            ((A[3] * x + A[9] * y) * sqrt(55.0/98.0) -
                            (A[1] * x - A[0xb] * y) * sqrt(3.0/98.0));
              B[4] = (A[3] * z) * sqrt(40.0/49.0) +
                            ((A[4] * x + A[8] * y) * sqrt(45.0/98.0) -
                            (A[2] * x - A[10] * y) * sqrt(3.0/49.0));
              B[5] = (A[4] * z) * sqrt(45.0/49.0) +
                            ((A[7] * y + A[5] * x) * sqrt(18.0/49.0) -
                            (A[3] * x - A[9] * y) * sqrt(5.0/49.0));
              B[6] = y * (A[6] * sqrt(4.0/7.0)) +
                            ((A[5] * z) * sqrt(48.0/49.0) -
                            (A[4] * x - A[8] * y) * sqrt(15.0/98.0));
              B[7] = A[6] * z -
                            (A[5] * y + A[7] * x) * sqrt(3.0/7.0);
              B[8] = (A[7] * z) * sqrt(48.0/49.0) +
                            (x * (A[6] * sqrt(4.0/7.0)) -
                            (A[4] * y + A[8] * x) * sqrt(15.0/98.0));
              B[9] = (z * A[8]) * sqrt(45.0/49.0) +
                            ((A[7] * x - A[5] * y) * sqrt(18.0/49.0) -
                            (A[3] * y + A[9] * x) * sqrt(5.0/49.0));
              B[10] = (A[9] * z) * sqrt(40.0/49.0) +
                             ((A[8] * x - A[4] * y) * sqrt(45.0/98.0) -
                             (A[2] * y + A[10] * x) * sqrt(3.0/49.0));
              cv = c[7];
              B[0xb] =
                   (z * A[10]) * sqrt(33.0/49.0) +
                   ((A[9] * x - A[3] * y) * sqrt(55.0/98.0) -
                   (A[1] * y + A[0xb] * x) * sqrt(3.0/98.0));
              B[0xc] =
                   (A[0xb] * z) * sqrt(24.0/49.0) +
                   ((A[10] * x - A[2] * y) * sqrt(33.0/49.0) -
                   (A[0] * y + A[0xc] * x) * sqrt(1.0/98.0));
              B[0xd] =
                   (A[0xc] * z) * sqrt(13.0/49.0) +
                   (A[0xb] * x - A[1] * y) * sqrt(39.0/49.0);
              B[0xe] = (A[0xc] * x - A[0] * y) * sqrt(13.0/14.0);
              for (int i = 0; i < 15; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(B[i]), cv);
              return;
            }
          }
        }
      }
    }
  }

}

// @ 0x00785500
float* SP_RotateZHToSHAdd(float* P, int order, float* in, float* out)
{
    out[0] += in[0];
    out[1] += in[1];
    out[2] += in[2];
    out[3] += in[3];
    if (order < 2) return out;

    const float b = P[1];
    const float c = P[2];
    const float a = P[0];

    // band 1
    {
        const float w[3] = { b, c, a };
        for (int i = 0; i < 3; ++i) {
            out[4 + i * 4 + 0] += w[i] * in[4];
            out[4 + i * 4 + 1] += w[i] * in[5];
            out[4 + i * 4 + 2] += w[i] * in[6];
            out[4 + i * 4 + 3] += w[i] * in[7];
        }
    }
    if (order < 3) return out + 4;

    // band 2
    float t[5];
    t[0] = ((a * b) * 2.0f) * k104;
    t[1] = ((c * b) * 2.0f) * k104;
    t[2] = c * c - (b * b + a * a) * k0dc;
    t[3] = ((a * c) * 2.0f) * k104;
    t[4] = (a * a - b * b) * k104;
    {
        float* o = out + 0x10;
        for (int i = 0; i < 5; ++i, o += 4) {
            const float v = t[i];
            o[0] += v * in[8];
            o[1] += v * in[9];
            o[2] += v * in[10];
            o[3] += v * in[11];
        }
    }
    if (order < 4) return out + 16;

    // band 3
    float s[7];
    s[0] = (t[4] * b + t[0] * a) * k078;
    s[1] = ((t[1] * a + t[3] * b) + t[0] * c) * k0cc;
    s[2] = ((k1e0 * t[1]) * c - (t[0] * a - t[4] * b) * k1b0) + (k150 * t[2]) * b;
    s[3] = t[2] * c - (t[1] * b + t[3] * a) * k0b0;
    s[4] = ((k150 * t[2]) * a - (t[0] * b + t[4] * a) * k1b0) + (k1e0 * t[3]) * c;
    s[5] = ((t[3] * a - t[1] * b) + t[4] * c) * k0cc;
    s[6] = (t[4] * a - t[0] * b) * k078;
    {
        float* o = out + 0x24;
        for (int i = 0; i < 7; ++i, o += 4) {
            const float v = s[i];
            o[0] = v * in[12];
            o[1] = v * in[13];
            o[2] = v * in[14];
            o[3] = v * in[15];
        }
    }
    if (order < 5) return out + 36;

    // band 4
    float q[9];
    q[0] = (s[6] * b + s[0] * a) * k0fc;
    q[1] = (s[5] * b + s[1] * a) * k09c + (k1dc * s[0]) * c;
    q[2] = ((s[2] * a + s[4] * b) * k0d4 - (s[0] * a - s[6] * b) * k130) + (k104 * s[1]) * c;
    q[3] = ((k0e8 * s[2]) * c - (s[1] * a - s[5] * b) * k074) + (k0ec * s[3]) * b;
    q[4] = s[3] * c - (s[2] * b + s[4] * a) * k0f8;
    q[5] = ((k0ec * s[3]) * a - (s[1] * b + s[5] * a) * k074) + (k0e8 * s[4]) * c;
    q[6] = ((s[4] * a - s[2] * b) * k0d4 - (s[0] * b + s[6] * a) * k130) + (k104 * s[5]) * c;
    q[7] = (s[5] * a - s[1] * b) * k09c + (k1dc * s[6]) * c;
    q[8] = (s[6] * a - s[0] * b) * k0fc;
    {
        float* o = out + 0x40;
        for (int i = 0; i < 9; ++i, o += 4) {
            const float v = q[i];
            o[0] = v * in[16];
            o[1] = v * in[17];
            o[2] = v * in[18];
            o[3] = v * in[19];
        }
    }
    if (order < 6) return out + 64;

    // band 5
    float r[11];
    r[0] = (q[8] * b + q[0] * a) * S(0.9);
    r[1] = (c * q[0]) * S(0.36) + (q[7] * b + q[1] * a) * k134;
    r[2] = (q[1] * c) * S(0.64) + ((q[6] * b + q[2] * a) * k10c - (q[0] * a - q[8] * b) * k168);
    r[3] = (q[2] * c) * S(0.84) + ((q[5] * b + q[3] * a) * k0e4 - (q[1] * a - q[7] * b) * k0a8);
    r[4] = (q[3] * c) * S(0.96) + ((q[4] * k064) * b - (q[2] * a - q[6] * b) * k05c);
    r[5] = q[4] * c - (q[3] * b + q[5] * a) * S(0.4);
    r[6] = (q[5] * c) * S(0.96) + ((q[4] * k064) * a - (q[2] * b + q[6] * a) * k05c);
    r[7] = (q[6] * c) * S(0.84) + ((q[5] * a - q[3] * b) * k0e4 - (q[1] * b + q[7] * a) * k0a8);
    r[8] = (q[7] * c) * S(0.64) + ((q[6] * a - q[2] * b) * k10c - (q[0] * b + q[8] * a) * k168);
    r[9] = (q[8] * c) * S(0.36) + (q[7] * a - q[1] * b) * k134;
    r[10] = (q[8] * a - q[0] * b) * S(0.9);
    {
        float* o = out + 0x64;
        for (int i = 0; i < 11; ++i, o += 4) {
            const float v = r[i];
            o[0] = v * in[20];
            o[1] = v * in[21];
            o[2] = v * in[22];
            o[3] = v * in[23];
        }
    }
    if (order < 7) return out + 100;

    // band 6
    float u[13];
    u[0] = (r[0] * a + r[10] * b) * S(0.9166666666666666);
    u[1] = (r[0] * c) * S(0.3055555555555556) + (r[9] * b + r[1] * a) * S(0.7638888888888888);
    u[2] = ((r[1] * k0cc) * c + (r[8] * b + r[2] * a) * k0ec) - (r[0] * a - r[10] * b) * S(0.013888888888888888);
    u[3] = (r[2] * k104) * c + ((r[3] * a + r[7] * b) * S(0.5) - (r[1] * a - r[9] * b) * S(0.041666666666666664));
    u[4] = (r[3] * k1e0) * c + ((r[6] * b + r[4] * a) * S(0.3888888888888889) - (r[2] * a - r[8] * b) * k07c);
    u[5] = b * (r[5] * S(0.5833333333333334)) + ((r[4] * c) * S(0.9722222222222222) - (r[3] * a - r[7] * b) * S(0.1388888888888889));
    u[6] = r[5] * c - (r[4] * b + r[6] * a) * S(0.4166666666666667);
    u[7] = (r[6] * c) * S(0.9722222222222222) + (a * (r[5] * S(0.5833333333333334)) - (r[3] * b + r[7] * a) * S(0.1388888888888889));
    u[8] = (r[7] * k1e0) * c + ((r[6] * a - r[4] * b) * S(0.3888888888888889) - (r[2] * b + r[8] * a) * k07c);
    u[9] = (r[8] * k104) * c + ((r[7] * a - r[3] * b) * S(0.5) - (r[1] * b + r[9] * a) * S(0.041666666666666664));
    u[10] = ((r[9] * k0cc) * c + (r[8] * a - r[2] * b) * k0ec) - (r[0] * b + r[10] * a) * S(0.013888888888888888);
    u[11] = (r[10] * c) * S(0.3055555555555556) + (r[9] * a - r[1] * b) * S(0.7638888888888888);
    u[12] = (r[10] * a - r[0] * b) * S(0.9166666666666666);
    {
        float* o = out + 0x90;
        for (int i = 0; i < 13; ++i, o += 4) {
            const float v = u[i];
            o[0] = v * in[24];
            o[1] = v * in[25];
            o[2] = v * in[26];
            o[3] = v * in[27];
        }
    }
    if (order < 8) return out + 144;

    // band 7
    float w[15];
    w[0] = (u[0] * a + u[12] * b) * S(0.9285714285714286);
    w[1] = (u[0] * c) * S(0.2653061224489796) + (u[1] * a + u[11] * b) * S(0.7959183673469388);
    w[2] = (u[1] * c) * S(0.4897959183673469) + ((u[2] * a + u[10] * b) * S(0.673469387755102) - (u[0] * a - u[12] * b) * S(0.01020408163265306));
    w[3] = (u[2] * c) * S(0.673469387755102) + ((u[3] * a + u[9] * b) * S(0.5612244897959183) - (u[1] * a - u[11] * b) * S(0.030612244897959183));
    w[4] = (u[3] * c) * S(0.8163265306122449) + ((u[4] * a + u[8] * b) * S(0.45918367346938777) - (u[2] * a - u[10] * b) * S(0.061224489795918366));
    w[5] = (u[4] * c) * S(0.9183673469387755) + ((u[7] * b + u[5] * a) * S(0.3673469387755102) - (u[3] * a - u[9] * b) * S(0.10204081632653061));
    w[6] = b * (u[6] * S(0.5714285714285714)) + ((u[5] * c) * S(0.9795918367346939) - (u[4] * a - u[8] * b) * S(0.15306122448979592));
    w[7] = u[6] * c - (u[5] * b + u[7] * a) * S(0.42857142857142855);
    w[8] = (u[7] * c) * S(0.9795918367346939) + (a * (u[6] * S(0.5714285714285714)) - (u[4] * b + u[8] * a) * S(0.15306122448979592));
    w[9] = (c * u[8]) * S(0.9183673469387755) + ((u[7] * a - u[5] * b) * S(0.3673469387755102) - (u[3] * b + u[9] * a) * S(0.10204081632653061));
    w[10] = (u[9] * c) * S(0.8163265306122449) + ((u[8] * a - u[4] * b) * S(0.45918367346938777) - (u[2] * b + u[10] * a) * S(0.061224489795918366));
    w[11] = (c * u[10]) * S(0.673469387755102) + ((u[9] * a - u[3] * b) * S(0.5612244897959183) - (u[1] * b + u[11] * a) * S(0.030612244897959183));
    w[12] = (u[11] * c) * S(0.4897959183673469) + ((u[10] * a - u[2] * b) * S(0.673469387755102) - (u[0] * b + u[12] * a) * S(0.01020408163265306));
    w[13] = (u[12] * c) * S(0.2653061224489796) + (u[11] * a - u[1] * b) * S(0.7959183673469388);
    w[14] = (u[12] * a - u[0] * b) * S(0.9285714285714286);
    {
        float* o = out + 0xc4;
        for (int i = 0; i < 15; ++i, o += 4) {
            const float v = w[i];
            o[0] = v * in[28];
            o[1] = v * in[29];
            o[2] = v * in[30];
            o[3] = v * in[31];
        }
    }
    return out + 256;
}

// @ 0x007864c0
namespace SP {
template <> void RotateSH<Vector4_s0078_64c0>(const float* m, int order, const Vector4_s0078_64c0* in, Vector4_s0078_64c0* out)
{
    float R1[3][3];
    float R2[5][5];
    float R3[7][7];
    float R4[9][9];
    float R5[11][11];
    float R6[13][13];
    float R7[15][15];
    float f1000, f1010, f1018, f1040, f1048, f1050, f1058, f1060, f1068, f106c;
    float f1078, f1080, f1088, f1090, f1098, f10a0, f10a8, f10b0, f10b8, f10c0;
    float f10c8, f10d0, f10d8, f10e0, f10e8, f10f0, f10f4, f10f8, f1100, f1104;
    float f1110, f1114, f1118, f111c, f1120, f1124, f1128, f112c, f1130, f1134;
    float f1138, f113c, f1140, f1144, f1148, f114c, f1150, f1154, f1158, f115c;
    float f1160, f1164, f1168, f116c, f1170, f1174, f1178, f117c, f1180, f1184;
    float f1188, fVar4, fVar7, fVar8, fVar9, ff98, ffa0, ffb0, ffb8, ffe0;
    float fff8;
    double d1080, d1090, d1098, d10a0, d10a8, d10b0, d10b8, d10c8, d10d8, d10e0;
    double d1100, d410, d428, db88, dba0, dba8, dd20, dd30, dd78, df28;
    double df80;

    // ---- band 0 ----
    out[0] = in[0];

    // ---- band 1: the rotation itself, rows/columns in SH (y, z, x) order ----
    if (order <= 1)
        return;
    R1[0][0] = m[4]; R1[0][1] = m[7]; R1[0][2] = m[1];
    R1[1][0] = m[5]; R1[1][1] = m[8]; R1[1][2] = m[2];
    R1[2][0] = m[3]; R1[2][1] = m[6]; R1[2][2] = m[0];
    out[1] = MulRow3(&in[1], R1[0]);
    out[2] = MulRow3(&in[1], R1[1]);
    out[3] = MulRow3(&in[1], R1[2]);

    // ---- band 2: explicit quadratic forms in R1 ----
    if (order <= 2)
        return;
    R2[0][0] = ((R1[2][0] * R1[0][2] + R1[2][2] * R1[0][0]) * 2.0f) * k_16340dc;
    R2[0][1] = R1[2][0] * R1[0][1] + R1[2][1] * R1[0][0];
    R2[0][2] = ((R1[2][1] * R1[0][1]) * 2.0f) * k_1634104;
    R2[0][3] = R1[2][1] * R1[0][2] + R1[2][2] * R1[0][1];
    R2[0][4] = ((R1[2][2] * R1[0][2] - R1[2][0] * R1[0][0]) * 2.0f) * k_16340dc;
    out[4] = WeightedSum(5, &in[4], R2[0]);
    R2[1][0] = ((R1[1][0] * R1[0][2] + R1[1][2] * R1[0][0]) * 2.0f) * k_16340dc;
    R2[1][1] = R1[1][0] * R1[0][1] + R1[1][1] * R1[0][0];
    R2[1][2] = ((R1[1][1] * R1[0][1]) * 2.0f) * k_1634104;
    R2[1][3] = R1[1][1] * R1[0][2] + R1[1][2] * R1[0][1];
    R2[1][4] = ((R1[1][2] * R1[0][2] - R1[1][0] * R1[0][0]) * 2.0f) * k_16340dc;
    out[5] = WeightedSum(5, &in[4], R2[1]);
    f1174 = (R1[2][2] * R1[2][0]) * 2.0f;
    f1154 = (R1[0][2] * R1[0][0]) * 2.0f;
    R2[2][0] = ((R1[1][2] * R1[1][0]) * 2.0f) * k_16340b0 -
                (f1154 + f1174) * k_163407c;
    f116c = R1[2][1] * R1[2][0];
    f1168 = R1[0][1] * R1[0][0];
    R2[2][1] = (k_16341f4 * R1[1][1]) * R1[1][0] -
                (f1168 + f116c) * k_16340b0;
    f1178 = R1[2][1] * R1[2][1];
    f114c = R1[0][1] * R1[0][1];
    R2[2][2] = R1[1][1] * R1[1][1] - (f114c + f1178) * k_16340dc;
    f1180 = R1[2][2] * R1[2][1];
    f1170 = R1[0][2] * R1[0][1];
    R2[2][3] = (k_16341f4 * R1[1][2]) * R1[1][1] -
                (f1170 + f1180) * k_16340b0;
    f1158 = R1[2][2] * R1[2][2] - R1[2][0] * R1[2][0];
    f1140 = R1[0][2] * R1[0][2] - R1[0][0] * R1[0][0];
    R2[2][4] = (R1[1][2] * R1[1][2] - R1[1][0] * R1[1][0]) * k_16340b0 -
                (f1140 + f1158) * k_163407c;
    out[6] = WeightedSum(5, &in[4], R2[2]);
    R2[3][0] = ((R1[2][0] * R1[1][2] + R1[2][2] * R1[1][0]) * 2.0f) * k_16340dc;
    R2[3][1] = R1[2][0] * R1[1][1] + R1[2][1] * R1[1][0];
    R2[3][2] = ((R1[2][1] * R1[1][1]) * 2.0f) * k_1634104;
    R2[3][3] = R1[2][1] * R1[1][2] + R1[2][2] * R1[1][1];
    R2[3][4] = ((R1[2][2] * R1[1][2] - R1[2][0] * R1[1][0]) * 2.0f) * k_16340dc;
    out[7] = WeightedSum(5, &in[4], R2[3]);
    R2[4][4] = k_16340dc;
    R2[4][0] = (f1174 - f1154) * R2[4][4];
    R2[4][1] = f116c - f1168;
    R2[4][2] = (f1178 - f114c) * k_1634104;
    R2[4][3] = f1180 - f1170;
    R2[4][4] = (f1158 - f1140) * R2[4][4];
    out[8] = WeightedSum(5, &in[4], R2[4]);

    // ---- band 3: R3 from R1 x R2 ----
    if (order <= 3)
        return;
    f1154 = R2[4][0] * R1[0][2] + R2[4][4] * R1[0][0];
    f1174 = R2[0][0] * R1[2][2] + R2[0][4] * R1[2][0];
    R3[0][0] = (f1174 + f1154) * k_16340dc;
    f1168 = R2[4][0] * R1[0][1];
    f116c = R2[0][0] * R1[2][1];
    R3[0][1] = (f116c + f1168) * k_16340b4;
    f114c = R2[4][1] * R1[0][1];
    f1178 = R2[0][1] * R1[2][1];
    R3[0][2] = (f1178 + f114c) * k_16340e8;
    f1180 = R2[0][2] * R1[2][1];
    f1170 = R2[4][2] * R1[0][1];
    R3[0][3] = (f1180 + f1170) * k_1634078;
    f1140 = R2[4][3] * R1[0][1];
    f1158 = R2[0][3] * R1[2][1];
    R3[0][4] = (f1158 + f1140) * k_16340e8;
    f1150 = R2[4][4] * R1[0][1];
    f117c = R2[0][4] * R1[2][1];
    R3[0][5] = (f117c + f1150) * k_16340b4;
    f113c = R2[0][4] * R1[2][2] - R2[0][0] * R1[2][0];
    f1148 = R2[4][4] * R1[0][2] - R2[4][0] * R1[0][0];
    R3[0][6] = (f113c + f1148) * k_16340dc;
    out[9] = WeightedSum(7, &in[9], R3[0]);
    R3[1][0] = (((R2[1][0] * R1[2][2] + R2[1][4] * R1[2][0]) +
                 (R2[3][0] * R1[0][2] + R2[3][4] * R1[0][0])) +
                (R2[0][0] * R1[1][2] + R2[0][4] * R1[1][0])) * k_1634084;
    R3[1][1] = (R2[1][0] * R1[2][1] + R2[3][0] * R1[0][1]) + R2[0][0] * R1[1][1];
    R3[1][2] = ((R2[1][1] * R1[2][1] + R2[3][1] * R1[0][1]) + R2[0][1] * R1[1][1]) *
                k_16340ec;
    R3[1][3] = ((R2[1][2] * R1[2][1] + R2[3][2] * R1[0][1]) + R2[0][2] * R1[1][1]) *
                k_16340cc;
    R3[1][4] = ((R2[1][3] * R1[2][1] + R2[3][3] * R1[0][1]) + R2[0][3] * R1[1][1]) *
                k_16340ec;
    R3[1][5] = (R2[1][4] * R1[2][1] + R2[3][4] * R1[0][1]) + R2[0][4] * R1[1][1];
    R3[1][6] = (((R2[1][4] * R1[2][2] - R2[1][0] * R1[2][0]) +
                 (R2[3][4] * R1[0][2] - R2[3][0] * R1[0][0])) +
                (R2[0][4] * R1[1][2] - R2[0][0] * R1[1][0])) * k_1634084;
    out[10] = WeightedSum(7, &in[9], R3[1]);
    fVar7 = R2[2][0] * k_1634120;
    R3[2][1] = ((R2[1][0] * k_16341ec) * R1[1][1] - (f116c - f1168) * k_1634114) +
                fVar7 * R1[0][1];
    R3[2][0] = ((R2[1][0] * R1[1][2] + R2[1][4] * R1[1][0]) * k_16340ac +
                (R2[2][0] * R1[0][2] + R2[2][4] * R1[0][0]) * k_1634054) -
                (f1174 - f1154) * sqrt(1.0 / 60.0);
    f1154 = R2[2][1] * k_1634104;
    f116c = R2[2][2] * k_1634150;
    R3[2][2] = (f1154 * R1[0][1] - (f1178 - f114c) * k_16340bc) +
                R2[1][1] * R1[1][1];
    R3[2][3] = ((R2[1][2] * k_16341e0) * R1[1][1] -
                (f1180 - f1170) * k_16341b0) + f116c * R1[0][1];
    f1168 = R2[2][3] * k_1634104;
    R3[2][6] = (k_1634054 * (R2[2][4] * R1[0][2] - R2[2][0] * R1[0][0]) +
                k_16340ac * (R2[1][4] * R1[1][2] - R2[1][0] * R1[1][0])) -
                (f113c - f1148) * sqrt(1.0 / 60.0);
    R3[2][4] = (f1168 * R1[0][1] - (f1158 - f1140) * k_16340bc) +
                R2[1][3] * R1[1][1];
    f1178 = R2[2][4] * k_1634120;
    R3[2][5] = ((R2[1][4] * k_16341ec) * R1[1][1] - (f117c - f1150) * k_1634114) +
                f1178 * R1[0][1];
    f1174 = fVar7;
    out[11] = WeightedSum(7, &in[9], R3[2]);
    fVar9 = R2[2][0] * k_1634080;
    f114c = R2[3][0] * R1[2][2] + R2[3][4] * R1[2][0];
    f1180 = R2[1][0] * R1[0][2] + R2[1][4] * R1[0][0];
    f1170 = R2[3][0] * R1[2][1];
    R3[3][0] = (R2[2][0] * R1[1][2] + R2[2][4] * R1[1][0]) * k_1634098 -
                (f1180 + f114c) * k_1634114;
    f1158 = R2[1][0] * R1[0][1];
    f117c = R2[1][1] * R1[0][1];
    R3[3][1] = fVar9 * R1[1][1] - (f1158 + f1170) * k_1634064;
    f1140 = R2[3][1] * R1[2][1];
    R3[3][2] = (R2[2][1] * k_1634094) * R1[1][1] -
                (f117c + f1140) * k_16340f8;
    f1150 = R2[3][2] * R1[2][1];
    f113c = R2[1][2] * R1[0][1];
    R3[3][3] = R2[2][2] * R1[1][1] - (f113c + f1150) * k_16340b0;
    f1080 = R2[1][3] * R1[0][1];
    f1148 = R2[3][3] * R1[2][1];
    R3[3][4] = (R2[2][3] * k_1634094) * R1[1][1] -
                (f1080 + f1148) * k_16340f8;
    f10c0 = R2[1][4] * R1[0][1];
    f10b0 = R2[3][4] * R1[2][1];
    R3[3][5] = (R2[2][4] * k_1634080) * R1[1][1] -
                (f10c0 + f10b0) * k_1634064;
    f10d0 = R2[3][4] * R1[2][2] - R2[3][0] * R1[2][0];
    f10e8 = (R2[1][4] * R1[0][2] - R2[1][0] * R1[0][0]);
    R3[3][6] = (R2[2][4] * R1[1][2] - R2[2][0] * R1[1][0]) * k_1634098 -
                (f10e8 + f10d0) * k_1634114;
    out[12] = WeightedSum(7, &in[9], R3[3]);
    f1114 = R2[4][0] * R1[2][2] + R2[4][4] * R1[2][0];
    f112c = R2[0][4] * R1[0][0] + R2[0][0] * R1[0][2];
    f10b8 = R2[0][0] * R1[0][1];
    R3[4][0] = ((R2[3][0] * R1[1][2] + R2[3][4] * R1[1][0]) * k_16340ac +
                (R2[2][4] * R1[2][0] + R2[2][0] * R1[2][2]) * k_1634054) -
                (f112c + f1114) * sqrt(1.0 / 60.0);
    f1098 = R2[4][0] * R1[2][1];
    R3[4][1] = (f1174 * R1[2][1] - (f10b8 + f1098) * k_1634114)
                + (R2[3][0] * k_16341ec) * R1[1][1];
    f1088 = R2[0][1] * R1[0][1];
    f1174 = R2[4][1] * R1[2][1];
    R3[4][2] = (f1154 * R1[2][1] - (f1088 + f1174) * k_16340bc) +
                R2[3][1] * R1[1][1];
    f1090 = R2[0][2] * R1[0][1];
    f1154 = R2[4][2] * R1[2][1];
    R3[4][3] = (f116c * R1[2][1] - (f1090 + f1154) * k_16341b0) +
                (R2[3][2] * k_16341e0) * R1[1][1];
    f10d8 = R2[0][3] * R1[0][1];
    f116c = R2[4][3] * R1[2][1];
    R3[4][4] = (f1168 * R1[2][1] - (f10d8 + f116c) * k_16340bc) +
                R2[3][3] * R1[1][1];
    f1168 = R2[4][4] * R1[2][1];
    f1100 = (R2[0][4] * R1[0][1]);
    fVar9 = f1178 * R1[2][1];
    f1144 = R2[4][4] * R1[2][2] - R2[4][0] * R1[2][0];
    f1178 = R2[0][4] * R1[0][2] - R2[0][0] * R1[0][0];
    R3[4][5] = (fVar9 - (f1100 + f1168) * k_1634114) +
                (R2[3][4] * k_16341ec) * R1[1][1];
    R3[4][6] = ((R2[3][4] * R1[1][2] - R2[3][0] * R1[1][0]) * k_16340ac +
                (R2[2][4] * R1[2][2] - R2[2][0] * R1[2][0]) * k_1634054) -
                (f1178 + f1144) * sqrt(1.0 / 60.0);
    out[13] = WeightedSum(7, &in[9], R3[4]);
    R3[5][6] = k_1634084;
    R3[5][0] = ((R2[4][0] * R1[1][2] + R2[4][4] * R1[1][0]) + (f114c - f1180))
                * R3[5][6];
    R3[5][1] = (f1170 - f1158) + R2[4][0] * R1[1][1];
    R3[5][2] = ((f1140 - f117c) + R2[4][1] * R1[1][1]) * k_16340ec;
    R3[5][3] = ((f1150 - f113c) + R2[4][2] * R1[1][1]) * k_16340cc;
    R3[5][4] = ((f1148 - f1080) + R2[4][3] * R1[1][1]) * k_16340ec;
    R3[5][5] = (f10b0 - f10c0) + R2[4][4] * R1[1][1];
    R3[5][6] = ((R2[4][4] * R1[1][2] - R2[4][0] * R1[1][0]) +
                (f10d0 - f10e8)) * R3[5][6];
    out[14] = WeightedSum(7, &in[9], R3[5]);
    R3[6][4] = k_16340e8;
    R3[6][6] = k_16340dc;
    R3[6][5] = k_16340b4;
    R3[6][0] = (f1114 - f112c) * R3[6][6];
    R3[6][1] = (f1098 - f10b8) * R3[6][5];
    R3[6][2] = (f1174 - f1088) * R3[6][4];
    R3[6][3] = (f1154 - f1090) * k_1634078;
    R3[6][4] = (f116c - f10d8) * R3[6][4];
    R3[6][5] = (f1168 - f1100) * R3[6][5];
    R3[6][6] = (f1144 - f1178) * R3[6][6];
    out[15] = WeightedSum(7, &in[9], R3[6]);

    // ---- band 4: R4 from R1 x R3 ----
    if (order <= 4)
        return;
    f10d8 = R3[0][6] * R1[2][0] + R3[0][0] * R1[2][2];
    f1090 = R3[6][0] * R1[0][2] + R3[6][6] * R1[0][0];
    f10b0 = R3[0][3] * R1[2][1];
    R4[0][0] = (f1090 + f10d8) * k_16340dc;
    f1080 = R3[6][3] * R1[0][1];
    R4[0][4] = (f10b0 + f1080) * k_16340fc;
    f10b8 = R3[6][0] * R1[0][1];
    f1088 = R3[0][0] * R1[2][1];
    R4[0][1] = (f1088 + f10b8) * sqrt(2.0);
    f10e8 = (R3[6][1] * R1[0][1]);
    f1098 = R3[0][1] * R1[2][1];
    R4[0][2] = (f1098 + f10e8) * sqrt(7.0 / 6.0);
    f10c0 = R3[6][2] * R1[0][1];
    f10d0 = R3[0][2] * R1[2][1];
    R4[0][3] = (f10d0 + f10c0) * sqrt(14.0 / 15.0);
    f1174 = R3[6][4] * R1[0][1];
    f1188 = (R3[0][4] * R1[2][1]);
    R4[0][5] = (f1188 + f1174) * sqrt(14.0 / 15.0);
    f116c = R3[6][5] * R1[0][1];
    f114c = R3[0][6] * R1[2][2] - R3[0][0] * R1[2][0];
    f1154 = R3[0][5] * R1[2][1];
    f1180 = R3[6][6] * R1[0][2] - R3[6][0] * R1[0][0];
    R4[0][6] = (f1154 + f116c) * sqrt(7.0 / 6.0);
    R4[0][8] = (f1180 + f114c) * k_16340dc;
    f1178 = R3[6][6] * R1[0][1];
    f1168 = R3[0][6] * R1[2][1];
    R4[0][7] = (f1168 + f1178) * sqrt(2.0);
    out[16] = WeightedSum(9, &in[16], R4[0]);
    f117c = R3[5][0] * R1[0][1];
    f1170 = R3[1][6] * R1[2][0] + R3[1][0] * R1[2][2];
    f1158 = R3[5][6] * R1[0][0] + R3[5][0] * R1[0][2];
    R4[1][0] = (f1158 + f1170) * sqrt(3.0 / 16.0) +
                (R3[0][0] * R1[1][2] + R3[0][6] * R1[1][0]) * sqrt(1.0 / 8.0);
    f1140 = R3[1][0] * R1[2][1];
    R4[1][1] = (f1140 + f117c) * k_16340b4 + R3[0][0] * R1[1][1];
    f1114 = R3[5][3] * R1[0][1];
    f112c = R3[1][3] * R1[2][1];
    R4[1][4] = (f112c + f1114) * k_163409c +
                (R3[0][3] * k_16341dc) * R1[1][1];
    f113c = R3[5][1] * R1[0][1];
    f1150 = R3[1][1] * R1[2][1];
    R4[1][2] = (R1[1][1] * R3[0][1]) * sqrt(7.0 / 12.0) +
                (f1150 + f113c) * k_16340fc;
    f1144 = R3[5][2] * R1[0][1];
    f1148 = R3[1][2] * R1[2][1];
    R4[1][3] = (R3[0][2] * R1[1][1]) * sqrt(7.0 / 15.0) + (f1148 + f1144) * sqrt(7.0 / 10.0);
    f10a0 = R3[5][4] * R1[0][1];
    f10c8 = R3[1][4] * R1[2][1];
    R4[1][5] = (R3[0][4] * R1[1][1]) * sqrt(7.0 / 15.0) +
                (f10c8 + f10a0) * sqrt(7.0 / 10.0);
    f1164 = R3[5][6] * R1[0][1];
    f10f0 = R3[1][6] * R1[2][1];
    f10e0 = R3[5][5] * R1[0][1];
    f10a8 = R3[1][5] * R1[2][1];
    R4[1][7] = (f10f0 + f1164) * k_16340b4 + R3[0][6] * R1[1][1];
    R4[1][6] = (R3[0][5] * R1[1][1]) * sqrt(7.0 / 12.0) +
                (f10a8 + f10e0) * k_16340fc;
    f115c = R3[1][6] * R1[2][2] - R3[1][0] * R1[2][0];
    f1184 = (R3[5][6] * R1[0][2] - R3[5][0] * R1[0][0]);
    R4[1][8] = (R3[0][6] * R1[1][2] - R3[0][0] * R1[1][0]) * sqrt(1.0 / 8.0) +
                (f1184 + f115c) * sqrt(3.0 / 16.0);
    out[17] = WeightedSum(9, &in[16], R4[1]);
    R4[2][0] = (((R3[2][6] * R1[2][0] + R1[2][2] * R3[2][0]) +
                 (R3[4][0] * R1[0][2] + R3[4][6] * R1[0][0])) * sqrt(15.0 / 112.0) -
                (f10d8 - f1090) * sqrt(1.0 / 112.0)) +
                (R1[1][0] * R3[1][6] + R1[1][2] * R3[1][0]) * sqrt(3.0 / 14.0);
    R4[2][1] = (R1[1][1] * R3[1][0]) * sqrt(12.0 / 7.0) +
                ((R3[2][0] * R1[2][1] + R3[4][0] * R1[0][1]) * sqrt(15.0 / 14.0) -
                (f1088 - f10b8) * sqrt(1.0 / 14.0));
    R4[2][2] = (R3[1][1] * R1[1][1] +
                (R3[4][1] * R1[0][1] + R3[2][1] * R1[2][1]) * k_16340ec) -
                (f1098 - f10e8) * sqrt(1.0 / 24.0);
    R4[2][4] = ((R3[2][3] * R1[2][1] + R3[4][3] * R1[0][1]) * k_16340d4 -
                (f10b0 - f1080) * k_1634130) +
                (R3[1][3] * k_1634104) * R1[1][1];
    R4[2][3] = (R3[1][2] * R1[1][1]) * sqrt(4.0 / 5.0) +
                ((R3[4][2] * R1[0][1] + R3[2][2] * R1[2][1]) * sqrt(1.0 / 2.0) -
                (f10d0 - f10c0) * sqrt(1.0 / 30.0));
    R4[2][5] = (R3[1][4] * R1[1][1]) * sqrt(4.0 / 5.0) +
                ((R3[4][4] * R1[0][1] + R3[2][4] * R1[2][1]) * sqrt(1.0 / 2.0) -
                (f1188 - f1174) * sqrt(1.0 / 30.0));
    R4[2][6] = (R3[1][5] * R1[1][1] +
                (R3[4][5] * R1[0][1] + R3[2][5] * R1[2][1]) * k_16340ec) -
                (f1154 - f116c) * sqrt(1.0 / 24.0);
    R4[2][7] = (R3[1][6] * R1[1][1]) * sqrt(12.0 / 7.0) +
                ((R3[4][6] * R1[0][1] + R3[2][6] * R1[2][1]) * sqrt(15.0 / 14.0) -
                (f1168 - f1178) * sqrt(1.0 / 14.0));
    R4[2][8] = (R3[1][6] * R1[1][2] - R3[1][0] * R1[1][0]) * sqrt(3.0 / 14.0) +
                (((R3[2][6] * R1[2][2] - R3[2][0] * R1[2][0]) +
                 (R3[4][6] * R1[0][2] - R3[4][0] * R1[0][0])) * sqrt(15.0 / 112.0) -
                (f114c - f1180) * sqrt(1.0 / 112.0));
    out[18] = WeightedSum(9, &in[16], R4[2]);
    R4[3][0] = (R3[3][6] * R1[0][0] + R1[0][2] * R3[3][0]) * sqrt(5.0 / 28.0) +
                ((R3[2][6] * R1[1][0] + R1[1][2] * R3[2][0]) * sqrt(15.0 / 56.0) -
                (f1170 - f1158) * sqrt(3.0 / 112.0));
    dba0 = (R3[3][0] * sqrt(10.0 / 7.0));
    f10d8 = R3[3][2] * k_1634150;
    R4[3][1] = ((R1[1][1] * R3[2][0]) * sqrt(15.0 / 7.0) -
                (f1140 - f117c) * sqrt(3.0 / 14.0)) +
                R1[0][1] * (R3[3][0] * sqrt(10.0 / 7.0));
    R4[3][3] = (f10d8 * R1[0][1] - (f1148 - f1144) * k_1634114) +
                R3[2][2] * R1[1][1];
    f1100 = (R3[3][1] * k_1634078);
    f1090 = R3[3][3] * k_16340ec;
    R4[3][4] = ((R3[2][3] * k_16340e8) * R1[1][1] -
                (f112c - f1114) * k_1634074) + f1090 * R1[0][1];
    f1088 = R3[3][4] * k_1634150;
    R4[3][5] = (f1088 * R1[0][1] -
                (f10c8 - f10a0) * k_1634114) + R3[2][4] * R1[1][1]
    ;
    R4[3][2] = (R3[2][1] * R1[1][1]) * sqrt(5.0 / 4.0) +
                (f1100 * R1[0][1] -
                (f1150 - f113c) * sqrt(1.0 / 8.0));
    f10a0 = R3[3][5] * k_1634078;
    R4[3][6] = (R3[2][5] * R1[1][1]) * sqrt(5.0 / 4.0) +
                (f10a0 * R1[0][1] -
                (f10a8 - f10e0) * sqrt(1.0 / 8.0));
    dba8 = (R3[3][6] * sqrt(10.0 / 7.0));
    R4[3][7] = ((R3[2][6] * R1[1][1]) * sqrt(15.0 / 7.0) -
                (f10f0 - f1164) * sqrt(3.0 / 14.0)) +
                R1[0][1] * (R3[3][6] * sqrt(10.0 / 7.0));
    R4[3][8] = ((R3[2][6] * R1[1][2] - R3[2][0] * R1[1][0]) * sqrt(15.0 / 56.0) -
                (f115c - f1184) * sqrt(3.0 / 112.0)) +
                (R3[3][6] * R1[0][2] - R3[3][0] * R1[0][0]) * sqrt(5.0 / 28.0);
    out[19] = WeightedSum(9, &in[16], R4[3]);
    f115c = R3[4][0] * R1[2][2] + R3[4][6] * R1[2][0];
    f1164 = R3[2][6] * R1[0][0] + R3[2][0] * R1[0][2];
    R4[4][0] = (R1[1][0] * R3[3][6] + R1[1][2] * R3[3][0]) * sqrt(2.0 / 7.0) -
                (f1164 + f115c) * sqrt(3.0 / 28.0);
    f1098 = R3[2][3] * R1[0][1];
    f10b8 = R3[4][3] * R1[2][1];
    R4[4][4] = R3[3][3] * R1[1][1] - (f1098 + f10b8) * k_16340f8;
    f10f0 = R3[4][0] * R1[2][1];
    f1144 = R3[2][0] * R1[0][1];
    R4[4][1] = (R1[1][1] * R3[3][0]) * sqrt(16.0 / 7.0) -
                (f1144 + f10f0) * sqrt(6.0 / 7.0);
    f10e0 = R3[4][1] * R1[2][1];
    f10a8 = R3[2][1] * R1[0][1];
    R4[4][2] = (R3[3][1] * k_16341f4) * R1[1][1] -
                (f10a8 + f10e0) * sqrt(1.0 / 2.0);
    f10c8 = R3[4][2] * R1[2][1];
    f112c = R3[2][2] * R1[0][1];
    R4[4][3] = (R3[3][2] * R1[1][1]) * sqrt(16.0 / 15.0) -
                (f112c + f10c8) * sqrt(2.0 / 5.0);
    f10e8 = (R3[4][4] * R1[2][1]);
    f1114 = R3[2][4] * R1[0][1];
    R4[4][5] = (R3[3][4] * R1[1][1]) * sqrt(16.0 / 15.0) -
                (f1114 + f10e8) * sqrt(2.0 / 5.0);
    f10d0 = R3[4][5] * R1[2][1];
    f10c0 = R3[2][5] * R1[0][1];
    R4[4][6] = (R3[3][5] * k_16341f4) * R1[1][1] -
                (f10c0 + f10d0) * sqrt(1.0 / 2.0);
    f10b0 = R3[4][6] * R1[2][1];
    f1080 = R3[2][6] * R1[0][1];
    R4[4][7] = (R3[3][6] * R1[1][1]) * sqrt(16.0 / 7.0) -
                (f1080 + f10b0) * sqrt(6.0 / 7.0);
    f1188 = (R3[4][6] * R1[2][2] - R3[4][0] * R1[2][0]);
    f1174 = R3[2][6] * R1[0][2] - R3[2][0] * R1[0][0];
    R4[4][8] = (R3[3][6] * R1[1][2] - R3[3][0] * R1[1][0]) * sqrt(2.0 / 7.0) -
                (f1174 + f1188) * sqrt(3.0 / 28.0);
    out[20] = WeightedSum(9, &in[16], R4[4]);
    f1154 = R3[5][0] * R1[2][2] + R3[5][6] * R1[2][0];
    f116c = R3[1][6] * R1[0][0] + R1[0][2] * R3[1][0];
    R4[5][0] = (R3[3][6] * R1[2][0] + R3[3][0] * R1[2][2]) * sqrt(5.0 / 28.0) +
                ((R3[4][0] * R1[1][2] + R3[4][6] * R1[1][0]) * sqrt(15.0 / 56.0) -
                (f116c + f1154) * sqrt(3.0 / 112.0));
    f1168 = R3[5][0] * R1[2][1];
    f1178 = R3[1][0] * R1[0][1];
    R4[5][1] = (R1[1][1] * R3[4][0]) * sqrt(15.0 / 7.0) +
                (R1[2][1] * dba0 - (f1178 + f1168) * sqrt(3.0 / 14.0))
    ;
    f114c = R3[5][1] * R1[2][1];
    f1180 = R3[1][1] * R1[0][1];
    R4[5][2] = (R3[4][1] * R1[1][1]) * sqrt(5.0 / 4.0) +
                (f1100 * R1[2][1] -
                (f1180 + f114c) * sqrt(1.0 / 8.0));
    f1100 = (R3[5][2] * R1[2][1]);
    f1170 = R3[1][2] * R1[0][1];
    R4[5][3] = (f10d8 * R1[2][1] -
                (f1170 + f1100) * k_1634114) +
                R3[4][2] * R1[1][1];
    f1158 = R3[1][3] * R1[0][1];
    f10d8 = R3[5][3] * R1[2][1];
    R4[5][4] = (f1090 * R1[2][1] -
                (f1158 + f10d8) * k_1634074) +
                (R3[4][3] * k_16340e8) * R1[1][1];
    f1090 = R3[5][4] * R1[2][1];
    f117c = R3[1][5] * R1[0][1];
    f1140 = R3[1][4] * R1[0][1];
    R4[5][5] = (f1088 * R1[2][1] -
                (f1140 + f1090) * k_1634114) + R3[4][4] * R1[1][1];
    R4[5][6] = (R3[4][5] * R1[1][1]) * sqrt(5.0 / 4.0) +
                (f10a0 * R1[2][1] -
                (f117c + R3[5][5] * R1[2][1]) * sqrt(1.0 / 8.0));
    f1148 = R3[5][6] * R1[2][1];
    f10a0 = R3[1][6] * R1[0][1];
    R4[5][7] = R1[2][1] * dba8 +
                ((R3[4][6] * R1[1][1]) * sqrt(15.0 / 7.0) -
                (f10a0 + f1148) * sqrt(3.0 / 14.0));
    f1150 = R3[5][6] * R1[2][2] - R3[5][0] * R1[2][0];
    f113c = R3[1][6] * R1[0][2] - R3[1][0] * R1[0][0];
    R4[5][8] = (R1[2][2] * R3[3][6] - R3[3][0] * R1[2][0]) * sqrt(5.0 / 28.0) +
                ((R3[4][6] * R1[1][2] - R3[4][0] * R1[1][0]) * sqrt(15.0 / 56.0) -
                (f113c + f1150) * sqrt(3.0 / 112.0));
    f1088 = R3[5][5] * R1[2][1];
    out[21] = WeightedSum(9, &in[16], R4[5]);
    f1130 = R1[0][2] * R3[0][0] + R3[0][6] * R1[0][0];
    f1134 = R3[6][6] * R1[2][0] + R1[2][2] * R3[6][0];
    f1160 = (R3[0][3] * R1[0][1]);
    f1098 = f10b8 - f1098;
    R4[6][0] = (R3[5][6] * R1[1][0] + R1[1][2] * R3[5][0]) * sqrt(3.0 / 14.0) +
                ((f115c - f1164) * sqrt(15.0 / 112.0) -
                (f1134 + f1130) * sqrt(1.0 / 112.0));
    f115c = R3[6][0] * R1[2][1];
    f1164 = R3[0][0] * R1[0][1];
    R4[6][1] = (R1[1][1] * R3[5][0]) * sqrt(12.0 / 7.0) +
                ((f10f0 - f1144) * sqrt(15.0 / 14.0) -
                (f1164 + f115c) * sqrt(1.0 / 14.0));
    f10f0 = R3[6][1] * R1[2][1];
    f1144 = R3[0][1] * R1[0][1];
    R4[6][2] = (R3[5][1] * R1[1][1] + (f10e0 - f10a8) * k_16340ec
                ) - (f1144 + f10f0) * sqrt(1.0 / 24.0);
    f10e0 = R3[6][2] * R1[2][1];
    f10a8 = R3[0][2] * R1[0][1];
    R4[6][3] = (R3[5][2] * R1[1][1]) * sqrt(4.0 / 5.0) +
                ((f10c8 - f112c) * sqrt(1.0 / 2.0) -
                (f10a8 + f10e0) * sqrt(1.0 / 30.0));
    f10b8 = R3[6][4] * R1[2][1];
    R4[6][4] = (f1098 * k_16340d4 -
                (f1160 + R3[6][3] * R1[2][1]) * k_1634130) +
                (R3[5][3] * k_1634104) * R1[1][1];
    f1098 = R3[0][4] * R1[0][1];
    R4[6][5] = (R3[5][4] * R1[1][1]) * sqrt(4.0 / 5.0) +
                ((f10e8 - f1114) * sqrt(1.0 / 2.0) -
                (f1098 + f10b8) * sqrt(1.0 / 30.0));
    f10e8 = (R3[6][5] * R1[2][1]);
    f112c = R3[0][5] * R1[0][1];
    R4[6][6] = (R3[5][5] * R1[1][1] + (f10d0 - f10c0) * k_16340ec
                ) - (f112c + f10e8) * sqrt(1.0 / 24.0);
    f10d0 = R3[6][6] * R1[2][1];
    f10c0 = R3[0][6] * R1[0][1];
    R4[6][7] = (R3[5][6] * R1[1][1]) * sqrt(12.0 / 7.0) +
                ((f10b0 - f1080) * sqrt(15.0 / 14.0) -
                (f10c0 + f10d0) * sqrt(1.0 / 14.0));
    f1080 = R3[0][6] * R1[0][2] - R3[0][0] * R1[0][0];
    f10b0 = R3[6][6] * R1[2][2] - R3[6][0] * R1[2][0];
    R4[6][8] = (R3[5][6] * R1[1][2] - R3[5][0] * R1[1][0]) * sqrt(3.0 / 14.0) +
                ((f1188 - f1174) * sqrt(15.0 / 112.0) -
                (f10b0 + f1080) * sqrt(1.0 / 112.0));
    f10c8 = R3[6][3] * R1[2][1];
    out[22] = WeightedSum(9, &in[16], R4[6]);
    R4[7][1] = (f1168 - f1178) * k_16340b4 + R3[6][0] * R1[1][1];
    R4[7][4] = (f10d8 - f1158) * k_163409c +
                (R3[6][3] * k_16341dc) * R1[1][1];
    R4[7][0] = (R1[1][0] * R3[6][6] + R1[1][2] * R3[6][0]) * sqrt(1.0 / 8.0) +
                (f1154 - f116c) * sqrt(3.0 / 16.0);
    R4[7][2] = (R1[1][1] * R3[6][1]) * sqrt(7.0 / 12.0) +
                (f114c - f1180) * k_16340fc;
    R4[7][3] = (R3[6][2] * R1[1][1]) * sqrt(7.0 / 15.0) +
                (f1100 - f1170) * sqrt(7.0 / 10.0);
    R4[7][7] = (f1148 - f10a0) * k_16340b4 + R3[6][6] * R1[1][1];
    R4[7][5] = (R3[6][4] * R1[1][1]) * sqrt(7.0 / 15.0) +
                (f1090 - f1140) * sqrt(7.0 / 10.0);
    R4[7][6] = (R3[6][5] * R1[1][1]) * sqrt(7.0 / 12.0) +
                (f1088 - f117c) * k_16340fc;
    R4[7][8] = (f1150 - f113c) * sqrt(3.0 / 16.0) +
                sqrt(1.0 / 8.0) * (R3[6][6] * R1[1][2] - R3[6][0] * R1[1][0]);
    out[23] = WeightedSum(9, &in[16], R4[7]);
    R4[8][8] = k_16340dc;
    R4[8][1] = (f115c - f1164) * sqrt(2.0);
    R4[8][0] = (f1134 - f1130) * R4[8][8];
    R4[8][4] = (f10c8 - f1160) * k_16340fc;
    R4[8][2] = (f10f0 - f1144) * sqrt(7.0 / 6.0);
    R4[8][3] = (f10e0 - f10a8) * sqrt(14.0 / 15.0);
    R4[8][5] = (f10b8 - f1098) * sqrt(14.0 / 15.0);
    R4[8][6] = (f10e8 - f112c) * sqrt(7.0 / 6.0);
    R4[8][7] = (f10d0 - f10c0) * sqrt(2.0);
    R4[8][8] = (f10b0 - f1080) * R4[8][8];
    out[24] = WeightedSum(9, &in[16], R4[8]);

    // ---- band 5: R5 from R1 x R4 ----
    if (order <= 5)
        return;
    f1134 = R4[8][0] * R1[0][2] + R4[8][8] * R1[0][0];
    f1130 = R4[0][0] * R1[2][2] + R4[0][8] * R1[2][0];
    R5[0][0] = (f1130 + f1134) * k_16340dc;
    f10a0 = R4[0][3] * R1[2][1];
    f10c8 = R4[8][3] * R1[0][1];
    R5[0][4] = (f10a0 + f10c8) * k_16340e8;
    f115c = R4[8][0] * R1[0][1];
    f1184 = (R4[0][0] * R1[2][1]);
    R5[0][1] = (f1184 + f115c) * sqrt(5.0 / 2.0);
    f10f0 = R4[8][1] * R1[0][1];
    f1164 = R4[0][1] * R1[2][1];
    R5[0][2] = (f1164 + f10f0) * sqrt(45.0 / 32.0);
    f10a8 = R4[8][2] * R1[0][1];
    f10e0 = R4[0][2] * R1[2][1];
    R5[0][3] = (f10e0 + f10a8) * sqrt(15.0 / 14.0);
    f10d8 = R4[8][4] * R1[0][1];
    f1100 = (R4[0][4] * R1[2][1]);
    R5[0][5] = (f1100 + f10d8) * sqrt(9.0 / 10.0);
    f1090 = R4[0][5] * R1[2][1];
    f1098 = R4[8][6] * R1[0][1];
    f1088 = R4[8][5] * R1[0][1];
    R5[0][6] = (f1090 + f1088) * k_16340e8;
    f10b8 = R4[0][6] * R1[2][1];
    f1188 = (R4[8][8] * R1[0][2] - R4[8][0] * R1[0][0]);
    R5[0][7] = (f10b8 + f1098) * sqrt(15.0 / 14.0);
    f1080 = R4[0][8] * R1[2][2] - R4[0][0] * R1[2][0];
    f10d0 = R4[8][7] * R1[0][1];
    R5[0][10] = (f1080 + f1188) * k_16340dc;
    f10e8 = (R4[0][7] * R1[2][1]);
    R5[0][8] = (f10e8 + f10d0) * sqrt(45.0 / 32.0);
    f10b0 = R4[8][8] * R1[0][1];
    f10c0 = R4[0][8] * R1[2][1];
    R5[0][9] = (f10c0 + f10b0) * sqrt(5.0 / 2.0);
    out[25] = WeightedSum(11, &in[25], R5[0]);
    f1154 = R4[7][8] * R1[0][0] + R4[7][0] * R1[0][2];
    f1174 = R4[1][8] * R1[2][0] + R4[1][0] * R1[2][2];
    f116c = R4[1][0] * R1[2][1];
    f1140 = R4[7][3] * R1[0][1];
    f1168 = R4[7][0] * R1[0][1];
    R5[1][0] = (R4[0][0] * R1[1][2] + R4[0][8] * R1[1][0]) * k_1634114 +
                (f1174 + f1154) * k_1634054;
    f1158 = R4[1][3] * R1[2][1];
    R5[1][1] = (f1168 + f116c) * sqrt(2.0) + R4[0][0] * R1[1][1];
    R5[1][4] = (f1140 + f1158) * k_1634104 +
                (R4[0][3] * k_16340f8) * R1[1][1];
    f1178 = R4[1][1] * R1[2][1];
    f114c = R4[7][1] * R1[0][1];
    R5[1][2] = (R4[0][1] * R1[1][1]) * sqrt(9.0 / 16.0) + (f114c + f1178) * k_1634094;
    f1180 = R4[1][2] * R1[2][1];
    f1170 = R4[7][2] * R1[0][1];
    R5[1][3] = (R4[0][2] * R1[1][1]) * sqrt(3.0 / 7.0) +
                (f1170 + f1180) * sqrt(6.0 / 7.0);
    f117c = R4[1][4] * R1[2][1];
    f1148 = R4[7][5] * R1[0][1];
    f113c = R4[1][5] * R1[2][1];
    f1150 = R4[7][4] * R1[0][1];
    R5[1][6] = (f1148 + f113c) * k_1634104 +
                (R4[0][5] * k_16340f8) * R1[1][1];
    f1138 = (R4[7][8] * R1[0][2] - R4[7][0] * R1[0][0]);
    R5[1][5] = (R4[0][4] * R1[1][1]) * sqrt(9.0 / 25.0) + (f1150 + f117c) * k_1634134;
    f1124 = R4[1][8] * R1[2][2] - R4[1][0] * R1[2][0];
    f1144 = R4[1][6] * R1[2][1];
    f112c = R4[7][6] * R1[0][1];
    R5[1][7] = (f112c + f1144) * sqrt(6.0 / 7.0) +
                (R4[0][6] * R1[1][1]) * sqrt(3.0 / 7.0);
    f1114 = R4[1][7] * R1[2][1];
    f1120 = R4[7][7] * R1[0][1];
    R5[1][8] = (f1120 + f1114) * k_1634094 + (R4[0][7] * R1[1][1]) * sqrt(9.0 / 16.0);
    f111c = R4[1][8] * R1[2][1];
    f1128 = R4[7][8] * R1[0][1];
    R5[1][9] = (f1128 + f111c) * sqrt(2.0) + R4[0][8] * R1[1][1];
    R5[1][10] = (R4[0][8] * R1[1][2] - R4[0][0] * R1[1][0]) * k_1634114 +
                (f1124 + f1138) * k_1634054;
    out[26] = WeightedSum(11, &in[25], R5[1]);
    f1078 = R4[2][8] * R1[2][0] + R1[2][2] * R4[2][0];
    f1110 = (R4[6][8] * R1[0][0] + R4[6][0] * R1[0][2]);
    R5[2][0] = ((f1110 + f1078) * sqrt(7.0 / 45.0) -
                (f1130 - f1134) * sqrt(1.0 / 180.0)) +
                (R1[1][2] * R4[1][0] + R4[1][8] * R1[1][0]) * sqrt(8.0 / 45.0);
    f1130 = R4[2][0] * R1[2][1];
    f1134 = R4[6][0] * R1[0][1];
    fVar9 = f1184 - f115c;
    f1184 = (R4[2][1] * R1[2][1]);
    f115c = R4[6][1] * R1[0][1];
    R5[2][1] = ((f1134 + f1130) * sqrt(14.0 / 9.0) - fVar9 * k_16341b0) +
                (R1[1][1] * R4[1][0]) * sqrt(16.0 / 9.0);
    fVar9 = f1164 - f10f0;
    f1164 = R4[2][2] * R1[2][1];
    f10f0 = R4[6][2] * R1[0][1];
    R5[2][2] = ((f115c + f1184) * k_16340fc - fVar9 * k_1634130) +
                R4[1][1] * R1[1][1];
    R5[2][3] = (R4[1][2] * R1[1][1]) * sqrt(16.0 / 21.0) +
                ((f10f0 + f1164) * k_1634150 -
                (f10e0 - f10a8) * sqrt(1.0 / 42.0));
    f10e0 = R4[2][3] * R1[2][1];
    f10a8 = R4[6][3] * R1[0][1];
    R5[2][4] = (R4[1][3] * k_1634150) * R1[1][1] +
                ((f10a8 + f10e0) * sqrt(7.0 / 12.0) -
                (f10a0 - f10c8) * sqrt(1.0 / 48.0));
    f10a0 = R4[2][4] * R1[2][1];
    f10c8 = R4[6][4] * R1[0][1];
    R5[2][5] = (R4[1][4] * R1[1][1]) * sqrt(16.0 / 25.0) +
                ((f10c8 + f10a0) * k_163410c -
                (f1100 - f10d8) * k_1634168);
    f1100 = (R4[2][5] * R1[2][1]);
    f10d8 = R4[6][5] * R1[0][1];
    R5[2][6] = (R4[1][5] * k_1634150) * R1[1][1] +
                ((f10d8 + f1100) * sqrt(7.0 / 12.0) -
                (f1090 - f1088) * sqrt(1.0 / 48.0));
    f1090 = R4[2][6] * R1[2][1];
    f1088 = R4[6][6] * R1[0][1];
    R5[2][8] = ((R4[6][7] * R1[0][1] + R4[2][7] * R1[2][1]) * k_16340fc -
                (f10e8 - f10d0) * k_1634130) +
                R4[1][7] * R1[1][1];
    R5[2][7] = (R4[1][6] * R1[1][1]) * sqrt(16.0 / 21.0) +
                ((f1088 + f1090) * k_1634150 -
                (f10b8 - f1098) * sqrt(1.0 / 42.0));
    f10e8 = (R4[2][8] * R1[2][1]);
    f10d0 = R4[6][8] * R1[0][1];
    R5[2][9] = (R4[1][8] * R1[1][1]) * sqrt(16.0 / 9.0) +
                ((f10d0 + f10e8) * sqrt(14.0 / 9.0) -
                (f10c0 - f10b0) * k_16341b0);
    f10c0 = R4[2][8] * R1[2][2] - R4[2][0] * R1[2][0];
    f10b0 = R4[6][8] * R1[0][2] - R4[6][0] * R1[0][0];
    R5[2][10] = (R4[1][8] * R1[1][2] - R4[1][0] * R1[1][0]) * sqrt(8.0 / 45.0) +
                ((f10b0 + f10c0) * sqrt(7.0 / 45.0) -
                (f1080 - f1188) * sqrt(1.0 / 180.0));
    f10b8 = R4[2][7] * R1[2][1];
    f1098 = R4[6][7] * R1[0][1];
    out[27] = WeightedSum(11, &in[25], R5[2]);
    R5[3][0] = (R4[2][8] * R1[1][0] + R1[1][2] * R4[2][0]) * sqrt(7.0 / 30.0) +
                (((R4[5][8] * R1[0][0] + R1[0][2] * R4[5][0]) +
                 (R4[3][8] * R1[2][0] + R1[2][2] * R4[3][0])) * sqrt(7.0 / 60.0) -
                (f1174 - f1154) * sqrt(1.0 / 60.0));
    R5[3][4] = ((R4[3][3] * R1[2][1] + R4[5][3] * R1[0][1]) * k_16341dc -
                (f1158 - f1140) * k_16340bc) +
                (R4[2][3] * k_16340fc) * R1[1][1];
    R5[3][1] = (R1[1][1] * R4[2][0]) * sqrt(7.0 / 3.0) +
                ((R4[3][0] * R1[2][1] + R4[5][0] * R1[0][1]) * sqrt(7.0 / 6.0) -
                (f116c - f1168) * k_1634084);
    R5[3][2] = (R4[2][1] * R1[1][1]) * sqrt(21.0 / 16.0) +
                ((R4[5][1] * R1[0][1] + R4[3][1] * R1[2][1]) * k_163409c -
                (f1178 - f114c) * k_1634074);
    R5[3][3] = R4[2][2] * R1[1][1] +
                ((R4[5][2] * R1[0][1] + R4[3][2] * R1[2][1]) * sqrt(1.0 / 2.0) -
                (f1180 - f1170) * sqrt(1.0 / 14.0));
    R5[3][6] = ((R4[3][5] * R1[2][1] + R4[5][5] * R1[0][1]) * k_16341dc -
                (f113c - f1148) * k_16340bc) +
                (R4[2][5] * k_16340fc) * R1[1][1];
    R5[3][5] = (R4[2][4] * R1[1][1]) * sqrt(21.0 / 25.0) +
                ((R4[5][4] * R1[0][1] + R4[3][4] * R1[2][1]) * k_16340e4 -
                (f117c - f1150) * k_16340a8);
    R5[3][7] = R4[2][6] * R1[1][1] +
                ((R4[5][6] * R1[0][1] + R4[3][6] * R1[2][1]) * sqrt(1.0 / 2.0) -
                (f1144 - f112c) * sqrt(1.0 / 14.0));
    R5[3][8] = (R4[2][7] * R1[1][1]) * sqrt(21.0 / 16.0) +
                ((R4[5][7] * R1[0][1] + R4[3][7] * R1[2][1]) * k_163409c -
                (f1114 - f1120) * k_1634074);
    R5[3][9] = (R4[2][8] * R1[1][1]) * sqrt(7.0 / 3.0) +
                ((R4[3][8] * R1[2][1] + R4[5][8] * R1[0][1]) * sqrt(7.0 / 6.0) -
                (f111c - f1128) * k_1634084);
    R5[3][10] = (R4[2][8] * R1[1][2] - R4[2][0] * R1[1][0]) * sqrt(7.0 / 30.0) +
                (((R4[5][8] * R1[0][2] - R4[5][0] * R1[0][0]) +
                 (R4[3][8] * R1[2][2] - R4[3][0] * R1[2][0])) * sqrt(7.0 / 60.0) -
                (f1124 - f1138) * sqrt(1.0 / 60.0));
    out[28] = WeightedSum(11, &in[25], R5[3]);
    R5[4][0] = ((R4[4][8] * R1[0][0] + R1[0][2] * R4[4][0]) * k_1634084 +
                (R4[3][8] * R1[1][0] + R1[1][2] * R4[3][0]) * k_16340ac) -
                (f1078 - f1110) * sqrt(1.0 / 30.0);
    df28 = (R4[4][0] * sqrt(5.0 / 3.0));
    R5[4][1] = ((R1[1][1] * R4[3][0]) * sqrt(8.0 / 3.0) -
                (f1130 - f1134) * k_16340b0) +
                R1[0][1] * (R4[4][0] * sqrt(5.0 / 3.0));
    f1078 = R4[4][1] * k_16340e8;
    R5[4][2] = (f1078 * R1[0][1] + (R4[3][1] * k_16340b4) * R1[1][1]) -
                (f1184 - f115c) * sqrt(3.0 / 16.0);
    dd78 = R4[4][2] * sqrt(5.0 / 7.0);
    R5[4][3] = R1[0][1] * dd78 +
                ((R4[3][2] * R1[1][1]) * sqrt(8.0 / 7.0) -
                (f1164 - f10f0) * sqrt(1.0 / 7.0));
    f1138 = (R4[4][3] * k_16340ec);
    R5[4][4] = (f1138 * R1[0][1] + R4[3][3] * R1[1][1]) -
                (f10e0 - f10a8) * sqrt(1.0 / 8.0);
    f1148 = R4[4][4] * k_1634064;
    R5[4][5] = f1148 * R1[0][1] +
                ((R4[3][4] * R1[1][1]) * sqrt(24.0 / 25.0) -
                (f10a0 - f10c8) * k_163405c);
    f1124 = R4[4][5] * k_16340ec;
    R5[4][6] = (f1124 * R1[0][1] + R4[3][5] * R1[1][1]) -
                (f1100 - f10d8) * sqrt(1.0 / 8.0);
    dba8 = (R4[4][6] * sqrt(5.0 / 7.0));
    R5[4][7] = (R4[4][6] * sqrt(5.0 / 7.0)) * R1[0][1] +
                ((R4[3][6] * R1[1][1]) * sqrt(8.0 / 7.0) -
                (f1090 - f1088) * sqrt(1.0 / 7.0));
    f1128 = R4[4][7] * k_16340e8;
    R5[4][8] = (f1128 * R1[0][1] + (R4[3][7] * k_16340b4) * R1[1][1]) -
                (f10b8 - f1098) * sqrt(3.0 / 16.0);
    db88 = (R4[4][8] * sqrt(5.0 / 3.0));
    R5[4][9] = (R4[4][8] * sqrt(5.0 / 3.0)) * R1[0][1] +
                ((R4[3][8] * R1[1][1]) * sqrt(8.0 / 3.0) -
                (f10e8 - f10d0) * k_16340b0);
    R5[4][10] = ((R4[4][8] * R1[0][2] - R4[4][0] * R1[0][0]) * k_1634084 +
                (R4[3][8] * R1[1][2] - R4[3][0] * R1[1][0]) * k_16340ac) -
                (f10c0 - f10b0) * sqrt(1.0 / 30.0);
    out[29] = WeightedSum(11, &in[25], R5[4]);
    f1120 = R4[3][8] * R1[0][0] + R1[0][2] * R4[3][0];
    f111c = R4[5][8] * R1[2][0] + R4[5][0] * R1[2][2];
    R5[5][0] = (R4[4][8] * R1[1][0] + R1[1][2] * R4[4][0]) * sqrt(5.0 / 18.0) -
                (f111c + f1120) * sqrt(1.0 / 9.0);
    f1130 = R4[3][0] * R1[0][1];
    f1160 = (R4[5][0] * R1[2][1]);
    R5[5][1] = (R1[1][1] * R4[4][0]) * sqrt(25.0 / 9.0) -
                (f1160 + f1130) * sqrt(10.0 / 9.0);
    f1184 = (R4[3][1] * R1[0][1]);
    f1134 = R4[5][1] * R1[2][1];
    R5[5][2] = (R4[4][1] * R1[1][1]) * sqrt(25.0 / 16.0) -
                (f1134 + f1184) * k_16340ec;
    f1164 = R4[3][2] * R1[0][1];
    f115c = R4[5][2] * R1[2][1];
    R5[5][3] = (R4[4][2] * R1[1][1]) * sqrt(25.0 / 21.0) -
                (f115c + f1164) * sqrt(10.0 / 21.0);
    f10f0 = R4[3][3] * R1[0][1];
    f1144 = R4[5][3] * R1[2][1];
    R5[5][4] = (R4[4][3] * R1[1][1]) * sqrt(25.0 / 24.0) -
                (f1144 + f10f0) * sqrt(5.0 / 12.0);
    f10a8 = R4[3][4] * R1[0][1];
    f10e0 = R4[5][4] * R1[2][1];
    R5[5][5] = R4[4][4] * R1[1][1] -
                (f10e0 + f10a8) * sqrt(2.0 / 5.0);
    f10a0 = R4[3][5] * R1[0][1];
    f112c = R4[5][5] * R1[2][1];
    R5[5][6] = (R4[4][5] * R1[1][1]) * sqrt(25.0 / 24.0) -
                (f112c + f10a0) * sqrt(5.0 / 12.0);
    f1100 = (R4[3][6] * R1[0][1]);
    f10c8 = R4[5][6] * R1[2][1];
    R5[5][7] = (R4[4][6] * R1[1][1]) * sqrt(25.0 / 21.0) -
                (f10c8 + f1100) * sqrt(10.0 / 21.0);
    f1090 = R4[3][7] * R1[0][1];
    f10d8 = R4[5][7] * R1[2][1];
    R5[5][8] = (R4[4][7] * R1[1][1]) * sqrt(25.0 / 16.0) -
                (f10d8 + f1090) * k_16340ec;
    f10b8 = R4[3][8] * R1[0][1];
    f1088 = R4[5][8] * R1[2][1];
    R5[5][9] = (R4[4][8] * R1[1][1]) * sqrt(25.0 / 9.0) -
                (f1088 + f10b8) * sqrt(10.0 / 9.0);
    f10e8 = (R4[3][8] * R1[0][2] - R4[3][0] * R1[0][0]);
    f1098 = R4[5][8] * R1[2][2] - R4[5][0] * R1[2][0];
    R5[5][10] = (R4[4][8] * R1[1][2] - R4[4][0] * R1[1][0]) * sqrt(5.0 / 18.0) -
                (f1098 + f10e8) * sqrt(1.0 / 9.0);
    out[30] = WeightedSum(11, &in[25], R5[5]);
    f10c0 = R4[2][8] * R1[0][0] + R1[0][2] * R4[2][0];
    f10d0 = R4[6][0] * R1[2][2] + R4[6][8] * R1[2][0];
    R5[6][0] = ((R4[5][8] * R1[1][0] + R4[5][0] * R1[1][2]) * k_16340ac +
                (R4[4][8] * R1[2][0] + R4[4][0] * R1[2][2]) * k_1634084) -
                (f10d0 + f10c0) * sqrt(1.0 / 30.0);
    f1080 = R4[2][0] * R1[0][1];
    f10b0 = R4[6][0] * R1[2][1];
    R5[6][1] = (R1[1][1] * R4[5][0]) * sqrt(8.0 / 3.0) +
                (R1[2][1] * df28 -
                (f10b0 + f1080) * k_16340b0);
    f1188 = (R4[2][1] * R1[0][1]);
    f1114 = R4[6][1] * R1[2][1];
    R5[6][2] = (f1078 * R1[2][1] + (R4[5][1] * k_16340b4) * R1[1][1]) -
                (f1114 + f1188) * sqrt(3.0 / 16.0);
    f1174 = R4[2][2] * R1[0][1];
    f1078 = R4[6][2] * R1[2][1];
    R5[6][3] = (R4[5][2] * R1[1][1]) * sqrt(8.0 / 7.0) +
                (R1[2][1] * dd78 -
                (f1078 + f1174) * sqrt(1.0 / 7.0));
    f1154 = R4[2][3] * R1[0][1];
    f113c = R4[6][3] * R1[2][1];
    R5[6][4] = (f1138 * R1[2][1] + R4[5][3] * R1[1][1]) -
                (f113c + f1154) * sqrt(1.0 / 8.0);
    f1138 = (R4[2][4] * R1[0][1]);
    f1150 = R4[6][4] * R1[2][1];
    R5[6][5] = f1148 * R1[2][1] +
                ((R4[5][4] * R1[1][1]) * sqrt(24.0 / 25.0) -
                (f1150 + f1138) * k_163405c);
    f116c = R4[2][5] * R1[0][1];
    f1148 = R4[6][5] * R1[2][1];
    R5[6][6] = (f1124 * R1[2][1] + R4[5][5] * R1[1][1]) -
                (f1148 + f116c) * sqrt(1.0 / 8.0);
    f1168 = R4[2][6] * R1[0][1];
    f1124 = R4[6][6] * R1[2][1];
    R5[6][7] = (R4[5][6] * R1[1][1]) * sqrt(8.0 / 7.0) +
                (R1[2][1] * dba8 -
                (f1124 + f1168) * sqrt(1.0 / 7.0));
    f1178 = R4[2][7] * R1[0][1];
    f117c = R4[6][7] * R1[2][1];
    R5[6][8] = (f1128 * R1[2][1] + (R4[5][7] * k_16340b4) * R1[1][1]) -
                (f117c + f1178) * sqrt(3.0 / 16.0);
    f114c = R4[2][8] * R1[0][1];
    f1128 = R4[6][8] * R1[2][1];
    R5[6][9] = (R4[5][8] * R1[1][1]) * sqrt(8.0 / 3.0) +
                (R1[2][1] * db88 - (f1128 + f114c) * k_16340b0);
    f1170 = R4[2][8] * R1[0][2] - R4[2][0] * R1[0][0];
    f1180 = R4[6][8] * R1[2][2] - R4[6][0] * R1[2][0];
    R5[6][10] = ((R4[5][8] * R1[1][2] - R4[5][0] * R1[1][0]) * k_16340ac +
                (R4[4][8] * R1[2][2] - R4[4][0] * R1[2][0]) * k_1634084) -
                (f1180 + f1170) * sqrt(1.0 / 30.0);
    out[31] = WeightedSum(11, &in[25], R5[6]);
    f1158 = R1[2][2] * R4[7][0] + R4[7][8] * R1[2][0];
    f1140 = R1[0][2] * R4[1][0] + R1[0][0] * R4[1][8];
    R5[7][0] = (R4[6][8] * R1[1][0] + R1[1][2] * R4[6][0]) * sqrt(7.0 / 30.0) +
                ((f111c - f1120) * sqrt(7.0 / 60.0) -
                (f1140 + f1158) * sqrt(1.0 / 60.0));
    f1120 = R4[1][0] * R1[0][1];
    f111c = R4[7][0] * R1[2][1];
    R5[7][1] = (R1[1][1] * R4[6][0]) * sqrt(7.0 / 3.0) +
                ((f1160 - f1130) * sqrt(7.0 / 6.0) -
                (f111c + f1120) * k_1634084);
    f1130 = R4[1][1] * R1[0][1];
    f1160 = (R4[7][1] * R1[2][1]);
    R5[7][2] = (R4[6][1] * R1[1][1]) * sqrt(21.0 / 16.0) +
                ((f1134 - f1184) * k_163409c -
                (f1160 + f1130) * k_1634074);
    f1184 = (R4[1][2] * R1[0][1]);
    f1134 = R4[7][2] * R1[2][1];
    fVar8 = f1144 - f10f0;
    R5[7][3] = R4[6][2] * R1[1][1] +
                ((f115c - f1164) * sqrt(1.0 / 2.0) -
                (f1134 + f1184) * sqrt(1.0 / 14.0));
    f1164 = R4[1][3] * R1[0][1];
    f1144 = R4[1][4] * R1[0][1];
    f115c = R4[7][3] * R1[2][1];
    f10f0 = R4[7][4] * R1[2][1];
    fVar9 = f10e0 - f10a8;
    R5[7][4] = (fVar8 * k_16341dc - (f115c + f1164) * k_16340bc) +
                (R4[6][3] * k_16340fc) * R1[1][1];
    f10a8 = R4[1][5] * R1[0][1];
    f10e0 = R4[7][5] * R1[2][1];
    R5[7][5] = (R4[6][4] * R1[1][1]) * sqrt(21.0 / 25.0) +
                (fVar9 * k_16340e4 - (f10f0 + f1144) * k_16340a8);
    R5[7][6] = ((f112c - f10a0) * k_16341dc -
                (f10e0 + f10a8) * k_16340bc) +
                (R4[6][5] * k_16340fc) * R1[1][1];
    f112c = R4[1][6] * R1[0][1];
    f10a0 = R4[7][6] * R1[2][1];
    R5[7][7] = R4[6][6] * R1[1][1] +
                ((f10c8 - f1100) * sqrt(1.0 / 2.0) -
                (f10a0 + f112c) * sqrt(1.0 / 14.0));
    f1100 = (R4[1][7] * R1[0][1]);
    f10c8 = R4[7][7] * R1[2][1];
    R5[7][8] = (R4[6][7] * R1[1][1]) * sqrt(21.0 / 16.0) +
                ((f10d8 - f1090) * k_163409c -
                (f10c8 + f1100) * k_1634074);
    f1090 = R1[0][1] * R4[1][8];
    f10d8 = R4[7][8] * R1[2][1];
    R5[7][9] = (R4[6][8] * R1[1][1]) * sqrt(7.0 / 3.0) +
                ((f1088 - f10b8) * sqrt(7.0 / 6.0) -
                (f10d8 + f1090) * k_1634084);
    f1088 = R4[7][8] * R1[2][2] - R4[7][0] * R1[2][0];
    f10b8 = R4[1][8] * R1[0][2] - R4[1][0] * R1[0][0];
    R5[7][10] = (R4[6][8] * R1[1][2] - R4[6][0] * R1[1][0]) * sqrt(7.0 / 30.0) +
                ((f1098 - f10e8) * sqrt(7.0 / 60.0) -
                (f10b8 + f1088) * sqrt(1.0 / 60.0));
    out[32] = WeightedSum(11, &in[25], R5[7]);
    f1098 = R4[8][8] * R1[2][0] + R1[2][2] * R4[8][0];
    f10e8 = (R4[0][8] * R1[0][0] + R1[0][2] * R4[0][0]);
    R5[8][0] = (R1[1][2] * R4[7][0] + R4[7][8] * R1[1][0]) * sqrt(8.0 / 45.0) +
                ((f10d0 - f10c0) * sqrt(7.0 / 45.0) -
                (f10e8 + f1098) * sqrt(1.0 / 180.0));
    f10d0 = R4[8][0] * R1[2][1];
    f10c0 = R4[0][0] * R1[0][1];
    R5[8][2] = ((f1114 - f1188) * k_16340fc -
                (R4[0][1] * R1[0][1] + R4[8][1] * R1[2][1]) * k_1634130) +
                R4[7][1] * R1[1][1];
    R5[8][1] = (R1[1][1] * R4[7][0]) * sqrt(16.0 / 9.0) +
                ((f10b0 - f1080) * sqrt(14.0 / 9.0) -
                (f10c0 + f10d0) * k_16341b0);
    f1188 = (R4[8][2] * R1[2][1]);
    f1114 = R4[0][2] * R1[0][1];
    R5[8][3] = (R4[7][2] * R1[1][1]) * sqrt(16.0 / 21.0) +
                ((f1078 - f1174) * k_1634150 -
                (f1114 + f1188) * sqrt(1.0 / 42.0));
    f1078 = R4[8][3] * R1[2][1];
    f1174 = R4[0][3] * R1[0][1];
    R5[8][4] = (R4[7][3] * k_1634150) * R1[1][1] +
                ((f113c - f1154) * sqrt(7.0 / 12.0) -
                (f1174 + f1078) * sqrt(1.0 / 48.0));
    f1154 = R4[8][4] * R1[2][1];
    f113c = R4[0][4] * R1[0][1];
    R5[8][5] = (R4[7][4] * R1[1][1]) * sqrt(16.0 / 25.0) +
                ((f1150 - f1138) * k_163410c -
                (f113c + f1154) * k_1634168);
    f1138 = (R4[8][5] * R1[2][1]);
    f1150 = R4[0][5] * R1[0][1];
    R5[8][6] = (R4[7][5] * k_1634150) * R1[1][1] +
                ((f1148 - f116c) * sqrt(7.0 / 12.0) -
                (f1150 + f1138) * sqrt(1.0 / 48.0));
    f116c = R4[8][6] * R1[2][1];
    f1148 = R4[0][6] * R1[0][1];
    R5[8][8] = ((f117c - f1178) * k_16340fc -
                (R4[0][7] * R1[0][1] + R4[8][7] * R1[2][1]) * k_1634130) +
                R4[7][7] * R1[1][1];
    R5[8][7] = (R4[7][6] * R1[1][1]) * sqrt(16.0 / 21.0) +
                ((f1124 - f1168) * k_1634150 -
                (f1148 + f116c) * sqrt(1.0 / 42.0));
    f1178 = R4[8][8] * R1[2][1];
    f117c = R4[0][8] * R1[0][1];
    R5[8][9] = (R4[7][8] * R1[1][1]) * sqrt(16.0 / 9.0) +
                ((f1128 - f114c) * sqrt(14.0 / 9.0) -
                (f117c + f1178) * k_16341b0);
    f1128 = R4[8][8] * R1[2][2] - R4[8][0] * R1[2][0];
    f114c = R4[0][8] * R1[0][2] - R4[0][0] * R1[0][0];
    R5[8][10] = (R4[7][8] * R1[1][2] - R4[7][0] * R1[1][0]) * sqrt(8.0 / 45.0) +
                ((f1180 - f1170) * sqrt(7.0 / 45.0) -
                (f114c + f1128) * sqrt(1.0 / 180.0));
    f1168 = R4[0][7] * R1[0][1];
    f1124 = R4[8][7] * R1[2][1];
    f1080 = R4[0][1] * R1[0][1];
    f10b0 = R4[8][1] * R1[2][1];
    out[33] = WeightedSum(11, &in[25], R5[8]);
    R5[9][1] = (f111c - f1120) * sqrt(2.0) + R4[8][0] * R1[1][1];
    R5[9][0] = (R4[8][0] * R1[1][2] + R4[8][8] * R1[1][0]) * k_1634114 +
                (f1158 - f1140) * k_1634054;
    R5[9][2] = (f1160 - f1130) * k_1634094 +
                (R4[8][1] * R1[1][1]) * sqrt(9.0 / 16.0);
    R5[9][4] = (f115c - f1164) * k_1634104 + (R4[8][3] * k_16340f8) * R1[1][1];
    R5[9][3] = (f1134 - f1184) * sqrt(6.0 / 7.0) +
                (R4[8][2] * R1[1][1]) * sqrt(3.0 / 7.0);
    R5[9][5] = (R4[8][4] * R1[1][1]) * sqrt(9.0 / 25.0) +
                (f10f0 - f1144) * k_1634134;
    R5[9][6] = (f10e0 - f10a8) * k_1634104 +
                (R4[8][5] * k_16340f8) * R1[1][1];
    R5[9][7] = (f10a0 - f112c) * sqrt(6.0 / 7.0) +
                (R4[8][6] * R1[1][1]) * sqrt(3.0 / 7.0);
    R5[9][10] = (R4[8][8] * R1[1][2] - R4[8][0] * R1[1][0]) * k_1634114 +
                (f1088 - f10b8) * k_1634054;
    R5[9][8] = (f10c8 - f1100) * k_1634094 +
                (R4[8][7] * R1[1][1]) * sqrt(9.0 / 16.0);
    R5[9][9] = (f10d8 - f1090) * sqrt(2.0) +
                R4[8][8] * R1[1][1];
    out[34] = WeightedSum(11, &in[25], R5[9]);
    R5[10][10] = k_16340dc;
    R5[10][1] = (f10d0 - f10c0) * sqrt(5.0 / 2.0);
    R5[10][0] = (f1098 - f10e8) * R5[10][10];
    R5[10][4] = (f1078 - f1174) * k_16340e8;
    R5[10][2] = (f10b0 - f1080) * sqrt(45.0 / 32.0);
    R5[10][3] = (f1188 - f1114) * sqrt(15.0 / 14.0);
    R5[10][5] = (f1154 - f113c) * sqrt(9.0 / 10.0);
    R5[10][7] = (f116c - f1148) * sqrt(15.0 / 14.0);
    R5[10][6] = (f1138 - f1150) * k_16340e8;
    R5[10][10] = (f1128 - f114c) * R5[10][10];
    R5[10][8] = (f1124 - f1168) * sqrt(45.0 / 32.0);
    R5[10][9] = (f1178 - f117c) * sqrt(5.0 / 2.0);
    out[35] = WeightedSum(11, &in[25], R5[10]);

    // ---- band 6: R6 from R1 x R5 ----
    if (order <= 6)
        return;
    f1138 = (R5[10][10] * R1[0][0] + R5[10][0] * R1[0][2]);
    f1078 = R5[0][10] * R1[2][0] + R5[0][0] * R1[2][2];
    R6[0][0] = (f1078 + f1138) * k_16340dc;
    f1124 = R5[0][0] * R1[2][1];
    f1128 = R5[10][0] * R1[0][1];
    R6[0][1] = (f1128 + f1124) * sqrt(3.0);
    f111c = R5[0][1] * R1[2][1];
    f1120 = R5[10][1] * R1[0][1];
    R6[0][2] = (f1120 + f111c) * sqrt(33.0 / 20.0);
    f1160 = (R5[0][2] * R1[2][1]);
    f1130 = R5[10][2] * R1[0][1];
    R6[0][3] = (f1130 + f1160) * sqrt(11.0 / 9.0);
    f1134 = R5[0][3] * R1[2][1];
    f1184 = (R5[10][3] * R1[0][1]);
    R6[0][4] = (f1184 + f1134) * sqrt(33.0 / 32.0);
    f115c = R5[0][4] * R1[2][1];
    f1164 = R5[10][4] * R1[0][1];
    f10d0 = R5[0][10] * R1[2][2] - R5[0][0] * R1[2][0];
    f10c0 = R5[10][10] * R1[0][2] - R5[10][0] * R1[0][0];
    R6[0][5] = (f1164 + f115c) * sqrt(33.0 / 35.0);
    R6[0][12] = (f10d0 + f10c0) * k_16340dc;
    f10f0 = R5[0][5] * R1[2][1];
    f10e0 = R5[10][5] * R1[0][1];
    R6[0][6] = (f10e0 + f10f0) * sqrt(11.0 / 12.0);
    f10a8 = R5[0][6] * R1[2][1];
    f10a0 = R5[10][6] * R1[0][1];
    R6[0][7] = (f10a0 + f10a8) * sqrt(33.0 / 35.0);
    f10c8 = R5[0][7] * R1[2][1];
    f1100 = (R5[10][7] * R1[0][1]);
    R6[0][8] = (f1100 + f10c8) * sqrt(33.0 / 32.0);
    f10d8 = R5[0][8] * R1[2][1];
    f1090 = R5[10][8] * R1[0][1];
    R6[0][9] = (f1090 + f10d8) * sqrt(11.0 / 9.0);
    f1088 = R5[0][9] * R1[2][1];
    f10b8 = R5[10][9] * R1[0][1];
    R6[0][10] = (f10b8 + f1088) * sqrt(33.0 / 20.0);
    f1098 = R5[0][10] * R1[2][1];
    f10e8 = (R5[10][10] * R1[0][1]);
    R6[0][11] = (f10e8 + f1098) * sqrt(3.0);
    out[36] = WeightedSum(13, &in[36], R6[0]);
    f1080 = R1[0][2] * R5[9][0] + R5[9][10] * R1[0][0];
    f10b0 = R5[1][10] * R1[2][0] + R5[1][0] * R1[2][2];
    R6[1][0] = (R1[1][2] * R5[0][0] + R1[1][0] * R5[0][10]) * k_163407c +
                (f10b0 + f1080) * sqrt(5.0 / 24.0);
    f1188 = (R5[1][0] * R1[2][1]);
    f1174 = R5[9][0] * R1[0][1];
    R6[1][1] = (f1174 + f1188) * sqrt(5.0 / 2.0) +
                R5[0][0] * R1[1][1];
    f1154 = R5[1][1] * R1[2][1];
    f116c = R5[9][1] * R1[0][1];
    R6[1][2] = (R5[0][1] * R1[1][1]) * sqrt(11.0 / 20.0) +
                (f116c + f1154) * sqrt(11.0 / 8.0);
    f1168 = R5[1][2] * R1[2][1];
    f1178 = R5[9][2] * R1[0][1];
    R6[1][3] = (R5[0][2] * R1[1][1]) * sqrt(11.0 / 27.0) +
                (f1178 + f1168) * sqrt(55.0 / 54.0);
    f114c = R5[1][3] * R1[2][1];
    f1180 = R5[9][3] * R1[0][1];
    R6[1][4] = (R5[0][3] * R1[1][1]) * sqrt(11.0 / 32.0) +
                (f1180 + f114c) * sqrt(55.0 / 64.0);
    f1170 = R5[1][4] * R1[2][1];
    f1158 = R5[9][4] * R1[0][1];
    R6[1][5] = (R5[0][4] * R1[1][1]) * sqrt(11.0 / 35.0) +
                (f1158 + f1170) * sqrt(11.0 / 14.0);
    f1140 = R5[1][5] * R1[2][1];
    f117c = R5[9][5] * R1[0][1];
    R6[1][6] = (R5[0][5] * R1[1][1]) * sqrt(11.0 / 36.0) +
                (f1140 + f117c) * sqrt(55.0 / 72.0);
    f113c = R5[9][6] * R1[0][1];
    f1150 = R5[1][6] * R1[2][1];
    R6[1][7] = (R5[0][6] * R1[1][1]) * sqrt(11.0 / 35.0) +
                (f1150 + f113c) * sqrt(11.0 / 14.0);
    f1144 = R5[9][7] * R1[0][1];
    f1148 = R5[1][7] * R1[2][1];
    R6[1][8] = (R5[0][7] * R1[1][1]) * sqrt(11.0 / 32.0) +
                (f1148 + f1144) * sqrt(55.0 / 64.0);
    f1114 = R5[9][8] * R1[0][1];
    f112c = R5[1][8] * R1[2][1];
    R6[1][9] = (R5[0][8] * R1[1][1]) * sqrt(11.0 / 27.0) +
                (f112c + f1114) * sqrt(55.0 / 54.0);
    f1068 = R5[9][9] * R1[0][1];
    f1060 = R5[1][9] * R1[2][1];
    R6[1][10] = (R5[0][9] * R1[1][1]) * sqrt(11.0 / 20.0) +
                (f1060 + f1068) * sqrt(11.0 / 8.0);
    f1058 = R5[9][10] * R1[0][1];
    f1050 = R5[1][10] * R1[2][1];
    R6[1][11] = (f1050 + f1058) * sqrt(5.0 / 2.0) + R5[0][10] * R1[1][1];
    f1104 = (R5[9][10] * R1[0][2] - R5[9][0] * R1[0][0]);
    f10f4 = R5[1][10] * R1[2][2] - R5[1][0] * R1[2][0];
    R6[1][12] = (f10f4 + f1104) * sqrt(5.0 / 24.0) +
                (R5[0][10] * R1[1][2] - R5[0][0] * R1[1][0]) * k_163407c;
    out[37] = WeightedSum(13, &in[36], R6[1]);
    f10f8 = R1[2][2] * R5[2][0] + R5[2][10] * R1[2][0];
    f1118 = (R5[8][0] * R1[0][2] + R5[8][10] * R1[0][0]);
    R6[2][0] = ((f1118 + f10f8) * sqrt(15.0 / 88.0) -
                (f1078 - f1138) * sqrt(1.0 / 264.0)) +
                (R1[1][0] * R5[1][10] + R1[1][2] * R5[1][0]) * sqrt(5.0 / 33.0);
    f1078 = R5[2][0] * R1[2][1];
    f1138 = (R5[8][0] * R1[0][1]);
    R6[2][1] = (R1[1][1] * R5[1][0]) * sqrt(20.0 / 11.0) +
                ((f1138 + f1078) * sqrt(45.0 / 22.0) -
                (f1124 - f1128) * sqrt(1.0 / 22.0));
    f1124 = R5[2][1] * R1[2][1];
    f1128 = R5[8][1] * R1[0][1];
    R6[2][2] = (R5[1][1] * R1[1][1] + (f1128 + f1124) * k_1634094) -
                (f111c - f1120) * sqrt(1.0 / 40.0);
    f111c = R5[2][2] * R1[2][1];
    f1120 = R5[8][2] * R1[0][1];
    R6[2][3] = (R5[1][2] * R1[1][1]) * sqrt(20.0 / 27.0) +
                ((f1120 + f111c) * k_1634078 -
                (f1160 - f1130) * sqrt(1.0 / 54.0));
    f1160 = (R5[2][3] * R1[2][1]);
    f1130 = R5[8][3] * R1[0][1];
    R6[2][4] = (R5[1][3] * k_16340ec) * R1[1][1] +
                ((f1130 + f1160) * sqrt(45.0 / 64.0) -
                (f1134 - f1184) * sqrt(1.0 / 64.0));
    f1134 = R5[2][4] * R1[2][1];
    f1184 = (R5[8][4] * R1[0][1]);
    R6[2][5] = (R5[1][4] * R1[1][1]) * sqrt(4.0 / 7.0) +
                ((f1184 + f1134) * sqrt(9.0 / 14.0) -
                (f115c - f1164) * sqrt(1.0 / 70.0));
    f115c = R5[2][5] * R1[2][1];
    f1164 = R5[8][5] * R1[0][1];
    R6[2][6] = ((R5[1][5] * k_16340cc) * R1[1][1] +
                (f1164 + f115c) * k_16340ec) -
                (f10f0 - f10e0) * sqrt(1.0 / 72.0);
    f10f0 = R5[2][6] * R1[2][1];
    f10e0 = R5[8][6] * R1[0][1];
    R6[2][7] = (R5[1][6] * R1[1][1]) * sqrt(4.0 / 7.0) +
                ((f10e0 + f10f0) * sqrt(9.0 / 14.0) -
                (f10a8 - f10a0) * sqrt(1.0 / 70.0));
    f10a8 = R5[2][7] * R1[2][1];
    f10a0 = R5[8][7] * R1[0][1];
    R6[2][8] = (R5[1][7] * k_16340ec) * R1[1][1] +
                ((f10a0 + f10a8) * sqrt(45.0 / 64.0) -
                (f10c8 - f1100) * sqrt(1.0 / 64.0));
    f10c8 = R5[2][8] * R1[2][1];
    f1100 = (R5[8][8] * R1[0][1]);
    R6[2][9] = (R5[1][8] * R1[1][1]) * sqrt(20.0 / 27.0) +
                ((f1100 + f10c8) * k_1634078 -
                (f10d8 - f1090) * sqrt(1.0 / 54.0));
    f10d8 = R5[2][9] * R1[2][1];
    f1090 = R5[8][9] * R1[0][1];
    R6[2][10] = (R5[1][9] * R1[1][1] +
                (f1090 + f10d8) * k_1634094) -
                (f1088 - f10b8) * sqrt(1.0 / 40.0);
    f1088 = R5[2][10] * R1[2][1];
    f10b8 = R5[8][10] * R1[0][1];
    R6[2][11] = (R5[1][10] * R1[1][1]) * sqrt(20.0 / 11.0) +
                ((f10b8 + f1088) * sqrt(45.0 / 22.0) -
                (f1098 - f10e8) * sqrt(1.0 / 22.0));
    f1098 = R5[2][10] * R1[2][2] - R5[2][0] * R1[2][0];
    f10e8 = (R5[8][10] * R1[0][2] - R5[8][0] * R1[0][0]);
    R6[2][12] = (R5[1][10] * R1[1][2] - R5[1][0] * R1[1][0]) * sqrt(5.0 / 33.0) +
                ((f10e8 + f1098) * sqrt(15.0 / 88.0) -
                (f10d0 - f10c0) * sqrt(1.0 / 264.0));
    out[38] = WeightedSum(13, &in[36], R6[2]);
    f1110 = (R1[2][2] * R5[3][0] + R5[3][10] * R1[2][0]);
    f10d0 = R1[0][2] * R5[7][0] + R5[7][10] * R1[0][0];
    R6[3][0] = ((f10d0 + f1110) * sqrt(3.0 / 22.0) -
                (f10b0 - f1080) * sqrt(1.0 / 88.0)) +
                (R5[2][0] * R1[1][2] + R5[2][10] * R1[1][0]) * sqrt(9.0 / 44.0);
    f10c0 = R5[3][0] * R1[2][1];
    f10b0 = R5[7][0] * R1[0][1];
    R6[3][1] = (R1[1][1] * R5[2][0]) * sqrt(27.0 / 11.0) +
                ((f10b0 + f10c0) * sqrt(18.0 / 11.0) -
                (f1188 - f1174) * sqrt(3.0 / 22.0));
    f1174 = R5[3][2] * R1[2][1];
    f1080 = R5[3][1] * R1[2][1];
    f1188 = (R5[7][1] * R1[0][1]);
    R6[3][3] = ((R5[7][2] * R1[0][1] + f1174) * k_1634150 -
                (f1168 - f1178) * k_16341b0) + R5[2][2] * R1[1][1];
    R6[3][2] = (R5[2][1] * R1[1][1]) * sqrt(27.0 / 20.0) +
                ((f1188 + f1080) * sqrt(9.0 / 10.0) -
                (f1154 - f116c) * sqrt(3.0 / 40.0));
    f116c = R5[3][3] * R1[2][1];
    f1168 = R5[7][3] * R1[0][1];
    R6[3][4] = (R5[2][3] * R1[1][1]) * sqrt(27.0 / 32.0) +
                ((f1168 + f116c) * sqrt(9.0 / 16.0) -
                (f114c - f1180) * sqrt(3.0 / 64.0));
    f1178 = R5[3][4] * R1[2][1];
    f114c = R5[7][4] * R1[0][1];
    R6[3][5] = (R5[2][4] * R1[1][1]) * sqrt(27.0 / 35.0) +
                ((f114c + f1178) * sqrt(18.0 / 35.0) -
                (f1170 - f1158) * sqrt(3.0 / 70.0));
    f1180 = R5[3][5] * R1[2][1];
    f1170 = R5[7][5] * R1[0][1];
    R6[3][6] = (R5[2][5] * k_1634104) * R1[1][1] +
                ((f1170 + f1180) * sqrt(1.0 / 2.0) -
                (f1140 - f117c) * sqrt(1.0 / 24.0));
    f1158 = R5[3][6] * R1[2][1];
    f1140 = R5[7][6] * R1[0][1];
    R6[3][7] = (R5[2][6] * R1[1][1]) * sqrt(27.0 / 35.0) +
                ((f1140 + f1158) * sqrt(18.0 / 35.0) -
                (f1150 - f113c) * sqrt(3.0 / 70.0));
    f117c = R5[3][7] * R1[2][1];
    f1150 = R5[7][7] * R1[0][1];
    R6[3][8] = (R5[2][7] * R1[1][1]) * sqrt(27.0 / 32.0) +
                ((f1150 + f117c) * sqrt(9.0 / 16.0) -
                (f1148 - f1144) * sqrt(3.0 / 64.0));
    f1144 = R5[3][9] * R1[2][1];
    R6[3][9] = ((R5[7][8] * R1[0][1] + R5[3][8] * R1[2][1]) * k_1634150 -
                (f112c - f1114) * k_16341b0) + R5[2][8] * R1[1][1];
    f112c = R5[7][9] * R1[0][1];
    R6[3][10] = (R5[2][9] * R1[1][1]) * sqrt(27.0 / 20.0) +
                ((f112c + f1144) * sqrt(9.0 / 10.0) -
                (f1060 - f1068) * sqrt(3.0 / 40.0));
    f1068 = R5[3][10] * R1[2][1];
    f1060 = R5[7][10] * R1[0][1];
    R6[3][11] = (R5[2][10] * R1[1][1]) * sqrt(27.0 / 11.0) +
                ((f1060 + f1068) * sqrt(18.0 / 11.0) -
                (f1050 - f1058) * sqrt(3.0 / 22.0));
    f1058 = R5[3][10] * R1[2][2] - R5[3][0] * R1[2][0];
    f1050 = R5[7][10] * R1[0][2] - R5[7][0] * R1[0][0];
    R6[3][12] = (R5[2][10] * R1[1][2] - R5[2][0] * R1[1][0]) * sqrt(9.0 / 44.0) +
                ((f1050 + f1058) * sqrt(3.0 / 22.0) -
                (f10f4 - f1104) * sqrt(1.0 / 88.0));
    f1154 = R5[7][2] * R1[0][1];
    f1148 = R5[7][8] * R1[0][1];
    f113c = R5[3][8] * R1[2][1];
    out[39] = WeightedSum(13, &in[36], R6[3]);
    R6[4][0] = (((R5[6][10] * R1[0][0] + R1[0][2] * R5[6][0]) +
                 (R1[2][2] * R5[4][0] + R5[4][10] * R1[2][0])) * sqrt(7.0 / 66.0) -
                (f10f8 - f1118) * sqrt(1.0 / 44.0)) +
                (R5[3][0] * R1[1][2] + R5[3][10] * R1[1][0]) * sqrt(8.0 / 33.0);
    R6[4][1] = (R1[1][1] * R5[3][0]) * sqrt(32.0 / 11.0) +
                ((R5[6][0] * R1[0][1] + R5[4][0] * R1[2][1]) * sqrt(14.0 / 11.0) -
                (f1078 - f1138) * sqrt(3.0 / 11.0));
    R6[4][2] = (R5[3][1] * k_16341ec) * R1[1][1] +
                ((R5[4][1] * R1[2][1] + R5[6][1] * R1[0][1]) * sqrt(7.0 / 10.0) -
                (f1124 - f1128) * sqrt(3.0 / 20.0));
    R6[4][4] = ((R5[4][3] * R1[2][1] + R5[6][3] * R1[0][1]) * k_16341dc -
                (f1160 - f1130) * k_1634074) + R5[3][3] * R1[1][1];
    R6[4][3] = (R5[3][2] * R1[1][1]) * sqrt(32.0 / 27.0) +
                ((R5[6][2] * R1[0][1] + R5[4][2] * R1[2][1]) * sqrt(14.0 / 27.0) -
                (f111c - f1120) * sqrt(1.0 / 9.0));
    R6[4][5] = (R5[3][4] * R1[1][1]) * sqrt(32.0 / 35.0) +
                ((R5[6][4] * R1[0][1] + R5[4][4] * R1[2][1]) * sqrt(2.0 / 5.0) -
                (f1134 - f1184) * sqrt(3.0 / 35.0));
    R6[4][6] = (R5[3][5] * k_16341e0) * R1[1][1] +
                ((R5[6][5] * R1[0][1] + R5[4][5] * R1[2][1]) * sqrt(7.0 / 18.0) -
                (f115c - f1164) * k_163407c);
    R6[4][8] = ((R5[4][7] * R1[2][1] + R5[6][7] * R1[0][1]) * k_16341dc -
                (f10a8 - f10a0) * k_1634074) +
                R5[3][7] * R1[1][1];
    R6[4][7] = (R5[3][6] * R1[1][1]) * sqrt(32.0 / 35.0) +
                ((R5[6][6] * R1[0][1] + R5[4][6] * R1[2][1]) * sqrt(2.0 / 5.0) -
                (f10f0 - f10e0) * sqrt(3.0 / 35.0));
    R6[4][9] = (R5[3][8] * R1[1][1]) * sqrt(32.0 / 27.0) +
                ((R5[6][8] * R1[0][1] + R5[4][8] * R1[2][1]) * sqrt(14.0 / 27.0) -
                (f10c8 - f1100) * sqrt(1.0 / 9.0));
    R6[4][10] = (R5[3][9] * k_16341ec) * R1[1][1] +
                ((R5[6][9] * R1[0][1] + R5[4][9] * R1[2][1]) * sqrt(7.0 / 10.0) -
                (f10d8 - f1090) * sqrt(3.0 / 20.0));
    R6[4][11] = (R5[3][10] * R1[1][1]) * sqrt(32.0 / 11.0) +
                ((R5[4][10] * R1[2][1] + R5[6][10] * R1[0][1]) * sqrt(14.0 / 11.0) -
                (f1088 - f10b8) * sqrt(3.0 / 11.0));
    R6[4][12] = (R5[3][10] * R1[1][2] - R5[3][0] * R1[1][0]) * sqrt(8.0 / 33.0) +
                (((R5[4][10] * R1[2][2] - R5[4][0] * R1[2][0]) +
                 (R5[6][10] * R1[0][2] - R5[6][0] * R1[0][0])) * sqrt(7.0 / 66.0) -
                (f1098 - f10e8) * sqrt(1.0 / 44.0));
    out[40] = WeightedSum(13, &in[36], R6[4]);
    R6[5][0] = (R1[1][2] * R5[4][0] + R5[4][10] * R1[1][0]) * sqrt(35.0 / 132.0) +
                ((R1[0][2] * R5[5][0] + R5[5][10] * R1[0][0]) * sqrt(7.0 / 44.0) -
                (f1110 - f10d0) * sqrt(5.0 / 132.0));
    dba8 = (R5[5][0] * sqrt(21.0 / 11.0));
    R6[5][1] = (R1[1][1] * R5[4][0]) * sqrt(35.0 / 11.0) +
                (R1[0][1] * (R5[5][0] * sqrt(21.0 / 11.0)) -
                (f10c0 - f10b0) * sqrt(5.0 / 11.0));
    db88 = (R5[5][1] * sqrt(21.0 / 20.0));
    R6[5][2] = (R5[4][1] * R1[1][1]) * sqrt(7.0 / 4.0) +
                ((R5[5][1] * sqrt(21.0 / 20.0)) * R1[0][1] -
                (f1080 - f1188) * k_16340dc);
    df80 = R5[5][2] * sqrt(7.0 / 9.0);
    R6[5][3] = R1[0][1] * df80 +
                ((R5[4][2] * R1[1][1]) * sqrt(35.0 / 27.0) -
                (f1174 - f1154) * sqrt(5.0 / 27.0));
    f10f8 = R5[5][3] * k_163409c;
    R6[5][4] = (R5[4][3] * R1[1][1]) * sqrt(35.0 / 32.0) +
                (f10f8 * R1[0][1] - (f116c - f1168) * sqrt(5.0 / 32.0));
    f1104 = (R5[5][4] * k_1634064);
    R6[5][5] = (f1104 * R1[0][1] + R5[4][4] * R1[1][1]) -
                (f1178 - f114c) * sqrt(1.0 / 7.0);
    dd20 = (R5[5][5] * sqrt(7.0 / 12.0));
    R6[5][6] = R1[0][1] * (R5[5][5] * sqrt(7.0 / 12.0)) +
                ((R5[4][5] * R1[1][1]) * sqrt(35.0 / 36.0) -
                (f1180 - f1170) * sqrt(5.0 / 36.0));
    f10f4 = R5[5][6] * k_1634064;
    R6[5][7] = (f10f4 * R1[0][1] + R5[4][6] * R1[1][1]) -
                (f1158 - f1140) * sqrt(1.0 / 7.0);
    f1110 = (R5[5][7] * k_163409c);
    R6[5][8] = (R5[4][7] * R1[1][1]) * sqrt(35.0 / 32.0) +
                (f1110 * R1[0][1] - (f117c - f1150) * sqrt(5.0 / 32.0));
    dd30 = (R5[5][8] * sqrt(7.0 / 9.0));
    R6[5][9] = R1[0][1] * (R5[5][8] * sqrt(7.0 / 9.0)) +
                ((R5[4][8] * R1[1][1]) * sqrt(35.0 / 27.0) -
                (f113c - f1148) * sqrt(5.0 / 27.0));
    dd78 = (R5[5][9] * sqrt(21.0 / 20.0));
    R6[5][10] = R1[0][1] * (R5[5][9] * sqrt(21.0 / 20.0)) +
                ((R5[4][9] * R1[1][1]) * sqrt(7.0 / 4.0) -
                (f1144 - f112c) * k_16340dc);
    df28 = (R5[5][10] * sqrt(21.0 / 11.0));
    R6[5][11] = R1[0][1] * (R5[5][10] * sqrt(21.0 / 11.0)) +
                ((R5[4][10] * R1[1][1]) * sqrt(35.0 / 11.0) -
                (f1068 - f1060) * sqrt(5.0 / 11.0));
    R6[5][12] = ((R5[5][10] * R1[0][2] - R5[5][0] * R1[0][0]) * sqrt(7.0 / 44.0) -
                (f1058 - f1050) * sqrt(5.0 / 132.0)) +
                (R5[4][10] * R1[1][2] - R5[4][0] * R1[1][0]) * sqrt(35.0 / 132.0);
    out[41] = WeightedSum(13, &in[36], R6[5]);
    f1058 = R5[6][10] * R1[2][0] + R1[2][2] * R5[6][0];
    f1050 = R1[0][2] * R5[4][0] + R5[4][10] * R1[0][0];
    R6[6][0] = (R1[1][2] * R5[5][0] + R5[5][10] * R1[1][0]) * sqrt(3.0 / 11.0) -
                (f1050 + f1058) * sqrt(5.0 / 44.0);
    f1078 = R5[4][1] * R1[0][1];
    f1060 = R5[6][1] * R1[2][1];
    R6[6][2] = (R5[5][1] * k_1634080) * R1[1][1] -
                (f1078 + f1060) * k_1634104;
    f1124 = R5[4][2] * R1[0][1];
    f1138 = (R5[6][2] * R1[2][1]);
    R6[6][3] = (R5[5][2] * k_16341f4) * R1[1][1] -
                (f1124 + f1138) * k_16340cc;
    f1128 = R5[6][3] * R1[2][1];
    f111c = R5[4][3] * R1[0][1];
    R6[6][4] = (R5[5][3] * k_1634094) * R1[1][1] -
                (f111c + f1128) * k_16340d4;
    f1068 = R5[6][0] * R1[2][1];
    f117c = R5[4][0] * R1[0][1];
    R6[6][1] = (R1[1][1] * R5[5][0]) * sqrt(36.0 / 11.0) -
                (f117c + f1068) * sqrt(15.0 / 11.0);
    f1120 = R5[6][4] * R1[2][1];
    f1150 = R5[4][4] * R1[0][1];
    f1184 = (R5[6][7] * R1[2][1]);
    f115c = R5[4][7] * R1[0][1];
    R6[6][5] = (R5[5][4] * R1[1][1]) * sqrt(36.0 / 35.0) -
                (f1150 + f1120) * sqrt(3.0 / 7.0);
    R6[6][8] = (R5[5][7] * k_1634094) * R1[1][1] -
                (f115c + f1184) * k_16340d4;
    f10f0 = R5[4][8] * R1[0][1];
    f1160 = (R5[6][5] * R1[2][1]);
    f1164 = R5[6][8] * R1[2][1];
    f1130 = R5[4][5] * R1[0][1];
    R6[6][9] = (R5[5][8] * k_16341f4) * R1[1][1] -
                (f10f0 + f1164) * k_16340cc;
    f10e0 = R5[6][9] * R1[2][1];
    f10a8 = R5[4][9] * R1[0][1];
    R6[6][10] = (R5[5][9] * k_1634080) * R1[1][1] -
                (f10a8 + f10e0) * k_1634104;
    R6[6][6] = R5[5][5] * R1[1][1] -
                (f1130 + f1160) * sqrt(5.0 / 12.0);
    f1134 = R5[6][6] * R1[2][1];
    f113c = R5[4][6] * R1[0][1];
    R6[6][7] = (R5[5][6] * R1[1][1]) * sqrt(36.0 / 35.0) -
                (f113c + f1134) * sqrt(3.0 / 7.0);
    f10c8 = R5[4][10] * R1[0][1];
    f10a0 = R5[6][10] * R1[2][1];
    R6[6][11] = (R5[5][10] * R1[1][1]) * sqrt(36.0 / 11.0) -
                (f10a0 + f10c8) * sqrt(15.0 / 11.0);
    f1100 = (R5[6][10] * R1[2][2] - R5[6][0] * R1[2][0]);
    f10d8 = R5[4][10] * R1[0][2] - R5[4][0] * R1[0][0];
    R6[6][12] = (R5[5][10] * R1[1][2] - R5[5][0] * R1[1][0]) * sqrt(3.0 / 11.0) -
                (f10d8 + f1100) * sqrt(5.0 / 44.0);
    out[42] = WeightedSum(13, &in[36], R6[6]);
    f1088 = R1[0][2] * R5[3][0] + R5[3][10] * R1[0][0];
    f1090 = R5[7][10] * R1[2][0] + R5[7][0] * R1[2][2];
    R6[7][0] = (R5[5][0] * R1[2][2] + R5[5][10] * R1[2][0]) * sqrt(7.0 / 44.0) +
                ((R5[6][10] * R1[1][0] + R1[1][2] * R5[6][0]) * sqrt(35.0 / 132.0) -
                (f1090 + f1088) * sqrt(5.0 / 132.0));
    f10b8 = R5[3][0] * R1[0][1];
    f1148 = R5[7][0] * R1[2][1];
    R6[7][1] = dba8 * R1[2][1] +
                ((R1[1][1] * R5[6][0]) * sqrt(35.0 / 11.0) -
                (f1148 + f10b8) * sqrt(5.0 / 11.0));
    f1098 = R5[3][1] * R1[0][1];
    f1144 = R5[7][1] * R1[2][1];
    R6[7][2] = R1[2][1] * db88 +
                ((R5[6][1] * R1[1][1]) * sqrt(7.0 / 4.0) -
                (f1144 + f1098) * k_16340dc);
    f10e8 = (R5[3][2] * R1[0][1]);
    f112c = R5[7][2] * R1[2][1];
    R6[7][3] = R1[2][1] * df80 +
                ((R5[6][2] * R1[1][1]) * sqrt(35.0 / 27.0) -
                (f112c + f10e8) * sqrt(5.0 / 27.0));
    f10c0 = R5[3][3] * R1[0][1];
    f10d0 = R5[7][3] * R1[2][1];
    R6[7][4] = (R5[6][3] * R1[1][1]) * sqrt(35.0 / 32.0) +
                (f10f8 * R1[2][1] -
                (f10d0 + f10c0) * sqrt(5.0 / 32.0));
    f10f8 = R5[3][4] * R1[0][1];
    f1114 = R5[7][4] * R1[2][1];
    R6[7][5] = (f1104 * R1[2][1] + R5[6][4] * R1[1][1]) -
                (f1114 + f10f8) * sqrt(1.0 / 7.0);
    f1104 = (R5[3][5] * R1[0][1]);
    f1140 = R5[7][5] * R1[2][1];
    R6[7][6] = R1[2][1] * dd20 +
                ((R5[6][5] * R1[1][1]) * sqrt(35.0 / 36.0) -
                (f1140 + f1104) * sqrt(5.0 / 36.0));
    f10b0 = R5[3][6] * R1[0][1];
    f1158 = R5[7][6] * R1[2][1];
    R6[7][7] = (f10f4 * R1[2][1] + R5[6][6] * R1[1][1]) -
                (f1158 + f10b0) * sqrt(1.0 / 7.0);
    f1080 = R5[3][7] * R1[0][1];
    f10f4 = R5[7][7] * R1[2][1];
    R6[7][8] = (R5[6][7] * R1[1][1]) * sqrt(35.0 / 32.0) +
                (f1110 * R1[2][1] -
                (f10f4 + f1080) * sqrt(5.0 / 32.0));
    f1110 = (R5[3][8] * R1[0][1]);
    f1170 = R5[7][8] * R1[2][1];
    R6[7][9] = R1[2][1] * dd30 +
                ((R5[6][8] * R1[1][1]) * sqrt(35.0 / 27.0) -
                (f1170 + f1110) * sqrt(5.0 / 27.0));
    f1188 = (R5[3][9] * R1[0][1]);
    f1180 = R5[7][9] * R1[2][1];
    R6[7][10] = R1[2][1] * dd78 +
                ((R5[6][9] * R1[1][1]) * sqrt(7.0 / 4.0) -
                (f1180 + f1188) * k_16340dc);
    f1154 = R5[3][10] * R1[0][1];
    f1174 = R5[7][10] * R1[2][1];
    R6[7][11] = (R5[6][10] * R1[1][1]) * sqrt(35.0 / 11.0) +
                (R1[2][1] * df28 -
                (f1174 + f1154) * sqrt(5.0 / 11.0));
    f1168 = R5[3][10] * R1[0][2] - R5[3][0] * R1[0][0];
    f116c = R5[7][10] * R1[2][2] - R5[7][0] * R1[2][0];
    R6[7][12] = (R1[2][2] * R5[5][10] - R5[5][0] * R1[2][0]) * sqrt(7.0 / 44.0) +
                ((R5[6][10] * R1[1][2] - R5[6][0] * R1[1][0]) * sqrt(35.0 / 132.0) -
                (f116c + f1168) * sqrt(5.0 / 132.0));
    out[43] = WeightedSum(13, &in[36], R6[7]);
    f1178 = R1[2][2] * R5[8][0] + R5[8][10] * R1[2][0];
    f114c = R1[0][2] * R5[2][0] + R1[0][0] * R5[2][10];
    R6[8][0] = (R1[1][2] * R5[7][0] + R5[7][10] * R1[1][0]) * sqrt(8.0 / 33.0) +
                ((f1058 - f1050) * sqrt(7.0 / 66.0) -
                (f114c + f1178) * sqrt(1.0 / 44.0));
    f1058 = R5[8][0] * R1[2][1];
    f1050 = R5[2][0] * R1[0][1];
    R6[8][1] = (R1[1][1] * R5[7][0]) * sqrt(32.0 / 11.0) +
                ((f1068 - f117c) * sqrt(14.0 / 11.0) -
                (f1050 + f1058) * sqrt(3.0 / 11.0));
    f1068 = R5[8][1] * R1[2][1];
    f117c = R5[2][1] * R1[0][1];
    R6[8][2] = (R5[7][1] * k_16341ec) * R1[1][1] +
                ((f1060 - f1078) * sqrt(7.0 / 10.0) -
                (f117c + f1068) * sqrt(3.0 / 20.0));
    f1060 = R5[8][2] * R1[2][1];
    f1078 = R5[2][2] * R1[0][1];
    R6[8][4] = ((f1128 - f111c) * k_16341dc -
                (R5[2][3] * R1[0][1] + R5[8][3] * R1[2][1]) * k_1634074) +
                R5[7][3] * R1[1][1];
    R6[8][3] = (R5[7][2] * R1[1][1]) * sqrt(32.0 / 27.0) +
                ((f1138 - f1124) * sqrt(14.0 / 27.0) -
                (f1078 + f1060) * sqrt(1.0 / 9.0));
    f1128 = R5[8][4] * R1[2][1];
    f111c = R5[2][4] * R1[0][1];
    R6[8][5] = (R5[7][4] * R1[1][1]) * sqrt(32.0 / 35.0) +
                ((f1120 - f1150) * sqrt(2.0 / 5.0) -
                (f111c + f1128) * sqrt(3.0 / 35.0));
    f1120 = R5[8][5] * R1[2][1];
    f1150 = R5[2][5] * R1[0][1];
    R6[8][6] = (R5[7][5] * k_16341e0) * R1[1][1] +
                ((f1160 - f1130) * sqrt(7.0 / 18.0) -
                (f1150 + f1120) * k_163407c);
    f1160 = (R5[8][6] * R1[2][1]);
    f1130 = R5[2][6] * R1[0][1];
    R6[8][8] = ((f1184 - f115c) * k_16341dc -
                (R5[2][7] * R1[0][1] + R5[8][7] * R1[2][1]) * k_1634074) +
                R5[7][7] * R1[1][1];
    R6[8][7] = (R5[7][6] * R1[1][1]) * sqrt(32.0 / 35.0) +
                ((f1134 - f113c) * sqrt(2.0 / 5.0) -
                (f1130 + f1160) * sqrt(3.0 / 35.0));
    f1184 = (R5[8][8] * R1[2][1]);
    f115c = R5[2][8] * R1[0][1];
    R6[8][9] = (R5[7][8] * R1[1][1]) * sqrt(32.0 / 27.0) +
                ((f1164 - f10f0) * sqrt(14.0 / 27.0) -
                (f115c + f1184) * sqrt(1.0 / 9.0));
    f1164 = R5[8][9] * R1[2][1];
    f10f0 = R5[2][9] * R1[0][1];
    R6[8][10] = (R5[7][9] * k_16341ec) * R1[1][1] +
                ((f10e0 - f10a8) * sqrt(7.0 / 10.0) -
                (f10f0 + f1164) * sqrt(3.0 / 20.0));
    f10e0 = R5[8][10] * R1[2][1];
    f10a8 = R5[2][10] * R1[0][1];
    R6[8][11] = (R5[7][10] * R1[1][1]) * sqrt(32.0 / 11.0) +
                ((f10a0 - f10c8) * sqrt(14.0 / 11.0) -
                (f10a8 + f10e0) * sqrt(3.0 / 11.0));
    f10a0 = R5[8][10] * R1[2][2] - R5[8][0] * R1[2][0];
    f10c8 = R5[2][10] * R1[0][2] - R5[2][0] * R1[0][0];
    R6[8][12] = (R5[7][10] * R1[1][2] - R5[7][0] * R1[1][0]) * sqrt(8.0 / 33.0) +
                ((f1100 - f10d8) * sqrt(7.0 / 66.0) -
                (f10c8 + f10a0) * sqrt(1.0 / 44.0));
    f113c = R5[2][7] * R1[0][1];
    f1138 = (R5[8][3] * R1[2][1]);
    f1134 = R5[8][7] * R1[2][1];
    f1124 = R5[2][3] * R1[0][1];
    out[44] = WeightedSum(13, &in[36], R6[8]);
    f1100 = (R1[2][2] * R5[9][0] + R1[2][0] * R5[9][10]);
    fVar8 = f112c - f10e8;
    f10d8 = R5[1][10] * R1[0][0] + R1[0][2] * R5[1][0];
    R6[9][0] = (R1[1][2] * R5[8][0] + R5[8][10] * R1[1][0]) * sqrt(9.0 / 44.0) +
                ((f1090 - f1088) * sqrt(3.0 / 22.0) -
                (f10d8 + f1100) * sqrt(1.0 / 88.0));
    f1088 = R5[1][0] * R1[0][1];
    f1090 = R5[9][0] * R1[2][1];
    R6[9][1] = (R1[1][1] * R5[8][0]) * sqrt(27.0 / 11.0) +
                ((f1148 - f10b8) * sqrt(18.0 / 11.0) -
                (f1090 + f1088) * sqrt(3.0 / 22.0));
    f1148 = R5[1][1] * R1[0][1];
    f10b8 = R5[9][1] * R1[2][1];
    R6[9][2] = (R5[8][1] * R1[1][1]) * sqrt(27.0 / 20.0) +
                ((f1144 - f1098) * sqrt(9.0 / 10.0) -
                (f10b8 + f1148) * sqrt(3.0 / 40.0));
    f112c = R5[1][3] * R1[0][1];
    f10e8 = (R5[9][3] * R1[2][1]);
    R6[9][3] = (fVar8 * k_1634150 -
                (R5[9][2] * R1[2][1] + R5[1][2] * R1[0][1]) * k_16341b0) +
                R5[8][2] * R1[1][1];
    R6[9][4] = (R5[8][3] * R1[1][1]) * sqrt(27.0 / 32.0) +
                ((f10d0 - f10c0) * sqrt(9.0 / 16.0) -
                (f10e8 + f112c) * sqrt(3.0 / 64.0));
    f10c0 = R5[1][4] * R1[0][1];
    f10d0 = R5[9][4] * R1[2][1];
    R6[9][5] = (R5[8][4] * R1[1][1]) * sqrt(27.0 / 35.0) +
                ((f1114 - f10f8) * sqrt(18.0 / 35.0) -
                (f10d0 + f10c0) * sqrt(3.0 / 70.0));
    f1114 = R5[1][5] * R1[0][1];
    f10f8 = R5[9][5] * R1[2][1];
    R6[9][6] = (R5[8][5] * k_1634104) * R1[1][1] +
                ((f1140 - f1104) * sqrt(1.0 / 2.0) -
                (f10f8 + f1114) * sqrt(1.0 / 24.0));
    f1104 = (R5[9][6] * R1[2][1]);
    f1140 = R5[1][6] * R1[0][1];
    R6[9][7] = (R5[8][6] * R1[1][1]) * sqrt(27.0 / 35.0) +
                ((f1158 - f10b0) * sqrt(18.0 / 35.0) -
                (f1140 + f1104) * sqrt(3.0 / 70.0));
    f10b0 = R5[9][7] * R1[2][1];
    f106c = R5[1][7] * R1[0][1];
    R6[9][9] = ((f1170 - f1110) * k_1634150 -
                (R5[1][8] * R1[0][1] + R5[9][8] * R1[2][1]) * k_16341b0) +
                R5[8][8] * R1[1][1];
    R6[9][8] = (R5[8][7] * R1[1][1]) * sqrt(27.0 / 32.0) +
                ((f10f4 - f1080) * sqrt(9.0 / 16.0) -
                (f106c + f10b0) * sqrt(3.0 / 64.0));
    f1110 = (R5[9][9] * R1[2][1]);
    R6[9][10] = (R5[8][9] * R1[1][1]) * sqrt(27.0 / 20.0) +
                ((f1180 - f1188) * sqrt(9.0 / 10.0) -
                (R5[1][9] * R1[0][1] + f1110) * sqrt(3.0 / 40.0));
    f1188 = (R5[9][10] * R1[2][1]);
    R6[9][11] = (R5[8][10] * R1[1][1]) * sqrt(27.0 / 11.0) +
                ((f1174 - f1154) * sqrt(18.0 / 11.0) -
                (R5[1][10] * R1[0][1] + f1188) * sqrt(3.0 / 22.0));
    f1154 = R5[1][10] * R1[0][2] - R5[1][0] * R1[0][0];
    f1174 = R5[9][10] * R1[2][2] - R5[9][0] * R1[2][0];
    R6[9][12] = (R5[8][10] * R1[1][2] - R5[8][0] * R1[1][0]) * sqrt(9.0 / 44.0) +
                ((f116c - f1168) * sqrt(3.0 / 22.0) -
                (f1174 + f1154) * sqrt(1.0 / 88.0));
    f1144 = R5[1][2] * R1[0][1];
    f10f4 = R5[9][8] * R1[2][1];
    f1048 = (R5[1][10] * R1[0][1]);
    f1010 = R5[1][9] * R1[0][1];
    f1098 = R5[9][2] * R1[2][1];
    f1080 = R5[1][8] * R1[0][1];
    out[45] = WeightedSum(13, &in[36], R6[9]);
    f116c = R1[2][2] * R5[10][0] + R5[10][10] * R1[2][0];
    f1168 = R1[0][2] * R5[0][0] + R5[0][10] * R1[0][0];
    R6[10][0] = (R1[1][2] * R5[9][0] + R5[9][10] * R1[1][0]) * sqrt(5.0 / 33.0) +
                ((f1178 - f114c) * sqrt(15.0 / 88.0) -
                (f1168 + f116c) * sqrt(1.0 / 264.0));
    f114c = R5[0][0] * R1[0][1];
    f1178 = R5[10][0] * R1[2][1];
    R6[10][1] = (R1[1][1] * R5[9][0]) * sqrt(20.0 / 11.0) +
                ((f1058 - f1050) * sqrt(45.0 / 22.0) -
                (f1178 + f114c) * sqrt(1.0 / 22.0));
    f1058 = R5[0][1] * R1[0][1];
    f1180 = R5[10][1] * R1[2][1];
    R6[10][2] = (R5[9][1] * R1[1][1] + (f1068 - f117c) * k_1634094) -
                (f1180 + f1058) * sqrt(1.0 / 40.0);
    f1068 = R5[0][2] * R1[0][1];
    f1050 = R5[10][2] * R1[2][1];
    R6[10][3] = (R5[9][2] * R1[1][1]) * sqrt(20.0 / 27.0) +
                ((f1060 - f1078) * k_1634078 -
                (f1050 + f1068) * sqrt(1.0 / 54.0));
    f1078 = R5[0][3] * R1[0][1];
    f1060 = R5[10][3] * R1[2][1];
    R6[10][4] = (R5[9][3] * k_16340ec) * R1[1][1] +
                ((f1138 - f1124) * sqrt(45.0 / 64.0) -
                (f1060 + f1078) * sqrt(1.0 / 64.0));
    f1124 = R5[0][4] * R1[0][1];
    f1138 = (R5[10][4] * R1[2][1]);
    R6[10][5] = (R5[9][4] * R1[1][1]) * sqrt(4.0 / 7.0) +
                ((f1128 - f111c) * sqrt(9.0 / 14.0) -
                (f1138 + f1124) * sqrt(1.0 / 70.0));
    f1128 = R5[0][5] * R1[0][1];
    f1170 = R5[10][5] * R1[2][1];
    R6[10][6] = ((R5[9][5] * k_16340cc) * R1[1][1] +
                (f1120 - f1150) * k_16340ec) -
                (f1170 + f1128) * sqrt(1.0 / 72.0);
    f1120 = R5[0][6] * R1[0][1];
    f111c = R5[10][6] * R1[2][1];
    R6[10][7] = (R5[9][6] * R1[1][1]) * sqrt(4.0 / 7.0) +
                ((f1160 - f1130) * sqrt(9.0 / 14.0) -
                (f111c + f1120) * sqrt(1.0 / 70.0));
    f1130 = R5[0][7] * R1[0][1];
    f1160 = (R5[10][7] * R1[2][1]);
    R6[10][8] = (R5[9][7] * k_16340ec) * R1[1][1] +
                ((f1134 - f113c) * sqrt(45.0 / 64.0) -
                (f1160 + f1130) * sqrt(1.0 / 64.0));
    f117c = R5[0][8] * R1[0][1];
    f1134 = R5[10][8] * R1[2][1];
    R6[10][9] = (R5[9][8] * R1[1][1]) * sqrt(20.0 / 27.0) +
                ((f1184 - f115c) * k_1634078 -
                (f1134 + f117c) * sqrt(1.0 / 54.0));
    f1184 = (R5[0][9] * R1[0][1]);
    f1158 = R5[10][9] * R1[2][1];
    R6[10][10] = (R5[9][9] * R1[1][1] + (f1164 - f10f0) * k_1634094)
                - (f1158 + f1184) * sqrt(1.0 / 40.0);
    f1164 = R5[0][10] * R1[0][1];
    f115c = R5[10][10] * R1[2][1];
    R6[10][11] = (R5[9][10] * R1[1][1]) * sqrt(20.0 / 11.0) +
                ((f10e0 - f10a8) * sqrt(45.0 / 22.0) -
                (f115c + f1164) * sqrt(1.0 / 22.0));
    f10f0 = R5[10][10] * R1[2][2] - R5[10][0] * R1[2][0];
    f10e0 = R5[0][10] * R1[0][2] - R5[0][0] * R1[0][0];
    R6[10][12] = (R5[9][10] * R1[1][2] - R5[9][0] * R1[1][0]) * sqrt(5.0 / 33.0) +
                ((f10a0 - f10c8) * sqrt(15.0 / 88.0) -
                (f10e0 + f10f0) * sqrt(1.0 / 264.0));
    out[46] = WeightedSum(13, &in[36], R6[10]);
    R6[11][0] = (R1[1][2] * R5[10][0] + R1[1][0] * R5[10][10]) * k_163407c +
                (f1100 - f10d8) * sqrt(5.0 / 24.0);
    R6[11][1] = (f1090 - f1088) * sqrt(5.0 / 2.0) +
                R5[10][0] * R1[1][1];
    R6[11][2] = (R5[10][1] * R1[1][1]) * sqrt(11.0 / 20.0) +
                (f10b8 - f1148) * sqrt(11.0 / 8.0);
    R6[11][3] = (R5[10][2] * R1[1][1]) * sqrt(11.0 / 27.0) +
                (f1098 - f1144) * sqrt(55.0 / 54.0);
    R6[11][4] = (R5[10][3] * R1[1][1]) * sqrt(11.0 / 32.0) +
                (f10e8 - f112c) * sqrt(55.0 / 64.0);
    R6[11][5] = (R5[10][4] * R1[1][1]) * sqrt(11.0 / 35.0) +
                (f10d0 - f10c0) * sqrt(11.0 / 14.0);
    R6[11][6] = (R5[10][5] * R1[1][1]) * sqrt(11.0 / 36.0) +
                (f10f8 - f1114) * sqrt(55.0 / 72.0);
    R6[11][7] = (R5[10][6] * R1[1][1]) * sqrt(11.0 / 35.0) +
                (f1104 - f1140) * sqrt(11.0 / 14.0);
    R6[11][8] = (R5[10][7] * R1[1][1]) * sqrt(11.0 / 32.0) +
                (f10b0 - f106c) * sqrt(55.0 / 64.0);
    R6[11][9] = (R5[10][8] * R1[1][1]) * sqrt(11.0 / 27.0) +
                (f10f4 - f1080) * sqrt(55.0 / 54.0);
    R6[11][10] = (R5[10][9] * R1[1][1]) * sqrt(11.0 / 20.0) +
                (f1110 - f1010) * sqrt(11.0 / 8.0);
    R6[11][11] = (f1188 - f1048) * sqrt(5.0 / 2.0) +
                R5[10][10] * R1[1][1];
    R6[11][12] = (f1174 - f1154) * sqrt(5.0 / 24.0) +
                (R5[10][10] * R1[1][2] - R5[10][0] * R1[1][0]) * k_163407c;
    out[47] = WeightedSum(13, &in[36], R6[11]);
    R6[12][12] = k_16340dc;
    R6[12][1] = (f1178 - f114c) * sqrt(3.0);
    R6[12][0] = (f116c - f1168) * R6[12][12];
    R6[12][2] = (f1180 - f1058) * sqrt(33.0 / 20.0);
    R6[12][3] = (f1050 - f1068) * sqrt(11.0 / 9.0);
    R6[12][4] = (f1060 - f1078) * sqrt(33.0 / 32.0);
    R6[12][12] = (f10f0 - f10e0) * R6[12][12];
    R6[12][5] = (f1138 - f1124) * sqrt(33.0 / 35.0);
    R6[12][6] = (f1170 - f1128) * sqrt(11.0 / 12.0);
    R6[12][7] = (f111c - f1120) * sqrt(33.0 / 35.0);
    R6[12][8] = (f1160 - f1130) * sqrt(33.0 / 32.0);
    R6[12][9] = (f1134 - f117c) * sqrt(11.0 / 9.0);
    R6[12][10] = (f1158 - f1184) * sqrt(33.0 / 20.0);
    R6[12][11] = (f115c - f1164) * sqrt(3.0);
    out[48] = WeightedSum(13, &in[36], R6[12]);

    // ---- band 7: R7 from R1 x R6 ----
    if (order <= 7)
        return;
    f1048 = (R6[0][12] * R1[2][0] + R6[0][0] * R1[2][2]);
    f1010 = R6[12][0] * R1[0][2] + R6[12][12] * R1[0][0];
    R7[0][0] = (f1010 + f1048) * k_16340dc;
    f1118 = (R6[12][0] * R1[0][1]);
    f106c = R6[0][0] * R1[2][1];
    R7[0][1] = (f106c + f1118) * sqrt(7.0 / 2.0);
    f1104 = (R6[12][1] * R1[0][1]);
    f10f8 = R6[0][1] * R1[2][1];
    R7[0][2] = (f10f8 + f1104) * sqrt(91.0 / 48.0);
    f1058 = R6[12][2] * R1[0][1];
    f10f4 = R6[0][2] * R1[2][1];
    R7[0][3] = (f10f4 + f1058) * sqrt(91.0 / 66.0);
    f1068 = R6[12][3] * R1[0][1];
    f1050 = R6[0][3] * R1[2][1];
    R7[0][4] = (f1050 + f1068) * sqrt(91.0 / 80.0);
    f1110 = (R6[12][4] * R1[0][1]);
    f1060 = R6[0][4] * R1[2][1];
    R7[0][5] = (f1060 + f1110) * sqrt(91.0 / 90.0);
    f1078 = R6[0][5] * R1[2][1];
    f1138 = (R6[12][5] * R1[0][1]);
    R7[0][6] = (f1138 + f1078) * sqrt(91.0 / 96.0);
    f1124 = R6[0][6] * R1[2][1];
    f1128 = R6[12][6] * R1[0][1];
    R7[0][7] = (f1128 + f1124) * sqrt(13.0 / 14.0);
    f111c = R6[0][7] * R1[2][1];
    f1120 = R6[12][7] * R1[0][1];
    R7[0][8] = (f1120 + f111c) * sqrt(91.0 / 96.0);
    f1160 = (R6[0][8] * R1[2][1]);
    f1130 = R6[12][8] * R1[0][1];
    R7[0][9] = (f1130 + f1160) * sqrt(91.0 / 90.0);
    f1134 = R6[0][9] * R1[2][1];
    f1184 = (R6[12][9] * R1[0][1]);
    R7[0][10] = (f1184 + f1134) * sqrt(91.0 / 80.0);
    f115c = R6[0][10] * R1[2][1];
    f1164 = R6[12][10] * R1[0][1];
    R7[0][11] = (f1164 + f115c) * sqrt(91.0 / 66.0);
    f10f0 = R6[0][11] * R1[2][1];
    f10e0 = R6[12][11] * R1[0][1];
    R7[0][12] = (f10e0 + f10f0) * sqrt(91.0 / 48.0);
    f10a8 = R1[2][1] * R6[0][12];
    f10a0 = R6[12][12] * R1[0][1];
    R7[0][13] = (f10a0 + f10a8) * sqrt(7.0 / 2.0);
    f1100 = (R6[12][12] * R1[0][2] - R6[12][0] * R1[0][0]);
    f10c8 = R6[0][12] * R1[2][2] - R6[0][0] * R1[2][0];
    R7[0][14] = (f1100 + f10c8) * k_16340dc;
    out[49] = WeightedSum(15, &in[49], R7[0]);
    f1090 = R1[0][2] * R6[11][0] + R6[11][12] * R1[0][0];
    f10d8 = R1[2][2] * R6[1][0] + R6[1][12] * R1[2][0];
    R7[1][0] = (f10d8 + f1090) * sqrt(3.0 / 14.0) +
                (R1[1][2] * R6[0][0] + R1[1][0] * R6[0][12]) * sqrt(1.0 / 14.0);
    f10b8 = R6[11][0] * R1[0][1];
    f1088 = R6[1][0] * R1[2][1];
    R7[1][1] = (f1088 + f10b8) * sqrt(3.0) +
                R6[0][0] * R1[1][1];
    f10e8 = (R6[11][1] * R1[0][1]);
    f1098 = R6[1][1] * R1[2][1];
    R7[1][2] = (R6[0][1] * R1[1][1]) * sqrt(13.0 / 24.0) +
                (f1098 + f10e8) * sqrt(13.0 / 8.0);
    f10c0 = R6[11][2] * R1[0][1];
    f10d0 = R6[1][2] * R1[2][1];
    R7[1][3] = (R6[0][2] * R1[1][1]) * sqrt(13.0 / 33.0) +
                (f10d0 + f10c0) * sqrt(13.0 / 11.0);
    f1080 = R6[11][3] * R1[0][1];
    f10b0 = R6[1][3] * R1[2][1];
    R7[1][4] = (R6[0][3] * R1[1][1]) * sqrt(13.0 / 40.0) +
                (f10b0 + f1080) * sqrt(39.0 / 40.0);
    f1174 = R6[11][4] * R1[0][1];
    f1188 = (R6[1][4] * R1[2][1]);
    R7[1][5] = (R6[0][4] * R1[1][1]) * sqrt(13.0 / 45.0) +
                (f1188 + f1174) * sqrt(13.0 / 15.0);
    f116c = R6[11][5] * R1[0][1];
    f1154 = R6[1][5] * R1[2][1];
    R7[1][6] = (R6[0][5] * R1[1][1]) * sqrt(13.0 / 48.0) +
                (f1154 + f116c) * sqrt(13.0 / 16.0);
    f1168 = R6[11][6] * R1[0][1];
    f1180 = R6[1][6] * R1[2][1];
    R7[1][7] = (R6[0][6] * R1[1][1]) * sqrt(13.0 / 49.0) +
                (f1168 + f1180) * sqrt(39.0 / 49.0);
    f114c = R6[11][7] * R1[0][1];
    f1178 = R6[1][7] * R1[2][1];
    R7[1][8] = (R6[0][7] * R1[1][1]) * sqrt(13.0 / 48.0) +
                (f1178 + f114c) * sqrt(13.0 / 16.0);
    f1150 = R6[11][8] * R1[0][1];
    f117c = R6[1][8] * R1[2][1];
    R7[1][9] = (R6[0][8] * R1[1][1]) * sqrt(13.0 / 45.0) +
                (f117c + f1150) * sqrt(13.0 / 15.0);
    f1148 = R6[11][9] * R1[0][1];
    f113c = R6[1][9] * R1[2][1];
    R7[1][10] = (R6[0][9] * R1[1][1]) * sqrt(13.0 / 40.0) +
                (f113c + f1148) * sqrt(39.0 / 40.0);
    f112c = R6[11][10] * R1[0][1];
    f1144 = R6[1][10] * R1[2][1];
    R7[1][11] = (R6[0][10] * R1[1][1]) * sqrt(13.0 / 33.0) +
                (f1144 + f112c) * sqrt(13.0 / 11.0);
    f1114 = R6[1][11] * R1[2][1];
    R7[1][12] = (R6[0][11] * R1[1][1]) * sqrt(13.0 / 24.0) +
                (f1114 + R6[11][11] * R1[0][1]) * sqrt(13.0 / 8.0);
    R7[1][13] = (R6[1][12] * R1[2][1] + R6[11][12] * R1[0][1]) * sqrt(3.0) +
                R6[0][12] * R1[1][1];
    fVar9 = R6[11][12] * R1[0][2] - R6[11][0] * R1[0][0];
    fVar8 = R6[1][12] * R1[2][2] - R6[1][0] * R1[2][0];
    R7[1][14] = (fVar8 + fVar9) * sqrt(3.0 / 14.0) +
                (R6[0][12] * R1[1][2] - R6[0][0] * R1[1][0]) * sqrt(1.0 / 14.0);
    ffb0 = R6[11][11] * R1[0][1];
    ffa0 = R6[11][12] * R1[0][1];
    ff98 = R6[1][12] * R1[2][1];
    ffe0 = fVar9;
    ffb8 = fVar8;
    out[50] = WeightedSum(15, &in[49], R7[1]);
    fVar9 = R1[0][2] * R6[10][0] + R6[10][12] * R1[0][0];
    fVar4 = R1[2][2] * R6[2][0] + R6[2][12] * R1[2][0];
    R7[2][0] = ((fVar4 + fVar9) * sqrt(33.0 / 182.0) -
                (f1048 - f1010) * sqrt(1.0 / 364.0)) +
                (R6[1][0] * R1[1][2] + R6[1][12] * R1[1][0]) * sqrt(12.0 / 91.0);
    f1048 = (R6[2][0] * R1[2][1]);
    f1010 = R6[10][0] * R1[0][1];
    R7[2][1] = (R1[1][1] * R6[1][0]) * sqrt(24.0 / 13.0) +
                ((f1010 + f1048) * sqrt(33.0 / 13.0) -
                (f106c - f1118) * sqrt(1.0 / 26.0));
    f1118 = (R6[10][1] * R1[0][1]);
    f106c = R6[2][1] * R1[2][1];
    R7[2][2] = R6[1][1] * R1[1][1] +
                ((f106c + f1118) * sqrt(11.0 / 8.0) -
                (f10f8 - f1104) * sqrt(1.0 / 48.0));
    f1104 = (R6[10][2] * R1[0][1]);
    f10f8 = R6[2][2] * R1[2][1];
    R7[2][3] = (R6[1][2] * R1[1][1]) * sqrt(8.0 / 11.0) +
                ((f10f8 + f1104) -
                (f10f4 - f1058) * sqrt(1.0 / 66.0));
    f1058 = R6[10][3] * R1[0][1];
    f10f4 = R6[2][3] * R1[2][1];
    R7[2][4] = (R6[1][3] * k_1634064) * R1[1][1] +
                ((f10f4 + f1058) * sqrt(33.0 / 40.0) -
                (f1050 - f1068) * sqrt(1.0 / 80.0));
    f1068 = R6[10][4] * R1[0][1];
    f1050 = R6[2][4] * R1[2][1];
    R7[2][5] = (R6[1][4] * R1[1][1]) * sqrt(8.0 / 15.0) +
                ((f1050 + f1068) * sqrt(11.0 / 15.0) -
                (f1060 - f1110) * sqrt(1.0 / 90.0));
    f1060 = R6[10][5] * R1[0][1];
    f1170 = R6[2][5] * R1[2][1];
    R7[2][6] = (R6[1][5] * R1[1][1]) * sqrt(1.0 / 2.0) +
                ((f1060 + f1170) * sqrt(11.0 / 16.0) -
                (f1078 - f1138) * sqrt(1.0 / 96.0));
    f1110 = (R6[10][6] * R1[0][1]);
    f1158 = R6[2][6] * R1[2][1];
    R7[2][7] = (R6[1][6] * R1[1][1]) * sqrt(24.0 / 49.0) +
                ((f1110 + f1158) * sqrt(33.0 / 49.0) -
                (f1124 - f1128) * sqrt(1.0 / 98.0));
    f1138 = (R6[10][7] * R1[0][1]);
    f1078 = R6[2][7] * R1[2][1];
    R7[2][8] = (R6[1][7] * R1[1][1]) * sqrt(1.0 / 2.0) +
                ((f1078 + f1138) * sqrt(11.0 / 16.0) -
                (f111c - f1120) * sqrt(1.0 / 96.0));
    f1128 = R6[10][8] * R1[0][1];
    f1124 = R6[2][8] * R1[2][1];
    R7[2][9] = (R6[1][8] * R1[1][1]) * sqrt(8.0 / 15.0) +
                ((f1124 + f1128) * sqrt(11.0 / 15.0) -
                (f1160 - f1130) * sqrt(1.0 / 90.0));
    f1120 = R6[10][9] * R1[0][1];
    f111c = R6[2][9] * R1[2][1];
    R7[2][10] = (R6[1][9] * k_1634064) * R1[1][1] +
                ((f111c + f1120) * sqrt(33.0 / 40.0) -
                (f1134 - f1184) * sqrt(1.0 / 80.0));
    f1130 = R6[10][10] * R1[0][1];
    f1160 = (R6[2][10] * R1[2][1]);
    R7[2][11] = (R6[1][10] * R1[1][1]) * sqrt(8.0 / 11.0) +
                ((f1160 + f1130) -
                (f115c - f1164) * sqrt(1.0 / 66.0));
    f1184 = (R6[10][11] * R1[0][1]);
    f1134 = R6[2][11] * R1[2][1];
    R7[2][12] = R6[1][11] * R1[1][1] +
                ((f1134 + f1184) * sqrt(11.0 / 8.0) -
                (f10f0 - f10e0) * sqrt(1.0 / 48.0));
    f1164 = R6[10][12] * R1[0][1];
    f115c = R6[2][12] * R1[2][1];
    R7[2][13] = (R6[1][12] * R1[1][1]) * sqrt(24.0 / 13.0) +
                ((f115c + f1164) * sqrt(33.0 / 13.0) -
                (f10a8 - f10a0) * sqrt(1.0 / 26.0));
    fVar8 = R6[10][12] * R1[0][2] - R6[10][0] * R1[0][0];
    f10e0 = fVar8;
    fVar7 = R6[2][12] * R1[2][2] - R6[2][0] * R1[2][0];
    f10f0 = fVar7;
    R7[2][14] = (R6[1][12] * R1[1][2] - R6[1][0] * R1[1][0]) * sqrt(12.0 / 91.0) +
                ((fVar7 + fVar8) * sqrt(33.0 / 182.0) -
                (f10c8 - f1100) * sqrt(1.0 / 364.0));
    f1040 = fVar9;
    f1000 = fVar4;
    out[51] = WeightedSum(15, &in[49], R7[2]);
    fVar9 = R6[3][12] * R1[2][0] + R1[2][2] * R6[3][0];
    f10a8 = fVar9;
    fVar8 = R1[0][2] * R6[9][0] + R6[9][12] * R1[0][0];
    f10a0 = fVar8;
    R7[3][0] = (R1[1][2] * R6[2][0] + R6[2][12] * R1[1][0]) * sqrt(33.0 / 182.0) +
                ((fVar8 + fVar9) * sqrt(55.0 / 364.0) -
                (f10d8 - f1090) * sqrt(3.0 / 364.0));
    f10c8 = R6[3][0] * R1[2][1];
    f1100 = R6[9][0] * R1[0][1];
    R7[3][1] = (R1[1][1] * R6[2][0]) * sqrt(33.0 / 13.0) +
                ((R6[9][0] * R1[0][1] + R6[3][0] * R1[2][1]) * sqrt(55.0 / 26.0) -
                (f1088 - f10b8) * sqrt(3.0 / 26.0));
    f10d8 = R6[3][1] * R1[2][1];
    f1090 = R6[9][1] * R1[0][1];
    R7[3][2] = (R6[2][1] * R1[1][1]) * sqrt(11.0 / 8.0) +
                ((R6[9][1] * R1[0][1] + R6[3][1] * R1[2][1]) * sqrt(55.0 / 48.0) -
                (f1098 - f10e8) * k_16340bc);
    f1088 = R6[3][2] * R1[2][1];
    f10b8 = R6[9][2] * R1[0][1];
    R7[3][3] = (R6[2][2] * R1[1][1] +
                (R6[9][2] * R1[0][1] + R6[3][2] * R1[2][1]) * k_1634078) -
                (f10d0 - f10c0) * sqrt(1.0 / 22.0);
    f1098 = R6[3][3] * R1[2][1];
    f10e8 = R6[9][3] * R1[0][1];
    R7[3][4] = (R6[2][3] * R1[1][1]) * sqrt(33.0 / 40.0) +
                ((R6[9][3] * R1[0][1] + R6[3][3] * R1[2][1]) * sqrt(11.0 / 16.0) -
                (f10b0 - f1080) * sqrt(3.0 / 80.0));
    f10d0 = R6[3][4] * R1[2][1];
    f10c0 = R6[9][4] * R1[0][1];
    R7[3][5] = (R6[2][4] * R1[1][1]) * sqrt(11.0 / 15.0) +
                ((R6[9][4] * R1[0][1] + R6[3][4] * R1[2][1]) * sqrt(11.0 / 18.0) -
                (f1188 - f1174) * sqrt(1.0 / 30.0));
    f10b0 = R6[3][5] * R1[2][1];
    f1080 = R6[9][5] * R1[0][1];
    R7[3][6] = (R6[2][5] * R1[1][1]) * sqrt(11.0 / 16.0) +
                ((R6[9][5] * R1[0][1] + R6[3][5] * R1[2][1]) * sqrt(55.0 / 96.0) -
                (f1154 - f116c) * k_1634130);
    f1188 = (R6[3][6] * R1[2][1]);
    f1140 = R6[9][6] * R1[0][1];
    R7[3][7] = (R6[2][6] * R1[1][1]) * sqrt(33.0 / 49.0) +
                ((f1188 + f1140) * sqrt(55.0 / 98.0) -
                (f1180 - f1168) * sqrt(3.0 / 98.0));
    f1174 = R6[3][7] * R1[2][1];
    f1154 = R6[9][7] * R1[0][1];
    R7[3][8] = (R6[2][7] * R1[1][1]) * sqrt(11.0 / 16.0) +
                ((f1154 + f1174) * sqrt(55.0 / 96.0) -
                (f1178 - f114c) * k_1634130);
    f116c = R6[3][8] * R1[2][1];
    f1168 = R6[9][8] * R1[0][1];
    R7[3][9] = (R6[2][8] * R1[1][1]) * sqrt(11.0 / 15.0) +
                ((f1168 + f116c) * sqrt(11.0 / 18.0) -
                (f117c - f1150) * sqrt(1.0 / 30.0));
    f1178 = R6[3][9] * R1[2][1];
    f114c = R6[9][9] * R1[0][1];
    R7[3][10] = (R6[2][9] * R1[1][1]) * sqrt(33.0 / 40.0) +
                ((f114c + f1178) * sqrt(11.0 / 16.0) -
                (f113c - f1148) * sqrt(3.0 / 80.0));
    f117c = R6[3][10] * R1[2][1];
    f1150 = R6[9][10] * R1[0][1];
    R7[3][11] = (R6[2][10] * R1[1][1] + (f1150 + f117c) * k_1634078) -
                (f1144 - f112c) * sqrt(1.0 / 22.0);
    f113c = R6[3][11] * R1[2][1];
    f1148 = R6[9][11] * R1[0][1];
    R7[3][12] = (R6[2][11] * R1[1][1]) * sqrt(11.0 / 8.0) +
                ((f1148 + f113c) * sqrt(55.0 / 48.0) -
                (f1114 - ffb0) * k_16340bc);
    ffb0 = R6[3][12] * R1[2][1];
    f1144 = R6[9][12] * R1[0][1];
    R7[3][13] = (R6[2][12] * R1[1][1]) * sqrt(33.0 / 13.0) +
                ((f1144 + ffb0) * sqrt(55.0 / 26.0) -
                (ff98 - ffa0) * sqrt(3.0 / 26.0));
    ffa0 = R6[3][12] * R1[2][2] - R6[3][0] * R1[2][0];
    ff98 = R6[9][12] * R1[0][2] - R6[9][0] * R1[0][0];
    R7[3][14] = (R6[2][12] * R1[1][2] - R6[2][0] * R1[1][0]) * sqrt(33.0 / 182.0) +
                ((ff98 + ffa0) * sqrt(55.0 / 364.0) -
                (ffb8 - ffe0) * sqrt(3.0 / 364.0));
    out[52] = WeightedSum(15, &in[49], R7[3]);
    fVar9 = R1[2][2] * R6[4][0] + R6[4][12] * R1[2][0];
    ffe0 = fVar9;
    ffb8 = R1[0][2] * R6[8][0] + R6[8][12] * R1[0][0];
    R7[4][0] = ((ffb8 + fVar9) * sqrt(45.0 / 364.0) -
                (f1000 - f1040) * sqrt(3.0 / 182.0)) +
                (R6[3][12] * R1[1][0] + R6[3][0] * R1[1][2]) * sqrt(20.0 / 91.0);
    f1040 = R6[4][0] * R1[2][1];
    f1000 = R6[8][0] * R1[0][1];
    R7[4][1] = (R1[1][1] * R6[3][0]) * sqrt(40.0 / 13.0) +
                ((R6[8][0] * R1[0][1] + R6[4][0] * R1[2][1]) * sqrt(45.0 / 26.0) -
                (f1048 - f1010) * sqrt(3.0 / 13.0));
    f1048 = (R6[4][1] * R1[2][1]);
    f1010 = R6[8][1] * R1[0][1];
    R7[4][2] = (R6[3][1] * R1[1][1]) * sqrt(5.0 / 3.0) +
                ((f1010 + f1048) * k_16340e8 -
                (f106c - f1118) * sqrt(1.0 / 8.0));
    f106c = R6[4][2] * R1[2][1];
    f1118 = (R6[8][2] * R1[0][1]);
    R7[4][3] = (R6[3][2] * R1[1][1]) * sqrt(40.0 / 33.0) +
                ((f1118 + f106c) * sqrt(15.0 / 22.0) -
                (f10f8 - f1104) * sqrt(1.0 / 11.0));
    f10f8 = R6[4][3] * R1[2][1];
    f1104 = (R6[8][3] * R1[0][1]);
    R7[4][4] = R6[3][3] * R1[1][1] +
                ((f1104 + f10f8) * sqrt(9.0 / 16.0) -
                (f10f4 - f1058) * sqrt(3.0 / 40.0));
    f10f4 = R6[4][4] * R1[2][1];
    f1058 = R6[8][4] * R1[0][1];
    fVar9 = f1050 - f1068;
    f1050 = R6[4][5] * R1[2][1];
    f1068 = R6[8][5] * R1[0][1];
    R7[4][5] = (R6[3][4] * k_16341e0) * R1[1][1] +
                ((R6[8][4] * R1[0][1] + f10f4) * sqrt(1.0 / 2.0) -
                fVar9 * sqrt(1.0 / 15.0));
    R7[4][6] = ((R6[8][5] * R1[0][1] + R6[4][5] * R1[2][1]) * k_16340d4 -
                (f1170 - f1060) * k_16340bc) +
                (R6[3][5] * k_1634078) * R1[1][1];
    f1170 = R6[8][7] * R1[0][1];
    f1060 = R6[4][6] * R1[2][1];
    f1180 = R6[8][6] * R1[0][1];
    fVar9 = f1158 - f1110;
    f1110 = R6[4][7] * R1[2][1];
    R7[4][8] = ((f1170 + R6[4][7] * R1[2][1]) * k_16340d4 -
                (f1078 - f1138) * k_16340bc) +
                (R6[3][7] * k_1634078) * R1[1][1];
    R7[4][7] = (R6[3][6] * R1[1][1]) * sqrt(40.0 / 49.0) +
                ((R6[4][6] * R1[2][1] + f1180) * sqrt(45.0 / 98.0) - fVar9 * sqrt(3.0 / 49.0))
    ;
    f1078 = R6[4][8] * R1[2][1];
    f1138 = (R6[8][8] * R1[0][1]);
    R7[4][9] = (R6[3][8] * k_16341e0) * R1[1][1] +
                ((f1138 + R6[4][8] * R1[2][1]) * sqrt(1.0 / 2.0) -
                (f1124 - f1128) * sqrt(1.0 / 15.0));
    f1124 = R6[4][9] * R1[2][1];
    f1128 = R6[8][9] * R1[0][1];
    R7[4][10] = R6[3][9] * R1[1][1] +
                ((f1128 + f1124) * sqrt(9.0 / 16.0) -
                (f111c - f1120) * sqrt(3.0 / 40.0));
    f111c = R6[4][10] * R1[2][1];
    f1120 = R6[8][10] * R1[0][1];
    R7[4][11] = (R6[3][10] * R1[1][1]) * sqrt(40.0 / 33.0) +
                ((f1120 + f111c) * sqrt(15.0 / 22.0) -
                (f1160 - f1130) * sqrt(1.0 / 11.0));
    f1160 = (R6[4][11] * R1[2][1]);
    f1130 = R6[8][11] * R1[0][1];
    R7[4][12] = (R6[3][11] * R1[1][1]) * sqrt(5.0 / 3.0) +
                ((f1130 + f1160) * k_16340e8 -
                (f1134 - f1184) * sqrt(1.0 / 8.0));
    f1134 = R6[4][12] * R1[2][1];
    f1184 = (R6[8][12] * R1[0][1]);
    R7[4][13] = (R6[3][12] * R1[1][1]) * sqrt(40.0 / 13.0) +
                ((f1184 + f1134) * sqrt(45.0 / 26.0) -
                (f115c - f1164) * sqrt(3.0 / 13.0));
    f115c = R6[4][12] * R1[2][2] - R6[4][0] * R1[2][0];
    f1164 = R6[8][12] * R1[0][2] - R6[8][0] * R1[0][0];
    R7[4][14] = (R6[3][12] * R1[1][2] - R6[3][0] * R1[1][0]) * sqrt(20.0 / 91.0) +
                ((f1164 + f115c) * sqrt(45.0 / 364.0) -
                (f10f0 - f10e0) * sqrt(3.0 / 182.0));
    out[53] = WeightedSum(15, &in[49], R7[4]);
    R7[5][0] = (((R6[7][12] * R1[0][0] + R1[0][2] * R6[7][0]) +
                 (R1[2][2] * R6[5][0] + R6[5][12] * R1[2][0])) * sqrt(9.0 / 91.0) -
                (f10a8 - f10a0) * sqrt(5.0 / 182.0)) +
                (R6[4][0] * R1[1][2] + R6[4][12] * R1[1][0]) * sqrt(45.0 / 182.0);
    R7[5][1] = (R1[1][1] * R6[4][0]) * sqrt(45.0 / 13.0) +
                ((R6[7][0] * R1[0][1] + R6[5][0] * R1[2][1]) * sqrt(18.0 / 13.0) -
                (f10c8 - f1100) * sqrt(5.0 / 13.0));
    R7[5][2] = (R6[4][1] * R1[1][1]) * sqrt(15.0 / 8.0) +
                ((R6[5][1] * R1[2][1] + R6[7][1] * R1[0][1]) * k_1634104 -
                (f10d8 - f1090) * sqrt(5.0 / 24.0));
    R7[5][3] = (R6[4][2] * R1[1][1]) * sqrt(15.0 / 11.0) +
                ((R6[5][2] * R1[2][1] + R6[7][2] * R1[0][1]) * sqrt(6.0 / 11.0) -
                (f1088 - f10b8) * sqrt(5.0 / 33.0));
    R7[5][4] = (R6[4][3] * k_1634094) * R1[1][1] +
                ((R6[5][3] * R1[2][1] + R6[7][3] * R1[0][1]) * sqrt(9.0 / 20.0) -
                (f1098 - f10e8) * sqrt(1.0 / 8.0));
    R7[5][5] = R6[4][4] * R1[1][1] +
                ((R6[5][4] * R1[2][1] + R6[7][4] * R1[0][1]) * sqrt(2.0 / 5.0) -
                (f10d0 - f10c0) * sqrt(1.0 / 9.0));
    R7[5][6] = ((R6[4][5] * k_16340e8) * R1[1][1] +
                (R6[5][5] * R1[2][1] + R6[7][5] * R1[0][1]) * k_16340f8) -
                (f10b0 - f1080) * sqrt(5.0 / 48.0);
    R7[5][7] = (R6[4][6] * R1[1][1]) * sqrt(45.0 / 49.0) +
                ((R6[5][6] * R1[2][1] + R6[7][6] * R1[0][1]) * sqrt(18.0 / 49.0) -
                (f1188 - f1140) * sqrt(5.0 / 49.0));
    R7[5][8] = ((R6[4][7] * k_16340e8) * R1[1][1] +
                (R6[5][7] * R1[2][1] + R6[7][7] * R1[0][1]) * k_16340f8) -
                (f1174 - f1154) * sqrt(5.0 / 48.0);
    R7[5][9] = R6[4][8] * R1[1][1] +
                ((R6[5][8] * R1[2][1] + R6[7][8] * R1[0][1]) * sqrt(2.0 / 5.0) -
                (f116c - f1168) * sqrt(1.0 / 9.0));
    R7[5][10] = (R6[4][9] * k_1634094) * R1[1][1] +
                ((R6[5][9] * R1[2][1] + R6[7][9] * R1[0][1]) * sqrt(9.0 / 20.0) -
                (f1178 - f114c) * sqrt(1.0 / 8.0));
    R7[5][11] = (R6[4][10] * R1[1][1]) * sqrt(15.0 / 11.0) +
                ((R6[5][10] * R1[2][1] + R6[7][10] * R1[0][1]) * sqrt(6.0 / 11.0) -
                (f117c - f1150) * sqrt(5.0 / 33.0));
    R7[5][12] = (R6[4][11] * R1[1][1]) * sqrt(15.0 / 8.0) +
                ((R6[7][11] * R1[0][1] + R6[5][11] * R1[2][1]) * k_1634104 -
                (f113c - f1148) * sqrt(5.0 / 24.0));
    R7[5][13] = (R6[4][12] * R1[1][1]) * sqrt(45.0 / 13.0) +
                ((R6[5][12] * R1[2][1] + R6[7][12] * R1[0][1]) * sqrt(18.0 / 13.0) -
                (ffb0 - f1144) * sqrt(5.0 / 13.0));
    R7[5][14] = (R6[4][12] * R1[1][2] - R6[4][0] * R1[1][0]) * sqrt(45.0 / 182.0) +
                (((R6[7][12] * R1[0][2] - R6[7][0] * R1[0][0]) +
                 (R6[5][12] * R1[2][2] - R6[5][0] * R1[2][0])) * sqrt(9.0 / 91.0) -
                (ffa0 - ff98) * sqrt(5.0 / 182.0));
    out[54] = WeightedSum(15, &in[49], R7[5]);
    R7[6][0] = (R1[1][2] * R6[5][0] + R6[5][12] * R1[1][0]) * sqrt(24.0 / 91.0) +
                ((R1[0][2] * R6[6][0] + R6[6][12] * R1[0][0]) * sqrt(2.0 / 13.0) -
                (ffe0 - ffb8) * sqrt(15.0 / 364.0));
    d10e0 = (R6[6][0] * sqrt(28.0 / 13.0));
    R7[6][1] = (R1[1][1] * R6[5][0]) * sqrt(48.0 / 13.0) +
                (R1[0][1] * (R6[6][0] * sqrt(28.0 / 13.0)) -
                (f1040 - f1000) * sqrt(15.0 / 26.0));
    d10a8 = (R6[6][1] * sqrt(7.0 / 6.0));
    R7[6][2] = (R6[5][1] * R1[1][1]) * sqrt(2.0) +
                (R1[0][1] * (R6[6][1] * sqrt(7.0 / 6.0)) -
                (f1048 - f1010) * sqrt(5.0 / 16.0));
    d10a0 = (R6[6][2] * sqrt(28.0 / 33.0));
    R7[6][3] = (R6[5][2] * R1[1][1]) * sqrt(16.0 / 11.0) +
                (R1[0][1] * (R6[6][2] * sqrt(28.0 / 33.0)) -
                (f106c - f1118) * sqrt(5.0 / 22.0));
    d1100 = (R6[6][3] * sqrt(7.0 / 10.0));
    R7[6][4] = (R6[5][3] * k_1634120) * R1[1][1] +
                ((R6[6][3] * sqrt(7.0 / 10.0)) * R1[0][1] -
                (f10f8 - f1104) * sqrt(3.0 / 16.0));
    d10d8 = (R6[6][4] * sqrt(28.0 / 45.0));
    R7[6][5] = (R6[5][4] * R1[1][1]) * sqrt(16.0 / 15.0) +
                ((R6[6][4] * sqrt(28.0 / 45.0)) * R1[0][1] -
                (f10f4 - f1058) * k_1634084);
    d1090 = (R6[6][5] * sqrt(7.0 / 12.0));
    R7[6][6] = R6[5][5] * R1[1][1] +
                ((R6[6][5] * sqrt(7.0 / 12.0)) * R1[0][1] -
                (f1050 - f1068) * sqrt(5.0 / 32.0));
    d10b8 = (R6[6][6] * sqrt(4.0 / 7.0));
    R7[6][7] = (R6[5][6] * R1[1][1]) * sqrt(48.0 / 49.0) +
                (R1[0][1] * (R6[6][6] * sqrt(4.0 / 7.0)) -
                (f1060 - f1180) * sqrt(15.0 / 98.0));
    d1098 = (R6[6][7] * sqrt(7.0 / 12.0));
    R7[6][8] = R6[5][7] * R1[1][1] +
                ((R6[6][7] * sqrt(7.0 / 12.0)) * R1[0][1] -
                (f1110 - f1170) * sqrt(5.0 / 32.0));
    d10b0 = (R6[6][8] * sqrt(28.0 / 45.0));
    R7[6][9] = (R6[5][8] * R1[1][1]) * sqrt(16.0 / 15.0) +
                ((R6[6][8] * sqrt(28.0 / 45.0)) * R1[0][1] -
                (f1078 - f1138) * k_1634084);
    d10c8 = (R6[6][9] * sqrt(7.0 / 10.0));
    R7[6][10] = R1[0][1] * (R6[6][9] * sqrt(7.0 / 10.0)) +
                ((R6[5][9] * k_1634120) * R1[1][1] -
                (f1124 - f1128) * sqrt(3.0 / 16.0));
    d1080 = (R6[6][10] * sqrt(28.0 / 33.0));
    R7[6][11] = (R6[5][10] * R1[1][1]) * sqrt(16.0 / 11.0) +
                ((R6[6][10] * sqrt(28.0 / 33.0)) * R1[0][1] -
                (f111c - f1120) * sqrt(5.0 / 22.0));
    d428 = (R6[6][11] * sqrt(7.0 / 6.0));
    R7[6][12] = (R6[5][11] * R1[1][1]) * sqrt(2.0) +
                ((R6[6][11] * sqrt(7.0 / 6.0)) * R1[0][1] -
                (f1160 - f1130) * sqrt(5.0 / 16.0));
    d410 = (R6[6][12] * sqrt(28.0 / 13.0));
    R7[6][13] = (R6[5][12] * R1[1][1]) * sqrt(48.0 / 13.0) +
                ((R6[6][12] * sqrt(28.0 / 13.0)) * R1[0][1] -
                (f1134 - f1184) * sqrt(15.0 / 26.0));
    R7[6][14] = ((R6[6][12] * R1[0][2] - R6[6][0] * R1[0][0]) * sqrt(2.0 / 13.0) -
                (f115c - f1164) * sqrt(15.0 / 364.0)) +
                (R6[5][12] * R1[1][2] - R6[5][0] * R1[1][0]) * sqrt(24.0 / 91.0);
    out[55] = WeightedSum(15, &in[49], R7[6]);
    f1078 = 0x3fe09a9ec0000000;
    fVar9 = R6[7][12] * R1[2][0] + R6[7][0] * R1[2][2];
    fVar8 = R1[0][2] * R6[5][0] + R1[0][0] * R6[5][12];
    R7[7][0] = (R1[1][2] * R6[6][0] + R6[6][12] * R1[1][0]) * sqrt(7.0 / 26.0) -
                (fVar8 + fVar9) * sqrt(3.0 / 26.0);
    f1180 = R6[5][0] * R1[0][1];
    R7[7][1] = (R1[1][1] * R6[6][0]) * sqrt(49.0 / 13.0) -
                (f1180 + R6[7][0] * R1[2][1]) * sqrt(21.0 / 13.0);
    ffb8 = R6[7][1] * R1[2][1];
    f1170 = R6[5][1] * R1[0][1];
    R7[7][2] = (R6[6][1] * R1[1][1]) * sqrt(49.0 / 24.0) -
                (f1170 + ffb8) * k_16340fc;
    ffa0 = R6[7][2] * R1[2][1];
    f1158 = R6[5][2] * R1[0][1];
    R7[7][3] = (R6[6][2] * R1[1][1]) * sqrt(49.0 / 33.0) -
                (f1158 + ffa0) * sqrt(7.0 / 11.0);
    ff98 = R6[7][3] * R1[2][1];
    f1140 = R6[5][3] * R1[0][1];
    R7[7][4] = (R6[6][3] * R1[1][1]) * sqrt(49.0 / 40.0) -
                (f1140 + ff98) * sqrt(21.0 / 40.0);
    ffb0 = R6[7][4] * R1[2][1];
    f117c = R6[5][4] * R1[0][1];
    R7[7][5] = (R6[6][4] * R1[1][1]) * sqrt(49.0 / 45.0) -
                (f117c + ffb0) * sqrt(7.0 / 15.0);
    f1048 = (R6[7][5] * R1[2][1]);
    f1150 = R6[5][5] * R1[0][1];
    R7[7][6] = (R6[6][5] * R1[1][1]) * sqrt(49.0 / 48.0) -
                (f1150 + f1048) * k_16341dc;
    f1010 = R6[7][6] * R1[2][1];
    f106c = R6[5][6] * R1[0][1];
    R7[7][7] = R6[6][6] * R1[1][1] -
                (f106c + f1010) * sqrt(3.0 / 7.0);
    f1118 = (R6[7][7] * R1[2][1]);
    f113c = R6[5][7] * R1[0][1];
    R7[7][8] = (R6[6][7] * R1[1][1]) * sqrt(49.0 / 48.0) -
                (f113c + f1118) * k_16341dc;
    f10f8 = R6[7][8] * R1[2][1];
    f1148 = R6[5][8] * R1[0][1];
    R7[7][9] = (R6[6][8] * R1[1][1]) * sqrt(49.0 / 45.0) -
                (f1148 + f10f8) * sqrt(7.0 / 15.0);
    f1104 = (R6[7][9] * R1[2][1]);
    f1144 = R6[5][9] * R1[0][1];
    R7[7][10] = (R6[6][9] * R1[1][1]) * sqrt(49.0 / 40.0) -
                (f1144 + f1104) * sqrt(21.0 / 40.0);
    f10f4 = R6[7][10] * R1[2][1];
    f112c = R6[5][10] * R1[0][1];
    R7[7][11] = (R6[6][10] * R1[1][1]) * sqrt(49.0 / 33.0) -
                (f112c + f10f4) * sqrt(7.0 / 11.0);
    f1058 = R6[5][11] * R1[0][1];
    f1114 = R6[7][11] * R1[2][1];
    R7[7][12] = (R6[6][11] * R1[1][1]) * sqrt(49.0 / 24.0) -
                (f1114 + f1058) * k_16340fc;
    f1068 = R1[0][1] * R6[5][12];
    f1050 = R6[7][12] * R1[2][1];
    R7[7][13] = (R6[6][12] * R1[1][1]) * sqrt(49.0 / 13.0) -
                (f1050 + f1068) * sqrt(21.0 / 13.0);
    f1110 = (R6[5][12] * R1[0][2] - R6[5][0] * R1[0][0]);
    f1060 = R6[7][12] * R1[2][2] - R6[7][0] * R1[2][0];
    R7[7][14] = (R6[6][12] * R1[1][2] - R6[6][0] * R1[1][0]) * sqrt(7.0 / 26.0) -
                (f1060 + f1110) * sqrt(3.0 / 26.0);
    f1000 = fVar8;
    ffe0 = R6[7][0] * R1[2][1];
    f1040 = fVar9;
    out[56] = WeightedSum(15, &in[49], R7[7]);
    fVar9 = R6[8][12] * R1[2][0] + R6[8][0] * R1[2][2];
    f1138 = (R1[0][2] * R6[4][0] + R6[4][12] * R1[0][0]);
    R7[8][0] = (R6[7][12] * R1[1][0] + R1[1][2] * R6[7][0]) * sqrt(24.0 / 91.0) +
                ((R6[6][0] * R1[2][2] + R6[6][12] * R1[2][0]) * sqrt(2.0 / 13.0) -
                (f1138 + fVar9) * sqrt(15.0 / 364.0));
    f1124 = R6[8][0] * R1[2][1];
    f114c = R6[4][0] * R1[0][1];
    R7[8][1] = R1[2][1] * d10e0 +
                ((R1[1][1] * R6[7][0]) * sqrt(48.0 / 13.0) -
                (f114c + f1124) * sqrt(15.0 / 26.0));
    f1128 = R6[8][1] * R1[2][1];
    f1178 = R6[4][1] * R1[0][1];
    R7[8][2] = R1[2][1] * d10a8 +
                ((R6[7][1] * R1[1][1]) * sqrt(2.0) -
                (f1178 + f1128) * sqrt(5.0 / 16.0));
    f111c = R6[8][2] * R1[2][1];
    f1168 = R6[4][2] * R1[0][1];
    R7[8][3] = R1[2][1] * d10a0 +
                ((R6[7][2] * R1[1][1]) * sqrt(16.0 / 11.0) -
                (f1168 + f111c) * sqrt(5.0 / 22.0));
    f1120 = R6[8][3] * R1[2][1];
    f1160 = (R6[4][3] * R1[0][1]);
    R7[8][4] = (R6[7][3] * k_1634120) * R1[1][1] +
                (R1[2][1] * d1100 -
                (f1160 + f1120) * sqrt(3.0 / 16.0));
    f1130 = R6[8][4] * R1[2][1];
    f116c = R6[4][4] * R1[0][1];
    R7[8][5] = R1[2][1] * d10d8 +
                ((R6[7][4] * R1[1][1]) * sqrt(16.0 / 15.0) -
                (f116c + f1130) * k_1634084);
    f1134 = R6[8][5] * R1[2][1];
    f1184 = (R6[4][5] * R1[0][1]);
    R7[8][6] = R6[7][5] * R1[1][1] +
                (R1[2][1] * d1090 -
                (f1184 + f1134) * sqrt(5.0 / 32.0));
    f115c = R6[8][6] * R1[2][1];
    f1154 = R6[4][6] * R1[0][1];
    R7[8][7] = R1[2][1] * d10b8 +
                ((R6[7][6] * R1[1][1]) * sqrt(48.0 / 49.0) -
                (f1154 + f115c) * sqrt(15.0 / 98.0));
    f1164 = R6[8][7] * R1[2][1];
    R7[8][8] = R6[7][7] * R1[1][1] +
                (R1[2][1] * d1098 -
                (R6[4][7] * R1[0][1] + f1164) * sqrt(5.0 / 32.0));
    f1174 = R6[4][8] * R1[0][1];
    R7[8][9] = R1[2][1] * d10b0 +
                ((R6[7][8] * R1[1][1]) * sqrt(16.0 / 15.0) -
                (f1174 + R6[8][8] * R1[2][1]) * k_1634084);
    R7[8][10] = (R6[7][9] * k_1634120) * R1[1][1] +
                (R1[2][1] * d10c8 -
                (R6[4][9] * R1[0][1] + R6[8][9] * R1[2][1]) * sqrt(3.0 / 16.0));
    f1188 = (R6[4][10] * R1[0][1]);
    R7[8][11] = R1[2][1] * d1080 +
                ((R6[7][10] * R1[1][1]) * sqrt(16.0 / 11.0) -
                (f1188 + R6[8][10] * R1[2][1]) * sqrt(5.0 / 22.0));
    R7[8][12] = (R6[7][11] * R1[1][1]) * sqrt(2.0) +
                (R1[2][1] * d428 -
                (R6[4][11] * R1[0][1] + R6[8][11] * R1[2][1]) * sqrt(5.0 / 16.0));
    R7[8][13] = (R6[7][12] * R1[1][1]) * sqrt(48.0 / 13.0) +
                (R1[2][1] * d410 -
                (R6[4][12] * R1[0][1] + R6[8][12] * R1[2][1]) * sqrt(15.0 / 26.0));
    fVar8 = R6[8][12] * R1[2][2] - R6[8][0] * R1[2][0];
    fVar7 = R6[4][12] * R1[0][2] - R6[4][0] * R1[0][0];
    R7[8][14] = (R6[7][12] * R1[1][2] - R6[7][0] * R1[1][0]) * sqrt(24.0 / 91.0) +
                ((R6[6][12] * R1[2][2] - R6[6][0] * R1[2][0]) * sqrt(2.0 / 13.0) -
                (fVar7 + fVar8) * sqrt(15.0 / 364.0));
    f1078 = fVar9;
    f10f0 = R6[4][7] * R1[0][1];
    f10e0 = R6[8][8] * R1[2][1];
    f10a8 = R6[8][9] * R1[2][1];
    f10a0 = R6[4][9] * R1[0][1];
    f10c8 = R6[8][10] * R1[2][1];
    f1100 = (R6[8][11] * R1[2][1]);
    f10d8 = R6[4][11] * R1[0][1];
    f1090 = R6[8][12] * R1[2][1];
    f1088 = R6[4][12] * R1[0][1];
    f10b8 = fVar8;
    f1098 = fVar7;
    out[57] = WeightedSum(15, &in[49], R7[8]);
    fVar9 = R1[0][0] * R6[3][12] + R1[0][2] * R6[3][0];
    fVar8 = R1[2][2] * R6[9][0] + R6[9][12] * R1[2][0];
    R7[9][0] = (R1[1][2] * R6[8][0] + R6[8][12] * R1[1][0]) * sqrt(45.0 / 182.0) +
                ((f1040 - f1000) * sqrt(9.0 / 91.0) -
                (fVar8 + fVar9) * sqrt(5.0 / 182.0));
    f1000 = R6[9][0] * R1[2][1];
    R7[9][1] = (R1[1][1] * R6[8][0]) * sqrt(45.0 / 13.0) +
                ((ffe0 - f1180) * sqrt(18.0 / 13.0) -
                (f1000 + R6[3][0] * R1[0][1]) * sqrt(5.0 / 13.0));
    ffe0 = R6[9][1] * R1[2][1];
    R7[9][2] = (R6[8][1] * R1[1][1]) * sqrt(15.0 / 8.0) +
                ((ffb8 - f1170) * k_1634104 -
                (ffe0 + R6[3][1] * R1[0][1]) * sqrt(5.0 / 24.0));
    ffb8 = R6[9][2] * R1[2][1];
    R7[9][3] = (R6[8][2] * R1[1][1]) * sqrt(15.0 / 11.0) +
                ((ffa0 - f1158) * sqrt(6.0 / 11.0) -
                (ffb8 + R6[3][2] * R1[0][1]) * sqrt(5.0 / 33.0));
    ffa0 = R6[9][3] * R1[2][1];
    R7[9][4] = (R6[8][3] * k_1634094) * R1[1][1] +
                ((ff98 - f1140) * sqrt(9.0 / 20.0) -
                (R6[3][3] * R1[0][1] + ffa0) * sqrt(1.0 / 8.0));
    ff98 = R6[9][4] * R1[2][1];
    R7[9][5] = R6[8][4] * R1[1][1] +
                ((ffb0 - f117c) * sqrt(2.0 / 5.0) -
                (R6[3][4] * R1[0][1] + ff98) * sqrt(1.0 / 9.0));
    f1180 = R6[9][5] * R1[2][1];
    f1170 = R6[3][5] * R1[0][1];
    R7[9][6] = ((R6[8][5] * k_16340e8) * R1[1][1] +
                (f1048 - f1150) * k_16340f8) -
                (f1170 + f1180) * sqrt(5.0 / 48.0);
    ffb0 = R6[9][6] * R1[2][1];
    f1048 = (R6[3][6] * R1[0][1]);
    R7[9][7] = (R6[8][6] * R1[1][1]) * sqrt(45.0 / 49.0) +
                ((f1010 - f106c) * sqrt(18.0 / 49.0) -
                (f1048 + ffb0) * sqrt(5.0 / 49.0));
    f1158 = R6[9][7] * R1[2][1];
    f1140 = R6[3][7] * R1[0][1];
    R7[9][8] = ((R6[8][7] * k_16340e8) * R1[1][1] +
                (f1118 - f113c) * k_16340f8) -
                (f1140 + f1158) * sqrt(5.0 / 48.0);
    f1010 = R6[9][8] * R1[2][1];
    f106c = R6[3][8] * R1[0][1];
    R7[9][9] = R6[8][8] * R1[1][1] +
                ((f10f8 - f1148) * sqrt(2.0 / 5.0) -
                (f106c + f1010) * sqrt(1.0 / 9.0));
    f1118 = (R6[9][9] * R1[2][1]);
    f10f8 = R6[3][9] * R1[0][1];
    R7[9][10] = (R6[8][9] * k_1634094) * R1[1][1] +
                ((f1104 - f1144) * sqrt(9.0 / 20.0) -
                (f10f8 + f1118) * sqrt(1.0 / 8.0));
    f1104 = (R6[9][10] * R1[2][1]);
    f117c = R6[3][10] * R1[0][1];
    R7[9][11] = (R6[8][10] * R1[1][1]) * sqrt(15.0 / 11.0) +
                ((f10f4 - f112c) * sqrt(6.0 / 11.0) -
                (f117c + f1104) * sqrt(5.0 / 33.0));
    f10f4 = R6[9][11] * R1[2][1];
    f1150 = R6[3][11] * R1[0][1];
    R7[9][12] = (R6[8][11] * R1[1][1]) * sqrt(15.0 / 8.0) +
                ((f1114 - f1058) * k_1634104 -
                (f1150 + f10f4) * sqrt(5.0 / 24.0));
    f1058 = R6[9][12] * R1[2][1];
    f113c = R6[3][12] * R1[0][1];
    R7[9][13] = (R6[8][12] * R1[1][1]) * sqrt(45.0 / 13.0) +
                ((f1050 - f1068) * sqrt(18.0 / 13.0) -
                (f113c + f1058) * sqrt(5.0 / 13.0));
    f1050 = R6[9][12] * R1[2][2] - R6[9][0] * R1[2][0];
    f1068 = R6[3][12] * R1[0][2] - R6[3][0] * R1[0][0];
    R7[9][14] = (R6[8][12] * R1[1][2] - R6[8][0] * R1[1][0]) * sqrt(45.0 / 182.0) +
                ((f1060 - f1110) * sqrt(9.0 / 91.0) -
                (f1068 + f1050) * sqrt(5.0 / 182.0));
    f10e8 = fVar8;
    f10d0 = fVar9;
    f10c0 = R6[3][0] * R1[0][1];
    f10b0 = R6[3][1] * R1[0][1];
    f1080 = R6[3][2] * R1[0][1];
    fff8 = R6[3][3] * R1[0][1];
    f1018 = R6[3][4] * R1[0][1];
    out[58] = WeightedSum(15, &in[49], R7[9]);
    f1060 = R1[2][2] * R6[10][0] + R6[10][12] * R1[2][0];
    f1110 = (R1[0][2] * R6[2][0] + R1[0][0] * R6[2][12]);
    R7[10][0] = (R1[1][2] * R6[9][0] + R6[9][12] * R1[1][0]) * sqrt(20.0 / 91.0) +
                ((f1078 - f1138) * sqrt(45.0 / 364.0) -
                (f1110 + f1060) * sqrt(3.0 / 182.0));
    f1138 = (R6[2][0] * R1[0][1]);
    f1078 = R6[10][0] * R1[2][1];
    R7[10][1] = (R1[1][1] * R6[9][0]) * sqrt(40.0 / 13.0) +
                ((f1124 - f114c) * sqrt(45.0 / 26.0) -
                (f1078 + f1138) * sqrt(3.0 / 13.0));
    f1124 = R6[10][1] * R1[2][1];
    f114c = R6[2][1] * R1[0][1];
    R7[10][2] = (R6[9][1] * R1[1][1]) * sqrt(5.0 / 3.0) +
                ((f1128 - f1178) * k_16340e8 -
                (f114c + f1124) * sqrt(1.0 / 8.0));
    f1128 = R6[10][2] * R1[2][1];
    f1178 = R6[2][2] * R1[0][1];
    R7[10][3] = (R6[9][2] * R1[1][1]) * sqrt(40.0 / 33.0) +
                ((f111c - f1168) * sqrt(15.0 / 22.0) -
                (f1178 + f1128) * sqrt(1.0 / 11.0));
    f111c = R6[10][3] * R1[2][1];
    f1168 = R6[2][3] * R1[0][1];
    R7[10][4] = R6[9][3] * R1[1][1] +
                ((f1120 - f1160) * sqrt(9.0 / 16.0) -
                (f1168 + f111c) * sqrt(3.0 / 40.0));
    f1120 = R6[10][4] * R1[2][1];
    f1160 = (R6[2][4] * R1[0][1]);
    fVar9 = f1134 - f1184;
    R7[10][5] = (R6[9][4] * k_16341e0) * R1[1][1] +
                ((f1130 - f116c) * sqrt(1.0 / 2.0) -
                (f1160 + f1120) * sqrt(1.0 / 15.0));
    f116c = R6[2][5] * R1[0][1];
    f1040 = R6[10][6] * R1[2][1];
    f1130 = R6[10][5] * R1[2][1];
    f1134 = R6[2][6] * R1[0][1];
    R7[10][6] = (fVar9 * k_16340d4 - (f116c + f1130) * k_16340bc) +
                (R6[9][5] * k_1634078) * R1[1][1];
    fVar9 = f115c - f1154;
    f115c = R6[2][7] * R1[0][1];
    f1184 = (R6[10][7] * R1[2][1]);
    R7[10][8] = ((f1164 - f10f0) * k_16340d4 -
                (f115c + f1184) * k_16340bc) +
                (R6[9][7] * k_1634078) * R1[1][1];
    R7[10][7] = (R6[9][6] * R1[1][1]) * sqrt(40.0 / 49.0) +
                (fVar9 * sqrt(45.0 / 98.0) -
                (f1134 + f1040) * sqrt(3.0 / 49.0));
    f1164 = R6[10][8] * R1[2][1];
    f10f0 = R6[2][8] * R1[0][1];
    R7[10][9] = (R6[9][8] * k_16341e0) * R1[1][1] +
                ((f10e0 - f1174) * sqrt(1.0 / 2.0) -
                (f10f0 + f1164) * sqrt(1.0 / 15.0));
    f10e0 = R6[10][9] * R1[2][1];
    f1174 = R6[2][9] * R1[0][1];
    R7[10][10] = R6[9][9] * R1[1][1] +
                ((f10a8 - f10a0) * sqrt(9.0 / 16.0) -
                (f1174 + f10e0) * sqrt(3.0 / 40.0));
    f10a8 = R6[10][10] * R1[2][1];
    f10a0 = R6[2][10] * R1[0][1];
    R7[10][11] = (R6[9][10] * R1[1][1]) * sqrt(40.0 / 33.0) +
                ((f10c8 - f1188) * sqrt(15.0 / 22.0) -
                (f10a0 + f10a8) * sqrt(1.0 / 11.0));
    f10c8 = R6[10][11] * R1[2][1];
    f1188 = (R6[2][11] * R1[0][1]);
    R7[10][12] = (R6[9][11] * R1[1][1]) * sqrt(5.0 / 3.0) +
                ((f1100 - f10d8) * k_16340e8 -
                (f1188 + f10c8) * sqrt(1.0 / 8.0));
    f1100 = (R6[10][12] * R1[2][1]);
    f10d8 = R6[2][12] * R1[0][1];
    R7[10][13] = (R6[9][12] * R1[1][1]) * sqrt(40.0 / 13.0) +
                ((f1090 - f1088) * sqrt(45.0 / 26.0) -
                (f10d8 + f1100) * sqrt(3.0 / 13.0));
    fVar9 = R6[10][12] * R1[2][2] - R6[10][0] * R1[2][0];
    f1090 = fVar9;
    fVar8 = R6[2][12] * R1[0][2] - R6[2][0] * R1[0][0];
    f1088 = fVar8;
    R7[10][14] = (R6[9][12] * R1[1][2] - R6[9][0] * R1[1][0]) * sqrt(20.0 / 91.0) +
                ((f10b8 - f1098) * sqrt(45.0 / 364.0) -
                (fVar8 + fVar9) * sqrt(3.0 / 182.0));
    out[59] = WeightedSum(15, &in[49], R7[10]);
    fVar9 = R1[2][2] * R6[11][0] + R6[11][12] * R1[2][0];
    f10b8 = fVar9;
    fVar8 = R1[0][2] * R6[1][0] + R6[1][12] * R1[0][0];
    f1098 = fVar8;
    R7[11][0] = (R1[1][2] * R6[10][0] + R6[10][12] * R1[1][0]) * sqrt(33.0 / 182.0) +
                ((f10e8 - f10d0) * sqrt(55.0 / 364.0) -
                (fVar8 + fVar9) * sqrt(3.0 / 364.0));
    f10e8 = R6[11][0] * R1[2][1];
    f10d0 = R6[1][0] * R1[0][1];
    R7[11][1] = (R1[1][1] * R6[10][0]) * sqrt(33.0 / 13.0) +
                ((f1000 - f10c0) * sqrt(55.0 / 26.0) -
                (R6[1][0] * R1[0][1] + R6[11][0] * R1[2][1]) * sqrt(3.0 / 26.0));
    f1000 = R6[11][1] * R1[2][1];
    f10c0 = R6[1][1] * R1[0][1];
    R7[11][2] = (R6[10][1] * R1[1][1]) * sqrt(11.0 / 8.0) +
                ((ffe0 - f10b0) * sqrt(55.0 / 48.0) -
                (R6[1][1] * R1[0][1] + R6[11][1] * R1[2][1]) * k_16340bc);
    ffe0 = R6[11][2] * R1[2][1];
    f10b0 = R6[1][2] * R1[0][1];
    R7[11][3] = (R6[10][2] * R1[1][1] +
                (ffb8 - f1080) * k_1634078) -
                (R6[1][2] * R1[0][1] + R6[11][2] * R1[2][1]) * sqrt(1.0 / 22.0);
    ffb8 = R6[11][3] * R1[2][1];
    f1080 = R6[1][3] * R1[0][1];
    R7[11][4] = (R6[10][3] * R1[1][1]) * sqrt(33.0 / 40.0) +
                ((ffa0 - fff8) * sqrt(11.0 / 16.0) -
                (R6[1][3] * R1[0][1] + R6[11][3] * R1[2][1]) * sqrt(3.0 / 80.0));
    fff8 = R6[11][4] * R1[2][1];
    ffa0 = R6[1][4] * R1[0][1];
    R7[11][5] = (R6[10][4] * R1[1][1]) * sqrt(11.0 / 15.0) +
                ((ff98 - f1018) * sqrt(11.0 / 18.0) -
                (R6[1][4] * R1[0][1] + R6[11][4] * R1[2][1]) * sqrt(1.0 / 30.0));
    f1018 = R6[11][5] * R1[2][1];
    ff98 = R6[1][5] * R1[0][1];
    R7[11][6] = (R6[10][5] * R1[1][1]) * sqrt(11.0 / 16.0) +
                ((f1180 - f1170) * sqrt(55.0 / 96.0) -
                (R6[1][5] * R1[0][1] + R6[11][5] * R1[2][1]) * k_1634130);
    f1154 = R6[11][6] * R1[2][1];
    f1180 = R6[1][6] * R1[0][1];
    R7[11][7] = (R6[10][6] * R1[1][1]) * sqrt(33.0 / 49.0) +
                ((ffb0 - f1048) * sqrt(55.0 / 98.0) -
                (f1180 + f1154) * sqrt(3.0 / 98.0));
    ffb0 = R6[11][7] * R1[2][1];
    f1048 = R6[1][7] * R1[0][1];
    R7[11][8] = (R6[10][7] * R1[1][1]) * sqrt(11.0 / 16.0) +
                ((f1158 - f1140) * sqrt(55.0 / 96.0) -
                (R6[1][7] * R1[0][1] + R6[11][7] * R1[2][1]) * k_1634130);
    f1170 = R6[11][8] * R1[2][1];
    f1158 = R6[1][8] * R1[0][1];
    R7[11][9] = (R6[10][8] * R1[1][1]) * sqrt(11.0 / 15.0) +
                ((f1010 - f106c) * sqrt(11.0 / 18.0) -
                (f1158 + f1170) * sqrt(1.0 / 30.0));
    f1010 = R6[11][9] * R1[2][1];
    f106c = R6[1][9] * R1[0][1];
    R7[11][10] = (R6[10][9] * R1[1][1]) * sqrt(33.0 / 40.0) +
                ((f1118 - f10f8) * sqrt(11.0 / 16.0) -
                (f106c + R6[11][9] * R1[2][1]) * sqrt(3.0 / 80.0));
    f1118 = (R6[11][10] * R1[2][1]);
    f10f8 = R6[1][10] * R1[0][1];
    R7[11][11] = (R6[10][10] * R1[1][1] +
                (f1104 - f117c) * k_1634078) -
                (f10f8 + f1118) * sqrt(1.0 / 22.0);
    f1104 = (R6[11][11] * R1[2][1]);
    f1140 = R6[1][11] * R1[0][1];
    R7[11][12] = (R6[10][11] * R1[1][1]) * sqrt(11.0 / 8.0) +
                ((f10f4 - f1150) * sqrt(55.0 / 48.0) -
                (f1140 + f1104) * k_16340bc);
    f10f4 = R6[11][12] * R1[2][1];
    f117c = R6[1][12] * R1[0][1];
    R7[11][13] = (R6[10][12] * R1[1][1]) * sqrt(33.0 / 13.0) +
                ((f1058 - f113c) * sqrt(55.0 / 26.0) -
                (f117c + f10f4) * sqrt(3.0 / 26.0));
    fVar9 = R6[11][12] * R1[2][2] - R6[11][0] * R1[2][0];
    f1058 = fVar9;
    f1150 = R6[1][12] * R1[0][2] - R6[1][0] * R1[0][0];
    R7[11][14] = (R6[10][12] * R1[1][2] - R6[10][0] * R1[1][0]) * sqrt(33.0 / 182.0) +
                ((f1050 - f1068) * sqrt(55.0 / 364.0) -
                (f1150 + fVar9) * sqrt(3.0 / 364.0));
    out[60] = WeightedSum(15, &in[49], R7[11]);
    fVar9 = R1[0][2] * R6[0][0] + R6[0][12] * R1[0][0];
    f1068 = fVar9;
    fVar8 = R6[12][12] * R1[2][0] + R1[2][2] * R6[12][0];
    f1050 = fVar8;
    R7[12][0] = (R1[1][2] * R6[11][0] + R6[11][12] * R1[1][0]) * sqrt(12.0 / 91.0) +
                ((f1060 - f1110) * sqrt(33.0 / 182.0) -
                (fVar8 + fVar9) * sqrt(1.0 / 364.0));
    f1060 = R6[12][0] * R1[2][1];
    f1110 = R6[0][0] * R1[0][1];
    R7[12][1] = (R1[1][1] * R6[11][0]) * sqrt(24.0 / 13.0) +
                ((f1078 - f1138) * sqrt(33.0 / 13.0) -
                (R6[0][0] * R1[0][1] + R6[12][0] * R1[2][1]) * sqrt(1.0 / 26.0));
    f1078 = R6[12][1] * R1[2][1];
    f1138 = (R6[0][1] * R1[0][1]);
    R7[12][2] = R6[11][1] * R1[1][1] +
                ((f1124 - f114c) * sqrt(11.0 / 8.0) -
                (f1138 + R6[12][1] * R1[2][1]) * sqrt(1.0 / 48.0));
    f1124 = R6[12][2] * R1[2][1];
    f114c = R6[0][2] * R1[0][1];
    R7[12][3] = (R6[11][2] * R1[1][1]) * sqrt(8.0 / 11.0) +
                ((f1128 - f1178) -
                (f114c + f1124) * sqrt(1.0 / 66.0));
    f1128 = R6[12][3] * R1[2][1];
    f1178 = R6[0][3] * R1[0][1];
    R7[12][4] = (R6[11][3] * k_1634064) * R1[1][1] +
                ((f111c - f1168) * sqrt(33.0 / 40.0) -
                (f1178 + f1128) * sqrt(1.0 / 80.0));
    f111c = R6[12][4] * R1[2][1];
    f1168 = R6[0][4] * R1[0][1];
    R7[12][5] = (R6[11][4] * R1[1][1]) * sqrt(8.0 / 15.0) +
                ((f1120 - f1160) * sqrt(11.0 / 15.0) -
                (f1168 + f111c) * sqrt(1.0 / 90.0));
    f1160 = (R6[0][5] * R1[0][1]);
    f1120 = R6[12][5] * R1[2][1];
    R7[12][6] = (R6[11][5] * R1[1][1]) * sqrt(1.0 / 2.0) +
                ((f1130 - f116c) * sqrt(11.0 / 16.0) -
                (f1120 + f1160) * sqrt(1.0 / 96.0));
    f116c = R6[0][6] * R1[0][1];
    f1130 = R6[12][6] * R1[2][1];
    R7[12][7] = (R6[11][6] * R1[1][1]) * sqrt(24.0 / 49.0) +
                ((f1040 - f1134) * sqrt(33.0 / 49.0) -
                (f1130 + f116c) * sqrt(1.0 / 98.0));
    f1134 = R6[0][7] * R1[0][1];
    f1040 = R6[12][7] * R1[2][1];
    R7[12][8] = (R6[11][7] * R1[1][1]) * sqrt(1.0 / 2.0) +
                ((f1184 - f115c) * sqrt(11.0 / 16.0) -
                (R6[12][7] * R1[2][1] + f1134) * sqrt(1.0 / 96.0));
    f115c = R6[0][8] * R1[0][1];
    f1184 = (R6[12][8] * R1[2][1]);
    R7[12][9] = (R6[11][8] * R1[1][1]) * sqrt(8.0 / 15.0) +
                ((f1164 - f10f0) * sqrt(11.0 / 15.0) -
                (f1184 + f115c) * sqrt(1.0 / 90.0));
    f10f0 = R6[0][9] * R1[0][1];
    f1164 = R6[12][9] * R1[2][1];
    R7[12][10] = (R6[11][9] * k_1634064) * R1[1][1] +
                ((f10e0 - f1174) * sqrt(33.0 / 40.0) -
                (f1164 + R6[0][9] * R1[0][1]) * sqrt(1.0 / 80.0));
    f1174 = R6[0][10] * R1[0][1];
    f10e0 = R6[12][10] * R1[2][1];
    R7[12][11] = (R6[11][10] * R1[1][1]) * sqrt(8.0 / 11.0) +
                ((f10a8 - f10a0) -
                (R6[12][10] * R1[2][1] + f1174) * sqrt(1.0 / 66.0));
    f10a0 = R6[0][11] * R1[0][1];
    f10a8 = R6[12][11] * R1[2][1];
    R7[12][12] = R6[11][11] * R1[1][1] +
                ((f10c8 - f1188) * sqrt(11.0 / 8.0) -
                (R6[12][11] * R1[2][1] + R6[0][11] * R1[0][1]) * sqrt(1.0 / 48.0));
    f1188 = (R6[0][12] * R1[0][1]);
    f10c8 = R6[12][12] * R1[2][1];
    R7[12][13] = (R6[11][12] * R1[1][1]) * sqrt(24.0 / 13.0) +
                ((f1100 - f10d8) * sqrt(33.0 / 13.0) -
                (R6[12][12] * R1[2][1] + f1188) * sqrt(1.0 / 26.0));
    fVar9 = R6[0][12] * R1[0][2] - R6[0][0] * R1[0][0];
    f10d8 = fVar9;
    fVar8 = R6[12][12] * R1[2][2] - R6[12][0] * R1[2][0];
    f1100 = fVar8;
    R7[12][14] = (R6[11][12] * R1[1][2] - R6[11][0] * R1[1][0]) * sqrt(12.0 / 91.0) +
                ((f1090 - f1088) * sqrt(33.0 / 182.0) -
                (fVar8 + fVar9) * sqrt(1.0 / 364.0));
    out[61] = WeightedSum(15, &in[49], R7[12]);
    R7[13][0] = (f10b8 - f1098) * sqrt(3.0 / 14.0) +
                (R1[1][0] * R6[12][12] + R1[1][2] * R6[12][0]) * sqrt(1.0 / 14.0);
    R7[13][1] = (f10e8 - f10d0) * sqrt(3.0) +
                R6[12][0] * R1[1][1];
    R7[13][2] = (f1000 - f10c0) * sqrt(13.0 / 8.0) +
                (R6[12][1] * R1[1][1]) * sqrt(13.0 / 24.0);
    R7[13][3] = (R6[12][2] * R1[1][1]) * sqrt(13.0 / 33.0) +
                (ffe0 - f10b0) * sqrt(13.0 / 11.0);
    R7[13][4] = (R6[12][3] * R1[1][1]) * sqrt(13.0 / 40.0) +
                (ffb8 - f1080) * sqrt(39.0 / 40.0);
    R7[13][5] = (R6[12][4] * R1[1][1]) * sqrt(13.0 / 45.0) +
                (fff8 - ffa0) * sqrt(13.0 / 15.0);
    R7[13][6] = (R6[12][5] * R1[1][1]) * sqrt(13.0 / 48.0) +
                (f1018 - ff98) * sqrt(13.0 / 16.0);
    R7[13][7] = (R6[12][6] * R1[1][1]) * sqrt(13.0 / 49.0) +
                (f1154 - f1180) * sqrt(39.0 / 49.0);
    R7[13][8] = (R6[12][7] * R1[1][1]) * sqrt(13.0 / 48.0) +
                (ffb0 - f1048) * sqrt(13.0 / 16.0);
    R7[13][9] = (R6[12][8] * R1[1][1]) * sqrt(13.0 / 45.0) +
                (f1170 - f1158) * sqrt(13.0 / 15.0);
    R7[13][10] = (R6[12][9] * R1[1][1]) * sqrt(13.0 / 40.0) +
                (f1010 - f106c) * sqrt(39.0 / 40.0);
    R7[13][11] = (R6[12][10] * R1[1][1]) * sqrt(13.0 / 33.0) +
                (f1118 - f10f8) * sqrt(13.0 / 11.0);
    R7[13][12] = (f1104 - f1140) * sqrt(13.0 / 8.0) +
                (R6[12][11] * R1[1][1]) * sqrt(13.0 / 24.0);
    R7[13][13] = (f10f4 - f117c) * sqrt(3.0) + R6[12][12] * R1[1][1];
    R7[13][14] = (f1058 - f1150) * sqrt(3.0 / 14.0) +
                (R6[12][12] * R1[1][2] - R6[12][0] * R1[1][0]) * sqrt(1.0 / 14.0);
    out[62] = WeightedSum(15, &in[49], R7[13]);
    R7[14][1] = (f1060 - f1110) * sqrt(7.0 / 2.0);
    R7[14][0] = (f1050 - f1068) * k_16340dc;
    R7[14][2] = (f1078 - f1138) * sqrt(91.0 / 48.0);
    R7[14][3] = (f1124 - f114c) * sqrt(91.0 / 66.0);
    R7[14][4] = (f1128 - f1178) * sqrt(91.0 / 80.0);
    R7[14][5] = (f111c - f1168) * sqrt(91.0 / 90.0);
    R7[14][6] = (f1120 - f1160) * sqrt(91.0 / 96.0);
    R7[14][7] = (f1130 - f116c) * sqrt(13.0 / 14.0);
    R7[14][8] = (f1040 - f1134) * sqrt(91.0 / 96.0);
    R7[14][9] = (f1184 - f115c) * sqrt(91.0 / 90.0);
    R7[14][14] = (f1100 - f10d8) * k_16340dc;
    R7[14][10] = (f1164 - f10f0) * sqrt(91.0 / 80.0);
    R7[14][11] = (f10e0 - f1174) * sqrt(91.0 / 66.0);
    R7[14][12] = (f10a8 - f10a0) * sqrt(91.0 / 48.0);
    R7[14][13] = (f10c8 - f1188) * sqrt(7.0 / 2.0);
    out[63] = WeightedSum(15, &in[49], R7[14]);
}
}  // namespace SP

// @ 0x00794610
void SP_MultiplyZH(int param_1, int param_2, int param_3, void* param_4, char* param_5)
{
    // omitted: the ZH basis multiply
    (void)param_1;
    (void)param_2;
    (void)param_3;
    (void)param_4;
    (void)param_5;
}

// @ 0x007948d0
void SP_AddColourSample(float* param_1, int param_2, float* param_3, float* param_4)
{
    // omitted: the colour-sample accumulation
    (void)param_1;
    (void)param_2;
    (void)param_3;
    (void)param_4;
}

// @ 0x00794e80
void RotateZHToSHAdd(float *param_1, int param_2, float *param_3, float *param_4, float *param_5)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float *pfVar7;
    int iVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float local_114[16];
    float local_d4[52];

    fVar3 = *param_3;
    fVar4 = param_3[1];
    fVar5 = param_3[2];
    fVar6 = param_3[3];
    fVar11 = *param_4;
    *param_5 = fVar11 * fVar3 + *param_5;
    param_5[1] = fVar11 * fVar4 + param_5[1];
    param_5[2] = fVar11 * fVar5 + param_5[2];
    param_5[3] = fVar11 * fVar6 + param_5[3];
    if (1 < param_2) {
        fVar11 = param_4[1];
        fVar9 = param_1[1];
        fVar1 = param_1[2];
        fVar2 = *param_1;
        fVar10 = fVar11 * fVar9;
        param_5[4] = fVar10 * fVar3 + param_5[4];
        param_5[5] = fVar10 * fVar4 + param_5[5];
        param_5[6] = fVar10 * fVar5 + param_5[6];
        param_5[7] = fVar10 * fVar6 + param_5[7];
        fVar10 = fVar11 * fVar1;
        fVar11 = fVar11 * fVar2;
        param_5[8] = fVar10 * fVar3 + param_5[8];
        param_5[9] = fVar10 * fVar4 + param_5[9];
        param_5[10] = fVar10 * fVar5 + param_5[10];
        param_5[0xb] = fVar10 * fVar6 + param_5[0xb];
        param_5[0xc] = fVar11 * fVar3 + param_5[0xc];
        param_5[0xd] = fVar11 * fVar4 + param_5[0xd];
        param_5[0xe] = fVar11 * fVar5 + param_5[0xe];
        param_5[0xf] = fVar11 * fVar6 + param_5[0xf];
        if (2 < param_2) {
            local_114[0] = ((fVar2 * fVar9) * 2.0) * DAT_01634104;
            local_114[1] = ((fVar1 * fVar9) * 2.0) * DAT_01634104;
            local_114[2] = fVar1 * fVar1 - (fVar9 * fVar9 + fVar2 * fVar2) * DAT_016340dc;
            local_114[4] = (fVar2 * fVar2 - fVar9 * fVar9) * DAT_01634104;
            fVar11 = param_4[2];
            local_114[3] = ((fVar2 * fVar1) * 2.0) * DAT_01634104;
            iVar8 = 0;
            pfVar7 = param_5 + 0x10;
            do {
                fVar10 = local_114[iVar8] * fVar11;
                iVar8 = iVar8 + 1;
                *pfVar7 = fVar10 * fVar3 + *pfVar7;
                pfVar7[1] = fVar10 * fVar4 + pfVar7[1];
                pfVar7[2] = fVar10 * fVar5 + pfVar7[2];
                pfVar7[3] = fVar10 * fVar6 + pfVar7[3];
                pfVar7 = pfVar7 + 4;
            } while (iVar8 < 5);
            if (3 < param_2) {
                local_d4[0] = (local_114[4] * fVar9 + local_114[0] * fVar2) * DAT_01634078;
                local_d4[1] = ((local_114[1] * fVar2 + local_114[0] * fVar1) + local_114[3] * fVar9) *
                              _DAT_016340cc;
                local_d4[2] = ((DAT_016341e0 * local_114[1]) * fVar1 -
                              (local_114[0] * fVar2 - local_114[4] * fVar9) * DAT_016341b0) +
                              (DAT_01634150 * local_114[2]) * fVar9;
                local_d4[3] = local_114[2] * fVar1 -
                              (local_114[1] * fVar9 + local_114[3] * fVar2) * DAT_016340b0;
                local_d4[4] = ((DAT_01634150 * local_114[2]) * fVar2 -
                              (local_114[0] * fVar9 + local_114[4] * fVar2) * DAT_016341b0) +
                              (DAT_016341e0 * local_114[3]) * fVar1;
                local_d4[6] = (local_114[4] * fVar2 - local_114[0] * fVar9) * DAT_01634078;
                local_d4[5] = ((local_114[4] * fVar1 + local_114[3] * fVar2) - local_114[1] * fVar9) *
                              _DAT_016340cc;
                fVar11 = param_4[3];
                iVar8 = 0;
                pfVar7 = param_5 + 0x24;
                do {
                    fVar10 = local_d4[iVar8] * fVar11;
                    iVar8 = iVar8 + 1;
                    *pfVar7 = fVar10 * fVar3;
                    pfVar7[1] = fVar10 * fVar4;
                    pfVar7[2] = fVar10 * fVar5;
                    pfVar7[3] = fVar10 * fVar6;
                    pfVar7 = pfVar7 + 4;
                } while (iVar8 < 7);
                if (4 < param_2) {
                    local_114[0] = (local_d4[6] * fVar9 + local_d4[0] * fVar2) * DAT_016340fc;
                    local_114[1] = (local_d4[5] * fVar9 + local_d4[1] * fVar2) * _DAT_0163409c +
                                   (DAT_016341dc * local_d4[0]) * fVar1;
                    local_114[2] = ((local_d4[2] * fVar2 + local_d4[4] * fVar9) * DAT_016340d4 -
                                   (local_d4[0] * fVar2 - local_d4[6] * fVar9) * DAT_01634130) +
                                   (DAT_01634104 * local_d4[1]) * fVar1;
                    local_114[3] = ((DAT_016340e8 * local_d4[2]) * fVar1 -
                                   (local_d4[1] * fVar2 - local_d4[5] * fVar9) * DAT_01634074) +
                                   (DAT_016340ec * local_d4[3]) * fVar9;
                    local_114[4] = local_d4[3] * fVar1 -
                                   (local_d4[2] * fVar9 + local_d4[4] * fVar2) * DAT_016340f8;
                    local_114[5] = ((DAT_016340ec * local_d4[3]) * fVar2 -
                                   (local_d4[1] * fVar9 + local_d4[5] * fVar2) * DAT_01634074) +
                                   (DAT_016340e8 * local_d4[4]) * fVar1;
                    local_114[6] = ((local_d4[4] * fVar2 - local_d4[2] * fVar9) * DAT_016340d4 -
                                   (local_d4[0] * fVar9 + local_d4[6] * fVar2) * DAT_01634130) +
                                   (DAT_01634104 * local_d4[5]) * fVar1;
                    fVar11 = param_4[4];
                    local_114[8] = (local_d4[6] * fVar2 - local_d4[0] * fVar9) * DAT_016340fc;
                    local_114[7] = (local_d4[5] * fVar2 - local_d4[1] * fVar9) * _DAT_0163409c +
                                   (DAT_016341dc * local_d4[6]) * fVar1;
                    iVar8 = 0;
                    pfVar7 = param_5 + 0x40;
                    do {
                        fVar10 = local_114[iVar8] * fVar11;
                        iVar8 = iVar8 + 1;
                        *pfVar7 = fVar10 * fVar3;
                        pfVar7[1] = fVar10 * fVar4;
                        pfVar7[2] = fVar10 * fVar5;
                        pfVar7[3] = fVar10 * fVar6;
                        pfVar7 = pfVar7 + 4;
                    } while (iVar8 < 9);
                    if (5 < param_2) {
                        local_d4[0] = (local_114[8] * fVar9 + local_114[0] * fVar2) * 0.94868326;
                        local_d4[1] = (fVar1 * local_114[0]) * 0.6 +
                                      (local_114[7] * fVar9 + local_114[1] * fVar2) * _DAT_01634134;
                        local_d4[2] = (local_114[1] * fVar1) * 0.8 +
                                      ((local_114[6] * fVar9 + local_114[2] * fVar2) * _DAT_0163410c -
                                      (local_114[0] * fVar2 - local_114[8] * fVar9) * _DAT_01634168);
                        local_d4[3] = (local_114[2] * fVar1) * 0.9165151 +
                                      ((local_114[5] * fVar9 + local_114[3] * fVar2) * _DAT_016340e4 -
                                      (local_114[1] * fVar2 - local_114[7] * fVar9) * _DAT_016340a8);
                        local_d4[4] = (local_114[3] * fVar1) * 0.9797959 +
                                      ((local_114[4] * _DAT_01634064) * fVar9 -
                                      (local_114[2] * fVar2 - local_114[6] * fVar9) * _DAT_0163405c);
                        local_d4[5] = local_114[4] * fVar1 -
                                      (local_114[3] * fVar9 + local_114[5] * fVar2) * 0.6324555;
                        local_d4[6] = (local_114[5] * fVar1) * 0.9797959 +
                                      ((local_114[4] * _DAT_01634064) * fVar2 -
                                      (local_114[2] * fVar9 + local_114[6] * fVar2) * _DAT_0163405c);
                        local_d4[7] = (local_114[6] * fVar1) * 0.9165151 +
                                      ((local_114[5] * fVar2 - local_114[3] * fVar9) * _DAT_016340e4 -
                                      (local_114[1] * fVar9 + local_114[7] * fVar2) * _DAT_016340a8);
                        local_d4[8] = (local_114[7] * fVar1) * 0.8 +
                                      ((local_114[6] * fVar2 - local_114[2] * fVar9) * _DAT_0163410c -
                                      (local_114[0] * fVar9 + local_114[8] * fVar2) * _DAT_01634168);
                        fVar11 = param_4[5];
                        iVar8 = 0;
                        local_d4[9] = (local_114[8] * fVar1) * 0.6 +
                                      (local_114[7] * fVar2 - local_114[1] * fVar9) * _DAT_01634134;
                        local_d4[10] = (local_114[8] * fVar2 - local_114[0] * fVar9) * 0.94868326;
                        pfVar7 = param_5 + 100;
                        do {
                            fVar10 = local_d4[iVar8] * fVar11;
                            iVar8 = iVar8 + 1;
                            *pfVar7 = fVar10 * fVar3;
                            pfVar7[1] = fVar10 * fVar4;
                            pfVar7[2] = fVar10 * fVar5;
                            pfVar7[3] = fVar10 * fVar6;
                            pfVar7 = pfVar7 + 4;
                        } while (iVar8 < 0xb);
                        if (param_2 < 7) {
                            return;
                        }
                        local_114[0] = (local_d4[0] * fVar2 + local_d4[10] * fVar9) * 0.95742714;
                        local_114[1] = (local_d4[0] * fVar1) * 0.5527708 +
                                       (local_d4[9] * fVar9 + local_d4[1] * fVar2) * 0.8740074;
                        local_114[2] = ((local_d4[1] * _DAT_016340cc) * fVar1 +
                                       (local_d4[8] * fVar9 + local_d4[2] * fVar2) * DAT_016340ec) -
                                       (local_d4[0] * fVar2 - local_d4[10] * fVar9) * 0.11785113;
                        local_114[3] = (local_d4[2] * DAT_01634104) * fVar1 +
                                       ((local_d4[3] * fVar2 + local_d4[7] * fVar9) * 0.70710677 -
                                       (local_d4[1] * fVar2 - local_d4[9] * fVar9) * 0.20412415);
                        local_114[4] = (local_d4[3] * DAT_016341e0) * fVar1 +
                                       ((local_d4[6] * fVar9 + local_d4[4] * fVar2) * 0.62360954 -
                                       (local_d4[2] * fVar2 - local_d4[8] * fVar9) * _DAT_0163407c);
                        local_114[5] = fVar9 * (local_d4[5] * 0.7637626) +
                                       ((local_d4[4] * fVar1) * 0.9860133 -
                                       (local_d4[3] * fVar2 - local_d4[7] * fVar9) * 0.37267798);
                        local_114[6] = local_d4[5] * fVar1 -
                                       (local_d4[4] * fVar9 + local_d4[6] * fVar2) * 0.6454972;
                        local_114[7] = (local_d4[6] * fVar1) * 0.9860133 +
                                       (fVar2 * (local_d4[5] * 0.7637626) -
                                       (local_d4[3] * fVar9 + local_d4[7] * fVar2) * 0.37267798);
                        fVar11 = param_4[6];
                        iVar8 = 0;
                        local_114[8] = (local_d4[7] * DAT_016341e0) * fVar1 +
                                       ((local_d4[6] * fVar2 - local_d4[4] * fVar9) * 0.62360954 -
                                       (local_d4[2] * fVar9 + local_d4[8] * fVar2) * _DAT_0163407c);
                        local_114[9] = (local_d4[8] * DAT_01634104) * fVar1 +
                                       ((local_d4[7] * fVar2 - local_d4[3] * fVar9) * 0.70710677 -
                                       (local_d4[1] * fVar9 + local_d4[9] * fVar2) * 0.20412415);
                        local_114[10] =
                             ((local_d4[9] * _DAT_016340cc) * fVar1 +
                             (local_d4[8] * fVar2 - local_d4[2] * fVar9) * DAT_016340ec) -
                             (local_d4[0] * fVar9 + local_d4[10] * fVar2) * 0.11785113;
                        local_114[0xb] =
                             (local_d4[10] * fVar1) * 0.5527708 +
                             (local_d4[9] * fVar2 - local_d4[1] * fVar9) * 0.8740074;
                        local_114[0xc] = (local_d4[10] * fVar2 - local_d4[0] * fVar9) * 0.95742714;
                        pfVar7 = param_5 + 0x90;
                        do {
                            fVar10 = local_114[iVar8] * fVar11;
                            iVar8 = iVar8 + 1;
                            *pfVar7 = fVar10 * fVar3;
                            pfVar7[1] = fVar10 * fVar4;
                            pfVar7[2] = fVar10 * fVar5;
                            pfVar7[3] = fVar10 * fVar6;
                            pfVar7 = pfVar7 + 4;
                        } while (iVar8 < 0xd);
                        if (7 < param_2) {
                            local_d4[0] = (local_114[0] * fVar2 + local_114[0xc] * fVar9) * 0.9636241;
                            local_d4[1] = (local_114[0] * fVar1) * 0.5150787 +
                                          (local_114[1] * fVar2 + local_114[0xb] * fVar9) * 0.89214253;
                            local_d4[2] = (local_114[1] * fVar1) * 0.6998542 +
                                          ((local_114[2] * fVar2 + local_114[10] * fVar9) * 0.82065177 -
                                          (local_114[0] * fVar2 - local_114[0xc] * fVar9) * 0.101015255);
                            local_d4[3] = (local_114[2] * fVar1) * 0.82065177 +
                                          ((local_114[9] * fVar9 + local_114[3] * fVar2) * 0.7491492 -
                                          (local_114[1] * fVar2 - local_114[0xb] * fVar9) * 0.17496355);
                            local_d4[4] = (local_114[3] * fVar1) * 0.9035079 +
                                          ((local_114[8] * fVar9 + local_114[4] * fVar2) * 0.6776309 -
                                          (local_114[2] * fVar2 - local_114[10] * fVar9) * 0.24743582);
                            local_d4[5] = (local_114[4] * fVar1) * 0.95831484 +
                                          ((local_114[7] * fVar9 + local_114[5] * fVar2) * 0.60609156 -
                                          (local_114[3] * fVar2 - local_114[9] * fVar9) * 0.31943828);
                            local_d4[6] = fVar9 * (local_114[6] * 0.75592893) +
                                          ((local_114[5] * fVar1) * 0.98974335 -
                                          (local_114[4] * fVar2 - local_114[8] * fVar9) * 0.3912304);
                            local_d4[7] = local_114[6] * fVar1 -
                                          (local_114[5] * fVar9 + local_114[7] * fVar2) * 0.65465367;
                            local_d4[8] = (local_114[7] * fVar1) * 0.98974335 +
                                          (fVar2 * (local_114[6] * 0.75592893) -
                                          (local_114[4] * fVar9 + local_114[8] * fVar2) * 0.3912304);
                            local_d4[9] = (fVar1 * local_114[8]) * 0.95831484 +
                                          ((local_114[7] * fVar2 - local_114[5] * fVar9) * 0.60609156 -
                                          (local_114[3] * fVar9 + local_114[9] * fVar2) * 0.31943828);
                            local_d4[10] = (local_114[9] * fVar1) * 0.9035079 +
                                           ((local_114[8] * fVar2 - local_114[4] * fVar9) * 0.6776309 -
                                           (local_114[2] * fVar9 + local_114[10] * fVar2) * 0.24743582);
                            fVar11 = param_4[7];
                            iVar8 = 0;
                            local_d4[0xb] =
                                 (fVar1 * local_114[10]) * 0.82065177 +
                                 ((local_114[9] * fVar2 - local_114[3] * fVar9) * 0.7491492 -
                                 (local_114[1] * fVar9 + local_114[0xb] * fVar2) * 0.17496355);
                            local_d4[0xc] =
                                 (local_114[0xb] * fVar1) * 0.6998542 +
                                 ((local_114[10] * fVar2 - local_114[2] * fVar9) * 0.82065177 -
                                 (local_114[0] * fVar9 + local_114[0xc] * fVar2) * 0.101015255);
                            local_d4[0xd] =
                                 (local_114[0xc] * fVar1) * 0.5150787 +
                                 (local_114[0xb] * fVar2 - local_114[1] * fVar9) * 0.89214253;
                            local_d4[0xe] = (local_114[0xc] * fVar2 - local_114[0] * fVar9) * 0.9636241;
                            pfVar7 = param_5 + 0xc4;
                            do {
                                fVar9 = local_d4[iVar8] * fVar11;
                                iVar8 = iVar8 + 1;
                                *pfVar7 = fVar9 * fVar3;
                                pfVar7[1] = fVar9 * fVar4;
                                pfVar7[2] = fVar9 * fVar5;
                                pfVar7[3] = fVar9 * fVar6;
                                pfVar7 = pfVar7 + 4;
                            } while (iVar8 < 0xf);
                            return;
                        }
                    }
                }
            }
        }
    }
    return;
}

// @ 0x00795ec0
void FUN_00795ec0(int param_1, int param_2, int param_3)
{
    int iVar6;
    unsigned int uVar8;
    int iVar7;
    int iVar1;
    int local_80;
    int local_70;
    unsigned int local_68;
    int *local_84;
    unsigned short *local_7c;
    float local_4c[4];
    float fStack_3c;
    float fStack_38;
    int uStack_34;
    float local_30;
    float fStack_2c;
    float fStack_28;
    int uStack_24;
    float local_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    iVar6 = *(int *)(param_1 + 0x1c);
    uVar8 = (int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2;
    if ((((uVar8 & uVar8 - 1) == 0) && (uVar8 * 4 - iVar6 == 0)) &&
        (uVar8 * 3 == *(int *)(param_1 + 0x20))) {
        iVar7 = *(int *)(param_1 + 0x28);
        uStack_34 = 0;
        local_68 = 0;
        local_84 = DAT_0140eae8;
        do {
            local_7c = (unsigned short *)(iVar7 + (local_84[1] * iVar6 * 3 + *local_84 * 3) * uVar8 * 2);
            local_80 = 0;
            if (0 < (int)uVar8) {
                iVar1 = ((int)local_68 >> 1) * 4;
                do {
                    local_70 = 0;
                    float fVar14 = (float)(1.0 - (((double)local_80 + 0.5) * 2.0) / (double)(int)uVar8);
                    float fVar2 = fVar14;
                    unsigned short *puVar9 = local_7c;
                    do {
                        double fVar13 = (((double)local_70 + 0.5) * 2.0) / (double)(int)uVar8 - 1.0;
                        double fVar15 = (double)(float)local_84[2] * fVar13 + (double)(float)local_84[3] * (double)fVar14;
                        fStack_38 = (float)((6.103609e-05 / ((float)(int)uVar8 * (float)(int)uVar8)) /
                                            (((float)fVar13 * (float)fVar13 + fVar2 * fVar2) + 1.0f));
                        local_4c[3] = (float)*puVar9 * fStack_38;
                        fVar14 = (float)((double)(float)local_84[5] * (double)fVar14 + (double)(float)local_84[4] * fVar13);
                        fStack_3c = (float)puVar9[1] * fStack_38;
                        fStack_38 = (float)puVar9[2] * fStack_38;
                        uStack_24 = uStack_34;
                        float fVar3 = (float)(1.0 / sqrt(((double)fVar14 * (double)fVar14 + fVar15 * fVar15) + 1.0));
                        float fVar16 = fVar3;
                        if ((local_68 & 1) != 0) {
                            fVar16 = -fVar3;
                        }
                        unsigned char bVar4 = (&DAT_0140eac5)[iVar1];
                        unsigned char bVar5 = (&DAT_0140eac6)[iVar1];
                        local_30 = local_4c[3];
                        fStack_2c = fStack_3c;
                        fStack_28 = fStack_38;
                        local_20 = fStack_38;
                        fStack_1c = fStack_38;
                        fStack_18 = fStack_38;
                        fStack_14 = fStack_38;
                        local_4c[(unsigned char)(&DAT_0140eac4)[iVar1]] = fVar16 * (float)fVar15;
                        local_4c[bVar4] = fVar3 * (float)fVar14;
                        local_4c[bVar5] = fVar16;
                        AddColourSample(local_4c + 3, param_2, local_4c, param_3);
                        local_70 = local_70 + 1;
                        puVar9 = puVar9 + 3;
                    } while (local_70 < (int)uVar8);
                    local_7c = local_7c + iVar6 * 3;
                    local_80 = local_80 + 1;
                } while (local_80 < (int)uVar8);
            }
            local_84 = local_84 + 6;
            local_68 = local_68 + 1;
        } while ((int)local_84 < (int)0x140eb78);
    }
    return;
}

// @ 0x007961d0
void AddSphereLighting(float param_1, float param_2, float param_3, float param_4, int param_5, int param_6, int param_7)
{
    float *pfVar1;
    float fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8;
    float local_8c, local_88, local_84, local_80, fStack_7c, fStack_78, fStack_74;
    float local_70, fStack_6c, fStack_68, fStack_64;
    float local_60, fStack_5c, fStack_58, fStack_54;
    float local_50, fStack_4c, fStack_48, fStack_44;
    float local_40, fStack_3c, fStack_38, fStack_34;
    float local_30, fStack_2c, fStack_28, fStack_24;
    float local_20, fStack_1c, fStack_18, fStack_14;

    if (0 < param_5) {
        fVar4 = DAT_016340e0 * DAT_0153ae10;
        fVar5 = DAT_016341d8 * DAT_0153ae10;
        fVar8 = DAT_01634068 * DAT_0153ae10;
        fVar6 = DAT_01634108 * DAT_0153ae10;
        local_70 = param_4;
        fStack_6c = param_4;
        fStack_68 = param_4;
        fStack_64 = param_4;
        pfVar1 = (float *)(param_6 + 0x18);
        do {
            local_88 = pfVar1[-1] - param_2;
            local_84 = *pfVar1 - param_3;
            fVar7 = pfVar1[-2] - param_1;
            fVar2 = (local_84 * local_84 + local_88 * local_88) + fVar7 * fVar7;
            fStack_74 = pfVar1[-3];
            local_80 = fStack_74 * local_70;
            fStack_7c = fStack_74 * fStack_6c;
            fStack_78 = fStack_74 * fStack_68;
            fStack_74 = fStack_74 * fStack_64;
            local_60 = pfVar1[-2];
            fStack_5c = pfVar1[-1];
            fStack_58 = *pfVar1;
            fStack_54 = pfVar1[1];
            fVar3 = fVar2 / (fStack_54 * fStack_54 + fVar2);
            local_8c = 1.0f / (sqrtf(fVar2) + 1e-06f);
            local_84 = local_84 * local_8c;
            local_88 = local_88 * local_8c;
            local_8c = local_8c * fVar7;
            fStack_44 = ((1.0f - sqrtf(fVar3)) * (fVar4 * 2.0f)) * local_80;
            local_20 = pfVar1[-6];
            fStack_1c = pfVar1[-5];
            fStack_18 = pfVar1[-4];
            fVar2 = pfVar1[-3];
            local_50 = fStack_44 * local_20;
            fStack_4c = fStack_44 * fStack_1c;
            fStack_48 = fStack_44 * fStack_18;
            fStack_44 = fStack_44 * fVar2;
            fStack_34 = (((1.0f - fVar3) * (fVar8 * 2.0f)) * local_80) * 0.5f;
            local_40 = fStack_34 * local_20;
            fStack_3c = fStack_34 * fStack_1c;
            fStack_38 = fStack_34 * fStack_18;
            fStack_34 = fStack_34 * fVar2;
            fStack_24 = (((fVar5 * 2.0f) * (1.0f - fVar3)) * local_80) * sqrtf(fVar3);
            local_30 = fStack_24 * local_20;
            fStack_2c = fStack_24 * fStack_1c;
            fStack_28 = fStack_24 * fStack_18;
            fStack_24 = fStack_24 * fVar2;
            fStack_14 = ((((6.0f - fVar3 * 5.0f) * fVar3 - 1.0f) * (fVar6 * 2.0f)) * local_80) * 0.25f;
            local_20 = fStack_14 * local_20;
            fStack_1c = fStack_14 * fStack_1c;
            fStack_18 = fStack_14 * fStack_18;
            fStack_14 = fStack_14 * fVar2;
            RotateZHToSHAddT(&local_8c, 4, &local_50, param_7);
            pfVar1 = pfVar1 + 8;
            param_5 = param_5 + -1;
        } while (param_5 != 0);
    }
    return;
}

// @ 0x00796420
void CalcAtmosphereZH(int param_1, int *param_2, int param_3, int param_4)
{
    float local_a0[8];
    unsigned char local_80[124];

    if (0 < param_1) {
        local_a0[0] = *(float *)param_2;
        local_a0[1] = *(float *)(param_2 + 1);
        local_a0[2] = *(float *)(param_2 + 2);
        local_a0[3] = *(float *)(param_2 + 3);
        CalcHGPhaseZH(*(float *)(param_2 + 3), local_a0, 7, local_80);
    }
    if (1 < param_1) {
        param_2 = param_2 + 7;
        param_1 = param_1 + -1;
        do {
            local_a0[3] = *(float *)param_2;
            local_a0[0] = *(float *)(param_2 - 3);
            local_a0[1] = *(float *)(param_2 - 2);
            local_a0[2] = *(float *)(param_2 - 1);
            CalcHGPhaseZHAdd(*(float *)param_2, local_a0, 7, local_80);
            param_2 = param_2 + 4;
            param_1 = param_1 + -1;
        } while (param_1 != 0);
    }
    local_a0[0] = DAT_0140ebdc;
    local_a0[1] = DAT_0140ebd8;
    local_a0[2] = DAT_0140ebd4;
    local_a0[3] = DAT_0140ebd0;
    local_a0[4] = DAT_0140ebcc;
    local_a0[5] = DAT_0140ebc8;
    local_a0[6] = DAT_0140ebc4;
    if (param_3 == 3) {
        MultiplyZH(3, local_a0, local_80, param_4, _kBasisTriples3);
    } else if (param_3 == 4) {
        MultiplyZH(4, local_a0, local_80, param_4, _kBasisTriples4);
    } else if (param_3 == 5) {
        MultiplyZH(5, local_a0, local_80, param_4, _kBasisTriples5);
    }
    return;
}
