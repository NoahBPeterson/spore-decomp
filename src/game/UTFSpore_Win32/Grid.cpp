// src/game/UTFSpore_Win32/Grid.cpp -- migrated from slice(s) s0097bfb0, s0097b110, s00979bc0, s00976f90, s00975ea0, s00974c60, s00973dd0, s00971eb0, s00970f30, s00970570, s0097cea0, s0097a130, s00978df0, s00977e50, s00972e30, s0096f3f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Grid.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/WinGrid.h"
#include "EA/UTFWin/RenderContext.h"
#include <intrin.h>
#include <math.h>
#include <float.h>
#include "EA/UTFWin/Image.h"
#include "EA/UTFWinControls/ImageDrawable.h"
#include "EA/UTFWin/cDropShadowDescriptor.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/CustomWindow.h"
#include <string.h>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s0096f3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWinControls {
#define PV(n) virtual void pv##n()
}
}
namespace EA {
namespace UTFWinControls {
struct WinGridSub {
PV(0);
PV(1);
PV(2);
PV(3);
PV(4);
PV(5);
PV(6);
PV(7);
PV(8);
PV(9);
PV(10);
PV(11);
PV(12);
PV(13);
PV(14);
PV(15);
PV(16);
PV(17);
PV(18);
PV(19);
PV(20);
PV(21);
PV(22);
PV(23);
PV(24);
PV(25);
PV(26);
PV(27);
PV(28);
PV(29);
    virtual void OnWheel(int delta);   // +0x78
PV(31);
PV(32);
PV(33);
PV(34);
PV(35);
PV(36);
PV(37);
PV(38);
PV(39);
PV(40);
PV(41);
PV(42);
PV(43);
PV(44);
PV(45);
PV(46);
PV(47);
PV(48);
PV(49);
PV(50);
PV(51);
PV(52);
PV(53);
PV(54);
PV(55);
PV(56);
PV(57);
PV(58);
PV(59);
PV(60);
PV(61);
PV(62);
PV(63);
PV(64);
PV(65);
PV(66);
PV(67);
PV(68);
PV(69);
PV(70);
PV(71);
PV(72);
PV(73);
PV(74);
PV(75);
PV(76);
PV(77);
PV(78);
PV(79);
PV(80);
PV(81);
PV(82);
PV(83);
PV(84);
PV(85);
PV(86);
PV(87);
PV(88);
PV(89);
PV(90);
PV(91);
PV(92);
PV(93);
PV(94);
PV(95);
PV(96);
PV(97);
PV(98);
PV(99);
PV(100);
PV(101);
PV(102);
    virtual bool OnHitTest(float x, float y, float* py, void* out);   // +0x19c
};
}
}
namespace EA {
namespace UTFWinControls {
struct WinGridVt {
PV(0);
PV(1);
PV(2);
PV(3);
PV(4);
PV(5);
PV(6);
PV(7);
PV(8);
PV(9);
PV(10);
PV(11);
PV(12);
PV(13);
PV(14);
PV(15);
PV(16);
PV(17);
PV(18);
PV(19);
PV(20);
PV(21);
PV(22);
PV(23);
PV(24);
PV(25);
PV(26);
PV(27);
PV(28);
PV(29);
PV(30);
PV(31);
PV(32);
PV(33);
PV(34);
PV(35);
    virtual void OnSelChanged();          // +0x90
PV(37);
PV(38);
PV(39);
PV(40);
PV(41);
PV(42);
PV(43);
PV(44);
PV(45);
PV(46);
PV(47);
PV(48);
PV(49);
PV(50);
PV(51);
PV(52);
PV(53);
PV(54);
PV(55);
PV(56);
PV(57);
PV(58);
PV(59);
PV(60);
PV(61);
PV(62);
PV(63);
PV(64);
PV(65);
PV(66);
PV(67);
PV(68);
    virtual void OnInsert(void* iter);    // +0x114
};
}
}
namespace EA {
namespace UTFWinControls {
struct WinGrid_s0096_f3f0 {
    char sub20c[0x20c];

    void SetDefaultFormatting();                                    // 0x009702b0
    void OnMouseWheel(int, int, int, int delta);                    // 0x00970540
    virtual bool OnMouseMove(float x, float y, unsigned int param); // 0x00970460
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

// ---- items of slice s0097cea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* ea_new(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
struct WinGridBase { void RefreshImpl(); };   // 0x97bc80, thiscall
struct WinGridRefreshThunk { void Refresh(); };
namespace Gr {
#define GVT(o, i) ((*(void***)(o))[i])
}
namespace Gr {
struct CellData_s0097_cea0 {                        // 0x1c bytes, allocated "UTFWin/Grid"
    int mType;                           // +0
    int mCol, mRow;                      // +4, +8
    void* mpWindow;                      // +0xc
    int pad10, pad14;
    unsigned mFlags;                     // +0x18
};
}
namespace Gr {
struct SparseMatrix_s0097_cea0 {                    // SparseMatrix<CellData*> at IWinGrid+0x114
    int  GetMaxUsedColAndRow(int* pOut);                              // 0x973980, ret 4
    bool GetMinMaxUsedColForRow(int row, int* pMin, int* pMax);      // 0x975350, ret 0xc
    bool GetMinMaxUsedRowForCol(int col, int* pMin, int* pMax);      // 0x973800, ret 0xc
    void InsertCell(int col, int row, CellData_s0097_cea0** ppCell, int flag);  // 0x976f90, ret 0x10
};
}
namespace Gr {
struct WinGridMain {                     // the full WinGrid object (IWinGrid subobject - 0x20c)
    void SetupCell(int col, int row, int one, int flag);             // 0x97bfb0, ret 0x10
    void InitCellWindow(int col, int row, void* w, bool b1, bool b2); // 0x975ea0, ret 0x14
};
}
namespace Gr {
struct WinGridIface {                    // IWinGrid subobject
    void* vtbl;                          // +0
    char  pad4[4];
    bool  mbDirty;                       // +8
    char  pad9[0x7c - 9];
    int   mLastCol;                      // +0x7c
    int   mLastRow;                      // +0x80
    char  pad84[0x114 - 0x84];
    SparseMatrix_s0097_cea0 mCells;                 // +0x114
    bool SetCellWindow(int col, int row, void* w, bool b1, bool b2, int flag);
};
}
// ---- items of slice s0097cea0 end

// ---- items of slice s00970570 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWinControls {
struct CRect {
    int left, top, right, bottom;
    void NormalizeRect();
};
}
}
// ---- items of slice s00970570 end

// ---- items of slice s00970f30 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s0097_0f30(n) virtual void pv##n()
namespace EA {
namespace UTFWinControls {
struct RectF {
    float left, top, right, bottom;
    RectF() {}
};
}
}
namespace EA {
namespace UTFWinControls {
struct CRect_s0097_0f30 {
    int left, top, right, bottom;
};
}
}
namespace EA {
namespace UTFWinControls {
struct Batch2D;
}
}
namespace EA {
namespace UTFWinControls {
struct RenderContext_s0097_0f30;
}
}
namespace EA {
namespace UTFWinControls {
namespace Text {
struct LineLayout;
}
}
}
namespace EA {
namespace UTFWinControls {
namespace Text {
struct Typesetter;
}
}
}
namespace EA {
namespace UTFWinControls {
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
}
}
namespace EA {
namespace UTFWinControls {
struct CellFormat_s0097_0f30 {
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
}
}
namespace EA {
namespace UTFWinControls {
struct CellData_s0097_0f30 {
    int   nCellType;                     // +0x00
    int   nColumn;                       // +0x04
    int   nRow;                          // +0x08
    void* pCellData;                     // +0x0c
    CellFormat_s0097_0f30* pCellFormat;             // +0x10
    void* pExtraData;                    // +0x14
    unsigned nCellFlags;                 // +0x18
};
}
}
namespace EA {
namespace UTFWinControls {
struct OwnerDrawInfo_s0097_0f30 {
    void*         pWinGrid;              // +0x00
    unsigned      nColumn;               // +0x04
    unsigned      nRow;                  // +0x08
    RectF*        pRectCell;             // +0x0c
    RectF*        pRectCellClip;         // +0x10
    RectF*        pRectAreaToDrawTo;     // +0x14
    RenderContext_s0097_0f30* pRenderContext;       // +0x18
    CellFormat_s0097_0f30*   pCellFormat;           // +0x1c
    CellData_s0097_0f30*     pCellData;             // +0x20
    char          bCellSelected;         // +0x24
    char          bCellHighlighted;      // +0x25
    char          bGridEnabled;          // +0x26
};
}
}
namespace EA {
namespace UTFWinControls {
struct Bitmap {
    char _pad00[0x1c];
    int  mnWidth;                        // +0x1c
    int  mnHeight;                       // +0x20
};
}
}
namespace EA {
namespace UTFWinControls {
struct TextBuffer {
    const unsigned short* mpBegin;       // +0x00
    const unsigned short* mpEnd;         // +0x04
};
}
}
namespace EA {
namespace UTFWinControls {
namespace Text {
struct LineLayout {
    char _data[0x2c];
    void Clear(int bArg);
};
}
}
}
namespace EA {
namespace UTFWinControls {
namespace Text {
struct Typesetter {
    char _data[0x530];
    void* LayoutParagraph(const unsigned short* pBegin, int nCount,
                          float l, float t, float r, float b,
                          TextStyle* pStyle, LineLayout* pLineLayout, int nArg);
};
}
}
}
namespace EA {
namespace UTFWinControls {
struct Batch2D {
    PV_s0097_0f30(0);
    virtual void SetColor(unsigned color);                    // +0x04 slot 1
    PV_s0097_0f30(2);
    virtual char GetX3(void* pOut);                           // +0x0c slot 3
    virtual void X4(char c, void* p);                         // +0x10 slot 4
    virtual void X5(unsigned v);                              // +0x14 slot 5
PV_s0097_0f30(6);
PV_s0097_0f30(7);
PV_s0097_0f30(8);
PV_s0097_0f30(9);
PV_s0097_0f30(10);
PV_s0097_0f30(11);
PV_s0097_0f30(12);
PV_s0097_0f30(13);
    virtual void DrawRect(float l, float t, float r, float b); // +0x38 slot 14
PV_s0097_0f30(15);
PV_s0097_0f30(16);
PV_s0097_0f30(17);
PV_s0097_0f30(18);
PV_s0097_0f30(19);
PV_s0097_0f30(20);
PV_s0097_0f30(21);
    virtual void DrawBitmap(RectF* pDest, Bitmap* pBmp, RectF* pSrc); // +0x58 slot 22
};
}
}
namespace EA {
namespace UTFWinControls {
struct RenderContext_s0097_0f30 {
    Batch2D* Begin2D(void* pRenderMode);  // 0x0095bc10 (EA::UTFWinControls::RenderContext::Begin2D)
};
}
}
namespace EA {
namespace UTFWinControls {
struct IWindow {
PV_s0097_0f30(0);
PV_s0097_0f30(1);
PV_s0097_0f30(2);
PV_s0097_0f30(3);
PV_s0097_0f30(4);
    virtual void* pv5();                                      // +0x14 slot 5
PV_s0097_0f30(6);
PV_s0097_0f30(7);
PV_s0097_0f30(8);
PV_s0097_0f30(9);
PV_s0097_0f30(10);
PV_s0097_0f30(11);
PV_s0097_0f30(12);
PV_s0097_0f30(13);
PV_s0097_0f30(14);
PV_s0097_0f30(15);
PV_s0097_0f30(16);
PV_s0097_0f30(17);
PV_s0097_0f30(18);
PV_s0097_0f30(19);
PV_s0097_0f30(20);
PV_s0097_0f30(21);
PV_s0097_0f30(22);
PV_s0097_0f30(23);
PV_s0097_0f30(24);
PV_s0097_0f30(25);
PV_s0097_0f30(26);
PV_s0097_0f30(27);
PV_s0097_0f30(28);
PV_s0097_0f30(29);
PV_s0097_0f30(30);
    virtual void SetFlag(unsigned flag, int value);           // +0x7c slot 31
PV_s0097_0f30(32);
PV_s0097_0f30(33);
PV_s0097_0f30(34);
PV_s0097_0f30(35);
    virtual void Invalidate();                                // +0x90 slot 36
    virtual void InvalidateLayout();                          // +0x94 slot 37 (0x009719a0)
};
}
}
namespace EA {
namespace UTFWinControls {
struct Window : IWindow {
    virtual void InvalidateLayout();                           // +0x94 slot 37 (0x009719a0)
};
}
}
namespace EA {
namespace UTFWinControls {
struct Win {
PV_s0097_0f30(0);
PV_s0097_0f30(1);
PV_s0097_0f30(2);
PV_s0097_0f30(3);
PV_s0097_0f30(4);
PV_s0097_0f30(5);
PV_s0097_0f30(6);
PV_s0097_0f30(7);
PV_s0097_0f30(8);
PV_s0097_0f30(9);
    virtual void SerUpdate();                                 // 0x009614a0
    virtual bool DoMessage(int* pMsg);                        // 0x00950bb0
};
}
}
namespace EA {
namespace UTFWinControls {
struct DropShadowDescriptor {
    int mMode1;                                               // +0x00
    int mMode2;                                               // +0x04
    void SetMode1(int mode);                                  // 0x00830280
    void SetMode2(int mode);                                  // 0x00830150
    void DrawCellText(Batch2D* pBatch, void* p1, void* p2, void* p3,
                      unsigned color, unsigned short ch, char flag); // 0x0096e740
};
}
}
namespace EA {
namespace UTFWinControls {
class WinGrid_s0097_0f30;
}
}
namespace EA {
namespace UTFWinControls {
class IWinGrid_s0097_0f30 { public:
    struct SelNode {
        SelNode* mpNext;                                      // +0x00
        SelNode* mpPrev;                                      // +0x04
        int      mnColumn;                                    // +0x08
        int      mnRow;                                       // +0x0c
    };

    // --- 135-slot vtable; only the slots exercised by this slice are named ---
PV_s0097_0f30(0);
PV_s0097_0f30(1);
PV_s0097_0f30(2);
PV_s0097_0f30(3);
PV_s0097_0f30(4);
PV_s0097_0f30(5);
PV_s0097_0f30(6);
    virtual bool GetGridArea(RectF& pOut);                    // +0x01c slot 7
    virtual bool GetCellArea(RectF& pOut);                    // +0x020 slot 8
PV_s0097_0f30(9);
PV_s0097_0f30(10);
    virtual void SetGridFlag(unsigned flag, bool value);      // +0x02c slot 11
    virtual bool GetGridFlag(unsigned flag);                  // +0x030 slot 12
    virtual bool SetDefaultTextStyle(unsigned style);         // +0x034 slot 13
PV_s0097_0f30(14);
PV_s0097_0f30(15);
PV_s0097_0f30(16);
PV_s0097_0f30(17);
PV_s0097_0f30(18);
    virtual bool SetDefaultTextWrapping(bool bWrap);          // +0x04c slot 19
PV_s0097_0f30(20);
PV_s0097_0f30(21);
    virtual bool SetGutters(float a, float b, float c, float d);      // +0x058 slot 22
    PV_s0097_0f30(23);
    virtual bool SetCellGutters(float a, float b, float c, float d);  // +0x060 slot 24
PV_s0097_0f30(25);
PV_s0097_0f30(26);
PV_s0097_0f30(27);
PV_s0097_0f30(28);
PV_s0097_0f30(29);
    virtual bool ScrollCellsVertically(int nCells);           // +0x078 slot 30
    virtual bool ScrollCellsHorizontally(int nCells);         // +0x07c slot 31
PV_s0097_0f30(32);
PV_s0097_0f30(33);
    virtual void ScrollToColumn(int col);                     // +0x088 slot 34
    virtual void ScrollToRow(int row);                        // +0x08c slot 35
PV_s0097_0f30(36);
PV_s0097_0f30(37);
PV_s0097_0f30(38);
PV_s0097_0f30(39);
PV_s0097_0f30(40);
    virtual bool GetSelection(int& col, int& row);            // +0x0a4 slot 41
PV_s0097_0f30(42);
PV_s0097_0f30(43);
PV_s0097_0f30(44);
PV_s0097_0f30(45);
PV_s0097_0f30(46);
    virtual void SetCellLimits(int col, int row);             // +0x0bc slot 47
    PV_s0097_0f30(48);
    virtual bool GetCellUsedRange(CRect_s0097_0f30& out);                // +0x0c4 slot 49
PV_s0097_0f30(50);
PV_s0097_0f30(51);
PV_s0097_0f30(52);
PV_s0097_0f30(53);
PV_s0097_0f30(54);
PV_s0097_0f30(55);
PV_s0097_0f30(56);
PV_s0097_0f30(57);
PV_s0097_0f30(58);
PV_s0097_0f30(59);
PV_s0097_0f30(60);
PV_s0097_0f30(61);
PV_s0097_0f30(62);
PV_s0097_0f30(63);
PV_s0097_0f30(64);
    virtual bool GetColumnHeadingArea(int col, RectF& out);   // +0x104 slot 65
    virtual bool GetRowHeadingArea(int row, RectF& out);      // +0x108 slot 66
PV_s0097_0f30(67);
PV_s0097_0f30(68);
    virtual bool SetHeadingSizes(float colHeight, float rowWidth); // +0x114 slot 69
PV_s0097_0f30(70);
PV_s0097_0f30(71);
PV_s0097_0f30(72);
PV_s0097_0f30(73);
PV_s0097_0f30(74);
PV_s0097_0f30(75);
PV_s0097_0f30(76);
PV_s0097_0f30(77);
PV_s0097_0f30(78);
PV_s0097_0f30(79);
PV_s0097_0f30(80);
PV_s0097_0f30(81);
PV_s0097_0f30(82);
PV_s0097_0f30(83);
PV_s0097_0f30(84);
PV_s0097_0f30(85);
PV_s0097_0f30(86);
PV_s0097_0f30(87);
PV_s0097_0f30(88);
PV_s0097_0f30(89);
PV_s0097_0f30(90);
PV_s0097_0f30(91);
PV_s0097_0f30(92);
PV_s0097_0f30(93);
PV_s0097_0f30(94);
PV_s0097_0f30(95);
PV_s0097_0f30(96);
PV_s0097_0f30(97);
PV_s0097_0f30(98);
    virtual bool GetCellRect(int col, int row, RectF& out);   // +0x18c slot 99
PV_s0097_0f30(100);
PV_s0097_0f30(101);
PV_s0097_0f30(102);
    virtual bool DoCursorHitTest(float x, float y, int& result, CRect_s0097_0f30& coords); // +0x19c slot 103
PV_s0097_0f30(104);
PV_s0097_0f30(105);
PV_s0097_0f30(106);
PV_s0097_0f30(107);
PV_s0097_0f30(108);
PV_s0097_0f30(109);
PV_s0097_0f30(110);
PV_s0097_0f30(111);
PV_s0097_0f30(112);
PV_s0097_0f30(113);
PV_s0097_0f30(114);
PV_s0097_0f30(115);
PV_s0097_0f30(116);
PV_s0097_0f30(117);
PV_s0097_0f30(118);
PV_s0097_0f30(119);
PV_s0097_0f30(120);
PV_s0097_0f30(121);
PV_s0097_0f30(122);
PV_s0097_0f30(123);
PV_s0097_0f30(124);
PV_s0097_0f30(125);
PV_s0097_0f30(126);
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
}
}
namespace EA {
namespace UTFWinControls {
class WinGrid_s0097_0f30 : public Win, public Window { public:
    char _pad008[0x88 - 0x08];                        // +0x008
    RectF mArea;                                      // +0x088
    char _pad098[0x20c - 0x098];                      // +0x098
    IWinGrid_s0097_0f30 mGrid;                                   // +0x20c
    char _padGrid[0x484 - 0x20c - sizeof(IWinGrid_s0097_0f30)];  // +0x414
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
    void DrawText(TextBuffer* pText, RectF* pRect, OwnerDrawInfo_s0097_0f30* pInfo);  // 0x00971250 (EA::UTFWinControls::WinGrid::DrawText)
    void DrawCellBackground(OwnerDrawInfo_s0097_0f30* pInfo);  // 0x00971490 (EA::UTFWinControls::WinGrid::DrawCellBackground)
    void DrawCell(OwnerDrawInfo_s0097_0f30* pInfo);  // 0x00971600 (EA::UTFWinControls::WinGrid::DrawCell)
};
}
}
// ---- items of slice s00970f30 end

// ---- items of slice s00971eb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWinControls {
struct CellNode {
    CellNode* mpLeft;                                  // +0x00  (list mpNext)
    CellNode* mpRight;                                 // +0x04  (list mpPrev)
    int       mUnknown08;                              // +0x08
    char      mbColor;                                 // +0x0c
    char      _pad0d[0x1c - 0x0d];                     // +0x0d
    unsigned  mKey;                                    // +0x1c
};
}
}
namespace EA {
namespace UTFWinControls {
struct CellList {
    CellNode* mpHead;                                  // +0x00
    CellNode* mpTail;                                  // +0x04
    int       mnSize;                                  // +0x08
    void clear();
};
}
}
namespace EA {
namespace UTFWinControls {
struct CellData_s0097_1eb0;
}
}
namespace EA {
namespace UTFWinControls {
struct CellRbtree {
    int       _pad00;                                  // +0x00
    CellNode* mHeaderLeft;                             // +0x04
    CellNode* mHeaderRight;                            // +0x08
    CellNode* mpRoot;                                  // +0x0c
    CellNode* AllocateNode(const CellData_s0097_1eb0* pData, void* pArg);
    void find(CellNode** pOut, const CellData_s0097_1eb0* pKey);
};
}
}
namespace EA {
namespace UTFWinControls {
void* EAAllocate(unsigned size, const char* pTag, int a, int b, const char* pFile, int line);
}
}
namespace EA {
namespace UTFWinControls {
void operator delete(void* p);
}
}
// ---- items of slice s00971eb0 end

// ---- items of slice s00973dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_serTypeTable[];                                             // 0x154eea0
void    __cdecl RBTreeInsert(RBNode*, RBNode*, RBNode*, int);              // 0x9216a0
RBNode* __cdecl RBTreeDecrement(const RBNode*);                            // 0x9215c0
void*   __cdecl EAlloc(unsigned, const char*, int, int, const char*, int);// 0xf473a0
void    __cdecl EFree(void*);                                              // 0xf47380
RBNode* __stdcall CreateNodeCopy(const RBNode*, RBNode*);                  // 0x972e30
RBNode* __stdcall CreateNodeCopy40(const RBNode*, RBNode*);                // 0x972dd0
struct ComparatorStr { int fn(const wchar_t* s); };   // 0x614950, ecx = CellData.pCellData
#define EA_ALLOC(sz) EAlloc(sz, "EASTL", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
struct V28 { int f[7]; };
struct V40 { int f[16]; };
struct V0c { int f[3]; };
struct RBTree_s0097_3dd0 {
    int allocator;
    RBNode anchor;
    int size;
    void    Find(RBNode** out, const void* key);
    void DoInsertValueImpl_1c(RBNode** out, RBNode* parent, const V28* value, char force);
    void DoInsertValueImpl_40(RBNode** out, RBNode* parent, const V40* value, char force);
    void DoInsertValueImpl_0c(RBNode** out, RBNode* parent, const V0c* value, char force);
    RBNode* DoCopySubtree_40(const RBNode* src, RBNode* parent);
    RBNode* DoCopySubtree_0c(const RBNode* src, RBNode* parent);
};
struct SparseMatrix_s0097_3dd0 {
    RBTree_s0097_3dd0 t;
    int  GetMinUsedColAndRow(int* pRow);  // 0x00973930 (SparseMatrix::GetMinUsedColAndRow)
    int  GetMaxUsedColAndRow(int* pRow);  // 0x00973980 (SparseMatrix::GetMaxUsedColAndRow)
    bool GetCellPtr(int col, int row, void*** out);  // 0x00973a90 (SparseMatrix::GetCellPtr)
};
struct CellFormat_s0097_3dd0 {
    unsigned int nTextStyle;      // 0x00
    unsigned int nColor[8];       // 0x04..0x24
    char nWrapping;               // 0x24
    char nHAlignment;             // 0x25
    char nVAlignment;             // 0x26
    char field27;                 // 0x27
    unsigned int nBorder;         // 0x28
    unsigned int nBorderColor;    // 0x2c
};                                // 0x30
struct CellFormatExtra_s0097_3dd0 : CellFormat_s0097_3dd0 {
    float nSizeDefault;           // 0x30
    float nSizeCachedActual;      // 0x34
};
struct CellData_s0097_3dd0 {
    int   nCellType;              // 0x00
    int   nColumn;                // 0x04
    int   nRow;                   // 0x08
    void* pCellData;              // 0x0c
    CellFormat_s0097_3dd0* pCellFormat;      // 0x10
    void* pExtraData;             // 0x14
    unsigned int nCellFlags;      // 0x18
};
struct CellCoordinates { int nColumn; int nRow; };
struct Rect_s0097_3dd0 { int left, top, right, bottom; };
struct VGrid {                        // ecx = IWinGrid (= WinGrid+0x20c)
virtual void p00();
virtual void p01();
virtual void p02();
virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
virtual void p08();
virtual void p09();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
    virtual void s0x88(int);
    virtual void s0x8c(int);
    virtual void s0x90(int, int);
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
virtual void p44();
virtual void p45();
virtual void p46();
virtual void p47();
virtual void p48();
    virtual void s0xc4(int*);
};
struct VWin {                         // ecx = WinGrid+4 (CustomWindow)
virtual void p00();
virtual void p01();
virtual void p02();
virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
virtual void p08();
virtual void p09();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
virtual void p34();
virtual void p35();
    virtual void s0x90();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
virtual void p44();
virtual void p45();
virtual void p46();
virtual void p47();
virtual void p48();
virtual void p49();
virtual void p50();
virtual void p51();
virtual void p52();
virtual void p53();
virtual void p54();
virtual void p55();
    virtual void s0xe0(void*);
};
struct VGridCf {                      // ecx = IWinGrid
virtual void p00();
virtual void p01();
virtual void p02();
virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
virtual void p08();
virtual void p09();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
virtual void p44();
virtual void p45();
virtual void p46();
virtual void p47();
virtual void p48();
virtual void p49();
virtual void p50();
virtual void p51();
virtual void p52();
virtual void p53();
virtual void p54();
virtual void p55();
virtual void p56();
virtual void p57();
virtual void p58();
virtual void p59();
virtual void p60();
virtual void p61();
virtual void p62();
virtual void p63();
virtual void p64();
virtual void p65();
virtual void p66();
virtual void p67();
virtual void p68();
virtual void p69();
virtual void p70();
virtual void p71();
virtual void p72();
virtual void p73();
virtual void p74();
virtual void p75();
virtual void p76();
virtual void p77();
virtual void p78();
virtual void p79();
    virtual bool s0x140(int, CellFormatExtra_s0097_3dd0**);
    virtual bool s0x144(int, CellFormatExtra_s0097_3dd0**);
};
struct VImg {                         // ecx = arbitrary object
    virtual void s0();
};
struct Alloc {                        // eastl allocator interface
    virtual void* allocate(unsigned size, int align);
};
struct HatIter { void* node; };
struct HatTable { HatIter* find(HatIter* out, const unsigned& key); };   // 0xa3b2c0
struct WinGrid_s0097_3dd0 {
    bool OnKeyDown(int, unsigned, unsigned);
    void DoArrowKey(unsigned, unsigned);  // 0x00972e90 (WinGrid::DoArrowKey)
    void DoWindowRemoval(int nRow, int nCol, void* pWindow);  // 0x00974a60 (WinGrid::DoWindowRemoval)
    void PlaceAllCellWindows();  // 0x00974b00 (WinGrid::PlaceAllCellWindows)
    void PlaceCellWindow(int, int, void*, bool, bool);   // 0x9720a0
    void kF30();                                         // 0x970f30
    void kF60();                                         // 0x970f60
    void kF80();                                         // 0x970f80
    void kFb0();                                         // 0x970fb0
};
struct IWinGrid {
    int  GetSelectionCount();
    bool GetSelection(CellCoordinates* out, int* count);
    bool SetSelection(int col, int row);
    bool GetCellUsedRange(Rect_s0097_3dd0* rect);
    bool GetCellType(int col, int row, int* out);
    bool GetCellFormat(int col, int row, CellFormat_s0097_3dd0* out);
    bool GetColCellFormatExtra(int col, CellFormatExtra_s0097_3dd0** out);
    bool GetRowCellFormatExtra(int row, CellFormatExtra_s0097_3dd0** out);
    bool GetCellTextValue(int col, int row, void** out);
    bool GetCellImage(int col, int row, void** out);
    bool GetCellWindow(int col, int row, void** out);
    int  GetCellExtraData(int col, int row);
};
static __forceinline void MergeFormat(CellFormat_s0097_3dd0* d, const CellFormat_s0097_3dd0* s)
{
    if (s->nColor[0]) d->nColor[0] = s->nColor[0];
    if (s->nColor[1]) d->nColor[1] = s->nColor[1];
    if (s->nColor[4]) d->nColor[4] = s->nColor[4];
    if (s->nColor[5]) d->nColor[5] = s->nColor[5];
    if (s->nColor[6]) d->nColor[6] = s->nColor[6];
    if (s->nColor[7]) d->nColor[7] = s->nColor[7];
    if (s->nColor[2]) d->nColor[2] = s->nColor[2];
    if (s->nColor[3]) d->nColor[3] = s->nColor[3];
    if (s->nWrapping != -1) d->nWrapping = s->nWrapping;
    if (s->nHAlignment) d->nHAlignment = s->nHAlignment;
    if (s->nVAlignment) d->nVAlignment = s->nVAlignment;
    if (s->nBorder) d->nBorder = s->nBorder;
    if (s->nBorderColor) d->nBorderColor = s->nBorderColor;
    if (s->nTextStyle) d->nTextStyle = s->nTextStyle;
}
static inline RBNode* FindInt(RBTree_s0097_3dd0* t, int key)
{
    RBNode* end = &t->anchor;
    RBNode* result = end;
    for (RBNode* p = t->anchor.parent; p; ) {
        if (FLD(int, p, 0x10) < key) p = p->right;
        else { result = p; p = p->left; }
    }
    if (result == end || key < FLD(int, result, 0x10)) result = end;
    return result;
}
// ---- items of slice s00973dd0 end

// ---- items of slice s00974c60 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWinControls {
struct CellData_s0097_4c60 {
    int   mType;                                       // +0x00
    int   mnColumn;                                    // +0x04
    int   mnRow;                                       // +0x08
    void* mpText;                                      // +0x0c
    int   _pad10;                                      // +0x10
    int   mUnknown14;                                  // +0x14
    int   mUnknown18;                                  // +0x18
};
}
}
namespace EA {
namespace UTFWinControls {
struct SparseMatrixIter {
    void* mpNode;                                      // +0x00
    void* mpOwner;                                     // +0x04

    SparseMatrixIter& operator++();
};
}
}
namespace EA {
namespace UTFWinControls {
struct SparseMatrix_s0097_4c60 {
    void** FirstUsed(SparseMatrixIter* pOut);          // 0x973cc0
    bool GetCellPtr(int col, int row, void*** ppOut);  // 0x973a90
    bool GetMinMaxUsedColForRow(int row, int* pMin, int* pMax);
};
}
}
namespace EA {
namespace UTFWinControls {
struct CellRecord {
    int          mType;                                // +0x00
    int          mnColumn;                             // +0x04
    int          mnRow;                                // +0x08
    void*        mpText;                               // +0x0c
    int          _pad10;                               // +0x10
    int          mUnknown14;                           // +0x14
    int          mUnknown18;                           // +0x18
};
}
}
namespace EA {
namespace UTFWinControls {
struct CellListNode {
    CellListNode* mpPrev;                              // +0x00
    CellListNode* mpNext;                              // +0x04
    int           mValueA;                             // +0x08
    int           mValueB;                             // +0x0c
};
}
}
namespace EA {
namespace UTFWinControls {
struct CellList_s0097_4c60 {
    CellListNode* mpHead;                              // +0x00
    CellListNode* mpTail;                              // +0x04

    void push_back(const int* pValue);
};
}
}
namespace EA {
namespace UTFWinControls {
struct CellRbtNode {
    CellRbtNode* mpLeft;                               // +0x00
    CellRbtNode* mpRight;                              // +0x04
    CellRbtNode* mpParent;                             // +0x08
    char         mbColor;                              // +0x0c
    char         _pad0d[0x1c - 0x0d];                  // +0x0d
    unsigned     mKey;                                 // +0x1c
};
}
}
namespace EA {
namespace UTFWinControls {
struct CellRbtree_s0097_4c60 {
    int          _pad00;                               // +0x00
    CellRbtNode* mHeaderLeft;                          // +0x04
    CellRbtNode* mHeaderRight;                         // +0x08
    CellRbtNode* mpRoot;                               // +0x0c

    void* DoInsertValue(const CellData_s0097_4c60* pValue, void* pOut);
    void  DoInsertValueImpl(const CellData_s0097_4c60** ppValue, CellRbtNode* pPos,
                            const CellData_s0097_4c60* pValue2, char b);
};
}
}
struct EColIterB {
    int   mRow;                                        // +0x00
    char  _pad04[4];                                   // +0x04
    void* mpListHead;                                  // +0x08
    void* mpListTail;                                  // +0x0c
    void* mpListSentinel2;                             // +0x10
    char  mbFlag;                                      // +0x14
    char  _pad15[3];                                   // +0x15
    int   mUnknown18;                                  // +0x18

    void Init(int row);
};
EA::UTFWinControls::CellRbtNode* RBTreeDecrement(const EA::UTFWinControls::CellRbtNode* pNode);
// ---- items of slice s00974c60 end

// ---- items of slice s00975ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_emptyString16;      // 0x01667bac
extern void* g_emptyString16_end;  // 0x01667bae
namespace EA {
namespace UTFWinControls {
extern "C" size_t wcslen(const wchar_t*);
}
}
namespace EA {
namespace UTFWinControls {
struct RBN {                     // eastl node base: right, left, parent, colour
    RBN* right;                  // +0x00
    RBN* left;                   // +0x04
    RBN* parent;                 // +0x08
    int  color;                  // +0x0c
};
}
}
namespace EA {
namespace UTFWinControls {
struct CellData_s0097_5ea0 {                // 0x1c bytes, "UTFWin/Grid"
    int      mType;              // +0x00
    int      mCol;               // +0x04
    int      mRow;               // +0x08
    void*    mpWindow;           // +0x0c
    int      pad10;              // +0x10
    int      pad14;              // +0x14
    unsigned mFlags;             // +0x18
};
}
}
namespace EA {
namespace UTFWinControls {
struct MatrixRow {
    char   alloc[4];             // +0x00
    RBN    anchor;               // +0x04
    int    mnSize;               // +0x14
    void CtorFrom(const int* src);                           // 0x009755a0, ret 4
    void f(void* value);                                     // 0x009a9600, ret 4
};
}
}
namespace EA {
namespace UTFWinControls {
struct TreeHdr {
    char      alloc[4];          // +0x00
    RBN       anchor;            // +0x04 (right/left/parent/colour)
    int       mnSize;            // +0x14
    void Find(RBN** out, const int* key);                    // 0xe39fb0, ret 8
};
}
}
extern "C" void* __cdecl EAAllocate(unsigned size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EaFree(void* p);                                   // 0x00f47380 (operator delete)
namespace EA {
namespace UTFWinControls {
void RBTreeInsert(RBN* node, RBN* hint, RBN* anchor, bool bSide);           // 0x009216a0
}
}
namespace EA {
namespace UTFWinControls {
RBN* RBTreeIncrement(RBN* node);                                            // 0x00921580
}
}
namespace EA {
namespace UTFWinControls {
void RBTreeErase(RBN* node, RBN* anchor);                                   // 0x00921880
}
}
struct WStringObj {              // eastl::basic_string<wchar_t> object, 0x10 bytes
    void* mpBegin;               // +0x00
    void* mpEnd;                 // +0x04
    void* mpCap;                 // +0x08
    void  Ctor(const wchar_t* src);                          // 0x0056e2d0
    void  assign(const wchar_t* begin, const wchar_t* end);  // 0x00423650
};
struct ExtraMap {
    char   mData[0x20];
    void** op_brackets(const unsigned* key);                 // 0x00975d40, ret 4
};
struct HeadingMap_s0097_5ea0 {
    char   mData[0x20];
    void** op_brackets(const unsigned* key);                 // 0x0068d340, ret 4
    void   ClearNodes(void* buckets, unsigned count);        // 0x0068d420, ret 8
};
struct CellFormat_s0097_5ea0 {              // 0x30-byte cell format block ("UTFWin/Grid")
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
    CellFormat_s0097_5ea0();
};
struct RowNode {                 // 0x30-byte outer node: {RBN, int key@0x10, pad, MatrixRow@0x18}
    EA::UTFWinControls::RBN       base;              // +0x00
    int       key;               // +0x10
    int       pad14;             // +0x14
    EA::UTFWinControls::MatrixRow row;               // +0x18
};
struct ColNode {                 // 0x1c-byte inner node: {RBN, int key@0x10, pad, CellData* value@0x18}
    EA::UTFWinControls::RBN       base;              // +0x00
    int       key;               // +0x10
    int       pad14;             // +0x14
    EA::UTFWinControls::CellData_s0097_5ea0* value;             // +0x18
};
struct CellsMatrix {             // SparseMatrix<CellData*>: at WinGrid+0x320 / IWinGrid+0x114
    char   alloc[4];             // +0x00
    EA::UTFWinControls::RBN    anchor;               // +0x04
    int    mnSize;               // +0x14
    int    pad18;                // +0x18
    int    mnTotalCells;         // +0x1c
    int    mnMinCol;             // +0x20
    int    mnMaxCol;             // +0x24
    int    mnMinRow;             // +0x28
    int    mnMaxRow;             // +0x2c

    void Find(EA::UTFWinControls::RBN** out, const int* key);                    // 0x00e39fb0, ret 8
    void DoNukeSubtree(EA::UTFWinControls::RBN* node);                           // 0x00976450, ret 4
    bool RemoveCell(int col, int row, EA::UTFWinControls::CellData_s0097_5ea0** out);       // 0x009768e0, ret 0xc
    bool RemoveRow(int start, int count);                    // 0x00976980, ret 8
    bool RemoveCol(int start, int count);                    // 0x00976a40, ret 8
    void EraseRow(EA::UTFWinControls::RBN** out, EA::UTFWinControls::RBN* node);                     // 0x00976770, ret 8
    bool GetCellPtr(int col, int row, EA::UTFWinControls::CellData_s0097_5ea0** out);      // 0x00973a90, ret 0xc
    int  GetCellsInRange(int c0, int r0, int c1, int r1, EA::UTFWinControls::CellData_s0097_5ea0** out); // 0x00973b90, ret 0x14
};
struct KeyNode_s0097_5ea0 {
    EA::UTFWinControls::RBN base;                    // +0x00
    int key;                     // +0x10
};
struct SortPack {
    int a;
    int b;
    int c;
};
void MergeSortWork(SortPack ctx, int* first, int* last, int* buf);            // 0x00976160
void MergeSortShell(int* first, int* last, int* cur0, int* cur1, int* cur2);// 0x00976310
void MergeRuns(int* first, int* mid, int* mid2, int* last, int* buf, SortPack ctx); // 0x00975e00
struct MatrixRowC {              // MatrixRow<CellFormatExtra>, 0x1c bytes
    char   alloc[4];
    EA::UTFWinControls::RBN    anchor;
    int    mnSize;
    int    pad18;
    void CtorFrom(const int* src);                           // 0x00975610, ret 4
    void f(void* value);                                     // 0x009a9600, ret 4
};
struct PairRowCD {               // pair<int, MatrixRow<CellData*>> payload
    int       key;               // +0x00
    int       pad;               // +0x04
    EA::UTFWinControls::MatrixRow row;               // +0x08
    PairRowCD(const int* pk, const int* src);                // 0x00976390
};
struct PairRowCF {               // pair<int, MatrixRow<CellFormatExtra>> payload
    int  key;                    // +0x00
    int  pad;                    // +0x04
    MatrixRowC row;              // +0x08
    PairRowCF(const int* pk, const int* src);                // 0x009763c0
};
struct RowTreeCD {
    char  alloc[4];              // +0x00
    EA::UTFWinControls::RBN   anchor;                // +0x04
    int   mnSize;                // +0x14
    void InsertValue(PairRowCD** out, EA::UTFWinControls::RBN* hint, const PairRowCD* value, bool bHint);  // 0x009764c0, ret 0x10
};
struct RowTreeCF {
    char  alloc[4];
    EA::UTFWinControls::RBN   anchor;
    int   mnSize;
    void InsertValue(PairRowCF** out, EA::UTFWinControls::RBN* hint, const PairRowCF* value, bool bHint);  // 0x00976550, ret 0x10
};
struct CellSet {
    char  alloc[4];              // +0x00
    EA::UTFWinControls::RBN   anchor;                // +0x04
    int   mnSize;                // +0x14
    void  DoInsertValue(void** out, const EA::UTFWinControls::CellData_s0097_5ea0* value, bool bTag);  // 0x009753f0, ret 0xc
};
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
    HeadingMap_s0097_5ea0 mColumnHeadings;  // +0x208
    HeadingMap_s0097_5ea0 mRowHeadings;     // +0x228

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
virtual void pv0();
virtual void pv1();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
virtual void pv6();
virtual void pv7();
virtual void pv8();
virtual void pv9();
virtual void pv10();
virtual void pv11();
virtual void pv12();
virtual void pv13();
virtual void pv14();
virtual void pv15();
virtual void pv16();
virtual void pv17();
virtual void pv18();
virtual void pv19();
virtual void pv20();
virtual void pv21();
virtual void pv22();
virtual void pv23();
virtual void pv24();
virtual void pv25();
virtual void pv26();
virtual void pv27();
virtual void pv28();
virtual void pv29();
virtual void pv30();
    virtual void SetFlag(unsigned flag, int value);           // +0x7c slot 31
virtual void pv32();
virtual void pv33();
virtual void pv34();
virtual void pv35();
    virtual void Invalidate();                                // +0x90 slot 36
virtual void pv37();
virtual void pv38();
virtual void pv39();
virtual void pv40();
virtual void pv41();
virtual void pv42();
virtual void pv43();
virtual void pv44();
virtual void pv45();
virtual void pv46();
virtual void pv47();
virtual void pv48();
virtual void pv49();
virtual void pv50();
virtual void pv51();
virtual void pv52();
    virtual void pv53();
    virtual bool AcceptsWindow(void* pWindow);                // +0xd8 slot 54
};
struct CellSet;
#define IVT(p, i) ((*(void***)(p))[i])
#define IVC1(R, p, i, a) (((R(__thiscall*)(void*, unsigned))IVT(p, i))(p, a))
#define IVC3(R, p, i, a, b, c) (((R(__thiscall*)(void*, unsigned, unsigned, unsigned))IVT(p, i))(p, a, b, c))
struct WinGrid_s0097_5ea0;
inline WinGrid_s0097_5ea0* GridOf(void* p) { return (WinGrid_s0097_5ea0*)((char*)p - 0x20c); }
struct WinGrid_s0097_5ea0 {
    char     pad0[0x004];
    IWindowSub mWindow;          // +0x004
    char     pad8[0x20c - 0x004 - sizeof(IWindowSub)];
    IWinGridIface mIface;        // +0x20c
    char     padRest[0x004];

    void PlaceCellWindow(int col, int row, void* pWindow, int a4, int a5);       // 0x009720a0, ret 0x14
    void DisposeOfCellData(int col, int row, EA::UTFWinControls::CellData_s0097_5ea0* p, bool bParam);          // 0x00975c50, ret 0x10
    void DoWindowAddition(int col, int row, void* pWindow, int a4, int a5);      // 0x00975ea0, ret 0x14
    bool CopyCellData(int c1, int r1, EA::UTFWinControls::CellData_s0097_5ea0* src, int c2, int r2, EA::UTFWinControls::CellData_s0097_5ea0* dst); // 0x00976010, ret 0x18
    void DisposeOfAllCellData();                                                 // 0x00976d20
};
struct FmtExtra {                // 0x38-byte CellFormatExtra value
    int f[0xe];
};
struct FmtTree {                 // SparseMatrix<CellFormatExtra> view
    char   alloc[4];             // +0x00
    EA::UTFWinControls::RBN    anchor;               // +0x04
    int    mnSize;               // +0x14
    int    pad18;                // +0x18
    int    mnTotalCells;         // +0x1c
    int    mnMinCol;             // +0x20
    int    mnMaxCol;             // +0x24
    int    mnMinRow;             // +0x28
    int    mnMaxRow;             // +0x2c

    void Find(EA::UTFWinControls::RBN** out, const int* key);                    // 0x00e39fb0
    void InsertCellInner(EA::UTFWinControls::RBN** out, const int* key, const void* value);  // 0x00975da0
    void InsertRow(EA::UTFWinControls::RBN** out, EA::UTFWinControls::RBN* hint, const void* value); // 0x00976b60
};
// ---- items of slice s00975ea0 end

// ---- items of slice s00976f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
typedef unsigned int uint;
struct RBN_s0097_6f90 {                     // eastl node base: right, left, parent, colour
    RBN_s0097_6f90* right;                  // +0x00
    RBN_s0097_6f90* left;                   // +0x04
    RBN_s0097_6f90* parent;                 // +0x08
    int  color;                  // +0x0c
};
struct RowNode_s0097_6f90 {
    RBN_s0097_6f90  base;                   // +0x00
    int  key;                    // +0x10
    int  pad14;                  // +0x14
    byte row[0x18];              // +0x18 -> MatrixRow (CD) or MatrixRowC (CF)
};
struct ColNode_s0097_6f90 {
    RBN_s0097_6f90   base;
    int   key;
    int   pad14;
    void* value;                 // +0x18
};
struct TreeHdr_s0097_6f90 {
    char alloc[4];               // +0x00
    RBN_s0097_6f90  anchor;                 // +0x04
    int  mnSize;                 // +0x14
    void Find(RBN_s0097_6f90** out, const int* key);                    // 0x00e39fb0
};
struct CellsMatrix_s0097_6f90 {
    char alloc[4];               // +0x00
    RBN_s0097_6f90  anchor;                 // +0x04
    int  mnSize;                 // +0x14
    int  pad18;                  // +0x18
    int  mnTotalCells;           // +0x1c
    int  mnMinCol;               // +0x20
    int  mnMaxCol;               // +0x24
    int  mnMinRow;               // +0x28
    int  mnMaxRow;               // +0x2c
    bool InsertCell(int col, int row, void* value, void** out); // 0x00976f90
};
struct FmtTree_s0097_6f90 {
    char alloc[4];               // +0x00
    RBN_s0097_6f90  anchor;                 // +0x04
    int  mnSize;                 // +0x14
    int  pad18;                  // +0x18
    int  mnTotalCells;           // +0x1c
    int  mnMinCol;               // +0x20
    int  mnMaxCol;               // +0x24
    int  mnMinRow;               // +0x28
    int  mnMaxRow;               // +0x2c
    void Find(RBN_s0097_6f90** out, const int* key);                    // 0x00e39fb0
};
void  RowTreeInsertCD(RBN_s0097_6f90** out, const int* key, const void* value); // 0x00976b90
bool  InsertCellFmt(FmtTree_s0097_6f90* self, int col, int row, const FmtExtra* value, FmtExtra* out); // 0x00976dd0
void  FmtInsertLeaf(FmtTree_s0097_6f90* self, RBN_s0097_6f90** out, const int* key, const void* value); // 0x00975dd0
bool  WindowShutdown(void* self);                                    // 0x00961e80
void  RecalcAll(void* self);                                         // 0x00962740
struct WinGrid_s0097_6f90 {
    char     pad0[0x004];
    char     pad4[0x0b4 - 0x004];
    FmtTree_s0097_6f90  mFmtRow;            // +0x0b4   (default row formatting matrix)
    char     padToIface[0x20c - 0x0b4 - sizeof(FmtTree_s0097_6f90)];
    char     iface[0x320 - 0x20c];  // IWinGrid sub-object (vptr at +0x20c)
    CellsMatrix_s0097_6f90 mCells;          // +0x320
    char     padAfterCells[0x3f8 - 0x320 - sizeof(CellsMatrix_s0097_6f90)];
    void*    mSound[4];          // +0x3f8 .. +0x404
    char     padTail[0x9d0 - 0x408];

    // methods
    WinGrid_s0097_6f90* Ctor(void* a2, void* a3);                  // 0x009770e0
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
// ---- items of slice s00976f90 end

// ---- items of slice s00979bc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint32;
struct RBTree_s0097_9bc0 {                 // eastl rbtree header (0x1c bytes): allocator, then the anchor
    int     mAllocator;
    RBNode  anchor;             // right = rightmost, left = leftmost(begin), parent = root
    int     mnSize;
    void Find(void** out, const void* key);   // 0xe39fb0 (eastl::rbtree::find)
};
struct CellFormatExtra_s0097_9bc0 {        // 0x38 bytes stored inline after the InNode value slot
    uint32  nTextStyle;         // +0x00
    uint32  nColor[8];          // +0x04
    uint8_t nWrapping, nHAlignment, nVAlignment, pad;  // +0x24
    uint32  nBorder;            // +0x28
    uint32  nBorderColor;       // +0x2c
    float   nSizeDefault;       // +0x30
    float   nSizeCachedActual;  // +0x34
};
struct CellData_s0097_9bc0 {               // 0x1c bytes, allocated "UTFWin/Grid"
    int      mType;             // +0x00
    int      mCol;              // +0x04
    int      mRow;              // +0x08
    void*    mpWindow;          // +0x0c
    int      pad10;             // +0x10
    int      pad14;             // +0x14
    unsigned mFlags;            // +0x18
};
struct SparseMatrix_s0097_9bc0 {           // header is 0x30 bytes
    RBTree_s0097_9bc0 t;
    char   pad18[0x30 - 0x18];

    int  GetCountForKey(int key);                                   // 0x9739e0, ret 4
    bool GetCellPtr(int col, int row, void*** out);                 // 0x973a90, ret 0xc
    int  GetCellsInRange(int a, int b, int c, int d, int* out);      // 0x973b90, ret 0x14
    void InsertCell(int col, int row, void** v, int flag);           // 0x976f90, ret 0x10
    bool RemoveCell(int col, int row, void** out);                   // 0x9768e0, ret 0xc
};
void  __cdecl EAOperatorDelete(void* p);                                      // 0xf47380
void* operator new[](size_t size, const char* name, int, int, int, int);
#define NEW_GA(n) new ("UTFWin/Grid", 0, 0, 0, 0) char[(n)]
struct WinGrid_s0097_9bc0 {
    char   pad0[0x250];
    float  mfVisibleColumnWidth;    // +0x250
    char   pad254[0x264 - 0x254];
    int    mnColumnCount;           // +0x264
    int    mnRowCount;              // +0x268
    float  mnColumnGridThickness;   // +0x26c
    float  mnRowGridThickness;      // +0x270
    char   pad274[0x2c0 - 0x274];
    SparseMatrix_s0097_9bc0 mColFormats;       // +0x2c0  SparseMatrix<CellFormatExtra>
    SparseMatrix_s0097_9bc0 mRowFormats;       // +0x2f0  SparseMatrix<CellFormatExtra>
    SparseMatrix_s0097_9bc0 mCells;            // +0x320  SparseMatrix<CellData*>

    float CalculateCellWidth(int col, int row, void* cell);         // 0x975180, ret 0xc
    float CalculateCellHeight(int col, int row, void* cell);        // 0x974fc0, ret 0xc
    void  DisposeOfCellData(int col, int row, CellData_s0097_9bc0* cell, bool deep);  // 0x975c50, ret 0x10
    void  DoCellWindowMove(int* msg);                               // 0x973330
    void  CopyCellData(int c1, int r1, CellData_s0097_9bc0* src, int c2, int r2, CellData_s0097_9bc0* dst); // 0x976010
    void  SetSizeCachedActualForColumn(int start, int count, float v);  // 0x978b50, ret 0xc
    void  SetSizeCachedActualForRow(int start, int count, float v);     // 0x9789a0, ret 0xc

    bool  CopyCellData(int srcCol, int srcRow, int dstCol, int dstRow, bool deep);  // 00979bc0
    float GetColumnWidthInternal(int col);                                          // 00979db0 0x00979db0
    float GetRowHeightInternal(int row);                                            // 00979f10 0x00979f10
};
float g_negOne = -1.0f;   // the +0x13eb1bc / +0x1442bc4 style constant pool entries
struct IWinGridSlots {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
virtual void v48();
virtual void v49();
virtual void v50();
virtual void v51();
virtual void v52();
virtual bool IsCellUsed(int col, int row);
virtual void v54();
virtual void v55();
virtual void v56();
virtual void v57();
virtual void v58();
virtual void v59();
virtual void v60();
virtual void v61();
virtual void v62();
virtual void v63();
virtual void v64();
virtual void v65();
virtual void v66();
virtual void v67();
virtual void v68();
virtual void v69();
virtual void v70();
virtual void v71();
virtual void v72();
virtual void v73();
virtual void v74();
virtual void v75();
virtual void v76();
virtual void v77();
virtual void v78();
virtual void v79();
virtual void v80();
virtual void v81();
virtual void v82();
virtual void v83();
virtual void v84();
virtual void v85();
virtual void v86();
virtual void v87();
virtual void v88();
    virtual void EraseCell(int col, int row);   // +0x164 slot 89
};
#define IFACE(g) ((IWinGridSlots*)((char*)(g) + 0x20c))
// ---- items of slice s00979bc0 end

// ---- items of slice s0097b110 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Gr {
template <class T> struct RectT { T left, top, right, bottom; };
}
namespace Gr {
struct CellData_s0097_b110 {                 // 0x1c bytes, "UTFWin/Grid"
    int      mType;               // +0x00
    int      mCol;                // +0x04
    int      mRow;                // +0x08
    void*    mpWindow;            // +0x0c
    int      pad10;               // +0x10
    int      pad14;               // +0x14
    unsigned mFlags;              // +0x18
};
}
namespace Gr {
struct CellFormatExtra_s0097_b110 {          // width is stored at +0x34
    char  pad[0x34];
    float mfWidth;                // +0x34
};
}
namespace Gr {
struct FmtNode {                  // inner node: key@0x10, CellFormatExtra* value@0x18
    FmtNode* left;                // +0x00
    FmtNode* right;               // +0x04
    char     pad8[8];             // +0x08..0x0f
    int      key;                 // +0x10
    char     pad14[4];            // +0x14..0x17
    void*    value;               // +0x18  (inner node) / inner anchor (outer node)
};
}
namespace Gr {
struct InnerTree {                // SparseMatrixCol<CellFormatExtra> header
    char     pad0[0x0c];
    FmtNode* mRoot;               // +0x0c
};
}
namespace Gr {
struct FmtOuterNode {             // outer key@0x10, inner tree header at +0x18
    FmtOuterNode* left;           // +0x00
    FmtOuterNode* right;          // +0x04
    char     pad8[8];             // +0x08..0x0f
    int      key;                 // +0x10
    char     pad14[4];            // +0x14..0x17
    InnerTree inner;              // +0x18 (anchor@0x1c, root@0x24)
};
}
namespace Gr {
struct FmtMatrix {                // SparseMatrix<CellFormatExtra>, at IWinGrid + 0xb4
    char          pad0[0x0c];
    FmtOuterNode* mRoot;          // +0x0c
    int InsertCell(int col, int row, void* fmt, int flag);   // 0x976dd0, ret 0x10
};
}
namespace Gr {
struct ColIter_s0097_b110 {
    void* mpBucket;               // +0x00
    void* mpNode;                 // +0x04
    ColIter_s0097_b110& operator++();        // 0x973640
};
}
namespace Gr {
struct SparseMatrixCells_s0097_b110 {        // SparseMatrix<CellData*>, at IWinGrid + 0x114
    char pad0[0x0c];
    bool  GetMinMaxUsedRowForCol(int col, int* pMin, int* pMax);   // 0x973800, ret 0xc
    bool  GetMinMaxUsedColForRow(int row, int* pMin, int* pMax);   // inlined twin (row-wise)
    void* GetRowCountForCol(ColIter_s0097_b110* out, int col);                // 0x973c30, ret 8
};
}
namespace Gr {
struct WString_s0097_b110 {
    wchar_t* mpData;              // +0x00
    unsigned mnSize;              // +0x04
    void assign(const wchar_t* p, unsigned n);   // 0x423650
};
}
namespace Gr {
struct HNodeP { unsigned key; void* value; HNodeP* next; };     // 0x0c bytes
}
namespace Gr {
struct HashHeader {
    unsigned  pad0;               // +0x00
    void**    mpBuckets;          // +0x04
    unsigned  mnBucketCount;      // +0x08
    char      padc[0x0c];
};
}
namespace Gr {
struct HeadingMap_s0097_b110 : HashHeader {                 // hash_map<unsigned, WString>
    WString_s0097_b110* Index(const unsigned* key);         // 0x68d340
    void     EraseKey(const unsigned* key);      // 0x6b5110
};
}
namespace Gr {
struct ExtraMap_s0097_b110 : HashHeader {                   // hash_map<unsigned, void*>
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
}
namespace Gr {
struct WinGrid_s0097_b110 {
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
}
namespace Gr {
extern unsigned g_recalcDepth;    // 0x166b20c
}
namespace Gr {
struct WinGridIface_s0097_b110 {
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
    SparseMatrixCells_s0097_b110 mCells;     // +0x114
    char     padCells[0x1a8 - 0x114 - sizeof(SparseMatrixCells_s0097_b110)];
    ExtraMap_s0097_b110 mRowExtraData;       // +0x1a8
    ExtraMap_s0097_b110 mColumnExtraData;    // +0x1c8
    char     pad1e8[0x208 - 0x1e8];
    HeadingMap_s0097_b110 mColumnHeadings;   // +0x208
    HeadingMap_s0097_b110 mRowHeadings;      // +0x228

    bool ScrollCellsVertically(int delta);
    bool ScrollCellsHorizontally(int delta);
    bool CopyColumns(int srcStart, int dstStart, int count, int bVal);
    bool CopyRows(int srcStart, int dstStart, int count, int bVal);
    bool GetCellRect(int col, int row, RectT<float>* out);
    void ResizeColumnToFitCellWindows(int col, int count);
};
}
namespace Gr {
inline WinGrid_s0097_b110* Base(WinGridIface_s0097_b110* p) { return (WinGrid_s0097_b110*)((char*)p - 0x20c); }
}
namespace Gr {
inline void*    Window_s0097_b110(WinGridIface_s0097_b110* p) { return (char*)p - 0x208; }
}
// ---- items of slice s0097b110 end

// ---- items of slice s0097bfb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CellEntry { int col; int row; void* cell; };                                        // 12 bytes
void* operator new[](unsigned size, const char* name, int a, int b, int c, int d) throw(); // 0xf473a0
namespace Gr {
struct CellData_s0097_bfb0 {                 // 0x1c bytes, "UTFWin/Grid"
    int      mType;               // +0x00
    int      mCol;                // +0x04
    int      mRow;                // +0x08
    void*    mpWindow;            // +0x0c
    void*    mpText;              // +0x10
    int      pad14;               // +0x14
    int      pad18;               // +0x18
};
}
namespace Gr {
struct RBNode_s0097_bfb0 {
    RBNode_s0097_bfb0* right;                // +0x00  (greater)
    RBNode_s0097_bfb0* left;                 // +0x04  (smaller)
    RBNode_s0097_bfb0* parent;               // +0x08
    int     color;                // +0x0c
    int     key;                  // +0x10
    int     pad14;                // +0x14
    void*   value;                // +0x18
};
}
namespace Gr {
struct FmtMatrix_s0097_bfb0 {                // SparseMatrix<CellFormatExtra>, at IWinGrid + 0xb4
    char pad0[0x0c];
    void* mRoot;                  // +0x0c
};
}
namespace Gr {
struct SparseMatrixCells_s0097_bfb0 {
    char     pad0[0x0c];
    RBNode_s0097_bfb0*  mRoot;               // +0x0c (== header.parent)

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
}
namespace Gr {
extern void* EAAllocate(unsigned size, const char* name, int a, int b, int c, int d);  // 0xf473a0
}
namespace Gr {
extern void  EAFree(void* p);                                                          // 0xf47380
}
namespace Gr {
struct WindowStub    { bool  Initialize();                                             // 0xb1fbf0
                     };
}
namespace Gr {
struct WStrStub      { void* WStr_Ctor(const wchar_t* s, void** alloc);                // 0x41df50
                     };
}
namespace Gr {
struct TextValueStub { void* TextValue_ctor(const wchar_t* s, void* font, void** alloc);  // 0x93d6f0
                     };
}
namespace Gr {
struct WinGrid_s0097_bfb0 {
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
    SparseMatrixCells_s0097_bfb0 mCells;         // +0x320

    float GetColumnWidthInternal(int col);                              // 0x979db0
    float GetRowHeightInternal(int row);                                // 0x979f10
    void  SetSizeCachedActualForRow(int row, int count, float h);       // 0x9789a0
    void  SetSizeCachedActualForColumn(int col, int count, float w);    // 0x978b50
    bool  CopyCellData(int srcCol, int srcRow, int dstCol, int dstRow, int deep);  // 0x979bc0
    void  DisposeOfCellData(int col, int row, void* cell, int deep);    // 0x975c50
    bool  RecalculateAll();                                             // 0x97bc80

    bool  MakeRoom(int col, int row, int amount, int dir);
    bool  MakeRoomForRow(int row, int amount, int dir);  // 0x0097c4f0 (Gr::WinGrid::MakeRoomForRow)
    bool  MakeRoomForColumn(int col, int amount, int dir);  // 0x0097c580 (Gr::WinGrid::MakeRoomForColumn)
    bool  Init();  // 0x0097c6d0 (Gr::WinGrid::Init)
    bool  OnTick();  // 0x0097c6f0 (Gr::WinGrid::OnTick)
};
}
namespace Gr {
struct WinGridIface_s0097_bfb0 {
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
    FmtMatrix_s0097_bfb0 mColFormat;         // +0x0b4
    char     padFmt[0x114 - 0x0b4 - sizeof(FmtMatrix_s0097_bfb0)];
    SparseMatrixCells_s0097_bfb0 mCells;     // +0x114
    char     padCells[0x230 - 0x114 - sizeof(SparseMatrixCells_s0097_bfb0)];

    float GetColumnWidth(int start, int count);
    float GetRowHeight(int start, int count);
    bool  DeleteColumns(int start, int count, int dir);
    bool  DeleteRows(int start, int count, int dir);
    bool  MakeCellVisible(int col, int row);
    bool  SetCellTextValue(int col, int row, const wchar_t* text, void* font, int dir, bool flag);
    bool  SetCellImage(int col, int row, void* image, int dir);
};
}
namespace Gr {
inline WinGrid_s0097_bfb0* Base_s0097_bfb0(WinGridIface_s0097_bfb0* p) { return (WinGrid_s0097_bfb0*)((char*)p - 0x20c); }
}
namespace Gr {
static void MarkDirtyIface(WinGridIface_s0097_bfb0* ig)
{
    void* w = (char*)ig - 0x208;
    ig->mbDirty = true;
    ((void(__thiscall*)(void*, int, int))GVT(w, 0x7c / 4))(w, 8, 1);
}
}
// ---- items of slice s0097bfb0 end

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
bool EA::UTFWinControls::WinGrid::OnMouseMove(float x, float y, unsigned int param)
{
    char* base = (char*)this;

    // 0x30-byte scratch frame: first the hit-test output, then the row-extra-data
    // key / node passed to the inlined hashtable insert.
    struct Row {
        unsigned k0, k1;             // +0x00 .. +0x04  (hit-test output)
        unsigned key0, key1, key2;   // +0x08 .. +0x10  (map key)
        unsigned it0, it1;           // +0x14 .. +0x18  (insert iterator result)
        unsigned hash;               // +0x1c
        void*    value;              // +0x20
        unsigned pad0, pad1;         // +0x24 .. +0x28
        void*    keyPtr;             // +0x2c
    } row;

    WinGridSub* sub = (WinGridSub*)(base + 0x20c);
    if (!sub->OnHitTest(x, y, &y, &row))
        return false;

    unsigned a = *(unsigned*)&y;
    unsigned b = row.k0;
    unsigned c = row.k1;
    if (a == *(unsigned*)(base + 0x3a8) &&
        b == *(unsigned*)(base + 0x3ac) &&
        c == *(unsigned*)(base + 0x3b0))
        return true;

    row.key0 = a;
    *(unsigned*)(base + 0x3a8) = a;
    row.key1 = b;
    row.key2 = c;
    *(unsigned*)(base + 0x3ac) = b;
    *(unsigned*)(base + 0x3b0) = c;
    row.hash = 0x9a1552d6;
    void* v = *(void**)(base + 0x84);
    row.value = v ? v : *(void**)(base + 0x80);
    row.keyPtr = &row.key0;

    WinGridVt* vt = (WinGridVt*)(base + 4);
    vt->OnInsert(&row.it0);
    vt->OnSelChanged();
    return true;
}

// @ 0x00970540
namespace EA { namespace UTFWinControls {
void WinGrid_s0096_f3f0::OnMouseWheel(int, int, int, int delta)
{
    ((WinGridSub*)((char*)this + 0x20c))->OnWheel(delta / -100);
}
}}  // namespace EA::UTFWinControls

// @ 0x00970c70
void EA::UTFWinControls::CRect::NormalizeRect()
{
    if (left > right) {
        int l = left;
        left = right;
        right = l;
    }
    if (top > bottom) {
        int t = top;
        top = bottom;
        bottom = t;
    }
}

// @ 0x009719a0
void EA::UTFWinControls::Window::InvalidateLayout()
{
    EA::UTFWinControls::IWindow::InvalidateLayout();

    EA::UTFWinControls::IWinGrid_s0097_0f30* pGrid = (EA::UTFWinControls::IWinGrid_s0097_0f30*)((char*)this + 0x208);

    EA::UTFWinControls::RectF gridArea;
    pGrid->GetGridArea(gridArea);
    EA::UTFWinControls::RectF cellArea;
    pGrid->GetCellArea(cellArea);

    EA::UTFWinControls::WinGrid_s0097_0f30* pWin = (EA::UTFWinControls::WinGrid_s0097_0f30*)((char*)this - 4);
    pWin->mGrid.mVisibleGridAreaWidth = gridArea.right - gridArea.left;
    pWin->mGrid.mVisibleGridAreaHeight = gridArea.bottom - gridArea.top;
    pWin->mGrid.mVisibleCellAreaWidth = cellArea.right - cellArea.left;
    pWin->mGrid.mVisibleCellAreaHeight = cellArea.bottom - cellArea.top;
    ((EA::UTFWinControls::IWindow*)this)->SetFlag(8, 1);
    pWin->mGrid.mbRecalculateAllNeeded = 1;
}

// @ 0x00972d30
void EA::UTFWinControls::CellList::clear()
{
    EA::UTFWinControls::CellNode* pFirst = mpHead;
    if (pFirst != (EA::UTFWinControls::CellNode*)this) {
        do {
            EA::UTFWinControls::CellNode* pNext = pFirst->mpLeft;
            EA::UTFWinControls::operator delete(pFirst);
            pFirst = pNext;
        } while (pFirst != (EA::UTFWinControls::CellNode*)this);
    }
    mpTail = (EA::UTFWinControls::CellNode*)this;
    mpHead = (EA::UTFWinControls::CellNode*)this;
}

// @ 0x00972d60
void EA::UTFWinControls::CellRbtree::find(EA::UTFWinControls::CellNode** pOut, const EA::UTFWinControls::CellData_s0097_1eb0* pKey)
{
    EA::UTFWinControls::CellNode* pHeader = (EA::UTFWinControls::CellNode*)&mHeaderLeft;
    EA::UTFWinControls::CellNode* pResult = pHeader;
    EA::UTFWinControls::CellNode* pNode = mpRoot;
    if (pNode) {
        const unsigned key = *(const unsigned*)((const char*)pKey + 0xc);
        do {
            if ((unsigned)pNode->mKey < key)
                pNode = pNode->mpLeft;
            else {
                pResult = pNode;
                pNode = pNode->mpRight;
            }
        } while (pNode);
    }
    if (pResult != pHeader &&
        *(const unsigned*)((const char*)pKey + 0xc) >= (unsigned)pResult->mKey)
        *pOut = pResult;
    else
        *pOut = pHeader;
}

// @ 0x00972dd0
EA::UTFWinControls::CellNode* EA::UTFWinControls::CellRbtree::AllocateNode(const EA::UTFWinControls::CellData_s0097_1eb0* pData, void* pArg)
{
    EA::UTFWinControls::CellNode* pNode = (EA::UTFWinControls::CellNode*)EA::UTFWinControls::EAAllocate(0x50, "EASTL", 0, 0, "rbtree.cpp", 0xd1);
    if (pNode) {
        unsigned* pDst = (unsigned*)((char*)pNode + 0x10);
        const unsigned* pSrc = (const unsigned*)((const char*)pData + 0x10);
        for (unsigned i = 0; i < 0x10u; ++i)
            pDst[i] = pSrc[i];
    }
    pNode->mpLeft = 0;
    pNode->mpRight = 0;
    pNode->mUnknown08 = (int)pArg;
    pNode->mbColor = *(char*)((const char*)pData + 0xc);
    return pNode;
}

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

// @ 0x00973dd0
void RBTree_s0097_3dd0::DoInsertValueImpl_1c(RBNode** __restrict out, RBNode* parent, const V28* value, char force)
{
    int side;
    if (force || parent == &anchor || (unsigned)value->f[3] < *(unsigned*)((char*)parent + 0x1c))
        side = 0;
    else
        side = 1;
    RBNode* n = (RBNode*)EA_ALLOC(0x2c);
    V28* dst = (V28*)((char*)n + 0x10);
    if (dst) memcpy(dst, value, sizeof(V28));
    RBNode** o = out;
    RBTreeInsert(n, parent, &anchor, side);
    size++;
    *o = n;
}

// @ 0x00973e60
void RBTree_s0097_3dd0::DoInsertValueImpl_40(RBNode** __restrict out, RBNode* parent, const V40* value, char force)
{
    int side;
    if (force || parent == &anchor || value->f[0] < *(int*)((char*)parent + 0x10))
        side = 0;
    else
        side = 1;
    RBNode* n = (RBNode*)EA_ALLOC(0x50);
    V40* dst = (V40*)((char*)n + 0x10);
    if (dst) memcpy(dst, value, sizeof(V40));
    RBTreeInsert(n, parent, &anchor, side);
    RBNode** o = out;
    size++;
    *o = n;
}

// @ 0x00973ef0
void RBTree_s0097_3dd0::DoInsertValueImpl_0c(RBNode** __restrict out, RBNode* parent, const V0c* value, char force)
{
    int side;
    if (force || parent == &anchor || value->f[0] < *(int*)((char*)parent + 0x10))
        side = 0;
    else
        side = 1;
    RBNode* n = (RBNode*)EA_ALLOC(0x1c);
    V0c* dst = (V0c*)((char*)n + 0x10);
    if (dst) memcpy(dst, value, sizeof(V0c));
    RBTreeInsert(n, parent, &anchor, side);
    RBNode** o = out;
    size++;
    *o = n;
}

// @ 0x00973f80
RBNode* RBTree_s0097_3dd0::DoCopySubtree_40(const RBNode* src, RBNode* parent)
{
    RBNode* newRoot = CreateNodeCopy40(src, parent);
    if (src->right)
        newRoot->right = DoCopySubtree_40(src->right, newRoot);
    RBNode* dest = newRoot;
    const RBNode* s = src->left;
    while (s) {
        RBNode* n = (RBNode*)EA_ALLOC(0x50);
        V40* d = (V40*)((char*)n + 0x10);
        if (d) memcpy(d, (const char*)s + 0x10, sizeof(V40));
        n->right = 0;
        n->left = 0;
        n->parent = dest;
        FLD(char, n, 0xc) = FLD(char, s, 0xc);
        dest->left = n;
        if (s->right)
            n->right = DoCopySubtree_40(s->right, n);
        dest = n;
        s = s->left;
    }
    return newRoot;
}

// @ 0x00974050
RBNode* RBTree_s0097_3dd0::DoCopySubtree_0c(const RBNode* src, RBNode* parent)
{
    RBNode* newRoot = CreateNodeCopy(src, parent);
    if (src->right)
        newRoot->right = DoCopySubtree_0c(src->right, newRoot);
    RBNode* dest = newRoot;
    const RBNode* s = src->left;
    if (!s) return newRoot;
    do {
        RBNode* n = (RBNode*)EA_ALLOC(0x1c);
        V0c* d = (V0c*)((char*)n + 0x10);
        if (d) memcpy(d, (const char*)s + 0x10, sizeof(V0c));
        n->right = 0;
        n->left = 0;
        n->parent = dest;
        FLD(char, n, 0xc) = FLD(char, s, 0xc);
        dest->left = n;
        if (s->right)
            n->right = DoCopySubtree_0c(s->right, n);
        dest = n;
        s = s->left;
    } while (s);
    return newRoot;
}

// @ 0x00974110
bool __cdecl SerializeProp(void** out, int a2, int a3, void** allocator)
{
    out[0] = g_serTypeTable[*(unsigned short*)((char*)a3 + 0xc) & 0xfff];
    char* p = (char*)(*(int*)((char*)a2 + 4) + *(int*)((char*)a3 + 0x10));
    int count = *(int*)(p + 0xc);
    out[2] = (void*)count;
    if (count == 0) return true;
    int* arr = (int*)((Alloc*)allocator)->allocate(count * 4, 4);
    out[1] = arr;
    int sentinel = *(int*)(*(int*)(p + 4) + *(int*)(p + 8) * 4);
    for (unsigned i = 0; i < *(unsigned*)((char*)out + 8); i++) {
        HatIter it;
        unsigned k = i;
        HatIter* r = ((HatTable*)p)->find(&it, k);
        int* node = (int*)r->node;
        arr[i] = (node == (int*)sentinel) ? 0 : node[1];
    }
    return true;
}

// @ 0x009741c0
bool WinGrid_s0097_3dd0::OnKeyDown(int a1, unsigned key, unsigned flags)
{
    if (a1 == 0) {
        bool sh = (flags >> 2) & 1;
        if (key - 0x21 <= 0xc) {
        switch (key) {
        case 0x21:
            if (sh) kF80(); else kF30();
            return true;
        case 0x22:
            if (sh) kFb0(); else kF60();
            return true;
        case 0x25: case 0x26: case 0x27: case 0x28:
            DoArrowKey(key, flags);
            return true;
        case 0x24:
            ((VGrid*)((char*)this + 0x20c))->s0x90(0, 0);
            return true;
        case 0x23: {
            int vis[4] = {0, 0, 0, 0};
            if ((FLD(unsigned, this, 0x210) & 0x10000) == 0 || (FLD(unsigned, this, 0x210) & 0x8000) == 0)
                ((VGrid*)((char*)this + 0x20c))->s0xc4(vis);
            if ((FLD(unsigned, this, 0x210) & 0x8000) == 0) {
                ((VGrid*)((char*)this + 0x20c))->s0x88(vis[2]);
            } else {
                int t = FLD(int, this, 0x264);
                if (t != -1 && t != 0) ((VGrid*)((char*)this + 0x20c))->s0x88(t - 1);
            }
            if ((FLD(unsigned, this, 0x210) & 0x10000) == 0) {
                ((VGrid*)((char*)this + 0x20c))->s0x8c(vis[3]);
                return true;
            }
            int t = FLD(int, this, 0x268);
            if (t != -1 && t != 0) ((VGrid*)((char*)this + 0x20c))->s0x8c(t - 1);
            return true;
        }
        case 0x2d: {
            unsigned f = FLD(unsigned, this, 0x210);
            if (f & 0x80u) FLD(unsigned, this, 0x210) = f & ~0x80u;
            else           FLD(unsigned, this, 0x210) = f | 0x80u;
            return true;
        }
        }
        }
    }
    return false;
}

// @ 0x009743e0
int IWinGrid::GetSelectionCount()
{
    RBNode* head = (RBNode*)((char*)this + 0xa8);
    int n = 0;
    for (RBNode* p = head->right; p != head; p = p->right)
        n++;
    return n;
}

// @ 0x00974400
bool IWinGrid::GetSelection(CellCoordinates* out, int* count)
{
    RBNode* head = (RBNode*)((char*)this + 0xa8);
    int n = 0;
    for (RBNode* p = head->right; p != head; p = p->right)
        n++;
    if (*count > n) *count = n;
    if (!out) return true;
    RBNode* p = head->right;
    for (int i = 0; i < *count; i++) {
        out->nColumn = FLD(int, p, 8);
        out->nRow = FLD(int, p, 0xc);
        out++;
        p = p->right;
    }
    return true;
}

// @ 0x00974510
bool IWinGrid::GetCellUsedRange(Rect_s0097_3dd0* rect)
{
    SparseMatrix_s0097_3dd0* m = (SparseMatrix_s0097_3dd0*)((char*)this + 0x114);
    int row;
    int minCol = m->GetMinUsedColAndRow(&row);
    if (minCol != (int)0x80000000) {
        rect->left = minCol;
        rect->top = m->t.size == 0 ? (int)0x80000000 : FLD(int, m->t.anchor.left, 0x14);
        rect->right = m->GetMaxUsedColAndRow(&row);
        rect->bottom = m->t.size == 0 ? (int)0x80000000
            : FLD(int, RBTreeDecrement(&m->t.anchor), 0x14);
        return true;
    }
    rect->left = 0;
    rect->top = 0;
    rect->right = 0;
    rect->bottom = 0;
    return false;
}

// @ 0x009745b0
bool IWinGrid::GetCellType(int col, int row, int* out)
{
    SparseMatrix_s0097_3dd0* m = (SparseMatrix_s0097_3dd0*)((char*)this + 0x114);
    void** p = 0;
    if (m->GetCellPtr(col, row, &p))
        *out = ((CellData_s0097_3dd0*)*p)->nCellType;
    return p != 0;
}

// @ 0x009745f0
bool IWinGrid::GetCellFormat(int col, int row, CellFormat_s0097_3dd0* out)
{
    IWinGrid* pThis = this;
    void** cell = 0;
    CellFormatExtra_s0097_3dd0* ex = 0;
    memcpy(out, (char*)pThis + 0x144, sizeof(CellFormat_s0097_3dd0));
    if (((VGridCf*)pThis)->s0x144(row, &ex) && ex)
        MergeFormat(out, ex);
    if (((VGridCf*)pThis)->s0x140(col, &ex) && ex)
        MergeFormat(out, ex);
    if (((SparseMatrix_s0097_3dd0*)((char*)pThis + 0x114))->GetCellPtr(col, row, &cell) && cell) {
        CellFormat_s0097_3dd0* f = ((CellData_s0097_3dd0*)*cell)->pCellFormat;
        if (f) MergeFormat(out, f);
    }
    return true;
}

// @ 0x00974860
bool IWinGrid::GetColCellFormatExtra(int col, CellFormatExtra_s0097_3dd0** out)
{
    SparseMatrix_s0097_3dd0* m = (SparseMatrix_s0097_3dd0*)((char*)this + 0xb4);
    if (!m->GetCellPtr(col, 0, (void***)out)) return false;
    CellFormatExtra_s0097_3dd0* e = *out;
    bool any = e->nBorder == 0 || e->nHAlignment == 0
            || e->nSizeCachedActual == -1.0f || e->nSizeDefault == -1.0f
            || e->nTextStyle == 0 || e->nWrapping == -1 || e->nVAlignment == 0;
    return !any;
}

// @ 0x009748f0
bool IWinGrid::GetRowCellFormatExtra(int row, CellFormatExtra_s0097_3dd0** out)
{
    SparseMatrix_s0097_3dd0* m = (SparseMatrix_s0097_3dd0*)((char*)this + 0xe4);
    if (!m->GetCellPtr(0, row, (void***)out)) return false;
    CellFormatExtra_s0097_3dd0* e = *out;
    bool any = e->nBorder == 0 || e->nHAlignment == 0
            || e->nSizeCachedActual == -1.0f || e->nSizeDefault == -1.0f
            || e->nTextStyle == 0 || e->nWrapping == -1 || e->nVAlignment == 0;
    return !any;
}

// @ 0x00974980
bool IWinGrid::GetCellTextValue(int col, int row, void** out)
{
    SparseMatrix_s0097_3dd0* m = (SparseMatrix_s0097_3dd0*)((char*)this + 0x114);
    void** p;
    if (m->GetCellPtr(col, row, &p) && ((CellData_s0097_3dd0*)*p)->nCellType == 2
        && ((CellData_s0097_3dd0*)*p)->pCellData) {
        *out = *(void**)((CellData_s0097_3dd0*)*p)->pCellData;
        return true;
    }
    return false;
}

// @ 0x009749d0
bool IWinGrid::GetCellImage(int col, int row, void** out)
{
    SparseMatrix_s0097_3dd0* m = (SparseMatrix_s0097_3dd0*)((char*)this + 0x114);
    void** p;
    if (m->GetCellPtr(col, row, &p) && ((CellData_s0097_3dd0*)*p)->nCellType == 4) {
        void* img = ((CellData_s0097_3dd0*)*p)->pCellData;
        *out = img;
        if (img) ((VImg*)img)->s0();
        return true;
    }
    return false;
}

// @ 0x00974a20
bool IWinGrid::GetCellWindow(int col, int row, void** out)
{
    SparseMatrix_s0097_3dd0* m = (SparseMatrix_s0097_3dd0*)((char*)this + 0x114);
    void** p;
    if (m->GetCellPtr(col, row, &p) && ((CellData_s0097_3dd0*)*p)->nCellType == 1) {
        *out = ((CellData_s0097_3dd0*)*p)->pCellData;
        return true;
    }
    return false;
}

// @ 0x00974a60
void EA::UTFWinControls::WinGrid::DoWindowRemoval(int nRow, int nCol, EA::UTFWin::IWindow * pWindow)
{
    if (!pWindow) return;
    CellData_s0097_3dd0 key;
    key.nCellType = 1;
    key.nColumn = nCol;
    key.nRow = nRow;
    key.pCellData = pWindow;
    key.pCellFormat = 0;
    key.pExtraData = 0;
    key.nCellFlags = 0;
    RBTree_s0097_3dd0* tree = (RBTree_s0097_3dd0*)((char*)this + 0x380);
    RBNode* node;
    tree->Find(&node, &key);
    RBNode* end = (RBNode*)((char*)tree + 4);
    if (node != end) {
        tree->size--;
        RBTreeIncrement(node);
        RBTreeErase(node, end);
        EFree(node);
        ((VWin*)((char*)this + 4))->s0xe0(pWindow);
    }
}

// @ 0x00974b00
void EA::UTFWinControls::WinGrid::PlaceAllCellWindows()
{
    RBTree_s0097_3dd0* list = (RBTree_s0097_3dd0*)((char*)this + 0x380);
    RBNode* end = &list->anchor;
    for (RBNode* n = end->left; n != end; n = RBTreeIncrement(n)) {
        if (FLD(int, n, 0x10) != 1) continue;
        int nCol = FLD(int, n, 0x14);
        int nRow = FLD(int, n, 0x18);
        RBTree_s0097_3dd0* outer = (RBTree_s0097_3dd0*)((char*)this + 0x320);
        RBNode* on = FindInt(outer, nRow);
        if (on == &outer->anchor) continue;
        RBTree_s0097_3dd0* inner = (RBTree_s0097_3dd0*)((char*)on + 0x18);
        RBNode* in = FindInt(inner, nCol);
        if (in == &inner->anchor) continue;
        void* cell = FLD(void*, in, 0x18);
        if (!cell) continue;
        void* w = FLD(void*, cell, 0xc);
        if (!w) continue;
        unsigned fl = FLD(unsigned, cell, 0x18);
        PlaceCellWindow(FLD(int, cell, 4), FLD(int, cell, 8), (EA::UTFWin::IWindow *)w, fl & 1, (fl >> 1) & 1);
    }
}

// @ 0x00974bf0
int IWinGrid::GetCellExtraData(int col, int row)
{
    SparseMatrix_s0097_3dd0* m = (SparseMatrix_s0097_3dd0*)((char*)this + 0x114);
    void** p;
    if (m->GetCellPtr(col, row, &p) && *p)
        return (int)((CellData_s0097_3dd0*)*p)->pExtraData;
    return 0;
}

// @ 0x00974c30
int __cdecl Comparator(CellData_s0097_3dd0* a, CellData_s0097_3dd0* b)
{
    int t = a->nCellType;
    void* pa = a->pCellData;
    void* pb = b->pCellData;
    if (t != b->nCellType) return 0;
    if (!pa) return 0;
    if (!pb) return 0;
    if (t != 2) return 0;
    return ((ComparatorStr*)pa)->fn(*(const wchar_t**)pb);
}

// @ 0x00975300
void EA::UTFWinControls::CellList_s0097_4c60::push_back(const int* pValue)
{
    EA::UTFWinControls::CellListNode* pNode = (EA::UTFWinControls::CellListNode*)EA::UTFWinControls::EAAllocate(0x10, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (&pNode->mValueA) {
        pValue += 0;
        *(long long*)&pNode->mValueA = *(const long long*)pValue;
    }
    pNode->mpPrev = (EA::UTFWinControls::CellListNode*)this;
    pNode->mpNext = mpTail;
    mpTail->mpPrev = pNode;
    mpTail = pNode;
}

// @ 0x00975350
bool EA::UTFWinControls::SparseMatrix_s0097_4c60::GetMinMaxUsedColForRow(int row, int* pMin, int* pMax)
{
    *pMin = 0x7fffffff;
    *pMax = 0x80000000;
    bool bFound = false;

    EA::UTFWinControls::SparseMatrixIter it;
    it.mpNode = 0;
    it.mpOwner = 0;
    FirstUsed(&it);
    if (it.mpNode != (char*)this + 4) {
        EA::UTFWinControls::CellRecord* pRec = *(EA::UTFWinControls::CellRecord**)((char*)it.mpNode + 0x20);
        *pMin = *(int*)((char*)pRec + 0x14);
        *pMax = *(int*)((char*)pRec + 0x14);
        return true;
    }
    return bFound;
}

// @ 0x009753c0
void EColIterB::Init(int row)
{
    EColIterB* self = this;
    self->mRow = row;
    void** pSentinel = &self->mpListHead;
    pSentinel[1] = 0;
    pSentinel[2] = 0;
    pSentinel[3] = 0;
    mpListHead = pSentinel;
    mpListTail = pSentinel;
    mpListSentinel2 = 0;
    mbFlag = 0;
    mUnknown18 = 0;
}

// @ 0x009753f0
void* EA::UTFWinControls::CellRbtree_s0097_4c60::DoInsertValue(const EA::UTFWinControls::CellData_s0097_4c60* pValue, void* pOut)
{
    EA::UTFWinControls::CellRbtNode* pHeader = (EA::UTFWinControls::CellRbtNode*)&mHeaderLeft;
    EA::UTFWinControls::CellRbtNode* pPos = pHeader;
    bool bLeft = true;

    EA::UTFWinControls::CellRbtNode* pNode = mpRoot;
    if (pNode != 0) {
        do {
            pPos = pNode;
            bLeft = *(const unsigned*)((const char*)pValue + 0xc) < pNode->mKey;
            pNode = bLeft ? pNode->mpRight : pNode->mpLeft;
        } while (pNode != 0);
    }

    EA::UTFWinControls::CellRbtNode* pPrev = pPos;
    if (bLeft) {
        if (pPos == *(EA::UTFWinControls::CellRbtNode**)((char*)this + 8))
            goto insert;
        pPrev = RBTreeDecrement(pPos);
    }
    if (*(const unsigned*)((const char*)pValue + 0xc) <= pPrev->mKey) {
        *(void**)pOut = pPrev;
        *(char*)((char*)pOut + 4) = 0;
        return pOut;
    }

insert:
    DoInsertValueImpl(&pValue, pPos, pValue, 0);
    *(void**)pOut = (void*)pValue;
    *(char*)((char*)pOut + 4) = 1;
    return pOut;
}

// @ 0x00975e00
int* MergeSelection(int* pFirst1, int* pLast1, int* pFirst2, int* pLast2, int* pOut, int (*pLess)(int, int), const int** ppTable, bool bSwap)
{
    while (pFirst1 != pLast1 && pFirst2 != pLast2) {
        const int* pTable = *ppTable;
        int a = pTable[*pFirst2];
        int b = pTable[*pFirst1];
        int r = bSwap ? pLess(a, b) : pLess(a, b);
        if (r < 0) {
            *pOut = *pFirst2;
            ++pFirst2;
        }
        else {
            *pOut = *pFirst1;
            ++pFirst1;
        }
        ++pOut;
    }
    return pOut;
}

// @ 0x00975ea0
void WinGrid_s0097_5ea0::DoWindowAddition(int col, int row, void* pWindow, int a4, int a5)
{
    if (pWindow == 0)
        return;
    if (!mWindow.AcceptsWindow(pWindow))
        return;

    EA::UTFWinControls::CellData_s0097_5ea0 cd;
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

// @ 0x00975f30
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

// @ 0x00975f80
void* IWinGridIface::GetColumnExtraData(unsigned key)
{
    unsigned k = key;
    return *mColumnExtraData.op_brackets(&k);
}

// @ 0x00975fa0
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

// @ 0x00975ff0
void* IWinGridIface::GetRowExtraData(unsigned key)
{
    unsigned k = key;
    return *mRowExtraData.op_brackets(&k);
}

// @ 0x00976010
bool WinGrid_s0097_5ea0::CopyCellData(int c1, int r1, EA::UTFWinControls::CellData_s0097_5ea0* src, int c2, int r2, EA::UTFWinControls::CellData_s0097_5ea0* dst)
{
    if (dst)
        DisposeOfCellData(c2, r2, dst, false);
    if (src->mType == 1)
        return false;

    if (dst == 0) {
        dst = (EA::UTFWinControls::CellData_s0097_5ea0*)EAAllocate(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
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
            *(CellFormat_s0097_5ea0*)fmt = CellFormat_s0097_5ea0();
        dst->pad10 = (int)fmt;
        *(CellFormat_s0097_5ea0*)fmt = *(CellFormat_s0097_5ea0*)src->pad10;
    }
    return true;
}

// @ 0x00976160
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

// @ 0x00976310
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

// @ 0x00976390
PairRowCD::PairRowCD(const int* pk, const int* src)
{
    key = *pk;
    pad = src[0];
    row.CtorFrom(src + 1);
}

// @ 0x009763c0
PairRowCF::PairRowCF(const int* pk, const int* src)
{
    key = *pk;
    pad = src[0];
    row.CtorFrom(src + 1);
}

// @ 0x00976450
void CellsMatrix::DoNukeSubtree(EA::UTFWinControls::RBN* node)
{
    while (node) {
        DoNukeSubtree(node->right);
        EA::UTFWinControls::RBN* next = node->left;
        RowNode* rn = (RowNode*)node;
        EA::UTFWinControls::MatrixRow* row = &rn->row;
        EA::UTFWinControls::RBN* inner = (EA::UTFWinControls::RBN*)rn->row.anchor.parent;
        while (inner) {
            row->f(*(void**)inner);                        // 0x009a9600
            EA::UTFWinControls::RBN* suiv = inner->left;
            EaFree(inner);
            inner = suiv;
        }
        EaFree(node);
        node = next;
    }
}

// @ 0x009764c0
void RowTreeCD::InsertValue(PairRowCD** out, EA::UTFWinControls::RBN* hint, const PairRowCD* value, bool bHint)
{
    bool bContinue;
    if (!bHint && (EA::UTFWinControls::RBN*)hint != &anchor && value->key >= ((KeyNode_s0097_5ea0*)hint)->key)
        bContinue = true;
    else
        bContinue = false;

    EA::UTFWinControls::RBN* node = (EA::UTFWinControls::RBN*)EAAllocate(0x34, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    RowNode* rn = (RowNode*)node;
    if (rn) {
        rn->key = value->key;
        rn->pad14 = value->pad;
        rn->row.CtorFrom((const int*)&value->row);
    }
    EA::UTFWinControls::RBTreeInsert(node, hint, &anchor, bContinue);          // 0x009216a0
    ++mnSize;
    *out = (PairRowCD*)node;
}

// @ 0x00976550
void RowTreeCF::InsertValue(PairRowCF** out, EA::UTFWinControls::RBN* hint, const PairRowCF* value, bool bHint)
{
    bool bContinue;
    if (!bHint && (EA::UTFWinControls::RBN*)hint != &anchor && value->key >= ((KeyNode_s0097_5ea0*)hint)->key)
        bContinue = true;
    else
        bContinue = false;

    EA::UTFWinControls::RBN* node = (EA::UTFWinControls::RBN*)EAAllocate(0x34, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    RowNode* rn = (RowNode*)node;
    if (rn) {
        rn->key = value->key;
        rn->pad14 = value->pad;
        ((MatrixRowC*)&rn->row)->CtorFrom((const int*)&value->row);
    }
    EA::UTFWinControls::RBTreeInsert(node, hint, &anchor, bContinue);
    ++mnSize;
    *out = (PairRowCF*)node;
}

// @ 0x009765e0
int BulkAssignHeadings(void* p1, const void* p2, const void* p3)
{
    HeadingMap_s0097_5ea0* map = (HeadingMap_s0097_5ea0*)(*(char**)((char*)p1 + 4) + *(const int*)((char*)p3 + 0x10));
    map->ClearNodes(*(void**)((char*)map + 4), *(const unsigned*)((char*)map + 8));
    *(int*)((char*)map + 0xc) = 0;

    void** items = *(void***)((const char*)p2 + 4);
    unsigned count = *(const unsigned*)((const char*)p2 + 8);
    for (unsigned i = 0; i < count; ++i, ++items) {
        const wchar_t* s = (const wchar_t*)*items;
        if (s) {
            WStringObj* w = (WStringObj*)map->op_brackets(&i);
            w->assign(s, s + EA::UTFWinControls::wcslen(s));
        }
    }
    return 1;
}

// @ 0x00976670
void IWinGridIface::SetRowHeading(unsigned key, void** pOut)
{
    unsigned k = key;
    void** w = mRowHeadings.op_brackets(&k);
    *pOut = *w;
}

// @ 0x009766a0
void IWinGridIface::SetColumnHeading(unsigned key, const wchar_t* text)
{
    WStringObj* w = (WStringObj*)mRowHeadings.op_brackets(&key);
    w->assign(text, text + EA::UTFWinControls::wcslen(text));
}

// @ 0x009766f0
void IWinGridIface::GetColumnHeading(unsigned key, void** pOut)
{
    unsigned k = key;
    void** w = mColumnHeadings.op_brackets(&k);
    *pOut = *w;
}

// @ 0x00976720
void IWinGridIface::SetColumnHeading2(unsigned key, const wchar_t* text)
{
    WStringObj* w = (WStringObj*)mColumnHeadings.op_brackets(&key);
    w->assign(text, text + EA::UTFWinControls::wcslen(text));
}

// @ 0x00976770
void CellsMatrix::EraseRow(EA::UTFWinControls::RBN** out, EA::UTFWinControls::RBN* node)
{
    --mnSize;
    EA::UTFWinControls::RBN* next = EA::UTFWinControls::RBTreeIncrement(node);                     // 0x00921580
    EA::UTFWinControls::RBTreeErase(node, &anchor);                            // 0x00921880
    RowNode* rn = (RowNode*)node;
    rn->row.f(rn->row.anchor.parent);                      // 0x009a9600
    EaFree(node);
    *out = next;
}

// @ 0x009768e0
bool CellsMatrix::RemoveCell(int col, int row, EA::UTFWinControls::CellData_s0097_5ea0** out)
{
    EA::UTFWinControls::RBN* rn;
    Find(&rn, &row);                       // outer: row
    if (rn == &anchor)
        return false;

    RowNode* rnode = (RowNode*)rn;
    EA::UTFWinControls::RBN* inner;
    ((EA::UTFWinControls::TreeHdr*)&rnode->row)->Find(&inner, &col);   // inner: col
    if (inner == &rnode->row.anchor)
        return false;

    if (out)
        *out = ((ColNode*)inner)->value;
    --rnode->row.mnSize;
    EA::UTFWinControls::RBTreeIncrement(inner);
    EA::UTFWinControls::RBTreeErase(inner, &rnode->row.anchor);
    EaFree(inner);
    --mnTotalCells;
    if (rnode->row.mnSize == 0)
        EraseRow(&rn, rn);
    return true;
}

// @ 0x00976980
bool CellsMatrix::RemoveRow(int start, int count)
{
    int end = start + count;
    for (int row = start; row < end; ++row) {
        EA::UTFWinControls::RBN* node = anchor.parent;
        EA::UTFWinControls::RBN* cand = &anchor;
        while (node) {
            if (((KeyNode_s0097_5ea0*)node)->key < row) {
                node = node->right;
            } else {
                cand = node;
                node = node->left;
            }
        }
        if (cand == &anchor || row < ((KeyNode_s0097_5ea0*)cand)->key)
            continue;
        RowNode* rn = (RowNode*)cand;
        mnTotalCells -= rn->row.mnSize;
        --mnSize;
        EA::UTFWinControls::RBTreeIncrement(cand);
        EA::UTFWinControls::RBTreeErase(cand, &anchor);
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

// @ 0x00976a40
bool CellsMatrix::RemoveCol(int start, int count)
{
    if (anchor.parent == 0)
        return true;

    EA::UTFWinControls::RBN* rn = anchor.left;
    int end = start + count;
    do {
        RowNode* rnode = (RowNode*)rn;
        for (int col = start; col < end; ++col) {
            EA::UTFWinControls::RBN* node = rnode->row.anchor.parent;
            EA::UTFWinControls::RBN* cand = &rnode->row.anchor;
            while (node) {
                if (((KeyNode_s0097_5ea0*)node)->key < col)
                    node = node->right;
                else { cand = node; node = node->left; }
            }
            if (cand == &rnode->row.anchor || col < ((KeyNode_s0097_5ea0*)cand)->key)
                continue;
            --rnode->row.mnSize;
            EA::UTFWinControls::RBTreeIncrement(cand);
            EA::UTFWinControls::RBTreeErase(cand, &rnode->row.anchor);
            EaFree(cand);
            --mnTotalCells;
        }
        EA::UTFWinControls::RBN* next;
        if (rnode->row.mnSize == 0) {
            next = EA::UTFWinControls::RBTreeIncrement(rn);
            --mnSize;
            EA::UTFWinControls::RBTreeErase(rn, &anchor);
            ColNode* inner = (ColNode*)rnode->row.anchor.parent;
            while (inner) {
                rnode->row.f(*(void**)inner);
                ColNode* suiv = (ColNode*)inner->base.left;
                EaFree(inner);
                inner = suiv;
            }
            EaFree(rn);
        } else {
            next = EA::UTFWinControls::RBTreeIncrement(rn);
        }
        rn = next;
    } while (rn != &anchor);
    return true;
}

// @ 0x00976bc0
bool IWinGridIface::ClearCell(int col, int row)
{
    bool bFormatted = false;
    bool bHadFormat = true;
    (void)bHadFormat;
    bool bWasFormatted = false;
    if (IVC3(bool, this, 0xac / 4, col, row, 0))
        bWasFormatted = true;

    EA::UTFWinControls::CellData_s0097_5ea0* cell;
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

// @ 0x00976c60
bool IWinGridIface::ClearCellFormat(int col, int row)
{
    bool bHadFont = false;
    EA::UTFWinControls::CellData_s0097_5ea0* cell = 0;
    if (mCells.GetCellPtr(col, row, &cell)) {
        if (cell) {
            if (cell->pad10) {
                CellFormat_s0097_5ea0* fmt = (CellFormat_s0097_5ea0*)cell->pad10;
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

// @ 0x00976d20
void WinGrid_s0097_5ea0::DisposeOfAllCellData()
{
    unsigned n = (unsigned)mIface.mCells.mnMaxCol * 0xc;
    EA::UTFWinControls::CellData_s0097_5ea0** list = (EA::UTFWinControls::CellData_s0097_5ea0**)EAAllocate(n, "UTFWin/Grid", 0, 0, 0, 0);
    if (list) {
        int count = mIface.mCells.GetCellsInRange(0, 0, 0x7fffffff, 0x7fffffff, list);
        if (count > 0) {
            EA::UTFWinControls::CellData_s0097_5ea0** p = list + 1;
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

// @ 0x00976dd0
bool InsertCellFmt(FmtTree* self, int col, int row, const FmtExtra* value, FmtExtra* out)
{
    if (row < self->mnMinRow || col < self->mnMinCol ||
        row > self->mnMaxRow || col > self->mnMaxCol)
        return false;

    EA::UTFWinControls::RBN* rowNode;
    self->Find(&rowNode, &row);
    if (rowNode != &self->anchor) {
        RowNode* rn = (RowNode*)rowNode;
        EA::UTFWinControls::RBN* inner;
        ((EA::UTFWinControls::TreeHdr*)&rn->row)->Find(&inner, &col);
        if (inner == &rn->row.anchor) {
            // insert a new inner cell into the existing row
            ColNode* c = (ColNode*)inner;  // unused; new element path
            FmtExtra tmp;
            tmp = *value;               // 0xe dwords
            self->InsertCellInner((EA::UTFWinControls::RBN**)&inner, &col, &tmp);
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
        EA::UTFWinControls::RBN* newNode;
        self->InsertRow(&newNode, (EA::UTFWinControls::RBN*)&self->anchor, &tmp);
        ++self->mnTotalCells;
    }
    return true;
}

// @ 0x00976f90
bool CellsMatrix_s0097_6f90::InsertCell(int col, int row, void* value, void** out)
{
    if (row < mnMinRow || col < mnMinCol || row > mnMaxRow || col > mnMaxCol)
        return false;

    RBN_s0097_6f90* rowNode;
    ((TreeHdr_s0097_6f90*)this)->Find(&rowNode, &row);
    if (rowNode != &anchor) {
        RowNode_s0097_6f90* rn = (RowNode_s0097_6f90*)rowNode;
        RBN_s0097_6f90* inner;
        ((TreeHdr_s0097_6f90*)rn->row)->Find(&inner, &col);
        if (inner != (RBN_s0097_6f90*)(rn->row + 0x1c)) {
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
        FmtInsertLeaf((FmtTree_s0097_6f90*)rn->row, &inner, &col, &tmp);
        ++mnTotalCells;
        return true;
    }

    // new row
    RBN_s0097_6f90* inserted;
    RowTreeInsertCD(&inserted, &row, (void*)value);
    FmtExtra tmp;
    ((int*)&tmp)[0] = col;
    ((int*)&tmp)[1] = col;
    ((void**)((byte*)&tmp + 8))[0] = *(void**)value;
    RBN_s0097_6f90* inner;
    FmtInsertLeaf((FmtTree_s0097_6f90*)((RowNode_s0097_6f90*)inserted)->row, &inner, &col, &tmp);
    ++mnTotalCells;
    return true;
}

// @ 0x009770e0
WinGrid_s0097_6f90* WinGrid_s0097_6f90::Ctor(void* a2, void* a3)
{
    (void)a2; (void)a3;
    *(void**)(B(this)) = (void*)0x1442f10;
    *(void**)(B(this) + 4) = (void*)0x1442df0;
    *(void**)(B(this) + 0x20c) = (void*)0x1442bd0;
    return this;
}

// @ 0x00977600
void WinGrid_s0097_6f90::Dtor(unsigned flags)
{
    *(void**)(B(this)) = (void*)0x1442f10;
    *(void**)(B(this) + 4) = (void*)0x1442df0;
    *(void**)(B(this) + 0x20c) = (void*)0x1442bd0;
    RecalcAll(this);
    if (flags & 1)
        EaFree(this);
}

// @ 0x009777c0
bool WinGrid_s0097_6f90::Shutdown()
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

// @ 0x00977830
bool WinGrid_s0097_6f90::SetDefaultTextColorByColumns(uint index, int start, int count, uint color)
{
    if (index >= 8)
        return false;

    bool ok = true;
    int end = start + count;
    for (int col = start; col < end; ++col) {
        FmtTree_s0097_6f90* fmt = &mFmtRow;

        // lower_bound on the outer row map for row==0
        byte* rn = B(fmt->anchor.parent);
        RBN_s0097_6f90* cand = &fmt->anchor;
        while (rn) {
            if (((RowNode_s0097_6f90*)rn)->key < 0) {
                rn = *(byte**)rn;
            } else {
                cand = (RBN_s0097_6f90*)rn;
                rn = *(byte**)(rn + 4);
            }
        }
        if (cand == &fmt->anchor || ((RowNode_s0097_6f90*)cand)->key > 0)
            cand = &fmt->anchor;

        if (cand != &fmt->anchor) {
            RowNode_s0097_6f90* rnode = (RowNode_s0097_6f90*)cand;
            // inner lower_bound for `col`
            byte* in = B(((TreeHdr_s0097_6f90*)rnode->row)->anchor.parent);
            RBN_s0097_6f90* icand = (RBN_s0097_6f90*)(rnode->row + 4);
            while (in) {
                if (((ColNode_s0097_6f90*)in)->key < col) {
                    in = *(byte**)in;
                } else {
                    icand = (RBN_s0097_6f90*)in;
                    in = *(byte**)(in + 4);
                }
            }
            if (icand == (RBN_s0097_6f90*)(rnode->row + 0x1c) || col < ((ColNode_s0097_6f90*)icand)->key)
                icand = (RBN_s0097_6f90*)(rnode->row + 0x1c);

            if (icand != (RBN_s0097_6f90*)(rnode->row + 0x1c)) {
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

// @ 0x00977970
bool EA::UTFWinControls::WinGrid::SetDefaultTextColorByRows(unsigned int index, unsigned int start, int count, int color)
{
    return SetDefaultTextColorByColumns(index, start, count, color);
}

// @ 0x00977ab0
bool EA::UTFWinControls::WinGrid::SetDefaultAlignmentByColumns(int index, int start, int count, int value)
{
    return SetDefaultTextColorByColumns(index, start, count, value);
}

// @ 0x00977be0
bool EA::UTFWinControls::WinGrid::SetDefaultAlignmentByRows(int index, int start, int count, int value)
{
    return SetDefaultTextColorByColumns(index, start, count, value);
}

// @ 0x00977d10
bool WinGrid_s0097_6f90::SetColumnWidth(int start, int count, float width)
{
    if (width < 0.0f)
        width = 0.0f;

    bool ok = true;
    int end = start + count;
    for (int col = start; col < end; ++col) {
        FmtTree_s0097_6f90* fmt = &mFmtRow;

        byte* rn = B(fmt->anchor.parent);
        RBN_s0097_6f90* cand = &fmt->anchor;
        while (rn) {
            if (((RowNode_s0097_6f90*)rn)->key < 0) {
                rn = *(byte**)rn;
            } else {
                cand = (RBN_s0097_6f90*)rn;
                rn = *(byte**)(rn + 4);
            }
        }
        if (cand == &fmt->anchor || ((RowNode_s0097_6f90*)cand)->key > 0)
            cand = &fmt->anchor;

        if (cand != &fmt->anchor) {
            RowNode_s0097_6f90* rnode = (RowNode_s0097_6f90*)cand;
            byte* in = B(((TreeHdr_s0097_6f90*)rnode->row)->anchor.parent);
            RBN_s0097_6f90* icand = (RBN_s0097_6f90*)(rnode->row + 4);
            while (in) {
                if (((ColNode_s0097_6f90*)in)->key < col) {
                    in = *(byte**)in;
                } else {
                    icand = (RBN_s0097_6f90*)in;
                    in = *(byte**)(in + 4);
                }
            }
            if (icand == (RBN_s0097_6f90*)(rnode->row + 0x1c) || col < ((ColNode_s0097_6f90*)icand)->key)
                icand = (RBN_s0097_6f90*)(rnode->row + 0x1c);

            if (icand != (RBN_s0097_6f90*)(rnode->row + 0x1c)) {
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

// @ 0x00979bc0
bool WinGrid_s0097_9bc0::CopyCellData(int srcCol, int srcRow, int dstCol, int dstRow, bool deep)
{
    if (!IFACE(this)->IsCellUsed(srcCol, srcRow))
        return false;
    if (srcCol == dstCol && srcRow == dstRow)
        return true;
    CellData_s0097_9bc0* old = 0;
    if (!IFACE(this)->IsCellUsed(dstCol, dstRow)) {
        if (!deep)
            IFACE(this)->EraseCell(srcCol, srcRow);
        return true;
    }
    if (deep) {
        if (mCells.GetCellPtr(srcCol, srcRow, (void***)&old))
            old = *(CellData_s0097_9bc0**)old;
    } else {
        mCells.RemoveCell(srcCol, srcRow, (void**)&old);
    }
    if (old == 0) {
        IFACE(this)->EraseCell(dstCol, dstRow);
        return true;
    }
    CellData_s0097_9bc0* cell = 0;
    if (mCells.GetCellPtr(dstCol, dstRow, (void***)&cell))
        cell = *(CellData_s0097_9bc0**)cell;
    else {
        cell = (CellData_s0097_9bc0*)EAAllocate(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
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
float WinGrid_s0097_9bc0::GetColumnWidthInternal(int colArg)
{
    int col = colArg;
    CellFormatExtra_s0097_9bc0* fmt;
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
float WinGrid_s0097_9bc0::GetRowHeightInternal(int row)
{
    float h = mnRowGridThickness;
    int nRows = mnRowCount;
    if (nRows != 0 && nRows != -1)
        h = mfVisibleColumnWidth / (float)nRows;
    CellFormatExtra_s0097_9bc0* fmt;
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

// @ 0x0097b110
namespace Gr {
bool WinGridIface_s0097_b110::ScrollCellsVertically(int delta)
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
        void* sub = Window_s0097_b110(this);
        ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
    }
    return true;
}
}  // namespace Gr

// @ 0x0097b230
namespace Gr {
bool WinGridIface_s0097_b110::ScrollCellsHorizontally(int delta)
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
        void* sub = Window_s0097_b110(this);
        ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
    }
    return true;
}
}  // namespace Gr

// @ 0x0097b350
namespace Gr {
bool WinGridIface_s0097_b110::CopyColumns(int srcStart, int dstStart, int count, int bVal)
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
        WString_s0097_b110* s = mColumnHeadings.Index(&srcKey);
        WString_s0097_b110* d = mColumnHeadings.Index(&dstKey);
        if (s != d)
            d->assign(s->mpData, s->mnSize);
        if (bVal == 1)
            mColumnHeadings.EraseKey(&srcKey);

        if (cur == last) {
            mbDirty = true;
            void* sub = Window_s0097_b110(this);
            ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
            return true;
        }
        cur += step;
    }
}
}  // namespace Gr

// @ 0x0097b630
namespace Gr {
bool WinGridIface_s0097_b110::CopyRows(int srcStart, int dstStart, int count, int bVal)
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
        WString_s0097_b110* s = mRowHeadings.Index(&srcKey);
        WString_s0097_b110* d = mRowHeadings.Index(&dstKey);
        if (s != d)
            d->assign(s->mpData, s->mnSize);
        if (bVal == 1)
            mRowHeadings.EraseKey(&srcKey);

        if (cur == last) {
            mbDirty = true;
            void* sub = Window_s0097_b110(this);
            ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
            return true;
        }
        cur += step;
    }
}
}  // namespace Gr

// @ 0x0097b910
namespace Gr {
bool WinGridIface_s0097_b110::GetCellRect(int col, int row, RectT<float>* out)
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
}  // namespace Gr

// @ 0x0097ba60
namespace Gr {
void WinGridIface_s0097_b110::ResizeColumnToFitCellWindows(int col, int count)
{
    bool changed = false;
    if (count == 0)
        return;

    for (int n = count; n != 0; --n, ++col) {
        float maxW = -1.0f;

        ColIter_s0097_b110 it;
        mCells.GetRowCountForCol(&it, col);
        while (it.mpNode != 0) {
            CellData_s0097_b110* cell = *(CellData_s0097_b110**)((char*)it.mpNode + 4);
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
                CellFormatExtra_s0097_b110* fmt = (CellFormatExtra_s0097_b110*)in->value;
                if (fmt->mfWidth == -1.0f || maxW > fmt->mfWidth) {
                    fmt->mfWidth = maxW;
                    changed = true;
                }
                continue;
            }
        }

        // Create a fresh CellFormatExtra for (col, 0) and insert it.
        CellFormatExtra_s0097_b110 fmt = {};
        fmt.mfWidth = maxW;
        changed = true;
        mColFormat.InsertCell(col, 0, &fmt, 0);
    }

    if (!changed)
        return;

    Base(this)->SetSizeCachedActualForRow(0, 0x7fffffff, -1.0f);
    mbDirty = true;
    void* sub = Window_s0097_b110(this);
    ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
}
}  // namespace Gr

// @ 0x0097bc80
namespace Gr {
bool WinGrid_s0097_b110::RecalculateAll()
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

// @ 0x0097bfb0
namespace Gr {
bool WinGrid_s0097_bfb0::MakeRoom(int col, int row, int amount, int dir)
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
}  // namespace Gr

// @ 0x0097c4f0
namespace Gr {
bool WinGrid_s0097_bfb0::MakeRoomForRow(int row, int amount, int dir)
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
}  // namespace Gr

// @ 0x0097c580
namespace Gr {
bool WinGrid_s0097_bfb0::MakeRoomForColumn(int col, int amount, int dir)
{
    if (dir == 0)
        dir = 2;
    else if (dir != 1 && dir != 2 && dir != 4)
        return false;

    RectT<int> r;
    if (!((bool(__thiscall*)(void*, RectT<int>*))GVT((char*)this + 0x20c, 0xc4 / 4))((char*)this + 0x20c, &r))
        return true;

    RBNode_s0097_bfb0* anchor = (RBNode_s0097_bfb0*)((char*)&mCells + 4);
    for (int row = r.top; row <= r.bottom; ++row) {
        RBNode_s0097_bfb0* best = anchor;
        RBNode_s0097_bfb0* n = anchor->parent;
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
}  // namespace Gr

// @ 0x0097c630
namespace Gr {
float WinGridIface_s0097_bfb0::GetColumnWidth(int start, int count)
{
    float sum = 0.0f;
    if (count > 0) {
        WinGrid_s0097_bfb0* base = Base_s0097_bfb0(this);
        do {
            --count;
            sum = base->GetColumnWidthInternal(start) + sum;
            ++start;
        } while (count > 0);
    }
    return sum;
}
}  // namespace Gr

// @ 0x0097c680
namespace Gr {
float WinGridIface_s0097_bfb0::GetRowHeight(int start, int count)
{
    float sum = 0.0f;
    if (count > 0) {
        WinGrid_s0097_bfb0* base = Base_s0097_bfb0(this);
        do {
            --count;
            sum = base->GetRowHeightInternal(start) + sum;
            ++start;
        } while (count > 0);
    }
    return sum;
}
}  // namespace Gr

// @ 0x0097c6d0
namespace Gr {
bool WinGrid_s0097_bfb0::Init()
{
    if (((WindowStub*)this)->Initialize())
        return RecalculateAll();
    return false;
}
}  // namespace Gr

// @ 0x0097c6f0
namespace Gr {
bool WinGrid_s0097_bfb0::OnTick()
{
    if (mbDirty)
        RecalculateAll();
    return false;
}
}  // namespace Gr

// @ 0x0097c710
namespace Gr {
bool WinGridIface_s0097_bfb0::DeleteColumns(int start, int count, int dir)
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
                Base_s0097_bfb0(this)->DisposeOfCellData(p->col, p->row, p->cell, 1);
        }
        EAFree(buf);
    }
    mCells.RemoveCol(start, count);

    switch (dir) {
    case 1:  Base_s0097_bfb0(this)->SetSizeCachedActualForColumn(start, 1, -1.0f);          break;
    case 2:  Base_s0097_bfb0(this)->SetSizeCachedActualForColumn(start, 0x7fffffff, -1.0f); break;
    case 4:  Base_s0097_bfb0(this)->SetSizeCachedActualForColumn(0, start + 1, -1.0f);      break;
    }
    if (dir == 2 || dir == 4)
        Base_s0097_bfb0(this)->MakeRoomForColumn(start, -count, dir);
    MarkDirtyIface(this);
    return true;
}
}  // namespace Gr

// @ 0x0097c8c0
namespace Gr {
bool WinGridIface_s0097_bfb0::DeleteRows(int start, int count, int dir)
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
                Base_s0097_bfb0(this)->DisposeOfCellData(p->col, p->row, p->cell, 1);
        }
        EAFree(buf);
    }
    mCells.RemoveRow(start, count);

    switch (dir) {
    case 1:  Base_s0097_bfb0(this)->SetSizeCachedActualForRow(start, 1, -1.0f);          break;
    case 3:  Base_s0097_bfb0(this)->SetSizeCachedActualForRow(start, 0x7fffffff, -1.0f); break;
    case 5:  Base_s0097_bfb0(this)->SetSizeCachedActualForRow(0, start + 1, -1.0f);      break;
    }
    if (dir == 3 || dir == 5)
        Base_s0097_bfb0(this)->MakeRoomForRow(start, -count, dir);
    MarkDirtyIface(this);
    return true;
}
}  // namespace Gr

// @ 0x0097ca70
namespace Gr {
bool WinGridIface_s0097_bfb0::MakeCellVisible(int col, int row)
{
    if (mbDirty)
        Base_s0097_bfb0(this)->RecalculateAll();

    if (!((bool(__thiscall*)(void*, int, int))GVT(this, 0x184 / 4))(this, col, row)) {
        ((void(__thiscall*)(void*, int))GVT(this, 0x78 / 4))(this, row - mnFirstVisibleRow);
        if (!((bool(__thiscall*)(void*, int, int))GVT(this, 0x184 / 4))(this, col, row))
            ((void(__thiscall*)(void*, int))GVT(this, 0x7c / 4))(this, col - mnFirstVisibleCol);
    }
    return true;
}
}  // namespace Gr

// @ 0x0097cae0
namespace Gr {
bool WinGridIface_s0097_bfb0::SetCellTextValue(int col, int row, const wchar_t* text, void* font, int dir, bool flag)
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
        CellData_s0097_bfb0* cd = (CellData_s0097_bfb0*)EAAllocate(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
        if (cd != 0) {
            cd->mType = 2;
            cd->mCol = col;
            cd->mRow = row;
            cd->mpWindow = textObj;
            cd->mpText = 0;
            cd->pad14 = 0;
            cd->pad18 = 0;
            Base_s0097_bfb0(this)->MakeRoom(col, row, 1, dir);
            mCells.InsertCell(col, row, (void**)&cd, 0);
        }
    }

    MarkDirtyIface(this);
    mLastCellCol = col;
    mLastCellRow = row;
    return true;
}
}  // namespace Gr

// @ 0x0097cd10
namespace Gr {
bool WinGridIface_s0097_bfb0::SetCellImage(int col, int row, void* image, int dir)
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
        CellData_s0097_bfb0* cd = (CellData_s0097_bfb0*)EAAllocate(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
        if (cd != 0) {
            cd->mType = 4;
            cd->mCol = col;
            cd->mRow = row;
            cd->mpWindow = image;
            cd->mpText = 0;
            cd->pad14 = 0;
            cd->pad18 = 0;
            ((void(__thiscall*)(void*))GVT(image, 0))(image);
            Base_s0097_bfb0(this)->MakeRoom(col, row, 1, dir);
            mCells.InsertCell(col, row, (void**)&cd, 0);
        }
        MarkDirtyIface(this);
    }

    mLastCellCol = col;
    mLastCellRow = row;
    return true;
}
}  // namespace Gr

// @ 0x0097cea0
namespace Gr {
bool WinGridIface::SetCellWindow(int colIn, int rowIn, void* w, bool b1, bool b2, int flag)
{
    if (flag == 0) flag = 1;
    if (((bool(__thiscall*)(void*, void*, int, int, int))GVT(this, 0x1b8 / 4))(this, w, 0, 0, 0))
        return false;
    int col = colIn, row = rowIn;
    {
    int mn, mx;
    if (col == 0x7fffffff) {
        bool skipToRow = false;
        if (row == 0x7fffffff) {
            col = mCells.GetMaxUsedColAndRow(&mx);
            if (col == (int)0x80000000) { col = 0; skipToRow = true; }
            else if (col != 0x7fffffff) skipToRow = true;
        }
        if (!skipToRow) {
            if (!mCells.GetMinMaxUsedColForRow(row, &mn, &mx)) col = 0;
            else col = mx + 1;
        }
    }
    if (row == 0x7fffffff) {
        if (!mCells.GetMinMaxUsedRowForCol(col, &mn, &mx)) row = 0;
        else row = mx + 1;
    }
    }
    if (!((bool(__thiscall*)(void*, int, int))GVT(this, 0xd4 / 4))(this, col, row)) {
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);
        return false;
    }
    if (w == 0) {
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);
        mLastRow = row;
        mLastCol = col;
        return true;
    }
    CellData_s0097_cea0* cell = 0;
    CellData_s0097_cea0* n = (CellData_s0097_cea0*)ea_new(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
    if (n) {
        n->pad10 = 0;
        n->pad14 = 0;
        n->mFlags = 0;
        n->mType = 1;
        n->mCol = col;
        n->mRow = row;
        n->mpWindow = w;
        cell = n;
        if (b1) n->mFlags |= 1;
        if (b2) n->mFlags |= 2;
        WinGridMain* wg = (WinGridMain*)((char*)this - 0x20c);
        wg->SetupCell(col, row, 1, flag);
        mCells.InsertCell(col, row, &cell, 0);
        wg->InitCellWindow(col, row, w, b1, b2);
    }
    mbDirty = true;
    void* sub = (char*)this - 0x208;
    ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
    mLastRow = row;
    mLastCol = col;
    return true;
}
}  // namespace Gr

// @ 0x0097d080
void WinGridRefreshThunk::Refresh()
{ ((WinGridBase*)((char*)this - 0x20c))->RefreshImpl(); }
