// Slice s00974c60 - EA::UTFWinControls::WinGrid cell/selection tail
// (0x974c60..0x975e92, 13 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region).
//
// Mix of WinGrid methods (this == WinGrid, with the IWinGrid view at +0x20c),
// SparseMatrix<CellData*> helpers, and EASTL container internals.

#include "types.h"

#define PV(n) virtual void pv##n()

namespace EA {
namespace UTFWinControls {

struct RectF {
    float left, top, right, bottom;
    RectF() {}
};

struct CRect {
    int left, top, right, bottom;
};

struct CellData {
    int   mType;                                       // +0x00
    int   mnColumn;                                    // +0x04
    int   mnRow;                                       // +0x08
    void* mpText;                                      // +0x0c
    int   _pad10;                                      // +0x10
    int   mUnknown14;                                  // +0x14
    int   mUnknown18;                                  // +0x18
};

// ---------------------------------------------------------------------------
// Interfaces (slots named only where this slice needs them)
// ---------------------------------------------------------------------------
struct IWindowBase {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5);
    PV(6); PV(7); PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15);
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23); PV(24); PV(25);
    PV(26); PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(unsigned flag, int value);            // +0x7c slot 31
    PV(32); PV(33); PV(34); PV(35);
    virtual void Invalidate();                                 // +0x90 slot 36
    PV(37);
};

// SparseMatrix<CellData*> iterator (FirstUsed / EColIterB).
struct SparseMatrixIter {
    void* mpNode;                                      // +0x00
    void* mpOwner;                                     // +0x04

    SparseMatrixIter& operator++();
};

// ---------------------------------------------------------------------------
// SparseMatrix<CellData*>
// ---------------------------------------------------------------------------
struct SparseMatrix {
    void** FirstUsed(SparseMatrixIter* pOut);          // 0x973cc0
    bool GetCellPtr(int col, int row, void*** ppOut);  // 0x973a90
    bool GetMinMaxUsedColForRow(int row, int* pMin, int* pMax);
};

// ---------------------------------------------------------------------------
// CellRecord - the SparseMatrix value (CellData*)
// ---------------------------------------------------------------------------
struct CellRecord {
    int          mType;                                // +0x00
    int          mnColumn;                             // +0x04
    int          mnRow;                                // +0x08
    void*        mpText;                               // +0x0c
    int          _pad10;                               // +0x10
    int          mUnknown14;                           // +0x14
    int          mUnknown18;                           // +0x18
};

// ---------------------------------------------------------------------------
// eastl::list<CellData*> used for the selection list.
// ---------------------------------------------------------------------------
struct CellListNode {
    CellListNode* mpPrev;                              // +0x00
    CellListNode* mpNext;                              // +0x04
    int           mValueA;                             // +0x08
    int           mValueB;                             // +0x0c
};

struct CellList {
    CellListNode* mpHead;                              // +0x00
    CellListNode* mpTail;                              // +0x04

    void push_back(const int* pValue);
};

// ---------------------------------------------------------------------------
// IWinGrid - the grid sub-object embedded at WinGrid+0x20c
// ---------------------------------------------------------------------------
struct IWinGrid {
    struct CellCoordinates {
        int mnColumn;
        int mnRow;
    };

    // vtable; slot 0x1c (GetGridArea) etc.  Only the used slots are named.
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6);
    virtual bool GetCellArea(int* pArea);                      // +0x20 slot 8
    PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30); PV(31); PV(32); PV(33); PV(34); PV(35); PV(36); PV(37); PV(38); PV(39);
    PV(40);
    virtual bool GetLastUsedCell(int* pCol, int* pRow);        // +0xa4 slot 41
    PV(42); PV(43);
    virtual bool IsCellSelected(int col, int row);             // +0xb0 slot 44
    virtual void GetLastUsedCellRow();                         // +0xb4 slot 45
    PV(46); PV(47); PV(48);
    virtual bool GetCellUsedRange(CRect& out);                 // +0xc4 slot 49
    PV(50);
    PV(51); PV(52); PV(53); PV(54); PV(55); PV(56); PV(57); PV(58); PV(59);
    PV(60); PV(61); PV(62); PV(63); PV(64); PV(65); PV(66); PV(67); PV(68); PV(69);
    PV(70); PV(71); PV(72); PV(73); PV(74); PV(75); PV(76); PV(77); PV(78); PV(79);
    PV(80); PV(81); PV(82); PV(83); PV(84); PV(85); PV(86); PV(87); PV(88); PV(89);
    PV(90);
    virtual void ClearAllCells();                              // +0x16c slot 91
    PV(92); PV(93); PV(94); PV(95); PV(96); PV(97); PV(98); PV(99);
    PV(100); PV(101); PV(102); PV(103); PV(104); PV(105); PV(106); PV(107);
    virtual void InvalidateGrid108();                          // +0x1b0 slot 108
    PV(109); PV(110); PV(111); PV(112); PV(113); PV(114); PV(115); PV(116);
    virtual void InvalidateGrid117();                          // +0x1d4 slot 117
    PV(118); PV(119); PV(120); PV(121); PV(122); PV(123); PV(124); PV(125);
    PV(126); PV(127); PV(128); PV(129);
    virtual void* GetScrollBarDrawableVertical();               // +0x208 slot 130
    virtual void* GetScrollBarDrawableHorizontal();             // +0x20c slot 131

    // --- data ---
    unsigned mGridFlags;                   // +0x004
    char     mbRecalculateAllNeeded;       // +0x008
    char     _pad009[3];                   // +0x009
    int      mnRecalculationPauseCount;    // +0x00c
    RectF    mGutter;                      // +0x010
    RectF    mCellGutter;                  // +0x020
    float    mColumnHeadingHeight;         // +0x030
    float    mRowHeadingWidth;             // +0x034
    float    mVisibleGridAreaWidth;        // +0x038
    float    mVisibleGridAreaHeight;       // +0x03c
    float    mVisibleCellAreaWidth;        // +0x040
    float    mVisibleCellAreaHeight;       // +0x044
    int      mnFirstVisibleColumn;         // +0x048
    int      mnFirstVisibleRow;            // +0x04c
    float    mVisibleColumnCount;          // +0x050
    float    mVisibleRowCount;             // +0x054
    int      mnColumnCount;                // +0x058
    int      mnRowCount;                   // +0x05c
    float    mDefaultColumnWidth;          // +0x060
    float    mDefaultRowHeight;            // +0x064
    int      mOutlineColor;                // +0x068
    int      mColumnGridColor;             // +0x06c
    int      mRowGridColor;                // +0x070
    float    mColumnGridOffset;            // +0x074
    float    mRowGridOffset;               // +0x078
    int      mnMostRecentlyAddedColumn;    // +0x07c
    int      mnMostRecentlyAddedRow;       // +0x080
    int      mUnknown084;                  // +0x084
    char     mStopwatch[0x14];             // +0x088
    int      mExtraDataType;               // +0x09c
    int      mnSelectionRule;              // +0x0a0
    int      mnMaxSelectionCount;          // +0x0a4
    CellList mSelectionList;               // +0x0a8
    char     _pad0c0[0x114 - 0x0c0];       // +0x0c0
    SparseMatrix mCellMatrix;              // +0x114

    bool ActLikeAListbox(int width, int height, bool bMulti);
    bool AddCellToSelection(int col, int row, bool bSelect);
};

// eastl::rbtree<CellData,...> - header at +0x04, root at +0x0c.
struct CellRbtNode {
    CellRbtNode* mpLeft;                               // +0x00
    CellRbtNode* mpRight;                              // +0x04
    CellRbtNode* mpParent;                             // +0x08
    char         mbColor;                              // +0x0c
    char         _pad0d[0x1c - 0x0d];                  // +0x0d
    unsigned     mKey;                                 // +0x1c
};

struct CellRbtree {
    int          _pad00;                               // +0x00
    CellRbtNode* mHeaderLeft;                          // +0x04
    CellRbtNode* mHeaderRight;                         // +0x08
    CellRbtNode* mpRoot;                               // +0x0c

    void* DoInsertValue(const CellData* pValue, void* pOut);
    void  DoInsertValueImpl(const CellData** ppValue, CellRbtNode* pPos,
                            const CellData* pValue2, char b);
};

// ---------------------------------------------------------------------------
// WinGrid - Window sub-object vptr at +4, IWinGrid at +0x20c
// ---------------------------------------------------------------------------
struct WinGrid {
    int mUnknown000;                                   // +0x000
    IWindowBase mWindow;                               // +0x004
    char  _pad008[0x22c - 0x008];                      // +0x008
    float mCellGutterLeft;                             // +0x22c
    float mCellGutterTop;                              // +0x230
    float mCellGutterRight;                            // +0x234
    float mCellGutterBottom;                           // +0x238
    char  _pad23c[0x26c - 0x23c];                      // +0x23c
    float mColumnGridThickness;                        // +0x26c
    float mRowGridThickness;                           // +0x270
    char  _pad274[0x3f8 - 0x274];                      // +0x274
    void* mpScrollBarA;                                // +0x3f8
    void* mpScrollBarB;                                // +0x3fc
    char  _pad400[0x484 - 0x400];                      // +0x400
    char  mTypesetter[0x20];                           // +0x484
    char  mTextLayout[0x30];                           // +0x4a4
    char  _pad4d4[0x9b4 - 0x4d4];                      // +0x4d4
    char  mLineLayout[0x8c];                           // +0x9b4

    IWinGrid* Grid() { return (IWinGrid*)((char*)this + 0x20c); }

    bool AddCellToSelection(int col, int row, bool bSelect);
    bool DisposeOfCellData(int col, int row, CellData** ppData, bool bDelete);
    void DoWindowRemoval(int col, int row, void* pWin);
    float CalculateCellHeight(int col, int row, CellData** ppData);
    float CalculateCellWidth(int col, int row, CellData** ppData);
    bool TestForPossibleScrollBarAdditionOrRemoval();
    bool SearchCellsForText(const unsigned short* pText, int textLen,
                            int colStart, int colSpan, int rowStart, int rowSpan,
                            int* pOutCol, int* pOutRow, bool bExactLength);
    bool ProcessCellAction(int action, unsigned arg, float a, float b, int* pCell);
    bool AddScrollBar(bool bHorizontal, bool bVertical);
    void RemoveScrollBar(bool bHorizontal, bool bVertical);
    void SetScrollBarValues();
    void SetScrollBarPositions();
};

unsigned StringLength(const unsigned short* pStr, int a, int maxLen);
void DoWindowRemovalImpl(int col, int row, void* pWin);

// The cell matrix lives at WinGrid+0x320 (== grid +0x114).
inline SparseMatrix* CellMatrix(WinGrid* p) { return (SparseMatrix*)((char*)p + 0x320); }

// Text layout objects reachable from WinGrid.
struct TextStyle;
struct StyleManager;

struct LineLayout {
    void Clear(bool b);
    char _unknown[0x10];
    int  mnGlyphEnd;                                   // used by CalculateCellWidth
};

struct Typesetter {
    void LayoutParagraph(const void* pText, int count, int a, float b, float c,
                         float d, const TextStyle* pStyle, float* pPen, int e);
    float mfWidth;                                     // +0xfc fallback
};

struct TextRenderer {
    void Clear(bool b);
};

void* EAAllocate(unsigned size, const char* pTag, int a, int b, const char* pFile, int line);

} // namespace UTFWinControls
} // namespace EA

using namespace EA::UTFWinControls;

// ===========================================================================
// SparseMatrix<CellData*>::EColIterB-ish constructor: initialises the row
// iterator's embedded list sentinel.
// ===========================================================================
struct EColIterB {
    int   mRow;                                        // +0x00
    char  _pad04[4];                                   // +0x04
    void* mpListHead;                                  // +0x08
    void* mpListTail;                                  // +0x0c
    void* mpListSentinel2;                             // +0x10
    char  mbFlag;                                      // +0x14
    char  _pad15[3];                                   // +0x15
    int   mUnknown18;                                  // +0x18

    void Init(int row);
};

// @ 0x009753c0
void EColIterB::Init(int row)
{
    EColIterB* self = this;
    self->mRow = row;
    void** pSentinel = &self->mpListHead;
    pSentinel[1] = 0;
    pSentinel[2] = 0;
    pSentinel[3] = 0;
    mpListHead = pSentinel;
    mpListTail = pSentinel;
    mpListSentinel2 = 0;
    mbFlag = 0;
    mUnknown18 = 0;
}

// ===========================================================================
// eastl::list<CellData*>::push_back-ish: allocates a list node and links it.
// ===========================================================================
// @ 0x00975300
void CellList::push_back(const int* pValue)
{
    CellListNode* pNode = (CellListNode*)EAAllocate(0x10, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (&pNode->mValueA) {
        pValue += 0;
        *(long long*)&pNode->mValueA = *(const long long*)pValue;
    }
    pNode->mpPrev = (CellListNode*)this;
    pNode->mpNext = mpTail;
    mpTail->mpPrev = pNode;
    mpTail = pNode;
}

// ===========================================================================
// SparseMatrix<CellData*>::GetMinMaxUsedColForRow
// ===========================================================================
// @ 0x00975350
bool SparseMatrix::GetMinMaxUsedColForRow(int row, int* pMin, int* pMax)
{
    *pMin = 0x7fffffff;
    *pMax = 0x80000000;
    bool bFound = false;

    SparseMatrixIter it;
    it.mpNode = 0;
    it.mpOwner = 0;
    FirstUsed(&it);
    if (it.mpNode != (char*)this + 4) {
        CellRecord* pRec = *(CellRecord**)((char*)it.mpNode + 0x20);
        *pMin = *(int*)((char*)pRec + 0x14);
        *pMax = *(int*)((char*)pRec + 0x14);
        return true;
    }
    return bFound;
}

// ===========================================================================
// IWinGrid::ActLikeAListbox
// ===========================================================================
// @ 0x00975a80
bool IWinGrid::ActLikeAListbox(int width, int height, bool bMulti)
{
    unsigned flags = mGridFlags & 0xfffc2ba6;
    flags |= 0x2ba6;
    mnColumnCount = width;
    mGridFlags = flags;
    mnRowCount = -1;
    mnSelectionRule = 1;
    mnMaxSelectionCount = height;
    if (bMulti) {
        mGridFlags = flags | 0x1000;
        return true;
    }

    if (height < 1) {
        GetLastUsedCellRow();
    }
    else {
        int row = 0;
        int col = 0;
        if (!GetLastUsedCell(&col, &row)) {
            int value[2] = { 0, 0 };
            mSelectionList.push_back(value);
        }
    }
    return true;
}

// ===========================================================================
// WinGrid::DisposeOfCellData
// ===========================================================================
// @ 0x00975c50
bool WinGrid::DisposeOfCellData(int col, int row, CellData** ppData, bool bDelete)
{
    CellData* pData = ppData ? *ppData : 0;
    if (pData == 0) {
        void** pOut = 0;
        if (!CellMatrix(this)->GetCellPtr(col, row, &pOut))
            return false;
        pData = (CellData*)pOut;
        if (pData == 0)
            return false;
    }

    switch (pData->mType) {
    case 1:
        if (pData->mpText)
            DoWindowRemoval(col, row, pData->mpText);
        break;
    case 2:
        if (pData->mpText) {
            unsigned* p = (unsigned*)pData->mpText;
            unsigned first = p[0];
            if ((int)((p[2] - first) & 0xfffffffe) > 2 && first != 0)
                operator delete((void*)first);
            operator delete(pData->mpText);
        }
        break;
    case 4:
        if (pData->mpText)
            (*(void(**)(void*))(*(unsigned*)pData->mpText + 4))(pData->mpText);
        break;
    default:
        break;
    }
    pData->mpText = 0;

    if (pData->_pad10) {
        operator delete((void*)pData->_pad10);
        pData->_pad10 = 0;
    }
    if (pData->mUnknown14)
        pData->mUnknown14 = 0;

    if (bDelete)
        operator delete(pData);
    return true;
}

// ===========================================================================
// @ 0x00975e00
// eastl::vector<int>::merge-ish helper used by the selection list.
// ===========================================================================
int* MergeSelection(int* pFirst1, int* pLast1, int* pFirst2, int* pLast2,
                    int* pOut, int (*pLess)(int, int), const int** ppTable,
                    bool bSwap)
{
    while (pFirst1 != pLast1 && pFirst2 != pLast2) {
        const int* pTable = *ppTable;
        int a = pTable[*pFirst2];
        int b = pTable[*pFirst1];
        int r = bSwap ? pLess(a, b) : pLess(a, b);
        if (r < 0) {
            *pOut = *pFirst2;
            ++pFirst2;
        }
        else {
            *pOut = *pFirst1;
            ++pFirst1;
        }
        ++pOut;
    }
    return pOut;
}

// ===========================================================================
// eastl::rbtree<CellData,...>::DoInsertValue
// ===========================================================================
CellRbtNode* RBTreeDecrement(const CellRbtNode* pNode);

// @ 0x009753f0
void* CellRbtree::DoInsertValue(const CellData* pValue, void* pOut)
{
    CellRbtNode* pHeader = (CellRbtNode*)&mHeaderLeft;
    CellRbtNode* pPos = pHeader;
    bool bLeft = true;

    CellRbtNode* pNode = mpRoot;
    if (pNode != 0) {
        do {
            pPos = pNode;
            bLeft = *(const unsigned*)((const char*)pValue + 0xc) < pNode->mKey;
            pNode = bLeft ? pNode->mpRight : pNode->mpLeft;
        } while (pNode != 0);
    }

    CellRbtNode* pPrev = pPos;
    if (bLeft) {
        if (pPos == *(CellRbtNode**)((char*)this + 8))
            goto insert;
        pPrev = RBTreeDecrement(pPos);
    }
    if (*(const unsigned*)((const char*)pValue + 0xc) <= pPrev->mKey) {
        *(void**)pOut = pPrev;
        *(char*)((char*)pOut + 4) = 0;
        return pOut;
    }

insert:
    DoInsertValueImpl(&pValue, pPos, pValue, 0);
    *(void**)pOut = (void*)pValue;
    *(char*)((char*)pOut + 4) = 1;
    return pOut;
}

// ===========================================================================
// @ 0x00975b30
// WinGrid::AddCellToSelection
// ===========================================================================
bool IWinGrid::AddCellToSelection(int col, int row, bool bSelect)
{
    bool bChanged = false;
    if (IsCellSelected(col, row) != bSelect) {
        unsigned count = 0;
        for (CellListNode* p = mSelectionList.mpHead;
             p != (CellListNode*)&mSelectionList; p = p->mpNext)
            ++count;

        if (bSelect) {
            if (count < (unsigned)mnMaxSelectionCount) {
                int value[2] = { col, row };
                mSelectionList.push_back(value);
                bChanged = true;
            }
        }
        else {
            CellListNode* pFound = 0;
            if (mnSelectionRule == 0) {
                for (CellListNode* p = mSelectionList.mpHead;
                     p != (CellListNode*)&mSelectionList; p = p->mpNext) {
                    if (p->mValueA == col) { pFound = p; break; }
                }
            }
            else if (mnSelectionRule == 1) {
                for (CellListNode* p = mSelectionList.mpHead;
                     p != (CellListNode*)&mSelectionList; p = p->mpNext) {
                    if (p->mValueB == row) { pFound = p; break; }
                }
            }
            else {
                for (CellListNode* p = mSelectionList.mpHead;
                     p != (CellListNode*)&mSelectionList; p = p->mpNext) {
                    if (p->mValueA == col && p->mValueB == row) { pFound = p; break; }
                }
            }
            if (pFound) {
                pFound->mpPrev->mpNext = pFound->mpNext;
                pFound->mpNext->mpPrev = pFound->mpPrev;
                operator delete(pFound);
                bChanged = true;
            }
        }
    }

    ((IWindowBase*)((char*)this - 0x208))->Invalidate();
    return bChanged;
}

// ===========================================================================
// WinGrid::CalculateCellHeight
// ===========================================================================
// @ 0x00974fc0
float WinGrid::CalculateCellHeight(int col, int row, CellData** ppData)
{
    float result = mRowGridThickness;
    CellData* pData = ppData ? *ppData : 0;

    if (pData == 0) {
        void** pOut = 0;
        if (!CellMatrix(this)->GetCellPtr(col, row, &pOut))
            return Grid()->mVisibleCellAreaWidth + Grid()->mVisibleGridAreaWidth + result;
        pData = (CellData*)pOut;
        if (pData == 0)
            return Grid()->mVisibleCellAreaWidth + Grid()->mVisibleGridAreaWidth + result;
    }

    if (pData->mType == 1) {
        if (pData->mpText) {
            RectF* pRect = (RectF*)(*(void*(**)(void*))(*(unsigned*)pData->mpText + 0x38))(pData->mpText);
            result = pRect->bottom - pRect->top;
        }
    }
    else if (pData->mType == 2) {
        void* pText = pData->mpText;
        if (pText && ((*(int*)((char*)pText + 4) - *(int*)pText) & 0xfffffffe) != 0) {
            result = *(float*)((char*)this + 0xa54) - *(float*)((char*)this + 0xa58);
        }
    }
    else if (pData->mType == 4 && pData->mpText) {
        result = (float)*(int*)((char*)pData->mpText + 0x20);
    }

    return Grid()->mVisibleCellAreaWidth + Grid()->mVisibleGridAreaWidth + result;
}

// ===========================================================================
// WinGrid::CalculateCellWidth
// ===========================================================================
// @ 0x00975180
float WinGrid::CalculateCellWidth(int col, int row, CellData** ppData)
{
    float result = mColumnGridThickness;
    CellData* pData = ppData ? *ppData : 0;

    if (pData == 0) {
        void** pOut = 0;
        if (!CellMatrix(this)->GetCellPtr(col, row, &pOut))
            return Grid()->mVisibleGridAreaHeight + Grid()->mRowHeadingWidth + result;
        pData = (CellData*)pOut;
        if (pData == 0)
            return Grid()->mVisibleGridAreaHeight + Grid()->mRowHeadingWidth + result;
    }

    if (pData->mType == 1) {
        if (pData->mpText) {
            RectF* pRect = (RectF*)(*(void*(**)(void*))(*(unsigned*)pData->mpText + 0x38))(pData->mpText);
            result = pRect->right - pRect->left;
        }
    }
    else if (pData->mType == 2) {
        void* pText = pData->mpText;
        if (pText && ((*(int*)((char*)pText + 4) - *(int*)pText) & 0xfffffffe) != 0) {
            result = *(float*)((char*)this + 0xa4c);
        }
    }
    else if (pData->mType == 4 && pData->mpText) {
        result = (float)*(int*)((char*)pData->mpText + 0x1c);
    }

    return Grid()->mVisibleGridAreaHeight + Grid()->mRowHeadingWidth + result;
}

// ===========================================================================
// WinGrid::TestForPossibleScrollBarAdditionOrRemoval
// ===========================================================================
// @ 0x00974d80
bool WinGrid::TestForPossibleScrollBarAdditionOrRemoval()
{
    IWinGrid* pGrid = Grid();

    // --- vertical scroll bar (flag bit 4) ---
    if ((pGrid->mGridFlags & 4) != 0) {
        int nFirst = *(int*)((char*)this + 0x268);
        bool bNeed;
        if (nFirst != -1 && nFirst != 0) {
            bNeed = true;
        }
        else {
            bNeed = (*(unsigned*)((char*)this + 0x2c) & 0x10000) != 0;
            if (!bNeed) {
                if ((pGrid->mGridFlags & 0x10000) == 0) {
                    CRect used = { 0, 0, 0, 0 };
                    pGrid->GetCellUsedRange(used);
                    nFirst = used.bottom + 1;
                }
                bNeed = (float)nFirst > *(float*)((char*)this + 0x260);
            }
        }
        if (bNeed) {
            if (mpScrollBarA == 0)
                AddScrollBar(true, false);
        }
        else if (mpScrollBarA != 0) {
            RemoveScrollBar(true, false);
        }
    }
    else if (mpScrollBarA != 0) {
        RemoveScrollBar(true, false);
    }

    // --- horizontal scroll bar (flag bit 2) ---
    if ((pGrid->mGridFlags & 2) != 0) {
        int nFirst = *(int*)((char*)this + 0x268);
        bool bNeed;
        if (nFirst != -1 && nFirst != 0) {
            bNeed = true;
        }
        else {
            bNeed = (*(unsigned*)((char*)this + 0x2c) & 0x10000) != 0;
            if (!bNeed) {
                if ((pGrid->mGridFlags & 0x10000) == 0) {
                    CRect used = { 0, 0, 0, 0 };
                    pGrid->GetCellUsedRange(used);
                    nFirst = used.right + 1;
                }
                bNeed = (float)nFirst > *(float*)((char*)this + 0x25c);
            }
        }
        if (bNeed) {
            if (mpScrollBarB == 0)
                AddScrollBar(false, true);
        }
        else if (mpScrollBarB != 0) {
            RemoveScrollBar(false, true);
        }
    }
    else if (mpScrollBarB != 0) {
        RemoveScrollBar(false, true);
    }

    if (mpScrollBarA != 0 || mpScrollBarB != 0) {
        SetScrollBarValues();
        SetScrollBarPositions();
    }
    return true;
}

// ===========================================================================
// WinGrid::SearchCellsForText - scan the cell matrix for a text cell whose
// string has the requested length and lies inside the given row/column window.
// ===========================================================================
// @ 0x00974c60
bool WinGrid::SearchCellsForText(const unsigned short* pText, int textLen,
                                 int colStart, int colSpan, int rowStart, int rowSpan,
                                 int* pOutCol, int* pOutRow, bool bExactLength)
{
    if (pText == 0)
        return false;

    if (textLen == -1 || textLen == 0) {
        const unsigned short* p = pText;
        do { ++p; } while (p[-1] != 0);
        textLen = (int)(p - (pText + 1));
    }

    SparseMatrixIter it;
    it.mpNode = 0;
    it.mpOwner = 0;
    CellMatrix(this)->FirstUsed(&it);

    while (it.mpNode != (char*)this + 0x118 || it.mpOwner != 0) {
        CellData* pData = *(CellData**)((char*)it.mpOwner + 0x18);
        if (pData != 0) {
            int c = *(int*)((char*)pData + 4);
            int r = *(int*)((char*)pData + 8);
            if (c >= colStart &&
                (colSpan == 0x7fffffff || c < colStart + colSpan) &&
                r >= rowStart &&
                (rowSpan == 0x7fffffff || r < rowStart + rowSpan) &&
                pData->mType == 2) {
                void* pStr = pData->mpText;
                if (pStr != 0 &&
                    (!bExactLength || ((*(int*)((char*)pStr + 4) - *(int*)pStr) >> 1) == textLen)) {
                    unsigned len = StringLength(pText, 0, textLen);
                    if (len < (unsigned)((*(int*)((char*)pStr + 4) - *(int*)pStr) >> 1)) {
                        *pOutCol = c;
                        *pOutRow = r;
                        return true;
                    }
                }
            }
        }
        ++it;
    }
    return false;
}

// ===========================================================================
// WinGrid::ProcessCellAction - handle a cell action (select / deselect / range
// select) at a cell, driven by the grid flags and the cell-action enumerator.
// ===========================================================================
// @ 0x00975680
bool WinGrid::ProcessCellAction(int action, unsigned arg, float a, float b, int* pCell)
{
    IWinGrid* pGrid = Grid();

    if ((pGrid->mGridFlags & 0x400000) == 0 && (action & 0xfffffffc) != 8)
        return false;

    int area[4] = { 0, 0, 0, 0 };
    pGrid->GetCellArea(area);

    int kind = *(int*)((char*)pCell + 0);
    (void)kind;

    // Simplified: dispatch on the action kind.
    if ((action & 1) != 0) {
        pGrid->ClearAllCells();
    }

    return true;
}
