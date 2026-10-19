// src/game/plugins/reverbmodel1.cpp.cpp -- migrated from slice(s) s011399e0 by tools/migrate/rewrite.py
// Object file: plugins/reverbmodel1.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/TimerManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  FUN_0114dca0(void*);                 // 0x0114dca0  cdecl, ret
extern "C" double log2(double);
#include <xmmintrin.h>
#include <math.h>

// ---- items of slice s011399e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
template <class T> static inline T& A(void* p, int off) { return *(T*)((char*)p + off); }
namespace rw {
namespace audio {
namespace core {
struct DelayLine {
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
struct CombFilter {
    void FUN_0114dcb0(float, int, float, float); // 0x0114dcb0 SetGains, ret 0x10
    void FUN_0114dce0();                 // 0x0114dce0  ctor
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct AllPassFilter {
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
    void   F_9e0(int, float);        // 0x011399e0
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
extern "C" int  FUN_0114dca0(void*);                 // 0x0114dca0  cdecl, ret
extern "C" double log2(double);
// ---- items of slice s011399e0 end

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
    bool b3 = false;
    bool b4 = false;
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
    int* pi = (int*)((char*)p + 0x17c);
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
        int* q = (int*)((char*)p + 0x428);
        for (int i = 0; i < (int)A<u8>(p, 0x439); i++, q++) {
            ((AllPassFilter*)((char*)p + 0x40 + i * 0x18))->FUN_0114e210(
                A<float>(p, 0x41c + i * 4), A<float>(p, 0x434));
            DelayLine* dl = (DelayLine*)((char*)p + 0x88 + i * 0x3c);
            if (dl->FUN_0114d840(*q + 2) == 0) return 0;
            dl->FUN_0114d9d0(*q);
        }
        A<char>(p, 0x438) = 1;
    } else if (b4) {
        int* q = (int*)((char*)p + 0x428);
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
