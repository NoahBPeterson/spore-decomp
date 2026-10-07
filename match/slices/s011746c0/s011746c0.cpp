// Slice s011746c0: 12th-order LPC (all-pole) synthesis filter of the RenderWare/EATech audio
// speech decoder region (next to the rw::audio::core MPEG decoder).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// The decoder interpolates 12 reflection (PARCOR) coefficients at voice+0x114, then calls
// LpcSynthesize(voice, sub * 12, 1) for each 12-sample sub-block (callers at 0x01175afd,
// 0x01175b80, 0x01175c00, 0x01175c80). LpcSynthesize converts the reflection coefficients to
// direct-form predictor coefficients (ReflectionToLpc, 0x01174420) and runs the all-pole filter
// in place over out[]: y[n] = x[n] + sum_k a[k] * y[n-1-k], with the 12-sample history kept as a
// circular buffer (hist[]) that one fully written-out block of 12 steps walks once around.
//
// Both functions are TU-local (static) with cl's register convention: LpcSynthesize takes the
// voice in ESI and the sample offset in EAX (block count on the stack), ReflectionToLpc takes the
// coefficients in ECX and the output in EDI. The stand-in caller at the bottom makes cl emit them
// with the same conventions. ReflectionToLpc (0x01174420) is not a VA of this slice; its real body
// is here because the convention of the call in LpcSynthesize depends on it (it matches too).
#include "types.h"

struct LpcVoice {
    uint32_t pad000[0x114 / 4];
    float refl[12];                          // +0x114 reflection coefficients (interpolated per sub-block)
    float hist[12];                          // +0x144 synthesis filter history (circular)
    uint32_t pad174[(0x684 - 0x174) / 4];
    float out[1];                            // +0x684 excitation in / speech out, in place
};

// @ 0x01174420 (not in this slice; static helper, refl in ECX, a in EDI)
// Step-up recursion done by running the lattice: T holds the backward lattice state, U the
// successive lattice outputs, a[] the resulting predictor coefficients.
static void ReflectionToLpc(const float* r, float* a)
{
    float T[12];
    float U[12];
    for (int k = 10; k >= 0; k--) T[k + 1] = r[k];
    T[0] = 1.0f;
    for (int i = 0; i < 12; i++) {
        float e = -(r[11] * T[11]);
        for (int k = 10; k >= 0; k--) {
            e -= r[k] * T[k];
            T[k + 1] = r[k] * e + T[k];
        }
        T[0] = e;
        U[i] = e;
        for (int j = 0; j < i; j++) e -= a[j] * U[i - 1 - j];
        a[i] = e;
    }
}

// One output sample j of a 12-sample block: coefficient a[(k + j) % 12] pairs with history
// slot k, and the new sample overwrites slot 11 - j (the oldest one).
#define LPC_TAP(k, j) a[((k) + (j)) % 12] * v->hist[k]
#define LPC_STEP(j)                                                                        \
    {                                                                                      \
        float y = p[j] + LPC_TAP(0, j) + LPC_TAP(1, j) + LPC_TAP(2, j) + LPC_TAP(3, j)     \
                  + LPC_TAP(4, j) + LPC_TAP(5, j) + LPC_TAP(6, j) + LPC_TAP(7, j)          \
                  + LPC_TAP(8, j) + LPC_TAP(9, j) + LPC_TAP(10, j) + LPC_TAP(11, j);       \
        v->hist[11 - (j)] = y;                                                             \
        p[j] = y;                                                                          \
    }

// @ 0x011746c0 (static: voice in ESI, offset in EAX, numBlocks on the stack)
static void LpcSynthesize(LpcVoice* v, int offset, int numBlocks)
{
    float a[12];
    float* p = &v->out[offset];
    ReflectionToLpc(v->refl, a);
    for (int i = 0; i < numBlocks; i++) {
        LPC_STEP(0) LPC_STEP(1) LPC_STEP(2) LPC_STEP(3) LPC_STEP(4) LPC_STEP(5)
        LPC_STEP(6) LPC_STEP(7) LPC_STEP(8) LPC_STEP(9) LPC_STEP(10) LPC_STEP(11)
        p += 12;
    }
}

// Stand-in for the decoder's sub-block loop (0x01175afd...), only so that cl emits the static
// functions above with the original register conventions.
void s011746c0_LpcSynthesizeCaller(LpcVoice* v, int offset, int numBlocks)
{
    LpcSynthesize(v, offset, numBlocks);
    LpcSynthesize(v, offset + 12, numBlocks);
}
