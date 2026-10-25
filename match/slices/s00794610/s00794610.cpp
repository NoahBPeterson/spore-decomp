// Slice s00794610: SP::MultiplyZH<float, rw::math::vpu::Vector4> (0x794610) and
// SP::AddColourSample (0x7948d0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
//
// 0x794610 is the Zonal/Spherical-Harmonic basis product: it clears the output,
// then walks the 8-byte sparse product table, decoding each basis index from the
// triangular number stored as a signed byte (i.e. index = floor(sqrt(entry))).
// 0x7948d0 evaluates the real SH basis functions for bands l = 0..4 and
// accumulates each one, scaled by the colour, into the matching Vector4 slot.
#include "types.h"
#include <math.h>
#include <string.h>
#include <xmmintrin.h>
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------------------
// SP::MultiplyZH<float, rw::math::vpu::Vector4>
// ---------------------------------------------------------------------------

// One entry of the sparse product table.  The three basis indices are encoded as
// the triangular numbers i*(i+1), j*(j+1), k*(k+1) in the first three signed
// bytes; the weight sits at +4 (the struct is 8 bytes, exactly like SHTriple).
struct ZHDesc { signed char i, j, k; char pad; float w; };

// One SH/ZH coefficient group (a Vector4) lives at base + index * 16 bytes.
static inline const float* zhVec(const void* base, int idx)
{
    return (const float*)((const char*)base + idx * 16);
}
static inline float* zhVecOut(void* base, int idx)
{
    return (float*)((char*)base + idx * 16);
}

// floor(sqrt(tri)): the original evaluates the square root in x87 extended
// precision (fild/fsqrt/fstp), then truncates and decrements if it rounded up.
static inline int zhBandIndex(signed char tri)
{
    float f = (float)sqrt((double)tri);
    int n = (int)f;
    if (f < (float)n)
        --n;
    return n;
}

// out[acc] += w * a[idx] * basis[idx]
static inline void zhAddDiagonal(void* out, const float* a, const char* basis,
                                 int acc, int idx, float w)
{
    __m128 v = _mm_mul_ps(_mm_set1_ps(a[idx] * w), _mm_load_ps(zhVec(basis, idx)));
    _mm_store_ps(zhVecOut(out, acc), _mm_add_ps(v, _mm_load_ps(zhVecOut(out, acc))));
}

// out[acc] += w * (a[y] * basis[x] + a[x] * basis[y])
static inline void zhAddCross(void* out, const float* a, const char* basis,
                              int acc, int x, int y, float w)
{
    __m128 v = _mm_mul_ps(_mm_set1_ps(a[y]), _mm_load_ps(zhVec(basis, x)));
    v = _mm_add_ps(v, _mm_mul_ps(_mm_set1_ps(a[x]), _mm_load_ps(zhVec(basis, y))));
    v = _mm_mul_ps(v, _mm_set1_ps(w));
    _mm_store_ps(zhVecOut(out, acc), _mm_add_ps(v, _mm_load_ps(zhVecOut(out, acc))));
}

// @ 0x00794610  SP::MultiplyZH<float, rw::math::vpu::Vector4>
void SP_MultiplyZH(int count, int a, int b, void* out, char* triples)
{
    const float* pa = (const float*)a;
    const char* pb = (const char*)b;
    char* po = (char*)out;
    memset(po, 0, count * 16);
    for (char* e = triples; *e >= 0; e += 8) {
        const ZHDesc* t = (const ZHDesc*)e;
        int i = zhBandIndex(t->i);
        int j = zhBandIndex(t->j);
        int k = zhBandIndex(t->k);
        if ((i + 1) * i != (int)t->i)
            continue;
        if ((j + 1) * j != (int)t->j)
            continue;
        if ((k + 1) * k != (int)t->k)
            continue;
        float w = t->w;
        if (i == j) {
            zhAddDiagonal(po, pa, pb, k, i, w);
            if (i == k)
                continue;
            zhAddCross(po, pa, pb, i, i, k, w);
        } else if (j == k) {
            zhAddDiagonal(po, pa, pb, i, j, w);
            zhAddCross(po, pa, pb, j, j, i, w);
        } else {
            zhAddCross(po, pa, pb, i, j, k, w);
            zhAddCross(po, pa, pb, j, i, k, w);
            zhAddCross(po, pa, pb, k, j, i, w);
        }
    }
}

// ---------------------------------------------------------------------------
// SP::AddColourSample
// ---------------------------------------------------------------------------

// Per-coefficient normalisation constants of the real SH basis (l = 0..4).
// Kept as globals so the codegen keeps the `movss xmm0,[addr] / shufps` form.
extern float kSH_Y_00;        // 0x01634100
extern float kSH_Y_1;         // 0x0163414c  (shared by the three l=1 terms)
extern float kSH_Y_2_2;       // 0x016340a4
extern float kSH_Y_2_1;       // 0x01634088
extern float kSH_Y_20;        // 0x01634058
extern float kSH_Y_21;        // 0x01634138
extern float kSH_Y_22;        // 0x0163406c
extern float kSH_Y_3_3;       // 0x01634050
extern float kSH_Y_3_2;       // 0x016340c4
extern float kSH_Y_3_1;       // 0x016340f4
extern float kSH_Y_30;        // 0x01634118
extern float kSH_Y_31;        // 0x01634060
extern float kSH_Y_32;        // 0x0163416c
extern float kSH_Y_33;        // 0x016340f0
extern float kSH_Y_4_4;       // 0x0163408c
extern float kSH_Y_4_3;       // 0x01634128
extern float kSH_Y_4_2;       // 0x016341e4
extern float kSH_Y_4_1;       // 0x01634070
extern float kSH_Y_40;        // 0x0163400c
extern float kSH_Y_41;        // 0x016340b8
extern float kSH_Y_42;        // 0x016341f0
extern float kSH_Y_43;        // 0x0163412c
extern float kSH_Y_44;        // 0x01634110

// dst += k * colour * p        (the original's constant, colour, polynomial order)
static inline void shAcc(__m128 c, float* dst, float k, __m128 p)
{
    __m128 v = _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(k), c), p);
    _mm_store_ps(dst, _mm_add_ps(v, _mm_load_ps(dst)));
}

// dst += k * colour * p * q
static inline void shAcc2(__m128 c, float* dst, float k, __m128 p, __m128 q)
{
    __m128 v = _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(_mm_set1_ps(k), c), p), q);
    _mm_store_ps(dst, _mm_add_ps(v, _mm_load_ps(dst)));
}

// @ 0x007948d0  SP::AddColourSample
void SP_AddColourSample(float* colour, int n, float* dir, float* dst)
{
    const __m128 c = _mm_load_ps(colour);
    const float x = dir[0];
    const float y = dir[1];
    const float z = dir[2];

    // l = 0
    _mm_store_ps(dst, _mm_add_ps(_mm_mul_ps(_mm_set1_ps(kSH_Y_00), c),
                                 _mm_load_ps(dst)));

    // l = 1: y, z, x
    shAcc(c, dst + 4,  kSH_Y_1, _mm_set1_ps(y));
    shAcc(c, dst + 8,  kSH_Y_1, _mm_set1_ps(z));
    shAcc(c, dst + 12, kSH_Y_1, _mm_set1_ps(x));

    const float xx = x * x;
    const float yy = y * y;
    const float zz = z * z;

    if (n < 3)
        return;

    const float xy = x * y;
    const float yz = y * z;

    // l = 2: xy, yz, 3z^2-1, xz, x^2-y^2
    shAcc(c, dst + 16, kSH_Y_2_2, _mm_set1_ps(xy));
    shAcc(c, dst + 20, kSH_Y_2_1, _mm_set1_ps(yz));
    shAcc(c, dst + 24, kSH_Y_20,  _mm_set1_ps(zz * 3.0f - 1.0f));
    const float xz = x * z;
    shAcc(c, dst + 28, kSH_Y_21,  _mm_set1_ps(xz));
    shAcc(c, dst + 32, kSH_Y_22,  _mm_set1_ps(xx - yy));

    if (n < 4)
        return;

    // l = 3: y(3x^2-y^2), xyz, y(5z^2-1), z(5z^2-3), x(5z^2-1),
    //        z(x^2-y^2), x(x^2-3y^2)
    shAcc2(c, dst + 36, kSH_Y_3_3, _mm_set1_ps(xx * 3.0f - yy), _mm_set1_ps(y));
    shAcc2(c, dst + 40, kSH_Y_3_2, _mm_set1_ps(xy), _mm_set1_ps(z));
    shAcc2(c, dst + 44, kSH_Y_3_1, _mm_set1_ps(zz * 5.0f - 1.0f), _mm_set1_ps(y));
    shAcc2(c, dst + 48, kSH_Y_30,  _mm_set1_ps(zz * 5.0f - 3.0f), _mm_set1_ps(z));
    shAcc2(c, dst + 52, kSH_Y_31,  _mm_set1_ps(zz * 5.0f - 1.0f), _mm_set1_ps(x));
    shAcc2(c, dst + 56, kSH_Y_32,  _mm_set1_ps(xx - yy),         _mm_set1_ps(z));
    shAcc2(c, dst + 60, kSH_Y_33,  _mm_set1_ps(xx - 3.0f * yy),  _mm_set1_ps(x));

    if (n < 5)
        return;

    // l = 4
    shAcc2(c, dst + 64, kSH_Y_4_4, _mm_set1_ps(xx - yy),             _mm_set1_ps(xy));
    shAcc2(c, dst + 68, kSH_Y_4_3, _mm_set1_ps(xx * 3.0f - yy),      _mm_set1_ps(yz));
    shAcc2(c, dst + 72, kSH_Y_4_2, _mm_set1_ps(zz * 7.0f - 1.0f),    _mm_set1_ps(xy));
    shAcc2(c, dst + 76, kSH_Y_4_1, _mm_set1_ps(zz * 7.0f - 3.0f),    _mm_set1_ps(yz));
    shAcc(c,  dst + 80, kSH_Y_40,  _mm_set1_ps(3.0f - zz * 30.0f + zz * zz * 35.0f));
    shAcc2(c, dst + 84, kSH_Y_41, _mm_set1_ps(zz * 7.0f - 3.0f),     _mm_set1_ps(xz));
    shAcc2(c, dst + 88, kSH_Y_42, _mm_set1_ps(zz * 7.0f - 1.0f),     _mm_set1_ps(xx - yy));
    shAcc2(c, dst + 92, kSH_Y_43, _mm_set1_ps(xx - 3.0f * yy),       _mm_set1_ps(xz));
    shAcc(c,  dst + 96, kSH_Y_44, _mm_set1_ps(xx * xx - 6.0f * xx * yy + yy * yy));
}
