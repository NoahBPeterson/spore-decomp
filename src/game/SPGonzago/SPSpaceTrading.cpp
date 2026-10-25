// src/game/SPGonzago/SPSpaceTrading.cpp -- migrated from slice(s) s013a55c0, s0103fe90, s0103e8e0, s0103d380, s0103b3e0, s010393a0 by tools/migrate/rewrite.py
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
extern "C" void  __cdecl FUN_006a1250(void* obj, int key, void* out); // 0x006a1250 SP::GetPropertyAsKey
extern "C" void  __cdecl FUN_0011e07ef(void* fn);                  // 0x011e07ef lib_crt::atexit
extern "C" void* __cdecl FUN_01021260(void);                       // 0x01021260 cSPLivingUniverse::GetActivePlanet
extern "C" void  __cdecl FUN_0103fc10(void* a, void* b);           // 0x0103fc10 AddCommodityToInventory
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
    void __thiscall FUN_010406d0();
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
    rec.mpField    = (void*)&g_5b83971;
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
    rec.mpField    = (void*)&g_5b83972;
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
    rec.mpField    = (void*)&g_5b83973;
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
    rec.mpField    = (void*)&g_60b5062;
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
    rec.mpField    = (void*)&g_5b83974;
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
    rec.mpField    = (void*)&g_5b83975;
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
    rec.mpField    = (void*)&g_5b83976;
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
    rec.mpField    = (void*)&g_5b83977;
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
    rec.mpField    = (void*)&g_3d840ef;
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
    rec.mpField    = (void*)&g_5b82ced;
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
    rec.mpField    = (void*)&g_5f76c77;
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
