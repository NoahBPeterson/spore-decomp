// src/game/SPGonzago/SPGonzagoAccessor.cpp -- migrated from slice(s) s00b3cf00, s00958a70 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGonzagoAccessor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/Thread/Mutex.h"
#include "EA/Text/Typesetter.h"
#include "SP/cLocomotiveObject.h"
#include <math.h>

// ---- items of slice s00958a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t u8;
typedef uint32_t u32;
struct EAlloc { void* p; EAlloc(void* x) : p(x) {} };
struct Node { Node* next; Node* prev; };
struct V2 {
    float x, y;
    V2() {}
    V2(float a, float b) : x(a), y(b) {}
    V2(const V2& o) : x(o.x), y(o.y) {}
};
struct Msg;
struct IWin;
struct ICb { virtual void c0(); virtual void Call(IWin* w, IWin* arg); };
struct IHook {
    virtual void h0();
    virtual void Release();
    virtual void h2();
    virtual void Notify(int code, IWin* w, Msg* m);   // vtbl+0xc
};
struct IAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(int sz, const char* name, u32 flags);   // vtbl+8
    virtual void Free(void* p, int sz);               // vtbl+0xc
};
struct IRel { virtual void r0(); virtual void Release(); };   // vtbl+4
struct IWin {
    virtual void i00();
    virtual void i01();
    virtual void i02();
    virtual void i03();
    virtual IWin* vGetParent();
    virtual void i05();
    virtual void i06();
    virtual void i07();
    virtual void i08();
    virtual void i09();
    virtual void i0a();
    virtual void i0b();
    virtual void i0c();
    virtual void i0d();
    virtual void i0e();
    virtual void i0f();
    virtual void i10();
    virtual void i11();
    virtual void i12();
    virtual void i13();
    virtual void i14();
    virtual void i15();
    virtual void i16();
    virtual void i17();
    virtual void i18();
    virtual void i19();
    virtual void i1a();
    virtual void i1b();
    virtual void i1c();
    virtual void i1d();
    virtual void i1e();
    virtual void vSetFlags(int a, int b);              // vtbl+0x7c (31)
virtual void i32();
virtual void i33();
virtual void i34();
virtual void i35();
virtual void i36();
virtual void i37();
virtual void i38();
virtual void i39();
virtual void i40();
virtual void i41();
virtual void i42();
virtual void i43();
virtual void i44();
virtual void i45();
virtual void i46();
    virtual bool vHitLocal(V2 p);                      // vtbl+0xbc (47)
    virtual void i48();
    virtual V2 vToLocal(V2 p);                         // vtbl+0xc4 (49)
    virtual bool vHit(V2 p, V2* out);                  // vtbl+0xc8 (50)
virtual void i51();
virtual void i52();
virtual void i53();
virtual void i54();
virtual void i55();
virtual void i56();
virtual void i57();
    virtual void vSetOwner(IWin* w);                   // vtbl+0xe8 (58)
virtual void i59();
virtual void i60();
virtual void i61();
    virtual bool vAccepts(IWin* w);                    // vtbl+0xf8 (62)
};
struct Base0 { virtual void b0(); virtual void Release(); };
struct Win : Base0, IWin {
    Node n8;            // +8 child-list link
    u32  f10;
    u32  f14;
    Node n18;           // +0x18, prev(+0x1c) != 0 means linked
    u32  f20, f24, f28;
    u32  flags;         // +0x2c
    u8   b30, b31, b32, b33;
    u32  f34;
    Win* parent;        // +0x38
    Node children;      // +0x3c
    u8   pad44[0x78 - 0x44];
    u32  f78;
};
struct Msg { IWin* src; IWin* dst; u32 rest[5]; };
struct Iter { Node* n; };
struct MsgList {
    Node    anchor;      // +0
    IAlloc* alloc;       // +8
    u32     allocFlags;  // +0xc
    MsgList(const EAlloc& a) { alloc = (IAlloc*)a.p; allocFlags = 0; anchor.next = &anchor; anchor.prev = &anchor; }
    ~MsgList() {
        Node* p = anchor.next;
        while (p != &anchor) { Node* n = p; p = p->next; alloc->Free(n, 0x24); }
    }
    // @ 0x958ca0
    Iter __thiscall EraseRange(Iter first, Iter last);
    // @ 0x9595e0
    void __thiscall InsertRange(Node* where, Iter first, Iter last, int tag);
};
struct FocusList {
    Node    anchor;      // +0
    IAlloc* alloc;       // +8
    u32     allocFlags;  // +0xc
    FocusList(const EAlloc& a) { alloc = (IAlloc*)a.p; allocFlags = 0; anchor.next = &anchor; anchor.prev = &anchor; }
    ~FocusList() {
        Node* p = anchor.next;
        while (p != &anchor) { Node* n = p; p = p->next; alloc->Free(n, 0x10); }
    }
};
template <class T> struct Ref {
    T* p;
    Ref(T* x) : p(x) {}
    ~Ref() { if (p) p->Release(); }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};
struct ListHead { Node n; ListHead() { n.prev = &n; n.next = &n; } ~ListHead(); };      // dtor 0x620230
struct Mutex {
    Mutex(int a, int b);   // 0x9222a0
    ~Mutex();
    u32 pad[12];
};
struct Typesetter {
    Typesetter(int a);     // 0x89d820
    ~Typesetter();
    u32 pad[0x14c];
};
struct WM {
    virtual ~WM();
    virtual void s01();
    virtual void s02(int a, int b);
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08(int a);
    virtual void s09();
    virtual void s0a();
    virtual void s0b();
    virtual void s0c();
    virtual void s0d();
    virtual void s0e(int a);
    virtual void s0f();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void SetFocus(int a, IWin* w);              // vtbl+0x4c (19)

    // @ 0x958bb0
    void __thiscall DestroyDisplayList(Node* head);
    // @ 0x958a70
    Win* __thiscall HitTest(Win* w, V2* pt, const V2& p3, V2* outLocal);
    // @ 0x958b60
    void __thiscall MarkTree(Win* w);
    // @ 0x958c60
    bool __thiscall IsFocusWindow(IWin* w);
    // @ 0x958cf0
    WM();
    // @ 0x958fa0
    bool __thiscall SendModifiedMsg(IWin* w, IWin* src, Msg* m);
    // @ 0x959050
    IWin* __thiscall UpdateCursorWindow(V2* out, bool flag);
    // @ 0x959230
    IWin* __thiscall FindWindowAt(const V2* pt);
    // @ 0x9592a0
    void __thiscall LinkTickable(Win* w);
    // @ 0x9592e0
    bool __thiscall DispatchTree(Msg* m, bool flag);
    // @ 0x9593d0
    bool __thiscall DispatchUp(Win* w, Msg* m, bool flag);
    // @ 0x9594b0
    bool __thiscall PopFocus(IWin* w, IWin* arg);
    // @ 0x959640
    bool __thiscall SendMsgFull(IWin* src, IWin* win, Msg* m, bool a4, bool a5);

    // @ 0x95b860
    void __thiscall Shutdown();
    // @ 0x95b310
    void __thiscall UpdateVisuals();
    // external (other slices)
    void __thiscall UpdateRenderState(Win* w, int a, int b);              // 0x95a140
    void __thiscall BuildDisplayList(Node* out, Win* w, void* tmp);       // 0x95a580
    void __thiscall RenderWindow(Win* w, void* ctx);                      // 0x95a510
    void __thiscall ComputeClip(void* out, Win* w);                       // 0x958150
    void __thiscall ResetChildWindowCache();                              // 0x962be0
    void __thiscall FlushMessageQueue();                                  // 0x95b290
    bool __thiscall DispatchMsgToWindow(Win* w, Msg* m, int f);  // 0x9589f0 (not in slice)
    void __thiscall F9587d0(Win* w);                               // 0x9587d0 (not in slice)

    Ref<Win> mainWin;    // +4
    ListHead lA;         // +8
    ListHead lB;         // +0x10 (tickable windows)
    ListHead lC;         // +0x18
    Node*  tickIter;     // +0x20
    u8     f24, f25, pad26[2];
    Mutex  mxA;          // +0x28
    u8     f58, f59, pad5a[2];
    ListHead lD;         // +0x5c
    ListHead lE;         // +0x64
    u8     pad6c[4];
    Mutex  mxB;          // +0x70
    ListHead lF;         // +0xa0
    float  fa8, fac, fb0, fb4;
    Ref<IRel> fb8;       // +0xb8
    float  mx, my;       // +0xbc,+0xc0
    u32    fc4;
    Ref<IHook> hook;     // +0xc8
    u32    fcc, fd0;
    MsgList q0, q1, q2, q3, q4;   // +0xd4
    u32    f124;
    Typesetter ts;       // +0x128
    Mutex  mxC;          // +0x658
    u32    f688;
    u8     pad68c[0x6b4 - 0x68c];
    Win*   f6b4;
    u32    f6b8;
    Win*   f6bc;
    u8     pad_6c0[0x81c - 0x6c0];
    FocusList focusList; // +0x81c
    IWin*  cur;          // +0x82c
    ICb*   curCb;        // +0x830
    u8     f834;
};
// ---- items of slice s00958a70 end

// ---- items of slice s00b3cf00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_167eae4;              // 0x0167eae4
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
struct V00 { virtual void      f00(); };
struct V04 { G0  virtual void      f04(); };
struct V1C { G6  virtual void*     f1C(unsigned id); };
struct V70 { G27 virtual float     f70(); };
struct VAC { G42 virtual void*     fAC(void* a); };
struct VB0 { G43 virtual void*     fB0(); };
void* __cdecl SP_GetCurrentGameMode();       // 0x00b5b800
void* __cdecl SP_ModelManager();              // 0x0067dd80
bool  __cdecl IsFinite(float f);              // 0x0059ab10
void* __cdecl FUN_00b3d3c0(void* p);          // 0x00b3d3c0
void* __cdecl FUN_010212f0();                 // 0x010212f0
struct Obj40 {
    char pad0[0x44];
    float f44;                       // +0x44
    char pad48[0x70 - 0x48];
    unsigned char b70;               // +0x70
    unsigned char b71;               // +0x71
    char pad72[0x75 - 0x72];
    unsigned char b75;               // +0x75
    char pad76[0x1f0 - 0x76];
    int  n1f0;                       // +0x1f0

    float* GetVelocity();            // 0x00d20610
    float* GetBounding();            // 0x00c41d50
};
struct C101 {
    char  pad0[4];
    int   nMode;                     // +0x04
    char  pad8[0xc - 8];
    int   nC;                        // +0x0c
    float f10;                       // +0x10
    float f14;                       // +0x14
    float f18;                       // +0x18
    float f1c, f20, f24;             // +0x1c
    float f28, f2c, f30;             // +0x28
    unsigned char b34, b35, b36, b37;// +0x34
    char  pad38[0x40 - 0x38];
    Obj40* p40;                      // +0x40
    char  pad44[0x68 - 0x44];
    int   n68, n6c;                  // +0x68
    char  pad70[0xe0 - 0x70];
    float e0, e4, e8;                // +0xe0
    float ec, f0, f4;                // +0xec
    char  padf8[0x1f8 - 0xf8];
    float arr;                       // +0xf8 (base of per-index vec3 array)

    float M_cf00();
    void  M_cf40();
    bool  M_d5f0();
    float M_d630();
    void* M_d6a0();
    void  M_d730();
    void  M_d7a0();
    void* M_d8c0();
    void  M_d9c0(float* out);
    void  M_da90(float* out, int idx, C101* other);
    void  M_dbb0();
    float M_dcd0();
    bool  M_dd40();
    void  M_dda0(float* a, float* b);
    void  M_dec0(float* v);
};
struct C7C   { void* f360(void*); void* f480(void*); }; // 0xb7c360 / 0xb7c480
struct C4F { void* f(); };                        // 0x00c4f030 (ecx = g_167eae4)
// ---- items of slice s00b3cf00 end

// @ 0x00959640
bool __thiscall WM::SendMsgFull(IWin* src, IWin* win, Msg* m, bool a4, bool a5)
{
    u32 saved = f688;
    f688 = 0;
    Win* w = static_cast<Win*>(win);
    Msg msg = *m;
    msg.src = src;
    IWin* wi = w;
    msg.dst = wi;
    if (hook)
        hook->Notify(0, 0, &msg);
    bool r = false;
    if (a5) {
        r = DispatchUp(w, &msg, 0);
        f688 = saved;
        return r;
    }
    if (a4) {
        r = DispatchTree(&msg, 0);
        f688 = saved;
        return r;
    }
    if (DispatchMsgToWindow(w, &msg, 0)) {
        if (hook) {
            IWin* a = w;
            hook->Notify(4, a, &msg);
        }
        r = true;
    }
    if (hook && !r)
        hook->Notify(5, 0, &msg);
    f688 = saved;
    return r;
}

// @ 0x00b3d2c0
void* __cdecl SP_RelationshipManager()
{
    void* m = SP_GetCurrentGameMode();
    if ((int)m < 0x01654c06) {
        if (m == (void*)0x01654c05)
            return ((C4F*)g_167eae4)->f();
        if (m != (void*)0x01654c02 && m != (void*)0x01654c04)
            return 0;
    } else if (m != (void*)0x01654c10) {
        if (m != (void*)0x02ccd1d2)
            return 0;
        return ((C4F*)g_167eae4)->f();
    }
    return FUN_010212f0();
}

// @ 0x00b3d520
void* __cdecl SP_GonzagoModelWorld()
{
    void* mm = SP_ModelManager();
    void* p = ((V1C*)mm)->f1C(0x00eb9968u);
    if (p) {
        ((V00*)p)->f00();
        ((V04*)p)->f04();
    }
    return p;
}

// @ 0x00b3d550
bool __cdecl FUN_00b3d550(float* v)
{
    if (((*(unsigned*)&v[3] & 0x7fffffffu) == 0) ||
        (((*(unsigned*)&v[3] - 0x00800000u) & 0x7f800000u) < 0x7f000000u)) {
        if (((*(unsigned*)&v[0] & 0x7fffffffu) == 0) ||
            (((*(unsigned*)&v[0] - 0x00800000u) & 0x7f800000u) < 0x7f000000u)) {
            if (((*(unsigned*)&v[1] & 0x7fffffffu) == 0) ||
                (((*(unsigned*)&v[1] - 0x00800000u) & 0x7f800000u) < 0x7f000000u)) {
                if (IsFinite(v[2]))
                    return true;
            }
        }
    }
    return false;
}

// @ 0x00b3d5f0
bool C101::M_d5f0()
{
    switch (nMode) {
    case 0: goto body;
    case 1: goto body;
    case 2:
        return true;
    }
    return false;
body:
    {
        Obj40* o = p40;
        if (o->b75 != 0 && (o->b70 != 0 || b35 != 0))
            return true;
        return false;
    }
}

// @ 0x00b3d630
float C101::M_d630()
{
    float local = 0.0f;
    if (f18 > 0.0f)
        return f18;
    switch (nMode) {
    case 0: goto mode01;
    case 1: goto mode01;
    case 2:
        local = p40->f44;
        break;
    }
    return f10 * local;
mode01:
    {
        float r = ((V70*)p40)->f70();
        return r * f10;
    }
}

// @ 0x00b3d6a0
void* C101::M_d6a0()
{
    switch (nMode) {
    case 0: goto body;
    case 1: goto body;
    case 2:
        return ((C7C*)FUN_00b3d3c0(p40))->f480(p40);
    }
    return 0;
body:
    {
        Obj40* o = p40;
        void* a = ((VB0*)o)->fB0();
        void* b = ((VAC*)o)->fAC(a);
        return ((C7C*)FUN_00b3d3c0(b))->f360(b);
    }
}
