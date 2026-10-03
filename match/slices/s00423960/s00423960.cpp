// EASTL-style vector support (unoptimized module: /Od /Ob1, frame pointers, every local in memory).
//   - Record56Vector      : vector of 0x38-byte records (DoInsertValue)
//   - CountedPtrVector    : vector of intrusive pointers whose refcount lives at +0x40 (DoInsertValue)
//   - AtomicPtrVector     : vector of intrusive pointers whose refcount lives at +4 (atomic add)
//   - ByteBuffer          : begin/end/cap triple allocated with an n-byte block
// Layout of every container: { T* mBegin; T* mEnd; T* mCapacity; Allocator mAllocator; }.

#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
#pragma intrinsic(memcpy)

struct Allocator { const char* mpName; };

// Allocator entry points (callees; resolved at link time).
void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------------------------------------
// Pointers to refcounted objects.
// ---------------------------------------------------------------------------------------------
struct AtomicRefCounted { int vtable; volatile long mnRefCount; };   // count at +4, atomic
struct Counted { char pad[0x40]; int mnRefCount; void Release(); };  // count at +0x40, plain; Release = FUN_0040f360
typedef AtomicRefCounted* AtomicPtr;
typedef Counted* CountedPtr;

extern "C" long _InterlockedIncrement(long volatile*);
#pragma intrinsic(_InterlockedIncrement)

inline bool NotEqual(AtomicPtr* a, AtomicPtr* b) { return a != b; }

// uninitialized_copy of intrusive pointers, adding a reference to each.
// @ 0x00423f50
AtomicPtr* __cdecl UninitializedCopyAtomic(AtomicPtr* first, AtomicPtr* last, AtomicPtr* dest)
{
    AtomicPtr* cur = dest;
    for (; NotEqual(first, last); ++first, ++cur)
    {
        AtomicPtr* p = cur;
        if (p)
        {
            *p = *first;
            if (*p)
            {
                AtomicPtr obj = *p;
                _InterlockedIncrement(&obj->mnRefCount);
            }
        }
    }
    return cur;
}

// ---------------------------------------------------------------------------------------------
// ByteBuffer: begin = (n ? allocate(n) : 0); end = begin; cap = begin + n.
// ---------------------------------------------------------------------------------------------
struct ByteBuffer
{
    char* mBegin;
    char* mEnd;
    char* mCapacity;
    Allocator mAllocator;

    ByteBuffer(uint32_t n, const Allocator* /*alloc*/);
};

// @ 0x00423be0
ByteBuffer::ByteBuffer(uint32_t n, const Allocator*)
{
    mBegin = n ? (char*)AllocatorAllocate(&mAllocator, n, 1, 0) : 0;
    mEnd = mBegin;
    mCapacity = mBegin + n;
}

// ---------------------------------------------------------------------------------------------
// AtomicPtrVector::DoAllocateAndCopy
// ---------------------------------------------------------------------------------------------
struct AtomicPtrVector
{
    AtomicPtr* mBegin;
    AtomicPtr* mEnd;
    AtomicPtr* mCapacity;
    Allocator mAllocator;

    AtomicPtr* DoAllocateAndCopy(uint32_t n, AtomicPtr* first, AtomicPtr* last);
};

// @ 0x00423ef0
AtomicPtr* AtomicPtrVector::DoAllocateAndCopy(uint32_t n, AtomicPtr* first, AtomicPtr* last)
{
    AtomicPtr* result = n ? (AtomicPtr*)AllocatorAllocate(&mAllocator, n * 4, 4, 0) : 0;
    ScratchSlots<13>();
    UninitializedCopyAtomic(first, last, result);
    return result;
}

// ---------------------------------------------------------------------------------------------
// CountedPtrVector::DoInsertValue(pos, value)
// ---------------------------------------------------------------------------------------------
CountedPtr* __cdecl CopyBackwardCounted(CountedPtr* first, CountedPtr* last, CountedPtr* destEnd);  // FUN_0042e6e0

struct CountedPtrVector
{
    CountedPtr* mBegin;
    CountedPtr* mEnd;
    CountedPtr* mCapacity;
    Allocator mAllocator;

    void DoInsertValue(CountedPtr* pos, CountedPtr* value);
};

// @ 0x00423c40
void CountedPtrVector::DoInsertValue(CountedPtr* pos, CountedPtr* value)
{
    if (mEnd != mCapacity)
    {
        CountedPtr* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        CountedPtr* slot = mEnd;
        if (slot)
        {
            *slot = mEnd[-1];
            if (*slot) ++(*slot)->mnRefCount;
        }

        CopyBackwardCounted(pos, mEnd - 1, mEnd);

        CountedPtr incoming = *v;
        if (incoming != *pos)
        {
            CountedPtr old = *pos;
            if (incoming) ++incoming->mnRefCount;
            *pos = incoming;
            if (old) old->Release();
        }
        ++mEnd;
    }
    else
    {
        int count = (int)(mEnd - mBegin);
        uint32_t newCount = count ? count * 2 : 1;
        CountedPtr* newBuf = newCount ? (CountedPtr*)AllocatorAllocate(&mAllocator, newCount * 4, 4, 0) : 0;

        CountedPtr* head = (CountedPtr*)memcpy(newBuf, mBegin, (char*)pos - (char*)mBegin);
        CountedPtr* ins = head + (pos - mBegin);
        if (ins)
        {
            *ins = *value;
            if (*ins) ++(*ins)->mnRefCount;
        }
        CountedPtr* tail = (CountedPtr*)memcpy(ins + 1, pos, (char*)mEnd - (char*)pos);
        CountedPtr* newEnd = tail + (mEnd - pos);

        if (mBegin && ((uint32_t*)mBegin)[-1])
            AllocatorDeallocate(mBegin);
        mBegin = newBuf;
        mEnd = newEnd;
        mCapacity = newBuf + newCount;
    }
}

// ---------------------------------------------------------------------------------------------
// Record56Vector::DoInsertValue(pos, value)   (element = 0x38-byte record)
// ---------------------------------------------------------------------------------------------
struct Record56
{
    uint32_t data[14];
    Record56* CopyConstruct(const Record56* src);   // FUN_0040ce80
    void Assign(const Record56* src);               // FUN_00537dc0
};
Record56* __cdecl   UninitializedCopyRecords(Record56* first, Record56* last, Record56* dest);  // FUN_00429ce0

struct Record56Vector
{
    Record56* mBegin;
    Record56* mEnd;
    Record56* mCapacity;
    Allocator mAllocator;

    void DoInsertValue(Record56* pos, const Record56* value);
};

// @ 0x00423960
void Record56Vector::DoInsertValue(Record56* pos, const Record56* value)
{
    if (mEnd != mCapacity)
    {
        const Record56* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        Record56* slot = mEnd;
        if (slot)
            slot->CopyConstruct(mEnd - 1);

        Record56* dst = mEnd;
        Record56* src = mEnd - 1;
        while (src != pos)
        {
            --src;
            --dst;
            dst->Assign(src);
        }
        pos->Assign(v);
        ++mEnd;
    }
    else
    {
        int count = (int)(mEnd - mBegin);
        uint32_t newCount = count ? count * 2 : 1;
        Record56* newBuf = newCount ? (Record56*)AllocatorAllocate(&mAllocator, newCount * sizeof(Record56), 4, 0) : 0;

        Record56* ins = UninitializedCopyRecords(mBegin, pos, newBuf);
        if (ins)
            ins->CopyConstruct(value);
        ins = ins + 1;
        Record56* newEnd = UninitializedCopyRecords(pos, mEnd, ins);

        int oldCapacity = (int)(mCapacity - mBegin);
        (void)oldCapacity;
        if (mBegin && ((uint32_t*)mBegin)[-1])
            AllocatorDeallocate(mBegin);
        mBegin = newBuf;
        mEnd = newEnd;
        mCapacity = newBuf + newCount;
    }
}
