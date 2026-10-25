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
    void DoInsertValueHint(uint32* outIter, HoleNode* hintNode, const HoleValue* value); // 0x6bf8f0
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
    void* FindOrInsert(const Key* key);   // 0x6bf7d0
};

extern void __cdecl HT_find(const void* key, void* outIter);   // 0x6befb0

// @ 0x006bf7d0  find-or-insert a typed record, returning node+0x10
void* PFItemsMap::FindOrInsert(const Key* key)
{
    void* it[4];
    HT_find(key, it);
    if (it[0] == mpBucketArray[mnBucketCount]) {
        HashValue hv;
        hv.mKey          = *key;
        hv.mPad          = 0;
        hv.mInfo.mOffset = 0;
        hv.mInfo.mSize   = 0;
        hv.mInfo.mA      = 0;
        hv.mInfo.mB      = 0;
        InsertRet r = DoInsertValue(hv, true_type());
        it[0] = r.first.mpNode;
    }
    return (char*)it[0] + 0x10;
}

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
// The item map reached from the index object (+0x28) — same layout as the
// standalone PFItemsMap above.
// ---------------------------------------------------------------------------
inline PFItemsMap& itemsMapOf(PFIndexModifiable* p) {
    return *(PFItemsMap*)((char*)p + 0x28);
}

// vtable-slot helper (vptr occupies slot 0).
#define VT(p) (*(void***)(p))

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

// ===========================================================================
// PFHoleTable's rbtree view (HoleRecord-keyed).  The tree object lives at
// PFHoleTable+0xc, so its member functions take ecx = that address.
// ===========================================================================
struct HoleTreeNode {
    HoleTreeNode* mpNodeRight;   // +0x00
    HoleTreeNode* mpNodeLeft;    // +0x04
    HoleTreeNode* mpNodeParent;  // +0x08
    uint8         mColor;        // +0x0c
    char          pad0d[3];      // +0x0d
    uint32        mField10;      // +0x10
    uint32        mField14;      // +0x14
    uint32        mOffsetLo;     // +0x18
    uint32        mOffsetHi;     // +0x1c
};

// The whole PFHoleTable (0x28 bytes); the tree object is the +0xc view below.
struct HoleTable {
    uint64       mTotal;         // +0x00  running size/offset
    HoleTreeNode mAnchor;        // +0x0c  map base (squid) node
    uint32       mnSize;         // +0x1c
    uint32       unk20;          // +0x20
    uint32       unk24;          // +0x24
};

struct HoleTreeC {
    HoleTreeNode mAnchor;        // +0x00 (== PFHoleTable+0xc)
    uint32       mnSize;         // +0x10
    uint32       unk14;          // +0x14

    uint64 FindHole(uint32 a, uint32 b);
};

// ---------------------------------------------------------------------------
// external helpers (callees, not slice targets)
// ---------------------------------------------------------------------------
extern void  __cdecl HT_find(const void* key, void* outIter);          // 0x6befb0
extern void  __cdecl HT_eraseNode(const void* it, const void* a, void* b); // 0x6be820
extern void* __cdecl HoleTree_median3(HoleNode** a, HoleNode** b, HoleNode** c, HoleLess cmp); // 0x6be730
extern void* __cdecl RBTreeIncrement(void* node);                      // 0x921580
extern void  __cdecl RBTreeErase(void* a, void* b);                    // 0x921880
extern void  __cdecl DeleteTreeNode(void* node);                       // 0xf47380 (operator delete)
extern void  __cdecl VecOfKey_DoInsertKey(void* vec, Key* slot, const void* value); // 0x4e3e10
extern void  __cdecl QuickSortPairs(void* first, void* last, uint32 cmp); // 0x6bf870

// ---------------------------------------------------------------------------
// @ 0x006bf4e0  PFIndexModifiable::FindRecord (header spelling: GetFileInfo)
// ---------------------------------------------------------------------------
void* PFIndexModifiable::GetFileInfo(const Key* key)
{
    PFItemsMap& map = itemsMapOf(this);
    void* it[2];
    HT_find(key, it);
    if (it[0] != map.mpBucketArray[map.mnBucketCount])
        return (char*)it[0] + 0x10;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006bf520  PFIndexModifiable::DeleteRecord (header spelling: RemoveFile)
// ---------------------------------------------------------------------------
bool PFIndexModifiable::RemoveFile(const Key* key, void* out)
{
    PFItemsMap& map = itemsMapOf(this);
    void* it[2];
    HT_find(key, it);
    void* node = it[0];
    if (node == map.mpBucketArray[map.mnBucketCount])
        return false;

    uint32* dst = (uint32*)out;
    dst[0] = *(uint32*)((char*)node + 0x10);
    dst[1] = *(uint32*)((char*)node + 0x14);
    dst[2] = *(uint32*)((char*)node + 0x18);
    dst[3] = *(uint32*)((char*)node + 0x1c);
    dst[4] = *(uint32*)((char*)node + 0x20);
    dst[5] = *(uint32*)((char*)node + 0x24);

    HT_eraseNode(node, node, it[1]);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006bfbc0  PFIndexModifiable::AddRecord / PutFileInfo
// ---------------------------------------------------------------------------
void* PFIndexModifiable::PutFileInfo(const Key* key, const void* info)
{
    PFItemsMap& map = itemsMapOf(this);
    void* dst = map.FindOrInsert(key);
    *(PFRecordInfo*)dst = *(const PFRecordInfo*)info;
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x006bfa00  PFIndexModifiable::GetKeyList (header spelling: GetFiles)
// ---------------------------------------------------------------------------
struct VecOfKey {
    Key* mpBegin;   // +0x00
    Key* mpEnd;     // +0x04
    Key* mpCap;     // +0x08
};
struct KeyFilterVtbl { virtual void f0(); virtual char Accept(const void* node); };
struct KeyFilter { KeyFilterVtbl* vtbl; };

void* PFIndexModifiable::GetFiles(void* dst, void* filter)
{
    PFItemsMap& map = itemsMapOf(this);
    HashNode** pBucket = map.mpBucketArray;
    HashNode*  pNode   = *pBucket;
    uint32     count   = 0;
    if (!pNode) {
        do { ++pBucket; } while (!*pBucket);
        pNode = *pBucket;
    }
    HashNode* const pEnd = (HashNode*)map.mpBucketArray[map.mnBucketCount];
    VecOfKey* vec = (VecOfKey*)dst;
    KeyFilter* f = (KeyFilter*)filter;

    while (pNode != pEnd) {
        if (!f || f->vtbl->Accept(pNode)) {
            if (vec) {
                Key* slot = vec->mpEnd;
                if (slot < vec->mpCap) {
                    vec->mpEnd = slot + 1;
                    if (slot) {
                        slot[0] = pNode->mValue.mKey;
                    }
                } else {
                    VecOfKey_DoInsertKey(vec, slot, &pNode->mValue.mKey);
                }
            }
            ++count;
        }
        pNode = pNode->mpNext;
        while (!pNode) pNode = *++pBucket;
    }
    return (void*)count;
}

// ---------------------------------------------------------------------------
// @ 0x006bfac0  PFIndexModifiable::GetKeysSortedByPosition (header: GetAllFiles)
// ---------------------------------------------------------------------------
void* PFIndexModifiable::GetAllFiles(void* dst)
{
    PFItemsMap& map = itemsMapOf(this);
    const uint32 n = map.mnElementCount;

    ICoreAllocator* alloc = mpAllocator;
    void* const pBase = ((void* (__thiscall*)(ICoreAllocator*, uint32, const char*, uint32))
                             VT(alloc)[8 / 4])(alloc, n * 4, "Resource/PFIndex", 0);

    HashNode** pBucket = map.mpBucketArray;
    HashNode*  pNode   = *pBucket;
    if (!pNode) {
        do { ++pBucket; } while (!*pBucket);
        pNode = *pBucket;
    }
    HashNode* const pEnd = (HashNode*)map.mpBucketArray[map.mnBucketCount];

    void** pOut = (void**)pBase;
    while (pNode != pEnd) {
        *pOut++ = pNode;
        pNode = pNode->mpNext;
        while (!pNode) pNode = *++pBucket;
    }

    QuickSortPairs(pBase, pOut, 0);

    VecOfKey* vec = (VecOfKey*)dst;
    for (void** i = (void**)pBase; i < pOut; ++i) {
        HashNode* node = (HashNode*)*i;
        Key* slot = vec->mpEnd;
        if (slot < vec->mpCap) {
            vec->mpEnd = slot + 1;
            if (slot) slot[0] = node->mValue.mKey;
        } else {
            VecOfKey_DoInsertKey(vec, slot, &node->mValue.mKey);
        }
    }

    ((void (__thiscall*)(ICoreAllocator*, void*, uint32))VT(alloc)[0xc / 4])(alloc, pBase, 0);
    return (void*)n;
}

// ---------------------------------------------------------------------------
// @ 0x006bf660  PFIndexModifiable::ReadFromMemory (header spelling: Read)
// ---------------------------------------------------------------------------
bool PFIndexModifiable::Read(void* data, uint32 a, uint32 count, int b)
{
    (void)a; (void)b;
    const uint32* p = (const uint32*)data;
    const uint32 flags = p[0];
    if (((flags >> 2) & 1) == 0)
        return false;

    uint32 i = 1;
    uint32 defA = 0xffffffff;
    if (flags & 1) { defA = p[1]; i = 2; }
    uint32 defB = 0xffffffff;
    if ((flags >> 1) & 1) { defB = p[i]; ++i; }
    if (p[i] != 0)
        return false;

    if (count != 0) {
        const uint32* q = p + i + 1;
        PFItemsMap& map = itemsMapOf(this);
        do {
            HashValue hv;
            hv.mPad          = 0;
            hv.mKey.group    = (flags & 1) ? defA : *q++;
            hv.mKey.instance = ((flags >> 1) & 1) ? defB : *q++;
            hv.mKey.type     = q[0];
            hv.mInfo.mOffset = (uint64)q[1];
            hv.mInfo.mSize   = q[2];
            hv.mInfo.mA      = q[3];
            hv.mInfo.mB      = q[4] & 1;
            q += 6;
            map.DoInsertValue(hv, true_type());
        } while (--count != 0);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006bf5d0  eastl::quick_sort_impl<HoleNode**> (recursive quicksort driver)
// ---------------------------------------------------------------------------
void FUN_006bf5d0(HoleNode** first, HoleNode** last, int depth, HoleLess cmp)
{
    while ((int)((char*)last - (char*)first) > 0x70 && depth > 0) {
        HoleNode** mid = first + ((last - first) >> 1);
        HoleNode** pivot = (HoleNode**)HoleTree_median3(first, mid, last - 1, cmp);
        HoleNode** cut = get_partition<HoleNode**, HoleNode*, HoleLess>(first, last, *pivot, cmp);
        --depth;
        FUN_006bf5d0(cut, last, depth, cmp);
        last = cut;
    }
    if (depth == 0) {
        partial_sort(first, last, last, cmp);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006bf8f0  HoleTree::DoInsertValueHint (rbtree insert with a hint node)
// ---------------------------------------------------------------------------
void HoleTree::DoInsertValueHint(uint32* outIter, HoleNode* hintNode, const HoleValue* value)
{
    HoleNodeBase* const pAnchor = &mAnchor;
    HoleNode* const pFirst = (HoleNode*)mAnchor.mpNodeParent;

    if ((HoleNodeBase*)hintNode == pAnchor || hintNode == pFirst) {
        if (mnSize != 0 && value->mOffset >= pFirst->mValue.mOffset &&
            (value->mOffset > pFirst->mValue.mOffset ||
             pFirst->mValue.mA < value->mA)) {
            HoleIter r = DoInsertValueImpl(pFirst, *value, false);
            *outIter = (uint32)r.mpNode;
            return;
        }
        HolePairIB r = DoInsertValue(*value, true_type());
        *outIter = (uint32)r.first.mpNode;
        return;
    }

    HoleNode* const pNext = (HoleNode*)RBTreeIncrement(hintNode);
    if (hintNode->mValue.mOffset <= value->mOffset &&
        (hintNode->mValue.mOffset < value->mOffset || hintNode->mValue.mA < value->mA) &&
        value->mOffset <= pNext->mValue.mOffset &&
        (value->mOffset < pNext->mValue.mOffset || value->mA < pNext->mValue.mA)) {
        const bool useHint = (hintNode->mValue.mOffset != 0);
        HoleIter r = DoInsertValueImpl(useHint ? (HoleNode*)pNext : hintNode, *value, useHint);
        *outIter = (uint32)r.mpNode;
        return;
    }

    HolePairIB r = DoInsertValue(*value, true_type());
    *outIter = (uint32)r.first.mpNode;
}

// ---------------------------------------------------------------------------
// @ 0x006bfc20  rbtree insert wrapper (returns the out-iter)
// ---------------------------------------------------------------------------
void* FUN_006bfc20(HoleTree* tree, uint32* outIter, HoleNode* hintNode, const HoleValue* value)
{
    tree->DoInsertValueHint(outIter, hintNode, value);
    return outIter;
}

// ---------------------------------------------------------------------------
// @ 0x006bfc50  HoleTreeC::FindHole
//   Find the smallest hole able to hold (a, b); on success carve it out (erase,
//   then re-insert the leftover tail) and return the hole's start offset.
// ---------------------------------------------------------------------------
uint64 HoleTreeC::FindHole(uint32 a, uint32 b)
{
    HoleTreeNode* const pAnchor = &mAnchor;
    HoleTreeNode* pNode = (HoleTreeNode*)mAnchor.mpNodeParent;
    HoleTreeNode* pBest = pAnchor;
    uint32 bestLo = 0xffffffff;
    uint32 bestHi = 0xffffffff;

    if (pNode != pAnchor) {
        do {
            const uint32 hi = *(uint32*)((char*)pNode + 0x1c);
            const uint32 lo = *(uint32*)((char*)pNode + 0x18);
            if (b <= hi && (hi != b || a <= lo) && hi <= bestHi &&
                (hi < bestHi || lo < bestLo)) {
                bestHi = hi;
                bestLo = lo;
                pBest = pNode;
                if (lo == a && hi == b) break;
            }
            pNode = (HoleTreeNode*)RBTreeIncrement(pNode);
        } while (pNode != pAnchor);

        if (pBest != pAnchor) {
            const uint64 oldStart = *(uint64*)((char*)pBest + 0x10);
            const uint32 holeLo = *(uint32*)((char*)pBest + 0x18);
            const uint32 holeHi = *(uint32*)((char*)pBest + 0x1c);
            const uint32 newLo  = holeLo + a;
            const uint32 newHi  = holeHi + b + (newLo < holeLo ? 1 : 0);
            const uint32 tailLo = holeLo - a;
            const uint32 tailHi = holeHi - b - (holeLo < a ? 1 : 0);

            --mnSize;
            RBTreeErase(pBest, pAnchor);
            DeleteTreeNode(pBest);

            if (tailLo != 0 || tailHi != 0) {
                HoleValue v;
                v.mOffset = ((uint64)newHi << 32) | newLo;
                v.mA      = tailLo;
                v.mB      = tailHi;
                uint32 outIter = 0;
                // Route through the shared insert helper on the tree view.
                ((HoleTree*)((char*)this - 8))->DoInsertValueHint(&outIter, 0, &v);
            }
            return oldStart;
        }
    }

    {
        // No hole fits: grow the table by (a, b) and return the previous total.
        const uint64 old = *(uint64*)this;
        const uint32 newLo = *(uint32*)this + a;
        const uint32 newHi = *(uint32*)((char*)this + 4) + b + (newLo < a ? 1 : 0);
        *(uint32*)((char*)this + 4) = newHi;
        *(uint32*)this = newLo;
        return old;
    }
}
