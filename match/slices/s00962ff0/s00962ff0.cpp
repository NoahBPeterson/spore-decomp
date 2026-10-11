// Slice s00962ff0 -- EA::UTFWin::* controls helpers (effects, index-buffer factories)
// plus a handful of button accessors.  Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"

extern "C" void __cdecl  FUN_0093a560(void*, int, int);   // Stopwatch::Stopwatch  0x93a560
extern "C" void __cdecl  FUN_0093a1a0(void*, int);        // Stopwatch::SetUnits   0x93a1a0
struct Stopwatch { void Init(int, int); void SetUnits(int); void Restart(); };

struct ResDesc { int a, b, c, d, e; };
extern "C" void __cdecl  FUN_011f51d0(ResDesc*, int, int, int, int);   // GetResourceDescriptor 0x11f51d0
extern "C" void* __cdecl FUN_011f36d0(int*, int, int, int);            // 0x11f36d0
extern "C" void* __cdecl FUN_011f5010(int*, int, int, int, int, int);  // 0x11f5010
extern void* g_pfnIndexBuffer;                                         // 0x16f4ae4

// ------------------------------------------------------------------ 0x962ff0
int __cdecl FUN_00962ff0(int p2, int p3, int p4, int p5)
{
    ResDesc desc;
    FUN_011f51d0(&desc + 0, p2, p3, p4, p5);
    int r = ((int (__cdecl*)(int, int))g_pfnIndexBuffer)(desc.b, desc.c);
    if (r != 0) {
        int local[4];
        local[0] = r;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        return (int)FUN_011f36d0(local, p2, p3, p4);
    }
    return 0;
}

// ------------------------------------------------------------------ 0x963060
// @ 0x00963060
int __cdecl FUN_00963060(int p1, int p2, int p3, int p4, int p5, int p6)
{
    ResDesc desc;
    FUN_011f51d0(&desc, p2, p3, p4, p5);
    (void)p6;
    int r = ((int (__cdecl*)(int, int))g_pfnIndexBuffer)(desc.b, desc.c);
    if (r != 0) {
        int local[4];
        local[0] = r;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        return (int)FUN_011f5010(local, p2, p3, p4, p5, p6);
    }
    return 0;
}

// ================================================================== controls
struct Btn {
    int   GetEventMask();                       // 0x9634c0
    void  OnlyWhenVisible(int* wnd, bool on);   // 0x963630
    void  SetFade(bool on);                     // 0x9635e0
    void  SetAlphaClamp(float a, float b);      // 0x9636f0
};

// @ 0x9634c0
int Btn::GetEventMask()
{
    uint32_t f = (*(uint32_t(__thiscall**)(void*))((char*)*(void**)this + 0x80))(this);
    uint32_t r = *(uint32_t*)((char*)this + 0x54) | 0x10459;
    if (f & 1)
        r |= 0x200;
    return (int)r;
}

struct WinButtonX {
    int   GetSlot(uint32_t i);                          // 0x964020
    void  SetSlot(uint32_t i, int v);                   // 0x963fd0
    int   GetCaptionColor();                            // 0x964000
};

// @ 0x964020
int WinButtonX::GetSlot(uint32_t i)
{
    if (i < 8)
        return *(int*)((char*)this + 0x54 + i * 4);
    return 0;
}

// @ 0x963fd0
void WinButtonX::SetSlot(uint32_t i, int v)
{
    if (i < 8 && *(int*)((char*)this + 0x54 + i * 4) != v) {
        *(int*)((char*)this + 0x54 + i * 4) = v;
        int* base = (int*)((char*)this - 0x20c);
        (*(void(__thiscall**)(int*))((char*)*base + 0xa0))(base);
    }
}

// @ 0x964000
int WinButtonX::GetCaptionColor()
{
    if (*(char*)((char*)this + 0x210) != 0)
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0xa0))(this);
    return *(int*)((char*)this + 0x224);
}

struct FlexFlag {
    int  GetEffectFlag();                       // 0x963f60
    void SetEffectFlag(uint32_t m, bool on);    // 0x963f70
};

// @ 0x963f60
int FlexFlag::GetEffectFlag()
{
    return *(int*)((char*)this - 0x160);
}

// @ 0x963f70
void FlexFlag::SetEffectFlag(uint32_t m, bool on)
{
    int v = *(int*)((char*)this - 0x160);
    if (on) {
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)this + 0x24))(this, (uint32_t)v | m);
    } else {
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)this + 0x24))(this, (uint32_t)v & ~m);
    }
}

// @ 0x9636f0
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

// @ 0x9635e0
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

// @ 0x963630
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

// @ 0x963db0
extern void* vtbl_FadeEffect;         // 0x1440d88
extern void* vtbl_FadeEffect2;        // 0x1440d6c
extern void* vtbl_FadeEffect3;        // 0x1440d30
void* __fastcall FadeEffect_Ctor(void* self)
{
    *(void**)((char*)self + 4) = (void*)0x13fa72c;
    *(int*)  ((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = (void*)0x14085f0;
    *(void**)self = (void*)0x1440d88;
    *(void**)((char*)self + 4) = (void*)0x1440d6c;
    *(void**)((char*)self + 0xc) = (void*)0x1440d30;
    *(float*) ((char*)self + 0x10) = 0.0f;
    ((Stopwatch*)((char*)self + 0x18))->Init(0, 0);
    *(int*)  ((char*)self + 0x30) = 1;
    *(int*)  ((char*)self + 0x34) = 0;
    *(float*)((char*)self + 0x38) = 0.0f;
    *(float*)((char*)self + 0x3c) = 0.0f;
    *(float*)((char*)self + 0x40) = 0.1f;
    *(float*)((char*)self + 0x44) = 0.0f;
    *(float*)((char*)self + 0x48) = 0.0f;
    *(float*)((char*)self + 0x4c) = 0.0f;
    *(char*) ((char*)self + 0x50) = 0;
    *(int*)  ((char*)self + 0x54) = 2;
    *(int*)  ((char*)self + 0x58) = 0;
    ((Stopwatch*)((char*)self + 0x18))->SetUnits(5);
    return self;
}

// @ 0x964040
struct Cap { void SelectCaptionColor(); };
void Cap::SelectCaptionColor()
{
    void* self = this;
    uint32_t v = (*(uint32_t(__thiscall**)(void*))((char*)*(void**)self + 0x28))(self);
    uint32_t xf = *(uint32_t*)((char*)self + 0x3c);
    char c2 = (char)((xf >> 4) | (v >> 1)) & 1;
    (void)c2;
}

// @ 0x9634f0
struct EaseFx { long double Ease(float t); };
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

// @ 0x9630e0  (approximate: non-degenerate append path only)
int __cdecl FUN_009630e0(int* a, int b, int c, int d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}

// @ 0x963780  (approximate: message dispatch skeleton)
int __cdecl FUN_00963780(int* a, int b, int c, int d)
{
    (void)a; (void)b; (void)c; (void)d;
    return 0;
}
