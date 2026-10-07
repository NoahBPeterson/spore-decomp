// s009d75b0: Anim/gait helpers: gait-element init, std::sort machinery for 0x108-byte elements and for
// 0x104-byte "gait group" records (copy/dtor/insertion sort), item vector assign/copy, pointer-array sorts.
#include "types.h"

typedef unsigned int u32;
struct CmpObj { u32 v; };

inline void* operator new(unsigned int, void* p) { return p; }

// EASTL allocator / free (0xf473a0 / 0xf47380) and memcpy thunk (0x11e0744)
void* __cdecl EastlAlloc(u32 size, const char* name, int flags, u32 align, const char* file, int line);
void __cdecl EastlFree(void* p);
void* __cdecl memcpy(void* d, const void* s, unsigned int n);

static inline void FreeArr(void* p)
{
    if (p && ((int*)p)[-1])
        EastlFree(p);
}

struct V3 {
    float x, y, z;
    V3(const V3& o) { x = o.x; y = o.y; z = o.z; }
};
struct V4 {
    float x, y, z, w;
    V4(const V4& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};

// ---- 0x108-byte element (gait/anim record) ----
struct TElem {
    u32 raw[0x42];
    TElem();                                            // 0x9ce5e0
    void Init(void* a, V3 p, V4 q);                     // 0x9cddf0
    TElem(const TElem& o);                              // 0x9ce790
};

struct TVec {
    TElem* b;
    TElem* e;
    TElem* c;
    void DoInsertValue(TElem* pos, const TElem& v);     // 0x9d7000
};

struct TOwner {
    char pad0[0x24];
    TVec v;
    int AddElem(void* a, const V3* p3, const V4* p4);   // 0x9d7d10
};

// ---- 0x38-byte item with an owned pointer array ----
struct Item;
struct ItemVec;

struct PtrVec {
    u32* b;
    u32* e;
    u32* c;
    u32 alloc;
    u32* DoAllocate(u32 n, u32* first, u32* last);      // 0x9d7560
    void DoAllocateN(u32 n, void* a);                   // 0x9d69b0
    PtrVec& operator=(const PtrVec& o);                 // 0x9d7bb0
};

struct Item {
    u32 key;
    PtrVec v;
    u32 pad14;
    float f18, f1c, f20;
    uint8_t b24;
    float f28, f2c, f30, f34;
    Item& operator=(const Item& o);                     // 0x9d7e50
    Item(const Item& o);                                // 0x9d7dd0
};

void* __cdecl UninitCopyOut(Item** out, Item* first, Item* last, Item* dst, u32 tag);   // 0x9d7ea0
void __cdecl SortRangeA(void* first, void* last, u32 pred);   // 0x9d7a40
void __cdecl SortRangeB(void* first, void* last, u32 pred);   // 0x9d79d0
void __cdecl SortRangeC(void* first, void* last, u32 pred);   // 0x9d7ab0
struct EmptyPred {};
u32 __cdecl MakePred(EmptyPred tag);                             // 0x921240

struct ItemVec {
    Item* b;
    Item* e;
    Item* c;
    u32 alloc;
    void DoAllocateN(u32 n, void* a);                   // 0x9d6a10
    ItemVec* CopyInit(ItemVec* src);                    // 0x9d86c0
    void DestroyRange(Item* first, Item* last);         // 0x9c15f0
};

struct FloatVec {
    int* b;
    int* e;
    int* c;
    u32 alloc;
    u32 pad;
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
};

struct LessIdx { bool operator()(S a, S b); };    // 0x9d7840
struct LessWord { bool operator()(S a, S b); };   // 0x9d7920

// ---- sort/insertion helper entry points used by SortElems ----
void __cdecl IntroLoop(TElem* first, TElem* last, int depth, CmpObj cmp);     // 0x9d7480
void __cdecl InsertionSort(TElem* first, TElem* last, CmpObj cmp);            // 0x9cea00
void __cdecl UnguardedInsertionSort(TElem* first, TElem* last, CmpObj cmp);   // 0x9ceab0

extern const float g_01485720;
extern const float g_01550b24, g_01550b28, g_01550b2c, g_01550b30, g_01550b34, g_01550b38, g_01550b3c;
extern const float g_01550b44, g_01550b48, g_01550b4c, g_01550b50, g_01550b54, g_01550b58, g_01550b5c;
extern const float g_01550b60, g_01550b64, g_01550b68, g_01471064;
extern const float g_0166c024, g_0166c028, g_0166c02c, g_0166c038, g_0166c03c, g_0166c040, g_0166c044;

template <class T> static inline T& at(void* p, int off) { return *(T*)((char*)p + off); }

// @ 0x9d75b0
struct GaitElemInit {
    char raw[0x108];
    GaitElemInit* Init();
};
GaitElemInit* GaitElemInit::Init()
{
    char* p = (char*)this;
    at<float>(p, 0xb0) = 0.0f;
    at<float>(p, 0xac) = 0.0f;
    at<float>(p, 0xa8) = 0.0f;
    at<float>(p, 0xe8) = 0.0f;
    at<float>(p, 0xe4) = 0.0f;
    at<float>(p, 0xe0) = 0.0f;
    at<float>(p, 0xf4) = 0.0f;
    at<float>(p, 0xf0) = 0.0f;
    at<float>(p, 0xec) = 0.0f;
    at<float>(p, 0x100) = 0.0f;
    at<float>(p, 0xfc) = 0.0f;
    at<float>(p, 0xf8) = 0.0f;
    at<int>(p, 0x4c) = 0;
    at<int>(p, 0x50) = 0;
    at<int>(p, 0x54) = 0;
    at<int>(p, 0xbc) = 0;
    at<int>(p, 0xc0) = 0;
    at<int>(p, 0xc4) = 0;
    at<float>(p, 0xd0) = 1.0f;
    at<float>(p, 0x9c) = 0.0f;
    at<int>(p, 0) = -1;
    at<float>(p, 0x88) = g_01550b24;
    at<float>(p, 0x90) = g_0166c024;
    at<float>(p, 0xd4) = g_0166c024;
    at<float>(p, 0x94) = g_0166c028;
    at<float>(p, 0xd8) = g_0166c028;
    at<float>(p, 0x98) = g_0166c02c;
    at<float>(p, 0x60) = 1.0f;
    at<float>(p, 0x64) = g_01550b28;
    at<float>(p, 0x68) = g_01550b2c;
    at<float>(p, 0x6c) = g_01550b30;
    at<float>(p, 0x70) = g_01550b34;
    at<float>(p, 0x74) = g_01550b38;
    at<float>(p, 0x78) = g_01550b3c;
    at<float>(p, 0x7c) = 0.0f;
    at<float>(p, 0x80) = g_01471064;
    at<float>(p, 0x84) = 1.0f;
    at<float>(p, 0xa4) = 1.0f;
    at<float>(p, 0xa8) = 0.0f;
    at<float>(p, 0xac) = 0.0f;
    at<float>(p, 0xb0) = 0.0f;
    at<float>(p, 0xb4) = 0.0f;
    at<float>(p, 0x8c) = 1.0f;
    at<float>(p, 0xa0) = 0.0f;
    at<float>(p, 0xdc) = 0.0f;
    at<float>(p, 0x10) = g_01550b44;
    at<float>(p, 0x14) = g_0166c038;
    at<float>(p, 0x18) = g_01550b48;
    at<float>(p, 0x1c) = g_01550b4c;
    at<float>(p, 0x20) = g_0166c03c;
    at<float>(p, 0x24) = g_0166c040;
    at<float>(p, 0x28) = g_01550b50;
    at<float>(p, 0x2c) = g_01550b54;
    at<float>(p, 0x30) = g_01550b58;
    at<float>(p, 0x34) = g_01550b5c;
    at<float>(p, 0x38) = g_0166c044;
    at<float>(p, 0x3c) = g_01550b60;
    at<float>(p, 0x40) = g_01550b64;
    at<float>(p, 0x44) = g_01550b68;
    at<float>(p, 0xf8) = 0.0f;
    at<float>(p, 0xfc) = 0.0f;
    at<float>(p, 0x100) = 0.0f;
    at<int>(p, 0xc) = -1;
    at<int>(p, 4) = -1;
    at<int>(p, 8) = -1;
    at<int>(p, 0xb8) = -1;
    return this;
}

// @ 0x9d7840
bool LessIdx::operator()(S a, S b)
{
    float fa = *(float*)(a.owner->arr + *a.idx.b * 0x108 + 0xac);
    float fb = *(float*)(b.owner->arr + *b.idx.b * 0x108 + 0xac);
    return fa > fb;
}

// @ 0x9d7920
bool LessWord::operator()(S a, S b)
{
    return a.hw < b.hw;
}

// @ 0x9d7b20
void __cdecl SortElems(TElem* first, TElem* last, CmpObj cmp)
{
    if (first != last) {
        int n = last - first;
        int m = n;
        int lg = 0;
        while (m != 0) {
            m >>= 1;
            ++lg;
        }
        IntroLoop(first, last, lg * 2 - 2, cmp);
        if (n > 28) {
            InsertionSort(first, first + 28, cmp);
            UnguardedInsertionSort(first + 28, last, cmp);
        } else {
            InsertionSort(first, last, cmp);
        }
    }
}

// @ 0x9d7bb0
PtrVec& PtrVec::operator=(const PtrVec& o)
{
    if (&o != this) {
        u32* oe = o.e;
        u32* ob = o.b;
        u32* tb = b;
        u32 n = ((char*)oe - (char*)ob) >> 2;
        u32 capn = ((char*)c - (char*)tb) >> 2;
        if (n > capn) {
            u32* p = DoAllocate(n, ob, oe);
            FreeArr(b);
            b = p;
            c = p + n;
            e = p + n;
            return *this;
        }
        u32 cur = ((char*)e - (char*)tb) >> 2;
        if (cur < n) {
            memcpy(tb, ob, cur * 4);
            u32 cur2 = ((char*)e - (char*)b) >> 2;
            u32* src = (u32*)((char*)ob + cur2 * 4);
            memcpy(e, src, (char*)oe - (char*)src);
            e = b + n;
        } else {
            memcpy(tb, ob, (char*)oe - (char*)ob);
            e = b + n;
        }
    }
    return *this;
}

// @ 0x9d7c80
S* __cdecl DestroyRecords(S* first, S* last, S* dst)
{
    if (first != last) {
        do {
            FreeArr(first->idx.b);
            Item* end = first->items.e;
            Item* it = first->items.b;
            for (; it < end; ++it)
                FreeArr(it->v.b);
            FreeArr(first->items.b);
            ++first;
            ++dst;
        } while (first != last);
        return dst;
    }
    return dst;
}

// @ 0x9d7d10
int TOwner::AddElem(void* a, const V3* p3, const V4* p4)
{
    TVec& vec = v;
    int idx = vec.e - vec.b;
    TElem t;
    t.Init(a, *p3, *p4);
    TElem* pe = vec.e;
    if (pe < vec.c) {
        vec.e = pe + 1;
        if (pe)
            new (pe) TElem(t);
    } else {
        vec.DoInsertValue(pe, t);
    }
    return idx;
}

// @ 0x9d7dd0
Item::Item(const Item& o)
{
    key = o.key;
    PtrVec& dv = v;
    dv.DoAllocateN(o.v.e - o.v.b, (void*)&o.v.alloc);
    int nbytes = (char*)o.v.e - (char*)o.v.b;
    u32* r = (u32*)memcpy(dv.b, o.v.b, nbytes);
    dv.e = r + (nbytes >> 2);
    f18 = o.f18;
    f1c = o.f1c;
    f20 = o.f20;
    b24 = o.b24;
    f28 = o.f28;
    f2c = o.f2c;
    f30 = o.f30;
    f34 = o.f34;
}

// @ 0x9d7e50
Item& Item::operator=(const Item& o)
{
    key = o.key;
    v = o.v;
    f18 = o.f18;
    f1c = o.f1c;
    f20 = o.f20;
    b24 = o.b24;
    f28 = o.f28;
    f2c = o.f2c;
    f30 = o.f30;
    f34 = o.f34;
    return *this;
}

// @ 0x9d7f20
Item* __cdecl CopyItems(Item* first, Item* last, Item* dst)
{
    if (first != last) {
        do {
            *dst = *first;
            ++first;
            ++dst;
        } while (first != last);
        return dst;
    }
    return dst;
}

// @ 0x9d7fa0
Item* __cdecl CopyItemsBackward(Item* first, Item* last, Item* dst)
{
    if (last != first) {
        do {
            --last;
            --dst;
            *dst = *last;
        } while (last != first);
        return dst;
    }
    return dst;
}

// 3-element sort of a pointer array (Item::v), keyed on floats of the pointed-to elements.
struct GaitSorter {
    char pad[0x48];
    int dummy;
    void Sort3(PtrVec* vec, float a, float b);                                         // 0x9d8020
    void Sort4(PtrVec* vec, float a, float b, float c, float d, float e, float f);     // 0x9d81f0
    void SortAll();                                                                    // 0x9d84f0
};

static inline float PX(u32 p) { return *(float*)(p + 0x7c); }
static inline float PZ(u32 p) { return *(float*)(p + 0x80); }

// @ 0x9d8020
void GaitSorter::Sort3(PtrVec* vec, float a, float b)
{
    if (a < 1e-06f || 100.0f < b / a) {
        SortRangeA(vec->b, vec->e, MakePred(EmptyPred()));
    } else if (b < 1e-06f || 100.0f < a / b) {
        u32* p = vec->b;
        u32 t = p[0];
        if (PX(p[1]) > PX(t)) {
            p[0] = p[1];
            p[1] = t;
        }
        p = vec->b;
        t = p[0];
        if (PX(p[2]) > PX(t)) {
            p[0] = p[2];
            p[2] = t;
        }
        p = vec->b;
        t = p[1];
        if (PX(t) > PX(p[2])) {
            p[1] = p[2];
            p[2] = t;
        }
    } else {
        u32* p = vec->b;
        float mean = ((PZ(p[0]) + PZ(p[1])) + PZ(p[2])) * 0.33333334f;
        int below = 0;
        if (PZ(p[0]) < mean)
            ++below;
        if (PZ(p[1]) < mean)
            ++below;
        if (PZ(p[2]) < mean)
            ++below;
        if (below > 1) {
            int i = 0;
            u32* q = p;
            do {
                if (PZ(*q) > mean) {
                    u32 t = p[2];
                    p[2] = p[i];
                    p[i] = t;
                    break;
                }
                ++i;
                ++q;
            } while (i < 2);
            p = vec->b;
            u32 t = p[0];
            if (PX(t) > PX(p[1])) {
                p[0] = p[1];
                p[1] = t;
            }
        } else {
            int i = 0;
            u32* q = p;
            do {
                if (mean > PZ(*q)) {
                    u32 t = p[2];
                    p[2] = p[i];
                    p[i] = t;
                    break;
                }
                ++i;
                ++q;
            } while (i < 2);
            p = vec->b;
            u32 t = p[0];
            if (PX(t) > PX(p[1])) {
                p[0] = p[1];
                p[1] = t;
            }
        }
    }
}

static inline float Sq2(float dx, float dz) { return dz * dz + dx * dx; }

static inline void SortA(u32* b, u32* e, EmptyPred pr) { SortRangeA(b, e, MakePred(pr)); }
static inline void SortB(u32* b, u32* e, EmptyPred pr) { SortRangeB(b, e, MakePred(pr)); }

// @ 0x9d81f0
void GaitSorter::Sort4(PtrVec* vec, float a, float b, float c, float d, float e, float f)
{
    if (a == 0.0f) {
        SortA(vec->b, vec->e, EmptyPred());
        return;
    }
    if (b == 0.0f) {
        SortB(vec->b, vec->e, EmptyPred());
        return;
    }
    u32* p = vec->b;
    if (Sq2(PX(p[0]) - d, PZ(p[0]) - f) > Sq2(PX(p[1]) - d, PZ(p[1]) - f)) {
        u32 t = p[0];
        p[0] = p[1];
        p[1] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[0]) - d, PZ(p[0]) - f) > Sq2(PX(p[2]) - d, PZ(p[2]) - f)) {
        u32 t = p[0];
        p[0] = p[2];
        p[2] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[0]) - d, PZ(p[0]) - f) > Sq2(PX(p[3]) - d, PZ(p[3]) - f)) {
        u32 t = p[0];
        p[0] = p[3];
        p[3] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[1]) - c, PZ(p[1]) - f) > Sq2(PX(p[2]) - c, PZ(p[2]) - f)) {
        u32 t = p[1];
        p[1] = p[2];
        p[2] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[1]) - c, PZ(p[1]) - f) > Sq2(PX(p[3]) - c, PZ(p[3]) - f)) {
        u32 t = p[1];
        p[1] = p[3];
        p[3] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[2]) - d, PZ(p[2]) - e) > Sq2(PX(p[3]) - d, PZ(p[3]) - e)) {
        u32 t = p[2];
        p[2] = p[3];
        p[3] = t;
    }
}

struct ItemOps {
    void Query(float* a, float* b, float* c, float* d, float* e, float* f);   // 0x9cfdc0
    void Update();                                                            // 0x9d0b10
};

// @ 0x9d84f0
void __fastcall GaitSorter_SortAll(GaitSorter* self)
{
    ItemVec* items = (ItemVec*)((char*)self + 0x4c);
    int count = items->e - items->b;
    if (count > 0) {
        int off = 0;
        do {
            Item* it = (Item*)((char*)items->b + off);
            int n = it->v.e - it->v.b;
            float fa, fb, f0, f1, f2, f3;
            ((ItemOps*)it)->Query(&fa, &fb, &f0, &f1, &f2, &f3);
            ((ItemOps*)it)->Update();
            switch (n) {
            case 0:
            case 1:
                break;
            case 2:
                if (fa > fb)
                    SortRangeB(it->v.b, it->v.e, MakePred(EmptyPred()));
                else
                    SortRangeA(it->v.b, it->v.e, MakePred(EmptyPred()));
                break;
            case 3:
                self->Sort3(&it->v, fa, fb);
                break;
            case 4:
                self->Sort4(&it->v, fa, fb, f0, f1, f2, f3);
                break;
            default:
                SortRangeC(it->v.b, it->v.e, MakePred(EmptyPred()));
                break;
            }
            off += 0x38;
        } while (--count);
    }
}

// @ 0x9d8660
Item* __cdecl AllocCopyItems(u32 n, Item* first, Item* last)
{
    Item* p;
    if (n)
        p = (Item*)EastlAlloc(n * 0x38, "Anim/gait/untagged", 0, 0,
                              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                              0xd1);
    else
        p = 0;
    UninitCopyOut((Item**)&n, first, last, p, n);
    return p;
}

// @ 0x9d86c0
ItemVec* ItemVec::CopyInit(ItemVec* src)
{
    DoAllocateN(src->e - src->b, &src->alloc);
    ItemVec* slot = src;
    UninitCopyOut((Item**)&slot, src->b, src->e, b, (u32)slot);
    e = (Item*)slot;
    return this;
}
