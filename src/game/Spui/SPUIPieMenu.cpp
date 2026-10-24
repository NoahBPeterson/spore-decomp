// src/game/Spui/SPUIPieMenu.cpp -- migrated from slice(s) s0081a790, s008198f0, s008189a0, s00817cb0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIPieMenu.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <math.h>
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/RenderContext.h"
#include <string.h>
#include <wchar.h>
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void SPUIHelpers_UpdateMouseFocus(int);

// ---- items of slice s00817cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma float_control(precise, off, push)   // fast-math codegen (inline fsqrt, SSE scalar)
typedef unsigned int  u32;
typedef unsigned char u8;
struct IWindow;
static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void Vv2(void* p, int off, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline int Vi0(void* p, int off) {
    return ((int(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void* Vcp0(void* p, int off) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline char Vb1(void* p, int off, int a) {
    return ((char(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void* Vcp1(void* p, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void* Vcp2(void* p, int off, int a, int b) {
    return ((void*(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline void Vv5(void* p, int off, int a, int b, int c, int d, int e) {
    ((void(__thiscall*)(void*, int, int, int, int, int))(*(void***)p)[off / 4])(p, a, b, c, d, e);
}
extern "C" void SPKeyFromName(void* out, void* name, u32, void*);
class cSPUIPieMenuItem { public:
    void**    vftable;          // +0x00
    u32       mID;              // +0x04
    IWindow*  mpCurrentWindow;  // +0x08
    char      pad_0c[0x14 - 0x0c];
    u32       mFlags;           // +0x14
    char      pad_18[0x1c - 0x18];
    void*     mpLHSWindowSet;   // +0x1c
    void*     mpRHSWindowSet;   // +0x20
    void*     mpIconWindow;     // +0x24
    void*     mpParentWin;      // +0x28
    void*     mpWinProc;        // +0x2c
    void*     f30;              // +0x30

    void SetIcon(int);          // 00818000
    void SetTextColor(int);     // 00817ee0
    void SetId(u32);            // 008188d0
    void MarkUnused();          // 00818950
    bool SetPos(int, int);      // 00817eb0
    void sub817fa0(int);        // 00817fa0
};
struct cItemInfo {
    cSPUIPieMenuItem item;
    char             pad_30[0x4c - 0x30];
};
struct Sub30 {
    char pad_00[0x18];
    int  f18;   // +0x18
    int  f1c;   // +0x1c
};
struct WinProcHolder {
    char      pad_00[0x24];
    IWindow*  mW24;   // +0x24
    bool has(IWindow* w);
};
struct Holder2 {
    char     pad_00[0x24];
    IWindow* mW24;   // +0x24
    char     pad_28[0xb0 - 0x28];
    void*    mWb0;   // +0xb0
    void teardown();
};
struct PieMenu02 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    bool assign(int a, int b);
};
struct PieMenu03 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    void setColor(u32 id, int color);
};
struct PieMenu04 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    char       pad_14[0x5c - 0x14];
    u8         b5c;      // +0x5c
    bool setTextColor(u32 id, int color);
};
struct PieMenuInit {
    char pad_00[0x100];
    void Init(void* n1, void* n2, void* p4, void* p5, void* p6, void* p7);
};
void* FUN_008067f0(void* w, int a);                // 0x008067f0 cdecl
char  FUN_00806aa0(void* w, void* image, int v);   // 0x00806aa0 cdecl
struct IRefObj {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct PieRect { float l, t, r, b; };
struct PieVert { float x, y; int c; float u, v; };
struct IPieDraw {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
    virtual void Quad(float* a, int ca, float* b, int cb, float* c, int cc);  // +0x4c
    virtual void Tri(PieVert* v, int n, int tex);                              // +0x50
};
struct WPBaseA { virtual int AddRef(); virtual int Release(); };
struct WPBaseB { virtual void wpb() = 0; int mB; WPBaseB() : mB(0) {} };
struct ItemWinProc : WPBaseA, WPBaseB {
    int  mButtonId;   // +0xc
    int  mItemId;     // +0x10
    bool mClicked;    // +0x14
    int  mCallback;   // +0x18
    ItemWinProc() : mButtonId(-1), mItemId(-1), mClicked(false), mCallback(0) {}
    virtual void wpb();
};
void* FUN_009512d0(int size, int align, const char* name, int flags);  // 0x009512d0 cdecl
int   FUN_009512c0();                                                   // 0x009512c0 cdecl
static inline void AssignRef(IRefObj*& d, IRefObj* s) {
    IRefObj* old = d;
    if (s != old) {
        if (s) s->AddRef();
        d = s;
        if (old) old->Release();
    }
}
struct PieItemFull {
    virtual void v0();
    u32        mID;           // +0x04
    void*      mpCurrentWin;  // +0x08
    float      mAnchorX;      // +0x0c
    float      mAnchorY;      // +0x10
    u32        mFlags;        // +0x14
    float      mRayWidth;     // +0x18
    IRefObj*   mpLHS;         // +0x1c
    IRefObj*   mpRHS;         // +0x20
    IRefObj*   mpIcon;        // +0x24
    IRefObj*   mpParent;      // +0x28
    IRefObj*   mpW2c;         // +0x2c
    ItemWinProc* mpWinProc;   // +0x30
    char       mB34;          // +0x34

    PieItemFull();
    PieItemFull(const PieItemFull& o);
    PieItemFull& assign(const PieItemFull& o);
};
extern "C" void SPKeyFromName(void* out, void* name, u32, void*);
// ---- items of slice s00817cb0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void SPKeyFromName(void* out, void* name, u32, void*);

// ---- items of slice s008189a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void AnchorWindowToWindow(void* target, void* anchor, int flags, int zero);  // 0x00807340
struct P2 {
    float x, y;
    P2(float a, float b) : x(a), y(b) {}
    P2(const P2& o) : x(o.x), y(o.y) {}
};
struct Rect0 { float l, t, r, b; };   // plain rect (default copy)
struct RectF {
    float l, t, r, b;
    RectF& operator=(const RectF& o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};
struct ICmp;
struct IWindow_s0081_89a0 {
    virtual void v00();
    virtual IWindow_s0081_89a0* v04();                          // 0x04
    virtual void v08();
    virtual ICmp* Cast(unsigned);                    // 0x0c
    virtual int v10();                               // 0x10
    virtual IWindow_s0081_89a0* v14();                          // 0x14
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual const Rect0* GetRect34();                // 0x34
    virtual const Rect0* GetArea();                     // 0x38
    virtual const wchar_t* GetCaption();             // 0x3c
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual void v60();
    virtual void SetPos(float, float);               // 0x64
    virtual void v68();
    virtual void SetArea(const float*);              // 0x6c
virtual void v70();
virtual void v74();
virtual void v78();
    virtual void v7c(int, int);                      // 0x7c
    virtual void SetCaption(const wchar_t*);         // 0x80
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual void v90();                              // 0x90
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
    virtual IWindow_s0081_89a0* va8();                          // 0xa8
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
    virtual P2 ToLocal(P2);                         // 0xc0
    virtual P2 ToGlobal(P2);                        // 0xc4
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
    virtual IWindow_s0081_89a0* FindByID(unsigned, int);        // 0xf0
};
struct ICmp {
    virtual void AddRef();                           // 0x00
    virtual void Release();                          // 0x04
virtual void v08();
virtual void v0c();
    virtual IWindow_s0081_89a0* GetWin();                       // 0x10
virtual void v14();
virtual void v18();
    virtual void v1c(int);                           // 0x1c
};
struct IScr {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual char GetPos(float*, float*);             // 0x10
    virtual char Valid();                            // 0x14
    virtual void Drop();                             // 0x18
};
struct cSPUIPieMenuItem_s0081_89a0 {
    void**   vftable;          // +0x00
    u32      mID;              // +0x04
    IWindow_s0081_89a0* mpCurrentWindow;  // +0x08
    float    mAnchorX;         // +0x0c
    float    mAnchorY;         // +0x10
    u32      mFlags;           // +0x14
    float    mRayWidth;        // +0x18
    void*    mpLHSWindowSet;   // +0x1c
    void*    mpRHSWindowSet;   // +0x20
    void*    mpIconWindow;     // +0x24
    void*    mpParentWin;      // +0x28
    void*    mpWinProc;        // +0x2c
    void*    mp30;             // +0x30
    u32      pad_34;           // +0x34

    void SetIcon(int);          // 00818000 0x00818000
    void Update();              // 008189a0 0x008189a0
    void MarkUnused();          // 00818950 (slice 6) 0x00818950
    bool sub8191b0();           // 008191b0 0x008191b0
    void dtor819880();          // 00819880 0x00819880
    void SetOrientation(bool, bool); // 008192e0 0x008192e0
    void Assign(const cSPUIPieMenuItem_s0081_89a0*); // 008186f0 (item copy)
    void SetText(const wchar_t*, bool);   // 00819220 0x00819220
};
struct Msg {
    char  pad_00[8];
    u32   type;    // +0x08
    int   arg;     // +0x0c
    char  pad_10[8];
    void* ctx;     // +0x18
};
struct RenderContext {
    void* Begin2D(int);  // 0x0095bc10
    void  End2D();       // 0x0095bb20
};
struct Rect4 { float v[4]; int Contains(const float*); };  // cSPSwatchPlanner::Contains 0x005f2350
struct Vec4f { float v[4]; };
extern "C" Vec4f* SPUIHelpers_GetMainWindowArea(Vec4f*);   // 0x00805ea0
class cSPUIPieMenu { public:
    char     pad_00[0xc];
    char*    mpBegin;       // +0xc
    char*    mpEnd;         // +0x10
    char     pad_14[0x20 - 0x14];
    int      mItemCount;    // +0x20 (used as a count in this build)
    IWindow_s0081_89a0* mpRootWin;    // +0x24
    char     pad_28[0x3c - 0x28];
    IWindow_s0081_89a0* mpCenterWin;  // +0x3c
    IWindow_s0081_89a0* mpBoundsWin;  // +0x40
    char     pad_44[0x5c - 0x44];
    u8       b5c;           // +0x5c
    char     pad_5d[3];
    int      mMaxPerCircle; // +0x60
    void   (*mpCallback)(int, void*); // +0x64
    void*    mpCallbackCtx; // +0x68
    float    mExt[4];       // +0x6c
    char     pad_7c[0xb0 - 0x7c];
    IScr*    mpScreenObj;  // +0xb0
    float    mScrX;         // +0xb4
    float    mScrY;         // +0xb8
    float    mOffX;         // +0xbc
    float    mOffY;         // +0xc0
    u8       pad_c4;
    u8       bC5;           // +0xc5

    void RemoveItem();      // 00818c80
    bool DoMessage(void*, Msg*);   // 00818d20
    void rebuild_layout();  // 00819360
    void DrawItem(void*, const P2&, const P2&, int, int, float, void*);  // 008183a0
    void disjoin_items(void*, void*, float, float);  // 00818500
    void teardown();        // 00818330
};
struct ItemInfo {
    cSPUIPieMenuItem_s0081_89a0 item;  // +0x00
    RectF rc;               // +0x38
    int   level;            // +0x48
};
struct DSub { float* GetPair40(float*, int); };   // 0x00830d60
// ---- items of slice s008189a0 end

// ---- items of slice s008198f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00818650(void*);
struct DestroyHelper { void Fn(); };
static inline void DestroyItem(char* p) {
    *(void**)p = (void*)0x1418ef8;
    ((DestroyHelper*)p)->Fn();
    void* q;
    q = *(void**)(p + 0x30); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x2c); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x28); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x24); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x20); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x1c); if (q) Vv0(q, 0x04);
}
struct Tail5 { float f0, f1, f2, f3; int i; };
struct IRef {
    virtual void AddRef();   // slot 0
    virtual void Release();  // slot 1
};
struct Key { u32 mInstance, mType, mGroup; };
struct Point2 { float x, y; Point2() {} Point2(const Point2& o) : x(o.x), y(o.y) {} };
struct Rect4_s0081_98f0 { float l, t, r, b; Rect4_s0081_98f0(float a, float b_, float c, float d) : l(a), t(b_), r(c), b(d) {} Rect4_s0081_98f0(const Rect4_s0081_98f0& o) : l(o.l), t(o.t), r(o.r), b(o.b) {} };
static inline void AssignRef_s0081_98f0(void*& slot, void* np) {
    IRef* old = (IRef*)slot;
    if ((IRef*)np != old) {
        if (np) ((IRef*)np)->AddRef();
        slot = np;
        if (old) old->Release();
    }
}
typedef void* (__thiscall *VP0)(void*);
typedef void  (__thiscall *VV0)(void*);
typedef void  (__thiscall *VV1)(void*, void*);
typedef void  (__thiscall *VV2i)(void*, int, int);
typedef void  (__thiscall *VVf2)(void*, float, float);
typedef void* (__thiscall *VPi)(void*, u32);
typedef int   (__thiscall *VI0)(void*);
typedef float* (__thiscall *VF0)(void*);
#define VT(o, off) ((*(void***)(o))[(off) / 4])
struct cSPUILayout_s0081_98f0 {
    u32 pad0, pad1, pad2, pad3, pad4, pad5;
    cSPUILayout_s0081_98f0();
    void Ctor810000();                              // 0x00810000
    ~cSPUILayout_s0081_98f0();                                 // 0x00811fe0
    bool Init(const Key& k, bool a, u32 b);         // 0x008120d0
    void* FindWindowByID(u32 id, bool a);           // 0x008105b0
    void Shutdown(u32 a);                           // 0x00811ad0
    void** GetObjects();                            // 0x008100c0
    bool SetParentWin(void* w, bool a, u32 b);      // 0x008121b0
    void SetReloadCallback(void (*cb)(void*, void*, bool), void* ctx); // 0x00810090
};
void ReloadCb_00c2e4e0(void*, void*, bool);          // 0x00c2e4e0
struct cSPUIPieMenuItem_s0081_98f0 {
    void**   vftable;          // +0x00
    u32      mID;              // +0x04
    void*    mpCurrentWindow;  // +0x08
    char     pad_0c[0x18 - 0x0c];
    float    mRayWidth;        // +0x18
    void*    mpLHSWindowSet;   // +0x1c
    void*    mpRHSWindowSet;   // +0x20
    void*    mpIconWindow;     // +0x24
    void*    mpParentWin;      // +0x28
    void*    mpWinProc;        // +0x2c
    void*    f30;              // +0x30
    u8       b34;              // +0x34

    bool sub8191b0();                   // 0x008191b0
    void SetOrientation(bool, bool);    // 0x008192e0
    void SetId(u32);                    // 0x008188d0
    void SetIcon(int);                  // 0x00818000
    void SetText(int, bool);            // 0x00819220
    void Update();                      // 0x008189a0
    bool Init(void* winproc, const Key* key, char a3, u32 id, char doUpdate,
              int text, int icon, bool orient);
};
struct ItemCopyBase { void Ctor(const char* src); };        // thiscall 0x00818650, ret 4
struct ItemAssign   { void Assign(const char* src); };      // thiscall 0x008186f0, ret 4
char* ext_00819e00(char* a, char* b, char* c);               // 0x00819e00 cdecl
int   ext_00819e60(char* a, char* b, char* c);               // 0x00819e60 cdecl
char* ext_008190f0(char* a, char* b, char* c);               // 0x008190f0 cdecl
char* ext_00819150(char* a, char* b, char* c);               // 0x00819150 cdecl
void* operator_new_f473a0(unsigned size, const char* name, int f, int d, const char* file, int line); // 0x00f473a0 cdecl
void  operator_delete_f47380(void* p);                       // 0x00f47380 cdecl
void* FUN_009512c0_s0081_98f0();                                        // 0x009512c0 cdecl
void* FUN_009512d0(unsigned size, unsigned align, const char* name, void* alloc); // 0x009512d0 cdecl
static inline void CopyTail(char* d, const char* s) {
    ((float*)(d + 0x38))[0] = ((const float*)(s + 0x38))[0];
    ((float*)(d + 0x38))[1] = ((const float*)(s + 0x38))[1];
    ((float*)(d + 0x38))[2] = ((const float*)(s + 0x38))[2];
    ((float*)(d + 0x38))[3] = ((const float*)(s + 0x38))[3];
    *(int*)(d + 0x48) = *(const int*)(s + 0x48);
}
struct ItemVec {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    char* mpCap;     // +0x08
    ItemVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~ItemVec() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete_f47380(mpBegin);
    }
    void DestroyRange(char* a, char* b);                    // 0x00819f10 (callee ignores ecx)
    void Clear() {
        char* b = mpBegin;
        char* e = mpEnd;
        char* r = ext_008190f0(e, e, b);
        DestroyRange(r, mpEnd);
        mpEnd -= (e - b) / 0x4c * 0x4c;
    }
    void DoInsertValue(char* pos, const char* val);         // 0x0081a510
};
static inline char* AllocItems(int cap) {
    return cap ? (char*)operator_new_f473a0(cap * 0x4c, (const char*)0x13f6b3c, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
}
struct AutoRef {
    IRef* p;
    AutoRef(IRef* q) : p(q) { if (q) q->AddRef(); }
    ~AutoRef() { if (p) p->Release(); }
};
struct RefPtr {
    void* p;
    RefPtr() : p(0) {}
    ~RefPtr() { if (p) ((IRef*)p)->Release(); }
};
struct IconVec {
    void** mpBegin;  // +0x00
    void** mpEnd;    // +0x04
    void** mpCap;    // +0x08
    IconVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~IconVec();                                     // 0x004b5440
    void erase(void** a, void** b);                 // 0x00e25bd0
    void DoInsertValue(void** pos, void** val);     // 0x004b6000
};
struct KeyZ : Key {
    KeyZ() { mInstance = 0; mType = 0; mGroup = 0; }
};
struct RectZ { float l, t, r, b; RectZ() : l(0.0f), t(0.0f), r(0.0f), b(0.0f) {} };
struct WinMem { void Ctor(); };                     // 0x00962a10
struct LayoutMgr { void* GetWorldMainWindow(u32 id); };   // 0x00810620
LayoutMgr* GetLayoutManager();                      // 0x00805070 cdecl
void UpdateMouseFocus(int);                         // 0x00804f50 cdecl
struct IWinProcBase { void** vftable; };                 // +0x00
struct RefCountBase {                                     // +0x04
    void** vftable2;
    int    mRefCount;
    RefCountBase() { vftable2 = (void**)0x13ec458; mRefCount = 0; }
    ~RefCountBase() { vftable2 = (void**)0x13ec458; }
};
struct IWinProcBase2 : IWinProcBase {
    ~IWinProcBase2() { vftable = (void**)0x13eb938; }
};
struct PieBase : IWinProcBase2, RefCountBase {
    PieBase() { vftable = (void**)0x1418fa4; vftable2 = (void**)0x1418f94; }
};
struct cSPUIPieMenu_s0081_98f0 : PieBase {
    ItemVec  mItems;       // +0x0c
    char     pad_18[8];
    int      mItemCount;   // +0x20
    RefPtr   mpRootWin;    // +0x24
    IconVec  mIcons;       // +0x28
    char     pad_34[8];
    RefPtr   mpWinA;       // +0x3c
    RefPtr   mpWinB;       // +0x40
    KeyZ     mKey44;       // +0x44
    KeyZ     mKey50;       // +0x50
    u8       mDirty;       // +0x5c
    int      mMaxPerCircle;// +0x60
    void*    f64;          // +0x64
    void*    f68;          // +0x68
    RectZ    mExt;         // +0x6c
    cSPUILayout_s0081_98f0 mLay7c;    // +0x7c
    cSPUILayout_s0081_98f0 mLay94;    // +0x94
    u8       bAC;          // +0xac
    RefPtr   mpCb;         // +0xb0
    float    f_b4, f_b8;   // +0xb4
    float    f_bc, f_c0;   // +0xbc
    u8       bC4, bC5;     // +0xc4

    cSPUILayout_s0081_98f0* L7c()  { return &mLay7c; }
    cSPUILayout_s0081_98f0* L94()  { return &mLay94; }

    void sub819360();                                    // 0x00819360
    void Show(Point2 pos, void* cb, int n);              // 0x00819ad0
    void reload_icons();                                 // 0x00819f90
    cSPUIPieMenu_s0081_98f0();                                      // 0x0081a1f0
    ~cSPUIPieMenu_s0081_98f0();                                     // 0x0081a2b0
    bool Init(const Key* k1, const Key* k2, char a3, void* parent, char a5); // 0x0081a350
    bool Shutdown();                                     // 0x0081a6d0
};
// ---- items of slice s008198f0 end

// ---- items of slice s0081a790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FUN_00817fa0(void*, int);
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])
struct cSPUIPieMenuItem_s0081_a790 {
  char pad00[0x38];
  float mf0;    // +0x38
  float mf1;    // +0x3c
  float mf2;    // +0x40
  float mf3;    // +0x44
  char pad01[0x4];
  void SetId(int);  // 0x008188d0 (cSPUIPieMenuItem::SetId)
  void SetText(int, int);  // 0x00819220 (cSPUIPieMenuItem::SetText)
  void SetTextColor(int);  // 0x00817ee0 (cSPUIPieMenuItem::SetTextColor)
  void SetIcon(void*);  // 0x00818000 (cSPUIPieMenuItem::SetIcon)
};
struct cSPUIPieMenu_s0081_a790 {
  char pad00[0xc];
  cSPUIPieMenuItem_s0081_a790* mpBegin;   // +0x0c
  cSPUIPieMenuItem_s0081_a790* mpEnd;     // +0x10
  cSPUIPieMenuItem_s0081_a790* mpCap;     // +0x14
  char pad01[0x8];             // +0x18..0x1f
  int mCount;                  // +0x20
  int mItem;                   // +0x24
  void** mpListBegin;          // +0x28
  void** mpListEnd;            // +0x2c
  char pad02[0x2c];            // +0x30..0x5b
  char mChanged;               // +0x5c

  cSPUIPieMenuItem_s0081_a790* get_unused_item();
  int AddItem(int a, int b, int c, int d);
};
// ---- items of slice s0081a790 end

// @ 0x00817e20
void PieMenuInit::Init(void* n1, void* n2, void* p4, void* p5, void* p6, void* p7)
{
    u32 key1[3] = {0, 0, 0};
    u32 key2[3] = {0, 0, 0};
    if (n1) SPKeyFromName(key1, n1, 0x510a95b, p4);
    if (n2) SPKeyFromName(key2, n2, 0x510a95b, p4);
    Vv5(this, 0x20, (int)key1, (int)key2, (int)p4, (int)p5, (int)p6);
}

// @ 0x00817ee0
void cSPUIPieMenuItem::SetTextColor(int color)
{
    if (!color) return;
    IWindow* w = (IWindow*)Vcp1(mpRHSWindowSet, 0xf0, 0x122d76c);
    if (!w) return;
    w = (IWindow*)Vcp1(w, 0x0c, 0xf15f4bd);
    if (!w) return;
    Vv1(w, 0x28, color);
    void* q = Vcp0(w, 0x10);
    Vv0(q, 0x90);
    w = (IWindow*)Vcp1(mpIconWindow, 0xf0, 0x122d76c);
    if (!w) return;
    w = (IWindow*)Vcp1(w, 0x0c, 0xf15f4bd);
    if (!w) return;
    Vv1(w, 0x28, color);
    q = Vcp0(w, 0x10);
    Vv0(q, 0x90);
}

// @ 0x00817fa0
void cSPUIPieMenuItem::sub817fa0(int color)
{
    IWindow* w = (IWindow*)Vcp2(mpRHSWindowSet, 0xf0, 0x122a5c7, 1);
    if (w) {
        Vv2(w, 0x7c, 2, color);
        w = (IWindow*)Vcp2(mpIconWindow, 0xf0, 0x122a5c7, 1);
        if (w) Vv2(w, 0x7c, 2, color);
    }
}

// @ 0x00818000
void cSPUIPieMenuItem::SetIcon(int arg)
{
    IRefObj* nw = (IRefObj*)arg;
    if ((int)mpParentWin == arg) return;
    void* rhs = Vcp2(mpCurrentWindow, 0xf0, 0x122a5c7, 1);
    if (*((char*)this + 0x34) != 0) {
        FUN_00806aa0(rhs, FUN_008067f0(nw, -1), 0);
        IRefObj* old = (IRefObj*)mpParentWin;
        if (nw != old) {
            if (nw) nw->AddRef();
            mpParentWin = nw;
            if (old) old->Release();
        }
    } else {
        IRefObj* cur = (IRefObj*)mpParentWin;
        if (cur) {
            void* par = Vcp0(cur, 0x10);
            if (par) Vv1(par, 0xdc, (int)mpParentWin);
            IRefObj* t = (IRefObj*)mpParentWin;
            if (t) { mpParentWin = 0; t->Release(); }
        }
        IRefObj* old = (IRefObj*)mpParentWin;
        if (nw != old) {
            if (nw) nw->AddRef();
            mpParentWin = nw;
            if (old) old->Release();
        }
        if (mpParentWin) {
            void* par = Vcp0(mpParentWin, 0x10);
            if (Vcp0(mpParentWin, 0x10)) Vv1(par, 0xdc, (int)mpParentWin);
            Vv1(rhs, 0xd8, (int)mpParentWin);
            PieRect* rp = (PieRect*)Vcp0(rhs, 0x38);
            PieRect r;
            r.l = rp->l; r.t = rp->t; r.r = rp->r; r.b = rp->b;
            PieRect* q = (PieRect*)Vcp0(mpParentWin, 0x38);
            float x = ((r.r - r.l) - (q->r - q->l)) * 0.5f;
            float y = ((r.b - r.t) - (q->b - q->t)) * 0.5f;
            ((void(__thiscall*)(void*, float, float))(*(void***)mpParentWin)[0x64 / 4])(mpParentWin, x, y);
            Vv2(mpParentWin, 0x7c, 0x10, 1);
        }
    }
}

// @ 0x008181e0
void PieMenu03::setColor(u32 id, int color)
{
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)((char*)mpBegin + i * 0x4c);
        if (it->mID == 0xffffffff || it->mID != id) continue;
        it->sub817fa0(color);
    }
}

// @ 0x00818250
bool PieMenu04::setTextColor(u32 id, int color)
{
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)((char*)mpBegin + i * 0x4c);
        if (it->mID == id) {
            b5c = 1;
            it->SetTextColor(color);
            return true;
        }
    }
    return false;
}

// @ 0x008182c0
bool PieMenu02::assign(int a, int b)
{
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        Sub30* s = *(Sub30**)((char*)mpBegin + i * 0x4c + 0x30);
        s->f18 = a;
        s->f1c = b;
    }
    return true;
}

// @ 0x00818330
void Holder2::teardown()
{
    if (mW24) Vv2(mW24, 0x7c, 1, 0);
    if (mWb0) { void* q = mWb0; mWb0 = 0; Vv0(q, 0x04); }
    SPUIHelpers_UpdateMouseFocus(1);
}

// @ 0x00818370
bool WinProcHolder::has(IWindow* w)
{
    bool result = false;
    if (w) {
        if (w != mW24) {
            if (!Vb1(mW24, 0xf8, (int)w)) return false;
        }
        result = true;
    }
    return result;
}

// @ 0x008183a0
void __stdcall FUN_008183a0(IPieDraw* dr, float* p2, float* p3, int c1, int c2, float width, int tex)
{
    PieVert v[3];
    float pts[4];
    pts[0] = p3[0];
    pts[1] = p3[1];
    v[0].x = p2[0];
    v[0].y = p2[1];
    float dx = pts[0] - v[0].x;
    float dy = -(pts[1] - v[0].y);
    float inv = 1.0f / (float)sqrt((double)(dy * dy + dx * dx));
    float half = width * 0.5f;
    float ux = dy * inv;
    float uy = dx * inv;
    float nx = ux * half;
    float ny = uy * half;
    pts[2] = nx + pts[0];
    pts[3] = ny + pts[1];
    pts[0] = pts[0] - nx;
    pts[1] = pts[1] - ny;
    if (tex) {
        v[0].c = c1; v[0].u = 1.0f; v[0].v = 0.5f;
        v[1].x = pts[2]; v[1].y = pts[3]; v[1].c = c2; v[1].u = 0.0f; v[1].v = 0.0f;
        v[2].x = pts[0]; v[2].y = pts[1]; v[2].c = c2; v[2].u = 0.0f; v[2].v = 1.0f;
        dr->Tri(v, 1, tex);
        return;
    }
    dr->Quad(p2, c1, &pts[2], c2, &pts[0], c2);
}

// @ 0x00818500
bool __stdcall FUN_00818500(float* r1, float* r2, float dx, float dy)
{
    float offx = 5.0f, offy = 5.0f;
    float ex, ey;
    if (dx > 0.0f) {
        ex = r1[0x40 / 4] - r2[0x38 / 4];
        if (dy > 0.0f) ey = r1[0x44 / 4] - r2[0x3c / 4];
        else { offy = -5.0f; ey = r1[0x3c / 4] - r2[0x44 / 4]; }
    } else {
        ex = r1[0x38 / 4] - r2[0x40 / 4];
        offx = -5.0f;
        if (dy > 0.0f) ey = r1[0x44 / 4] - r2[0x3c / 4];
        else { offy = -5.0f; ey = r1[0x3c / 4] - r2[0x44 / 4]; }
    }
    if (ex * dx > 0.0f && ey * dy > 0.0f) {
        float tY = ex / dx * dy;
        float tX = ey / dy * dx;
        if (tY * tY + ex * ex > tX * tX + ey * ey) ex = tX;
        else ey = tY;
        ex += offx;
        ey += offy;
        float* rc = r2 + 0x38 / 4;
        rc[0] += ex;
        rc[1] += ey;
        rc[2] += ex;
        rc[3] += ey;
        Vv1(*(void**)((char*)r2 + 8), 0x60, (int)rc);
    }
    return true;
}

// @ 0x00818650
PieItemFull::PieItemFull(const PieItemFull& o)
{
    mID = o.mID;
    mpCurrentWin = o.mpCurrentWin;
    mAnchorX = o.mAnchorX;
    mAnchorY = o.mAnchorY;
    mFlags = o.mFlags;
    mRayWidth = o.mRayWidth;
    mpLHS = o.mpLHS;       if (mpLHS)    mpLHS->AddRef();
    mpRHS = o.mpRHS;       if (mpRHS)    mpRHS->AddRef();
    mpIcon = o.mpIcon;     if (mpIcon)   mpIcon->AddRef();
    mpParent = o.mpParent; if (mpParent) mpParent->AddRef();
    mpW2c = o.mpW2c;       if (mpW2c)    mpW2c->AddRef();
    mpWinProc = o.mpWinProc; if (mpWinProc) mpWinProc->AddRef();
    mB34 = o.mB34;
}

// @ 0x008186f0
PieItemFull& PieItemFull::assign(const PieItemFull& o)
{
    mID = o.mID;
    mpCurrentWin = o.mpCurrentWin;
    mAnchorX = o.mAnchorX;
    mAnchorY = o.mAnchorY;
    mFlags = o.mFlags;
    mRayWidth = o.mRayWidth;
    AssignRef(mpLHS, o.mpLHS);
    AssignRef(mpRHS, o.mpRHS);
    AssignRef(mpIcon, o.mpIcon);
    AssignRef(mpParent, o.mpParent);
    AssignRef(mpW2c, o.mpW2c);
    AssignRef((IRefObj*&)mpWinProc, (IRefObj*)(void*)o.mpWinProc);
    mB34 = o.mB34;
    return *this;
}

// @ 0x00818820
PieItemFull::PieItemFull()
{
    mID = 0xffffffff;
    mpCurrentWin = 0;
    mFlags = 3;
    mRayWidth = 10.0f;
    mpLHS = 0; mpRHS = 0; mpIcon = 0; mpParent = 0; mpW2c = 0;
    void* mem = FUN_009512d0(0x20, 4, "UI/ItemWinProc", FUN_009512c0());
    ItemWinProc* wp = mem ? new (mem) ItemWinProc() : 0;
    mpWinProc = wp;
    if (wp) wp->AddRef();
    mpWinProc->mButtonId = 0x122a5c7;
}

// @ 0x008188d0
void cSPUIPieMenuItem::SetId(u32 id)
{
    IWindow* p = mpCurrentWindow;
    *(u32*)((char*)f30 + 0x10) = id;
    if (id == mID) return;
    SetIcon(0);
    mID = id;
    if (id == 0xffffffff) {
        if (p) {
            if (Vi0(p, 0x10))
                Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
    } else {
        if (p) {
            if (Vi0(p, 0x10) == 0) {
                Vv1(mpWinProc, 0xd8, (int)mpCurrentWindow);
                mFlags = 3;
                return;
            }
        }
    }
    mFlags = 3;
}

// @ 0x00818950
void cSPUIPieMenuItem::MarkUnused()
{
    *(u32*)(*(int*)((char*)this + 0x30) + 0x10) = 0xffffffff;
    if (mID != 0xffffffff) {
        SetIcon(0);
        mID = 0xffffffff;
        if (mpCurrentWindow) {
            int r = Vi0(mpCurrentWindow, 0x10);
            if (r) Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
        mFlags = 3;
    }
}

// @ 0x008189a0
void cSPUIPieMenuItem_s0081_89a0::Update()
{
    if (mFlags & 2) mFlags |= 1;
    if (mFlags & 1) {
        const wchar_t empty[1] = { 0 };
        IWindow_s0081_89a0* t0 = mpCurrentWindow->FindByID(0x122d76c, 1);
        const wchar_t* txt = t0->GetCaption();
        if (!txt) txt = empty;
        bool hasText = *txt != 0;
        IWindow_s0081_89a0* target = mpCurrentWindow->FindByID(0x122a5c7, 1);
        Rect0 rc;
        if (hasText) {
            IWindow_s0081_89a0* tw = mpCurrentWindow->FindByID(0x122d76c, 1);
            if (tw) {
                ICmp* cmp = (ICmp*)tw->Cast(0xf15f4bd);
                if (cmp) {
                    cmp->GetWin()->v7c(1, 0);
                    Rect0 ra;
                    { const Rect0* a = cmp->GetWin()->GetArea(); ra.l = a->l; ra.r = a->r; }
                    cmp->v1c(0);
                    int fl = (mpCurrentWindow != (IWindow_s0081_89a0*)mpRHSWindowSet ? 0x40 : 0x20) | 0x200;
                    AnchorWindowToWindow(target, cmp->GetWin(), fl, 0);
                    { const Rect0* q = mpCurrentWindow->GetArea(); rc.l = q->l; rc.t = q->t; rc.r = q->r; rc.b = q->b; }
                    const Rect0* b = cmp->GetWin()->GetArea();
                    rc.r = (b->r - b->l) - (ra.r - ra.l) + rc.r;
                    mpCurrentWindow->SetArea(&rc.l);
                }
            }
        } else {
            { const Rect0* q = mpCurrentWindow->GetArea(); rc.l = q->l; rc.t = q->t; rc.r = q->r; rc.b = q->b; }
            const Rect0* tb = target->GetArea();
            rc.r = (tb->r - tb->l) + rc.l;
            mpCurrentWindow->SetArea(&rc.l);
        }
        const Rect0* ta = target->GetArea();
        float ax = (ta->r + ta->l) * 0.5f;
        float ay = (ta->b + ta->t) * 0.5f;
        mAnchorX = ax;
        mAnchorY = ay;
        float offx = 0.0f, offy = 0.0f;
        IWindow_s0081_89a0* extra = target->va8();
        ICmp* cast;
        if (extra) {
            cast = (ICmp*)extra->Cast(0x53eb526);
            if (cast) {
                cast->AddRef();
                const float* pr = ((DSub*)cast)->GetPair40(&rc.l, 0);
                offx = pr[0];
                offy = pr[1];
            }
        } else {
            cast = 0;
        }
        mAnchorX += offx;
        mAnchorY += offy;
        if (cast) cast->Release();
    }
    mFlags &= ~3u;
}

// @ 0x00818c80
void cSPUIPieMenu::RemoveItem()
{
    for (u32 i = 0; i < (u32)((mpEnd - mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem_s0081_89a0* it = (cSPUIPieMenuItem_s0081_89a0*)(mpBegin + i * 0x4c);
        if (it->mID != 0xffffffff) {
            // MarkUnused() inlined by the original
            *(u32*)(*(int*)((char*)it + 0x30) + 0x10) = 0xffffffff;
            if (it->mID != 0xffffffff) {
                it->SetIcon(0);
                it->mID = 0xffffffff;
                if (it->mpCurrentWindow && Vi0(it->mpCurrentWindow, 0x10))
                    Vv1(it->mpWinProc, 0xdc, (int)it->mpCurrentWindow);
                it->mFlags = 3;
            }
            mItemCount += -1;
        }
    }
}

// @ 0x00818d20
bool cSPUIPieMenu::DoMessage(void* /*win*/, Msg* msg)
{
    u32 type = msg->type;
    if (type == 0x2ccb7e3) {
        if (mpCallback) mpCallback(msg->arg, mpCallbackCtx);
        return true;
    }
    if (type == 0xd) {
        RenderContext* rctx = (RenderContext*)msg->ctx;
        void* h = rctx->Begin2D(0);
        for (u32 i = 0; i < (u32)((mpEnd - mpBegin) / 0x4c); ++i) {
            ItemInfo* it = (ItemInfo*)(mpBegin + i * 0x4c);
            if (it->item.mID != 0xffffffff && it->level <= 0) {
                P2 A(it->rc.l + it->item.mAnchorX, it->rc.t + it->item.mAnchorY);
                if (it->item.mpLHSWindowSet)
                    DrawItem(h, P2(mOffX + mScrX, mOffY + mScrY), A, -1, -1, it->item.mRayWidth, it->item.mpLHSWindowSet);
                else
                    DrawItem(h, P2(mOffX + mScrX, mOffY + mScrY), A, 0xafffffff, 0x5f3f3f5f, it->item.mRayWidth, 0);
            }
        }
        rctx->End2D();
        return false;
    }
    if (type == 0xc && mpScreenObj) {
        if (mpScreenObj->GetPos(&mScrX, &mScrY)) {
            *(P2*)&mScrX = mpRootWin->ToGlobal(*(P2*)&mScrX);
            mpRootWin->v90();
            if (mpCenterWin) {
                IWindow_s0081_89a0* cw = mpCenterWin;
                const Rect0* r1 = cw->GetRect34();
                float hh = r1->b - r1->t;
                const Rect0* r2 = cw->GetRect34();
                cw->SetPos((mOffX + mScrX) - (r2->r - r2->l) * 0.5f,
                           (mOffY + mScrY) - hh * 0.5f);
            }
            const Rect0* r3 = mpCenterWin->GetArea();
            P2 o2 = mpCenterWin->ToLocal(P2((r3->r - r3->l) * 0.5f, (r3->b - r3->t) * 0.5f));
            IWindow_s0081_89a0* par2 = mpCenterWin->v14()->v04();
            P2 t = par2->ToGlobal(P2(o2.x, o2.y));
            o2.x = t.x;
            o2.y = t.y;
            Rect4 area;
            SPUIHelpers_GetMainWindowArea((Vec4f*)&area);
            float wd = (area.v[2] - area.v[0]) * 0.2f;
            float ht = (area.v[3] - area.v[1]) * 0.2f;
            area.v[0] -= wd;
            area.v[1] -= ht;
            area.v[2] += wd;
            area.v[3] += ht;
            if (!mpScreenObj->Valid() || !area.Contains(&o2.x)) {
                mpScreenObj->Drop();
                teardown();
            }
        }
    }
    return false;
}

// @ 0x008190f0
ItemInfo* CopyItemsFwd(ItemInfo* first, ItemInfo* last, ItemInfo* dest)
{
    for (; first != last; ++dest, ++first) {
        dest->item.Assign(&first->item);
        dest->rc = first->rc;
        dest->level = first->level;
    }
    return dest;
}

// @ 0x00819150
ItemInfo* CopyItemsBack(ItemInfo* first, ItemInfo* last, ItemInfo* dest)
{
    while (last != first) {
        --last;
        --dest;
        dest->item.Assign(&last->item);
        dest->rc = last->rc;
        dest->level = last->level;
    }
    return dest;
}

// @ 0x008191b0
bool cSPUIPieMenuItem_s0081_89a0::sub8191b0()
{
    MarkUnused();
    mpCurrentWindow = 0;
    { void* q = mpRHSWindowSet;  if (q) { mpRHSWindowSet = 0;  Vv0(q, 0x04); } }
    { void* q = mpIconWindow;    if (q) { mpIconWindow = 0;    Vv0(q, 0x04); } }
    { void* q = mpParentWin;     if (q) { mpParentWin = 0;     Vv0(q, 0x04); } }
    { void* q = mpWinProc;       if (q) { mpWinProc = 0;       Vv0(q, 0x04); } }
    { void* q = *(void**)((char*)this + 0x30);
      if (q) { *(void**)((char*)this + 0x30) = 0; Vv0(q, 0x04); } }
    return true;
}

// @ 0x00819220
void cSPUIPieMenuItem_s0081_89a0::SetText(const wchar_t* text, bool update)
{
    IWindow_s0081_89a0* w = ((IWindow_s0081_89a0*)mpRHSWindowSet)->FindByID(0x122d76c, 1);
    if (w) {
        const wchar_t empty[1] = { 0 };
        const wchar_t* s = text ? text : empty;
        const wchar_t* cur = w->GetCaption();
        if (wcscmp(s, cur) != 0) {
            w->SetCaption(s);
            IWindow_s0081_89a0* w2 = ((IWindow_s0081_89a0*)mpIconWindow)->FindByID(0x122d76c, 1);
            if (w2) w2->SetCaption(s);
            mFlags |= 1;
            if (update) Update();
        }
    }
}

// @ 0x008192e0
void cSPUIPieMenuItem_s0081_89a0::SetOrientation(bool vert, bool update)
{
    void** slot = vert ? &mpRHSWindowSet : &mpIconWindow;
    IWindow_s0081_89a0* w = (IWindow_s0081_89a0*)*slot;
    if (mpCurrentWindow != w) {
        if (mpCurrentWindow) {
            if (Vi0(mpCurrentWindow, 0x10))
                Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
        mpCurrentWindow = w;
        if (mID != 0xffffffff)
            Vv1(mpWinProc, 0xd8, (int)w);
        mFlags |= 2;
        if (update) Update();
        IWindow_s0081_89a0* parent = (IWindow_s0081_89a0*)mpParentWin;
        SetIcon(0);
        SetIcon((int)parent);
    }
}

// @ 0x00819360
void cSPUIPieMenu::rebuild_layout()
{
    if (!b5c) return;
    __declspec(align(16)) int idx[512];
    int cnt = 0;
    for (u32 i = 0; i < (u32)((mpEnd - mpBegin) / 0x4c); ++i) {
        ItemInfo* it = (ItemInfo*)(mpBegin + i * 0x4c);
        if (it->item.mID != 0xffffffff) idx[cnt++] = i;
    }
    if (cnt < 1) return;
    mExt[0] = 10000.0f;
    mExt[1] = 10000.0f;
    mExt[2] = -10000.0f;
    mExt[3] = -10000.0f;
    int m = mMaxPerCircle;
    int pos = 0;
    if (cnt <= m) m = cnt;
    ItemInfo* base = (ItemInfo*)mpBegin;
    const Rect0* r0 = base[idx[0]].item.mpCurrentWindow->GetRect34();
    float ch = r0->b - r0->t;
    float ang0;
    if (bC5) {
        ang0 = -1.57079637f;
    } else {
        int mx = mMaxPerCircle;
        ang0 = 3.14159274f / (float)(mx + ((mx & 1) ? 0 : 3));
    }
    float R = (float)m * ch * 0.25f;
    if (R < 70.0f) R = 70.0f;
    int lvl = -mMaxPerCircle;
    do {
        int end = m + pos;
        float step = 6.28318548f / (float)m;
        for (int j = pos; j < end; ++j) {
            ItemInfo* it = (ItemInfo*)((char*)mpBegin + idx[j] * 0x4c);
            double ang = (double)j * step + ang0;
            float x = (float)(cos(ang) * R);
            float y = (float)(sin(ang) * R);
            IWindow_s0081_89a0* win = (IWindow_s0081_89a0*)((x > -1.5258789e-05f) ? it->item.mpIconWindow : it->item.mpRHSWindowSet);
            if (it->item.mpCurrentWindow != win) {
                if (it->item.mpCurrentWindow) {
                    if (Vi0(it->item.mpCurrentWindow, 0x10))
                        Vv1(it->item.mpWinProc, 0xdc, (int)it->item.mpCurrentWindow);
                }
                it->item.mpCurrentWindow = win;
                if (it->item.mID != 0xffffffff)
                    Vv1(it->item.mpWinProc, 0xd8, (int)win);
                it->item.mFlags |= 2;
                it->item.Update();
                IWindow_s0081_89a0* parent = (IWindow_s0081_89a0*)it->item.mpParentWin;
                it->item.SetIcon(0);
                it->item.SetIcon((int)parent);
            }
            it->item.Update();
            it->level = ++lvl;
            IWindow_s0081_89a0* w = it->item.mpCurrentWindow;
            w->GetArea();
            w->SetPos(x - *(float*)((char*)it + 0xc), y - *(float*)((char*)it + 0x10));
            it->rc = *(const RectF*)w->GetArea();
            mExt[0] = (it->rc.l <= mExt[0]) ? it->rc.l : mExt[0];
            mExt[1] = (it->rc.t <= mExt[1]) ? it->rc.t : mExt[1];
            mExt[2] = (mExt[2] <= it->rc.r) ? it->rc.r : mExt[2];
            mExt[3] = (mExt[3] <= it->rc.b) ? it->rc.b : mExt[3];
        }
        pos = end;
        int rem = cnt - pos;
        if (rem != 0) {
            float wv = mExt[3] - mExt[1];
            float hv = mExt[2] - mExt[0];
            const float* pm = (wv > hv) ? &wv : &hv;
            m = (int)((*pm / ch) * 2.0f + 0.5f);
            ang0 *= 0.5f;
        }
        if (rem < m) m = rem;
    } while (pos < cnt);
    for (int pass = 3; pass != 0; --pass) {
        for (int k = 0; k < cnt; ++k) {
            ItemInfo* a = base + k;
            if (a->level > 0) {
                for (int j = 0; j < cnt; ++j) {
                    ItemInfo* b = base + j;
                    if (b->level < a->level && a->rc.r > b->rc.l && b->rc.r > a->rc.l && a->rc.b > b->rc.t && b->rc.b > a->rc.t)
                        disjoin_items(b, a, a->rc.l + *(float*)((char*)a + 0xc), a->rc.t + *(float*)((char*)a + 0x10));
                }
                mExt[0] = (a->rc.l <= mExt[0]) ? a->rc.l : mExt[0];
                mExt[1] = (a->rc.t <= mExt[1]) ? a->rc.t : mExt[1];
                mExt[2] = (mExt[2] <= a->rc.r) ? a->rc.r : mExt[2];
                mExt[3] = (mExt[3] <= a->rc.b) ? a->rc.b : mExt[3];
            }
        }
    }
    if (mpBoundsWin) {
        float e[4] = { -R, -R, R, R };
        mpBoundsWin->SetArea(e);
    }
    b5c = 0;
}

// @ 0x00819880
void cSPUIPieMenuItem_s0081_89a0::dtor819880()
{
    vftable = (void**)0x1418ef8;
    sub8191b0();
    void* q;
    q = *(void**)((char*)this + 0x30); if (q) Vv0(q, 0x04);
    q = mpWinProc;    if (q) Vv0(q, 0x04);
    q = mpParentWin;  if (q) Vv0(q, 0x04);
    q = mpIconWindow; if (q) Vv0(q, 0x04);
    q = mpRHSWindowSet; if (q) Vv0(q, 0x04);
    q = mpLHSWindowSet; if (q) Vv0(q, 0x04);
}

// @ 0x008198f0
bool cSPUIPieMenuItem_s0081_98f0::Init(void* winproc, const Key* key, char a3, u32 id, char doUpdate, int text, int icon, bool orient)
{
    AssignRef_s0081_98f0(mpWinProc, winproc);
    if (mpRHSWindowSet && mpIconWindow) sub8191b0();
    cSPUILayout_s0081_98f0 lay;
    if (lay.Init(*key, true, 0x5b598fa)) {
        AssignRef_s0081_98f0(mpRHSWindowSet, lay.FindWindowByID(0x123ebe3, true));
        AssignRef_s0081_98f0(mpIconWindow, lay.FindWindowByID(0x123ebe4, true));
        void* w = lay.FindWindowByID(0x4332b60, true);
        if (w) {
            float* r = ((VF0)VT(w, 0x38))(w);
            mRayWidth = r[2] - r[0];
            AssignRef_s0081_98f0(mpLHSWindowSet, FUN_008067f0(w, -1));
        }
        lay.Shutdown(1);
        if (mpIconWindow && mpRHSWindowSet) {
            ((VV1)VT(mpIconWindow, 0x104))(mpIconWindow, f30);
            ((VV1)VT(mpRHSWindowSet, 0x104))(mpRHSWindowSet, f30);
            b34 = a3;
            SetOrientation(orient, false);
            SetId(id);
            SetIcon(icon);
            SetText(text, false);
            if (doUpdate) Update();
            return true;
        }
    }
    return false;
}

// @ 0x00819ad0
void cSPUIPieMenu_s0081_98f0::Show(Point2 pos, void* cb, int n)
{
    AssignRef_s0081_98f0(mpCb.p, cb);
    if (mMaxPerCircle != n) {
        mDirty = 1;
        if (n > 0) mMaxPerCircle = n;
    }
    if (mDirty) sub819360();
    void* root = mpRootWin.p;
    ((VV2i)VT(mpRootWin.p, 0x7c))(mpRootWin.p, 1, 1);
    void* par = ((VP0)VT(mpRootWin.p, 0x10))(mpRootWin.p);
    Point2 pt;
    ((void* (__thiscall *)(void*, Point2*, Point2))VT(par, 0xc4))(par, &pt, pos);
    float offx = 0.0f, offy = 0.0f;
    Rect4_s0081_98f0 rc(mExt.l, mExt.t, mExt.r, mExt.b);
    rc.l += pt.x;
    rc.t += pt.y;
    rc.r += pt.x;
    rc.b += pt.y;
    void* par2 = ((VP0)VT(mpRootWin.p, 0x10))(mpRootWin.p);
    Rect4_s0081_98f0 sr(*(Rect4_s0081_98f0*)((VF0)VT(par2, 0x38))(par2));
    float sw = sr.r - sr.l;
    float sh = sr.b - sr.t;
    if (rc.r - rc.l > sw) offx = (sw - rc.l - rc.r) * 0.5f;
    else if (0.0f > rc.l) offx = -rc.l;
    else if (rc.r > sw) offx = sw - rc.r;
    if (rc.b - rc.t > sh) offy = (sh - rc.t - rc.b) * 0.5f;
    else if (0.0f > rc.t) offy = -rc.t;
    else if (rc.b > sh) offy = sh - rc.b;
    ((VVf2)VT(mpRootWin.p, 0x64))(mpRootWin.p, pt.x + offx, pt.y + offy);
    Point2 v(pos);
    if (mpCb.p) ((void (__thiscall *)(void*, float*, float*))VT(mpCb.p, 0x10))(mpCb.p, &v.x, &v.y);
    float dy = pos.y - v.y;
    float dx = pos.x - v.x;
    f_bc = dx;
    f_c0 = dy;
    float* np = ((float* (__thiscall *)(void*, Point2*, Point2))VT(mpRootWin.p, 0xc4))(mpRootWin.p, &pt, v);
    f_b4 = np[0];
    f_b8 = np[1];
    ((VV0)VT(mpRootWin.p, 0x90))(mpRootWin.p);
    void* c = mpWinA.p;
    if (c) {
        float* r1 = ((VF0)VT(c, 0x34))(c);
        float h = r1[3] - r1[1];
        float* r2 = ((VF0)VT(c, 0x34))(c);
        float sy = f_b8 + f_c0;
        float sx = f_b4 + f_bc;
        ((VVf2)VT(c, 0x64))(c, sx - (r2[2] - r2[0]) * 0.5f, sy - h * 0.5f);
    }
    UpdateMouseFocus(1);
}

// @ 0x00819e00
int __cdecl FUN_00819e00(char* a, char* b, char* c)
{
    if (a == b) return (int)c;
    char* dst = c + 0x40;
    char* src = a + 0x40;
    do {
        if (c) {
            FUN_00818650(a);
            Tail5* d = (Tail5*)(dst - 8);
            Tail5* s = (Tail5*)(src - 8);
            d->f0 = s->f0;
            d->f1 = s->f1;
            d->f2 = s->f2;
            d->f3 = s->f3;
            d->i  = s->i;
        }
        a += 0x4c;
        src += 0x4c;
        c += 0x4c;
        dst += 0x4c;
    } while (a != b);
    return (int)c;
}

// @ 0x00819e60
int __cdecl FUN_00819e60(char* a, char* b, int c)
{
    if (a == b) return c;
    do {
        DestroyItem(a);
        a += 0x4c;
        c += 0x4c;
    } while (a != b);
    return c;
}

// @ 0x00819f10
void __stdcall FUN_00819f10(char* a, char* b)
{
    for (; a < b; a += 0x4c) DestroyItem(a);
}

// @ 0x00819f90
void cSPUIPieMenu_s0081_98f0::reload_icons()
{
    if (mpWinA.p) {
        ((VV1)VT(mpRootWin.p, 0xdc))(mpRootWin.p, mpWinA.p);
        IRef* o = (IRef*)mpWinA.p;
        if (o) { mpWinA.p = 0; o->Release(); }
    }
    if (mpWinB.p) {
        ((VV1)VT(mpRootWin.p, 0xdc))(mpRootWin.p, mpWinB.p);
        IRef* o = (IRef*)mpWinB.p;
        if (o) { mpWinB.p = 0; o->Release(); }
    }
    IconVec* icons = &mIcons;
    icons->erase(icons->mpBegin, icons->mpEnd);
    void** objs = L94()->GetObjects();
    void** it = (void**)objs[0];
    void** last = (void**)objs[1];
    while (it != last) {
        void* ob = *it++;
        void* q = ((VPi)VT(ob, 0xc))(ob, 0xeeee8218);
        if (q) {
            int id = ((VI0)VT(q, 0x1c))(q);
            if (id == 0x123ef00) {
                AssignRef_s0081_98f0(mpWinA.p, q);
            } else if (id == 0x8096020) {
                AssignRef_s0081_98f0(mpWinB.p, q);
            } else if (id != 0) {
                AutoRef tmp((IRef*)q);
                if (icons->mpEnd < icons->mpCap) {
                    void** d = icons->mpEnd++;
                    if (d) { *d = q; ((IRef*)q)->AddRef(); }
                } else {
                    icons->DoInsertValue(icons->mpEnd, (void**)&tmp.p);
                }
            }
        }
    }
    if (mpWinB.p) {
        ((VV1)VT(mpRootWin.p, 0xd8))(mpRootWin.p, mpWinB.p);
        void* c = mpWinB.p;
        float* r1 = ((VF0)VT(c, 0x34))(c);
        float h = r1[3] - r1[1];
        float* r2 = ((VF0)VT(c, 0x34))(c);
        ((VVf2)VT(c, 0x64))(c, (r2[2] - r2[0]) * -0.5f, h * -0.5f);
        ((VV2i)VT(mpWinB.p, 0x7c))(mpWinB.p, 0x10, 1);
    }
    if (mpWinA.p) {
        ((VV1)VT(mpRootWin.p, 0xd8))(mpRootWin.p, mpWinA.p);
        void* c = mpWinA.p;
        float* r1 = ((VF0)VT(c, 0x34))(c);
        float h = r1[3] - r1[1];
        float* r2 = ((VF0)VT(c, 0x34))(c);
        ((VVf2)VT(c, 0x64))(c, (r2[2] - r2[0]) * -0.5f, h * -0.5f);
        ((VV2i)VT(mpWinA.p, 0x7c))(mpWinA.p, 0x10, 1);
    }
}

// @ 0x0081a1f0
cSPUIPieMenu_s0081_98f0::cSPUIPieMenu_s0081_98f0()
: mItemCount(0), mDirty(1), mMaxPerCircle(0), f64(0), f68(0), bAC(0), bC4(0), bC5(0) {
}

// @ 0x0081a2b0
cSPUIPieMenu_s0081_98f0::~cSPUIPieMenu_s0081_98f0()
{
    vftable = (void**)0x1418fa4;
    vftable2 = (void**)0x1418f94;
}

// @ 0x0081a350
bool cSPUIPieMenu_s0081_98f0::Init(const Key* k1, const Key* k2, char a3, void* parent, char a5)
{
    void* mem = FUN_009512d0(0x20c, 4, "UI/PieMenu", FUN_009512c0_s0081_98f0());
    void* w;
    if (mem) {
        ((WinMem*)mem)->Ctor();
        *(void**)mem = (void*)0x1414b10;
        w = (char*)mem + 4;
        *(void**)w = (void*)0x14431f8;
    } else {
        w = 0;
    }
    AssignRef_s0081_98f0(mpRootWin.p, w);
    ((VV1)VT(mpRootWin.p, 0x104))(mpRootWin.p, this);
    ((VV2i)VT(mpRootWin.p, 0x7c))(mpRootWin.p, 0x10, 1);
    ((VV2i)VT(mpRootWin.p, 0x7c))(mpRootWin.p, 1, 0);
    ((VV1)VT(mpRootWin.p, 0xac))(mpRootWin.p, 0);
    if (!parent) parent = GetLayoutManager()->GetWorldMainWindow(0x5b598f7);
    ((VV1)VT(parent, 0xd8))(parent, mpRootWin.p);
    ((VVf2)VT(mpRootWin.p, 0x64))(mpRootWin.p, 0.0f, 0.0f);
    ((VVf2)VT(mpRootWin.p, 0x68))(mpRootWin.p, 1.0f, 1.0f);
    bC4 = a3;
    bC5 = a5;
    Key* pk = &mKey44;
    *pk = *k2;
    if (pk->mInstance != 0 || pk->mType != 0 || pk->mGroup != 0) {
        if (L94()->Init(*pk, true, 0x5b598fa)) {
            L94()->SetParentWin(0, false, 0x5b598fa);
            L94()->SetReloadCallback(ReloadCb_00c2e4e0, this);
            reload_icons();
        }
    }
    Key* pk2 = &mKey50;
    *pk2 = *k1;
    if (L7c()->Init(*pk2, true, 0x5b598fa)) {
        L7c()->SetParentWin(0, false, 0x5b598fa);
        L7c()->SetReloadCallback(ReloadCb_00c2e4e0, this);
        return true;
    }
    return false;
}

// @ 0x0081a510
void ItemVec::DoInsertValue(char* pos, const char* val)
{
    char* e = mpEnd;
    if (e != mpCap) {
        const char* v = val;
        if (v >= pos && v < e) v += 0x4c;
        if (e) {
            ((ItemCopyBase*)e)->Ctor(e - 0x4c);
            CopyTail(e, e - 0x4c);
        }
        ext_00819150(pos, mpEnd - 0x4c, mpEnd);
        ((ItemAssign*)pos)->Assign(v);
        CopyTail(pos, v);
        mpEnd += 0x4c;
        return;
    }
    int n = (int)(e - mpBegin) / 0x4c;
    int cap = n ? n * 2 : 1;
    char* nb = AllocItems(cap);
    char* ob = mpBegin;
    char* np = ext_00819e00(ob, pos, nb);
    ext_00819e60(ob, pos, nb);
    if (np) {
        ((ItemCopyBase*)np)->Ctor(val);
        CopyTail(np, val);
    }
    char* oe = mpEnd;
    char* ne = ext_00819e00(pos, oe, np + 0x4c);
    ext_00819e60(pos, oe, np + 0x4c);
    if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete_f47380(mpBegin);
    mpBegin = nb;
    mpEnd = ne;
    mpCap = nb + cap * 0x4c;
}

// @ 0x0081a6d0
bool cSPUIPieMenu_s0081_98f0::Shutdown()
{
    f64 = 0;
    f68 = 0;
    mItems.Clear();
    mIcons.erase(mIcons.mpBegin, mIcons.mpEnd);
    mItemCount = 0;
    L94()->Shutdown(1);
    L7c()->Shutdown(1);
    void* p = ((VP0)VT(mpRootWin.p, 0x10))(mpRootWin.p);
    ((VV1)VT(p, 0xe0))(p, mpRootWin.p);
    { IRef* o = (IRef*)mpRootWin.p; if (o) { mpRootWin.p = 0; o->Release(); } }
    { IRef* o = (IRef*)mpCb.p; if (o) { mpCb.p = 0; o->Release(); } }
    return true;
}

// @ 0x0081a790
cSPUIPieMenuItem_s0081_a790* cSPUIPieMenu_s0081_a790::get_unused_item()
{
  return 0;
}

// @ 0x0081a940
int cSPUIPieMenu_s0081_a790::AddItem(int a, int b, int c, int d)
{
  cSPUIPieMenuItem_s0081_a790* item = get_unused_item();
  if (item == 0) return 0;
  item->mf0 = 0.f; item->mf1 = 0.f; item->mf2 = 0.f; item->mf3 = 0.f;
  item->SetId(a);
  item->SetText(b, 1);
  item->SetTextColor(c);
  FUN_00817fa0(item, d);
  uint32_t n = (uint32_t)(mpListEnd - mpListBegin);
  if (n != 0) {
    uint32_t i = 0;
    for (;;) {
      void* p = mpListBegin[i];
      int id = ((int (__thiscall*)(void*))VTSLOT(p, 0x1c))(p);
      if (id == a) { item->SetIcon(p); break; }
      i++;
      if (i >= (uint32_t)(mpListEnd - mpListBegin)) break;
    }
  }
  mCount++;
  mChanged = 1;
  return 1;
}
