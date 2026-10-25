// src/game/SPGonzago/SPSimulatorUniverse.cpp -- migrated from slice(s) s010146c0, s010137b0, s010104c0, s0100e150, s0100d0d0, s00b8d190 by tools/migrate/rewrite.py
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
class cSPTimer {
public:
    uint64_t GetElapsedTime();              // 0x00bc3190
};
class cGonzagoTimer {
public:
    uint8_t pad00[8];
    void Destroy();                         // 0x00b638b0
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
    bool FindEmbassyEntry(char* pUniverse, cStarRecordRef* pRef);   // 0x0100e730
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
  ~cGonzagoTimer_s0101_37b0();                      // 0x00b638b0
};
struct tGrobShockData_s0101_37b0 {
  u32           mId_00;                  // 0x00
  u32           mField_04;               // 0x04
  cGonzagoTimer_s0101_37b0 mTimer_08;               // 0x08
};
struct ShockVec {                        // eastl::vector<tGrobShockData>
  tGrobShockData_s0101_37b0* mpBegin;               // 0x00
  tGrobShockData_s0101_37b0* mpEnd;                 // 0x04
  tGrobShockData_s0101_37b0* mpCap;                 // 0x08
  tGrobShockData_s0101_37b0* erase(tGrobShockData_s0101_37b0* first, tGrobShockData_s0101_37b0* last);
  void  DoInsertValue(tGrobShockData_s0101_37b0* pos, const tGrobShockData_s0101_37b0& value);
};
struct cMissionIface {                   // the mission face passed to the raids
  virtual u32 v00();                     // 0x00
  virtual u32 v04(u32 id, u32 param);    // 0x04
};
struct cSpaceGame {
  u8          mPad_00[0x30];             // 0x00
  cStarTable* mpStars_30;                // 0x30
};
struct cGameNounManager_s0101_37b0 {
  void* GetAvatar();                     // 0x00b1fdb0
  Vec3* GetCities();                     // 0x005c65e0
};
struct cNounBase {                       // `anonymous_namespace'::BioProtectorSort
  cGameNounManager_s0101_37b0* BioProtectorSort();  // 0x00b8de30 (this = the noun)
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
u32   __cdecl GetPlayerEmpireID();                     // 0x01021090
cStarManager_s0101_37b0* __cdecl StarManager();                   // 0x00b3d2a0
cTerrainEditor_s0101_37b0* __cdecl NounManager();                 // 0x00b3d300
MapNode* __cdecl RBTreeIncrement(MapNode* node);       // 0x00921580
void  __cdecl FUN_010144c0(void* self, cStarRefVec* refs);       // 0x010144c0
void  __cdecl FUN_01012d70(void* a, void* b, Vec3 pos);          // 0x01012d70
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

    uint8_t            pad000[0x11c];                    // +0x000 .. +0x11b
    uint32_t           mShockThreshold;                  // +0x11c
    uint8_t            pad120[8];                        // +0x120 .. +0x127
    tGrobShockData_s0101_46c0*    mGrobShockBegin;                  // +0x128
    tGrobShockData_s0101_46c0*    mGrobShockEnd;                    // +0x12c
};
}
// ---- items of slice s010146c0 end

// @ 0x00b8de30
uint32_t cBioElemSort::SortBanners()
{
    uint32_t banner = ((cStarObject*)SP::StarManager(mField184))->FUN_00ba6440();
    return ((cStarObject*)SP::StarManager(banner))->FUN_00ba6d80();
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
bool cSimulatorUniverse::FindEmbassyEntry(char* pUniverse, cStarRecordRef* pRef)
{
    char* p = mp128;
    char* end = mp12c;
    while (p != end) {
        if (*(int*)(p + 4) == pRef->GetCommContext() &&
            *(unsigned*)p == *(unsigned*)(pUniverse + 0x84))
            return true;
        p += 0x28;
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

// @ 0x01010720
void __stdcall FUN_01010720(int a, int b)
{
    (void)b;
    Start(a);
}

// @ 0x01010870
tGrobShockData* tGrobShockData::FUN_01010870(const tGrobShockData& o)
{
    mField00 = o.mField00;
    mField04 = o.mField04;
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
void __cdecl quick_sort_grob_shock()
{
}
}  // namespace SP

// @ 0x01014e30
namespace SP {
void __thiscall cSimulatorUniverse_s0101_46c0::OnTick()
{
}
}  // namespace SP

// @ 0x01015130
namespace SP {
void __thiscall cSimulatorUniverse_s0101_46c0::FUN_01015130()
{
}
}  // namespace SP

// @ 0x010151a0
void __cdecl FUN_010151a0()
{
}

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
