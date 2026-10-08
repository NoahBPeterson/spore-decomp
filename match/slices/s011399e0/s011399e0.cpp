// Slice s011399e0: RenderWare 4 core audio -- ReverbModel1 / ReverbIR1 (EQ tables, FastFirEngine).
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG; none of these are byte-exact from a single-object
// compile, so this is the complete behaviour-equivalent reconstruction (offset-addressed types).
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <xmmintrin.h>
#include <math.h>

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

template <class T> static inline T& A(void* p, int off) { return *(T*)((char*)p + off); }

namespace rw { namespace audio { namespace core {

struct DelayLine {
    int Init(int a, int b, int size);   // 0x0114d7b0  thiscall, ret 0xc
};
struct FastFirEngine {
    int  Reset();                                    // 0x0114e580
    int  Configure(int, int, int, int, int, int, int);// 0x0114e5e0
    int  FUN_0114e210(int, float);                   // 0x0114e210
    int  FUN_0114e230(int);                          // 0x0114e230
    int  FUN_0114e300();                             // 0x0114e300
    int  FUN_0114e340();                             // 0x0114e340
    int  FUN_0114e370(int, int);                     // 0x0114e370
};

// Stub owner for the __thiscall ReverbModel1 / ReverbIR1 helpers (real class only partly known).
struct RevObj {
    void   F_9e0(int, float);        // 0x011399e0
    bool   F_d60(float*);            // 0x01139d60
    RevObj* F_e10();                 // 0x01139e10
    void   F_eb0();                  // 0x01139eb0
    void   F_f20();                  // 0x01139f20
    int    F_fe0(void*);             // 0x01139fe0
    void   F_7a0(int);               // 0x0113a7a0
    RevObj* F_840(u8);               // 0x0113a840
};
} } } // namespace rw::audio::core

using namespace rw::audio::core;

extern const float g_revA[];              // 0x014b2374
extern const float g_revB[];              // 0x014b232c
extern const float g_freqTab[];           // 0x014b23e0 (shared frequency table)

extern "C" {
int  FUN_0114d730(void*);                 // 0x0114d730  thiscall, ret
int  FUN_0114d770(void*);                 // 0x0114d770  thiscall, ret
void FUN_0114d9d0(void* ctx, int);        // 0x0114d9d0  thiscall ctx, ret 4
int  FUN_0114d840(void* ctx, int);        // 0x0114d840  thiscall ctx, ret 4
int  FUN_0114dca0(void*);                 // 0x0114dca0  thiscall, ret
int  FUN_0114dcb0(float, int, float, float); // 0x0114dcb0
int  FUN_0114dce0(void*);                 // 0x0114dce0  thiscall, ret
int  FUN_0114e210(void* ctx, int a, float b); // 0x0114e210 thiscall-ish
int  FUN_0114e230(void*);                 // 0x0114e230  thiscall
char FUN_0112d8e0(void*, void*, void*, void*, const char*, int, int); // AddTimer
void operator_delete__(void*);            // 0x00f47380
void EA_Audio_sys_gui(void);              // 0x00c2e4e0
double log2(double);
}

namespace rw { namespace audio { namespace core {

// @ 0x011399e0  ReverbModel1::ConfigureEq (this, outTable, sampleRate)
void RevObj::F_9e0(int out, float sr)
{
    void* p = this;
    float blend;
    int idx;
    if (sr < 50000.0f) {
        if (sr > 10000.0f) {
            if (sr > 25000.0f) { blend = (50000.0f - sr) * 4e-05f; idx = 1; }
            else { blend = (25000.0f - sr) * 6.666667e-05f; idx = 0; }
        } else { sr = 10000.0f; blend = (25000.0f - sr) * 6.666667e-05f; idx = 0; }
    } else { sr = 50000.0f; blend = (50000.0f - sr) * 4e-05f; idx = 1; }
    float inv = 1.0f - blend;
    float tab[17];
    tab[0] = 12.5f; tab[1] = 25.0f; tab[2] = 37.5f; tab[3] = 50.0f;
    tab[4] = 62.5f; tab[5] = 75.0f; tab[6] = 87.5f; tab[7] = 100.0f;
    tab[8]  = g_revA[idx * 0x12] * inv + g_revB[idx * 0x12] * blend;
    tab[9]  = g_revA[idx * 0x12 + 1] * inv + g_revB[idx * 0x12 + 1] * blend;
    tab[10] = g_revA[idx * 0x12 + 2] * inv + g_revB[idx * 0x12 + 2] * blend;
    tab[11] = g_revA[idx * 0x12 + 3] * inv + g_revB[idx * 0x12 + 3] * blend;
    tab[12] = g_revA[idx * 0x12 + 4] * inv + g_revB[idx * 0x12 + 4] * blend;
    tab[13] = g_revA[idx * 0x12 + 5] * inv + g_revB[idx * 0x12 + 5] * blend;
    tab[14] = g_revA[idx * 0x12 + 6] * inv + g_revB[idx * 0x12 + 6] * blend;
    tab[15] = g_revA[idx * 0x12 + 7] * inv + g_revB[idx * 0x12 + 7] * blend;
    tab[16] = g_revA[idx * 0x12 + 8] * inv + g_revB[idx * 0x12 + 8] * blend;

    float* pf = (float*)((char*)p + 0x164);
    for (int i = 0; i < 6; i++, pf++) {
        int k = 0;
        while (k < 16 && tab[k] < *pf) k++;
        float f = (tab[k] - *pf) * 0.08f;
        *(float*)(out + i * 4) = (1.0f - f) * tab[k + 9] + tab[k + 8] * f;
    }
    if (A<float>(p, 0x38) != A<float>(p, 0x160)) {
        float f = *(float*)(out + 0x14) + 0.001f;
        if (A<float>(p, 0x38) < f) A<float>(p, 0x38) = f;
        int* pi = (int*)((char*)p + 0x17c);
        for (int i = 0; i < 6; i++, pi++) {
            FUN_0114dca0((char*)p + 0x1dc + i * 0x24);
            FUN_0114d840((char*)p + 0x2b4 + i * 0x3c, *pi + 3);
            FUN_0114d9d0((char*)p + 0x2b4 + i * 0x3c, *pi + 1);
            *(float*)(out + i * 4) = *(float*)(out + i * 4) / A<float>(p, 0x38);
        }
    }
}

// @ 0x01139d60  ReverbModel1 (this, out6)
bool RevObj::F_d60(float* out)
{
    void* p = this;
    if (A<float>(p, 0x28) <= 0.366f && A<float>(p, 0x28) != 0.366f)
        A<float>(p, 0x28) = 0.366f;
    float f = 1.0f - 0.366f / A<float>(p, 0x28);
    out[0] = (1.0f - A<float>(p, 0x1ac)) * f;
    out[1] = (1.0f - A<float>(p, 0x1b0)) * f;
    out[2] = (1.0f - A<float>(p, 0x1b4)) * f;
    out[3] = (1.0f - A<float>(p, 0x1b8)) * f;
    out[4] = (1.0f - A<float>(p, 0x1bc)) * f;
    out[5] = (1.0f - A<float>(p, 0x1c0)) * f;
    return true;
}

// @ 0x01139e10  ReverbModel1 ctor
RevObj* RevObj::F_e10()
{
    void* p = this;
    *(void**)p = (void*)0x14b3dd4;
    for (int i = 0; i < 3; i++) FUN_0114e230((char*)p + 0x40 + i * 0x18);
    for (int i = 0; i < 3; i++) FUN_0114d730((char*)p + 0x88 + i * 0x3c);
    A<void*>(p, 0xc) = 0;
    for (int i = 0; i < 6; i++) FUN_0114dce0((char*)p + 0x1dc + i * 0x24);
    for (int i = 0; i < 6; i++) FUN_0114d730((char*)p + 0x2b4 + i * 0x3c);
    return this;
}

// @ 0x01139eb0  ReverbModel1 dtor
void RevObj::F_eb0()
{
    void* p = this;
    for (int i = 0; i < 6; i++) FUN_0114d770((char*)p + 0x1e0 + i * 0x3c);
    EA_Audio_sys_gui();
    for (int i = 0; i < 3; i++) FUN_0114d770((char*)p + 0xc4 + i * 0x3c);
    *(void**)p = (void*)0x14bc0fc;
}

// @ 0x01139f20  ReverbModel1::UpdateGain
void RevObj::F_f20()
{
    void* p = this;
    float max1 = 0.0f, max2 = 0.0f;
    int n = A<u8>(p, 0x439);
    for (int i = 0; i < n; i++)
        if (max1 < A<float>(p, 0x41c + i * 4)) max1 = A<float>(p, 0x41c + i * 4);
    int mx = 0;
    for (int i = 0; i < n; i++)
        if (mx < A<int>(p, 0x428 + i * 4)) mx = A<int>(p, 0x428 + i * 4);
    double v6 = (double)A<int>(p, 0x190) - (double)A<int>(p, 0x190) * 10.0 / (0.3010299956639812 * log2((double)A<float>(p, 0x1c4)));
    double v1 = (double)mx - (double)mx * 10.0 / (0.3010299956639812 * log2((double)max1));
    double dv = (v6 + v1) - (double)A<float>(p, 0x18);
    A<float>(A<void*>(p, 8), 0x28) = (float)(dv + (double)A<float>(A<void*>(p, 8), 0x28));
    A<float>(p, 0x18) = (float)(v6 + v1);
}

// @ 0x01139fe0  ReverbModel1 timer-driven configure
int RevObj::F_fe0(void* sys)
{
    void* p = this;
    float sr = A<float>(sys, 0xc0);
    float g = A<float>(p, 0x30);
    bool b3 = false;
    bool b4 = false;
    if (g == A<float>(p, 0x15c)) {
        if (sr == A<float>(p, 0x154)) {
            if (A<float>(p, 0x38) != A<float>(p, 0x160))
                F_9e0((int)((char*)p + 0x1ac), sr);
            F_d60((float*)((char*)p + 0x1c4));
        } else {
            extern int FUN_01139920(float*, int*, float);
            FUN_01139920((float*)((char*)p + 0x164), (int*)((char*)p + 0x17c), sr);
            F_9e0((int)((char*)p + 0x1ac), sr);
            F_d60((float*)((char*)p + 0x1c4));
            b3 = true;
        }
    } else {
        if (g > 83.3f || g < 2.0f) A<float>(p, 0x30) = 83.3f;
        g = A<float>(p, 0x30) * 0.8f;
        float hi = g * 1.5f;
        if (hi > 100.0f) { g = 66.666664f; hi = 100.0f; A<float>(p, 0x30) = 83.333336f; }
        float step = (hi - g) * 0.2f;
        A<float>(p, 0x164) = g;
        A<float>(p, 0x168) = step + g;
        A<float>(p, 0x16c) = (step + g) + step;
        A<float>(p, 0x170) = ((step + g) + step) + step;
        A<float>(p, 0x174) = (((step + g) + step) + step) + step;
        A<float>(p, 0x178) = hi;
        extern int FUN_01139920(float*, int*, float);
        FUN_01139920((float*)((char*)p + 0x164), (int*)((char*)p + 0x17c), sr);
        F_9e0((int)((char*)p + 0x1ac), sr);
        F_d60((float*)((char*)p + 0x1c4));
        b4 = true;
    }
    int* pi = (int*)((char*)p + 0x17c);
    for (int i = 0; i < 6; i++, pi++) {
        FUN_0114dcb0(-(float)pi[0xc], pi[0x12] ^ 0x80000000, -(float)pi[0xc], 0.16666667f);
        if (A<int>((char*)p + 0x2b4 + i * 0x3c, 0x28) != *pi + 1) {
            if (FUN_0114d840((char*)p + 0x2b4 + i * 0x3c, *pi + 3) == 0) return 0;
            FUN_0114d9d0((char*)p + 0x2b4 + i * 0x3c, *pi + 1);
        }
    }
    float fVar1 = sr;
    if (A<char>(p, 0x438) == 0 || b3) {
        char c = A<char>(p, 0x21);
        if (c == 1) {
            A<u8>(p, 0x439) = 1;
            A<float>(p, 0x41c) = 0.69999999f;
            A<int>(p, 0x428) = _mm_cvtss_si32(_mm_load_ss(&(fVar1 = fVar1 * 0.006f)));
        } else if (c == 2 || c == 4) {
            A<float>(p, 0x41c) = 0.63f;
            A<u8>(p, 0x439) = 2;
            A<float>(p, 0x420) = 0.77700001f;
            A<int>(p, 0x428) = _mm_cvtss_si32(_mm_load_ss(&(fVar1 = sr * 0.006666667f)));
            fVar1 = sr * 0.0053999997f;
            A<int>(p, 0x42c) = _mm_cvtss_si32(_mm_load_ss(&fVar1));
        } else {
            A<float>(p, 0x41c) = 0.63f;
            A<u8>(p, 0x439) = 3;
            fVar1 = sr * 0.006666667f;
            A<int>(p, 0x428) = _mm_cvtss_si32(_mm_load_ss(&fVar1));
            A<float>(p, 0x420) = 0.69999999f;
            A<float>(p, 0x424) = 0.77700001f;
            fVar1 = sr * 0.006f;
            A<int>(p, 0x42c) = _mm_cvtss_si32(_mm_load_ss(&fVar1));
            fVar1 = sr * 0.0053999997f;
            A<int>(p, 0x430) = _mm_cvtss_si32(_mm_load_ss(&fVar1));
        }
        int* q = (int*)((char*)p + 0x428);
        for (int i = 0; i < (int)A<u8>(p, 0x439); i++, q++) {
            FUN_0114e210((char*)p + 0x88 + i * 0x3c, q[-3], A<float>(p, 0x434));
            if (FUN_0114d840((char*)p + 0x88 + i * 0x3c, *q + 2) == 0) return 0;
            FUN_0114d9d0((char*)p + 0x88 + i * 0x3c, *q);
        }
        A<char>(p, 0x438) = 1;
    } else if (b4) {
        int* q = (int*)((char*)p + 0x428);
        for (int i = 0; i < (int)A<u8>(p, 0x439); i++, q++)
            FUN_0114d9d0((char*)p + 0x88 + i * 0x3c, *q);
    }
    A<float>(p, 0x158) = A<float>(p, 0x28);
    A<float>(p, 0x154) = sr;
    A<float>(p, 0x15c) = A<float>(p, 0x30);
    A<float>(p, 0x160) = A<float>(p, 0x38);
    F_f20();
    return 1;
}

// @ 0x0113a4c0  ReverbModel1 timer callback
void __cdecl FUN_0113a4c0(void* self)
{
    if (A<float>(self, 0x28) > 0.0f) {
        if (A<float>(self, 0x28) != A<float>(self, 0x158) ||
            A<float>(self, 0x30) != A<float>(self, 0x15c) ||
            A<float>(self, 0x38) != A<float>(self, 0x160) ||
            A<float>(A<void*>(self, 4), 0xc0) != A<float>(self, 0x154))
            ((RevObj*)self)->F_fe0(A<void*>(self, 4));
        return;
    }
    if (A<float>(self, 0x158) <= 0.0f) return;
    for (int i = 0; i < 6; i++) {
        FUN_0114d9d0((char*)self + 0x2b4 + i * 0x3c, A<int>(self, 0x17c + i * 4) + 1);
        FUN_0114dca0((char*)self + 0x1dc + i * 0x24);
    }
    for (int i = 0; i < (int)A<u8>(self, 0x439); i++)
        FUN_0114d9d0((char*)self + 0x88 + i * 0x3c, A<int>(self, 0x428 + i * 4));
}

// @ 0x0113a5c0  ReverbModel1::CreateInstance
bool __cdecl FUN_0113a5c0(void* self)
{
    if (self) ((RevObj*)self)->F_e10();
    char ch = A<char>(self, 0x21);
    A<void*>(self, 0xc) = (char*)self + 0x28;
    A<char>(self, 0x43a) = 0;
    u8 mode;
    if (ch == 1) mode = 1;
    else if (ch == 2 || ch == 4) mode = 2;
    else mode = 3;
    A<u8>(self, 0x439) = mode;
    A<float>(self, 0x30) = 15.0f;
    A<float>(self, 0x28) = 0.0f;
    A<float>(self, 0x38) = 1.0f;
    A<float>(self, 0x158) = 0.0f;
    A<float>(self, 0x154) = 0.0f;
    A<float>(self, 0x160) = 1.0f;
    for (int i = 0; i < 6; i++)
        ((DelayLine*)((char*)self + 0x2b4 + i * 0x3c))->Init(1, 0, A<int>(self, 0x1e4 + i * 0x24));
    for (int i = 0; i < (int)mode; i++)
        ((DelayLine*)((char*)self + 0x88 + i * 0x3c))->Init(1, 0, A<int>(self, 0x48 + i * 0x18));
    char c = A<char>(self, 0x21);
    float f = (c <= 4) ? (float)c : (float)c - 1.0f;
    A<float>(self, 0x434) = 2.0f / f;
    A<char>(self, 0x438) = 0;
    if (FUN_0112d8e0((void*)((char*)A<void*>(self, 4) + 0x60), (char*)self + 0x13c,
                     (void*)&FUN_0113a4c0, self, "ReverbModel1", 1, 1) != 0)
        return false;
    A<char>(self, 0x43a) = 1;
    return true;
}

// @ 0x0113a770  ReverbIR1::StopReverbHandler
int __cdecl FUN_0113a770(void* rec)
{
    void* self = A<void*>(rec, 4);
    ((FastFirEngine*)((char*)self + 0x50))->Reset();
    A<int>(self, 0x4c) = 0;
    A<int>(self, 0xe8) = 0;
    return 8;
}

// @ 0x0113a7a0  ReverbIR1::Configure
void RevObj::F_7a0(int idx)
{
    void* p = this;
    char* i1 = (char*)p + idx * 0x28;
    if (A<int>(p, 0x4c + idx * 0x28) != 0)
        ((FastFirEngine*)((char*)p + 0x50 + idx * 0x94))->Reset();
    int i2 = A<int>(p, 0x24) + 0x30;
    A<int>(i1, 0x4c) = i2;
    ((FastFirEngine*)((char*)p + 0x50 + idx * 0x94))->Configure(
        0x100, A<int>(i1, 0x3c), A<int>(i1, 0x40), A<int>(i1, 0x44),
        A<int>(i1, 0x30), A<int>(i1, 0x34), i2);
    float f = (float)(A<int>(i1, 0x3c) - 0x100);
    A<float>(p, 0x14) = f;
    f = (float)A<int>(i1, 0x34) + f;
    A<float>(A<void*>(p, 8), 0x28) = (f - A<float>(p, 0x18)) + A<float>(A<void*>(p, 8), 0x28);
    A<float>(p, 0x18) = f;
}

// @ 0x0113a840  ReverbIR1 deleting destructor
RevObj* RevObj::F_840(u8 flags)
{
    void* p = this;
    ((FastFirEngine*)((char*)p + 0x50))->FUN_0114e340();
    *(void**)p = (void*)0x14bc0fc;
    if (flags & 1) operator_delete__(p);
    return this;
}

} } } // namespace rw::audio::core
