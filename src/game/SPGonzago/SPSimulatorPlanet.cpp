// src/game/SPGonzago/SPSimulatorPlanet.cpp -- migrated from slice(s) s00ff6a50, s00ffb180, s00ffa2c0, s00ff8460, s00ff5d20, s00ff4d50 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSimulatorPlanet.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlayer.h"
#include "SP/cTribe.h"
#include "SP/cDataSerializationInfo.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPropertyList.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCivilization.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPMission.h"
#include "SP/cSPPlanetaryArtifact.h"
#include "SP/cSPTimer.h"
#include <math.h>
#include "SP/cEmpire.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cStarManager.h"
#include "SP/cStarRecord.h"
#include "SP/cPlanetRecord.h"
#include "SP/cRelationshipManager.h"
#include "SP/cTerrainSphere.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "cSPQuaternion.h"
#include "EA/ResourceMan/Key.h"
#include "cSPVector3.h"
#include "SP/cBuilding.h"
#include "SP/cBuildingData.h"
#include "SP/cCityData.h"
#include "SP/cCivData.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cOrnament.h"
#include "SP/cOrnamentData.h"
#include "SP/cPlanet.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cVehicle.h"
#include "SP/cVehicleData.h"
#include "SP/cITerrainSphere.h"

// unnamed retail callees and globals (address in the comment)
extern char g_15b6160;      // [0x015b6160] variable-list table used when writing
extern char g_13f09b4[];    // [0x013f09b4] "Simulator"

// ---- items of slice s00ff4d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_1654c05[];    // [0x01654c05] active-vignette identifier
extern char g_67b69c4[];    // [0x067b69c4] UFO-count message fragments
extern char g_67b69d0[];    // [0x067b69d0]
extern char g_67b69d8[];    // [0x067b69d8]
extern char g_67b69e3[];    // [0x067b69e3]
extern char g_67b69eb[];    // [0x067b69eb]
extern char g_67b69f1[];    // [0x067b69f1]
struct VObj { void** vt; };
typedef void* (__thiscall *FnVp0)(void*);
struct IStream;
bool __cdecl EA_IO_WriteUint32(void* s, const void* p, uint32_t n, int endian); // 0x0093aa70
bool __cdecl EA_IO_ReadInt32(void* s, void* p, uint32_t n, int endian);         // 0x0093a780
void* __cdecl operator_new(uint32_t size, const char* tag, int a, int b, int c, int d); // 0x00f473a0
struct cDataSerializationInfo { char d[0x14]; };
class cVarListSerializer {
public:
    cDataSerializationInfo mInfos[128];  // +0x0000
    int      mSerializableVarCount;      // +0x0a00
    int      mSerializedVarCount;        // +0x0a04
    uint32_t mSignature;                 // +0x0a08
    void*    mpObject;                   // +0x0a0c
    void*    mpSerializerList;           // +0x0a10

    cVarListSerializer(void* obj, void* list, uint32_t sig); // 0x00692f90
    bool __thiscall Serialize(IStream* s);                   // 0x00692900
    bool __thiscall SerializeRead(IStream* s);               // 0x00693e10
};
static inline void* StreamWriter(IStream* s) {
    return ((FnVp0)((VObj*)s)->vt[0x20 / 4])(s);
}
static inline void* WriterValue(void* w) {
    return ((FnVp0)((VObj*)w)->vt[0x18 / 4])(w);
}
struct cRefCounted;
struct cRefCounted {
    virtual void Dtor();                 // vt[0]
    virtual void AddRef();               // vt[4]
    virtual void Release();              // vt[8]
};
struct cGonzagoTimer {
    void __thiscall ctor();                    // 0x00b63890
    void __thiscall dtor();                    // 0x00b638b0
    void __thiscall Start();                   // 0x00bc30f0
    void __thiscall Restart();                 // 0x00bc3130
    long long __thiscall GetElapsedTime();     // 0x00bc3190
    char pad[0x40];
};
struct cColonySimulator {
    void* mpVtbl;                            // +0x00
    int   m04;                               // +0x04
    cGonzagoTimer mTimer;                    // +0x08

    cColonySimulator* __thiscall ctor();                       // 0x00ff54e0
    void* __thiscall scalarDeletingDtor(char flags);           // 0x00ff5810
    void __thiscall DoGrowthSim(void* city);                   // 0x00ff5720
    void __thiscall OnTick(int a, int b, int c);               // 0x00ff5840
};
struct CB8de30 { void* __thiscall GetNounManager(); };   // 0x00b8de30
struct CC8b560 { char  __thiscall IsSomething(); };       // 0x00c8b560
struct CB8dab0 { int   __thiscall GetType(); };           // 0x00b8dab0
struct CAvatar { void* __thiscall GetAvatar(); };         // 0x00b1fdb0
struct CStarManager {
    void* __thiscall GetEmpireByID();                     // 0x00ba9370
    void* __thiscall FUN_00baf700();                      // 0x00baf700
};
struct CTerraforming {
    char __thiscall IsEnabled();                          // 0x00bbe5c0
};
void* __cdecl FUN_01021230();                     // 0x01021230
int   __cdecl FUN_01021090();                     // 0x01021090
void* __stdcall FUN_00b3d2a0(void* which);        // 0x00b3d2a0  SP::StarManager
void* __stdcall FUN_00b3d430(void* which);        // 0x00b3d430  SP::TerraformingManager
char  __cdecl FUN_00c6fe50(void* p);              // 0x00c6fe50
int   __cdecl FUN_0102b010(void* a, char* b, char* c); // 0x0102b010  SP::sGetNumUFOs
void* __cdecl FUN_010666a0_s00ff_4d50();                     // 0x010666a0
struct cSPSimPlanetHighLOD {
    void** mpVtbl;                        // +0x00
    char   pad04[0x20 - 0x04];
    void*  mp20;                          // +0x20

    bool __thiscall WriteBase(IStream* s);       // 0x00b5b610
    char __thiscall ReadBase(IStream* s);        // 0x00b5b650
    bool __thiscall Write(IStream* s);           // 0x00ff5a90
    char __thiscall Read(IStream* s);            // 0x00ff5c50
};
struct CGetter10666a0B {
    int __thiscall FUN_01067e60();        // 0x01067e60
};
void __cdecl FUN_00ce8f70(void* a, int b);            // 0x00ce8f70
void* __cdecl FUN_00b3d480_0();   // 0x00b3d480  (no-argument form)
struct CCityVisualizer {
    void __thiscall setActiveVignette(char* name);   // 0x00ad2560
};
// ---- items of slice s00ff4d50 end

// ---- items of slice s00ff5d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          f32;
struct Vec3 { f32 x, y, z; };
struct cPlanetModel;
struct cGameNounManager;
struct cTerraformingManager;
struct cTriggerMgr;
struct cMessageServer;
struct cEffectsManager;
struct cSPSimulatorSpaceGame;
struct cSPMissionManager;
struct cMoviePlayer;
struct cCity;
cPlanetModel*          __cdecl FUN_00b3d350();   // 0x00b3d350 SP::PlanetModel
cGameNounManager*      __cdecl FUN_00b3d300();   // 0x00b3d300 SP::NounManager
cTerraformingManager*  __cdecl FUN_00b3d430();   // 0x00b3d430 SP::TerraformingManager
cTriggerMgr*           __cdecl FUN_00b3d4d0();   // 0x00b3d4d0 SP::GetTriggerMgr
cMessageServer*        __cdecl FUN_0067dcc0();   // 0x0067dcc0 MessageServer
cEffectsManager*       __cdecl FUN_0067ddd0();   // 0x0067ddd0 EffectsManagerPtr
cSPSimulatorSpaceGame* __cdecl FUN_00ffbe50();   // 0x00ffbe50 SP::GetUFOSimulator
cSPMissionManager*     __cdecl FUN_00feb9f0();   // 0x00feb9f0 SP::GetMissionManager
cMoviePlayer*          __cdecl FUN_010666a0();   // 0x010666a0
void*                  __cdecl FUN_010212a0();   // 0x010212a0 active planet record
void*                  __cdecl FUN_01021370();   // 0x01021370 player home planet
struct cActivePlanet;
cActivePlanet*         __cdecl FUN_01021260();   // 0x01021260 active planet
u32                    __cdecl FUN_00932e80(const char*, u32, u32); // 0x00932e80 FNVHash
void                   __cdecl FUN_01043c60(void*, const void*);    // 0x01043c60
void                   __cdecl SetZooMarker(void*, const void*, const Vec3*, void*); // 0x01043fd0
Vec3*                  __cdecl Swarm_Normalize(Vec3*, void*);       // 0x006e6df0
extern const f32 g_f13eb1bc;   // 0x13eb1bc
extern const f32 g_f13ec480;   // 0x13ec480  0.2f
extern const f32 g_f1486110;   // 0x1486110  5.0f
extern const f32 g_f1494fb8;   // 0x1494fb8  130.0f
extern const f32 g_f16db418;   // 0x16db418
extern const f32 g_f16db41c;   // 0x16db41c
extern const f32 g_f16db420;   // 0x16db420
struct ResourceKey { u32 k0, k1, k2; };   // 12 bytes
struct RefObj {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08(u32);
    virtual void* v0c(void*);
};
struct cHallSub {
virtual void  v00();
virtual void  v04();
virtual void  v08();
virtual void  v0c();
virtual void  v10();
virtual void  v14();
virtual void  v18();
virtual void  v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
    virtual void* v2c();
    virtual void* v30();
    virtual f32   v34();
    virtual void  v38(Vec3*);
    virtual void  v3c(void*);
virtual void  v40();
virtual void  v44();
virtual void  v48();
virtual void  v4c();
virtual void  v50();
virtual void  v54();
virtual void  v58();
virtual void  v5c();
virtual void  v60();
virtual void  v64();
virtual void  v68();
virtual void  v6c();
virtual void  v70();
virtual void  v74();
virtual void  v78();
virtual void  v7c();
virtual void  v80();
virtual void  v84();
virtual void  v88();
virtual void  v8c();
virtual void  v90();
virtual void  v94();
virtual void  v98();
virtual void  v9c();
virtual void  va0();
virtual void  va4();
virtual void  va8();
    virtual void* vac();
};
struct cHallSub2 {    // +0x34 sub-object of the player inventory (vtable slot +0x2c takes a float)
virtual void  v00();
virtual void  v04();
virtual void  v08();
virtual void  v0c();
virtual void  v10();
virtual void  v14();
virtual void  v18();
virtual void  v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
    virtual void* v2c(f32);
};
struct cSub2cU {
virtual void  v00();
virtual void  v04();
virtual void  v08();
virtual void  v0c();
virtual void  v10();
virtual void  v14();
virtual void  v18();
virtual void  v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
    virtual void* v2c(u32);
};
struct cCityHall {
    u8        pad00[0x34];
    cHallSub  mSub;                    // +0x34
};
struct cGovernment {
    void FUN_01062e60(u32);            // 0x01062e60
    void FUN_01062e70(u32, void*);     // 0x01062e70
};
struct cCivilization {
    cGovernment* FUN_00bef8e0();       // 0x00bef8e0
};
struct cCity : RefObj {
    cCivilization* GetCivilization();             // 0x00bd9bf0
    cCityHall*     GetCityHall();                 // 0x00bd9b40
    void           FUN_00bd7f70(Vec3*, void*);    // 0x00bd7f70
};
struct cZooMarkerMgr {
    u8           pad00[0x2c];
    u32          mFlags2c;             // +0x2c
    u8           pad30[0xa0];
    ResourceKey* mBegin;               // +0xd0
    ResourceKey* mEnd;                 // +0xd4
};
struct cPlanetModel {
    void  GetRandomSurfacePoint(Vec3*);   // 0x00b84730
    void* FUN_00b81720(void*);            // 0x00b81720
    bool  FUN_00b7e3e0(Vec3*);            // 0x00b7e3e0
    bool  FUN_00b83870(Vec3*);            // 0x00b83870
    void* FUN_00b7f190(void*, void*);     // 0x00b7f190
};
struct cGameNounManager {
    void*  CreateNoun(void*);             // 0x00b20c60
    cCity* FUN_00b25c30();                // 0x00b25c30
};
struct cMoviePlayer { void FUN_01066dd0(); };   // 0x01066dd0
struct cTerraformingManager {
    u32  FUN_00bbc670(u32);               // 0x00bbc670
    void FUN_00bbf2b0(u32);               // 0x00bbf2b0
};
struct cTriggerMgr {
    void setModal(u32);                                   // 0x00ad7e40
    void FUN_00adde90(u32, void*, u32);                   // 0x00adde90
    void PostTrigger(const char*, u32, u32, u32, u32, u32);// 0x00ae0930
};
struct cMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void v18(u32, u32, u32, u32);
};
struct cEffectsManager {
virtual void v00();
virtual void v04();
virtual void v08(u32);
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18(void*);
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool v2c(u32, u32, void*);
};
struct cPlayerInventory {
    void FUN_00c37130(u32);               // 0x00c37130
    void FUN_00c3aa40(Vec3*, void*);      // 0x00c3aa40
    void FUN_00c3daa0(f32);               // 0x00c3daa0
    void FUN_00c7e2f0(u32);               // 0x00c7e2f0
    u8        pad000[0x34];
    cHallSub2 m34;                        // +0x34
    u8        pad038[0x5ec];
    u8        m624;                       // +0x624
    u8        pad625[0x8f];
    f32       m6b4;                       // +0x6b4
    f32       m6b8;                       // +0x6b8
};
struct cSPSimulatorSpaceGame {
    cPlayerInventory* GetPlayerInventory();   // 0x00a1ad60
};
struct cMissionList { void** mBegin; void** mEnd; };
struct cSPMission {
    u32   GetMissionID();                 // 0x01030e10
    void* GetTargetPlanet();              // 0x00970b30
    void  FUN_00c485e0();                 // 0x00c485e0
};
struct cSPMissionManager {
    cMissionList* GetMissionList();       // 0x00fedd50
};
struct cActivePlanet {
    void* FUN_008414c0();                 // 0x008414c0
    void  FUN_00c7e2f0(u32);              // 0x00c7e2f0
};
struct cInvInner {
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
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
    virtual void v40(u32, void*);
};
struct Mat3 { f32 m[9]; };
struct TriggerCtx { u32 a, b, c; };   // 12-byte trigger payload
struct XformMsg {
    void ctor();
    u16  mFlags;      // +0x00
    u16  mSequence;   // +0x02
    Vec3 mPos;        // +0x04  (its x slot is re-used as the 1.0 "w" tag)
    u16  mPad10;      // +0x10
    u16  mPad12;      // +0x12
    Mat3 mMat;        // +0x14
};
void __cdecl Matrix3FromQuaternion(f32*, void*);   // 0x0059c190
struct cVisualEffect : RefObj {
virtual void v10();
virtual void v14();
    virtual void v18(void*);
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
    virtual void v40(u32, void*);
    virtual void v44(u32, void*, u32);
};
struct cSPPlanetaryArtifact {
    void Set(u8, void*, u16, u32);        // 0x00c74d30
    u8        pad000[0x34];
    cHallSub  mSub;                       // +0x34
    u8        pad038[0x1ec];
    u32       m224;                       // +0x224
    u8        pad228[0x418];
    u32       m640;                       // +0x640
    u8        pad644[0x1a];
    u8        m65e;                       // +0x65e
};
struct cArtifactParams {
    u32 k0;                               // +0x00
    f32 x4;                               // +0x04
    f32 y8;                               // +0x08
    f32 z_c;                              // +0x0c
    u16 w10;                              // +0x10
    u8  b12;                              // +0x12
    u8  pad13[5];
    u32 v18;                              // +0x18
    u8  pad1c[0xc];
    u8  flags28;                          // +0x28
};
struct cSub1e4   { void FUN_007d01d0(u32, u32); };  // 0x007d01d0
struct cField1b0 { void FUN_00ebdc20(void*, f32); };// 0x00ebdc20
struct cSPTimer  { u8 mBytes[0x20]; void Restart(); };// 0x00bc3130
struct cSPSimPlanetHighLOD_s00ff_5d20 {
    void FUN_00ff6190();                       // 0x00ff6190
    void FUN_00ff6290();                       // 0x00ff6290
    void FUN_00ff62d0();                       // 0x00ff62d0
    void FUN_00ff6200();                       // 0x00ff6200
    void FUN_00ff6450(Vec3*);                  // 0x00ff6450
    void FUN_00ff6520(void*, f32);             // 0x00ff6520
    cSPPlanetaryArtifact* SpawnArtifact(cArtifactParams*);   // 0x00ff5d20
    void StartCVG2SPG(u32, u8);                // 0x00ff5ee0
    void ShowUFOForTransition();               // 0x00ff60d0
    void StartUFOCelebration(cCity*);          // 0x00ff65f0

    u8             pad000[0x18];
    cVisualEffect* mp18;                       // +0x18
    cVisualEffect* mp1c;                       // +0x1c
    u8             pad020[0x10];
    cCity*         mpCity;                     // +0x30
    u8             pad034[0x124];
    u8             m158;                       // +0x158
    u8             pad159[3];
    Vec3           m15c;                       // +0x15c
    u32            m168;                       // +0x168
    u8             pad16c[4];
    cSPTimer       mTimer170;                  // +0x170
    f32            m190;                       // +0x190
    f32            m194;                       // +0x194
    f32            m198;                       // +0x198
    u8             pad19c[0x14];
    cField1b0*     mp1b0;                      // +0x1b0
    u8             pad1b4[0x30];
    cSub1e4        m1e4;                       // +0x1e4
};
// ---- items of slice s00ff5d20 end

// ---- items of slice s00ff8460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void quick_sort_impl(int a, int b, int depth);   // 0x00ff8260
extern void FUN_00ff5ba0(int a, int b);                 // 0x00ff5ba0
extern void FUN_00ff5be0(int a, int b);                 // 0x00ff5be0
extern void* __cdecl SP_NounManager();                     // 0x00b3d300
extern void op_delete_array(void* p);   // operator_delete_array 0x00f47380
extern void __fastcall BaseGonzagoSim_ctor(void* self);   // 0x00b5b6c0
extern void* __cdecl operator_new(unsigned size, const char* desc,
                                  int a, int b, int c, int d);   // 0x00f473a0
extern void* __cdecl FUN_01067e60(void* a);                // 0x01067e60
extern void  __cdecl FUN_010421c0(void* a, void* b);       // 0x010421c0
extern void  __cdecl FUN_01009a40(void* a);                // 0x01009a40
extern int   __cdecl FUN_00b8e040(void* a, int b);         // 0x00b8e040
extern void  __cdecl FUN_00ac9200(void* a);                // 0x00ac9200
extern void  __cdecl FUN_00c74a30(void* a);                // 0x00c74a30
extern void  __cdecl FUN_00c74860(void* a);                // 0x00c74860
extern void  __cdecl FUN_00f924e0(void* a, float f);       // 0x00f924e0
extern void  __cdecl FUN_00dd85c0(void* a, void* b);       // 0x00dd85c0
extern void* __cdecl SP_PropertyManager();                 // 0x0067de30
extern void  __cdecl SP_GetPropertyAsKeyInstance(void* a, unsigned k, void* out);  // 0x006a12a0
extern void* __cdecl SP_CreateNoun(void* self, unsigned key);    // 0x00b20c60
extern void* __cdecl SP_QuaternionFromDirections(void* q, void* d, void* up);      // 0x00698180
extern float* __cdecl SP_GetPropertyAsFloat();             // 0x0041ea70
extern void* __cdecl SP_StarManager(void* a);              // 0x00b3d2a0
extern void* __cdecl SP_GetEmpireByID(void* sm);           // 0x00ba9370
extern void* __cdecl SP_GetStarRecords(void* sm);          // 0x00bb1080
extern void* __cdecl SP_GetStars(void* emp);               // 0x00c308d0
extern void* __cdecl SP_GetUFOKey(void* emp);              // 0x00c326b0
extern void* __cdecl SP_CreateUFO(int a, void* b, void* c);     // 0x0102acb0
extern void* __cdecl SP_SpaceGameGet(void* ufo);           // 0x01002bd0
extern void* __cdecl SP_GetSpaceCombatTuning();            // 0x01029940
extern void* __cdecl SP_EffectsManager();                  // 0x0067ddd0
extern void* __cdecl SP_GetSystemAT();                     // 0x00a206f0
extern int   __cdecl SP_FNVHash(const char* s, unsigned seed, int a);   // 0x00932e80
extern void* __cdecl SP_GetUFOSimulator();                 // 0x00ffbe50
extern void* __cdecl SP_GetPlayerInventory(void* sim);     // 0x00a1ad60
extern void  __cdecl SP_Matrix3Assign(void* m, void* src); // 0x0041cb40
extern void* __cdecl SP_Matrix3FromFacingAndUp(void* out, void* a, void* b);  // 0x0069b440
extern void* __cdecl SP_GetSetting9();                     // 0x00401090
extern void* __cdecl SP_GetAvatarProfile(void* a);         // 0x004df420
extern void* __cdecl SP_GetGameDataVector(void* self, unsigned a, void* b,
                                          void* c, void* d, void* e);   // 0x00b21340
extern void* __cdecl FUN_00bd9d70(void* a, int b);         // 0x00bd9d70
extern void* __cdecl SP_GetPlayerCivilization(void* self); // 0x00b25fb0
extern void* __cdecl SP_GetPlayerEmpireOrMinus1();         // 0x00b1f9d0
extern void  __cdecl SP_SetPlayerEmpire(void* a, void* b, int c, unsigned d, int e);
extern void  __cdecl SP_ReduceCitiesOnPlanet(void* self, void* city);   // 0x00bf4370
extern void* __cdecl SP_GetCivilization(void* city);       // 0x00bd9bf0
extern void* __cdecl FUN_00be8680(void* a, int b, int c, int d, int e,
                                  int f, int g, int h, int i, int j);   // 0x00be8680
extern void* __cdecl GetPlayerEmpireIDFn();                // 0x01021090
extern unsigned g_placeEmbassy;                            // 0x016db738
struct FixedPoolBase {
    void* mpHead;                                  // +0x00
    void* mpUnk04;                                 // +0x04  (never written here)
    // eastl::fixed_pool_base::init @ 0x00921260 (__thiscall ret 0x14)
    void init(void* pBegin, unsigned nodeSize, unsigned nodeCount,
              unsigned alignment, unsigned flags);
};
struct PooledRegion {
    void*         mPrev;        // +0x00  list sentinel
    void*         mNext;        // +0x04  list sentinel
    FixedPoolBase mPool;        // +0x08  embedded fixed pool
    void*         mFirst10;     // +0x10
    void*         mLast14;      // +0x14
    unsigned      mCount18;     // +0x18
    char          mNodes[1];    // +0x1c  node buffer (node stride 0xf0)

    PooledRegion* FUN_00ff8460();
};
extern void* SP_NounManager(void);
struct GameDataRange {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
};
struct GameDataList {
    void*         mpUnk0;   // +0x00
    GameDataRange mRange;   // +0x04
};
struct cGameNounManager_s00ff_8460 {
    GameDataList* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340 (cGameNounManager::GetGameDataVector)
};
typedef void (__fastcall *GameDataSlotFn)(void* self);
struct RCObject {
    virtual void v00();      // +0x00  AddRef
    virtual void v04();      // +0x04  Release
    virtual void v08();      // +0x08  Release (variant)
    virtual void* v0c(int);   // +0x0c
};
struct SimListNode { SimListNode* mpNext; SimListNode* mpPrev; RCObject* mpObj; };   // 0x0c B  (pool list node)
struct SimPool34   {
    SimListNode mHead;        // +0x34  intrusive list sentinel
    unsigned    mData[0x46];  // +0x40  pool storage
    void Init();                               // 0x00ff8460
    void Destroy();                            // 0x00ff80b0
    SimListNode* AllocNode(const void* pData); // 0x00ff8100
    void PopFront();                           // 0x00ff8210
};
struct SimTimer170 {                                                       // 0x2c B
    unsigned mData[0x0b];
    void Init();                               // 0x00b63890
    void Destroy();                            // 0x00b638b0
};
struct SimTree1c0 {                                                          // +0x1c0..+0x1cc
    void* mpRoot;      // +0x1c0
    void* mpNode;      // +0x1c4  self-linked sentinel head
    void* mpPrev;      // +0x1c8
    void Destroy(void* pNode);          // 0x00d0c930
};
struct SimSub1e4   {
    unsigned mData[0x01];
    void Init();                               // 0x007cf5d0
    void Destroy();                            // 0x007cfa90
};
struct cSPSimPlanetHighLOD_s00ff_8460 {
    void*         mpVtbl0;      // +0x00  primary vtable
    void*         mpUnk04;      // +0x04
    void*         mpVtbl8;      // +0x08  secondary (base-subobject) vtable
    void*         mPad0c;       // +0x0c
    unsigned      mFlag10;      // +0x10
    unsigned char mByte14;      // +0x14
    unsigned char mPad15[3];    // +0x15
    RCObject*     mpFx18;       // +0x18  release vtable+4
    RCObject*     mpFx1c;       // +0x1c  release vtable+4
    RCObject*     mpFx20;       // +0x20  release vtable+8
    void*         mPad24;       // +0x24
    RCObject*     mpFx28;       // +0x28  release vtable+8 (reset to null first)
    RCObject*     mpFx2c;       // +0x2c  release vtable+4
    RCObject*     mpFx30;       // +0x30  release vtable+4
    SimPool34     mPool34;      // +0x34
    unsigned char mByte158;     // +0x158
    unsigned char mPad159[3];   // +0x159
    float         mF15c;        // +0x15c
    float         mF160;        // +0x160
    float         mF164;        // +0x164
    void*         mPad168[2];   // +0x168
    SimTimer170   mTimer170;    // +0x170
    unsigned*     mpArray19c;   // +0x19c  heap array (delete[] when the preceding slot is non-zero)
    void*         mpUnk1a0;     // +0x1a0
    void*         mpUnk1a4;     // +0x1a4
    void*         mPad1a8[2];   // +0x1a8
    RCObject*     mpFx1b0;      // +0x1b0  release vtable+8
    unsigned char mByte1b4;     // +0x1b4
    unsigned char mPad1b5[3];   // +0x1b5
    void*         mpUnk1b8;     // +0x1b8
    RCObject*     mpFx1bc;      // +0x1bc  release vtable+4
    SimTree1c0    mTree1c0;     // +0x1c0
    void*         mpNode1cc;    // +0x1cc
    unsigned      mCount1d0;    // +0x1d0  sentinel node count (cleared as a dword)
    void*         mpUnk1d4;     // +0x1d4
    void*         mPad1d8;      // +0x1d8
    RCObject*     mpFx1dc;      // +0x1dc  release vtable+4
    unsigned char mByte1e0;     // +0x1e0
    unsigned char mPad1e1[3];   // +0x1e1
    SimSub1e4     mSub1e4;      // +0x1e4

    ~cSPSimPlanetHighLOD_s00ff_8460();
    void AddToList(const unsigned* pSrc, RCObject* pObj);              // 0x00ff88c0
    void SpawnRallyChargeup(void* pTarget, float* pPos);               // 0x00ff8e00
};
extern RCObject* __fastcall Simulator_alloc(void* mem);   // 0x00ff54e0
extern void* __cdecl FUN_01021240_s00ff_8460();                       // 0x01021240  SimulatorUniverse::instance
extern void* __cdecl FUN_010666a0_s00ff_8460();                       // 0x010666a0
// ---- items of slice s00ff8460 end

// ---- items of slice s00ffa2c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV  virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
namespace SP {
struct Vec3_s00ff_a2c0 { float x, y, z; };
}
namespace SP {
struct RefObj_s00ff_a2c0 {
    PV
    virtual void Release();          // +0x04
    virtual void FX();               // +0x08
    virtual void SetFlag(int);       // +0x0c
    void FUN_00ebd340();             // 0x00ebd340
};
}
namespace SP {
struct RefObjI {
    PV
    virtual void Release();          // +0x04
    virtual void Slot2(int);         // +0x08
    virtual void SetFlag(int);       // +0x0c
};
}
namespace SP {
struct SFXObj {
    void FUN_00becd70(int);          // 0x00becd70
};
}
namespace SP {
struct CreatureAnim {
    void* Play(int a, unsigned flags);   // 0x00bc96a0
};
}
namespace SP {
struct Creature { uint32_t m00, m04; CreatureAnim m08; };
}
namespace SP {
struct Sub120 {                         // noun+0x120 (position provider)
    PV8 PV2 PV
    virtual Vec3_s00ff_a2c0* Slot2C();             // +0x2c
};
}
namespace SP {
struct Sub508 {                         // noun+0x508
    int FUN_008e7f80();                 // 0x008e7f80
};
}
namespace SP {
struct PbObj {                          // *(noun+0x518)
    PV4 PV2
    virtual void* Slot18();             // +0x18
};
}
namespace SP {
struct Entity {
    PV                                  // +0x00
    virtual void* Slot04(int);          // +0x04
    PV8                                 // +0x08..0x24
    PV                                  // +0x28
    virtual bool  Slot2C();             // +0x2c
    PV4 PV2 PV                          // +0x30..0x48
    virtual int   Slot4C();             // +0x4c
    PV4 PV                          // +0x50..0x60
    virtual Vec3_s00ff_a2c0* Slot64();             // +0x64
    PV                                  // +0x68
    virtual SFXObj* Slot6C();           // +0x6c
    bool  FUN_00c372b0();               // 0x00c372b0
    bool  FUN_00c004c0(int);            // 0x00c004c0
    int   FUN_00bd9b60();               // 0x00bd9b60
    void  FUN_00bdc050();               // 0x00bdc050
    // data (object offset +0x04 onward)
    uint8_t pad04[0x10 - 0x04];
    int8_t  m10;                        // +0x10
    uint8_t pad11[0x12 - 0x11];
    int8_t  m12;                        // +0x12
    uint8_t pad13[0x18 - 0x13];
    int     m18;                        // +0x18
    uint8_t pad1c[0x28 - 0x1c];
    int     m28;                        // +0x28
    uint8_t pad2c[0x120 - 0x2c];
    Sub120  m120;                       // +0x120
    uint8_t pad124[0x220 - 0x124];
    float   m220;                       // +0x220
    uint8_t pad224[0x508 - 0x224];
    Sub508  m508;                       // +0x508
    uint8_t pad50c[0x518 - 0x50c];
    PbObj*  m518;                       // +0x518
    uint8_t pad51c[0x640 - 0x51c];
    int     m640;                       // +0x640
    uint8_t pad644[0x658 - 0x644];
    int     m658;                       // +0x658
    uint8_t pad65c[0x68c - 0x65c];
    int     m68c;                       // +0x68c
    uint8_t pad690[0x6c8 - 0x690];
    Creature* m6c8;                     // +0x6c8
    uint8_t pad6cc[0x714 - 0x6cc];
    int     m714;                       // +0x714
    uint8_t pad718[0x748 - 0x718];
    float   m748;                       // +0x748
    int     m74c;                       // +0x74c
};
}
namespace SP {
struct RecElem {
    uint8_t pad00[0x12];
    int8_t  m12;                        // +0x12
    uint8_t pad13[0x18 - 0x13];
    int     m18;                        // +0x18
    uint8_t pad1c[0x28 - 0x1c];
    int     m28;                        // +0x28
};
}
namespace SP {
struct ElemList {
    RecElem* m00;                       // +0x134
    RecElem* m04;                       // +0x138
    void FUN_00b8e540(RecElem*);        // 0x00b8e540
};
}
namespace SP {
struct GdVector { uint32_t m00; void** m04; void** m08; uint32_t m0c; uint32_t m10; };
}
namespace SP {
struct GameTimeManager { uint64_t FUN_00b316c0(); };   // 0x00b316c0
}
namespace SP {
struct NounIter { void FUN_00acc390(); void FUN_00ad0bd0(); };
}
namespace SP {
struct cGameNounManager_s00ff_a2c0 {
    void* GetAvatar();                                             // 0x00b1fdb0
    void  RemoveNoun(void*);                                       // 0x00b225d0
    GdVector* GetGameDataVector(void*, void*, void*, void*, void*); // 0x00b21340
    void  FUN_00b25fe0();                                          // 0x00b25fe0
    void  FUN_00b22bc0();                                          // 0x00b22bc0
    void  FUN_00b22960();                                          // 0x00b22960
    void  FUN_00b222a0();                                          // 0x00b222a0
};
}
namespace SP {
struct AudioSystem {
    PV8 PV4 PV2
    virtual void Slot38(int);                                       // +0x38
    virtual void Slot3c(int, float);                                // +0x3c
    virtual void Slot40(int, int);                                  // +0x40
    PV4 PV
    virtual void Slot58();                                          // +0x58
};
}
namespace SP {
struct BehaviorManager {
    PV8 PV4
    virtual void Slot30();                                          // +0x30
    PV4
    virtual void Slot44();                                          // +0x44
};
}
namespace SP {
struct CheatManager {
    PV4 PV2 PV
    virtual void Slot1c(void*);                                     // +0x1c
};
}
namespace SP {
struct MessageServer {
    PV4 PV
    virtual void Slot14(int, int, int);                             // +0x14
};
}
namespace SP {
struct SimTicker {
    PV16 PV4 PV
    virtual void Slot54(void*);                                     // +0x54
};
}
namespace SP {
struct SimSingleton {
    SimSingleton* ctor();               // 0x00dc7d70
    void FUN_00dcc2c0();                // 0x00dcc2c0
};
}
namespace SP {
struct cStarRecord_s00ff_a2c0 { uint8_t pad[4]; };
}
namespace SP {
struct cEmpire_s00ff_a2c0 {
    uint8_t pad00[0x84];
    cStarRecord_s00ff_a2c0* m84;                   // +0x84
    int  GetUFOKey();                   // 0x00c326b0
    int  GetHomePlanet();               // 0x00c31730
    bool IsHostileToPlayer();           // 0x00c309e0
};
}
namespace SP {
struct cStarManager_s00ff_a2c0 { cEmpire_s00ff_a2c0* GetEmpireByID(int id); };           // 0x00ba9370
}
namespace SP {
struct InvSub {
    PV8 PV2 PV
    virtual Vec3_s00ff_a2c0* Slot2C();             // +0x2c
};
}
namespace SP {
struct Inventory {
    uint8_t pad00[0x34];
    InvSub m34;                         // +0x34
    bool FUN_00c38500();                // 0x00c38500
};
}
namespace SP {
struct UFOsim { Inventory* GetPlayerInventory(); };                // 0x00a1ad60
}
namespace SP {
struct PlanetModelObj {
    void GetRandomSurfacePoint(Vec3_s00ff_a2c0*); // 0x00b84730
    void FUN_00b87bb0();               // 0x00b87bb0
};
}
namespace SP {
struct cSPGameDataUFO_s00ff_a2c0 {
    void FUN_00c3be70(Vec3_s00ff_a2c0*);          // 0x00c3be70
    void FUN_00c3daa0(float);          // 0x00c3daa0
    void PopToDestination();           // 0x00c37e60
};
}
namespace SP {
struct PlanetObj {                      // GetActivePlanet()
    uint8_t pad00[0x108];
    int m108;                           // +0x108
    int  FUN_00c71e30();                // 0x00c71e30
    int  FUN_00c70e00();                // 0x00c70e00
    void FUN_00c70bc0(int);             // 0x00c70bc0
};
}
namespace SP {
struct PlanetRecord {                   // GetActivePlanetRecord()
    uint8_t pad00[0x134];
    ElemList mElemList;                 // +0x134
    cGameNounManager_s00ff_a2c0* FUN_00b8de30();        // 0x00b8de30
    int          FUN_00b8dab0();        // 0x00b8dab0
};
}
namespace SP {
struct RandomLCG { float FUN_009360d0(); };                         // 0x009360d0
}
namespace SP {
struct cSPSpaceCombatTuning { float GetLootCityMoneyChance(); };    // 0x0102a310
}
namespace SP {
struct AeObj { void FUN_00ae49d0(int, int, void*, int, int, int, int, int); };  // 0x00ae49d0
}
namespace SP {
struct TempC {
    void* mPtr;                         // scratch array begin
    void FUN_00b93c60(int, void*);      // 0x00b93c60
};
}
namespace SP {
extern char gFn_00cd7d10[];    // 0x00cd7d10
}
namespace SP {
extern char gFn_00d3d420[];    // 0x00d3d420
}
namespace SP {
extern char gFn_00ad48b0[];    // 0x00ad48b0
}
namespace SP {
extern char gFn_00acdff0[];    // 0x00acdff0
}
namespace SP {
extern char gFn_00ad4930[];    // 0x00ad4930
}
namespace SP {
extern char gFn_00b1e500[];    // 0x00b1e500
}
namespace SP {
extern char gStr_spgspg[];     // 0x01495078 "spg_war_music_level"
}
namespace SP {
extern char gStr_SimSingleton[]; // 0x0145f924 "Simulator/SimSingleton"
}
namespace SP {
extern uint32_t gU_15b8690;     // 0x015b8690
}
namespace SP {
extern void* gSim_1699ab8;      // 0x01699ab8
}
namespace SP {
extern RandomLCG gRand_1601760; // 0x01601760
}
namespace SP {
cGameNounManager_s00ff_a2c0* NounManager();          // 0x00b3d300
}
namespace SP {
GameTimeManager* GameTimeManager300();    // 0x00b3d380
}
namespace SP {
cStarManager_s00ff_a2c0* StarManager();              // 0x00b3d2a0
}
namespace SP {
PlanetModelObj* PlanetModel();            // 0x00b3d350
}
namespace SP {
SimTicker* SimTicker_();                  // 0x00b3d330
}
namespace SP {
BehaviorManager* BehaviorManager_();      // 0x00b3d260
}
namespace SP {
CheatManager* CheatManager_();            // 0x0067de20
}
namespace SP {
MessageServer* MessageServer_();          // 0x0067dcc0
}
namespace SP {
AudioSystem* GetSystemAT();               // 0x00a206f0
}
namespace SP {
UFOsim* GetUFOSimulator();                // 0x00ffbe50
}
namespace SP {
PlanetObj* GetActivePlanet();             // 0x01021260
}
namespace SP {
PlanetRecord* GetActivePlanetRecord();    // 0x010212a0
}
namespace SP {
cEmpire_s00ff_a2c0* GetPlayerEmpire();               // 0x01021300
}
namespace SP {
int GetPlayerEmpireID();                  // 0x01021090
}
namespace SP {
cGameNounManager_s00ff_a2c0* FUN_01021240();         // 0x01021240
}
namespace SP {
NounIter* FUN_00b3d480();                 // 0x00b3d480
}
namespace SP {
cSPGameDataUFO_s00ff_a2c0* CreateUFO(int, void*, int);   // 0x0102acb0
}
namespace SP {
cSPSpaceCombatTuning* GetSpaceCombatTuning(); // 0x01029940
}
namespace SP {
void DropLoot(Vec3_s00ff_a2c0);                      // 0x0102ba30
}
namespace SP {
void* operator_new(uint32_t, const void*, int, int, int, int);  // 0x00f473a0
}
namespace SP {
void  operator_delete_array(void*);       // 0x00f47380
}
namespace SP {
void* RBTreeIncrement(void*);             // 0x00921580
}
namespace SP {
void  FUN_00ba5270(void*, int);           // 0x00ba5270
}
namespace SP {
void  FUN_00bd7f70(Vec3_s00ff_a2c0*, float*);        // 0x00bd7f70
}
namespace SP {
uint32_t FNVHash(const char*, uint32_t, int);  // 0x00932e80
}
namespace SP {
void  FUN_00c9a080();                     // 0x00c9a080
}
namespace SP {
void  FUN_00829110(void**, void*, void*, void*, void*); // 0x00829110
}
namespace SP {
void* FUN_00b26930(int, int, void*, int, int, int, int, int);   // 0x00b26930
}
namespace SP {
int   FUN_0102b690(int, int, int);        // 0x0102b690
}
namespace SP {
struct ListNode { ListNode* mNext; uint32_t m04; RefObj_s00ff_a2c0* m08; };
}
namespace SP {
struct ListHead {
    ListNode* mHead;                    // +0x34
    ListNode* mTail;                    // +0x38
    void FUN_00ff80b0();                // 0x00ff80b0
};
}
namespace SP {
struct TreeNode { uint8_t pad[0x14]; RefObj_s00ff_a2c0* m14; };
}
namespace SP {
struct RBTree {
    uint32_t m00;                       // +0x1c0
    void*    m04;                       // +0x1c4
    void*    m08;                       // +0x1c8
    void*    m0c;                       // +0x1cc
    uint8_t  m10;                       // +0x1d0
    uint32_t m14;                       // +0x1d4
    void FUN_00d0c930(void*);           // 0x00d0c930
};
}
namespace SP {
class cSPSimPlanetHighLOD_s00ff_a2c0 {
public:
    void FUN_00ffa2c0();                       // 0x00ffa2c0
    void CreateReplacement();                  // 0x00ffa780
    void BlowUpCity(void* city, int param3);   // 0x00ffa900
    void FUN_00ffaa90(int param);              // 0x00ffaa90
    void FUN_00ffabc0();                       // 0x00ffabc0
    void FUN_00ffb030();                       // 0x00ffb030

    uint8_t pad00[0x10];
    int     m10;                        // +0x10
    int8_t  m14;                        // +0x14
    uint8_t pad15[0x18 - 0x15];
    RefObj_s00ff_a2c0* m18;                        // +0x18
    RefObj_s00ff_a2c0* m1c;                        // +0x1c
    uint8_t pad20[0x28 - 0x20];
    RefObj_s00ff_a2c0* m28;                        // +0x28
    RefObj_s00ff_a2c0* m2c;                        // +0x2c
    RefObj_s00ff_a2c0* m30;                        // +0x30
    ListHead m34;                       // +0x34
    uint8_t pad3c[0x1b0 - 0x3c];
    RefObj_s00ff_a2c0* m1b0;                       // +0x1b0
    int8_t  m1b4;                       // +0x1b4
    uint8_t pad1b5[0x1b8 - 0x1b5];
    int     m1b8;                       // +0x1b8
    RefObj_s00ff_a2c0* m1bc;                       // +0x1bc
    RBTree  m1c0;                       // +0x1c0
    RefObjI* m1dc;                      // +0x1dc
    int8_t  m1e0;                       // +0x1e0
};
}
// ---- items of slice s00ffa2c0 end

// ---- items of slice s00ffb180 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete_array(void* pBlock);                                                          // 0x00f47380
extern char g_nounListPlanet[];        // 0x018c43e8
extern char g_nounListHarvest[];       // 0x0142db2a
extern uint32_t g_planetBusterKey[3];  // 0x016db5c4 planet-buster bomb key
extern float    g_defaultVector[3];    // 0x016db418
extern char     g_szUFOString[];       // 0x015b60ec
extern void*    g_slotMessageVtable[]; // 0x013eb844
extern void*    g_slotMessageBaseVtable[]; // 0x013eb90c
extern uint32_t g_gameModeGalaxy;      // 0x01654c05
extern uint32_t g_ufoMessageKey;       // 0x019d6324
extern float g_kRealZero;           // 0x01485378
void __cdecl FUN_00cd7d10();           // 0x00cd7d10
void __cdecl FUN_00d3d420();           // 0x00d3d420
void __cdecl FUN_00acdff0();           // 0x00acdff0
void __cdecl FUN_00b1e500();           // 0x00b1e500
void __cdecl FUN_00ae7060();           // 0x00ae7060 VecT_clear_cb
void __cdecl FUN_00ae7080();           // 0x00ae7080 CollectSubsystemA
void __cdecl FUN_00b1e520();           // 0x00b1e520
class cSimGameData;
class cCityHall_s00ff_b180;
class tEffectHandle;
class tUFOData;
struct tPtrVector {
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
};
struct tGameDataList {
    void*      mPad00;              // +0x00
    tPtrVector mData;               // +0x04
    void*      mPad0c;              // +0x0c
    void*      mPad10;              // +0x10
};
class cGameNounManager_s00ff_b180 {
public:
    uint8_t mPad00[0x54];           // +0x000
    void*   mpAvatar;               // +0x054

    tGameDataList* GetGameDataVector(void* pF1, void* pF2, void* pF3, void* pF4, void* pAlloc); // 0x00b21340
    void*          GetCurrentTerrainSphere();                                                  // 0x00f67d90
    tUFOData*      CreateNoun(void* pNoun);                                                    // 0x00b20c60
    void*          GetAvatar();                                                                // 0x00b1fdb0
};
cGameNounManager_s00ff_b180* __cdecl NounManager_s00ff_b180();        // 0x00b3d300
class tRefObject {
public:
    virtual void AddRef();                      // +0x00
    virtual void Release();                     // +0x04
};
class cPlanetRecord {
public:
    uint8_t mPad00[0x54];           // +0x000
    void*   mp54;                   // +0x054
    uint8_t mPad58[0xd0];           // +0x058
    float   mf128;                  // +0x128 replacement timer
    float   mf12c;                  // +0x12c ping timer
    uint8_t mPad130[0x0c];          // +0x130
    cPlanetRecord* mp13c;           // +0x13c the owning record
    uint8_t mPad140[0x14];          // +0x140
    int32_t mn154;                  // +0x154
    uint8_t mPad158[0x2c];          // +0x158
    int32_t mn184;                  // +0x184
    uint8_t mPad188[0x0c];          // +0x188
    int32_t mn194;                  // +0x194 noun type

    int32_t        GetNounType();           // 0x00b8dab0
    cPlanetRecord* GetOwnerRecord();        // 0x00b8de30
    void*          GetAvatar();             // 0x00b1fdb0
    cPlanetRecord* FUN_00c71e30();          // 0x00c71e30
    int32_t        FUN_00c70e00();          // 0x00c70e00
    int32_t        FUN_008414c0();          // 0x008414c0
};
cPlanetRecord* __cdecl GetActivePlanet_s00ff_b180();   // 0x01021260
void*          __cdecl GetPlayerEmpire_s00ff_b180();   // 0x01021300
class tCityObj {                    // a polymorphic sub-object embedded in a noun
public:
    virtual void  v00();            // +0x00
    virtual void  v04();            // +0x04
    virtual void  v08();            // +0x08
    virtual void  v0c();            // +0x0c
    virtual void  v10();            // +0x10
    virtual void  v14();            // +0x14
    virtual void  v18();            // +0x18
    virtual void  v1c();            // +0x1c
    virtual void  v20();            // +0x20
    virtual void  v24();            // +0x24
    virtual void  v28();            // +0x28
    virtual void* v2c();            // +0x2c
    virtual void* v30();            // +0x30

    int32_t FUN_008e7f80();         // 0x008e7f80
};
class tCityInner {
public:
    uint8_t  mPad00[0x5fc];         // +0x000
    uint32_t mn5fc;                 // +0x5fc visibility/flag word
};
class cCityHall_s00ff_b180 {
public:
    uint8_t    mPad00[0x120];       // +0x000
    tCityObj   mObj120;             // +0x120
    uint8_t    mPad124[0x38];       // +0x124
    int32_t    mn15c;               // +0x15c owning empire
};
class cSimGameData : public tRefObject {    // vptr +0x00, AddRef +0x00, Release +0x04
public:
    virtual void    v08();          // +0x08
    virtual void    v0c();          // +0x0c
    virtual void    v10();          // +0x10
    virtual void    v14();          // +0x14
    virtual void    v18();          // +0x18
    virtual void    v1c();          // +0x1c
    virtual void    v20();          // +0x20
    virtual void    v24();          // +0x24
    virtual void    v28();          // +0x28
    virtual void    v2c();          // +0x2c
    virtual void    v30();          // +0x30
    virtual void    v34();          // +0x34
    virtual void    v38();          // +0x38
    virtual void    v3c();          // +0x3c
    virtual void    v40();          // +0x40
    virtual void    v44();          // +0x44
    virtual void    v48();          // +0x48
    virtual int32_t v4c();          // +0x4c owning empire

    uint8_t        mPad04[0x30];    // +0x004
    tCityObj       mObj34;          // +0x034
    uint8_t        mPad38[0xe8];    // +0x038
    tCityObj       mObj120;         // +0x120
    uint8_t        mPad124[0xfc];   // +0x124
    float          mf220;           // +0x220
    uint8_t        mPad224[0x48c];  // +0x224
    int32_t        mn6b0;           // +0x6b0
    uint8_t        mPad6b4[0x14];   // +0x6b4
    tCityInner*    mp6c8;           // +0x6c8
    uint8_t        mPad6cc[0x48];   // +0x6cc
    int32_t        mn714;           // +0x714 noun type

    cCityHall_s00ff_b180* GetCityHall();                               // 0x00bd9b40
    bool       FUN_00c38990(int32_t nIndex);                // 0x00c38990
    void       FUN_00c38740(float fA, double fB);           // 0x00c38740
    void       FUN_00bdbf10();                              // 0x00bdbf10
};
class cRelationshipManager {
public:
    void RecordEvent(uint32_t nKey, void* pFrom, void* pTo, float fValue);   // 0x00d06240
};
cRelationshipManager* __cdecl RelationshipManager();    // 0x00b3d2c0
class tEffectHandle {
public:
    virtual void v00();             // +0x00
    virtual void Release();         // +0x04
    virtual void v08(int32_t nValue);   // +0x08
    virtual void v0c(int32_t nValue);   // +0x0c
};
class tEffectsManager {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14();             // +0x14
    virtual void v18();             // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual void v24();             // +0x24
    virtual void v28();             // +0x28
    virtual bool v2c(uint32_t nKey, int32_t nFlags, tEffectHandle** ppEffect);   // +0x2c
};
tEffectsManager* __cdecl EffectsManagerPtr();       // 0x0067ddd0
class cEffects {
public:
    void Tick(float fSeconds);      // 0x00ebe3e0
};
class cSPTimer_s00ff_b180 {
public:
    uint64_t GetElapsedTime();      // 0x00bc3190
    void     Restart();             // 0x00bc3130
    uint32_t mPad00[8];             // +0x00
};
class tMessageServer {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14(uint32_t nKey, void* pPayload, int32_t nFlags);    // +0x14
    virtual void v18(uint32_t nKey, int32_t nA, int32_t nB, int32_t nC); // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual void v24(void* pListener, uint32_t nKey);                   // +0x24
    virtual void v28();             // +0x28
    virtual void v2c();             // +0x2c
    virtual void v30();             // +0x30
    virtual void v34();             // +0x34
    virtual void v38();             // +0x38
    virtual void v3c();             // +0x3c
    virtual void v40();             // +0x40
    virtual void v44();             // +0x44
    virtual void v48();             // +0x48
    virtual void v4c();             // +0x4c
    virtual void v50(void* pListener);  // +0x50
};
tMessageServer* __cdecl MessageServer_s00ff_b180();            // 0x0067dcc0
namespace EA {
namespace Messaging {
 tMessageServer* __cdecl GetServer();   // 0x00883860
}
}
uint32_t        __cdecl GetCurrentGameMode();       // 0x00b5b800
class tBombKey {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14();             // +0x14
    virtual uint32_t* v18();        // +0x18
};
class tSimThing {
public:
    virtual void v00();             // +0x00
    uint8_t   mPad04[0x514];        // +0x004
    tBombKey* mp518;                // +0x518
};
class tHarvestNoun {
public:
    virtual void      v00();                    // +0x00
    virtual tSimThing* v04(uint32_t nKey);      // +0x04
    uint8_t   mPad04[0x0c];         // +0x004
    bool      mb10;                 // +0x010
};
class tUFOData : public tRefObject {        // vptr +0x00
public:
    virtual void  v08();            // +0x08
    virtual void* v0c(uint32_t nSub);   // +0x0c

    void Init(void* pA, void* pB);  // 0x00c3e0b0
};
class cSimInventory {
public:
    tCityObj mObj34;                // +0x034
};
class cUFOSimulator {
public:
    uint8_t        mPad00[0x30];    // +0x000
    cSimInventory* mp30;            // +0x030

    cSimInventory* GetPlayerInventory();    // 0x00a1ad60
};
cUFOSimulator* __cdecl GetUFOSimulator_s00ff_b180();   // 0x00ffbe50
struct tVector3 {
    float x;
    float y;
    float z;
};
class tDOMNode {
public:
    uint8_t  mPad00[0xc0];          // +0x000
    tCityObj mObjC0;                // +0x0c0
};
class tDOMWrapper {
public:
    bool      FUN_00a98020();       // 0x00a98020
    tDOMNode* FUN_00ff0420();       // 0x00ff0420
};
tDOMWrapper* __cdecl FUN_01015df0();    // 0x01015df0
struct tStringKey {
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    void* mpCapacity;                   // +0x08
};
class tAppCom {
public:
    virtual void  v00();            // +0x00
    virtual void  v04();            // +0x04
    virtual void  v08();            // +0x08
    virtual void  v0c();            // +0x0c
    virtual void  v10();            // +0x10
    virtual void  v14();            // +0x14
    virtual void  v18();            // +0x18
    virtual void* v1c();            // +0x1c
};
class tApp {
public:
    virtual void    v00();          // +0x00
    virtual void    v04();          // +0x04
    virtual void    v08();          // +0x08
    virtual void    v0c();          // +0x0c
    virtual void    v10();          // +0x10
    virtual void    v14();          // +0x14
    virtual void    v18();          // +0x18
    virtual void    v1c();          // +0x1c
    virtual void    v20();          // +0x20
    virtual void    v24();          // +0x24
    virtual void    v28();          // +0x28
    virtual void    v2c();          // +0x2c
    virtual void    v30();          // +0x30
    virtual void    v34();          // +0x34
    virtual void    v38();          // +0x38
    virtual void    v3c();          // +0x3c
    virtual void    v40();          // +0x40
    virtual void    v44();          // +0x44
    virtual void    v48();          // +0x48
    virtual void    v4c();          // +0x4c
    virtual tAppCom* v50();         // +0x50
};
tApp* __cdecl App();                // 0x0067dd10
tVector3* __cdecl FUN_0095df60(void* pString, void* pKey, uint32_t nValue);  // 0x0095df60
tVector3* __cdecl FUN_0059aed0(void* pString, void* pKey, uint32_t nValue);  // 0x0059aed0
struct tSlotMessage {
    void*      mpVtable;            // +0x00
    uint32_t   mnRefCount;          // +0x04
    tVector3*  mpPosition;          // +0x08
    uint32_t   mn0c;                // +0x0c
    tVector3*  mpSize;              // +0x10
    uint32_t   mPad14[0x07];        // +0x14
    uint32_t   mnKey;               // +0x30
    uint32_t   mn34;                // +0x34
    uint32_t   mn38;                // +0x38

    void Destruct();                // 0x00421cf0
};
class cTerrainSphere {
public:
    void FUN_00c77bf0(uint32_t nKey);   // 0x00c77bf0
    bool Check();                       // 0x00c75650
};
class tPlanetGate {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14();             // +0x14
    virtual void v18();             // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual void v24();             // +0x24
    virtual void v28();             // +0x28
    virtual void v2c();             // +0x2c
    virtual void v30();             // +0x30
    virtual void v34();             // +0x34
    virtual void v38();             // +0x38
    virtual void v3c();             // +0x3c
    virtual void v40();             // +0x40
    virtual void v44();             // +0x44
    virtual void v48();             // +0x48
    virtual void v4c();             // +0x4c
    virtual bool v50();             // +0x50
};
class cPlanetModel_s00ff_b180 {
public:
    uint8_t      mPad00[0x24];      // +0x000
    tPlanetGate* mp24;              // +0x024 planet gate object

    float GetWaterHeight();                                         // 0x00b7e390
    tVector3* DirectionToSurfacePosition(tVector3* pOut, void* pID); // 0x00b815a0
};
cPlanetModel_s00ff_b180* __cdecl PlanetModel_s00ff_b180();    // 0x00b3d350
class tRenderConsumer {
public:
    virtual void v00();                             // +0x00
    virtual void v04();                             // +0x04
    virtual void v08();                             // +0x08
    virtual void v0c();                             // +0x0c
    virtual void v10(uint32_t nTimeLo, uint32_t nTimeHi, void* pValue);   // +0x10
};
class cSPSimPlanetHighLOD_s00ff_b180 {
public:
    uint8_t      mPad00[0x28];      // +0x000
    tRenderConsumer* mp28;          // +0x028 render consumer (v10)
    void*        mp2c;              // +0x02c drawn UFO / message-server handle
    void*        mp30;              // +0x030 message listener
    void*        mp34;              // +0x034 listener vtable
    int32_t      mn38;              // +0x038
    int32_t      mn3c;              // +0x03c
    tUFOData*    mp40;              // +0x040 UFO game data
    uint8_t      mPad44[0x3c];      // +0x044
    cSPTimer_s00ff_b180     mTimer80;          // +0x080
    int32_t      mnA0;              // +0x0a0
    uint8_t      mPadA4[0xb4];      // +0x0a4
    bool         mb158;             // +0x158
    uint8_t      mPad159[0x57];     // +0x159
    cEffects*    mp1b0;             // +0x1b0
    uint8_t      mPad1b4[0x04];     // +0x1b4
    int32_t      mn1b8;             // +0x1b8 threshold
    tEffectHandle* mp1bc;           // +0x1bc terrain effect
    uint8_t      mPad1c0[0x1c];     // +0x1c0
    tEffectHandle* mp1dc;           // +0x1dc
    bool         mb1e0;             // +0x1e0

    void FUN_00ffb180();                                            // 0x00ffb180
    void SolarSystemUpdateNPC_UFOs(uint32_t nElapsedMS);            // 0x00ffb270
    void CheckForCityDestruction();                                 // 0x00ffb830
    void OnTick(uint32_t nTimeLo, uint32_t nTimeHi);                // 0x00ffbb20
    void Init();                                                    // 0x00ffbf60
    bool FUN_00ffbfe0();                                            // 0x00ffbfe0
    void FUN_00ffc030();                                            // 0x00ffc030
    bool CheckAndReplaceData(void* pKey, void* pB, void* pC);       // 0x00ffc160
    void CreateReplacement();                                       // 0x00ffa780
    void FUN_00ff8ad0();                                            // 0x00ff8ad0
    void FUN_00ffabc0();                                            // 0x00ffabc0
    void FUN_00ffaf20(uint32_t nTimeLo);                            // 0x00ffaf20
    void FUN_00ffa690();                                            // 0x00ffa690
    void FUN_00ffab60();                                            // 0x00ffab60
    void FUN_00ff7530(uint32_t nTimeLo, uint32_t nTimeHi);          // 0x00ff7530
    void FUN_00ffa900(cSimGameData* pNoun, int32_t nEmpire);        // 0x00ffa900
};
class tCityVector {
public:
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
    void** mpCapacity;              // +0x08

    tCityVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(void** pEnd, void* const& pValue);   // 0x00aea5d0
    void DoDestroy();                                       // 0x00ae6970
};
// ---- items of slice s00ffb180 end

// ---- items of slice s00ff6a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
extern "C" void __cdecl operator_delete_arr(void* p);              // 0x00f47380 (operator delete[])
#pragma intrinsic(_InterlockedExchange)
typedef unsigned short char16;
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
extern const char16 gEmptyString16[1];                              // 0x01667bac
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    bool operator==(const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }
    bool operator!=(const Vector3& v) const { return x != v.x || y != v.y || z != v.z; }
};
extern const Vector3 kZeroVector;                                  // 0x016db418
struct Quaternion { float x, y, z, w; };
struct ResourceKey_s00ff_6a50 { uint32_t instanceID, typeID, groupID; };
extern const ResourceKey_s00ff_6a50 kPlayerColorKey;                          // 0x01572b54
struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t mAllocator;
    string16() {
        mpBegin = mpEnd = (char16*)gEmptyString16;
        mpCapacity = mpBegin + 1;
    }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_arr(mpBegin);
        }
    }
    bool empty() const { return mpBegin == mpEnd; }
    const char16* c_str() const { return mpBegin; }
    void assign(const char16* pBegin, const char16* pEnd);         // 0x00423650
    static unsigned int CharStrlen(const char16* p) {
        const char16* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        return (unsigned int)(pCurrent - p);
    }
    string16& operator=(const string16& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    string16& operator=(const char16* p) {
        assign(p, p + CharStrlen(p));
        return *this;
    }
};
template <typename T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    bool empty() const { return mpBegin == mpEnd; }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return mpBegin[n]; }
    const T& operator[](unsigned int n) const { return mpBegin[n]; }
};
template <typename T> inline const T& min_ref(const T& a, const T& b) { return (b < a) ? b : a; }
struct cBuildingData {                   // 0x38
    Vector3 mPosition;                   // +00
    Quaternion mOrientation;             // +0c
    float mHealthPoints;                 // +1c
    int mDamageState;                    // +20
    bool mConnected;                     // +24
    bool mbUnk25;                        // +25
    uint16_t pad26;
    int mEffectiveness;                  // +28
    int mFreezeCount;                    // +2c
    int mSlot;                           // +30
    uint32_t mClassId;                   // +34
};
struct cOrnamentData {                   // 0x34
    Vector3 mPosition;                   // +00
    Quaternion mOrientation;             // +0c
    float mHealthPoints;                 // +1c
    int mDamageState;                    // +20
    ResourceKey_s00ff_6a50 mModelKey;               // +24
    uint32_t mClassId;                   // +30
};
struct cVehicleData {                    // 0x14
    Vector3 mPosition;                   // +00
    int mLocomotion;                     // +0c
    int mPurpose;                        // +10
    const Vector3& GetPosition();        // 0x00572590
    int GetLocomotion();                 // 0x00fc7e50
    int GetPurpose();                    // 0x007f54d0
};
struct cCityData {
    uint32_t pad00[0x30 / 4];
    float mSpiceProduction;              // +30
    int mSize;                           // +34
    uint32_t pad38[(0x7c - 0x38) / 4];
    sp_vector<cBuildingData> mBuildings; // +7c
    sp_vector<cOrnamentData> mOrnaments; // +90
    uint32_t padA4[(0xb8 - 0xa4) / 4];
    int mLayout;                         // +b8
    int mFieldBC;                        // +bc
    int mFieldC0;                        // +c0

    const Vector3& GetPosition();        // 0x00572590
    const string16& GetName();           // 0x00ff0390
    const uint32_t& GetBuildingLinks();  // 0x00ff03a0
    int GetMaxSize();                    // 0x00ff35d0
    void SetMaxSize(int n);              // 0x009879d0
    float GetHappiness();                // 0x00b7e0a0
    int GetIncome();                     // 0x00a1ad10
    const Quaternion& GetOrientation();  // 0x008dc790
    uint8_t GetTurretLocations();        // 0x00ffc0c0
    void RestoreWalls(struct cCity_s00ff_6a50* city, int planetType);      // 0x00ff2810
    void RestoreCityWalls(int size, int planetType);            // 0x00ff1da0
};
struct cCivData {
    sp_vector<ResourceKey_s00ff_6a50> mModelKeys;   // +00
    int GetPoliticalID();                // 0x00ff0420
    int GetColorID();                    // 0x006c0200
    float GetWealth();                   // 0x00fd9410
    const sp_vector<cVehicleData*>& GetVehicles();  // 0x00830a50
    const sp_vector<cCityData*>& GetCities();       // 0x005c65e0
    const ResourceKey_s00ff_6a50& GetResourceKey(const cBuildingData* data);  // 0x00ff0cd0
    void LoadModelKeys(void* dst);       // 0x00ff3540
    void DefaultModelKeys(void* dst);    // 0x00ff3190
};
class cSpatial {
public:
virtual void _v00();
virtual void _v04();
    virtual void SetOwner(uint32_t v);                       // 08
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
    virtual int GetModelID();                                // 2c
virtual void _v30();
virtual void _v34();
    virtual void SetPosition(const Vector3& v);              // 38
    virtual void SetOrientation(const Quaternion& q);        // 3c
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
virtual void _v50();
virtual void _v54();
virtual void _v58();
virtual void _v5c();
virtual void _v60();
virtual void _v64();
virtual void _v68();
virtual void _v6c();
virtual void _v70();
virtual void _v74();
virtual void _v78();
virtual void _v7c();
virtual void _v80();
virtual void _v84();
virtual void _v88();
virtual void _v8c();
    virtual void _v90();
    virtual void SetModelKey(const ResourceKey_s00ff_6a50& key);        // 94
};
class cGameData {
public:
    virtual int AddRef();                                    // 00
    virtual int Release();                                   // 04
    virtual void _v08();
    virtual void* Cast(uint32_t typeID);                     // 0c
};
struct cCombatant {
    void SetHealthPoints(float hp);      // 0x00f924e0
    void SetDamageState(int state);      // 0x00bfc460
};
template <typename T> inline T* object_cast(cGameData* p, uint32_t typeID)
{
    return p ? (T*)p->Cast(typeID) : 0;
}
struct cSPTimer_s00ff_6a50 { void Restart(); };     // 0x00bc3130
struct cCity_s00ff_6a50;
class cBuilding {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
    virtual void _v50();
    virtual void SetCity(cCity_s00ff_6a50* city);                       // 54
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatial mSpatial;                                       // +34
    uint32_t pad38[(0x120 - 0x38) / 4];
    cCombatant mCombatant;                                   // +120
    uint32_t pad124[(0x258 - 0x124) / 4];
    cSPTimer_s00ff_6a50 mTimer;                                         // +258
    uint32_t pad25C[(0x28c - 0x25c) / 4];
    int mEffectiveness;                                      // +28c

    void SetConnected(bool b);           // 0x00bcc6e0
    void SetUnk25(bool b);               // 0x00bcd550
    void SetFreezeCount(int n);          // 0x00bcc760
};
class cOrnament {
public:
    virtual void _v00();
    uint32_t pad04[(0x70 - 4) / 4];
    cSpatial mSpatial;                                       // +70
    void SetModel(uint32_t groupID, uint32_t politicalID, uint32_t instanceID);  // 0x00c6f770
};
struct cBuildingNet {
    void AddBuilding(cBuilding* b);      // 0x00afa030
};
struct cCityGrid {
    cBuildingNet* GetNet(int modelID);   // 0x00afad70
};
struct cCityState {
    uint32_t pad[0x350 / 4];
    bool mbRestored;                     // +350
    void SetActive(int b);               // 0x00becd70
};
struct cCity_s00ff_6a50 {
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
    virtual void SetPoliticalID(int id);                     // 48
virtual void _v4c();
virtual void _v50();
virtual void _v54();
virtual void _v58();
virtual void _v5c();
virtual void _v60();
virtual void _v64();
virtual void _v68();
    virtual cCityState* GetState();                          // 6c
virtual void _v70();
virtual void _v74();
virtual void _v78();
virtual void _v7c();
virtual void _v80();
virtual void _v84();
virtual void _v88();
    virtual void SetIsPlayer(bool b);                        // 8c
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatial mOwner;                                         // +34
    uint32_t pad38[(0x120 - 0x38) / 4];
    cSpatial mSpatial;                                       // +120
    uint32_t pad124[(0x2e8 - 0x124) / 4];
    int mField2E8;                                           // +2e8
    int mField2EC;                                           // +2ec
    uint32_t pad2F0[(0x304 - 0x2f0) / 4];
    float mSpiceProduction;                                  // +304

    void SetCityData(cCityData* data);   // 0x00bd81e0
    void SetSize(int size, int b);       // 0x00be73d0
    void SetIncome(int income, float happiness);             // 0x00bd7d10
    int GetMaxSize();                    // 0x00bd8110
    void Layout(const Vector3* pos, float wealth, int turrets, int buildings, bool isPlayer, int a,
                int layout, int b, int c, int d);            // 0x00be8680
    void Initialize(int layout, int a, int b, int c);        // 0x00be7bf0
    void SetUnk(int a);                  // 0x00be32f0
    cBuilding* GetCityHall();            // 0x00bd9b40
    void AddBuilding(cBuilding* b, int a);                   // 0x00be1ef0
    cCityGrid* GetGrid();                // 0x00bd7f40
    void AddOrnament(cOrnament* o);      // 0x00be1e80
    void UpdateBuildings();              // 0x00bdbbb0
    void AddTurret(int slot);            // 0x00be3990
    void SetUnk2(int a);                 // 0x00c01e20
};
class cVehicle {
public:
    virtual int AddRef();                                    // 00
    virtual int Release();                                   // 04
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatial mSpatial;                                       // +34
    uint32_t pad38[(0x5d0 - 0x38) / 4];
    uint32_t mBehavior;                                      // +5d0

    void Init(int locomotion, int purpose, ResourceKey_s00ff_6a50 key);  // 0x00ca6630
    void SetVehicleData(cVehicleData* data);                 // 0x00a110b0
    void SetCivData(cCivData* data);                         // 0x00c9eae0
    void SetJustEyeCandy(bool b);                            // 0x00c9ecb0
};
struct cTextHolder { void SetText(const string16& s); };     // 0x00b6f380
struct cCivilization_s00ff_6a50 {
    uint32_t pad00[0x3c / 4];
    cTextHolder mName;                   // +3c
    int mField40;                        // +40
    uint32_t pad44[(0x6c - 0x44) / 4];
    uint32_t mModelKeys;                 // +6c
    uint32_t pad70[(0x98 - 0x70) / 4];
    float mWealth;                       // +98

    void Init(int politicalID, bool isPlayer, int colorID, int a);  // 0x00bf8170
    void SetWealth(float w, int a);      // 0x00befd80
    void SetColor(const ResourceKey_s00ff_6a50* key);                   // 0x00bef8f0
    void SetTribeData(void* data);       // 0x00bebdd0
    void AddCity(cCity_s00ff_6a50* city);           // 0x00bf4370
    const sp_vector<cCity_s00ff_6a50*>* GetCities();  // 0x00bef6c0
    void AddVehicle(cVehicle* v);        // 0x00bf5630
    const ResourceKey_s00ff_6a50& GetModelTypeKey(uint32_t id);         // 0x00bf9770
};
struct cGameNounManager_s00ff_6a50 {
    cCivilization_s00ff_6a50* GetCivilization(int politicalID);         // 0x00b25f40
    cGameData* CreateNoun(uint32_t classID);                 // 0x00b20c60
    cGameData* Func_00b25c30();                              // 0x00b25c30 (the requested class's noun)
};
struct cSpeciesProfile { void GetUiName(string16& name); };  // 0x004da330
struct cTribeInfo { uint32_t pad[4]; int mID; };
struct cPlanet {
    uint32_t pad00[0x13c / 4];
    int mType;                           // +13c
    cTribeInfo* GetTribe();              // 0x00c71e30
    cSpeciesProfile* GetSpecies();       // 0x00c70860
    int GetTechLevel();                  // 0x00c70e00
};
struct cStarManager { int GetPlayerPoliticalID(); };         // 0x00885c90
struct cPlanetModel_s00ff_6a50 { Vector3 DirectionToSurfacePosition(const Vector3& dir); };  // 0x00b815a0
struct cLocaleManager { string16 GetText(uint32_t id); };   // 0x005ecf80
class IMessageServer {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
    virtual void PostMessage(uint32_t messageID, void* msg, int a, int b);  // 18
};
class IBehaviorManager {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
    virtual void Register(uint32_t* behavior);               // 38
};
cGameNounManager_s00ff_6a50* NounManager_s00ff_6a50();                             // 0x00b3d300
cStarManager* StarManager_s00ff_6a50();                                 // 0x00b3d2a0
cPlanetModel_s00ff_6a50* PlanetModel_s00ff_6a50();                                 // 0x00b3d350
IMessageServer* MessageServer();                             // 0x0067dcc0
IBehaviorManager* BehaviorManager();                         // 0x00b3d260
int GetPlayerEmpireID();                                     // 0x01021090
cPlanet* GetActivePlanet_s00ff_6a50();                                  // 0x01021260
cLocaleManager* LocaleManager();                             // 0x004010a0
const ResourceKey_s00ff_6a50* GetColorKey(int colorID);                 // 0x00b6f0c0
cCity_s00ff_6a50* CreateCity(const Vector3* pos, const char16* name);   // 0x00bd9d70
void GetCityLimits(int maxSize, int* a, int* b, int* c, int* d, int* e);  // 0x00ff5330
int GetTurretCount(int maxSize);                             // 0x00ff53f0
class cBehaviorMessage {
public:
    virtual void _v00();
    volatile long mnRefCount;            // +04
    cBehaviorMessage() { _InterlockedExchange(&mnRefCount, 0); }
};
struct cMessageHeader {
    void* mpData0;                       // +08
    uint32_t pad0C;
    void* mpData1;                       // +10
    uint32_t pad14;
    void* mpData2;                       // +18
    uint32_t pad1C[5];
    uint32_t mMessageID;                 // +30
    uint32_t field_34;
    cMessageHeader(uint32_t id) : mMessageID(id) {}
};
class cSimMessage : public cMessageHeader, public cBehaviorMessage {
public:
    void* mpExtra;                       // +38
    uint32_t field_3C;
    cSimMessage() : cMessageHeader(0), mpExtra(0) {}
    virtual void _v00();
};
struct cPlanetSimHost {
    void LoadCivilization(cCivData* civ, cPlanetSimHost* host);
    uint32_t pad[0x504 / 4];
    uint32_t mTribeData;                 // +504
};
class Screen {
public:
    void setModal(bool modal);           // 0x00ad7e40 (ret 4)
};
Screen* GetTriggerMgr();                 // 0x00b3d4d0
class cSpaceGameHudHost {
public:
    void Func_01066d60();                // 0x01066d60
};
cSpaceGameHudHost* FUN_010666a0_s00ff_6a50();       // 0x010666a0
class cSPSimPlanetHighLOD_s00ff_6a50 {              // holds the celebrated noun at +0x30
public:
    void StartUFOCelebration(cGameData* target);   // 0x00ff65f0 (ret 4)
    void Func_00ff74f0();                          // 0x00ff74f0
};
// ---- items of slice s00ff6a50 end

// @ 0x00ff5930
int __cdecl FUN_00ff5930(void* param_1)
{
    CB8de30* nounMgr = (CB8de30*)((CB8de30*)param_1)->GetNounManager();
    if (((CC8b560*)FUN_01021230())->IsSomething() == 0) {
        if (((CB8dab0*)param_1)->GetType() == 5) {
            CAvatar* avatarMgr = (CAvatar*)nounMgr;
            if (avatarMgr->GetAvatar() != (void*)FUN_01021090()) {
                void* starMgr = FUN_00b3d2a0(avatarMgr->GetAvatar());
                void* empire = ((CStarManager*)starMgr)->GetEmpireByID();
                void* starMgr2 = FUN_00b3d2a0(empire);
                void* ufo = ((CStarManager*)starMgr2)->FUN_00baf700();

                if (FUN_00c6fe50(param_1) != 0)
                    return FUN_0102b010(ufo, ((char*)0x067b69e3), ((char*)0x067b69f1));

                CTerraforming* terra = (CTerraforming*)FUN_00b3d430(param_1);
                if (terra->IsEnabled() != 0)
                    return FUN_0102b010(ufo, ((char*)0x067b69d8), ((char*)0x067b69eb));

                return FUN_0102b010(ufo, ((char*)0x067b69c4), ((char*)0x067b69d0));
            }
        }
    }
    return 0;
}

// @ 0x00ff5a90
bool __thiscall cSPSimPlanetHighLOD::Write(IStream* s)
{
    void* stream = StreamWriter(s);
    uint32_t id = 0xf04d0722;
    void* value = WriterValue(stream);
    EA_IO_WriteUint32(value, &id, 1, 0);

    char ok = WriteBase(s);
    cVarListSerializer ser((char*)this - 8, &g_15b6160, 0x1a80d26);
    if (ok && ser.Serialize(s))
        return true;
    return false;
}

// @ 0x00ff5b30
void __stdcall FUN_00ff5b30(void* param_1)
{
    CGetter10666a0B* g = (CGetter10666a0B*)FUN_010666a0_s00ff_4d50();
    FUN_00ce8f70(param_1, g->FUN_01067e60());
}

// @ 0x00ff5b50
void __cdecl FUN_00ff5b50()
{
    CCityVisualizer* v = (CCityVisualizer*)FUN_00b3d480_0();
    v->setActiveVignette(g_1654c05);
}

// @ 0x00ff5ba0
void __cdecl FUN_00ff5ba0(int* param_1, int* param_2)
{
    int* it = param_1;
    if (param_1 != param_2) {
        while (it = it + 1, it != param_2) {
            int v = *it;
            int* p;
            for (p = it; p != param_1 && v < p[-1]; p = p - 1)
                *p = p[-1];
            *p = v;
        }
    }
}

// @ 0x00ff5be0
void __cdecl FUN_00ff5be0(int* param_1, int* param_2)
{
    for (int* it = param_1; it != param_2; it = it + 1) {
        int v = *it;
        int* p = it;
        int prev = p[-1];
        while (v < prev) {
            *p = prev;
            p = p - 1;
            prev = p[-1];
        }
        *p = v;
    }
}

// @ 0x00ff5c50
char __thiscall cSPSimPlanetHighLOD::Read(IStream* s)
{
    int id;
    void* stream = StreamWriter(s);
    void* value = WriterValue(stream);
    EA_IO_ReadInt32(value, &id, 1, 0);

    char ok = ReadBase(s);
    cVarListSerializer ser((char*)this - 8, &g_15b6160, 0x1a80d26);
    char res;
    if (ok != 0 && ser.SerializeRead(s) != 0)
        res = 1;
    else
        res = 0;

    cColonySimulator* sim = (cColonySimulator*)operator_new(0x28, g_13f09b4, 0, 0, 0, 0);
    if (sim != 0)
        sim = sim->ctor();

    void* old = mp20;
    if (sim != old) {
        if (sim != 0)
            ((cRefCounted*)sim)->AddRef();
        mp20 = sim;
        if (old != 0)
            ((cRefCounted*)old)->Release();
    }
    return res;
}

// @ 0x00ff5d20
cSPPlanetaryArtifact* cSPSimPlanetHighLOD_s00ff_5d20::SpawnArtifact(cArtifactParams* pm)
{
    cPlanetModel* mdl = FUN_00b3d350();
    RefObj* noun = (RefObj*)FUN_00b3d300()->CreateNoun((void*)0x2dd8c42);
    if (noun == 0)
        return 0;
    cSPPlanetaryArtifact* art = (cSPPlanetaryArtifact*)noun->v0c((void*)0x2dd8c33);
    if (art != 0) {
        ResourceKey key;
        key.k0 = pm->k0;
        key.k1 = 0;
        key.k2 = 0;
        art->Set(pm->b12, &key, pm->w10, (pm->flags28 >> 1) & 1);
        art->m640 = pm->v18;
        Vec3 v = { g_f16db418, g_f16db41c, g_f16db420 };
        if (pm->x4 == g_f16db418 && pm->y8 == g_f16db41c && pm->z_c == g_f16db420) {
            for (u32 i = 0; i < 100; i++) {
                Vec3* p = (Vec3*)mdl->FUN_00b81720(&key);
                v = *p;
                if (mdl->FUN_00b7e3e0(&v))
                    continue;
                if (!mdl->FUN_00b83870(&v))
                    break;
            }
        } else {
            v.x = pm->x4;
            v.y = pm->y8;
            v.z = pm->z_c;
        }
        pm->x4  = v.x;
        pm->y8  = v.y;
        pm->z_c = v.z;
        cHallSub* sub = (cHallSub*)((char*)art + 0x34);
        sub->v38(&v);
        void* ori = mdl->FUN_00b7f190(&key, sub->v2c());
        sub->v3c(ori);
        if (mdl->FUN_00b7e3e0((Vec3*)sub->v2c()))
            art->m224 = 6;
        art->m65e = (pm->flags28 >> 5) & 1;
    }
    return art;
}

// @ 0x00ff5ee0
void cSPSimPlanetHighLOD_s00ff_5d20::StartCVG2SPG(u32 param2, u8 flag)
{
    cCity* city = FUN_00b3d300()->FUN_00b25c30();
    if (city == 0)
        return;
    if (city != mpCity) {
        ((RefObj*)city)->v00();
        cCity* old = mpCity;
        mpCity = city;
        if (old)
            ((RefObj*)old)->v04();
    }
    cPlayerInventory* inv =
        ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    cCityHall* hall = mpCity->GetCityHall();
    if (inv != 0 && hall != 0) {
        cHallSub* sub = (cHallSub*)((char*)hall + 0x34);
        void* r = sub->vac();
        f32 f = sub->v34() * *(f32*)((char*)r + 0x84);
        Vec3 tmp;
        Vec3* n = Swarm_Normalize(&tmp, sub->v2c());
        Vec3* c = (Vec3*)sub->v2c();
        Vec3 off;
        off.x = c->x + n->x * f;
        off.y = c->y + n->y * f;
        off.z = c->z + n->z * f;
        inv->FUN_00c3aa40(&off, sub->v30());
        inv->FUN_00c3daa0(sqrtf(off.x * off.x + off.y * off.y + off.z * off.z) + g_f1486110);
    }
    m1e4.FUN_007d01d0(0x9c377c26, 0);
    u32 h1 = FUN_00932e80("cinematics_spg", 0x811c9dc5, 1);
    u32 h2 = FUN_00932e80("UFOCreateText", 0x811c9dc5, 1);
    TriggerCtx ctx;
    ctx.a = param2;
    ctx.b = 0;
    ctx.c = h1;
    FUN_00b3d4d0()->FUN_00adde90(h2, &ctx, 0);
    if (flag != 0)
        FUN_00b3d4d0()->PostTrigger("CVG2SPG", 1, 0, 0, 0, 0);
    else
        FUN_00b3d4d0()->PostTrigger("CVG2SPG_short", 1, 0, 0, 0, 0);
}

// @ 0x00ff60d0
void cSPSimPlanetHighLOD_s00ff_5d20::ShowUFOForTransition()
{
    cPlayerInventory* inv =
        ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    if (inv == 0)
        return;
    cCity* city = FUN_00b3d300()->FUN_00b25c30();
    cCityHall* hall = city ? city->GetCityHall() : 0;
    Vec3 v;
    u32  unk;
    city->FUN_00bd7f70(&v, &unk);
    inv->m624 = 1;
    cHallSub* sub = (cHallSub*)((char*)hall + 0x34);
    inv->FUN_00c3aa40(&v, sub->v30());
    inv->FUN_00c3daa0(sqrtf(v.z * v.z + v.x * v.x + v.y * v.y) + g_f1494fb8);
    inv->FUN_00c37130(1);
    f32 c = g_f13ec480;
    inv->m6b4 = c;
    inv->m6b8 = c;
}

// @ 0x00ff6190
void cSPSimPlanetHighLOD_s00ff_5d20::FUN_00ff6190()
{
    FUN_010666a0()->FUN_01066dd0();
    if (mpCity) {
        cCivilization* civ = mpCity->GetCivilization();
        if (civ) {
            cGovernment* gov = civ->FUN_00bef8e0();
            if (gov)
                gov->FUN_01062e60(0);
        }
    }
    cPlayerInventory* inv = ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    if (inv)
        inv->FUN_00c37130(1);
    if (mpCity) {
        cCity* p = mpCity;
        mpCity = 0;
        p->v04();
    }
}

// @ 0x00ff6200
void cSPSimPlanetHighLOD_s00ff_5d20::FUN_00ff6200()
{
    void* active = FUN_010212a0();
    cPlayerInventory* inv = 0;
    if (active == FUN_01021370()) {
        inv = ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
        FUN_010666a0()->FUN_01066dd0();
    }
    FUN_00b3d4d0()->setModal(0);
    if (inv) {
        inv->FUN_00c37130(1);
        if (mpCity) {
            cCivilization* civ = mpCity->GetCivilization();
            if (civ) {
                cGovernment* gov = civ->FUN_00bef8e0();
                if (gov) {
                    cHallSub2* sub = (cHallSub2*)((char*)inv + 0x34);
                    gov->FUN_01062e70(5, sub->v2c(g_f13eb1bc));
                }
            }
        }
    }
}

// @ 0x00ff6290
void cSPSimPlanetHighLOD_s00ff_5d20::FUN_00ff6290()
{
    if (mpCity) {
        cCivilization* civ = mpCity->GetCivilization();
        if (civ) {
            cGovernment* gov = civ->FUN_00bef8e0();
            if (gov)
                gov->FUN_01062e60(0);
        }
    }
    if (mpCity) {
        cCity* p = mpCity;
        mpCity = 0;
        p->v04();
    }
}

// @ 0x00ff62d0
void cSPSimPlanetHighLOD_s00ff_5d20::FUN_00ff62d0()
{
    if (mp18) {
        mp18->v0c((void*)1);
        if (mp18) {
            cVisualEffect* p = mp18;
            mp18 = 0;
            p->v04();
        }
    }
    if (mp1c) {
        mp1c->v0c((void*)1);
        if (mp1c) {
            cVisualEffect* p = mp1c;
            mp1c = 0;
            p->v04();
        }
    }
    FUN_00b3d4d0()->setModal(0);
    cPlayerInventory* inv = ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    if (inv)
        inv->FUN_00c37130(1);
    FUN_010666a0()->FUN_01066dd0();
}

// @ 0x00ff6380
void __cdecl FUN_00ff6380()
{
    cPlanetModel*  pm  = FUN_00b3d350();
    cZooMarkerMgr* mgr = (cZooMarkerMgr*)FUN_010212a0();
    for (ResourceKey* it = mgr->mBegin; it != mgr->mEnd; ++it) {
        Vec3 pt;
        pm->GetRandomSurfacePoint(&pt);
        SetZooMarker(mgr, it, &pt, 0);
    }
}

// @ 0x00ff63e0
void __cdecl FUN_00ff63e0()
{
    FUN_00b3d350();
    cZooMarkerMgr* mgr = (cZooMarkerMgr*)FUN_010212a0();
    for (ResourceKey* it = mgr->mBegin; it != mgr->mEnd; ++it)
        FUN_01043c60(mgr, it);
    mgr->mFlags2c &= 0xfffff7ff;
    FUN_0067dcc0()->v18(0x490d429, 0, 0, 0);
    FUN_00b3d430()->FUN_00bbf2b0(0);
}

// @ 0x00ff6450
void cSPSimPlanetHighLOD_s00ff_5d20::FUN_00ff6450(Vec3* v)
{
    m158 = 1;
    m15c = *v;
    mTimer170.Restart();
    m168 = FUN_00b3d430()->FUN_00bbc670(0);
    m198 = 0.0f;
    m194 = 0.0f;
    m190 = 0.0f;
    void* y = FUN_01021260()->FUN_008414c0();
    if (y != 0)
        ((cActivePlanet*)y)->FUN_00c7e2f0(0);
    cMissionList* list = FUN_00feb9f0()->GetMissionList();
    for (void** it = list->mBegin; it != list->mEnd; ++it) {
        cSPMission* m = (cSPMission*)*it;
        if (m->GetMissionID() == 0x311cc10f) {
            if ((void*)m->GetTargetPlanet() == (void*)FUN_01021260())
                m->FUN_00c485e0();
        }
    }
}

// @ 0x00ff6520
void cSPSimPlanetHighLOD_s00ff_5d20::FUN_00ff6520(void* obj, f32 x)
{
    void* p = obj ? (void*)((char*)obj + 0x508) : 0;
    mp1b0->FUN_00ebdc20(p, x);
}

// @ 0x00ff6570
void __cdecl FUN_00ff6570(int* a, int lo, int n, int i, int v)
{
    int j = i * 2 + 2;
    int c;
    while (j < n) {
        c = a[j];
        if (c < a[j - 1])
            c = a[--j];
        a[i] = c;
        i = j;
        j = j * 2 + 2;
    }
    if (j == n) {
        a[i] = a[j - 1];
        i = j - 1;
    }
    while (i > lo) {
        int p = (i - 1) >> 1;
        c = a[p];
        if (c >= v)
            break;
        a[i] = c;
        i = p;
    }
    a[i] = v;
}

// @ 0x00ff65f0
void cSPSimPlanetHighLOD_s00ff_5d20::StartUFOCelebration(cCity* param)
{
    if (param == 0)
        return;
    if (param != mpCity) {
        ((RefObj*)param)->v00();
        cCity* old = mpCity;
        mpCity = param;
        if (old)
            ((RefObj*)old)->v04();
    }
    if (mp18) {
        mp18->v0c((void*)1);
        if (mp18) {
            cVisualEffect* p = mp18;
            mp18 = 0;
            p->v04();
        }
    }
    if (mp1c) {
        mp1c->v0c((void*)1);
        if (mp1c) {
            cVisualEffect* p = mp1c;
            mp1c = 0;
            p->v04();
        }
    }
    void* home = FUN_01021370();
    cPlayerInventory* inv = 0;
    if (FUN_010212a0() == home)
        inv = ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    cCityHall* hall = mpCity->GetCityHall();
    if (inv != 0 && hall != 0) {
        cHallSub* sub = (cHallSub*)((char*)hall + 0x34);
        void* r = sub->vac();
        f32 f = sub->v34() * *(f32*)((char*)r + 0x84);
        Vec3 tmp;
        Vec3* n = Swarm_Normalize(&tmp, sub->v2c());
        f32 sx = n->x * f;
        f32 sy = n->y * f;
        f32 sz = n->z * f;
        Vec3* c = (Vec3*)sub->v2c();
        Vec3 off;
        off.x = c->x + sx;
        off.y = c->y + sy;
        off.z = c->z + sz;
        inv->FUN_00c3aa40(&off, sub->v30());
        inv->FUN_00c3daa0(sqrtf(off.x * off.x + off.y * off.y + off.z * off.z) + g_f1486110);
    }
    cEffectsManager* em = FUN_0067ddd0();
    if (mp18) {
        cVisualEffect* p = mp18;
        mp18 = 0;
        p->v04();
    }
    if (em->v2c(0x60713c20, 0, &mp18)) {
        cCityHall* hall2 = mpCity->GetCityHall();
        if (hall2 != 0) {
            cHallSub* sub = (cHallSub*)((char*)hall2 + 0x34);
            XformMsg m1;
            m1.ctor();
            m1.mPos = *(Vec3*)sub->v2c();
            m1.mFlags |= 4;
            m1.mSequence++;
            Mat3 rot;
            Matrix3FromQuaternion(rot.m, sub->v30());
            m1.mMat = rot;
            m1.mFlags |= 2;
            m1.mSequence++;
            m1.mPos.x = 1.0f;                  // re-uses the +0x04 slot as the scale tag
            ((cInvInner*)inv)->v40(9, ((cSub2cU*)((char*)inv + 0x34))->v2c(1));
            mp18->v44(10, &m1, 1);
            mp18->v18(&m1);
            mp18->v08(0);
            cCivilization* civ = mpCity->GetCivilization();
            if (civ != 0) {
                cGovernment* gov = civ->FUN_00bef8e0();
                if (gov != 0)
                    gov->FUN_01062e60(1);
            }
            cEffectsManager* em2 = FUN_0067ddd0();
            if (mp1c) {
                cVisualEffect* p = mp1c;
                mp1c = 0;
                p->v04();
            }
            if (em2->v2c(0x5dd13c64, 0, &mp1c)) {
                XformMsg m2;
                m2.ctor();
                m2.mPos = *(Vec3*)((cHallSub*)((char*)inv + 0x34))->v2c();
                m2.mFlags |= 4;
                m2.mSequence++;
                Mat3 rot2;
                Matrix3FromQuaternion(rot2.m, sub->v30());
                m2.mMat = rot2;
                m2.mFlags |= 2;
                m2.mSequence++;
                mp1c->v18(&m2);
                mp1c->v08(0);
            }
        }
    }
}

// @ 0x00ff69c0
void __cdecl FUN_00ff69c0(u32* begin, u32* end)
{
    int count = (int)(end - begin);
    if (count >= 2)
        for (int i = (count - 2) >> 1; i >= 0; --i)
            FUN_00ff6570((int*)begin, i, count, i, (int)begin[i]);
}

// @ 0x00ff6a00
void __cdecl FUN_00ff6a00(u32* begin, u32* end)
{
    int count = (int)(end - begin);
    if (count > 1) {
        u32* p = end - 1;
        do {
            u32 v = *p;
            *p = *begin;
            FUN_00ff6570((int*)begin, 0, --count, 0, (int)v);
            --p;
        } while (count > 1);
    }
}

// @ 0x00ff6a50
void cPlanetSimHost::LoadCivilization(cCivData* civ, cPlanetSimHost* host)
{
    cGameNounManager_s00ff_6a50* nounManager = NounManager_s00ff_6a50();
    int politicalID = civ->GetPoliticalID();
    int playerID = GetPlayerEmpireID();
    if (nounManager == 0)
        return;

    cPlanet* planet = GetActivePlanet_s00ff_6a50();
    cTribeInfo* tribe = planet->GetTribe();
    cCivilization_s00ff_6a50* civilization = nounManager->GetCivilization(politicalID);
    if (civilization == 0) {
        civilization = object_cast<cCivilization_s00ff_6a50>(nounManager->CreateNoun(0x18c816a), 0x901f1362);
        civilization->Init(politicalID, politicalID == playerID, civ->GetColorID(), 0);
        if (tribe)
            civilization->mField40 = tribe->mID;
        string16 name;
        planet->GetSpecies()->GetUiName(name);
        civilization->mName.SetText(name);
        civilization->SetWealth(civ->GetWealth(), 0);
    }
    if (civilization == 0)
        return;

    uint32_t instance = civ->mModelKeys.mpBegin->instanceID;
    if (instance != 0 && instance != 0xffffffff)
        civ->LoadModelKeys(&civilization->mModelKeys);
    else
        civ->DefaultModelKeys(&civilization->mModelKeys);

    int starPlayerID = StarManager_s00ff_6a50()->GetPlayerPoliticalID();
    if (civ->GetPoliticalID() == starPlayerID)
        civilization->SetColor(&kPlayerColorKey);
    else
        civilization->SetColor(GetColorKey(civ->GetColorID()));
    civilization->SetTribeData(&host->mTribeData);
    GetActivePlanet_s00ff_6a50();

    int cityCount = (int)civ->GetCities().size();
    for (int i = 0; i < cityCount; i++) {
        cCityData* data = civ->GetCities()[i];
        const Vector3& pos = data->GetPosition();
        if (pos != kZeroVector) {
            string16 cityName;
            if (data->GetName().empty())
                cityName = LocaleManager()->GetText(0x58f4c251).c_str();
            else
                cityName = data->GetName();

            cCity_s00ff_6a50* city = CreateCity(&pos, cityName.c_str());
            city->mOwner.SetOwner(data->GetBuildingLinks());
            city->mField2E8 = data->mFieldBC;
            city->mField2EC = data->mFieldC0;
            city->SetPoliticalID(politicalID);
            city->SetCityData(data);
            city->mSpiceProduction = data->mSpiceProduction;
            city->SetSize(data->mSize, 0);
            city->SetIncome(data->GetIncome(), data->GetHappiness());
            civilization->AddCity(city);

            if (data->mBuildings.empty()) {
                int a = 0, b = 0, c = 0, d = 0, e = 0;
                int cityMax = city->GetMaxSize();
                int dataMax = data->GetMaxSize();
                data->SetMaxSize(min_ref(cityMax, dataMax));
                GetCityLimits(data->GetMaxSize(), &a, &b, &c, &d, &e);
                int turrets = GetTurretCount(data->GetMaxSize());
                city->Layout(&pos, civilization->mWealth, turrets, d + c + b, politicalID == playerID, e,
                             data->mLayout, 0, 0, 1);
                data->RestoreWalls(city, planet->mType);
            } else {
                city->mSpatial.SetPosition(PlanetModel_s00ff_6a50()->DirectionToSurfacePosition(pos));
                city->mSpatial.SetOrientation(data->GetOrientation());
                city->Initialize(data->mLayout, 0, 0, 1);
                city->GetState()->mbRestored = true;
                city->SetIsPlayer(politicalID == playerID);
                data->RestoreCityWalls(city->GetMaxSize(), planet->mType);
                city->SetUnk(0);
                city->GetCityHall()->SetCity(city);

                for (unsigned int j = 0; j < data->mBuildings.size(); j++) {
                    cBuildingData* bd = &data->mBuildings[j];
                    if (bd->mClassId == 0x18ea1eb) {
                        cBuilding* hall = city->GetCityHall();
                        hall->mSpatial.SetPosition(bd->mPosition);
                        hall->mSpatial.SetOrientation(bd->mOrientation);
                        hall->mSpatial.SetModelKey(civ->GetResourceKey(bd));
                        hall->mCombatant.SetHealthPoints(bd->mHealthPoints);
                        hall->mCombatant.SetDamageState(bd->mDamageState);
                        hall->SetConnected(bd->mConnected);
                        hall->mEffectiveness = bd->mEffectiveness;
                        hall->SetFreezeCount(bd->mFreezeCount);
                    } else {
                        cBuilding* building = (cBuilding*)NounManager_s00ff_6a50()->CreateNoun(bd->mClassId);
                        if (building) {
                            building->SetCity(city);
                            building->mSpatial.SetPosition(bd->mPosition);
                            building->mSpatial.SetOrientation(bd->mOrientation);
                            building->mSpatial.SetModelKey(civ->GetResourceKey(bd));
                            building->mCombatant.SetHealthPoints(bd->mHealthPoints);
                            building->mCombatant.SetDamageState(bd->mDamageState);
                            building->SetConnected(bd->mConnected);
                            building->SetUnk25(bd->mbUnk25);
                            building->mEffectiveness = bd->mEffectiveness;
                            building->SetFreezeCount(bd->mFreezeCount);
                            city->AddBuilding(building, 1);
                            cBuildingNet* net = city->GetGrid()->GetNet(building->mSpatial.GetModelID());
                            if (net)
                                net->AddBuilding(building);
                            if (bd->mDamageState == 2)
                                building->mTimer.Restart();
                        }
                    }
                }

                for (unsigned int j = 0; j < data->mOrnaments.size(); j++) {
                    cOrnamentData* od = &data->mOrnaments[j];
                    cOrnament* ornament = (cOrnament*)NounManager_s00ff_6a50()->CreateNoun(od->mClassId);
                    if (ornament) {
                        ornament->SetModel(0x2ae5ba7, civ->GetPoliticalID(), od->mModelKey.instanceID);
                        ornament->mSpatial.SetPosition(od->mPosition);
                        ornament->mSpatial.SetOrientation(od->mOrientation);
                        city->AddOrnament(ornament);
                    }
                }

                city->UpdateBuildings();
                uint8_t turrets = data->GetTurretLocations();
                for (int t = 0; t < 8; t++) {
                    if (turrets & (1 << t))
                        city->AddTurret(t);
                }
            }

            city->GetState()->SetActive(1);
            city->SetUnk2(0);
            cSimMessage* msg = new ("Simulator", 0, 0, 0, 0) cSimMessage();
            msg->mpData0 = city;
            MessageServer()->PostMessage(0x56e50f1, msg, 0, 0);
        }
    }

    const sp_vector<cVehicleData*>& vehicles = civ->GetVehicles();
    int vehicleCount = (int)vehicles.size();
    for (int i = 0; i < vehicleCount; i++) {
        cVehicleData* vd = vehicles[i];
        Vector3 pos = vd->GetPosition();
        if (pos == kZeroVector) {
            cSimMessage* msg = new ("Simulator", 0, 0, 0, 0) cSimMessage();
            msg->mpData0 = civilization->GetCities()->mpBegin[0];
            msg->mpData1 = vd;
            msg->mpData2 = civ;
            MessageServer()->PostMessage(0x5416d55, msg, 0, 0);
        } else {
            cVehicle* vehicle = object_cast<cVehicle>(nounManager->CreateNoun(0x18c6de8), 0x137e8e0);
            if (vehicle)
                vehicle->AddRef();
            civilization->AddVehicle(vehicle);
            uint32_t modelType = 0xffffffff;
            switch (vd->GetLocomotion()) {
            case 0: modelType = 0xbc1041e6; break;
            case 1: modelType = 0xc15695da; break;
            case 2: modelType = 0x2090a11b; break;
            }
            vehicle->Init(vd->GetLocomotion(), vd->GetPurpose(), civilization->GetModelTypeKey(modelType));
            vehicle->SetVehicleData(vd);
            vehicle->SetCivData(civ);
            vehicle->mSpatial.SetPosition(pos);
            if (planet->GetTechLevel() == 5)
                vehicle->SetJustEyeCandy(true);
            BehaviorManager()->Register(&vehicle->mBehavior);
            vehicle->Release();
        }
    }
}

// @ 0x00ff74f0
void cSPSimPlanetHighLOD_s00ff_6a50::Func_00ff74f0()
{
    StartUFOCelebration(NounManager_s00ff_6a50()->Func_00b25c30());
    GetTriggerMgr()->setModal(true);
    FUN_010666a0_s00ff_6a50()->Func_01066d60();
}

// @ 0x00ff8460
PooledRegion* PooledRegion::FUN_00ff8460()
{
    FixedPoolBase tmp;
    tmp.mpHead = 0;
    tmp.init(&mNodes[0], 0xf0, 0x18, 4, 0);
    void* head = tmp.mpHead;

    mPrev = 0;
    mNext = 0;
    mPool.mpHead = 0;
    mPool.init(head, 0xf0, 0x18, 4, 0);
    mFirst10 = head;
    mLast14  = (char*)head + 0xf0;
    mCount18 = 0x18;

    mPrev = this;
    mNext = this;
    return this;
}

// @ 0x00ff84f0
void FUN_00ff84f0(int a, int b)
{
    if (a == b)
        return;
    int n = (b - a) >> 2;
    int t = n;
    int bits = 0;
    for (; t != 0; t >>= 1)
        bits++;
    quick_sort_impl(a, b, bits * 2 - 2);
    if (n > 0x1c) {
        FUN_00ff5ba0(a, a + 0x70);
        FUN_00ff5be0(a + 0x70, b);
    } else {
        FUN_00ff5ba0(a, b);
    }
}

// @ 0x00ff8560
void FUN_00ff8560(int param_1, float* param_2, unsigned param_3)
{
    void* pUniverse = FUN_01021260();
    int   taken     = (int)FUN_00b8e040(pUniverse, param_1) & 0xff;
    if (taken == 0)
        FUN_00ac9200(param_2);

    void* pm   = SP_PropertyManager();
    SP_GetPropertyAsKeyInstance(pm, 0x30608f0bu, param_2);
    void* tool = SP_CreateNoun(SP_NounManager(), 0x4e3fab5u);
    void* prop = tool ? ((RCObject*)tool)->v0c(0x4e3faaf) : 0;
    if (prop) {
        FUN_00c74a30(prop);
        FUN_00c74860(prop);
        FUN_00f924e0(prop, 0.0f);
    }
    void* q = 0;
    SP_QuaternionFromDirections(&q, param_2, 0);
    if ((unsigned)param_1 == g_placeEmbassy)
        SP_StarManager(0);
    FUN_010421c0(FUN_01067e60(FUN_010666a0_s00ff_8460()), 0);
}

// @ 0x00ff8780
cSPSimPlanetHighLOD_s00ff_8460::~cSPSimPlanetHighLOD_s00ff_8460()
{
    mpVtbl0 = (void*)0x01495000;
    mpVtbl8 = (void*)0x01494fdc;

    if (mpFx28) {
        RCObject* p = mpFx28;
        mpFx28 = 0;
        p->v08();
    }
    mSub1e4.Destroy();
    if (mpFx1dc) mpFx1dc->v04();
    mTree1c0.Destroy(mpNode1cc);
    if (mpFx1bc) mpFx1bc->v04();
    if (mpFx1b0) mpFx1b0->v08();
    if (mpArray19c && mpArray19c[-1] != 0)
        op_delete_array(mpArray19c);
    mTimer170.Destroy();
    mPool34.Destroy();
    if (mpFx30) mpFx30->v04();
    if (mpFx2c) mpFx2c->v04();
    if (mpFx28) mpFx28->v08();
    if (mpFx1c) mpFx1c->v04();
    if (mpFx18) mpFx18->v04();

    mpVtbl0 = (void*)0x013ec458;
    mpVtbl8 = (void*)0x013eb938;
}

// @ 0x00ff88c0
void cSPSimPlanetHighLOD_s00ff_8460::AddToList(const unsigned* pSrc, RCObject* pObj)
{
    SimListNode* head = &mPool34.mHead;
    SimListNode* cur  = head->mpNext;
    if (cur != head) {
        unsigned count = 0;
        do {
            cur = cur->mpNext;
            ++count;
        } while (cur != head);
        if (count >= 10) {
            SimListNode* first = head->mpNext;
            if (first->mpObj != 0)
                first->mpObj->v0c(0);
            mPool34.PopFront();
        }
    }

    RCObject* hold = 0;
    if (pObj != 0) {
        pObj->v00();
        hold = pObj;
    }

    struct NodeData { RCObject* mpObj; unsigned mD0, mD1, mD2; } data;
    data.mpObj = hold;
    data.mD0 = pSrc[0];
    data.mD1 = pSrc[1];
    data.mD2 = pSrc[2];

    SimListNode* n = mPool34.AllocNode(&data);
    n->mpNext = head;
    n->mpPrev = head->mpPrev;
    head->mpPrev->mpNext = n;
    head->mpPrev = n;

    if (hold != 0)
        hold->v04();
}

// @ 0x00ff8970
cSPSimPlanetHighLOD_s00ff_8460* __fastcall cSPSimPlanetHighLOD_ctor(cSPSimPlanetHighLOD_s00ff_8460* self)
{
    BaseGonzagoSim_ctor(self);

    self->mpVtbl0 = (void*)0x01495000;
    self->mpVtbl8 = (void*)0x01494fdc;
    self->mFlag10 = 1;
    self->mByte14 = 0;
    self->mpFx18 = 0;
    self->mpFx1c = 0;
    self->mpFx20 = 0;
    self->mpFx28 = 0;
    self->mpFx2c = 0;
    self->mpFx30 = 0;
    self->mPool34.Init();
    self->mByte158 = 0;
    self->mF15c = 1.0f;                  // 0x015b60e0
    self->mF160 = 0.0f;                  // 0x015b60e4
    self->mF164 = 0.0f;                  // 0x015b60e8
    self->mTimer170.Init();
    self->mpArray19c = 0;
    self->mpUnk1a0 = 0;
    self->mpUnk1a4 = 0;
    self->mpFx1b0 = 0;
    self->mByte1b4 = 0;
    self->mpUnk1b8 = 0;
    self->mpFx1bc = 0;
    self->mTree1c0.mpNode = &self->mTree1c0.mpNode;
    self->mTree1c0.mpPrev = &self->mTree1c0.mpNode;
    self->mpNode1cc = 0;
    self->mCount1d0 = 0;
    self->mpUnk1d4 = 0;
    self->mpFx1dc = 0;
    self->mByte1e0 = 0;
    self->mSub1e4.Init();

    void* mem = operator_new(0x28, "Simulator", 0, 0, 0, 0);
    RCObject* pNew = mem ? Simulator_alloc(mem) : 0;
    RCObject* pOld = self->mpFx28;
    if (pNew != pOld) {
        if (pNew) pNew->v04();
        self->mpFx28 = pNew;
        if (pOld) pOld->v08();
    }
    return self;
}

// @ 0x00ff8ad0
void FUN_00ff8ad0(void)
{
    void* self   = FUN_01021240_s00ff_8460();
    void* avatar = SP_StarManager(self);
    void* empire = SP_GetEmpireByID(SP_StarManager(avatar));
    if (empire == 0)
        return;

    float range = 10.0f;
    if (SP_GetSpaceCombatTuning() != 0) {
        float* pf = SP_GetPropertyAsFloat();
        if (pf) range = *pf;
    }

    void* stars = SP_GetStars(empire);
    SP_GetStarRecords(SP_StarManager(0));
    SP_GetPropertyAsKeyInstance(stars, 0x1601760u, 0);

    int count = 3;
    if (SP_GetSpaceCombatTuning() != 0) {
        float* pf = SP_GetPropertyAsFloat();
        if (pf) count = (int)*pf;
    }

    void* ufoKey = SP_GetUFOKey(empire);
    for (int i = 0; i < count; ++i) {
        void* ufo = SP_CreateUFO(8, 0, ufoKey);
        SP_SpaceGameGet(ufo);
        FUN_01009a40(ufo);
    }

    RCObject* audio = (RCObject*)SP_GetSystemAT();
    if (audio != 0) {
        audio->v0c(0x3475365);
        audio->v0c(0x3475381);
        audio->v0c((int)GetPlayerEmpireIDFn());
    }
    (void)range;
}

// @ 0x00ff8e00
void cSPSimPlanetHighLOD_s00ff_8460::SpawnRallyChargeup(void* pTarget, float* pPos)
{
    void* fx     = SP_EffectsManager();
    unsigned hash = (unsigned)SP_FNVHash("SG_ufo_raider_rally_chargeup", 0x811c9dc5u, 1);
    RCObject* effect = (RCObject*)((RCObject*)fx)->v0c((int)hash);

    if (effect != 0) {
        void* sim = SP_GetUFOSimulator();
        void* inv = SP_GetPlayerInventory(sim);
        float pos[3];
        pos[0] = pPos[0];
        pos[1] = pPos[1];
        pos[2] = pPos[2];
        float mat[9];
        SP_Matrix3Assign(mat, pos);
        SP_Matrix3FromFacingAndUp(mat, pos, (void*)pTarget);
        FUN_00dd85c0(&this->mTree1c0, mat);
        this->mpFx18 = effect;
    }
}

// @ 0x00ff9070
void FUN_00ff9070(void)
{
    cGameNounManager_s00ff_8460* mgr = (cGameNounManager_s00ff_8460*)SP_NounManager();
    GameDataList* v = mgr->GetGameDataVector((void*)0x00b21080, (void*)0x00d3d420,
                                             (void*)0x00b236c0, (void*)0x00b1e500,
                                             (void*)0x018c816a);
    GameDataRange* r = &v->mRange;
    void** it = r->mpBegin;
    if (it != r->mpEnd) {
        do {
            void* obj = *it;
            GameDataSlotFn f = *(GameDataSlotFn*)((char*)*(void**)obj + 0x40);
            f(obj);
            ++it;
        } while (it != r->mpEnd);
    }

    mgr = (cGameNounManager_s00ff_8460*)SP_NounManager();
    v = mgr->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                               (void*)0x00ad48b0, (void*)0x00b1e500,
                               (void*)0x018ebadc);
    r = &v->mRange;
    it = r->mpBegin;
    if (it != r->mpEnd) {
        do {
            void* obj = *it;
            GameDataSlotFn f = *(GameDataSlotFn*)((char*)*(void**)obj + 0x40);
            f(obj);
            ++it;
        } while (it != r->mpEnd);
    }
}

// @ 0x00ff9100
void* FUN_00ff9100(int arg0, void* arg1)
{
    void* setting = SP_GetSetting9();
    if (setting == 0)
        return 0;

    void* profile = SP_GetAvatarProfile(setting);
    void* nounVec = SP_GetGameDataVector(SP_NounManager(),
                                         0x18c43e8u, 0, 0, 0, 0);
    (void)profile; (void)nounVec;

    RCObject* city = (RCObject*)FUN_00bd9d70(arg1, 0);
    if (city == 0)
        return 0;

    RCObject* player = (RCObject*)SP_GetPlayerCivilization(SP_NounManager());
    if (player == 0) {
        RCObject* created = (RCObject*)SP_CreateNoun(SP_NounManager(), 0x18c816au);
        if (created)
            player = (RCObject*)created->v0c(0x901f1362);
        SP_SetPlayerEmpire(player, SP_GetPlayerEmpireOrMinus1(), 1, 0x53dbcf2u, 0);
    }

    SP_ReduceCitiesOnPlanet(player, city);

    RCObject* civil = (RCObject*)SP_GetCivilization(city);
    if (civil == 0)
        return city;

    void* mem = operator_new(0x50, "Simulator/cCivData", 0, 0, 0, 0);
    if (mem)
        FUN_00be8680(mem, 0, 0, 0, 1, 0, 0, 0, 1, 0);

    (void)arg0;
    return city;
}

// @ 0x00ffa2c0
namespace SP {
void cSPSimPlanetHighLOD_s00ff_a2c0::FUN_00ffa2c0()
{
    this->m1b8 = 0;
    PlanetObj* planet = GetActivePlanet();
    if (this->m1b4) {
        this->m1b4 = 0;
        FUN_00ba5270(planet, 0);
    }
    this->m1e0 = 0;
    if (this->m1dc) {
        this->m1dc->SetFlag(0);
        if (this->m1dc) { RefObjI* q = this->m1dc; this->m1dc = 0; q->Release(); }
    }
    for (TreeNode* n = (TreeNode*)this->m1c0.m08; n != (TreeNode*)&this->m1c0.m04; n = (TreeNode*)RBTreeIncrement(n))
        n->m14->SetFlag(1);
    this->m1c0.FUN_00d0c930(this->m1c0.m0c);
    this->m1c0.m04 = &this->m1c0.m04;
    this->m1c0.m08 = &this->m1c0.m04;
    this->m1c0.m0c = 0;
    this->m1c0.m10 = 0;
    this->m1c0.m14 = 0;
    if (this->m1bc) {
        this->m1bc->SetFlag(1);
        if (this->m1bc) { RefObj_s00ff_a2c0* q = this->m1bc; this->m1bc = 0; q->Release(); }
    }
    if (this->m18) {
        this->m18->SetFlag(1);
        if (this->m18) { RefObj_s00ff_a2c0* q = this->m18; this->m18 = 0; q->Release(); }
    }
    if (this->m1c) {
        this->m1c->SetFlag(1);
        if (this->m1c) { RefObj_s00ff_a2c0* q = this->m1c; this->m1c = 0; q->Release(); }
    }
    cGameNounManager_s00ff_a2c0* nm = NounManager();
    if (nm) {
        FUN_00b3d480()->FUN_00acc390();
        FUN_00b3d480()->FUN_00ad0bd0();
        BehaviorManager_()->Slot30();
        GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00ad48b0, gFn_00b1e500, (void*)0x18ebadc);
        int cnt10 = 0, cnt14 = 0;
        for (void** pp = (void**)gv->m04; pp != (void**)gv->m08; pp++) {
            Entity* e = (Entity*)*pp;
            if (e->FUN_00c372b0()) continue;
            Creature* c = e->m6c8;
            if (c && c->m08.Play(0x10, 0)) continue;
            if (e->m714 == 6) cnt10++;
            else if (e->m714 == 7) cnt14++;
        }
        planet->FUN_00c70bc0(cnt10);
        planet->m108 = cnt14;
        FUN_00c9a080();
        nm->FUN_00b25fe0();
        nm->FUN_00b22bc0();
        nm->FUN_00b22960();
        nm->FUN_00b222a0();
        BehaviorManager_()->Slot44();
        CheatManager_()->Slot1c(&gU_15b8690);
        if (gSim_1699ab8 == 0) {
            SimSingleton* s = (SimSingleton*)operator_new(0x58, gStr_SimSingleton, 0, 0, 0, 0);
            gSim_1699ab8 = s ? (void*)s->ctor() : 0;
        }
        SimSingleton* sim = (SimSingleton*)gSim_1699ab8;
        sim->FUN_00dcc2c0();
        SimTicker* st = SimTicker_();
        if (gSim_1699ab8 == 0) {
            SimSingleton* s2 = (SimSingleton*)operator_new(0x58, gStr_SimSingleton, 0, 0, 0, 0);
            gSim_1699ab8 = s2 ? (void*)s2->ctor() : 0;
        }
        st->Slot54(gSim_1699ab8);
        if (this->m10 != 1) {
            this->m10 = 1;
            uint32_t u = FNVHash(gStr_spgspg, 0x811c9dc5, 1);
            AudioSystem* as = GetSystemAT();
            if (as) {
                as->Slot38(0x3cdd1a9);
                as->Slot40(0x34753a7, u);
                as->Slot3c(0x34753aa, (float)this->m10);
                as->Slot58();
            }
            MessageServer_()->Slot14(0x4c703a5, 0, 0);
        }
        if (this->m28) { RefObj_s00ff_a2c0* q = this->m28; this->m28 = 0; q->FX(); }
        if (this->m30) { RefObj_s00ff_a2c0* q = this->m30; this->m30 = 0; q->Release(); }
        for (ListNode* n = this->m34.mHead; n != (ListNode*)&this->m34; n = n->mNext)
            if (n->m08) n->m08->SetFlag(0);
        this->m34.FUN_00ff80b0();
        this->m34.mHead = (ListNode*)&this->m34;
        this->m34.mTail = (ListNode*)&this->m34;
        if (this->m1b0) {
            this->m1b0->FUN_00ebd340();
            if (this->m1b0) { RefObj_s00ff_a2c0* q = this->m1b0; this->m1b0 = 0; q->FX(); }
        }
    }
}
}  // namespace SP

// @ 0x00ffa690
namespace SP {
void FUN_00ffa690()
{
    GameTimeManager* gt = GameTimeManager300();
    uint64_t v = gt->FUN_00b316c0();
    uint32_t u = (uint32_t)(v / 1000);

    PlanetRecord* pr = GetActivePlanetRecord();
    ElemList* list = &pr->mElemList;
    for (RecElem* e = list->m00; ; e = (RecElem*)((char*)e + 0x2c)) {
        if (e == list->m04) break;
        if ((e->m28 & 8) && e->m12 == 7 && (uint32_t)e->m18 < u && (u - (uint32_t)e->m18) > 300) {
            list->FUN_00b8e540(e);
            break;
        }
    }
    cGameNounManager_s00ff_a2c0* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00ad4930, gFn_00b1e500, (void*)0x2dd8c42);
    int cnt = (int)(((char*)gv->m08 - (char*)gv->m04) >> 2);
    for (int i = 0; i < cnt; i++) {
        Entity* e = ((Entity**)gv->m04)[i];
        if (e->m658 == 7 && (uint32_t)e->m640 < u && (u - (uint32_t)e->m640) > 0x12c) {
            NounManager()->RemoveNoun(e);
            return;
        }
    }
}
}  // namespace SP

// @ 0x00ffa780
namespace SP {
void cSPSimPlanetHighLOD_s00ff_a2c0::CreateReplacement()
{
    void* avatar = FUN_01021240()->GetAvatar();
    cEmpire_s00ff_a2c0* empire = StarManager()->GetEmpireByID((int)avatar);
    if (!empire) return;

    int key = empire->GetUFOKey();
    cStarRecord_s00ff_a2c0* rec = empire->m84;
    cSPGameDataUFO_s00ff_a2c0* ufo = CreateUFO(6, &rec, key);

    Inventory* inv = GetUFOSimulator()->GetPlayerInventory();
    Vec3_s00ff_a2c0* base = inv->m34.Slot2C();

    Entity* best = 0;
    float bestD = 0.0f;
    GdVector* gv = NounManager()->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    if (gv->m04 != gv->m08) {
        for (void** pp = (void**)gv->m04; pp != (void**)gv->m08; pp++) {
            Entity* e = (Entity*)*pp;
            Vec3_s00ff_a2c0* p2 = e->m120.Slot2C();
            float dy = p2->y - base->y;
            float dz = p2->z - base->z;
            float dx = p2->x - base->x;
            float d = (float)sqrt(dy * dy + (dz * dz + dx * dx));
            if (d > bestD) { bestD = d; best = e; }
        }
        if (best) {
            Vec3_s00ff_a2c0 v;
            FUN_00bd7f70(&v, &bestD);
            float len = (float)sqrt(v.x * v.x + (v.z * v.z + v.y * v.y));
            ufo->FUN_00c3be70(&v);
            ufo->FUN_00c3daa0(len);
            ufo->PopToDestination();
            ufo->FUN_00c3daa0(len + 35.0f);
        }
    }
}
}  // namespace SP

// @ 0x00ffa900
namespace SP {
void cSPSimPlanetHighLOD_s00ff_a2c0::BlowUpCity(void* city, int param3)
{
    RefObj_s00ff_a2c0* c = this->m2c;
    if (city == c && c != 0) {
        this->m2c = 0;
        c->Release();
    }
    int empId = GetPlayerEmpireID();
    PlanetRecord* pr = GetActivePlanetRecord();
    int avatar = -1;
    if (pr != 0 && pr->FUN_00b8de30() != 0)
        avatar = (int)pr->FUN_00b8de30()->GetAvatar();

    ((Entity*)city)->FUN_00bdc050();
    if (((Entity*)city)->m74c == empId) {
        float r = gRand_1601760.FUN_009360d0();
        float chance = GetSpaceCombatTuning()->GetLootCityMoneyChance();
        if (r <= chance) {
            Vec3_s00ff_a2c0* p = ((Entity*)city)->Slot64();
            DropLoot(*p);
        }
    }
    cGameNounManager_s00ff_a2c0* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    bool four = (((char*)gv->m08 - (char*)gv->m04) & 0xfffffffc) == 4;
    int home = GetPlayerEmpire()->GetHomePlanet();
    if (pr == (PlanetRecord*)home && four) {
        Vec3_s00ff_a2c0 v;
        PlanetModel()->GetRandomSurfacePoint(&v);
        void* rr = FUN_00b26930((int)0x1058c90, empId, &v, 0, 0xfd701f6f, 0, 0, 0);
        ((AeObj*)rr)->FUN_00ae49d0((int)0x1058c90, empId, &v, 0, 0xfd701f6f, 0, 0, 0);
    }
    nm->RemoveNoun(city);
    if (param3 == empId && avatar != empId && four)
        FUN_0102b690(avatar, param3, 1);
}
}  // namespace SP

// @ 0x00ffaa90
namespace SP {
void cSPSimPlanetHighLOD_s00ff_a2c0::FUN_00ffaa90(int param)
{
    cGameNounManager_s00ff_a2c0* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    int cnt = (int)(((char*)gv->m08 - (char*)gv->m04) >> 2);
    TempC tmp;
    tmp.FUN_00b93c60(cnt, &gv->m10);
    void* end = 0;
    FUN_00829110(&end, gv->m04, gv->m08, tmp.mPtr, (void*)param);
    int n = (int)(((char*)end - (char*)tmp.mPtr) >> 2);
    for (int i = 0; i < n; i++)
        BlowUpCity(((void**)tmp.mPtr)[i], param);
    for (void** p = (void**)tmp.mPtr; (char*)p < (char*)end; p++)
        if (*p) ((RefObj_s00ff_a2c0*)*p)->Release();
    if (tmp.mPtr && ((int*)tmp.mPtr)[-1] != 0)
        operator_delete_array(tmp.mPtr);
}
}  // namespace SP

// @ 0x00ffab60
namespace SP {
void FUN_00ffab60()
{
    cGameNounManager_s00ff_a2c0* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    int cnt = (int)(((char*)gv->m08 - (char*)gv->m04) >> 2);
    for (int i = 0; i < cnt; i++) {
        Entity* e = ((Entity**)gv->m04)[i];
        SFXObj* s = e->Slot6C();
        s->FUN_00becd70(0);
    }
}
}  // namespace SP

// @ 0x00ffb180
void cSPSimPlanetHighLOD_s00ff_b180::FUN_00ffb180()
{
    cGameNounManager_s00ff_b180* pManager = NounManager_s00ff_b180();
    tGameDataList* pList = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00ae7060,
                                                       (void*)FUN_00ae7080, (void*)FUN_00b1e520,
                                                       g_nounListHarvest);
    tPtrVector* pNouns = &pList->mData;
    void** pCur = pNouns->mpBegin;
    void** pEnd = pNouns->mpEnd;
    if (pCur != pEnd)
    {
        do
        {
            tHarvestNoun* pNoun = (tHarvestNoun*)*pCur;
            if (pNoun != 0)
            {
                tSimThing* pThing = pNoun->v04(0x024270c4);
                if (pThing != 0)
                {
                    tBombKey* pKey = pThing->mp518;
                    if (pKey != 0)
                    {
                        uint32_t* pValue = pKey->v18();
                        if (pValue[0] == g_planetBusterKey[0] && pValue[1] == g_planetBusterKey[1] &&
                            pValue[2] == g_planetBusterKey[2])
                        {
                            pNoun->mb10 = false;
                        }
                    }
                }
            }
            ++pCur;
        } while (pCur != pEnd);
    }

    MessageServer_s00ff_b180()->v18(0x04f4d25e, 0, 0, 0);
    mb1e0 = false;
    if (mp1dc != 0)
    {
        mp1dc->v0c(1);
        if (mp1dc != 0)
        {
            tEffectHandle* pOld = mp1dc;
            mp1dc = 0;
            pOld->Release();
        }
    }
}

// @ 0x00ffb830
void cSPSimPlanetHighLOD_s00ff_b180::CheckForCityDestruction()
{
    float fWater = PlanetModel_s00ff_b180()->GetWaterHeight();
    float fWater2 = fWater * fWater;
    tCityVector cities;
    GetActivePlanet_s00ff_b180();
    if (!PlanetModel_s00ff_b180()->mp24->v50())
    {
        cities.DoDestroy();
        return;
    }

    int32_t nEmpire = -1;
    cGameNounManager_s00ff_b180* pManager = NounManager_s00ff_b180();
    tGameDataList* pList = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                       (void*)FUN_00acdff0, (void*)FUN_00b1e500,
                                                       g_nounListPlanet);
    tPtrVector* pNouns = &pList->mData;
    int32_t nCount = (int32_t)(pNouns->mpEnd - pNouns->mpBegin);
    for (int32_t i = 0; i < nCount; ++i)
    {
        cSimGameData* pCity = (cSimGameData*)pNouns->mpBegin[i];
        cCityHall_s00ff_b180* pHall = pCity->GetCityHall();
        tVector3 vPos;
        PlanetModel_s00ff_b180()->DirectionToSurfacePosition(&vPos, pCity->mObj120.v2c());
        bool bInside = vPos.x * vPos.x + vPos.y * vPos.y + vPos.z * vPos.z < fWater2;

        bool bDamaged = pHall->mObj120.FUN_008e7f80() != 0;
        if (bDamaged)
        {
            nEmpire = pHall->mn15c;
        }
        else
        {
            if (!bInside)
                continue;
            nEmpire = -1;
        }

        cSimGameData* pRef = pCity;
        if (pCity != 0)
            pCity->AddRef();
        if (cities.mpEnd < cities.mpCapacity)
        {
            *cities.mpEnd = pCity;
            ++cities.mpEnd;
            if (pCity != 0)
                pCity->AddRef();
        }
        else
        {
            cities.DoInsertValue(cities.mpEnd, pRef);
        }
        if (pRef != 0)
            pRef->Release();

        if (GetCurrentGameMode() == (uint32_t)g_gameModeGalaxy)
        {
            if (bInside)
            {
                if (pCity->v4c() != GetPlayerEmpireID())
                {
                    RelationshipManager()->RecordEvent(0x0526e5cf, (void*)GetPlayerEmpireID(),
                                                       (void*)(uint32_t)pCity->v4c(), 1.0f);
                }
            }
            if (pCity->mf220 > g_kRealZero)
            {
                tGameDataList* pList2 = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                                    (void*)FUN_00acdff0, (void*)FUN_00b1e500,
                                                                    g_nounListPlanet);
                tPtrVector* pNouns2 = &pList2->mData;
                int32_t nCount2 = (int32_t)(pNouns2->mpEnd - pNouns2->mpBegin);
                for (int32_t k = 0; k < nCount2; ++k)
                {
                    cSimGameData* pOther = (cSimGameData*)pNouns2->mpBegin[k];
                    if ((void*)pOther->v4c() == (void*)pCity->v4c())
                        pOther->FUN_00bdbf10();
                }
            }
        }
    }

    void** pSlot = cities.mpBegin;
    while (pSlot != cities.mpEnd)
    {
        FUN_00ffa900((cSimGameData*)*pSlot, nEmpire);
        ++pSlot;
    }
    pSlot = cities.mpBegin;
    while (pSlot < cities.mpEnd)
    {
        if (*pSlot != 0)
            ((tRefObject*)*pSlot)->Release();
        ++pSlot;
    }
    if (cities.mpBegin != 0 && ((int32_t*)cities.mpBegin)[-1] != 0)
        operator_delete_array(cities.mpBegin);
}

// @ 0x00ffbb20
void cSPSimPlanetHighLOD_s00ff_b180::OnTick(uint32_t nTimeLo, uint32_t nTimeHi)
{
    FUN_00ffabc0();
    SolarSystemUpdateNPC_UFOs(nTimeLo);
    CheckForCityDestruction();

    cPlanetRecord* pPlanet = GetActivePlanet_s00ff_b180();
    void* pEmpire = pPlanet->FUN_00c71e30();
    if (pEmpire != 0 && pEmpire != GetPlayerEmpire_s00ff_b180())
    {
        NounManager_s00ff_b180()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
                                         (void*)FUN_00b1e500, g_nounListPlanet);
    }

    FUN_00ffaf20(nTimeLo);
    FUN_00ffa690();

    uint64_t nTime = ((uint64_t)nTimeHi << 32) | nTimeLo;
    mp1b0->Tick((float)nTime * 0.001f);

    if (pPlanet->FUN_00c70e00() == 5)
        mp28->v10(nTimeLo, nTimeHi, (void*)pPlanet->FUN_008414c0());

    if (pPlanet->FUN_00c70e00() == 5 || pPlanet->FUN_00c70e00() == 4)
        FUN_00ffab60();

    cTerrainSphere* pSphere = (cTerrainSphere*)NounManager_s00ff_b180()->GetCurrentTerrainSphere();
    if (pSphere->Check())
    {
        if (mp1bc == 0)
        {
            tEffectsManager* pEffects = EffectsManagerPtr();
            if (mp1bc != 0)
            {
                tEffectHandle* pOld = mp1bc;
                mp1bc = 0;
                pOld->Release();
            }
            if (pEffects->v2c(0x20caebfa, 0, &mp1bc))
                mp1bc->v08(0);
        }
    }
    else
    {
        if (mp1bc != 0)
        {
            mp1bc->v0c(1);
            if (mp1bc != 0)
            {
                tEffectHandle* pOld = mp1bc;
                mp1bc = 0;
                pOld->Release();
            }
        }
    }

    if (GetCurrentGameMode() == (uint32_t)g_gameModeGalaxy && mb158)
        FUN_00ff7530(nTimeLo, nTimeHi);

    tVector3 vPos;
    vPos.x = g_defaultVector[0];
    vPos.y = g_defaultVector[1];
    vPos.z = g_defaultVector[2];
    tVector3 vSize;

    tSlotMessage msg;
    msg.mpVtable = g_slotMessageBaseVtable;
    msg.mnRefCount = 0;
    msg.mpVtable = g_slotMessageVtable;
    msg.mnKey = g_ufoMessageKey;
    msg.mn38 = 0;
    FUN_01015df0();

    tDOMWrapper* pNode = (tDOMWrapper*)0;
    tStringKey nString;
    tVector3* pComputed;
    if (pNode != 0 && pNode->FUN_00a98020() && pNode->FUN_00ff0420() != 0)
    {
        tVector3* pv = (tVector3*)pNode->FUN_00ff0420()->mObjC0.v2c();
        vPos.x = pv->x;
        vPos.y = pv->y;
        vPos.z = pv->z;
        pComputed = FUN_0095df60(&nString, g_szUFOString, (uint32_t)App()->v50()->v1c());
    }
    else
    {
        cSimInventory* pInventory = GetUFOSimulator_s00ff_b180()->GetPlayerInventory();
        tVector3* pv = (tVector3*)pInventory->mObj34.v2c();
        vPos.x = pv->x;
        vPos.y = pv->y;
        vPos.z = pv->z;
        cSimInventory* pInventory2 = GetUFOSimulator_s00ff_b180()->GetPlayerInventory();
        pComputed = FUN_0059aed0(&nString, g_szUFOString, (uint32_t)pInventory2->mObj34.v30());
    }
    vSize = *pComputed;

    msg.mpPosition = &vPos;
    msg.mpSize = &vSize;
    EA::Messaging::GetServer()->v14(msg.mnKey, &msg, 0);
    msg.Destruct();
}
