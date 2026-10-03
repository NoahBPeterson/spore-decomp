// Slice 0x0042D560..0x0042DDD2: unoptimized (/Od /Ob1) EASTL-style helpers shared with the
// neighbouring slice: hash node release, deque iterator/ptr-array helpers for 0x30-byte elements,
// vector<pair<int, RcPtr>>::operator=, uninitialized_copy wrapper, lower_bound and partial_sort.
#include "types.h"

extern "C" void* memcpy(void*, const void*, unsigned);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned);

void __cdecl EASTL_allocator_deallocate(void* p);   // 0x00F47380

// Unused stack slots of inlined helpers are reproduced with this (kept as in the original frames).
template <int N> inline void PadN() { uint32_t s[N]; }

// ---- ref-counted pointer members -------------------------------------------------------------
struct VObj { virtual void Reserved(); virtual void Release(); };

struct VRcPtr {
    VObj* p;
    ~VRcPtr() { if (p) p->Release(); }
};

// Hash node: two key words, then a ref-counted pointer; freed through the EASTL allocator.
struct RcNode {
    uint32_t key0, key1;
    VRcPtr   value;
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};

struct NodeOwner {
    uint32_t pad;
    void FreeNode(RcNode* n);
};

inline void DeallocNode(void* q) { void* p = q; EASTL_allocator_deallocate(p); }

// @ 0x0042D560
void NodeOwner::FreeNode(RcNode* n)
{
    n->~RcNode();
    DeallocNode(n);
}

// ---- deque of 0x30-byte elements, 4 per subarray ---------------------------------------------
struct Item30 {
    uint32_t data[12];
    ~Item30();   // 0x00401F20
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};

// 16-byte deque iterator copied by value through an out-of-line copy constructor.
struct DequeIter {
    uint32_t a, b, c, d;
    DequeIter(const DequeIter& o);   // 0x00420050
};

struct Tag { char c; Tag() : c(0) {} };

void* __cdecl DequeCopyImpl3(void* out, DequeIter a, DequeIter b, DequeIter c);   // 0x0042EA00
void  __cdecl DequeCopyImpl2(void* out, DequeIter a, DequeIter b, DequeIter c);   // 0x0042EA50

// @ 0x0042D690
void* DequeCopyThunk3(void* out, DequeIter a, DequeIter b, DequeIter c)
{
    Tag t1;
    Tag t2;
    PadN<21>();
    DequeCopyImpl3(out, a, b, c);
    return out;
}

// @ 0x0042D6E0
void* DequeCopyThunk2(void* out, DequeIter a, DequeIter b, DequeIter c)
{
    Tag t1;
    Tag t2;
    PadN<21>();
    DequeCopyImpl2(out, a, b, c);
    return out;
}

struct Iter30 {
    Item30*  cur;     // +0
    Item30*  begin;   // +4
    Item30*  end;     // +8
    Item30** sub;     // +0xC
    void SetSubarray(Item30** p);
    Iter30& Advance(int n);
};

// @ 0x0042D650
void Iter30::SetSubarray(Item30** p)
{
    sub = p;
    begin = *p;
    end = begin + 4;
}

// @ 0x0042D5C0
Iter30& Iter30::Advance(int n)
{
    unsigned offset = (cur - begin) + n;
    if (offset < 4) {
        cur += n;
    } else {
        int d = (int)(offset + 0x1000000) / 4 - 0x400000;
        SetSubarray(sub + d);
        cur = begin + (offset - d * 4);
    }
    return *this;
}

void* __cdecl AllocateRaw(void* alloc, unsigned size, unsigned align, unsigned offset);   // 0x0042DEE0

struct Deque30 {
    Item30** ptrArray;     // +0x00
    uint32_t ptrArraySize; // +0x04
    Iter30   itBegin;      // +0x08
    Iter30   itEnd;        // +0x18
    uint32_t allocator;    // +0x28

    void     FreeSubarray(Item30* p);                 // 0x00569260
    void     DoPopBack();
    Item30*  AllocateSubarray();
    Item30** AllocatePtrArray(unsigned n);            // 0x0056A240
    void     FreePtrArray(Item30** p, unsigned n);    // 0x00502EB0
    void     DoReallocPtrArray(unsigned nAdditional, int side);
};

// @ 0x0042D730
void Deque30::DoPopBack()
{
    FreeSubarray(itEnd.begin);
    itEnd.SetSubarray(itEnd.sub - 1);
    itEnd.cur = itEnd.end - 1;
    Item30* p = itEnd.cur;
    p->~Item30();
}

// @ 0x0042D7A0
Item30* Deque30::AllocateSubarray()
{
    return (Item30*)AllocateRaw(&allocator, 0xc0, 4, 0);
}

inline const unsigned& MaxU(const unsigned& a, const unsigned& b) { return (a < b) ? b : a; }

// @ 0x0042D7D0
void Deque30::DoReallocPtrArray(unsigned nAdditionalCapacity, int allocationSide)
{
    int nSubarrays = (itEnd.sub - itBegin.sub) + 1;
    unsigned nNeed = nSubarrays + nAdditionalCapacity;
    Item30** pPtrArrayBegin;
    if (ptrArraySize <= nNeed * 2) {
        unsigned nNewPtrArraySize = ptrArraySize + 2 + MaxU(ptrArraySize, nAdditionalCapacity);
        Item30** pNewPtrArray = AllocatePtrArray(nNewPtrArraySize);
        pPtrArrayBegin = pNewPtrArray + (itBegin.sub - ptrArray) + (allocationSide == 0 ? nAdditionalCapacity : 0);
        if (ptrArray)
            memcpy(pPtrArrayBegin, itBegin.sub, (char*)(itEnd.sub + 1) - (char*)itBegin.sub);
        FreePtrArray(ptrArray, ptrArraySize);
        ptrArray = pNewPtrArray;
        ptrArraySize = nNewPtrArraySize;
    } else {
        pPtrArrayBegin = ptrArray + ((ptrArraySize - nNeed) >> 1) + (allocationSide == 0 ? nAdditionalCapacity : 0);
        if (pPtrArrayBegin < itBegin.sub)
            memcpy(pPtrArrayBegin, itBegin.sub, (char*)(itEnd.sub + 1) - (char*)itBegin.sub);
        else
            memmove(pPtrArrayBegin + nSubarrays - ((itEnd.sub + 1) - itBegin.sub), itBegin.sub,
                    (char*)(itEnd.sub + 1) - (char*)itBegin.sub);
    }
    itBegin.SetSubarray(pPtrArrayBegin);
    itEnd.SetSubarray(pPtrArrayBegin + nSubarrays - 1);
}

// ---- vector of { key, ref-counted pointer } (8 bytes) ----------------------------------------
namespace Resource { struct ThreadedObject { void Release(); }; }

struct RcPtr {
    Resource::ThreadedObject* p;
    ~RcPtr() { if (p) p->Release(); }
};

struct RcEntry {
    uint32_t key;
    RcPtr    obj;
    RcEntry& operator=(const RcEntry&);   // 0x0042F8B0
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};

RcEntry* __cdecl UninitCopyEntries(RcEntry* first, RcEntry* last, RcEntry* dest);   // 0x0042DCC0

struct RcVector {
    RcEntry* begin;
    RcEntry* end;
    RcEntry* cap;
    RcVector& operator=(const RcVector& x);
    RcEntry* AllocateAndCopy(unsigned n, RcEntry* first, RcEntry* last);   // 0x0042EBA0
};

inline RcEntry* CopyEntries(RcEntry* first, RcEntry* last, RcEntry* dest)
{
    Tag a, w, t3;
    uint32_t pad[6];
    RcEntry* out = dest;
    RcEntry* src = first;
    for (; src != last; ++out, ++src) *out = *src;
    return out;
}

inline void DestroyEntries(RcEntry* first, RcEntry* last)
{
    for (; first < last; ++first) first->~RcEntry();
}

inline void FreeEntries(RcEntry* p, unsigned n)
{
    if (p) { RcEntry* q = p; EASTL_allocator_deallocate(q); }
}

// @ 0x0042D990
RcVector& RcVector::operator=(const RcVector& x)
{
    if (&x != this) {
        unsigned n = x.end - x.begin;
        if (n > (unsigned)(cap - begin)) {
            RcEntry* newBuf = AllocateAndCopy(n, x.begin, x.end);
            PadN<12>();
            DestroyEntries(begin, end);
            FreeEntries(begin, cap - begin);
            begin = newBuf;
            cap = begin + n;
        } else if (n > (unsigned)(end - begin)) {
            CopyEntries(x.begin, x.begin + (end - begin), begin);
            UninitCopyEntries(x.begin + (end - begin), x.end, end);
            PadN<12>();
        } else {
            RcEntry* mid = CopyEntries(x.begin, x.end, begin);
            PadN<3>();
            DestroyEntries(mid, end);
        }
        end = begin + n;
    }
    return *this;
}

// @ 0x0042DCC0
// Wrapper around the 0x0042EC30 uninitialized-copy implementation (tag type passed uninitialized).
// Not byte-exact: frame has one more dword / the tag byte lands at a different slot.
struct UTag { char c; };
void __cdecl UninitCopyImpl(RcEntry** out, RcEntry* a, RcEntry* b, RcEntry* c, UTag t);   // 0x0042EC30

RcEntry* __cdecl UninitCopyEntries(RcEntry* first, RcEntry* last, RcEntry* dest)
{
    RcEntry* pRet;
    UTag t;
    UTag u;
    RcEntry* c2 = dest;
    RcEntry* bb = last;
    RcEntry* a2 = first;
    UninitCopyImpl(&pRet, a2, bb, c2, t);
    PadN<6>();
    return pRet;
}

// ---- lower_bound over { int key, value } (8-byte) elements -----------------------------------
struct KeyPair { int key; void* value; };

inline bool LessInt(const int& a, const int& b) { return a < b; }

// @ 0x0042DD00
KeyPair* LowerBound(KeyPair* first, KeyPair* last, const KeyPair& value)
{
    int n = last - first;
    while (n > 0) {
        KeyPair* mid = first;
        int half = n >> 1;
        mid += half;
        if (LessInt(mid->key, value.key)) { ++mid; first = mid; n = n - (half + 1); }
        else n = half;
    }
    PadN<1>();
    return first;
}

// ---- partial_sort over 12-byte elements keyed by an unsigned first word ----------------------
struct Elem12 { uint32_t key, b, c; };
struct Compare { char c; };
void __cdecl MakeHeap(Elem12* first, Elem12* last, Compare c);                                   // 0x0042EDD0
void __cdecl AdjustHeap(Elem12* first, int top, int size, int node, Elem12 value, Compare c);   // 0x0042EE60

inline bool Less12(const Elem12& a, const Elem12& b) { return a.key < b.key; }

// @ 0x0042DD80
void PartialSort(Elem12* first, Elem12* middle, Elem12* last, Compare comp)
{
    MakeHeap(first, middle, comp);
    for (Elem12* i = middle; i < last; i += 1) {
        if (Less12(*i, *first)) {
            Elem12 tmp = *i;
            *i = *first;
            AdjustHeap(first, 0, middle - first, 0, tmp, comp);
        }
    }
    {
        Elem12 value;
        Compare cmp = comp;
        Elem12* last2 = middle;
        for (; (last2 - first) > 1; last2 -= 1) {
            value = last2[-1];
            last2[-1] = *first;
            AdjustHeap(first, 0, (last2 - first) - 1, 0, value, cmp);
        }
    }
}
