// EASTL-style containers in an unoptimized module (/Od /Ob1, every local in memory).
//   0x0042ab80  Deque::DoInit                 (byte-exact)
//   0x0042ac80  HashNodeOwner::ClearBuckets   (byte-exact)
//   0x0042ad20  IdPtrVecBase copy constructor (near match, local slot order differs)
//   0x0042adf0  uninitialized move of IdPtrVec elements (near match)
//   0x0042aeb0  vector<RefPtr>::DoInsertValues (behavioral only)
//   0x0042b2d0  introsort loop over 12-byte keyed records (behavioral only, slot layout differs)

#include "types.h"
extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
#pragma intrinsic(memcpy)

inline void* operator new(unsigned int, void* p) { return p; }

struct Allocator { const char* mpName; };

// At /Od every local of an inlined helper keeps a stack slot; unused slots are reproduced with this.
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
template<> inline void ScratchSlots<0>() {}

// Thin iterator wrapper (EASTL generic_iterator): by-value arguments get stack temporaries.
template <typename T> struct gi
{
    T* it;
    explicit gi(T* x) : it(x) {}
};
struct Tag {};
struct TagB { char c; TagB() : c(0) {} };

void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate

// ---------------------------------------------------------------------------------------------
// Deque (subarrays of 4 elements of 0x30 bytes)
// ---------------------------------------------------------------------------------------------
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct DequeIter
{
    char* mpCurrent; char* mpBegin; char* mpEnd; char** mpCurrentArrayPtr;
    void SetSubarray(char** p);   // FUN_0042d650
};

struct Deque
{
    char** mpPtrArray;
    uint32_t mnPtrArraySize;
    DequeIter mItBegin;
    DequeIter mItEnd;
    char** DoAllocatePtrArray(uint32_t n);   // FUN_0056a240
    char* DoAllocateSubarray();              // FUN_0042d7a0
    void DoInit(uint32_t nElements);
};

// @ 0x0042ab80
void Deque::DoInit(uint32_t nElements)
{
    const uint32_t nNewPtrArraySize = (nElements / 4) + 1;
    const uint32_t kDequeInitialPtrArraySize = 8;
    mnPtrArraySize = Max(kDequeInitialPtrArraySize, nNewPtrArraySize + 2);
    mpPtrArray = DoAllocatePtrArray(mnPtrArraySize);
    char** pPtrArrayBegin = mpPtrArray + ((mnPtrArraySize - nNewPtrArraySize) / 2);
    char** pPtrArrayEnd = pPtrArrayBegin + nNewPtrArraySize;
    char** pPtrArrayCurrent = pPtrArrayBegin;
    while (pPtrArrayCurrent < pPtrArrayEnd)
    {
        *pPtrArrayCurrent = DoAllocateSubarray();
        ++pPtrArrayCurrent;
    }
    mItBegin.SetSubarray(pPtrArrayBegin);
    mItBegin.mpCurrent = mItBegin.mpBegin;
    mItEnd.SetSubarray(pPtrArrayEnd - 1);
    mItEnd.mpCurrent = mItEnd.mpBegin + (nElements % 4) * 0x30;
}

// ---------------------------------------------------------------------------------------------
// Hash table bucket clearing (nodes hold a ThreadedObject reference)
// ---------------------------------------------------------------------------------------------
struct ThreadedObject { void Release(); };   // Resource::ThreadedObject::Release
struct HashNode { ThreadedObject* obj; uint32_t key; HashNode* next; };

inline void DestroyNode(HashNode* n, int flags)
{
    ScratchSlots<3>();
    if (n->obj) n->obj->Release();
    if (flags & 1) AllocatorDeallocate(n);
}
inline void FreeNode(void* p) { void* q = p; AllocatorDeallocate(q); }

struct HashNodeOwner { void ClearBuckets(HashNode** buckets, uint32_t count); };

// @ 0x0042ac80
void HashNodeOwner::ClearBuckets(HashNode** buckets, uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        HashNode* node = buckets[i];
        while (node)
        {
            HashNode* p = node;
            node = node->next;
            DestroyNode(p, 0);
            FreeNode(p);
        }
        buckets[i] = 0;
    }
}

// ---------------------------------------------------------------------------------------------
// IdPtrVec: 0x18-byte element = vector of 8-byte records (+0x10 pad, +0x14 flag byte)
// ---------------------------------------------------------------------------------------------
struct Pair { uint32_t a, b; };

struct IdPtrVecBase
{
    Pair* mBegin; Pair* mEnd; Pair* mCapacity; Allocator mAllocator;
    IdPtrVecBase(const IdPtrVecBase& o);   // FUN_0042ad20
    void Dtor();                           // IdPtrVec_dtor (0x00421190)
};
struct IdPtrVec : IdPtrVecBase
{
    uint32_t pad;
    uint8_t flag;
    IdPtrVec(const IdPtrVec& o) : IdPtrVecBase(o) { flag = o.flag; }
};

gi<Pair> __cdecl UninitCopyPairs(gi<const Pair> a, gi<const Pair> b, gi<Pair> c, Tag t);   // FUN_0042ec30

inline gi<Pair> UninitCopyW(const Pair* a, const Pair* b, Pair* c)
{
    ScratchSlots<6>();
    gi<Pair> gc(c);
    gi<const Pair> gb(b);
    gi<const Pair> ga(a);
    Tag t;
    return UninitCopyPairs(ga, gb, gc, t);
}

inline void DestroyElem(IdPtrVec* p, int flags)
{
    p->Dtor();
    if (flags & 1) AllocatorDeallocate(p);
}

template<int N, int M> struct MoveHelpers
{
    static inline IdPtrVec* CopyImpl(IdPtrVec* first, IdPtrVec* last, IdPtrVec* dest)
    {
        ScratchSlots<N>();
        for (; first != last; ++first, ++dest) ::new (dest) IdPtrVec(*first);
        return dest;
    }
    static inline void DestroyImpl(IdPtrVec* first, IdPtrVec* last, IdPtrVec* dest)
    {
        ScratchSlots<M>();
        for (; first != last; ++first, ++dest) DestroyElem(first, 0);
    }
};

// @ 0x0042adf0   (uninitialized_move: copy-construct [first,last) at dest, then destroy the sources)
IdPtrVec* __cdecl UninitializedMoveIdPtrVec(IdPtrVec* first, IdPtrVec* last, IdPtrVec* dest)
{
    IdPtrVec* result;
    TagB t1;
    result = MoveHelpers<9, 10>::CopyImpl(first, last, dest);
    TagB t2;
    MoveHelpers<9, 10>::DestroyImpl(first, last, dest);
    return result;
}

// @ 0x0042ad20
IdPtrVecBase::IdPtrVecBase(const IdPtrVecBase& o)
{
    int n = o.mEnd - o.mBegin;
    mBegin = n ? (Pair*)AllocatorAllocate(&mAllocator, n << 3, 4, 0) : 0;
    mEnd = mBegin;
    mCapacity = mBegin + n;
    mEnd = UninitCopyW(o.mBegin, o.mEnd, mBegin).it;
}

// ---------------------------------------------------------------------------------------------
// vector<RefPtr>::DoInsertValues  (behavioral only)
// ---------------------------------------------------------------------------------------------
struct RefObject { virtual void AddRef(); virtual void Release(); };
struct RefPtr
{
    RefObject* mp;
    RefPtr(const RefPtr& o) : mp(o.mp) { if (mp) mp->AddRef(); }
    RefPtr(RefObject* p);             // FUN_004535d0
    ~RefPtr() { if (mp) mp->Release(); }
};

gi<RefPtr> __cdecl UninitCopyPtrs(gi<const RefPtr> a, gi<const RefPtr> b, gi<RefPtr> c, Tag t);   // FUN_004e8ee0
void __cdecl FillRange(RefPtr* first, RefPtr* last, const RefPtr* value);                        // FUN_0042ece0
void __cdecl UninitFillN(RefPtr* dest, uint32_t n, const RefPtr* value, Tag t);                   // FUN_0042ed50
RefPtr* __cdecl CopyBackwardPtrs(RefPtr* first, RefPtr* last, RefPtr* destEnd);                   // FUN_004e8c80

struct RefPtrVec
{
    RefPtr* mBegin; RefPtr* mEnd; RefPtr* mCapacity; Allocator mAllocator;
    void DoInsertValues(RefPtr* pos, uint32_t n, const RefPtr& value);
};

// @ 0x0042aeb0
void RefPtrVec::DoInsertValues(RefPtr* pos, uint32_t n, const RefPtr& value)
{
    if (n <= (uint32_t)(mCapacity - mEnd))
    {
    if (n)
{
        const RefPtr temp(value);
        const uint32_t nExtra = mEnd - pos;
        RefPtr* const pOldEnd = mEnd;
        if (n < nExtra)
        {
            UninitCopyPtrs(gi<const RefPtr>(mEnd - n), gi<const RefPtr>(mEnd), gi<RefPtr>(mEnd), Tag());
            mEnd += n;
            RefPtr* src = pOldEnd - n;
            RefPtr* dst = pOldEnd;
            while (src != pos)
            {
                --src; --dst;
                new (dst) RefPtr(src->mp);
            }
            FillRange(pos, pos + n, &temp);
        }
        else
        {
            UninitFillN(mEnd, n - nExtra, &temp, Tag());
            mEnd += n - nExtra;
            CopyBackwardPtrs(pos, pOldEnd, mEnd);
            mEnd += nExtra;
            FillRange(pos, pOldEnd, &temp);
        }
    }
    }
    else
{
        const uint32_t nPrevSize = mEnd - mBegin;
        const uint32_t nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        const uint32_t nNewSize = (nGrowSize > nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        RefPtr* const pNewData = nNewSize ? (RefPtr*)AllocatorAllocate(&mAllocator, nNewSize * sizeof(RefPtr), 4, 0) : 0;
        RefPtr* pNewEnd = pNewData;
        pNewEnd = (RefPtr*)memcpy(pNewData, mBegin, (char*)pos - (char*)mBegin) + (pos - mBegin);
        UninitFillN(pNewEnd, n, &value, Tag());
        pNewEnd = (RefPtr*)memcpy(pNewEnd + n, pos, (char*)mEnd - (char*)pos) + (mEnd - pos);
        if (mBegin && ((uint32_t*)mBegin)[-1])
            AllocatorDeallocate(mBegin);
        mBegin = pNewData;
        mEnd = pNewEnd;
        mCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------------------------
// Introsort over 12-byte records keyed by the first word (behavioral only)
// ---------------------------------------------------------------------------------------------
// @ 0x0042b2d0
struct Elem12 { uint32_t key, b, c; };
struct Less { char c; };
inline bool LessCmp(const Elem12& a, const Elem12& b) { return a.key < b.key; }
void __cdecl PartialSortHeap(Elem12* first, Elem12* last, Elem12* last2, Less cmp);   // FUN_0042dd80
inline const Elem12* MedianOf3(const Elem12* a, const Elem12* b, const Elem12* c, Less cmp)
{
    if (LessCmp(*a, *b))
    {
        if (LessCmp(*b, *c)) return b;
        else if (LessCmp(*a, *c)) return c;
        else return a;
    }
    else if (LessCmp(*a, *c)) return a;
    else if (LessCmp(*b, *c)) return c;
    else return b;
}
inline Elem12* Partition(Elem12* first, Elem12* last, Elem12 pivot, Less cmp)
{
    for (;; ++first)
    {
        while (LessCmp(*first, pivot)) ++first;
        --last;
        while (LessCmp(pivot, *last)) --last;
        if (!(first < last)) return first;
        Elem12 t = *first; *first = *last; *last = t;
    }
}
void __cdecl IntroSortLoop(Elem12* first, Elem12* last, int depthLimit, Less cmp);
void __cdecl IntroSortLoop(Elem12* first, Elem12* last, int depthLimit, Less cmp)
{
    while (((last - first) > 28) && (depthLimit > 0))
    {
        Less c1 = cmp;
        const Elem12* mid = MedianOf3(first, first + (last - first) / 2, last - 1, c1);
        Elem12* cut = Partition(first, last, *mid, cmp);
        --depthLimit;
        IntroSortLoop(cut, last, depthLimit, cmp);
        last = cut;
    }
    if (depthLimit == 0)
        PartialSortHeap(first, last, last, cmp);
}
