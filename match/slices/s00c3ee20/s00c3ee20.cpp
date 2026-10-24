// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00c3ee20.
//
// Gameplay markers, hit spheres, interactable objects and interactive
// ornaments: constructors, serialization (Read / Write / GetFields) and
// definition initialization.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;
typedef int intptr_t;
typedef unsigned int uintptr_t;
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

// Binary stream handed to the serializers.
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

// ---------------------------------------------------------------------------
// Shared game objects
// ---------------------------------------------------------------------------

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

// Model key used by the solar hit sphere.
struct ModelKey {
    uint32_t typeID;                // 0x00
    uint32_t instanceID;            // 0x04
    uint32_t groupID;               // 0x08
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
    void* Cast(void* pType);
    int GetDelegateLowerBound(int nOffset);
};

class cSolarHitSphere : public cHitSphere {
public:
    ModelKey mModelKey;             // 0x230
    cSolarHitSphere();
};

class cString {
public:
    cString();
    const wchar_t* c_str();
};

class cGameplayMarker : public cGameData {
public:
    uint8_t mType;                  // 0x134
    uint8_t mPad135[0x03];          // 0x135
    uint32_t mId;                   // 0x138
    uint32_t mDefinitionId;         // 0x13c
    uint8_t mPad140[0x08];          // 0x140
    uint8_t mNounData[0xa00];       // 0x148
    uint8_t mPadB48[0x20];          // 0xb48
    IRefCounted* mpTriggerA;        // 0xb68
    IRefCounted* mpTriggerB;        // 0xb6c
    IRefCounted* mpUseNounTriggers; // 0xb70
    IRefCounted* mpNextMarker;      // 0xb74

    cGameplayMarker();
    void Destroy(int bDelete);
    void Shutdown();
    bool Read(void* pData);
    bool InitFromDefinition(void* pData, int a, int b);
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
    void ClearEffectState();
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

class cGameNounManager {
public:
    void RemoveNoun(void* pNoun);
};

cGameNounManager* NounManager(int id);
cGameNounManager* NounManager();
void* EffectsManager();
void* PlanetModel();
bool QueryProperty(void* pDefinition, int key, void* pOut);
bool QueryPropertyExists(void* pDefinition, int key);
bool ReadInteractableSubobject(void* pData);
void* CastOrnamentBase(void* pObject);
void* CastSpatialObjectBase(void* pObject);
void* CastHitSphereBase(void* pObject);
void RemoveOwnerExtra();
void* GetPropertyAsKeyArray(void* pDefinition, int key);
void GetPropertyAsUint32(void* pDefinition, int key, void* pOut);
void GetPropertyAsText(void* pDefinition, int key, void* pOut);
int GetPropertyAsInt(void* pDefinition, int key);
uint32_t RandomUint32Uniform(int nRange);
void operator_delete__(void* pMemory);
void SetModelVariant(cSpatialObject* pObject, int nVariant, int bA, int bB);
int SplitModelVariantList(void* pDefinition, int key, int* pCount, void** ppList);
void ResetOrnamentList(void* pOwner);
void ResetInteractableState(void* pOwner);
void ShutdownMarkerExtras();
void FreeOrnamentMembers();
void FreeGameDataMembers();
void FreeInteractableInherited();
void MarkSpatialFlag(int* pFlags);

extern const void* sGameplayMarkerFields;
extern const void* sHitSphereFields;
extern const void* sInteractableFields;
extern const void* sOrnamentFields;

// ---------------------------------------------------------------------------
// 0x00c3ee20  Simulator::cGameplayMarker::Read
// ---------------------------------------------------------------------------
// @ 0x00c3ee20
bool cGameplayMarker::Read(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0;
    ReadInt32(pStream->GetStream(), &nType, 1, 0);

    bool bData = cGameData::Read(pData);
    bool bBase = ReadInteractableSubobject(pData);

    cVarListSerializer serializer(this, sGameplayMarkerFields, 0x1a80d26);
    bool bFields = serializer.Serialize(pData);

    uint32_t nCount = 0x88;
    uint32_t nMax = 0x88;
    uint32_t* pCount = (nCount < 0x89) ? &nCount : &nMax;
    ((ISerializer*)pData)->ReadBlock(mNounData + 0x50, *pCount ? *pCount : 0);

    return bData && bBase && bFields;
}

// ---------------------------------------------------------------------------
// 0x00c3ef00  Simulator::cGameplayMarker::Shutdown
// ---------------------------------------------------------------------------
// @ 0x00c3ef00
void cGameplayMarker::Shutdown()
{
    if (mPad68 != nullptr) {
        IRefCounted* pOld = mpTriggerA;
        mpTriggerA = nullptr;
        pOld->Release();
    }
    if (mpTriggerB != nullptr) {
        IRefCounted* pOld = mpTriggerB;
        mpTriggerB = nullptr;
        pOld->Release();
    }
    if (mpUseNounTriggers != nullptr) {
        IRefCounted* pOld = mpUseNounTriggers;
        mpUseNounTriggers = nullptr;
        pOld->Release();
    }
    if (mpNextMarker != nullptr) {
        IRefCounted* pOld = mpNextMarker;
        mpNextMarker = nullptr;
        pOld->Release();
    }
    NounManager()->RemoveNoun(mpNextMarker);
    ShutdownMarkerExtras();
}

// ---------------------------------------------------------------------------
// 0x00c3efb0  Simulator::cGameplayMarker::cGameplayMarker
// ---------------------------------------------------------------------------
// @ 0x00c3efb0
cGameplayMarker::cGameplayMarker()
{
    mType = 0;
    mId = 0;
    mDefinitionId = 0;
    mOriginalExtentsLower.mX = 0.0f;
    mOriginalExtentsLower.mY = 0.0f;
    mOriginalExtentsLower.mZ = 0.0f;
    mOriginalExtentsUpper.mX = 0.0f;
    mOriginalExtentsUpper.mY = 0.0f;
    mModelReady = 0;
    mpNextMarker = nullptr;
    mpTriggerA = nullptr;
    mpTriggerB = nullptr;
    mpUseNounTriggers = nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c3f040  Simulator::cGameplayMarker::InitFromDefinition
// ---------------------------------------------------------------------------
// @ 0x00c3f040
bool cGameplayMarker::InitFromDefinition(void* pData, int a, int b)
{
    if (!cGameData::Init(pData, a, b))
        return false;

    void* pDefinition = *(void**)((uint8_t*)pData + 0xc);
    if (pDefinition == nullptr)
        return true;

    int nValue = 0;
    if (QueryProperty(pDefinition, 0x82b066b7, &nValue)) {
        mNounData[0x44] = (uint8_t)nValue;
    }
    if (QueryProperty(pDefinition, 0x29831f0c, &nValue)) {
        mNounData[0x50] = (uint8_t)nValue;
    }
    if (mNounData[0x44] == 0x1f) {
        GetPropertyAsUint32(pDefinition, 0xe8e03081, mNounData + 0x58);
        GetPropertyAsUint32(pDefinition, 0xeeaf4d29, mNounData + 0x5c);
        GetPropertyAsUint32(pDefinition, 0xc7760a47, mNounData + 0x60);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00c3f160  cInteractableObject::SetEffectId
// ---------------------------------------------------------------------------
// @ 0x00c3f160
void cInteractableObject::SetEffectId(int nEffectId)
{
    ((void (*)(int))*(void**)(*(uint32_t*)((uint8_t*)this + 0x70) + 0x38))(nEffectId);
    *(uint32_t*)((uint8_t*)this + 0x238) = (uint32_t)nEffectId;
}

// ---------------------------------------------------------------------------
// 0x00c3f1d0  Object::Cast
// ---------------------------------------------------------------------------
// @ 0x00c3f1d0
void* cGameplayMarkerCast(void* pObject, int nType)
{
    if (nType != 0x32f9777 && nType != 0x2e71a5a)
        return CastOrnamentBase(pObject);
    return pObject;
}

// ---------------------------------------------------------------------------
// 0x00c3f1f0  cGameplayMarker::~cGameplayMarker
// ---------------------------------------------------------------------------
// @ 0x00c3f1f0
void cGameplayMarker::Destroy(int bDelete)
{
    if (mpNextMarker != nullptr)
        mpNextMarker->Release();
    if (mpUseNounTriggers != nullptr)
        mpUseNounTriggers->Release();
    if (mpTriggerB != nullptr)
        mpTriggerB->Release();
    if (mpTriggerA != nullptr)
        mpTriggerA->Release();
    if ((bDelete & 1) != 0)
        operator_delete__(this);
}

// ---------------------------------------------------------------------------
// 0x00c3f250  cInteractableObject::Shutdown
// ---------------------------------------------------------------------------
// @ 0x00c3f250
void cInteractableObject::Shutdown()
{
    ResetInteractableState(this);
    ResetOrnamentList(this);
    *(uint32_t*)((uint8_t*)this + 0x144) = 0x1466c14;
    FreeInteractableInherited();
    *(uint32_t*)((uint8_t*)this + 0x34) = 0x146c56c;
    if (mpOwner != nullptr)
        mpOwner->Release();
    if (*(IRefCounted**)((uint8_t*)this + 0x54) != nullptr)
        (*(IRefCounted**)((uint8_t*)this + 0x54))->Release();
    if (*(IRefCounted**)((uint8_t*)this + 0x50) != nullptr)
        (*(IRefCounted**)((uint8_t*)this + 0x50))->Release();
    if (*(IRefCounted**)((uint8_t*)this + 0x4c) != nullptr)
        (*(IRefCounted**)((uint8_t*)this + 0x4c))->Release();
    FreeGameDataMembers();
}

// ---------------------------------------------------------------------------
// 0x00c3f310  Simulator::cGameData::RemoveOwner
// ---------------------------------------------------------------------------
// @ 0x00c3f310
void cGameData::RemoveOwner()
{
    IRefCounted* pOwner = *(IRefCounted**)((uint8_t*)this + 0x2c);
    if (pOwner != nullptr) {
        *(IRefCounted**)((uint8_t*)this + 0x2c) = nullptr;
        pOwner->Release();
    }
    RemoveOwnerExtra();
}

// ---------------------------------------------------------------------------
// 0x00c3f340  Simulator::cHitSphere::Write
// ---------------------------------------------------------------------------
// @ 0x00c3f340
bool cHitSphere::Write(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0x2e71a5a;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    bool bOk = cGameData::Write(pData);
    if (bOk)
        bOk = cSpatialObject::Write(pData);

    if (mpDelegate != nullptr) {
        if (mpDelegate->Query(nullptr) != nullptr) {
            cGameData* pOld = mpDelegate;
            mpDelegate = nullptr;
            pOld->Release();
        }
    }

    cVarListSerializer serializer(this, sHitSphereFields, 0x1a80d26);
    if (bOk)
        return serializer.Serialize(pData);
    return false;
}

// ---------------------------------------------------------------------------
// 0x00c3f4a0  Simulator::cHitSphere::cHitSphere
// ---------------------------------------------------------------------------
// @ 0x00c3f4a0
cHitSphere::cHitSphere()
{
    mRadius = 1.0f;
    mMaxScreenSize = 1.0f;
    mMinScreenSize = 0.0f;
    mMinDistance = 0.0f;
    mMaxDistance = 3.4028234e+38f;
    mpDelegate = nullptr;
    mbKeepPinnedToPlanet = false;
}

// ---------------------------------------------------------------------------
// 0x00c3f560  cHitSphere::GetDelegateLowerBound
// ---------------------------------------------------------------------------
// @ 0x00c3f560
int cHitSphere::GetDelegateLowerBound(int nOffset)
{
    if (nOffset != 0x34)
        return nOffset + 0x3c;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c3f6f0  Simulator::cSolarHitSphere::cSolarHitSphere
// ---------------------------------------------------------------------------
// @ 0x00c3f6f0
cSolarHitSphere::cSolarHitSphere()
{
    mModelKey.typeID = 0;
    mModelKey.instanceID = 0;
    mModelKey.groupID = 0;
}

// ---------------------------------------------------------------------------
// 0x00c3f850  cHitSphere::Cast
// ---------------------------------------------------------------------------
// @ 0x00c3f850
void* cHitSphere::Cast(void* pType)
{
    if (pType == (void*)0x1186577) {
        if (this != nullptr)
            return (uint8_t*)this + 0x34;
        return nullptr;
    }
    if (pType != (void*)0x398420d)
        return CastSpatialObjectBase(this);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00c3f890  cInteractableObject::LoadModel
// ---------------------------------------------------------------------------
// @ 0x00c3f890
bool cInteractableObject::LoadModelChecked(void* pModel)
{
    return cSpatialObject::LoadModel(pModel);
}

// ---------------------------------------------------------------------------
// 0x00c3f8b0  cInteractableObject::SetModelState
// ---------------------------------------------------------------------------
// @ 0x00c3f8b0
void cInteractableObject::SetModelState(int nState, bool bForce)
{
    if (((uint8_t)nState == mModelStateIndex) && !bForce)
        return;

    mModelStateIndex = (uint8_t)nState;
    if (mModelReady == 0)
        return;

    if (GetModel() != nullptr) {
        va8(nState, 1, 0);
    }
}

// ---------------------------------------------------------------------------
// 0x00c3f920  cInteractableObject::GetFields
// ---------------------------------------------------------------------------
// @ 0x00c3f920
int cInteractableObject::GetFieldValues(int nFlags)
{
    cVarListSerializer base(this, sInteractableFields, 0x1a80d26);
    int nBase = base.GetFields(nFlags);
    int nGameData = cGameData::GetFieldValues(nFlags);
    cVarListSerializer own(this, sOrnamentFields, 0x1a80d26);
    return own.GetFields(nFlags) + nBase + nGameData;
}

// ---------------------------------------------------------------------------
// 0x00c3f9b0  cInteractableObject::cInteractableObject
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c3fa70  cInteractableObject::~cInteractableObject
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c3fad0  cInteractableObject::ClearEffectState
// ---------------------------------------------------------------------------
// @ 0x00c3fad0
void cInteractableObject::ClearEffectState()
{
    mFlags &= ~0x100u;
    if (*(IRefCounted**)((uint8_t*)this + 0x108) != nullptr) {
        IRefCounted* pOld = *(IRefCounted**)((uint8_t*)this + 0x108);
        *(IRefCounted**)((uint8_t*)this + 0x108) = nullptr;
        pOld->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00c3fb00  SP::cInteractableObject::Write
// ---------------------------------------------------------------------------
// @ 0x00c3fb00
bool cInteractableObject::Write(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0x398420d;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    bool bOk = cSpatialObject::Write(pData);
    if (bOk)
        bOk = cGameData::Write(pData);

    cVarListSerializer serializer(this, sInteractableFields, 0x1a80d26);
    if (bOk)
        return serializer.Serialize(pData);
    return false;
}

// ---------------------------------------------------------------------------
// 0x00c3fba0  SP::cInteractableObject::Read
// ---------------------------------------------------------------------------
// @ 0x00c3fba0
bool cInteractableObject::Read(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0;
    ReadInt32(pStream->GetStream(), &nType, 1, 0);

    bool bOk = ReadInteractableSubobject(pData);
    if (bOk)
        bOk = cGameData::Read(pData);

    cVarListSerializer serializer(this, sInteractableFields, 0x1a80d26);
    if (bOk)
        return serializer.Serialize(pData);
    return false;
}

// ---------------------------------------------------------------------------
// 0x00c3fc80  SP::cInteractableObject::InitFromDefinition
// ---------------------------------------------------------------------------
// @ 0x00c3fc80
bool cInteractableObject::InitFromDefinition(void* pData, int a, uint flags)
{
    if (!cGameData::Init(pData, a, flags))
        return false;

    void* pDefinition = *(void**)((uint8_t*)pData + 0xc);
    if (!QueryPropertyExists(pDefinition, 0x2e9c0dc))
        return false;

    void* pKeyArray = GetPropertyAsKeyArray(pDefinition, 0x2e9c0dc);
    if (pKeyArray != nullptr) {
        mDefinitionWord = *(uint64_t*)pKeyArray;
        mModelId = *(uint32_t*)((uint8_t*)pKeyArray + 8);
    }

    uint8_t nArray[4];
    if (QueryProperty(pDefinition, 0x5309c7d, &nArray)) {
        mModelReady = nArray[0];
    }

    uint32_t nCount = 0;
    void* pList = nullptr;
    if (QueryProperty(pDefinition, 0x67364ba, &nArray) && nArray[0] != 0) {
        void* pOrnamentList = PlanetModel();
        if (pOrnamentList != nullptr)
            (void)SplitModelVariantList(pDefinition, 0x3d08e15, (int*)&nCount, &pList);
        if ((int)nCount > 0) {
            uint32_t nPick = RandomUint32Uniform((int)nCount);
            uint32_t* pEntry = (uint32_t*)pList + nPick * 3;
            mDefinitionWord = *(uint64_t*)pEntry;
            mModelId = pEntry[2];
        }
    }

    float fScale = 0.0f;
    if (QueryProperty(pDefinition, 0x1a85fc9d, &nArray))
        mScale = fScale;
    GetPropertyAsText(pDefinition, 0x738fe71, &mOrnamentId);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00c3fe70  cInteractiveOrnament::Shutdown
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c3ff10  cInteractiveOrnament::AttachEffect
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c40150  Object::Cast
// ---------------------------------------------------------------------------
// @ 0x00c40150
void* cInteractiveOrnamentCast(void* pObject, void* pType)
{
    if (pType == (void*)0x13f94d4) {
        if (pObject != nullptr)
            return (uint8_t*)pObject + 0x5c;
        return nullptr;
    }
    if (pType == (void*)0x3a25119)
        return pObject;
    if (pType != (void*)0x8367427)
        return CastHitSphereBase(pObject);
    if (pObject != nullptr)
        return (uint8_t*)pObject + 0x4c;
    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c40200  SP::cInteractiveOrnament::SetNextDestructedState
// ---------------------------------------------------------------------------
// @ 0x00c40200
int cInteractiveOrnament::SetNextDestructedState()
{
    int nNext = mDestructedState + 1;
    if (nNext < (mDestructedCount - mDestructedStep) / 0xc) {
        mDestructedState = nNext;
        void (*pCallback)(void*) = *(void (**)(void*))((uint8_t*)GetPosition() + 0x94);
        pCallback((uint8_t*)(uintptr_t)mDestructedStep + nNext * 0xc);
        mOrnamentState = 0;
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c40270  SP::cInteractiveOrnament::Write
// ---------------------------------------------------------------------------
// @ 0x00c40270
bool cInteractiveOrnament::Write(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0x3a25119;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    bool bOk = cInteractableObject::Write(pData);

    cVarListSerializer serializer(this, sOrnamentFields, 0x1a80d26);
    if (bOk)
        return serializer.Serialize(pData);
    return false;
}
