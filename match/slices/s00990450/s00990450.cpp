// EA::UTFWinControls::WinTreeView pick/draw/rebuild/scrollbar helpers and the TreeNode
// list walks (0x00990450-0x009913d0).  Object file UTFSpore_Win32/TreeView.obj.
//
// The 2008 PDB layout drifts from retail (+0x14 from mNodes on); offsets below are the
// retail ones read off the disassembly.  mColors[0..3] are floats (they are added to
// coordinates), mColors[4..8] are flag/int members.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>

// --- float constants the original uses as .rdata loads ------------------------------
extern const float g_1471064;  // 0.5f             0x01471064
extern const float g_1485720;  // 1.0f             0x01485720
extern const float g_1470f1c;  // 2.0f             0x01470f1c
extern const float g_1485378;  // 0.0f             0x01485378
extern const float g_13eecd8;  // 20.0f            0x013eecd8
extern const float g_13f4fd0;  // 4294967296.0f    0x013f4fd0  ((float)(unsigned) fixup)

double __cdecl iat_floor(double x);  // 0x011e0906

// --- the EASTL intrusive list (anchor-node ring) ------------------------------------
namespace eastl {
struct intrusive_list_node {
    intrusive_list_node* mpNext;
    intrusive_list_node* mpPrev;
};
template <typename T>
struct intrusive_list {
    intrusive_list_node mAnchor;
    class iterator {
    public:
        T* mpNode;
        iterator() : mpNode(0) {}
        explicit iterator(T* p) : mpNode(p) {}
        iterator& operator++()
        {
            mpNode = static_cast<T*>(mpNode->mpNext);
            return *this;
        }
        T* operator->() const { return mpNode; }
        T& operator*() const { return *mpNode; }
        bool operator==(const iterator& o) const { return mpNode == o.mpNode; }
        bool operator!=(const iterator& o) const { return mpNode != o.mpNode; }
    };
    iterator begin() { return iterator(static_cast<T*>(mAnchor.mpNext)); }
    iterator end() { return iterator(static_cast<T*>(&mAnchor)); }
    bool empty() const { return mAnchor.mpPrev == &mAnchor; }
};
}  // namespace eastl

namespace EA { namespace UTFWin {
struct Point2F { float x, y; };
struct RectF { float left, top, right, bottom; };
struct RenderCtx;
struct Batch2D {
    virtual void b0(); virtual void b1(int idx); virtual void b2(); virtual void b3();
    virtual void b4(); virtual void b5(float* colors); virtual void b6(); virtual void b7();
    virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11();
    virtual void b12(); virtual void b13();
    virtual void b14(float a, float b, float c, float d);        // +0x38
};
}}  // namespace EA::UTFWin

namespace EA { namespace UTFWinControls {

struct TreeNode;
struct WinTreeView;

struct IDrawable {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(void* ctx, void* rect, void* state);         // +0x10
};
struct IWinScrollbar {
    virtual void x0();
    virtual void x1();
    virtual void x2();
    virtual void x3();
    virtual void* x4();                                          // +0x10  ::GetWindow/owner
    virtual void x5(int mode);                                   // +0x14
    virtual void x6();
    virtual void x7();
    virtual void x8();
    virtual void x9();
    virtual void x10();
    virtual void x11();
    virtual void x12();
    virtual void x13();
    virtual void x14();
    virtual void x15();
    virtual void x16();
    virtual void x17();
    virtual void x18();
    virtual void x19();
    virtual void x20();
    virtual void x21();
    virtual void x22();
    virtual void x23(void* drawable);                            // +0x5c
    virtual void x24();
    virtual void x25();
    virtual void x26();
    virtual void x27();
    virtual void x28();
    virtual void x29();
    virtual void x30();
    virtual void x31(int attr, int value);                       // +0x7c
};
struct IScrollbarDrawable {
    virtual void x0();                                           // +0x0  ::AddRef
    virtual void x1();                                           // +0x4  ::Release
    virtual void y2();
    virtual void* y3();                                           // +0xc
    virtual void* y4();                                          // +0x10  ::GetWindow
    virtual void* y5();                                          // +0x14
};

// AutoRefCount<T>: single pointer plus the intrusive AddRef/Release protocol.
template <class T>
struct AutoRefCount {
    T* mpObject;                                                 // +0
    T* operator=(T* p)
    {
        if (p)
            p->x0();
        T* old = mpObject;
        mpObject = p;
        if (old)
            old->x1();
        return p;
    }
};

// 0x14 bytes: scrollbar @0, drawable @4, enabled @8, preferred size @0xc/@0x10
struct ScrollbarState {
    AutoRefCount<IWinScrollbar> mScrollbar;                      // +0
    AutoRefCount<IScrollbarDrawable> mDrawable;                  // +4
    int mEnabled;                                                // +8
    float mPreferredX;                                           // +0xc
    float mPreferredY;                                           // +0x10
};

struct TreeNodeBase {                                            // vptr + 2 words = 0xc
    virtual void n0();
    virtual void n1();
    virtual void n2();
    void* pad0;
    void* pad1;
};

struct TreeNode : TreeNodeBase, eastl::intrusive_list_node {
    WinTreeView* mpTreeView;                                     // +0x14
    TreeNode* mpParent;                                          // +0x18
    eastl::intrusive_list<TreeNode> mChildren;                   // +0x1c
    int mVisibleLineCount;                                       // +0x24
    unsigned int mFlags;                                         // +0x28
    unsigned int pad2[2];                                        // +0x2c
    unsigned int mCaption[4];                                    // +0x34
    void* mpIcon;                                                // +0x44
    void* mpUserData;                                            // +0x48
    void* pad3;                                                  // +0x4c

    void Attach(WinTreeView* tree);                              // 0x009911e0
    void Detach();                                               // 0x00991230 (other slice)
    void CalcVisibleLines();                                     // 0x00991280
    int CollectVisible(TreeNode** out, unsigned int count);      // 0x009912e0
};

// The IWinManager handed back by IWindow slot +0x14.
struct IWinManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14();
    virtual void m15(); virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20();
    virtual void m21(void* child);                               // +0x54
};

// The object IWinScrollbar::slot4 hands back; it is a window-like thing whose
// slot +0x7c sets (attribute, value).
struct IWinScrollbarExt {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4();
    virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9();
    virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14();
    virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
    virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24();
    virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29();
    virtual void e30();
    virtual void e31(int attr, int value);                       // +0x7c
};

struct IWindow {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4();
    virtual IWinManager* w5();                                   // +0x14
    virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual unsigned int w10();                                  // +0x28
    virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24();
    virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void w30();
    virtual void w31(int a, int b);                              // +0x7c
    virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
    virtual void w36();                                          // +0x90
    virtual void w37(); virtual void w38(); virtual void w39(); virtual void w40();
    virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44();
    virtual void w45();
    virtual void w46(void* window);                              // +0xb8
    virtual void w47(); virtual void w48(); virtual void w49(); virtual void w50(); virtual void w51();
    virtual void w52(); virtual void w53();
    virtual void w54(void* child);                               // +0xd8
    virtual void w55();
    virtual void w56(void* drawable);                            // +0xe0
};
// WinTreeView's own (custom-window) vtable: node drawing lives at +0x88 / +0x8c.
struct CustomWindowBase {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14();
    virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24();
    virtual void c25(); virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29();
    virtual void c30(); virtual void c31(); virtual void c32(); virtual void c33();
    virtual void c34(void* ctx, TreeNode* node, EA::UTFWin::Point2F* pt);    // +0x88
    virtual void c35(void* ctx, TreeNode* node, EA::UTFWin::Point2F* pt);    // +0x8c
};

struct WinTreeView : CustomWindowBase {
    IWindow mWindow;                                             // +0x4
    unsigned int pad0[0x20];                                     // +0x8 .. 0x88
    float mLocalX0;                                              // +0x88
    float mLocalY0;                                              // +0x8c
    float mLocalX1;                                              // +0x90
    float mLocalY1;                                              // +0x94
    unsigned int pad1[0x50];                                     // +0x98 .. 0x1d8
    float mLineOff0;                                             // +0x1d8
    float mLineOff1;                                             // +0x1dc
    IDrawable* mpBackground;                                     // +0x1e0
    unsigned int pad2[0xb];                                      // +0x1e4 .. 0x210
    bool mInited;                                                // +0x210
    unsigned char pad3[3];
    TreeNode mNodes;                                             // +0x214
    unsigned int pad4[4];                                        // +0x264 .. 0x274
    float mColors[4];                                            // +0x274  geometry floats
    unsigned int mColorFlags[5];                                 // +0x284  .. 0x298
    unsigned int mItemHeight;                                    // +0x298
    void* mpIconDrawable;                                        // +0x29c
    void* mpIconDrawableRef;                                     // +0x2a0
    unsigned int mIndentWidth;                                   // +0x2a4
    unsigned int mLineWidth;                                     // +0x2a8
    unsigned int mLineIndent;                                    // +0x2ac
    unsigned int mIconSpacing;                                   // +0x2b0
    IDrawable* mpExpanderDrawable;                               // +0x2b4
    int mIndentY;                                                // +0x2b8
    int mRowHeightIn;                                            // +0x2bc
    int mTopRow;                                                 // +0x2c0
    unsigned int pad5;                                           // +0x2c4
    float mExpanderW;                                            // +0x2c8
    float mExpanderH;                                            // +0x2cc
    float mRowHeight;                                            // +0x2d0
    unsigned int pad6[6];                                        // +0x2d4 .. 0x2ec
    TreeNode* mPickNode;                                         // +0x2ec
    unsigned int mPickType;                                      // +0x2f0
    ScrollbarState mScrollbars[2];                               // +0x2f4  (0x28)
    float mScrollX;                                              // +0x31c
    float mScrollY;                                              // +0x320
    float mVirtualTop;                                           // +0x324
    float mVirtualSize;                                          // +0x328
    unsigned int pad7[9];                                        // +0x32c

    TreeNode* PickRow(float* pY);                                // 0x00990450
    bool OnMouseMove(float x, float y, float z);                 // 0x00990530
    void DrawTreeLines(void* ctx, float y, float* p);            // 0x009906b0
    bool OnRebuild(void* ctx);                                   // 0x00990a90
    void Refresh();                                              // 0x00990f80
    void CreateScrollbar(int which);                             // 0x00990ff0
};

// The CustomWindow methods that live outside this slice.
struct TreeViewExtra {
    void CalculateRowHeight();                                   // 0x0098f620
    void FocusChanged();                                         // 0x0098fd20
};

struct IWinTextEdit {                                            // WinScrollbar's real type
    unsigned int pad[0x83];
};

void* __cdecl FUN_009512c0();                                                        // 0x009512c0
void* __cdecl FUN_009512d0(unsigned int size, unsigned int align, const char* name, void* a);  // 0x009512d0
void* __cdecl WinScrollbarCtor(void* mem);                                           // 0x00983790
void* __cdecl ScrollbarDrawableCtor(void* mem);                                      // 0x009838a0
void __cdecl RenderCtx_Begin2D(void* ctx, void* mode);                               // inside
void __cdecl RenderCtx_End2D(void* ctx);                                             // inside

// Thin thiscall wrappers so the calls land on the right symbols/registers.
struct RenderCtxShim {
    EA::UTFWin::Batch2D* Begin2D(void* mode);                    // 0x0095bc10
    void End2D();                                                // 0x0095bb20
};

struct BasicFactory_TreeExpanderDrawable {
    void* CreateInstance(void* unused, void* alloc);             // 0x00991380
};

}}  // namespace EA::UTFWinControls

using EA::UTFWinControls::TreeNode;
using EA::UTFWinControls::WinTreeView;
using EA::UTFWinControls::TreeViewExtra;
using EA::UTFWinControls::BasicFactory_TreeExpanderDrawable;
using EA::UTFWinControls::IWindow;
using EA::UTFWinControls::IWinManager;
using EA::UTFWinControls::IDrawable;
using EA::UTFWinControls::IWinScrollbar;
using EA::UTFWinControls::IScrollbarDrawable;
using EA::UTFWinControls::RenderCtxShim;

extern void* g_vtbl_13fa72c;      // 0x013fa72c
extern void* g_vtbl_1445c04;      // 0x01445c04
extern void* g_vtbl_1445bec;      // 0x01445bec

// @ 0x00990450
TreeNode* WinTreeView::PickRow(float* pY)
{
    if (mRowHeight == 0.0f)
        return 0;
    TreeNode* pParent = &mNodes;
    eastl::intrusive_list<TreeNode>::iterator it = pParent->mChildren.begin();
    while (it != pParent->mChildren.end()) {
        int n = it->mVisibleLineCount;
        float h = (float)(unsigned int)n * mRowHeight;
        if (*pY >= h) {
            *pY -= h;
            ++it;
            continue;
        }
        if (*pY < mRowHeight)
            return &*it;
        if (it->mChildren.empty())
            return &*it;
        if (((it->mFlags >> 1) & 1) == 0)
            return &*it;
        *pY -= mRowHeight;
        pParent = &*it;
        it = pParent->mChildren.begin();
    }
    return 0;
}

// @ 0x00990530
bool WinTreeView::OnMouseMove(float x, float y, float z)
{
    float fy = mScrollY - mColors[1] + y;
    (void)z;
    TreeNode* node = PickRow(&fy);
    unsigned int pick = 0;
    if (node) {
        int level = 0;
        for (TreeNode* p = node->mpParent; p; p = p->mpParent)
            ++level;
        --level;
        if ((mColorFlags[0] & 2) != 0)
            ++level;
        float indent = (float)(unsigned int)(mIndentY * level);
        float fx = x - (indent + mColors[0]);
        if (mpExpanderDrawable) {
            float ew = mExpanderW;
            float base = (float)(unsigned int)mTopRow;
            float eh = mExpanderH;
            float x1 = (base - (float)(unsigned int)mIndentY) - ew * 0.5f;
            float hw = (mRowHeight - eh) * 0.5f;
            if ((x1 - 1.0f <= fx && hw - 1.0f <= fy) &&
                (fx < (ew + x1) + 1.0f) && (fy < (eh + hw) + 1.0f))
                pick = 1;
        }
        if (fx > 0.0f)
            pick = 2;
    }
    if (node != mPickNode || pick != mPickType) {
        mPickNode = node;
        mWindow.w36();
        mPickType = pick;
    }
    return false;
}

// @ 0x009906b0
void WinTreeView::DrawTreeLines(void* pCtx, float y, float* p)
{
    float topF = (float)(unsigned int)mTopRow;
    float rh = (float)(unsigned int)mRowHeightIn;
    float bot = p[3];
    float half = (float)iat_floor((double)(rh * 0.5f));
    float base = (float)iat_floor((double)((bot - p[1]) * 0.5f));
    float l = p[0];
    if ((mColorFlags[0] & 1) != 0) {
        EA::UTFWin::Batch2D* b = ((RenderCtxShim*)pCtx)->Begin2D(0);
        float y1 = base - half;
        float y2 = y1 + rh;
        b->b1(mLineWidth);
        float indent = (float)(unsigned int)mIndentY;
        float yRun = base;
        eastl::intrusive_list<TreeNode>::iterator it = mNodes.mChildren.begin();
        eastl::intrusive_list<TreeNode>::iterator end = mNodes.mChildren.end();
        while (it != end) {
            b->b14(l + y2, base + base + y, (indent + l) - 2.0f, yRun + rh + y);
            yRun += (float)(unsigned int)it->mVisibleLineCount * mRowHeight;
            ++it;
        }
        b->b14(l + (topF - half), (base - half) + 2.0f, l + y2, yRun + y);
    }
    if (mpExpanderDrawable != 0) {
        float ex = p[0];
        float ey = p[3];
        float ew = (float)iat_floor((double)(mExpanderW * 0.5f));
        float eh = (float)iat_floor((double)(mExpanderH * 0.5f));
        float exs = (ex + topF) - ew;
        float eys = (ey + base) - eh;
        float yRun = base;
        eastl::intrusive_list<TreeNode>::iterator it = mNodes.mChildren.begin();
        eastl::intrusive_list<TreeNode>::iterator end = mNodes.mChildren.end();
        while (it != end) {
            if (mColors[3] > yRun) {
                if (!it->mChildren.empty() && yRun + mRowHeight > mColors[1]) {
                    EA::UTFWin::RectF rect;
                    rect.left = exs;
                    rect.top = eys + yRun;
                    rect.right = (ex + mExpanderW) + yRun;
                    rect.bottom = yRun + mExpanderH;
                    unsigned int state = 0;
                    if (mPickNode == &*it && mPickType == 1)
                        state = 2;
                    if ((it->mFlags & 2) != 0)
                        state |= 8;
                    mpExpanderDrawable->d4(pCtx, &rect, &state);
                }
            }
            yRun += (float)(unsigned int)it->mVisibleLineCount * mRowHeight;
            ++it;
        }
    }
}

// @ 0x00990a90
bool WinTreeView::OnRebuild(void* pCtx)
{
    RenderCtxShim* ctx = (RenderCtxShim*)pCtx;
    EA::UTFWin::Batch2D* b = ctx->Begin2D(0);
    float rw = mLocalX1 - mLocalX0;
    float rh = mLocalY1 - mLocalY0;
    IWinManager* mgr = mWindow.w5();
    if (mgr)
        mgr->m21(0);
    unsigned int flags = mWindow.w10();
    if (mpBackground != 0) {
        int state[2] = {0, 0};
        float rect[4] = {0.0f, 0.0f, mLineOff0, mLineOff1};
        if (((flags >> 1) & 1) == 0)
            state[0] = 1;
        else
            state[0] = 3;
        mpBackground->d4(pCtx, rect, state);
    } else if (mColorFlags[2] != 0) {
        b->b1(mColorFlags[2]);
        b->b14(0.0f, 0.0f, rw, rh);
    }
    ((TreeViewExtra*)this)->CalculateRowHeight();
    if (mRowHeight == 0.0f)
        return true;

    b->b5(mColors);

    float x0 = mColors[0] - mScrollX;
    float y0 = mColors[1] - mScrollY;
    float right = mColors[2] - mScrollX;
    float xind = x0;
    if ((mColorFlags[0] & 2) != 0) {
        if (!mNodes.mChildren.empty())
            c34(pCtx, &mNodes, 0);
        xind = (float)(unsigned int)mIndentY + x0;
    }

    TreeNode* parent = &mNodes;
    eastl::intrusive_list<TreeNode>::iterator it = parent->mChildren.begin();
    float y = y0;
    int level = 0;
    while (it != parent->mChildren.end()) {
        if (mColors[3] <= y)
            break;
        if (y + mRowHeight > mColors[1]) {
            float indent = (float)(unsigned int)(mIndentY * level);
            EA::UTFWin::Point2F pt;
            pt.x = indent + xind;
            pt.y = y;
            if (!it->mChildren.empty() && ((it->mFlags >> 1) & 1) != 0)
                c34(pCtx, &*it, &pt);
            c35(pCtx, &*it, &pt);
        }
        y += mRowHeight;
        if (!it->mChildren.empty() && ((it->mFlags >> 1) & 1) != 0) {
            parent = &*it;
            it = parent->mChildren.begin();
            ++level;
            continue;
        }
        ++it;
        while (it == parent->mChildren.end() && parent->mpParent != 0) {
            TreeNode* up = parent;
            parent = parent->mpParent;
            it = eastl::intrusive_list<TreeNode>::iterator(
                static_cast<TreeNode*>(up->mpNext));
            --level;
        }
    }
    ctx->End2D();
    return true;
}

// @ 0x00990f80
void WinTreeView::Refresh()
{
    if ((mWindow.w10() & 8) != 0) {
        mWindow.w31(8, 0);
        ((TreeViewExtra*)this)->CalculateRowHeight();
        int n = mNodes.mVisibleLineCount - 1;
        mVirtualTop = 0.0f;
        mVirtualSize = (float)(unsigned int)n * mRowHeight;
        ((TreeViewExtra*)this)->FocusChanged();
    }
}

// @ 0x00990ff0
void WinTreeView::CreateScrollbar(int which)
{
    ScrollbarState* sb = &mScrollbars[which];
    if (sb->mEnabled == 0) {
        if (sb->mDrawable.mpObject == 0)
            return;
        IWinScrollbarExt* w = (IWinScrollbarExt*)sb->mDrawable.mpObject->y4();
        mWindow.w56(w);
        IScrollbarDrawable* d = sb->mDrawable.mpObject;
        if (d == 0)
            return;
        sb->mDrawable.mpObject = 0;
        d->x1();
        return;
    }
    if (sb->mScrollbar.mpObject == 0) {
        void* mem = FUN_009512d0(0x2d0, 8, "UTFWin/WinTextEdit/Scrollbar", FUN_009512c0());
        IWinScrollbar* w = 0;
        if (mem) {
            void* r = WinScrollbarCtor(mem);
            if (r)
                w = (IWinScrollbar*)((char*)r + 0x20c);
        }
        sb->mScrollbar = w;
        ((IWinScrollbarExt*)sb->mScrollbar.mpObject->x4())->e31(0x200, 1);
        mWindow.w56(sb->mScrollbar.mpObject->x4());
        sb->mScrollbar.mpObject->x5(which == 1 ? 2 : 1);
    }
    if (sb->mDrawable.mpObject != 0) {
        void* src;
        if (sb->mDrawable.mpObject != 0)
            src = sb->mDrawable.mpObject->y3();
        else
            src = 0;
        sb->mScrollbar.mpObject->x23(src);
    } else {
        void* mem = FUN_009512d0(0x2c, 4, "UTFWin/WinTextEdit/ScrollbarDrawable", FUN_009512c0());
        void* d = 0;
        if (mem) {
            d = ScrollbarDrawableCtor(mem);
        }
        sb->mDrawable = (IScrollbarDrawable*)d;
    }
    sb->mPreferredX = 20.0f;
    sb->mPreferredY = 20.0f;
    int pad[2] = {0x16, 0};
    if (mWindow.w5()) {
        IWinScrollbarExt* a = (IWinScrollbarExt*)sb->mScrollbar.mpObject->x4();
        int v = *(int*)a;
        mWindow.w5();
        (void)v;
        (void)pad;
    }
}

// @ 0x009911e0
void TreeNode::Attach(WinTreeView* tree)
{
    WinTreeView* pTreeView = tree;
    eastl::intrusive_list<TreeNode>::iterator end = mChildren.end();
    mpTreeView = pTreeView;
    eastl::intrusive_list<TreeNode>::iterator it = mChildren.begin();
    while (it != end) {
        it->Attach(pTreeView);
        ++it;
    }
}

// @ 0x00991280
void TreeNode::CalcVisibleLines()
{
    for (TreeNode* n = this; n; n = n->mpParent) {
        eastl::intrusive_list<TreeNode>::iterator end = n->mChildren.end();
        n->mVisibleLineCount = 1;
        if ((n->mFlags & 2) != 0) {
            eastl::intrusive_list<TreeNode>::iterator it = n->mChildren.begin();
            while (it != end) {
                n->mVisibleLineCount += it->mVisibleLineCount;
                ++it;
            }
        }
    }
}

// @ 0x009912e0
int TreeNode::CollectVisible(TreeNode** out, unsigned int count)
{
    int total = 0;
    if (mpParent != 0 && (mFlags & 1) != 0) {
        total = 1;
        if (count != 0) {
            --count;
            *out = this;
        }
    }
    eastl::intrusive_list<TreeNode>::iterator it = mChildren.begin();
    eastl::intrusive_list<TreeNode>::iterator end = mChildren.end();
    while (it != end) {
        unsigned int k = it->CollectVisible(out, count);
        unsigned int take = count < k ? count : k;
        total += k;
        count -= take;
        out += take;
        ++it;
    }
    return total;
}

// @ 0x00991380
void* BasicFactory_TreeExpanderDrawable::CreateInstance(void* unused, void* alloc)
{
    (void)unused;
    if (!alloc)
        alloc = FUN_009512c0();
    unsigned int* p = (unsigned int*)FUN_009512d0(
        0xc, 4, "UTFWin/EA::UTFWinControls::TreeExpanderDrawable", alloc);
    if (p) {
        p[1] = (unsigned int)&g_vtbl_13fa72c;
        p[2] = 0;
        p[0] = (unsigned int)&g_vtbl_1445c04;
        p[1] = (unsigned int)&g_vtbl_1445bec;
    }
    return p;
}

