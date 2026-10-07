// Slice s0097a130: EA::UTFWinControls::WinGrid::OnRebuild (MSVC 2008 SP1, /O2 /arch:SSE).
// Draws the grid: grid lines, column/row headings, cell backgrounds, cells, outline.
// Retail layout: the IWinGrid subobject (vptr, mGridFlags at +4) sits at WinGrid+0x20c.
#include "types.h"
#include <math.h>

struct Rect { float x1, y1, x2, y2; };

struct CellFormat {
    uint32_t nTextStyle;
    uint32_t nColor[8];
    uint8_t  nWrapping, nHAlignment, nVAlignment, pad;
    uint32_t nBorder;
    uint32_t nBorderColor;
    CellFormat() {
        nTextStyle = 0;
        for (int i = 0; i < 8; i++) nColor[i] = 0;
        nWrapping = 0xff; nHAlignment = 0; nVAlignment = 0;
        nBorder = 0; nBorderColor = 0;
    }
};

struct Renderer2D {
    virtual void s0();
    virtual void SetColor(unsigned int c);
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void DrawRect(float x1,float y1,float x2,float y2,float t);
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void FillRect(float x1,float y1,float x2,float y2);
};

struct IWinGridView {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void GetClipRect(Rect* out);
    virtual void GetGridRect(Rect* out);
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual bool TestFlag(unsigned int f);
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual bool IsCellHighlighted(int col,int row);
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void GetVisibleRange(int* out);
    virtual void GetCellRange(int* out);
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual float GetColumnsExtent(int start,int count);
    virtual float GetRowsExtent(int start,int count);
    virtual void GetColumnHeaderRect(int col,Rect* out);
    virtual void GetRowHeaderRect(int row,Rect* out);
    virtual void s67();
    virtual void s68();
    virtual void s69();
    virtual void s70();
    virtual void s71();
    virtual void s72();
    virtual void s73();
    virtual void s74();
    virtual void s75();
    virtual void s76();
    virtual void GetCellFormat(int col,int row,CellFormat* out);
};

struct RenderContext {
    Renderer2D* Begin2D(int a);   // 0x0095bc10
};

// eastl::basic_string<wchar_t> (16 bytes)
extern wchar_t gEmptyWStr[2];   // 0x01667bac
void __cdecl EASTLFree(void* p);   // 0x00f47380 EASTL_allocator_deallocate
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAlloc;
    WString() { mpBegin = gEmptyWStr; mpEnd = gEmptyWStr; mpCapacity = gEmptyWStr + 1; }
    ~WString() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTLFree(mpBegin); }   // inlined into the atexit thunk 0x013c1330
};
extern "C" int WStr_Format(WString* s, const wchar_t* fmt, ...);   // 0x0041e050

struct HNode { uint32_t key; WString value; HNode* next; };
struct HeadingMap {
    uint32_t pad[5];
    HNode**  mpBuckets;
    uint32_t mnBuckets;
    uint32_t pad2[6];
};

struct RBNode { RBNode* right; RBNode* left; RBNode* parent; int color; int key; int pad; void* value; };
static RBNode* LowerBound(RBNode* hdr, int key) {
    RBNode* best = hdr;
    RBNode* n = hdr->parent;
    while (n) {
        if (n->key < key) n = n->right;
        else { best = n; n = n->left; }
    }
    return best;
}
static void* FindCell(RBNode* rows, int col, int row) {
    RBNode* r = LowerBound(rows, row);
    if (r == rows || row < r->key) return 0;
    RBNode* inner = (RBNode*)((char*)r + 0x1c);
    RBNode* c = LowerBound(inner, col);
    if (c == inner || col < c->key) c = inner;
    if (c == inner) return 0;
    return c->value;
}

struct CellDrawArgs {
    IWinGridView* grid;
    int   col;
    int   row;
    Rect* cellRect;
    Rect* clipRect;
    Rect* gridRect;
    RenderContext* rc;
    CellFormat* fmt;
    void* cellData;
    bool  highlighted;
    bool  mouseOver;
    bool  flag;
};

static void IntersectRect(const Rect& a, const Rect& b, Rect& out) {
    if (a.x1 >= b.x2 || b.x1 >= a.x2 || a.y1 >= b.y2 || b.y1 >= a.y2) {
        out.y2 = 0.0f; out.y1 = 0.0f; out.x2 = 0.0f; out.x1 = 0.0f;
        return;
    }
    out.x1 = (b.x1 > a.x1) ? b.x1 : a.x1;
    out.y1 = (b.y1 > a.y1) ? b.y1 : a.y1;
    out.x2 = (a.x2 > b.x2) ? b.x2 : a.x2;
    out.y2 = (a.y2 > b.y2) ? b.y2 : a.y2;
}

struct WinGrid {
    char     pad0[0x2c];
    uint32_t mWinFlags;                 // +0x2c
    char     pad1[0x88 - 0x30];
    Rect     mArea;                     // +0x88
    char     pad2[0x20c - 0x98];
    IWinGridView mGrid;                 // +0x20c (vptr)
    uint32_t mGridFlags;                // +0x210
    char     pad3[0x254 - 0x214];
    int      mnFirstVisibleColumn;      // +0x254
    int      mnFirstVisibleRow;         // +0x258
    float    mfVisibleColumnCount;      // +0x25c
    float    mfVisibleRowCount;         // +0x260
    int      mnColumnCount;             // +0x264
    int      mnRowCount;                // +0x268
    uint32_t pad4;                      // +0x26c
    uint32_t pad5;                      // +0x270
    uint32_t mnOutlineColor;            // +0x274
    uint32_t mnColumnGridColor;         // +0x278
    uint32_t mnRowGridColor;            // +0x27c
    float    mnColumnGridThickness;     // +0x280
    float    mnRowGridThickness;        // +0x284
    char     pad6[0x2ac - 0x288];
    int      mExtraDataType;            // +0x2ac
    char     pad7[0x324 - 0x2b0];
    RBNode   mCellDataRows;             // +0x324 (map header)
    char     pad8[0x3a8 - (0x324 + sizeof(RBNode))];
    int      mHitType;                  // +0x3a8
    int      mHitColumn;                // +0x3ac
    int      mHitRow;                   // +0x3b0
    char     pad9[0x404 - 0x3b4];
    HeadingMap mColumnHeadings;         // +0x404
    HeadingMap mRowHeadings;            // +0x424
    char     pad10[0x454 - 0x444];
    CellFormat mDefaultHeadingFormatting; // +0x454

    float GetColumnWidthInternal(int col);   // 0x00979db0
    float GetRowHeightInternal(int row);     // 0x00979f10
    void  DrawCellBackground(CellDrawArgs* a);   // 0x00971490
    void  DrawCell(CellDrawArgs* a);         // 0x00971600
    void  DrawText(WString* s, Rect* r, CellDrawArgs* a);   // 0x00971250
    bool  OnRebuild(RenderContext* rc);
};

static WString* FindHeading(HeadingMap& m, int key) {
    unsigned idx = (unsigned)key % m.mnBuckets;
    for (HNode* n = m.mpBuckets[idx]; n; n = n->next)
        if ((int)n->key == key) return &n->value;
    return 0;
}

// @ 0x0097A130
bool WinGrid::OnRebuild(RenderContext* rc) {
    CellFormat fmt;
    Rect gridRect;
    int  vis[4] = {0, 0, 0, 0};
    mGrid.GetGridRect(&gridRect);
    mGrid.GetVisibleRange(vis);

    int firstCol = mnFirstVisibleColumn;
    int firstRow = mnFirstVisibleRow;
    int colEnd = (int)(__int64)ceil((double)mfVisibleColumnCount) + firstCol;
    int rowEnd = (int)(__int64)ceil((double)mfVisibleRowCount) + firstRow;
    uint32_t flags = mGridFlags;
    if (!(flags & 0x8000) && vis[2] < colEnd) colEnd = vis[2] + 1;
    if (!(flags & 0x10000) && vis[3] < rowEnd) rowEnd = vis[3] + 1;

    Renderer2D* r = rc->Begin2D(0);
    flags = mGridFlags;
    Rect cell;
    if (((flags & 0x20) && mnColumnGridColor != 0) || ((flags & 0x40) && mnRowGridColor != 0)) {
        float yLim = gridRect.y2 - 1.0f;
        float xLim = gridRect.x2 - 1.0f;
        if ((flags & 0x20) && mnColumnGridColor != 0) {
            int c = mnRowCount;
            bool skip = false;
            if (c == -1 && (flags & 0x10000)) skip = true;
            if (!skip) {
                if (!(flags & 0x10000)) c = vis[3] + 1;
                float v = gridRect.y1 + mGrid.GetRowsExtent(mnFirstVisibleRow, c - mnFirstVisibleRow);
                if (v < yLim) yLim = v - 1.0f;
            }
        }
        flags = mGridFlags;
        if ((flags & 0x40) && mnRowGridColor != 0) {
            int c = mnColumnCount;
            bool skip = false;
            if (c == -1 && (flags & 0x8000)) skip = true;
            if (!skip) {
                if (!(flags & 0x8000)) c = vis[2] + 1;
                float v = gridRect.x1 + mGrid.GetColumnsExtent(mnFirstVisibleColumn, c - mnFirstVisibleColumn);
                if (v < xLim) xLim = v - 1.0f;
            }
        }
        cell.x1 = gridRect.x1;
        cell.x2 = cell.x1 + GetColumnWidthInternal(firstCol);
        int col = firstCol;
        int lastCol = colEnd - 1;
        if (col < lastCol) {
            do {
                if ((mGridFlags & 0x20) && mnColumnGridColor != 0) {
                    r->SetColor(mnColumnGridColor);
                    r->FillRect(cell.x2, gridRect.y1, mnColumnGridThickness + cell.x2, yLim);
                }
                if (col == firstCol) {
                    int row = firstRow;
                    cell.y1 = gridRect.y1;
                    cell.y2 = cell.y1 + GetRowHeightInternal(row);
                    int lastRow = rowEnd - 1;
                    if (row < lastRow) {
                        do {
                            if ((mGridFlags & 0x40) && mnRowGridColor != 0) {
                                r->SetColor(mnRowGridColor);
                                r->FillRect(gridRect.x1, cell.y2, xLim, mnRowGridThickness + cell.y2);
                            }
                            cell.y1 = cell.y2;
                            row++;
                            cell.y2 = cell.y2 + GetRowHeightInternal(row);
                        } while (row < lastRow);
                    }
                }
                col++;
                cell.x1 = cell.x2;
                cell.x2 = cell.x2 + GetColumnWidthInternal(col);
            } while (col < lastCol);
        }
    }

    Rect clip;
    int  range[4];
    mGrid.GetClipRect(&clip);
    mGrid.GetCellRange(range);

    Rect hdr;
    Rect clipOut;
    CellDrawArgs args;

    // column headings
    if (mGridFlags & 8) {
        for (int col = range[0]; col <= range[2]; col++) {
            if (mGrid.TestFlag(0x8000)) {
                if (mnColumnCount != -1 && col >= mnColumnCount) break;
            } else {
                if (col > vis[2]) break;
            }
            hdr.x1 = hdr.y1 = hdr.x2 = hdr.y2 = 0.0f;
            mGrid.GetColumnHeaderRect(col, &hdr);
            IntersectRect(clip, hdr, clipOut);
            if (hdr.x2 > gridRect.x2) clipOut.x2 = gridRect.x2;
            args.grid = &mGrid;
            args.col = col;
            args.row = -1;
            args.cellRect = &hdr;
            args.clipRect = &clipOut;
            args.gridRect = &gridRect;
            args.rc = rc;
            args.fmt = &mDefaultHeadingFormatting;
            args.highlighted = false;
            args.mouseOver = false;
            args.flag = true;
            DrawCellBackground(&args);
            WString* name = FindHeading(mColumnHeadings, col);
            if (!name) {
                if (mGridFlags & 0x100000) {
                    static WString sColumnName;
                    WStr_Format(&sColumnName, L"Column #%d", col);
                    DrawText(&sColumnName, &hdr, &args);
                }
            } else {
                DrawText(name, &hdr, &args);
            }
        }
    }

    // row headings
    if (mGridFlags & 0x10) {
        for (int row = range[1]; row <= range[3]; row++) {
            if (mGrid.TestFlag(0x10000)) {
                if (mnRowCount != -1 && row >= mnRowCount) break;
            } else {
                if (row > vis[3]) break;
            }
            hdr.x1 = hdr.y1 = hdr.x2 = hdr.y2 = 0.0f;
            mGrid.GetRowHeaderRect(row, &hdr);
            IntersectRect(clip, hdr, clipOut);
            if (hdr.y2 > gridRect.y2) clipOut.y2 = gridRect.y2;
            args.grid = &mGrid;
            args.col = -1;
            args.row = row;
            args.cellRect = &hdr;
            args.clipRect = &clipOut;
            args.gridRect = &gridRect;
            args.rc = rc;
            args.fmt = &mDefaultHeadingFormatting;
            args.highlighted = false;
            args.mouseOver = false;
            args.flag = true;
            DrawCellBackground(&args);
            WString* name = FindHeading(mRowHeadings, row);
            if (!name) {
                if (mGridFlags & 0x100000) {
                    static WString sRowName;
                    WStr_Format(&sRowName, L"Row #%d", row);
                    DrawText(&sRowName, &hdr, &args);
                }
            } else {
                DrawText(name, &hdr, &args);
            }
        }
    }

    // cell backgrounds
    if (mWinFlags & 0x20000) {
        int col = firstCol;
        cell.x1 = gridRect.x1;
        cell.x2 = cell.x1 + GetColumnWidthInternal(col);
        if (col < colEnd) {
            do {
                int row = firstRow;
                cell.y1 = gridRect.y1;
                cell.y2 = cell.y1 + GetRowHeightInternal(row);
                if (row < rowEnd) {
                    do {
                        mGrid.GetCellFormat(col, row, &fmt);
                        IntersectRect(gridRect, cell, clipOut);
                        args.cellRect = &cell;
                        args.clipRect = &clipOut;
                        args.gridRect = &gridRect;
                        args.rc = rc;
                        args.fmt = &fmt;
                        args.grid = &mGrid;
                        args.col = col;
                        args.row = row;
                        bool hl = mGrid.IsCellHighlighted(col, row);
                        args.highlighted = hl;
                        bool over;
                        if (mHitType == 5) {
                            if (mExtraDataType == 0) over = (col == mHitColumn);
                            else if (mExtraDataType == 1) over = (row == mHitRow) ? hl : false;
                            else over = (col == mHitColumn && row == mHitRow);
                        } else over = false;
                        args.mouseOver = over;
                        args.flag = true;
                        DrawCellBackground(&args);
                        cell.y1 = cell.y2;
                        row++;
                        cell.y2 = cell.y2 + GetRowHeightInternal(row);
                    } while (row < rowEnd);
                }
                col++;
                cell.x1 = cell.x2;
                cell.x2 = cell.x2 + GetColumnWidthInternal(col);
            } while (col < colEnd);
        }
    }

    // cells
    {
        int col = firstCol;
        cell.x1 = gridRect.x1;
        cell.x2 = cell.x1 + GetColumnWidthInternal(col);
        if (col < colEnd) {
            do {
                int row = firstRow;
                cell.y1 = gridRect.y1;
                cell.y2 = cell.y1 + GetRowHeightInternal(row);
                if (row < rowEnd) {
                    do {
                        IntersectRect(gridRect, cell, clipOut);
                        mGrid.GetCellFormat(col, row, &fmt);
                        args.cellData = FindCell(&mCellDataRows, col, row);
                        args.cellRect = &cell;
                        args.clipRect = &clipOut;
                        args.gridRect = &gridRect;
                        args.rc = rc;
                        args.fmt = &fmt;
                        args.grid = &mGrid;
                        args.col = col;
                        args.row = row;
                        bool hl = mGrid.IsCellHighlighted(col, row);
                        args.highlighted = hl;
                        bool over;
                        if (mHitType == 5) {
                            if (mExtraDataType == 0) over = (col == mHitColumn);
                            else if (mExtraDataType == 1) over = (row == mHitRow) ? hl : false;
                            else over = (col == mHitColumn && row == mHitRow);
                        } else over = false;
                        args.mouseOver = over;
                        args.flag = true;
                        DrawCell(&args);
                        cell.y1 = cell.y2;
                        row++;
                        cell.y2 = cell.y2 + GetRowHeightInternal(row);
                    } while (row < rowEnd);
                }
                col++;
                cell.x1 = cell.x2;
                cell.x2 = cell.x2 + GetColumnWidthInternal(col);
            } while (col < colEnd);
        }
    }

    if (mGridFlags & 0x400) {
        r->SetColor(mnOutlineColor);
        r->DrawRect(gridRect.x1, gridRect.y1, gridRect.x2, gridRect.y2, 1.0f);
    }
    if (mGridFlags & 0x200) {
        r->SetColor(mnOutlineColor);
        r->DrawRect(0.0f, 0.0f, mArea.x2 - mArea.x1, mArea.y2 - mArea.y1, 1.0f);
    }
    return true;
}
