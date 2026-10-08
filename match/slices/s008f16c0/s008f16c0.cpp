// Slice s008f16c0 -- EA::XHTML::Layout::Table::MeasureContent @ 0x008F1C40 (EA XHTML layout engine, Table.cpp).
// Retail layouts: EA::Text::Typesetter is 0x530 bytes in retail (0x548 in the 2008 dev PDB), and Table keeps its
// two column/row vectors 0x14 bytes wide, so mMinWidth/mMaxWidth/mBuilt sit 8 bytes above the PDB offsets.
//
// Computes the table's min/max content width: builds the column/row structure on first use, rounds the
// border spacing, measures the children, then folds every cell's min/max/percent width into the columns
// (a spanning cell distributes its excess over the spanned columns proportionally) and sums the columns.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace EA {

template <typename T>
struct RectT {
    T mLeft, mTop, mRight, mBottom;
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

struct FontMetrics {
    float mfFontSize, mfEmSize, mfExSize, mfAscent, mfDescent;
};

struct Length {
    float mValue;   // +0
    int mUnits;     // +4
    float ToPixelsNonNeg(float reference, const FontMetrics& fm) const;    // 0x008f9660
};

class StyleState {
public:
    uint32_t pad000[0x41c / 4];
    Length mBorderSpacingH;       // +0x41c
    Length mBorderSpacingV;       // +0x424
    uint32_t pad42c;
    FontMetrics mFontMetrics;     // +0x430
};

}  // namespace Style

namespace Layout {

class SizingContext {
public:
    SizingContext(float enclosingWidth);   // 0x008ef870
    Text::Typesetter mTypesetter;          // +0x0
    float mMaxWidth;                       // +0x530
    float mMinWidth;                       // +0x534
    float mEnclosingWidth;                 // +0x538
};

class Item {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style);   // +0x20

    void* mpNext;                          // +0x4
    void* mpPrev;                          // +0x8
    void* mpPage;                          // +0xc
    int mItemType;                         // +0x10
    unsigned int mSelectableIndex;         // +0x14
};

class ContainerItem : public Item {
public:
    void* mChildItems[2];                  // +0x18
    void* mpElement;                       // +0x20
    void* mStyleRules;                     // +0x24
    unsigned int mnRuleCount;              // +0x28
    int mDisplay;                          // +0x2c
    int mPosition;                         // +0x30
    uint32_t pad34[(0x50 - 0x34) / 4];
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style);   // +0x20, 0x008eaa90
};

class Block : public ContainerItem {
public:
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

class TableCell : public Block {
public:
    int mColSpan;                          // +0xc4
    int mRowSpan;                          // +0xc8
    int mColPos;                           // +0xcc
    int mRowPos;                           // +0xd0
    float mMinWidth;                       // +0xd4
    float mMaxWidth;                       // +0xd8
    float mPercentWidth;                   // +0xdc
    RectT<float> mPadding;                 // +0xe0
};

// eastl::vector<T*> header (begin, end, capacity, allocator)
template <typename T>
struct Vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
};

class TableRow {
public:
    uint32_t pad000[0x5c / 4];             // InlineItem base
    Vector<TableCell*> mCells;             // +0x5c
};

struct TableColumn {
    float mMinWidth;                       // +0x0
    float mMaxWidth;                       // +0x4
    float mPercentWidth;                   // +0x8
    float mXPos;                           // +0xc
    float mWidth;                          // +0x10
};

template <typename T>
inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }

inline float Round(float f) { return (float)floor(f + 0.5f); }

class Table : public Block {
public:
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style);
    void Build();                          // 0x008f1960

    int mColCount;                         // +0xc4
    int mRowIndex;                         // +0xc8
    int mColIndex;                         // +0xcc
    float mRowSpacing;                     // +0xd0
    float mColSpacing;                     // +0xd4
    Vector<TableColumn> mCols;             // +0xd8
    Vector<TableRow*> mRows;               // +0xec
    float mMinWidth;                       // +0x100
    float mMaxWidth;                       // +0x104
    bool mBuilt;                           // +0x108
};

// @ 0x008F1C40
void Table::MeasureContent(SizingContext& sc, Style::StyleState& style)
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

    for (TableColumn* col = mCols.mpBegin; col != mCols.mpEnd; ++col) {
        col->mMinWidth = 0.0f;
        col->mMaxWidth = 0.0f;
        col->mPercentWidth = 0.0f;
    }

    for (TableRow** rowIt = mRows.mpBegin; rowIt != mRows.mpEnd; ++rowIt) {
        TableRow* row = *rowIt;
        TableCell** cellEnd = row->mCells.mpEnd;
        for (TableCell** cellIt = row->mCells.mpBegin; cellIt != cellEnd; ++cellIt) {
            TableCell* cell = *cellIt;
            float extra = ((cell->mPadding.mRight + cell->mPadding.mLeft) + cell->mBorderWidth.mRight) + cell->mBorderWidth.mLeft;
            float minW = cell->mMinWidth + extra;
            float maxW = cell->mMaxWidth + extra;
            float pctW = cell->mPercentWidth;
            const int span = cell->mColSpan;

            if (span == 1) {
                TableColumn& col = mCols.mpBegin[cell->mColPos];
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
                        TableColumn* col = &mCols.mpBegin[c];
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
                        TableColumn* col = &mCols.mpBegin[c];
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
                        TableColumn* col = &mCols.mpBegin[c];
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

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA
