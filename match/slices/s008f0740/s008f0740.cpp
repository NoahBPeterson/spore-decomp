// Slice s008f0740: EA::XHTML::Layout::Table row/column placement (retail EAWebKit XHTML layout).
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.  Retail offsets (checked against the disassembly):
// Table: rowSpacing +0xd0, colSpacing +0xd4, cols +0xd8 (vector, 0x14 stride slot), rows +0xec,
// minWidth +0x100, maxWidth +0x104; TableCell : Block rects at +0x64..+0xb4.
#include <math.h>

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

// StackingContext: only the y cursor is touched (retail +0x55c)
struct StackingContext {
    char pad[0x55c];
    float mYPos;
};

// StyleState: height style (retail +0x374 value, +0x378 kind)
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

// intrusive_list node -> item (the node sits at +4, after the vptr); null stays null
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

// @ 0x008f0740  distribute the table width over the columns, place the cells, then size the rows
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
