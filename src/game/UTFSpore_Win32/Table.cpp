// src/game/UTFSpore_Win32/Table.cpp -- migrated from slice(s) s008efad0, s008eebb0, s008ea290, s008e9a10, s008e6340, s008f16c0, s008f0740 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Table.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "EA/Text/Typesetter.h"
#include "EA/XHTML/Layout/Page.h"
#include <stddef.h>
#include "EA/Text/LineLayout.h"
#include "EA/Allocator/StackAllocator.h"
#include <new>
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/TextStyle.h"
#include "EA/Text/GlyphInfo.h"

// ---- items of slice s008f0740 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
struct RectF {
    float l, t, r, b;
    RectF& operator=(const RectF& o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};
struct TableColumn { float minWidth, maxWidth, percentWidth, xPos, width; };   // 0x14
struct StackingContext;
struct StyleState;
struct ListNode { ListNode* mpNext; ListNode* mpPrev; };
struct Item {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void Layout(StackingContext* ctx, StyleState* style);   // vtable +0x0c
    ListNode node;          // +0x04
    int      pad0c;
    int      mItemType;     // +0x10
};
struct StackingContext {
    char pad[0x55c];
    float mYPos;
};
struct StyleState {
    char pad[0x374];
    float mHeight;
    int   mHeightKind;
};
struct TableCell {
    u32 pad0[0x64 / 4];
    RectF mOuterRect;       // +0x64
    RectF mBorderRect;      // +0x74
    RectF mPaddingRect;     // +0x84
    RectF mContentRect;     // +0x94
    RectF mPickRect;        // +0xa4
    RectF mBorderWidth;     // +0xb4
    int   mColSpan;         // +0xc4
    int   mRowSpan;         // +0xc8
    int   mColPos;          // +0xcc
    int   mRowPos;          // +0xd0
    float mMinWidth;        // +0xd4
    float mMaxWidth;        // +0xd8
    float mPercentWidth;    // +0xdc
    RectF mPadding;         // +0xe0
    int   mVAlign;          // +0xf0
    float mValignPct;       // +0xf4
};
struct TableRow {
    u32 pad0[0x5c / 4];
    TableCell** mCellsBegin;    // +0x5c
    TableCell** mCellsEnd;      // +0x60
    u32 pad64[(0x74 - 0x64) / 4];
    float mTop;                 // +0x74
    float mBottom;              // +0x78
    float mHeight;              // +0x7c
};
struct Table {
    u32 pad0[0x18 / 4];
    ListNode mItems;            // +0x18 (anchor node of the child item list)
    u32 pad20[(0x94 - 0x20) / 4];
    RectF mContentRect;         // +0x94
    u32 padA4[(0xc4 - 0xa4) / 4];
    int   mColCount;            // +0xc4
    int   mRowIndex;            // +0xc8
    int   mColIndex;            // +0xcc
    float mRowSpacing;          // +0xd0
    float mColSpacing;          // +0xd4
    TableColumn* mColsBegin;    // +0xd8
    TableColumn* mColsEnd;
    TableColumn* mColsCap;
    u32 padE4[2];
    TableRow** mRowsBegin;      // +0xec
    TableRow** mRowsEnd;        // +0xf0
    TableRow** mRowsCap;
    u32 padF8[2];
    float mMinWidth;            // +0x100
    float mMaxWidth;            // +0x104

    void LayoutRows(StackingContext* ctx, StyleState* style);       // @ 0x008f0740
};
static inline Item* ItemOf(ListNode* n)
{
    return n ? (Item*)((char*)n - 4) : 0;
}
static inline const float& Max(const float& a, const float& b)
{
    return (a < b) ? b : a;
}
static inline float Floor(float v)
{
    return (float)floor((double)v);
}
// ---- items of slice s008f0740 end

// ---- items of slice s008f16c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class RectT_s008f_16c0 { public:
    T mLeft, mTop, mRight, mBottom;
};
}
namespace EA {
namespace Text {
class Typesetter_s008f_16c0 {
public:
    ~Typesetter_s008f_16c0();                     // 0x0089c540
    uint32_t mData[0x530 / 4];
};  // namespace Text
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
    float ToPixelsNonNeg(float reference, const FontMetrics& fm) const;    // 0x008f9660
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState_s008f_16c0 {
public:
    uint32_t pad000[0x41c / 4];
    Length mBorderSpacingH;       // +0x41c
    Length mBorderSpacingV;       // +0x424
    uint32_t pad42c;
    FontMetrics mFontMetrics;     // +0x430
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class SizingContext {
public:
    SizingContext(float enclosingWidth);   // 0x008ef870
    Text::Typesetter_s008f_16c0 mTypesetter;          // +0x0
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
class Item_s008f_16c0 {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void MeasureContent(SizingContext& sc, Style::StyleState_s008f_16c0& style);   // +0x20

    void* mpNext;                          // +0x4
    void* mpPrev;                          // +0x8
    void* mpPage;                          // +0xc
    int mItemType;                         // +0x10
    unsigned int mSelectableIndex;         // +0x14
    void Dispose();                        // 0x008eae70
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem : public Item_s008f_16c0 {
public:
    void* mChildItems[2];                  // +0x18
    void* mpElement;                       // +0x20
    void* mStyleRules;                     // +0x24
    unsigned int mnRuleCount;              // +0x28
    int mDisplay;                          // +0x2c
    int mPosition;                         // +0x30
    uint32_t pad34[(0x50 - 0x34) / 4];
    virtual void MeasureContent(SizingContext& sc, Style::StyleState_s008f_16c0& style);   // +0x20, 0x008eaa90
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block : public ContainerItem {
public:
    bool mbOutOfFlow;                      // +0x50
    int mFloat;                            // +0x54
    float mVerticalOffset;                 // +0x58
    Block* mpNextFloat;                    // +0x5c
    Block* mpNextOOF;                      // +0x60
    RectT_s008f_16c0<float> mOuterRect;               // +0x64
    RectT_s008f_16c0<float> mBorderRect;              // +0x74
    RectT_s008f_16c0<float> mPaddingRect;             // +0x84
    RectT_s008f_16c0<float> mContentRect;             // +0x94
    RectT_s008f_16c0<float> mPickRect;                // +0xa4
    RectT_s008f_16c0<float> mBorderWidth;             // +0xb4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TableCell_s008f_16c0 : public Block {
public:
    int mColSpan;                          // +0xc4
    int mRowSpan;                          // +0xc8
    int mColPos;                           // +0xcc
    int mRowPos;                           // +0xd0
    float mMinWidth;                       // +0xd4
    float mMaxWidth;                       // +0xd8
    float mPercentWidth;                   // +0xdc
    RectT_s008f_16c0<float> mPadding;                 // +0xe0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
template <typename T>
struct Vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];

    void resize(uint32_t n);               // 0x008f18c0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct VectorOps {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];
    void F_8f1210(void* pos, int n, void* val);  // 0x008f1210
    void DoInsertValue(void** pos, void* const& value);   // 0x00a80dd0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void FUN_011e0744(void* first, void* last, int zero);   // 0x011e0744
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void FUN_00951bf0(void* first, void* last, void* dst);  // 0x00951bf0
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Table_s008f_16c0;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct ItemList_s008f_16c0 {
    Item_s008f_16c0* mpNext;                          // +0x18
    Item_s008f_16c0* mpPrev;                          // +0x1c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TableRow_s008f_16c0 {
public:
    uint32_t pad000[0x18 / 4];             // InlineItem head
    ItemList_s008f_16c0 mChildItems;                  // +0x18
    uint32_t pad020[0x3c / 4];             // +0x20..+0x5c
    Vector<TableCell_s008f_16c0*> mCells;             // +0x5c
    void Dispose();                        // 0x008f16c0
    void Build(Table_s008f_16c0* pTable);             // 0x008f1700
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TableColumn_s008f_16c0 { public:
    float mMinWidth;                       // +0x0
    float mMaxWidth;                       // +0x4
    float mPercentWidth;                   // +0x8
    float mXPos;                           // +0xc
    float mWidth;                          // +0x10
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
template <typename T>
inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }
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
namespace EA {
namespace XHTML {
namespace Layout {
class Table_s008f_16c0 : public Block {
public:
    virtual void MeasureContent(SizingContext& sc, Style::StyleState_s008f_16c0& style);
    void Build();                          // 0x008f1960

    int mColCount;                         // +0xc4
    int mRowIndex;                         // +0xc8
    int mColIndex;                         // +0xcc
    float mRowSpacing;                     // +0xd0
    float mColSpacing;                     // +0xd4
    Vector<TableColumn_s008f_16c0> mCols;             // +0xd8
    Vector<TableRow_s008f_16c0*> mRows;               // +0xec
    float mMinWidth;                       // +0x100
    float mMaxWidth;                       // +0x104
    bool mBuilt;                           // +0x108
    void Dispose();                        // 0x008f1850
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
template void Vector<TableColumn_s008f_16c0>::resize(uint32_t n);
}
}
}
// ---- items of slice s008f16c0 end

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
struct SizeT {
    T w, h;
    SizeT(T aw, T ah) : w(aw), h(ah) {}
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
enum BackgroundRepeat { kNoRepeat = 0, kRepeatX = 1, kRepeatY = 2, kRepeatXY = 3 };
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
class Element {
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
    Element* Parent();                                     // 0x00ff0420
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
class Background;
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
    DOM::Element* mpElement;               // +0x20
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
namespace EA {
namespace XHTML {
namespace Layout {
class Background : public ImageRequester {
public:
    bool Draw(RenderingContext& ctx, const RectT_s008e_6340<float>& pen, const RectT_s008e_6340<float>& rect);   // 0x008e6710
    void SetStyle(Style::StyleState_s008e_6340& style);                                               // 0x008e68f0

    Page_s008e_6340* mpPage;                          // +0xc
    unsigned int mImageTableIndex;         // +0x10
    const wchar_t* mpImageURL;             // +0x14
    Style::BackgroundRepeat mRepeat;       // +0x18
    int mAttachment;                       // +0x1c
    Style::Length_s008e_6340 mPosX;                   // +0x20
    Style::Length_s008e_6340 mPosY;                   // +0x28
    Style::FontMetrics mFontMetrics;       // +0x30
    bool mbDraw;                           // +0x44
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct Fn8e69b0Target {
    DOM::Element* mpNode;   // +0x0
    void* mpDocument;       // +0x4
    float mX;               // +0x8
    float mY;               // +0xc
    uint32_t mZero;         // +0x10
    uint32_t mArg2;         // +0x14
    void* mArg3;            // +0x18

    void Fn8e69b0(DOM::Element* pNode, uint32_t arg2, void* arg3, Point2DT<float>* pPos);
};
}
}
}
// ---- items of slice s008e6340 end

// ---- items of slice s008e9a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uchar;
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext_s008e_9a10 {
public:
    void ReleaseScroll(int arg);                                  // 0x008ee7a0 (thiscall)
    void ScrollViewport(float x0, float y0, float x1, float y1);  // 0x008ee7b0 (thiscall)
    void DrawQuad(const float* p0, uint32_t v0, const float* p1, uint32_t v1,
                  const float* p2, uint32_t v2, const float* p3, uint32_t v3);  // 0x008eebb0
};
}
}
}
void __cdecl FUN_008e9900(int color, int x, float* out, int count);   // 0x008e9900
// ---- items of slice s008e9a10 end

// ---- items of slice s008ea290 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned short ushort;
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
struct SizeT_s008e_a290 {
    T w, h;
    SizeT_s008e_a290() {}
    SizeT_s008e_a290(T aw, T ah) : w(aw), h(ah) {}
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
class Rule_s008e_a290;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState_s008e_a290;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class FontMetrics_s008e_a290 { public:
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
struct Length_s008e_a290 {
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
    virtual void Apply(StyleState_s008e_a290* pStyle);  // +0x04

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
class Rule_s008e_a290 {
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
class StyleState_s008e_a290 {
public:
    struct Edge {
        Length_s008e_a290 mMargin;             // +0x00
        Length_s008e_a290 mPadding;            // +0x08
        Length_s008e_a290 mBorder;             // +0x10
        int mBorderStyle;           // +0x18
        unsigned int mBorderColor;  // +0x1c
    };

    StyleState_s008e_a290(StyleState_s008e_a290* pBase);  // 0x008fc130
    StyleState_s008e_a290(const StyleState_s008e_a290& src);
    ~StyleState_s008e_a290();                  // 0x008e8650
    void Resolve();                 // 0x008fc670

    // 0x008fba80: true when any edge carries a non-zero border width.
    bool HasBorder() const;
    // 0x008fba70: true when the computed style asks for any background image.
    bool HasBackground() const;

    StyleState_s008e_a290* mpBase;               // +0x000
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
    Length_s008e_a290 mBoxWidth;                 // +0x36c
    Length_s008e_a290 mBoxHeight;                // +0x374
    int mFloat;                       // +0x37c
    int mClearFloat;                  // +0x380
    int mPosition;                    // +0x384
    Length_s008e_a290 mBoxOffset[4];             // +0x388
    int mDisplay;                     // +0x3a8
    uint32_t pad3ac[(0x3bc - 0x3ac) / 4];
    HashTable mFonts;                 // +0x3bc
    HashTable mColors;                // +0x3dc
    HashTable mRules;                 // +0x3fc
    uint32_t pad41c[(0x430 - 0x41c) / 4];
    FontMetrics_s008e_a290 mFontMetrics;         // +0x430
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
    virtual void GetIntrinsicSize(EA::SizeT_s008e_a290<float>* pSize);  // +0x10
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
class Typesetter_s008e_a290 {
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
class Item_s008e_a290;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem_s008e_a290;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block_s008e_a290;
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
class Background_s008e_a290;
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
class SizingContext_s008e_a290 {
public:
    SizingContext_s008e_a290(float fEnclosingWidth);  // 0x008ef870
    void Finish();                         // 0x008ef900

    Text::Typesetter_s008e_a290 mTypesetter;  // +0x000
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
class RenderingContext_s008e_a290 {
public:
    RenderingContext_s008e_a290(const RenderingContext_s008e_a290& src);           // 0x008ee8c0
    ~RenderingContext_s008e_a290();                                     // 0x008e8620
    void EndContent();                                       // 0x008f0010
    void Reset();                                            // 0x008ef6d0
    bool TestRect(float x0, float y0, float x1, float y1);   // 0x008eeac0
    void SetScrollColor(unsigned int color);                 // 0x008ee7a0
    void ScrollRect(RectT_s008e_a290<float> rect);                      // 0x008eeb30
    void SetContextRect(const RectT_s008e_a290<float>& rect);           // 0x008eed80
    void SetSubStyle(Item_s008e_a290* pItem, const PickBox* pBox);      // 0x008ee720
    void DrawQuadGradient(float x, float y, float w, float h, void* pImage);  // 0x008eec80

    Item_s008e_a290* mpContextRoot;                     // +0x000
    Text::Typesetter_s008e_a290 mTypesetter;            // +0x004
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
class PickingContext_s008e_a290 : public Text::Typesetter_s008e_a290 {
public:
    PickingContext_s008e_a290(const PickingContext_s008e_a290& src);  // 0x008ee2f0
    ~PickingContext_s008e_a290();                          // 0x008e8620
    bool Flush(PickEntry* pEntry);              // 0x008ee010
    bool FlushAll(PickEntry* pEntry);           // 0x008ee4a0
    void PlaceFloat(Item_s008e_a290* pItem);               // 0x008edf60
    void SetContextRect(const float* rect);     // 0x008ede40
    void SetContextRect(Item_s008e_a290* pItem, const RectT_s008e_a290<float>* rect);  // 0x008edd30

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
    void Draw(RenderingContext_s008e_a290& rc, const RectT_s008e_a290<float>* pRect, uchar flags);  // 0x008ea290
    void Compute(const Style::StyleState_s008e_a290* pStyle, float reference);           // 0x008e9e30

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
class Background_s008e_a290 {
public:
    Background_s008e_a290(EA::Allocator::StackAllocator_s008e_a290* pAllocator);  // 0x008e6130
    void SetStyle(const Style::StyleState_s008e_a290* pStyle);          // 0x008e68f0
    bool Draw(RenderingContext_s008e_a290& rc, const RectT_s008e_a290<float>* pBounds,
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
class Item_s008e_a290 : public eastl::intrusive_list_node_s008e_a290 {
public:
    Item_s008e_a290(Page_s008e_a290* pPage, int nType);  // 0x008eae40
    virtual ~Item_s008e_a290();                                                          // +0x00
    virtual void v04(unsigned int nColor);                                    // +0x04
    virtual void Measure(SizingContext_s008e_a290& sc, Style::StyleState_s008e_a290& style);        // +0x08
    virtual void LayoutFlow(RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style); // +0x0c
    virtual void PlaceControls(unsigned int nArg);                            // +0x10
    virtual void Render(RenderingContext_s008e_a290& ctx);                               // +0x14
    virtual bool Pick(PickingContext_s008e_a290& ctx, PickEntry* pEntry);                // +0x18
    virtual void v1c();                                                       // +0x1c
    virtual void MeasureContent(SizingContext_s008e_a290& sc, Style::StyleState_s008e_a290& style); // +0x20
    virtual void v24(RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style);        // +0x24
    virtual void PlaceControlsContent(unsigned int nArg);                     // +0x28
    virtual void RenderContent(void* pArg);                                   // +0x2c
    virtual bool PickContent(PickingContext_s008e_a290& ctx, PickEntry* pEntry);         // +0x30
    virtual void Layout(RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style);     // +0x34
    virtual void Scroll(RectT_s008e_a290<float> rect);                                   // +0x38
    virtual void PlaceOutOfFlow(RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style);  // +0x3c

    void Dispose();  // 0x008eae70

    // 0x008eaf30: true when this item's [mSelectableIndex, +nLength) range
    // overlaps the page's selection range; *pOutOffset / *pOutLength are the
    // clipped intersection in item-local coordinates.
    bool IntersectSelection(uint* pOutOffset, uint* pOutLength, uint nLength);  // 0x008eaf30 (EA::XHTML::Layout::Item::IntersectSelection)

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
typedef eastl::intrusive_list_s008e_a290<Item_s008e_a290> ItemList;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem_s008e_a290 : public Item_s008e_a290 {
public:
    virtual void MeasureContent(SizingContext_s008e_a290& sc, Style::StyleState_s008e_a290& style);  // +0x20 0x008eaa90
    virtual void LayoutFlow(RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style);  // +0x0c
    virtual void Render(RenderingContext_s008e_a290& ctx);                                // +0x14
    virtual bool Pick(PickingContext_s008e_a290& ctx, PickEntry* pEntry);                 // +0x18 0x008eaba0

    ItemList mChildItems;     // +0x18
    DOM::Element_s008e_a290* mpElement;  // +0x20
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block_s008e_a290 : public ContainerItem_s008e_a290 {
public:
    Block_s008e_a290(Page_s008e_a290* pPage, DOM::Element_s008e_a290* pElement, int nType);                    // 0x008e7f90
    virtual void Measure(SizingContext_s008e_a290& sc, Style::StyleState_s008e_a290& style);        // +0x08 0x008e8700
    virtual void Render(RenderingContext_s008e_a290& ctx);                               // +0x14
    virtual bool Pick(PickingContext_s008e_a290& ctx, PickEntry* pEntry);                // +0x18

    // 0x008eaa20 / 0x008eac20: lane in the style's border + background objects.
    void SetUpBox(SizingContext_s008e_a290& sc, Style::StyleState_s008e_a290& style);
    void SetUpBox(RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style);
    // 0x008ead40: push this block onto the context's place-chain and render content.
    void PlaceControls(RenderingContext_s008e_a290& ctx);  // 0x008e6c60 (EA::XHTML::Layout::Block::PlaceControls)
    // 0x008eadb0: cascade + resolve the style, then lay out this block's box.
    void SetStyle(RenderingContext_s008e_a290& ctx, const Style::StyleState_s008e_a290& baseStyle);  // 0x008eadb0 (EA::XHTML::Layout::Block::SetStyle)

    void DrawContent(RenderingContext_s008e_a290& ctx);                          // 0x008e6a20
    void PlaceContent(RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style);  // 0x008e95c0
    void GetPickBox(PickBox* pBox);                                   // 0x008e7da0

    Style::Rule_s008e_a290** mStyleRules;          // +0x24
    unsigned int mnRuleCount;           // +0x28
    int mDisplay;                       // +0x2c
    int mPosition;                      // +0x30
    int mPlacement;                     // +0x34
    unsigned int mFgColor;              // +0x38
    unsigned int mBgColor;              // +0x3c
    Border* mpBorder;                   // +0x40
    Background_s008e_a290* mpBackground;           // +0x44
    unsigned int mBoxWidthPx;           // +0x48  (from style +0x25c)
    unsigned int mBoxHeightPx;          // +0x4c  (from style +0x250)
    void* mpPlaceChain;                 // +0x50
    uint mPlaceStateA;                  // +0x54
    uint mPlaceStateB;                  // +0x58
    Block_s008e_a290* mpNextFloat;                 // +0x5c
    Block_s008e_a290* mpNextOOF;                   // +0x60
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
    Item_s008e_a290* mpRootItem;            // +0x3c
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
    Text::TextStyle* GetTextStyle(Style::StyleState_s008e_a290& style);  // 0x008ec580
    void SetChildItem(unsigned int index, void* pItem);       // 0x008eb910
    void SetSelectionRange(unsigned int a, unsigned int b);   // 0x008eba20
};
}
}
}
void __stdcall BorderDrawEdges(EA::XHTML::Layout::RenderingContext_s008e_a290* rc, float* a, float* b, int* c, uchar flags);  // 0x008e9a10
void __stdcall BorderDrawDashes(EA::XHTML::Layout::RenderingContext_s008e_a290* rc, float* a, float* b, int* c, uchar flags,
                                float step);  // 0x008e9b10
void __stdcall BorderDrawGradients(EA::XHTML::Layout::RenderingContext_s008e_a290* rc, float* a, float* b, int* c, float* colors,
                                   uchar flags);  // 0x008e9fe0
const float kHalf = 0.5f;             // 0x01471064
const float kThree = 3.0f;            // 0x013eb95c
const float kNegPointOne = -0.1f;     // 0x013eb964
const float kNegPointTwo = -0.2f;     // 0x013f6a3c
const float kPointOne = 0.1f;         // 0x01488874
const float kPointTwo = 0.2f;         // 0x013ec480
const float kOneThird = 1.0f / 3.0f;  // 0x013f26dc
// ---- items of slice s008ea290 end

// ---- items of slice s008eebb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct Link { Link* mpNext; };
}
namespace eastl {
struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
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
template <typename T> inline const T& tmax(const T& a, const T& b) { return (a < b) ? b : a; }
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
extern void   FUN_008e7e00(float, float);                           // 0x008e7e00  (RegisterFloat's two-float callee)
extern double iat_floor(double);                                    // 0x011e0906  msvcr90!floor (?iat_floor@@YANN@Z)
typedef unsigned char u8;
struct RectF_s008e_fad0 { float l, t, r, b; };
struct StackingContext_s008e_fad0;
struct RenderingContext_s008e_fad0;
struct PickingContext_s008e_fad0;
struct RenderingContext_s008e_fad0 {
    void SetContextRectRelative(RectF_s008e_fad0 r);    // 0x008eedb0
};
struct PickingContext_s008e_fad0 {
    void SetContextRectRelative(RectF_s008e_fad0 r);    // 0x008edeb0
};
struct Item_s008e_fad0 {
    virtual void s0();                     // vtable +0x00
    virtual void s1();                     // vtable +0x04
    virtual void s2();                     // vtable +0x08
    virtual void Layout(u32 a1, u32 a2);   // vtable +0x0c
    virtual void s4();                     // vtable +0x10
    virtual void Draw(RenderingContext_s008e_fad0* ctx);          // vtable +0x14
    virtual char Pick(PickingContext_s008e_fad0* ctx, u32 arg);   // vtable +0x18
    Item_s008e_fad0* mpNext;                          // +0x04
    int   pad08;                           // +0x08
    int   pad0c;                           // +0x0c
    int   mItemType;                       // +0x10
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
struct StackingContext_s008e_fad0 {
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

    StackingContext_s008e_fad0(u32 owner);                       // @ 0x008efad0
    StackingContext_s008e_fad0* Init(u32 owner, u32 a1, u32 a2);            // @ 0x008efba0
    void  SetContextRect(const RectF_s008e_fad0& r);             // @ 0x008efc80
    void  InsertFloat(int kind);                      // @ 0x008efcd0
    void  RecomputeFloatLimits();                     // @ 0x008efd50
    void  AddFloats(LineLayout_s008e_fad0* line);                // @ 0x008efde0
    void  FlushLines(int count);                      // @ 0x008efe80
    void  FlushAllLines();                            // @ 0x008f0010
    void  CollapseMargin(float margin);               // @ 0x008f01b0
    float ClampWidth(float w);                        // @ 0x008f0240
    void  RegisterFloat(FloatEntry* e);               // @ 0x008f0280
};
struct StyleSource {
    char  pad[0x2d4];
    float mf2d4;                        // +0x2d4
    int   mi2d8;                        // +0x2d8
    int   mi2dc;                        // +0x2dc
};
struct SlotOwner {
    char  pad[0xf0];
    int   miF0;                         // +0xf0
    float mfF4;                         // +0xf4

    void Setup(u32 a1, StyleSource* src);   // @ 0x008f0490
};
struct TableRow_s008e_fad0 {
    u32 pad0[0x5c / 4];
    void** mCellsBegin;                 // +0x5c
    void** mCellsEnd;                   // +0x60
    u32 pad64[(0x74 - 0x64) / 4];
    float mTop;                         // +0x74
};
struct Table_s008e_fad0 {
    u32 pad0[0x18 / 4];
    ListNode mItems;                    // +0x18
    u32 pad20[(0x94 - 0x20) / 4];
    RectF_s008e_fad0 mContentRect;                 // +0x94
    u32 padA4[(0xec - 0xa4) / 4];
    TableRow_s008e_fad0** mRowsBegin;              // +0xec
    TableRow_s008e_fad0** mRowsEnd;                // +0xf0

    void DrawContent(RenderingContext_s008e_fad0* ctx);               // @ 0x008f04d0
    char PickContent(PickingContext_s008e_fad0* ctx, u32 arg);        // @ 0x008f0550
};
struct Cell14 { u32 v[5]; };
struct ItemListOwner {
    u32       pad00[0x18 / 4];
    ListNode  mHead;                        // +0x18

    void Walk7(u32 a1, u32 a2);             // @ 0x008f0680
    void Walk8(u32 a1, u32 a2);             // @ 0x008f06e0
};
static inline Item_s008e_fad0* EndOf(ListNode* a) { return a ? (Item_s008e_fad0*)((char*)a - 4) : 0; }
// ---- items of slice s008efad0 end

// @ 0x008e68f0
namespace EA { namespace XHTML { namespace Layout {
void Background::SetStyle(Style::StyleState_s008e_6340& style)
{
    mpImageURL = style.mpBackgroundImage;
    mRepeat = (Style::BackgroundRepeat)style.mBackgroundRepeat;
    mAttachment = style.mBackgroundAttachment;
    mPosX.mValue = style.mBackgroundPosX.mValue;
    mPosX.mUnits = style.mBackgroundPosX.mUnits;
    mPosY.mValue = style.mBackgroundPosY.mValue;
    mPosY.mUnits = style.mBackgroundPosY.mUnits;
    mFontMetrics = style.mFontMetrics;

    mbDraw = (mpImageURL != 0);
    if (mpImageURL != 0) {
        COM::IUnknown32_s008e_6340* pRes = mpPage->GetResource(mImageTableIndex);
        if (pRes == 0 || pRes->AsInterface(0xee3f516e) == 0) {
            if (mnJobId == 0)
                mpPage->LoadImage(this, mpImageURL);
        }
    }
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008e69b0
namespace EA { namespace XHTML { namespace Layout {
void Fn8e69b0Target::Fn8e69b0(DOM::Element* pNode, uint32_t arg2, void* arg3, Point2DT<float>* pPos)
{
    Fn8e69b0Target* self = this;
    self->mArg2 = arg2;
    self->mpNode = pNode;
    self->mZero = 0;
    self->mArg3 = arg3;
    self->mX = pPos->mX;
    self->mY = pPos->mY;
    self->mpDocument = 0;
    while (pNode != 0) {
        if (pNode->Type() == 1) {
            void* pDocument = pNode->mpDocument;
            self->mpDocument = pDocument;
            if (pDocument != 0)
                break;
        }
        pNode = pNode->Parent();
    }
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008e6a20
namespace EA { namespace XHTML { namespace Layout {
void Block_s008e_6340::DrawContent(RenderingContext& ctx)
{
    if (mpElement != 0) {
        if (mpElement->v14()) {
            int pControl = mpElement->Fn8e42d0();
            ctx.SetContextRectRelative(mContentRect.mLeft, mContentRect.mTop, mContentRect.mRight,
                                       mContentRect.mBottom);
            ctx.Fn8ee7a0(-1);
            if (pControl == 0)
                return;
            ctx.Fn8eec80(0.0f, 0.0f, mContentRect.mRight - mContentRect.mLeft,
                         mContentRect.mBottom - mContentRect.mTop, (void*)pControl);
            return;
        }
        if (mpElement->v18())
            return;
    }

    Style::ParagraphStyle saved;
    ctx.Fn8ee770(&saved);
    ctx.SetParagraphStyle(mParaStyle);
    ctx.SetContextRectRelative(mContentRect.mLeft, mContentRect.mTop, mContentRect.mRight,
                               mContentRect.mBottom);
    ctx.mYPos = 0.0f;
    Fn8eab50(ctx);
    ctx.Fn8ef6d0();
    ctx.SetParagraphStyle(saved);
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008e9a10
void __stdcall FUN_008e9a10(EA::XHTML::Layout::RenderingContext_s008e_9a10* ctx, float* a, float* b, int* c, uchar flags)
{
    if (flags & 8) {
        ctx->ReleaseScroll(c[0]);
        ctx->ScrollViewport(a[0], b[1], b[0], b[3]);
    }
    if (flags & 1) {
        ctx->ReleaseScroll(c[1]);
        ctx->ScrollViewport(a[0], a[1], a[2], b[1]);
    }
    if (flags & 2) {
        ctx->ReleaseScroll(c[2]);
        ctx->ScrollViewport(b[2], b[1], a[2], b[3]);
    }
    if (flags & 4) {
        ctx->ReleaseScroll(c[3]);
        ctx->ScrollViewport(a[0], b[3], a[2], a[3]);
    }
}

// @ 0x008e9b10
void __stdcall FUN_008e9b10(EA::XHTML::Layout::RenderingContext_s008e_9a10* ctx, float* a, float* b, int* c, uchar flags, float step)
{
    if (flags & 8) {
        ctx->ReleaseScroll(c[0]);
        float delta = (b[0] - a[0]) * step;
        float cur = b[1] + delta;
        if (b[3] >= cur) {
            float delta2 = delta * 2.0f;
            do {
                float next = cur + delta;
                if (next + delta >= b[3])
                    next = b[3];
                ctx->ScrollViewport(a[0], cur, b[0], next);
                cur = cur + delta2;
            } while (b[3] >= cur);
        }
    }
    if (flags & 1) {
        ctx->ReleaseScroll(c[1]);
        float delta = (b[1] - a[1]) * step;
        float cur = a[0];
        if (a[2] >= cur) {
            float delta2 = delta * 2.0f;
            do {
                float next = cur + delta;
                if (next + delta >= a[2])
                    next = a[2];
                ctx->ScrollViewport(cur, a[1], next, b[1]);
                cur = cur + delta2;
            } while (a[2] >= cur);
        }
    }
    if (flags & 2) {
        ctx->ReleaseScroll(c[2]);
        float delta = (a[2] - b[2]) * step;
        float cur = b[1] + delta;
        if (b[3] >= cur) {
            float delta2 = delta * 2.0f;
            do {
                float next = cur + delta;
                if (next + delta >= b[3])
                    next = b[3];
                ctx->ScrollViewport(b[2], cur, a[2], next);
                cur = cur + delta2;
            } while (b[3] >= cur);
        }
    }
    if (flags & 4) {
        ctx->ReleaseScroll(c[3]);
        float delta = (a[3] - b[3]) * step;
        float cur = a[0];
        if (a[2] >= cur) {
            float delta2 = delta * 2.0f;
            do {
                float next = cur + delta;
                if (next + delta >= a[2])
                    next = a[2];
                ctx->ScrollViewport(cur, b[3], next, a[3]);
                cur = cur + delta2;
            } while (a[2] >= cur);
        }
    }
}

// @ 0x008e9fe0
void __stdcall FUN_008e9fe0(EA::XHTML::Layout::RenderingContext_s008e_9a10* ctx, float* a, float* b, int* c, float x, uchar flags)
{
    float pts[8];
    __declspec(align(8)) uint32_t grad[4];
    int last = 0;

    ctx->ReleaseScroll(-1);

    if (flags & 8) {
        FUN_008e9900(c[0], *(int*)&x, (float*)grad, 4);
        pts[6] = a[3];
        pts[7] = a[0];
        pts[4] = b[3];
        last = c[0];
        pts[5] = b[0];
        pts[2] = b[1];
        pts[0] = a[1];
        pts[3] = pts[5];
        pts[1] = pts[7];
        ctx->DrawQuad(&pts[1], grad[0], &pts[3], grad[1],
                      &pts[5], grad[1], &pts[7], grad[0]);
    }
    if (flags & 1) {
        if (last != c[1] || last == 0)
            FUN_008e9900(c[1], *(int*)&x, (float*)grad, 4);
        last = c[1];
        pts[1] = b[0];
        pts[3] = b[2];
        pts[2] = b[1];
        pts[5] = a[2];
        pts[7] = a[0];
        pts[6] = a[1];
        pts[4] = pts[6];
        pts[0] = pts[2];
        ctx->DrawQuad(&pts[7], grad[0], &pts[5], grad[0],
                      &pts[3], grad[1], &pts[1], grad[1]);
    }
    if (flags & 2) {
        if (last != c[2] || last == 0)
            FUN_008e9900(c[2], *(int*)&x, (float*)grad, 4);
        last = c[2];
        pts[0] = b[3];
        pts[7] = b[2];
        pts[2] = a[3];
        pts[5] = a[2];
        pts[4] = a[1];
        pts[6] = b[1];
        pts[3] = pts[5];
        pts[1] = pts[7];
        ctx->DrawQuad(&pts[7], grad[2], &pts[5], grad[3],
                      &pts[3], grad[3], &pts[1], grad[2]);
    }
    if (flags & 4) {
        if (last != c[3] || last == 0)
            FUN_008e9900(c[3], *(int*)&x, (float*)grad, 4);
        last = c[3];
        pts[3] = b[2];
        pts[1] = a[2];
        pts[5] = b[0];
        pts[4] = b[3];
        pts[6] = a[3];
        pts[7] = a[0];
        pts[2] = pts[4];
        pts[0] = pts[6];
        ctx->DrawQuad(&pts[7], grad[3], &pts[5], grad[2],
                      &pts[3], grad[2], &pts[1], grad[3]);
    }
}

// @ 0x008ea290
void EA::XHTML::Layout::Border::Draw(EA::XHTML::Layout::RenderingContext_s008e_a290& rc, const EA::RectT_s008e_a290<float>* pRect, uchar flags)
{
    // Per-phrase edge mask: a phrase only draws the edges it is selected for.
    volatile ushort edgeFlags[9] = {0};
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

    if (!((borderLeft != 0.0f && mEdgeLeftPhraseIndex != 0) ||
          (borderRight != 0.0f && mEdgeRightPhraseIndex != 0) ||
          (borderTop != 0.0f && mEdgeTopPhraseIndex != 0) ||
          (borderBottom != 0.0f && mEdgeBottomPhraseIndex != 0)))
        return;

    const EA::RectT_s008e_a290<float>& rect = *pRect;
    const float width = rect.mRight - rect.mLeft;
    const float height = rect.mBottom - rect.mTop;

    if (borderLeft + borderRight > width) {
        const float half = (float)floor((double)(width * kHalf));
        if (borderLeft > half)
            borderLeft = half;
        borderRight = width - borderLeft;
    }
    if (borderTop + borderBottom > height) {
        const float half = (float)floor((double)(height * kHalf));
        if (borderTop > half)
            borderTop = half;
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
        BorderDrawDashes(&rc, a, b, (int*)this, (int)(ushort)edgeFlags[1], 1.0f);
    if (edgeFlags[2] != 0)
        BorderDrawDashes(&rc, a, b, (int*)this, (uchar)edgeFlags[2], kThree);

    // One-third-inset edge bands, drawn from the outer rect inwards and from
    // the inner rect outwards.
    if (edgeFlags[4] != 0) {
        const float f1 = (float)floor((double)(borderLeft * kOneThird + kHalf));
        const float f2 = (float)floor((double)(borderTop * kOneThird + kHalf));
        const float f3 = (float)floor((double)(borderRight * kOneThird + kHalf));
        const float f4 = (float)floor((double)(borderBottom * kOneThird + kHalf));
        float outerIn[4];
        float innerOut[4];
        outerIn[0] = a[0] + f1;
        outerIn[1] = a[1] + f2;
        outerIn[2] = a[2] - f3;
        outerIn[3] = a[3] - f4;
        innerOut[0] = b[0] - f1;
        innerOut[1] = b[1] - f2;
        innerOut[2] = b[2] + f3;
        innerOut[3] = b[3] + f4;
        BorderDrawEdges(&rc, a, outerIn, (int*)this, (uchar)edgeFlags[4]);
        BorderDrawEdges(&rc, innerOut, b, (int*)this, (uchar)edgeFlags[4]);
    }

    // Corner banks: two 4-colour ramps swept in opposite directions.
    const float colsNeg[4] = {kNegPointTwo, kNegPointOne, kPointOne, kPointTwo};
    const float colsPos[4] = {kPointTwo, kPointOne, kNegPointOne, kNegPointTwo};
    if (edgeFlags[5] != 0 || edgeFlags[6] != 0) {
        const float h1 = (float)floor((double)(borderLeft * kHalf));
        const float h2 = (float)floor((double)(borderTop * kHalf));
        const float h3 = (float)floor((double)(borderRight * kHalf));
        const float h4 = (float)floor((double)(borderBottom * kHalf));
        float outerIn[4];
        float innerOut[4];
        outerIn[0] = a[0] + h1;
        outerIn[1] = a[1] + h2;
        outerIn[2] = a[2] - h3;
        outerIn[3] = a[3] - h4;
        innerOut[0] = b[0] - h1;
        innerOut[1] = b[1] - h2;
        innerOut[2] = b[2] + h3;
        innerOut[3] = b[3] + h4;
        if (edgeFlags[5] != 0) {
            BorderDrawGradients(&rc, a, outerIn, (int*)this, (float*)colsNeg, (uchar)edgeFlags[5]);
            BorderDrawGradients(&rc, innerOut, b, (int*)this, (float*)colsPos, (uchar)edgeFlags[5]);
        }
        if (edgeFlags[6] != 0) {
            BorderDrawGradients(&rc, a, outerIn, (int*)this, (float*)colsPos, (uchar)edgeFlags[6]);
            BorderDrawGradients(&rc, innerOut, b, (int*)this, (float*)colsNeg, (uchar)edgeFlags[6]);
        }
    }
    if (edgeFlags[7] != 0)
        BorderDrawGradients(&rc, a, b, (int*)this, (float*)colsNeg, (uchar)edgeFlags[7]);
    if (edgeFlags[8] != 0)
        BorderDrawGradients(&rc, a, b, (int*)this, (float*)colsPos, (uchar)edgeFlags[8]);
}

// @ 0x008ea9d0
void __stdcall RenderingContext_EndContentThunk(EA::XHTML::Layout::RenderingContext_s008e_a290* pCtx, void* pArg)
{
    (void)pArg;
    pCtx->EndContent();
}

// @ 0x008ea9e0
void __stdcall SizingContext_FinishThunk(EA::XHTML::Layout::SizingContext_s008e_a290* pCtx, void* pArg)
{
    (void)pArg;
    pCtx->Finish();
}

// @ 0x008ea9f0
void __stdcall RenderingContext_ResetThunk(EA::XHTML::Layout::RenderingContext_s008e_a290* pCtx)
{
    pCtx->Reset();
}

// @ 0x008eaa00
bool __stdcall PickingContext_FlushAllThunk(EA::XHTML::Layout::PickingContext_s008e_a290* pCtx, EA::XHTML::Layout::PickEntry* pEntry)
{
    pCtx->FlushAll(pEntry);
    return false;
}

// @ 0x008eaa20
void EA::XHTML::Layout::Block_s008e_a290::SetUpBox(EA::XHTML::Layout::SizingContext_s008e_a290& sc, Style::StyleState_s008e_a290& style)
{
    if (mpBorder == 0 && style.HasBorder()) {
        EA::XHTML::Layout::Border* pBorder = 0;
        EA::Allocator::StackAllocator_s008e_a290* pAlloc = (EA::Allocator::StackAllocator_s008e_a290*)mpPage;
        char* p = pAlloc->mpCurrentObjectBegin;
        if (pAlloc->mpCurrentBlockEnd - pAlloc->mpCurrentObjectBegin - 0x38 >= 0 ||
            pAlloc->AllocateNewBlock(0x38)) {
            p = pAlloc->mpCurrentObjectBegin;
            pAlloc->mpCurrentObjectBegin = p + 0x38;
            pAlloc->mpCurrentObjectEnd = p + 0x38;
            pBorder = (EA::XHTML::Layout::Border*)p;
        }
        mpBorder = pBorder;
    }
    if (mpBorder != 0)
        mpBorder->Compute(&style, sc.mEnclosingWidth);
}

// @ 0x008eaaf0
void EA::XHTML::Layout::ContainerItem_s008e_a290::LayoutFlow(EA::XHTML::Layout::RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style)
{
    for (EA::XHTML::Layout::ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it->LayoutFlow(ctx, style);
}

// @ 0x008eab50
void EA::XHTML::Layout::ContainerItem_s008e_a290::Render(EA::XHTML::Layout::RenderingContext_s008e_a290& ctx)
{
    for (EA::XHTML::Layout::ItemList::iterator it = mChildItems.begin(); it != mChildItems.end(); ++it)
        it->Render(ctx);
}

// @ 0x008eac20
void EA::XHTML::Layout::Block_s008e_a290::SetUpBox(EA::XHTML::Layout::RenderingContext_s008e_a290& ctx, Style::StyleState_s008e_a290& style)
{
    mFgColor = style.mColor;
    mBgColor = style.mBackgroundColor;
    if (mpBorder == 0 && style.HasBorder()) {
        EA::XHTML::Layout::Border* pBorder = 0;
        EA::Allocator::StackAllocator_s008e_a290* pAlloc = (EA::Allocator::StackAllocator_s008e_a290*)mpPage;
        char* p = pAlloc->mpCurrentObjectBegin;
        if (pAlloc->mpCurrentBlockEnd - pAlloc->mpCurrentObjectBegin - 0x38 >= 0 ||
            pAlloc->AllocateNewBlock(0x38)) {
            p = pAlloc->mpCurrentObjectBegin;
            pAlloc->mpCurrentObjectBegin = p + 0x38;
            pAlloc->mpCurrentObjectEnd = p + 0x38;
            pBorder = (EA::XHTML::Layout::Border*)p;
        }
        mpBorder = pBorder;
    }
    if (mpBorder != 0)
        mpBorder->Compute(&style, ctx.mContextRect.mRight - ctx.mContextRect.mLeft);

    if (mpBackground == 0 && style.HasBackground()) {
        EA::XHTML::Layout::Background_s008e_a290* pBg = 0;
        EA::Allocator::StackAllocator_s008e_a290* pAlloc = (EA::Allocator::StackAllocator_s008e_a290*)mpPage;
        char* p = pAlloc->mpCurrentObjectBegin;
        if (pAlloc->mpCurrentBlockEnd - pAlloc->mpCurrentObjectBegin - 0x48 >= 0 ||
            pAlloc->AllocateNewBlock(0x48)) {
            p = pAlloc->mpCurrentObjectBegin;
            pAlloc->mpCurrentObjectBegin = p + 0x48;
            pAlloc->mpCurrentObjectEnd = p + 0x48;
            if (p != 0)
                pBg = new (p) EA::XHTML::Layout::Background_s008e_a290((EA::Allocator::StackAllocator_s008e_a290*)mpPage);
        }
        mpBackground = pBg;
    }
    if (mpBackground != 0)
        mpBackground->SetStyle(&style);

    mBoxWidthPx = style.mBorderMask;
    mBoxHeightPx = style.mBoxWidthPx;
}

// @ 0x008eae40
EA::XHTML::Layout::Item_s008e_a290::Item_s008e_a290(EA::XHTML::Layout::Page_s008e_a290* pPage, int nType)
{
    mpPrev = 0;
    mpNext = 0;
    mpPage = pPage;
    mItemType = (EA::XHTML::Layout::ItemType)nType;
    mSelectableIndex = pPage->mSelectableCount;
}

// @ 0x008ef870
EA::XHTML::Layout::SizingContext_s008e_ebb0::SizingContext_s008e_ebb0(float h)
: EA::Text::Typesetter_s008e_ebb0(0)
{
    mfMaxHeight = 0.0f;
    mfMaxWidth = 0.0f;
    mfHeight = h;
    Reset(1);
}

// @ 0x008ef8b0
void EA::XHTML::Layout::SizingContext_s008e_ebb0::Clear()
{
    float z = 0.0f;
    mfMaxHeight = z;
    mfMaxWidth = z;
    Reset(1);
}

// @ 0x008ef900
void EA::XHTML::Layout::SizingContext_s008e_ebb0::Finish()
{
    EA::Text::LineLayout_s008e_ebb0* pLine = GetLineLayout();
    GetGameData()->mMode = 3;
    Set(*(const float*)0x013f6d90, 0.0f, 0.0f);
    while (GetType() != 2) {
        FinalizeLine();
        mfMaxHeight = tmax(mfMaxHeight, (float)ceil((double)pLine->mLineMetrics[2]));
        NextLine(0);
    }
    Reset(0);
    GetGameData()->mMode = 3;
    Set(0.0f, 0.0f, 0.0f);
    while (GetType() != 2) {
        FinalizeLine();
        mfMaxWidth = tmax(mfMaxWidth, pLine->mLineMetrics[2]);
        NextLine(0);
    }
    if (mfMaxWidth == *(const float*)0x01485378)
        mfMaxWidth = mfMaxHeight;
    Reset(1);
}

// @ 0x008efba0
struct R2F8 { float f[8]; void Reset() { f[0] = 0.0f; f[1] = 0.0f; f[2] = 0.0f; f[3] = 0.0f; f[4] = 0.0f; f[5] = 0.0f; f[6] = 0.0f; f[7] = 0.0f; } };
struct R2F4 { float x, y, z, w; void Reset() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; } };
StackingContext_s008e_fad0* StackingContext_s008e_fad0::Init(u32 owner, u32 a1, u32 a2)
{
    pad00 = owner;
    ((TypesetterCtor*)&mTypesetter)->Construct(0);
    ((R2F8*)&mf534)->Reset(); mf554 = 0.0f; mf558 = 0.0f; mf55c = 0.0f; mf560 = 0.0f;
    mf564 = 0.0f; mf568 = 0.0f; mf56c = 0.0f; mf570 = 0.0f;
    mb574 = 1;
    mpFloatsHead = 0;
    mpFloatsTail = 0;
    mf580 = 0;
    ((TypesetterCtor*)&mTypesetter)->SetSomething((void*)((char*)a2 + 0xc));
    return this;
}

// @ 0x008efcd0
void StackingContext_s008e_fad0::InsertFloat(int kind)
{
    FloatEntry* p;
    FloatEntry** pp;
    for (p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (kind == 3 || kind == p->mKind) {
            if (mf55c < p->mTop)
                mf55c = p->mTop;
        }
    }
    pp = &mpFloatsHead;
    while (*pp != 0) {
        p = *pp;
        if (mf55c < p->mTop)
            pp = &p->mpNext;
        else
            *pp = p->mpNext;
    }
}

// @ 0x008efe80
void StackingContext_s008e_fad0::FlushLines(int count)
{
    LineLayout_s008e_fad0* line = mTypesetter.GetLineLayout();
    TripleFloat_s008e_fad0* tf = &mTypesetter;
    tf->Set(mf558 - mf554, mf554, mf55c);
    while (count != 0) {
        if (mTypesetter.ProcessLine() != 1)
            break;
        --count;
        mTypesetter.FinalizeLine();
        if (line->miFlagAC == 0) {
            mf56c = line->mfHeight;
            mf570 = line->mfHeight - line->mfDescent;
        }
        float h = (float)ceil((double)line->mfHeight);
        float descent = line->mfDescent;
        AddFloats(line);
        mf55c += h - (float)iat_floor((double)descent);
        FloatEntry** pp = &mpFloatsHead;
        bool changed = false;
        while (*pp != 0) {
            FloatEntry* p = *pp;
            if (mf55c >= p->mTop) {
                *pp = p->mpNext;
                changed = true;
                continue;
            }
            pp = &p->mpNext;
        }
        if (changed)
            RecomputeFloatLimits();
        tf->Set(mf558 - mf554, mf554, mf55c);
        mTypesetter.NextLine(0);
    }
}

// @ 0x008f0010
void StackingContext_s008e_fad0::FlushAllLines()
{
    LineLayout_s008e_fad0* line = mTypesetter.GetLineLayout();
    TripleFloat_s008e_fad0* tf = &mTypesetter;
    tf->Set(mf558 - mf554, mf554, mf55c);
    while (mTypesetter.GetType() != 2) {
        mTypesetter.FinalizeLine();
        if (line->miFlagAC == 0) {
            mf56c = line->mfHeight;
            mf570 = line->mfHeight - line->mfDescent;
        }
        float h = (float)ceil((double)line->mfHeight);
        float descent = line->mfDescent;
        AddFloats(line);
        mf55c += h - (float)iat_floor((double)descent);
        FloatEntry** pp = &mpFloatsHead;
        bool changed = false;
        while (*pp != 0) {
            FloatEntry* p = *pp;
            if (mf55c >= p->mTop) {
                *pp = p->mpNext;
                changed = true;
                continue;
            }
            pp = &p->mpNext;
        }
        if (changed)
            RecomputeFloatLimits();
        tf->Set(mf558 - mf554, mf554, mf55c);
        mTypesetter.NextLine(0);
    }
    mTypesetter.Reset(1);
}

// @ 0x008f0280
void StackingContext_s008e_fad0::RegisterFloat(FloatEntry* e)
{
    int kind = e->mKind;
    float cur = mf55c;
    float lo = cur;
    float hi = cur;
    float zero = 0.0f;
    float width = mf53c - mf534;
    FloatEntry* p;
    FloatEntry* match = 0;
    float best = hi;

    for (p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (mf55c < p->mTop)
            p = p;
        else
            p = p;
    }
    for (p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (p->mKind == kind) {
            best = (p->mTop <= best) ? best : p->mTop;
            hi = best;
            match = p;
        }
    }
    if (match != 0) {
        lo = (match->mSide <= cur) ? cur : match->mSide;
        cur = lo;
        if (kind == 1)
            zero = match->mSide2;
        else
            width = match->mOuter;
    }
    for (p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (p->mKind != kind && lo < p->mTop) {
            if (kind == 2) {
                zero = (p->mSide2 <= zero) ? zero : p->mSide2;
            } else {
                width = (width < p->mOuter || width == p->mOuter) ? width : p->mOuter;
            }
        }
    }
    {
        float a = hi;
        float b = lo;
        if (kind == 1) {
            float c = zero;
            if (width - zero < e->mSide2 - e->mOuter) {
                c = 0.0f;
                b = hi;
            }
            FUN_008e7e00(c, b);
        } else {
            if (width - zero < e->mSide2 - e->mOuter) {
                width = mf53c - mf534;
                b = hi;
            }
            FUN_008e7e00(width - (e->mSide2 - e->mOuter), b);
        }
        (void)a;
    }
    e->mpNext = 0;
    if (mpFloatsHead == 0)
        mpFloatsHead = e;
    else
        mpFloatsTail->mpNext = e;
    mpFloatsTail = e;
    RecomputeFloatLimits();
}

// @ 0x008f0490
void SlotOwner::Setup(u32 a1, StyleSource* src)
{
    (void)a1;
    miF0 = src->mi2dc;
    mfF4 = 1.0f;
    if (src->mi2d8 == 9)
        mfF4 = src->mf2d4;
}

// @ 0x008f04d0
void Table_s008e_fad0::DrawContent(RenderingContext_s008e_fad0* ctx)
{
    TableRow_s008e_fad0** row;
    ctx->SetContextRectRelative(mContentRect);
    for (row = mRowsBegin; row != mRowsEnd; ++row) {
        void** cell;
        TableRow_s008e_fad0* r = *row;
        for (cell = r->mCellsBegin; cell != r->mCellsEnd; ++cell) {
            Item_s008e_fad0* item = (Item_s008e_fad0*)*cell;
            Item_s008e_fad0* anchor = (Item_s008e_fad0*)((char*)item + 0x18);
            if (*(void**)((char*)anchor + 4) != anchor)
                item->Draw(ctx);
        }
    }
}

// @ 0x008f0550
char Table_s008e_fad0::PickContent(PickingContext_s008e_fad0* ctx, u32 arg)
{
    TableRow_s008e_fad0** row;
    ctx->SetContextRectRelative(mContentRect);
    for (row = mRowsBegin; row != mRowsEnd; ++row) {
        void** cell;
        TableRow_s008e_fad0* r = *row;
        for (cell = r->mCellsBegin; cell != r->mCellsEnd; ++cell) {
            Item_s008e_fad0* item = (Item_s008e_fad0*)*cell;
            Item_s008e_fad0* anchor = (Item_s008e_fad0*)((char*)item + 0x18);
            if (*(void**)((char*)anchor + 4) != anchor) {
                if (item->Pick(ctx, arg))
                    return 1;
            }
        }
    }
    return 0;
}

// @ 0x008f05f0
void CopyCells(Cell14** out, const Cell14* first, const Cell14* last, Cell14* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0)
                *dst = *first;
            ++first;
            if (dst != 0)
                ++dst;
        } while (first != last);
        *out = dst;
    }
}

// @ 0x008f0640
void FillCells(Cell14* dst, unsigned count, const Cell14* src)
{
    Cell14* d = dst;
    for (unsigned i = count; i > 0; --i, ++d)
        if (d) *d = *src;
}

// @ 0x008f0680
void ItemListOwner::Walk7(u32 a1, u32 a2)
{
    for (Item_s008e_fad0* it = EndOf(mHead.mpNext);;) {
        Item_s008e_fad0* end = EndOf(&mHead);
        if (it == end)
            break;
        if (it->mItemType == 7)
            it->Layout(a1, a2);
        it = EndOf((ListNode*)it->mpNext);
    }
}

// @ 0x008f06e0
void ItemListOwner::Walk8(u32 a1, u32 a2)
{
    for (Item_s008e_fad0* it = EndOf(mHead.mpNext);;) {
        Item_s008e_fad0* end = EndOf(&mHead);
        if (it == end)
            break;
        if (it->mItemType == 8)
            it->Layout(a1, a2);
        it = EndOf((ListNode*)it->mpNext);
    }
}

// @ 0x008f0740
void Table::LayoutRows(StackingContext* ctx, StyleState* style)
{
    float width = mContentRect.r - mContentRect.l;
    u32 rowCount = (u32)(mRowsEnd - mRowsBegin);

    // every column starts at its minimum width
    for (int i = 0; i < mColCount; ++i)
        mColsBegin[i].width = mColsBegin[i].minWidth;

    // hand the extra width to the columns (percent columns first by their percentage)
    if (width > mMinWidth) {
        float extra = width - mMinWidth;
        float flex = mMaxWidth - mMinWidth;
        for (int i = 0; i < mColCount; ++i) {
            TableColumn* c = &mColsBegin[i];
            float pct = c->percentWidth;
            if (pct > 0.0f) {
                c->width = Floor((width - (float)(mColCount + 1) * mColSpacing) * pct + 0.5f);
            } else {
                float range = c->maxWidth - c->minWidth;
                float add;
                if (flex > 0.0f && extra > 0.0f) {
                    add = Floor(((range * extra + flex) - 1.0f) / flex);
                    extra = extra - add;
                    flex = flex - range;
                } else {
                    add = 0.0f;
                }
                c->width = c->width + add;
            }
        }
    }

    // column x positions
    float x = mColSpacing;
    for (int i = 0; i < mColCount; ++i) {
        TableColumn* c = &mColsBegin[i];
        c->xPos = x;
        x = (c->width + mColSpacing) + x;
    }

    for (TableRow** r = mRowsBegin; r != mRowsEnd; ++r)
        (*r)->mHeight = 0.0f;

    // cell rectangles in x; the y extent is filled in below
    for (TableRow** r = mRowsBegin; r != mRowsEnd; ++r) {
        for (TableCell** cp = (*r)->mCellsBegin; cp != (*r)->mCellsEnd; ++cp) {
            TableCell* cell = *cp;
            TableColumn* last = mColsBegin + (cell->mColSpan + cell->mColPos) - 1;
            cell->mOuterRect.l = mColsBegin[cell->mColPos].xPos;
            cell->mOuterRect.r = last->width + last->xPos;
            cell->mOuterRect.t = 0.0f;
            cell->mOuterRect.b = 0.0f;
            cell->mBorderRect = cell->mOuterRect;
            cell->mPaddingRect = cell->mBorderRect;
            cell->mPaddingRect.l = cell->mBorderWidth.l + cell->mPaddingRect.l;
            cell->mPaddingRect.r = cell->mPaddingRect.r - cell->mBorderWidth.r;
            cell->mPaddingRect.t = cell->mBorderWidth.t + cell->mPaddingRect.t;
            cell->mPaddingRect.b = cell->mPaddingRect.b - cell->mBorderWidth.b;
            cell->mContentRect = cell->mPaddingRect;
            cell->mContentRect.l = cell->mPadding.l + cell->mContentRect.l;
            cell->mContentRect.r = cell->mContentRect.r - cell->mPadding.r;
            cell->mContentRect.t = cell->mPadding.t + cell->mContentRect.t;
            cell->mContentRect.b = cell->mContentRect.b - cell->mPadding.b;
        }
    }

    // lay out the child items that are row groups / rows
    for (Item* it = ItemOf(mItems.mpNext); it != ItemOf(&mItems); it = ItemOf(it->node.mpNext)) {
        if (it->mItemType == 8)
            it->Layout(ctx, style);
        else if (it->mItemType == 9)
            it->Layout(ctx, style);
    }

    // row heights from the cells that span a single row, then from the spanning cells
    for (TableRow** r = mRowsBegin; r != mRowsEnd; ++r) {
        for (TableCell** cp = (*r)->mCellsBegin; cp != (*r)->mCellsEnd; ++cp) {
            TableCell* cell = *cp;
            TableRow* row = *r;
            float cellH = cell->mBorderRect.b - cell->mBorderRect.t;
            if (cell->mRowSpan == 1) {
                row->mHeight = Max(row->mHeight, cellH);
            } else {
                int first = cell->mRowPos;
                int end = cell->mRowSpan + first;
                float sum = 0.0f;
                for (int i = first; i < end; ++i)
                    sum += mRowsBegin[i]->mHeight;
                float avail = cellH - (float)(cell->mRowSpan - 1) * mRowSpacing;
                if (sum < avail) {
                    float extra = avail - sum;
                    for (int i = cell->mRowPos; i < end; ++i) {
                        TableRow* sr = mRowsBegin[i];
                        float h = sr->mHeight;
                        float add;
                        if (sum > 0.0f && extra > 0.0f) {
                            add = Floor(((extra * h + sum) - 1.0f) / sum);
                            extra = extra - add;
                            sum = sum - h;
                        } else {
                            add = 0.0f;
                        }
                        sr->mHeight = h + add;
                    }
                }
            }
        }
    }

    // total height of all rows
    float total = mRowSpacing;
    for (TableRow** r = mRowsBegin; r != mRowsEnd; ++r)
        total = ((*r)->mHeight + mRowSpacing) + total;

    // an explicit height (not auto) distributes the leftover height over the rows
    if (style->mHeightKind != 10 && style->mHeight != 0.0f) {
        float extra = (mContentRect.b - mContentRect.t) - total;
        float sum = total - (float)(rowCount + 1) * mRowSpacing;
        for (TableRow** r = mRowsBegin; r != mRowsEnd; ++r) {
            TableRow* row = *r;
            float h = row->mHeight;
            float add;
            if (sum > 0.0f && extra > 0.0f) {
                add = Floor(((extra * h + sum) - 1.0f) / sum);
                extra = extra - add;
                sum = sum - h;
            } else {
                add = 0.0f;
            }
            row->mHeight = row->mHeight + add;
        }
    }

    // row y positions
    ctx->mYPos = 0.0f;
    ctx->mYPos = mRowSpacing;
    for (TableRow** r = mRowsBegin; r != mRowsEnd; ++r) {
        (*r)->mTop = ctx->mYPos;
        ctx->mYPos = (*r)->mHeight + ctx->mYPos;
        (*r)->mBottom = ctx->mYPos;
        ctx->mYPos = mRowSpacing + ctx->mYPos;
    }
    mContentRect.b = mContentRect.t + ctx->mYPos;

    // cell y extents and vertical alignment inside the cell
    for (TableRow** r = mRowsBegin; r != mRowsEnd; ++r) {
        for (TableCell** cp = (*r)->mCellsBegin; cp != (*r)->mCellsEnd; ++cp) {
            TableCell* cell = *cp;
            TableRow* row = *r;
            u32 endRow = (u32)(cell->mRowPos + cell->mRowSpan);
            float contentH = cell->mContentRect.b - cell->mContentRect.t;
            float top = row->mTop;
            if (endRow > rowCount)
                endRow = rowCount;
            TableRow* lastRow = mRowsBegin[endRow - 1];
            cell->mBorderRect.t = top;
            cell->mOuterRect.t = top;
            cell->mPaddingRect.t = cell->mBorderWidth.t + cell->mBorderRect.t;
            cell->mContentRect.t = cell->mPadding.t + cell->mPaddingRect.t;
            cell->mBorderRect.b = lastRow->mBottom;
            cell->mOuterRect.b = lastRow->mBottom;
            cell->mPaddingRect.b = cell->mBorderRect.b - cell->mBorderWidth.b;
            cell->mContentRect.b = cell->mPaddingRect.b - cell->mPadding.b;
            cell->mPickRect = cell->mContentRect;
            switch (cell->mVAlign) {
            case 0:
            case 5:
            case 7:
                cell->mContentRect.t = cell->mContentRect.b - contentH;
                break;
            case 3:
                cell->mContentRect.t = (float)(floor((double)(((cell->mContentRect.b - cell->mContentRect.t) - contentH) * 0.5f)) + cell->mContentRect.t);
                break;
            case 9:
                cell->mContentRect.t = (float)(floor((double)(((cell->mContentRect.b - cell->mContentRect.t) - contentH) * cell->mValignPct + 0.5f)) + cell->mContentRect.t);
                break;
            }
            cell->mContentRect.b = contentH + cell->mContentRect.t;
        }
    }
}

// @ 0x008f16c0
namespace EA { namespace XHTML { namespace Layout {
void TableRow_s008f_16c0::Dispose()
{
    FUN_011e0744(mCells.mpBegin, mCells.mpEnd, 0);
    const int count = (int)((char*)mCells.mpEnd - (char*)mCells.mpBegin) >> 2;
    mCells.mpEnd = (TableCell_s008f_16c0**)((char*)mCells.mpEnd - count * 4);
    ((Item_s008f_16c0*)this)->Dispose();
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f1850
namespace EA { namespace XHTML { namespace Layout {
void Table_s008f_16c0::Dispose()
{
    FUN_00951bf0(mCols.mpEnd, mCols.mpEnd, mCols.mpBegin);
    const int colCount = (int)((char*)mCols.mpEnd - (char*)mCols.mpBegin) / 0x14;
    mCols.mpEnd = (TableColumn_s008f_16c0*)((char*)mCols.mpEnd - colCount * 0x14);
    FUN_011e0744(mRows.mpBegin, mRows.mpEnd, 0);
    const int rowCount = (int)((char*)mRows.mpEnd - (char*)mRows.mpBegin) >> 2;
    mRows.mpEnd = (TableRow_s008f_16c0**)((char*)mRows.mpEnd - rowCount * 4);
    ((Item_s008f_16c0*)this)->Dispose();
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f18c0
namespace EA { namespace XHTML { namespace Layout {
template <typename T> void Vector<T>::resize(uint32_t n)
{
    T* end = mpEnd;
    const uint32_t count = (uint32_t)(end - mpBegin);
    if (count < n) {
        T tmp = T();
        ((VectorOps*)this)->F_8f1210(mpEnd, (int)(n - count), &tmp);
        return;
    }
    T* newEnd = mpBegin + n;
    FUN_00951bf0(end, end, newEnd);
    const int back = (int)((char*)newEnd - (char*)end) / (int)sizeof(T);
    mpEnd = (T*)((char*)end + back * (int)sizeof(T));
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f1c40
namespace EA { namespace XHTML { namespace Layout {
void Table_s008f_16c0::MeasureContent(SizingContext& sc, Style::StyleState_s008f_16c0& style)
{
    if (!mBuilt) {
        mBuilt = true;
        Build();
    }

    const float enclosing = sc.mEnclosingWidth;
    mRowSpacing = Round(style.mBorderSpacingV.ToPixelsNonNeg(enclosing, style.mFontMetrics));
    mColSpacing = Round(style.mBorderSpacingH.ToPixelsNonNeg(enclosing, style.mFontMetrics));

    SizingContext sizing(enclosing);
    ContainerItem::MeasureContent(sizing, style);

    for (TableColumn_s008f_16c0* col = mCols.mpBegin; col != mCols.mpEnd; ++col) {
        col->mMinWidth = 0.0f;
        col->mMaxWidth = 0.0f;
        col->mPercentWidth = 0.0f;
    }

    for (TableRow_s008f_16c0** rowIt = mRows.mpBegin; rowIt != mRows.mpEnd; ++rowIt) {
        TableRow_s008f_16c0* row = *rowIt;
        TableCell_s008f_16c0** cellEnd = row->mCells.mpEnd;
        for (TableCell_s008f_16c0** cellIt = row->mCells.mpBegin; cellIt != cellEnd; ++cellIt) {
            TableCell_s008f_16c0* cell = *cellIt;
            float extra = ((cell->mPadding.mRight + cell->mPadding.mLeft) + cell->mBorderWidth.mRight) + cell->mBorderWidth.mLeft;
            float minW = cell->mMinWidth + extra;
            float maxW = cell->mMaxWidth + extra;
            float pctW = cell->mPercentWidth;
            const int span = cell->mColSpan;

            if (span == 1) {
                TableColumn_s008f_16c0& col = mCols.mpBegin[cell->mColPos];
                col.mMinWidth = max_(col.mMinWidth, minW);
                col.mMaxWidth = max_(col.mMaxWidth, maxW);
                col.mPercentWidth = max_(col.mPercentWidth, cell->mPercentWidth);
            } else {
                const float spacing = (float)(span - 1) * mColSpacing;
                const int first = cell->mColPos;
                const int last = first + span;
                float sumMin = 0.0f, sumMax = 0.0f, sumPct = 0.0f;
                for (int c = first; c < last; ++c) {
                    sumMin += mCols.mpBegin[c].mMinWidth;
                    sumMax += mCols.mpBegin[c].mMaxWidth;
                    sumPct += mCols.mpBegin[c].mPercentWidth;
                }

                // min widths
                if (sumMin < minW - spacing) {
                    float remaining = (minW - spacing) - sumMin;
                    float runSum = sumMin;
                    for (int c = cell->mColPos; c < cell->mColPos + cell->mColSpan; ++c) {
                        TableColumn_s008f_16c0* col = &mCols.mpBegin[c];
                        const float colValue = col->mMinWidth;
                        float add = 0.0f;
                        if (runSum > 0.0f && remaining > 0.0f) {
                            add = (float)floor(((remaining * colValue + runSum) - 1.0f) / runSum);
                            remaining = remaining - add;
                            runSum = runSum - colValue;
                        }
                        col->mMinWidth = colValue + add;
                    }
                }

                // percent widths
                if (cell->mPercentWidth != 0.0f && sumPct < pctW - spacing) {
                    float remaining = pctW - sumPct;
                    float runSum = sumPct;
                    for (int c = cell->mColPos; c < cell->mColPos + cell->mColSpan; ++c) {
                        TableColumn_s008f_16c0* col = &mCols.mpBegin[c];
                        const float colValue = col->mPercentWidth;
                        float add = 0.0f;
                        if (runSum > 0.0f && remaining > 0.0f) {
                            add = (float)floor(((remaining * colValue + runSum) - 1.0f) / runSum);
                            remaining = remaining - add;
                            runSum = runSum - colValue;
                        }
                        col->mPercentWidth = colValue + add;
                    }
                }

                // max widths
                if (sumMax < maxW) {
                    float remaining = (maxW - spacing) - sumMax;
                    float runSum = sumMax;
                    for (int c = cell->mColPos; c < cell->mColPos + cell->mColSpan; ++c) {
                        TableColumn_s008f_16c0* col = &mCols.mpBegin[c];
                        const float colValue = col->mMaxWidth;
                        float add = 0.0f;
                        if (runSum > 0.0f && remaining > 0.0f) {
                            add = (float)floor(((remaining * colValue + runSum) - 1.0f) / runSum);
                            remaining = remaining - add;
                            runSum = runSum - colValue;
                        }
                        col->mMaxWidth = colValue + add;
                    }
                }
            }
        }
    }

    const int colCount = mColCount;
    mMinWidth = 0.0f;
    mMaxWidth = 0.0f;
    for (int i = 0; i < colCount; ++i) {
        mMinWidth = mMinWidth + mCols.mpBegin[i].mMinWidth;
        mMaxWidth = mCols.mpBegin[i].mMaxWidth + mMaxWidth;
    }
    const float spacingTotal = (float)(colCount + 1) * mColSpacing;
    mMinWidth = spacingTotal + mMinWidth;
    mMaxWidth = spacingTotal + mMaxWidth;
    sc.mMinWidth = mMinWidth;
    sc.mMaxWidth = mMaxWidth;
}
}}}  // namespace EA::XHTML::Layout
