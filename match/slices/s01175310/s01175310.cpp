// Slice s01175310: one frame decode of the RenderWare/EATech speech codec (LPC vocoder), @ 0x01175310.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// The voice state at `v` holds a little-endian bit reader (+0 read pointer, +4 bit buffer, +8 bit count) and
// the previous frame's 12 reflection (PARCOR) coefficients at +0x114. One frame:
//   * 12 quantised reflection coefficients (4 x 6 bits, then 8 x 5 bits) are looked up in a shared table
//     (the 5-bit ones use the upper half, tab+16) and turned into per-quarter deltas ((q - old) * 0.25);
//   * 4 sub-frames of 108 samples: each reads an 8-bit lag (pos - lag selects the pitch source in the history
//     ring), a 4-bit pitch gain (x 1/15) and a 6-bit excitation gain, then decodes the excitation
//     (0x011741c0: algebraic pulses, stride 1, or stride 2 with a 2-bit pulse offset/interpolation selector)
//     and mixes excitation * gain + history[lag] * pitchGain into the output;
//   * the 12 coefficients are advanced by one delta each quarter and the all-pole filter LpcSynthesize
//     (0x011746c0) runs over the output after every step (offsets 0, 12, 24, 36; the last one covers the rest);
//   * finally the last 324 output samples are moved into the history ring (memmove).
#include "types.h"

struct LpcVoice {
    const unsigned char* p;                  // +0x000 bit reader: read pointer
    unsigned int buf;                        // +0x004 bit buffer
    int cnt;                                 // +0x008 valid bit count
    int mode;                                // +0x00c 0: dense excitation, else sparse (stride 2)
    int thresh;                              // +0x010 first-index threshold selecting the excitation codebook
    float gain[64];                          // +0x014 excitation gain table
    float refl[12];                          // +0x114 reflection coefficients (interpolated per quarter)
    float hist[12];                          // +0x144 synthesis filter history (circular)
    float ring[324];                         // +0x174 history ring (0x510 bytes), directly followed by out[]
    float out[432];                          // +0x684 excitation in / speech out, in place
};

extern "C" void* (__cdecl* _imp__memcpy)(void*, const void*, unsigned int);   // IAT 0x015c3848 (msvcr90 memcpy)
extern unsigned int g_bitMask[];             // 0x015c4b74: g_bitMask[n] = (1 << n) - 1
extern float g_quantTab[];                   // 0x015c4b98: reflection quantiser table (64 entries)
extern "C" void __cdecl FUN_011741c0(LpcVoice* v, int sparse, float* out, int stride);   // excitation decode

// helper at 0x01174420 (static, refl in ECX, a in EDI)
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

// helper at 0x011746c0 (static: voice in ESI, offset in EAX, numBlocks on the stack)
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


static __forceinline unsigned ReadBits(LpcVoice* v, int n)
{
    unsigned r = v->buf & g_bitMask[n];
    v->cnt -= n;
    int c = v->cnt;
    unsigned rest = v->buf >> n;
    v->buf = rest;
    if (c < 8) {
        const unsigned char* q = v->p;
        unsigned b = *q;
        v->p = q + 1;
        v->buf = (b << c) | rest;
        v->cnt = c + 8;
    }
    return r;
}

#define DELTA6(k) { unsigned i = ReadBits(v, 6); d[k] = (g_quantTab[i] - v->refl[k]) * 0.25f; }
#define DELTA5(k) { unsigned i = ReadBits(v, 5); d[k] = (g_quantTab[16 + i] - v->refl[k]) * 0.25f; }
#define ADD6(k) { v->refl[(k) + 0] = d[(k) + 0] + v->refl[(k) + 0]; v->refl[(k) + 1] = d[(k) + 1] + v->refl[(k) + 1]; \
                  v->refl[(k) + 2] = d[(k) + 2] + v->refl[(k) + 2]; v->refl[(k) + 3] = d[(k) + 3] + v->refl[(k) + 3]; \
                  v->refl[(k) + 4] = d[(k) + 4] + v->refl[(k) + 4]; v->refl[(k) + 5] = d[(k) + 5] + v->refl[(k) + 5]; }

// @ 0x01175310
namespace SpeechCodec { void DecodeFrame(LpcVoice* v);
void DecodeFrame(LpcVoice* v)
{
    float d[12];
    int sparseSel;
    {
        unsigned i0 = ReadBits(v, 6);
        sparseSel = (int)i0 < v->thresh;
        d[0] = (g_quantTab[i0] - v->refl[0]) * 0.25f;
    }
    DELTA6(1) DELTA6(2) DELTA6(3)
    DELTA5(4) DELTA5(5) DELTA5(6) DELTA5(7) DELTA5(8) DELTA5(9) DELTA5(10) DELTA5(11)

    const float c1 = 0.018032679f, c2 = 0.11459156f, c3 = 0.59738594f;
    float work[5 + 108 + 5];
    float* buf = work + 5;
    float* dst = v->out;

    for (int pos = 0xd8; pos < 0x288; pos += 0x6c) {
        int base = pos - (int)ReadBits(v, 8);
        float mix = (float)ReadBits(v, 4) * 0.06666667f;
        float gain = v->gain[ReadBits(v, 6)];

        if (v->mode == 0) {
            FUN_011741c0(v, sparseSel, buf, 1);
        } else {
            unsigned off = ReadBits(v, 1);
            unsigned zero = ReadBits(v, 1);
            FUN_011741c0(v, sparseSel, buf + off, 2);
            if (zero == 0) {
                for (int k = 0; k < 5; k++) { work[k] = 0.0f; work[113 + k] = 0.0f; }
                float* q = buf + (6 - off);
                for (int n = 0x36; n != 0; n--) {
                    q[-5] = ((q[-10] + q[0]) * c1 - (q[-8] + q[-2]) * c2) + (q[-6] + q[-4]) * c3;
                    q += 2;
                }
                gain = gain * 0.5f;
            } else {
                float* q = buf + (1 - off);
                for (int n = 0x36; n != 0; n--) { *q = 0.0f; q += 2; }
            }
        }

        const float* src = v->ring + base;
        for (int j = 0; j < 0x6c; j += 9) {
            dst[0] = buf[j + 0] * gain + src[j + 0] * mix;
            dst[1] = buf[j + 1] * gain + src[j + 1] * mix;
            dst[2] = buf[j + 2] * gain + src[j + 2] * mix;
            dst[3] = buf[j + 3] * gain + src[j + 3] * mix;
            dst[4] = buf[j + 4] * gain + src[j + 4] * mix;
            dst[5] = buf[j + 5] * gain + src[j + 5] * mix;
            dst[6] = buf[j + 6] * gain + src[j + 6] * mix;
            dst[7] = buf[j + 7] * gain + src[j + 7] * mix;
            dst[8] = buf[j + 8] * gain + src[j + 8] * mix;
            dst += 9;
        }
    }

    _imp__memcpy(v->ring, &v->out[108], 0x510);
    for (int k = 0; k < 12; k += 6) ADD6(k)
    LpcSynthesize(v, 0, 1);
    for (int k = 0; k < 12; k += 6) ADD6(k)
    LpcSynthesize(v, 12, 1);
    for (int k = 0; k < 12; k += 6) ADD6(k)
    LpcSynthesize(v, 24, 1);
    for (int k = 0; k < 12; k += 6) ADD6(k)
    LpcSynthesize(v, 36, 0x21);
}
} // namespace SpeechCodec
