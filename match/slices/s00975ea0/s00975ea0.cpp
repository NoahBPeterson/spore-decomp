// Slice s00975ea0: EA::UTFWinControls::WinGrid cell editing / sparse matrix internals.
// Module UTFSpore_Win32/Grid.obj (MSVC 2008 SP1).
// Flags (neighbour manifest, UTFWin region): /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
//
// Real PDB names:
//   WinGrid::DoWindowAddition                     0x975ea0
//   WinGrid::SetColumnExtraData / GetColumnExtraData  0x975f30 / 0x975f80
//   WinGrid::SetRowExtraData    / GetRowExtraData     0x975fa0 / 0x975ff0
//   WinGrid::CopyCellData (6-arg deep copy)       0x976010
//   merge-sort worker / shell                     0x976160 / 0x976310
//   pair copy ctors (MatrixRow trees)             0x976390 / 0x9763c0
//   rbtree DoNukeSubtree (CellFormatExtra row tree) 0x976450
//   rbtree insert-with-hint pair ctors            0x9764c0 / 0x976550
//   headings bulk assign                          0x9765e0
//   WinGrid::{Set,Get}{Row,Column}Heading         0x976670 / 0x9766a0 / 0x9766f0 / 0x976720
//   map<int,MatrixRow<CellData*>>::erase          0x976770
//   SparseMatrix<CellData*>::RemoveCell/RemoveRow/RemoveCol  0x9768e0 / 0x976980 / 0x976a40
//   WinGrid::ClearCell / ClearCellFormat / DisposeOfAllCellData  0x976bc0 / 0x976c60 / 0x976d20
//   SparseMatrix<CellFormatExtra>::InsertCell     0x976dd0
#include "types.h"

namespace EA {
namespace UTFWinControls {

// ---------------------------------------------------------------------------
// Shared stubs.  Layouts are raw offsets confirmed against the disassembly.
// ---------------------------------------------------------------------------

typedef unsigned int size_t;
extern "C" size_t wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

struct RBN {                     // eastl node base: right, left, parent, colour
    RBN* right;                  // +0x00
    RBN* left;                   // +0x04
    RBN* parent;                 // +0x08
    int  color;                  // +0x0c
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

// MatrixRow<CellData*>: an inner rbtree<int, CellData*> (0x18 bytes) stored at
// outer-node offset +0x18.
struct MatrixRow {
    char   alloc[4];             // +0x00
    RBN    anchor;               // +0x04
    int    mnSize;               // +0x14
    void CtorFrom(const int* src);                           // 0x009755a0, ret 4
    void f(void* value);                                     // 0x009a9600, ret 4
};

// eastl::rbtree header (allocator dword + anchor + size)
struct TreeHdr {
    char      alloc[4];          // +0x00
    RBN       anchor;            // +0x04 (right/left/parent/colour)
    int       mnSize;            // +0x14
    void Find(RBN** out, const int* key);                    // 0xe39fb0, ret 8
};

struct WString {
    wchar_t* mpData;             // +0x00
    unsigned mnSize;             // +0x04
    void assign(const wchar_t* p, unsigned n);               // 0x423650, ret 8
};

struct HdrW {                    // eastl hashtable header for hash_map<unsigned, WString>
    void**    mpBuckets;         // +0x00
    unsigned  mnBucketCount;     // +0x04
    char      pad8[8];           // +0x08..0x0f
    void** OpIndex(const unsigned* key);                     // 0x68d340, ret 4 (returns WString*)
    void   ClearNodes(void* buckets, unsigned count);        // 0x68d420, ret 8
};

extern "C" void* __cdecl EAAllocate(unsigned size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EaFree(void* p);                                   // 0x00f47380 (operator delete)

// eastl rbtree free functions (cdecl).
void RBTreeInsert(RBN* node, RBN* hint, RBN* anchor, bool bSide);           // 0x009216a0
RBN* RBTreeIncrement(RBN* node);                                            // 0x00921580
void RBTreeErase(RBN* node, RBN* anchor);                                   // 0x00921880

} // namespace UTFWinControls
} // namespace EA

using namespace EA::UTFWinControls;

// ---------------------------------------------------------------------------
// The IWinGrid subobject (embedded in WinGrid at +0x20c) and WinGrid itself.
// ---------------------------------------------------------------------------

struct WStringObj {              // eastl::basic_string<wchar_t> object, 0x10 bytes
    void* mpBegin;               // +0x00
    void* mpEnd;                 // +0x04
    void* mpCap;                 // +0x08
    void  Ctor(const wchar_t* src);                          // 0x0056e2d0
    void  assign(const wchar_t* begin, const wchar_t* end);  // 0x00423650
};

extern void* g_emptyString16;      // 0x01667bac
extern void* g_emptyString16_end;  // 0x01667bae

// eastl::hash_map<unsigned, void*> / <unsigned, WString> (0x20-byte header).
struct ExtraMap {
    char   mData[0x20];
    void** op_brackets(const unsigned* key);                 // 0x00975d40, ret 4
};

struct HeadingMap {
    char   mData[0x20];
    void** op_brackets(const unsigned* key);                 // 0x0068d340, ret 4
    void   ClearNodes(void* buckets, unsigned count);        // 0x0068d420, ret 8
};

struct CellFormat {              // 0x30-byte cell format block ("UTFWin/Grid")
    void* mpFont;                // +0x00  (deleted by ClearCellFormat)
    int   f04;                   // +0x04
    int   f08;                   // +0x08
    int   f0c;                   // +0x0c
    int   f10;                   // +0x10
    int   f14;                   // +0x14
    int   f18;                   // +0x18
    int   f1c;                   // +0x1c
    int   f20;                   // +0x20
    signed char b24;             // +0x24  (init 0xff)
    signed char b25;             // +0x25
    signed char b26;             // +0x26
    int   f28;                   // +0x28
    int   f2c;                   // +0x2c
    CellFormat();
};

// MatrixRow<CellData*>: an inner rbtree<int, CellData*> (0x18 bytes) stored at
// outer-node offset +0x18.  (Declared in the prologue above.)

struct RowNode {                 // 0x30-byte outer node: {RBN, int key@0x10, pad, MatrixRow@0x18}
    RBN       base;              // +0x00
    int       key;               // +0x10
    int       pad14;             // +0x14
    MatrixRow row;               // +0x18
};

struct ColNode {                 // 0x1c-byte inner node: {RBN, int key@0x10, pad, CellData* value@0x18}
    RBN       base;              // +0x00
    int       key;               // +0x10
    int       pad14;             // +0x14
    CellData* value;             // +0x18
};

struct CellsMatrix {             // SparseMatrix<CellData*>: at WinGrid+0x320 / IWinGrid+0x114
    char   alloc[4];             // +0x00
    RBN    anchor;               // +0x04
    int    mnSize;               // +0x14
    int    pad18;                // +0x18
    int    mnTotalCells;         // +0x1c
    int    mnMinCol;             // +0x20
    int    mnMaxCol;             // +0x24
    int    mnMinRow;             // +0x28
    int    mnMaxRow;             // +0x2c

    void Find(RBN** out, const int* key);                    // 0x00e39fb0, ret 8
    void DoNukeSubtree(RBN* node);                           // 0x00976450, ret 4
    bool RemoveCell(int col, int row, CellData** out);       // 0x009768e0, ret 0xc
    bool RemoveRow(int start, int count);                    // 0x00976980, ret 8
    bool RemoveCol(int start, int count);                    // 0x00976a40, ret 8
    void EraseRow(RBN** out, RBN* node);                     // 0x00976770, ret 8
    bool GetCellPtr(int col, int row, CellData** out);      // 0x00973a90, ret 0xc
    int  GetCellsInRange(int c0, int r0, int c1, int r1, CellData** out); // 0x00973b90, ret 0x14
};

// eastl node base with a key at +0x10 (rbtree payload node).
struct KeyNode {
    RBN base;                    // +0x00
    int key;                     // +0x10
};

// A single 12-byte by-value sort context (comparator + payload + key fn).
struct SortPack {
    int a;
    int b;
    int c;
};

void MergeSortWork(SortPack ctx, int* first, int* last, int* buf);            // 0x00976160
void MergeSortShell(int* first, int* last, int* cur0, int* cur1, int* cur2);// 0x00976310
void MergeRuns(int* first, int* mid, int* mid2, int* last, int* buf, SortPack ctx); // 0x00975e00

// pair<int, MatrixRow<...>> copy ctors used by the two rbtree insert paths.
// The out-of-line row copy ctors are member functions (dest is `this`).
struct MatrixRowC {              // MatrixRow<CellFormatExtra>, 0x1c bytes
    char   alloc[4];
    RBN    anchor;
    int    mnSize;
    int    pad18;
    void CtorFrom(const int* src);                           // 0x00975610, ret 4
    void f(void* value);                                     // 0x009a9600, ret 4
};

struct PairRowCD {               // pair<int, MatrixRow<CellData*>> payload
    int       key;               // +0x00
    int       pad;               // +0x04
    MatrixRow row;               // +0x08
    PairRowCD(const int* pk, const int* src);                // 0x00976390
};
struct PairRowCF {               // pair<int, MatrixRow<CellFormatExtra>> payload
    int  key;                    // +0x00
    int  pad;                    // +0x04
    MatrixRowC row;              // +0x08
    PairRowCF(const int* pk, const int* src);                // 0x009763c0
};

// rbtree insert-with-hint helpers (one per row-map instantiation).
struct RowTreeCD {
    char  alloc[4];              // +0x00
    RBN   anchor;                // +0x04
    int   mnSize;                // +0x14
    void InsertValue(PairRowCD** out, RBN* hint, const PairRowCD* value, bool bHint);  // 0x009764c0, ret 0x10
};
struct RowTreeCF {
    char  alloc[4];
    RBN   anchor;
    int   mnSize;
    void InsertValue(PairRowCF** out, RBN* hint, const PairRowCF* value, bool bHint);  // 0x00976550, ret 0x10
};

// rbtree<CellData, CellData, ..., 0, 1> header at WinGrid+0x380
// (IWinGrid-relative +0x174).
struct CellSet {
    char  alloc[4];              // +0x00
    RBN   anchor;                // +0x04
    int   mnSize;                // +0x14
    void  DoInsertValue(void** out, const CellData* value, bool bTag);  // 0x009753f0, ret 0xc
};

// IWinGrid subobject view at WinGrid+0x20c; all offsets below are relative to it.
struct IWinGridIface {
    char     pad0[0x008];
    char     mbDirty;            // +0x008
    char     pad9[0x9c - 0x9];
    int      mExtraDataType;     // +0x09c
    char     padA0[0x114 - 0xa0];
    CellsMatrix mCells;          // +0x114   (WinGrid+0x320)
    char     pad1[0x174 - 0x114 - sizeof(CellsMatrix)];
    CellSet  mAddedCells;        // +0x174   (WinGrid+0x380)
    char     pad2[0x1a8 - 0x174 - sizeof(CellSet)];
    ExtraMap mRowExtraData;      // +0x1a8
    ExtraMap mColumnExtraData;   // +0x1c8
    char     pad3[0x208 - 0x1c8 - sizeof(ExtraMap)];
    HeadingMap mColumnHeadings;  // +0x208
    HeadingMap mRowHeadings;     // +0x228

    bool  SetColumnExtraData(unsigned key, void* data);
    void* GetColumnExtraData(unsigned key);
    bool  SetRowExtraData(unsigned key, void* data);
    void* GetRowExtraData(unsigned key);
    void  SetRowHeading(unsigned key, void** pOut);           // 0x00976670
    void  SetColumnHeading(unsigned key, const wchar_t* text); // 0x009766a0
    void  GetColumnHeading(unsigned key, void** pOut);        // 0x009766f0
    void  SetColumnHeading2(unsigned key, const wchar_t* text);// 0x00976720
    bool  ClearCell(int col, int row);                        // 0x00976bc0
    bool  ClearCellFormat(int col, int row);                  // 0x00976c60
};

struct IWindowSub {              // secondary window interface at WinGrid+4
    virtual void pv0();  virtual void pv1();  virtual void pv2();  virtual void pv3();
    virtual void pv4();  virtual void pv5();  virtual void pv6();  virtual void pv7();
    virtual void pv8();  virtual void pv9();  virtual void pv10(); virtual void pv11();
    virtual void pv12(); virtual void pv13(); virtual void pv14(); virtual void pv15();
    virtual void pv16(); virtual void pv17(); virtual void pv18(); virtual void pv19();
    virtual void pv20(); virtual void pv21(); virtual void pv22(); virtual void pv23();
    virtual void pv24(); virtual void pv25(); virtual void pv26(); virtual void pv27();
    virtual void pv28(); virtual void pv29(); virtual void pv30();
    virtual void SetFlag(unsigned flag, int value);           // +0x7c slot 31
    virtual void pv32(); virtual void pv33(); virtual void pv34(); virtual void pv35();
    virtual void Invalidate();                                // +0x90 slot 36
    virtual void pv37(); virtual void pv38(); virtual void pv39(); virtual void pv40();
    virtual void pv41(); virtual void pv42(); virtual void pv43(); virtual void pv44();
    virtual void pv45(); virtual void pv46(); virtual void pv47(); virtual void pv48();
    virtual void pv49(); virtual void pv50(); virtual void pv51(); virtual void pv52();
    virtual void pv53();
    virtual bool AcceptsWindow(void* pWindow);                // +0xd8 slot 54
};

// rbtree<CellData, CellData, ..., 0, 1> header at WinGrid+0x380.
struct CellSet;

// IWinGrid vtable helpers (this == the IWinGrid subobject at WinGrid+0x20c).
#define IVT(p, i) ((*(void***)(p))[i])
#define IVC1(R, p, i, a) (((R(__thiscall*)(void*, unsigned))IVT(p, i))(p, a))
#define IVC2(R, p, i, a, b) (((R(__thiscall*)(void*, unsigned, unsigned))IVT(p, i))(p, a, b))
#define IVC3(R, p, i, a, b, c) (((R(__thiscall*)(void*, unsigned, unsigned, unsigned))IVT(p, i))(p, a, b, c))

struct WinGrid;

inline WinGrid* GridOf(void* p) { return (WinGrid*)((char*)p - 0x20c); }

struct WinGrid {
    char     pad0[0x004];
    IWindowSub mWindow;          // +0x004
    char     pad8[0x20c - 0x004 - sizeof(IWindowSub)];
    IWinGridIface mIface;        // +0x20c
    char     padRest[0x004];

    void PlaceCellWindow(int col, int row, void* pWindow, int a4, int a5);       // 0x009720a0, ret 0x14
    void DisposeOfCellData(int col, int row, CellData* p, bool bParam);          // 0x00975c50, ret 0x10
    void DoWindowAddition(int col, int row, void* pWindow, int a4, int a5);      // 0x00975ea0, ret 0x14
    bool CopyCellData(int c1, int r1, CellData* src, int c2, int r2, CellData* dst); // 0x00976010, ret 0x18
    void DisposeOfAllCellData();                                                 // 0x00976d20
};

// ===========================================================================
// @ 0x00975ea0  WinGrid::DoWindowAddition
// ===========================================================================
void WinGrid::DoWindowAddition(int col, int row, void* pWindow, int a4, int a5)
{
    if (pWindow == 0)
        return;
    if (!mWindow.AcceptsWindow(pWindow))
        return;

    CellData cd;
    cd.mType = 1;
    cd.mCol = col;
    cd.mRow = row;
    cd.mpWindow = pWindow;
    cd.pad10 = 0;
    cd.pad14 = 0;
    cd.mFlags = 0;

    void* out[2];
    mIface.mAddedCells.DoInsertValue(out, &cd, false);
    PlaceCellWindow(col, row, pWindow, a4, a5);
}

// ===========================================================================
// @ 0x00975f30  IWinGrid::SetColumnExtraData(unsigned key, void* unused)
// ===========================================================================
bool IWinGridIface::SetColumnExtraData(unsigned key, void* data)
{
    (void)data;
    unsigned k = key;
    mExtraDataType = 1;
    if (!IVC1(bool, this, 0xcc / 4, k))
        return false;
    *mColumnExtraData.op_brackets(&k) = (void*)k;
    return true;
}

// ===========================================================================
// @ 0x00975f80  IWinGrid::GetColumnExtraData
// ===========================================================================
void* IWinGridIface::GetColumnExtraData(unsigned key)
{
    unsigned k = key;
    return *mColumnExtraData.op_brackets(&k);
}

// ===========================================================================
// @ 0x00975fa0  IWinGrid::SetRowExtraData(unsigned key, void* unused)
// ===========================================================================
bool IWinGridIface::SetRowExtraData(unsigned key, void* data)
{
    (void)data;
    unsigned k = key;
    mExtraDataType = 1;
    if (!IVC1(bool, this, 0xd0 / 4, k))
        return false;
    *mRowExtraData.op_brackets(&k) = (void*)k;
    return true;
}

// ===========================================================================
// @ 0x00975ff0  IWinGrid::GetRowExtraData
// ===========================================================================
void* IWinGridIface::GetRowExtraData(unsigned key)
{
    unsigned k = key;
    return *mRowExtraData.op_brackets(&k);
}

// ===========================================================================
// @ 0x00976010  WinGrid::CopyCellData  (deep copy)
// ===========================================================================
bool WinGrid::CopyCellData(int c1, int r1, CellData* src, int c2, int r2, CellData* dst)
{
    if (dst)
        DisposeOfCellData(c2, r2, dst, false);
    if (src->mType == 1)
        return false;

    if (dst == 0) {
        dst = (CellData*)EAAllocate(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
        if (dst == 0) {
            dst = 0;
        } else {
            dst->mType = 0; dst->mCol = 0; dst->mRow = 0;
            dst->mpWindow = 0; dst->pad10 = 0; dst->pad14 = 0; dst->mFlags = 0;
        }
    }

    dst->mType = src->mType;
    dst->mCol = c2;
    dst->mRow = r2;
    dst->mpWindow = 0;
    dst->pad10 = 0;
    dst->pad14 = 0;
    dst->mFlags = src->mFlags;

    if (src->mType == 4) {
        void** w = (void**)src->mpWindow;
        if (w)
            ((void(__thiscall*)(void*))w[0])(w);
        dst->mpWindow = w;
    }
    else if (src->mType == 2) {
        const wchar_t* str = (const wchar_t*)src->mpWindow;
        void* ws = EAAllocate(0x10, "UTFWin/Grid", 0, 0, 0, 0);
        if (str != 0) {
            if (ws == 0)
                ws = 0;
            else
                ((WStringObj*)ws)->Ctor(str);
        } else {
            if (ws == 0)
                ws = 0;
            else {
                ((void**)ws)[0] = g_emptyString16;
                ((void**)ws)[1] = g_emptyString16;
                ((void**)ws)[2] = g_emptyString16_end;
            }
        }
        dst->mpWindow = ws;
    }

    if (src->pad10 != 0) {
        void* fmt = EAAllocate(0x30, "UTFWin/Grid", 0, 0, 0, 0);
        if (fmt == 0)
            fmt = 0;
        else
            *(CellFormat*)fmt = CellFormat();
        dst->pad10 = (int)fmt;
        *(CellFormat*)fmt = *(CellFormat*)src->pad10;
    }
    return true;
}

// ===========================================================================
// @ 0x00976160  merge-sort worker (eastl internal)
// ===========================================================================
void MergeSortWork(SortPack ctx, int* first, int* last, int* buf)
{
    int n = last - first;
    if (n <= 1)
        return;

    int half = n / 2;
    int* mid = first + half;
    if (half > 1) {
        int quarter = half / 2;
        int* q = first + quarter;
        MergeSortWork(ctx, first, q, buf);
        MergeSortWork(ctx, q, mid, buf + quarter);
        MergeRuns(first, q, q, mid, buf, ctx);
    }

    if (n - half > 1) {
        int rest = (half + n) / 2;
        int* r = first + rest;
        MergeSortWork(ctx, mid, r, buf + half);
        MergeSortWork(ctx, r, last, buf + rest);
        MergeRuns(mid, r, r, last, buf + half, ctx);
    } else {
        buf[half] = *mid;
    }

    MergeRuns(buf, buf + half, buf + half, buf + n, first, ctx);
}

// ===========================================================================
// @ 0x00976310  merge_sort shell
// ===========================================================================
void MergeSortShell(int* first, int* last, int* cur0, int* cur1, int* cur2)
{
    int n = last - first;
    if (n <= 1)
        return;

    int* buf = (int*)EAAllocate((unsigned)n * 4, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    for (int* p = buf; p != buf + n; ++p)
        *p = 0;

    SortPack ctx;
    ctx.a = (int)cur0;
    ctx.b = (int)cur1;
    ctx.c = (int)cur2;
    MergeSortWork(ctx, first, last, buf);
    EaFree(buf);
}

// ===========================================================================
// @ 0x00976390  pair<int, MatrixRow<CellData*>> copy ctor
// ===========================================================================
PairRowCD::PairRowCD(const int* pk, const int* src)
{
    key = *pk;
    pad = src[0];
    row.CtorFrom(src + 1);
}

// ===========================================================================
// @ 0x009763c0  pair<int, MatrixRow<CellFormatExtra>> copy ctor
// ===========================================================================
PairRowCF::PairRowCF(const int* pk, const int* src)
{
    key = *pk;
    pad = src[0];
    row.CtorFrom(src + 1);
}

// ===========================================================================
// @ 0x00976450  rbtree DoNukeSubtree (row map with cell-list values)
// ===========================================================================
void CellsMatrix::DoNukeSubtree(RBN* node)
{
    while (node) {
        DoNukeSubtree(node->right);
        RBN* next = node->left;
        RowNode* rn = (RowNode*)node;
        MatrixRow* row = &rn->row;
        RBN* inner = (RBN*)rn->row.anchor.parent;
        while (inner) {
            row->f(*(void**)inner);                        // 0x009a9600
            RBN* suiv = inner->left;
            EaFree(inner);
            inner = suiv;
        }
        EaFree(node);
        node = next;
    }
}

// ===========================================================================
// @ 0x009764c0  rbtree insert-with-hint (CellData* row map)
// ===========================================================================
void RowTreeCD::InsertValue(PairRowCD** out, RBN* hint, const PairRowCD* value, bool bHint)
{
    bool bContinue;
    if (!bHint && (RBN*)hint != &anchor && value->key >= ((KeyNode*)hint)->key)
        bContinue = true;
    else
        bContinue = false;

    RBN* node = (RBN*)EAAllocate(0x34, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    RowNode* rn = (RowNode*)node;
    if (rn) {
        rn->key = value->key;
        rn->pad14 = value->pad;
        rn->row.CtorFrom((const int*)&value->row);
    }
    RBTreeInsert(node, hint, &anchor, bContinue);          // 0x009216a0
    ++mnSize;
    *out = (PairRowCD*)node;
}

// ===========================================================================
// @ 0x00976550  rbtree insert-with-hint (row map with 0x1c-byte rows)
// ===========================================================================
void RowTreeCF::InsertValue(PairRowCF** out, RBN* hint, const PairRowCF* value, bool bHint)
{
    bool bContinue;
    if (!bHint && (RBN*)hint != &anchor && value->key >= ((KeyNode*)hint)->key)
        bContinue = true;
    else
        bContinue = false;

    RBN* node = (RBN*)EAAllocate(0x34, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    RowNode* rn = (RowNode*)node;
    if (rn) {
        rn->key = value->key;
        rn->pad14 = value->pad;
        ((MatrixRowC*)&rn->row)->CtorFrom((const int*)&value->row);
    }
    RBTreeInsert(node, hint, &anchor, bContinue);
    ++mnSize;
    *out = (PairRowCF*)node;
}

// ===========================================================================
// @ 0x009765e0  bulk heading assign
// ===========================================================================
int BulkAssignHeadings(void* p1, const void* p2, const void* p3)
{
    HeadingMap* map = (HeadingMap*)(*(char**)((char*)p1 + 4) + *(const int*)((char*)p3 + 0x10));
    map->ClearNodes(*(void**)((char*)map + 4), *(const unsigned*)((char*)map + 8));
    *(int*)((char*)map + 0xc) = 0;

    void** items = *(void***)((const char*)p2 + 4);
    unsigned count = *(const unsigned*)((const char*)p2 + 8);
    for (unsigned i = 0; i < count; ++i, ++items) {
        const wchar_t* s = (const wchar_t*)*items;
        if (s) {
            WStringObj* w = (WStringObj*)map->op_brackets(&i);
            w->assign(s, s + wcslen(s));
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00976670  IWinGrid heading accessor (map +0x228, returns data pointer)
// ===========================================================================
void IWinGridIface::SetRowHeading(unsigned key, void** pOut)
{
    unsigned k = key;
    void** w = mRowHeadings.op_brackets(&k);
    *pOut = *w;
}

// ===========================================================================
// @ 0x009766a0  IWinGrid heading assign (map +0x228)
// ===========================================================================
void IWinGridIface::SetColumnHeading(unsigned key, const wchar_t* text)
{
    WStringObj* w = (WStringObj*)mRowHeadings.op_brackets(&key);
    w->assign(text, text + wcslen(text));
}

// ===========================================================================
// @ 0x009766f0  IWinGrid heading accessor (map +0x208)
// ===========================================================================
void IWinGridIface::GetColumnHeading(unsigned key, void** pOut)
{
    unsigned k = key;
    void** w = mColumnHeadings.op_brackets(&k);
    *pOut = *w;
}

// ===========================================================================
// @ 0x00976720  IWinGrid heading assign (map +0x208)
// ===========================================================================
void IWinGridIface::SetColumnHeading2(unsigned key, const wchar_t* text)
{
    WStringObj* w = (WStringObj*)mColumnHeadings.op_brackets(&key);
    w->assign(text, text + wcslen(text));
}

// ===========================================================================
// @ 0x00976770  map<...>::erase(iterator, node)
// ===========================================================================
void CellsMatrix::EraseRow(RBN** out, RBN* node)
{
    --mnSize;
    RBN* next = RBTreeIncrement(node);                     // 0x00921580
    RBTreeErase(node, &anchor);                            // 0x00921880
    RowNode* rn = (RowNode*)node;
    rn->row.f(rn->row.anchor.parent);                      // 0x009a9600
    EaFree(node);
    *out = next;
}

// ===========================================================================
// @ 0x009768e0  SparseMatrix<CellData*>::RemoveCell(int col, int row, CellData** out)
// ===========================================================================
bool CellsMatrix::RemoveCell(int col, int row, CellData** out)
{
    RBN* rn;
    Find(&rn, &row);                       // outer: row
    if (rn == &anchor)
        return false;

    RowNode* rnode = (RowNode*)rn;
    RBN* inner;
    ((TreeHdr*)&rnode->row)->Find(&inner, &col);   // inner: col
    if (inner == &rnode->row.anchor)
        return false;

    if (out)
        *out = ((ColNode*)inner)->value;
    --rnode->row.mnSize;
    RBTreeIncrement(inner);
    RBTreeErase(inner, &rnode->row.anchor);
    EaFree(inner);
    --mnTotalCells;
    if (rnode->row.mnSize == 0)
        EraseRow(&rn, rn);
    return true;
}

// ===========================================================================
// @ 0x00976980  SparseMatrix<CellData*>::RemoveRow(int start, int count)
// ===========================================================================
bool CellsMatrix::RemoveRow(int start, int count)
{
    int end = start + count;
    for (int row = start; row < end; ++row) {
        RBN* node = anchor.parent;
        RBN* cand = &anchor;
        while (node) {
            if (((KeyNode*)node)->key < row) {
                node = node->right;
            } else {
                cand = node;
                node = node->left;
            }
        }
        if (cand == &anchor || row < ((KeyNode*)cand)->key)
            continue;
        RowNode* rn = (RowNode*)cand;
        mnTotalCells -= rn->row.mnSize;
        --mnSize;
        RBTreeIncrement(cand);
        RBTreeErase(cand, &anchor);
        ColNode* inner = (ColNode*)rn->row.anchor.parent;
        while (inner) {
            rn->row.f(*(void**)inner);
            ColNode* suiv = (ColNode*)inner->base.left;
            EaFree(inner);
            inner = suiv;
        }
        EaFree(cand);
    }
    return true;
}

// ===========================================================================
// @ 0x00976a40  SparseMatrix<CellData*>::RemoveCol(int start, int count)
// ===========================================================================
bool CellsMatrix::RemoveCol(int start, int count)
{
    if (anchor.parent == 0)
        return true;

    RBN* rn = anchor.left;
    int end = start + count;
    do {
        RowNode* rnode = (RowNode*)rn;
        for (int col = start; col < end; ++col) {
            RBN* node = rnode->row.anchor.parent;
            RBN* cand = &rnode->row.anchor;
            while (node) {
                if (((KeyNode*)node)->key < col)
                    node = node->right;
                else { cand = node; node = node->left; }
            }
            if (cand == &rnode->row.anchor || col < ((KeyNode*)cand)->key)
                continue;
            --rnode->row.mnSize;
            RBTreeIncrement(cand);
            RBTreeErase(cand, &rnode->row.anchor);
            EaFree(cand);
            --mnTotalCells;
        }
        RBN* next;
        if (rnode->row.mnSize == 0) {
            next = RBTreeIncrement(rn);
            --mnSize;
            RBTreeErase(rn, &anchor);
            ColNode* inner = (ColNode*)rnode->row.anchor.parent;
            while (inner) {
                rnode->row.f(*(void**)inner);
                ColNode* suiv = (ColNode*)inner->base.left;
                EaFree(inner);
                inner = suiv;
            }
            EaFree(rn);
        } else {
            next = RBTreeIncrement(rn);
        }
        rn = next;
    } while (rn != &anchor);
    return true;
}

// ===========================================================================
// @ 0x00976bc0  WinGrid::ClearCell(int col, int row)
// ===========================================================================
bool IWinGridIface::ClearCell(int col, int row)
{
    bool bFormatted = false;
    bool bHadFormat = true;
    (void)bHadFormat;
    bool bWasFormatted = false;
    if (IVC3(bool, this, 0xac / 4, col, row, 0))
        bWasFormatted = true;

    CellData* cell;
    if (mCells.RemoveCell(col, row, &cell)) {
        GridOf(this)->DisposeOfCellData(col, row, cell, true);
        ((IWindowSub*)((char*)GridOf(this) + 4))->SetFlag(8, 1);
        mbDirty = true;
        bFormatted = bWasFormatted;
    } else {
        bFormatted = false;
    }
    ((IWindowSub*)((char*)GridOf(this) + 4))->Invalidate();
    return bFormatted;
}

// ===========================================================================
// @ 0x00976c60  WinGrid::ClearCellFormat(int col, int row)
// ===========================================================================
bool IWinGridIface::ClearCellFormat(int col, int row)
{
    bool bHadFont = false;
    CellData* cell = 0;
    if (mCells.GetCellPtr(col, row, &cell)) {
        if (cell) {
            if (cell->pad10) {
                CellFormat* fmt = (CellFormat*)cell->pad10;
                void* font = fmt->mpFont;
                if (font)
                    bHadFont = true;
                EaFree(font);
                cell->pad10 = 0;
                if (cell->pad14 == 0) {
                    mCells.RemoveCell(col, row, 0);
                } else if (!bHadFont) {
                    ((IWindowSub*)((char*)GridOf(this) + 4))->Invalidate();
                    return true;
                }
                ((IWindowSub*)((char*)GridOf(this) + 4))->SetFlag(8, 1);
                mbDirty = true;
            }
        }
    }
    ((IWindowSub*)((char*)GridOf(this) + 4))->Invalidate();
    return true;
}

// ===========================================================================
// @ 0x00976d20  WinGrid::DisposeOfAllCellData()
// ===========================================================================
void WinGrid::DisposeOfAllCellData()
{
    unsigned n = (unsigned)mIface.mCells.mnMaxCol * 0xc;
    CellData** list = (CellData**)EAAllocate(n, "UTFWin/Grid", 0, 0, 0, 0);
    if (list) {
        int count = mIface.mCells.GetCellsInRange(0, 0, 0x7fffffff, 0x7fffffff, list);
        if (count > 0) {
            CellData** p = list + 1;
            do {
                DisposeOfCellData(p[-1] ? (int)p[-1] : 0, (int)p[0], p[1], true);
                p += 3;
            } while (--count);
        }
        EaFree(list);
    }
    mIface.mCells.DoNukeSubtree(mIface.mCells.anchor.parent);
    mIface.mCells.anchor.left = &mIface.mCells.anchor;
    mIface.mCells.anchor.right = &mIface.mCells.anchor;
    mIface.mCells.anchor.parent = 0;
    mIface.mCells.mnSize = 0;
    mIface.mCells.mnTotalCells = 0;
    mIface.mCells.anchor.color = 0;
    mIface.mCells.mnMaxCol = 0;
}

// ===========================================================================
// @ 0x00976dd0  SparseMatrix<CellFormatExtra>::InsertCell
//   bool InsertCell(int col, int row, const FmtExtra* value, FmtExtra* out)
// ===========================================================================
struct FmtExtra {                // 0x38-byte CellFormatExtra value
    int f[0xe];
};
struct FmtTree {                 // SparseMatrix<CellFormatExtra> view
    char   alloc[4];             // +0x00
    RBN    anchor;               // +0x04
    int    mnSize;               // +0x14
    int    pad18;                // +0x18
    int    mnTotalCells;         // +0x1c
    int    mnMinCol;             // +0x20
    int    mnMaxCol;             // +0x24
    int    mnMinRow;             // +0x28
    int    mnMaxRow;             // +0x2c

    void Find(RBN** out, const int* key);                    // 0x00e39fb0
    void InsertCellInner(RBN** out, const int* key, const void* value);  // 0x00975da0
    void InsertRow(RBN** out, RBN* hint, const void* value); // 0x00976b60
};

bool InsertCellFmt(FmtTree* self, int col, int row, const FmtExtra* value, FmtExtra* out)
{
    if (row < self->mnMinRow || col < self->mnMinCol ||
        row > self->mnMaxRow || col > self->mnMaxCol)
        return false;

    RBN* rowNode;
    self->Find(&rowNode, &row);
    if (rowNode != &self->anchor) {
        RowNode* rn = (RowNode*)rowNode;
        RBN* inner;
        ((TreeHdr*)&rn->row)->Find(&inner, &col);
        if (inner == &rn->row.anchor) {
            // insert a new inner cell into the existing row
            ColNode* c = (ColNode*)inner;  // unused; new element path
            FmtExtra tmp;
            tmp = *value;               // 0xe dwords
            self->InsertCellInner((RBN**)&inner, &col, &tmp);
            ++self->mnTotalCells;
            return true;
        }
        // existing cell: swap value
        if (out)
            *out = *(FmtExtra*)((char*)inner + 0x18);
        *(FmtExtra*)((char*)inner + 0x18) = *value;
        return true;
    }

    // new row
    {
        int key = row;
        FmtExtra tmp;
        tmp = *value;
        // build a pair (key, MatrixRow) and insert into the outer tree
        RBN* newNode;
        self->InsertRow(&newNode, (RBN*)&self->anchor, &tmp);
        ++self->mnTotalCells;
    }
    return true;
}

// APPEND4
