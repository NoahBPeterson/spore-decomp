// RenderWare 4 core audio: FFT / FIR / Butterworth-biquad coefficient helpers (slice s0115ffe0).
// Built with VS2008 SP1 (cl 15.00.30729.01) at /arch:SSE /fp:fast.  The straight-line integer
// and simple float leaf routines are byte-exact; the SSE-unrolled and x87-transcendental bodies
// are the behaviour-equivalent reconstruction.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Globals / extern helpers
// ---------------------------------------------------------------------------
extern float  g_015c412c[];                                                          // 0x015c412c  T1 table
extern float  g_015c3f4c[];                                                          // 0x015c3f4c  T2[-1] base
extern void*  __cdecl operator_new_arr(void* dst, int zero, int size);                // 0x011e073e
extern void   __cdecl eastl_vector_insert(void* dst, const void* src, unsigned count); // 0x011e0744
extern void   __cdecl FUN_011342c0(void* dst, void* src, float start, int count);     // 0x011342c0
extern void   __cdecl FUN_01134260(void* dst, void* src, float gain, int count);      // 0x01134260
extern void   __cdecl FUN_0115f2a0(void* ctx, float* buf);                            // 0x0115f2a0
extern double __cdecl FUN_011e08f0(double base, double exp);                          // 0x011e08f0  x87 pow

// ---------------------------------------------------------------------------
// thiscall callees modelled as member functions so ecx=this and ret N are reproduced
// ---------------------------------------------------------------------------
struct Fir64Obj
{
    void FUN_01160540(void);                                    // 0x01160540
};

struct BiquadObj
{
    void FUN_011604d0(float* coeffs, int n);                    // 0x011604d0
};

struct ButterworthObj
{
    void FUN_01160560(float* dst, float* src, float* coeffs, int count); // 0x01160560
    void FUN_01160790(void* ctx, void* coeffs);                 // 0x01160790
    void FUN_01160910(float cutoff, int order, float sr, int type); // 0x01160910
    void FUN_01160dc0(void);                                    // 0x01160dc0
};

// ---------------------------------------------------------------------------
// @ 0x0115ffe0
// ---------------------------------------------------------------------------
void __cdecl FUN_0115ffe0(int* param_1, float* param_2)
{
    int size = 1 << (param_1[0] + 1);
    int half = size >> 1;
    char* tblA = (char*)param_1 + param_1[3];
    char* tblB = (char*)param_1 + param_1[4];

    float* q = param_2 + size;
    for (int i = 0; i <= half; i += 2)
    {
        float u0 = q[0];
        float t0 = param_2[i];
        float s0 = u0 + t0;
        float d0 = t0 - u0;
        float u1 = q[1];
        float t1 = param_2[i + 1];
        float s1 = t1 + u1;
        float d1 = t1 - u1;
        int k = (i >> 1) * 4;
        float a = *(float*)(tblA + k);
        float b = *(float*)(tblB + k);

        param_2[i]     = (s0 - b * d0) - a * s1;
        param_2[i + 1] = (a * d0 + d1) - b * s1;
        q[0] = (a * s1 + b * d0) + s0;
        q[1] = (a * d0 - d1) - b * s1;

        q -= 2;
    }

    FUN_0115f2a0(param_1, param_2);
}

// ---------------------------------------------------------------------------
// @ 0x011600e0
// ---------------------------------------------------------------------------
void __cdecl FUN_011600e0(float* dst, float* src, float start, float delta, int count)
{
    if (delta != 0.0f)
    {
        count -= 0x40;
        for (int k = 0; k < 0x40; k++)
            dst[k] += (start + (float)k * delta) * src[k];
        start = start + delta * 64.0f;
        dst += 0x40;
        src += 0x40;
    }
    FUN_011342c0(dst, src, start, count);
}

// ---------------------------------------------------------------------------
// @ 0x01160300
// ---------------------------------------------------------------------------
void __cdecl FUN_01160300(float* dst, float* src, float start, float delta, int count)
{
    if (delta != 0.0f)
    {
        count -= 0x40;
        for (int k = 0; k < 0x40; k++)
            dst[k] = (start + (float)k * delta) * src[k];
        start = start + delta * 64.0f;
        dst += 0x40;
        src += 0x40;
    }
    FUN_01134260(dst, src, start, count);
}

// ---------------------------------------------------------------------------
// @ 0x011604d0
// ---------------------------------------------------------------------------
void BiquadObj::FUN_011604d0(float* coeffs, int n)
{
    int cnt = n / 2 + 1;
    for (int i = 0; i < cnt; i++)
        coeffs[i] = (0.54f - cosf((float)i * 6.2831855f / (float)n) * 0.46f) * coeffs[i];
}

// ---------------------------------------------------------------------------
// @ 0x01160540
// ---------------------------------------------------------------------------
void Fir64Obj::FUN_01160540(void)
{
    operator_new_arr((char*)this + *(uint16_t*)this, 0,
                     *(uint8_t*)((char*)this + 6) * *(uint16_t*)((char*)this + 2));
}

// ---------------------------------------------------------------------------
// @ 0x01160560
// ---------------------------------------------------------------------------
void ButterworthObj::FUN_01160560(float* dst, float* src, float* coeffs, int count)
{
    float F[272];

    for (int t = 0; t < 8; t++) F[64 + t]  = 0.0f;
    for (int t = 0; t < 8; t++) F[132 + t] = 0.0f;
    for (int t = 0; t < 8; t++) F[200 + t] = 0.0f;

    for (int i = 0; i < 8; i++)
    {
        int r = 64 - 4 * i;
        for (int b = 0; b < 4; b++)
        {
            int base = 69 * b;
            F[base + 4 * i + 0] = coeffs[4 * i + 0];
            F[base + 4 * i + 1] = coeffs[4 * i + 1];
            F[base + 4 * i + 2] = coeffs[4 * i + 2];
            F[base + 4 * i + 3] = coeffs[4 * i + 3];
            F[base + r - 3] = coeffs[4 * i + 3];
            F[base + r - 2] = coeffs[4 * i + 2];
            F[base + r - 1] = coeffs[4 * i + 1];
            F[base + r - 0] = coeffs[4 * i + 0];
        }
    }

    for (int b = 0; b < 4; b++)
        F[69 * b + 32] = coeffs[32];

    for (int o = 0; o < count; o += 4)
    {
        for (int j = 0; j < 4; j++)
        {
            float acc = 0.0f;
            for (int t = 0; t < 68; t++)
                acc += F[68 * j + t] * src[o - 64 + t];
            dst[o + j] = acc;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x01160790
// ---------------------------------------------------------------------------
void ButterworthObj::FUN_01160790(void* ctx, void* coeffs)
{
    uint8_t* self  = (uint8_t*)this;
    uint8_t* base  = self + *(uint16_t*)self;
    int      len   = *(uint16_t*)(self + 2);
    int      off   = *(uint16_t*)(self + 4);
    unsigned chans = *(uint8_t*)(self + 6);
    uint8_t* ndA   = *(uint8_t**)((uint8_t*)ctx + 0x3000c);
    uint8_t* ndB   = *(uint8_t**)((uint8_t*)ctx + 0x30010);

    uint8_t* p = base;
    for (unsigned ch = 0; ch < chans; ch++)
    {
        uint8_t* dstB = *(uint8_t**)(ndB + 4) + *(uint16_t*)(ndB + 0xe) * ch * 4;
        eastl_vector_insert(dstB, p, len);
        uint8_t* dstA = *(uint8_t**)(ndA + 4) + *(uint16_t*)(ndA + 0xe) * ch * 4;
        eastl_vector_insert(dstB + off * 4, dstA, len);
        p += off * 4;
    }

    for (unsigned ch = 0; ch < chans; ch++)
    {
        uint8_t* dstB = *(uint8_t**)(ndB + 4) + *(uint16_t*)(ndB + 0xe) * ch * 4;
        FUN_01160560((float*)dstB, (float*)(dstB + off * 4), (float*)coeffs, off);
    }

    p = base;
    for (unsigned ch = 0; ch < chans; ch++)
    {
        uint8_t* dstA = *(uint8_t**)(ndA + 4) + *(uint16_t*)(ndA + 0xe) * ch * 4;
        uint8_t* srcB = *(uint8_t**)(ndB + 4) +
                        (*(uint16_t*)(ndB + 0xe) * ch + off) * 4;
        FUN_01160560((float*)(dstA + off * 4), (float*)srcB, (float*)coeffs, 0x100 - off);
        eastl_vector_insert(p, dstA + (0x100 - off) * 4, len);
        p += off * 4;
    }

    void* tmp = *(void**)((uint8_t*)ctx + 0x30010);
    *(void**)((uint8_t*)ctx + 0x30010) = *(void**)((uint8_t*)ctx + 0x3000c);
    *(void**)((uint8_t*)ctx + 0x3000c) = tmp;
}

// ---------------------------------------------------------------------------
// @ 0x01160910
// ---------------------------------------------------------------------------
void ButterworthObj::FUN_01160910(float cutoff, int order, float sr, int type)
{
    float* self = (float*)this;
    float  f[5];

    for (int j = 0; j < 10; j++) self[j] = 0.0f;
    f[0] = 1.0f; f[1] = 0.0f; f[2] = 0.0f; f[3] = 0.0f; f[4] = 0.0f;

    if (type == 0)
        f[1] = 1.0f / tanf(cutoff * 6.2831855f / sr * 0.5f);
    else if (type == 1)
        f[1] = tanf(cutoff * 6.2831855f / sr * 0.5f);

    f[2] = (float)FUN_011e08f0(f[1], 2.0);
    f[3] = (float)FUN_011e08f0(f[1], 3.0);
    f[4] = (float)FUN_011e08f0(f[1], 4.0);

    for (int m = 0; m <= order; m++)
    {
        float sgn = (type == 0 || (m & 1) == 0) ? 1.0f : -1.0f;
        self[m] = g_015c412c[order * 5 + m] * sgn;

        float acc = 0.0f;
        for (int k = 0; k <= order; k++)
            acc += f[k] * g_015c3f4c[order * 25 + 5 * m + k]
                       * g_015c3f4c[order * 5 + k] * sgn;
        self[5 + m] = acc;
    }

    float inv = 1.0f / self[5];
    for (int j = 0; j <= order; j++)
    {
        self[j]     *= inv;
        self[5 + j] *= inv;
    }

    float g = 0.0f;
    float h = 0.0f;
    for (int j = 0; j <= order; j++)
    {
        float sgn = (type == 0 || (j & 1) == 0) ? 1.0f : -1.0f;
        g += sgn * self[5 + j];
        h += sgn * self[j];
    }

    float ratio = g / h;
    for (int j = 0; j <= order; j++)
        self[j] *= ratio;
}

// ---------------------------------------------------------------------------
// @ 0x01160dc0  rw::audio::core::Butterworth::ClearBuffer
// ---------------------------------------------------------------------------
void ButterworthObj::FUN_01160dc0(void)
{
    char* self = (char*)this;
    char* d0 = self + *(uint16_t*)(self + 0x2c);
    char* d1 = self + *(uint16_t*)(self + 0x2e);
    operator_new_arr(d0, 0, *(int*)(self + 0x28) * 0x14);
    operator_new_arr(d1, 0, *(int*)(self + 0x28) * 0x14);
}
