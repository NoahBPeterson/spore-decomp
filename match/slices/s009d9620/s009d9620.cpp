// s009d9620: gait-group record (0x104 bytes) assign + std::sort machinery (insertion sort, heap helpers)
// for two comparators (by element value / by key word).
#include "types.h"

typedef unsigned int u32;

inline void* operator new(unsigned int, void* p) { return p; }

void __cdecl EastlFree(void* p);   // 0xf47380 operator delete[]
void* __cdecl memcpy(void* d, const void* s, unsigned int n);

static inline void FreeArr(void* p)
{
    if (p && ((int*)p)[-1])
        EastlFree(p);
}

struct Item;
struct PtrVec {
    u32* b;
    u32* e;
    u32* c;
    u32 alloc;
    void PushSlow(u32* pos, u32* val);      // 0x9d6ef0
};

struct Item {
    u32 key;
    PtrVec v;
    u32 pad14;
    float f18, f1c, f20;
    uint8_t b24;
    float f28, f2c, f30, f34;
    Item() {}
    Item(const Item& o);                    // 0x9d7dd0
    ~Item() { FreeArr(v.b); }
};

struct ItemVec {
    Item* b;
    Item* e;
    Item* c;
    u32 alloc;
    ItemVec& operator=(const ItemVec& o);   // 0x9d8fd0
    void DestroyRange(Item* first, Item* last);    // 0x9c15f0 / 0x9d8e20 range destroy
    void DoInsertValue(Item* pos, const Item& v);  // 0x9d8e80
};

struct FloatVec {
    int* b;
    int* e;
    int* c;
    u32 alloc;
    u32 pad;
    FloatVec& operator=(const FloatVec& o);        // eastl::vector<float,sp_vector_allocator>::operator=
};

struct S;
struct Owner {
    char pad0[0x24];
    char* arr;        // array of 0x108-byte elements
};

// ---- 0x104-byte record ----
struct S {
    u32 w0[4];
    float wf[14];
    Owner* owner;
    ItemVec items;
    u32 itemsPad;
    float w1[22];
    u32 hw;
    FloatVec idx;
    float w2[13];
    S(const S& o);                      // 0x9d8720
    S& operator=(const S& o);           // 0x9d9620
    ~S()
    {
        FreeArr(idx.b);
        items.DestroyRange(items.b, items.e);
        FreeArr(items.b);
    }
    void FillGroups(void* y);           // 0x9da000
    void SortGroups(u32 unused);        // 0x9da5b0 (ret 4: one unused stack arg)
};

struct LessIdx { bool operator()(S a, S b); };    // 0x9d7840
struct LessWord { bool operator()(S a, S b); };   // 0x9d7920

typedef void (__cdecl *DummyFn)();
struct PredTag { char c; };
u32 __cdecl MakePred(PredTag tag);        // 0x921240
void __cdecl SortGroupsSmall(Item* first, Item* last, u32 pred);   // 0x9d9420
void __cdecl SortGroupsLarge(Item* first, Item* last, u32 pred);   // 0x9d9520

// @ 0x9d9620
S& S::operator=(const S& o)
{
    w0[0] = o.w0[0];
    w0[1] = o.w0[1];
    w0[2] = o.w0[2];
    w0[3] = o.w0[3];
    wf[0] = o.wf[0];
    wf[1] = o.wf[1];
    wf[2] = o.wf[2];
    wf[3] = o.wf[3];
    wf[4] = o.wf[4];
    wf[5] = o.wf[5];
    wf[6] = o.wf[6];
    wf[7] = o.wf[7];
    wf[8] = o.wf[8];
    wf[9] = o.wf[9];
    wf[10] = o.wf[10];
    wf[11] = o.wf[11];
    wf[12] = o.wf[12];
    wf[13] = o.wf[13];
    owner = o.owner;
    items = o.items;
    w1[0] = o.w1[0];
    w1[1] = o.w1[1];
    w1[2] = o.w1[2];
    w1[3] = o.w1[3];
    w1[4] = o.w1[4];
    w1[5] = o.w1[5];
    w1[6] = o.w1[6];
    w1[7] = o.w1[7];
    w1[8] = o.w1[8];
    w1[9] = o.w1[9];
    w1[10] = o.w1[10];
    w1[11] = o.w1[11];
    w1[12] = o.w1[12];
    w1[13] = o.w1[13];
    w1[14] = o.w1[14];
    w1[15] = o.w1[15];
    w1[16] = o.w1[16];
    w1[17] = o.w1[17];
    w1[18] = o.w1[18];
    w1[19] = o.w1[19];
    w1[20] = o.w1[20];
    w1[21] = o.w1[21];
    hw = o.hw;
    idx = o.idx;
    w2[0] = o.w2[0];
    w2[1] = o.w2[1];
    w2[2] = o.w2[2];
    w2[3] = o.w2[3];
    w2[4] = o.w2[4];
    w2[5] = o.w2[5];
    w2[6] = o.w2[6];
    w2[7] = o.w2[7];
    w2[8] = o.w2[8];
    w2[9] = o.w2[9];
    w2[10] = o.w2[10];
    w2[11] = o.w2[11];
    w2[12] = o.w2[12];
    return *this;
}

// @ 0x9d9840
void __cdecl InsertionSortIdx(S* first, S* last)
{
    LessIdx predI;
    if (first != last) {
        for (S* it = first + 1; it != last; ++it) {
            S val(*it);
            S* hole = it;
            while (hole != first) {
                S* prev = hole - 1;
                if (!predI(val, *prev))
                    break;
                *hole = *prev;
                hole = prev;
            }
            *hole = val;
        }
    }
}

// @ 0x9d9970
void __cdecl UnguardedInsertionSortIdx(S* first, S* last)
{
    LessIdx predI;
    for (; first != last; ++first) {
        S val(*first);
        S* hole = first;
        for (;;) {
            S* prev = hole - 1;
            if (!predI(val, *prev))
                break;
            *hole = *prev;
            hole = prev;
        }
        *hole = val;
    }
}

// @ 0x9d9a90
void __cdecl InsertionSortWord(S* first, S* last)
{
    LessWord predW;
    if (first != last) {
        for (S* it = first + 1; it != last; ++it) {
            S val(*it);
            S* hole = it;
            while (hole != first) {
                S* prev = hole - 1;
                if (!predW(val, *prev))
                    break;
                *hole = *prev;
                hole = prev;
            }
            *hole = val;
        }
    }
}

// @ 0x9d9bc0
void __cdecl UnguardedInsertionSortWord(S* first, S* last)
{
    LessWord predW;
    for (; first != last; ++first) {
        S val(*first);
        S* hole = first;
        for (;;) {
            S* prev = hole - 1;
            if (!predW(val, *prev))
                break;
            *hole = *prev;
            hole = prev;
        }
        *hole = val;
    }
}

// @ 0x9d9d60
void __cdecl PushHeapIdx(S* first, int top, int hole, S value)
{
    LessIdx predI;
    int parent = (hole - 1) >> 1;
    while (top < hole && predI(first[parent], value)) {
        first[hole] = first[parent];
        hole = parent;
        parent = (hole - 1) >> 1;
    }
    first[hole] = value;
}

// @ 0x9d9e70
void __cdecl PushHeapWord(S* first, int top, int hole, S value)
{
    LessWord predW;
    int parent = (hole - 1) >> 1;
    while (top < hole && predW(first[parent], value)) {
        first[hole] = first[parent];
        hole = parent;
        parent = (hole - 1) >> 1;
    }
    first[hole] = value;
}

// @ 0x9d9f80
void __cdecl SwapRecords(S* a, S* b)
{
    S tmp(*a);
    *a = *b;
    *b = tmp;
}

// @ 0x9da000
void S::FillGroups(void* y)
{
    int n = idx.e - idx.b;
    items.DestroyRange(items.b, items.e);
    for (int i = 0; i < n; ++i) {
        char* elem = owner->arr + idx.b[i] * 0x108;
        char* ybase = *(char**)((char*)y + 0x2e4);
        u32 ia = *(u32*)(elem + 0x58);
        char* rec = *(char**)(ybase + ia * 700);
        u32 ib = *(u32*)(rec + 0x430);
        Item it;
        it.key = (u32)(ybase + ib * 700);
        it.v.b = 0;
        it.v.c = 0;
        memcpy(0, 0, 0);
        it.v.e = 0;
        it.f18 = 0.0f;
        it.f1c = 0.0f;
        it.f20 = 0.0f;
        it.f34 = 0.0f;
        u32 elemp = (u32)elem;
        Item* f = items.b;
        Item* last = items.e;
        for (; f != last; ++f)
            if (it.key == f->key)
                break;
        if (f == last) {
            it.v.PushSlow(0, &elemp);
            Item* pe = items.e;
            if (pe < items.c) {
                items.e = pe + 1;
                if (pe)
                    new (pe) Item(it);
            } else {
                items.DoInsertValue(pe, it);
            }
        } else {
            PtrVec& pv = f->v;
            u32* pe = pv.e;
            if (pe < pv.c) {
                pv.e = pe + 1;
                if (pe)
                    *pe = elemp;
            } else {
                pv.PushSlow(pe, &elemp);
            }
        }
    }
}

// @ 0x9da170
void __cdecl AdjustHeapIdx(S* first, int top, int len, int hole, S value)
{
    LessIdx predI;
    int child = hole * 2 + 2;
    while (child < len) {
        if (predI(first[child], first[child - 1]))
            --child;
        first[hole] = first[child];
        hole = child;
        child = hole * 2 + 2;
    }
    if (child == len) {
        first[hole] = first[child - 1];
        hole = child - 1;
    }
    PushHeapIdx(first, top, hole, value);
}

// @ 0x9da2d0
void __cdecl AdjustHeapWord(S* first, int top, int len, int hole, S value)
{
    LessWord predW;
    int child = hole * 2 + 2;
    while (child < len) {
        if (predW(first[child], first[child - 1]))
            --child;
        first[hole] = first[child];
        hole = child;
        child = hole * 2 + 2;
    }
    if (child == len) {
        first[hole] = first[child - 1];
        hole = child - 1;
    }
    PushHeapWord(first, top, hole, value);
}

// @ 0x9da430
void __cdecl PopHeapIdx(S* first, S* last)
{
    S val(last[-1]);
    last[-1] = *first;
    AdjustHeapIdx(first, 0, (int)(last - first) - 1, 0, val);
}

// @ 0x9da4f0
void __cdecl PopHeapWord(S* first, S* last)
{
    S val(last[-1]);
    last[-1] = *first;
    AdjustHeapWord(first, 0, (int)(last - first) - 1, 0, val);
}

template <void (__cdecl *F)(Item*, Item*, u32)>
static inline void SortRange(Item* first, Item* last)
{
    F(first, last, MakePred(PredTag()));
}
static inline int ISize(const ItemVec& v) { return v.e - v.b; }
static inline u32 FSize(const FloatVec& v) { return v.e - v.b; }

// @ 0x9da5b0
void S::SortGroups(u32)
{
    if (FSize(idx) == 3 && ISize(items) == 2)
        SortRange<SortGroupsSmall>(items.b, items.e);
    else
        SortRange<SortGroupsLarge>(items.b, items.e);
}
