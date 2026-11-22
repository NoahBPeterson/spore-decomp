#include "game/types.h"
#include "rw/graphics/BuildState.h"

// Local stand-ins for the retail classes; the generated headers carry no
// class at these addresses (0x9634c0 / 0x9634f0).
struct Stopwatch { void Restart(); };
struct Btn {
    int   GetEventMask();                       // 0x9634c0
    void  OnlyWhenVisible(int* wnd, bool on);   // 0x963630
    void  SetFade(bool on);                     // 0x9635e0
    void  SetAlphaClamp(float a, float b);      // 0x9636f0
};
struct EaseFx { long double Ease(float t); };

struct IBtnWnd_9636 {   // UTFWin::IWindow slots used here
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98();
    virtual void Invalidate();                                  // +0x9c
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110();
    virtual void SendMsg(void* msg);                            // +0x114
};

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
            ((IBtnWnd_9636*)wnd)->Invalidate();
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
        ((IBtnWnd_9636*)wnd)->SendMsg(&msg);
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

// @ 0x00963780
int __fastcall FUN_00963780(void* self, int, void* wnd, void* msg)
{
    (void)self; (void)wnd;
    unsigned code = *(unsigned*)((char*)msg + 8);
    return (int)(code & 0xffffff00u);
}
