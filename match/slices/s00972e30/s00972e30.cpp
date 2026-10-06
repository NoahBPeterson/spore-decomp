// Slice s00972e30: EA::UTFWinControls::WinGrid helpers and SparseMatrix<> / eastl::list instances.
// MSVC 2008 SP1, /O2 /arch:SSE.
// Retail layout: the IWinGrid subobject (vptr, mGridFlags at +4) sits at WinGrid+0x20c; WinGrid::Set*Cell*
// methods run with ecx = that subobject, while DoArrowKey/DoCellWindowMove run with ecx = WinGrid.
// SparseMatrix<T> = eastl::map<int, eastl::map<int, T>>: a tree object {alloc, anchor(right,left,parent,color), size}.
#include "types.h"

#define FLD(T, p, off) (*(T*)((char*)(p) + (off)))
// Generic interface stub: virtual slot at byte offset N is named sN (only the slots used here are typed).
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

// @ 0x972e30
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

struct Msg { int a, b; unsigned id; int tmp; int c, d; int* pCur; };

struct WinGridView {
    void SetGridFlags(unsigned flags);                 // 0x973100
    bool GetCellIsSelected(int col, int row);          // 0x973160
    void ClearSelection();                             // 0x973200
    bool IsWindowACellWindow(int id, int ptr, int* o1, int* o2);   // 0x973270
};
struct WinGrid {
    void DoArrowKey(int vk, bool bExtend);             // 0x972e90
    void DoCellWindowMove(int* msg);                   // 0x973330
    bool SetScrollBarDrawableVertical(void* p);        // 0x973390
    bool SetScrollBarDrawableHorizontal(void* p);      // 0x973410
    bool AddScrollBar(bool vert, bool horz);           // 0x973490
    void RemoveScrollBar(bool a, bool b);              // 0x972600
    void SetScrollBarValues();                         // 0x9726c0
};
struct ListHead { void Clear(); };                     // 0x972d30 (eastl::list<CellCoordinates>::clear)

// @ 0x972e90
void WinGrid::DoArrowKey(int vk, bool bExtend)
{
    int curCol = 0, curRow = 0;
    int vis[4] = {0, 0, 0, 0};
    void* view = (char*)this + 0x20c;
    VCALL1(void, view, 0xc4, vis);
    RBNode* sel = (RBNode*)((char*)this + 0x2b4);
    if (sel->right != sel) {                 // list not empty: start from the first selected cell
        RBNode* first = (RBNode*)sel->left;
        curCol = FLD(int, first, 8);
        curRow = FLD(int, first, 0xc);
    }
    switch (vk) {
    case 0x25:
        if (curCol <= 0) return;
        curCol--;
        break;
    case 0x26:
        if (curRow <= 0) return;
        curRow--;
        break;
    case 0x27: {
        int t = FLD(int, this, 0x264);
        unsigned bit = 0;
        if ((t != -1 && t != 0) || !(FLD(unsigned, this, 0x210) & 0x8000)) {
            bit = FLD(unsigned, this, 0x210) & 0x8000;
            if (!bit) t = vis[2] + 1;
            if (curCol >= t - 1) {
                if (bit) return;
                break;
            }
        }
        curCol++;
        break;
    }
    case 0x28: {
        int t = FLD(int, this, 0x268);
        unsigned bit = 0;
        if ((t != -1 && t != 0) || !(FLD(unsigned, this, 0x210) & 0x10000)) {
            bit = FLD(unsigned, this, 0x210) & 0x10000;
            if (!bit) t = vis[3] + 1;
            if (curRow >= t - 1) {
                if (bit) return;
                break;
            }
        }
        curRow++;
        break;
    }
    default:
        return;
    }
    if (sel->right != sel && !bExtend) ((ListHead*)sel)->Clear();
    VCALL3(void, view, 0xac, curCol, curRow, 1);
    Msg msg;
    msg.id = 0x9a1552d2;
    msg.tmp = FLD(int, this, 0x84);
    if (msg.tmp == 0) msg.tmp = FLD(int, this, 0x80);
    msg.pCur = &curCol;
    void* win = (char*)this + 4;
    VCALL1(void, win, 0x114, &msg);
    switch (vk - 0x25) {
    case 0:
        if (curCol < FLD(int, this, 0x254)) VCALL1(void, view, 0x88, curCol);
        break;
    case 1:
        if (curRow < FLD(int, this, 0x258)) VCALL1(void, view, 0x8c, curRow);
        break;
    case 2: {
        float vc = FLD(float, this, 0x25c);
        if ((float)curCol >= (float)FLD(int, this, 0x254) + vc)
            VCALL1(void, view, 0x88, curCol - (int)vc + 1);
        break;
    }
    case 3: {
        float vr = FLD(float, this, 0x260);
        if ((float)curRow >= (float)FLD(int, this, 0x258) + vr)
            VCALL1(void, view, 0x8c, curRow - (int)vr + 1);
        break;
    }
    }
    SetScrollBarValues();
    FLD(char, this, 0x214) = 1;
    VCALL2(void, win, 0x7c, 8, 1);
}

// @ 0x973100
void WinGridView::SetGridFlags(unsigned flags)
{
    if (flags != FLD(unsigned, this, 4)) {
        unsigned diff = FLD(unsigned, this, 4) ^ flags;
        FLD(unsigned, this, 4) = flags;
        if (diff & 6) {
            WinGrid* g = (WinGrid*)((char*)this - 0x20c);
            g->RemoveScrollBar(!((flags >> 2) & 1), !((flags >> 1) & 1));
            VObj* win = (VObj*)((char*)g + 4);
            win->s0x7c(8, FLD(char, g, 0x214) = 1);
        }
    }
}

// @ 0x973160
bool WinGridView::GetCellIsSelected(int col, int row)
{
    RBNode* head = (RBNode*)((char*)this + 0xa8);
    switch (FLD(int, this, 0xa0)) {
    case 0:
        for (RBNode* n = head->right; n != head; n = n->right)
            if (col == FLD(int, n, 8)) return true;
        return false;
    case 1:
        for (RBNode* n = head->right; n != head; n = n->right)
            if (row == FLD(int, n, 0xc)) return true;
        return false;
    case 2:
        for (RBNode* n = head->right; n != head; n = n->right)
            if (col == FLD(int, n, 8) && row == FLD(int, n, 0xc)) return true;
        return false;
    }
    return false;
}

// @ 0x973200
void WinGridView::ClearSelection()
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

// @ 0x973270
bool WinGridView::IsWindowACellWindow(int id, int ptr, int* o1, int* o2)
{
    RBNode* end = (RBNode*)((char*)this + 0x178);
    RBNode* n = ((RBNode*)end)->left;
    if (id != 0) {
        for (n = end->left; n != end; n = RBTreeIncrement(n)) {
            if (id == FLD(int, n, 0x1c)) {
                if (o1) *o1 = FLD(int, n, 0x14);
                if (o2) *o2 = FLD(int, n, 0x18);
                return true;
            }
        }
        return false;
    }
    for (n = end->left; n != end; n = RBTreeIncrement(n)) {
        void* w = FLD(void*, n, 0x1c);
        if (w && VCALL0(int, w, 0x1c) == ptr) {
            if (o1) *o1 = FLD(int, n, 0x14);
            if (o2) *o2 = FLD(int, n, 0x18);
            return true;
        }
    }
    return false;
}

// @ 0x973330
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

static inline void* AsDrawable(void* d) { return d ? VCALL1(void*, d, 0xc, 0x6ec581fd) : 0; }

// @ 0x973390
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

// @ 0x973410
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

// ---- AddScrollBar ----
void* __cdecl WinScrollbar_CreateDef(int orientation, int a, int w, int h);   // 0x9839b0
struct AutoRefCount { void* p; void Assign(void* v); };                         // 0xb5f950
void* __cdecl interface_cast_IDrawable(void* ref);                              // 0x972db0

// @ 0x973490
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

// ---- SparseMatrix member functions ----
struct ColIterA { SparseMatrix* mat; OutNode* out; int* cur; ColIterA& operator++(); };
struct ColIterB { SparseMatrix* mat; OutNode* out; RBNode* in;  ColIterB& operator++(); };

// @ 0x973640
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

// @ 0x9736c0
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

// @ 0x973740
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

// @ 0x9737a0
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

// @ 0x973800
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
            OutNode* m = End();
            if (m != Begin()) {
                do {
                    m = (OutNode*)RBTreeDecrement(&m->b);
                    if (InnerFind(&m->inner, key) != (InNode*)&m->inner.anchor) {
                        *pMax = m->f14;
                        return true;
                    }
                } while (m != Begin());
            }
            return true;
        }
    }
    return r;
}

// @ 0x973930
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

// @ 0x973980
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

// @ 0x9739e0
int SparseMatrix::GetCountForKey(int key)
{
    int count = 0;
    for (OutNode* n = Begin(); n != End(); n = (OutNode*)RBTreeIncrement(&n->b)) {
        if (InnerFind(&n->inner, key) != (InNode*)&n->inner.anchor) count++;
    }
    return count;
}

// @ 0x973a40
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

// @ 0x973a90
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

// @ 0x973b00
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

// @ 0x973b90
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

// @ 0x973c30
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

// @ 0x973cc0
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

// ---- eastl::list<CellCoordinates> range helpers ----
struct CellCoord { int col, row; CellCoord(const CellCoord& o) : col(o.col), row(o.row) {} };
struct ListNode { ListNode* next; ListNode* prev; CellCoord value; };
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

struct ListIter {
    ListNode* mpNode;
    ListIter& operator++() { mpNode = mpNode->next; return *this; }
    bool operator!=(const ListIter& o) const { return mpNode != o.mpNode; }
};

// @ 0x973d10   (eastl::list::erase(first, last))
static inline ListIter ListErase1(ListIter position)
{
    ++position;
    ListNode* n = position.mpNode->prev;
    n->prev->next = n->next;
    n->next->prev = n->prev;
    operator_delete_ea(n);
    return position;
}
ListIter* __stdcall ListErase(ListIter* ret, ListIter first, ListIter last)
{
    while (first != last) first = ListErase1(first);
    *ret = last;
    return ret;
}

// @ 0x973d60   (eastl::list::insert(pos, first, last))
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
void __stdcall ListInsertRange(ListNode* pos, ListIter first, ListIter last, int tag)
{
    for (; first != last; ++first)
        DoInsertValue(pos, first.mpNode->value);
}
