// EASTL-style containers compiled without optimization (/Od /Ob1, no EH):
//  - a sorted-vector lookup wrapper,
//  - vector<Elem24>::DoInsert-style insert (Elem24 = {vector<8-byte>, uint, bool}),
//    its uninitialized_copy helpers and the 16-byte-element equivalents,
//  - hashtable DoRehash, vector destructors, eastl::sort over 12-byte items,
//  - a pointer-to-member call thunk.
// Flags: /Od /Ob1 /MD /Gy /TP   (frame pointer, all locals in memory, only inline-marked
// functions expanded; no /EHsc so loops with placement new still inline).
//
// /Od notes: inlined helper parameters get their own stack slots, so the nested inline
// helpers below (generic_iterator wrappers, comparator by value) are there to reproduce
// the original slot layout. Dead `unused[]` locals stand in for slots that belonged to
// helpers whose bodies compiled to nothing.
#include "types.h"

typedef unsigned int uint;
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

// ---------------------------------------------------------------------------
// Externals (addresses are masked by relocations; only shapes matter)
// ---------------------------------------------------------------------------
void* __cdecl AllocatorAllocate(void* alloc, uint size, uint align, uint offset);   // 0x42DEE0

// ---------------------------------------------------------------------------
// eastl helpers
// ---------------------------------------------------------------------------
struct false_type { false_type() {} };

template<class T> struct generic_iterator {
    T* mIterator;
    generic_iterator(T* const& x) : mIterator(x) {}
    T* base() const { return mIterator; }
    T& operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
};
template<class T> inline bool operator!=(const generic_iterator<T>& a, const generic_iterator<T>& b)
{ return a.mIterator != b.mIterator; }

// ---------------------------------------------------------------------------
// Element types
// ---------------------------------------------------------------------------
// vector<8-byte> (begin, end, capacity, allocator): copy ctor 0x42AD20, operator= 0x42D990
struct Vec8 {
    void* mBegin; void* mEnd; void* mCapEnd; uint mAllocator;
    Vec8(const Vec8& o);
    Vec8& operator=(const Vec8& o);
};

struct Elem24 {
    Vec8   vec;
    uint   pad;
    bool   flag;
    Elem24(const Elem24& o) : vec(o.vec) { flag = o.flag; }
    Elem24& operator=(const Elem24& o) { vec = o.vec; bool t = o.flag; flag = t; return *this; }
};

struct Elem16 { uint32_t a, b, c, d; };
struct Item12 { uint32_t key, a, b; };

// ---------------------------------------------------------------------------
// uninitialized_copy over generic_iterator wrappers
// ---------------------------------------------------------------------------
inline void ScratchSlots9() { unsigned unused[9]; }
typedef generic_iterator<Elem24> GI24;
inline GI24 uninitialized_copy_impl(GI24 first, GI24 last, GI24 result, const false_type&)
{
    GI24 currentDest(result);
    for (; first != last; ++first, ++currentDest) {
        ::new((void*)&*currentDest) Elem24(*first);
        ScratchSlots9();   // dead slots of the original's construct helper
    }
    return currentDest;
}

// @ 0x00427160
Elem24* __cdecl UninitializedCopyElem24(Elem24* first, Elem24* last, Elem24* result)
{
    const GI24 i(uninitialized_copy_impl(GI24(first), GI24(last), GI24(result), false_type()));
    return i.base();
}

typedef generic_iterator<Elem16> GI16;
inline GI16 uninitialized_copy_impl16(GI16 first, GI16 last, GI16 result, const false_type&)
{
    GI16 currentDest(result);
    for (; first != last; ++first, ++currentDest)
        ::new((void*)&*currentDest) Elem16(*first);
    return currentDest;
}

// @ 0x00427270
Elem16* __cdecl UninitializedCopyElem16(Elem16* first, Elem16* last, Elem16* result)
{
    const GI16 i(uninitialized_copy_impl16(GI16(first), GI16(last), GI16(result), false_type()));
    return i.base();
}

// 0x42ADF0: guarded uninitialized_copy (destroys on failure)
Elem24* __cdecl UninitializedCopyGuardedElem24(Elem24* first, Elem24* last, Elem24* result);

// ---------------------------------------------------------------------------
// Sorted vector of (key, value) pairs; comparator flag at +0x14
// ---------------------------------------------------------------------------
void* __cdecl LowerBoundImpl(int* first, int* last, const int* key, bool flag);  // 0x42DD00

struct IntPair { int* first; int* second; };

struct SortedPairVector {
    int*  mBegin;
    int*  mEnd;
    int   pad[3];
    bool  mFlag;

    inline int* begin() { return mBegin; }
    inline int* end() { return mEnd; }
    static inline bool less(const int& a, const int& b) { return a < b; }

    IntPair* __thiscall Find(IntPair* out, const int* key);
};

// @ 0x00426d90
IntPair* __thiscall SortedPairVector::Find(IntPair* out, const int* key)
{
    int* next;
    int* ret = (int*)LowerBoundImpl(begin(), end(), key, mFlag);
    if (ret == end() || less(*key, *ret)) {
        out->first = ret;
        out->second = ret;
        return out;
    }
    next = ret;
    next += 2;
    out->first = ret;
    out->second = next;
    return out;
}

// ---------------------------------------------------------------------------
// vector<Elem24>
// ---------------------------------------------------------------------------
struct VectorAllocator {
    inline void deallocate(void* p, uint n) { if (((int*)p)[-1]) delete[] (char*)p; }
};
static VectorAllocator sAllocator;

inline Elem24* copy_backward_impl(Elem24* first, Elem24* last, Elem24* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

inline Elem24* copy_backward(Elem24* first, Elem24* last, Elem24* resultEnd)
{
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl(first, last, resultEnd);
}

struct Elem24Vector {
    Elem24* mBegin;
    Elem24* mEnd;
    Elem24* mCapEnd;
    uint    mAllocator;

    inline uint GetNewCapacity(uint currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    inline Elem24* DoAllocate(uint n) { return n ? (Elem24*)AllocatorAllocate(&mAllocator, n * sizeof(Elem24), 4, 0) : 0; }
    inline void DoFree(Elem24* p, uint n) { if (p) sAllocator.deallocate(p, n * sizeof(Elem24)); }

    void    __thiscall Insert(Elem24* position, const Elem24& value);
    Elem24* __thiscall AllocateAndCopy(uint n, Elem24* first, Elem24* last);
};

// dead slots of helpers that compiled away (reproduces the original frame layout)
inline void ScratchSlots() { unsigned unused[19]; }

// @ 0x00426E30
void __thiscall Elem24Vector::Insert(Elem24* position, const Elem24& value)
{
    if (mEnd != mCapEnd) {
        const Elem24* pValue = &value;
        if ((pValue >= position) && (pValue < mEnd))
            ++pValue;
        ::new((void*)mEnd) Elem24(*(mEnd - 1));
        copy_backward(position, mEnd - 1, mEnd);
        *position = *pValue;
        ++mEnd;
    } else {
        const uint nPrevSize = mEnd - mBegin;
        const uint nNewSize = GetNewCapacity(nPrevSize);
        Elem24* const pNewData = DoAllocate(nNewSize);
        Elem24* pNewEnd = UninitializedCopyGuardedElem24(mBegin, position, pNewData);
        ::new((void*)pNewEnd) Elem24(value);
        pNewEnd++;
        pNewEnd = UninitializedCopyGuardedElem24(position, mEnd, pNewEnd);
        ScratchSlots();
        DoFree(mBegin, mCapEnd - mBegin);
        mBegin = pNewData;
        mEnd = pNewEnd;
        mCapEnd = pNewData + nNewSize;
    }
}

// @ 0x00427100
Elem24* __thiscall Elem24Vector::AllocateAndCopy(uint n, Elem24* first, Elem24* last)
{
    Elem24* const pNewData = DoAllocate(n);
    unsigned unused[19];
    UninitializedCopyElem24(first, last, pNewData);
    return pNewData;
}

// ---------------------------------------------------------------------------
// vector<Elem16>
// ---------------------------------------------------------------------------
struct Elem16Vector {
    Elem16* mBegin;
    Elem16* mEnd;
    Elem16* mCapEnd;
    uint    mAllocator;

    inline Elem16* DoAllocate(uint n) { return n ? (Elem16*)AllocatorAllocate(&mAllocator, n * sizeof(Elem16), 4, 0) : 0; }
    Elem16* __thiscall AllocateAndCopy(uint n, Elem16* first, Elem16* last);
};

// @ 0x00427210
Elem16* __thiscall Elem16Vector::AllocateAndCopy(uint n, Elem16* first, Elem16* last)
{
    Elem16* const pNewData = DoAllocate(n);
    unsigned unused[11];
    UninitializedCopyElem16(first, last, pNewData);
    return pNewData;
}

// ---------------------------------------------------------------------------
// Hashtable DoRehash: bucket array at +4, bucket count at +8; node = {hash, value, next}
// ---------------------------------------------------------------------------
struct HashNode { uint hash; uint value; HashNode* next; };

struct HashAllocator {
    inline void deallocate(void* p, uint n) { delete[] (char*)p; }
};

inline uint hash_uint32(uint k) { return k; }
inline uint mod_range_hashing(uint r, uint n) { return r % n; }

struct Hashtable {
    uint           pad0;
    HashNode**     mpBucketArray;
    uint           mnBucketCount;
    HashAllocator  mAllocator;

    HashNode** __thiscall DoAllocateBuckets(uint n);   // 0x567260
    inline void DoFreeBuckets(HashNode** pBucketArray, uint n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(HashNode*));
    }
    void __thiscall DoRehash(uint nNewBucketCount);
};

// @ 0x00427320
void __thiscall Hashtable::DoRehash(uint nNewBucketCount)
{
    HashNode** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
    HashNode* pNode;
    for (uint i = 0; i < mnBucketCount; ++i) {
        while ((pNode = mpBucketArray[i]) != 0) {
            const uint nNewBucketIndex = mod_range_hashing(hash_uint32(pNode->hash), nNewBucketCount);
            mpBucketArray[i] = pNode->next;
            pNode->next = pBucketArray[nNewBucketIndex];
            pBucketArray[nNewBucketIndex] = pNode;
        }
    }
    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
}

// ---------------------------------------------------------------------------
// Vector destructors (32-byte and 56-byte elements)
// ---------------------------------------------------------------------------
struct Block32 { char b[32]; };
struct Block56 { char b[56]; };

template<class T> struct PodVector {
    T* mBegin; T* mEnd; T* mCapEnd;
    inline void DoFree(T* p, uint n) { sAllocator.deallocate(p, n); }
};

// @ 0x004273F0
void __fastcall DestroyVector32(PodVector<Block32>* v)
{
    if (v->mBegin)
        v->DoFree(v->mBegin, (v->mCapEnd - v->mBegin) * sizeof(Block32));
}

// @ 0x00427440
void __fastcall DestroyVector56(PodVector<Block56>* v)
{
    if (v->mBegin)
        v->DoFree(v->mBegin, (v->mCapEnd - v->mBegin) * sizeof(Block56));
}

// ---------------------------------------------------------------------------
// eastl::sort over 12-byte items ordered by their first field
// ---------------------------------------------------------------------------
struct less_uint { inline bool operator()(const uint& a, const uint& b) const { return a < b; } };

void __cdecl IntroSortLoop(Item12* first, Item12* last, int depth, less_uint cmp);  // 0x42B2D0
void __cdecl InsertionSort(Item12* first, Item12* last, less_uint cmp);             // 0x42B4E0

// Shifts larger elements right until `value` fits. `next` starts at the slot being filled;
// the iterator copies are separate parameters because that is how the original expanded.
inline void unguarded_linear_insert(Item12 value, Item12* next, Item12* last, const less_uint& compare)
{
    --next;
    for (; compare(value.key, next->key); --last, --next)
        *last = *next;
    *last = value;
}

inline void insertion_sort_tail(Item12* start, Item12* last, less_uint compare)
{
    for (Item12* i = start; i != last; ++i)
        unguarded_linear_insert(*i, i, i, compare);
}

// @ 0x004274A0
void __cdecl Sort(Item12* first, Item12* last, less_uint compare)
{
    if (first != last) {
        int log2n;
        {
            int n = (last - first);
            log2n = 0;
            for (; n != 0; ++log2n)
                n >>= 1;
        }
        IntroSortLoop(first, last, log2n * 2 - 2, compare);
        if ((last - first) > 28) {
            InsertionSort(first, first + 28, compare);
            unsigned unused[22];   // dead slots of helpers that compiled away
            int unused2;
            insertion_sort_tail(first + 28, last, compare);
        } else {
            InsertionSort(first, last, compare);
        }
    }
}

// ---------------------------------------------------------------------------
// Member-function-pointer call thunk
// ---------------------------------------------------------------------------
struct TargetBaseA { virtual void a(); };
struct TargetBaseB { virtual void b(); };
class Target : public TargetBaseA, public TargetBaseB { public: void __thiscall Handler(int arg); };

// @ 0x00427600
void __cdecl CallHandler(int arg, Target* obj)
{
    void (__thiscall Target::*pm)(int) = &Target::Handler;
    (obj->*pm)(arg);
}
