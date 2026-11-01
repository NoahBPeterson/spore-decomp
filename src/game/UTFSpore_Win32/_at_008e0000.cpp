// src/game/UTFSpore_Win32/_at_008e0000.cpp -- migrated from slice(s) s008efad0, s008eebb0, s008edc30, s008ea290, s008e5320, s008e4310, s008e2dd0, s008e1d50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_008e0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include "EA/Allocator/ICoreAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern const void* gListStyleDefs[];      // 0x154c490 static definition table (begin)
extern const void* gListStyleDefsEnd[];   // 0x154c5d8 (end)
#include <new>
#include <intrin.h>
#include "EA/XHTML/DOM/Document.h"
#include "EA/Allocator/StackAllocator.h"
#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "EA/XHTML/DOM/IFormControlMgr.h"
#include "EA/Text/LineLayout.h"
#include "EA/XHTML/Layout/Page.h"
#include "EA/Text/Typesetter.h"
#include <math.h>
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/TextStyle.h"
#include "EA/Text/GlyphInfo.h"

// ---- items of slice s008e1d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IObj;
void __cdecl FUN_008f3790(void* out, const void* first, const void* last, const void* key);   // eastl::equal_range over a static definition table
struct IKV { int m0; int m4; char m8; char pad9[7]; int m10; };
struct Obj6 {
    virtual void v0(int);
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9(void* ctx, int flag);
    virtual void v10();
    virtual void v11();
};
struct Ref {
    char pad0[0xc];
    Obj6* mp0c;             // +0x0c
    char pad10[0x1c - 0x10];
    uint8_t mb1c;           // +0x1c
    uint8_t mb1d;           // +0x1d
    char pad1e[2];
    int mnRef;              // +0x20
    bool Test();
    bool Release();
};
struct BaseV {
    virtual ~BaseV() {}     // vtable 0x013effb8: only the deleting dtor
    int mRef4;      // +0x04
    int m8;         // +0x08
    int m12;        // +0x0c
    BaseV(int a, int b) { _InterlockedExchange((volatile long*)&mRef4, 0); m8 = a; m12 = b; }
    void ForceRelease();    // 0x008e2300
    static void operator delete(void* p);   // 0x00926060
};
struct DerV : BaseV {
    virtual void bv0();
    int v10, v14, v18;      // +0x10,14,18
    uint8_t b1c, b1d;       // +0x1c,0x1d
    char pad1e[2];
    int mRef20;             // +0x20
    DerV(int a, int b, const int* c, uint8_t d, uint8_t e);
    virtual ~DerV();
};
struct DocX {
    char pad0[0x2c];
    uint8_t mFlag;          // +0x2c
    char pad1[0xb];
    void* mpOther;          // +0x38
    char pad2[4];
    int   mVal40;           // +0x40
    void SetChild(int v);
    void CallA();
    void CallB();
    void* FindBody();
    void SetAt(unsigned idx, IObj* o);
    void RemoveAllChildren();
    bool CheckFlag(bool flag);
    int LookupStyle();
    void RemoveAttr(IKV* kv);
};
struct IObj {
    virtual void AddRef();
    virtual void Release();
};
struct M10 { void Remove(void*); };
struct Base46 {
    virtual void v();
    virtual ~Base46();
};
struct Node46 : Base46 {
    char pad[0xc];
    void* m10;      // +0x10
    char pad14[4];
    void* m18;      // +0x18
    void* m1c;      // +0x1c
    ~Node46();
};
extern const void* gListStyleDefs[];      // 0x154c490 static definition table (begin)
extern const void* gListStyleDefsEnd[];   // 0x154c5d8 (end)
// ---- items of slice s008e1d50 end

// ---- items of slice s008e2dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
int  __fastcall Fn8e42c0(void* p);                                  // 0x008e42c0 (defined below)
struct StylesheetQueue;                                             // defined below
struct DocumentVec {
    void Fn962210(void* end, void** out);
};
struct StylesheetQueue {
    void Fn8e42e0(void* arg);       // @ 0x008e42e0 (thiscall)
    void Fn8e2900(int id);          // 0x008e2900 (thiscall)
    void Fn8e28b0(int id, void* arg); // 0x008e28b0 (thiscall)
};
// ---- items of slice s008e2dd0 end

// ---- items of slice s008e4310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_wstr_src[];        // 0x0154c6ec  "src" attribute name
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
#pragma pack(push, 4)
#pragma pack(pop)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
u32   Fnfc7e50(void* n);                                 // 0x00fc7e50  Node::Type (free spelling)
void* Fn8e3fa0(void** a, u16* b, u16* c);                // 0x008e3fa0
void  Fn429580(void* wstr, const u16* b, const u16* e);  // 0x00429580  WStr::Append
struct Node;
struct Element;
struct Attr;
struct Node {                 // sizeof 0x18
    void* vftable;            // 0x00
    void* link0;              // 0x04
    void* link1;              // 0x08
    u32   mnType;             // 0x0c
    void* mpDocument;         // 0x10  Document*
    void* mpParent;           // 0x14  Element*
    int      Type();                                // 0x00fc7e50
    Element* AsElement();                           // 0x008e52f0
    void*    Init(void* doc, int type);             // 0x008e52b0
};
struct IntList {
    void* link0;              // this+0 : first link
    void* link1;              // this+4 : last link
};
static __forceinline Node* ListHead(IntList* l) {
    void* p = l->link0;
    return (Node*)(p ? (char*)p - 4 : 0);
}
static __forceinline Node* ListNext(Node* n) {
    void* p = n->link0;
    return (Node*)(p ? (char*)p - 4 : 0);
}
static __forceinline Node* ListEndP(void* sentinel) {
    return (Node*)(sentinel ? (char*)sentinel - 4 : 0);
}
struct Link {                 // 0x14, Element::mpLink
    const u16* mpURI;         // 0x00
    const u16* mpName;        // 0x04
    u32        mLinkType;     // 0x08
    u32        mState;        // 0x0c
    u8         mbVisited;     // 0x10
    u8         _pad11[3];     // 0x11
};
struct Element : Node {       // sizeof 0x44
    IntList mChildNodes;      // 0x18
    IntList mAttributes;      // 0x20
    union {
        u32        mElementType;    // 0x28
        const u16* mpTagName;       // legacy alias used by the ctor bodies
    };
    union {
        u32 mResourceIndex;         // 0x2c
        int mnAttrId;
    };
    union {
        u32 mElementState;          // 0x30
        u32 mFlags30;
    };
    union {
        const u16* mpName;          // 0x34
        const u16* mpClassName;
    };
    union {
        const u16* mpId;            // 0x38
        const u16* mpIdValue;
    };
    union {
        const u16* mpClass;         // 0x3c
        const u16* mpNameValue;
    };
    union {
        Link* mpLink;               // 0x40
        void* mpExtra40;
    };

    __declspec(noinline) void HandleEvent(void* ev, int phase); // 0x008e4310
    void    AppendChild(Element* child);               // 0x008e4350
    void*   AppendAttr(Attr* attr);                    // 0x008e4380
    void*   ScalarDeletingDtor(u8 flags);              // 0x008e4450
    Element* FindChildNodeByName(const u16* name);     // 0x008e4480
    Attr*   GetAttr(const u16* name);                  // 0x008e4530
    __declspec(noinline) u16* GetAttrValue(const u16* name); // 0x008e45b0
    int     SetAttrValue(const u16*, const u16*, u8);  // 0x008e45d0
    void    SetAttrChecked(const u16*, const u16*);    // 0x008e46e0
    void    ReleaseChildren();                         // 0x008e48a0
    void    ReleaseChildren2();                        // 0x008e48f0
    void    CollectText(void* wstr);                   // 0x008e49e0
    void    OnAdded();                                 // 0x008e4a70
    void    OnRemoved();                               // 0x008e4a90
    void    DispatchA(void* a);                        // 0x008e4ab0
    u8      DispatchB(void* a);                        // 0x008e4ad0
    void    DispatchC(void* a);                        // 0x008e4af0
    u8      AddSubElement(const u16* name);            // 0x008e4b10
    void    Dtor2();                                   // 0x008e4ba0
    void    Dtor1();                                   // 0x008e4bd0
    void    GatherValues(void* a, void* b);            // 0x008e4f00
    Element* Ctor1(void* doc, const u16* tag);         // 0x008e4940
    Element* Ctor2(void* doc, void* tag);              // 0x008e4400
};
struct Attr {                 // sizeof 0x20
    void* vftable;            // 0x00
    void* link0;              // 0x04
    void* link1;              // 0x08
    u32   mnType;             // 0x0c
    void* mpDocument;         // 0x10
    void* mpOwner;            // 0x14
    u16*  mpName;             // 0x18
    u16*  mpValue;            // 0x1c
};
// ---- items of slice s008e4310 end

// ---- items of slice s008e5320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* Fn8e42d0Get();   // 0x008e42d0 (ecx-inherited singleton)
typedef unsigned int   uint32;
typedef unsigned short wchar16;
typedef unsigned char  uint8;
struct XmlParser {
    void*    mpVtbl_0;                 // +0x000
    void*    mpDocument_4;             // +0x004
    wchar16* mpTextBegin_8;            // +0x008  shared string begin
    wchar16* mpTextEnd_c;              // +0x00c
    wchar16* mpTextCapacity_10;        // +0x010  == mpInlinePool (aliased)
    uint32   pad_14;                   // +0x014
    wchar16* mpInlinePool_18;          // +0x018
    wchar16  mInlinePool_1c[0x100];    // +0x01c .. +0x21b (inline buffer)
    void*    mpParserNode_21c;         // +0x21c
    void*    mpXmlParser_220;          // +0x220
    uint8    mbSpace_224;              // +0x224
    uint8    pad_225[3];               // +0x225
    int      mOffset_228;              // +0x228
    wchar16  mBuffer_22c[0x100];       // +0x22c .. +0x42b
    uint32   pad_42c;                  // +0x42c
    int      mCount_430;               // +0x430
    int      mIndex_434;               // +0x434
    uint8    mbFlag_438;               // +0x438

    void  Fn8e5600(short* p, int n);                 // 0x008e5600
    int   Fn8e5a20(const char* s, int len, unsigned char fin); // 0x008e5a20
    int   Fn8e5730(void* parser, void* uri);         // 0x008e5730
    void  Fn8e59a0(char param2);                     // 0x008e59a0
    void  Fn8e5ca0();                                // 0x008e5ca0
    void  Fn8e5da0(wchar16* data, int count);        // 0x008e5da0
    void  Fn8e5fb0();                                // 0x008e5fb0
    wchar16* Fn8e5670();                             // 0x008e5670
    void* Fn8e5ea0(void* doc);                       // 0x008e5ea0
    int   Fn8e60a0(void* stream);                    // 0x008e60a0
};
struct GuiThing {
    void Fn8e4400(int a, int b, int c);   // thiscall
    __declspec(noinline) void* Fn8e5370(int a, int b, int c);
};
struct GuiThing2 {
    void Fn8e52b0(int a, int n);          // thiscall
    __declspec(noinline) void* Fn8e55d0(int a, int b, int c);
};
struct GuiThing3 {
    __declspec(noinline) void* Fn8e6130(void* a);
};
struct SubA { void* Fn8ec910(); };
struct SubB { void Fn8eb910(void* a, void* arg); };
struct Q18 { __declspec(noinline) void Fn8e6180(void* arg); };
// ---- items of slice s008e5320 end

// ---- items of slice s008ea290 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned char uchar;
namespace eastl {
struct intrusive_list_node_s008e_a290 {
    intrusive_list_node_s008e_a290* mpNext;  // +0x00
    intrusive_list_node_s008e_a290* mpPrev;  // +0x04
};
}
namespace eastl {
template <typename T>
class intrusive_list_iterator {
public:
    T* mpItem;  // owning object (node address - 4), or 0

    intrusive_list_iterator() : mpItem(0) {}
    explicit intrusive_list_iterator(T* pItem) : mpItem(pItem) {}
    intrusive_list_iterator(const intrusive_list_iterator& x) : mpItem(x.mpItem) {}

    __forceinline T* operator->() const { return mpItem; }
    __forceinline T& operator*() const { return *mpItem; }
    __forceinline bool operator==(const intrusive_list_iterator& x) const
    {
        return mpItem == x.mpItem;
    }
    __forceinline bool operator!=(const intrusive_list_iterator& x) const
    {
        return mpItem != x.mpItem;
    }
    __forceinline intrusive_list_iterator& operator++()
    {
        intrusive_list_node_s008e_a290* pNext = *(intrusive_list_node_s008e_a290**)((char*)mpItem + 4);
        mpItem = pNext ? (T*)((char*)pNext - 4) : 0;
        return *this;
    }
};
}
namespace eastl {
class intrusive_list_base_s008e_a290 {
public:
    intrusive_list_node_s008e_a290 mAnchor;  // +0x00

    __forceinline intrusive_list_base_s008e_a290() { mAnchor.mpNext = mAnchor.mpPrev = &mAnchor; }
};
}
namespace eastl {
template <typename T>
class intrusive_list_s008e_a290 : public intrusive_list_base_s008e_a290 {
public:
    typedef T node_type;
    typedef intrusive_list_iterator<T> iterator;

    __forceinline iterator begin()
    {
        intrusive_list_node_s008e_a290* pNode = mAnchor.mpNext;
        return iterator(pNode ? (T*)((char*)pNode - 4) : 0);
    }
    __forceinline iterator end()
    {
        intrusive_list_node_s008e_a290* pNode = &mAnchor;
        return iterator(pNode ? (T*)((char*)pNode - 4) : 0);
    }
};
}
namespace EA {
template <typename T>
class RectT_s008e_a290 {
public:
    T mLeft, mTop, mRight, mBottom;  // +0x00..+0x0c

    RectT_s008e_a290() {}
    RectT_s008e_a290(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    RectT_s008e_a290(const RectT_s008e_a290& x) : mLeft(x.mLeft), mTop(x.mTop), mRight(x.mRight), mBottom(x.mBottom) {}
    RectT_s008e_a290& operator=(const RectT_s008e_a290& x)
    {
        mLeft = x.mLeft; mTop = x.mTop; mRight = x.mRight; mBottom = x.mBottom;
        return *this;
    }
    T Width() const { return mRight - mLeft; }
    T Height() const { return mBottom - mTop; }
};
}
namespace EA {
template <typename T>
struct SizeT {
    T w, h;
    SizeT() {}
    SizeT(T aw, T ah) : w(aw), h(ah) {}
};
}
namespace EA {
namespace Allocator {
class StackAllocator_s008e_a290 {
public:
    unsigned int mnDefaultBlockSize;  // +0x00
    void* mpCurrentBlock;             // +0x04
    char* mpCurrentBlockEnd;          // +0x08
    char* mpCurrentObjectBegin;       // +0x0c
    char* mpCurrentObjectEnd;         // +0x10
    void* mpCoreAllocationFunction;   // +0x14
    void* mpCoreFreeFunction;         // +0x18
    void* mpCoreFunctionContext;      // +0x1c
    void* mpTopBookmark;              // +0x20

    // Slow path when the current block cannot satisfy the bump.
    bool __thiscall AllocateNewBlock(unsigned int nSize);  // 0x00928ba0
};  // namespace Allocator
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Rule;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
void ComputeStyle(void* pElement, Rule** pRules, unsigned int nRuleCount, StyleState* pStyle);
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class FontMetrics { public:
    float mfFontSize;  // +0x00
    float mfEmSize;    // +0x04
    float mfExSize;    // +0x08
    float mfAscent;    // +0x0c
    float mfDescent;   // +0x10
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Length {
    float mValue;  // +0x00
    int mUnits;    // +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Selector {
public:
    virtual void v00();
    virtual bool Match(void* pElement, int flag);  // +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Declaration {
public:
    virtual void v00();
    virtual void Apply(StyleState* pStyle);  // +0x04

    Declaration* mpNext;  // +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class DeclarationList {
public:
    Declaration* mpFirst;  // +0x00
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class DeclarationCollection {
public:
    DeclarationList mList[2];  // +0x00, +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Rule {
public:
    virtual void v00();
    virtual bool Match(void* pElement, int flag);  // +0x04

    Selector* mpSelector;                    // +0x04
    DeclarationCollection* mpDeclarations;   // +0x08
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class HashTable {
public:
    uint32_t mField00;         // +0x00
    void* mpBuckets;           // +0x04
    unsigned int mnBuckets;    // +0x08
    unsigned int mnElements;   // +0x0c
    uint32_t pad10[4];         // +0x10
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState {
public:
    struct Edge {
        Length mMargin;             // +0x00
        Length mPadding;            // +0x08
        Length mBorder;             // +0x10
        int mBorderStyle;           // +0x18
        unsigned int mBorderColor;  // +0x1c
    };

    StyleState(StyleState* pBase);  // 0x008fc130
    StyleState(const StyleState& src);
    ~StyleState();                  // 0x008e8650
    void Resolve();                 // 0x008fc670

    // 0x008fba80: true when any edge carries a non-zero border width.
    bool HasBorder() const;
    // 0x008fba70: true when the computed style asks for any background image.
    bool HasBackground() const;

    StyleState* mpBase;               // +0x000
    uint32_t pad004[(0x250 - 0x004) / 4];
    unsigned int mBoxWidthPx;         // +0x250
    uint32_t pad254;
    unsigned int mBoxHeightPx;        // +0x258
    unsigned int mBorderMask;         // +0x25c
    uint32_t pad260[(0x28c - 0x260) / 4];
    unsigned int mColor;              // +0x28c
    uint32_t pad290[(0x2bc - 0x290) / 4];
    unsigned int mBackgroundColor;    // +0x2bc
    uint32_t pad2c0[(0x2ec - 0x2c0) / 4];
    Edge mEdges[4];                   // +0x2ec
    Length mBoxWidth;                 // +0x36c
    Length mBoxHeight;                // +0x374
    int mFloat;                       // +0x37c
    int mClearFloat;                  // +0x380
    int mPosition;                    // +0x384
    Length mBoxOffset[4];             // +0x388
    int mDisplay;                     // +0x3a8
    uint32_t pad3ac[(0x3bc - 0x3ac) / 4];
    HashTable mFonts;                 // +0x3bc
    HashTable mColors;                // +0x3dc
    HashTable mRules;                 // +0x3fc
    uint32_t pad41c[(0x430 - 0x41c) / 4];
    FontMetrics mFontMetrics;         // +0x430
    uint32_t pad444[(0x450 - 0x444) / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace DOM {
class Element_s008e_a290 {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void GetIntrinsicSize(EA::SizeT<float>* pSize);  // +0x10
    virtual bool v05();
    virtual bool v06();
};  // namespace DOM
}
}
}
namespace EA {
namespace XHTML {
namespace Text {
class LineLayout;
}
}
}
namespace EA {
namespace XHTML {
namespace Text {
class TextStyle { public:
    uint32_t mData[0x27c / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Text {
class Typesetter {
public:
    uint32_t mData[0x530 / 4];  // retail 0x530 (dev PDB 0x548)

    void Reset(bool bReset);                                                  // 0x0089cdf0
    void SetWidth(float fWidth, float fX, float fY);                          // 0x00897640
    int LayoutLine(const wchar_t* pText, int nLength, float fX, float fY,
                   const TextStyle* pStyle);                                  // 0x0089db20
    LineLayout* GetLineLayout();                                              // 0x008976a0
    uint GetState();                                                          // 0x00897690
};
}
}
}
namespace EA {
namespace XHTML {
namespace Text {
class LineLayout {
public:
    uint32_t mData[0x54 / 4];
    void* mpGlyphsBegin;  // +0x54
    void* mpGlyphsEnd;    // +0x58
    uint32_t pad5c[(0x98 - 0x5c) / 4];
    float mHeight;    // +0x98
    uint32_t pad9c;
    float mBaseline;  // +0xa0

    void OffsetSegment(float fX, float fY, int nGlyph, int nGlyphCount);  // 0x00897b40
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_a290;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Border;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Background;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickEntry;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickBox;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Resource {
public:
    virtual void vf00();                          // +0x00
    virtual void vf04();                          // +0x04
    virtual void vf08();                          // +0x08
    virtual void* GetInterface(unsigned int id);  // +0x0c

    static const unsigned int kImageInterface = 0xee3f516e;
    static const unsigned int kImageSizeInterface = 0x02f84737;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class SizingContext {
public:
    SizingContext(float fEnclosingWidth);  // 0x008ef870
    void Finish();                         // 0x008ef900

    Text::Typesetter mTypesetter;  // +0x000
    float mMaxWidth;               // +0x530
    float mMinWidth;               // +0x534
    float mEnclosingWidth;         // +0x538
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext {
public:
    RenderingContext(const RenderingContext& src);           // 0x008ee8c0
    ~RenderingContext();                                     // 0x008e8620
    void EndContent();                                       // 0x008f0010
    void Reset();                                            // 0x008ef6d0
    bool TestRect(float x0, float y0, float x1, float y1);   // 0x008eeac0
    void SetScrollColor(unsigned int color);                 // 0x008ee7a0
    void ScrollRect(RectT_s008e_a290<float> rect);                      // 0x008eeb30
    void SetContextRect(const RectT_s008e_a290<float>& rect);           // 0x008eed80
    void SetSubStyle(Item* pItem, const PickBox* pBox);      // 0x008ee720
    void DrawQuadGradient(float x, float y, float w, float h, void* pImage);  // 0x008eec80

    Item* mpContextRoot;                     // +0x000
    Text::Typesetter mTypesetter;            // +0x004
    RectT_s008e_a290<float> mContextRect;               // +0x534
    RectT_s008e_a290<float> mBoundsRect;                // +0x544
    float mMarginLeft;                       // +0x554
    float mMarginRight;                      // +0x558
    float mYPos;                             // +0x55c
    float mPendingCollapse;                  // +0x560
    float mMaxBreak;                         // +0x564
    float mMinBreak;                         // +0x568
    float mFirstLineBaseline;                // +0x56c
    float mFirstLineHeight;                  // +0x570
    void* mpPlaceChain;                      // +0x574
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickingContext : public Text::Typesetter {
public:
    PickingContext(const PickingContext& src);  // 0x008ee2f0
    ~PickingContext();                          // 0x008e8620
    bool Flush(PickEntry* pEntry);              // 0x008ee010
    bool FlushAll(PickEntry* pEntry);           // 0x008ee4a0
    void PlaceFloat(Item* pItem);               // 0x008edf60
    void SetContextRect(const float* rect);     // 0x008ede40
    void SetContextRect(Item* pItem, const RectT_s008e_a290<float>* rect);  // 0x008edd30

    float mX530;              // +0x530
    float mY534;              // +0x534
    float mX538;              // +0x538
    float mY53c;              // +0x53c
    void* mpPickedItem;       // +0x540
    RectT_s008e_a290<float> mBoundsRect; // +0x544
    float mExtra554;          // +0x554
    float mExtra558;          // +0x558
    float mYPos;              // +0x55c
    uint32_t pad560;          // +0x560
    void* mpVecBegin;         // +0x564
    uint32_t pad568[(0x574 - 0x568) / 4];
    void* mpInline;           // +0x574
    uint32_t pad578[(0xb84 - 0x578) / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Border {
public:
    void Draw(RenderingContext& rc, const RectT_s008e_a290<float>* pRect, uchar flags);  // 0x008ea290
    void Compute(const Style::StyleState* pStyle, float reference);           // 0x008e9e30

    void* mpPhrases;                 // +0x00  (style +0x2ec phrase table)
    uint32_t pad04[(0x10 - 0x04) / 4];
    int mEdgeLeftPhraseIndex;        // +0x10
    int mEdgeTopPhraseIndex;         // +0x14
    int mEdgeRightPhraseIndex;       // +0x18
    int mEdgeBottomPhraseIndex;      // +0x1c
    float mBorderLeft;               // +0x20
    float mBorderTop;                // +0x24
    float mBorderRight;              // +0x28
    float mBorderBottom;             // +0x2c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Background {
public:
    Background(EA::Allocator::StackAllocator_s008e_a290* pAllocator);  // 0x008e6130
    void SetStyle(const Style::StyleState* pStyle);          // 0x008e68f0
    bool Draw(RenderingContext& rc, const RectT_s008e_a290<float>* pBounds,
              const RectT_s008e_a290<float>* pRect);                    // 0x008e6710
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickEntry {
public:
    void Add(DOM::Element_s008e_a290* pElement, int nArg, unsigned int nIndex, const PickBox* pBox);  // 0x008e69b0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
enum ItemType { kItemNone = 0, kItemBlock = 1 };
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item : public eastl::intrusive_list_node_s008e_a290 {
public:
    Item(Page_s008e_a290* pPage, int nType);  // 0x008eae40
    virtual ~Item();                                                          // +0x00
    virtual void v04(unsigned int nColor);                                    // +0x04
    virtual void Measure(SizingContext& sc, Style::StyleState& style);        // +0x08
    virtual void LayoutFlow(RenderingContext& ctx, Style::StyleState& style); // +0x0c
    virtual void PlaceControls(unsigned int nArg);                            // +0x10
    virtual void Render(RenderingContext& ctx);                               // +0x14
    virtual bool Pick(PickingContext& ctx, PickEntry* pEntry);                // +0x18
    virtual void v1c();                                                       // +0x1c
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style); // +0x20
    virtual void v24(RenderingContext& ctx, Style::StyleState& style);        // +0x24
    virtual void PlaceControlsContent(unsigned int nArg);                     // +0x28
    virtual void RenderContent(void* pArg);                                   // +0x2c
    virtual bool PickContent(PickingContext& ctx, PickEntry* pEntry);         // +0x30
    virtual void Layout(RenderingContext& ctx, Style::StyleState& style);     // +0x34
    virtual void Scroll(RectT_s008e_a290<float> rect);                                   // +0x38
    virtual void PlaceOutOfFlow(RenderingContext& ctx, Style::StyleState& style);  // +0x3c

    void Dispose();  // 0x008eae70

    // 0x008eaf30: true when this item's [mSelectableIndex, +nLength) range
    // overlaps the page's selection range; *pOutOffset / *pOutLength are the
    // clipped intersection in item-local coordinates.
    bool IntersectSelection(uint* pOutOffset, uint* pOutLength, uint nLength);

    Page_s008e_a290* mpPage;                   // +0x0c
    ItemType mItemType;             // +0x10
    unsigned int mSelectableIndex;  // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
typedef eastl::intrusive_list_s008e_a290<Item> ItemList;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem : public Item {
public:
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style);  // +0x20
    virtual void LayoutFlow(RenderingContext& ctx, Style::StyleState& style);  // +0x0c
    virtual void Render(RenderingContext& ctx);                                // +0x14
    virtual bool Pick(PickingContext& ctx, PickEntry* pEntry);                 // +0x18

    ItemList mChildItems;     // +0x18
    DOM::Element_s008e_a290* mpElement;  // +0x20
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block : public ContainerItem {
public:
    Block(Page_s008e_a290* pPage, DOM::Element_s008e_a290* pElement, int nType);                    // 0x008e7f90
    virtual void Measure(SizingContext& sc, Style::StyleState& style);        // +0x08
    virtual void Render(RenderingContext& ctx);                               // +0x14
    virtual bool Pick(PickingContext& ctx, PickEntry* pEntry);                // +0x18

    // 0x008eaa20 / 0x008eac20: lane in the style's border + background objects.
    void SetUpBox(SizingContext& sc, Style::StyleState& style);
    void SetUpBox(RenderingContext& ctx, Style::StyleState& style);
    // 0x008ead40: push this block onto the context's place-chain and render content.
    void PlaceControls(RenderingContext& ctx);
    // 0x008eadb0: cascade + resolve the style, then lay out this block's box.
    void SetStyle(RenderingContext& ctx, const Style::StyleState& baseStyle);

    void DrawContent(RenderingContext& ctx);                          // 0x008e6a20
    void PlaceContent(RenderingContext& ctx, Style::StyleState& style);  // 0x008e95c0
    void GetPickBox(PickBox* pBox);                                   // 0x008e7da0

    Style::Rule** mStyleRules;          // +0x24
    unsigned int mnRuleCount;           // +0x28
    int mDisplay;                       // +0x2c
    int mPosition;                      // +0x30
    int mPlacement;                     // +0x34
    unsigned int mFgColor;              // +0x38
    unsigned int mBgColor;              // +0x3c
    Border* mpBorder;                   // +0x40
    Background* mpBackground;           // +0x44
    unsigned int mBoxWidthPx;           // +0x48  (from style +0x25c)
    unsigned int mBoxHeightPx;          // +0x4c  (from style +0x250)
    void* mpPlaceChain;                 // +0x50
    uint mPlaceStateA;                  // +0x54
    uint mPlaceStateB;                  // +0x58
    Block* mpNextFloat;                 // +0x5c
    Block* mpNextOOF;                   // +0x60
    RectT_s008e_a290<float> mOuterRect;            // +0x64
    RectT_s008e_a290<float> mBorderRect;           // +0x74
    RectT_s008e_a290<float> mPaddingRect;          // +0x84
    RectT_s008e_a290<float> mContentRect;          // +0x94
    RectT_s008e_a290<float> mPickRect;             // +0xa4
    RectT_s008e_a290<float> mBorderWidth;          // +0xb4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_a290 {
public:
    EA::Allocator::StackAllocator_s008e_a290 mAllocator;  // +0x00
    uint32_t pad24[(0x3c - 0x24) / 4];
    Item* mpRootItem;            // +0x3c
    void* mpLastWS;              // +0x40
    void* mpResourceTableBegin;  // +0x44
    void* mpResourceTableEnd;    // +0x48
    uint32_t pad4c[(0x258 - 0x4c) / 4];
    void* mpImagesLoading;          // +0x258
    void* mpResourceProvider;       // +0x25c
    void* mpActiveLink;             // +0x260
    void* mpHoverNode;              // +0x264
    unsigned int mSelectableCount;  // +0x268
    unsigned int mCursorPos;        // +0x26c
    unsigned int mAnchorPos;        // +0x270
    unsigned int mSelectionStart;   // +0x274
    unsigned int mSelectionEnd;     // +0x278
    uint32_t pad27c[(0x2a0 - 0x27c) / 4];

    Resource* GetResource(unsigned int index);                // 0x008eb960
    Text::TextStyle* GetTextStyle(Style::StyleState& style);  // 0x008ec580
    void SetChildItem(unsigned int index, void* pItem);       // 0x008eb910
    void SetSelectionRange(unsigned int a, unsigned int b);   // 0x008eba20
};
}
}
}
// ---- items of slice s008ea290 end

// ---- items of slice s008edc30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace XHTML {
namespace Layout {
struct Vec2 {
    float x, y;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void* __fastcall StyleCtor(void* self, int, void* rect, int a, int b);  // 0x0089b250
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void* __cdecl  ScrollAppGet(void);                               // 0x006e64f0
}
}
}
// ---- items of slice s008edc30 end

// ---- items of slice s008eebb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct Link_s008e_ebb0 { Link_s008e_ebb0* mpNext; };
}
namespace eastl {
struct fixed_pool_base {
    Link_s008e_ebb0* mpHead;
    Link_s008e_ebb0* mpNext;
    struct NoInit {};
    fixed_pool_base() : mpHead(0) {}
    fixed_pool_base(NoInit) {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset); // 0x00921260
};
}
namespace eastl {
class fixed_pool_with_overflow : public fixed_pool_base { public:
    void* mpPoolBegin;     // +8
    void* mpPoolEnd;       // +0xc
    uint32_t mnNodeSize;   // +0x10
    __forceinline fixed_pool_with_overflow() : fixed_pool_base(NoInit()) {}
    __forceinline fixed_pool_with_overflow(void* pMemory)
    {
        init(pMemory, 0x80, 0x20, 4, 0);
        mpPoolBegin = pMemory;
        mpPoolEnd = (char*)pMemory + 0x80;
        mnNodeSize = 0x20;
    }
};
}
namespace EA {
namespace Text {
struct GlyphLayoutInfo_s008e_ebb0 { void* mpFont; float mfPenX; float mfPenY; float mfAdvance; float mfX1; float mfY1; float mfX2; float mfY2; };
}
}
namespace EA {
namespace Text {
struct RectNode { RectNode* mpRight; RectNode* mpLeft; RectNode* mpParent; unsigned char mColor; };
}
}
namespace EA {
namespace Text {
typedef eastl::fixed_pool_with_overflow RectAlloc;
}
}
namespace EA {
namespace Text {
struct RectTree {
    int pad0;
    RectNode mAnchor;                  // +4
    unsigned mnSize;                   // +0x14
    RectAlloc mAlloc;                  // +0x18

    __forceinline RectTree(const RectAlloc& a)
        : mAlloc(a.mpHead)
    {
        mAnchor.mpRight = 0; mAnchor.mpLeft = 0; mAnchor.mpParent = 0; mAnchor.mColor = 0; mnSize = 0;
        mAnchor.mpLeft = &mAnchor;
        mAnchor.mpRight = &mAnchor;
        mAnchor.mpParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    RectTree() {}                          // initialised by RectSetExt::Init
    void DoNukeSubtree(RectNode* root);   // 0x00d3b370
    ~RectTree() { DoNukeSubtree(mAnchor.mpParent); }
};
}
}
namespace EA {
namespace Text {
struct AnalysisInfo_s008e_ebb0 { struct TextStyle_s008e_ebb0* mpTextStyle; void* mpFont; int mBits; };
}
}
namespace EA {
namespace Text {
struct TextStyle_s008e_ebb0 { char pad[0x224]; unsigned mColor; char pad2[0x238 - 0x228]; unsigned mDecorations; };
}
}
namespace EA {
namespace Text {
template <typename T> struct cvec { T* mpBegin; T* mpEnd; T* mpCapacity; void* mpAllocator; int mFlags; };
}
}
namespace EA {
namespace Text {
class LineLayout_s008e_ebb0 { public:
    void* mpCoreAllocator;                          // +0x00
    cvec<wchar_t> mCharArray;                       // +0x04
    cvec<AnalysisInfo_s008e_ebb0> mAnalysisInfoArray;          // +0x18
    cvec<uint16_t> mGlyphArray;                     // +0x2c
    cvec<uint32_t> mGlyphInfoArray;                 // +0x40
    cvec<GlyphLayoutInfo_s008e_ebb0> mGlyphLayoutInfoArray;    // +0x54
    cvec<uint32_t> mGlyphIndexArray;                // +0x68
    cvec<uint32_t> mCharIndexArray;                 // +0x7c
    float mLineMetrics[8];                          // +0x90: length, visLength, space, visSpace, baseline, descent, +2
    unsigned GetGlyphSelection(unsigned a, unsigned b, RectTree* out);        // 0x0089c110
    unsigned GetGlyphDecoration(int type, unsigned a, unsigned b, RectTree* out);   // 0x0089c2d0
};
}
}
namespace EA {
namespace Text {
struct TripleFloat {
    float mX, mY, mZ;
    void Set(float x, float y, float z);                 // 0x00897640
};
}
}
namespace EA {
namespace Text {
class Typesetter_s008e_ebb0 : public TripleFloat {
public:
    char mState[0x524];
    Typesetter_s008e_ebb0(int a);                                   // 0x0089d820
    unsigned GetType();                                  // 0x00897680
    unsigned GetLineType();                             // 0x0089cf10
    LineLayout_s008e_ebb0* GetLineLayout();                         // 0x008976a0
    void FinalizeLine();                                 // 0x0089d9a0
    void NextLine(int a);                                // 0x0089c5d0
    void Reset(int a);                                   // 0x0089cdf0
    void SetRunStyle(int a);                             // 0x0089b360
    void AddTextRun(const wchar_t* s, unsigned n);       // 0x0089b1e0
    void AddLineBreak(const wchar_t* s, unsigned n, int a, int b);   // 0x0089b250
};
}
}
namespace Simulator {
 struct cGameData { char mPad[0x348]; int mMode; }; 
}
namespace EA {
namespace XHTML {
namespace Layout {
class SizingContext_s008e_ebb0 : public EA::Text::Typesetter_s008e_ebb0 {
public:
    float mfMaxHeight;   // +0x530
    float mfMaxWidth;    // +0x534
    float mfHeight;      // +0x538

    SizingContext_s008e_ebb0(float h);                                 // 0x008ef870
    void Clear();                                           // 0x008ef8b0
    void AddRun(const wchar_t* s, unsigned n, int style);    // 0x008ef8d0
    void Finish();                                          // 0x008ef900
    Simulator::cGameData* GetGameData();                    // 0x006e64f0
};
}
}
}
// ---- items of slice s008eebb0 end

// ---- items of slice s008efad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RectF { float l, t, r, b; };
struct StackingContext;
struct Block_s008e_fad0 {
    void MoveTo(float x, float y);      // 0x008e7e00  EA::XHTML::Layout::Block::MoveTo
};
struct RunRecord {
    u32 mFlags;                         // +0x00
    u32 mValue;                         // +0x04
};
struct InlineBox {
    u32   mpItemAndFlags;               // +0x00
    u32   pad04[3];
    float mfX;                          // +0x10
    float mfY;                          // +0x14
    u32   pad18[2];
};
struct LineLayout_s008e_fad0 {                     // +0x418 inside the Typesetter, 0x118 bytes
    u32        pad00[0x40 / 4];
    RunRecord* mpRunsBegin;             // +0x40
    RunRecord* mpRunsEnd;               // +0x44
    u32        pad48[(0x54 - 0x48) / 4];
    InlineBox* mpBoxes;                 // +0x54
    u32        pad58[(0xa0 - 0x58) / 4];
    float      mfHeight;                // +0xa0
    float      mfDescent;               // +0xa4
    u32        padA8;
    int        miFlagAC;                // +0xac
    u32        padB0[(0x118 - 0xb0) / 4];
};
struct TripleFloat_s008e_fad0 {
    u32   pad00[0x3c0 / 4];
    float mfA;                          // +0x3c0
    float mfB;                          // +0x3c4
    float mfC;                          // +0x3c8
    void Set(float a, float b, float c);   // 0x00897640
};
struct Typesetter_s008e_fad0 : TripleFloat_s008e_fad0 {
    u32         pad3cc[(0x414 - 0x3cc) / 4];
    unsigned    mType;                  // +0x414
    LineLayout_s008e_fad0  mLineLayout;            // +0x418
    unsigned    GetType();              // 0x00897680
    LineLayout_s008e_fad0* GetLineLayout();        // 0x008976a0
    unsigned    ProcessLine();          // 0x0089cf10
    void        FinalizeLine();         // 0x0089d9a0
    void        NextLine(int a);        // 0x0089c5d0
    void        Reset(int a);           // 0x0089cdf0
};
struct TypesetterCtor : Typesetter_s008e_fad0 {
    void Construct(int b);              // 0x0089d820  EA::Text::Typesetter::Typesetter
    void SetSomething(void* p);         // 0x0089b360
};
struct ValueFlagPair {
    void* mpValue;                      // +0x00  the LineLayout
    void* mpFlag;                       // +0x04  current run index
    void* Store(void* pValue);          // 0x00897600
    void  Assign(void* pValue);         // 0x00897620
    bool  Next(int* pIndex);            // 0x008981a0
};
struct FloatEntry {                     // 0x74 stride
    u32   pad00[0x54 / 4];
    int   mKind;                        // +0x54
    u32   pad58;
    FloatEntry* mpNext;                 // +0x5c
    u32   pad60;
    float mOuter;                       // +0x64
    float mSide;                        // +0x68
    float mSide2;                       // +0x6c
    float mTop;                         // +0x70
};
struct StackingContext {
    u32        pad00;                   // +0x00
    Typesetter_s008e_fad0 mTypesetter;             // +0x04 .. +0x533
    float      mf534;                   // +0x534  rect left
    float      mf538;                   // +0x538  rect top
    float      mf53c;                   // +0x53c  rect right
    float      mf540;                   // +0x540  rect bottom
    float      mf544;                   // +0x544
    float      mf548;                   // +0x548
    float      mf54c;                   // +0x54c
    float      mf550;                   // +0x550
    float      mf554;                   // +0x554  line x
    float      mf558;                   // +0x558  line right
    float      mf55c;                   // +0x55c  y cursor
    float      mf560;                   // +0x560  pending margin
    float      mf564;                   // +0x564  min width
    float      mf568;                   // +0x568  max width
    float      mf56c;                   // +0x56c  last line height
    float      mf570;                   // +0x570  last line descent
    u8         mb574;                   // +0x574
    u8         pad575[3];
    FloatEntry* mpFloatsHead;           // +0x578
    FloatEntry* mpFloatsTail;           // +0x57c
    FloatEntry* mf580;                  // +0x580

    StackingContext(u32 owner);                       // @ 0x008efad0
    void  Init(u32 owner, u32 a1, u32 a2);            // @ 0x008efba0
    void  SetContextRect(const RectF& r);             // @ 0x008efc80
    void  InsertFloat(int kind);                      // @ 0x008efcd0
    void  RecomputeFloatLimits();                     // @ 0x008efd50
    void  AddFloats(LineLayout_s008e_fad0* line);                // @ 0x008efde0
    void  FlushLines(int count);                      // @ 0x008efe80
    void  FlushAllLines();                            // @ 0x008f0010
    void  CollapseMargin(float margin);               // @ 0x008f01b0
    float ClampWidth(float w);                        // @ 0x008f0240
    void  RegisterFloat(FloatEntry* e);               // @ 0x008f0280
};
// ---- items of slice s008efad0 end

// @ 0x008e22e0
bool Ref::Test()
{
    if (_InterlockedExchangeAdd((volatile long*)&mnRef, 0) != 0) {
        _InterlockedExchangeAdd((volatile long*)&mnRef, 1);
        return true;
    }
    return false;
}

// @ 0x008e2300
bool Ref::Release()
{
    if (_InterlockedExchangeAdd((volatile long*)&mnRef, 0) == 0)
        return false;
    if (_InterlockedDecrement((volatile long*)&mnRef) == 0) {
        if (mb1c != 0 && mp0c != 0) {
            mp0c->v6();
            if (mb1d != 0) {
                Obj6* p = mp0c;
                if (p != 0)
                    p->v0(1);
            }
        }
    }
    return true;
}

// @ 0x008e2350
DerV::~DerV()
{
    if (_InterlockedExchangeAdd((volatile long*)&mRef20, 0) != 0) {
        _InterlockedExchange((volatile long*)&mRef20, 1);
        ForceRelease();
    }
}

// @ 0x008e2380
DerV::DerV(int a, int b, const int* c, uint8_t d, uint8_t e)
: BaseV(a, b)
{
    v10 = c[0];
    v14 = c[1];
    v18 = c[2];
    b1c = d;
    b1d = e;
    _InterlockedExchange((volatile long*)&mRef20, 1);
}

// @ 0x008e2460
Node46::~Node46()
{
    ((M10*)m10)->Remove(m18);
    ((M10*)m10)->Remove(m1c);
}

// @ 0x008e24a0
int DocX::LookupStyle()
{
    struct Key { int name; int value; } key;
    key.value = 0;
    key.name = *(int*)((char*)this + 0x18);
    struct Range { char* first; char* last; } r;
    FUN_008f3790(&r, gListStyleDefs, gListStyleDefsEnd, &key);
    const int* p = (r.first + 8 == r.last) ? (const int*)(r.first + 4) : &key.value;
    return *p;
}

// @ 0x008e3850
__declspec(noinline) int __fastcall Fn8e3850(void* pThis)
{
    char* base = (char*)pThis + 0x108;
    int* end = *(int**)(base + 4);
    int  idx = (int)(((char*)end - *(char**)base) >> 2);
    int* local = 0;
    if ((char*)end < *(char**)(base + 8)) {
        *(int**)(base + 4) = end + 1;
        if (end) { *end = 0; return idx; }
    } else {
        ((DocumentVec*)base)->Fn962210(end, (void**)&local);
        if (local) {
            void** vt = *(void***)local;
            typedef void (__fastcall *Fn)(void*);
            ((Fn)vt[1])(local);
        }
    }
    return idx;
}

// @ 0x008e42c0
int __fastcall Fn8e42c0(void* p)
{
    return *(int*)((char*)p + 0x2c) != -1;
}

// @ 0x008e42d0
void __fastcall Fn8e42d0(void* p)
{
    void* sub = *(void**)((char*)p + 0x10);
    int   id  = *(int*)((char*)p + 0x2c);
    ((StylesheetQueue*)sub)->Fn8e2900(id);
}

// @ 0x008e42e0
void StylesheetQueue::Fn8e42e0(void* arg)
{
    char* c = (char*)this;
    if (*(int*)(c + 0x2c) == -1) {
        *(int*)(c + 0x2c) = Fn8e3850(*(void**)(c + 0x10));
    }
    void* sub = *(void**)(c + 0x10);
    int   id  = *(int*)(c + 0x2c);
    ((StylesheetQueue*)sub)->Fn8e28b0(id, arg);
}

// @ 0x008e49e0
void Element::CollectText(void* wstr)
{
    Element* self = this;
    void* end = (char*)self + 0x18;
    IntList* list = (IntList*)end;
    for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
        if (Fnfc7e50(n) == 1) {
            ((void (__thiscall*)(Node*, void*))(*(void***)n)[0x8 / 4])(n, wstr);
        } else if (Fnfc7e50(n) == 2) {
            u16* b = *(u16**)((char*)n + 0x18);
            u16* e = (u16*)((char*)b + *(u32*)((char*)n + 0x1c) * 2);
            Fn429580(wstr, b, e);
        }
    }
}

// @ 0x008e4b10
u8 Element::AddSubElement(const u16* name)
{
    Element* self = this;
    const u16* v = self->GetAttrValue( (const u16*)g_wstr_src);
    if (v == 0)
        return 0;
    void* doc = self->mpDocument;
    if (doc == 0)
        return 0;
    void* p = *(void**)((char*)doc + 0x4c);
    void* q;
    if (p != 0) q = p; else q = *(void**)((char*)doc + 0x48);
    Fn8e3fa0((void**)q, (u16*)self, (u16*)v);
    return 1;
}

// @ 0x008e5320
char __stdcall Fn8e5320(float* out)
{
    out[1] = 16.0f;
    out[0] = 16.0f;
    int* p = (int*)Fn8e42d0Get();
    if (p != 0) {
        int* r = (int*)(*(int* (__thiscall**)(int*, int))(*(int*)p + 0xc))(p, 0x2f84737);
        if (r != 0) {
            float tmp[2];
            tmp[0] = (float)r[0];
            tmp[1] = (float)r[1];
            out[0] = tmp[0];
            out[1] = tmp[1];
        }
    }
    return 1;
}

// @ 0x008e5370
void* GuiThing::Fn8e5370(int a, int b, int c)
{
    Fn8e4400(a, b, c);
    *(void**)this = (void*)0x1436da8;
    return this;
}

// @ 0x008e55d0
void* GuiThing2::Fn8e55d0(int a, int b, int c)
{
    Fn8e52b0(a, 2);
    *(void**)this = (void*)0x1437bd8;
    *(int*)((char*)this + 0x18) = b;
    *(int*)((char*)this + 0x1c) = c;
    return this;
}

// @ 0x008e5600
void XmlParser::Fn8e5600(short* p, int n)
{
    char* c = (char*)this;
    if (n <= 0) return;
    do {
        short s = *p;
        if (s == 10 || s == 0xd) {
            *(char*)(c + 0x438) = 0;
            *(int*)(c + 0x434) = 0;
        } else {
            int idx = *(int*)(c + 0x434);
            *(short*)(c + 0x22c + idx * 2) = s;
            idx = idx + 1;
            *(int*)(c + 0x434) = idx;
            p++;
            if ((unsigned int)idx > 0xff) {
                *(char*)(c + 0x438) = 1;
                *(int*)(c + 0x434) = 0;
            }
        }
        *(int*)(c + 0x430) = *(int*)(c + 0x430) + 1;
        n = n - 1;
    } while (n > 0);
}

// @ 0x008e5980
void Fn8e5980(void* self, short* p, int n)
{
    ((XmlParser*)self)->Fn8e5600(p, n);
}

// @ 0x008e6130
void* GuiThing3::Fn8e6130(void* a)
{
    char* c = (char*)this;
    *(int*)(c + 4) = 0;
    *(int*)(c + 8) = 0;
    *(void**)c = (void*)0x1437bf4;
    *(void**)(c + 0xc) = a;
    *(int*)(c + 0x10) = -1;
    *(int*)(c + 0x14) = 0;
    *(int*)(c + 0x18) = 3;
    *(int*)(c + 0x1c) = 0;
    *(float*)(c + 0x20) = 0.0f;
    *(int*)(c + 0x24) = 0;
    *(float*)(c + 0x28) = 0.0f;
    *(int*)(c + 0x2c) = 0;
    *(char*)(c + 0x44) = 0;
    return this;
}

// @ 0x008e6180
void Q18::Fn8e6180(void* arg)
{
    char* c = (char*)this;
    if (*(int*)(c + 0x10) == -1) {
        void* s = ((SubA*)*(void**)(c + 0xc))->Fn8ec910();
        *(void**)(c + 0x10) = s;
    }
    ((SubB*)*(void**)(c + 0xc))->Fn8eb910(*(void**)(c + 0x10), arg);
}

// @ 0x008eaba0
bool EA::XHTML::Layout::ContainerItem::Pick(EA::XHTML::Layout::PickingContext& ctx, EA::XHTML::Layout::PickEntry* pEntry)
{
    void* pSaved = ctx.mpPickedItem;
    ctx.mpPickedItem = mpElement;
    bool bFound = false;
    for (EA::XHTML::Layout::ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it) {
        if (it->Pick(ctx, pEntry)) {
            bFound = true;
            break;
        }
    }
    ctx.mpPickedItem = pSaved;
    return bFound;
}

// @ 0x008ead40
void EA::XHTML::Layout::Block::PlaceControls(EA::XHTML::Layout::RenderingContext& ctx)
{
    mPlaceStateA = ctx.mTypesetter.GetState();
    mPlaceStateB = 0xffffffff;
    if (mpBorder != 0 || mpBackground != 0 || (mBgColor & 0xff000000) != 0) {
        mpPlaceChain = ctx.mpPlaceChain;
        ctx.mpPlaceChain = this;
    }
    RenderContent(&ctx);
    mPlaceStateB = ctx.mTypesetter.GetState();
}

// @ 0x008eadb0
void EA::XHTML::Layout::Block::SetStyle(EA::XHTML::Layout::RenderingContext& ctx, const Style::StyleState& baseStyle)
{
    Style::StyleState style(&const_cast<Style::StyleState&>(baseStyle));
    Style::ComputeStyle(mpElement, mStyleRules, mnRuleCount, &style);
    if (style.mDisplay == 0) {
        return;
    }
    style.Resolve();
    SetUpBox(ctx, style);
    v24(ctx, style);
}

// @ 0x008eae80
void EA::XHTML::Style::ComputeStyle(void* pElement, EA::XHTML::Style::Rule** pRules, unsigned int nRuleCount, EA::XHTML::Style::StyleState* pStyle)
{
    if (nRuleCount == 0) {
        return;
    }
    for (unsigned int i = 0; i < nRuleCount; ++i) {
        EA::XHTML::Style::Rule* pRule = pRules[i];
        EA::XHTML::Style::Selector* pSelector = pRule->mpSelector;
        if (pSelector == 0 || pSelector->Match(pElement, 0)) {
            for (EA::XHTML::Style::Declaration* p = pRule->mpDeclarations->mList[0].mpFirst; p != 0;
                 p = p->mpNext) {
                p->Apply(pStyle);
            }
        }
    }
    for (unsigned int i = 0; i < nRuleCount; ++i) {
        EA::XHTML::Style::Rule* pRule = pRules[i];
        EA::XHTML::Style::Selector* pSelector = pRule->mpSelector;
        if (pSelector == 0 || pSelector->Match(pElement, 0)) {
            for (EA::XHTML::Style::Declaration* p = pRule->mpDeclarations->mList[1].mpFirst; p != 0;
                 p = p->mpNext) {
                p->Apply(pStyle);
            }
        }
    }
}

// @ 0x008eaf30
bool EA::XHTML::Layout::Item::IntersectSelection(uint* pOutOffset, uint* pOutLength, uint nLength)
{
    EA::XHTML::Layout::Page_s008e_a290* pPage = mpPage;
    uint selStart = pPage->mSelectionStart;
    uint selEnd = pPage->mSelectionEnd;
    uint base = mSelectableIndex;
    if (selEnd <= base)
        return false;
    if (selStart >= base + nLength)
        return false;
    *pOutOffset = (selStart > base) ? selStart - base : 0;
    if (selEnd < base + nLength)
        *pOutLength = selEnd - base;
    else
        *pOutLength = nLength;
    return true;
}

// @ 0x008edd30
void* __stdcall StyleCtorForward(void* self, void* rect)
{
    return EA::XHTML::Layout::StyleCtor(self, 0, rect, 0, 0);
}

// @ 0x008edd50
void __stdcall ScrollbarStyleSet(const EA::XHTML::Layout::Vec2* value)
{
    char* p = (char*)EA::XHTML::Layout::ScrollAppGet() + 0xf8;
    *(int*)(p + 0x250) = *(int*)&value->x;
    *(int*)(p + 0x244) = *(int*)&value->y;
}

// @ 0x008edd80
void __stdcall ScrollbarStyleGet(EA::XHTML::Layout::Vec2* out)
{
    char* p = (char*)EA::XHTML::Layout::ScrollAppGet();
    int a = *(int*)(p + 0x348);
    p += 0xf8;
    *(int*)&out->x = a;
    *(int*)&out->y = *(int*)(p + 0x244);
}

// @ 0x008ef8d0
void EA::XHTML::Layout::SizingContext_s008e_ebb0::AddRun(const wchar_t* s, unsigned n, int style)
{
    SetRunStyle(style);
    AddTextRun(s, n);
}

// @ 0x008efad0
StackingContext::StackingContext(u32 owner)
{
    pad00 = owner;
    ((TypesetterCtor*)&mTypesetter)->Construct(0);
    mf534 = 0.0f; mf538 = 0.0f; mf53c = 0.0f; mf540 = 0.0f;
    mf544 = 0.0f; mf548 = 0.0f; mf54c = 0.0f; mf550 = 0.0f;
    mf554 = 0.0f; mf558 = 0.0f; mf55c = 0.0f; mf560 = 0.0f;
    mf564 = 0.0f; mf568 = 0.0f; mf56c = 0.0f; mf570 = 0.0f;
    mb574 = 1;
    mpFloatsHead = 0;
    mpFloatsTail = 0;
    mf580 = 0;
}

// @ 0x008efc80
void StackingContext::SetContextRect(const RectF& r)
{
    mf534 = r.l;
    mf538 = r.t;
    mf53c = r.r;
    mf540 = r.b;
    mf554 = mf534;
    mf558 = mf53c;
}

// @ 0x008efd50
void StackingContext::RecomputeFloatLimits()
{
    float x = mf534;
    float* pf554 = &mf554;
    float* pf558 = &mf558;
    *pf558 = mf53c;
    *pf554 = x;
    for (FloatEntry* p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (p->mKind == 1) {
            float v = p->mSide2 + x;
            float* s = (v > *pf554) ? &v : pf554;
            *pf554 = *s;
        } else {
            float v = p->mOuter + x;
            float* s = (*pf558 > v) ? pf558 : &v;
            *pf558 = *s;
        }
    }
}

// @ 0x008efde0
void StackingContext::AddFloats(LineLayout_s008e_fad0* line)
{
    ValueFlagPair it;
    it.Store(line);
    it.Assign(0);
    int index;
    while (it.Next(&index)) {
        InlineBox* e = (InlineBox*)((char*)line->mpBoxes + (index << 5));
        u32 v = e->mpItemAndFlags;
        if ((v & 3u) == 0)
            ((Block_s008e_fad0*)(v & ~3u))->MoveTo((float)ceil((double)(e->mfX - mf534)),
                                        (float)ceil((double)e->mfY));
    }
}
