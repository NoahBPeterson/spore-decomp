// Slice s00817cb0 (batch w2g7 #6), 32-bit MSVC 2008.
// cSPUIPieMenuItem / cSPUIPieMenu and helpers.

typedef unsigned int  u32;
typedef unsigned char u8;
#include <new>
#include <math.h>

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

extern "C" void SPUIHelpers_UpdateMouseFocus(int);
extern "C" void SPKeyFromName(void* out, void* name, u32, void*);
extern "C" void FUN_00817fa0(void*, int);

// cSPUIPieMenuItem layout (PDB, size 0x30)
struct cSPUIPieMenuItem {
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

    void SetIcon(int);          // 00818000
    void SetTextColor(int);     // 00817ee0
    void SetId(u32);            // 008188d0
    void MarkUnused();          // 00818950
    bool SetPos(int, int);      // 00817eb0
    void sub817fa0(int);        // 00817fa0
};

// cSPUIPieMenu::cItemInfo (0x4c) embeds the item's fields at the front
struct cItemInfo {
    cSPUIPieMenuItem item;
    char             pad_30[0x4c - 0x30];
};
struct Sub30 {
    char pad_00[0x18];
    int  f18;   // +0x18
    int  f1c;   // +0x1c
};

// @ 0x00817eb0
bool cSPUIPieMenuItem::SetPos(int a, int b) {
    *(int*)((char*)this + 0x64) = a;
    *(int*)((char*)this + 0x68) = b;
    return true;
}

// @ 0x00818370
struct WinProcHolder {
    char      pad_00[0x24];
    IWindow*  mW24;   // +0x24
    bool has(IWindow* w);
};
bool WinProcHolder::has(IWindow* w) {
    bool result = false;
    if (w) {
        if (w != mW24) {
            if (!Vb1(mW24, 0xf8, (int)w)) return false;
        }
        result = true;
    }
    return result;
}

// @ 0x00818330
struct Holder2 {
    char     pad_00[0x24];
    IWindow* mW24;   // +0x24
    char     pad_28[0xb0 - 0x28];
    void*    mWb0;   // +0xb0
    void teardown();
};
void Holder2::teardown() {
    if (mW24) Vv2(mW24, 0x7c, 1, 0);
    if (mWb0) { void* q = mWb0; mWb0 = 0; Vv0(q, 0x04); }
    SPUIHelpers_UpdateMouseFocus(1);
}

// @ 0x00818950
void cSPUIPieMenuItem::MarkUnused() {
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

// @ 0x00817fa0
void cSPUIPieMenuItem::sub817fa0(int color) {
    IWindow* w = (IWindow*)Vcp2(mpRHSWindowSet, 0xf0, 0x122a5c7, 1);
    if (w) {
        Vv2(w, 0x7c, 2, color);
        w = (IWindow*)Vcp2(mpIconWindow, 0xf0, 0x122a5c7, 1);
        if (w) Vv2(w, 0x7c, 2, color);
    }
}

// @ 0x008182c0
struct PieMenu02 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    bool assign(int a, int b);
};
bool PieMenu02::assign(int a, int b) {
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        Sub30* s = *(Sub30**)((char*)mpBegin + i * 0x4c + 0x30);
        s->f18 = a;
        s->f1c = b;
    }
    return true;
}

// @ 0x008181e0
struct PieMenu03 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    void setColor(u32 id, int color);
};
void PieMenu03::setColor(u32 id, int color) {
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)((char*)mpBegin + i * 0x4c);
        if (it->mID == 0xffffffff || it->mID != id) continue;
        it->sub817fa0(color);
    }
}

// @ 0x00818250
struct PieMenu04 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    char       pad_14[0x5c - 0x14];
    u8         b5c;      // +0x5c
    bool setTextColor(u32 id, int color);
};
bool PieMenu04::setTextColor(u32 id, int color) {
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

// @ 0x008188d0
void cSPUIPieMenuItem::SetId(u32 id) {
    IWindow* p = mpCurrentWindow;
    *(u32*)((char*)mpWinProc + 0x10) = id;
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

// @ 0x00817ee0
void cSPUIPieMenuItem::SetTextColor(int color) {
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

// @ 0x00817e20
struct PieMenuInit {
    char pad_00[0x100];
    void Init(void* n1, void* n2, void* p4, void* p5, void* p6, void* p7);
};
void PieMenuInit::Init(void* n1, void* n2, void* p4, void* p5, void* p6, void* p7) {
    u32 key1[3] = {0, 0, 0};
    u32 key2[3] = {0, 0, 0};
    if (n1) SPKeyFromName(key1, n1, 0x510a95b, p4);
    if (n2) SPKeyFromName(key2, n2, 0x510a95b, p4);
    Vv5(this, 0x20, (int)key1, (int)key2, (int)p4, (int)p5, (int)p6);
}

// ===========================================================================
// completed partials (formerly stubs)
// ===========================================================================
#pragma float_control(precise, off, push)   // fast-math codegen (inline fsqrt, SSE scalar)
void* FUN_008067f0(void* w, int a);                // 0x008067f0 cdecl
char  FUN_00806aa0(void* w, void* image, int v);   // 0x00806aa0 cdecl

struct IRefObj {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

struct PieRect { float l, t, r, b; };

// @ 0x00818000
void cSPUIPieMenuItem::SetIcon(int arg) {
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

struct PieVert { float x, y; int c; float u, v; };
struct IPieDraw {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18();
    virtual void Quad(float* a, int ca, float* b, int cb, float* c, int cc);  // +0x4c
    virtual void Tri(PieVert* v, int n, int tex);                              // +0x50
};

// @ 0x008183a0
void __stdcall FUN_008183a0(IPieDraw* dr, float* p2, float* p3, int c1, int c2, float width, int tex) {
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
bool __stdcall FUN_00818500(float* r1, float* r2, float dx, float dy) {
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

// Retail layout of the item as seen by its constructors (the 0x2c field and the +0x30 win proc
// are what the stubs above call mpWinProc / pad).
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

// @ 0x00818650
PieItemFull::PieItemFull(const PieItemFull& o) {
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
PieItemFull& PieItemFull::assign(const PieItemFull& o) {
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
PieItemFull::PieItemFull() {
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

// ===========================================================================
// incomplete / approximate (see partial.txt)
// ===========================================================================
struct PieStub {
    char pad_00[0x4000];
    void a() { *(volatile int*)pad_00 = 0; }
};
void stub_817cb0(PieStub* p) { p->a(); }
void stub_817d70(PieStub* p) { p->a(); }
#pragma float_control(pop)
