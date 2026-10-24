// Slice s00c86aa0 -- Simulator cSolarSystem graphics toggles, cSpaceInventory and
// cSPSpaceInventoryItem (space inventory items).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ============================================================ imports
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);

namespace EA { namespace IO {
bool WriteUint32(void* pStream, const uint32_t* pData, uint32_t nCount, int endian);
bool ReadInt32(void* pStream, uint32_t* pData, uint32_t nCount, int endian);
}}

namespace EA { namespace Messaging {
void RemoveHandler(void* pServer, void* pHandler, uint32_t* pIds, uint32_t nCount, uint32_t extra);
}}

struct VObj174;
struct cMWModel;
struct ResourceKey;

// ============================================================ ResourceKey
struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};

extern ResourceKey kDefaultItemID;               // 0x01694cc4
extern ResourceKey kCargoPanelID;                // 0x01579eb0
extern uint32_t   kHitSphereModelGroup;          // 0x01694c1c
extern float      kRockyRadius;                  // 0x01579ea8
extern float      kGasGiantRadius;               // 0x01579eac
extern uint32_t   kItemMessageIDs[1];            // 0x01473528
extern void*      kItemSerializerList;           // 0x01579f50
extern void*      kSpaceInventorySerializerList; // 0x01579ed8

// ============================================================ generic engine object
// Slot names are the vtable byte offsets.
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

// Message server: only slot 0x24 (AddHandler) is used here.
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

// ============================================================ MW model / world
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
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { T* p = mpObject; if (p) p->Release(); }
};

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

void ModelVecDoInsertValue(cMWModel** pPos, AutoRefCount<cMWModel>* pValue);   // 0x00423c40
cMWModel** ModelVecDoCopy(cMWModel** pFirst, cMWModel** pLast, cMWModel** pResult); // 0x005f4e10
void ModelVecDoDestroyValues(cMWModel** pFirst, cMWModel** pLast);            // 0x005f3680

struct ModelVec {
    cMWModel**  mpBegin;
    cMWModel**  mpEnd;
    cMWModel**  mpCapacity;
    struct Alloc { char* mpName; uint32_t mFlags; } mAllocator;

    void push_back(cMWModel* p)
    {
        AutoRefCount<cMWModel> value(p);
        if (mpEnd < mpCapacity) {
            AutoRefCount<cMWModel>* pSlot = (AutoRefCount<cMWModel>*)mpEnd++;
            pSlot->mpObject = p;
            if (p) p->AddRef();
        } else {
            ModelVecDoInsertValue(mpEnd, &value);
        }
    }
    void clear()
    {
        cMWModel** pNewEnd = ModelVecDoCopy(mpEnd, mpEnd, mpBegin);
        ModelVecDoDestroyValues(pNewEnd, mpEnd);
        mpEnd -= (mpEnd - mpBegin);
    }
};

struct RawPtrVec {
    void**      mpBegin;
    void**      mpEnd;
    void**      mpCapacity;
    struct Alloc { char* mpName; uint32_t mFlags; } mAllocator;
    void erase(void** pFirst, void** pLast);   // 0x00e25bd0
};

// ============================================================ cPlanet
struct cPlanetSub {
    char        pad00[0x28];
    int32_t     m28;
};

class cPlanet {
public:
    char        pad00[0xd4];
    VObj174    mTransform;      // 0xd4
    char        padD8[0x13c - 0xd8];
    cPlanetSub* mp13c;          // 0x13c

    int  GetEntityType();               // 0x00c70880
    void SetPlanetVisibility(int vis);  // 0x00c719d0
};

bool PlanetIsMarkedForRemoval(cPlanet* pPlanet);  // 0x00c83e40

// ============================================================ property helpers
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

// ============================================================ cSolarSystem
class cSolarSystem {
public:
    char        pad00[0x0c];
    void*       mpStar;         // 0x0c
    RawPtrVec   mPlanets;       // 0x10
    RawPtrVec   mCelestialBodies; // 0x24
    VObj174*    mp38;           // 0x38
    VObj174*    mp3c;           // 0x3c
    ModelVec    mPtolemaicHitSpheres; // 0x40

    void ActivatePtolemaicHitSpheres(bool activate);
    void ActivateGraphics(bool activate);
    void Destroy();

    void  ActivateHitSpheres(bool activate);            // 0x00c83fd0
    void  ActivateEffects(bool activate, float value);  // 0x00c84620
    VObj174* GetModelManager();                         // 0x00b3d240
};

VObj174*     GetUniverseContext();                      // 0x01021080
cPlanet*     GetActivePlanet();                         // 0x01021260
cMessageServer* MessageServer();                        // 0x0067dcc0

// @ 0x00c86aa0
void cSolarSystem::ActivatePtolemaicHitSpheres(bool activate)
{
    if (!activate) {
        for (cMWModel** pp = mPtolemaicHitSpheres.mpBegin; pp != mPtolemaicHitSpheres.mpEnd; ++pp) {
            cMWModel* pModel = *pp;
            pModel->mpWorld->v16c(pModel, false);
        }
        return;
    }
    if (mPtolemaicHitSpheres.mpBegin != mPtolemaicHitSpheres.mpEnd) {
        for (cMWModel** pp = mPtolemaicHitSpheres.mpBegin; pp != mPtolemaicHitSpheres.mpEnd; ++pp) {
            cMWModel* pModel = *pp;
            pModel->mpWorld->v16c(pModel, true);
        }
        return;
    }

    VObj174* pModelManager = GetModelManager()->v070();
    cPlanet** ppPlanet = (cPlanet**)mPlanets.mpBegin;
    if (ppPlanet == (cPlanet**)mPlanets.mpEnd)
        return;
    do {
        cPlanet* pPlanet = *ppPlanet;
        if (pPlanet->GetEntityType() != 0) {
            cMWModel* pModel = pModelManager->v00c(0x2e81370, kHitSphereModelGroup, 0x10);
            VObj174* pTransform = pPlanet ? &pPlanet->mTransform : 0;
            VObj174* pOldOwner = pModel->mpOwner;
            if (pTransform != pOldOwner) {
                if (pTransform) pTransform->AddRef();
                pModel->mpOwner = pTransform;
                if (pOldOwner) pOldOwner->Release();
            }
            pModel->mFlags++;
            pModel->mRadius = (pPlanet->GetEntityType() == 1) ? kGasGiantRadius : kRockyRadius;
            mPtolemaicHitSpheres.push_back(pModel);
        }
        ++ppPlanet;
    } while (ppPlanet != (cPlanet**)mPlanets.mpEnd);
}

// @ 0x00c86c70
void cSolarSystem::ActivateGraphics(bool activate)
{
    if (activate) {
        float fValue = 1.0f;
        if (GetUniverseContext() == 0) {
            VObj174* pPropList = 0;
            VObj174* pPropertyManager = SP_PropertyManager();
            if (pPropList) { VObj174* pOld = pPropList; pPropList = 0; pOld->Release(); }
            pPropertyManager->v02c(0x272ddeda, 0x2ae0c7e, &pPropList);
            if (pPropList) {
                cProperty* pProp = 0;
                if (pPropList->v024(0x379762b, &pProp) && pProp->mType == 0xd)
                    fValue = *pProp->GetFloat();
            }
            cPlanet* pActivePlanet = GetActivePlanet();
            ActivateHitSpheres(false);
            ActivatePtolemaicHitSpheres(true);
            for (cPlanet** pp = (cPlanet**)mPlanets.mpBegin; pp != (cPlanet**)mPlanets.mpEnd; ++pp) {
                cPlanet* pPlanet = *pp;
                int vis;
                if (pPlanet == pActivePlanet) {
                    vis = 0;
                } else {
                    int t = pPlanet->mp13c->m28;
                    if (t != 0 && t != 1) {
                        vis = PlanetIsMarkedForRemoval(pPlanet) ? 2 : 3;
                    } else {
                        vis = 2;
                    }
                }
                pPlanet->SetPlanetVisibility(vis);
            }
            if (pPropList) pPropList->Release();
        } else {
            ActivateHitSpheres(true);
            for (cMWModel** pp = mPtolemaicHitSpheres.mpBegin; pp != mPtolemaicHitSpheres.mpEnd; ++pp) {
                cMWModel* pModel = *pp;
                pModel->mpWorld->v16c(pModel, false);
            }
            for (cPlanet** pp = (cPlanet**)mPlanets.mpBegin; pp != (cPlanet**)mPlanets.mpEnd; ++pp)
                (*pp)->SetPlanetVisibility(1);
        }
        ActivateEffects(true, fValue);
    } else {
        ActivateHitSpheres(false);
        for (cMWModel** pp = mPtolemaicHitSpheres.mpBegin; pp != mPtolemaicHitSpheres.mpEnd; ++pp) {
            cMWModel* pModel = *pp;
            pModel->mpWorld->v16c(pModel, false);
        }
        ActivateEffects(false, 1.0f);
        for (cPlanet** pp = (cPlanet**)mPlanets.mpBegin; pp != (cPlanet**)mPlanets.mpEnd; ++pp)
            (*pp)->SetPlanetVisibility(0);
    }
}

// @ 0x00c86e50
void cSolarSystem::Destroy()
{
    ActivateGraphics(false);

    for (void** pp = mCelestialBodies.mpBegin; pp != mCelestialBodies.mpEnd; ++pp)
        ((VObj174*)*pp)->v044();
    mCelestialBodies.erase(mCelestialBodies.mpBegin, mCelestialBodies.mpEnd);
    mPlanets.erase(mPlanets.mpBegin, mPlanets.mpEnd);

    mpStar = 0;

    VObj174* p38 = mp38;
    if (p38) {
        mp38 = 0;
        p38->Release();
    }
    VObj174* p3c = mp3c;
    if (p3c) {
        mp3c = 0;
        p3c->Release();
    }

    mPtolemaicHitSpheres.clear();
}

// ============================================================ helpers
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

// A property list: AddRef at 0x00, Release at 0x04, GetProperty at 0x24.
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

// ============================================================ cSpaceInventory
struct cISerializableObject {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
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

// ============================================================ item bodies
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

// Writes one item through its serializable interface.
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
    if (SP_GetPropertyAsKey(mpPropList.mPtr, 0x3068d95c, &key))
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
    if (SP_GetPropertyAsKey(mpPropList.mPtr, 0xa6a37fc4, &key)) {
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

// Writes every item of a list through the serializable interface.
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

// Creates the multi-delivery item bound to the given key.
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
