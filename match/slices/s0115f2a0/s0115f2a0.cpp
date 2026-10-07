// Slice s0115f2a0: rw::audio::core radix-2 complex FFT, in place, scaled by 1/N.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar math, 16-byte aligned frame).
//
// The original's middle passes (the 4-wide butterflies on the SoA scratch buffer) are an
// inline __asm block (movaps against aligned locals, `sub edi,N; cmp edi,0; jne`,
// `push eax; mul dword ptr [..]; pop eax`).  They are written here with SSE intrinsics
// that perform the same per-lane operations in the same order (bitwise identical
// results), so this function is complete but cannot be byte-exact.
#include "types.h"
#include <xmmintrin.h>

namespace rw { namespace audio { namespace core {
class System {
 public:
    void* Alloc(uint32_t size, const char* name, uint32_t align, uint32_t flags);  // 0x0112c820
    void  Free(void* p, uint32_t flags);                                             // 0x0112c850
};
}}}  // namespace rw::audio::core

extern rw::audio::core::System* gAudioSystem;  // 0x016e61a8

// Precomputed tables live behind the header; the offsets are relative to the header.
struct FftTable {
    int log2n;          // +0x00
    int unk04;          // +0x04
    int unk08;          // +0x08
    int cosOffset;      // +0x0c  float cos[]
    int sinOffset;      // +0x10  float sin[]
    int bitrevOffset;   // +0x14  int   bitrev[]
};

// ---- 4-wide butterflies on the scratch buffer (each complex = re4, im4) ---------------
static inline void Bfly(float* a, float* b)
{
    __m128 a0 = _mm_load_ps(a), a1 = _mm_load_ps(a + 4);
    __m128 b0 = _mm_load_ps(b), b1 = _mm_load_ps(b + 4);
    _mm_store_ps(a,     _mm_add_ps(a0, b0));
    _mm_store_ps(a + 4, _mm_add_ps(a1, b1));
    _mm_store_ps(b,     _mm_sub_ps(a0, b0));
    _mm_store_ps(b + 4, _mm_sub_ps(a1, b1));
}

static inline void BflyScaled(float* a, float* b, __m128 s)
{
    __m128 a0 = _mm_load_ps(a), a1 = _mm_load_ps(a + 4);
    __m128 b0 = _mm_load_ps(b), b1 = _mm_load_ps(b + 4);
    __m128 r0 = _mm_add_ps(a0, b0), r1 = _mm_add_ps(a1, b1);
    __m128 r2 = _mm_sub_ps(a0, b0), r3 = _mm_sub_ps(a1, b1);
    _mm_store_ps(a,     _mm_mul_ps(r0, s));
    _mm_store_ps(a + 4, _mm_mul_ps(r1, s));
    _mm_store_ps(b,     _mm_mul_ps(r2, s));
    _mm_store_ps(b + 4, _mm_mul_ps(r3, s));
}

// twiddle -j
static inline void BflyJ(float* a, float* b)
{
    __m128 a0 = _mm_load_ps(a), a1 = _mm_load_ps(a + 4);
    __m128 b0 = _mm_load_ps(b), b1 = _mm_load_ps(b + 4);
    _mm_store_ps(a,     _mm_sub_ps(a0, b1));
    _mm_store_ps(a + 4, _mm_add_ps(a1, b0));
    _mm_store_ps(b,     _mm_add_ps(a0, b1));
    _mm_store_ps(b + 4, _mm_sub_ps(a1, b0));
}

// twiddle (1 - j) * sqrt(1/2)
static inline void BflyR1(float* a, float* b, __m128 r)
{
    __m128 a0 = _mm_load_ps(a), a1 = _mm_load_ps(a + 4);
    __m128 x = _mm_mul_ps(_mm_load_ps(b), r);
    __m128 y = _mm_mul_ps(_mm_load_ps(b + 4), r);
    __m128 t0 = _mm_sub_ps(x, y);
    __m128 t1 = _mm_add_ps(x, y);
    _mm_store_ps(a,     _mm_add_ps(a0, t0));
    _mm_store_ps(a + 4, _mm_add_ps(a1, t1));
    _mm_store_ps(b,     _mm_sub_ps(a0, t0));
    _mm_store_ps(b + 4, _mm_sub_ps(a1, t1));
}

// twiddle -(1 + j) * sqrt(1/2)
static inline void BflyR3(float* a, float* b, __m128 r)
{
    __m128 a0 = _mm_load_ps(a), a1 = _mm_load_ps(a + 4);
    __m128 x = _mm_mul_ps(_mm_load_ps(b), r);
    __m128 y = _mm_mul_ps(_mm_load_ps(b + 4), r);
    __m128 t0 = _mm_add_ps(x, y);
    __m128 t1 = _mm_sub_ps(x, y);
    _mm_store_ps(a,     _mm_sub_ps(a0, t0));
    _mm_store_ps(a + 4, _mm_add_ps(a1, t1));
    _mm_store_ps(b,     _mm_add_ps(a0, t0));
    _mm_store_ps(b + 4, _mm_sub_ps(a1, t1));
}

// general twiddle: t = (b0*w0 - b1*w1, b1*w0 + b0*w1)
static inline void BflyW(float* a, float* b, __m128 w0, __m128 w1)
{
    __m128 a0 = _mm_load_ps(a), a1 = _mm_load_ps(a + 4);
    __m128 b0 = _mm_load_ps(b), b1 = _mm_load_ps(b + 4);
    __m128 t0 = _mm_sub_ps(_mm_mul_ps(b0, w0), _mm_mul_ps(b1, w1));
    __m128 t1 = _mm_add_ps(_mm_mul_ps(b1, w0), _mm_mul_ps(b0, w1));
    _mm_store_ps(a,     _mm_add_ps(a0, t0));
    _mm_store_ps(a + 4, _mm_add_ps(a1, t1));
    _mm_store_ps(b,     _mm_sub_ps(a0, t0));
    _mm_store_ps(b + 4, _mm_sub_ps(a1, t1));
}

// @ 0x0115f2a0
void ComplexFFT(FftTable* table, float* data)
{
    int log2n = table->log2n;
    const float* cosT = (const float*)((char*)table + table->cosOffset);
    const float* sinT = (const float*)((char*)table + table->sinOffset);
    const int* bitrev = (const int*)((char*)table + table->bitrevOffset);
    int n = 1 << log2n;
    float scale = 1.0f / (float)n;

    // bit-reversal permutation of the complex samples
    float* p = data;
    for (int i = 0; i < n; ++i, p += 2) {
        int j = bitrev[i];
        if (i < j) {
            float re = p[0];
            float im = p[1];
            p[0] = data[j * 2];
            p[1] = data[j * 2 + 1];
            data[j * 2] = re;
            data[j * 2 + 1] = im;
        }
    }

    float* buf = (float*)gAudioSystem->Alloc(n * 8, "FFT Buffer", 0x10, 0);
    int half = n >> 1;

    // split the 2n floats into 4 lanes: buf[4*m + lane] = data[lane*half + m]
    {
        const float* src = data;
        float* lane = buf + 8;
        for (int k = 4; k != 0; --k) {
            float* d = lane;
            for (int m = 0; m < half; m += 8) {
                d[-8] = src[m];
                d[-4] = src[m + 1];
                d[0] = src[m + 2];
                d[4] = src[m + 3];
                d[8] = src[m + 4];
                d[12] = src[m + 5];
                d[16] = src[m + 6];
                d[20] = src[m + 7];
                d += 32;
            }
            src += half;
            lane += 1;
        }
    }

    // ---- 4-wide passes (inline __asm in the original) ----
    {
        const __m128 negOne = _mm_set1_ps(-1.0f);
        const __m128 r = _mm_set1_ps(0.70710677f);
        const __m128 s = _mm_set1_ps(scale);
        int total = n * 2;
        int cnt;
        float* x;

        // pass 1: span 1, scaled by 1/N
        x = buf;
        cnt = total;
        do {
            BflyScaled(x, x + 8, s);
            BflyScaled(x + 16, x + 24, s);
            x += 32;
        } while ((cnt -= 32) != 0);

        // pass 2: span 2
        x = buf;
        cnt = total;
        do {
            Bfly(x, x + 16);
            BflyJ(x + 8, x + 24);
            x += 32;
        } while ((cnt -= 32) != 0);

        // pass 3: span 4
        x = buf;
        cnt = total;
        do {
            Bfly(x, x + 32);
            BflyJ(x + 16, x + 48);
            BflyR1(x + 8, x + 40, r);
            BflyR3(x + 24, x + 56, r);
            x += 64;
        } while ((cnt -= 64) != 0);

        // remaining 4-wide passes
        unsigned int L = 16;              // span in floats/4 (complex count * 2)
        unsigned int m = (unsigned int)n >> 4;  // twiddle stride
        int stages = log2n - 5;
        do {
            x = buf;
            unsigned int groups = m >> 2;
            unsigned int kEnd = (L << 4) >> 6;
            do {
                float* y = x + L * 4;
                Bfly(x, y);
                BflyJ(x + L * 2, y + L * 2);
                BflyR1(x + L, y + L, r);
                BflyR3(x + L * 3, y + L * 3, r);
                unsigned int k = 2;
                do {
                    unsigned int idx = k * m;
                    __m128 C = _mm_set1_ps(cosT[idx]);
                    __m128 nC = _mm_mul_ps(C, negOne);
                    __m128 S = _mm_set1_ps(sinT[idx]);
                    __m128 nS = _mm_mul_ps(S, negOne);
                    unsigned int o = k * 4;
                    BflyW(x + o, y + o, C, S);
                    BflyW(x + L * 4 - o, y + L * 4 - o, nC, S);
                    BflyW(x + L * 2 - o, y + L * 2 - o, S, C);
                    BflyW(x + L * 2 + o, y + L * 2 + o, nS, C);
                    k += 2;
                } while (k != kEnd);
                x += L * 8;
            } while (--groups != 0);
            m >>= 1;
            L <<= 1;
        } while (--stages != 0);
    }

    // ---- last two passes, scalar on the interleaved data ----
    int mm = n >> (log2n - 1);
    int L = 16 << (log2n - 5);

    // merge the lanes back: data[lane*half + m] = buf[4*m + lane]
    {
        float* dst = data;
        float* lane = buf + 8;
        for (int k = 4; k != 0; --k) {
            const float* sp = lane;
            for (int m = 0; m < half; m += 8) {
                dst[m] = sp[-8];
                dst[m + 1] = sp[-4];
                dst[m + 2] = sp[0];
                dst[m + 3] = sp[4];
                dst[m + 4] = sp[8];
                dst[m + 5] = sp[12];
                dst[m + 6] = sp[16];
                dst[m + 7] = sp[20];
                sp += 32;
            }
            dst += half;
            lane += 1;
        }
    }

    const float r = 0.70710677f;
    for (int stage = 2; stage != 0; --stage) {
        int i = 0;
        if (mm > 0) {
            int q = L >> 2;
            int h = L >> 1;
            for (int g = mm; g != 0; --g) {
                float* a;
                float* b;
                float are, aim, bre, bim, t, u;

                // twiddle 1
                a = data + i;
                b = data + i + L;
                are = a[0]; aim = a[1]; bre = b[0]; bim = b[1];
                a[0] = bre + are;
                a[1] = bim + aim;
                b[0] = are - bre;
                b[1] = aim - bim;

                // twiddle -j
                a = data + h + i;
                b = data + h + i + L;
                are = a[0]; aim = a[1]; bre = b[0]; bim = b[1];
                a[0] = are - bim;
                a[1] = bre + aim;
                b[1] = aim - bre;
                b[0] = bim + are;

                // twiddle (1 - j) * sqrt(1/2)
                a = data + q + i;
                b = data + q + i + L;
                are = a[0]; aim = a[1];
                bre = b[0] * r; bim = b[1] * r;
                t = bre - bim;
                u = bim + bre;
                a[0] = t + are;
                a[1] = u + aim;
                b[1] = aim - u;
                b[0] = are - t;

                // twiddle -(1 + j) * sqrt(1/2)
                a = data + q + h + i;
                b = data + q + h + i + L;
                are = a[0]; aim = a[1];
                bim = b[1] * r; bre = b[0] * r;
                t = bim + bre;
                u = bre - bim;
                a[0] = are - t;
                a[1] = u + aim;
                b[0] = t + are;
                b[1] = aim - u;

                for (int j = 2; j < q; j += 2) {
                    float c = cosT[j * mm];
                    float sn = sinT[j * mm];

                    a = data + i + j;
                    b = data + i + L + j;
                    are = a[0]; aim = a[1]; bre = b[0]; bim = b[1];
                    t = bre * c - bim * sn;
                    u = bim * c + bre * sn;
                    a[0] = t + are;
                    a[1] = u + aim;
                    b[0] = are - t;
                    b[1] = aim - u;

                    a = data + i + L - j;
                    b = data + i + 2 * L - j;
                    are = a[0]; aim = a[1]; bre = b[0]; bim = b[1];
                    u = bre * sn - bim * c;
                    t = -(bre * c) - bim * sn;
                    a[0] = t + are;
                    a[1] = u + aim;
                    b[0] = are - t;
                    b[1] = aim - u;

                    a = data + i + h - j;
                    b = data + i + h + L - j;
                    are = a[0]; aim = a[1]; bre = b[0]; bim = b[1];
                    u = bim * sn + bre * c;
                    t = bre * sn - bim * c;
                    a[0] = t + are;
                    a[1] = u + aim;
                    b[1] = aim - u;
                    b[0] = are - t;

                    a = data + i + h + j;
                    b = data + i + h + L + j;
                    are = a[0]; aim = a[1]; bre = b[0]; bim = b[1];
                    t = -(bre * sn) - bim * c;
                    u = bre * c - bim * sn;
                    a[0] = t + are;
                    a[1] = u + aim;
                    b[0] = are - t;
                    b[1] = aim - u;
                }
                i += L * 2;
            }
        }
        mm >>= 1;
        L += L;
    }

    gAudioSystem->Free(buf, 0);
}
