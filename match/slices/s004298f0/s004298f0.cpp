// Slice s004298f0: EASTL vector internals in an unoptimized module (/Od /Ob1 /MD /Gy /TP, no EH).
//   0x004298f0  Vec56::DoInsertValues    vector of 0x38-byte records, insert(pos, n, value)   (not byte-exact)
//   0x00429ce0  UninitCopy56             uninitialized_copy of 0x38-byte records             (not byte-exact)
//   0x00429d80  UninitCopyIt56           uninitialized_copy, iterator-wrapper overload        (byte-exact)
//   0x00429e00  RefVector::DoInsertN     vector of intrusive refs, insert(pos, n, value)      (not byte-exact)
//
// /Od notes learned here:
//  - padfn(): an inline helper with an unused local array reproduces the dead stack slots that nested
//    EASTL inline layers leave behind (UninitCopyIt56 needs one 14-word block, matching a 0x38-byte slot).
//  - GIt / GRef stand for eastl::generic_iterator: passed by value, so each call site copy-constructs
//    three temporaries, which is why the pointers hop through two stack slots before being pushed.
//  - The empty `tag` struct stands for eastl::is_pod<>/true_type temporaries (one uninitialised byte slot).
//  - Stack slot ORDER inside one inline expansion depends on local names (symbol hash order), so the
//    remaining diffs in DoInsertValues/DoInsertN/UninitCopy56 are dead-slot layout, not logic.
#include <new>
#include <string.h>
#include <intrin.h>
typedef unsigned int uint32_t;

struct Alloc { int unused; };
void* __cdecl AllocatorAllocate(Alloc* a, unsigned size, unsigned align, unsigned off);
void __cdecl EASTL_allocator_deallocate(void* p);

struct tag { tag() {} };

// ===================== Vec56 =====================
struct Rec56 {
    uint32_t d[14];
    Rec56() {}
    Rec56(const Rec56& o) throw();            // 0x40ce80
    Rec56& operator=(const Rec56& o) throw(); // 0x537dc0
};


struct GIt {
    Rec56* mIterator;
    GIt(Rec56* const& x) : mIterator(x) {}
    Rec56& operator*() const { return *mIterator; }
    GIt& operator++() { ++mIterator; return *this; }
};
inline bool operator!=(GIt a, GIt b) { return a.mIterator != b.mIterator; }
inline void padfn() { uint32_t pad[14]; }

// @ 0x00429d80
GIt __cdecl UninitCopyIt56(GIt first, GIt last, GIt dest, tag)
{
    GIt currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        ::new((void*)&*currentDest) Rec56(*first);
    padfn();
    return currentDest;
}

inline void padfn13() { uint32_t pad[13]; }
inline Rec56* uc_impl1(Rec56* first, Rec56* last, Rec56* dest) {
    padfn13();
    Rec56* currentDest = dest; Rec56* it = first;
    for (; it != last; ++it, ++currentDest) { ::new((void*)&*currentDest) Rec56(*it); }
    return currentDest;
}
inline void uc_impl2(Rec56* first, Rec56* last, Rec56* dest) {
    Rec56* d2 = dest; Rec56* f2 = first;
    for (; f2 != last; ++f2, ++d2) {}
}
// @ 0x00429ce0  (nonmatching: stack slot layout only)
Rec56* __cdecl UninitCopy56(Rec56* first, Rec56* last, Rec56* dest)
{
    Rec56* result;
    const bool b = false;
    result = uc_impl1(first, last, dest);
    const bool b2 = false;
    uc_impl2(first, last, dest);
    return result;
}

void __cdecl FillN56(GIt first, unsigned n, const Rec56* value, tag);          // 0x42e680
Rec56* __cdecl UninitCopyA56(Rec56* first, Rec56* last, Rec56* dest);               // 0x42e510

inline void uninitialized_fill_n56(Rec56* first, uint32_t n, const Rec56& value)
{
    FillN56(GIt(first), n, &value, tag());
}
inline void uninitialized_copy_it56(Rec56* first, Rec56* last, Rec56* result)
{
    const GIt i(UninitCopyIt56(GIt(first), GIt(last), GIt(result), tag()));
}
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
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl56(first, last, resultEnd);
}
inline void fill56(Rec56* first, Rec56* last, const Rec56& value)
{
    for (; first != last; ++first)
        *first = value;
}
struct Vec56 {
    Rec56* mpBegin; Rec56* mpEnd; Rec56* mpCapacity; Alloc mAllocator;
    inline Rec56* DoAllocate(uint32_t n) {
        return n ? (Rec56*)AllocatorAllocate(&mAllocator, n * sizeof(Rec56), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        if (((uint32_t*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); }
    }
    inline void DoFree(Rec56* p, uint32_t n) { if (p) deallocate(p, n * sizeof(Rec56)); }
    void DoInsertValues(Rec56* position, uint32_t n, const Rec56& value);
};

// @ 0x004298f0  (nonmatching: stack slot layout only)
void Vec56::DoInsertValues(Rec56* position, uint32_t n, const Rec56& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Rec56 temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Rec56* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_it56(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward56(position, pEnd - n, pEnd);
                fill56(position, position + n, temp);
            } else {
                uninitialized_fill_n56(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                UninitCopyA56(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill56(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Rec56* const pNewData = DoAllocate(nNewSize);
        Rec56* pNewEnd = UninitCopy56(mpBegin, position, pNewData);
        uninitialized_fill_n56(pNewEnd, n, value);
        pNewEnd = UninitCopy56(position, mpEnd, pNewEnd + n);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ===================== RefVector: vector of intrusive refs =====================
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)
struct ThreadedObject {
    void* vtable; volatile long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();
};
struct Ref {
    ThreadedObject* p;
    Ref(const Ref& o) : p(o.p) { if (p) p->AddRef(); }
    ~Ref() { if (p) p->Release(); }
    Ref& operator=(ThreadedObject* x);       // 0x41d8b0
};
struct GRef {
    Ref* mIterator;
    GRef(Ref* const& x) : mIterator(x) {}
};
GRef __cdecl UninitMoveRef(GRef first, GRef last, GRef dest, tag);       // 0x47c800
void __cdecl FillNRef(GRef first, unsigned n, Ref* value, tag);          // 0x42e7e0
Ref* __cdecl UninitCopyRefs(Ref* first, Ref* last, Ref* dest);           // 0x423f50
void __cdecl FillRef(Ref* first, Ref* last, Ref* value);                  // 0x42d430

inline void uninitialized_copy_it(Ref* first, Ref* last, Ref* result)
{
    UninitMoveRef(GRef(first), GRef(last), GRef(result), tag());
}
inline void uninitialized_fill_n_ref(Ref* first, uint32_t n, Ref* value)
{
    FillNRef(GRef(first), n, value, tag());
}
inline Ref* copy_backward_impl(Ref* first, Ref* last, Ref* resultEnd)
{
    while (last != first) {
        --last;
        --resultEnd;
        *resultEnd = last->p;
    }
    return resultEnd;
}
inline Ref* copy_backward_r(Ref* first, Ref* last, Ref* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl(first, last, resultEnd);
}
inline Ref* copy_memcpy(Ref* first, Ref* last, Ref* result)
{
    return (Ref*)memcpy(result, first, (uint32_t)((char*)last - (char*)first)) + (last - first);
}
inline Ref* uninitialized_copy_ptr(Ref* first, Ref* last, Ref* result)
{
    const bool bA = true;
    Ref* p = copy_memcpy(first, last, result);
    const bool bB = true;
    return p;
}

struct RefVector {
    Ref* mpBegin; Ref* mpEnd; Ref* mpCapacity; Alloc mAllocator;
    inline Ref* DoAllocate(uint32_t n) {
        return n ? (Ref*)AllocatorAllocate(&mAllocator, n * sizeof(Ref), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        if (((uint32_t*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); }
    }
    inline void DoFree(Ref* p, uint32_t n) { if (p) deallocate(p, n * sizeof(Ref)); }
    void DoInsertN(Ref* position, uint32_t n, Ref* value);
};

// @ 0x00429e00  (nonmatching: stack slot layout only)
void RefVector::DoInsertN(Ref* position, uint32_t n, Ref* value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Ref temp(*value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Ref* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_it(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_r(position, pEnd - n, pEnd);
                FillRef(position, position + n, (Ref*)&temp);
            } else {
                uninitialized_fill_n_ref(mpEnd, n - nExtra, (Ref*)&temp);
                mpEnd += n - nExtra;
                UninitCopyRefs(position, pEnd, mpEnd);
                mpEnd += nExtra;
                FillRef(position, pEnd, (Ref*)&temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Ref* const pNewData = DoAllocate(nNewSize);
        Ref* pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
        uninitialized_fill_n_ref(pNewEnd, n, value);
        pNewEnd = uninitialized_copy_ptr(position, mpEnd, pNewEnd + n);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
