// Slice s006f2710 — SP::cEffectsRenderer / EffectsManager helpers (many small).
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"

// ---- 0x006f2710 (skeleton) --------------------------------------------------
// @ 0x006f2710
void EffectsHelper710(int, int)
{
}

// ---- 0x006f2e80 (skeleton) --------------------------------------------------
// @ 0x006f2e80
void BaseDtor2e80()
{
}

// ---- 0x006f2f30 -------------------------------------------------------------
// @ 0x006f2f30
int __stdcall RetMinus1(int, int, int, int)
{
    return -1;
}

// ---- 0x006f2f40 -------------------------------------------------------------
// @ 0x006f2f40
int __stdcall RetThird(int, int, int c)
{
    return c;
}

// ---- 0x006f2f70 (skeleton: adjustor) ---------------------------------------
// @ 0x006f2f70
void Adjustor2f70()
{
}

// ---- 0x006f2fb0 (skeleton: constructor) ------------------------------------
// @ 0x006f2fb0
void Ctor2fb0()
{
}

// ---- 0x006f3030 (skeleton: destructor) -------------------------------------
// @ 0x006f3030
void Dtor3030()
{
}

// ---- 0x006f31b0 (skeleton: constructor) ------------------------------------
// @ 0x006f31b0
void Ctor31b0()
{
}

// ---- EffectsManager virtual-dispatch stubs ---------------------------------
struct IVT_A { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
               virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
               virtual void a8(); virtual void a9(); };
struct IVT_B : IVT_A { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3();
               virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7();
               virtual void b8(); virtual void b9(); };
struct IVT_C : IVT_B { virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
               virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7();
               virtual void c8(); virtual void c9(); };
struct IVT_D : IVT_C { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
               virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
               virtual void SetState(int a, int b); };

void* EffectsManager();   // SP::EffectsManager

// ---- 0x006f3290 -------------------------------------------------------------
// @ 0x006f3290
void ResetEffectStates()
{
    IVT_D* m = (IVT_D*)EffectsManager();
    m->SetState(0, 0);
    m->SetState(1, 0);
    m->SetState(2, 0);
    m->SetState(3, 1);
}

// ---- 0x006f32e0 (approximate) ----------------------------------------------
// @ 0x006f32e0
void ApplyStateFromProperty(void* prop, float)
{
    (void)prop;
}

// ---- 0x006f33d0 -------------------------------------------------------------
struct IVT33d0 {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12(int);
};
struct Owner33d0 {
    char pad0[0x34];
    IVT33d0* mpAt34;   // +0x34
    char pad1[0x58 - 0x38];
    int mAt58;         // +0x58
    void ReleaseIf();
};
// @ 0x006f33d0
void Owner33d0::ReleaseIf()
{
    if (mAt58 >= 0) {
        mpAt34->v12(mAt58);
        IVT33d0* p = mpAt34;
        if (p) {
            mpAt34 = 0;
            p->Release();
        }
        mAt58 = -1;
    }
}
