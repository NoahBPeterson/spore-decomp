// Slice s0103e8e0: SP::cSPSpaceTrading::CreateNPCInventory @ 0x0103e8e0 (PDB name via card).
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc), same module as s0103eff0 (PerformTrade); the retail layout
// follows ModAPI's Simulator::cSpaceTrading (mNPCStore +0x48, field_74 +0x74, mLastNPCStoreIndex +0x9c).
//
// Given the planet being visited (arg1, a cStarRecordRef-like object with GetCommContext() @ 0x00ce6950):
//   1. drops this planet's NPC stores older than 30 minutes,
//   2. finds this planet's store (or, if none, creates one, evicting the oldest when 5 exist),
//   3. clears a store flagged for reset, or, when the store is not new, mirrors its stock into field_74 as
//      zero-count placeholders (spice/rare tools with no stock are zeroed first),
//   4. runs every commodity of this->mCommodities through a per-kind handler (tool/spice/rare/...) and remembers
//      which commodity is the planet's spice and which is the store's spice,
//   5. if arg2 is nonzero, posts one of two text lines about one of those two commodities,
//   6. sorts field_74.
#include "types.h"
#include <new>

struct ResourceKey {
    uint32_t instance, type, group;
};
inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
    return a.instance == b.instance && a.type == b.type && a.group == b.group;
}

#define VSLOT(n) virtual void _v##n();

// App::PropertyList (ref counted: AddRef +0, Release +4)
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
};
void GetPropertyAsKey(PropertyList* list, uint32_t id, ResourceKey* out);       // 0x006a1250
void GetPropertyAsText(PropertyList* list, uint32_t id, int arg);               // 0x006a1360

struct PropertyManager {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst);   // +0x2c
};
PropertyManager* PropertyManager_Get();                                         // 0x0067de30

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    intrusive_ptr(const intrusive_ptr& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T** AsOutParam()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
        return &mpObject;
    }
    intrusive_ptr& operator=(T* p)
    {
        T* const pTemp = mpObject;
        if (p != pTemp) {
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    intrusive_ptr& operator=(const intrusive_ptr& o) { return operator=(o.mpObject); }
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

// Inventory item: ref count at +0x04 (AddRef +4, Release +8), property list at +0x30.
struct cSpaceInventoryItem {
    VSLOT(0)
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
    VSLOT(3)
    virtual uint32_t GetType();                                              // +0x10
    virtual void SetItemID(const ResourceKey& key);                          // +0x14
    virtual const ResourceKey& GetItemID();                                  // +0x18

    uint32_t mnRefCount;                                                     // +0x04
    uint32_t pad08[2];
    int mItemCount;                                                          // +0x10
    uint32_t mItemType;                                                      // +0x14
    uint32_t mItemCost;                                                      // +0x18
    uint32_t pad1c[5];
    PropertyList* mpPropList;                                                // +0x30

    int GetUnitValue_006c0200();
};
typedef intrusive_ptr<cSpaceInventoryItem> ItemPtr;

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct cSPTimer {
    uint64_t GetElapsedTime();                                               // 0x00bc3190
    void Restart();                                                          // 0x00bc3130
};

// Simulator::cNPCStore (0xc0 bytes): IRefCount sub-object at +8 (AddRef +0, Release +4).
struct cNPCStoreBase { virtual void _b0(); uint32_t pad04; };
struct IRefCount { virtual int AddRef(); virtual int Release(); };
struct cNPCStore : cNPCStoreBase, IRefCount {
    uint32_t mPlanetKey;                                                     // +0x0c
    cSPTimer mTimer;                                                         // +0x10
    uint32_t pad14[(0x30 - 0x14) / 4];
    int mSpiceBought;                                                        // +0x30
    vector<ItemPtr> mNPCInventory;                                           // +0x34
    uint32_t pad44[(0x5c - 0x44) / 4];
    uint8_t mbNeedsReset;                                                    // +0x5c
    uint8_t pad5d[3];
    ResourceKey* mpSpiceID;                                                  // +0x60
    uint32_t pad64[(0xc0 - 0x64) / 4];
    cNPCStore();                                                             // 0x0103cf20
};
typedef intrusive_ptr<cNPCStore> NPCStorePtr;

void* operator new(size_t, const char*, int, int, int, int);                 // 0x00f473a0

// fixed_vector<NPCStorePtr, 5> (begin +0x48, end +0x4c, capacity +0x50)
struct NPCStoreVector {
    NPCStorePtr* mpBegin;
    NPCStorePtr* mpEnd;
    NPCStorePtr* mpCapacity;
    uint32_t mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    NPCStorePtr& operator[](int i) { return mpBegin[i]; }
    NPCStorePtr& back() { return *(mpEnd - 1); }
    void DoInsertValue(NPCStorePtr* position, const NPCStorePtr& value);     // 0x0103c550
    void push_back(const NPCStorePtr& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) NPCStorePtr(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void pop_back()
    {
        --mpEnd;
        mpEnd->~NPCStorePtr();
    }
    void erase(NPCStorePtr* position)
    {
        if (position + 1 < mpEnd)
            CopyRange(position + 1, mpEnd, position);
        --mpEnd;
        mpEnd->~NPCStorePtr();
    }
    static NPCStorePtr* __cdecl CopyRange(NPCStorePtr* first, NPCStorePtr* last, NPCStorePtr* dest);   // 0x00ad73a0
};

// The object passed in by the caller (the planet the player is trading at).
struct cEmpire {
    uint32_t* GetStars();                                                    // 0x00c308d0 (returns this+0x88)
};
struct cStarManager {
    cEmpire* GetEmpireByID(uint32_t id);                                     // 0x00ba9370
};
cStarManager* StarManager();                                                 // 0x00b3d2a0
struct cAvatarHolder {
    uint32_t GetAvatarEmpireID();                                            // 0x00b1fdb0
};
struct cPlanetRef {
    uint32_t GetCommContext();                                               // 0x00ce6950
    cAvatarHolder* GetAvatarHolder();                                        // 0x00b8de30
    ResourceKey* GetSpiceKey();                                              // 0x00b8dad0 (this+0x198)
};

namespace EA { namespace Random { struct RandomLinearCongruential { double RandomDoubleUniform(); }; } }   // 0x009360d0
extern const float kHalf;                                                   // 0x01471064
extern EA::Random::RandomLinearCongruential gRandom;                         // 0x01601760

// eastl::sort over the ItemPtr range with the comparator at 0x0103bf70
typedef bool (__cdecl *ItemCompare)(const ItemPtr&, const ItemPtr&);
bool __cdecl ItemLess(const ItemPtr&, const ItemPtr&);                       // 0x0103bf70
void __cdecl QuickSortImpl(ItemPtr* first, ItemPtr* last, int depth, ItemCompare cmp);          // 0x0103c800
void __cdecl InsertionSort(ItemPtr* first, ItemPtr* last, ItemCompare cmp);                      // 0x0103a0e0
void __cdecl InsertionSortUnguarded(ItemPtr* first, ItemPtr* last, ItemCompare cmp);             // 0x0103a1b0
ItemPtr* __cdecl CopyItemPtrs(ItemPtr* first, ItemPtr* last, ItemPtr* dest);                     // 0x0062ffd0

inline int Log2(int n)
{
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return i - 1;
}
inline void SortItems(ItemPtr* first, ItemPtr* last, ItemCompare cmp)
{
    if (first != last) {
        QuickSortImpl(first, last, 2 * Log2((int)(last - first)), cmp);
        if (last - first > 28) {
            InsertionSort(first, first + 28, cmp);
            InsertionSortUnguarded(first + 28, last, cmp);
        } else {
            InsertionSort(first, last, cmp);
        }
    }
}

namespace SP {
class cSPSpaceTrading {
public:
    uint32_t pad00[0x34 / 4];
    vector<ResourceKey> mCommodities;                                        // +0x34
    uint32_t pad44;
    NPCStoreVector mNPCStore;                                                // +0x48
    uint32_t pad58[(0x74 - 0x58) / 4];
    vector<ItemPtr> field_74;                                                // +0x74
    uint32_t pad84[(0x9c - 0x84) / 4];
    int mLastNPCStoreIndex;                                                  // +0x9c

    void CreateCommodityFromID(ItemPtr& dst, const ResourceKey& id, int count, float cost);   // 0x0103a480
    bool FUN_0103b320(PropertyList* list);
    void RefreshNPCSpiceCosts(cPlanetRef* planet);                           // 0x0103cd00
    void ConsiderBuyingRareGroup(ResourceKey key);                           // 0x0103d580
    void CreateCommodityEntry_0103d720(cEmpire* empire, ResourceKey key);    // 0x0103d720
    void FUN_0103d9b0(cPlanetRef* planet, ResourceKey key);
    void ConsiderSellingTool(cPlanetRef* planet, uint32_t flag, ResourceKey key);   // 0x0103dee0
    void FUN_0103e6e0(cPlanetRef* planet, ResourceKey key);
    void CreateNPCInventory(cPlanetRef* planet, int text);
};
}
using SP::cSPSpaceTrading;

// @ 0x0103e8e0
void cSPSpaceTrading::CreateNPCInventory(cPlanetRef* planet, int text)
{
    int numCommodities = mCommodities.size();
    int spiceOfStore = 0;
    int spiceOfPlanet = 0;
    uint32_t planetKey = planet->GetCommContext();

    // Drop this planet's stores older than 30 minutes.
    for (int i = 0; i < mNPCStore.size(); ++i) {
        cNPCStore* store = mNPCStore[i].get();
        if (store->mPlanetKey == planetKey) {
            if (store->mTimer.GetElapsedTime() > 1800000) {
                NPCStorePtr& slot = mNPCStore[i];
                slot = mNPCStore.back().get();
                mNPCStore.pop_back();
                --i;
            }
        }
    }

    bool isNew = true;
    int numStores = mNPCStore.size();
    vector<ItemPtr>* pInventory = (vector<ItemPtr>*)planet;
    for (int i = 0; i < numStores; ++i) {
        if (mNPCStore[i]->mPlanetKey == planetKey) {
            mLastNPCStoreIndex = i;
            isNew = false;
            pInventory = &mNPCStore[i]->mNPCInventory;
        }
    }

    if (isNew) {
        if ((uint32_t)numStores >= 5)
            mNPCStore.erase(mNPCStore.mpBegin);
        cNPCStore* pNew = new ("Simulator/cNPCStore", 0, 0, 0, 0) cNPCStore();
        {
            NPCStorePtr store(pNew);
            mNPCStore.push_back(store);
        }
        mLastNPCStoreIndex = mNPCStore.size() - 1;
        pInventory = &pNew->mNPCInventory;
        pNew->mPlanetKey = planetKey;
        pNew->mTimer.Restart();
        pNew->mSpiceBought = 0;
        pNew->mbNeedsReset = 0;
        RefreshNPCSpiceCosts(planet);
    }

    if (mNPCStore[mLastNPCStoreIndex]->mbNeedsReset) {
        mNPCStore[mLastNPCStoreIndex]->mbNeedsReset = 0;
        // erase(begin, end)
        ItemPtr* first = pInventory->mpBegin;
        ItemPtr* last = pInventory->mpEnd;
        ItemPtr* i = CopyItemPtrs(last, last, first);
        ItemPtr* end = pInventory->mpEnd;
        for (; i < end; ++i)
            i->~ItemPtr();
        isNew = true;
        pInventory->mpEnd = pInventory->mpEnd - (last - first);
    } else if (!isNew) {
        int n = pInventory->size();
        for (int j = 0; j < n; ++j) {
            ResourceKey kind = {0, 0, 0};
            cSpaceInventoryItem* item = (*pInventory)[j].get();
            GetPropertyAsKey(item->mpPropList, 0x34f1a4f, &kind);
            if (kind.instance == 0x82af541 || (kind.instance == 0x4edcc2bf && !FUN_0103b320(item->mpPropList)))
                item->mItemCount = 0;
            if (item->mItemCount > 0) {
                ItemPtr placeholder;
                CreateCommodityFromID(placeholder, item->GetItemID(), 0, (float)item->GetUnitValue_006c0200());
                field_74.push_back(placeholder);
            }
        }
    }

    cEmpire* empire = StarManager()->GetEmpireByID(planet->GetAvatarHolder()->GetAvatarEmpireID());
    empire->GetStars();

    for (int i = 0; i < numCommodities; ++i) {
        ResourceKey kind = {0, 0, 0};
        intrusive_ptr<PropertyList> props;
        PropertyManager_Get()->GetPropertyList(mCommodities.mpBegin[i].instance, 0x34d97fa, props.AsOutParam());
        GetPropertyAsKey(props.get(), 0x34f1a4f, &kind);
        switch (kind.instance) {
        case 0x4edcc2bf:
        case 0xc045a9a3:
            ConsiderSellingTool(planet, isNew, mCommodities.mpBegin[i]);
            break;
        case 0x82af541:
            FUN_0103d9b0(planet, mCommodities.mpBegin[i]);
            FUN_0103e6e0(planet, mCommodities.mpBegin[i]);
            break;
        case 0x7ecbe6f5:
            CreateCommodityEntry_0103d720(empire, mCommodities.mpBegin[i]);
            break;
        case 0xeb1a8062:
            ConsiderBuyingRareGroup(mCommodities.mpBegin[i]);
            break;
        }
        if (mCommodities.mpBegin[i] == *planet->GetSpiceKey())
            spiceOfPlanet = i;
        else if (mCommodities.mpBegin[i] == *mNPCStore[mLastNPCStoreIndex]->mpSpiceID)
            spiceOfStore = i;
    }

    if (text) {
        intrusive_ptr<PropertyList> props;
        if (gRandom.RandomDoubleUniform() < kHalf) {
            PropertyManager_Get()->GetPropertyList(mCommodities.mpBegin[spiceOfStore].instance, 0x34d97fa, props.AsOutParam());
            GetPropertyAsText(props.get(), 0x36801e9, text);
        } else {
            PropertyManager_Get()->GetPropertyList(mCommodities.mpBegin[spiceOfPlanet].instance, 0x34d97fa, props.AsOutParam());
            GetPropertyAsText(props.get(), 0x36801e8, text);
        }
    }

    SortItems(field_74.mpBegin, field_74.mpEnd, ItemLess);
}
