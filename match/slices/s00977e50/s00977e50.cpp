// Slice s00977e50: EA::UTFWinControls::WinGrid cell setters (format, text style, colors, wrapping, alignment,
// border, extra data), SetRowHeight and the SetSizeCachedActualFor{Column,Row} loops.
// MSVC 2008 SP1, /O2 /arch:SSE.
// Retail layout: the IWinGrid subobject sits at WinGrid+0x20c. The Set*Cell* methods run with ecx = that
// subobject (matrices at +0xb4 column formats, +0xe4 row formats, +0x114 cells, default CellFormat at +0x144);
// SetSizeCachedActualFor* run with ecx = WinGrid.
#include "types.h"
#include <math.h>
#include <float.h>

#define FLD(T, p, off) (*(T*)((char*)(p) + (off)))
// Generic interface stub: virtual slot at byte offset N is named sN (only the slots used here are typed).
struct VObj {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual void pad24();
    virtual void pad25();
    virtual void pad26();
    virtual void pad27();
    virtual void pad28();
    virtual void pad29();
    virtual void pad30();
    virtual void s0x7c(int, int);
    virtual void pad32();
    virtual void pad33();
    virtual void pad34();
    virtual void pad35();
    virtual void s0x90();
    virtual void pad37();
    virtual void pad38();
    virtual void pad39();
    virtual void pad40();
    virtual void pad41();
    virtual void pad42();
    virtual void pad43();
    virtual void pad44();
    virtual void pad45();
    virtual void pad46();
    virtual void pad47();
    virtual void pad48();
    virtual void pad49();
    virtual void pad50();
    virtual void pad51();
    virtual void pad52();
    virtual bool s0xd4(int, int);
    virtual void pad54();
    virtual void pad55();
    virtual void pad56();
    virtual void pad57();
    virtual void pad58();
    virtual void pad59();
    virtual void pad60();
    virtual void pad61();
    virtual void pad62();
    virtual void pad63();
    virtual void pad64();
    virtual void pad65();
    virtual void pad66();
    virtual void pad67();
    virtual void pad68();
    virtual void pad69();
};
#define VCALL0(R, p, off)          (((VObj*)(p))->s##off())
#define VCALL1(R, p, off, a)       (((VObj*)(p))->s##off(a))
#define VCALL2(R, p, off, a, b)    (((VObj*)(p))->s##off(a, b))
#define VCALL3(R, p, off, a, b, c) (((VObj*)(p))->s##off(a, b, c))

struct RBNode { RBNode* right; RBNode* left; RBNode* parent; int color; };
RBNode* __cdecl RBTreeIncrement(RBNode*);   // 0x921580
void* operator new(size_t, const char*, int, int, int, int);
void operator delete(void*, const char*, int, int, int, int);   // 0xf473a0 EA 6-arg operator new
#define NEW_G(T) new ("UTFWin/Grid", 0, 0, 0, 0) T
#define NEW_G2(T, a) new ("UTFWin/Grid", 0, 0, 0, 0) T(a)
void* __cdecl operator_new_ea(unsigned size, const char* name, int a, int b, const char* file, int line); // 0xf473a0

struct Iter { void* mat; int* node; RBNode* cur; };
struct RBTree { int alloc; RBNode anchor; int size; };
struct KeyNode { RBNode b; int f10; };                       // node whose int key sits at +0x10

// ---- cell data ----
struct CellFormat {
    uint32_t nTextStyle;
    uint32_t nColor[8];
    uint8_t  nWrapping, nHAlignment, nVAlignment, pad;
    uint32_t nBorder;
    uint32_t nBorderColor;
    CellFormat()                                     // 0x970190
        : nTextStyle(0), nWrapping(0xff), nHAlignment(0), nVAlignment(0), nBorder(0), nBorderColor(0)
    {
        nColor[0] = 0; nColor[1] = 0; nColor[2] = 0; nColor[3] = 0;
        nColor[6] = 0; nColor[7] = 0; nColor[4] = 0; nColor[5] = 0;
    }
};
struct CellFormatExtra : CellFormat {
    float nSizeDefault;
    float nSizeCachedActual;
    CellFormatExtra() : nSizeDefault(-1.0f), nSizeCachedActual(-1.0f) {}     // 0x9701c0
    CellFormatExtra(const CellFormat& f);                                    // 0x970210
};
struct CellData {
    int nCellType, nColumn, nRow;
    void* pCellData;
    CellFormat* pCellFormat;
    void* pExtraData;
    unsigned nCellFlags;
    CellData() {
        nCellType = 0; nColumn = 0; nRow = 0; pCellData = 0; pCellFormat = 0; pExtraData = 0; nCellFlags = 0;
    }
    CellData(void* extra) {
        nCellType = 0; nColumn = 0; nRow = 0; pCellData = 0; pCellFormat = 0; nCellFlags = 0; pExtraData = extra;
    }
};

// ---- SparseMatrix<T>: eastl::map<int, eastl::map<int, T>>; node key at +0x10, value at +0x18 ----
struct ColIterA { void* mat; int* node; int* cur; ColIterA& operator++(); };      // 0x973640
struct SparseMatrixFmt {          // SparseMatrix<CellFormatExtra>
    int pad[12];
    void RowBegin(Iter* ret, int key);                                          // 0x973740
    void RowEnd(Iter* ret, int key);                                            // 0x9737a0
    ColIterA* FindByValue(ColIterA* ret, int value);                            // 0x973c30
    bool GetCellPtr(int a, int b, CellFormatExtra** out);                       // 0x973a90
    bool Set(int a, int b, const CellFormatExtra* v, int flag);                 // 0x976dd0
};
struct SparseMatrixCells {        // SparseMatrix<CellData*>
    int pad[12];
    bool GetCellPtr(int col, int row, CellData*** out);                         // 0x973a90
    void Set(int col, int row, CellData* const* v, int flag);                   // 0x976f90
};
struct SparseMatrixTree { RBTree t; int pad[6]; };

static inline KeyNode* LowerBoundKey(RBTree* t, int key)
{
    KeyNode* pRangeEnd = (KeyNode*)&t->anchor;
    KeyNode* pCurrent = (KeyNode*)t->anchor.parent;
    while (pCurrent) {
        if (!(pCurrent->f10 < key)) { pRangeEnd = pCurrent; pCurrent = (KeyNode*)pCurrent->b.left; }
        else                        pCurrent = (KeyNode*)pCurrent->b.right;
    }
    return pRangeEnd;
}
static inline KeyNode* FindKey(RBTree* t, int key)
{
    KeyNode* it = LowerBoundKey(t, key);
    return (it == (KeyNode*)&t->anchor || key < it->f10) ? (KeyNode*)&t->anchor : it;
}
struct FmtOuter { RBNode b; int f10; int pad14; RBTree inner; };
struct FmtInner { RBNode b; int f10; int pad14; CellFormatExtra v; };

struct WinGridView {
    void* vptr;                                  // +0
    uint32_t pad04[(0xb4 - 4) / 4];
    SparseMatrixFmt   mColFormats;               // +0xb4
    SparseMatrixFmt   mRowFormats;               // +0xe4
    SparseMatrixCells mCells;                    // +0x114
    CellFormat        mDefaultFormat;            // +0x144

    bool SetRowHeight(int start, int count, float h);                        // 0x977e50
    bool SetCellFormat(int col, int row, const CellFormat* fmt);             // 0x977f90
    bool SetCellTextStyle(int col, int row, unsigned style);                 // 0x978250
    bool SetCellColors(int col, int row, int index, unsigned color);         // 0x9783f0
    bool SetCellWrapping(int col, int row, char wrapping);                   // 0x978560
    bool SetCellAlignment(int col, int row, char h, char v);                 // 0x9786c0
    bool SetCellBorder(int col, int row, unsigned border, unsigned color);   // 0x978830
    bool SetCellExtraData(int col, int row, void* extra);                    // 0x978d30
};
struct WinGrid {
    void SetSizeCachedActualForColumn(int start, int count, float v);        // 0x978b50
    void SetSizeCachedActualForRow(int start, int count, float v);           // 0x9789a0
};
// the WinGrid-side helpers called on the real this
struct WinGridReal { void Recalculate(bool b); };                            // 0x970c50

CellFormatExtra::CellFormatExtra(const CellFormat& f) : nSizeDefault(-1.0f), nSizeCachedActual(-1.0f)
{
    *(CellFormat*)this = f;
}

// @ 0x977e50
bool WinGridView::SetRowHeight(int start, int count, float h)
{
    bool ok = true;
    if (h < 0.0f) h = 0.0f;
    for (int row = start; row < start + count; row++) {
        RBTree* t = (RBTree*)&mRowFormats;
        FmtOuter* outer = (FmtOuter*)FindKey(t, row);
        if (outer != (FmtOuter*)&t->anchor) {
            FmtInner* in = (FmtInner*)FindKey(&outer->inner, 0);
            if (in != (FmtInner*)&outer->inner.anchor) {
                in->v.nSizeDefault = h;
                continue;
            }
        }
        CellFormatExtra tmp;
        tmp.nSizeDefault = h;
        if (!mRowFormats.Set(0, row, &tmp, 0)) ok = false;
    }
    return ok;
}

// @ 0x977f90
bool WinGridView::SetCellFormat(int col, int row, const CellFormat* fmt)
{
    bool changed = false;
    if (col == -1) {
        if (row == -1) {
            mDefaultFormat = *fmt;
            return true;
        }
        CellFormatExtra* p = 0;
        if (!mRowFormats.GetCellPtr(0, row, &p)) {
            CellFormatExtra tmp;
            mRowFormats.Set(0, row, &tmp, 0);
            mRowFormats.GetCellPtr(0, row, &p);
        }
        if (!p) return false;
        CellFormatExtra v(*fmt);
        *p = v;
        return true;
    }
    if (row == -1) {
        CellFormatExtra* p = 0;
        if (!mColFormats.GetCellPtr(col, 0, &p)) {
            CellFormatExtra tmp;
            mColFormats.Set(col, 0, &tmp, 0);
            mColFormats.GetCellPtr(col, 0, &p);
        }
        if (!p) return false;
        CellFormatExtra v(*fmt);
        *p = v;
        return true;
    }
    if (!VCALL2(bool, this, 0xd4, col, row)) return false;
    CellData** pp = 0;
    if (mCells.GetCellPtr(col, row, &pp) && pp) {
        CellData* cd = *pp;
        if (!cd->pCellFormat) {
            cd->pCellFormat = NEW_G(CellFormat);
            changed = true;
        } else if (cd->pCellFormat->nTextStyle != 0) {
            changed = true;
        }
        *cd->pCellFormat = *fmt;
    } else {
        CellData* cd = NEW_G(CellData);
        cd->pCellFormat = NEW_G(CellFormat);
        *cd->pCellFormat = *fmt;
        mCells.Set(col, row, &cd, 0);
        changed = true;
    }
    if (fmt->nTextStyle != 0 || changed)
        ((WinGridReal*)((char*)this - 0x20c))->Recalculate(true);
    void* win = (char*)this - 0x208;
    VCALL0(void, win, 0x90);
    return true;
}

// @ 0x978250
bool WinGridView::SetCellTextStyle(int col, int row, unsigned style)
{
    if (!VCALL2(bool, this, 0xd4, col, row)) return false;
    bool changed = false;
    CellData** pp = 0;
    if (style != 0) changed = true;
    if (mCells.GetCellPtr(col, row, &pp) && pp) {
        CellData* cd = *pp;
        if (!cd->pCellFormat) cd->pCellFormat = NEW_G(CellFormat);
        else if (cd->pCellFormat->nTextStyle != 0) changed = true;
        cd->pCellFormat->nTextStyle = style;
    } else {
        CellData* cd = NEW_G(CellData);
        cd->pCellFormat = NEW_G(CellFormat);
        cd->pCellFormat->nTextStyle = style;
        mCells.Set(col, row, &cd, 0);
    }
    if (changed) {
        FLD(char, this, 8) = 1;
        void* win = (char*)this - 0x208;
        VCALL2(void, win, 0x7c, 8, 1);
    }
    return true;
}

// @ 0x9783f0
bool WinGridView::SetCellColors(int col, int row, int index, unsigned color)
{
    if (VCALL2(bool, this, 0xd4, col, row)) {
        CellData** pp = 0;
        if (mCells.GetCellPtr(col, row, &pp) && pp) {
            if (!(*pp)->pCellFormat) (*pp)->pCellFormat = NEW_G(CellFormat);
            (*pp)->pCellFormat->nColor[index] = color;
        } else {
            CellData* cd = NEW_G(CellData);
            cd->pCellFormat = NEW_G(CellFormat);
            cd->pCellFormat->nColor[index] = color;
            mCells.Set(col, row, &cd, 0);
        }
        void* win = (char*)this - 0x208;
        VCALL0(void, win, 0x90);
        return true;
    }
    return false;
}

// @ 0x978560
bool WinGridView::SetCellWrapping(int col, int row, char wrapping)
{
    if (VCALL2(bool, this, 0xd4, col, row)) {
        CellData** pp = 0;
        if (mCells.GetCellPtr(col, row, &pp) && pp) {
            if (!(*pp)->pCellFormat) (*pp)->pCellFormat = NEW_G(CellFormat);
            (*pp)->pCellFormat->nWrapping = wrapping;
        } else {
            CellData* cd = NEW_G(CellData);
            cd->pCellFormat = NEW_G(CellFormat);
            cd->pCellFormat->nWrapping = wrapping;
            mCells.Set(col, row, &cd, 0);
        }
        void* win = (char*)this - 0x208;
        VCALL0(void, win, 0x90);
        return true;
    }
    return false;
}

// @ 0x9786c0
bool WinGridView::SetCellAlignment(int col, int row, char h, char v)
{
    if (VCALL2(bool, this, 0xd4, col, row)) {
        CellData** pp = 0;
        if (mCells.GetCellPtr(col, row, &pp) && pp) {
            if (!(*pp)->pCellFormat) (*pp)->pCellFormat = NEW_G(CellFormat);
            (*pp)->pCellFormat->nHAlignment = h;
            (*pp)->pCellFormat->nVAlignment = v;
        } else {
            CellData* cd = NEW_G(CellData);
            cd->pCellFormat = NEW_G(CellFormat);
            cd->pCellFormat->nHAlignment = h;
            cd->pCellFormat->nVAlignment = v;
            mCells.Set(col, row, &cd, 0);
        }
        void* win = (char*)this - 0x208;
        VCALL0(void, win, 0x90);
        return true;
    }
    return false;
}

// @ 0x978830
bool WinGridView::SetCellBorder(int col, int row, unsigned border, unsigned color)
{
    if (VCALL2(bool, this, 0xd4, col, row)) {
        CellData** pp = 0;
        if (mCells.GetCellPtr(col, row, &pp) && pp) {
            if (!(*pp)->pCellFormat) (*pp)->pCellFormat = NEW_G(CellFormat);
            (*pp)->pCellFormat->nBorder = border;
            (*pp)->pCellFormat->nBorderColor = color;
        } else {
            CellData* cd = NEW_G(CellData);
            cd->pCellFormat = NEW_G(CellFormat);
            cd->pCellFormat->nBorder = border;
            cd->pCellFormat->nBorderColor = color;
            mCells.Set(col, row, &cd, 0);
        }
        void* win = (char*)this - 0x208;
        VCALL0(void, win, 0x90);
        return true;
    }
    return false;
}

// @ 0x978d30
bool WinGridView::SetCellExtraData(int col, int row, void* extra)
{
    FLD(int, this, 0x9c) = 1;
    if (VCALL2(bool, this, 0xd4, col, row)) {
        CellData** pp;
        if (mCells.GetCellPtr(col, row, &pp) && *pp) {
            (*pp)->pExtraData = extra;
        } else if (extra != 0) {
            CellData* cd = NEW_G2(CellData, extra);
            if (cd) mCells.Set(col, row, &cd, 0);
        }
        return true;
    }
    return false;
}

// @ 0x978b50
void WinGrid::SetSizeCachedActualForColumn(int start, int count, float v)
{
    int t = FLD(int, this, 0x264);
    int limit = 0x7fffffff;
    if (t != -1 && t != 0) limit = t - 1;
    if (count == 0x7fffffff) {
        count = 0x7fffffff - start;
        if (start + count > limit) count = limit - start + 1;
        if (v == -1.0f) {
            Iter it, e;
            ((SparseMatrixFmt*)((char*)this + 0x2c0))->RowBegin(&it, 0);
            ((SparseMatrixFmt*)((char*)this + 0x2c0))->RowEnd(&e, 0);
            int* bnode = it.node;
            RBNode* bcur = it.cur;
            int* enode = e.node;
            RBNode* ecur = e.cur;
            for (;;) {
                if (bnode == 0) {
                    if (enode == 0) return;
                } else if (bnode == enode && bcur == ecur) {
                    return;
                }
                ((FmtInner*)bcur)->v.nSizeCachedActual = -1.0f;
                bcur = RBTreeIncrement(bcur);
            }
        }
    }
    if (count == 0) return;
    RBTree* tree = (RBTree*)((char*)this + 0x2c0);
    int col = start;
    while (count--) {
        FmtOuter* o = (FmtOuter*)FindKey(tree, 0);
        FmtInner* in = 0;
        if (o != (FmtOuter*)&tree->anchor) {
            in = (FmtInner*)FindKey(&o->inner, col);
            if (in == (FmtInner*)&o->inner.anchor) in = 0;
        }
        if (in) {
            in->v.nSizeCachedActual = v;
        } else if (fabs(-1.0f - v) > FLT_EPSILON) {
            CellFormatExtra tmp;
            tmp.nSizeCachedActual = v;
            ((SparseMatrixFmt*)tree)->Set(col, 0, &tmp, 0);
        }
        col++;
    }
}

// @ 0x9789a0
void WinGrid::SetSizeCachedActualForRow(int start, int count, float v)
{
    int t = FLD(int, this, 0x268);
    int limit = 0x7fffffff;
    if (t != -1 && t != 0) limit = t - 1;
    if (count == 0x7fffffff) {
        count = 0x7fffffff - start;
        if (start + count > limit) count = limit - start + 1;
        if (fabs(-1.0f - v) < FLT_EPSILON) {
            ColIterA it;
            ((SparseMatrixFmt*)((char*)this + 0x2f0))->FindByValue(&it, 0);
            while (it.cur) {
                ((FmtInner*)((char*)it.cur - 0x14))->v.nSizeCachedActual = -1.0f;
                ++it;
            }
            return;
        }
    }
    if (count == 0) return;
    RBTree* tree = (RBTree*)((char*)this + 0x2f0);
    int row = start;
    while (count--) {
        FmtOuter* o = (FmtOuter*)FindKey(tree, row);
        FmtInner* in = 0;
        if (o != (FmtOuter*)&tree->anchor) {
            in = (FmtInner*)FindKey(&o->inner, 0);
            if (in == (FmtInner*)&o->inner.anchor) in = 0;
        }
        if (in) {
            in->v.nSizeCachedActual = v;
        } else if (v != -1.0f) {
            CellFormatExtra tmp;
            tmp.nSizeCachedActual = v;
            ((SparseMatrixFmt*)tree)->Set(0, row, &tmp, 0);
        }
        row++;
    }
}
