// Slice s005688f0: eastl::deque<eastl::pair<int,int>> and eastl::vector helpers (unoptimized module).
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>
#include <string.h>

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);

// ---------------------------------------------------------------- pair<int,int>
struct Pair {
    int first;
    int second;
};

template <class T1, class T2>
inline T1* construct(T1* p, const T2& value) { return ::new((void*)p) T1(value); }

// ---------------------------------------------------------------- deque iterator
struct DequeIter {
    Pair* mpCurrent;    // +0
    Pair* mpFirst;      // +4
    Pair* mpLast;       // +8
    Pair** mpNode;      // +0xc

    void SetSubarray(Pair** p);      // @ 0x00569340
    DequeIter& operator--();         // @ 0x005692d0
    DequeIter& operator+=(int n);    // @ 0x0056a270
    bool operator!=(const DequeIter& o) const { return mpCurrent != o.mpCurrent; }
    Pair& operator*() const { return *mpCurrent; }
};

void DequeIter::SetSubarray(Pair** p)
{
    mpNode = p;
    mpFirst = *p;
    mpLast = mpFirst + 32;
}

DequeIter& DequeIter::operator--()
{
    if (mpCurrent == mpFirst) {
        --mpNode;
        mpFirst = *mpNode;
        mpLast = mpFirst + 32;
        mpCurrent = mpLast;
    }
    --mpCurrent;
    return *this;
}

// ---------------------------------------------------------------- deque base
struct DequeBase {
    Pair** mpPtrArray;      // +0
    int mnPtrArraySize;     // +4
    DequeIter mItBegin;     // +8
    DequeIter mItEnd;       // +0x18

    void Deallocate(void* p);                 // @ 0x00569260
    void FreeSubarrays(Pair** first, Pair** last); // @ 0x00569290
    void push_front(const Pair& value);       // @ 0x00568f00
    void push_back(const Pair& value);        // @ 0x00568f70
    void Insert(DequeIter position, const Pair& value); // @ 0x00568ff0
    void DoPushFront(const Pair& value);      // @ 0x00569d20
    void DoPushBack(const Pair& value);       // @ 0x00569dc0
};

void DequeBase::Deallocate(void* p)
{
    if (p) {
        void* q = p;
        EASTL_allocator_deallocate(q);
    }
}

void DequeBase::FreeSubarrays(Pair** first, Pair** last)
{
    while (first < last) {
        Deallocate(*first);
        ++first;
    }
}

void DequeBase::push_front(const Pair& value)
{
    if (mItBegin.mpCurrent == mItBegin.mpFirst)
        DoPushFront(value);
    else {
        --mItBegin.mpCurrent;
        construct(mItBegin.mpCurrent, value);
    }
}

void DequeBase::push_back(const Pair& value)
{
    if (mItEnd.mpCurrent + 1 == mItEnd.mpLast)
        DoPushBack(value);
    else {
        Pair* p = mItEnd.mpCurrent;
        ++mItEnd.mpCurrent;
        construct(p, value);
    }
}

// ---------------------------------------------------------------- eastl::vector helpers
struct Alloc { };

void* CopyN(void* dst, const void* first, unsigned nbytes);          // copy(first,last,dst)
void* UninitCopy(const void* first, const void* last, void* dst);    // uninitialized_copy

struct Vec4 {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    Alloc mAllocator;
    void* AllocCopy(size_t n, const int* first, const int* last);
    void DoAssign(const int* first, const int* last, bool tag);      // @ 0x00568d10
};

void Vec4::DoAssign(const int* first, const int* last, bool)
{
    unsigned n = (unsigned)(last - first);
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        int* p = (int*)AllocCopy(n, first, last);
        for (int* q = mpBegin; q < mpEnd; ++q) { }
        if (mpBegin)
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = p;
        mpEnd = p + n;
        mpCapacity = mpEnd;
    }
    else if ((unsigned)(mpEnd - mpBegin) < n) {
        const int* mid = first + (mpEnd - mpBegin);
        CopyN(mpBegin, first, (unsigned)((const char*)mid - (const char*)first));
        mpEnd = (int*)UninitCopy(mid, last, mpEnd);
    }
    else {
        int* p = (int*)CopyN(mpBegin, first, (unsigned)((const char*)last - (const char*)first));
        p += n;
        for (int* q = p; q < mpEnd; ++q) { }
        mpEnd = p;
    }
}

struct V8 { int a; int b; };
struct Vec8 {
    V8* mpBegin;
    V8* mpEnd;
    V8* mpCapacity;
    Alloc mAllocator;
    void* AllocCopy8(size_t n, const V8* first, const V8* last);
    void DoAssign(const V8* first, const V8* last, bool tag);        // @ 0x00569460
};

void Vec8::DoAssign(const V8* first, const V8* last, bool)
{
    unsigned n = (unsigned)(last - first);
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        V8* p = (V8*)AllocCopy8(n, first, last);
        for (V8* q = mpBegin; q < mpEnd; ++q) { }
        if (mpBegin)
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = p;
        mpEnd = p + n;
        mpCapacity = mpEnd;
    }
    else if ((unsigned)(mpEnd - mpBegin) < n) {
        const V8* mid = first + (mpEnd - mpBegin);
        CopyN(mpBegin, first, (unsigned)((const char*)mid - (const char*)first));
        mpEnd = (V8*)UninitCopy(mid, last, mpEnd);
    }
    else {
        V8* p = (V8*)CopyN(mpBegin, first, (unsigned)((const char*)last - (const char*)first));
        p += n;
        for (V8* q = p; q < mpEnd; ++q) { }
        mpEnd = p;
    }
}

struct V12 { char d[12]; };
struct Vec12 {
    V12* mpBegin;
    V12* mpEnd;
    V12* mpCapacity;
    Alloc mAllocator;
    void* AllocBytes(size_t bytes);
    void Insert(V12* position, const V12* first, const V12* last);   // @ 0x005688f0
};

void Vec12::Insert(V12* position, const V12* first, const V12* last)
{
    size_t n = last - first;
    if (n == 0)
        return;
    size_t size = mpEnd - mpBegin;
    if (n > (size_t)(mpCapacity - mpEnd)) {
        size_t newcap = size * 2;
        if (newcap < size + n)
            newcap = size + n;
        V12* p = (V12*)AllocBytes(newcap * 12);
        V12* q = p;
        memcpy(q, mpBegin, (size_t)((char*)position - (char*)mpBegin));
        q += position - mpBegin;
        memcpy(q, first, n * 12);
        q += n;
        memcpy(q, position, (size_t)((char*)mpEnd - (char*)position));
        q += mpEnd - position;
        if (mpBegin)
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = p;
        mpEnd = q;
        mpCapacity = p + newcap;
    }
    else {
        size_t after = mpEnd - position;
        memmove(position + n, position, after * 12);
        if (n <= after) {
            memcpy(position, first, n * 12);
        }
        else {
            memcpy(position, first, after * 12);
            memcpy(mpEnd, first + after, (n - after) * 12);
            mpEnd += n - after;
        }
    }
}

// ---------------------------------------------------------------- eastl::deque::insert (single)
void DequeBase::Insert(DequeIter position, const Pair& value)         // @ 0x00568ff0
{
    push_back(value);
    DequeIter it = mItEnd;
    --it;
    while (it != position) {
        DequeIter prev = it;
        --prev;
        *it = *prev;
        it = prev;
    }
    *position = value;
}

// ---------------------------------------------------------------- lower_bound over 8-byte keyed elements
struct KeyElem { float key; int value; };
struct KeyIter {
    KeyElem* mpCurrent; KeyElem* mpFirst; KeyElem* mpLast; KeyElem** mpNode;
    KeyIter& operator--();
    KeyIter operator+(int n) const;
    bool operator!=(const KeyIter& o) const { return mpCurrent != o.mpCurrent; }
    const KeyElem& operator*() const { return *mpCurrent; }
};

KeyIter& KeyIter::operator--()
{
    if (mpCurrent == mpFirst) {
        --mpNode;
        mpFirst = *mpNode;
        mpLast = mpFirst + 32;
        mpCurrent = mpLast;
    }
    --mpCurrent;
    return *this;
}

KeyIter KeyIter::operator+(int n) const
{
    KeyIter it = *this;
    it.mpCurrent += n;
    return it;
}

KeyIter LowerBound(KeyIter first, KeyIter last, const float& value)   // @ 0x00569380
{
    int n = (int)(last.mpCurrent - first.mpCurrent) / (int)sizeof(KeyElem);
    while (n > 0) {
        int half = n >> 1;
        KeyIter it = first + half;
        if (value > (*it).key) {
            first = it + 1;
            n -= half + 1;
        }
        else {
            n = half;
        }
    }
    return first;
}
