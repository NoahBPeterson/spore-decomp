// Slice s00970f30 - EA::UTFWinControls::WinGrid / IWinGrid (0x970f30..0x971ea1, 21 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region).
//
// Retail layout: the 135-slot IWinGrid sub-object (vtable at +0, mGridFlags at +4) lives at
// WinGrid+0x20c.  Its methods run with `this` == that sub-object and reach the owning WinGrid
// through negative offsets, or through ((WinGrid*)((char*)this - 0x20c)).

#include "types.h"
#include <math.h>

#define PV(n) virtual void pv##n()

namespace EA {
namespace UTFWinControls {

// ---------------------------------------------------------------------------
// Shared small types
// ---------------------------------------------------------------------------

struct RectF {
    float left, top, right, bottom;
    RectF() {}
};

// Plain Win32 tagRECT (also used for GetCellUsedRange).
struct CRect {
    int left, top, right, bottom;
};

struct Batch2D;
struct RenderContext;
struct IUnknown2;

namespace Text {
struct StyleManager;
struct LineLayout;
struct Typesetter;
} // namespace Text

// A concrete text style (opaque apart from the fields DrawText swaps around).
struct TextStyle {
    char     _pad000[0x224];
    unsigned field224;                   // +0x224
    unsigned field228;                   // +0x228
    char     _pad22c[0x244 - 0x22c];
    unsigned field244;                   // +0x244
    unsigned field248;                   // +0x248
    char     _pad24c[0x250 - 0x24c];
    unsigned field250;                   // +0x250
};

// ---------------------------------------------------------------------------
// The owner-draw packet handed to the Draw* callbacks.
// ---------------------------------------------------------------------------
struct CellFormat {
    unsigned nTextStyle;                 // +0x00
    unsigned nColor[8];                  // +0x04
    char     nWrapping;                  // +0x24
    char     nHAlignment;                // +0x25
    char     nVAlignment;                // +0x26
    char     field27;                    // +0x27
    unsigned nBorder;                    // +0x28
    unsigned nBorderColor;               // +0x2c
    float    field30;                    // +0x30
    float    field34;                    // +0x34
};

struct CellData {
    int   nCellType;                     // +0x00
    int   nColumn;                       // +0x04
    int   nRow;                          // +0x08
    void* pCellData;                     // +0x0c
    CellFormat* pCellFormat;             // +0x10
    void* pExtraData;                    // +0x14
    unsigned nCellFlags;                 // +0x18
};

struct OwnerDrawInfo {
    void*         pWinGrid;              // +0x00
    unsigned      nColumn;               // +0x04
    unsigned      nRow;                  // +0x08
    RectF*        pRectCell;             // +0x0c
    RectF*        pRectCellClip;         // +0x10
    RectF*        pRectAreaToDrawTo;     // +0x14
    RenderContext* pRenderContext;       // +0x18
    CellFormat*   pCellFormat;           // +0x1c
    CellData*     pCellData;             // +0x20
    char          bCellSelected;         // +0x24
    char          bCellHighlighted;      // +0x25
    char          bGridEnabled;          // +0x26
};

struct Bitmap {
    char _pad00[0x1c];
    int  mnWidth;                        // +0x1c
    int  mnHeight;                       // +0x20
};

struct TextBuffer {
    const unsigned short* mpBegin;       // +0x00
    const unsigned short* mpEnd;         // +0x04
};

namespace Text {
struct StyleManager {
    TextStyle* GetStyle(unsigned styleId, TextStyle* pIn);
};
StyleManager* GetStyleManager(bool bArg);
struct LineLayout {
    char _data[0x2c];
    void Clear(int bArg);
};
struct Typesetter {
    char _data[0x530];
    void* LayoutParagraph(const unsigned short* pBegin, int nCount,
                          float l, float t, float r, float b,
                          TextStyle* pStyle, LineLayout* pLineLayout, int nArg);
};
} // namespace Text

// ---------------------------------------------------------------------------
// Render interfaces
// ---------------------------------------------------------------------------
struct Batch2D {
    PV(0);
    virtual void SetColor(unsigned color);                    // +0x04 slot 1
    PV(2);
    virtual char GetX3(void* pOut);                           // +0x0c slot 3
    virtual void X4(char c, void* p);                         // +0x10 slot 4
    virtual void X5(unsigned v);                              // +0x14 slot 5
    PV(6); PV(7); PV(8); PV(9); PV(10); PV(11); PV(12); PV(13);
    virtual void DrawRect(float l, float t, float r, float b); // +0x38 slot 14
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20); PV(21);
    virtual void DrawBitmap(RectF* pDest, Bitmap* pBmp, RectF* pSrc); // +0x58 slot 22
};

struct RenderContext {
    Batch2D* Begin2D(void* pRenderMode);
};

// Secondary IUnknown-ish objects reached through IWindow slot 5.
struct ITextFormatter {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7); PV(8); PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30); PV(31); PV(32); PV(33); PV(34);
    virtual char pv35();                                      // +0x8c slot 35
};

// Secondary interface sub-object of WinGrid: its vtable lives at WinGrid+4.
struct IWindow {
    PV(0); PV(1); PV(2); PV(3); PV(4);
    virtual void* pv5();                                      // +0x14 slot 5
    PV(6); PV(7); PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15);
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23); PV(24); PV(25);
    PV(26); PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(unsigned flag, int value);           // +0x7c slot 31
    PV(32); PV(33); PV(34); PV(35);
    virtual void Invalidate();                                // +0x90 slot 36
    virtual void InvalidateLayout();                          // +0x94 slot 37 (0x009719a0)
};

// WinGrid inherits the IWindow interface through a concrete Window base (the
// virtual InvalidateLayout override is a Window method, so its `this` is the
// Window (= IWindow) sub-object at WinGrid+4, not WinGrid itself).
struct Window : IWindow {
    virtual void InvalidateLayout();                           // +0x94 slot 37 (0x009719a0)
};

// Primary base of WinGrid (vtable at WinGrid+0).
struct Win {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7); PV(8); PV(9);
    virtual void SerUpdate();                                 // 0x009614a0
    virtual bool DoMessage(int* pMsg);                        // 0x00950bb0
};

struct DropShadowDescriptor {
    int mMode1;                                               // +0x00
    int mMode2;                                               // +0x04
    void SetMode1(int mode);                                  // 0x00830280
    void SetMode2(int mode);                                  // 0x00830150
    void DrawCellText(Batch2D* pBatch, void* p1, void* p2, void* p3,
                      unsigned color, unsigned short ch, char flag); // 0x0096e740
};

struct WinGrid;

// ---------------------------------------------------------------------------
// IWinGrid - the grid sub-object embedded at WinGrid+0x20c
// ---------------------------------------------------------------------------
struct IWinGrid {
    struct SelNode {
        SelNode* mpNext;                                      // +0x00
        SelNode* mpPrev;                                      // +0x04
        int      mnColumn;                                    // +0x08
        int      mnRow;                                       // +0x0c
    };

    // --- 135-slot vtable; only the slots exercised by this slice are named ---
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6);
    virtual bool GetGridArea(RectF& pOut);                    // +0x01c slot 7
    virtual bool GetCellArea(RectF& pOut);                    // +0x020 slot 8
    PV(9); PV(10);
    virtual void SetGridFlag(unsigned flag, bool value);      // +0x02c slot 11
    virtual bool GetGridFlag(unsigned flag);                  // +0x030 slot 12
    virtual bool SetDefaultTextStyle(unsigned style);         // +0x034 slot 13
    PV(14); PV(15); PV(16); PV(17); PV(18);
    virtual bool SetDefaultTextWrapping(bool bWrap);          // +0x04c slot 19
    PV(20); PV(21);
    virtual bool SetGutters(float a, float b, float c, float d);      // +0x058 slot 22
    PV(23);
    virtual bool SetCellGutters(float a, float b, float c, float d);  // +0x060 slot 24
    PV(25); PV(26); PV(27); PV(28); PV(29);
    virtual bool ScrollCellsVertically(int nCells);           // +0x078 slot 30
    virtual bool ScrollCellsHorizontally(int nCells);         // +0x07c slot 31
    PV(32); PV(33);
    virtual void ScrollToColumn(int col);                     // +0x088 slot 34
    virtual void ScrollToRow(int row);                        // +0x08c slot 35
    PV(36); PV(37); PV(38); PV(39); PV(40);
    virtual bool GetSelection(int& col, int& row);            // +0x0a4 slot 41
    PV(42); PV(43); PV(44); PV(45); PV(46);
    virtual void SetCellLimits(int col, int row);             // +0x0bc slot 47
    PV(48);
    virtual bool GetCellUsedRange(CRect& out);                // +0x0c4 slot 49
    PV(50); PV(51); PV(52); PV(53); PV(54); PV(55); PV(56); PV(57); PV(58); PV(59);
    PV(60); PV(61); PV(62); PV(63); PV(64);
    virtual bool GetColumnHeadingArea(int col, RectF& out);   // +0x104 slot 65
    virtual bool GetRowHeadingArea(int row, RectF& out);      // +0x108 slot 66
    PV(67); PV(68);
    virtual bool SetHeadingSizes(float colHeight, float rowWidth); // +0x114 slot 69
    PV(70); PV(71); PV(72); PV(73); PV(74); PV(75); PV(76); PV(77); PV(78); PV(79);
    PV(80); PV(81); PV(82); PV(83); PV(84); PV(85); PV(86); PV(87); PV(88); PV(89);
    PV(90); PV(91); PV(92); PV(93); PV(94); PV(95); PV(96); PV(97); PV(98);
    virtual bool GetCellRect(int col, int row, RectF& out);   // +0x18c slot 99
    PV(100); PV(101); PV(102);
    virtual bool DoCursorHitTest(float x, float y, int& result, CRect& coords); // +0x19c slot 103
    PV(104); PV(105); PV(106); PV(107); PV(108); PV(109); PV(110); PV(111); PV(112);
    PV(113); PV(114); PV(115); PV(116); PV(117); PV(118); PV(119); PV(120); PV(121);
    PV(122); PV(123); PV(124); PV(125); PV(126);
    virtual bool SetDefaultAlignment(int hAlign, int vAlign);  // +0x1fc slot 127

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
    char     _pad16b[0x19c - 0x16b];       // +0x16b
    int      mUnknown19c;                  // +0x19c
    char     _pad1a0[0x1e8 - 0x1a0];       // +0x1a0
    void*    mpExtraData;                  // +0x1e8

    // --- helper declared in slice-49 (definition lives there) ---
};

// ---------------------------------------------------------------------------
// WinGrid - the owning window (primary vtable at +0, IWindow vtable at +4)
// ---------------------------------------------------------------------------
struct WinGrid : Win, Window {
    char _pad008[0x88 - 0x08];                        // +0x008
    RectF mArea;                                      // +0x088
    char _pad098[0x20c - 0x098];                      // +0x098
    IWinGrid mGrid;                                   // +0x20c
    char _padGrid[0x484 - 0x20c - sizeof(IWinGrid)];  // +0x414
    Text::Typesetter mTypesetter;                     // +0x484
    Text::LineLayout mLineLayout;                     // +0x9b4
    void* mp9e0;                                      // +0x9e0
    char  _pad9e4[0xa08 - 0x9e4];                     // +0x9e4
    void* mpA08;                                      // +0xa08
    char  _padA0c[0xa64 - 0xa0c];                     // +0xa0c
    DropShadowDescriptor mDropShadow;                 // +0xa64

    void FUN_00970f30();
    void FUN_00970f60();
    void FUN_00970f80();
    void FUN_00970fb0();
    void DrawText(TextBuffer* pText, RectF* pRect, OwnerDrawInfo* pInfo);
    void DrawCellBackground(OwnerDrawInfo* pInfo);
    void DrawCell(OwnerDrawInfo* pInfo);
};

} // namespace UTFWinControls
} // namespace EA

using namespace EA::UTFWinControls;

// ===========================================================================
// 0x970f30 WinGrid::FUN_00970f30
// ===========================================================================
// @ 0x00970f30
void WinGrid::FUN_00970f30()
{
    mGrid.ScrollCellsVertically((int)-mGrid.mVisibleRowCount);
}

// ===========================================================================
// 0x970f60 WinGrid::FUN_00970f60
// ===========================================================================
// @ 0x00970f60
void WinGrid::FUN_00970f60()
{
    mGrid.ScrollCellsVertically((int)mGrid.mVisibleRowCount);
}

// ===========================================================================
// 0x970f80 WinGrid::FUN_00970f80
// ===========================================================================
// @ 0x00970f80
void WinGrid::FUN_00970f80()
{
    mGrid.ScrollCellsHorizontally((int)-mGrid.mVisibleColumnCount);
}

// ===========================================================================
// 0x970fb0 WinGrid::FUN_00970fb0
// ===========================================================================
// @ 0x00970fb0
void WinGrid::FUN_00970fb0()
{
    mGrid.ScrollCellsHorizontally((int)mGrid.mVisibleColumnCount);
}

// ===========================================================================
// 0x970fd0 IWinGrid::DoCursorHitTest
// ===========================================================================
// @ 0x00970fd0
bool IWinGrid::DoCursorHitTest(float x, float y, int& result, CRect& coords)
{
    result = 0;
    coords.left = 0;
    coords.top = 0;

    RectF gridArea;
    GetGridArea(gridArea);
    if (x < gridArea.left || y < gridArea.top || x > gridArea.right || y > gridArea.bottom) {
        result = 0;
        return result != 0;
    }

    RectF cellArea;
    GetCellArea(cellArea);
    if (!(x >= cellArea.left && y >= cellArea.top
          && x <= cellArea.right && y <= cellArea.bottom)) {
        if ((mGridFlags & 8) && (mGridFlags & 0x10)) {
            char bCol = (y >= mGutter.top && y < mColumnHeadingHeight);
            char bRow = (x >= mGutter.left && x < mRowHeadingWidth);
            if (bCol) {
                if (bRow) {
                    result = 4;
                    return result != 0;
                }
                result = 3;
            }
            else if (bRow) {
                result = 2;
            }
        }
        if (result != 5 && result != 3 && result != 2)
            return result != 0;
    }
    else {
        result = 5;
    }

    int nColEnd = mnFirstVisibleColumn + (int)(float)ceil((double)mVisibleColumnCount);
    coords.left = nColEnd;
    int nRowEnd = mnFirstVisibleRow + (int)(float)ceil((double)mVisibleRowCount);
    coords.top = nRowEnd;

    RectF r;
    for (int i = mnFirstVisibleColumn; i < nColEnd; ++i) {
        GetCellRect(i, 0, r);
        if (r.right > x) {
            coords.left = i;
            break;
        }
    }
    for (int j = mnFirstVisibleRow; j < nRowEnd; ++j) {
        GetCellRect(0, j, r);
        if (r.bottom > y) {
            coords.top = j;
            break;
        }
    }

    if (result == 3) {
        coords.top = 0;
        return result != 0;
    }
    if (result == 2) {
        coords.left = 0;
    }
    return result != 0;
}

// ===========================================================================
// 0x971250 WinGrid::DrawText
// ===========================================================================
// @ 0x00971250
void WinGrid::DrawText(TextBuffer* pText, RectF* pRect, OwnerDrawInfo* pInfo)
{
    CellFormat* pFormat = pInfo->pCellFormat;
    if (pFormat == 0)
        return;

    unsigned styleId = pFormat->nTextStyle;
    Text::StyleManager* pMgr = Text::GetStyleManager(true);
    TextStyle* pStyle = pMgr->GetStyle(styleId, 0);
    if (pStyle == 0)
        return;

    unsigned saved250 = pStyle->field250;
    if (pFormat->nWrapping == 0)
        pStyle->field250 = 0;

    unsigned saved224 = pStyle->field224;
    unsigned saved228 = pStyle->field228;
    unsigned color;
    if (pInfo->bCellSelected) {
        saved224 = pFormat->nColor[6];
        saved228 = pFormat->nColor[7];
    }
    else if (pInfo->bCellHighlighted) {
        saved224 = pFormat->nColor[4];
        saved228 = pFormat->nColor[5];
    }
    else if (pInfo->bGridEnabled) {
        saved224 = pFormat->nColor[0];
        saved228 = pFormat->nColor[1];
    }
    else {
        saved224 = pFormat->nColor[2];
        saved228 = pFormat->nColor[3];
    }
    color = saved224;
    pStyle->field228 = saved228;

    unsigned saved244 = pStyle->field244;
    if (pFormat->nHAlignment == 2)
        pStyle->field244 = 0;
    else if (pFormat->nHAlignment == 3)
        pStyle->field244 = 1;
    else if (pFormat->nHAlignment == 4)
        pStyle->field244 = 2;

    unsigned saved248 = pStyle->field248;
    if (pFormat->nVAlignment == 5)
        pStyle->field248 = 0;
    else if (pFormat->nVAlignment == 6)
        pStyle->field248 = 1;
    else if (pFormat->nVAlignment == 7)
        pStyle->field248 = 2;

    if (pInfo->pRenderContext != 0) {
        Batch2D* pBatch = pInfo->pRenderContext->Begin2D(0);
        pBatch->SetColor(color);
        RectF local;
        char c = pBatch->GetX3(&local);
        pBatch->X5((unsigned)pInfo->pRectCellClip);
        mLineLayout.Clear(1);
        void* pLayout = mTypesetter.LayoutParagraph(pText->mpBegin,
                                                    (int)(pText->mpEnd - pText->mpBegin),
                                                    pRect->left, pRect->top,
                                                    pRect->right, pRect->bottom,
                                                    pStyle, &mLineLayout, 0x14);
        ITextFormatter* pFmt2 = (ITextFormatter*)((IWindow*)((char*)this + 4))->pv5();
        char b = pFmt2->pv35();
        mDropShadow.DrawCellText(pBatch, mp9e0, mpA08, pLayout, color,
                                 *pText->mpBegin, b);
        pBatch->X4(c, &local);
    }

    pStyle->field224 = saved224;
    pStyle->field228 = saved228;
    pStyle->field244 = saved244;
    pStyle->field248 = saved248;
    pStyle->field250 = saved250;
}

// ===========================================================================
// 0x971490 WinGrid::DrawCellBackground
// ===========================================================================
// @ 0x00971490
void WinGrid::DrawCellBackground(OwnerDrawInfo* pInfo)
{
    float l = pInfo->pRectCell->left;
    float t = pInfo->pRectCell->top;
    float r = pInfo->pRectCell->right;
    float b = pInfo->pRectCell->bottom;

    if ((mGrid.mGridFlags & 0x20) && mGrid.mColumnGridColor != 0)
        l += mGrid.mColumnGridOffset;
    if ((mGrid.mGridFlags & 0x40) && mGrid.mRowGridColor != 0)
        t += mGrid.mRowGridOffset;

    if (pInfo->pRectCellClip) {
        const RectF* pClip = pInfo->pRectCellClip;
        float cl = pClip->left;
        float ct = pClip->top;
        float cr = pClip->right;
        float cb = pClip->bottom;
        if (!(cl < r && l < cr && ct < b && t < cb)) {
            l = 0.0f;
            t = 0.0f;
            r = 0.0f;
            b = 0.0f;
        }
        else {
            if (!(l > cl))
                l = cl;
            if (!(t > ct))
                t = ct;
            if (!(cr > r))
                r = cr;
            if (!(cb > b))
                b = cb;
        }
    }

    RenderContext* pCtx = pInfo->pRenderContext;
    if (pCtx == 0)
        return;

    Batch2D* pBatch = pCtx->Begin2D(0);
    if (pInfo->bCellSelected) {
        unsigned c = pInfo->pCellFormat->nColor[7];
        if (c != 0 && !(mGrid.mGridFlags & 0x80000))
            pBatch->SetColor(c);
    }
    else if (pInfo->bCellHighlighted) {
        unsigned c = pInfo->pCellFormat->nColor[5];
        if (c != 0 && !(mGrid.mGridFlags & 0x80000))
            pBatch->SetColor(c);
    }
    else {
        unsigned c = pInfo->pCellFormat->nColor[1];
        if (c != 0)
            pBatch->SetColor(c);
    }
    pBatch->DrawRect(l, t, r, b);
}

// ===========================================================================
// 0x971600 WinGrid::DrawCell
// ===========================================================================
// @ 0x00971600
void WinGrid::DrawCell(OwnerDrawInfo* pInfo)
{
    float l = pInfo->pRectCell->left;
    float t = pInfo->pRectCell->top;
    float r = pInfo->pRectCell->right;
    float b = pInfo->pRectCell->bottom;

    if ((mGrid.mGridFlags & 0x20) && mGrid.mColumnGridColor != 0)
        l += mGrid.mColumnGridOffset;
    if ((mGrid.mGridFlags & 0x40) && mGrid.mRowGridColor != 0)
        t += mGrid.mRowGridOffset;

    float bl = l, bt = t, br = r, bb = b;
    if (pInfo->pRectCellClip) {
        float cl = pInfo->pRectCellClip->left;
        if (!(cl < r && l < pInfo->pRectCellClip->right
              && pInfo->pRectCellClip->top < b && t < pInfo->pRectCellClip->bottom)) {
            bl = 0.0f;
            bt = 0.0f;
            br = 0.0f;
            bb = 0.0f;
        }
        else {
            if (!(l > cl))
                bl = cl;
            if (!(t > pInfo->pRectCellClip->top))
                bt = pInfo->pRectCellClip->top;
            if (!(pInfo->pRectCellClip->right > r))
                br = pInfo->pRectCellClip->right;
            if (!(pInfo->pRectCellClip->bottom > b))
                bb = pInfo->pRectCellClip->bottom;
        }
    }

    if (pInfo->pRenderContext) {
        Batch2D* pBatch = pInfo->pRenderContext->Begin2D(0);
        if (!(mGrid.mGridFlags & 0x20000)) {
            unsigned c;
            if (pInfo->bCellSelected)
                c = pInfo->pCellFormat->nColor[7];
            else if (pInfo->bCellHighlighted)
                c = pInfo->pCellFormat->nColor[5];
            else
                c = pInfo->pCellFormat->nColor[1];
            if (c != 0 && !(mGrid.mGridFlags & 0x80000))
                pBatch->SetColor(c);
            pBatch->DrawRect(bl, bt, br, bb);
        }
    }

    float ax = l, ay = t, az = r, aw = b;
    ax = ax + mGrid.mCellGutter.left;
    ay = mGrid.mCellGutter.top + ay;
    az = az - mGrid.mCellGutter.right;
    aw = aw - mGrid.mCellGutter.bottom;

    CellData* pData = pInfo->pCellData;
    if (pData == 0)
        return;

    if (pData->nCellType == 2) {
        if (pData->pCellData) {
            RectF textRect;
            textRect.left = ax;
            textRect.top = ay;
            textRect.right = az;
            textRect.bottom = aw;
            DrawText((TextBuffer*)pData->pCellData, &textRect, pInfo);
        }
        return;
    }
    if (pData->nCellType != 4)
        return;

    Bitmap* pBmp = (Bitmap*)pData->pCellData;
    if (pBmp == 0)
        return;

    RectF dest;
    RectF src;
    dest.left = ax;
    dest.top = ay;
    dest.right = az;
    dest.bottom = aw;
    src.left = 0.0f;
    src.top = 0.0f;
    src.right = 1.0f;
    src.bottom = 1.0f;

    if (!(mGrid.mGridFlags & 0x200000)) {
        int bw = pBmp->mnWidth;
        int bh = pBmp->mnHeight;
        CellFormat* pFmt = pInfo->pCellFormat;
        if (pFmt->nHAlignment == 3) {
            float cx = (az - ax) * 0.5f - (float)(bw / 2) + ax;
            dest.left = cx;
            dest.right = (float)bw + cx;
        }
        else if (pFmt->nHAlignment == 4) {
            dest.right = az;
            dest.left = az - (float)bw;
        }
        else {
            dest.left = ax;
            dest.right = (float)bw + ax;
        }
        if (pFmt->nVAlignment == 6) {
            float cy = (aw - ay) * 0.5f - (float)(bh / 2) + ay;
            dest.top = cy;
            dest.bottom = (float)bh + cy;
        }
        else if (pFmt->nVAlignment == 7) {
            dest.bottom = aw;
            dest.top = aw - (float)bh;
        }
        else {
            dest.top = ay;
            dest.bottom = (float)bh + ay;
        }
    }

    if (pInfo->pRenderContext) {
        Batch2D* pBatch = pInfo->pRenderContext->Begin2D(0);
        pBatch->DrawBitmap(&dest, pBmp, &src);
    }
}

// ===========================================================================
// 0x9719a0 Window::InvalidateLayout  (WinGrid's IWindow override)
// ===========================================================================
// @ 0x009719a0
void Window::InvalidateLayout()
{
    IWindow::InvalidateLayout();

    IWinGrid* pGrid = (IWinGrid*)((char*)this + 0x208);

    RectF gridArea;
    pGrid->GetGridArea(gridArea);
    RectF cellArea;
    pGrid->GetCellArea(cellArea);

    WinGrid* pWin = (WinGrid*)((char*)this - 4);
    pWin->mGrid.mVisibleGridAreaWidth = gridArea.right - gridArea.left;
    pWin->mGrid.mVisibleGridAreaHeight = gridArea.bottom - gridArea.top;
    pWin->mGrid.mVisibleCellAreaWidth = cellArea.right - cellArea.left;
    pWin->mGrid.mVisibleCellAreaHeight = cellArea.bottom - cellArea.top;
    ((IWindow*)this)->SetFlag(8, 1);
    pWin->mGrid.mbRecalculateAllNeeded = 1;
}

// ===========================================================================
// 0x971a40 IWinGrid::SetDefaultTextStyle
// ===========================================================================
// @ 0x00971a40
bool IWinGrid::SetDefaultTextStyle(unsigned style)
{
    int* pStyle = &mDefaultTextStyle;
    *pStyle = style;
    mbRecalculateAllNeeded = 1;
    ((IWindow*)((char*)this - 0x208))->SetFlag(8, 1);
    return true;
}

// ===========================================================================
// 0x971a70 IWinGrid::SetDefaultTextWrapping
// ===========================================================================
// @ 0x00971a70
bool IWinGrid::SetDefaultTextWrapping(bool bWrap)
{
    if (bWrap != GetGridFlag(0x800)) {
        SetGridFlag(0x800, bWrap);
        mbRecalculateAllNeeded = 1;
        ((IWindow*)((char*)this - 0x208))->SetFlag(8, 1);
    }
    return true;
}

// ===========================================================================
// 0x971ac0 IWinGrid::SetGutters
// ===========================================================================
// @ 0x00971ac0
bool IWinGrid::SetGutters(float a, float b, float c, float d)
{
    float* p = &mGutter.left;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    mbRecalculateAllNeeded = 1;
    ((IWindow*)((char*)this - 0x208))->SetFlag(8, 1);
    return true;
}

// ===========================================================================
// 0x971b10 IWinGrid::SetCellGutters
// ===========================================================================
// @ 0x00971b10
bool IWinGrid::SetCellGutters(float a, float b, float c, float d)
{
    float* p = &mCellGutter.left;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    mbRecalculateAllNeeded = 1;
    ((IWindow*)((char*)this - 0x208))->SetFlag(8, 1);
    return true;
}

// ===========================================================================
// 0x971b60 IWinGrid::ScrollToColumn
// ===========================================================================
// @ 0x00971b60
void IWinGrid::ScrollToColumn(int col)
{
    if (col == mnFirstVisibleColumn)
        return;
    if (mnColumnCount > 0 && mnColumnCount != -1 && (mGridFlags & 0x8000)) {
        if (col >= mnColumnCount)
            col = mnColumnCount - 1;
    }
    else if (!(mGridFlags & 0x8000)) {
        CRect r = { 0, 0, 0, 0 };
        GetCellUsedRange(r);
        if (col >= r.right + 1)
            col = r.right;
    }
    mnFirstVisibleColumn = col;
    ((IWindow*)((char*)this - 0x208))->Invalidate();
}

// ===========================================================================
// 0x971be0 IWinGrid::ScrollToRow
// ===========================================================================
// @ 0x00971be0
void IWinGrid::ScrollToRow(int row)
{
    if (row == mnFirstVisibleRow)
        return;
    if (mnRowCount > 0 && mnRowCount != -1 && (mGridFlags & 0x10000)) {
        if (row >= mnRowCount)
            row = mnRowCount - 1;
    }
    else if (!(mGridFlags & 0x10000)) {
        CRect r = { 0, 0, 0, 0 };
        GetCellUsedRange(r);
        if (row >= r.right + 1)
            row = r.right;
    }
    mnFirstVisibleRow = (row > 0) ? row : 0;
    ((IWindow*)((char*)this - 0x208))->Invalidate();
}

// ===========================================================================
// 0x971c70 IWinGrid::GetSelection
// ===========================================================================
// @ 0x00971c70
bool IWinGrid::GetSelection(int& col, int& row)
{
    if (mSelectionList.mpNext != &mSelectionList) {
        col = mSelectionList.mpNext->mnColumn;
        row = mSelectionList.mpNext->mnRow;
        return true;
    }
    return false;
}

// ===========================================================================
// 0x971ca0 IWinGrid::SetCellLimits
// ===========================================================================
// @ 0x00971ca0
void IWinGrid::SetCellLimits(int col, int row)
{
    if (col == mnColumnCount && row == mnRowCount)
        return;
    mnRowCount = row;
    mnColumnCount = col;
    mbRecalculateAllNeeded = 1;
    ((IWindow*)((char*)this - 0x208))->SetFlag(8, 1);
}

// ===========================================================================
// 0x971ce0 IWinGrid::SetDefaultAlignment
// ===========================================================================
// @ 0x00971ce0
bool IWinGrid::SetDefaultAlignment(int hAlign, int vAlign)
{
    if (mAlign16a != 0 || mAlign169 != 0) {
        char b = (char)vAlign;
        char a = (char)hAlign;
        mAlign16a = b;
        mAlign169 = a;
        mbRecalculateAllNeeded = 1;
        ((IWindow*)((char*)this - 0x208))->SetFlag(8, 1);
    }
    return true;
}

// ===========================================================================
// 0x971d30 IWinGrid::GetColumnHeadingArea
// ===========================================================================
// @ 0x00971d30
bool IWinGrid::GetColumnHeadingArea(int col, RectF& out)
{
    bool bResult = false;
    if (mGridFlags & 8) {
        if (col == -1) {
            WinGrid* pWin = (WinGrid*)((char*)this - 0x20c);
            out.left = mGutter.left;
            out.top = mGutter.top;
            out.right = pWin->mArea.right - pWin->mArea.left - mGutter.right;
            out.bottom = mColumnHeadingHeight + mGutter.top;
            bResult = true;
        }
        else if (GetCellRect(col, 0, out)) {
            out.top = mGutter.top;
            out.bottom = mColumnHeadingHeight + mGutter.top;
            bResult = true;
        }
    }
    return bResult;
}

// ===========================================================================
// 0x971dd0 IWinGrid::GetRowHeadingArea
// ===========================================================================
// @ 0x00971dd0
bool IWinGrid::GetRowHeadingArea(int row, RectF& out)
{
    bool bResult = false;
    if (mGridFlags & 0x10) {
        if (row == -1) {
            WinGrid* pWin = (WinGrid*)((char*)this - 0x20c);
            out.left = mGutter.left;
            out.top = mGutter.top;
            out.right = mColumnHeadingHeight + mGutter.left;
            out.bottom = pWin->mArea.bottom - pWin->mArea.top - mGutter.bottom;
            bResult = true;
        }
        else if (GetCellRect(0, row, out)) {
            float g = mGutter.left;
            out.left = g;
            out.right = mRowHeadingWidth + g;
            bResult = true;
        }
    }
    return bResult;
}

// ===========================================================================
// 0x971e70 IWinGrid::SetHeadingSizes
// ===========================================================================
// @ 0x00971e70
bool IWinGrid::SetHeadingSizes(float colHeight, float rowWidth)
{
    float* p = &mColumnHeadingHeight;
    p[0] = colHeight;
    p[1] = rowWidth;
    mbRecalculateAllNeeded = 1;
    ((IWindow*)((char*)this - 0x208))->SetFlag(8, 1);
    return true;
}
