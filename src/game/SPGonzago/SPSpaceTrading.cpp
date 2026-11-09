// src/game/SPGonzago/SPSpaceTrading.cpp -- migrated from slice(s) s0103eff0, s0103dee0, s0103c3a0, s0103a480, s013a55c0, s0103fe90, s0103e8e0, s0103d380, s0103b3e0, s010393a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceTrading.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPlanetRecord.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPSpaceInventoryItem.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cStarManager.h"
#include "SP/cStarRecord.h"
#include "SP/cTradeRouteData.h"
#include <math.h>
#include <intrin.h>
#include "SP/cString.h"
#include <string.h>
#include "SP/cSPTimer.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "SP/cPropertyList.h"
#include <xmmintrin.h>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cGameData.h"
#include "SP/cTerrainSphere.h"
#include "SP/cRelationshipManager.h"
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s010393a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
inline void* operator new(size_t, void* p) { return p; }
struct ResourceKey {
    uint32_t instance, type, group;
};
inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
    return a.instance == b.instance && a.type == b.type && a.group == b.group;
}
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
struct IMessageServer {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4)
    virtual void SendMSG(uint32_t id, void* msg, void* target);              // +0x14
    VSLOT(6) VSLOT(7) VSLOT(8)
    virtual void AddHandler(void* pHandler, uint32_t msgID);                 // +0x24
};
struct cEmpire_s0103_93a0 {
    uint32_t pad00[0x84 / 4];
    uint32_t mPoliticalID;                                                   // +0x84
    uint32_t GetPoliticalID();                                               // 0x00b1fdb0
};
struct cPlanetRecord_s0103_93a0 {
    virtual void v00();
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
    cEmpire_s0103_93a0* GetOwnerEmpire();                                               // 0x00b8de30
};
struct cStarManager_s0103_93a0 {
    cPlanetRecord_s0103_93a0* GetPlanetRecord(uint32_t planetKey);                      // 0x00ba6dc0
};
cStarManager_s0103_93a0* StarManager();                                                 // 0x00b3d2a0
struct cSpaceInventoryItem;
namespace SP {
uint32_t GetPlayerEmpireID();                                                // 0x01021090
}
namespace SP {
void __stdcall MapRareToSpiceKey(ResourceKey* pKey);                           // 0x01039690
}
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
struct cPlayerItemStore {
    bool DoInsertValue(cSpaceInventoryItem* pItem);                          // 0x00fe4180
    cSpaceInventoryItem* GetReplacement(cSpaceInventoryItem* pItem);         // 0x00fe41c0
};
struct cSpaceGame {
    cSpaceInventory* GetPlayerInventory();                                   // 0x00a1ad60
    cPlayerItemStore* GetItemStore();                                        // 0x00bfc5f0
};
cSpaceGame* SpaceGameGet();                                                  // 0x01002bd0
struct cGonzagoTimer_s0103_93a0 { uint32_t pad00[8]; };
struct cNPCStore {
    uint32_t pad00[3];
    uint32_t mPlanetKey;                                                     // +0x0c
    uint32_t pad10[8];
    int mSpiceBought;                                                        // +0x30
    vector<cSpaceInventoryItemPtr> mNPCInventory;                            // +0x34
    uint32_t pad44;
    vector<cGonzagoTimer_s0103_93a0> mNPCInventoryAges;                                 // +0x48
    uint32_t pad58;
    bool mMarked;                                                            // +0x5c
};
namespace SP {
struct cHandlerIface {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* Cast(uint32_t typeID);                                     // +0x0c
};
}
namespace SP {
struct cTradingHandler {
    uint32_t pad00[2];                                                       // +0x14
    cHandlerIface mIface;                                                    // +0x1c
};
}
namespace SP {
struct cAutoMessageHandler {
    IMessageServer* mpServer;                                                // +0x00
    void* mpHandler;                                                         // +0x04
    const uint32_t* mpIDs;                                                   // +0x08
    uint32_t mnCount;                                                        // +0x0c
    uint32_t mnIndex;                                                        // +0x10
};
}
namespace SP {
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
}
using SP::cSPSpaceTrading;
typedef int (*ItemPtrCompare)(cSpaceInventoryItem*, cSpaceInventoryItem*);
// ---- items of slice s010393a0 end

// ---- items of slice s0103b3e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_13f4fd0;           // 0x013f4fd0
bool GetPropertyAsKeyInstance(PropertyList* pList, uint32_t id, uint32_t* pOut);  // 0x006a12a0
void GetPropertyAsText(PropertyList* pList, uint32_t id, void* pOut);             // 0x006a1360
class cString_s0103_b3e0 {
public:
    uint32_t mTableId;                                                       // +0x00
    void* mpText;                                                            // +0x04
    cString_s0103_b3e0();                                                               // 0x006b5060
    ~cString_s0103_b3e0();                                                              // 0x006b5240
    const uint16_t* GetText();                                               // 0x006b55c0
};
namespace SP {
int __stdcall AddTradingItems(PropertyList* pList, bool bAddMissing);         // 0x01039520
}
namespace SP {
int __stdcall HasTradingItems(PropertyList* pList);                           // 0x01039990
}
template <class T> struct vector_s0103_b3e0 {
    T* mpBegin;                                                              // +0x00
    T* mpEnd;                                                                // +0x04
    T* mpCapacity;                                                           // +0x08
    void* mpAllocator;                                                       // +0x0c
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void reserve(int count);                                                 // 0x00c77b60
    void DoInsertValue(T* pos, const T* value);                              // 0x00cc4160
    void Destroy(T* begin, T* end);                                          // 0x00733030 (FUN_00733030)
    void DestroyAll();                                                       // 0x005c7f10 (vector<AutoRefCount>::~vector)
};
template <class T> struct uvector_s0103_b3e0 {   // size() as size_type
    T* mpBegin;                                                              // +0x00
    T* mpEnd;                                                                // +0x04
    T* mpCapacity;                                                           // +0x08
    void* mpAllocator;                                                       // +0x0c
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
struct cNPCStore_s0103_b3e0;
struct NPCVector {
    intrusive_ptr<cNPCStore_s0103_b3e0>* mpBegin;                                       // +0x00 -> 0x48
    intrusive_ptr<cNPCStore_s0103_b3e0>* mpEnd;                                         // +0x04 -> 0x4c
    intrusive_ptr<cNPCStore_s0103_b3e0>* mpCapacity;                                    // +0x08 -> 0x50
    void* mpAllocName;                                                       // +0x0c -> 0x54
    void* mpPoolBegin;                                                       // +0x10 -> 0x58
    void* mpPoolEnd;                                                         // +0x14 -> 0x5c
    intrusive_ptr<cNPCStore_s0103_b3e0> mBuffer[5];                                     // +0x18 -> 0x60
    int size() const { return (int)(mpEnd - mpBegin); }
    intrusive_ptr<cNPCStore_s0103_b3e0>& operator[](int i) { return mpBegin[i]; }
    void DestroyStore();                                                     // 0x0103b0c0
};
struct cGonzagoTimer_s0103_b3e0 { uint32_t pad00[8]; };
struct cNPCStore_s0103_b3e0 {
    VSLOT(0)
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
    uint32_t mPlanetKey;                                                     // +0x0c
    uint32_t pad10[8];
    int mSpiceBought;                                                        // +0x30
    vector_s0103_b3e0<cSpaceInventoryItemPtr> mNPCInventory;                            // +0x34
    uint32_t pad44;
    vector_s0103_b3e0<cGonzagoTimer_s0103_b3e0> mNPCInventoryAges;                                 // +0x48
    uint32_t pad58;
    bool mMarked;                                                            // +0x5c
};
extern "C" void cGonzagoSubsystem_ctor(void* pThis);                          // 0x00b5b960
extern "C" void cGonzagoSubsystem_dtor(void* pThis);                          // 0x00b5b9a0
namespace SP {
struct cRareGroup {
    ResourceKey mGroupKey;                                                   // +0x00
    uint32_t mGroupID;                                                       // +0x0c
    uvector_s0103_b3e0<ResourceKey> mRares;                                             // +0x10
    uint32_t mState;                                                         // +0x20
};
}
namespace SP {
struct RareMapHeader {
    void* mpAllocator;                                                       // +0x00 -> 0xa0
    void* mpRight;                                                           // +0x04 -> 0xa4
    void* mpLeft;                                                            // +0x08 -> 0xa8
    uint32_t mpParent;                                                       // +0x0c -> 0xac
    uint32_t mColor;                                                         // +0x10 -> 0xb0
    uint32_t mSize;                                                          // +0x14 -> 0xb4
    void DoNukeSubtree(void* root);                                          // 0x009a9600
};
}
namespace SP {
class cSPSpaceTrading_s0103_b3e0 {
public:
    void* mpVtbl00;                                                          // +0x00
    void* mpVtbl04;                                                          // +0x04
    uint32_t mPad08[5];                                                      // +0x08
    void* mpVtblIHandler;                                                    // +0x1c
    void* mpCommodityA;                                                      // +0x20  sp_vector begin  (freed in dtor)
    void* mpCommodityAEnd;                                                   // +0x24
    void* mpCommodityACap;                                                   // +0x28
    uint32_t mPad2c[2];                                                      // +0x2c
    void* mpCommodityB;                                                      // +0x34  sp_vector begin  (freed in dtor)
    void* mpCommodityBEnd;                                                   // +0x38
    void* mpCommodityBCap;                                                   // +0x3c
    uint32_t mPad40[2];                                                      // +0x40
    NPCVector mNPCStore;                                                     // +0x48  fixed_vector<AutoRefCount<cNPCStore>,5,1>
    vector_s0103_b3e0<cSpaceInventoryItemPtr> mUserItems;                               // +0x74  mNPCGiving
    uint32_t mPad84;                                                         // +0x84
    vector_s0103_b3e0<cSpaceInventoryItemPtr> mNPCItems;                                // +0x88  mNPCGetting
    uint32_t mPad94[2];                                                      // +0x94
    int mLastNPCStoreIndex;                                                  // +0x9c
    RareMapHeader mRareMap;                                                   // +0xa0
    uint32_t mPadB8;                                                         // +0xb8
    vector_s0103_b3e0<cRareGroup> mRareGroups;                                          // +0xbc
    uint32_t mPadCC;                                                         // +0xcc
    void* mpAutoServer;                                                      // +0xd0
    void* mpAutoHandler;                                                     // +0xd4
    void* mpAutoIDs;                                                         // +0xd8
    uint32_t mAutoCount;                                                     // +0xdc
    uint32_t mAutoIndex;                                                     // +0xe0
    void* mpStoreArray;                                                      // +0xe4  freed in dtor (array)
    uint32_t mPadE8;                                                         // +0xe8
    uint32_t mPadEC;                                                         // +0xec

    cSPSpaceTrading_s0103_b3e0();                                                       // 0x0103b690
    ~cSPSpaceTrading_s0103_b3e0();                                                      // 0x0103b7c0
    bool AreBasicToolConditionsMet(PropertyList* pList, int param2);          // 0x0103b8d0
    bool FUN_0103bef0(ResourceKey key);                                      // 0x0103bef0
    int ModifyTrade(bool bBuy, bool bProposal, cSpaceInventoryItem* pItem, bool bApply);  // 0x0103b950
    bool IsToolAvailableForTrading(uint32_t toolKey, uint32_t, uint32_t,
                                   PropertyList** ppProperty);               // 0x010398e0
    int GetItemValue(cSpaceInventoryItem* pItem);                            // 0x01039b70
    int GetTradeBalance();                                                   // 0x01039ca0
    int AdjustTradeValue(int bSetCountToOne, cSpaceInventoryItem* pItem);    // 0x01039d20
    cSpaceInventoryItem* FindStoreItem(cSpaceInventoryItem* pItem);          // 0x01039c00
    cSpaceInventoryItem* GetUserItem(uint32_t index);                        // 0x01039ab0
    cSpaceInventoryItem* GetNPCItem(uint32_t index);                         // 0x01039ad0
    bool HasTradingItems(PropertyList* pList);                                // 0x01039990
    bool AddTradingItems(PropertyList* pList, int param2);                    // 0x01039520
    bool ToolConditionA(PropertyList* pList);                                // 0x0103b320
    void MapRareToSpiceKey(ResourceKey* pKey);                               // 0x01039690
    cSpaceInventoryItem* CreateCommodityFromID(void** out, int* id, int count, float cost);  // 0x0103a480
};
}
using SP::cSPSpaceTrading_s0103_b3e0;
struct cSpaceInventory_s0103_b3e0 {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    virtual cSpaceInventoryItem* GetItemEntry(int index);                    // +0x60
    virtual int IndexOf(uint32_t type, const ResourceKey& id);               // +0x64
    virtual cSpaceInventoryItem* GetItemByKey(const ResourceKey* key);        // +0x68
    VSLOT(27) VSLOT(28)
    virtual bool HasItem(const ResourceKey& id);                             // +0x74
    VSLOT(30)
    virtual bool TakeItems(int index, cSpaceInventoryItemPtr& dst, int count);  // +0x7c
    virtual void AddItem(cSpaceInventoryItem* item, int a, bool b);          // +0x80
    VSLOT(33) VSLOT(34)
    virtual int GetCargoCount();                                             // +0x8c
};
struct cSpaceGame_s0103_b3e0 { cSpaceInventory_s0103_b3e0* GetPlayerInventory(); };                 // 0x00a1ad60
cSpaceGame_s0103_b3e0* SpaceGameGet_s0103_b3e0();                                                  // 0x01002bd0
struct cSpaceEconomyTuning {
    int GetMaxCargo();                                                       // 0x0102ff00
    int GetTradingMaxSpiceToBuy();                                           // 0x0102fde0
};
cSpaceEconomyTuning* SpaceEconomyTuning();                                   // 0x0102f810
void* operator_new(int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void  operator_delete_array(void* p);                                        // 0x00f47380
struct EAArrayBlock { uint32_t mnCapacity; uint32_t mData[]; };
inline uint32_t& ArrayCapacity(void* data) { return ((EAArrayBlock*)data - 1)->mnCapacity; }
void  FUN_00a11310(const void* first, const void* last, void* dst);          // 0x00a11310
void  WriteUint32(void* stream, const void* v, int a, int b);                // 0x0093aa70
void  ReadInt32(void* stream, void* v, int a, int b);                        // 0x0093a780
void  RBTreeInsert(void* node, void* parent, void* anchor, int side);        // 0x009216a0
void* RBTreeDecrement(void* node);                                           // 0x009215c0
void  RemoveHandler(void* server, void* handler, void* ids, uint32_t count,
                    uint32_t index);                                          // 0x00571db0 EA::Messaging::RemoveHandler
void  DoNukeSubtree(void* node);                                             // 0x009a9600
struct RandomLinearCongruential { uint32_t RandomUint32Uniform(int n); };      // 0x00a68fb0
void  FUN_00ae2ed0(void* rng, void* out);                                    // 0x00ae2ed0
void  FUN_00eeee80(void* pos, void* value);                                  // 0x00eeee80
void* FUN_00c463d0(void* p1, int a, float b);                                // 0x00c463d0
void  FUN_0103b290(int* a, int b, int c);                                    // 0x0103b290
void  FUN_0103a330(int* a, int* b);                                          // 0x0103a330 iter_swap
cSpaceInventoryItem* interface_cast_item(void* p);                           // 0x00c87070
void* FUN_00b3d3d0(int a, int b, void* c, int d);                           // 0x00b3d3d0
struct cPlayerEmpire { int GetMoney(); };                                     // 0x00c30cb0
cPlayerEmpire* FUN_01021300();                                               // 0x01021300
int   FUN_006c0200(cSpaceInventoryItem* pItem);                              // 0x006c0200
struct ObjV04 { VSLOT(0) virtual void v1(int v); virtual void v2(); };       // +0x04 / +0x08
struct ObjV04x { VSLOT(0) virtual void v1(int a, int b); virtual void v2(); };// +0x04 (2-arg sift call)
struct ObjV08 { VSLOT(0) VSLOT(1) virtual void v2(); };                      // +0x08
struct IStreamWrite {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void* v6();                                                      // +0x18
    virtual void v7();                                                       // +0x1c
    virtual void* v8();                                                      // +0x20
    VSLOT(9) VSLOT(10)
    virtual void v11(uint32_t v);                                            // +0x2c
};
struct ObjV18 { VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) virtual void* v6(); };
struct StoreIface { VSLOT(0) VSLOT(1) VSLOT(2) virtual void* Cast(uint32_t typeID); };
struct StoreLayout { uint32_t pad00[2]; StoreIface mIface; };               // iface at +0x08
struct RBNode {
    RBNode* mpNodeRight;                                                     // +0x00
    RBNode* mpNodeLeft;                                                      // +0x04
    RBNode* mpNodeParent;                                                    // +0x08
    char mColor;                                                             // +0x0c
    uint32_t pad0d[3];
    ResourceKey mKey;                                                        // +0x10
    uint32_t mValue;                                                         // +0x1c
};
struct RBAnchorSet {
    uint32_t pad0;
    RBNode mAnchor;                                                          // +0x04
    uint32_t mnSize;                                                         // +0x14
};
struct RareMapKey { ResourceKey mKey; uint32_t mValue; };
void FUN_0103b1b0(int* a, int param2, int n, int start);
struct RBInsertResult { void* mpNode; uint8_t mbInserted; };
void FUN_0103b640(int* first, int* last, int extra);
struct EntryTail {
    uint32_t w0;                                                             // +0x00
    uint32_t rest[4];                                                        // +0x04
    void Copy(void* src);                                                    // 0x006606a0
};
struct Entry24 {
    uint32_t w0, w1, w2, w3;                                                 // +0x00..+0x0c
    EntryTail tail;                                                          // +0x10
};
static uint32_t TradeItemRank(uint32_t id)
{
    switch (id) {
        case 0xb978c47a: return 1;
        case 0x82af541:  return 0;
        case 0x4edcc2bf: return 4;
        case 0x7ecbe6f5: return 3;
        case 0xc045a9a3: return 4;
        case 0xeb1a8062: return 2;
        default:         return id;
    }
}
struct ObjV20 {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void* v6();                                                      // +0x18
    virtual void v7();                                                       // +0x1c
    virtual void* v8();                                                      // +0x20
};
void FUN_0103b4e0(vector_s0103_b3e0<ResourceKey>* self, uint32_t count);
// ---- items of slice s0103b3e0 end

// ---- items of slice s0103d380 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
#define VS(o, off)   (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)  ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))
struct Vector3 { float x, y, z; };
struct RBTree {
    u32    mField00;      // +0x00
    void*  mAnchorLeft;   // +0x04  (self pointer)
    void*  mAnchorRight;  // +0x08
    void*  mpRoot;        // +0x0c
    u8     mColor;        // +0x10
    u8     mPad11[3];
    u32    mSize;         // +0x14
    void   DoNukeSubtree(void* root);   // 0x009a9600
    u32*   FUN_0103bc40(void* key0, void* key1, u8 flag);  // 0x0103bc40
    void   FUN_00c7f560(void** out, void* key);            // 0x00c7f560
    void   FUN_0103c6b0(void* node, void* key, void* key2, u32 flag);  // 0x0103c6b0
    u32*   FUN_0103de50(u32* key);      // 0x0103de50
};
struct cNPCStoreFixedVec {
    void* mpBegin;     // +0
    void* mpEnd;       // +4
    void* mpCapacity;  // +8
    void  clearRange(void* b, void* e);          // 0x0103c4f0
    void  pushSlow(void* pos, void* val);        // 0x0103c550
    void  FUN_00c77b60(u32 count);               // 0x00c77b60
};
struct RefObj {
    u8    mPad0[8];
    void* mpVtbl;      // +8
};
struct SpVector3 {
    Vector3* mpBegin;      // +0
    Vector3* mpEnd;        // +4
    Vector3* mpCapacity;   // +8
    Vector3* erase(Vector3* first, Vector3* last);   // 0x0050f740
};
struct cNPCStoreVec {
    void* mpBegin;     // +0
    void* mpEnd;       // +4
    void* mpCapacity;  // +8
    void  clearRange(void* first, void* last);   // 0x0103c4f0
};
struct cGonzagoTimer {
    u32 mData[8];           // +0x00 .. +0x20
    cGonzagoTimer();        // 0x00b63890
    ~cGonzagoTimer();       // 0x00b638b0
};
void FUN_00571db0(void* h, u32 a, u32 b, u32 c, u32 d);  // 0x00571db0 (EA::Messaging::RemoveHandler)
struct cGonzagoTimerVec {
    cGonzagoTimer* mpBegin;     // +0
    cGonzagoTimer* mpEnd;       // +4
    cGonzagoTimer* mpCapacity;  // +8
    void insert(cGonzagoTimer* pos, cGonzagoTimer* val);  // 0x00bf5420
    void push_back();           // 0x0103de00
};
struct cSPSpaceTrading_s0103_d380 {
    u8             m00[0x20];        // +0x000
    SpVector3      mV20;             // +0x020
    u8             m2c[0x08];        // +0x02c
    SpVector3      mV34;             // +0x034
    u8             m40[0x08];        // +0x040
    cNPCStoreVec   m48;              // +0x048
    u8             m54[0x4c];        // +0x054
    RBTree         mTree;            // +0x0a0
    u8             mB8[0x18];        // +0x0b8
    void*          mpMsgD0;          // +0x0d0
    u32            mD4;              // +0x0d4
    u32            mD8;              // +0x0d8
    u32            mDC;              // +0x0dc
    u32            mE0;              // +0x0e0

    void ShutdownGonzagoSubsystem();          // 0x0103dd20
    void FUN_0103dd80();                      // 0x0103dd80
};
struct SpRefVec {
    void** mpBegin;      // +0
    void** mpEnd;        // +4
    void** mpCapacity;   // +8
    void** erase(void** first, void** last);   // 0x005c2170
};
struct cPaletteItem {
    u8     m00[0x10];
    u32    m10;          // +0x10
    u8     m14[0x1c];
    u32    m30;          // +0x30
};
struct cPaletteGroup {
    u8     m00[0x10];
    u32    m10;          // +0x10
    u8     m14[0x20];    // +0x14 .. +0x34
    void** mpBegin34;    // +0x34
    void** mpEnd38;      // +0x38
};
struct cPaletteHost {
    u8         m00[0x48];
    void**     mVec48Begin;   // +0x48
    void**     mVec48End;     // +0x4c
    u8         m50[0x28];     // +0x50 .. +0x74
    SpRefVec   mV74;          // +0x74
    u8         m80[0x08];     // +0x80 .. +0x88
    SpRefVec   mV88;          // +0x88
    void FUN_0103dbd0(u8 param_2);   // 0x0103dbd0
};
void GetPropertyAsKey(u32 prop, u32 tag, void* out);   // 0x006a1250
struct RBNode_s0103_d380 {
    u32 m00;   // +0x00
    u32 m04;   // +0x04
    u32 m08;   // +0x08
    u32 m0c;   // +0x0c
    u32 m10;   // +0x10
    u32 m14;   // +0x14
    u32 m18;   // +0x18
};
// ---- items of slice s0103d380 end

// ---- items of slice s0103e8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kHalf;                                                   // 0x01471064
struct PropertyList_s0103_e8e0 {
    virtual int AddRef();
    virtual int Release();
};
void GetPropertyAsKey(PropertyList_s0103_e8e0* list, uint32_t id, ResourceKey* out);       // 0x006a1250
void GetPropertyAsText(PropertyList_s0103_e8e0* list, uint32_t id, int arg);               // 0x006a1360
struct PropertyManager {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList_s0103_e8e0** ppDst);   // +0x2c
};
PropertyManager* PropertyManager_Get();                                         // 0x0067de30
template <class T> struct intrusive_ptr_s0103_e8e0 {
    T* mpObject;
    intrusive_ptr_s0103_e8e0() : mpObject(0) {}
    intrusive_ptr_s0103_e8e0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    intrusive_ptr_s0103_e8e0(const intrusive_ptr_s0103_e8e0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr_s0103_e8e0() { if (mpObject) mpObject->Release(); }
    T** AsOutParam()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
        return &mpObject;
    }
    intrusive_ptr_s0103_e8e0& operator=(T* p)
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
    intrusive_ptr_s0103_e8e0& operator=(const intrusive_ptr_s0103_e8e0& o) { return operator=(o.mpObject); }
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cSpaceInventoryItem_s0103_e8e0 {
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
    PropertyList_s0103_e8e0* mpPropList;                                                // +0x30

    int GetUnitValue_006c0200();
};
typedef intrusive_ptr_s0103_e8e0<cSpaceInventoryItem_s0103_e8e0> ItemPtr;
struct cSPTimer_s0103_e8e0 {
    uint64_t GetElapsedTime();                                               // 0x00bc3190
    void Restart();                                                          // 0x00bc3130
};
struct cNPCStoreBase { virtual void _b0(); uint32_t pad04; };
struct IRefCount_s0103_e8e0 {
    virtual int AddRef();
    virtual int Release();
};
struct cNPCStore_s0103_e8e0 : cNPCStoreBase, IRefCount_s0103_e8e0 {
    uint32_t mPlanetKey;                                                     // +0x0c
    cSPTimer_s0103_e8e0 mTimer;                                                         // +0x10
    uint32_t pad14[(0x30 - 0x14) / 4];
    int mSpiceBought;                                                        // +0x30
    vector<ItemPtr> mNPCInventory;                                           // +0x34
    uint32_t pad44[(0x5c - 0x44) / 4];
    uint8_t mbNeedsReset;                                                    // +0x5c
    uint8_t pad5d[3];
    ResourceKey* mpSpiceID;                                                  // +0x60
    uint32_t pad64[(0xc0 - 0x64) / 4];
    cNPCStore_s0103_e8e0();                                                             // 0x0103cf20
};
typedef intrusive_ptr_s0103_e8e0<cNPCStore_s0103_e8e0> NPCStorePtr;
void* operator new(size_t, const char*, int, int, int, int);                 // 0x00f473a0
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
struct cEmpire_s0103_e8e0 {
    uint32_t* GetStars();                                                    // 0x00c308d0 (returns this+0x88)
};
struct cStarManager_s0103_e8e0 {
    cEmpire_s0103_e8e0* GetEmpireByID(uint32_t id);                                     // 0x00ba9370
};
cStarManager_s0103_e8e0* StarManager_s0103_e8e0();                                                 // 0x00b3d2a0
struct cAvatarHolder {
    uint32_t GetAvatarEmpireID();                                            // 0x00b1fdb0
};
struct cPlanetRef {
    uint32_t GetCommContext();                                               // 0x00ce6950
    cAvatarHolder* GetAvatarHolder();                                        // 0x00b8de30
    ResourceKey* GetSpiceKey();                                              // 0x00b8dad0 (this+0x198)
};
namespace EA {
namespace Random {
 struct RandomLinearCongruential_s0103_e8e0 { double RandomDoubleUniform(); };   // 0x009360d0
}
}
extern EA::Random::RandomLinearCongruential_s0103_e8e0 gRandom;                         // 0x01601760
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
class cSPSpaceTrading_s0103_e8e0 {
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
    bool FUN_0103b320(PropertyList_s0103_e8e0* list);
    void RefreshNPCSpiceCosts(cPlanetRef* planet);                           // 0x0103cd00
    void ConsiderBuyingRareGroup(ResourceKey key);                           // 0x0103d580
    void CreateCommodityEntry_0103d720(cEmpire_s0103_e8e0* empire, ResourceKey key);    // 0x0103d720
    void FUN_0103d9b0(cPlanetRef* planet, ResourceKey key);
    void ConsiderSellingTool(cPlanetRef* planet, uint32_t flag, ResourceKey key);   // 0x0103dee0
    void FUN_0103e6e0(cPlanetRef* planet, ResourceKey key);
    void CreateNPCInventory(cPlanetRef* planet, int text);  // 0x0103e8e0 (SP::cSPSpaceTrading::CreateNPCInventory)
};
}
using SP::cSPSpaceTrading_s0103_e8e0;
// ---- items of slice s0103e8e0 end

// ---- items of slice s0103fe90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_0067de30(void);                       // 0x0067de30 SP::PropertyManager
extern "C" void  __cdecl FUN_00f47380(void* p);                    // 0x00f47380 operator_delete_array
extern "C" void  __cdecl FUN_006a1250(void* obj, int key, void* out); // 0x006a1250 SP::GetPropertyAsKey
extern "C" void  __cdecl FUN_0011e07ef(void* fn);                  // 0x011e07ef lib_crt::atexit
extern "C" void* __cdecl FUN_01021260(void);                       // 0x01021260 cSPLivingUniverse::GetActivePlanet
extern "C" void  __cdecl FUN_0103fc10(void* a, void* b);           // 0x0103fc10 AddCommodityToInventory
extern "C" void* __cdecl FUN_0103c8a0(void* a, void* b, void* c);  // 0x0103c8a0
extern "C" void* __cdecl FUN_00b3d300(void);                       // 0x00b3d300 SP::NounManager
extern "C" void* __cdecl FUN_00ac9310(void* a, void* b, int c);    // 0x00ac9310
extern "C" void* __cdecl FUN_00b3d2c0(void* a);                    // 0x00b3d2c0 SP::RelationshipManager
extern "C" void* __cdecl FUN_00b3d3e0(int a, int b, int c, int d, int e, int f); // 0x00b3d3e0 SP::EventLog
extern "C" void* __cdecl FUN_00b8dad0(void);                       // 0x00b8dad0
extern "C" void* __cdecl FUN_00675250(int a, int b);               // 0x00675250 Achievements::Controller
extern "C" void* __cdecl FUN_00bd81f0(float f);                    // 0x00bd81f0
extern "C" void* __cdecl FUN_00ffbe50(int a, int b);               // 0x00ffbe50 SP::GetUFOSimulator
extern "C" void  __cdecl FUN_00ff5270(void* a, float b, void* c);  // 0x00ff5270 SP::DoCommunityReaction
extern "C" void  __cdecl FUN_013caa00(void);                       // 0x013caa00 static dtor
extern "C" void  __cdecl FUN_00cd7d10(void);                       // 0x00cd7d10
extern "C" void  __cdecl FUN_00d3d420(void);                       // 0x00d3d420
extern "C" void  __cdecl FUN_00acdff0(void);                       // 0x00acdff0
extern "C" void  __cdecl FUN_00b1e500(void);                       // 0x00b1e500
extern uint32_t  DAT_016df524;               // 0x016df524 static cRegNode object
extern uint32_t  DAT_016df538;               // 0x016df538 static guard
extern uint32_t  DAT_018c43e8;               // 0x018c43e8
extern uint32_t  vtbl_01499b0c[];            // 0x01499b0c static vtable
#pragma intrinsic(_ReadWriteBarrier)
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
extern "C" void* __cdecl FUN_01021300_s0103_fe90(void);                       // 0x01021300 cSPLivingUniverse::GetPlayerEmpire
class tHost {
public:
    void  __thiscall FUN_00692f60(int a);                    // 0x00692f60 cRegNode::Construct
    char  __thiscall FUN_00ab30c0();                         // 0x00ab30c0
    void  __thiscall FUN_00692850();                         // 0x00692850
    void* __thiscall FUN_00baf700();                         // 0x00baf700
    void  __thiscall FUN_00733030(void* a, void* b);         // 0x00733030
    void* __thiscall FUN_00c71e30();                         // 0x00c71e30
    void* __thiscall FUN_00f67d90();                         // 0x00f67d90 GetCurrentTerrainSphere
    char  __thiscall FUN_00c75650();                         // 0x00c75650 cTerrainSphere::Check
    void  __thiscall FUN_00bdbf10();                         // 0x00bdbf10
    void  __thiscall FUN_00ff0350(float f);                  // 0x00ff0350 cCityData::AddValue
    void  __thiscall FUN_00fffdd0(int a, int b);             // 0x00fffdd0
    void* __thiscall FUN_00d06240(void* a);                  // 0x00d06240 cRelationshipManager::RecordEvent
    void  __thiscall FUN_00dd8640(int a, int b, int c, int d, int e, int f); // 0x00dd8640 PostFeedbackEvent
    void  __thiscall FUN_00676e90(int a, int b);             // 0x00676e90 Achievements::AutoTest
    void* __thiscall FUN_00b21340(void* a, void* b, void* c, void* d, void* e); // 0x00b21340 GetGameDataVector
};
class SpVec24 {
public:
    void* mBegin;                // +0x00
    void* mEnd;                  // +0x04
    void* mCap;                  // +0x08
    void __thiscall FUN_01040090(void* dst, void* src);
};
class SpVec3 {
public:
    void* mBegin;                // +0x00
    void* mEnd;                  // +0x04
    void* mCap;                  // +0x08
    void* __thiscall FUN_0050f740(void* a, void* b);
    void  __thiscall FUN_004548d0(int n);   // 0x004548d0 reserve
    void  __thiscall FUN_004e3e10(void* a, void* b); // 0x004e3e10 SPVector<Key>::DoInsertKey
};
class cSPSpaceTrading_s0103_fe90 {
public:
    void*    mpVfptr;            // +0x000
    uint8_t  m004[0x1c];         // +0x004
    SpVec3   mVec20;             // +0x020
    uint8_t  m02c[8];            // +0x02c
    SpVec3   mVec34;             // +0x034
    uint8_t  m040[0x70];         // +0x040 -> +0x0b0
    SpVec3   mVecB0;             // +0x0b0
    SpVec24  mVecBC;             // +0x0bc
    uint8_t  m0c8[0x570];        // +0x0c8 -> +0x638
    void*    m638;               // +0x638
    void*    m63c;               // +0x63c
    uint8_t  m640[0xc];          // +0x640 -> +0x64c
    int      m64c;               // +0x64c
    int      m650;               // +0x650
    int      m654;               // +0x654

    void __thiscall FUN_01040220();
    void __thiscall FUN_01040610();
    void __thiscall FUN_010406d0();  // 0x010406d0 (cSPSpaceTrading::FUN_010406d0)
    static void __cdecl CollectSpicePile(void* param_1, void* param_2);  // 0x0103fe90 (cSPSpaceTrading::CollectSpicePile)
};
// ---- items of slice s0103fe90 end

// ---- items of slice s013a55c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AttrRec {
    const char* mpName;              // +0x00
    void*       mpField;             // +0x04
    int32_t     mFieldOfs;           // +0x08
    int32_t     mUnk0c;              // +0x0c  (left indeterminate, as in the original)
    int32_t     mUnk10;              // +0x10
    int32_t     mUnk14;              // +0x14
    int32_t     mZero18;             // +0x18
    int32_t     mZero1c;             // +0x1c
    void*       mpFn20;              // +0x20
    void*       mpFn24;              // +0x24
    void*       mpFn28;              // +0x28
    void*       mpFn2c;              // +0x2c
    void*       mpFn30;              // +0x30
    void*       mpFn34;              // +0x34
    void*       mpFn38;              // +0x38
};
char g_5b83971;  char g_5b83972;  char g_5b83973;  char g_5b83974;
char g_5b83975;  char g_5b83976;  char g_5b83977;  char g_60b5062;
char g_3d840ef;  char g_5b82ced;  char g_5f76c77;
char g_692ca0;   char g_572810;   char g_572840;   char g_693090;
char g_6930b0;   char g_694fc0;   char g_acbb80;   char g_ae3470;
char g_ae3490;   char g_c2e4e0;   char g_692fb0;   char g_ae3310;
char g_ac8050;   char g_692ff0;   char g_694ee0;   char g_57cde0;
char g_ac8750;   char g_ac8780;   char g_694fa0;   char g_57ce00;
char g_103c1f0;  char g_c6adc0;   char g_c6c4e0;   char g_103c2c0;
char g_f26ca0;   char g_103c3a0;  char g_c87f80;   char g_c87c00;
char g_c875f0;   char g_c6c390;   char g_bf77d0;   char g_bf1cf0;
char g_bf1d50;   char g_f29650;   char g_103d380;  char g_103b100;
char g_d011e0;   char g_fe4aa0;   char g_103d4a0;  char g_103b460;
char g_103a0a0;  char g_b04e00;   char g_c761c0;   char g_eafe40;
AttrRec g_t15b8140[8];
AttrRec g_t15b8360[3];
// ---- items of slice s013a55c0 end

// ---- items of slice s0103a480 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_rand;              // 0x01601760
extern int g_16df56c, g_16df570, g_16df574;   // key sentinel ints
extern float g_16df53c, g_16df540, g_16df544;
typedef unsigned int uint;
struct V14 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void v14(void*); };
struct V18 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual int v18(); };
struct V1c { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void v1c(); };
struct V20 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
virtual void z4();
virtual void z5();
virtual void z6();
virtual void z7();
             virtual void* v20(); };
struct V4  { virtual int AddRef(); virtual int Release(); };
struct HRef { virtual void h0(); virtual int AddRef(); virtual int Release(); };
struct AutoRef {
    HRef* mpRef;
    AutoRef(HRef* p = 0) : mpRef(p) { if (mpRef) mpRef->AddRef(); }
    AutoRef(const AutoRef& o) : mpRef(o.mpRef) { if (mpRef) mpRef->AddRef(); }
    ~AutoRef() { if (mpRef) mpRef->Release(); }
    AutoRef& operator=(const AutoRef& o) {
        if (mpRef != o.mpRef) {
            if (o.mpRef) o.mpRef->AddRef();
            HRef* old = mpRef;
            mpRef = o.mpRef;
            if (old) old->Release();
        }
        return *this;
    }
};
struct V70 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
virtual void z4();
virtual void z5();
virtual void z6();
virtual void z7();
virtual void z8();
virtual void z9();
virtual void z10();
virtual void z11();
virtual void z12();
virtual void z13();
virtual void z14();
virtual void z15();
virtual void z16();
virtual void z17();
virtual void z18();
virtual void z19();
virtual void z20();
virtual void z21();
virtual void z22();
virtual void z23();
virtual void z24();
virtual void z25();
virtual void z26();
virtual void z27();
             virtual bool v70(int id, void* k); };
struct V74 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
virtual void z4();
virtual void z5();
virtual void z6();
virtual void z7();
virtual void z8();
virtual void z9();
virtual void z10();
virtual void z11();
virtual void z12();
virtual void z13();
virtual void z14();
virtual void z15();
virtual void z16();
virtual void z17();
virtual void z18();
virtual void z19();
virtual void z20();
virtual void z21();
virtual void z22();
virtual void z23();
virtual void z24();
virtual void z25();
virtual void z26();
virtual void z27();
             virtual void z28(); virtual bool v74(void* k); };
struct Prop { char pad[0x12]; unsigned short type; float* GetFloat();   // 0x0041ea70
};
struct VProp24 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
virtual void z4();
virtual void z5();
virtual void z6();
virtual void z7();
                 virtual void z8(); virtual bool v24(uint id, void** out); };
struct IUnk { virtual int AddRef(); virtual int Release(); };
struct PropertyMgr {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
    virtual void Unregister(int id, int key, IUnk** out);   // +0x2c
};
void* operator_new(int size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void  operator_delete(void* p);                                                // 0x00f47380
void* PropertyManager();                                                       // 0x0067de30
void  GetPropertyAsKey(void* list, uint id, void* out);                        // 0x006a1250
void  GetFloatProperty(void* list, uint id, void* out);                        // 0x0040cf10
void* SpaceGameGet_s0103_a480();                                                          // 0x01002bd0
void* StarManager_s0103_a480();                                                           // 0x00b3d2a0
void* NounManager();                                                           // 0x00b3d300
void* PlanetModel();                                                           // 0x00b3d350
void* GetPlayerEmpire();                                                       // 0x01021300
int   GetCurrentGameMode();                                                    // 0x00b5b800
void* RBTreeIncrement(void* node);                                             // 0x00921580
void  FUN_00ae2e40(void* a, void* b);                                          // 0x00ae2e40
void  FUN_00c731a0(int a, int b, int c, int d, int e, int f, int g, int h, int i);  // 0x00c731a0
void  FUN_00c731a0(int a, int b, int c);                                       // 3-arg form (0x00c731a0)
void  FUN_00c731a0(int a, int b, int c, int d);                                // 4-arg form (0x00c731a0)
void  FUN_00afa030(void* o);                                                   // 0x00afa030
struct Vec3f { float x, y, z; };
struct Commodity {
    char pad0[0x10];
    int   mItemCount;    // +0x10
    int   mType;         // +0x14
    int   mCost;         // +0x18
    Commodity* ctor_00c87660();                 // thiscall ctor (ecx = item)
    void SetPropertyList_00c877f0(void* list);  // thiscall
};
struct VItemRef { virtual void z0(); virtual int AddRef(); };   // AddRef at +4
struct T540 {
    char pad0[0x34];
    int* mBegin;   // +0x34
    int* mEnd;     // +0x38
    uint scan(void* p);
};
struct Vec3i { int x, y, z; };
struct HashObj { virtual void z0(); virtual void z1(); virtual void z2(); virtual int v3(uint id); };
struct V6 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
            virtual void z4(); virtual void z5(); virtual Vec3i* get(); };
struct HPosition { void get(void* out); };                    // 0x0104be80 (thiscall, ret 4)
struct TToolMgr { bool createTool(void* key, void** out); };  // 0x0104e340 (thiscall, ret 8)
void* FUN_00b3d390();                                          // 0x00b3d390 (global getter)
struct A630 {
    bool f_0103a630(void* item, int x, int y, int z);
};
struct T760 {
    char pad0[0xbc];
    int* volatile mBegin;   // +0xbc
    int* volatile mEnd;     // +0xc0
    uint find(int id);
};
struct MsgRef { virtual int AddRef(); virtual int Release(); };
struct B3Obj {
    void* get_ba6dc0(int id);      // 0x00ba6dc0 (thiscall, ret 4)
    int   get_ba9370(void* av);    // 0x00ba9370 (thiscall, ret 4)
};
struct NounObj { void* f_b8de30(); };   // 0x00b8de30 (thiscall)
struct AvObj   { void* f_b1fdb0(); };   // 0x00b1fdb0 (thiscall)
struct SPTrading {
    char pad0[0x2c];
    void** mBegin;   // +0x2c
    void** mEnd;     // +0x30
    int handleMessage(int msg, void* arg);
};
struct Empire { int f_c30c60(); };                      // 0x00c30c60 (thiscall)
struct RngObj { double nextDouble(); };                 // 0x009360d0 (thiscall)
struct RareNoun { bool f_b8d970(); void* f_b8de30(); }; // 0x00b8d970 / 0x00b8de30
struct Trading34 {
    char pad0[0x34];
    int* mBegin;   // +0x34 (0xc-byte elements)
    int* mEnd;     // +0x38
    void addRareCommodity(void* p2);
};
struct RBTreeT {
    void** find(void** out, const int* k);   // 0x00a21dc0
};
struct TAC40 {
    char pad0[0xa0];
    void* find(int* key);
};
struct RareNode {
    char pad0[0x1c];
    int  mCount;      // +0x1c
};
struct RareTree {          // EASTL rbtree map living at trading+0xa0
    char  pad0[4];
    void* mAnchor;         // +0x4   header node (end iterator)
    char  pad1[4];
    void* mRoot;           // +0xc
    int   mCount;          // +0x10
    void** find(void** out, const int* key);   // 0x00a21dc0
};
struct GroupEntry {        // 0x24-byte element of the commodity-group table
    char pad0[0x10];
    int* mBegin;           // +0x10  int[3] keys, stride 0xc
    int* mEnd;             // +0x14
    char pad1[0xc];
};
struct SpaceGame {
    void* get_00a1ad60();  // GetPlayerInventory (thiscall)
};
struct TSx {
    char pad0[0xa0];
    RareTree  mRare;       // +0xa0
    char pad1[8];
    GroupEntry* mGroups;   // +0xbc
    bool f_ac70(int group, bool needInventory);
    void f_af90(void* p1, void* p2);
    bool f_b320(int* prop);
};
struct ItemVecB { char pad0[0x3c]; void** mBegin; void** mEnd; };  // +0x3c / +0x40
struct ItemCtr  { ItemVecB* getItems(int kind); };                  // 0x00b8dec0 (thiscall, ret 4)
struct RngAd    { uint nextInt(int n); };                           // 0x00a68fb0 (thiscall, ret 4)
struct WorldItemAd { Vec3f* getPos(); };                            // 0x00572590 (thiscall)
struct VItem3 {
virtual void z0();
virtual void z1();
virtual void Release();
virtual void z3();
virtual void z4();
virtual void z5();
    virtual void* v18(int a, int b, Vec3f pos);                     // +0x18
};
struct VItem2 {
virtual void z0();
virtual void z1();
virtual void Release();
virtual void z3();
virtual void z4();
virtual void z5();
    virtual void* v18(int a, int b);                                // +0x18
};
struct VPosAd {
virtual void z0();
virtual void z1();
virtual void z2();
virtual void z3();
virtual void z4();
virtual void z5();
virtual void z6();
virtual void z7();
virtual void z8();
virtual void z9();
virtual void z10();
    virtual int  get_2c();                                          // +0x2c
    virtual void z12();                                             // +0x30
    virtual void z13();                                             // +0x34
    virtual void get_38(Vec3f* out);                                // +0x38
    virtual void set_3c(int v);                                     // +0x3c
};
struct ArtifactAd {
    char pad0[0x34];
    VPosAd mPos;                                                    // +0x34 (vptr)
    void f_c69090();                                                // 0x00c69090 (thiscall)
};
struct SetterAd { void set(void* a, void* b); };                    // 0x00c74d30 (thiscall, 2 args)
struct ModelAd  { int build(int angle, Vec3f* pos); };              // 0x00b7f190 (thiscall, 2 args)
struct NounAd {
virtual void z0();
virtual void z1();
virtual void z2();
    virtual void* getArtifact(int id);                              // +0x0c
};
struct NounMgrAd { void* createNoun(int id); };                     // 0x00b20c60 (thiscall, ret 4)
struct Rng {                        // global RNG object at 0x01601760
    uint next_00a68fb0(int n);       // uniform int in [0,n)
};
struct WorldObj {
    Vec3i* pos_00b8dad0();           // returns this+0x198
    void*  item_00b8dec0(int idx);   // 0x00b8dec0
};
struct ItemVec {                     // container read at +0x3c/+0x40
    char pad0[0x3c];
    void** mBegin;                   // +0x3c
    void** mEnd;                     // +0x40
};
struct ItemElem {
    char  pad0[0x1c];
    float mValue;                    // +0x1c
    void add_00ff0350(float f);      // thiscall
};
struct Ad50 {                        // view of the trading object for the AddCitySpicePile call
    void call_0103ad50(void* star, Vec3i* pos, uint amount, int extra);
};
struct RefObj_s0103_a480 { char pad[8]; V4 base; };
struct VecDtor {
    void** mpBegin;    // +0
    void** mpEnd;      // +4
    void** mpCapacity; // +8
    void** mpFixed0;   // +0xc
    void** mpFixed;    // +0x10
    void dtor();
};
void FUN_0103a280(AutoRef* a, int top, int hole, AutoRef value, int (*fn)(int,int));
struct InvItems {
    void* list_00ff5b80();   // returns this+0x34
};
// ---- items of slice s0103a480 end

// ---- items of slice s0103c3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* memcpy(void*, const void*, unsigned int);
extern const char kEastlAllocatorName[];     // 0x013f09b4 "Simulator"
extern const int kEastlAllocatorDesc;        // 0x013ebb38 eastl allocator description
struct ResourceKey_s0103_c3a0 {
    uint32_t instance;      // +0x00
    uint32_t type;          // +0x04
    uint32_t group;         // +0x08
};
inline bool operator<(const ResourceKey_s0103_c3a0& a, const ResourceKey_s0103_c3a0& b)
{
    if (a.instance != b.instance)
        return a.instance < b.instance;
    if (a.group != b.group)
        return a.group < b.group;
    return a.type < b.type;
}
inline bool operator==(const ResourceKey_s0103_c3a0& a, const ResourceKey_s0103_c3a0& b)
{
    return a.instance == b.instance && a.type == b.type && a.group == b.group;
}
inline bool operator!=(const ResourceKey_s0103_c3a0& a, const ResourceKey_s0103_c3a0& b) { return !(a == b); }
extern const ResourceKey_s0103_c3a0 kNoKey;      // 0x016df56c: the empty EA::ResourceMan::Key
struct Property_s0103_c3a0 {
    union Value {
        void* mpData;       // +0x00 pointer form (used when mFlags has 0x30)
        float mFloat;       // +0x00 inline float form
        uint32_t mUInt;     // +0x00 inline integer form
    } mValue;
    uint32_t mPad04[(0x10 - 4) / 4];    // +0x04
    uint8_t mFlags;                     // +0x10 (0x30 = value is heap/offset pointer)
    uint8_t mPad11;                     // +0x11
    uint16_t mType;                     // +0x12 (0x0a = uint, 0x0d = float)

    float* GetFloatPtr();               // 0x0041ea70
    uint32_t* GetUIntPtr();             // 0x0041ea00
};
struct PropertyList_s0103_c3a0 {
    virtual int AddRef();                                   // +0x00 0x00432be0
    virtual void Release();                                 // +0x04
    virtual void _v2();                                     // +0x08
    virtual void _v3();                                     // +0x0c
    virtual void _v4();                                     // +0x10
    virtual void _v5();                                     // +0x14
    virtual void _v6();                                     // +0x18
    virtual void _v7();                                     // +0x1c
    virtual void _v8();                                     // +0x20
    virtual bool GetProperty(uint32_t id, Property_s0103_c3a0** ppProp);   // +0x24
};
struct PropertyManager_s0103_c3a0 {
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();
virtual void _v7();
virtual void _v8();
virtual void _v9();
virtual void _v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList_s0103_c3a0** ppList);   // +0x2c
};
PropertyManager_s0103_c3a0* PropertyManager_Get_s0103_c3a0();                                   // 0x0067de30
bool GetPropertyAsKey_s0103_c3a0(PropertyList_s0103_c3a0* pList, uint32_t id, ResourceKey_s0103_c3a0* pKey);   // 0x006a1250
void GetPropertyT_int(PropertyList_s0103_c3a0* pList, uint32_t id, int* pOut);          // 0x0040cf10
struct IRefCount_s0103_c3a0 {
    virtual int AddRef();                // +0x00
    virtual void Release();              // +0x04
};
inline int RefAddRef(PropertyList_s0103_c3a0* p) { return p->AddRef(); }
inline void RefRelease(PropertyList_s0103_c3a0* p) { p->Release(); }
template <class T> inline int RefAddRef(T* p) { return p->mRefCount.AddRef(); }
template <class T> inline void RefRelease(T* p) { p->mRefCount.Release(); }
class cSpaceInventoryItem_s0103_c3a0 {
public:
    uint32_t mPad00[2];                  // +0x00
    IRefCount_s0103_c3a0 mRefCount;                 // +0x08
    uint32_t mItemCount;                 // +0x10
    uint32_t mItemType;                  // +0x14
    uint32_t mItemCost;                  // +0x18
    uint32_t mPad1c[5];                  // +0x1c
    PropertyList_s0103_c3a0* mpPropList;            // +0x30
};
template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) RefAddRef(mpObject); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { if (mpObject) RefAddRef(mpObject); }
    ~AutoRefCount() { if (mpObject) RefRelease(mpObject); }
    T** AsOutParam()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; RefRelease(pOld); }
        return &mpObject;
    }
    AutoRefCount& operator=(const AutoRefCount& o) { return operator=(o.mpObject); }
    AutoRefCount& operator=(T* p)
    {
        T* const pOld = mpObject;
        if (p != pOld) {
            if (p)
                RefAddRef(p);
            mpObject = p;
            if (pOld)
                RefRelease(pOld);
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
typedef AutoRefCount<cSpaceInventoryItem_s0103_c3a0> ItemPtr_s0103_c3a0;
template <class T> struct Vec {
    T* mpBegin;              // +0x00
    T* mpEnd;                // +0x04
    T* mpCapacity;           // +0x08
    const char* mpName;      // +0x0c (eastl allocator name)
    void* mpPoolBegin;       // +0x10 (inline buffer address of the fixed variants)
    Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    ~Vec();
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(T* position, const T& value);
};
template <class T> T* MoveItemRange(T* first, T* last, T* out);           // 0x00ad73a0
template <class T> T* MoveItemRangeBackward(T* first, T* last, T* out);   // 0x00ad7400
class ItemVec_s0103_c3a0 : public Vec<ItemPtr_s0103_c3a0> {
public:
    void erase(ItemPtr_s0103_c3a0* first, ItemPtr_s0103_c3a0* last);
    ~ItemVec_s0103_c3a0();                          // 0x005c7f10
};
class cGonzagoTimer_s0103_c3a0 {
public:
    cGonzagoTimer_s0103_c3a0();                     // 0x00b63890
    ~cGonzagoTimer_s0103_c3a0();                    // 0x00b638b0
    uint32_t mData[8];                   // +0x00 (0x20 bytes)
};
struct InventoryAges {
    void* mpBegin;                       // +0x00
    void* mpEnd;                         // +0x04
    void* mpCapacity;                    // +0x08
    const char* mpName;                  // +0x0c
    void* mpPoolBegin;                   // +0x10
    ~InventoryAges();                    // 0x00bf1b60
};
struct KeyVec3 {
    ResourceKey_s0103_c3a0* mpBegin;                // +0x00
    ResourceKey_s0103_c3a0* mpEnd;                  // +0x04
    ResourceKey_s0103_c3a0* mpCapacity;             // +0x08
    uint32_t mAllocator;                 // +0x0c
    ResourceKey_s0103_c3a0* mpPoolBegin;            // +0x10 (mBuffer, never freed)
    uint32_t mAllocatorEx;               // +0x14
    ResourceKey_s0103_c3a0 mBuffer[3];              // +0x18
    void Init() { mpPoolBegin = mBuffer; mpEnd = mBuffer; mpBegin = mBuffer; mpCapacity = mBuffer + 3; }
    void push_back(const ResourceKey_s0103_c3a0& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) ResourceKey_s0103_c3a0(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(ResourceKey_s0103_c3a0* position, const ResourceKey_s0103_c3a0& value);      // 0x004e3e10
    void erase(ResourceKey_s0103_c3a0* first, ResourceKey_s0103_c3a0* last);                        // 0x009e0480
    void Clear() { erase(mpBegin, mpEnd); }
};
struct FloatVec3 {
    float* mpBegin;                      // +0x00
    float* mpEnd;                        // +0x04
    float* mpCapacity;                   // +0x08
    uint32_t mAllocator;                 // +0x0c
    float* mpPoolBegin;                  // +0x10 (mBuffer, never freed)
    uint32_t mAllocatorEx;               // +0x14
    float mBuffer[3];                    // +0x18
    void Init() { mpPoolBegin = mBuffer; mpEnd = mBuffer; mpBegin = mBuffer; mpCapacity = mBuffer + 3; }
    void push_back(float value)
    {
        if (mpEnd < mpCapacity)
            *mpEnd++ = value;
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(float* position, const float& value);                  // 0x00cc4160
    void Clear()
    {
        // The retail build empties the vector by copying the (empty) tail range back over the head.
        float* pEnd = mpEnd;
        float* pBegin = mpBegin;
        memcpy(pBegin, pEnd, (unsigned int)((char*)pEnd - (char*)pEnd));
        mpEnd += pBegin - pEnd;
    }
};
struct cNPCStoreBase_s0103_c3a0 {
    virtual int AddRef();                // +0x00
    virtual void Release();              // +0x04
    ~cNPCStoreBase_s0103_c3a0();
    uint32_t mnRefCount;                 // +0x04
};
class cNPCStore_s0103_c3a0 : public cNPCStoreBase_s0103_c3a0, public IRefCount_s0103_c3a0 {
public:
    uint32_t mPlanetKey;                 // +0x0c
    cGonzagoTimer_s0103_c3a0 mTimer;                // +0x10
    uint32_t mPad30;                     // +0x30
    ItemVec_s0103_c3a0 mNPCInventory;               // +0x34
    InventoryAges mInventoryAges;        // +0x48
    uint8_t mbNeedsReset;                // +0x5c
    uint8_t mPad5d[3];                   // +0x5d
    KeyVec3 mSpiceID;                    // +0x60
    FloatVec3 mSpiceCost;                // +0x9c
public:
    cNPCStore_s0103_c3a0();
    ~cNPCStore_s0103_c3a0();
};
inline int RefAddRef(cNPCStore_s0103_c3a0* p) { return static_cast<IRefCount_s0103_c3a0*>(p)->AddRef(); }
inline void RefRelease(cNPCStore_s0103_c3a0* p) { static_cast<IRefCount_s0103_c3a0*>(p)->Release(); }
typedef AutoRefCount<cNPCStore_s0103_c3a0> NPCStorePtr_s0103_c3a0;
class StoreVec {
public:
    NPCStorePtr_s0103_c3a0* mpBegin;                // +0x00
    NPCStorePtr_s0103_c3a0* mpEnd;                  // +0x04
    NPCStorePtr_s0103_c3a0* mpCapacity;             // +0x08
    const char* mpName;                  // +0x0c
    NPCStorePtr_s0103_c3a0* mpPoolBegin;            // +0x10 (inline buffer, never freed)
    StoreVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    int size() const { return (int)(mpEnd - mpBegin); }
    NPCStorePtr_s0103_c3a0& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(NPCStorePtr_s0103_c3a0* position, const NPCStorePtr_s0103_c3a0& value);
    void push_back(const NPCStorePtr_s0103_c3a0& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) NPCStorePtr_s0103_c3a0(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
namespace EA {
namespace Random {
struct RandomLinearCongruential_s0103_c3a0 {
    double RandomDouble();                       // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t n);    // 0x00a68fb0
};
}
}
extern EA::Random::RandomLinearCongruential_s0103_c3a0 gRandom_s0103_c3a0;    // 0x01601760
void RandomShuffle(ResourceKey_s0103_c3a0* first, ResourceKey_s0103_c3a0* last, void* pRandom);   // 0x0103b3e0
class cTerrainSphere_s0103_c3a0 {
public:
    double Measure();                    // 0x00c75c30
};
class cNounManager {
public:
    cTerrainSphere_s0103_c3a0* GetCurrentTerrainSphere();   // 0x00f67d90
};
cNounManager* NounManager(uint32_t id);          // 0x00b3d300
struct cPlanetRecord_s0103_c3a0 {
    int GetSpiceSituation();             // 0x00801920 (this+0x48)
};
class cPlanetRef_s0103_c3a0 {
public:
    ResourceKey_s0103_c3a0* GetSpiceKey();          // 0x00b8dad0 (this+0x198)
    void SetSpiceKey(const ResourceKey_s0103_c3a0& key);    // 0x00b8dae0
    cPlanetRecord_s0103_c3a0* GetRecord();          // 0x00b8de30
    uint32_t mPad00[(0x2c) / 4];         // +0x00
    uint32_t mFlags;                     // +0x2c (0x3000 = planet has a trade post?)
};
class cEmpire_s0103_c3a0 {
public:
    bool IsCommodityKnown();             // 0x00fe4180
};
class cGameData_s0103_c3a0 {
public:
    cEmpire_s0103_c3a0* GetPlayerEmpire();          // 0x00bfc5f0
};
cGameData_s0103_c3a0* SpaceGameGet(uint32_t planetKey);   // 0x01002bd0
typedef bool (__cdecl *ItemCompare_s0103_c3a0)(const ItemPtr_s0103_c3a0&, const ItemPtr_s0103_c3a0&);
struct RBNode_s0103_c3a0 {
    RBNode_s0103_c3a0* mpNodeRight;                 // +0x00
    RBNode_s0103_c3a0* mpNodeLeft;                  // +0x04
    RBNode_s0103_c3a0* mpNodeParent;                // +0x08
    char mColor;                         // +0x0c
    char mPad0d[3];                      // +0x0d
    ResourceKey_s0103_c3a0 mValue;                  // +0x10
};
struct RBInsertResult_s0103_c3a0 {
    RBNode_s0103_c3a0* mpNode;                      // +0x00
    bool mbInserted;                     // +0x04
};
RBNode_s0103_c3a0* RBTreeIncrement(RBNode_s0103_c3a0* pNode);                     // 0x00921580
class RBTree_s0103_c3a0 {
public:
    uint8_t mCompare;                    // +0x00 (eastl::less, empty)
    uint8_t mPad01[3];
    RBNode_s0103_c3a0* mpAnchorRight;               // +0x04 (rightmost node / &mAnchor when empty)
    RBNode_s0103_c3a0* mpAnchorLeft;                // +0x08 (leftmost node / &mAnchor when empty)
    RBNode_s0103_c3a0* mpAnchorParent;              // +0x0c (root)
    char mAnchorColor;                   // +0x10
    uint8_t mPad11[3];
    uint32_t mnSize;                     // +0x14
    void* mAllocator;                    // +0x18
public:
    bool Less(const ResourceKey_s0103_c3a0& a, const ResourceKey_s0103_c3a0& b) { return a < b; }
    void DoInsertValueImpl(RBInsertResult_s0103_c3a0* pResult, RBNode_s0103_c3a0* pParent, const ResourceKey_s0103_c3a0& value, bool bForceToLeft);   // 0x0103b590
    void DoInsertUnique(RBInsertResult_s0103_c3a0* pResult, const ResourceKey_s0103_c3a0& value, bool bInsertUnique);                       // 0x0103bc40
    RBInsertResult_s0103_c3a0* insert(RBInsertResult_s0103_c3a0* pResult, RBNode_s0103_c3a0* position, const ResourceKey_s0103_c3a0& value, bool bUnused);
};
void* MedianOfThree(ItemPtr_s0103_c3a0* first, ItemPtr_s0103_c3a0* mid, ItemPtr_s0103_c3a0* last, ItemCompare_s0103_c3a0 cmp, ItemCompare_s0103_c3a0 cmp2);   // 0x01021180
ItemPtr_s0103_c3a0* PartitionRange(ItemPtr_s0103_c3a0* first, ItemPtr_s0103_c3a0* last);                        // 0x0103bd10
void UnguardedInsertionSort(ItemPtr_s0103_c3a0* first, ItemPtr_s0103_c3a0* last, ItemPtr_s0103_c3a0* end, ItemCompare_s0103_c3a0 cmp);  // 0x0103bd90
void QuickSortImpl(ItemPtr_s0103_c3a0* first, ItemPtr_s0103_c3a0* last, int depth, ItemCompare_s0103_c3a0 cmp);  // 0x0103c800
namespace SP {
class cSPSpaceTrading_s0103_c3a0 {
public:
    uint32_t mPad00[0x20 / 4];           // +0x00
    Vec<ResourceKey_s0103_c3a0> mFoodCommodities;   // +0x20
    Vec<ResourceKey_s0103_c3a0> mCommodities;       // +0x34
    StoreVec mNPCStore;                  // +0x48
    uint32_t mPad5c[(0x9c - 0x5c) / 4];  // +0x5c (rare-map state)
    int mLastNPCStoreIndex;              // +0x9c
    uint32_t mPad0a0[(0xe4 - 0xa0) / 4]; // +0xa0
    Vec<ResourceKey_s0103_c3a0> mRareRequests;      // +0xe4

    void BuildSpiceCommodities();
    void RefreshNPCSpiceCosts(cPlanetRef_s0103_c3a0* planet);  // 0x0103cd00 (SP::cSPSpaceTrading::RefreshNPCSpiceCosts)
    void ChooseNPCSpices(cPlanetRef_s0103_c3a0* planet, bool bForce);
    void ConsiderBuyingRare(uint32_t planetKey, Vec<ResourceKey_s0103_c3a0>* pOut);
    void ConsiderRareGroupRequest(uint32_t planetKey);
};
}
using SP::cSPSpaceTrading_s0103_c3a0;
void* operator new(size_t n, const char* pName, int nFlags, int nAlignment, const void* pAllocator, int nLine);   // 0x00f473a0
struct KeyVec {
    uint32_t mData[5];                   // +0x00
    KeyVec& operator=(const KeyVec& other);   // 0x006609a0
};
struct KeyVecEntry {
    uint32_t mData[4];                   // +0x00
    KeyVec mKeys;                        // +0x10
};
// ---- items of slice s0103c3a0 end

// ---- items of slice s0103dee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Property_s0103_dee0 {
    virtual void v00();            // +0x00
    virtual void Release();        // +0x04
    virtual void v02();            // +0x08
    uint8_t  mPad0c[6];            // +0x0c
    uint16_t mValueType;           // +0x12
    bool*    GetBool();            // 0x0041e920
    int*     GetInt();             // 0x0041e990
    uint32_t* GetUInt();           // 0x0041ea00
    float*   GetFloat();           // 0x0041ea70
};
struct PropertyManager_s0103_dee0 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
    virtual bool HasProperty(uint32_t prop);                                   // +0x1c
    virtual void v08();                                                        // +0x20
    virtual bool GetPropertyByKey(uint32_t prop, Property_s0103_dee0** ppOut);            // +0x24
    virtual void v0a();                                                        // +0x28
    virtual bool GetProperty(uint32_t key, uint32_t prop, Property_s0103_dee0** ppOut);   // +0x2c
};
struct cSpaceItem {
    virtual void v00();            // +0x00
    virtual void AddRef();         // +0x04
    virtual void Release();        // +0x08
    virtual void v03();            // +0x0c
    virtual void v04();            // +0x10
    virtual void v05();            // +0x14
    virtual int* GetKey();         // +0x18
    uint8_t  mPad04[0x0c];         // +0x04
    uint32_t mPoliticalId;         // +0x10
    uint32_t mItemCount;           // +0x14
};
struct ItemRef {
    cSpaceItem* mpObject;          // +0x00
    ItemRef() : mpObject(0) {}
    ItemRef(cSpaceItem* p) : mpObject(p) {}
    operator cSpaceItem*() const { return mpObject; }
};
struct ItemVec_s0103_dee0 {
    ItemRef* mpBegin;              // +0x00
    ItemRef* mpEnd;                // +0x04
    ItemRef* mpCapacity;           // +0x08
    void DoInsert(ItemRef* pWhere, const ItemRef* pValue);        // 0x00f14270
    void push_back(cSpaceItem* pObject) {
        ItemRef* pSlot = mpEnd;
        if (pSlot < mpCapacity) {
            mpEnd = pSlot + 1;
            if (pSlot) {
                pSlot->mpObject = pObject;
                if (pObject)
                    pObject->AddRef();
            }
        } else {
            ItemRef value(pObject);
            DoInsert(pSlot, &value);
        }
    }
};
struct cSPTimer {
    void Restart();                // 0x00bc3130
    unsigned long long GetElapsedTime();   // 0x00bc2e50
};
struct ItemStore {
    uint8_t  mPad00[0x2c];         // +0x00
    cSPTimer mTimer;               // +0x2c
    uint32_t mPad30;               // +0x30
    ItemVec_s0103_dee0  mInventory;           // +0x34
    uint32_t mPad40[2];            // +0x40
    uint32_t mAgesHandle;          // +0x48
    uint32_t mPad4c;               // +0x4c
};
struct cInventory {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
    virtual void v28();
    virtual bool HasItem(const char* pName);       // +0x74
};
struct cGameNounManager {
    void* GetAvatar();                             // 0x00b1fdb0
};
struct cSPSimulatorSpaceGame {
    cInventory* GetPlayerInventory();              // 0x00a1ad60
};
struct ToolInfo {
    uint8_t  mPad00[0x28];         // +0x00
    int32_t  mCount;               // +0x28
    uint8_t  mPad2c[0x2c];         // +0x2c
    int32_t  mSpiceIndex;          // +0x58
};
struct cSPSpaceTrading_s0103_dee0 {
    uint8_t        mPad00[0x48];       // +0x00
    ItemStore**    mppStores;          // +0x48
    uint32_t       mPad4c[0x0a];       // +0x4c
    ItemVec_s0103_dee0        mSelling;           // +0x74
    uint32_t       mPad80[0x07];       // +0x80
    int32_t        mStoreIndex;        // +0x9c
    uint32_t       mPadA0[0x40];       // +0xa0
    ToolInfo*      mpSelectedToolInfo; // +0x1a0

    void CreateCommodityFromID(cSpaceItem** ppOut, cSpaceItem** ppSecond,
                               Property_s0103_dee0* pProp, float fValue);      // 0x0103a480
    bool ConsiderSellingTool(int iObjectID, ToolInfo* pInfo, uint32_t iKey,
                             int iMode, void* pExtra);
    bool ConsiderSellingSpice(int iObject, int iKeyA, int iKeyB, int iKeyC);
};
struct SpaceGame_s0103_dee0 {
    uint8_t mPad00[0xc4];          // +0x00
    uint8_t mFlags;                // +0xc4
};
struct RandomLinearCongruential_s0103_dee0 {
    double RandomDoubleUniform();  // 0x009360d0 (RandomLinearCongruential::RandomDoubleUniform)
};
cSPSimulatorSpaceGame* SP_SpaceGameGet();                                  // 0x01002bd0
SpaceGame_s0103_dee0* SpaceGameGet_s0103_dee0();                                                 // 0x01002bd0
int*   FUN_00b8dad0(cSPSpaceTrading_s0103_dee0* pThis);                               // 0x00b8dad0
Property_s0103_dee0* FUN_00c705c0(int iObject, int iFlag);                            // 0x00c705c0
cGameNounManager* FUN_00b8de30(cSPSpaceTrading_s0103_dee0* pThis);                     // 0x00b8de30
int    SP_GetPlayerEmpireID();                                             // 0x01021090
void*  SP_GetPlayerEmpire();                                               // 0x00c32c10
PropertyManager_s0103_dee0* GetPropertyManager();                                     // 0x0067de30
void   SP_GetPropertyT(Property_s0103_dee0* pProp, uint32_t prop, void* pOut);        // 0x0040cf10
void   FUN_0103de00(void* pAges);                                          // 0x0103de00
float  FUN_01005c60(int n);                                                // 0x01005c60
bool   FUN_00c322c0(int n);                                                // 0x00c322c0
float  FUN_00c75c30(uint32_t key);                                         // 0x00c75c30
void   FUN_00c308d0(void* pEmpire);                                        // 0x00c308d0
void   FUN_00c31bc0(int iValue);                                           // 0x00c31bc0
void   FUN_00b3d2a0(void* pAvatar);                                        // 0x00b3d2a0
int    FUN_00ba9370(void* pAvatar);                                        // 0x00ba9370
void   GetPropertyAsKey(Property_s0103_dee0* pProp, uint32_t prop, uint32_t* pOut);   // 0x0040cf50
bool   GetPropertyAsKeyInstance(Property_s0103_dee0* pProp, uint32_t prop, int* pOut); // 0x006a12a0
float* GetPropertyAsFloat(Property_s0103_dee0* pProp);                                // 0x0040cfb0
int*   GetPropertyAsInt(Property_s0103_dee0* pProp);                                  // 0x0040cfa0
cGameNounManager* GetNounManager();                                        // 0x0067de90
void*  NounManager_s0103_dee0(uint32_t key);                                          // 0x00b5b800
bool   AreBasicToolConditionsMet(Property_s0103_dee0* pProp, int bFlag);              // 0x0103c000
int    FUN_011e0810();                                                     // 0x011e0810
RandomLinearCongruential_s0103_dee0 sMathRandom;                                      // 0x016aca40
const char kItemInterplanetaryDrive[] = "k_interplanetarydrive";
static const uint32_t s_spiceChanceKeys[] = {
    0x0567ddd0, 0x0567ddd1, 0x0567ddd2, 0x0567ddd3, 0x0567ddd4,
    0x0567ddd5, 0x0567ddd6, 0x0567ddd7, 0x0567ddd8, 0x05f89ff4,
    0x05f89ff5, 0x05f89ff6, 0x05f89ff7, 0x05f89ff8, 0x05f89ff9,
    0x05f89ffa, 0x05f89ffb, 0x05f89ffc, 0x05f89ffd
};
static const uint32_t s_spicePriceKeys[] = {
    0x05b80b32, 0x05b80b33, 0x05b80b34, 0x05b80b35, 0x05b80b36,
    0x05b80b37, 0x05b80b38, 0x05b80b39, 0x05b80b3a, 0x05b80b3c,
    0x05b80b3b, 0x05b80b3c, 0x05b80b3d, 0x05b80b3d, 0x05b80b3c,
    0x05b80b3b, 0x05b80b3d, 0x05b80b3b, 0x05b80b3c
};
// ---- items of slice s0103dee0 end

// ---- items of slice s0103eff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Property_s0103_eff0 {
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
struct PropertyList_s0103_eff0 {
    VSLOT(0)
    virtual int Release();                                                   // +0x04
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual bool HasProperty(uint32_t id);                                   // +0x1c
    VSLOT(8)
    virtual bool GetProperty(uint32_t id, Property_s0103_eff0*& out);                   // +0x24
    virtual Property_s0103_eff0* GetPropertyObject(uint32_t id);                        // +0x28
};
void GetPropertyAsKey(PropertyList_s0103_eff0* list, uint32_t id, ResourceKey* out);    // 0x006a1250
void GetPropertyAsKeyInstance(PropertyList_s0103_eff0* list, uint32_t id, uint32_t* out);  // 0x006a12a0
struct cObject {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* Cast(uint32_t typeID);                                     // +0x0c
};
template <class T> inline T* object_cast(cObject* p) { return p ? (T*)p->Cast(T::TYPE) : 0; }
struct cSpaceInventoryItem_s0103_eff0 {
    enum { TYPE = 0x707459dd };
    VSLOT(0)
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
    VSLOT(3)
    virtual uint32_t GetType();                                              // +0x10
    virtual void SetItemID(const ResourceKey& key);                          // +0x14
    virtual const ResourceKey& GetItemID();                                  // +0x18
    virtual uint32_t GetItemInstanceID();                                    // +0x1c

    cSpaceInventoryItem_s0103_eff0();                                                   // 0x00c87660
    void SetPropertyList(PropertyList_s0103_eff0* list);                                // 0x00c877f0

    uint32_t mnRefCount;                                                     // +0x04
    uint32_t pad08[2];
    int mItemCount;                                                          // +0x10
    uint32_t mItemType;                                                      // +0x14
    uint32_t mItemCost;                                                      // +0x18
    uint32_t pad1c[5];
    PropertyList_s0103_eff0* mpPropList;                                                // +0x30
    uint32_t pad34[(0x7c - 0x34) / 4];
    int mnToolCount;                                                         // +0x7c (tools only)

    int GetUnitValue_006c0200();
    bool IsStackable_0104cbc0();
};
struct cSpaceCommodityItem {
    VSLOT(0)
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
    VSLOT(3)
    virtual uint32_t GetType();                                              // +0x10
    virtual void SetItemID(const ResourceKey& key);                          // +0x14
    virtual const ResourceKey& GetItemID();                                  // +0x18
    virtual uint32_t GetItemInstanceID();                                    // +0x1c

    cSpaceCommodityItem();                                                   // 0x00c87660
    void SetPropertyList(PropertyList_s0103_eff0* list);                                // 0x00c877f0

    uint32_t mnRefCount;                                                     // +0x04
    uint32_t pad08[2];
    int mItemCount;                                                          // +0x10
    uint32_t mItemType;                                                      // +0x14
    uint32_t mItemCost;                                                      // +0x18
    uint32_t pad1c[5];
    PropertyList_s0103_eff0* mpPropList;                                                // +0x30
    uint32_t pad34[(0x7c - 0x34) / 4];
};
struct RareNode_s0103_eff0 {
    uint32_t pad00[4];
    ResourceKey mKey;                                                        // +0x10
    int mValue;                                                              // +0x1c
};
struct RareIterator {
    RareNode_s0103_eff0* mpNode;
    __forceinline RareIterator() {}
    __forceinline RareIterator(const RareIterator& o) : mpNode(o.mpNode) {}
};
struct RareMap {
    uint32_t pad00[7];                                                       // 0x1c bytes
    RareIterator find(const ResourceKey* key);                               // 0x00a21dc0 (sret, ret 8)
    int* insert(const ResourceKey* key);                                     // 0x0103de50 (ret 4)
    RareNode_s0103_eff0* end() { return (RareNode_s0103_eff0*)((char*)this + 4); }
};
struct IPropertyManager {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual void v2c(uint32_t instance, uint32_t propertyID, PropertyList_s0103_eff0** out);  // +0x2c
};
IPropertyManager* PropertyManager_s0103_eff0();                                         // 0x0067de30
bool IsItemARare(uint32_t* pItemID);                                         // 0x0103a3c0
struct cEventLog {
    void PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);  // 0x00dd8640 (ret 0x18)
};
cEventLog* EventLog();                                                       // 0x00b3d3e0
struct Translator {
    uint32_t pad00[5];
    cSpaceInventoryItem_s0103_eff0* mpItem14;                                           // +0x14
};
extern Translator* gpTranslator;                                             // 0x016e0d08
template <class T> struct intrusive_ptr_s0103_eff0 {
    T* mpObject;
    intrusive_ptr_s0103_eff0() : mpObject(0) {}
    intrusive_ptr_s0103_eff0(const intrusive_ptr_s0103_eff0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr_s0103_eff0() { if (mpObject) mpObject->Release(); }
    intrusive_ptr_s0103_eff0& operator=(T* p)
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
typedef intrusive_ptr_s0103_eff0<cSpaceInventoryItem_s0103_eff0> cSpaceInventoryItemPtr_s0103_eff0;
template <class T> struct vector_s0103_eff0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    T& back() { return *(mpEnd - 1); }
    void DoInsertValue(T* position, const T& value);  // 0x00621fc0 (vector::DoInsertValue)
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (vector::DoInsertValue)
    }
    void push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());  // 0x00621fc0 (vector::DoInsertValue)
    }
};
template <class T> struct uvector_s0103_eff0 {   // size() as size_type
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
};
struct cSPTimer_s0103_eff0 { void Restart(); };                                         // 0x00bc3130
struct cGonzagoTimer_s0103_eff0 {
    cSPTimer_s0103_eff0 mTimer;
    uint32_t pad[7];
    cGonzagoTimer_s0103_eff0();                                                         // 0x00b63890
    ~cGonzagoTimer_s0103_eff0();                                                        // 0x00b638b0
};
struct cNPCStore_s0103_eff0 {
    uint32_t pad00[3];
    uint32_t mPlanetKey;                                                     // +0x0c
    uint32_t pad10[8];
    int mSpiceBought;                                                        // +0x30
    vector_s0103_eff0<cSpaceInventoryItemPtr_s0103_eff0> mNPCInventory;                            // +0x34
    uint32_t pad44;
    vector_s0103_eff0<cGonzagoTimer_s0103_eff0> mNPCInventoryAges;                                 // +0x48
};
struct cTradeEntryBase { virtual void _e0(); uint32_t pad[2]; };
struct cTradeEntry : cTradeEntryBase, cObject {};                           // cObject at +0x0c
struct cSpaceInventory_s0103_eff0 {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20)
    VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24)
    virtual int IndexOf(uint32_t type, const ResourceKey& id);               // +0x64
    VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30)
    virtual bool TakeItems(int index, cSpaceInventoryItemPtr_s0103_eff0& dst, int count);  // +0x7c
    virtual void AddItem(cSpaceInventoryItem_s0103_eff0* item, int a, bool b);          // +0x80
};
struct cPlanetRecord_s0103_eff0 {
    virtual int AddRef();
    virtual int Release();
};
struct cEmpire_s0103_eff0 {
    uint32_t pad[0x84 / 4];
    uint32_t mPoliticalID;
    void AddTradeValue_00c31a00(int v);
};
struct cStarManager_s0103_eff0 {
    cPlanetRecord_s0103_eff0* GetPlanetRecord_00ba6dc0(uint32_t key);
    cEmpire_s0103_eff0* GetEmpireByID(uint32_t id);                                     // 0x00ba9370
};
cStarManager_s0103_eff0* StarManager_s0103_eff0();                                                 // 0x00b3d2a0
struct cCommRecord { uint32_t GetCommContext(); };                           // 0x00ce6950
cCommRecord* GetActivePlanetRecord();                                        // 0x010212a0
cEmpire_s0103_eff0* GetPlayerEmpire_s0103_eff0();                                                  // 0x01021300
struct cAvatarSource { uint32_t GetAvatarEmpireID_00b1fdb0(); };
cAvatarSource* GetAvatarSource_01021240();
struct cToolManager { void CreateToolFromToolID(const ResourceKey& id, cSpaceInventoryItemPtr_s0103_eff0& dst); };  // 0x0104e340
cToolManager* ToolManager();                                                 // 0x00b3d390
struct cStats { void AddStat_00fe5430(int stat, int value); };
struct cBadgeTarget { uint32_t pad[7]; uint32_t mID; uint32_t mKind; };
struct cBadgeUI { uint32_t pad[3]; cBadgeTarget* mpTarget; void SetMode_007eb820(int mode); };
struct cSpaceGame_s0103_eff0 {
    cSpaceInventory_s0103_eff0* GetPlayerInventory();                                   // 0x00a1ad60
    cStats* GetPlayerStats();                                                // 0x00bfc5f0
    cBadgeUI* GetUI_01005180(int which);
};
cSpaceGame_s0103_eff0* SpaceGameGet_s0103_eff0();                                                  // 0x01002bd0
struct cRelationshipManager_s0103_eff0 { float RecordEvent(uint32_t a, uint32_t b, uint32_t eventID, float scale); };  // 0x00d06240
cRelationshipManager_s0103_eff0* RelationshipManager();                                 // 0x00b3d2c0
struct cPlayerUFO { void CalcMaxTravelDistance(); };                         // 0x00ffc6d0
cPlayerUFO* GetUFOSimulator();                                               // 0x00ffbe50
void ShowSpiceEvent_00c704a0(cPlanetRecord_s0103_eff0* planet, ResourceKey id, float amount);
void ShowEventLog_00e39ab0(uint32_t id, cEmpire_s0103_eff0* empire, ResourceKey* a, ResourceKey* b, uint32_t context,
                           int count, ResourceKey* c, ResourceKey* d);
struct IMessageServer_s0103_eff0 {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4)
    virtual void SendMSG(uint32_t id, void* msg, void* target);              // +0x14
};
IMessageServer_s0103_eff0* MessageServer();                                             // 0x0067dcc0
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
struct RareMessage : MessageBase1 {
    struct Slot { IRefSlot* p; uint32_t pad; } mSlots[5];
    uint32_t mMessageID;                                                     // +0x30
    uint32_t pad34;
    uint32_t mRefMask;                                                       // +0x38
    RareMessage(uint32_t id) { mMessageID = id; mRefMask = 0; }
    ~RareMessage();                                                          // 0x00421cf0
    void SetValue(int i, uint32_t v) { *(uint32_t*)&mSlots[i].p = v; }
};
namespace SP {
class cSPSpaceTrading_s0103_eff0 {
public:
    struct RareGroup {
        ResourceKey mGroupKey;
        uint32_t mGroupID;
        uvector_s0103_eff0<ResourceKey> mRares;                                         // +0x10
        uint32_t pad20;
    };

    uint32_t pad00[0x48 / 4];
    vector_s0103_eff0<intrusive_ptr_s0103_eff0<cNPCStore_s0103_eff0> > mNPCStore;                             // +0x48
    uint32_t pad58[(0x74 - 0x58) / 4];
    vector_s0103_eff0<cSpaceInventoryItemPtr_s0103_eff0> field_74;                                 // +0x74
    uint32_t pad84;
    vector_s0103_eff0<cTradeEntry*> field_88;                                           // +0x88
    uint32_t pad98;
    int mLastNPCStoreIndex;                                                  // +0x9c
    RareMap mRareMap;                                                        // +0xa0
    uvector_s0103_eff0<RareGroup> mRareGroups;                                          // +0xbc

    int GetTradeBalance_01039ca0();
    void MarkRareFound_01039690(ResourceKey* key);
    void CreateCommodityFromID(cSpaceInventoryItemPtr_s0103_eff0& dst, const ResourceKey& id, int count, float cost);  // 0x0103a480
    cSpaceInventoryItem_s0103_eff0* FindStoreItem_01039c00(cSpaceInventoryItem_s0103_eff0* item);
    uint32_t FindRareGroup_0103a760(uint32_t groupID);
    void FUN_0103fba0(const ResourceKey* key, int value);
    void AddCommodityToInventory(const ResourceKey* id, int count);  // 0x0103fc10 (SP::cSPSpaceTrading::AddCommodityToInventory)
    void PerformTrade();  // 0x0103eff0 (SP::cSPSpaceTrading::PerformTrade)
};
}
using SP::cSPSpaceTrading_s0103_eff0;
template <> struct intrusive_ptr_s0103_eff0<cNPCStore_s0103_eff0> {
    cNPCStore_s0103_eff0* mpObject;
    cNPCStore_s0103_eff0* operator->() const { return mpObject; }
};
// ---- items of slice s0103eff0 end

// @ 0x01039690
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

// @ 0x010397b0
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

// @ 0x01039ab0
cSpaceInventoryItem* SP::cSPSpaceTrading::GetUserItem(uint32_t index)
{
    if (index >= (uint32_t)mUserItems.size())
        return 0;
    return mUserItems.mpBegin[index].get();
}

// @ 0x01039ad0
cSpaceInventoryItem* SP::cSPSpaceTrading::GetNPCItem(uint32_t index)
{
    if (index >= (uint32_t)mNPCItems.size())
        return 0;
    return mNPCItems.mpBegin[index].get();
}

// @ 0x01039b00
void SP::cSPSpaceTrading::MarkNPCStores(bool bAll)
{
    int count = mNPCStore.size();
    for (int i = 0; i < count; ++i) {
        cPlanetRecord_s0103_93a0* pPlanet = StarManager()->GetPlanetRecord(mNPCStore.mpBegin[i]->mPlanetKey);
        if (bAll || (pPlanet != 0 &&
                     pPlanet->GetOwnerEmpire()->GetPoliticalID() != SP::GetPlayerEmpireID()))
            mNPCStore.mpBegin[i]->mMarked = true;
    }
}

// @ 0x01039b70
int SP::cSPSpaceTrading::GetItemValue(cSpaceInventoryItem* pItem)
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

// @ 0x01039ca0
int SP::cSPSpaceTrading::GetTradeBalance()
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

// @ 0x01039ff0
int SP::cSPSpaceTrading::GetRareKeyCount(uint32_t groupIndex)
{
    uvector<ResourceKey>* pRares = &mRareGroups.mpBegin[groupIndex].mRares;
    return (int)(pRares->mpEnd - pRares->mpBegin);
}

// @ 0x0103a0e0
void eastl_insertion_sort(cSpaceInventoryItemPtr* pBegin, cSpaceInventoryItemPtr* pEnd, ItemPtrCompare pCompare)
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

// @ 0x0103a330
void eastl_iter_swap(cSpaceInventoryItemPtr& a, cSpaceInventoryItemPtr& b)
{
    cSpaceInventoryItemPtr temp = a;
    a = b;
    b = temp;
}

// @ 0x0103a480
void __stdcall FUN_0103a480(void** out, int* id, int count, float cost)
{
    Commodity* item = (Commodity*)operator_new(0x7c, "Simulator/cSpaceInventoryItem", 0, 0, 0, 0);
    Commodity* inst = item ? item->ctor_00c87660() : 0;
    IUnk* local = 0;
    PropertyMgr* pm = (PropertyMgr*)PropertyManager();
    if (local) {
        IUnk* old = local; local = 0; old->Release();
    }
    pm->Unregister(*id, 0x34d97fa, &local);
    ((V14*)inst)->v14(id);
    inst->mType = 4;
    inst->mItemCount = count;
    inst->mCost = (int)(cost + 0.5);   // rounds like the original's x87 fistp
    inst->SetPropertyList_00c877f0(local);
    ((VItemRef*)inst)->AddRef();
    *out = inst;
    if (local) local->Release();
}

// @ 0x0103a540
uint T540::scan(void* p)
{
    int n = ((int)mEnd - (int)mBegin) / 0xc;
    uint result = 0;
    IUnk* local = 0;
    int idx = 0;
    if (n > 0) {
        int count = n;
        do {
            void* e = (void*)((char*)mBegin + idx);
            void* q = (void*)((V18*)p)->v18();
            if (*(int*)e == *(int*)q) {
                PropertyMgr* pm = (PropertyMgr*)PropertyManager();
                if (local) { IUnk* old = local; local = 0; old->Release(); }
                pm->Unregister(*(int*)e, 0x34d97fa, &local);
                if (local) {
                    Prop* pr;
                    if (((VProp24*)local)->v24(0x58cbb75, (void**)&pr) && pr->type == 10) {
                        uint* base = (uint*)pr;
                        if ((base[4] & 0x30) != 0) base = (uint*)*base;
                        result = *base | 0xff000000;
                    }
                }
            }
            idx += 0xc;
            --count;
        } while (count != 0);
        if (local) local->Release();
    }
    return result;
}

// @ 0x0103a630
bool A630::f_0103a630(void* item, int x, int y, int z)
{
    if (item == 0) return false;
    void* pi = (void*)((HashObj*)(*(void**)((char*)item + 0xc)))->v3(0x707459f0);
    if (pi == 0) return false;
    Vec3i tmp;
    Vec3i key = { 0, 0, 0 };
    ((HPosition*)pi)->get(&tmp);
    key.x = tmp.x;
    key.y = tmp.y;
    key.z = tmp.z;
    IUnk* local = 0;
    if (key.x != g_16df56c || key.y != g_16df570 || key.z != g_16df574) {
        if (((TToolMgr*)FUN_00b3d390())->createTool(&key, (void**)&local)) {
            bool r = f_0103a630(item, x, y, z);
            if (local) local->Release();
            return r;
        }
    }
    if (local) local->Release();
    Vec3i* v = ((V6*)pi)->get();
    return v->x == x && v->y == y && v->z == z;
}

// @ 0x0103a760
uint T760::find(int id)
{
    uint i = 0;
    if ((uint)(((int)mEnd - (int)mBegin) / 0x24) == 0) return i;
    int* p = (int*)((char*)mBegin + 0xc);
    do {
        if (*p == id) return i;
        ++i;
        p += 9;
    } while (i < (uint)(((int)mEnd - (int)mBegin) / 0x24));
    return i;
}

// @ 0x0103a7d0
int SPTrading::handleMessage(int msg, void* arg)
{
    if (msg < 0x4445d43 || msg > 0x4445d44) return 0;
    int a = *(int*)((char*)arg + 0x10);
    int b = *(int*)((char*)arg + 8);
    int player = (int)GetPlayerEmpire();
    int target;
    if (b == player) target = a;
    else if (a == player) target = b;
    else return 0;
    int count = (int)(mEnd - mBegin);
    if (count <= 0) return 0;
    int i = 0;
    do {
        void* entry = mBegin[i];
        int id = *(int*)((char*)entry + 0xc);
        void* noun = ((B3Obj*)StarManager_s0103_a480())->get_ba6dc0(id);
        void* keep = 0;
        if (noun) {
            ((MsgRef*)noun)->AddRef();
            keep = noun;
        }
        void* av = ((NounObj*)keep)->f_b8de30();
        void* avatar = ((AvObj*)av)->f_b1fdb0();
        int emp = ((B3Obj*)StarManager_s0103_a480())->get_ba9370(avatar);
        if (target == emp) {
            int n = (int)(mEnd - mBegin);
            if (i != n - 1) {
                void* last = mBegin[n - 1];
                void* cur = mBegin[i];
                if (last != cur) {
                    if (last) ((MsgRef*)((char*)last + 8))->AddRef();
                    mBegin[i] = last;
                    if (cur) ((MsgRef*)((char*)cur + 8))->Release();
                }
            }
            mEnd = mEnd - 1;
            void* popped = *mEnd;
            if (popped) ((MsgRef*)((char*)popped + 8))->Release();
        } else {
            ++i;
        }
        if (keep) ((MsgRef*)keep)->Release();
        count = (int)(mEnd - mBegin);
    } while (i < count);
    return 0;
}

// @ 0x0103a930
bool FUN_0103a930(int* list)
{
    int n = (list[1] - *list) / 0xc;
    IUnk* local = 0;
    int idx = 0;
    if (n > 0) {
        int i = 0;
        int count = n;
        do {
            PropertyMgr* pm = (PropertyMgr*)PropertyManager();
            if (local) { IUnk* old = local; local = 0; old->Release(); }
            pm->Unregister(*(int*)(*list + idx), 0x34d97fa, &local);
            int key[3];
            key[0] = key[1] = key[2] = 0;
            GetPropertyAsKey(local, 0x34f1a4f, key);
            if (key[0] == 0x7ecbe6f5) {
                if (local) local->Release();
                return true;
            }
            ++i;
            idx += 0xc;
        } while (i < count);
        if (local) local->Release();
    }
    return false;
}

// @ 0x0103aa00
void Trading34::addRareCommodity(void* p2)
{
    int count = (int)(((char*)mEnd - (char*)mBegin) / 0xc);
    if (GetCurrentGameMode() != 0x1654c05) return;
    if (*(int*)((char*)p2 + 0x28) <= 1) return;
    if (((RareNoun*)p2)->f_b8d970()) return;
    if (GetPlayerEmpire() == 0) return;
    int e1 = ((Empire*)GetPlayerEmpire())->f_c30c60();
    if ((int)((RareNoun*)p2)->f_b8de30() == e1) return;
    if (!FUN_0103a930((int*)((char*)this + 0x34))) return;
    IUnk* local = 0;
    bool found = false;
    do {
        int idx = 0;
        int left = count;
        while (left > 0) {
            if (local) { IUnk* old = local; local = 0; old->Release(); }
            PropertyMgr* pm = (PropertyMgr*)PropertyManager();
            pm->Unregister(*(int*)((char*)mBegin + idx), 0x34d97fa, &local);
            int key[3] = { 0, 0, 0 };
            GetPropertyAsKey(local, 0x34f1a4f, key);
            if (key[0] == 0x7ecbe6f5) {
                float chance = 0.0f;
                void* pr = 0;
                if (local && ((VProp24*)local)->v24(0x34f1a4e, &pr) &&
                    *(short*)((char*)pr + 0x12) == 0xd) {
                    float* f = ((Prop*)pr)->GetFloat();
                    chance = *f;
                }
                double roll = ((RngObj*)&g_rand)->nextDouble();
                if (roll < (double)chance) {
                    float amt = 0.0f;
                    GetFloatProperty(local, 0x34f1a49, &amt);
                    int n = (int)(amt + (amt >= 0.0f ? 0.5f : -0.5f));
                    FUN_00c731a0((int)p2, 4, *(int*)((char*)mBegin + idx), n, 0,
                                  *(int*)&g_16df53c, *(int*)&g_16df540, *(int*)&g_16df544, 1);
                    found = true;
                }
            }
            idx += 0xc;
            --left;
        }
    } while (!found);
    if (local) local->Release();
}

// @ 0x0103ac40
void* TAC40::find(int* key)
{
    void* node;
    void* p = *((RBTreeT*)((char*)this + 0xa0))->find((void**)&node, key);
    return (p != (void*)((char*)this + 0xa4)) ? *(void**)((char*)p + 0x1c) : 0;
}

// @ 0x0103ac70
bool TSx::f_ac70(int group, bool needInventory)
{
    uint n = (uint)(((int)mGroups[group].mEnd - (int)mGroups[group].mBegin) / 0xc);
    for (uint i = 0; i < n; ++i) {
        int* arr = mGroups[group].mBegin + i * 3;
        int key[3];
        key[0] = arr[0];
        key[1] = arr[1];
        key[2] = arr[2];
        void* node;
        void* p = *mRare.find((void**)&node, key);
        if (p == mRare.mAnchor) return false;
        if (((RareNode*)p)->mCount != 1) return false;
        if (needInventory) {
            void* inv = ((SpaceGame*)SpaceGameGet_s0103_a480())->get_00a1ad60();
            if (!((V70*)inv)->v70(4, key)) return false;
        }
    }
    return true;
}

// @ 0x0103ad50
void FUN_0103ad50(void* self, int* p2, int a3, int a4)
{
    if ((*(int*)((char*)self + 0x160) - *(int*)((char*)self + 0x15c)) == 0) return;
    ItemVecB* bp = ((ItemCtr*)self)->getItems(0);
    int cnt = (int)(bp->mEnd - bp->mBegin);
    if (cnt == 0) return;
    uint matches = 0;
    for (int* q = *(int**)((char*)self + 0x134); q != *(int**)((char*)self + 0x138); q += 3) {
        if (q[0] == p2[0]) ++matches;
    }
    if (matches >= (uint)(cnt * 2)) return;
    Vec3f pos;
    void* placed = 0;
    if (a4 == 0) {
        uint k = ((RngAd*)&g_rand)->nextInt(cnt);
        Vec3f* v = ((WorldItemAd*)bp->mBegin[k])->getPos();
        pos.x = v->x;
        pos.y = v->y;
        pos.z = v->z;
    } else {
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;
    }
    void* item = 0;
    FUN_0103a480(&item, p2, a3, 0.0f);
    void* id = ((VItem3*)item)->v18(*(int*)((char*)item + 0x10), 1, pos);
    FUN_00c731a0((int)self, 4, (int)id, 0);
    if (a4 != 0) {
        void* mgr = NounManager();
        void* noun = mgr ? ((NounMgrAd*)mgr)->createNoun(0x2dd8c42) : 0;
        if (noun) {
            void* art = ((NounAd*)noun)->getArtifact(0x2dd8c33);
            if (art) {
                ArtifactAd* a = (ArtifactAd*)art;
                Vec3f apos;
                a->mPos.get_38(&apos);
                int angle = a->mPos.get_2c();
                ModelAd* model = (ModelAd*)PlanetModel();
                int orient = model->build(angle, &apos);
                a->mPos.set_3c(orient);
                a->f_c69090();
                void* aid = ((VItem2*)item)->v18(*(int*)((char*)item + 0x10), 1);
                ((SetterAd*)art)->set(*(void**)((char*)item + 0x14), aid);
                if (placed) FUN_00afa030(art);
            }
        }
    }
    ((VItem3*)item)->Release();
}

// @ 0x0103af90
void TSx::f_af90(void* p1, void* p2)
{
    uint a = ((Rng*)&g_rand)->next_00a68fb0(4) + 1;
    uint b = ((Rng*)&g_rand)->next_00a68fb0(4) + 1;
    Vec3i* v1 = ((WorldObj*)p1)->pos_00b8dad0();
    Vec3i* v2 = ((WorldObj*)p2)->pos_00b8dad0();
    if (v2->x == v1->x && v2->y == v1->y && v2->z == v1->z) {
        ItemVec* r = (ItemVec*)((WorldObj*)p1)->item_00b8dec0(0);
        if (r) {
            int n = ((int)r->mEnd - (int)r->mBegin) >> 2;
            if (n) {
                uint k = ((Rng*)&g_rand)->next_00a68fb0(n);
                ((ItemElem*)r->mBegin[k])->add_00ff0350((float)a);
            }
        }
        ItemVec* r2 = (ItemVec*)((WorldObj*)p2)->item_00b8dec0(0);
        if (r2) {
            int n = ((int)r2->mEnd - (int)r2->mBegin) >> 2;
            if (n) {
                uint k = ((Rng*)&g_rand)->next_00a68fb0(n);
                ((ItemElem*)r2->mBegin[k])->add_00ff0350((float)b);
            }
        }
    } else {
        ((Ad50*)this)->call_0103ad50(p1, ((WorldObj*)p2)->pos_00b8dad0(), a, 0);
        ((Ad50*)this)->call_0103ad50(p2, ((WorldObj*)p1)->pos_00b8dad0(), b, 0);
    }
}

// @ 0x0103b0c0
void VecDtor::dtor()
{
    void** end = mpEnd;
    for (void** it = mpBegin; it < end; ++it) {
        void* p = *it;
        if (p) ((RefObj_s0103_a480*)p)->base.Release();
    }
    void* begin = mpBegin;
    if (begin && begin != (void*)mpFixed) operator_delete(begin);
}

// @ 0x0103b100
void FUN_0103b100(void* stream, void* map)
{
    int save = *(int*)((char*)map + 0x14);
    void* s = ((V20*)stream)->v20();
    int x = ((V18*)s)->v18();
    WriteUint32((void*)x, &save, 1, 0);
    int node = *(int*)((char*)map + 8);
    int stop = (int)map + 4;
    while (node != stop) {
        FUN_00ae2e40(stream, (void*)(node + 0x10));
        ((V1c*)stream)->v1c();
        int v = *(int*)(node + 0x1c);
        void* s2 = ((V20*)stream)->v20();
        int x2 = ((V18*)s2)->v18();
        WriteUint32((void*)x2, &v, 1, 0);
        ((V1c*)stream)->v1c();
        node = (int)RBTreeIncrement((void*)node);
    }
    ((V1c*)stream)->v1c();
}

// @ 0x0103b1b0
void FUN_0103b1b0(AutoRef* a, int top, int n, int start, AutoRef value, int (*fn)(int,int))
{
    int hole = start;
    int child = start * 2 + 2;
    while (child < n) {
        if (fn((int)a[child].mpRef, (int)a[child - 1].mpRef) != 0) --child;
        a[hole] = a[child];
        hole = child;
        child = hole * 2 + 2;
    }
    if (child == n) {
        a[hole] = a[child - 1];
        hole = child - 1;
    }
    FUN_0103a280(a, top, hole, value, fn);
}

// @ 0x0103b290
void FUN_0103b290(AutoRef* a, AutoRef* b, int (*fn)(int,int))
{
    AutoRef value = b[-1];
    b[-1] = a[0];
    FUN_0103b1b0(a, 0, (int)(b - a) - 1, 0, value, fn);
}

// @ 0x0103b320
bool TSx::f_b320(int* prop)
{
    void* self = this;
    int key[3] = { 0, 0, 0 };
    GetPropertyAsKey(prop, 0x35d5cb4, key);
    Vec3i k2;
    k2.x = key[0];
    k2.y = 0;
    k2.z = 0;
    void* inv = ((SpaceGame*)SpaceGameGet_s0103_a480())->get_00a1ad60();
    if (((V74*)inv)->v74(&k2)) return false;
    void* list = ((InvItems*)((SpaceGame*)SpaceGameGet_s0103_a480())->get_00a1ad60())->list_00ff5b80();
    for (void** it = *(void***)list; it != *(void***)((char*)list + 4); ++it) {
        if (((A630*)self)->f_0103a630(*it, k2.x, k2.y, k2.z)) return false;
    }
    return true;
}

// @ 0x0103b3e0
void random_shuffle(ResourceKey* first, ResourceKey* last, RandomLinearCongruential* rng)
{
    ResourceKey* i = first + 1;
    if (i >= last)
        return;
    int span = (int)((char*)i - (char*)first);
    do {
        uint32_t j = rng->RandomUint32Uniform(span / 0xc + 1);
        ResourceKey* other = (ResourceKey*)((char*)first + j * 0xc);
        ResourceKey tmp = *i;
        *i = *other;
        *other = tmp;
        ++i;
        span += 0xc;
    } while (i < last);
}

// @ 0x0103b460
void WriteSTLSequenceT(IStreamWrite* stream, NPCVector* list)
{
    int count = list->size();
    ObjV18* writer = (ObjV18*)stream->v8();
    void* base = writer->v6();
    WriteUint32(base, &count, 1, 0);
    for (intrusive_ptr<cNPCStore_s0103_b3e0>* it = list->mpBegin; it != list->mpEnd; ++it) {
        cNPCStore_s0103_b3e0* pStore = it->get();
        uint32_t id = 0;
        if (pStore)
            id = (uint32_t)((StoreLayout*)pStore)->mIface.Cast(0x179c807);
        stream->v11(id);
    }
    stream->v7();
}

// @ 0x0103b4e0
void FUN_0103b4e0(vector_s0103_b3e0<ResourceKey>* self, uint32_t count)
{
    if ((uint32_t)self->size() < count) {
        ResourceKey* newBegin = 0;
        if (count != 0)
            newBegin = (ResourceKey*)operator_new(count * 0xc, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        FUN_00a11310(self->mpBegin, self->mpEnd, newBegin);
        ResourceKey* oldBegin = self->mpBegin;
        if (oldBegin != 0 && oldBegin != (ResourceKey*)&self->mpAllocator)
            operator_delete_array(oldBegin);
        int keep = (int)(self->mpEnd - oldBegin);
        self->mpBegin = newBegin;
        self->mpEnd = newBegin + keep;
        self->mpCapacity = newBegin + count;
    }
}

// @ 0x0103b590
void FUN_0103b590(RBAnchorSet* tree, RBNode** pOut, RBNode* parent, RareMapKey* key, int bUnique)
{
    int left = 0;
    if (bUnique == 0 && parent != &tree->mAnchor) {
        bool less = key->mKey.instance < parent->mKey.instance;
        if (key->mKey.instance == parent->mKey.instance) {
            less = key->mKey.group < parent->mKey.group;
            if (key->mKey.group == parent->mKey.group)
                less = key->mKey.type < parent->mKey.type;
        }
        left = 1;
        if (less)
            left = 0;
    }
    RBNode* node = (RBNode*)operator_new(0x20, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (node != 0) {
        node->mKey = key->mKey;
        node->mValue = key->mValue;
    }
    RBTreeInsert(node, parent, &tree->mAnchor, left);
    ++tree->mnSize;
    *pOut = node;
}

// @ 0x0103b640
void FUN_0103b640(int* first, int* last, int extra)
{
    int n = (int)(last - first);
    if (n < 2)
        return;
    int i = ((n - 2) >> 1) + 1;
    do {
        --i;
        ObjV04x* p = *(ObjV04x**)(first + i);
        if (p != 0)
            p->v1((int)p, extra);
        FUN_0103b1b0(first, i, n, i);
    } while (i != 0);
}

// @ 0x0103b690
SP::cSPSpaceTrading_s0103_b3e0::cSPSpaceTrading_s0103_b3e0()
{
    cGonzagoSubsystem_ctor(this);
    mpVtblIHandler = (void*)0x13eb384;
    mpVtbl00 = (void*)0x1499b30;
    mpVtbl04 = (void*)0x1499b2c;
    mpVtblIHandler = (void*)0x1499b1c;
    mpCommodityA = 0;
    mpCommodityAEnd = 0;
    mpCommodityACap = 0;
    mpCommodityB = 0;
    mpCommodityBEnd = 0;
    mpCommodityBCap = 0;
    intrusive_ptr<cNPCStore_s0103_b3e0>* buf = mNPCStore.mBuffer;
    mNPCStore.mpPoolBegin = buf;
    mNPCStore.mpEnd = buf;
    mNPCStore.mpBegin = buf;
    mNPCStore.mpCapacity = buf + 5;
    mUserItems.mpBegin = 0;
    mUserItems.mpEnd = 0;
    mUserItems.mpCapacity = 0;
    mNPCItems.mpBegin = 0;
    mNPCItems.mpEnd = 0;
    mNPCItems.mpCapacity = 0;
    mRareMap.mpLeft = 0;
    mRareMap.mpParent = 0;
    mRareMap.mColor = 0;
    mRareMap.mpParent = 0;
    mRareMap.mColor = 0;
    mRareMap.mSize = 0;
    mRareMap.mpLeft = (void*)&mRareMap.mpRight;
    mRareMap.mpRight = (void*)&mRareMap.mpRight;
    mRareGroups.mpBegin = 0;
    mRareGroups.mpEnd = 0;
    mRareGroups.mpCapacity = 0;
    mpAutoServer = 0;
    mpAutoHandler = 0;
    mpAutoIDs = 0;
    mAutoCount = 0;
    mAutoIndex = 0;
    mpStoreArray = 0;
    mPadE8 = 0;
    mPadEC = 0;
}

// @ 0x0103b7c0
SP::cSPSpaceTrading_s0103_b3e0::~cSPSpaceTrading_s0103_b3e0()
{
    mpVtbl00 = (void*)0x1499b30;
    mpVtbl04 = (void*)0x1499b2c;
    mpVtblIHandler = (void*)0x1499b1c;
    if (mpStoreArray != 0 && ArrayCapacity(mpStoreArray) != 0)
        operator_delete_array(mpStoreArray);
    if (mpAutoServer != 0) {
        void* d = mpAutoIDs;
        uint32_t e = mAutoCount;
        uint32_t f = mAutoIndex;
        mpAutoServer = 0;
        RemoveHandler(0, mpAutoHandler, d, e, f);
    }
    mRareGroups.Destroy(mRareGroups.mpBegin, mRareGroups.mpEnd);
    if (mRareGroups.mpBegin != 0 && ArrayCapacity(mRareGroups.mpBegin) != 0)
        operator_delete_array(mRareGroups.mpBegin);
    mRareMap.DoNukeSubtree((void*)mRareMap.mpParent);
    mNPCItems.DestroyAll();
    mUserItems.DestroyAll();
    mNPCStore.DestroyStore();
    if (mpCommodityB != 0 && ArrayCapacity(mpCommodityB) != 0)
        operator_delete_array(mpCommodityB);
    if (mpCommodityA != 0 && ArrayCapacity(mpCommodityA) != 0)
        operator_delete_array(mpCommodityA);
    mpVtblIHandler = (void*)0x13eb394;
    cGonzagoSubsystem_dtor(this);
}

// @ 0x0103b8d0
bool SP::cSPSpaceTrading_s0103_b3e0::AreBasicToolConditionsMet(PropertyList* pList, int param2)
{
    ResourceKey key = {0, 0, 0};
    GetPropertyAsKey(pList, 0x34f1a4f, &key);
    if (key.instance == 0x4edcc2bf) {
        if (!ToolConditionA(pList))
            goto fail;
    }
    if (!HasTradingItems(pList))
        goto fail;
    if (!AddTradingItems(pList, param2))
        goto fail;
    return true;
fail:
    return false;
}

// @ 0x0103b950
int SP::cSPSpaceTrading_s0103_b3e0::ModifyTrade(bool bBuy, bool bProposal, cSpaceInventoryItem* pItem, bool bApply)
{
    cSpaceInventory_s0103_b3e0* pInv = SpaceGameGet_s0103_b3e0()->GetPlayerInventory();
    cPlayerEmpire* pEmpire = FUN_01021300();
    if (pItem == 0)
        return 1;
    if (!bBuy) {
        if (!bProposal) {
            int money = pEmpire->GetMoney() + GetTradeBalance();
            if (money < FUN_006c0200(pItem))
                return 2;
        }
        if (bApply && pItem->mItemCount > 0)
            --pItem->mItemCount;
        return 0;
    }
    if (bProposal) {
        uint32_t toolId = 0;
        GetPropertyAsKeyInstance(pItem->mpPropList, 0x35d5cb4, &toolId);
        if (toolId == 0) {
            int need = AdjustTradeValue(1, pItem);
            if (pInv->GetCargoCount() < need)
                return 3;
        }
        ResourceKey key = {0, 0, 0};
        GetPropertyAsKey(pItem->mpPropList, 0x34f1a4f, &key);
        int value;
        if (key.instance == 0xb978c47a) {
            ResourceKey spiceKey = pItem->GetItemID();
            key = spiceKey;
            MapRareToSpiceKey(&key);
            float cost = (float)(int)pItem->mItemCost;
            if ((int)pItem->mItemCost < 0)
                cost += g_13f4fd0;
            void* made = FUN_00c463d0(&key, pItem->mItemCount, cost);
            cSpaceInventoryItem* created =
                CreateCommodityFromID(&made, (int*)&key, pItem->mItemCount, cost);
            value = GetItemValue(created);
        } else {
            value = GetItemValue(pItem);
        }
        if (SpaceEconomyTuning()->GetMaxCargo() <= pItem->mItemCount + value)
            return 3;
        ResourceKey toolKey = {(uint32_t)toolId, 0, 0};
        cSpaceInventoryItem* existing = pInv->GetItemByKey(&toolKey);
        cSpaceInventoryItem* tool = interface_cast_item(existing);
        if (toolId != 0) {
            if (tool != 0) {
                if (SpaceEconomyTuning()->GetMaxCargo() <= tool->mnToolCount + pItem->mItemCount)
                    return 3;
            }
            if (!AreBasicToolConditionsMet(pItem->mpPropList, 0))
                return 4;
        }
        int money = pEmpire->GetMoney() + GetTradeBalance();
        if (money < FUN_006c0200(pItem))
            return 2;
        cSpaceInventoryItem* found = FindStoreItem(pItem);
        if (found != 0 && found->mItemCount <= pItem->mItemCount)
            return 1;
    } else {
        ResourceKey key = {0, 0, 0};
        GetPropertyAsKey(pItem->mpPropList, 0x34f1a4f, &key);
        if (key.instance == 0x82af541) {
            cNPCStore_s0103_b3e0* store = mNPCStore.mpBegin[mLastNPCStoreIndex].mpObject;
            int maxSpice = SpaceEconomyTuning()->GetTradingMaxSpiceToBuy();
            if (maxSpice > store->mSpiceBought + pItem->mItemCount)
                return 1;
        }
        if (pItem->mItemCount >= GetItemValue(pItem))
            return 1;
    }
    if (bApply) {
        ++pItem->mItemCount;
        return 0;
    }
    return 0;
}

// @ 0x0103bc40
void** FUN_0103bc40(RBAnchorSet* tree, RBInsertResult* pOut, RareMapKey* key)
{
    RBNode* anchor = &tree->mAnchor;
    RBNode* parent = anchor;
    bool less = true;
    RBNode* node = tree->mAnchor.mpNodeParent;
    if (node != 0) {
        do {
            parent = node;
            less = key->mKey.instance < node->mKey.instance;
            if (key->mKey.instance == node->mKey.instance) {
                less = key->mKey.group < node->mKey.group;
                if (key->mKey.group == node->mKey.group)
                    less = key->mKey.type < node->mKey.type;
            }
            node = less ? node->mpNodeLeft : node->mpNodeRight;
        } while (node != 0);
    }
    RBNode* found = parent;
    if (less) {
        if (parent == tree->mAnchor.mpNodeLeft) {
            RBNode* inserted = 0;
            FUN_0103b590(tree, &inserted, parent, key, 0);
            pOut->mpNode = inserted;
            pOut->mbInserted = 1;
            return (void**)pOut;
        }
        found = (RBNode*)RBTreeDecrement(parent);
    }
    bool before = found->mKey.instance < key->mKey.instance;
    if (found->mKey.instance == key->mKey.instance) {
        before = found->mKey.group < key->mKey.group;
        if (found->mKey.group == key->mKey.group)
            before = found->mKey.type < key->mKey.type;
    }
    if (before) {
        RBNode* inserted = 0;
        FUN_0103b590(tree, &inserted, parent, key, 0);
        pOut->mpNode = inserted;
        pOut->mbInserted = 1;
        return (void**)pOut;
    }
    pOut->mpNode = found;
    pOut->mbInserted = 0;
    return (void**)pOut;
}

// @ 0x0103bd10
int* FUN_0103bd10(int* first, int* last, int* pred, int (*fn)(int, int))
{
    for (;;) {
        while (fn(*first, (int)pred) != 0)
            ++first;
        while (fn((int)pred, *(last - 1)) != 0)
            --last;
        if (first >= last)
            break;
        FUN_0103a330(first, last);
        ++first;
    }
    if (pred != 0)
        ((ObjV08*)pred)->v2();
    return first;
}

// @ 0x0103bd90
void FUN_0103bd90(int* first, int* mid, int* last, int (*cmp)(int, int))
{
    FUN_0103b640(first, mid, (int)cmp);
    for (int* it = mid; it < last; ++it) {
        if (cmp(*it, *first) != 0) {
            int* value = (int*)*it;
            if (value != 0)
                ((ObjV04*)value)->v1((int)cmp);
            int* firstVal = (int*)*first;
            if (firstVal != value) {
                if (firstVal != 0)
                    ((ObjV04*)firstVal)->v1((int)cmp);
                *it = (int)firstVal;
                if (value != 0)
                    ((ObjV04*)value)->v2();
            }
            FUN_0103b1b0(first, 0, (int)(mid - first), 0);
            if (value != 0)
                ((ObjV04*)value)->v2();
        }
    }
    for (int n = (int)(mid - first); (n & 0xfffffffc) > 4; n -= 4, --mid)
        FUN_0103b290(first, (int)mid, (int)cmp);
}

// @ 0x0103be80
Entry24* FUN_0103be80(Entry24* first, Entry24* last, Entry24* out)
{
    while (first != last) {
        if (out != 0) {
            out->w0 = first->w0;
            out->w1 = first->w1;
            out->w2 = first->w2;
            out->w3 = first->w3;
            out->tail.Copy(&first->tail);
        }
        first = (Entry24*)((char*)first + 0x24);
        out = (Entry24*)((char*)out + 0x24);
    }
    return out;
}

// @ 0x0103bef0
bool SP::cSPSpaceTrading_s0103_b3e0::FUN_0103bef0(ResourceKey key)
{
    PropertyList* prop = 0;
    if (IsToolAvailableForTrading(key.instance, key.type, key.group, &prop)) {
        bool r = AreBasicToolConditionsMet(prop, 0);
        if (prop != 0)
            prop->Release();
        return r;
    }
    if (prop != 0)
        prop->Release();
    return true;
}

// @ 0x0103bf70
int FUN_0103bf70(cSpaceInventoryItem* a, cSpaceInventoryItem* b)
{
    cSPSpaceTrading_s0103_b3e0* t1 = (cSPSpaceTrading_s0103_b3e0*)FUN_00b3d3d0(1, 1, a, 0);
    int ra = t1->ModifyTrade(true, true, a, false);
    cSPSpaceTrading_s0103_b3e0* t2 = (cSPSpaceTrading_s0103_b3e0*)FUN_00b3d3d0(1, 1, b, 0);
    int rb = t2->ModifyTrade(true, true, b, false);
    if ((ra == 4 || rb == 4) && ra != rb)
        return ra < rb;
    if (a->mItemType != 4 || b->mItemType != 4)
        return a->mItemType < b->mItemType;

    PropertyList* pa = a->mpPropList;
    if (pa != 0)
        pa->_v0();
    PropertyList* pb = b->mpPropList;
    if (pb != 0)
        pb->_v0();

    uint32_t ka = 0, kb = 0;
    GetPropertyAsKeyInstance(pa, 0x34f1a4f, &ka);
    GetPropertyAsKeyInstance(pb, 0x34f1a4f, &kb);
    ka = TradeItemRank(ka);
    kb = TradeItemRank(kb);
    bool less = ka < kb;
    if (ka == kb) {
        if (ka == 4) {
            GetPropertyAsKeyInstance(pa, 0x6009608, &ka);
            GetPropertyAsKeyInstance(pb, 0x6009608, &kb);
        }
        less = ka < kb;
        if (ka == kb) {
            cString_s0103_b3e0 sa;
            cString_s0103_b3e0 sb;
            GetPropertyAsText(pa, 0x3068d95d, &sa);
            GetPropertyAsText(pb, 0x3068d95d, &sb);
            ka = sa.GetText()[0];
            kb = sb.GetText()[0];
            if (ka == kb) {
                GetPropertyAsKeyInstance(pa, 0x34f1a4a, &ka);
                GetPropertyAsKeyInstance(pb, 0x34f1a4a, &kb);
            }
            less = ka < kb;
        }
    }
    if (pb != 0)
        pb->Release();
    if (pa != 0)
        pa->Release();
    return less;
}

// @ 0x0103c1f0
void FUN_0103c1f0(int* self, vector_s0103_b3e0<ResourceKey>* list)
{
    list->mpBegin = list->mpEnd;      // erase(begin(), end())
    int count = 0;
    ObjV20* writer = (ObjV20*)(*(ObjV20**)self)->v8();
    void* base = writer->v6();
    ReadInt32(base, &count, 1, 0);
    FUN_0103b4e0(list, (uint32_t)count);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        ResourceKey key = {0, 0, 0};
        FUN_00ae2ed0(self, &key);
        if (list->mpEnd < list->mpCapacity) {
            ResourceKey* slot = list->mpEnd;
            list->mpEnd = slot + 1;
            *slot = key;
        } else {
            FUN_00eeee80(list->mpEnd, &key);
        }
    }
    (*(ObjV20**)self)->v7();
}

// @ 0x0103c2c0
void FUN_0103c2c0(vector_s0103_b3e0<float>* list, int streamObj)
{
    float* begin = list->mpBegin;
    float* end = list->mpEnd;
    memcpy(begin, end, 0);
    list->mpEnd = list->mpBegin;
    int count = 0;
    void* reader = (*(ObjV20**)*(void**)streamObj)->v8();
    void* base = ((ObjV20*)reader)->v6();
    ReadInt32(base, &count, 1, 0);
    list->reserve(count);
    for (int i = 0; i < count; ++i) {
        int value = 0;
        void* reader2 = (*(ObjV20**)*(void**)streamObj)->v8();
        void* base2 = ((ObjV20*)reader2)->v6();
        ReadInt32(base2, &value, 1, 0);
        float f = (float)value;
        if (list->mpEnd < list->mpCapacity) {
            float* slot = list->mpEnd;
            list->mpEnd = slot + 1;
            *slot = f;
        } else {
            list->DoInsertValue(list->mpEnd, &f);
        }
    }
    (*(ObjV20**)*(void**)streamObj)->v7();
}

// @ 0x0103c4f0
void ItemVec_s0103_c3a0::erase(ItemPtr_s0103_c3a0* first, ItemPtr_s0103_c3a0* last)
{
    ItemPtr_s0103_c3a0* p = MoveItemRange(last, mpEnd, first);
    for (ItemPtr_s0103_c3a0* pEnd = mpEnd; p < pEnd; ++p)
        p->~ItemPtr_s0103_c3a0();
    mpEnd -= last - first;
}

// @ 0x0103c550
void StoreVec::DoInsertValue(NPCStorePtr_s0103_c3a0* position, const NPCStorePtr_s0103_c3a0& value)
{
    if (mpEnd != mpCapacity) {
        const NPCStorePtr_s0103_c3a0* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) NPCStorePtr_s0103_c3a0(*(mpEnd - 1));
        MoveItemRangeBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
        return;
    }

    uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
    uint32_t nNewSize = nPrevSize * 2;
    if ((int)nPrevSize <= 0)
        nNewSize = 1;
    NPCStorePtr_s0103_c3a0* pNewData = 0;
    if (nNewSize)
        pNewData = (NPCStorePtr_s0103_c3a0*)::operator new(nNewSize * sizeof(NPCStorePtr_s0103_c3a0), kEastlAllocatorName,
                                                0, 0, &kEastlAllocatorDesc, 0xd1);

    // Elements are relocatable pointers, so the old range is block-copied around the new slot.
    memcpy(pNewData, mpBegin, (char*)position - (char*)mpBegin);
    NPCStorePtr_s0103_c3a0* pNewEnd = (NPCStorePtr_s0103_c3a0*)((char*)pNewData + ((char*)position - (char*)mpBegin));
    if (pNewEnd)
        ::new (pNewEnd) NPCStorePtr_s0103_c3a0(value);
    memcpy(pNewEnd + 1, position, (char*)mpEnd - (char*)position);
    pNewEnd = pNewEnd + 1 + (mpEnd - position);

    if (mpBegin && mpBegin != mpPoolBegin)
        operator delete(mpBegin);
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
}

// @ 0x0103c6b0
RBInsertResult_s0103_c3a0* RBTree_s0103_c3a0::insert(RBInsertResult_s0103_c3a0* pResult, RBNode_s0103_c3a0* position, const ResourceKey_s0103_c3a0& value, bool bUnused)
{
    if (position == mpAnchorRight || position == (RBNode_s0103_c3a0*)&mpAnchorRight) {
        // Hint is end(): append after the rightmost node when the value is larger.
        if (mnSize != 0 && Less(mpAnchorRight->mValue, value)) {
            DoInsertValueImpl(pResult, mpAnchorRight, value, false);
            return pResult;
        }
    } else {
        RBNode_s0103_c3a0* pNext = RBTreeIncrement(position);
        if (Less(position->mValue, value) && Less(value, pNext->mValue)) {
            if (position->mpNodeRight != 0)
                DoInsertValueImpl(pResult, pNext, value, true);
            else
                DoInsertValueImpl(pResult, position, value, false);
            return pResult;
        }
    }
    RBInsertResult_s0103_c3a0 result;
    bool bInsertUnique = false;
    DoInsertUnique(&result, value, bInsertUnique);
    pResult->mpNode = result.mpNode;
    return pResult;
}

// @ 0x0103c800
void QuickSortImpl(ItemPtr_s0103_c3a0* first, ItemPtr_s0103_c3a0* last, int depth, ItemCompare_s0103_c3a0 cmp)
{
    for (;;) {
        int nBytes = (int)((char*)last - (char*)first) & ~3;
        if (!(nBytes > 0x70 && depth > 0)) {
            if (depth == 0)
                UnguardedInsertionSort(first, last, last, cmp);
            return;
        }
        ItemPtr_s0103_c3a0* pPivot = (ItemPtr_s0103_c3a0*)MedianOfThree(first, first + (last - first) / 2, last - 1, cmp, cmp);
        ItemPtr_s0103_c3a0 pivot = *pPivot;
        pivot.~ItemPtr_s0103_c3a0();
        ItemPtr_s0103_c3a0* pMid = PartitionRange(first, last);
        --depth;
        QuickSortImpl(pMid, last, depth, cmp);
        last = pMid;
    }
}

// @ 0x0103c8a0
KeyVecEntry* CopyKeyVecRange(KeyVecEntry* first, KeyVecEntry* last, KeyVecEntry* out)
{
    while (first != last) {
        *out = *first;
        ++first;
        ++out;
    }
    return out;
}

// @ 0x0103c8f0
KeyVecEntry* CopyKeyVecRangeBackward(KeyVecEntry* first, KeyVecEntry* last, KeyVecEntry* out)
{
    while (last != first) {
        --last;
        --out;
        *out = *last;
    }
    return out;
}

// @ 0x0103c940
void SP::cSPSpaceTrading_s0103_c3a0::BuildSpiceCommodities()
{
    if (!mFoodCommodities.empty())
        return;

    int nCommodities = (int)(mCommodities.mpEnd - mCommodities.mpBegin);
    if (nCommodities <= 0)
        return;

    PropertyList_s0103_c3a0* pProps = 0;
    ResourceKey_s0103_c3a0 kind = {0, 0, 0};
    ResourceKey_s0103_c3a0* pKey = mCommodities.mpBegin;
    for (; nCommodities != 0; --nCommodities, ++pKey) {
        // Release the previous property list before the next lookup.
        if (pProps != 0) {
            PropertyList_s0103_c3a0* pOld = pProps;
            pProps = 0;
            pOld->Release();
        }
        PropertyManager_Get_s0103_c3a0()->GetPropertyList(pKey->instance, 0x34d97fa, &pProps);
        GetPropertyAsKey_s0103_c3a0(pProps, 0x34f1a4f, &kind);
        if (kind.instance == 0x82af541)
            mFoodCommodities.push_back(*pKey);
    }
    if (pProps != 0)
        pProps->Release();
}

// @ 0x0103ca40
void SP::cSPSpaceTrading_s0103_c3a0::ChooseNPCSpices(cPlanetRef_s0103_c3a0* planet, bool bForce)
{
    if (*planet->GetSpiceKey() != kNoKey && !bForce)
        return;

    BuildSpiceCommodities();
    int situation = planet->GetRecord()->GetSpiceSituation() - 4;    // 4..11 -> 0..7
    bool bTradePost = (planet->mFlags & 0x3000) != 0;
    int nCommodities = (int)(mFoodCommodities.mpEnd - mFoodCommodities.mpBegin);
    if (nCommodities <= 0)
        return;

    float fLimit = (float)gRandom_s0103_c3a0.RandomDouble();
    float fSum = 0.0f;
    ResourceKey_s0103_c3a0* pKey = mFoodCommodities.mpBegin;
    for (int i = 0; i < nCommodities; ++i, ++pKey) {
        AutoRefCount<PropertyList_s0103_c3a0> props;
        PropertyManager_Get_s0103_c3a0()->GetPropertyList(pKey->instance, 0x34d97fa, props.AsOutParam());

        union { int mInt; float mFloat; } value;
        value.mInt = 0;
        switch (situation) {
        case 0:
        case 5:
        case 6:
        case 7:
            if (bTradePost)
                GetPropertyT_int(props.get(), 0x68b657e, &value.mInt);
            else
                GetPropertyT_int(props.get(), 0x68b657d, &value.mInt);
            break;
        case 1:
        case 3:
        case 4:
            if (bTradePost)
                GetPropertyT_int(props.get(), 0x68b657a, &value.mInt);
            else
                GetPropertyT_int(props.get(), 0x68b6579, &value.mInt);
            break;
        default: {
            Property_s0103_c3a0* pProp = 0;
            if (props.get() != 0) {
                if (bTradePost) {
                    if (props->GetProperty(0x68b657c, &pProp) && pProp->mType == 0x0d)
                        value.mFloat = *pProp->GetFloatPtr();
                } else {
                    if (props->GetProperty(0x68b657b, &pProp) && pProp->mType == 0x0d)
                        value.mFloat = *pProp->GetFloatPtr();
                }
            }
            break;
        }
        }

        fSum += value.mFloat;
        bool bTake;
        if (!bForce) {
            bTake = (fSum >= fLimit);
        } else {
            uint32_t rareTag = 0;
            Property_s0103_c3a0* pProp = 0;
            if (props.get() != 0 && props->GetProperty(0x58cbb75, &pProp) && pProp->mType == 0x0a)
                rareTag = *pProp->GetUIntPtr();
            bTake = (rareTag == 0xcd3700);
        }
        if (bTake) {
            planet->SetSpiceKey(*pKey);
            return;
        }
    }
}

// @ 0x0103cd00
void SP::cSPSpaceTrading_s0103_c3a0::RefreshNPCSpiceCosts(cPlanetRef_s0103_c3a0* planet)
{
    // Per-slot price scales (0.6f .. 3.0f), a static local so the compiler pools them.
    static const float kSpiceCostScale[10] = {
        0.6f, 0.75f, 0.85f, 1.0f, 1.2f, 1.4f, 1.65f, 2.0f, 2.5f, 3.0f
    };

    BuildSpiceCommodities();
    if ((int)(mFoodCommodities.mpEnd - mFoodCommodities.mpBegin) <= 0)
        return;

    RandomShuffle(mFoodCommodities.mpBegin, mFoodCommodities.mpEnd, &gRandom_s0103_c3a0);

    PropertyList_s0103_c3a0* pProps = 0;
    int nKey = 0;                        // next commodity to price
    for (int slot = 0; slot < 3; ++slot) {
        // Never price the planet's own spice; step over it.
        if (mFoodCommodities[nKey] == *planet->GetSpiceKey())
            ++nKey;
        const ResourceKey_s0103_c3a0& commodity = mFoodCommodities[nKey];

        if (pProps != 0) {
            pProps->Release();
            pProps = 0;
        }
        PropertyManager_Get_s0103_c3a0()->GetPropertyList(commodity.instance, 0x34d97fa, &pProps);

        float fBase = 0.0f;
        Property_s0103_c3a0* pProp = 0;
        if (pProps != 0 && pProps->GetProperty(0x34f1a4a, &pProp) && pProp->mType == 0x0d)
            fBase = (pProp->mFlags & 0x30) ? *(float*)pProp->mValue.mpData : pProp->mValue.mFloat;

        mNPCStore[mLastNPCStoreIndex]->mSpiceID.mpBegin[slot] = commodity;
        mNPCStore[mLastNPCStoreIndex]->mSpiceCost.mpBegin[slot] =
            (float)(NounManager(0x1c2e590d)->GetCurrentTerrainSphere()->Measure() * fBase) *
            kSpiceCostScale[gRandom_s0103_c3a0.RandomUint32Uniform(10)];
    }
    if (pProps != 0)
        pProps->Release();
}

// @ 0x0103cf20
cNPCStore_s0103_c3a0::cNPCStore_s0103_c3a0()
{
    mnRefCount = 0;
    mNPCInventory.mpBegin = 0;
    mNPCInventory.mpEnd = 0;
    mNPCInventory.mpCapacity = 0;
    mInventoryAges.mpBegin = 0;
    mInventoryAges.mpEnd = 0;
    mInventoryAges.mpCapacity = 0;

    mSpiceID.Init();
    mSpiceCost.Init();
    mPlanetKey = 0xffffffff;

    // The two inline vectors start out empty.
    mSpiceCost.Clear();
    mSpiceID.Clear();

    mbNeedsReset = 0;
    for (int i = 0; i < 3; ++i) {
        mSpiceCost.push_back(0.0f);
        ResourceKey_s0103_c3a0 noKey = {0, 0, 0};
        mSpiceID.push_back(noKey);
    }
}

// @ 0x0103d090
cNPCStore_s0103_c3a0::~cNPCStore_s0103_c3a0()
{
    if (mSpiceCost.mpBegin && mSpiceCost.mpBegin != mSpiceCost.mpPoolBegin)
        operator delete(mSpiceCost.mpBegin);
    if (mSpiceID.mpBegin && mSpiceID.mpBegin != mSpiceID.mpPoolBegin)
        operator delete(mSpiceID.mpBegin);
    mInventoryAges.~InventoryAges();
    mNPCInventory.~ItemVec_s0103_c3a0();
    mTimer.~cGonzagoTimer_s0103_c3a0();
}

// @ 0x0103d110
void SP::cSPSpaceTrading_s0103_c3a0::ConsiderBuyingRare(uint32_t planetKey, Vec<ResourceKey_s0103_c3a0>* pOut)
{
    int nCommodities = (int)(mCommodities.mpEnd - mCommodities.mpBegin);
    AutoRefCount<PropertyList_s0103_c3a0> props;
    ResourceKey_s0103_c3a0 key1 = {0, 0, 0};
    ResourceKey_s0103_c3a0 key2 = {0, 0, 0};
    ResourceKey_s0103_c3a0 key3 = {0, 0, 0};
    if (nCommodities <= 0)
        return;

    ResourceKey_s0103_c3a0* pKey = mCommodities.mpBegin;
    do {
        PropertyManager_Get_s0103_c3a0()->GetPropertyList(pKey->instance, 0x34d97fa, props.AsOutParam());
        if (GetPropertyAsKey_s0103_c3a0(props.get(), 0x5107709, &key1)) {
            GetPropertyAsKey_s0103_c3a0(props.get(), 0x510770a, &key2);
            GetPropertyAsKey_s0103_c3a0(props.get(), 0x510770b, &key3);

            bool bKnown1 = true;
            bool bKnown2 = true;
            bool bKnown3 = false;
            if (key1 != kNoKey)
                bKnown1 = SpaceGameGet(key1.instance)->GetPlayerEmpire()->IsCommodityKnown();
            if (key2 != kNoKey)
                bKnown2 = SpaceGameGet(key2.instance)->GetPlayerEmpire()->IsCommodityKnown();
            if (key3 != kNoKey)
                bKnown3 = SpaceGameGet(key3.instance)->GetPlayerEmpire()->IsCommodityKnown();

            if ((!bKnown1 || !bKnown2) && !bKnown3) {
                if (!bKnown1)
                    bKnown1 = (key1.instance == planetKey);
                if (!bKnown2)
                    bKnown2 = (key2.instance == planetKey);
                if ((bKnown1 && bKnown2) || key3.instance == planetKey)
                    pOut->push_back(*pKey);
            }
        }
        ++pKey;
    } while (--nCommodities != 0);
}

// @ 0x0103d360
void SP::cSPSpaceTrading_s0103_c3a0::ConsiderRareGroupRequest(uint32_t planetKey)
{
    ConsiderBuyingRare(planetKey, &mRareRequests);
}

// @ 0x0103d380
void FUN_0103d380(void* stream, RBTree* tree)
{
    tree->DoNukeSubtree(tree->mpRoot);
    tree->mAnchorLeft  = &tree->mAnchorLeft;
    tree->mAnchorRight = &tree->mAnchorLeft;
    tree->mpRoot       = 0;
    tree->mColor       = 0;
    tree->mSize        = 0;

    u32 count = 0;
    void* reader = (void*)VC0(void*, stream, 0x20);
    ReadInt32((void*)VC0(void*, reader, 0x18), &count, 1, 0);

    u32 i = 0;
    if (count != 0) {
        do {
            u32 key[3];
            key[0] = 0; key[1] = 0; key[2] = 0;
            FUN_00ae2ed0(stream, key);
            VC0(void, stream, 0x1c);

            u32 val = 0;
            void* reader2 = (void*)VC0(void*, stream, 0x20);
            ReadInt32((void*)VC0(void*, reader2, 0x18), &val, 1, 0);
            VC0(void, stream, 0x1c);

            u32 key2[3];
            key2[0] = key[0]; key2[1] = key[1]; key2[2] = key[2];
            u8  flag = 0;
            u32* node = tree->FUN_0103bc40(key, key2, flag);
            if (flag == 0)
                *(u32*)((char*)node + 0x1c) = val;
            i++;
        } while (i < count);
    }
    VC0(void, stream, 0x1c);
}

// @ 0x0103d4a0
void FUN_0103d4a0(void* stream, cNPCStoreFixedVec* vec)
{
    vec->clearRange(vec->mpBegin, vec->mpEnd);

    u32 count = 0;
    void* reader = (void*)VC0(void*, stream, 0x20);
    void* src = (void*)VC0(void*, reader, 0x18);
    ReadInt32(src, &count, 1, 0);
    vec->FUN_00c77b60(count);

    for (u32 i = 0; i < count; i++) {
        RefObj* val = 0;
        VC3(void, stream, 0x28, u32, 0x5b82ef9u, void**, (void**)&val, int, 0);

        void** pEnd = (void**)vec->mpEnd;
        if ((char*)pEnd < (char*)vec->mpCapacity) {
            vec->mpEnd = (char*)pEnd + 4;
            if (pEnd != 0) {
                *pEnd = val;
                if (val != 0)
                    VC0(void, (char*)val + 8, 0);
            }
        } else {
            vec->pushSlow(vec->mpEnd, &val);
        }

        if (val != 0)
            VC0(void, (char*)val + 8, 4);
    }
    VC0(void, stream, 0x1c);
}

// @ 0x0103dbd0
void cPaletteHost::FUN_0103dbd0(u8 param_2)
{
    mV74.erase(mV74.mpBegin, mV74.mpEnd);
    mV88.erase(mV88.mpBegin, mV88.mpEnd);

    int n = (char*)mVec48End - (char*)mVec48Begin;
    if (param_2 != 0 && (n & 0xfffffffc) > 0) {
        for (int i = 0; i < n >> 2; i++) {
            cPaletteGroup* g = (cPaletteGroup*)mVec48Begin[i];
            int m = ((char*)g->mpEnd38 - (char*)g->mpBegin34) >> 2;
            for (int j = 0; j < m; j++) {
                u32 key[3];
                key[0] = 0; key[1] = 0; key[2] = 0;
                cPaletteItem* it = (cPaletteItem*)g->mpBegin34[j];
                GetPropertyAsKey(it->m30, 0x34f1a4fu, key);
                if (key[0] == 0x7ecbe6f5u || key[0] == 0xb978c47au)
                    it->m10 = 0;
            }
        }
    }
}

// @ 0x0103dd20
void cSPSpaceTrading_s0103_d380::ShutdownGonzagoSubsystem()
{
    mV34.erase(mV34.mpBegin, mV34.mpEnd);
    mV20.erase(mV20.mpBegin, mV20.mpEnd);
    m48.clearRange(m48.mpBegin, m48.mpEnd);
    RBTree* t = &mTree;
    t->DoNukeSubtree(t->mpRoot);
    t->mAnchorLeft  = &t->mAnchorLeft;
    t->mAnchorRight = &t->mAnchorLeft;
    t->mpRoot       = 0;
    t->mColor       = 0;
    t->mSize        = 0;
}

// @ 0x0103dd80
void cSPSpaceTrading_s0103_d380::FUN_0103dd80()
{
    m48.clearRange(m48.mpBegin, m48.mpEnd);
    RBTree* t = &mTree;
    t->DoNukeSubtree(t->mpRoot);
    t->mAnchorLeft  = &t->mAnchorLeft;
    t->mAnchorRight = &t->mAnchorLeft;
    t->mpRoot       = 0;
    t->mColor       = 0;
    t->mSize        = 0;

    void* h = mpMsgD0;
    if (h != 0) {
        mpMsgD0 = 0;
        FUN_00571db0(h, mD4, mD8, mDC, mE0);
    }
}

// @ 0x0103de00
void cGonzagoTimerVec::push_back()
{
    cGonzagoTimer* pEnd = mpEnd;
    if (pEnd < mpCapacity) {
        mpEnd = pEnd + 1;
        if (pEnd != 0)
            new (pEnd) cGonzagoTimer();
    } else {
        cGonzagoTimer tmp;
        insert(mpEnd, &tmp);
    }
}

// @ 0x0103de50
u32* RBTree::FUN_0103de50(u32* key)
{
    void* node = 0;
    FUN_00c7f560(&node, key);
    if ((char*)node != (char*)&mAnchorLeft) {
        RBNode_s0103_d380* nd = (RBNode_s0103_d380*)node;
        bool lt;
        if (key[0] != nd->m10)
            lt = key[0] < nd->m10;
        else if (key[2] != nd->m18)
            lt = key[2] < nd->m18;
        else
            lt = key[1] < nd->m14;
        if (!lt)
            return (u32*)node + 7;
    }
    u32 local[3];
    local[0] = key[0]; local[1] = key[1]; local[2] = key[2];
    FUN_0103c6b0(node, key, local, 0);
    return (u32*)node + 7;
}

// @ 0x0103dee0
bool cSPSpaceTrading_s0103_dee0::ConsiderSellingTool(int iObjectID, ToolInfo* pInfo, uint32_t iKey, int iMode, void* pExtra)
{
    Property_s0103_dee0* pProp = 0;
    bool      bToolTypeOk = false;
    int       iToolType = 0;
    int       iKeyOut = 0;

    cGameNounManager* pNounMgr = GetNounManager();
    void* pAvatar = pNounMgr->GetAvatar();
    FUN_00b3d2a0(pAvatar);
    int iEmpire = FUN_00ba9370(pAvatar);
    FUN_00c308d0(SP_GetPlayerEmpire());
    FUN_00c31bc0(iEmpire);

    PropertyManager_s0103_dee0* pProps = GetPropertyManager();
    pProps->GetProperty(iKey, 0x34d97fa, &pProp);

    uint32_t keyA[3] = { 0, 0, 0 };
    GetPropertyAsKey(pProp, 0x34f1a4f, keyA);
    if (keyA[0] == 0x4edcc2bf) {
        iToolType = 1;
        bToolTypeOk = true;
    } else if (!pProps->HasProperty(0x057f3499)) {
        iToolType = 3;
    } else {
        Property_s0103_dee0* pTypeProp = 0;
        if (pProp != 0 && pProps->GetPropertyByKey(0x057f3499, &pTypeProp) &&
            pTypeProp->mValueType == 10)
            iToolType = *GetPropertyAsInt(pTypeProp);
    }

    bool bHasSpice = pProps->HasProperty(0x05caa7c3);
    if ((!bToolTypeOk && !bHasSpice) || (iEmpire == iMode && pInfo->mCount < 3))
        goto Fail;

    if (bHasSpice) {
        ItemStore* pStore = mppStores[mStoreIndex];
        ItemVec_s0103_dee0*   pVec   = &pStore->mInventory;
        int        nItems = (int)(pVec->mpEnd - pVec->mpBegin);
        for (int i = 0; i < nItems; ++i) {
            cSpaceItem* pItem = pVec->mpBegin[i].mpObject;
            int* pItemKey = pItem->GetKey();
            if (pItemKey[0] != pInfo->mCount || pItemKey[1] != iKey ||
                pItemKey[2] != iObjectID)
                continue;

            int iAgeProp = 0;
            if (pProp != 0) {
                Property_s0103_dee0* pAge = 0;
                if (pProps->GetPropertyByKey(0x05caa7c3, &pAge) &&
                    pAge->mValueType == 9)
                    iAgeProp = *GetPropertyAsInt(pAge);
            }
            NounManager_s0103_dee0(0xa5345685);
            FUN_00c75c30(0xa5345685);
            int iAgeLimit = iAgeProp * 60000;
            int iNow      = FUN_011e0810();
            (void)iAgeLimit;
            // per-item age timer: mAgesHandle points at a 0x20-byte record array
            unsigned long long iElapsed =
                ((cSPTimer*)((char*)pStore->mAgesHandle + i * 0x20))->GetElapsedTime();
            if (iNow == 0 || iElapsed < (unsigned long long)(long long)iNow ||
                pItem->mPoliticalId == (uint32_t)iToolType)
                goto Fail;
        }
    }

    bool bTypeFlag = false;
    Property_s0103_dee0* pType1 = 0;
    if (pProp != 0 && pProps->GetPropertyByKey(0x34f1a50, &pType1) &&
        pType1->mValueType == 1)
        bTypeFlag = *pType1->GetBool();
    bool bProceed = !(!bToolTypeOk && bTypeFlag);

    uint32_t keyB[3] = { 0, 0, 0 };
    GetPropertyAsKey(pProp, 0x35d5cb4, keyB);

    float fBasePrice = 0.0f;
    Property_s0103_dee0* pPriceProp = 0;
    if (pProp != 0 && pProps->GetPropertyByKey(0x34f1a49, &pPriceProp) &&
        pPriceProp->mValueType == 0x0d)
        fBasePrice = *GetPropertyAsFloat(pPriceProp);

    if (!bProceed || !AreBasicToolConditionsMet(pProp, 1))
        goto Fail;

    uint32_t iChanceKey = s_spiceChanceKeys[pInfo->mSpiceIndex];
    int      iChance = 0;
    if (pProps->HasProperty(iChanceKey))
        SP_GetPropertyT(pProp, iChanceKey, &iChance);

    if ((float)iChance <= (float)sMathRandom.RandomDoubleUniform() * 100.0f)
        goto Fail;

    float fMultiplier = 1.0f;
    Property_s0103_dee0* pMultProp = 0;
    if (pProp != 0 && pProps->GetPropertyByKey(0x34f1a4a, &pMultProp) &&
        pMultProp->mValueType == 0x0d)
        fMultiplier = *GetPropertyAsFloat(pMultProp);

    int iPrice = 0x3f800000;
    SP_GetPropertyT(pProp, s_spicePriceKeys[pInfo->mSpiceIndex], &iPrice);

    float fPriceFactor = 1.0f;
    if (pInfo == mpSelectedToolInfo) {
        int iType = 0;
        GetPropertyAsKeyInstance(pProp, 0x6009608, &iType);
        if ((iType == (int)0x9ab762c0 && (SpaceGameGet_s0103_dee0()->mFlags & 4) != 0) ||
            (iType == (int)0x5ec025c8 && (SpaceGameGet_s0103_dee0()->mFlags & 2) != 0)) {
            fPriceFactor = FUN_01005c60(2);
        } else {
            if (iType == (int)0xa4c2f6bd && FUN_00c322c0(6))
                fPriceFactor = FUN_01005c60(2);
            if (iType == (int)0x90348c2e && FUN_00c322c0(8))
                fPriceFactor = FUN_01005c60(2);
        }
    }

    NounManager_s0103_dee0(0x35edc257);
    float fTerrain = FUN_00c75c30(0x35edc257);
    float fValue = (float)iPrice * fMultiplier * fTerrain * fPriceFactor;

    cSpaceItem* pItem = 0;
    CreateCommodityFromID(&pItem, (cSpaceItem**)&iKeyOut, pProp, fValue);

    ItemStore* pStore = mppStores[mStoreIndex];
    pStore->mInventory.push_back(pItem);
    FUN_0103de00(&pStore->mAgesHandle);
    pStore->mTimer.Restart();

    cSpaceItem* pItemB = 0;
    CreateCommodityFromID(&pItemB, (cSpaceItem**)&iKeyOut, (Property_s0103_dee0*)0, fValue);
    mSelling.push_back(pItemB);

    if (pItemB != 0)
        pItemB->Release();
    if (pItem != 0)
        pItem->Release();
    if (pProp != 0)
        pProp->Release();
    return true;

Fail:
    if (pProp != 0)
        pProp->Release();
    return false;
}

// @ 0x0103e6e0
bool cSPSpaceTrading_s0103_dee0::ConsiderSellingSpice(int iObject, int iKeyA, int iKeyB, int iKeyC)
{
    if (!SP_SpaceGameGet()->GetPlayerInventory()->HasItem(kItemInterplanetaryDrive))
        return false;

    int* pKey = FUN_00b8dad0((cSPSpaceTrading_s0103_dee0*)iObject);   // key of the object handed in
    if (iKeyA != pKey[0] || iKeyB != pKey[1] || iKeyC != pKey[2])
        return false;

    Property_s0103_dee0* pSpice = FUN_00c705c0(iObject, 0);
    if (pSpice == 0)
        return false;

    float fValue;
    if ((int)FUN_00b8de30(this)->GetAvatar() == SP_GetPlayerEmpireID()) {
        fValue = 0.0f;
    } else {
        Property_s0103_dee0* pProp = 0;
        GetPropertyManager()->GetProperty(iKeyA, 0x34d97fa, &pProp);
        SP_GetPropertyT(pProp, 0x34f1a4a, &fValue);
        if (pProp != 0)
            pProp->Release();
    }

    cSpaceItem* pItem = 0;
    cSpaceItem* pOther = 0;
    CreateCommodityFromID(&pItem, &pOther, pSpice, fValue);
    mppStores[mStoreIndex]->mInventory.push_back(pItem);
    cSpaceItem* pFirst = pItem;
    FUN_0103de00(&mppStores[mStoreIndex]->mAgesHandle);
    mppStores[mStoreIndex]->mTimer.Restart();

    CreateCommodityFromID(&pItem, &pOther, (Property_s0103_dee0*)0, fValue);
    mSelling.push_back(pItem);

    if (pItem != 0)
        pItem->Release();
    if (pFirst != 0)
        pFirst->Release();
    return true;
}

// @ 0x0103e8e0
void SP::cSPSpaceTrading_s0103_e8e0::CreateNPCInventory(cPlanetRef* planet, int text)
{
    int numCommodities = mCommodities.size();
    int spiceOfStore = 0;
    int spiceOfPlanet = 0;
    uint32_t planetKey = planet->GetCommContext();

    // Drop this planet's stores older than 30 minutes.
    for (int i = 0; i < mNPCStore.size(); ++i) {
        cNPCStore_s0103_e8e0* store = mNPCStore[i].get();
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
        cNPCStore_s0103_e8e0* pNew = new ("Simulator/cNPCStore", 0, 0, 0, 0) cNPCStore_s0103_e8e0();
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
            cSpaceInventoryItem_s0103_e8e0* item = (*pInventory)[j].get();
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

    cEmpire_s0103_e8e0* empire = StarManager_s0103_e8e0()->GetEmpireByID(planet->GetAvatarHolder()->GetAvatarEmpireID());
    empire->GetStars();

    for (int i = 0; i < numCommodities; ++i) {
        ResourceKey kind = {0, 0, 0};
        intrusive_ptr_s0103_e8e0<PropertyList_s0103_e8e0> props;
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
        intrusive_ptr_s0103_e8e0<PropertyList_s0103_e8e0> props;
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

// @ 0x0103eff0
void SP::cSPSpaceTrading_s0103_eff0::PerformTrade()
{
    cSpaceInventory_s0103_eff0* inventory = SpaceGameGet_s0103_eff0()->GetPlayerInventory();
    cSpaceInventoryItemPtr_s0103_eff0 pTool;
    cSpaceInventoryItemPtr_s0103_eff0 pCommodity;
    int balance = GetTradeBalance_01039ca0();

    // Items the player sells.
    int count = field_74.size();
    for (int i = 0; i < count; ++i) {
        cSpaceInventoryItem_s0103_eff0* pSold = field_74[i].get();
        int& itemCount = pSold->mItemCount;
        if (itemCount == 0)
            continue;
        cSpaceInventoryItem_s0103_eff0* pItem = pSold;
        ResourceKey tradeType = {0, 0, 0};
        GetPropertyAsKey(pItem->mpPropList, 0x34f1a4f, &tradeType);

        if (tradeType.instance == 0x82af541) {
            intrusive_ptr_s0103_eff0<cPlanetRecord_s0103_eff0> planet;
            cPlanetRecord_s0103_eff0* p = StarManager_s0103_eff0()->GetPlanetRecord_00ba6dc0(mNPCStore[mLastNPCStoreIndex]->mPlanetKey);
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
            ShowEventLog_00e39ab0(0xd12f991e, GetPlayerEmpire_s0103_eff0(), &a, &b,
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
                Property_s0103_eff0* prop = pItem->mpPropList->GetPropertyObject(0x58cd55b);
                int n = prop->GetItemCount();
                ResourceKey* keys = prop->GetValueKey();
                for (int j = 0; j < n; ++j) {
                    cSpaceInventoryItemPtr_s0103_eff0 pExtra;
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
            cBadgeUI* ui = SpaceGameGet_s0103_eff0()->GetUI_01005180(0xf);
            ui->SetMode_007eb820(9);
            ui->mpTarget->mID = pItem->GetItemID().instance;
            ui->mpTarget->mKind = 4;
            SpaceGameGet_s0103_eff0()->GetPlayerStats()->AddStat_00fe5430(0x1c, 1);
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
            SpaceGameGet_s0103_eff0()->GetPlayerStats()->AddStat_00fe5430(0xd, value);
        }

        // Take the sold amount out of the NPC store's own stock of the same item.
        vector_s0103_eff0<cSpaceInventoryItemPtr_s0103_eff0>& stock = mNPCStore[mLastNPCStoreIndex]->mNPCInventory;
        int stockCount = stock.size();
        for (int j = 0; j < stockCount; ++j) {
            cSpaceInventoryItem_s0103_eff0* pStock = stock[j].get();
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
        cSpaceInventoryItem_s0103_eff0* pItem = object_cast<cSpaceInventoryItem_s0103_eff0>(*it);
        cSpaceInventoryItemPtr_s0103_eff0 pTaken;
        uint32_t tradeType = 0;
        GetPropertyAsKeyInstance(pItem->mpPropList, 0x34f1a4f, &tradeType);
        if (pItem->mItemCount == 0)
            continue;

        if (tradeType == 0xeb1a8062) {
            uint32_t groupID;
            if (PropertyList_s0103_eff0* list = pItem->mpPropList) {
                Property_s0103_eff0* prop;
                if (list->GetProperty(0x3c72dc6, prop) && prop->mnType == 9)
                    groupID = *prop->GetValueUInt32();
            }
            uint32_t groupIndex = FindRareGroup_0103a760(groupID);
            if (groupIndex < mRareGroups.size()) {
                for (uint32_t k = 0; k < mRareGroups[groupIndex].mRares.size(); ++k) {
                    cSpaceInventory_s0103_eff0* playerInventory = SpaceGameGet_s0103_eff0()->GetPlayerInventory();
                    ResourceKey rareKey = mRareGroups[groupIndex].mRares[k];
                    int index = playerInventory->IndexOf(4, rareKey);
                    inventory->TakeItems(index, pTaken, 1);
                }
            }
        } else {
            cSpaceInventory_s0103_eff0* playerInventory = SpaceGameGet_s0103_eff0()->GetPlayerInventory();
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
                cSpaceInventoryItemPtr_s0103_eff0 pStockItem;
                CreateCommodityFromID(pStockItem, pItem->GetItemID(), pItem->mItemCount, (float)pItem->mItemCost);
                if (cSpaceInventoryItem_s0103_eff0* pExisting = FindStoreItem_01039c00(pStockItem.get())) {
                    pExisting->mItemCount += pStockItem->mItemCount;
                } else {
                    mNPCStore[mLastNPCStoreIndex]->mNPCInventory.push_back(pStockItem);
                    mNPCStore[mLastNPCStoreIndex]->mNPCInventoryAges.push_back();
                    mNPCStore[mLastNPCStoreIndex]->mNPCInventoryAges.back().mTimer.Restart();
                    cSpaceInventoryItemPtr_s0103_eff0 pPlaceholder;
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
            ShowEventLog_00e39ab0(0xd12f991e, GetPlayerEmpire_s0103_eff0(), &a, &b,
                                  GetActivePlanetRecord()->GetCommContext(), pItem->mItemCount, &c, &d);
        }
        SpaceGameGet_s0103_eff0()->GetPlayerStats()->AddStat_00fe5430(0xd, pItem->GetUnitValue_006c0200() * pItem->mItemCount);
    }

    cEmpire_s0103_eff0* empire = GetPlayerEmpire_s0103_eff0();
    empire->AddTradeValue_00c31a00(balance);
    cEmpire_s0103_eff0* avatarEmpire = StarManager_s0103_eff0()->GetEmpireByID(GetAvatarSource_01021240()->GetAvatarEmpireID_00b1fdb0());
    if (avatarEmpire != empire && (balance > 1000 || balance < -1000))
        RelationshipManager()->RecordEvent(avatarEmpire->mPoliticalID, empire->mPoliticalID, 0x526e527, 1.0f);
    GetUFOSimulator()->CalcMaxTravelDistance();
}

// @ 0x0103fba0
void SP::cSPSpaceTrading_s0103_eff0::FUN_0103fba0(const ResourceKey* key, int value)
{
    RareNode_s0103_eff0* node = mRareMap.find(key).mpNode;
    int old;
    if (node != mRareMap.end())
        old = *(int*)((char*)node + 0x1c);
    else
        old = 0;
    if (old != value) {
        *mRareMap.insert(key) = value;
        if (value == 1) {
            uint32_t instance = key->instance;
            MessageServer()->SendMSG(0x6779f04, &instance, 0);
        }
    }
}

// @ 0x0103fc10
void SP::cSPSpaceTrading_s0103_eff0::AddCommodityToInventory(const ResourceKey* id, int count)
{
    cSpaceCommodityItem* item = new ("Simulator/cSpaceInventoryItem", 0, 0, 0, 0) cSpaceCommodityItem;
    if (item == 0)
        return;
    item->mItemType = 4;
    item->SetItemID(*id);
    item->mItemCount = count;

    PropertyList_s0103_eff0* pPropList = 0;
    IPropertyManager* pPropMgr = PropertyManager_s0103_eff0();
    if (pPropList) {
        PropertyList_s0103_eff0* pOld = pPropList;
        pPropList = 0;
        pOld->Release();
    }
    pPropMgr->v2c(item->GetItemInstanceID(), 0x34d97fa, &pPropList);
    item->SetPropertyList(pPropList);

    SpaceGameGet_s0103_eff0()->GetPlayerInventory()->AddItem((cSpaceInventoryItem_s0103_eff0*)item, 0, true);

    if (IsItemARare((uint32_t*)id)) {
        RareNode_s0103_eff0* node = mRareMap.find((ResourceKey*)&item->GetItemID()).mpNode;
        if (node == mRareMap.end() || node->mValue != 1) {
            SpaceGameGet_s0103_eff0()->GetPlayerStats()->AddStat_00fe5430(0xb, 1);
            ResourceKey k0 = {0, 0, 0};
            ResourceKey k1 = {0, 0, 0};
            ResourceKey k2 = {0, 0, 0};
            ShowEventLog_00e39ab0(0xdf8b9fc2, 0, &k2, (ResourceKey*)&item->GetItemID(),
                                  GetActivePlanetRecord()->GetCommContext(), 0, &k1, &k0);
        }

        ResourceKey* pID2 = (ResourceKey*)&item->GetItemID();
        RareNode_s0103_eff0* node2 = mRareMap.find(pID2).mpNode;
        if (node2 == mRareMap.end() || node2->mValue != 1) {
            *mRareMap.insert(pID2) = 1;
            uint32_t instance = pID2->instance;
            MessageServer()->SendMSG(0x6779f04, &instance, 0);
        }

        RareMessage msg(0xf46092d4);
        msg.SetValue(0, item->GetItemID().instance);
        MessageServer()->SendMSG(msg.mMessageID, &msg, 0);
        gpTranslator->mpItem14 = (cSpaceInventoryItem_s0103_eff0*)item;
        EventLog()->PostFeedbackEvent(0x554fe3de, 0x131a9f54, 0, 0, 1, 0);
    }

    item->AddRef();
    if (pPropList)
        pPropList->Release();
}

// @ 0x0103fe90
void __cdecl cSPSpaceTrading_s0103_fe90::CollectSpicePile(void* param_1, void* param_2)
{
    (void)param_1;
    cSPSpaceTrading_s0103_fe90* self = (cSPSpaceTrading_s0103_fe90*)param_2;

    int local_c = self->m64c;
    int local_8 = self->m650;
    int local_4 = self->m654;
    void* piVar1 = (void*)&self->m638;

    FUN_0103fc10((void*)&local_c, self->m638);
    void* ebx = FUN_01021260();
    void* pcVar4 = FUN_00b3d300();
    void* iVar5 = (void*)((tHost*)pcVar4)->FUN_00b21340((void*)FUN_00cd7d10,
                       (void*)FUN_00d3d420, (void*)FUN_00acdff0, (void*)FUN_00b1e500, (void*)&DAT_018c43e8);
    void* uVar6 = ((void*(__thiscall*)(void*))VFN((void*)&self->mVec34, 0x2c))((void*)&self->mVec34);
    void* piVar7 = FUN_00ac9310((char*)iVar5 + 4, uVar6, (int)((uint32_t)param_2 & 0xffffff00u));

    if (piVar7 != 0) {
        void* iVar5b = ((tHost*)ebx)->FUN_00c71e30();
        void* iVar8 = FUN_01021300_s0103_fe90();
        if (iVar5b != iVar8) {
            void* pcVar9 = FUN_00b3d300();
            void* sphere = ((tHost*)pcVar9)->FUN_00f67d90();
            char cVar3 = ((tHost*)sphere)->FUN_00c75650();
            if (cVar3 == 0) {
                void* uVar10 = ((void*(__thiscall*)(void*, int))VFN(piVar7, 0x4c))(piVar7, 0x526e5d8);
                void* rel = FUN_00b3d2c0(uVar10);
                float fVar13 = *(float*)&uVar10;
                fVar13 = *(float*)&uVar10;
                (void)rel;
                ((tHost*)rel)->FUN_00d06240((void*)0x3f800000);
                ((tHost*)piVar7)->FUN_00bdbf10();
                void* uVar6c = ((void*(__thiscall*)(void*))VFN(((char*)piVar7 + 0x120), 0x2c))((char*)piVar7 + 0x120);
                FUN_00ff5270(piVar7, fVar13, uVar6c);
            }
            void* pcVar11 = FUN_00b3d3e0(0x70983f0e, 0x131a9f54, 0, 0, 1, 0);
            ((tHost*)pcVar11)->FUN_00dd8640(0x70983f0e, 0x131a9f54, 0, 0, 1, 0);
            local_c = 0; local_8 = 0; local_4 = 0;
            FUN_006a1250(self->m63c, 0x34f1a4f, &local_c);
            if (local_c == 0x82af541) {
                void* pCVar12 = FUN_00675250(0x7c1a0684, 1);
                ((tHost*)pCVar12)->FUN_00676e90(0x7c1a0684, 1);
            }
        }
        local_8 = self->m650;
        int iVar5c = self->m64c;
        int iVar8c = self->m654;
        void* piVar7b = FUN_00b8dad0();
        if (((int*)piVar7b)[0] == iVar5c && ((int*)piVar7b)[1] == local_8 && ((int*)piVar7b)[2] == iVar8c) {
            float fVar18 = (float)*(int*)piVar1;
            if (*(int*)piVar1 < 0) {
                fVar18 = fVar18 + 4294967296.0f;
            }
            fVar18 = -fVar18;
            void* r1 = FUN_00bd81f0(fVar18);
            ((tHost*)r1)->FUN_00ff0350(fVar18);
            int iVar5d = *(int*)piVar1;
            void* r2 = FUN_00ffbe50(1, iVar5d);
            ((tHost*)r2)->FUN_00fffdd0(1, iVar5d);
        }
    }
}

// @ 0x01040220
void __thiscall cSPSpaceTrading_s0103_fe90::FUN_01040220()
{
    int n = (int)((char*)mVec34.mEnd - (char*)mVec34.mBegin) / 0xc;
    void* local_4c = 0;
    int local_30[3];
    local_30[0] = 0; local_30[1] = 0; local_30[2] = 0;

    void* oldEnd = mVecBC.mEnd;
    void* r = FUN_0103c8a0(oldEnd, oldEnd, mVecBC.mBegin);
    ((tHost*)&mVecBC)->FUN_00733030(r, mVecBC.mEnd);
    mVecBC.mEnd = (char*)mVecBC.mEnd - ((int)((char*)oldEnd - (char*)mVecBC.mBegin) / 0x24) * 0x24;

    if (n > 0) {
        for (int pass = 0; pass < 2; pass++) {
            int key = (pass == 0) ? (int)0x7ecbe6f5 : (int)0xeb1a8062;
            for (int i = 0; i < n; i++) {
                uint8_t* elem = (uint8_t*)mVec34.mBegin + i * 0xc;
                uint32_t elemId = *(uint32_t*)elem;
                void* pm = FUN_0067de30();
                if (local_4c != 0) {
                    void* old = local_4c;
                    local_4c = 0;
                    ((void(__thiscall*)(void*))VFN(old, 4))(old);
                }
                ((void(__thiscall*)(void*, uint32_t, int, void**))VFN(pm, 0x2c))(pm, elemId, 0x34d97fa, &local_4c);
                FUN_006a1250(local_4c, 0x34f1a4f, local_30);
                if (local_30[0] != key) continue;

                int val = 0;
                if (local_4c != 0) {
                    void* tmp = 0;
                    char c = ((char(__thiscall*)(void*, int, void**))VFN(local_4c, 0x24))(local_4c, 0x3c72dc6, &tmp);
                    if (c != 0 && *(uint16_t*)((char*)tmp + 0x12) == 9) {
                        void* t = tmp;
                        if ((*(uint8_t*)((char*)tmp + 0x10) & 0x30) != 0) {
                            t = *(void**)tmp;
                        }
                        val = *(int*)t;
                    }
                }

                int cnt = (int)((char*)mVecBC.mEnd - (char*)mVecBC.mBegin) / 0x24;
                if (pass == 0) {
                    int idx;
                    for (idx = 0; idx < cnt; idx++) {
                        if (*(int*)((char*)mVecBC.mBegin + idx * 0x24 + 0xc) == val) break;
                    }
                    if (idx >= cnt) {
                        uint8_t* base = (uint8_t*)mVecBC.mEnd;
                        if (mVecBC.mEnd < mVecBC.mCap) {
                            mVecBC.mEnd = base + 0x24;
                        } else {
                            uint8_t tmpItem[0x24];
                            *(uint32_t*)(tmpItem + 0x00) = 0;
                            *(uint32_t*)(tmpItem + 0x04) = 0;
                            *(uint32_t*)(tmpItem + 0x08) = 0;
                            *(uint32_t*)(tmpItem + 0x10) = 0;
                            *(uint32_t*)(tmpItem + 0x14) = 0;
                            *(uint32_t*)(tmpItem + 0x18) = 0;
                            mVecBC.FUN_01040090(mVecBC.mEnd, tmpItem);
                            base = (uint8_t*)mVecBC.mEnd - 0x24;
                        }
                        *(uint32_t*)(base + 0x00) = 0;
                        *(uint32_t*)(base + 0x04) = 0;
                        *(uint32_t*)(base + 0x08) = 0;
                        *(uint32_t*)(base + 0x10) = 0;
                        *(uint32_t*)(base + 0x14) = 0;
                        *(uint32_t*)(base + 0x18) = 0;
                        *(int*)(base + 0x0c) = val;
                    }
                    uint8_t* item = (uint8_t*)mVecBC.mBegin + idx * 0x24;
                    SpVec3* sub = (SpVec3*)(item + 0x10);
                    if (sub->mEnd < sub->mCap) {
                        uint8_t* e = (uint8_t*)sub->mEnd;
                        sub->mEnd = e + 0xc;
                        *(uint32_t*)(e + 0) = *(uint32_t*)elem;
                        *(uint32_t*)(e + 4) = *(uint32_t*)(elem + 4);
                        *(uint32_t*)(e + 8) = *(uint32_t*)(elem + 8);
                    } else {
                        sub->FUN_004e3e10(sub->mEnd, elem);
                    }
                } else {
                    for (int j = 0; j < cnt; j++) {
                        uint8_t* item = (uint8_t*)mVecBC.mBegin + j * 0x24;
                        if (*(int*)(item + 0xc) == val) {
                            *(uint32_t*)(item + 0x00) = *(uint32_t*)elem;
                            *(uint32_t*)(item + 0x04) = *(uint32_t*)(elem + 4);
                            *(uint32_t*)(item + 0x08) = *(uint32_t*)(elem + 8);
                        }
                    }
                }
            }
        }
    }
    if (local_4c != 0) {
        void* o = local_4c;
        ((void(__thiscall*)(void*))VFN(o, 4))(o);
    }
}

// @ 0x01040610
void __thiscall cSPSpaceTrading_s0103_fe90::FUN_01040610()
{
    mVec34.FUN_0050f740(mVec34.mBegin, mVec34.mEnd);
    mVec20.FUN_0050f740(mVec20.mBegin, mVec20.mEnd);

    void* local[3];
    local[0] = 0; local[1] = 0; local[2] = 0;
    void* pm = FUN_0067de30();
    ((void(__thiscall*)(void*, int, void**))VFN(pm, 0x48))(pm, 0x34d97fa, local);

    int n = (int)((char*)local[1] - (char*)local[0]) >> 2;
    mVec34.FUN_004548d0(n);
    for (int i = 0; i < n; i++) {
        uint32_t* puVar2 = (uint32_t*)((char*)mVec34.mBegin + i * 0xc);
        puVar2[0] = ((uint32_t*)local[0])[i];
        puVar2[1] = 0;
        puVar2[2] = 0;
    }
    FUN_01040220();
    if (local[0] != 0 && *(int*)((char*)local[0] - 4) != 0) {
        FUN_00f47380(local[0]);
    }
}

// @ 0x010406d0
void __thiscall cSPSpaceTrading_s0103_fe90::FUN_010406d0()
{
    FUN_01040610();
    if ((DAT_016df538 & 1) == 0) {
        DAT_016df538 |= 1;
        ((tHost*)&DAT_016df524)->FUN_00692f60(0);
        DAT_016df524 = (uint32_t)vtbl_01499b0c;
        FUN_0011e07ef((void*)FUN_013caa00);
    }
    if (((tHost*)&DAT_016df524)->FUN_00ab30c0() == 0) {
        ((tHost*)&DAT_016df524)->FUN_00692850();
    }
}

// @ 0x013a6f80
void FUN_013a6f80(void)
{
    extern char g_694f00; extern char g_b1fbf0; extern char g_675ca0;
    AttrRec rec;

    rec.mpName     = "planetKey";
    rec.mpField    = (void*)((char*)0x05b83971);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0xc;
    g_t15b8140[0] = rec;

    rec.mpName     = "lifetime";
    rec.mpField    = (void*)((char*)0x05b83972);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_ae3470;
    rec.mpFn28     = (void*)&g_ae3490;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_ae3310;
    rec.mpFn38     = (void*)&g_ac8050;
    rec.mFieldOfs  = 0x10;
    g_t15b8140[1] = rec;

    rec.mpName     = "spiceBought";
    rec.mpField    = (void*)((char*)0x05b83973);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_692ff0;
    rec.mpFn30     = (void*)&g_694ee0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_57cde0;
    rec.mFieldOfs  = 0x30;
    g_t15b8140[2] = rec;

    rec.mpName     = "mbDirty";
    rec.mpField    = (void*)((char*)0x060b5062);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_ac8750;
    rec.mpFn28     = (void*)&g_ac8780;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694fa0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_57ce00;
    rec.mFieldOfs  = 0x5c;
    g_t15b8140[3] = rec;

    rec.mpName     = "mSpiceID";
    rec.mpField    = (void*)((char*)0x05b83974);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_103c1f0;
    rec.mpFn28     = (void*)&g_c6adc0;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_c6c4e0;
    rec.mFieldOfs  = 0x60;
    g_t15b8140[4] = rec;

    rec.mpName     = "mSpiceCost";
    rec.mpField    = (void*)((char*)0x05b83975);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_103c2c0;
    rec.mpFn28     = (void*)&g_f26ca0;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_103c3a0;
    rec.mFieldOfs  = 0x9c;
    g_t15b8140[5] = rec;

    rec.mpName     = "mNPCInventory";
    rec.mpField    = (void*)((char*)0x05b83976);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_c87f80;
    rec.mpFn28     = (void*)&g_c87c00;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_c875f0;
    rec.mpFn38     = (void*)&g_c6c390;
    rec.mFieldOfs  = 0x34;
    g_t15b8140[6] = rec;

    rec.mpName     = "mNPCInventoryAges";
    rec.mpField    = (void*)((char*)0x05b83977);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_bf77d0;
    rec.mpFn28     = (void*)&g_bf1cf0;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_bf1d50;
    rec.mpFn38     = (void*)&g_f29650;
    rec.mFieldOfs  = 0x48;
    g_t15b8140[7] = rec;
}

// @ 0x013a72b0
void FUN_013a72b0(void)
{
    extern char g_b1fbf0;
    AttrRec rec;

    rec.mpName     = "mRareMap";
    rec.mpField    = (void*)((char*)0x03d840ef);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_103d380;
    rec.mpFn28     = (void*)&g_103b100;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_d011e0;
    rec.mpFn38     = (void*)&g_fe4aa0;
    rec.mFieldOfs  = 0xa0;
    g_t15b8360[0] = rec;

    rec.mpName     = "mNPCStore";
    rec.mpField    = (void*)((char*)0x05b82ced);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_103d4a0;
    rec.mpFn28     = (void*)&g_103b460;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_103a0a0;
    rec.mpFn38     = (void*)&g_c6c390;
    rec.mFieldOfs  = 0x48;
    g_t15b8360[1] = rec;

    rec.mpName     = "mNewlyAvailableCommodities";
    rec.mpField    = (void*)((char*)0x05f76c77);
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_b04e00;
    rec.mpFn28     = (void*)&g_c761c0;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_eafe40;
    rec.mFieldOfs  = 0xe4;
    g_t15b8360[2] = rec;
}
