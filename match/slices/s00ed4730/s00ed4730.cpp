// Slice s00ed4730 -- Simulator::cScenarioEditModeDisplayStrategy and UI glue.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- globals
extern char* g_16c7aa4;   // 0x016c7aa4

// ---------------------------------------------------------------- thiscall callee stubs
struct S_ef72b0 { void f(); };
struct S_ef72c0 { void f(); };
struct S_f45970 { void* f(); };
struct S_f45a80 { void f(); };
struct S_f46450 { int  f(void*); };
struct S_ed38a0 { void f(int); };
struct S_ed3b20 { void f(void*, void*); };
struct S_644b10 { void f(); };
struct S_644b60 { void f(); };
struct S_ef00b0 { void f(); };
struct S_ef0b80 { void f(); };
struct S_f46630 { char f(void*); };
struct S_b3d3c0 { void* f(); };
struct S_b3d310 { void* f(); };
struct S_8105b0 { void* f(int, int); };
struct S_e281a0 { void f(int); };
struct S_e22700 { void f(int); };
struct S_f3bfa0 { void* f(unsigned); };
struct S_f3bf60 { int  f(); };
struct S_f3bf70 { unsigned f(); };
struct S_f3bde0 { char f(int); };
struct S_f3bd90 { void f(void*, unsigned char); };
struct S_e02e80 { void f(); };
struct S_e226c0 { char f(); };
struct S_ed4c70 { void f(int); };

// ---------------------------------------------------------------- cdecl free callees
void  __cdecl operator_delete(void*);
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
void  __cdecl SP_ShowContextSensitiveSporepedia(void*);        // 0xe02040
void* __cdecl SP_MessageServer(void);                          // 0x67dcc0
void* __cdecl SP_CheatManager(void);                           // 0x67de20
void* __cdecl FUN_00b3d3c0(void);
void* __cdecl FUN_00b3d310(void);
void  __cdecl FUN_00b781d0(void);
void  __cdecl FUN_00b5a390(void);
void  __cdecl FUN_00b515e0(void);
void  __cdecl FUN_00b79aa0(void);
void  __cdecl FUN_00efc8c0(int);
void  __cdecl FUN_00f190a0(void);
void* __cdecl FUN_00957f30(void);   // UTFWin::GetManager
void* __cdecl FUN_009512c0(void);
void* __cdecl FUN_009512d0(int, int, const char*, void*);
void  __cdecl FUN_008085d0(void*, void*, int, int, int);
void  __cdecl FUN_00804f50(int);
void* __cdecl SP_EffectsManager(void);                          // 0x67ddd0
char  __cdecl FUN_00e00ac0(void);                               // 0xe00ac0
void* __cdecl SP_WindowManager(void);                           // 0x67caa0
void* __cdecl FUN_00d539d0(void);                               // 0xd539d0
unsigned __cdecl FUN_00f3bf70_v(void);
char  __cdecl cSPUIPosseItem_init(void*, int);                  // 0xe277b0
void  __cdecl FUN_00571db0(int, int, int, int, int);            // EA::Messaging::RemoveHandler

// ---------------------------------------------------------------- typedefs
typedef void  (__thiscall *FV_v)(void*);
typedef void* (__thiscall *FV_p)(void*);
typedef void  (__thiscall *FV_i)(void*, int);
typedef void* (__thiscall *FV_ip)(void*, int);
typedef void  (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_iip)(void*, int, int, void*);
typedef void* (__thiscall *FV_iir)(void*, int, int);
typedef int   (__thiscall *FV_ipr)(void*, int);
typedef unsigned long long (__thiscall *FV_q)(void*);
typedef void  (__thiscall *FV_ff)(void*, float, float);

// ================================================================ 0x00ed4730
struct Obj4730 { char pad[0x38]; int f(int* list); };
int Obj4730::f(int* list)
{
    ((S_ef72b0*)*(int*)(g_16c7aa4 + 0xd4))->f();
    if (*list != list[1] && *list != 0) {
        ((S_f45970*)*(int*)(g_16c7aa4 + 0x74))->f();
        int* q = *(int**)((char*)this + 0x38);
        int* r = *(int**)((char*)q + 0xc);
        void* a = r ? ((FV_ip)(*(void***)r)[3])(r, 0x722de52) : 0;
        ((S_ed3b20*)((char*)this - 0xc))->f(a, (void*)*list);
        for (unsigned i = 1; i < (unsigned)((list[1] - *list) / 0xc); i++) {
            int v = ((S_f46450*)*(int*)(g_16c7aa4 + 0x74))->f((void*)(*list + i * 0xc));
            if (v != -1)
                ((S_ed38a0*)((char*)this - 0xc))->f(v);
        }
        ((S_f45a80*)*(int*)(g_16c7aa4 + 0x74))->f();
        int obj = *(int*)((char*)this + 0x38);
        if (obj != 0) {
            ((S_644b60*)obj)->f();
            operator_delete((void*)obj);
            *(int*)((char*)this + 0x38) = 0;
        }
    }
    return 0;
}

// ================================================================ 0x00ed4840
struct Obj4840 { char pad0[0x14]; unsigned m14; char pad1[8]; char m20; int f(); };
int Obj4840::f()
{
    if (m20 != 0 && m14 > 0)
        return 1;
    return 0;
}

// ================================================================ 0x00ed48a0
char __cdecl FUN_00ed48a0(void* a, int* c)
{
    (void)a;
    return (unsigned)(c[2] - 1) <= 9;
}

// ================================================================ 0x00ed48b0
struct Obj48b0 { int* m0; int* m4; char pad0[0xc]; unsigned m14; char pad1[8]; char m20; int f(); };
int Obj48b0::f()
{
    if (m20 != 0 && m14 < (unsigned)((int*)m4 - (int*)m0))
        return 1;
    return 0;
}

// ================================================================ 0x00ed4930
void FUN_00ed4930(void)
{
    uint32_t buf[0x12];
    char* g = g_16c7aa4;
    ((S_ef72c0*)*(int*)(g + 0xd4))->f();
    ((S_644b10*)buf)->f();
    SP_ShowContextSensitiveSporepedia(buf);
    ((S_644b60*)buf)->f();
}

// ================================================================ 0x00ed4970
char __cdecl FUN_00ed4970(void* a, int* msg)
{
    (void)a;
    if (msg[2] == 0x1b) {
        int* q = (int*)msg[6];
        if (q != 0) {
            if (((FV_ip)(*(void***)q)[3])(q, 0xcf428691) != 0)
                ((S_ef0b80*)g_16c7aa4)->f();
        }
    }
    return 0;
}

// ================================================================ 0x00ed49a0
struct Obj49a0 { void f(); };
void Obj49a0::f()
{
    char* s = (char*)this;
    *(int**)s = (int*)0x1489e8c;
    *(int**)(s + 8) = (int*)0x1489e70;
    *(int**)(s + 0xc) = (int*)0x1489e64;
    *(int**)(s + 0x10) = (int*)0x1489e54;
    if (SP_MessageServer() != 0) {
        int* sv = (int*)SP_MessageServer();
        ((FV_iip)(*(void***)sv)[0x2c / 4])(sv, 0xffffd8f1, 0x65ff54a, s + 0x10);
    }
    if (*(int**)(s + 0x8c)) ((FV_v)(*(void***)*(int**)(s + 0x8c))[4 / 4])(*(int**)(s + 0x8c));
    if (*(int**)(s + 0x88)) ((FV_v)(*(void***)*(int**)(s + 0x88))[4 / 4])(*(int**)(s + 0x88));
    if (*(int**)(s + 0x84)) ((FV_v)(*(void***)*(int**)(s + 0x84))[4 / 4])(*(int**)(s + 0x84));
    if (*(int*)(s + 0x70)) {
        int h = *(int*)(s + 0x70);
        *(int*)(s + 0x70) = 0;
        FUN_00571db0(h, *(int*)(s + 0x74), *(int*)(s + 0x78), *(int*)(s + 0x7c), *(int*)(s + 0x80));
    }
    if (*(int*)(s + 0x5c)) {
        int h = *(int*)(s + 0x5c);
        *(int*)(s + 0x5c) = 0;
        FUN_00571db0(h, *(int*)(s + 0x60), *(int*)(s + 0x64), *(int*)(s + 0x68), *(int*)(s + 0x6c));
    }
    if (*(int**)(s + 0x44)) ((FV_v)(*(void***)*(int**)(s + 0x44))[4 / 4])(*(int**)(s + 0x44));
    if (*(int**)(s + 0x40)) ((FV_v)(*(void***)*(int**)(s + 0x40))[4 / 4])(*(int**)(s + 0x40));
    for (int i = 1; i >= 0; i--) {
        int* p = *(int**)(s + 0x3c - i * 4);
        if (p) ((FV_v)(*(void***)p)[4 / 4])(p);
    }
    if (*(int**)(s + 0x34)) ((FV_v)(*(void***)*(int**)(s + 0x34))[4 / 4])(*(int**)(s + 0x34));
    if (*(int**)(s + 0x30)) ((FV_v)(*(void***)*(int**)(s + 0x30))[4 / 4])(*(int**)(s + 0x30));
    if (*(int**)(s + 0x2c)) ((FV_v)(*(void***)*(int**)(s + 0x2c))[4 / 4])(*(int**)(s + 0x2c));
    if (*(int**)(s + 0x28)) ((FV_v)(*(void***)*(int**)(s + 0x28))[8 / 4])(*(int**)(s + 0x28));
    if (*(int**)(s + 0x24)) ((FV_v)(*(void***)*(int**)(s + 0x24))[8 / 4])(*(int**)(s + 0x24));
    if (*(int**)(s + 0x18)) ((FV_v)(*(void***)*(int**)(s + 0x18))[8 / 4])(*(int**)(s + 0x18));
    if (*(int**)(s + 0x14)) ((FV_v)(*(void***)*(int**)(s + 0x14))[8 / 4])(*(int**)(s + 0x14));
    *(int**)(s + 0x10) = (int*)0x13eb394;
    *(int**)(s + 8) = (int*)0x13eb938;
    *(int**)s = (int*)0x13ec458;
}

// ================================================================ 0x00ed4b70
struct Obj4b70 { void f(); };
void Obj4b70::f()
{
    char* s = (char*)this;
    switch (*(int*)(s + 0x58)) {
    case 1: case 3: case 6:
        ((S_ef00b0*)s)->f();
        *(int*)(s + 0x58) = 0;
        return;
    case 4: {
        ((S_b3d3c0*)FUN_00b3d3c0())->f();
        ((S_b3d3c0*)FUN_00b3d310())->f();
        ((S_b3d3c0*)FUN_00b3d310())->f();
        ((S_b3d3c0*)FUN_00b3d3c0())->f();
        FUN_00efc8c0(0);
        ((S_ef00b0*)(*(int*)(g_16c7aa4 + 0x78)))->f();
        char c = ((S_f46630*)(*(int*)(g_16c7aa4 + 0x74)))->f(s + 0x48);
        if (c) {
            int* sv = (int*)SP_MessageServer();
            ((FV_ii)(*(void***)sv)[0x14 / 4])(sv, 0x86a4609d, 0);
        }
        *(int*)(s + 0x48) = 0;
        *(int*)(s + 0x4c) = 0;
        *(int*)(s + 0x50) = 0;
        *(int*)(s + 0x58) = 0;
        break;
    }
    case 7: {
        int* cm = (int*)SP_CheatManager();
        ((FV_i)(*(void***)cm)[0x20 / 4])(cm, (int)"quit");
        *(int*)(s + 0x58) = 0;
        return;
    }
    }
    *(int*)(s + 0x58) = 0;
}

// ================================================================ 0x00ed4c70
struct Obj4c70 { void f(int flag); };
void Obj4c70::f(int flag)
{
    int* mgr = (int*)FUN_00957f30();
    int* m = (int*)((FV_p)(*(void***)mgr)[4 / 4])(mgr);
    if (m == 0) return;
    int* win = (int*)((FV_iir)(*(void***)m)[0xf0 / 4])(m, 0x2ccda9c, 0);
    char created = 0;
    if (win == 0) {
        if (flag) return;
        void* u = FUN_009512c0();
        int esi = (int)FUN_009512d0(0x20c, 4, "InputCaptureWin", u);
        if (esi != 0) {
            ((S_644b10*)esi)->f();
            *(int*)esi = 0x1414b10;
            *(int*)(esi + 4) = 0x14431f8;
            win = (int*)(esi + 4);
        } else {
            win = 0;
        }
        ((FV_ip)(*(void***)win)[0x50 / 4])(win, 0x2ccda9c);
        ((FV_ip)(*(void***)win)[0x78 / 4])(win, 0x1003);
        void* arg = ((FV_p)(*(void***)m)[0x38 / 4])(m);
        ((FV_i)(*(void***)win)[0x6c / 4])(win, (int)arg);
        ((FV_ff)(*(void***)win)[0x70 / 4])(win, 0.0f, 0.0f);
        ((FV_ii)(*(void***)win)[0x7c / 4])(win, 0x40, 1);
        ((FV_ip)(*(void***)m)[0xd8 / 4])(m, (int)win);
        ((FV_ip)(*(void***)m)[0xe8 / 4])(m, (int)win);
        created = 1;
    } else if (flag) {
        int* mgr2 = (int*)FUN_00957f30();
        int* w2 = (int*)((FV_ip)(*(void***)mgr2)[0x54 / 4])(mgr2, 1);
        if (w2 == win) {
            int* mgr3 = (int*)FUN_00957f30();
            ((FV_ii)(*(void***)mgr3)[0x5c / 4])(mgr3, 1, (int)win);
        }
        int* mgr4 = (int*)FUN_00957f30();
        int* w3 = (int*)((FV_ip)(*(void***)mgr4)[0x54 / 4])(mgr4, 0);
        if (w3 == win) {
            int* mgr5 = (int*)FUN_00957f30();
            ((FV_ii)(*(void***)mgr5)[0x5c / 4])(mgr5, 0, (int)win);
        }
        ((FV_ip)(*(void***)m)[0xe0 / 4])(m, (int)win);
        FUN_00804f50(1);
        return;
    }
    {
        int* g1 = (int*)FUN_00957f30();
        ((FV_ii)(*(void***)g1)[0x4c / 4])(g1, 1, (int)win);
        int* g2 = (int*)FUN_00957f30();
        ((FV_ii)(*(void***)g2)[0x4c / 4])(g2, 0, (int)win);
        int* g3 = (int*)FUN_00957f30();
        ((FV_ii)(*(void***)g3)[0x58 / 4])(g3, 1, (int)win);
        int* g4 = (int*)FUN_00957f30();
        ((FV_ii)(*(void***)g4)[0x58 / 4])(g4, 0, (int)win);
    }
    if (created)
        FUN_008085d0(win, (void*)&FUN_00ed48a0, -1, 0, 0);
}

// ================================================================ 0x00ed4e30
struct Obj4e30 { char pad[0x84]; int f(); };
int Obj4e30::f()
{
    char* s = (char*)this;
    int* p = *(int**)(s + 0x84);
    if (p != 0) {
        if (((FV_q)(*(void***)p)[0x60 / 4])(p) == 0x6ca35b3bull) {
            int* q = (int*)((FV_iir)(*(void***)p)[0x58 / 4])(p, 6, 0);
            int v = *q;
            if (v > 0x7eaf737 && v <= 0x7eaf739)
                return v;
        }
    }
    return 0;
}

// ================================================================ 0x00ed4e90
struct Obj4e90 { void f(); };
void Obj4e90::f()
{
    char* s = (char*)this;
    int* p = *(int**)(s + 0x88);
    if (p != 0) {
        ((FV_i)(*(void***)p)[0xc / 4])(p, 0);
        int* q = *(int**)(s + 0x88);
        if (q != 0) {
            *(int**)(s + 0x88) = 0;
            ((FV_v)(*(void***)q)[4 / 4])(q);
        }
    }
    int* r = *(int**)(s + 0x8c);
    if (r != 0) {
        ((FV_i)(*(void***)r)[0xc / 4])(r, 0);
        int* t = *(int**)(s + 0x8c);
        if (t != 0) {
            *(int**)(s + 0x8c) = 0;
            ((FV_v)(*(void***)t)[4 / 4])(t);
        }
    }
}

// ================================================================ 0x00ed4f00
struct Obj4f00 { void f(int v); };
void Obj4f00::f(int v)
{
    char* s = (char*)this;
    int* p = (int*)((S_8105b0*)(*(int*)(s + 0x24)))->f(0x78d57d8, 1);
    if (p != 0)
        ((FV_ii)(*(void***)p)[0x7c / 4])(p, 2, v);
}

// ================================================================ 0x00ed4f90
struct Obj4f90 { int f(int a, int b); };
int Obj4f90::f(int a, int b)
{
    (void)a;
    char* s = (char*)this;
    int* msg = (int*)b;
    if (msg[2] == 0x287259f6 && msg[3] == 0x7c4b4a0) {
        ((S_f45970*)(*(int*)(g_16c7aa4 + 0x74)))->f();
        int* q = *(int**)(s + 0x50);
        int* r = q ? (int*)((FV_ip)(*(void***)q)[0xc / 4])(q, 0x774c96f) : 0;
        int v = *(int*)((char*)r + 8);
        char c = ((S_e226c0*)s)->f();
        ((S_f3bd90*)(*(int*)(g_16c7aa4 + 0x74)))->f((void*)v, (unsigned char)c);
        ((S_f45a80*)(*(int*)(g_16c7aa4 + 0x74)))->f();
        return 1;
    }
    return 0;
}

// ================================================================ 0x00ed5020
struct Obj5020 { int f(void*, void*, void*, void*, void*); };
int Obj5020::f(void* a1, void* a2, void* a3, void* a4, void* a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    char* s = (char*)this;
    if (*(void**)(s + 0x13c) == a1) {
        int* q = *(int**)(s + 0x50);
        int* r = q ? (int*)((FV_ip)(*(void***)q)[0xc / 4])(q, 0x774c96f) : 0;
        unsigned idx = *(unsigned*)((char*)r + 8);
        unsigned n = ((S_f3bf70*)(*(int*)(g_16c7aa4 + 0x74)))->f();
        int v0 = 0, v1 = 0, v2 = 0;
        if (idx < n) {
            int* v = (int*)((S_f3bfa0*)(*(int*)(g_16c7aa4 + 0x74)))->f(idx);
            v0 = v[0]; v1 = v[1]; v2 = v[2];
        }
        (void)v0; (void)v1; (void)v2;
        return 1;
    }
    return 0;
}

// ================================================================ 0x00ed5190
struct Obj5190 { int f(int w); };
int Obj5190::f(int w)
{
    char* s = (char*)this;
    if (!cSPUIPosseItem_init(s, w)) return 0;
    int* win = (int*)((S_8105b0*)(w + 0x1bc))->f(0x3dae412, 1);
    ((FV_ii)(*(void***)win)[0x7c / 4])(win, 0x10, 1);
    int* q = *(int**)(s + 0x50);
    int* r = q ? (int*)((FV_ip)(*(void***)q)[0xc / 4])(q, 0x774c96f) : 0;
    int b = (*(int*)((char*)r + 8) != -1) ? 1 : 0;
    int* lay = *(int**)(s + 0x13c);
    int* win2 = lay ? (int*)((FV_iir)(*(void***)lay)[0xf0 / 4])(lay, 0x7c4b4a0, 1) : 0;
    if (win2 != 0)
        ((FV_ii)(*(void***)win2)[0x7c / 4])(win2, 1, b);
    return 1;
}

// ================================================================ 0x00ed5220
struct Obj5220 { void* f(); };
void* Obj5220::f()
{
    char* s = (char*)this;
    *(int*)(s + 4) = 0;
    *(int*)(s + 8) = 0x14426a0;
    *(int*)(s + 0x10) = 0x13eb384;
    *(int*)s = 0x1489e8c;
    *(int*)(s + 8) = 0x1489e70;
    *(int*)(s + 0xc) = 0x1489e64;
    *(int*)(s + 0x10) = 0x1489e54;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = -1;
    *(int*)(s + 0x20) = -1;
    for (int off = 0x24; off <= 0x8c; off += 4) *(int*)(s + off) = 0;
    if (SP_MessageServer() != 0) {
        int* sv = (int*)SP_MessageServer();
        ((FV_ii)(*(void***)sv)[0x20 / 4])(sv, 0x65ff54a, (int)(s + 0x10));
    }
    for (int i = 0; i < 2; i++) {
        int off = 0x38 + i * 4;
        int* p = *(int**)(s + off);
        if (p) { *(int**)(s + off) = 0; ((FV_v)(*(void***)p)[4 / 4])(p); }
    }
    return s;
}

// ================================================================ 0x00ed5330
struct Obj5330 { int f(int a); };
int Obj5330::f(int a)
{
    (void)a;
    char* s = (char*)this;
    char* f84 = s + 0x84;
    int* p = *(int**)(s + 0x84);
    if (p != 0 && ((FV_q)(*(void***)p)[0x60 / 4])(p) != 0x6ca35b3bull) {
        ((FV_i)(*(void***)*(int**)f84)[0xc / 4])(*(int**)f84, 0);
        int* q = *(int**)f84;
        if (q != 0) { *(int**)f84 = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
    }
    if (*(int**)f84 == 0) {
        int* em = (int*)SP_EffectsManager();
        int* q = *(int**)f84;
        if (q != 0) { *(int**)f84 = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
        char c = (char)((FV_ipr)(*(void***)em)[0x2c / 4])(em, 0x6ca35b3b);
        if (c) {
            if (FUN_00e00ac0()) ((S_e02e80*)(*(int*)(s + 0x44)))->f();
            ((S_ed4c70*)s)->f(0);
            int* z = *(int**)f84;
            ((FV_ii)(*(void***)z)[0x48 / 4])(z, 6, 1);
            ((FV_i)(*(void***)z)[8 / 4])(z, 0);
            return 1;
        }
    }
    return 0;
}

// ================================================================ 0x00ed5400
struct Obj5400 { void f(int a); };
void Obj5400::f(int a)
{
    (void)a;
    char* s = (char*)this;
    char* f84 = s + 0x84;
    int* p = *(int**)(s + 0x84);
    if (p != 0 && ((FV_q)(*(void***)p)[0x60 / 4])(p) != 0xf08ce134ull) {
        ((FV_i)(*(void***)*(int**)f84)[0xc / 4])(*(int**)f84, 0);
        int* q = *(int**)f84;
        if (q != 0) { *(int**)f84 = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
    }
    if (*(int**)f84 == 0) {
        int* em = (int*)SP_EffectsManager();
        int* q = *(int**)f84;
        if (q != 0) { *(int**)f84 = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
        char c = (char)((FV_ipr)(*(void***)em)[0x2c / 4])(em, 0xf08ce134);
        if (c) {
            int* z = *(int**)f84;
            ((FV_ii)(*(void***)z)[0x48 / 4])(z, 6, 1);
            ((FV_ii)(*(void***)z)[0x64 / 4])(z, 0x7ec5866, 0);
            ((FV_i)(*(void***)z)[8 / 4])(z, 0);
        }
    }
}

// ================================================================ 0x00ed54b0
struct Obj54b0 { void f(int a); };
void Obj54b0::f(int a)
{
    char* s = (char*)this;
    if (*(int**)(s + 0x88) == 0) {
        int* em = (int*)SP_EffectsManager();
        int* q = *(int**)(s + 0x88);
        if (q != 0) { *(int**)(s + 0x88) = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
        char c = (char)((FV_ipr)(*(void***)em)[0x2c / 4])(em, 0x54248876);
        if (c) {
            int* z = *(int**)(s + 0x88);
            ((FV_i)(*(void***)z)[8 / 4])(z, 0);
        }
    }
    if (*(int**)(s + 0x8c) == 0) {
        int* em = (int*)SP_EffectsManager();
        int* q = *(int**)(s + 0x8c);
        if (q != 0) { *(int**)(s + 0x8c) = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
        char c = (char)((FV_ipr)(*(void***)em)[0x2c / 4])(em, 0x14785c1);
        if (c) {
            int* z = *(int**)(s + 0x8c);
            ((FV_i)(*(void***)z)[8 / 4])(z, 0);
        }
    }
    *(int*)(s + 0x90) = a;
}

// ================================================================ 0x00ed5580
bool __stdcall FUN_00ed5580(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
    return false;
}

// ================================================================ 0x00ed5640
struct Obj5640 { void f(); };
void Obj5640::f()
{
    char* s = (char*)this;
    int* mgr = *(int**)(g_16c7aa4 + 0x74);
    int count = ((S_f3bf60*)mgr)->f();
    unsigned count2 = ((S_f3bf70*)mgr)->f();
    int* wm = (int*)SP_WindowManager();
    int* wm2 = (int*)((FV_p)(*(void***)wm)[4 / 4])(wm);
    int* win = (int*)((FV_iir)(*(void***)wm2)[0xf0 / 4])(wm2, 0x774b060, 1);
    if (win != 0)
        ((FV_ii)(*(void***)win)[0x7c / 4])(win, 2, count < 3);
    ((S_e281a0*)(*(int*)(s + 0x40)))->f(1);
    int* x = (int*)FUN_00d539d0();
    if (x != 0) *(int*)((char*)x + 0x18) = count;
    for (int i = 0; i < count; i++) {
        int pos = ((unsigned)i < count2) ? i : -1;
        int* pi = (int*)operator_new(0xc, "Simulator/tPosseIndex", 0, 0, 0, 0);
        if (pi != 0) {
            pi[1] = 0;
            pi[0] = 0x1489eac;
            pi[2] = pos;
        }
        void* u = FUN_009512c0();
        int* item = (int*)FUN_009512d0(0x150, 4, "UI/cScenarioEditPosseItem", u);
        if (item != 0) {
            ((S_e226c0*)item)->f();
            item[0x14c / 4] = 0x140b5a0;
            item[0] = 0x1489d70;
            item[1] = 0x1489d58;
            item[3] = 0x1489d48;
            item[0x14c / 4] = 0x1489d44;
        }
        ((S_e281a0*)(*(int*)(s + 0x40)))->f((int)item);
        if ((unsigned)i < count2) {
            int* v = (int*)((S_f3bfa0*)mgr)->f(i);
            int v0 = v[0], v1 = v[1], v2 = v[2];
            char c = ((S_f3bde0*)mgr)->f(i);
            ((FV_ii)(*(void***)item)[0x90 / 4])(item, (int)&v0, 0);
            ((S_e22700*)item)->f(c);
        }
    }
}
