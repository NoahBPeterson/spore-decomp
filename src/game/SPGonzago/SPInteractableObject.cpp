// src/game/SPGonzago/SPInteractableObject.cpp -- migrated from slice(s) s00c3ee20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPInteractableObject.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cInteractableObject.h"
#include "cSPVector3.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cHitSphere.h"
#include "SP/cOrnament.h"
#include "SP/cSolarHitSphere.h"
#include "SP/cSpatialObject.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern const void* sInteractableFields;

// ---- items of slice s00c3ee20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
};
class IOStream {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual IOStream* GetStream();         // 0x20
    virtual void GetStream2();             // 0x24
    virtual void ReadBlock(void* pDest, uint nCount);   // 0x34
};
class ISerializer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual bool Serialize(void* pData);
    virtual int GetFields(int nFlags);
    virtual IOStream* GetStream();
    virtual void ReadBlock(void* pDest, int nCount);
};
void ReadInt32(IOStream* pStream, void* pDest, int nCount, int bFlag);
void WriteUint32(IOStream* pStream, void* pSource, int nCount, int bFlag);
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const void* pFields, int nFlags);
    bool Serialize(void* pData);
    int GetFields(int nFlags);
    uint8_t mPad00[0x414];
};
class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual Vec3* GetPosition();          // 0x2c
    virtual Vec3* GetDirection();         // 0x30
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8(int nState, int bA, int bB);   // 0xac
    virtual void* GetModel();                        // 0xb0
    virtual void vb4();
    virtual void vb8();
    virtual void vbc(int a);
    virtual void vc0();
    virtual bool vc4();

    Vec3 mPosition;                 // 0x04
    uint8_t mPad10[0x24];           // 0x10
    Vec3 mLocalExtentsMin;          // 0x34
    Vec3 mLocalExtentsMax;          // 0x40
    Vec3 mOriginalExtentsLower;     // 0x4c
    Vec3 mOriginalExtentsUpper;     // 0x58
    float mFootprintRadius;         // 0x64
    uint8_t mPad68[0x20];           // 0x68
    uint32_t mFlags;                // 0x88
    uint8_t mPad8c[0x18];           // 0x8c
    uint8_t mVisible;               // 0xa4
    uint8_t mHidden;                // 0xa5
    uint8_t mPadA6[0x87];           // 0xa6
    uint8_t mModelStateIndex;       // 0x12d
    uint8_t mPad12e[0x02];          // 0x12e
    uint8_t mModelReady;            // 0x130

    bool LoadModel(void* pModel);
    bool Write(void* pData);
};
class cGameData : public cSpatialObject {
public:
    bool Read(void* pData);
    bool Write(void* pData);
    bool Init(void* pData, int a, int b);
    int GetFieldValues(int nFlags);
    void RemoveOwner();
};
class cOrnament : public cGameData {
public:
    uint8_t mPad54[0x1c0];
};
class cHitSphere : public cOrnament {
public:
    float mRadius;                  // 0x214
    float mMaxScreenSize;           // 0x218
    float mMinScreenSize;           // 0x21c
    float mMinDistance;             // 0x220
    float mMaxDistance;             // 0x224
    cGameData* mpDelegate;          // 0x228
    uint8_t mbKeepPinnedToPlanet;   // 0x22c

    cHitSphere();
    bool Write(void* pData);
    int GetDelegateLowerBound(int nOffset);
};
class cInteractableObject : public cGameData {
public:
    uint8_t mPad134[0x50];          // 0x134
    uint64_t mDefinitionWord;       // 0x184
    uint32_t mModelId;              // 0x18c
    uint32_t mOrnamentId;           // 0x190
    float mScale;                   // 0x194
    uint8_t mPad198[0x14];          // 0x198
    IRefCounted* mpOwner;           // 0x1ac
    uint32_t mEffectState;          // 0x1b0
    uint8_t mPad1b4[0x08];          // 0x1b4

    cInteractableObject();
    bool Write(void* pData);
    bool Read(void* pData);
    int GetFieldValues(int nFlags);
    void SetEffectId(int nEffectId);
    bool LoadModelChecked(void* pModel);
    void SetModelState(int nState, bool bForce);
    bool InitFromDefinition(void* pData, int a, uint flags);
    void Destroy(int bDelete);
    void Shutdown();
    void AttachEffect(void* pEffect);
    void ClearEffectState(void* pArg);
};
class cInteractiveOrnament : public cInteractableObject {
public:
    uint8_t mPad1bc[0x84];          // 0x1bc
    int mDestructedState;           // 0x240
    int mDestructedCount;           // 0x244
    int mDestructedStep;            // 0x248
    int mDestructedMax;             // 0x24c
    uint32_t mOrnamentFlags;        // 0x250
    uint8_t mOrnamentState;         // 0x254

    bool Write(void* pData);
    int SetNextDestructedState();
    void ShutdownOrnament();
    void AttachEffect(void* pEffect);
};
void* EffectsManager();
// Retail query views. Native construction puts the spatial base at +0x34;
// the generated class layout still places it at +0x2c. Only base conversion
// and direct game-data/spatial calls are needed here. The spatial view represents
// its vptr prefix only; no constructor, field access or sizeof uses this view.
typedef eastl::vector<SP::cField, eastl::sp_vector_allocator> InteractableFields;
namespace RetailInteractableObject {
class cGameData {
    uint32_t mStorage[0x34 / 4];
public:
    void* AsInterface(uint32_t type); // 0x00b18460, thiscall, ret 4
    bool Write(void* data); // 0x00b18590
    bool Read(void* data); // 0x00b18600
    int GetFieldValues(InteractableFields& fields); // 0x00b18420
};
class cSpatialObject {
    const void* mVTable;
public:
    bool Write(void* data); // 0x00c88a90
    bool Read(void* data); // 0x00c88b00
};
class cModel {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0();
    virtual void SetModelVariant(int variant); // 0xc4
};
// The spatial base's virtual interface (only the slots used here).
class cSpatialObjectView {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual int GetModelVariant(int state, int a, int b); // 0xac
    virtual cModel* GetModel();                           // 0xb0
};
class cInteractableObject : public cGameData, public cSpatialObject {
    uint8_t mPad38[0x12c - 0x38];
public:
    uint8_t mModelReady;      // 0x12c
    uint8_t mModelStateIndex; // 0x12d
    void SetModelState(int nState, bool bForce);
    cSpatialObjectView* Spatial() { return (cSpatialObjectView*)static_cast<cSpatialObject*>(this); }
    void* AsInterface(uint32_t type);
    bool Write(void* data);
    bool Read(void* data);
    int GetFieldValues(InteractableFields& fields);
};
}
void SetModelVariant(cSpatialObject* pObject, int nVariant, int bA, int bB);
void ShutdownMarkerExtras();
void FreeOrnamentMembers();
void FreeGameDataMembers();
void FreeInteractableInherited();
extern const void* sInteractableFields;
// ---- items of slice s00c3ee20 end

// @ 0x00c3f850
void* RetailInteractableObject::cInteractableObject::AsInterface(uint32_t type)
{
    if (type != 0x01186577u)
        return type != 0x0398420du ? cGameData::AsInterface(type) : this;
    return static_cast<cSpatialObject*>(this);
}

// @ 0x00c3f890
bool cInteractableObject::LoadModelChecked(void* pModel)
{
    return cSpatialObject::LoadModel(pModel) ? true : false;
}

// @ 0x00c3f8b0
void RetailInteractableObject::cInteractableObject::SetModelState(int nState, bool bForce)
{
    if (((uint8_t)nState == mModelStateIndex) && !bForce)
        return;

    mModelStateIndex = (uint8_t)nState;
    if (mModelReady == 0)
        return;

    if (Spatial()->GetModel() != nullptr)
        Spatial()->GetModel()->SetModelVariant(Spatial()->GetModelVariant(nState, 1, 0));
}

// @ 0x00c3f9b0
cInteractableObject::cInteractableObject()
{
    mModelId = 0;
    mOrnamentId = 0;
    mScale = 0.0f;
    mEffectState = 0;
    mpOwner = nullptr;
    mDefinitionWord = 0;
    mPad198[0] = 0;
    mModelStateIndex = 1;
}

// @ 0x00c3fa70
void cInteractableObject::Destroy(int bDelete)
{
    (void)bDelete;
    FreeOrnamentMembers();
    if (mpOwner != nullptr)
        mpOwner->Release();
    if (*(IRefCounted**)((uint8_t*)this + 0x108) != nullptr)
        (*(IRefCounted**)((uint8_t*)this + 0x108))->Release();
    FreeInteractableInherited();
    FreeGameDataMembers();
}

// @ 0x00c3fad0
void cInteractableObject::ClearEffectState(void* pArg)
{    (void)pArg;
    *(volatile uint32_t*)((uint8_t*)this + 0x84) &= ~0x100u;
    IRefCounted* pOld = *(IRefCounted* volatile*)((uint8_t*)this + 0x108);
    if (pOld != nullptr) {
        *(IRefCounted**)((uint8_t*)this + 0x108) = nullptr;
        pOld->Release();
    }
}

extern SP::cDataSerializerGeneric gInteractableSerializerList[]; // 0x01573ee8
struct InteractableStreamHolder {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual IOStream* GetStream(); // slot 6
};
struct InteractableArchive {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7();
    virtual InteractableStreamHolder* GetStreamHolder(); // slot 8
};

extern SP::cDataSerializerGeneric gInteractableSpatialSerializerList[]; // 0x0157a1f8

// @ 0x00c3f920
int RetailInteractableObject::cInteractableObject::GetFieldValues(InteractableFields& fields)
{
    SP::cVarListSerializer spatial((char*)this + sizeof(cGameData), gInteractableSpatialSerializerList, 0x1a80d26);
    int count = spatial.GetFields(fields);
    count += cGameData::GetFieldValues(fields);
    SP::cVarListSerializer own(this, gInteractableSerializerList, 0x1a80d26);
    return own.GetFields(fields) + count;
}

// @ 0x00c3fb00
bool RetailInteractableObject::cInteractableObject::Write(void* data)
{
    InteractableStreamHolder* __restrict holder = ((InteractableArchive*)data)->GetStreamHolder();
    uint32_t type = 0x398420d;
    IOStream* stream = holder->GetStream();
    WriteUint32(stream, &type, 1, 0);
    bool ok;
    if (cSpatialObject::Write(data) && cGameData::Write(data))
        ok = true;
    else
        ok = false;
    SP::cVarListSerializer serializer(this, gInteractableSerializerList, 0x1a80d26);
    if (ok) {
        if (serializer.Serialize(*(SP::cIObjectDatabaseOStream*)data))
            return true;
    }
    return false;
}

// @ 0x00c3fba0
bool RetailInteractableObject::cInteractableObject::Read(void* data)
{
    InteractableStreamHolder* __restrict holder = ((InteractableArchive*)data)->GetStreamHolder();
    uint32_t type;
    IOStream* stream = holder->GetStream();
    ReadInt32(stream, &type, 1, 0);
    bool ok;
    if (cSpatialObject::Read(data) && cGameData::Read(data))
        ok = true;
    else
        ok = false;
    SP::cVarListSerializer serializer(this, gInteractableSerializerList, 0x1a80d26);
    if (ok) {
        if (serializer.Serialize(*(SP::cIObjectDatabaseIStream*)data))
            return true;
    }
    return false;
}

// @ 0x00c3fe70
void cInteractiveOrnament::ShutdownOrnament()
{
    IRefCounted* pCounted = (IRefCounted*)((uint8_t*)this + 0xd0);
    if (*(uint32_t*)((uint8_t*)this + 0xd0) != 0) {
        *(uint32_t*)((uint8_t*)this + 0xd0) = 0;
        uint32_t* pState = (uint32_t*)((uint8_t*)this + 0xd0);
        (void)pState;
        (void)pCounted;
    }
    if (*(IRefCounted**)((uint8_t*)this + 0xd4) != nullptr) {
        IRefCounted* pOld = *(IRefCounted**)((uint8_t*)this + 0xd4);
        *(IRefCounted**)((uint8_t*)this + 0xd4) = nullptr;
        pOld->Release();
    }
    if (*(IRefCounted**)((uint8_t*)this + 0x108) != nullptr) {
        IRefCounted* pOld = *(IRefCounted**)((uint8_t*)this + 0x108);
        *(IRefCounted**)((uint8_t*)this + 0x108) = nullptr;
        pOld->Release();
    }
    if (*(IRefCounted**)((uint8_t*)this + 0x10c) != nullptr) {
        IRefCounted* pOld = *(IRefCounted**)((uint8_t*)this + 0x10c);
        *(IRefCounted**)((uint8_t*)this + 0x10c) = nullptr;
        pOld->Release();
    }
    if (mpOwner != nullptr) {
        mpOwner->Release();
        mpOwner = nullptr;
    }
    ShutdownMarkerExtras();
}

// @ 0x00c3ff10
void cInteractiveOrnament::AttachEffect(void* pEffect)
{
    mHidden = 1;
    mFlags |= 0x100u;

    if (pEffect != *(void**)((uint8_t*)this + 0x108)) {
        if (pEffect != nullptr)
            ((IRefCounted*)pEffect)->AddRef();
        IRefCounted* pOld = *(IRefCounted**)((uint8_t*)this + 0x108);
        *(void**)((uint8_t*)this + 0x108) = pEffect;
        if (pOld != nullptr)
            pOld->Release();
    }

    mModelStateIndex = 0;
    if (mModelReady != 0 && GetModel() != nullptr) {
        void* pModel = GetModel();
        SetModelVariant(this, 0, 1, 0);
        (void)pModel;
    }

    uint32_t nEffectId;
    switch (mEffectState) {
    case 1:
        nEffectId = 0x82d94ccd;
        break;
    case 3:
        nEffectId = 0x402e4458;
        break;
    case 4:
        nEffectId = 0x6b230eae;
        break;
    case 5:
        nEffectId = 0xa5eab12b;
        break;
    case 6:
        nEffectId = 0x9014f4b9;
        break;
    default:
        return;
    }

    void* pEffects = EffectsManager();
    void* pInstance = nullptr;
    if (((ISerializer*)pEffects)->Serialize(&pInstance)) {
        Vec3 position;
        position.mX = 0.0f;
        position.mY = 0.0f;
        position.mZ = 0.0f;
        (void)nEffectId;
        (void)position;
    }
    if (pInstance != nullptr)
        ((IRefCounted*)pInstance)->Release();
}
