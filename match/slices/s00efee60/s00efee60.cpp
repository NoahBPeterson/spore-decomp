// Slice s00efee60 -- UI::cScenarioTutorialsChecklistUI helper methods (flag toggles, object
// selection, placement updates, audio cues).  Region flags: /O2 /MD /Gy /TP
//
// `this` layout: +0x00 vtable, +0x05 byte flag, +0x08 pGame (scene/game object), +0x0c pC,
// +0x10 p10.  Global singleton g_mgr at 0x016c7b88.
#include "types.h"

static inline void** Vt(void* p) { return *(void***)p; }

// Inline vtable-slot dispatch. The regions below talk to engine objects through their vtables;
// spelling the dispatch out as function-pointer casts keeps the object file free of undefined
// member references (the equivalence harness cannot bind those).
static inline void VCall0(void* p, int slot)             { ((void (__thiscall*)(void*))(*(void***)p)[slot / 4])(p); }
static inline void VCall1(void* p, int slot, int a)      { ((void (__thiscall*)(void*, int))(*(void***)p)[slot / 4])(p, a); }
static inline void VCall1P(void* p, int slot, void* a)   { ((void (__thiscall*)(void*, void*))(*(void***)p)[slot / 4])(p, a); }
static inline void VCall2I(void* p, int slot, int a, int b)   { ((void (__thiscall*)(void*, int, int))(*(void***)p)[slot / 4])(p, a, b); }
static inline void VCall2F(void* p, int slot, int a, float b) { ((void (__thiscall*)(void*, int, float))(*(void***)p)[slot / 4])(p, a, b); }
static inline bool VCallB(void* p, int slot)             { return ((bool (__thiscall*)(void*))(*(void***)p)[slot / 4])(p); }

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
    char pad0[0x1b0];
    void* p1b0;            // +0x1b0
    char pad1b4[0x400 - 0x1b4];
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
    void* F329E0(void*);           // 0x00f329e0 ret 4
    void F36450(int, int, void*);  // 0x00f36450 ret 0xc
    void F38330(int);              // 0x00f38330 ret 4
    void F32410();                 // 0x00f32410
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
    void v58();                    // vtable slot +0x58
};
struct RefObj {
    void v0();
    void v4();
};
struct Handle {
    void* v0c(int);               // vtable slot 0xc
};

struct OrientationState {
    char pad0[0x58];
    float f58;     // +0x58
    float f5c;     // +0x5c
    float f60;     // +0x60
    float f64;     // +0x64
    float f68;     // +0x68
    float f6c;     // +0x6c
    float f70;     // +0x70
};

struct Object1b0 {
    char pad0[4];
    OrientationState* p4;  // +0x04
    char pad8[4];
    float value0c;         // +0x0c
};

struct PlacementView {
    char pad0[4];
    OrientationState* p4;  // +0x04
};

struct MgrState {
    char pad0[4];
    void* handle;          // +0x04
    void* p8;              // +0x08
    void* pC;              // +0x0c
    void* p10;             // +0x10
    char pad14[0x0c];
    void* p20;             // +0x20
    char pad24[0x38];
    void* p5c;             // +0x5c
    void* p60;             // +0x60
    int   f64;             // +0x64
    int   f68;             // +0x68
};

struct RotationRing {
    void SetTLerp(float value);  // 0x00c65b50 ret 4
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
    bool  f_eff1e0(int);           // 0x00eff1e0 ret 4
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
    void* volatile self = this;
    __declspec(align(16)) volatile float stagedLerp;
    if (((MgrState*)g_mgr)->p20 == 0) return;

    Object1b0* o = (Object1b0*)pGame->p1b0;
    void* obj = 0;
    void* firstArg = 0;
    void* secondArg = 0;

    if (o != 0) {
        void* h = ((MgrState*)g_mgr)->handle;
        if (h != 0 && (((MgrState*)g_mgr)->pC == 0 || ((MgrState*)g_mgr)->p10 != 0)) {
            obj = FUN_00b18e00(h);

            OrientationState* s = o->p4;
            if (s->f64 > s->f60) {
                void* ring = ((MgrState*)g_mgr)->p5c;
                stagedLerp = ((float(__thiscall*)(void*))Vt(obj)[0x34 / 4])(obj);
                stagedLerp -= 3.0f;
                ((RotationRing*)ring)->SetTLerp(stagedLerp);
                firstArg = obj;
            }

            s = o->p4;
            if (s->f5c > s->f58) {
                ((RotationRing*)((MgrState*)g_mgr)->p60)->SetTLerp(o->value0c);
                secondArg = obj;
            }
        }
    }

    {
        void* p = ((MgrState*)g_mgr)->p20;
        ((void(__thiscall*)(void*, void*))Vt(p)[0x54 / 4])(p, obj);
    }
    {
        void* p = ((MgrState*)g_mgr)->p5c;
        ((void(__thiscall*)(void*, void*))Vt(p)[0x54 / 4])(p, firstArg);
    }
    {
        void* p = ((MgrState*)g_mgr)->p60;
        ((void(__thiscall*)(void*, void*))Vt(p)[0x54 / 4])(p, secondArg);
    }
    self = this;
}

// @ 0x00eff1e0
bool UI::f_eff1e0(int)
{
    void* a = *(void**)((char*)g_mgr + 4);
    if (a == 0) return false;
    void* r = pGame->F32790(a);
    if (r == 0) return false;
    OrientationState* o = ((PlacementView*)r)->p4;
    return o->f64 > o->f60;
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
    // Snapshot the current "active placement" pointer before the game-state calls.
    void* saved = *(void**)((char*)g_mgr + 0x10);

    pGame->F33BF0();
    pGame->F36450((int)p, 0, 0);

    // Assign p into g_mgr+0x0c with refcount bookkeeping.
    void** slot = &((MgrState*)g_mgr)->pC;
    void* old = *slot;
    if (p != old) {
        if (p) VCall0(p, 0x00);
        *slot = p;
        if (old) VCall0(old, 0x04);
    }

    // Whichever of the three tracked handles was active gets its lerp refreshed and is committed.
    Object1b0* o = (Object1b0*)pGame->p1b0;
    void* cur = *(void**)((char*)g_mgr + 0x20);
    if (saved == cur) {
        VCall0(cur, 0x58);
    } else {
        void* r5c = *(void**)((char*)g_mgr + 0x5c);
        if (saved == r5c) {
            ((RotationRing*)r5c)->SetTLerp(o->p4->f70);
            VCall0(r5c, 0x58);
        } else {
            void* r60 = *(void**)((char*)g_mgr + 0x60);
            if (saved == r60) {
                ((RotationRing*)r60)->SetTLerp(o->p4->f6c);
                VCall0(r60, 0x58);
            }
        }
    }

    ((MgrState*)g_mgr)->f68 = 1;
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
    void* entry = FUN_00b18e00(*(void**)((char*)g_mgr + 0xc));
    GObj* g = pGame;

    if (*(uint8_t*)((char*)entry + 0x6e) == 0) {
        g->F38330(1);
        g->F34560();

        // If the current placement object is the scenario-tutorial sentinel, tell the tutorial
        // controller that the placement finished.
        void* v = p10;
        if (v != 0 && *(int*)((char*)v + 0x54) == 0x5184ae0d) {
            void* ctx = *(void**)((char*)0x016c7aa4);
            ctx = *(void**)((char*)ctx + 0xd4);
            ((void (__thiscall*)(void*, int, int))0x00efbbe0)(ctx, 0xaa, 0xab);
        }
    } else {
        // 0x00f352e0 is a thiscall on the game object (it reads this->p1b0); the singleton drop
        // that follows is a plain cdecl with no arguments.
        ((void (__thiscall*)(void*))0x00f352e0)(g);
        ((void (__cdecl*)())0x00f32410)();
    }

    // Release the tracked handle.
    void* old = *(void**)((char*)g_mgr + 0xc);
    if (old) {
        *(void**)((char*)g_mgr + 0xc) = 0;
        VCall0(old, 0x04);
    }

    // Toggle the audio mute flag and drive the placement sound.
    g_016c7d24 = (g_016c7d24 == 0.0f) ? 1.0f : 0.0f;
    float level = g_016c7d24;

    void* at = EA_Audio_GetSystemAT();
    if (at) {
        VCall1(at, 0x38, 0x3cdd1a9);
        VCall2I(at, 0x40, 0x34753a7, 0xa984aa45);
        VCall2F(at, 0x3c, 0x34753aa, level);
        VCall0(at, 0x58);
    }
}

// @ 0x00eff4c0
void UI::f_eff4c0(void* p, float f)
{
    GObj* g = pGame;
    void* r = g->F32790(p);
    void* obj = FUN_00b18e00(p);

    OrientationState* s = ((Object1b0*)r)->p4;
    if (s->f64 > s->f60) {
        // t = clamp(f - 3, 0, 1); the object gets 3 + t, the ring and the sound get t.
        float t = f - 3.0f;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;

        ((void (__thiscall*)(void*, float))Vt(obj)[0x40 / 4])(obj, 3.0f + t);
        ((RotationRing*)*(void**)((char*)g_mgr + 0x5c))->SetTLerp(t);
        ((void (__cdecl*)(int, float))0x005ca880)(0xfa65b8cd, t);
    }
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
    if (g_016065f8 == 0)
        return;

    void* m = *(void**)&g_015ad298;
    if (VCallB(m, 0x38))
        return;

    // Lookup chain: the intermediate results are used unguarded, exactly as in the retail code.
    void* a = FUN_0067dd10();
    void* a2 = ((void* (__thiscall*)(void*))Vt(a)[0x50 / 4])(a);
    void* w = ((void* (__thiscall*)(void*))Vt(a2)[0x38 / 4])(a2);
    if (w == 0)
        return;
    if (((void* (__thiscall*)(void*, int))Vt(w)[0x0c / 4])(w, 0x11966ed) == 0)
        return;

    void* r = pGame->F329E0((void*)arg);
    if (r == 0)
        return;

    ((void (__thiscall*)(void*, void*))Vt(this)[0x20 / 4])(this, *(void**)r);

    void* b = FUN_0067dd10();
    void* b2 = ((void* (__thiscall*)(void*))Vt(b)[0x50 / 4])(b);
    void* w2 = ((void* (__thiscall*)(void*))Vt(b2)[0x38 / 4])(b2);
    if (w2 == 0)
        return;
    if (((void* (__thiscall*)(void*, int))Vt(w2)[0x0c / 4])(w2, 0x11966ed) == 0)
        return;

    FUN_00b18e00(*(void**)r);
    FUN_00efccd0();
}

// @ 0x00eff6c0
void __cdecl f_eff6c0(void* obj, char flag)
{
    if (obj == 0)
        return;

    void* r = FUN_00ae66d0(obj);

    // Refresh the obj-side visual state, then commit (flag set) or drop (flag clear) the tracked
    // object in the manager's +0x08 slot.
    ((void (__thiscall*)(void*, char))Vt(obj)[0x28 / 4])(obj, flag);

    if (flag != 0) {
        void** slot = &((MgrState*)g_mgr)->p8;
        void* old = *slot;
        if (r != old) {
            if (r) VCall0(r, 0x00);
            *slot = r;
            if (old) VCall0(old, 0x04);
        }
    } else {
        void* cur = *(void**)((char*)g_mgr + 8);
        if (r == cur && cur != 0) {
            *(void**)((char*)g_mgr + 8) = 0;
            VCall0(cur, 0x04);
        }
    }

    // Toggle bit 3 of the render object's flag word.
    void* x = ((void* (__thiscall*)(void*))Vt(obj)[0xac / 4])(obj);
    if (x != 0) {
        if (flag != 0)
            *(int*)((char*)x + 4) |= 8;
        else
            *(int*)((char*)x + 4) &= ~8;
    }
}

// @ 0x00eff760
void __cdecl f_eff760(void* obj, char flag)
{
    if (obj == 0)
        return;
    void* m = *(void**)&g_015ad298;
    if (VCallB(m, 0x38))
        return;
    f_eff6c0(obj, flag);
}
