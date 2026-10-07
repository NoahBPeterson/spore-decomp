// Slice s008e8af0 -- EA::XHTML::Layout::Block::PlaceOutOfFlow (EA XHTML layout engine, Block.cpp).
// Places an absolutely/fixed positioned block: resolves its edges and box offsets against the
// enclosing context rect, sets the content/padding/border/outer rects, lays out the children in a
// new StackingContext and grows the parent context's bounds by the block's pick rect.
// Retail layouts: EA::Text::Typesetter is 0x530 bytes in retail (0x548 in the 2008 dev PDB), so
// StackingContext / SizingContext members after it sit 0x18 lower than in the PDB.
// Block vtable (retail 0x01437c20): +0x20 MeasureContent, +0x34 Layout, +0x38 SetMargins,
// +0x3c PlaceOutOfFlow.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc: the StyleState/StackingContext locals get no EH frame).
#include "types.h"
#include <math.h>

namespace EA {

template <typename T>
struct RectT {
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
    SizeT(T aw, T ah) : w(aw), h(ah) {}
};

namespace Text {
class Typesetter {
public:
    ~Typesetter();                     // 0x0089c540
    uint32_t mData[0x530 / 4];
};
}  // namespace Text

namespace XHTML {

namespace Layout { class Item; class StackingContext; }

namespace Style {

enum Units { kUnitsPixels = 1, kUnitsAuto = 10 };
enum DisplayType { kDisplayListItem = 5, kDisplayTable = 6 };
enum EdgeIndex { kEdgeTop = 0, kEdgeRight = 1, kEdgeBottom = 2, kEdgeLeft = 3 };

struct FontMetrics {
    float mfFontSize, mfEmSize, mfExSize, mfAscent, mfDescent;
};

struct Length {
    float mValue;   // +0
    int mUnits;     // +4
    float ToPixels(float reference, const FontMetrics& fm) const;          // 0x008f95c0
    float ToPixelsNonNeg(float reference, const FontMetrics& fm) const;    // 0x008f9660
};

struct ParagraphStyle {
    uint32_t mData[2];
};

class Rule;

class StyleState {
public:
    struct Edge {
        Length mMargin;           // +0x0
        Length mPadding;          // +0x8
        Length mBorder;           // +0x10
        int mBorderStyle;         // +0x18
        unsigned int mBorderColor; // +0x1c
    };

    StyleState(StyleState* pBase);   // 0x008fc130
    ~StyleState();                   // 0x008e8650

    StyleState* mpBase;           // +0x0
    uint32_t pad004[(0x2ec - 0x4) / 4];
    Edge mEdges[4];               // +0x2ec
    Length mBoxWidth;             // +0x36c
    Length mBoxHeight;            // +0x374
    int mFloat;                   // +0x37c
    int mClearFloat;              // +0x380
    int mPosition;                // +0x384
    Length mBoxOffset[4];         // +0x388
    int mDisplay;                 // +0x3a8
    uint32_t pad3ac[(0x430 - 0x3ac) / 4];
    FontMetrics mFontMetrics;     // +0x430
    uint32_t pad444[(0x450 - 0x444) / 4];
};

// 0x008eae80: applies the element's matched style rules to a StyleState.
void ComputeStyle(void* pElement, Rule** pRules, unsigned int nRuleCount, StyleState* pStyle);  // 0x008eae80

}  // namespace Style

namespace DOM {
class Element {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void GetIntrinsicSize(SizeT<float>* pSize);   // +0x10
};
}  // namespace DOM

namespace Layout {

class SizingContext {
public:
    SizingContext(float enclosingWidth);   // 0x008ef870
    void Finish();                         // 0x008ef900
    Text::Typesetter mTypesetter;          // +0x0
    float mMaxWidth;                       // +0x530
    float mMinWidth;                       // +0x534
    float mEnclosingWidth;                 // +0x538
};

class Block;

class StackingContext {
public:
    StackingContext(Item* pContextRoot, StackingContext& parent, Style::StyleState& style);  // 0x008efba0
    void SetParagraphStyle(const Style::ParagraphStyle& ps);   // 0x008ee740
    void SetContextRect(const RectT<float>& rect);             // 0x008efc80
    float ClampWidth(float width);                             // 0x008f0240

    Item* mpContextRoot;                   // +0x0
    Text::Typesetter mTypesetter;          // +0x4
    RectT<float> mContextRect;             // +0x534
    RectT<float> mBoundsRect;              // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c
    float mPendingCollapse;                // +0x560
    float mMaxBreak;                       // +0x564
    float mMinBreak;                       // +0x568
    float mFirstLineBaseline;              // +0x56c
    float mFirstLineHeight;                // +0x570
    bool mbAtLineBreak;                    // +0x574
    Block* mpFloatHead;                    // +0x578
    Block* mpFloatTail;                    // +0x57c
    Block* mpOutOfFlowList;                // +0x580
};

class Item {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style);   // +0x20
    virtual void v09(); virtual void v0a(); virtual void v0b(); virtual void v0c();
    virtual void Layout(StackingContext& sc, Style::StyleState& style);         // +0x34

    void* mpNext;                          // +0x4
    void* mpPrev;                          // +0x8
    void* mpPage;                          // +0xc
    int mItemType;                         // +0x10
    unsigned int mSelectableIndex;         // +0x14
};

class ContainerItem : public Item {
public:
    void* mChildItems[2];                  // +0x18
    DOM::Element* mpElement;               // +0x20
    Style::Rule** mStyleRules;             // +0x24
    unsigned int mnRuleCount;              // +0x28
    int mDisplay;                          // +0x2c
    int mPosition;                         // +0x30
    uint32_t pad34[(0x48 - 0x34) / 4];
    Style::ParagraphStyle mParaStyle;      // +0x48
};

class Block : public ContainerItem {
public:
    virtual void SetMargins(StackingContext& sc, Style::StyleState& style);        // +0x38
    virtual void PlaceOutOfFlow(StackingContext& sc, Style::StyleState& style);    // +0x3c

    bool mbOutOfFlow;                      // +0x50
    int mFloat;                            // +0x54
    float mVerticalOffset;                 // +0x58
    Block* mpNextFloat;                    // +0x5c
    Block* mpNextOOF;                      // +0x60
    RectT<float> mOuterRect;               // +0x64
    RectT<float> mBorderRect;              // +0x74
    RectT<float> mPaddingRect;             // +0x84
    RectT<float> mContentRect;             // +0x94
    RectT<float> mPickRect;                // +0xa4
    RectT<float> mBorderWidth;             // +0xb4
};

inline float Round(float f) { return (float)floor(f + 0.5f); }
inline float Min(float a, float b) { return (a < b) ? a : b; }
inline float Max(float a, float b) { return (a > b) ? a : b; }

// @ 0x008e8af0
void Block::PlaceOutOfFlow(StackingContext& sc, Style::StyleState& parentStyle)
{
    using namespace Style;

    StyleState style(&parentStyle);
    ComputeStyle(mpElement, mStyleRules, mnRuleCount, &style);

    StackingContext context(this, sc, style);
    context.SetParagraphStyle(mParaStyle);
    context.SetContextRect(sc.mContextRect);

    const RectT<float> contextRect(sc.mContextRect);
    SizeT<float> intrinsic(0.0f, 0.0f);
    float containerWidth = contextRect.Width();
    float availWidth = containerWidth;
    float containerHeight = contextRect.Height();

    mpElement->GetIntrinsicSize(&intrinsic);

    if (mDisplay == kDisplayListItem)
        availWidth = context.mMarginRight - context.mMarginLeft;

    RectT<float> border, padding, margin;
    StyleState::Edge& top = style.mEdges[kEdgeTop];
    StyleState::Edge& right = style.mEdges[kEdgeRight];
    StyleState::Edge& bottom = style.mEdges[kEdgeBottom];
    StyleState::Edge& left = style.mEdges[kEdgeLeft];

    margin.mLeft = Round(left.mMargin.ToPixels(availWidth, style.mFontMetrics));
    margin.mRight = Round(right.mMargin.ToPixels(availWidth, style.mFontMetrics));
    margin.mTop = Round(top.mMargin.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    margin.mBottom = Round(bottom.mMargin.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    border.mLeft = Round(left.mBorder.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    border.mRight = Round(right.mBorder.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    border.mTop = Round(top.mBorder.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    border.mBottom = Round(bottom.mBorder.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    padding.mLeft = Round(left.mPadding.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    padding.mRight = Round(right.mPadding.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    padding.mTop = Round(top.mPadding.ToPixelsNonNeg(availWidth, style.mFontMetrics));
    padding.mBottom = Round(bottom.mPadding.ToPixelsNonNeg(availWidth, style.mFontMetrics));

    float width;
    if (style.mBoxWidth.mUnits != kUnitsAuto)
        width = Round(style.mBoxWidth.ToPixelsNonNeg(containerWidth, style.mFontMetrics));
    else if (intrinsic.w != 0.0f)
        width = intrinsic.w;
    else {
        SizingContext sizing(availWidth);
        MeasureContent(sizing, style);
        sizing.Finish();
        intrinsic.w = sizing.mMaxWidth;
        context.mMinBreak = sizing.mMinWidth;
        context.mMaxBreak = sizing.mMaxWidth;
        width = context.ClampWidth(availWidth - (padding.mRight + padding.mLeft + border.mRight + border.mLeft +
                                                 margin.mRight + margin.mLeft));
    }

    if ((style.mDisplay == kDisplayTable) && (style.mBoxWidth.mUnits != kUnitsAuto))
        width -= padding.mRight + padding.mLeft + border.mRight + border.mLeft;

    // Horizontal: left/right box offsets resolve against the space left over.
    const float remainingWidth = availWidth - width - margin.mLeft - margin.mRight - padding.mLeft - padding.mRight -
                                 border.mLeft - border.mRight;
    const float offsetLeft = Round(style.mBoxOffset[kEdgeLeft].ToPixels(remainingWidth, style.mFontMetrics));
    const float offsetRight = Round(style.mBoxOffset[kEdgeRight].ToPixels(remainingWidth, style.mFontMetrics));

    if (style.mBoxOffset[kEdgeLeft].mUnits == kUnitsAuto) {
        if (style.mBoxOffset[kEdgeRight].mUnits == kUnitsAuto) {
            mContentRect.mLeft = contextRect.mLeft + padding.mLeft + border.mLeft + margin.mLeft;
            mContentRect.mRight = width + mContentRect.mLeft;
        } else {
            mContentRect.mRight = contextRect.mRight - offsetRight - margin.mRight - border.mRight - padding.mRight;
            mContentRect.mLeft = mContentRect.mRight - width;
        }
    } else {
        mContentRect.mLeft = contextRect.mLeft + offsetLeft + padding.mLeft + border.mLeft + margin.mLeft;
        if ((style.mBoxOffset[kEdgeRight].mUnits == kUnitsAuto) || (style.mBoxWidth.mUnits != kUnitsAuto))
            mContentRect.mRight = width + mContentRect.mLeft;
        else
            mContentRect.mRight = contextRect.mRight - offsetRight - margin.mRight - border.mRight - padding.mRight;
    }

    float height;
    if (style.mBoxHeight.mUnits != kUnitsAuto)
        height = Round(style.mBoxHeight.ToPixelsNonNeg(contextRect.Height(), style.mFontMetrics));
    else
        height = (intrinsic.h != 0.0f) ? intrinsic.h : mContentRect.Height();

    // Vertical. Note the original tests mBoxWidth (not mBoxHeight) units here too.
    const float remainingHeight = containerHeight - height - margin.mTop - margin.mBottom - padding.mTop -
                                  padding.mBottom - border.mTop - border.mBottom;
    const float offsetTop = Round(style.mBoxOffset[kEdgeTop].ToPixels(remainingHeight, style.mFontMetrics));
    const float offsetBottom = Round(style.mBoxOffset[kEdgeBottom].ToPixels(remainingHeight, style.mFontMetrics));

    if (style.mBoxOffset[kEdgeTop].mUnits == kUnitsAuto) {
        if (style.mBoxOffset[kEdgeBottom].mUnits == kUnitsAuto) {
            mContentRect.mTop = contextRect.mTop + padding.mTop + border.mTop + margin.mTop;
            mContentRect.mBottom = height + mContentRect.mTop;
        } else {
            mContentRect.mBottom = contextRect.mBottom - offsetBottom - margin.mBottom - border.mBottom - padding.mBottom;
            mContentRect.mTop = mContentRect.mBottom - height;
        }
    } else {
        mContentRect.mTop = contextRect.mTop + offsetTop + padding.mTop + border.mTop + margin.mTop;
        if ((style.mBoxOffset[kEdgeBottom].mUnits == kUnitsAuto) || (style.mBoxWidth.mUnits != kUnitsAuto))
            mContentRect.mBottom = height + mContentRect.mTop;
        else
            mContentRect.mBottom = contextRect.mBottom - offsetBottom - margin.mBottom - border.mBottom - padding.mBottom;
    }

    mPaddingRect = mContentRect;
    mPaddingRect.Inflate(padding.mLeft, padding.mTop, padding.mRight, padding.mBottom);
    mBorderRect = mPaddingRect;
    mBorderRect.Inflate(border.mLeft, border.mTop, border.mRight, border.mBottom);
    mOuterRect = mBorderRect;
    mOuterRect.Inflate(margin.mLeft, margin.mTop, margin.mRight, margin.mBottom);

    Layout(context, style);

    mPickRect.mLeft = Min(mBorderRect.mLeft, context.mBoundsRect.mLeft);
    mPickRect.mTop = Min(mBorderRect.mTop, context.mBoundsRect.mTop);
    mPickRect.mRight = Max(mBorderRect.mRight, context.mBoundsRect.mRight);
    mPickRect.mBottom = Max(mBorderRect.mBottom, context.mBoundsRect.mBottom);

    sc.mBoundsRect.mLeft = Min(sc.mBoundsRect.mLeft, mPickRect.mLeft);
    sc.mBoundsRect.mTop = Min(sc.mBoundsRect.mTop, mPickRect.mTop);
    sc.mBoundsRect.mRight = Max(sc.mBoundsRect.mRight, mPickRect.mRight);
    sc.mBoundsRect.mBottom = Max(sc.mBoundsRect.mBottom, mPickRect.mBottom);

    mBorderWidth.mLeft = border.mLeft;
    mBorderWidth.mTop = border.mTop;
    mBorderWidth.mRight = border.mRight;
    mBorderWidth.mBottom = border.mBottom;
}

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA
