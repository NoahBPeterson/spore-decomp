// Slice s008e7230 -- EA::XHTML::Layout::Block::SetMargins (EA XHTML layout engine, Block.cpp).
// Retail layouts: EA::Text::Typesetter is 0x530 bytes in retail (0x548 in the 2008 dev PDB), so
// StackingContext / SizingContext members after it sit 0x18 lower than in the PDB.
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

namespace Style {

enum Units { kUnitsPixels = 1, kUnitsAuto = 10 };
enum FloatStyle { kFloatNone = 0, kFloatLeft = 1, kFloatRight = 2 };
enum Position { kPositionStatic = 0, kPositionRelative = 1, kPositionAbsolute = 2, kPositionFixed = 3 };
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

class StyleState {
public:
    struct Edge {
        Length mMargin;           // +0x0
        Length mPadding;          // +0x8
        Length mBorder;           // +0x10
        int mBorderStyle;         // +0x18
        unsigned int mBorderColor; // +0x1c
    };

    bool HasBoxEdges() const;     // 0x008fb9e0

    uint32_t pad000[0x2ec / 4];
    Edge mEdges[4];               // +0x2ec
    Length mBoxWidth;             // +0x36c
    Length mBoxHeight;            // +0x374
    uint32_t pad37c[(0x3a8 - 0x37c) / 4];
    int mDisplay;                 // +0x3a8
    uint32_t pad3ac[(0x42c - 0x3ac) / 4];
    int mTableAlign;              // +0x42c
    FontMetrics mFontMetrics;     // +0x430
};

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
    float ClampWidth(float width);         // 0x008f0240
    void CollapseMargin(float margin);     // 0x008f01b0

    void* mpContextRoot;                   // +0x0
    uint32_t mTypesetter[0x530 / 4];       // +0x4
    RectT<float> mContextRect;             // +0x534
    RectT<float> mBoundsRect;              // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c
    float mPendingCollapse;                // +0x560
    float mMaxBreak;                       // +0x564
    float mMinBreak;                       // +0x568
};

class Item {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void CalculateSize(SizingContext& sc, Style::StyleState& style);   // +0x20

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
    void* mStyleRules;                     // +0x24
    unsigned int mnRuleCount;              // +0x28
    int mDisplay;                          // +0x2c
    int mPosition;                         // +0x30
    uint32_t pad34[(0x50 - 0x34) / 4];
};

class Block : public ContainerItem {
public:
    void SetMargins(StackingContext& sc, Style::StyleState& style);

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

// @ 0x008e7230
void Block::SetMargins(StackingContext& sc, Style::StyleState& style)
{
    using namespace Style;

    const RectT<float> contextRect(sc.mContextRect);
    SizeT<float> intrinsic(0.0f, 0.0f);
    RectT<float> margin(0.0f, 0.0f, 0.0f, 0.0f);
    RectT<float> border(0.0f, 0.0f, 0.0f, 0.0f);
    RectT<float> padding(0.0f, 0.0f, 0.0f, 0.0f);
    float containerWidth = contextRect.mRight - contextRect.mLeft;
    float availWidth = containerWidth;
    float width, height;

    mpElement->GetIntrinsicSize(&intrinsic);

    if (mDisplay == kDisplayListItem)
        availWidth = sc.mMarginRight - sc.mMarginLeft;

    mbOutOfFlow = (mFloat != kFloatNone) || (mPosition == kPositionAbsolute) || (mPosition == kPositionFixed);

    if ((mbOutOfFlow && (style.mBoxWidth.mUnits == kUnitsAuto) && (intrinsic.w == 0.0f)) ||
        (mDisplay == kDisplayTable)) {
        SizingContext sizing(availWidth);
        CalculateSize(sizing, style);
        sizing.Finish();
        intrinsic.w = sizing.mMaxWidth;
        sc.mMinBreak = sizing.mMinWidth;
        sc.mMaxBreak = sizing.mMaxWidth;
    }

    if (style.HasBoxEdges()) {
        StyleState::Edge& left = style.mEdges[kEdgeLeft];
        StyleState::Edge& right = style.mEdges[kEdgeRight];

        margin.mLeft = Round(left.mMargin.ToPixels(availWidth, style.mFontMetrics));
        margin.mRight = Round(right.mMargin.ToPixels(availWidth, style.mFontMetrics));
        margin.mTop = Round(style.mEdges[kEdgeTop].mMargin.ToPixels(availWidth, style.mFontMetrics));
        margin.mBottom = Round(style.mEdges[kEdgeBottom].mMargin.ToPixels(availWidth, style.mFontMetrics));
        border.mLeft = Round(left.mBorder.ToPixelsNonNeg(availWidth, style.mFontMetrics));
        border.mRight = Round(right.mBorder.ToPixelsNonNeg(availWidth, style.mFontMetrics));
        border.mTop = Round(style.mEdges[kEdgeTop].mBorder.ToPixelsNonNeg(availWidth, style.mFontMetrics));
        border.mBottom = Round(style.mEdges[kEdgeBottom].mBorder.ToPixelsNonNeg(availWidth, style.mFontMetrics));
        padding.mLeft = Round(left.mPadding.ToPixelsNonNeg(availWidth, style.mFontMetrics));
        padding.mRight = Round(right.mPadding.ToPixelsNonNeg(availWidth, style.mFontMetrics));
        padding.mTop = Round(style.mEdges[kEdgeTop].mPadding.ToPixelsNonNeg(availWidth, style.mFontMetrics));
        padding.mBottom = Round(style.mEdges[kEdgeBottom].mPadding.ToPixelsNonNeg(availWidth, style.mFontMetrics));

        if (style.mBoxWidth.mUnits != kUnitsAuto)
            width = Round(style.mBoxWidth.ToPixelsNonNeg(containerWidth, style.mFontMetrics));
        else
            width = (intrinsic.w != 0.0f) ? intrinsic.w : 0.0f;

        if (style.mBoxHeight.mUnits != kUnitsAuto)
            height = Round(style.mBoxHeight.ToPixelsNonNeg(contextRect.mBottom - contextRect.mTop, style.mFontMetrics));
        else
            height = (intrinsic.h != 0.0f) ? intrinsic.h : 0.0f;

        float remaining = availWidth - (width + padding.mRight + padding.mLeft + border.mRight + border.mLeft +
                                        margin.mRight + margin.mLeft);

        if (style.mDisplay == kDisplayTable) {
            if (style.mBoxWidth.mUnits != kUnitsAuto)
                width -= padding.mRight + padding.mLeft + border.mRight + border.mLeft;
            else {
                width = sc.ClampWidth(remaining);
                style.mBoxWidth.mUnits = kUnitsPixels;
            }

            if ((left.mMargin.mUnits == kUnitsAuto) && (right.mMargin.mUnits == kUnitsAuto)) {
                if (style.mTableAlign == 0)
                    left.mMargin.mUnits = kUnitsPixels;
                else if (style.mTableAlign == 2)
                    right.mMargin.mUnits = kUnitsPixels;
            }

            remaining = availWidth - (width + padding.mRight + padding.mLeft + border.mRight + border.mLeft +
                                      margin.mRight + margin.mLeft);
        }

        if (remaining < 0.0f) {
            // Over-constrained: take the excess out of the horizontal margins, right first.
            const float excess = -remaining;
            if (excess > margin.mRight + margin.mLeft) {
                margin.mLeft = 0.0f;
                margin.mRight = 0.0f;
            } else if (excess < margin.mRight) {
                margin.mRight = margin.mRight - excess;
            } else {
                margin.mLeft = margin.mLeft - (excess - margin.mRight);
                margin.mRight = 0.0f;
            }
        } else if (mFloat != kFloatNone) {
            if (style.mBoxWidth.mUnits == kUnitsAuto)
                width = sc.ClampWidth(remaining);
        } else if (style.mBoxWidth.mUnits == kUnitsAuto) {
            if (left.mMargin.mUnits == kUnitsAuto)
                margin.mLeft = 0.0f;
            if (right.mMargin.mUnits == kUnitsAuto)
                margin.mRight = 0.0f;
            if (left.mBorder.mUnits == kUnitsAuto)
                border.mLeft = 0.0f;
            if (right.mBorder.mUnits == kUnitsAuto)
                border.mRight = 0.0f;
            if (left.mPadding.mUnits == kUnitsAuto)
                padding.mLeft = 0.0f;
            if (right.mPadding.mUnits == kUnitsAuto)
                padding.mRight = 0.0f;
            width = availWidth - (padding.mRight + padding.mLeft + border.mRight + border.mLeft +
                                  margin.mRight + margin.mLeft);
        } else if (left.mMargin.mUnits == kUnitsAuto) {
            if (right.mMargin.mUnits == kUnitsAuto) {
                margin.mLeft = (float)floor((remaining + 1.0f) * 0.5f);
                margin.mRight = remaining - margin.mLeft;
            } else
                margin.mLeft = remaining;
        } else if (right.mMargin.mUnits == kUnitsAuto) {
            margin.mRight = remaining;
        } else if (left.mPadding.mUnits == kUnitsAuto) {
            if (right.mPadding.mUnits == kUnitsAuto) {
                padding.mLeft = (float)floor((remaining + 1.0f) * 0.5f);
                padding.mRight = remaining - padding.mLeft;
            } else
                padding.mLeft = remaining;
        } else if (right.mPadding.mUnits == kUnitsAuto) {
            padding.mRight = remaining;
        } else if (left.mBorder.mUnits == kUnitsAuto) {
            if (right.mBorder.mUnits == kUnitsAuto) {
                border.mLeft = (float)floor((remaining + 1.0f) * 0.5f);
                border.mRight = remaining - border.mLeft;
            } else
                border.mLeft = remaining;
        } else if (right.mBorder.mUnits == kUnitsAuto) {
            border.mRight = remaining;
        } else {
            margin.mRight = remaining + margin.mRight;
        }
    } else {

        if (style.mBoxWidth.mUnits != kUnitsAuto)
            width = style.mBoxWidth.ToPixelsNonNeg(availWidth, style.mFontMetrics);
        else
            width = (intrinsic.w != 0.0f) ? intrinsic.w : availWidth;

        if (style.mBoxHeight.mUnits != kUnitsAuto)
            height = style.mBoxHeight.ToPixelsNonNeg(availWidth, style.mFontMetrics);
        else
            height = (intrinsic.h != 0.0f) ? intrinsic.h : 0.0f;

        if (availWidth > width)
            margin.mRight = availWidth - width;
    }

    if (mFloat != kFloatNone)
        sc.mPendingCollapse = 0.0f;

    sc.CollapseMargin(margin.mTop);

    if (margin.mTop < 0.0f)
        margin.mTop = 0.0f;
    if (margin.mBottom < 0.0f)
        margin.mBottom = 0.0f;

    mOuterRect.mLeft = 0.0f;
    mOuterRect.mTop = sc.mYPos - margin.mTop;
    mOuterRect.mRight = width + padding.mRight + padding.mLeft + border.mRight + border.mLeft + margin.mRight +
                        margin.mLeft;
    mOuterRect.mBottom = mOuterRect.mTop + height + padding.mBottom + padding.mTop + border.mBottom + border.mTop +
                         margin.mBottom + margin.mTop;

    if (mFloat == kFloatLeft) {
        mOuterRect.mRight = mOuterRect.mRight - mOuterRect.mLeft + sc.mMarginLeft;
        mOuterRect.mLeft = sc.mMarginLeft;
    } else if (mFloat == kFloatRight) {
        mOuterRect.mLeft = sc.mMarginRight - (mOuterRect.mRight - mOuterRect.mLeft);
        mOuterRect.mRight = sc.mMarginRight;
    }

    mBorderRect = mOuterRect;
    mBorderRect.Inflate(-margin.mLeft, -margin.mTop, -margin.mRight, -margin.mBottom);
    mBorderWidth.mLeft = border.mLeft;
    mBorderWidth.mTop = border.mTop;
    mBorderWidth.mRight = border.mRight;
    mBorderWidth.mBottom = border.mBottom;
    mPaddingRect = mBorderRect;
    mPaddingRect.Inflate(-border.mLeft, -border.mTop, -border.mRight, -border.mBottom);
    mContentRect = mPaddingRect;
    mContentRect.Inflate(-padding.mLeft, -padding.mTop, -padding.mRight, -padding.mBottom);
}

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA
