// Slice s00978df0: EA::UTFWinControls::WinGrid sorting. Both functions run with ecx = the IWinGrid subobject
// (WinGrid+0x20c; sparse cell matrix at +0x114, selection list at +0xa8).
//   0x00978df0 SortRowsByColumn: sorts the rows by the cells of one column, then rewrites the row index of every
//              cell in that column (or in all visible columns) and of the selected cells.
//   0x00979440 SortColumnsByRow: the transposed version.
// Method: collect the cells of the sort line, merge_sort their index list with a (compare, cell list, ascending)
// functor, erase and re-insert every cell with its new index, remap the selection list, invalidate.
// MSVC 2008 SP1; flags /O2 /MD /Gy /TP (no EH frame in the original).
#include "types.h"

inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

#define FLD(T, p, off) (*(T*)((char*)(p) + (off)))

struct RBNode { RBNode* right; RBNode* left; RBNode* parent; int color; };
RBNode* __cdecl RBTreeIncrement(RBNode*);                   // 0x921580
void __cdecl RBTreeErase(RBNode* node, RBNode* anchor);     // 0x921880
void* __cdecl operator_new_ea(unsigned size, const char* name, int a, int b, const char* file, int line);   // 0xf473a0
void __cdecl operator_delete_ea(void* p);                   // 0xf47380

struct RBTree
{
    int alloc;
    RBNode anchor;       // right = rightmost, left = leftmost (begin), parent = root
    int size;
    void Find(RBNode** out, const int* key);     // eastl::rbtree::find (0xe39fb0)
    void DoNukeSubtree(RBNode* node);            // eastl::rbtree::DoNukeSubtree (0x9a9600, shared instance)
};
struct KeyNode { RBNode b; int key; };
struct CellData { int nCellType, nColumn, nRow; void* pCellData; void* pCellFormat; void* pExtraData; unsigned nCellFlags; };

// SparseMatrix<CellData*>: outer map keyed by row, inner map keyed by column; inner node = {key, column copy, cell}.
struct InNode { RBNode b; int key; int col; CellData* cell; };
struct OutNode { RBNode b; int key; int idx; RBTree inner; };

struct ColIter { void* mat; OutNode* out; int* cur; ColIter& operator++(); };   // 0x973640 (SparseMatrixColIterator<CellData*>::operator++)

struct SparseMatrixCells
{
    RBTree t;
    int f18;
    int cellCount;       // +0x1c
    int pad[4];
    ColIter* FindByValue(ColIter* ret, int column);              // 0x973c30 (all cells of one column)
    void Set(int col, int row, CellData* const* v, int flag);    // 0x976f90 (InsertCell)
};

static __forceinline KeyNode* FindKeyNode(RBTree* t, int key)
{
    KeyNode* pRangeEnd = (KeyNode*)&t->anchor;
    KeyNode* pCurrent = (KeyNode*)t->anchor.parent;
    while (pCurrent) {
        if (!(pCurrent->key < key)) { pRangeEnd = pCurrent; pCurrent = (KeyNode*)pCurrent->b.left; }
        else                        pCurrent = (KeyNode*)pCurrent->b.right;
    }
    return (pRangeEnd == (KeyNode*)&t->anchor || key < pRangeEnd->key) ? (KeyNode*)&t->anchor : pRangeEnd;
}

// SparseMatrix::erase(col, row): erase the inner node, and the row when it becomes empty.
static __forceinline void EraseCell(SparseMatrixCells* m, int col, int row)
{
    OutNode* outer = (OutNode*)FindKeyNode(&m->t, row);
    if (outer == (OutNode*)&m->t.anchor)
        return;
    InNode* in = (InNode*)FindKeyNode(&outer->inner, col);
    if (in == (InNode*)&outer->inner.anchor)
        return;
    --outer->inner.size;
    RBTreeIncrement(&in->b);
    RBTreeErase(&in->b, &outer->inner.anchor);
    operator_delete_ea(in);
    --m->cellCount;
    if (outer->inner.size == 0) {
        --m->t.size;
        RBTreeIncrement(&outer->b);
        RBTreeErase(&outer->b, &m->t.anchor);
        RBNode* p = outer->inner.anchor.parent;
        while (p) {
            outer->inner.DoNukeSubtree(p->right);
            RBNode* next = p->left;
            operator_delete_ea(p);
            p = next;
        }
        operator_delete_ea(outer);
    }
}

namespace SP {
template <class T> struct SimpleVector     // eastl::vector<T, sp_vector_allocator>
{
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int mAllocator;
    SimpleVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SimpleVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete_ea(mpBegin); }
    void DoInsertValue(T* position, const T& value);        // 0x4558a0 (unsigned) / 0xa80dd0 (pointers)
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
}

// ---- eastl::list<CellCoordinates> (the selection list) ----
struct CellCoord { int col, row; };
struct ListNode { ListNode* next; ListNode* prev; CellCoord value; };
struct ListHead { ListNode* next; ListNode* prev; };
struct ListIter { ListNode* mpNode; };
ListIter* __stdcall ListErase(ListIter* ret, ListIter first, ListIter last);              // 0x973d10
void __stdcall ListInsertRange(ListNode* pos, ListIter first, ListIter last, int tag);    // 0x973d60

static __forceinline void ListPushBack(ListHead* h, const CellCoord& v)
{
    ListNode* n = (ListNode*)operator_new_ea(0x10, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&n->value) CellCoord(v);
    n->next = (ListNode*)h;
    n->prev = h->prev;
    h->prev->next = n;
    h->prev = n;
}
static __forceinline void ListAssign(ListNode* head, ListHead* x)
{
    ListNode* dst = head->next;
    ListNode* src = x->next;
    for (; dst != head && src != (ListNode*)x; dst = dst->next, src = src->next)
        dst->value = src->value;
    ListIter ret;
    ListIter first = { dst }, last = { head };
    if (src == (ListNode*)x) {
        ListErase(&ret, first, last);
    } else {
        ListIter sf = { src }, sl = { (ListNode*)x };
        ListInsertRange(head, sf, sl, 0);
    }
}
static __forceinline void ListClear(ListHead* h)
{
    ListNode* n = h->next;
    while (n != (ListNode*)h) {
        ListNode* next = n->next;
        operator_delete_ea(n);
        n = next;
    }
}

// ---- merge_sort of the index list ----
typedef int (__cdecl *CompareFn)(const CellData*, const CellData*);
int __cdecl DefaultCompare(const CellData*, const CellData*);                // 0x974c30
struct SortFunctor { CompareFn compare; SP::SimpleVector<CellData*>* cells; bool bAscending; };
struct EASTLAllocator;
EASTLAllocator* __cdecl EASTLAllocatorDefault();                             // 0x921240 (returns a global)
void __cdecl merge_sort(unsigned* first, unsigned* last, EASTLAllocator* alloc, SortFunctor cmp);   // 0x976310

// ---- views ----
struct VisRect { int v[4]; };
struct WinGridVT
{
    virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03(); virtual void pad04();
    virtual void pad05(); virtual void pad06(); virtual void pad07(); virtual void pad08(); virtual void pad09();
    virtual void pad10(); virtual void pad11(); virtual void pad12(); virtual void pad13(); virtual void pad14();
    virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
    virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23(); virtual void pad24();
    virtual void pad25(); virtual void pad26(); virtual void pad27(); virtual void pad28(); virtual void pad29();
    virtual void pad30(); virtual void pad31(); virtual void pad32(); virtual void pad33(); virtual void pad34();
    virtual void pad35(); virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39();
    virtual void pad40(); virtual void pad41(); virtual void pad42(); virtual void pad43(); virtual void pad44();
    virtual void pad45(); virtual void pad46(); virtual void pad47(); virtual void pad48();
    virtual void GetVisibleRange(int* rect);                    // 0xc4
};
struct WinGridWindowVT
{
    virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03(); virtual void pad04();
    virtual void pad05(); virtual void pad06(); virtual void pad07(); virtual void pad08(); virtual void pad09();
    virtual void pad10(); virtual void pad11(); virtual void pad12(); virtual void pad13(); virtual void pad14();
    virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
    virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23(); virtual void pad24();
    virtual void pad25(); virtual void pad26(); virtual void pad27(); virtual void pad28(); virtual void pad29();
    virtual void pad30();
    virtual void Invalidate(int what, int flag);                // 0x7c
};
struct WinGrid { void SetSizeCachedActualForRow(int start, int count, float v); };   // 0x9789a0

struct WinGridView : WinGridVT
{
    char pad04[0xa8 - 4];
    ListHead mSelection;                  // +0xa8
    char pad_b0[0x114 - 0xb0];
    SparseMatrixCells mCells;             // +0x114

    void SortRowsByColumn(int nColumn, int nDescending, bool bAllColumns, CompareFn pfnCompare);   // 0x978df0
    void SortColumnsByRow(int nRow, int nDescending, bool bAllRows, CompareFn pfnCompare);         // 0x979440

    __forceinline void FinishSort(VisRect& vis)
    {
        VisRect now;
        GetVisibleRange(now.v);
        if (!(vis.v[0] < now.v[0])) vis.v[0] = now.v[0];
        if (!(vis.v[1] < now.v[1])) vis.v[1] = now.v[1];
        if (!(vis.v[2] > now.v[2])) vis.v[2] = now.v[2];
        if (!(vis.v[3] > now.v[3])) vis.v[3] = now.v[3];
        WinGrid* grid = (WinGrid*)((char*)this - 0x20c);
        grid->SetSizeCachedActualForRow(vis.v[1], vis.v[3] - vis.v[1] + 1, -1.0f);
        FLD(char, this, 8) = 1;
        WinGridWindowVT* win = (WinGridWindowVT*)((char*)this - 0x208);
        win->Invalidate(8, 1);
    }
};

// @ 0x978df0
void WinGridView::SortRowsByColumn(int nColumn, int nDescending, bool bAllColumns, CompareFn pfnCompare)
{
    SP::SimpleVector<unsigned> rows;           // row index of every cell in the sort column, sorted below
    SP::SimpleVector<CellData*> cells;         // those cells
    ListHead newSelection;
    newSelection.next = newSelection.prev = (ListNode*)&newSelection;
    VisRect vis = { { 0, 0, 0, 0 } };
    GetVisibleRange(vis.v);
    if (!pfnCompare)
        pfnCompare = DefaultCompare;

    ColIter it;
    mCells.FindByValue(&it, nColumn);
    while (it.cur) {
        CellData* c = *(CellData**)((char*)it.cur + 4);
        if (c) {
            rows.push_back(*(unsigned*)&c->nRow);
            cells.push_back(c);
        }
        ++it;
    }
    SortFunctor sorter = { pfnCompare, &cells, nDescending == 0 };
    merge_sort(rows.mpBegin, rows.mpEnd, EASTLAllocatorDefault(), sorter);

    int first, count;
    if (bAllColumns) { first = vis.v[0]; count = vis.v[2] - vis.v[0] + 1; }
    else             { first = nColumn;  count = 1; }
    unsigned numRows = rows.size();
    for (int col = first; col < first + count; col++) {
        SP::SimpleVector<CellData*> colCells;
        ColIter ci;
        mCells.FindByValue(&ci, col);
        while (ci.cur) {
            CellData* c = *(CellData**)((char*)ci.cur + 4);
            if (c)
                colCells.push_back(c);
            ++ci;
        }
        unsigned n = colCells.size();
        for (unsigned i = 0; i < n; i++)
            EraseCell(&mCells, colCells.mpBegin[i]->nColumn, colCells.mpBegin[i]->nRow);
        unsigned nextRow = numRows;
        for (unsigned i = 0; i < n; i++) {
            CellData* c = colCells.mpBegin[i];
            unsigned j = 0;
            for (; j < numRows; j++)
                if ((unsigned)c->nRow == rows.mpBegin[j]) { c->nRow = j; break; }
            if (j == numRows)
                c->nRow = nextRow++;
            mCells.Set(c->nColumn, c->nRow, &colCells.mpBegin[i], 0);
        }
    }

    // selected cells follow their rows
    unsigned nextSel = rows.size();
    ListNode* head = (ListNode*)&mSelection;
    for (ListNode* n = head->next; n != head; n = n->next) {
        int selCol = n->value.col;
        if (selCol != nColumn && !bAllColumns) {
            ListPushBack(&newSelection, n->value);
        } else {
            unsigned selRow = (unsigned)n->value.row;
            unsigned* p = rows.mpBegin;
            while (p != rows.mpEnd && *p != selRow) ++p;
            unsigned idx;
            if (p == rows.mpEnd) idx = nextSel++;
            else idx = (unsigned)(p - rows.mpBegin);
            CellCoord nc;
            nc.col = selCol;
            nc.row = idx;
            ListPushBack(&newSelection, nc);
        }
    }
    ListAssign(head, &newSelection);
    FinishSort(vis);
    ListClear(&newSelection);
}

// @ 0x979440
void WinGridView::SortColumnsByRow(int nRow, int nDescending, bool bAllRows, CompareFn pfnCompare)
{
    SP::SimpleVector<unsigned> cols;           // column index of every cell in the sort row, sorted below
    SP::SimpleVector<CellData*> cells;         // those cells
    ListHead newSelection;
    newSelection.next = newSelection.prev = (ListNode*)&newSelection;
    VisRect vis = { { 0, 0, 0, 0 } };
    GetVisibleRange(vis.v);
    if (!pfnCompare)
        pfnCompare = DefaultCompare;

    RBNode* rowNode;
    InNode* it = 0;
    InNode* end = 0;
    mCells.t.Find(&rowNode, &nRow);
    if (rowNode != &mCells.t.anchor)
        it = (InNode*)((OutNode*)rowNode)->inner.anchor.left;
    mCells.t.Find(&rowNode, &nRow);
    if (rowNode != &mCells.t.anchor)
        end = (InNode*)&((OutNode*)rowNode)->inner.anchor;
    while (it != end) {
        CellData* c = it->cell;
        if (c) {
            cols.push_back(*(unsigned*)&c->nColumn);
            cells.push_back(c);
        }
        it = (InNode*)RBTreeIncrement(&it->b);
    }
    SortFunctor sorter = { pfnCompare, &cells, nDescending == 0 };
    merge_sort(cols.mpBegin, cols.mpEnd, EASTLAllocatorDefault(), sorter);

    int first, count;
    if (bAllRows) { first = vis.v[1]; count = vis.v[3] - vis.v[1] + 1; }
    else          { first = nRow;     count = 1; }
    unsigned numCols = cols.size();
    for (int row = first; row < first + count; row++) {
        SP::SimpleVector<CellData*> rowCells;
        OutNode* o = (OutNode*)FindKeyNode(&mCells.t, row);
        InNode* i1 = 0;
        InNode* i2 = 0;
        if (o != (OutNode*)&mCells.t.anchor)
            i1 = (InNode*)o->inner.anchor.left;
        o = (OutNode*)FindKeyNode(&mCells.t, row);
        if (o != (OutNode*)&mCells.t.anchor)
            i2 = (InNode*)&o->inner.anchor;
        while (i1 != i2) {
            CellData* c = i1->cell;
            if (c)
                rowCells.push_back(c);
            i1 = (InNode*)RBTreeIncrement(&i1->b);
        }
        unsigned n = rowCells.size();
        for (unsigned i = 0; i < n; i++)
            EraseCell(&mCells, rowCells.mpBegin[i]->nColumn, rowCells.mpBegin[i]->nRow);
        unsigned nextCol = numCols;
        for (unsigned i = 0; i < n; i++) {
            CellData* c = rowCells.mpBegin[i];
            unsigned j = 0;
            for (; j < numCols; j++)
                if ((unsigned)c->nColumn == cols.mpBegin[j]) { c->nColumn = j; break; }
            if (j == numCols)
                c->nColumn = nextCol++;
            mCells.Set(c->nColumn, c->nRow, &rowCells.mpBegin[i], 0);
        }
    }

    // selected cells follow their columns (the search key is the cell's row, as in the binary)
    unsigned nextSel = cols.size();
    ListNode* head = (ListNode*)&mSelection;
    for (ListNode* n = head->next; n != head; n = n->next) {
        unsigned selRow = (unsigned)n->value.row;
        if ((int)selRow != nRow && !bAllRows) {
            ListPushBack(&newSelection, n->value);
        } else {
            unsigned* p = cols.mpBegin;
            while (p != cols.mpEnd && *p != selRow) ++p;
            unsigned idx;
            if (p == cols.mpEnd) idx = nextSel++;
            else idx = (unsigned)(p - cols.mpBegin);
            CellCoord nc;
            nc.col = idx;
            nc.row = selRow;
            ListPushBack(&newSelection, nc);
        }
    }
    ListAssign(head, &newSelection);
    FinishSort(vis);
    ListClear(&newSelection);
}
