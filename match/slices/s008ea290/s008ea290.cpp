// Slice s008ea290 (batch gold7) -- 0x008ea290..0x008eb24c.
//
// Border drawing, the container/block item-step dispatchers, the Item ctor /
// Dispose pair, Style::ComputeStyle, a selection-range intersection helper and the
// ListItem::Place / ListItem::DrawContent overrides.  Everything here is EAWebKit's
// EA/XHTML/Layout subtree as built into Spore's SporeApp.exe; the class layouts
// follow the neighbouring slices (s008e8080 drives the same Block/Border/
// RenderingContext objects, s008eb250 the same Item/ContainerItem/ListItem/Page
// tuple) and are repeated here so this translation unit stands alone.
//
// Retail-vs-PDB offsets: EA::Text::Typesetter is 0x530 bytes in retail (0x548 in the
// dev PDB), so every member behind it inside RenderingContext / PickingContext sits
// 0x18 lower than its PDB offset.  A block style carries a per-phrase border table
// at +0x2ec (4 Edge records of 0x20 bytes) that the border code indexes with the
// per-edge phrase indices.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (EA::XHTML module, no /EHsc).
#include "types.h"
#include <math.h>
#include <stddef.h>
#include <new>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

// ------------------------------- EASTL -------------------------------------
namespace eastl {

struct intrusive_list_node {
    intrusive_list_node* mpNext;  // +0x00
    intrusive_list_node* mpPrev;  // +0x04
};

// The list anchor is a node embedded 4 bytes into T, so an iterator converts
// between the stored node address and the owning T* by subtracting 4 (guarding
// the null case).  advance walks the node's mpNext.
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
        intrusive_list_node* pNext = *(intrusive_list_node**)((char*)mpItem + 4);
        mpItem = pNext ? (T*)((char*)pNext - 4) : 0;
        return *this;
    }
};

class intrusive_list_base {
public:
    intrusive_list_node mAnchor;  // +0x00

    __forceinline intrusive_list_base() { mAnchor.mpNext = mAnchor.mpPrev = &mAnchor; }
};

template <typename T>
class intrusive_list : public intrusive_list_base {
public:
    typedef T node_type;
    typedef intrusive_list_iterator<T> iterator;

    __forceinline iterator begin()
    {
        intrusive_list_node* pNode = mAnchor.mpNext;
        return iterator(pNode ? (T*)((char*)pNode - 4) : 0);
    }
    __forceinline iterator end()
    {
        intrusive_list_node* pNode = &mAnchor;
        return iterator(pNode ? (T*)((char*)pNode - 4) : 0);
    }
};

}  // namespace eastl

namespace EA {

template <typename T>
class RectT {
public:
    T mLeft, mTop, mRight, mBottom;  // +0x00..+0x0c

    RectT() {}
    RectT(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    RectT(const RectT& x) : mLeft(x.mLeft), mTop(x.mTop), mRight(x.mRight), mBottom(x.mBottom) {}
    RectT& operator=(const RectT& x)
    {
        mLeft = x.mLeft; mTop = x.mTop; mRight = x.mRight; mBottom = x.mBottom;
        return *this;
    }
    T Width() const { return mRight - mLeft; }
    T Height() const { return mBottom - mTop; }
};

template <typename T>
struct SizeT {
    T w, h;
    SizeT() {}
    SizeT(T aw, T ah) : w(aw), h(ah) {}
};

namespace Allocator {

// EA::Allocator::StackAllocator as laid out at 0x00928ba0's owner: a bump pointer
// pair (begin/end) with a slow-path allocator call when the block is exhausted.
class StackAllocator {
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
};

}  // namespace Allocator

}  // namespace EA

namespace EA {
namespace XHTML {

namespace Style {

class Rule;
class Condition;
class StyleState;

void ComputeStyle(void* pElement, Rule** pRules, unsigned int nRuleCount, StyleState* pStyle);

class FontMetrics { public:
    float mfFontSize;  // +0x00
    float mfEmSize;    // +0x04
    float mfExSize;    // +0x08
    float mfAscent;    // +0x0c
    float mfDescent;   // +0x10
};

struct Length {
    float mValue;  // +0x00
    int mUnits;    // +0x04
};

// The selector half of a rule: slot +0x04 is Match(element, flag).
class Selector {
public:
    virtual void v00();
    virtual bool Match(void* pElement, int flag);  // +0x04
};

// One declaration; slot +0x04 applies it to a style state and mpNext (+0x04)
// threads the list of declarations.
class Declaration {
public:
    virtual void v00();
    virtual void Apply(StyleState* pStyle);  // +0x04

    Declaration* mpNext;  // +0x04
};

// A head for one declaration list.
class DeclarationList {
public:
    Declaration* mpFirst;  // +0x00
};

// A rule carries two declaration lists (applied in two separate passes).
class DeclarationCollection {
public:
    DeclarationList mList[2];  // +0x00, +0x04
};

// A rule: selector (slot +0x04) and the declaration collection to cascade.
class Rule {
public:
    virtual void v00();
    virtual bool Match(void* pElement, int flag);  // +0x04

    Selector* mpSelector;                    // +0x04
    DeclarationCollection* mpDeclarations;   // +0x08
};

// 0x008fba80 / 0x008fba70: StyleState predicates, declared as members above.

class HashTable {
public:
    uint32_t mField00;         // +0x00
    void* mpBuckets;           // +0x04
    unsigned int mnBuckets;    // +0x08
    unsigned int mnElements;   // +0x0c
    uint32_t pad10[4];         // +0x10
};

// One computed style.  The first dword of the object chain is the base style this
// state inherits from; the edges at +0x2ec hold the resolved border/padding values.
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

}  // namespace Style

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
};
}  // namespace DOM

namespace Text {

class LineLayout;

class TextStyle { public:
    uint32_t mData[0x27c / 4];
};

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

}  // namespace Text

namespace Layout {

class Page;
class Item;
class ContainerItem;
class Block;
class ListItem;
class Border;
class Background;
class PickEntry;
class PickBox;

// One slot of the page resource table; the marker code asks a slot for two well
// known interfaces (the image object and its size object).
class Resource {
public:
    virtual void vf00();                          // +0x00
    virtual void vf04();                          // +0x04
    virtual void vf08();                          // +0x08
    virtual void* GetInterface(unsigned int id);  // +0x0c

    static const unsigned int kImageInterface = 0xee3f516e;
    static const unsigned int kImageSizeInterface = 0x02f84737;
};

class SizingContext {
public:
    SizingContext(float fEnclosingWidth);  // 0x008ef870
    void Finish();                         // 0x008ef900

    Text::Typesetter mTypesetter;  // +0x000
    float mMaxWidth;               // +0x530
    float mMinWidth;               // +0x534
    float mEnclosingWidth;         // +0x538
};

// The context threaded through Measure / Layout / Render.  Retail Typesetter is
// 0x530 bytes so every member after it sits 0x18 below the PDB offsets.
class RenderingContext {
public:
    RenderingContext(const RenderingContext& src);           // 0x008ee8c0
    ~RenderingContext();                                     // 0x008e8620
    void EndContent();                                       // 0x008f0010
    void Reset();                                            // 0x008ef6d0
    bool TestRect(float x0, float y0, float x1, float y1);   // 0x008eeac0
    void SetScrollColor(unsigned int color);                 // 0x008ee7a0
    void ScrollRect(RectT<float> rect);                      // 0x008eeb30
    void SetContextRect(const RectT<float>& rect);           // 0x008eed80
    void SetSubStyle(Item* pItem, const PickBox* pBox);      // 0x008ee720
    void DrawQuadGradient(float x, float y, float w, float h, void* pImage);  // 0x008eec80

    Item* mpContextRoot;                     // +0x000
    Text::Typesetter mTypesetter;            // +0x004
    RectT<float> mContextRect;               // +0x534
    RectT<float> mBoundsRect;                // +0x544
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

// The pick context: same object shape, the point being tested lives at +0x538/+0x53c.
class PickingContext : public Text::Typesetter {
public:
    PickingContext(const PickingContext& src);  // 0x008ee2f0
    ~PickingContext();                          // 0x008e8620
    bool Flush(PickEntry* pEntry);              // 0x008ee010
    bool FlushAll(PickEntry* pEntry);           // 0x008ee4a0
    void PlaceFloat(Item* pItem);               // 0x008edf60
    void SetContextRect(const float* rect);     // 0x008ede40
    void SetContextRect(Item* pItem, const RectT<float>* rect);  // 0x008edd30

    float mX530;              // +0x530
    float mY534;              // +0x534
    float mX538;              // +0x538
    float mY53c;              // +0x53c
    void* mpPickedItem;       // +0x540
    RectT<float> mBoundsRect; // +0x544
    float mExtra554;          // +0x554
    float mExtra558;          // +0x558
    float mYPos;              // +0x55c
    uint32_t pad560;          // +0x560
    void* mpVecBegin;         // +0x564
    uint32_t pad568[(0x574 - 0x568) / 4];
    void* mpInline;           // +0x574
    uint32_t pad578[(0xb84 - 0x578) / 4];
};

// Result of the border/phrase walker 0x008e9e30: four border pixel widths, four
// border styles, four rounded border widths and a visible-border flag.
struct BlockMetrics {
    int m0, m1, m2, m3;      // +0x00  borders: left, right, top, bottom
    int m4, m5, m6, m7;      // +0x10  styles:  left, right, top, bottom
    float f8, f9, f10, f11;  // +0x20  rounded: left, right, top, bottom
    uchar mFlag;             // +0x30

    void Compute(const Style::StyleState* pStyle, float reference);  // 0x008e9e30
};

// A block's border object.  The per-edge phrase index selects which 0x20-byte
// Edge record of the style supplies the edge's border parameters.
class Border {
public:
    void Draw(RenderingContext& rc, const RectT<float>* pRect, uchar flags);  // 0x008ea290
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

class Background {
public:
    Background(EA::Allocator::StackAllocator* pAllocator);  // 0x008e6130
    void SetStyle(const Style::StyleState* pStyle);          // 0x008e68f0
    bool Draw(RenderingContext& rc, const RectT<float>* pBounds,
              const RectT<float>* pRect);                    // 0x008e6710
};

// An entry in the picking list; the ctor-shaped helper fills it in place.
class PickEntry {
public:
    void Add(DOM::Element* pElement, int nArg, unsigned int nIndex, const PickBox* pBox);  // 0x008e69b0
};

enum ItemType { kItemNone = 0, kItemBlock = 1 };

// The linked-list node lives 4 bytes into every Item, so list iteration walks the
// node chain and subtracts 4 to recover the owning Item.
class Item : public eastl::intrusive_list_node {
public:
    Item(Page* pPage, int nType);  // 0x008eae40
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
    virtual void Scroll(RectT<float> rect);                                   // +0x38
    virtual void PlaceOutOfFlow(RenderingContext& ctx, Style::StyleState& style);  // +0x3c

    void Dispose();  // 0x008eae70

    // 0x008eaf30: true when this item's [mSelectableIndex, +nLength) range
    // overlaps the page's selection range; *pOutOffset / *pOutLength are the
    // clipped intersection in item-local coordinates.
    bool IntersectSelection(uint* pOutOffset, uint* pOutLength, uint nLength);

    Page* mpPage;                   // +0x0c
    ItemType mItemType;             // +0x10
    unsigned int mSelectableIndex;  // +0x14
};

typedef eastl::intrusive_list<Item> ItemList;

// The list walkers below are the retail codegen for a by-value iterator loop whose
// iterator stores the node address and adjusts by 4.
class ContainerItem : public Item {
public:
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style);  // +0x20
    virtual void LayoutFlow(RenderingContext& ctx, Style::StyleState& style);  // +0x0c
    virtual void Render(RenderingContext& ctx);                                // +0x14
    virtual bool Pick(PickingContext& ctx, PickEntry* pEntry);                 // +0x18

    ItemList mChildItems;     // +0x18
    DOM::Element* mpElement;  // +0x20
};

class Block : public ContainerItem {
public:
    Block(Page* pPage, DOM::Element* pElement, int nType);                    // 0x008e7f90
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
    RectT<float> mOuterRect;            // +0x64
    RectT<float> mBorderRect;           // +0x74
    RectT<float> mPaddingRect;          // +0x84
    RectT<float> mContentRect;          // +0x94
    RectT<float> mPickRect;             // +0xa4
    RectT<float> mBorderWidth;          // +0xb4
};

// Second polymorphic base of ListItem (an image requester), occupying +0xc4 in
// ListItem: a vptr plus two bookkeeping words.
class ImageRequester {
public:
    virtual ~ImageRequester();
    virtual void vf04();
    virtual void OnImageRequest(void* pArg);
    void* mpVf1;          // +0x04
    unsigned int mnJobId; // +0x08
};

class ListItem : public Block, public ImageRequester {
public:
    ListItem(Page* pPage, DOM::Element* pElement);  // 0x008eb250

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

class RefItem {
public:
    virtual void vf0();
    virtual void Release(int flag);
};

class Page {
public:
    EA::Allocator::StackAllocator mAllocator;  // +0x00
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

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA

using namespace EA;
using namespace EA::XHTML;
using namespace EA::XHTML::Style;
using namespace EA::XHTML::Layout;
using namespace EA::XHTML::Text;

// ---------------------------------------------------------------------------
// External border emitters (reconstructed in slice s008e9a10) and helpers.
// ---------------------------------------------------------------------------
// 0x008e9a10 / 0x008e9b10 / 0x008e9fe0 -- __stdcall: (rc, a, b, edgeIndices, flags[, ...]).
void __stdcall BorderDrawEdges(RenderingContext* rc, float* a, float* b, int* c, uchar flags);
void __stdcall BorderDrawDashes(RenderingContext* rc, float* a, float* b, int* c, uchar flags,
                                float step);
void __stdcall BorderDrawGradients(RenderingContext* rc, float* a, float* b, int* c, float* colors,
                                   uchar flags);

const float kHalf = 0.5f;             // 0x01471064
const float kNegZero = -0.0f;         // 0x013eb8b0
const float kThree = 3.0f;            // 0x013eb95c
const float kNegPointOne = -0.1f;     // 0x013eb964
const float kNegPointTwo = -0.2f;     // 0x013f6a3c
const float kPointOne = 0.1f;         // 0x01488874
const float kPointTwo = 0.2f;         // 0x013ec480
const float kOneThird = 1.0f / 3.0f;  // 0x013f26dc
const float kSixteen = 16.0f;         // 0x014763b0
const float kNegEight = -8.0f;        // 0x01437c88
const float kEight = 8.0f;            // 0x013eeda0

// =====================================================================
// 0x008ea290  EA::XHTML::Layout::Border::Draw
// =====================================================================
// @ 0x008ea290
void Border::Draw(RenderingContext& rc, const RectT<float>* pRect, uchar flags)
{
    // Per-phrase edge mask: a phrase only draws the edges it is selected for.
    ushort edgeFlags[9] = {0};
    edgeFlags[mEdgeLeftPhraseIndex] |= 8;
    edgeFlags[mEdgeRightPhraseIndex] |= 2;
    edgeFlags[mEdgeTopPhraseIndex] |= 1;
    edgeFlags[mEdgeBottomPhraseIndex] |= 4;

    float borderLeft = mBorderLeft;
    float borderRight = mBorderRight;
    float borderTop = mBorderTop;
    float borderBottom = mBorderBottom;
    if (flags & 8)
        borderLeft = 0.0f;
    if (flags & 2)
        borderRight = 0.0f;
    if (flags & 1)
        borderTop = 0.0f;
    if (flags & 4)
        borderBottom = 0.0f;

    if (borderLeft == 0.0f && mEdgeLeftPhraseIndex == 0 && borderRight == 0.0f &&
        mEdgeRightPhraseIndex == 0 && borderTop == 0.0f && mEdgeTopPhraseIndex == 0 &&
        borderBottom == 0.0f && mEdgeBottomPhraseIndex == 0)
        return;

    const RectT<float>& rect = *pRect;
    const float width = rect.mRight - rect.mLeft;
    const float height = rect.mBottom - rect.mTop;

    if (borderLeft + borderRight > width) {
        const float half = (float)floor((double)(width * kHalf));
        borderLeft = (borderLeft > half) ? half : borderLeft;
        borderRight = width - borderLeft;
    }
    if (borderTop + borderBottom > height) {
        const float half = (float)floor((double)(height * kHalf));
        borderTop = (borderTop > half) ? half : borderTop;
        borderBottom = height - borderTop;
    }

    // Outer rect and the rect inset by the resolved border widths.
    float a[4];
    float b[4];
    a[0] = rect.mLeft;
    a[1] = rect.mTop;
    a[2] = rect.mRight;
    a[3] = rect.mBottom;

    b[0] = rect.mLeft + borderLeft;
    b[1] = rect.mTop + borderTop;
    b[2] = rect.mRight - borderRight;
    b[3] = rect.mBottom - borderBottom;

    if (edgeFlags[3] != 0)
        BorderDrawEdges(&rc, a, b, (int*)this, (uchar)edgeFlags[3]);
    if (edgeFlags[1] != 0)
        BorderDrawDashes(&rc, a, b, (int*)this, (uchar)edgeFlags[1], 1.0f);
    if (edgeFlags[2] != 0)
        BorderDrawDashes(&rc, a, b, (int*)this, (uchar)edgeFlags[2], kThree);

    // The 1/3-inset dash rects.
    if (edgeFlags[4] != 0) {
        float c0[4];
        float c1[4];
        const float il = (float)floor((double)((width)*kOneThird)) + kHalf;
        const float it = (float)floor((double)((height)*kOneThird)) + kHalf;
        const float ir = (float)floor((double)((borderRight)*kOneThird)) + kHalf;
        const float ib = (float)floor((double)((borderBottom)*kOneThird)) + kHalf;
        c0[0] = a[0]; c0[1] = a[1]; c0[2] = a[2] - il; c0[3] = a[3] - it;
        c1[0] = a[0] + ir; c1[1] = a[1] + ib; c1[2] = a[2]; c1[3] = a[3];
        BorderDrawEdges(&rc, c0, c1, (int*)this, (uchar)edgeFlags[4]);
        BorderDrawEdges(&rc, c1, c0, (int*)this, (uchar)edgeFlags[4]);
    }

    // Corner banks: two 4-colour ramps swept in opposite directions.
    const float colsNeg[4] = {kNegPointTwo, kNegPointOne, kPointOne, kPointTwo};
    const float colsPos[4] = {kPointTwo, kPointOne, kNegPointOne, kNegPointTwo};
    if (edgeFlags[5] != 0 || edgeFlags[6] != 0) {
        if (edgeFlags[5] != 0) {
            BorderDrawGradients(&rc, a, b, (int*)this, (float*)colsNeg, (uchar)edgeFlags[5]);
            BorderDrawGradients(&rc, b, a, (int*)this, (float*)colsPos, (uchar)edgeFlags[5]);
        }
        if (edgeFlags[6] != 0) {
            BorderDrawGradients(&rc, a, b, (int*)this, (float*)colsPos, (uchar)edgeFlags[6]);
            BorderDrawGradients(&rc, b, a, (int*)this, (float*)colsNeg, (uchar)edgeFlags[6]);
        }
    }
    if (edgeFlags[7] != 0)
        BorderDrawGradients(&rc, a, b, (int*)this, (float*)colsNeg, (uchar)edgeFlags[7]);
    if (edgeFlags[8] != 0)
        BorderDrawGradients(&rc, a, b, (int*)this, (float*)colsPos, (uchar)edgeFlags[8]);
}

// =====================================================================
// 0x008ea9d0  RenderingContext::EndContent thunk
// =====================================================================
// @ 0x008ea9d0
void __stdcall RenderingContext_EndContentThunk(RenderingContext* pCtx, void* pArg)
{
    (void)pArg;
    pCtx->EndContent();
}

// =====================================================================
// 0x008ea9e0  SizingContext::Finish thunk
// =====================================================================
// @ 0x008ea9e0
void __stdcall SizingContext_FinishThunk(SizingContext* pCtx, void* pArg)
{
    (void)pArg;
    pCtx->Finish();
}

// =====================================================================
// 0x008ea9f0  RenderingContext::Reset thunk
// =====================================================================
// @ 0x008ea9f0
void __stdcall RenderingContext_ResetThunk(RenderingContext* pCtx)
{
    pCtx->Reset();
}

// =====================================================================
// 0x008eaa00  PickingContext::FlushAll thunk (returns false)
// =====================================================================
// @ 0x008eaa00
bool __stdcall PickingContext_FlushAllThunk(PickingContext* pCtx, PickEntry* pEntry)
{
    pCtx->FlushAll(pEntry);
    return false;
}

// =====================================================================
// 0x008eaa20  EA::XHTML::Layout::Block::SetUpBox (sizing)
// =====================================================================
// @ 0x008eaa20
void Block::SetUpBox(SizingContext& sc, Style::StyleState& style)
{
    if (mpBorder == 0 && style.HasBorder()) {
        Border* pBorder = 0;
        EA::Allocator::StackAllocator* pAlloc = (EA::Allocator::StackAllocator*)mpPage;
        char* p = pAlloc->mpCurrentObjectBegin;
        if (pAlloc->mpCurrentBlockEnd - pAlloc->mpCurrentObjectBegin - 0x38 >= 0 ||
            pAlloc->AllocateNewBlock(0x38)) {
            p = pAlloc->mpCurrentObjectBegin;
            pAlloc->mpCurrentObjectBegin = p + 0x38;
            pAlloc->mpCurrentObjectEnd = p + 0x38;
            pBorder = (Border*)p;
        }
        mpBorder = pBorder;
    }
    if (mpBorder != 0)
        mpBorder->Compute(&style, sc.mEnclosingWidth);
}

// =====================================================================
// 0x008eaa90  EA::XHTML::Layout::ContainerItem::MeasureContent
// =====================================================================
// @ 0x008eaa90
void ContainerItem::MeasureContent(SizingContext& sc, Style::StyleState& style)
{
    for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it->Measure(sc, style);
}

// =====================================================================
// 0x008eaaf0  EA::XHTML::Layout::ContainerItem::LayoutFlow
// =====================================================================
// @ 0x008eaaf0
void ContainerItem::LayoutFlow(RenderingContext& ctx, Style::StyleState& style)
{
    for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it->LayoutFlow(ctx, style);
}

// =====================================================================
// 0x008eab50  EA::XHTML::Layout::ContainerItem::Render
// =====================================================================
// @ 0x008eab50
void ContainerItem::Render(RenderingContext& ctx)
{
    for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it->Render(ctx);
}

// =====================================================================
// 0x008eaba0  EA::XHTML::Layout::ContainerItem::Pick
// =====================================================================
// @ 0x008eaba0
bool ContainerItem::Pick(PickingContext& ctx, PickEntry* pEntry)
{
    void* pSaved = ctx.mpPickedItem;
    ctx.mpPickedItem = mpElement;
    bool bFound = false;
    for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it) {
        if (it->Pick(ctx, pEntry)) {
            bFound = true;
            break;
        }
    }
    ctx.mpPickedItem = pSaved;
    return bFound;
}

// =====================================================================
// 0x008eac20  EA::XHTML::Layout::Block::SetUpBox (render)
// =====================================================================
// @ 0x008eac20
void Block::SetUpBox(RenderingContext& ctx, Style::StyleState& style)
{
    mFgColor = style.mColor;
    mBgColor = style.mBackgroundColor;
    if (mpBorder == 0 && style.HasBorder()) {
        Border* pBorder = 0;
        EA::Allocator::StackAllocator* pAlloc = (EA::Allocator::StackAllocator*)mpPage;
        char* p = pAlloc->mpCurrentObjectBegin;
        if (pAlloc->mpCurrentBlockEnd - pAlloc->mpCurrentObjectBegin - 0x38 >= 0 ||
            pAlloc->AllocateNewBlock(0x38)) {
            p = pAlloc->mpCurrentObjectBegin;
            pAlloc->mpCurrentObjectBegin = p + 0x38;
            pAlloc->mpCurrentObjectEnd = p + 0x38;
            pBorder = (Border*)p;
        }
        mpBorder = pBorder;
    }
    if (mpBorder != 0)
        mpBorder->Compute(&style, ctx.mContextRect.mRight - ctx.mContextRect.mLeft);

    if (mpBackground == 0 && style.HasBackground()) {
        Background* pBg = 0;
        EA::Allocator::StackAllocator* pAlloc = (EA::Allocator::StackAllocator*)mpPage;
        char* p = pAlloc->mpCurrentObjectBegin;
        if (pAlloc->mpCurrentBlockEnd - pAlloc->mpCurrentObjectBegin - 0x48 >= 0 ||
            pAlloc->AllocateNewBlock(0x48)) {
            p = pAlloc->mpCurrentObjectBegin;
            pAlloc->mpCurrentObjectBegin = p + 0x48;
            pAlloc->mpCurrentObjectEnd = p + 0x48;
            if (p != 0)
                pBg = new (p) Background((EA::Allocator::StackAllocator*)mpPage);
        }
        mpBackground = pBg;
    }
    if (mpBackground != 0)
        mpBackground->SetStyle(&style);

    mBoxWidthPx = style.mBorderMask;
    mBoxHeightPx = style.mBoxWidthPx;
}

// =====================================================================
// 0x008ead40  EA::XHTML::Layout::Block::PlaceControls
// =====================================================================
// @ 0x008ead40
void Block::PlaceControls(RenderingContext& ctx)
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

// =====================================================================
// 0x008eadb0  EA::XHTML::Layout::Block::SetStyle
// =====================================================================
// @ 0x008eadb0
void Block::SetStyle(RenderingContext& ctx, const Style::StyleState& baseStyle)
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

// =====================================================================
// 0x008eae40  EA::XHTML::Layout::Item::Item
// =====================================================================
// @ 0x008eae40
Item::Item(Page* pPage, int nType)
{
    mpPrev = 0;
    mpNext = 0;
    mpPage = pPage;
    mItemType = (ItemType)nType;
    mSelectableIndex = pPage->mSelectableCount;
}

// =====================================================================
// 0x008eae70  EA::XHTML::Layout::Item::Dispose
// =====================================================================
// @ 0x008eae70
void Item::Dispose()
{
    (*(void(__thiscall**)(Item*, int)) * (void**)this)(this, 0);
}

// =====================================================================
// 0x008eae80  EA::XHTML::Style::ComputeStyle
// =====================================================================
// @ 0x008eae80
void EA::XHTML::Style::ComputeStyle(void* pElement, Rule** pRules, unsigned int nRuleCount,
                                    StyleState* pStyle)
{
    if (nRuleCount == 0) {
        return;
    }
    for (unsigned int i = 0; i < nRuleCount; ++i) {
        Rule* pRule = pRules[i];
        Selector* pSelector = pRule->mpSelector;
        if (pSelector == 0 || pSelector->Match(pElement, 0)) {
            for (Declaration* p = pRule->mpDeclarations->mList[0].mpFirst; p != 0;
                 p = p->mpNext) {
                p->Apply(pStyle);
            }
        }
    }
    for (unsigned int i = 0; i < nRuleCount; ++i) {
        Rule* pRule = pRules[i];
        Selector* pSelector = pRule->mpSelector;
        if (pSelector == 0 || pSelector->Match(pElement, 0)) {
            for (Declaration* p = pRule->mpDeclarations->mList[1].mpFirst; p != 0;
                 p = p->mpNext) {
                p->Apply(pStyle);
            }
        }
    }
}

// =====================================================================
// 0x008eaf30  EA::XHTML::Layout::Item::IntersectSelection
// =====================================================================
// @ 0x008eaf30
bool Item::IntersectSelection(uint* pOutOffset, uint* pOutLength, uint nLength)
{
    Page* pPage = mpPage;
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

// =====================================================================
// 0x008eafa0  EA::XHTML::Layout::ListItem::Place
// =====================================================================
// @ 0x008eafa0
void ListItem::Place(RenderingContext& ctx, Style::StyleState& style)
{
    PlaceContent(ctx, style);
    mLineY = ctx.mFirstLineBaseline;
    mLineHeight = ctx.mFirstLineHeight;
}

// =====================================================================
// 0x008eb000  EA::XHTML::Layout::ListItem::DrawContent
// =====================================================================
// @ 0x008eb000
void ListItem::DrawContent(RenderingContext& ctx)
{
    ctx.SetScrollColor(mFgColor);

    if (mMarkerImageURI != 0) {
        if (mImageTableIndex != -1) {
            Resource* pResource = mpPage->GetResource(mImageTableIndex);
            if (pResource != 0) {
                void* pImage = pResource->GetInterface(Resource::kImageInterface);
                if (pImage != 0) {
                    float markerW = kSixteen;
                    float markerH = kSixteen;
                    void** pImageVtbl = *(void***)pImage;
                    void* pSize =
                        (*(void*(__thiscall**)(void*, unsigned int))((char*)pImageVtbl + 0xc))(
                            pImage, Resource::kImageSizeInterface);
                    if (pSize != 0) {
                        markerW = (float)*(int*)pSize;
                        markerH = (float)*(int*)((char*)pSize + 4);
                    }
                    float y = (float)floor((double)((mLineHeight - markerH) * kHalf));
                    ctx.SetScrollColor(0xffffffff);
                    ctx.DrawQuadGradient(mContentRect.mLeft + (kNegEight - markerW),
                                         mContentRect.mTop + y, markerW, markerH, pImage);
                    Block::DrawContent(ctx);
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
                                   x, yy, (const TextStyle*)mpTextStyle);
        LineLayout* pLine = ctx.mTypesetter.GetLineLayout();
        mMarkerWidth = pLine->mHeight;
        int nGlyphs = (int)((char*)pLine->mpGlyphsEnd - (char*)pLine->mpGlyphsBegin) >> 5;
        pLine->OffsetSegment(0.0f,
                             (float)floor((double)(mLineY - pLine->mBaseline)), 0, nGlyphs);
        ctx.mpContextRoot->RenderContent(pLine);
        ctx.mTypesetter.Reset(true);
    }

    Block::DrawContent(ctx);
}
