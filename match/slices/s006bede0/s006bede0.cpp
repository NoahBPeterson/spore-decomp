// Slice s006bede0 — PFIndexModifiable index/record methods + PFHoleTable rbtree (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <new>
#include "../s006bc1b0/s006bc1b0.h"

// ===========================================================================
// PFHoleTable's eastl::rbtree (object at PFHoleTable+8).
// ---------------------------------------------------------------------------
struct HoleValue {
    uint64 mOffset;   // +0x00 (sorted key)
    uint32 mA;        // +0x08
    uint32 mB;        // +0x0c
};

struct HoleNodeBase {
    HoleNodeBase* mpNodeRight;   // +0x00
    HoleNodeBase* mpNodeLeft;    // +0x04
    HoleNodeBase* mpNodeParent;  // +0x08
    uint8         mColor;        // +0x0c
};

struct HoleNode : HoleNodeBase {
    HoleValue mValue;            // +0x10
};

struct HoleIter {
    HoleNode* mpNode;
    HoleIter() : mpNode(0) {}
    HoleIter(HoleNode* p) : mpNode(p) {}
};

struct HolePairIB {
    HoleIter first;
    bool     second;
    HolePairIB(const HoleIter& f, bool s) : first(f), second(s) {}
};

struct true_type {};

struct HoleLess {
    bool operator()(const HoleNode* a, const HoleNode* b) const {
        return a->mValue.mOffset < b->mValue.mOffset;
    }
};

void* __cdecl EastlNew(uint32 n, const char* name, int flags, int dbg, const char* file, int line); // 0xF473A0
void  __cdecl RBTreeInsert(void* pNode, void* pNodeParent, void* pNodeAnchor, int side);           // 0x9216A0
void* __cdecl RBTreeDecrement(const void* pNode);                                                  // 0x9215C0

// Heap helpers (external callees, not slice targets).
void __cdecl make_heap(HoleNode** first, HoleNode** last, HoleLess compare);         // 0x6bea00
void __cdecl sort_heap(HoleNode** first, HoleNode** last, HoleLess compare);         // 0x6bea40
void __cdecl adjust_heap(HoleNode** first, int top, int heapSize, int position,
                         HoleNode* value, HoleLess compare);                          // 0x6be980

struct HoleTree {
    int          mCompare;      // +0x00
    HoleNodeBase mAnchor;       // +0x04
    uint32       mnSize;        // +0x14
    void*        mAllocator;    // +0x18

    void DoNukeSubtree(void* p);   // 0x9a9600
    HoleIter DoInsertValueImpl(HoleNodeBase* pNodeParent, const HoleValue& value, bool bForceToLeft);
    HolePairIB DoInsertValue(const HoleValue& value, true_type);
};

// @ 0x006bef70
void PFHoleTable::FUN_006bef70(uint32 a, uint32 b)
{
    HoleTree* t = (HoleTree*)((char*)this + 8);
    t->DoNukeSubtree(t->mAnchor.mpNodeParent);
    t->mAnchor.mpNodeLeft   = (HoleNodeBase*)&t->mAnchor;
    t->mAnchor.mpNodeRight  = (HoleNodeBase*)&t->mAnchor;
    t->mAnchor.mpNodeParent = 0;
    t->mAnchor.mColor       = 0;
    t->mnSize               = 0;
    *(uint32*)((char*)this + 0) = a;
    *(uint32*)((char*)this + 4) = b;
}

// @ 0x006bf140
HoleIter HoleTree::DoInsertValueImpl(HoleNodeBase* pNodeParent, const HoleValue& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || (pNodeParent == &mAnchor) ||
        (value.mOffset < ((HoleNode*)pNodeParent)->mValue.mOffset))
        side = 0;
    else
        side = 1;
    HoleNode* const pNodeNew = (HoleNode*)EastlNew(sizeof(HoleNode), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&pNodeNew->mValue) HoleValue(value);
    RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
    mnSize++;
    return HoleIter(pNodeNew);
}

// @ 0x006bf2c0
HolePairIB HoleTree::DoInsertValue(const HoleValue& value, true_type)
{
    HoleNode* pCurrent    = (HoleNode*)mAnchor.mpNodeParent;
    HoleNode* pLowerBound = (HoleNode*)&mAnchor;
    HoleNode* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = (value.mOffset < pCurrent->mValue.mOffset);
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (HoleNode*)pCurrent->mpNodeLeft;
        else
            pCurrent = (HoleNode*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (HoleNode*)mAnchor.mpNodeLeft) {
            pLowerBound = (HoleNode*)RBTreeDecrement(pLowerBound);
        } else {
            const HoleIter itResult(DoInsertValueImpl(pLowerBound, value, false));
            return HolePairIB(itResult, true);
        }
    }

    if (pLowerBound->mValue.mOffset < value.mOffset) {
        const HoleIter itResult(DoInsertValueImpl(pParent, value, false));
        return HolePairIB(itResult, true);
    }

    return HolePairIB(HoleIter(pLowerBound), false);
}

// @ 0x006bf1e0
template <typename It, typename T, typename Compare>
__declspec(noinline) It get_partition(It first, It last, T pivotValue, Compare compare) {
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        const T temp(*first);
        *first = *last;
        *last = temp;
    }
}

template HoleNode** get_partition<HoleNode**, HoleNode*, HoleLess>
    (HoleNode**, HoleNode**, HoleNode*, HoleLess);

// @ 0x006bf240
void partial_sort(HoleNode** first, HoleNode** middle, HoleNode** last, HoleLess compare) {
    make_heap(first, middle, compare);
    for (HoleNode** i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            HoleNode* const temp(*i);
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    sort_heap(first, middle, compare);
}

// ===========================================================================
// PFIndexModifiable's item map: eastl::hashtable at +0x28.
// ---------------------------------------------------------------------------
struct PFRecordInfo { uint64 mOffset; uint32 mSize; uint32 mA; uint32 mB; };  // 0x18
struct HashValue { Key mKey; uint32 mPad; PFRecordInfo mInfo; };              // 0x28
struct HashNode  { HashValue mValue; HashNode* mpNext; };                     // 0x30

struct HashIter {
    HashNode*  mpNode;
    HashNode** mpBucket;
    HashIter(HashNode** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    HashIter(HashNode* n, HashNode** b) : mpNode(n), mpBucket(b) {}
    void increment_bucket() { ++mpBucket; while (!*mpBucket) ++mpBucket; mpNode = *mpBucket; }
    void increment() { mpNode = mpNode->mpNext; while (!mpNode) mpNode = *++mpBucket; }
    HashIter& operator++() { increment(); return *this; }
};
inline bool operator!=(const HashIter& a, const HashIter& b) { return a.mpNode != b.mpNode; }

struct InsertRet {
    HashIter first;
    bool     second;
    InsertRet(const HashIter& i, bool b) : first(i), second(b) {}
};

struct PairBU { bool first; uint32 second; };

struct PrimeRehashPolicy {
    float  mfMaxLoadFactor;   // +0
    float  mfGrowthFactor;    // +4
    uint32 mnNextResize;      // +8
    PairBU GetRehashRequired(uint32 nBucketCount, uint32 nElementCount, uint32 nElementAdd) const; // 0x921440
};

struct CoreAlloc {
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(uint32 n, const char* pName, uint32 flags);
    virtual void  Free(void* p, uint32 nBytes);
};

struct PFItemsMap {
    void*      mHashCodeBase;          // +0x00
    HashNode** mpBucketArray;          // +0x04
    uint32     mnBucketCount;          // +0x08
    uint32     mnElementCount;         // +0x0c
    PrimeRehashPolicy mRehashPolicy;   // +0x10
    void*      mpCoreAllocator;        // +0x1c
    int        mnFlags;                // +0x20

    void Rehash(uint32 nBucketCount);   // 0x6be8d0
    void FreeNodes(HashNode** pBucketArray, uint32 nBucketCount); // 0x6be640
    HashIter begin() { HashIter i(mpBucketArray); if (!i.mpNode) i.increment_bucket(); return i; }
    HashIter end()   { return HashIter(mpBucketArray + mnBucketCount); }
    InsertRet DoInsertValue(const HashValue& value, true_type);
};

// @ 0x006bf030
InsertRet PFItemsMap::DoInsertValue(const HashValue& value, true_type) {
    const Key&  k = value.mKey;
    const uint32 c = (uint32)(k.type ^ k.instance);
    uint32      n  = c % mnBucketCount;

    HashNode* pNode = mpBucketArray[n];
    while (pNode) {
        if (k.type == pNode->mValue.mKey.type && k.group == pNode->mValue.mKey.group &&
            k.instance == pNode->mValue.mKey.instance)
            break;
        pNode = pNode->mpNext;
    }

    if (pNode == 0) {
        const PairBU bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
        HashNode* const pNodeNew =
            (HashNode*)((CoreAlloc*)mpCoreAllocator)->Alloc(sizeof(HashNode), 0, (uint32)mnFlags);
        if (pNodeNew) {
            ::new (&pNodeNew->mValue) HashValue(value);
        }
        pNodeNew->mpNext = 0;

        if (bRehash.first) {
            n = (uint32)(c % bRehash.second);
            Rehash(bRehash.second);
        }

        pNodeNew->mpNext = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;

        return InsertRet(HashIter(pNodeNew, mpBucketArray + n), true);
    }

    return InsertRet(HashIter(pNode, mpBucketArray + n), false);
}

// ---------------------------------------------------------------------------
// View of EA::ResourceMan::PFIndexModifiable (identical layout, arity-correct
// member signatures for the range/interference validators).
// ---------------------------------------------------------------------------
// The map's node pool at +0x08, its vptr and the map's globals.  Both vtable
// pointers and the empty bucket array are link-time constants in the original
// (`mov [esi], 0x140a200`), so they are modelled as immediate addresses.
extern HashNode* g_pBucketArrayEmpty[1]; // 0x154df28
extern const float g_kMaxLoadFactor;     // 0x1485720
extern const float g_kGrowthFactor;      // 0x1470f1c

// 0x925f30 / 0x925e60: the node pool's ctor/dtor.
struct PFNodePool {
    void*  mAllocator;    // +0x00
    uint32 mnBlockSize;   // +0x04
    uint32 mnBlockCount;  // +0x08
    char   mRest[0x14];   // +0x0c
    void InitPool(void* pAllocator, uint32 nA, uint32 nB); // 0x925f30
    void DestroyPool();                                // 0x925e60
};

// operator delete() of a polymorphic class reaches its scalar deleting
// destructor through a vtable slot; the allocator's slot 3 is its Free(p, n).
struct PFIndex {
    void*     vtbl;             // +0x00
    void*     mpAllocator;      // +0x04
    PFNodePool mPool;           // +0x08
    PFItemsMap mItemsMap;        // +0x28

    void Ctor(void* pAllocator);  // 0x6bf370
    void Dtor();                  // 0x6bf430
    bool Validate(uint64 begin, uint64 end);
    bool ValidateFreeSpace(uint64 begin, uint64 size);
};

// @ 0x006bf370
void PFIndex::Ctor(void* pAllocator)
{
    vtbl = (void*)0x140a200;
    mpAllocator = pAllocator;
    mPool.InitPool(pAllocator, 0x80, 0x30);

    mItemsMap.mpBucketArray                 = g_pBucketArrayEmpty;
    mItemsMap.mnBucketCount                 = 1;
    mItemsMap.mnElementCount                = 0;
    mItemsMap.mRehashPolicy.mfMaxLoadFactor = g_kMaxLoadFactor;
    mItemsMap.mRehashPolicy.mfGrowthFactor  = g_kGrowthFactor;
    mItemsMap.mRehashPolicy.mnNextResize    = 0;
    mItemsMap.mpCoreAllocator               = &mPool;
    mItemsMap.mnFlags                       = 0;
}

// @ 0x006bf430
void PFIndex::Dtor()
{
    mItemsMap.FreeNodes(mItemsMap.mpBucketArray, mItemsMap.mnBucketCount);
    mItemsMap.mnElementCount = 0;
    if (mItemsMap.mnBucketCount > 1)
        ((CoreAlloc*)mItemsMap.mpCoreAllocator)->Free(mItemsMap.mpBucketArray,
                                                      mItemsMap.mnBucketCount * 4 + 4);
    mPool.DestroyPool();
    vtbl = (void*)0x13effb8;
}

// @ 0x006bede0
bool PFIndex::Validate(uint64 begin, uint64 end)
{
    HashIter it    = mItemsMap.begin();
    HashIter itEnd = mItemsMap.end();
    while (it != itEnd) {
        HashNode* const p = it.mpNode;
        if (p->mValue.mInfo.mSize) {
            const uint64 off = p->mValue.mInfo.mOffset;
            if (off - begin >= end - begin)
                return false;
            if ((uint64)p->mValue.mInfo.mSize > end - off)
                return false;
        }
        ++it;
    }
    return true;
}

// @ 0x006beeb0
bool PFIndex::ValidateFreeSpace(uint64 begin, uint64 size)
{
    if (size) {
        const uint64 limit = begin + size;
        HashIter it    = mItemsMap.begin();
        HashIter itEnd = mItemsMap.end();
        while (it != itEnd) {
            HashNode* const p = it.mpNode;
            if (p->mValue.mInfo.mSize) {
                const uint64 off = p->mValue.mInfo.mOffset;
                if (off < limit && begin < off + (uint64)p->mValue.mInfo.mSize)
                    return false;
            }
            ++it;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Non-target skeletons (kept for the module picture; tracked in partial.txt).
// ---------------------------------------------------------------------------
// The retail initialiser returns the object pointer in eax (mov eax, ecx at
// 0x006bf5a0).  A plain C++ body leaves ecx holding it; route the initial
// pointer through a tiny noinline identity so cl copies `this` into eax and
// keeps the tree pointer in ecx, matching the retail register roles.
__declspec(noinline) static void* __fastcall PFHoleTableKeepThis(void* self) { return self; }

// @ 0x006bf5a0
void PFHoleTable::FUN_006bf5a0()
{
    uint32* a = (uint32*)PFHoleTableKeepThis(this);
    uint32* p = a + 3;
    a[0] = 0xffffffff;
    a[1] = 0xffffffff;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[0] = (uint32)p;
    a[4] = (uint32)p;
    a[5] = 0;
    *((uint8*)a + 0x18) = 0;
    a[7] = 0;
}

// @ 0x006bfc50
int64_t PFHoleTable::FUN_006bfc50(uint32 a, uint32 b)
{
    // TODO(partial): find largest hole fitting (size, offset).
    return 0;
}

// @ 0x006bf4e0
void* PFIndexModifiable::GetFileInfo(const Key* key)
{
    // TODO(partial): hashtable find + return &entry.info.
    return 0;
}

// @ 0x006bf520
bool PFIndexModifiable::RemoveFile(const Key* key, void* out)
{
    // TODO(partial): hashtable find + erase.
    return false;
}

// @ 0x006bfa00
void* PFIndexModifiable::GetFiles(void* dst, void* filter)
{
    // TODO(partial): iterate records matching an IKeyFilter.
    return 0;
}

// @ 0x006bfac0
void* PFIndexModifiable::GetAllFiles(void* dst)
{
    // TODO(partial): append every key to the destination vector.
    return 0;
}

// @ 0x006bfbc0
void* PFIndexModifiable::PutFileInfo(const Key* key, const void* info)
{
    // TODO(partial): insert-or-find then copy the record info.
    return 0;
}

// @ 0x006bf660
bool PFIndexModifiable::Read(void* data, uint32 size, uint32 count, int flag)
{
    // TODO(partial): parse DBPF index records into the map.
    return false;
}

// ---------------------------------------------------------------------------
void FUN_006bf5d0(void* a, void* b, void* c, void* d); // 0x6bf5d0
void* FUN_006bf7d0(void* a, void* b);                // 0x6bf7d0
void FUN_006bf8f0(void* a, void* b, void* c, void* d); // 0x6bf8f0
void* FUN_006bfc20(void* a, void* b, void* c);       // 0x6bfc20

// @ 0x006bf5d0
void FUN_006bf5d0(void*, void*, void*, void*) {}
// @ 0x006bf7d0
void* FUN_006bf7d0(void*, void*) { return 0; }
// @ 0x006bf8f0
void FUN_006bf8f0(void*, void*, void*, void*) {}
// @ 0x006bfc20
void* FUN_006bfc20(void* a, void*, void*) { return a; }
