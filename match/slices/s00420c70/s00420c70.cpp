// EASTL-style containers in an unoptimized module (/Od /Ob1): byte vector, int-keyed map,
// vectors of intrusive-pointer pairs, and a hashtable unique-insert.
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

void __cdecl FreeBlock(void* p);   // EASTL_allocator_deallocate

struct Counted { void Release(); };   // Resource::ThreadedObject::Release (0x00404f90)

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
void __cdecl MoveBytes(void* first, void* last, void* dest);   // 0x00475bd0

// ---- byte vector ----
struct ByteVec {
    uint8_t* mBegin;
    uint8_t* mEnd;
    uint8_t* mCap;
    void DoPushBackRealloc(uint8_t* pos, const uint8_t& v);   // 0x00426730
    uint8_t* DoAllocateAndCopy(uint32_t n, const uint8_t* first, const uint8_t* last);  // 0x00426950
    void push_back(const uint8_t& v);
    ByteVec& assign(const ByteVec& x);
    static void DoFree(uint8_t* p, uint32_t n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                FreeBlock(q);
            }
        }
    }
    void DestroyFrom(uint8_t* first) { for (; first < mEnd; ++first) { } }
    static uint8_t* DoCopy(const uint8_t* first, const uint8_t* last, uint8_t* dest)
    {
        bool b0, b1, b2;
        b2 = false;
        b0 = false;
        b1 = true;
        return (uint8_t*)memcpy(dest, first, last - first) + (last - first);
    }
};

// @ 0x00420e30
ByteVec& ByteVec::assign(const ByteVec& x)
{
    if (&x != this) {
        uint32_t n = x.mEnd - x.mBegin;
        if (n > (uint32_t)(mCap - mBegin)) {
            uint8_t* pNew = DoAllocateAndCopy(n, x.mBegin, x.mEnd);
            ScratchSlots<13>();
            DestroyFrom(mBegin);
            DoFree(mBegin, mCap - mBegin);
            mBegin = pNew;
            mCap = mBegin + n;
        } else if (n > (uint32_t)(mEnd - mBegin)) {
            DoCopy(x.mBegin, x.mBegin + (mEnd - mBegin), mBegin);
            ScratchSlots<17>();
            MoveBytes(x.mBegin + (mEnd - mBegin), x.mEnd, mEnd);
        } else {
            uint8_t* r = DoCopy(x.mBegin, x.mEnd, mBegin);
            DestroyFrom(r);
        }
        mEnd = mBegin + n;
    }
    return *this;
}

// @ 0x00421080
void ByteVec::push_back(const uint8_t& v)
{
    if (mEnd < mCap) {
        ::new(mEnd++) uint8_t(v);
    } else {
        DoPushBackRealloc(mEnd, v);
    }
}

// ---- int-keyed map: operator[] ----
struct IntNode { int key; int value; };
IntNode* __cdecl LowerBound(IntNode* first, IntNode* last, const int* k, uint8_t flag);   // 0x0042dd00
inline bool IntLess(const int& a, const int& b) { return a < b; }
struct IntMap {
    IntNode* mBegin;
    IntNode* mEnd;
    uint32_t pad[3];
    uint8_t mFlag;
    IntNode* DoInsertValue(IntNode* pos, const IntNode& v);   // 0x00426cc0
    IntNode* lower_bound(const int& k)
    {
        IntNode* last = mEnd;
        IntNode* first = mBegin;
        return LowerBound(first, last, &k, mFlag);
    }
    IntNode* end() { return mEnd; }
    int& operator[](const int& k);
};

// @ 0x004210f0
int& IntMap::operator[](const int& k)
{
    IntNode* it = lower_bound(k);
    int unused1;
    if (it == end() || IntLess(k, it->key)) {
        int zero = 0;
        IntNode v;
        v.key = k;
        v.value = zero;
        it = DoInsertValue(it, v);
    }
    return it->value;
}

// ---- vector of (id, intrusive ptr) pairs, element 8 bytes ----
struct IPtr {
    Counted* p;
    ~IPtr() { if (p) p->Release(); }
};
struct IdPtr {
    int id;
    IPtr ptr;
};
struct IdPtrVec {
    IdPtr* mBegin;
    IdPtr* mEnd;
    IdPtr* mCap;
    uint32_t mAlloc[2];
    static void DestroyRange(IdPtr* first, IdPtr* last) { for (; first < last; ++first) first->~IdPtr(); }
    static void DoFree(IdPtr* p, uint32_t n) { void* q = p; FreeBlock(q); }
    ~IdPtrVec();
    IdPtrVec& assign(const IdPtrVec& o);   // 0x0042d990
};

// @ 0x00421190
IdPtrVec::~IdPtrVec()
{
    ScratchSlots<3>();
    DestroyRange(mBegin, mEnd);
    if (mBegin)
        DoFree(mBegin, (mCap - mBegin) * sizeof(IdPtr));
}

// ---- vector of 24-byte elements, each holding an IdPtrVec ----
struct Elem24 {
    IdPtrVec v;
    uint8_t flag;
    ~Elem24() {}
    __forceinline void SetFlag(uint8_t b) { flag = b; }
    __forceinline Elem24& operator=(const Elem24& o)
    {
        v.assign(o.v);   // 0x0042d990
        SetFlag(o.flag);
        return *this;
    }
};
struct Elem24Vec {
    Elem24* mBegin;
    Elem24* mEnd;
    Elem24* mCap;
    Elem24* DoAllocateAndCopy(uint32_t n, const Elem24* first, const Elem24* last);   // 0x00427100
    static void UninitCopy(const Elem24* first, const Elem24* last, Elem24* dest);    // 0x00427160
    ~Elem24Vec();
    Elem24Vec& assign(const Elem24Vec& x);
    void Free();   // 0x004fd940
    static void DestroyRange(Elem24* first, Elem24* last) { for (; first < last; ++first) first->~Elem24(); }
    static void DoFree(Elem24* p, uint32_t n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                FreeBlock(q);
            }
        }
    }
    __forceinline static Elem24* DoCopy(const Elem24* first, const Elem24* last, Elem24* dest)
    {
        bool b0, b1, b2;
        b2 = false;
        b0 = false;
        b1 = false;
        Elem24* d = dest;
        const Elem24* f = first;
        for (; f != last; ++f, ++d)
            *d = *f;
        return d;
    }
};

// @ 0x00421230
Elem24Vec::~Elem24Vec()
{
    ScratchSlots<9>();
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

// @ 0x00421290
Elem24Vec& Elem24Vec::assign(const Elem24Vec& x)
{
    if (&x != this) {
        uint32_t n = x.mEnd - x.mBegin;
        if (n > (uint32_t)(mCap - mBegin)) {
            Elem24* pNew = DoAllocateAndCopy(n, x.mBegin, x.mEnd);
            ScratchSlots<14>();
            DestroyRange(mBegin, mEnd);
            DoFree(mBegin, mCap - mBegin);
            mBegin = pNew;
            mCap = mBegin + n;
        } else if (n > (uint32_t)(mEnd - mBegin)) {
            DoCopy(x.mBegin, x.mBegin + (mEnd - mBegin), mBegin);
            ScratchSlots<12>();
            UninitCopy(x.mBegin + (mEnd - mBegin), x.mEnd, mEnd);
        } else {
            Elem24* pEnd = DoCopy(x.mBegin, x.mEnd, mBegin);
            DestroyRange(pEnd, mEnd);
        }
        mEnd = mBegin + n;
    }
    return *this;
}

// ---- hashtable unique insert (hash set of 32-bit keys) ----
struct HashNode { uint32_t key; uint32_t value; HashNode* next; };
struct RehashResult { uint8_t doRehash; uint32_t newBucketCount; };
struct Iter { HashNode* node; HashNode** bucket; Iter(HashNode* n, HashNode** b) : node(n), bucket(b) {}  };
struct InsertResult {
    Iter first; uint8_t second;
    InsertResult(Iter i, const bool& b) : first(i), second(b) {}
};
struct FieldHash { uint32_t operator()(uint32_t k) const; };
struct FieldEq { bool operator()(uint32_t a, uint32_t b) const; };
struct TrueTag {};
struct Policy { RehashResult* __thiscall NeedRehash(RehashResult* out, uint32_t bc, uint32_t ec, uint32_t n); };
struct FieldSetHashTable {
    uint8_t pad0;
    FieldEq eq;
    FieldHash hash;
    uint8_t pad1;
    HashNode** mBuckets;
    uint32_t mBucketCount;
    uint32_t mElementCount;
    Policy policy;
    HashNode* DoAllocateNode(const HashNode* v);
    void DoRehash(uint32_t n);
    uint32_t GetHash(uint32_t k) { return hash(k); }
    bool Compare(uint32_t a, uint32_t b) { return eq(a, b); }
    HashNode* DoFindNode(HashNode* p, const uint32_t& k)
    {
        for (; p; p = p->next) {
            if (Compare(k, p->key)) return p;
        }
        return 0;
    }
    InsertResult DoInsertValue(const HashNode* v, const TrueTag&);
};
// @ 0x00420c70
InsertResult FieldSetHashTable::DoInsertValue(const HashNode* v, const TrueTag&)
{
    const uint32_t& k = v->key;
    uint32_t c = GetHash(k);
    uint32_t n = c % mBucketCount;
    HashNode* pNode = DoFindNode(mBuckets[n], k);
    if (pNode == 0) {
        RehashResult rr;
        policy.NeedRehash(&rr, mBucketCount, mElementCount, 1);
        HashNode* pNodeNew = DoAllocateNode(v);
        if (rr.doRehash) {
            n = c % rr.newBucketCount;
            DoRehash(rr.newBucketCount);
        }
        pNodeNew->next = mBuckets[n];
        mBuckets[n] = pNodeNew;
        ++mElementCount;
        return InsertResult(Iter(pNodeNew, mBuckets + n), true);
    }
    return InsertResult(Iter(pNode, mBuckets + n), false);
}
