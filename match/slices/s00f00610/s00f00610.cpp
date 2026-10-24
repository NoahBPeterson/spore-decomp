// Slice s00f00610 -- UI::cScenarioTutorialsChecklistUI / tutorial object helpers.
// Region flags: /O2 /MD /Gy /TP
#include "types.h"

#include <math.h>

// ---- singleton pointers / globals (the named addresses hold pointers unless noted) ----
extern void*   g_mgr;             // 0x016c7b88 (singleton pointer variable)
extern void*   gSimulator;        // 0x016c7aa4 (simulator pointer variable)
extern uint8_t g_016c7b34[];      // 0x016c7b34
extern uint8_t g_015ad328[];      // 0x015ad328
extern uint8_t g_015acb40;        // 0x015acb40  tutorial scenario enabled flag
extern float   g_015ad360;        // 0x015ad360  approach-rate constant
extern float   g_16c7d74;         // 0x016c7d74  audio cue toggle float
extern float   g_0148cfe8;        // 0x0148cfe8  +3.0f constant
extern uint8_t g_016c7b98[];      // 0x016c7b98  sphere description for ray_sphere

extern "C" void* __cdecl FUN_00b18e00(void*);          // 0x00b18e00
extern "C" void* __cdecl FUN_00eebf80(void*);          // 0x00eebf80 GetRefCounted18
extern "C" void  __cdecl f_eff4c0_impl(void*, float);  // 0x00eff4c0 (thiscall in real code)
extern "C" void  __cdecl FUN_00eec3d0(void*, void*);   // 0x00eec3d0
extern "C" void* __cdecl FUN_00eec0d0(void*);          // 0x00eec0d0
extern "C" float __cdecl FUN_00f409a0(void*, void*, float, int, void*); // 0x00f409a0 ScenarioNode_ClampValue
extern "C" int   __cdecl FUN_00eece20(void*);          // 0x00eece20 ResourceKeyToIcon
extern "C" void* __cdecl FUN_0067dcc0();               // 0x0067dcc0 MessageServer
extern "C" void  __cdecl FUN_00efd970(void*);          // 0x00efd970
extern "C" void* __cdecl FUN_00b3d250();               // 0x00b3d250 SP::GameInputManager
extern "C" void  __cdecl FUN_00efe260();               // 0x00efe260 ScenarioTutorials_SetSelectedObject
extern "C" void  __cdecl FUN_00eef7d0(void*);          // 0x00eef7d0
extern "C" void* __cdecl FUN_00b3d240();               // 0x00b3d240
extern "C" void* __cdecl FUN_00ae66d0(void*);          // 0x00ae66d0
extern "C" void  __cdecl FUN_00eef4b0(void*);          // 0x00eef4b0
struct Container {                                     // object at g_mgr+0x30
    void F_00c688a0(void*, char*);   // 0x00c688a0 (element, &flag)
    void F_00c68d20(void*);          // 0x00c68d20
};

// fixed-address objects reached directly (ecx = the immediate address).
struct B34Obj { void F_eeff40(); };                    // 0x00eeff40
extern B34Obj   g_016c7b34obj;    // 0x016c7b34
struct STut { char CheckObject(void*); };              // 0x00efeae0 on 0x015ad328
extern STut     g_015ad328obj;    // 0x015ad328
struct Obj74 { void F3BBD0(int, int); void F3DA90(void*, int); }; // 0x00f3bbd0 / 0x00f3da90 on gSimulator+0x74
struct AutoRef { void F_00b5f950(void*); };             // 0x00b5f950 refcounted slot assign

// *gSimulator @ 0x016c7aa4
struct Simulator {
    char  pad0[0x74];
    Obj74* p74;                    // +0x74  window/hint owner
    char  pad78[0x5c];             // +0x78 .. +0xd3
    void* pD4;                     // +0xd4  checklist UI
};

// *g_mgr @ 0x016c7b88
struct Mgr {
    int      mIndex;               // +0x00  index of the current placement record
    void*    mp4;                  // +0x04  refcounted current object
    void*    mp8;                  // +0x08  refcounted secondary slot
    void*    mpSelected;           // +0x0c  refcounted selected object
    void*    mp10;                 // +0x10  refcounted active object
    char     pad14[0xc];           // +0x14
    void*    mp20;                 // +0x20  raw compare object
    char     pad24[4];             // +0x24
    void*    mp28;                 // +0x28  compare object
    char     pad2c[4];             // +0x2c
    char     mVec30[0x2c];         // +0x30  association container
    void*    mp5c;                 // +0x5c
    void*    mp60;                 // +0x60
    uint8_t  b64;                  // +0x64
    char     pad65[3];             // +0x65
    int      f68;                  // +0x68
    char     pad6c[0xc];           // +0x6c
    float    f78;                  // +0x78
    char     pad7c[0x10];          // +0x7c
    void*    begin8c;              // +0x8c  list begin (used as a pair +0x8c/+0x90)
    void*    end90;                // +0x90  list end
};

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// Object returned by GetRefCounted18 (FUN_00eebf80): scenario node with placement.
struct Node {
    void*    vtable;               // +0x00
    Vec3     pos;                  // +0x04
    Quat     rot;                  // +0x10
    float    f20;                  // +0x20
    uint32_t f24;                  // +0x24
    char*    p28;                  // +0x28  record array begin
    char*    p2c;                  // +0x2c  record array end
    char     pad30[0x1f0];         // +0x30 .. +0x21f
    float    f220;                 // +0x220
};
struct SNode {                     // object returned by GObj::F3E8A0
    char     pad0[0x20];
    uint8_t  b20;                  // +0x20
};
struct NodeB {                     // object returned by FUN_00b18e00(0)
    char     pad0[0x6e];
    uint8_t  b6e;                  // +0x6e
};
struct PObj {                      // object returned by GObj::F32790
    char     pad0[4];
    uint32_t f4;                   // +0x04
};
struct Key { uint32_t a; uint32_t b; };

struct GObj {
    char pad0[0x1b0];
    void* f1b0;                // +0x1b0  associated object pointer
    char pad1b4[0x24c];
    void* F32790(void*);       // 0x00f32790 ret 4
    void  F33BF0();            // 0x00f33bf0
    void  F38150(void*);       // 0x00f38150 ret 4
    void  F34560();            // 0x00f34560
    void  F36450(int, int, void*); // 0x00f36450 ret 0xc
    void* F336A0(void*);       // 0x00f336a0 ret 4
    void  F38330(int);         // 0x00f38330 ret 4
    void  F45970();            // 0x00f45970
    void  F45A80();            // 0x00f45a80
    void  F3DA90(void*, int);  // 0x00f3da90 ret 8
    char  F3EC90(void*);       // 0x00f3ec90 ret 4
    char  F326D0(void*);       // 0x00f326d0 ret 4
    void* F3E8A0(void*);       // 0x00f3e8a0 ret 4
    void* F445C0(void*);       // 0x00f445c0 ret 4
    void  F3BBD0(int, int);    // 0x00f3bbd0 ret 8
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

// object behind Mgr::mp10 (has the float accessor and virtual slot 0x5c).
struct Mp10Obj {
    float F_efc4c0();          // 0x00efc4c0
    char  CheckObj(void*);     // 0x00efeae0 (same target as STut::CheckObject)
};

struct UI {
    void* vtable;      // +0x00
    uint8_t f4;        // +0x04
    uint8_t b5;        // +0x05
    uint8_t b6;        // +0x06
    uint8_t b7;        // +0x07
    GObj* pGame;       // +0x08
    void* pC;          // +0x0c
    void* p10;         // +0x10
    char  F_efc660(void*);         // 0x00efc660 ret 4
    char  F_efc7d0(void*, void*);  // 0x00efc7d0 ret 8
    void  F_efec90(void*);         // 0x00efec90 ret 4
    void  F_efcde0();              // 0x00efcde0
    void  FwdC6E0(void*);          // 0x00efc6e0 ret 4
    void  SetObject(void*);        // 0x00eff230 ret 4
    void  UpdateVisibility();      // 0x00eff0c0
    void  Adjust(void*, float);    // 0x00eff4c0 ret 8
    void* Place(void*);            // 0x00efeee0 ret 4
    void* GetPlacement();          // 0x00eff590
    void  ToggleHint(int, int);    // 0x00efbbe0 ret 8
    char  CheckObject(void*);      // 0x00efeae0 ret 4
    void  f00b50();                // 0x00f00b50
    void  f00ba0();                // 0x00f00ba0
    void  f01030(void*, float);    // 0x00f01030 ret 8
    void  SyncPlacement(int, float);   // 0x00f00610 ret 8
    char  ApplyPlacement(void*);       // 0x00f00790 ret 4
    char  ApplyPlacementEx(void*);     // 0x00f00850 ret 4
    void  CommitPlacement(void*);      // 0x00f00bd0 ret 4
    void  Teardown();                  // 0x00f00d10
    char  UpdatePlacement(void*);      // 0x00f00e50 ret 4
    void  Dispatch();                  // 0x00f00f80
    char  AddObject(void*);            // 0x00f01090 ret 4
};

struct GD { void* F_B18530(); char dummy; };   // 0x00b18530 object accessor
struct CGameData { char F_F253E0(); };         // 0x00f253e0

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
void** __cdecl f01140(void** out, const Rec* begin, const Rec* end, Rec* dst)
{
    *out = dst;
    if (begin == end) return out;
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
    return out;
}

// ---------------------------------------------------------------------------
// virtual-call helpers (thiscall slots on the object's vtable).
typedef void  (__thiscall *ThV0)(void*);
typedef void  (__thiscall *ThV1)(void*, int);
typedef void  (__thiscall *ThV2)(void*, int, int);
typedef void  (__thiscall *ThV3)(void*, int, int, int);
typedef void  (__thiscall *ThV2F)(void*, int, float);
typedef void* (__thiscall *ThP0)(void*);
typedef void* (__thiscall *ThP1)(void*, void*);
typedef void  (__thiscall *ThV2P)(void*, void*, void*);
typedef int   (__thiscall *ThI0)(void*);
typedef int   (__thiscall *ThI1)(void*, int);
typedef int*  (__thiscall *ThIP0)(void*);

static inline void* vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
static inline void  do_release(void* o) { ((ThV0)vslot(o, 4))(o); }

// e^x = 2^(x*log2e).  The original inlines the x87 f2xm1/fscale sequence; the CRT `exp`
// is not present in the image, so reproduce the value with a self-contained approximation
// that cl expands inline (no CRT import).
static __forceinline float s_exp(float x)
{
    double y = (double)x * 1.4426950408889634;
    double dn = (double)(long long)(y >= 0.0 ? y + 0.5 : y - 0.5);
    double r = y - dn;
    double p = 1.0 + r * (0.6931471805599453094
               + r * (0.2402265069591007123
               + r * (0.05550410866482157995
               + r * (0.009618129107628477161
               + r * (0.001333355814642844342
               + r * 0.0001540353039338161012)))));
    union { unsigned long long u; double d; } sc;
    sc.u = ((unsigned long long)((long long)dn + 1023)) << 52;
    return (float)(p * sc.d);
}

extern "C" void* __cdecl FUN_00a206f0();              // 0x00a206f0 EA::Audio::GetSystemAT

// @ 0x00f00610 -- advance the placed object toward its target over `dt`
void UI::SyncPlacement(int handle, float dt)
{
    if (handle == 0) return;
    Mgr* m = (Mgr*)g_mgr;
    if (g_015acb40 != 0 && m->begin8c != m->end90) {
        ((Simulator*)gSimulator)->p74->F3BBD0((int)m->mp4, 0);
        return;
    }
    if (b5 == 0) {
        g_016c7b34obj.F_eeff40();
        b5 = 1;
        pGame->F45970();
    }
    Node* n = (Node*)FUN_00eebf80((void*)handle);
    Key key;
    FUN_00eec3d0(&key, n);
    float cur = n->f20;
    float scaled = s_exp(g_015ad360 * dt) * cur;
    int gt = scaled > cur;
    float res = FUN_00f409a0(n, &key, scaled, gt, &n->f24);
    n->f20 = res;
    if (res != cur) {
        if (key.b == 0x2b978c46) {
            ((UI*)((Simulator*)gSimulator)->pD4)->ToggleHint(0x23, 0x24);
        } else if (FUN_00eece20(&key) == 0xe137ff08) {
            ((UI*)((Simulator*)gSimulator)->pD4)->ToggleHint(0x37, 0x38);
        }
    }
    pGame->F3DA90(n, 0);
    char chk = g_015ad328obj.CheckObject((void*)handle);
    ((Simulator*)gSimulator)->p74->F3BBD0(handle, chk == 0);
}

// @ 0x00f00790 -- apply the placement for `p`
char UI::ApplyPlacement(void* p)
{
    if (!pGame->F3EC90(p)) {
        void* ms = FUN_0067dcc0();
        ((ThV3)vslot(ms, 0x14))(ms, 0x78c406b, 0, 0);
        return 0;
    }
    pGame->F45970();
    b6 = 1;
    void* r = FUN_00eec0d0(Place(p));
    FUN_00efe260();
    FwdC6E0(r);
    ((ThV1)vslot(this, 0x18))(this, 1);
    FUN_00efd970(r);
    void* gd = ((GD*)r)->F_B18530();
    if (gd != 0 && ((CGameData*)gd)->F_F253E0())
        ((UI*)r)->F_efcde0();
    g_016c7b34obj.F_eeff40();
    void* gim = FUN_00b3d250();
    ((ThV2)vslot(gim, 0x64))(gim, 0xc9d8638f, 1);
    return 1;
}

// @ 0x00f00850 -- apply the placement with the extended record walk
char UI::ApplyPlacementEx(void* p)
{
    Mgr* m = (Mgr*)g_mgr;
    if (m->mp10 != 0) {
        void* obj = m->mp10;
        int t = ((ThI1)vslot(obj, 0xc))(obj, 0x76c67df);
        if (t == 0) return 0;
        if (t == (int)m->mp28) return 0;
        if (m->mpSelected != p) F_efec90(p);
        ((Container*)m->mVec30)->F_00c68d20((void*)t);
        Node* n = (Node*)FUN_00eebf80(m->mp4);
        SNode* s = (SNode*)pGame->F3E8A0(n->vtable);
        char* base = n->p28;
        if (s->b20 == 0) {
            char flag = 0;
            ((Container*)m->mVec30)->F_00c688a0(base + m->mIndex * 0x34 + 0x1c, &flag);
            if (flag) *(uint32_t*)(base + m->mIndex * 0x34 + 0x30) = 2;
        } else {
            int count = (int)((n->p2c - n->p28) / 0x34);
            for (int i = 0; i < count; i++) {
                char flag = 0;
                ((Container*)m->mVec30)->F_00c688a0(base + i * 0x34 + 0x1c, &flag);
                if (flag) *(uint32_t*)(base + i * 0x34 + 0x30) = 2;
            }
        }
        ((UI*)((Simulator*)gSimulator)->pD4)->ToggleHint(0x63, 0x64);
        return 1;
    }
    if (!F_efc660(p)) return 0;
    bool e0 = (m->mpSelected == 0);
    bool skip = false;
    if (b5 != 0) { b5 = 0; FUN_00efe260(); }
    else if (e0) skip = true;
    if (!skip) {
        if (b6 != 0) {
            void* h = FUN_00eebf80(p);
            FUN_00eef7d0(h);
        }
        pGame->F45A80();
        b6 = 0;
    }
    pGame->F45970();
    void* n3 = FUN_00b3d240();
    void* r = ((ThP0)vslot(n3, 0x34))(n3);
    int t = 0;
    if (r != 0) t = ((ThI1)vslot(r, 0xc))(r, 0x17f243b);
    if (t != (int)p) {
        Node* o = (Node*)FUN_00b18e00(p);
        if (o != 0) {
            void* h = FUN_00ae66d0(o);
            ((ThV1)vslot(o, 0x28))(o, 0);
            if (h == m->mp8 && m->mp8 != 0) {
                void* old = m->mp8;
                m->mp8 = 0;
                do_release(old);
            }
            int* f = ((ThIP0)vslot(o, 0xac))(o);
            if (f) f[1] &= ~8u;
        }
    }
    void* h2 = FUN_00eebf80(p);
    void* r2 = FUN_00eec0d0(pGame->F445C0(h2));
    char c = CheckObject(r2);
    pGame->F3BBD0((int)r2, c == 0);
    FUN_00efe260();
    FwdC6E0(r2);
    ((UI*)((Simulator*)gSimulator)->pD4)->ToggleHint(0x21, 0x22);
    b7 = 1;
    FUN_00eef4b0(&m->begin8c);
    return 1;
}

// @ 0x00f00bd0 -- commit / clear the pending placement
void UI::CommitPlacement(void* p)
{
    Mgr* m = (Mgr*)g_mgr;
    if (m->mp20 == 0) return;
    if (p == 0) {
        void* x = m->mp10;
        if (x != 0) { m->mp10 = 0; do_release(x); }
        ((ThV1)vslot(this, 0x18))(this, 0);
    }
    void* r = pGame->F32790(p);
    if (p != 0) {
        int t = ((ThI0)vslot(p, 0x38))(p);
        bool matched = (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a ||
                        t == 0x7a81824 || t == 0x7abdd8d);
        if (matched && r == 0) {
            ((AutoRef*)&m->mp10)->F_00b5f950(p);
            return;
        }
    }
    pGame->f1b0 = r;
    void* old4 = m->mp4;
    if (p != old4) {
        if (p != 0) ((ThV0)vslot(p, 0))(p);
        m->mp4 = p;
        if (old4 != 0) do_release(old4);
    }
    if (p == 0 && m->mp8 != 0) { void* o = m->mp8; m->mp8 = 0; do_release(o); }
    UpdateVisibility();
    if (old4 != p) {
        void* gim = FUN_00b3d250();
        uint32_t arg = (p != 0 ? 0x463ccfb9u : 0u) + 0x91247de4u;
        ((ThV2)vslot(gim, 0x64))(gim, (int)arg, 1);
    }
}

// @ 0x00f00d10 -- tear the placement down
void UI::Teardown()
{
    Mgr* m = (Mgr*)g_mgr;
    Node* x = (Node*)FUN_00b18e00(m->mp10);
    if (x != 0) {
        void* h = FUN_00ae66d0(x);
        ((ThV1)vslot(x, 0x28))(x, 0);
        if (h == m->mp8 && m->mp8 != 0) { void* o = m->mp8; m->mp8 = 0; do_release(o); }
        int* f = ((ThIP0)vslot(x, 0xac))(x);
        if (f) f[1] &= ~8u;
    }
    pGame->F38330(1);
    pGame->F34560();
    if (m->mpSelected != 0) { void* o = m->mpSelected; m->mpSelected = 0; do_release(o); }
    if (m->mp10 != 0) { void* o = m->mp10; m->mp10 = 0; do_release(o); }
    g_16c7d74 = (g_16c7d74 == 0.0f) ? 1.0f : 0.0f;
    void* at = FUN_00a206f0();
    if (at != 0) {
        ((ThV1)vslot(at, 0x38))(at, 0x3cdd1a9);
        ((ThV2)vslot(at, 0x40))(at, 0x34753a7, (int)0xa984aa45u);
        ((ThV2F)vslot(at, 0x3c))(at, 0x34753aa, g_16c7d74);
        ((ThV0)vslot(at, 0x58))(at);
    }
}

// @ 0x00f00e50 -- update the placement for `p`
char UI::UpdatePlacement(void* p)
{
    Mgr* m = (Mgr*)g_mgr;
    void* n = pGame->F32790(p);
    if (p != 0) {
        int t = ((ThI0)vslot(p, 0x38))(p);
        bool inSet = (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a ||
                      t == 0x7a81824 || t == 0x7abdd8d);
        if (inSet && n == 0) return 0;
    }
    bool e0 = (m->mpSelected == 0);
    if (!F_efc7d0(p, (void*)(size_t)((PObj*)n)->f4)) return 0;
    bool skip = false;
    if (b5 != 0) b5 = 0;
    else if (e0) skip = true;
    if (!skip) {
        void* o = (void*)FUN_00b18e00(p);
        if (o != 0) {
            void* h = FUN_00ae66d0(o);
            ((ThV1)vslot(o, 0x28))(o, 0);
            if (h == m->mp8 && m->mp8 != 0) { void* old = m->mp8; m->mp8 = 0; do_release(old); }
            int* f = ((ThIP0)vslot(o, 0xac))(o);
            if (f) f[1] &= ~8u;
        }
        pGame->F38330(1);
        pGame->F34560();
        b6 = 0;
    }
    pGame->F33BF0();
    void* r = pGame->F336A0(n);
    SetObject(r);
    pGame->F36450((int)r, 0, n);
    b7 = 1;
    return 1;
}

// @ 0x00f00f80 -- dispatch pointer-motion to the active placement objects
void UI::Dispatch()
{
    Mgr* m = (Mgr*)g_mgr;
    void* obj = m->mp10;
    if (obj == 0 || m->mpSelected == 0) return;
    ((ThV0)vslot(obj, 0x5c))(obj);
    if (obj == m->mp20) {
        void* a = FUN_00b18e00(m->mpSelected);
        ((ThP1)vslot(a, 0x3c))(a, (char*)obj + 0x1a4);
        return;
    }
    if (obj == m->mp5c) {
        float v = ((Mp10Obj*)obj)->F_efc4c0() + g_0148cfe8;
        uint8_t old = b5;
        b5 = 1;
        Adjust(m->mpSelected, v);
        b5 = old;
        return;
    }
    if (obj == m->mp60) {
        float v = ((Mp10Obj*)obj)->F_efc4c0();
        *(float*)((char*)pGame->f1b0 + 0xc) = v;
    }
}

// @ 0x00f01090 -- add the tutorial object if the game accepts it
char UI::AddObject(void* unused)
{
    (void)unused;
    void* p10 = this->p10;
    NodeB* v = (NodeB*)FUN_00b18e00(0);
    if (v != 0 && v->b6e != 0) return 0;
    if (!pGame->F326D0(p10)) {
        void* ms = FUN_0067dcc0();
        ((ThV3)vslot(ms, 0x14))(ms, 0x78c406b, 0, 0);
        return 0;
    }
    b6 = 1;
    pGame->F33BF0();
    void* r = GetPlacement();
    SetObject(r);
    pGame->F36450((int)r, (int)p10, 0);
    ((ThV1)vslot(this, 0x18))(this, 1);
    FUN_00efd970(r);
    g_016c7b34obj.F_eeff40();
    void* gim = FUN_00b3d250();
    ((ThV2)vslot(gim, 0x64))(gim, 0xc9d8638f, 1);
    return 1;
}

// ---------------------------------------------------------------------------
// BuildScene helpers (addresses in comments).
extern "C" void* __cdecl FUN_0067dd10();               // 0x0067dd10 SP::App
extern "C" void  __cdecl FUN_007c4900(void*, void*);   // 0x007c4900
extern "C" void  __cdecl FUN_00efd8e0();               // 0x00efd8e0 ObjPlaneVec (pointer arrives in esi)
extern "C" char  __cdecl FUN_00ebaa20(void*, void*, void*, float, void*); // 0x00ebaa20 ray_sphere
extern "C" void  __cdecl FUN_00698180(void*, void*, void*); // 0x00698180 QuaternionFromDirections
extern "C" void  __cdecl FUN_00eed720(void*, void*, void*); // 0x00eed720
extern "C" float __cdecl FUN_00eec370(void*, uint32_t, void*); // 0x00eec370
extern "C" void  __cdecl FUN_00eec8e0(void*, void*, void*); // 0x00eec8e0 ResourceFlagPair
extern "C" void* __cdecl FUN_00b3d350(void*, void*);   // 0x00b3d350 SP::PlanetModel
extern "C" void* __cdecl FUN_00b82df0(void*, void*, uint32_t, int, int, int); // 0x00b82df0 ProjectToSurface
extern "C" void  __cdecl FUN_00eee760(void*, void*);   // 0x00eee760

// @ 0x00f011b0 -- build the scene placement for the selected object
void BuildScene()
{
    Mgr* m = (Mgr*)g_mgr;
    void* sel = m->mpSelected;
    Node* n = (Node*)FUN_00eebf80(sel);
    uint32_t handle = (uint32_t)(size_t)FUN_00b18e00(sel);
    Vec3 base = n->pos;
    float radius = m->f78;

    void* app = FUN_0067dd10();
    Vec3 dirA, dirB;
    ((ThV2P)vslot(app, 0x58))(app, &dirB, &dirA);
    FUN_007c4900(&dirB, &dirA);
    FUN_00efd8e0();

    // probe point: base + dirA
    float p1 = base.x + dirA.x;
    float p2 = base.y + dirA.y;
    float p3 = base.z + dirA.z;
    float g1 = p1, g2 = p2, g3 = p3;

    float probeR = radius;
    if (FUN_00ebaa20(&p1, &dirB, g_016c7b98, radius, &probeR)) {
        Vec3 hit;
        hit.x = dirB.x * radius + g1;
        hit.y = dirB.y * radius + g2;
        hit.z = dirB.z * radius + g3;

        Quat q;
        FUN_00698180(&q, &n->pos, &hit);

        float rx = n->rot.x, ry = n->rot.y, rz = n->rot.z, rw = n->rot.w;
        float t68 = rz * q.w - ry * q.z;
        float t64 = q.z * rx - rz * q.x;
        float t60 = ry * q.x - q.y * rx;
        float nx = q.w * rx + rw * q.x + t68;
        float ny = q.w * ry + rw * q.y + t64;
        float nz = q.w * rz + rw * q.z + t60;
        float nw = q.w * rw - (rx * q.x + rz * q.z + ry * q.y);
        float inv = 1.0f / sqrtf(nw * nw + (nz * nz + (ny * ny + nx * nx)));
        nx *= inv; ny *= inv; nz *= inv; nw *= inv;

        n->rot.x = nx; n->rot.y = ny; n->rot.z = nz; n->rot.w = nw;
        n->pos = hit;

        uint32_t flags = 1;
        FUN_00eed720(n, (void*)(size_t)handle, &flags);
        uint32_t f = (uint32_t)((handle >> 4) & 1);
        uint32_t sel2 = 1;
        float dist = FUN_00eec370(&n->pos, f, &sel2);
        n->f220 = dist;
        char c81 = 0, c82 = 0;
        FUN_00eec8e0(n, &c82, &c81);
        if ((n->f220 > 0.0f && c81 == 0) || (n->f220 < 0.0f && c82 == 0)) {
            Vec3 out;
            out.x = out.y = out.z = 0.0f;
            void* surf = FUN_00b3d350(&out, &n->pos);
            void* res = FUN_00b82df0(surf, &n->pos, f, 1, 1, 0);
            float* rp = (float*)res;
            n->pos.x = rp[0]; n->pos.y = rp[1]; n->pos.z = rp[2];
            n->f220 = 0.0f;
        }
    }
    ((Obj74*)((Simulator*)gSimulator)->p74)->F3DA90(n, 0);
    if (g_015acb40 != 0) FUN_00eee760(n, &m->begin8c);
}
