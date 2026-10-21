// Slice s00970570 - EA::UTFWinControls::WinGrid (0x970570..0x970f1e, 40 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region).
//
// Retail layout: a 135-slot IWinGrid sub-object (vtable at +0, mGridFlags at +4) sits at
// WinGrid+0x20c.  Its methods run with `this` == that sub-object, so GetGridArea reaches the
// owning WinGrid through negative offsets; OnFocusChange / FUN_970c50 / SerUpdate / DoMessage run
// with `this` == WinGrid (primary vtable at +0, secondary IWindow vtable at +4).

#include "types.h"

#define PV(n) virtual void pv##n()

namespace EA {
namespace UTFWinControls {

// ---------------------------------------------------------------------------
// Small shared types
// ---------------------------------------------------------------------------

struct RectF {
    float left, top, right, bottom;
    RectF() {}
};

// Plain Win32 tagRECT; CRect::NormalizeRect (0x970c70) lives here.
struct CRect {
    int left, top, right, bottom;
    void NormalizeRect();
};

// Secondary interface sub-object of WinGrid: its vtable lives at WinGrid+4.
struct IWindow {
    PV(0);  PV(1);  PV(2);  PV(3);  PV(4);  PV(5);  PV(6);  PV(7);  PV(8);  PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30);
    virtual void SetFlag(unsigned flag, int value);        // +0x7c  slot 31
    PV(32); PV(33); PV(34); PV(35);
    virtual void Invalidate();                             // +0x90  slot 36
};

// Primary base of WinGrid (vtable at WinGrid+0); Window::SerUpdate / Window::DoMessage live here.
struct Win {
    PV(0);  PV(1);  PV(2);  PV(3);  PV(4);  PV(5);  PV(6);  PV(7);  PV(8);  PV(9);
    virtual void SerUpdate();                              // 0x009614a0
    virtual bool DoMessage(int* pMsg);                     // 0x00950bb0
};

struct IDrawableRect {
    PV(0);  PV(1);  PV(2);  PV(3);  PV(4);  PV(5);  PV(6);  PV(7);  PV(8);  PV(9);
    PV(10); PV(11); PV(12); PV(13);
    virtual RectF* GetArea();                              // +0x38  slot 14
};

struct IScrollBar {
    PV(0); PV(1); PV(2); PV(3);
    virtual IDrawableRect* GetContent();                   // +0x10  slot 4
};

// Objects handed back by GetCellExtraData / GetExtraDataObject (slot 3 accessor).
struct ICellData { PV(0); PV(1); PV(2); virtual void* GetValue(int id); };
struct IUserData { PV(0); PV(1); PV(2); virtual void* GetValue(int id); };

struct DropShadowDescriptor {
    int mMode1;                                            // +0x00
    int mMode2;                                            // +0x04
    void SetMode1(int mode);                               // 0x00830280
    void SetMode2(int mode);                               // 0x00830150
};

class WinGrid;

// ---------------------------------------------------------------------------
// IWinGrid - the grid sub-object embedded at WinGrid+0x20c
// ---------------------------------------------------------------------------
class IWinGrid { public:
    // --- 135-slot vtable; only the slots exercised by this slice are named ---
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6);
    virtual bool GetGridArea(RectF* pOut);                        // +0x01c  slot 7
    PV(8); PV(9); PV(10);
    virtual void SetGridFlag(unsigned flag, int value);           // +0x02c  slot 11
    PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27);
    PV(28); PV(29);
    virtual void ScrollCellsVertically(int nCells);               // +0x078  slot 30
    virtual void ScrollCellsHorizontally(int nCells);             // +0x07c  slot 31
    PV(32); PV(33);
    virtual void ScrollToColumn(int col);                         // +0x088  slot 34
    virtual void ScrollToRow(int row);                            // +0x08c  slot 35
    PV(36); PV(37); PV(38); PV(39); PV(40); PV(41); PV(42); PV(43); PV(44);
    virtual void ClearSelection();                                // +0x0b4  slot 45
    PV(46); PV(47); PV(48); PV(49); PV(50);
    virtual bool IsColumnWithinBounds(int col);                   // +0x0cc  slot 51
    virtual bool IsRowWithinBounds(int row);                      // +0x0d0  slot 52
    virtual bool IsCellWithinBounds(int col, int row);            // +0x0d4  slot 53
    PV(54); PV(55); PV(56); PV(57); PV(58); PV(59); PV(60); PV(61); PV(62);
    PV(63); PV(64); PV(65); PV(66); PV(67); PV(68); PV(69); PV(70); PV(71);
    PV(72); PV(73); PV(74); PV(75); PV(76); PV(77); PV(78); PV(79);
    virtual char GetColCellFormatExtra(int col, void* pOut);      // +0x140  slot 80
    virtual char GetRowCellFormatExtra(int row, void* pOut);      // +0x144  slot 81
    PV(82); PV(83); PV(84); PV(85); PV(86); PV(87); PV(88); PV(89); PV(90);
    PV(91); PV(92); PV(93); PV(94); PV(95); PV(96); PV(97); PV(98); PV(99);
    PV(100); PV(101); PV(102); PV(103); PV(104); PV(105); PV(106); PV(107);
    PV(108); PV(109); PV(110); PV(111);
    virtual void SetCellExtraData(int col, int row, void* pData); // +0x1c0  slot 112
    virtual void* GetCellExtraData(int col, int row);             // +0x1c4  slot 113

    // --- data ---
    unsigned mGridFlags;                   // +0x004
    char     mbRecalculateAllNeeded;       // +0x008
    char     _pad009[3];                   // +0x009
    int      mnRecalculationPauseCount;    // +0x00c
    RectF    mGutter;                      // +0x010
    RectF    mCellGutter;                  // +0x020
    float    mColumnHeadingHeight;         // +0x030
    float    mRowHeadingWidth;             // +0x034
    float    mUnknown038[4];               // +0x038
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
    int      mUnknown074;                  // +0x074
    int      mUnknown078;                  // +0x078
    int      mnMostRecentlyAddedColumn;    // +0x07c
    int      mnMostRecentlyAddedRow;       // +0x080
    int      mUnknown084;                  // +0x084
    char     mStopwatch[0x14];             // +0x088
    int      mExtraDataType;               // +0x09c
    int      mnSelectionRule;              // +0x0a0
    int      mnMaxSelectionCount;          // +0x0a4
    char     _pad0a8[0x144 - 0x0a8];       // +0x0a8
    int      mDefaultTextStyle;            // +0x144
    int      mDefaultTextColor[8];         // +0x148
    char     _pad168[0x19c - 0x168];       // +0x168
    int      mUnknown19c;                  // +0x19c
    char     _pad1a0[0x1e8 - 0x1a0];       // +0x1a0
    void*    mpExtraData;                  // +0x1e8
    IScrollBar* mpScrollBarVertical;       // +0x1ec
    IScrollBar* mpScrollBarHorizontal;     // +0x1f0
    char     _pad1f4[0x1fc - 0x1f4];       // +0x1f4
    int      mSoundIDs[3];                 // +0x1fc

    // --- methods (plain members here; their vtable slots are not needed by this slice) ---
    bool  GetDefaultTextStyle(int* pOut);
    bool  SetDefaultTextColor(int color, unsigned index);
    bool  GetDefaultTextColor(int* pOut, unsigned index);
    bool  GetGutters(float* a, float* b, float* c, float* d);
    bool  GetCellGutters(float* a, float* b, float* c, float* d);
    void  SetOutlineUse(int iUse, int iColor);
    int   PauseRecalculations(bool bPause);
    void  ScrollPagesVertically(int nPages);
    void  ScrollPagesHorizontally(int nPages);
    void  ScrollToCell(int col, int row);
    bool  GetSelectionRules(int* pRule, int* pMaxCount);
    bool  SetSelectionRules(int rule, int maxCount);
    void  EnableFixedRanges(bool bColumns, bool bRows);
    bool  GetCellLimits(int* pCol, int* pRow);
    bool  GetCellVisibleRange(int* pOut);
    bool  GetMostRecentlyAddedCell(int* pCol, int* pRow);
    bool  SetGridColors(int colColor, int rowColor);
    void  GetGridColors(int* pCol, int* pRow);
    bool  EnableHeadings(int bColumnHeadings, int bRowHeadings);
    bool  GetHeadingSizes(float* pColHeight, float* pRowWidth);
    bool  IsCellVisible(int col, int row);
    bool  GetFirstVisibleCell(int* pCol, int* pRow);
    bool  GetVisibleColumnAndRowCount(float* pCols, float* pRows);
    bool  GetColRowCellFormatExtra(int col, int row, void* pOut);
    bool  SetExtraData(void* pData);
    void* GetCellExtraDataObject(int col, int row, int id);
    bool  SetCellExtraDataObject(int col, int row, void* pData);
    void* GetExtraDataObject(int id);
    bool  SetExtraDataObject(void* pData);
    bool  SetSoundID(int index, int soundID);
    bool  GetCellArea(RectF* pOut);
};

// ---------------------------------------------------------------------------
// WinGrid - the owning window (primary vtable at +0, IWindow vtable at +4)
// ---------------------------------------------------------------------------
class WinGrid : public Win, public IWindow { public:
    char _pad008[0x88 - 0x08];                        // +0x008
    RectF mArea;                                      // +0x088
    char _pad098[0x20c - 0x098];                      // +0x098
    IWinGrid mGrid;                                   // +0x20c
    char _padGrid[0xa64 - 0x20c - sizeof(IWinGrid)];  // after mGrid
    DropShadowDescriptor mDropShadow;                 // +0xa64

    bool OnFocusChange(int iReason, IWindow* pWindow);
    void FUN_970c50(int value);
    void SerUpdate();
    bool DoMessage(int* pMsg);
};

} // namespace UTFWinControls
} // namespace EA

using namespace EA::UTFWinControls;

// ===========================================================================
// 0x970570 WinGrid::OnFocusChange
// ===========================================================================
// @ 0x00970570
bool WinGrid::OnFocusChange(int iReason, IWindow* pWindow)
{
    if (iReason == 0) {
        if (mGrid.mGridFlags & 1) {
            ((IWindow*)((char*)this + 4))->Invalidate();
            return true;
        }
    }
    else if (iReason == 1) {
        if (pWindow != static_cast<IWindow*>(this)) {
            mGrid.mUnknown19c = 0;
            ((IWindow*)((char*)this + 4))->Invalidate();
        }
    }
    return true;
}

// ===========================================================================
// 0x970610 IWinGrid::GetDefaultTextStyle
// ===========================================================================
// @ 0x00970610
bool IWinGrid::GetDefaultTextStyle(int* pOut)
{
    *pOut = mDefaultTextStyle;
    return true;
}

// ===========================================================================
// 0x970630 IWinGrid::SetDefaultTextColor
// ===========================================================================
// @ 0x00970630
bool IWinGrid::SetDefaultTextColor(int color, unsigned index)
{
    if (index < 8) {
        mDefaultTextColor[index] = color;
        return true;
    }
    return false;
}

// ===========================================================================
// 0x970650 IWinGrid::GetDefaultTextColor
// ===========================================================================
// @ 0x00970650
bool IWinGrid::GetDefaultTextColor(int* pOut, unsigned index)
{
    if (index < 8) {
        *pOut = mDefaultTextColor[index];
        return true;
    }
    return false;
}

// ===========================================================================
// 0x970680 IWinGrid::GetGutters
// ===========================================================================
// @ 0x00970680
bool IWinGrid::GetGutters(float* a, float* b, float* c, float* d)
{
    *a = mGutter.left;
    *b = mGutter.top;
    *c = mGutter.right;
    *d = mGutter.bottom;
    return true;
}

// ===========================================================================
// 0x9706b0 IWinGrid::GetCellGutters
// ===========================================================================
// @ 0x009706b0
bool IWinGrid::GetCellGutters(float* a, float* b, float* c, float* d)
{
    *a = mCellGutter.left;
    *b = mCellGutter.top;
    *c = mCellGutter.right;
    *d = mCellGutter.bottom;
    return true;
}

// ===========================================================================
// 0x9706e0 IWinGrid::SetOutlineUse
// ===========================================================================
// @ 0x009706e0
void IWinGrid::SetOutlineUse(int iUse, int iColor)
{
    SetGridFlag(0x200, iUse);
    mOutlineColor = iColor;
}

// ===========================================================================
// 0x970720 IWinGrid::PauseRecalculations
// ===========================================================================
// @ 0x00970720
int IWinGrid::PauseRecalculations(bool bPause)
{
    if (bPause) {
        mnRecalculationPauseCount = mnRecalculationPauseCount + 1;
        return mnRecalculationPauseCount;
    }
    mnRecalculationPauseCount = mnRecalculationPauseCount - 1;
    return mnRecalculationPauseCount;
}

// ===========================================================================
// 0x970740 IWinGrid::ScrollPagesVertically
// ===========================================================================
// @ 0x00970740
void IWinGrid::ScrollPagesVertically(int nPages)
{
    ScrollCellsVertically(nPages * 4);
}

// ===========================================================================
// 0x970760 IWinGrid::ScrollPagesHorizontally
// ===========================================================================
// @ 0x00970760
void IWinGrid::ScrollPagesHorizontally(int nPages)
{
    ScrollCellsHorizontally(nPages * 4);
}

// ===========================================================================
// 0x970780 IWinGrid::ScrollToCell
// ===========================================================================
// @ 0x00970780
void IWinGrid::ScrollToCell(int col, int row)
{
    ScrollToColumn(col);
    ScrollToRow(row);
}

// ===========================================================================
// 0x9707b0 IWinGrid::GetSelectionRules
// ===========================================================================
// @ 0x009707b0
bool IWinGrid::GetSelectionRules(int* pRule, int* pMaxCount)
{
    *pRule = mnSelectionRule;
    *pMaxCount = mnMaxSelectionCount;
    return true;
}

// ===========================================================================
// 0x9707d0 IWinGrid::SetSelectionRules
// ===========================================================================
// @ 0x009707d0
bool IWinGrid::SetSelectionRules(int rule, int maxCount)
{
    mnSelectionRule = rule;
    mnMaxSelectionCount = maxCount;
    ClearSelection();
    return true;
}

// ===========================================================================
// 0x970800 IWinGrid::EnableFixedRanges
// ===========================================================================
// @ 0x00970800
void IWinGrid::EnableFixedRanges(bool bColumns, bool bRows)
{
    if (bColumns) {
        SetGridFlag(0x2000, 1);
    }
    else {
        SetGridFlag(0x2000, 0);
        mnColumnCount = -1;
    }
    if (bRows) {
        SetGridFlag(0x4000, 1);
        return;
    }
    SetGridFlag(0x4000, 0);
    mnRowCount = -1;
}

// ===========================================================================
// 0x970860 IWinGrid::GetCellLimits
// ===========================================================================
// @ 0x00970860
bool IWinGrid::GetCellLimits(int* pCol, int* pRow)
{
    *pCol = mnColumnCount;
    *pRow = mnRowCount;
    return *pCol != -1 && *pRow != -1;
}

// ===========================================================================
// 0x970890 IWinGrid::GetCellVisibleRange
// ===========================================================================
// @ 0x00970890
bool IWinGrid::GetCellVisibleRange(int* pOut)
{
    pOut[0] = mnFirstVisibleColumn;
    pOut[1] = mnFirstVisibleRow;
    pOut[2] = mnFirstVisibleColumn + (int)mVisibleColumnCount;
    pOut[3] = mnFirstVisibleRow + (int)mVisibleRowCount;
    return true;
}

// ===========================================================================
// 0x9708c0 IWinGrid::IsColumnWithinBounds
// ===========================================================================
// @ 0x009708c0
bool IWinGrid::IsColumnWithinBounds(int col)
{
    return mnColumnCount == 0 || mnColumnCount == -1
        || (col >= 0 && col < mnColumnCount);
}

// ===========================================================================
// 0x9708f0 IWinGrid::IsRowWithinBounds
// ===========================================================================
// @ 0x009708f0
bool IWinGrid::IsRowWithinBounds(int row)
{
    return mnRowCount == 0 || mnRowCount == -1
        || (row >= 0 && row < mnRowCount);
}

// ===========================================================================
// 0x970920 IWinGrid::IsCellWithinBounds
// ===========================================================================
// @ 0x00970920
bool IWinGrid::IsCellWithinBounds(int col, int row)
{
    return IsColumnWithinBounds(col) && IsRowWithinBounds(row);
}

// ===========================================================================
// 0x970960 IWinGrid::GetMostRecentlyAddedCell
// ===========================================================================
// @ 0x00970960
bool IWinGrid::GetMostRecentlyAddedCell(int* pCol, int* pRow)
{
    *pCol = mnMostRecentlyAddedColumn;
    *pRow = mnMostRecentlyAddedRow;
    return *pCol != -1;
}

// ===========================================================================
// 0x970990 IWinGrid::SetGridColors
// ===========================================================================
// @ 0x00970990
bool IWinGrid::SetGridColors(int colColor, int rowColor)
{
    mColumnGridColor = colColor;
    mRowGridColor = rowColor;
    return true;
}

// ===========================================================================
// 0x9709b0 IWinGrid::GetGridColors
// ===========================================================================
// @ 0x009709b0
void IWinGrid::GetGridColors(int* pCol, int* pRow)
{
    *pCol = mColumnGridColor;
    *pRow = mRowGridColor;
}

// ===========================================================================
// 0x9709e0 IWinGrid::EnableHeadings
// ===========================================================================
// @ 0x009709e0
bool IWinGrid::EnableHeadings(int bColumnHeadings, int bRowHeadings)
{
    SetGridFlag(8, bColumnHeadings);
    SetGridFlag(0x10, bRowHeadings);
    return false;
}

// ===========================================================================
// 0x970a10 IWinGrid::GetHeadingSizes
// ===========================================================================
// @ 0x00970a10
bool IWinGrid::GetHeadingSizes(float* pColHeight, float* pRowWidth)
{
    *pColHeight = mColumnHeadingHeight;
    *pRowWidth = mRowHeadingWidth;
    return true;
}

// ===========================================================================
// 0x970a30 IWinGrid::IsCellVisible
// ===========================================================================
// @ 0x00970a30
bool IWinGrid::IsCellVisible(int col, int row)
{
    return col >= mnFirstVisibleColumn
        && (float)col < (float)mnFirstVisibleColumn + mVisibleColumnCount
        && row >= mnFirstVisibleRow
        && (float)row < (float)mnFirstVisibleRow + mVisibleRowCount;
}

// ===========================================================================
// 0x970a80 IWinGrid::GetFirstVisibleCell
// ===========================================================================
// @ 0x00970a80
bool IWinGrid::GetFirstVisibleCell(int* pCol, int* pRow)
{
    *pCol = mnFirstVisibleColumn;
    *pRow = mnFirstVisibleRow;
    return true;
}

// ===========================================================================
// 0x970aa0 IWinGrid::GetVisibleColumnAndRowCount
// ===========================================================================
// @ 0x00970aa0
bool IWinGrid::GetVisibleColumnAndRowCount(float* pCols, float* pRows)
{
    *pCols = mVisibleColumnCount;
    *pRows = mVisibleRowCount;
    return true;
}

// ===========================================================================
// 0x970ac0 IWinGrid::GetColRowCellFormatExtra
// ===========================================================================
// @ 0x00970ac0
bool IWinGrid::GetColRowCellFormatExtra(int col, int row, void* pOut)
{
    if (GetColCellFormatExtra(col, pOut))
        return true;
    return GetRowCellFormatExtra(row, pOut);
}

// ===========================================================================
// 0x970b10 IWinGrid::SetExtraData
// ===========================================================================
// @ 0x00970b10
bool IWinGrid::SetExtraData(void* pData)
{
    mExtraDataType = 1;
    mpExtraData = pData;
    return true;
}

// ===========================================================================
// 0x970b40 IWinGrid::GetCellExtraDataObject
// ===========================================================================
// @ 0x00970b40
void* IWinGrid::GetCellExtraDataObject(int col, int row, int id)
{
    mExtraDataType = 1;
    ICellData* pData = (ICellData*)GetCellExtraData(col, row);
    mExtraDataType = 2;
    if (pData)
        return pData->GetValue(id);
    return 0;
}

// ===========================================================================
// 0x970b90 IWinGrid::SetCellExtraDataObject
// ===========================================================================
// @ 0x00970b90
bool IWinGrid::SetCellExtraDataObject(int col, int row, void* pData)
{
    mExtraDataType = 2;
    if (IsCellWithinBounds(col, row)) {
        mExtraDataType = 1;
        SetCellExtraData(col, row, pData);
        mExtraDataType = 2;
        return true;
    }
    return false;
}

// ===========================================================================
// 0x970bf0 IWinGrid::GetExtraDataObject
// ===========================================================================
// @ 0x00970bf0
void* IWinGrid::GetExtraDataObject(int id)
{
    IUserData* pData = (IUserData*)mpExtraData;
    if (pData)
        return pData->GetValue(id);
    return 0;
}

// ===========================================================================
// 0x970c10 IWinGrid::SetExtraDataObject
// ===========================================================================
// @ 0x00970c10
bool IWinGrid::SetExtraDataObject(void* pData)
{
    mpExtraData = pData;
    mExtraDataType = 2;
    return true;
}

// ===========================================================================
// 0x970c30 IWinGrid::SetSoundID
// ===========================================================================
// @ 0x00970c30
bool IWinGrid::SetSoundID(int index, int soundID)
{
    if (index < 3) {
        mSoundIDs[index] = soundID;
        return true;
    }
    return false;
}

// ===========================================================================
// 0x970c50 WinGrid::FUN_970c50
// ===========================================================================
// @ 0x00970c50
void WinGrid::FUN_970c50(int value)
{
    mGrid.mbRecalculateAllNeeded = (char)value;
    ((IWindow*)((char*)this + 4))->SetFlag(8, value);
}

// ===========================================================================
// 0x970c70 CRect::NormalizeRect
// ===========================================================================
// @ 0x00970c70
void CRect::NormalizeRect()
{
    if (left > right) {
        int l = left;
        left = right;
        right = l;
    }
    if (top > bottom) {
        int t = top;
        top = bottom;
        bottom = t;
    }
}

// ===========================================================================
// 0x970d20 WinGrid::SerUpdate
// ===========================================================================
// @ 0x00970d20
void WinGrid::SerUpdate()
{
    mGrid.mbRecalculateAllNeeded = 1;
    ((IWindow*)((char*)this + 4))->SetFlag(8, 1);
    mDropShadow.SetMode1(mDropShadow.mMode1);
    mDropShadow.SetMode2(mDropShadow.mMode2);
    Win::SerUpdate();
}

// ===========================================================================
// 0x970d70 WinGrid::DoMessage
// ===========================================================================
// @ 0x00970d70
bool WinGrid::DoMessage(int* pMsg)
{
    if (pMsg[2] == (int)0x8ef0c8dd) {
        switch (pMsg[3]) {
        case 0x1a7c4510:
            if (pMsg[5] == mGrid.mnFirstVisibleColumn)
                return true;
            mGrid.mnFirstVisibleColumn = pMsg[5];
            break;
        case 0x1a7c4511:
            if (pMsg[5] == mGrid.mnFirstVisibleRow)
                return true;
            mGrid.mnFirstVisibleRow = pMsg[5];
            break;
        default:
            return true;
        }
        mGrid.mbRecalculateAllNeeded = 1;
        ((IWindow*)((char*)this + 4))->SetFlag(8, 1);
        return true;
    }
    return Win::DoMessage(pMsg);
}

// ===========================================================================
// 0x970de0 IWinGrid::GetGridArea
// ===========================================================================
// @ 0x00970de0
bool IWinGrid::GetGridArea(RectF* pOut)
{
    WinGrid* pGrid = (WinGrid*)((char*)this - 0x20c);
    pOut->left = mGutter.left;
    pOut->top = mGutter.top;
    pOut->right = pGrid->mArea.right - pGrid->mArea.left - mGutter.right;
    pOut->bottom = pGrid->mArea.bottom - pGrid->mArea.top - mGutter.bottom;
    return pOut->right - pOut->left > 1.1920929e-07f
        && pOut->bottom - pOut->top > 1.1920929e-07f;
}

// ===========================================================================
// 0x970e50 IWinGrid::GetCellArea
// ===========================================================================
// @ 0x00970e50
bool IWinGrid::GetCellArea(RectF* pOut)
{
    GetGridArea(pOut);
    if (mGridFlags & 8)
        pOut->top += mColumnHeadingHeight;
    if (mGridFlags & 0x10)
        pOut->left += mRowHeadingWidth;
    IScrollBar* pBarVert = mpScrollBarVertical;
    if (pBarVert) {
        IDrawableRect* pDrawable = pBarVert->GetContent();
        RectF* pArea = pDrawable->GetArea();
        pOut->right -= (pArea->right - pArea->left);
    }
    IScrollBar* pBarHorz = mpScrollBarHorizontal;
    if (pBarHorz) {
        IDrawableRect* pDrawable = pBarHorz->GetContent();
        RectF* pArea = pDrawable->GetArea();
        pOut->bottom -= (pArea->bottom - pArea->top);
    }
    return pOut->right - pOut->left > 1.1920929e-07f
        && pOut->bottom - pOut->top > 1.1920929e-07f;
}
