// RenderWare 4 core audio: SubMix pan/HPF/FIR/Butterworth filter callbacks (slice s01152b70).
// Built with VS2008 SP1 (cl 15.00.30729.01) at /arch:SSE /fp:fast: the bodies use scalar SSE
// (movss/addss/divss/comiss) plus x87 fcos/fsin, so they only match cl 15.00 with fast floats.
// The integer leaf helpers and a few straight-line float routines are byte-exact; the rest are
// the behaviour-equivalent reconstruction (chased to the closest codegen available).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// Globals / extern helpers
// ---------------------------------------------------------------------------
extern uint8_t g_015c3794[];                                            // 0x015c3794  channel index table
extern void* __cdecl operator_new_arr(void* dst, int zero, int size);   // 0x011e073e
extern void  __cdecl FUN_01134260(void* dst, void* src, float gain, int count);              // 0x01134260
extern void  __cdecl FUN_01160300(void* dst, void* src, float start, float delta, int count); // 0x01160300

// x87 transcendental helpers (the original issues fcos/fsin/fsqrt directly)
static float X87Cos(float a)  { float r; __asm { fld a } __asm { fcos }  __asm { fstp r } return r; }
static float X87Sin(float a)  { float r; __asm { fld a } __asm { fsin }  __asm { fstp r } return r; }
static float X87Sqrt(float a) { float r; __asm { fld a } __asm { fsqrt } __asm { fstp r } return r; }
// sin(a) / (i * pi), the denominator formed in x87 like the original table loop
static const float k_pi = 3.1415927f;
static float X87SinOverPi(float a, int i)
{
    float r;
    __asm { fld a }
    __asm { fsin }
    __asm { fild i }
    __asm { fmul k_pi }
    __asm { fdivp st(1), st }
    __asm { fstp r }
    return r;
}

// 2 * sqrt(sqrt(q)) * (sin(ang) * 0.70710653), all kept in x87 extended precision like the original
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

// thiscall callees that live elsewhere in the image (resolved by their FUN_<va> name)
struct SubMixObj
{
    uint32_t FUN_011529d0(void* ctx);              // 0x011529d0
    uint32_t FUN_011378a0(uint8_t slot);           // 0x011378a0
    uint32_t FUN_0115d180(void* dst, uint32_t n);  // 0x0115d180
};
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
    void FUN_01153940(float sr);           // 0x01153940
};
struct Biquad
{
    void FUN_011631c0(void* ctx, uint8_t channels);   // 0x011631c0
    void FUN_011633e0(void);                          // 0x011633e0
    void FUN_011604d0(void* a, int b);                // 0x011604d0
};

// ---------------------------------------------------------------------------
// RenderWare classes whose leaf statics mangle exactly
// ---------------------------------------------------------------------------
namespace rw { namespace audio { namespace core {

class Fir64
{
public:
    static int GetSize(int np, int nt);                                     // 0x01153770
    static Fir64* CreateInstance(int unused, int np, int nt, Fir64* self);  // 0x01153790
};

class Butterworth
{
public:
    static unsigned int GetSize(int order);                                        // 0x011538d0
    static Butterworth* CreateInstance(int unused, int order, Butterworth* self);  // 0x011538f0
};

}}}

// ---------------------------------------------------------------------------
// @ 0x01152b70
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01152b70(int self, int ctx)
{
    if (*(uint8_t*)(self + 0x166) && *(uint8_t*)(self + 0x165))
        return ((SubMixObj*)self)->FUN_011529d0((void*)ctx);

    uint8_t fmt = *(uint8_t*)(self + 0x152);
    int top = 0;
    int local8 = 0;
    uint32_t got = 0;
    *(int*)(self + 0x13c) = 0;

    if (fmt != 4 && fmt != 0)
    {
        if (*(float*)(self + 0x14c) != *(float*)(self + 0x15c) ||
            *(uint8_t*)(self + 0x153) != *(uint8_t*)(self + 0x21))
        {
            *(int*)(ctx + 0x30020) = 0;
            *(uint8_t*)(ctx + 0x3002c) = *(uint8_t*)(self + 0x153);
            *(float*)(ctx + 0x30024) = *(float*)(self + 0x14c);
            *(float*)(self + 0x15c) = *(float*)(self + 0x14c);
            *(uint8_t*)(self + 0x21) = *(uint8_t*)(self + 0x153);
            return 1;
        }
        int slot = *(uint8_t*)(self + 0x168);
        if (*(uint8_t*)(self + 0x55 + slot * 0xc) == 0)
        {
            do
            {
                if (*(uint8_t*)(self + 0x168) == *(uint8_t*)(self + 0x167))
                    break;
                uint8_t ns = *(uint8_t*)(self + 0x168) + 1;
                if (ns == 0x14) ns = 0;
                *(uint8_t*)(self + 0x168) = ns;
                slot = ns;
            } while (*(uint8_t*)(self + 0x55 + slot * 0xc) == 0);
        }
        if (*(uint8_t*)(self + 0x55 + slot * 0xc) == 1)
        {
            int obj = *(int*)(self + 0x148);
            int sysQ = *(int*)(*(int*)(self + 4));
            top = *(int*)(sysQ + 0xc);
            local8 = top - ((*(uint16_t*)(self + 0x150) + 0x7f) & 0xffffff80);
            *(int*)(sysQ + 0xc) = local8;
            *(int*)(self + 0x13c) = obj;
            uint32_t avail = ((SubMixObj*)obj)->FUN_011378a0(*(uint8_t*)(self + (slot + 7) * 0xc));
            uint32_t lim = *(uint16_t*)(self + 0x160);
            int cnt = ((int)lim < (int)avail) ? (int)lim : (int)avail;
            got = ((SubMixObj*)obj)->FUN_0115d180((void*)*(int*)(ctx + 0x30010), (uint32_t)cnt);
            int tmp = *(int*)(ctx + 0x3000c);
            *(int*)(ctx + 0x3000c) = *(int*)(ctx + 0x30010);
            *(int*)(ctx + 0x30010) = tmp;
            *(uint32_t*)(ctx + 0x30020) = got;
            *(uint8_t*)(ctx + 0x3002c) = *(uint8_t*)(self + 0x153);
            *(float*)(ctx + 0x30024) = *(float*)(self + 0x14c);
            *(int*)(self + 0x158) += (int)got;
            *(int*)(self + 0x50 + slot * 0xc) += (int)got;
            if (avail == got)
            {
                int drain = 0;
                do
                {
                    if (*(uint8_t*)(self + 0x55 + slot * 0xc) != 1) break;
                    *(uint8_t*)(self + 0x55 + slot * 0xc) = 2;
                    uint8_t ns = *(uint8_t*)(self + 0x168) + 1;
                    if (ns == 0x14) ns = 0;
                    *(uint8_t*)(self + 0x168) = ns;
                    slot = ns;
                    if (*(int*)(self + 0x13c) != 0 &&
                        *(uint8_t*)(self + 0x55 + slot * 0xc) == 1)
                        drain = (int)((SubMixObj*)*(int*)(self + 0x13c))->
                            FUN_011378a0(*(uint8_t*)(self + (slot * 3 + 0x15) * 4));
                } while (drain == 0);
            }
        }
    }

    if (*(int*)(self + 0x13c) != 0)
    {
        *(int*)(self + 0x13c) = 0;
        if (local8 != 0)
            *(int*)(*(int*)(*(int*)(self + 4)) + 0xc) = top;
    }
    *(uint8_t*)(ctx + 0x3002c) = *(uint8_t*)(self + 0x21);
    *(float*)(ctx + 0x30024) = *(float*)(self + 0x15c);

    if (got == 0)
    {
        if (*(uint16_t*)(self + 0x160) != 0)
            return 0;
        *(int*)(ctx + 0x30020) = 0;
        return 1;
    }

    int node = *(int*)(ctx + 0x3000c);
    uint8_t n = *(uint8_t*)(ctx + 0x3002c);
    uint8_t lim = *(uint8_t*)(self + 0x164);
    if (lim <= n) n = lim;
    uint32_t stride = *(uint16_t*)(node + 0xe);
    float* data = (float*)*(int*)(node + 4);
    float* dst = (float*)(self + *(uint16_t*)(self + 0x162));
    for (int k = 0; k < (int)n; k++)
        dst[k] = data[stride * k + got - 1];
    *(uint8_t*)(self + 0x165) = 1;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01152ef0
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01152ef0(int self, int ctx, uint8_t flag)
{
    int node10 = *(int*)(ctx + 0x30010);
    uint8_t* tbl = g_015c3794 + *(uint8_t*)(self + 0x70) * 6;
    int chans = *(uint8_t*)(self + 0x21);

    if (flag)
    {
        for (unsigned i = 0; i < (unsigned)chans; i++)
            *(float*)(self + 0x58 + i * 4) = *(float*)(self + 0x28 + tbl[i] * 8);
    }

    uint32_t srcBase = *(uint32_t*)(*(int*)(ctx + 0x3000c) + 4);
    for (unsigned ch = 0; ch < (unsigned)chans; ch++)
    {
        float target = *(float*)(self + 0x28 + tbl[ch] * 8);
        float* cur = (float*)(self + 0x58 + ch * 4);
        void* dst = (void*)(*(int*)(node10 + 4) + *(uint16_t*)(node10 + 0xe) * ch * 4);
        FUN_01160300(dst, (void*)srcBase, *cur, (target - *cur) * 0.015625f, 0x100);
        *cur = target;
    }

    int tmp = *(int*)(ctx + 0x30010);
    *(int*)(ctx + 0x30010) = *(int*)(ctx + 0x3000c);
    *(int*)(ctx + 0x3000c) = tmp;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01153060
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01153060(int self, int ctx)
{
    uint8_t* tbl = (uint8_t*)(self + *(uint16_t*)(self + 0x24));
    int count = *(int*)(ctx + 0x30020);
    uint32_t chans = *(uint8_t*)(ctx + 0x3002c);

    if (count == 0)
        *(uint8_t*)(self + 0x20) = *(uint8_t*)(ctx + 0x3002c);

    uint32_t limit = *(uint8_t*)(self + 0x21);
    uint32_t m = chans < limit ? chans : limit;

    int identity = 1;
    for (uint32_t i = 0; i < m; i++)
    {
        if ((int8_t)tbl[i] != (int)i)
        {
            identity = 0;
            break;
        }
    }

    if (!identity)
    {
        if (count != 0)
        {
            int node0c = *(int*)(ctx + 0x3000c);
            int node10 = *(int*)(ctx + 0x30010);
            for (uint32_t ch = 0; ch < limit; ch++)
            {
                void* dst = (void*)(*(int*)(node10 + 4) + *(uint16_t*)(node10 + 0xe) * ch * 4);
                uint32_t idx = (uint32_t)(int8_t)tbl[ch];
                if (idx < chans)
                    FUN_01134260(dst, (void*)(*(int*)(node0c + 4) +
                                  *(uint16_t*)(node0c + 0xe) * idx * 4), 1.0f, count);
                else
                    operator_new_arr(dst, 0, count * 4);
            }
        }
        int tmp = *(int*)(ctx + 0x30010);
        *(int*)(ctx + 0x30010) = *(int*)(ctx + 0x3000c);
        *(int*)(ctx + 0x3000c) = tmp;
    }
    else
    {
        int node0c = *(int*)(ctx + 0x3000c);
        for (uint32_t ch = chans; ch < limit; ch++)
            operator_new_arr((void*)(*(int*)(node0c + 4) +
                              *(uint16_t*)(node0c + 0xe) * ch * 4), 0, count * 4);
    }

    *(uint8_t*)(ctx + 0x3002c) = *(uint8_t*)(self + 0x21);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011531c0  rw::audio::core::Pan3D::Update3D
// ---------------------------------------------------------------------------
struct Pan3D
{
    void FUN_011531c0(float ang, float q);   // 0x011531c0
    void FUN_01153460(float ang);            // 0x01153460
};

void Pan3D::FUN_011531c0(float ang, float q)
{
    float c = X87Cos(ang);
    float sq = X87Sqrt(q);
    float A = sq - 1.0f;
    float B = sq + 1.0f;
    float Ac = A * c;
    float Bc = B * c;
    float f2 = X87F2(q, ang);
    float inv = 1.0f / ((B + Ac) + f2);
    *(float*)((char*)this + 0x9c) = ((Bc + A) * inv) * -2.0f;
    *(float*)((char*)this + 0xa0) = ((B + Ac) - f2) * inv;
    *(float*)((char*)this + 0xa4) = (((B - Ac) + f2) * inv) * sq;
    *(float*)((char*)this + 0xa8) = (((A - Bc) * inv) * sq) * 2.0f;
    *(float*)((char*)this + 0xac) = (((B - Ac) - f2) * inv) * sq;
}

// ---------------------------------------------------------------------------
// @ 0x011532b0
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_011532b0(int self, int ctx)
{
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);
    float phase = (*(float*)(self + 0x28) / sr) * 6.2831855f;

    if (!(0.003141593f >= phase) && *(float*)(self + 0x30) != 1.0f)
    {
        if (*(int*)(self + 0x98) == 0)
            *(int*)(self + 0x98) = 1;
        if (phase > 3.138451f)
            phase = 3.138451f;
        if (phase != *(float*)(self + 0xb0) || *(float*)(self + 0x30) != *(float*)(self + 0xb4))
        {
            ((Pan3D*)self)->FUN_011531c0(phase, *(float*)(self + 0x30));
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
        int tmp = *(int*)(ctx + 0x3000c);
        *(int*)(ctx + 0x3000c) = *(int*)(ctx + 0x30010);
        *(int*)(ctx + 0x30010) = tmp;
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
// @ 0x01153460  rw::audio::core::Pan3D::Update2D
// ---------------------------------------------------------------------------
void Pan3D::FUN_01153460(float ang)
{
    float c = X87Cos(ang);
    float s = X87Sin(ang) * 0.5f;
    float d = 1.0f + s;
    float inv = 1.0f / d;
    *(float*)((char*)this + 0x90) = (c * -2.0f) * inv;
    float e = 1.0f - c;
    float f = e / (d * 2.0f);
    *(float*)((char*)this + 0x94) = (1.0f - s) * inv;
    *(float*)((char*)this + 0x98) = f;
    *(float*)((char*)this + 0x9c) = e * inv;
    *(float*)((char*)this + 0xa0) = f;
}

// ---------------------------------------------------------------------------
// @ 0x01153500
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01153500(int self, int ctx)
{
    float phase = (*(float*)(self + 0x28) /
                   *(float*)(*(int*)(ctx + 0x30018) + 0xc)) * 6.2831855f;

    if (phase >= 3.138451f)
    {
        if (*(float*)(self + 0xa4) < 3.138451f)
        {
            for (uint32_t ch = 0; ch < *(uint8_t*)(self + 0x21); ch++)
                ((Filter*)(self + 0x30 + ch * 0x10))->FUN_0114f4f0();
        }
        *(float*)(self + 0xa4) = phase;
        return 1;
    }

    if (phase < 0.003141593f)
        phase = 0.003141593f;
    if (phase != *(float*)(self + 0xa4))
    {
        ((Pan3D*)self)->FUN_01153460(phase);
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

// ---------------------------------------------------------------------------
// @ 0x01153630  rw::audio::core::HpFilter::BuildTable
// ---------------------------------------------------------------------------
struct HpFilter
{
    void FUN_01153630(float phase);   // 0x01153630
};

void HpFilter::FUN_01153630(float phase)
{
    float* tab = (float*)((char*)this + 0x30);
    void* bw = (char*)this + *(uint16_t*)((char*)this + 0xb8);
    for (int i = -32; i < 0; i++)
        tab[i + 32] = X87SinOverPi((float)i * phase, i);
    *(float*)((char*)this + 0xb0) = phase * 0.31830987f;
    ((Biquad*)bw)->FUN_011604d0(tab, 0x40);
}

// ---------------------------------------------------------------------------
// @ 0x011536b0
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_011536b0(int self, int ctx)
{
    int bw = self + *(uint16_t*)(self + 0xb8);
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);
    float phase = (*(float*)(self + 0x28) / sr) * 6.2831855f;

    if (phase >= 3.1415927f)
    {
        if (*(float*)(self + 0xb4) < 3.1415927f)
            ((ButterworthObj*)bw)->FUN_01160540();
        *(float*)(self + 0xb4) = phase;
        return 1;
    }

    if (phase < 0.0f)
        phase = 0.0f;
    if (phase != *(float*)(self + 0xb4))
    {
        ((HpFilter*)self)->FUN_01153630(phase);
        *(float*)(self + 0xb4) = phase;
    }
    ((ButterworthObj*)bw)->FUN_01160790((void*)ctx, (void*)(self + 0x30));
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01153770  rw::audio::core::Fir64::GetSize
// ---------------------------------------------------------------------------
int rw::audio::core::Fir64::GetSize(int np, int nt)
{
    return np * nt * 4 + 8;
}

// ---------------------------------------------------------------------------
// @ 0x01153790  rw::audio::core::Fir64::CreateInstance
// ---------------------------------------------------------------------------
rw::audio::core::Fir64* rw::audio::core::Fir64::CreateInstance(int unused, int np, int nt, Fir64* self)
{
    int buf = ((int)self + 0xf) & ~7;
    *(uint16_t*)self = (uint16_t)(buf - (int)self);
    operator_new_arr((void*)buf, 0, np * nt * 4);
    *(uint16_t*)((char*)self + 4) = (uint16_t)nt;
    *(uint16_t*)((char*)self + 2) = (uint16_t)(nt * 4);
    *(uint8_t*)((char*)self + 6) = (uint8_t)np;
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x011537e0
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_011537e0(int self, int ctx)
{
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);
    float nyq = sr * 0.5f;
    float margin = nyq * 0.01f;
    float hi = nyq - margin;
    int bw = self + *(uint16_t*)(self + 0x48);

    if (*(float*)(self + 0x28) > hi)
    {
        if (*(float*)(self + 0x38) <= hi)
            ((ButterworthObj*)bw)->FUN_01160dc0();
        *(float*)(self + 0x38) = *(float*)(self + 0x28);
        return 1;
    }

    if (*(float*)(self + 0x28) < margin)
        *(float*)(self + 0x28) = margin;
    if (*(float*)(self + 0x28) != *(float*)(self + 0x38) ||
        *(float*)(self + 0x30) != *(float*)(self + 0x40))
    {
        int order = (int)*(float*)(self + 0x30);
        ((ButterworthObj*)bw)->FUN_01160910(*(float*)(self + 0x28), order, sr, 0);
        *(float*)(self + 0x38) = *(float*)(self + 0x28);
        *(float*)(self + 0x40) = *(float*)(self + 0x30);
    }
    ((ButterworthObj*)bw)->FUN_01160e00((void*)ctx);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011538d0  rw::audio::core::Butterworth::GetSize
// ---------------------------------------------------------------------------
unsigned int rw::audio::core::Butterworth::GetSize(int order)
{
    int e = order * 0x14;
    return (unsigned int)(((e + 0x37) & ~7) + e);
}

// ---------------------------------------------------------------------------
// @ 0x011538f0  rw::audio::core::Butterworth::CreateInstance
// ---------------------------------------------------------------------------
rw::audio::core::Butterworth* rw::audio::core::Butterworth::CreateInstance(int unused, int order, Butterworth* self)
{
    int bufA = ((int)self + 0x37) & ~7;
    *(uint16_t*)((char*)self + 0x2c) = (uint16_t)(bufA - (int)self);
    int rows = order * 0x14;
    int bufB = (bufA + rows + 7) & ~7;
    *(uint16_t*)((char*)self + 0x2e) = (uint16_t)(bufB - (int)self);
    *(uint32_t*)((char*)self + 0x28) = (uint8_t)order;
    operator_new_arr((void*)bufA, 0, rows);
    operator_new_arr((void*)bufB, 0, rows);
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x01153a00
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_01153a00(int self, int ctx)
{
    if (*(float*)(self + 0x28) >= 20.0f)
    {
        if (*(int*)(self + 0xa0) == 1)
        {
            ((Biquad*)(self + 0x40))->FUN_011633e0();
            *(int*)(self + 0xa0) = 0;
        }
        *(float*)(self + 0x90) = *(float*)(self + 0x28);
        return 1;
    }

    if (*(int*)(self + 0xa0) == 0)
        *(int*)(self + 0xa0) = 1;
    float sr = *(float*)(*(int*)(ctx + 0x30018) + 0xc);
    if (*(float*)(self + 0x28) != *(float*)(self + 0x90) ||
        *(float*)(self + 0x30) != *(float*)(self + 0x94) ||
        *(float*)(self + 0x38) != *(float*)(self + 0x98) ||
        sr != *(float*)(self + 0x9c))
    {
        ((HpSelf*)self)->FUN_01153940(sr);
        *(float*)(self + 0x90) = *(float*)(self + 0x28);
        *(float*)(self + 0x9c) = sr;
        *(float*)(self + 0x94) = *(float*)(self + 0x30);
        *(float*)(self + 0x98) = *(float*)(self + 0x38);
    }
    ((Biquad*)(self + 0x40))->FUN_011631c0((void*)ctx, *(uint8_t*)(self + 0x21));
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01153b00
// ---------------------------------------------------------------------------
void* __fastcall FUN_01153b00(void* self)
{
    operator_new_arr(self, 0, 0x30);
    return self;
}
