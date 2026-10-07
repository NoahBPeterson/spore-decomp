// Slice s0116efb0 -- rw::audio::core::HELPER_Imdct36X4Implementation (0x0116efb0, 2478 bytes):
// EA RenderWare Audio, MPEG layer-3 36-point IMDCT with windowing for four interleaved subbands at once.
//
// Each float4 is one group of four subband lanes (float index 4*v is vector v). The aligned path
// (all of in/out/win on 16 bytes) runs the SIMD butterflies in place on `in`, two passes over the
// vectors (loop index i = 0,1 selects the second 4-vector block), then writes the 36 windowed output
// vectors. The unaligned path calls the scalar HELPER_Imdct36X1 once per lane (0x0116e4f0).
//
// Float constants are the 0x014daac0 table (bit-exact): 0.34729636, 1.5320889, 1.8793852, 0.70710677,
// 1.7320508, 0.6840403, 1.2855753, 1.9696155, 0.5019099, 0.5176381, 0.55168897, 0.61038727,
// 0.8717234, 1.1831008, 1.9318516, 5.7368565.
//
// Calling convention: cdecl (plain ret, 3 stack args). The scalar fallback calls
// HELPER_Imdct36X1 with win in ECX, out in EDX and `in` pushed; the caller pops (add esp,4).
// Declared __fastcall here, so the callee pops instead (ret 4): the same register/stack assignment
// with a different cleanup site, as in the s0116e4f0 slice.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <xmmintrin.h>

namespace rw { namespace audio { namespace core {
// 0x0116e4f0 (slice s0116e4f0): win in ECX, out in EDX, in on the stack.
void __fastcall HELPER_Imdct36X1(const float* win, float* out, float* in);
}}}

namespace {

// One group of four lanes (SSE register).
typedef __m128 F4;
__forceinline F4 operator+(const F4& a, const F4& b) { return _mm_add_ps(a, b); }
__forceinline F4 operator-(const F4& a, const F4& b) { return _mm_sub_ps(a, b); }
__forceinline F4 operator*(const F4& a, float c) { return _mm_mul_ps(a, _mm_set1_ps(c)); }

}  // namespace

namespace rw { namespace audio { namespace core {

// @ 0x0116efb0
void HELPER_Imdct36X4Implementation(float* param_1, float* param_2, float* param_3)
{
    if ((((unsigned int)param_1 | (unsigned int)param_2 | (unsigned int)param_3) & 0xf) == 0) {
        F4* P = (F4*)param_1;
#define V(f) P[(f) >> 2]

        // Stage 1: butterflies in place on the input vectors.
        F4 f50 = V(0x3c) + V(0x38);
        F4 f54 = V(0x34) + V(0x30);
        F4 f66 = V(0x2c) + V(0x28);
        V(0x44) = (V(0x44) + V(0x40)) + f50;
        V(0x40) = V(0x40) + V(0x3c);
        V(0x3c) = f50 + f54;
        V(0x38) = V(0x38) + V(0x34);
        V(0x34) = f54 + f66;
        V(0x30) = V(0x30) + V(0x2c);

        F4 g50 = V(0x24) + V(0x20);
        F4 g54 = V(0x1c) + V(0x18);
        F4 g55 = V(0x14) + V(0x10);
        V(0x2c) = f66 + g50;
        V(0x28) = V(0x28) + V(0x24);
        V(0x24) = g50 + g54;
        V(0x20) = V(0x20) + V(0x1c);
        V(0x1c) = g54 + g55;
        V(0x18) = V(0x18) + V(0x14);

        F4 h54 = V(0xc) + V(0x8);
        F4 h50 = V(0x4) + V(0x0);
        V(0x14) = g55 + h54;
        V(0x10) = V(0x10) + V(0xc);
        V(0xc) = h54 + h50;
        V(0x8) = V(0x8) + V(0x4);
        V(0x4) = h50;

        // Stage 2: two passes (i = 0, 1) over the block at vector i; results go to two-vector arrays.
        F4 A120[2], A100[2], A140[2], Ae0[2], Aa0[2], Ac0[2], A80[2], A60[2], A40[2];
        for (int i = 0; i < 2; ++i) {
            F4* b = P + i;
            F4 t0 = b[0] + b[0];
            F4 a56 = b[12] + t0;
            A120[i] = ((b[4] * 1.8793852f + a56) + b[8] * 1.5320889f) + b[16] * 0.34729636f;
            A40[i] = (((b[4] + t0) - b[8]) - (b[12] + b[12])) - b[16];
            A100[i] = ((b[16] * 1.5320889f + a56) - b[4] * 0.34729636f) - b[8] * 1.8793852f;
            A140[i] = ((b[8] * 0.34729636f + a56) - b[4] * 1.5320889f) - b[16] * 1.8793852f;
            F4 t5 = ((b[0] - b[4]) - b[12]) + (b[8] + b[16]);
            if (i != 0) t5 = t5 * 0.70710677f;
            Ae0[i] = t5;
            F4 t6 = b[6] * 1.7320508f;
            Aa0[i] = (b[2] * 1.9696155f + t6) + (b[10] * 1.2855753f + b[14] * 0.6840403f);
            A60[i] = ((b[2] - b[10]) - b[14]) * 1.7320508f;
            Ac0[i] = (b[2] * 1.2855753f + b[14] * 1.9696155f) - (b[10] * 0.6840403f + t6);
            A80[i] = (b[2] * 0.6840403f + b[10] * 1.9696155f) - (b[14] * 1.2855753f + t6);
        }

        // Stage 3: combine the two passes (sum/difference groups, each scaled by its cosine constant).
        F4 t18 = (A120[1] + Aa0[1]) * 0.5019099f;
        F4 s18 = A120[0] + Aa0[0];
        F4 f54b = s18 + t18;
        F4 d18 = s18 - t18;
        F4 t19 = (A40[1] + A60[1]) * 0.5176381f;
        F4 s19 = A40[0] + A60[0];
        F4 f57 = s19 + t19;
        F4 d19 = s19 - t19;
        F4 t20 = (A100[1] + Ac0[1]) * 0.55168897f;
        F4 s20 = A100[0] + Ac0[0];
        F4 f60 = s20 + t20;
        F4 d20 = s20 - t20;
        F4 t21 = (A140[1] + A80[1]) * 0.61038727f;
        F4 s21 = A140[0] + A80[0];
        F4 f63 = s21 + t21;
        F4 d21 = s21 - t21;
        F4 t22 = (A140[1] - A80[1]) * 0.8717234f;
        F4 s22 = A140[0] - A80[0];
        F4 f55 = s22 + t22;
        F4 d22 = s22 - t22;
        F4 t23 = (A100[1] - Ac0[1]) * 1.1831008f;
        F4 s23 = A100[0] - Ac0[0];
        F4 f58 = s23 + t23;
        F4 d23 = s23 - t23;
        F4 t24 = (A40[1] - A60[1]) * 1.9318516f;
        F4 s24 = A40[0] - A60[0];
        F4 f61 = s24 + t24;
        F4 d24 = s24 - t24;
        F4 t25 = (A120[1] - Aa0[1]) * 5.7368565f;
        F4 s25 = A120[0] - Aa0[0];
        F4 f64 = s25 + t25;
        F4 d25 = s25 - t25;
        F4 e4 = Ae0[0] - Ae0[1];
        F4 e8 = Ae0[0] + Ae0[1];

        // Stage 4: window each output vector by its scalar window value (broadcast).
        F4* O = (F4*)param_2;
        O[0] = d25 * param_3[0];
        O[1] = d24 * param_3[1];
        O[2] = d23 * param_3[2];
        O[3] = d22 * param_3[3];
        O[4] = e4 * param_3[4];
        O[5] = d21 * param_3[5];
        O[6] = d20 * param_3[6];
        O[7] = d19 * param_3[7];
        O[8] = d18 * param_3[8];
        O[9] = d18 * param_3[9];
        O[10] = d19 * param_3[10];
        O[11] = d20 * param_3[11];
        O[12] = d21 * param_3[12];
        O[13] = e4 * param_3[13];
        O[14] = d22 * param_3[14];
        O[15] = d23 * param_3[15];
        O[16] = d24 * param_3[16];
        O[17] = d25 * param_3[17];
        O[18] = f64 * param_3[18];
        O[19] = f61 * param_3[19];
        O[20] = f58 * param_3[20];
        O[21] = f55 * param_3[21];
        O[22] = e8 * param_3[22];
        O[23] = f63 * param_3[23];
        O[24] = f60 * param_3[24];
        O[25] = f57 * param_3[25];
        O[26] = f54b * param_3[26];
        O[27] = f54b * param_3[27];
        O[28] = f57 * param_3[28];
        O[29] = f60 * param_3[29];
        O[30] = f63 * param_3[30];
        O[31] = e8 * param_3[31];
        O[32] = f55 * param_3[32];
        O[33] = f58 * param_3[33];
        O[34] = f61 * param_3[34];
        O[35] = f64 * param_3[35];
#undef V
        return;
    }

    // Unaligned: one scalar 36-point IMDCT per lane.
    for (int k = 0; k < 4; ++k)
        HELPER_Imdct36X1(param_3, param_2 + k, param_1 + k);
}

}}}  // namespace rw::audio::core
