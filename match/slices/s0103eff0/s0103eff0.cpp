// Slice s0103eff0: SP::cSPSpaceTrading::PerformTrade (retail 0x0103eff0).
// Flags: /O2 /MD /Gy /TP /arch:SSE (cvtsi2ss for int->float, x87 fild/fadd for unsigned->float;
// no /EHsc: the stack message and timer temporaries get no EH frame).
// Retail layout follows ModAPI's Simulator::cSpaceTrading (mNPCStore +0x48, field_74/field_88,
// mLastNPCStoreIndex +0x9c, mRareGroups +0xbc) and cSpaceInventoryItem.
#include "types.h"
#include <intrin.h>

#define VSLOT(n) virtual void _v##n();

inline void* operator new(size_t, void* p) { return p; }

struct ResourceKey {
    uint32_t instance, type, group;
};
inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
    return a.instance == b.instance && a.type == b.type && a.group == b.group;
}

// App::Property: data (or pointer to array) at +0, count at +8, flags at +0x10, type at +0x12.
struct Property {
    void* mpData;
    uint32_t pad4;
    int mnItemCount;
    uint32_t padc;
    uint16_t mnFlags;
    uint16_t mnType;
    int GetItemCount() const { return (mnFlags & 0x30) ? mnItemCount : (mnType != 0); }
    ResourceKey* GetValueKey() { return (mnFlags & 0x30) ? (ResourceKey*)mpData : (mnType ? (ResourceKey*)this : 0); }
    uint32_t* GetValueUInt32() { return (mnFlags & 0x30) ? (uint32_t*)mpData : (uint32_t*)this; }
};
struct PropertyList {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual bool HasProperty(uint32_t id);                                   // +0x1c
    VSLOT(8)
    virtual bool GetProperty(uint32_t id, Property*& out);                   // +0x24
    virtual Property* GetPropertyObject(uint32_t id);                        // +0x28
};
void GetPropertyAsKey(PropertyList* list, uint32_t id, ResourceKey* out);    // 0x006a1250
void GetPropertyAsKeyInstance(PropertyList* list, uint32_t id, uint32_t* out);  // 0x006a12a0

struct cObject {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* Cast(uint32_t typeID);                                     // +0x0c
};
template <class T> inline T* object_cast(cObject* p) { return p ? (T*)p->Cast(T::TYPE) : 0; }

struct cSpaceInventoryItem {
    enum { TYPE = 0x707459dd };
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
    uint32_t pad34[(0x7c - 0x34) / 4];
    int mnToolCount;                                                         // +0x7c (tools only)

    int GetUnitValue_006c0200();
    bool IsStackable_0104cbc0();
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(const intrusive_ptr& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
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
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
typedef intrusive_ptr<cSpaceInventoryItem> cSpaceInventoryItemPtr;

// eastl::vector<T, sp_vector_allocator> (only what PerformTrade uses)
template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    T& back() { return *(mpEnd - 1); }
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
    }
};
template <class T> struct uvector {   // size() as size_type
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
};

struct cSPTimer { void Restart(); };                                         // 0x00bc3130
struct cGonzagoTimer {
    cSPTimer mTimer;
    uint32_t pad[7];
    cGonzagoTimer();                                                         // 0x00b63890
    ~cGonzagoTimer();                                                        // 0x00b638b0
};

struct cNPCStore {
    uint32_t pad00[3];
    uint32_t mPlanetKey;                                                     // +0x0c
    uint32_t pad10[8];
    int mSpiceBought;                                                        // +0x30
    vector<cSpaceInventoryItemPtr> mNPCInventory;                            // +0x34
    uint32_t pad44;
    vector<cGonzagoTimer> mNPCInventoryAges;                                 // +0x48
};

struct cTradeEntryBase { virtual void _e0(); uint32_t pad[2]; };
struct cTradeEntry : cTradeEntryBase, cObject {};                           // cObject at +0x0c

struct cSpaceInventory {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20)
    VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24)
    virtual int IndexOf(uint32_t type, const ResourceKey& id);               // +0x64
    VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30)
    virtual bool TakeItems(int index, cSpaceInventoryItemPtr& dst, int count);  // +0x7c
    virtual void AddItem(cSpaceInventoryItem* item, int a, bool b);          // +0x80
};

struct cPlanetRecord {
    virtual int AddRef();
    virtual int Release();
};
struct cEmpire { uint32_t pad[0x84 / 4]; uint32_t mPoliticalID; void AddTradeValue_00c31a00(int v); };
struct cStarManager {
    cPlanetRecord* GetPlanetRecord_00ba6dc0(uint32_t key);
    cEmpire* GetEmpireByID(uint32_t id);                                     // 0x00ba9370
};
cStarManager* StarManager();                                                 // 0x00b3d2a0

struct cCommRecord { uint32_t GetCommContext(); };                           // 0x00ce6950
cCommRecord* GetActivePlanetRecord();                                        // 0x010212a0
cEmpire* GetPlayerEmpire();                                                  // 0x01021300
struct cAvatarSource { uint32_t GetAvatarEmpireID_00b1fdb0(); };
cAvatarSource* GetAvatarSource_01021240();

struct cToolManager { void CreateToolFromToolID(const ResourceKey& id, cSpaceInventoryItemPtr& dst); };  // 0x0104e340
cToolManager* ToolManager();                                                 // 0x00b3d390

struct cStats { void AddStat_00fe5430(int stat, int value); };
struct cBadgeTarget { uint32_t pad[7]; uint32_t mID; uint32_t mKind; };
struct cBadgeUI { uint32_t pad[3]; cBadgeTarget* mpTarget; void SetMode_007eb820(int mode); };
struct cSpaceGame {
    cSpaceInventory* GetPlayerInventory();                                   // 0x00a1ad60
    cStats* GetPlayerStats();                                                // 0x00bfc5f0
    cBadgeUI* GetUI_01005180(int which);
};
cSpaceGame* SpaceGameGet();                                                  // 0x01002bd0

struct cRelationshipManager { float RecordEvent(uint32_t a, uint32_t b, uint32_t eventID, float scale); };  // 0x00d06240
cRelationshipManager* RelationshipManager();                                 // 0x00b3d2c0
struct cPlayerUFO { void CalcMaxTravelDistance(); };                         // 0x00ffc6d0
cPlayerUFO* GetUFOSimulator();                                               // 0x00ffbe50

void ShowSpiceEvent_00c704a0(cPlanetRecord* planet, ResourceKey id, float amount);
void ShowEventLog_00e39ab0(uint32_t id, cEmpire* empire, ResourceKey* a, ResourceKey* b, uint32_t context,
                           int count, ResourceKey* c, ResourceKey* d);

struct IMessageServer {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4)
    virtual void SendMSG(uint32_t id, void* msg, void* target);              // +0x14
};
IMessageServer* MessageServer();                                             // 0x0067dcc0

// Stack message (vtables UI::BehaviorMessage 0x013eb90c / 0x013eb844): 8-byte slots,
// a refcount mask over the slots, and the message id.
struct IRefSlot { VSLOT(0) virtual int Release(); };
struct MessageBase0 { virtual ~MessageBase0() {} };
struct MessageBase1 : MessageBase0 {
    volatile long mnRefCount;
    MessageBase1() { _InterlockedExchange((long*)&mnRefCount, 0); }
};
struct TradeMessage : MessageBase1 {
    struct Slot { IRefSlot* p; uint32_t pad; } mSlots[5];
    uint32_t mMessageID;                                                     // +0x30
    uint32_t pad34;
    uint32_t mRefMask;                                                       // +0x38
    TradeMessage(uint32_t id) { mMessageID = id; mRefMask = 0; }
    ~TradeMessage()
    {
        for (int i = 0; i < 32; ++i)
            if ((mRefMask & (1 << i)) && mSlots[i].p)
                mSlots[i].p->Release();
    }
    void SetValue(int i, uint32_t v) { *(uint32_t*)&mSlots[i].p = v; }
};

namespace SP {
class cSPSpaceTrading {
public:
    struct RareGroup {
        ResourceKey mGroupKey;
        uint32_t mGroupID;
        uvector<ResourceKey> mRares;                                         // +0x10
        uint32_t pad20;
    };

    uint32_t pad00[0x48 / 4];
    vector<intrusive_ptr<cNPCStore> > mNPCStore;                             // +0x48
    uint32_t pad58[(0x74 - 0x58) / 4];
    vector<cSpaceInventoryItemPtr> field_74;                                 // +0x74
    uint32_t pad84;
    vector<cTradeEntry*> field_88;                                           // +0x88
    uint32_t pad98;
    int mLastNPCStoreIndex;                                                  // +0x9c
    uint32_t padA0[(0xbc - 0xa0) / 4];
    uvector<RareGroup> mRareGroups;                                          // +0xbc

    int GetTradeBalance_01039ca0();
    void MarkRareFound_01039690(ResourceKey* key);
    void CreateCommodityFromID(cSpaceInventoryItemPtr& dst, const ResourceKey& id, int count, float cost);  // 0x0103a480
    cSpaceInventoryItem* FindStoreItem_01039c00(cSpaceInventoryItem* item);
    uint32_t FindRareGroup_0103a760(uint32_t groupID);
    void PerformTrade();
};
}
using SP::cSPSpaceTrading;

template <> struct intrusive_ptr<cNPCStore> {
    cNPCStore* mpObject;
    cNPCStore* operator->() const { return mpObject; }
};

// @ 0x0103eff0
void cSPSpaceTrading::PerformTrade()
{
    cSpaceInventory* inventory = SpaceGameGet()->GetPlayerInventory();
    cSpaceInventoryItemPtr pTool;
    cSpaceInventoryItemPtr pCommodity;
    int balance = GetTradeBalance_01039ca0();

    // Items the player sells.
    int count = field_74.size();
    for (int i = 0; i < count; ++i) {
        cSpaceInventoryItem* pSold = field_74[i].get();
        int& itemCount = pSold->mItemCount;
        if (itemCount == 0)
            continue;
        cSpaceInventoryItem* pItem = pSold;
        ResourceKey tradeType = {0, 0, 0};
        GetPropertyAsKey(pItem->mpPropList, 0x34f1a4f, &tradeType);

        if (tradeType.instance == 0x82af541) {
            intrusive_ptr<cPlanetRecord> planet;
            cPlanetRecord* p = StarManager()->GetPlanetRecord_00ba6dc0(mNPCStore[mLastNPCStoreIndex]->mPlanetKey);
            if (p) {
                p->AddRef();
                planet.mpObject = p;
            }
            mNPCStore[mLastNPCStoreIndex]->mSpiceBought += itemCount;
            ShowSpiceEvent_00c704a0(planet.get(), pItem->GetItemID(), (float)itemCount);
            ResourceKey a = {0, 0, 0};
            ResourceKey b = {0, 0, 0};
            ResourceKey c = {0, 0, 0};
            ResourceKey d = {0, 0, 0};
            ShowEventLog_00e39ab0(0xd12f991e, GetPlayerEmpire(), &a, &b,
                                  GetActivePlanetRecord()->GetCommContext(), itemCount, &c, &d);
        }
        if (tradeType.instance == 0xb978c47a) {
            ResourceKey id = pItem->GetItemID();
            MarkRareFound_01039690(&id);
            pCommodity = 0;
            CreateCommodityFromID(pCommodity, id, itemCount, (float)pItem->mItemCost);
            pItem = pCommodity.get();
        }
        uint32_t toolID = 0;
        GetPropertyAsKeyInstance(pItem->mpPropList, 0x35d5cb4, &toolID);
        if (toolID) {
            pTool = 0;
            ResourceKey toolKey = {toolID, 0, 0};
            ToolManager()->CreateToolFromToolID(toolKey, pTool);
            if (pTool->IsStackable_0104cbc0()) {
                pTool->mnToolCount = pItem->mItemCount;
                pTool->mItemCount = 1;
            }
            if (pItem->mpPropList->HasProperty(0x58cd55b)) {
                Property* prop = pItem->mpPropList->GetPropertyObject(0x58cd55b);
                int n = prop->GetItemCount();
                ResourceKey* keys = prop->GetValueKey();
                for (int j = 0; j < n; ++j) {
                    cSpaceInventoryItemPtr pExtra;
                    ResourceKey extraKey = {keys[j].instance, 0, 0};
                    ToolManager()->CreateToolFromToolID(extraKey, pExtra);
                    if (pExtra->IsStackable_0104cbc0()) {
                        pExtra->mnToolCount = pItem->mItemCount;
                        pExtra->mItemCount = 1;
                    }
                    inventory->AddItem(pExtra.get(), 0, true);
                }
            }
            pItem = pTool.get();
            cBadgeUI* ui = SpaceGameGet()->GetUI_01005180(0xf);
            ui->SetMode_007eb820(9);
            ui->mpTarget->mID = pItem->GetItemID().instance;
            ui->mpTarget->mKind = 4;
            SpaceGameGet()->GetPlayerStats()->AddStat_00fe5430(0x1c, 1);
        }
        inventory->AddItem(pItem, 0, true);

        {
            TradeMessage msg(0xf46092c1);
            msg.SetValue(1, tradeType.instance);
            msg.SetValue(0, 1);
            msg.SetValue(2, pItem->GetItemID().instance);
            msg.SetValue(3, pItem->mItemCount);
            msg.SetValue(4, GetActivePlanetRecord()->GetCommContext());
            MessageServer()->SendMSG(msg.mMessageID, &msg, 0);
            int value = pItem->GetUnitValue_006c0200() * pItem->mItemCount;
            if (tradeType.instance == 0xb978c47a || tradeType.instance == 0x7ecbe6f5)
                value = -value;
            SpaceGameGet()->GetPlayerStats()->AddStat_00fe5430(0xd, value);
        }

        // Take the sold amount out of the NPC store's own stock of the same item.
        vector<cSpaceInventoryItemPtr>& stock = mNPCStore[mLastNPCStoreIndex]->mNPCInventory;
        int stockCount = stock.size();
        for (int j = 0; j < stockCount; ++j) {
            cSpaceInventoryItem* pStock = stock[j].get();
            if (pStock->GetItemID() == pSold->GetItemID()) {
                if (pSold->mItemCount < pStock->mItemCount)
                    pStock->mItemCount -= pSold->mItemCount;
                else
                    pStock->mItemCount = 0;
            }
        }
    }

    // Items the player buys.
    for (cTradeEntry** it = field_88.mpBegin, **itEnd = field_88.mpEnd; it != itEnd; ++it) {
        cSpaceInventoryItem* pItem = object_cast<cSpaceInventoryItem>(*it);
        cSpaceInventoryItemPtr pTaken;
        uint32_t tradeType = 0;
        GetPropertyAsKeyInstance(pItem->mpPropList, 0x34f1a4f, &tradeType);
        if (pItem->mItemCount == 0)
            continue;

        if (tradeType == 0xeb1a8062) {
            uint32_t groupID;
            if (PropertyList* list = pItem->mpPropList) {
                Property* prop;
                if (list->GetProperty(0x3c72dc6, prop) && prop->mnType == 9)
                    groupID = *prop->GetValueUInt32();
            }
            uint32_t groupIndex = FindRareGroup_0103a760(groupID);
            if (groupIndex < mRareGroups.size()) {
                for (uint32_t k = 0; k < mRareGroups[groupIndex].mRares.size(); ++k) {
                    cSpaceInventory* playerInventory = SpaceGameGet()->GetPlayerInventory();
                    ResourceKey rareKey = mRareGroups[groupIndex].mRares[k];
                    int index = playerInventory->IndexOf(4, rareKey);
                    inventory->TakeItems(index, pTaken, 1);
                }
            }
        } else {
            cSpaceInventory* playerInventory = SpaceGameGet()->GetPlayerInventory();
            int index = playerInventory->IndexOf(pItem->mItemType, pItem->GetItemID());
            inventory->TakeItems(index, pTaken, pItem->mItemCount);
            if (tradeType == 0x7ecbe6f5 || tradeType == 0x82af541) {
                ResourceKey id = pItem->GetItemID();
                if (tradeType == 0x82af541) {
                    switch (id.instance) {
                    case 0x1ca01562: id.instance = 0x671e8057; break;
                    case 0x1ca01561: id.instance = 0x6872fd1a; break;
                    case 0x1ca01560: id.instance = 0x8fe43469; break;
                    case 0x1ca01567: id.instance = 0xd634626c; break;
                    case 0x1ca01566: id.instance = 0x874eba8b; break;
                    case 0x1ca01565: id.instance = 0x34502c4e; break;
                    }
                    pItem->SetItemID(id);
                }
                cSpaceInventoryItemPtr pStockItem;
                CreateCommodityFromID(pStockItem, pItem->GetItemID(), pItem->mItemCount, (float)pItem->mItemCost);
                if (cSpaceInventoryItem* pExisting = FindStoreItem_01039c00(pStockItem.get())) {
                    pExisting->mItemCount += pStockItem->mItemCount;
                } else {
                    mNPCStore[mLastNPCStoreIndex]->mNPCInventory.push_back(pStockItem);
                    mNPCStore[mLastNPCStoreIndex]->mNPCInventoryAges.push_back();
                    mNPCStore[mLastNPCStoreIndex]->mNPCInventoryAges.back().mTimer.Restart();
                    cSpaceInventoryItemPtr pPlaceholder;
                    CreateCommodityFromID(pPlaceholder, pItem->GetItemID(), 0, (float)pItem->mItemCost);
                    field_74.push_back(pPlaceholder);
                }
            }
        }

        TradeMessage msg(0xf46092c1);
        msg.SetValue(1, tradeType);
        msg.SetValue(0, 0);
        msg.SetValue(2, pItem->GetItemID().instance);
        msg.SetValue(3, pItem->mItemCount);
        msg.SetValue(4, GetActivePlanetRecord()->GetCommContext());
        MessageServer()->SendMSG(msg.mMessageID, &msg, 0);
        if (tradeType == 0x82af541) {
            ResourceKey a = {0, 0, 0};
            ResourceKey b = {0, 0, 0};
            ResourceKey c = {0, 0, 0};
            ResourceKey d = {0, 0, 0};
            ShowEventLog_00e39ab0(0xd12f991e, GetPlayerEmpire(), &a, &b,
                                  GetActivePlanetRecord()->GetCommContext(), pItem->mItemCount, &c, &d);
        }
        SpaceGameGet()->GetPlayerStats()->AddStat_00fe5430(0xd, pItem->GetUnitValue_006c0200() * pItem->mItemCount);
    }

    cEmpire* empire = GetPlayerEmpire();
    empire->AddTradeValue_00c31a00(balance);
    cEmpire* avatarEmpire = StarManager()->GetEmpireByID(GetAvatarSource_01021240()->GetAvatarEmpireID_00b1fdb0());
    if (avatarEmpire != empire && (balance > 1000 || balance < -1000))
        RelationshipManager()->RecordEvent(avatarEmpire->mPoliticalID, empire->mPoliticalID, 0x526e527, 1.0f);
    GetUFOSimulator()->CalcMaxTravelDistance();
}
