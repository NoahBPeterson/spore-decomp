// slice s00598340 -- SP::cCollectableItems helpers: rbtree insert/lower_bound, pool-backed ctor,
// editor base-unlock computation and collectable-item metadata.
// 0x00598540 (EnsureBaseUnlocksForEditor) is complete; the others are skeletons.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>

extern "C++" {
void* operator new(unsigned size, const char* tag, int a, int b, const char* file, int line);  // 0x00f473a0
void operator delete[](void* p);                                                               // 0x00f47380
}

// ---- property system -----------------------------------------------------------------------
struct cPropertyList {
    virtual void AddRef();
    virtual void Release();
};
struct IPropertyManager {
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5(); virtual void vf6(); virtual void vf7();
    virtual void vf8(); virtual void vf9(); virtual void vf10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** out);  // slot 11
};
IPropertyManager* PropertyManager();                                                        // 0x0067de30
bool GetPropertyAsUint32Array(cPropertyList* list, uint32_t id, int* count, uint32_t** out);  // 0x006a0840
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

// rows map (std::map<u64, fixed_vector<ItemID,4>>)
struct RowKey { uint32_t lo, hi; };
// Stack-local keys are padded to 12 bytes: a local 8-byte POD object (with a 64-bit op in the same
// function) makes cl 15.00 realign the frame (push ebp; and esp,-8), which the original lacks.
struct RowKeyLoc : RowKey { int pad; };
struct ItemIDLoc : ItemID { int pad; };
struct RowNode { char pad[0x18]; ItemID* mpBegin; };
struct RowIter { RowNode* node; };
struct RowMap {
    char pad[0x14 - 0x10];
    void find(RowIter* out, const RowKey* key);                               // 0x00a05730
};
struct StatusMap {
    uint8_t* index(const ItemID& id);                                           // 0x00595eb0
};
struct ListNode { ListNode* next; ListNode* prev; ItemID value; };

static inline RowKeyLoc MakeRowKey(uint32_t cat, uint32_t page, uint32_t row) {
    uint64_t r = ((uint64_t)cat << 32) | ((uint64_t)page << 16) | (int64_t)(int)row;
    RowKeyLoc k;
    k.lo = (uint32_t)r;
    k.hi = (uint32_t)(r >> 32);
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
    RowMap mRows;                    // +0x10 (std::map header at +0x14)
    char pad1[0x4d00 - 0x10 - sizeof(RowMap)];
    StatusMap mStatus;               // +0x4d00 (item status flags)
    char pad2[0x6d80 - 0x4d00 - sizeof(StatusMap)];
    ListNode* mListNext;             // +0x6d80 mUnlockedItems list head node
    ListNode* mListPrev;             // +0x6d84
    char pad3[0x100];

    void EnsureBaseUnlocksForEditor(uint32_t instanceID);                     // 0x00598540
    void AddCollectableItemInfo(int a, int b, int c, int d, int e, int f, int g); // 0x00598e90
    void FUN_00598340(void* a, void* b, void* c);                             // 0x00598340
    int  FUN_00598470(int a, int b);                                          // 0x00598470
    void* FUN_00598b50(void* a, void* b, void* c, void* d);                   // 0x00598b50
    int  FUN_00598cb0(void* a);                                               // 0x00598cb0
    void FUN_00598db0(int a, int b, int c, int d, int e, int f, int g, int h, int i); // 0x00598db0

    uint64_t GetRowIdForItem(uint32_t inst, uint32_t group);                  // 0x00595040
    bool IsItemUnlocked(uint32_t inst, uint32_t group);                       // 0x00595110
    void BuildCategoryMap(CatMap* dst, int a, int b);                         // 0x00597f00
};

}  // namespace SP

using namespace SP;

// @ 0x00598340 PARTIAL: EASTL rbtree lower_bound+insert; skeleton only.
void cCollectableItems::FUN_00598340(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }

// @ 0x00598470 PARTIAL: pool-backed construct; skeleton returns this.
int cCollectableItems::FUN_00598470(int a, int b) { (void)b; return (int)(size_t)this; }

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
                        ItemID* first = r1.node->mpBegin;
                        uint64_t rowId2 = GetRowIdForItem(first[0].instanceID, first[0].groupID);
                        RowKeyLoc k2;
                        k2.lo = (uint32_t)rowId2;
                        k2.hi = (uint32_t)(rowId2 >> 32);
                        RowIter r2;
                        mRows.find(&r2, &k2);
                        if (r2.node != (RowNode*)((char*)this + 0x14)) {
                            ItemID* src = r2.node->mpBegin;
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
                                ListNode* head = (ListNode*)&mListNext;
                                n->next = head;
                                n->prev = mListPrev;
                                mListPrev->next = n;
                                mListPrev = n;
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

// @ 0x00598b50 PARTIAL: rbtree node plumbing; skeleton returns 0.
void* cCollectableItems::FUN_00598b50(void* a, void* b, void* c, void* d) { (void)a; (void)b; (void)c; (void)d; return 0; }

// @ 0x00598cb0 PARTIAL: rbtree emplace; skeleton returns 0.
int cCollectableItems::FUN_00598cb0(void* a) { (void)a; return 0; }

// @ 0x00598db0 PARTIAL: 220 B metadata append; skeleton only.
void cCollectableItems::FUN_00598db0(int a, int b, int c, int d, int e, int f, int g, int h, int i) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; }

// @ 0x00598e90 PARTIAL: AddCollectableItemInfo 418 B; skeleton only.
void cCollectableItems::AddCollectableItemInfo(int a, int b, int c, int d, int e, int f, int g) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; }
