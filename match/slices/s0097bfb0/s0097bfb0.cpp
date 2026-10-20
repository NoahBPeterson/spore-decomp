// Slice s0097bfb0: EA::UTFWinControls::WinGrid row/column room-making + cell setters.
// Module UTFSpore_Win32/Grid.obj (MSVC 2008 SP1, /O2 /arch:SSE /fp:fast).
//
// Real PDB names:
//   WinGrid::MakeRoom(int,int,int,int)             0x97bfb0
//   WinGrid::MakeRoomForRow(int,int,int)           0x97c4f0
//   WinGrid::MakeRoomForColumn(int,int,int)        0x97c580
//   WinGrid::GetColumnWidth(int,int)               0x97c630
//   WinGrid::GetRowHeight(int,int)                 0x97c680
//   WinGrid::Init()                                0x97c6d0
//   WinGrid::OnTick()                              0x97c6f0
//   WinGrid::DeleteColumns(int,int,int)            0x97c710
//   WinGrid::DeleteRows(int,int,int)               0x97c8c0
//   WinGrid::MakeCellVisible(int,int)              0x97ca70
//   WinGrid::SetCellTextValue(int,int,wchar_t*,void*,int,int)  0x97cae0
//   WinGrid::SetCellImage(int,int,void*,int)       0x97cd10
//
// Calling convention note: MakeRoom / MakeRoomForRow / MakeRoomForColumn / Init / OnTick are
// WinGrid *base* methods.  The IWinGrid subobject lives at WinGrid base + 0x20c and carries the
// virtual IWinGrid interface; DeleteColumns/DeleteRows/MakeCellVisible/SetCellTextValue/
// SetCellImage/GetColumnWidth/GetRowHeight are IWinGrid-subobject methods (base = this - 0x20c).
// The Window subobject vtable sits at base + 0x004 (= IWinGrid - 0x208); its slot 0x7c(8,1) is the
// "invalidate / mark dirty" notification.  All offsets are raw, taken from the disassembly.
#include "types.h"

// The scratch cell buffer is allocated with a checked array-new (count * sizeof(CellEntry),
// saturating at 0xffffffff on overflow); that is why the original emits mul/seto/neg/or around
// the allocation call.  A global placement array-new binds the 6-argument allocator.
struct CellEntry { int col; int row; void* cell; };                                        // 12 bytes
void* operator new[](unsigned size, const char* name, int a, int b, int c, int d) throw(); // 0xf473a0

namespace Gr {

#define GVT(o, i) ((*(void***)(o))[i])

template <class T> struct RectT { T left, top, right, bottom; };

// ---------------------------------------------------------------------------------------------
// Raw layouts (offsets from the disassembly)
// ---------------------------------------------------------------------------------------------
struct CellData {                 // 0x1c bytes, "UTFWin/Grid"
    int      mType;               // +0x00
    int      mCol;                // +0x04
    int      mRow;                // +0x08
    void*    mpWindow;            // +0x0c
    void*    mpText;              // +0x10
    int      pad14;               // +0x14
    int      pad18;               // +0x18
};

// eastl red-black tree node as used by the SparseMatrix maps (see slice s0097a130)
struct RBNode {
    RBNode* right;                // +0x00  (greater)
    RBNode* left;                 // +0x04  (smaller)
    RBNode* parent;               // +0x08
    int     color;                // +0x0c
    int     key;                  // +0x10
    int     pad14;                // +0x14
    void*   value;                // +0x18
};

struct FmtMatrix {                // SparseMatrix<CellFormatExtra>, at IWinGrid + 0xb4
    char pad0[0x0c];
    void* mRoot;                  // +0x0c
};

// SparseMatrix<CellData*>, at IWinGrid + 0x114 (= WinGrid base + 0x320).
// The map header sits at matrix + 0x04: anchor@+0x04, root@+0x0c.
struct SparseMatrixCells {
    char     pad0[0x0c];
    RBNode*  mRoot;               // +0x0c (== header.parent)

    bool GetCellPtr(int col, int row, void*** out);                  // 0x973a90, ret 0xc
    bool GetMinMaxUsedRowForCol(int col, int* pMin, int* pMax);      // 0x973800, ret 0xc
    bool GetMinMaxUsedColForRow(int row, int* pMin, int* pMax);      // 0x975350, ret 0xc
    bool IsCellUsed(int col, int row);                               // 0x973a40, ret 8
    int  GetMaxUsedColAndRow(int* out);                              // 0x973980, ret 4
    int  CountCellsInRange(int r1, int r2, int c1, int c2);          // 0x973b00, ret 0x10
    int  GetCellsInRange(int r1, int r2, int c1, int c2, int* buf);  // 0x973b90, ret 0x14
    int  GetCountForKey(int key);                                    // 0x9739e0, ret 4
    void RemoveCol(int col, int count);                              // 0x976a40, ret 8
    void RemoveRow(int row, int count);                              // 0x976980, ret 8
    void InsertCell(int col, int row, void** cell, int flag);        // 0x976f90, ret 0x10
};

// ---------------------------------------------------------------------------------------------
// External helpers.  The constructors and Window::Initialize are __thiscall in the original
// (ECX = object); MSVC refuses __thiscall on free functions, so they are declared as members of
// tiny stub classes and invoked through a cast of the raw object pointer.  The '// 0x' comments
// bind each declaration to its real address for the equivalence resolver.
// ---------------------------------------------------------------------------------------------
extern void* EAAllocate(unsigned size, const char* name, int a, int b, int c, int d);  // 0xf473a0
extern void  EAFree(void* p);                                                          // 0xf47380

struct WindowStub    { bool  Initialize();                                             // 0xb1fbf0
                     };
struct WStrStub      { void* WStr_Ctor(const wchar_t* s, void** alloc);                // 0x41df50
                     };
struct TextValueStub { void* TextValue_ctor(const wchar_t* s, void* font, void** alloc);  // 0x93d6f0
                     };

// ---------------------------------------------------------------------------------------------
// The full WinGrid object (only the members touched by this slice)
// ---------------------------------------------------------------------------------------------
struct WinGrid {
    char     pad0[0x004];
    void*    mWindowVtbl;             // +0x004 (Window subobject vtable)
    char     pad8[0x20c - 0x008];
    void*    mIfaceVtbl;              // +0x20c (IWinGrid subobject vtable)
    unsigned mGridFlags;              // +0x210
    bool     mbDirty;                 // +0x214
    char     pad215[0x264 - 0x215];
    int      mnColumnLimit;           // +0x264
    int      mnRowLimit;              // +0x268
    char     pad26c[0x320 - 0x26c];
    SparseMatrixCells mCells;         // +0x320

    float GetColumnWidthInternal(int col);                              // 0x979db0
    float GetRowHeightInternal(int row);                                // 0x979f10
    void  SetSizeCachedActualForRow(int row, int count, float h);       // 0x9789a0
    void  SetSizeCachedActualForColumn(int col, int count, float w);    // 0x978b50
    bool  CopyCellData(int srcCol, int srcRow, int dstCol, int dstRow, int deep);  // 0x979bc0
    void  DisposeOfCellData(int col, int row, void* cell, int deep);    // 0x975c50
    bool  RecalculateAll();                                             // 0x97bc80

    bool  MakeRoom(int col, int row, int amount, int dir);
    bool  MakeRoomForRow(int row, int amount, int dir);
    bool  MakeRoomForColumn(int col, int amount, int dir);
    bool  Init();
    bool  OnTick();
};

// ---------------------------------------------------------------------------------------------
// The IWinGrid subobject at WinGrid base + 0x20c
// ---------------------------------------------------------------------------------------------
struct WinGridIface {
    void*    vtbl;                // +0x000
    unsigned mGridFlags;          // +0x004
    bool     mbDirty;             // +0x008
    char     pad9[0x00c - 0x009];
    int      mPauseCount;         // +0x00c
    char     pad10[0x040 - 0x010];
    float    mfVisibleCellWidth;  // +0x040
    float    mfVisibleCellHeight; // +0x044
    int      mnFirstVisibleCol;   // +0x048
    int      mnFirstVisibleRow;   // +0x04c
    char     pad50[0x058 - 0x050];
    int      mnColLimit;          // +0x058
    int      mnRowLimit;          // +0x05c
    char     pad60[0x07c - 0x060];
    int      mLastCellCol;        // +0x07c
    int      mLastCellRow;        // +0x080
    char     pad84[0x0b4 - 0x084];
    FmtMatrix mColFormat;         // +0x0b4
    char     padFmt[0x114 - 0x0b4 - sizeof(FmtMatrix)];
    SparseMatrixCells mCells;     // +0x114
    char     padCells[0x230 - 0x114 - sizeof(SparseMatrixCells)];

    float GetColumnWidth(int start, int count);
    float GetRowHeight(int start, int count);
    bool  DeleteColumns(int start, int count, int dir);
    bool  DeleteRows(int start, int count, int dir);
    bool  MakeCellVisible(int col, int row);
    bool  SetCellTextValue(int col, int row, const wchar_t* text, void* font, int dir, bool flag);
    bool  SetCellImage(int col, int row, void* image, int dir);
};

inline WinGrid* Base(WinGridIface* p) { return (WinGrid*)((char*)p - 0x20c); }
inline void*    Window(WinGridIface* p) { return (char*)p - 0x208; }

static void MarkDirtyIface(WinGridIface* ig)
{
    void* w = (char*)ig - 0x208;
    ig->mbDirty = true;
    ((void(__thiscall*)(void*, int, int))GVT(w, 0x7c / 4))(w, 8, 1);
}

// =============================================================================================
// @ 0x0097bfb0  EA::UTFWinControls::WinGrid::MakeRoom
//   Shifts cell data to open `amount` cells at (col,row) in one of five directions.
//   amount > 0 always widens the used range; amount < 0 shrinks it.
// =============================================================================================
bool WinGrid::MakeRoom(int col, int row, int amount, int dir)
{
    if (dir == 0)
        dir = 1;

    switch (dir - 1) {
    case 0:                                   // dir == 1: erase a single cell
        if (amount > 0) {
            SetSizeCachedActualForRow(row, 1, -1.0f);
            void** cell = 0;
            if (mCells.GetCellPtr(col, row, &cell)) {
                DisposeOfCellData(col, row, *cell, 1);
                *cell = 0;
            }
        }
        break;

    case 1:                                   // dir == 2: shift row contents left/right
        if (amount >= 1) {
            SetSizeCachedActualForRow(row, 1, -1.0f);
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedColForRow(row, &mn, &mx)) {
                int t = mn - amount;
                int start = (t < 0) ? 0 : t;
                for (int i = start; i <= col - 1; ++i) {
                    SetSizeCachedActualForColumn(i, 1, -1.0f);
                    CopyCellData(i + amount, row, i, row, 0);
                }
            }
        } else if (amount < 0) {
            amount = -amount;
            SetSizeCachedActualForRow(row, 1, -1.0f);
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedColForRow(row, &mn, &mx)) {
                int i = col + amount;
                if (i <= mx) {
                    int d = i - amount;
                    do {
                        SetSizeCachedActualForColumn(i, 1, -1.0f);
                        CopyCellData(i, row, d, row, 0);
                        ++i; ++d;
                    } while (i <= mx);
                }
            }
        }
        break;

    case 2:                                   // dir == 3: shift column contents up/down
        if (amount >= 1) {
            SetSizeCachedActualForRow(row, 1, -1.0f);
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedRowForCol(col, &mn, &mx)) {
                int t = mx - amount;
                int start = (t < 0) ? 0 : t;
                for (int i = start; i <= row - 1; ++i) {
                    SetSizeCachedActualForRow(i, 1, -1.0f);
                    CopyCellData(col, i + amount, col, i, 0);
                }
            }
        } else if (amount < 0) {
            amount = -amount;
            SetSizeCachedActualForRow(row, 1, -1.0f);
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedRowForCol(col, &mn, &mx)) {
                int i = row + amount;
                if (i <= mx) {
                    int d = i - amount;
                    do {
                        SetSizeCachedActualForRow(i, 1, -1.0f);
                        CopyCellData(col, i, col, d, 0);
                        ++i; ++d;
                    } while (i <= mx);
                }
            }
        }
        break;

    case 3:                                   // dir == 4: open room for columns, right-anchored
        if (amount >= 1) {
            SetSizeCachedActualForRow(row, 1, -1.0f);
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedColForRow(row, &mn, &mx)) {
                int t = amount + mx;
                if (mnColumnLimit != -1 && t > mnColumnLimit)
                    t = mnColumnLimit;
                if (t >= col) {
                    int d = t - amount;
                    for (int i = t; i >= col; --i, --d) {
                        SetSizeCachedActualForColumn(i, 1, -1.0f);
                        CopyCellData(d, row, i, row, 0);
                    }
                }
            }
        } else if (amount < 0) {
            amount = -amount;
            SetSizeCachedActualForRow(row, 1, -1.0f);
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedColForRow(row, &mn, &mx)) {
                for (int i = col - 1; i >= mn; --i) {
                    SetSizeCachedActualForColumn(i, 1, -1.0f);
                    CopyCellData(i, row, i + amount, row, 0);
                }
            }
        }
        break;

    case 4:                                   // dir == 5: open room for rows, bottom-anchored
        if (amount >= 1) {
            SetSizeCachedActualForRow(row, 1, -1.0f);
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedRowForCol(col, &mn, &mx)) {
                int t = amount + mx;
                if (mnRowLimit != -1 && t > mnRowLimit)
                    t = mnRowLimit;
                if (t >= row) {
                    int d = t - amount;
                    for (int i = t; i >= row; --i, --d) {
                        SetSizeCachedActualForRow(i, 1, -1.0f);
                        CopyCellData(col, d, col, i, 0);
                    }
                }
            }
        } else if (amount < 0) {
            amount = -amount;
            SetSizeCachedActualForRow(row, 1, -1.0f);
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedRowForCol(col, &mn, &mx)) {
                for (int i = row - 1; i >= mn; --i) {
                    SetSizeCachedActualForRow(i, 1, -1.0f);
                    CopyCellData(col, i, col, i + amount, 0);
                }
            }
        }
        break;

    default:
        return false;
    }

    mbDirty = true;
    ((void(__thiscall*)(void*, int, int))GVT((char*)this + 4, 0x7c / 4))((char*)this + 4, 8, 1);
    return true;
}

// =============================================================================================
// @ 0x0097c4f0  EA::UTFWinControls::WinGrid::MakeRoomForRow
// =============================================================================================
bool WinGrid::MakeRoomForRow(int row, int amount, int dir)
{
    if (dir == 0)
        dir = 3;
    else if (dir != 1 && dir != 3 && dir != 5)
        return false;

    RectT<int> r;
    if (!((bool(__thiscall*)(void*, RectT<int>*))GVT((char*)this + 0x20c, 0xc4 / 4))((char*)this + 0x20c, &r))
        return true;

    for (int col = r.left; col <= r.right; ++col) {
        if (mCells.GetCountForKey(col) != 0)
            MakeRoom(col, row, amount, dir);
    }
    return true;
}

// =============================================================================================
// @ 0x0097c580  EA::UTFWinControls::WinGrid::MakeRoomForColumn
// =============================================================================================
bool WinGrid::MakeRoomForColumn(int col, int amount, int dir)
{
    if (dir == 0)
        dir = 2;
    else if (dir != 1 && dir != 2 && dir != 4)
        return false;

    RectT<int> r;
    if (!((bool(__thiscall*)(void*, RectT<int>*))GVT((char*)this + 0x20c, 0xc4 / 4))((char*)this + 0x20c, &r))
        return true;

    RBNode* anchor = (RBNode*)((char*)&mCells + 4);
    for (int row = r.top; row <= r.bottom; ++row) {
        RBNode* best = anchor;
        RBNode* n = anchor->parent;
        while (n) {
            if (n->key < row) {
                n = n->right;
            } else {
                best = n;
                n = n->left;
            }
        }
        if (best != anchor && row >= best->key && *(void**)((char*)best + 0x2c) != 0)
            MakeRoom(col, row, amount, dir);
    }
    return true;
}

// =============================================================================================
// @ 0x0097c630  EA::UTFWinControls::WinGrid::GetColumnWidth
// =============================================================================================
float WinGridIface::GetColumnWidth(int start, int count)
{
    float sum = 0.0f;
    if (count > 0) {
        WinGrid* base = Base(this);
        do {
            --count;
            sum = base->GetColumnWidthInternal(start) + sum;
            ++start;
        } while (count > 0);
    }
    return sum;
}

// =============================================================================================
// @ 0x0097c680  EA::UTFWinControls::WinGrid::GetRowHeight
// =============================================================================================
float WinGridIface::GetRowHeight(int start, int count)
{
    float sum = 0.0f;
    if (count > 0) {
        WinGrid* base = Base(this);
        do {
            --count;
            sum = base->GetRowHeightInternal(start) + sum;
            ++start;
        } while (count > 0);
    }
    return sum;
}

// =============================================================================================
// @ 0x0097c6d0  EA::UTFWinControls::WinGrid::Init
// =============================================================================================
bool WinGrid::Init()
{
    if (((WindowStub*)this)->Initialize())
        return RecalculateAll();
    return false;
}

// =============================================================================================
// @ 0x0097c6f0  EA::UTFWinControls::WinGrid::OnTick
// =============================================================================================
bool WinGrid::OnTick()
{
    if (mbDirty)
        RecalculateAll();
    return false;
}

// =============================================================================================
// @ 0x0097c710  EA::UTFWinControls::WinGrid::DeleteColumns
// =============================================================================================
bool WinGridIface::DeleteColumns(int start, int count, int dir)
{
    if (dir == 0)
        dir = 2;
    else if (dir != 2 && dir != 4 && dir != 1)
        dir = 1;

    if (count < 0)
        return false;
    if (count < 1)
        return true;

    int end = start - 1 + count;
    CellEntry* buf = new ("UTFWin/Grid", 0, 0, 0, 0)
        CellEntry[mCells.CountCellsInRange(start, end, 0, 0x7fffffff)];
    if (buf) {
        int got = mCells.GetCellsInRange(start, end, 0, 0x7fffffff, (int*)buf);
        if (got > 0) {
            CellEntry* p = buf;
            for (int k = got; k != 0; --k, ++p)
                Base(this)->DisposeOfCellData(p->col, p->row, p->cell, 1);
        }
        EAFree(buf);
    }
    mCells.RemoveCol(start, count);

    switch (dir) {
    case 1:  Base(this)->SetSizeCachedActualForColumn(start, 1, -1.0f);          break;
    case 2:  Base(this)->SetSizeCachedActualForColumn(start, 0x7fffffff, -1.0f); break;
    case 4:  Base(this)->SetSizeCachedActualForColumn(0, start + 1, -1.0f);      break;
    }
    if (dir == 2 || dir == 4)
        Base(this)->MakeRoomForColumn(start, -count, dir);
    MarkDirtyIface(this);
    return true;
}

// =============================================================================================
// @ 0x0097c8c0  EA::UTFWinControls::WinGrid::DeleteRows
// =============================================================================================
bool WinGridIface::DeleteRows(int start, int count, int dir)
{
    if (dir == 0)
        dir = 3;
    else if (dir != 3 && dir != 5 && dir != 1)
        dir = 1;

    if (count < 0)
        return false;
    if (count < 1)
        return true;

    int end = start - 1 + count;
    CellEntry* buf = new ("UTFWin/Grid", 0, 0, 0, 0)
        CellEntry[mCells.CountCellsInRange(0, 0x7fffffff, start, end)];
    if (buf) {
        int got = mCells.GetCellsInRange(0, 0x7fffffff, start, end, (int*)buf);
        if (got > 0) {
            CellEntry* p = buf;
            for (int k = got; k != 0; --k, ++p)
                Base(this)->DisposeOfCellData(p->col, p->row, p->cell, 1);
        }
        EAFree(buf);
    }
    mCells.RemoveRow(start, count);

    switch (dir) {
    case 1:  Base(this)->SetSizeCachedActualForRow(start, 1, -1.0f);          break;
    case 3:  Base(this)->SetSizeCachedActualForRow(start, 0x7fffffff, -1.0f); break;
    case 5:  Base(this)->SetSizeCachedActualForRow(0, start + 1, -1.0f);      break;
    }
    if (dir == 3 || dir == 5)
        Base(this)->MakeRoomForRow(start, -count, dir);
    MarkDirtyIface(this);
    return true;
}

// =============================================================================================
// @ 0x0097ca70  EA::UTFWinControls::WinGrid::MakeCellVisible
// =============================================================================================
bool WinGridIface::MakeCellVisible(int col, int row)
{
    if (mbDirty)
        Base(this)->RecalculateAll();

    if (!((bool(__thiscall*)(void*, int, int))GVT(this, 0x184 / 4))(this, col, row)) {
        ((void(__thiscall*)(void*, int))GVT(this, 0x78 / 4))(this, row - mnFirstVisibleRow);
        if (!((bool(__thiscall*)(void*, int, int))GVT(this, 0x184 / 4))(this, col, row))
            ((void(__thiscall*)(void*, int))GVT(this, 0x7c / 4))(this, col - mnFirstVisibleCol);
    }
    return true;
}

// =============================================================================================
// @ 0x0097cae0  EA::UTFWinControls::WinGrid::SetCellTextValue
// =============================================================================================
bool WinGridIface::SetCellTextValue(int col, int row, const wchar_t* text, void* font, int dir, bool flag)
{
    int local = 0;
    bool ok;
    if (col == 0x7fffffff || row == 0x7fffffff)
        ok = false;
    else
        ok = ((bool(__thiscall*)(void*, int, int, int*))GVT(this, 0x1b0 / 4))(this, col, row, &local);

    if (dir == 0)
        dir = 1;
    if (flag)
        return true;
    if (ok && local != 0)
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);

    if (col == 0x7fffffff) {
        if (row == 0x7fffffff) {
            col = mCells.GetMaxUsedColAndRow(&local);
            if (col == (int)0x80000000) {
                col = 0;
                goto resolveRow;
            }
            if (col != 0x7fffffff)
                goto resolveRow;
        }
        {
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedColForRow(row, &mn, &mx))
                col = mx + 1;
            else
                col = 0;
        }
    }

    if (row == 0x7fffffff) {
    resolveRow:
        int mn = 0, mx = 0;
        if (mCells.GetMinMaxUsedRowForCol(col, &mn, &mx))
            row = mx + 1;
        else
            row = 0;
    }

    if (!((bool(__thiscall*)(void*, int, int))GVT(this, 0xd4 / 4))(this, col, row)) {
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);
        return true;
    }

    if (text == 0) {
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);
        mLastCellCol = col;
        mLastCellRow = row;
        return true;
    }

    void* textObj = EAAllocate(0x10, "UTFWin/Grid", 0, 0, 0, 0);
    void* alloc;
    if (font != 0) {
        if (textObj != 0)
            textObj = ((TextValueStub*)textObj)->TextValue_ctor(text, font, &alloc);
    } else {
        if (textObj != 0)
            textObj = ((WStrStub*)textObj)->WStr_Ctor(text, &alloc);
    }

    if (textObj != 0) {
        CellData* cd = (CellData*)EAAllocate(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
        if (cd != 0) {
            cd->mType = 2;
            cd->mCol = col;
            cd->mRow = row;
            cd->mpWindow = textObj;
            cd->mpText = 0;
            cd->pad14 = 0;
            cd->pad18 = 0;
            Base(this)->MakeRoom(col, row, 1, dir);
            mCells.InsertCell(col, row, (void**)&cd, 0);
        }
    }

    MarkDirtyIface(this);
    mLastCellCol = col;
    mLastCellRow = row;
    return true;
}

// =============================================================================================
// @ 0x0097cd10  EA::UTFWinControls::WinGrid::SetCellImage
// =============================================================================================
bool WinGridIface::SetCellImage(int col, int row, void* image, int dir)
{
    if (dir == 0)
        dir = 1;

    int local = 0;
    if (col == 0x7fffffff) {
        if (row == 0x7fffffff) {
            col = mCells.GetMaxUsedColAndRow(&local);
            if (col == (int)0x80000000) {
                col = 0;
                goto resolveRow;
            }
            if (col != 0x7fffffff)
                goto resolveRow;
        }
        {
            int mn = 0, mx = 0;
            if (mCells.GetMinMaxUsedColForRow(row, &mn, &mx))
                col = mx + 1;
            else
                col = 0;
        }
    }

    if (row == 0x7fffffff) {
    resolveRow:
        int mn = 0, mx = 0;
        if (mCells.GetMinMaxUsedRowForCol(col, &mn, &mx))
            row = mx + 1;
        else
            row = 0;
    }

    if (!((bool(__thiscall*)(void*, int, int))GVT(this, 0xd4 / 4))(this, col, row)) {
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);
        return false;
    }

    if (mCells.IsCellUsed(col, row))
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);

    if (image != 0) {
        CellData* cd = (CellData*)EAAllocate(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
        if (cd != 0) {
            cd->mType = 4;
            cd->mCol = col;
            cd->mRow = row;
            cd->mpWindow = image;
            cd->mpText = 0;
            cd->pad14 = 0;
            cd->pad18 = 0;
            ((void(__thiscall*)(void*))GVT(image, 0))(image);
            Base(this)->MakeRoom(col, row, 1, dir);
            mCells.InsertCell(col, row, (void**)&cd, 0);
        }
        MarkDirtyIface(this);
    }

    mLastCellCol = col;
    mLastCellRow = row;
    return true;
}

} // namespace Gr
