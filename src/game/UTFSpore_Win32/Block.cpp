// src/game/UTFSpore_Win32/Block.cpp -- migrated from slice(s) s008e6340, s008e8af0, s008e7230 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Block.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/Typesetter.h"
#include <math.h>
#include "EA/XHTML/Layout/Page.h"

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

// ---- items of slice s008e6340 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class RectT_s008e_6340 { public:
    T mLeft, mTop, mRight, mBottom;
    RectT_s008e_6340() {}
    RectT_s008e_6340(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    RectT_s008e_6340(const RectT_s008e_6340& x) : mLeft(x.mLeft), mTop(x.mTop), mRight(x.mRight), mBottom(x.mBottom) {}
    RectT_s008e_6340& operator=(const RectT_s008e_6340& x)
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
class Point2DT { public:
    T mX, mY;
    Point2DT() {}
    Point2DT(T x, T y) : mX(x), mY(y) {}
};
}
namespace EA {
namespace COM {
class IUnknown32_s008e_6340 {
public:
    virtual void v00();                                      // +0x0
    virtual void v04();                                      // +0x4
    virtual void v08();                                      // +0x8
    virtual IUnknown32_s008e_6340* AsInterface(uint32_t interfaceId);   // +0xc
};  // namespace COM
}
}
namespace EA {
namespace XHTML {
namespace Text {
class Typesetter {
public:
    ~Typesetter();
    uint32_t mData[0x530 / 4];
};  // namespace Text
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum Units_s008e_6340 { kUnitsPixels_s008e_6340 = 1, kUnitsPercentage = 9, kUnitsAuto_s008e_6340 = 10 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Length_s008e_6340 {
    float mValue;   // +0
    int mUnits;     // +4
    float ToPixels(float reference, const FontMetrics& fm) const;   // 0x008f95c0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState_s008e_6340 {
public:
    StyleState_s008e_6340* mpBase;                    // +0x0
    uint32_t pad004[(0x2a0 - 0x4) / 4];
    const wchar_t* mpBackgroundImage;      // +0x2a0
    int mBackgroundRepeat;                 // +0x2a4
    int mBackgroundAttachment;             // +0x2a8
    Length_s008e_6340 mBackgroundPosX;                // +0x2ac
    Length_s008e_6340 mBackgroundPosY;                // +0x2b4
    uint32_t pad2bc[(0x374 - 0x2bc) / 4];
    Length_s008e_6340 mBoxHeight;                     // +0x374  (units at +0x378)
    uint32_t pad37c[(0x430 - 0x37c) / 4];
    FontMetrics mFontMetrics;              // +0x430
};
}
}
}
namespace EA {
namespace XHTML {
namespace DOM {
class Element_s008e_6340 {
public:
    virtual void v00();                                    // +0x00
    virtual void v04();                                    // +0x04
    virtual void v08();                                    // +0x08
    virtual void v0c();                                    // +0x0c
    virtual void GetIntrinsicSize(SizeT<float>* pSize);    // +0x10
    virtual bool v14();                                    // +0x14
    virtual bool v18();                                    // +0x18
    virtual void v1c();                                    // +0x1c
    virtual void v20(RectT_s008e_6340<float>* pRect);                 // +0x20

    int Type();                                            // 0x00fc7e50
    Element_s008e_6340* Parent();                                     // 0x00ff0420
    int Fn8e42d0();                                        // 0x008e42d0

    char mPad[0x3c];                                       // +0x04..+0x3f
    void* mpDocument;                                      // +0x40
};  // namespace DOM
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_6340;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block_s008e_6340;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item_s008e_6340;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem_s008e_6340;
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
class StackingContext_s008e_6340;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class SizingContext_s008e_6340;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ImageRequester {
public:
    virtual void r00();
    void* mpNextLoading;    // +0x4
    uint32_t mnJobId;       // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_6340 {
public:
    COM::IUnknown32_s008e_6340* GetResource(unsigned int index);                    // 0x008eb960
    void LoadImage(ImageRequester* pRequester, const wchar_t* pURL);     // 0x008ec5e0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext {
public:
    void* mpDC;                            // +0x0
    Text::Typesetter mTypesetter;          // +0x4 (0x530 bytes)
    RectT_s008e_6340<float> mContextRect;             // +0x534
    RectT_s008e_6340<float> mViewRect;                // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c

    void SetContextRectRelative(float l, float t, float r, float b);     // 0x008eedb0
    void Fn8ee7a0(int arg);                                              // 0x008ee7a0
    void Fn8ee770(Style::ParagraphStyle* pOut);                          // 0x008ee770
    void SetParagraphStyle(const Style::ParagraphStyle& ps);             // 0x008ee740
    void Fn8eec80(float l, float t, float r, float b, void* p);          // 0x008eec80
    void Fn8ef6d0();                                                     // 0x008ef6d0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickingContext {
public:
    uint32_t mData0[0x538 / 4];            // +0x0
    Point2DT<float> mRelPos;               // +0x538
    void* mpElement;                       // +0x540
    RectT_s008e_6340<float> mContextRect;             // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c

    void SetContextRectRelative(float l, float t, float r, float b);     // 0x008edeb0
    void Fn8edd80(Style::ParagraphStyle* pOut);                          // 0x008edd80
    void Fn8edd50(const Style::ParagraphStyle& ps);                      // 0x008edd50
    bool Fn8ee4a0(void* p);                                              // 0x008ee4a0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item_s008e_6340 {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void MeasureContent(SizingContext_s008e_6340& sc, Style::StyleState_s008e_6340& style);   // +0x20
    virtual void LayoutChildren(StackingContext_s008e_6340& sc, Style::StyleState_s008e_6340& style); // +0x24
    virtual void PlaceControl(RectT_s008e_6340<float>* pRect);                             // +0x28
virtual void v0b();
virtual void v0c();
    virtual void Layout(StackingContext_s008e_6340& sc, Style::StyleState_s008e_6340& style);         // +0x34

    void* mpNext;                          // +0x4
    void* mpPrev;                          // +0x8
    Page_s008e_6340* mpPage;                          // +0xc
    int mItemType;                         // +0x10
    unsigned int mSelectableIndex;         // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem_s008e_6340 : public Item_s008e_6340 {
public:
    void* mChildItems[2];                  // +0x18
    DOM::Element_s008e_6340* mpElement;               // +0x20
    Style::Rule* mStyleRules;              // +0x24
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
class StackingContext_s008e_6340 {
public:
    void SetParagraphStyle(const Style::ParagraphStyle& ps);   // 0x008ee740
    void SetContextRect(const RectT_s008e_6340<float>& rect);             // 0x008efc80
    void Fn8efcd0(int arg);                                    // 0x008efcd0
    void Fn8f0010();                                           // 0x008f0010

    Item_s008e_6340* mpContextRoot;                   // +0x0
    Text::Typesetter mTypesetter;          // +0x4
    RectT_s008e_6340<float> mContextRect;             // +0x534
    RectT_s008e_6340<float> mBoundsRect;              // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c
    float mPendingCollapse;                // +0x560
    float mMaxBreak;                       // +0x564
    float mMinBreak;                       // +0x568
    float mFirstLineBaseline;              // +0x56c
    float mFirstLineHeight;                // +0x570
    bool mbAtLineBreak;                    // +0x574
    Block_s008e_6340* mpFloatHead;                    // +0x578
    Block_s008e_6340* mpFloatTail;                    // +0x57c
    Block_s008e_6340* mpOutOfFlowList;                // +0x580
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block_s008e_6340 : public ContainerItem_s008e_6340 {
public:
    virtual void SetMargins(StackingContext_s008e_6340& sc, Style::StyleState_s008e_6340& style);        // +0x38 0x008e7230
    virtual void PlaceOutOfFlow(StackingContext_s008e_6340& sc, Style::StyleState_s008e_6340& style);    // +0x3c 0x008e8af0

    void Fn8eab50(RenderingContext& ctx);                     // 0x008eab50
    bool Fn8eaba0(PickingContext& pc, void* pArg);            // 0x008eaba0
    void DrawContent(RenderingContext& ctx);                  // 0x008e6a20
    bool PickContent(PickingContext& pc, void* pArg);         // 0x008e6b70
    void PlaceControls(Point2DT<float>& pos);                 // 0x008e6c60
    void Layout(StackingContext_s008e_6340& sc, Style::StyleState_s008e_6340& style);   // 0x008e6d30

    bool mbOutOfFlow;                      // +0x50
    int mFloat;                            // +0x54
    float mVerticalOffset;                 // +0x58
    Block_s008e_6340* mpNextFloat;                    // +0x5c
    Block_s008e_6340* mpNextOOF;                      // +0x60
    RectT_s008e_6340<float> mOuterRect;               // +0x64
    RectT_s008e_6340<float> mBorderRect;              // +0x74
    RectT_s008e_6340<float> mPaddingRect;             // +0x84
    RectT_s008e_6340<float> mContentRect;             // +0x94
    RectT_s008e_6340<float> mPickRect;                // +0xa4
    RectT_s008e_6340<float> mBorderWidth;             // +0xb4
};
}
}
}
// ---- items of slice s008e6340 end

// @ 0x008e6b70
namespace EA { namespace XHTML { namespace Layout {
bool Block_s008e_6340::PickContent(PickingContext& pc, void* pArg)
{
    if (pc.mRelPos.mX < mPickRect.mLeft)
        return false;
    if (pc.mRelPos.mY < mPickRect.mTop)
        return false;
    if (mPickRect.mRight <= pc.mRelPos.mX)
        return false;
    if (mPickRect.mBottom <= pc.mRelPos.mY)
        return false;

    Style::ParagraphStyle saved;
    pc.Fn8edd80(&saved);
    pc.Fn8edd50(mParaStyle);
    pc.SetContextRectRelative(mContentRect.mLeft, mContentRect.mTop, mContentRect.mRight,
                              mContentRect.mBottom);
    pc.mYPos = 0.0f;
    if (Fn8eaba0(pc, pArg))
        return true;
    if (pc.Fn8ee4a0(pArg))
        return true;
    pc.Fn8edd50(saved);
    return false;
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008e6c60
namespace EA { namespace XHTML { namespace Layout {
void Block_s008e_6340::PlaceControls(Point2DT<float>& pos)
{
    RectT_s008e_6340<float> rect(pos.mX + mContentRect.mLeft, mContentRect.mTop + pos.mY,
                      pos.mX + mContentRect.mRight, mContentRect.mBottom + pos.mY);
    if (mpElement != 0) {
        if (mpElement->v18()) {
            RectT_s008e_6340<float> elementRect = rect;
            mpElement->v20(&elementRect);
        }
    }
    PlaceControl(&rect);
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008e6d30
namespace EA { namespace XHTML { namespace Layout {
void Block_s008e_6340::Layout(StackingContext_s008e_6340& sc, Style::StyleState_s008e_6340& style)
{
    const float padContentDiff = mPaddingRect.mBottom - mContentRect.mBottom;
    const float borderPadDiff = mBorderRect.mBottom - mPaddingRect.mBottom;
    const float outerBorderDiff = mOuterRect.mBottom - mBorderRect.mBottom;

    const RectT_s008e_6340<float> savedContextRect(sc.mContextRect);

    RectT_s008e_6340<float> contextRect(mContentRect.mLeft + sc.mContextRect.mLeft,
                             mContentRect.mTop + sc.mContextRect.mTop,
                             mContentRect.mRight + sc.mContextRect.mLeft,
                             mContentRect.mBottom + sc.mContextRect.mTop);
    sc.SetContextRect(contextRect);

    Block_s008e_6340* pOutOfFlow = sc.mpOutOfFlowList;
    sc.mpOutOfFlowList = 0;
    const RectT_s008e_6340<float> savedBounds(sc.mBoundsRect);
    sc.mBoundsRect.mLeft = 0.0f;
    sc.mBoundsRect.mTop = 0.0f;
    sc.mBoundsRect.mRight = 0.0f;
    sc.mBoundsRect.mBottom = 0.0f;
    sc.mYPos = 0.0f;

    if (mpElement != 0 && (mpElement->v14() || mpElement->v18())) {
        SizeT<float> intrinsic(16.0f, 16.0f);
        mpElement->GetIntrinsicSize(&intrinsic);
        sc.mYPos = intrinsic.h;
        sc.mFirstLineBaseline = 0.0f;
        sc.mFirstLineHeight = intrinsic.h;
    } else {
        LayoutChildren(sc, style);
        sc.Fn8f0010();
    }

    if (sc.mpContextRoot == this)
        sc.Fn8efcd0(3);

    if (style.mBoxHeight.mUnits == Style::kUnitsAuto_s008e_6340)
        mContentRect.mBottom = mContentRect.mTop + sc.mYPos;

    mPaddingRect.mBottom = mContentRect.mBottom + padContentDiff;
    mBorderRect.mBottom = mPaddingRect.mBottom + borderPadDiff;
    mOuterRect.mBottom = mBorderRect.mBottom + outerBorderDiff;

    sc.mContextRect = mPaddingRect;
    sc.mContextRect.mLeft -= mContentRect.mLeft;
    sc.mContextRect.mTop -= mContentRect.mTop;
    sc.mContextRect.mRight -= mContentRect.mLeft;
    sc.mContextRect.mBottom -= mContentRect.mTop;

    for (Block_s008e_6340* pBlock = sc.mpOutOfFlowList; pBlock != 0; pBlock = pBlock->mpNextOOF)
        pBlock->PlaceOutOfFlow(sc, style);

    if (sc.mBoundsRect.mLeft == sc.mBoundsRect.mRight ||
        sc.mBoundsRect.mTop == sc.mBoundsRect.mBottom) {
        sc.mBoundsRect = mBorderRect;
    } else {
        sc.mBoundsRect.mLeft += mContentRect.mLeft;
        sc.mBoundsRect.mTop += mContentRect.mTop;
        sc.mBoundsRect.mRight += mContentRect.mLeft;
        sc.mBoundsRect.mBottom += mContentRect.mTop;
        sc.mBoundsRect.mLeft = Min(mBorderRect.mLeft, sc.mBoundsRect.mLeft);
        sc.mBoundsRect.mTop = Min(mBorderRect.mTop, sc.mBoundsRect.mTop);
        sc.mBoundsRect.mRight = Max(mBorderRect.mRight, sc.mBoundsRect.mRight);
        sc.mBoundsRect.mBottom = Max(mBorderRect.mBottom, sc.mBoundsRect.mBottom);
    }

    mPickRect = sc.mBoundsRect;
    sc.mBoundsRect.mLeft = Min(savedBounds.mLeft, sc.mBoundsRect.mLeft);
    sc.mBoundsRect.mTop = Min(savedBounds.mTop, sc.mBoundsRect.mTop);
    sc.mBoundsRect.mRight = Max(savedBounds.mRight, sc.mBoundsRect.mRight);
    sc.mBoundsRect.mBottom = Max(savedBounds.mBottom, sc.mBoundsRect.mBottom);

    sc.SetContextRect(savedContextRect);
    sc.mpOutOfFlowList = pOutOfFlow;
    sc.mPendingCollapse = outerBorderDiff;
    sc.mYPos = mOuterRect.mBottom;
}
}}}  // namespace EA::XHTML::Layout

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
