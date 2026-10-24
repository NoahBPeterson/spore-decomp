// Slice s010393a0: space-stage trading (SP::cSPSpaceTrading helpers, trade-route insertion,
// rare/spice key remapping and the EASTL intrusive-pointer sort/heap helpers).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Layouts follow the retail ModAPI cSpaceTrading layout (mNPCStore +0x48, field_74 +0x74,
// field_88 +0x88, mLastNPCStoreIndex +0x9c, mRareGroups +0xbc), the PDB cTradeRouteData and
// the AutoRefCount intrusive list algorithms used by cSpaceInventory.
#include "types.h"
#include <math.h>
#include <intrin.h>

#define VSLOT(n) virtual void _v##n();

inline void* operator new(size_t, void* p) { return p; }

// ---------------------------------------------------------------------------
// shared value types
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
};

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
};

struct IRefCounted {
    VSLOT(0)
    virtual int Release();                                                   // +0x04
    virtual int AddRef();                                                    // +0x08
};

struct PropertyList : IRefCounted {
    VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual bool HasProperty(uint32_t id);                                   // +0x1c
    VSLOT(8)
    virtual bool GetProperty(uint32_t id, Property*& pOut);                  // +0x24
    virtual Property* GetPropertyObject(uint32_t id);                        // +0x28
};

void GetPropertyAsKey(PropertyList* pList, uint32_t id, ResourceKey* pOut);      // 0x006a1250
bool GetPropertyAsKeyInstance(PropertyList* pList, uint32_t id, uint32_t* pOut);  // 0x006a12a0

// AutoRefCount pointer used for property lists: a null assignment still runs the release test.
struct cPropertyListPtr {
    PropertyList* mpObject;
    cPropertyListPtr() : mpObject((PropertyList*)0) {}
    cPropertyListPtr& operator=(PropertyList* p)
    {
        PropertyList* const pTemp = mpObject;
        if (p != pTemp) {
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    ~cPropertyListPtr()
    {
        PropertyList* p = mpObject;
        if (p)
            p->Release();
    }
    PropertyList* get() const { return mpObject; }
    PropertyList* operator->() const { return mpObject; }
};

struct cPropertyManager {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual void GetProperty(uint32_t key, uint32_t id, void** pOut);        // +0x2c
};
cPropertyManager* PropertyManager();                                         // 0x0067de30

// ---------------------------------------------------------------------------
// message dispatch
// ---------------------------------------------------------------------------
struct IMessageServer {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4)
    virtual void SendMSG(uint32_t id, void* msg, void* target);              // +0x14
    VSLOT(6) VSLOT(7) VSLOT(8)
    virtual void AddHandler(void* pHandler, uint32_t msgID);                 // +0x24
};
IMessageServer* MessageServer();                                             // 0x0067dcc0

// Stack message (vtables UI::BehaviorMessage 0x013eb90c / 0x013eb844): 8-byte slots, a refcount
// mask over the slots and the message id.
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
            if ((mRefMask & (1u << i)) && mSlots[i].p)
                mSlots[i].p->Release();
    }
    void SetValue(int i, uint32_t v) { *(uint32_t*)&mSlots[i].p = v; }
};

// ---------------------------------------------------------------------------
// simulator objects
// ---------------------------------------------------------------------------
struct cObject {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* Cast(uint32_t typeID);                                     // +0x0c
};

struct cSpatialEntity {
    const Vector3& GetPosition();                                            // 0x005c65e0
};

struct cEmpire {
    uint32_t pad00[0x84 / 4];
    uint32_t mPoliticalID;                                                   // +0x84
    uint32_t GetPoliticalID();                                               // 0x00b1fdb0
};

struct cPlanetRecord {
    virtual void v00();
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
    cEmpire* GetOwnerEmpire();                                               // 0x00b8de30
};

struct cStarRecord : cSpatialEntity {
    uint32_t pad00[0x70 / 4];
    uint32_t mKey;                                                           // +0x70
};

struct cStarManager {
    cPlanetRecord* GetPlanetRecord(uint32_t planetKey);                      // 0x00ba6dc0
};
cStarManager* StarManager();                                                 // 0x00b3d2a0

struct cSpaceInventoryItem;

namespace SP {
uint32_t GetPlayerEmpireID();                                                // 0x01021090
cSpatialEntity* GetActivePlanet();                                           // 0x01021230
int __stdcall AddTradingItems(PropertyList* pList, bool bAddMissing);          // 0x01039520
void __stdcall MapRareToSpiceKey(ResourceKey* pKey);                           // 0x01039690
int __stdcall HasTradingItems(PropertyList* pList);                            // 0x01039990
bool IsItemARare(uint32_t* pItemID);                                           // 0x0103a3c0
}

struct cMissionManager { bool IsRunning(); };                                // 0x00feba90
cMissionManager* GetMissionManager();                                        // 0x00feb9f0

// ---------------------------------------------------------------------------
// inventory items
// ---------------------------------------------------------------------------
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
    bool mTradeState;                                                        // +0x1c
    uint8_t pad1d[3];
    uint32_t pad20[4];
    PropertyList* mpPropList;                                                // +0x30
    uint32_t pad34[(0x7c - 0x34) / 4];
    int mnToolCount;                                                         // +0x7c (tools only)

    int GetUnitValue_006c0200();                                             // 0x006c0200
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(const intrusive_ptr& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    intrusive_ptr& operator=(const intrusive_ptr& o) { return operator=(o.mpObject); }
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

// eastl::vector<T, sp_vector_allocator> (only what this slice uses)
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
template <class T> struct uvector {   // size() as size_type
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};

// eastl::vector<ResourceKey>: 12-byte entries, only begin/end observed in this code.
struct cTradeKeyList {
    ResourceKey* mpBegin;                                                    // +0x00
    ResourceKey* mpEnd;                                                      // +0x04
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cSpaceInventory {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    virtual cSpaceInventoryItem* GetItemEntry(int index);                    // +0x60
    virtual int IndexOf(uint32_t type, const ResourceKey& id);               // +0x64
    VSLOT(26) VSLOT(27) VSLOT(28)
    virtual bool HasItem(const ResourceKey& id);                             // +0x74
    VSLOT(30)
    virtual bool TakeItems(int index, cSpaceInventoryItemPtr& dst, int count);  // +0x7c
    virtual void AddItem(cSpaceInventoryItem* item, int a, bool b);          // +0x80
};

// Object returned by 0x00bfc5f0: owns the AutoRefCount item vector.
struct cPlayerItemStore {
    bool DoInsertValue(cSpaceInventoryItem* pItem);                          // 0x00fe4180
    cSpaceInventoryItem* GetReplacement(cSpaceInventoryItem* pItem);         // 0x00fe41c0
};

struct cSpaceGame {
    cSpaceInventory* GetPlayerInventory();                                   // 0x00a1ad60
    cPlayerItemStore* GetItemStore();                                        // 0x00bfc5f0
};
cSpaceGame* SpaceGameGet();                                                  // 0x01002bd0

struct cSpaceEconomyTuning {
    int GetMaxCargo();                                                       // 0x0102ff00
};
cSpaceEconomyTuning* SpaceEconomyTuning();                                   // 0x0102f810

struct cGameNounManager {
    cObject* CreateNoun(uint32_t nounID);                                    // 0x00b20c60
    void* CreatePlanetaryArtifact();
};

// ---------------------------------------------------------------------------
// NPC store (SP::cSPSpaceTrading::mNPCStore elements)
// ---------------------------------------------------------------------------
struct cGonzagoTimer { uint32_t pad00[8]; };

struct cNPCStore {
    uint32_t pad00[3];
    uint32_t mPlanetKey;                                                     // +0x0c
    uint32_t pad10[8];
    int mSpiceBought;                                                        // +0x30
    vector<cSpaceInventoryItemPtr> mNPCInventory;                            // +0x34
    uint32_t pad44;
    vector<cGonzagoTimer> mNPCInventoryAges;                                 // +0x48
    uint32_t pad58;
    bool mMarked;                                                            // +0x5c
};

// ---------------------------------------------------------------------------
// trade routes (PDB SP::cTradeRouteData / cSpaceTradeRouteManager)
// ---------------------------------------------------------------------------
struct cTradeRouteData {
    virtual ~cTradeRouteData() {}
    virtual bool Write(void* stream);
    virtual bool Read(void* stream);

    uint32_t mPoliticalID1;                                                  // +0x04
    uint32_t mPoliticalID2;                                                  // +0x08
    uint32_t mStarID1;                                                       // +0x0c
    uint32_t mStarID2;                                                       // +0x10
    float mTradeRouteProgress;                                               // +0x14
    bool mInDetectableRange;                                                 // +0x18
    uint32_t mTimeSinceLastUFOMS;                                            // +0x1c
    uint32_t mTimeSinceLastSimMS;                                            // +0x20
    float mRouteLength;                                                      // +0x24
    int mLastMerchantVoyage;                                                 // +0x28
};

struct TradeKey { uint32_t first, second; };

namespace eastl {
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
}

struct TradeRouteNode : eastl::rbtree_node_base {
    TradeKey mKey;                                                           // +0x10
    cTradeRouteData mValue;                                                  // +0x18
};

struct TradeRouteMap {
    uint32_t mCompare;                                                       // +0x04
    eastl::rbtree_node_base mAnchor;                                         // +0x08
    uint32_t mnSize;                                                         // +0x18
    uint32_t mAllocator;                                                     // +0x1c

    TradeRouteNode* end() { return (TradeRouteNode*)&mAnchor; }
    void Find(TradeRouteNode** pOut, const TradeKey& key);                   // 0x00d00f80
    TradeRouteNode* Insert(const TradeKey& key);                             // 0x010392f0
};

struct cSpaceTradeRouteManager {
    virtual ~cSpaceTradeRouteManager();
    TradeRouteMap mTradeRoutes;                                              // +0x04
    uint32_t mLastStarID;                                                    // +0x20

    void UpdateRouteLength(cTradeRouteData* route, Vector3 pos);             // 0x01037c30
    void AddTradeRoute(cStarRecord* pStar1, uint32_t politicalID1,
                       cStarRecord* pStar2, uint32_t politicalID2);
};

// ---------------------------------------------------------------------------
// SP::cSPSpaceTrading
// ---------------------------------------------------------------------------
namespace SP {
// Message target registered at +0x1c; Cast finds the owning handler 8 bytes back.
struct cHandlerIface {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* Cast(uint32_t typeID);                                     // +0x0c
};
struct cTradingHandler {
    uint32_t pad00[2];                                                       // +0x14
    cHandlerIface mIface;                                                    // +0x1c
};

struct cAutoMessageHandler {
    IMessageServer* mpServer;                                                // +0x00
    void* mpHandler;                                                         // +0x04
    const uint32_t* mpIDs;                                                   // +0x08
    uint32_t mnCount;                                                        // +0x0c
    uint32_t mnIndex;                                                        // +0x10
};

class cSPSpaceTrading {
public:
    struct RareGroup {
        ResourceKey mGroupKey;                                               // +0x00
        uint32_t mGroupID;                                                   // +0x0c
        uvector<ResourceKey> mRares;                                         // +0x10
        uint32_t pad20;                                                      // +0x20
    };

    uint32_t pad00[5];                                                       // +0x00
    cTradingHandler mHandler;                                                // +0x14
    uint32_t pad20[3];                                                       // +0x20
    cTradeKeyList mPlanetKeys;                                               // +0x2c
    cTradeKeyList mToolKeys;                                                 // +0x34
    uint32_t pad3c[3];                                                       // +0x3c
    vector<intrusive_ptr<cNPCStore> > mNPCStore;                             // +0x48
    uint32_t pad58[7];                                                       // +0x58
    vector<cSpaceInventoryItemPtr> mUserItems;                               // +0x74  (field_74)
    uint32_t pad84;
    vector<cSpaceInventoryItemPtr> mNPCItems;                                // +0x88  (field_88)
    uint32_t pad98;
    int mLastNPCStoreIndex;                                                  // +0x9c
    uint32_t padA0[7];                                                       // +0xa0
    uvector<RareGroup> mRareGroups;                                          // +0xbc
    uint32_t padCC;
    cAutoMessageHandler mAutoHandler;                                        // +0xd0
    uint32_t padE4;
    void** mpStackTop;                                                       // +0xe8

    void RegisterMessages();
    bool IsToolAvailableForTrading(uint32_t toolKey, uint32_t unused2, uint32_t unused3,
                                   PropertyList** ppProperty);
    void MarkNPCStores(bool bAll);
    int GetItemValue(cSpaceInventoryItem* pItem);
    cSpaceInventoryItem* FindStoreItem(cSpaceInventoryItem* pItem);
    int GetTradeBalance();
    int AdjustTradeValue(bool bSetCountToOne, cSpaceInventoryItem* pItem);
    void GetRareKey(ResourceKey* pOut, uint32_t groupIndex, uint32_t rareIndex);
    int GetRareKeyCount(uint32_t groupIndex);
    void* PopValue();
    cSpaceInventoryItem* GetUserItem(uint32_t index);
    cSpaceInventoryItem* GetNPCItem(uint32_t index);
};

}  // namespace SP

using SP::cSPSpaceTrading;

// @ 0x010393a0  SP::cSpaceTradeRouteManager::AddTradeRoute
void cSpaceTradeRouteManager::AddTradeRoute(cStarRecord* pStar1, uint32_t politicalID1,
                                            cStarRecord* pStar2, uint32_t politicalID2)
{
    uint32_t star1 = pStar1->mKey;
    uint32_t star2 = pStar2->mKey;
    uint32_t keyStar1 = star1;
    uint32_t keyStar2 = star2;
    if (keyStar1 > keyStar2) {
        uint32_t swap = keyStar1;
        keyStar1 = keyStar2;
        keyStar2 = swap;
    }
    TradeKey key;
    key.first = keyStar1;
    key.second = keyStar2;
    TradeRouteNode* pFound;
    mTradeRoutes.Find(&pFound, key);
    if (pFound != mTradeRoutes.end())
        return;
    if (star1 > star2) {
        uint32_t swap = star1;
        star1 = star2;
        star2 = swap;
        swap = politicalID1;
        politicalID1 = politicalID2;
        politicalID2 = swap;
    }
    TradeRouteNode* pNode = mTradeRoutes.Insert(key);
    cTradeRouteData* pRoute = &pNode->mValue;
    pRoute->mPoliticalID1 = politicalID1;
    pRoute->mStarID1 = star1;
    pRoute->mStarID2 = star2;
    pRoute->mPoliticalID2 = politicalID2;
    pRoute->mTradeRouteProgress = 0.0f;
    pRoute->mTimeSinceLastUFOMS = 0;
    pRoute->mTimeSinceLastSimMS = 0;

    const Vector3& pos2 = pStar2->GetPosition();
    const Vector3& pos1 = pStar1->GetPosition();
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    float dz = pos1.z - pos2.z;
    pRoute->mRouteLength = sqrtf(dx * dx + (dy * dy + dz * dz));

    Vector3 activePos = SP::GetActivePlanet()->GetPosition();
    UpdateRouteLength(pRoute, activePos);

    TradeMessage msg(0xf46092d1);
    msg.SetValue(0, star1);
    msg.SetValue(1, star2);
    msg.SetValue(2, politicalID1);
    msg.SetValue(3, politicalID2);
    MessageServer()->SendMSG(msg.mMessageID, &msg, 0);
}

// @ 0x01039520  SP::AddTradingItems
// Reads the three traded-item properties (0x5107709/a/b) and pushes each item into the player's
// AutoRefCount vector; when bAddMissing is set, failed items are retried through GetReplacement.
int __stdcall SP::AddTradingItems(PropertyList* pList, bool bAddMissing)
{
    cPlayerItemStore* pStore = SpaceGameGet()->GetItemStore();
    uint32_t item0;
    uint32_t item1;
    uint32_t item2;
    bool b3 = !GetPropertyAsKeyInstance(pList, 0x5107709, &item0) ||
              pStore->DoInsertValue((cSpaceInventoryItem*)item0);
    bool b2 = !GetPropertyAsKeyInstance(pList, 0x510770a, &item1) ||
              pStore->DoInsertValue((cSpaceInventoryItem*)item1);
    bool b1 = GetPropertyAsKeyInstance(pList, 0x510770b, &item2) &&
              pStore->DoInsertValue((cSpaceInventoryItem*)item2);
    if (bAddMissing && GetMissionManager()->IsRunning()) {
        if (!b3) {
            cSpaceInventoryItem* pReplacement = pStore->GetReplacement((cSpaceInventoryItem*)item0);
            b3 = pReplacement == 0 || pStore->DoInsertValue(pReplacement);
        }
        if (!b2) {
            cSpaceInventoryItem* pReplacement = pStore->GetReplacement((cSpaceInventoryItem*)item1);
            b2 = pReplacement == 0 || pStore->DoInsertValue(pReplacement);
        }
        if (!b1) {
            cSpaceInventoryItem* pReplacement = pStore->GetReplacement((cSpaceInventoryItem*)item2);
            b1 = pReplacement == 0 || pStore->DoInsertValue(pReplacement);
        }
    }
    if (!((b3 && b2) || b1))
        return 0;
    return 1;
}

// @ 0x01039690  SP::MapRareToSpiceKey
// Maps a rare resource id to the spice resource id that stands in for it in trades.
void __stdcall SP::MapRareToSpiceKey(ResourceKey* pKey)
{
    switch (pKey->instance) {
    case 0x874eba8b:
        pKey->instance = 0x1ca01566;
        return;
    case 0x34502c4e:
        pKey->instance = 0x1ca01565;
        return;
    case 0x671e8057:
        pKey->instance = 0x1ca01562;
        return;
    case 0x6872fd1a:
        pKey->instance = 0x1ca01561;
        return;
    case 0x8fe43469:
        pKey->instance = 0x1ca01560;
        return;
    case 0xd634626c:
        pKey->instance = 0x1ca01567;
        return;
    }
}

// @ 0x01039730  SP::cSPSpaceTrading::RegisterMessages
void cSPSpaceTrading::RegisterMessages()
{
    static const uint32_t sMessageIDs[2] = {0x1499b04, 0x1499b05};
    if (MessageServer() == 0)
        return;
    void* pHandler = this ? (void*)&mHandler.mIface : 0;
    IMessageServer* pServer = MessageServer();
    mAutoHandler.mpServer = pServer;
    mAutoHandler.mpHandler = pHandler;
    mAutoHandler.mpIDs = sMessageIDs;
    mAutoHandler.mnCount = 2;
    mAutoHandler.mnIndex = 0;
    if (pServer != 0 && pHandler != 0) {
        for (const uint32_t* pID = sMessageIDs; pID != sMessageIDs + 2; ++pID)
            pServer->AddHandler(pHandler, *pID);
    }
}

// @ 0x010397b0  SP::cHandlerIface::Cast
void* SP::cHandlerIface::Cast(uint32_t typeID)
{
    if (typeID == 0x5b82ef9)
        return (char*)this - 8;
    if (typeID == 0x179c807) {
        cHandlerIface* pSelf = (cHandlerIface*)((char*)this - 8);
        return pSelf != 0 ? this : 0;
    }
    return 0;
}

// @ 0x010398e0  SP::cSPSpaceTrading::IsToolAvailableForTrading
// Looks up each tradeable tool key in the property manager and compares the tool id stored on it.
bool cSPSpaceTrading::IsToolAvailableForTrading(uint32_t toolKey, uint32_t, uint32_t,
                                                PropertyList** ppProperty)
{
    int count = mToolKeys.size();
    for (int i = 0; i < count; ++i) {
        cPropertyManager* pManager = PropertyManager();
        pManager->GetProperty(mToolKeys.mpBegin[i].instance, 0x34d97fa, (void**)ppProperty);
        uint32_t itemToolKey = 0;
        if (GetPropertyAsKeyInstance(*ppProperty, 0x35d5cb4, &itemToolKey) && toolKey == itemToolKey)
            return true;
    }
    *ppProperty = 0;
    return false;
}

// Reads the two traded-item properties (0x5107706/07) and checks the player inventory.
static __forceinline bool PlayerHasItem(uint32_t item)
{
    ResourceKey id = {item, 0, 0};
    return SpaceGameGet()->GetPlayerInventory()->HasItem(id);
}

// @ 0x01039990  SP::HasTradingItems
int __stdcall SP::HasTradingItems(PropertyList* pList)
{
    uint32_t item = 0;
    bool b3 = !GetPropertyAsKeyInstance(pList, 0x5107706, &item) || PlayerHasItem(item);
    bool b2 = !GetPropertyAsKeyInstance(pList, 0x5107707, &item) || PlayerHasItem(item);
    bool b1 = GetPropertyAsKeyInstance(pList, 0x5107707, &item) && PlayerHasItem(item);
    if (!((b3 && b2) || b1))
        return 0;
    return 1;
}

// @ 0x01039ab0  SP::cSPSpaceTrading::GetUserItem
cSpaceInventoryItem* cSPSpaceTrading::GetUserItem(uint32_t index)
{
    if (index >= (uint32_t)mUserItems.size())
        return 0;
    return mUserItems.mpBegin[index].get();
}

// @ 0x01039ad0  SP::cSPSpaceTrading::GetNPCItem
cSpaceInventoryItem* cSPSpaceTrading::GetNPCItem(uint32_t index)
{
    if (index >= (uint32_t)mNPCItems.size())
        return 0;
    return mNPCItems.mpBegin[index].get();
}

// @ 0x01039b00  SP::cSPSpaceTrading::MarkNPCStores
// Marks the NPC stores that belong to another empire (or all of them when bAll is set).
void cSPSpaceTrading::MarkNPCStores(bool bAll)
{
    int count = mNPCStore.size();
    for (int i = 0; i < count; ++i) {
        cPlanetRecord* pPlanet = StarManager()->GetPlanetRecord(mNPCStore.mpBegin[i]->mPlanetKey);
        if (bAll || (pPlanet != 0 &&
                     pPlanet->GetOwnerEmpire()->GetPoliticalID() != SP::GetPlayerEmpireID()))
            mNPCStore.mpBegin[i]->mMarked = true;
    }
}

// @ 0x01039b70  SP::cSPSpaceTrading::GetItemValue
int cSPSpaceTrading::GetItemValue(cSpaceInventoryItem* pItem)
{
    ResourceKey tradeType = {0, 0, 0};
    GetPropertyAsKey(pItem->mpPropList, 0x34f1a4f, &tradeType);
    if (tradeType.instance != 0xeb1a8062) {
        cSpaceInventory* pInventory = SpaceGameGet()->GetPlayerInventory();
        int index = pInventory->IndexOf(pItem->mItemType, pItem->GetItemID());
        if (index == -1)
            return 0;
        return pInventory->GetItemEntry(index)->mItemCount;
    }
    return 1;
}

// @ 0x01039c00  SP::cSPSpaceTrading::FindStoreItem
// Finds the largest stack of the same item in the current NPC store.
cSpaceInventoryItem* cSPSpaceTrading::FindStoreItem(cSpaceInventoryItem* pItem)
{
    cSpaceInventoryItem* pBest = 0;
    int bestCount = -1;
    vector<cSpaceInventoryItemPtr>& inventory = mNPCStore.mpBegin[mLastNPCStoreIndex]->mNPCInventory;
    int count = inventory.size();
    for (int index = 0; index < count; ++index) {
        cSpaceInventoryItem* pStock = inventory.mpBegin[index].get();
        if (pStock->GetItemID() == pItem->GetItemID() && pStock->mItemCount > bestCount) {
            bestCount = pStock->mItemCount;
            pBest = pStock;
        }
    }
    return pBest;
}

// @ 0x01039ca0  SP::cSPSpaceTrading::GetTradeBalance
int cSPSpaceTrading::GetTradeBalance()
{
    SpaceGameGet()->GetPlayerInventory();
    int balance = 0;
    int count = mUserItems.size();
    for (int i = 0; i < count; ++i) {
        cSpaceInventoryItem* pItem = mUserItems.mpBegin[i].get();
        balance -= pItem->GetUnitValue_006c0200() * pItem->mItemCount;
    }
    count = mNPCItems.size();
    for (int i = 0; i < count; ++i) {
        cSpaceInventoryItem* pItem = mNPCItems.mpBegin[i].get();
        balance += pItem->GetUnitValue_006c0200() * pItem->mItemCount;
    }
    return balance;
}

// @ 0x01039d20  SP::cSPSpaceTrading::AdjustTradeValue
// Counts how many carried items the player cannot offer (and how many wanted items are already
// covered), then deducts the wanted item from the carried list when the trade goes through.
int cSPSpaceTrading::AdjustTradeValue(bool bSetCountToOne, cSpaceInventoryItem* pItem)
{
    int itemCount = pItem->mItemCount;
    if (bSetCountToOne)
        pItem->mItemCount = 1;
    int value = 0;
    cSpaceInventory* pInventory = SpaceGameGet()->GetPlayerInventory();
    int maxCargo = SpaceEconomyTuning()->GetMaxCargo();
    int count = mUserItems.size();
    for (int i = 0; i < count; ++i) {
        cSpaceInventoryItem* pUser = mUserItems.mpBegin[i].get();
        ResourceKey id = pUser->GetItemID();
        SP::MapRareToSpiceKey(&id);
        if (pInventory->IndexOf(pUser->mItemType, id) == -1 && pUser->mItemCount != 0)
            ++value;
    }
    count = mNPCItems.size();
    for (int i = 0; i < count; ++i) {
        cSpaceInventoryItem* pNPC = mNPCItems.mpBegin[i].get();
        int index = pInventory->IndexOf(pNPC->mItemType, pNPC->GetItemID());
        if (index != -1 && pNPC->mItemCount >= pInventory->GetItemEntry(index)->mItemCount)
            --value;
    }
    int index = pInventory->IndexOf(pItem->mItemType, pItem->GetItemID());
    if (index == -1) {
        if (!bSetCountToOne) {
            pItem->mItemCount = itemCount;
            return value;
        }
        bool bFound = false;
        if (!pItem->mTradeState) {
            int userCount = mUserItems.size();
            for (int i = 0; i < userCount; ++i) {
                cSpaceInventoryItem* pUser = mUserItems.mpBegin[i].get();
                if (pUser->GetItemID() == pItem->GetItemID() &&
                    pUser->mItemType == pItem->mItemType && pUser->mItemCount < maxCargo) {
                    bFound = true;
                    break;
                }
            }
        }
        if (!bFound)
            ++value;
    } else if (!bSetCountToOne && pItem->mItemCount >= pInventory->GetItemEntry(index)->mItemCount) {
        --value;
        pItem->mItemCount = itemCount;
        return value;
    }
    pItem->mItemCount = itemCount;
    return value;
}

// @ 0x01039fb0  SP::cSPSpaceTrading::GetRareKey
void cSPSpaceTrading::GetRareKey(ResourceKey* pOut, uint32_t groupIndex, uint32_t rareIndex)
{
    const uint32_t* pSrc = (const uint32_t*)&mRareGroups.mpBegin[groupIndex].mRares.mpBegin[rareIndex];
    uint32_t* pDst = (uint32_t*)pOut;
    pDst[0] = pSrc[0];
    pDst[1] = pSrc[1];
    pDst[2] = pSrc[2];
}

// @ 0x01039ff0  SP::cSPSpaceTrading::GetRareKeyCount
int cSPSpaceTrading::GetRareKeyCount(uint32_t groupIndex)
{
    uvector<ResourceKey>* pRares = &mRareGroups.mpBegin[groupIndex].mRares;
    return (int)(pRares->mpEnd - pRares->mpBegin);
}

// @ 0x0103a060  SP::cSPSpaceTrading::PopValue
void* cSPSpaceTrading::PopValue()
{
    --mpStackTop;
    return *mpStackTop;
}

// @ 0x0103a080  SP::cGameNounManager::CreatePlanetaryArtifact
void* cGameNounManager::CreatePlanetaryArtifact()
{
    cObject* pNoun = CreateNoun(0x2dd8c42);
    if (pNoun != 0)
        return pNoun->Cast(0x2dd8c33);
    return 0;
}

// ---------------------------------------------------------------------------
// EASTL algorithms over EA::AutoRefCount (4-byte intrusive pointers)
// ---------------------------------------------------------------------------
typedef int (*ItemPtrCompare)(cSpaceInventoryItem*, cSpaceInventoryItem*);

// @ 0x0103a0e0
void eastl_insertion_sort(cSpaceInventoryItemPtr* pBegin, cSpaceInventoryItemPtr* pEnd,
                          ItemPtrCompare pCompare)
{
    if (pBegin == pEnd)
        return;
    for (cSpaceInventoryItemPtr* i = pBegin + 1; i != pEnd; ++i) {
        cSpaceInventoryItemPtr value = *i;
        cSpaceInventoryItemPtr* j = i;
        while (j != pBegin && pCompare(value.get(), (*(j - 1)).get())) {
            *j = *(j - 1);
            --j;
        }
        *j = value;
    }
}

// @ 0x0103a1b0
void eastl_unguarded_insertion_sort(cSpaceInventoryItemPtr* pBegin, cSpaceInventoryItemPtr* pEnd,
                                    ItemPtrCompare pCompare)
{
    for (cSpaceInventoryItemPtr* i = pBegin; i != pEnd; ++i) {
        cSpaceInventoryItemPtr value = *i;
        if (pCompare(value.get(), (*(i - 1)).get())) {
            cSpaceInventoryItemPtr* j = i;
            do {
                *j = *(j - 1);
                --j;
            } while (pCompare(value.get(), (*(j - 1)).get()));
            *j = value;
        }
    }
}

// @ 0x0103a280
void eastl_adjust_heap(cSpaceInventoryItemPtr* pFirst, int topIndex, int holeIndex,
                       cSpaceInventoryItemPtr value, ItemPtrCompare pCompare)
{
    int parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && pCompare(pFirst[parent].get(), value.get())) {
        pFirst[holeIndex] = pFirst[parent];
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    pFirst[holeIndex] = value;
}

// @ 0x0103a330
void eastl_iter_swap(cSpaceInventoryItemPtr& a, cSpaceInventoryItemPtr& b)
{
    cSpaceInventoryItemPtr temp = a;
    a = b;
    b = temp;
}

// @ 0x0103a3c0  SP::IsItemARare
bool SP::IsItemARare(uint32_t* pItemID)
{
    cPropertyListPtr pPropList;
    PropertyManager()->GetProperty(*pItemID, 0x34d97fa, (void**)&pPropList);
    if (!(pPropList.get() != 0 && pPropList->HasProperty(0x34f1a4f)))
        return false;
    ResourceKey tradeType = {0, 0, 0};
    GetPropertyAsKey(pPropList.get(), 0x34f1a4f, &tradeType);
    return tradeType.instance == 0x7ecbe6f5;
}
