// src/game/UTFSpore_Win32/BiStateEffect.cpp -- migrated from slice(s) s00962ff0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/BiStateEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00962ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Stopwatch { void Init(int, int); void SetUnits(int); void Restart(); };
struct Btn {
    int   GetEventMask();                       // 0x9634c0
    void  OnlyWhenVisible(int* wnd, bool on);   // 0x963630
    void  SetFade(bool on);                     // 0x9635e0
    void  SetAlphaClamp(float a, float b);      // 0x9636f0
};
struct EaseFx { long double Ease(float t); };
// ---- items of slice s00962ff0 end

// @ 0x009634c0
int Btn::GetEventMask()
{
    uint32_t f = (*(uint32_t(__thiscall**)(void*))((char*)*(void**)this + 0x80))(this);
    uint32_t r = *(uint32_t*)((char*)this + 0x54) | 0x10459;
    if (f & 1)
        r |= 0x200;
    return (int)r;
}

// @ 0x009634f0
long double EaseFx::Ease(float t)
{
    int mode = *(int*)((char*)this + 0x34);
    if (mode == 1) {
        if (t != 0.0f && t != 1.0f) {
            float a = *(float*)((char*)this + 0x38);
            float b = *(float*)((char*)this + 0x3c);
            if (a + b != 0.0f) {
                float s = 1.0f / ((2.0f - a) - b);
                if (a > t)
                    return (long double)t * ((long double)s / (long double)a * (long double)t);
                if (1.0f - b > t)
                    return ((long double)t + (long double)t - (long double)a) * (long double)s;
                long double r = 1.0 - (long double)t;
                return 1.0 - ((long double)s / (long double)b) * r * r;
            }
        }
        return t;
    }
    if (mode == 2 || mode == 0)
        return t;
    return 0.0;
}

// @ 0x009635e0
void Btn::SetFade(bool on)
{
    int* p = *(int**)((char*)this + 0x58);
    if (p == 0)
        return;
    if (on) {
        if (*(int*)((char*)this + 0x54) != 0)
            return;
        *(int*)((char*)this + 0x54) = 2;
        (*(void(__thiscall**)(int*, void*))((char*)*p + 0x104))(p, this);
    } else {
        if (*(int*)((char*)this + 0x54) == 0)
            return;
        *(int*)((char*)this + 0x54) = 0;
        (*(void(__thiscall**)(int*, void*))((char*)*p + 0x104))(p, this);
    }
}

// @ 0x00963630
void Btn::OnlyWhenVisible(int* wnd, bool on)
{
    float f = on ? 1.0f : 0.0f;
    *(float*)((char*)this + 0x44) = f;
    if (f != *(float*)((char*)this + 0x4c)) {
        int m = *(int*)((char*)this + 0x30);
        if (m == 0 || m == 1)
            (*(void(__thiscall**)(int*))((char*)*wnd + 0x9c))(wnd);
        ((Stopwatch*)((char*)this + 0x18))->Restart();
        int* p = *(int**)((char*)this + 0x58);
        if (p != 0 && *(int*)((char*)this + 0x54) == 0) {
            *(int*)((char*)this + 0x54) = 2;
            (*(void(__thiscall**)(int*, void*))((char*)*p + 0x104))(p, this);
        }
        struct Msg { char pad0[8]; uint32_t type; char pad1[0xc]; void* self; };
        Msg msg;
        msg.type = 0x7e1a520;
        msg.self = this;
        (*(void(__thiscall**)(int*, Msg*))((char*)*wnd + 0x114))(wnd, &msg);
    }
}

// @ 0x009636f0
void Btn::SetAlphaClamp(float a, float b)
{
    if (0.0f > a) a = 0.0f;
    if (0.0f > b) b = 0.0f;
    if (a > 1.0f) a = 1.0f;
    if (b > 1.0f) b = 1.0f;
    if (1.0f < a + b) {
        float s = 1.0f / (a + b);
        a = s * a;
        b = s * b;
    }
    *(float*)((char*)this + 0x2c) = a;
    *(float*)((char*)this + 0x30) = b;
}
