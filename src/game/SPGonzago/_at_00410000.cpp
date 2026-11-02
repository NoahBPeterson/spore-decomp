// src/game/SPGonzago/_at_00410000.cpp -- migrated from slice(s) s0041f940, s0041efb0, s0041e730 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00410000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)

// ---- items of slice s0041e730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
void __cdecl EASTL_allocator_deallocate(void* p);                                  // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }
struct Alloc { int unused; };
void* __cdecl AllocatorAllocate(Alloc* a, unsigned size, unsigned align, unsigned off);   // 0x0042dee0
struct ThreadedObject {
    void* vtable; volatile long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();                                                                // 0x00404f90
};
struct Ref {
    ThreadedObject* p;
    Ref(const Ref& o) : p(o.p) { if (p) p->AddRef(); }
    ~Ref() { if (p) p->Release(); }
};
Ref* __cdecl CopyRefs(Ref* first, Ref* last, Ref* dest);          // 0x0042d4a0
Ref* __cdecl UninitCopyRefs(Ref* first, Ref* last, Ref* dest);    // 0x00423f50
struct RefVectorBase {
    Ref* mpBegin; Ref* mpEnd; Ref* mpCap; Alloc alloc;
    ~RefVectorBase();                                                              // 0x00425990
};
struct RefVector : RefVectorBase {
    Ref* DoAllocateAndCopy(unsigned n, Ref* first, Ref* last);                     // 0x00423ef0
    void DoInsertValue(Ref* pos, const Ref& v);                                    // 0x00424430
    void DoInsertN(Ref* pos, unsigned n, Ref* val);                                // 0x00429e00
    void DoErase(Ref* first, Ref* last);                                           // 0x00426280
    Ref* DoAllocate(unsigned n) {
        int u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12;
        return n ? (Ref*)AllocatorAllocate(&alloc, n * 4, 4, 0) : 0;
    }
    void ins(Ref* pos, unsigned n, Ref* val) { DoInsertN(pos, n, val); }
    void er(unsigned n) {
        int u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12, u13, u14, u15, u16, u17;
        DoErase(mpBegin + n, mpEnd);
    }
    void tail() { int x, y, z; }
    RefVector(const RefVector& o);
    ~RefVector();
    RefVector& operator=(const RefVector& x);
    void resize(unsigned n);
    void push_back(const Ref& v);
};
inline void destructRefs(Ref* first, Ref* last) { int a, b, c; for (; first < last; ++first) first->~Ref(); }
inline void dealloc(Ref* p, unsigned n) { if (((int*)p)[-1]) { Ref* q = p; EASTL_allocator_deallocate(q); } }
inline void freeRefs(Ref* p, unsigned n) { if (p) dealloc(p, n); }
inline void pad9() { int u0, u1, u2, u3, u4, u5, u6, u7, u8; }
inline Ref* copyW(Ref* first, Ref* last, Ref* dest) { bool t1 = false; bool t2 = false; int w[4]; return CopyRefs(first, last, dest); }
inline Ref* copyW3(Ref* first, Ref* last, Ref* dest) { bool t1 = false; bool t2 = false; int w[8]; return CopyRefs(first, last, dest); }
// ---- items of slice s0041e730 end

// ---- items of slice s0041efb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCounted { virtual void AddRef(); virtual void Release(); };
struct DefaultRefCounted { void Release(); };  // @ 0x00453540
template <class T> struct ptr {
    T* p;
    ptr() : p(0) {}
    ~ptr() { if (p) p->Release(); }
};
void AllocDeallocate(void* p);  // EASTL allocator deallocate (0x00F47380)
void* AllocAllocate(void* alloc, size_t n, size_t align, size_t off);  // 0x0042DEE0
template <int N> inline void PadN() { uint32_t s[N]; }
struct Elem16 { uint32_t pad[4]; };
struct Elem20 {
    uint32_t pad[7];
    ptr<IRefCounted> a;                  // +0x1C, released through vtable slot 1
    Elem20(const Elem20&);               // 0x00423080
};
struct Elem7c {
    char pad[0x74];
    ptr<IRefCounted> a;                  // +0x74
    ptr<DefaultRefCounted> b;            // +0x78
    Elem7c(const Elem7c&);               // 0x00422FD0
    Elem7c& operator=(const Elem7c&);    // 0x00429370
    ~Elem7c();
};
struct Elem8c {
    uint32_t pad[35];
    Elem8c(const Elem8c&);
    ~Elem8c();                           // 0x0041F940
};
typedef ptr<DefaultRefCounted> RcPtr;
struct Tag {};
struct Ret16 { uint32_t a, b, c, d; };
struct TagA { char c; TagA() : c(0) {} };
struct TagB { char c; TagB() : c(0) {} };
struct TagC { char c; TagC() : c(0) {} };
void UninitCopyImpl(Ret16* out, Elem16* first, Elem16* last, Elem16* dest, Tag t);  // 0x0047A500
Elem16* CopyElems16(Elem16* first, Elem16* last, Elem16* dest);                      // 0x00424770
Elem7c* UninitCopy7c(Elem7c* first, Elem7c* last, Elem7c* dest);                     // 0x00424C00
template <class T> T* UninitCopy(T* first, T* last, T* dest);  // 0x00425010 / 0x00425110
template <class T> struct Vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t alloc;

    void Destroy(T* first, T* last) {
        for (; first < last; ++first) first->~T();
    }
    void DoFreeImpl();
    void DoFree() { uint32_t s[3]; DoFreeImpl(); }
    ~Vec();
    void push_back(const T& v);
    void DoInsertValue(T* pos, const T& v);
    Vec(const Vec& o);
    Vec& operator=(const Vec& x);
    T* DoAllocateAndCopy(size_t n, T* first, T* last);
    T* DoAllocate(size_t n) { return n ? (T*)AllocAllocate(&alloc, n * sizeof(T), 4, 0) : 0; }

    // free a block obtained from the allocator (EASTL frees only blocks with a nonzero header word)
    void FreeImpl(void* p) { AllocDeallocate(p); }
    void DoFreeRange(T* p, size_t n) {
        if (p) {
            if (((int*)p)[-1]) { void* q = p; FreeImpl(q); }
        }
    }
    // Elem16 only: uninitialized_copy through three nested helpers (the stack layout shows all three)
    void UninitCopy16(T* first, T* last, T* dest) {
        Ret16 ret16; Tag t;
        volatile char tag;   // an unused 1-byte local occupies the slot just under the tag
        UninitCopy16M(&ret16, &t, dest, last, first);
    }
    void UninitCopy16M(Ret16* o, Tag* t, T* p0, T* p1, T* p2) {
        T* pDest = p0; T* last = p1; T* pFirst = p2;
        UninitCopy16O(o, t, pFirst, last, pDest);
    }
    void UninitCopy16O(Ret16* o, Tag* t, T* first, T* last, T* dest) {
        uint32_t pad[4];
        UninitCopyImpl(o, first, last, dest, *t);
    }
    void Destruct(T* first) { for (; first < mpEnd; ++first) {} }

    // Elem7c only: element-wise copy assignment
    static T* Copy(T* first, T* last, T* dest) {
TagA ta = TagA();
TagB tag2 = TagB();
TagC c = TagC();
        return CopyImpl(first, last, dest);
    }
    static T* Copy2(T* first, T* last, T* dest) {
        TagA ta = TagA(); TagB tag2 = TagB(); TagC c = TagC(); PadN<2>();
        return CopyImpl(first, last, dest);
    }
    static T* CopyImpl(T* first, T* last, T* dest) {
        for (; first != last; ++dest, ++first) *dest = *first;
        return dest;
    }
};
struct VecP {
    RcPtr* mpBegin; RcPtr* mpEnd; RcPtr* mpCapacity; uint32_t alloc;
    void DoInsertValues(RcPtr* pos, size_t n, const RcPtr& v);   // 0x0042A220
    void Erase(RcPtr* first, RcPtr* last);                       // 0x004247F0
    void Insert(RcPtr* pos, size_t n, const RcPtr& v) { DoInsertValues(pos, n, v); }
    void resize(size_t n);
};
// ---- items of slice s0041efb0 end

// ---- items of slice s0041f940 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct IRefCounted_s0041_f940 {
    virtual void v0();
    virtual void Release();
};
struct IntrusivePtr {
    IRefCounted_s0041_f940* mp;
    ~IntrusivePtr() { if (mp) mp->Release(); }
};
struct Elem16_s0041_f940 {                         // 16-byte element, ref at +0xc
    uint pad[3];
    IntrusivePtr mRef;
};
__forceinline void DestroyElems(Elem16_s0041_f940* first, Elem16_s0041_f940* last)
{
    for (; first < last; ++first)
        first->~Elem16_s0041_f940();
}
struct ElemBase {
    Elem16_s0041_f940* mpBegin;
    Elem16_s0041_f940* mpEnd;
    ~ElemBase();                        // 0x00424ca0
};
struct ElemList : ElemBase {
    ~ElemList();                        // 0x0041f9b0
};
__forceinline void DestroyRange(uint* first, uint* last)
{
    for (; first < last; ++first) {
    }
}
struct PtrVec {
    uint* mpBegin; uint* mpEnd; uint* mpCap;
    void FreeStorage();                 // 0x004c0b80
    ~PtrVec()
    {
        DestroyRange(mpBegin, mpEnd);
        FreeStorage();
    }
};
struct Owner {
    uint pad0[3];
    IntrusivePtr mRef;                  // +0x0c
    uint pad1;
    PtrVec mVec;                        // +0x14
    uint pad2[(0x44 - 0x20) / 4];
    ElemList mList;                     // +0x44
    ~Owner();
};
struct Alloc;
void* AllocBlock(Alloc* a, int size, int align, int flags);          // 0x0042dee0 (cdecl)
uint* CopyRange(uint* first, uint* last, uint* dest);                // 0x004e8c80 (cdecl)
struct UIntVec {
    uint* mpBegin; uint* mpEnd; uint* mpCap;
    uint mAlloc;                        // +0x0c
    UIntVec(const UIntVec& other);
};
struct Key64 { uint lo, hi; };
struct HNode { Key64 key; uint v[2]; HNode* next; };   // next at +0x10
struct HIter {
    HNode* mpNode; HNode** mpBucket;
    HIter(HNode* n, HNode** b) : mpNode(n), mpBucket(b) {}
    HIter(HNode** b) : mpNode(*b), mpBucket(b) {}
    HIter(const HIter& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
};
struct HInsertResult {
    HIter mIter; bool mInserted;
    HInsertResult(const HIter& it, bool b) : mIter(it), mInserted(b) {}
};
struct RehashResult { bool doRehash; uint newBucketCount; };
struct RehashPolicy {
    uint mData[4];
    void Needed(RehashResult* out, uint buckets, uint elems, uint add);  // 0x00921440
};
__forceinline bool KeyEq(const Key64& a, const Key64& b)
{
    return a.lo == b.lo && a.hi == b.hi;
}
struct HashTable {
    uint pad0;
    HNode** mBuckets;                   // +0x04
    uint mBucketCount;                  // +0x08
    uint mElemCount;                    // +0x0c
    RehashPolicy mPolicy;               // +0x10 rehash policy object

    void ClearBuckets(HNode** b, uint n);                                       // 0x0042a7b0
    void Rehash(uint n);                                                        // 0x004252b0
    __forceinline uint HashCode(const Key64& k) const { return k.lo; }
    __forceinline HNode* DoFindNode(HNode* pNode, const Key64& k) const
    {
        for (; pNode; pNode = pNode->next)
            if (KeyEq(k, pNode->key))
                return pNode;
        return 0;
    }
    HIter Find(const Key64& k);                                                 // 0x0041fb20
    void Destroy();                                                             // 0x0041fac0
};
struct InsertTag { uint mUnused; };
struct HashTableA : HashTable {
    HNode* AllocNode(const Key64& k);                                           // 0x004251b0
    HInsertResult Insert(const Key64& k, InsertTag tag);                        // 0x0041fc40
};
struct HashTableB : HashTable {
    HNode* AllocNode(const Key64& k);                                           // 0x00425240
    HInsertResult Insert(const Key64& k, InsertTag tag);                        // 0x0041fe00
};
__forceinline void FreeMem(void* p) { void* q = p; operator delete(q); }
__forceinline void DoFreeBuckets(HNode** pArray, uint n)
{
    if (n > 1)
        FreeMem(pArray);
}
struct Triple { uint a, b, c; };
struct TripleVec {
    uint pad0;
    Triple* mpEnd;                      // +4
    Triple* mpCap;                      // +8
    void GrowAndAppend(Triple* pos, const Triple& v);   // 0x004e3e10
    void PushBackDefault();
};
// ---- items of slice s0041f940 end

// @ 0x0041eae0
RefVector::RefVector(const RefVector& o)
{
    int n = o.mpEnd - o.mpBegin;
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCap = mpBegin + n;
    mpEnd = UninitCopyRefs(o.mpBegin, o.mpEnd, mpBegin);
}

// @ 0x0041eb80
RefVector::~RefVector()
{
    destructRefs(mpBegin, mpEnd);
    tail();
}

// @ 0x0041ebe0
RefVector& RefVector::operator=(const RefVector& x)
{
    if (&x != this) {
        const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCap - mpBegin)) {
            Ref* pNewData = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            pad9();
            destructRefs(mpBegin, mpEnd);
            freeRefs(mpBegin, mpCap - mpBegin);
            mpBegin = pNewData;
            mpCap = mpBegin + n;
        } else if (n > (unsigned)(mpEnd - mpBegin)) {
            copyW(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitCopyRefs(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Ref* pNewEnd = copyW3(x.mpBegin, x.mpEnd, mpBegin);
            destructRefs(pNewEnd, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0041ee90
void RefVector::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        ThreadedObject* val = 0;
        ins(mpEnd, n - (unsigned)(mpEnd - mpBegin), (Ref*)&val);
        if (val) val->Release();
    } else er(n);
}

// @ 0x0041ef20
void RefVector::push_back(const Ref& v)
{
    if (mpEnd < mpCap) {
        ::new((void*)mpEnd++) Ref(v);
    } else DoInsertValue(mpEnd, v);
}

// @ 0x0041efb0
template <> Vec<Elem16>& Vec<Elem16>::operator=(const Vec& x)
{
    if (&x != this) {
        size_t n = x.mpEnd - x.mpBegin;
        if (n > (size_t)(mpCapacity - mpBegin)) {
            Elem16* pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            PadN<9>(); Destruct(mpBegin);
            DoFreeRange(mpBegin, mpCapacity - mpBegin);
            mpBegin = pNew;
            mpCapacity = mpBegin + n;
        } else if (n > (size_t)(mpEnd - mpBegin)) {
            CopyElems16(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitCopy16(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Elem16* pos = CopyElems16(x.mpBegin, x.mpEnd, mpBegin);
            PadN<3>(); Destruct(pos);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0041f1e0
void VecP::resize(size_t n)
{
    if (n > (size_t)(mpEnd - mpBegin)) {
        RcPtr val;
        Insert(mpEnd, n - (mpEnd - mpBegin), val);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
    PadN<18>();
}

// @ 0x0041f270
template <> Vec<Elem7c>::~Vec()
{ uint32_t s1[5]; Destroy(mpBegin, mpEnd); DoFree(); }

// @ 0x0041f2d0
Elem7c::~Elem7c()
{ uint32_t s[3]; }

// @ 0x0041f320
template <> Vec<Elem7c>& Vec<Elem7c>::operator=(const Vec& x)
{
    if (&x != this) {
        size_t n = x.mpEnd - x.mpBegin;
        if (n > (size_t)(mpCapacity - mpBegin)) {
            Elem7c* pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            PadN<11>();
            Destroy(mpBegin, mpEnd);
            DoFreeRange(mpBegin, mpCapacity - mpBegin);
            mpBegin = pNew;
            mpCapacity = mpBegin + n;
        } else if (n > (size_t)(mpEnd - mpBegin)) {
            Copy2(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            PadN<10>();
            UninitCopy7c(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Elem7c* pos;
            PadN<2>();
            pos = Copy(x.mpBegin, x.mpEnd, mpBegin);
            PadN<5>();
            Destroy(pos, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0041f650
template <> void Vec<Elem7c>::push_back(const Elem7c& v)
{
    if (mpEnd < mpCapacity) { new (mpEnd++) Elem7c(v); PadN<18>(); }
    else DoInsertValue(mpEnd, v);
}

// @ 0x0041f6c0
template <> Vec<Elem20>::Vec(const Vec& o)
{
    size_t n = o.mpEnd - o.mpBegin;
    uint32_t s[13];
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = UninitCopy(o.mpBegin, o.mpEnd, mpBegin);
}

// @ 0x0041f760
template <> Vec<Elem20>::~Vec()
{ Destroy(mpBegin, mpEnd); DoFree(); }

// @ 0x0041f7d0
template <> void Vec<Elem20>::push_back(const Elem20& v)
{
    if (mpEnd < mpCapacity) { new (mpEnd++) Elem20(v); PadN<1>(); }
    else DoInsertValue(mpEnd, v);
}

// @ 0x0041f840
template <> Vec<Elem8c>::Vec(const Vec& o)
{
    size_t n = o.mpEnd - o.mpBegin;
    uint32_t s[14]; uint32_t s14, s15;
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = UninitCopy(o.mpBegin, o.mpEnd, mpBegin);
}

// @ 0x0041f8e0
template <> Vec<Elem8c>::~Vec()
{ uint32_t s1[9]; Destroy(mpBegin, mpEnd); DoFree(); }

// @ 0x0041f940
Owner::~Owner()
{
}

// @ 0x0041f9b0
ElemList::~ElemList()
{
    DestroyElems(mpBegin, mpEnd);
}

// @ 0x0041fa20
UIntVec::UIntVec(const UIntVec& other)
{
    int n = other.mpEnd - other.mpBegin;
    mpBegin = n ? (uint*)AllocBlock((Alloc*)&mAlloc, n * 4, 4, 0) : 0;
    mpEnd = mpBegin;
    mpCap = mpBegin + n;
    mpEnd = CopyRange(other.mpBegin, other.mpEnd, mpBegin);
}

// @ 0x0041fac0
void HashTable::Destroy()
{
    ClearBuckets(mBuckets, mBucketCount);
    mElemCount = 0;
    DoFreeBuckets(mBuckets, mBucketCount);
}

// @ 0x0041fb20
HIter HashTable::Find(const Key64& k)
{
    uint c = HashCode(k);
    uint n = c % mBucketCount;
    HNode* pNode = DoFindNode(mBuckets[n], k);
    return pNode ? HIter(pNode, mBuckets + n) : HIter(mBuckets + mBucketCount);
}

// @ 0x0041fc40
HInsertResult HashTableA::Insert(const Key64& k, InsertTag tag)
{
    uint c = HashCode(k);
    uint n = c % mBucketCount;
    HNode* pNode = DoFindNode(mBuckets[n], k);
    if (!pNode) {
        RehashResult rr;
        mPolicy.Needed(&rr, mBucketCount, mElemCount, 1);
        HNode* node = AllocNode(k);
        if (rr.doRehash) {
            n = c % rr.newBucketCount;
            Rehash(rr.newBucketCount);
        }
        node->next = mBuckets[n];
        mBuckets[n] = node;
        ++mElemCount;
        return HInsertResult(HIter(node, mBuckets + n), true);
    }
    return HInsertResult(HIter(pNode, mBuckets + n), false);
}

// @ 0x0041fe00
HInsertResult HashTableB::Insert(const Key64& k, InsertTag tag)
{
    uint c = HashCode(k);
    uint n = c % mBucketCount;
    HNode* pNode = DoFindNode(mBuckets[n], k);
    if (!pNode) {
        RehashResult rr;
        mPolicy.Needed(&rr, mBucketCount, mElemCount, 1);
        HNode* node = AllocNode(k);
        if (rr.doRehash) {
            n = c % rr.newBucketCount;
            Rehash(rr.newBucketCount);
        }
        node->next = mBuckets[n];
        mBuckets[n] = node;
        ++mElemCount;
        return HInsertResult(HIter(node, mBuckets + n), true);
    }
    return HInsertResult(HIter(pNode, mBuckets + n), false);
}

// @ 0x0041ffc0
void TripleVec::PushBackDefault()
{
    if (mpEnd < mpCap) {
        ::new((void*)mpEnd++) Triple();
    } else {
        GrowAndAppend(mpEnd, Triple());
    }
}
