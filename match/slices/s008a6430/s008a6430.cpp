// Least-squares endpoint fit for a 565 colour block (BC1-style): finds two endpoint colours
// (weights a[] and b[] per sample) quantised to 5/6/5 bits, and returns the weighted error.
#include "types.h"
#include <math.h>

struct ColorFit {
    uint32_t pad0;
    int**    pCount;       // 0x04: **pCount = sample count
    uint32_t pad1[4];      // 0x08
    float    v[112];       // 0x18: samples, 3 floats each (stride 12)
    float    wx, wy, wz;   // 0x1d8..0x1e0: per-channel error weights
    float    a[16];        // 0x1e4
    float    b[16];        // 0x224
    float    kx, ky, kz;   // 0x264..0x26c: per-channel constant error terms
    float    __thiscall Fit(float* outA, float* outB);
};

static inline float clamp01(float x) { return x <= 0.0f ? 0.0f : (1.0f <= x ? 1.0f : x); }

// @ 0x008A6430
float ColorFit::Fit(float* outA, float* outB)
{
    int n = **pCount;
    int i = 0;
    float sAA0 = 0, sAA1 = 0, sBB0 = 0, sBB1 = 0, sAB0 = 0, sAB1 = 0;
    float xa0 = 0, xa1 = 0, xa2 = 0, xb0 = 0, xb1 = 0, xb2 = 0;
    float tAA = 0, tBB = 0, tAB = 0;

    if (n > 1) {
        int cnt = ((n - 2) >> 1) + 1;
        i = cnt * 2;
        const float* p = &v[0];
        const float* pa = &a[0];
        const float* pb = &b[0];
        do {
            float a0 = pa[0], b0 = pb[0];
            float a1 = pa[1], b1 = pb[1];
            sAA0 = a0 * a0 + sAA0;
            sBB0 = b0 * b0 + sBB0;
            sAB0 = b0 * a0 + sAB0;
            sAA1 = a1 * a1 + sAA1;
            sBB1 = b1 * b1 + sBB1;
            sAB1 = b1 * a1 + sAB1;
            xa0 = p[3] * a1 + (p[0] * a0 + xa0);
            xa1 = p[4] * a1 + (p[1] * a0 + xa1);
            xa2 = p[5] * a1 + (p[2] * a0 + xa2);
            xb0 = p[3] * b1 + (p[0] * b0 + xb0);
            xb1 = p[4] * b1 + (p[1] * b0 + xb1);
            xb2 = p[5] * b1 + (p[2] * b0 + xb2);
            p += 6; pa += 2; pb += 2;
        } while (--cnt != 0);
    }
    if (i < n) {
        float a0 = a[i], b0 = b[i];
        const float* p = &v[i * 3];
        tAA = a0 * a0;
        tBB = b0 * b0;
        tAB = b0 * a0;
        xa0 = p[0] * a0 + xa0;
        xa1 = p[1] * a0 + xa1;
        xa2 = p[2] * a0 + xa2;
        xb0 = p[0] * b0 + xb0;
        xb1 = p[1] * b0 + xb1;
        xb2 = p[2] * b0 + xb2;
    }
    float sBB = (sBB0 + sBB1) + tBB;
    float sAB = (sAB0 + sAB1) + tAB;
    float sAA = (sAA0 + sAA1) + tAA;

    float ca0, ca1, ca2, cb0, cb1, cb2;
    if (sBB == 0.0f) {
        float inv = 1.0f / sAA;
        ca0 = inv * xa0; ca1 = xa1 * inv; ca2 = xa2 * inv;
        cb0 = 0.0f; cb1 = 0.0f; cb2 = 0.0f;
    } else if (sAA == 0.0f) {
        float inv = 1.0f / sBB;
        ca0 = 0.0f; ca1 = 0.0f; ca2 = 0.0f;
        cb0 = inv * xb0; cb1 = xb1 * inv; cb2 = xb2 * inv;
    } else {
        float inv = 1.0f / (sBB * sAA - sAB * sAB);
        ca0 = (xa0 * sBB - xb0 * sAB) * inv;
        ca1 = (xa1 * sBB - xb1 * sAB) * inv;
        ca2 = (xa2 * sBB - xb2 * sAB) * inv;
        cb0 = (xb0 * sAA - xa0 * sAB) * inv;
        cb1 = (xb1 * sAA - xa1 * sAB) * inv;
        cb2 = (xb2 * sAA - xa2 * sAB) * inv;
    }

    float qa0 = clamp01(ca0), qa1 = clamp01(ca1), qa2 = clamp01(ca2);
    float qb0 = clamp01(cb0), qb1 = clamp01(cb1), qb2 = clamp01(cb2);

    float ra0 = (float)floor((double)(qa0 * 31.0f + 0.5f)) * (1.0f / 31.0f);
    float ra1 = (float)floor((double)(qa1 * 63.0f + 0.5f)) * (1.0f / 63.0f);
    float ra2 = (float)floor((double)(qa2 * 31.0f + 0.5f)) * (1.0f / 31.0f);
    float rb0 = (float)floor((double)(qb0 * 31.0f + 0.5f)) * (1.0f / 31.0f);
    float rb1 = (float)floor((double)(qb1 * 63.0f + 0.5f)) * (1.0f / 63.0f);
    float rb2 = (float)floor((double)(qb2 * 31.0f + 0.5f)) * (1.0f / 31.0f);

    outA[0] = ra0; outA[1] = ra1; outA[2] = ra2;
    outB[0] = rb0; outB[1] = rb1; outB[2] = rb2;

    return wz * ((kz + ((ra2 * ra2) * sAA + (rb2 * rb2) * sBB))
                 + (((ra2 * rb2) * sAB - ra2 * xa2) - rb2 * xb2) * 2.0f)
         + wy * ((ky + ((ra1 * ra1) * sAA + (rb1 * rb1) * sBB))
                 + (((ra1 * rb1) * sAB - ra1 * xa1) - rb1 * xb1) * 2.0f)
         + ((((ra0 * ra0) * sAA + (rb0 * rb0) * sBB) + kx)
                 + (((rb0 * ra0) * sAB - ra0 * xa0) - rb0 * xb0) * 2.0f) * wx;
}
