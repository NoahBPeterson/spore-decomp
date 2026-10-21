// slice s00979bc0 -- EA::UTFWinControls::WinGrid (UTFSpore_Win32/Grid.obj)
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Real PDB names:
//   WinGrid::CopyCellData(int,int,int,int,bool)   0x979bc0
//   WinGrid::GetColumnWidthInternal(int)          0x979db0
//   WinGrid::GetRowHeightInternal(int)            0x979f10
//
// All three are ordinary (non-virtual) member functions: `this` is the WinGrid base object
// in ECX, and they use `ret 4` (one stack argument).  Offsets are raw, straight from the
// original disassembly:
//   mfVisibleColumnWidth     +0x250   (column width in pixels, the "row block" numerator)
//   mnColumnCount            +0x264
//   mnRowCount               +0x268
//   mnColumnGridThickness    +0x26c
//   mnRowGridThickness       +0x270
//   mColFormats              +0x2c0   SparseMatrix<CellFormatExtra>
//   mRowFormats              +0x2f0   SparseMatrix<CellFormatExtra>
//   mCells                   +0x320   SparseMatrix<CellData*>
typedef unsigned int   uint32;
typedef unsigned char  uint8_t;
typedef unsigned short wchar_t_;

// ---------------------------------------------------------------------------------------------
// eastl::rbtree node + SparseMatrix (2-level tree: outer key = row, inner key = col)
// ---------------------------------------------------------------------------------------------
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; int color; };

struct RBTree {                 // eastl rbtree header (0x1c bytes): allocator, then the anchor
    int     mAllocator;
    RBNode  anchor;             // right = rightmost, left = leftmost(begin), parent = root
    int     mnSize;
    void Find(void** out, const void* key);   // 0xe39fb0 (eastl::rbtree::find)
};

struct InNode  { RBNode b; int f14; void* f18; };   // inner node: col @ +0x14, value @ +0x18
struct OutNode { RBNode b; int f10; int f14; RBTree inner; };  // outer node: row @ +0x14

struct CellFormatExtra {        // 0x38 bytes stored inline after the InNode value slot
    uint32  nTextStyle;         // +0x00
    uint32  nColor[8];          // +0x04
    uint8_t nWrapping, nHAlignment, nVAlignment, pad;  // +0x24
    uint32  nBorder;            // +0x28
    uint32  nBorderColor;       // +0x2c
    float   nSizeDefault;       // +0x30
    float   nSizeCachedActual;  // +0x34
};

struct CellData {               // 0x1c bytes, allocated "UTFWin/Grid"
    int      mType;             // +0x00
    int      mCol;              // +0x04
    int      mRow;              // +0x08
    void*    mpWindow;          // +0x0c
    int      pad10;             // +0x10
    int      pad14;             // +0x14
    unsigned mFlags;            // +0x18
};

struct SparseMatrix {           // header is 0x30 bytes
    RBTree t;
    char   pad18[0x30 - 0x18];

    int  GetCountForKey(int key);                                   // 0x9739e0, ret 4
    bool GetCellPtr(int col, int row, void*** out);                 // 0x973a90, ret 0xc
    int  GetCellsInRange(int a, int b, int c, int d, int* out);      // 0x973b90, ret 0x14
    void InsertCell(int col, int row, void** v, int flag);           // 0x976f90, ret 0x10
    bool RemoveCell(int col, int row, void** out);                   // 0x9768e0, ret 0xc
};

void* __cdecl EAAllocate(uint32 size, const char* name, int, int, int, int);  // 0xf473a0
void  __cdecl EAOperatorDelete(void* p);                                      // 0xf47380
void* operator new(size_t size, const char* name, int, int, int, int);
void* operator new[](size_t size, const char* name, int, int, int, int);
#define NEW_G(T) new ("UTFWin/Grid", 0, 0, 0, 0) T
#define NEW_GA(n) new ("UTFWin/Grid", 0, 0, 0, 0) char[(n)]

// ---------------------------------------------------------------------------------------------
// The WinGrid object (only the members touched by this slice)
// ---------------------------------------------------------------------------------------------
struct WinGrid {
    char   pad0[0x250];
    float  mfVisibleColumnWidth;    // +0x250
    char   pad254[0x264 - 0x254];
    int    mnColumnCount;           // +0x264
    int    mnRowCount;              // +0x268
    float  mnColumnGridThickness;   // +0x26c
    float  mnRowGridThickness;      // +0x270
    char   pad274[0x2c0 - 0x274];
    SparseMatrix mColFormats;       // +0x2c0  SparseMatrix<CellFormatExtra>
    SparseMatrix mRowFormats;       // +0x2f0  SparseMatrix<CellFormatExtra>
    SparseMatrix mCells;            // +0x320  SparseMatrix<CellData*>

    float CalculateCellWidth(int col, int row, void* cell);         // 0x975180, ret 0xc
    float CalculateCellHeight(int col, int row, void* cell);        // 0x974fc0, ret 0xc
    void  DisposeOfCellData(int col, int row, CellData* cell, bool deep);  // 0x975c50, ret 0x10
    void  DoCellWindowMove(int* msg);                               // 0x973330
    void  CopyCellData(int c1, int r1, CellData* src, int c2, int r2, CellData* dst); // 0x976010
    void  SetSizeCachedActualForColumn(int start, int count, float v);  // 0x978b50, ret 0xc
    void  SetSizeCachedActualForRow(int start, int count, float v);     // 0x9789a0, ret 0xc

    bool  CopyCellData(int srcCol, int srcRow, int dstCol, int dstRow, bool deep);  // 00979bc0
    float GetColumnWidthInternal(int col);                                          // 00979db0
    float GetRowHeightInternal(int row);                                            // 00979f10
};

float g_negOne = -1.0f;   // the +0x13eb1bc / +0x1442bc4 style constant pool entries

// ---------------------------------------------------------------------------------------------
// Virtual interface at WinGrid + 0x20c.  Only the two slots used here are named.
// ---------------------------------------------------------------------------------------------
struct IWinGridSlots {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual bool IsCellUsed(int col, int row);   // +0xd4 slot 53
    virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
    virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61();
    virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65();
    virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
    virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73();
    virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77();
    virtual void v78(); virtual void v79(); virtual void v80(); virtual void v81();
    virtual void v82(); virtual void v83(); virtual void v84(); virtual void v85();
    virtual void v86(); virtual void v87(); virtual void v88();
    virtual void EraseCell(int col, int row);   // +0x164 slot 89
};

#define IFACE(g) ((IWinGridSlots*)((char*)(g) + 0x20c))

// @ 0x00979bc0
bool WinGrid::CopyCellData(int srcCol, int srcRow, int dstCol, int dstRow, bool deep)
{
    if (!IFACE(this)->IsCellUsed(srcCol, srcRow))
        return false;
    if (srcCol == dstCol && srcRow == dstRow)
        return true;
    CellData* old = 0;
    if (!IFACE(this)->IsCellUsed(dstCol, dstRow)) {
        if (!deep)
            IFACE(this)->EraseCell(srcCol, srcRow);
        return true;
    }
    if (deep) {
        if (mCells.GetCellPtr(srcCol, srcRow, (void***)&old))
            old = *(CellData**)old;
    } else {
        mCells.RemoveCell(srcCol, srcRow, (void**)&old);
    }
    if (old == 0) {
        IFACE(this)->EraseCell(dstCol, dstRow);
        return true;
    }
    CellData* cell = 0;
    if (mCells.GetCellPtr(dstCol, dstRow, (void***)&cell))
        cell = *(CellData**)cell;
    else {
        cell = (CellData*)EAAllocate(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
        if (cell) {
            cell->mType = 0; cell->mCol = 0; cell->mRow = 0;
            cell->mpWindow = 0; cell->pad10 = 0; cell->pad14 = 0; cell->mFlags = 0;
        }
        mCells.InsertCell(dstCol, dstRow, (void**)&cell, 0);
    }
    if (deep) {
        CopyCellData(srcCol, srcRow, old, dstCol, dstRow, cell);
    } else {
        DisposeOfCellData(dstCol, dstRow, cell, false);
        *cell = *old;
        cell->mCol = dstCol;
        cell->mRow = dstRow;
        if (cell->mType == 1)
            DoCellWindowMove((int*)cell);
        EAOperatorDelete(old);
    }
    return true;
}

// @ 0x00979db0
float WinGrid::GetColumnWidthInternal(int colArg)
{
    int col = colArg;
    CellFormatExtra* fmt;
    float best;
    if (mColFormats.GetCellPtr(col, 0, (void***)&fmt)) {
        if (fmt->nSizeDefault != g_negOne)
            return fmt->nSizeDefault;
        if (fmt->nSizeCachedActual != g_negOne)
            return fmt->nSizeCachedActual;
    } else if (mCells.GetCountForKey(col) == 0) {
        return mnColumnGridThickness;
    }
    best = mnColumnGridThickness;
    int count = mCells.GetCountForKey(col);
    if (count != 0) {
        int* cells = (int*)NEW_GA(count * 0xc);
        if (cells) {
            count = mCells.GetCellsInRange(col, col, 0x80000000, 0x7fffffff, cells);
            if (count > 0) {
                int* it = cells + 1;
                do {
                    float w = CalculateCellWidth(it[-1], it[0], (void*)it[1]);
                    if (!(best >= w))
                        best = w;
                    it += 3;
                } while (--count);
            }
            EAOperatorDelete(cells);
        }
    }
    SetSizeCachedActualForColumn(col, 1, best);
    return best;
}

// @ 0x00979f10
float WinGrid::GetRowHeightInternal(int row)
{
    float h = mnRowGridThickness;
    int nRows = mnRowCount;
    if (nRows != 0 && nRows != -1)
        h = mfVisibleColumnWidth / (float)nRows;
    CellFormatExtra* fmt;
    if (mRowFormats.GetCellPtr(0, row, (void***)&fmt)) {
        if (fmt->nSizeDefault != g_negOne)
            return fmt->nSizeDefault;
        if (fmt->nSizeCachedActual != g_negOne)
            return fmt->nSizeCachedActual;
    } else {
        RBNode* it;
        mCells.t.Find((void**)&it, &row);
        if (it == (RBNode*)((char*)&mCells.t + 4) || *(int*)((char*)it + 0x2c) == 0)
            return mnRowGridThickness;
    }
    int count = 0;
    {
        RBNode* it;
        mCells.t.Find((void**)&it, &row);
        if (it != (RBNode*)((char*)&mCells.t + 4))
            count = *(int*)((char*)it + 0x2c);
    }
    if (count <= 0) {
        SetSizeCachedActualForRow(row, 1, h);
        return h;
    }
    int* cells = (int*)EAAllocate((uint32)(count * 0xc), "UTFWin/Grid", 0, 0, 0, 0);
    if (cells) {
        count = mCells.GetCellsInRange(0x80000000, 0x7fffffff, row, row, cells);
        if (count > 0) {
            int* it = cells + 1;
            do {
                float v = CalculateCellHeight(it[-1], it[0], (void*)it[1]);
                if (!(h >= v))
                    h = v;
                it += 3;
            } while (--count);
        }
        EAOperatorDelete(cells);
    }
    SetSizeCachedActualForRow(row, 1, h);
    return h;
}
