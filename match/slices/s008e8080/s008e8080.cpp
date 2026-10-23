// Slice s008e8080 -- EA::XHTML::Layout rendering / picking / measurement and the two
// destructors that live next to them in EAWebKit's Block.cpp:
//
//   008e8080  Block::Render(RenderingContext&)
//   008e8310  AnonymousBox::LayoutFlow(RenderingContext&, StyleState&)
//   008e84b0  AnonymousBox::Render(RenderingContext&)
//   008e8520  AnonymousBox::Pick(PickingContext&, PickEntry*)
//   008e85d0  ContainerItem::PlaceControls(unsigned)
//   008e8620  PickingContext::~PickingContext()
//   008e8650  Style::StyleState::~StyleState()
//   008e8700  Block::Measure(SizingContext&, StyleState&)
//   008e8870  Block::Pick(PickingContext&, PickEntry*)
//
// Item vtable slot map used here (retail 0x01437c20 Block / 0x01437df8 AnonymousBox):
//   +0x08 Measure, +0x0c LayoutFlow, +0x10 PlaceControls, +0x14 Render, +0x18 Pick,
//   +0x20 MeasureContent, +0x28 PlaceControlsContent, +0x2c RenderContent,
//   +0x30 PickContent, +0x38 Scroll, +0x3c PlaceOutOfFlow.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace EA {

// 0x00f47380: ::operator delete
void FreeMem(void* p);

template <typename T>
class RectT { public:
    T mLeft, mTop, mRight, mBottom;
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
    void Inflate(T l, T t, T r, T b)
    {
        mLeft -= l; mTop -= t; mRight += r; mBottom += b;
    }
};

template <typename T>
struct SizeT {
    T w, h;
    SizeT() {}
    SizeT(T aw, T ah) : w(aw), h(ah) {}
};

// ---- EASTL intrusive_list (node_type is a base of T, so iterator steps adjust by the base offset)
namespace eastl {

struct intrusive_list_node {
    intrusive_list_node* mpNext;
    intrusive_list_node* mpPrev;
};

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

class intrusive_list_base {
public:
    intrusive_list_node mAnchor;
    __forceinline intrusive_list_base() { mAnchor.mpNext = mAnchor.mpPrev = &mAnchor; }
};

template <typename T>
class intrusive_list : public intrusive_list_base {
public:
    typedef T node_type;
    typedef intrusive_list_iterator<T> iterator;

    __forceinline iterator begin() { return iterator(static_cast<T*>(mAnchor.mpNext)); }
    __forceinline iterator end() { return iterator(static_cast<T*>(&mAnchor)); }
};

}  // namespace eastl

namespace Text {
class Typesetter {
public:
    ~Typesetter();                 // 0x0089c540
    int GetType();                 // 0x00897680
    uint32_t mData[0x530 / 4];
};
}  // namespace Text

namespace XHTML {

namespace Style {

class Rule;
class StyleState;

class FontMetrics { public:
    float mfFontSize, mfEmSize, mfExSize, mfAscent, mfDescent;
};

struct Length {
    float mValue;   // +0
    int mUnits;     // +4
};

enum EdgeIndex { kEdgeTop = 0, kEdgeRight = 1, kEdgeBottom = 2, kEdgeLeft = 3 };

// eastl::hashtable of the style rule maps; the destructor is 0x008e8650's third of a second.
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

void ComputeStyle(void* pElement, Rule** pRules, unsigned int nRuleCount, StyleState* pStyle);  // 0x008eae80

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

}  // namespace Style

namespace DOM {
class Element {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void GetIntrinsicSize(SizeT<float>* pSize);   // +0x10
    virtual bool v05();                                   // +0x14
    virtual bool v06();                                   // +0x18
};
}  // namespace DOM

namespace Layout {

class RenderingContext;
class PickingContext;
class SizingContext;
class PickEntry;
class Item;
class Block;
class AnonymousBox;

// dom element placement result: size, a float, a top offset and the width again (0x14 bytes).
struct PickBox {
    float mLeft, mTop, mRight, mBottom, mExtra;
};

class SizingContext {
public:
    SizingContext(float fEnclosingWidth);   // 0x008ef870
    void Finish();                          // 0x008ef900

    Text::Typesetter mTypesetter;           // +0x000
    float mMaxWidth;                        // +0x530
    float mMinWidth;                        // +0x534
    float mEnclosingWidth;                  // +0x538
};

// The layout context threaded through Measure/Layout/Render.  Retail Typesetter is 0x530
// bytes so everything after it sits 0x18 below the PDB offsets.
class RenderingContext {
public:
    RenderingContext(const RenderingContext& src);            // 0x008ee8c0
    bool TestRect(float x0, float y0, float x1, float y1);    // 0x008eeac0
    void ScrollRect(RectT<float> rect);                       // 0x008eeb30
    void SetContextRect(const RectT<float>& rect);            // 0x008eed80
    void PlaceFloat(Item* pItem);                             // 0x008eee30
    void CollapseMargin(float fMargin);                       // 0x008f01b0
    void Reset();                                             // 0x008f0010
    void BeginContent();                                      // 0x008ef550
    void EndContent();                                        // 0x008ef6d0
    void SetSubStyle(Item* pItem, const PickBox* pBox);       // 0x008ee720
    void SetScrollColor(unsigned int color);                  // 0x008ee7a0

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
    float mLastLineHeight;                   // +0x574
};

// The pick context: same object shape, but the point being tested lives at +0x538/+0x53c.
class PickingContext : public Text::Typesetter {
public:
    PickingContext(const PickingContext& src);        // 0x008ee2f0
    ~PickingContext();                                // 0x008e8620
    bool Flush(PickEntry* pEntry);                    // 0x008ee010
    bool FlushAll(PickEntry* pEntry);                 // 0x008ee4a0
    void PlaceFloat(Item* pItem);                     // 0x008edf60
    void SetContextRect(const float* rect);           // 0x008ede40
    void SetContextRect(Item* pItem, const RectT<float>* rect);   // 0x008edd30

    float mX530;              // +0x530
    float mY534;              // +0x534
    float mX538;              // +0x538
    float mY53c;              // +0x53c
    float mVal540;            // +0x540
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

class Background {
public:
    bool Draw(RenderingContext& rc, const RectT<float>* pBounds, const RectT<float>* pRect);  // 0x008e6710
};

class Border {
public:
    void Draw(RenderingContext& rc, const RectT<float>* pRect, int nPhase);   // 0x008ea290
};

// An entry in the picking list; the ctor-shaped helper fills it in place.
class PickEntry {
public:
    void Add(DOM::Element* pElement, int nArg, unsigned int nIndex, const PickBox* pBox);  // 0x008e69b0
};

enum ItemType { kItemNone = 0, kItemBlock = 1 };

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
    virtual void Scroll(RectT<float> rect);                                    // +0x38
    virtual void PlaceOutOfFlow(RenderingContext& ctx, Style::StyleState& style);  // +0x3c

    void* mpPage;                       // +0x0c
    ItemType mItemType;                 // +0x10
    unsigned int mSelectableIndex;      // +0x14
};

typedef eastl::intrusive_list<Item> ItemList;

class ContainerItem : public Item {
public:
    virtual void PlaceControls(unsigned int nArg);   // +0x10

    ItemList mChildItems;               // +0x18
};

class Block : public ContainerItem {
public:
    virtual void Measure(SizingContext& sc, Style::StyleState& style);          // +0x08
    virtual void Render(RenderingContext& ctx);                                 // +0x14
    virtual bool Pick(PickingContext& ctx, PickEntry* pEntry);                  // +0x18
    void SetUpBox(SizingContext& sc, Style::StyleState& style);      // 0x008eaa20
    void GetPickBox(PickBox* pBox);                                  // 0x008e7da0

    DOM::Element* mpElement;            // +0x20
    Style::Rule** mStyleRules;          // +0x24
    unsigned int mnRuleCount;           // +0x28
    int mDisplay;                       // +0x2c
    int mPosition;                      // +0x30
    int mPlacement;                     // +0x34
    unsigned int mFgColor;              // +0x38
    unsigned int mBgColor;              // +0x3c
    Border* mpBorder;                   // +0x40
    Background* mpBackground;           // +0x44
    uint32_t pad48[(0x50 - 0x48) / 4];
    bool mbOutOfFlow;                   // +0x50
    int mFloat;                         // +0x54
    float mVerticalOffset;              // +0x58
    Block* mpNextFloat;                 // +0x5c
    Block* mpNextOOF;                   // +0x60
    RectT<float> mOuterRect;            // +0x64
    RectT<float> mBorderRect;           // +0x74
    RectT<float> mPaddingRect;          // +0x84
    RectT<float> mContentRect;          // +0x94
    RectT<float> mPickRect;             // +0xa4
    RectT<float> mBorderWidth;          // +0xb4
};

class AnonymousBox : public ContainerItem {
public:
    virtual void LayoutFlow(RenderingContext& ctx, Style::StyleState& style);   // +0x0c
    virtual void Render(RenderingContext& ctx);                                 // +0x14
    virtual bool Pick(PickingContext& ctx, PickEntry* pEntry);                  // +0x18

    RectT<float> mRect20;               // +0x20
    RectT<float> mRect30;               // +0x30
};

inline float Min(float a, float b) { return (a < b) ? a : b; }
inline float Max(float a, float b) { return (a > b) ? a : b; }
template <typename T> inline T& MaxRef(T& a, T& b) { return (a > b) ? a : b; }

// @ 0x008e8080
void Block::Render(RenderingContext& rc)
{
    if (mPlacement == 3)
    {
        if (mpBackground != 0)
        {
            if (mpBackground->Draw(rc, &rc.mBoundsRect, &mOuterRect))
                goto drawBorder;
        }
        rc.mpContextRoot->v04(mBgColor);
        rc.mpContextRoot->Scroll(rc.mBoundsRect);
        goto drawBorder;
    }

    if (!rc.TestRect(mPickRect.mLeft, mPickRect.mTop, mPickRect.mRight, mPickRect.mBottom))
        return;
    if (!rc.TestRect(mBorderRect.mLeft, mBorderRect.mTop, mBorderRect.mRight, mBorderRect.mBottom))
        goto drawBorder;
    if (mpElement == 0)
        goto drawBorder;
    if (mpElement->v06())
        goto drawBorder;
    if (mpBackground != 0)
        mpBackground->Draw(rc, &rc.mBoundsRect, &mBorderRect);
    else if ((mBgColor & 0xff000000) != 0)
    {
        rc.SetScrollColor(mBgColor);
        rc.ScrollRect(mBorderRect);
    }

drawBorder:
    if (mpBorder != 0 &&
        rc.TestRect(mBorderRect.mLeft, mBorderRect.mTop, mBorderRect.mRight, mBorderRect.mBottom))
        mpBorder->Draw(rc, &mBorderRect, 0);

    switch (mPlacement)
    {
    case 1:
    {
        RenderingContext tmp(rc);
        RenderContent(tmp);
        PickBox box;
        GetPickBox(&box);
        rc.SetSubStyle(this, &box);
        break;
    }
    case 2:
    case 3:
    {
        RectT<float> saved(rc.mContextRect);
        rc.EndContent();
        RenderContent(rc);
        rc.SetContextRect(saved);
        return;
    }
    case 4:
    {
        rc.BeginContent();
        RenderingContext tmp(rc);
        RenderContent(tmp);
        rc.PlaceFloat(this);
        break;
    }
    case 5:
    {
        rc.BeginContent();
        RenderingContext tmp(rc);
        RenderContent(tmp);
        break;
    }
    default:
        return;
    }
}

// @ 0x008e8310
void AnonymousBox::LayoutFlow(RenderingContext& ctx, Style::StyleState& style)
{
    ctx.CollapseMargin(0.0f);

    mRect20.mLeft = 0.0f;
    mRect20.mRight = ctx.mContextRect.mRight - ctx.mContextRect.mLeft;
    mRect20.mTop = ctx.mYPos;

    RectT<float> saved(ctx.mBoundsRect);
    ctx.mBoundsRect.mLeft = 0.0f;
    ctx.mBoundsRect.mTop = 0.0f;
    ctx.mBoundsRect.mRight = 0.0f;
    ctx.mBoundsRect.mBottom = 0.0f;

        for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it.mpNode->LayoutFlow(ctx, style);

    if (ctx.mTypesetter.GetType() != 2)
        ctx.Reset();

    mRect20.mBottom = ctx.mYPos;

    mRect30 = mRect20;

    ctx.mBoundsRect.mLeft = Min(mRect20.mLeft, saved.mLeft);
    ctx.mBoundsRect.mTop = Min(mRect20.mTop, saved.mTop);
    ctx.mBoundsRect.mRight = Max(mRect20.mRight, saved.mRight);
    ctx.mBoundsRect.mBottom = Max(mRect20.mBottom, saved.mBottom);
}

// @ 0x008e84b0
void AnonymousBox::Render(RenderingContext& ctx)
{
    ctx.mYPos = mRect20.mTop;

    for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it.mpNode->Render(ctx);

    ctx.EndContent();
    ctx.mYPos = -10.0f;
}

// @ 0x008e8520
bool AnonymousBox::Pick(PickingContext& ctx, PickEntry* pEntry)
{
    ctx.mYPos = mRect20.mTop;

    if (ctx.mX538 >= mRect30.mLeft && ctx.mY53c >= mRect30.mTop &&
        ctx.mX538 < mRect30.mRight && ctx.mY53c < mRect30.mBottom)
    {
        for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        {
            if (it.mpNode->Pick(ctx, pEntry))
                return true;
        }
        return ctx.FlushAll(pEntry);
    }
    return false;
}

// @ 0x008e85d0
void ContainerItem::PlaceControls(unsigned int nArg)
{
    for (ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it.mpNode->PlaceControls(nArg);
}

// @ 0x008e8700
void Block::Measure(SizingContext& sc, Style::StyleState& parentStyle)
{
    using namespace Style;

    StyleState style(&parentStyle);

    if (style.mDisplay != 0 && (mPlacement == 2 || mPlacement == 1))
    {
        ComputeStyle(mpElement, mStyleRules, mnRuleCount, &style);
        style.Resolve();
        SetUpBox(sc, style);
        mFloat = style.mFloat;

        if (mPlacement == 2)
        {
            sc.Finish();
            MeasureContent(sc, style);
            sc.Finish();
        }
        else if (mpElement != 0 && (mpElement->v05() || mpElement->v06()))
        {
            SizeT<float> size;
            mpElement->GetIntrinsicSize(&size);
            sc.mMinWidth = MaxRef(size.w, sc.mMinWidth);

            size.w = mOuterRect.mRight - mOuterRect.mLeft;
            float width = MaxRef(size.w, sc.mMinWidth);
            sc.mMaxWidth = width;
            sc.mMinWidth = width;
        }
        else
        {
            MeasureContent(sc, style);
        }
    }
}

// @ 0x008e8870
bool Block::Pick(PickingContext& ctx, PickEntry* pEntry)
{
    PickBox rect;

    switch (mPlacement)
    {
    case 1:
        if (ctx.mX538 >= mPickRect.mLeft && ctx.mY53c >= mPickRect.mTop &&
            ctx.mX538 < mPickRect.mRight && ctx.mY53c < mPickRect.mBottom)
        {
            PickingContext tmp(ctx);
            if (PickContent(tmp, pEntry))
                return true;
        }
        GetPickBox(&rect);
        ctx.SetContextRect(this, (const RectT<float>*)&rect);
        break;
    case 2:
    case 3:
    {
        if (ctx.FlushAll(pEntry))
            return true;
        rect.mLeft = ctx.mBoundsRect.mLeft;
        rect.mTop = ctx.mBoundsRect.mTop;
        rect.mRight = ctx.mBoundsRect.mRight;
        rect.mBottom = ctx.mBoundsRect.mBottom;
        if (PickContent(ctx, pEntry))
            return true;
        ctx.SetContextRect(&rect.mLeft);
        break;
    }
    case 4:
    {
        if (ctx.Flush(pEntry))
            return true;
        PickingContext tmp(ctx);
        if (PickContent(tmp, pEntry))
            return true;
        ctx.PlaceFloat(this);
        break;
    }
    case 5:
    {
        if (ctx.Flush(pEntry))
            return true;
        PickingContext tmp(ctx);
        if (PickContent(tmp, pEntry))
            return true;
        break;
    }
    default:
        break;
    }

    if (ctx.mX530 >= ctx.mBoundsRect.mLeft + mContentRect.mLeft &&
        ctx.mY534 >= ctx.mBoundsRect.mTop + mContentRect.mTop &&
        ctx.mX530 < ctx.mBoundsRect.mLeft + mContentRect.mRight &&
        ctx.mY534 < ctx.mBoundsRect.mTop + mContentRect.mBottom)
    {
        rect.mLeft = ctx.mX538 - mContentRect.mLeft;
        rect.mTop = ctx.mY53c - mContentRect.mTop;
        pEntry->Add(mpElement, 0, mSelectableIndex, &rect);
        return true;
    }
    return false;
}

// @ 0x008e8620
PickingContext::~PickingContext()
{
    if (mpVecBegin != 0 && mpVecBegin != mpInline)
        FreeMem(mpVecBegin);
}

}  // namespace Layout

namespace Style {

// @ 0x008e8650
StyleState::~StyleState()
{
}

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
