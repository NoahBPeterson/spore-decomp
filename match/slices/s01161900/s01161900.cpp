// Control-point smoothing / min-max solver (6336 bytes, /O2, SSE).  FUN_01161900.
//
// Reconstructed from the disassembly.  Computes an absolute-scaled copy of the
// input point array, then per 0x20-wide window runs two interleaved chains:
//   x[k] = x[k-1]*0.997f + work[base+k]        (seeded by param_5[0])
//   c[k] = Clamp(c[k-1], x[k])                 (seeded by param_5[1])
// solves the window with FUN_01161540 and writes the result either into param_3
// (when param_1[0x4c] == 0) or param_4 (otherwise, with an optional min-accumulate
// when param_6 != 0).  Behavioural reconstruction; NOT byte-exact (see
// nonmatching.txt).

#include "../../include/types.h"
#include <math.h>
#include <string.h>
#include <xmmintrin.h>   // switches scalar float codegen to SSE
#include <emmintrin.h>

void FUN_01161540(float* in, float scale, float* a, float* out, int count);

// lazily-initialised per-axis scale factors (retail globals)
extern "C" float g_016f1720[4];   // 0x16f1720  per-axis scale factors
extern "C" int   g_016f1730;      // 0x16f1730  lazy-init flag

static const float HK_EPS = 1.000000045813705e-18f;

static float AbsEps(float v) {
    __m128 r = _mm_add_ss(_mm_set_ss(v), _mm_set_ss(HK_EPS));
    r = _mm_and_ps(r, _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff)));
    return _mm_cvtss_f32(r);
}

// @ 0x01161900
// param_1 arrives in ecx (the retail build's first-arg-in-ecx ABI): declare __fastcall with the
// register slot then a dummy edx slot so param_2..param_6 land on the stack as the original reads them.
extern "C" void __fastcall SmoothControlPoints(int param_1, int param_edx, float* param_2, int param_3,
                                    int param_4, float* param_5, int param_6) {
    (void)param_edx;

    const float* pi = (const float*)param_1; // p[0x30..0x4c] fields

    if (!(g_016f1730 & 1)) {
        g_016f1730 |= 1;
        g_016f1720[0] = g_016f1720[1] = g_016f1720[2] = g_016f1720[3] = 0.003000020980834961f;
    }

    float work[0x100];

    // scale + |.| the whole 0x100-float input block: work[j] = fabs(scale[j&3] * src[j])
    {
        float sc[4] = { g_016f1720[0], g_016f1720[1], g_016f1720[2], g_016f1720[3] };
        for (int j = 0; j < 0x100; ++j)
            work[j] = AbsEps(sc[j & 3] * param_2[j]);
    }

    const float s30 = pi[0x30 / 4];
    const float s34 = pi[0x34 / 4];
    const float s38 = pi[0x38 / 4];
    const float s44 = pi[0x44 / 4];
    const float s48 = pi[0x48 / 4];

    int base = 0;
    if (*(const unsigned char*)(param_1 + 0x4c) != 0) {
        // `param_1[0x4c] != 0` path: solve into a scratch buffer, then write param_4.
        do {
            char zb[0x7c];
            memset(zb, 0, 0x7c);
            volatile char zv = zb[0x7b];
            (void)zv;
            float xch[0x20];
            float cch[0x20];
            float solved[0x20];

            float x = *param_5;
            for (int k = 0; k < 0x20; ++k) {
                x = x * 0.997f + work[base + k];
                xch[k] = x;
            }
            float c = param_5[1];
            for (int k = 0; k < 0x20; ++k) {
                float v = xch[k];
                if (!(v > s30)) {
                    if (!(s34 <= v)) c = (c < s48) ? (c - s48) : 0.0f;
                } else if (c > s38) {
                    c = s44 + c;
                }
                cch[k] = c;
            }
            *param_5 = xch[0x1f];
            param_5[1] = cch[0x1f];

            FUN_01161540(xch, 1.0f / s30, cch, solved, 0x20);

            float* out = (float*)(param_4 + base * 4);
            if (param_6 == 0) {
                for (int i = 0; i < 0x20; ++i) out[i] = solved[i];
            } else {
                for (int i = 0; i < 0x20; ++i)
                    out[i] = (solved[i] < out[i]) ? solved[i] : out[i];
            }
            base += 0x20;
        } while (base < 0x100);
    } else {
        // `param_1[0x4c] == 0` path: solve straight into param_3.
        do {
            char zb[0x7c];
            memset(zb, 0, 0x7c);
            volatile char zv = zb[0x7b];
            (void)zv;
            float xch[0x20];
            float cch[0x20];

            float x = *param_5;
            for (int k = 0; k < 0x20; ++k) {
                x = x * 0.997f + work[base + k];
                xch[k] = x;
            }
            float c = param_5[1];
            for (int k = 0; k < 0x20; ++k) {
                float v = xch[k];
                if (!(v > s30)) {
                    if (!(s34 <= v)) c = (c < s48) ? (c - s48) : 0.0f;
                } else if (c > s38) {
                    c = s44 + c;
                }
                cch[k] = c;
            }
            *param_5 = xch[0x1f];
            param_5[1] = cch[0x1f];

            FUN_01161540(xch, 1.0f / s30, cch, (float*)(param_3 + base * 4), 0x20);
            base += 0x20;
        } while (base < 0x100);
    }
}
