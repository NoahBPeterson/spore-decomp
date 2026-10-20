// Slice s00973dd0: EA::UTFWinControls::WinGrid cell/selection APIs + eastl rbtree instantiations.
// MSVC 2008 SP1 (cl 15.00), /O2.  All offsets read from retail disassembly; types are self-contained stubs.
// ecx = IWinGrid subobject for the Get*/Set* cell APIs; ecx = WinGrid for OnKeyDown/DoWindowRemoval/
// PlaceAllCellWindows.  IWinGrid == WinGrid+0x20c, so (IWinGrid*)this - 0x208 == WinGrid+4.
#include "types.h"
#include <string.h>

#define FLD(T, p, off) (*(T*)((char*)(p) + (off)))

struct RBNode { RBNode* right; RBNode* left; RBNode* parent; int color; };

void    __cdecl RBTreeInsert(RBNode*, RBNode*, RBNode*, int);              // 0x9216a0
RBNode* __cdecl RBTreeIncrement(RBNode*);                                  // 0x921580
RBNode* __cdecl RBTreeDecrement(const RBNode*);                            // 0x9215c0
void    __cdecl RBTreeErase(RBNode*, RBNode*);                             // 0x921880
void*   __cdecl EAlloc(unsigned, const char*, int, int, const char*, int);// 0xf473a0
void    __cdecl EFree(void*);                                              // 0xf47380
RBNode* __stdcall CreateNodeCopy(const RBNode*, RBNode*);                  // 0x972e30
RBNode* __stdcall CreateNodeCopy40(const RBNode*, RBNode*);                // 0x972dd0
struct ComparatorStr { int fn(const wchar_t* s); };   // 0x614950, ecx = CellData.pCellData
extern void* g_serTypeTable[];                                             // 0x154eea0

#define EA_ALLOC(sz) EAlloc(sz, "EASTL", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)

struct V28 { int f[7]; };
struct V40 { int f[16]; };
struct V0c { int f[3]; };

struct RBTree {
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

struct SparseMatrix {
    RBTree t;
    int  GetMinUsedColAndRow(int* pRow);
    int  GetMaxUsedColAndRow(int* pRow);
    bool GetCellPtr(int col, int row, void*** out);
};

struct CellFormat {
    unsigned int nTextStyle;      // 0x00
    unsigned int nColor[8];       // 0x04..0x24
    char nWrapping;               // 0x24
    char nHAlignment;             // 0x25
    char nVAlignment;             // 0x26
    char field27;                 // 0x27
    unsigned int nBorder;         // 0x28
    unsigned int nBorderColor;    // 0x2c
};                                // 0x30
struct CellFormatExtra : CellFormat {
    float nSizeDefault;           // 0x30
    float nSizeCachedActual;      // 0x34
};

struct CellData {
    int   nCellType;              // 0x00
    int   nColumn;                // 0x04
    int   nRow;                   // 0x08
    void* pCellData;              // 0x0c
    CellFormat* pCellFormat;      // 0x10
    void* pExtraData;             // 0x14
    unsigned int nCellFlags;      // 0x18
};

struct CellCoordinates { int nColumn; int nRow; };
struct Rect { int left, top, right, bottom; };

// ---- virtual interface stubs -------------------------------------------------
struct VGrid {                        // ecx = IWinGrid (= WinGrid+0x20c)
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33();
    virtual void s0x88(int);
    virtual void s0x8c(int);
    virtual void s0x90(int, int);
    virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40();
    virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44();
    virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48();
    virtual void s0xc4(int*);
};

struct VSelf {                        // ecx = IWinGrid
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
    virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
    virtual void p40(); virtual void p41(); virtual void p42();
    virtual void s0xac(int, int, int);
    virtual bool s0xb0(int, int);
    virtual void s0xb4();
};

struct VWin {                         // ecx = WinGrid+4 (CustomWindow)
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
    virtual void s0x90();
    virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40();
    virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44();
    virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48();
    virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52();
    virtual void p53(); virtual void p54(); virtual void p55();
    virtual void s0xe0(void*);
};

struct VGridCf {                      // ecx = IWinGrid
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
    virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
    virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43();
    virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47();
    virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51();
    virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55();
    virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59();
    virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63();
    virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67();
    virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71();
    virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75();
    virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79();
    virtual bool s0x140(int, CellFormatExtra**);
    virtual bool s0x144(int, CellFormatExtra**);
};

struct VImg {                         // ecx = arbitrary object
    virtual void s0();
};

struct Alloc {                        // eastl allocator interface
    virtual void* allocate(unsigned size, int align);
};

struct HatIter { void* node; };
struct HatTable { HatIter* find(HatIter* out, const unsigned& key); };   // 0xa3b2c0

// external WinGrid methods (0x9720a0 and 0x970f30..0x970fb0) are declared in the WinGrid struct below.

// ---- eastl rbtree<...> insert/copy helpers ----------------------------------
// @ 0x973dd0
void RBTree::DoInsertValueImpl_1c(RBNode** __restrict out, RBNode* parent, const V28* value, char force)
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

// @ 0x973e60
void RBTree::DoInsertValueImpl_40(RBNode** __restrict out, RBNode* parent, const V40* value, char force)
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

// @ 0x973ef0
void RBTree::DoInsertValueImpl_0c(RBNode** __restrict out, RBNode* parent, const V0c* value, char force)
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

// @ 0x973f80
RBNode* RBTree::DoCopySubtree_40(const RBNode* src, RBNode* parent)
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

// @ 0x974050
RBNode* RBTree::DoCopySubtree_0c(const RBNode* src, RBNode* parent)
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

// ---- property serializer helper ---------------------------------------------
// @ 0x974110
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

// ---- WinGrid key handling ---------------------------------------------------
struct WinGrid {
    bool OnKeyDown(int, unsigned, unsigned);
    void DoArrowKey(unsigned, unsigned);
    void DoWindowRemoval(int nRow, int nCol, void* pWindow);
    void PlaceAllCellWindows();
    void PlaceCellWindow(int, int, void*, bool, bool);   // 0x9720a0
    void kF30();                                         // 0x970f30
    void kF60();                                         // 0x970f60
    void kF80();                                         // 0x970f80
    void kFb0();                                         // 0x970fb0
};

// @ 0x9741c0
bool WinGrid::OnKeyDown(int a1, unsigned key, unsigned flags)
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

// ---- IWinGrid cell/selection APIs -------------------------------------------
struct IWinGrid {
    int  GetSelectionCount();
    bool GetSelection(CellCoordinates* out, int* count);
    bool SetSelection(int col, int row);
    bool GetCellUsedRange(Rect* rect);
    bool GetCellType(int col, int row, int* out);
    bool GetCellFormat(int col, int row, CellFormat* out);
    bool GetColCellFormatExtra(int col, CellFormatExtra** out);
    bool GetRowCellFormatExtra(int row, CellFormatExtra** out);
    bool GetCellTextValue(int col, int row, void** out);
    bool GetCellImage(int col, int row, void** out);
    bool GetCellWindow(int col, int row, void** out);
    int  GetCellExtraData(int col, int row);
};

// @ 0x9743e0
int IWinGrid::GetSelectionCount()
{
    RBNode* head = (RBNode*)((char*)this + 0xa8);
    int n = 0;
    for (RBNode* p = head->right; p != head; p = p->right)
        n++;
    return n;
}

// @ 0x974400
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

// @ 0x974460
bool IWinGrid::SetSelection(int col, int row)
{
    if (FLD(int, this, 0xa4) > 0) {
        bool skip = false;
        if (((VSelf*)this)->s0xb0(col, row)) {
            RBNode* head = (RBNode*)((char*)this + 0xa8);
            int n = 0;
            if (head->right != head) {
                RBNode* p = head->right;
                do { p = p->right; n++; } while (p != head);
                if (n == 1) skip = true;
            }
        }
        if (!skip) {
            ((VSelf*)this)->s0xb4();
            ((VSelf*)this)->s0xac(col, row, 1);
            ((VWin*)((char*)this - 0x208))->s0x90();
            FLD(int, this, 0x190) = 0;
            FLD(int, this, 0x194) = -1;
            FLD(int, this, 0x198) = -1;
            return true;
        }
    }
    return false;
}

// @ 0x974510
bool IWinGrid::GetCellUsedRange(Rect* rect)
{
    SparseMatrix* m = (SparseMatrix*)((char*)this + 0x114);
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

// @ 0x9745b0
bool IWinGrid::GetCellType(int col, int row, int* out)
{
    SparseMatrix* m = (SparseMatrix*)((char*)this + 0x114);
    void** p = 0;
    if (m->GetCellPtr(col, row, &p))
        *out = ((CellData*)*p)->nCellType;
    return p != 0;
}

static __forceinline void MergeFormat(CellFormat* d, const CellFormat* s)
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

// @ 0x9745f0
bool IWinGrid::GetCellFormat(int col, int row, CellFormat* out)
{
    IWinGrid* pThis = this;
    void** cell = 0;
    CellFormatExtra* ex = 0;
    memcpy(out, (char*)pThis + 0x144, sizeof(CellFormat));
    if (((VGridCf*)pThis)->s0x144(row, &ex) && ex)
        MergeFormat(out, ex);
    if (((VGridCf*)pThis)->s0x140(col, &ex) && ex)
        MergeFormat(out, ex);
    if (((SparseMatrix*)((char*)pThis + 0x114))->GetCellPtr(col, row, &cell) && cell) {
        CellFormat* f = ((CellData*)*cell)->pCellFormat;
        if (f) MergeFormat(out, f);
    }
    return true;
}

// @ 0x974860
bool IWinGrid::GetColCellFormatExtra(int col, CellFormatExtra** out)
{
    SparseMatrix* m = (SparseMatrix*)((char*)this + 0xb4);
    if (!m->GetCellPtr(col, 0, (void***)out)) return false;
    CellFormatExtra* e = *out;
    bool any = e->nBorder == 0 || e->nHAlignment == 0
            || e->nSizeCachedActual == -1.0f || e->nSizeDefault == -1.0f
            || e->nTextStyle == 0 || e->nWrapping == -1 || e->nVAlignment == 0;
    return !any;
}

// @ 0x9748f0
bool IWinGrid::GetRowCellFormatExtra(int row, CellFormatExtra** out)
{
    SparseMatrix* m = (SparseMatrix*)((char*)this + 0xe4);
    if (!m->GetCellPtr(0, row, (void***)out)) return false;
    CellFormatExtra* e = *out;
    bool any = e->nBorder == 0 || e->nHAlignment == 0
            || e->nSizeCachedActual == -1.0f || e->nSizeDefault == -1.0f
            || e->nTextStyle == 0 || e->nWrapping == -1 || e->nVAlignment == 0;
    return !any;
}

// @ 0x974980
bool IWinGrid::GetCellTextValue(int col, int row, void** out)
{
    SparseMatrix* m = (SparseMatrix*)((char*)this + 0x114);
    void** p;
    if (m->GetCellPtr(col, row, &p) && ((CellData*)*p)->nCellType == 2
        && ((CellData*)*p)->pCellData) {
        *out = *(void**)((CellData*)*p)->pCellData;
        return true;
    }
    return false;
}

// @ 0x9749d0
bool IWinGrid::GetCellImage(int col, int row, void** out)
{
    SparseMatrix* m = (SparseMatrix*)((char*)this + 0x114);
    void** p;
    if (m->GetCellPtr(col, row, &p) && ((CellData*)*p)->nCellType == 4) {
        void* img = ((CellData*)*p)->pCellData;
        *out = img;
        if (img) ((VImg*)img)->s0();
        return true;
    }
    return false;
}

// @ 0x974a20
bool IWinGrid::GetCellWindow(int col, int row, void** out)
{
    SparseMatrix* m = (SparseMatrix*)((char*)this + 0x114);
    void** p;
    if (m->GetCellPtr(col, row, &p) && ((CellData*)*p)->nCellType == 1) {
        *out = ((CellData*)*p)->pCellData;
        return true;
    }
    return false;
}

// @ 0x974bf0
int IWinGrid::GetCellExtraData(int col, int row)
{
    SparseMatrix* m = (SparseMatrix*)((char*)this + 0x114);
    void** p;
    if (m->GetCellPtr(col, row, &p) && *p)
        return (int)((CellData*)*p)->pExtraData;
    return 0;
}

// @ 0x974a60
void WinGrid::DoWindowRemoval(int nRow, int nCol, void* pWindow)
{
    if (!pWindow) return;
    CellData key;
    key.nCellType = 1;
    key.nColumn = nCol;
    key.nRow = nRow;
    key.pCellData = pWindow;
    key.pCellFormat = 0;
    key.pExtraData = 0;
    key.nCellFlags = 0;
    RBTree* tree = (RBTree*)((char*)this + 0x380);
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

static inline RBNode* FindInt(RBTree* t, int key)
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

// @ 0x974b00
void WinGrid::PlaceAllCellWindows()
{
    RBTree* list = (RBTree*)((char*)this + 0x380);
    RBNode* end = &list->anchor;
    for (RBNode* n = end->left; n != end; n = RBTreeIncrement(n)) {
        if (FLD(int, n, 0x10) != 1) continue;
        int nCol = FLD(int, n, 0x14);
        int nRow = FLD(int, n, 0x18);
        RBTree* outer = (RBTree*)((char*)this + 0x320);
        RBNode* on = FindInt(outer, nRow);
        if (on == &outer->anchor) continue;
        RBTree* inner = (RBTree*)((char*)on + 0x18);
        RBNode* in = FindInt(inner, nCol);
        if (in == &inner->anchor) continue;
        void* cell = FLD(void*, in, 0x18);
        if (!cell) continue;
        void* w = FLD(void*, cell, 0xc);
        if (!w) continue;
        unsigned fl = FLD(unsigned, cell, 0x18);
        PlaceCellWindow(FLD(int, cell, 4), FLD(int, cell, 8), w, fl & 1, (fl >> 1) & 1);
    }
}

// @ 0x974c30
int __cdecl Comparator(CellData* a, CellData* b)
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
