// Shared types for slices s00958a70 and s0095b310 (EA::UTFWin::WindowMgr and friends).
#pragma once
#include "types.h"
typedef uint8_t u8;
typedef uint32_t u32;

extern void* __cdecl GetAlloc();                                   // 0x9512c0
struct EAlloc { void* p; EAlloc(void* x) : p(x) {} };
struct Node { Node* next; Node* prev; };
inline void* operator new(unsigned int, void* p) { return p; }

struct V2 {
    float x, y;
    V2() {}
    V2(float a, float b) : x(a), y(b) {}
    V2(const V2& o) : x(o.x), y(o.y) {}
};
struct IObj { virtual void o0(); virtual void Release(); virtual void o2(); virtual void o3(); virtual void o4(); virtual void Destroy(void* p); };
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
    virtual void i32(); virtual void i33(); virtual void i34(); virtual void i35();
    virtual void i36(); virtual void i37(); virtual void i38(); virtual void i39();
    virtual void i40(); virtual void i41(); virtual void i42(); virtual void i43();
    virtual void i44(); virtual void i45(); virtual void i46();
    virtual bool vHitLocal(V2 p);                      // vtbl+0xbc (47)
    virtual void i48();
    virtual V2 vToLocal(V2 p);                         // vtbl+0xc4 (49)
    virtual bool vHit(V2 p, V2* out);                  // vtbl+0xc8 (50)
    virtual void i51(); virtual void i52(); virtual void i53(); virtual void i54();
    virtual void i55(); virtual void i56(); virtual void i57();
    virtual void vSetOwner(IWin* w);                   // vtbl+0xe8 (58)
    virtual void i59(); virtual void i60(); virtual void i61();
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
struct MsgNode { Node link; Msg msg; };
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
struct ChunkItem { IRel* obj; u32 b; };
struct Chunk { Chunk* next; int count; ChunkItem items[5]; void __thiscall Swap(Chunk* o); };   // Swap 0x95ba90
template <class T> struct Ref {
    T* p;
    Ref(T* x) : p(x) {}
    ~Ref() { if (p) p->Release(); }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};

extern void __cdecl FreeRenderableListChunks(void* first, void* last);   // 0x956e30
extern void __cdecl FreeDisplayListEntries(void* head);                  // 0x956fa0
extern char vtbl_WindowMgr;                                        // 0x14406a0
extern float g_13eb1bc, g_1440738;

struct ListHead { Node n; ListHead() { n.prev = &n; n.next = &n; } ~ListHead(); };      // dtor 0x620230
struct Mutex { Mutex(int a, int b); ~Mutex(); u32 pad[12]; };             // 0x9222a0
struct Typesetter { Typesetter(int a); ~Typesetter(); u32 pad[0x14c]; };         // 0x89d820
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


