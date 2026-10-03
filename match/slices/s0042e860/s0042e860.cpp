// EASTL-style range helpers (uninitialized copy/fill, copy-assign, destroy, heap sift)
// instantiated for ref-counted pointers and small POD records. Unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE (frame pointer, every local in memory).

#include <intrin.h>
typedef unsigned int uint32_t;

#include <new>

// Project placement new used for non-trivial types: the result goes through a local at /Od.
inline void* operator new(unsigned int, void* p, int) { void* r = p; return r; }
inline void operator delete(void*, void*, int) {}
#define PLACE_NEW(p) new (p, 0)

// ---------------------------------------------------------------------------
// Ref-counted types
// ---------------------------------------------------------------------------
// Plain counted object: count at +4 (non-atomic).
struct Counted {
    int mVtbl;
    int mRefCount;
    int AddRef() { return mRefCount++ + 1; }
};

struct CountedPtr {
    Counted* mp;
    CountedPtr(const CountedPtr& o) : mp(o.mp) { if (mp) mp->AddRef(); }
};

// Atomic ref-counted object (AtomicRefCounted): count at +8, Release is out of line.
struct AtomicCounted {
    int mVtbl;
    int mPad;
    int mRefCount;
    void AddRef() { _InterlockedIncrement((long*)&mRefCount); }
    void Release();  // 0x00402420
};

struct AtomicPtr {
    AtomicCounted* mp;
};

// Interface with virtual AddRef (slot 0) / Release (slot 1).
struct IRefCounted {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

struct IntrusivePtr {
    IRefCounted* mp;
    IntrusivePtr(const IntrusivePtr& o) : mp(o.mp) { if (mp) mp->AddRef(); }
    void Assign(IRefCounted* p)
    {
        if (p != mp) {
            IRefCounted* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
    }
};

// Small smart pointer to an atomic counted object whose count lives at +4.
struct AtomicCounted4 {
    int mVtbl;
    int mRefCount;
    void AddRef() { _InterlockedIncrement((long*)&mRefCount); }
};

struct AtomicPtr4 {
    AtomicCounted4* mp;
    AtomicPtr4(const AtomicPtr4& o) : mp(o.mp) { if (mp) mp->AddRef(); }
};

struct PairRec {  // 8 bytes
    int mKey;
    AtomicPtr4 mPtr;
};

struct OwnerRef {
    IRefCounted* mp;
    ~OwnerRef() { if (mp) mp->Release(); }
};

// ---------------------------------------------------------------------------
// Callees
// ---------------------------------------------------------------------------
struct StringRec {  // 16 bytes, by-value copy goes through 0x00420050
    uint32_t pad[4];
    StringRec(const StringRec&);
};
void* __cdecl AllocatorAllocate(void* allocator, unsigned int size, unsigned int align, unsigned int offset);  // 0x0042DEE0
void __cdecl EastlDeallocate(void* p);  // 0x00F47380

// ---------------------------------------------------------------------------
// Range helpers
// ---------------------------------------------------------------------------
template<class T> inline bool NotEqual(const T& a, const T& b) { return a != b; }
// Iterator dereference: the result reference lives in a temp at /Od.
template<class T> inline T& Deref(T* p) { return *p; }

// @ 0x0042E860
CountedPtr** __cdecl UninitializedCopyCounted(CountedPtr** out, CountedPtr* first, CountedPtr* last, CountedPtr* dest)
{
    CountedPtr* cur = dest;
    for (; NotEqual(first, last); ++first, ++cur) {
        PLACE_NEW(cur) CountedPtr(Deref(first));
    }
    *out = cur;
    return out;
}

// @ 0x0042E910
void __cdecl UninitializedFillCounted(CountedPtr* first, unsigned int n, CountedPtr* value)
{
    CountedPtr* p = first;
    for (; n > 0; --n, ++p) {
        PLACE_NEW(p) CountedPtr(*value);
    }
}

struct Elem32 {  // 0x20 bytes; owned object at +0x1c, released through vtable slot 1
    uint32_t pad[7];
    OwnerRef mOwner;
    static void operator delete(void* p) { EastlDeallocate(p); }
};

// @ 0x0042E9A0
Elem32* __cdecl DestroyElem32Range(Elem32* first, Elem32* last, Elem32* dest)
{
    for (; first != last; ++first, ++dest)
        first->~Elem32();
    return dest;
}

void __cdecl Callee42F490(StringRec* p, StringRec a, StringRec b, StringRec c);  // 0x0042F490
void __cdecl Callee42F4E0(StringRec* p, StringRec a, StringRec b, StringRec c);  // 0x0042F4E0

// Forwarding layers around the by-value string-record call (inlined at /Ob1; the seven
// layers account for the 0x60-byte frame).
inline void FwdA0(StringRec* p, StringRec a, StringRec b, StringRec c) { Callee42F490(p, a, b, c); }
inline void FwdA1(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdA0(p, a, b, c); }
inline void FwdA2(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdA1(p, a, b, c); }
inline void FwdA3(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdA2(p, a, b, c); }
inline void FwdA4(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdA3(p, a, b, c); }
inline void FwdA5(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdA4(p, a, b, c); }
inline void FwdA6(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdA5(p, a, b, c); }
inline void FwdB0(StringRec* p, StringRec a, StringRec b, StringRec c) { Callee42F4E0(p, a, b, c); }
inline void FwdB1(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdB0(p, a, b, c); }
inline void FwdB2(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdB1(p, a, b, c); }
inline void FwdB3(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdB2(p, a, b, c); }
inline void FwdB4(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdB3(p, a, b, c); }
inline void FwdB5(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdB4(p, a, b, c); }
inline void FwdB6(StringRec* p, StringRec a, StringRec b, StringRec c) { FwdB5(p, a, b, c); }

// @ 0x0042EA00
StringRec* __cdecl ForwardStringRecs3(StringRec* p, StringRec a, StringRec b, StringRec c)
{
    FwdA6(p, a, b, c);
    return p;
}

// @ 0x0042EA50
StringRec* __cdecl ForwardStringRecs3b(StringRec* p, StringRec a, StringRec b, StringRec c)
{
    FwdB6(p, a, b, c);
    return p;
}

// Note: /Od orders stack slots by local name, so the local names in the two functions below
// are chosen to reproduce the original frame layout.
// @ 0x0042EAA0
AtomicPtr* __cdecl CopyAssignAtomic(AtomicPtr* first, AtomicPtr* last, AtomicPtr* dest)
{
    bool tag = false;
    AtomicCounted* pNew;
    AtomicCounted* prev;
    AtomicPtr* out = dest;
    AtomicPtr* src = first;
    for (; src != last; ++out, ++src) {
        pNew = src->mp;
        if (pNew != out->mp) {
            prev = out->mp;
            if (pNew)
                pNew->AddRef();
            out->mp = pNew;
            if (prev)
                prev->Release();
        }
    }
    return out;
}

// @ 0x0042EB20
AtomicPtr* __cdecl CopyAssignAtomicBackward(AtomicPtr* first, AtomicPtr* last, AtomicPtr* destEnd)
{
    bool tag = false;
    AtomicCounted* pNew;
    AtomicCounted* prev;
    AtomicPtr* out = destEnd;
    AtomicPtr* src = last;
    while (src != first) {
        --src;
        --out;
        pNew = src->mp;
        if (pNew != out->mp) {
            prev = out->mp;
            if (pNew)
                pNew->AddRef();
            out->mp = pNew;
            if (prev)
                prev->Release();
        }
    }
    return out;
}

// Iterator wrapper passed by value through the forwarding layers.
struct PairIter {
    PairRec* mp;
};

struct PairAllocator {
    uint32_t pad[3];
    char mAllocator[4];
    PairRec* AllocateCopy(unsigned int n, PairIter first, PairIter last);
};
PairRec** __cdecl UninitializedCopyPairs(PairRec** out, PairRec* first, PairRec* last, PairRec* dest, char tag);

inline void CopyPairsInner(PairIter dest, PairIter last, PairIter first)
{
    PairRec* out;
    char tag;
    UninitializedCopyPairs(&out, first.mp, last.mp, dest.mp, tag);
}

inline void CopyPairsOuter(PairIter dest, PairIter last, PairIter first)
{
    CopyPairsInner(dest, last, first);
}

// @ 0x0042EBA0
PairRec* PairAllocator::AllocateCopy(unsigned int n, PairIter first, PairIter last)
{
    PairRec* mem;
    if (n)
        mem = (PairRec*)AllocatorAllocate(mAllocator, n << 3, 4, 0);
    else
        mem = 0;
    PairIter result;
    result.mp = mem;
    CopyPairsOuter(result, last, first);
    return result.mp;
}

// @ 0x0042EC30
PairRec** __cdecl UninitializedCopyPairs(PairRec** out, PairRec* first, PairRec* last, PairRec* dest)
{
    PairRec* cur = dest;
    for (; NotEqual(first, last); ++first, ++cur)
        PLACE_NEW(cur) PairRec(Deref(first));
    *out = cur;
    return out;
}

// @ 0x0042ECE0
void __cdecl CopyAssignIntrusive(IntrusivePtr* first, IntrusivePtr* last, IntrusivePtr* src)
{
    for (; first != last; ++first)
        first->Assign(src->mp);
}

// @ 0x0042ED50
void __cdecl UninitializedFillIntrusive(IntrusivePtr* first, unsigned int n, IntrusivePtr* value)
{
    IntrusivePtr* p = first;
    for (; n > 0; --n, ++p)
        PLACE_NEW(p) IntrusivePtr(*value);
}

// ---------------------------------------------------------------------------
// Heap of 12-byte records keyed by a uint
// ---------------------------------------------------------------------------
struct HeapRec {
    uint32_t mKey, mA, mB;
};
struct HeapLessFn {  // stateless comparator (an empty struct passed by value)
    bool operator()(const HeapRec& a, const HeapRec& b) const { return a.mKey < b.mKey; }
};

void __cdecl AdjustHeap(HeapRec* first, int top, int len, int hole, HeapRec value, HeapLessFn cmp);  // 0x0042EE60

// @ 0x0042EDD0
void __cdecl MakeHeap(HeapRec* first, HeapRec* last, HeapLessFn cmp)
{
    int len = (int)(last - first);
    if (len >= 2) {
        int parent = (len - 2 >> 1) + 1;
        do {
            --parent;
            HeapRec value = first[parent];
            AdjustHeap(first, parent, len, parent, value, cmp);
        } while (parent != 0);
    }
}

// Sift a value up from `position` toward `top` (inlined into AdjustHeap).
inline void PromoteHeap(HeapRec* first, int top, int position, HeapRec value, HeapLessFn cmp)
{
    int parent = (position - 1) >> 1;
    for (; position > top && cmp(first[parent], value); parent = (position - 1) >> 1) {
        first[position] = first[parent];
        position = parent;
    }
    first[position] = value;
}

// @ 0x0042EE60
void __cdecl AdjustHeap(HeapRec* first, int top, int len, int hole, HeapRec value, HeapLessFn cmp)
{
    int child = 2 * hole + 2;
    for (; child < len; child = 2 * child + 2) {
        if (cmp(first[child], first[child - 1]))
            --child;
        first[hole] = first[child];
        hole = child;
    }
    if (child == len) {
        first[hole] = first[child - 1];
        hole = child - 1;
    }
    PromoteHeap(first, top, hole, value, cmp);
}

// (Local names chosen to reproduce the original /Od slot order.)
// @ 0x0042EFC0
float** __cdecl UninitializedFillFloat(float** result, float* first, unsigned int count, float* pValue)
{
    unsigned int n = count;
    float* dst = first;
    float value = *pValue;
    for (; n-- > 0; ++dst)
        *dst = value;
    *result = dst;
    return result;
}

// ---------------------------------------------------------------------------
// 0x30-byte elements
// ---------------------------------------------------------------------------
struct Elem48 {
    uint32_t pad[12];
    Elem48(const Elem48&);  // 0x0042CBF0
};

// @ 0x0042F020
Elem48** __cdecl UninitializedCopyElem48(Elem48** out, Elem48* first, Elem48* last, Elem48* dest)
{
    Elem48* cur = dest;
    for (; NotEqual(first, last); ++first, ++cur)
        PLACE_NEW(cur) Elem48(Deref(first));
    *out = cur;
    return out;
}

// @ 0x0042F0A0
void __cdecl UninitializedFillElem48(Elem48* first, unsigned int n, Elem48* value)
{
    Elem48* p = first;
    for (; n > 0; --n, ++p)
        PLACE_NEW(p) Elem48(*value);
}

// @ 0x0042F100
void __cdecl UninitializedFillHeapRec(HeapRec* first, HeapRec* last, HeapRec* value)
{
    for (HeapRec* p = first; p != last; ++p)
        new (p) HeapRec(*value);
}
