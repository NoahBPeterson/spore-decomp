// EASTL template instantiations (hashtable with fixed node pool, fixed_vector,
// vector<T*>::DoInsertValues). This module was built WITHOUT optimization:
// compile with /Od /Ob1 /MD /Gy /EHsc /TP (frame pointer, every local in memory,
// only inline-marked functions expanded).
//
// /Od notes learned here:
//  - inline-function params whose address is taken (bound to const&) or whose
//    argument is a memory load get their own stack slot; plain variables are substituted.
//  - stack slot order of locals depends on their NAMES (symbol hashing), not only on
//    declaration order, so EASTL's original local names matter.
#include <new>
#include <string.h>

void* EASTL_allocator_allocate(unsigned int n, const char* pName, int flags, unsigned int debugFlags,
                               const char* pFile, int line);

// ---------------------------------------------------------------------------
// eastl::allocator (stateless, overflow allocator for the fixed pools)
// ---------------------------------------------------------------------------
struct EASTLAllocator {
    inline void* allocate(unsigned int n, int flags = 0) {
        void* p = EASTL_allocator_allocate(n, "Editor", flags, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        return p;
    }
    inline void deallocate(void* p, unsigned int n) { delete[] (char*)p; }
};

// ---------------------------------------------------------------------------
// hashtable<uint32_t key, 12-byte value_type> with fixed_hashtable_allocator
// ---------------------------------------------------------------------------
struct HashValue { unsigned int first, second, third; };
struct HashNode { HashValue mValue; HashNode* mpNext; };
struct PoolLink { PoolLink* mpNext; };

struct FixedPool {
    PoolLink* mpHead;
    PoolLink* mpNext;
    void* mpPoolBegin;
    void* mpCapacity;
    unsigned int mnNodeSize;
    static EASTLAllocator mOverflowAllocator;

    void* allocate();
    inline void deallocate(void* p) {
        if ((p >= mpPoolBegin) && (p < mpCapacity)) {
            ((PoolLink*)p)->mpNext = mpHead;
            mpHead = (PoolLink*)p;
        } else
            mOverflowAllocator.deallocate(p, mnNodeSize);
    }
};

struct FixedHashtableAllocator {
    FixedPool mPool;
    void* mpBucketBuffer;

    inline void* allocate(unsigned int n, int flags = 0) {
        int unused[3];  // stand-in for three dead stack slots in the original
        if (n == sizeof(HashNode))
            return mPool.allocate();
        return mpBucketBuffer;
    }
    inline void deallocate(void* p, unsigned int n) {
        if (p != mpBucketBuffer)
            mPool.deallocate(p);
    }
};

void* allocate_memory(FixedHashtableAllocator& a, unsigned int n, unsigned int alignment,
                      unsigned int alignmentOffset);

inline unsigned int hash_uint32(unsigned int k) { return k; }
inline unsigned int mod_range_hashing(unsigned int r, unsigned int n) { return r % n; }

struct Hashtable {
    void* mpPad0;
    HashNode** mpBucketArray;
    unsigned int mnBucketCount;
    unsigned int mnElementCount;
    char mRehashPolicy[0xc];
    FixedHashtableAllocator mAllocator;

    HashNode* DoAllocateNode(const HashValue& value);
    HashNode** DoAllocateBuckets(unsigned int n);
    inline void DoFreeBuckets(HashNode** pBucketArray, unsigned int n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(HashNode*));
    }
    void DoRehash(unsigned int nNewBucketCount);
};

// @ 0x004CE770
HashNode* Hashtable::DoAllocateNode(const HashValue& value) {
    HashNode* const pNode = (HashNode*)allocate_memory(mAllocator, sizeof(HashNode), 4, 0);
    ::new(&pNode->mValue) HashValue(value);
    pNode->mpNext = 0;
    return pNode;
}

// @ 0x004CE7E0
HashNode** Hashtable::DoAllocateBuckets(unsigned int n) {
    HashNode** const pBucketArray = (HashNode**)mAllocator.allocate((n + 1) * sizeof(HashNode*));
    memset(pBucketArray, 0, n * sizeof(HashNode*));
    pBucketArray[n] = (HashNode*)(unsigned int)~0;
    return pBucketArray;
}

// @ 0x004CE850
void* FixedPool::allocate() {
    void* p;
    if (mpHead) {
        p = mpHead;
        mpHead = mpHead->mpNext;
    } else
        p = mOverflowAllocator.allocate(mnNodeSize);
    return p;
}

// @ 0x004CE8B0
void Hashtable::DoRehash(unsigned int nNewBucketCount) {
    HashNode** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
    HashNode* pNode;
    for (unsigned int i = 0; i < mnBucketCount; ++i) {
        while ((pNode = mpBucketArray[i]) != 0) {
            const unsigned int nNewBucketIndex = mod_range_hashing(hash_uint32(pNode->mValue.first), nNewBucketCount);
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pBucketArray[nNewBucketIndex];
            pBucketArray[nNewBucketIndex] = pNode;
        }
    }
    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
}

// ---------------------------------------------------------------------------
// fixed_vector<T*, 4>
// ---------------------------------------------------------------------------
struct FixedVectorAllocator {
    int mOverflowAllocator;
    void* mpPoolBegin;
    FixedVectorAllocator(void* pNodeBuffer) : mpPoolBegin(pNodeBuffer) {}
    FixedVectorAllocator(const FixedVectorAllocator& x) { mpPoolBegin = x.mpPoolBegin; }
};

struct FixedVectorBase {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    FixedVectorAllocator mAllocator;
    int mPad14;
    FixedVectorBase(const FixedVectorAllocator& allocator)
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {}
};

struct FixedVectorPtr4 : FixedVectorBase {
    void* mBuffer[4];
    FixedVectorPtr4();
};

// @ 0x004CE9D0
FixedVectorPtr4::FixedVectorPtr4() : FixedVectorBase(FixedVectorAllocator(mBuffer)) {
    mpBegin = mpEnd = (void**)&mBuffer[0];
    mpCapacity = mpBegin + 4;
}

// ---------------------------------------------------------------------------
// vector<T*>::DoInsertValues
// ---------------------------------------------------------------------------
typedef void* VecT;

struct true_type { true_type() {} };

struct generic_iterator {
    VecT* mIterator;
    generic_iterator(VecT* const& x) : mIterator(x) {}
    VecT* base() const { return mIterator; }
};

generic_iterator copy_generic_iterator_do_copy(generic_iterator first, generic_iterator last,
                                               generic_iterator result);  // 0x004D1240
generic_iterator fill_n(generic_iterator first, unsigned int n, const VecT& value);  // 0x004AB450

struct VectorAllocator {
    inline void deallocate(void* p, unsigned int n) {
        if (((void**)p)[-1])
            delete[] (char*)p;
    }
};
void* allocate_memory(void* a, unsigned int n, unsigned int alignment, unsigned int alignmentOffset);

inline generic_iterator copy(generic_iterator first, generic_iterator last, generic_iterator result) {
    const bool bInputIsGenericIterator = true;
    const bool bOutputIsGenericIterator = true;
    return copy_generic_iterator_do_copy(first, last, result);
}
inline generic_iterator uninitialized_copy_impl(generic_iterator first, generic_iterator last,
                                                generic_iterator result, const true_type&) {
    return copy(first, last, result);
}
inline VecT* uninitialized_copy_generic(VecT* first, VecT* last, VecT* result) {
    const generic_iterator i(uninitialized_copy_impl(generic_iterator(first), generic_iterator(last),
                                                     generic_iterator(result), true_type()));
    return i.base();
}
inline void uninitialized_fill_n_impl(generic_iterator first, unsigned int n, const VecT& value, const true_type&) {
    fill_n(first, n, value);
}
inline void uninitialized_fill_n_ptr(VecT* first, unsigned int n, const VecT& value) {
    uninitialized_fill_n_impl(generic_iterator(first), n, value, true_type());
}
inline VecT* copy_backward(VecT* first, VecT* last, VecT* resultEnd) {
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    const bool bHasTrivialCopy = true;
    return (VecT*)memmove(resultEnd - (last - first), first, (unsigned int)((char*)last - (char*)first));
}
inline VecT* copy_memcpy(VecT* first, VecT* last, VecT* result) {
    return (VecT*)memcpy(result, first, (unsigned int)((char*)last - (char*)first)) + (last - first);
}
inline VecT* uninitialized_copy_ptr(VecT* first, VecT* last, VecT* result) {
    const bool bA = true;
    VecT* p = copy_memcpy(first, last, result);
    const bool bB = true;
    return p;
}
inline void fill(VecT* first, VecT* last, const VecT& value) {
    for (const VecT temp = value; first != last; ++first)
        *first = temp;
}

struct VectorPtr {
    VecT* mpBegin;
    VecT* mpEnd;
    VecT* mpCapacity;
    static VectorAllocator sAllocator;
    char mAllocator[4];

    inline unsigned int GetNewCapacity(unsigned int currentCapacity) {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
    inline VecT* DoAllocate(unsigned int n) {
        return n ? (VecT*)allocate_memory(&mAllocator, n * sizeof(VecT), 4, 0) : 0;
    }
    inline void DoFree(VecT* p, unsigned int n) {
        if (p)
            sAllocator.deallocate(p, n * sizeof(VecT));
    }
    void DoInsertValues(VecT* position, unsigned int n, const VecT& value);
};

// @ 0x004CEA40
void VectorPtr::DoInsertValues(VecT* position, unsigned int n, const VecT& value) {
    if (n <= (unsigned int)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const VecT temp = value;
            const unsigned int nExtra = (unsigned int)(mpEnd - position);
            VecT* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_generic(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward(position, pEnd - n, pEnd);
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_generic(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill(position, pEnd, temp);
            }
        }
    } else {
        const unsigned int nPrevSize = (unsigned int)(mpEnd - mpBegin);
        const unsigned int nGrowSize = GetNewCapacity(nPrevSize);
        const unsigned int nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        VecT* const pNewData = DoAllocate(nNewSize);
        VecT* pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_copy_ptr(position, mpEnd, pNewEnd + n);
        DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
