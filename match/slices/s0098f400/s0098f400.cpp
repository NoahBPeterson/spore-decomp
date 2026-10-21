// EA::UTFWinControls::WinTreeView accessors, layout vars, drawables, scrollbar update,
// tree-node helpers and serialization marshaller (0x98f400-0x9903a0).
//
// Retail layout (settled by the neighbouring slices s0098e3a0 / s00990450 / s009913d0):
//   The Window occupies 0x20c bytes: primary vptr +0x000, IWindow vptr +0x004, treeview
//   flags +0x078, mColors[9] +0x07c, item height +0x0a0, icon drawable +0x0a4, expander
//   drawable +0x0a8, layout vars +0x0ac..+0x0b8, expander extent +0x0bc/+0x0c0, scrollbar
//   slots (stride 0x14) from +0x0e8.  The window's own area is +0x088..+0x094.
//   For a WinTreeView method `this` is the window pointer; the IWindow interface lives at
//   `this + 0x004`.  The tree code re-derives the raw window base as `this - 0x208`
//   (the primary vtable is at window+0, the object pointer handed to the primary-vtable
//   slots +0x7c / +0x90 is that base) -- declaring those slots as IWindowLike members of
//   a thin wrapper reproduces the `lea esi,[ecx-0x208]` + `call [eax+0x7c]` shape.
#include "types.h"

#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])

extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

// 9.0f as a shared constant (retail reads it from 0x13f8734); a plain float global makes
// MSVC emit the `movss xmm0, [const]` form the original uses.
float g_kNine = 9.0f;
float g_kBias = 4294967296.0f;   // 0x13f4fd0: (double)(int)->float correction

// Globals / imports referenced by TreeExpanderDrawable::CreateRenderables.
float  g_k1485720 = 1.0f;        // 0x1485720
float  g_k13ef74c = 0.5f;        // 0x13ef74c
float  g_k13eb8c8 = 0.5f;        // 0x13eb8c8
double g_k1471064 = 0.5;         // 0x1471064
float  g_k1470f1c = 1.0f;        // 0x1470f1c
uint32_t g_serTypeTable[0x1000]; // 0x154eea0 (_kSerTypeTable)
uint32_t __cdecl ColorLerp(uint32_t c0, uint32_t c1, float t);   // 007F5EB0
double   __cdecl iat_floor(double);                              // 01 1E0906

namespace EA { namespace UTFWinControls {

// ------------------------------------------------------------------ shared helpers

// Minimal vtable carriers.  Raw dispatch (VSLOT) only ever uses the slot offsets below.
struct IWindowLike {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94();
};

// Retail thiscall helpers, declared as members of a dummy struct so the compiler passes
// `self` in ecx only.
struct WindowBase {
    void Shutdown();                                // 00961E80
    void SetFlag(unsigned flag, char on);           // 00961760
    void SerUpdate();                               // 009614A0
};
#define WND(self) ((WindowBase*)(self))

// ---------------------------------------------------------------- tree-view layout
struct TreeNode;
struct WinTreeView;

struct TreeNode {                                   // vptr + 2 words = 0x0c
    void* vt;                                       // +0x00
    void* pLists;                                   // +0x04
    TreeNode* mpNextSibling;                        // +0x08
    uint32_t p0c;                                   // +0x0c
    uint32_t p10;                                   // +0x10
    WinTreeView* mpTreeView;                        // +0x14
    uint32_t p18;                                   // +0x18
    TreeNode* mChildrenNext;                        // +0x1c  intrusive_list anchor next
    TreeNode* mChildrenPrev;                        // +0x20
    uint32_t p24;                                   // +0x24
    uint32_t mFlags;                                // +0x28

    void InnerChildRemoveAllRecursive();             // 00990040
};

struct ScrollbarState {
    void*   mScrollbar;                              // +0x00
    void*   mDrawable;                               // +0x04
    int     mEnabled;                                // +0x08
    float   mF0C;                                    // +0x0c
    float   mF10;                                    // +0x10
};

struct WinTreeView {
    void*    vtPrimary;                              // +0x000
    void*    vtIWindow;                              // +0x004
    uint32_t p08[(0x02c - 0x08) / 4];                // +0x008 .. 0x02b
    uint8_t  mDrawFlags;                             // +0x02c
    uint8_t  p02d[(0x078 - 0x02d)];                  // +0x02d .. 0x077
    uint32_t mTreeViewFlags;                         // +0x078
    uint32_t mColors[9];                             // +0x07c  colour table (GetColor/SetColor);
                                                     //         mColors[3..6] alias the window area
    uint32_t mItemHeight;                            // +0x0a0
    void*    mpIconDrawable;                         // +0x0a4
    void*    mpExpanderDrawable;                     // +0x0a8
    uint32_t mLayoutVar0;                            // +0x0ac
    uint32_t mLayoutVar1;                            // +0x0b0
    uint32_t mLayoutVar2;                            // +0x0b4
    uint32_t mLayoutVar3;                            // +0x0b8
    union { float mExpanderW; uint32_t mExpanderWu; };  // +0x0bc
    union { float mExpanderH; uint32_t mExpanderHu; };  // +0x0c0
    uint32_t p0c4[(0x0e8 - 0x0c4) / 4];              // +0x0c4 .. 0x0e7
    ScrollbarState mScrollbars[2];                   // +0x0e8, +0x0fc
    uint32_t p110[(0x210 - 0x110) / 4];              // +0x110 .. 0x20f
    uint8_t  mInited;                                // +0x210
    uint8_t  p211[3];                                // +0x211
    uint32_t mFlags;                                 // +0x214
    uint8_t  p218[0x234 - 0x218];                    // +0x218 .. 0x233
    float    areaTop;                                // +0x234
    uint8_t  p238[0x23c - 0x238];                    // +0x238 .. 0x23b
    float    areaBottom;                             // +0x23c
    uint32_t p240[(0x264 - 0x240) / 4];              // +0x240 .. 0x263
    float    mRect0;                                 // +0x264
    float    mRect1;                                 // +0x268
    float    mRect2;                                 // +0x26c
    float    mRect3;                                 // +0x270
    float    mVisibleTop;                            // +0x274
    float    mVisibleLeft;                           // +0x278
    float    mVisibleBottom;                         // +0x27c
    float    mVisibleRight;                          // +0x280
    uint32_t p284[(0x288 - 0x284) / 4];              // +0x284 .. 0x287
    uint32_t mColDefaultA;                           // +0x288
    uint32_t mColBaseline;                           // +0x28c
    uint32_t mColDefaultB;                           // +0x290
    uint32_t p294;                                   // +0x294
    uint32_t mColSelected;                           // +0x298
    uint32_t mColSetBit0;                            // +0x29c
    uint32_t mColHotB;                               // +0x2a0
    uint32_t mColPicked;                             // +0x2a4
    uint32_t p2a8[(0x2ac - 0x2a8) / 4];              // +0x2a8
    uint32_t mLineIndent;                            // +0x2ac
    uint32_t p2b0[(0x2b4 - 0x2b0) / 4];              // +0x2b0
    void*    mpExpander2;                            // +0x2b4
    uint32_t p2b8[(0x2c8 - 0x2b8) / 4];              // +0x2b8 .. 0x2c7
    float    mExpanderW2;                            // +0x2c8
    union { float mExpanderH2; uint32_t mExpanderH2u; };  // +0x2cc
    float    mRowHeight;                             // +0x2d0
    uint32_t p2d4[(0x2ec - 0x2d4) / 4];              // +0x2d4 .. 0x2eb
    TreeNode* mpPickNode;                            // +0x2ec
    uint32_t mPickType;                              // +0x2f0
    ScrollbarState mScrollSlot1;                     // +0x2f4
    ScrollbarState mScrollSlot2;                     // +0x308
    float    mLastScrollX;                           // +0x31c
    float    mLastScrollY;                           // +0x320
    float    f324;                                   // +0x324
    float    f328;                                   // +0x328
    uint32_t p32c[(0x340 - 0x32c) / 4];              // +0x32c .. 0x33f

    uint32_t GetColor(unsigned idx);                              // 0098F400
    void     SetColor(unsigned idx, uint32_t c);                  // 0098F420
    void     SetTreeViewFlag(uint32_t flag, char on);             // 0098F460
    void     SetItemHeight(uint32_t h);                           // 0098F490
    void     SetLayoutVar(unsigned idx, uint32_t v);              // 0098F4D0
    uint32_t GetLayoutVar(unsigned idx);                          // 0098F550
    char     OnFocusChange(int flag, void* other);                // 0098F5B0
    uint32_t GetScrollbarEnabled(int idx);                        // 0098F610
    void     CalculateRowHeight();                                // 0098F620
    void     Shutdown();                                          // 0098F7D0
    void     SetDefaultIconDrawable(void* d);                     // 0098F850
    void     SetExpanderDrawable(void* d);                        // 0098F8B0
    void     DrawTreeNode(void* ctx, TreeNode* node, float* rect);  // 0098F950
    int      DoMessage(void* msg);                                // 0098FAB0
    void*    GetScrollbarDrawable(int idx);                       // 0098FB80
    int      IsScrollbarVisible(int idx);                         // 0098FBA0
    void     CalculateVisibleArea();                              // 0098FBE0
    void     UpdateScrollbars();                                  // 0098FD20
};

// TreeExpanderDrawable -- only CreateRenderables is written here.
struct TreeExpanderDrawable {
    uint32_t p00[(0xd8 - 0x00) / 4];                 // +0x00 .. 0xd7
    void __stdcall CreateRenderables(void* ctx, float* rect, void* state);  // 009900B0
};

// Describe/Serialize context and the tree-node marshaller.
struct TreeNodeListMarshaller {
    static char Write(void* out, void* a2, void* a3, void* serCtx);  // 009903A0
};

// Text layout helpers used by CalculateRowHeight / DrawTreeNode.  All are thiscall
// members of the ~0x370-byte EA::Text::Layout stack object.
struct Layout {
    uint8_t data[0x37c];
    Layout();                                        // 00890F50
    void  Assign(const void* style, int a, int b);   // 0088FFA0
    ~Layout();                                       // 00890560
    float Get1(int a);                               // 00890D20
    float Get2(int a);                               // 00890E20
};
struct StyleManager {
    const void* GetStyle(unsigned id, void* a);      // 00894670
};
StyleManager* GetStyleManager(char a);                              // 00885BD0
char FUN_00950bb0(void* msg);                                       // 00950BB0

struct BatchRenderCtx {                                             // 0095BC10
    void* Begin2D(void* renderMode);
};
struct RenderBatch {                                                // 0096F1F0
    void DrawIcon(float* rect);
};

// ============================================================ 0x990040
// @ 0x990040
void TreeNode::InnerChildRemoveAllRecursive() {
    uint32_t* anchor = (uint32_t*)((char*)this + 0x1c);
    while (*(uint32_t**)((char*)anchor + 4) != anchor) {
        uint32_t* n = *(uint32_t**)anchor;                 // anchor->next
        TreeNode* child = n ? (TreeNode*)((char*)n - 0xc) : 0;
        *(uint32_t**)(*n + 4) = anchor;                    // n->next->prev = anchor
        *anchor = **(uint32_t**)anchor;                    // anchor->next = n->next
        if (n != anchor) {
            *(uint32_t*)((char*)n + 4) = 0;
            *n = 0;
        }
        WinTreeView* w = mpTreeView;
        if (w && w->mpPickNode == child) {
            w->mpPickNode = 0;
        }
        child->InnerChildRemoveAllRecursive();
        void (__thiscall* fn)(void*) = VSLOT(void (__thiscall*)(void*), child, 4);
        *(uint32_t*)((char*)child + 0x14) = 0;
        *(uint32_t*)((char*)child + 0x18) = 0;
        fn(child);
    }
}

// ============================================================ 0x98f720
// @ 0x98f720
char __fastcall FUN_0098f720(uint32_t* self, void* unused) {
    uint32_t* n = *(uint32_t**)((char*)self + 0x18);
    for (;;) {
        if (n == 0) return 1;
        if ((unsigned char)((*(uint32_t*)((char*)n + 0x28) >> 1) & 1) == 0) break;
        n = *(uint32_t**)((char*)n + 0x18);
    }
    return 0;
}

// ============================================================ 0x98f750
// @ 0x98f750
char __stdcall FUN_0098f750(float* out, void* b, void* c) {
    float v = g_kNine;
    out[1] = v;
    out[0] = v;
    return 1;
}

// ============================================================ 0x98f620
// @ 0x98f620
void WinTreeView::CalculateRowHeight() {
    Layout layout;
    StyleManager* mgr = GetStyleManager(1);
    const void* style = 0;
    if (mgr) {
        style = mgr->GetStyle(mExpanderHu, 0);
        if (style) {
            layout.Assign(style, 0, 0);
        }
    }
    unsigned indent = mLineIndent;
    mRowHeight = (float)indent;
    if (style && indent == 0) {
        float a = layout.Get1(0);
        float b = layout.Get2(0);
        mRowHeight = (float)ceil((double)(a - b));
    }
}

// ============================================================ 0x990350
// @ 0x990350
void __cdecl FUN_00990350(WinTreeView* w) {
    float nine = g_kNine;
    w->mExpanderW2 = nine;
    w->mExpanderH2 = nine;
    if (w->mpExpander2) {
        VSLOT(void (__thiscall*)(void*, float*, int, int), w->mpExpander2, 0x18)
            (w->mpExpander2, &w->mExpanderW2, 0, 0);
    }
    IWindowLike* iw = (IWindowLike*)((char*)w + 4);
    VSLOT(void (__thiscall*)(void*, int, int), iw, 0x7c)(iw, 8, 1);
    WND(w)->SerUpdate();
}

// ============================================================ 0x98fbe0
// @ 0x98fbe0
void WinTreeView::CalculateVisibleArea() {
    struct VisF { float top, left, bottom, right; };
    float zero = 0.0f;
    VisF* v = (VisF*)&mVisibleTop;
    v->bottom = *(float*)&mColors[5] - *(float*)&mColors[3];        // +0x90 - +0x88
    v->top = zero;
    v->left = zero;
    v->right = *(float*)&mColors[6] - *(float*)&mColors[4];         // +0x94 - +0x8c
    void* iface = (char*)this + 0x20c;
    v->top = zero + *(float*)&mRect0;
    v->left = v->left + mRect1;
    v->bottom = v->bottom - mRect2;
    v->right = v->right - mRect3;
    if (VSLOT(char (__thiscall*)(void*, int), iface, 0x80)(iface, 1)) {
        mVisibleBottom = mVisibleBottom - mScrollSlot2.mF0C;
    }
    if (VSLOT(char (__thiscall*)(void*, int), iface, 0x80)(iface, 0)) {
        mVisibleRight = mVisibleRight - mScrollSlot1.mF10;
    }
    if (mVisibleBottom < mVisibleTop || mVisibleRight < mVisibleLeft) {
        mVisibleBottom = mVisibleTop;
        mVisibleRight = mVisibleLeft;
    }
}

// ============================================================ 0x98fab0
// @ 0x98fab0
int WinTreeView::DoMessage(void* msg) {
    if (*(uint32_t*)((char*)msg + 8) != 0x8ef0c8dd) {
        return FUN_00950bb0(msg);
    }
    float x = mScrollSlot1.mScrollbar
        ? (float)VSLOT(int (__thiscall*)(void*), mScrollSlot1.mScrollbar, 0x28)(mScrollSlot1.mScrollbar)
        : 0.0f;
    float y = mScrollSlot2.mScrollbar
        ? (float)VSLOT(int (__thiscall*)(void*), mScrollSlot2.mScrollbar, 0x28)(mScrollSlot2.mScrollbar)
        : 0.0f;
    if (x != mLastScrollX || y != mLastScrollY) {
        IWindowLike* w = (IWindowLike*)((char*)this + 4);
        void (__thiscall* fn)(void*) = VSLOT(void (__thiscall*)(void*), w, 0x90);
        mLastScrollX = x;
        mLastScrollY = y;
        fn(w);
    }
    return 1;
}

// ============================================================ 0x98f950
// @ 0x98f950
void __fastcall FUN_0098f950(void* self, void* unused, void* ctx, TreeNode* node, float* rect) {
    WinTreeView* tv = (WinTreeView*)self;
    void* batch = ((BatchRenderCtx*)ctx)->Begin2D(0);
    char hot = (node == tv->mpPickNode && tv->mPickType == 2);
    uint32_t c;
    if (tv->mDrawFlags & 2) {
        uint32_t baseline = tv->mColBaseline;
        c = baseline;
        if (node->mFlags & 1) {
            c = tv->mColSetBit0;
        } else if (hot) {
            c = tv->mColPicked;
        }
        if ((c & 0xff000000u) != 0 && c != baseline) {
            VSLOT(void (__thiscall*)(void*, uint32_t), batch, 4)(batch, c);
            ((RenderBatch*)batch)->DrawIcon(rect);
        }
    }
    StyleManager* mgr = GetStyleManager(1);
    if (mgr) {
        const void* style = mgr->GetStyle(tv->mExpanderHu, 0);
        if (style) {
            Layout layout;
            layout.Assign(style, 0, 0);
            c = tv->mColDefaultA;
            if (!(tv->mDrawFlags & 2)) {
                c = tv->mColDefaultB;
            } else if (node->mFlags & 1) {
                c = tv->mColSelected;
            } else if (hot) {
                c = tv->mColHotB;
            }
            VSLOT(void (__thiscall*)(void*, uint32_t), batch, 4)(batch, c);
            VSLOT(void (__thiscall*)(void*, float, float, void*, int, const void*, void*, int), batch, 0x24)
                (batch, rect[0], rect[1], *(void**)((char*)node + 0x34),
                 (int)(*(uint32_t*)((char*)node + 0x38) - *(uint32_t*)((char*)node + 0x34)) >> 1,
                 style, &layout, 0);
        }
    }
}

// ============================================================ 0x98fd20
// @ 0x98fd20
void __fastcall FUN_0098fd20(WinTreeView* tv, void* unused) {
    char visA;
    int mode = tv->mScrollSlot2.mEnabled;   // +0x310
    if (mode == 2) {
        visA = 1;
    } else if (mode == 1 && tv->f328 > tv->mVisibleRight - tv->mVisibleLeft) {
        visA = 1;
    } else {
        visA = 0;
    }
    if (tv->mScrollSlot2.mScrollbar) {
        void* so = VSLOT(void* (__thiscall*)(void*), tv->mScrollSlot2.mScrollbar, 0x10)(tv->mScrollSlot2.mScrollbar);
        VSLOT(void (__thiscall*)(void*, int, char), so, 0x7c)(so, 1, visA);
    }
    tv->CalculateVisibleArea();
    char visB;
    int mode2 = tv->mScrollSlot1.mEnabled;  // +0x2fc
    if (mode2 == 2) {
        visB = 1;
    } else if (mode2 == 1 && tv->f324 > tv->mVisibleBottom - tv->mVisibleTop) {
        visB = 1;
    } else {
        visB = 0;
    }
    if (tv->mScrollSlot1.mScrollbar) {
        void* so = VSLOT(void* (__thiscall*)(void*), tv->mScrollSlot1.mScrollbar, 0x10)(tv->mScrollSlot1.mScrollbar);
        VSLOT(void (__thiscall*)(void*, int, char), so, 0x7c)(so, 1, visB);
    }
    tv->CalculateVisibleArea();
    if (tv->mScrollSlot2.mScrollbar) {
        float r0 = *(float*)((char*)tv + 0xa0) - *(float*)((char*)tv + 0x98) - tv->mScrollSlot2.mF0C;
        float r1 = 0.0f;
        float r2 = *(float*)((char*)tv + 0xa0) - *(float*)((char*)tv + 0x98);
        float r3 = *(float*)((char*)tv + 0xa4) - *(float*)((char*)tv + 0x9c);
        if (visB) {
            r3 = r3 - tv->mScrollSlot1.mF10;
        }
        float r[4] = { r0, r1, r2, r3 };
        void* sb = tv->mScrollSlot2.mScrollbar;
        void* so = VSLOT(void* (__thiscall*)(void*), sb, 0x10)(sb);
        VSLOT(void (__thiscall*)(void*, float*), so, 0x60)(so, r);
        VSLOT(void (__thiscall*)(void*, int, int), sb, 0x34)(sb, (int)tv->f328, 1);
        VSLOT(void (__thiscall*)(void*, int, int), sb, 0x3c)(sb, (int)(tv->mVisibleRight - tv->mVisibleLeft), 1);
        VSLOT(void (__thiscall*)(void*, int), sb, 0x4c)(sb, (int)tv->mRowHeight);
        void* so2 = VSLOT(void* (__thiscall*)(void*), sb, 0x10)(sb);
        if (!VSLOT(char (__thiscall*)(void*, int), so2, 0x100)(so2, 1)) {
            VSLOT(void (__thiscall*)(void*, int, int), sb, 0x24)(sb, (int)tv->mLastScrollY, 0);
        }
    }
    if (tv->mScrollSlot1.mScrollbar) {
        float r0 = 0.0f;
        float r1 = *(float*)((char*)tv + 0xa4) - *(float*)((char*)tv + 0x9c);
        float r2 = *(float*)((char*)tv + 0xa4) - *(float*)((char*)tv + 0x9c) - tv->mScrollSlot1.mF10;
        float r3 = *(float*)((char*)tv + 0xa0) - *(float*)((char*)tv + 0x98);
        if (visA) {
            r3 = r3 - tv->mScrollSlot2.mF0C;
        }
        float r[4] = { r0, r1, r2, r3 };
        void* sb = tv->mScrollSlot1.mScrollbar;
        void* so = VSLOT(void* (__thiscall*)(void*), sb, 0x10)(sb);
        VSLOT(void (__thiscall*)(void*, float*), so, 0x60)(so, r);
        VSLOT(void (__thiscall*)(void*, int, int), sb, 0x34)(sb, (int)tv->f324, 1);
        VSLOT(void (__thiscall*)(void*, int, int), sb, 0x3c)(sb, (int)(tv->mVisibleBottom - tv->mVisibleTop), 1);
        VSLOT(void (__thiscall*)(void*, int), sb, 0x4c)(sb, 0x10);
        void* so2 = VSLOT(void* (__thiscall*)(void*), sb, 0x10)(sb);
        if (!VSLOT(char (__thiscall*)(void*, int), so2, 0x100)(so2, 1)) {
            VSLOT(void (__thiscall*)(void*, int, int), sb, 0x24)(sb, (int)tv->mLastScrollX, 0);
        }
    }
}

}}  // namespace EA::UTFWinControls

using namespace EA::UTFWinControls;

namespace EA { namespace UTFWinControls {

// ============================================================ 0x98f400
// @ 0x98f400
uint32_t WinTreeView::GetColor(unsigned idx) {
    if (idx <= 8) return mColors[idx];
    return 0;
}

// ============================================================ 0x98f420
// @ 0x98f420
void WinTreeView::SetColor(unsigned idx, uint32_t c) {
    if (idx > 8) return;
    if (mColors[idx] == c) return;
    mColors[idx] = c;
    IWindowLike* w = (IWindowLike*)((char*)this - 0x208);
    VSLOT(void (__thiscall*)(void*), w, 0x90)(w);
}

// ============================================================ 0x98f460
// @ 0x98f460
void WinTreeView::SetTreeViewFlag(uint32_t flag, char on) {
    if (on) {
        mTreeViewFlags |= flag;
    } else {
        mTreeViewFlags &= ~flag;
    }
}

// ============================================================ 0x98f490
// @ 0x98f490
void WinTreeView::SetItemHeight(uint32_t h) {
    if (mItemHeight == h) return;
    IWindowLike* w = (IWindowLike*)((char*)this - 0x208);
    mItemHeight = h;
    VSLOT(void (__thiscall*)(void*, int, int), w, 0x7c)(w, 8, 1);
    VSLOT(void (__thiscall*)(void*), w, 0x90)(w);
}

// ============================================================ 0x98f4d0
// @ 0x98f4d0
void WinTreeView::SetLayoutVar(unsigned idx, uint32_t v) {
    switch (idx) {
    case 0: mLayoutVar0 = v; break;
    case 1: mLayoutVar1 = v; break;
    case 2: mLayoutVar2 = v; break;
    case 3: mLayoutVar3 = v; break;
    }
    IWindowLike* w = (IWindowLike*)((char*)this - 0x208);
    VSLOT(void (__thiscall*)(void*, int, int), w, 0x7c)(w, 8, 1);
    VSLOT(void (__thiscall*)(void*), w, 0x90)(w);
}

// ============================================================ 0x98f550
// @ 0x98f550
uint32_t WinTreeView::GetLayoutVar(unsigned idx) {
    switch (idx) {
    case 0: return mLayoutVar0;
    case 1: return mLayoutVar1;
    case 2: return mLayoutVar2;
    case 3: return mLayoutVar3;
    }
    return 0;
}

// ============================================================ 0x98f5b0
// @ 0x98f5b0
char WinTreeView::OnFocusChange(int flag, void* other) {
    if (flag == 1) {
        char* self = this ? (char*)this + 4 : 0;
        if (other != self && mpPickNode != 0) {
            mpPickNode = 0;
            mPickType = 0;
            VSLOT(int (__thiscall*)(void*), (char*)this + 4, 0x90)((char*)this + 4);
        }
    }
    return 0;
}

// ============================================================ 0x98f610
// @ 0x98f610
uint32_t WinTreeView::GetScrollbarEnabled(int idx) {
    return *(uint32_t*)((char*)this + idx * 0x14 + 0xf0);
}

// ============================================================ 0x98f7d0
// @ 0x98f7d0
void WinTreeView::Shutdown() {
    if (mScrollSlot2.mScrollbar) {
        void* p = mScrollSlot2.mScrollbar;
        mScrollSlot2.mScrollbar = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    if (mScrollSlot2.mDrawable) {
        void* p = mScrollSlot2.mDrawable;
        mScrollSlot2.mDrawable = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    if (mScrollSlot1.mScrollbar) {
        void* p = mScrollSlot1.mScrollbar;
        mScrollSlot1.mScrollbar = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    if (mScrollSlot1.mDrawable) {
        void* p = mScrollSlot1.mDrawable;
        mScrollSlot1.mDrawable = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    mInited = 0;
    WND(this)->Shutdown();
}

// ============================================================ 0x98f850
// @ 0x98f850
void WinTreeView::SetDefaultIconDrawable(void* d) {
    void* old = mpIconDrawable;
    if (d != old) {
        if (d) VSLOT(void (__thiscall*)(void*), d, 0)(d);
        mpIconDrawable = d;
        if (old) VSLOT(void (__thiscall*)(void*), old, 4)(old);
    }
    IWindowLike* w = (IWindowLike*)((char*)this - 0x208);
    VSLOT(void (__thiscall*)(void*, int, int), w, 0x7c)(w, 8, 1);
    VSLOT(void (__thiscall*)(void*), w, 0x90)(w);
}

// ============================================================ 0x98f8b0
// @ 0x98f8b0
void WinTreeView::SetExpanderDrawable(void* d) {
    void* old = mpExpanderDrawable;
    if (d != old) {
        if (d) VSLOT(void (__thiscall*)(void*), d, 0)(d);
        mpExpanderDrawable = d;
        if (old) VSLOT(void (__thiscall*)(void*), old, 4)(old);
    }
    void* cur = mpExpanderDrawable;
    const float nine = 9.0f;
    mExpanderW = nine;
    mExpanderH = nine;
    if (cur) {
        VSLOT(void (__thiscall*)(void*, float*, int, int), cur, 0x18)(cur, &mExpanderW, 0, 0);
    }
    IWindowLike* w = (IWindowLike*)((char*)this - 0x208);
    VSLOT(void (__thiscall*)(void*, int, int), w, 0x7c)(w, 8, 1);
    VSLOT(void (__thiscall*)(void*), w, 0x90)(w);
}

// ============================================================ 0x98fb80
// @ 0x98fb80
void* WinTreeView::GetScrollbarDrawable(int idx) {
    return *(void**)((char*)this + idx * 0x14 + 0xec);
}

// ============================================================ 0x98fba0
// @ 0x98fba0
int WinTreeView::IsScrollbarVisible(int idx) {
    void* p = *(void**)((char*)this + idx * 0x14 + 0xe8);
    if (p) {
        void* q = VSLOT(void* (__thiscall*)(void*), p, 0x10)(p);
        char r = (char)VSLOT(int (__thiscall*)(void*), q, 0x28)(q);
        if (r & 1) return 1;
    }
    return 0;
}

// ============================================================ 0x9900b0
// @ 0x9900b0
void __stdcall TreeExpanderDrawable::CreateRenderables(void* ctx, float* rect, void* state) {
    void* batch = ((BatchRenderCtx*)ctx)->Begin2D(0);
    VSLOT(void (__thiscall*)(void*, uint32_t), batch, 4)(batch, 0x20000000u);
    float k = g_k1485720;
    float y1 = rect[3] + k;
    float x1 = rect[2] + k;
    float y0 = rect[1] + k;
    float x0 = rect[0] + k;
    VSLOT(void (__thiscall*)(void*, float, float, float, float), batch, 0x38)(batch, x0, y0, x1, y1);
    uint32_t c0 = *(uint32_t*)state & 7;
    uint32_t col;
    if (c0 == 2) {
        col = 0xffbeddffu;
    } else if (c0 == 3) {
        col = 0xff7f94ffu;
    } else {
        col = 0xffffffffu;
    }
    uint32_t lerpA = ColorLerp(col, col & 0xff000000u, g_k13ef74c);
    VSLOT(void (__thiscall*)(void*, uint32_t), batch, 4)(batch, 0xffffffffu);
    uint32_t lerpB = ColorLerp(col, col & 0xff000000u, g_k13eb8c8);
    VSLOT(void (__thiscall*)(void*, uint32_t, uint32_t, float, float, float, float), batch, 0x48)
        (batch, lerpB, lerpA, x0, y0, x1, y1);
    uint32_t c1 = *(uint32_t*)state;
    uint32_t col2 = ((c1 & 7) == 1) ? 0xffa9bdbdu : 0xff000000u;
    uint32_t lerpC = ColorLerp(col2, col2 | 0xffffffu, g_k13ef74c);
    VSLOT(void (__thiscall*)(void*, uint32_t), batch, 4)(batch, lerpC);
    VSLOT(void (__thiscall*)(void*, float, float, float, float, float), batch, 0x1c)
        (batch, rect[0], rect[1], rect[2], rect[3], 1.0f);
    float q0 = (float)iat_floor((double)((rect[2] + rect[0]) * g_k1471064));
    float q1 = (float)iat_floor((double)((rect[3] + rect[1]) * g_k1471064));
    VSLOT(void (__thiscall*)(void*, uint32_t), batch, 4)(batch, col2);
    VSLOT(void (__thiscall*)(void*, float, float, float, float, float), batch, 0x1c)
        (batch, rect[0] + g_k1470f1c, q0, rect[2] - g_k1470f1c, q0 + 1.0f, 1.0f);
    if ((*(uint8_t*)state & 8) == 0) {
        VSLOT(void (__thiscall*)(void*, float, float, float, float, float), batch, 0x1c)
            (batch, q1, rect[1] + 2.0f, q1 + 1.0f, rect[3] - 2.0f, 1.0f);
    }
}

// ============================================================ 0x9903a0
// @ 0x9903a0
char TreeNodeListMarshaller::Write(void* out, void* a2, void* a3, void* serCtx) {
    uint32_t* o = (uint32_t*)out;
    int* anchor = (int*)(*(int*)((char*)a2 + 4) + *(int*)((char*)a3 + 0x10) + 0x1c);
    int count = -1;
    int* it = anchor;
    do { it = (int*)*it; count++; } while (it != anchor);
    o[2] = (uint32_t)count;
    uint32_t* buf = (uint32_t*)VSLOT(uint32_t* (__thiscall*)(void*, int, int), serCtx, 0)
                        (serCtx, count * 4, 4);
    o[1] = (uint32_t)buf;
    o[0] = g_serTypeTable[*(uint16_t*)((char*)a3 + 0xc) & 0xfff];
    if (buf == 0) return 0;
    int* first = (int*)((char*)anchor + (0x10 - 0x1c));
    int* node = (*anchor == 0) ? 0 : (int*)(*anchor - 0xc);
    while (node != first) {
        uint32_t v;
        if (node == 0) {
            v = 0;
        } else {
            v = VSLOT(uint32_t (__thiscall*)(void*, uint32_t), node, 0xc)(node, 0xeec58382u);
        }
        *buf++ = v;
        node = (node[3] == 0) ? 0 : (int*)(node[3] - 0xc);
    }
    return 1;
}

}}  // namespace EA::UTFWinControls
