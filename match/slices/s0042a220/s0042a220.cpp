// Slice 0x0042A220..0x0042AB70: unoptimized (/Od /Ob1) EASTL-style helpers:
// vector<RcPtr>::DoInsertValues, uninitialized_move for 0x7C / 0x20 byte elements,
// hash-table bucket clearing, deque iterator helpers and deque push_front/push_back/pop_back.
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }

void AllocDeallocate(void* p);                                        // EASTL allocator deallocate 0x00F47380

// ---- elements -------------------------------------------------------------------------------
template <int N> inline void PadN() { uint32_t s[N]; }

struct Elem7c {
    char pad[0x7C];
    Elem7c(const Elem7c&);   // 0x00422FD0
    ~Elem7c();               // 0x0041F2D0
};

struct Elem20 {
    uint32_t pad[8];
    Elem20(const Elem20&);   // 0x00423080
};

struct Elem30 {
    uint32_t pad[12];
    Elem30(const Elem30&);   // 0x004063D0
    ~Elem30();               // 0x00401F20
};

// ---- uninitialized_move for Elem7c / Elem20 ------------------------------------------------
void DestroyRange20(Elem20* first, Elem20* last, Elem20* dest);   // 0x0042E9A0

struct TagA { char c; TagA() : c(0) {} };
struct TagB { char c; TagB() : c(0) {} };

inline Elem7c* UninitCopy7c(Elem7c* first, Elem7c* last, Elem7c* dest, const TagA&)
{
    PadN<5>();
    for (; first != last; ++first, ++dest) { new (dest) Elem7c(*first); }
    return dest;
}
inline void DestroyRange7c(Elem7c* first, Elem7c* last, Elem7c* dest, const TagB&)
{
    PadN<5>();
    for (; first != last; ++first, ++dest) first->~Elem7c();
}

// @ 0x0042A680
Elem7c* UninitMove7c(Elem7c* first, Elem7c* last, Elem7c* dest)
{
    Elem7c* ret = UninitCopy7c(first, last, dest, TagA());
    PadN<1>();
    DestroyRange7c(first, last, dest, TagB());
    return ret;
}

inline Elem20* UninitCopy20(Elem20* first, Elem20* last, Elem20* dest, const TagA&)
{
    PadN<1>();
    for (; first != last; ++first, ++dest) { new (dest) Elem20(*first); }
    return dest;
}

inline void DestroyRange20Tag(Elem20* first, Elem20* last, Elem20* dest, const TagB&)
{
    DestroyRange20(first, last, dest);
}

// @ 0x0042A730
Elem20* UninitMove20(Elem20* first, Elem20* last, Elem20* dest)
{
    Elem20* ret = UninitCopy20(first, last, dest, TagA());
    PadN<2>();
    DestroyRange20Tag(first, last, dest, TagB());
    return ret;
}

// ---- hash table ----------------------------------------------------------------------------
struct HashNode { uint32_t pad[4]; HashNode* next; };

struct HashTable {
    void FreeNode(HashNode* n);        // 0x0042D560
    void ClearBuckets(HashNode** buckets, unsigned count);
};

// @ 0x0042A7B0
void HashTable::ClearBuckets(HashNode** buckets, unsigned count)
{
    for (unsigned i = 0; i < count; ++i) {
        HashNode* node = buckets[i];
        while (node) {
            HashNode* cur = node;
            node = node->next;
            FreeNode(cur);
        }
        buckets[i] = 0;
    }
    PadN<2>();
}

// ---- deque iterator (16 bytes) --------------------------------------------------------------
struct DequeIter {
    uint32_t a, b, c, d;
    DequeIter(const DequeIter& o);               // 0x00420050
    DequeIter(const DequeIter& o, int);
    DequeIter& operator++();                      // 0x004253C0
    DequeIter& operator+=(int n);                 // 0x0042D5C0
    DequeIter operator+(int n) const;
    void* Func3(DequeIter* out, const DequeIter& p1, const DequeIter& p2, int);
    void Func2(const DequeIter& p1, const DequeIter& p2, int);
};
void* Impl3(void* out, DequeIter a, DequeIter b, DequeIter c);    // 0x0042D690
void  Impl2(void* out, DequeIter a, DequeIter b, DequeIter c);    // 0x0042D6E0

// @ 0x0042A820
DequeIter::DequeIter(const DequeIter& o, int)
{
    a = o.a; b = o.b; c = o.c; d = o.d;
    ++*this;
}

// @ 0x0042A870
DequeIter DequeIter::operator+(int n) const
{
    return DequeIter(DequeIter(*this) += n);
}

// @ 0x0042A8B0
void* DequeIter::Func3(DequeIter* out, const DequeIter& p1, const DequeIter& p2, int)
{
    PadN<25>();
    Impl3(out, p1, p2, *this);
    return out;
}

// @ 0x0042A900
void DequeIter::Func2(const DequeIter& p1, const DequeIter& p2, int)
{
    uint32_t out[7];
    PadN<22>();
    Impl2(out, p1, p2, *this);
}

// ---- deque of Elem30 ----------------------------------------------------------------------
struct Iter30 {
    Elem30*  cur;     // +0
    Elem30*  begin;   // +4
    Elem30*  end;     // +8
    Elem30** sub;     // +0xC
    void SetSubarray(Elem30** p);                // 0x0042D650
};

struct Deque30 {
    Elem30** mpPtrArray;     // +0x00
    int      mnPtrArraySize; // +0x04
    Iter30   mItBegin;       // +0x08
    Iter30   mItEnd;         // +0x18
    uint32_t mAlloc;         // +0x28

    Elem30* AllocateSubarray();                  // 0x0042D7A0
    void ReallocSubarray(int n, int front);      // 0x0042D7D0
    void FreeSubarray(Elem30* p);                // 0x00569260
    void PopBackSub();                           // 0x0042D730
    void PopBack();
    void PopFront();
    void PushFront(const Elem30& v);
    void PushBack(const Elem30& v);
};

// @ 0x0042A950
void Deque30::PopBack()
{
    if (mItEnd.cur != mItEnd.begin) {
        --mItEnd.cur;
        Elem30* p = mItEnd.cur;
        p->~Elem30();
    } else {
        PopBackSub();
    }
}

// @ 0x0042A9B0
void Deque30::PushFront(const Elem30& v)
{
    Elem30 tmp(v);
    if (mItBegin.sub == mpPtrArray)
        ReallocSubarray(1, 0);
    mItBegin.sub[-1] = AllocateSubarray();
    mItBegin.SetSubarray(mItBegin.sub - 1);
    mItBegin.cur = mItBegin.end - 1;
    new (mItBegin.cur) Elem30(tmp);
    PadN<18>();
}

// @ 0x0042AA60
void Deque30::PushBack(const Elem30& v)
{
    Elem30 tmp(v);
    if ((mItEnd.sub - mpPtrArray) + 1 >= mnPtrArraySize)
        ReallocSubarray(1, 1);
    mItEnd.sub[1] = AllocateSubarray();
    new (mItEnd.cur) Elem30(tmp);
    mItEnd.SetSubarray(mItEnd.sub + 1);
    mItEnd.cur = mItEnd.begin;
    PadN<18>();
}

// @ 0x0042AB10
void Deque30::PopFront()
{
    Elem30* p = mItBegin.cur;
    p->~Elem30();
    FreeSubarray(mItBegin.begin);
    mItBegin.SetSubarray(mItBegin.sub + 1);
    mItBegin.cur = mItBegin.begin;
}

// ---- vector<RcPtr>::DoInsertValues: insert n copies of a ref-counted pointer at pos -------------------
// Not byte-exact: structure and instruction stream match (248 instructions), but a few of the
// /Od stack slots (hash-ordered local names, byte tag temps) still differ. See nonmatching.txt.
extern "C" void* memcpy(void*, const void*, size_t);

namespace RcVecImpl {
struct RcObj {
    int pad; int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    void Release();                       // 0x00453540
};
struct RcPtr {
    RcObj* p;
    RcPtr(const RcPtr& o) : p(o.p) { if (p) p->AddRef(); }
    ~RcPtr() { if (p) p->Release(); }
    void Reset(RcObj* v);                 // 0x0041CC60
    RcPtr& operator=(const RcPtr& o);     // 0x004E4350
};
struct Ret4 { RcPtr* p; };
struct Tag {};
struct Tag2 {};
struct TagA { char c; TagA() : c(0) {} };
struct TagB { char c; TagB() : c(0) {} };
struct TagT { bool c; TagT() : c(true) {} };
struct TagC { char c; TagC() : c(0) {} };

void MoveImpl(Ret4* out, RcPtr* first, RcPtr* last, RcPtr* dest, Tag t);      // 0x0042E860
void FillImpl(RcPtr* dest, size_t n, const RcPtr* v, Tag t);                    // 0x0042E910
RcPtr* MovePtr(RcPtr* first, RcPtr* last, RcPtr* dest);                         // 0x0042D520
void* AllocAllocate(void* alloc, size_t n, size_t align, size_t off);           // 0x0042DEE0
void AllocDeallocate(void* p);                                                  // 0x00F47380

struct VecRc {
    RcPtr* mpBegin; RcPtr* mpEnd; RcPtr* mpCapacity; uint32_t alloc;
    RcPtr* MoveA(RcPtr* f0, RcPtr* l0, RcPtr* d0) {
        Ret4 res; Tag2 pad; Tag tg;
        RcPtr* pOut = d0; RcPtr* last = l0; RcPtr* pFirst = f0;
        MoveImpl(&res, pFirst, last, pOut, tg);
        return res.p;
    }
    RcPtr* CopyBack(RcPtr* first, RcPtr* last, RcPtr* dest) {
        TagA a; TagB b; TagC c;
        while (last != first) { --last; --dest; dest->Reset(last->p); }
        return dest;
    }
    void FillN(RcPtr* dest, size_t n, const RcPtr& v) {
        Tag t;
        RcPtr* pDest = dest;
        FillImpl(pDest, n, &v, t);
    }
    RcPtr* PodMoveImpl(RcPtr* first, RcPtr* last, RcPtr* dest, const TagT&) {
        RcPtr* r = (RcPtr*)((last - first) * 4 + (int)memcpy(dest, first, (char*)last - (char*)first));
        return r;
    }
    RcPtr* PodMove(RcPtr* first, RcPtr* last, RcPtr* dest) {
        RcPtr* r = PodMoveImpl(first, last, dest, TagT());
        return r;
    }
    void DoFreeRange(RcPtr* p, size_t n) {
        if (p) {
            if (((int*)p)[-1]) { void* q = p; AllocDeallocate(q); }
        }
    }
    void FillA(RcPtr* first, RcPtr* last, const RcPtr& v) {
        PadN<2>();
        for (; first != last; ++first) *first = v;
    }
    void FillB(RcPtr* first, RcPtr* last, const RcPtr& v) {
        PadN<14>();
        for (; first != last; ++first) *first = v;
    }
    RcPtr* AllocN(size_t n) { return n ? (RcPtr*)AllocAllocate(&alloc, n * 4, 4, 0) : 0; }

    void DoInsertValues(RcPtr* position, size_t n, const RcPtr& value);
};

// @ 0x0042A220
void VecRc::DoInsertValues(RcPtr* position, size_t n, const RcPtr& value)
{
    if (n <= (size_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const RcPtr val = value;
            const size_t nExtra = mpEnd - position;
            RcPtr* const pOldEnd = mpEnd;
            if (n < nExtra) {
                MoveA(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                CopyBack(position, pOldEnd - n, pOldEnd);
                FillA(position, position + n, val);
            } else {
                FillN(mpEnd, n - nExtra, val);
                mpEnd += n - nExtra;
                MovePtr(position, pOldEnd, mpEnd);
                mpEnd += nExtra;
                FillB(position, pOldEnd, val);
            }
        }
    } else {
        const size_t nPrevSize = mpEnd - mpBegin;
        const size_t nGrowSize = nPrevSize > 0 ? 2 * nPrevSize : 1;
        const size_t nNewSize = nGrowSize > nPrevSize + n ? nGrowSize : nPrevSize + n;
        RcPtr* const pNewData = AllocN(nNewSize);
        RcPtr* pNewEnd = PodMove(mpBegin, position, pNewData);
        FillN(pNewEnd, n, value);
        pNewEnd = PodMove(position, mpEnd, pNewEnd + n);
        DoFreeRange(mpBegin, mpCapacity - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

}  // namespace RcVecImpl
