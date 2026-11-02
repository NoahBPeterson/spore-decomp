// src/game/SPGonzago/SPSpaceCombatUtilities.cpp -- migrated from slice(s) s0102be20, s010297e0, s0102af80 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceCombatUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cEmpire.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cSPMission.h"
#include "SP/cStarManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_01002bd0(void);          // SP::SpaceGameGet()
extern "C" void* __cdecl FUN_00ffbe50(void);          // SP::GetUFOSimulator()
extern "C" bool  __cdecl FUN_010299c0(void);          // SP::PlayerHasAnyAutoblaster
extern "C" void* __cdecl FUN_00b3d350(void);          // SP::PlanetModel()
extern "C" void* __cdecl FUN_00b3d300(void);          // SP::NounManager()
extern "C" void* __cdecl FUN_00b3d2a0(int);          // SP::StarManager()
extern "C" int   __cdecl FUN_01021080(void);          // cSPLivingUniverse::GetUniverseContext
extern "C" int   __cdecl FUN_01021090(void);          // cSPLivingUniverse::GetPlayerEmpireID
extern "C" void* __cdecl FUN_01021260(void);          // cSPLivingUniverse::GetActivePlanet
extern "C" void* __cdecl FUN_010212a0(void);          // cSPLivingUniverse::GetActivePlanetRecord
extern "C" void* __cdecl FUN_01021300(void);          // cSPLivingUniverse::GetPlayerEmpire
extern "C" void* __cdecl FUN_01021240(void);          // cCivData / SP::GetCivData
extern "C" void* __cdecl FUN_0102acb0(int type, void* a, void* b);  // SP::CreateUFO
extern "C" void* __cdecl FUN_0102ac50(int type, void* globe);       // CreateUFOForSolarOrGalaxy
extern "C" bool  __cdecl FUN_0102aa50(void* t, void* self, void* p); // cSPSpaceCommCanTarget
extern "C" void* __cdecl FUN_010666a0(void*);
extern "C" void  __cdecl FUN_00f47380(void*);
extern "C" void _ReadWriteBarrier(void);
extern float DAT_016de6d4, DAT_016de6d8, DAT_016de6dc, DAT_016de6e0;
extern float DAT_016de6e4, DAT_016de6e8, DAT_016de6ec, DAT_016de6f0, DAT_016de6f4, DAT_016de6f8;
extern float DAT_016dc060[];
extern float DAT_0147c308, DAT_0147c310;
extern float DAT_01465544, DAT_01477fc0, DAT_01465160;
extern float DAT_013ef54c, DAT_013ef53c;
extern float DAT_0145c12c;
extern float DAT_013f56a4;
extern int   DAT_015b7518;
extern int   DAT_018ebadc;
extern char  DAT_0149954c[];
extern "C" float* __cdecl FUN_0059aed0(void*, void*, void*);
extern "C" void* __cdecl FUN_00cd7d10(void);
extern "C" void* __cdecl FUN_00d3d420(void);
extern "C" void* __cdecl FUN_00ad48b0(void);
extern "C" void* __cdecl FUN_00b1e500(void);
extern "C" void* __cdecl FUN_0067de30(void);         // PropertyManager
extern "C" void* __cdecl FUN_0067dcc0(void);         // MessageServer
extern "C" void* __cdecl FUN_00a206f0(void);         // Audio::GetSystemAT
extern "C" void* __cdecl FUN_00b3d2c0(void);         // RelationshipManager
extern "C" void* __cdecl FUN_00b3d380(void);         // GameTimeManager
extern "C" void  __cdecl FUN_01009a40(void*, void*);
extern "C" float sinf(float);
extern "C" float cosf(float);
extern "C" float sqrtf(float);
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s0102af80 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
extern "C" void* __cdecl FUN_01002bd0(void);          // SP::SpaceGameGet()
extern "C" void* __cdecl FUN_00ffbe50(void);          // SP::GetUFOSimulator()
extern "C" bool  __cdecl FUN_010299c0(void);          // SP::PlayerHasAnyAutoblaster
extern "C" void* __cdecl FUN_00b3d350(void);          // SP::PlanetModel()
extern "C" void* __cdecl FUN_00b3d300(void);          // SP::NounManager()
extern "C" void* __cdecl FUN_00b3d2a0(int);          // SP::StarManager()
extern "C" int   __cdecl FUN_01021080(void);          // cSPLivingUniverse::GetUniverseContext
extern "C" int   __cdecl FUN_01021090(void);          // cSPLivingUniverse::GetPlayerEmpireID
extern "C" void* __cdecl FUN_01021260(void);          // cSPLivingUniverse::GetActivePlanet
extern "C" void* __cdecl FUN_010212a0(void);          // cSPLivingUniverse::GetActivePlanetRecord
extern "C" void* __cdecl FUN_01021300(void);          // cSPLivingUniverse::GetPlayerEmpire
extern "C" void* __cdecl FUN_01021240(void);          // cCivData / SP::GetCivData
extern "C" void* __cdecl FUN_0102acb0(int type, void* a, void* b);  // SP::CreateUFO
extern "C" void* __cdecl FUN_0102ac50(int type, void* globe);       // CreateUFOForSolarOrGalaxy
extern "C" bool  __cdecl FUN_0102aa50(void* t, void* self, void* p); // cSPSpaceCommCanTarget
extern "C" void* __cdecl FUN_010666a0(void*);
extern "C" void  __cdecl FUN_006a07d0(void* p, uint32_t prop, void* outCount, void* outArr);
extern "C" void  __cdecl FUN_006a12a0(void* p, uint32_t key, void* out);
extern "C" void* __cdecl FUN_00f473a0(uint32_t n, const char* name, int a, int b, const char* file, int line);
extern "C" void  __cdecl FUN_00f47380(void*);
extern "C" uint32_t __cdecl FUN_011e0970(uint32_t lo, uint32_t hi, uint32_t b, uint32_t z);
extern "C" void _ReadWriteBarrier(void);
extern float DAT_016de6d4, DAT_016de6d8, DAT_016de6dc, DAT_016de6e0;
extern float DAT_016de6e4, DAT_016de6e8, DAT_016de6ec, DAT_016de6f0, DAT_016de6f4, DAT_016de6f8;
extern float DAT_016dc060[];
extern float DAT_0147c308, DAT_0147c310;
extern float DAT_01465544, DAT_01477fc0, DAT_01465160;
extern float DAT_013ef54c, DAT_013ef53c;
extern float DAT_0145c12c;
extern float DAT_013f56a4;
extern int   DAT_015b7518;
extern int   DAT_018ebadc;
extern char  DAT_0149954c[];
class Obj {
public:
    void* F_inv();                                   // 0x00a1ad60 GetPlayerInventory
    void* F_sgd();                                   // 0x00bfc5f0 SetGameDataOwner2 -> owner
    int   F_42a0();                                  // 0x00fe42a0
    void* F_4bb0(int);                               // 0x01004bb0 f4bb0
    void  F_9a40(void*);                             // 0x01009a40
    void* F_8db30();                                 // 0x0108db30
    bool  F_cce0();                                  // 0x0104cce0
    bool  F_cdb0(void*);                             // 0x0104cdb0
    bool  F_8990(int);                               // 0x00c38990
    void  F_b500();                                  // 0x0106b500
    void  F_7b0(int, int);                           // 0x010027b0 AddPosseMember
    float* F_f70();                                  // 0x0041ea70 Property::GetFloat
    void  F_dstruct();                               // 0x00421cf0 ~MessageBasicRC
    void* F_a9370(int);                              // 0x00ba9370 GetEmpireByID
    int   F_17a0();                                  // 0x00c317a0 GetWeaponryLevel
    void* F_26b0();                                  // 0x00c326b0 GetUFOKey
    float* F_65e0();                                 // 0x005c65e0 GetCities
    int*  F_21340(void*, void*, void*, void*, void*); // 0x00b21340 GetGameDataVector
    void* F_7d90();                                  // 0x00f67d90 GetCurrentTerrainSphere
    void  F_76790(int, int);                         // 0x00c76790
    char  F_784c0(int);                              // 0x00c784c0 TestPlayerWarVictory
    void  F_75520(int);                              // 0x00c75520 DoPlayerWarVictory
    void  F_e5430(int, int);                         // 0x00fe5430
    void* F_5d20(void*);                             // 0x00ff5d20 SpawnArtifact
    void* F_b1fdb0();                                // 0x00b1fdb0 GetAvatar
    void  F_81780(void*, void*, float, float);       // 0x00b81780 MakeRandomWorldPosition
    void* F_7f190(void*, void*);                     // 0x00b7f190 BuildSurfaceOrientation
    void  F_aa40(void*, void*);                      // 0x00c3aa40
    void  F_dae0(void*);                             // 0x00c3dae0
    void  F_be70(void*);                             // 0x00c3be70
    void  F_21b0(void*);                             // 0x00c421b0
    char  F_e040(void*);                             // 0x00b8e040
    void  F_9200(void*);                             // 0x00ac9200
    void  F_b810(unsigned, void*);                   // 0x00acb810
    void  F_f950(void*);                             // 0x00b5f950
    void  F_bfc470(int);                             // 0x00bfc470
    float F_06240(int, int, int, float);             // 0x00d06240 RecordEvent
    float F_2a230(int);                              // 0x0102a230 GetLootCityMinMoneyDrop
    float F_2a2a0(int);                              // 0x0102a2a0 GetLootCityMaxMoneyDrop
    float F_29f60(int);                              // 0x01029f60 GetLootMinMoneyDrop
    float F_29fd0(int);                              // 0x01029fd0 GetLootMaxMoneyDrop
    int   F_2a360(float, float, float);              // 0x0102a360 GetWeaponLevel
    uint64_t F_316c0();                              // 0x00b316c0 GameTimeManager::GetGameTime
};
class RLC {
public:
    uint32_t RandomUint32Uniform(uint32_t n);        // 0x00a68fb0
    double   RandomDoubleUniform();                  // 0x009360d0
};
extern RLC DAT_1601760;
extern Obj DAT_015b7510;
extern "C" void* __cdecl FUN_010666a0(void*);
extern "C" float* __cdecl FUN_0059aed0(void*, void*, void*);
extern "C" void  __cdecl FUN_00435ed0(uint32_t, void*);
extern "C" void* __cdecl FUN_00cd7d10(void);
extern "C" void* __cdecl FUN_00d3d420(void);
extern "C" void* __cdecl FUN_00ad48b0(void);
extern "C" void* __cdecl FUN_00b1e500(void);
extern "C" void* __cdecl FUN_0067de30(void);         // PropertyManager
extern "C" void* __cdecl FUN_0067dcc0(void);         // MessageServer
extern "C" void* __cdecl FUN_00a206f0(void);         // Audio::GetSystemAT
extern "C" void* __cdecl FUN_00b3d2c0(void);         // RelationshipManager
extern "C" void* __cdecl FUN_00b3d380(void);         // GameTimeManager
extern "C" void  __cdecl FUN_01009a40(void*, void*);
class Owner01402 {
public:
    uint32_t vtbl;    // @0x00
    uint32_t pad04;   // @0x04
    uint32_t child;   // @0x08
    void* FUN_0102b140(uint8_t flags);
};
namespace SP {
struct cSPSpaceCombatTuning {
    uint32_t vtbl;    // @0x00
    uint32_t pad04;   // @0x04
    uint32_t prop;    // @0x08  AutoRefCount<cPropertyList>
    void Init();
};
}
class VObj {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void* v14();
};
extern "C" float sinf(float);
extern "C" float cosf(float);
extern "C" float sqrtf(float);
struct MsgRC5 {
    uint32_t vtbl;      // @0x00
    uint32_t d0;        // @0x04
    uint32_t d8;        // @0x08
    uint32_t pad[9];    // @0x0c..0x2f
    uint32_t m30;       // @0x30
    uint32_t m34;       // @0x34
    uint32_t m38;       // @0x38
    void F_dstruct();   // 0x00421cf0
};
// ---- items of slice s0102af80 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void  __cdecl FUN_006a07d0(void* p, uint32_t prop, void* outCount, void* outArr);
extern "C" void  __cdecl FUN_006a12a0(void* p, uint32_t key, void* out);
extern "C" void* __cdecl FUN_00f473a0(uint32_t n, const char* name, int a, int b, const char* file, int line);
extern "C" uint32_t __cdecl FUN_011e0970(uint32_t lo, uint32_t hi, uint32_t b, uint32_t z);
extern RLC DAT_1601760;
extern Obj DAT_015b7510;
extern "C" void  __cdecl FUN_00435ed0(uint32_t, void*);

// ---- items of slice s010297e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_100;        // 0x013ec4d0
extern float g_1_1;        // 0x013ef54c
extern float g_13ec5b4;    // 0x013ec5b4
extern float g_15b7504;    // 0x015b7504
extern float g_v0, g_v1, g_v2;     // 0x015b74d0, 0x015b74d4, 0x015b74d8
extern float g_16de114;              // 0x016de114
extern float g_16de118;              // 0x016de118
extern float g_16de11c;              // 0x016de11c
extern float g_13eb1bc;              // 0x013eb1bc
extern float g_140f7ac;              // 0x0140f7ac
typedef unsigned int uint;
struct cPropertyList;
struct GetsFloat {
virtual void q0();
virtual void q1();
virtual void q2();
virtual void q3();
virtual void q4();
virtual void q5();
virtual void q6();
virtual void q7();
    virtual void q8();
    virtual bool GetProperty(uint id, void** out);       // +0x24
};
struct Prop {
    char pad[0x12];
    unsigned short type;
    float* GetFloat();   // 0x0041ea70
};
struct cPropertyList : GetsFloat {
};
struct Obj4c {   // vtable slot +0x4c returns int
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
    virtual int v4c();
};
struct Obj0c {   // vtable slot +0xc
virtual void b0();
virtual void b1();
virtual void b2();
    virtual void* v0c(int id);
};
struct Obj10 {   // vtable slot +0x10 returns int
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
    virtual int v10();
};
struct Obj38 {   // vtable slot +0x38 returns int
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
    virtual int v38();
};
struct Obj68 {   // vtable slot +0x68: bool(void*)
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
virtual void e8();
virtual void e9();
virtual void e10();
virtual void e11();
virtual void e12();
virtual void e13();
virtual void e14();
virtual void e15();
virtual void e16();
virtual void e17();
virtual void e18();
virtual void e19();
virtual void e20();
virtual void e21();
virtual void e22();
virtual void e23();
virtual void e24();
virtual void e25();
    virtual bool v68(void* id);
};
struct cSPSpaceCombatTuning_s0102_97e0 {
    char pad[8];
    cPropertyList* mPropList;
    int   GetAirRaidSirenTimeMS();  // 0x01029af0 (cSPSpaceCombatTuning::GetAirRaidSirenTimeMS)
    float GetBackgroundFighterDPS(int index);  // 0x01029cc0 (cSPSpaceCombatTuning::GetBackgroundFighterDPS)
    float GetBackgroundBomberDPS(int index);  // 0x01029d50 (cSPSpaceCombatTuning::GetBackgroundBomberDPS)
    float GetBackgroundTurretDPS(int index);  // 0x01029de0 (cSPSpaceCombatTuning::GetBackgroundTurretDPS)
    float GetLootMinMoneyDrop(int index);  // 0x01029f60 (cSPSpaceCombatTuning::GetLootMinMoneyDrop)
    float GetLootMaxMoneyDrop(int index);  // 0x01029fd0 (cSPSpaceCombatTuning::GetLootMaxMoneyDrop)
    float GetLootCityMinMoneyDrop(int index);  // 0x0102a230 (cSPSpaceCombatTuning::GetLootCityMinMoneyDrop)
    float GetLootCityMaxMoneyDrop(int index);  // 0x0102a2a0 (cSPSpaceCombatTuning::GetLootCityMaxMoneyDrop)
    float GetLootUFOMoneyChance(int type);
    float GetLootRaiderMoneyChance();        // 0x0102a090
    float GetLootBomberMoneyChance();        // 0x0102a040
    float GetLootThiefMoneyChance();         // 0x0102a180
    float GetLootDefenderMoneyChance();      // 0x0102a0e0
    float GetLootInterceptorMoneyChance();   // 0x0102a130
    int   GetWeaponLevel(float x, float y, float z);  // 0x0102a360 (cSPSpaceCombatTuning::GetWeaponLevel)
    float GetUFOHealth(int type, int index);  // 0x0102a630 (cSPSpaceCombatTuning::GetUFOHealth)
    float GetTurretHealth(int index);  // 0x0102a780 (cSPSpaceCombatTuning::GetTurretHealth)
    float LootChanceA(int type);
    float LootChanceB(int type);
};
struct cSPGameDataUFO {
    void Init(int a, int b);                                 // 0x00c3e0b0 (ret 8)
    void SetDesiredModel(void* model, bool flag);            // 0x00c37180 (ret 8)
    void SetOrientation(void* scaledNormal, void* orientation);  // 0x00c3aa40 (ret 8)
};
struct MissionVec { Obj4c** begin; Obj4c** end; Obj4c** cap; };
struct cSPMission  { Obj4c* GetTargetPlanet(); bool IsActive(); };
struct cSPMissionManager {
    MissionVec* GetMissionList();            // 0x00fedd50
};
void* StarManager();                                        // 0x00b3d2a0
void* NounManager();                                        // 0x00b3d300
void* GetPlanetModel();                                     // 0x00b3d350
void* GetUFOSimulator();                                    // 0x00ffbe50
int   GetCurrentGameMode();                                 // 0x00b5b800
void* GetMissionManager();                                  // 0x00feb9f0
void* GetPlayerHomePlanet();                                // 0x01021370
void* GetUniverseContext();                                 // 0x01021080
void* IsArchived();                                         // 0x01021240
struct GameNounMgr {
    void* GetAvatar();                                      // 0x00b1fdb0
};
void  GetPropertyAsFloatArray(cPropertyList* list, uint id, int* count, float** out);  // 0x006a08b0
void  GetPropertyAsVector3(cPropertyList* list, uint id, void* out);                    // 0x006a1110
void  CreateMinimapIcon(void* ufo, void* param);            // 0x01042080
struct TerrainSphere {
    float Clamp(unsigned id);   // 0x00c75c30
};
struct NounMgrObj {
    TerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
extern cPropertyList* g_15b7518;   // 0x015b7518
template<class T> inline const T& tmin(const T& a, const T& b) { return a < b ? a : b; }
template<class T> inline const T& tmax(const T& a, const T& b) { return a < b ? b : a; }
struct cStarManager {
    int    m_885c90();                       // 0x00885c90
    Obj4c* GetEmpireByID(int id);            // 0x00ba9370
};
struct cEmpire { bool IsHostileToPlayer(); };   // 0x00c309e0
struct Inventory;
struct SpaceGame {
    Inventory* GetPlayerInventory();   // 0x00a1ad60
};
struct Planet {
    Obj4c base;                              // vptr @0
    char pad0[0x220 - 4];
    float f220;                              // +0x220
    char pad1[0x544 - 0x224];
    void* f544;                              // +0x544
    char pad2[0x6c8 - 0x548];
    struct Creature* f6c8;                   // +0x6c8
    char pad3[0x714 - 0x6cc];
    int f714;                                // +0x714
    char pad4[0x748 - 0x718];
    float f748;                              // +0x748
};
struct Inventory {
    Obj68 base;
    bool HasItem(const void* key);           // 0x00ff3bb0
};
struct CreatureBase {
    int PlayIdleAnimation(int a, int b);   // 0x00bc96a0
};
struct Creature { char pad[8]; CreatureBase base; };
struct UFOInv { char pad[0x508]; Obj10 f508; };
struct Vec3 { float x, y, z; };
struct Vec3Holder {
    char pad[8];
    cPropertyList* mPropList;
    Vec3* f();
};
struct Obj2c {   // vtable slot +0x2c: bool()
virtual void z0();
virtual void z1();
virtual void z2();
virtual void z3();
virtual void z4();
virtual void z5();
virtual void z6();
virtual void z7();
virtual void z8();
virtual void z9();
virtual void z10();
    virtual bool pred();
};
bool FUN_01029a60(Planet* p, bool b);
struct NounMgr { Obj0c* CreateNoun(int id); };
struct SurfaceOrientation { uint32_t mWords[4]; };
struct PlanetModel {
    char pad[0x24];
    void* mpSphere;                                             // +0x24
    void GetPosition(Vec3* out);                                // 0x00b81720 (ret 4)
    void* BuildSurfaceOrientation(SurfaceOrientation* out, Vec3* in);  // 0x00b7f190 (ret 8)
};
void* MinimapIconSource();                                      // 0x010666a0
struct IconSource {
    char pad[0x31c];
    void* mpMinimapParam;                                       // +0x31c
    void* GetMinimapParam();                                    // 0x01067e60
};
struct DistObj {
    char pad[0x148];
    float f148;
    char pad2[0x1cc - 0x14c];
    float f1cc;
    float Dist() { return f1cc * f148; }   // 0x0104be30
};
// ---- items of slice s010297e0 end

// ---- items of slice s0102be20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gPosseFlockOffsets[3];
extern float gPosseRadius;
extern float gPosseAxisX;
extern float gPosseAxisY;
extern float gPosseAxisZ;
extern float gPosseScaleA;
extern float gPosseScaleB;
extern float gPosseScaleC;
extern void* gColorProperties;
typedef int intptr_t;
#define nullptr 0
struct Vec3_s0102_be20 {
    float mX;
    float mY;
    float mZ;
};
struct cObjectVector {
    void** mpBegin;                             // 0x00
    void** mpEnd;                               // 0x04
    void** mpCapacity;                          // 0x08
};
struct cIntVector {
    uint32_t* mpBegin;                          // 0x00
    uint32_t* mpEnd;                            // 0x04
    uint32_t* mpCapacity;                       // 0x08
};
struct cCreatureData {
    uint8_t mPad000[0x68c];                     // 0x000
    void* mpMission;                            // 0x68c
    uint8_t mPad690[0x04];                      // 0x690
    Vec3_s0102_be20 mPosseOffset;                          // 0x694
    Vec3_s0102_be20 mPosseAxis;                            // 0x6a0
    uint8_t mPad6ac[0x04];                      // 0x6ac
    int mnPosseIndex;                           // 0x6b0
    uint8_t mPad6b4[0x60];                      // 0x6b4
    int mnState;                                // 0x714
};
void* GetCreatureDataVector();
void* GetCombatantDataVector();
void* GetCurrentGameMode_s0102_be20();
void* BeginGameModeIteration();
void* SpaceGameGet();
void* SpaceGameGet(uint32_t nA, int nB);
void* ResolveNoun(void* pNoun);
void* GetMissionManager(void* pA);
void* GetActivePlanet();
void* RandomMath();
char ResolveSpaceObject(void* pObject);
char ResolvePlanet(void* pPlanet);
char IsTribeOwned(void* pOwner);
char CheckMissionAllowed(void* pOwner, void* pMission);
char DoMissionsPreventHostility(void* pOwner, void* pMission);
char GetPropertyAsColorRGB(void* pProperties, uint32_t nId, void* pOut);
int GetCreatureCount(void* pData);
int GetCombatantDamageState(void* pCombatant);
int GetLanguageId(void* pCreature);
int GetEmpireId(void* pCreature);
int GetLanguageOwner(int nLanguage);
int GetEmbassyData(void* pA, void* pB);
int IsCreatureComplete(void* pCreature);
uint32_t RandomUint32Uniform(void* pRandom, int nRange);
float fsinf(float fAngle);
float fcosf(float fAngle);
void ReleaseRef(void* pObject);
void* SelectCombatTargets(void* pA, void* pB);
void ClearActionGroup(int nSlot);
void ResetCreatureAction(void* pCreature);
void UpdateMissionState(void* pCreature);
void RemoveCreatureFromGroup(void* pCreature);
void RemoveNounFromManager(void* pManager, void* pNoun);
void operator_delete__(void* pMemory);
// ---- items of slice s0102be20 end

// @ 0x01029a10
bool FUN_01029a10(int empireId, int planetId)
{
    if (GetCurrentGameMode() == 0x1654c05) {
        if (empireId == -1) return false;
        if (empireId == ((cStarManager*)StarManager())->m_885c90()) return false;
        if (((cStarManager*)StarManager())->GetEmpireByID(empireId) == 0) return false;
        if (planetId == (int)GetPlayerHomePlanet()) return false;
    }
    return true;
}

// @ 0x01029a60
bool FUN_01029a60(Planet* p, bool b)
{
    bool r;
    if (p->f714 == 6) {
        r = b;
    } else {
        cEmpire* emp = (cEmpire*)((cStarManager*)StarManager())->GetEmpireByID(p->base.v4c());
        if (emp == 0 || emp->IsHostileToPlayer()) r = 1;
        else r = 0;
    }
    UFOInv* inv = (UFOInv*)((SpaceGame*)GetUFOSimulator())->GetPlayerInventory();
    if (r == 0) {
        int cur = (int)p->f544;
        if (cur == inv->f508.v10()) r = 1;
    } else {
        r = 1;
    }
    Creature* c = p->f6c8;
    if (c && c->base.PlayIdleAnimation(0x10, 0)) return false;
    return r;
}

// @ 0x01029af0
int cSPSpaceCombatTuning_s0102_97e0::GetAirRaidSirenTimeMS()
{
    float v = 0.0f;
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* p;
        if (pl->GetProperty(0x289453d, (void**)&p) && p->type == 0xd)
            v = *p->GetFloat();
    }
    return (int)(v * g_13ec5b4);
}

// @ 0x01029cc0
float cSPSpaceCombatTuning_s0102_97e0::GetBackgroundFighterDPS(int index)
{
    float result = 1.0f;
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(g_15b7518, 0x56b734f, &count, &arr);
    if (count > 0)
        result = arr[tmax(0, tmin(index, count - 1))];
    return result;
}

// @ 0x01029d50
float cSPSpaceCombatTuning_s0102_97e0::GetBackgroundBomberDPS(int index)
{
    float result = 1.0f;
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(g_15b7518, 0x56b7354, &count, &arr);
    if (count > 0)
        result = arr[tmax(0, tmin(index, count - 1))];
    return result;
}

// @ 0x01029de0
float cSPSpaceCombatTuning_s0102_97e0::GetBackgroundTurretDPS(int index)
{
    float result = 1.0f;
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(g_15b7518, 0x56b7358, &count, &arr);
    if (count > 0)
        result = arr[tmax(0, tmin(index, count - 1))];
    return result;
}

// @ 0x01029f60
float cSPSpaceCombatTuning_s0102_97e0::GetLootMinMoneyDrop(int index)
{
    if (mPropList) {
        float* arr = 0;
        int count = 0;
        GetPropertyAsFloatArray(mPropList, 0x5d23ad7, &count, &arr);
        if (count > 0)
            return arr[tmin(count - 1, index)];
    }
    return 0.0f;
}

// @ 0x01029fd0
float cSPSpaceCombatTuning_s0102_97e0::GetLootMaxMoneyDrop(int index)
{
    if (mPropList) {
        float* arr = 0;
        int count = 0;
        GetPropertyAsFloatArray(mPropList, 0x5d23ae0, &count, &arr);
        if (count > 0)
            return arr[tmin(count - 1, index)];
    }
    return 0.0f;
}

// @ 0x0102a1d0
float cSPSpaceCombatTuning_s0102_97e0::GetLootUFOMoneyChance(int type)
{
    switch (type) {
    case 4: return GetLootBomberMoneyChance();
    case 2: return GetLootRaiderMoneyChance();
    case 6: return GetLootDefenderMoneyChance();
    case 8: return GetLootInterceptorMoneyChance();
    case 5: return GetLootThiefMoneyChance();
    default: return 0.0f;
    }
}

// @ 0x0102a230
float cSPSpaceCombatTuning_s0102_97e0::GetLootCityMinMoneyDrop(int index)
{
    if (mPropList) {
        float* arr = 0;
        int count = 0;
        GetPropertyAsFloatArray(mPropList, 0x5d282ce, &count, &arr);
        if (count > 0)
            return arr[tmin(count - 1, index)];
    }
    return 0.0f;
}

// @ 0x0102a2a0
float cSPSpaceCombatTuning_s0102_97e0::GetLootCityMaxMoneyDrop(int index)
{
    if (mPropList) {
        float* arr = 0;
        int count = 0;
        GetPropertyAsFloatArray(mPropList, 0x5d282d4, &count, &arr);
        if (count > 0)
            return arr[tmin(count - 1, index)];
    }
    return 0.0f;
}

// @ 0x0102a360
int cSPSpaceCombatTuning_s0102_97e0::GetWeaponLevel(float x, float y, float z)
{
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(mPropList, 0x578e8dc, &count, &arr);
    float dist = sqrtf(y * y + x * x + z * z);
    int n = 0;
    while (count > 0) {
        count = count - 1;
        if (arr[count] > dist) ++n;
    }
    return n;
}

// @ 0x0102a3e0
Vec3* Vec3Holder::f()
{
    static Vec3 v = { g_v0, g_v1, g_v2 };
    if (mPropList)
        GetPropertyAsVector3(mPropList, 0x5f89281, &v);
    return &v;
}

// @ 0x0102a630
float cSPSpaceCombatTuning_s0102_97e0::GetUFOHealth(int type, int index)
{
    float* arr = 0;
    int count = 0;
    unsigned keys[12] = {
        0x33b0a8d, 0x578ce0c, 0x33b0a8d, 0x5d67a3a,
        0x33b0a90, 0x398f85c, 0x5d67a28, 0x33b0a8d,
        0x5d67a34, 0x33b0a8d, 0x33b0a8d, 0x640f84a
    };
    GetPropertyAsFloatArray(g_15b7518, keys[type], &count, &arr);
    if (count < 1) return g_100;
    int idx = tmin(index, count - 1);
    float mult = 1.0f;
    switch (type) {
    case 1: case 2: case 4: case 5: case 6: case 7: case 8: case 9:
        if (NounManager() && ((NounMgrObj*)NounManager())->GetCurrentTerrainSphere())
            mult = ((NounMgrObj*)NounManager())->GetCurrentTerrainSphere()->Clamp(0xbd68b7c6);
        break;
    case 3:
        mult = ((NounMgrObj*)NounManager())->GetCurrentTerrainSphere()->Clamp(0x17e57dec);
        break;
    }
    return mult * arr[idx];
}

// @ 0x0102a780
float cSPSpaceCombatTuning_s0102_97e0::GetTurretHealth(int index)
{
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(g_15b7518, 0x57e2cff, &count, &arr);
    if (count > 0)
        return arr[tmin(count - 1, index)];
    return g_100;
}

// @ 0x0102a840
float cSPSpaceCombatTuning_s0102_97e0::LootChanceA(int type)
{
    float v = 1.0f;
    uint id = 0;
    switch (type) {
    case 3:  id = 0x6259d65; break;
    case 6:  id = 0x6259d76; break;
    case 8:  id = 0x6259d7e; break;
    case 2:  id = 0x6259d90; break;
    case 1:  id = 0x6259d99; break;
    case 11: id = 0x6259da2; break;
    }
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* p;
        if (pl->GetProperty(id, (void**)&p) && p->type == 0xd)
            v = *p->GetFloat();
    }
    return v;
}

// @ 0x0102a8f0
float cSPSpaceCombatTuning_s0102_97e0::LootChanceB(int type)
{
    float v = 1.0f;
    uint id = 0;
    switch (type) {
    case 3:  id = 0x6259dc1; break;
    case 6:  id = 0x6259e0b; break;
    case 8:  id = 0x6259e11; break;
    case 2:  id = 0x6259e17; break;
    case 1:  id = 0x6259e1c; break;
    case 11: id = 0x6259e22; break;
    case 4:  id = 0x6270bf8; break;
    }
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* p;
        if (pl->GetProperty(id, (void**)&p) && p->type == 0xd)
            v = *p->GetFloat();
    }
    return v;
}

// @ 0x0102aa50
bool FUN_0102aa50(Planet* a, Planet* b, bool c)
{
    if (a && ((Obj2c*)a)->pred()) return false;
    if (b && ((Obj2c*)b)->pred()) return false;
    int bType = b->f714;
    int aType = a->f714;
    int bId = b->base.v4c();
    int aId = a->base.v4c();
    switch (bType) {
    case 0: case 3:
        if (aType == 0) return false;
        if (aType == 3) return false;
        if (FUN_01029a60(a, c)) return true;
        if (aType != 8) return false;
        if (GetUniverseContext() != 0) return false;
        if (((GameNounMgr*)IsArchived())->GetAvatar() != (void*)a->base.v4c()) return false;
        return c != 0;
    case 1:
        if (aType != 2 && aType != 4 && aType != 5 && aType != 8) return false;
        if (a->f6c8 == 0) return true;
        if (a->f6c8->base.PlayIdleAnimation(8, 0) != 0) return false;
        return true;
    case 2: case 4: case 5:
        if (b->f6c8->base.PlayIdleAnimation(0x10, 0) == 0 &&
            (aType == 0 || aType == 3) && FUN_01029a60(b, c))
            return true;
        if (aType != 6) return false;
        return bId != aId;
    case 6:
        if ((aType == 2 || aType == 4 || aType == 5) && bId != aId) {
            if (a->f6c8 == 0) return true;
            if (a->f6c8->base.PlayIdleAnimation(8, 0) == 0) return true;
        }
        if (aType != 0 && aType != 3) return false;
        return FUN_01029a60(b, c);
    case 8:
        if (aType != 0 && aType != 3) return false;
        return FUN_01029a60(b, c);
    case 11:
        if (aType == 0 || aType == 3) return true;
        return false;
    default:
        return false;
    }
}

// @ 0x0102ac50
void* SP_CreateUFOForSolarOrGalaxy(int arg1, int arg2)
{
    Obj0c* n = ((NounMgr*)NounManager())->CreateNoun(0x18ebadc);
    cSPGameDataUFO* d;
    if (n) d = (cSPGameDataUFO*)n->v0c(0xb033b403);
    else d = 0;
    d->Init(arg1, arg2);
    return d;
}

// @ 0x0102acb0
void* SP_CreateUFO(int arg1, int* arg2, Vec3* arg3)
{
    Obj0c* n = ((NounMgr*)NounManager())->CreateNoun(0x18ebadc);
    cSPGameDataUFO* d;
    if (n) d = (cSPGameDataUFO*)n->v0c(0xb033b403);
    else d = 0;
    void* emp = 0;
    if (*arg2 != -1)
        emp = ((cStarManager*)StarManager())->GetEmpireByID(*arg2);
    d->Init(arg1, (int)emp);
    bool flag;
    Vec3 tmp;
    if (arg3 == 0) {
        if (arg1 == 0) return d;
        tmp.x = -18057132.0f;
        tmp.y = 60056.777f;
        tmp.z = g_15b7504;
        arg3 = &tmp;
        flag = true;
    } else {
        flag = arg1 != 1;
    }
    d->SetDesiredModel(arg3, flag);
    if (arg1 != 0) {
        PlanetModel* pm = (PlanetModel*)GetPlanetModel();
        if (pm && pm->mpSphere) {
            Vec3 p;
            pm->GetPosition(&p);
            Vec3 scaled;
            scaled.x = p.x * g_1_1;
            scaled.y = p.y * g_1_1;
            scaled.z = p.z * g_1_1;
            SurfaceOrientation orient;
            void* orientPtr = pm->BuildSurfaceOrientation(&orient, &p);
            d->SetOrientation(&scaled, orientPtr);
        }
        if (GetCurrentGameMode() == 0x1654c05) {
            IconSource* src = (IconSource*)MinimapIconSource();
            CreateMinimapIcon(d, src->GetMinimapParam());
        }
    }
    return d;
}

// @ 0x0102adf0
bool FUN_0102adf0(Obj4c* planet)
{
    MissionVec* list = ((cSPMissionManager*)GetMissionManager())->GetMissionList();
    int n = list->end - list->begin;
    for (int i = 0; i < n; ++i) {
        cSPMission* m = (cSPMission*)list->begin[i];
        if ((Obj4c*)m->GetTargetPlanet() == planet) {
            Obj38* o = (Obj38*)m;
            if (o->v38() == 0x397bff2 || o->v38() == 0x3960c0a)
                return m->IsActive();
        }
    }
    return false;
}

// @ 0x0102ae60
bool FUN_0102ae60(Obj4c* planet)
{
    MissionVec* list = ((cSPMissionManager*)GetMissionManager())->GetMissionList();
    int n = list->end - list->begin;
    for (int i = 0; i < n; ++i) {
        cSPMission* m = (cSPMission*)list->begin[i];
        if ((Obj4c*)m->GetTargetPlanet() == planet) {
            if (((Obj38*)m)->v38() == 0x3960c0a) return m->IsActive();
        }
    }
    return false;
}

// @ 0x0102aec0
bool FUN_0102aec0(DistObj* self, Vec3* a, Vec3* b)
{
    float d = self->Dist();
    if (d == g_13eb1bc) d = g_140f7ac;
    else d = self->Dist();
    if ((g_16de114 != b->x || g_16de118 != b->y || g_16de11c != b->z) &&
        sqrtf((b->x - a->x) * (b->x - a->x) +
              (b->y - a->y) * (b->y - a->y) +
              (b->z - a->z) * (b->z - a->z)) > d)
        return true;
    return false;
}

// @ 0x0102af80
bool __cdecl FUN_0102af80(void* p1, void* p2)
{
    if (p1 != 0) {
        if (((Obj*)p1)->F_cce0()) {
            if (((Obj*)p1)->F_cdb0(p2)) {
                return true;
            }
        }
    }
    bool result = false;
    ((Obj*)FUN_01002bd0())->F_inv();
    if (FUN_010299c0()) {
        void* v = ((VObj*)((char*)((Obj*)FUN_00ffbe50())->F_inv() + 0x508))->v14();
        if (v != 0) {
            if (((Obj*)v)->F_cce0()) {
                if (((Obj*)v)->F_cdb0(p2)) {
                    return true;
                }
            }
        }
        return false;
    }
    return result;
}

// @ 0x0102b010
int __cdecl FUN_0102b010(void* p1, uint32_t param_2, uint32_t param_3)
{
    int result = 0;
    if (p1 != 0) {
        int iVar4 = ((Obj*)((Obj*)FUN_01002bd0())->F_sgd())->F_42a0();
        int local_18, local_14, local_10, local_c;
        int local_8[2];
        int param_1;
        param_1 = 0;
        local_18 = 0;
        local_10 = 0;
        local_14 = 0;
        FUN_006a07d0(p1, param_2, &local_14, &local_10);
        if (local_14 == 0xb) {
            param_1 = *(int*)(local_10 + iVar4 * 4);
        }
        local_8[0] = 0;
        local_c = 0;
        FUN_006a07d0(p1, param_3, &local_c, local_8);
        if (local_c == 0xb) {
            local_18 = *(int*)(local_8[0] + iVar4 * 4);
        }
        local_8[1] = 0;
        int* pi = &param_1;
        if (param_1 < 1) {
            pi = &local_8[1];
        }
        int iVar1 = *pi;
        int* pi2 = &local_18;
        if (local_18 <= iVar1) {
            pi2 = &param_1;
        }
        result = DAT_1601760.RandomUint32Uniform((*pi2 - iVar1) + 1) + iVar1;
    }
    return result;
}

// @ 0x0102b140
void* Owner01402::FUN_0102b140(uint8_t flags)
{
    this->vtbl = 0x1499570;
    _ReadWriteBarrier();
    uint32_t p = this->child;
    if (p != 0) {
        this->child = 0;
        ((void(__thiscall*)(uint32_t))VF(p, 4))(p);
    }
    p = this->child;
    if (p != 0) {
        ((void(__thiscall*)(uint32_t))VF(p, 4))(p);
    }
    this->vtbl = 0x1416f14;
    if ((flags & 1) != 0) {
        FUN_00f47380(this);
    }
    return this;
}

// @ 0x0102b190
void SP::cSPSpaceCombatTuning::Init()
{
    void* pm = FUN_0067de30();
    uint32_t p = this->prop;
    if (p != 0) {
        this->prop = 0;
        ((void(__thiscall*)(uint32_t))VF(p, 4))(p);
    }
    (*(void(__thiscall**)(void*, uint32_t, uint32_t, void*))(*(uint32_t*)pm + 0x2c))
        (pm, 0x9f9f0139, 0x2ae0c7e, &this->prop);
}

// @ 0x0102b1d0
int* __cdecl FUN_0102b1d0(void* param_1, int param_2, int param_3)
{
    int ctx = FUN_01021080();
    int* piVar2;
    if (ctx == 0) {
        void* key = ((Obj*)param_1)->F_26b0();
        void* sp = *(void**)((char*)param_1 + 0x84);
        piVar2 = (int*)FUN_0102acb0(3, &sp, key);
        uint32_t q = (uint32_t)piVar2[0x1a3];
        if (q != 0) {
            piVar2[0x1a3] = 0;
            ((void(__thiscall*)(uint32_t))VF(q, 4))(q);
        }
        Obj* planet = (Obj*)FUN_00b3d350();
        void* u = (void*)((float*(__thiscall*)(void*, float, float))VF((char*)piVar2 + 0x34, 0x2c))
                             ((char*)piVar2 + 0x34, 40.0f, 100.0f);
        float pos[3];
        float scaled[3];
        char buf[16];
        planet->F_81780(pos, u, DAT_01477fc0, DAT_01465544);
        scaled[0] = pos[0] * DAT_013ef54c;
        scaled[1] = pos[1] * DAT_013ef54c;
        scaled[2] = pos[2] * DAT_013ef54c;
        void* u2 = planet->F_7f190(buf, pos);
        ((Obj*)piVar2)->F_aa40(scaled, u2);
        float f = ((float)param_2 / (float)param_3) * DAT_016de6d4 * 0.5f;
        float s = sinf(f);
        float c = cosf(f);
        float qf[4];
        qf[0] = s * DAT_016de6d8;
        qf[1] = s * DAT_016de6dc;
        qf[2] = s * DAT_016de6e0;
        qf[3] = c;
        char buf2[16];
        float* quat = FUN_0059aed0(buf2, &DAT_016de6e4, qf);
        piVar2[0x1a8] = *(int*)&quat[0];
        piVar2[0x1a9] = *(int*)&quat[1];
        piVar2[0x1aa] = *(int*)&quat[2];
        piVar2[0x1a5] = *(int*)&DAT_016dc060[param_2 * 3];
        piVar2[0x1a6] = *(int*)&DAT_016dc060[param_2 * 3 + 1];
        piVar2[0x1a7] = *(int*)&DAT_016dc060[param_2 * 3 + 2];
        piVar2[0x1ac] = param_2;
        ((void(__thiscall*)(void*, void*))VF(piVar2, 0x48))(piVar2, *(void**)((char*)param_1 + 0x84));
    } else {
        if ((uint32_t)(ctx - 1) > 1) {
            return 0;
        }
        piVar2 = (int*)FUN_0102ac50(3, param_1);
        int inv = (int)((Obj*)FUN_00ffbe50())->F_inv();
        piVar2[0x1a5] = *(int*)&DAT_016dc060[param_2 * 3];
        piVar2[0x1a6] = *(int*)&DAT_016dc060[param_2 * 3 + 1];
        int iVar1 = *(int*)&DAT_016dc060[param_2 * 3 + 2];
        piVar2[0x1ac] = param_2;
        piVar2[0x1a7] = iVar1;
        float f = ((float)param_2 / (float)param_3) * DAT_016de6d4 * 0.5f;
        float s = sinf(f);
        float c = cosf(f);
        float qf[4];
        qf[0] = s * DAT_016de6d8;
        qf[1] = s * DAT_016de6dc;
        qf[2] = s * DAT_016de6e0;
        qf[3] = c;
        char buf2[16];
        float* quat = FUN_0059aed0(buf2, &DAT_016de6e4, qf);
        piVar2[0x1a8] = *(int*)&quat[0];
        piVar2[0x1a9] = *(int*)&quat[1];
        piVar2[0x1aa] = *(int*)&quat[2];
        ((void(__thiscall*)(void*, void*))VF(piVar2, 0x48))(piVar2, *(void**)((char*)param_1 + 0x84));
        void* u = (void*)((float*(__thiscall*)(void*))VF((char*)inv + 0x34, 0x2c))((char*)inv + 0x34);
        ((Obj*)((char*)piVar2 + 0x508))->F_dae0(u);
        int* pv = (int*)((float*(__thiscall*)(void*))VF((char*)inv + 0x34, 0x30))((char*)inv + 0x34);
        piVar2[0x1cc] = pv[0];
        piVar2[0x1cd] = pv[1];
        piVar2[0x1ce] = pv[2];
        piVar2[0x1cf] = pv[3];
    }
    FUN_01009a40(FUN_01002bd0(), piVar2);
    return piVar2;
}

// @ 0x0102b4f0
void __cdecl FUN_0102b4f0(int param_1, void* param_2)
{
    Obj* planet = (Obj*)FUN_00b3d350();
    void* inv = ((Obj*)FUN_00ffbe50())->F_inv();
    if (param_1 > 0) {
        int i = 0;
        do {
            void* ufo = FUN_0102acb0(0xb, DAT_0149954c, param_2);
            if (ufo != 0) {
                float pos[3];
                float scaled[3];
                char buf[16];
                planet->F_81780(pos, (char*)inv + 0x718, DAT_01477fc0, DAT_01465544);
                scaled[0] = pos[0] * DAT_013ef54c;
                scaled[1] = pos[1] * DAT_013ef54c;
                scaled[2] = pos[2] * DAT_013ef54c;
                void* u = planet->F_7f190(buf, pos);
                ((Obj*)ufo)->F_aa40(scaled, u);
                float f = (float)(i + 1) * DAT_0147c308;
                *(float*)((char*)ufo + 0x694) = DAT_016de6e4 * f;
                *(float*)((char*)ufo + 0x698) = DAT_016de6e8 * f;
                *(float*)((char*)ufo + 0x69c) = DAT_016de6ec * f;
            }
            i++;
        } while (i < param_1);
    }
}

// @ 0x0102b620
void __cdecl FUN_0102b620(void)
{
    Obj* sg = (Obj*)FUN_01002bd0();
    char* list = (char*)((Obj*)FUN_00ffbe50())->F_8db30();
    char* p1 = *(char**)list;
    for (char* p2 = p1; p2 != list; p2 = *(char**)p2) {
    }
    for (; p1 != list; p1 = *(char**)p1) {
        void* r = sg->F_4bb0(*(int*)(p1 + 8));
        if (r == 0) {
            ((Obj*)FUN_00ffbe50())->F_7b0(*(int*)(p1 + 8), 0);
        } else {
            ((Obj*)FUN_010666a0(r))->F_b500();
        }
    }
}

// @ 0x0102b690
bool __cdecl FUN_0102b690(int param_1, int param_2, uint32_t param_3)
{
    int pid = FUN_01021090();
    bool bCaptured = false;
    if (param_1 != pid && param_2 == pid) {
        ((Obj*)FUN_00b3d2c0())->F_06240(param_1, param_2, 0x57b9100, 1.0f);
        Obj* te = (Obj*)((Obj*)FUN_00b3d300())->F_7d90();
        te->F_76790(param_2, param_1);
        char c = te->F_784c0(param_1);
        bCaptured = c != 0;
        if (bCaptured) {
            te->F_75520(param_1);
        }
        ((Obj*)((Obj*)FUN_01002bd0())->F_sgd())->F_e5430(0x1b, 1);
        MsgRC5 msg;
        msg.m30 = 0xf46092da;
        msg.vtbl = 0x13eb90c;
        msg.d0 = 0;
        msg.vtbl = 0x13eb844;
        msg.m38 = 0;
        msg.d8 = param_3;
        void* ms = FUN_0067dcc0();
        ((void(__thiscall*)(void*, uint32_t, void*, int))VF(ms, 0x14))(ms, 0xf46092da, &msg, 0);
        msg.F_dstruct();
    }
    return bCaptured;
}

// @ 0x0102b780
void __cdecl FUN_0102b780(void* param_1, float* param_2)
{
    Obj* rec = *(Obj**)((char*)FUN_01021260() + 0x13c);
    if (rec->F_e040(param_1) == 0) {
        uint8_t rbuf[0x2c] = {0};
        *(void**)(rbuf + 0x00) = param_1;
        *(float*)(rbuf + 0x04) = param_2[0];
        *(float*)(rbuf + 0x08) = param_2[1];
        *(float*)(rbuf + 0x0c) = param_2[2];
        rbuf[0x28] = 1;
        uint32_t uVar1 = *(uint32_t*)((char*)rec + 0x138);
        if (uVar1 < *(uint32_t*)((char*)rec + 0x13c)) {
            *(uint32_t*)((char*)rec + 0x138) = uVar1 + 0x2c;
            if (uVar1 != 0) {
                ((Obj*)((char*)rec + 0x134))->F_9200(rbuf);
            }
        } else {
            ((Obj*)((char*)rec + 0x134))->F_b810(uVar1, rbuf);
        }
    }
    Obj* pm = (Obj*)FUN_0067de30();
    uint32_t prop = 0;
    if (prop != 0) {
        uint32_t t = prop;
        prop = 0;
        ((void(__thiscall*)(uint32_t))VF(t, 4))(t);
    }
    (*(void(__thiscall**)(void*, void*, uint32_t, void*))(*(uint32_t*)pm + 0x2c))
        (pm, param_1, 0x30608f0b, &prop);
    uint32_t key = 0;
    FUN_006a12a0((void*)prop, 0x4e3eca1, &key);
    int pe = *(int*)((char*)FUN_01021300() + 0x84);
    uint32_t key2 = 0;
    void* ufo = FUN_0102acb0(1, &pe, &key2);
    Obj* planet = (Obj*)FUN_00b3d350();
    float scaled[3];
    char buf[16];
    scaled[0] = param_2[0] * DAT_01465160;
    scaled[1] = param_2[1] * DAT_01465160;
    scaled[2] = param_2[2] * DAT_01465160;
    void* u = planet->F_7f190(buf, param_2);
    ((Obj*)ufo)->F_aa40(scaled, u);
    scaled[0] = param_2[0] * DAT_013f56a4;
    scaled[1] = param_2[1] * DAT_013f56a4;
    scaled[2] = param_2[2] * DAT_013f56a4;
    ((Obj*)ufo)->F_be70(scaled);
    float ang = (float)(DAT_1601760.RandomDoubleUniform() * 50.0);
    float clamped = 50.0f;
    if (ang < clamped) {
        clamped = ang;
        if (ang < 0.0f) {
            clamped = 0.0f;
        }
    }
    float a = clamped - 25.0f;
    *(float*)((char*)ufo + 0x694) = DAT_016de6f0 * a + DAT_016de6e4 * DAT_0147c308;
    *(float*)((char*)ufo + 0x698) = DAT_016de6f4 * a + DAT_016de6e8 * DAT_0147c308;
    *(float*)((char*)ufo + 0x69c) = DAT_016de6f8 * a + DAT_016de6ec * DAT_0147c308;
    float ang2 = (float)(DAT_1601760.RandomDoubleUniform() * 20.0 - 10.0);
    float clamped2 = 10.0f;
    if (ang2 < clamped2) {
        clamped2 = ang2;
        if (ang2 < -10.0f) {
            clamped2 = -10.0f;
        }
    }
    *(float*)((char*)ufo + 0x6ac) = clamped2;
    ((Obj*)((char*)ufo + 0x508))->F_bfc470(1);
}

// @ 0x0102ba30
void __cdecl FUN_0102ba30(uint32_t param_1, uint32_t param_2, uint32_t param_3, void* param_4)
{
    void* planetRec = FUN_010212a0();
    int iVar4 = ((int(__thiscall*)(void*))VF(param_4, 0x4c))(param_4);
    uint32_t uVar6 = 0;
    bool have = false;
    if (iVar4 != -1) {
        Obj* sm = (Obj*)FUN_00b3d2a0(iVar4);
        Obj* emp = (Obj*)sm->F_a9370(iVar4);
        if (emp != 0) {
            uVar6 = (uint32_t)emp->F_17a0();
            have = true;
        }
    }
    if (!have) {
        float* cities = ((Obj*)FUN_01021240())->F_65e0();
        uVar6 = (uint32_t)DAT_015b7510.F_2a360(cities[0], cities[1], cities[2]);
    }
    int iVar4b = ((int(__thiscall*)(void*))VF(param_4, 0x38))(param_4);
    float fMin = 0.0f;
    float fMax = 0.0f;
    if (iVar4b == (int)0xb033b403u) {
        fMin = DAT_015b7510.F_29f60((int)uVar6);
        fMax = DAT_015b7510.F_29fd0((int)uVar6);
    } else if (iVar4b == (int)0xee9b2232u) {
        fMin = DAT_015b7510.F_2a230((int)uVar6);
        fMax = DAT_015b7510.F_2a2a0((int)uVar6);
    }
    double rd = DAT_1601760.RandomDoubleUniform();
    float res = (float)(rd * ((double)fMax - (double)fMin) + (double)fMin);
    float val = fMax;
    if (res < fMax) {
        val = res;
        if (res < fMin) {
            val = fMin;
        }
    }
    int count = (int)(val * 0.04f + 0.5f) * 0x19;
    if (count > 0) {
        uint8_t rbuf[0x2c] = {0};
        *(uint32_t*)(rbuf + 0x00) = 0x2cb59744;
        *(uint32_t*)(rbuf + 0x04) = param_1;
        *(uint32_t*)(rbuf + 0x08) = param_2;
        *(uint32_t*)(rbuf + 0x0c) = param_3;
        *(uint16_t*)(rbuf + 0x10) = (uint16_t)count;
        *(uint8_t*)(rbuf + 0x12) = 7;
        Obj* gtm = (Obj*)FUN_00b3d380();
        uint64_t t = gtm->F_316c0();
        *(uint32_t*)(rbuf + 0x18) = FUN_011e0970((uint32_t)t, (uint32_t)(t >> 32), 1000, 0);
        uint32_t uVar2 = *(uint32_t*)((char*)planetRec + 0x138);
        if (uVar2 < *(uint32_t*)((char*)planetRec + 0x13c)) {
            *(uint32_t*)((char*)planetRec + 0x138) = uVar2 + 0x2c;
            if (uVar2 != 0) {
                ((Obj*)((char*)planetRec + 0x134))->F_9200(rbuf);
            }
        } else {
            ((Obj*)((char*)planetRec + 0x134))->F_b810(uVar2, rbuf);
        }
        Obj* avatar = (Obj*)((Obj*)FUN_01002bd0())->F_b1fdb0();
        int artifact = (int)avatar->F_5d20(rbuf);
        *(uint32_t*)(artifact + 0x224) = 4;
        void* loco = FUN_00f473a0(0x14, "Simulator/cDropToGroundLocomotion", 0, 0, 0, 0);
        if (loco != 0) {
            *(uint32_t*)((char*)loco + 8) = 0x13ec458;
            *(uint32_t*)((char*)loco + 0xc) = 0;
            *(uint32_t*)((char*)loco + 0) = 0x1499590;
            *(uint32_t*)((char*)loco + 8) = 0x1499580;
            *(uint32_t*)((char*)loco + 0x10) = 0;
        } else {
            loco = 0;
        }
        ((Obj*)((char*)artifact + 0x34))->F_21b0(loco);
        *(float*)(artifact + 0x660) = 0.0f;
        int* audio = (int*)FUN_00a206f0();
        int r2 = 0;
        if (audio != 0) {
            r2 = ((int(__thiscall*)(void*))VF(audio, 0x20))(audio);
        }
        FUN_00435ed0(0xa9cf08ea, (void*)r2);
    }
}

// @ 0x0102bc90
int __cdecl FUN_0102bc90(void* param_1, void* param_2, char param_3)
{
    float local_10 = 0.0f;
    int local_8 = 0;
    if (DAT_015b7518 != 0) {
        void* gm = (void*)DAT_015b7518;
        char c = ((char(__thiscall*)(void*, uint32_t, int*))VF(gm, 0x24))(gm, 0x304039c, &local_8);
        if (c != 0 && *(short*)(local_8 + 0x12) == 0xd) {
            local_10 = *((Obj*)local_8)->F_f70();
        } else {
            local_10 = 0.0f;
        }
    }
    if (*(int*)((char*)param_1 + 0x714) == 1 || param_3 != 0) {
        local_10 = DAT_0145c12c;
    }
    int local_14 = 0;
    float local_c = 0.0f;
    int* vec = ((Obj*)FUN_00b3d300())->F_21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                               (void*)FUN_00ad48b0, (void*)FUN_00b1e500, &DAT_018ebadc);
    int n = (vec[2] - vec[1]) >> 2;
    if (n > 0) {
        int i = 0;
        do {
            int obj = *(int*)(vec[1] + i * 4);
            if (!((Obj*)obj)->F_8990(1)) {
                float* pf3 = (float*)((float*(__thiscall*)(void*))VF((char*)obj + 0x34, 0x2c))((char*)obj + 0x34);
                float* pf6 = (float*)((float*(__thiscall*)(void*))VF((char*)param_1 + 0x34, 0x2c))((char*)param_1 + 0x34);
                float dx = pf6[0] - pf3[0];
                float dy = pf6[1] - pf3[1];
                float dz = pf6[2] - pf3[2];
                float d = sqrtf(dz * dz + (dy * dy + dx * dx));
                if (d <= local_10 && FUN_0102aa50((void*)obj, param_1, param_2)) {
                    if (local_14 == 0 || d < local_c) {
                        local_c = d;
                        local_14 = obj;
                    }
                }
            }
            i++;
        } while (i < n);
        if (local_14 != 0) {
            return local_14 + 0x508;
        }
    }
    return 0;
}

// @ 0x0102be20
void PositionPosseMembers()
{
    void* pManager = NounManager();
    (void)pManager;
    cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();

    int nCount = (int)(((uint8_t*)pCreatures->mpEnd - (uint8_t*)pCreatures->mpBegin) >> 2);
    int nPlaced = 0;
    int nIndex = 0;
    int nFlockCount = 0;
    (void)nPlaced;

    BeginGameModeIteration();
    void* pList = nullptr;
    (void)pList;
    for (int i = 0; i < nCount; ++i) {
        cCreatureData* pData = (cCreatureData*)pCreatures->mpBegin[i];
        if (pData->mnState != 3)
            continue;

        pData->mPosseOffset.mX = gPosseFlockOffsets[0];
        pData->mPosseOffset.mY = gPosseFlockOffsets[1];
        pData->mPosseOffset.mZ = gPosseFlockOffsets[2];
        pData->mnPosseIndex = nIndex;

        float fAngle = ((float)nIndex / (float)nFlockCount) * gPosseRadius * 0.5f;
        float fSin = fsinf(fAngle);
        float fCos = fcosf(fAngle);

        float fX = gPosseAxisX * fSin;
        float fY = gPosseAxisY * fSin;
        float fZ = gPosseAxisZ * fSin;

        pData->mPosseAxis.mX = ((fY * fZ - fCos * fX) * gPosseScaleB +
                               (fCos * fY + fX * fZ) * gPosseScaleC) * 2.0f +
                              (1.0f - (fX * fX + fZ * fZ) * 2.0f) * gPosseScaleA;
        pData->mPosseAxis.mY = ((fZ * fX - fCos * fY) * gPosseScaleB +
                               (fCos * fZ + fY * fX) * gPosseScaleC) * 2.0f +
                              (1.0f - (fZ * fZ + fY * fY) * 2.0f) * gPosseScaleA;
        pData->mPosseAxis.mZ = ((fCos * fX + fZ * fY) * gPosseScaleC +
                               (fX * fY - fCos * fZ) * gPosseScaleA) * 2.0f +
                              (1.0f - (fY * fY + fX * fX) * 2.0f) * gPosseScaleB;

        ++nIndex;
        nFlockCount = nIndex;
    }
}

// @ 0x0102c0c0
void ReleaseCreaturePosse(void* pNoun)
{
    if (pNoun == nullptr)
        return;
    if (ResolveSpaceObject(pNoun) == 0)
        return;

    cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();
    (void)pCreatures;
    cObjectVector list;
    list.mpBegin = nullptr;
    list.mpEnd = nullptr;
    list.mpCapacity = nullptr;

    int nCount = (int)(((uint8_t*)list.mpEnd - (uint8_t*)list.mpBegin) >> 2);
    for (int i = 0; i < nCount; ++i) {
        cCreatureData* pData = (cCreatureData*)(intptr_t)list.mpBegin[i];
        int nState = pData->mnState;
        if ((nState == 2 || nState == 4 || nState == 5 || nState == 0xb) &&
            IsTribeOwned(pNoun) == 0)
            ResetCreatureAction(list.mpBegin[i]);
    }
    for (void** p = list.mpBegin; p != list.mpEnd; ++p) {
        if (*p != nullptr)
            ReleaseRef(*p);
    }
    if (list.mpBegin != nullptr && ((uint32_t*)list.mpBegin)[-1] != 0)
        operator_delete__(list.mpBegin);
}

// @ 0x0102c1a0
void UpdatePosseMembers(void* pNest)
{
    ResolveNoun(pNest);
    if (ResolveSpaceObject(pNest) == 0)
        return;

    cIntVector* pList = (cIntVector*)GetCreatureCount(nullptr);
    int nCount = (int)(((uint8_t*)pList->mpEnd - (uint8_t*)pList->mpBegin) >> 2);
    int nLoop = nCount;
    for (int i = 0; i < nLoop; ++i) {
        void* pCreature = (void*)(intptr_t)pList->mpBegin[i];
        void* pMember = nullptr;
        ResolveNoun(pCreature);
        (void)pMember;
        if (ResolvePlanet(pMember) == 0) {
            ClearActionGroup(0);
            continue;
        }

        cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();
        int nCreatureCount = (int)(((uint8_t*)pCreatures->mpEnd -
                                    (uint8_t*)pCreatures->mpBegin) >> 2);
        uint32_t* pBuffer = nullptr;
        if (nCreatureCount != 0)
            pBuffer = (uint32_t*)pCreatures->mpBegin;
        cObjectVector group;
        group.mpBegin = (void**)pBuffer;
        group.mpEnd = (void**)pBuffer;

        int nGroup = (int)(((uint8_t*)group.mpEnd - (uint8_t*)group.mpBegin) >> 2);
        for (int j = 0; j < nGroup; ++j) {
            cCreatureData* pData = (cCreatureData*)(intptr_t)pBuffer[j];
            if (pData->mnState == 6 && IsTribeOwned(pMember) == 0)
                ResetCreatureAction((void*)(intptr_t)pBuffer[j]);
        }
        for (void** p = group.mpBegin; p != group.mpEnd; ++p) {
            if (*p != nullptr)
                ReleaseRef(*p);
        }
        if (pBuffer != nullptr && pBuffer[-1] != 0)
            operator_delete__(pBuffer);
        ClearActionGroup(0);
    }
}

// @ 0x0102c340
void DestroyCreature(cCreatureData* pCreature, uint32_t nFlags)
{
    void* pManager = NounManager();
    cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();
    int nCount = (int)(((uint8_t*)pCreatures->mpEnd - (uint8_t*)pCreatures->mpBegin) >> 2);

    for (int i = 0; i < nCount; ++i) {
        cCreatureData* pData = (cCreatureData*)pCreatures->mpBegin[i];
        if (pData == nullptr)
            continue;
        if (pData->mpMission != (void*)pCreature)
            continue;
        void* pMission = pData->mpMission;
        if (pMission == nullptr)
            continue;
        pData->mpMission = nullptr;
        ReleaseRef(pMission);
    }

    if (pCreature->mPad000[0] && *(int*)((uint8_t*)pCreature + 0x714) == 3) {
        (void)0;
    }
    if (*(int*)((uint8_t*)pCreature + 0x714) == 3) {
        void* pResult = ((void* (*)(void*, uint32_t))((void**)*(void**)pCreature)[0x4c >> 2])(
            pCreature, nFlags);
        BeginGameModeIteration();
        (void)pResult;
    }

    if (GetCurrentGameMode_s0102_be20() == (void*)0x01654c05) {
        void* pGame = SpaceGameGet();
        if (pGame != nullptr) {
            void* pSub = *(void**)((uint8_t*)pGame + 0x18);
            (void)pSub;
            void* pMinimap = nullptr;
            (void)pMinimap;
        }
    }

    (void)pManager;
    void* pSlot = *(void**)((uint8_t*)pCreature + 0x508);
    (void)pSlot;
    RemoveCreatureFromGroup(pCreature);
    RemoveNounFromManager(pManager, pCreature);
}

// @ 0x0102c460
cCreatureData* PickCombatTarget(cCreatureData* pCreature)
{
    void* pManager = NounManager();
    (void)pManager;
    void* pCombatants = GetCombatantDataVector();
    void* pSource = ((void* (*)(void*))((void**)*(void**)pCreature)[0x2c >> 2])(pCreature);
    (void)pSource;
    void* pResult = SelectCombatTargets(pCombatants, pSource);
    if (pResult == nullptr)
        return nullptr;

    cObjectVector list;
    list.mpBegin = nullptr;
    list.mpEnd = nullptr;
    list.mpCapacity = nullptr;
    while (list.mpBegin != list.mpEnd) {
        uint32_t nPick = RandomUint32Uniform(RandomMath(),
                                             (int)(((uint8_t*)list.mpEnd -
                                                    (uint8_t*)list.mpBegin) >> 2));
        cCreatureData* pCandidate = (cCreatureData*)list.mpBegin[nPick];
        if (GetCombatantDamageState((uint8_t*)pCandidate + 0x588) == 0) {
            if (pCandidate == nullptr) {
                UpdateMissionState(pCreature);
                return nullptr;
            }
            UpdateMissionState(pCandidate);
            return (cCreatureData*)((uint8_t*)pCandidate + 0x588);
        }
        list.mpEnd = (void**)((uint8_t*)list.mpEnd - 4);
    }
    UpdateMissionState(pCreature);
    return nullptr;
}

// @ 0x0102c600
char IsHostileToAll(void* pPlanet)
{
    if (ResolveSpaceObject(pPlanet) == 0)
        return 0;
    int nMode = GetLanguageId(nullptr);
    if (nMode != 5 && nMode != 4)
        return 0;

    cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();
    void** pBegin = pCreatures->mpBegin;
    int nCount = (int)(((uint8_t*)pCreatures->mpEnd - (uint8_t*)pBegin) >> 2);
    for (int i = 0; i < nCount; ++i) {
        void* pCreature = pBegin[i];
        void* pOwner = ((void* (*)(void*))((void**)*(void**)pCreature)[0x4c >> 2])(pCreature);
        (void)pOwner;
        int nEmpire = GetLanguageOwner(0);
        int nPlayerEmpire = GetEmpireId(nullptr);
        if (nEmpire == nPlayerEmpire)
            continue;
        if ((float)((int*)pCreature)[0x1d2] < 100.0f) {
            if (0.0f < (float)((int*)pCreature)[0x88])
                goto CheckPrevention;
            if (nEmpire != 0) {
                (void)CheckMissionAllowed((void*)(intptr_t)nEmpire, (void*)(intptr_t)nPlayerEmpire);
                if (IsCreatureComplete((void*)(intptr_t)nEmpire) != 0)
                    goto CheckPrevention;
            }
        }
        continue;

CheckPrevention:
        {
            void* pMission = nullptr;
            (void)pMission;
            void* pManager = GetMissionManager(pPlanet);
            (void)pManager;
            if (DoMissionsPreventHostility(pPlanet, (void*)0x016de144) == 0)
                return 1;
            return 0;
        }
    }
    return 0;
}

// @ 0x0102c720
char GetCreatureColorProperty(void* pUnused, void* pObject, void* pOut)
{
    (void)pUnused;
    if (GetCurrentGameMode_s0102_be20() != (void*)0x01654c05)
        return 0;
    if (pObject == nullptr)
        return 0;

    void* pType = ((void* (*)(void*))((void**)*(void**)pObject)[0x20 >> 2])(pObject);
    uint32_t nProperty = 0;
    if (pType == (void*)0x018ebadc) {
        cCreatureData* pCreature =
            (cCreatureData*)((void* (*)(void*, uint32_t))((void**)*(void**)pObject)[0xc >> 2])(
                pObject, 0xb033b403);
        if (pCreature == nullptr)
            return 0;
        if (pCreature->mnState == 0)
            return 0;
        if (pCreature->mnState == 3) {
            nProperty = 0x2587f996;
        } else {
            uint32_t nFlag = 0;
            if (GetUniverseContext() == nullptr) {
                void* pPlanet = GetActivePlanet();
                nFlag = (uint32_t)IsHostileToAll(pPlanet);
            }
            char bHostile = (char)GetEmbassyData((void*)pCreature, (void*)(intptr_t)nFlag);
            nProperty = (bHostile != 0) ? 0xc10fd3ec : 0x62872966;
        }
    } else {
        void* pPlanet = GetActivePlanet();
        char bHostile = IsHostileToAll(pPlanet);
        nProperty = (bHostile != 0) ? 0xc10fd3ec : 0x62872966;
    }

    if (gColorProperties != nullptr &&
        GetPropertyAsColorRGB(gColorProperties, nProperty, pOut) != 0)
        return 1;
    return 0;
}
