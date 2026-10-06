// Control-point smoothing / min-max solver  @ 0x01161900  (6336 bytes, /O2, SSE).
//
// Reconstructed from the Ghidra decompile.  Computes an absolute-scaled copy of the
// input point array, then iteratively smooths it (factor 0.997), solves each 0x20-wide
// window with FUN_01161540 and either writes the solution into param_4 or keeps a
// running min/max when param_6 selects that path.  Behavioural reconstruction; NOT
// byte-exact (see nonmatching.txt/Its working array and the two solve calls are the
// parts most likely to drift from retail).

#include "../../include/types.h"
#include <math.h>

void FUN_01161540(float* in, float scale, float* a, float* out, int count);

// lazily-initialised per-axis scale factors
static float s_scale[4];
static int   s_scaleInit;

static float AbsEps(float v) {
    float r = v + 1e-18f;
    return r < 0.0f ? -r : r;
}

// @ 0x01161900
extern "C" void SmoothControlPoints(int param_1, float* param_2, int param_3,
                                    int param_4, float* param_5, int param_6) {
    if (!(s_scaleInit & 1)) {
        s_scaleInit |= 1;
        s_scale[0] = s_scale[1] = s_scale[2] = s_scale[3] = 0.003000021f;
    }

    float work[0x130 + 0x20];
    int   n = 0;

    // scale + |.| the first 12 blocks of 0x14 floats, then the tail
    {
        float s0 = s_scale[0], s1 = s_scale[1], s2 = s_scale[2], s3 = s_scale[3];
        float a = s0 * param_2[0], b = s1 * param_2[1], c = s2 * param_2[2], d = s3 * param_2[3];
        float e = s0 * param_2[4], f = s1 * param_2[5], g = s2 * param_2[6], h = s3 * param_2[7];
        int   blk = 0xc;
        float* src = param_2;
        float* dst = work;
        do {
            float v8 = src[8], v9 = src[9], v10 = src[10], v11 = src[11];
            float v12 = src[0xc], v13 = src[0xd], v14 = src[0xe], v15 = src[0xf];
            dst[0] = AbsEps(a); dst[1] = AbsEps(b); dst[2] = AbsEps(c); dst[3] = AbsEps(d);
            float v16 = src[0x10], v17 = src[0x11], v18 = src[0x12], v19 = src[0x13];
            dst[4] = AbsEps(e); dst[5] = AbsEps(f); dst[6] = AbsEps(g); dst[7] = AbsEps(h);
            dst[8]  = AbsEps(s0 * v8);  dst[9]  = AbsEps(s1 * v9);
            dst[10] = AbsEps(s2 * v10); dst[0xb] = AbsEps(s3 * v11);
            dst[0xc] = AbsEps(s0 * v12); dst[0xd] = AbsEps(s1 * v13);
            dst[0xe] = AbsEps(s2 * v14); dst[0xf] = AbsEps(s3 * v15);
            a = s0 * src[0x14]; b = s1 * src[0x15]; c = s2 * src[0x16]; d = s3 * src[0x17];
            dst[0x10] = AbsEps(s0 * v16); dst[0x11] = AbsEps(s1 * v17);
            dst[0x12] = AbsEps(s2 * v18); dst[0x13] = AbsEps(s3 * v19);
            e = s0 * src[0x18]; f = s1 * src[0x19]; g = s2 * src[0x1a]; h = s3 * src[0x1b];
            src += 0x14;
            dst += 0x14;
        } while (--blk != 0);
        for (int i = 0; i < 8; ++i) {
            dst[0x14 + i] = AbsEps((i & 1) == 0 ? s0 * src[0x1c + i] : s1 * src[0x1c + i]);
        }
    }

    int base = 0;
    do {
        // smoothing pass: v = v*0.997 + input, seeded from param_5
        float acc = (*param_5 * 0.997f + work[base]);
        work[0x104] = acc;
        work[0x105] = work[0x104] * 0.997f + work[base + 1];
        work[0x106] = work[0x105] * 0.997f + work[base + 2];

        // running min/max over the window
        float lo = work[0x104], hi = work[0x104];
        for (int i = 0; i < 0x20; ++i) {
            float v = work[base + i];
            if (v < lo) lo = v;
            if (v > hi) hi = v;
        }
        (void)lo; (void)hi;

        // solve this window
        float solved[0x20];
        FUN_01161540(work + 0x104, 1.0f / *(float*)(param_1 + 0x30), &work[0x104], solved, 0x20);

        float* out = (float*)(param_4 + base * 4);
        if (param_6 == 0) {
            for (int i = 0; i < 0xb; ++i) out[i] = solved[i];
        } else {
            // component-wise max of solved vs the accumulated window
            for (int i = 0; i < 0x20; i += 8)
                for (int j = 0; j < 8; ++j)
                    out[i + j] = solved[i + j] < work[base + i + j] ? work[base + i + j]
                                                                    : solved[i + j];
        }
        *param_5 = solved[0];
        param_5[1] = solved[1];

        base += 0x20;
    } while (base < 0x100);
}
