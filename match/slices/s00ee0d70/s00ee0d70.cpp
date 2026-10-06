// slice s00ee0d70 -- more UI::cScenarioTutorialsChecklistUI-adjacent helpers:
// a 0x4c4 property dispatcher, the checklist teardown, and window-callback handlers.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE2.
//
// Direct __thiscall callees are declared as `__fastcall(void* self, int dummy, args...)`:
// the callee reads `this` from ecx and ignores edx, which reproduces its call exactly at
// the source level (real C++, no assembly).
#include "types.h"

struct Elem {
    int  v0;
    char pad0[0x4a4 - 0x4];
    int  v4a4, v4a8, v4ac, v4b0, v4b4, v4b8, v4bc, v4c0, v4c4;
    char pad1[0x4e0 - 0x4c8];
};

struct Container {
    char  pad0[0x20];
    char  f20;
    char  pad1[0x70 - 0x21];
    char* begin;
    char* end;
};

struct Manager { void Lock(); void Unlock(); void FUN_00f40d00(int key, void* out); };
struct GlobalObj {
    char pad0[0x14]; void* f14; char pad1[0x74 - 0x18]; Manager* f74;
    char pad2[0xd4 - 0x78]; void* fD4;
};
extern GlobalObj* g_16c7aa4;

// ---------------------------------------------------------------------------
// vtable invoke helpers: __fastcall supplies ecx=this, edx=0; the callee is a
// __thiscall member and ignores edx.
// ---------------------------------------------------------------------------
typedef void  (__fastcall *VF0)(void*, int);
typedef void  (__fastcall *VF1)(void*, int, int);
typedef void  (__fastcall *VFp)(void*, int, void*);
typedef void* (__fastcall *VFQ)(void*, int, int);
typedef void* (__fastcall *VFQ2)(void*, int, int, int);
typedef float (__fastcall *VFF)(void*, int);

static __forceinline void  vc0(void* o, int slot)
{ ((VF0)(((void**)(*(void***)o))[slot]))(o, 0); }
static __forceinline void  vc1(void* o, int slot, int a)
{ ((VF1)(((void**)(*(void***)o))[slot]))(o, 0, a); }
static __forceinline void  vcp(void* o, int slot, void* a)
{ ((VFp)(((void**)(*(void***)o))[slot]))(o, 0, a); }
static __forceinline void* vcq(void* o, int slot, int a)
{ return ((VFQ)(((void**)(*(void***)o))[slot]))(o, 0, a); }
static __forceinline void* vcq2(void* o, int slot, int a, int b)
{ return ((VFQ2)(((void**)(*(void***)o))[slot]))(o, 0, a, b); }
static __forceinline float vcf(void* o, int slot)
{ return ((VFF)(((void**)(*(void***)o))[slot]))(o, 0); }

// ---------------------------------------------------------------------------
// external helpers (__fastcall wrapper convention as documented above)
// ---------------------------------------------------------------------------
void  __cdecl   operator_delete(void* p);
void  __stdcall FUN_00edfbf0(void* p);
bool  __cdecl   FUN_00eddf30(void* a, void* b, void* c, void* d);
void  __cdecl   FUN_00f40d00(int key, void* out);

void  __fastcall  FUN_00edf410(void*, int);
void  __fastcall  FUN_00edf2c0(void*, int, int);
void* __fastcall  FUN_00e09c80(void*, int);           // count
void* __fastcall  FUN_00e09c90(void*, int, int idx);  // layout by index
void  __fastcall  FUN_00e0a5c0(void*, int);
void  __fastcall  FUN_00edd810(void*, int);
void  __fastcall  FUN_00edbcb0(void*, int);
void* __fastcall  FUN_00mgr_RemoveWindowCallback2(void*, int);

void  __cdecl   SPUIHelpers_RemoveWindowCallback(void* w, void* cb);
void  __cdecl   SPUIHelpers_EndModal(void* w, int a, int b);
void* __cdecl   Layout_FindWindowByID(void* layout, int id, int flag);
void  __cdecl   cSPUIPopupMenuWin_OnMenuItemSelected(void* p, int a, void* b);
void  __cdecl   EA_Messaging_RemoveHandler(int a, int b, int c, int d, int e);
void  __cdecl   cSPUILayout_SetParentWin(void* layout, int a, int b, int hash);
void  __cdecl   cSPUILayout_Shutdown(void* layout, int a);
void  __fastcall FUN_00bfc470(void*, int, int);

void  __cdecl   FUN_00f3e8a0_b();
void  __cdecl   FUN_00f45970_b();
void  __cdecl   FUN_00f45a80_b();
void  __cdecl   FUN_00f427c0_b();

struct IntVec { int* begin; int* end; int* cap; };

// Stub interface used by the window-callback walks: slot 1 releases, slot 3 is a
// query/handoff, slot 29 is a scalar getter.
struct IObj {
    virtual void  u0();
    virtual void  Release();            // 1
    virtual void  u2();
    virtual void* Query(int key);       // 3
    virtual void  u4();  virtual void u5();  virtual void u6();  virtual void u7();
    virtual void  u8();  virtual void u9();  virtual void u10(); virtual void u11();
    virtual void  u12(); virtual void u13(); virtual void u14(); virtual void u15();
    virtual void  u16(); virtual void u17(); virtual void u18(); virtual void u19();
    virtual void  u20(); virtual void u21(); virtual void u22(); virtual void u23();
    virtual void  u24(); virtual void u25(); virtual void u26(); virtual void u27();
    virtual void  u28();
    virtual float GetFloat();           // 29
    // non-virtual fixed methods
    bool FUN_00c88940(int key);
    void FUN_00c8b1a0(int key);
    void FUN_00c88a00(int key);
    void FUN_00c8a020(int key, float v);
    void FUN_00c8ad30(int key, int v);
    void FUN_00bfc470(int a);
};

// ===========================================================================
// @ 0x00ee0d70   property +0x4c4
// ===========================================================================
bool __cdecl f_ee0d70(Container* c, Elem* e, int value)
{
    bool changed = false;
    if (c->f20 != 0) {
        int cur = e->v4c4;
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
            if (*(int*)(c->begin + i * 0x4e0 + 0x4c4) != cur) {
                changed = true;
                goto save;
            }
        }
        changed = (cur != value);
        if (!changed)
            return changed;
    save:
        g_16c7aa4->f74->Lock();
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
            *(int*)(c->begin + i * 0x4e0 + 0x4c4) = value;
        g_16c7aa4->f74->Unlock();
        return changed;
    }
    if (e->v4c4 == value)
        return false;
    g_16c7aa4->f74->Lock();
    e->v4c4 = value;
    g_16c7aa4->f74->Unlock();
    return true;
}

// defined in the neighbouring slice's TU (same layouts)
bool __cdecl f_ee0af0(Container* c, Elem* e, int value);
bool __cdecl f_ee0c30(Container* c, Elem* e, int value);

// ===========================================================================
// @ 0x00ee0eb0   dispatcher
// ===========================================================================
bool __cdecl f_ee0eb0(Container* c, Elem* e, void* p3, int arg4, unsigned id)
{
    bool r = false;
    if (FUN_00eddf30(e, p3, (void*)arg4, (void*)id)) {
        switch (id) {
        case 0x742bdb0: r = f_ee0d70(c, e, arg4); break;
        case 0x742bdc0: r = f_ee0c30(c, e, arg4); break;
        case 0x742bdd0: r = f_ee0af0(c, e, arg4); break;
        }
    }
    return r;
}

// ===========================================================================
// @ 0x00ee0f50   teardown
// ===========================================================================
struct CCLarge {
    char  pad0[0x10];
    void* f10;               // +0x10 layout
    void* f14;               // +0x14 window
    void* f18;               // +0x18
    void* f1c;               // +0x1c refcounted array
    char  pad1[0x70 - 0x20];
    int   f70, f74, f78, f7c, f80;
};

void __fastcall f_ee0f50(CCLarge* c)
{
    FUN_00edf410(c, 0);
    if (c->f14 != 0) {
        void* w = c->f18;
        FUN_00edf2c0(w, 0, 1);
        SPUIHelpers_RemoveWindowCallback(w, (void*)FUN_00edf410);
        vc0(*(void**)((char*)c->f14 + 0x24), 2);
        vc0(*(void**)c->f14, 2);
        c->f14 = 0;
    }
    if (c->f1c != 0) {
        unsigned u = 0;
        do {
            void* p = *(void**)((char*)c->f1c + u);
            if (p != 0) {
                vc0(p, 5);
                p = *(void**)((char*)c->f1c + u);
                if (p != 0) {
                    *(void**)((char*)c->f1c + u) = 0;
                    vc0(p, 3);
                }
            }
            u += 4;
        } while (u < 0x18);
        int* base = (int*)c->f1c;
        if (base != 0) {
            int n = base[-1];
            int* end = (int*)((char*)base + n * 4);
            while (--n >= 0) {
                int* slot = end - 1;
                --end;
                if (*slot != 0)
                    vc0((void*)*slot, 3);
            }
            operator_delete(base - 1);
        }
    }
    if (c->f10 != 0) {
        cSPUILayout_SetParentWin(c->f10, 0, 1, 0x5b598fa);
        cSPUILayout_Shutdown(c->f10, 1);
        void* p = c->f10;
        if (p != 0) {
            c->f10 = 0;
            vc0(p, 2);
        }
    }
    if (c->f70 != 0) {
        int a = c->f70;
        c->f70 = 0;
        EA_Messaging_RemoveHandler(a, c->f74, c->f78, c->f7c, c->f80);
    }
}

// ===========================================================================
// @ 0x00ee1060   thunk
// ===========================================================================
void __stdcall f_ee1060(int* p)
{
    if (*p != 0)
        FUN_00edfbf0(p);
}

// ===========================================================================
// @ 0x00ee1080   popup-menu handler (menu-title selection)
// ===========================================================================
void __cdecl f_ee1080(void* param_1, void* param_2)
{
    if (param_2 == 0)
        return;
    void* menu = vcq(param_2, 3, 0x4c058d5);
    if (menu == 0)
        return;
    // The original walks an intrusive iterator anchored at (menu+4) via vtable slots
    // 0xcc/0xd0, finds the first node whose query(0x4c058cf) has +0x888 == param_1,
    // and invokes OnMenuItemSelected(menu, 0, node).
    int local0 = 0;
    vcp((char*)menu + 4, 51, &local0);
    int* it = (int*)vcq((char*)menu + 4, 52, 0);
    if (it != &local0) {
        for (;;) {
            void* node = it ? (void*)it : 0;
            void* r = node ? vcq(node, 3, 0x4c058cf) : 0;
            if (r != 0 && param_1 == *(void**)((char*)r + 0x888)) {
                cSPUIPopupMenuWin_OnMenuItemSelected(menu, 0, r);
                return;
            }
            int* nxt = (int*)vcq((char*)menu + 4, 52, 0);
            it = nxt;
            if (it == &local0)
                return;
        }
    }
}

// ===========================================================================
// @ 0x00ee1140   walk vector: set byte +0x78 from param_2, release items
// ===========================================================================
void __cdecl f_ee1140(int key, char value)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    g_16c7aa4->f74->FUN_00f40d00(key, &v);
    for (IObj** it = (IObj**)v.begin; it != (IObj**)v.end; ++it) {
        IObj* o = *it;
        if (o != 0) {
            void* r = o->Query(0x1186577);
            if (r != 0)
                *(char*)((char*)r + 0x78) = (value == 0);
        }
    }
    for (IObj** q = (IObj**)v.begin; q < (IObj**)v.end; ++q) {
        if (*q != 0)
            (*q)->Release();
    }
    if (v.begin != 0 && v.begin[-1] != 0)
        operator_delete(v.begin);
}

// ===========================================================================
// @ 0x00ee1200
// ===========================================================================
void __cdecl f_ee1200(int key, int arg2)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    g_16c7aa4->f74->FUN_00f40d00(key, &v);
    for (IObj** it = (IObj**)v.begin; it != (IObj**)v.end; ++it) {
        if (*it != 0) {
            IObj* r = (IObj*)(*it)->Query(0x13f94d4);
            if (r != 0)
                r->FUN_00bfc470(arg2);
        }
    }
    for (IObj** q = (IObj**)v.begin; q < (IObj**)v.end; ++q) {
        if (*q != 0)
            (*q)->Release();
    }
    if (v.begin != 0 && v.begin[-1] != 0)
        operator_delete(v.begin);
}

// ===========================================================================
// @ 0x00ee12c0   big teardown
// ===========================================================================
struct CCLarge2 {
    char pad0[0x8];
    char f8;                 // +0x8
    char pad1[0x10 - 0x9];
    void* f10;               // +0x10
    void* f14;               // +0x14
    void* f18;               // +0x18
    void* f1c; void* f20; void* f24; void* f28;
    char pad2[0x40 - 0x2c];
    void* f40;               // +0x40
    void* f44;               // +0x44
    void* f48;               // +0x48
    char pad3[0xbc - 0x4c];
    void* fbc;               // +0xbc
    void* fc0;               // +0xc0
    char fc5, fc6;           // +0xc5, +0xc6
};

void __fastcall f_ee12c0(CCLarge2* c)
{
    char* s = (char*)c;
    void* mgr = s + 0x4c;
    unsigned n = 0;
    if (FUN_00e09c80(mgr, 0) != 0) {
        do {
            void* layout = FUN_00e09c90(mgr, 0, (int)n);
            void* w = Layout_FindWindowByID(layout, 0x715cde0, 1);
            if (w != 0) {
                void* sub = vcq2(w, 60, 0x7df4c98, 1);
                if (sub != 0)
                    vcp(sub, 66, c->fc0);
            }
            ++n;
        } while (n < (unsigned)FUN_00e09c80(mgr, 0));
    }
    void* idbase = (c != 0) ? (void*)(s + 8) : 0;
    void* w = Layout_FindWindowByID(c->f40, 0x71725b0, 1);
    if (w != 0) vcp(w, 66, idbase);
    idbase = s + 8;
    w = Layout_FindWindowByID(c->f44, 0x7172600, 1);
    if (w != 0) vcp(w, 66, idbase);
    if (c->f20 != 0) vcp(c->f20, 66, idbase);
    if (c->f24 != 0) vcp(c->f24, 66, idbase);
    FUN_00e0a5c0(mgr, 0);
    if (c->f28 != 0) vcp(c->f28, 66, idbase);
    w = Layout_FindWindowByID(c->f40, 0x71725b0, 1);
    if (w != 0) SPUIHelpers_EndModal(w, 0, 1);
    w = Layout_FindWindowByID(c->f44, 0x7172600, 1);
    if (w != 0) SPUIHelpers_EndModal(w, 0, 1);
    c->fc5 = 0;
    c->fc6 = 0;
    FUN_00edd810(c, 0);
    if (c->f40 != 0) {
        cSPUILayout_Shutdown(c->f40, 1);
        void* p = c->f40;
        if (p != 0) { c->f40 = 0; vc0(p, 2); }
    }
    if (c->f44 != 0) {
        cSPUILayout_Shutdown(c->f44, 1);
        void* p = c->f44;
        if (p != 0) { c->f44 = 0; vc0(p, 2); }
    }
    if (c->f18 != 0) {
        f_ee0f50((CCLarge*)c->f18);
        if (c->f18 != 0) {
            void* p = c->f18;
            c->f18 = 0;
            vc0(p, 2);
        }
    }
    if (c->f48 != 0) {
        FUN_00edbcb0(c->f48, 0);
        void* p = c->f48;
        if (p != 0) { c->f48 = 0; vc0(p, 2); }
    }
    if (c->fbc != 0) {
        vc0(c->fbc, 9);
        void* p = c->fbc;
        if (p != 0) { c->fbc = 0; vc0(p, 1); }
    }
    if (c->fc0 != 0) { void* p = c->fc0; c->fc0 = 0; vc0(p, 1); }
    if (c->f1c != 0) { void* p = c->f1c; c->f1c = 0; vc0(p, 1); }
    if (c->f20 != 0) { void* p = c->f20; c->f20 = 0; vc0(p, 1); }
    if (c->f24 != 0) { void* p = c->f24; c->f24 = 0; vc0(p, 1); }
    if (c->f28 != 0) { void* p = c->f28; c->f28 = 0; vc0(p, 1); }
}

// ===========================================================================
// @ 0x00ee1510   walk vector, apply a float offset
// ===========================================================================
void __cdecl f_ee1510(int key, float param_2)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    g_16c7aa4->f74->FUN_00f40d00(key, &v);
    static const float kMin = 1.5258789e-05f;
    if (kMin > param_2)
        param_2 = kMin;
    for (IObj** it = (IObj**)v.begin; it != (IObj**)v.end; ++it) {
        IObj* obj = (*it == 0) ? 0 : (IObj*)(*it)->Query(0x1186577);
        if (!obj->FUN_00c88940(0xb78987ff)) {
            obj->FUN_00c8b1a0(0xb78987ff);
            obj->FUN_00c88a00(0xb78987ff);
        }
        float f = obj->GetFloat();
        obj->FUN_00c8a020(0xb78987ff, f + param_2);
    }
    for (IObj** q = (IObj**)v.begin; q < (IObj**)v.end; ++q) {
        if (*q != 0)
            (*q)->Release();
    }
    if (v.begin != 0 && v.begin[-1] != 0)
        operator_delete(v.begin);
}

// ===========================================================================
// @ 0x00ee1630   walk vector, reset
// ===========================================================================
void __cdecl f_ee1630(int key)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    g_16c7aa4->f74->FUN_00f40d00(key, &v);
    IObj** end = (IObj**)v.end;
    for (IObj** it = (IObj**)v.begin; it != end; ++it) {
        IObj* obj = *it;
        IObj* r = (obj != 0) ? (IObj*)obj->Query(0x1186577) : 0;
        r->FUN_00c8ad30(0xb78987ff, 0);
    }
    for (IObj** q = (IObj**)v.begin; q < (IObj**)v.end; ++q) {
        if (*q != 0)
            (*q)->Release();
    }
    if (v.begin != 0 && v.begin[-1] != 0)
        operator_delete(v.begin);
}
