// src/game/UTFSpore_Win32/ContainerItem.cpp -- migrated from slice(s) s008e8080 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ContainerItem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/Typesetter.h"
#include <math.h>

// ---- items of slice s008e8080 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
void FreeMem(void* p);
}
namespace EA {
template <typename T>
class RectT_s008e_8080 { public:
    T mLeft, mTop, mRight, mBottom;
    RectT_s008e_8080() {}
    RectT_s008e_8080(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    RectT_s008e_8080(const RectT_s008e_8080& x) : mLeft(x.mLeft), mTop(x.mTop), mRight(x.mRight), mBottom(x.mBottom) {}
    RectT_s008e_8080& operator=(const RectT_s008e_8080& x)
    {
        mLeft = x.mLeft; mTop = x.mTop; mRight = x.mRight; mBottom = x.mBottom;
        return *this;
    }
    T Width() const { return mRight - mLeft; }
    T Height() const { return mBottom - mTop; }
    void Inflate(T l, T t, T r, T b)
    {
        mLeft -= l; mTop -= t; mRight += r; mBottom += b;
    }
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
namespace eastl {
struct intrusive_list_node {
    intrusive_list_node* mpNext;
    intrusive_list_node* mpPrev;
};
}
}
namespace EA {
namespace eastl {
template <typename T>
class intrusive_list_iterator { public:
    T* mpNode;
    intrusive_list_iterator() {}
    explicit intrusive_list_iterator(T* pNode) : mpNode(pNode) {}
    intrusive_list_iterator(const intrusive_list_iterator& x) : mpNode(x.mpNode) {}
    __forceinline T& operator*() const { return *mpNode; }
    __forceinline T* operator->() const { return mpNode; }
    __forceinline intrusive_list_iterator& operator++()
    {
        mpNode = static_cast<T*>(mpNode->mpNext);
        return *this;
    }
    __forceinline bool operator==(const intrusive_list_iterator& x) const { return mpNode == x.mpNode; }
    __forceinline bool operator!=(const intrusive_list_iterator& x) const { return mpNode != x.mpNode; }
};
}
}
namespace EA {
namespace eastl {
class intrusive_list_base {
public:
    intrusive_list_node mAnchor;
    __forceinline intrusive_list_base() { mAnchor.mpNext = mAnchor.mpPrev = &mAnchor; }
};
}
}
namespace EA {
namespace eastl {
template <typename T>
class intrusive_list : public intrusive_list_base {
public:
    typedef T node_type;
    typedef intrusive_list_iterator<T> iterator;

    __forceinline iterator begin() { return iterator(static_cast<T*>(mAnchor.mpNext)); }
    __forceinline iterator end() { return iterator(static_cast<T*>(&mAnchor)); }
};
}
}
namespace EA {
namespace Text {
class Typesetter_s008e_8080 {
public:
    ~Typesetter_s008e_8080();                 // 0x0089c540
    int GetType();                 // 0x00897680
    uint32_t mData[0x530 / 4];
};  // namespace Text
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
    float mfFontSize, mfEmSize, mfExSize, mfAscent, mfDescent;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Length {
    float mValue;   // +0
    int mUnits;     // +4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class HashTable {
public:
    ~HashTable()
    {
        FreeBuckets(mpBuckets, mnBuckets);
        mnElements = 0;
        if (mnBuckets > 1)
            FreeMem(mpBuckets);
    }
    void FreeBuckets(void* pBuckets, unsigned int nBuckets);   // 0x00693230 (eastl DoAllocateBuckets)

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
        Length mMargin;            // +0x0
        Length mPadding;           // +0x8
        Length mBorder;            // +0x10
        int mBorderStyle;          // +0x18
        unsigned int mBorderColor; // +0x1c
    };

    StyleState(StyleState* pBase);   // 0x008fc130
    ~StyleState();                   // 0x008e8650
    void Resolve();                  // 0x008fc670

    StyleState* mpBase;              // +0x000
    uint32_t pad004[(0x2ec - 0x004) / 4];
    Edge mEdges[4];                  // +0x2ec
    Length mBoxWidth;                // +0x36c
    Length mBoxHeight;               // +0x374
    int mFloat;                      // +0x37c
    int mClearFloat;                 // +0x380
    int mPosition;                   // +0x384
    Length mBoxOffset[4];            // +0x388
    int mDisplay;                    // +0x3a8
    uint32_t pad3ac[(0x3bc - 0x3ac) / 4];
    HashTable mFonts;                // +0x3bc
    HashTable mColors;               // +0x3dc
    HashTable mRules;                // +0x3fc
    uint32_t pad41c[(0x430 - 0x41c) / 4];
    FontMetrics mFontMetrics;        // +0x430
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
    virtual void GetIntrinsicSize(SizeT<float>* pSize);   // +0x10
    virtual bool v05();                                   // +0x14
    virtual bool v06();                                   // +0x18
};  // namespace DOM
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickingContext;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class SizingContext;
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
class Item;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct PickBox {
    float mLeft, mTop, mRight, mBottom, mExtra;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class SizingContext {
public:
    SizingContext(float fEnclosingWidth);   // 0x008ef870
    void Finish();                          // 0x008ef900

    Text::Typesetter_s008e_8080 mTypesetter;           // +0x000
    float mMaxWidth;                        // +0x530
    float mMinWidth;                        // +0x534
    float mEnclosingWidth;                  // +0x538
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext {
public:
    RenderingContext(const RenderingContext& src);            // 0x008ee8c0
    bool TestRect(float x0, float y0, float x1, float y1);    // 0x008eeac0
    void ScrollRect(RectT_s008e_8080<float> rect);                       // 0x008eeb30
    void SetContextRect(const RectT_s008e_8080<float>& rect);            // 0x008eed80
    void PlaceFloat(Item* pItem);                             // 0x008eee30
    void CollapseMargin(float fMargin);                       // 0x008f01b0
    void Reset();                                             // 0x008f0010
    void BeginContent();                                      // 0x008ef550
    void EndContent();                                        // 0x008ef6d0
    void SetSubStyle(Item* pItem, const PickBox* pBox);       // 0x008ee720
    void SetScrollColor(unsigned int color);                  // 0x008ee7a0

    Item* mpContextRoot;                     // +0x000
    Text::Typesetter_s008e_8080 mTypesetter;            // +0x004
    RectT_s008e_8080<float> mContextRect;               // +0x534
    RectT_s008e_8080<float> mBoundsRect;                // +0x544
    float mMarginLeft;                       // +0x554
    float mMarginRight;                      // +0x558
    float mYPos;                             // +0x55c
    float mPendingCollapse;                  // +0x560
    float mMaxBreak;                         // +0x564
    float mMinBreak;                         // +0x568
    float mFirstLineBaseline;                // +0x56c
    float mFirstLineHeight;                  // +0x570
    float mLastLineHeight;                   // +0x574
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickingContext : public Text::Typesetter_s008e_8080 {
public:
    PickingContext(const PickingContext& src);        // 0x008ee2f0
    ~PickingContext();                                // 0x008e8620
    bool Flush(PickEntry* pEntry);                    // 0x008ee010
    bool FlushAll(PickEntry* pEntry);                 // 0x008ee4a0
    void PlaceFloat(Item* pItem);                     // 0x008edf60
    void SetContextRect(const float* rect);           // 0x008ede40
    void SetContextRect(Item* pItem, const RectT_s008e_8080<float>* rect);   // 0x008edd30

    float mX530;              // +0x530
    float mY534;              // +0x534
    float mX538;              // +0x538
    float mY53c;              // +0x53c
    float mVal540;            // +0x540
    RectT_s008e_8080<float> mBoundsRect; // +0x544
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
class Item : public eastl::intrusive_list_node {
public:
    virtual void v00();                                                        // +0x00
    virtual void v04(unsigned int nColor);                                     // +0x04
    virtual void Measure(SizingContext& sc, Style::StyleState& style);         // +0x08
    virtual void LayoutFlow(RenderingContext& ctx, Style::StyleState& style);  // +0x0c
    virtual void PlaceControls(unsigned int nArg);                             // +0x10
    virtual void Render(RenderingContext& ctx);                                // +0x14
    virtual bool Pick(PickingContext& ctx, PickEntry* pEntry);                 // +0x18
    virtual void v1c();                                                        // +0x1c
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style);  // +0x20
    virtual void v24();                                                        // +0x24
    virtual void PlaceControlsContent(unsigned int nArg);                      // +0x28
    virtual void RenderContent(RenderingContext& ctx);                         // +0x2c
    virtual bool PickContent(PickingContext& ctx, PickEntry* pEntry);          // +0x30
    virtual void Layout(RenderingContext& ctx, Style::StyleState& style);      // +0x34
    virtual void Scroll(RectT_s008e_8080<float> rect);                                    // +0x38
    virtual void PlaceOutOfFlow(RenderingContext& ctx, Style::StyleState& style);  // +0x3c

    void* mpPage;                       // +0x0c
    ItemType mItemType;                 // +0x10
    unsigned int mSelectableIndex;      // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
typedef eastl::intrusive_list<Item> ItemList;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem : public Item {
public:
    virtual void PlaceControls(unsigned int nArg);   // +0x10

    ItemList mChildItems;               // +0x18
};
}
}
}
// ---- items of slice s008e8080 end

// @ 0x008e85d0
namespace EA { namespace XHTML { namespace Layout {
void ContainerItem::PlaceControls(unsigned int nArg)
{
    for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it.mpNode->PlaceControls(nArg);
}
}}}  // namespace EA::XHTML::Layout
