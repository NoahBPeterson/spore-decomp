// src/game/UTFSpore_Win32/manager2.cpp -- migrated from slice(s) s0095b310, s0095a580, s00959780, s00958a70, s009579f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/manager2.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/WindowMgr.h"
#include "EA/Thread/Mutex.h"
#include <intrin.h>
#include <xmmintrin.h>
#include "EA/UTFWin/IModalWindowCallback.h"
#include "EA/Audio/Group.h"
#include "EA/Swarm/cIMap.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Text/Typesetter.h"
#include <string.h>
#include "EA/UTFWin/IRenderer.h"
#include "EA/UTFWin/Renderable2DBuilder.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/UTFWin/IStandardShader.h"
#include "EA/UTFWin/IRenderable.h"
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchange)

// ---- items of slice s009579f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define B(p)     ((char*)(p))
#define I8(p,o)  (*(char*)((char*)(p)+(o)))
#define U8(p,o)  (*(unsigned char*)((char*)(p)+(o)))
#define I32(p,o) (*(int*)((char*)(p)+(o)))
#define U32(p,o) (*(unsigned*)((char*)(p)+(o)))
#define PTR(p,o) (*(void**)((char*)(p)+(o)))
#define F32(p,o) (*(float*)((char*)(p)+(o)))
struct Ext {
    void* ctor(int, int);                                    // 0x009222A0 Mutex::Mutex
    int   Lock(const void*);                                 // 0x009221B0 Mutex::Lock
    void  tp3(float* out, const float* in);                  // 0x0095EEB0 TransformPoint3
    void  tp4(float* out, const float* in);                  // 0x0095F1C0 TransformPoint4
    void  bb80(void*);                                       // 0x0095BB80
    void  bd60(void*, void*);                                // 0x0095BD60
    void  Splice1(void*);                                    // 0x0099A9D0 XmlReaderState::Splice
    void  ba90(void*);                                       // 0x0095BA90
    void* ba70(void*);                                       // 0x0095BA70
    void  ea0();                                             // 0x00961AE0
    void  r2db_dtor();                                       // 0x00952F80 Renderable2DBuilder::~Renderable2DBuilder
    void  iba0();                                            // 0x00951BA0
};
int __fastcall Mutex_Unlock(void*);                          // 0x00922270
struct VTab {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c(int);
    virtual void  v10(int, int);
    virtual void  v14();
    virtual void  v18(int, int, void*);
    virtual void  v1c();
    virtual char  v20(void*);
    virtual void  v24();
    virtual void  v28();
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void  v38();
    virtual void  v3c();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58(int, int);
    virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void  v70();
    virtual char  v74(void*, int);
    virtual void  v78(void*, int);
    virtual void  v7c();
};
struct VS6 {
    virtual void  a0(); virtual void  a1(); virtual void  a2();
    virtual void  a3(); virtual void  a4(); virtual void  a5();
    virtual char  f(void*, void*);
};
struct APCData { char lead[8]; int tag; int p2; void* p3; };
struct W {
    void     PostAPC(int a, void* b);            // 0x00957D40
    void     d90(void* a);                       // 0x00957D90
    char*    db0(int idx);                       // 0x00957DB0
    unsigned dd0(void* target);                  // 0x00957DD0
    char*    e70(int idx);                       // 0x00957E70
    void     e90(int idx, void* arg);            // 0x00957E90
    void     ed0(unsigned mask, char set);       // 0x00957ED0
    void     ff0(void* obj);                     // 0x00957FF0
    void     x070(float* pt);                    // 0x00958070
    void     x0b0(void* target);                 // 0x009580B0
    void     x0e0(char* node);                   // 0x009580E0
    char     x500(void* obj, int a);             // 0x00958500
    void     ComputeClip(float* out, void* node);// 0x00958150
    void     Plot(int param);                    // 0x009586F0
    void     m7d0(char* node);                   // 0x009587D0
    void     m820(char* node);                   // 0x00958820
    void     m860(char* node);                   // 0x00958860
    void     m8c0(char* node);                   // 0x009588C0
    void     DispatchMsgToWindow(int p2, char* p3, int p4); // 0x009589F0
};
void  __fastcall Fn00957fa0(void* self);     // 0x00957FA0
void  __fastcall Fn00958110(void* self);     // 0x00958110
void  __cdecl    Fn00958570(void* a, int* b, int* c);   // 0x00958570
void  __fastcall DumpDisplayList(void* self);            // 0x00958640
char  __cdecl    Fn00958920(int* self, void* p2, char* p3, char p4, unsigned p5); // 0x00958920
void* __fastcall Fn00957f50(void* self);                 // 0x00957F50
void  __cdecl    ProcessPendingTextures();               // 0x00957D30
struct MsgNode {
    void* f0;
    void* f4;
    int   fc;
    int   f8;
    char  f10;
};
// ---- items of slice s009579f0 end

// ---- items of slice s00958a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __cdecl GetAlloc();                                   // 0x9512c0
extern void __cdecl FreeRenderableListChunks(void* first, void* last);   // 0x956e30
extern void __cdecl FreeDisplayListEntries(void* head);                  // 0x956fa0
extern float g_13eb1bc, g_1440738;
typedef uint8_t u8;
typedef uint32_t u32;
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
struct MsgNode_s0095_8a70 { Node link; Msg msg; };
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
#define W_s0095_8a70(o) (*(u32*)((u8*)this + (o)))
static inline Win* NodeToWin(Node* n) { return n ? (Win*)((u8*)n - 8) : 0; }
// ---- items of slice s00958a70 end

// ---- items of slice s00959780 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uchar;
double __cdecl  iat_floor(double);                                 // 0x11e0906
int    __cdecl  ModulateARGB32(int a, int b);                      // 0x95f8c0
struct TC {
    void* Fn00951d50();                                            // 0x951d50
    void  Fn009592e0(void* p, int a);                              // 0x9592e0
    void* GetPositionStatic(void* p, int b);                       // 0x959050
    char  AllDescendants(int a);                                   // 0x95fbb0
    void* Fn0095fc00(int a);                                       // 0x95fc00
    void  Fn0095e7a0();                                            // 0x95e7a0
    void  Fn0095f620();                                            // 0x95f620 Invert
    void  Fn0095e890(void* p);                                     // 0x95e890
    void  Fn0095e810(void* a, void* b);                            // 0x95e810
    void  Fn0095f860(void* p);                                     // 0x95f860 Matrix43::Multiply
    int   Lock_(const void* name);                                 // 0x9221b0
    int   Unlock_();                                               // 0x922270
    void  e31b20(void* p);                                         // 0x00e31b20
    void  End2D();                                                 // 0x0095bb20
    void  Fn00957fa0();                                            // 0x957fa0
};
#define TH(x) ((TC*)(x))
struct W_s0095_9780 {
    char GV(int a, int b, void* c, int d, int e);                  // 0x00959640
    void RenderWindow(int win, void* ctx);                         // 0x0095a510
    void a0b0(int p2, int* p3);                                    // 0x0095a0b0
    void fe0(int win);                                             // 0x00959fe0
    void cf0(int p2, int p3);                                      // 0x00959cf0
    int  b70(int p2, int p3);                                      // 0x00959b70
    void DetachWindow(void* win);                                  // 0x00959e00
    void UpdateRenderState(int win, char p3, char p4);             // 0x0095a140
    char Fn00959780(int* ev, char p3);                             // 0x00959780
};
#define VFP(off) (*(void**)((char*)*(void**)this + (off)))
// ---- items of slice s00959780 end

// ---- items of slice s0095a580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void __cdecl FreeDisplayListEntry(void* p);                // 0x956e90
extern void __cdecl EastlListSwap(void* a, void* b);              // 0x75d8d0
extern float g_1470f1c;                                           // 2.0f
typedef uint16_t u16;
struct RectF { float x0, y0, x1, y1; };
struct Xform { float m[17]; };
struct IRenderMode;
struct IRenderer {
    virtual void AddRef();                                         // +0
virtual void Release();
virtual void r2();
virtual void r3();
    virtual void* CreateData(IWin* w);                             // +0x10
};
struct Base2D { Base2D(void*); virtual ~Base2D(); u32 d[8]; };      // ctor 0x9520a0 dtor 0x951ba0
struct Builder { Builder(); ~Builder(); u32 d[40]; };               // ctor 0x952aa0 dtor 0x952f80
struct Batch2D : Base2D { Builder b; Batch2D(void* a) : Base2D(a) {} };
struct RenderCtx {
    Xform* xf; u32 shade; RectF clip; RectF vp; float trans[3]; float scale[3];
    IRenderMode* mode; IRenderMode* defMode; Node* list; Xform* mat; u32 colorMod; Chunk* chunks;
    Batch2D batch;
    RenderCtx(void* a);                                            // 0x95bb80
};
struct DLEntry {                                                  // 0x100
    Node link;                                                    // +0
    DLEntry* prevEntry;                                           // +8
    u8 b0c, b0d, b0e, b0f;                                        // +0xc
    u16 depth, lowest;                                            // +0x10
    IRenderer* renderer;                                          // +0x14
    Chunk chunks;                                                 // +0x18
    u8 data[0x44];                                                // +0x48
    u8 clip[0x10];                                                // +0x8c
    u32 f9c;                                                      // +0x9c
    u32 fA0;                                                      // +0xa0
    u8 pad[0x58];                                                 // +0xa4 .. +0xfb
    u32 fFC;                                                      // +0xfc
};
extern DLEntry* __cdecl AllocDisplayListEntry();                  // 0x956ff0
struct WindowMgr : WM {
    // @ 0x95a580
    void __thiscall BuildDisplayList(Node* out, Win* w, void* info);
    // @ 0x95a8e0
    void __thiscall SetViewportSize(float vw, float vh);
    // @ 0x95a980
    bool __thiscall SendMsg(IWin* src, IWin* win, Msg* m, bool a4);
    // @ 0x95a9a0
    void __thiscall PostMsg(IWin* src, IWin* dst, const Msg* m);
    // @ 0x95aa80
    void __thiscall ProcessMessages();
    // @ 0x95add0
    void __thiscall AttachWindow(Win* w);
    // @ 0x95af00
    void __thiscall UpdateWindowCachedTransforms(Win* w);
    // @ 0x95af20
    bool __thiscall SetFocusWindow(IWin* w, ICb* cb);
    // @ 0x95b080
    bool __thiscall SetMainWindow(IWin* w, char release);
    // @ 0x95b290
    void __thiscall FlushMessageQueue();

    // callees outside this slice
    void __thiscall F959fe0(Win* w);          // 0x959fe0
    void __thiscall F9588c0(Win* w);          // 0x9588c0
    void __thiscall F958860(Win* w);          // 0x958860
    void __thiscall F958110();                // 0x958110
    void __thiscall DetachWindow(Win* w);     // 0x959e00
    bool __thiscall FCtx(Msg* m, int flag);   // 0x959780
};
struct MsgListX : MsgList {
    // @ 0x95a870
    MsgListX* __thiscall AssignFrom(MsgListX* src);
    // @ 0x95afd0
    void __thiscall Swap(MsgListX& other);
};
struct FocusListX : FocusList {
    // @ 0x95a820
    void __thiscall InsertFront(const void* value);
};
struct MutexOps {
    void __thiscall Lock(const void* name);                        // 0x9221b0
    void __thiscall Unlock();                                      // 0x922270
};
#define LMUTEX() ((MutexOps*)&mxC)->Lock((const void*)0x1440688)
#define UMUTEX() ((MutexOps*)&mxC)->Unlock()
struct RawMsgList { Node anchor; IAlloc* alloc; u32 allocFlags; };
static inline Iter MkIter(Node* n) { Iter i; i.n = n; return i; }
static void Splice(Node* pos, Node* first, Node* last)
{
    Node* after = last->prev;
    after->next = pos;
    first->prev->next = last;
    pos->prev->next = first;
    Node* old = pos->prev;
    pos->prev = last->prev;
    last->prev = first->prev;
    first->prev = old;
}
static void FillDLEntry(WindowMgr* self, DLEntry* e, Win* w, u32* info, u8 b0c)
{
    e->prevEntry = (DLEntry*)w->f78;
    e->b0c = b0c;
    e->b0d = 0;
    e->b0e = 0;
    e->depth  = (u16)info[0];
    e->lowest = (u16)info[1];
    IRenderer* r = *(IRenderer**)((u8*)w + 0x1e8);
    e->renderer = r;
    if (r != 0) {
        ((void(__thiscall*)(void*))(*(void***)r)[0])(r);
        e->fA0 = (u32)((void*(__thiscall*)(void*, void*))(*(void***)r)[0x10 / 4])(r, (void*)((u8*)w + 4));
    }
    e->fFC = 0;
    {
        u32* d = (u32*)e->data;
        u32* s = (u32*)((u8*)w + 0x14c);
        for (int i = 0; i < 0x11; i++) d[i] = s[i];
    }
    self->ComputeClip(e->clip, w);
    e->f9c = *(u32*)((u8*)w + 0x1d4);
}
// ---- items of slice s0095a580 end

// ---- items of slice s0095b310 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RectF_s0095_b310 {
    float x0, y0, x1, y1;
    void __thiscall Intersect(const RectF_s0095_b310& a, const RectF_s0095_b310& b);     // 0x634b60
};
struct Xform_s0095_b310 {
    float m[17];                                                    // 0x44 bytes (Matrix43)
    void __thiscall Init(const float* trans, const float* scale);   // 0x95e810
    void __thiscall Multiply(const Xform_s0095_b310* o);                       // 0x95f860
};
struct RenderCtx_s0095_b310;
struct IRenderable {
    virtual void AddRef();                                          // +0
    virtual void Release();                                         // +4
    virtual void r2();
    virtual void Render(RenderCtx_s0095_b310* c);                              // +0xc
};
struct IRenderMode_s0095_b310 {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void Begin();                                           // +0x10
    virtual void Render(IRenderable* r, RenderCtx_s0095_b310* c);              // +0x14
    virtual void End();                                             // +0x18
    virtual bool vFlag();                                           // +0x1c
};
struct IRenderer_s0095_b310 {
    virtual void AddRef(); virtual void Release(); virtual void r2();
    virtual bool NeedsPrepass();                                    // +0xc
    virtual void* CreateData(IWin* w);                              // +0x10
    virtual void  FreeData(void* d);                                // +0x14
    virtual void  RenderBatch(void* data, RenderCtx_s0095_b310* c, Node** begin, int n, int flag);   // +0x18
    virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16();
    virtual void r17(); virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21();
    virtual void DrawRect(const RectF_s0095_b310* dst, const RectF_s0095_b310* clip, const RectF_s0095_b310* uv);   // +0x58
};
struct Base2D_s0095_b310 {                                                  // size 0x24
    Base2D_s0095_b310(void* a);                                             // 0x9520a0
    virtual ~Base2D_s0095_b310();                                           // 0x951ba0
    u32 d[8];
};
struct Batch2D_s0095_b310 : Base2D_s0095_b310 {
    Builder b;                                                       // +0x24
    Batch2D_s0095_b310(void* a) : Base2D_s0095_b310(a) {}
    IRenderable* __thiscall Take();                                  // 0x9557c0
};
struct RenderData {                                                  // 0x5c
    Xform_s0095_b310 xf;                                                        // +0
    float r0, r1, r2, r3;                                            // +0x44 clip rect
    u32 shade;                                                       // +0x54
    void* rdata;                                                     // +0x58
};
struct DispEntry {                                                   // 0x100
    Node link;                                                       // +0
    DispEntry* prevEntry;                                            // +8
    u8 bReplace, bActive, bSecond, pad0f;                            // +0xc..
    u16 depth, lowest;                                               // +0x10 / +0x12
    IRenderer_s0095_b310* renderer;                                             // +0x14
    Chunk chunks;                                                    // +0x18 (0x30)
    RenderData data[2];                                              // +0x48
};
struct RenderCtx_s0095_b310 {
    Xform_s0095_b310* xf;          // 0
    u32    shade;       // 4
    RectF_s0095_b310  clip;        // 8
    RectF_s0095_b310  vp;          // 0x18
    float  trans[3];    // 0x28
    float  scale[3];    // 0x34
    IRenderMode_s0095_b310* mode;  // 0x40
    IRenderMode_s0095_b310* defMode;   // 0x44
    Node*  list;        // 0x48
    Xform_s0095_b310* mat;         // 0x4c
    u32    colorMod;    // 0x50
    Chunk* chunks;      // 0x54
    Batch2D_s0095_b310 batch;      // 0x58

    // @ 0x95bb80
    RenderCtx_s0095_b310(void* a) : mode(0), defMode(0), mat(0), colorMod(0xffffffff), chunks(0), batch(a) {}
    // @ 0x95bb20
    void __thiscall End2D();
    // @ 0x95bbc0
    void __thiscall AddRenderable(IRenderable* r);
    // @ 0x95bc10
    Batch2D_s0095_b310* __thiscall Begin2D(IRenderMode_s0095_b310* m);
    // @ 0x95bc40
    Node** __thiscall RenderBatch(Node** pIt, DispEntry* head, int flag);
    // @ 0x95bd60
    void __thiscall RenderList(Node* lst, const RectF_s0095_b310* r);
};
extern DispEntry* __cdecl AllocDisplayListEntry_s0095_b310();                   // 0x956ff0
extern u32 g_tbl_1440748[29];
extern void __cdecl MergePending(Node* lD, Node* L1, Node* L2);      // 0x958570
#define WB(w, o)   (*(u8*)((u8*)(w) + (o)))
#define WD(w, o)   (*(u32*)((u8*)(w) + (o)))
static inline void PopFront(Node* a) {
    Node* n = a->next;
    n->next->prev = a;
    a->next = n->next;
    if (n != a) { n->prev = 0; n->next = 0; }
}
static inline void PopBack(Node* a) {
    Node* n = a->prev;
    n->prev->next = a;
    a->prev = n->prev;
    if (n != a) { n->prev = 0; n->next = 0; }
}
static inline void PushBack(Node* a, Node* n) {
    n->prev = a->prev;
    n->next = a;
    a->prev = n;
    n->prev->next = n;
}
static inline void AppendAll(Node* dst, Node* src) {
    Node* first = src->next;
    Node* last = src->prev;
    Node* tail = dst->prev;
    tail->next = first;
    first->prev = tail;
    last->next = dst;
    dst->prev = last;
    src->prev = src;
    src->next = src;
}
static inline void SwapLists(Node* a, Node* b) {
    Node* an = a->next; Node* ap = a->prev;
    a->next = b->next; a->prev = b->prev;
    b->next = an; b->prev = ap;
    if (a->next == b) { a->prev = a; a->next = a; }
    else { a->prev->next = a; a->next->prev = a; }
    if (b->next == a) { b->prev = b; b->next = b; }
    else { b->prev->next = b; b->next->prev = b; }
}
static inline void ClearLinks(Node* a) {
    for (Node* n = a->next; n != a; ) { Node* nx = n->next; n->prev = 0; n->next = 0; n = nx; }
}
// ---- items of slice s0095b310 end

// @ 0x00957d40
void W::PostAPC(int a, void* b)
{
    APCData d;
    d.tag = 0x74d2e9;
    if (b) ((VTab*)b)->v00();
    d.p2 = a;
    d.p3 = b;
    ((VTab*)this)->v18(0, 0, &d);
}

// @ 0x00957d90
void W::d90(void* a)
{
    ((VTab*)this)->v18(0, 0, a);
}

// @ 0x00957db0
char* W::db0(int idx)
{
    char* p = (char*)PTR(this, 0x68c + idx * 0x28);
    if (p) return p + 4;
    return 0;
}

// @ 0x00957dd0
unsigned W::dd0(void* target)
{
    unsigned result = 0;
    unsigned bit = 1;
    char* p = B(this) + 0x6b4;
    int n = 2;
    do {
        for (int k = 0; k < 5; k++) {
            void* f = *(void**)(p + k * 0x28 - 0x28);
            void* v = f ? (char*)f + 4 : 0;
            if (v == target) result |= bit;
            bit += bit;
        }
        p += 0xc8;
    } while (--n);
    return result;
}

// @ 0x00957e70
char* W::e70(int idx)
{
    char* p = (char*)PTR(this, 0x694 + idx * 0x28);
    if (p) return p + 4;
    return 0;
}

// @ 0x00957e90
void W::e90(int idx, void* arg)
{
    void* stored = PTR(this, 0x694 + idx * 0x28);
    void* v = arg ? (char*)arg - 4 : 0;
    if (stored == v) {
        ((VTab*)this)->v58(idx, 0);
    }
}

// @ 0x00957ed0
void W::ed0(unsigned mask, char set)
{
    U32(this, 0xd0) = U32(this, 0xd0) & ~mask;
    if (set) U32(this, 0xd0) = U32(this, 0xd0) | mask;
}

// @ 0x00957f50
void* __fastcall Fn00957f50(void* self)
{
    void* p = PTR(self, 4);
    if (p) return (char*)p + 4;
    return 0;
}

// @ 0x00957fa0
void __fastcall Fn00957fa0(void* self)
{
    void* n = PTR(self, 0x6b4);
    if (n != 0) {
        int v;
        do {
            v = I32(n, 0xa8);
            if (v != 0) break;
            n = PTR(n, 0x38);
        } while (n != 0);
        if (I32(self, 0xc4) != v) {
            I32(self, 0xc4) = v;
            void* o = PTR(self, 0xb8);
            if (o) ((VTab*)o)->v0c(v);
        }
    }
}

// @ 0x00957ff0
void EA::UTFWin::WindowMgr::SetCanvasCallback(EA::UTFWin::ICanvasCallback * obj)
{
    void* old = PTR(this, 0xb8);
    if (obj != old) {
        if (obj) ((VTab*)obj)->v00();
        PTR(this, 0xb8) = obj;
        if (old) ((VTab*)old)->v04();
    }
    if (obj && I32(this, 0xc4) != 0) {
        ((VTab*)PTR(this, 0xb8))->v0c(I32(this, 0xc4));
    }
}

// @ 0x00958070
void W::x070(float* pt)
{
    void* o = PTR(this, 0xb8);
    if (o) {
        int a = _mm_cvtss_si32(_mm_load_ss(&pt[0]));
        int b = _mm_cvtss_si32(_mm_load_ss(&pt[1]));
        ((VTab*)o)->v10(a, b);
    }
}

// @ 0x009580b0
void W::x0b0(void* target)
{
    void* n = PTR(this, 0x6b4);
    if (n != 0) {
        do {
            if (n == target) { Fn00957fa0(this); return; }
            n = *(void**)((char*)n + 0x38);
        } while (n != 0);
    }
}

// @ 0x009580e0
void W::x0e0(char* node)
{
    if (I32(node, 0x24) == 0 && I8(this, 0x25) == 0) {
        int edx = I32(this, 0x1c);
        char* base = B(this) + 0x18;
        node += 0x20;
        *(int*)(node + 4) = edx;
        *(char**)node = base;
        *(char**)(base + 4) = node;
        char* c = *(char**)(node + 4);
        *(char**)c = node;
    }
}

// @ 0x00958110
void __fastcall Fn00958110(void* self)
{
    if (I8(self, 0x25) != 0) return;
    char* H = B(self) + 0x18;
    I8(self, 0x25) = 1;
    while (*(char**)(H + 4) != H) {
        char* edx = *(char**)(H + 4);
        char* edi = *(char**)(edx + 4);
        char* esi = *(char**)(B(self) + 0x1c);
        *(char**)edi = H;
        edi = *(char**)(H + 4);
        edi = *(char**)(edi + 4);
        *(char**)(H + 4) = edi;
        if (edx != H) {
            *(void**)(edx + 4) = 0;
            *(void**)edx = 0;
        }
        *(void**)(esi + 4) = 0;
    }
}

// @ 0x00958150
void W::ComputeClip(float* out, void* node)
{
    float xmin = -10000.0f, ymin = -10000.0f, xmax = 10000.0f, ymax = 10000.0f;
    for (; node != 0; node = PTR(node, 0x38)) {
        if ((U32(node, 0x2c) & 0x400) != 0) {
            float w = F32(node, 0x90) - F32(node, 0x88);
            float h = F32(node, 0x94) - F32(node, 0x8c);
            float pxmin, pymin, pxmax, pymax;
            if (w == 0.0f || h == 0.0f) {
                pxmin = pymin = pxmax = pymax = 0.0f;
            } else {
                void* M = B(node) + 0x14c;
                if (I32(node, 0x18c) < 2) {
                    float i[4] = {0, 0, 0, 0}, o[4];
                    ((Ext*)M)->tp3(o, i);
                    float i2[4] = {w, h, 0, 0}, o2[4];
                    ((Ext*)M)->tp3(o2, i2);
                    pxmin = o[0] < o2[0] ? o[0] : o2[0];
                    pymin = o[1] < o2[1] ? o[1] : o2[1];
                    pxmax = o[0] > o2[0] ? o[0] : o2[0];
                    pymax = o[1] > o2[1] ? o[1] : o2[1];
                } else {
                    float p[4] = {0, 0, 0, 0}, a[4], b[4], c[4], d[4];
                    ((Ext*)M)->tp4(a, p);
                    p[0] = w; p[1] = h; p[2] = 0; p[3] = 0; ((Ext*)M)->tp4(b, p);
                    p[0] = w; p[1] = 0; ((Ext*)M)->tp4(c, p);
                    p[0] = 0; p[1] = h; ((Ext*)M)->tp4(d, p);
                    pxmin = a[0]; if (b[0] < pxmin) pxmin = b[0]; if (c[0] < pxmin) pxmin = c[0]; if (d[0] < pxmin) pxmin = d[0];
                    pymin = a[1]; if (b[1] < pymin) pymin = b[1]; if (c[1] < pymin) pymin = c[1]; if (d[1] < pymin) pymin = d[1];
                    pxmax = a[0]; if (b[0] > pxmax) pxmax = b[0]; if (c[0] > pxmax) pxmax = c[0]; if (d[0] > pxmax) pxmax = d[0];
                    pymax = a[1]; if (b[1] > pymax) pymax = b[1]; if (c[1] > pymax) pymax = c[1]; if (d[1] > pymax) pymax = d[1];
                }
            }
            if (xmax <= pxmin || pxmax <= xmin || ymax <= pymin || pymax <= ymin) {
                xmin = 0; ymin = 0; xmax = 0; ymax = 0;
            } else {
                if (xmin < pxmin) xmin = pxmin;
                if (ymin < pymin) ymin = pymin;
                if (pxmax < xmax) xmax = pxmax;
                if (pymax < ymax) ymax = pymax;
            }
        }
        if ((U8(node, 0x30) & 2) == 0) break;
    }
    out[0] = xmin;
    out[1] = ymin;
    out[2] = xmax;
    out[3] = ymax;
}

// @ 0x00958500
char W::x500(void* obj, int a)
{
    char result = 0;
    if (obj) ((VTab*)obj)->v00();
    void* saved = PTR(this, 0x688);
    PTR(this, 0x688) = 0;
    if (obj) {
        if (((VTab*)this)->v74(obj, a)) {
            ((VTab*)this)->v78(obj, 0);
            result = 1;
        }
    }
    PTR(this, 0x688) = saved;
    if (obj) ((VTab*)obj)->v04();
    return result;
}

// @ 0x00958570
void __cdecl Fn00958570(void* pa, int* b, int* c)
{
    int param_1 = (int)pa;
    int zero = 0;
    while ((int*)b[1] != b) {
        int* piVar1 = (int*)*b;
        *(int**)(*piVar1 + 4) = b;
        *b = *(int*)*b;
        if (piVar1 != b) {
            piVar1[1] = zero;
            *piVar1 = zero;
        }
        int* piVar2 = (int*)piVar1[2];
        int iVar3;
        if (piVar1[7] == zero && piVar1[5] == zero) {
            iVar3 = *piVar2;
            if (iVar3 != param_1 && *(unsigned short*)(piVar2 + 4) < *(unsigned short*)(iVar3 + 0x12)) {
                *(unsigned short*)(iVar3 + 0x12) = *(unsigned short*)(piVar2 + 4);
            }
            int* piVar4 = (int*)piVar2[1];
            iVar3 = *piVar2;
            *piVar4 = iVar3;
            *(int**)(iVar3 + 4) = piVar4;
            *piVar2 = zero;
            piVar2[1] = zero;
            piVar2[1] = c[1];
            *piVar2 = (int)c;
            c[1] = (int)piVar2;
            *(int**)piVar2[1] = piVar2;
            piVar1[1] = c[1];
            *piVar1 = (int)c;
            c[1] = (int)piVar1;
            *(int**)piVar1[1] = piVar1;
        } else {
            *(char*)((int)piVar1 + 0xd) = *(char*)((int)piVar2 + 0xd);
            piVar1[2] = piVar2[2];
            *(char*)((int)piVar2 + 0xd) = (char)zero;
            int* puVar5 = (int*)piVar2[1];
            piVar2[1] = (int)piVar1;
            *puVar5 = (int)piVar1;
            piVar1[1] = (int)puVar5;
            *piVar1 = (int)piVar2;
            if (c != piVar2) {
                iVar3 = *piVar2;
                piVar1 = (int*)piVar2[1];
                *(int**)(iVar3 + 4) = piVar1;
                *piVar1 = iVar3;
                puVar5 = (int*)c[1];
                *puVar5 = (int)piVar2;
                c[1] = (int)piVar2;
                piVar2[1] = (int)puVar5;
                *piVar2 = (int)c;
            }
        }
    }
}

// @ 0x00958640
void __fastcall DumpDisplayList(void* self)
{
    if (I8(self, 0x58) == 0) return;
    I8(self, 0x58) = 0;
    if (I8(self, 0x59) != 0) {
        Fn00958570(B(self) + 0xa0, (int*)(B(self) + 0x5c), (int*)(B(self) + 0x64));
        return;
    }
    char* piVar1 = B(self) + 0x5c;
    ((Ext*)(B(self) + 0xa0))->Splice1(piVar1);
    for (char* puVar2 = *(char**)(B(self) + 0xa0); puVar2 != B(self) + 0xa0; puVar2 = *(char**)puVar2) {
        if (*(void**)(puVar2 + 8) != 0 && *(char*)(puVar2 + 0xc) == 0) {
            ((Ext*)(*(char**)(puVar2 + 8) + 0x18))->ba90(puVar2 + 0x18);
        }
        *(void**)(puVar2 + 8) = 0;
        *(char*)(puVar2 + 0xd) = 1;
        *(char*)(puVar2 + 0xc) = 0;
    }
    char* piVar3 = *(char**)(piVar1 + 0);
    if (piVar3 != piVar1) {
        char* piVar4 = *(char**)(B(self) + 0x68);
        char* piVar5 = *(char**)(B(self) + 0x60);
        *(char**)piVar4 = piVar3;
        *(char**)(piVar3 + 4) = piVar4;
        *(char**)piVar5 = B(self) + 0x64;
        *(char**)(B(self) + 0x68) = piVar5;
        *(char**)piVar1 = piVar1;
        *(char**)(B(self) + 0x60) = piVar1;
    }
}

// @ 0x009586f0
void W::Plot(int param)
{
    char local[0x3c34];
    ((Ext*)(local + 0xc))->bb80(local + 0xc);
    ((Ext*)(B(this) + 0x28))->Lock((const void*)0x1440688);
    ProcessPendingTextures();
    DumpDisplayList(this);
    Mutex_Unlock(B(this) + 0x28);
    ((Ext*)(B(this) + 0x70))->Lock((const void*)0x1440688);
    ((Ext*)(local + 0x10))->bd60(B(this) + 0xa0, (void*)param);
    Mutex_Unlock(B(this) + 0x70);
    ((Ext*)(local + 0x84))->r2db_dtor();
    ((Ext*)(local + 0x60))->iba0();
}

// @ 0x00958780
void __fastcall DebugDumpDisplayList(void* self)
{
    ((Ext*)(B(self) + 0x28))->Lock((const void*)0x1440688);
    char pending = I8(self, 0x58);
    if (pending == 0) {
        Mutex_Unlock(B(self) + 0x28);
        return;
    }
    ((Ext*)(B(self) + 0x70))->Lock((const void*)0x1440688);
    DumpDisplayList(self);
    Mutex_Unlock(B(self) + 0x70);
    Mutex_Unlock(B(self) + 0x28);
}

// @ 0x009587d0
void W::m7d0(char* node)
{
    void** piVar2 = (void**)(*(char**)(B(this) + 0x20));
    if ((char*)piVar2 == node + 0x18) {
        I8(this, 0x24) = 1;
        void** piVar1 = (void**)piVar2[1];
        void*  iVar3 = *piVar2;
        *piVar1 = iVar3;
        *(void**)((char*)iVar3 + 4) = piVar1;
        *piVar2 = 0;
        piVar2[1] = 0;
        *(void**)(B(this) + 0x20) = iVar3;
        *(void**)(node + 0x1c) = 0;
        return;
    }
    void* a = *(void**)(node + 0x1c);
    void* c = *(void**)(node + 0x18);
    *(void**)a = c;
    *(void**)((char*)c + 4) = a;
    *(void**)(node + 0x18) = 0;
    *(void**)(node + 0x1c) = 0;
    *(void**)(node + 0x1c) = 0;
}

// @ 0x00958820
void W::m820(char* node)
{
    if ((U8(node, 0x30) & 0x14) == 0) {
        U8(node, 0x30) = U8(node, 0x30) | 0x10;
        if (I32(node, 0x78) == 0) {
            Fn00958110(this);
            return;
        }
        char* base = B(this) + 8;
        void** p = (void**)(node + 0x10);
        void* t = *(void**)(base + 4);
        p[1] = t;
        *p = base;
        *(void**)(base + 4) = p;
        void** c = (void**)p[1];
        *c = p;
    }
}

// @ 0x00958860
void W::m860(char* node)
{
    if ((U8(node, 0x30) & 0x40) == 0) {
        if (I32(node, 0x78) != 0 && I32(node, 0x24) == 0 && I8(this, 0x25) == 0) {
            char* base = B(this) + 0x18;
            void** p = (void**)(node + 0x20);
            void* t = *(void**)(base + 4);
            p[1] = t;
            *p = base;
            *(void**)(base + 4) = p;
            void** c = (void**)p[1];
            *c = p;
        }
        char* iVar2 = *(char**)(node + 0x38);
        U8(node, 0x30) = U8(node, 0x30) | 0x40;
        for (; iVar2 != 0; iVar2 = *(char**)(iVar2 + 0x38)) {
            if (I8(iVar2, 0x30) < 0) break;
            U8(iVar2, 0x30) = U8(iVar2, 0x30) | 0x80;
        }
    }
}

// @ 0x009588c0
void W::m8c0(char* node)
{
    if ((U8(node, 0x30) & 0x20) == 0) {
        if (I32(node, 0x78) != 0 && I32(node, 0x24) == 0 && I8(this, 0x25) == 0) {
            char* base = B(this) + 0x18;
            void** p = (void**)(node + 0x20);
            void* t = *(void**)(base + 4);
            p[1] = t;
            *p = base;
            *(void**)(base + 4) = p;
            void** c = (void**)p[1];
            *c = p;
        }
        char* iVar2 = *(char**)(node + 0x38);
        U8(node, 0x30) = U8(node, 0x30) | 0x20;
        for (; iVar2 != 0; iVar2 = *(char**)(iVar2 + 0x38)) {
            if (I8(iVar2, 0x30) < 0) break;
            U8(iVar2, 0x30) = U8(iVar2, 0x30) | 0x80;
        }
    }
}

// @ 0x00958920
char __cdecl Fn00958920(int* self, void* p2, char* p3, char p4, unsigned p5)
{
    char cVar4 = 0;
    ((VTab*)self)->v00();
    self[0x1d] = self[0x1d] + 1;
    int* piVar1 = *(int**)(p3 + 0xc);
    for (;;) {
        if (piVar1 == self + 0x19) {
            self[0x1d] = self[0x1d] - 1;
            if (self[0x1d] == 0) ((Ext*)self)->ea0();
            if (p4 == 0 && cVar4 == 0) {
                cVar4 = ((VTab*)self)->v20(p2);
            }
            ((VTab*)self)->v04();
            return cVar4;
        }
        piVar1 = (int*)piVar1[2];
        if (piVar1) ((VTab*)piVar1)->v00();
        unsigned uVar2 = *(unsigned*)(*(int*)(p3 + 0xc) + 0xc);
        *(int*)(p3 + 0xc) = **(int**)(p3 + 0xc);
        if (((p5 & uVar2) != 0) && ((char)((VS6*)piVar1)->f((void*)(self + 1), p2) != 0)) {
            cVar4 = 1;
            if (piVar1) ((VTab*)piVar1)->v04();
            self[0x1d] = self[0x1d] - 1;
            if (self[0x1d] == 0) ((Ext*)self)->ea0();
            if (p4 == 0 && cVar4 == 0) {
                cVar4 = ((VTab*)self)->v20(p2);
            }
            ((VTab*)self)->v04();
            return cVar4;
        }
        if (piVar1) ((VTab*)piVar1)->v04();
        piVar1 = *(int**)(p3 + 0xc);
    }
}

// @ 0x009589f0
void W::DispatchMsgToWindow(int p2, char* p3, int p4)
{
    void* uVar1 = ((Ext*)this)->ba70(*(void**)(p3 + 8));
    MsgNode local;
    local.f8 = I32(p2, 100);
    local.f0 = PTR(this, 0x688);
    local.fc = p2;
    local.f10 = (char)p4;
    if (local.f0 != 0 && I32(local.f0, 8) == p2 && I8(local.f0, 0x10) == local.f10) {
        local.f8 = I32(local.f0, 0xc);
    }
    PTR(this, 0x688) = &local;
    Fn00958920((int*)p2, p3, (char*)&local, local.f10, (unsigned)uVar1);
    PTR(this, 0x688) = local.f0;
}

// @ 0x00958a70
Win* __thiscall WM::HitTest(Win* w, V2* pt, const V2& p3, V2* outLocal)
{
    if (!(w->flags & 1))
        return 0;
    Node* head = &w->children;
    Node* n = head->next;
    if (!(w->flags & 0x1000)) {
        for (; n != head; n = n->next) {
            Win* r = HitTest(NodeToWin(n), pt, p3, outLocal);
            if (r)
                return r;
        }
    }
    if (w->flags & 0x10)
        return 0;
    V2 loc;
    IWin* iw = w;
    if (!iw->vHit(*pt, &loc))
        return 0;
    if (!iw->vHitLocal(loc))
        return 0;
    if (outLocal) { outLocal->x = loc.x; outLocal->y = loc.y; }
    return w;
}

// @ 0x00958b60
void __thiscall WM::MarkTree(Win* w)
{
    Node* head = &w->children;
    Node* n = head->next;
    w->b30 = (w->b30 & 0xef) | 8;
    w->f14 = 0;
    w->f78 = 0;
    for (; n != head; n = n->next)
        MarkTree(NodeToWin(n));
}

// @ 0x00958bb0
void __thiscall WM::DestroyDisplayList(Node* head)
{
    for (Node* e = head->next; e != head; e = e->next) {
        u8* ep = (u8*)e;
        Chunk* c = (Chunk*)(ep + 0x18);
        Chunk* last;
        for (;;) {
            last = c;
            int cnt = c->count;
            for (int i = 0; i < cnt; i++) {
                IRel* o = c->items[i].obj;
                if (o) o->Release();
            }
            if (!c->next) break;
            c = c->next;
        }
        if (*(u32*)(ep + 0x18))
            FreeRenderableListChunks(*(void**)(ep + 0x18), last);
        if (*(u32*)(ep + 0x14)) {
            if (*(u32*)(ep + 0xa0)) (*(IObj**)(ep + 0x14))->Destroy(*(void**)(ep + 0xa0));
            if (*(u32*)(ep + 0xfc)) (*(IObj**)(ep + 0x14))->Destroy(*(void**)(ep + 0xfc));
            (*(IObj**)(ep + 0x14))->Release();
        }
    }
    FreeDisplayListEntries(head);
}

// @ 0x00958c60
bool __thiscall WM::IsFocusWindow(IWin* w)
{
    if (w) {
        if (cur == w)
            return true;
        Node* head = &focusList.anchor;
        for (Node* n = head->next; n != head; n = n->next) {
            if (((IWin**)n)[2] == w)
                return true;
        }
    }
    return false;
}

// @ 0x00958ca0
Iter __thiscall MsgList::EraseRange(Iter first, Iter last)
{
    while (first.n != last.n) {
        Node* nx = first.n->next;
        Node* n = nx->prev;
        n->prev->next = n->next;
        n->next->prev = n->prev;
        alloc->Free(n, 0x24);
        first.n = nx;
    }
    return last;
}

// @ 0x00958cf0
WM::WM()
: mainWin(0), tickIter(&lB.n), f24(0), f25(0), mxA(0, 1), f58(0), f59(0), mxB(0, 1),
      fa8(0.0f), fac(0.0f), fb0(0.0f), fb4(0.0f), fb8(0), mx(0.0f), my(0.0f), fc4(0), hook(0),
      fcc(1), fd0(0), q0(EAlloc(GetAlloc())), q1(EAlloc(GetAlloc())), q2(EAlloc(GetAlloc())), q3(EAlloc(GetAlloc())), q4(EAlloc(GetAlloc())), f124(0), ts(0), mxC(0, 1), f688(0), focusList(EAlloc(GetAlloc())), cur(0), curCb(0), f834(0)
{
    W_s0095_8a70(0x68c) = 0;
    W_s0095_8a70(0x6b4) = 0;
    W_s0095_8a70(0x690) = 0;
    W_s0095_8a70(0x694) = 0;
    W_s0095_8a70(0x6a0) = 0;
    W_s0095_8a70(0x6b8) = 0;
    W_s0095_8a70(0x6bc) = 0;
    W_s0095_8a70(0x6c8) = 0;
    W_s0095_8a70(0x6dc) = 0;
    W_s0095_8a70(0x6e0) = 0;
    W_s0095_8a70(0x6e4) = 0;
    W_s0095_8a70(0x6f0) = 0;
    W_s0095_8a70(0x704) = 0;
    W_s0095_8a70(0x708) = 0;
    W_s0095_8a70(0x70c) = 0;
    W_s0095_8a70(0x718) = 0;
    W_s0095_8a70(0x72c) = 0;
    W_s0095_8a70(0x730) = 0;
    W_s0095_8a70(0x734) = 0;
    W_s0095_8a70(0x740) = 0;
    W_s0095_8a70(0x754) = 0;
    W_s0095_8a70(0x758) = 0;
    W_s0095_8a70(0x75c) = 0;
    W_s0095_8a70(0x768) = 0;
    W_s0095_8a70(0x77c) = 0;
    W_s0095_8a70(0x780) = 0;
    W_s0095_8a70(0x784) = 0;
    W_s0095_8a70(0x790) = 0;
    W_s0095_8a70(0x7a4) = 0;
    W_s0095_8a70(0x7a8) = 0;
    W_s0095_8a70(0x7ac) = 0;
    W_s0095_8a70(0x7b8) = 0;
    W_s0095_8a70(0x7cc) = 0;
    W_s0095_8a70(0x7d0) = 0;
    W_s0095_8a70(0x7d4) = 0;
    W_s0095_8a70(0x7e0) = 0;
    W_s0095_8a70(0x7f4) = 0;
    W_s0095_8a70(0x7f8) = 0;
    W_s0095_8a70(0x7fc) = 0;
    W_s0095_8a70(0x808) = 0;
}

// @ 0x00958fa0
bool __thiscall WM::SendModifiedMsg(IWin* w, IWin* src, Msg* m)
{
    WM* self = this;
    Win* t = static_cast<Win*>(w);
    Msg msg = *m;
    msg.src = src;
    IWin* wi = t;
    msg.dst = wi;
    if (self->hook)
        self->hook->Notify(2, 0, &msg);
    bool r = false;
    if (self->DispatchMsgToWindow(t, &msg, 0))
        r = true;
    if (self->hook)
        self->hook->Notify(r ? 4 : 5, 0, &msg);
    return r;
}

// @ 0x00959230
IWin* __thiscall WM::FindWindowAt(const V2* pt)
{
    if (!mainWin)
        return 0;
    V2 zero(0.0f, 0.0f);
    float q[4];
    q[0] = g_13eb1bc; q[1] = pt->x; q[2] = pt->y; q[3] = 0.0f;
    Win* hit = HitTest(mainWin, (V2*)&q[1], zero, 0);
    if (hit)
        return hit;
    return 0;
}

// @ 0x009594b0
bool __thiscall WM::PopFocus(IWin* w, IWin* arg)
{
    IWin* oldCur;
    ICb* oldCb;
    if (w == 0)
        return false;
    if (cur == w) {
        oldCur = cur;
        oldCb = curCb;
        Node* head = &focusList.anchor;
        if (head->next != head) {
            Node* node = head->next;
            cur = ((IWin**)node)[2];
            curCb = ((ICb**)node)[3];
            if (cur->vGetParent()) {
                cur->vSetFlags(0x40, 1);
                cur->vGetParent()->vSetOwner(cur);
                SetFocus(0, cur);
            }
            node = head->next;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            focusList.alloc->Free(node, 0x10);
        } else {
            cur = 0;
            curCb = 0;
        }
    } else {
        Node* head = &focusList.anchor;
        Node* node = head->next;
        if (node == head)
            return false;
        while (((IWin**)node)[2] != w) {
            node = node->next;
            if (node == head)
                return false;
        }
        oldCur = ((IWin**)node)[2];
        oldCb = ((ICb**)node)[3];
        node = node->next->prev;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        focusList.alloc->Free(node, 0x10);
    }
    if (oldCur == 0)
        return false;
    if (oldCb)
        oldCb->Call(oldCur, arg);
    return true;
}

// @ 0x009595e0
void __thiscall MsgList::InsertRange(Node* where, Iter first, Iter last, int tag)
{
    if (first.n == last.n)
        return;
    do {
        const Msg& sm = ((MsgNode_s0095_8a70*)first.n)->msg;
        MsgNode_s0095_8a70* n = (MsgNode_s0095_8a70*)alloc->Alloc(0x24, 0, allocFlags);
        new (&n->msg) Msg(sm);
        n->link.next = where;
        n->link.prev = where->prev;
        where->prev->next = &n->link;
        where->prev = &n->link;
        first.n = first.n->next;
    } while (first.n != last.n);
}

// @ 0x00959b70
int W_s0095_9780::b70(int p2, int p3)
{
    p3 = p3 ? p3 - 4 : 0;
    int* piVar1 = (int*)(B(this) + p2 * 0x28 + 0x68c);
    if (p3 != 0) {
        void* obj = (void*)(p3 + 4);
        uchar r = ((uchar(__thiscall*)(void*))*(void**)((char*)*(void**)obj + 0x28))(obj);
        if ((r & 1) == 0)
            return 0;
        if ((r & 2) == 0 && p2 != 1)
            return 0;
        if (TH(p3)->AllDescendants(p2 == 1) == 0)
            return 0;
    }
    if (piVar1[2] != 0) {
        piVar1[1] = p3;
        return 1;
    }
    if (p3 != piVar1[0]) {
        int ev[7];
        if (piVar1[5] != 0) {
            memcpy(ev, piVar1 + 3, 28);
            piVar1[5] = 0;
            Fn00959780(ev, 0);
        }
        ev[3] = p2;
        ev[6] = p3 ? p3 + 4 : 0;
        int iVar4 = piVar1[0] ? piVar1[0] + 4 : 0;
        piVar1[0] = p3;
        piVar1[1] = p3;
        if (iVar4 != 0) {
            ev[2] = 10;
            GV(0, iVar4, ev, 0, 0);
            ev[2] = 0x1c;
            ev[6] = iVar4;
            GV(iVar4, iVar4, ev, 1, 0);
            if (piVar1[0] != p3)
                return 1;
        }
        piVar1[0] = p3;
        piVar1[1] = p3;
        TH(this)->Fn00957fa0();
        if (p3 != 0) {
            p3 = p3 + 4;
            ev[2] = 10;
            ev[6] = p3;
            GV(0, p3, ev, 0, 0);
            ev[2] = 0x1b;
            GV(p3, p3, ev, 1, 0);
        }
    }
    return 1;
}

// @ 0x00959cf0
void W_s0095_9780::cf0(int p2, int p3)
{
    p3 = p3 ? p3 - 4 : 0;
    int* piVar1 = (int*)(B(this) + p2 * 0x28 + 0x68c);
    if (p3 != piVar1[2]) {
        int ev[7];
        if (piVar1[5] != 0) {
            memcpy(ev, piVar1 + 3, 28);
            piVar1[5] = 0;
            Fn00959780(ev, 0);
        }
        ev[2] = 0xb;
        ev[3] = p2;
        ev[6] = p3 ? p3 + 4 : 0;
        int iVar2 = piVar1[2];
        piVar1[2] = 0;
        if (iVar2 != 0) {
            GV(0, iVar2 + 4, ev, 0, 0);
        }
        if (piVar1[2] == 0) {
            if (p3 == 0) {
                int t = piVar1[1] ? piVar1[1] + 4 : 0;
                ((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, p2, t);
            } else {
                ((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, p2, p3 + 4);
                if (piVar1[2] == 0 && piVar1[0] == p3) {
                    piVar1[2] = p3;
                    GV(0, p3 + 4, ev, 0, 0);
                    return;
                }
            }
        }
    }
}

// @ 0x00959e00
void W_s0095_9780::DetachWindow(void* win)
{
    int ev[7];
    ev[2] = 0x12;
    void* p = win ? (void*)((int)B(win) + 4) : 0;
    GV((int)p, (int)p, ev, 0, 0);

    void* anchor0 = B(win) + 0x3c;
    for (void** pu = (void**)PTR(win, 0x3c); pu != (void**)anchor0; pu = (void**)*pu) {
        void* q = pu ? (void*)((int)pu - 8) : 0;
        DetachWindow(q);
    }

    int iVar13 = 0;
    char* pSVar = B(this) + 0x690;
    do {
        if (I32(pSVar, 4) == (int)win) {
            ((int(__thiscall*)(void*, int, int))VFP(0x5c))(this, iVar13, (int)B(win) + 4);
        }
        if (I32(pSVar, 0) == (int)win) {
            int mId = I32(win, 0x38);
            int iVar10 = mId ? mId + 4 : 0;
            char c = (char)((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, iVar13, iVar10);
            if (c == 0) {
                int t = (int)TH(mId)->Fn0095fc00(0);
                iVar10 = t ? t + 4 : 0;
                ((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, iVar13, iVar10);
            }
        }
        iVar13++;
        pSVar += 0x28;
    } while (iVar13 < 10);

    TH(B(this) + 0x658)->Lock_((const void*)0x1440688);
    void* head = PTR(this, 0xd4);
    void* anchor1 = B(this) + 0xd4;
    while (head != anchor1) {
        void* w4 = (void*)((int)B(win) + 4);
        if (I32(head, 8) == (int)w4 || I32(head, 0xc) == (int)w4) {
            void* nxt = PTR(head, 0);
            void* eax = PTR(nxt, 4);
            void* c1 = PTR(eax, 4);
            void* d1 = PTR(eax, 0);
            I32(c1, 0) = (int)d1;
            void* c2 = PTR(eax, 0);
            void* d2 = PTR(eax, 4);
            I32(c2, 4) = (int)d2;
            void* alloc = PTR(this, 0xdc);
            ((void(__thiscall*)(void*, void*, int))*(void**)((char*)*(void**)alloc + 0xc))
                (alloc, eax, 0x24);
            head = nxt;
        } else {
            head = PTR(head, 0);
        }
    }
    TH(B(this) + 0x658)->Unlock_();

    if (I32(win, 0x1c) != 0) {
        void* node = B(win) + 0x18;
        void* it = PTR(this, 0x20);
        if (it == node) {
            U8(this, 0x24) = 1;
            void* nxt = PTR(node, 0);
            void* prv = PTR(node, 4);
            I32(prv, 0) = (int)nxt;
            I32(nxt, 4) = (int)prv;
            I32(node, 0) = 0;
            I32(node, 4) = 0;
            PTR(this, 0x20) = nxt;
        } else {
            void* prv = PTR(node, 4);
            void* nxt = PTR(node, 0);
            I32(prv, 0) = (int)nxt;
            I32(nxt, 4) = (int)prv;
            I32(node, 0) = 0;
            I32(node, 4) = 0;
        }
        I32(win, 0x1c) = 0;
    }
    if (I32(win, 0x24) != 0) {
        void* prv = PTR(win, 0x24);
        void* nxt = PTR(win, 0x20);
        I32(prv, 0) = (int)nxt;
        I32(nxt, 4) = (int)prv;
        I32(win, 0x20) = 0;
        I32(win, 0x24) = 0;
    }
    if (I32(win, 0x14) != 0) {
        void* prv = PTR(win, 0x14);
        void* nxt = PTR(win, 0x10);
        I32(prv, 0) = (int)nxt;
        I32(nxt, 4) = (int)prv;
        I32(win, 0x10) = 0;
        I32(win, 0x14) = 0;
    }
    if (PTR(win, 0x78) != 0 && U8(this, 0x25) == 0) {
        char* anchor = B(this) + 0x18;
        U8(this, 0x25) = 1;
        while (PTR(anchor, 4) != anchor) {
            void* N = PTR(anchor, 4);
            void* P = PTR(N, 4);
            I32(P, 0) = (int)anchor;
            PTR(anchor, 4) = P;
            if (N != anchor) {
                I32(N, 4) = 0;
                I32(N, 0) = 0;
            }
        }
    }
    I32(win, 0x78) = 0;
    I32(win, 0x34) = 0;
}

// @ 0x00959fe0
void W_s0095_9780::fe0(int win)
{
    float* dst = (float*)(B(win) + 0x88);
    dst[0] = F32(win, 0x98);
    int ev[7];
    ev[2] = 0x10;
    dst[1] = F32(win, 0x9c);
    ev[6] = (int)dst;
    dst[2] = F32(win, 0xa0);
    dst[3] = F32(win, 0xa4);
    void* b = win ? (void*)(B(win) + 4) : 0;
    GV((int)b, (int)b, ev, 0, 0);
    float* ft = (float*)ev;
    ft[0] = (float)iat_floor((double)F32(win, 0x88));
    ft[1] = (float)iat_floor((double)F32(win, 0x8c));
    ft[2] = (float)iat_floor((double)F32(win, 0x90));
    float t3 = (float)iat_floor((double)F32(win, 0x94));
    dst[0] = ft[0];
    dst[1] = ft[1];
    dst[2] = ft[2];
    dst[3] = t3;
}

// @ 0x0095a0b0
void W_s0095_9780::a0b0(int p2, int* p3)
{
    int saved = I32(this, 0x688);
    I32(this, 0x688) = 0;
    int local[7];
    memcpy(local, p3, 28);
    local[0] = p2 ? p2 + 4 : 0;
    int v = I32(p2, 0x38);
    local[1] = v ? v + 4 : 0;
    int* p = (int*)PTR(this, 0xc8);
    if (p != 0) {
        ((int(__thiscall*)(void*, int, int, void*))*(void**)((char*)*(void**)p + 0xc))
            (p, 3, 0, local);
    }
    TH(this)->Fn009592e0(local, 1);
    I32(this, 0x688) = saved;
}

// @ 0x0095a140
void W_s0095_9780::UpdateRenderState(int win, char p3, char p4)
{
    char c1 = 0, c2 = 0;
    if ((U8(win, 0x30) & 0x20) != 0) {
        U8(win, 0x30) = (uchar)(U8(win, 0x30) & 0xdf);
        TH(win + 0xc4)->Fn0095e7a0();
        int ev[7];
        ev[2] = 0x15;
        ev[6] = win + 0xc4;
        GV(0, win + 4, ev, 0, 0);
        memcpy((void*)(win + 0x108), (void*)(win + 0xc4), 0x44);
        TH(win + 0x108)->Fn0095f620();
        c1 = 1;
    }
    if ((U8(win, 0x30) & 0x40) != 0) {
        U8(win, 0x30) = (uchar)(U8(win, 0x30) & 0xbf);
        c2 = 1;
    }
    if (c1 != 0) {
        float f0 = (F32(win, 0x90) + F32(win, 0x88)) * 0.5f;
        float f1 = (F32(win, 0x94) + F32(win, 0x8c)) * 0.5f;
        memcpy((void*)(win + 0x14c), (void*)(win + 0xc4), 0x44);
        float lv[3];
        lv[0] = f0;
        lv[1] = f1;
        lv[2] = 0.0f;
        TH(win + 0x14c)->Fn0095e890(lv);
        int p = I32(win, 0x38);
        if (p != 0 && I32(p, 0x1e8) == 0) {
            TH(win + 0x14c)->Fn0095f860((void*)(p + 0x14c));
        }
        if (I32(win, 0x38) == 0) {
            float one[3];
            one[0] = 1.0f;
            one[1] = 1.0f;
            one[2] = 1.0f;
            float neg[3];
            neg[0] = -f0;
            neg[1] = -f1;
            neg[2] = -0.0f;
            TH(win + 0x190)->Fn0095e810(neg, one);
        } else {
            memcpy((void*)(win + 0x190), (void*)(I32(win, 0x38) + 0x190), 0x44);
            float neg[3];
            neg[0] = -f0;
            neg[1] = -f1;
            neg[2] = -0.0f;
            TH(win + 0x190)->Fn0095e890(neg);
        }
        if (I32(win, 0x148) != 4) {
            TH(win + 0x190)->Fn0095f860((void*)(win + 0x108));
        }
        float g0 = (F32(win, 0x90) - F32(win, 0x88)) * 0.5f;
        float g1 = (F32(win, 0x94) - F32(win, 0x8c)) * 0.5f;
        float gv[3];
        gv[0] = g0;
        gv[1] = g1;
        gv[2] = 0.0f;
        TH(win + 0x190)->Fn0095e890(gv);
        if (I32(win, 0x18c) == 0)
            I32(win, 0x18c) = 1;
        F32(win, 0x180) = F32(win, 0x180) - (F32(win, 0x150) * g0 + F32(win, 0x160) * g1);
        F32(win, 0x184) = F32(win, 0x184) - (F32(win, 0x154) * g0 + F32(win, 0x164) * g1);
        F32(win, 0x17c) = F32(win, 0x17c) - (F32(win, 0x14c) * g0 + F32(win, 0x15c) * g1);
        F32(win, 0x188) = F32(win, 0x188) - (F32(win, 0x158) * g0 + F32(win, 0x168) * g1);
        if (I32(win, 0x78) != 0 && I32(win, 0x24) == 0 && U8(this, 0x25) == 0) {
            void* node = B(win) + 0x20;
            I32(node, 4) = I32(this, 0x1c);
            I32(node, 0) = (int)(B(this) + 0x18);
            I32(this, 0x1c) = (int)node;
            I32(I32(node, 4), 0) = (int)node;
        }
    }
    if (p4 != 0) {
        I32(win, 0x1d4) = I32(win, 0x1d8);
        int p = I32(win, 0x38);
        if (p != 0) {
            I32(win, 0x1d4) = ModulateARGB32(I32(win, 0x1d8), I32(p, 0x1d4));
        }
        if (I32(win, 0x78) != 0 && I32(win, 0x24) == 0 && U8(this, 0x25) == 0) {
            void* node = B(win) + 0x20;
            I32(node, 4) = I32(this, 0x1c);
            I32(node, 0) = (int)(B(this) + 0x18);
            I32(this, 0x1c) = (int)node;
            I32(I32(node, 4), 0) = (int)node;
        }
    }
    int bVar2;
    if (c1 == 0 && p4 == 0)
        bVar2 = 0;
    else
        bVar2 = 1;
    if (I8(win, 0x30) < 0) {
        U8(win, 0x30) = (uchar)(U8(win, 0x30) & 0x7f);
    } else if (bVar2 == 0) {
        return;
    }
    void* anchor = B(win) + 0x3c;
    for (void** pu = (void**)PTR(win, 0x3c); pu != (void**)anchor; pu = (void**)*pu) {
        void* q = pu ? (void*)((int)pu - 8) : 0;
        UpdateRenderState((int)q, p3, p4);
    }
}

// @ 0x0095a510
void W_s0095_9780::RenderWindow(int win, void* ctx)
{
    void* v = PTR(win, 0x1e4);
    if (v == 0)
        v = TH(this)->Fn00951d50();
    TH(ctx)->e31b20(v);
    void* sub = B(ctx) + 0x58;
    ((int(__thiscall*)(void*, int, int))*(void**)((char*)*(void**)sub + 0x10))(sub, 0, 0);
    int ev[7];
    ev[2] = 0xd;
    ev[6] = (int)ctx;
    GV(0, win + 4, ev, 0, 0);
    TH(ctx)->End2D();
}

// @ 0x0095a580
void __thiscall WindowMgr::BuildDisplayList(Node* out, Win* w, void* info_)
{
    u32* info = (u32*)info_;
    bool go = !(w->b30 & 4) && ((w->b30 & 1) != 0 || (w->flags & 1) != 0);
    if (info[1] > info[0]) info[1] = info[0];
    if (!go) {
        if (!(w->b30 & 8)) MarkTree(w);
        return;
    }

    if (w->b30 & 0x10) {
        DLEntry* e = AllocDisplayListEntry();
        {
            RenderCtx ctx((void*)this);
            ctx.chunks = &e->chunks;
            RenderWindow(w, &ctx);
            if (e->chunks.count == 0 && *(IRenderer**)((u8*)w + 0x1e8) == 0) {
                FreeDisplayListEntry(e);
                w->f78 = 0;
            } else {
                FillDLEntry(this, e, w, info, 1);
                Node* prev = out->prev;
                e->link.prev = prev;
                e->link.next = out;
                out->prev = &e->link;
                prev->next = &e->link;
                w->f78 = (u32)e;
            }
        }
    } else {
        DLEntry* e = (DLEntry*)w->f78;
        if (e != 0) {
            if (e->b0c == 0 || e->chunks.count != 0 || e->renderer != 0) {
                e = AllocDisplayListEntry();
                FillDLEntry(this, e, w, info, 0);
                Node* prev = out->prev;
                e->link.prev = prev;
                e->link.next = out;
                out->prev = &e->link;
                prev->next = &e->link;
                w->f78 = (u32)e;
            } else {
                w->f78 = 0;
            }
        }
    }

    if (w->f78 != 0) info[1] = 0x7fffffff;
    w->b30 &= 0xe7;
    w->f14 = 0;

    Node* head = &w->children;
    if (head->prev != head) {
        (*info)++;
        Node* stop = head->next;
        for (Node* n = head->prev; ; n = n->prev) {
            Win* child = (Win*)((u8*)n - 8);
            BuildDisplayList(out, child, info);
            if (n == stop) break;
        }
        (*info)--;
    }
}

// @ 0x0095a820
void __thiscall FocusListX::InsertFront(const void* value)
{
    Node* first = anchor.next;
    u8* n = (u8*)alloc->Alloc(0x10, 0, allocFlags);
    u8* v = n + 8;
    if (v != 0) {
        ((u32*)v)[0] = ((const u32*)value)[0];
        ((u32*)v)[1] = ((const u32*)value)[1];
    }
    ((Node*)n)->next = first;
    ((Node*)n)->prev = first->prev;
    first->prev->next = (Node*)n;
    first->prev = (Node*)n;
}

// @ 0x0095a870
MsgListX* __thiscall MsgListX::AssignFrom(MsgListX* src)
{
    if (this == src) return this;
    Node* d = anchor.next;
    Node* s = src->anchor.next;
    for (;;) {
        if (d == &anchor) break;
        if (s == &src->anchor) {
            EraseRange(MkIter(d), MkIter((Node*)this));
            return this;
        }
        ((MsgNode_s0095_8a70*)d)->msg = ((MsgNode_s0095_8a70*)s)->msg;
        d = d->next;
        s = s->next;
    }
    if (s != &src->anchor)
        InsertRange(&anchor, MkIter(s), MkIter((Node*)src), (int)src);
    return this;
}

// @ 0x0095a8e0
void __thiscall WindowMgr::SetViewportSize(float vw, float vh)
{
    LMUTEX();
    Msg msg;
    msg.src = 0;
    msg.dst = 0;
    msg.rest[0] = 0x4ecd5687;
    *(float*)&msg.rest[1] = vw;
    *(float*)&msg.rest[2] = vh;
    Node* first = q0.anchor.next;
    MsgNode_s0095_8a70* n = (MsgNode_s0095_8a70*)q0.alloc->Alloc(0x24, 0, q0.allocFlags);
    Msg* pm = &n->msg;
    if (pm != 0)
        *(Msg*)pm = msg;
    n->link.next = first;
    n->link.prev = first->prev;
    first->prev->next = &n->link;
    first->prev = &n->link;
    UMUTEX();
}

// @ 0x0095a980
bool __thiscall WindowMgr::SendMsg(IWin* src, IWin* win, Msg* m, bool a4)
{
    return SendMsgFull(src, win, m, a4, false);
}

// @ 0x0095a9a0
void __thiscall WindowMgr::PostMsg(IWin* src, IWin* dst, const Msg* m)
{
    MutexOps* mx = (MutexOps*)&mxC;
    mx->Lock((const void*)0x1440688);
    if (q4.anchor.next == &q4.anchor) {
        MsgNode_s0095_8a70* n = (MsgNode_s0095_8a70*)q0.alloc->Alloc(0x24, 0, q0.allocFlags);
        Msg* pm = &n->msg;
        if (pm != 0) *pm = *m;
        n->link.next = &q0.anchor;
        n->link.prev = q0.anchor.prev;
        q0.anchor.prev->next = &n->link;
        q0.anchor.prev = &n->link;
    } else {
        Node* first = q4.anchor.next;
        Node* second = first->next;
        if (&q0.anchor != first && &q0.anchor != second)
            Splice(&q0.anchor, first, second);
        ((MsgNode_s0095_8a70*)q0.anchor.prev)->msg = *m;
        f124--;
    }
    MsgNode_s0095_8a70* last = (MsgNode_s0095_8a70*)q0.anchor.prev;
    last->msg.src = src;
    last->msg.dst = dst;
    mx->Unlock();
}

// @ 0x0095aa80
void __thiscall WindowMgr::ProcessMessages()
{
    MsgList mA(EAlloc((void*)GetAlloc()));
    MsgList mB(EAlloc((void*)GetAlloc()));

    LMUTEX();
    if (q0.anchor.next != &q0.anchor)
        Splice(&q1.anchor, q0.anchor.next, &q0.anchor);
    u32 count = f124;
    UMUTEX();

    u32 saved = f688;
    f688 = 0;

    if (q1.anchor.next != &q1.anchor) {
        int deferred = 0;
        while (q1.anchor.next != &q1.anchor) {
            Node* first = q1.anchor.next;
            Node* second = first->next;
            if (&mA.anchor != first && &mA.anchor != second)
                Splice(&mA.anchor, first, second);
            Node* cur = mA.anchor.prev;
            Msg* msg = (Msg*)((u8*)cur + 8);
            if (hook)
                hook->Notify(1, (IWin*)0, msg);
            bool ok;
            if (msg->dst == 0) {
                ok = FCtx(msg, 1);
            } else {
                ok = DispatchMsgToWindow((Win*)((u8*)msg->dst - 4), msg, 0);
            }
            if (hook)
                hook->Notify(ok ? 4 : 5, (IWin*)0, msg);
            if (count < 0x10) {
                Node* c2 = mA.anchor.prev;
                Splice(&mB.anchor, c2, c2->next);
                deferred++;
                count++;
            } else {
                Node* c2 = mA.anchor.prev;
                c2->prev->next = c2->next;
                c2->next->prev = c2->prev;
                mA.alloc->Free(c2, 0x24);
            }
        }
        if (mB.anchor.next != &mB.anchor) {
            LMUTEX();
            Splice(q4.anchor.next, mB.anchor.next, &mB.anchor);
            f124 += (u32)deferred;
            UMUTEX();
        }
    }

    for (int i = 0; i < 10; i++) {
        u8* cb = (u8*)this + 0x6a0 + i * 0x28;
        if (*(u32*)cb != 0) {
            Msg m;
            {
                u32* d = (u32*)&m;
                u32* s = (u32*)(cb - 8);
                for (int j = 0; j < 7; j++) d[j] = s[j];
            }
            *(u32*)cb = 0;
            FCtx(&m, 0);
        }
    }

    {
        tickIter = lB.n.next;
        while (tickIter != &lB.n) {
            Node* it = tickIter;
            IWin* iw = (IWin*)((u8*)it - 0x14);
            Msg m;
            m.rest[0] = 0xc;
            SendMsgFull((IWin*)0, iw, &m, false, false);
            if (f24) f24 = 0;
            else tickIter = tickIter->next;
        }
    }

    f688 = saved;
}

// @ 0x0095add0
void __thiscall WindowMgr::AttachWindow(Win* w)
{
    w->b30 &= 0xef;
    w->f34 = (u32)this;
    w->f78 = 0;
    *(u32*)((u8*)w + 0x1c) = 0;
    w->f14 = 0;
    w->f24 = 0;
    *(u32*)((u8*)w + 0x7c) = fcc;
    fcc++;
    w->b30 &= 0x9f;
    F959fe0(w);
    if (!(w->b30 & 0x14)) {
        w->b30 |= 0x10;
        if (w->f78 == 0) {
            F958110();
        } else {
            Node* node   = (Node*)((u8*)w + 0x10);
            Node* anchor = (Node*)((u8*)this + 8);
            node->prev = anchor->prev;
            node->next = anchor;
            anchor->prev = node;
            node->prev->next = node;
        }
    }
    F9588c0(w);
    F958860(w);
    if ((w->b31 & 1) != 0 || (w->flags & 8) != 0) {
        if (*(u32*)((u8*)w + 0x1c) == 0) {
            Node* node   = (Node*)((u8*)w + 0x18);
            Node* anchor = (Node*)((u8*)this + 0x10);
            node->prev = anchor->prev;
            node->next = anchor;
            anchor->prev = node;
            node->prev->next = node;
        }
    } else {
        if (*(u32*)((u8*)w + 0x1c) != 0)
            F9587d0(w);
    }
    F958110();

    Node* head = &w->children;
    for (Node* n = head->next; n != head; n = n->next)
        AttachWindow(NodeToWin(n));

    IWin* iw = (IWin*)((u8*)w + 4);
    Msg m;
    m.rest[0] = 0x11;
    SendMsgFull(iw, iw, &m, false, false);
    m.rest[0] = 0xe;
    m.rest[1] = 0xffffffff;
    SendMsgFull(iw, iw, &m, false, false);
}

// @ 0x0095af00
void EA::UTFWin::WindowMgr::UpdateWindowCachedTransforms(EA::UTFWin::Window & w)
{
    UpdateRenderState(w, 0, 0);
}

// @ 0x0095af20
bool __thiscall WindowMgr::SetFocusWindow(IWin* w, ICb* cb)
{
    if (w != 0) {
        if (!((bool(__thiscall*)(void*, IWin*))(*(void***)this)[0x80 / 4])(this, w)) {
            if (cur != 0)
                ((FocusListX*)&focusList)->InsertFront(&cur);
            curCb = cb;
            cur = w;
            void* v = ((void*(__thiscall*)(void*))(*(void***)w)[0x10 / 4])(w);
            if (v != 0) {
                ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 0x40, 1);
                void* v2 = ((void*(__thiscall*)(void*))(*(void***)w)[0x10 / 4])(w);
                ((void(__thiscall*)(void*, IWin*))(*(void***)v2)[0xe8 / 4])(v2, w);
                ((void(__thiscall*)(void*, int, IWin*))(*(void***)this)[0x4c / 4])(this, 0, w);
            }
            if (curCb != 0)
                ((void(__thiscall*)(void*, IWin*))(*(void***)curCb)[0])(curCb, w);
            return true;
        }
    }
    return false;
}

// @ 0x0095afd0
void __thiscall MsgListX::Swap(MsgListX& other)
{
    if (alloc == other.alloc && allocFlags == other.allocFlags) {
        EastlListSwap(this, &other);
        return;
    }
    RawMsgList tmp;
    tmp.anchor.next = &tmp.anchor;
    tmp.anchor.prev = &tmp.anchor;
    tmp.alloc = alloc;
    tmp.allocFlags = allocFlags;
    ((MsgList*)&tmp)->InsertRange(&tmp.anchor, MkIter(anchor.next), MkIter((Node*)this), 0);
    AssignFrom(&other);
    other.AssignFrom((MsgListX*)&tmp);
    Node* p = tmp.anchor.next;
    while (p != &tmp.anchor) {
        Node* n = p;
        p = p->next;
        tmp.alloc->Free(n, 0x24);
    }
}

// @ 0x0095b080
bool __thiscall WindowMgr::SetMainWindow(IWin* w, char release)
{
    Win* nw = (w == 0) ? 0 : (Win*)((u8*)w - 4);
    Win* old = mainWin;
    if (old == nw) return true;

    if (old != 0) {
        for (int i = 0; i < 10; i++) {
            u8* b = (u8*)this + 0x68c + i * 0x28;
            *(u32*)(b + 0x00) = 0;
            *(u32*)(b + 0x04) = 0;
            *(u32*)(b + 0x08) = 0;
            *(u32*)(b + 0x14) = 0;
        }
        DetachWindow(old);
        old = mainWin;
        mainWin.p = 0;
        if (release)
            ((void(__thiscall*)(void*))(*(void***)old)[7])(old);
        if (old)
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }

    Win* old2 = mainWin;
    if (nw != old2) {
        if (nw)
            ((void(__thiscall*)(void*))(*(void***)nw)[0])(nw);
        mainWin.p = nw;
        if (old2)
            ((void(__thiscall*)(void*))(*(void***)old2)[1])(old2);
    }

    if (nw != 0) {
        AttachWindow(nw);
        if (!((bool(__thiscall*)(void*))(*(void***)nw)[6])(nw)) {
            DetachWindow(nw);
            return false;
        }
        IWin* iw = (IWin*)((u8*)nw + 4);
        float r[4];
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = fa8 * g_1470f1c;
        r[3] = fac * g_1470f1c;
        ((void(__thiscall*)(void*, void*))(*(void***)iw)[0x60 / 4])(iw, r);
        for (int i = 0; i < 10; i++)
            SetFocus(i, iw);
    }
    return true;
}

// @ 0x0095b290
void __thiscall WindowMgr::FlushMessageQueue()
{
    LMUTEX();
    ((MsgListX*)&q1)->Swap(*(MsgListX*)&q0);
    UMUTEX();

    Node* n = q1.anchor.next;
    while (n != &q1.anchor) {
        if (*(u32*)((u8*)n + 0x10) == 0x74d2e9 && *(u32*)((u8*)n + 0x18) != 0) {
            void* p = *(void**)((u8*)n + 0x18);
            ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        }
        n = n->next;
    }
    n = q1.anchor.next;
    while (n != &q1.anchor) {
        Node* nx = n->next;
        q1.alloc->Free(n, 0x24);
        n = nx;
    }
    q1.anchor.prev = &q1.anchor;
    q1.anchor.next = &q1.anchor;
}

// @ 0x0095b310
void __thiscall WM::UpdateVisuals()
{
    Node L1; L1.prev = &L1; L1.next = &L1;
    Node L2;
    if (mainWin)
        UpdateRenderState(mainWin, 0, 0);
    bool b27 = false;
    bool b13 = false;
    if (f25 == 0) {
        if (lA.n.prev != &lA.n) {
            b13 = true;
            do {
                u8* nb = (u8*)lA.n.next;
                Win* w = (Win*)((nb - 8) ? nb - 0x10 : 0);
                PopFront(&lA.n);
                WB(w, 0x30) &= 0xef;
                WD(w, 0x14) = 0;
                DispEntry* e = AllocDisplayListEntry_s0095_b310();
                RenderCtx_s0095_b310 ctx(this);
                ctx.chunks = &e->chunks;
                RenderWindow(w, &ctx);
                DispEntry* old = (DispEntry*)WD(w, 0x78);
                e->prevEntry = old;
                e->bReplace = 1;
                e->bActive = 0;
                e->depth = ((DispEntry*)WD(w, 0x78))->depth;
                e->lowest = ((DispEntry*)WD(w, 0x78))->lowest;
                e->renderer = (IRenderer_s0095_b310*)WD(w, 0x1e8);
                if (e->renderer) {
                    e->renderer->AddRef();
                    e->data[0].rdata = e->renderer->CreateData((IWin*)w);
                    e->data[1].rdata = 0;
                }
                e->bSecond = 0;
                e->data[0].xf = *(Xform_s0095_b310*)((u8*)w + 0x14c);
                ComputeClip(&e->data[0].r0, w);
                e->data[0].shade = WD(w, 0x1d4);
                PushBack(&L1, &e->link);
                if (e->chunks.count == 0 && ((DispEntry*)WD(w, 0x78))->renderer == 0)
                    WD(w, 0x78) = 0;
                else
                    WD(w, 0x78) = (u32)e;
            } while (lA.n.prev != &lA.n);
            b27 = true;
        }
    } else {
        f25 = 0;
        if (mainWin) {
            u32 tmp[2];
            tmp[0] = 0; tmp[1] = 0;
            BuildDisplayList(&L1, mainWin, tmp);
        }
        ClearLinks(&lA.n);
        lA.n.prev = &lA.n;
        lA.n.next = &lA.n;
        b27 = true;
    }
    L2.prev = &L2; L2.next = &L2;
    ((MutexOps*)&mxA)->Lock((const void*)0x1440688);
    if (lC.n.prev != &lC.n) {
        do {
            u8* nb = (u8*)lC.n.prev;
            Win* w = (Win*)((nb - 0x18) ? nb - 0x20 : 0);
            PopBack(&lC.n);
            WD(w, 0x24) = 0;
            DispEntry* e = (DispEntry*)WD(w, 0x78);
            if (e) {
                RenderData* d = &e->data[e->bSecond == 0];
                if (e->renderer) {
                    if (d->rdata)
                        e->renderer->FreeData(d->rdata);
                    d->rdata = e->renderer->CreateData((IWin*)w);
                }
                d->xf = *(Xform_s0095_b310*)((u8*)w + 0x14c);
                ComputeClip(&d->r0, w);
                d->shade = WD(w, 0x1d4);
                e->bSecond = (e->bSecond == 0);
            }
        } while (lC.n.prev != &lC.n);
    }
    SwapLists(&lE.n, &L2);
    if (b27) {
        if (f58 != 0) {
            if (f59 == 0 && b13) {
                MergePending(&lD.n, &L1, &L2);
                b13 = false;
                goto L7cd;
            }
            for (Node* it = L1.next; it != &L1; it = it->next) {
                DispEntry* e = (DispEntry*)it;
                DispEntry* p = e->prevEntry;
                if (p && !p->bActive) {
                    e->prevEntry = p->prevEntry;
                    if (p->bReplace && !e->bReplace) {
                        e->bReplace = 1;
                        e->chunks.Swap(&p->chunks);
                    }
                    p->link.prev->next = p->link.next;
                    p->link.next->prev = p->link.prev;
                    p->link.next = 0;
                    p->link.prev = 0;
                    PushBack(&L2, &p->link);
                }
            }
            if (b13) {
                if (lD.n.next != &lD.n)
                    AppendAll(&L1, &lD.n);
            }
        }
        if (lD.n.next != &lD.n)
            AppendAll(&L2, &lD.n);
        SwapLists(&lD.n, &L1);
    L7cd:
        if (lE.n.next != &lE.n)
            AppendAll(&L2, &lE.n);
        f58 = 1;
        f59 = b13;
    }
    ((MutexOps*)&mxA)->Unlock();
    DestroyDisplayList(&L2);
    ClearLinks(&L2);
    L2.prev = 0; L2.next = 0;
    ClearLinks(&L1);
}

// @ 0x0095b860
void __thiscall WM::Shutdown()
{
    ResetChildWindowCache();
    FlushMessageQueue();
    s02(0, 1);
    s0e(0);
    s08(0);
    DestroyDisplayList(&lF.n);
    DestroyDisplayList(&lD.n);
    DestroyDisplayList(&lE.n);
}

// @ 0x0095ba70
u32 __cdecl GetTableEntry(u32 i)
{
    if (i < 0x1d)
        return g_tbl_1440748[i];
    return 0x80;
}

// @ 0x0095ba90
void __thiscall Chunk::Swap(Chunk* o)
{
    Chunk* tn = next; next = o->next; o->next = tn;
    int tc = count; count = o->count; o->count = tc;
    u32 n = (u32)o->count;
    if ((u32)count > n)
        n = (u32)count;
    for (int i = (int)n; i > 0; i--) {
        IRel* a = items[i - 1].obj; items[i - 1].obj = o->items[i - 1].obj; o->items[i - 1].obj = a;
        u32 b = items[i - 1].b; items[i - 1].b = o->items[i - 1].b; o->items[i - 1].b = b;
    }
}
