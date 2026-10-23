// RenderWare 4 audio core (slice s01153b20): the second Pan3D/HPF/mix-ramp method set
// (twin of s01152b70 with different field offsets and constants), plus the EA Thread
// device-watchdog atomics and rw::audio::core::Mixer::HandleBufferStatusUnavailable.
// Built with VS2008 SP1 (cl 15.00.30729.01) at /arch:SSE /fp:fast: the float bodies use
// scalar SSE (movss/mulss/comiss) plus x87 fcos/fsin/fsqrt/fyl2x, so they only match
// cl 15.00 with fast floats.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <intrin.h>

// ---------------------------------------------------------------------------
// extern free helpers
// ---------------------------------------------------------------------------
extern void* __cdecl operator_new_arr(void* dst, int zero, int size);                     // 0x011e073e
extern void  __cdecl FUN_01163620(void* dst, int count, float a, float b, int c, int d);  // 0x01163620 MixRampLinear
extern void  __cdecl FUN_01163520(void* dst, int count, float a, float b, int c, int d);  // 0x01163520 MixRampSqrt
extern void  __cdecl FUN_011633f0(void* dst, int count, float a, float b, int c, int d);  // 0x011633f0 MixRampSin
extern long long __cdecl FUN_0113ccf0(void* out);                                          // 0x0113ccf0
extern "C" int __stdcall FUN_0120ba6a(const void* guid, void** out);                       // 0x0120ba6a DSOUND DirectSoundCreate thunk
extern "C" void  __cdecl FUN_00921df0(int* ms);                                            // 0x00921df0 EA::Thread::ThreadSleep
extern "C" void* __cdecl FUN_00922920(void);                                               // 0x00922920

// ---------------------------------------------------------------------------
// x87 transcendental helpers (the original issues fcos/fsin/fsqrt/fyl2x directly)
// ---------------------------------------------------------------------------
static float X87Cos(float a)  { float r; __asm { fld a } __asm { fcos } __asm { fstp r } return r; }
static float X87Sin(float a)  { float r; __asm { fld a } __asm { fsin } __asm { fstp r } return r; }
static float X87Sqrt(float a) { float r; __asm { fld a } __asm { fsqrt } __asm { fstp r } return r; }

// 2 * sqrt(sqrt(q)) * (sin(ang) * 0.70710653), kept in x87 extended precision like the original
static const float k0_70710653 = 0.70710653f;
static float X87F2(float q, float ang)
{
    float r;
    __asm { fld ang }
    __asm { fsin }
    __asm { fmul k0_70710653 }
    __asm { fld q }
    __asm { fsqrt }
    __asm { fsqrt }
    __asm { fmulp st(1), st }
    __asm { fadd st(0), st(0) }
    __asm { fstp r }
    return r;
}

// ---------------------------------------------------------------------------
// thiscall callees that live elsewhere in the image (resolved by their FUN_<va> name)
// ---------------------------------------------------------------------------
struct Filter
{
    void FUN_0114f100(void* a, void* b, void* coeffs);   // 0x0114f100
    void FUN_0114f4f0(void);                             // 0x0114f4f0
};
struct ButterworthObj
{
    void FUN_01160dc0(void);                                        // 0x01160dc0
    void FUN_01160910(float cutoff, int order, float sr, int type); // 0x01160910
    void FUN_01160e00(void* ctx);                                   // 0x01160e00
    void FUN_01160540(void);                                        // 0x01160540
    void FUN_01160790(void* ctx, void* coeffs);                     // 0x01160790
};
struct HpSelf
{
    void FUN_01153f90(float phase);   // 0x01153f90
};
struct DelayLine
{
    void FUN_00fccdd0(void* p);                       // 0x00fccdd0
    void FUN_0115d5e0(int p, int n);                  // 0x0115d5e0
    int  FUN_0115d600(void);                          // 0x0115d600
    void FUN_0115d5c0(int n);                         // 0x0115d5c0
    void FUN_0114d9d0(int n);                         // 0x0114d9d0 DelayLine::Reset
    void FUN_0115d990(int a, int b, int c, int d);    // 0x0115d990
};
struct MixRamp
{
    void FUN_01163be0(float fade);                    // 0x01163be0 cMixRamp::SetFade
};
struct Obj64
{
    long long FUN_0068c140(void);                     // 0x0068c140
};
struct ThreadParams
{
    void FUN_00922900(void);                          // 0x00922900
};

// ---------------------------------------------------------------------------
// Pan3D matrix builders (this is the second Pan3D method set)
// ---------------------------------------------------------------------------
struct Pan3D
{
    void FUN_01153b20(float ang, float q);   // 0x01153b20
    void FUN_01153dc0(float ang);            // 0x01153dc0
};

// ---------------------------------------------------------------------------
// EA Thread device watchdog object (the atomic flags live at +0x10)
// ---------------------------------------------------------------------------
struct ThreadObj
{
    void FUN_01154730(int value);                     // 0x01154730 atomic OR
    void FUN_01154770(int value);                     // 0x01154770 atomic AND
    void FUN_011547b0(void);                          // 0x011547b0
    void FUN_011547e0(void);                          // 0x011547e0
    void FUN_01154800(void);                          // 0x01154800 watchdog loop
    void FUN_011548d0(void);                          // 0x011548d0 start watchdog thread
    void Wake(void);                                  // 0x00922d10 EA::Thread::Thread::Wake
    int  WaitForEnd(const unsigned int* id, int* out); // 0x00922940 EA::Thread::Thread::WaitForEnd
    void FUN_00922f30(void* fn, void* arg, void* params, void* prio); // 0x00922f30
};

// ---------------------------------------------------------------------------
// rw::audio::core::Mixer (only the buffer-status handler is in this slice)
// ---------------------------------------------------------------------------
namespace rw { namespace audio { namespace core {

class Mixer
{
public:
    unsigned int HandleBufferStatusUnavailable(int sampleBuffer, int system, int numSamples);
};

}}}

// ---------------------------------------------------------------------------
// @ 0x01153b20
// ---------------------------------------------------------------------------
void Pan3D::FUN_01153b20(float ang, float q)
{
    float c = X87Cos(ang);
    float q2 = X87Sqrt(q);
    float q4 = X87Sqrt(q2);
    float A = q2 - 1.0f;
    float B = q2 + 1.0f;
    float Ac = A * c;
    float Bc = B * c;
    float f2 = X87F2(q, ang);
    float inv = 1.0f / ((B - Ac) + f2);
    *(float*)((char*)this + 0x9c) = ((A - Bc) * inv) * 2.0f;
    *(float*)((char*)this + 0xa0) = ((B - Ac) - f2) * inv;
    *(float*)((char*)this + 0xa4) = (((Ac + B) + f2) * inv) * q2;
    *(float*)((char*)this + 0xa8) = (((Bc + A) * inv) * q2) * -2.0f;
    *(float*)((char*)this + 0xac) = (((Ac + B) - f2) * inv) * q2;
}

// ---------------------------------------------------------------------------
// @ 0x01153c20
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01153c20(int self, int ctx)
{
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);
    float phase = (*(float*)(self + 0x28) / sr) * 6.2831855f;

    if (!(3.138451f <= phase) && *(float*)(self + 0x30) != 1.0f)
    {
        if (*(int*)(self + 0x98) == 0)
            *(int*)(self + 0x98) = 1;
        if (phase < 0.003141593f)
            phase = 0.003141593f;
        if (phase != *(float*)(self + 0xb0) || *(float*)(self + 0x30) != *(float*)(self + 0xb4))
        {
            ((Pan3D*)self)->FUN_01153b20(phase, *(float*)(self + 0x30));
            *(float*)(self + 0xb4) = *(float*)(self + 0x30);
            *(float*)(self + 0xb0) = phase;
        }
        int node0c = *(int*)(ctx + 0x3000c);
        int node10 = *(int*)(ctx + 0x30010);
        for (uint32_t ch = 0; ch < *(uint8_t*)(self + 0x21); ch++)
            ((Filter*)(self + 0x38 + ch * 0x10))->FUN_0114f100(
                (void*)(*(int*)(node10 + 4) + *(uint16_t*)(node10 + 0xe) * ch * 4),
                (void*)(*(int*)(node0c + 4) + *(uint16_t*)(node0c + 0xe) * ch * 4),
                (void*)(self + 0x9c));
        int tmp = *(int*)(ctx + 0x30010);
        *(int*)(ctx + 0x30010) = *(int*)(ctx + 0x3000c);
        *(int*)(ctx + 0x3000c) = tmp;
        return 1;
    }

    if (*(int*)(self + 0x98) == 1)
    {
        for (uint32_t ch = 0; ch < *(uint8_t*)(self + 0x21); ch++)
            ((Filter*)(self + 0x38 + ch * 0x10))->FUN_0114f4f0();
        *(int*)(self + 0x98) = 0;
    }
    *(float*)(self + 0xb4) = *(float*)(self + 0x30);
    *(float*)(self + 0xb0) = phase;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01153dc0
// ---------------------------------------------------------------------------
void Pan3D::FUN_01153dc0(float ang)
{
    float c = X87Cos(ang);
    float s = X87Sin(ang) * 0.5f;
    float d = s + 1.0f;
    float inv = 1.0f / d;
    float e = c + 1.0f;
    *(float*)((char*)this + 0x90) = (c * -2.0f) * inv;
    float f = e / (d * 2.0f);
    *(float*)((char*)this + 0x94) = (1.0f - s) * inv;
    *(float*)((char*)this + 0x98) = f;
    *(float*)((char*)this + 0x9c) = -(e * inv);
    *(float*)((char*)this + 0xa0) = f;
}

// ---------------------------------------------------------------------------
// @ 0x01153e60
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01153e60(int self, int ctx)
{
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);
    float phase = (*(float*)(self + 0x28) / sr) * 6.2831855f;

    if (!(0.003141593f >= phase))
    {
        if (phase > 3.138451f)
            phase = 3.138451f;
        if (phase != *(float*)(self + 0xa4))
        {
            ((Pan3D*)self)->FUN_01153dc0(phase);
            *(float*)(self + 0xa4) = phase;
        }
        int node0c = *(int*)(ctx + 0x3000c);
        int node10 = *(int*)(ctx + 0x30010);
        for (uint32_t ch = 0; ch < *(uint8_t*)(self + 0x21); ch++)
            ((Filter*)(self + 0x30 + ch * 0x10))->FUN_0114f100(
                (void*)(*(int*)(node10 + 4) + *(uint16_t*)(node10 + 0xe) * ch * 4),
                (void*)(*(int*)(node0c + 4) + *(uint16_t*)(node0c + 0xe) * ch * 4),
                (void*)(self + 0x90));
        int tmp = *(int*)(ctx + 0x3000c);
        *(int*)(ctx + 0x3000c) = *(int*)(ctx + 0x30010);
        *(int*)(ctx + 0x30010) = tmp;
        return 1;
    }

    if (*(float*)(self + 0xa4) > 0.003141593f)
    {
        for (uint32_t ch = 0; ch < *(uint8_t*)(self + 0x21); ch++)
            ((Filter*)(self + 0x30 + ch * 0x10))->FUN_0114f4f0();
    }
    *(float*)(self + 0xa4) = phase;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01154030
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01154030(int self, int ctx)
{
    int bw = self + *(uint16_t*)(self + 0xb8);
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);
    float phase = (*(float*)(self + 0x28) / sr) * 6.2831855f;

    if (0.0f >= phase)
    {
        if (*(float*)(self + 0xb4) > 0.0f)
            ((ButterworthObj*)bw)->FUN_01160540();
        *(float*)(self + 0xb4) = phase;
        return 1;
    }

    if (phase > 3.1415927f)
        phase = 3.1415927f;
    if (phase != *(float*)(self + 0xb4))
    {
        ((HpSelf*)self)->FUN_01153f90(phase);
        *(float*)(self + 0xb4) = phase;
    }
    ((ButterworthObj*)bw)->FUN_01160790((void*)ctx, (void*)(self + 0x30));
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011540f0
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_011540f0(int self, int ctx)
{
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);
    float nyq = sr * 0.5f;
    float margin = nyq * 0.01f;
    float hi = nyq - margin;
    int bw = self + *(uint16_t*)(self + 0x48);

    if (*(float*)(self + 0x28) < margin)
    {
        if (*(float*)(self + 0x38) >= margin)
            ((ButterworthObj*)bw)->FUN_01160dc0();
        *(float*)(self + 0x38) = *(float*)(self + 0x28);
        return 1;
    }

    if (*(float*)(self + 0x28) > hi)
        *(float*)(self + 0x28) = hi;
    if (*(float*)(self + 0x28) != *(float*)(self + 0x38) ||
        *(float*)(self + 0x30) != *(float*)(self + 0x40))
    {
        int order = (int)(long long)*(float*)(self + 0x30);
        ((ButterworthObj*)bw)->FUN_01160910(*(float*)(self + 0x28), order, sr, 1);
        *(float*)(self + 0x38) = *(float*)(self + 0x28);
        *(float*)(self + 0x40) = *(float*)(self + 0x30);
    }
    ((ButterworthObj*)bw)->FUN_01160e00((void*)ctx);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011541e0
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_011541e0(int self, int ctx)
{
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);

    if (*(uint8_t*)(self + 0x68) == 1)
    {
        *(float*)(self + 0x5c) = *(float*)(self + 0x64);
        *(float*)(self + 0x50) = *(float*)(self + 0x38);
        *(double*)(self + 0x48) = *(double*)(self + 0x30);
        *(uint8_t*)(self + 0x6a) = *(uint8_t*)(self + 0x40);
        *(float*)(self + 0x60) = *(float*)(self + 0x3c);
        int n = (int)(*(float*)(self + 0x38) * sr);
        *(int*)(self + 0x54) = n;
        if (n < 1)
            *(int*)(self + 0x54) = 1;
        *(uint8_t*)(self + 0x69) = 1;
        *(uint8_t*)(self + 0x68) = 0;
    }

    if (*(uint8_t*)(self + 0x69) == 1)
    {
        int off = 0;
        bool doBlock = true;
        if (*(double*)(self + 0x48) != 0.0)
        {
            off = (int)((*(double*)(self + 0x48) - *(double*)(ctx + 0x30000)) * sr);
            if (off >= 0x100)
                doBlock = false;
        }
        if (doBlock)
        {
            int neg = -off;
            int lim = *(int*)(self + 0x54) - 1;
            *(int*)(self + 0x58) = neg;
            if (neg > lim)
            {
                *(uint8_t*)(self + 0x69) = 0;
            }
            else
            {
                if (neg > 0)
                    *(int*)(self + 0x58) = 0;
                *(uint8_t*)(self + 0x69) = 2;
            }
        }
    }

    int node0c = *(int*)(ctx + 0x3000c);
    float* ramp = *(float**)(*(int*)(ctx + 0x30010) + 4);

    if (*(uint8_t*)(self + 0x69) == 0 || *(uint8_t*)(self + 0x69) == 1)
    {
        if (*(float*)(self + 0x64) == 1.0f)
            return 1;
        for (int i = 0; i < 0x100; i++)
            ramp[i] = *(float*)(self + 0x64);
    }
    else
    {
        float a = *(float*)(self + 0x5c);
        float b = *(float*)(self + 0x60);
        int c = *(int*)(self + 0x58);
        int d = *(int*)(self + 0x54);
        uint8_t m = *(uint8_t*)(self + 0x6a);
        if (m == 0)
            FUN_01163620(ramp, 0x100, a, b, c, d);
        else if (m == 1)
            FUN_01163520(ramp, 0x100, a, b, c, d);
        else
            FUN_011633f0(ramp, 0x100, a, b, c, d);
        *(int*)(self + 0x58) += 0x100;
        if (*(int*)(self + 0x58) >= *(int*)(self + 0x54))
            *(uint8_t*)(self + 0x69) = 0;
    }

    for (uint32_t ch = 0; ch < *(uint8_t*)(self + 0x20); ch++)
    {
        float* dst = (float*)(*(int*)(node0c + 4) + *(uint16_t*)(node0c + 0xe) * ch * 4);
        for (int i = 0; i < 0x100; i++)
            dst[i] = dst[i] * ramp[i];
    }

    float last = ramp[0xff];
    *(float*)(self + 0x64) = last;
    *(float*)(self + 0x28) = last;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011544d0
// ---------------------------------------------------------------------------
void __fastcall FUN_011544d0(int self)
{
    if (*(int*)(self + 0x38) == 1)
    {
        float f = (float)*(int*)(self + 0x84);
        float r = f;
        if (*(float*)(self + 0x54) != 0.0f)
        {
            double d = (double)f;
            r = (float)(d - (5.0 * d) / log10(fabs((double)*(float*)(self + 0x54))));
        }
        *(float*)(self + 0x14) = f;
        int p = *(int*)(self + 8);
        *(float*)(p + 0x28) = (r - *(float*)(self + 0x18)) + *(float*)(p + 0x28);
        *(float*)(self + 0x18) = r;
        return;
    }
    *(float*)(self + 0x14) = 0.0f;
    int p = *(int*)(self + 8);
    float neg = -*(float*)(self + 0x18);
    *(float*)(p + 0x28) = neg + *(float*)(p + 0x28);
    *(float*)(self + 0x18) = 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x01154580
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01154580(int self, int ctx)
{
    MixRamp* ramp = (MixRamp*)(self + 0x44);
    DelayLine* delay = (DelayLine*)(self + 0x5c);

    *(void**)(self + 0x44) = (void*)0x01163b50;   // MixDispatch
    *(void**)(self + 0x48) = (void*)0x01163bc0;   // cMixRamp::ClearFade
    delay->FUN_00fccdd0((void*)(self + 0x44));

    int sysQ = *(int*)(*(int*)(self + 4));
    int top = *(int*)(sysQ + 0xc);
    int lo = top - 0xb00;
    *(int*)(sysQ + 0xc) = lo;
    delay->FUN_0115d5e0(lo, 0x2c0);

    float fade = *(float*)(self + 0x30);
    int state = *(int*)(self + 0x38);
    int n = (int)(*(float*)(*(int*)(ctx + 0x30018) + 0xc) * *(float*)(self + 0x28));

    switch (state)
    {
    case 0:
        if (n > 0)
        {
            (*(void(__cdecl*)(void*))*(void**)(self + 0x48))((void*)(self + 0x44));
            ramp->FUN_01163be0(fade);
            delay->FUN_0114d9d0(n);
            *(int*)(self + 0x38) = 1;
        }
        break;
    case 1:
        if (n <= 0)
        {
            *(int*)(self + 0x38) = 0;
        }
        else
        {
            int cur = delay->FUN_0115d600();
            if (cur < n)
            {
                *(int*)(self + 0x38) = 2;
            }
            else
            {
                ramp->FUN_01163be0(fade);
                delay->FUN_0115d5c0(n);
            }
        }
        break;
    case 2:
        if (n <= 0)
        {
            *(int*)(self + 0x38) = 0;
        }
        else
        {
            int cur = delay->FUN_0115d600();
            if (n <= cur)
            {
                ramp->FUN_01163be0(fade);
                delay->FUN_0115d5c0(n);
                *(int*)(self + 0x38) = 1;
            }
        }
        break;
    }

    if (*(int*)(self + 0x38) != 0)
    {
        delay->FUN_0115d990(0x100, *(int*)(ctx + 0x3000c),
                            *(int*)(ctx + 0x30010), 0);
        int tmp = *(int*)(ctx + 0x3000c);
        *(int*)(ctx + 0x3000c) = *(int*)(ctx + 0x30010);
        *(int*)(ctx + 0x30010) = tmp;
    }

    FUN_011544d0(self);

    *(int*)(sysQ + 0xc) = top;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011546f0
// ---------------------------------------------------------------------------
void __fastcall FUN_011546f0(int self)
{
    int* p = (int*)self;
    int z = 0;
    p[0] = z;
    p[1] = z;
    p[3] = z;
    p[2] = 1;
    ((float*)p)[4] = 0.0f;
    ((float*)p)[5] = 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x01154730
// ---------------------------------------------------------------------------
void ThreadObj::FUN_01154730(int value)
{
    volatile long* p = (volatile long*)((char*)this + 0x10);
    long old, nv;
    bool again;
    do
    {
        old = _InterlockedExchangeAdd(p, 0);
        nv = old | value;
        again = (_InterlockedCompareExchange(p, nv, old) != old);
    } while (again);
}

// ---------------------------------------------------------------------------
// @ 0x01154770
// ---------------------------------------------------------------------------
void ThreadObj::FUN_01154770(int value)
{
    value = ~value;
    volatile long* p = (volatile long*)((char*)this + 0x10);
    long old, nv;
    bool again;
    do
    {
        old = _InterlockedExchangeAdd(p, 0);
        nv = value & old;
        again = (_InterlockedCompareExchange(p, nv, old) != old);
    } while (again);
}

// ---------------------------------------------------------------------------
// @ 0x011547b0
// ---------------------------------------------------------------------------
void ThreadObj::FUN_011547b0(void)
{
    FUN_01154730(4);
    Wake();
    WaitForEnd((const unsigned int*)0x014ce70c, 0);
}

// ---------------------------------------------------------------------------
// @ 0x011547e0
// ---------------------------------------------------------------------------
void ThreadObj::FUN_011547e0(void)
{
    FUN_01154730(2);
    FUN_01154770(1);
    Wake();
}

// ---------------------------------------------------------------------------
// @ 0x01154800
// ---------------------------------------------------------------------------
void ThreadObj::FUN_01154800(void)
{
    volatile long* p = (volatile long*)((char*)this + 0x10);
    long f = _InterlockedExchangeAdd(p, 0);

    while ((f & 4) == 0)
    {
        if ((f & 2) != 0)
        {
            long old, nv;
            do
            {
                old = _InterlockedExchangeAdd(p, 0);
                nv = old & ~2;
            } while (_InterlockedCompareExchange(p, nv, old) != old);
        }
        else if ((f & 1) == 0)
        {
            void* dev = 0;
            if (FUN_0120ba6a((void*)0x014f8eb4, &dev) >= 0)
            {
                long long a = ((Obj64*)((char*)this + 8))->FUN_0068c140();
                long long b = FUN_0113ccf0(&dev);
                if (a != b)
                    FUN_01154730(1);
            }
        }
        int ms = 5000;
        FUN_00921df0(&ms);
        f = _InterlockedExchangeAdd(p, 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x011548c0
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_011548c0(int self)
{
    ((ThreadObj*)self)->FUN_01154800();
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011548d0
// ---------------------------------------------------------------------------
void ThreadObj::FUN_011548d0(void)
{
    FUN_01154770(-1);
    FUN_01154730(2);

    uint8_t params[0x18];
    ((ThreadParams*)params)->FUN_00922900();
    params[0x10] = 0;
    *(const char**)(params + 0x14) = "RwAudioCore Device WatchDog";
    void* prio = FUN_00922920();
    FUN_00922f30((void*)&FUN_011548c0, (void*)this, params, prio);
}

// ---------------------------------------------------------------------------
// @ 0x01154920  rw::audio::core::Mixer::HandleBufferStatusUnavailable
// ---------------------------------------------------------------------------
unsigned int rw::audio::core::Mixer::HandleBufferStatusUnavailable(int sampleBuffer, int system,
                                                                   int numSamples)
{
    float f = *(float*)(sampleBuffer + 0x28);
    if (f > *(float*)(sampleBuffer + 0x30))
        *(float*)(sampleBuffer + 0x30) = f;

    if (!(*(float*)(sampleBuffer + 0x2c) < *(float*)(sampleBuffer + 0x30)))
    {
        *(uint8_t*)(sampleBuffer + 0x45) = 0;
        return 0;
    }

    *(float*)(sampleBuffer + 0x2c) = (float)numSamples + *(float*)(sampleBuffer + 0x2c);
    int node = *(int*)((char*)this + 0x3000c);
    for (uint32_t i = 0; i < *(uint8_t*)(system + 0x21); i++)
    {
        void* dst = (void*)(*(int*)(node + 4) + *(uint16_t*)(node + 0xe) * i * 4);
        operator_new_arr(dst, 0, numSamples * 4);
    }
    *(int*)((char*)this + 0x30020) = numSamples;
    return 1;
}
