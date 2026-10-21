// src/game/UTFSpore_Win32/Table.cpp -- migrated from slice(s) s008f16c0, s008f0740 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Table.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "EA/Text/Typesetter.h"

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
struct RectT_s008f_16c0 {
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
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TableRow_s008f_16c0 {
public:
    uint32_t pad000[0x5c / 4];             // InlineItem base
    Vector<TableCell_s008f_16c0*> mCells;             // +0x5c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct TableColumn_s008f_16c0 {
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
};
}
}
}
// ---- items of slice s008f16c0 end

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
