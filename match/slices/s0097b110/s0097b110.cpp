// Slice s0097b110: EA::UTFWinControls::WinGrid scrolling / copy / rect / recalc tail.
// Module UTFSpore_Win32/Grid.obj (MSVC 2008 SP1, /O2 /arch:SSE /fp:fast).
//
// Real PDB names:
//   WinGrid::ScrollCellsVertically(int)          0x97b110
//   WinGrid::ScrollCellsHorizontally(int)        0x97b230
//   WinGrid::CopyColumns(int,int,int,bool)       0x97b350
//   WinGrid::CopyRows(int,int,int,bool)          0x97b630
//   WinGrid::GetCellRect(int,int,RectT<float>&)  0x97b910
//   WinGrid::ResizeColumnToFitCellWindows(int,int) 0x97ba60
//   WinGrid::RecalculateAll()                    0x97bc80
//
// Calling convention note: for the six non-RecalculateAll functions `this` is the IWinGrid
// subobject located at WinGrid base + 0x20c; the base is recovered with `(char*)this - 0x20c`.
// RecalculateAll is a WinGrid (base) method.  Offsets below are raw, taken directly from the
// original disassembly.
#include "types.h"

namespace Gr {

#define GVT(o, i) ((*(void***)(o))[i])

template <class T> struct RectT { T left, top, right, bottom; };

// ---------------------------------------------------------------------------------------------
// Cell / format / matrix layouts (raw offsets from the disassembly)
// ---------------------------------------------------------------------------------------------
struct CellData {                 // 0x1c bytes, "UTFWin/Grid"
    int      mType;               // +0x00
    int      mCol;                // +0x04
    int      mRow;                // +0x08
    void*    mpWindow;            // +0x0c
    int      pad10;               // +0x10
    int      pad14;               // +0x14
    unsigned mFlags;              // +0x18
};

struct CellFormatExtra {          // width is stored at +0x34
    char  pad[0x34];
    float mfWidth;                // +0x34
};

// eastl::rbtree node as used by the column-format SparseMatrix<CellFormatExtra> (2 levels deep)
struct FmtNode {                  // inner node: key@0x10, CellFormatExtra* value@0x18
    FmtNode* left;                // +0x00
    FmtNode* right;               // +0x04
    char     pad8[8];             // +0x08..0x0f
    int      key;                 // +0x10
    char     pad14[4];            // +0x14..0x17
    void*    value;               // +0x18  (inner node) / inner anchor (outer node)
};

struct InnerTree {                // SparseMatrixCol<CellFormatExtra> header
    char     pad0[0x0c];
    FmtNode* mRoot;               // +0x0c
};

struct FmtOuterNode {             // outer key@0x10, inner tree header at +0x18
    FmtOuterNode* left;           // +0x00
    FmtOuterNode* right;          // +0x04
    char     pad8[8];             // +0x08..0x0f
    int      key;                 // +0x10
    char     pad14[4];            // +0x14..0x17
    InnerTree inner;              // +0x18 (anchor@0x1c, root@0x24)
};

struct FmtMatrix {                // SparseMatrix<CellFormatExtra>, at IWinGrid + 0xb4
    char          pad0[0x0c];
    FmtOuterNode* mRoot;          // +0x0c
    int InsertCell(int col, int row, void* fmt, int flag);   // 0x976dd0, ret 0x10
};

// SparseMatrix<CellData*> col-iterator returned by GetRowCountForCol
struct ColIter {
    void* mpBucket;               // +0x00
    void* mpNode;                 // +0x04
    ColIter& operator++();        // 0x973640
};

struct SparseMatrixCells {        // SparseMatrix<CellData*>, at IWinGrid + 0x114
    char pad0[0x0c];
    bool  GetMinMaxUsedRowForCol(int col, int* pMin, int* pMax);   // 0x973800, ret 0xc
    bool  GetMinMaxUsedColForRow(int row, int* pMin, int* pMax);   // inlined twin (row-wise)
    void* GetRowCountForCol(ColIter* out, int col);                // 0x973c30, ret 8
};

// ---------------------------------------------------------------------------------------------
// eastl hash maps used for the per-column/row "extra data" (4-byte value) and the headings
// (WString value).  Both share the eastl hashtable header layout {pad, buckets, count}.
// ---------------------------------------------------------------------------------------------
struct WString {
    wchar_t* mpData;              // +0x00
    unsigned mnSize;              // +0x04
    void assign(const wchar_t* p, unsigned n);   // 0x423650
};

struct HNodeW { unsigned key; WString value; HNodeW* next; };   // 0x10 bytes
struct HNodeP { unsigned key; void* value; HNodeP* next; };     // 0x0c bytes

struct HashHeader {
    unsigned  pad0;               // +0x00
    void**    mpBuckets;          // +0x04
    unsigned  mnBucketCount;      // +0x08
    char      padc[0x0c];
};

struct HeadingMap : HashHeader {                 // hash_map<unsigned, WString>
    WString* Index(const unsigned* key);         // 0x68d340
    void     EraseKey(const unsigned* key);      // 0x6b5110
};

struct ExtraMap : HashHeader {                   // hash_map<unsigned, void*>
    void* FindOrInsert(const unsigned* key);     // 0x902290 (returns node)
    void  Erase(const unsigned* key);            // 0xa460d0
    HNodeP* Find(const unsigned& key) {
        unsigned idx = key % mnBucketCount;
        HNodeP* n = (HNodeP*)mpBuckets[idx];
        while (n) {
            if (n->key == key) return n;
            n = n->next;
        }
        return (HNodeP*)mpBuckets[mnBucketCount];
    }
    HNodeP* End() const { return (HNodeP*)mpBuckets[mnBucketCount]; }
};

// ---------------------------------------------------------------------------------------------
// The full WinGrid object (only the members touched by this slice)
// ---------------------------------------------------------------------------------------------
struct WinGrid {
    char  pad0[0x004];
    void* mWindowVtbl;            // +0x004 (Window subobject vtable)
    char  pad8[0x20c - 0x008];
    void* mIfaceVtbl;             // +0x20c (IWinGrid subobject vtable)
    unsigned mGridFlags;          // +0x210
    char  pad214[0x244 - 0x214];
    float mfRect1Width;           // +0x244
    float mfRect1Height;          // +0x248
    float mfVisibleCellWidth;     // +0x24c
    float mfVisibleCellHeight;    // +0x250
    int   mnFirstVisibleCol;      // +0x254
    int   mnFirstVisibleRow;      // +0x258
    float mfAccumColFraction;     // +0x25c
    float mfAccumRowFraction;     // +0x260
    int   mnColumnLimit;          // +0x264
    int   mnRowLimit;             // +0x268
    char  pad26c[0x3f8 - 0x26c];
    unsigned mSoundIDs[2];        // +0x3f8, +0x3fc

    float GetColumnWidthInternal(int col);                        // 0x979db0
    float GetRowHeightInternal(int row);                          // 0x979f10
    void  SetSizeCachedActualForRow(int row, int count, float h);         // 0x9789a0
    void  SetSizeCachedActualForColumn(int col, int count, float w);      // 0x978b50
    bool  CopyCellData(int srcCol, int srcRow, int dstCol, int dstRow, int deep);  // 0x979bc0
    void  TestForPossibleScrollBarAdditionOrRemoval();            // 0x974d80
    void  PlaceAllCellWindows();                                  // 0x974b00
    bool  RecalculateAll();                                       // 0x97bc80
};

extern unsigned g_recalcDepth;    // 0x166b20c
extern unsigned g_one33;          // 0x1485720 (1.0f) -- referenced through memory, see notes

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
    char     pad60[0x0b4 - 0x060];
    FmtMatrix mColFormat;         // +0x0b4
    char     padFmt[0x114 - 0x0b4 - sizeof(FmtMatrix)];
    SparseMatrixCells mCells;     // +0x114
    char     padCells[0x1a8 - 0x114 - sizeof(SparseMatrixCells)];
    ExtraMap mRowExtraData;       // +0x1a8
    ExtraMap mColumnExtraData;    // +0x1c8
    char     pad1e8[0x208 - 0x1e8];
    HeadingMap mColumnHeadings;   // +0x208
    HeadingMap mRowHeadings;      // +0x228

    bool ScrollCellsVertically(int delta);
    bool ScrollCellsHorizontally(int delta);
    bool CopyColumns(int srcStart, int dstStart, int count, int bVal);
    bool CopyRows(int srcStart, int dstStart, int count, int bVal);
    bool GetCellRect(int col, int row, RectT<float>* out);
    void ResizeColumnToFitCellWindows(int col, int count);
};

inline WinGrid* Base(WinGridIface* p) { return (WinGrid*)((char*)p - 0x20c); }
inline void*    Window(WinGridIface* p) { return (char*)p - 0x208; }

// =============================================================================================
// @ 0x0097b110  EA::UTFWinControls::WinGrid::ScrollCellsVertically
// =============================================================================================
bool WinGridIface::ScrollCellsVertically(int delta)
{
    int firstRow = mnFirstVisibleRow;
    int limit = mnRowLimit;

    if ((limit == -1 || limit == 0) && (mGridFlags & 0x10000)) {
        mnFirstVisibleRow = firstRow + delta;
    } else {
        int l = limit;
        if (!(mGridFlags & 0x10000)) {
            RectT<int> r = { 0, 0, 0, 0 };
            ((void(__thiscall*)(void*, RectT<int>*))GVT(this, 0xc4 / 4))(this, &r);
            l = r.bottom + 1;
        }
        mnFirstVisibleRow += delta;
        if (mnFirstVisibleRow >= l)
            mnFirstVisibleRow = l - 1;
        else if (mnFirstVisibleRow < 0)
            mnFirstVisibleRow = 0;

        if (mnFirstVisibleRow > 0) {
            float acc = 0.0f;
            while (mfVisibleCellHeight > acc) {
                acc = 0.0f;
                int row = mnFirstVisibleRow;
                if (row < l) {
                    do {
                        acc = Base(this)->GetRowHeightInternal(row) + acc;
                        if (acc >= mfVisibleCellHeight) break;
                        ++row;
                    } while (row < l);
                }
                if (mfVisibleCellHeight > acc)
                    --mnFirstVisibleRow;
                if (mnFirstVisibleRow < 0) break;
            }
        }
    }

    if (mnFirstVisibleRow < 0)
        mnFirstVisibleRow = 0;

    if (firstRow != mnFirstVisibleRow) {
        mbDirty = true;
        void* sub = Window(this);
        ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
    }
    return true;
}

// =============================================================================================
// @ 0x0097b230  EA::UTFWinControls::WinGrid::ScrollCellsHorizontally
// =============================================================================================
bool WinGridIface::ScrollCellsHorizontally(int delta)
{
    int firstCol = mnFirstVisibleCol;
    int limit = mnColLimit;

    if ((limit == -1 || limit == 0) &&
        (*(unsigned*)((char*)this - 0x1e0) & 0x8000)) {
        mnFirstVisibleCol = firstCol + delta;
    } else {
        int l = limit;
        if (!(mGridFlags & 0x10000)) {
            RectT<int> r = { 0, 0, 0, 0 };
            ((void(__thiscall*)(void*, RectT<int>*))GVT(this, 0xc4 / 4))(this, &r);
            l = r.right + 1;
        }
        mnFirstVisibleCol += delta;
        if (mnFirstVisibleCol >= l)
            mnFirstVisibleCol = l - 1;
        if (mnFirstVisibleCol < 0)
            mnFirstVisibleCol = 0;

        if (mnFirstVisibleCol > 0) {
            float acc = 0.0f;
            while (mfVisibleCellWidth > acc) {
                acc = 0.0f;
                int col = mnFirstVisibleCol;
                if (col < l) {
                    do {
                        acc = Base(this)->GetColumnWidthInternal(col) + acc;
                        if (acc >= mfVisibleCellWidth) break;
                        ++col;
                    } while (col < l);
                }
                if (mfVisibleCellWidth > acc)
                    --mnFirstVisibleCol;
                if (mnFirstVisibleCol < 0) break;
            }
        }
    }

    if (mnFirstVisibleCol < 0)
        mnFirstVisibleCol = 0;

    if (firstCol != mnFirstVisibleCol) {
        mbDirty = true;
        void* sub = Window(this);
        ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
    }
    return true;
}

// =============================================================================================
// @ 0x0097b350  EA::UTFWinControls::WinGrid::CopyColumns
//   Returns true when srcStart == dstStart.  Otherwise shifts the source column block
//   [srcStart, srcStart+count-1] to the destination block starting at dstStart, copying the
//   used cells of each column and the per-column extra data + heading.  When bVal != 0 the
//   source extra data / heading is erased.  bVal == 0 selects the "deep" CopyCellData path.
// =============================================================================================
bool WinGridIface::CopyColumns(int srcStart, int dstStart, int count, int bVal)
{
    if (srcStart == dstStart)
        return true;

    int srcEnd = srcStart + count - 1;
    int dstEnd = dstStart + count - 1;

    int step;
    int cur;
    if (srcEnd < dstStart || srcStart > dstEnd) {
        cur = srcStart; step = 1;
    } else if (dstEnd <= srcEnd && dstEnd >= srcStart) {
        cur = srcStart; step = 1;
    } else if (srcEnd <= dstEnd) {
        cur = srcEnd; step = -1;
    } else {
        cur = srcStart; step = 0;      // unreachable
    }

    int last  = cur + (count - 1) * step;
    int delta = dstStart - cur;
    int bCopy = (bVal == 0);

    for (;;) {
        int minRow, maxRow;
        if (mCells.GetMinMaxUsedRowForCol(cur, &minRow, &maxRow) && minRow <= maxRow) {
            for (int row = minRow; row <= maxRow; ++row) {
                Base(this)->SetSizeCachedActualForRow(row, 1, -1.0f);
                Base(this)->CopyCellData(cur, row, cur + delta, row, bCopy);
            }
        }

        HNodeP* srcNode = mColumnExtraData.Find((unsigned)cur);
        if (srcNode != mColumnExtraData.End()) {
            unsigned dstKey = (unsigned)(cur + delta);
            void** dstVal = (void**)mColumnExtraData.FindOrInsert(&dstKey);
            *(void**)((char*)dstVal + 4) = srcNode->value;
            if (bVal == 1)
                mColumnExtraData.Erase((const unsigned*)&cur);
        }

        unsigned srcKey = (unsigned)cur;
        unsigned dstKey = (unsigned)(cur + delta);
        WString* s = mColumnHeadings.Index(&srcKey);
        WString* d = mColumnHeadings.Index(&dstKey);
        if (s != d)
            d->assign(s->mpData, s->mnSize);
        if (bVal == 1)
            mColumnHeadings.EraseKey(&srcKey);

        if (cur == last) {
            mbDirty = true;
            void* sub = Window(this);
            ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
            return true;
        }
        cur += step;
    }
}

// =============================================================================================
// @ 0x0097b630  EA::UTFWinControls::WinGrid::CopyRows   (mirror of CopyColumns)
// =============================================================================================
bool WinGridIface::CopyRows(int srcStart, int dstStart, int count, int bVal)
{
    if (srcStart == dstStart)
        return true;

    int srcEnd = srcStart + count - 1;
    int dstEnd = dstStart + count - 1;

    int step;
    int cur;
    if (srcEnd < dstStart || srcStart > dstEnd) {
        cur = srcStart; step = 1;
    } else if (dstEnd <= srcEnd && dstEnd >= srcStart) {
        cur = srcStart; step = 1;
    } else if (srcEnd <= dstEnd) {
        cur = srcEnd; step = -1;
    } else {
        cur = srcStart; step = 0;      // unreachable
    }

    int last  = cur + (count - 1) * step;
    int delta = dstStart - cur;
    int bCopy = (bVal == 0);

    for (;;) {
        int minCol, maxCol;
        if (mCells.GetMinMaxUsedColForRow(cur, &minCol, &maxCol) && minCol <= maxCol) {
            for (int col = minCol; col <= maxCol; ++col) {
                Base(this)->SetSizeCachedActualForColumn(col, 1, -1.0f);
                Base(this)->CopyCellData(col, cur, col, cur + delta, bCopy);
            }
        }

        HNodeP* srcNode = mRowExtraData.Find((unsigned)cur);
        if (srcNode != mRowExtraData.End()) {
            unsigned dstKey = (unsigned)(cur + delta);
            void** dstVal = (void**)mRowExtraData.FindOrInsert(&dstKey);
            *(void**)((char*)dstVal + 4) = srcNode->value;
            if (bVal == 1)
                mRowExtraData.Erase((const unsigned*)&cur);
        }

        unsigned srcKey = (unsigned)cur;
        unsigned dstKey = (unsigned)(cur + delta);
        WString* s = mRowHeadings.Index(&srcKey);
        WString* d = mRowHeadings.Index(&dstKey);
        if (s != d)
            d->assign(s->mpData, s->mnSize);
        if (bVal == 1)
            mRowHeadings.EraseKey(&srcKey);

        if (cur == last) {
            mbDirty = true;
            void* sub = Window(this);
            ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
            return true;
        }
        cur += step;
    }
}

// =============================================================================================
// @ 0x0097b910  EA::UTFWinControls::WinGrid::GetCellRect
// =============================================================================================
bool WinGridIface::GetCellRect(int col, int row, RectT<float>* out)
{
    RectT<float> pos;

    out->left  = ((float(__thiscall*)(void*, int, int))GVT(this, 0xfc / 4))(this, 0, col);
    out->right = out->left + Base(this)->GetColumnWidthInternal(col);

    float xoff;
    if (mnFirstVisibleCol != 0)
        xoff = ((float(__thiscall*)(void*, int, int))GVT(this, 0xfc / 4))(this, 0, mnFirstVisibleCol);
    else
        xoff = 0.0f;

    out->top    = ((float(__thiscall*)(void*, int, int))GVT(this, 0x100 / 4))(this, 0, row);
    out->bottom = out->top + Base(this)->GetRowHeightInternal(row);

    float yoff;
    if (mnFirstVisibleRow != 0)
        yoff = ((float(__thiscall*)(void*, int, int))GVT(this, 0x100 / 4))(this, 0, mnFirstVisibleRow);
    else
        yoff = 0.0f;

    float nx = -xoff;              // original negates with xorps + addss
    float ny = -yoff;

    out->left   += nx;
    out->top    += ny;
    out->right  += nx;
    out->bottom += ny;

    ((void(__thiscall*)(void*, RectT<float>*))GVT(this, 0x20 / 4))(this, &pos);
    out->left   += pos.left;
    out->top    += pos.top;
    out->right  += pos.left;
    out->bottom += pos.top;
    return true;
}

// =============================================================================================
// @ 0x0097ba60  EA::UTFWinControls::WinGrid::ResizeColumnToFitCellWindows
//   For each of `count` columns starting at `col`: measure the widest cell window placed in
//   that column and, when wider than the current column format width, widen (or create) the
//   column's CellFormatExtra.  When anything changed, clear the row size cache and flag the
//   grid dirty.
// =============================================================================================
void WinGridIface::ResizeColumnToFitCellWindows(int col, int count)
{
    bool changed = false;
    if (count == 0)
        return;

    for (int n = count; n != 0; --n, ++col) {
        float maxW = -1.0f;

        ColIter it;
        mCells.GetRowCountForCol(&it, col);
        while (it.mpNode != 0) {
            CellData* cell = *(CellData**)((char*)it.mpNode + 4);
            if (cell != 0 && cell->mType == 1 && cell->mpWindow != 0) {
                RectT<float>* area =
                    (RectT<float>*)((void*(__thiscall*)(void*))GVT(cell->mpWindow, 0x38 / 4))(cell->mpWindow);
                float w = area->right - area->left;
                if (maxW == -1.0f || w > maxW)
                    maxW = w;
            }
            ++it;
        }

        if (maxW == -1.0f)
            continue;

        // Locate (or create) the CellFormatExtra for (col, row 0) in the column-format matrix.
        FmtOuterNode* outer = mColFormat.mRoot;
        FmtOuterNode* outerAnchor = (FmtOuterNode*)((char*)&mColFormat + 4);
        FmtOuterNode* o = outerAnchor;
        while (outer != 0) {
            if (outer->key < 0) {
                outer = outer->left;
            } else {
                o = outer;
                outer = outer->right;
            }
        }
        if (o != outerAnchor && o->key > 0)
            o = outerAnchor;

        if (o != outerAnchor) {
            FmtNode* innerAnchor = (FmtNode*)((char*)o + 0x1c);
            FmtNode* inner = o->inner.mRoot;
            FmtNode* in = innerAnchor;
            while (inner != 0) {
                if (inner->key < col) {
                    inner = inner->left;
                } else {
                    in = inner;
                    inner = inner->right;
                }
            }
            if (in != innerAnchor && col < in->key)
                in = innerAnchor;

            if (in != innerAnchor) {
                CellFormatExtra* fmt = (CellFormatExtra*)in->value;
                if (fmt->mfWidth == -1.0f || maxW > fmt->mfWidth) {
                    fmt->mfWidth = maxW;
                    changed = true;
                }
                continue;
            }
        }

        // Create a fresh CellFormatExtra for (col, 0) and insert it.
        CellFormatExtra fmt = {};
        fmt.mfWidth = maxW;
        changed = true;
        mColFormat.InsertCell(col, 0, &fmt, 0);
    }

    if (!changed)
        return;

    Base(this)->SetSizeCachedActualForRow(0, 0x7fffffff, -1.0f);
    mbDirty = true;
    void* sub = Window(this);
    ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
}

// =============================================================================================
// @ 0x0097bc80  EA::UTFWinControls::WinGrid::RecalculateAll
//   `this` is the WinGrid base.  Guarded against re-entrancy (>= 2 levels) by a global depth
//   counter; recomputes the visible row/column fractions and re-runs the layout tail.
// =============================================================================================
bool WinGrid::RecalculateAll()
{
    if (g_recalcDepth >= 2)
        return true;

    ++g_recalcDepth;
    ((void(__thiscall*)(void*))GVT((char*)this + 4, 0x90 / 4))((char*)this + 4);

    if (*(int*)((char*)this + 0x218) <= 0) {
        void* ig = (char*)this + 0x20c;

        RectT<float> r1, r2;
        ((void(__thiscall*)(void*, RectT<float>*))GVT(ig, 0x1c / 4))(ig, &r1);
        ((void(__thiscall*)(void*, RectT<float>*))GVT(ig, 0x20 / 4))(ig, &r2);

        mfRect1Width        = r1.right - r1.left;
        mfRect1Height       = r1.bottom - r1.top;
        mfVisibleCellWidth  = r2.right - r2.left;
        mfVisibleCellHeight = r2.bottom - r2.top;
        mfAccumColFraction  = 0.0f;
        mfAccumRowFraction  = 0.0f;

        // ---- visible column count ----
        {
            float accum = 0.0f;
            int limit = mnColumnLimit;
            int i = mnFirstVisibleCol;
            if (limit == -1 || limit == 0)
                limit = 0x7fffffff;
            if (!(*(unsigned*)((char*)this + 0x210) & 0x8000)) {
                RectT<int> rr = { 0, 0, 0, 0 };
                ((void(__thiscall*)(void*, RectT<int>*))GVT(ig, 0xc4 / 4))(ig, &rr);
                if (rr.right <= limit)
                    limit = rr.right + 1;
            }
            for (; i < limit; ++i) {
                float t = GetColumnWidthInternal(i) + accum;
                if (t > mfVisibleCellWidth) {
                    float frac = (mfVisibleCellWidth - accum) / (t - accum);
                    if (frac < 0.0f) frac = -frac;
                    if (frac > 0.05f)
                        mfAccumColFraction += frac;
                    break;
                }
                mfAccumColFraction += 1.0f;
                accum = t;
            }
        }

        // ---- visible row count ----
        {
            float accum = 0.0f;
            int limit = mnRowLimit;
            int i = mnFirstVisibleRow;
            if (limit == -1 || limit == 0)
                limit = 0x7fffffff;
            if (!(*(unsigned*)((char*)this + 0x210) & 0x10000)) {
                RectT<int> rr = { 0, 0, 0, 0 };
                ((void(__thiscall*)(void*, RectT<int>*))GVT(ig, 0xc4 / 4))(ig, &rr);
                if (rr.bottom <= limit)
                    limit = rr.bottom + 1;
            }
            for (; i < limit; ++i) {
                float t = GetRowHeightInternal(i) + accum;
                if (t > mfVisibleCellHeight) {
                    float frac = (mfVisibleCellHeight - accum) / (t - accum);
                    if (frac < 0.0f) frac = -frac;
                    if (frac > 0.05f)
                        mfAccumRowFraction += frac;
                    break;
                }
                mfAccumRowFraction += 1.0f;
                accum = t;
            }
        }

        unsigned oldMask = (mSoundIDs[1] != 0 ? 1u : 0u) | (mSoundIDs[0] != 0 ? 2u : 0u);
        TestForPossibleScrollBarAdditionOrRemoval();
        unsigned newMask = (mSoundIDs[1] != 0 ? 1u : 0u) | (mSoundIDs[0] != 0 ? 2u : 0u);
        if (oldMask != newMask)
            RecalculateAll();
        if (g_recalcDepth == 1)
            PlaceAllCellWindows();
    }

    --g_recalcDepth;
    if (g_recalcDepth < 1) {
        *(unsigned char*)((char*)this + 0x214) = 0;
        ((void(__thiscall*)(void*, int, int))GVT((char*)this + 4, 0x7c / 4))((char*)this + 4, 8, 0);
    }
    return true;
}

}  // namespace Gr
