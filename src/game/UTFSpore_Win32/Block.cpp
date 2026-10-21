// src/game/UTFSpore_Win32/Block.cpp -- migrated from slice(s) s008e8af0, s008e7230 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Block.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/Typesetter.h"
#include <math.h>

// ---- items of slice s008e7230 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
struct RectT_s008e_7230 {
    T mLeft, mTop, mRight, mBottom;
    RectT_s008e_7230() {}
    RectT_s008e_7230(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    RectT_s008e_7230(const RectT_s008e_7230& x) : mLeft(x.mLeft), mTop(x.mTop), mRight(x.mRight), mBottom(x.mBottom) {}
    RectT_s008e_7230& operator=(const RectT_s008e_7230& x)
    {
        mLeft = x.mLeft; mTop = x.mTop; mRight = x.mRight; mBottom = x.mBottom;
        return *this;
    }
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
    SizeT(T aw, T ah) : w(aw), h(ah) {}
};
}
namespace EA {
namespace Text {
class Typesetter_s008e_7230 {
public:
    ~Typesetter_s008e_7230();                     // 0x0089c540
    uint32_t mData[0x530 / 4];
};  // namespace Text
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum Units { kUnitsPixels = 1, kUnitsAuto = 10 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum FloatStyle { kFloatNone = 0, kFloatLeft = 1, kFloatRight = 2 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum Position { kPositionStatic = 0, kPositionRelative = 1, kPositionAbsolute = 2, kPositionFixed = 3 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum DisplayType { kDisplayListItem = 5, kDisplayTable = 6 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum EdgeIndex { kEdgeTop = 0, kEdgeRight = 1, kEdgeBottom = 2, kEdgeLeft = 3 };
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
    float ToPixels(float reference, const FontMetrics& fm) const;          // 0x008f95c0
    float ToPixelsNonNeg(float reference, const FontMetrics& fm) const;    // 0x008f9660
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
};  // namespace DOM
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class SizingContext {
public:
    SizingContext(float enclosingWidth);   // 0x008ef870
    void Finish();                         // 0x008ef900
    Text::Typesetter_s008e_7230 mTypesetter;          // +0x0
    float mMaxWidth;                       // +0x530
    float mMinWidth;                       // +0x534
    float mEnclosingWidth;                 // +0x538
};
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
class StackingContext {
public:
    float ClampWidth(float width);         // 0x008f0240
    void CollapseMargin(float margin);     // 0x008f01b0

    void* mpContextRoot;                   // +0x0
    uint32_t mTypesetter[0x530 / 4];       // +0x4
    RectT_s008e_7230<float> mContextRect;             // +0x534
    RectT_s008e_7230<float> mBoundsRect;              // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c
    float mPendingCollapse;                // +0x560
    float mMaxBreak;                       // +0x564
    float mMinBreak;                       // +0x568
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void CalculateSize(SizingContext& sc, Style::StyleState& style);   // +0x20

    void* mpNext;                          // +0x4
    void* mpPrev;                          // +0x8
    void* mpPage;                          // +0xc
    int mItemType;                         // +0x10
    unsigned int mSelectableIndex;         // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block : public ContainerItem {
public:
    void SetMargins(StackingContext& sc, Style::StyleState& style);

    bool mbOutOfFlow;                      // +0x50
    int mFloat;                            // +0x54
    float mVerticalOffset;                 // +0x58
    Block* mpNextFloat;                    // +0x5c
    Block* mpNextOOF;                      // +0x60
    RectT_s008e_7230<float> mOuterRect;               // +0x64
    RectT_s008e_7230<float> mBorderRect;              // +0x74
    RectT_s008e_7230<float> mPaddingRect;             // +0x84
    RectT_s008e_7230<float> mContentRect;             // +0x94
    RectT_s008e_7230<float> mPickRect;                // +0xa4
    RectT_s008e_7230<float> mBorderWidth;             // +0xb4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
inline float Round(float f) { return (float)floor(f + 0.5f); }
}
}
}
// ---- items of slice s008e7230 end

// ---- items of slice s008e8af0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
struct RectT_s008e_8af0 {
    T mLeft, mTop, mRight, mBottom;
    RectT_s008e_8af0() {}
    RectT_s008e_8af0(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    RectT_s008e_8af0(const RectT_s008e_8af0& x) : mLeft(x.mLeft), mTop(x.mTop), mRight(x.mRight), mBottom(x.mBottom) {}
    RectT_s008e_8af0& operator=(const RectT_s008e_8af0& x)
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
namespace Text {
class Typesetter_s008e_8af0 {
public:
    ~Typesetter_s008e_8af0();                     // 0x0089c540
    uint32_t mData[0x530 / 4];
};  // namespace Text
}
}
namespace EA {
namespace XHTML {
namespace Layout {
 class Item_s008e_8af0; class StackingContext_s008e_8af0; 
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct ParagraphStyle {
    uint32_t mData[2];
};
}
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
class StyleState_s008e_8af0 {
public:
    struct Edge {
        Length mMargin;           // +0x0
        Length mPadding;          // +0x8
        Length mBorder;           // +0x10
        int mBorderStyle;         // +0x18
        unsigned int mBorderColor; // +0x1c
    };

    StyleState_s008e_8af0(StyleState_s008e_8af0* pBase);   // 0x008fc130
    ~StyleState_s008e_8af0();                   // 0x008e8650

    StyleState_s008e_8af0* mpBase;           // +0x0
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
void ComputeStyle(void* pElement, Rule** pRules, unsigned int nRuleCount, StyleState_s008e_8af0* pStyle);  // 0x008eae80
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class SizingContext_s008e_8af0 {
public:
    SizingContext_s008e_8af0(float enclosingWidth);   // 0x008ef870
    void Finish();                         // 0x008ef900
    Text::Typesetter_s008e_8af0 mTypesetter;          // +0x0
    float mMaxWidth;                       // +0x530
    float mMinWidth;                       // +0x534
    float mEnclosingWidth;                 // +0x538
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block_s008e_8af0;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class StackingContext_s008e_8af0 {
public:
    StackingContext_s008e_8af0(Item_s008e_8af0* pContextRoot, StackingContext_s008e_8af0& parent, Style::StyleState_s008e_8af0& style);  // 0x008efba0
    void SetParagraphStyle(const Style::ParagraphStyle& ps);   // 0x008ee740
    void SetContextRect(const RectT_s008e_8af0<float>& rect);             // 0x008efc80
    float ClampWidth(float width);                             // 0x008f0240

    Item_s008e_8af0* mpContextRoot;                   // +0x0
    Text::Typesetter_s008e_8af0 mTypesetter;          // +0x4
    RectT_s008e_8af0<float> mContextRect;             // +0x534
    RectT_s008e_8af0<float> mBoundsRect;              // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c
    float mPendingCollapse;                // +0x560
    float mMaxBreak;                       // +0x564
    float mMinBreak;                       // +0x568
    float mFirstLineBaseline;              // +0x56c
    float mFirstLineHeight;                // +0x570
    bool mbAtLineBreak;                    // +0x574
    Block_s008e_8af0* mpFloatHead;                    // +0x578
    Block_s008e_8af0* mpFloatTail;                    // +0x57c
    Block_s008e_8af0* mpOutOfFlowList;                // +0x580
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item_s008e_8af0 {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void MeasureContent(SizingContext_s008e_8af0& sc, Style::StyleState_s008e_8af0& style);   // +0x20
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
    virtual void Layout(StackingContext_s008e_8af0& sc, Style::StyleState_s008e_8af0& style);         // +0x34

    void* mpNext;                          // +0x4
    void* mpPrev;                          // +0x8
    void* mpPage;                          // +0xc
    int mItemType;                         // +0x10
    unsigned int mSelectableIndex;         // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem_s008e_8af0 : public Item_s008e_8af0 {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block_s008e_8af0 : public ContainerItem_s008e_8af0 {
public:
    virtual void SetMargins(StackingContext_s008e_8af0& sc, Style::StyleState_s008e_8af0& style);        // +0x38 0x008e7230
    virtual void PlaceOutOfFlow(StackingContext_s008e_8af0& sc, Style::StyleState_s008e_8af0& style);    // +0x3c 0x008e8af0

    bool mbOutOfFlow;                      // +0x50
    int mFloat;                            // +0x54
    float mVerticalOffset;                 // +0x58
    Block_s008e_8af0* mpNextFloat;                    // +0x5c
    Block_s008e_8af0* mpNextOOF;                      // +0x60
    RectT_s008e_8af0<float> mOuterRect;               // +0x64
    RectT_s008e_8af0<float> mBorderRect;              // +0x74
    RectT_s008e_8af0<float> mPaddingRect;             // +0x84
    RectT_s008e_8af0<float> mContentRect;             // +0x94
    RectT_s008e_8af0<float> mPickRect;                // +0xa4
    RectT_s008e_8af0<float> mBorderWidth;             // +0xb4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
inline float Min(float a, float b) { return (a < b) ? a : b; }
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
inline float Max(float a, float b) { return (a > b) ? a : b; }
}
}
}
// ---- items of slice s008e8af0 end

// @ 0x008e7230
namespace EA { namespace XHTML { namespace Layout {
void Block::SetMargins(StackingContext& sc, Style::StyleState& style)
{
    using namespace Style;

    const RectT_s008e_7230<float> contextRect(sc.mContextRect);
    SizeT<float> intrinsic(0.0f, 0.0f);
    RectT_s008e_7230<float> margin(0.0f, 0.0f, 0.0f, 0.0f);
    RectT_s008e_7230<float> border(0.0f, 0.0f, 0.0f, 0.0f);
    RectT_s008e_7230<float> padding(0.0f, 0.0f, 0.0f, 0.0f);
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
}}}  // namespace EA::XHTML::Layout

// @ 0x008e8af0
namespace EA { namespace XHTML { namespace Layout {
void Block_s008e_8af0::PlaceOutOfFlow(StackingContext_s008e_8af0& sc, Style::StyleState_s008e_8af0& parentStyle)
{
    using namespace Style;

    StyleState_s008e_8af0 style(&parentStyle);
    ComputeStyle(mpElement, mStyleRules, mnRuleCount, &style);

    StackingContext_s008e_8af0 context(this, sc, style);
    context.SetParagraphStyle(mParaStyle);
    context.SetContextRect(sc.mContextRect);

    const RectT_s008e_8af0<float> contextRect(sc.mContextRect);
    SizeT<float> intrinsic(0.0f, 0.0f);
    float containerWidth = contextRect.Width();
    float availWidth = containerWidth;
    float containerHeight = contextRect.Height();

    mpElement->GetIntrinsicSize(&intrinsic);

    if (mDisplay == kDisplayListItem)
        availWidth = context.mMarginRight - context.mMarginLeft;

    RectT_s008e_8af0<float> border, padding, margin;
    StyleState_s008e_8af0::Edge& top = style.mEdges[kEdgeTop];
    StyleState_s008e_8af0::Edge& right = style.mEdges[kEdgeRight];
    StyleState_s008e_8af0::Edge& bottom = style.mEdges[kEdgeBottom];
    StyleState_s008e_8af0::Edge& left = style.mEdges[kEdgeLeft];

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
        SizingContext_s008e_8af0 sizing(availWidth);
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
}}}  // namespace EA::XHTML::Layout
