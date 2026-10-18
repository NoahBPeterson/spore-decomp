// src/game/UTFSpore_Win32/Grid.cpp -- migrated from slice(s) s0097a130, s00978df0, s00977e50, s00972e30, s0096f3f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Grid.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/WinGrid.h"
#include "EA/UTFWin/RenderContext.h"
#include <intrin.h>
#include <math.h>
#include <float.h>

// ---- items of slice s0096f3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWinControls {
#define PV(n) virtual void pv##n()
}
}
namespace EA {
namespace UTFWinControls {
struct WinGridSub {
    PV(0);PV(1);PV(2);PV(3);PV(4);PV(5);PV(6);PV(7);PV(8);PV(9);
    PV(10);PV(11);PV(12);PV(13);PV(14);PV(15);PV(16);PV(17);PV(18);PV(19);
    PV(20);PV(21);PV(22);PV(23);PV(24);PV(25);PV(26);PV(27);PV(28);PV(29);
    virtual void OnWheel(int delta);   // +0x78
};
}
}
namespace EA {
namespace UTFWinControls {
struct WinGrid_s0096_f3f0 {
    char sub20c[0x20c];

    void SetDefaultFormatting();                            // 0x009702b0
    void OnMouseWheel(int, int, int, int delta);            // 0x00970540
    int  OnMouseMove(int, float x, float y);                // 0x00970460
};
}
}
// ---- items of slice s0096f3f0 end

// ---- items of slice s00972e30 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define FLD(T, p, off) (*(T*)((char*)(p) + (off)))
struct VObj {
    virtual void s0x0();
    virtual void s0x4();
    virtual void pad2();
    virtual void* s0xc(int);
    virtual void* s0x10();
    virtual void pad5();
    virtual void pad6();
    virtual int s0x1c();
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
    virtual void s0x50(int);
    virtual void pad21();
    virtual void pad22();
    virtual void s0x5c(void*);
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
    virtual void s0x88(int);
    virtual void s0x8c(int);
    virtual void s0x90();
    virtual void pad37();
    virtual void pad38();
    virtual void pad39();
    virtual void pad40();
    virtual void pad41();
    virtual void pad42();
    virtual void s0xac(int, int, int);
    virtual void pad44();
    virtual void pad45();
    virtual void pad46();
    virtual void pad47();
    virtual void pad48();
    virtual void s0xc4(int*);
    virtual void pad50();
    virtual void pad51();
    virtual void pad52();
    virtual bool s0xd4(int, int);
    virtual bool s0xd8(void*);
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
    virtual void s0x114(void*);
};
#define VCALL0(R, p, off)          (((VObj*)(p))->s##off())
#define VCALL1(R, p, off, a)       (((VObj*)(p))->s##off(a))
#define VCALL2(R, p, off, a, b)    (((VObj*)(p))->s##off(a, b))
#define VCALL3(R, p, off, a, b, c) (((VObj*)(p))->s##off(a, b, c))
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; int color; };
RBNode* __cdecl RBTreeIncrement(RBNode*);   // 0x921580
RBNode* __cdecl RBTreeDecrement(RBNode*);   // 0x9215c0
void* __cdecl operator_new_ea(unsigned size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl operator_delete_ea(void* p);                                                               // 0xf47380
struct RBTree {
    int alloc;
    RBNode anchor;      // right = rightmost, left = leftmost (begin), parent = root
    int size;
    void Find(RBNode** out, const int* key);   // eastl::rbtree::find (0xe39fb0)
};
struct InNode  { RBNode b; int f10; int f14; int f18; };
struct OutNode { RBNode b; int f10; int f14; RBTree inner; };
struct Iter    { struct SparseMatrix* mat; OutNode* node; int* cur; Iter() {} Iter(SparseMatrix* m, OutNode* n, int* c) : mat(m), node(n), cur(c) {} };
struct SparseMatrix {
    RBTree t;
    OutNode* Begin() { return (OutNode*)t.anchor.left; }
    OutNode* End()   { return (OutNode*)&t.anchor; }

    bool GetMinMaxUsedRowForCol(int key, int* pMin, int* pMax);     // 0x973800
    int  GetMinUsedColAndRow(int* pRow);                            // 0x973930
    int  GetMaxUsedColAndRow(int* pRow);                            // 0x973980
    int  GetCountForKey(int key);                                   // 0x9739e0
    bool IsCellUsed(int col, int row);                              // 0x973a40
    bool GetCellPtr(int col, int row, void*** out);                 // 0x973a90
    int  CountCellsInRange(int a, int b, int c, int d);             // 0x973b00
    int  GetCellsInRange(int a, int b, int c, int d, int* out);     // 0x973b90
    Iter* FindByValue(Iter* ret, int value);                        // 0x973c30
    Iter* FirstUsed(Iter* ret);                                     // 0x973cc0
    void  RowBegin(Iter* ret, int key);                             // 0x973740
    void  RowEnd(Iter* ret, int key);                               // 0x9737a0
};
static inline InNode* InnerLowerBound(RBTree* t, int key)
{
    InNode* pRangeEnd = (InNode*)&t->anchor;
    InNode* pCurrent = (InNode*)t->anchor.parent;
    while (pCurrent) {
        if (!(pCurrent->f10 < key)) { pRangeEnd = pCurrent; pCurrent = (InNode*)pCurrent->b.left; }
        else                        pCurrent = (InNode*)pCurrent->b.right;
    }
    return pRangeEnd;
}
static inline InNode* InnerFind(RBTree* t, int key)
{
    InNode* it = InnerLowerBound(t, key);
    return (it == (InNode*)&t->anchor || key < it->f10) ? (InNode*)&t->anchor : it;
}
struct Msg { int a, b; unsigned id; int tmp; int c, d; int* pCur; };
struct WinGrid {
    void DoArrowKey(int vk, bool bExtend);             // 0x972e90
    void DoCellWindowMove(int* msg);                   // 0x973330
    bool SetScrollBarDrawableVertical(void* p);        // 0x973390
    bool SetScrollBarDrawableHorizontal(void* p);      // 0x973410
    bool AddScrollBar(bool vert, bool horz);           // 0x973490
    void RemoveScrollBar(bool a, bool b);              // 0x972600
    void SetScrollBarValues();                         // 0x9726c0
};
struct ListHead {
    void Clear();                                      // 0x972d30 (eastl::list<CellCoordinates>::clear)
};
static inline void* AsDrawable(void* d) { return d ? VCALL1(void*, d, 0xc, 0x6ec581fd) : 0; }
void* __cdecl WinScrollbar_CreateDef(int orientation, int a, int w, int h);   // 0x9839b0
struct AutoRefCount { void* p; void Assign(void* v); };                         // 0xb5f950
void* __cdecl interface_cast_IDrawable(void* ref);                              // 0x972db0
struct ColIterA { SparseMatrix* mat; OutNode* out; int* cur; ColIterA& operator++(); };
struct ColIterB { SparseMatrix* mat; OutNode* out; RBNode* in;  ColIterB& operator++(); };
struct CellCoord { int col, row; CellCoord(const CellCoord& o) : col(o.col), row(o.row) {} };
struct ListNode { ListNode* next; ListNode* prev; CellCoord value; };
inline void* operator new(size_t, void* p) { return p; }
struct ListIter {
    ListNode* mpNode;
    ListIter& operator++() { mpNode = mpNode->next; return *this; }
    bool operator!=(const ListIter& o) const { return mpNode != o.mpNode; }
};
static inline ListIter ListErase1(ListIter position)
{
    ++position;
    ListNode* n = position.mpNode->prev;
    n->prev->next = n->next;
    n->next->prev = n->prev;
    operator_delete_ea(n);
    return position;
}
static inline void DoInsertValue(ListNode* pos, const CellCoord& v)
{
    ListNode* n = (ListNode*)operator_new_ea(0x10, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&n->value) CellCoord(v);
    n->next = pos;
    n->prev = pos->prev;
    pos->prev->next = n;
    pos->prev = n;
}
// ---- items of slice s00972e30 end

// ---- items of slice s00977e50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj_s0097_7e50 {
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
#define VCALL0_s0097_7e50(R, p, off)          (((VObj_s0097_7e50*)(p))->s##off())
#define VCALL2_s0097_7e50(R, p, off, a, b)    (((VObj_s0097_7e50*)(p))->s##off(a, b))
void* operator new(size_t, const char*, int, int, int, int);
#define NEW_G(T) new ("UTFWin/Grid", 0, 0, 0, 0) T
#define NEW_G2(T, a) new ("UTFWin/Grid", 0, 0, 0, 0) T(a)
struct Iter_s0097_7e50 { void* mat; int* node; RBNode* cur; };
struct RBTree_s0097_7e50 { int alloc; RBNode anchor; int size; };
struct KeyNode { RBNode b; int f10; };                       // node whose int key sits at +0x10
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
struct ColIterA_s0097_7e50 {  // 0x973640
    void* mat;
    int* node;
    int* cur;
    ColIterA_s0097_7e50& operator++();
};
struct SparseMatrixFmt {          // SparseMatrix<CellFormatExtra>
    int pad[12];
    void RowBegin(Iter_s0097_7e50* ret, int key);                                          // 0x973740
    void RowEnd(Iter_s0097_7e50* ret, int key);                                            // 0x9737a0
    ColIterA_s0097_7e50* FindByValue(ColIterA_s0097_7e50* ret, int value);                            // 0x973c30
    bool GetCellPtr(int a, int b, CellFormatExtra** out);                       // 0x973a90
    bool Set(int a, int b, const CellFormatExtra* v, int flag);                 // 0x976dd0
};
struct SparseMatrixCells {        // SparseMatrix<CellData*>
    int pad[12];
    bool GetCellPtr(int col, int row, CellData*** out);                         // 0x973a90
    void Set(int col, int row, CellData* const* v, int flag);                   // 0x976f90
};
static inline KeyNode* LowerBoundKey(RBTree_s0097_7e50* t, int key)
{
    KeyNode* pRangeEnd = (KeyNode*)&t->anchor;
    KeyNode* pCurrent = (KeyNode*)t->anchor.parent;
    while (pCurrent) {
        if (!(pCurrent->f10 < key)) { pRangeEnd = pCurrent; pCurrent = (KeyNode*)pCurrent->b.left; }
        else                        pCurrent = (KeyNode*)pCurrent->b.right;
    }
    return pRangeEnd;
}
static inline KeyNode* FindKey(RBTree_s0097_7e50* t, int key)
{
    KeyNode* it = LowerBoundKey(t, key);
    return (it == (KeyNode*)&t->anchor || key < it->f10) ? (KeyNode*)&t->anchor : it;
}
struct FmtOuter { RBNode b; int f10; int pad14; RBTree_s0097_7e50 inner; };
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
struct WinGrid_s0097_7e50 {
    void SetSizeCachedActualForColumn(int start, int count, float v);        // 0x978b50
    void SetSizeCachedActualForRow(int start, int count, float v);           // 0x9789a0
};
struct WinGridReal { void Recalculate(bool b); };                            // 0x970c50
CellFormatExtra::CellFormatExtra(const CellFormat& f) : nSizeDefault(-1.0f), nSizeCachedActual(-1.0f)
{
    *(CellFormat*)this = f;
}
// ---- items of slice s00977e50 end

// ---- items of slice s00978df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __cdecl RBTreeErase(RBNode* node, RBNode* anchor);     // 0x921880
struct RBTree_s0097_8df0
{
    int alloc;
    RBNode anchor;       // right = rightmost, left = leftmost (begin), parent = root
    int size;
    void Find(RBNode** out, const int* key);     // eastl::rbtree::find (0xe39fb0)
    void DoNukeSubtree(RBNode* node);            // eastl::rbtree::DoNukeSubtree (0x9a9600, shared instance)
};
struct KeyNode_s0097_8df0 { RBNode b; int key; };
struct CellData_s0097_8df0 { int nCellType, nColumn, nRow; void* pCellData; void* pCellFormat; void* pExtraData; unsigned nCellFlags; };
struct InNode_s0097_8df0 { RBNode b; int key; int col; CellData_s0097_8df0* cell; };
struct OutNode_s0097_8df0 { RBNode b; int key; int idx; RBTree_s0097_8df0 inner; };
struct ColIter { void* mat; OutNode_s0097_8df0* out; int* cur; ColIter& operator++(); };   // 0x973640 (SparseMatrixColIterator<CellData*>::operator++)
struct SparseMatrixCells_s0097_8df0
{
    RBTree_s0097_8df0 t;
    int f18;
    int cellCount;       // +0x1c
    int pad[4];
    ColIter* FindByValue(ColIter* ret, int column);              // 0x973c30 (all cells of one column)
    void Set(int col, int row, CellData_s0097_8df0* const* v, int flag);    // 0x976f90 (InsertCell)
};
static __forceinline KeyNode_s0097_8df0* FindKeyNode(RBTree_s0097_8df0* t, int key)
{
    KeyNode_s0097_8df0* pRangeEnd = (KeyNode_s0097_8df0*)&t->anchor;
    KeyNode_s0097_8df0* pCurrent = (KeyNode_s0097_8df0*)t->anchor.parent;
    while (pCurrent) {
        if (!(pCurrent->key < key)) { pRangeEnd = pCurrent; pCurrent = (KeyNode_s0097_8df0*)pCurrent->b.left; }
        else                        pCurrent = (KeyNode_s0097_8df0*)pCurrent->b.right;
    }
    return (pRangeEnd == (KeyNode_s0097_8df0*)&t->anchor || key < pRangeEnd->key) ? (KeyNode_s0097_8df0*)&t->anchor : pRangeEnd;
}
static __forceinline void EraseCell(SparseMatrixCells_s0097_8df0* m, int col, int row)
{
    OutNode_s0097_8df0* outer = (OutNode_s0097_8df0*)FindKeyNode(&m->t, row);
    if (outer == (OutNode_s0097_8df0*)&m->t.anchor)
        return;
    InNode_s0097_8df0* in = (InNode_s0097_8df0*)FindKeyNode(&outer->inner, col);
    if (in == (InNode_s0097_8df0*)&outer->inner.anchor)
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
struct CellCoord_s0097_8df0 { int col, row; };
struct ListNode_s0097_8df0 { ListNode_s0097_8df0* next; ListNode_s0097_8df0* prev; CellCoord_s0097_8df0 value; };
struct ListHead_s0097_8df0 { ListNode_s0097_8df0* next; ListNode_s0097_8df0* prev; };
struct ListIter_s0097_8df0 { ListNode_s0097_8df0* mpNode; };
ListIter_s0097_8df0* __stdcall ListErase(ListIter_s0097_8df0* ret, ListIter_s0097_8df0 first, ListIter_s0097_8df0 last);              // 0x973d10
void __stdcall ListInsertRange(ListNode_s0097_8df0* pos, ListIter_s0097_8df0 first, ListIter_s0097_8df0 last, int tag);    // 0x973d60
static __forceinline void ListPushBack(ListHead_s0097_8df0* h, const CellCoord_s0097_8df0& v)
{
    ListNode_s0097_8df0* n = (ListNode_s0097_8df0*)operator_new_ea(0x10, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&n->value) CellCoord_s0097_8df0(v);
    n->next = (ListNode_s0097_8df0*)h;
    n->prev = h->prev;
    h->prev->next = n;
    h->prev = n;
}
static __forceinline void ListAssign(ListNode_s0097_8df0* head, ListHead_s0097_8df0* x)
{
    ListNode_s0097_8df0* dst = head->next;
    ListNode_s0097_8df0* src = x->next;
    for (; dst != head && src != (ListNode_s0097_8df0*)x; dst = dst->next, src = src->next)
        dst->value = src->value;
    ListIter_s0097_8df0 ret;
    ListIter_s0097_8df0 first = { dst }, last = { head };
    if (src == (ListNode_s0097_8df0*)x) {
        ListErase(&ret, first, last);
    } else {
        ListIter_s0097_8df0 sf = { src }, sl = { (ListNode_s0097_8df0*)x };
        ListInsertRange(head, sf, sl, 0);
    }
}
static __forceinline void ListClear(ListHead_s0097_8df0* h)
{
    ListNode_s0097_8df0* n = h->next;
    while (n != (ListNode_s0097_8df0*)h) {
        ListNode_s0097_8df0* next = n->next;
        operator_delete_ea(n);
        n = next;
    }
}
typedef int (__cdecl *CompareFn)(const CellData_s0097_8df0*, const CellData_s0097_8df0*);
int __cdecl DefaultCompare(const CellData_s0097_8df0*, const CellData_s0097_8df0*);                // 0x974c30
struct SortFunctor { CompareFn compare; SP::SimpleVector<CellData_s0097_8df0*>* cells; bool bAscending; };
struct EASTLAllocator;
EASTLAllocator* __cdecl EASTLAllocatorDefault();                             // 0x921240 (returns a global)
void __cdecl merge_sort(unsigned* first, unsigned* last, EASTLAllocator* alloc, SortFunctor cmp);   // 0x976310
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
struct WinGrid_s0097_8df0 { void SetSizeCachedActualForRow(int start, int count, float v); };   // 0x9789a0
struct WinGridView_s0097_8df0 : WinGridVT
{
    char pad04[0xa8 - 4];
    ListHead_s0097_8df0 mSelection;                  // +0xa8
    char pad_b0[0x114 - 0xb0];
    SparseMatrixCells_s0097_8df0 mCells;             // +0x114

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
        WinGrid_s0097_8df0* grid = (WinGrid_s0097_8df0*)((char*)this - 0x20c);
        grid->SetSizeCachedActualForRow(vis.v[1], vis.v[3] - vis.v[1] + 1, -1.0f);
        FLD(char, this, 8) = 1;
        WinGridWindowVT* win = (WinGridWindowVT*)((char*)this - 0x208);
        win->Invalidate(8, 1);
    }
};
// ---- items of slice s00978df0 end

// ---- items of slice s0097a130 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWStr[2];   // 0x01667bac
struct Rect { float x1, y1, x2, y2; };
struct CellFormat_s0097_a130 {
    uint32_t nTextStyle;
    uint32_t nColor[8];
    uint8_t  nWrapping, nHAlignment, nVAlignment, pad;
    uint32_t nBorder;
    uint32_t nBorderColor;
    CellFormat_s0097_a130() {
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
    virtual void GetCellFormat(int col,int row,CellFormat_s0097_a130* out);
};
struct RenderContext {
    Renderer2D* Begin2D(int a);   // 0x0095bc10
};
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
struct RBNode_s0097_a130 { RBNode_s0097_a130* right; RBNode_s0097_a130* left; RBNode_s0097_a130* parent; int color; int key; int pad; void* value; };
static RBNode_s0097_a130* LowerBound(RBNode_s0097_a130* hdr, int key) {
    RBNode_s0097_a130* best = hdr;
    RBNode_s0097_a130* n = hdr->parent;
    while (n) {
        if (n->key < key) n = n->right;
        else { best = n; n = n->left; }
    }
    return best;
}
static void* FindCell(RBNode_s0097_a130* rows, int col, int row) {
    RBNode_s0097_a130* r = LowerBound(rows, row);
    if (r == rows || row < r->key) return 0;
    RBNode_s0097_a130* inner = (RBNode_s0097_a130*)((char*)r + 0x1c);
    RBNode_s0097_a130* c = LowerBound(inner, col);
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
    CellFormat_s0097_a130* fmt;
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
struct WinGrid_s0097_a130 {
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
    RBNode_s0097_a130   mCellDataRows;             // +0x324 (map header)
    char     pad8[0x3a8 - (0x324 + sizeof(RBNode_s0097_a130))];
    int      mHitType;                  // +0x3a8
    int      mHitColumn;                // +0x3ac
    int      mHitRow;                   // +0x3b0
    char     pad9[0x404 - 0x3b4];
    HeadingMap mColumnHeadings;         // +0x404
    HeadingMap mRowHeadings;            // +0x424
    char     pad10[0x454 - 0x444];
    CellFormat_s0097_a130 mDefaultHeadingFormatting; // +0x454

    float GetColumnWidthInternal(int col);   // 0x00979db0
    float GetRowHeightInternal(int row);     // 0x00979f10
    void  DrawCellBackground(CellDrawArgs* a);   // 0x00971490
    void  DrawCell(CellDrawArgs* a);         // 0x00971600
    void  DrawText(WString* s, Rect* r, CellDrawArgs* a);   // 0x00971250
    bool  OnRebuild(RenderContext* rc);  // 0x0097a130 (WinGrid::OnRebuild)
};
static WString* FindHeading(HeadingMap& m, int key) {
    unsigned idx = (unsigned)key % m.mnBuckets;
    for (HNode* n = m.mpBuckets[idx]; n; n = n->next)
        if ((int)n->key == key) return &n->value;
    return 0;
}
// ---- items of slice s0097a130 end

// @ 0x009702b0
void EA::UTFWinControls::WinGrid::SetDefaultFormatting()
{
    char* ecx = (char*)this;
    unsigned edx = 0;
    const int esi = (int)0xff000000;
    int eax = -1;

    if (*(int*)(ecx + 0x354) == (int)edx) *(int*)(ecx + 0x354) = esi;
    if (*(int*)(ecx + 0x358) == (int)edx) *(int*)(ecx + 0x358) = eax;
    if (*(int*)(ecx + 0x364) == (int)edx) *(int*)(ecx + 0x364) = eax;
    if (*(int*)(ecx + 0x368) == (int)edx) *(int*)(ecx + 0x368) = esi;
    if (*(int*)(ecx + 0x36c) == (int)edx) *(int*)(ecx + 0x36c) = eax;
    if (*(int*)(ecx + 0x370) == (int)edx) *(int*)(ecx + 0x370) = esi;
    if (*(int*)(ecx + 0x35c) == (int)edx) *(int*)(ecx + 0x35c) = (int)0xffc0c0c0;
    if (*(int*)(ecx + 0x360) == (int)edx) *(int*)(ecx + 0x360) = eax;
    if (*(unsigned char*)(ecx + 0x374) == 0xff) *(unsigned char*)(ecx + 0x374) = 1;
    if (*(unsigned char*)(ecx + 0x375) == (unsigned char)edx) *(unsigned char*)(ecx + 0x375) = 2;
    if (*(unsigned char*)(ecx + 0x376) == (unsigned char)edx) *(unsigned char*)(ecx + 0x376) = 6;
    if (*(int*)(ecx + 0x378) == (int)edx) *(int*)(ecx + 0x378) = edx;
    if (*(int*)(ecx + 0x37c) == (int)edx) *(int*)(ecx + 0x37c) = esi;
    if (*(int*)(ecx + 0x458) == (int)edx) *(int*)(ecx + 0x458) = esi;
    if (*(int*)(ecx + 0x45c) == (int)edx) *(int*)(ecx + 0x45c) = eax;
    if (*(int*)(ecx + 0x468) == (int)edx) *(int*)(ecx + 0x468) = esi;
    eax = (int)0xffdcdcff;
    if (*(int*)(ecx + 0x46c) == (int)edx) *(int*)(ecx + 0x46c) = eax;
    if (*(int*)(ecx + 0x470) == (int)edx) *(int*)(ecx + 0x470) = esi;
    if (*(int*)(ecx + 0x474) == (int)edx) *(int*)(ecx + 0x474) = eax;
    if (*(int*)(ecx + 0x460) == (int)edx) *(int*)(ecx + 0x460) = (int)0xff808080;
    if (*(int*)(ecx + 0x464) == (int)edx) *(int*)(ecx + 0x464) = (int)0xffdcdcdc;
    if (*(unsigned char*)(ecx + 0x478) == 0xff) *(unsigned char*)(ecx + 0x478) = 1;
    if (*(unsigned char*)(ecx + 0x479) == (unsigned char)edx) *(unsigned char*)(ecx + 0x479) = 2;
    if (*(unsigned char*)(ecx + 0x47a) == (unsigned char)edx) *(unsigned char*)(ecx + 0x47a) = 6;
    if (*(int*)(ecx + 0x47c) == (int)edx) *(int*)(ecx + 0x47c) = edx;
    if (*(int*)(ecx + 0x480) == (int)edx) *(int*)(ecx + 0x480) = esi;
    *(int*)(ecx + 0x274) = esi;
    *(int*)(ecx + 0x278) = esi;
    *(int*)(ecx + 0x27c) = esi;
}






// @ 0x00970460
bool EA::UTFWinControls::WinGrid::OnMouseMove(float a0, float x, unsigned int y)
{
    char* esi = (char*)this;
    void* vt = *(void**)(esi + 0x20c);
    float area[3];
    int hit;
    typedef int(__fastcall* Fn)(void*, void*, float, float);
    Fn fn = (Fn)((char*)vt + 0x19c);
    hit = fn((char*)esi + 0x20c, 0, x, y);
    if ((hit & 0xff) == 0)
        return 0;
    return 1;
}






// @ 0x00970540
namespace EA { namespace UTFWinControls {
void WinGrid_s0096_f3f0::OnMouseWheel(int, int, int, int delta)
{
    ((WinGridSub*)((char*)this + 0x20c))->OnWheel(delta / -100);
}
}}  // namespace EA::UTFWinControls





// @ 0x00972e30
RBNode* __stdcall CreateNodeCopy(const RBNode* src, RBNode* parent)
{
    RBNode* n = (RBNode*)operator_new_ea(0x1c, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int* dst = (int*)n + 4;
    if (dst) {
        dst[0] = FLD(int, src, 0x10);
        dst[1] = FLD(int, src, 0x14);
        dst[2] = FLD(int, src, 0x18);
    }
    n->right = 0;
    n->left = 0;
    n->parent = parent;
    *(char*)&n->color = FLD(char, src, 0xc);
    return n;
}




// @ 0x00972e90
void EA::UTFWinControls::WinGrid::DoArrowKey(unsigned int vk, unsigned int bExtend)
{
    struct { int col, row; } cur = {0, 0};   // CellCoordinates: msg.pCur points at both
    int vis[4] = {0, 0, 0, 0};
    void* view = (char*)this + 0x20c;
    VCALL1(void, view, 0xc4, vis);
    RBNode* sel = (RBNode*)((char*)this + 0x2b4);
    if (sel->right != sel) {                 // list not empty: start from the first selected cell
        RBNode* first = (RBNode*)sel->left;
        cur.col = FLD(int, first, 8);
        cur.row = FLD(int, first, 0xc);
    }
    switch (vk) {
    case 0x25:
        if (cur.col <= 0) return;
        cur.col--;
        break;
    case 0x26:
        if (cur.row <= 0) return;
        cur.row--;
        break;
    case 0x27: {
        int t = FLD(int, this, 0x264);
        unsigned bit = 0;
        if ((t != -1 && t != 0) || !(FLD(unsigned, this, 0x210) & 0x8000)) {
            bit = FLD(unsigned, this, 0x210) & 0x8000;
            if (!bit) t = vis[2] + 1;
            if (cur.col >= t - 1) {
                if (bit) return;
                break;
            }
        }
        cur.col++;
        break;
    }
    case 0x28: {
        int t = FLD(int, this, 0x268);
        unsigned bit = 0;
        if ((t != -1 && t != 0) || !(FLD(unsigned, this, 0x210) & 0x10000)) {
            bit = FLD(unsigned, this, 0x210) & 0x10000;
            if (!bit) t = vis[3] + 1;
            if (cur.row >= t - 1) {
                if (bit) return;
                break;
            }
        }
        cur.row++;
        break;
    }
    default:
        return;
    }
    if (sel->right != sel && !bExtend) ((ListHead*)sel)->Clear();
    VCALL3(void, view, 0xac, cur.col, cur.row, 1);
    Msg msg;
    msg.id = 0x9a1552d2;
    msg.tmp = FLD(int, this, 0x84);
    if (msg.tmp == 0) msg.tmp = FLD(int, this, 0x80);
    msg.pCur = &cur.col;
    void* win = (char*)this + 4;
    VCALL1(void, win, 0x114, &msg);
    switch (vk - 0x25) {
    case 0:
        if (cur.col < FLD(int, this, 0x254)) VCALL1(void, view, 0x88, cur.col);
        break;
    case 1:
        if (cur.row < FLD(int, this, 0x258)) VCALL1(void, view, 0x8c, cur.row);
        break;
    case 2: {
        float vc = FLD(float, this, 0x25c);
        if ((float)cur.col >= (float)FLD(int, this, 0x254) + vc)
            VCALL1(void, view, 0x88, cur.col - (int)vc + 1);
        break;
    }
    case 3: {
        float vr = FLD(float, this, 0x260);
        if ((float)cur.row >= (float)FLD(int, this, 0x258) + vr)
            VCALL1(void, view, 0x8c, cur.row - (int)vr + 1);
        break;
    }
    }
    SetScrollBarValues();
    FLD(char, this, 0x214) = 1;
    VCALL2(void, win, 0x7c, 8, 1);
}




// @ 0x00973200
void EA::UTFWinControls::WinGrid::ClearSelection()
{
    RBNode* head = (RBNode*)((char*)this + 0xa8);
    if (head->right != head) {
        RBNode* n = head->right;
        while (n != head) {
            RBNode* cur = n;
            n = n->right;
            operator_delete_ea(cur);
        }
        VObj* win = (VObj*)((char*)this - 0x208);
        head->right = head;
        head->left = head;
        win->s0x90();
        if (FLD(__int64, this, 0x84) == 0) {
            FLD(int, this, 0x190) = 0;
            FLD(int, this, 0x194) = -1;
            FLD(int, this, 0x198) = -1;
        }
    }
}




// @ 0x00973330
void WinGrid::DoCellWindowMove(int* msg)
{
    if (msg[0] == 1) {
        int w = msg[3];
        if (w != 0) {
            RBNode* end = (RBNode*)((char*)this + 0x384);
            for (RBNode* n = end->left; n != end; n = RBTreeIncrement(n)) {
                if (FLD(int, n, 0x10) == 1 && FLD(int, n, 0x1c) == w) {
                    FLD(int, n, 0x14) = msg[1];
                    FLD(int, n, 0x18) = msg[2];
                    return;
                }
            }
        }
    }
}




// @ 0x00973390
bool WinGrid::SetScrollBarDrawableVertical(void* p)
{
    void* old = FLD(void*, this, 0x1f4);
    if (p != old) {
        if (p) VCALL0(void, p, 0x0);
        FLD(void*, this, 0x1f4) = p;
        if (old) VCALL0(void, old, 0x4);
    }
    void* sb = FLD(void*, this, 0x1ec);
    if (sb) VCALL1(void, sb, 0x5c, AsDrawable(FLD(void*, this, 0x1f4)));
    return true;
}




// @ 0x00973410
bool WinGrid::SetScrollBarDrawableHorizontal(void* p)
{
    void* old = FLD(void*, this, 0x1f8);
    if (p != old) {
        if (p) VCALL0(void, p, 0x0);
        FLD(void*, this, 0x1f8) = p;
        if (old) VCALL0(void, old, 0x4);
    }
    void* sb = FLD(void*, this, 0x1f0);
    if (sb) VCALL1(void, sb, 0x5c, AsDrawable(FLD(void*, this, 0x1f8)));
    return true;
}




// @ 0x00973490
bool WinGrid::AddScrollBar(bool vert, bool horz)
{
    bool added = false;
    if (vert && (FLD(unsigned, this, 0x210) & 4) && FLD(void*, this, 0x3f8) == 0) {
        AutoRefCount* ref = (AutoRefCount*)((char*)this + 0x3f8);
        ref->Assign(WinScrollbar_CreateDef(2, 0, 10, 10));
        if (ref->p) {
            void* w = VCALL0(void*, ref->p, 0x10);
            VCALL1(void, w, 0x50, 0x1a7c4511);
            w = VCALL0(void*, ref->p, 0x10);
            VCALL2(void, w, 0x7c, 0x200, 1);
            if (FLD(void*, this, 0x400)) {
                void* sb = ref->p;
                VCALL1(void, sb, 0x5c, interface_cast_IDrawable((char*)this + 0x400));
            }
            void* sb = ref->p;
            void* win = (char*)this + 4;
            added = VCALL1(bool, win, 0xd8, VCALL0(int, sb, 0x10));
        }
    }
    if (horz && (FLD(unsigned, this, 0x210) & 2) && FLD(void*, this, 0x3fc) == 0) {
        AutoRefCount* ref = (AutoRefCount*)((char*)this + 0x3fc);
        ref->Assign(WinScrollbar_CreateDef(1, 0, 10, 10));
        if (ref->p) {
            void* w = VCALL0(void*, ref->p, 0x10);
            VCALL1(void, w, 0x50, 0x1a7c4510);
            w = VCALL0(void*, ref->p, 0x10);
            VCALL2(void, w, 0x7c, 0x200, 1);
            if (FLD(void*, this, 0x404)) {
                void* sb = ref->p;
                VCALL1(void, sb, 0x5c, interface_cast_IDrawable((char*)this + 0x404));
            }
            void* sb = ref->p;
            void* win = (char*)this + 4;
            added = VCALL1(bool, win, 0xd8, VCALL0(int, sb, 0x10));
        }
    }
    if (added) {
        void* win = (char*)this + 4;
        FLD(char, this, 0x214) = 1;
        VCALL2(void, win, 0x7c, 8, 1);
    }
    return true;
}




// @ 0x00973640
ColIterA& ColIterA::operator++()
{
    out = (OutNode*)RBTreeIncrement(&out->b);
    while (out != mat->End()) {
        InNode* end = (InNode*)&out->inner.anchor;
        for (InNode* in = (InNode*)out->inner.anchor.left; in != end; in = (InNode*)RBTreeIncrement(&in->b)) {
            if (in->f14 == *cur) { cur = &in->f14; return *this; }
        }
        out = (OutNode*)RBTreeIncrement(&out->b);
    }
    cur = 0;
    return *this;
}




// @ 0x009736c0
ColIterB& ColIterB::operator++()
{
    in = RBTreeIncrement(in);
    if (in == (RBNode*)&out->inner.anchor) {
        in = 0;
        out = (OutNode*)RBTreeIncrement(&out->b);
        while (out != mat->End()) {
            if (out->inner.size != 0) { in = out->inner.anchor.left; break; }
            out = (OutNode*)RBTreeIncrement(&out->b);
        }
    }
    return *this;
}




// @ 0x00973740
void SparseMatrix::RowBegin(Iter* ret, int key)
{
    RBNode* it;
    t.Find(&it, &key);
    if (it != &t.anchor) {
        OutNode* n = (OutNode*)it;
        ret->mat = this;
        ret->node = (OutNode*)&n->f14;
        ret->cur = (int*)n->inner.anchor.left;
    } else {
        ret->mat = this;
        ret->node = 0;
        ret->cur = 0;
    }
}




// @ 0x009737a0
void SparseMatrix::RowEnd(Iter* ret, int key)
{
    RBNode* it;
    t.Find(&it, &key);
    if (it != &t.anchor) {
        OutNode* n = (OutNode*)it;
        ret->node = (OutNode*)&n->f14;
        ret->mat = this;
        ret->cur = (int*)&n->inner.anchor;
    } else {
        ret->mat = this;
        ret->node = 0;
        ret->cur = 0;
    }
}




// @ 0x00973800
bool SparseMatrix::GetMinMaxUsedRowForCol(int key, int* pMin, int* pMax)
{
    *pMin = 0x7fffffff;
    *pMax = 0x80000000;
    bool r = false;
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        if (InnerFind(&n->inner, key) != (InNode*)&n->inner.anchor) {
            *pMin = n->f14;
            *pMax = n->f14;
            r = true;
            // reverse_iterator walk: each dereference decrements a copy of the base, ++ decrements the base
            for (OutNode* base = End(); base != Begin(); base = (OutNode*)RBTreeDecrement(&base->b)) {
                OutNode* m = (OutNode*)RBTreeDecrement(&base->b);
                if (InnerFind(&m->inner, key) != (InNode*)&m->inner.anchor) {
                    *pMax = m->f14;
                    return true;
                }
            }
            return true;
        }
    }
    return r;
}




// @ 0x00973930
int SparseMatrix::GetMinUsedColAndRow(int* pRow)
{
    int r = 0x80000000;
    *pRow = 0x80000000;
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        int v = ((InNode*)n->inner.anchor.left)->f14;
        if (v < r || r == 0x80000000) {
            r = v;
            *pRow = n->f14;
        }
    }
    return r;
}




// @ 0x00973980
int SparseMatrix::GetMaxUsedColAndRow(int* pRow)
{
    int r = 0x80000000;
    *pRow = 0x80000000;
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        InNode* last = (InNode*)RBTreeDecrement(&n->inner.anchor);
        int v = last->f14;
        if (v > r || r == 0x80000000) {
            r = v;
            *pRow = n->f14;
        }
    }
    return r;
}




// @ 0x009739e0
int SparseMatrix::GetCountForKey(int key)
{
    int count = 0;
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        if (InnerFind(&n->inner, key) != (InNode*)&n->inner.anchor) count++;
    }
    return count;
}




// @ 0x00973a40
bool SparseMatrix::IsCellUsed(int col, int row)
{
    RBNode* it;
    t.Find(&it, &row);
    if (it == &t.anchor) return false;
    OutNode* n = (OutNode*)it;
    RBNode* in;
    n->inner.Find(&in, &col);
    return in != &n->inner.anchor;
}




// @ 0x00973a90
bool SparseMatrix::GetCellPtr(int col, int row, void*** out)
{
    RBNode* it;
    t.Find(&it, &row);
    if (it == &t.anchor) return false;
    OutNode* n = (OutNode*)it;
    RBNode* in;
    n->inner.Find(&in, &col);
    if (in == &n->inner.anchor) return false;
    if (out) *out = (void**)&((InNode*)in)->f18;
    return true;
}




// @ 0x00973b00
int SparseMatrix::CountCellsInRange(int a, int b, int c, int d)
{
    int count = 0;
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        if (n->f14 < c) continue;
        if (n->f14 > d) break;
        InNode* end = (InNode*)&n->inner.anchor;
        for (InNode* in = (InNode*)n->inner.anchor.left; in != end; in = (InNode*)RBTreeIncrement(&in->b)) {
            if (in->f14 < a) continue;
            if (in->f14 > b) break;
            count++;
        }
    }
    return count;
}




// @ 0x00973b90
int SparseMatrix::GetCellsInRange(int a, int b, int c, int d, int* out)
{
    int count = 0;
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        if (n->f14 < c) continue;
        if (n->f14 > d) break;
        InNode* end = (InNode*)&n->inner.anchor;
        for (InNode* in = (InNode*)n->inner.anchor.left; in != end; in = (InNode*)RBTreeIncrement(&in->b)) {
            if (in->f14 < a) continue;
            if (in->f14 > b) break;
            if (out) {
                out[count * 3 + 0] = in->f14;
                out[count * 3 + 1] = n->f14;
                out[count * 3 + 2] = in->f18;
            }
            count++;
        }
    }
    return count;
}




// @ 0x00973c30
Iter* SparseMatrix::FindByValue(Iter* ret, int value)
{
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        InNode* end = (InNode*)&n->inner.anchor;
        for (InNode* in = (InNode*)n->inner.anchor.left; in != end; in = (InNode*)RBTreeIncrement(&in->b)) {
            if (in->f14 == value) {
                ret->mat = this;
                ret->node = n;
                ret->cur = &in->f14;
                return ret;
            }
        }
    }
    ret->mat = this;
    ret->node = End();
    ret->cur = 0;
    return ret;
}




// @ 0x00973cc0
Iter* SparseMatrix::FirstUsed(Iter* ret)
{
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        if (n->inner.size != 0) {
            *ret = Iter(this, n, (int*)n->inner.anchor.left);
            return ret;
        }
    }
    *ret = Iter(this, End(), 0);
    return ret;
}




// @ 0x00973d10
ListIter* __stdcall ListErase(ListIter* ret, ListIter first, ListIter last)
{
    while (first != last) first = ListErase1(first);
    *ret = last;
    return ret;
}




// @ 0x00973d60
void __stdcall ListInsertRange(ListNode* pos, ListIter first, ListIter last, int tag)
{
    for (; first != last; ++first)
        DoInsertValue(pos, first.mpNode->value);
}



// @ 0x00977e50
bool WinGridView::SetRowHeight(int start, int count, float h)
{
    bool ok = true;
    if (h < 0.0f) h = 0.0f;
    for (int row = start; row < start + count; row++) {
        RBTree_s0097_7e50* t = (RBTree_s0097_7e50*)&mRowFormats;
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



// @ 0x00977f90
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
    if (!VCALL2_s0097_7e50(bool, this, 0xd4, col, row)) return false;
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
    VCALL0_s0097_7e50(void, win, 0x90);
    return true;
}



// @ 0x00978250
bool WinGridView::SetCellTextStyle(int col, int row, unsigned style)
{
    if (!VCALL2_s0097_7e50(bool, this, 0xd4, col, row)) return false;
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
        VCALL2_s0097_7e50(void, win, 0x7c, 8, 1);
    }
    return true;
}



// @ 0x009783f0
bool WinGridView::SetCellColors(int col, int row, int index, unsigned color)
{
    if (VCALL2_s0097_7e50(bool, this, 0xd4, col, row)) {
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
        VCALL0_s0097_7e50(void, win, 0x90);
        return true;
    }
    return false;
}



// @ 0x00978560
bool WinGridView::SetCellWrapping(int col, int row, char wrapping)
{
    if (VCALL2_s0097_7e50(bool, this, 0xd4, col, row)) {
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
        VCALL0_s0097_7e50(void, win, 0x90);
        return true;
    }
    return false;
}



// @ 0x009786c0
bool WinGridView::SetCellAlignment(int col, int row, char h, char v)
{
    if (VCALL2_s0097_7e50(bool, this, 0xd4, col, row)) {
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
        VCALL0_s0097_7e50(void, win, 0x90);
        return true;
    }
    return false;
}



// @ 0x00978830
bool WinGridView::SetCellBorder(int col, int row, unsigned border, unsigned color)
{
    if (VCALL2_s0097_7e50(bool, this, 0xd4, col, row)) {
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
        VCALL0_s0097_7e50(void, win, 0x90);
        return true;
    }
    return false;
}



// @ 0x009789a0
void WinGrid_s0097_7e50::SetSizeCachedActualForRow(int start, int count, float v)
{
    int t = FLD(int, this, 0x268);
    int limit = 0x7fffffff;
    if (t != -1 && t != 0) limit = t - 1;
    if (count == 0x7fffffff) {
        count = 0x7fffffff - start;
        if (start + count > limit) count = limit - start + 1;
        if (fabs(-1.0f - v) < FLT_EPSILON) {
            ColIterA_s0097_7e50 it;
            ((SparseMatrixFmt*)((char*)this + 0x2f0))->FindByValue(&it, 0);
            while (it.cur) {
                ((FmtInner*)((char*)it.cur - 0x14))->v.nSizeCachedActual = -1.0f;
                ++it;
            }
            return;
        }
    }
    if (count == 0) return;
    RBTree_s0097_7e50* tree = (RBTree_s0097_7e50*)((char*)this + 0x2f0);
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



// @ 0x00978b50
void WinGrid_s0097_7e50::SetSizeCachedActualForColumn(int start, int count, float v)
{
    int t = FLD(int, this, 0x264);
    int limit = 0x7fffffff;
    if (t != -1 && t != 0) limit = t - 1;
    if (count == 0x7fffffff) {
        count = 0x7fffffff - start;
        if (start + count > limit) count = limit - start + 1;
        if (v == -1.0f) {
            Iter_s0097_7e50 it, e;
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
    RBTree_s0097_7e50* tree = (RBTree_s0097_7e50*)((char*)this + 0x2c0);
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



// @ 0x00978d30
bool WinGridView::SetCellExtraData(int col, int row, void* extra)
{
    FLD(int, this, 0x9c) = 1;
    if (VCALL2_s0097_7e50(bool, this, 0xd4, col, row)) {
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


// @ 0x00978df0
void WinGridView_s0097_8df0::SortRowsByColumn(int nColumn, int nDescending, bool bAllColumns, CompareFn pfnCompare)
{
    SP::SimpleVector<unsigned> rows;           // row index of every cell in the sort column, sorted below
    SP::SimpleVector<CellData_s0097_8df0*> cells;         // those cells
    ListHead_s0097_8df0 newSelection;
    newSelection.next = newSelection.prev = (ListNode_s0097_8df0*)&newSelection;
    VisRect vis = { { 0, 0, 0, 0 } };
    GetVisibleRange(vis.v);
    if (!pfnCompare)
        pfnCompare = DefaultCompare;

    ColIter it;
    mCells.FindByValue(&it, nColumn);
    while (it.cur) {
        CellData_s0097_8df0* c = *(CellData_s0097_8df0**)((char*)it.cur + 4);
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
        SP::SimpleVector<CellData_s0097_8df0*> colCells;
        ColIter ci;
        mCells.FindByValue(&ci, col);
        while (ci.cur) {
            CellData_s0097_8df0* c = *(CellData_s0097_8df0**)((char*)ci.cur + 4);
            if (c)
                colCells.push_back(c);
            ++ci;
        }
        unsigned n = colCells.size();
        for (unsigned i = 0; i < n; i++)
            EraseCell(&mCells, colCells.mpBegin[i]->nColumn, colCells.mpBegin[i]->nRow);
        unsigned nextRow = numRows;
        for (unsigned i = 0; i < n; i++) {
            CellData_s0097_8df0* c = colCells.mpBegin[i];
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
    ListNode_s0097_8df0* head = (ListNode_s0097_8df0*)&mSelection;
    for (ListNode_s0097_8df0* n = head->next; n != head; n = n->next) {
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
            CellCoord_s0097_8df0 nc;
            nc.col = selCol;
            nc.row = idx;
            ListPushBack(&newSelection, nc);
        }
    }
    ListAssign(head, &newSelection);
    FinishSort(vis);
    ListClear(&newSelection);
}


// @ 0x00979440
void WinGridView_s0097_8df0::SortColumnsByRow(int nRow, int nDescending, bool bAllRows, CompareFn pfnCompare)
{
    SP::SimpleVector<unsigned> cols;           // column index of every cell in the sort row, sorted below
    SP::SimpleVector<CellData_s0097_8df0*> cells;         // those cells
    ListHead_s0097_8df0 newSelection;
    newSelection.next = newSelection.prev = (ListNode_s0097_8df0*)&newSelection;
    VisRect vis = { { 0, 0, 0, 0 } };
    GetVisibleRange(vis.v);
    if (!pfnCompare)
        pfnCompare = DefaultCompare;

    RBNode* rowNode;
    InNode_s0097_8df0* it = 0;
    InNode_s0097_8df0* end = 0;
    mCells.t.Find(&rowNode, &nRow);
    if (rowNode != &mCells.t.anchor)
        it = (InNode_s0097_8df0*)((OutNode_s0097_8df0*)rowNode)->inner.anchor.left;
    mCells.t.Find(&rowNode, &nRow);
    if (rowNode != &mCells.t.anchor)
        end = (InNode_s0097_8df0*)&((OutNode_s0097_8df0*)rowNode)->inner.anchor;
    while (it != end) {
        CellData_s0097_8df0* c = it->cell;
        if (c) {
            cols.push_back(*(unsigned*)&c->nColumn);
            cells.push_back(c);
        }
        it = (InNode_s0097_8df0*)RBTreeIncrement(&it->b);
    }
    SortFunctor sorter = { pfnCompare, &cells, nDescending == 0 };
    merge_sort(cols.mpBegin, cols.mpEnd, EASTLAllocatorDefault(), sorter);

    int first, count;
    if (bAllRows) { first = vis.v[1]; count = vis.v[3] - vis.v[1] + 1; }
    else          { first = nRow;     count = 1; }
    unsigned numCols = cols.size();
    for (int row = first; row < first + count; row++) {
        SP::SimpleVector<CellData_s0097_8df0*> rowCells;
        OutNode_s0097_8df0* o = (OutNode_s0097_8df0*)FindKeyNode(&mCells.t, row);
        InNode_s0097_8df0* i1 = 0;
        InNode_s0097_8df0* i2 = 0;
        if (o != (OutNode_s0097_8df0*)&mCells.t.anchor)
            i1 = (InNode_s0097_8df0*)o->inner.anchor.left;
        o = (OutNode_s0097_8df0*)FindKeyNode(&mCells.t, row);
        if (o != (OutNode_s0097_8df0*)&mCells.t.anchor)
            i2 = (InNode_s0097_8df0*)&o->inner.anchor;
        while (i1 != i2) {
            CellData_s0097_8df0* c = i1->cell;
            if (c)
                rowCells.push_back(c);
            i1 = (InNode_s0097_8df0*)RBTreeIncrement(&i1->b);
        }
        unsigned n = rowCells.size();
        for (unsigned i = 0; i < n; i++)
            EraseCell(&mCells, rowCells.mpBegin[i]->nColumn, rowCells.mpBegin[i]->nRow);
        unsigned nextCol = numCols;
        for (unsigned i = 0; i < n; i++) {
            CellData_s0097_8df0* c = rowCells.mpBegin[i];
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
    ListNode_s0097_8df0* head = (ListNode_s0097_8df0*)&mSelection;
    for (ListNode_s0097_8df0* n = head->next; n != head; n = n->next) {
        unsigned selRow = (unsigned)n->value.row;
        if ((int)selRow != nRow && !bAllRows) {
            ListPushBack(&newSelection, n->value);
        } else {
            unsigned* p = cols.mpBegin;
            while (p != cols.mpEnd && *p != selRow) ++p;
            unsigned idx;
            if (p == cols.mpEnd) idx = nextSel++;
            else idx = (unsigned)(p - cols.mpBegin);
            CellCoord_s0097_8df0 nc;
            nc.col = idx;
            nc.row = selRow;
            ListPushBack(&newSelection, nc);
        }
    }
    ListAssign(head, &newSelection);
    FinishSort(vis);
    ListClear(&newSelection);
}

// @ 0x0097a130
bool WinGrid_s0097_a130::OnRebuild(RenderContext* rc)
{
    CellFormat_s0097_a130 fmt;
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
