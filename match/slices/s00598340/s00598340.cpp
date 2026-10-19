// slice s00598340 -- SP::cCollectableItems helpers: rbtree insert/lower_bound, pool-backed ctor,
// editor base-unlock computation and collectable-item metadata.
// All six targets are complete reconstructions (none byte-exact; see nonmatching.txt).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>

extern "C++" {
void* operator new(unsigned size, const char* tag, int a, int b, const char* file, int line);  // 0x00f473a0
void operator delete[](void* p);                                                               // 0x00f47380
}

// ---- property system -----------------------------------------------------------------------
struct Property;
struct cPropertyList {
    virtual void AddRef();                                                          // slot 0
    virtual void Release();                                                         // slot 1
    virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5();
    virtual void vf6(); virtual void vf7(); virtual void vf8();
    virtual bool GetProperty(uint32_t id, Property** out);                          // slot 9 (0x24)
    virtual void vf10();
};
struct Property {
    char pad0[0x12];
    uint16_t mType;                                                                 // +0x12
    int*   GetInt();                                                                // 0x0041e990
    float* GetFloat();                                                              // 0x0041ea70
};
struct IPropertyManager {
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5(); virtual void vf6(); virtual void vf7();
    virtual void vf8(); virtual void vf9(); virtual void vf10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** out);  // slot 11
};
IPropertyManager* PropertyManager();                                                        // 0x0067de30
bool GetPropertyAsUint32Array(cPropertyList* list, uint32_t id, int* count, uint32_t** out);  // 0x006a0840
void GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, void* out);                    // 0x006a12a0
extern uint32_t gEditorUnlockGroup;                                                         // 0x0150d514

struct PropListPtr {
    cPropertyList* mpObject;
    PropListPtr() : mpObject(0) {}
    ~PropListPtr() { if (mpObject) mpObject->Release(); }
    cPropertyList** operator&() {
        if (mpObject) {
            cPropertyList* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

// ---- random numbers --------------------------------------------------------------------------
struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t nLimit);    // 0x00a68fb0
};
extern RandomLinearCongruential gRandom;              // 0x01601760
void random_shuffle(uint32_t* first, uint32_t* last, RandomLinearCongruential& rng);  // 0x00afb8a0

// ---- eastl fixed_pool / hashtable entry points ------------------------------------------------
struct FixedPoolBase {
    void* mpHead;                                                               // +0
    void* mpNext;                                                               // +4
    void* mpBegin;                                                              // +8
    void* mpEnd;                                                                // +0xc
    uint32_t mnNodeSize;                                                        // +0x10
    void* mpOwner;                                                              // +0x14
    void  init(void* pBegin, uint32_t nSize, uint32_t nNodeSize, uint32_t nAlign, uint32_t nFlags); // 0x00921260
    uint32_t fn13c0(uint32_t n);                                                // 0x009213c0
};
int   FUN_00921340(int a);                                                          // 0x00921340
extern float gF10000;      // 0x013f0620
extern float gF2;          // 0x01470f1c
extern float gF1;          // 0x01485720
extern char  gRowVecTag;   // 0x013f6228

// ---- containers -------------------------------------------------------------------------------
struct ItemID { uint32_t instanceID, groupID; };

// eastl::fixed_vector<uint32_t, N> (begin/end/capacity, 3 allocator words, buffer)
template <int N>
struct FixedVec32 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc0;
    uint32_t* mpPool;
    uint32_t mAlloc2;
    uint32_t mBuffer[N];

    FixedVec32() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
        mpPool = mBuffer;
    }
    ~FixedVec32() {
        if (mpBegin && mpBegin != mpPool)
            operator delete[](mpBegin);
    }
    void DoInsertValue(uint32_t* pos, const uint32_t& v);                      // 0x0060a600
    void push_back(const uint32_t& v) {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
    void erase_first() {
        uint32_t* first = mpBegin;
        uint32_t* next = first + 1;
        if (next < mpEnd)
            memcpy(first, next, (size_t)((char*)mpEnd - (char*)next));
        --mpEnd;
    }
};

// page table: cCollectableItemID-style key -> 4 x u16 (field_4 = bitmask of locked columns)
struct PageNode {
    uint32_t key;
    uint32_t pad;
    union { uint64_t q; uint16_t w[4]; } v;
    PageNode* next;
};
struct PageIter { PageNode* node; PageNode** bucket; };
struct PagePair { uint32_t key; uint32_t pad; uint32_t value0; uint32_t value1; };
struct InsertTag { bool b; };
struct PageHT {
    void* mAlloc;
    PageNode** mpBuckets;
    uint32_t mBucketCount;
    uint32_t mElemCount;
    char pad[0xDC - 16];
    void begin(PageIter* out);                                                  // 0x00594410
    void insert(PageIter* out, const PagePair& v, InsertTag t);                 // 0x00594e20
    __forceinline PageIter find(uint32_t k) {
        uint32_t n = k % mBucketCount;
        for (PageNode* p = mpBuckets[n]; p; p = p->next) {
            if (k == p->key) {
                PageIter r;
                r.node = p;
                r.bucket = mpBuckets + n;
                return r;
            }
        }
        PageIter e;
        e.node = mpBuckets[mBucketCount];
        e.bucket = mpBuckets + mBucketCount;
        return e;
    }
};

// category map: uint32 category -> page table
struct CatNode {
    uint32_t key;
    PageHT pages;
    CatNode* next;
};
struct CatIter { CatNode* node; CatNode** bucket; };
struct Empty {};
struct CatMap {
    void* mAlloc;
    CatNode** mpBuckets;
    uint32_t mBucketCount;
    uint32_t mElemCount;
    char pad10[0xC];
    void** mpHead;           // +0x1c free-list head
    uint32_t pad20;
    char* mpPoolBegin;       // +0x24
    char* mpPoolEnd;         // +0x28
    uint32_t pad2c;
    CatNode** mpFixedBuckets;  // +0x30
    char rest[0x888 - 0x34];

    CatMap(const Empty& a, const Empty& b);                                     // 0x00598470
    void FUN_00594760(int u, void* p2, void* p3, void* p4, void* p5, void* p6, FixedPoolBase* pool); // 0x00594760
    void FUN_00594030(uint32_t n);                                              // 0x00594030
    void DoFreeNodes(CatNode** buckets, uint32_t count);                        // 0x00597b30
    void find(CatIter* out, const uint32_t* key);                               // 0x00594ee0
    ~CatMap() {
        DoFreeNodes(mpBuckets, mBucketCount);
        mElemCount = 0;
        if (mBucketCount > 1 && (CatNode**)mpBuckets != mpFixedBuckets) {
            char* p = (char*)mpBuckets;
            if (p < mpPoolBegin || p >= mpPoolEnd)
                operator delete[](p);
            else
                *(void**)p = mpHead;
        }
    }
};

// rows map: eastl::map<uint64_t, fixed_vector<ItemID,4>>
struct RowKey { uint32_t lo, hi; };
// Stack-local keys are padded to 12 bytes: a local 8-byte POD object (with a 64-bit op in the same
// function) makes cl 15.00 realign the frame (push ebp; and esp,-8), which the original lacks.
struct RowKeyLoc : RowKey { int pad; };
struct ItemIDLoc : ItemID { int pad; };

struct RowNode;
RowNode* RBTreeIncrement(RowNode* p);                                          // 0x00921580
RowNode* RBTreeDecrement(const RowNode* p);                                    // 0x009215c0
void RBTreeInsert(RowNode* pNode, RowNode* pParent, void* pAnchor, int side);  // 0x009216a0

// fixed_vector<ItemID,4> (begin/end/capacity, allocator word, pool, 8-aligned inline buffer)
struct FixedVec4 {
    ItemID* mpBegin;                                                            // +0
    ItemID* mpEnd;                                                              // +4
    ItemID* mpCapacity;                                                         // +8
    uint32_t mAllocator;                                                        // +0xc
    ItemID* mpPoolBegin;                                                        // +0x10
    uint32_t mPad;                                                              // +0x14
    ItemID mBuffer[4];                                                          // +0x18
    void DoAssignFromIterator(const ItemID* first, const ItemID* last, const void* tag); // 0x005972f0
    void Resize(uint32_t n, const void* tag);                                   // 0x00597530
};

// map value: pair<RowKey, fixed_vector<ItemID,4>>  (key + inline vector)
struct RowValue {
    RowKey first;                                                               // +0 (lo), +4 (hi)
    FixedVec4 second;                                                           // +8
    RowValue() {
        first.lo = first.hi = 0;
        second.mpBegin = second.mpEnd = second.mpPoolBegin = second.mBuffer;
        second.mpCapacity = second.mBuffer + 4;
    }
    RowValue(const RowValue& x) : first(x.first) {
        second.mpBegin = second.mpEnd = second.mpPoolBegin = second.mBuffer;
        second.mpCapacity = second.mBuffer + 4;
        second.DoAssignFromIterator(x.second.mpBegin, x.second.mpEnd, &x);
    }
    ~RowValue() {
        if (second.mpBegin && second.mpBegin != second.mpPoolBegin)
            operator delete[](second.mpBegin);
    }
};

struct RowNode {
    RowNode* mpNodeRight;                                                       // +0
    RowNode* mpNodeLeft;                                                        // +4
    RowNode* mpNodeParent;                                                      // +8
    char mColor;                                                                // +0xc
    char pad[3];
    RowValue mValue;                                                            // +0x10
};
struct RowIter { RowNode* node; };
struct InsertResult { RowNode* node; char inserted; char pad[3]; };
struct RowMap {
    uint32_t mCompare;                                                          // +0
    struct Anchor { RowNode* mpNodeRight; RowNode* mpNodeLeft; RowNode* mpNodeParent; char mColor; char pad[3]; } mAnchor; // +4
    uint32_t mnSize;                                                            // +0x14
    struct Pool { void* mpHead; void* mpNext; void* mpPoolBegin; void* mpCapacity; uint32_t mnNodeSize; } mAllocator; // +0x18

    __declspec(noinline) RowNode* DoCreateNode(const RowValue* v);              // 0x00598260
    __declspec(noinline) void DoInsertValueImpl(void* out, RowNode* parent, const RowValue* v, int side); // 0x005982e0
    __declspec(noinline) void DoInsertUnique(void* out, const RowValue* v);      // 0x00598340
    void find(RowIter* out, const RowKey* key);                                 // 0x00a05730
    void find64(RowIter* out, const RowKey* key);                               // 0x00a057f0
    __declspec(noinline) void* insert_hint(void* out, RowNode* pos, const RowValue* v, void* x); // 0x00598b50
    __declspec(noinline) FixedVec4* find_or_insert(const uint64_t& key);        // 0x00598cb0
};
struct StatusMap {
    uint8_t* index(const ItemID& id);                                           // 0x00595eb0
};
struct cStaticItemInfo {
    uint32_t mField0;                                                           // +0
    float    mField4;                                                           // +4
    uint32_t mField8;                                                           // +8
    uint32_t mFieldC;                                                           // +0xc
    uint32_t mField10;                                                          // +0x10
    uint32_t mField14;                                                          // +0x14
    uint32_t mField18;                                                          // +0x18
};
struct ItemInfoMap {
    char opaque[0x3874];
    cStaticItemInfo* index(const ItemID& id);                                   // 0x00595d40
};
struct ListNode { ListNode* next; ListNode* prev; ItemID value; };
struct UnlockedList {
    ListNode* mpNext;                                                           // +0
    ListNode* mpPrev;                                                           // +4
    void push_back(const ItemID& id);                                           // 0x00594b10
};

static inline bool KeyLess(const RowKey& a, const RowKey& b) {
    if (a.hi != b.hi) return a.hi < b.hi;
    return a.lo < b.lo;
}
static inline RowKeyLoc MakeRowKey(uint32_t cat, uint32_t page, uint32_t row) {
    uint64_t r = ((uint64_t)cat << 32) | ((uint64_t)page << 16) | (int64_t)(int)row;
    RowKeyLoc k;
    k.lo = (uint32_t)r;
    k.hi = (uint32_t)(r >> 32);
    return k;
}
static inline RowKey MakeKey64(uint64_t v) {
    RowKey k;
    k.lo = (uint32_t)v;
    k.hi = (uint32_t)(v >> 32);
    return k;
}
static inline uint32_t Ctz32(uint32_t x) {
    if (x == 0) return 32;
    uint32_t n = 1;
    if ((x & 0xffff) == 0) { n += 16; x >>= 16; }
    if ((x & 0xff) == 0) { n += 8; x >>= 8; }
    if ((x & 0xf) == 0) { n += 4; x >>= 4; }
    if ((x & 3) == 0) { n += 2; x >>= 2; }
    return n - (x & 1);
}

namespace SP {

class cCollectableItems {
public:
    char pad0[0x10];
    RowMap mRows;                    // +0x10 (map header/anchor at +0x14)
    char pad1[0x148c - 0x10 - sizeof(RowMap)];
    ItemInfoMap mItemInfo;           // +0x148c (fixed_hash_map<ItemID, cStaticItemInfo>)
    StatusMap mStatus;               // +0x4d00 (item status flags)
    char pad2[0x6d80 - 0x4d00 - sizeof(StatusMap)];
    UnlockedList mUnlocked;          // +0x6d80 mUnlockedItems list sentinel
    char pad3[0x100];

    void EnsureBaseUnlocksForEditor(uint32_t instanceID);                        // 0x00598540
    void FUN_00598db0(int a, int b, int c, int d, int e, int f, int g, int h, int i); // 0x00598db0
    bool AddCollectableItemInfo(int a, int b, int c, int d, int e, int f, int g); // 0x00598e90

    uint64_t GetRowIdForItem(uint32_t inst, uint32_t group);                     // 0x00595040
    bool IsItemUnlocked(uint32_t inst, uint32_t group);                          // 0x00595110
    void BuildCategoryMap(CatMap* dst, int a, int b);                            // 0x00597f00
};

}  // namespace SP

using namespace SP;

// @ 0x00598340
// rbtree unique-insert: lower_bound(the value's key) then link the new node at the found slot
// (or return the existing equal node), reporting {node,bool} through `out`.
void RowMap::DoInsertUnique(void* out, const RowValue* v) {
    RowNode* const header = (RowNode*)&mAnchor;
    const RowKey vk = v->first;
    RowNode* y = header;
    bool comp = true;
    for (RowNode* x = mAnchor.mpNodeParent; x != 0; x = comp ? x->mpNodeLeft : x->mpNodeRight) {
        y = x;
        comp = KeyLess(vk, x->mValue.first);
    }
    RowNode* j = y;
    if (comp) {
        if (j == mAnchor.mpNodeLeft) {
            int side = (y == header || KeyLess(vk, y->mValue.first)) ? 0 : 1;
            RowNode* const n = DoCreateNode(v);
            RBTreeInsert(n, y, &mAnchor, side);
            ++mnSize;
            *(RowNode**)out = n;
            *((char*)out + 4) = 1;
            return;
        }
        j = RBTreeDecrement(j);
    }
    if (!(j->mValue.first.hi > vk.hi ||
          (j->mValue.first.hi == vk.hi && j->mValue.first.lo >= vk.lo))) {
        int side = (y == header || KeyLess(vk, y->mValue.first)) ? 0 : 1;
        RowNode* const n = DoCreateNode(v);
        RBTreeInsert(n, y, &mAnchor, side);
        ++mnSize;
        *(RowNode**)out = n;
        *((char*)out + 4) = 1;
        return;
    }
    *(RowNode**)out = j;
    *((char*)out + 4) = 0;
}

// @ 0x00598470
// pool-backed hashtable construct: init the fixed_pool over [this+0x5c, this+0x77c) (node size
// 0xe4) and hand it to the map constructor, then set the load factors and prime the buckets.
CatMap::CatMap(const Empty& a, const Empty& b) {
    char* const self = (char*)this;
    FixedPoolBase pool;
    pool.mpHead = 0;
    pool.init(self + 0x5c, 0x720, 0xe4, 4, 0);
    pool.mpBegin = self + 0x5c;
    pool.mpEnd = self + 0x77c;
    pool.mnNodeSize = 0xe4;
    pool.mpOwner = self + 0x34;
    int u = FUN_00921340(9);
    FUN_00594760(u, (void*)&a, (void*)&b, (void*)&b, (void*)&b, (void*)&b, &pool);
    u = *(int*)&gF10000;
    int f2 = *(int*)&gF2;
    *(uint32_t*)(self + 0x10) = (uint32_t)u;
    *(uint32_t*)(self + 0x14) = (uint32_t)f2;
    pool.mpBegin = 0;
    *(uint32_t*)(self + 0x18) = 0;
    uint32_t v = pool.fn13c0(*(int*)(self + 0xc));
    if (*(uint32_t*)(self + 8) < v)
        FUN_00594030(v);
}

// @ 0x00598540 EnsureBaseUnlocksForEditor: for each (category, count) pair of the editor's
// "base unlocks" property, randomly unlocks `count` items from that category's page table
// (shuffled page keys, random unlockable column of a page), marking them Unlocked|Highlighted.
void cCollectableItems::EnsureBaseUnlocksForEditor(uint32_t instanceID) {
    PropListPtr list;
    int count = 0;
    uint32_t* arr = 0;
    if (PropertyManager()->GetPropertyList(instanceID, gEditorUnlockGroup, &list)) {
        if (GetPropertyAsUint32Array(list.mpObject, 0x57e9439, &count, &arr)) {
            if (count % 2 == 0) {
                Empty e1, e2;
                CatMap map(e1, e2);
                BuildCategoryMap(&map, 1, 0);
                for (int i = 0; i < count; i += 2) {
                    uint32_t cat = arr[i];
                    uint32_t wanted = arr[i + 1];
                    CatIter cit;
                    map.find(&cit, &cat);
                    if (cit.node != map.mpBuckets[map.mBucketCount]) {
        PageHT& pages = cit.node->pages;
        FixedVec32<16> keys;
        PageIter pit;
        pages.begin(&pit);
        while (pit.node != pages.mpBuckets[pages.mBucketCount]) {
            keys.push_back(pit.node->key);
            pit.node = pit.node->next;
            while (!pit.node) {
                ++pit.bucket;
                pit.node = *pit.bucket;
            }
        }

        uint32_t done = 0;
        if (wanted != 0) {
            uint32_t rounds = 0;
            do {
                if (keys.mpBegin == keys.mpEnd)
                    break;
                if (rounds++ >= 100)
                    break;
                random_shuffle(keys.mpBegin, keys.mpEnd, gRandom);
                uint32_t* firstKey = keys.mpBegin;
                uint32_t page = *firstKey;

                PageIter found = pages.find(page);
                PageNode* node;
                if (found.node == pages.mpBuckets[pages.mBucketCount]) {
                    PagePair pair;
                    pair.key = page;
                    pair.value0 = 0;
                    pair.value1 = 0;
                    InsertTag tag;
                    tag.b = false;
                    PageIter res;
                    pages.insert(&res, pair, tag);
                    node = res.node;
                } else
                    node = found.node;
                uint64_t* item = &node->v.q;
                uint16_t* itemW = node->v.w;

                FixedVec32<16> bits;
                for (uint32_t m = itemW[2]; m != 0; m &= m - 1)
                    bits.push_back(Ctz32(m));
                uint32_t bit = bits.mpBegin[gRandom.RandomUint32Uniform((uint32_t)(bits.mpEnd - bits.mpBegin))];

                if ((1ULL << bit) & (int64_t)(int)itemW[2]) {
                    RowKeyLoc k1 = MakeRowKey(cat, page, bit);
                    RowIter r1;
                    mRows.find(&r1, &k1);
                    if (r1.node != (RowNode*)((char*)this + 0x14)) {
                        ItemID* first = r1.node->mValue.second.mpBegin;
                        uint64_t rowId2 = GetRowIdForItem(first[0].instanceID, first[0].groupID);
                        RowKeyLoc k2;
                        k2.lo = (uint32_t)rowId2;
                        k2.hi = (uint32_t)(rowId2 >> 32);
                        RowIter r2;
                        mRows.find(&r2, &k2);
                        if (r2.node != (RowNode*)((char*)this + 0x14)) {
                            ItemID* src = r2.node->mValue.second.mpBegin;
                            ItemIDLoc id;
                            id.instanceID = src->instanceID;
                            id.groupID = src->groupID;
                            if (!IsItemUnlocked(id.instanceID, id.groupID)) {
                                *mStatus.index(id) |= 3;
                                ListNode* n = (ListNode*)operator new(
                                    16, "Editor", 0, 0,
                                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                    0xd1);
                                if (&n->value) {
                                    n->value.instanceID = id.instanceID;
                                    n->value.groupID = id.groupID;
                                }
                                ListNode* head = (ListNode*)&mUnlocked.mpNext;
                                n->next = head;
                                n->prev = mUnlocked.mpPrev;
                                mUnlocked.mpPrev->next = n;
                                mUnlocked.mpPrev = n;
                            }
                        }
                        *item &= ~(1ULL << (bit + 32));
                        ++done;
                    }
                }
                if (itemW[2] == 0)
                    keys.erase_first();
            } while (done < wanted);
        }
                    }
                }
            }
        }
    }
}

// @ 0x00598b50
// rbtree insert with a position hint: if `pos` is a valid neighbourhood for `v`, link the new node
// relative to it; otherwise fall back to a plain unique-insert. Returns the {node} report.
void* RowMap::insert_hint(void* out, RowNode* pos, const RowValue* v, void* x) {
    (void)x;
    RowNode* const header = (RowNode*)&mAnchor;
    RowNode* const first = mAnchor.mpNodeRight;
    if (pos != first && pos != header) {
        RowNode* nb = RBTreeIncrement(pos);
        if (KeyLess(pos->mValue.first, v->first) && KeyLess(v->first, nb->mValue.first)) {
            if (pos->mpNodeRight != 0)
                DoInsertValueImpl(out, nb, v, 1);
            else
                DoInsertValueImpl(out, pos, v, 0);
            return out;
        }
        goto fallback;
    }
    if (mnSize != 0 && KeyLess(first->mValue.first, v->first)) {
        int side = (first == header || KeyLess(v->first, first->mValue.first)) ? 0 : 1;
        RowNode* const n = DoCreateNode(v);
        RBTreeInsert(n, first, &mAnchor, side);
        ++mnSize;
        *(RowNode**)out = n;
        return out;
    }
fallback:
    {
        InsertResult r;
        DoInsertUnique(&r, v);
        *(RowNode**)out = r.node;
        return out;
    }
}

// @ 0x00598cb0
// map::operator[] insert side: find the key, insert a fresh value built from *key when absent, and
// return a pointer just past the key of the stored element (i.e. the inline fixed_vector).
FixedVec4* RowMap::find_or_insert(const uint64_t& key) {
    RowIter it;
    find64(&it, (const RowKey*)&key);
    RowNode* p = it.node;
    RowKey k = MakeKey64(key);
    if (p == (RowNode*)&mAnchor || KeyLess(k, p->mValue.first)) {
        RowValue v;
        v.first = k;
        insert_hint(&p, p, &v, 0);
    }
    return &p->mValue.second;
}

// @ 0x00598db0
// Append per-item static metadata: fill the (a0,a1) item-info record from the nine scalars, push the
// item id into the row vector selected by the (category,page,row) key, and touch the status map.
void cCollectableItems::FUN_00598db0(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    ItemID key;
    key.instanceID = (uint32_t)a0;
    key.groupID = (uint32_t)a1;
    cStaticItemInfo* info = mItemInfo.index(key);
    info->mField0 = (uint32_t)(a2 - 1);
    info->mField8 = (uint32_t)a3;
    info->mField18 = (uint32_t)a8;
    info->mFieldC = (uint32_t)a4;
    info->mField10 = (uint32_t)a5;
    info->mField14 = (uint32_t)a6;
    info->mField4 = *(float*)&a7;
    uint64_t k = ((uint64_t)(uint32_t)a3 << 32) |
                 ((uint64_t)(int64_t)(int32_t)a6 << 16) |
                 (uint64_t)(int64_t)(int32_t)a5;
    FixedVec4* vec = mRows.find_or_insert(k);
    if (a4 >= (int)(vec->mpEnd - vec->mpBegin))
        vec->Resize((uint32_t)a4 + 1, &gRowVecTag);
    vec->mpBegin[a4] = key;
    mStatus.index(key);
}

// @ 0x00598e90
// AddCollectableItemInfo: read the item's category/price properties, register the static metadata
// and, when the item is valued at least 1.0 (or the debug override is on), flag it unlocked.
bool cCollectableItems::AddCollectableItemInfo(int p0, int p1, int p2, int p3, int p4, int p5, int p6) {
    (void)p1;
    PropListPtr list;
    IPropertyManager* pm = PropertyManager();
    if (list.mpObject) {
        cPropertyList* t = list.mpObject; list.mpObject = 0; t->Release();
    }
    if (!pm->GetPropertyList((uint32_t)p0, (uint32_t)p2, &list))
        return false;

    ItemID key;
    key.instanceID = (uint32_t)p0;
    key.groupID = (uint32_t)p2;

    uint64_t lookupId = 0;
    int ival = 0;
    float fval = 0.0f;
    if (list.mpObject) {
        Property* prop;
        if (list.mpObject->GetProperty(0x3a289ac, &prop) && prop->mType == 9)
            ival = *prop->GetInt();
        if (list.mpObject->GetProperty(0x3a289c3, &prop) && prop->mType == 0xd)
            fval = *prop->GetFloat();
    }
    GetPropertyAsKeyInstance(list.mpObject, 0xd3bcdc94, &lookupId);

    FUN_00598db0(p0, p2, ival, p3, p4, p5, p6, *(int*)&fval, (int)(uint32_t)lookupId);

    if (*(int*)(*(int*)(*(int*)0x015fd918 + 0x3c) + 0x118) != 0 || fval >= gF1) {
        if ((*mStatus.index(key) & 4) == 0) {
            *mStatus.index(key) |= 1;
            mUnlocked.push_back(key);
        }
    }
    return true;
}
