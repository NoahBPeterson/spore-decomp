// Slice s0103b3e0: SP::cSPSpaceTrading ctor/dtor + trade modification, the rare-key table helpers and
// the EASTL shuffle / reserve / rbtree-insert / heap / partition / read-sequence helpers used by
// the space-stage trading code.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>

#define VSLOT(n) virtual void _v##n();

inline void* operator new(size_t, void* p) { return p; }

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// shared value types
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };

struct ResourceKey { uint32_t instance, type, group; };
inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
    return a.instance == b.instance && a.type == b.type && a.group == b.group;
}

// App::Property: data at +0, count at +8, flags at +0x10, type at +0x12.
struct Property {
    void* mpData;                                                            // +0x00
    uint32_t pad4;
    int mnItemCount;                                                         // +0x08
    uint32_t padc;
    uint16_t mnFlags;                                                        // +0x10
    uint16_t mnType;                                                         // +0x12
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

void GetPropertyAsKey(PropertyList* pList, uint32_t id, ResourceKey* pOut);       // 0x006a1250
bool GetPropertyAsKeyInstance(PropertyList* pList, uint32_t id, uint32_t* pOut);  // 0x006a12a0
void GetPropertyAsText(PropertyList* pList, uint32_t id, void* pOut);             // 0x006a1360

struct cPropertyManager {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual void GetProperty(uint32_t key, uint32_t id, void** pOut);        // +0x2c
};
cPropertyManager* PropertyManager();                                         // 0x0067de30

// cString: a small refcounted wide-string holder.
class cString {
public:
    uint32_t mTableId;                                                       // +0x00
    void* mpText;                                                            // +0x04
    cString();                                                               // 0x006b5060
    ~cString();                                                              // 0x006b5240
    const uint16_t* GetText();                                               // 0x006b55c0
};

// ---------------------------------------------------------------------------
// simulator objects
// ---------------------------------------------------------------------------
struct cObject {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* Cast(uint32_t typeID);                                     // +0x0c
};
struct cSpatialEntity { const Vector3& GetPosition(); };                      // 0x005c65e0
struct cEmpire {
    uint32_t pad00[0x84 / 4];
    uint32_t mPoliticalID;                                                   // +0x84
    uint32_t GetPoliticalID();                                               // 0x00b1fdb0
};
struct cPlanetRecord {
    virtual void v00(); virtual int AddRef(); virtual int Release();
    cEmpire* GetOwnerEmpire();                                               // 0x00b8de30
};

namespace SP {
uint32_t GetPlayerEmpireID();                                                // 0x01021090
int __stdcall AddTradingItems(PropertyList* pList, bool bAddMissing);         // 0x01039520
void __stdcall MapRareToSpiceKey(ResourceKey* pKey);                          // 0x01039690
int __stdcall HasTradingItems(PropertyList* pList);                           // 0x01039990
bool IsItemARare(uint32_t* pItemID);                                          // 0x0103a3c0
}

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

// eastl::vector<T, sp_vector_allocator>; only the first three words are observed.
template <class T> struct vector {
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
template <class T> struct uvector {   // size() as size_type
    T* mpBegin;                                                              // +0x00
    T* mpEnd;                                                                // +0x04
    T* mpCapacity;                                                           // +0x08
    void* mpAllocator;                                                       // +0x0c
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};

// The NPC store inventory vector: fixed_vector<AutoRefCount<cNPCStore>,5,1> (0x2c bytes).
struct cNPCStore;
struct NPCVector {
    intrusive_ptr<cNPCStore>* mpBegin;                                       // +0x00 -> 0x48
    intrusive_ptr<cNPCStore>* mpEnd;                                         // +0x04 -> 0x4c
    intrusive_ptr<cNPCStore>* mpCapacity;                                    // +0x08 -> 0x50
    void* mpAllocName;                                                       // +0x0c -> 0x54
    void* mpPoolBegin;                                                       // +0x10 -> 0x58
    void* mpPoolEnd;                                                         // +0x14 -> 0x5c
    intrusive_ptr<cNPCStore> mBuffer[5];                                     // +0x18 -> 0x60
    int size() const { return (int)(mpEnd - mpBegin); }
    intrusive_ptr<cNPCStore>& operator[](int i) { return mpBegin[i]; }
    void DestroyStore();                                                     // 0x0103b0c0
};

struct cGonzagoTimer { uint32_t pad00[8]; };

struct cNPCStore {
    VSLOT(0)
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
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
// SP::cSPSpaceTrading
// ---------------------------------------------------------------------------
namespace SP {
extern "C" void cGonzagoSubsystem_ctor(void* pThis);                          // 0x00b5b960
extern "C" void cGonzagoSubsystem_dtor(void* pThis);                          // 0x00b5b9a0

struct cHandlerIface {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* Cast(uint32_t typeID);                                     // +0x0c
};
struct cTradingHandler {
    uint32_t pad00[2];                                                       // +0x00
    cHandlerIface mIface;                                                    // +0x08
};

struct cAutoMessageHandler {
    void* mpServer;                                                          // +0x00
    void* mpHandler;                                                         // +0x04
    const uint32_t* mpIDs;                                                   // +0x08
    uint32_t mnCount;                                                        // +0x0c
    uint32_t mnIndex;                                                        // +0x10
};

struct cTradeKeyList {
    ResourceKey* mpBegin;                                                    // +0x00
    ResourceKey* mpEnd;                                                      // +0x04
    int size() const { return (int)(mpEnd - mpBegin); }
};

// Rare-group table entry (0x24 bytes).
struct cRareGroup {
    ResourceKey mGroupKey;                                                   // +0x00
    uint32_t mGroupID;                                                       // +0x0c
    uvector<ResourceKey> mRares;                                             // +0x10
    uint32_t mState;                                                         // +0x20
};

// eastl::rbtree header used by the rare map (0x18 bytes starting at +0xa0).
struct RareMapHeader {
    void* mpAllocator;                                                       // +0x00 -> 0xa0
    void* mpRight;                                                           // +0x04 -> 0xa4
    void* mpLeft;                                                            // +0x08 -> 0xa8
    uint32_t mpParent;                                                       // +0x0c -> 0xac
    uint32_t mColor;                                                         // +0x10 -> 0xb0
    uint32_t mSize;                                                          // +0x14 -> 0xb4
    void DoNukeSubtree(void* root);                                          // 0x009a9600
};

class cSPSpaceTrading {
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
    vector<cSpaceInventoryItemPtr> mUserItems;                               // +0x74  mNPCGiving
    uint32_t mPad84;                                                         // +0x84
    vector<cSpaceInventoryItemPtr> mNPCItems;                                // +0x88  mNPCGetting
    uint32_t mPad94[2];                                                      // +0x94
    int mLastNPCStoreIndex;                                                  // +0x9c
    RareMapHeader mRareMap;                                                   // +0xa0
    uint32_t mPadB8;                                                         // +0xb8
    vector<cRareGroup> mRareGroups;                                          // +0xbc
    uint32_t mPadCC;                                                         // +0xcc
    void* mpAutoServer;                                                      // +0xd0
    void* mpAutoHandler;                                                     // +0xd4
    void* mpAutoIDs;                                                         // +0xd8
    uint32_t mAutoCount;                                                     // +0xdc
    uint32_t mAutoIndex;                                                     // +0xe0
    void* mpStoreArray;                                                      // +0xe4  freed in dtor (array)
    uint32_t mPadE8;                                                         // +0xe8
    uint32_t mPadEC;                                                         // +0xec

    cSPSpaceTrading();                                                       // 0x0103b690
    ~cSPSpaceTrading();                                                      // 0x0103b7c0
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

}  // namespace SP

using SP::cSPSpaceTrading;

// ---------------------------------------------------------------------------
// simulator accessors
// ---------------------------------------------------------------------------
struct cSpaceInventory {
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
struct cSpaceGame { cSpaceInventory* GetPlayerInventory(); };                 // 0x00a1ad60
cSpaceGame* SpaceGameGet();                                                  // 0x01002bd0

struct cSpaceEconomyTuning {
    int GetMaxCargo();                                                       // 0x0102ff00
    int GetTradingMaxSpiceToBuy();                                           // 0x0102fde0
};
cSpaceEconomyTuning* SpaceEconomyTuning();                                   // 0x0102f810

struct cPlayerItemStore {
    bool DoInsertValue(cSpaceInventoryItem* pItem);                          // 0x00fe4180
    cSpaceInventoryItem* GetReplacement(cSpaceInventoryItem* pItem);         // 0x00fe41c0
};

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void* operator_new(int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void  operator_delete_array(void* p);                                        // 0x00f47380
// eastl arrays store the element count in the dword immediately before the data pointer.
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
// EA::Random::RandomLinearCongruential::RandomUint32Uniform is a __thiscall member (ecx = rng).
struct RandomLinearCongruential { uint32_t RandomUint32Uniform(int n); };      // 0x00a68fb0
void  FUN_00ae2ed0(void* rng, void* out);                                    // 0x00ae2ed0
void  FUN_00eeee80(void* pos, void* value);                                  // 0x00eeee80
void  FUN_00c77b60(int count);                                               // 0x00c77b60
void  FUN_00cc4160(void* pos, const void* value);                            // 0x00cc4160
void* FUN_00c463d0(void* p1, int a, float b);                                // 0x00c463d0
int   FUN_01039b70(cSpaceInventoryItem* pItem);                              // 0x01039b70 GetItemValue
cSpaceInventoryItem* FUN_01039c00(cSpaceInventoryItem* pItem);               // 0x01039c00 FindStoreItem
int   FUN_01039ca0();                                                        // 0x01039ca0 GetTradeBalance
int   FUN_01039d20(bool bSetCountToOne, cSpaceInventoryItem* pItem);         // 0x01039d20
void  FUN_0103a480(void** out, int* id, int count, float cost);              // 0x0103a480 CreateCommodityFromID
void  FUN_01039690(ResourceKey* pKey);                                       // 0x01039690 MapRareToSpiceKey
bool  FUN_010398e0(cSPSpaceTrading* self, uint32_t a, uint32_t b, uint32_t c,
                   PropertyList** ppProperty);                               // 0x010398e0
void  FUN_0103b290(int* a, int b, int c);                                    // 0x0103b290
void  FUN_0103a330(int* a, int* b);                                          // 0x0103a330 iter_swap
void  FUN_006606a0(void* dst, void* src);                                    // 0x006606a0 (stdcall: callee pops 8)
cSpaceInventoryItem* interface_cast_item(void* p);                           // 0x00c87070
void* FUN_00b3d3d0(int a, int b, void* c, int d);                           // 0x00b3d3d0
struct cPlayerEmpire { int GetMoney(); };                                     // 0x00c30cb0
cPlayerEmpire* FUN_01021300();                                               // 0x01021300
int   FUN_006c0200(cSpaceInventoryItem* pItem);                              // 0x006c0200

extern void* g_rand;              // 0x01601760
extern float g_13f4fd0;           // 0x013f4fd0

// indirect-call object wrappers (slot reached through the object's vtable).
struct ObjV04 { VSLOT(0) virtual void v1(int v); virtual void v2(); };       // +0x04 / +0x08
struct ObjV04x { VSLOT(0) virtual void v1(int a, int b); virtual void v2(); };// +0x04 (2-arg sift call)
struct ObjV08 { VSLOT(0) VSLOT(1) virtual void v2(); };                      // +0x08

// ===========================================================================
// 0x0103b3e0  eastl::random_shuffle<ResourceKey*, RandomLinearCongruential>
// ===========================================================================
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

// ===========================================================================
// 0x0103b460  SP::WriteSTLSequenceT<fixed_vector<AutoRefCount<cNPCStore>,5,1>>
// ===========================================================================
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
// @ 0x0103b460
void WriteSTLSequenceT(IStreamWrite* stream, NPCVector* list)
{
    int count = list->size();
    ObjV18* writer = (ObjV18*)stream->v8();
    void* base = writer->v6();
    WriteUint32(base, &count, 1, 0);
    for (intrusive_ptr<cNPCStore>* it = list->mpBegin; it != list->mpEnd; ++it) {
        cNPCStore* pStore = it->get();
        uint32_t id = 0;
        if (pStore)
            id = (uint32_t)((StoreLayout*)pStore)->mIface.Cast(0x179c807);
        stream->v11(id);
    }
    stream->v7();
}

// ===========================================================================
// 0x0103b4e0  eastl::vector<ResourceKey, sp_vector_allocator>::reserve
// ===========================================================================
// @ 0x0103b4e0
void FUN_0103b4e0(vector<ResourceKey>* self, uint32_t count)
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

// ===========================================================================
// 0x0103b590  eastl rbtree DoInsertValue (rare-group map)
// ===========================================================================
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
// Rare-map key: a ResourceKey followed by the stored 4th dword.
struct RareMapKey { ResourceKey mKey; uint32_t mValue; };
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

// ===========================================================================
// 0x0103b640  eastl::make_heap over AutoRefCount elements
// ===========================================================================
void FUN_0103b1b0(int* a, int param2, int n, int start);
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

// ===========================================================================
// 0x0103b690  SP::cSPSpaceTrading::cSPSpaceTrading
// ===========================================================================
// @ 0x0103b690
cSPSpaceTrading::cSPSpaceTrading()
{
    SP::cGonzagoSubsystem_ctor(this);
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
    intrusive_ptr<cNPCStore>* buf = mNPCStore.mBuffer;
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
cSPSpaceTrading::~cSPSpaceTrading()
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
    SP::cGonzagoSubsystem_dtor(this);
}

// @ 0x0103b8d0
bool cSPSpaceTrading::AreBasicToolConditionsMet(PropertyList* pList, int param2)
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

// @ 0x0103b950  SP::cSPSpaceTrading::ModifyTrade
int cSPSpaceTrading::ModifyTrade(bool bBuy, bool bProposal, cSpaceInventoryItem* pItem, bool bApply)
{
    cSpaceInventory* pInv = SpaceGameGet()->GetPlayerInventory();
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
            cNPCStore* store = mNPCStore.mpBegin[mLastNPCStoreIndex].mpObject;
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

// ===========================================================================
// 0x0103bc40  rare-map emplace (lower_bound + insert)
// ===========================================================================
// @ 0x0103bc40
struct RBInsertResult { void* mpNode; uint8_t mbInserted; };
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

// ===========================================================================
// 0x0103bd10  eastl::partition over AutoRefCount elements
// ===========================================================================
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

// ===========================================================================
// 0x0103bd90  eastl::inplace_merge over AutoRefCount elements
// ===========================================================================
void FUN_0103b290(int* a, int b, int c);
void FUN_0103b640(int* first, int* last, int extra);
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

// ===========================================================================
// 0x0103be80  eastl::uninitialized_copy over 0x24-byte entries
// ===========================================================================
struct EntryTail {
    uint32_t w0;                                                             // +0x00
    uint32_t rest[4];                                                        // +0x04
    void Copy(void* src);                                                    // 0x006606a0
};
struct Entry24 {
    uint32_t w0, w1, w2, w3;                                                 // +0x00..+0x0c
    EntryTail tail;                                                          // +0x10
};
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

// ===========================================================================
// 0x0103bef0
// ===========================================================================
// @ 0x0103bef0
bool cSPSpaceTrading::FUN_0103bef0(ResourceKey key)
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

// ===========================================================================
// 0x0103bf70  SP::cSPSpaceTrading trade-proposal comparator
// ===========================================================================
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
// @ 0x0103bf70
int FUN_0103bf70(cSpaceInventoryItem* a, cSpaceInventoryItem* b)
{
    cSPSpaceTrading* t1 = (cSPSpaceTrading*)FUN_00b3d3d0(1, 1, a, 0);
    int ra = t1->ModifyTrade(true, true, a, false);
    cSPSpaceTrading* t2 = (cSPSpaceTrading*)FUN_00b3d3d0(1, 1, b, 0);
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
            cString sa;
            cString sb;
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

// ===========================================================================
// 0x0103c1f0  SP::ReadSTLSequenceT<eastl::vector<ResourceKey>>
// ===========================================================================
struct ObjV20 {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void* v6();                                                      // +0x18
    virtual void v7();                                                       // +0x1c
    virtual void* v8();                                                      // +0x20
};
void FUN_0103b4e0(vector<ResourceKey>* self, uint32_t count);
// @ 0x0103c1f0
void FUN_0103c1f0(int* self, vector<ResourceKey>* list)
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

// ===========================================================================
// 0x0103c2c0  SP::ReadSTLSequenceT<eastl::fixed_vector<float,3,1>>
// ===========================================================================
// @ 0x0103c2c0
void FUN_0103c2c0(vector<float>* list, int streamObj)
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
