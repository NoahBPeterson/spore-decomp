// EA::UTFWinControls::TreeNode / WinTreeView node-list, flag, selection and factory
// helpers, plus WatchGraph (0x009913d0-0x00992180).  Object file
// UTFSpore_Win32/TreeView.obj.
//
// Offsets follow the retail image (the 2008 PDB drifts from +0x14 on).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>
#include <math.h>
#pragma intrinsic(fabs)

// --- float constants the original loads from .rdata --------------------------------
extern const float g_1470f1c;  // 2.0f            0x01470f1c
extern const float g_1471064;  // 0.5f            0x01471064
extern const float g_1485720;  // 1.0f            0x01485720
extern const float g_13f18d4;  // 1e-07f          0x013f18d4
extern const float g_14853e0;  // 0.0f            0x014853e0
extern const float g_13f4fd0;  // 4294967296.0f   0x013f4fd0  ((float)(unsigned) fixup)
extern const float g_13f9428;  // 0.001f          0x013f9428

double __cdecl iat_floor(double x);                       // 0x011e0906
void* __cdecl operator_new(unsigned int size);            // 0x011e073e
void __cdecl FUN_00f47380(void* p);                       // 0x00f47380  operator delete
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void __cdecl FUN_011e0744(void* dst, void* src, unsigned int n);   // 0x011e0744 memset/memmove

extern const wchar_t gEmptyString16[];                    // 0x01667bac

// --- vtable / class-layout immediates (kept extern so they emit as relocations) ----
extern void* g_vtbl_1445c58;   // 0x01445c58  TreeNode::vftable (IUnknown32 subobject)
extern void* g_vtbl_1445c54;   // 0x01445c54  TreeNode::vftable (RefCount subobject)
extern void* g_vtbl_13ef094;   // 0x013ef094  GmeRefCount::vftable
extern void* g_vtbl_13eb938;   // 0x013eb938  GmeEditorResBase::vftable
extern void* g_vtbl_1445b68;   // 0x01445b68  (Window node subobject)
extern void* g_vtbl_1445e60;   // 0x01445e60  WinTreeView::vftable
extern void* g_vtbl_1445d40;   // 0x01445d40  WinTreeView::vftable (IWindow subobject)
extern void* g_vtbl_1445cb8;   // 0x01445cb8  WinTreeView node-companion vftable
extern void* g_vtbl_1446078;   // 0x01446078  WatchGraph::vftable
extern void* g_vtbl_1445f58;   // 0x01445f58  WatchGraph::vftable (IWindow subobject)
extern void* g_rdata_1667bae;  // 0x01667bae  (empty-string terminator)

extern void* FUN_00960020_arg(int x);
void FUN_00960020(int cursor);                                  // 0x00960020  SetCursor
void FUN_0093a560(void* stopwatch, int units, bool a);          // 0x0093a560  Stopwatch ctor
unsigned int __stdcall GetDoubleClickTime();                    // 0x011765e8
void FUN_00962740(void* p);                                     // 0x00962740
void* FUN_00962a10(void* p);                                    // 0x00962a10
void FUN_0095bc10_begin2d(void* ctx, void* mode);
void FUN_0095bb20_end2d(void* ctx);

namespace eastl {
struct intrusive_list_node {
    intrusive_list_node* mpNext;
    intrusive_list_node* mpPrev;
};
template <typename T>
class intrusive_list { public:
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
    // raw accessors mirroring the original's `&mChildren` / `mAnchor.mpNext` forms
    intrusive_list_node* rawAnchor() { return &mAnchor; }
    intrusive_list_node* firstRaw() { return mAnchor.mpNext; }
    void pushPrev(intrusive_list_node* node, intrusive_list_node* pos);
};
}  // namespace eastl

namespace EA { namespace UTFWin {
struct Point2F { float x, y; };
struct RectF { float left, top, right, bottom; };
struct RenderCtx;
struct Batch2D {
    virtual void b0(); virtual void b1(int idx); virtual void b2(); virtual void b3();
    virtual void b4(); virtual void b5(float* colors); virtual void b6(); virtual void b7();
    virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12();
    virtual void b13(float a, float b, float c, float d, float e);   // +0x1c
    virtual void b14(float a, float b, float c, float d);           // +0x38
};
void Begin2D(RenderCtx* ctx, void* mode);                      // 0x0095bc10
void End2D(RenderCtx* ctx);                                    // 0x0095bb20
Batch2D* Begin2D_batch(RenderCtx* ctx, void* mode);            // 0x0095bc10
}}

namespace EA { namespace UTFWinControls {

class TreeNode;
class WinTreeView;

struct IDrawable {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(void* ctx, void* rect, void* state);        // +0x10
};
struct IUnknown32 {
    virtual void u0();                                         // +0x0 AddRef
    virtual void u1();                                         // +0x4 Release
    virtual void* u2();                                        // +0x8
    virtual void* u3(int id);                                  // +0xc QueryInterface
};
struct IWinScrollbarExt {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4();
    virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9();
    virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14();
    virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
    virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24();
    virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29();
    virtual void e30();
    virtual void e31(int a, int b);                            // +0x7c
};
class IWinScrollbar { public:
    virtual void x0(); virtual void x1(); virtual void x2(); virtual void x3();
    virtual void* x4();                                        // +0x10
    virtual void x5(int mode);                                 // +0x14
    virtual void x6(); virtual void x7(); virtual void x8(); virtual void x9(); virtual void x10();
    virtual void x11(); virtual void x12(); virtual void x13(); virtual void x14(); virtual void x15();
    virtual void x16(); virtual void x17(); virtual void x18(); virtual void x19(); virtual void x20();
    virtual void x21(); virtual void x22();
    virtual void x23(void* d);                                 // +0x5c
    virtual void x24(); virtual void x25(); virtual void x26(); virtual void x27(); virtual void x28();
    virtual void x29(); virtual void x30();
    virtual void x31(int a, int v);                            // +0x7c
};
class IScrollbarDrawable { public:
    virtual void x0(); virtual void x1();                      // AddRef/Release
    virtual void y2(); virtual void* y3();                     // +0xc
    virtual void* y4(); virtual void* y5();
};

template <class T>
struct AutoRefCount {
    T* mpObject;                                               // +0
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
    AutoRefCount<IWinScrollbar> mScrollbar;                     // +0
    AutoRefCount<IScrollbarDrawable> mDrawable;                 // +4
    int mEnabled;                                               // +8
    float mPreferredX;                                          // +0xc
    float mPreferredY;                                          // +0x10
};

struct TreeNodeBase {                                           // vptr + 2 words = 0xc
    virtual void n0(); virtual void n1(); virtual void n2();
    virtual void n3(); virtual void n4(); virtual void n5();
    virtual void n6(unsigned int oldFlags, unsigned int newFlags);   // +0x18
    void* pad0;
    void* pad1;
};

class WinTreeView;
class TreeNode : public TreeNodeBase, public eastl::intrusive_list_node { public:
    WinTreeView* mpTreeView;                                    // +0x14
    TreeNode* mpParent;                                         // +0x18
    eastl::intrusive_list<TreeNode> mChildren;                  // +0x1c
    int mVisibleLineCount;                                      // +0x24
    unsigned int mFlags;                                        // +0x28
    unsigned int mTextStyle;                                    // +0x2c
    unsigned int mNodeID;                                       // +0x30
    wchar_t* mCaptionBegin;                                     // +0x34
    wchar_t* mCaptionEnd;                                       // +0x38
    wchar_t* mCaptionCap;                                       // +0x3c
    IDrawable* mpIcon;                                          // +0x44
    IUnknown32* mpUserData;                                     // +0x48

    void Attach(WinTreeView* tree);                             // 0x009911e0
    void Detach();                                              // 0x00991230
    void CalcVisibleLines();                                    // 0x00991280
    int CollectVisible(TreeNode** out, unsigned int count);     // 0x009912e0
    void InnerChildRemoveAllRecursive();                        // 0x00990040

    ~TreeNode();                                                // 0x00991410
    bool IsExpanded();                                          // 0x00991470
    void SetFlag(unsigned int flag, bool on);                   // 0x00991490
    void SetFlagRecursive(unsigned int flag, bool on);          // 0x00991520
    void ChildInsert(eastl::intrusive_list_node* pos, TreeNode* child);  // 0x00991580
    void ChildRemoveAll();                                      // 0x00991600
};

struct IWindow {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4();
    virtual void* w5();                                         // +0x14
    virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual unsigned int w10();                                 // +0x28
    virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24();
    virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void w30();
    virtual void w31(int a, int b);                             // +0x7c
    virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
    virtual void w36();                                         // +0x90
    virtual void w37(); virtual void w38(); virtual void w39(); virtual void w40();
    virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44();
    virtual void w45();
    virtual void w46(void* w);                                  // +0xb8
    virtual void w47(); virtual void w48(); virtual void w49(); virtual void w50(); virtual void w51();
    virtual void w52(); virtual void w53();
    virtual void w54(void* d);                                  // +0xd8
    virtual void w55();
    virtual void w56(void* d);                                  // +0xe0
};
struct IWinManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14();
    virtual void m15(); virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20();
    virtual void m21(void* c);                                  // +0x54
};

// WinTreeView's own (custom-window) vtable: node drawing at +0x88 / +0x8c.
struct CustomWindowBase {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14();
    virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24();
    virtual void c25(); virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29();
    virtual void c30(); virtual void c31(); virtual void c32(); virtual void c33();
    virtual void c34(void* ctx, TreeNode* node, EA::UTFWin::Point2F* pt);   // +0x88
    virtual void c35(void* ctx, TreeNode* node, EA::UTFWin::Point2F* pt);   // +0x8c
};

struct TreeViewExtra {
    void CalculateRowHeight();                                  // 0x0098f620
    void FocusChanged();                                        // 0x0098fd20
    void CalculateVisibleArea();                                // 0x0098fbe0
};

class WinTreeView : public CustomWindowBase { public:
    IWindow mWindow;                                            // +0x4
    unsigned int pad0[0x20];                                    // +0x8 .. 0x88
    float mLocalX0;                                             // +0x88
    float mLocalY0;                                             // +0x8c
    float mLocalX1;                                             // +0x90
    float mLocalY1;                                             // +0x94
    unsigned int pad1[0x50];                                    // +0x98 .. 0x1d8
    float mLineOff0;                                            // +0x1d8
    float mLineOff1;                                            // +0x1dc
    IDrawable* mpBackground;                                    // +0x1e0
    unsigned int pad2[0xb];                                     // +0x1e4 .. 0x210
    bool mInited;                                               // +0x210
    unsigned char pad3[3];
    TreeNode mNodes;                                            // +0x214
    unsigned int pad4[4];                                       // +0x264 .. 0x274
    float mColors[4];                                           // +0x274
    unsigned int mColorFlags[5];                                // +0x284  .. 0x298
    unsigned int mItemHeight;                                   // +0x298
    void* mpIconDrawable;                                       // +0x29c
    void* mpIconDrawableRef;                                    // +0x2a0
    unsigned int mIndentWidth;                                  // +0x2a4
    unsigned int mLineWidth;                                    // +0x2a8
    unsigned int mLineIndent;                                   // +0x2ac
    unsigned int mIconSpacing;                                  // +0x2b0
    IDrawable* mpExpanderDrawable;                              // +0x2b4
    int mIndentY;                                               // +0x2b8
    int mRowHeightIn;                                           // +0x2bc
    int mTopRow;                                                // +0x2c0
    unsigned int pad5;                                          // +0x2c4
    float mExpanderW;                                           // +0x2c8
    float mExpanderH;                                           // +0x2cc
    float mRowHeight;                                           // +0x2d0
    unsigned int pad6[1];                                       // +0x2d4
    void* mpSelectedNodesBegin;                                 // +0x2d8
    unsigned int pad6b[3];                                      // +0x2dc .. 0x2e8
    TreeNode* mPickNode;                                        // +0x2ec
    unsigned int mPickType;                                     // +0x2f0
    ScrollbarState mScrollbars[2];                              // +0x2f4
    float mScrollX;                                             // +0x31c
    float mScrollY;                                             // +0x320
    float mVirtualTop;                                          // +0x324
    float mVirtualSize;                                         // +0x328
    unsigned int pad7[1];                                       // +0x32c
    unsigned int mAutoScroll1;                                  // +0x330
    unsigned int pad8[5];                                       // +0x334 .. 0x348
    unsigned int mAutoScroll2;                                  // +0x348
    unsigned int pad9[5];                                       // +0x34c .. 0x360
    float mDoubleClickInterval;                                 // +0x360

    WinTreeView();                                              // 0x00991a70
    void Refresh();                                             // 0x00990f80
    void CreateScrollbar(int which);                            // 0x00990ff0

    int GetSelection(int which);                                // 0x009913d0
    void InvalidateLayout();                                    // 0x009917b0
    void SetBorders(EA::UTFWin::RectF* r);                      // 0x009917f0
    void ClearSelection();                                      // 0x00991860
    void OnMouseDown();                                         // 0x009918b0
    void SetScrollbarDrawable(int which, void* p);              // 0x00991930
    void SetScrollbarEnabled(int which, int v);                 // 0x00991990
    ~WinTreeView();                                             // 0x00991df0
};

class BasicFactory_TreeNode { public:
    void* CreateInstance(void* unused, void* alloc);            // 0x009919e0
};

// TreeNodeListMarshaller<TreeNode> and its SerUpdate helper.
struct TreeNodeListMarshaller {
    bool Read(void* a, void* container, void* b);               // 0x00991710
};

// WatchGraph: a window that plots per-channel history.
class WatchGraph : public CustomWindowBase { public:
    IWindow mWindow;                                            // +0x4
    unsigned int pad0[0x81];                                    // +0x8 .. 0x20c
    eastl::intrusive_list_node mChannels;                       // +0x20c
    float mSample0;                                             // +0x214
    float mSample1;                                             // +0x218
    bool mbAutoScale;                                           // +0x21c
    bool mbClip;                                                // +0x21d
    unsigned char pad1[2];                                      // +0x21e .. 0x220
    unsigned int mHistorySize;                                  // +0x220
    unsigned int mHistoryCount;                                 // +0x224

    WatchGraph();                                               // 0x00991ff0
    void Clear();                                               // 0x00991f90
    void SetHistorySize(unsigned int n);                        // 0x00992080
    void OnAreaChanged(EA::UTFWin::RectF* r);                   // 0x00992140
    bool OnRebuild(void* ctx);                                  // 0x00992180
};

void* __cdecl FUN_009512c0();                                                    // 0x009512c0
void* __cdecl FUN_009512d0(unsigned int size, unsigned int align, const char* n, void* a);  // 0x009512d0

}}  // namespace EA::UTFWinControls

using EA::UTFWinControls::TreeNode;
using EA::UTFWinControls::WinTreeView;
using EA::UTFWinControls::WatchGraph;
using EA::UTFWinControls::TreeViewExtra;
using EA::UTFWinControls::BasicFactory_TreeNode;
using EA::UTFWinControls::TreeNodeListMarshaller;
using EA::UTFWinControls::IWindow;
using EA::UTFWinControls::IDrawable;
using EA::UTFWinControls::IUnknown32;
using namespace EA::UTFWin;

// @ 0x009913d0
int WinTreeView::GetSelection(int which)
{
    TreeNode* out;
    unsigned int cap;
    if (which == 0) {
        out = 0;
        cap = 0;
    } else {
        out = (TreeNode*)0;
        cap = (unsigned int)which;
    }
    return ((TreeNode*)&mNodes)->CollectVisible(&out, cap);
}

// @ 0x00991400
bool WinTreeView_OnTick(WinTreeView* self)
{
    self->Refresh();
    return true;
}

// @ 0x00991410
TreeNode::~TreeNode()
{
    *(void**)this = &g_vtbl_1445c58;
    *(void**)((char*)this + 4) = &g_vtbl_1445c54;
    if (mpUserData != 0)
        mpUserData->u1();
    if (mpIcon != 0)
        mpIcon->d1();
    if (mCaptionBegin != 0 && (unsigned int)(mCaptionCap - mCaptionBegin) > 2)
        FUN_00f47380(mCaptionBegin);
    ((eastl::intrusive_list<TreeNode>*)&mChildren)->~intrusive_list();
    *(void**)((char*)this + 4) = &g_vtbl_13ef094;
    *(void**)this = &g_vtbl_13eb938;
}

// @ 0x00991470
bool TreeNode::IsExpanded()
{
    return ((mFlags >> 1) & 1) != 0;
}

// @ 0x00991490
void TreeNode::SetFlag(unsigned int flag, bool on)
{
    unsigned int old = mFlags;
    if (on)
        mFlags = old | flag;
    else
        mFlags = ~flag & old;
    if (old == mFlags)
        return;
    unsigned int now = mFlags;
    n6(old, now);
    unsigned int changed = (now ^ old) & 2;
    if (changed != 0)
        CalcVisibleLines();
    if (mpTreeView == 0)
        return;
    WinTreeView* tv = mpTreeView;
    ((IWindow*)((char*)tv + 4))->w36();
    if (changed != 0)
        ((IWindow*)((char*)tv + 4))->w31(8, 1);
}

// @ 0x00991520
void TreeNode::SetFlagRecursive(unsigned int flag, bool on)
{
    SetFlag(flag, on);
    eastl::intrusive_list<TreeNode>::iterator end = mChildren.end();
    eastl::intrusive_list<TreeNode>::iterator it = mChildren.begin();
    while (it != end) {
        it->SetFlagRecursive(flag, on);
        ++it;
    }
}

// @ 0x00991580
void TreeNode::ChildInsert(eastl::intrusive_list_node* pos, TreeNode* child)
{
    void (*addref)(void*) = *(void (**)(void*))*(void**)child;
    child->mpParent = (TreeNode*)pos;
    addref(child);
    child->mpParent = this;
    eastl::intrusive_list_node* p = pos;
    eastl::intrusive_list_node* cur = p->mpNext;
    eastl::intrusive_list_node* cn = (eastl::intrusive_list_node*)child + 1;
    p->mpNext = cn;
    cur->mpPrev = cn;
    cn->mpNext = p;
    cn->mpPrev = cur;
    child->Attach(mpTreeView);
    child->CalcVisibleLines();
    if (mpTreeView != 0) {
        ((IWindow*)((char*)mpTreeView + 4))->w31(8, 1);
        ((IWindow*)((char*)mpTreeView + 4))->w36();
    }
}

// @ 0x00991600
void TreeNode::ChildRemoveAll()
{
    eastl::intrusive_list_node* anchor =
        (eastl::intrusive_list_node*)((char*)this + 0x1c);
    while (anchor->mpPrev != anchor) {
        eastl::intrusive_list_node* n = anchor->mpNext;
        TreeNode* child = (TreeNode*)((char*)n - 0xc);
        n->mpNext->mpPrev = anchor;
        anchor->mpNext = anchor->mpNext->mpNext;
        if (n != anchor) {
            n->mpPrev = 0;
            n->mpNext = 0;
        }
        if (mpTreeView != 0 && mpTreeView->mPickNode == child)
            mpTreeView->mPickNode = 0;
        child->mpParent = 0;
        child->mpTreeView = 0;
        eastl::intrusive_list_node* ca =
            (eastl::intrusive_list_node*)((char*)child + 0x1c);
        eastl::intrusive_list_node* ci = ca->mpNext;
        while (ci != ca) {
            eastl::intrusive_list_node* cn = ci->mpNext;
            ((TreeNode*)((char*)ci - 0xc))->Detach();
            ci = cn;
        }
        (*(IUnknown32**)&child)->u1();
    }
    CalcVisibleLines();
}

// @ 0x009916b0
void SerUpdate(TreeNode* p)
{
    p->CalcVisibleLines();
    if (p->mpTreeView != 0) {
        ((IWindow*)((char*)p->mpTreeView + 4))->w31(8, 1);
        ((IWindow*)((char*)p->mpTreeView + 4))->w36();
    }
}

// @ 0x009916f0
void TreeNode_Expand(TreeNode* p)
{
    p->SetFlag(2, true);
}

// @ 0x00991700
void TreeNode_Collapse(TreeNode* p)
{
    p->SetFlag(2, false);
}

// @ 0x00991710
bool TreeNodeListMarshaller::Read(void* a, void* container, void* b)
{
    (void)a; (void)container; (void)b;
    return true;
}

// @ 0x009917b0
void WinTreeView::InvalidateLayout()
{
    ((TreeViewExtra*)this)->CalculateVisibleArea();
}

// @ 0x009917f0
void WinTreeView::SetBorders(EA::UTFWin::RectF* r)
{
    mLocalX0 = r->left;
    mLocalY0 = r->top;
    mLocalX1 = r->right;
    mLocalY1 = r->bottom;
    CreateScrollbar(1);
    CreateScrollbar(0);
    ((TreeViewExtra*)this)->CalculateVisibleArea();
    mWindow.w31(8, 1);
    mWindow.w36();
}

// @ 0x00991860
void WinTreeView::ClearSelection()
{
    eastl::intrusive_list<TreeNode>::iterator end = mNodes.mChildren.end();
    eastl::intrusive_list<TreeNode>::iterator it = mNodes.mChildren.begin();
    while (it != end) {
        it->SetFlagRecursive(1, false);
        ++it;
    }
}

// @ 0x009918b0
void WinTreeView::OnMouseDown()
{
    TreeNode* node = mPickNode;
    if (node == 0) {
        mWindow.w5();
        return;
    }
    if (mPickType == 1) {
        node->SetFlag(2, ((node->mFlags >> 1) & 1) == 0);
        return;
    }
    if ((node->mFlags & 1) == 0) {
        mWindow.w5();
        mPickNode->SetFlag(1, true);
    }
}

// @ 0x00991930
void WinTreeView::SetScrollbarDrawable(int which, void* p)
{
    ScrollbarState* sb = &mScrollbars[which];
    IScrollbarDrawable* old = sb->mDrawable.mpObject;
    if ((void*)old != p) {
        if (p != 0)
            (*(IScrollbarDrawable**)&p)->x0();
        sb->mDrawable.mpObject = (IScrollbarDrawable*)p;
        if (old != 0)
            old->x1();
    }
    CreateScrollbar(1);
    CreateScrollbar(0);
}

// @ 0x00991990
void WinTreeView::SetScrollbarEnabled(int which, int v)
{
    mScrollbars[which].mEnabled = v;
    CreateScrollbar(1);
    CreateScrollbar(0);
}

// @ 0x009919e0
void* BasicFactory_TreeNode::CreateInstance(void* unused, void* alloc)
{
    (void)unused;
    if (!alloc)
        alloc = FUN_009512c0();
    unsigned int* p = (unsigned int*)FUN_009512d0(
        0x50, 4, "UTFWin/EA::UTFWinControls::TreeNode", alloc);
    if (p == 0)
        return 0;
    p[2] = 0;
    p[1] = (unsigned int)&g_vtbl_13ef094;
    p[4] = 0;
    p[3] = 0;
    p[5] = 0;
    p[6] = 0;
    p[0] = (unsigned int)&g_vtbl_1445c58;
    p[1] = (unsigned int)&g_vtbl_1445c54;
    p[8] = (unsigned int)(p + 7);
    p[7] = (unsigned int)(p + 7);
    p[9] = 0;
    p[11] = 0;
    p[12] = 0;
    p[10] = 2;
    p[13] = (unsigned int)gEmptyString16;
    p[14] = (unsigned int)gEmptyString16;
    p[15] = (unsigned int)&g_rdata_1667bae;
    p[17] = 0;
    p[18] = 0;
    p[19] = 0;
    return p;
}

// @ 0x00991a70
WinTreeView::WinTreeView()
{
    FUN_00962a10(this);
    *(void**)((char*)this + 0x20c) = &g_vtbl_1445b68;
    *(void**)this = &g_vtbl_1445e60;
    *(void**)((char*)this + 4) = &g_vtbl_1445d40;
    *(void**)((char*)this + 0x20c) = &g_vtbl_1445cb8;
    mInited = false;
    *(void**)((char*)this + 0x218) = &g_vtbl_13ef094;
    *(void**)((char*)this + 0x21c) = 0;
    *(void**)((char*)this + 0x224) = 0;
    *(void**)((char*)this + 0x220) = 0;
    *(void**)((char*)this + 0x214) = &g_vtbl_1445c58;
    *(void**)((char*)this + 0x218) = &g_vtbl_1445c54;
    *(void**)((char*)this + 0x228) = 0;
    *(void**)((char*)this + 0x22c) = 0;
    float z = g_14853e0;
    unsigned int* anchor = (unsigned int*)((char*)this + 0x230);
    anchor[1] = (unsigned int)anchor;
    anchor[0] = (unsigned int)anchor;
    *(void**)((char*)this + 0x238) = 0;
    *(void**)((char*)this + 0x240) = 0;
    *(void**)((char*)this + 0x244) = 0;
    *(void**)((char*)this + 0x23c) = (void*)2;
    *(void**)((char*)this + 0x250) = &g_rdata_1667bae;
    *(void**)((char*)this + 0x248) = (void*)gEmptyString16;
    *(void**)((char*)this + 0x24c) = (void*)gEmptyString16;
    *(void**)((char*)this + 0x258) = 0;
    *(void**)((char*)this + 0x25c) = 0;
    *(void**)((char*)this + 0x260) = 0;
    *(float*)((char*)this + 0x264) = z;
    *(float*)((char*)this + 0x268) = z;
    *(float*)((char*)this + 0x26c) = z;
    *(float*)((char*)this + 0x270) = z;
    *(float*)((char*)this + 0x274) = 0.0f;
    *(float*)((char*)this + 0x278) = 0.0f;
    *(float*)((char*)this + 0x27c) = 0.0f;
    *(float*)((char*)this + 0x280) = 0.0f;
    *(void**)((char*)this + 0x284) = (void*)0xb;
    *(void**)((char*)this + 0x2ac) = 0;
    *(void**)((char*)this + 0x2b0) = 0;
    *(void**)((char*)this + 0x2b4) = 0;
    *(void**)((char*)this + 0x2bc) = (void*)2;
    *(void**)((char*)this + 0x2b8) = (void*)0x18;
    *(void**)((char*)this + 0x2c0) = (void*)8;
    *(void**)((char*)this + 0x2c4) = (void*)4;
    *(float*)((char*)this + 0x2c8) = 0.0f;
    *(float*)((char*)this + 0x2cc) = 0.0f;
    *(float*)((char*)this + 0x2d0) = 0.0f;
    *(void**)((char*)this + 0x2d4) = 0;
    *(void**)((char*)this + 0x2d8) = 0;
    *(void**)((char*)this + 0x2dc) = 0;
    *(void**)((char*)this + 0x2e8) = 0;
    *(void**)((char*)this + 0x2ec) = 0;
    *(void**)((char*)this + 0x2f0) = 0;
    *(void**)((char*)this + 0x2f4) = 0;
    *(void**)((char*)this + 0x2f8) = 0;
    *(float*)((char*)this + 0x31c) = 0.0f;
    *(float*)((char*)this + 0x320) = 0.0f;
    *(void**)((char*)this + 0x308) = 0;
    *(void**)((char*)this + 0x30c) = 0;
    *(float*)((char*)this + 0x324) = 0.0f;
    *(float*)((char*)this + 0x328) = 0.0f;
    FUN_0093a560((char*)this + 0x330, 5, false);
    FUN_0093a560((char*)this + 0x348, 5, false);
    *(float*)((char*)this + 0x360) = g_1471064;
    *(void**)((char*)this + 0x22c) = 0;
    *(void**)((char*)this + 0x228) = this;
    *(void**)((char*)this + 0x288) = (void*)0xff000000;
    *(void**)((char*)this + 0x28c) = (void*)0xffffffff;
    *(void**)((char*)this + 0x290) = (void*)0xff808080;
    *(void**)((char*)this + 0x294) = (void*)0xffffffff;
    *(void**)((char*)this + 0x298) = (void*)0xff000000;
    *(void**)((char*)this + 0x29c) = (void*)0xffc0c0ff;
    *(void**)((char*)this + 0x2a0) = (void*)0xff0000ff;
    *(void**)((char*)this + 0x2a4) = (void*)0xffffffff;
    *(void**)((char*)this + 0x2a8) = (void*)0x30000000;
    if (*(void**)((char*)this + 0x30c) != 0) {
        void* q = *(void**)((char*)this + 0x30c);
        *(void**)((char*)this + 0x30c) = 0;
        (*(IUnknown32**)&q)->u1();
    }
    if (*(void**)((char*)this + 0x308) != 0) {
        void* q = *(void**)((char*)this + 0x308);
        *(void**)((char*)this + 0x308) = 0;
        (*(IUnknown32**)&q)->u1();
    }
    *(void**)((char*)this + 0x310) = 0;
    if (*(void**)((char*)this + 0x2f8) != 0) {
        void* q = *(void**)((char*)this + 0x2f8);
        *(void**)((char*)this + 0x2f8) = 0;
        (*(IUnknown32**)&q)->u1();
    }
    if (*(void**)((char*)this + 0x2f4) != 0) {
        void* q = *(void**)((char*)this + 0x2f4);
        *(void**)((char*)this + 0x2f4) = 0;
        (*(IUnknown32**)&q)->u1();
    }
    FUN_00960020(0x1002);
    *(void**)((char*)this + 0x2fc) = 0;
    unsigned int t = GetDoubleClickTime();
    float f = (float)(int)t;
    if ((int)t < 0)
        f = f + g_13f4fd0;
    *(float*)((char*)this + 0x360) = f * g_13f9428;
}

// @ 0x00991df0
WinTreeView::~WinTreeView()
{
    *(void**)this = &g_vtbl_1445e60;
    *(void**)((char*)this + 4) = &g_vtbl_1445d40;
    *(void**)((char*)this + 0x20c) = &g_vtbl_1445cb8;
    void* srcEnd = *(void**)((char*)this + 0x2d8);
    void* srcBeg = *(void**)((char*)this + 0x2d4);
    FUN_011e0744(srcEnd, srcBeg, 0);
    ((TreeViewExtra*)this)->CalculateVisibleArea();
    mNodes.InnerChildRemoveAllRecursive();
    mNodes.CalcVisibleLines();
    if (mNodes.mpTreeView != 0) {
        ((IWindow*)((char*)mNodes.mpTreeView + 4))->w31(8, 1);
        ((IWindow*)((char*)mNodes.mpTreeView + 4))->w36();
    }
    (void)srcBeg;
}

// @ 0x00991f90
void WatchGraph::Clear()
{
    eastl::intrusive_list_node* anchor = &mChannels;
    eastl::intrusive_list_node* it = anchor->mpNext;
    while (it != anchor) {
        eastl::intrusive_list_node* next = it->mpNext;
        FUN_00f47380(*(void**)((char*)it + 0x14));
        next->mpPrev = anchor;
        anchor->mpNext = next;
        if (it != anchor) {
            it->mpPrev = 0;
            it->mpNext = 0;
        }
        (*(IUnknown32**)&it)->u0();
        it = next;
    }
}

// @ 0x00991ff0
WatchGraph::WatchGraph()
{
    FUN_00962a10(this);
    *(void**)this = &g_vtbl_1446078;
    *(void**)((char*)this + 4) = &g_vtbl_1445f58;
    eastl::intrusive_list_node* anchor = &mChannels;
    anchor->mpNext = anchor;
    anchor->mpPrev = anchor;
    mSample0 = 0.0f;
    mSample1 = 0.0f;
    mbAutoScale = false;
    mbClip = true;
    mHistorySize = 0;
    mHistoryCount = 0;
}

// @ 0x00992080
void WatchGraph::SetHistorySize(unsigned int n)
{
    if (n == mHistorySize)
        return;
    mHistorySize = n;
    eastl::intrusive_list_node* anchor = &mChannels;
    eastl::intrusive_list_node* it = anchor->mpNext;
    while (it != anchor) {
        eastl::intrusive_list_node* cur = it;
        it = it->mpNext;
        if (*(void**)((char*)cur + 0x14) != 0)
            FUN_00f47380(*(void**)((char*)cur + 0x14));
        if (n == 0) {
            *(void**)((char*)cur + 0x14) = 0;
        } else {
            void* p = EAAllocate(n * 4, "WatchGraph/ChannelHistory", 0, 0, 0, 0);
            *(void**)((char*)cur + 0x14) = p;
            FUN_011e0744(p, 0, n * 4);
        }
    }
    mHistoryCount = 0;
}

// @ 0x00992140
void WatchGraph::OnAreaChanged(EA::UTFWin::RectF* r)
{
    int v = (int)(r->right - r->left);
    SetHistorySize((unsigned int)v);
}

// @ 0x00992180
bool WatchGraph::OnRebuild(void* ctx)
{
    EA::UTFWin::RenderCtx* pCtx = (EA::UTFWin::RenderCtx*)ctx;
    EA::UTFWin::Batch2D* b = EA::UTFWin::Begin2D_batch(pCtx, 0);
    float w = *(float*)((char*)this + 0xa0) - *(float*)((char*)this + 0x98);
    float h = *(float*)((char*)this + 0xa4) - *(float*)((char*)this + 0x9c);
    b->b1(0x563d517f);
    b->b14(0.0f, 0.0f, w, h);
    b->b1(0x6e8a9dc4);
    b->b13(0.0f, 0.0f, w, h, 2.0f);
    float gap = (h - 2.0f) - 2.0f;
    float scale;
    float absSample1 = (float)fabs((double)*(float*)((char*)this + 0x218));
    if (absSample1 > g_13f18d4)
        scale = gap / *(float*)((char*)this + 0x218);
    else
        scale = 1.0f;
    float z = 0.0f;
    (void)z;
    unsigned int n = *(unsigned int*)((char*)this + 0x220);
    if ((int)(n - 4) > 0) {
        int total = (int)(n - 4);
        for (int i = 0; i < total; ++i) {
            unsigned int idx = (*(unsigned int*)((char*)this + 0x224) - (unsigned int)i) - 1;
            if ((int)idx < 0)
                idx += n;
            float top = h;
            float bot = h;
            eastl::intrusive_list_node* anchor = (eastl::intrusive_list_node*)((char*)this + 0x20c);
            eastl::intrusive_list_node* it = anchor->mpNext;
            while (it != anchor) {
                float* hist = *(float**)((char*)it + 0x14);
                float v = (float)iat_floor((double)(hist[idx] * scale + 0.5f));
                if (v > 0.0f) {
                    float y = top - v;
                    bot = y;
                    top = y;
                } else if (v < 0.0f) {
                    top = top - v;
                    bot = top;
                }
                if (*(char*)((char*)this + 0x21c) != 0) {
                    if (2.0f > bot)
                        bot = 2.0f;
                    if (top > h)
                        top = h;
                }
                if (bot < top) {
                    b->b1(*(int*)((char*)it + 0x10));
                    b->b14(h, v, v + 1.0f, top);
                }
                if (*(char*)((char*)this + 0x21d) == 0) {
                    top = h;
                    bot = h;
                }
                it = it->mpNext;
            }
        }
    }
    EA::UTFWin::End2D(pCtx);
    return true;
}
