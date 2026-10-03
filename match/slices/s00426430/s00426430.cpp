// EASTL-style container internals (unoptimized module: /Od /Ob1, frame pointers, every local in memory,
// built without C++ EH unwinding: /Od /Ob1 /MD /Gy /TP).
//   - SmallBuffer::swap                 : member-wise swap, copy-and-swap when allocators differ
//   - RefPairTable::DoAllocateNode      : hash-table node holding {refcounted ptr, int}
//   - HashTable::DoRehash               : move every node into a new bucket array
//   - ByteVector                        : vector<char> (DoInsertValue, DoAllocateAndCopy)
//   - Vector8 / VectorBase8             : vector of 8-byte elements (operator=, base destructor)
//   - SortedVector::InsertHint          : sorted-vector insert with a position hint
//
// /Od notes learned here (see also the other EASTL slices):
//  - Inlined helper functions keep their parameters, locals and return temporaries in the caller's
//    frame.  Plain-variable arguments are passed straight through; expression arguments and
//    arguments the helper modifies get a stack temporary.
//  - Unused inlined helper locals are reproduced with ScratchSlots<N>().
//  - Tag objects EASTL passes by const reference (true_type/false_type) are one-byte temporaries.
//  - `X + memcpy(...)` only keeps X in esi when memcpy is the plain (non-intrinsic) function and
//    the whole thing lives inside a template helper.

#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, uint32_t);

inline void* operator new(unsigned int, void* p) { return p; }

void* __cdecl AllocatorAllocate(void* alloc, uint32_t size, uint32_t align, uint32_t flags);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                               // EASTL_allocator_deallocate

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// Empty tag objects EASTL passes down copy/move helpers (each is a byte at /Od).
struct TagA { char c; TagA() : c(0) {} };
struct TagB { char c; TagB() : c(0) {} };
struct TagC { char c; TagC() : c(1) {} };
struct TagD { char c; TagD() : c(1) {} };

// ---------------------------------------------------------------------------------------------
// SmallBuffer::swap
// ---------------------------------------------------------------------------------------------
struct Triple { uint32_t a, b, c; };
template <class T> inline void swap(T& a, T& b) { T temp = a; a = b; b = temp; }
struct EqualAllocator { };
inline bool operator==(const EqualAllocator&, const EqualAllocator&) { return true; }

struct SmallBuffer
{
    uint32_t mVtbl;          // +0x00
    uint32_t mBegin;         // +0x04
    uint32_t mEnd;           // +0x08
    uint32_t mCapacity;      // +0x0c
    Triple mInline;          // +0x10
    EqualAllocator mAllocator;

    SmallBuffer(const SmallBuffer& x);   // FUN_00426320
    ~SmallBuffer();                      // 0x00420ab0
    SmallBuffer& operator=(const SmallBuffer& x)
    {
        if (this != &x)
        {
            SmallBuffer t(x);
            swap(t);
        }
        return *this;
    }
    void swap(SmallBuffer& x);
};

// @ 0x00426430
void SmallBuffer::swap(SmallBuffer& x)
{
    if (mAllocator == x.mAllocator)
    {
        ScratchSlots<1>();
        ::swap(mInline, x.mInline);
        ::swap(mBegin, x.mBegin);
        ::swap(mEnd, x.mEnd);
        ::swap(mCapacity, x.mCapacity);
    }
    else
    {
        const SmallBuffer temp(*this);
        *this = x;
        ScratchSlots<3>();
        x = temp;
        ScratchSlots<6>();
    }
}

// ---------------------------------------------------------------------------------------------
// Hash table with refcounted-pair values
// ---------------------------------------------------------------------------------------------
struct RefCounted { int pad; long mRefCount; };   // refcount at +4, atomic
extern "C" long _InterlockedIncrement(long volatile*);
#pragma intrinsic(_InterlockedIncrement)
inline void AddRefObj(RefCounted* o) { _InterlockedIncrement(&o->mRefCount); }

struct RefPtr
{
    RefCounted* mp;
    RefPtr(const RefPtr& o) : mp(o.mp) { if (mp) AddRefObj(mp); }
};
struct RefPairValue
{
    RefPtr first;
    int second;
    RefPairValue(const RefPairValue& v) : first(v.first), second(v.second) {}
};
struct RefPairNode
{
    RefPairValue mValue;
    RefPairNode* mpNext;
    RefPairNode(const RefPairValue& v) : mValue(v) {}
};
struct RefPairTable
{
    uint32_t mpad[7];
    uint32_t mAllocator;   // +0x1c
    RefPairNode* DoAllocateNode(const RefPairValue& v);
};

// @ 0x004265b0
RefPairNode* RefPairTable::DoAllocateNode(const RefPairValue& v)
{
    RefPairNode* pNode = (RefPairNode*)AllocatorAllocate(&mAllocator, sizeof(RefPairNode), 4, 0);
    ::new (pNode) RefPairNode(v);
    pNode->mpNext = 0;
    return pNode;
}

// ---------------------------------------------------------------------------------------------
// HashTable::DoRehash
// ---------------------------------------------------------------------------------------------
struct HashNode { uint32_t key; uint32_t pad; HashNode* mpNext; };
struct FieldSetHash { uint32_t operator()(uint32_t k) const; };   // 0x00401bf0

struct HashTable
{
    uint16_t mFlags;
    FieldSetHash mHash;                // +2
    HashNode** mpBucketArray;          // +4
    uint32_t mnBucketCount;            // +8

    HashNode** DoAllocateBuckets(uint32_t n);   // FUN_00567260
    void DoFreeBuckets(HashNode** p, uint32_t n)
    {
        if (n > 1)
        {
            void* q = p;
            AllocatorDeallocate(q);
        }
    }
    uint32_t GetHashCode(uint32_t k) { uint32_t h = mHash(k); return h; }
    uint32_t BucketIndex(const HashNode* node, uint32_t n)
    {
        uint32_t k = node->key;
        return GetHashCode(k) % n;
    }
    void DoRehash(uint32_t nNewBucketCount);
};

// @ 0x00426640
void HashTable::DoRehash(uint32_t nNewBucketCount)
{
    HashNode** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
    HashNode* pNode;
    for (uint32_t i = 0; i < mnBucketCount; ++i)
    {
        while ((pNode = mpBucketArray[i]) != 0)
        {
            const uint32_t nNewBucketIndex = BucketIndex(pNode, nNewBucketCount);
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pBucketArray[nNewBucketIndex];
            pBucketArray[nNewBucketIndex] = pNode;
        }
    }
    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
}

// ---------------------------------------------------------------------------------------------
// ByteVector: vector<char> with a header-carrying array allocator
// ---------------------------------------------------------------------------------------------
struct ArrayAllocator { uint32_t mFlags, mFlags2; };

inline char* CopyBackwardBytes(char* first, char* last, char* destEnd)
{
    TagB tb = TagB(); TagA ta = TagA(); TagC tc = TagC();
    return (char*)memmove(destEnd - (last - first), first, last - first);
}
template<class T> inline T* MoveImpl(const T* first, const T* last, T* result)
{
    return (T*)memcpy(result, first, (last - first) * sizeof(T)) + (last - first);
}
inline char* UninitMoveImpl(char* first, char* last, char* result, const TagC&) { return MoveImpl(first, last, result); }
inline void UninitMoveDone(char* r, const TagD&) { }
inline char* UninitializedMove(char* first, char* last, char* result)
{
    char* r = UninitMoveImpl(first, last, result, TagC());
    UninitMoveDone(r, TagD());
    return r;
}
char* __cdecl UninitializedCopyBytes(const char* first, const char* last, char* dest);   // FUN_00475bd0
inline char* uninitialized_copy(const char* first, const char* last, char* dest)
{
    ScratchSlots<17>();
    return UninitializedCopyBytes(first, last, dest);
}

struct ByteVector
{
    char* mBegin;
    char* mEnd;
    char* mCapacity;
    ArrayAllocator mAllocator;   // +0x0c

    char* DoAllocate(uint32_t n) { return n ? (char*)AllocatorAllocate(&mAllocator, n, 1, 0) : 0; }
    void DoFree(char* p, uint32_t n)
    {
        if (p)
        {
            if (((int*)p)[-1])
            {
                void* q = p;
                AllocatorDeallocate(q);
            }
        }
    }
    void DoInsertValue(char* position, const char* value);
    char* DoAllocateAndCopy(uint32_t n, const char* first, const char* last);
};

// @ 0x00426730
void ByteVector::DoInsertValue(char* position, const char* value)
{
    if (mEnd != mCapacity)
    {
        const char* pValue = value;
        if (pValue >= position && pValue < mEnd)
            ++pValue;
        new (mEnd) char(*(mEnd - 1));
        CopyBackwardBytes(position, mEnd - 1, mEnd);
        *position = *pValue;
        ++mEnd;
    }
    else
    {
        const uint32_t nPrevSize = mEnd - mBegin;
        const uint32_t nNewSize = nPrevSize ? nPrevSize * 2 : 1;
        char* const pNewData = nNewSize ? (char*)AllocatorAllocate(&mAllocator, nNewSize, 1, 0) : 0;
        char* pNewEnd = UninitializedMove(mBegin, position, pNewData);
        new (pNewEnd) char(*value);
        ++pNewEnd;
        pNewEnd = UninitializedMove(position, mEnd, pNewEnd);
        DoFree(mBegin, mCapacity - mBegin);
        mBegin = pNewData;
        mEnd = pNewEnd;
        mCapacity = pNewData + nNewSize;
    }
}

// @ 0x00426950
char* ByteVector::DoAllocateAndCopy(uint32_t n, const char* first, const char* last)
{
    char* p = DoAllocate(n);
    uninitialized_copy(first, last, p);
    return p;
}

// ---------------------------------------------------------------------------------------------
// Vector of 8-byte elements
// ---------------------------------------------------------------------------------------------
struct Elem8 { uint32_t a, b; };

struct DeallocAllocator
{
    void deallocate(void* p, unsigned int) { delete[] (char*)p; }   // EASTL_allocator_deallocate
    unsigned int mFlags;
};

struct VectorBase8
{
    Elem8* mpBegin;
    Elem8* mpEnd;
    Elem8* mpCapacity;
    DeallocAllocator mAllocator;
    ~VectorBase8();
};

// @ 0x00426c70
VectorBase8::~VectorBase8()
{
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(Elem8));
}

inline void destruct(Elem8* first, Elem8* last) { for (; first < last; ++first) {} }
inline Elem8* CopyImpl(const Elem8* first, const Elem8* last, Elem8* dest)
{
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}
inline Elem8* CopyRange(const Elem8* first, const Elem8* last, Elem8* dest)
{
    TagB tb; TagA ta; TagA tc;
    return CopyImpl(first, last, dest);
}
Elem8* __cdecl UninitializedCopy8(const Elem8* first, const Elem8* last, Elem8* dest);   // FUN_004d0960

struct Vector8
{
    Elem8* mBegin;
    Elem8* mEnd;
    Elem8* mCapacity;
    uint32_t mAllocator;

    Elem8* DoAllocateAndCopy(uint32_t n, const Elem8* first, const Elem8* last);   // FUN_0056a0e0
    uint32_t size() const { return mEnd - mBegin; }
    uint32_t capacity() const { return mCapacity - mBegin; }
    void DoFree(Elem8* p, uint32_t n)
    {
        if (p)
        {
            void* q = p;
            AllocatorDeallocate(q);
        }
    }
    Vector8& operator=(const Vector8& x);
};

// @ 0x004269b0
Vector8& Vector8::operator=(const Vector8& x)
{
    if (&x != this)
    {
        const uint32_t n = x.mEnd - x.mBegin;
        if (n > capacity())
        {
            Elem8* const pNewData = DoAllocateAndCopy(n, x.mBegin, x.mEnd);
            ScratchSlots<9>();
            destruct(mBegin, mEnd);
            DoFree(mBegin, capacity());
            mBegin = pNewData;
            mCapacity = mBegin + n;
        }
        else if (n > size())
        {
            CopyRange(x.mBegin, x.mBegin + size(), mBegin);
            ScratchSlots<11>();
            UninitializedCopy8(x.mBegin + size(), x.mEnd, mEnd);
        }
        else
        {
            Elem8* pNewEnd = CopyRange(x.mBegin, x.mEnd, mBegin);
            destruct(pNewEnd, mEnd);
        }
        mEnd = mBegin + n;
    }
    return *this;
}

// ---------------------------------------------------------------------------------------------
// Sorted vector of ints: insert with a position hint
// ---------------------------------------------------------------------------------------------
struct less_int { bool operator()(const int& a, const int& b) const { return a < b; } };
int* __cdecl SearchRange(int* first, int* last, const int* key, bool flag);   // FUN_0042dd00

struct SortedVector
{
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    int mpad[2];
    bool mFlag;               // +0x14
    less_int mCompare;

    int* begin() { return mpBegin; }
    int* end() { return mpEnd; }
    int* InsertAt(int* position, const int* key);   // FUN_00565c80
    int* InsertHint(int* position, const int* key);
};

// @ 0x00426cc0
int* SortedVector::InsertHint(int* position, const int* key)
{
    int* result;
    if (position != end() && mCompare(*key, *position))
        result = SearchRange(begin(), position, key, mFlag);
    else
        result = SearchRange(position, end(), key, mFlag);
    if (result == end() || mCompare(*key, *result))
        result = InsertAt(result, key);
    ScratchSlots<3>();
    return result;
}
