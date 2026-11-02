// src/game/UTFSpore_Win32/ListItem.cpp -- migrated from slice(s) s008eb250, s008ea290, s00614f20 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ListItem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "SP/Pollen/cAssetDirectory.h"
#include "SP/Pollen/cAssetMetadata.h"
#include "SP/Pollen/cModelUploadTransaction.h"
#include "SP/Pollen/cServerResponse.h"
#include "SP/Pollen/cTransactionQueue.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#include <intrin.h>
#include "EA/Text/LineLayout.h"
#include "EA/XHTML/Layout/Page.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/Text/Typesetter.h"
#include <math.h>
#include <stddef.h>
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include <string.h>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(wcscmp)

// ---- items of slice s00614f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0 (EASTL allocate)
struct IFactory { virtual void slot0(); virtual int AddRef(); virtual int Release(); };
template <typename T> struct RefPtr {
    T* p;
    RefPtr() : p(0) {}
    void AssignOutOfLine(T* o);   // 0x00572620 (out-of-line AutoRefCount::operator=)
    __forceinline RefPtr& operator=(T* o) {
        if (o != p) {
            T* t = p;
            if (o) o->AddRef();
            p = o;
            if (t) t->Release();
        }
        return *this;
    }
};
struct cThrottleObj : IFactory { int mnRef; cThrottleObj(); };    // 0x0093c430
struct cThrottleOwner { char pad[0x43c]; int mnCount; char pad2[0xf3c - 0x440]; RefPtr<IFactory> mpThrottle; };
// ---- items of slice s00614f20 end

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
class Element {
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
class ListItem;
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
    void Add(DOM::Element* pElement, int nArg, unsigned int nIndex, const PickBox* pBox);  // 0x008e69b0
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
    DOM::Element* mpElement;  // +0x20
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block : public ContainerItem {
public:
    Block(Page_s008e_a290* pPage, DOM::Element* pElement, int nType);                    // 0x008e7f90
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
class ImageRequester {
public:
    virtual ~ImageRequester();
    virtual void vf04();
    virtual void OnImageRequest(void* pArg);
    void* mpVf1;          // +0x04
    unsigned int mnJobId; // +0x08
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ListItem : public Block, public ImageRequester {
public:
    ListItem(Page_s008e_a290* pPage, DOM::Element* pElement);  // 0x008eb250

    void Place(RenderingContext& ctx, Style::StyleState& style);  // 0x008eafa0
    void DrawContent(RenderingContext& ctx);                      // 0x008eb000

    int mListStyleType;              // +0xd0
    const wchar_t* mMarkerImageURI;  // +0xd4
    wchar_t* mMarkerTextBegin;       // +0xd8
    wchar_t* mMarkerTextEnd;         // +0xdc
    wchar_t* mMarkerTextCapacity;    // +0xe0
    uint32_t pade4[(0xec - 0xe4) / 4];
    float mMarkerWidth;    // +0xec
    float mLineY;          // +0xf0
    float mLineHeight;     // +0xf4
    void* mpTextStyle;     // +0xf8
    int mImageTableIndex;  // +0xfc
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
const float kHalf = 0.5f;             // 0x01471064
const float kSixteen = 16.0f;         // 0x014763b0
const float kNegEight = -8.0f;        // 0x01437c88
const float kEight = 8.0f;            // 0x013eeda0
// ---- items of slice s008ea290 end

// ---- items of slice s008eb250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t kStr_None[];        // 0x01437CE8
extern const wchar_t kStr_Disc[];        // 0x01437CE4
extern const wchar_t kStr_Circle[];      // 0x01437CE0
extern const wchar_t kStr_DecimalFmt[];  // 0x01437CD8
extern const wchar_t kStr_list[];        // 0x013F58AC  L"list"
extern const unsigned short kRomanSizes[];     // 0x0154CF5C
extern const wchar_t* const kRomanUpperStr[];  // 0x0154CFC4
extern const wchar_t* const kRomanLowerStr[];  // 0x0154CF90
namespace eastl {
struct intrusive_list_node_s008e_b250 {
    intrusive_list_node_s008e_b250* mpNext;
    intrusive_list_node_s008e_b250* mpPrev;
    void Destroy();  // 0x00620230
};  // namespace eastl
}
namespace EA {
namespace Allocator {
class StackAllocator_s008e_b250 {
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
};  // namespace Allocator
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState_s008e_b250 { public:
    uint32_t pad000[0x37c / 4];
    int mFloat;                      // +0x37c
    uint32_t pad380;
    int mPosition;                   // +0x384
    uint32_t pad388[(0x3a8 - 0x388) / 4];
    int mDisplay;                    // +0x3a8
    int mWhiteSpace;                 // +0x3ac
    int mListStyleType;              // +0x3b0
    const wchar_t* mListStyleImage;  // +0x3b4
    uint32_t pad3b8[(0x450 - 0x3b8) / 4];
};  // namespace Style
}
}
}
namespace EA {
namespace XHTML {
namespace Text {
struct TextStyle_s008e_b250 { uint32_t mData[0x27c / 4]; };
}
}
}
namespace EA {
namespace XHTML {
namespace Text {
class Typesetter_s008e_b250 {
public:
    uint32_t mData[0x240 / 4];
    void Reset(bool bReset);  // 0x0089cdf0 (EA::XHTML::Text::Typesetter::Reset)
    void SetWidth(float fLineWidth, float x, float y);
    int LayoutLine(const wchar_t* pText, unsigned int nLength, float fLineWidth, float fY,
                   const TextStyle_s008e_b250* pStyle);
    void* GetLineLayout();  // 0x008976a0 (EA::XHTML::Text::Typesetter::GetLineLayout)
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_b250;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item_s008e_b250;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem_s008e_b250;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block_s008e_b250;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ListItem_s008e_b250;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Border_s008e_b250;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Background_s008e_b250;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item_s008e_b250 : public eastl::intrusive_list_node_s008e_b250 {
public:
    Item_s008e_b250(Page_s008e_b250* pPage, int itemType);  // 0x008EAE40
    virtual ~Item_s008e_b250();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();

    Page_s008e_b250* mpPage;                   // +0x0c
    int mItemType;                  // +0x10
    unsigned int mSelectableIndex;  // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem_s008e_b250 : public Item_s008e_b250 {
public:
    __forceinline ContainerItem_s008e_b250(Page_s008e_b250* pPage, int type) : Item_s008e_b250(pPage, type) {}
    eastl::intrusive_list_node_s008e_b250 mChildItems;  // +0x18
    void* mpElement;                         // +0x20
    void* mStyleRules;                       // +0x24
    unsigned int mnRuleCount;                // +0x28
    int mDisplay;                            // +0x2c
    int mPosition;                           // +0x30
    int mPlacement;                          // +0x34
    unsigned int mFgColor;                   // +0x38
    unsigned int mBgColor;                   // +0x3c
    Border_s008e_b250* mpBorder;                        // +0x40
    Background_s008e_b250* mpBackground;                // +0x44
    uint32_t mParaStyle[(0x50 - 0x48) / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block_s008e_b250 : public ContainerItem_s008e_b250 {
public:
    Block_s008e_b250(Page_s008e_b250* pPage, void* pElement, int type);  // 0x008E7F90
    uint32_t pad50[(0xc4 - 0x50) / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ListItem_s008e_b250 : public Block_s008e_b250, public ImageRequester {
public:
    ListItem_s008e_b250(Page_s008e_b250* pPage, void* pElement);  // 0x008EB250
    ~ListItem_s008e_b250();                            // 0x008EB2E0

    void FormatMarkerText(unsigned int index);                            // 0x008EB350
    void PlaceContent(void* pLayoutContext, const Style::StyleState_s008e_b250& s);  // 0x008EB520

    int mListStyleType;              // +0xd0
    const wchar_t* mMarkerImageURI;  // +0xd4
    wchar_t* mMarkerTextBegin;       // +0xd8
    wchar_t* mMarkerTextEnd;         // +0xdc
    wchar_t* mMarkerTextCapacity;    // +0xe0
    uint32_t pade4[(0xec - 0xe4) / 4];
    float mMarkerWidth;  // +0xec
    uint32_t padf0[2];
    void* mpTextStyle;    // +0xf8
    int mImageTableIndex;  // +0xfc
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_b250 {
public:
    EA::Allocator::StackAllocator_s008e_b250 mAllocator;  // +0x00
    uint32_t pad24[(0x3c - 0x24) / 4];
    Item_s008e_b250* mpRootItem;  // +0x3c
    void* mpLastWS;    // +0x40
    uint32_t pad44[(0x258 - 0x44) / 4];
    void* mpResources;       // +0x258
    void* mpImageRequester;  // +0x25c
    void* mpFocusItem;       // +0x260
    uint32_t pad264[2];
    unsigned int mSelStart;  // +0x26c
    unsigned int mSelEnd;    // +0x270
    unsigned int mSelMin;    // +0x274
    unsigned int mSelMax;    // +0x278
    uint32_t pad27c[(0x2a0 - 0x27c) / 4];

    void Render(Text::Typesetter_s008e_b250* pTS, const float* pRect, const void* pState);  // 0x008EB870
    void* GetResource(int index);                                                // 0x008EB960
    void* GetTextStyle(const Style::StyleState_s008e_b250& s);                              // 0x008EC580
    void NotifyImagesAbandoned();                                                // 0x008EB7A0
    void SetImageRequester(void* pNew, int flag);                                // 0x008EB7E0
    void SetChildItem(unsigned int index, void* pItem);                          // 0x008EB910
    void ImageRequestCallback(int* pMsg);                                        // 0x008EB980
    void SetSelectionRange(unsigned int a, unsigned int b);                      // 0x008EBA20
    void CreateAttributeStyles(void* pElement, void* pOut);                      // 0x008EBDE0
    static void DestroyItem(ContainerItem_s008e_b250* pItem);                               // 0x008EBD50
};
}
}
}
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
};
WString* WStr_Assign(WString* pStr, const wchar_t* pSrc);                      // 0x005C3D90
void WStr_PushBack(WString* pStr, wchar_t c);                                  // 0x004F6510
void WStr_Append(WString* pStr, const wchar_t* pFirst, const wchar_t* pLast);  // 0x00429580
void WStr_Format(WString* pStr, const wchar_t* pFmt, ...);                     // 0x0041E050
int StyleState_GetCounter(const EA::XHTML::Style::StyleState_s008e_b250* pState, const wchar_t* pName);  // 0x008FBDA0
void ImageRequest_Request(void* pRequester, const wchar_t* pURI);              // 0x008EC5E0
void PlaceBlock(const EA::XHTML::Style::StyleState_s008e_b250& s, void* pLayoutContext);  // 0x008EAAF0
using EA::XHTML::Style::StyleState_s008e_b250;
// ---- items of slice s008eb250 end

// @ 0x00615c70
bool __stdcall UpdateThrottle(cThrottleOwner* o)
{
    if (o) {
        int n = o->mnCount;
        if (n >= 400) {
            cThrottleObj* t = new ("Pollinator", 0, 0, 0, 0) cThrottleObj();
            o->mpThrottle = t;
        } else if (n >= 300) {
            cThrottleObj* t = new ("Pollinator", 0, 0, 0, 0) cThrottleObj();
            o->mpThrottle.AssignOutOfLine(t);
        }
        return true;
    }
    return false;
}

// @ 0x008eafa0
void EA::XHTML::Layout::ListItem::Place(EA::XHTML::Layout::RenderingContext& ctx, Style::StyleState& style)
{
    PlaceContent(ctx, style);
    mLineY = ctx.mFirstLineBaseline;
    mLineHeight = ctx.mFirstLineHeight;
}

// @ 0x008eb000
void EA::XHTML::Layout::ListItem::DrawContent(EA::XHTML::Layout::RenderingContext& ctx)
{
    ctx.SetScrollColor(mFgColor);

    if (mMarkerImageURI != 0) {
        if (mImageTableIndex != -1) {
            EA::XHTML::Layout::Resource* pResource = mpPage->GetResource(mImageTableIndex);
            if (pResource != 0) {
                void* pImage = pResource->GetInterface(EA::XHTML::Layout::Resource::kImageInterface);
                if (pImage != 0) {
                    float markerW = kSixteen;
                    float markerH = kSixteen;
                    void** pImageVtbl = *(void***)pImage;
                    void* pSize =
                        (*(void*(__thiscall**)(void*, unsigned int))((char*)pImageVtbl + 0xc))(
                            pImage, EA::XHTML::Layout::Resource::kImageSizeInterface);
                    if (pSize != 0) {
                        markerW = (float)*(int*)pSize;
                        markerH = (float)*(int*)((char*)pSize + 4);
                    }
                    float y = (float)floor((double)((mLineHeight - markerH) * kHalf));
                    ctx.SetScrollColor(0xffffffff);
                    ctx.DrawQuadGradient(mContentRect.mLeft + (kNegEight - markerW),
                                         mContentRect.mTop + y, markerW, markerH, pImage);
                    EA::XHTML::Layout::Block::DrawContent(ctx);
                    return;
                }
            }
        }
    } else if (mListStyleType != 0) {
        ctx.mTypesetter.Reset(true);
        ctx.mTypesetter.SetWidth(ctx.mMarginRight - ctx.mMarginLeft - mMarkerWidth,
                                 ctx.mMarginLeft, ctx.mContextRect.mTop);
        const float x = ctx.mContextRect.mLeft + mContentRect.mLeft - mMarkerWidth - kEight;
        const float yy = mContentRect.mTop + ctx.mContextRect.mTop;
        ctx.mTypesetter.LayoutLine(mMarkerTextBegin, (int)(mMarkerTextEnd - mMarkerTextBegin),
                                   x, yy, (const EA::XHTML::Text::TextStyle*)mpTextStyle);
        EA::XHTML::Text::LineLayout* pLine = ctx.mTypesetter.GetLineLayout();
        mMarkerWidth = pLine->mHeight;
        int nGlyphs = (int)((char*)pLine->mpGlyphsEnd - (char*)pLine->mpGlyphsBegin) >> 5;
        pLine->OffsetSegment(0.0f,
                             (float)floor((double)(mLineY - pLine->mBaseline)), 0, nGlyphs);
        ctx.mpContextRoot->RenderContent(pLine);
        ctx.mTypesetter.Reset(true);
    }

    EA::XHTML::Layout::Block::DrawContent(ctx);
}

// @ 0x008eb250
EA::XHTML::Layout::ListItem_s008e_b250::ListItem_s008e_b250(EA::XHTML::Layout::Page_s008e_b250* pPage, void* pElement)
: EA::XHTML::Layout::Block_s008e_b250(pPage, pElement, 5)
{
    EA::XHTML::Layout::ImageRequester::mnJobId = 0;
    EA::XHTML::Layout::ImageRequester::mpVf1 = 0;
    mListStyleType = 0;
    mMarkerImageURI = 0;
    mMarkerTextBegin = (wchar_t*)kStr_None;
    mMarkerTextEnd = (wchar_t*)kStr_None;
    mMarkerTextCapacity = (wchar_t*)((char*)kStr_None + 2);
    mpTextStyle = 0;
    mImageTableIndex = -1;
}

// @ 0x008eb2e0
EA::XHTML::Layout::ListItem_s008e_b250::~ListItem_s008e_b250()
{
    if (mMarkerTextBegin) {
        unsigned int nBytes = (unsigned int)((char*)mMarkerTextCapacity - (char*)mMarkerTextBegin);
        if ((nBytes & 0xfffffffe) > 2)
            operator delete[]((char*)mMarkerTextBegin);
    }
    mMarkerImageURI = kStr_None;
    mMarkerTextBegin = (wchar_t*)kStr_None;
}

// @ 0x008eb350
void EA::XHTML::Layout::ListItem_s008e_b250::FormatMarkerText(unsigned int index)
{
    WString* pStr = (WString*)((char*)this + 0xd8);
    switch (mListStyleType) {
    case 0:
    case 1:
        WStr_Assign(pStr, kStr_None);
        return;
    case 2:
        WStr_Assign(pStr, kStr_Disc);
        return;
    case 3:
        WStr_Assign(pStr, kStr_Circle);
        return;
    case 4:
        WStr_Format(pStr, kStr_DecimalFmt, index);
        return;
    case 5:
    case 6:
    {
        const wchar_t* const* pTable = (mListStyleType != 6) ? kRomanLowerStr : kRomanUpperStr;
        wchar_t* pBegin = mMarkerTextBegin;
        if (pBegin != mMarkerTextEnd) {
            *pBegin = 0;
            mMarkerTextEnd = pBegin;
        }
        const unsigned short* pSizes = kRomanSizes;
        for (int i = 0; i < 13; i++) {
            while (index >= (unsigned int)pSizes[i]) {
                const wchar_t* pCur = *pTable;
                const wchar_t* pCurEnd = pCur;
                while (*pCurEnd)
                    pCurEnd++;
                WStr_Append(pStr, pCur, pCurEnd);
                index -= pSizes[i];
            }
            pTable++;
        }
        WStr_PushBack(pStr, L'.');
        return;
    }
    case 7:
    {
        wchar_t* pBegin = mMarkerTextBegin;
        if (pBegin != mMarkerTextEnd) {
            *pBegin = 0;
            mMarkerTextEnd = pBegin;
        }
        if (index - 1 < 0x1a) {
            WStr_PushBack(pStr, (wchar_t)(index + 0x60));
            WStr_PushBack(pStr, L'.');
            return;
        }
        WStr_PushBack(pStr, L'?');
        WStr_PushBack(pStr, L'.');
        return;
    }
    case 8:
    {
        wchar_t* pBegin = mMarkerTextBegin;
        if (pBegin != mMarkerTextEnd) {
            *pBegin = 0;
            mMarkerTextEnd = pBegin;
        }
        if (index - 1 < 0x1a) {
            WStr_PushBack(pStr, (wchar_t)(index + 0x40));
            WStr_PushBack(pStr, L'.');
            return;
        }
        WStr_PushBack(pStr, L'?');
        WStr_PushBack(pStr, L'.');
        return;
    }
    default:
        return;
    }
}

// @ 0x008eb520
void EA::XHTML::Layout::ListItem_s008e_b250::PlaceContent(void* pLayoutContext, const Style::StyleState_s008e_b250& s)
{
    int counter = StyleState_GetCounter(&s, kStr_list);

    mListStyleType = s.mListStyleType;
    mMarkerImageURI = s.mListStyleImage;

    if (mMarkerImageURI) {
        bool bUseImage = false;
        if (mImageTableIndex != -1) {
            void* pRes = mpPage->GetResource(mImageTableIndex);
            if (pRes)
                bUseImage = (*(int (**)(void*, int))(*(int*)pRes + 0xc))(pRes, 0xee3f516e) != 0;
        }
        if (!bUseImage) {
            if (!EA::XHTML::Layout::ImageRequester::mnJobId)
                ImageRequest_Request((char*)this + 0xc4, mMarkerImageURI);
        }

        if (mImageTableIndex != -1) {
            void* pRes = mpPage->GetResource(mImageTableIndex);
            if (pRes) {
                void* pImg = (void*)(*(int (**)(void*, int))(*(int*)pRes + 0xc))(pRes, 0xee3f516e);
                if (pImg) {
                    mMarkerWidth = 16.0f;
                    int val = (*(int (**)(void*, int))(*(int*)pImg + 0xc))(pImg, 0x2f84737);
                    if (val)
                        mMarkerWidth = (float)*(int*)(val + 4);
                }
            }
        }
        PlaceBlock(s, (char*)pLayoutContext);
        return;
    }

    if (mListStyleType) {
        mpTextStyle = mpPage->GetTextStyle(s);
        FormatMarkerText((unsigned int)counter);

        char* pBase = (char*)pLayoutContext;
        Text::Typesetter_s008e_b250* pTS = (Text::Typesetter_s008e_b250*)(pBase + 4);
        pTS->Reset(true);
        pTS->SetWidth(*(float*)(pBase + 0x558) - *(float*)(pBase + 0x554), *(float*)(pBase + 0x554),
                      *(float*)(pBase + 0x538));
        pTS->LayoutLine(mMarkerTextBegin, (int)(mMarkerTextEnd - mMarkerTextBegin), 0.0f, 0.0f,
                        (const Text::TextStyle_s008e_b250*)mpTextStyle);
        unsigned char* pLine = (unsigned char*)pTS->GetLineLayout();
        mMarkerWidth = *(float*)(pLine + 0x98);
        pTS->Reset(true);
    }
    PlaceBlock(s, (char*)pLayoutContext);
}
