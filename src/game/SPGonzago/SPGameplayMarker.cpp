// src/game/SPGonzago/SPGameplayMarker.cpp -- migrated from slice(s) s00c3ee20, s00c3daa0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameplayMarker.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPGameDataUFO.h"
#include <math.h>
#include <stdlib.h>
#include "cSPVector3.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cHitSphere.h"
#include "SP/cInteractableObject.h"
#include "SP/cOrnament.h"
#include "SP/cSolarHitSphere.h"
#include "SP/cSpatialObject.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s00c3daa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_146c388[];
extern "C" char g_146c44c[];
extern "C" char g_146c460[];
struct FnB184c0 { void __thiscall f(); };                      // 0x00b184c0 cGameData::~cGameData
struct FnC8a420 { void __thiscall f(); };                      // 0x00c8a420
bool  __cdecl FUN_0093aa70(void*, void*, int, int);            // 0x0093aa70 WriteUint32
bool  __cdecl FUN_0093a9d0(void*, void*, int, int);            // 0x0093a9d0 WriteUint16
struct Fn88670 { void __thiscall f(void*); };                 // 0x00c88670
struct Fn886d0 { void __thiscall f(void*); };                 // 0x00c886d0
struct C3ebd0 { void f(int* p); };                             // 0x00c3ebd0
struct C3ec00 { void f(int* p); };                             // 0x00c3ec00
struct C3ec40 { void f(); };                                   // 0x00c3ec40
// ---- items of slice s00c3daa0 end

// ---- items of slice s00c3ee20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char sGameplayMarkerFields; // 0x01573ad8
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
struct GameplayStreamHolder {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void* GetStream(); // +0x18
};
struct GameplayArchive {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7();
    virtual GameplayStreamHolder* GetStreamHolder(); // +0x20
    virtual void slot9(); virtual void slot10(); virtual void slot11(); virtual void slot12();
    virtual void TransferBlock(void* data, unsigned size); // +0x34
};
struct GameplayCachedObject {
    virtual void AddRef(); virtual void Release();
    virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9(); virtual void slot10();
    virtual bool IsInvalid(); // +0x2c
};
struct GameplayMarkerState {
    char pad000[0x114];
    unsigned char nounData[0x88]; // +0x114
    char pad19c[8];
    GameplayCachedObject* cachedObject; // +0x1a4
    char pad1a8[0x1c];
    bool needsRecreation; // +0x1c4
};
void __cdecl GameplayReadInt32(void*, void*, int, int); // 0x0093a780
void __cdecl GameplayReadUint16(void*, void*, int, int); // 0x0093a700
struct GameplaySpatialReader {
    bool Read(SP::cIObjectDatabaseIStream&); // 0x00c88b00
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
    bool Write(void* pData);
    bool InitFromDefinition(void* pData, int a, int b);
};
class cGameNounManager {
public:
    void RemoveNoun(void* pNoun);
};
cGameNounManager* NounManager(int id);
cGameNounManager* NounManager();
bool QueryProperty(void* pDefinition, int key, void* pOut);
bool ReadInteractableSubobject(void* pData);
void GetPropertyAsUint32(void* pDefinition, int key, void* pOut);
void ShutdownMarkerExtras();
// ---- items of slice s00c3ee20 end

// @ 0x00c3ebd0
void C3ebd0::f(int* p)
{
    char* self = (char*)this;
    ((Fn88670*)self)->f(p);
    *(int*)(self + 0x174) = p[0];
    *(int*)(self + 0x178) = p[1];
    *(int*)(self + 0x17c) = p[2];
}

// @ 0x00c3ec00
void C3ec00::f(int* p)
{
    char* self = (char*)this;
    ((Fn886d0*)self)->f(p);
    *(int*)(self + 0x180) = p[0];
    *(int*)(self + 0x184) = p[1];
    *(int*)(self + 0x188) = p[2];
    *(int*)(self + 0x18c) = p[3];
}

// @ 0x00c3ec40
void C3ec40::f()
{
    char* self = (char*)this;
    char* p34 = self + 0x34;
    *(int*)(self) = (int)g_146c460;
    *(int*)(self + 4) = (int)g_146c44c;
    *(int*)(p34) = (int)g_146c388;

    void* p;
    p = *(void**)(self + 0x1a4);
    if (p) { typedef void(__thiscall* Vf)(void*); ((Vf)(*(void**)(*(char**)p + 4)))(p); }
    p = *(void**)(self + 0x1a0);
    if (p) { typedef void(__thiscall* Vf)(void*); ((Vf)(*(void**)(*(char**)p + 4)))(p); }
    p = *(void**)(self + 0x19c);
    if (p) { typedef void(__thiscall* Vf)(void*); ((Vf)(*(void**)(*(char**)p + 4)))(p); }

    ((FnC8a420*)p34)->f();
    ((FnB184c0*)self)->f();
}

// @ 0x00c3ed20
bool cGameplayMarker::Write(void* stream)
{
    GameplayArchive* archive = static_cast<GameplayArchive*>(stream);
    {
        GameplayStreamHolder* __restrict holder = archive->GetStreamHolder();
        uint32_t tag = 0x36be278;
        void* output = holder->GetStream();
        FUN_0093aa70(output, &tag, 1, 0);
    }
    SP::cIObjectDatabaseOStream& outputArchive =
        *static_cast<SP::cIObjectDatabaseOStream*>(stream);
    bool result = true;
    result &= reinterpret_cast<SP::cGameData*>(this)->SP::cGameData::Write(outputArchive);
    result &= reinterpret_cast<SP::cSpatialObject*>((char*)this + 0x34)->SP::cSpatialObject::Write(outputArchive);

    GameplayMarkerState* state = reinterpret_cast<GameplayMarkerState*>(this);
    GameplayCachedObject* cached = state->cachedObject;
    if (cached && cached->IsInvalid()) {
        cached = state->cachedObject;
        if (cached) {
            state->cachedObject = 0;
            cached->Release();
        }
        state->needsRecreation = true;
    }
    SP::cVarListSerializer serializer(this,
        reinterpret_cast<SP::cDataSerializerGeneric*>(&sGameplayMarkerFields),
        SP::cVarListSerializer::kSignature);
    result &= serializer.Serialize(outputArchive);
    {
        GameplayStreamHolder* __restrict holder = archive->GetStreamHolder();
        uint32_t size = 0x88;
        void* output = holder->GetStream();
        FUN_0093a9d0(output, &size, 1, 0);
    }
    archive->TransferBlock(state->nounData, 0x88);
    return result;
}

// @ 0x00c3ee20
bool cGameplayMarker::Read(void* pData)
{
    GameplayArchive* archive = static_cast<GameplayArchive*>(pData);
    void* input = archive->GetStreamHolder()->GetStream();
    uint32_t tag;
    GameplayReadInt32(input, &tag, 1, 0);
    SP::cIObjectDatabaseIStream& inputArchive =
        *static_cast<SP::cIObjectDatabaseIStream*>(pData);
    bool result = true;
    result &= reinterpret_cast<SP::cGameData*>(this)->SP::cGameData::Read(inputArchive);
    result &= reinterpret_cast<GameplaySpatialReader*>((char*)this + 0x34)->Read(inputArchive);
    SP::cVarListSerializer serializer(this,
        reinterpret_cast<SP::cDataSerializerGeneric*>(&sGameplayMarkerFields),
        SP::cVarListSerializer::kSignature);
    result &= serializer.Serialize(inputArchive);
    uint32_t size = 0x88;
    void* blockInput = archive->GetStreamHolder()->GetStream();
    GameplayReadUint16(blockInput, &size, 1, 0);
    uint32_t maxSize = 0x88;
    const uint16_t* chosen = (uint16_t)maxSize < (uint16_t)size ?
        reinterpret_cast<const uint16_t*>(&maxSize) : reinterpret_cast<const uint16_t*>(&size);
    archive->TransferBlock(reinterpret_cast<GameplayMarkerState*>(this)->nounData, *chosen);
    return result;
}

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

// 0x00c3efb0: not byte-exact; the byte-exact version is the lifted one in match/slices/s00c3efb0/s00c3efb0.cpp
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
