// Slice 0x0041f940..0x00420270: unoptimized (/Od /Ob1) EASTL-style container helpers:
// a pointer-vector owner, vector copy, hash-table find/insert/dtor, 12-byte vector
// push_back, and a fixed 8-slot ring of 44-byte buckets with iterator accessors.
#include <new>

typedef unsigned int uint;


struct IRefCounted {
    virtual void v0();
    virtual void Release();
};

// 16-byte iterator state with a field-wise copy constructor (0x00420050).
struct SubIter {
    uint a, b, c, d;
    SubIter() {}
    SubIter(const SubIter& o);
    void Next();                        // 0x004253c0
    bool operator!=(const SubIter& o) const { return a != o.a; }
};
struct Node { ~Node(); };               // 0x00401f20
struct IterOwner {
    uint pad[2];
    SubIter mBegin;                     // +8
    SubIter mEnd;                       // +0x18
    void Finish();                      // 0x00501ef0
    void Destroy();
};

// @ 0x00420050
SubIter::SubIter(const SubIter& o)
{
    a = o.a;
    b = o.b;
    c = o.c;
    d = o.d;
}

// ---------------------------------------------------------------- owner of ref + element lists
struct IntrusivePtr {
    IRefCounted* mp;
    ~IntrusivePtr() { if (mp) mp->Release(); }
};
struct Elem16 {                         // 16-byte element, ref at +0xc
    uint pad[3];
    IntrusivePtr mRef;
};
__forceinline void DestroyElems(Elem16* first, Elem16* last)
{
    for (; first < last; ++first)
        first->~Elem16();
}
struct ElemBase {
    Elem16* mpBegin;
    Elem16* mpEnd;
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

// @ 0x0041f940
Owner::~Owner()
{
}

// @ 0x0041f9b0
// Not byte-exact: the original frame has three extra dead dword slots (0x1c vs 0x10).
ElemList::~ElemList()
{
    DestroyElems(mpBegin, mpEnd);
}

// ---------------------------------------------------------------- vector copy-construct
struct Alloc;
void* AllocBlock(Alloc* a, int size, int align, int flags);          // 0x0042dee0 (cdecl)
uint* CopyRange(uint* first, uint* last, uint* dest);                // 0x004e8c80 (cdecl)

struct UIntVec {
    uint* mpBegin; uint* mpEnd; uint* mpCap;
    uint mAlloc;                        // +0x0c
    UIntVec(const UIntVec& other);
};

// @ 0x0041fa20
UIntVec::UIntVec(const UIntVec& other)
{
    int n = other.mpEnd - other.mpBegin;
    mpBegin = n ? (uint*)AllocBlock((Alloc*)&mAlloc, n * 4, 4, 0) : 0;
    mpEnd = mpBegin;
    mpCap = mpBegin + n;
    mpEnd = CopyRange(other.mpBegin, other.mpEnd, mpBegin);
}

// ---------------------------------------------------------------- hash table
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
void RehashPolicyNeeded(void* policy, RehashResult* out, uint buckets, uint elems, uint add);  // 0x00921440

__forceinline bool KeyEq(const Key64& a, const Key64& b)
{
    return a.lo == b.lo && a.hi == b.hi;
}

struct HashTable {
    uint pad0;
    HNode** mBuckets;                   // +0x04
    uint mBucketCount;                  // +0x08
    uint mElemCount;                    // +0x0c
    uint mPolicy[4];                    // +0x10 rehash policy object

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
struct HashTableA : HashTable {
    HNode* AllocNode(const Key64& k);                                           // 0x004251b0
    HInsertResult Insert(const Key64& k);                                       // 0x0041fc40
};
struct HashTableB : HashTable {
    HNode* AllocNode(const Key64& k);                                           // 0x00425240
    HInsertResult Insert(const Key64& k);                                       // 0x0041fe00
};

__forceinline void FreeMem(void* p) { void* q = p; operator delete(q); }
__forceinline void DoFreeBuckets(HNode** pArray, uint n)
{
    if (n > 1)
        FreeMem(pArray);
}

// @ 0x0041fac0
void HashTable::Destroy()
{
    ClearBuckets(mBuckets, mBucketCount);
    mElemCount = 0;
    DoFreeBuckets(mBuckets, mBucketCount);
}

// @ 0x0041fb20
// Not byte-exact: the original also spills the by-reference key arguments of the
// inlined equality predicate to stack slots (frame 0x4c vs 0x38 here).
HIter HashTable::Find(const Key64& k)
{
    uint c = HashCode(k);
    uint n = c % mBucketCount;
    HNode* pNode = DoFindNode(mBuckets[n], k);
    return pNode ? HIter(pNode, mBuckets + n) : HIter(mBuckets + mBucketCount);
}

// @ 0x0041fc40
// Not byte-exact (same inlined-predicate spill issue as Find, plus extra frame slots).
HInsertResult HashTableA::Insert(const Key64& k)
{
    uint c = HashCode(k);
    uint n = c % mBucketCount;
    HNode* pNode = DoFindNode(mBuckets[n], k);
    if (!pNode) {
        RehashResult rr;
        RehashPolicyNeeded(mPolicy, &rr, mBucketCount, mElemCount, 1);
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
HInsertResult HashTableB::Insert(const Key64& k)
{
    uint c = HashCode(k);
    uint n = c % mBucketCount;
    HNode* pNode = DoFindNode(mBuckets[n], k);
    if (!pNode) {
        RehashResult rr;
        RehashPolicyNeeded(mPolicy, &rr, mBucketCount, mElemCount, 1);
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

// ---------------------------------------------------------------- 12-byte vector push_back
struct Triple { uint a, b, c; };
struct TripleVec {
    uint pad0;
    Triple* mpEnd;                      // +4
    Triple* mpCap;                      // +8
    void GrowAndAppend(Triple* pos, const Triple& v);   // 0x004e3e10
    void PushBackDefault();
};

// @ 0x0041ffc0
void TripleVec::PushBackDefault()
{
    if (mpEnd < mpCap) {
        ::new((void*)mpEnd++) Triple();
    } else {
        GrowAndAppend(mpEnd, Triple());
    }
}

struct Wrapper {
    void Init(int a, int b);            // 0x00425860
    Wrapper(int b);
};

// @ 0x00420090
Wrapper::Wrapper(int b) { Init(0, b); }

// ---------------------------------------------------------------- bucket ring iterators
struct Iter {
    uint cur;
    SubIter sub;
    uint x, y;
    Iter(uint c, void* beg, void* end, uint pos);                     // 0x004258b0
    void Normalize();                                                  // 0x004258f0
};
struct ConstIter {                      // converting copy of Iter
    uint cur;
    SubIter sub;
    uint x, y;
    ConstIter(const Iter& i) : cur(i.cur), sub(i.sub), x(i.x), y(i.y) {}
};
struct Bucket {                         // 0x2c bytes
    uint pad[11];
    uint Probe(SubIter* out);                                      // 0x00565740
    uint ProbeEnd(SubIter* out);                                   // 0x00565760
};
struct Ring {
    Bucket mBuckets[8];                 // 0x160 bytes
    Iter IterAt(int idx);               // 0x00420120
    Iter IterAtEnd(int idx);            // 0x00420270
    Iter IterBegin();                   // 0x00420200
    ConstIter IterFirst();              // 0x004201a0
};

// @ 0x00420120
Iter Ring::IterAt(int idx)
{
    SubIter tmp;
    uint r = mBuckets[idx].Probe(&tmp);
    Iter it((uint)&mBuckets[idx], this, (char*)this + 0x160, r);
    it.Normalize();
    return it;
}

// @ 0x00420200
Iter Ring::IterBegin()
{
    SubIter tmp;
    uint r = mBuckets[0].Probe(&tmp);
    Iter it((uint)this, this, (char*)this + 0x160, r);
    it.Normalize();
    return it;
}

// @ 0x004201a0
ConstIter Ring::IterFirst()
{
    return IterBegin();
}

// @ 0x00420270
Iter Ring::IterAtEnd(int idx)
{
    SubIter tmp;
    uint r = mBuckets[idx].ProbeEnd(&tmp);
    Iter it((uint)&mBuckets[idx], this, (char*)this + 0x160, r);
    it.Normalize();
    return it;
}

// @ 0x004200b0
void IterOwner::Destroy()
{
    SubIter it(mBegin);
    for (; it != mEnd; it.Next()) {
        Node* n = (Node*)it.a;
        n->~Node();
    }
    Finish();
}
