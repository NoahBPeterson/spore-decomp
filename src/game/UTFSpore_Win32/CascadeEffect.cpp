// src/game/UTFSpore_Win32/CascadeEffect.cpp -- migrated from slice(s) s0097f390, s00966b20 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/CascadeEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWindow.h"

// unnamed retail callees and globals (address in the comment)
extern float g_13f9428;                                                    // 0.001f
extern float    g_1488874;   // 0.1f

// ---- items of slice s00966b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define F(o, off)  (*(uint32_t*)((uint8_t*)(o) + (off)))
#define FB(o, off) (*(uint8_t*)((uint8_t*)(o) + (off)))
#define FF(o, off) (*(float*)((uint8_t*)(o) + (off)))
struct Stopwatch {
    void* __thiscall Ctor(int, int);   // 0x93a560
    void  __thiscall SetUnits(int);    // 0x93a1a0
};
struct S_93a3a0 { double __thiscall m(); };                                // 0x93a3a0
struct S_571e80 { void   __thiscall m(); };                                // 0x571e80
struct S_93a2e0 { void   __thiscall m(); };                                // 0x93a2e0
extern float g_13f9428;                                                    // 0.001f
static inline void VCALL0(void* o, int off) {
    ((void (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
static inline uint32_t VCALL0R(void* o, int off) {
    return ((uint32_t (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
static inline void* VCALL1P(void* o, int off, uint32_t a) {
    return ((void* (__thiscall*)(void*, uint32_t))(*(void***)o)[off / 4])(o, a);
}
struct S_967300 { void     __thiscall m(float); };
struct S_967320 { void     __thiscall m(float); };
struct S_9675c0 { void*    __thiscall m(); };
struct S_9673b0 { uint32_t __thiscall m(void*, uint8_t*); };
extern float    g_1488874;   // 0.1f
// ---- items of slice s00966b20 end

// ---- items of slice s0097f390 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)
void  MultiHeapDelete(void* p);                                  // 0x00951330
namespace EA {
namespace UTFWinControls {
struct CascadeEffect {
    void* m00;
    void* m04;
    void* m08;
    void* m0c;
    CascadeEffect* Destroy(uint8_t flags);
};
}
}
// ---- items of slice s0097f390 end

// @ 0x00967300
void S_967300::m(float v)
{
    void* this_ = this;
    if (v < 0.0f)
        FF(this_, 4) = 0.0f;
    else
        FF(this_, 4) = v;
}

// @ 0x00967320
void S_967320::m(float v)
{
    void* this_ = this;
    if (v < 0.0f)
        FF(this_, 8) = 0.0f;
    else
        FF(this_, 8) = v;
}

// @ 0x009673b0
uint32_t S_9673b0::m(void* param_2, uint8_t* param_3)
{
    void* this_ = this;
    int msg = *(int*)(param_3 + 8);

    if (msg == 0xc) {
        if (F(this_, 0x30) == 0)
            return 0;
        double lo = ((S_93a3a0*)((uint8_t*)this_ + 0x18))->m();
        float f = ((float)lo * FF(this_, 0x2c)) * g_13f9428;
        if (FB(this_, 0x38) == 0) {
            if (f < FF(this_, 0x14))
                return 0;
        } else {
            if (f < FF(this_, 0x10))
                return 0;
            FB(this_, 0x38) = 0;
        }
        ((S_571e80*)((uint8_t*)this_ + 0x18))->m();

        if (F(this_, 0x30) > 0) {
            void* e = VCALL1P(param_2, 0xd0, 0);
            uint8_t* cur = *(uint8_t**)((uint8_t*)this_ + 0x34);
            if (cur == *(uint8_t**)e) {
                F(this_, 0x30) = 0;
                ((S_93a2e0*)((uint8_t*)this_ + 0x18))->m();
                VCALL0(param_2, 0xa0);
                return 0;
            }
            uint8_t* base = cur - 4;
            void** vt = *(void***)base;
            void (__thiscall* fn)(void*, int, uint32_t) =
                (void (__thiscall*)(void*, int, uint32_t))vt[0x7c / 4];
            fn(base, 1, (uint32_t)FB(this_, 0x39));
            F(this_, 0x34) = *(uint32_t*)cur;
            return 0;
        }
        void* e = VCALL1P(param_2, 0xcc, 0);
        uint8_t* cur = *(uint8_t**)((uint8_t*)this_ + 0x34);
        if (cur == *(uint8_t**)e) {
            F(this_, 0x30) = 0;
            ((S_93a2e0*)((uint8_t*)this_ + 0x18))->m();
            VCALL0(param_2, 0xa0);
            return 0;
        }
        uint8_t* prev = *(uint8_t**)(cur + 4);
        F(this_, 0x34) = (uint32_t)prev;
        {
            uint8_t* base = prev - 4;
            void** vt = *(void***)base;
            void (__thiscall* fn)(void*, int, uint32_t) =
                (void (__thiscall*)(void*, int, uint32_t))vt[0x7c / 4];
            fn(base, 1, (uint32_t)FB(this_, 0x39));
        }
        return 0;
    }

    if (msg == 0xe) {
        int d = *(int*)(param_3 + 0xc);
        if (d != 1 && d != -1)
            return 0;
        uint32_t sel = VCALL0R(param_2, 0x28);
        void* e0 = VCALL1P(param_2, 0xd0, 0);
        void* e1 = VCALL1P(param_2, 0xcc, 0);
        if (*(uint32_t*)e1 == *(uint32_t*)e0)
            return 0;
        uint32_t t = sel & 1;
        int sign = (int)t + (int)t - 1;
        if (F(this_, 0x30) == 0) {
            FB(this_, 0x38) = 1;
            void* res = (sign > 0) ? VCALL1P(param_2, 0xcc, 0)
                                   : VCALL1P(param_2, 0xd0, 0);
            F(this_, 0x34) = *(uint32_t*)res;
        }
        F(this_, 0x30) = (uint32_t)sign;
        FB(this_, 0x39) = (uint8_t)t;
        ((S_571e80*)((uint8_t*)this_ + 0x18))->m();
        VCALL0(param_2, 0x9c);
        return 0;
    }

    return 0;
}

// @ 0x009675c0
void* S_9675c0::m()
{
    void* this_ = this;
    F(this_, 0x04) = 0x13fa72c;
    F(this_, 0x08) = 0;
    F(this_, 0x0c) = 0x1444434;
    FF(this_, 0x10) = 0.0f;
    F(this_, 0x00) = 0x14414b8;
    F(this_, 0x04) = 0x144149c;
    F(this_, 0x0c) = 0x1441478;
    FF(this_, 0x14) = g_1488874;
    Stopwatch* sw = (Stopwatch*)((uint8_t*)this_ + 0x18);
    sw->Ctor(0, 0);
    F(this_, 0x30) = 0;
    FB(this_, 0x38) = 0;
    FB(this_, 0x39) = 0;
    sw->SetUnits(4);
    return this_;
}

// @ 0x00980490
namespace EA { namespace UTFWinControls {
CascadeEffect* CascadeEffect::Destroy(uint8_t flags)
{
    m0c = (void*)0x13eb938;
    m04 = (void*)0x13eb938;
    m00 = (void*)0x13eb938;
    if (flags & 1)
        MultiHeapDelete(this);
    return this;
}
}}  // namespace EA::UTFWinControls
