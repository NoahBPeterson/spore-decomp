// src/game/SPGonzago/SPSpaceInventory.cpp -- migrated from slice(s) s0104bcc0, s00c87be0, s00c86aa0, s01351ae0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceInventory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cISerializableObject.h"
#include "SP/cLocalizedString.h"
#include "SP/cMWModel.h"
#include "SP/cIModelWorld.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyList.h"
#include "SP/cSolarSystem.h"
#include "SP/cSPSpaceInventoryItem.h"
#include "SP/cVarListSerializer.h"
#include "EA/Messaging/IHandler.h"
#include "SP/cViewer.h"
#include "SP/cCommunity.h"
#include "SP/cSpatialObject.h"
#include <math.h>
#include "EA/Variant.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPEditorVerbIconTray.h"
#include "SP/cSPSpaceToolData.h"
#include "SP/cSPTimer.h"
#include "SP/cString.h"
#include "SP/cTerrainSphere.h"
#include "EA/COM/IUnknown32.h"

// unnamed retail callees and globals (address in the comment)
extern void S3800_F34A();   // 0x00b1fbf0
extern void S3800_F34B();   // 0x00b1fbf0
extern void S3800_F38A();   // 0x0057cde0
extern void S3800_F38B();   // 0x00675ca0
extern void U_01353800_0_34();   // 0x00b1fbf0
extern void U_01353800_1_24();   // 0x00572810
extern void U_01353800_1_28();   // 0x00572840
extern void U_01353800_1_2c();   // 0x00692ff0
extern void U_01353800_1_30();   // 0x00694ee0
extern void U_01353800_2_24();   // 0x00572810
extern void U_01353800_2_28();   // 0x00572840
extern void U_01353800_2_2c();   // 0x00692ff0
extern void U_01353800_2_30();   // 0x00694ee0
extern void U_01353800_3_24();   // 0x00572810
extern void U_01353800_3_28();   // 0x00572840
extern void U_01353800_3_2c();   // 0x00693090
extern void U_01353800_3_30();   // 0x00694f00
extern void U_01353800_4_24();   // 0x00ac8750
extern void U_01353800_4_28();   // 0x00ac8780
extern void U_01353800_4_2c();   // 0x00693090
extern void U_01353800_4_30();   // 0x00694fa0
extern void U_01353800_4_34();   // 0x00b1fbf0
extern void U_01353800_4_38();   // 0x0057ce00
extern void U_01353800_6_24();   // 0x00572810
extern void U_01353800_6_28();   // 0x00572840
extern void U_01353800_6_2c();   // 0x00693090
extern void U_01353800_6_30();   // 0x00694f00
extern void U_01353800_7_24();   // 0x00572810
extern void U_01353800_7_28();   // 0x00572840
extern void U_01353800_7_2c();   // 0x00693090
extern void U_01353800_7_30();   // 0x00694f00
extern void U_01353800_8_24();   // 0x00ac8750
extern void U_01353800_8_28();   // 0x00ac8780
extern void U_01353800_8_2c();   // 0x00693090
extern void U_01353800_8_30();   // 0x00694fa0
extern void U_01353800_8_34();   // 0x00b1fbf0
extern void U_01353800_8_38();   // 0x0057ce00

// ---- items of slice s01351ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
struct PropDesc {
    const char* mName;   // +0x00
    u32 mHash;   // +0x04
    u32 mType;   // +0x08
    u32 mPad0C;   // +0x0c
    u32 mPad10;   // +0x10
    u32 mPad14;   // +0x14
    u32 mZero18;   // +0x18
    u32 mZero1C;   // +0x1c
    void* mDefault;   // +0x20
    void* mFn24;   // +0x24
    void* mFn28;   // +0x28
    void* mFn2C;   // +0x2c
    void* mFn30;   // +0x30
    void* mFn34;   // +0x34
    void* mFn38;   // +0x38
};
extern void S3800_F34A();   // 0x00b1fbf0
extern void S3800_F34B();   // 0x00b1fbf0
extern void S3800_F38A();   // 0x0057cde0
extern void S3800_F38B();   // 0x00675ca0
extern void U_01353800_0_34();   // 0x00b1fbf0
extern void U_01353800_1_24();   // 0x00572810
extern void U_01353800_1_28();   // 0x00572840
extern void U_01353800_1_2c();   // 0x00692ff0
extern void U_01353800_1_30();   // 0x00694ee0
extern void U_01353800_2_24();   // 0x00572810
extern void U_01353800_2_28();   // 0x00572840
extern void U_01353800_2_2c();   // 0x00692ff0
extern void U_01353800_2_30();   // 0x00694ee0
extern void U_01353800_3_24();   // 0x00572810
extern void U_01353800_3_28();   // 0x00572840
extern void U_01353800_3_2c();   // 0x00693090
extern void U_01353800_3_30();   // 0x00694f00
extern void U_01353800_4_24();   // 0x00ac8750
extern void U_01353800_4_28();   // 0x00ac8780
extern void U_01353800_4_2c();   // 0x00693090
extern void U_01353800_4_30();   // 0x00694fa0
extern void U_01353800_4_34();   // 0x00b1fbf0
extern void U_01353800_4_38();   // 0x0057ce00
extern void U_01353800_6_24();   // 0x00572810
extern void U_01353800_6_28();   // 0x00572840
extern void U_01353800_6_2c();   // 0x00693090
extern void U_01353800_6_30();   // 0x00694f00
extern void U_01353800_7_24();   // 0x00572810
extern void U_01353800_7_28();   // 0x00572840
extern void U_01353800_7_2c();   // 0x00693090
extern void U_01353800_7_30();   // 0x00694f00
extern void U_01353800_8_24();   // 0x00ac8750
extern void U_01353800_8_28();   // 0x00ac8780
extern void U_01353800_8_2c();   // 0x00693090
extern void U_01353800_8_30();   // 0x00694fa0
extern void U_01353800_8_34();   // 0x00b1fbf0
extern void U_01353800_8_38();   // 0x0057ce00
// ---- items of slice s01351ae0 end

// ---- items of slice s00c86aa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t   kItemMessageIDs[1];            // 0x01473528
extern void*      kItemSerializerList;           // 0x01579f50
extern void*      kSpaceInventorySerializerList; // 0x01579ed8
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);
namespace EA {
namespace IO {
bool WriteUint32(void* pStream, const uint32_t* pData, uint32_t nCount, int endian);
}
}
namespace EA {
namespace IO {
bool ReadInt32(void* pStream, uint32_t* pData, uint32_t nCount, int endian);
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(void* pServer, void* pHandler, uint32_t* pIds, uint32_t nCount, uint32_t extra);
}
}
struct VObj174;
struct cMWModel;
struct ResourceKey;
struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};
extern ResourceKey kDefaultItemID;               // 0x01694cc4
extern ResourceKey kCargoPanelID;                // 0x01579eb0
struct VObj174 {
    virtual void        AddRef();   // 0x00
    virtual void        Release();  // 0x04
    virtual void        v008();   // 0x08
    virtual cMWModel*   v00c(uint32_t type, uint32_t group, uint32_t arg); // 0x0c
    virtual void        v010();
    virtual void        v014();
    virtual VObj174*    v018();   // 0x18
    virtual void        v01c();
    virtual VObj174*    v020();   // 0x20
    virtual bool        v024(uint32_t key, struct cProperty** out);
    virtual void        v028();
    virtual void        v02c(uint32_t a, uint32_t b = 0, VObj174** out = 0);
    virtual void        v030();
    virtual void        v034();
    virtual void        v038();
    virtual void        v03c();
    virtual void        v040();
    virtual void        v044();
    virtual void        v048();
    virtual void        v04c();
    virtual void        v050();
    virtual void        v054();
    virtual void        v058();
    virtual void        v05c();
    virtual void        v060(const ResourceKey* pKey);
    virtual void        v064();
    virtual void        v068();
    virtual void        v06c();
    virtual VObj174*    v070();   // 0x70
    virtual void        v074();
    virtual void        v078();
    virtual void        v07c();
    virtual void        v080();
    virtual void        v084();
    virtual void        v088();
    virtual void        v08c();
    virtual void        v090();
    virtual void        v094();
    virtual void        v098();
    virtual void        v09c();
    virtual void        v0a0();
    virtual void        v0a4();
    virtual void        v0a8();
    virtual void        v0ac();
    virtual void        v0b0();
    virtual void        v0b4();
    virtual void        v0b8();
    virtual void        v0bc();
    virtual void        v0c0();
    virtual void        v0c4();
    virtual void        v0c8();
    virtual void        v0cc();
    virtual void        v0d0();
    virtual void        v0d4();
    virtual void        v0d8();
    virtual void        v0dc();
    virtual void        v0e0();
    virtual void        v0e4();
    virtual void        v0e8();
    virtual void        v0ec();
    virtual void        v0f0();
    virtual void        v0f4();
    virtual void        v0f8();
    virtual void        v0fc();
    virtual void        v100();
    virtual void        v104();
    virtual void        v108();
    virtual void        v10c();
    virtual void        v110();
    virtual void        v114();
    virtual void        v118();
    virtual void        v11c();
    virtual void        v120();
    virtual void        v124();
    virtual void        v128();
    virtual void        v12c();
    virtual void        v130();
    virtual void        v134();
    virtual void        v138();
    virtual void        v13c();
    virtual void        v140();
    virtual void        v144();
    virtual void        v148();
    virtual void        v14c();
    virtual void        v150();
    virtual void        v154();
    virtual void        v158();
    virtual void        v15c();
    virtual void        v160();
    virtual void        v164();
    virtual void        v168();
    virtual void        v16c(cMWModel* pModel, bool bVisible);   // 0x16c
    virtual void        v170(cMWModel* pModel, bool bDelete);    // 0x170
};
struct cMessageServer {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void AddHandler(void* pHandler, uint32_t msgId);   // 0x24
};
struct cMWWorld : VObj174 {
};
struct cMWModel {
    cMWWorld*   mpWorld;        // 0x00
    int32_t     mState;         // 0x04
    char        pad08[2];
    uint16_t    mFlags;         // 0x0a
    char        pad0c[0x18 - 0x0c];
    float       mRadius;        // 0x18
    char        pad1c[0x40 - 0x1c];
    uint32_t    mRefCount;      // 0x40
    char        pad44[0x64 - 0x44];
    VObj174*    mpOwner;        // 0x64

    void AddRef() { mRefCount++; }
    void Release();
};
inline void cMWModel::Release()
{
    if (mRefCount > 1) { mRefCount--; return; }
    mpWorld->v170(this, mState < 0);
}
template <typename T>
struct RefPtr {
    T* mPtr;
    RefPtr() : mPtr(0) {}
    RefPtr(T* p) : mPtr(p) { if (mPtr) mPtr->AddRef(); }
    ~RefPtr() { T* p = mPtr; if (p) p->Release(); }
    RefPtr& operator=(T* p)
    {
        T* pOld = mPtr;
        if (p != pOld) {
            if (p) p->AddRef();
            mPtr = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
struct RawPtrVec {
    void**      mpBegin;
    void**      mpEnd;
    void**      mpCapacity;
    struct Alloc { char* mpName; uint32_t mFlags; } mAllocator;
    void erase(void** pFirst, void** pLast);   // 0x00e25bd0
};
struct cProperty {
    char      pad00[0x12];
    uint16_t  mType;            // 0x12
    uint32_t* GetUInt();        // 0x0041ea00
    float*    GetFloat();       // 0x0041ea70
};
VObj174*     SP_PropertyManager();                       // 0x0067de30
VObj174*     SP_ObjectTemplateDB();                      // 0x0067cb40
bool         SP_GetPropertyAsKey(void* pList, uint32_t key, void* pDst);        // 0x006a1250
bool         SP_GetPropertyAsText(void* pList, uint32_t key, void* pDst);       // 0x006a1360
bool         SP_GetPropertyAsUint32Array(void* pList, uint32_t key, uint32_t& dstCount, void** pDst); // 0x006a0840
VObj174*     GetUniverseContext();                      // 0x01021080
cMessageServer* MessageServer();                        // 0x0067dcc0
struct cLocalizedString {
    char mData[0x14];
    cLocalizedString();                                  // 0x006b5060
    ~cLocalizedString();                                 // 0x006b5240
    cLocalizedString& operator=(const cLocalizedString&); // 0x006b5430
};
enum SpaceInventoryItemType {
    kItemNone = 0,
    kItemPlant = 1,
    kItemTool = 2,
    kItemCargoSlot = 3,
    kItemTradingObject = 4,
    kItemMultiDeliveryObject = 5,
    kItemSentient = 6,
};
class cSpaceInventoryItem;
struct cItemSerializable;
class cPropertyList : public VObj174 {
public:
    bool GetProperty(uint32_t key, cProperty** out) { return v024(key, out); }
};
struct ItemRefCount {
    virtual ~ItemRefCount();                             // 0x00
    virtual void AddRef();                               // 0x04
    virtual void Release();                              // 0x08
    virtual int  GetReferenceCount();                    // 0x0c
    virtual uint32_t GetType();                          // 0x10
    virtual void SetItemID(const ResourceKey& key);      // 0x14
    virtual const ResourceKey& GetItemID();              // 0x18
    virtual uint32_t GetPropertyListParent(uint32_t key, VObj174** out); // 0x1c
    virtual bool IsCargoType();                          // 0x20
    virtual void Duplicate(cSpaceInventoryItem** pDst);  // 0x24
    virtual void v28();                                  // 0x28
    virtual void v2c();                                  // 0x2c
    virtual ResourceKey GetImageID();                    // 0x30
    virtual bool GetImageColors(uint32_t& dstCount, void** pDst);   // 0x34
    virtual ResourceKey GetPanelID();                    // 0x38
    virtual bool GetItemCount(uint32_t& dst);            // 0x3c
    virtual bool func40h();                              // 0x40
    virtual void v44();                                  // 0x44
    virtual void v48();                                  // 0x48
    virtual void ParseProp();                            // 0x4c

    int32_t mRefCount;                                   // 0x04
};
struct ItemHandler {
    virtual void h00();                                  // 0x00
    virtual bool HandleMessage(uint32_t msgId, void* msg); // 0x04
};
struct cItemSerializable {
    virtual void v00();                                  // 0x00
    virtual void v04();                                  // 0x04
    virtual void v08();                                  // 0x08
    virtual void* Cast(uint32_t typeID);                 // 0x0c
    virtual void v10();                                  // 0x10
    virtual void v14();                                  // 0x14
    virtual void v18();                                  // 0x18
    virtual bool Write(void* pStream);                   // 0x1c
    virtual bool Read(void* pStream);                    // 0x20
};
class cSpaceInventoryItem : public ItemRefCount, public ItemHandler, public cItemSerializable {
public:
    /* 0x10 */ uint32_t  mItemCount;
    /* 0x14 */ SpaceInventoryItemType mItemType;
    /* 0x18 */ uint32_t  mItemCost;
    /* 0x1c */ bool      mbIsUnique;
    /* 0x20 */ uint32_t  mPoliticalId;
    /* 0x24 */ uint32_t  mItemPosition;
    /* 0x28 */ bool      mbIsActive;
    /* 0x2c */ RefPtr<cSpaceInventoryItem> mpCargoSlot;
    /* 0x30 */ RefPtr<cPropertyList> mpPropList;
    /* 0x34 */ cLocalizedString mDescription;
    /* 0x48 */ cLocalizedString mDetailDescription;
    /* 0x5c */ ResourceKey mItemID;
    /* 0x68 */ cMessageServer* mpMessageManager;
    /* 0x6c */ ItemHandler* mpMessageListener;
    /* 0x70 */ uint32_t* mpMessageIDs;
    /* 0x74 */ uint32_t  mNumMessageIDs;
    /* 0x78 */ int32_t   field_78;

    cSpaceInventoryItem();
    ~cSpaceInventoryItem();

    cSpaceInventoryItem& operator=(const cSpaceInventoryItem& src);
    void SetPropList(cPropertyList* pPropList);

    void* Cast(uint32_t typeID);
    bool IsCargoType();
    void Duplicate(cSpaceInventoryItem** pDst);
    ResourceKey GetImageID();
    bool GetImageColors(uint32_t& dstCount, void** pDst);
    ResourceKey GetPanelID();
    bool GetItemCount(uint32_t& dst);
    bool func40h();
    void ParseProp();
    bool HandleMessage(uint32_t msgId, void* msg);
    bool Write(void* pStream);
    bool Read(void* pStream);
};
struct cItemMsg {
    char     pad00[0x18];
    uint32_t mInstanceID;       // 0x18
};
struct cISerializableObject {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
    virtual void v050();
};
struct cRefCountV {
    virtual void r00();
    virtual void r04();
};
struct cGameData : cISerializableObject, cRefCountV {
    cGameData();
    bool Write(void* pStream);                           // 0x00b18590
};
class cSpaceInventory : public cGameData {
public:
    /* 0x08 */ char pad08[0x34 - 0x08];
    /* 0x34 */ RawPtrVec mInventoryItems;
    /* 0x48 */ int32_t   mMaxItemCountPerItem;

    cSpaceInventory();

    virtual void func54h();                              // 0x54
    virtual void SetMaxCargoAmount(int amount);          // 0x58
    virtual uint32_t GetItemCount();                     // 0x5c
    virtual cSpaceInventoryItem* GetItem(uint32_t index); // 0x60
    virtual int  IndexOf(SpaceInventoryItemType type, const ResourceKey& id);  // 0x64
    virtual cSpaceInventoryItem* GetTool(const ResourceKey& id);               // 0x68
    virtual int  IndexOfNthItem(SpaceInventoryItemType type, uint32_t nth);    // 0x6c
    virtual bool HasItem(SpaceInventoryItemType type, const ResourceKey& id);  // 0x70
    virtual bool HasTool(const ResourceKey& id);                               // 0x74
    virtual bool RemoveItem(cSpaceInventoryItem* pItem);                       // 0x78
    virtual void func7Ch();                                                    // 0x7c
    virtual void AddItem(cSpaceInventoryItem* pItem);                          // 0x80
    virtual cSpaceInventoryItem* GetItemByCargoSlot(cSpaceInventoryItem* pSlot);// 0x84
    virtual uint32_t GetCargoSlotsCount();                                     // 0x88
    virtual uint32_t GetAvailableCargoSlotsCount();                            // 0x8c
    virtual bool GetFreeCargoSlot(cSpaceInventoryItem*& pDst);                 // 0x90
    virtual void AddCargoSlots(uint32_t count);                                // 0x94
    virtual bool CargoSlotIsFree(cSpaceInventoryItem* pSlot);                  // 0x98

    bool Write(void* pStream);
};
struct cVarListSerializer {
    char mData[0xa14];
    cVarListSerializer(void* pObject, void** pList, uint32_t version);  // 0x00692f90
    bool Serialize(void* pStream);                                      // 0x00692900
    bool Read(void* pStream);                                           // 0x00693e10
};
// ---- items of slice s00c86aa0 end

// ---- items of slice s00c87be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);
struct cResource {
    virtual void v00();     // 0x00
    virtual void AddRef();  // 0x04
    virtual void Release(); // 0x08
};
struct IResourceManager {
    virtual void v0();      // 0x00
    virtual void v1();      // 0x04
    virtual void v2();      // 0x08
    virtual bool IsLoaded(const ResourceKey& key, void* a, void* b, void* c, void* d, void* e); // 0x0c
};
IResourceManager* GetManager();                 // 0x0067dcd0
struct ToolMethods {
    bool ToolCheck();               // 0x0104cbc0
    int  ToolCount();               // 0x00a02d30
    void ToolSetCount(int n);       // 0x0104cc00
    void ToolSetCount2(int n);      // 0x0104cbd0
};
void FUN_00ba57f0(const ResourceKey& key, int action);  // 0x00ba57f0
void FUN_00ba5650(const ResourceKey& key, int action);  // 0x00ba5650
struct VObj174_s00c8_7be0 {
virtual void     v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void     v010();
virtual void v014();
virtual VObj174_s00c8_7be0* v018();
virtual VObj174_s00c8_7be0* v01c();
virtual VObj174_s00c8_7be0* v020();
virtual void v024();
virtual void v028();
virtual float* v02c();
virtual void     v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void     v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual VObj174_s00c8_7be0* v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void     v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void     v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void     v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual bool     v090(void** out);
virtual void v094();
virtual bool v098(void* r);
virtual void v09c();
virtual void     v0a0();
virtual void v0a4();
virtual void v0a8();
virtual unsigned int v0ac();
virtual void     v0b0();
virtual void v0b4();
virtual VObj174_s00c8_7be0* v0b8(uint32_t id, uint32_t arg);
virtual bool     v0bc();
virtual void v0c0();
virtual void v0c4();
    void GetCameraLocationInfo(void* pos, void* a, void* b, void* c);   // 0x007c3d30
};
struct cSpaceInventoryItem_s00c8_7be0;
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) throw() : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() throw() { T* p = mpObject; if (p) p->Release(); }
    AutoRefCount* Reset();                  // 0x00c463d0
};
template <class T> struct RefPtr_s00c8_7be0 {
    T* mPtr;
    RefPtr_s00c8_7be0() : mPtr(0) {}
    RefPtr_s00c8_7be0(T* p) : mPtr(p) { if (mPtr) mPtr->AddRef(); }
    ~RefPtr_s00c8_7be0() { T* p = mPtr; if (p) p->Release(); }
    RefPtr_s00c8_7be0& operator=(T* p) {
        T* pOld = mPtr;
        if (p != pOld) {
            if (p) p->AddRef();
            mPtr = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
struct ItemRefCount_s00c8_7be0 {
    virtual ~ItemRefCount_s00c8_7be0();                                    // 0x00
    virtual void AddRef() throw();                              // 0x04
    virtual void Release() throw();                             // 0x08
    virtual int  GetReferenceCount();                           // 0x0c
    virtual uint32_t GetType();                                 // 0x10
    virtual void SetItemID(const ResourceKey& key) throw();     // 0x14
    virtual const ResourceKey& GetItemID();                     // 0x18
    virtual void v1c();                                         // 0x1c
    virtual bool IsCargoType();                                 // 0x20
    virtual void Duplicate(AutoRefCount<cSpaceInventoryItem_s00c8_7be0>* pDst); // 0x24
    int32_t mRefCount;                                          // 0x04
};
class cSpaceInventoryItem_s00c8_7be0 : public ItemRefCount_s00c8_7be0, public ItemHandler, public cItemSerializable {
public:
    uint32_t mItemCount;                       // 0x10
    uint32_t mItemType;                        // 0x14
    uint32_t mItemCost;                        // 0x18
    bool     mbIsUnique;                       // 0x1c
    uint32_t mPoliticalId;                     // 0x20
    uint32_t mItemPosition;                    // 0x24
    bool     mbIsActive;                       // 0x28
    RefPtr_s00c8_7be0<cResource> mpCargoSlot;             // 0x2c
    void*    mpPropList;                       // 0x30
    char     pad34[0x7c - 0x34];               // 0x34..0x7c (mItemID key lives at 0x5c)
    cSpaceInventoryItem_s00c8_7be0() throw();
};
struct InvVec {
    cSpaceInventoryItem_s00c8_7be0** mpBegin;   // 0x00
    cSpaceInventoryItem_s00c8_7be0** mpEnd;     // 0x04
    cSpaceInventoryItem_s00c8_7be0** mpCapacity;// 0x08
    struct Alloc { char* mpName; uint32_t mFlags; } mAllocator;  // 0x0c
    ~InvVec() throw();                                      // 0x005c7f10
    void InsertAt(cSpaceInventoryItem_s00c8_7be0** p, void* v) throw(); // 0x00f14270
    cSpaceInventoryItem_s00c8_7be0** Erase(cSpaceInventoryItem_s00c8_7be0** first, cSpaceInventoryItem_s00c8_7be0** last); // 0x005c2170
    __forceinline void push_back(cSpaceInventoryItem_s00c8_7be0* p) {
        AutoRefCount<cSpaceInventoryItem_s00c8_7be0> value(p);
        if (mpEnd < mpCapacity) {
            AutoRefCount<cSpaceInventoryItem_s00c8_7be0>* pSlot = (AutoRefCount<cSpaceInventoryItem_s00c8_7be0>*)mpEnd++;
            pSlot->mpObject = p;
            if (p) p->AddRef();
        } else {
            InsertAt(mpEnd, &value);
        }
    }
};
cSpaceInventoryItem_s00c8_7be0** VecDoCopy(cSpaceInventoryItem_s00c8_7be0** first, cSpaceInventoryItem_s00c8_7be0** last,
                                cSpaceInventoryItem_s00c8_7be0** result);   // 0x0062ffd0
struct ItemPtrRef {
    cSpaceInventoryItem_s00c8_7be0* mpObject;
    ItemPtrRef(cSpaceInventoryItem_s00c8_7be0* p) throw() { mpObject = p; p->AddRef(); }
};
struct cISerializableObject_s00c8_7be0 {
    virtual ~cISerializableObject_s00c8_7be0();                            // 0x00
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
    virtual void v050();
};
struct cRefCountV_s00c8_7be0 {
    virtual ~cRefCountV_s00c8_7be0();                                      // 0x00
    virtual void r04();                                         // 0x04
};
struct cGameData_s00c8_7be0 : cISerializableObject_s00c8_7be0, cRefCountV_s00c8_7be0 {
    virtual ~cGameData_s00c8_7be0();                                       // 0x00b184c0
    bool Read(void* pStream);                                   // 0x00b18600
    bool Write(void* pStream);                                  // 0x00b18590
};
class cSpaceInventory_s00c8_7be0 : public cGameData_s00c8_7be0 {
public:
    char    pad08[0x34 - 0x08];
    InvVec  mInventoryItems;            // 0x34
    int32_t mMaxItemCountPerItem;       // 0x48

    virtual ~cSpaceInventory_s00c8_7be0();
    virtual void func54h();                                        // 0x54
    virtual void SetMaxCargoAmount(int amount);                    // 0x58
    virtual uint32_t GetItemCount();                               // 0x5c
    virtual cSpaceInventoryItem_s00c8_7be0* GetItem(uint32_t index);          // 0x60
    virtual int  IndexOf(uint32_t type, const ResourceKey& id);    // 0x64 0x00c87270
    virtual cSpaceInventoryItem_s00c8_7be0* GetTool(const ResourceKey& id);   // 0x68 0x00c86ff0
    virtual int  IndexOfNthItem(uint32_t type, uint32_t nth);      // 0x6c 0x00c872e0
    virtual bool HasItem(uint32_t type, const ResourceKey& id);    // 0x70 0x00c87320
    virtual bool HasTool(const ResourceKey& id);                   // 0x74 0x00c87020
    virtual bool RemoveItem(cSpaceInventoryItem_s00c8_7be0* pItem);           // 0x78
    virtual bool func7Ch();                                        // 0x7c
    virtual bool AddItem(cSpaceInventoryItem_s00c8_7be0* pItem, cResource* pResource, bool bAdd); // 0x80
    virtual cSpaceInventoryItem_s00c8_7be0* GetItemByCargoSlot(cSpaceInventoryItem_s00c8_7be0* pSlot);// 0x84 0x00c87390
    virtual uint32_t GetCargoSlotsCount();                         // 0x88 0x00c87420
    virtual uint32_t GetAvailableCargoSlotsCount();                // 0x8c 0x00c873d0
    virtual bool GetFreeCargoSlot(cSpaceInventoryItem_s00c8_7be0*& pDst);     // 0x90 0x00c87450
    virtual void AddCargoSlots(int count);                         // 0x94
    virtual bool CargoSlotIsFree(void* pSlot);                     // 0x98 0x00c874a0

    bool func40h();
    bool TakeFromInventory(uint32_t index, AutoRefCount<cSpaceInventoryItem_s00c8_7be0>* pOut, int amount);
    bool Read(void* pStream);
};
struct cVarListSerializer_s00c8_7be0 {
    uint32_t mData[0xa14 / 4];
    cVarListSerializer_s00c8_7be0(void* pObject, void** pList, uint32_t version);  // 0x00692f90
    bool Serialize(void* pStream);                                      // 0x00692900
    bool Read(void* pStream);                                           // 0x00693e10
};
// ---- items of slice s00c87be0 end

// ---- items of slice s0104bcc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int                i32;
void  __cdecl GetPropertyAsIntArray(u32 id, u32 tag, i32* pCount, void** ppArr); // 0x006a07d0
namespace SP {
struct cSPSpaceInventoryItem_s0104_bcc0;
}
namespace SP {
struct cSPSpaceInventoryItem_s0104_bcc0 {
    // Retail reads both arguments from the stack and ends in a plain `ret`,
    // so this is a static (cdecl) member despite the stale PDB `thiscall` name.
    static void UpdateTuning(u32 propId, u32* out);            // 0x0104c120
};
}
// ---- items of slice s0104bcc0 end

// @ 0x00c86f10
void* cSpaceInventoryItem::Cast(uint32_t typeID)
{
    if (typeID == 0x707459dd)
        return static_cast<cSpaceInventoryItem*>(this);
    if (typeID == 0x179c807)
        return static_cast<cItemSerializable*>(this);
    return 0;
}

// @ 0x00c86f40
bool cSpaceInventoryItem::IsCargoType()
{
    switch (mItemType) {
    case kItemNone:
        return false;
    case kItemPlant:
    case kItemTool:
    case kItemTradingObject:
    case kItemMultiDeliveryObject:
    case kItemSentient:
        return true;
    default:
        return false;
    }
}

// @ 0x00c86f90
bool cSpaceInventoryItem::GetItemCount(uint32_t& dst)
{
    dst = mItemCount;
    return true;
}

// @ 0x00c86fa0
bool cSpaceInventoryItem::func40h()
{
    return GetUniverseContext() == 0;
}

// @ 0x00c86ff0
cSpaceInventoryItem* cSpaceInventory::GetTool(const ResourceKey& id)
{
    int index = IndexOf(kItemTool, id);
    if (index == -1)
        return 0;
    return GetItem(index);
}

// @ 0x00c87020
bool cSpaceInventory::HasTool(const ResourceKey& id)
{
    return HasItem(kItemTool, id);
}

// @ 0x00c87090
bool WriteSingleItem(void* pStream, cSpaceInventoryItem** ppItem)
{
    if (*ppItem != 0)
        (*ppItem)->Write(pStream);
    return true;
}

// @ 0x00c870b0
cSpaceInventoryItem& cSpaceInventoryItem::operator=(const cSpaceInventoryItem& src)
{
    if (this != &src) {
        mItemID = src.mItemID;
        mItemCount = src.mItemCount;
        mItemType = src.mItemType;
        mDescription = src.mDescription;
        mDetailDescription = src.mDetailDescription;
        mpPropList = src.mpPropList.mPtr;
        mPoliticalId = src.mPoliticalId;
        mpCargoSlot = 0;
    }
    return *this;
}

// @ 0x00c87140
bool cSpaceInventoryItem::HandleMessage(uint32_t msgId, void* pMsg)
{
    if (msgId == 0xf62def && ((cItemMsg*)pMsg)->mInstanceID == mItemID.mInstanceID) {
        static_cast<cSpaceInventoryItem*>(this)->ParseProp();
    }
    return false;
}

// @ 0x00c87170
ResourceKey cSpaceInventoryItem::GetImageID()
{
    ResourceKey key;
    key.mInstanceID = 0;
    key.mTypeID = 0;
    key.mGroupID = 0;
    cPropertyList* pList = mpPropList.mPtr;
    if (SP_GetPropertyAsKey(pList, 0x3068d95c, &key))
        key.mTypeID = 0x2f7d0004;
    return key;
}

// @ 0x00c871b0
bool cSpaceInventoryItem::GetImageColors(uint32_t& dstCount, void** pDst)
{
    return SP_GetPropertyAsUint32Array(mpPropList.mPtr, 0xadc0291e, dstCount, pDst);
}

// @ 0x00c871d0
ResourceKey cSpaceInventoryItem::GetPanelID()
{
    ResourceKey key;
    key.mInstanceID = 0;
    key.mTypeID = 0;
    key.mGroupID = 0;
    if (IsCargoType()) {
        key = kCargoPanelID;
        return key;
    }
    cPropertyList* pList = mpPropList.mPtr;
    if (SP_GetPropertyAsKey(pList, 0xa6a37fc4, &key)) {
        key.mTypeID = 0xb1b104;
        key.mGroupID = 0x5f4d5e7;
    }
    return key;
}

// @ 0x00c87270
int cSpaceInventory::IndexOf(SpaceInventoryItemType type, const ResourceKey& id)
{
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)mInventoryItems.mpBegin[i];
        if (pItem->mItemType == type) {
            const ResourceKey& key = pItem->GetItemID();
            if (key.mInstanceID == id.mInstanceID && key.mTypeID == id.mTypeID && key.mGroupID == id.mGroupID)
                return i;
        }
    }
    return -1;
}

// @ 0x00c872e0
int cSpaceInventory::IndexOfNthItem(SpaceInventoryItemType type, uint32_t nth)
{
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)mInventoryItems.mpBegin[i];
        if (pItem->mItemType == type) {
            if (nth == 0)
                return i;
            --nth;
        }
    }
    return -1;
}

// @ 0x00c87320
bool cSpaceInventory::HasItem(SpaceInventoryItemType type, const ResourceKey& id)
{
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)mInventoryItems.mpBegin[i];
        if (pItem->mItemType == type) {
            const ResourceKey& key = pItem->GetItemID();
            if (key.mInstanceID == id.mInstanceID && key.mTypeID == id.mTypeID && key.mGroupID == id.mGroupID)
                return true;
        }
    }
    return false;
}

// @ 0x00c87390
cSpaceInventoryItem* cSpaceInventory::GetItemByCargoSlot(cSpaceInventoryItem* pSlot)
{
    if (pSlot != 0) {
        int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
        for (int i = 0; i < count; i++) {
            cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)mInventoryItems.mpBegin[i];
            if (pItem->mpCargoSlot.mPtr == pSlot)
                return pItem;
        }
    }
    return 0;
}

// @ 0x00c873d0
uint32_t cSpaceInventory::GetAvailableCargoSlotsCount()
{
    uint32_t available = 0;
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)mInventoryItems.mpBegin[i];
        if (pItem->mItemType == kItemCargoSlot && CargoSlotIsFree(pItem))
            ++available;
    }
    return available;
}

// @ 0x00c87420
uint32_t cSpaceInventory::GetCargoSlotsCount()
{
    uint32_t slots = 0;
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)mInventoryItems.mpBegin[i];
        if (pItem->mItemType == kItemCargoSlot)
            ++slots;
    }
    return slots;
}

// @ 0x00c87450
bool cSpaceInventory::GetFreeCargoSlot(cSpaceInventoryItem*& pDst)
{
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)mInventoryItems.mpBegin[i];
        if (pItem->mItemType == kItemCargoSlot && CargoSlotIsFree(pItem)) {
            pDst = pItem;
            return true;
        }
    }
    return false;
}

// @ 0x00c874a0
bool cSpaceInventory::CargoSlotIsFree(cSpaceInventoryItem* pSlot)
{
    if (pSlot == 0)
        return false;
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)mInventoryItems.mpBegin[i];
        if (pItem->mpCargoSlot.mPtr == pSlot)
            return false;
    }
    return true;
}

// @ 0x00c874f0
bool cSpaceInventory::Write(void* pStream)
{
    VObj174* pIo = ((VObj174*)pStream)->v020()->v018();
    uint32_t type = 0xb075dec5;
    EA::IO::WriteUint32(pIo, &type, 1, 0);
    bool ok = cGameData::Write(pStream);
    cVarListSerializer serializer(this, &kSpaceInventorySerializerList, 0x1a80d26);
    if (ok) {
        if (serializer.Serialize(pStream))
            return true;
    }
    return false;
}

// @ 0x00c87580
bool cSpaceInventoryItem::Write(void* pStream)
{
    VObj174* pIo = ((VObj174*)pStream)->v020()->v018();
    uint32_t type = 0x707459dd;
    EA::IO::WriteUint32(pIo, &type, 1, 0);
    cSpaceInventoryItem* pItem = static_cast<cSpaceInventoryItem*>(static_cast<cItemSerializable*>(this));
    cVarListSerializer serializer(pItem, &kItemSerializerList, 0x1a80d26);
    return serializer.Serialize(pStream) != 0;
}

// @ 0x00c875f0
bool WriteItemList(void* pStream, RawPtrVec* pItems)
{
    void** pEnd = pItems->mpEnd;
    for (void** pp = pItems->mpBegin; pp != pEnd; ++pp) {
        cSpaceInventoryItem* pItem = (cSpaceInventoryItem*)*pp;
        if (pItem)
            pItem->Write(pStream);
    }
    return true;
}

// @ 0x00c87660
cSpaceInventoryItem::cSpaceInventoryItem()
: mItemCount(1),
      mItemType(kItemTool),
      mItemCost(0),
      mbIsUnique(false),
      mPoliticalId(0xffffffff),
      mItemPosition(0xffffffff),
      mbIsActive(false),
      mpCargoSlot(0),
      mpPropList(0),
      mItemID(kDefaultItemID),
      mpMessageManager(0),
      mpMessageListener(0),
      mpMessageIDs(0),
      mNumMessageIDs(0),
      field_78(0)
{
    mpMessageManager = MessageServer();
    mpMessageListener = static_cast<ItemHandler*>(this);
    mpMessageIDs = kItemMessageIDs;
    mNumMessageIDs = 1;
    field_78 = 0;
    if (mpMessageManager != 0 && mpMessageListener != 0)
        mpMessageManager->AddHandler(mpMessageListener, 0xf62def);
}

// @ 0x00c87770
cSpaceInventoryItem::~cSpaceInventoryItem()
{
    cMessageServer* pServer = mpMessageManager;
    if (pServer != 0) {
        mpMessageManager = 0;
        EA::Messaging::RemoveHandler(pServer, mpMessageListener, mpMessageIDs, mNumMessageIDs, field_78);
    }
}

// @ 0x00c877f0
void cSpaceInventoryItem::SetPropList(cPropertyList* pPropList)
{
    cPropertyList* pOld = mpPropList.mPtr;
    if (pPropList != pOld) {
        if (pPropList) pPropList->AddRef();
        mpPropList.mPtr = pPropList;
        if (pOld) pOld->Release();
    }
    if (pPropList != 0) {
        SP_GetPropertyAsText(pPropList, 0x3068d95d, &mDescription);
        SP_GetPropertyAsText(pPropList, 0x4cad19b, &mDetailDescription);
        cProperty* pProp;
        if (pPropList->v024(0x1bfc1dee, &pProp) && pProp->mType == 0xa)
            mItemPosition = *pProp->GetUInt();
        ParseProp();
    }
}

// @ 0x00c87880
void cSpaceInventoryItem::Duplicate(cSpaceInventoryItem** pDst)
{
    cSpaceInventoryItem* pNew = new ("Simulator/cSpaceInventoryItem", 0, 0, 0, 0) cSpaceInventoryItem;
    *pNew = *this;
    pNew->AddRef();
    *pDst = pNew;
}

// @ 0x00c878d0
void CreateMultiDeliveryObject(const ResourceKey& key, cSpaceInventoryItem** pDst)
{
    cSpaceInventoryItem* pItem = new ("Simulator/cSpaceInventoryItem", 0, 0, 0, 0) cSpaceInventoryItem;
    if (pItem == 0) {
        *pDst = 0;
        return;
    }
    pItem->mItemType = kItemMultiDeliveryObject;
    pItem->SetItemID(key);
    VObj174* pPropList = 0;
    VObj174* pPropertyManager = SP_PropertyManager();
    if (pPropList) { VObj174* pOld = pPropList; pPropList = 0; pOld->Release(); }
    pPropertyManager->v02c(key.mInstanceID, 0x37d494e, &pPropList);
    pItem->SetPropList((cPropertyList*)pPropList);
    pItem->AddRef();
    if (pPropList) pPropList->Release();
    *pDst = pItem;
}

// @ 0x00c879a0
bool cSpaceInventoryItem::Read(void* pStream)
{
    uint32_t version = 0;
    VObj174* pIo = ((VObj174*)pStream)->v020()->v018();
    EA::IO::ReadInt32(pIo, &version, 1, 0);
    cSpaceInventoryItem* pItem = static_cast<cSpaceInventoryItem*>(static_cast<cItemSerializable*>(this));
    cVarListSerializer serializer(pItem, &kItemSerializerList, 0x1a80d26);
    bool ok = serializer.Read(pStream) != 0;
    VObj174* pPropList = 0;
    switch (mItemType) {
    case kItemPlant:
    case kItemSentient:
        SP_ObjectTemplateDB()->v060(&pItem->GetItemID());
        break;
    case kItemTool:
        pPropList = 0;
        SP_PropertyManager()->v02c(pItem->GetPropertyListParent(0x30608f0b, &pPropList));
        break;
    case kItemTradingObject:
        pPropList = 0;
        SP_PropertyManager()->v02c(pItem->GetPropertyListParent(0x34d97fa, &pPropList));
        break;
    case kItemMultiDeliveryObject:
        pPropList = 0;
        SP_PropertyManager()->v02c(pItem->GetPropertyListParent(0x37d494e, &pPropList));
        break;
    default:
        break;
    }
    pItem->SetPropList((cPropertyList*)pPropList);
    if (pPropList) pPropList->Release();
    return ok;
}

// @ 0x00c87b20
cSpaceInventory::cSpaceInventory()
{
    mInventoryItems.mpBegin = 0;
    mInventoryItems.mpEnd = 0;
    mInventoryItems.mpCapacity = 0;
    mMaxItemCountPerItem = -1;
}

// @ 0x00c87be0
cSpaceInventory_s00c8_7be0::~cSpaceInventory_s00c8_7be0()
{
}

// @ 0x00c87cc0
bool cSpaceInventory_s00c8_7be0::func40h()
{
    cSpaceInventoryItem_s00c8_7be0** p = mInventoryItems.mpBegin;
    if (p == mInventoryItems.mpEnd)
        return true;
    cSpaceInventoryItem_s00c8_7be0** next = p + 1;
    for (;;) {
        cSpaceInventoryItem_s00c8_7be0* pItem = *p;
        const ResourceKey& key = pItem->GetItemID();
        if (key.mTypeID != 0 && key.mGroupID != 0 && key.mInstanceID != 0) {
            IResourceManager* pManager = GetManager();
            if (!pManager->IsLoaded(pItem->GetItemID(), 0, 0, 0, 0, 0)) {
                if (next < mInventoryItems.mpEnd)
                    VecDoCopy(next, mInventoryItems.mpEnd, p);
                mInventoryItems.mpEnd--;
                cSpaceInventoryItem_s00c8_7be0* pLast = *mInventoryItems.mpEnd;
                if (pLast)
                    pLast->Release();
                if (p == mInventoryItems.mpEnd)
                    break;
                continue;
            }
        }
        p = next;
        next = p + 1;
        if (p == mInventoryItems.mpEnd)
            break;
    }
    return true;
}

// @ 0x00c87d80
bool cSpaceInventory_s00c8_7be0::RemoveItem(cSpaceInventoryItem_s00c8_7be0* pItem)
{
    cSpaceInventoryItem_s00c8_7be0** p = mInventoryItems.mpBegin;
    cSpaceInventoryItem_s00c8_7be0** end = mInventoryItems.mpEnd;
    while (p != end) {
        if (*p == pItem)
            goto found;
        ++p;
    }
    return false;
found:
    {
        cSpaceInventoryItem_s00c8_7be0* pFound = *p;
        pFound->mpCargoSlot = 0;
        if (p + 1 < mInventoryItems.mpEnd)
            VecDoCopy(p + 1, mInventoryItems.mpEnd, p);
        mInventoryItems.mpEnd--;
        cSpaceInventoryItem_s00c8_7be0* pLast = *mInventoryItems.mpEnd;
        if (pLast)
            pLast->Release();
    }
    return true;
}

// @ 0x00c87df0
bool cSpaceInventory_s00c8_7be0::TakeFromInventory(uint32_t index, AutoRefCount<cSpaceInventoryItem_s00c8_7be0>* pOut, int amount)
{
    if (index >= (uint32_t)(mInventoryItems.mpEnd - mInventoryItems.mpBegin))
        return false;
    cSpaceInventoryItem_s00c8_7be0* pItem = mInventoryItems.mpBegin[index];
    if (pItem->mItemType == 2 && amount != -1) {
        cSpaceInventoryItem_s00c8_7be0* pTool = 0;
        if (pItem)
            pTool = (cSpaceInventoryItem_s00c8_7be0*)static_cast<cItemSerializable*>(pItem)->Cast(0x707459f0);
        cSpaceInventoryItem_s00c8_7be0* pOutItem = 0;
        if (pOut->mpObject)
            pOutItem = (cSpaceInventoryItem_s00c8_7be0*)static_cast<cItemSerializable*>(pOut->mpObject)->Cast(0x707459f0);
        if (((ToolMethods*)pTool)->ToolCheck()) {
            int n = ((ToolMethods*)pTool)->ToolCount();
            if (n >= amount)
                ((ToolMethods*)pTool)->ToolSetCount(amount);
            if (pOutItem)
                ((ToolMethods*)pOutItem)->ToolSetCount2(amount);
            return true;
        }
    }
    pItem = mInventoryItems.mpBegin[index];
    if (!pItem->mbIsUnique && amount != -1 && pItem->mItemCount != (uint32_t)amount) {
        if ((int)pItem->mItemCount > amount) {
            pItem->Duplicate(pOut->Reset());
            pOut->mpObject->mItemCount = amount;
            mInventoryItems.mpBegin[index]->mItemCount -= amount;
            return true;
        }
        return false;
    }
    cSpaceInventoryItem_s00c8_7be0* pOld = pOut->mpObject;
    if (pItem != pOld) {
        if (pItem) pItem->AddRef();
        pOut->mpObject = pItem;
        if (pOld) pOld->Release();
    }
    pOut->mpObject->mpCargoSlot = 0;
    {
        cSpaceInventoryItem_s00c8_7be0** p = mInventoryItems.mpBegin + index;
        if (p + 1 < mInventoryItems.mpEnd)
            VecDoCopy(p + 1, mInventoryItems.mpEnd, p);
        mInventoryItems.mpEnd--;
        cSpaceInventoryItem_s00c8_7be0* pLast = *mInventoryItems.mpEnd;
        if (pLast)
            pLast->Release();
    }
    return true;
}

// @ 0x00c88060
bool cSpaceInventory_s00c8_7be0::AddItem(cSpaceInventoryItem_s00c8_7be0* pItem, cResource* pResource, bool bAdd)
{
    cSpaceInventoryItem_s00c8_7be0** pp = mInventoryItems.mpBegin;
    while (pp != mInventoryItems.mpEnd) {
        if (*pp == pItem)
            break;
        ++pp;
    }
    if (pp != mInventoryItems.mpEnd)
        return false;
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem_s00c8_7be0* p = mInventoryItems.mpBegin[i];
        const ResourceKey& kB = pItem->GetItemID();
        const ResourceKey& kA = p->GetItemID();
        if (kA.mInstanceID == kB.mInstanceID && kA.mTypeID == kB.mTypeID &&
            kA.mGroupID == kB.mGroupID && p->mItemType == pItem->mItemType) {
            if (p->mItemType == 2) {
                cSpaceInventoryItem_s00c8_7be0* pToolA = (cSpaceInventoryItem_s00c8_7be0*)static_cast<cItemSerializable*>(p)->Cast(0x707459f0);
                cSpaceInventoryItem_s00c8_7be0* pToolB = (cSpaceInventoryItem_s00c8_7be0*)static_cast<cItemSerializable*>(pItem)->Cast(0x707459f0);
                if (((ToolMethods*)pToolA)->ToolCheck()) {
                    if (!bAdd)
                        return true;
                    int n = ((ToolMethods*)pToolB)->ToolCount();
                    ((ToolMethods*)pToolA)->ToolSetCount2(n);
                    return true;
                }
            }
            if (p->mbIsUnique)
                return false;
            if (mMaxItemCountPerItem != -1 && (int)p->mItemCount >= mMaxItemCountPerItem)
                return false;
            if (!bAdd)
                return true;
            p->mItemCount += pItem->mItemCount;
            if (mMaxItemCountPerItem != -1 && (int)p->mItemCount > mMaxItemCountPerItem) {
                pItem->mItemCount += mMaxItemCountPerItem - p->mItemCount;
                p->mItemCount = mMaxItemCountPerItem;
            }
            return true;
        }
    }
    if (pItem->mItemType == 0 || pItem->mItemType == 1 || pItem->mItemType == 6 ||
        pItem->mItemType == 4 || pItem->mItemType == 5) {
        if (pResource != 0) {
            if (!CargoSlotIsFree(pResource))
                return false;
            pItem->mpCargoSlot = pResource;
        } else {
            cSpaceInventoryItem_s00c8_7be0* pOut;
            if (!GetFreeCargoSlot(pOut))
                return false;
            pItem->mpCargoSlot = (cResource*)pOut;
        }
    }
    if (bAdd) {
        ItemPtrRef ref(pItem);
        if (mInventoryItems.mpEnd < mInventoryItems.mpCapacity) {
            AutoRefCount<cSpaceInventoryItem_s00c8_7be0>* pSlot = (AutoRefCount<cSpaceInventoryItem_s00c8_7be0>*)mInventoryItems.mpEnd++;
            if (pSlot) {
                pSlot->mpObject = pItem;
                pItem->AddRef();
            }
        } else {
            mInventoryItems.InsertAt(mInventoryItems.mpEnd, &ref);
        }
        ref.mpObject->Release();
        if (mMaxItemCountPerItem != -1 && (int)pItem->mItemCount > mMaxItemCountPerItem)
            pItem->mItemCount = mMaxItemCountPerItem;
        if (pItem->mItemType == 0)
            FUN_00ba57f0(pItem->GetItemID(), 3);
        else if (pItem->mItemType == 1)
            FUN_00ba5650(pItem->GetItemID(), 3);
    }
    return true;
}

// @ 0x00c88310
void cSpaceInventory_s00c8_7be0::AddCargoSlots(int count)
{
    if (count > 0) {
        InvVec* pVec = &mInventoryItems;
        int local = count;
        do {
            cSpaceInventoryItem_s00c8_7be0* pItem = new ("Simulator/cSpaceInventoryItem", 0, 0, 0, 0) cSpaceInventoryItem_s00c8_7be0;
            pItem->mItemType = 3;
            pItem->SetItemID(kDefaultItemID);
            pItem->mItemCount = 1;
            cSpaceInventoryItem_s00c8_7be0* pKeep = pItem;
            pItem->AddRef();
            if (pVec->mpEnd < pVec->mpCapacity) {
                AutoRefCount<cSpaceInventoryItem_s00c8_7be0>* pSlot = (AutoRefCount<cSpaceInventoryItem_s00c8_7be0>*)pVec->mpEnd++;
                if (pSlot) {
                    pSlot->mpObject = pItem;
                    pItem->AddRef();
                }
            } else {
                pVec->InsertAt(pVec->mpEnd, &pKeep);
                pItem = pKeep;
            }
            if (pItem)
                pItem->Release();
        } while (--local);
    }
}

// @ 0x00c883d0
bool cSpaceInventory_s00c8_7be0::Read(void* pStream)
{
    InvVec* pVec = &mInventoryItems;
    cSpaceInventoryItem_s00c8_7be0** pBegin = pVec->mpBegin;
    cSpaceInventoryItem_s00c8_7be0** pEnd = pVec->mpEnd;
    pVec->Erase(pBegin, pEnd);
    uint32_t version;
    VObj174_s00c8_7be0* pIo = ((VObj174_s00c8_7be0*)pStream)->v020()->v018();
    EA::IO::ReadInt32(pIo, &version, 1, 0);
    bool ok = cGameData_s00c8_7be0::Read(pStream);
    cVarListSerializer_s00c8_7be0 serializer(this, &kSpaceInventorySerializerList, 0x1a80d26);
    if (ok) {
        if (serializer.Read(pStream))
            return true;
    }
    return false;
}

// @ 0x0104c120
void SP::cSPSpaceInventoryItem_s0104_bcc0::UpdateTuning(u32 propId, u32* out)
{
    *out = 0;
    void* arr  = 0;
    i32  count = 0;
    GetPropertyAsIntArray(propId, 0x5e51b17, &count, &arr);
    for (i32 i = 0; i < count; i++) {
        i32 v = ((i32*)arr)[i];
        switch (v) {
        case 0xe7ca2d90: *out |= 0x20;   break;
        case 0xa13abc9f: *out |= 2;      break;
        case 0x9b8e862f: *out |= 0x80;   break;
        case 0x9f6db313: *out |= 0x10;   break;
        case 0xa6663355: *out |= 0x200;  break;
        case 0xc710b6e9: *out |= 0x40;   break;
        case 0x2dc69129: *out |= 1;      break;
        case 0x3e9c273b: *out |= 0x100;  break;
        case 0x476a98c7: *out |= 4;      break;
        case 0x4bf0fa5a: *out |= 0x400;  break;
        case 0x78bddf27: *out |= 8;      break;
        }
    }
}

// @ 0x01353800
void FUN_01353800(void)
{
    PropDesc d;
    d.mName = (const char*)0x1473734;
    d.mHash = 0x223eb9d;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xae3430;
    d.mFn28 = (void*)0xae3450;
    d.mFn2C = (void*)0x693150;
    d.mFn30 = (void*)0x695080;
    d.mFn34 = (void*)U_01353800_0_34;
    d.mFn38 = (void*)0xae5720;
    d.mType = 0x5c;
    *(PropDesc*)0x1579f50 = d;

    d.mName = (const char*)0x1473728;
    d.mHash = 0x223eb9e;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_1_24;
    d.mFn28 = (void*)U_01353800_1_28;
    d.mFn2C = (void*)U_01353800_1_2c;
    d.mFn30 = (void*)U_01353800_1_30;
    d.mFn34 = (void*)S3800_F34A;
    d.mFn38 = (void*)S3800_F38A;
    d.mType = 0x10;
    *(PropDesc*)0x1579f8c = d;

    d.mName = (const char*)0x147371c;
    d.mHash = 0x362aeb9;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_2_24;
    d.mFn28 = (void*)U_01353800_2_28;
    d.mFn2C = (void*)U_01353800_2_2c;
    d.mFn30 = (void*)U_01353800_2_30;
    d.mFn34 = (void*)S3800_F34A;
    d.mFn38 = (void*)S3800_F38A;
    d.mType = 0x14;
    *(PropDesc*)0x1579fc8 = d;

    d.mName = (const char*)0x1473710;
    d.mHash = 0x362aeba;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_3_24;
    d.mFn28 = (void*)U_01353800_3_28;
    d.mFn2C = (void*)U_01353800_3_2c;
    d.mFn30 = (void*)U_01353800_3_30;
    d.mFn34 = (void*)S3800_F34B;
    d.mFn38 = (void*)S3800_F38B;
    d.mType = 0x18;
    *(PropDesc*)0x157a004 = d;

    d.mName = (const char*)0x1473704;
    d.mHash = 0x362aebb;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_4_24;
    d.mFn28 = (void*)U_01353800_4_28;
    d.mFn2C = (void*)U_01353800_4_2c;
    d.mFn30 = (void*)U_01353800_4_30;
    d.mFn34 = (void*)U_01353800_4_34;
    d.mFn38 = (void*)U_01353800_4_38;
    d.mType = 0x1c;
    *(PropDesc*)0x157a040 = d;

    d.mName = (const char*)0x14736f8;
    d.mHash = 0x223eba1;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc87630;
    d.mFn28 = (void*)0xbd1780;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xc87090;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x2c;
    *(PropDesc*)0x157a07c = d;

    d.mName = (const char*)0x14736e8;
    d.mHash = 0x5d28f83;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_6_24;
    d.mFn28 = (void*)U_01353800_6_28;
    d.mFn2C = (void*)U_01353800_6_2c;
    d.mFn30 = (void*)U_01353800_6_30;
    d.mFn34 = (void*)S3800_F34B;
    d.mFn38 = (void*)S3800_F38B;
    d.mType = 0x20;
    *(PropDesc*)0x157a0b8 = d;

    d.mName = (const char*)0x14736d8;
    d.mHash = 0x61d7ac0;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_7_24;
    d.mFn28 = (void*)U_01353800_7_28;
    d.mFn2C = (void*)U_01353800_7_2c;
    d.mFn30 = (void*)U_01353800_7_30;
    d.mFn34 = (void*)S3800_F34B;
    d.mFn38 = (void*)S3800_F38B;
    d.mType = 0x24;
    *(PropDesc*)0x157a0f4 = d;

    d.mName = (const char*)0x14736cc;
    d.mHash = 0x61d7ac9;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_8_24;
    d.mFn28 = (void*)U_01353800_8_28;
    d.mFn2C = (void*)U_01353800_8_2c;
    d.mFn30 = (void*)U_01353800_8_30;
    d.mFn34 = (void*)U_01353800_8_34;
    d.mFn38 = (void*)U_01353800_8_38;
    d.mType = 0x28;
    *(PropDesc*)0x157a130 = d;
}
