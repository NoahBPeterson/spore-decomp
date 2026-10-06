// Slice s00f00610 -- UI::cScenarioTutorialsChecklistUI / tutorial object helpers.
// Region flags: /O2 /MD /Gy /TP
#include "types.h"

extern void*   g_mgr;             // 0x016c7b88 (singleton pointer variable)
extern uint8_t g_016c7b34[];      // 0x016c7b34
extern uint8_t g_015ad328[];      // 0x015ad328

extern "C" void* __cdecl FUN_00b18e00(void*);          // 0x00b18e00
extern "C" void* __cdecl FUN_00eebf80(void*);          // 0x00eebf80
extern "C" void  __cdecl f_eff4c0_impl(void*, float);  // 0x00eff4c0 (thiscall in real code)

struct GObj {
    char pad0[0x400];
    void* F32790(void*);       // 0x00f32790 ret 4
    void  F33BF0();            // 0x00f33bf0
    void  F38150(void*);       // 0x00f38150 ret 4
    void  F34560();            // 0x00f34560
    void  F36450(int, int, void*); // 0x00f36450 ret 0xc
};
struct VObj {
    void  v0();                // vtable slot 0 (addref)
    void  v4();                // vtable slot 1 (release)
    float v34();               // vtable slot 0x34, returns float
    void  v38(void*);
    void  v3c(void*);
    void  v40(float);
};

struct Ref {
    virtual void v0();     // slot 0 addref
    virtual void v4();     // slot 1 release
};

// 4-dword / refcounted value used by the tutorial placement list.
struct V4 {
    void* p0;    // refcounted object
    int   f4;
    int   f8;
    float fC;
    V4* assign(V4* src);   // 0x00f00b00
};

struct UI {
    void* vtable;      // +0x00
    uint8_t f4;        // +0x04
    uint8_t b5;        // +0x05
    char pad6[2];
    GObj* pGame;       // +0x08
    void* pC;          // +0x0c
    void* p10;         // +0x10
    void  f00610(int, int);        // 0x00f00610 ret 8
    void  f00790(void*);           // 0x00f00790 ret 4
    void  f00850(void*);           // 0x00f00850 ret 4
    void  f00b50();                // 0x00f00b50
    void  f00ba0();                // 0x00f00ba0
    void  f00bd0(void*);           // 0x00f00bd0 ret 4
    void  f00d10();                // 0x00f00d10
    void  f00e50(void*);           // 0x00f00e50 ret 4
    void  f00f80();                // 0x00f00f80
    void  f01030(void*, float);    // 0x00f01030 ret 8
    void  f01090(void*);           // 0x00f01090 ret 4
};

// @ 0x00f00b00 -- V4 assignment with refcount (returns this)
V4* V4::assign(V4* src)
{
    void* old = p0;
    void* nw = src->p0;
    if (nw != old) {
        if (nw) ((Ref*)nw)->v0();
        p0 = nw;
        if (old) ((Ref*)old)->v4();
    }
    f4 = src->f4;
    f8 = src->f8;
    fC = src->fC;
    return this;
}

// @ 0x00f00ba0
void UI::f00ba0()
{
    void* r = pGame->F32790(*(void**)((char*)g_mgr + 4));
    if (r) ((V4*)pC)->assign((V4*)r);
}

// @ 0x00f00b50
void UI::f00b50()
{
    void* u = *(void**)((char*)g_mgr + 4);
    void* r = pGame->F32790(u);
    if (r) {
        pGame->F33BF0();
        ((V4*)pC)->assign((V4*)r);
        ((void(__thiscall*)(void*, int)) * ((void**)vtable + 0x20 / 4))(this, 0);
        pGame->F38150(u);
        pGame->F34560();
    }
}

// @ 0x00f01030
void UI::f01030(void* p, float f)
{
    if (p == 0) return;
    if (b5 == 0) {
        b5 = 1;
        pGame->F33BF0();
        pGame->F36450(0, 0, p);
    }
    VObj* r = (VObj*)FUN_00b18e00(p);
    float cur = r->v34();
    ((void(__thiscall*)(void*, void*, float))f_eff4c0_impl)(this, p, f * 0.01f + cur);
}

// @ 0x00f01140 -- copy [begin,end) of 0x20-byte records into dst, *out = dst.
struct Rec { int f0; float f1, f2, f3, f4, f5, f6, f7; };
void __cdecl f01140(void** out, const Rec* begin, const Rec* end, Rec* dst)
{
    *out = dst;
    if (begin == end) return;
    do {
        if (dst) {
            dst->f0 = begin->f0;
            dst->f1 = begin->f1;
            dst->f2 = begin->f2;
            dst->f3 = begin->f3;
            dst->f4 = begin->f4;
            dst->f5 = begin->f5;
            dst->f6 = begin->f6;
            dst->f7 = begin->f7;
        }
        begin = (const Rec*)((const char*)begin + 0x20);
        dst = (Rec*)((char*)dst + 0x20);
    } while (begin != end);
    *out = dst;
}

// ---------------------------------------------------------------------------
// @ 0x00f00610 -- large: two-object placement sync (stub; partial)
void UI::f00610(int a, int b) { (void)a; (void)b; }
// @ 0x00f00790 -- large: placement apply (stub; partial)
void UI::f00790(void* a) { (void)a; }
// @ 0x00f00850 -- large: secondary placement apply (stub; partial)
void UI::f00850(void* a) { (void)a; }
// @ 0x00f00bd0 -- large: placement commit (stub; partial)
void UI::f00bd0(void* a) { (void)a; }
// @ 0x00f00d10 -- large: teardown (stub; partial)
void UI::f00d10() {}
// @ 0x00f00e50 -- large: placement update (stub; partial)
void UI::f00e50(void* a) { (void)a; }
// @ 0x00f00f80 -- large: vtable dispatch (stub; partial)
void UI::f00f80() {}
// @ 0x00f01090 -- large: object add (stub; partial)
void UI::f01090(void* a) { (void)a; }
// @ 0x00f011b0 -- large: scene build (stub; partial)
void __cdecl f011b0() {}
