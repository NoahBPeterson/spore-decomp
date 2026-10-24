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
class RectT { public:
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

class FontMetrics { public:
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
    void Dispose();                        // 0x008eae70
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

    void resize(uint32_t n);               // 0x008f18c0
};

// non-template view of the same vector layout so the helper's annotation resolves
struct VectorOps {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];
    void F_8f1210(void* pos, int n, void* val);  // 0x008f1210
};

void FUN_011e0744(void* first, void* last, int zero);   // 0x011e0744
void FUN_00951bf0(void* first, void* last, void* dst);  // 0x00951bf0

class Table;

class TableRow {
public:
    uint32_t pad000[0x5c / 4];             // InlineItem base
    Vector<TableCell*> mCells;             // +0x5c
    void Dispose();                        // 0x008f16c0
    void Build(Table* pTable);             // 0x008f1700
};

class TableColumn { public:
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
    void Dispose();                        // 0x008f1850
};

// --- property/list helpers (TextItem family) ------------------------------

class PageText {
public:
    uint32_t GetTextStyle(void* arg);                       // 0x008ec580
};

class StyleOwner {
public:
    void ApplyStyleA(void* a, int b, uint32_t c);           // 0x008efa50
    void ApplyStyleB(void* a, int b, uint32_t c);           // 0x008ef8d0
};

class TextItemX {
public:
    uint8_t pad00[0x0c];
    PageText* mpPage;                      // +0x0c
    uint8_t pad10[0x08];
    void* mpStyle;                         // +0x18
    int mLength;                           // +0x1c
    uint32_t mTextStyle;                   // +0x20

    void F_8f2350(void* owner, void* styleArg);             // 0x008f2350
    void F_8f2380(void* owner, void* styleArg);             // 0x008f2380
    void F_8f23b0(void* owner);                             // 0x008f23b0
    bool F_8f23d0(void* owner, void* unused);               // 0x008f23d0
};

class PickCtxX {
public:
    void PickTextA(TextItemX* item, uint32_t style);        // 0x008ee400
    void PickTextB(TextItemX* item, uint32_t style);        // 0x008ee990
};

class PropNodeX {
public:
    uint32_t mVtable;                      // +0x00
    uint32_t mField04;                     // +0x04
    uint32_t mField08;                     // +0x08
    uint32_t mField0c;                     // +0x0c
    int mLength;                           // +0x10

    PropNodeX* F_8f2440(int a, const uint16_t* str);        // 0x008f2440
    PropNodeX* F_8f24a0(int a, const uint16_t* str);        // 0x008f24a0
};

struct ListNodeX {
    uint32_t mField0;                      // +0x00
    uint32_t mField4;                      // +0x04
};

class HeadTailX {
public:
    ListNodeX* mpHead;                     // +0x00
    ListNodeX* mpTail;                     // +0x04

    void F_8f24f0(ListNodeX* node);                         // 0x008f24f0
};

class PoolX {
public:
    uint8_t pad00[0x08];
    int mField08;                          // +0x08
    int mField0c;                          // +0x0c
    int mField10;                          // +0x10
    uint8_t pad14[0x04];

    bool F_928ba0(uint32_t size);                           // 0x00928ba0
};

class PoolNodeX {
public:
    uint32_t mVtable;                      // +0x00
    uint32_t mField04;                     // +0x04
    uint32_t mField08;                     // +0x08
    uint32_t mField0c;                     // +0x0c
    uint32_t mField10;                     // +0x10
    uint32_t mField14;                     // +0x14
    uint32_t mField18;                     // +0x18
    uint32_t mField1c;                     // +0x1c
};

PoolNodeX* FUN_008f2550(PoolX* pool, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
PoolNodeX* FUN_008f25f0(PoolX* pool, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);

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

// @ 0x008F16C0
void TableRow::Dispose()
{
    FUN_011e0744(mCells.mpBegin, mCells.mpEnd, 0);
    const int count = (int)((char*)mCells.mpEnd - (char*)mCells.mpBegin) >> 2;
    mCells.mpEnd = (TableCell**)((char*)mCells.mpEnd - count * 4);
    ((Item*)this)->Dispose();
}

// @ 0x008F1850
void Table::Dispose()
{
    FUN_00951bf0(mCols.mpEnd, mCols.mpEnd, mCols.mpBegin);
    const int colCount = (int)((char*)mCols.mpEnd - (char*)mCols.mpBegin) / 0x14;
    mCols.mpEnd = (TableColumn*)((char*)mCols.mpEnd - colCount * 0x14);
    FUN_011e0744(mRows.mpBegin, mRows.mpEnd, 0);
    const int rowCount = (int)((char*)mRows.mpEnd - (char*)mRows.mpBegin) >> 2;
    mRows.mpEnd = (TableRow**)((char*)mRows.mpEnd - rowCount * 4);
    ((Item*)this)->Dispose();
}

// @ 0x008F18C0
template <typename T>
void Vector<T>::resize(uint32_t n)
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

template void Vector<TableColumn>::resize(uint32_t n);

// @ 0x008F2350
void TextItemX::F_8f2350(void* owner, void* styleArg)
{
    if (mLength > 0) {
        mTextStyle = mpPage->GetTextStyle(styleArg);
        ((StyleOwner*)owner)->ApplyStyleA(mpStyle, mLength, mTextStyle);
    }
}

// @ 0x008F2380
void TextItemX::F_8f2380(void* owner, void* styleArg)
{
    if (mLength > 0) {
        mTextStyle = mpPage->GetTextStyle(styleArg);
        ((StyleOwner*)owner)->ApplyStyleB(mpStyle, mLength, mTextStyle);
    }
}

// @ 0x008F23B0
void TextItemX::F_8f23b0(void* owner)
{
    if (mLength > 0)
        ((PickCtxX*)owner)->PickTextB(this, mTextStyle);
}

// @ 0x008F23D0
bool TextItemX::F_8f23d0(void* owner, void* unused)
{
    if (mLength > 0)
        ((PickCtxX*)owner)->PickTextA(this, mTextStyle);
    return false;
}

// @ 0x008F2440
PropNodeX* PropNodeX::F_8f2440(int a, const uint16_t* str)
{
    mField04 = 0;
    mVtable = 0x01439a3c;
    mField08 = (uint32_t)a;
    mField0c = (uint32_t)str;
    if (str) {
        const uint16_t* p = str + 1;
        uint16_t c;
        do {
            c = *str;
            ++str;
        } while (c != 0);
        mLength = (int)(str - p);
    } else {
        mLength = -1;
    }
    return this;
}

// @ 0x008F24A0
PropNodeX* PropNodeX::F_8f24a0(int a, const uint16_t* str)
{
    mField04 = 0;
    mVtable = 0x01439a48;
    mField08 = (uint32_t)a;
    mField0c = (uint32_t)str;
    if (str) {
        const uint16_t* p = str + 1;
        uint16_t c;
        do {
            c = *str;
            ++str;
        } while (c != 0);
        mLength = (int)(str - p);
    } else {
        mLength = -1;
    }
    return this;
}

// @ 0x008F24F0
void HeadTailX::F_8f24f0(ListNodeX* node)
{
    if (mpTail) {
        mpTail->mField4 = (uint32_t)node;
        mpTail = node;
    } else {
        mpHead = node;
        mpTail = node;
    }
}

// @ 0x008F2550
PoolNodeX* FUN_008f2550(PoolX* pool, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    if ((pool->mField08 - pool->mField0c) - 0x18 < 0) {
        if (!pool->F_928ba0(0x18))
            return 0;
    }
    PoolNodeX* node = (PoolNodeX*)pool->mField0c;
    pool->mField0c = (int)((char*)node + 0x18);
    pool->mField10 = (int)((char*)node + 0x18);
    if (!node)
        return 0;
    node->mField04 = 0;
    node->mVtable = 0x01439a54;
    node->mField08 = a;
    node->mField0c = b;
    node->mField10 = c;
    node->mField14 = d;
    return node;
}

// @ 0x008F25F0
PoolNodeX* FUN_008f25f0(PoolX* pool, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e)
{
    if ((pool->mField08 - pool->mField0c) - 0x20 < 0) {
        if (!pool->F_928ba0(0x20))
            return 0;
    }
    PoolNodeX* node = (PoolNodeX*)pool->mField0c;
    pool->mField0c = (int)((char*)node + 0x20);
    pool->mField10 = (int)((char*)node + 0x20);
    if (!node)
        return 0;
    node->mField04 = 0;
    node->mVtable = 0x01439a60;
    node->mField08 = a;
    node->mField0c = b;
    node->mField10 = c;
    node->mField14 = d;
    node->mField18 = e;
    return node;
}

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA
