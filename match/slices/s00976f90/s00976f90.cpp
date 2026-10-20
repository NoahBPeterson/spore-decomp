// Slice s00976f90: EA::UTFWinControls::WinGrid ctor/dtor, default-format setters,
// sparse-matrix InsertCell and column width.
// Module UTFSpore_Win32/Grid.obj (MSVC 2008 SP1).
// Flags (neighbour manifest, UTFWin region): /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast

typedef unsigned int size_t;
typedef unsigned char byte;
typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Shared types (see slice s00975ea0 for the full grid object model).
// ---------------------------------------------------------------------------

struct RBN {                     // eastl node base: right, left, parent, colour
    RBN* right;                  // +0x00
    RBN* left;                   // +0x04
    RBN* parent;                 // +0x08
    int  color;                  // +0x0c
};

struct WString {                 // eastl::basic_string<wchar_t> object, 0x10 bytes
    void* mpBegin;               // +0x00
    void* mpEnd;                 // +0x04
    void* mpCap;                 // +0x08
};

struct CellData {                // 0x1c bytes, "UTFWin/Grid"
    int      mType;              // +0x00
    int      mCol;               // +0x04
    int      mRow;               // +0x08
    void*    mpWindow;           // +0x0c
    int      pad10;              // +0x10
    int      pad14;              // +0x14
    unsigned mFlags;             // +0x18
};

// 0x38-byte CellFormatExtra value.
struct FmtExtra {
    int f[0xe];
};

// 0x18-byte MatrixRow<CellData*>.
struct MatrixRow {
    char   alloc[4];             // +0x00
    RBN    anchor;               // +0x04
    int    mnSize;               // +0x14
    void   f(void* value);                        // 0x009a9600
    void   CtorFrom(const int* src);              // 0x009755a0
};

// 0x1c-byte MatrixRow<CellFormatExtra>.
struct MatrixRowC {
    char   alloc[4];
    RBN    anchor;
    int    mnSize;
    int    pad18;
    void   f(void* value);                        // 0x009a9600
    void   CtorFrom(const int* src);              // 0x00975610
};

// Outer row node: {RBN, int key@0x10, pad, cell row@0x18}.
struct RowNode {
    RBN  base;                   // +0x00
    int  key;                    // +0x10
    int  pad14;                  // +0x14
    byte row[0x18];              // +0x18 -> MatrixRow (CD) or MatrixRowC (CF)
};

// Inner node: {RBN, int key@0x10, pad, value@0x18}.
struct ColNode {
    RBN   base;
    int   key;
    int   pad14;
    void* value;                 // +0x18
};

// eastl::rbtree find (ret 8).
struct TreeHdr {
    char alloc[4];               // +0x00
    RBN  anchor;                 // +0x04
    int  mnSize;                 // +0x14
    void Find(RBN** out, const int* key);                    // 0x00e39fb0
};

// SparseMatrix<CellData*> view (CellsMatrix, WinGrid+0x320).
struct CellsMatrix {
    char alloc[4];               // +0x00
    RBN  anchor;                 // +0x04
    int  mnSize;                 // +0x14
    int  pad18;                  // +0x18
    int  mnTotalCells;           // +0x1c
    int  mnMinCol;               // +0x20
    int  mnMaxCol;               // +0x24
    int  mnMinRow;               // +0x28
    int  mnMaxRow;               // +0x2c
    bool InsertCell(int col, int row, void* value, void** out); // 0x00976f90
};

// SparseMatrix<CellFormatExtra> view (FmtMatrix, WinGrid+0xb4).
struct FmtTree {
    char alloc[4];               // +0x00
    RBN  anchor;                 // +0x04
    int  mnSize;                 // +0x14
    int  pad18;                  // +0x18
    int  mnTotalCells;           // +0x1c
    int  mnMinCol;               // +0x20
    int  mnMaxCol;               // +0x24
    int  mnMinRow;               // +0x28
    int  mnMaxRow;               // +0x2c
    void Find(RBN** out, const int* key);                    // 0x00e39fb0
};

extern "C" void* __cdecl EAAllocate(unsigned size, const char* tag, int a, int b, const char* file, int line);
extern "C" void  __cdecl EaFree(void* p);

// Helpers living in neighbouring slices (declared, never defined here).
RBN*  MakeRowNode(int row);                                          // 0x009753c0
void  RowTreeInsertCD(RBN** out, const int* key, const void* value); // 0x00976b90
bool  InsertCellFmt(FmtTree* self, int col, int row, const FmtExtra* value, FmtExtra* out); // 0x00976dd0
void  FmtInsertLeaf(FmtTree* self, RBN** out, const int* key, const void* value); // 0x00975dd0
bool  WindowShutdown(void* self);                                    // 0x00961e80
void  RecalcAll(void* self);                                         // 0x00962740

// ---------------------------------------------------------------------------
// WinGrid object: primary vtable at +0, IWindow secondary vptr at +4, IWinGrid
// sub-object vtable at +0x20c.  Only the offsets used by this slice are named;
// the rest is opaque padding reached through byte pointers.
// ---------------------------------------------------------------------------
struct WinGrid {
    char     pad0[0x004];
    char     pad4[0x0b4 - 0x004];
    FmtTree  mFmtRow;            // +0x0b4   (default row formatting matrix)
    char     padToIface[0x20c - 0x0b4 - sizeof(FmtTree)];
    char     iface[0x320 - 0x20c];  // IWinGrid sub-object (vptr at +0x20c)
    CellsMatrix mCells;          // +0x320
    char     padAfterCells[0x3f8 - 0x320 - sizeof(CellsMatrix)];
    void*    mSound[4];          // +0x3f8 .. +0x404
    char     padTail[0x9d0 - 0x408];

    // methods
    WinGrid* Ctor(void* a2, void* a3);                  // 0x009770e0
    void     Dtor(unsigned flags);                      // 0x00977600
    void     DisposeOfAllCellData();                    // 0x00976d20
    bool     WindowShutdown();                          // 0x00961e80
    bool     Shutdown();                                // 0x009777c0
    bool     SetDefaultTextColorByColumns(uint i, int start, int count, uint color); // 0x00977830
    bool     SetDefaultTextColorByRows(uint i, int start, int count, uint color);    // 0x00977970
    bool     SetDefaultAlignmentByColumns(uint i, int start, int count, uint value); // 0x00977ab0
    bool     SetDefaultAlignmentByRows(uint i, int start, int count, uint value);    // 0x00977be0
    bool     SetColumnWidth(int start, int count, float width);                      // 0x00977d10
};

inline byte* B(void* p) { return (byte*)p; }

// ===========================================================================
// @ 0x00976f90  SparseMatrix<CellData*>::InsertCell
//   bool InsertCell(int col, int row, const CellData* value, CellData** out)
// ===========================================================================
bool CellsMatrix::InsertCell(int col, int row, void* value, void** out)
{
    if (row < mnMinRow || col < mnMinCol || row > mnMaxRow || col > mnMaxCol)
        return false;

    RBN* rowNode;
    ((TreeHdr*)this)->Find(&rowNode, &row);
    if (rowNode != &anchor) {
        RowNode* rn = (RowNode*)rowNode;
        RBN* inner;
        ((TreeHdr*)rn->row)->Find(&inner, &col);
        if (inner != (RBN*)(rn->row + 0x1c)) {
            if (out)
                *out = *(void**)(inner + 0x18);
            *(void**)(inner + 0x18) = value;
            return true;
        }
        // new column inside an existing row
        FmtExtra tmp;
        ((int*)&tmp)[0] = col;
        ((int*)&tmp)[1] = col;
        ((void**)((byte*)&tmp + 8))[0] = *(void**)value;
        FmtInsertLeaf((FmtTree*)rn->row, &inner, &col, &tmp);
        ++mnTotalCells;
        return true;
    }

    // new row
    RBN* inserted;
    RowTreeInsertCD(&inserted, &row, (void*)value);
    FmtExtra tmp;
    ((int*)&tmp)[0] = col;
    ((int*)&tmp)[1] = col;
    ((void**)((byte*)&tmp + 8))[0] = *(void**)value;
    RBN* inner;
    FmtInsertLeaf((FmtTree*)((RowNode*)inserted)->row, &inner, &col, &tmp);
    ++mnTotalCells;
    return true;
}

// ===========================================================================
// @ 0x009770e0  WinGrid::WinGrid (constructor)
// ===========================================================================
// The retail constructor writes ~250 individual member fields (vtables, tuning
// floats from the .rdata pool, rbtree anchors and stopwatch state).  Recorded in
// nonmatching.txt; this reconstruction sets the observable vtable / anchor state
// so the object is well-formed.
WinGrid* WinGrid::Ctor(void* a2, void* a3)
{
    (void)a2; (void)a3;
    *(void**)(B(this)) = (void*)0x1442f10;
    *(void**)(B(this) + 4) = (void*)0x1442df0;
    *(void**)(B(this) + 0x20c) = (void*)0x1442bd0;
    return this;
}

// ===========================================================================
// @ 0x00977600  WinGrid::~WinGrid (destructor)
// ===========================================================================
void WinGrid::Dtor(unsigned flags)
{
    *(void**)(B(this)) = (void*)0x1442f10;
    *(void**)(B(this) + 4) = (void*)0x1442df0;
    *(void**)(B(this) + 0x20c) = (void*)0x1442bd0;
    RecalcAll(this);
    if (flags & 1)
        EaFree(this);
}

// ===========================================================================
// @ 0x009777c0  WinGrid::Shutdown
// ===========================================================================
bool WinGrid::Shutdown()
{
    DisposeOfAllCellData();

    void** vt;

    if (mSound[0]) {
        void* p = mSound[0];
        mSound[0] = 0;
        vt = *(void***)p;
        (*(void(__thiscall**)(void*))vt[1])(p);
    }
    if (mSound[1]) {
        void* p = mSound[1];
        mSound[1] = 0;
        vt = *(void***)p;
        (*(void(__thiscall**)(void*))vt[1])(p);
    }
    if (mSound[2]) {
        void* p = mSound[2];
        mSound[2] = 0;
        vt = *(void***)p;
        (*(void(__thiscall**)(void*))vt[1])(p);
    }
    if (mSound[3]) {
        void* p = mSound[3];
        mSound[3] = 0;
        vt = *(void***)p;
        (*(void(__thiscall**)(void*))vt[1])(p);
    }

    if (*(void**)(B(this) + 0x3d8)) {
        void* h = *(void**)(B(this) + 0x3d8);
        *(void**)(B(this) + 0x3d8) = 0;
        *(void**)(B(this) + 0x3dc) = 0;
        *(void**)(B(this) + 0x3e0) = 0;
        *(void**)(B(this) + 0x3e4) = 0;
        *(void**)(B(this) + 0x3e8) = 0;
        vt = *(void***)h;
        (*(void(__thiscall**)(void*))vt[1])(h);
    }

    return WindowShutdown();
}

// ===========================================================================
// @ 0x00977830  WinGrid::SetDefaultTextColorByColumns
// ===========================================================================
bool WinGrid::SetDefaultTextColorByColumns(uint index, int start, int count, uint color)
{
    if (index >= 8)
        return false;

    bool ok = true;
    int end = start + count;
    for (int col = start; col < end; ++col) {
        FmtTree* fmt = &mFmtRow;

        // lower_bound on the outer row map for row==0
        byte* rn = B(fmt->anchor.parent);
        RBN* cand = &fmt->anchor;
        while (rn) {
            if (((RowNode*)rn)->key < 0) {
                rn = *(byte**)rn;
            } else {
                cand = (RBN*)rn;
                rn = *(byte**)(rn + 4);
            }
        }
        if (cand == &fmt->anchor || ((RowNode*)cand)->key > 0)
            cand = &fmt->anchor;

        if (cand != &fmt->anchor) {
            RowNode* rnode = (RowNode*)cand;
            // inner lower_bound for `col`
            byte* in = B(((TreeHdr*)rnode->row)->anchor.parent);
            RBN* icand = (RBN*)(rnode->row + 4);
            while (in) {
                if (((ColNode*)in)->key < col) {
                    in = *(byte**)in;
                } else {
                    icand = (RBN*)in;
                    in = *(byte**)(in + 4);
                }
            }
            if (icand == (RBN*)(rnode->row + 0x1c) || col < ((ColNode*)icand)->key)
                icand = (RBN*)(rnode->row + 0x1c);

            if (icand != (RBN*)(rnode->row + 0x1c)) {
                *(uint*)((byte*)icand + 0x1c + index * 4) = color;
                continue;
            }
        }

        FmtExtra v;
        for (int i = 0; i < 0xe; ++i) v.f[i] = 0;
        ((byte*)&v)[0] = 0xff;
        ((uint*)((byte*)&v + 0x20))[0] = color;
        if (!InsertCellFmt(fmt, col, 0, &v, 0))
            ok = false;
    }
    return ok;
}

// ===========================================================================
// @ 0x00977970  WinGrid::SetDefaultTextColorByRows
// ===========================================================================
bool WinGrid::SetDefaultTextColorByRows(uint index, int start, int count, uint color)
{
    return SetDefaultTextColorByColumns(index, start, count, color);
}

// ===========================================================================
// @ 0x00977ab0  WinGrid::SetDefaultAlignmentByColumns
// ===========================================================================
bool WinGrid::SetDefaultAlignmentByColumns(uint index, int start, int count, uint value)
{
    return SetDefaultTextColorByColumns(index, start, count, value);
}

// ===========================================================================
// @ 0x00977be0  WinGrid::SetDefaultAlignmentByRows
// ===========================================================================
bool WinGrid::SetDefaultAlignmentByRows(uint index, int start, int count, uint value)
{
    return SetDefaultTextColorByColumns(index, start, count, value);
}

// ===========================================================================
// @ 0x00977d10  WinGrid::SetColumnWidth
// ===========================================================================
bool WinGrid::SetColumnWidth(int start, int count, float width)
{
    if (width < 0.0f)
        width = 0.0f;

    bool ok = true;
    int end = start + count;
    for (int col = start; col < end; ++col) {
        FmtTree* fmt = &mFmtRow;

        byte* rn = B(fmt->anchor.parent);
        RBN* cand = &fmt->anchor;
        while (rn) {
            if (((RowNode*)rn)->key < 0) {
                rn = *(byte**)rn;
            } else {
                cand = (RBN*)rn;
                rn = *(byte**)(rn + 4);
            }
        }
        if (cand == &fmt->anchor || ((RowNode*)cand)->key > 0)
            cand = &fmt->anchor;

        if (cand != &fmt->anchor) {
            RowNode* rnode = (RowNode*)cand;
            byte* in = B(((TreeHdr*)rnode->row)->anchor.parent);
            RBN* icand = (RBN*)(rnode->row + 4);
            while (in) {
                if (((ColNode*)in)->key < col) {
                    in = *(byte**)in;
                } else {
                    icand = (RBN*)in;
                    in = *(byte**)(in + 4);
                }
            }
            if (icand == (RBN*)(rnode->row + 0x1c) || col < ((ColNode*)icand)->key)
                icand = (RBN*)(rnode->row + 0x1c);

            if (icand != (RBN*)(rnode->row + 0x1c)) {
                *(float*)((byte*)icand + 0x48) = width;
                continue;
            }
        }

        FmtExtra v;
        for (int i = 0; i < 0xe; ++i) v.f[i] = 0;
        *(float*)((byte*)&v + 0x2c) = width;
        if (!InsertCellFmt(fmt, col, 0, &v, 0))
            ok = false;
    }
    return ok;
}
