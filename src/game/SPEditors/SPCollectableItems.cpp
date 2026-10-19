// src/game/SPEditors/SPCollectableItems.cpp -- migrated from slice(s) s00599040, s00598340 by tools/migrate/rewrite.py
// Object file: SPEditors/SPCollectableItems.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCollectableItems.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cPropertyList.h"
#include <string.h>
#include "cSPUILayout.h"

// ---- items of slice s00598340 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ItemID { uint32_t instanceID, groupID; };
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
struct RowKey { uint32_t lo, hi; };
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
namespace SP {
class cCollectableItems_s0059_8340 {
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
};  // namespace SP
}
// ---- items of slice s00598340 end

// ---- items of slice s00599040 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cSPUILayout {
public:
    void* FindWindowByID(int id, int b);   // 0x008105b0
};
}
namespace SP {
class cSpaceInventory {
public:
    char pad0[0xc];
    cSPUILayout mLayout;                    // +0x0c
    char pad10[0x78 - (0xc + sizeof(cSPUILayout))];
    float mFloats[4];                       // +0x78
    char pad88[0xa8 - 0x88];
    void* mpA8;                             // +0xa8
    char padAc[0x6d74 - 0xac];
    int mField6d74;                         // +0x6d74

    bool FUN_00599440(int a, int b, int c);           // 0x00599440
    __declspec(noinline) void LoadConfiguration(int a, int b);   // 0x00599040
    void FUN_00599460();                              // 0x00599460
    void* FUN_005994d0();                             // 0x005994d0
    void FUN_00599530();                              // 0x00599530
    void FUN_00599560();                              // 0x00599560
    void FUN_005995d0();                              // 0x005995d0
    void FUN_00599730(void* a, void* b);              // 0x00599730
    __declspec(noinline) void FUN_005997f0(int a, int b, int c, int d, int e); // 0x005997f0
    void FUN_00599be0(int a);                         // 0x00599be0
    void FUN_00599c10(int a);                         // 0x00599c10

    // external (not in this slice)
    void FUN_00828020(int a);
    void FUN_00828010(float f);
    void FUN_00828be0();
    void FUN_00827fc0(const wchar_t* s, int a);
    void SetMaxCargoAmount(int a);
};
}
volatile int g_dummySideEffect;
#define SIDE_EFFECT() (g_dummySideEffect = 1)
// ---- items of slice s00599040 end

// @ 0x00598b50
void* SP::cCollectableItems_s0059_8340::FUN_00598b50(void* a, void* b, void* c, void* d)
{ (void)a; (void)b; (void)c; (void)d; return 0; }

// @ 0x00598cb0
int SP::cCollectableItems_s0059_8340::FUN_00598cb0(void* a)
{ (void)a; return 0; }

// @ 0x00598db0
void SP::cCollectableItems_s0059_8340::FUN_00598db0(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{ (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; }

// @ 0x00598e90
void SP::cCollectableItems_s0059_8340::AddCollectableItemInfo(int a, int b, int c, int d, int e, int f, int g)
{ (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; }

// @ 0x00599040
__declspec(noinline) void SP::cSpaceInventory::LoadConfiguration(int a, int b)
{ (void)a; (void)b; SIDE_EFFECT(); }
