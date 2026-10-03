// EASTL vector support in an unoptimized module (/Od /Ob1 /MD /Gy /EHsc /TP):
//   - RefPtrVec    : vector<intrusive_ptr<AtomicRefCounted>>  DoInsertValue (0x425a80)
//   - Vec12        : vector of 12-byte PODs (with fixed-buffer pointer at +0x10)  DoInsertValue (0x425d30)
//   - Vec56        : vector of 0x38-byte records  DoInsertValue (0x425f90) and free (0x426220)
//   - ThreadedVec  : vector<ThreadedObject*> erase (0x426280)
//   - PtrHashtable : hashtable copy constructor (0x426320)
#include <string.h>
#include <new>
#include <intrin.h>

typedef unsigned int uint32_t;

struct Allocator { const char* mpName; };

void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate

// ---------------------------------------------------------------------------
// RefPtrVec
// ---------------------------------------------------------------------------
struct AtomicRefCounted {
    int mVtbl;
    int mPad;
    long mRefCount;
    inline void AddRef() { _InterlockedIncrement(&mRefCount); }
    void Release();                                  // 0x402420
};

struct RefPtr {
    AtomicRefCounted* mp;
    inline RefPtr(const RefPtr& x) throw() : mp(x.mp) { if (mp) mp->AddRef(); }
    inline RefPtr& operator=(const RefPtr& x) {
        AtomicRefCounted* p = x.mp;
        if (p != mp) {
            AtomicRefCounted* old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
};

RefPtr* __cdecl CopyBackwardRef(RefPtr* first, RefPtr* last, RefPtr* resultEnd);   // FUN_0042eb20

inline RefPtr* copy_backward_ref(RefPtr* first, RefPtr* last, RefPtr* resultEnd)
{
    const bool bInputIsPointer = false;
    const bool bOutputIsPointer = false;
    return CopyBackwardRef(first, last, resultEnd);
}

struct RefPtrVec {
    RefPtr* mpBegin;
    RefPtr* mpEnd;
    RefPtr* mpCapacity;
    Allocator mAllocator;

    inline RefPtr* DoAllocate(uint32_t n) {
        return n ? (RefPtr*)AllocatorAllocate(&mAllocator, n * sizeof(RefPtr), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        if (((uint32_t*)p)[-1]) {
            void* q = p;
            AllocatorDeallocate(q);
        }
    }
    inline void DoFree(RefPtr* p, uint32_t n) {
        if (p)
            deallocate(p, n * sizeof(RefPtr));
    }
    void DoInsertValue(RefPtr* position, const RefPtr& value);
};

inline RefPtr* uninitialized_copy_ref(RefPtr* first, RefPtr* last, RefPtr* result)
{
    const bool bIsPod = true;
    RefPtr* p = (RefPtr*)memcpy(result, first, (uint32_t)((char*)last - (char*)first)) + (last - first);
    const bool bB = true;
    return p;
}

// @ 0x00425a80
void RefPtrVec::DoInsertValue(RefPtr* position, const RefPtr& value)
{
    if (mpEnd != mpCapacity) {
        const RefPtr* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) RefPtr(*(mpEnd - 1));
        copy_backward_ref(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        RefPtr* const pNewData = DoAllocate(nNewSize);
        RefPtr* pNewEnd = uninitialized_copy_ref(mpBegin, position, pNewData);
        ::new(pNewEnd) RefPtr(value);
        ++pNewEnd;
        pNewEnd = uninitialized_copy_ref(position, mpEnd, pNewEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// Vec12
// ---------------------------------------------------------------------------
struct Rec12 { uint32_t a, b, c; };

Rec12* __cdecl UninitializedCopy12(Rec12* first, Rec12* last, Rec12* dest);   // FUN_0050f8b0

inline Rec12* copy_backward_impl12(Rec12* first, Rec12* last, Rec12* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

inline Rec12* copy_backward12(Rec12* first, Rec12* last, Rec12* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl12(first, last, resultEnd);
}

struct Vec12 {
    Rec12* mpBegin;
    Rec12* mpEnd;
    Rec12* mpCapacity;
    Allocator mAllocator;
    Rec12* mpFixedBuffer;

    inline Rec12* DoAllocate(uint32_t n) {
        uint32_t reserved[16];   // unused stack slots of the original's inlined allocator layers
        return n ? (Rec12*)AllocatorAllocate(&mAllocator, n * sizeof(Rec12), 4, 0) : 0;
    }
    static inline void FreeBlock(void* q) { AllocatorDeallocate(q); }
    inline void deallocate(void* p, uint32_t n) {
        if (p != mpFixedBuffer) {
            void* q = p;
            AllocatorDeallocate(q);
        }
    }
    inline void DoFree(Rec12* p, uint32_t n) {
        if (p)
            deallocate(p, n * sizeof(Rec12));
    }
    void DoInsertValue(Rec12* position, const Rec12& value);
};

// @ 0x00425d30
void Vec12::DoInsertValue(Rec12* position, const Rec12& value)
{
    if (mpEnd != mpCapacity) {
        const Rec12* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) Rec12(*(mpEnd - 1));
        copy_backward12(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Rec12* const pNewData = DoAllocate(nNewSize);
        Rec12* pNewEnd = UninitializedCopy12(mpBegin, position, pNewData);
        ::new(pNewEnd) Rec12(value);
        ++pNewEnd;
        pNewEnd = UninitializedCopy12(position, mpEnd, pNewEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// Vec56
// ---------------------------------------------------------------------------
struct Rec56 {
    uint32_t data[14];
    Rec56() {}
    Rec56(const Rec56& src) throw();                      // FUN_0040ce80
    Rec56& operator=(const Rec56& src) throw();           // FUN_00537dc0
};

Rec56* __cdecl UninitializedCopy56(Rec56* first, Rec56* last, Rec56* dest);   // FUN_00429ce0

inline Rec56* copy_backward_impl56(Rec56* first, Rec56* last, Rec56* resultEnd)
{
    while (last != first) {
        --last;
        --resultEnd;
        *resultEnd = *last;
    }
    return resultEnd;
}

inline Rec56* copy_backward56(Rec56* first, Rec56* last, Rec56* resultEnd)
{
    uint32_t spare1;   // unused stack slots left by the original's inlined helper layers
    uint32_t spare2;
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl56(first, last, resultEnd);
}

struct Vec56 {
    Rec56* mpBegin;
    Rec56* mpEnd;
    Rec56* mpCapacity;
    Allocator mAllocator;
    Rec56* mpFixedBuffer;

    inline Rec56* DoAllocate(uint32_t n) {
        uint32_t reserved[28];   // unused stack slots of the original's inlined allocator layers
        return n ? (Rec56*)AllocatorAllocate(&mAllocator, n * sizeof(Rec56), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        if (p != mpFixedBuffer) {
            void* q = p;
            AllocatorDeallocate(q);
        }
    }
    inline void DoFree(Rec56* p, uint32_t n) {
        if (p)
            deallocate(p, n * sizeof(Rec56));
    }
    void DoInsertValue(Rec56* position, const Rec56& value);
    void Free();
};

// @ 0x00425f90
void Vec56::DoInsertValue(Rec56* position, const Rec56& value)
{
    if (mpEnd != mpCapacity) {
        const Rec56* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) Rec56(*(mpEnd - 1));
        copy_backward56(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Rec56* const pNewData = DoAllocate(nNewSize);
        Rec56* pNewEnd = UninitializedCopy56(mpBegin, position, pNewData);
        ::new(pNewEnd) Rec56(value);
        ++pNewEnd;
        pNewEnd = UninitializedCopy56(position, mpEnd, pNewEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00426220
void Vec56::Free()
{
    Rec56* q;
    if (mpBegin) {
        uint32_t n = (uint32_t)(mpCapacity - mpBegin) * sizeof(Rec56);
        (void)n;
        Rec56* p = mpBegin;
        if (p != mpFixedBuffer) {
            q = p;
            AllocatorDeallocate(q);
        }
    }
}

// ---------------------------------------------------------------------------
// ThreadedVec : vector<intrusive_ptr<ThreadedObject>>::erase
// ---------------------------------------------------------------------------
namespace Resource { struct ThreadedObject { int Release(); }; }   // 0x404f90

struct ThreadedPtr {
    Resource::ThreadedObject* mp;
    ~ThreadedPtr() { if (mp) mp->Release(); }
};

ThreadedPtr* __cdecl CopyThreaded(ThreadedPtr* first, ThreadedPtr* last, ThreadedPtr* result);   // FUN_0042d4a0

inline ThreadedPtr* copy_threaded(ThreadedPtr* first, ThreadedPtr* last, ThreadedPtr* result)
{
    uint32_t spare[7];   // unused stack slots left by the original's inlined helper layers
    const bool bA = false;
    const bool bInputIsPointer = false;
    return CopyThreaded(first, last, result);
}

inline void destroy_threaded(ThreadedPtr* first, ThreadedPtr* last)
{
    uint32_t spare[3];
    for (; first < last; ++first)
        first->~ThreadedPtr();
}

struct ThreadedVec {
    ThreadedPtr* mpBegin;
    ThreadedPtr* mpEnd;
    ThreadedPtr* mpCapacity;

    ThreadedPtr* erase(ThreadedPtr* first, ThreadedPtr* last);
};

// @ 0x00426280
ThreadedPtr* ThreadedVec::erase(ThreadedPtr* first, ThreadedPtr* last)
{
    ThreadedPtr* const i = copy_threaded(last, mpEnd, first);
    destroy_threaded(i, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// ---------------------------------------------------------------------------
// PtrHashtable : copy constructor of a hashtable with 8-byte values
// ---------------------------------------------------------------------------
struct HashNode { uint32_t mValue[2]; HashNode* mpNext; };
extern HashNode* gEmptyBucketArray[2];   // 0x154df28

struct RehashPolicy { float mfMaxLoadFactor; float mfGrowthFactor; uint32_t mnNextResize; };
struct HashFn { uint32_t v; };

struct PtrHashtable {
    HashFn mHash;
    HashNode** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    RehashPolicy mRehashPolicy;

    PtrHashtable(const PtrHashtable& x);
    HashNode** DoAllocateBuckets(uint32_t n);        // FUN_00567260
    HashNode* DoAllocateNode(const HashNode* p);     // FUN_004265b0
};

// @ 0x00426320
PtrHashtable::PtrHashtable(const PtrHashtable& x)
{
    mHash = x.mHash;
    mnBucketCount = x.mnBucketCount;
    mnElementCount = x.mnElementCount;
    mRehashPolicy = x.mRehashPolicy;
    if (mnElementCount) {
        mpBucketArray = DoAllocateBuckets(mnBucketCount);
        for (uint32_t i = 0; i < x.mnBucketCount; ++i) {
            HashNode* pNodeSource = x.mpBucketArray[i];
            HashNode** ppNodeDest = mpBucketArray + i;
            while (pNodeSource) {
                *ppNodeDest = DoAllocateNode(pNodeSource);
                ppNodeDest = &(*ppNodeDest)->mpNext;
                pNodeSource = pNodeSource->mpNext;
            }
        }
    } else {
        mnBucketCount = 1;
        mpBucketArray = gEmptyBucketArray;
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
}
