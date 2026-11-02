// src/game/UTFSpore_Win32/TreeView.cpp -- migrated from slice(s) s00990450, s0098f400, s007f5300, s01300280, s0098e3a0, s00950bb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/TreeView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include <intrin.h>
#include "EA/Text/FontServer.h"
#include "EA/Text/LineLayout.h"
#include "EA/Stopwatch.h"
#include "EA/Text/TextStyle.h"
#include "EA/Text/Typesetter.h"
#include <stddef.h>
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/Window.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWin/IWindow.h"

// ---- items of slice s00950bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_pMemPool16c8b44;  // 0x016c8b44
void* __fastcall LockedAlignedCall(void* self, int reserved, int ptr,
                                   unsigned n, int align, int, int, int,
                                   int, int);  // 0x00928a30
namespace EA {
namespace UTFWin {
class CustomWinProc_s0095_0bb0 { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);
    char pad[0x18];
    unsigned int mnRefCount;    // +0x1c

    void* AsInterface(int typeId);   // 0x00950EB0
    void* AsInterfaceA(int typeId);  // 0x00951240
    int   Release();                 // 0x009514A0
};
}
}
using EA::UTFWin::CustomWinProc_s0095_0bb0;
// ---- items of slice s00950bb0 end

// ---- items of slice s0098e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc();
#pragma pack(4)
#pragma intrinsic(__rdtsc)
namespace EA {
namespace UTFWinControls {
struct TypeRegistry {
    virtual void v0();
    virtual void Register(void* type, int flags);
};
}
}
namespace EA {
namespace UTFWinControls {
TypeRegistry* GetTypeRegistry();                              // 0x920090
}
}
namespace EA {
namespace UTFWinControls {
extern void* g_WinTextEditType0;                              // 0x154fe5c
}
}
namespace EA {
namespace UTFWinControls {
extern void* g_WinTextEditType1;                              // 0x154fe60
}
}
namespace EA {
namespace UTFWinControls {
extern void* g_WinTextEditType2;                              // 0x154fe64
}
}
namespace EA {
namespace UTFWinControls {
struct UTFWindow { bool Initialize(); };                      // 0xb1fbf0
}
}
namespace EA {
namespace UTFWinControls {
class WinTreeView : public UTFWindow { public:
    uint32_t pad[0x84];
    bool mInited;                                             // +0x210
    bool Init();
};
}
}
// ---- items of slice s0098e3a0 end

// ---- items of slice s007f5300 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vt_01415350;
extern void* g_vt_01415338;
extern void* g_vt_013fa72c;
#define VTOBJ(p) (*(void***)(p))
typedef void   (__thiscall *FV0)(void*);
typedef void   (__thiscall *FVP)(void*, void*);
typedef void*  (__thiscall *FPR0)(void*);
typedef void*  (__thiscall *FPRI)(void*, int);
typedef char   (__thiscall *FPCV)(void*, void*);
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(int size, int align, const char* name, void* caller);
struct Obj {
    void  M5300(void* p);
    int   M53C0(void* p);
    bool  M53D0();
    void* M5410(int type);
    bool  M5460(int v);
    int   M5490();
    void  M54B0(int v);
    bool  M54E0();
    void  M55B0();
    bool  M55F0(void* ev);
    bool  M5660(void* p);
    void  M5690();
    void  M56C0();
    float M56E0();
    bool  M5710(float v);
    void  M58E0();
    bool  M5990();
    bool  M59E0(void* obj, int a2, int a3, int a4);
    bool  M5A60(void* ctx);
    bool  M5BD0(void* out, int, int);
    Obj*  M5C20();
    void  M5D00();
    void* M5FF0(char flags);
};
// ---- items of slice s007f5300 end

// ---- items of slice s0098f400 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) double __cdecl ceil(double);
#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])
float g_kNine = 9.0f;
float  g_k1485720 = 1.0f;        // 0x1485720
float  g_k13ef74c = 0.5f;        // 0x13ef74c
float  g_k13eb8c8 = 0.5f;        // 0x13eb8c8
double g_k1471064 = 0.5;         // 0x1471064
float  g_k1470f1c = 1.0f;        // 0x1470f1c
uint32_t g_serTypeTable[0x1000]; // 0x154eea0 (_kSerTypeTable)
uint32_t __cdecl ColorLerp(uint32_t c0, uint32_t c1, float t);   // 007F5EB0
double   __cdecl iat_floor(double);                              // 01 1E0906
namespace EA {
namespace UTFWinControls {
struct IWindowLike {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
};
}
}
namespace EA {
namespace UTFWinControls {
struct WindowBase {
    void Shutdown();                                // 00961E80
    void SetFlag(unsigned flag, char on);           // 00961760
    void SerUpdate();                               // 009614A0
};
}
}
namespace EA {
namespace UTFWinControls {
#define WND(self) ((WindowBase*)(self))
}
}
namespace EA {
namespace UTFWinControls {
class TreeNode;
}
}
namespace EA {
namespace UTFWinControls {
class WinTreeView_s0098_f400;
}
}
namespace EA {
namespace UTFWinControls {
class TreeNode { public:                                   // vptr + 2 words = 0x0c
    void* vt;                                       // +0x00
    void* pLists;                                   // +0x04
    TreeNode* mpNextSibling;                        // +0x08
    uint32_t p0c;                                   // +0x0c
    uint32_t p10;                                   // +0x10
    WinTreeView_s0098_f400* mpTreeView;                        // +0x14
    uint32_t p18;                                   // +0x18
    TreeNode* mChildrenNext;                        // +0x1c  intrusive_list anchor next
    TreeNode* mChildrenPrev;                        // +0x20
    uint32_t p24;                                   // +0x24
    uint32_t mFlags;                                // +0x28

    void InnerChildRemoveAllRecursive();             // 00990040
};
}
}
namespace EA {
namespace UTFWinControls {
struct ScrollbarState {
    void*   mScrollbar;                              // +0x00
    void*   mDrawable;                               // +0x04
    int     mEnabled;                                // +0x08
    float   mF0C;                                    // +0x0c
    float   mF10;                                    // +0x10
};
}
}
namespace EA {
namespace UTFWinControls {
class WinTreeView_s0098_f400 { public:
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

    uint32_t GetColor(unsigned idx);                              // 0098F400 0x0098f400
    void     SetColor(unsigned idx, uint32_t c);                  // 0098F420 0x0098f420
    void     SetTreeViewFlag(uint32_t flag, char on);             // 0098F460 0x0098f460
    void     SetItemHeight(uint32_t h);                           // 0098F490 0x0098f490
    void     SetLayoutVar(unsigned idx, uint32_t v);              // 0098F4D0 0x0098f4d0
    uint32_t GetLayoutVar(unsigned idx);                          // 0098F550 0x0098f550
    char     OnFocusChange(int flag, void* other);                // 0098F5B0 0x0098f5b0
    uint32_t GetScrollbarEnabled(int idx);                        // 0098F610 0x0098f610
    void     CalculateRowHeight();                                // 0098F620 0x0098f620
    void     Shutdown();                                          // 0098F7D0 0x0098f7d0
    void     SetDefaultIconDrawable(void* d);                     // 0098F850 0x0098f850
    void     SetExpanderDrawable(void* d);                        // 0098F8B0 0x0098f8b0
    void     DrawTreeNode(void* ctx, TreeNode* node, float* rect);  // 0098F950
    int      DoMessage(void* msg);                                // 0098FAB0 0x0098fab0
    void*    GetScrollbarDrawable(int idx);                       // 0098FB80 0x0098fb80
    int      IsScrollbarVisible(int idx);                         // 0098FBA0 0x0098fba0
    void     CalculateVisibleArea();                              // 0098FBE0 0x0098fbe0
    void     UpdateScrollbars();                                  // 0098FD20
};
}
}
namespace EA {
namespace UTFWinControls {
class TreeExpanderDrawable { public:
    uint32_t p00[(0xd8 - 0x00) / 4];                 // +0x00 .. 0xd7
    void __stdcall CreateRenderables(void* ctx, float* rect, void* state);  // 009900B0
};
}
}
namespace EA {
namespace UTFWinControls {
struct TreeNodeListMarshaller {
    static char Write(void* out, void* a2, void* a3, void* serCtx);  // 009903A0
};
}
}
namespace EA {
namespace UTFWinControls {
struct Layout {
    uint8_t data[0x37c];
    Layout();                                        // 00890F50
    void  Assign(const void* style, int a, int b);   // 0088FFA0
    ~Layout();                                       // 00890560
    float Get1(int a);                               // 00890D20
    float Get2(int a);                               // 00890E20
};
}
}
namespace EA {
namespace UTFWinControls {
struct StyleManager {
    const void* GetStyle(unsigned id, void* a);      // 00894670
};
}
}
namespace EA {
namespace UTFWinControls {
StyleManager* GetStyleManager(char a);                              // 00885BD0
}
}
namespace EA {
namespace UTFWinControls {
char FUN_00950bb0(void* msg);                                       // 00950BB0
}
}
namespace EA {
namespace UTFWinControls {
struct BatchRenderCtx {                                             // 0095BC10
    void* Begin2D(void* renderMode);
};
}
}
namespace EA {
namespace UTFWinControls {
struct RenderBatch {                                                // 0096F1F0
    void DrawIcon(float* rect);
};
}
}
// ---- items of slice s0098f400 end

// ---- items of slice s00990450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtbl_13fa72c;      // 0x013fa72c
extern void* g_vtbl_1445c04;      // 0x01445c04
extern void* g_vtbl_1445bec;      // 0x01445bec
namespace eastl {
struct intrusive_list_node_s0099_0450 {
    intrusive_list_node_s0099_0450* mpNext;
    intrusive_list_node_s0099_0450* mpPrev;
};
}
namespace eastl {
template <typename T>
class intrusive_list_s0099_0450 { public:
    intrusive_list_node_s0099_0450 mAnchor;
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
}
namespace EA {
namespace UTFWin {
struct Point2F { float x, y; };
}
}
namespace EA {
namespace UTFWin {
struct RectF { float left, top, right, bottom; };
}
}
namespace EA {
namespace UTFWin {
struct Batch2D {
virtual void b0();
virtual void b1(int idx);
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5(float* colors);
virtual void b6();
virtual void b7();
virtual void b8();
virtual void b9();
virtual void b10();
virtual void b11();
virtual void b12();
virtual void b13();
    virtual void b14(float a, float b, float c, float d);        // +0x38
};
}
}
namespace EA {
namespace UTFWinControls {
class TreeNode_s0099_0450;
}
}
namespace EA {
namespace UTFWinControls {
class WinTreeView_s0099_0450;
}
}
namespace EA {
namespace UTFWinControls {
struct IDrawable {
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
    virtual void d4(void* ctx, void* rect, void* state);         // +0x10
};
}
}
namespace EA {
namespace UTFWinControls {
class IWinScrollbar_s0099_0450 { public:
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
}
}
namespace EA {
namespace UTFWinControls {
class IScrollbarDrawable_s0099_0450 { public:
    virtual void x0();                                           // +0x0  ::AddRef
    virtual void x1();                                           // +0x4  ::Release
    virtual void y2();
    virtual void* y3();                                           // +0xc
    virtual void* y4();                                          // +0x10  ::GetWindow
    virtual void* y5();                                          // +0x14
};
}
}
namespace EA {
namespace UTFWinControls {
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
}
}
namespace EA {
namespace UTFWinControls {
struct ScrollbarState_s0099_0450 {
    AutoRefCount<IWinScrollbar_s0099_0450> mScrollbar;                      // +0
    AutoRefCount<IScrollbarDrawable_s0099_0450> mDrawable;                  // +4
    int mEnabled;                                                // +8
    float mPreferredX;                                           // +0xc
    float mPreferredY;                                           // +0x10
};
}
}
namespace EA {
namespace UTFWinControls {
struct TreeNodeBase {                                            // vptr + 2 words = 0xc
    virtual void n0();
    virtual void n1();
    virtual void n2();
    void* pad0;
    void* pad1;
};
}
}
namespace EA {
namespace UTFWinControls {
class TreeNode_s0099_0450 : public TreeNodeBase, public eastl::intrusive_list_node_s0099_0450 { public:
    WinTreeView_s0099_0450* mpTreeView;                                     // +0x14
    TreeNode_s0099_0450* mpParent;                                          // +0x18
    eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450> mChildren;                   // +0x1c
    int mVisibleLineCount;                                       // +0x24
    unsigned int mFlags;                                         // +0x28
    unsigned int pad2[2];                                        // +0x2c
    unsigned int mCaption[4];                                    // +0x34
    void* mpIcon;                                                // +0x44
    void* mpUserData;                                            // +0x48
    void* pad3;                                                  // +0x4c

    void Attach(WinTreeView_s0099_0450* tree);                              // 0x009911e0
    void Detach();                                               // 0x00991230 (other slice)
    void CalcVisibleLines();                                     // 0x00991280
    int CollectVisible(TreeNode_s0099_0450** out, unsigned int count);      // 0x009912e0
};
}
}
namespace EA {
namespace UTFWinControls {
struct IWinManager {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual void m14();
virtual void m15();
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
    virtual void m20();
    virtual void m21(void* child);                               // +0x54
};
}
}
namespace EA {
namespace UTFWinControls {
struct IWinScrollbarExt {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
virtual void e8();
virtual void e9();
virtual void e10();
virtual void e11();
virtual void e12();
virtual void e13();
virtual void e14();
virtual void e15();
virtual void e16();
virtual void e17();
virtual void e18();
virtual void e19();
virtual void e20();
virtual void e21();
virtual void e22();
virtual void e23();
virtual void e24();
virtual void e25();
virtual void e26();
virtual void e27();
virtual void e28();
virtual void e29();
    virtual void e30();
    virtual void e31(int attr, int value);                       // +0x7c
};
}
}
namespace EA {
namespace UTFWinControls {
struct IWindow {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
    virtual void w4();
    virtual IWinManager* w5();                                   // +0x14
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
    virtual unsigned int w10();                                  // +0x28
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
    virtual void w30();
    virtual void w31(int a, int b);                              // +0x7c
virtual void w32();
virtual void w33();
virtual void w34();
virtual void w35();
    virtual void w36();                                          // +0x90
virtual void w37();
virtual void w38();
virtual void w39();
virtual void w40();
virtual void w41();
virtual void w42();
virtual void w43();
virtual void w44();
    virtual void w45();
    virtual void w46(void* window);                              // +0xb8
virtual void w47();
virtual void w48();
virtual void w49();
virtual void w50();
virtual void w51();
virtual void w52();
virtual void w53();
    virtual void w54(void* child);                               // +0xd8
    virtual void w55();
    virtual void w56(void* drawable);                            // +0xe0
};
}
}
namespace EA {
namespace UTFWinControls {
struct CustomWindowBase {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void c21();
virtual void c22();
virtual void c23();
virtual void c24();
virtual void c25();
virtual void c26();
virtual void c27();
virtual void c28();
virtual void c29();
virtual void c30();
virtual void c31();
virtual void c32();
virtual void c33();
    virtual void c34(void* ctx, TreeNode_s0099_0450* node, EA::UTFWin::Point2F* pt);    // +0x88
    virtual void c35(void* ctx, TreeNode_s0099_0450* node, EA::UTFWin::Point2F* pt);    // +0x8c
};
}
}
namespace EA {
namespace UTFWinControls {
class WinTreeView_s0099_0450 : public CustomWindowBase { public:
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
    TreeNode_s0099_0450 mNodes;                                             // +0x214
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
    TreeNode_s0099_0450* mPickNode;                                         // +0x2ec
    unsigned int mPickType;                                      // +0x2f0
    ScrollbarState_s0099_0450 mScrollbars[2];                               // +0x2f4  (0x28)
    float mScrollX;                                              // +0x31c
    float mScrollY;                                              // +0x320
    float mVirtualTop;                                           // +0x324
    float mVirtualSize;                                          // +0x328
    unsigned int pad7[9];                                        // +0x32c

    TreeNode_s0099_0450* PickRow(float* pY);                                // 0x00990450
    bool OnMouseMove(float x, float y, float z);                 // 0x00990530
    void DrawTreeLines(void* ctx, float y, float* p);            // 0x009906b0
    bool OnRebuild(void* ctx);                                   // 0x00990a90
    void Refresh();                                              // 0x00990f80
    void CreateScrollbar(int which);                             // 0x00990ff0
};
}
}
namespace EA {
namespace UTFWinControls {
struct TreeViewExtra {
    void CalculateRowHeight();                                   // 0x0098f620
    void FocusChanged();                                         // 0x0098fd20
};
}
}
namespace EA {
namespace UTFWinControls {
void* __cdecl FUN_009512c0();                                                        // 0x009512c0
}
}
namespace EA {
namespace UTFWinControls {
void* __cdecl FUN_009512d0(unsigned int size, unsigned int align, const char* name, void* a);  // 0x009512d0
}
}
namespace EA {
namespace UTFWinControls {
void* __cdecl WinScrollbarCtor(void* mem);                                           // 0x00983790
}
}
namespace EA {
namespace UTFWinControls {
void* __cdecl ScrollbarDrawableCtor(void* mem);                                      // 0x009838a0
}
}
namespace EA {
namespace UTFWinControls {
struct RenderCtxShim {
    EA::UTFWin::Batch2D* Begin2D(void* mode);                    // 0x0095bc10
    void End2D();                                                // 0x0095bb20
};
}
}
namespace EA {
namespace UTFWinControls {
class BasicFactory_TreeExpanderDrawable { public:
    void* CreateInstance(void* unused, void* alloc);             // 0x00991380
};
}
}
using EA::UTFWinControls::TreeNode_s0099_0450;
using EA::UTFWinControls::WinTreeView_s0099_0450;
using EA::UTFWinControls::TreeViewExtra;
using EA::UTFWinControls::BasicFactory_TreeExpanderDrawable;
using EA::UTFWinControls::IWindow;
using EA::UTFWinControls::IWinManager;
using EA::UTFWinControls::IDrawable;
using EA::UTFWinControls::IWinScrollbar_s0099_0450;
using EA::UTFWinControls::IScrollbarDrawable_s0099_0450;
using EA::UTFWinControls::RenderCtxShim;
// ---- items of slice s00990450 end

// @ 0x007f5d00
void Obj::M5D00()
{
    void* spr = *(void**)((char*)this + 0x248);
    int cols = *(int*)((char*)this + 0x238);
    int frames = *(int*)((char*)this + 0x230);
    int rows = *(int*)((char*)this + 0x240);
    int cw = *(int*)((char*)this + 0x234);
    int r = 1;
    int c = 1;                          // eax at the +0x23c store (1 in the spr==0 arm)
    if (spr == 0) {
        rows = 1;
        cw = 0x20;
        cols = 0x20;
        frames = 1;
    } else {
        if (cw < 1) {
            if (rows < 1)
                cw = *(int*)((char*)spr + 0x20);
            else
                cw = (int)((float)*(int*)((char*)spr + 0x1c) / (float)rows);
            if (cw < 1)
                cw = 1;
        }
        r = *(int*)((char*)spr + 0x1c) / cw;
        if (cols < 1) {
            if (*(int*)((char*)this + 0x23c) < 1)
                cols = *(int*)((char*)spr + 0x20);
            else
                cols = (int)((float)*(int*)((char*)spr + 0x20) / (float)*(int*)((char*)this + 0x23c));
            if (cols < 1)
                cols = 1;
        }
        c = *(int*)((char*)spr + 0x20) / cols;
        if (frames < 1)
            frames = c * r;
    }
    *(int*)((char*)this + 0x234) = cw;
    *(int*)((char*)this + 0x238) = cols;
    *(int*)((char*)this + 0x240) = r;
    *(int*)((char*)this + 0x23c) = c;
    void* sub = (char*)this + 4;
    void* dp = ((FPR0)VTOBJ(sub)[0xa8 / 4])(sub);
    *(int*)((char*)this + 0x230) = frames;
    void* drawable = 0;
    if (dp != 0)
        drawable = ((FPRI)VTOBJ(dp)[0xc / 4])(dp, (int)0x26e0fbc);
    if (drawable == 0) {
        void* caller = FUN_009512c0();
        drawable = FUN_009512d0(0x14, 4, "UI/AnimatedIconDrawable", caller);
        if (drawable) {
            *(void**)((char*)drawable + 4) = &g_vt_013fa72c;
            *(void**)((char*)drawable + 8) = 0;
            *(void**)drawable = &g_vt_01415350;
            *(void**)((char*)drawable + 4) = &g_vt_01415338;
            *(float*)((char*)drawable + 0xc) = (float)*(int*)((char*)this + 0x234);
            *(float*)((char*)drawable + 0x10) = (float)*(int*)((char*)this + 0x238);
        } else {
            drawable = 0;
        }
        ((FVP)VTOBJ(sub)[0xb0 / 4])(sub, drawable);
    }
    *(float*)((char*)drawable + 0xc) = (float)*(int*)((char*)this + 0x234);
    *(float*)((char*)drawable + 0x10) = (float)*(int*)((char*)this + 0x238);
    void* q = (char*)this + 0x270;
    ((FV0)VTOBJ(q)[0x14 / 4])(q);
    *(int*)((char*)this + 0x228) = 0;
    char r2 = ((FPCV)VTOBJ(q)[0x10 / 4])(q, (char*)this + 0x20c);
    *(char*)((char*)this + 0x22c) = r2;
}

// @ 0x00951240
namespace EA { namespace UTFWin {
void* CustomWinProc_s0095_0bb0::AsInterfaceA(int typeId)
{
    if (typeId == 0x6ec581fd) return this;
    if (typeId == (int)0xee3f516e || typeId == (int)0xeec58382) {
        if (this) return (char*)this + 4;
    }
    return 0;
}
}}  // namespace EA::UTFWin

// @ 0x009512d0
void* AllocAligned(int base, int size, int extra, int* allocator)
{
    unsigned n = (size - 1U | 7) + 1;
    void* p;
    if (allocator == 0) {
        p = LockedAlignedCall(g_pMemPool16c8b44, 0, base + 8, n, 8,
                              0, 0, 0, 0, 0);
    } else {
        p = ((void*(__thiscall*)(void*, int, int, int, unsigned, int))((void**)*(void**)allocator)[1])(allocator, base + 8, extra, 0, n, 8);
    }
    if (p == 0) return 0;
    *(void**)p = allocator;
    return (char*)p + 8;
}

// @ 0x0098f330
namespace EA { namespace UTFWinControls {
void RegisterWinTextEditTypes()
{
    GetTypeRegistry()->Register(&g_WinTextEditType0, 0);
    GetTypeRegistry()->Register(&g_WinTextEditType1, 0);
    GetTypeRegistry()->Register(&g_WinTextEditType2, 0);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f3d0
namespace EA { namespace UTFWinControls {
bool WinTreeView::Init()
{
    if (!mInited) {
        if (Initialize())
            mInited = true;
    }
    return mInited;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f400
namespace EA { namespace UTFWinControls {
uint32_t WinTreeView_s0098_f400::GetColor(unsigned idx)
{
    if (idx <= 8) return mColors[idx];
    return 0;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f420
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::SetColor(unsigned idx, uint32_t c)
{
    if (idx > 8) return;
    if (mColors[idx] == c) return;
    mColors[idx] = c;
    IWindowLike* w = (IWindowLike*)((char*)this - 0x208);
    VSLOT(void (__thiscall*)(void*), w, 0x90)(w);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f460
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::SetTreeViewFlag(uint32_t flag, char on)
{
    if (on) {
        mTreeViewFlags |= flag;
    } else {
        mTreeViewFlags &= ~flag;
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f490
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::SetItemHeight(uint32_t h)
{
    if (mItemHeight == h) return;
    IWindowLike* w = (IWindowLike*)((char*)this - 0x208);
    mItemHeight = h;
    VSLOT(void (__thiscall*)(void*, int, int), w, 0x7c)(w, 8, 1);
    VSLOT(void (__thiscall*)(void*), w, 0x90)(w);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f4d0
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::SetLayoutVar(unsigned idx, uint32_t v)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098f550
namespace EA { namespace UTFWinControls {
uint32_t WinTreeView_s0098_f400::GetLayoutVar(unsigned idx)
{
    switch (idx) {
    case 0: return mLayoutVar0;
    case 1: return mLayoutVar1;
    case 2: return mLayoutVar2;
    case 3: return mLayoutVar3;
    }
    return 0;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f5b0
namespace EA { namespace UTFWinControls {
char WinTreeView_s0098_f400::OnFocusChange(int flag, void* other)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098f610
namespace EA { namespace UTFWinControls {
uint32_t WinTreeView_s0098_f400::GetScrollbarEnabled(int idx)
{
    return *(uint32_t*)((char*)this + idx * 0x14 + 0xf0);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f620
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::CalculateRowHeight()
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098f720
namespace EA { namespace UTFWinControls {
char __fastcall FUN_0098f720(uint32_t* self, void* unused)
{
    uint32_t* n = *(uint32_t**)((char*)self + 0x18);
    for (;;) {
        if (n == 0) return 1;
        if ((unsigned char)((*(uint32_t*)((char*)n + 0x28) >> 1) & 1) == 0) break;
        n = *(uint32_t**)((char*)n + 0x18);
    }
    return 0;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f750
namespace EA { namespace UTFWinControls {
char __stdcall FUN_0098f750(float* out, void* b, void* c)
{
    float v = g_kNine;
    out[1] = v;
    out[0] = v;
    return 1;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098f7d0
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::Shutdown()
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098f850
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::SetDefaultIconDrawable(void* d)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098f8b0
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::SetExpanderDrawable(void* d)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098f950
namespace EA { namespace UTFWinControls {
void __fastcall FUN_0098f950(void* self, void* unused, void* ctx, TreeNode* node, float* rect)
{
    WinTreeView_s0098_f400* tv = (WinTreeView_s0098_f400*)self;
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
}}  // namespace EA::UTFWinControls

// @ 0x0098fab0
namespace EA { namespace UTFWinControls {
int WinTreeView_s0098_f400::DoMessage(void* msg)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098fb80
namespace EA { namespace UTFWinControls {
void* WinTreeView_s0098_f400::GetScrollbarDrawable(int idx)
{
    return *(void**)((char*)this + idx * 0x14 + 0xec);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098fba0
namespace EA { namespace UTFWinControls {
int WinTreeView_s0098_f400::IsScrollbarVisible(int idx)
{
    void* p = *(void**)((char*)this + idx * 0x14 + 0xe8);
    if (p) {
        void* q = VSLOT(void* (__thiscall*)(void*), p, 0x10)(p);
        char r = (char)VSLOT(int (__thiscall*)(void*), q, 0x28)(q);
        if (r & 1) return 1;
    }
    return 0;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098fbe0
namespace EA { namespace UTFWinControls {
void WinTreeView_s0098_f400::CalculateVisibleArea()
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098fd20
namespace EA { namespace UTFWinControls {
void __fastcall FUN_0098fd20(WinTreeView_s0098_f400* tv, void* unused)
{
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

// @ 0x00990040
namespace EA { namespace UTFWinControls {
void TreeNode::InnerChildRemoveAllRecursive()
{
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
        WinTreeView_s0098_f400* w = mpTreeView;
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
}}  // namespace EA::UTFWinControls

// @ 0x009900b0
namespace EA { namespace UTFWinControls {
void __stdcall TreeExpanderDrawable::CreateRenderables(void* ctx, float* rect, void* state)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x00990350
namespace EA { namespace UTFWinControls {
void __cdecl FUN_00990350(WinTreeView_s0098_f400* w)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x009903a0
namespace EA { namespace UTFWinControls {
char TreeNodeListMarshaller::Write(void* out, void* a2, void* a3, void* serCtx)
{
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

// @ 0x00990450
TreeNode_s0099_0450* WinTreeView_s0099_0450::PickRow(float* pY)
{
    if (mRowHeight == 0.0f)
        return 0;
    TreeNode_s0099_0450* pParent = &mNodes;
    eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator it = pParent->mChildren.begin();
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
bool WinTreeView_s0099_0450::OnMouseMove(float x, float y, float z)
{
    float fy = mScrollY - mColors[1] + y;
    (void)z;
    TreeNode_s0099_0450* node = PickRow(&fy);
    unsigned int pick = 0;
    if (node) {
        int level = 0;
        for (TreeNode_s0099_0450* p = node->mpParent; p; p = p->mpParent)
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
void WinTreeView_s0099_0450::DrawTreeLines(void* pCtx, float y, float* p)
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
        eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator it = mNodes.mChildren.begin();
        eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator end = mNodes.mChildren.end();
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
        eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator it = mNodes.mChildren.begin();
        eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator end = mNodes.mChildren.end();
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
bool WinTreeView_s0099_0450::OnRebuild(void* pCtx)
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

    TreeNode_s0099_0450* parent = &mNodes;
    eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator it = parent->mChildren.begin();
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
            TreeNode_s0099_0450* up = parent;
            parent = parent->mpParent;
            it = eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator(
                static_cast<TreeNode_s0099_0450*>(up->mpNext));
            --level;
        }
    }
    ctx->End2D();
    return true;
}

// @ 0x00990f80
void WinTreeView_s0099_0450::Refresh()
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
void WinTreeView_s0099_0450::CreateScrollbar(int which)
{
    ScrollbarState_s0099_0450* sb = &mScrollbars[which];
    if (sb->mEnabled == 0) {
        if (sb->mDrawable.mpObject == 0)
            return;
        IWinScrollbarExt* w = (IWinScrollbarExt*)sb->mDrawable.mpObject->y4();
        mWindow.w56(w);
        IScrollbarDrawable_s0099_0450* d = sb->mDrawable.mpObject;
        if (d == 0)
            return;
        sb->mDrawable.mpObject = 0;
        d->x1();
        return;
    }
    if (sb->mScrollbar.mpObject == 0) {
        void* mem = FUN_009512d0(0x2d0, 8, "UTFWin/WinTextEdit/Scrollbar", FUN_009512c0());
        IWinScrollbar_s0099_0450* w = 0;
        if (mem) {
            void* r = WinScrollbarCtor(mem);
            if (r)
                w = (IWinScrollbar_s0099_0450*)((char*)r + 0x20c);
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
        sb->mDrawable = (IScrollbarDrawable_s0099_0450*)d;
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
void TreeNode_s0099_0450::Attach(WinTreeView_s0099_0450* tree)
{
    WinTreeView_s0099_0450* pTreeView = tree;
    eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator end = mChildren.end();
    mpTreeView = pTreeView;
    eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator it = mChildren.begin();
    while (it != end) {
        it->Attach(pTreeView);
        ++it;
    }
}

// @ 0x00991280
void TreeNode_s0099_0450::CalcVisibleLines()
{
    for (TreeNode_s0099_0450* n = this; n; n = n->mpParent) {
        eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator end = n->mChildren.end();
        n->mVisibleLineCount = 1;
        if ((n->mFlags & 2) != 0) {
            eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator it = n->mChildren.begin();
            while (it != end) {
                n->mVisibleLineCount += it->mVisibleLineCount;
                ++it;
            }
        }
    }
}

// @ 0x009912e0
int TreeNode_s0099_0450::CollectVisible(TreeNode_s0099_0450** out, unsigned int count)
{
    int total = 0;
    if (mpParent != 0 && (mFlags & 1) != 0) {
        total = 1;
        if (count != 0) {
            --count;
            *out = this;
        }
    }
    eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator it = mChildren.begin();
    eastl::intrusive_list_s0099_0450<TreeNode_s0099_0450>::iterator end = mChildren.end();
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

// @ 0x01300e90
void init_154ff0c()
{
    *(int*)0x154ff0c = 1;
    *(int*)0x154ff10 = 0;
    *(void**)0x154ff14 = (void*)0x1418fd8;
    *(int*)0x154ff18 = 0x302a0006;
    *(short*)0x154ff1c = 0x13;
    *(int*)0x154ff20 = 0x2b4;
    *(int*)0x154ff24 = 1;
    *(int*)0x154ff28 = 0;
    *(int*)0x154ff2c = 0;
    *(int*)0x154ff30 = 0x302a0007;
    *(short*)0x154ff34 = 9;
    *(int*)0x154ff38 = 0x2b8;
    *(int*)0x154ff3c = 1;
    *(int*)0x154ff40 = 0;
    *(int*)0x154ff44 = 0;
    *(int*)0x154ff48 = 0x302a0008;
    *(short*)0x154ff4c = 9;
    *(int*)0x154ff50 = 0x2bc;
    *(int*)0x154ff54 = 1;
    *(int*)0x154ff58 = 0;
    *(int*)0x154ff5c = 0;
    *(int*)0x154ff60 = 0x302a0009;
    *(short*)0x154ff64 = 9;
    *(int*)0x154ff68 = 0x2c0;
    *(int*)0x154ff6c = 1;
    *(int*)0x154ff70 = 0;
    *(int*)0x154ff74 = 0;
    *(int*)0x154ff78 = 0x302a000a;
    *(short*)0x154ff7c = 9;
    *(int*)0x154ff80 = 0x2c4;
    *(int*)0x154ff84 = 1;
    *(int*)0x154ff88 = 0;
    *(void**)0x154ff8c = (void*)0x14455f4;
    *(int*)0x154ff90 = 0x302a000b;
    *(short*)0x154ff94 = 9;
    *(int*)0x154ff98 = 0x2fc;
    *(int*)0x154ff9c = 1;
    *(int*)0x154ffa0 = 0;
    *(void**)0x154ffa4 = (void*)0x14455f4;
    *(int*)0x154ffa8 = 0x302a000c;
    *(short*)0x154ffac = 9;
    *(int*)0x154ffb0 = 0x14 + 0x2fc;
    *(int*)0x154ffb4 = 1;
    *(int*)0x154ffb8 = 0;
    *(void**)0x154ffbc = (void*)0x1441580;
    *(int*)0x154ffc0 = 0x302a000d;
    *(short*)0x154ffc4 = 0x13;
    *(int*)0x154ffc8 = 0x2f8;
    *(int*)0x154ffcc = 1;
    *(int*)0x154ffd0 = 0;
    *(void**)0x154ffd4 = (void*)0x1441580;
    *(int*)0x154ffd8 = 0x302a000e;
    *(short*)0x154ffdc = 0x13;
    *(int*)0x154ffe0 = 0x14 + 0x2f8;
    *(int*)0x154ffe4 = 1;
}
