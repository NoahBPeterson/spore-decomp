// Slice s00971eb0 - EA::UTFWinControls::WinGrid (0x971eb0..0x972e25, 14 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region).
//
// The IWinGrid virtuals run with `this` == the grid sub-object at WinGrid+0x20c,
// so the owning window is reached through a negative offset.  The scroll-bar and
// layout helpers are plain WinGrid methods (this == WinGrid).

#include "types.h"
#include <math.h>

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

// Cell format record consumed/produced by GetCellFormat (slot +0x134).  Only the
// fields this slice touches are named; the rest is padding.
struct CellFormat {
    char  mUnknown00[0x0c];
    int   mUnknown0c;                                  // +0x0c
    int   mUnknown10;                                  // +0x10
    int   mUnknown14;                                  // +0x14
    int   mUnknown18;                                  // +0x18
    int   mUnknown1c;                                  // +0x1c
    int   mUnknown20;                                  // +0x20
    char  mUnknown24;                                  // +0x24
    char  mAlignH;                                     // +0x25
    char  mAlignV;                                     // +0x26
    char  mUnknown27;                                  // +0x27
    int   mUnknown28;                                  // +0x28
    int   mUnknown2c;                                  // +0x2c
    int   mUnknown30;                                  // +0x30
    int   mUnknown34;                                  // +0x34
    int   mUnknown38;                                  // +0x38
};

struct IScrollbarDrawable;

// ---------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------
struct IWindowBase {
    PV(0); PV(1); PV(2);
    virtual bool GetVisible();                                // +0x10 slot 4
    PV(5); PV(6); PV(7); PV(8);
    virtual RectF* GetArea();                                 // +0x38 slot 14
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual void SetArea(const RectF* pRect);                 // +0x60 slot 24
    PV(25); PV(26); PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(unsigned flag, int value);           // +0x7c slot 31
};

// A scroll-bar drawable: GetDrawable() returns the concrete drawable, whose
// GetDrawableByType() hands back the part we want.
struct IScrollbarDrawable {
    PV(0); PV(1); PV(2);
    virtual IScrollbarDrawable* GetDrawableByType(unsigned type); // +0x0c slot 3
    PV(4); PV(5); PV(6); PV(7); PV(8); PV(9); PV(10); PV(11); PV(12); PV(13);
    virtual RectF* GetRect();                                     // +0x38 slot 14
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual void SetRect(const RectF* pRect);                     // +0x60 slot 24
};

struct ScrollBarBase {
    PV(0);
    virtual void Release();                                    // +0x04 slot 1
    PV(2);
    virtual IScrollbarDrawable* GetDrawableByType(unsigned t);// +0x0c slot 3
    virtual void* GetWindow();                                 // +0x10 slot 4
    PV(5); PV(6); PV(7); PV(8);
    virtual void SetValue(int v, bool notify);                 // +0x24 slot 9
    PV(10);
    virtual void SetMinimumValue(int v, bool notify);          // +0x2c slot 11
    PV(12);
    virtual void SetMaximumValue(int v, bool notify);          // +0x34 slot 13
    PV(14);
    virtual void SetVisibleRange(int v, bool notify);          // +0x3c slot 15
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual IScrollbarDrawable* GetDrawable();                 // +0x60 slot 24
};

// A cell/child window placed by PlaceCellWindow: only the slots used here.
struct ICellWindow {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13);
    virtual RectF* GetArea();                                  // +0x38 slot 14
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual void SetArea(const RectF* pRect);                  // +0x60 slot 24
    PV(25); PV(26); PV(27); PV(28); PV(29); PV(30);
    virtual void SetVisible(bool bVisible, int flag);          // +0x7c slot 31
};

// The owning window base reached as (grid `this`) - 0x208.  Only the slots used
// by AutoSize / PlaceCellWindow / RemoveScrollBar are named.
struct WindowBase {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15);
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23); PV(24); PV(25);
    virtual void SetSize(float w, float h);                    // +0x68 slot 26
    PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(unsigned flag, int value);            // +0x7c slot 31
    PV(32); PV(33); PV(34); PV(35);
    virtual void Invalidate();                                 // +0x90 slot 36
    PV(37); PV(38); PV(39);
    PV(40); PV(41); PV(42); PV(43); PV(44); PV(45); PV(46); PV(47);
    PV(48); PV(49); PV(50); PV(51); PV(52); PV(53); PV(54); PV(55);
    virtual void RemoveChild(ICellWindow* pChild);             // +0xe0 slot 56
};

// ---------------------------------------------------------------------------
// IWinGrid - the grid sub-object embedded at WinGrid+0x20c
// ---------------------------------------------------------------------------
struct IWinGrid {
    struct CellCoordinates {
        int mnColumn;                                     // +0x00
        int mnRow;                                        // +0x04
    };

    struct CellData {
        int mnColumn;                                     // +0x00
        int mnRow;                                        // +0x04
        int mUnknown08;                                   // +0x08
        int _pad0c;                                       // +0x0c
        int mSortKey;                                     // +0x10
        int _pad14;                                       // +0x14
        char _pad18[0x1c - 0x18];                         // +0x18
        unsigned mKey;                                    // +0x1c
    };

    struct SelNode {
        SelNode* mpNext;                                  // +0x00
        SelNode* mpPrev;                                  // +0x04
        int      mnColumn;                                // +0x08
        int      mnRow;                                   // +0x0c
    };

    // --- vtable; only the slots exercised by this slice are named ---
    // slot N lives at byte offset N*4.
    PV(0); PV(1); PV(2); PV(3); PV(4);
    virtual bool IsReady();                                   // +0x014 slot 5
    PV(6);
    virtual bool GetGridArea(RectF& pOut);                    // +0x01c slot 7
    virtual bool GetCellArea(RectF& pOut);                    // +0x020 slot 8
    PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17);
    PV(18); PV(19); PV(20); PV(21); PV(22); PV(23); PV(24); PV(25);
    virtual void SetColumnLimits(int a, int b, float c, float d); // +0x068 slot 26
    PV(27); PV(28); PV(29); PV(30); PV(31); PV(32); PV(33); PV(34); PV(35);
    PV(36); PV(37); PV(38); PV(39); PV(40); PV(41); PV(42); PV(43); PV(44);
    virtual void InvalidateGrid45();                          // +0x0b4 slot 45
    PV(46); PV(47); PV(48);
    virtual bool GetCellUsedRange(CRect& out);                // +0x0c4 slot 49
    PV(50); PV(51); PV(52); PV(53); PV(54); PV(55); PV(56); PV(57);
    virtual void SetColumnWidth(int col, int mode, float w);  // +0x0e8 slot 58
    PV(59);
    virtual void SetRowHeight(int row, int mode, float h);    // +0x0f0 slot 60
    PV(61); PV(62);
    virtual void SetColumnCount(int n, int grow);             // +0x0fc slot 63
    virtual void SetRowCount(int n, int grow);                // +0x100 slot 64
    PV(65); PV(66); PV(67); PV(68); PV(69);
    virtual void SetHeadingFormat(const void* pFormat);       // +0x11c slot 71
    PV(71); PV(72); PV(73); PV(74); PV(75); PV(76);
    virtual void GetCellFormat(int col, int row, CellFormat* pOut); // +0x134 slot 77
    PV(78); PV(79);
    PV(80); PV(81); PV(82); PV(83); PV(84); PV(85); PV(86); PV(87); PV(88);
    virtual void SetCellData(int col, int row, const void* p); // +0x164 slot 89
    virtual bool ClearCellRect(int col, int row, int w, int h); // +0x168 slot 90
    virtual bool ClearAllCells();                             // +0x16c slot 91
    PV(92); PV(93); PV(94); PV(95); PV(96); PV(97); PV(98);
    virtual bool GetCellRect(int col, int row, RectF& out);   // +0x18c slot 99
    PV(100);
    virtual bool SetFirstVisibleCell(int col, int row);       // +0x194 slot 101
    PV(102); PV(103); PV(104); PV(105); PV(106); PV(107);
    PV(108); PV(109); PV(110); PV(111); PV(112); PV(113); PV(114); PV(115);
    PV(116); PV(117); PV(118); PV(119); PV(120); PV(121); PV(122); PV(123);
    PV(124); PV(125); PV(126); PV(127); PV(128); PV(129);
    virtual IScrollbarDrawable* GetScrollBarDrawableVertical();   // +0x208 slot 130
    virtual IScrollbarDrawable* GetScrollBarDrawableHorizontal(); // +0x20c slot 131

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
    SelNode  mSelectionList;               // +0x0a8
    char     _pad0b8[0x144 - 0x0b8];       // +0x0b8
    int      mDefaultTextStyle;            // +0x144
    int      mDefaultTextColor[8];         // +0x148
    char     _pad168[1];                   // +0x168
    char     mAlign169;                    // +0x169
    char     mAlign16a;                    // +0x16a
    char     _pad16b[0x1e8 - 0x16b];       // +0x16b
    void*    mpExtraData;                  // +0x1e8
    ScrollBarBase* mpScrollBarA;           // +0x1ec
    ScrollBarBase* mpScrollBarB;           // +0x1f0
    IScrollbarDrawable* mpScrollBarFallback; // +0x1f4
    IScrollbarDrawable* mpScrollBarFallbackH;// +0x1f8
    char     _pad1fc[0x208 - 0x1fc];       // +0x1fc

    // --- cell layout helpers (this slice) ---
    void AutoSize(unsigned int w, unsigned int h, float a, float b);
};

// ---------------------------------------------------------------------------
// The owning window / concrete WinGrid.  WinGrid's Window sub-object sits at
// +4 (its vptr is at +4), and the IWinGrid sub-object at +0x20c.
// ---------------------------------------------------------------------------
struct WinGrid {
    int mUnknown000;                                   // +0x000
    WindowBase mWindow;                                // +0x004  (vptr at +4)
    char  _pad008[0x214 - 0x008];                      // +0x008
    char  mbPendingUpdate;                             // +0x214
    char  _pad22c[0x22c - 0x215];                      // +0x215
    float mCellGutterLeft;                             // +0x22c
    float mCellGutterTop;                              // +0x230
    float mCellGutterRight;                            // +0x234
    float mCellGutterBottom;                           // +0x238
    char  _pad280[0x280 - 0x23c];                      // +0x23c
    char  mbFlag280;                                   // +0x280
    char  _pad284;                                     // +0x284
    char  mbFlag284;                                   // +0x285
    char  _pad3f8[0x3f8 - 0x286];                      // +0x286
    ScrollBarBase* mpScrollBarA;                       // +0x3f8
    ScrollBarBase* mpScrollBarB;                       // +0x3fc

    void PlaceCellWindow(int col, int row, void* pInfo, ICellWindow* pCellWindow);
    bool RemoveScrollBar(bool bHorizontal, bool bVertical);
    bool SetScrollBarValues();
    bool SetScrollBarPositions();

    // The IWinGrid sub-object: methods taking `this` as the grid view use this.
    IWinGrid* Grid() { return (IWinGrid*)((char*)this + 0x208); }
    WindowBase* Window() { return (WindowBase*)((char*)this + 4); }
};

// ---------------------------------------------------------------------------
// EASTL containers used by the grid (slice tail)
// ---------------------------------------------------------------------------
struct CellNode {
    CellNode* mpLeft;                                  // +0x00  (list mpNext)
    CellNode* mpRight;                                 // +0x04  (list mpPrev)
    int       mUnknown08;                              // +0x08
    char      mbColor;                                 // +0x0c
    char      _pad0d[0x1c - 0x0d];                     // +0x0d
    unsigned  mKey;                                    // +0x1c
};

// eastl::list<CellCoordinates> - the sentinel node is at the object's head.
struct CellList {
    CellNode* mpHead;                                  // +0x00
    CellNode* mpTail;                                  // +0x04
    int       mnSize;                                  // +0x08
    void clear();
};

struct CellData;

// eastl::rbtree<CellData,...> - header node at +0x04 (left/right only), root
// pointer at +0x0c.
struct CellRbtree {
    int       _pad00;                                  // +0x00
    CellNode* mHeaderLeft;                             // +0x04
    CellNode* mHeaderRight;                            // +0x08
    CellNode* mpRoot;                                  // +0x0c
    CellNode* AllocateNode(const CellData* pData, void* pArg);
    void find(CellNode** pOut, const CellData* pKey);
};

void* EAAllocate(unsigned size, const char* pTag, int a, int b, const char* pFile, int line);
void operator delete(void* p);

} // namespace UTFWinControls
} // namespace EA

using namespace EA::UTFWinControls;

// ===========================================================================
// 0x971eb0 WinGrid::SetHeadingFormat
// ===========================================================================
// @ 0x00971eb0
void IWinGrid::SetHeadingFormat(const void* pFormat)
{
    unsigned long* pDst = (unsigned long*)&mVisibleColumnCount;
    const unsigned long* pSrc = (const unsigned long*)pFormat;
    for (unsigned i = 0; i < 12; ++i)
        *pDst++ = *pSrc++;
    mbRecalculateAllNeeded = 1;
    ((WindowBase*)((char*)this - 0x208))->SetFlag(8, 1);
}

// ===========================================================================
// 0x971ef0 WinGrid::ClearCellRect
// ===========================================================================
// @ 0x00971ef0
bool IWinGrid::ClearCellRect(int col, int row, int width, int height)
{
    if (width < 1 || height < 1)
        return true;

    CRect used;
    GetCellUsedRange(used);

    if (used.left > col)
        col = used.left;
    int nCols = width;
    if (used.right + 1 < col + width)
        nCols = used.right - col + 1;
    if (nCols <= 0)
        return false;

    if (used.top > row)
        row = used.top;
    int nRows = height;
    if (used.bottom + 1 < row + height)
        nRows = used.bottom - row + 1;
    if (nRows <= 0)
        return false;

    const int colEnd = col + nCols;
    const int rowEnd = row + nRows;
    for (int c = col; c < colEnd; ++c)
        for (int r = row; r < rowEnd; ++r)
            SetCellData(c, r, 0);
    ((WindowBase*)((char*)this - 0x208))->SetFlag(8, 1);
    return true;
}

// ===========================================================================
// 0x971fe0 WinGrid::ClearAllCells
// ===========================================================================
// @ 0x00971fe0
bool IWinGrid::ClearAllCells()
{
    CRect used = { 0, 0, 0, 0 };
    if (GetCellUsedRange(used)) {
        ClearCellRect(used.left, used.top, used.right - used.left + 1,
                      used.bottom - used.top + 1);
        InvalidateGrid45();
        ((WindowBase*)((char*)this - 0x208))->Invalidate();
    }
    return true;
}

// ===========================================================================
// 0x972060 WinGrid::SetFirstVisibleCell
// ===========================================================================
// @ 0x00972060
bool IWinGrid::SetFirstVisibleCell(int col, int row)
{
    if (mnFirstVisibleColumn != col || mnFirstVisibleRow != row) {
        mnFirstVisibleRow = row;
        mnFirstVisibleColumn = col;
        mbRecalculateAllNeeded = 1;
        ((WindowBase*)((char*)this - 0x208))->SetFlag(8, 1);
    }
    return true;
}

// ===========================================================================
// 0x9725a0 WinGrid::GetScrollBarDrawableVertical
// ===========================================================================
// @ 0x009725a0
IScrollbarDrawable* IWinGrid::GetScrollBarDrawableVertical()
{
    IScrollbarDrawable* pResult;
    ScrollBarBase* pBar = mpScrollBarA;
    if (pBar != 0) {
        IScrollbarDrawable* pDrawable = pBar->GetDrawable();
        if (pDrawable != 0)
            pResult = pDrawable->GetDrawableByType(0xeef3af8c);
        else
            pResult = 0;
    }
    else
        pResult = mpScrollBarFallback;
    return pResult;
}

// ===========================================================================
// 0x9725d0 WinGrid::GetScrollBarDrawableHorizontal
// ===========================================================================
// @ 0x009725d0
IScrollbarDrawable* IWinGrid::GetScrollBarDrawableHorizontal()
{
    IScrollbarDrawable* pResult;
    ScrollBarBase* pBar = mpScrollBarB;
    if (pBar != 0) {
        IScrollbarDrawable* pDrawable = pBar->GetDrawable();
        if (pDrawable != 0)
            pResult = pDrawable->GetDrawableByType(0xeef3af8c);
        else
            pResult = 0;
    }
    else
        pResult = mpScrollBarFallbackH;
    return pResult;
}

// ===========================================================================
// 0x9720a0 WinGrid::PlaceCellWindow
// ===========================================================================
// @ 0x009720a0
void WinGrid::PlaceCellWindow(int col, int row, void* pInfo, ICellWindow* pCellWindow)
{
    if (!pCellWindow)
        return;

    IWinGrid* pGrid = Grid();

    RectF cellArea;
    pGrid->GetCellArea(cellArea);
    if (col < (int)cellArea.left || row < (int)cellArea.top)
        goto hide;
    if (col >= (int)cellArea.right || row >= (int)cellArea.bottom)
        goto hide;

    {
        CellFormat fmt;
        fmt.mUnknown0c = 0;
        fmt.mUnknown10 = 0;
        fmt.mUnknown14 = 0;
        fmt.mUnknown18 = 0;
        fmt.mUnknown1c = 0;
        fmt.mUnknown20 = 0;
        fmt.mAlignH = 0xff;
        fmt.mAlignV = 0;
        fmt.mUnknown27 = 0;
        fmt.mUnknown28 = 0;
        fmt.mUnknown2c = 0;
        fmt.mUnknown30 = 0;
        fmt.mUnknown34 = 0;
        fmt.mUnknown38 = 0;
        (void)pInfo;
        pGrid->GetCellFormat(col, row, &fmt);

        RectF cellRect;
        pGrid->GetCellRect((int)fmt.mUnknown38, row, cellRect);

        RectF winRect;
        winRect.left   = cellRect.left + mCellGutterLeft;
        winRect.top    = cellRect.top + mCellGutterTop;
        winRect.right  = cellRect.right - mCellGutterRight;
        winRect.bottom = cellRect.bottom - mCellGutterBottom;

        RectF* pWinArea = pCellWindow->GetArea();
        const float winW = pWinArea->right - pWinArea->left;
        RectF* pWinArea2 = pCellWindow->GetArea();
        const float winH = pWinArea2->bottom - pWinArea2->top;

        RectF out;
        out.left = winRect.left;
        out.top = winRect.top;
        out.right = winW + winRect.left;
        out.bottom = winH + winRect.top;

        const float half = 0.5f;
        if (!*(char*)((char*)this + 0x280) && !*(char*)((char*)this + 0x284)) {
            const char hAlign = fmt.mAlignH;
            const char vAlign = fmt.mAlignV;
            if (hAlign == 3) {
                out.left = (winRect.right - winW) * half + winRect.left;
                out.right = out.left + winW;
            }
            else if (hAlign == 4) {
                out.right = winRect.right;
                out.left = out.right - winW;
            }
            if (vAlign == 6) {
                out.top = (winRect.bottom - winH) * half + winRect.top;
                out.bottom = out.top + winH;
            }
            else if (vAlign == 7) {
                out.bottom = winRect.bottom;
                out.top = out.bottom - winH;
            }
        }
        pCellWindow->SetArea(&out);
        pCellWindow->SetVisible(true, 1);
        return;
    }

hide:
    pCellWindow->SetVisible(false, 1);
}

// ===========================================================================
// 0x972330 IWinGrid::AutoSize (virtual override; this == grid sub-object)
// ===========================================================================
// @ 0x00972330
void IWinGrid::AutoSize(unsigned int w, unsigned int h, float a, float b)
{
    if (!IsReady())
        return;

    CRect used;
    if (!GetCellUsedRange(used))
        return;

    int nCols = used.right - used.left + 1;
    if ((unsigned)nCols > w)
        SetColumnCount(used.left, w);
    else
        SetColumnCount(used.left, nCols);
    const float fColW0 = a + mGutter.left + mGutter.right;

    int nRows = used.bottom - used.top + 1;
    if ((unsigned)nRows > h)
        SetRowCount(used.top, h);
    else
        SetRowCount(used.top, nRows);
    const float fRowH0 = b + mGutter.top + mGutter.bottom;

    {
        WindowBase* pWin = (WindowBase*)((char*)this - 0x208);
        pWin->SetSize(fColW0, fRowH0);
    }
    (void)IsReady();

    float fRowH = fRowH0;
    float fColW = fColW0;

    if (mpScrollBarB) {
        IScrollbarDrawable* p = mpScrollBarB->GetDrawable();
        RectF* pRect = p->GetRect();
        fRowH = (pRect->bottom - pRect->top) + fRowH;
    }
    if (mpScrollBarA) {
        IScrollbarDrawable* p = mpScrollBarA->GetDrawable();
        RectF* pRect = p->GetRect();
        fColW = (pRect->right - pRect->left) + fColW;
    }

    if (mVisibleColumnCount < fColW) {
        const float cols = (float)ceil((double)mVisibleColumnCount);
        SetColumnCount(mnFirstVisibleColumn, (int)(cols - 1));
        SetColumnWidth(mnFirstVisibleColumn, 1, fColW - mVisibleColumnCount);
        mVisibleColumnCount = fColW;
    }
    if (mVisibleRowCount < fRowH) {
        const float rows = (float)ceil((double)mVisibleRowCount);
        SetRowCount(mnFirstVisibleRow, (int)(rows - 1));
        SetRowHeight(mnFirstVisibleRow, 1, fRowH - mVisibleRowCount);
        mVisibleRowCount = fRowH;
    }

    ((WindowBase*)((char*)this - 0x208))->SetSize(mVisibleColumnCount, mVisibleRowCount);
}

// ===========================================================================
// 0x972600 WinGrid::RemoveScrollBar
// ===========================================================================
// @ 0x00972600
bool WinGrid::RemoveScrollBar(bool bHorizontal, bool bVertical)
{
    bool bChanged = false;

    if (bHorizontal && mpScrollBarA) {
        WindowBase* pWin = Window();
        pWin->RemoveChild((ICellWindow*)mpScrollBarA->GetWindow());
        bChanged = true;
        if (mpScrollBarA) {
            ScrollBarBase* pBar = mpScrollBarA;
            mpScrollBarA = 0;
            pBar->Release();
        }
    }

    if (bVertical && mpScrollBarB) {
        WindowBase* pWin = Window();
        pWin->RemoveChild((ICellWindow*)mpScrollBarB->GetWindow());
        if (mpScrollBarB) {
            ScrollBarBase* pBar = mpScrollBarB;
            mpScrollBarB = 0;
            pBar->Release();
        }
    }
    else if (!bChanged) {
        return true;
    }

    {
        WindowBase* pWin = Window();
        mbPendingUpdate = 1;
        pWin->SetFlag(8, 1);
    }
    return true;
}

// ===========================================================================
// 0x9726c0 WinGrid::SetScrollBarValues
// ===========================================================================
// @ 0x009726c0
bool WinGrid::SetScrollBarValues()
{
    IWinGrid* pGrid = Grid();
    ScrollBarBase* pVertical = *(ScrollBarBase**)((char*)this + 0x3f8);
    if (pVertical && pGrid->mVisibleRowCount > 0.0f) {
        int nRows = pGrid->mnRowCount;
        if (nRows == 0 || nRows < 0)
            nRows = (pGrid->mGridFlags & 0x10000) ? (int)pGrid->mVisibleRowCount : 0;
        else if (pGrid->mGridFlags & 0x10000)
            nRows = (int)pGrid->mVisibleRowCount;
        else {
            CRect used;
            pGrid->GetCellUsedRange(used);
            nRows = used.bottom + 1;
        }
        pVertical->SetMinimumValue(0, false);
        pVertical->SetMaximumValue(nRows, false);
        pVertical->SetVisibleRange((int)pGrid->mVisibleRowCount, false);
        pVertical->SetValue(pGrid->mnFirstVisibleRow, false);
    }

    ScrollBarBase* pHorizontal = *(ScrollBarBase**)((char*)this + 0x3fc);
    if (pHorizontal && pGrid->mVisibleColumnCount > 0.0f) {
        int nCols = pGrid->mnColumnCount;
        if (nCols == 0 || nCols < 0)
            nCols = (pGrid->mGridFlags & 0x8000) ? (int)pGrid->mVisibleColumnCount : 0;
        else if (pGrid->mGridFlags & 0x8000)
            nCols = (int)pGrid->mVisibleColumnCount;
        else {
            CRect used;
            pGrid->GetCellUsedRange(used);
            nCols = used.right + 1;
        }
        pHorizontal->SetMinimumValue(0, false);
        pHorizontal->SetMaximumValue(nCols, false);
        pHorizontal->SetVisibleRange((int)pGrid->mVisibleColumnCount, false);
        pHorizontal->SetValue(pGrid->mnFirstVisibleColumn, false);
    }
    return true;
}

// ===========================================================================
// 0x972910 WinGrid::SetScrollBarPositions
// ===========================================================================
// @ 0x00972910
bool WinGrid::SetScrollBarPositions()
{
    IWinGrid* pGrid = Grid();
    const float one = 1.0f;

    ScrollBarBase* pVertical = *(ScrollBarBase**)((char*)this + 0x3f8);
    if (pVertical) {
        IScrollbarDrawable* pDraw = pVertical->GetDrawable();
        if (pDraw) {
            RectF vert;
            vert.left = 0.0f;
            vert.top = 0.0f;
            vert.right = one;
            vert.bottom = 0.0f;
            pDraw->SetRect(&vert);
        }
    }

    ScrollBarBase* pHorizontal = *(ScrollBarBase**)((char*)this + 0x3fc);
    if (pHorizontal) {
        IScrollbarDrawable* pDraw = pHorizontal->GetDrawable();
        if (pDraw) {
            RectF horiz;
            horiz.left = 0.0f;
            horiz.top = 0.0f;
            horiz.right = 0.0f;
            horiz.bottom = one;
            pDraw->SetRect(&horiz);
        }
    }
    (void)pGrid;
    return true;
}

// ===========================================================================
// 0x972d30 eastl::list<IWinGrid::CellCoordinates>::clear
// ===========================================================================
// @ 0x00972d30
void CellList::clear()
{
    CellNode* pFirst = mpHead;
    if (pFirst != (CellNode*)this) {
        do {
            CellNode* pNext = pFirst->mpLeft;
            operator delete(pFirst);
            pFirst = pNext;
        } while (pFirst != (CellNode*)this);
    }
    mpTail = (CellNode*)this;
    mpHead = (CellNode*)this;
}

// ===========================================================================
// 0x972d60 eastl::rbtree<IWinGrid::CellData,...>::find
// ===========================================================================
// @ 0x00972d60
void CellRbtree::find(CellNode** pOut, const CellData* pKey)
{
    CellNode* pHeader = (CellNode*)&mHeaderLeft;
    CellNode* pResult = pHeader;
    CellNode* pNode = mpRoot;
    if (pNode) {
        const unsigned key = *(const unsigned*)((const char*)pKey + 0xc);
        do {
            if ((unsigned)pNode->mKey < key)
                pNode = pNode->mpLeft;
            else {
                pResult = pNode;
                pNode = pNode->mpRight;
            }
        } while (pNode);
    }
    if (pResult != pHeader &&
        *(const unsigned*)((const char*)pKey + 0xc) >= (unsigned)pResult->mKey)
        *pOut = pResult;
    else
        *pOut = pHeader;
}

// ===========================================================================
// 0x972dd0 eastl rbtree node allocator (EAAllocate + inline copy)
// ===========================================================================
// @ 0x00972dd0
CellNode* CellRbtree::AllocateNode(const CellData* pData, void* pArg)
{
    CellNode* pNode = (CellNode*)EAAllocate(0x50, "EASTL", 0, 0, "rbtree.cpp", 0xd1);
    if (pNode) {
        unsigned* pDst = (unsigned*)((char*)pNode + 0x10);
        const unsigned* pSrc = (const unsigned*)((const char*)pData + 0x10);
        for (unsigned i = 0; i < 0x10u; ++i)
            pDst[i] = pSrc[i];
    }
    pNode->mpLeft = 0;
    pNode->mpRight = 0;
    pNode->mUnknown08 = (int)pArg;
    pNode->mbColor = *(char*)((const char*)pData + 0xc);
    return pNode;
}
