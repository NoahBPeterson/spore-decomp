// src/game/UTFSpore_Win32/Item.cpp -- migrated from slice(s) s008ea290 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Item.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/LineLayout.h"
#include "EA/XHTML/Layout/Page.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/Text/Typesetter.h"
#include <math.h>
#include <stddef.h>
#include <new>

// ---- items of slice s008ea290 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
namespace eastl {
struct intrusive_list_node_s008e_a290 {
    intrusive_list_node_s008e_a290* mpNext;  // +0x00
    intrusive_list_node_s008e_a290* mpPrev;  // +0x04
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

// @ 0x008eae70
void EA::XHTML::Layout::Item::Dispose()
{
    (*(void(__thiscall**)(EA::XHTML::Layout::Item*, int)) * (void**)this)(this, 0);
}
