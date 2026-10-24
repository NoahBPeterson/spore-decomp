// Slice s00783590: spherical-harmonic (SH) helpers (0x783590..0x7843a0):
// normalisation apply/remove, diffuse reflection, Z mirror, SH basis multiply,
// hemisphere-environment projection and Henyey-Greenstein phase terms.
// /O2 /MD /Gy /EHsc /TP module (SSE1 + x87).
#include "types.h"
#include <math.h>
#include <string.h>
#include <xmmintrin.h>
#pragma intrinsic(sqrt)

// cl15 does not inline `sqrt` in this TU (the original ends each term with an x87 fsqrt);
// sqrt_ss gives the same single-precision result without a CRT call.
static inline float isqrt(const float* p) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_load_ss(p))); }

// SH normalisation constants (PDB names)
extern float kSH_Y_00, kSH_Y_1x;
extern float kSH_Y_2_2, kSH_Y_2_1, kSH_Y_20, kSH_Y_21, kSH_Y_22;
extern float kSH_Y_3_3, kSH_Y_3_2, kSH_Y_3_1, kSH_Y_30, kSH_Y_31, kSH_Y_32, kSH_Y_33;
extern float kSH_Y_4_4, kSH_Y_4_3, kSH_Y_4_2, kSH_Y_4_1, kSH_Y_40, kSH_Y_41, kSH_Y_42, kSH_Y_43, kSH_Y_44;
extern float g_153ae10;
extern char  kBasisTriples3, kBasisTriples4, kBasisTriples5;

void SP_MultiplySH(int n, int a, int b, void* out, char* triples);
float FUN_00783130(float theta, unsigned m, float phi, float extra);

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
            __m128 scale = _mm_set1_ps(isqrt(&t));
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
            __m128 scale = _mm_set1_ps(isqrt(&t));
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

// @ 0x00783f40
void FUN_00783f40(int order, int a, int b, void* out)
{
    switch (order) {
    case 3: SP_MultiplySH(9, a, b, out, &kBasisTriples3); break;
    case 4: SP_MultiplySH(0x10, a, b, out, &kBasisTriples4); break;
    case 5: SP_MultiplySH(0x19, a, b, out, &kBasisTriples5); break;
    }
}

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

// @ 0x00783fb0
// Projects a hemisphere environment map onto the real SH basis: for every texel inside the unit
// disc the direction gives (theta, phi), the texel colour is weighted by the solid-angle sinc
// term and accumulated per basis function FUN_00783130(l, m, ...).
void FindSHCoeffsFromHemiEnvMap(int env, int order, float* out)
{
    const int w = *(const int*)(env + 0x1c);
    const int h = *(const int*)(env + 0x20);
    const unsigned char* row = (const unsigned char*)(*(const int*)(env + 0x28));
    const float wf = (float)w;
    const float hf = (float)h;
    const float scale = (g_153ae10 * 2.0f) / wf;
    const float scale2 = scale * scale;
    for (int y = 0; y < h; ++y) {
        const float ny = (float)(1.0 - 2.0 * ((double)y + 0.5) / hf);
        const float ny2 = ny * ny;
        for (int x = 0; x < w; ++x) {
            const unsigned char* tex = row + x * 4;
            const float nx = (float)(2.0 * ((double)x + 0.5) / wf - 1.0);
            const float r2 = nx * nx + ny2;
            if (r2 > 1.0f)
                continue;
            const float pr = sqrtf(r2) * g_153ae10;
            const float ang = atan2f(ny, nx);
            const float sp = sinf(pr);
            const float q = sp / pr;
            const float sinc = q * scale2;
            const float phi = atan2f(-cosf(pr), cosf(ang) * sp);
            const float acosv = acosf(sinf(ang) * sp);
            const float ch0 = (float)tex[0] * (1.0f / 255.0f);
            const float ch1 = (float)tex[1] * (1.0f / 255.0f);
            const float ch2 = (float)tex[2] * (1.0f / 255.0f);
            const float ch3 = (float)tex[3] * (1.0f / 255.0f);
            int l = 0;
            float* o = out;
            for (int m = 0; m < order; ++m) {
                if ((float)m >= (float)(l + 1) * (float)(l + 1))
                    ++l;
                union { int i; float f; } tb;   // the original passes l's bit pattern as a float
                tb.i = l;
                float g = FUN_00783130(tb.f, (unsigned)(m - l * (l + 1)), acosv, phi) * sinc;
                o[0] += ch2 * g;
                o[1] += ch1 * g;
                o[2] += ch0 * g;
                o[3] += ch3 * g;
                o += 4;
            }
        }
        row += w * 4;
    }
}
