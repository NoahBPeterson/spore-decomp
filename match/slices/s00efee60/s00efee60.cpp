// Slice s00efee60 -- UI::cScenarioTutorialsChecklistUI helper methods (flag toggles, object
// selection, placement updates, audio cues).  Region flags: /O2 /MD /Gy /TP
//
// `this` layout: +0x00 vtable, +0x05 byte flag, +0x08 pGame (scene/game object), +0x0c pC,
// +0x10 p10.  Global singleton g_mgr at 0x016c7b88.
#include "types.h"

extern void*    g_mgr;           // 0x016c7b88 (singleton pointer variable)
extern float   g_016c7d20;       // 0x016c7d20
extern float   g_016c7d24;       // 0x016c7d24
extern uint8_t g_016065f8;       // 0x016065f8
extern uint8_t g_015ad298[];     // 0x015ad298

extern "C" void* __cdecl FUN_00b3d350(void*, void*);        // SP::PlanetModel (cdecl factory)
extern "C" void* __cdecl FUN_00b18e00(void*);               // get object from handle
extern "C" void* __cdecl EA_Audio_GetSystemAT();            // 0x00a206f0
extern "C" void* __cdecl FUN_00f43420(void*, void*);        // 0x00f43420
extern "C" void* __cdecl FUN_00f3e8a0(int);                 // 0x00f3e8a0
extern "C" void* __cdecl FUN_00f44370(int, void*, void*, float); // 0x00f44370
extern "C" void* __cdecl FUN_00ae66d0(void*);               // 0x00ae66d0
extern "C" void  __cdecl FUN_00f352e0();                    // 0x00f352e0
extern "C" void* __cdecl FUN_0067dd10();                    // 0x0067dd10
extern "C" void  __cdecl FUN_00efccd0();                    // 0x00efccd0
extern "C" void  __cdecl FUN_00f32410();                    // 0x00f32410

struct GObj {
    char pad0[0x400];
    void F43970();
    void BSO(void*, void*);        // 0x00b7f190 BuildSurfaceOrientation
    char FC930();                  // 0x00efc930
    char FC7D0(void*, void*);      // 0x00efc7d0
    void* F32790(void*);           // 0x00f32790 ret 4
    void F33BF0();                 // 0x00f33bf0
    void F38150(void*);            // 0x00f38150 ret 4
    void F34560();                 // 0x00f34560
    void* F336A0(void*);           // 0x00f336a0 ret 4
    void* F33640(void*);           // 0x00f33640 ret 4
    void* F329E0(void*, void*);    // 0x00f329e0 ret 8
    void F36450(int, int, void*);  // 0x00f36450 ret 0xc
    void F38330(int);              // 0x00f38330 ret 4
    void F427C0();                 // 0x00f427c0
    void F45970();
};
struct AudioAT {
    void v38(int);
    void v3c(int, float);
    void v40(int, int);
    void v58();
};
struct Manager {
    void v0();
};
struct VObj {
    void v0();
    void v4();
    void v38(void*);
    void v3c(void*);
    void v40(float);
};
struct RefObj {
    void v0();
    void v4();
};
struct Handle {
    void* v0c(int);               // vtable slot 0xc
};

// UI self-methods implemented elsewhere in the TU / this slice.
struct UI {
    void* vtable;      // +0x00
    uint8_t f4;        // +0x04
    uint8_t b5;        // +0x05
    char pad6[2];
    GObj* pGame;       // +0x08
    void* pC;          // +0x0c
    void* p10;         // +0x10

    void SetSelectedObject();      // 0x00efe260
    void FwdC6E0(void*);           // 0x00efc6e0 ret 4
    char f_efc930();               // 0x00efc930
    char f_efc7d0(void*, void*);   // 0x00efc7d0 ret 8

    void  f_efee60(void*);         // 0x00efee60
    void* f_efeee0(int);           // 0x00efeee0
    void  f_efefe0();              // 0x00efefe0
    void  f_eff030();              // 0x00eff030
    void  f_eff0c0();              // 0x00eff0c0
    bool  f_eff1e0();              // 0x00eff1e0
    void  f_eff230(void*);         // 0x00eff230
    void  f_eff280(void*);         // 0x00eff280
    void  f_eff360(void*);         // 0x00eff360
    void  f_eff3b0();              // 0x00eff3b0
    void  f_eff4c0(void*, float);  // 0x00eff4c0 ret 8
    void* f_eff590();              // 0x00eff590
    void  f_eff600(int);           // 0x00eff600 ret 4
};

void __cdecl f_eff6c0(void* obj, char flag);   // 0x00eff6c0
void __cdecl f_eff760(void* obj, char flag);   // 0x00eff760
struct Mgr2 { bool v38(); };

// @ 0x00efee60
void UI::f_efee60(void* p)
{
    GObj* g = pGame;
    void* q = *(void**)((char*)g_mgr + 0xc);
    void* e = p;
    if (q) e = q;
    if (b5) {
        b5 = 0;
        SetSelectedObject();
        FwdC6E0(e);
        return;
    }
    if (q == 0) {
        g->F45970();
        SetSelectedObject();
        if (e) {
            void* r = ((Handle*)e)->v0c(0x74e0069);
            if (r) *(uint8_t*)((char*)r + 0x12b) = 0;
        }
    }
    FwdC6E0(e);
}

// @ 0x00efeee0
void* UI::f_efeee0(int param)
{
    char local1c[12];
    char local10[8];
    f_efc930();
    void* model = FUN_00b3d350(local10, local1c);
    ((GObj*)model)->BSO(local10, local1c);
    void* r;
    if (param == -2) {
        r = FUN_00f43420(local1c, local10);
    } else {
        FUN_00f3e8a0(param);
        r = FUN_00f44370(param, local1c, local10, -1.0f);
    }
    pGame->F427C0();
    g_016c7d20 = (g_016c7d20 == 0.0f) ? 1.0f : 0.0f;
    AudioAT* at = (AudioAT*)EA_Audio_GetSystemAT();
    if (at) {
        at->v38(0x3cdd1a9);
        at->v40(0x34753a7, 0xcb1fdf45);
        at->v3c(0x34753aa, g_016c7d20);
        at->v58();
    }
    return r;
}

// @ 0x00efefe0
void UI::f_efefe0()
{
    void* u = *(void**)((char*)g_mgr + 4);
    if (pGame->F32790(u) != 0) {
        pGame->F33BF0();
        ((void(__thiscall*)(void*, int)) * ((void**)vtable + 0x20 / 4))(this, 0);
        pGame->F38150(u);
        pGame->F34560();
    }
}

// @ 0x00eff030
void UI::f_eff030()
{
    int* pc = (int*)pC;
    if (pc[0] == 0) return;
    if (!f_efc7d0((void*)pc[0], (void*)pc[1])) return;
    if (!f_efc930()) return;
    pGame->F33BF0();
    void* r = pGame->F336A0(pC);
    if (r == 0) return;
    VObj* o = (VObj*)FUN_00b18e00(r);
    int local;
    o->v38(&local);
    pGame->F36450(0, 0, r);
    pGame->F38330(1);
    pGame->F34560();
}

// @ 0x00eff0c0
void UI::f_eff0c0()
{
    // approximate: placement/visibility update driven by g_mgr fields.
    if (*(int*)((char*)g_mgr + 0x20) == 0) return;
}

// @ 0x00eff1e0
bool UI::f_eff1e0()
{
    void* a = *(void**)((char*)g_mgr + 4);
    if (a == 0) return false;
    void* r = pGame->F32790(a);
    if (r == 0) return false;
    float* o = (float*)(*(void**)((char*)r + 4));
    return (float)(o[0x64 / 4] > o[0x60 / 4]) != 0.0f;
}

// @ 0x00eff230
void UI::f_eff230(void* p)
{
    *(uint8_t*)((char*)g_mgr + 0x64) = 1;
    *(int*)((char*)g_mgr + 0x68) = 1;
    void** slot = (void**)((char*)g_mgr + 0xc);
    void* old = *slot;
    if (p != old) {
        if (p) ((RefObj*)p)->v0();
        *slot = p;
        if (old) ((RefObj*)old)->v4();
    }
}

// @ 0x00eff280
void UI::f_eff280(void* p)
{
    // approximate
    (void)p;
}

// @ 0x00eff360
void UI::f_eff360(void* p)
{
    if (b5) {
        void* u = *(void**)((char*)g_mgr + 4);
        b5 = 0;
        f_eff230(u);
        return;
    }
    pGame->F33BF0();
    pGame->F36450(0, 0, p);
    f_eff230(p);
}

// @ 0x00eff3b0
void UI::f_eff3b0()
{
    // approximate
    if (*(int*)((char*)g_mgr + 0xc) != 0) {
        *(void**)((char*)g_mgr + 0xc) = 0;
    }
}

// @ 0x00eff4c0
void UI::f_eff4c0(void* p, float f)
{
    // approximate
    (void)p; (void)f;
}

// @ 0x00eff590
void* UI::f_eff590()
{
    char local10[8];
    char local1c[12];
    f_efc930();
    void* model = FUN_00b3d350(local10, local1c);
    ((GObj*)model)->BSO(local10, local1c);
    void* r = pGame->F33640(p10);
    VObj* o = (VObj*)FUN_00b18e00(r);
    int a, b;
    o->v38(&a);
    o->v3c(&b);
    o->v40(1.0f);
    return r;
}

// @ 0x00eff600
void UI::f_eff600(int arg)
{
    if (g_016065f8 == 0) return;
    (void)arg;
}

// @ 0x00eff6c0
void __cdecl f_eff6c0(void* obj, char flag)
{
    if (obj == 0) return;
    void* r = FUN_00ae66d0(obj);
    ((GObj*)obj)->BSO((void*)0, (void*)0);
    (void)r; (void)flag;
}

// @ 0x00eff760
void __cdecl f_eff760(void* obj, char flag)
{
    if (obj == 0) return;
    Mgr2* m = *(Mgr2**)&g_015ad298;
    if (m->v38()) return;
    f_eff6c0(obj, flag);
}
