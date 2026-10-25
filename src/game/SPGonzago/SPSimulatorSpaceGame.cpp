// src/game/SPGonzago/SPSimulatorSpaceGame.cpp -- migrated from slice(s) s01399700, s01009820, s010077e0, s01006880, s01005800, s01004bb0, s01003230, s00bb9950 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSimulatorSpaceGame.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPlanetRecord.h"
#include "SP/cStarManager.h"
#include <stddef.h>
#include "SP/cCivData.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cPlanet.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cSolarSystem.h"
#include "SP/cStar.h"
#include "SP/cTerrainSphere.h"
#include <math.h>
#include "SP/cSpatialObject.h"
#include <string.h>
#pragma warning(disable: 4100)

// ---- items of slice s00bb9950 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec {              // eastl::vector, 0x14 bytes (empty allocator tail)
    void*    mpBegin;
    void*    mpEnd;
    void*    mpCapacity;
    uint32_t mAllocator0;
    uint32_t mAllocator1;

    void push_back(void* p);            // inline growth; see 0xaea5d0

    void Dtor();                        // 0xae6970
    void Erase(void* first, void* last);// 0xe25bd0
    void Reserve(int n);                // 0xd01790
    void PushBackGrow(void* p);         // 0xaea5d0
};
struct String16 {         // eastl::basic_string<wchar_t>, 0x10 bytes
    uint32_t mpBegin;
    uint32_t mpEnd;
    uint32_t mpCapacity;
    uint32_t mAllocator;
};
struct Key {              // EA::ResourceMan::Key, 0xc bytes
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
void   FUN_00f47380(void* p);                                  // operator delete[]
class cStarRecord;
class cStarRecord {
public:
    // vtable slot helpers
    int  AddRef();                                             // 0xc6a960
    int  Release();                                            // 0x7b86e0
    bool Write(void* outStream);                               // 0xbb9a70
    bool Read(void* inStream);                                 // 0xbba570
    void* AsInterface(uint32_t iid);                           // 0xbb9c70

    cStarRecord();                                             // 0xbba130
    void Dtor();                                               // 0xbba220

    // flag helpers
    String16* EnsureName();                                    // 0xbb9de0
    void SetFlags(uint32_t mask, bool on);                     // 0xbb9b00
    void SetNoMonolith();                                      // 0xbb9b30  (clear 0x4000, set 0x2000)
    bool HasRare();                                            // 0xbb9c90
    void SetBlownUp(bool on);                                  // 0xbb9c40  (bit 0x40)
    bool UpdateSETI();                                         // 0xbb9eb0
    bool HasMonolith();                                        // 0xbb9fb0
    void SetName(const String16* s);                           // 0xbba4b0
    void* GetCitizenSpecies();                                 // 0xbba500
    void OnBan();                                              // 0xbba2a0

    void CachePlanetRecords();                                 // 0xbba640
    Vec* GetPlanetRecords();                                   // 0xbba790
    bool HasActivePlanets(bool checkMission);                  // 0xbba870
    bool HasUndiscoveredPlanets();                             // 0xbba8c0
    bool HasVisitableObject();                                 // 0xbba900
    int  GetStarSystemPurchaseValue();                         // 0xbba990
    void* GetPlanetRecord(int index);                          // 0xbbaa60
    bool IsOwned();                                            // 0xbb9b70 (calls flag query)

    // data (retail offsets)
    uint32_t pad_000;      // 0x00 vftable0
    uint32_t pad_004;      // 0x04 vftable1
    uint32_t pad_008;      // 0x08
    uint32_t mLastObservedTime;        // 0x0c
    uint32_t mSavedGameVersionMajor;   // 0x10
    uint32_t mSavedGameVersionMinor;   // 0x14
    uint32_t mSavedGameTimeStamp[9];   // 0x18 (TimeStamp)
    float    mPosition[3];             // 0x3c
    int32_t  mType;                    // 0x48
    int32_t  mTechLevel;               // 0x4c
    uint8_t  field_50;                 // 0x50
    uint8_t  pad_51[3];                // 0x51
    uint32_t mEmpireID;                // 0x54
    uint32_t mStarterWorldID;          // 0x58
    uint32_t mFlags;                   // 0x5c
    String16 mName;                    // 0x60
    uint32_t mKey;                     // 0x70
    Key      mCitizenSpeciesKey;       // 0x74
    cStarRecord* mpSpeciesProfile_80;  // 0x80 (cSpeciesProfile*)
    Vec      mPlanets;                 // 0x84 (vector<cPlanetRecord*>)
    Vec      field_98;                 // 0x98
    uint8_t  mPlanetCount;             // 0xac
    uint8_t  pad_ad[3];                // 0xad
};
// ---- items of slice s00bb9950 end

// ---- items of slice s01003230 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t, void* p) { return p; }
typedef void  (__thiscall *PFNv)(void*);
typedef void  (__thiscall *PFNvi)(void*, int);
typedef void  (__thiscall *PFNvu)(void*, unsigned);
typedef void  (__thiscall *PFNvp)(void*, void*);
typedef void  (__thiscall *PFNvii)(void*, int, int);
typedef void  (__thiscall *PFNvpi)(void*, void*, int);
typedef void  (__thiscall *PFNv_di)(void*, unsigned, void*, int);
typedef void  (__thiscall *PFNvf)(void*, float);
typedef void* (__thiscall *PFNpv)(void*);
typedef void* (__thiscall *PFNpvu)(void*, unsigned);
typedef char  (__thiscall *PFNcv)(void*);
struct cSPSimulatorSpaceGame;
struct cSPUISpace {
    cSPUISpace();                              // 0x01070ba0
    void Init();                               // 0x01073700
    void OnContextDeactivate();                // 0x0106e270
    void FUN_0106f380();                       // 0x0106f380
    void FUN_01070890();                       // 0x01070890
    char mPad[0x6ac];
};
struct cCitySimulator {
    cCitySimulator();                          // 0x00ae6a70
    void AttachSubsystems();                   // 0x00ae7350
    char mPad[0x40];
};
struct SimSingleton {
    SimSingleton();                            // 0x00ae5c30
    void SetSerializer();                      // 0x00c2e4e0
    char mPad[0xc8];
};
struct cUIMissionCardPanel {
    void RefreshFromMissionList();             // 0x00e184d0
    void SetCardsVisibility(bool show);        // 0x00e14c10
};
class SpVectorF {
public:
    float x, y, z;
    SpVectorF() {}
    SpVectorF(const SpVectorF& o) { x = o.x; y = o.y; z = o.z; }
    SpVectorF(float a, float b, float c) { x = a; y = b; z = c; }
};
struct cCivData {
    SpVectorF* GetCities();                    // 0x005c65e0
};
struct cSPPlayerInventory {
    void  FUN_00ff3e80();                      // 0x00ff3e80
    char  FUN_00c37170();                      // 0x00c37170
};
struct cSPGameDataUFO {
    void SetDestinationFromCities(void* cities); // 0x00c3c360
    void PopToDestination();                     // 0x00c37e60
};
struct cTerrainSphere {
    void FUN_00c77bf0();                       // 0x00c77bf0
};
struct cStarMap {
    void FilterHelperRebuildAll();             // 0x01048ce0
};
struct cSolarSystem {
    void ActivateGraphics(int on);             // 0x00c86c70
};
struct cSimulatorUniverse {
    void AdjustAwareness(void* a, int b);      // 0x01014a80
};
struct cDirectPropertyList {
    char GetDescription(unsigned key);         // 0x006a25a0
};
struct cPlanet {
    char  _pad00[0x13c];
    void* mpCiv13c;                            // +0x13c
    int   FUN_00c70e00();                      // 0x00c70e00
    void  FUN_00c70bc0(int a);                 // 0x00c70bc0
    int   FUN_00c70880();                      // 0x00c70880
    char  FUN_00c70c00();                      // 0x00c70c00
    void  PlanetSimActivate();                 // 0x00c71e70
    void* FUN_00c71e30();                      // 0x00c71e30
    void  FUN_008414c0();                      // 0x008414c0
};
struct cStar {
    char            _pad00[0x48];
    void*           mpTime48;                  // +0x48
    float* FUN_00c8b360();                     // 0x00c8b360
    cSolarSystem* GetSolarSystem();            // 0x00c8b770
};
struct cSPCameraControllerSolarSystem {
    char  _pad00[0x68];
    float mf68;                                // +0x68
    float mf6c;                                // +0x6c
    float mf70;                                // +0x70
    char  _pad74[0x80 - 0x74];
    float mf80;                                // +0x80
    void  FUN_01017170(float v);               // 0x01017170
    void  FUN_010171b0(float v);               // 0x010171b0
    float FUN_010175b0(float v);               // 0x010175b0
};
struct H00b3d360 { void FUN_00b7dec0(); };                // 0x00b7dec0
struct H00b3d2a0 { void FUN_00bb5990(); };                // 0x00bb5990
struct H00b3d3b0 { void FUN_00b2ec80(); };                // 0x00b2ec80
struct H00b3d440 { void FUN_00b0b150(); };                // 0x00b0b150
struct H00b3d3c0 { void FUN_00b79aa0(); };                // 0x00b79aa0
struct H00b3d480 { void FUN_00acd790(); };                // 0x00acd790
struct H00b3d430 { void FUN_00bc2070(); void FUN_00bc0180(); }; // 0x00bc2070 / 0x00bc0180
struct H00b3d230 { void FUN_00b5cde0(); };                // 0x00b5cde0
struct H00b3d380 { uint64_t FUN_00b316c0(); };            // 0x00b316c0
struct H00b3d240 { float FUN_00b35fa0(); };               // 0x00b35fa0
struct H00b3d300 { void* GetCurrentTerrainSphere(); };    // 0x00f67d90 (cTerrainEditor)
struct H00b8de30  { cCivData* SortBanners(); };           // 0x00b8de30
void  FUN_00cfea20();                                     // 0x00cfea20
void* App();                                              // 0x0067dd10
void* MessageServer();                                    // 0x0067dcc0
void* EffectsManagerPtr();                                // 0x0067ddd0
void* FUN_0067dd40();                                     // 0x0067dd40
void* FUN_0067de00();                                     // 0x0067de00
void* __stdcall FUN_0067de00u(unsigned kind);             // 0x0067de00
void* FUN_0067ddc0();                                     // 0x0067ddc0
void* ModelManager();                                     // 0x0067dd80
void* FUN_0067dd50();                                     // 0x0067dd50
void* SimTicker();                                        // 0x00b3d330
cUIMissionCardPanel* FUN_00b3d400();                      // 0x00b3d400
cSPSimulatorSpaceGame* FUN_00b3d470();                    // 0x00b3d470
H00b3d360* FUN_00b3d360();                                // 0x00b3d360
H00b3d2a0* __stdcall FUN_00b3d2a0(void* planet, int flag);         // 0x00b3d2a0
H00b3d3b0* __stdcall FUN_00b3d3b0(int a);                 // 0x00b3d3b0
H00b3d440* FUN_00b3d440();                                // 0x00b3d440
H00b3d3c0* FUN_00b3d3c0();                                // 0x00b3d3c0
H00b3d480* FUN_00b3d480();                                // 0x00b3d480
H00b3d430* __stdcall TerraformingManager(void* planet, int flag);    // 0x00b3d430
H00b3d430* __stdcall TerraformingManager1(int flag);                 // 0x00b3d430
H00b3d230* __stdcall FUN_00b3d230(unsigned id);                    // 0x00b3d230
H00b3d300* __stdcall NounManager(unsigned id);                     // 0x00b3d300
H00b3d380* GameTimeManager();                             // 0x00b3d380
H00b3d240* FUN_00b3d240();                                // 0x00b3d240
void* GonzagoModelWorld();                                // 0x00b3d520
void* PlanetModel();                                      // 0x00b3d350
int   GetUniverseContext();                               // 0x01021080
void* FUN_01021230();                                     // 0x01021230
void* FUN_01021260();                                     // 0x01021260
void* FUN_01021240();                                     // 0x01021240
void  FUN_01021740(void* planet);                         // 0x01021740
void  FUN_01021960(int a);                                // 0x01021960
void  FUN_01034810();                                     // 0x01034810
void  FUN_01034950(int a, int b);                         // 0x01034950
void  FUN_01036940(SpVectorF v);                          // 0x01036940
void  FUN_01036590(void* planet);                         // 0x01036590
void  FUN_010347e0();                                     // 0x010347e0
void  FUN_01034b90(void* star);                           // 0x01034b90
void  FUN_010367e0(int a);                                // 0x010367e0
void  FUN_01036830(int a);                                // 0x01036830
void  FUN_0106f380(void* ui);                             // 0x0106f380
void  FUN_01070890(void* ui);                             // 0x01070890
void* FUN_01046fc0();                                     // 0x01046fc0
float FUN_01017030(int ctx);                              // 0x01017030
float FUN_01017070(int ctx);                              // 0x01017070
float FUN_01017010(int ctx, float f);                     // 0x01017010
void  __fastcall FUN_00ff9390(void* p);                   // 0x00ff9390
cSPSimulatorSpaceGame* GetUFOSimulator();                 // 0x00ffbe50
unsigned FNVHash(const char* s, unsigned basis, int a);   // 0x00932e80
cCitySimulator*        g_167a690;        // 0x0167a690
SimSingleton*          g_167a60c;        // 0x0167a60c
void*                  g_167ea54;        // 0x0167ea54
cDirectPropertyList*   g_15fd918;        // 0x015fd918
unsigned char          g_15b743e;        // 0x015b743e
cSimulatorUniverse*    g_16dc798;        // 0x016dc798
struct cSPSimulatorSpaceGame {
    char              _pad00[0x14];
    cSPUISpace*       mpSpaceUI;      // +0x14
    char              _pad18[0x3c - 0x18];
    float             mfCamOffset_3c; // +0x3c
    cSPPlayerInventory* mpInv_40;     // +0x40
    char              _pad44[0x4c - 0x44];
    bool              mFlag4c;        // +0x4c
    bool              mFlag4d;        // +0x4d
    bool              mFlag4e;        // +0x4e
    bool              mFlag4f;        // +0x4f
    char              _pad50[0x54 - 0x50];
    void*             mpEditorResult; // +0x54
    char              _pad58[0x6c - 0x58];
    void*             mpObj6c;        // +0x6c
    void*             mpSub70;        // +0x70
    char              _pad74[0xac - 0x74];
    void*             mpObjAC;        // +0xac
    char              _padB0[0xb4 - 0xb0];
    void*             mpSubB4;        // +0xb4
    void*             mpSubB8;        // +0xb8
    void*             mpSubBC;        // +0xbc
    void*             mpSubC0;        // +0xc0

    void  FUN_01003230();                                    // 0x01003230
    void  FUN_01003620();                                    // 0x01003620
    void  FUN_01003690();                                    // 0x01003690
    void  GalaxyContextActivate();                           // 0x01003490
    void  FUN_010039c0(cStar* star);                         // 0x010039c0
    void  ChangeCameraByOffset(float a, float b);            // 0x01003c60
    void  FUN_01034950(int a, int b);                        // 0x01034950
    void  FUN_010367e0(int a);                               // 0x010367e0
    void  FUN_01036830(int a);                               // 0x01036830
    void  FUN_01034810();                                    // 0x01034810
    void  FUN_01036940(SpVectorF v);                         // 0x01036940
    void  FUN_01036590(void* planet);                        // 0x01036590
    void  FUN_010347e0();                                    // 0x010347e0
    void  FUN_01034b90(void* star);                          // 0x01034b90
    void  SolarContextFinishActivate(float len, bool flag);  // 0x01036c20
    cSPPlayerInventory* GetPlayerInventory();                // 0x00a1ad60
};
// ---- items of slice s01003230 end

// ---- items of slice s01004bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_016dc0fc;    // cSPSimulatorSpaceGame singleton
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef unsigned int   uintptr_t;
typedef int            intptr_t;
extern u32   DAT_016dc1e0;    // k_wormhole key
void* __cdecl FUN_00ffbe50();                        // SP::GetUFOSimulator
void* __cdecl FUN_00b3d300();                        // NounManager
void* __cdecl FUN_00b67740(void*);                   // 0x00b67740
void* __cdecl FUN_00c8b770();                        // cStar::GetSolarSystem
void  __cdecl FUN_0106ab20(int);                     // 0x0106ab20
void  __cdecl FUN_0106200(void*, int);               // ToggleStarmapFilters
void  __cdecl FUN_00b22960();                        // cGameNounManager_ProcessPending
void* __cdecl FUN_00ffd710(void*);                   // 0x00ffd710
unsigned __int64 __cdecl FUN_00b316c0();             // returns u64
struct Ext {
    void* FUN_00a1ad60();                    // GetPlayerInventory
    void* FUN_00c30cb0();                    // 0x00c30cb0
    void* FUN_00b25fb0();                    // GetPlayerCivilization
    void* FUN_00bf01e0();                    // 0x00bf01e0 -> int
    void* FUN_00bef6c0();                    // 0x00bef6c0
    void* FUN_00bd9e30();                    // SP::ProfLeaveZone -> void*
    void* FUN_00b22960();                    // 0x00b22960
    void* FUN_00b8d950(int);                 // 0x00b8d950
    void* FUN_00b8de30();                    // 0x00b8de30
    int   FUN_00bbaa60(int);                 // 0x00bbaa60
    void  FUN_00bb9c40(int);                 // 0x00bb9c40
    void* FUN_00c71530();                    // 0x00c71530
    void* FUN_00e0fb50();                    // RemoveAllIcons
    void* FUN_00e0ad00(int);                 // 0x00e0ad00
    void* FUN_00e0e1a0();                    // 0x00e0e1a0
    void  FUN_0106ab20(int);                 // 0x0106ab20
    void* FUN_01067e60();                    // 0x01067e60
    void* FUN_00ff3f00();                    // 0x00ff3f00
    void* FUN_00c32cd0(void*);               // GetColor
    void* FUN_00c30c60();                    // 0x00c30c60
    void* FUN_00c31730();                    // GetHomePlanet
    void* FUN_00bb59b0(int);                 // GetOrActivatePlanet
    void* FUN_00b67740(void*);               // 0x00b67740
    void* FUN_00befee0(void*, int);          // 0x00befee0
    void* FUN_00ffd710(void*);               // 0x00ffd710
    void  FUN_00c71530b();                   // placeholder
    void* FUN_00b316c0();                    // 0x00b316c0 -> u64
    void* FUN_00c8b770();                    // GetSolarSystem
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }
struct SimGame {
    u8 raw[0x400];
    void* f4bb0(int key);
    int   f4c00();
    char  f4c30();
    void  f4c80(float* dir);
    char  f52d0(int id);
    void  f5320();
    void  f5130();
    void* f5180(int param);
    bool  f53c0(int msg, int* p);
};
void  __stdcall f50d0(int param);
bool  f53a0();
// ---- items of slice s01004bb0 end

// ---- items of slice s01005800 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01485720;    // _HK_REAL_ONE = 1.0f
extern float DAT_01495378;    // degrees->radians
typedef unsigned short u16;
typedef          int   s32;
void* __cdecl operator_new(u32 size, const char* file, int, int, int, int); // 0xf473a0
void  __cdecl operator_delete_(void*);                                      // 0xf47380
void* __cdecl SP_PropertyManager();            // 0x0067de30 SP::PropertyManager()
void* __cdecl SP_NounManager();                // 0x00b3d300 SP::NounManager()
void* __cdecl SP_GetUFOSimulator();            // 0x00ffbe50 SP::GetUFOSimulator()
void* __cdecl SP_PlanetModel();                // 0x00b3d350 SP::PlanetModel()
void* __cdecl SP_GetActivePlanet();            // 0x01021260 ?FUN_01021260@@YAPAXXZ
void* __cdecl FUN_00b5b6c0(void* self);        // 0x00b5b6c0 cGonzagoSimulator ctor
void* __cdecl FUN_00b63890(void* self);        // 0x00b63890 cGonzagoTimer ctor
void  __cdecl FUN_00bc30f0(void* self);        // 0x00bc30f0 cSPTimer::Start
void* __cdecl FUN_00fe68a0(void* self);        // 0x00fe68a0 (sub-object ctor)
static void* TC_b5b6c0(void* s){ return ((void*(__thiscall*)(void*))FUN_00b5b6c0)(s); }
static void* TC_b63890(void* s){ return ((void*(__thiscall*)(void*))FUN_00b63890)(s); }
static void  TC_bc30f0(void* s){ ((void(__thiscall*)(void*))FUN_00bc30f0)(s); }
static void* TC_fe68a0(void* s){ return ((void*(__thiscall*)(void*))FUN_00fe68a0)(s); }
void* __cdecl FUN_00760c00(void* self);        // 0x00760c00 (sub-object ctor)
void* __cdecl FUN_00b60070(void* self);        // 0x00b60070 (sub-object ctor)
void  __cdecl FUN_0061df40(void*);             // 0x0061df40 AutoRefCount ctor
void* __cdecl FUN_00572660(void* dst, void* src); // 0x00572660 AutoRefCount ctor
void* __cdecl FUN_00454cb0(void* dst, void* src); // 0x00454cb0 eastl string assign (2-arg form)
static void StrAssign(void* self, void* begin, void* end) {
  ((void(__thiscall*)(void*, void*, void*))FUN_00454cb0)(self, begin, end);
}
void  __cdecl FUN_00475ab0(void* self, u32 n);    // 0x00475ab0 eastl string RangeInitialize (this=+0, n on stack)
void* __cdecl memcpy(void* dst, const void* src, u32 n); // 0x011e0744 memcpy
void* __cdecl FUN_0067dd60();                  // 0x0067dd60 singleton
void* __cdecl FUN_0067cab0();                  // 0x0067cab0 singleton
void* __cdecl FUN_00675250(u32 id);            // 0x00675250 Achievements::Controller()
bool  __cdecl FUN_00675e80(void* self, u32 id);// 0x00675e80 Achievement has-check
void  __cdecl FUN_00676710(void* self, u32 id);// 0x00676710 AwardAchievement
void* __cdecl FUN_00556440(void*, void*, void*, void*); // 0x00556440
void  __cdecl FUN_00c75cc0(u32, void*);        // 0x00c75cc0
void  __cdecl FUN_00e39ab0(u32, u32, void*, void*, u32, u32, void*, void*); // 0x00e39ab0
bool  __cdecl FUN_00685520(int);               // 0x00685520 IsWorldLayoutFlagSet
void* __cdecl FUN_00fd9c60();                  // 0x00fd9c60
void  __cdecl FUN_00fde3e0(void* self);        // 0x00fde3e0 TransitionFromPlanetToSolar
void  __cdecl FUN_00fdbf90(void* self);        // 0x00fdbf90 AwardSpaceAchievements
void  __cdecl FUN_00801360(void* self);        // 0x00801360 Show
void  __cdecl FUN_00801380(void* self);        // 0x00801380 Hide
bool  __cdecl FUN_01044920();                  // 0x01044920
bool  __cdecl FUN_00ffc5b0(void* self);        // 0x00ffc5b0
void  __cdecl FUN_00b7daf0(void* self);        // 0x00b7daf0
void* __cdecl FUN_00b3d360(void* p);           // 0x00b3d360
float __cdecl FUN_00ffda80(void* self);        // 0x00ffda80 CalculateMaxEnergy
float __cdecl FUN_00ffd8e0(void* self);        // 0x00ffd8e0 CalculateMaxHealth
void* __cdecl FUN_00c30c80(void* self);        // 0x00c30c80
void* __cdecl FUN_00c707e0(void* self);        // 0x00c707e0 cPlanet::GetName
void* __cdecl FUN_00b3d390(void* a, void* b);  // 0x00b3d390 vector::erase
bool  __cdecl FUN_0104e340(void* self, u32 id); // 0x0104e340 CreateToolFromToolID
void* __cdecl FUN_00f67d90(void* self);        // 0x00f67d90 GetCurrentTerrainSphere
void* __cdecl FUN_00555e80(void* a, void* b);  // 0x00555e80 vector append
void  __cdecl FUN_00760fd0(void* self, u32 a, u32 b, u32 c); // 0x00760fd0 listener add
void* __cdecl FUN_00576650(void* self, void* a); // 0x00576650 GetImageResource
void* __cdecl FUN_0093c570(void* a, void* b);  // 0x0093c570 EA::ConvertToString8
void* __cdecl FUN_01021300();                  // 0x01021300 ?FUN_01021300@@YAPAXXZ
void* __cdecl FUN_0040cf10(u32 a, u32 b, void* out); // 0x0040cf10 SP::GetPropertyT<int>
void* __cdecl FUN_0041ea70();                  // 0x0041ea70 Property::GetFloat
extern u32 DAT_016dc648, DAT_016dc64c, DAT_016dc650, DAT_016dc654, DAT_016dc658,
    DAT_016dc65c, DAT_016dc660, DAT_016dc664, DAT_016dc668, DAT_016dc66c,
    DAT_016dc670, DAT_016dc674, DAT_016dc678, DAT_016dc67c, DAT_016dc680,
    DAT_016dc684, DAT_016dc688, DAT_016dc68c, DAT_016dc690, DAT_016dc694,
    DAT_016dc698, DAT_016dc69c, DAT_016dc6a0, DAT_016dc6a4, DAT_016dc6a8,
    DAT_016dc6ac, DAT_016dc6b0;
extern u32 DAT_016dc794;      // initialised flag
extern u32 DAT_016dc728[30];  // 10 tool ids * 3 u32 = 0x78 bytes
// ---- items of slice s01005800 end

// ---- items of slice s01006880 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl FUN_01005320(void* self);              // 0x01005320 SimGame::f5320
void* __cdecl FUN_006fab90(void* a, void* b);        // 0x006fab90 SP::cFragmentDecl::~cFragmentDecl
void* __cdecl FUN_00b638b0(void* self);              // 0x00b638b0 cGonzagoTimer::~cGonzagoTimer
void* __cdecl FUN_00ae6970(void* self);              // 0x00ae6970 vector dtor
void  __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e); // 0x00571db0 EA::Messaging::RemoveHandler
void* __cdecl FUN_00b3d330();                        // 0x00b3d330 SP::SimTicker
void* __cdecl FUN_00f473a0(u32 size, const char*, int, int, int, int); // 0x00f473a0 operator new
void* __cdecl FUN_00fe4fa0(void* self);              // 0x00fe4fa0 cSPBadgeManager ctor
void* __cdecl FUN_00ae6a70(void* self);              // 0x00ae6a70 cCitySimulator ctor
void* __cdecl FUN_00ae7350(void* self);              // 0x00ae7350 cCitySimulator::AttachSubsystems
void* __cdecl FUN_010154f0(void* self);              // 0x010154f0 cSimulatorUniverse ctor
void* __cdecl FUN_00b6f4c0(void* self);              // 0x00b6f4c0
void* __cdecl FUN_01000740(void* self);              // 0x01000740 cSPSimulatorPlayerUFO ctor
void* __cdecl FUN_00ffc160(void* a, void* b, void* c);// 0x00ffc160
void* __cdecl FUN_00fecc90(void* self);              // 0x00fecc90
void* __cdecl FUN_00fedb50(void* self);              // 0x00fedb50 cSPMissionManager::InitForGame
void* __cdecl FUN_010164d0(void* self);              // 0x010164d0 cSPSimulatorWalkAround ctor
void* __cdecl FUN_01015f50(void* self);              // 0x01015f50
void* __cdecl FUN_00579a90(void* self, const void* wstr); // 0x00579a90 eastl::wstring::range_initialize
void* __cdecl FUN_00d0d200(void* self);              // 0x00d0d200 Simulator::cCommunityEditor ctor
void* __cdecl FUN_00d0a760(void* self, void* a, u32 b, void* c, void* d); // 0x00d0a760 cCommunityEditor::Init
void* __cdecl FUN_00ff5190(void* self);              // 0x00ff5190 Simulator::cPlayerInventory ctor
void* __cdecl FUN_00883860();                        // 0x00883860 EA::Messaging::GetServer
void* __cdecl FUN_01070ba0(void* self);              // 0x01070ba0 cSPUISpace ctor
void* __cdecl FUN_01073700(void* self);              // 0x01073700 cSPUISpace::Init
void* __cdecl FUN_010762e0(void* self);              // 0x010762e0
void* __cdecl FUN_01075490(void* self);              // 0x01075490
void* __cdecl FUN_00b22960(void* self);              // 0x00b22960 cGNM2::ProcessPending
void* __cdecl FUN_00a1ad60(void* self);              // 0x00a1ad60 GetPlayerInventory
void* __cdecl FUN_00c37180(void* self, void* a, int b); // 0x00c37180 cSPGameDataUFO::SetDesiredModel
void* __cdecl FUN_00fe7160(void* self);              // 0x00fe7160
void* __cdecl FUN_00bc3130(void* self);              // 0x00bc3130 cSPTimer::Restart
void* __cdecl FUN_010060d0(void* self);              // 0x010060d0 cSPSimulatorSpaceGame::ConfigUpdated
void* __cdecl FUN_00c75a50(void* self);              // 0x00c75a50
void* __cdecl FUN_01005d80(void* self, int a, int b); // 0x01005d80
void* __cdecl FUN_008de1a0();                        // 0x008de1a0 ObjectError
void* __cdecl FUN_00926020(int a, u32 b, int c, int d, int e, int f); // 0x00926020 ZoneObject_new
void* __cdecl FUN_00998820(void* self);              // 0x00998820
void* __cdecl FUN_0067dcd0();                        // 0x0067dcd0 GetManager
void* __cdecl FUN_00b6a530();                        // 0x00b6a530
void* __cdecl FUN_00ff5b50(void* self);              // 0x00ff5b50
void* __cdecl FUN_00ffbf60(void* self);              // 0x00ffbf60
void* __cdecl FUN_00feb9f0();                        // 0x00feb9f0 SP::GetMissionManager
void* __cdecl FUN_00fee310(void* self);              // 0x00fee310
void* __cdecl FUN_00e184d0(void* self);              // 0x00e184d0
void* __cdecl FUN_00685520_s0100_6880(int flag);                // 0x00685520 IsWorldLayoutFlagSet
void* __cdecl FUN_00b3d400_s0100_6880();                        // 0x00b3d400
void* __cdecl FUN_00c32980(void* self);              // 0x00c32980
void* __cdecl FUN_0102b620();                        // 0x0102b620
float __cdecl FUN_00c3ae70();                        // 0x00c3ae70
void* __cdecl FUN_0059aed0(void* out, void* a, void* b); // 0x0059aed0
void* __cdecl FUN_00c3bfe0(void* self, void* v);     // 0x00c3bfe0 cSPGameDataUFO::SetDestination
void* __cdecl FUN_00b3d2a0(void* a);                 // 0x00b3d2a0 SP::StarManager
void* __cdecl FUN_00ba9370(void* self, void* a);     // 0x00ba9370 cStarManager::GetEmpireByID
void* __cdecl FUN_00c309e0(void* self);              // 0x00c309e0 cEmpire::IsHostileToPlayer
// ---- items of slice s01006880 end

// ---- items of slice s010077e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float   kDist100;         // 0x015b6888  100.0f
extern const float   kDist1000;        // 0x015b688c  1000.0f
extern const float   kDist500;         // 0x015b6890  500.0f
extern const float   kDist5;           // 0x015b6894  5.0f
extern const float   kNearTargetDist;  // 0x015b6898  state-6 approach threshold
extern const float   kNearPosDist;     // 0x01477fc0  300.0f
extern const float   kOrbitSpeed;      // 0x016dc720  per-UFO orbit angle seed scale
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
extern const Vector3 kYAxis;           // 0x015b64c4  (0,1,0)
extern const Vector3 kZAxis;           // 0x015b64d0  (0,0,1)
extern const Vector3 kChaseOffset;     // 0x016dc100  solar->galaxy destination offset
struct cSPGameDataUFO_s0100_77e0;
struct cCreatureData;
class cSpatialObject {
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
    virtual const Vector3* GetPosition();              // +0x2c
virtual void v30();
virtual void v34();
    virtual void SetPosition(const Vector3* pPos);     // +0x38
    virtual void v3c();
    virtual void Notify();                             // +0x40
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void GetPositionOut(Vector3* pOut);        // +0x5c
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
virtual void vA0();
virtual void vA4();
virtual void vA8();
    virtual void* GetTarget();                         // +0xac
};
class cSPGameDataUFO_s0100_77e0 {
public:
    virtual int  AddRef();                // +0x00
    virtual int  Release();               // +0x04
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void v28();
    virtual bool IsDestroyed();           // +0x2c

    // non-virtual interface (direct calls in the retail image)
    void SetDestination(const Vector3* pDest);       // 0x00c3bfe0
    void SetDestinationOffset(const Vector3* pOff);  // 0x00c381e0
    void PopToDestination();                         // 0x00c37e60
    void FlyTowards(const Vector3* pDest);           // 0x00c3dae0
    void OnContextChange(int context);               // 0x00c3a2b0
    bool FUN_00c370e0();                             // 0x00c370e0  post-flag retask test

    // data: the only virtual storage is the single vptr
    char            mPad04[0x34 - 0x04];
    cSpatialObject  mSpatial;          // +0x34
    char            mPad38[0x68c - 0x38];
    cSPGameDataUFO_s0100_77e0* mpCached68c;       // +0x68c  interceptor's cached player
    Vector3         mDir694;           // +0x694  heading / approach direction
    int             mAngleSeed6b0;     // +0x6b0  orbit phase seed
    Vector3         mVec6bc;           // +0x6bc  fallback destination
    char            mPad6c8[0x714 - 0x6c8];
    unsigned int    mState;            // +0x714  chase state (3..9)
    Vector3         mPos718;           // +0x718  current position
    char            mPad724[0x730 - 0x724];
    Quaternion      mOrientation;      // +0x730
    Vector3         mOffset740;        // +0x740
    char            mPad74c[0x750 - 0x74c];
    Vector3         mTargetPos750;     // +0x750
    void*           mp75c;             // +0x75c  host object, null <=> "no host"
    char            mPad760[0x77e - 0x760];
    bool            mb77e;             // +0x77e
    char            mPad77f[0x7b0 - 0x77f];
    void*           mp7b0;             // +0x7b0  record whose dword at +0x70 is a handle
};
class cStar_s0100_77e0 {
public:
    bool   FUN_00c8b800();          // 0x00c8b800  refcount-based "background busy" test
    cStar_s0100_77e0* GetSolarSystem();        // 0x00c8b770
    float  FUN_00c84d40(int arg);   // 0x00c84d40  returns a float in st(0), ret 4
};
class cStarMap_s0100_77e0 {
public:
    void RemoveVisual(unsigned int handle, unsigned int visualId, int a, int b); // 0x01045ae0
};
class cActivePlanet {
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
    virtual const Vector3* GetPosition();     // +0x2c
};
class cCivData_s0100_77e0 {
public:
    Vector3* GetCities();            // 0x005c65e0  lea eax,[ecx+0x3c]; ret
};
class cSPUIMinimapWin {
public:
    void RemoveIcon(cSPGameDataUFO_s0100_77e0* pUfo, int a, int b);   // 0x00e0f9c0  ret 0xc
};
class cSpaceUI {
public:
    cSPUIMinimapWin* GetMinimap();   // 0x01067e60  returns this->mpMinimap (+0x31c)
};
cStar_s0100_77e0*         GetBackgroundSim();       // 0x01021230
cStarMap_s0100_77e0*      GetStarMap();             // 0x01046fc0
cCivData_s0100_77e0*      GetCurrentStar();         // 0x01021240
cActivePlanet* GetActivePlanet();        // 0x01021260
void  DestroyCreature(cCreatureData* cr, unsigned int flags);            // 0x0102c340
void  CreateMinimapIcon(cSPGameDataUFO_s0100_77e0* pUfo, cSPUIMinimapWin* pWin);    // 0x01042080
void  QuaternionFromFacingAndUp(Quaternion* pOut, const Vector3* pFacing, const Vector3* pUp);
Vector3* QuatRotateAxis(Vector3* pOut, const Vector3* pAxis, const float* pQuat); // 0x0059aed0
Vector3* RandomDirection3(Vector3* pOut);                                // 0x00b7e560
class cSPSimulatorSpaceGame_s0100_77e0 {
public:
    cSPGameDataUFO_s0100_77e0* GetPlayerInventory();        // 0x00a1ad60
    void BeginChase(int mode);                   // 0x00ffe3a0
    void UpdatePosseUFO(cSPGameDataUFO_s0100_77e0* pUfo, unsigned int id,
                        float a, float b, float c);                 // 0x01006a40
    bool UpdateInterceptorUFO(cSPGameDataUFO_s0100_77e0* pUfo, bool flag);     // 0x01003df0

    void ChaseFromGalaxyToSolar();               // 0x010077e0  (this file)
    void ChaseFromSolarToPlanet();               // 0x01007bf0
    void ChaseFromPlanetToSolar();               // 0x01007ed0
    void ChaseFromSolarToGalaxy();               // 0x01008100
    void UpdateChasingUFOs(unsigned int param);  // 0x01008270

    char              mPad00[0x14];
    cSpaceUI*         mpSpaceUI;      // +0x14
    char              mPad18[0x78 - 0x18];
    cSPGameDataUFO_s0100_77e0**  mUFOsBegin;     // +0x78
    cSPGameDataUFO_s0100_77e0**  mUFOsEnd;       // +0x7c
};
cSPSimulatorSpaceGame_s0100_77e0* GetUFOSimulator_s0100_77e0();        // 0x00ffbe50
struct UFOElem {
    virtual void v00();                // +0x00
    virtual void v04();                // +0x04
    virtual void Destroy(int flags);   // +0x08
    char         mPad0c[0x0c - 0x04];
    void*        mpLink0c;             // +0x0c
    void*        mpLink10;             // +0x10
};
struct UFOArray {
    UFOElem* mpBegin;             // +0x00
    UFOElem* mpEnd;               // +0x04
    UFOElem* mpCap;               // +0x08
    UFOElem* erase(UFOElem* first, UFOElem* last);  // 0x01008850
};
// ---- items of slice s010077e0 end

// ---- items of slice s01009820 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void VT_08_1(void* p, int a) { ((void (__thiscall*)(void*, int))(*(void***)p)[2])(p, a); }
void __cdecl FUN_01008820(void* dst, void* src, void* arg);  // 0x01008820
struct cObjectList {
    u8*   mpBegin;                                 // 0x00
    u8*   mpEnd;                                   // 0x04

    void* EraseFront(u8* p);                       // 0x01009ab0
};
// ---- items of slice s01009820 end

// ---- items of slice s01399700 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct PropDesc {
    const char* name;    // +0x00
    uint        hash;    // +0x04
    uint        offset;  // +0x08
    uint        f0c;     // +0x0c  (uninitialised in the original)
    uint        f10;     // +0x10  (uninitialised in the original)
    uint        f14;     // +0x14  (uninitialised in the original)
    void*       f18;     // +0x18
    void*       f1c;     // +0x1c
    void*       f20;     // +0x20
    void*       f24;     // +0x24
    void*       f28;     // +0x28
    void*       f2c;     // +0x2c
    void*       f30;     // +0x30
    void*       f34;     // +0x34
    void*       f38;     // +0x38
};
extern PropDesc g_props_d420[6];    // 0x15b6618  (stride 0x3c)
void FUN_00692ca0();
void FUN_00692fb0();
void FUN_00ac8050();
void FUN_00aca730();
void FUN_00ae3310();
void FUN_00ae3470();
void FUN_00ae3490();
void FUN_00b6f550();
void FUN_00b6f860();
void FUN_00bca960();
void FUN_00c2e4e0();
void FUN_00c51440();
void FUN_00c6c390();
void FUN_00fd9e80();
void FUN_01002e30();
void FUN_01005360();
void FUN_010061f0();
void FUN_01006220();
void FUN_01006250();
void FUN_01006600();
void FUN_01008680();
void FUN_0100a640();
// ---- items of slice s01399700 end

// @ 0x00bba2a0
void cStarRecord::OnBan()
{
    int mode = mTechLevel - 2;
    uint32_t key = 0;
    void* empire = 0;
    if (mode == 0) {
        key = 0x876201aa;
    } else if (mode == 2) {
        key = 0xefc33700;
    } else if (mode == 3) {
        void* sm = ((void*(__cdecl*)(uint32_t))0xb3d2a0)(mEmpireID);
        empire = ((void*(__thiscall*)(void*))0xba9370)(sm);
        key = 0xfc5a17bc;
    } else {
        mCitizenSpeciesKey.instanceID = 0;
        mCitizenSpeciesKey.typeID = 0;
        mCitizenSpeciesKey.groupID = 0;
        mpSpeciesProfile_80 = 0;
        return;
    }

    int count = 0x64;
    uint32_t ki = 0;
    uint32_t kj = 0;
    uint32_t kk = 0;
    void* node = 0;
    ((void*(*)())0xb3d450);            // keep source shape
    uint32_t mgr = ((uint32_t(*)())0xb3d450)();

    for (;;) {
        if (ki != 0) {
            if (ki != mCitizenSpeciesKey.instanceID) break;
            if (kj != mCitizenSpeciesKey.typeID) break;
            if (kk != mCitizenSpeciesKey.groupID) break;
        }
        if (--count < 0) break;

        void* species;
        if (node != 0)
            species = ((void*(__cdecl*)(uint32_t))0xac1190)(*(uint32_t*)((char*)node + 0x58));
        else
            species = ((void*(__cdecl*)(void*))0xac10a0)(empire);
        if (species == 0) break;

        String16 name;
        name.mpBegin = 0x1667bac;
        name.mpEnd = 0x1667bac;
        name.mpCapacity = 0x1667bae;
        ((void(__thiscall*)(void*, String16*))0x4da330)(species, &name);

        void* sm = ((void*(__cdecl*)(void*))0xb3d2a0)(&name);
        if (!((bool(__thiscall*)(void*, String16*))0xbaf5d0)(sm, &name)) {
            void* sm2 = ((void*(__cdecl*)(void*))0xb3d2a0)(&name);
            ((void(__thiscall*)(void*, String16*))0xbb5b50)(sm2, &name);
            kk = *(uint32_t*)((char*)species + 0x50c);
            ki = *(uint32_t*)((char*)species + 0x504);
            kj = *(uint32_t*)((char*)species + 0x508);
        }
        int len = (int)(name.mpEnd - name.mpBegin) & 0xfffffffe;
        if (len <= 2) continue;
        if (name.mpBegin == 0) continue;
        FUN_00f47380((void*)name.mpBegin);
    }

    if (ki != 0 && (ki != mCitizenSpeciesKey.instanceID || kj != mCitizenSpeciesKey.typeID
                    || kk != mCitizenSpeciesKey.groupID)) {
        if (node == 0) {
            mCitizenSpeciesKey.instanceID = 0;
            mCitizenSpeciesKey.typeID = 0;
            mCitizenSpeciesKey.groupID = 0;
            mpSpeciesProfile_80 = 0;
            return;
        }
    } else {
        void* species;
        if (node != 0)
            species = ((void*(__cdecl*)(uint32_t))0xac1190)(*(uint32_t*)((char*)node + 0x58));
        else
            species = ((void*(__cdecl*)(void*))0xac10a0)(empire);
        if (species == 0) {
            mCitizenSpeciesKey.typeID = 0;
            mCitizenSpeciesKey.groupID = 0;
            mCitizenSpeciesKey.instanceID = 0;
            mpSpeciesProfile_80 = 0;
            return;
        }
        ki = *(uint32_t*)((char*)species + 0x504);
        kj = *(uint32_t*)((char*)species + 0x508);
        kk = *(uint32_t*)((char*)species + 0x50c);
        node = species;
    }

    bool tech5 = (mTechLevel == 5);
    mCitizenSpeciesKey.instanceID = ki;
    mCitizenSpeciesKey.typeID = kj;
    mCitizenSpeciesKey.groupID = kk;
    mpSpeciesProfile_80 = (cStarRecord*)node;
    (void)tech5; (void)key;
    if (tech5 && empire != 0)
        ((void(__thiscall*)(void*, void*))0xc33690)(empire, node);
}

// @ 0x01003230
void cSPSimulatorSpaceGame::FUN_01003230()
{
    void* ticker = SimTicker();                              // 0x00b3d330
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, this);
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSub70);
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSubB8);

    cCitySimulator* sim = g_167a690;
    if (sim == 0)
        g_167a690 = new ("Simulator/SimSingleton", 0, 0, 0, 0) cCitySimulator();
    g_167a690->AttachSubsystems();                           // 0x00ae7350

    cCitySimulator* sim2 = g_167a690;
    if (sim2 == 0)
        g_167a690 = new ("Simulator/SimSingleton", 0, 0, 0, 0) cCitySimulator();
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, g_167a690);

    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSubC0);
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSubB4);
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSubBC);

    if (mpSpaceUI == 0) {
        cSPUISpace* ui = new ("Simulator", 0, 0, 0, 0) cSPUISpace();
        cSPUISpace* old = mpSpaceUI;
        if (ui != old) {
            if (ui != 0)
                (*(PFNv*)((char*)*(void**)ui + 0x00))(ui);
            mpSpaceUI = ui;
            if (old != 0)
                (*(PFNv*)((char*)*(void**)old + 0x04))(old);
        }
        mpSpaceUI->Init();                                   // 0x01073700
        if (mpEditorResult != 0)
            FUN_00ff9390(mpEditorResult);                    // 0x00ff9390
    }

    cUIMissionCardPanel* panel = FUN_00b3d400();             // 0x00b3d400
    if (panel != 0) {
        panel->RefreshFromMissionList();                     // 0x00e184d0
        panel->SetCardsVisibility(true);                     // 0x00e14c10
    }
    void* sys = g_167ea54;
    (*(PFNvu*)((char*)*(void**)sys + 0x30))(sys, 0x74d2735b);
}

// @ 0x010033a0
void UpdateSound()
{
    void* app = App();                                       // 0x0067dd10
    void* frame = (*(PFNpv*)((char*)*(void**)app + 0x50))(app);
    void* mode  = (*(PFNpv*)((char*)*(void**)frame + 0x38))(frame);
    if (mode == 0)
        return;
    cSPCameraControllerSolarSystem* cam =
        (cSPCameraControllerSolarSystem*)(*(PFNpvu*)((char*)*(void**)mode + 0x0c))(mode, 0x303154cc);
    if (cam == 0)
        return;

    int ctx = GetUniverseContext();                          // 0x01021080
    float lo = FUN_01017030(ctx);                            // 0x01017030
    float hi = FUN_01017070(ctx);                            // 0x01017070
    float v = cam->mf68;                                     // +0x68
    if (v < lo) v = lo;
    if (v > hi) v = hi;
    float t = (v - lo) / (hi - lo) * 0.5f + (float)(ctx - 1) * 0.5f;
    void* msg = MessageServer();                             // 0x0067dcc0
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x1959007, &t, 0);
}

// @ 0x01003490
void cSPSimulatorSpaceGame::GalaxyContextActivate()
{
    if (mpInv_40 != 0)
        mpInv_40->FUN_00ff3e80();                            // 0x00ff3e80
    void* msg = MessageServer();                             // 0x0067dcc0
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x279a680, 0, 0);

    FUN_00b3d470()->FUN_010367e0(1);                         // 0x010367e0
    FUN_00b3d470()->FUN_01036830(1);                         // 0x01036830
    FUN_00b3d470()->FUN_01034950(3, -1);                     // 0x01034950

    cSPSimulatorSpaceGame* sim = FUN_00b3d470();
    char* slotAC = (char*)sim + offsetof(cSPSimulatorSpaceGame, mpObjAC); // +0xac
    void* ac = *(void**)slotAC;
    (*(PFNvi*)((char*)*(void**)ac + 0x0c))(ac, 0);

    FUN_01021960(2);                                         // 0x01021960
    void* o = FUN_0067de00();                                // 0x0067de00
    char* slotE0 = (char*)*(void**)o + 0xe0;
    (*(PFNvi*)slotE0)(o, GetUniverseContext());

    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x12, 1);
    void* d1 = FUN_0067dd40();                               // 0x0067dd40
    (*(PFNvi*)((char*)*(void**)d1 + 0x100))(d1, 1);
    void* d2 = FUN_0067dd40();
    (*(PFNvi*)((char*)*(void**)d2 + 0x108))(d2, 1);

    cCivData* civ = (cCivData*)FUN_01021240();               // 0x01021240
    SpVectorF* p = civ->GetCities();                         // 0x005c65e0
    FUN_00b3d470()->FUN_01036940(*p);                        // 0x01036940

    cSPSimulatorSpaceGame* ufo = GetUFOSimulator();          // 0x00ffbe50
    cSPGameDataUFO* inv = (cSPGameDataUFO*)ufo->GetPlayerInventory(); // 0x00a1ad60
    inv->SetDestinationFromCities(civ);                      // 0x00c3c360
    inv->PopToDestination();                                 // 0x00c37e60

    H00b3d300* te = NounManager(0x574ac68);                  // 0x00b3d300
    cTerrainSphere* ts = (cTerrainSphere*)te->GetCurrentTerrainSphere(); // 0x00f67d90
    ts->FUN_00c77bf0();                                      // 0x00c77bf0

    msg = MessageServer();
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x248976a, 0, 0);
    mpSpaceUI->FUN_01070890();                               // 0x01070890

    void* sys = g_167ea54;
    (*(PFNvu*)((char*)*(void**)sys + 0x30))(sys, 0x74d2735b);

    cStarMap* map = (cStarMap*)FUN_01046fc0();               // 0x01046fc0
    map->FilterHelperRebuildAll();                           // 0x01048ce0

    void* gm = GonzagoModelWorld();                          // 0x00b3d520
    if (gm != 0)
        (*(PFNvf*)((char*)*(void**)gm + 0x154))(gm, 0.0f);
}

// @ 0x01003620
void cSPSimulatorSpaceGame::FUN_01003620()
{
    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x12, 0);

    FUN_00b3d470()->FUN_01036830(0);                         // 0x01036830
    cSPSimulatorSpaceGame* sim = FUN_00b3d470();
    char* slotAC = (char*)sim + offsetof(cSPSimulatorSpaceGame, mpObjAC); // +0xac
    void* ac = *(void**)slotAC;
    (*(PFNvi*)((char*)*(void**)ac + 0x0c))(ac, 2);

    void* fx2 = EffectsManagerPtr();
    void* o = (*(PFNpv*)((char*)*(void**)fx2 + 0x5c))(fx2);
    (*(PFNv*)((char*)*(void**)o + 0x38))(o);

    if (mpSpaceUI != 0) {
        mpSpaceUI->OnContextDeactivate();                    // 0x0106e270
        mpSpaceUI->FUN_0106f380();                           // 0x0106f380
    }
}

// @ 0x01003690
void cSPSimulatorSpaceGame::FUN_01003690()
{
    cPlanet* planet = (cPlanet*)FUN_01021260();              // 0x01021260
    H00b8de30* civOwner = (H00b8de30*)planet->mpCiv13c;      // +0x13c

    FUN_00b3d360()->FUN_00b7dec0();                          // 0x00b7dec0
    FUN_00b3d2a0(planet, 0)->FUN_00bb5990();                 // 0x00b3d2a0 / 0x00bb5990

    if (planet->FUN_00c70e00() < 4)                          // 0x00c70e00
        planet->FUN_00c70bc0(0);                             // 0x00c70bc0

    mFlag4d = 0;
    mFlag4c = 0;
    mFlag4f = 0;
    mFlag4e = 0;

    void* o = FUN_0067de00();                                // 0x0067de00
    (*(PFNvi*)((char*)*(void**)o + 0xe0))(o, 0);
    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x14, 1);
    void* d1 = FUN_0067dd40();                               // 0x0067dd40
    (*(PFNvi*)((char*)*(void**)d1 + 0x100))(d1, 1);
    void* d2 = FUN_0067dd40();
    (*(PFNvi*)((char*)*(void**)d2 + 0x108))(d2, 0);

    cSPSimulatorSpaceGame* sim = FUN_00b3d470();             // 0x00b3d470
    if (sim->mpObj6c != 0) {                                 // +0x6c
        if ((*(PFNcv*)((char*)*(void**)sim->mpObj6c + 0x10))(sim->mpObj6c) == 0)
            (*(PFNvi*)((char*)*(void**)sim->mpObj6c + 0x08))(sim->mpObj6c, 0);
    }

    FUN_01021960(0);                                         // 0x01021960
    FUN_00b3d470()->FUN_01034810();                          // 0x01034810
    FUN_00b3d470()->FUN_01034950(1, planet->FUN_00c70880()); // 0x00c70880 / 0x01034950

    cStar* star = (cStar*)FUN_01021230();                    // 0x01021230
    cSolarSystem* solar = star->GetSolarSystem();            // 0x00c8b770
    if (solar != 0)
        solar->ActivateGraphics(1);                          // 0x00c86c70

    TerraformingManager(planet, 1)->FUN_00bc2070();          // 0x00b3d430 / 0x00bc2070

    FUN_00b3d3b0(0)->FUN_00b2ec80();                         // 0x00b3d3b0 / 0x00b2ec80
    FUN_00b3d440()->FUN_00b0b150();                          // 0x00b3d440 / 0x00b0b150
    FUN_00b3d3c0()->FUN_00b79aa0();                          // 0x00b3d3c0 / 0x00b79aa0
    FUN_00b3d480()->FUN_00acd790();                          // 0x00b3d480 / 0x00acd790

    if (planet->FUN_00c70c00() == 0)                         // 0x00c70c00
        planet->PlanetSimActivate();                         // 0x00c71e70
    planet->FUN_008414c0();                                  // 0x008414c0
    sim->FUN_01036590(planet);                               // 0x01036590

    cCivData* civ = civOwner->SortBanners();                 // 0x00b8de30
    SpVectorF* p = civ->GetCities();                         // 0x005c65e0
    FUN_00b3d470()->FUN_01036940(*p);                        // 0x01036940

    FUN_01021740(planet);                                    // 0x01021740

    void* ticker = SimTicker();                              // 0x00b3d330
    if (g_167a60c == 0)
        g_167a60c = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, g_167a60c);

    if (g_167a60c == 0)
        g_167a60c = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
    g_167a60c->SetSerializer();                              // 0x00c2e4e0

    TerraformingManager1(1)->FUN_00bc0180();                 // 0x00b3d430 / 0x00bc0180

    void* sys = g_167ea54;
    (*(PFNvu*)((char*)*(void**)sys + 0x30))(sys, FNVHash("Planet_Space", 0x811c9dc5, 1)); // 0x00932e80

    void* gm = GonzagoModelWorld();                          // 0x00b3d520
    if (gm != 0)
        (*(PFNvf*)((char*)*(void**)gm + 0x154))(gm, FUN_00b3d240()->FUN_00b35fa0()); // 0x00b3d240 / 0x00b35fa0

    void* layout = FUN_0067ddc0();                           // 0x0067ddc0
    if (layout != 0) {
        (*(PFNvp*)((char*)*(void**)layout + 0x10))(layout, g_167ea54);
        (*(PFNvpi*)((char*)*(void**)layout + 0x18))(layout, gm, 3);
        void* mdl = ModelManager();                          // 0x0067dd80
        void* m = (*(PFNpvu*)((char*)*(void**)mdl + 0x1c))(mdl, 0x3fbae24);
        if (m != 0)
            (*(PFNvpi*)((char*)*(void**)layout + 0x18))(layout, m, 0);
        (*(PFNvp*)((char*)*(void**)layout + 0x1c))(layout, FUN_0067de00u(0x20007));
        (*(PFNvu*)((char*)*(void**)layout + 0x48))(layout, 0x5e51c01);
        (*(PFNvi*)((char*)*(void**)layout + 0x28))(layout, 1);
    }

    void* aware = planet->FUN_00c71e30();                    // 0x00c71e30
    if (aware != 0) {
        void* a = *(void**)((char*)aware + 0x84);
        g_16dc798->AdjustAwareness(a, 1);                    // 0x01014a80
    }

    void* pm = *(void**)((char*)PlanetModel() + 0x24);       // 0x00b3d350
    char* slot8c = (char*)*(void**)pm + 0x8c;
    (*(PFNvp*)slot8c)(pm, FUN_0067dd50());                   // 0x0067dd50
    FUN_00cfea20();                                          // 0x00cfea20
}

// @ 0x010039c0
void cSPSimulatorSpaceGame::FUN_010039c0(cStar* star)
{
    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x13, 0);
    void* fx2 = EffectsManagerPtr();
    void* o = (*(PFNpv*)((char*)*(void**)fx2 + 0x5c))(fx2);
    (*(PFNv*)((char*)*(void**)o + 0x38))(o);

    if (mpSpaceUI != 0)
        mpSpaceUI->OnContextDeactivate();                    // 0x0106e270

    cSolarSystem* solar = star->GetSolarSystem();            // 0x00c8b770
    if (solar != 0) {
        solar->ActivateGraphics(0);                          // 0x00c86c70
        void* time = star->mpTime48;
        uint64_t t = GameTimeManager()->FUN_00b316c0();      // 0x00b3d380 / 0x00b316c0
        *(unsigned*)((char*)time + 0xc) = (unsigned)(t / 60000);
    }
    FUN_00b3d470()->FUN_01034950(0, -1);                     // 0x01034950
}

// @ 0x01003a50
void FUN_01003a50()
{
    cStar* star = (cStar*)FUN_01021230();                    // 0x01021230

    void* msg = MessageServer();                             // 0x0067dcc0
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x279a67c, 0, 0);
    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x13, 1);
    void* d1 = FUN_0067dd40();                               // 0x0067dd40
    (*(PFNvi*)((char*)*(void**)d1 + 0x100))(d1, 1);
    void* d2 = FUN_0067dd40();
    (*(PFNvi*)((char*)*(void**)d2 + 0x108))(d2, 1);

    FUN_01021960(1);                                         // 0x01021960
    void* o = FUN_0067de00();                                // 0x0067de00
    (*(PFNvi*)((char*)*(void**)o + 0xe0))(o, 1);

    FUN_00b3d230(0x1103192)->FUN_00b5cde0();                 // 0x00b3d230 / 0x00b5cde0

    void* app = App();                                       // 0x0067dd10
    void* frame = (*(PFNpv*)((char*)*(void**)app + 0x50))(app);
    void* g = (*(PFNpv*)((char*)*(void**)frame + 0x38))(frame);
    void* camRoot = (g != 0)
        ? (*(PFNpvu*)((char*)*(void**)g + 0x0c))(g, 0x303154cc)
        : 0;
    (*(PFNv*)((char*)*(void**)camRoot + 0x58))(camRoot);

    float* p = star->FUN_00c8b360();                         // 0x00c8b360
    float x = p[0];
    float y = p[1];
    float z = p[2];
    float len = sqrtf(x * x + (y * y + z * z));

    FUN_00b3d470()->SolarContextFinishActivate(len, true);    // 0x01036c20
    FUN_00b3d470()->FUN_010347e0();                          // 0x010347e0
    FUN_00b3d470()->FUN_01034950(2, -1);                     // 0x01034950
    FUN_00b3d470()->FUN_01036940(SpVectorF(x, y, z));         // 0x01036940
    star->GetSolarSystem()->ActivateGraphics(1);             // 0x00c8b770 / 0x00c86c70

    void* sys = g_167ea54;
    (*(PFNvu*)((char*)*(void**)sys + 0x30))(sys, 0x74d2735b);

    void* fx3 = EffectsManagerPtr();
    (*(PFNv*)((char*)*(void**)fx3 + 0x48))(fx3);

    msg = MessageServer();
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x2489766, 0, 0);
    FUN_00b3d470()->FUN_01034b90(star);                      // 0x01034b90

    if (g_15b743e != 0 || g_15fd918->GetDescription(0xffbdc58d) != 0) { // 0x006a25a0
        msg = MessageServer();
        (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x1cd20f0, (void*)1, 0);
    }

    void* gm = GonzagoModelWorld();                          // 0x00b3d520
    if (gm != 0)
        (*(PFNvf*)((char*)*(void**)gm + 0x154))(gm, 0.0f);
}

// @ 0x01003c60
void cSPSimulatorSpaceGame::ChangeCameraByOffset(float a, float b)
{
    cSPSimulatorSpaceGame* ufo = GetUFOSimulator();          // 0x00ffbe50
    cSPPlayerInventory* inv = (cSPPlayerInventory*)ufo->GetPlayerInventory(); // 0x00a1ad60
    bool blocked = false;
    if (inv == 0)
        blocked = true;
    else if (inv->FUN_00c37170() != 0)                       // 0x00c37170
        blocked = true;

    if (blocked) {
        int ctx = GetUniverseContext();                      // 0x01021080
        if (ctx == 0) {
            void* app = App();                               // 0x0067dd10
            void* frame = (*(PFNpv*)((char*)*(void**)app + 0x50))(app);
            void* g = (*(PFNpv*)((char*)*(void**)frame + 0x38))(frame);
            if (g != 0) {
                cSPCameraControllerSolarSystem* cam =
                    (cSPCameraControllerSolarSystem*)(*(PFNpvu*)((char*)*(void**)g + 0x0c))(g, 0x303154cd);
                if (cam != 0) {
                    cam->FUN_01017170(mfCamOffset_3c * a);   // 0x01017170
                    cam->FUN_010171b0(mfCamOffset_3c * b);   // 0x010171b0
                }
            }
        } else if (ctx > 0 && ctx < 3) {
            void* app = App();
            void* frame = (*(PFNpv*)((char*)*(void**)app + 0x50))(app);
            void* g = (*(PFNpv*)((char*)*(void**)frame + 0x38))(frame);
            if (g != 0) {
                cSPCameraControllerSolarSystem* cam =
                    (cSPCameraControllerSolarSystem*)(*(PFNpvu*)((char*)*(void**)g + 0x0c))(g, 0x303154cc);
                if (cam != 0) {
                    cam->mf6c = a * 0.005f + cam->mf6c;
                    cam->mf70 = b * 0.005f + cam->mf70;
                    float lim = FUN_01017010(ctx, cam->mf68); // 0x01017010
                    float v = cam->mf70;
                    if (v < 0.1f) v = 0.1f;
                    if (v > lim) v = lim;
                    cam->mf70 = v;
                    float r = cam->FUN_010175b0(cam->mf68);  // 0x010175b0
                    cam->mf80 = cam->mf70 - r;
                    return;
                }
            }
        }
    }
    return;
}

// @ 0x01004bb0
void* SimGame::f4bb0(int key)
{
    int** it = *(int***)(raw + 0x78);
    if (it != *(int***)(raw + 0x7c)) {
        do {
            int* p = *it;
            if (((int(__thiscall*)(void*))VTP(p)[0x4c / 4])(p) == key && p[0x1c5] == 3)
                return p;
            ++it;
        } while (it != *(int***)(raw + 0x7c));
    }
    return 0;
}

// @ 0x01004c00
int SimGame::f4c00()
{
    int n = 0;
    int** it = *(int***)(raw + 0x78);
    int** end = *(int***)(raw + 0x7c);
    for (; it != end; ++it) {
        if ((*it)[0x1c5] == 8) ++n;
    }
    return n;
}

// @ 0x01004c30
char SimGame::f4c30()
{
    void* sim = FUN_00ffbe50();
    void* inv = E(sim)->FUN_00a1ad60();
    int target = *(int*)((char*)inv + 0x544);
    int** it = *(int***)(raw + 0x78);
    if (it != *(int***)(raw + 0x7c)) {
        do {
            int* p = *it;
            if (p[0x1c5] == 8) {
                if (((int(__thiscall*)(void*))VTP(p)[0x4c / 4])(p) == target) return 1;
            }
            ++it;
        } while (it != *(int***)(raw + 0x7c));
    }
    return 0;
}

// @ 0x010050d0
void __stdcall f50d0(int param)
{
    void* nouns = FUN_00b3d300();
    void* civ = E(nouns)->FUN_00b25fb0();
    if (!civ) return;
    if ((int)(intptr_t)E(civ)->FUN_00bf01e0() <= 0) return;
    int* v = (int*)(intptr_t)E(civ)->FUN_00bef6c0();
    int* it = (int*)v[0];
    int* end = (int*)v[1];
    for (; it != end; ++it) {
        void* z = E((void*)*it)->FUN_00bd9e30();
        if (z) {
            void* obj = (void*)((char*)z + 0x34);
            ((void(__thiscall*)(void*, int))VTP(obj)[0x54 / 4])(obj, param);
        }
    }
}

// @ 0x01005130
void SimGame::f5130()
{
    char* s = (char*)this;
    void* m = E(*(void**)(s + 0x14))->FUN_01067e60();
    if (m) {
        E(m)->FUN_00e0fb50();
        E(m)->FUN_00e0ad00(4);
        E(m)->FUN_00e0e1a0();
    }
    E(*(void**)(s + 0x14))->FUN_0106ab20(1);
    FUN_0106200(*(void**)(s + 0x14), 0);
    void* nouns = FUN_00b3d300();
    E(nouns)->FUN_00b22960();
}

// @ 0x010052d0
char SimGame::f52d0(int id)
{
    int n = (*(int*)(raw + 0xe0) - *(int*)(raw + 0xdc)) / 0x14;
    if (n > 0) {
        int* p = (int*)(*(int*)(raw + 0xdc) + 0xc);
        for (int i = 0; i < n; ++i) {
            if (*p == id) return 1;
            p += 5;
        }
    }
    return 0;
}

// @ 0x01005320
void SimGame::f5320()
{
    char* s = (char*)raw;
    char* it = *(char**)(s + 0);
    char* end = *(char**)(s + 4);
    for (; it < end; it += 0x14) {
        ((void(__thiscall*)(void*, int))VTP(it)[8 / 4])(it, 0);
    }
    void* base = *(void**)(s + 0);
    if (base && *(int*)((char*)base - 4) != 0) {
        FUN_00f47380(base);
    }
}

// @ 0x010053a0
bool f53a0()
{
    void* s = DAT_016dc0fc;
    void* o = *(void**)((char*)s + 0x40);
    return ((char(__thiscall*)(void*, u32))VTP(o)[0x74 / 4])(o, (u32)(uintptr_t)&DAT_016dc1e0) != 0;
}

// @ 0x01005800
void __fastcall FUN_01005800(void* self, void* /*edx*/, void* outVec)
{
  char* p = (char*)self;
  // vector accumulators: local_14/10/c are the begin/end/cap of a u32 vector
  u32* vecBegin = 0;
  u32  vecEnd   = 0;
  u32  vecCap   = 0;

  if ((DAT_016dc794 & 1) == 0) {
    DAT_016dc794 |= 1;
    DAT_016dc728[0]  = DAT_016dc648;  DAT_016dc728[1]  = DAT_016dc64c;
    DAT_016dc728[2]  = DAT_016dc650;  DAT_016dc728[3]  = DAT_016dc654;
    DAT_016dc728[4]  = DAT_016dc658;  DAT_016dc728[5]  = DAT_016dc65c;
    DAT_016dc728[6]  = DAT_016dc660;  DAT_016dc728[7]  = DAT_016dc664;
    DAT_016dc728[8]  = DAT_016dc668;  DAT_016dc728[9]  = DAT_016dc66c;
    DAT_016dc728[10] = DAT_016dc670;  DAT_016dc728[11] = DAT_016dc674;
    DAT_016dc728[12] = DAT_016dc678;  DAT_016dc728[13] = DAT_016dc67c;
    DAT_016dc728[14] = DAT_016dc680;  DAT_016dc728[15] = DAT_016dc684;
    DAT_016dc728[16] = DAT_016dc688;  DAT_016dc728[17] = DAT_016dc68c;
    DAT_016dc728[18] = DAT_016dc690;  DAT_016dc728[19] = DAT_016dc694;
    DAT_016dc728[20] = DAT_016dc698;  DAT_016dc728[21] = DAT_016dc69c;
    DAT_016dc728[22] = DAT_016dc6a0;  DAT_016dc728[23] = DAT_016dc6a4;
    DAT_016dc728[24] = DAT_016dc6a8;  DAT_016dc728[25] = DAT_016dc6ac;
    DAT_016dc728[26] = DAT_016dc6b0;
  }

  char* sphere = (char*)FUN_00f67d90(SP_NounManager());
  u32* sf = (u32*)sphere;
  FUN_00555e80((void*)sf[0x10fc / 4], &vecBegin);
  FUN_00555e80((void*)sf[0x1100 / 4], &vecBegin);
  FUN_00555e80((void*)sf[0x1104 / 4], &vecBegin);
  FUN_00555e80((void*)sf[0x1108 / 4], &vecBegin);
  FUN_00555e80((void*)sf[0x110c / 4], &vecBegin);

  s32 n = (s32)(vecEnd - (u32)vecBegin) >> 2;
  s32 i = 0;
  *(u32*)(p + 0xc4) = 0;
  s32 cur = -1;
  if (n > 0) {
    s32 prev = cur;
    do {
      u32 id = vecBegin[i];
      cur = prev;
      switch (id) {
      case 0x9afd99c1: cur = 1; break;
      case 0x92d11083: *(u32*)(p + 0xc4) |= 8;    break;
      case 0xa08d482a: *(u32*)(p + 0xc4) |= 0x200; break;
      case 0xa7b3defa: *(u32*)(p + 0xc4) |= 0x10; break;
      case 0xb27471c6: *(u32*)(p + 0xc4) |= 0x40; break;
      case 0xbce4ad98: cur = 2; break;
      case 0xcf7f7780: *(u32*)(p + 0xc4) |= 0x800; break;
      case 0xd6b2c7f0: *(u32*)(p + 0xc4) |= 2;   break;
      case 0xed489b99: cur = 7; break;
      case 0xf0db6039: *(u32*)(p + 0xc4) |= 4;   break;
      case 0xf42be530: *(u32*)(p + 0xc4) |= 0x100; break;
      case 0x496d884f: *(u32*)(p + 0xc4) |= 0x80;  break;
      case 0x0d7dbbe1: cur = 4; break;
      case 0x0b7b9820: cur = 0; break;
      case 0x0bc14e8f: *(u32*)(p + 0xc4) |= 0x20;  break;
      case 0x2ac5df1f: cur = 6; break;
      case 0x46aff0dc: *(u32*)(p + 0xc4) |= 0x400; break;
      case 0x69073562: cur = 3; break;
      case 0x622280f4: cur = 8; break;
      case 0x629ee549: cur = 5; break;
      case 0x714e0388: *(u32*)(p + 0xc4) |= 1;     break;
      default: break;
      }
      i++;
      prev = cur;
    } while (i < n);
  }

  // Rebuild the tool tray: clear each of the 10 slots, then create the tool.
  u32* slot = DAT_016dc728;
  s32 k = 10;
  do {
    void* mgr = *(void**)(p + 0x40);
    void* existing = ((void*(__thiscall*)(void*, u32*))(*(void***)mgr)[0x68 / 4])(mgr, slot);
    if (existing != 0) {
      ((void(__thiscall*)(void*, void*))(*(void***)mgr)[0x78 / 4])(mgr, existing);
    }
    slot += 3;
  } while (--k != 0);

  if (cur != -1) {
    void* erased;
    u32* dstSlot = &DAT_016dc728[cur * 3];
    erased = FUN_00b3d390(dstSlot, &outVec);              // vector::erase
    void* toolmgr = (void*)((char*)p + 0x40);
    (void)toolmgr;
    FUN_0104e340(p + 0x40, (u32)erased);                  // CreateToolFromToolID
    void* tok = outVec;
    if (tok != 0) {
      void* mgr = *(void**)(p + 0x40);
      ((void(__thiscall*)(void*, void*, int, int))(*(void***)mgr)[0x80 / 4])(mgr, tok, 0, 1);
      if (tok != 0) {
        ((void(__thiscall*)(void*))(*(void***)tok)[8 / 4])(tok);
      }
    }
  }

  if (FUN_00685520(2)) {
    void* u = FUN_00fd9c60();
    FUN_00fdbf90(u);
  }
  {
    void* u = SP_GetUFOSimulator();
    float e = FUN_00ffda80(u);
    (void)e;
  }
  {
    void* u = SP_GetUFOSimulator();
    float h = FUN_00ffd8e0(u);
    (void)h;
  }

  if (vecBegin != 0 && *(u32*)((char*)vecBegin - 4) != 0) {
    operator_delete_(vecBegin);
  }
}

// @ 0x01005c60
float __stdcall FUN_01005c60(u32 selector)
{
  void* pm = SP_PropertyManager();
  void* holder = 0;
  {
    void* mgr = pm;
    ((void(__thiscall*)(void*, u32, u32, void**))(*(void***)mgr)[0x2c / 4])(
        mgr, 0x8da597e4, 0x2ae0c7e, &holder);
  }
  u32 propId;
  switch (selector) {
  case 0x3:  propId = 0x2f5c9502; break;
  case 0x0:  propId = 0xdc13b0ec; break;
  case 0xa:  propId = 0x7492aef4; break;
  case 0x1: case 0x2: case 0x6: case 0x8:
             propId = 0xee6cc96d; break;
  case 0x5:  propId = 0x97b7d5cb; break;
  case 0x9:  propId = 0x2da66ec8; break;
  case 0xb:  propId = 0x7c945213; break;
  default:   goto done;
  }
  {
    float value = 1.0f;
    FUN_0040cf10(0x2ae0c7e, propId, &value);
    (void)value;
  }
done:
  if (holder != 0) {
    ((void(__thiscall*)(void*))(*(void***)holder)[4 / 4])(holder);
  }
  return DAT_01485720;
}

// @ 0x01005d80
void __fastcall FUN_01005d80(void* /*ecx*/, void* /*edx*/, u8 flag, u32 param)
{
  FUN_00c30c80(FUN_01021300());
  void* sphere = (void*)FUN_00f67d90(SP_NounManager());
  u32* sf = (u32*)sphere;

  u32 handle;
  if (flag == 0) {
    handle = sf[0x110c / 4];
  } else {
    handle = (u32)FUN_00556440((void*)sf[0x10fc / 4], (void*)sf[0x1100 / 4],
                               (void*)sf[0x1104 / 4], (void*)sf[0x1108 / 4]);
  }

  u32 awardId = 0;
  u32 eventId = 0;
  u32 counter = param;
  if (handle != 0) {
    FUN_00c75cc0(0x2db6dad3, (void*)handle);
    u32 tier = 0x11;
    switch (handle) {
    case 0x0d832b059: break;
    case 0xa6cb4c9f: tier = 0xc; awardId = 0x7afcb267; eventId = 0xa6cb4c9f; break;
    case 0x7bceaa86: tier = 0x10; awardId = 0xda2fec0e; eventId = 0x7bceaa86; break;
    case 0x6cd9ec7b: awardId = 0xae94ffe3; eventId = 0x6cd9ec7b; break;
    case 0xcdb3696f: tier = 0xf; awardId = 0x59bf4bc7; eventId = 0xcdb3696f; break;
    case 0xd536c91d: tier = 10; awardId = 0x23752db5; eventId = 0xd536c91d; break;
    case 0x980e43f2: tier = 0x12; awardId = 0x5ae3a08a; eventId = 0x980e43f2; break;
    case 0xe0bc9d45: tier = 9;  awardId = 0x2b54d82d; eventId = 0xe0bc9d45; break;
    case 0xa0973374: tier = 0xe; awardId = 0xcb7d6d3c; eventId = 0xa0973374; break;
    case 0x5fcf28d0: tier = 0xd; awardId = 0x7d7b59e8; eventId = 0x5fcf28d0; break;
    default: eventId = 0; break;
    }
    (void)eventId;
    FUN_01021300();  // player empire accessor (logged value unused here)
    *(u32*)((char*)SP_GetActivePlanet() + 0x58) = tier;

    if (flag != 0) {
      void* ctrl = FUN_00675250(awardId);
      FUN_00676710(ctrl, awardId);
      u32 scratch[12] = {0};
      FUN_00e39ab0(counter, 0, &scratch[3], &scratch[0], 0, 0, &scratch[6], &scratch[9]);
      static const u32 chain[] = {
          0x7d7b59e8, 0xda2fec0e, 0xcb7d6d3c, 0x59bf4bc7, 0x3e06ba31,
          0x23752db5, 0x7afcb267, 0x2b54d82d, 0xae94ffe3, 0x5ae3a08a };
      for (u32 ci = 0; ci < 10; ci++) {
        void* c = FUN_00675250(chain[ci]);
        if (!FUN_00675e80(c, chain[ci])) return;
      }
      void* c = FUN_00675250(0x99bb05bb);
      FUN_00676710(c, 0x99bb05bb);
    }
  }

  FUN_01005800(0, 0, (void*)0);
  (void)param;

  if (flag != 0) {
    void* s2 = (void*)FUN_00f67d90(SP_NounManager());
    u32* s2f = (u32*)s2;
    if (s2f[0x10fc / 4] != 0 && s2f[0x1100 / 4] != 0 &&
        s2f[0x1104 / 4] != 0 && s2f[0x1108 / 4] != 0) {
      void* c = FUN_00675250(0xaf2819b8);
      FUN_00676710(c, 0xaf2819b8);
    }
  }
}

// @ 0x010060d0
void __fastcall SP_cSPSimulatorSpaceGame_ConfigUpdated(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  void* holder = 0;
  void* pm = SP_PropertyManager();
  void* pmv = pm;
  if (holder != 0) {
    holder = 0;
    ((void(__thiscall*)(void*))(*(void***)pmv)[4 / 4])(pmv);
  }
  ((void(__thiscall*)(void*, u32, u32, void**))(*(void***)pmv)[0x2c / 4])(
      pmv, 0x521d0174, 0x2ae0c7e, &holder);

  if (holder != 0) {
    // float property 0x5820b5e -> mContextSwitchTimer.mTime (+0x34)
    if (((bool(__thiscall*)(void*, u32, void**))(*(void***)holder)[0x24 / 4])(holder, 0x5820b5e, (void**)(p + 0x34))) {
      u32* prop = *(u32**)(p + 0x34);
      if (prop != 0 && ((u16*)prop)[9] == 0xd) {
        void* fv = FUN_0041ea70();
        (void)fv;
      }
    }
    // float property 0x5820b65 -> mSpaceUI.mValue (+0x38)
    if (((bool(__thiscall*)(void*, u32, void**))(*(void***)holder)[0x24 / 4])(holder, 0x5820b65, (void**)(p + 0x38))) {
      u32* prop = *(u32**)(p + 0x38);
      if (prop != 0 && ((u16*)prop)[9] == 0xd) {
        void* fv = FUN_0041ea70();
        (void)fv;
      }
    }
    *(float*)(p + 0x3c) = 1.0f;
    // float property 0x195a065 -> mRaresUI.mRotation (+0x3c)
    if (((bool(__thiscall*)(void*, u32, void**))(*(void***)holder)[0x24 / 4])(holder, 0x195a065, (void**)(p + 0x3c))) {
      u32* prop = *(u32**)(p + 0x3c);
      if (prop != 0 && ((u16*)prop)[9] == 0xd) {
        void* fv = FUN_0041ea70();
        (void)fv;
      }
    }
    *(float*)(p + 0x3c) = *(float*)(p + 0x3c) * DAT_01495378;
    if (holder != 0) {
      ((void(__thiscall*)(void*))(*(void***)holder)[4 / 4])(holder);
    }
  }
}

// @ 0x01006280
void* __cdecl FUN_01006280(char* first, char* last, char* dst)
{
  while (first != last) {
    if (first != dst) {
      StrAssign(dst, *(void**)first, *(void**)(first + 4));
    }
    *(u32*)(dst + 0x10) = *(u32*)(first + 0x10);
    *(float*)(dst + 0x14) = *(float*)(first + 0x14);
    *(u32*)(dst + 0x18) = *(u32*)(first + 0x18);
    first += 0x1c;
    dst   += 0x1c;
  }
  return dst;
}

// @ 0x010062d0
void __cdecl FUN_010062d0(char* first, char* last, char* dst)
{
  while (first != last) {
    if (dst != 0) {
      *(u32*)(dst + 4) = 0x013ec458;   // ??_7ContentValidationSummarizer@@6B@
      *(u32*)(dst + 8) = 0;
      *(u32*)(dst + 0) = 0x01495400;
      *(u32*)(dst + 4) = 0x0149bad8;
      *(u32*)(dst + 0xc)  = *(u32*)(first + 0xc);
      *(u32*)(dst + 0x10) = *(u32*)(first + 0x10);
    }
    first += 0x14;
    dst   += 0x14;
  }
}

// @ 0x01006320
void* __cdecl FUN_01006320(char* first, char* last, char* dst)
{
  if (last == first) return dst;
  char* si = last;
  char* di = dst;
  do {
    si -= 0x1c;
    di -= 0x1c;
    if (si != di) {
      StrAssign(di, *(void**)si, *(void**)(si + 4));
    }
    *(u32*)(di + 0x10) = *(u32*)(si + 0x10);
    *(float*)(di + 0x14) = *(float*)(si + 0x14);
    *(u32*)(di + 0x18) = *(u32*)(si + 0x18);
  } while (si != first);
  return di;
}

// @ 0x01006370
void __fastcall FUN_01006370(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  if (!FUN_01044920()) goto lab_d8;
  {
    void* ufo = SP_GetUFOSimulator();
    if (!FUN_00ffc5b0(ufo)) goto lab_d8;
  }
  {
    void* pm = SP_PlanetModel();
    void* obj = *(void**)((char*)pm + 0x24);
    if (!((bool(__thiscall*)(void*))(*(void***)obj)[0x50 / 4])(obj)) goto lab_72;
  }

  if (*(u8*)(p + 0x4e) == 0) {
    if (*(u8*)(p + 0x4c) == 0) {
      if (*(u8*)(p + 0x4f) == 0) {
        // Create the space tool tray and its listener UI.
        {
          void* a = operator_new(0x2c, "Simulator", 0, 0, 0, 0);
          if (a) a = FUN_00b60070(a);
          FUN_0061df40(a);
        }
        void* listener;
        {
          void* b = operator_new(0x20, "Simulator", 0, 0, 0, 0);
          if (b) listener = FUN_00760c00(b);
          else   listener = 0;
        }
        void* refHolder;
        FUN_00572660(&refHolder, listener);
        void* reg = FUN_0067dd50();
        s32 cnt = ((s32(__thiscall*)(void*))(*(void***)reg)[0x68 / 4])(reg);
        for (s32 i = 0; i < cnt; i++) {
          void* r = FUN_0067dd50();
          u32* rec = (u32*)((u32(__thiscall*)(void*, s32))(*(void***)r)[0x70 / 4])(r, i);
          u32 kind = rec[1];
          if (kind == 7 || kind == 8 || kind == 0xa) {
            FUN_00760fd0((void*)refHolder, rec[0], kind, rec[2]);
          }
        }
        void* planet = (void*)FUN_01021260();  // active planet
        void* reg2 = FUN_0067dd60();
        u32 res = ((u32(__thiscall*)(void*, const char*, const char*, int, int, int, int, int))
                       (*(void***)reg2)[0x3c / 4])(reg2, (const char*)0x5fe9b92,
                        (const char*)0x5fe9b97, 0x80, 0x80, 1, 0x208, 0x15);
        u32 img = (u32)FUN_00576650(p + 0x48, (void*)res);
        void* name = FUN_00c707e0(planet);
        void* str = FUN_0093c570(&name, name);
        (void)str;
        (void)img;
      } else {
        goto lab_8c;
      }
    }
  } else {
lab_8c:
    if (*(u8*)(p + 0x4c) == 0 && *(u8*)(p + 0x4f) != 0) {
      void* planet = (void*)FUN_01021260();
      void* e = (void*)FUN_00b3d360(planet);
      FUN_00b7daf0(e);
      *(u8*)(p + 0x4f) = 0;
      *(u8*)(p + 0x4e) = 0;
      *(u8*)(p + 0x4c) = 1;
      *(u8*)(p + 0x4d) = 0;
      goto lab_72;
    }
  }
  if (*(u8*)(p + 0x4d) != 0) {
    *(u8*)(p + 0x4d) = 0;
    *(u8*)(p + 0x4c) = 0;
    void* am = FUN_00fd9c60();
    FUN_00fde3e0(am);
  }
lab_d8:
  if (*(u8*)(p + 0x77) == 0) return;
  *(u8*)(p + 0x77) = 0;
  {
    void* s = FUN_0067cab0();
    FUN_00801380(s);
  }
  return;
lab_72:
  if (*(u8*)(p + 0x77) != 0) return;
  *(u8*)(p + 0x77) = 1;
  {
    void* s = FUN_0067cab0();
    FUN_00801360(s);
  }
}

// @ 0x01006600
bool __cdecl FUN_01006600(void* dst, void** src)
{
  u32 v = 0;
  if (*src != 0) {
    void* o = (char*)*src + 8;
    v = ((u32(__thiscall*)(void*, u32))(*(void***)o)[0xc / 4])(o, 0x179c807);
  }
  ((void(__thiscall*)(void*, u32))(*(void***)dst)[0x2c / 4])(dst, v);
  return true;
}

// @ 0x01006630
void* __fastcall FUN_01006630(void* self, void* /*edx*/, void* src)
{
  u32* d = (u32*)self;
  u32* s = (u32*)src;
  d[0] = 0; d[1] = 0; d[2] = 0;
  char* sBegin = (char*)s[0];
  char* sEnd   = (char*)s[1];
  u32  n       = (u32)(sEnd - sBegin);
  FUN_00475ab0(d, n + 1);
  char* dBegin = (char*)d[0];
  memcpy(dBegin, sBegin, n);
  char* dEnd = dBegin + n;
  d[1] = (u32)dEnd;
  *dEnd = 0;
  *(u32*)((char*)d + 0x10) = *(u32*)((char*)s + 0x10);
  *(float*)((char*)d + 0x14) = *(float*)((char*)s + 0x14);
  *(u32*)((char*)d + 0x18) = *(u32*)((char*)s + 0x18);
  return d;
}

// @ 0x010066e0
void* __fastcall FUN_010066e0(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  TC_b5b6c0(self);                        // cGonzagoSimulator base ctor
  *(u32*)(p + 0x10) = 0x013eb384;         // ??_7cListenerBase@@6B@
  *(u32*)(p + 0x00) = 0x0149544c;
  *(u32*)(p + 0x08) = 0x01495428;
  *(u32*)(p + 0x10) = 0x01495418;
  *(u32*)(p + 0x14) = 0;
  *(u32*)(p + 0x18) = 0;
  *(u32*)(p + 0x1c) = 0xffffffff;
  *(u32*)(p + 0x20) = 0;
  *(u32*)(p + 0x24) = 0;
  *(u32*)(p + 0x28) = 0;
  void* sub = operator_new(0x108, "Simulator", 0, 0, 0, 0);
  if (sub) sub = TC_fe68a0(sub);
  else     sub = 0;
  *(u32*)(p + 0x30) = (u32)sub;
  *(float*)(p + 0x34) = 0.0f;
  *(float*)(p + 0x38) = 0.0f;
  *(u32*)(p + 0x40) = 0;
  *(u32*)(p + 0x44) = 0;
  *(u32*)(p + 0x48) = 0;
  *(u8*)(p + 0x4c) = 0;
  *(u8*)(p + 0x4d) = 0;
  *(u8*)(p + 0x4e) = 0;
  *(u8*)(p + 0x4f) = 0;
  *(u32*)(p + 0x50) = 0;
  *(u32*)(p + 0x54) = 0;
  *(u32*)(p + 0x58) = 0;
  *(u32*)(p + 0x5c) = 0;
  *(u32*)(p + 0x60) = 0;
  *(u32*)(p + 0x64) = 0;
  *(u32*)(p + 0x68) = 0;
  *(u8*)(p + 0x6c) = 0;
  *(u32*)(p + 0x70) = 0;
  *(u8*)(p + 0x74) = 0;
  *(u8*)(p + 0x75) = 1;
  *(u8*)(p + 0x76) = 0;
  *(u8*)(p + 0x77) = 0;
  *(u32*)(p + 0x78) = 0;
  *(u32*)(p + 0x7c) = 0;
  *(u32*)(p + 0x80) = 0;
  TC_b63890(p + 0x90);                    // cGonzagoTimer ctor
  *(u32*)(p + 0xb0) = 0;
  *(u32*)(p + 0xb4) = 0;
  *(u32*)(p + 0xb8) = 0;
  *(u32*)(p + 0xbc) = 0;
  *(u32*)(p + 0xc0) = 0;
  *(u32*)(p + 0xc4) = 0;
  *(u32*)(p + 0xc8) = 0;
  *(u32*)(p + 0xcc) = 0;
  *(u32*)(p + 0xd0) = 0;
  *(u32*)(p + 0xdc) = 0;
  *(u32*)(p + 0xe0) = 0;
  *(u32*)(p + 0xe4) = 0;
  *(u32*)0x016dc0fc = (u32)self;          // singleton
  {
    u32* r = (u32*)(p + 0x28);
    u32 obj = *r;
    if (obj != 0) {
      *r = 0;
      void* o = (void*)obj;
      ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
    }
  }
  *(u32*)(p + 0xc4) = 0;
  TC_bc30f0(p + 0x90);                    // cSPTimer::Start
  return self;
}

// @ 0x01006880
void __fastcall FUN_01006880(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  *(u32*)(p + 0) = 0x0149544c;
  *(u32*)(p + 8) = 0x01495428;
  *(u32*)(p + 0x10) = 0x01495418;
  {
    void* a = *(void**)(p + 0x28);
    if (a != 0) {
      *(void**)(p + 0x28) = 0;
      (*(void(__thiscall**)(void*))(*(void***)a + 1))(a);
    }
  }
  {
    void* b = *(void**)(p + 0x30);
    if (b != 0) {
      (*(void(__thiscall**)(void*, int))*(void***)b)(b, 1);
    }
  }
  *(void**)(p + 0x30) = 0;
  *(u32*)0x016dc0fc = 0;
  ((void(__thiscall*)(void*))FUN_01005320)(p + 0xdc);
  ((void(__thiscall*)(void*, void*, void*))FUN_006fab90)(
      p + 0xc8, *(void**)(p + 0xc8), *(void**)(p + 0xcc));
  {
    void* c = *(void**)(p + 0xc8);
    if (c != 0 && *(u32*)((char*)c - 4) != 0) {
      FUN_00f47380(c);
    }
  }
  {
    void* d = *(void**)(p + 0xc0);
    if (d != 0) (*(void(__thiscall**)(void*))(*(void***)d + 2))(d);
  }
  {
    void* e = *(void**)(p + 0xbc);
    if (e != 0) (*(void(__thiscall**)(void*))(*(void***)e + 2))(e);
  }
  {
    void* f = *(void**)(p + 0xb8);
    if (f != 0) (*(void(__thiscall**)(void*))(*(void***)f + 2))(f);
  }
  {
    void* g = *(void**)(p + 0xb4);
    if (g != 0) (*(void(__thiscall**)(void*))(*(void***)g + 2))(g);
  }
  ((void(__thiscall*)(void*))FUN_00b638b0)(p + 0x90);
  ((void(__thiscall*)(void*))FUN_00ae6970)(p + 0x78);
  {
    void* h = *(void**)(p + 0x70);
    if (h != 0) (*(void(__thiscall**)(void*))(*(void***)h + 2))(h);
  }
  {
    void* i = *(void**)(p + 0x58);
    if (i != 0) {
      *(void**)(p + 0x58) = 0;
      FUN_00571db0(i, *(void**)(p + 0x5c), *(void**)(p + 0x60),
                   *(void**)(p + 0x64), *(void**)(p + 0x68));
    }
  }
  {
    void* j = *(void**)(p + 0x54);
    if (j != 0) (*(void(__thiscall**)(void*))(*(void***)j + 2))(j);
  }
  {
    char* k = *(char**)(p + 0x48);
    if (k != 0) {
      char* kk = k + 8;
      --*(s32*)kk;
      s32 old = *(s32*)kk;
      if (old < 1) {
        ++*(s32*)kk;
      } else {
        volatile s32 dummy = *(s32*)kk;
        (void)dummy;
      }
    }
  }
  {
    void* l = *(void**)(p + 0x44);
    if (l != 0) (*(void(__thiscall**)(void*))(*(void***)l + 2))(l);
  }
  {
    void* m = *(void**)(p + 0x40);
    if (m != 0) (*(void(__thiscall**)(void*))(*(void***)m + 1))(m);
  }
  {
    void* n = *(void**)(p + 0x28);
    if (n != 0) (*(void(__thiscall**)(void*))(*(void***)n + 1))(n);
  }
  {
    void* o = *(void**)(p + 0x24);
    if (o != 0) (*(void(__thiscall**)(void*))(*(void***)o + 2))(o);
  }
  {
    void* q = *(void**)(p + 0x20);
    if (q != 0) (*(void(__thiscall**)(void*))(*(void***)q + 3))(q);
  }
  {
    void* r = *(void**)(p + 0x18);
    if (r != 0) (*(void(__thiscall**)(void*))(*(void***)r + 1))(r);
  }
  {
    void* s = *(void**)(p + 0x14);
    if (s != 0) (*(void(__thiscall**)(void*))(*(void***)s + 1))(s);
  }
  *(u32*)(p + 0x10) = 0x013eb394;
  *(u32*)(p + 8) = 0x013eb938;
  *(u32*)(p + 0) = 0x013ec458;
}

// @ 0x01006a40
void __fastcall FUN_01006a40(void* self, void* /*edx*/, void* arg1, int arg2, int arg3, float arg4, float arg5)
{
  char* p = (char*)self;
  char* ufo = (char*)arg1;
  char* gd = *(char**)(ufo + 0x68c);
  if (gd == 0) return;

  float r = FUN_00c3ae70();
  float fscale = (r <= arg4) ? arg4 : r;

  char* g1 = *(char**)(ufo + 0x68c);
  float best = 0.0f;
  void* bestObj = 0;

  if (g1[0x74c] != 0) {
    // rotational branch
    float rad = (float)arg3;
    if (arg3 < 0) rad += 4294967300.0f;
    rad *= *(float*)0x013f999c;
    float sn = (float)0;
    float cs = (float)0;
    (void)sn; (void)cs;
    float fwd[3];
    fwd[0] = 0; fwd[1] = 0; fwd[2] = 0;
    float out[3];
    out[0] = 0; out[1] = 0; out[2] = 0;
    FUN_0059aed0(out, ufo + 0x6a0, fwd);
    float* mp = (float*)(*(void*(__thiscall**)(void*))(*(void***)(g1 + 0x34) + 0x2c / 4))(g1 + 0x34);
    float dx = mp[0] - *(float*)(ufo + 0x750);
    float dy = mp[1] - *(float*)(ufo + 0x754);
    float dz = mp[2] - *(float*)(ufo + 0x758);
    float dist = 0.0f;
    (void)dx; (void)dy; (void)dz; (void)dist;
    ufo[0x624] = 1;
  } else {
    // positional branch
    int idx = *(int*)(ufo + 0x6b0);
    char* off = (char*)(0x016dc060 + idx * 12);
    float x = *(float*)(off + 0) * (float)arg2 * fscale;
    float y = *(float*)(off + 4) * (float)arg2 * fscale;
    float z = *(float*)(off + 8) * (float)arg2 * fscale;
    float base[3];
    base[0] = x; base[1] = y; base[2] = z;
    void* m = (*(void*(__thiscall**)(void*))(*(void***)(g1 + 0x34) + 0x30 / 4))(g1 + 0x34);
    float* pos = (float*)FUN_0059aed0(pos, base, m);
    float out[3];
    out[0] = *(float*)(g1 + 0x750) + pos[0];
    out[1] = *(float*)(g1 + 0x754) + pos[1];
    out[2] = *(float*)(g1 + 0x758) + pos[2];
    FUN_00c3bfe0(ufo, out);
    ufo[0x624] = 1;
  }

  if (*(int*)(ufo + 0x76c) != 3) {
    void* owner = (*(void*(__thiscall**)(void*))(*(void***)(ufo + 0x34) + 0x2c / 4))(ufo + 0x34);
    float* op = (float*)owner;
    best = *(float*)0x149538c;
    char* it = *(char**)(p + 0x78);
    char* e = *(char**)(p + 0x7c);
    for (; it != e; it += 4) {
      char* cand = *(char**)it;
      if (*(int*)(cand + 0x714) == 8 && *(int*)(cand + 0x76c) != 3) {
        void* co = (*(void*(__thiscall**)(void*))(*(void***)(cand + 0x34) + 0x2c / 4))(cand + 0x34);
        float* cp = (float*)co;
        float dx = op[0] - cp[0];
        float dy = op[1] - cp[1];
        float dz = op[2] - cp[2];
        float d2 = dx * dx + dy * dy + dz * dz;
        if (d2 < best) {
          int id = (*(int(__thiscall**)(void*))(*(void***)cand + 0x4c / 4))(cand);
          void* sm = FUN_00b3d2a0((void*)id);
          void* emp = FUN_00ba9370(sm, 0);
          if (emp == 0 || FUN_00c309e0(emp) != 0) {
            best = d2;
            bestObj = cand;
          }
        }
      }
    }
  }
  void* res = bestObj ? (char*)bestObj + 0x508 : 0;
  (*(void(__thiscall**)(void*, void*))(*(void***)(ufo + 0x508) + 0x50 / 4))(ufo + 0x508, res);
}

// @ 0x01006ef0
void __fastcall FUN_01006ef0(void* self, void* /*edx*/, char* arg1)
{
  char* p = (char*)self;
  char* a1 = arg1;

  void* tick = FUN_00b3d330();
  (*(void(__thiscall**)(void*, void*))(*(void***)tick + 0x50 / 4))(tick, self);

  if (*(void**)(p + 0x70) == 0) {
    char* nb = (char*)FUN_00f473a0(0xc0, "Simulator", 0, 0, 0, 0);
    char* created = nb ? (char*)FUN_00fe4fa0(nb) : 0;
    char* old = *(char**)(p + 0x70);
    if (created != old) {
      if (created != 0) (*(void(__thiscall**)(void*))(*(void***)created + 1))(created);
      *(char**)(p + 0x70) = created;
      if (old != 0) (*(void(__thiscall**)(void*))(*(void***)old + 2))(old);
    }
    void* tk2 = FUN_00b3d330();
    (*(void(__thiscall**)(void*, char*))(*(void***)tk2 + 0x50 / 4))(tk2, *(char**)(p + 0x70));
  }

  if (*(void**)0x0167a690 == 0) {
    char* nb = (char*)FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
    *(void**)0x0167a690 = nb ? (void*)FUN_00ae6a70(nb) : 0;
  }
  char* sim = *(char**)0x0167a690;
  FUN_00ae7350(sim);
  void* tk3 = FUN_00b3d330();
  (*(void(__thiscall**)(void*, char*))(*(void***)tk3 + 0x50 / 4))(tk3, sim);

  char* nb1 = (char*)FUN_00f473a0(0x1b8, "Simulator", 0, 0, 0, 0);
  char* uni = nb1 ? (char*)FUN_010154f0(nb1) : 0;
  char* oldU = *(char**)(p + 0xc0);
  if (uni != oldU) {
    if (uni != 0) (*(void(__thiscall**)(void*))(*(void***)uni + 1))(uni);
    *(char**)(p + 0xc0) = uni;
    if (oldU != 0) (*(void(__thiscall**)(void*))(*(void***)oldU + 2))(oldU);
  }
  FUN_00b6f4c0(*(void**)(p + 0xc0));

  char* nb2 = (char*)FUN_00f473a0(0xe0, "Simulator", 0, 0, 0, 0);
  char* pu = nb2 ? (char*)FUN_01000740(nb2) : 0;
  char* oldP = *(char**)(p + 0xb4);
  if (pu != oldP) {
    if (pu != 0) (*(void(__thiscall**)(void*))(*(void***)pu + 1))(pu);
    *(char**)(p + 0xb4) = pu;
    if (oldP != 0) (*(void(__thiscall**)(void*))(*(void***)oldP + 2))(oldP);
  }
  FUN_00ffc160(*(void**)(a1 + 0), *(void**)(a1 + 4), 0);
  (void)0;

  char* nb3 = (char*)FUN_00f473a0(0x144, "Simulator", 0, 0, 0, 0);
  char* mm = nb3 ? (char*)FUN_00fecc90(nb3) : 0;
  char* oldM = *(char**)(p + 0xb8);
  if (mm != oldM) {
    if (mm != 0) (*(void(__thiscall**)(void*))(*(void***)mm + 1))(mm);
    *(char**)(p + 0xb8) = mm;
    if (oldM != 0) (*(void(__thiscall**)(void*))(*(void***)oldM + 2))(oldM);
  }
  FUN_00fedb50(*(void**)(p + 0xb8));

  char* nb4 = (char*)FUN_00f473a0(0x70, "Simulator", 0, 0, 0, 0);
  char* wa = nb4 ? (char*)FUN_010164d0(nb4) : 0;
  char* oldW = *(char**)(p + 0xbc);
  if (wa != oldW) {
    if (wa != 0) (*(void(__thiscall**)(void*))(*(void***)wa + 1))(wa);
    *(char**)(p + 0xbc) = wa;
    if (oldW != 0) (*(void(__thiscall**)(void*))(*(void***)oldW + 2))(oldW);
  }
  FUN_01015f50(*(void**)(p + 0xbc));

  u32 wstr[3];
  wstr[0] = 0; wstr[1] = 0; wstr[2] = 0;
  FUN_00579a90(wstr, (const void*)0x014772a0);
  char* nb5 = (char*)FUN_00f473a0(0x2fc, "Simulator/cCommunityEditor", 0, 0, 0, 0);
  char* ce = nb5 ? (char*)FUN_00d0d200(nb5) : 0;
  char* oldC = *(char**)(p + 0x20);
  if (ce != oldC) {
    if (ce != 0) (*(void(__thiscall**)(void*))(*(void***)ce + 2))(ce);
    *(char**)(p + 0x20) = ce;
    if (oldC != 0) (*(void(__thiscall**)(void*))(*(void***)oldC + 3))(oldC);
  }
  FUN_00d0a760(*(void**)(p + 0x20), wstr, 0x54e13add, 0, (void*)1);

  if (*(void**)(p + 0x40) == 0) {
    char* nb6 = (char*)FUN_00f473a0(0x98, "Simulator", 0, 0, 0, 0);
    char* pi = nb6 ? (char*)FUN_00ff5190(nb6) : 0;
    char* oldI = *(char**)(p + 0x40);
    if (pi != oldI) {
      if (pi != 0) (*(void(__thiscall**)(void*))(*(void***)pi + 0))(pi);
      *(char**)(p + 0x40) = pi;
      if (oldI != 0) (*(void(__thiscall**)(void*))(*(void***)oldI + 1))(oldI);
    }
    (*(void(__thiscall**)(void*))(*(void***)*(void**)(p + 0x40) + 0x54 / 4))(*(void**)(p + 0x40));
  }

  char* srv = (char*)FUN_00883860();
  *(char**)(p + 0x58) = srv;
  *(char**)(p + 0x5c) = p + 0x10;
  *(u32*)(p + 0x60) = 0x014952a0;
  *(u32*)(p + 0x64) = 0x2f;
  *(u32*)(p + 0x68) = 0;
  if (srv != 0 && (p + 0x10) != 0) {
    for (u32 off = 0; off < 0xbc; off += 4) {
      u32 v = *(u32*)(0x014952a0 + off);
      (*(void(__thiscall**)(void*, char*, u32))(*(void***)srv + 0x24 / 4))(srv, p + 0x10, v);
    }
  }

  if (*(void**)(p + 0x14) == 0) {
    char* nb7 = (char*)FUN_00f473a0(0x6ac, "Simulator", 0, 0, 0, 0);
    char* us = nb7 ? (char*)FUN_01070ba0(nb7) : 0;
    char* oldS = *(char**)(p + 0x14);
    if (us != oldS) {
      if (us != 0) (*(void(__thiscall**)(void*))(*(void***)us + 0))(us);
      *(char**)(p + 0x14) = us;
      if (oldS != 0) (*(void(__thiscall**)(void*))(*(void***)oldS + 1))(oldS);
    }
    FUN_01073700(*(void**)(p + 0x14));
  }
  if (*(void**)(p + 0x18) == 0) {
    char* nb8 = (char*)FUN_00f473a0(0x128, "Simulator", 0, 0, 0, 0);
    char* o8 = nb8 ? (char*)FUN_010762e0(nb8) : 0;
    char* old8 = *(char**)(p + 0x18);
    if (o8 != old8) {
      if (o8 != 0) (*(void(__thiscall**)(void*))(*(void***)o8 + 0))(o8);
      *(char**)(p + 0x18) = o8;
      if (old8 != 0) (*(void(__thiscall**)(void*))(*(void***)old8 + 1))(old8);
    }
    FUN_01075490(*(void**)(p + 0x18));
  }
  FUN_00b22960(FUN_00b3d300());

  if (a1[0] != 0 && *(int*)(a1 + 0x58) != 0) {
    char* uf = (char*)FUN_00ffbe50();
    char* inv = (char*)FUN_00a1ad60(uf);
    if (inv != 0) {
      FUN_00c37180(inv, a1 + 0x58, 1);
    }
  }
  FUN_00fe7160(*(void**)(p + 0x30));
  FUN_00bc3130(p + 0x90);
  FUN_010060d0(self);
  FUN_00f67d90(FUN_00b3d300());
  FUN_00c75a50((void*)0);
  FUN_01005d80(self, 1, 1);
  FUN_008de1a0();

  if (*(void**)(p + 0x44) == 0) {
    char* nb9 = (char*)FUN_00926020(0xc, 0, 0, 0, 0, 0);
    char* b9 = nb9 ? (char*)FUN_00998820(nb9) : 0;
    char* old9 = *(char**)(p + 0x44);
    if (b9 != old9) {
      if (b9 != 0) (*(void(__thiscall**)(void*))(*(void***)b9 + 1))(b9);
      *(char**)(p + 0x44) = b9;
      if (old9 != 0) (*(void(__thiscall**)(void*))(*(void***)old9 + 2))(old9);
    }
    void* rm = FUN_0067dcd0();
    (*(void(__thiscall**)(void*, int, char*, int))(*(void***)rm + 0x44 / 4))(rm, 1, *(char**)(p + 0x44), 0);
  }
}

// @ 0x01007430
void __fastcall FUN_01007430(void* self, void* /*edx*/)
{
  char* p = (char*)self;

  void* tick = FUN_00b3d330();
  (*(void(__thiscall**)(void*, void*))(*(void***)tick + 0x50 / 4))(tick, self);
  FUN_00b6a530();

  char* handler = (p != 0) ? p + 0x10 : 0;
  char* srv = (char*)FUN_00883860();
  *(char**)(p + 0x58) = srv;
  *(char**)(p + 0x5c) = handler;
  *(u32*)(p + 0x60) = 0x014952a0;
  *(u32*)(p + 0x64) = 0x2f;
  *(u32*)(p + 0x68) = 0;
  if (srv != 0 && handler != 0) {
    for (u32 off = 0; off < 0xbc; off += 4) {
      u32 v = *(u32*)(0x014952a0 + off);
      (*(void(__thiscall**)(void*, char*, u32))(*(void***)srv + 0x24 / 4))(srv, handler, v);
    }
  }

  if (*(void**)(p + 0x54) != 0) {
    FUN_00ff5b50(*(void**)(p + 0x54));
  }

  char* uf = (char*)FUN_00ffbe50();
  char* oldU = *(char**)(p + 0xb4);
  if (uf != oldU) {
    if (uf != 0) (*(void(__thiscall**)(void*))(*(void***)uf + 1))(uf);
    *(char**)(p + 0xb4) = uf;
    if (oldU != 0) (*(void(__thiscall**)(void*))(*(void***)oldU + 2))(oldU);
  }
  FUN_00ffbf60(*(void**)(p + 0xb4));

  char* mm = (char*)FUN_00feb9f0();
  char* oldM = *(char**)(p + 0xb8);
  if (mm != oldM) {
    if (mm != 0) (*(void(__thiscall**)(void*))(*(void***)mm + 1))(mm);
    *(char**)(p + 0xb8) = mm;
    if (oldM != 0) (*(void(__thiscall**)(void*))(*(void***)oldM + 2))(oldM);
  }
  FUN_00fee310(*(void**)(p + 0xb8));

  {
    char* g = *(char**)0x016dcd54;
    char* oldG = *(char**)(p + 0xbc);
    if (g != oldG) {
      if (g != 0) (*(void(__thiscall**)(void*))(*(void***)g + 1))(g);
      *(char**)(p + 0xbc) = g;
      if (oldG != 0) (*(void(__thiscall**)(void*))(*(void***)oldG + 2))(oldG);
    }
    FUN_00b6f4c0(*(void**)(p + 0xbc));
  }
  {
    char* g = *(char**)0x016dc798;
    char* oldG = *(char**)(p + 0xc0);
    if (g != oldG) {
      if (g != 0) (*(void(__thiscall**)(void*))(*(void***)g + 1))(g);
      *(char**)(p + 0xc0) = g;
      if (oldG != 0) (*(void(__thiscall**)(void*))(*(void***)oldG + 2))(oldG);
    }
    FUN_00b6f4c0(*(void**)(p + 0xc0));
  }

  if (*(void**)(p + 0x40) != 0) {
    (*(void(__thiscall**)(void*))(*(void***)*(void**)(p + 0x40) + 0x40 / 4))(*(void**)(p + 0x40));
  }

  u32 wstr[3];
  wstr[0] = 0; wstr[1] = 0; wstr[2] = 0;
  FUN_00579a90(wstr, (const void*)0x014772a0);
  char* nb5 = (char*)FUN_00f473a0(0x2fc, "Simulator/cCommunityEditor", 0, 0, 0, 0);
  char* ce = nb5 ? (char*)FUN_00d0d200(nb5) : 0;
  char* oldC = *(char**)(p + 0x20);
  if (ce != oldC) {
    if (ce != 0) (*(void(__thiscall**)(void*))(*(void***)ce + 2))(ce);
    *(char**)(p + 0x20) = ce;
    if (oldC != 0) (*(void(__thiscall**)(void*))(*(void***)oldC + 3))(oldC);
  }
  FUN_00d0a760(*(void**)(p + 0x20), wstr, 0x54e13add, 0, (void*)1);

  if (*(void**)(p + 0x44) == 0) {
    char* nb9 = (char*)FUN_00926020(0xc, 0, 0, 0, 0, 0);
    char* b9 = nb9 ? (char*)FUN_00998820(nb9) : 0;
    char* old9 = *(char**)(p + 0x44);
    if (b9 != old9) {
      if (b9 != 0) (*(void(__thiscall**)(void*))(*(void***)b9 + 1))(b9);
      *(char**)(p + 0x44) = b9;
      if (old9 != 0) (*(void(__thiscall**)(void*))(*(void***)old9 + 2))(old9);
    }
    void* rm = FUN_0067dcd0();
    (*(void(__thiscall**)(void*, int, char*, int))(*(void***)rm + 0x44 / 4))(rm, 1, *(char**)(p + 0x44), 0);
  }
  if (*(void**)(p + 0x14) == 0) {
    char* nb7 = (char*)FUN_00f473a0(0x6ac, "Simulator", 0, 0, 0, 0);
    char* us = nb7 ? (char*)FUN_01070ba0(nb7) : 0;
    char* oldS = *(char**)(p + 0x14);
    if (us != oldS) {
      if (us != 0) (*(void(__thiscall**)(void*))(*(void***)us + 0))(us);
      *(char**)(p + 0x14) = us;
      if (oldS != 0) (*(void(__thiscall**)(void*))(*(void***)oldS + 1))(oldS);
    }
    FUN_01073700(*(void**)(p + 0x14));
  }
  FUN_00e184d0(FUN_00b3d400_s0100_6880());

  if (*(void**)(p + 0x18) == 0) {
    char* nb8 = (char*)FUN_00f473a0(0x128, "Simulator", 0, 0, 0, 0);
    char* o8 = nb8 ? (char*)FUN_010762e0(nb8) : 0;
    char* old8 = *(char**)(p + 0x18);
    if (o8 != old8) {
      if (o8 != 0) (*(void(__thiscall**)(void*))(*(void***)o8 + 0))(o8);
      *(char**)(p + 0x18) = o8;
      if (old8 != 0) (*(void(__thiscall**)(void*))(*(void***)old8 + 1))(old8);
    }
    FUN_01075490(*(void**)(p + 0x18));
  }

  FUN_00fe7160(*(void**)(p + 0x30));
  if (FUN_00685520_s0100_6880(2) != 0) {
    FUN_00c75a50(FUN_00f67d90(FUN_00b3d300()));
    FUN_00c32980(FUN_01021300());
  }
  FUN_01005d80(self, 0, 0);
  FUN_010060d0(self);
  FUN_0102b620();
}

// @ 0x010077e0
void cSPSimulatorSpaceGame_s0100_77e0::ChaseFromGalaxyToSolar()
{
    cSPSimulatorSpaceGame_s0100_77e0* self = this;
    cSPSimulatorSpaceGame_s0100_77e0* sim = GetUFOSimulator_s0100_77e0();
    sim->BeginChase(1);
    cSPGameDataUFO_s0100_77e0* player = sim->GetPlayerInventory();
    const Vector3* playerPos = player->mSpatial.GetPosition();

    cSPGameDataUFO_s0100_77e0** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO_s0100_77e0** nxt = cur + 1;
        cSPGameDataUFO_s0100_77e0* ufo = *cur;
        bool bErase = false;
        if (ufo->IsDestroyed()) {
            bErase = true;
        } else {
            if (ufo->mState == 8) {
                unsigned int handle = *(unsigned int*)((char*)ufo->mp7b0 + 0x70);
                GetStarMap()->RemoveVisual(handle, 0xb7735c3, 0, 1);

                double a = (double)ufo->mAngleSeed6b0 * kOrbitSpeed * 0.41176471f * 0.5f;
                float s = (float)sin(a);
                float c = (float)cos(a);
                float ax = s * kZAxis.x;
                float ay = s * kZAxis.y;
                float az = s * kZAxis.z;
                ufo->mDir694.x = ((c * ay + az * ax) * kYAxis.z + (ax * ay - c * az) * kYAxis.y) * 2.0f
                                 + (1.0f - (az * az + ay * ay) * 2.0f) * kYAxis.x;
                ufo->mDir694.y = ((az * ay - c * ax) * kYAxis.z + (c * az + ax * ay) * kYAxis.x) * 2.0f
                                 + (1.0f - (az * az + ax * ax) * 2.0f) * kYAxis.y;
                ufo->mDir694.z = (c * ax + az * ay) * kYAxis.y * 2.0f + (az * ax - c * ay) * kYAxis.x
                                 + (1.0f - (ax * ax + ay * ay) * 2.0f) * kYAxis.z;

                if (!GetBackgroundSim()->FUN_00c8b800())
                    bErase = true;
            }
            {
                float inv = (float)(1.0 / sqrt((double)ufo->mDir694.x * (double)ufo->mDir694.x
                                             + (double)ufo->mDir694.y * (double)ufo->mDir694.y
                                             + (double)ufo->mDir694.z * (double)ufo->mDir694.z));
                Vector3 n;
                n.x = ufo->mDir694.x * inv;
                n.y = ufo->mDir694.y * inv;
                n.z = ufo->mDir694.z * inv;

                Vector3 dest;
                dest.x = playerPos->x + n.x * kDist100;
                dest.y = playerPos->y + n.y * kDist100;
                dest.z = playerPos->z + n.z * kDist100;
                ufo->SetDestination(&dest);
                ufo->PopToDestination();

                Vector3 facing;
                facing.x = -n.x;
                facing.y = -n.y;
                facing.z = -n.z;
                Quaternion q;
                QuaternionFromFacingAndUp(&q, &facing, &kZAxis);
                ufo->mOrientation = q;
                ufo->OnContextChange(1);
            }
        }

        if (!bErase) {
            ++cur;
            continue;
        }

        /* shared erase/release tail (LAB_01007b79) */
        if (!ufo->IsDestroyed())
            DestroyCreature((cCreatureData*)ufo, 0);
        for (cSPGameDataUFO_s0100_77e0** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
            *d++ = *s;
        self->mUFOsEnd -= 1;
        cSPGameDataUFO_s0100_77e0* tail = *self->mUFOsEnd;
        if (tail)
            tail->Release();
    }
}

// @ 0x01007bf0
void cSPSimulatorSpaceGame_s0100_77e0::ChaseFromSolarToPlanet()
{
    cSPSimulatorSpaceGame_s0100_77e0* self = this;
    cSPSimulatorSpaceGame_s0100_77e0* sim = GetUFOSimulator_s0100_77e0();
    sim->BeginChase(0);
    cSPGameDataUFO_s0100_77e0* player = sim->GetPlayerInventory();
    const Vector3* playerPos = player->mSpatial.GetPosition();

    float upInv = (float)(1.0 / sqrt((double)playerPos->x * (double)playerPos->x
                                    + (double)playerPos->y * (double)playerPos->y
                                    + (double)playerPos->z * (double)playerPos->z));
    Vector3 up;
    up.x = playerPos->x * upInv;
    up.y = playerPos->y * upInv;
    up.z = playerPos->z * upInv;

    cSPUIMinimapWin* win = self->mpSpaceUI->GetMinimap();

    cSPGameDataUFO_s0100_77e0** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO_s0100_77e0** nxt = cur + 1;
        cSPGameDataUFO_s0100_77e0* ufo = *cur;
        if (ufo->IsDestroyed()) {
            for (cSPGameDataUFO_s0100_77e0** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
                *d++ = *s;
            self->mUFOsEnd -= 1;
            cSPGameDataUFO_s0100_77e0* tail = *self->mUFOsEnd;
            if (tail)
                tail->Release();
            continue;
        }
        ++cur;

        if (ufo->mState == 8) {
            Vector3 tmp;
            Vector3* rd = RandomDirection3(&tmp);
            ufo->mDir694 = *rd;
        }
        float inv = (float)(1.0 / sqrt((double)ufo->mDir694.x * (double)ufo->mDir694.x
                                     + (double)ufo->mDir694.y * (double)ufo->mDir694.y
                                     + (double)ufo->mDir694.z * (double)ufo->mDir694.z));
        Vector3 n;
        n.x = ufo->mDir694.x * inv;
        n.y = ufo->mDir694.y * inv;
        n.z = ufo->mDir694.z * inv;

        Vector3 temp;
        temp.x = playerPos->x + n.x * kDist500;
        temp.y = playerPos->y + n.y * kDist500;
        temp.z = playerPos->z + n.z * kDist500;
        float tempInv = (float)(1.0 / sqrt((double)temp.x * (double)temp.x
                                          + (double)temp.y * (double)temp.y
                                          + (double)temp.z * (double)temp.z));
        Vector3 dest;
        dest.x = temp.x * tempInv * kDist1000;
        dest.y = temp.y * tempInv * kDist1000;
        dest.z = temp.z * tempInv * kDist1000;
        ufo->FlyTowards(&dest);

        Vector3 facing;
        facing.x = -n.x;
        facing.y = -n.y;
        facing.z = -n.z;
        Quaternion q;
        QuaternionFromFacingAndUp(&q, &facing, &up);
        ufo->mOrientation = q;
        ufo->OnContextChange(0);
        CreateMinimapIcon(ufo, win);
    }
}

// @ 0x01007ed0
void cSPSimulatorSpaceGame_s0100_77e0::ChaseFromPlanetToSolar()
{
    cSPSimulatorSpaceGame_s0100_77e0* self = this;
    const Vector3* planetPos = GetActivePlanet()->GetPosition();

    cSPSimulatorSpaceGame_s0100_77e0* sim = GetUFOSimulator_s0100_77e0();
    sim->BeginChase(1);
    cSPGameDataUFO_s0100_77e0* player = sim->GetPlayerInventory();

    Vector3 playerPos;
    player->mSpatial.GetPositionOut(&playerPos);

    cSPUIMinimapWin* win = self->mpSpaceUI->GetMinimap();

    cSPGameDataUFO_s0100_77e0** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO_s0100_77e0** nxt = cur + 1;
        cSPGameDataUFO_s0100_77e0* ufo = *cur;
        if (ufo->IsDestroyed()) {
            for (cSPGameDataUFO_s0100_77e0** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
                *d++ = *s;
            self->mUFOsEnd -= 1;
            cSPGameDataUFO_s0100_77e0* tail = *self->mUFOsEnd;
            if (tail)
                tail->Release();
            continue;
        }
        ++cur;

        unsigned int st = ufo->mState;
        if (st == 3) {
            cSPGameDataUFO_s0100_77e0* old = ufo->mpCached68c;
            if (player != old) {
                player->AddRef();
                ufo->mpCached68c = player;
                if (old)
                    old->Release();
            }
        } else if (st == 8) {
            double a = (double)ufo->mAngleSeed6b0 * kOrbitSpeed * 0.41176471f * 0.5f;
            float s = (float)sin(a);
            float c = (float)cos(a);
            float rot[4];
            rot[0] = s * kZAxis.x;
            rot[1] = s * kZAxis.y;
            rot[2] = s * kZAxis.z;
            rot[3] = c;
            Vector3 tmp;
            ufo->mDir694 = *QuatRotateAxis(&tmp, &kYAxis, rot);
        }

        ufo->SetDestination(planetPos);
        ufo->PopToDestination();

        Quaternion q;
        QuaternionFromFacingAndUp(&q, &playerPos, &kZAxis);
        ufo->mOrientation = q;
        ufo->mSpatial.Notify();
        ufo->OnContextChange(1);
        win->RemoveIcon(ufo, 1, 0);
    }
}

// @ 0x01008100
void cSPSimulatorSpaceGame_s0100_77e0::ChaseFromSolarToGalaxy()
{
    cSPSimulatorSpaceGame_s0100_77e0* self = this;
    Vector3* cityPos = GetCurrentStar()->GetCities();

    cSPSimulatorSpaceGame_s0100_77e0* sim = GetUFOSimulator_s0100_77e0();
    sim->BeginChase(2);
    cSPGameDataUFO_s0100_77e0* player = sim->GetPlayerInventory();

    Vector3 playerPos;
    player->mSpatial.GetPositionOut(&playerPos);

    cSPGameDataUFO_s0100_77e0** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO_s0100_77e0** nxt = cur + 1;
        cSPGameDataUFO_s0100_77e0* ufo = *cur;
        if (ufo->IsDestroyed()) {
            for (cSPGameDataUFO_s0100_77e0** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
                *d++ = *s;
            self->mUFOsEnd -= 1;
            cSPGameDataUFO_s0100_77e0* tail = *self->mUFOsEnd;
            if (tail)
                tail->Release();
            continue;
        }
        ++cur;

        ufo->SetDestination(cityPos);
        ufo->PopToDestination();
        ufo->SetDestinationOffset(&kChaseOffset);

        Vector3 d2;
        d2.x = cityPos->x + kZAxis.x;
        d2.y = cityPos->y + kZAxis.y;
        d2.z = cityPos->z + kZAxis.z;
        ufo->SetDestination(&d2);

        Quaternion q;
        QuaternionFromFacingAndUp(&q, &playerPos, &kZAxis);
        ufo->mOrientation = q;
        ufo->mSpatial.Notify();
        ufo->OnContextChange(2);
    }
}

// @ 0x01008270
void cSPSimulatorSpaceGame_s0100_77e0::UpdateChasingUFOs(unsigned int param)
{
    cSPSimulatorSpaceGame_s0100_77e0* self = this;
    unsigned int posseSeed = 0;        // state-3 orbit seed counter
    unsigned int interceptorSeed = 0;  // state-8 orbit seed counter

    cSPGameDataUFO_s0100_77e0** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO_s0100_77e0** nxt = cur + 1;
        cSPGameDataUFO_s0100_77e0* ufo = *cur;
        bool erase = false;

        unsigned int idx = ufo->mState - 3;
        if (idx <= 6) {
            switch (ufo->mState) {
            case 3:
                ufo->mAngleSeed6b0 = (int)posseSeed;
                ++posseSeed;
                UpdatePosseUFO(ufo, param, 10.0f, 0.7f, 10.0f);
                break;

            case 6: {
                double dx = (double)ufo->mPos718.x - (double)ufo->mTargetPos750.x;
                double dy = (double)ufo->mPos718.y - (double)ufo->mTargetPos750.y;
                double dz = (double)ufo->mPos718.z - (double)ufo->mTargetPos750.z;
                float dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
                if (dist >= kNearTargetDist)
                    break;                       // too far, leave as is
                if (ufo->mp75c == 0) {
                    float pdist = (float)sqrt((double)ufo->mPos718.x * (double)ufo->mPos718.x
                                             + (double)ufo->mPos718.y * (double)ufo->mPos718.y
                                             + (double)ufo->mPos718.z * (double)ufo->mPos718.z);
                    if (pdist >= kNearPosDist) {
                        erase = true;            // LAB_01008318
                        break;
                    }
                    ufo->SetDestination(&ufo->mVec6bc);
                } else {
                    float invPos = (float)(1.0 / sqrt((double)ufo->mPos718.x * (double)ufo->mPos718.x
                                                     + (double)ufo->mPos718.y * (double)ufo->mPos718.y
                                                     + (double)ufo->mPos718.z * (double)ufo->mPos718.z));
                    float invDest = (float)(1.0 / sqrt((double)ufo->mVec6bc.x * (double)ufo->mVec6bc.x
                                                              + (double)ufo->mVec6bc.y * (double)ufo->mVec6bc.y
                                                              + (double)ufo->mVec6bc.z * (double)ufo->mVec6bc.z));
                    Vector3 sum;
                    sum.x = ufo->mVec6bc.x * invDest + ufo->mPos718.x * invPos;
                    sum.y = ufo->mVec6bc.y * invDest + ufo->mPos718.y * invPos;
                    sum.z = ufo->mVec6bc.z * invDest + ufo->mPos718.z * invPos;
                    float invSum = (float)(1.0 / sqrt((double)sum.x * (double)sum.x
                                                     + (double)sum.y * (double)sum.y
                                                     + (double)sum.z * (double)sum.z));
                    float scale = GetBackgroundSim()->GetSolarSystem()->FUN_00c84d40(0) + 20.0f;
                    Vector3 dest;
                    // retail reads the destination back out of the sum/normalise scratch:
                    // the x component uses the un-normalised sum.z, y/z use -n.x/-n.y.
                    dest.x = sum.z * scale;
                    dest.y = -sum.x * invSum * scale;
                    dest.z = -sum.y * invSum * scale;
                    ufo->SetDestination(&dest);
                }
                break;
            }

            case 8:
                ufo->mAngleSeed6b0 = (int)interceptorSeed;
                ++interceptorSeed;
                if (!UpdateInterceptorUFO(ufo, false))
                    break;
                erase = true;                    // fall into LAB_01008318
                break;

            case 9: {
                double dx = (double)ufo->mPos718.x - (double)ufo->mTargetPos750.x;
                double dy = (double)ufo->mPos718.y - (double)ufo->mTargetPos750.y;
                double dz = (double)ufo->mPos718.z - (double)ufo->mTargetPos750.z;
                float dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
                if (dist < kDist5)
                    erase = true;                // close enough -> retask
                break;
            }

            default:                             // states 4, 5, 7
                break;
            }
        }

        if (!erase) {
            ++cur;
            continue;
        }

        /* LAB_01008318: flag the craft and retask it if the host says so */
        ufo->mb77e = true;
        if (!ufo->FUN_00c370e0()) {
            ++cur;
            continue;
        }
        DestroyCreature((cCreatureData*)ufo, 0);
        for (cSPGameDataUFO_s0100_77e0** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
            *d++ = *s;
        self->mUFOsEnd -= 1;
        cSPGameDataUFO_s0100_77e0* tail = *self->mUFOsEnd;
        if (tail)
            tail->Release();
    }
}

// @ 0x01008820
void TCopyForward(UFOElem* first, UFOElem* last, UFOElem* dst)
{
    if (first != last) {
        do {
            dst->mpLink0c = first->mpLink0c;
            dst->mpLink10 = first->mpLink10;
            ++first;
            ++dst;
        } while (first != last);
    }
}

// @ 0x01008850
UFOElem* UFOArray::erase(UFOElem* first, UFOElem* last)
{
    UFOElem* dst = first;
    if (last != this->mpEnd) {
        UFOElem* src = last;
        do {
            dst->mpLink0c = src->mpLink0c;
            dst->mpLink10 = src->mpLink10;
            ++src;
            ++dst;
        } while (src != this->mpEnd);
    }
    for (UFOElem* p = dst; p < this->mpEnd; ++p)
        p->Destroy(0);
    this->mpEnd += last - first;
    return first;
}

// @ 0x010088e0
void TCopyBackward(UFOElem* first, UFOElem* last, UFOElem* dst)
{
    while (last != first) {
        --last;
        --dst;
        dst->mpLink0c = last->mpLink0c;
        dst->mpLink10 = last->mpLink10;
    }
}

// @ 0x01009ab0
void* cObjectList::EraseFront(u8* p)
{
    if (p + 0x14 < mpEnd)
        FUN_01008820(p + 0x14, mpEnd, p);
    mpEnd = mpEnd - 0x14;
    void* obj = *(void**)mpEnd;
    VT_08_1(obj, 0);
    return p;
}

// @ 0x0139d420
void PropTableInit_d420()
{
    PropDesc d;
    d.name = "mPlayerInventory"; d.hash = 0x22556eau;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_010061f0;
    d.f28 = (void*)&FUN_00bca960; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f550;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x40u;
    g_props_d420[0] = d;

    d.name = "mHighLODPlanetSim"; d.hash = 0x22556f0u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_01006220;
    d.f28 = (void*)(bool(__cdecl *)(void *, void **))FUN_01006600; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00fd9e80;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x54u;
    g_props_d420[1] = d;

    d.name = "mBadgeManager"; d.hash = 0x22556f1u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_01006250;
    d.f28 = (void*)(bool(__cdecl *)(void *, void **))FUN_01006600; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00fd9e80;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x70u;
    g_props_d420[2] = d;

    d.name = "mTimeSinceStartedSpaceGame"; d.hash = 0x57a55b9u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00ae3470;
    d.f28 = (void*)&FUN_00ae3490; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00ae3310;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x90u;
    g_props_d420[3] = d;

    d.name = "mNPC_UFOs"; d.hash = 0x53eb2edu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_01008680;
    d.f28 = (void*)&FUN_00aca730; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f860;
    d.f38 = (void*)&FUN_00c6c390;
    d.offset = 0x78u;
    g_props_d420[4] = d;

    d.name = "mPlanetsToUplift"; d.hash = 0x670c962u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_0100a640;
    d.f28 = (void*)&FUN_01002e30; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_01005360;
    d.f38 = (void*)&FUN_00c51440;
    d.offset = 0xdcu;
    g_props_d420[5] = d;
}
