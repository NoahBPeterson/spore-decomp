// src/game/SPGonzago/SPMissionRaid.cpp -- migrated from slice(s) s00c5b9c0, s00c5a580 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionRaid.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cGameData.h"
#include "SP/cSPMission.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include "SP/cPlanet.h"

// ---- items of slice s00c5a580 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef int intptr_t;
#define nullptr 0
float sqrtf(float fValue);
#define __builtin_sqrtf sqrtf
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
    virtual IOStream* GetStream();          // 0x20
    virtual void GetStream2();              // 0x24
    virtual void ReadBlock(void* pDest, int nCount);
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
    virtual IOStream* GetStream();          // 0x20
    virtual uint32_t GetType();             // 0x3c
};
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
    virtual Vec3* GetPosition();            // 0x1c
    virtual void v20();
    uint8_t mPad18[0x1c];
};
class cGameData : public cSpatialObject {
public:
    uint8_t mPad34[0x100];                  // 0x34 .. 0x134
};
class cEmpire : public IRefCounted {
public:
    uint8_t mPad14[0x28];
};
class cCivData : public IRefCounted {
public:
    Vec3* GetCities();
    uint8_t mPad14[0x28];
};
class cSPMission : public cGameData {
public:
    bool IsActive();                        // 0x00
    bool Init();
    void Accept();
    uint32_t GetTargetPlanet();
    cEmpire* GetOwnerEmpire();

    uint8_t mPad134[0x0bc];                 // 0x134 .. 0x1f0
};
class cPlanetMission : public cSPMission {
public:
    Vec3 mPlanetPosition;                   // 0x1f0
    uint8_t mPad1fc[0x30];                  // 0x1fc
    int mTargetId;                          // 0x22c

    bool Read(void* pData);                 // 0x00c5b210
    void UpdateFromPlanet();                // 0x00c5b280
    uint32_t GetOwnerEmpireId();            // 0x00c5b340
    void SetTarget(int nTarget);            // 0x00c5b370
    void SetPlanetPosition(int a, int b, int c);   // 0x00c5b3a0
};
class cSPRaidEvent : public cSPMission {
public:
    uint8_t mPad1f0[0x40];                  // 0x1f0
    int mTargetId;                          // 0x230
    void GenerateBomberCount();             // 0x00c5b530
    bool Init(int a, int b, int c);         // 0x00c5b600
    void Shutdown();                        // 0x00c5b660
    uint32_t CheckDistanceCondition();      // 0x00c5b6c0
    void Update();                          // 0x00c5b860
};
class cSPRaidPlunderEvent : public cSPRaidEvent {
public:
    void GeneratePirateCount();             // 0x00c5b510
    void BackgroundUpdate();                // 0x00c5b550
};
class cUFOKinestheticsTuning {
public:
    double GetGalaxyWarpMultiplier(uint a, uint b);
    uint8_t mPad00[0x11c];
    float mWarpSpeed;                       // 0x11c
};
class cTerrainEditor {
public:
    void* GetCurrentTerrainSphere();
};
class cMessageServer {
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
    virtual void v24();
    virtual void v28();
    virtual void v2c(int* pTarget, const void* pMessage, int nFlags);
};
struct MissionElement {
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    uint32_t mField0c;
    uint32_t mField10;
    uint32_t mField14;
    uint32_t mField18;
    uint32_t mField1c;
};
cTerrainEditor* NounManager();
Vec3* GetTerrainSpherePosition();
void* GetSpaceTuning();
cUFOKinestheticsTuning* GetKinestheticsTuning();
cUFOKinestheticsTuning* GetKinestheticsTuning(int a, int b);
cMessageServer* MessageServer();
void* GetUniverseContext();
void* GetActivePlanet();
int sGetNumUFOs(void* pDefinition, int keyA, int keyB);
void RemoveArtifact(int pOwner, void* pArtifact, uint16_t nCount);
void GetPropertyAsKeyArray(void* pDefinition, int key, void* pOut);
void* GetPropertyAsFloat();
bool IsPlanetValid(uint32_t planetId);
void SetPlanetHighlight(uint32_t planetId);
void SpawnRaidUFOs(void* pDefinition, int a, int b);
void ShutdownMissionStepState();
void UpdateStepUI(cSPMission* pMission);
void UpdateMissionStepState();
bool ReadMissionBase(void* pData);
void ClearMissionUI();
void RequestMissionRefresh();
cCivData* GetPlanetEmpire(uint32_t planetId);
void NotifyMissionEvent(uint32_t id);
double RoundValue(double fValue);
// ---- items of slice s00c5a580 end

// ---- items of slice s00c5b9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int       u32;
typedef unsigned short     u16;
typedef unsigned char      u8;
typedef          int       s32;
struct Vec3_s00c5_b9c0 {
  float x, y, z;
  Vec3_s00c5_b9c0& operator=(const Vec3_s00c5_b9c0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
void  __cdecl operator_delete_array(void* p);                            // 0x00f47380
struct IRef {
  virtual void v0();
  virtual void Release();          // vtable slot 4
};
struct MissionObjVt {              // property bag stored at cSPMission+0x180
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
  virtual void v08();
  virtual u8   GetProperty(u32 id, void** out);    // vtable slot 0x24
};
struct Property {
  float* GetFloat();                               // 0x0041ea70
};
struct cEntity {
  u32 pad000[0x21];
  u32 empireID;                    // 0x084
};
struct cPlaceList {
  u32 pad000[0x4d];                // 0x000
  u32 pl134Begin;                  // 0x134
  u32 pl134End;                    // 0x138
  u32 pl134Cap;                    // 0x13c
  Vec3_s00c5_b9c0*       GetCitiesPos();      // 0x005c65e0 (no arg form)
  void*       GetCitiesRef(void* ref); // 0x005c65e0 (query form)
  void*       FUN_00b8de30();      // 0x00b8de30
  u8          FUN_00b8e040(u32);   // 0x00b8e040
  void*       GetCommContext(void*);// 0x00ce6950
};
struct cPlanet {
  u32 pad000[0x4f];                // 0x000
  cPlaceList* p13c;                // 0x13c
  cEntity*    FUN_00c71e30();      // 0x00c71e30
};
struct cCivObject {                // cEmpire / cCivData shared surface
  u32  pad000[0x1b];
  u32  f06c;                       // 0x06c
  u32  f070;                       // 0x070
  void*  FUN_00c30c80();           // 0x00c30c80
  void*  FUN_00c30c60();           // 0x00c30c60
  Vec3_s00c5_b9c0*  GetCitiesPos();           // 0x005c65e0 (no arg form)
  void*  GetCitiesRef(void* ref);  // 0x005c65e0 (query form)
  Vec3_s00c5_b9c0*  GetUFOKey();              // 0x00c326b0
  u8     FUN_00c31bc0(void*);      // 0x00c31bc0
  void*  FUN_00b8de30();           // 0x00b8de30
  void*  FUN_00bb0e90(void*);      // 0x00bb0e90
};
struct cGameData2 {
  void FUN_00fe5430();             // 0x00fe5430
};
struct cSpaceGame {
  cGameData2* SetGameDataOwner2(); // 0x00fe53b0
};
struct cRelMgr {
  void RecordEvent(u32 a, u32 b, u32 ev, float v);   // 0x00d06240
  u8   FUN_00d01fb0(u32 a, u32 b);                   // 0x00d01fb0
  u8   FUN_00d01ff0(void* a, u32 b);                 // 0x00d01ff0
};
struct cStarMgr {
  cCivObject* GetEmpireByID(u32 id);                 // 0x00ba9370
  void*       FUN_00bb0e90(void* q);                 // 0x00bb0e90
};
struct cEventLog {
  void* PostFeedbackEvent(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f); // 0x00dd8640
  void  ModifyEventText(void* ev, void* text);                       // 0x00dd6df0
  void  EventDoNotAddToHistory(void* ev, u32 flag);                  // 0x00dd67d0
};
struct cCommMgr {
  void* FUN_00aeb3e0(u32 a, void* b);                // 0x00aeb3e0
};
struct cNounMgr {
  void* GetCurrentTerrainSphere();                   // 0x00f67d90
  void* GetAvatar();                                 // 0x00b1fdb0
  void  FUN_00bb9b00(s32 a, s32 b);                  // 0x00bb9b00
};
struct cMissionVt {                                  // primary vtable of cSPMission
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
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
  virtual void v40();
  virtual void* GetCommContext(u32 tag, s32 mode, void* self, s32 flag); // 0xa4
};
u32   __cdecl GetPlayerEmpireID();                   // 0x01021090
void* __cdecl GetPlayerEmpire();                     // 0x01021300
void  __cdecl ReleaseCreaturePosse(void* p);         // 0x0102c0c0
void  __cdecl GetPropertyT(void* obj, u32 id, void* out); // 0x0040cf10
cSpaceGame* __stdcall SpaceGameGet(s32 a, s32 b);    // 0x01002bd0
cRelMgr* __cdecl RelationshipManager();              // 0x00b3d2c0
cStarMgr* __cdecl StarManager();                     // 0x00b3d2a0
cEventLog* __cdecl EventLog();                       // 0x00b3d3e0
cCommMgr* __cdecl CommManager();                     // 0x00b3d4a0
cNounMgr* __cdecl NounManager_s00c5_b9c0();                     // 0x00b3d300
void* __cdecl FUN_00401010();                        // 0x00401010
Vec3_s00c5_b9c0* __cdecl FUN_00c75770();                        // 0x00c75770
s32   __cdecl FUN_00c70420(void* p);                 // 0x00c70420
void  __cdecl WStr_Format(void* out, const u16* fmt, u32 v); // 0x0041e050
float __cdecl RandomDoubleUniform();                 // 0x009360d0
struct SPVecU32 {
  u32* begin; u32* end; u32* cap;
  void DoInsertValue(u32* pos, const u32* val);      // 0x004558a0
};
struct cSPMission_s00c5_b9c0 {
  u32   vtbl000;                   // 0x000
  u32   vtbl004;                   // 0x004
  u32   pad008[11];                // 0x008
  u32   vtbl034;                   // 0x034
  u32   pad038[23];                // 0x038
  u32   targetEmpireID;            // 0x094
  u32   pad098[39];                // 0x098
  SPVecU32 ev134;                  // 0x134
  u32   pad140[16];                // 0x140
  void* p180;                      // 0x180
  u32   pad184[24];                // 0x184
  void* p1e4;                      // 0x1e4
  u32   pad1e8[2];                 // 0x1e8

  void  InitGeneric();             // 0x00c48e90
  void  Destroy();                 // 0x00c47680
  void* GetTargetPlanet();         // 0x00970b30
  u32   GetMissionID();            // 0x01030e10
  void  GetText(u32 tag, void* out);            // 0x00c487d0
  u8    GetTagString(u32 tag, void* out);       // 0x00c491c0
  void  OnAcceptBase();                         // 0x00c47a10
  void  HandlerComplete();                      // 0x00c46b80
  void  HandlerFail();                          // 0x00c469f0
};
struct cRaidEvent : cSPMission_s00c5_b9c0 {
  void* p1f0;
  u32   f1f4, f1f8, f1fc, f200, f204, f208;
  float f20c, f210;
  u8    b214, b215;
  u16   pad216;
  u32   f218;
  u8    b21c, b21d, b21e; u8 pad21f;
  u32   f220;
  Vec3_s00c5_b9c0  v224;
  u32   f230;
  u8    b234; u8 pad235[3];
  u32   f238, f23c, f240;
};
struct cStarRef {
  u32   flags;      // 0x00
  s32   mode;       // 0x04
  u32   f08;        // 0x08
  float f0c;        // 0x0c
  float f10;        // 0x10
  u32   f14;        // 0x14
  float f18;        // 0x18
};
struct WStr {
  u16* begin; u16* end; u16* cap;
};
// ---- items of slice s00c5b9c0 end

// @ 0x00c5b210
bool cPlanetMission::Read(void* pData)
{
    bool bBase = ReadMissionBase(pData);
    cVarListSerializer serializer(this, (const void*)0x01576bc8, 0x1a80d26);
    bool bFields = serializer.Serialize(pData) != 0;
    bool bOk = bBase && bFields;

    if (((ISerializer*)pData)->GetType() < 0x210014u)
        mTargetId = *(int*)((uint8_t*)this + 0x8c);
    return bOk;
}

// @ 0x00c5b280
void cPlanetMission::UpdateFromPlanet()
{
    UpdateMissionStepState();
    int nTarget = mTargetId;
    Vec3* pPosition;
    if (nTarget == -1) {
        cTerrainEditor* pEditor = NounManager();
        ((IRefCounted*)pEditor->GetCurrentTerrainSphere())->v10();
        pEditor = NounManager();
        pEditor->GetCurrentTerrainSphere();
        pPosition = GetTerrainSpherePosition();
    } else {
        IsPlanetValid(nTarget);
        int nEmpire = (int)(intptr_t)GetPlanetEmpire((uint32_t)nTarget);
        if (nEmpire == 0)
            return;
        pPosition = GetTerrainSpherePosition();
    }

    mPlanetPosition = *pPosition;

    void* pTuning = GetSpaceTuning();
    if (!((ISerializer*)pTuning)->Serialize(&mPlanetPosition))
        ClearMissionUI();
}

// @ 0x00c5b450
MissionElement* CopyMissionElementsForward(MissionElement* pFirst, MissionElement* pLast, MissionElement* pDest)
{
    while (pFirst != pLast) {
        *pDest = *pFirst;
        ++pFirst;
        ++pDest;
    }
    return pDest;
}

// @ 0x00c5b4b0
MissionElement* CopyMissionElementsBackward(MissionElement* pFirst, MissionElement* pLast, MissionElement* pDest)
{
    MissionElement* pSrc = pLast;
    while (pSrc != pFirst) {
        --pSrc;
        --pDest;
        *pDest = *pSrc;
    }
    return pDest;
}

// @ 0x00c5b510
void cSPRaidPlunderEvent::GeneratePirateCount()
{
    sGetNumUFOs(this, 0x398db08, 0x398db09);
}

// @ 0x00c5b530
void cSPRaidEvent::GenerateBomberCount()
{
    sGetNumUFOs(this, 0x2fd1ef6, 0x2fd1efa);
}

// @ 0x00c5b550
void cSPRaidPlunderEvent::BackgroundUpdate()
{
    uint32_t nPlanet = GetTargetPlanet();
    if (IsPlanetValid(nPlanet))
        return;

    GetTargetPlanet();
    void* pWorld = GetActivePlanet();
    uint32_t nPlanetId = GetTargetPlanet();
    int pList = *(int*)((uint8_t*)(void*)nPlanetId + 0x13c);
    int nCount = (*(int*)((uint8_t*)pList + 0x138) - *(int*)((uint8_t*)pList + 0x134)) / 0x2c;
    for (int i = nCount - 1; i >= 0; --i) {
        uint8_t* pEntry = (uint8_t*)(*(int*)((uint8_t*)pList + 0x134) + i * 0x2c);
        if ((*(uint8_t*)(pEntry + 0x28) & 8) != 0 && *(uint8_t*)(pEntry + 0x12) == 4) {
            uint32_t artifact[3];
            artifact[0] = *(uint32_t*)pEntry;
            artifact[1] = 0;
            artifact[2] = 0;
            RemoveArtifact(pList, artifact, *(uint16_t*)(pEntry + 0x10));
        }
    }
    (void)pWorld;
}

// @ 0x00c5b600
bool cSPRaidEvent::Init(int a, int b, int c)
{
    if (!cSPMission::Init())
        return false;

    void* pDefinition = nullptr;
    if (pDefinition != nullptr) {
        if (((ISerializer*)pDefinition)->Serialize((void*)0x39787b4) && (c & 0x10000) != 0) {
            uint8_t* pKeyArray = nullptr;
            GetPropertyAsKeyArray(nullptr, 0x39787b4, nullptr);
            (void)pKeyArray;
        }
    }
    (void)a;
    (void)b;
    return true;
}

// @ 0x00c5b660
void cSPRaidEvent::Shutdown()
{
    GetTargetPlanet();
    SpawnRaidUFOs(nullptr, 0, 0);
    RequestMissionRefresh();
    uint32_t nPlanet = GetTargetPlanet();
    SetPlanetHighlight(nPlanet);
    ShutdownMissionStepState();
    NotifyMissionEvent(0);

    cMessageServer* pServer = MessageServer();
    pServer->v2c(&mTargetId, (const void*)0x01622184, 0xffffd8f1);
}

// @ 0x00c5b6c0
uint32_t cSPRaidEvent::CheckDistanceCondition()
{
    uint32_t nContext = (uint32_t)(intptr_t)GetUniverseContext();
    (void)nContext;
    void* pTuning = GetSpaceTuning();
    if (!((ISerializer*)pTuning)->Serialize(&mTargetId))
        return 0;

    cUFOKinestheticsTuning* pKinesthetics = GetKinestheticsTuning();
    float fWarpSpeed = pKinesthetics->mWarpSpeed;
    pKinesthetics = GetKinestheticsTuning(1, 4);
    double fMultiplier = pKinesthetics->GetGalaxyWarpMultiplier(1, 4);

    cCivData* pTarget = nullptr;
    uint32_t nEmpire = (uint32_t)mTargetId;
    if (nEmpire != 0)
        pTarget = GetPlanetEmpire(nEmpire);

    GetTargetPlanet();
    cCivData* pPlanet = GetPlanetEmpire(0);
    Vec3* pCitiesA = pPlanet->GetCities();
    Vec3* pCitiesB = pTarget->GetCities();

    float fDx = pCitiesB->mX - pCitiesA->mX;
    float fDy = pCitiesB->mY - pCitiesA->mY;
    float fDz = pCitiesB->mZ - pCitiesA->mZ;
    float fDistance = (float)(__builtin_sqrtf(fDx * fDx + fDy * fDy + fDz * fDz) /
                              (fMultiplier * (double)fWarpSpeed));
    if (fDistance > 10000.0f)
        fDistance = 10000.0f;

    float fBudget = (float)mTargetId;
    if (fBudget <= 10000.0f - fDistance)
        return 0;
    return 1;
}

// @ 0x00c5b860
void cSPRaidEvent::Update()
{
    float fThreshold = 10.0f;
    void* pDefinition = nullptr;
    if (pDefinition != nullptr) {
        if (((ISerializer*)pDefinition)->Serialize((void*)0x3a38abe) &&
            *(uint16_t*)((uint8_t*)pDefinition + 0x12) == 0xd) {
            float* pValue = (float*)GetPropertyAsFloat();
            fThreshold = *pValue;
        }
    }

    int nScaled = (int)(float)RoundValue((double)fThreshold * 1000.0);

    cUFOKinestheticsTuning* pKinesthetics = GetKinestheticsTuning();
    float fWarpSpeed = pKinesthetics->mWarpSpeed;
    pKinesthetics = GetKinestheticsTuning(1, 4);
    double fMultiplier = pKinesthetics->GetGalaxyWarpMultiplier(1, 4);

    cCivData* pTarget = nullptr;
    uint32_t nEmpire = (uint32_t)mTargetId;
    if (nEmpire != 0)
        pTarget = GetPlanetEmpire(nEmpire);

    GetTargetPlanet();
    cCivData* pPlanet = GetPlanetEmpire(0);
    Vec3* pCitiesA = pPlanet->GetCities();
    Vec3* pCitiesB = pTarget->GetCities();

    float fDx = pCitiesB->mX - pCitiesA->mX;
    float fDy = pCitiesB->mY - pCitiesA->mY;
    float fDz = pCitiesB->mZ - pCitiesA->mZ;
    float fDistance = (float)(__builtin_sqrtf(fDx * fDx + fDy * fDy + fDz * fDz) /
                              (fMultiplier * (double)(fWarpSpeed * (float)nScaled)));
    if (fDistance > 10000.0f)
        fDistance = 10000.0f;

    UpdateStepUI(this);
}

// @ 0x00c5b9c0
void __fastcall FUN_00c5b9c0(cRaidEvent* self, void* dummy)
{
  (void)dummy;
  float val;
  void* prop;

  if (self->b21c != 0) goto done;
  if (self->p180 == 0) goto done;
  val = 0.0f;
  prop = 0;
  if (((MissionObjVt*)self->p180)->GetProperty(0x39787b3, &prop) != 0 &&
      *(u16*)((char*)prop + 0x12) == 0xd) {
    val = *((Property*)prop)->GetFloat();
  }
  {
    cPlanet* planet = (cPlanet*)self->GetTargetPlanet();
    if (planet != 0) {
      cEntity* ent = planet->FUN_00c71e30();
      if (ent == 0) goto done;
      {
        u32 other = ent->empireID;
        u32 me = GetPlayerEmpireID();
        if (other != me) {
          RelationshipManager()->RecordEvent(other, me, 0x526e519, val);
          if (RelationshipManager()->FUN_00d01fb0(other, me) == 0)
            goto done;
        }
        SpaceGameGet(0x12, 1)->SetGameDataOwner2()->FUN_00fe5430();
      }
    }
  }
done:
  ReleaseCreaturePosse(self->GetTargetPlanet());
  self->HandlerComplete();
}

// @ 0x00c5bab0
void __fastcall FUN_00c5bab0(cRaidEvent* self, void* dummy)
{
  (void)dummy;
  ReleaseCreaturePosse(self->GetTargetPlanet());
  if (GetUniverseContext() == 0) {
    if (self->GetTargetPlanet() == GetActivePlanet()) {
      self->HandlerComplete();
      return;
    }
  }
  if (self->p180 != 0) {
    u32 other = self->targetEmpireID;
    if (other != GetPlayerEmpireID()) {
      cCivObject* emp = StarManager()->GetEmpireByID(other);
      if (emp != 0) {
        if (RelationshipManager()->FUN_00d01ff0(emp, 0) != 0) {
          float f = 0.0f;
          GetPropertyT(self->p180, 0x39787ae, &f);
          float v = (float)(f < 0.0f ? -f : f);
          RelationshipManager()->RecordEvent(other, GetPlayerEmpireID(), 0x526e51c, v);
        }
      }
    }
  }
  self->HandlerFail();
}

// @ 0x00c5bea0
void* __fastcall FUN_00c5bea0(cRaidEvent* self, void* dummy, u32 flags)
{
  (void)dummy;
  if (self->f238 != 0 && ((u32*)self->f238)[-1] != 0)
    operator_delete_array((void*)self->f238);
  {
    IRef* ref = (IRef*)self->p1f0;
    if (ref != 0)
      ref->Release();
  }
  self->Destroy();
  if ((flags & 1) != 0)
    operator_delete_array(self);
  return self;
}

// @ 0x00c5c410
u8 __fastcall FUN_00c5c410(cRaidEvent* self, void* dummy, u32 tag, void* out)
{
  (void)dummy;
  if (tag == 0x21eb4188) {
    if (self->f230 != 0xffffffff) {
      cCivObject* emp = StarManager()->GetEmpireByID(self->f230);
      if (emp != 0) {
        emp->FUN_00c30c80();
        WStr_Format(out, (const u16*)0x013f5c04, *(u32*)emp->GetCitiesPos());
      }
    }
    return 1;
  }
  return self->GetTagString(tag, out);
}

// @ 0x00c5c470
void __fastcall FUN_00c5c470(cRaidEvent* self, void* dummy)
{
  (void)dummy;
  self->OnAcceptBase();

  if (self->b21e != 0 && self->GetMissionID() != 0xbbae6b99) {
    cPlanet* planet = (cPlanet*)self->GetTargetPlanet();
    *(void**)(*(u32*)0x016e0d08 + 0xc) = planet->p13c;

    {
      WStr text;
      text.begin = text.end = (u16*)0x01667bac;
      text.cap = (u16*)0x01667bae;
      self->GetText(0xa3139d, &text);

      {
        u32 ev = (u32)EventLog()->PostFeedbackEvent(0x6c0fa994, 0x131a9f54, 0, 0, 1, 0);
        EventLog()->ModifyEventText((void*)ev, text.begin);
        EventLog()->EventDoNotAddToHistory((void*)ev, 1);
        if (self->ev134.end < self->ev134.cap) {
          u32* p = self->ev134.end;
          self->ev134.end = p + 1;
          if (p != 0)
            *p = ev;
        } else {
          self->ev134.DoInsertValue(self->ev134.end, &ev);
        }
      }

      if ((((u32)text.cap - (u32)text.begin) & 0xfffffffeu) > 2 && text.begin != 0)
        operator_delete_array(text.begin);
    }

    {
      cPlanet* p = (cPlanet*)self->GetTargetPlanet();
      if (p != 0) {
        cEntity* ent = ((cPlanet*)self->GetTargetPlanet())->FUN_00c71e30();
        void* me = GetPlayerEmpire();
        if (ent != 0 && (ent == (cEntity*)me ||
                         ((cCivObject*)ent)->FUN_00c31bc0(me) != 0)) {
          cPlaceList* pl1 = ((cPlanet*)self->GetTargetPlanet())->p13c;
          cPlaceList* pl2 = ((cPlanet*)self->GetTargetPlanet())->p13c;
          u32 flag = (ent == (cEntity*)me);
          u32 empID = ent->empireID;

          {
            void* ctx = ((cMissionVt*)self->vtbl000)->GetCommContext(0x8b756f4b, 2, self, (s32)flag);
            void* comm = pl2->FUN_00b8de30();
            void* res = CommManager()->FUN_00aeb3e0(empID,
                          (void*)((cPlaceList*)pl1)->GetCommContext(ctx));
            void* old = self->p1e4;
            (void)comm;
            if (res != old) {
              if (res != 0)
                (*(void(__thiscall**)(void*))*(void**)res)(res);
              self->p1e4 = res;
              if (old != 0)
                ((IRef*)old)->Release();
            }
          }
        }
      }
    }

    {
      cPlaceList* pl = ((cPlanet*)self->GetTargetPlanet())->p13c;
      s32 n = (s32)((pl->pl134End - pl->pl134Begin) / 0x2c);
      s32 cnt = 0;
      if (n > 0) {
        u32* e = (u32*)pl->pl134Begin;
        s32 k = n;
        do {
          if (((u8*)e)[0x28] & 1) {
            if (*e != *(u32*)0x016922ac)
              cnt++;
          }
          e += 0xb;
        } while (--k != 0);
      }
      {
        float ratio = (float)cnt / (float)(FUN_00c70420(pl) + cnt);
        if (ratio >= RandomDoubleUniform())
          self->b214 = 1;
      }
    }
  }

  self->b21d = 1;

  {
    cPlaceList* pl = ((cPlanet*)self->GetTargetPlanet())->p13c;
    void* mgr = pl->FUN_00b8de30();
    cCivObject* emp;

    ((cNounMgr*)mgr)->FUN_00bb9b00(0x200, 1);
    self->targetEmpireID = (u32)((cNounMgr*)mgr)->GetAvatar();
    emp = StarManager()->GetEmpireByID(self->f230);

    if (emp != 0) {
      Vec3_s00c5_b9c0* c = emp->GetUFOKey();
      self->v224 = *c;
    } else {
      cNounMgr* nm = NounManager_s00c5_b9c0();
      Vec3_s00c5_b9c0* c = (Vec3_s00c5_b9c0*)nm->GetCurrentTerrainSphere();
      self->v224 = *(Vec3_s00c5_b9c0*)((u32*)c ? FUN_00c75770() : 0);
    }

    {
      void* obj = FUN_00401010();
      u8 ok = (*(u8(__thiscall**)(void*, Vec3_s00c5_b9c0*, s32))*(void**)(*(u32*)obj + 0x1c))(obj, &self->v224, 0);
      if (ok == 0) {
        cStarRef ref;
        obj = FUN_00401010();
        ref.flags = 0x1ff1;
        ref.mode  = 0x1e;
        ref.f08   = 0;
        ref.f0c   = 0.0f;
        ref.f10   = *(float*)0x013eecd8;
        ref.f14   = 0;
        ref.f18   = -1.0f;
        (*(void(__thiscall**)(void*, Vec3_s00c5_b9c0*, cStarRef*))*(void**)(*(u32*)obj + 0x4c))(obj, &self->v224, &ref);
      }
    }

    if (emp != 0) {
      cCivObject* c = (cCivObject*)emp->FUN_00c30c60();
      self->f1f4 = c->f070;
    } else {
      cNounMgr* nm2 = NounManager_s00c5_b9c0();
      (void)nm2;
      {
        cPlaceList* plx = ((cPlanet*)self->GetTargetPlanet())->p13c;
        cStarRef ref;
        ref.flags = 0x1ff1;
        ref.mode  = 0x1e;
        ref.f08   = 0;
        ref.f0c   = 0.0f;
        ref.f10   = *(float*)0x013eecd8;
        ref.f14   = 0;
        ref.f18   = -1.0f;
        void* r = StarManager()->FUN_00bb0e90(plx->GetCitiesRef(&ref));
        if (r == 0) {
          ref.flags |= 0x20;
          r = StarManager()->FUN_00bb0e90(plx->GetCitiesRef(&ref));
        }
        self->f1f4 = *(u32*)((char*)r + 0x70);
      }
    }
  }
}
