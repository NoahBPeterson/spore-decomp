// src/game/plugins/reverbmodel1.cpp.cpp -- migrated from slice(s) s011388f0, s011399e0 by tools/migrate/rewrite.py
// Object file: plugins/reverbmodel1.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/TimerManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  FUN_0114dca0(void*);                 // 0x0114dca0  cdecl, ret
extern "C" double log2(double);
#include <xmmintrin.h>
#include <math.h>
#include "rw/audio/core/DecoderRegistry.h"
#include "rw/audio/core/PlugIn.h"
#include "rw/audio/core/StreamPool.h"
#include "rw/audio/core/SubMix.h"
#include "rw/audio/core/System.h"
#include "rw/audio/core/TimerHandle.h"

// ---- items of slice s011399e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_revA[];              // 0x014b2374
extern const float g_revB[];              // 0x014b232c
extern "C" void* memset(void*, int, unsigned);       // 0x011e073e  msvcr90!memset
typedef unsigned char u8;
template <class T> static inline T& A(void* p, int off) { return *(T*)((char*)p + off); }
namespace rw {
namespace audio {
namespace core {
class DelayLine { public:
    int  Init(int a, int b, int size);   // 0x0114d7b0  thiscall, ret 0xc
    void FUN_0114d730();                 // 0x0114d730  ctor
    void FUN_0114d770();                 // 0x0114d770  Release
    void FUN_0114d9d0(int);              // 0x0114d9d0  Reset, ret 4
    int  FUN_0114d840(int);              // 0x0114d840  Resize, ret 4
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class CombFilter { public:
    void FUN_0114dcb0(float, int, float, float); // 0x0114dcb0 SetGains, ret 0x10
    void FUN_0114dce0();                 // 0x0114dce0  ctor
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class AllPassFilter { public:
    void FUN_0114e230();                 // 0x0114e230  ctor
    void FUN_0114e210(float, float);     // 0x0114e210  ret 8
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct TimerMgr {
    char AddTimer(void*, void*, void*, const char*, int, int); // 0x0112d8e0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct RevObj {
    int    F_9e0(int, float);        // 0x011399e0
    bool   F_d60(float*);            // 0x01139d60
    RevObj* F_e10();                 // 0x01139e10
    void   F_eb0();                  // 0x01139eb0
    void   F_f20();                  // 0x01139f20
    int    F_fe0(void*);             // 0x01139fe0
    void   F_7a0(int);               // 0x0113a7a0
    RevObj* F_840(u8);               // 0x0113a840
};
}
}
}
// ---- items of slice s011399e0 end

// ---- items of slice s011388f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_tab014b23e0[];                // 0x014b23e0
// ---- items of slice s011388f0 end

// @ 0x01139920
namespace rw { namespace audio { namespace core {
int __stdcall FUN_01139920(float* src, int* out, float f)
{
    int i = 0;
    out[5] = 0;
    float* p = src;
    int n = 6;
    do {
        float a, b;
        if (f <= 48000.0f) { a = 1.0f; b = f; }
        else { a = f * 2.0833333e-05f; b = 48000.0f; }
        float lim = b * (*p * 0.002900232f);
        for (; i < 0x674; i++) {
            if (g_tab014b23e0[i] > lim) { *out = (int)g_tab014b23e0[i]; i++; break; }
        }
        if (a > 1.0f) *out = (int)((float)*out * a);
        out++; p++;
    } while (--n != 0);
    return n + 1;
}
}}}  // namespace rw::audio::core

// @ 0x011399e0
namespace rw { namespace audio { namespace core {
int RevObj::F_9e0(int out, float sr)
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
    // keep the external memset call the original makes (an intrinsic would inline it)
    void* (__cdecl *volatile clearTab)(void*, int, unsigned) = memset;
    clearTab(tab, 0, 0x44);
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
        while (!(tab[k] >= *pf)) k++;   // comiss/jb: continues on unordered (NaN)
        float f = (tab[k] - *pf) * 0.08f;
        *(float*)(out + i * 4) = (1.0f - f) * tab[k + 9] + tab[k + 8] * f;
    }
    if (A<float>(p, 0x38) != A<float>(p, 0x160)) {
        float f = *(float*)(out + 0x14) + 0.001f;
        if (A<float>(p, 0x38) < f) A<float>(p, 0x38) = f;
        int* pi = (int*)((char*)p + 0x17c);
        for (int i = 0; i < 6; i++, pi++) {
            FUN_0114dca0((char*)p + 0x1dc + i * 0x24);
            DelayLine* dl = (DelayLine*)((char*)p + 0x2b4 + i * 0x3c);
            dl->FUN_0114d840(*pi + 3);
            dl->FUN_0114d9d0(*pi + 1);
            *(float*)(out + i * 4) = *(float*)(out + i * 4) / A<float>(p, 0x38);
        }
    }
    return 1;
}
}}}  // namespace rw::audio::core

// 0x01139d60 (byte-exact lifted version: match/slices/s01139d60/s01139d60.cpp)
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01139e10
namespace rw { namespace audio { namespace core {
RevObj* RevObj::F_e10()
{
    void* p = this;
    *(void**)p = (void*)0x14b3dd4;
    for (int i = 0; i < 3; i++) ((AllPassFilter*)((char*)p + 0x40 + i * 0x18))->FUN_0114e230();
    for (int i = 0; i < 3; i++) ((DelayLine*)((char*)p + 0x88 + i * 0x3c))->FUN_0114d730();
    /* PlugIn::Initialize<...>(p+0x13c) */
    A<int>(p, 0x13c) = 0;
    A<int>(p, 0x148) = 0x13f9034;
    A<int>(p, 0x14c) = 0;
    A<u8>(p, 0x150) = 3;
    for (int i = 0; i < 6; i++) ((CombFilter*)((char*)p + 0x1dc + i * 0x24))->FUN_0114dce0();
    for (int i = 0; i < 6; i++) ((DelayLine*)((char*)p + 0x2b4 + i * 0x3c))->FUN_0114d730();
    return this;
}
}}}  // namespace rw::audio::core

// @ 0x01139f20
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01139fe0
namespace rw { namespace audio { namespace core {
int RevObj::F_fe0(void* sys)
{
    void* p = this;
    float sr = A<float>(sys, 0xc0);
    float g = A<float>(p, 0x30);
    int* pi;
    int* q;
    int b3 = 0;
    int b4 = 0;
    float fVar1 = sr;
    if (g == A<float>(p, 0x15c)) {
        if (sr == A<float>(p, 0x154)) {
            if (A<float>(p, 0x38) != A<float>(p, 0x160))
                F_9e0((int)((char*)p + 0x1ac), sr);
            F_d60((float*)((char*)p + 0x1c4));
        } else {
            extern int __stdcall FUN_01139920(float*, int*, float);
            FUN_01139920((float*)((char*)p + 0x164), (int*)((char*)p + 0x17c), sr);
            F_9e0((int)((char*)p + 0x1ac), sr);
            F_d60((float*)((char*)p + 0x1c4));
            b3 = true;
        }
    } else {
        if (g > 83.3f) A<float>(p, 0x30) = 83.3f;
        else if (g < 2.0f) A<float>(p, 0x30) = 2.0f;
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
        extern int __stdcall FUN_01139920(float*, int*, float);
        FUN_01139920((float*)((char*)p + 0x164), (int*)((char*)p + 0x17c), sr);
        F_9e0((int)((char*)p + 0x1ac), sr);
        F_d60((float*)((char*)p + 0x1c4));
        b4 = true;
    }
    pi = (int*)((char*)p + 0x17c);
    for (int i = 0; i < 6; i++, pi++) {
        // pi[0xc] loaded as float bits and negated with a sign flip (x87 fchs), so a NaN keeps
        // its payload and only the sign changes -- unlike an SSE 0.0-x.
        int g1bits = A<int>((char*)p, 0x1ac + i * 4) ^ 0x80000000;
        float g1 = *(float*)&g1bits;
        ((CombFilter*)((char*)p + 0x1dc + i * 0x24))->FUN_0114dcb0(
            g1, pi[0x12] ^ 0x80000000, g1, 0.16666667f);
        DelayLine* dl = (DelayLine*)((char*)p + 0x2b4 + i * 0x3c);
        if (A<int>((char*)p + 0x2b4 + i * 0x3c, 0x28) != *pi + 1) {
            if (dl->FUN_0114d840(*pi + 3) == 0) return 0;
            dl->FUN_0114d9d0(*pi + 1);
        }
    }
    fVar1 = sr;
    if (A<char>(p, 0x438) == 0 || b3) {
        char c = A<char>(p, 0x21);
        if (c == 1) {
            A<u8>(p, 0x439) = 1;
            A<float>(p, 0x41c) = 0.69999999f;
            A<int>(p, 0x428) = _mm_cvtss_si32(_mm_load_ss(&(fVar1 = fVar1 * 0.006f)));
        } else if (c == 2 || c == 4) {
            A<float>(p, 0x41c) = 0.63f;
            A<u8>(p, 0x439) = 2;
            A<float>(p, 0x420) = 0.77777779f;
            A<int>(p, 0x428) = _mm_cvtss_si32(_mm_load_ss(&(fVar1 = sr * 0.006666667f)));
            fVar1 = sr * 0.0053999997f;
            A<int>(p, 0x42c) = _mm_cvtss_si32(_mm_load_ss(&fVar1));
        } else {
            A<float>(p, 0x41c) = 0.63f;
            A<u8>(p, 0x439) = 3;
            fVar1 = sr * 0.006666667f;
            A<int>(p, 0x428) = _mm_cvtss_si32(_mm_load_ss(&fVar1));
            A<float>(p, 0x420) = 0.69999999f;
            A<float>(p, 0x424) = 0.77777779f;
            fVar1 = sr * 0.006f;
            A<int>(p, 0x42c) = _mm_cvtss_si32(_mm_load_ss(&fVar1));
            fVar1 = sr * 0.0053999997f;
            A<int>(p, 0x430) = _mm_cvtss_si32(_mm_load_ss(&fVar1));
        }
        q = (int*)((char*)p + 0x428);
        for (int i = 0; i < (int)A<u8>(p, 0x439); i++, q++) {
            ((AllPassFilter*)((char*)p + 0x40 + i * 0x18))->FUN_0114e210(
                A<float>(p, 0x41c + i * 4), A<float>(p, 0x434));
            DelayLine* dl = (DelayLine*)((char*)p + 0x88 + i * 0x3c);
            if (dl->FUN_0114d840(*q + 2) == 0) return 0;
            dl->FUN_0114d9d0(*q);
        }
        A<char>(p, 0x438) = 1;
    } else if (b4) {
        q = (int*)((char*)p + 0x428);
        for (int i = 0; i < (int)A<u8>(p, 0x439); i++, q++)
            ((DelayLine*)((char*)p + 0x88 + i * 0x3c))->FUN_0114d9d0(*q);
    }
    A<float>(p, 0x158) = A<float>(p, 0x28);
    A<float>(p, 0x154) = sr;
    A<float>(p, 0x15c) = A<float>(p, 0x30);
    A<float>(p, 0x160) = A<float>(p, 0x38);
    F_f20();
    return 1;
}
}}}  // namespace rw::audio::core

// @ 0x0113a4c0
namespace rw { namespace audio { namespace core {
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
        ((DelayLine*)((char*)self + 0x2b4 + i * 0x3c))->FUN_0114d9d0(A<int>(self, 0x17c + i * 4) + 1);
        FUN_0114dca0((char*)self + 0x1dc + i * 0x24);
    }
    for (int i = 0; i < (int)A<u8>(self, 0x439); i++)
        ((DelayLine*)((char*)self + 0x88 + i * 0x3c))->FUN_0114d9d0(A<int>(self, 0x428 + i * 4));
}
}}}  // namespace rw::audio::core

// @ 0x0113a5c0
namespace rw { namespace audio { namespace core {
bool __cdecl FUN_0113a5c0(void* self)
{
    if (self) ((RevObj*)self)->F_e10();
    u8 ch = A<u8>(self, 0x21);
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
    u8 c = A<u8>(self, 0x21);
    float f = (c <= 4) ? (float)c : (float)c - 1.0f;
    A<float>(self, 0x434) = 2.0f / f;
    A<char>(self, 0x438) = 0;
    char ok = ((TimerMgr*)((char*)A<void*>(self, 4) + 0x60))->AddTimer(
                  (char*)self + 0x13c, (void*)&FUN_0113a4c0, self, "ReverbModel1", 1, 1);
    if (ok != 0)
        return false;
    A<char>(self, 0x43a) = 1;
    return true;
}
}}}  // namespace rw::audio::core
