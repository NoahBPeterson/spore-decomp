// Slice s008198f0 (batch w2g7 #8), 32-bit MSVC 2008.
// cSPUIPieMenu / cSPUIPieMenuItem bulk destroy + copy helpers.

typedef unsigned int  u32;
typedef unsigned char u8;

struct IWindow;

static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}

extern "C" void FUN_00818650(void*);
extern "C" void FUN_008191b0_p();
extern "C" int  FUN_008190f0(int, int, int);
struct DestroyHelper { void Fn(); };

// same shape as FUN_008191b0 (slice 7): vtable 0x1418ef8 + release members
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

// @ 0x00819e00
int __cdecl FUN_00819e00(char* a, char* b, char* c) {
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
int __cdecl FUN_00819e60(char* a, char* b, int c) {
    if (a == b) return c;
    do {
        DestroyItem(a);
        a += 0x4c;
        c += 0x4c;
    } while (a != b);
    return c;
}

// @ 0x00819f10
void __stdcall FUN_00819f10(char* a, char* b) {
    for (; a < b; a += 0x4c) DestroyItem(a);
}

// ===========================================================================
// cSPUIPieMenuItem::Init and the cSPUIPieMenu members (retail layout)
// ===========================================================================
struct IRef {
    virtual void AddRef();   // slot 0
    virtual void Release();  // slot 1
};
struct Key { u32 mInstance, mType, mGroup; };
struct Point2 { float x, y; Point2() {} Point2(const Point2& o) : x(o.x), y(o.y) {} };
struct Rect4 { float l, t, r, b; Rect4(float a, float b_, float c, float d) : l(a), t(b_), r(c), b(d) {} Rect4(const Rect4& o) : l(o.l), t(o.t), r(o.r), b(o.b) {} };

// intrusive pointer assign: AddRef the new one, store, Release the old one
static inline void AssignRef(void*& slot, void* np) {
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

struct cSPUILayout {
    u32 pad0, pad1, pad2, pad3, pad4, pad5;
    cSPUILayout();
    void Ctor810000();                              // 0x00810000
    ~cSPUILayout();                                 // 0x00811fe0
    bool Init(const Key& k, bool a, u32 b);         // 0x008120d0
    void* FindWindowByID(u32 id, bool a);           // 0x008105b0
    void Shutdown(u32 a);                           // 0x00811ad0
    void** GetObjects();                            // 0x008100c0
    bool SetParentWin(void* w, bool a, u32 b);      // 0x008121b0
    void SetReloadCallback(void (*cb)(void*, void*, bool), void* ctx); // 0x00810090
};
void ReloadCb_00c2e4e0(void*, void*, bool);          // 0x00c2e4e0
void* FUN_008067f0(void* w, int a);                  // 0x008067f0 cdecl

struct cSPUIPieMenuItem {
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

// @ 0x008198f0
bool cSPUIPieMenuItem::Init(void* winproc, const Key* key, char a3, u32 id, char doUpdate,
                            int text, int icon, bool orient) {
    AssignRef(mpWinProc, winproc);
    if (mpRHSWindowSet && mpIconWindow) sub8191b0();
    cSPUILayout lay;
    if (lay.Init(*key, true, 0x5b598fa)) {
        AssignRef(mpRHSWindowSet, lay.FindWindowByID(0x123ebe3, true));
        AssignRef(mpIconWindow, lay.FindWindowByID(0x123ebe4, true));
        void* w = lay.FindWindowByID(0x4332b60, true);
        if (w) {
            float* r = ((VF0)VT(w, 0x38))(w);
            mRayWidth = r[2] - r[0];
            AssignRef(mpLHSWindowSet, FUN_008067f0(w, -1));
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

// ---- vector helpers (element = cItemInfo, 0x4c bytes) ---------------------
struct ItemCopyBase { void Ctor(const char* src); };        // thiscall 0x00818650, ret 4
struct ItemAssign   { void Assign(const char* src); };      // thiscall 0x008186f0, ret 4
char* ext_00819e00(char* a, char* b, char* c);               // 0x00819e00 cdecl
int   ext_00819e60(char* a, char* b, char* c);               // 0x00819e60 cdecl
char* ext_008190f0(char* a, char* b, char* c);               // 0x008190f0 cdecl
char* ext_00819150(char* a, char* b, char* c);               // 0x00819150 cdecl
void* operator_new_f473a0(unsigned size, const char* name, int f, int d, const char* file, int line); // 0x00f473a0 cdecl
void  operator_delete_f47380(void* p);                       // 0x00f47380 cdecl
void* FUN_009512c0();                                        // 0x009512c0 cdecl
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

// @ 0x0081a510
static inline char* AllocItems(int cap) {
    return cap ? (char*)operator_new_f473a0(cap * 0x4c, (const char*)0x13f6b3c, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
}
void ItemVec::DoInsertValue(char* pos, const char* val) {
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

struct AutoRef {
    IRef* p;
    AutoRef(IRef* q) : p(q) { if (q) q->AddRef(); }
    ~AutoRef() { if (p) p->Release(); }
};

// AutoRefCount<T> member
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
// vtable setup of the final class runs after both bases are built
struct PieBase : IWinProcBase2, RefCountBase {
    PieBase() { vftable = (void**)0x1418fa4; vftable2 = (void**)0x1418f94; }
};

struct cSPUIPieMenu : PieBase {
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
    cSPUILayout mLay7c;    // +0x7c
    cSPUILayout mLay94;    // +0x94
    u8       bAC;          // +0xac
    RefPtr   mpCb;         // +0xb0
    float    f_b4, f_b8;   // +0xb4
    float    f_bc, f_c0;   // +0xbc
    u8       bC4, bC5;     // +0xc4

    cSPUILayout* L7c()  { return &mLay7c; }
    cSPUILayout* L94()  { return &mLay94; }

    void sub819360();                                    // 0x00819360
    void Show(Point2 pos, void* cb, int n);              // 0x00819ad0
    void reload_icons();                                 // 0x00819f90
    cSPUIPieMenu();                                      // 0x0081a1f0
    ~cSPUIPieMenu();                                     // 0x0081a2b0
    bool Init(const Key* k1, const Key* k2, char a3, void* parent, char a5); // 0x0081a350
    bool Shutdown();                                     // 0x0081a6d0
};

// @ 0x00819ad0
void cSPUIPieMenu::Show(Point2 pos, void* cb, int n) {
    AssignRef(mpCb.p, cb);
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
    Rect4 rc(mExt.l, mExt.t, mExt.r, mExt.b);
    rc.l += pt.x;
    rc.t += pt.y;
    rc.r += pt.x;
    rc.b += pt.y;
    void* par2 = ((VP0)VT(mpRootWin.p, 0x10))(mpRootWin.p);
    Rect4 sr(*(Rect4*)((VF0)VT(par2, 0x38))(par2));
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

// @ 0x00819f90
void cSPUIPieMenu::reload_icons() {
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
                AssignRef(mpWinA.p, q);
            } else if (id == 0x8096020) {
                AssignRef(mpWinB.p, q);
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
cSPUIPieMenu::cSPUIPieMenu()
    : mItemCount(0), mDirty(1), mMaxPerCircle(0), f64(0), f68(0), bAC(0), bC4(0), bC5(0) {
}

// @ 0x0081a2b0
cSPUIPieMenu::~cSPUIPieMenu() {
    vftable = (void**)0x1418fa4;
    vftable2 = (void**)0x1418f94;
}

// @ 0x0081a350
bool cSPUIPieMenu::Init(const Key* k1, const Key* k2, char a3, void* parent, char a5) {
    void* mem = FUN_009512d0(0x20c, 4, "UI/PieMenu", FUN_009512c0());
    void* w;
    if (mem) {
        ((WinMem*)mem)->Ctor();
        *(void**)mem = (void*)0x1414b10;
        w = (char*)mem + 4;
        *(void**)w = (void*)0x14431f8;
    } else {
        w = 0;
    }
    AssignRef(mpRootWin.p, w);
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

// @ 0x0081a6d0
bool cSPUIPieMenu::Shutdown() {
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
