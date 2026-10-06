// Slice s00f02160 -- scenario tutorial placement implementation (ctor/dtor, global teardown,
// update dispatch).  Region flags: /O2 /MD /Gy /TP
#include "types.h"

extern void*   g_mgr;             // 0x016c7b88 (singleton pointer variable)
extern uint8_t g_015acb40;        // 0x015acb40
extern void*   g_Simulator;       // 0x016c7aa4

extern "C" void* __cdecl operator_new6(unsigned, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void  __cdecl operator_delete_(void*);          // 0x00f47380
extern "C" void* __cdecl FUN_0067dd10();                    // 0x0067dd10
extern "C" void  __cdecl FUN_00f31fd0(void*);               // 0x00f31fd0
extern "C" void* __cdecl FUN_00eebf80(void*);               // 0x00eebf80

struct SW {                       // EA::Stopwatch at +0xb0
    void ctor(int, int);          // 0x93a560
    void SetTimeLimit(int, int);  // 0x93a480
};
struct X { void run(); };
extern "C" void f_eff0c0_ext();   // 0x00eff0c0
extern "C" void f_efd020_ext();   // 0x00efd020
extern "C" void f01c20_ext();     // 0x00f01c20
extern "C" void f00f80_ext();     // 0x00f00f80
struct Ref {
    virtual void v0();
    virtual void v4();
};
struct V4 {
    void* p0;
    int   f4;
    int   f8;
    float fC;
};
struct PL {
    void*  vtable;    // +0x00
    uint8_t b4;       // +0x04
    uint8_t b5;       // +0x05
    uint8_t b6;       // +0x06
    uint8_t b7;       // +0x07
    void*  p8;        // +0x08
    V4*    pC;        // +0x0c
    void*  p10;       // +0x10
    void  f02160();              // 0x00f02160
    void  f02670();              // 0x00f02670
    void  f02700();              // 0x00f02700
    int   f02a10(int, int, float); // 0x00f02a10 ret 0xc
    void  f02b00();              // 0x00f02b00
    PL*   f02b80();              // 0x00f02b80
    PL*   ctor_2cd0();           // 0x00f02cd0
    void  f02c50();              // 0x00f02c50
    PL*   f02d30(int);           // 0x00f02d30 ret 4
    void  f02e00();              // 0x00f02e00
    void  f03010();              // 0x00f03010
    void  f030a0();              // 0x00f030a0
};
extern void* g_vtbl_148b708;   // 0x0148b708
extern void* g_vtbl_148b788;   // 0x0148b788

// @ 0x00f02b80
PL* PL::f02b80()
{
    char* s = (char*)this;
    *(int*)(s + 0x00) = 0;
    *(int*)(s + 0x04) = 0;
    *(int*)(s + 0x08) = 0;
    *(int*)(s + 0x0c) = 0;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x2c) = 0;
    *(int*)(s + 0x34) = 0;
    *(int*)(s + 0x38) = 0;
    *(int*)(s + 0x3c) = 0;
    *(int*)(s + 0x54) = 0;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x5c) = 0;
    *(int*)(s + 0x60) = 0;
    *(int*)(s + 0x8c) = 0;
    *(int*)(s + 0x90) = 0;
    *(int*)(s + 0x94) = 0;
    SW* sw = (SW*)(s + 0xb0);
    *(uint8_t*)(s + 0xa5) = 1;
    *(int*)(s + 0xa8) = 0;
    *(int*)(s + 0xac) = 0;
    sw->ctor(4, 0);
    sw->SetTimeLimit(0, 0);
    return this;
}

// @ 0x00f02cd0
PL* PL::ctor_2cd0()
{
    PL* self = this;
    *(void**)self = g_vtbl_148b708;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    void* m = operator_new6(0x10, (const char*)0x148b76c, 0, 0, 0, 0);
    if (m) {
        FUN_00f31fd0(m);
        *(void**)((char*)self + 0xc) = m;
    } else {
        *(void**)((char*)self + 0xc) = 0;
    }
    self->f02670();
    return self;
}

// @ 0x00f02d30
PL* PL::f02d30(int flag)
{
    V4* p = pC;
    vtable = g_vtbl_148b708;
    if (p) {
        void* o = p->p0;
        if (o) ((Ref*)o)->v4();
        operator_delete_(p);
    }
    *(void**)((char*)this + 0xc) = 0;
    if (flag & 1) operator_delete_(this);
    return this;
}

// @ 0x00f02dd0
void __cdecl destroy_global_2dd0()
{
    X* p = (X*)g_mgr;
    if (p) {
        p->run();
        operator_delete_(p);
    }
    g_mgr = 0;
}

// @ 0x00f02670
void PL::f02670()
{
    void* sim = g_Simulator;
    *(void**)((char*)this + 8) = sim ? *(void**)((char*)sim + 0x18) : 0;
    void** vt = *(void***)this;
    ((void(__thiscall*)(void*, int))vt[0x18 / 4])(this, 0);
    b5 = 0;
    b6 = 0;
    b7 = 0;
    V4 tmp;
    tmp.p0 = 0; tmp.f4 = 0; tmp.f8 = 0; tmp.fC = 0;
    FUN_00f31fd0(&tmp);
    V4* dst = pC;
    void* old = dst->p0;
    void* nw = tmp.p0;
    if (nw != old) {
        if (nw) ((Ref*)nw)->v0();
        dst->p0 = nw;
        if (old) ((Ref*)old)->v4();
    }
    dst->f4 = tmp.f4;
    dst->f8 = tmp.f8;
    dst->fC = tmp.fC;
    if (tmp.p0) ((Ref*)tmp.p0)->v4();
}

// @ 0x00f02b00
void PL::f02b00()
{
    void** vt = *(void***)this;
    if (!((bool(__thiscall*)(void*))vt[0x38 / 4])(this)) return;
    void* a = FUN_0067dd10();
    void** va = *(void***)a;
    void* b = ((void*(__thiscall*)(void*))va[0x50 / 4])(a);
    void** vb = *(void***)b;
    void* c = ((void*(__thiscall*)(void*))vb[0x38 / 4])(b);
    if (c) {
        void** vc = *(void***)c;
        void* d = ((void*(__thiscall*)(void*, int))vc[0x0c / 4])(c, 0x11966ed);
        if (d) {
            if (*(uint8_t*)((char*)d + 0x319) == 0) return;
        }
    }
    if (*(int*)((char*)g_mgr + 0x10) != 0) { f00f80_ext(); f_eff0c0_ext(); return; }
    if (*(int*)((char*)g_mgr + 0xc) != 0) { f02700(); f_eff0c0_ext(); return; }
    if (b5) f00f80_ext();
    f_eff0c0_ext();
}

// @ 0x00f02c50
void PL::f02c50()
{
    void** vt = *(void***)this;
    if (!((bool(__thiscall*)(void*))vt[0x38 / 4])(this)) return;
    void* a = FUN_0067dd10();
    void** va = *(void***)a;
    void* b = ((void*(__thiscall*)(void*))va[0x50 / 4])(a);
    void** vb = *(void***)b;
    void* c = ((void*(__thiscall*)(void*))vb[0x38 / 4])(b);
    if (c) {
        void** vc = *(void***)c;
        void* d = ((void*(__thiscall*)(void*, int))vc[0x0c / 4])(c, 0x11966ed);
        if (d && *(uint8_t*)((char*)d + 0x319) == 0) return;
    }
    if (*(int*)((char*)g_mgr + 0x10) != 0) { f02160(); f_efd020_ext(); return; }
    if (*(int*)((char*)g_mgr + 0xc) != 0) { f01c20_ext(); }
    f_efd020_ext();
}

// stubs / partial
void PL::f02160() {}
void PL::f02700() {}
int PL::f02a10(int a, int b, float c) { (void)a; (void)b; (void)c; return 0; }
void PL::f02e00() {}
void PL::f03010() {}
void PL::f030a0() {}
