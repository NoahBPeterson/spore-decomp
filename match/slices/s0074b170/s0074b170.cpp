// Slice s0074b170: cModelWorld load-queue / draw-list helpers (~0x0074b170-0x0074c020).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar float moves, EH prologs present).
#include "../../include/types.h"
#include <new>

static inline void** VT(void* p) { return *(void***)p; }

extern "C" void __cdecl eastl_dealloc(void*);
extern "C" void* __cdecl eastl_alloc(uint32_t size, const char* name, int a, int b, const char* file, int line);

// ---------------------------------------------------------------------------
// @ 0x0074B310  vector<T>::DoInsertValue (element size 0x1c, EH)
// ---------------------------------------------------------------------------
struct T1c {
    uint32_t b[7];                 // 0x1c bytes
    T1c(const T1c&);
};
extern "C" void __cdecl FUN_00747980(const T1c* v);   // grow path

struct Vec1c {
    char pad[0x18];
    T1c* end;      // +0x18
    char pad2[4];
    T1c* cap;      // +0x20
    void DoInsert(const T1c* v);
};

void Vec1c::DoInsert(const T1c* val)
{
    T1c* e = end;
    if ((char*)e + 0x1c == (char*)cap) {
        FUN_00747980(val);
    } else {
        end = (T1c*)((char*)e + 0x1c);
        if (e)
            new (e) T1c(*val);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0074B490  heap-swap loop (element 8 bytes, float key at +4)
// ---------------------------------------------------------------------------
extern "C" void __cdecl FUN_00748010(void*, void*, void*);
extern "C" void __cdecl FUN_00748060(void*, void*, void*);
extern "C" void __cdecl FUN_00745e00(void*, int, int, int, uint32_t, uint32_t, void*);

void heap_loop_b490(void* a, void* b, void* c, void* d)
{
    FUN_00748010(a, b, d);
    char* p = (char*)b;
    while (p < (char*)c) {
        float key = *(float*)(p + 4);
        if (key > *(float*)((char*)a + 4)) {
            uint32_t k = *(uint32_t*)(p + 4);
            uint32_t o = *(uint32_t*)p;
            uint32_t k0 = *(uint32_t*)a;
            uint32_t k1 = *(uint32_t*)((char*)a + 4);
            *(uint32_t*)p = k0;
            *(uint32_t*)(p + 4) = k1;
            FUN_00745e00(a, 0, (int)((char*)b - (char*)a) >> 3, 0, o, k, d);
        }
        p += 8;
    }
    FUN_00748060(a, b, d);
}

// ---------------------------------------------------------------------------
// @ 0x0074B510  heap-swap loop (comparator reversed)
// ---------------------------------------------------------------------------
extern "C" void __cdecl FUN_007480c0(void*, void*, void*);
extern "C" void __cdecl FUN_00748110(void*, void*, void*);
extern "C" void __cdecl FUN_00745e80(void*, int, int, int, uint32_t, uint32_t, void*);

void heap_loop_b510(void* a, void* b, void* c, void* d)
{
    FUN_007480c0(a, b, d);
    char* p = (char*)b;
    while (p < (char*)c) {
        if (*(float*)((char*)a + 4) > *(float*)(p + 4)) {
            uint32_t k = *(uint32_t*)(p + 4);
            uint32_t o = *(uint32_t*)p;
            uint32_t k0 = *(uint32_t*)a;
            uint32_t k1 = *(uint32_t*)((char*)a + 4);
            *(uint32_t*)p = k0;
            *(uint32_t*)(p + 4) = k1;
            FUN_00745e80(a, 0, (int)((char*)b - (char*)a) >> 3, 0, o, k, d);
        }
        p += 8;
    }
    FUN_00748110(a, b, d);
}

// ---------------------------------------------------------------------------
// @ 0x0074B690  SP::cModelWorld::SetInWorld
// ---------------------------------------------------------------------------
struct ListNode { ListNode* prev; ListNode* next; char pad[4]; uint32_t flags; };

namespace SP {
struct cModelWorld {
    char pad0[0x1c];
    char mWorldType;       // +0x1c
    char pad1[0x1a0 - 0x1d];
    ListNode  mListA;      // +0x19c anchor area
    char pad2[4];
    ListNode  mListB;      // +0x1a4 anchor area
    void AddAttachments(ListNode* n);
    void ShutdownModel(ListNode* n);
    void SetInWorld(ListNode* n, bool b);
};
}

void SP::cModelWorld::SetInWorld(ListNode* n, bool b)
{
    if (mWorldType == 0)
        return;
    if (((n->flags >> 0xf) & 1) == (uint32_t)b)
        return;
    ListNode* node = (ListNode*)((char*)n - 8);
    ListNode* prev = node->prev;
    ListNode* next = node->next;
    next->prev = prev;
    prev->next = next;
    node->prev = 0;
    node->next = 0;
    if (b) {
        node->next = mListA.next;
        node->prev = &mListA;
        mListA.next = node;
        node->next->prev = node;
        AddAttachments(node);
    } else {
        node->next = mListB.next;
        node->prev = &mListB;
        mListB.next = node;
        node->next->prev = node;
        ShutdownModel(node);
    }
    if (b)
        node->flags |= 0x8000;
    else
        node->flags &= 0xffff7fff;
}

// ---------------------------------------------------------------------------
// @ 0x0074B170  cLoadQueue reset/clear   (partial: refcount/list walk stubbed)
// ---------------------------------------------------------------------------
void cloadqueue_b170(void* self)
{
    (void)self;
}

// ---------------------------------------------------------------------------
// @ 0x0074B2B0  cLoadQueue<T...>::~cLoadQueue   (EH, member-array destruction)
// ---------------------------------------------------------------------------
namespace SP {
struct cLoadingModel { uint32_t pad[0x14]; ~cLoadingModel(); };   // 0x50 bytes
struct LoadDeque { ~LoadDeque(); };
struct cLoadQueue {
    char pad[4];
    cLoadingModel arr[8];                       // +4, 0x50 each
    LoadDeque dq;                               // +0x284
    ~cLoadQueue();
};
}
SP::cLoadQueue::~cLoadQueue() {}

// ---------------------------------------------------------------------------
// @ 0x0074B390  eastl::partial_sort<cOccluder*>   (partial)
// ---------------------------------------------------------------------------
void partial_sort_b390(void* a, void* b, void* c, void* cmp)
{
    (void)a; (void)b; (void)c; (void)cmp;
}

// ---------------------------------------------------------------------------
// @ 0x0074B760  SP::cModelWorld::UpdateFromPropList   (partial: 1591B)
// ---------------------------------------------------------------------------
void update_from_proplist_b760(void* self, int* prop)
{
    (void)self; (void)prop;
}

// ---------------------------------------------------------------------------
// @ 0x0074BDA0  slot-list find helper   (partial)
// ---------------------------------------------------------------------------
void list_find_bda0(void* self, void* key)
{
    (void)self; (void)key;
}

// ---------------------------------------------------------------------------
// @ 0x0074BE40  slot-list erase by key   (partial)
// ---------------------------------------------------------------------------
void list_erase_be40(void* self, int* key)
{
    (void)self; (void)key;
}

// ---------------------------------------------------------------------------
// @ 0x0074BF10  vector::insert (element 8B)   (partial: growth path)
// ---------------------------------------------------------------------------
void vec_insert_bf10(void* self, void* pos, void* val)
{
    (void)self; (void)pos; (void)val;
}

// ---------------------------------------------------------------------------
// @ 0x0074C020  vector::insert (element 0x18B)   (partial: growth path)
// ---------------------------------------------------------------------------
void vec_insert_c020(void* self, void* pos, void* val)
{
    (void)self; (void)pos; (void)val;
}
