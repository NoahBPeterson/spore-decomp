// slice s00f38330 -- Simulator / cSPUISpace UI-object helpers (0x00f38330..0x00f39220).
//
// cSPUISpace "seti" panel: object create/destroy, message handling, a 4-digit
// clock display, a cCivTokenTranslator and its string members.  Module flags
// /O2 /MD /Gy /TP.
#include "types.h"

extern void* g_15ad298;                     // 0x015ad298: UI system object pointer

// --- free callees (signatures per call site) ---
void* __cdecl   operator_new(int, const char*, int, int, int, int);
void  __cdecl   operator_del(void*);
void  __cdecl   FUN_00f373a0(int, int, int, int, float, float);
void  __cdecl   FUN_00f372b0(int, int, int, float);
void  __cdecl   FUN_00f32d10();
void  __cdecl   FUN_00f37b60();
void* __cdecl   FUN_00b18e00(void*);
int   __cdecl   FUN_00edc9e0(void*, int);
void  __cdecl   FUN_00435e90();
void  __cdecl   FUN_00aea5d0(void*, void*);
void  __cdecl   FUN_00b32490();
void  __cdecl   FUN_00b32470();
char  __cdecl   FUN_005bf0e0(int, void*);
char  __cdecl   FUN_005bf1e0(void*, void*);
void  __cdecl   FUN_00595a90(int);
int   __cdecl   FUN_00595230(void*);
void  __cdecl   FUN_00593960(int, int, void*, void*);
void  __cdecl   FUN_00f38ab0(int self, int v);        // thunk_FUN_00f388b0 @ f38ab0
void  __cdecl   cSPUILayout_Init_();
void* __cdecl   cString_ctor_dummy();

char  __cdecl   cSPUILayout_Init(void* p, void* rk, int a, int b);
void  __cdecl   cSPUILayout_Shutdown(void* p, int a);
void  __cdecl   cSPUILayout_SetParentWin(void* p, void* w, int a, int b);
void* __cdecl   cSPUILayout_FindWindowByID(void* p, int id, int a);
void* __cdecl   CenterWindowInRect();
void* __cdecl   SP_MessageServer();
void* __cdecl   SP_WindowManager();
void  __cdecl   EA_Messaging_RemoveHandler(int, int, int, int, int);
void* __cdecl   EA_GetSystemAT();

// generic virtual-call helpers (the real callees are masked relocations; the
// exact receiver convention only matters for byte-matching, not behaviour).
static inline void  vc0(void* o, int off) { ((void(__cdecl*)(void*))((void**)*(void***)o)[off/4])(o); }
static inline char  vcc0(void* o, int off) { return ((char(__cdecl*)(void*))((void**)*(void***)o)[off/4])(o); }
static inline void* vcp0(void* o, int off) { return ((void*(__cdecl*)(void*))((void**)*(void***)o)[off/4])(o); }
static inline void  vcv1(void* o, int off, int a) { ((void(__cdecl*)(void*,int))((void**)*(void***)o)[off/4])(o,a); }
static inline char  vcc1(void* o, int off, int a) { return ((char(__cdecl*)(void*,int))((void**)*(void***)o)[off/4])(o,a); }
static inline void* vcp1(void* o, int off, int a) { return ((void*(__cdecl*)(void*,int))((void**)*(void***)o)[off/4])(o,a); }

// member contexts
struct Ctx { void f32bf0(int); void f37b60(); void f1c(int); };
struct UIHelpers { void* Center(); };
struct SpaceObj {
    int  f385a0(int k); int f38890(char del); int f38b30(int k);
    void f38b60(int v); void f38b90(int v); void f38bc0(int v);
    int  f38d70(char del); int f38e80(int* win); int f38930(int msg, int* d);
    void f38ac0(char show); int f38d90(int msg, void* d); int f388b0(int v);
};

// ===========================================================================
// 0x00f38330 -- per-tile transform/mesh update
// ===========================================================================
struct Obj38330 { void run(char flag); };
void Obj38330::run(char flag) {
    int self = (int)this;
    int* pv = *(int**)(self + 0x1b0);
    if (!pv) return;
    int iVar2 = pv[2];
    int iVar1 = pv[1];
    int* piVar4 = (int*)FUN_00b18e00((void*)pv[0]);
    pv = *(int**)(self + 0x1b0);
    int* piVar5 = (int*)FUN_00b18e00((void*)pv[0]);
    int iVar11 = pv[1];
    float f14 = *(float*)(iVar11 + 0x60);
    float f13 = ((float(__cdecl*)(int*))(*(void***)piVar5)[0x34/4])(piVar5);
    int iVar3 = *(int*)(*(int*)(self + 0x1b0) + 4);
    f14 = (*(float*)(iVar11 + 100) - f14) * (f13 - 3.0f) + f14;
    float f15 = *(float*)(iVar3 + 0x58);
    f15 = (*(float*)(iVar3 + 0x5c) - f15) * *(float*)(*(int*)(self + 0x1b0) + 0xc) + f15;
    if (*(char*)(self + 0x1b8) == 0) {
        vcp0(piVar4, 0x2c);
        vcp0(piVar4, 0x30);
    } else {
        int uVar9 = *(int*)(iVar1 + 0x30);
        if (*(char*)(iVar1 + 0x68) == 0) {
            int a = (int)vcp0(piVar4, 0x30);
            int b = (int)vcp1(piVar4, 0x2c, a);
            FUN_00f373a0(uVar9, 0, b, a, f14, f15);
        } else {
            int a = (int)vcp0(piVar4, 0x30);
            int b = (int)vcp1(piVar4, 0x2c, a);
            FUN_00f372b0(uVar9, b, a, f14);
        }
    }
    (void)iVar2;
    FUN_00f32d10();
    *(char*)(self + 0x1ba) = 1;
    if (flag) FUN_00f37b60();
}

// ===========================================================================
// 0x00f38540 / 0x00f38570 -- close a sub-window and refresh
// ===========================================================================
struct V20 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
             virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
             virtual void q(int); };
void __fastcall FUN_00f38540(int* self) {
    int v = *(int*)((char*)self + 0xc);
    ((V20*)g_15ad298)->q(0);
    (*(Ctx**)((char*)self + 0x3c))->f32bf0(v);
    return (*(Ctx**)((char*)self + 0x3c))->f37b60();
}
void __fastcall FUN_00f38570(int* self) {
    int v = *(int*)((char*)self + 0x24);
    ((V20*)g_15ad298)->q(0);
    (*(Ctx**)((char*)self + 0x3c))->f32bf0(v);
    return (*(Ctx**)((char*)self + 0x3c))->f37b60();
}

// ===========================================================================
// 0x00f385a0 -- query-interface style filter
// ===========================================================================
int SpaceObj::f385a0(int k) {
    int self = (int)this;
    if (k == (int)0xee3f516e || k == 0x7c3ea9f) return self;
    return self & ((k != 0x2f009dd0) - 1);
}

// ===========================================================================
// 0x00f385d0 -- construct the seti panel object
// ===========================================================================
void __fastcall FUN_00f385d0(int* p) {
    *(int*)((char*)p + 4) = 0;
    *(int*)((char*)p + 8) = 0;
    *(int*)((char*)p + 0xc) = 0;
    *(int*)((char*)p + 0x10) = 0;
    *(int*)((char*)p + 0x14) = 0;
    *(int*)((char*)p + 0x18) = 0;
    *(int*)((char*)p + 0x28) = 0;
}

// ===========================================================================
// 0x00f38600 -- adjustor thunk (derived -> base at -4)
// ===========================================================================
int __fastcall FUN_00f38600(int p) { return p; }

// ===========================================================================
// 0x00f38610 -- destruct the seti panel object
// ===========================================================================
void __fastcall FUN_00f38610(int* p) {
    if (*(int**)((char*)p + 0x28)) vc0(*(void**)((char*)p + 0x28), 8);
    if (*(int**)((char*)p + 0x18)) vc0(*(void**)((char*)p + 0x18), 4);
    if (*(int**)((char*)p + 0x14)) vc0(*(void**)((char*)p + 0x14), 4);
    if (*(int**)((char*)p + 0x10)) vc0(*(void**)((char*)p + 0x10), 4);
    if (*(int**)((char*)p + 0xc))  vc0(*(void**)((char*)p + 0xc),  4);
}

// ===========================================================================
// 0x00f38680 -- initialise the seti panel layout
// ===========================================================================
int __fastcall FUN_00f38680(int self, int* win, int count) {
    int* old = *(int**)(self + 0xc);
    if (win != old) {
        if (win) vc0(win, 0);
        *(int**)(self + 0xc) = win;
        if (old) vc0(old, 4);
    }
    *(char*)(self + 0x24) = 0;
    *(int*)(self + 0x1c) = 0;
    *(int*)(self + 0x20) = count;
    if (!*(int*)(self + 0xc)) return 1;
    void* obj = operator_new(0x18, "", 0, 0, 0, 0);
    int* layout = obj ? (int*)CenterWindowInRect() : 0;
    int* pl = *(int**)(self + 0x28);
    if (layout != pl) {
        if (layout) vc0(layout, 4);
        *(int**)(self + 0x28) = layout;
        if (pl) vc0(pl, 8);
    }
    if (!cSPUILayout_Init(*(void**)(self + 0x28), (void*)0, 0, 0x5b598fa)) {
        cSPUILayout_Shutdown(*(void**)(self + 0x28), 1);
        int* q = *(int**)(self + 0x28);
        if (q) { *(int*)(self + 0x28) = 0; vc0(q, 8); }
        return 0;
    }
    cSPUILayout_SetParentWin(*(void**)(self + 0x28), *(void**)(self + 0xc), 1, 0x5b598fa);
    // find child windows
    int* w = (int*)cSPUILayout_FindWindowByID(*(void**)(self + 0x28), 0x7c3eca1, 1);
    int* t = *(int**)(self + 0x10);
    if (w != t) { if (w) vc0(w, 0); *(int**)(self + 0x10) = w; if (t) vc0(t, 4); }
    w = (int*)cSPUILayout_FindWindowByID(*(void**)(self + 0x28), 0x7c3ed43, 1);
    t = *(int**)(self + 0x14);
    if (w != t) { if (w) vc0(w, 0); *(int**)(self + 0x14) = w; if (t) vc0(t, 4); }
    w = (int*)cSPUILayout_FindWindowByID(*(void**)(self + 0x28), 0x7c3edb7, 1);
    t = *(int**)(self + 0x18);
    if (w != t) { if (w) vc0(w, 0); *(int**)(self + 0x18) = w; if (t) vc0(t, 4); }
    for (int i = 0; i < 10; i++) {
        int* c = (int*)cSPUILayout_FindWindowByID(*(void**)(self + 0x28), i + 0x7c40930, 1);
        if (c) vcv1(c, 0x7c, i <= *(int*)(self + 0x20));
    }
    return 1;
}

// ===========================================================================
// 0x00f38850 -- shutdown the seti panel
// ===========================================================================
void __fastcall FUN_00f38850(int* p) {
    vcv1(p, 0x28, 0);
    int* q = (int*)p[3];
    if (q) { p[3] = 0; vc0(q, 4); }
    if (p[10]) cSPUILayout_Shutdown((void*)p[10], 1);
}

// ===========================================================================
// 0x00f38890 -- scalar deleting destructor
// ===========================================================================
int SpaceObj::f38890(char del) {
    int p = (int)this;
    FUN_00f38610(0);
    if (del & 1) operator_del((void*)p);
    return p;
}

// ===========================================================================
// 0x00f388b0 -- set the displayed number
// ===========================================================================
struct CStr16 { char pad0[0x18]; void* p18; char pad1c[4]; int v; };
int SpaceObj::f388b0(int v) {
    int self = (int)this;
    *(int*)(self + 0x1c) = v;
    if (*(int*)(self + 0x18)) {
        void* s = 0;
        vcv1(*(void**)(self + 0x18), 0x80, (int)&s);
    }
    return v;
}

// ===========================================================================
// 0x00f38930 -- message handler
// ===========================================================================
int SpaceObj::f38930(int msg, int* d) {
    int self = (int)this;
    if (d[2] == 0x1c) {
        if (d[3] == 0) {
            void* wm = SP_WindowManager();
            void* w = vcp0(wm, 0x48);
            if (!FUN_00edc9e0(w, 0x7c3ed43) && *(int**)(self + 0x14)) {
                vcv1(*(void**)(self + 0x14), 0x7c, 0);
                *(char*)(self + 0x24) = 0;
                void* at = EA_GetSystemAT();
                if (at) vc0(at, 0x20);
                FUN_00435e90();
            }
        }
    } else if (d[2] == 0x287259f6) {
        if (d[3] == 0x7c3edb7) {
            if (*(int**)(self + 0x14)) {
                int on = *(char*)(self + 0x24) == 0;
                vcv1(*(void**)(self + 0x14), 0x7c, on);
                *(char*)(self + 0x24) = on;
                FUN_00435e90();
            }
            void* ms = SP_MessageServer();
            vcv1(ms, 0x14, 0x7c41aeb);
            return 1;
        }
        int i = d[3] - 0x7c40930;
        if (i >= 0 && i <= *(int*)(self + 0x20)) {
            ((SpaceObj*)self)->f388b0(i);
            if (*(int**)(self + 0x14)) { vcv1(*(void**)(self + 0x14), 0x7c, 0); *(char*)(self + 0x24) = 0; }
            FUN_00435e90();
            void* ms = SP_MessageServer();
            vcv1(ms, 0x14, 0x7c41aea);
            return 0;
        }
    }
    return 0;
}

// ===========================================================================
// 0x00f38ac0 -- show / hide the panel
// ===========================================================================
void SpaceObj::f38ac0(char show) {
    int self = (int)this;
    if (show) ((SpaceObj*)self)->f388b0(*(int*)(self + 0x1c));
    if (*(int*)(self + 0x28)) {
        if (*(int**)(self + 0x18)) {
            if (show) vc0(*(void**)(self + 0x18), 0x104);
            else      vc0(*(void**)(self + 0x18), 0x108);
        }
        if (*(int**)(self + 0x14)) {
            if (show) { vc0(*(void**)(self + 0x14), 0x104); return; }
            vc0(*(void**)(self + 0x14), 0x108);
        }
    }
}

// ===========================================================================
// 0x00f38b30 -- query-interface style filter (variant)
// ===========================================================================
int SpaceObj::f38b30(int k) {
    int self = (int)this;
    if (k != (int)0xee3f516e) {
        if (k == 0x7c3e995) return self - 4;
        if (k != 0x2f009dd0) return 0;
    }
    return -(int)(self != 4) & self;
}

// ===========================================================================
// 0x00f38b60 / 0x00f38b90 -- broadcast to child widgets
// ===========================================================================
struct V28 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
             virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
             virtual void p8(); virtual void p9(); virtual void q(int); };
struct V24v { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
              virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
              virtual void p8(); virtual void q(int); };
void SpaceObj::f38b60(int v) {
    int self = (int)this;
    int* p = *(int**)(self + 0x2c);
    if (p == *(int**)(self + 0x30)) return;
    do { ((V28*)*p)->q(v); p++; } while (p != *(int**)(self + 0x30));
}
void SpaceObj::f38b90(int v) {
    int self = (int)this;
    int* p = *(int**)(self + 0x2c);
    if (p == *(int**)(self + 0x30)) return;
    do { ((V24v*)*p)->q(v); p++; } while (p != *(int**)(self + 0x30));
}

// ===========================================================================
// 0x00f38bc0 -- set a hh:mm clock from a second count
// ===========================================================================
void SpaceObj::f38bc0(int v) {
    int self = (int)this;
    if (((*(int*)(self + 0x30) - *(int*)(self + 0x2c)) & 0xfffffffc) == 0x10) {
        int* w = *(int**)(self + 0x2c);
        FUN_00f38ab0(w[0], (v % 0x3c) % 10);
        FUN_00f38ab0(w[1], (v % 0x3c) / 10);
        FUN_00f38ab0(w[2], (v / 0x3c) % 10);
        FUN_00f38ab0(w[3], (v / 0x3c) / 10);
    }
}

// ===========================================================================
// 0x00f38c70 -- construct the large-asset-view object
// ===========================================================================
void __fastcall FUN_00f38c70(int* p) {
    p[3] = 0; p[4] = 0; p[5] = 0; p[6] = 0; p[7] = 0; p[8] = 0;
    p[9] = 0; p[10] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0; p[0x10] = 0;
}

// ===========================================================================
// 0x00f38cc0 / 0x00f38cd0 -- adjustor thunks
// ===========================================================================
int __fastcall FUN_00f38cc0(int p) { return p; }
int __fastcall FUN_00f38cd0(int p) { return p; }

// ===========================================================================
// 0x00f38ce0 -- destruct the large-asset-view object
// ===========================================================================
void __fastcall FUN_00f38ce0(int* p) {
    if (p[0x10]) vc0((void*)p[0x10], 4);
    if (p[6]) { int h = p[6]; p[6] = 0; EA_Messaging_RemoveHandler(h, p[7], p[8], p[9], p[10]); }
    if (p[5]) vc0((void*)p[5], 8);
    if (p[4]) vc0((void*)p[4], 4);
}

// ===========================================================================
// 0x00f38d70 -- scalar deleting destructor
// ===========================================================================
int SpaceObj::f38d70(char del) {
    int p = (int)this;
    FUN_00f38ce0(0);
    if (del & 1) operator_del((void*)p);
    return p;
}

// ===========================================================================
// 0x00f38d90 -- post a UI behavior message
// ===========================================================================
int SpaceObj::f38d90(int msg, void* d) {
    int self = (int)this;
    if (msg == 0x7c41aea &&
        ((*(int*)(self + 0x30) - *(int*)(self + 0x2c)) & 0xfffffffc) == 0x10 &&
        vcc1(*(void**)(self + 0x10), 0xf8, (int)d)) {
        int* piVar6 = *(int**)(self + 0x2c);
        int iVar1 = *(int*)(piVar6[3] + 0x1c);
        int iVar2 = *(int*)(piVar6[2] + 0x1c);
        int iVar3 = *(int*)(piVar6[1] + 0x1c);
        int iVar4 = *(int*)(piVar6[0] + 0x1c);
        (void)iVar1; (void)iVar2; (void)iVar3; (void)iVar4;
    }
    return 0;
}

// ===========================================================================
// 0x00f38e80 -- initialise the large-asset-view UI
// ===========================================================================
int SpaceObj::f38e80(int* win) {
    int self = (int)this;
    int* p = *(int**)(self + 0x10);
    if (win != p) {
        if (win) vc0(win, 0);
        *(int**)(self + 0x10) = win;
        if (p) vc0(p, 4);
    }
    if (*(int**)(self + 0x40)) { int* q = *(int**)(self + 0x40); *(int*)(self + 0x40) = 0; vc0(q, 4); }
    if (!*(int*)(self + 0x10)) { /* register message handler below */ }
    else {
        void* obj = operator_new(0x18, "", 0, 0, 0, 0);
        int* layout = obj ? (int*)CenterWindowInRect() : 0;
        int* pl = *(int**)(self + 0x14);
        if (layout != pl) { if (layout) vc0(layout,4); *(int**)(self + 0x14) = layout; if (pl) vc0(pl,8); }
        if (!cSPUILayout_Init(*(void**)(self + 0x14), (void*)0, 0, 0x5b598fa)) {
            cSPUILayout_Shutdown(*(void**)(self + 0x14), 1);
            int* q = *(int**)(self + 0x14);
            if (q) { *(int*)(self + 0x14) = 0; vc0(q, 8); }
            return 0;
        }
        cSPUILayout_SetParentWin(*(void**)(self + 0x14), *(void**)(self + 0x10), 1, 0x5b598fa);
        int id = 0x7c3ebe0;
        for (int i = 4; i != 0; i--) {
            int* w = (int*)operator_new(0x2c, "", 0, 0, 0, 0);
            w = w ? (int*)(FUN_00f385d0(w), w) : 0;
            int n = (id == 0x7c3ebe1 || id == 0x7c3ebe3) ? 5 : 9;
            void* found = cSPUILayout_FindWindowByID(*(void**)(self + 0x14), id, 1);
            vcv1(w, 0x1c, (int)found); (void)n;
            vc0(w, 0);
            id++;
        }
    }
    void* ms = SP_MessageServer();
    *(void**)(self + 0x18) = ms;
    *(int*)(self + 0x1c) = self;
    *(int*)(self + 0x24) = 1;
    *(int*)(self + 0x28) = 0;
    if (ms) vcv1(ms, 0x24, 0x7c41aea);
    return 1;
}

// ===========================================================================
// 0x00f39080 -- shutdown the large-asset-view UI
// ===========================================================================
void __fastcall FUN_00f39080(int* p) {
    vcv1(p, 0x1c, 0);
    int* w = (int*)p[0xb];
    if (w != (int*)p[0xc]) {
        do { vc0((void*)*w, 0x20); w++; } while (w != (int*)p[0xc]);
    }
    if (p[6]) { int h = p[6]; p[6] = 0; EA_Messaging_RemoveHandler(h, p[7], p[8], p[9], p[10]); }
    int* q = (int*)p[4];
    if (q) { p[4] = 0; vc0(q, 4); }
    if (p[5]) cSPUILayout_Shutdown((void*)p[5], 1);
}

// ===========================================================================
// 0x00f39110 -- construct a cString
// ===========================================================================
struct CString { void* p; };
struct CStringCls { void ctor(int, int, int); };
CString* __cdecl FUN_00f39110(CString* out) {
    ((CStringCls*)out)->ctor(0x8b1a2341, 0x7c4093a, 0);
    return out;
}

// ===========================================================================
// 0x00f39130 -- read a value out of a property
// ===========================================================================
unsigned char __cdecl FUN_00f39130(int prop) {
    void* a = 0;
    unsigned char r = 0;
    if (FUN_005bf0e0(prop, &a)) {
        void* b = 0;
        if (FUN_005bf1e0(a, &b)) {
            FUN_00595a90(prop);
            char tmp[8];
            r = (unsigned char)FUN_00595230(tmp);
        }
        if (b) vc0(b, 4);
    }
    if (a) vc0(a, 4);
    return r;
}

// ===========================================================================
// 0x00f391c0 -- construct a cCivTokenTranslator
// ===========================================================================
extern wchar_t* DAT_01667bac;
extern wchar_t* DAT_01667bae;
void* __fastcall FUN_00f391c0(void* p) {
    FUN_00b32470();
    *(int*)((char*)p + 0xc) = 0;
    *(int*)((char*)p + 0x10) = 0;
    *(int*)((char*)p + 0x14) = 0;
    *(int*)((char*)p + 0x18) = 0;
    *(int*)((char*)p + 0x1c) = 0;
    *(int*)((char*)p + 0x20) = -1;
    *(wchar_t***)((char*)p + 0x24) = &DAT_01667bac;
    *(wchar_t***)((char*)p + 0x28) = &DAT_01667bac;
    *(wchar_t***)((char*)p + 0x2c) = &DAT_01667bae;
    *(wchar_t***)((char*)p + 0x34) = &DAT_01667bac;
    *(wchar_t***)((char*)p + 0x38) = &DAT_01667bac;
    *(wchar_t***)((char*)p + 0x3c) = &DAT_01667bae;
    *(wchar_t***)((char*)p + 0x44) = &DAT_01667bac;
    *(wchar_t***)((char*)p + 0x48) = &DAT_01667bac;
    *(wchar_t***)((char*)p + 0x4c) = &DAT_01667bae;
    *(wchar_t***)((char*)p + 0x54) = &DAT_01667bac;
    *(wchar_t***)((char*)p + 0x58) = &DAT_01667bac;
    *(wchar_t***)((char*)p + 0x5c) = &DAT_01667bae;
    return p;
}

// ===========================================================================
// 0x00f39220 -- destruct a cCivTokenTranslator
// ===========================================================================
void __fastcall FUN_00f39220(int* p) {
    int* b;
    b = (int*)p[0x15]; if (((char*)p[0x17] - (char*)b) && (((char*)p[0x17] - (char*)b) & 0xfffffffe) > 2 && b) operator_del(b);
    b = (int*)p[0x11]; if (((char*)p[0x13] - (char*)b) && (((char*)p[0x13] - (char*)b) & 0xfffffffe) > 2 && b) operator_del(b);
    b = (int*)p[0xd];  if (((char*)p[0xf]  - (char*)b) && (((char*)p[0xf]  - (char*)b) & 0xfffffffe) > 2 && b) operator_del(b);
    b = (int*)p[9];    if (((char*)p[0xb]  - (char*)b) && (((char*)p[0xb]  - (char*)b) & 0xfffffffe) > 2 && b) operator_del(b);
    FUN_00b32490();
}
