// Slice s008189a0 (batch w2g7 #7), 32-bit MSVC 2008.
// cSPUIPieMenuItem / cSPUIPieMenu.

#include <math.h>
#include <string.h>
#include <wchar.h>

typedef unsigned int  u32;
typedef unsigned char u8;

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
struct IWindow {
    virtual void v00();
    virtual IWindow* v04();                          // 0x04
    virtual void v08();
    virtual ICmp* Cast(unsigned);                    // 0x0c
    virtual int v10();                               // 0x10
    virtual IWindow* v14();                          // 0x14
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual const Rect0* GetRect34();                // 0x34
    virtual const Rect0* GetArea();                     // 0x38
    virtual const wchar_t* GetCaption();             // 0x3c
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60();
    virtual void SetPos(float, float);               // 0x64
    virtual void v68();
    virtual void SetArea(const float*);              // 0x6c
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void v7c(int, int);                      // 0x7c
    virtual void SetCaption(const wchar_t*);         // 0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90();                              // 0x90
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual IWindow* va8();                          // 0xa8
    virtual void vac(); virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual P2 ToLocal(P2);                         // 0xc0
    virtual P2 ToGlobal(P2);                        // 0xc4
    virtual void vc8(); virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void vd8(); virtual void vdc(); virtual void ve0(); virtual void ve4();
    virtual void ve8(); virtual void vec();
    virtual IWindow* FindByID(unsigned, int);        // 0xf0
};
struct ICmp {
    virtual void AddRef();                           // 0x00
    virtual void Release();                          // 0x04
    virtual void v08(); virtual void v0c();
    virtual IWindow* GetWin();                       // 0x10
    virtual void v14(); virtual void v18();
    virtual void v1c(int);                           // 0x1c
};
struct IScr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual char GetPos(float*, float*);             // 0x10
    virtual char Valid();                            // 0x14
    virtual void Drop();                             // 0x18
};

static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline int Vi0(void* p, int off) {
    return ((int(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void* Vcp1(void* p, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}

extern "C" void SPUIHelpers_UpdateMouseFocus(int);
extern "C" void FUN_00819880_p();

struct cSPUIPieMenuItem {
    void**   vftable;          // +0x00
    u32      mID;              // +0x04
    IWindow* mpCurrentWindow;  // +0x08
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

    void SetIcon(int);          // 00818000
    void Update();              // 008189a0
    void MarkUnused();          // 00818950 (slice 6)
    bool sub8191b0();           // 008191b0
    void dtor819880();          // 00819880
    void SetOrientation(bool, bool); // 008192e0
    void Assign(const cSPUIPieMenuItem*); // 008186f0 (item copy)
    void SetText(const wchar_t*, bool);   // 00819220
};

// @ 0x008191b0
bool cSPUIPieMenuItem::sub8191b0() {
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

// @ 0x00819880
void cSPUIPieMenuItem::dtor819880() {
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

// @ 0x008192e0
void cSPUIPieMenuItem::SetOrientation(bool vert, bool update) {
    void** slot = vert ? &mpRHSWindowSet : &mpIconWindow;
    IWindow* w = (IWindow*)*slot;
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
        IWindow* parent = (IWindow*)mpParentWin;
        SetIcon(0);
        SetIcon((int)parent);
    }
}

// ---- cSPUIPieMenu (partial layout) ----------------------------------------
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

struct cSPUIPieMenu {
    char     pad_00[0xc];
    char*    mpBegin;       // +0xc
    char*    mpEnd;         // +0x10
    char     pad_14[0x20 - 0x14];
    int      mItemCount;    // +0x20 (used as a count in this build)
    IWindow* mpRootWin;    // +0x24
    char     pad_28[0x3c - 0x28];
    IWindow* mpCenterWin;  // +0x3c
    IWindow* mpBoundsWin;  // +0x40
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

// @ 0x00818c80
void cSPUIPieMenu::RemoveItem() {
    for (u32 i = 0; i < (u32)((mpEnd - mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)(mpBegin + i * 0x4c);
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

// ---- cSPUIPieMenu::cItemInfo: item (0x38) + rect + level, 0x4c bytes --------
struct ItemInfo {
    cSPUIPieMenuItem item;  // +0x00
    RectF rc;               // +0x38
    int   level;            // +0x48
};

// @ 0x008190f0
ItemInfo* CopyItemsFwd(ItemInfo* first, ItemInfo* last, ItemInfo* dest) {
    for (; first != last; ++dest, ++first) {
        dest->item.Assign(&first->item);
        dest->rc = first->rc;
        dest->level = first->level;
    }
    return dest;
}

// @ 0x00819150
ItemInfo* CopyItemsBack(ItemInfo* first, ItemInfo* last, ItemInfo* dest) {
    while (last != first) {
        --last;
        --dest;
        dest->item.Assign(&last->item);
        dest->rc = last->rc;
        dest->level = last->level;
    }
    return dest;
}

extern "C" void AnchorWindowToWindow(void* target, void* anchor, int flags, int zero);  // 0x00807340
struct DSub { float* GetPair40(float*, int); };   // 0x00830d60

// @ 0x008189a0
void cSPUIPieMenuItem::Update() {
    if (mFlags & 2) mFlags |= 1;
    if (mFlags & 1) {
        const wchar_t empty[1] = { 0 };
        IWindow* t0 = mpCurrentWindow->FindByID(0x122d76c, 1);
        const wchar_t* txt = t0->GetCaption();
        if (!txt) txt = empty;
        bool hasText = *txt != 0;
        IWindow* target = mpCurrentWindow->FindByID(0x122a5c7, 1);
        Rect0 rc;
        if (hasText) {
            IWindow* tw = mpCurrentWindow->FindByID(0x122d76c, 1);
            if (tw) {
                ICmp* cmp = (ICmp*)tw->Cast(0xf15f4bd);
                if (cmp) {
                    cmp->GetWin()->v7c(1, 0);
                    Rect0 ra;
                    { const Rect0* a = cmp->GetWin()->GetArea(); ra.l = a->l; ra.r = a->r; }
                    cmp->v1c(0);
                    int fl = (mpCurrentWindow != (IWindow*)mpRHSWindowSet ? 0x40 : 0x20) | 0x200;
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
        IWindow* extra = target->va8();
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

// @ 0x00819220
void cSPUIPieMenuItem::SetText(const wchar_t* text, bool update) {
    IWindow* w = ((IWindow*)mpRHSWindowSet)->FindByID(0x122d76c, 1);
    if (w) {
        const wchar_t empty[1] = { 0 };
        const wchar_t* s = text ? text : empty;
        const wchar_t* cur = w->GetCaption();
        if (wcscmp(s, cur) != 0) {
            w->SetCaption(s);
            IWindow* w2 = ((IWindow*)mpIconWindow)->FindByID(0x122d76c, 1);
            if (w2) w2->SetCaption(s);
            mFlags |= 1;
            if (update) Update();
        }
    }
}

// @ 0x00818d20
bool cSPUIPieMenu::DoMessage(void* /*win*/, Msg* msg) {
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
                IWindow* cw = mpCenterWin;
                const Rect0* r1 = cw->GetRect34();
                float hh = r1->b - r1->t;
                const Rect0* r2 = cw->GetRect34();
                cw->SetPos((mOffX + mScrX) - (r2->r - r2->l) * 0.5f,
                           (mOffY + mScrY) - hh * 0.5f);
            }
            const Rect0* r3 = mpCenterWin->GetArea();
            P2 o2 = mpCenterWin->ToLocal(P2((r3->r - r3->l) * 0.5f, (r3->b - r3->t) * 0.5f));
            IWindow* par2 = mpCenterWin->v14()->v04();
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

// @ 0x00819360
void cSPUIPieMenu::rebuild_layout() {
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
            IWindow* win = (IWindow*)((x > -1.5258789e-05f) ? it->item.mpIconWindow : it->item.mpRHSWindowSet);
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
                IWindow* parent = (IWindow*)it->item.mpParentWin;
                it->item.SetIcon(0);
                it->item.SetIcon((int)parent);
            }
            it->item.Update();
            it->level = ++lvl;
            IWindow* w = it->item.mpCurrentWindow;
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
