// src/game/SPGonzago/SPSimulatorUniverse.cpp -- migrated from slice(s) s01012730, s010146c0, s010137b0, s010104c0, s0100e150, s0100d0d0, s00b8d190 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSimulatorUniverse.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cSPTimer.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cVarListSerializer.h"
#include <algorithm>
#include <intrin.h>
#include <math.h>
#include <new>
#include "EA/Variant.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cGameNounManager.h"
#include "SP/cPropertyList.h"
#include "SP/cRelationshipManager.h"
#include "SP/cGameData.h"

// ---- items of slice s00b8d190 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
    void* __stdcall StarManager(uint32_t id);             // 0x00b3d2a0
}
struct cStarObject {
    int32_t  FUN_00bb99e0();                              // 0x00bb99e0
    uint32_t FUN_00ba6440();                              // 0x00ba6440
    void     FUN_00ba6660();                              // 0x00ba6660
    uint32_t FUN_00ba6d80();                              // 0x00ba6d80
    void*    FUN_00bb9b80();                              // 0x00bb9b80
};
struct cBioElemSort {                                     // sort predicate object
    uint8_t  mPad00[0x184];                               // +0x000
    uint32_t mField184;                                   // +0x184
    uint32_t SortBanners();                               // 0x00b8de30
};
// ---- items of slice s00b8d190 end

// ---- items of slice s0100d0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kfMillisecondsPerUnit;   // 0x013f9428
extern const float kfHalfLog;               // 0x013fdf1c
extern const float kfHalfLogPerUnit;        // 0x01495720
extern const float kfThousand;              // 0x013ec5b4
extern const uint32_t kPlaceBioProtector;   // 0x016dca94
extern const char kSimulatorUniverseName[]; // 0x015b6b38
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct cStreamObj {
    PV4 PV2
    virtual cStreamObj* GetStream();        // +0x18
};
struct cOutStream {
    PV8
    virtual cStreamObj* GetStreamObj();     // +0x20
};
class cSPTimer {
public:
    uint64_t GetElapsedTime();              // 0x00bc3190
};
class cGonzagoTimer {
public:
    uint8_t pad00[8];
    void Destroy();                         // 0x00b638b0
};
struct cSpaceEvent {
    void* mv00;                 // +0x00
    void* mv04;                 // +0x04
    void* mv08;                 // +0x08
    uint32_t mu0C;              // +0x0c
    uint32_t mu10;              // +0x10
    float mf14;                 // +0x14
    uint32_t mu18;              // +0x18
};
struct cSimObject {
    void Update();              // 0x00e0e1a0
};
struct cEditorHelper {
    cSimObject* GetSimObject(); // 0x01067e60
};
struct cSpaceUpdater {
    PV4
    virtual void Update(uint32_t arg0, uint32_t arg1);   // +0x10
};
struct cSPSimulatorSpaceGame {
    uint8_t pad00[0x14];
    cEditorHelper* mp14;        // +0x14 (editor-side helper object)
    uint8_t pad18[0x3c];
    cSpaceUpdater* mp54;        // +0x54 (optional per-system updater)
    uint8_t pad58[0x70];
    cSpaceEvent* mpEventsC8;    // +0xc8 (event vector begin)
    cSpaceEvent* mpEventsCC;    // +0xcc (event vector end)
    uint8_t padD0[0xc8];
    cSPTimer mTimer;            // +0x198

    void GalaxyUpdate(uint32_t elapsedMS);      // 0x0100d0d0
    void GameUpdate(uint32_t arg);              // 0x0100d230
    void OnTick(uint32_t arg0, uint32_t arg1);  // 0x0100d2a0
    float GetTimerSeconds();                    // 0x0100d410
    void AdvanceTimer(float seconds);           // 0x01008e60
    void OnPreTick();                           // 0x01006370
    static int GetUniverseContext();            // 0x01021080
    bool IsZoomedOut();                         // 0x00b18e40
    void SolarSystemUpdate(uint32_t arg);       // 0x01009df0
    void UpdateUFOStatusEffects();              // 0x0100a080
    void GalaxyUpdateNPC_UFOs(uint32_t elapsedMS);  // 0x0100b430
    void GalaxyTestForIntercept();              // 0x01008910
    void UpdateEmpireHud(uint32_t arg0, uint32_t arg1);  // 0x0100a160
};
struct cVarList;
class cVarListSerializer {
public:
    cVarListSerializer(cVarList* pList, const char* pName, uint32_t id);   // 0x00692f90
    bool Serialize(cOutStream* pOut);                                      // 0x00692900
    bool SerializeRead(cOutStream* pOut);                                  // 0x00693e10
    uint8_t mBuffer[0xa00];     // inline stream buffer (object size pinned by the frame)
};
struct cSimulatorUniverse_s0100_d0d0 {
    uint8_t pad00[0x40];
    uint64_t mFirstEvent;       // +0x40
    uint64_t mSecondEvent;      // +0x58
    uint64_t mThirdEvent;       // +0x70
    uint64_t mFourthEvent;      // +0x88
    uint64_t mFifthEvent;       // +0xa0
    uint32_t mRaidFrequency;    // +0xb0
    uint32_t padB4[6];
    uint32_t mEventCount;       // +0xcc
    uint32_t padD0[2];
    float mfD8;                 // +0xd8
    uint32_t padDC[2];
    float mfE4;                 // +0xe4

    void Write(cOutStream* pOut);   // 0x0100d560
    void Read(cOutStream* pOut);    // 0x0100d790
};
struct WarAttackEvent {
    uint8_t pad00[8];
    uint64_t mTimeSinceLastRaid;    // +0x08
    float GetEventFrequency(float deltaSeconds, uint32_t deltaHi);   // 0x0100dfb0
};
struct cGrobShockSelection {
    uint8_t pad000[0x110];
    uint32_t mu110;             // +0x110
    uint32_t mu114;             // +0x114
    void Reset();                       // 0x0100d9f0
    bool Get(uint32_t* pOut);           // 0x0100da10
};
struct cCivData {
    float* GetCities();                 // 0x005c65e0
    void* GetAvatar();                  // 0x00b1fdb0
};
struct cGameNoun {
    cCivData* GetCivData();             // 0x00b8de30
    bool HasPlace(uint32_t place);      // 0x00b8e040
};
struct cPlayerEmpire_s0100_d0d0 {
    uint8_t pad00[0x5c];
    void* mp5c;                 // +0x5c
    void* mp60;                 // +0x60
};
struct cSimProperty {
    uint8_t pad00[0x12];
    uint16_t mw12;                      // +0x12
    float* GetFloat();                  // 0x0041ea70
};
struct cPropertyStore {
    PV8 PV
    virtual bool Find(uint32_t id, cSimProperty** ppOut);   // +0x24
};
struct cSimUniverseStore {
    uint8_t pad00[0x10];
    cPropertyStore* mp10;               // +0x10
};
struct cTerrainSphere_s0100_d0d0 {
    float GetValue(uint32_t id);        // 0x00c75c30
    void UpdateA();                     // 0x00c7ada0
    void UpdateB(uint32_t elapsedMS);   // 0x00c774b0
};
struct cNounManager {
    cTerrainSphere_s0100_d0d0* GetCurrentTerrainSphere();  // 0x00f67d90
};
struct cCivEntryList {
    uint8_t pad00[0x2c];
    cCivData** mp2c;            // +0x2c (begin)
    cCivData** mp30;            // +0x30 (end)
};
struct cSpaceGame_s0100_d0d0 {
    uint8_t pad00[0x30];
    cCivEntryList* mp30;        // +0x30
};
cSpaceGame_s0100_d0d0* __cdecl SpaceGameGet_s0100_d0d0();                 // 0x01002bd0
void* __cdecl GetPlayerHomePlanet();                // 0x01021370
int   __cdecl GetCivValue(cCivData* pCiv);          // 0x00c702f0
void* __cdecl FUN_01021300_s0100_d0d0();                       // 0x01021300
cNounManager* __cdecl NounManager_s0100_d0d0();                // 0x00b3d300
bool  __cdecl EA_IO_WriteUint32(cStreamObj* pStream, const uint32_t* value, int count, int flags); // 0x0093aa70
bool  __cdecl EA_IO_WriteUint64(cStreamObj* pStream, const uint64_t* value, int count, int flags); // 0x0093ab10
bool  __cdecl EA_IO_ReadUint32(cStreamObj* pStream, uint32_t* value, int count, int flags);        // 0x0093a780
bool  __cdecl EA_IO_ReadBlock(cStreamObj* pStream, void* value, int count, int flags);             // 0x0093a800
extern cSimUniverseStore* gpSimUniverse;    // 0x016dc798
struct BioProtectorSort {
    float mPos[3];              // +0x00
    bool operator()(cGameNoun* a, cGameNoun* b);        // 0x0100db40
    bool CompareAndCheck(cGameNoun* a, cGameNoun* b);   // 0x0100dc20
};
// ---- items of slice s0100d0d0 end

// ---- items of slice s0100e150 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Property {
    char mPad[0x12];
    uint16_t mType;                                           // +0x12
    int* GetInt();                                            // 0x0041e990
    float* GetFloat();                                        // 0x0041ea70
};
struct cPropertyList {
    virtual void vf0();
    virtual int Release();                                    // +0x04
virtual void vf2();
virtual void vf3();
virtual void vf4();
virtual void vf5();
virtual void vf6();
virtual void vf7();
virtual void vf8();
    virtual bool GetProperty(uint32_t id, Property** out);    // +0x24
};
struct PropListPtr {
    cPropertyList* mpObject;
};
struct RandomLinearCongruential {
    unsigned RandomUint32Uniform(unsigned n);                 // 0x00a68fb0
    double RandomDoubleUniform();                             // 0x009360d0
};
extern RandomLinearCongruential g_random;                     // 0x01601760
void* SpaceGameGet();                                         // 0x01002bd0
int __stdcall GetPlayerHomePlanet(int arg);                   // 0x01021370
struct cGameNounManager {
    void* GetAvatar();                                        // 0x00b1fdb0
    float* GetCities();                                       // 0x005c65e0
};
struct cGameNounOwner {
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
    cGameNounManager* GetNounManager();                       // 0x00b8de30
};
struct cStarRecordRef {
    int GetCommContext();                                     // 0x00ce6950
};
struct cStarManager {
    void* GetEmpireByID();                                    // 0x00ba9370
    void* GetRelationshipCore();                              // 0x00885c90
};
struct cRelationshipManager {
    bool IsAtWar(void* core);                                 // 0x00d01b50
};
void* RelationshipManager(void* core);                        // 0x00b3d2c0
struct cPlayerEmpire {
    char mPad70[0x70];
    int mHostileCount;                                        // +0x70
    int mHostileEnd;                                          // +0x74
    char mPad78[0x84 - 0x78];
    int mEmpireId;                                            // +0x84
};
cPlayerEmpire* FUN_01021300();                                // 0x01021300
float RaidFrequencyFromTime(float seconds, int thresholdMSec);   // 0x0100d500
void GetPropertyInt(cPropertyList* list, uint32_t id, int* out);   // 0x0040cf10
struct cSPMission {
    void Init(int);                                           // 0x00c5b370
    void SetTarget(int);                                      // 0x00c47180
    void SetEmpire(int);                                      // 0x00c5b390
    void Accept();                                            // 0x00c485b0
};
struct IMission;
struct cSPMissionManager {
    IMission* CreateMissionFromID(unsigned id, int source, void* empire, int flag);   // 0x00fec590
};
void* GetMissionManager();                                    // 0x00feb9f0
cStarManager* __stdcall StarManager(void* avatar);            // 0x00b3d2a0
struct SimUniverseBase {
    virtual void vf0();
    virtual void vf1();
};
struct SimUniverseSecond {
    virtual void vf0();
    virtual void vf1();
};
struct cSimulatorUniverse : SimUniverseBase, SimUniverseSecond {
    char mPad08[8];                                           // +0x08
    PropListPtr mTuning;                                      // +0x10
    int m14;                                                  // +0x14
    char mPad18[0x110 - 0x18];                                // +0x18
    void* mProperty;                                          // +0x110
    uint32_t mPropertyId;                                     // +0x114
    char mPad118[0x128 - 0x118];                              // +0x118
    char* mp128;                                              // +0x128
    char* mp12c;                                              // +0x12c

    void SetPropertyRef(void* def);                           // 0x0100e6e0
    bool FindEmbassyEntry(cStarRecordRef* pRef, char* pUniverse);   // 0x0100e730
    bool RemoveRaid(int param1, int pNoun, int pEmpire);      // 0x0100e780
};
extern cSimulatorUniverse* gSimUniverse;                      // 0x016dc798
struct GrobWarAttackEvent {
    virtual void f();
    int a;                                                    // +0x04
    float mFreqGrobExtremelyAware;                            // +0x08
    float mFreqGrobVeryAware;                                 // +0x0c
    float mFreqGrobAware;                                     // +0x10
    int mMinTimeBetweenAttacksMSec;                           // +0x14
    bool Init();                                              // 0x0100e150
};
struct GrobTeaseRaidEvent {
    virtual void f();
    unsigned __int64 mTimeSinceLastRaidMSec;                  // +0x08
    float GetEventFrequency(unsigned __int64 deltaMs);        // 0x0100e270
};
struct ArtifactEvent {
    virtual void f();
    unsigned mTimeSinceLastArtifactMSec;                      // +0x04
    float GetEventFrequency(unsigned __int64 deltaMs);        // 0x0100e550
};
struct PirateRaidEvent {
    virtual void f();
    unsigned __int64 mTimeSinceLastRaidMSec;                  // +0x08
    float GetEventFrequency(unsigned __int64 deltaMs);        // 0x0100f1e0
};
struct cTerrainSphere {
    float GetRadius();                                        // 0x00c75c30
};
struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere();                // 0x00f67d90
};
cTerrainEditor* NounManager(unsigned id);                     // 0x00b3d300
struct SpaceGame {
    char mPadC4[0xc4];
    uint32_t mFlags;                                          // +0xc4
    float GetRaidSpeedFactor(int mode);                       // 0x01005c60
};
struct IntVector {
    int* mpBegin;                                             // +0x00
    int* mpEnd;                                               // +0x04
};
struct IMission {
    virtual void vf0();
    virtual int Create(int a, int b);                         // +0x04
    virtual void vf2();                                       // +0x08
    virtual cSPMission* GetSPMission(unsigned id);            // +0x0c
};
struct SpaceGameData {
    char mPad[0x18];
    IntVector mList;                                          // +0x18
};
struct PirateRaidAllyEvent {
    virtual void f();
    char mPad04[4];
    int mTimeLo;                                              // +0x08
    int mTimeHi;                                              // +0x0c
    int TryCreateMission(IMission* pMission, int param);      // 0x0100e3c0
};
struct IPlanetMission {
    virtual void vf0();
    virtual int Create(int planet);                           // +0x04
};
struct BiosphereCollapseEvent {
    virtual void f();
    float mTimeSinceLastEvent;                                // +0x04
    int TryCreateMission(IPlanetMission* pMission, int param);   // 0x0100e690
};
struct GenericDisaster {
    float GetEventFrequency(unsigned __int64 deltaMs);        // 0x0100e430
};
struct NounCompare {
    bool Less(cGameNounOwner* pA, cGameNounOwner* pB);          // 0x0100dc20
};
// ---- items of slice s0100e150 end

// ---- items of slice s010104c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPTimer_s0101_04c0 {
    void*  mVtbl;        // +0x00
    int    mRefCount;    // +0x04
    int    mElapsedLo;   // +0x08
    int    mElapsedHi;   // +0x0c
    int    mBaseLo;      // +0x10
    int    mBaseHi;      // +0x14
    char   mRunning;     // +0x18
    char   mPad19[3];
    int    mGetMs;       // +0x1c

    cSPTimer_s0101_04c0& operator=(const cSPTimer_s0101_04c0& o)
    {
        mElapsedLo = o.mElapsedLo;
        mElapsedHi = o.mElapsedHi;
        mBaseLo    = o.mBaseLo;
        mBaseHi    = o.mBaseHi;
        mRunning   = o.mRunning;
        mGetMs     = o.mGetMs;
        return *this;
    }
};
struct tGrobShockData {
    int       mField00;  // +0x00
    int       mField04;  // +0x04
    cSPTimer_s0101_04c0  mTimer;    // +0x08

    tGrobShockData* FUN_01010870(const tGrobShockData& o);   // 0x01010870
};
void __stdcall Start(int a);        // 0x0100f7c0  SP::CreateArtifact::Start
// ---- items of slice s010104c0 end

// ---- items of slice s010137b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int       u32;
typedef int                s32;
typedef unsigned char      u8;
typedef unsigned __int64   u64;
struct Vec3 { float x, y, z; };
void* __cdecl EAAlloc(u32 size, const char* area, s32 a, s32 b,
                      const char* file, s32 line);     // operator_new overload
void  __cdecl EAFree(void* p);                         // operator_delete
struct U32Vec {                          // eastl::vector<unsigned int>
  u32* mpBegin;                          // 0x00
  u32* mpEnd;                            // 0x04
  u32* mpCap;                            // 0x08
};
struct StarVec {                         // SPVector<unsigned int> (with alloc)
  u32*  mpBegin;                         // 0x00
  u32*  mpEnd;                           // 0x04
  u32*  mpCap;                           // 0x08
  void* mpAlloc;                         // 0x0c
};
struct cStarRefVec {                     // vector<EA::AutoRefCount<cStarRecord>>
  void* mpBegin;                         // 0x00
  void* mpEnd;                           // 0x04
  void* mpCap;                           // 0x08
  void* FUN_01011cc0(StarVec* stars);    // 0x01011cc0
};
struct cTerrainSphere_s0101_37b0 {
  float GetTerrainRadius();              // 0x00c75c30
  u8    FUN_00c77410();                  // 0x00c77410
};
struct cTerrainEditor_s0101_37b0 {
  cTerrainSphere_s0101_37b0* GetCurrentTerrainSphere(u32 key);  // 0x00f67d90
};
struct cEmpire {
  u8  mPad_00[0x50];                     // 0x00
  u32 mFlags_50;                         // 0x50
  u8  mPad_54[0x30];                     // 0x54
  u32 mId_84;                            // 0x84
  u32 GetHomePlanet();                   // SP::cEmpire::GetHomePlanet
  s32 HasDemandForTributeExpired();      // SP::cEmpire::HasDemandForTributeExpired
  s32 FUN_00c31bf0(u32 empire);          // 0x00c31bf0
  void FUN_00c30bb0();                   // 0x00c30bb0
  s32 FUN_00c30b30();                    // 0x00c30b30
  s32 FUN_00c32610();                    // 0x00c32610
};
struct cStarManager_s0101_37b0 {
  s32      FUN_00885c90();               // 0x00885c90
  void*    FUN_00ba6430();               // 0x00ba6430 (the star map)
  cEmpire* GetEmpireByID(u32 id);        // 0x00ba9370
};
struct cStarTable {
  u8      mPad_00[0x18];                 // 0x00
  StarVec mStars_18;                     // 0x18
  u8      mPad_28[4];                    // 0x28
  StarVec mStars2_2c;                    // 0x2c
};
struct MapNode {
  MapNode* mpLeft;                       // 0x00
  MapNode* mpRight;                      // 0x04
  MapNode* mpParent;                     // 0x08
  u32      mColor;                       // 0x0c
  u32      mKey;                         // 0x10
  cEmpire* mpEmpire;                     // 0x14
  u64      mStamp;                       // 0x18
};
struct EmpireMap {                       // eastl::map<u32, pair<cEmpire*,u64>>
  u8       mPad_00[4];                   // 0x00
  MapNode  mAnchor_04;                   // 0x04
  MapNode* Begin() { return mAnchor_04.mpRight; }
  MapNode* End()   { return &mAnchor_04; }
  MapNode* Root()  { return mAnchor_04.mpParent; }
  u64*     Index(u32 key);               // 0x01012c20
};
struct FloatMap {                        // eastl::map<u32, float>
  u8       mPad_00[4];                   // 0x00
  MapNode  mAnchor_04;                   // 0x04
  MapNode* Begin() { return mAnchor_04.mpRight; }
  MapNode* End()   { return &mAnchor_04; }
  MapNode* Find(const float* key);       // 0x00e5c780
  float*   Index(const float* key);      // 0x00c8c550
};
struct cGonzagoTimer_s0101_37b0 {
  void* mpTable_00;                      // 0x00 (not copied)
  u32   mPad_04;                         // 0x04 (not copied)
  u32   mA_08;                           // 0x08
  u32   mB_0c;                           // 0x0c
  u32   mC_10;                           // 0x10
  u32   mD_14;                           // 0x14
  u8    mFlag_18;                        // 0x18
  u32   mE_1c;                           // 0x1c
  cGonzagoTimer_s0101_37b0();                       // 0x00b63890
  ~cGonzagoTimer_s0101_37b0();                      // 0x00b638b0
  void Restart();                                   // 0x00bc3130
};
struct tGrobShockData_s0101_37b0 {
  u32           mId_00;                  // 0x00
  u32           mField_04;               // 0x04
  cGonzagoTimer_s0101_37b0 mTimer_08;               // 0x08
  tGrobShockData_s0101_37b0() : mId_00(0), mField_04(0) {}
  tGrobShockData_s0101_37b0(const tGrobShockData_s0101_37b0&); // 0x01010870
};
typedef bool (__cdecl* ShockCompare)(const tGrobShockData_s0101_37b0&, const tGrobShockData_s0101_37b0&);
struct ShockVec {                        // eastl::vector<tGrobShockData>
  tGrobShockData_s0101_37b0* mpBegin;               // 0x00
  tGrobShockData_s0101_37b0* mpEnd;                 // 0x04
  tGrobShockData_s0101_37b0* mpCap;                 // 0x08
  tGrobShockData_s0101_37b0* erase(tGrobShockData_s0101_37b0* first, tGrobShockData_s0101_37b0* last);
  void  DoInsertValue(tGrobShockData_s0101_37b0* pos, const tGrobShockData_s0101_37b0& value);
};
struct cShockObj {                       // the objects held by the shock records
  virtual u32  v00();                    // 0x00
  virtual s32  v04(u32 id, U32Vec* out);// 0x04
  virtual u32  v08();                    // 0x08
  virtual u32  v0c();                    // 0x0c
};
struct cMissionIface {                   // the mission face passed to the raids
  virtual u32 v00();                     // 0x00
  virtual u32 v04(u32 id, u32 param);    // 0x04
};
struct cSPMission_s0101_37b0 {
  virtual void  v00();                   // 0x00
  virtual void  v04();                   // 0x04
  virtual void* v08(u32);                // 0x08
  virtual void* v0c(u32);                // 0x0c
  u8     mPad_04[0x130];                 // 0x04
  U32Vec mVec_134;                       // 0x134
  u8     mPad_140[0xc0];                 // 0x140
  u32    mMissionID_200;                 // 0x200
  u32    mElapsedTimeMS_204;             // 0x204
  void   Accept();                       // 0x00c485b0
};
struct cSPRaidEvent : cSPMission_s0101_37b0 {
  s32 GenerateBomberCount();             // 0x00c5b530
  s32 GeneratePirateCount();             // 0x00c5b510
};
struct cSPMissionManager_s0101_37b0 {
  cSPMission_s0101_37b0* CreateMissionFromID(u32 id, void* mission, cEmpire* empire,
                                  u32 flags);            // 0x00fec590
};
struct cSpaceGame {
  u8          mPad_00[0x30];             // 0x00
  cStarTable* mpStars_30;                // 0x30
};
struct cSpaceTokenTranslator {
  u8    mPad_00[0xc];                    // 0x00
  void* mpMission_0c;                    // 0x0c
};
struct cGameData {
  u32 GetGameDataOwner();                // Simulator::cGameData::GetGameDataOwner
};
struct cGameNounManager_s0101_37b0 {
  void* GetAvatar();                     // 0x00b1fdb0
  Vec3* GetCities();                     // 0x005c65e0
};
struct cNounBase {                       // `anonymous_namespace'::BioProtectorSort
  cGameNounManager_s0101_37b0* BioProtectorSort();  // 0x00b8de30 (this = the noun)
};
struct cSPUIEventLog {
  u32 PostFeedbackEvent(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);
};
struct RandomLinearCongruential_s0101_37b0 {
  u32 RandomUint32Uniform(u32 range);    // 0x00a68fb0
};
struct cSimulatorUniverse_s0101_37b0 {
  u8        mPad_00[4];                  // 0x00
  u32       mField_04;                   // 0x04
  u8        mPad_08[0x10];               // 0x08
  EmpireMap mEmpireMap_18;               // 0x18
  u8        mPad_3c[0xbc];               // 0x3c
  u32*      mpShockBegin_f8;             // 0xf8
  u32*      mpShockEnd_fc;               // 0xfc
  u8        mPad_100[0x3c];              // 0x100
  float     mClampLo_13c;                // 0x13c
  float     mClampHi_140;                // 0x140
  u8        mPad_144[8];                 // 0x144
  float     mClampCap_14c;               // 0x14c
  u8        mPad_150[4];                 // 0x150
  float     mPlayerRate_154;             // 0x154
  u32       mAwareness_158;              // 0x158
  u8        mPad_15c[4];                 // 0x15c
  float     mClampLoB_160;               // 0x160
  float     mClampHiB_164;               // 0x164
  u8        mPad_168[8];                 // 0x168
  float     mClampCapB_170;              // 0x170
  u8        mPad_174[4];                 // 0x174
  float     mOtherRate_178;              // 0x178
  FloatMap  mFloatMap_17c;               // 0x17c

  void UpdateEmpires(u64 elapsed);                        // 0x010137b0
  s32  FUN_010107b0(float key);                           // 0x010107b0
  void FUN_01013a70(float key, float scale);              // 0x01013a70
  void UpdateAwareness(u32 elapsedLo, u32 elapsedHi);     // 0x01013ba0
  u32  FUN_01013d20(u32 id);                              // 0x01013d20
  u32  FUN_01014220(cMissionIface* iface, u32 param);     // 0x01014220
  void UpdateEmpireAlliancesAndWars(cEmpire* empire, float dt);  // 0x010134d0 (cSimulatorUniverse::UpdateEmpireAlliancesAndWars)
};
struct GrobTeaseRaidEvent_s0101_37b0 {
  u8   mPad_00[8];                       // 0x00
  s32  mTimerLo_08;                      // 0x08
  s32  mTimerHi_0c;                      // 0x0c
  u32  TryCreateMission(cMissionIface* iface, u32 param); // 0x010143d0
};
u64   __cdecl GameTimeGet();                           // 0x00b316c0
void* __cdecl RelationshipManager();                   // 0x00b3d2c0
u32   __cdecl GetPlayerEmpireID();                     // 0x01021090
cEmpire* __cdecl GetPlayerEmpire();                    // SP::cSPLivingUniverse
cStarManager_s0101_37b0* __cdecl StarManager();                   // 0x00b3d2a0
cTerrainEditor_s0101_37b0* __cdecl NounManager();                 // 0x00b3d300
void* __cdecl EventLog(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f); // 0x00b3d3e0
MapNode* __cdecl RBTreeIncrement(MapNode* node);       // 0x00921580
void  __cdecl FUN_010129c0(U32Vec* out);               // 0x010129c0
bool  __cdecl FUN_00d01b50(u32 empire, u32 player);    // 0x00d01b50
s32   __cdecl FUN_0100e970(U32Vec* list);              // 0x0100e970
bool  __cdecl FUN_0100fb00(u32 id);                    // 0x0100fb00
void  __cdecl FUN_0100d960();                          // the shock comparator
void* __cdecl FUN_0107bcb0();                          // 0x0107bcb0
u32   __cdecl FUN_00c702f0(u32 planet);                // 0x00c702f0
void  __cdecl FUN_01024df0(u32* first, u32* last, void* cmp);   // 0x01024df0
void  __cdecl FUN_00829110(U32Vec* out, u32* a, u32* b, u32* c, void* d);
void  __cdecl FUN_00b93c60(U32Vec* self, s32 count, void* alloc); // 0x00b93c60
void  __cdecl FUN_00ae6970(void* vec);                 // 0x00ae6970
void  __cdecl FUN_010144c0(void* self, cStarRefVec* refs);       // 0x010144c0
void  __cdecl FUN_01012d70(void* a, void* b, Vec3 pos);          // 0x01012d70
void  __cdecl FUN_00c47180(void* ev);                            // 0x00c47180
void  __cdecl FUN_00aea5d0(void* end, void* value);              // 0x00aea5d0
void  __cdecl FUN_004558a0(U32Vec* self, u32* pos, u32* value);  // SPVector insert
static MapNode* LowerBoundKey(MapNode* node, MapNode* end, u32 key)
{
  MapNode* best = end;
  while (node != 0) {
    if (node->mKey < key) {
      node = node->mpLeft;
    } else {
      best = node;
      node = node->mpRight;
    }
  }
  return best;
}
tGrobShockData_s0101_37b0* __cdecl ShockCopy(tGrobShockData_s0101_37b0* first, tGrobShockData_s0101_37b0* last,
                                  tGrobShockData_s0101_37b0* result);   // 0x01010bb0
void  __cdecl ConstructCopy(tGrobShockData_s0101_37b0* dst, const tGrobShockData_s0101_37b0& src); // 0x01010870
void* __cdecl MoveElements(tGrobShockData_s0101_37b0* first, tGrobShockData_s0101_37b0* last,
                           tGrobShockData_s0101_37b0* dst);  // 0x01010b30 / 0x01010e30
void  __cdecl DestroyRange(tGrobShockData_s0101_37b0* first, tGrobShockData_s0101_37b0* last); // 0x0100daa0
static void CopyShockFields(tGrobShockData_s0101_37b0* dst, const tGrobShockData_s0101_37b0* src)
{
  dst->mId_00 = src->mId_00;
  dst->mField_04 = src->mField_04;
  dst->mTimer_08.mA_08 = src->mTimer_08.mA_08;
  dst->mTimer_08.mB_0c = src->mTimer_08.mB_0c;
  dst->mTimer_08.mC_10 = src->mTimer_08.mC_10;
  dst->mTimer_08.mD_14 = src->mTimer_08.mD_14;
  dst->mTimer_08.mFlag_18 = src->mTimer_08.mFlag_18;
  dst->mTimer_08.mE_1c = src->mTimer_08.mE_1c;
}
void __cdecl ShockPartialSort(tGrobShockData_s0101_37b0* first, tGrobShockData_s0101_37b0* last,
                              tGrobShockData_s0101_37b0* dst, ShockCompare cmp);
tGrobShockData_s0101_37b0* __cdecl ShockPartition(tGrobShockData_s0101_37b0* begin, tGrobShockData_s0101_37b0* end,
                                       const tGrobShockData_s0101_37b0* pivot,
                                       ShockCompare cmp);
// ---- items of slice s010137b0 end

// ---- items of slice s010146c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
class cGonzagoTimer_s0101_46c0 {
public:
    ~cGonzagoTimer_s0101_46c0();                                    // 0x00b638b0
};
class cSPTimer_s0101_46c0 : public cGonzagoTimer_s0101_46c0 {
public:
    ~cSPTimer_s0101_46c0();
    uint64_t GetElapsedTime();                           // 0x00bc3190
};
namespace eastl {
void __cdecl copy_impl_grob_shock(void* pFirst, void* pLast, void* pDest); // 0x1010bb0
}
namespace SP {
struct tGrobShockData_s0101_46c0 {
    uint32_t  mField0;                                   // +0x00
    uint32_t  mField4;                                   // +0x04
    cSPTimer_s0101_46c0  mTimer;                                    // +0x08
    uint8_t   mPayload[0x1f];                            // +0x09 .. +0x27
};
}
namespace SP {
struct tActionAllocator {
    void* mpPool;                                        // +0x00
    void* mpOwner;                                       // +0x04
};
}
namespace SP {
struct tUniverseActionVector {
    void*             mpBegin;                           // +0x00
    void*             mpEnd;                             // +0x04
    void*             mpCapacity;                        // +0x08
    tActionAllocator  mAllocator;                        // +0x0c
};
}
namespace SP {
struct tUniversePair {
    void*                 mpEvent;                       // +0x00
    tUniverseActionVector mActions;                      // +0x08

    void Construct(const tUniversePair& value);          // 0x1012f30
};
}
namespace SP {
class cUniversePairVector {
public:
    tUniversePair* Insert(tUniversePair* pPosition, const tUniversePair& value);
    tUniversePair* DoInsertValue(tUniversePair* pPosition, const tUniversePair& value); // 0x1015250

    tUniversePair* mpBegin;                              // +0x00
    tUniversePair* mpEnd;                                // +0x04
    tUniversePair* mpCapacity;                           // +0x08
};
}
void __cdecl FUN_010146c0();  // 0x010146c0 (defined below; used by a stub's inline body)
void __cdecl FUN_01014870();  // 0x01014870 (defined below; used by a stub's inline body)
namespace SP {
class cSimulatorUniverse_s0101_46c0 {
public:
    void FUN_010146c0();
    void FUN_01014870();
    void UpdateGrobShock(int32_t a1, int32_t a2);  // 0x01014a00 (SP::cSimulatorUniverse::UpdateGrobShock)
    void AdjustAwareness();  // 0x01014a80 (SP::cSimulatorUniverse::AdjustAwareness)
    void FUN_01015130();
    void OnTick();  // 0x01014e30 (SP::cSimulatorUniverse::OnTick)
    void StartGrobShock(cStarRecordRef* pRecord, ::cEmpire* pEmpire); // 0x010151a0

    uint8_t            pad000[0x11c];                    // +0x000 .. +0x11b
    uint32_t           mShockThreshold;                  // +0x11c
    uint8_t            pad120[8];                        // +0x120 .. +0x127
    tGrobShockData_s0101_46c0*    mGrobShockBegin;                  // +0x128
    tGrobShockData_s0101_46c0*    mGrobShockEnd;                    // +0x12c
    tGrobShockData_s0101_46c0*    mGrobShockCapacity;               // +0x130
};
}
// ---- items of slice s010146c0 end

// ---- items of slice s01012730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, size_t size);
namespace eastl {
struct cIntArray {
    int* mpBegin;                                            // +0x00
    int* mpEnd;                                              // +0x04
    void Reserve(int count, const void* allocator);          // 0x00b93c60
};
}
namespace eastl {
struct cArrayCopySrc {
    int      mKey;                                           // +0x00
    cIntArray mValues;                                       // +0x04
    uint32_t  mPad0c;                                        // +0x0c
    cIntArray mAllocator;                                    // +0x10
};
}
namespace eastl {
struct cArrayCopyDst {
    int      mKey;                                           // +0x00
    cIntArray mValues;                                       // +0x04
    cArrayCopyDst* Assign(const cArrayCopySrc& src);
};
}
// ---- items of slice s01012730 end

// @ 0x00b8de30
uint32_t cBioElemSort::SortBanners()
{
    uint32_t banner = ((cStarObject*)SP::StarManager(mField184))->FUN_00ba6440();
    uint32_t result = ((cStarObject*)SP::StarManager(banner))->FUN_00ba6d80();
    _ReadWriteBarrier();
    return result;
}

// @ 0x0100d410
float cSPSimulatorSpaceGame::GetTimerSeconds()
{
    return (float)mTimer.GetElapsedTime() * kfMillisecondsPerUnit;
}

// @ 0x0100d500
float ProbabilityFromRatio(float value, float max)
{
    if (!(max > 0.0f))
        return 0.0f;
    double ratio = (double)(value / max);
    return 1.0f - (float)exp(ratio * kfHalfLog);
}

// @ 0x0100d560
void cSimulatorUniverse_s0100_d0d0::Write(cOutStream* pOut)
{
    uint32_t header = 0x2a8c0c0;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), &header, 1, 0);

    uint64_t v0 = mFirstEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v0, 1, 0);
    uint64_t v1 = mSecondEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v1, 1, 0);
    uint64_t v2 = mThirdEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v2, 1, 0);
    uint64_t v3 = mFourthEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v3, 1, 0);
    uint64_t v4 = mFifthEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v4, 1, 0);

    uint32_t count = mEventCount;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), &count, 1, 0);

    float f0 = mfD8;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), (uint32_t*)&f0, 1, 0);

    uint32_t freq = mRaidFrequency;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), &freq, 1, 0);

    float f1 = mfE4;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), (uint32_t*)&f1, 1, 0);

    cVarListSerializer serializer((cVarList*)((char*)this - 8), kSimulatorUniverseName, 0x1a80d26);
    serializer.Serialize(pOut);
}

// @ 0x0100d790
void cSimulatorUniverse_s0100_d0d0::Read(cOutStream* pOut)
{
    uint32_t header;
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), &header, 1, 0);

    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mFirstEvent, 1, 0);
    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mSecondEvent, 1, 0);
    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mThirdEvent, 1, 0);
    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mFourthEvent, 1, 0);
    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mFifthEvent, 1, 0);
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), &mEventCount, 1, 0);
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), (uint32_t*)&mfD8, 1, 0);
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), &mRaidFrequency, 1, 0);
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), (uint32_t*)&mfE4, 1, 0);

    cVarListSerializer serializer((cVarList*)((char*)this - 8), kSimulatorUniverseName, 0x1a80d26);
    serializer.SerializeRead(pOut);
}

// @ 0x0100d960
bool CompareProtectorDistances(cGameNoun* a, cGameNoun* b)
{
    float* pCitiesA = a->GetCivData()->GetCities();
    float fA = pCitiesA[0] * pCitiesA[0] + pCitiesA[1] * pCitiesA[1] + pCitiesA[2] * pCitiesA[2];
    float* pCitiesB = b->GetCivData()->GetCities();
    float fB = pCitiesB[0] * pCitiesB[0] + pCitiesB[1] * pCitiesB[1] + pCitiesB[2] * pCitiesB[2];
    return fB > fA;
}

// @ 0x0100d9f0
void cGrobShockSelection::Reset()
{
    mu110 = 0xffffffff;
    mu114 = 0;
}

// @ 0x0100da10
bool cGrobShockSelection::Get(uint32_t* pOut)
{
    if (mu114 <= 0)
        return false;
    *pOut = mu110;
    return true;
}

// @ 0x0100da40
bool sCompareGrobShockData(void* a, void* b)
{
    uint64_t tA = ((cSPTimer*)((char*)a + 8))->GetElapsedTime();
    uint64_t tB = ((cSPTimer*)((char*)b + 8))->GetElapsedTime();
    return tA < tB;
}

// @ 0x0100daa0
void* DestroyTimerRange(void* first, void* last, void* dest)
{
    while (first != last) {
        ((cGonzagoTimer*)((char*)first + 8))->Destroy();
        first = (char*)first + 0x28;
        dest = (char*)dest + 0x28;
    }
    return dest;
}

// @ 0x0100dae0
int SumOfOtherCivValues()
{
    int total = 0;
    cCivEntryList* pList = SpaceGameGet_s0100_d0d0()->mp30;
    int count = (int)(pList->mp30 - pList->mp2c);
    cCivData* pHome = (cCivData*)GetPlayerHomePlanet();
    if (count <= 0)
        return 0;
    for (int i = 0; i < count; ++i) {
        cCivData* pCiv = pList->mp2c[i];
        if (pCiv != pHome)
            total += GetCivValue(pCiv);
    }
    return total;
}

// @ 0x0100db40
bool BioProtectorSort::operator()(cGameNoun* a, cGameNoun* b)
{
    float* pCitiesA = a->GetCivData()->GetCities();
    float dxA = pCitiesA[0] - mPos[0];
    float dyA = pCitiesA[1] - mPos[1];
    float dzA = pCitiesA[2] - mPos[2];
    float* pCitiesB = b->GetCivData()->GetCities();
    return dxA * dxA + dyA * dyA + dzA * dzA <
           (pCitiesB[0] - mPos[0]) * (pCitiesB[0] - mPos[0]) +
           (pCitiesB[1] - mPos[1]) * (pCitiesB[1] - mPos[1]) +
           (pCitiesB[2] - mPos[2]) * (pCitiesB[2] - mPos[2]);
}

// @ 0x0100dc20
bool BioProtectorSort::CompareAndCheck(cGameNoun* a, cGameNoun* b)
{
    bool bA = a->HasPlace(kPlaceBioProtector);
    bool bB = b->HasPlace(kPlaceBioProtector);
    if (bA == bB) {
        float* pCitiesA = a->GetCivData()->GetCities();
        float dxA = pCitiesA[0] - mPos[0];
        float dyA = pCitiesA[1] - mPos[1];
        float dzA = pCitiesA[2] - mPos[2];
        float* pCitiesB = b->GetCivData()->GetCities();
        return dxA * dxA + dyA * dyA + dzA * dzA <
               (pCitiesB[2] - mPos[2]) * (pCitiesB[2] - mPos[2]) +
               (pCitiesB[1] - mPos[1]) * (pCitiesB[1] - mPos[1]) +
               (pCitiesB[0] - mPos[0]) * (pCitiesB[0] - mPos[0]);
    }
    return !bA;
}

// @ 0x0100dd40
static float Clamp01(float v)
{
    if (!(v > 0.0f))
        return 0.0f;
    if (v > 1.0f)
        return 1.0f;
    return v;
}

// @ 0x0100dfb0
float WarAttackEvent::GetEventFrequency(float deltaSeconds, uint32_t deltaHi)
{
    mTimeSinceLastRaid += ((uint64_t)deltaHi << 32) | *(uint32_t*)&deltaSeconds;

    cPlayerEmpire_s0100_d0d0* pPlayerEmpire = (cPlayerEmpire_s0100_d0d0*)FUN_01021300_s0100_d0d0();
    if (pPlayerEmpire->mp5c == pPlayerEmpire->mp60)
        return 0.0f;

    float fFrequency = 0.0f;
    if (gpSimUniverse->mp10) {
        cSimProperty* pProperty = 0;
        if (gpSimUniverse->mp10->Find(0x31e94b7, &pProperty) && pProperty->mw12 == 0xd)
            fFrequency = *pProperty->GetFloat();
    }

    if (fFrequency * kfThousand <= (float)mTimeSinceLastRaid)
        return 0.0f;

    if (gpSimUniverse->mp10) {
        cSimProperty* pProperty = 0;
        if (gpSimUniverse->mp10->Find(0x31e94b8, &pProperty) && pProperty->mw12 == 0xd)
            fFrequency = *pProperty->GetFloat();
    }

    float fRate = NounManager_s0100_d0d0()->GetCurrentTerrainSphere()->GetValue(0xc42edf05) * fFrequency;
    if (!(fRate > 0.0f))
        return 0.0f;

    double ratio = (double)(((uint64_t)deltaHi << 32) | *(uint32_t*)&deltaSeconds) / (double)fRate;
    return 1.0f - (float)exp(ratio * kfHalfLogPerUnit);
}

// @ 0x0100e150
bool GrobWarAttackEvent::Init()
{
    Property* p;
    {
        cPropertyList* pList = gSimUniverse->mTuning.mpObject;
        if (pList && pList->GetProperty(0x31e94c1, &p) && p->mType == 13)
            mFreqGrobExtremelyAware = *p->GetFloat();
    }
    {
        cPropertyList* pList = gSimUniverse->mTuning.mpObject;
        if (pList && pList->GetProperty(0x31e94c2, &p) && p->mType == 13)
            mFreqGrobVeryAware = *p->GetFloat();
    }
    {
        cPropertyList* pList = gSimUniverse->mTuning.mpObject;
        if (pList && pList->GetProperty(0x31e94c3, &p) && p->mType == 13)
            mFreqGrobAware = *p->GetFloat();
    }
    float secs;
    {
        cPropertyList* pList = gSimUniverse->mTuning.mpObject;
        if (pList && pList->GetProperty(0x31e94c4, &p) && p->mType == 13)
            secs = *p->GetFloat();
    }
    mMinTimeBetweenAttacksMSec = (int)(secs * 1000.0f);
    return true;
}

// @ 0x0100e270
float GrobTeaseRaidEvent::GetEventFrequency(unsigned __int64 deltaMs)
{
    mTimeSinceLastRaidMSec += deltaMs;
    cPlayerEmpire* pEmpire = FUN_01021300();
    cStarManager* stars = StarManager((void*)pEmpire->mEmpireId);
    void* core = stars->GetRelationshipCore();
    bool atWar = ((cRelationshipManager*)RelationshipManager(core))->IsAtWar(core);
    float secs = 0.0f;
    if (pEmpire->mHostileCount != pEmpire->mHostileEnd && !atWar) {
        Property* p;
        if (gSimUniverse->mTuning.mpObject &&
            gSimUniverse->mTuning.mpObject->GetProperty(0x31e94c0, &p) && p->mType == 13)
            secs = *p->GetFloat();
        if ((double)mTimeSinceLastRaidMSec > (double)secs * 1000.0) {
            int threshold = 0;
            GetPropertyInt(gSimUniverse->mTuning.mpObject, 0x31e94b9, &threshold);
            return RaidFrequencyFromTime((float)((double)mTimeSinceLastRaidMSec * 0.001f), threshold);
        }
    }
    return 0.0f;
}

// @ 0x0100e3c0
int PirateRaidAllyEvent::TryCreateMission(IMission* pMission, int param)
{
    char* p = (char*)SpaceGameGet();
    IntVector* list = &(*(SpaceGameData**)(p + 0x30))->mList;
    if ((list->mpEnd - list->mpBegin) != 0 && list->mpBegin != list->mpEnd) {
        int v = list->mpBegin[g_random.RandomUint32Uniform(list->mpEnd - list->mpBegin)];
        if (v) {
            mTimeLo = 0;
            mTimeHi = 0;
            return pMission->Create(v, param);
        }
    }
    return 0;
}

// @ 0x0100e430
float GenericDisaster::GetEventFrequency(unsigned __int64 deltaMs)
{
    float secs = 0.0f;
    char* pGame = (char*)SpaceGameGet();
    char* pData = *(char**)(pGame + 0x30);
    int count = (*(int*)(pData + 0x30) - *(int*)(pData + 0x2c)) >> 2;
    if (count < 1)
        return 0.0f;
    float fraction = (float)(count - *(int*)(pData + 0x104)) / (float)count;
    Property* p;
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x319266b, &p) && p->mType == 13)
        secs = *p->GetFloat();
    float area = ((cTerrainEditor*)NounManager(0xc42edf05))->GetCurrentTerrainSphere()->GetRadius() * secs;
    if (0.0f < area)
        return (float)(1.0 - exp((double)deltaMs / area * -0.000301030028)) * fraction;
    return 0.0f * fraction;
}

// @ 0x0100e550
float ArtifactEvent::GetEventFrequency(unsigned __int64 deltaMs)
{
    mTimeSinceLastArtifactMSec += (unsigned)deltaMs;
    float secs = 0.0f;
    Property* p;
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x2e0583d, &p) && p->mType == 13)
        secs = *p->GetFloat();
    if ((double)mTimeSinceLastArtifactMSec <= (double)secs * 1000.0f)
        return 0.0f;
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x2e057f0, &p) && p->mType == 13) {
        float scale = *p->GetFloat();
        if (0.0f < scale)
            return (float)(1.0 - exp((double)deltaMs / scale * -0.000301030028));
    }
    return 0.0f;
}

// @ 0x0100e690
int BiosphereCollapseEvent::TryCreateMission(IPlanetMission* pMission, int param)
{
    mTimeSinceLastEvent = 0.0f;
    char* p = (char*)SpaceGameGet();
    char* u = *(char**)(p + 0x30);
    if ((unsigned)((*(int*)(u + 0x30) - *(int*)(u + 0x2c)) >> 2) <= 1 &&
        *(int*)(u + 0x18) == *(int*)(u + 0x1c))
        return 0;
    return pMission->Create(GetPlayerHomePlanet(param));
}

// @ 0x0100e6e0
void cSimulatorUniverse::SetPropertyRef(void* def)
{
    if (mTuning.mpObject) {
        Property* pResult;
        mTuning.mpObject->GetProperty(0x5a5e5bc, &pResult);
        mProperty = pResult;
        mPropertyId = 0x5a5e5bc;
        return;
    }
    mProperty = def;
    mPropertyId = 0x5a5e5bc;
}

// @ 0x0100e730
bool cSimulatorUniverse::FindEmbassyEntry(cStarRecordRef* pRef, char* pUniverse)
{
    char* p = mp128;
    char* end = mp12c;
    if (p != end) {
        char* uni = *(char* volatile*)&pUniverse;
        cStarRecordRef* ref = pRef;
        do {
            if (*(int*)(p + 4) == ref->GetCommContext() &&
                *(unsigned*)p == *(unsigned*)(uni + 0x84))
                return true;
            p += 0x28;
        } while (p != end);
    }
    return false;
}

// @ 0x0100e780
bool cSimulatorUniverse::RemoveRaid(int param1, int pNoun, int pEmpire)
{
    void* mgr = GetMissionManager();
    if (!mgr)
        return false;
    if (pNoun) {
        cGameNounManager* nouns = ((cGameNounOwner*)pNoun)->GetNounManager();
        void* avatar = nouns->GetAvatar();
        cStarManager* stars = StarManager(avatar);
        void* empire = stars->GetEmpireByID();
        IMission* mission = ((cSPMissionManager*)mgr)->CreateMissionFromID(0xa4b0a2df, pNoun, empire, 0);
        if (mission) {
            cSPMission* sp = mission->GetSPMission(0x3960c0a);
            if (sp) {
                sp->Init(0);
                sp->SetTarget(pNoun);
                sp->SetEmpire(pEmpire);
                sp->Accept();
            }
        }
    }
    return true;
}

// @ 0x0100e970
int PickWeightedIndex(IntVector* pWeights)
{
    double total = 0.0;
    for (int* it = pWeights->mpBegin; it != pWeights->mpEnd; ++it)
        total += (unsigned)*it;
    if (0.0 < total) {
        double draw = (double)g_random.RandomDoubleUniform() * total;
        if (draw < total) {
            double sum = 0.0;
            int index = 0;
            for (int* it = pWeights->mpBegin; it != pWeights->mpEnd; ++it, ++index) {
                sum += (unsigned)*it;
                if (draw < sum)
                    return index;
            }
        }
        return (int)(pWeights->mpEnd - pWeights->mpBegin) - 1;
    }
    return (int)(pWeights->mpEnd - pWeights->mpBegin);
}

// @ 0x0100ea20
void SortNounsByDistance(cGameNounOwner** pBegin, cGameNounOwner** pEnd, float x, float y, float z)
{
    if (pBegin == pEnd)
        return;
    for (cGameNounOwner** pInsert = pBegin + 1; pInsert != pEnd; ++pInsert) {
        cGameNounOwner* pCurrent = *pInsert;
        if (pCurrent)
            pCurrent->AddRef();
        cGameNounOwner** pSlot = pInsert;
        while (pSlot != pBegin) {
            float* pC = pCurrent->GetNounManager()->GetCities();
            float dx = pC[0] - x;
            float dy = pC[1] - y;
            float dz = pC[2] - z;
            cGameNounOwner* pPrevious = pSlot[-1];
            float* pP = pPrevious->GetNounManager()->GetCities();
            float px = pP[0] - x;
            float py = pP[1] - y;
            float pz = pP[2] - z;
            if (pz * pz + py * py + px * px <= dz * dz + dx * dx + dy * dy)
                break;
            if (pPrevious != *pSlot) {
                if (pPrevious)
                    pPrevious->AddRef();
                cGameNounOwner* pOld = *pSlot;
                *pSlot = pPrevious;
                if (pOld)
                    pOld->Release();
            }
            --pSlot;
        }
        cGameNounOwner* pOld = *pSlot;
        if (pCurrent != pOld) {
            if (pCurrent)
                pCurrent->AddRef();
            *pSlot = pCurrent;
            if (pOld)
                pOld->Release();
        }
        if (pCurrent)
            pCurrent->Release();
    }
}

// @ 0x0100ebb0
void SortNounsByDistanceInPlace(cGameNounOwner** pBegin, cGameNounOwner** pEnd, float x, float y, float z)
{
    for (; pBegin != pEnd; ++pBegin) {
        cGameNounOwner* pCurrent = *pBegin;
        if (pCurrent)
            pCurrent->AddRef();
        cGameNounOwner** pSlot = pBegin;
        for (;;) {
            float* pC = pCurrent->GetNounManager()->GetCities();
            float dx = pC[0] - x;
            float dy = pC[1] - y;
            float dz = pC[2] - z;
            cGameNounOwner* pPrevious = pSlot[-1];
            float* pP = pPrevious->GetNounManager()->GetCities();
            float px = pP[0] - x;
            float py = pP[1] - y;
            float pz = pP[2] - z;
            if (pz * pz + py * py + px * px <= dz * dz + dx * dx + dy * dy)
                break;
            if (pPrevious != *pSlot) {
                if (pPrevious)
                    pPrevious->AddRef();
                cGameNounOwner* pOld = *pSlot;
                *pSlot = pPrevious;
                if (pOld)
                    pOld->Release();
            }
            --pSlot;
        }
        cGameNounOwner* pOld = *pSlot;
        if (pCurrent != pOld) {
            if (pCurrent)
                pCurrent->AddRef();
            *pSlot = pCurrent;
            if (pOld)
                pOld->Release();
        }
        if (pCurrent)
            pCurrent->Release();
    }
}

// @ 0x0100ed20
void SortNounsByCompare(cGameNounOwner** pBegin, cGameNounOwner** pEnd)
{
    if (pBegin == pEnd)
        return;
    for (cGameNounOwner** pInsert = pBegin + 1; pInsert != pEnd; ++pInsert) {
        cGameNounOwner* pCurrent = *pInsert;
        if (pCurrent)
            pCurrent->AddRef();
        NounCompare compare;
        cGameNounOwner** pSlot = pInsert;
        while (pSlot != pBegin && compare.Less(pCurrent, pSlot[-1])) {
            cGameNounOwner* pPrevious = pSlot[-1];
            if (pPrevious != *pSlot) {
                if (pPrevious)
                    pPrevious->AddRef();
                cGameNounOwner* pOld = *pSlot;
                *pSlot = pPrevious;
                if (pOld)
                    pOld->Release();
            }
            --pSlot;
        }
        cGameNounOwner* pOld = *pSlot;
        if (pCurrent != pOld) {
            if (pCurrent)
                pCurrent->AddRef();
            *pSlot = pCurrent;
            if (pOld)
                pOld->Release();
        }
        if (pCurrent)
            pCurrent->Release();
    }
}

// @ 0x0100edf0
void SortNounsByCompareInPlace(cGameNounOwner** pBegin, cGameNounOwner** pEnd)
{
    for (; pBegin != pEnd; ++pBegin) {
        cGameNounOwner* pCurrent = *pBegin;
        if (pCurrent)
            pCurrent->AddRef();
        NounCompare compare;
        bool less = compare.Less(pCurrent, pBegin[-1]);
        cGameNounOwner** pSlot = pBegin;
        while (less) {
            cGameNounOwner* pPrevious = pSlot[-1];
            if (pPrevious != *pSlot) {
                if (pPrevious)
                    pPrevious->AddRef();
                cGameNounOwner* pOld = *pSlot;
                *pSlot = pPrevious;
                if (pOld)
                    pOld->Release();
            }
            less = compare.Less(pCurrent, pSlot[-2]);
            --pSlot;
        }
        cGameNounOwner* pOld = *pSlot;
        if (pCurrent != pOld) {
            if (pCurrent)
                pCurrent->AddRef();
            *pSlot = pCurrent;
            if (pOld)
                pOld->Release();
        }
        if (pCurrent)
            pCurrent->Release();
    }
}

// @ 0x0100efc0
void PromoteHeap(cGameNounOwner** pArray, int topIndex, int nHole, cGameNounOwner* pValue, float x, float y, float z)
{
    while (nHole > topIndex) {
        int nParent = (nHole - 1) / 2;
        float* pP = pArray[nParent]->GetNounManager()->GetCities();
        float px = pP[0] - x;
        float py = pP[1] - y;
        float pz = pP[2] - z;
        float* pC = pValue->GetNounManager()->GetCities();
        float dx = pC[0] - x;
        float dy = pC[1] - y;
        float dz = pC[2] - z;
        if (pz * pz + py * py + px * px <= dz * dz + dx * dx + dy * dy)
            break;
        cGameNounOwner* pParent = pArray[nParent];
        if (pParent != pArray[nHole]) {
            if (pParent)
                pParent->AddRef();
            cGameNounOwner* pOld = pArray[nHole];
            pArray[nHole] = pParent;
            if (pOld)
                pOld->Release();
        }
        nHole = nParent;
    }
    if (pValue != pArray[nHole]) {
        if (pValue)
            pValue->AddRef();
        cGameNounOwner* pOld = pArray[nHole];
        pArray[nHole] = pValue;
        if (pOld)
            pOld->Release();
    }
    if (pValue)
        pValue->Release();
}

// @ 0x0100f1e0
float PirateRaidEvent::GetEventFrequency(unsigned __int64 deltaMs)
{
    mTimeSinceLastRaidMSec += deltaMs;
    float secs = 0.0f;
    Property* p;
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x31e761f, &p) && p->mType == 13)
        secs = *p->GetFloat();
    if ((double)mTimeSinceLastRaidMSec <= (double)secs * 1000.0)
        return 0.0f;
    char* pGame = (char*)SpaceGameGet();
    char* pData = *(char**)(pGame + 0x30);
    float averageSeconds = (float)((*(int*)(pData + 0x30) - *(int*)(pData + 0x2c)) >> 2);
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x31e7620, &p) && p->mType == 13)
        secs = *p->GetFloat();
    SpaceGame* pSpaceGame = (SpaceGame*)SpaceGameGet();
    if (pSpaceGame->mFlags & 0x200)
        secs *= ((SpaceGame*)SpaceGameGet())->GetRaidSpeedFactor(9);
    float radius = ((cTerrainEditor*)NounManager(0xc42edf05))->GetCurrentTerrainSphere()->GetRadius() * secs;
    if (0.0f < averageSeconds) {
        averageSeconds = radius / averageSeconds;
        if (0.0f < averageSeconds)
            return (float)(1.0 - exp((double)deltaMs / averageSeconds * -0.000301030028));
    }
    return 0.0f;
}

// @ 0x010104c0
void FUN_010104c0(void)
{}

// @ 0x01010650
void FUN_01010650(void)
{}

// @ 0x01010720
void __stdcall FUN_01010720(int a, int b)
{
    (void)b;
    Start(a);
}

// @ 0x01010730
void FUN_01010730(void)
{}

// @ 0x010107b0
void FUN_010107b0(void)
{}

// @ 0x01010870
tGrobShockData* tGrobShockData::FUN_01010870(const tGrobShockData& o)
{
    mField00 = o.mField00;
    mField04 = o.mField04;
    _ReadWriteBarrier();
    mTimer.mVtbl = (void*)0x01465d54;
    mTimer.mRefCount = 0;
    mTimer.mElapsedLo = o.mTimer.mElapsedLo;
    mTimer.mElapsedHi = o.mTimer.mElapsedHi;
    mTimer.mBaseLo = o.mTimer.mBaseLo;
    mTimer.mBaseHi = o.mTimer.mBaseHi;
    mTimer.mRunning = o.mTimer.mRunning;
    mTimer.mGetMs = o.mTimer.mGetMs;
    mTimer.mVtbl = (void*)0x01464450;
    return this;
}

// @ 0x010108c0
void FUN_010108c0(void)
{}

// @ 0x010109f0
void FUN_010109f0(void)
{}

// @ 0x01010b30
void FUN_01010b30(void)
{}

// @ 0x01010bb0
tGrobShockData* __cdecl FUN_01010bb0(tGrobShockData* first, tGrobShockData* last, tGrobShockData* result)
{
    while (first != last) {
        *result = *first;
        first++;
        result++;
    }
    return result;
}

// @ 0x01010c20
void FUN_01010c20(void)
{}

// @ 0x01010e30
tGrobShockData* __cdecl FUN_01010e30(tGrobShockData* first, tGrobShockData* last, tGrobShockData* result)
{
    while (first != last) {
        last--;
        result--;
        *result = *last;
    }
    return result;
}

// @ 0x01010ea0
void FUN_01010ea0(void)
{}

// @ 0x01010f70
void FUN_01010f70(void)
{}

// @ 0x01011030
void FUN_01011030(void)
{}

// @ 0x01011120
void FUN_01011120(void)
{}

// @ 0x01011350
void FUN_01011350(void)
{}

// @ 0x01012f30
namespace eastl {
cArrayCopyDst* cArrayCopyDst::Assign(const cArrayCopySrc& src)
{
    mKey = src.mKey;
    int bytes = (int)((char*)src.mValues.mpEnd - (char*)src.mValues.mpBegin);
    mValues.Reserve(bytes >> 2, &src.mAllocator);
    int* dst = mValues.mpBegin;
    memcpy(dst, src.mValues.mpBegin, (size_t)bytes);
    mValues.mpEnd = dst + (bytes >> 2);
    return this;
}
}  // namespace eastl

// @ 0x010137b0
void cSimulatorUniverse_s0101_37b0::UpdateEmpires(u64 elapsed)
{
  float dt = (float)elapsed * 0.001f;
  u64 now = GameTimeGet();
  u32 playerEmpire = GetPlayerEmpireID();

  U32Vec empires;
  empires.mpBegin = 0;
  empires.mpEnd = 0;
  empires.mpCap = 0;
  FUN_010129c0(&empires);

  s32 count = (s32)(empires.mpEnd - empires.mpBegin);
  for (s32 i = 0; i < count; i++) {
    cEmpire* empire = (cEmpire*)empires.mpBegin[i];
    UpdateEmpireAlliancesAndWars(empire, dt);
    *mEmpireMap_18.Index(empire->mId_84) = now;
  }

  RelationshipManager();
  cStarManager_s0101_37b0* stars = StarManager();
  EmpireMap* starMap = (EmpireMap*)stars->FUN_00ba6430();
  if ((*(u32*)0x16dcd50 & 1) == 0) {
    *(u32*)0x16dcd4c = starMap->Begin()->mpEmpire->mId_84;
    *(u32*)0x16dcd50 |= 1;
  }

  s32 processed = 0;
  MapNode* end = starMap->End();
  MapNode* node = LowerBoundKey(starMap->Root(), end, *(u32*)0x16dcd4c);
  if (node == end || *(u32*)0x16dcd4c < node->mKey)
    node = end;

  for (;;) {
    if (node != end) {
      for (;;) {
        if (processed > 99)
          goto done;
        cEmpire* empire = node->mpEmpire;
        if (((empire->mFlags_50 >> 6) & 1) == 0) {
          u32 id = empire->mId_84;
          if (FUN_00d01b50(id, playerEmpire)) {
            MapNode* hit = LowerBoundKey(mEmpireMap_18.Root(), mEmpireMap_18.End(), id);
            if (hit == mEmpireMap_18.End() || hit->mKey != id) {
              u64* slot = mEmpireMap_18.Index(id);
              slot[0] = now;
            } else {
              u64 delta = now - hit->mStamp;
              UpdateEmpireAlliancesAndWars(empire, (float)delta * 0.001f);
              hit->mStamp = now;
            }
          }
        }
        processed++;
        node = RBTreeIncrement(node);
        if (node == starMap->End())
          break;
      }
    }
    node = starMap->Begin();
    *(u32*)0x16dcd4c = node->mpEmpire->mId_84;
    if (processed > 99)
      break;
  }
done:
  if (empires.mpBegin != 0)
    EAFree(empires.mpBegin);
}

// @ 0x01013a70
void cSimulatorUniverse_s0101_37b0::FUN_01013a70(float key, float scale)
{
  bool isPlayer = key == (float)StarManager()->FUN_00885c90();
  FUN_010107b0(key);

  if (mFloatMap_17c.Find(&key) == mFloatMap_17c.End())
    *mFloatMap_17c.Index(&key) = 0.0f;
  float* slot = mFloatMap_17c.Index(&key);

  float hi, lo, cap;
  if (isPlayer) {
    hi  = mClampHi_140;
    lo  = mClampLo_13c;
    cap = mClampCap_14c;
  } else {
    hi  = mClampHiB_164;
    lo  = mClampLoB_160;
    cap = mClampCapB_170;
  }

  float radius =
      ((cTerrainSphere_s0101_37b0*)NounManager()->GetCurrentTerrainSphere(0x24446c70))->GetTerrainRadius();
  if (*slot < hi)
    hi = lo;
  float v = *slot + radius * scale;
  if (v <= hi)
    v = hi;
  if (cap <= v)
    v = cap;
  *slot = v;
}

// @ 0x01013ba0
void cSimulatorUniverse_s0101_37b0::UpdateAwareness(u32 elapsedLo, u32 elapsedHi)
{
  u64 elapsed = ((u64)elapsedHi << 32) | elapsedLo;
  float dt = (float)elapsed * 0.001f;

  s32 id = StarManager()->FUN_00885c90();
  u32 playerEmpire = GetPlayerEmpireID();
  float rate = mPlayerRate_154;

  FUN_010107b0((float)id);
  FUN_01013a70((float)id, -(dt * rate));

  s32 state = FUN_010107b0((float)id);
  if (state == 2 || state == 3)
    mAwareness_158 += elapsedLo;
  else
    mAwareness_158 = 0;

  cTerrainSphere_s0101_37b0* sphere = NounManager()->GetCurrentTerrainSphere(0x24446c70);
  u8 allow = sphere->FUN_00c77410();

  FloatMap* map = &mFloatMap_17c;
  for (MapNode* node = map->Begin(); node != map->End(); node = RBTreeIncrement(node)) {
    u32 empireId = node->mKey;
    if (empireId == (u32)id || empireId == playerEmpire)
      continue;
    FUN_01013a70((float)empireId, -(mOtherRate_178 * dt));
    if (!allow)
      continue;
    cEmpire* empire = StarManager()->GetEmpireByID(empireId);
    if (empire == 0)
      continue;
    if (empire->FUN_00c31bf0(playerEmpire))
      empire->FUN_00c30bb0();
    if (!empire->FUN_00c30b30())
      continue;
    if (!empire->HasDemandForTributeExpired())
      continue;
    empire->FUN_00c32610();
  }
}

// @ 0x01013d20
u32 cSimulatorUniverse_s0101_37b0::FUN_01013d20(u32 id)
{
  u32* rec = mpShockBegin_f8;
  for (; rec != mpShockEnd_fc; rec += 6) {
    cShockObj* obj = (cShockObj*)rec[0];
    if (obj->v0c() != id)
      continue;

    u32* first = (u32*)rec[1];
    u32* last  = (u32*)rec[2];
    s32 n = (s32)(last - first);
    u32* list = 0;
    if (n != 0) {
      list = (u32*)EAAlloc(n * 4, "Simulator", 0, 0,
              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
              0xd1);
    }
    for (s32 k = 0; k < n; k++)
      list[k] = 0;
    for (s32 k = 0; k < n; k++)
      list[k] = ((cShockObj*)first[k])->v08();

    U32Vec ids;
    ids.mpBegin = list;
    ids.mpEnd = list + n;
    ids.mpCap = list + n;
    s32 pick = FUN_0100e970(&ids);
    u32 result = 0;
    if (pick < n) {
      U32Vec out;
      out.mpBegin = 0;
      out.mpEnd = 0;
      out.mpCap = 0;
      s32 released = obj->v04(first[pick], &out);
      if (released > 0) {
        for (u32* p = out.mpBegin; p < out.mpEnd; p++) {
          if (*p != 0)
            ((cShockObj*)*p)->v04(0, 0);
        }
        if (out.mpBegin != 0)
          EAFree(out.mpBegin);
        result = 1;
      }
      if (out.mpBegin != 0)
        EAFree(out.mpBegin);
    }
    if (list != 0)
      EAFree(list);
    return result;
  }
  return 0;
}

// @ 0x01013ec0
tGrobShockData_s0101_37b0* ShockVec::erase(tGrobShockData_s0101_37b0* first, tGrobShockData_s0101_37b0* last)
{
  tGrobShockData_s0101_37b0* newEnd = ShockCopy(last, mpEnd, first);
  tGrobShockData_s0101_37b0* end = mpEnd;
  for (tGrobShockData_s0101_37b0* p = newEnd; p < end; p++)
    p->mTimer_08.~cGonzagoTimer_s0101_37b0();
  mpEnd += last - first;
  return first;
}

// @ 0x01013f20
void ShockVec::DoInsertValue(tGrobShockData_s0101_37b0* pos, const tGrobShockData_s0101_37b0& value)
{
  if (mpEnd != mpCap) {
    tGrobShockData_s0101_37b0* oldEnd = mpEnd;
    mpEnd = mpEnd + 1;
    if (pos == oldEnd) {
      ConstructCopy(oldEnd, value);
    } else {
      ConstructCopy(oldEnd, *(oldEnd - 1));
      MoveElements(pos, oldEnd, oldEnd + 1);
      CopyShockFields(pos, &value);
    }
    return;
  }

  s32 used = (s32)(mpEnd - mpBegin);
  s32 grow;
  tGrobShockData_s0101_37b0* buffer;
  if (used == 0) {
    grow = 1;
    buffer = (tGrobShockData_s0101_37b0*)EAAlloc(0x28, "Simulator", 0, 0,
              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
              0xd1);
  } else {
    grow = used * 2;
    if (grow == 0) {
      buffer = 0;
    } else {
      buffer = (tGrobShockData_s0101_37b0*)EAAlloc(grow * 0x28, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
    }
  }

  tGrobShockData_s0101_37b0* mid = (tGrobShockData_s0101_37b0*)MoveElements(mpBegin, pos, buffer);
  DestroyRange(mpBegin, pos);
  if (mid != 0)
    ConstructCopy(mid, value);
  tGrobShockData_s0101_37b0* newEnd = (tGrobShockData_s0101_37b0*)MoveElements(pos, mpEnd, mid + 1);
  DestroyRange(pos, mpEnd);
  if (mpBegin != 0)
    EAFree(mpBegin);
  mpEnd = newEnd;
  mpBegin = buffer;
  mpCap = buffer + grow;
}

// @ 0x01014090
void ShockQuickSort(tGrobShockData_s0101_37b0* begin, tGrobShockData_s0101_37b0* end, s32 depth, ShockCompare cmp)
{
  s32 n = (s32)((u8*)end - (u8*)begin);
  for (;;) {
    if (n / 0x28 < 0x1d || depth < 1) {
      if (depth == 0)
        ShockPartialSort(begin, end, end, cmp);
      return;
    }
    tGrobShockData_s0101_37b0* mid = begin + (n / 0x50);
    const tGrobShockData_s0101_37b0* pivot;
    if (cmp(*begin, *mid)) {
      pivot = mid;
      if (cmp(*mid, *(end - 1))) {
        pivot = end - 1;
        if (!cmp(*begin, *pivot))
          pivot = begin;
      }
    } else {
      pivot = begin;
      if (!cmp(*begin, *(end - 1))) {
        pivot = end - 1;
        if (!cmp(*mid, *pivot))
          pivot = mid;
      }
    }
    tGrobShockData_s0101_37b0* split = ShockPartition(begin, end, pivot, cmp);
    depth--;
    ShockQuickSort(split, end, depth, cmp);
    n = (s32)((u8*)split - (u8*)begin);
    end = split;
  }
}

// @ 0x01014220
u32 cSimulatorUniverse_s0101_37b0::FUN_01014220(cMissionIface* iface, u32 param)
{
  mField_04 = 0;

  cEmpire* player = GetPlayerEmpire();
  u32 homePlanet = player->GetHomePlanet();

  cStarTable* stars = ((cSpaceGame*)SpaceGameGet())->mpStars_30;
  U32Vec tmp;
  tmp.mpBegin = 0;
  tmp.mpEnd = 0;
  tmp.mpCap = 0;
  FUN_00b93c60(&tmp, (s32)(stars->mStars2_2c.mpEnd - stars->mStars2_2c.mpBegin),
               &stars->mStars2_2c.mpAlloc);

  U32Vec merged;
  merged.mpBegin = 0;
  merged.mpEnd = 0;
  merged.mpCap = 0;
  FUN_00829110(&merged, stars->mStars2_2c.mpBegin, stars->mStars2_2c.mpEnd,
               tmp.mpBegin, iface);
  FUN_01024df0(tmp.mpBegin, merged.mpBegin, (void*)FUN_0100d960);

  s32 n = (s32)(merged.mpBegin - tmp.mpBegin);
  s32 start = (s32)((RandomLinearCongruential_s0101_37b0*)0x1601760)->RandomUint32Uniform(
                        n > 2 ? 3 : n);

  u32 found = 0;
  s32 i = start;
  for (s32 tries = 0; tries < n; tries++) {
    u32 candidate;
    if (tmp.mpBegin[i] == homePlanet) {
      cGameData* gd = (cGameData*)FUN_0107bcb0();
      u32 owner = gd->GetGameDataOwner();
      if (owner <= FUN_00c702f0(homePlanet))
        candidate = tmp.mpBegin[i];
      else
        candidate = 0;
    } else {
      candidate = tmp.mpBegin[i];
    }
    if (candidate != 0) {
      found = candidate;
      break;
    }
    i = (i + 1) % n;
  }

  u32 result = 0;
  if (found != 0 && FUN_0100fb00(found))
    result = iface->v04(found, param);

  for (u32* p = tmp.mpBegin; p < merged.mpBegin; p++) {
    if (*p != 0)
      ((cShockObj*)*p)->v04(0, 0);
  }
  if (tmp.mpBegin != 0)
    EAFree(tmp.mpBegin);
  return result;
}

// @ 0x010143d0
u32 GrobTeaseRaidEvent_s0101_37b0::TryCreateMission(cMissionIface* iface, u32 param)
{
  mTimerLo_08 = 0;
  mTimerHi_0c = 0;

  cStarTable* stars = ((cSpaceGame*)SpaceGameGet())->mpStars_30;
  U32Vec src;
  src.mpBegin = 0;
  src.mpEnd = 0;
  src.mpCap = 0;
  FUN_00b93c60(&src, (s32)(stars->mStars_18.mpEnd - stars->mStars_18.mpBegin),
               &stars->mStars_18.mpAlloc);

  U32Vec out;
  out.mpBegin = 0;
  out.mpEnd = 0;
  out.mpCap = 0;
  FUN_00829110(&out, stars->mStars_18.mpBegin, stars->mStars_18.mpEnd,
               src.mpBegin, iface);
  FUN_01024df0(src.mpBegin, out.mpBegin, (void*)FUN_0100d960);

  s32 n = (s32)(out.mpBegin - src.mpBegin);
  u32 result = 0;
  if (n != 0) {
    s32 k = n < 3 ? n : 3;
    s32 idx = (s32)((RandomLinearCongruential_s0101_37b0*)0x1601760)->RandomUint32Uniform(k);
    u32 candidate = src.mpBegin[idx];
    if (candidate != 0 && FUN_0100fb00(candidate))
      result = iface->v04(candidate, param);
  }
  FUN_00ae6970(&out);
  return result;
}

// @ 0x010144c0
void __cdecl FUN_010144c0(void* self, cStarRefVec* refs)
{
  cStarTable* stars = ((cSpaceGame*)SpaceGameGet())->mpStars_30;
  refs->FUN_01011cc0(&stars->mStars2_2c);

  cGameNounManager_s0101_37b0* nouns = ((cNounBase*)self)->BioProtectorSort();
  Vec3* cities = nouns->GetCities();
  Vec3 pos;
  pos.x = cities->x;
  pos.y = cities->y;
  pos.z = cities->z;
  FUN_01012d70(refs->mpBegin, refs->mpEnd, pos);
}

// @ 0x01014540
s32 __cdecl FUN_01014540(void* mission)
{
  cSPMissionManager_s0101_37b0* managers = (cSPMissionManager_s0101_37b0*)GetMissionManager();
  if (mission == 0)
    return 0;

  cGameNounManager_s0101_37b0* nouns = ((cNounBase*)mission)->BioProtectorSort();
  u32 avatar = (u32)nouns->GetAvatar();
  cEmpire* empire = StarManager()->GetEmpireByID(avatar);

  cSPMission_s0101_37b0* m = managers->CreateMissionFromID(0xc4956aa7, mission, empire, 0);
  if (m == 0)
    return 0;

  cSPRaidEvent* ev = (cSPRaidEvent*)m->v0c(0x397bff2);
  if (ev == 0)
    return 0;

  u32 bomber = (u32)ev->GenerateBomberCount();
  u32 pirate = (u32)ev->GeneratePirateCount();

  cStarRefVec refs;
  refs.mpBegin = 0;
  refs.mpEnd = 0;
  refs.mpCap = 0;
  FUN_010144c0(mission, &refs);

  ((cSpaceTokenTranslator*)*(u32*)0x16e0d08)->mpMission_0c = mission;

  cSPUIEventLog* log = (cSPUIEventLog*)EventLog(0x31df9ac0, 0x131a9f54, 0, 0, 1, 0);
  u32 evt = log->PostFeedbackEvent(0x31df9ac0, 0x131a9f54, 0, 0, 1, 0, 0);

  if (m->mVec_134.mpEnd < m->mVec_134.mpCap) {
    *m->mVec_134.mpEnd++ = evt;
  } else {
    FUN_004558a0(&m->mVec_134, m->mVec_134.mpEnd, &evt);
  }

  FUN_00c47180(ev);
  ev->mMissionID_200 = pirate;
  ev->mElapsedTimeMS_204 = bomber;
  ev->Accept();

  m->v00();
  U32Vec* accepted = (U32Vec*)((u8*)mission + 4);
  if (accepted->mpEnd < accepted->mpCap) {
    *accepted->mpEnd++ = (u32)m;
    m->v00();
  } else {
    FUN_00aea5d0(accepted->mpEnd, &m);
  }
  m->v04();
  FUN_00ae6970(&refs);
  return 1;
}

// @ 0x010146c0
void __cdecl FUN_010146c0()
{
}

// @ 0x01014870
void __cdecl FUN_01014870()
{
}

// @ 0x01014a00
namespace SP {
void __thiscall cSimulatorUniverse_s0101_46c0::UpdateGrobShock(int32_t a1, int32_t a2)
{
    (void)a1;
    (void)a2;
    tGrobShockData_s0101_46c0* pStart = mGrobShockBegin;
    if (pStart == mGrobShockEnd)
        return;
    for (tGrobShockData_s0101_46c0* p = pStart; p != mGrobShockEnd; ) {
        if (p->mTimer.GetElapsedTime() < mShockThreshold)
            break;
        tGrobShockData_s0101_46c0* pNext = p + 1;
        if (pNext < mGrobShockEnd)
            eastl::copy_impl_grob_shock(pNext, mGrobShockEnd, p);
        mGrobShockEnd -= 1;
        mGrobShockEnd->mTimer.~cSPTimer_s0101_46c0();
    }
}
}  // namespace SP

// @ 0x01014a80
namespace SP {
void __thiscall cSimulatorUniverse_s0101_46c0::AdjustAwareness()
{
}
}  // namespace SP

// @ 0x01014db0
namespace SP {
void __cdecl ShockInsertionSort(tGrobShockData_s0101_37b0* first,
                                tGrobShockData_s0101_37b0* last,
                                ShockCompare compare);
void __cdecl ShockInsertionSortStarted(tGrobShockData_s0101_37b0* first,
                                       tGrobShockData_s0101_37b0* last,
                                       ShockCompare compare);
template<typename Size> inline Size ShockLog2(Size n)
{
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return i - 1;
}
void __cdecl quick_sort_grob_shock(tGrobShockData_s0101_37b0* first,
                                   tGrobShockData_s0101_37b0* last,
                                   ShockCompare compare)
{
    if (first != last) {
        ShockQuickSort(first, last, 2 * ShockLog2((int32_t)(last - first)), compare);
        if ((last - first) > 28) {
            ShockInsertionSort(first, first + 28, compare);
            ShockInsertionSortStarted(first + 28, last, compare);
        } else {
            ShockInsertionSort(first, last, compare);
        }
    }
}
}  // namespace SP

// @ 0x01014e30
namespace SP {
void __thiscall cSimulatorUniverse_s0101_46c0::OnTick()
{
}
}  // namespace SP

// @ 0x01015130
struct UniFace;
struct UniNode {
    UniNode* mpNext;
    UniNode* mpPrev;
};
struct UniSub {
    char pad[4];
    UniNode mNode;
    int mCount;
    char mFlag;
    char mPad11[3];
    int mExtra;
    void DoNuke(int n); // 0x009a9600
};
struct UniPair {
    void* mpA;
    void* mpB;
    void Both(void* a, void* b); // 0x01013ec0
};
struct UniFace {
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
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void Method(void* self); // slot +0x54
};
UniFace* UniGetFace(); // 0x00b3d330
namespace SP {
void __thiscall cSimulatorUniverse_s0101_46c0::FUN_01015130()
{
    UniGetFace()->Method(this);
    UniSub* s = (UniSub*)((char*)this + 0x18);
    s->DoNuke(s->mCount);
    UniPair* p = (UniPair*)((char*)this + 0x128);
    s->mNode.mpNext = &s->mNode;
    s->mNode.mpPrev = &s->mNode;
    s->mCount = 0;
    s->mFlag = 0;
    s->mExtra = 0;
    p->Both(p->mpA, p->mpB);
    UniSub* t = (UniSub*)((char*)this + 0x198);
    t->DoNuke(t->mCount);
    t->mNode.mpNext = &t->mNode;
    t->mNode.mpPrev = &t->mNode;
    t->mCount = 0;
    t->mFlag = 0;
    t->mExtra = 0;
}
}  // namespace SP

// @ 0x010151a0
namespace SP {
void __thiscall cSimulatorUniverse_s0101_46c0::StartGrobShock(cStarRecordRef* pRecord, ::cEmpire* pEmpire)
{
    if (!pEmpire)
        return;

    tGrobShockData_s0101_37b0 value;
    value.mId_00 = pEmpire->mId_84;
    value.mField_04 = pRecord->GetCommContext();
    value.mTimer_08.Restart();

    ShockVec& shocks = *(ShockVec*)&mGrobShockBegin;
    if (shocks.mpEnd < shocks.mpCap) {
        tGrobShockData_s0101_37b0* pSlot = shocks.mpEnd;
        shocks.mpEnd = pSlot + 1;
        if (pSlot)
            ::new(pSlot) tGrobShockData_s0101_37b0(value);
    } else {
        shocks.DoInsertValue(shocks.mpEnd, value);
    }

    quick_sort_grob_shock((tGrobShockData_s0101_37b0*)mGrobShockBegin,
                          (tGrobShockData_s0101_37b0*)mGrobShockEnd,
                          (ShockCompare)sCompareGrobShockData);
}
}  // namespace SP

// @ 0x01015250
SP::tUniversePair* __thiscall SP::cUniversePairVector::DoInsertValue(SP::tUniversePair* pPosition, const SP::tUniversePair& value)
{
    return 0;
}

// @ 0x010153a0
SP::tUniversePair* __thiscall SP::cUniversePairVector::Insert(SP::tUniversePair* pPosition, const SP::tUniversePair& value)
{
    uint32_t index = (uint32_t)(pPosition - mpBegin);
    if (pPosition == mpEnd && mpEnd != mpCapacity) {
        SP::tUniversePair* pSlot = mpEnd;
        mpEnd = pSlot + 1;
        if (pSlot)
            pSlot->Construct(value);
        return mpBegin + index;
    }
    DoInsertValue(pPosition, value);
    return mpBegin + index;
}

// @ 0x01015410
void __cdecl UniverseEventMapIndex()
{
}
