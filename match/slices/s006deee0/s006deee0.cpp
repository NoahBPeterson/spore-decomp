// slice s006deee0: SP::cClusterRect / pointer EASTL sort machinery plus a few
// refcounted-vector helpers (16-byte element with an intrusive pointer at +0xc).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// The heap/insertion primitives that live outside this slice (adjust_heap,
// sort_heap, the pointer-type insertion sorts) are declared extern; their bodies
// are emitted elsewhere.  Only shapes/offsets matter for the calls.
#include "types.h"

typedef unsigned int uint;

extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedExchange(volatile long*, long);

// ---------------------------------------------------------------------------
// SP::cClusterRect, size 0x34 (from the dev PDB)
// ---------------------------------------------------------------------------
namespace SP {

struct cSPVector2 { float x, y; };

struct cClusterRect {
    uint  mStartIndices;   // +0x00
    uint  mEndIndices;     // +0x04
    float mArea;           // +0x08
    uint  mMeshIndex;      // +0x0c
    cSPVector2 mMinUV;     // +0x10
    cSPVector2 mMaxUV;     // +0x18
    cSPVector2 mTexBound;  // +0x20
    float mAreaWeight;     // +0x28
    int   mRectID;         // +0x2c
    float mLinearScale;    // +0x30

    cClusterRect() {}
    cClusterRect(const cClusterRect& o)
        : mStartIndices(o.mStartIndices), mEndIndices(o.mEndIndices), mArea(o.mArea),
          mMeshIndex(o.mMeshIndex), mMinUV(o.mMinUV), mMaxUV(o.mMaxUV), mTexBound(o.mTexBound),
          mAreaWeight(o.mAreaWeight), mRectID(o.mRectID), mLinearScale(o.mLinearScale) {}
};

}  // namespace SP

// The original comparator orders the raw 32-bit pattern of mArea (positive
// float areas, so this is the numeric order).  Keeping mArea a float makes the
// element copies use movss like the original; the cast gives the integer
// compare the original emitted.
struct cRectAreaSort {
    bool operator()(const SP::cClusterRect& a, const SP::cClusterRect& b) const {
        return *(const uint*)&a.mArea > *(const uint*)&b.mArea;
    }
};

inline uint AreaKey(const SP::cClusterRect& r) { return *(const uint*)&r.mArea; }

template <typename T, typename Compare>
const T& Median3(const T& a, const T& b, const T& c, const Compare& compare) {
    if (compare(a, b)) {
        if (compare(b, c)) return b;
        else if (compare(a, c)) return c;
        else return a;
    } else {
        if (compare(a, c)) return a;
        else if (compare(b, c)) return c;
        else return b;
    }
}

// Pointer element with its sort key at +0x04 (the two pointer sorts below).
struct SortKeyObj { uint mPad; uint mKey; };

struct SortKeyGreater {
    bool operator()(const SortKeyObj* a, const SortKeyObj* b) const { return a->mKey > b->mKey; }
};
struct SortKeyLess {
    bool operator()(const SortKeyObj* a, const SortKeyObj* b) const { return a->mKey < b->mKey; }
};

// ---------------------------------------------------------------------------
// 16-byte element: {uint, uint, ushort, ushort, IntrusivePtr} at +0xc
// ---------------------------------------------------------------------------
struct IRefObj {                        // vtable[0]=AddRef, vtable[1]=Release
    virtual void AddRef();
    virtual void Release();
};

struct IntrusiveRef {
    IRefObj* mpObject;                  // +0x0
    IntrusiveRef& operator=(const IntrusiveRef& x) {
        IRefObj* src = x.mpObject;
        IRefObj* old = mpObject;
        if (src != old) {
            if (src)
                src->AddRef();
            mpObject = src;
            if (old)
                old->Release();
        }
        return *this;
    }
};

struct Elem16 {
    uint32_t f0;      // +0x0
    uint32_t f4;      // +0x4
    uint16_t f8;      // +0x8
    uint16_t fa;      // +0xa
    IntrusiveRef ref; // +0xc
};

// ---------------------------------------------------------------------------
// Intrusive object with a refcount at +0x4 and a virtual deleting dtor at
// vtable[0] (called with flag 1).  Used by the 4-byte pointer copy.
// ---------------------------------------------------------------------------
struct RefCountObj {
    virtual void Delete(int flags);
    int mnRefCount;                     // +0x4
};

struct RefPtr {
    RefCountObj* mpObject;              // +0x0
    RefPtr& operator=(const RefPtr& x) {
        RefCountObj* src = x.mpObject;
        RefCountObj* old = mpObject;
        if (src != old) {
            if (src)
                _InterlockedIncrement((volatile long*)&src->mnRefCount);
            mpObject = src;
            if (old) {
                volatile long* p = (volatile long*)&old->mnRefCount;
                long n = _InterlockedDecrement(p);
                if (n == 0) {
                    _InterlockedExchange(p, 1);
                    old->Delete(1);
                }
            }
        }
        return *this;
    }
};

extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedExchange(volatile long*, long);

// ---------------------------------------------------------------------------
// Externals (masked by relocations)
// ---------------------------------------------------------------------------
extern "C" {
void  FreeMem(void* p);                                                  // 0xf47380
void* AllocMem(unsigned n, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
void  AdjustHeapCR(SP::cClusterRect* first, int top, int size, int pos, SP::cClusterRect value, const cRectAreaSort* cmp);  // 0x6dea60
void  SortHeapCR(SP::cClusterRect* first, SP::cClusterRect* last, const cRectAreaSort* cmp);  // 0x6df220
void  InsertionSortCR(SP::cClusterRect* first, SP::cClusterRect* last, const cRectAreaSort* cmp);  // 0x6dede0
void  AdjustHeapKeyGT(SortKeyObj** first, int top, int size, int pos, SortKeyObj* value, const SortKeyGreater* cmp);  // 0x6de980
void  AdjustHeapKeyLT(SortKeyObj** first, int top, int size, int pos, SortKeyObj* value, const SortKeyLess* cmp);  // 0x6de9f0
void  MakeHeapKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater* cmp);       // 0x6df050
void  MakeHeapKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess* cmp);          // 0x6df0e0
void  SortHeapKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater* cmp);       // 0x6df090
void  SortHeapKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess* cmp);          // 0x6df120
void  InsertionSortKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater* cmp);  // 0x6de3a0
void  InsertionSortKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess* cmp);     // 0x6de440
void  InsertionSortSimpleKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater* cmp);  // 0x6de3f0
void  InsertionSortSimpleKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess* cmp);     // 0x6de490
void  Elem16Fill(Elem16* first, Elem16* last, const Elem16* value);                          // 0x6de8f0
void  Elem16MoveBack(Elem16* first, Elem16* last, void* dest, void* destEnd, Elem16* p);     // 0x6de850
void* CopyMem(void* dst, void* src, unsigned n);                                             // 0x6c2b10 / 0x65c750
void  VecPushBackSlow(void* end, const void* value);                                          // 0x6ec4a0
void  GlobalCtor(void* p, const void* v);                                                     // 0x4746c0
}

// ---------------------------------------------------------------------------
// @ 0x006deee0  eastl::Internal::insertion_sort_simple<SP::cClusterRect*,cRectAreaSort>
// ---------------------------------------------------------------------------
void InsertionSortSimpleCR(SP::cClusterRect* first, SP::cClusterRect* last, const cRectAreaSort& compare) {
    for (SP::cClusterRect* current = first; current != last; ++current) {
        SP::cClusterRect* end = current;
        SP::cClusterRect* prev = current;
        const SP::cClusterRect value(*current);
        for (--prev; compare(value, *prev); --end, --prev)
            *end = *prev;
        *end = value;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006defe0  eastl::fill<Elem16*,Elem16>
// ---------------------------------------------------------------------------
void FillElem16(Elem16* first, Elem16* last, const Elem16* value) {
    for (; first != last; ++first)
        *first = *value;
}

// ---------------------------------------------------------------------------
// @ 0x006df170  eastl::make_heap<SP::cClusterRect*,cRectAreaSort>
// ---------------------------------------------------------------------------
void MakeHeapCR(SP::cClusterRect* first, SP::cClusterRect* last, const cRectAreaSort& compare) {
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            AdjustHeapCR(first, parentPosition, heapSize, parentPosition,
                         *(first + parentPosition), &compare);
        } while (parentPosition != 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006df280  Intrusive RefPtr::operator= (4-byte pointer, refcount at +4)
// ---------------------------------------------------------------------------
RefPtr& AssignRefPtr(RefPtr* self, const RefPtr* x) {
    return (*self = *x), *self;
}

// ---------------------------------------------------------------------------
// @ 0x006df2d0  eastl::copy<Elem16*,Elem16*>
// ---------------------------------------------------------------------------
Elem16* CopyElem16(Elem16* first, Elem16* last, Elem16* dest) {
    if (first == last)
        return dest;
    do {
        *dest = *first;
        ++first;
        ++dest;
    } while (first != last);
    return dest;
}

// ---------------------------------------------------------------------------
// @ 0x006df340  eastl::copy_backward<Elem16*,Elem16*>
// ---------------------------------------------------------------------------
Elem16* CopyBackwardElem16(Elem16* first, Elem16* last, Elem16* destEnd) {
    if (first == last)
        return destEnd;
    do {
        --last;
        --destEnd;
        *destEnd = *last;
    } while (last != first);
    return destEnd;
}

// ---------------------------------------------------------------------------
// @ 0x006df3b0  eastl::vector<Elem16,...>::~vector  (this in ecx)
// ---------------------------------------------------------------------------
struct Elem16Vector {
    Elem16* mpBegin;    // +0x00
    Elem16* mpEnd;      // +0x04
    Elem16* mpCapacity; // +0x08
    void*   mpPad;      // +0x0c
    void*   mpInline;   // +0x10
    void Destroy();
};

void Elem16Vector::Destroy() {
    for (Elem16* p = mpBegin; p < mpEnd; ++p) {
        if (p->ref.mpObject)
            p->ref.mpObject->Release();
    }
    if (mpBegin && mpBegin != (Elem16*)mpInline)
        FreeMem(mpBegin);
}

// ---------------------------------------------------------------------------
// @ 0x006df420  eastl::get_partition_ref<SortKeyObj**,SortKeyObj*,SortKeyGreater>
// ---------------------------------------------------------------------------
SortKeyObj** GetPartitionKeyGT(SortKeyObj** first, SortKeyObj** last, SortKeyObj* pivotValue,
                               const SortKeyGreater& compare) {
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        SortKeyObj* temp = *first;
        *first = *last;
        *last = temp;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006df470  eastl::partial_sort<SortKeyObj**,SortKeyGreater>
// ---------------------------------------------------------------------------
void PartialSortKeyGT(SortKeyObj** first, SortKeyObj** middle, SortKeyObj** last,
                      const SortKeyGreater& compare) {
    MakeHeapKeyGT(first, middle, &compare);
    for (SortKeyObj** i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            SortKeyObj* temp = *i;
            *i = *first;
            AdjustHeapKeyGT(first, 0, (int)(middle - first), 0, temp, &compare);
        }
    }
    SortHeapKeyGT(first, middle, &compare);
}

// ---------------------------------------------------------------------------
// @ 0x006df4e0  eastl::get_partition_ref<SortKeyObj**,SortKeyObj*,SortKeyLess>
// ---------------------------------------------------------------------------
SortKeyObj** GetPartitionKeyLT(SortKeyObj** first, SortKeyObj** last, SortKeyObj* pivotValue,
                               const SortKeyLess& compare) {
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        SortKeyObj* temp = *first;
        *first = *last;
        *last = temp;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006df530  eastl::partial_sort<SortKeyObj**,SortKeyLess>
// ---------------------------------------------------------------------------
void PartialSortKeyLT(SortKeyObj** first, SortKeyObj** middle, SortKeyObj** last,
                      const SortKeyLess& compare) {
    MakeHeapKeyLT(first, middle, &compare);
    for (SortKeyObj** i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            SortKeyObj* temp = *i;
            *i = *first;
            AdjustHeapKeyLT(first, 0, (int)(middle - first), 0, temp, &compare);
        }
    }
    SortHeapKeyLT(first, middle, &compare);
}

// ---------------------------------------------------------------------------
// @ 0x006df5a0  eastl::partial_sort<SP::cClusterRect*,cRectAreaSort>
// ---------------------------------------------------------------------------
void PartialSortCR(SP::cClusterRect* first, SP::cClusterRect* middle, SP::cClusterRect* last,
                   const cRectAreaSort& compare) {
    MakeHeapCR(first, middle, compare);
    for (SP::cClusterRect* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const SP::cClusterRect temp(*i);
            *i = *first;
            AdjustHeapCR(first, 0, (int)(middle - first), 0, temp, &compare);
        }
    }
    SortHeapCR(first, middle, &compare);
}

// ---------------------------------------------------------------------------
// @ 0x006df700  eastl::copy<RefPtr*,RefPtr*>
// ---------------------------------------------------------------------------
RefPtr* CopyRefPtr(RefPtr* first, RefPtr* last, RefPtr* dest) {
    if (first == last)
        return dest;
    do {
        *dest = *first;
        ++first;
        ++dest;
    } while (first != last);
    return dest;
}

// ---------------------------------------------------------------------------
// @ 0x006df770  eastl::quick_sort_impl<SortKeyObj**,int,SortKeyGreater>
// ---------------------------------------------------------------------------
void QuickSortImplKeyGT(SortKeyObj** first, SortKeyObj** last, int kRecursionCount,
                        const SortKeyGreater& compare) {
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        SortKeyObj** mid = first + (last - first) / 2;
        SortKeyObj** lastm1 = last - 1;
        SortKeyObj* const& pivot = Median3(*first, *mid, *lastm1, compare);
        SortKeyObj** position = GetPartitionKeyGT(first, last, pivot, compare);
        QuickSortImplKeyGT(position, last, --kRecursionCount, compare);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortKeyGT(first, last, last, compare);
}

// ---------------------------------------------------------------------------
// @ 0x006df830  eastl::quick_sort_impl<SortKeyObj**,int,SortKeyLess>
// ---------------------------------------------------------------------------
void QuickSortImplKeyLT(SortKeyObj** first, SortKeyObj** last, int kRecursionCount,
                        const SortKeyLess& compare) {
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        SortKeyObj** mid = first + (last - first) / 2;
        SortKeyObj** lastm1 = last - 1;
        SortKeyObj* const& pivot = Median3(*first, *mid, *lastm1, compare);
        SortKeyObj** position = GetPartitionKeyLT(first, last, pivot, compare);
        QuickSortImplKeyLT(position, last, --kRecursionCount, compare);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortKeyLT(first, last, last, compare);
}

// ---------------------------------------------------------------------------
// @ 0x006df8f0  eastl::get_partition<SP::cClusterRect*,SP::cClusterRect,cRectAreaSort>
// ---------------------------------------------------------------------------
SP::cClusterRect* GetPartitionCR(SP::cClusterRect* first, SP::cClusterRect* last,
                                 SP::cClusterRect pivotValue, const cRectAreaSort& compare) {
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        const SP::cClusterRect temp(*first);
        *first = *last;
        *last = temp;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006df9d0  destroy range of 0x58-byte records (a pointer at +0x00, a
// second at +0x10 that is left alone)
// ---------------------------------------------------------------------------
struct Elem58 {
    void* mpData;      // +0x00
    uint  mPad[3];     // +0x04
    void* mpInline;    // +0x10
    uint  mPad2[0x11]; // +0x14 .. +0x58
};

void __stdcall DestroyRange58(Elem58* first, Elem58* last) {
    for (; first < last; ++first) {
        void* p = first->mpData;
        if (p && p != first->mpInline)
            FreeMem(p);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006dfa00  eastl::quick_sort<SortKeyObj**,SortKeyGreater>
// ---------------------------------------------------------------------------
void QuickSortKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater& compare) {
    if (first != last) {
        int n = (int)(last - first);
        int k = 0;
        for (int i = n; i != 0; i >>= 1)
            ++k;
        QuickSortImplKeyGT(first, last, k * 2 - 2, compare);
        if (n > 28) {
            InsertionSortKeyGT(first, first + 28, &compare);
            InsertionSortSimpleKeyGT(first + 28, last, &compare);
        } else {
            InsertionSortKeyGT(first, last, &compare);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006dfa80  eastl::quick_sort<SortKeyObj**,SortKeyLess>
// ---------------------------------------------------------------------------
void QuickSortKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess& compare) {
    if (first != last) {
        int n = (int)(last - first);
        int k = 0;
        for (int i = n; i != 0; i >>= 1)
            ++k;
        QuickSortImplKeyLT(first, last, k * 2 - 2, compare);
        if (n > 28) {
            InsertionSortKeyLT(first, first + 28, &compare);
            InsertionSortSimpleKeyLT(first + 28, last, &compare);
        } else {
            InsertionSortKeyLT(first, last, &compare);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006dfb00  eastl::quick_sort_impl<SP::cClusterRect*,int,cRectAreaSort>
// ---------------------------------------------------------------------------
void QuickSortImplCR(SP::cClusterRect* first, SP::cClusterRect* last, int kRecursionCount,
                     const cRectAreaSort& compare) {
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        SP::cClusterRect* mid = first + (last - first) / 2;
        SP::cClusterRect* lastm1 = last - 1;
        const SP::cClusterRect& pivot = Median3(*first, *mid, *lastm1, compare);
        SP::cClusterRect* position = GetPartitionCR(first, last, pivot, compare);
        QuickSortImplCR(position, last, --kRecursionCount, compare);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortCR(first, last, last, compare);
}

// ---------------------------------------------------------------------------
// @ 0x006dfc30  class method: register a cluster and accumulate its area
// ---------------------------------------------------------------------------
void ClusterMapAdd(int* self, int* rect) {
    void* model = *(void**)(self + 6);                       // self+0x18
    if (*(void**)((char*)model + *rect * 0x10 + 4) != 0) {
        int** pEnd = (int**)((char*)self + 0x238);
        int** pCap = (int**)((char*)self + 0x23c);
        int* slot = *pEnd;
        if (*pEnd < *pCap) {
            *pEnd = slot + 1;
            if (slot)
                *slot = (int)rect;
        } else {
            VecPushBackSlow(*pEnd, &rect);
        }
        *(float*)((char*)self + 0x230) += (float)rect[2];
    }
}

// ---------------------------------------------------------------------------
// @ 0x006dfca0  erase a range from an Elem16 vector (returns the insert point)
// ---------------------------------------------------------------------------
int Elem16VecEraseRange(int* self, int dest, int from) {
    Elem16* newEnd = CopyElem16((Elem16*)from, *(Elem16**)(self + 1), (Elem16*)dest);
    uint count = ((uint)*(self + 1) - (uint)newEnd) >> 4;
    if (newEnd < *(Elem16**)(self + 1)) {
        Elem16* p = newEnd;
        uint n = count;
        do {
            if (p->ref.mpObject)
                p->ref.mpObject->Release();
            ++p;
        } while (--n);
    }
    *(int*)(self + 1) = *(int*)(self + 1) + ((from - dest) >> 4) * -0x10;
    return dest;
}

// ---------------------------------------------------------------------------
// @ 0x006dfd00  eastl::quick_sort<SP::cClusterRect*,cRectAreaSort>
// ---------------------------------------------------------------------------
void QuickSortCR(SP::cClusterRect* first, SP::cClusterRect* last, const cRectAreaSort& compare) {
    if (first != last) {
        int n = (int)(last - first);
        int k = 0;
        for (int i = n; i != 0; i >>= 1)
            ++k;
        QuickSortImplCR(first, last, k * 2 - 2, compare);
        if (n > 28) {
            InsertionSortCR(first, first + 28, &compare);
            InsertionSortSimpleCR(first + 28, last, compare);
        } else {
            InsertionSortCR(first, last, &compare);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006dfd90  Elem16 vector DoInsertValues (one value, with growth)
// ---------------------------------------------------------------------------
void Elem16VecInsert(int* self, int position, uint n, Elem16* value) {
    uint space = (uint)((*(Elem16**)(self + 2) - *(Elem16**)(self + 1)) >> 4);
    if (space < n) {
        int size = (*(int*)(self + 1) - *self) >> 4;
        uint newCap = size * 2;
        if (size == 0)
            newCap = 1;
        uint want = size + n;
        if (want < newCap)
            want = newCap;
        Elem16* pNew = 0;
        if (want != 0)
            pNew = (Elem16*)AllocMem(want << 4, "Graphics", 0, 0,
                                     "eastl/allocator.h", 0xd1);
        Elem16* newEnd = CopyElem16((Elem16*)*self, (Elem16*)position, pNew);
        Elem16Fill(newEnd, newEnd + n, value);
        newEnd += n;
        CopyElem16((Elem16*)position, *(Elem16**)(self + 1), newEnd);
        if (*self && *self != *(int*)(self + 4))
            FreeMem((void*)*self);
        *(int*)(self + 1) = (int)(pNew + size + n);
        *self = (int)pNew;
        *(int*)(self + 2) = (int)(pNew + want);
    } else if (n != 0) {
        Elem16 local = *value;
        if (local.ref.mpObject)
            local.ref.mpObject->AddRef();
        int end = *(int*)(self + 1);
        uint tail = (uint)((end - position) >> 4);
        if (n < tail) {
            Elem16* src = (Elem16*)(end - (n << 4));
            Elem16MoveBack((Elem16*)src, (Elem16*)end, (void*)end, (void*)end, (Elem16*)0);
            CopyBackwardElem16((Elem16*)position, src, (Elem16*)end);
            *(int*)(self + 1) += n << 4;
            for (uint i = 0; i < n; ++i)
                *((Elem16*)position + i) = *value;
        } else {
            Elem16* pEnd = (Elem16*)end;
            Elem16Fill(pEnd, pEnd + (n - tail), value);
            *(int*)(self + 1) += (n - tail) << 4;
            Elem16* src = (Elem16*)(*(int*)(self + 1) - (n << 4));
            CopyElem16((Elem16*)position, src, (Elem16*)end);
            *(int*)(self + 1) += tail << 4;
            for (uint i = 0; i < tail; ++i)
                *((Elem16*)position + i) = *value;
        }
        if (local.ref.mpObject)
            local.ref.mpObject->Release();
    }
}

// ---------------------------------------------------------------------------
// @ 0x006dffc0  cluster-map constructor (this in ecx)
// ---------------------------------------------------------------------------
struct ClusterMap {
    bool     mFlag;        // +0x000
    void*    mpPad1;       // +0x004
    void*    mpPad2;       // +0x008
    void*    mpPad3;       // +0x00c
    char     mPad10[0x8];  // +0x010
    void*    mpVecBegin;   // +0x018
    void*    mpVecEnd;     // +0x01c
    void*    mpInlineAlloc;// +0x020
    char     mPad24[0x4];  // +0x024
    void*    mpVecCap;     // +0x028
    char     mPad2c[0x204];// +0x02c
    float    mArea;        // +0x230
    int**    mpListBegin;  // +0x234
    int**    mpListEnd;    // +0x238
    int**    mpListCap;    // +0x23c
    char     mPad240[0x8]; // +0x240
    void*    mpVec2Begin;  // +0x248
    void*    mpVec2End;    // +0x24c
    void*    mpVec2Cap;    // +0x250
    char     mPad254[0x8]; // +0x254
    void*    mpVec3Begin;  // +0x25c
    void*    mpVec3End;    // +0x260
    void*    mpVec3Cap;    // +0x264
    void Init();
};

void ClusterMap::Init() {
    void* inlineBuf = (char*)this + 0x30;
    mFlag = false;
    mpPad1 = 0;
    mpPad2 = 0;
    mpPad3 = 0;
    mpVecEnd = inlineBuf;
    mpVecBegin = inlineBuf;
    mpInlineAlloc = (char*)this + 0x230;
    mpVecCap = inlineBuf;
    mArea = 0.0f;
    mpListBegin = 0;
    mpListEnd = 0;
    mpListCap = 0;
    mpVec2Begin = 0;
    mpVec2End = 0;
    mpVec2Cap = 0;
    mpVec3Begin = 0;
    mpVec3End = 0;
    mpVec3Cap = 0;
}
