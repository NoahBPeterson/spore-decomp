// src/game/SPGonzago/SPMissionRaid.cpp -- migrated from slice(s) s00c5d640, s00c5c860, s00c5b9c0, s00c5a580 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionRaid.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "sse_helpers.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cGameData.h"
#include "SP/cSPMission.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include "SP/cPlanet.h"
#include "SP/cGameNounManager.h"

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
extern "C" extern float g_elemPosX;      // 0x01691fc8
extern "C" extern float g_elemPosY;      // 0x01691fcc
extern "C" extern float g_elemPosZ;      // 0x01691fd0
extern "C" extern float g_elemNegOne;    // 0x013eb1bc
typedef unsigned int       u32;
typedef unsigned short     u16;
typedef unsigned char      u8;
typedef          int       s32;
struct Vec3_s00c5_b9c0 {
  float x, y, z;
  Vec3_s00c5_b9c0& operator=(const Vec3_s00c5_b9c0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct MissionElem {
  u32   vtbl;      // 0x00
  s32   id;        // 0x04
  Vec3_s00c5_b9c0  pos;       // 0x08
  float f14;       // 0x14
  float f18;       // 0x18
  s32   i1c;       // 0x1c
};
struct MissionElem;
struct ElemVec {
  MissionElem* begin;   // 0x00
  MissionElem* end;     // 0x04
  MissionElem* cap;     // 0x08

  void Insert(MissionElem* pos, MissionElem* val);   // 0x00c5bf80
  void PushDefault();                                // 0x00c5c240
};
MissionElem* __cdecl CopyMissionElementsForward(MissionElem* first, MissionElem* last,
                                                MissionElem* dst);       // 0x00c5b450
MissionElem* __cdecl CopyMissionElementsBackward(MissionElem* first, MissionElem* last,
                                                 MissionElem* dst);      // 0x00c5b4b0
MissionElem* __cdecl FUN_00c5bbc0(MissionElem* first, MissionElem* last, MissionElem* dst);
void* __cdecl operator_new(u32 size, const char* name, s32 a, s32 b,
                           const char* file, s32 line);                  // 0x00f473a0
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
struct cSpaceCombatTuning {
  s32   GetWeaponLevel(Vec3_s00c5_b9c0 v);                      // 0x0102a360
  float GetBackgroundUberTurretDPS();                // 0x01029e70
  float GetUFOHealth(s32 a, s32 b);                  // 0x0102a630
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
cSpaceCombatTuning* __cdecl GetSpaceCombatTuning();  // 0x01029940
void* __cdecl FUN_00401010();                        // 0x00401010
void* __cdecl FUN_00fe3b10(cPlanet* p);              // 0x00fe3b10
Vec3_s00c5_b9c0* __cdecl FUN_00c75770();                        // 0x00c75770
s32   __cdecl FUN_00c70420(void* p);                 // 0x00c70420
void  __cdecl WStr_Format(void* out, const u16* fmt, u32 v); // 0x0041e050
// cRandomGlobal::RandomDouble (0x009360d0) is a thiscall member on the global at 0x01601760.
struct cRandomGlobal_c5 { float RandomDouble(); };
extern cRandomGlobal_c5 g_cRandomGlobal;            // 0x01601760
// retail inlined the CRT __ftol2_sse helper (`fstp dword; cvtss2si` = round-to-nearest);
// a plain (s32) cast truncates with cvttss2si, which the equivalence gate also fails.
// RoundToInt_c5c310: the vetted SseRoundToInt in sse_helpers.h

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

// ---- items of slice s00c5c860 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3_s00c5_c860 {
    float x, y, z;
    Vec3_s00c5_c860(const Vec3_s00c5_c860& o) : x(o.x), y(o.y), z(o.z) {}
};
}
namespace SP {
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
bool GetFloatProperty(PropertyList* list, uint32_t propertyID, float& result);   // 0x40cf10
}
namespace SP {
struct PropertyManager {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst);   // +0x2c
};
}
namespace SP {
PropertyManager* GetPropertyManager();   // 0x67de30
}
namespace SP {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
}
namespace SP {
class cSPSpaceCombatTuning { public:
    int   GetWeaponLevel(Vec3_s00c5_c860 pos);                       // 0x102a360 (ret 0xc)
    float GetBackgroundTurretDPS(int level);              // 0x1029de0
    float GetBackgroundBomberDPS(int level);              // 0x1029d50
    float GetBackgroundFighterDPS(int level);             // 0x1029cc0
    float GetBackgroundUberTurretDPS();                   // 0x1029e70
    float GetTurretHealth(int level);                     // 0x102a780
    float GetUFOHealth(int type, int level);              // 0x102a630
    float GetCityCaptureFactor(int politicalID, int);     // 0x1029be0
};
}
namespace SP {
cSPSpaceCombatTuning* GetSpaceCombatTuning_s00c5_c860();             // 0x1029940
}
namespace SP {
class cEmpire_s00c5_c860 { public:
    float GetBackgroundFighterDPS();                      // 0xc31890
    float GetBackgroundBomberDPS();                       // 0xc318c0
    float GetBackgroundTurretDPS();                       // 0xc318f0
    float GetUFOHealth(int type);                         // 0xc31920
    float GetTurretHealth();                              // 0xc31960
};
}
namespace SP {
class cStarManager_s00c5_c860 { public:
    cEmpire_s00c5_c860* GetEmpireByID(int id);                       // 0xba9370
};
}
namespace SP {
cStarManager_s00c5_c860* StarManager_s00c5_c860();                              // 0xb3d2a0
}
namespace SP {
class cCivData_s00c5_c860 { public:
    const Vec3_s00c5_c860& GetCities();                              // 0x5c65e0
};
}
namespace SP {
struct cOwnerNoun {
    int GetAvatar();                                      // 0xb1fdb0 (field at +0x54)
};
}
namespace SP {
struct SimpleVectorU {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void DoInsertValue(uint32_t* pos, const uint32_t& v);     // 0x4558a0
    void push_back(const uint32_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p)
                *p = v;
        }
        else
            DoInsertValue(mpEnd, v);
    }
};
}
namespace SP {
class cCity_s00c5_c860 { public:
    uint8_t  pad00[0x24];
    int      mnCount;               // +0x24
    uint8_t  pad28[0xbc - 0x28];
    uint32_t mTurretKeyA;           // +0xbc
    uint32_t mTurretKeyB;           // +0xc0
    int      GetCount();                                  // 0xff35d0
    int      GetNumTurrets();                             // 0xff0760
    int      GetNumBuildings();                           // 0xff0870
    float    GetHealth();                                 // 0xb7e0a0
    int      GetOwnerID();                                // 0xa1ad10
    void     RemoveTurret();                              // 0xff07e0
    void     SetCount(int n);                             // 0x9879d0
};
}
namespace SP {
struct cCityGroup {
    uint8_t  pad00[0x3c];
    cCity_s00c5_c860**  mpCitiesBegin;         // +0x3c
    cCity_s00c5_c860**  mpCitiesEnd;           // +0x40
    int      GetOwnerID();                                // 0xff0420
    int      CityCount() const { return (int)(mpCitiesEnd - mpCitiesBegin); }
};
}
namespace SP {
struct BuildingRec {
    uint32_t id;                    // +0x00
    uint8_t  pad04[0x10];
    float    health;                // +0x14
    uint8_t  pad18[0x10];
    uint32_t flags;                 // +0x28
};
}
namespace SP {
struct ForceElem {
    uint32_t pad00;
    int      type;                  // +4
    uint8_t  pad08[0x18];
};
}
namespace SP {
class cPlanetRecord_s00c5_c860 { public:
    uint8_t  pad00[0x134];
    BuildingRec* mpRecBegin;        // +0x134
    BuildingRec* mpRecEnd;          // +0x138
    uint8_t  pad13c[0x148 - 0x13c];
    SimpleVectorU mDestroyedKeys;   // +0x148
    uint8_t  pad154[0x15c - 0x154];
    cCityGroup** mpGroupsBegin;     // +0x15c
    cCityGroup** mpGroupsEnd;       // +0x160
    cOwnerNoun* GetOwner();                               // 0xb8de30
    cCityGroup* GetGroup(int i);                          // 0xb8dec0
    bool        HasBuildingRec(uint32_t id);              // 0xb8e040
    void        RemoveBuildingRec(uint32_t id);           // 0xb8e7d0
    int RecCount() const { return (int)(mpRecEnd - mpRecBegin); }
    int GroupCount() const { return (int)(mpGroupsEnd - mpGroupsBegin); }
};
}
namespace SP {
struct cForceList {
    ForceElem* mpBegin;             // +0
    ForceElem* mpEnd;               // +4
};
}
namespace SP {
struct cBattle {
    uint8_t    pad00[0x13c];
    cPlanetRecord_s00c5_c860* mpPlanet;        // +0x13c
    void FUN_00c711e0(cCity_s00c5_c860* city);                       // 0xc711e0
};
}
namespace SP {
extern uint32_t kPlaceUberTurretID;                       // 0x16922ac
}
namespace SP {
bool    FUN_00fe3b10(cBattle* b);                         // cdecl
}
namespace SP {
void*   FUN_0107bcb0();                                   // 0x107bcb0 (global getter)
}
namespace SP {
cPlanetRecord_s00c5_c860* GetPlayerHomePlanet();                  // 0x1021370
}
namespace SP {
int     FUN_00c702f0(cPlanetRecord_s00c5_c860* p);                   // cdecl
}
namespace SP {
bool    FUN_01029a10(int politicalID, cPlanetRecord_s00c5_c860* p);  // cdecl
}
namespace SP {
float   FUN_00bd7fb0(int, int);                           // cdecl
}
namespace SP {
void    FUN_00be9b20(cPlanetRecord_s00c5_c860* p, int zero, cCity_s00c5_c860* city, int groupOwner, float amount);   // cdecl
}
namespace SP {
ForceElem* EraseCopy(ForceElem* srcBegin, ForceElem* srcEnd, ForceElem* dst);   // 0xc5b450 cdecl
}
namespace SP {
struct cGameDataStub {
    int GetGameDataOwner();                               // 0x967e70 (field at +0x2c)
};
}
// ---- items of slice s00c5c860 end

// ---- items of slice s00c5d640 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3_s00c5_d640 {
    float x, y, z;
    Vec3_s00c5_d640() {}
    Vec3_s00c5_d640(const Vec3_s00c5_d640& o) : x(o.x), y(o.y), z(o.z) {}
};
}
namespace SP {
extern wchar_t gEmptyWString[];   // 0x01667bac
}
namespace SP {
struct WStr_s00c5_d640 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    WStr_s00c5_d640() { mpBegin = gEmptyWString; mpEnd = gEmptyWString; mpCapacity = gEmptyWString + 1; }
    void DeallocateSelf();        // 0x00933960
    ~WStr_s00c5_d640()
    {
        if ((((int)((char*)mpCapacity - (char*)mpBegin)) & 0xfffffffe) > 2 && mpBegin != 0)
            ::operator delete(mpBegin);
    }
};
}
namespace SP {
extern Vec3_s00c5_d640  gDefaultVec3;        // 0x01691fc8
}
namespace SP {
extern float gFloat_01473c70;     // 0x01473c70  (10.0f)
}
namespace SP {
extern float gFloat_013ec5b4;     // 0x013ec5b4  (1000.0f)
}
namespace SP {
extern float gFloat_013f9428;     // 0x013f9428  (0.001f)
}
namespace SP {
extern int   gGameDataTag;        // 0x018ebadc
}
namespace SP {
void* __cdecl GetUniverseContext();   // 0x01021080
}
namespace SP {
void* __cdecl GetActivePlanet();      // 0x01021260
}
namespace SP {
void* __cdecl GetPlayerEmpire();      // 0x01021300
}
namespace SP {
void* __cdecl GetSpaceCombatTuning_s00c5_d640(); // 0x01029940
}
namespace SP {
void* __cdecl GameTimeManager();      // 0x00b3d380
}
namespace SP {
void* __cdecl GetUFOSimulator();      // 0x00ffbe50
}
namespace SP {
void* __cdecl FUN_00401010();         // 0x00401010
}
namespace SP {
void* __cdecl FUN_00ae3370(void* p);  // 0x00ae3370
}
namespace SP {
void* __cdecl FUN_00c5b430(void* p);  // 0x00c5b430  interface_cast<cBuilding*,cCombatant>
}
namespace SP {
void  __cdecl FUN_00c5b450(void* a, void* b, void* c);   // 0x00c5b450  copy records (32B elems)
}
namespace SP {
void  __cdecl FUN_00c5d140(void* m, void* vec, int a, void* b, Vec3_s00c5_d640 v, int c, int d);  // 0x00c5d140
}
namespace SP {
void  __cdecl FUN_00c5c310(void* a0, void* a1, void* a2, void* a3, int a4, int a5);   // 0x00c5c310
}
namespace SP {
void  __cdecl FUN_00c5c0f0(void* a0, void* a1, void* a2, void* a3, void* a4, int a5); // 0x00c5c0f0
}
namespace SP {
void  __cdecl FUN_00410370(void* prop, uint32_t id, int* out);   // 0x00410370  (GetPropertyAsInt)
}
namespace SP {
void  __cdecl FUN_0040cf10(void* prop, uint32_t id, float* out); // 0x0040cf10  GetPropertyT<int>
}
namespace SP {
struct Planet   { void FUN_00c70fd0(int v); };                       // 0x00c70fd0  ret 4
}
namespace SP {
void* __cdecl FUN_0102c0c0(void* self);                          // 0x0102c0c0
}
namespace SP {
char  __cdecl FUN_00fe3b10(void* self);                          // 0x00fe3b10  returns char
}
namespace SP {
void* __cdecl FUN_00b3d4a0();                      // 0x00b3d4a0  CommManager global (0 args)
}
namespace SP {
struct CommMgr {
    void* FUN_00aeb3e0(void* a1, void* a2, void* a3, void* a4,
                       void* a5, void* a6, void* a7, void* a8);   // 0x00aeb3e0 ret 0x20
};
}
namespace SP {
void* __cdecl FUN_00cd7d10();         // 0x00cd7d10 (game-data descriptor)
}
namespace SP {
void* __cdecl FUN_00d3d420();         // 0x00d3d420
}
namespace SP {
void* __cdecl FUN_00ad48b0();         // 0x00ad48b0
}
namespace SP {
void* __cdecl FUN_00b1e500();         // 0x00b1e500
}
namespace SP {
struct GameObject {
    void* FUN_00c37710();   // 0x00c37710  -> [this+0x800]
    char  FUN_00c372b0();   // 0x00c372b0
    void* FUN_00c38b00();   // 0x00c38b00
};
}
namespace SP {
struct GameDataVec { int pad0; void** begin; void** end; };
}
namespace SP {
struct cGameNounManager_s00c5_d640 {
    GameDataVec* GetGameDataVector(void* a, void* b, void* c, void* d, int* e);  // 0x00b21340 ret 0x14
};
}
namespace SP {
cGameNounManager_s00c5_d640* __cdecl SP_NounManager();   // 0x00b3d300
}
namespace SP {
struct Rec {                 // 0x20-byte combat record appended to the output vector
    uint32_t f00;
    uint32_t f04;
    float    f08, f0c, f10;
    float    f14;
    float    f18;
    int      f1c;
};
}
namespace SP {
struct RecVec {              // {begin,end,cap}
    Rec* begin;
    Rec* end;
    Rec* cap;
    void AppendDefault();    // 0x00c5c240  (grows by one, constructs a default Rec)
};
}
namespace SP {
struct ObjVec {              // {begin,end,cap} of ref-counted object pointers
    void** begin;
    void** end;
    void** cap;
    void  PushBack(void* const* src);   // 0x00e1c7f0 ret 4
};
}
namespace SP {
struct Mission {
    void* GetTargetPlanet();                 // 0x00970b30
    void* GetOwnerEmpire();                  // 0x00c451e0
    void  GetText(uint32_t key, WStr_s00c5_d640* out);  // 0x00c487d0
    int   Update(int dt);                    // 0x00c478b0 ret 4
    void  FUN_00c485e0();                    // 0x00c485e0
};
}
namespace SP {
struct EventLog_s00c5_d640 {
    void* PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f); // 0x00dd8640 ret 0x18
    void  ModifyEventText(void* ev, wchar_t* text);                             // 0x00dd6df0 ret 8
    void  EventDoNotAddToHistory(void* ev, int flag);                           // 0x00dd67d0 ret 8
};
}
namespace SP {
EventLog_s00c5_d640* __cdecl GetEventLog();        // 0x00b3d3e0  (0 args)
}
namespace SP {
struct Empire   { char FUN_00c31bc0(void* other); };                 // 0x00c31bc0
}
namespace SP {
struct StarRec  { void* GetCommContext(); };                         // 0x00ce6950  [ecx+0x184], 0 args
}
namespace SP {
struct ThrB8    { void* FUN_00b8de30(); };                           // 0x00b8de30  0 args
}
namespace SP {
struct Tuning   { float FUN_0102a590(); };                           // 0x0102a590
}
namespace SP {
struct AutoRef  { void operator=(void* p); };                        // 0x00b5f950
}
namespace SP {
struct UFOSim   { void* GetPlayerInventory(); };                     // 0x00a1ad60
}
namespace SP {
struct Combatant{ int GetDamageState(); };                           // 0x008e7f80
}
namespace SP {
typedef void* (__thiscall *ThunkV0)(void*);
}
namespace SP {
typedef char  (__thiscall *ThunkV0c)(void*);
}
namespace SP {
typedef float (__thiscall *ThunkV0f)(void*);
}
namespace SP {
static inline void* vcall0(void* o, int slot) { return ((ThunkV0)(*(void***)o)[slot])(o); }
}
namespace SP {
static inline char   vcallc(void* o, int slot) { return ((ThunkV0c)(*(void***)o)[slot])(o); }
}
namespace SP {
struct RaidHandler {
    char BaseHandleMessage(uint32_t msg, void* m);   // 0x00c4a6b0 (cSPMission::HandleMessage)
    bool HandleMessage_F50(uint32_t msg, void* m);   // 0x00c5df50
    bool HandleMessage_020(uint32_t msg, void* m);   // 0x00c5e020

    template<class T> T& F(int off) { return *(T*)((char*)this + off); }
    Mission* Mis() { return (Mission*)((char*)this - 0x34); }
};
}
namespace SP {
struct RaidPlunderEvent {
    template<class T> T& F(int off) { return *(T*)((char*)this + off); }
    void  BackgroundUpdate(int a);      // 0x00c5b550
    int   Update(int dt);               // 0x00c5dae0
};
}
// ---- items of slice s00c5d640 end

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

// @ 0x00c5b340
uint32_t cPlanetMission::GetOwnerEmpireId()
{
    uint32_t nEmpire = GetTargetPlanet();
    if (nEmpire == 0)
        return 0;
    IsPlanetValid(nEmpire);
    return (uint32_t)(intptr_t)GetPlanetEmpire(nEmpire);
}

// @ 0x00c5b370
void cPlanetMission::SetTarget(int nTarget)
{
    if (nTarget != 0)
        mTargetId = *(int*)((uint8_t*)this + 0x84);
}

// @ 0x00c5b3a0
void cPlanetMission::SetPlanetPosition(int a, int b, int c)
{
    *(int*)((uint8_t*)this + 0x224) = a;
    *(int*)((uint8_t*)this + 0x228) = b;
    *(int*)((uint8_t*)this + 0x22c) = c;
}

// @ 0x00c5b3d0
void WriteMissionElementList(ISerializer* pSerializer, MissionElement** ppElements)
{
    MissionElement* pBegin = ppElements[0];
    MissionElement* pEnd = ppElements[1];

    IOStream* pStream = pSerializer->GetStream();
    uint32_t nType = 0;
    int nCount = (int)((uint8_t*)pEnd - (uint8_t*)pBegin) >> 5;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    for (MissionElement* pCur = pBegin; pCur != pEnd; ++pCur)
        ((IRefCounted*)pCur->mField00)->AddRef();

    nCount = 0;
    (void)nCount;
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

// @ 0x00c5bbc0
MissionElem* __cdecl FUN_00c5bbc0(MissionElem* first, MissionElem* last, MissionElem* dst)
{
  if (first != last) {
    do {
      if (dst != 0) {
        dst->vtbl = 0x0146f688;
        dst->id    = first->id;
        dst->pos   = first->pos;
        dst->f14   = first->f14;
        dst->f18   = first->f18;
        dst->i1c   = first->i1c;
      }
      first++;
      dst++;
    } while (first != last);
  }
  return dst;
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

// @ 0x00c5bf80
void __fastcall FUN_00c5bf80(ElemVec* vec, void* dummy, MissionElem* pos, MissionElem* val)
{
  (void)dummy;
  MissionElem* p = vec->end;

  if (p != vec->cap) {
    if (val >= pos && val < p)
      val++;
    if (p != 0) {
      p->vtbl  = 0x0146f688;
      p->id    = p[-1].id;
      p->pos.x = p[-1].pos.x;
      p->pos.y = p[-1].pos.y;
      p->pos.z = p[-1].pos.z;
      p->f14   = p[-1].f14;
      p->f18   = p[-1].f18;
      p->i1c   = p[-1].i1c;
    }
    CopyMissionElementsBackward(pos, p - 1, p);
    pos->id    = val->id;
    pos->pos.x = val->pos.x;
    pos->pos.y = val->pos.y;
    pos->pos.z = val->pos.z;
    pos->f14   = val->f14;
    pos->f18   = val->f18;
    pos->i1c   = val->i1c;
    ++vec->end;
    return;
  }

  {
    s32 n = (s32)(vec->end - vec->begin);
    s32 cap = n ? n * 2 : 1;
    MissionElem* buf;
    MissionElem* mid;

    if (cap != 0)
      buf = (MissionElem*)operator_new((u32)(cap * 0x20), "Simulator", 0, 0,
                                       (const char*)0x013ebb38, 0xd1);
    else
      buf = 0;

    mid = FUN_00c5bbc0(vec->begin, pos, buf);
    if (mid != 0) {
      mid->vtbl  = 0x0146f688;
      mid->id    = val->id;
      mid->pos.x = val->pos.x;
      mid->pos.y = val->pos.y;
      mid->pos.z = val->pos.z;
      mid->f14   = val->f14;
      mid->f18   = val->f18;
      mid->i1c   = val->i1c;
    }
    vec->end = FUN_00c5bbc0(pos, vec->end, mid + 1);
    if (vec->begin != 0 && ((u32*)vec->begin)[-1] != 0)
      operator_delete_array(vec->begin);
    vec->cap = buf + cap;
    vec->begin = buf;
  }
}

// @ 0x00c5c0f0
void __cdecl FUN_00c5c0f0(ElemVec* vec, cPlanet* planet, s32* count, u32 unused, float* out, s32 n)
{
  (void)unused;
  if (FUN_00fe3b10(planet) != 0)
    return;

  {
    cPlaceList* pl = planet->p13c;
    cPlaceList* city = (cPlaceList*)pl->FUN_00b8de30();
    if (pl == 0)
      return;
    if (pl->FUN_00b8e040(*(u32*)0x016922ac) == 0)
      return;

    {
      cSpaceCombatTuning* tun = GetSpaceCombatTuning();
      Vec3_s00c5_b9c0* cityPos = city->GetCitiesPos();
      s32 level = tun->GetWeaponLevel(*cityPos);
      float dps = tun->GetBackgroundUberTurretDPS();
      float hp  = tun->GetUFOHealth(5, level);
      float total = (float)n;
      MissionElem* it;
      float remain;

      if (n < 0)
        total += 4294967296.0f;
      total = total * 0.001f * dps + *out;
      *out = 0.0f;

      for (it = vec->begin; it != vec->end && it->id != 5; ++it)
        ;
      remain = total;
      while (*count > 0 && hp <= remain && it != vec->end) {
        if (it->id == 5) {
          if (it + 1 < vec->end)
            CopyMissionElementsForward(it + 1, vec->end, it);
          vec->end -= 1;
          *count -= 1;
          remain -= hp;
        }
      }
      *out = remain;
    }
  }
}

// @ 0x00c5c240
void __fastcall FUN_00c5c240(ElemVec* vec, void* dummy)
{
  (void)dummy;
  MissionElem* e = vec->end;

  if (e < vec->cap) {
    vec->end = e + 1;
    if (e != 0) {
      e->vtbl  = 0x0146f688;
      e->id    = -1;
      e->pos.x = g_elemPosX;
      e->pos.y = g_elemPosY;
      e->pos.z = g_elemPosZ;
      {
        float n = g_elemNegOne;
        e->f14 = n;
        e->f18 = n;
      }
      e->i1c   = -1;
    }
    return;
  }

  {
    MissionElem tmp;
    tmp.vtbl  = 0x0146f688;
    tmp.id    = -1;
    tmp.pos.x = g_elemPosX;
    tmp.pos.y = g_elemPosY;
    tmp.pos.z = g_elemPosZ;
    {
      float n = g_elemNegOne;
      tmp.f14 = n;
      tmp.f18 = n;
    }
    tmp.i1c   = -1;
    vec->Insert(e, &tmp);
  }
}

// @ 0x00c5c310
void __cdecl FUN_00c5c310(ElemVec* vec, s32* p2, s32* p3, s32* p4, s32 lo, s32 hi)
{
  if (*p2 != 0 || *p4 != 0) {
    *p3 = 0;

    {
      s32 i;
      s32 idv;
      for (i = 0, idv = i + 4; i < *p2; ++i) {
        vec->PushDefault();
        vec->end[-1].id = idv;
      }
    }

    {
      s32 i;
      for (i = 0; i < *p2; ++i) {
        float fbuf[1];
        fbuf[0] = g_cRandomGlobal.RandomDouble() * (float)(hi - lo) + (float)lo;
        s32 n = SseRoundToInt(fbuf[0]);
        if (n > 5)
          n = 5;
        if (n > 0) {
          s32 k = n;
          do {
            vec->PushDefault();
            MissionElem* e = vec->end - 1;
            e->id  = 2;
            e->i1c = i;
          } while (--k != 0);
        }
        *p3 += n;
      }
    }

    {
      s32 i;
      for (i = 0; i < *p4; ++i) {
        vec->PushDefault();
        vec->end[-1].id = 5;
      }
    }
  }
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
        if (ratio >= g_cRandomGlobal.RandomDouble())
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

// @ 0x00c5c860
namespace SP {
void DoBuildingDamage(cForceList* pForces, cBattle* pBattle, int attackerID, int* pnType4, int* pnType2, int unused, float* pTurretLeft, float* pForceLeft, bool* pbHaveRec, uint32_t dtMs)
{
    if (FUN_00fe3b10(pBattle))
        return;

    cPlanetRecord_s00c5_c860* planet = pBattle->mpPlanet;
    int avatarID = planet->GetOwner()->GetAvatar();
    cCivData_s00c5_c860* civ = (cCivData_s00c5_c860*)planet->GetOwner();
    if (avatarID == attackerID)
        return;

    if (planet == GetPlayerHomePlanet()) {
        int owner = ((cGameDataStub*)FUN_0107bcb0())->GetGameDataOwner();
        if (FUN_00c702f0(planet) < owner)
            return;
    }

    cSPSpaceCombatTuning* tuning = GetSpaceCombatTuning_s00c5_c860();
    cEmpire_s00c5_c860* attacker = StarManager_s00c5_c860()->GetEmpireByID(attackerID);
    cEmpire_s00c5_c860* avatar = StarManager_s00c5_c860()->GetEmpireByID(avatarID);
    int level = tuning->GetWeaponLevel(civ->GetCities());

    float turretDPS = avatar ? avatar->GetBackgroundTurretDPS() : tuning->GetBackgroundTurretDPS(level);
    float bomberDPS, fighterDPS;
    if (attacker) {
        bomberDPS = attacker->GetBackgroundBomberDPS();
        fighterDPS = attacker->GetBackgroundFighterDPS();
    }
    else {
        bomberDPS = tuning->GetBackgroundBomberDPS(level);
        fighterDPS = tuning->GetBackgroundFighterDPS(level);
    }
    float uberDPS = tuning->GetBackgroundUberTurretDPS();
    float turretHealth = avatar ? avatar->GetTurretHealth() : tuning->GetTurretHealth(level);
    float ufoHealth4, ufoHealth2;
    if (attacker) {
        ufoHealth4 = attacker->GetUFOHealth(4);
        ufoHealth2 = attacker->GetUFOHealth(2);
    }
    else {
        ufoHealth4 = tuning->GetUFOHealth(4, level);
        ufoHealth2 = tuning->GetUFOHealth(2, level);
    }

    AutoRefCount<PropertyList> props;
    GetPropertyManager()->GetPropertyList(0xa4c2f6bd, 0, props.AsPPTypeParam());
    float buildingHealth = 10.0f;
    float cityHealth = 10.0f;
    GetFloatProperty(props.mpObject, 0x7d566743, cityHealth);
    GetFloatProperty(props.mpObject, 0x17efa840, buildingHealth);

    int quot = *pnType2;
    int n = 1;
    int hasType4 = 0;
    if (*pnType4 != 0) {
        quot = *pnType2 / *pnType4;
        n = *pnType4;
        hasType4 = 1;
    }
    float dtSec = (float)dtMs * 0.001f;
    float acc = 0.0f;
    float damage = *pTurretLeft / (float)n + dtSec * ((float)quot * fighterDPS + (float)hasType4 * bomberDPS);
    *pTurretLeft = 0.0f;

    bool bPlayerSide = FUN_01029a10(attackerID, planet);

    if (*pbHaveRec && n > 0) {
        int nRec = planet->RecCount();
        if (nRec > 0) {
            BuildingRec* rec = planet->mpRecBegin;
            for (int i = 0; i < nRec; ++i, ++rec) {
                if ((rec->flags & 1) && rec->id != kPlaceUberTurretID) {
                    float h = rec->health - damage;
                    rec->health = h;
                    if (!(0.0f < h)) {
                        planet->RemoveBuildingRec(rec->id);
                        *pbHaveRec = false;
                    }
                    --n;
                    break;
                }
            }
        }
    }

    int iGroup = 0;
    if (planet->GroupCount() > 0) {
        do {
            if (n <= 0)
                goto done_cities;
            cCityGroup* group = planet->GetGroup(iGroup);
            bool emptied = false;
            int groupOwner = group->GetOwnerID();
            int iCity = 0;
            if (group->CityCount() > 0) {
                while (n > 0) {
                    cCity_s00c5_c860* city = group->mpCitiesBegin[iCity];
                    bool destroyed = false;
                    int cityCount = city->GetCount();
                    int nTurrets = city->GetNumTurrets();
                    int nBuildings = city->GetNumBuildings();
                    float health = city->GetHealth();
                    int owner = city->GetOwnerID();
                    if (bPlayerSide && owner == attackerID && !(health < 100.0f)) {
                        ++iCity;
                    }
                    else {
                        acc = (float)nTurrets * turretDPS * dtSec + acc;
                        float rem = damage;
                        while (rem > 0.0f) {
                            if (nTurrets > 0 && rem >= turretHealth) {
                                city->RemoveTurret();
                                rem = rem - turretHealth;
                            }
                            else if (nBuildings > 1 && rem >= buildingHealth) {
                                city->SetCount(cityCount - 1);
                                if (bPlayerSide)
                                    FUN_00be9b20(planet, 0, city, groupOwner, FUN_00bd7fb0(attackerID, 0));
                                rem = rem - buildingHealth;
                            }
                            else if (nBuildings == 1) {
                                if (bPlayerSide) {
                                    FUN_00be9b20(planet, 0, city, groupOwner,
                                                 tuning->GetCityCaptureFactor(attackerID, 0) * rem);
                                    break;
                                }
                                if (rem >= cityHealth) {
                                    uint32_t k = city->mTurretKeyA;
                                    if (k)
                                        planet->mDestroyedKeys.push_back(k);
                                    k = city->mTurretKeyB;
                                    if (k)
                                        planet->mDestroyedKeys.push_back(k);
                                    if (group->CityCount() == 1)
                                        emptied = true;
                                    pBattle->FUN_00c711e0(city);
                                    *pTurretLeft = (rem - cityHealth) + *pTurretLeft;
                                    destroyed = true;
                                    break;
                                }
                                *pTurretLeft = *pTurretLeft + rem;
                                break;
                            }
                            else {
                                *pTurretLeft = *pTurretLeft + rem;
                                break;
                            }
                        }
                        --n;
                        if (!destroyed)
                            ++iCity;
                    }
                    if (!(iCity < group->CityCount()))
                        break;
                }
                if (emptied)
                    continue;
            }
            ++iGroup;
        } while (iGroup < planet->GroupCount());
    }
    if (n > 0)
        *pTurretLeft = (float)n * damage + *pTurretLeft;

done_cities:
    int hasUber = 0;
    if (pBattle->mpPlanet && pBattle->mpPlanet->HasBuildingRec(kPlaceUberTurretID))
        hasUber = 1;
    float total = (float)hasUber * uberDPS * dtSec + acc + *pForceLeft;
    *pForceLeft = 0.0f;

    ForceElem* it = pForces->mpBegin;
    while (it != pForces->mpEnd && it->type != 2)
        ++it;
    if (*pnType2 > 0) {
        while (*pnType2 > 0 && total >= ufoHealth2 && it != pForces->mpEnd) {
            if (it->type == 2) {
                if (it + 1 < pForces->mpEnd)
                    EraseCopy(it + 1, pForces->mpEnd, it);
                --pForces->mpEnd;
                --*pnType2;
                total -= ufoHealth2;
            }
            else
                it = pForces->mpEnd;
        }
    }
    if (!(*pnType2 > 0)) {
        it = pForces->mpBegin;
        if (it != pForces->mpEnd && it->type != 4)
            it = pForces->mpEnd;
        while (*pnType4 > 0 && total >= ufoHealth4 && it != pForces->mpEnd) {
            if (it->type == 4) {
                if (it + 1 < pForces->mpEnd)
                    EraseCopy(it + 1, pForces->mpEnd, it);
                --pForces->mpEnd;
                --*pnType4;
                total -= ufoHealth4;
            }
            else
                it = pForces->mpEnd;
        }
    }
    *pForceLeft = total;
}
}  // namespace SP

// @ 0x00c5d640
namespace SP {
void FUN_00c5d640(void* mission, RecVec* vec, int* outA, int* outB, int* outC)
{
    // clear the output vector: destroy the range then reset end to begin
    FUN_00c5b450(vec->end, vec->end, vec->begin);
    vec->end = (Rec*)((char*)vec->end - ((((char*)vec->end - (char*)vec->begin) >> 5) << 5));

    ObjVec va = {0, 0, 0};   // kind 4
    ObjVec vb = {0, 0, 0};   // kind 2
    ObjVec vc = {0, 0, 0};   // kind 5

    GameDataVec* gd = SP_NounManager()->GetGameDataVector(
        (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420, (void*)&FUN_00ad48b0, (void*)&FUN_00b1e500, &gGameDataTag);
    int n = (int)((char*)gd->end - (char*)gd->begin) >> 2;
    for (int i = 0; i < n; ++i) {
        void* o = gd->begin[i];
        if (((GameObject*)o)->FUN_00c37710() == mission) {
            char b0 = ((GameObject*)o)->FUN_00c372b0();
            char b1 = vcallc(o, 0x2c / 4);
            if (!b0 && !b1 && 0.0f < *(float*)((char*)o + 0x540)) {
                int kind = *(int*)((char*)o + 0x714);
                ObjVec* dst = 0;
                if (kind == 2) dst = &vb;
                else if (kind == 4) dst = &va;
                else if (kind == 5) dst = &vc;
                if (dst) {
                    void* tmp = o;
                    vcall0(o, 0);                       // AddRef
                    dst->PushBack(&tmp);
                    if (tmp) ((ThunkV0)(*(void***)tmp)[1])(tmp);   // Release
                }
            }
        }
    }

    // records for kind-4 objects (they also carry the "index within kind-4" field)
    *outA = (int)((char*)va.end - (char*)va.begin) >> 2;
    for (int i = 0; i < *outA; ++i) {
        void* o = va.begin[i];
        vec->AppendDefault();
        Rec* r = vec->end - 1;
        r->f14 = *(float*)((char*)o + 0x540);
        r->f18 = ((ThunkV0f)(*(void***)((char*)o + 0x508))[0x58 / 4])((char*)o + 0x508);
        r->f04 = *(uint32_t*)((char*)o + 0x714);
        float* q = (float*)((ThunkV0)(*(void***)((char*)o + 0x34))[0x2c / 4])((char*)o + 0x34);
        r->f08 = q[0];
        r->f0c = q[1];
        r->f10 = q[2];
        void* x = ((GameObject*)o)->FUN_00c38b00();
        if (x) {
            void* y = ((void*(__thiscall*)(void*, void*))(*(void***)x)[0xc / 4])(x, (void*)0xb033b403);
            if (y) {
                for (int k = 0; k < *outA; ++k) {
                    if (va.begin[k] == y) { r->f1c = k; break; }
                }
            }
        }
    }

    // records for kind-2 objects
    *outB = (int)((char*)vb.end - (char*)vb.begin) >> 2;
    for (int i = 0; i < *outB; ++i) {
        void* o = vb.begin[i];
        vec->AppendDefault();
        Rec* r = vec->end - 1;
        r->f14 = *(float*)((char*)o + 0x540);
        r->f18 = ((ThunkV0f)(*(void***)((char*)o + 0x508))[0x58 / 4])((char*)o + 0x508);
        r->f04 = *(uint32_t*)((char*)o + 0x714);
        float* q = (float*)((ThunkV0)(*(void***)((char*)o + 0x34))[0x2c / 4])((char*)o + 0x34);
        r->f08 = q[0];
        r->f0c = q[1];
        r->f10 = q[2];
    }

    // records for kind-5 objects
    *outC = (int)((char*)vc.end - (char*)vc.begin) >> 2;
    for (int i = 0; i < *outC; ++i) {
        void* o = vc.begin[i];
        vec->AppendDefault();
        Rec* r = vec->end - 1;
        r->f14 = *(float*)((char*)o + 0x540);
        r->f18 = ((ThunkV0f)(*(void***)((char*)o + 0x508))[0x58 / 4])((char*)o + 0x508);
        r->f04 = *(uint32_t*)((char*)o + 0x714);
        float* q = (float*)((ThunkV0)(*(void***)((char*)o + 0x34))[0x2c / 4])((char*)o + 0x34);
        r->f08 = q[0];
        r->f0c = q[1];
        r->f10 = q[2];
    }

    // release the three scratch vectors (C, B, A order in retail)
    ObjVec* order[3] = { &vc, &vb, &va };
    for (int v = 0; v < 3; ++v) {
        ObjVec* p = order[v];
        for (void** it = p->begin; it != p->end; ++it) {
            void* o = *it;
            if (o) ((ThunkV0)(*(void***)o)[1])(o);
        }
        if (p->begin && ((int*)p->begin)[-1] != 0) ::operator delete(p->begin);
    }
}
}  // namespace SP

// @ 0x00c5da10
namespace SP {
bool FUN_00c5da10(Mission* mission, int* pvec)
{
    if (GetUniverseContext() == 0) {
        void* tp = mission->GetTargetPlanet();
        if (GetActivePlanet() == tp) {
            GameDataVec* gd = SP_NounManager()->GetGameDataVector(
                (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420, (void*)&FUN_00ad48b0, (void*)&FUN_00b1e500, &gGameDataTag);
            int n = (int)((char*)gd->end - (char*)gd->begin) >> 2;
            for (int i = 0; i < n; ++i) {
                void* o = gd->begin[i];
                if (((GameObject*)o)->FUN_00c37710() == mission) {
                    char b0 = ((GameObject*)o)->FUN_00c372b0();
                    char b1 = vcallc(o, 0x2c / 4);
                    if (!b0 && !b1 && 0.0f < *(float*)((char*)o + 0x540)) return true;
                }
            }
            return false;
        }
    }
    return *pvec != pvec[1];
}
}  // namespace SP

// @ 0x00c5dae0
namespace SP {
int RaidPlunderEvent::Update(int dt)
{
    Mission* mi = (Mission*)this;
    int r = mi->Update(dt);
    if (r != 3) return r;

    int gt = *(int*)((char*)GameTimeManager() + 0x48);
    if ((gt & 1) != 0) dt = 0;

    if (F<uint8_t>(0x1fc) == 0) {
        void* p = FUN_00401010();
        char ok = ((char(__thiscall*)(void*, void*, int))(*(void***)p)[0x1c / 4])(
                      p, (char*)this + 0x1f0, 0);
        if (ok != 0) {
            int v14 = 1, v10 = 1;
            void* prop = *(void**)((char*)this + 0x180);
            F<uint8_t>(0x1fc) = 1;
            if (prop != 0) {
                FUN_00410370(prop, 0x339bbc1, &v14);
                FUN_00410370(*(void**)((char*)this + 0x180), 0x339bbc5, &v10);
            }
            FUN_00c5c310((char*)this + 0x214, (char*)this + 0x204, (char*)this + 0x208,
                         (char*)this + 0x200, v14, v10);

            if (GetUniverseContext() == 0) {
                if (GetActivePlanet() == mi->GetTargetPlanet()) {
                    FUN_00c5d140(this, (char*)this + 0x214, -1, (char*)this + 0x1f0, gDefaultVec3, 0, 0);
                }
            }

            void* owner  = mi->GetOwnerEmpire();
            void* player = GetPlayerEmpire();
            if (owner != 0 && (owner == player || ((Empire*)owner)->FUN_00c31bc0(player))) {
                int   recA = *(int*)((char*)mi->GetTargetPlanet() + 0x13c);
                int   recB = *(int*)((char*)mi->GetTargetPlanet() + 0x13c);
                int   owner84 = *(int*)((char*)owner + 0x84);
                bool  eq = (owner == player);
                // the four "input" helpers take no stack arguments; the eight pushed slots the
                // callee pops are (owner84, ctx2, ctx, tree, key, 2, this, eq)
                ((AutoRef*)((char*)this + 0x1e4))->operator=(
                    ((CommMgr*)FUN_00b3d4a0())->FUN_00aeb3e0(
                        (void*)owner84,
                        ((ThrB8*)recB)->FUN_00b8de30(),
                        ((StarRec*)recA)->GetCommContext(),
                        ((void*(__thiscall*)(void*))(*(void***)this)[0xa4 / 4])(this),
                        (void*)0x8b756f4b, (void*)2, this, (void*)eq));
            }
        }
        if (F<uint8_t>(0x1fc) == 0) return 3;
    }

    if (!FUN_00c5da10(mi, (int*)((char*)this + 0x214))) {
        WStr_s00c5_d640 text;
        mi->GetText(0x25594ea8, &text);
        void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
        GetEventLog()->ModifyEventText(ev, text.mpBegin);
        GetEventLog()->EventDoNotAddToHistory(ev, 1);
        return 5;
    }

    {
        float f = gFloat_01473c70;
        if (*(void**)((char*)this + 0x180) != 0)
            FUN_0040cf10(*(void**)((char*)this + 0x180), 0x2b9e524, &f);
        int n = (int)(gFloat_013ec5b4 * f);

        if (!(*(uint32_t*)((char*)this + 0x7c) < (uint32_t)n)) {
            FUN_0102c0c0(mi->GetTargetPlanet());
            BackgroundUpdate(0);
            WStr_s00c5_d640 text;
            mi->GetText(0xb681fba2, &text);
            void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
            GetEventLog()->ModifyEventText(ev, text.mpBegin);
            GetEventLog()->EventDoNotAddToHistory(ev, 1);
            return 6;
        }
    }

    {
        void* tp = mi->GetTargetPlanet();
        if (FUN_00fe3b10(tp) == 0) {
            float tuning = ((Tuning*)GetSpaceCombatTuning_s00c5_d640())->FUN_0102a590();
            float acc = (float)(uint32_t)dt * gFloat_013f9428;
            acc = acc * *(int*)((char*)this + 0x200);
            acc = acc * tuning;
            acc = acc + *(float*)((char*)this + 0x210);
            *(float*)((char*)this + 0x210) = acc;
            uint32_t rounded = (uint32_t)acc;
            if (rounded != 0) {
                *(float*)((char*)this + 0x210) = acc - (float)rounded;
                ((Planet*)mi->GetTargetPlanet())->FUN_00c70fd0((int)rounded);
            }
        }
    }
    FUN_00c5c0f0((char*)this + 0x214, mi->GetTargetPlanet(), (char*)this + 0x200,
                 *(void**)((char*)this + 0x180), (char*)this + 0x20c, dt);
    return 3;
}
}  // namespace SP

// @ 0x00c5df50
namespace SP {
bool RaidHandler::HandleMessage_F50(uint32_t msg, void* m)
{
    if (msg == 0x2489760) {
        if (*(int*)((char*)m + 8) == (int)Mis()->GetTargetPlanet()) {
            FUN_00c5d640(Mis(), (RecVec*)&F<void*>(0x1e0), (int*)&F<void*>(0x1d0),
                         (int*)&F<void*>(0x1d4), (int*)&F<void*>(0x1cc));
        }
    } else if (msg == 0x248975f) {
        if (*(int*)((char*)m + 0x10) == (int)Mis()->GetTargetPlanet()) {
            FUN_00c5d140(Mis(), &F<void*>(0x1e0), -1, &F<void*>(0x1bc), gDefaultVec3, 0, 0);
        }
    }
    return BaseHandleMessage(msg, m) != 0;
}
}  // namespace SP

// @ 0x00c5e020
namespace SP {
bool RaidHandler::HandleMessage_020(uint32_t msg, void* m)
{
    if (msg == 0x2489760) {
        if (*(int*)((char*)m + 8) == (int)Mis()->GetTargetPlanet()) {
            if (F<uint8_t>(0x200) == 0) {
                int local = 0;
                FUN_00c5d640(Mis(), (RecVec*)&F<void*>(0x204), (int*)&F<void*>(0x1c4),
                             (int*)&F<void*>(0x1c8), &local);
            } else {
                Mis()->FUN_00c485e0();
            }
        }
    } else if (msg == 0x248975f) {
        if (*(int*)((char*)m + 0x10) == (int)Mis()->GetTargetPlanet()) {
            FUN_00c5d140(Mis(), &F<void*>(0x204), F<int>(0x1fc), &F<void*>(0x1cc),
                         gDefaultVec3, 0, (int)F<uint8_t>(0x1e8));
        }
    }

    if (BaseHandleMessage(msg, m) != 0) return false;
    if (F<uint32_t>(0x44) != 0xd646c543) return false;
    if (Mis()->GetTargetPlanet() != GetActivePlanet()) return false;
    if (GetUniverseContext() != 0) return false;
    if (msg != 0x1622184) return false;

    void* c = *(void**)((char*)m + 8);
    int   x = *(int*)((char*)m + 0x10);
    void* inv = ((UFOSim*)GetUFOSimulator())->GetPlayerInventory();
    if (inv) inv = (char*)inv + 0x508; else inv = 0;
    if (x == (int)inv) {
        if (((Combatant*)c)->GetDamageState() == 2) {
            bool b = FUN_00c5b430(c) != 0;
            void* r = FUN_00ae3370(c);
            if (((r != 0) && (*(int*)((char*)r + 0x714) == 6)) || b) {
                if (++F<int>(0x1e4) == 3) {
                    WStr_s00c5_d640 text;
                    Mis()->GetText(0xdb458701, &text);
                    void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
                    GetEventLog()->ModifyEventText(ev, text.mpBegin);
                    GetEventLog()->EventDoNotAddToHistory(ev, 1);
                    text.DeallocateSelf();
                }
            }
        }
    }
    return true;
}
}  // namespace SP
