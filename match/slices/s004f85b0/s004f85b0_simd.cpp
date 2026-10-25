// w1g1 slice s004f85b0 -- the two SIMD evaluators, kept apart from the scalar source
// because they use integer SIMD (cvttps2dq/packssdw/pmaddwd) while the rest of the module
// is plain SSE1.  /Od /Ob1 /MD /Gy /TP /arch:SSE2 /fp:fast (no /EHsc).
#include "s004f85b0.h"
#include <xmmintrin.h>
#include <emmintrin.h>

extern const float g_150ca80[4];    // 0x0150ca80  4 x 1.0f
extern const short g_150ca90[8];    // 0x0150ca90  {256, 32, 4, 0, ...}  grid cell strides

// ===========================================================================
// @ 0x004f90a0
// SSE2 evaluator (chosen when the CPU reports SIMD level >= 2): sum the four
// lanes of every block in the point's bucket.
// ===========================================================================
float* ForceGrid::FUN_004f90a0(const float* point, float* out)
{
    const float* origin = (const float*)mpGridOrigin;
    const float* scale  = (const float*)mpGridScale;
    SphereFields** buckets = mppBuckets;

    __m128 p = _mm_loadu_ps(point);
    __m128 p1 = p;
    p = _mm_mul_ps(_mm_sub_ps(p, _mm_load_ps(origin)), _mm_load_ps(scale));

    __m128i idx = _mm_cvttps_epi32(p);
    __m128i k = _mm_load_si128((const __m128i*)g_150ca90);
    idx = _mm_packs_epi32(idx, idx);
    idx = _mm_madd_epi16(idx, k);
    int lo = _mm_cvtsi128_si32(idx);
    int hi = _mm_extract_epi16(idx, 2);
    SphereFields* e = *(SphereFields**)((char*)buckets + lo + hi);

    __m128 sum = _mm_set_ss(mfNegCost);
    if (e != 0) {
        uint32_t n = *(uint32_t*)((char*)e - 8);
        __m128 px = _mm_shuffle_ps(p1, p1, 0);
        __m128 py = _mm_shuffle_ps(p1, p1, 0x55);
        __m128 pz = _mm_shuffle_ps(p1, p1, 0xaa);
        __m128 one = _mm_load_ps(g_150ca80);
        do {
            __m128 d = _mm_sub_ps(_mm_load_ps(e->mX), px);
            d = _mm_mul_ps(d, d);
            __m128 d2 = _mm_sub_ps(_mm_load_ps(e->mY), py);
            d2 = _mm_mul_ps(d2, d2);
            d = _mm_add_ps(d, d2);
            __m128 d3 = _mm_sub_ps(_mm_load_ps(e->mZ), pz);
            d3 = _mm_mul_ps(d3, d3);
            d = _mm_add_ps(d, d3);

            __m128 mask = _mm_cmplt_ps(d, _mm_load_ps(e->mRadiusSq));
            __m128 t = _mm_mul_ps(d, _mm_load_ps(e->mInvRadiusSq));
            t = _mm_sub_ps(t, one);
            t = _mm_mul_ps(t, t);
            t = _mm_mul_ps(t, t);
            t = _mm_mul_ps(t, _mm_load_ps(e->mStrength));
            t = _mm_and_ps(t, mask);
            sum = _mm_add_ps(sum, t);

            e = (SphereFields*)((char*)e + 0x80);
            n--;
        } while (n != 0);
        sum = _mm_add_ps(sum, _mm_shuffle_ps(sum, sum, 0x1b));
        sum = _mm_add_ss(sum, _mm_shuffle_ps(sum, sum, 0xb1));
    }
    *out = _mm_cvtss_f32(sum);
    return out;
}

// ===========================================================================
// @ 0x004f9180
// SSE1 evaluator (chosen when the CPU reports SIMD level == 1).  With no block
// at the point the result is just the negated cost.
// ===========================================================================
void ForceGrid::FUN_004f9180(const float* point, float* out)
{
    SphereFields* e = FUN_004f8f70(point);
    if (e == 0) {
        *out = mfNegCost;
        return;
    }

    __m128 p = _mm_loadu_ps(point);
    __m128 sum = _mm_set_ss(mfNegCost);
    uint32_t n = *(uint32_t*)((char*)e - 8);
    __m128 px = _mm_shuffle_ps(p, p, 0);
    __m128 py = _mm_shuffle_ps(p, p, 0x55);
    __m128 pz = _mm_shuffle_ps(p, p, 0xaa);
    __m128 one = _mm_load_ps(g_150ca80);
    do {
        __m128 d = _mm_sub_ps(_mm_load_ps(e->mX), px);
        d = _mm_mul_ps(d, d);
        __m128 d2 = _mm_sub_ps(_mm_load_ps(e->mY), py);
        d2 = _mm_mul_ps(d2, d2);
        d = _mm_add_ps(d, d2);
        __m128 d3 = _mm_sub_ps(_mm_load_ps(e->mZ), pz);
        d3 = _mm_mul_ps(d3, d3);
        d = _mm_add_ps(d, d3);

        __m128 mask = _mm_cmplt_ps(d, _mm_load_ps(e->mRadiusSq));
        __m128 t = _mm_mul_ps(d, _mm_load_ps(e->mInvRadiusSq));
        t = _mm_sub_ps(t, one);
        t = _mm_mul_ps(t, t);
        t = _mm_mul_ps(t, t);
        t = _mm_mul_ps(t, _mm_load_ps(e->mStrength));
        t = _mm_and_ps(t, mask);
        sum = _mm_add_ps(sum, t);

        e = (SphereFields*)((char*)e + 0x80);
        n--;
    } while (n != 0);

    __m128 t = _mm_movehl_ps(sum, sum);
    sum = _mm_add_ps(sum, t);
    t = sum;
    t = _mm_shuffle_ps(t, t, 1);
    sum = _mm_add_ss(sum, t);
    *out = _mm_cvtss_f32(sum);
}
