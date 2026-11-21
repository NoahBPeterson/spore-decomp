// src/game/SPGonzago/SPCity.cpp -- migrated from slice(s) s00beb6d0, s00bea930, s00be9850, s00be6f90, s00be6310, s00be4000, s00be10d0, s00bdfd30, s00bdee20, s00bdde70, s00bdc350, s00bda190, s00bd5ea0, s0132d6d0, s0132abc0, s00be9d60, s00be30e0, s00bdd380, s00bdb3b0, s00bd91e0, s00bd8140 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCity.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_14682dc[];
extern "C" char g_1468300[];
extern "C" char g_1468324[];
extern "C" char g_1468350[];
extern "C" char g_1464450[];
extern "C" char g_1465d54[];
extern "C" char g_1467f40[];
extern "C" char g_1467f48[];
extern "C" char g_1467f50[];
extern "C" char g_1467f58[];
extern "C" char g_1467f60[];
extern "C" char g_1467f74[];
extern "C" char g_1467f90[];
extern "C" char g_1467fa0[];
extern "C" char g_1467fb0[];
extern "C" char g_14682ac[];
extern "C" char g_14684d8[];
extern "C" char g_14685a0[];
extern "C" char g_1468608[];
extern "C" char g_1468618[];
extern "C" char g_168bd4c[];

#include "game/types.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cCity.h"
#include "SP/cCityWalls.h"
#include "SP/cCivilization.h"
#include "SP/cCulturalTarget.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpatialObject.h"
#include "SP/cStarManager.h"
#include "SP/cTurret.h"
#include <math.h>
#include "SP/cCombatant.h"
#include "SP/cSPTimer.h"
#include "SP/cActionCircle.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "SP/cCelestialBody.h"
#include "SP/cEllipticalOrbit.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cInteractionTarget.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "cSPVector3.h"
#include "SP/cVarListSerializer.h"
#include "SP/cIPropertyManager.h"
#include "SP/cPropertyList.h"
#include "SP/cTerrainSphere.h"
#include <stddef.h>
#include <xmmintrin.h>
#include "SP/cEmptyBubble.h"
#include "EA/Variant.h"
#include "SP/cString.h"
#include <string.h>
#include "SP/cCommunity.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cEffectDesc.h"
#include "SP/cVehicle.h"
#include <stdlib.h>
#include "SP/cCityTerritory.h"

// unnamed retail callees and globals (address in the comment)
extern "C" extern double sqrt(double);
extern "C" void  __cdecl FUN_00c004a0(void);                          // 0x00c004a0
extern "C" void  __fastcall FUN_00b638b0(void* ecx_this);              // 0x00b638b0 cGonzagoTimer dtor
extern "C" void* __cdecl FUN_00b3d350();                              // 0x00b3d350 SP::PlanetModel
extern "C" void* __cdecl FUN_00b3d300();                              // 0x00b3d300 SP::NounManager
extern "C" void* __cdecl FUN_00b3d240();                              // 0x00b3d240 (effect manager)
extern "C" void* __stdcall FUN_00b3d430(int a);                      // 0x00b3d430 SP::TerraformingManager
extern "C" void* __cdecl FUN_00b3d480(void* a);                       // 0x00b3d480
extern "C" void* __cdecl FUN_00b3d4d0();                              // 0x00b3d4d0 GetTriggerMgr
extern "C" void* __cdecl FUN_01021260();                              // 0x01021260 GetActivePlanet
extern "C" void* __cdecl FUN_010212a0();                              // 0x010212a0 GetActivePlanetRecord
extern "C" int   __cdecl FUN_00b5b800();                              // 0x00b5b800 GetCurrentGameMode
extern "C" void  __cdecl FUN_00ac8d60(void* a);                       // 0x00ac8d60
extern float g_13f1cac;         // 0x013f1cac  (50.0f)
extern float g_13ec4b8;         // 0x013ec4b8  (1e-08f)
extern float g_13ec4d0;         // 0x013ec4d0  (100.0f)
extern float g_1468454;         // 0x01468454
extern float g_146847c;         // 0x0146847c  (FLT_MAX)
extern void* g_1601760;         // 0x01601760  (math random state)
#pragma warning(disable : 4100)

// ---- items of slice s00bd8140 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
struct Float3 { float x, y, z; };
struct cCity;
extern "C" extern double sqrt(double);
extern "C" void  __cdecl FUN_00c004a0(void);                          // 0x00c004a0
extern "C" void  __fastcall FUN_00b638b0(void* ecx_this);              // 0x00b638b0 cGonzagoTimer dtor
extern "C" void* __cdecl FUN_00b3d350();                              // 0x00b3d350 SP::PlanetModel
extern "C" void* __cdecl FUN_00b3d300();                              // 0x00b3d300 SP::NounManager
extern "C" void* __cdecl FUN_00b3d240();                              // 0x00b3d240 (effect manager)
extern "C" void* __stdcall FUN_00b3d430(int a);                      // 0x00b3d430 SP::TerraformingManager
extern "C" void* __cdecl FUN_00b3d480(void* a);                       // 0x00b3d480
extern "C" void* __cdecl FUN_00b3d4d0();                              // 0x00b3d4d0 GetTriggerMgr
extern "C" void* __cdecl FUN_01021260();                              // 0x01021260 GetActivePlanet
extern "C" void* __cdecl FUN_010212a0();                              // 0x010212a0 GetActivePlanetRecord
extern "C" int   __cdecl FUN_00b5b800();                              // 0x00b5b800 GetCurrentGameMode
struct cPlanetRecord
{
int  GameMode();                                    // 0x00b8dab0 (thiscall)
};
struct cTerraformingMgr
{
int  TerraformCount();                              // 0x00bbe5f0 (thiscall)
};
struct cTriggerMgr
{
u8  pad00[0x2c];
int mMode2c;                                        // +0x2c
};
struct Entry80
{
u8    pad00[0x70];
void* mp70;                                         // +0x70
u8    pad74[0x78 - 0x74];
void* mp78;                                         // +0x78
u8    pad7c[0x80 - 0x7c];
};
struct cCivData
{
int** GetCities();                                  // 0x00c5c65e0 (thiscall)
void  RemoveAt(int i, void* other);                 // 0x00ff2d50 (thiscall)
u8    pad000[0x3c];
int*  mBeg3c;                                       // +0x3c
int*  mEnd40;                                       // +0x40
};
struct cPlanet
{
cCivData* GetCiv(void* a);                          // 0x00c71040 (thiscall)
};
extern "C" void  __cdecl FUN_00ac8d60(void* a);                       // 0x00ac8d60
char  __fastcall FUN_00b183f0(void* ecx_this, void* edx, void* a);  // 0x00b183f0
void  __fastcall FUN_00bebdd0(void* ecx_this, void* edx, void* a);  // 0x00bebdd0
char  __fastcall FUN_00ac8d60(void* ecx_this, void* edx, void* a);  // 0x00ac8d60
void  __fastcall FUN_00bd7d90(void* ecx_this, void* edx);           // 0x00bd7d90
u32   __fastcall RandomUint32Uniform(void* ecx_this, void* edx, u32 n);     // 0x00a68fb0
char  __fastcall FUN_00c004c0(void* ecx_this, void* edx, int a);     // 0x00c004c0
extern u32   g_168d248;         // 0x0168d248
extern u32   g_169c088;         // 0x0169c088
extern float g_13f1cac;         // 0x013f1cac  (50.0f)
extern float g_13ec4b8;         // 0x013ec4b8  (1e-08f)
extern float g_13ec4d0;         // 0x013ec4d0  (100.0f)
extern float g_1468454;         // 0x01468454
extern float g_146847c;         // 0x0146847c  (FLT_MAX)
extern u32   g_1654c05;         // 0x01654c05  (GetCurrentGameMode result)
extern void* g_1601760;         // 0x01601760  (math random state)
struct cSPTimer
{
    virtual ~cSPTimer();
    u8 pad04[0x20 - 0x04];
    char IsRunning();                                   // 0x00feba90
    long long GetElapsedTime();                         // 0x00bc3190 (edx:eax)
    void Restart();                                     // 0x00bc3130
};
struct IObj
{
    virtual void  v00();                                 // +0x00
    virtual void  v04();                                 // +0x04
    virtual void  v08();                                 // +0x08
    virtual void* Cast(u32 id);                          // +0x0c
    virtual void* Slot10();                              // +0x10
    virtual void  v14();                                 // +0x14
    virtual void  v18();                                 // +0x18
    virtual void  v1c();                                 // +0x1c
    virtual void  v20();                                 // +0x20
    virtual void  v24();                                 // +0x24
    virtual void  v28();                                 // +0x28
    virtual Float3* GetPosition();                       // +0x2c
    virtual void* v30();                                 // +0x30
    virtual void  v34();                                 // +0x34
    virtual u32   GetTypeId();                           // +0x38
    virtual void  v3c();                                 // +0x3c
    virtual void  v40();                                 // +0x40
    virtual void  v44();                                 // +0x44
    virtual void  v48();                                 // +0x48
    virtual u32   Slot4c(u32 a, float b);                // +0x4c
    virtual void  v50();                                 // +0x50
    virtual u32   Slot54();                              // +0x54
    virtual u32   Slot58(Float3* out);                   // +0x58
    virtual u32   Slot5c(Float3* out, u32 a);            // +0x5c
    virtual void  v60();                                 // +0x60
    virtual void  v64();                                 // +0x64
    virtual void  v68();                                 // +0x68
    virtual u32   Slot6c();                              // +0x6c

    void SetEffectId(u32 id, float v);                   // 0x00c3f160
    void DoF3d2(void* a);                                // 0x00c3f2d0
};
struct CSlot38
{
    u8   pad000[0x1d4 - 0x38];
    void DoC470(int a);                                  // 0x00bfc470
};
struct cCityRegion38
{
    u8   pad000[0x100 - 0x38];
    IObj mObj100;                                       // +0x100 embedded interface
    u8   pad104[0x1d4 - 0x104];

    CSlot38* AsSlot38() { return (CSlot38*)(void*)this; }
};
struct IFwd
{
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
    virtual void Call38(void* a);                        // +0x38
};
struct cCom108
{
    u8   pad000[0x70];
    IFwd mFwd70;                                         // +0x70
};
struct cCommunity
{
    void     func54h(void* a);                           // 0x00c88670
    u8       pad000[0x108];
    cCom108* mp108;                                      // +0x108
};
struct cGameNounManager
{
    IObj* CreateNoun(u32 id);                            // 0x00b20c60
    int   GetPlayerEmpireOrMinus1();                     // 0x00b1f9d0
};
struct cPlanetModel
{
    void GetContinent(u32 id);                           // 0x00b88590
    void Attach(void* b);                                // 0x00b7e360
    void Despawn(void* b);                               // 0x00b8d420
    void Spawn(void* a, void* b);                        // 0x00b86650
    void SpawnAlt(void* a, void* b);                     // 0x00b866f0
    char Probe(void* target, float a, Float3* out);      // 0x00b88f60
    Float3* Sample(Float3* out);                         // 0x00b81720
};
struct cTarget55c
{
    void AddEntry(cCity* a, void* b, int c);             // 0x00c41c60
    u8   pad000[0x11c];
    void* p11c;                                          // +0x11c
};
struct cElem55c
{
    void*        p0;                                     // +0x00
    cTarget55c*  p4;                                     // +0x04
    int          kind;                                   // +0x08
};
struct ISlot120
{
    char Test();                                        // 0x00bfc600
    u8   pad01[4];
};
struct cCombatCarrier : IObj
{
    u8   pad004[0x34 - 0x04];
    IObj mObj34;                                        // +0x34 embedded interface
    u8   pad038[0x120 - 0x38];
    ISlot120 mSlot120;                                  // +0x120
    u8   pad124[0x289 - 0x124];
    u8   b289;                                          // +0x289
    u8   pad28a[0x290 - 0x28a];
    int  i290;                                          // +0x290
    u8   pad294[0x508 - 0x294];
    IObj mObj508;                                       // +0x508 embedded interface
    u8   pad50c[0x588 - 0x50c];
    ISlot120 mSlot588;                                  // +0x588
    u8   pad58c[0x684 - 0x58c];
    int  i684;                                          // +0x684
    u8   pad688[0xb1c - 0x688];
    int  iB1c;                                          // +0xb1c
};
struct IX54
{
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
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual u32  Slot5c(u32 a);                         // +0x5c
};
struct IX508
{
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
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual void v50();
    virtual IX54* Slot54();                             // +0x54
    virtual void  v58();
    virtual u32   Slot5c(u32 a);                        // +0x5c
    int   GetFileCount();                               // 0x008e7f80
    float Distance();                                   // 0x00bfc490
};
struct cElem1f4
{
    u8    pad000[0x508];
    IX508 mObj508;                                      // +0x508
    u8    pad50c[0xc50 - 0x50c];
    float f0c50;                                        // +0xc50
};
struct cCity
{
    // vtable pointer at +0 (a single vptr; the individual virtual slots are not touched here).
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
    virtual char v2c();                                 // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
    virtual void v40();

    u8    pad04[0x38 - 0x04];
    cCityRegion38 mRegion38;        // +0x38 overlay region (mTurrets & friends)
    u8    b1d4;                     // 0x1d4
    u8    pad1d5[0x1d8 - 0x1d5];
    int   i1d8;                     // 0x1d8
    int   i1dc;                     // 0x1dc
    cCity** mBeg1e0;                // 0x1e0
    cCity** mEnd1e4;                // 0x1e4
    u8    pad1e8[0x1f4 - 0x1e8];
    cElem1f4** mBeg1f4;             // 0x1f4
    cElem1f4** mEnd1f8;             // 0x1f8
    u8    pad1fc[0x208 - 0x1fc];
    IObj* mp208;                    // 0x208
    u8    pad20c[0x230 - 0x20c];
    cSPTimer mTimer230;             // 0x230
    cSPTimer mTimer250;             // 0x250
    cSPTimer mTimer270;             // 0x270
    u32   u290;                     // 0x290  (low half of the timer-270 deadline)
    u32   u294;                     // 0x294  (high half)
    u8    pad298[0x2e3 - 0x298];
    u8    b2e3;                     // 0x2e3
    u8    pad2e4[0x2e5 - 0x2e4];
    u8    b2e5;                     // 0x2e5
    u8    pad2e6[0x2f0 - 0x2e6];
    u32   u2f0;                     // 0x2f0
    int   u2f4;                     // 0x2f4
    int   u2f8;                     // 0x2f8
    u8    b2fc;                     // 0x2fc
    u8    pad2fd[0x300 - 0x2fd];
    float f300;                     // 0x300
    float f304;                     // 0x304
    u8    pad308[0x324 - 0x308];
    IObj* mp324;                    // 0x324
    u8    pad328[0x340 - 0x328];
    cCombatCarrier** mBeg340;       // 0x340
    cCombatCarrier** mEnd344;       // 0x344
    u8    pad348[0x354 - 0x348];
    cCombatCarrier** mBeg354;       // 0x354
    cCombatCarrier** mEnd358;       // 0x358
    u8    pad35c[0x508 - 0x35c];
    IObj  mObj508;                  // 0x508
    u8    pad50c[0x519 - 0x50c];
    u8    b519;                     // 0x519
    u8    pad51a[0x540 - 0x51a];
    int   i540;                     // 0x540
    u8    pad544[0x55c - 0x544];
    cElem55c* mBeg55c;              // 0x55c
    cElem55c* mEnd560;              // 0x560
    u8    pad564[0x62c - 0x564];
    cCity** mBeg62c;                // 0x62c
    cCity** mEnd630;                // 0x630
    u8    pad634[0x678 - 0x634];
    int   i678;                     // 0x678
    u8    pad67c[0x698 - 0x67c];
    u8    b698;                     // 0x698
    u8    pad699[0x6a0 - 0x699];
    cSPTimer mTimer6a0;             // 0x6a0
    u8    b6c0;                     // 0x6c0
    u8    pad6c1[0x6c8 - 0x6c1];
    cSPTimer mTimer6c8;             // 0x6c8

    // ---- slice functions (thiscall) ---------------------------------------------------
    // The 64-bit deadline at 0x290 is the (u294:u290) pair viewed as one qword.
    unsigned long long& Timer270End() { return *(unsigned long long*)&u290; }
    void  SetGameDataOwner2(void* owner);               // 0x00b18550 (modeled callee)
    void  SetField2f4(int v);                           // 0x00bd8140
    void  SetField2f8(int v);                           // 0x00bd8170
    void  GetContinent();                               // 0x00bd8210
    char  Timer230Active();                             // 0x00bd8240
    char  Timer250Active();                             // 0x00bd8280
    char  Timer270Under();                              // 0x00bd82c0
    void  AddTimer270(int ms);                          // 0x00bd8300
    void  SetVisitEffectActive(char flag, float v);     // 0x00bd8380
    char  InVisitEffectWindow();                        // 0x00bd8630
    IObj* PickSlot();                                   // 0x00bd8660
    void* NearestCombatant(IObj* carrier);              // 0x00bd8d70
    float* DirToThing(Float3* out, Float3* target);     // 0x00bd8750 (free-ish)
    int   CountTypeId();                                // 0x00bd8960
    int   NumBig();                                     // 0x00bd89c0
    int   NumBig2();                                    // 0x00bd8a00
    int   ThreeWay();                                   // 0x00bd8aa0
    int   ThreeWayB();                                  // 0x00bd8b10
    int   WealthAmount();                               // 0x00bd8b80
    void  TickThings();                                 // 0x00bd8bd0
    void  GetAmount(float* out, int* n);                // 0x00bd85c0
    char  AnyTwo();                                     // 0x00bd8f30
    char  AnyThree();                                   // 0x00bd8f60
    void  RemoveCiv(unsigned a, unsigned b);            // 0x00bd8fe0
    void  TriggerSomething(IObj* other);                // 0x00bd9060
    void  EmitEffectIds(IObj* other);                   // 0x00bd9140
};
// ---- items of slice s00bd8140 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32   g_168d248;         // 0x0168d248
extern u32   g_169c088;         // 0x0169c088
extern u32   g_1654c05;         // 0x01654c05  (GetCurrentGameMode result)

// ---- items of slice s00bd91e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float   kFloatMax;                             // 0x0146847c
extern const float   kTenFold;                              // 0x01473c70
extern const float   kEmitScale;                            // 0x01468468
extern const float   kSqrtEpsilon;                          // 0x013ec4b8
extern const float   kGrowStep;                             // 0x013eeda0
extern const char    kDefaultCivilizationData;              // 0x0156e14c
struct Vector3 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
};
struct Vector4 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
    float w;                                                // +0x0c
};
struct Quaternion {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
    float w;                                                // +0x0c
};
struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};
template <class T>
struct cVec {
    T*       mpBegin;                                       // +0x00
    T*       mpEnd;                                         // +0x04
    T*       mpCapacity;                                    // +0x08
    void*    mpAllocator;                                   // +0x0c
    uint32_t mPad10;                                        // +0x10

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T&       operator[](uint32_t nIndex) const { return mpBegin[nIndex]; }
};
struct cCity_s00bd_91e0;
struct cAnimatingCreature;
struct cGameData {
    virtual void       AddRef();                            // +0x00
    virtual void       Release();                           // +0x04
    virtual void       v08();                               // +0x08
    virtual cGameData* Cast(uint32_t nType);                // +0x0c
};
struct cPlanetModel_s00bd_91e0 {
    int32_t  GetContinent(const Vector3* pPosition);        // 0x00b88590
    Quaternion* BuildSurfaceOrientation(Quaternion* pOut, const Vector3* pPosition);  // 0x00b7f190
    Quaternion* BuildSurfaceOrientation2(Quaternion* pOut, const Vector3* pDirection,
                                         const Vector3* pPosition);                   // 0x00b7f250
    Vector3* GetSurfacePosition(Vector3* pOut, const Vector3* pPosition);           // 0x00b81630
};
struct cGameTimeManager {
    void IncPauseGate(uint32_t nGate);                      // 0x00b32220
};
struct cGameNounManager_s00bd_91e0 {
    cGameData* CreateNoun(uint32_t nNounID);                // 0x00b20c60
    int32_t    GetAvatar();                                 // 0x00b1fdb0
    void*      GetPlayerCivilization();                     // 0x00b25fb0
    void*      GetCurrentTerrainSphere();                   // 0x00f67d90
};
struct cStarEmpire;
struct cStarManager {
    cStarEmpire* GetEmpireByID(int32_t nEmpireID);          // 0x00ba9370
    cGameData*   GetEmpireData(cStarEmpire* pEmpire);       // 0x00baf700
};
struct cTerraformingManager {
    bool HasEvent(void* pOwner);                            // 0x00bbe5c0
};
struct cCivilization {
    uint8_t CanUseSuperweapon(bool bValue);                 // 0x00bf8a00
    char    mPad000[0xc4];                                  // +0x000 .. +0xc3
    uint8_t mDataC4;                                        // +0xc4
};
struct cSlotObjectVtbl {
    void* mpSlots00[0x30];                                  // +0x00 .. +0xbf
    void (*pRelease)(void* pThis);                          // +0xc0
};
struct cSlotObject {
    cSlotObjectVtbl* mpVtbl;                                // +0x00
};
struct cModeHelper;
cModeHelper* __cdecl GetLiveSimulator();                    // 0x00b3d240
struct cLayoutSlot {
    cGameData* GetObject();                                 // 0x00fcc210
    void       Reserve(cGameData* pObject);                 // 0x00afa030

    bool       mbIsOccupied;                                // +0x00
    uint32_t   mPad04;                                      // +0x04
    cGameData* mpObject;                                    // +0x08
    Vector3    mPosition;                                   // +0x0c
};
struct cCommunityLayout {
    cLayoutSlot* SlotAt(uint32_t nIndex);                   // 0x00af9ff0
    cLayoutSlot* FindSlotAt(const Vector3* pPosition);      // 0x00afad70
    void         SetAtCenter(const Vector3* pCenter, float fRadius, const Vector3* pFacing); // 0x00af9cf0
    void         EmitCopy(void* pOwner, float fScale);      // 0x00afec00

    Vector3           mDirection;                           // +0x00
    float             mField0C;                             // +0x0c
    float             mField10;                             // +0x10
    Vector3           mOrigin;                              // +0x14
    float             mField20;                             // +0x20
    int32_t           mField24;                             // +0x24
    bool              mbField28;                            // +0x28
    Quaternion        mOrientation;                         // +0x2c
    cVec<int32_t>     mField3C;                             // +0x3c
    cVec<cLayoutSlot> mSlots;                               // +0x50 .. +0x63
};
struct cSpatialObject {
    virtual void     v00();                                 // +0x00
    virtual void     v04();                                 // +0x04
    virtual void     v08();                                 // +0x08
    virtual void     v0c();                                 // +0x0c
    virtual void     v10();                                 // +0x10
    virtual void     v14();                                 // +0x14
    virtual void     v18();                                 // +0x18
    virtual void     v1c();                                 // +0x1c
    virtual void     v20();                                 // +0x20
    virtual void     v24();                                 // +0x24
    virtual void     v28();                                 // +0x28
    virtual Vector3*    GetPosition(const Vector4* pParams);   // +0x2c
    virtual Quaternion* GetOrientation();                   // +0x30
    virtual void        v34();                              // +0x34
    virtual void     SetPosition(const Vector3* pValue);    // +0x38
    virtual void     SetOrientation(const Quaternion* pValue);   // +0x3c
    virtual void     v40();                                 // +0x40
    virtual void     v44();                                 // +0x44
    virtual void     v48();                                 // +0x48
    virtual void     v4c();                                 // +0x4c
    virtual void     v50();                                 // +0x50
    virtual void     v54();                                 // +0x54
    virtual void*    GetPlanetPosition(void* pOut);         // +0x58
    virtual void*    v5c(void* pOut, float fAltitude);      // +0x5c

    int32_t GetObjectCount();                               // 0x008e7f80
};
struct cHallObject {
    virtual void     v00(void* pArg);                       // +0x00
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
    virtual void     v28();
    virtual Vector3*    GetPosition();                      // +0x2c
    virtual Quaternion* GetOrientation();                   // +0x30
    virtual void        v34();                              // +0x34
    virtual void        SetPosition(const Vector3* pValue); // +0x38
    virtual void        SetOrientation(const Quaternion* pValue);   // +0x3c
};
struct cWallsVtbl {
    void*    mpSlots00[0x1b];                               // +0x00 .. +0x6b
    int32_t (*pGetState)(void* pThis);                      // +0x6c
};
struct cCityWalls {
    cWallsVtbl* mpVtbl;                                     // +0x000
    char        mPad004[0x258];                             // +0x004 .. +0x25b
    float       mRadius;                                    // +0x25c

    int32_t     GetState();                                 // vtable slot +0x6c
    void        GetCenter(Vector3* pOut);                   // 0x00bec190
    bool        ContainsPoint(const Vector3* pPoint);       // 0x00bec0f0
    Vector3*    RequestPosition(Vector3* pOut, int32_t nWhich);   // 0x00bec2d0
};
struct cCityObjectVtbl {
    void*    mpSlots00[0x23];                               // +0x00 .. +0x8b
    Vector3* (__fastcall* pGetPosition)(void* pThis);       // +0x8c
};
struct cCityObject {
    cCityObjectVtbl* mpVtbl;                                // +0x000
    char           mPad004[0x30];                           // +0x004 .. +0x033
    cHallObject    mObject34;                               // +0x034
    char           mPad038[0xe8];                           // +0x038 .. +0x11f
    cSpatialObject mSpatial120;                             // +0x120
    char           mPad124[0x165];                          // +0x124 .. +0x288
    uint8_t        mbFlag289;                               // +0x289
};
struct cTurret {
    char           mPad000[0x34];                           // +0x000 .. +0x033
    cHallObject    mObject34;                               // +0x034
    char           mPad038[0x550];                          // +0x038 .. +0x587
    cSpatialObject mSpatial588;                             // +0x588
};
struct cActionTarget {
    char    mPad000[0xc4];                                  // +0x000 .. +0xc3
    Vector3 mPosition;                                      // +0xc4
};
struct cGonzagoTimer {
    virtual ~cGonzagoTimer();                               // +0x00

    void Reset();                                           // 0x00bc3170
    void Stop();                                            // 0x00bc3110

    uint32_t mRefCount;                                     // +0x04
    uint32_t mElapsedTime[2];                               // +0x08
    uint32_t mField10[2];                                   // +0x10
    uint8_t  mbRunning;                                     // +0x18
    uint32_t mpTimeFunction;                                // +0x1c
};
struct cCulturalTarget {
    void*   mpVtbl;                                         // +0x000
    char    mPad004[0x1d4];                                 // +0x004 .. +0x1d7
    int32_t mState;                                         // +0x1d8
};
struct tCultureTargetInfo {
    int32_t mBucketMaxPopulation[2];                        // +0x00
    int32_t mBucketPopulation[2];                           // +0x08
    int32_t mBucketEmigration[2];                           // +0x10
    int32_t mBucketImmigration[2];                          // +0x18
    bool    mbClearEverything;                              // +0x20
    char    mPad21[3];                                      // +0x21
    float   mAngryCrowdFraction;                            // +0x24
    float   mDancingCrowdFraction;                          // +0x28
    float   mIndifferentCrowdFraction;                      // +0x2c
    cGonzagoTimer mConvertCheckTimer;                       // +0x30
    cGonzagoTimer mConvertedTimer;                          // +0x50
    cSlotObject* mpAttackTarget;                            // +0x70
    bool    mbAttackTargetChanged;                          // +0x74
    char    mPad75[3];                                      // +0x75
    void*   mpCultureObject;                                // +0x78
    char    mPad7c[4];                                      // +0x7c
};
struct cCityPartner {
    void*   mpInterCityRoad;                                // +0x00 (first dword is the empire id)
    void*   mpPartnerCity;                                  // +0x04
    int32_t mField08;                                       // +0x08
};
struct cCreatureDisplay {
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual void v18();                                     // +0x18
    virtual void v1c();                                     // +0x1c
    virtual void v20();                                     // +0x20
    virtual void v24();                                     // +0x24
    virtual void v28();                                     // +0x28
    virtual void v2c();                                     // +0x2c
    virtual void v30();                                     // +0x30
    virtual void v34();                                     // +0x34
    virtual void v38();                                     // +0x38
    virtual void SetCreature(cAnimatingCreature* pCreature);   // +0x3c
};
struct cModeHelper {
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual void v18();                                     // +0x18
    virtual void v1c();                                     // +0x1c
    virtual void v20();                                     // +0x20
    virtual void v24();                                     // +0x24
    virtual void v28();                                     // +0x28
    virtual void v2c();                                     // +0x2c
    virtual void v30();                                     // +0x30
    virtual void v34();                                     // +0x34
    virtual void v38();                                     // +0x38
    virtual void v3c();                                     // +0x3c
    virtual void v40();                                     // +0x40
    virtual void v44();                                     // +0x44
    virtual void v48();                                     // +0x48
    virtual void v4c();                                     // +0x4c
    virtual void v50();                                     // +0x50
    virtual void v54();                                     // +0x54
    virtual void v58();                                     // +0x58
    virtual void v5c();                                     // +0x5c
    virtual void v60();                                     // +0x60
    virtual void v64();                                     // +0x64
    virtual void v68();                                     // +0x68
    virtual void v6c();                                     // +0x6c
    virtual void v70();                                     // +0x70
    virtual cCreatureDisplay* GetDisplay();                  // +0x74
};
struct cAnimatingCreature {
    void Release();                                         // 0x00a05270
};
struct cSectionObject {
    void OnCityChanged(cCity_s00bd_91e0* pCity, int32_t nValue);       // 0x00ff2810
};
struct cGameModeSection {
    char    mPad000[0x13c];                                 // +0x000 .. +0x13b
    int32_t mField13C;                                      // +0x13c
};
struct cProtectorSource {
    cGameNounManager_s00bd_91e0* GetNounManager();                     // 0x00b8de30
    int32_t           GetCategory();                        // 0x00b8dab0
};
struct cCityVtbl {
    void*    mpSlots00[0x16];                               // +0x00 .. +0x57
    void*    (*pGetPlanetPosition)(void* pThis, void* pOut);   // +0x58
    void*    mpSlot5C;                                      // +0x5c
    void*    mpSlots60[3];                                  // +0x60 .. +0x6b
    int32_t  (__fastcall* pGetState)(void* pThis);           // +0x6c
};
struct cCity_s00bd_91e0 {
    cCityVtbl*     mpVtbl;                                  // +0x000
    char           mPad004[0x11c];                          // +0x004 .. +0x11f
    cSpatialObject mSpatial;                                // +0x120
    char           mPad124[0xe0];                           // +0x124 .. +0x203
    cCityWalls*    mpLayoutWalls;                           // +0x204
    char           mPad208[0x6c];                           // +0x208 .. +0x273
    uint8_t        mFlagTable[0x28];                        // +0x274 .. +0x29b (overlaps a timer at +0x270)
    int32_t        mContextState;                           // +0x29c
    char           mPad2a0[0x50];                           // +0x2a0 .. +0x2ef
    cSectionObject* mpSection2F0;                           // +0x2f0
    char           mPad2f4[0x2c];                           // +0x2f4 .. +0x31f
    cCityObject*   mpCityHall;                              // +0x320
    cCityWalls*    mpCityWalls;                             // +0x324
    void*          mpCityTerritory;                         // +0x328
    Vector3        mCityPosition;                           // +0x32c
    char           mPad338[8];                              // +0x338 .. +0x33f
    cVec<cCityObject*> mBuildings;                          // +0x340
    cVec<cTurret*> mTurrets;                                // +0x354 (fixed_vector: 32 entries)
    char           mPad368[0x84];                           // +0x368 .. +0x3eb
    cCommunityLayout mBuildingsLayout;                      // +0x3ec
    cCommunityLayout mDecorationsLayout;                    // +0x450
    cCommunityLayout mTurretsLayout;                        // +0x4b4
    bool           mbSmallCity;                             // +0x518
    bool           mbField519;                              // +0x519
    char           mPad51a[2];                              // +0x51a
    Vector3        mPendingPosition;                        // +0x51c
    char           mPad528[0x18];                           // +0x528 .. +0x53f
    int32_t        mVehicleSpecialty;                       // +0x540
    char           mPad544[0x18];                           // +0x544 .. +0x55b
    cVec<cCityPartner> mTradePartners;                      // +0x55c
    char           mPad570[0x20];                           // +0x570 .. +0x58f
    cCivilization* mpCivilization;                          // +0x590
    char           mPad594[0x84];                           // +0x594 .. +0x617
    cVec<tCultureTargetInfo> mCultureTargetInfo;            // +0x618
    cVec<cCulturalTarget*> mCulturalTargets;                // +0x62c
    char           mPad640[0xc];                            // +0x640 .. +0x64b
    int32_t        mRoboPopulation;                         // +0x64c
    char           mPad650[0x114];                          // +0x650 .. +0x763
    cAnimatingCreature* mpCreature;                         // +0x764
    cGameData*     mpObject768;                             // +0x768
    char           mPad76c[4];                              // +0x76c
    cGonzagoTimer  mMessiahTimer;                           // +0x770
    char           mPad790[0x80];                           // +0x790 .. +0x80f
    cGameData*     mpTarget810;                             // +0x810
    char           mPad814[4];                              // +0x814 .. +0x817 (8-byte class alignment tail)

    // --- methods of this slice ---
    void ShowTransitionWarning();                           // 0x00bd91e0
    bool HasTradePartner(uint32_t nEmpireID);               // 0x00bd9260
    cCity_s00bd_91e0* FindNearestCity(int32_t nReason);                // 0x00bd92d0
    void PrintBuildingCount(float fValue);                  // 0x00bd9440
    float GetCityRadius();                                  // 0x00bd9470
    Vector3* GetWallsCenter(Vector3* pOut);                 // 0x00bd9480
    void UpdateTurretLayout(void* pOwner);                  // 0x00bd94a0
    void SetField51C(const cVec<Vector3>* pPositions);      // 0x00bd9620
    bool SetDecoration(cCityObject* pObject);               // 0x00bd9660
    void UpdateCityPosition();                              // 0x00bd9710
    cLayoutSlot* FindFarthestTurretSlot();                  // 0x00bd98c0
    void* GetCivilizationData();                            // 0x00bd99e0
    void DoCityAction(cActionTarget* pTarget);              // 0x00bd9a00
    int32_t GetTurretSlotCount();                           // 0x00bd8b10 (helper used by 00bd98c0)
    int32_t CountEmptyTurrets();                            // 0x00bd9b70
    int32_t CountEmptyBuildings();                          // 0x00bd9bb0
    bool  ContainsPoint(const Vector3* pPoint);             // 0x00bd9c00
    bool  IsWithinRadius(const Vector3& rPoint, float fExtra);   // 0x00bd9c30
    Vector3* GetCenter(Vector3* pOut);                      // 0x00bd9ca0
    void* GetPlayerTerrainSphere();                         // 0x00bd9cf0
    bool  HasOnlyCityHall();                                // 0x00bd9d20
    void  ClearCreature();                                  // 0x00bd9dd0
    void  NotifySectionObject();                            // 0x00bd9e50
    tCultureTargetInfo* GetCultureTarget(int32_t nIndex);   // 0x00bd9e80
    void  SetCultureTargetBuckets(int32_t nIndex, int32_t nFirst, int32_t nSecond);   // 0x00bd9ea0
    void  ResetCultureTarget(int32_t nIndex);               // 0x00bd9ed0
    int32_t IsCultureActive();                              // 0x00bd9fa0
    bool  IsFestivalActive();                               // 0x00bd8f60 (helper used by 00bd9fa0)
    bool  HasCultureEvent(bool bValue);                     // 0x00c004c0 (helper used by 00bd9fa0)
    bool  HasLayoutFlag(int32_t nOffset);                   // 0x00bda000
    bool  CanUseSuperweapon(bool bValue);                   // 0x00bda080
    void  ClearCultureState();                              // 0x00bda0a0
    void  SetTarget810(cGameData* pNew);                    // 0x00bda120

    // --- helpers (no markers) ---
    int32_t GetBuildingCount() const { return (int32_t)(mBuildings.mpEnd - mBuildings.mpBegin); }

    void ReleaseCreature()
    {
        if (!mpCreature)
            return;
        cModeHelper* pSimulator = GetLiveSimulator();
        cCreatureDisplay* pDisplay = pSimulator->GetDisplay();
        pDisplay->SetCreature(mpCreature);
        cAnimatingCreature* pOld = mpCreature;
        mpCreature = 0;
        if (pOld)
            pOld->Release();
    }
};
namespace UI {
    void __cdecl CalloutMessageBox(const ResourceKey* pTable, const ResourceKey* pMessage);   // 0x00809db0
}
cGameTimeManager*     __cdecl GameTimeManager();            // 0x00b3d380
cGameNounManager_s00bd_91e0*     __cdecl NounManager();                // 0x00b3d300
cStarManager*         __cdecl StarManager();                // 0x00b3d2a0
cPlanetModel_s00bd_91e0*         __cdecl PlanetModel();                // 0x00b3d350
cTerraformingManager* __cdecl TerraformingManager();        // 0x00b3d430
cVec<cCity_s00bd_91e0*>*         __fastcall GetCityList(int32_t nReason);   // 0x00bef6c0
int32_t               __cdecl GetPlayerEmpireID();          // 0x01021090
cGameModeSection*     __cdecl GetGameModeSection();         // 0x01021260
bool                  __cdecl IsOnTerraformedGround(int32_t nMode, const Vector3* pPosition);   // 0x00c9e8e0
bool                  __cdecl HasTerraformEvent(void* pOwner);   // 0x00c6fe50
void                  __cdecl GetPropertyFloat(void* pObject, uint32_t nProperty, float* pOut); // 0x0040cf10
extern const Vector3 kDefaultCityPosition;                  // 0x0168bd70
extern const ResourceKey kTransitionWarningTable;           // 0x0156e29c
extern const ResourceKey kTransitionWarningEcoHostile;      // 0x0156e254
extern const ResourceKey kTransitionWarningEco;             // 0x0156e260
extern const ResourceKey kTransitionWarningTrader;          // 0x0156e26c
extern const ResourceKey kTransitionWarningTraderHostile;   // 0x0156e278
extern const ResourceKey kTransitionWarningMilitaryHostile; // 0x0156e284
extern const ResourceKey kTransitionWarningMilitary;        // 0x0156e290
// ---- items of slice s00bd91e0 end

// ---- items of slice s00bdb3b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_16dc798;                                // 0x016dc798 gSimUniverse
extern float g_168bd70;                                // 0x0168bd70
extern float g_168bd74;                                // 0x0168bd74
extern float g_168bd78;                                // 0x0168bd78
extern float g_1485720;                                // 0x01485720 1.0f
extern float g_1468468;                                // 0x01468468 4.0f
extern float g_13ef580;                                // 0x013ef580 0.02f
extern float g_146869c[4];                             // 0x0146869c
extern float g_168c330;                                // 0x0168c330 matrix source
extern float g_168c354;                                // 0x0168c354
extern float g_168c358;                                // 0x0168c358
extern float g_168c35c;                                // 0x0168c35c
extern void* g_168bda0;                                // 0x0168bda0
extern void* g_156e16c;                                // 0x0156e16c resource key
typedef unsigned short u16;
typedef unsigned long long u64;
void* __cdecl SP_NounManager();                        // 0x00b3d300
void* __stdcall SP_PlanetModel(int model);             // 0x00b3d350 ret 4
void* __stdcall SP_PlanetModel1(float* pos);           // 0x00b3d350 (pos alias)
void* __cdecl SP_PropertyManager();                    // 0x0067de30
void* __cdecl SP_EffectsManager();                     // 0x0067ddd0
void* __stdcall SP_GetMissionManager(void* a);         // 0x00feb9f0 ret 4
void* __cdecl SP_GetCurrentGameMode();                 // 0x00b5b800
void* __stdcall SP_SpaceGameGet(int a);                // 0x01002bd0 ret 4
void* __cdecl SP_GetSpaceCombatTuning();               // 0x01029940
void* __cdecl FUN_00ff2810(void* a, void* b);          // 0x00ff2810 ret 8
void  __stdcall FUN_00bed3c0(void* out);               // 0x00bed3c0 ret 4
void* __cdecl FUN_00bda200(void* out, int a, int b);   // 0x00bda200 ret 0xc
void  __cdecl XformMsg_ctor(void* p);                  // 0x00434040 ret 0
int* __cdecl SP_Matrix3FromQuaternion(void* out, void* q); // 0x0059c190 ret 8
void  __cdecl operator_delete(void* p);                // 0x00f47380 ret 4
u8    __stdcall FUN_00bec190(void* out);               // 0x00bec190 ret 4
int   __cdecl FUN_00bd8b80(void* self);                // 0x00bd8b80 ret 0
u8    __cdecl FUN_00bd7e20(void* self);                // 0x00bd7e20 ret 0
u8    __cdecl FUN_00bda000(void* self, int a);         // 0x00bda000 ret 4
void  __cdecl FUN_00a04c80(void* self, int a);         // 0x00a04c80 ret 4
void  __cdecl FUN_00a047d0(void* self, int a);         // 0x00a047d0 ret 4
struct MissionMgrStub {
    u8 DoMissionsPreventHostility(void* b);            // 0x00fedea0 ret 4
};
struct XformMsg {
    XformMsg();
    char m[0x24];
};
struct SimGameStub {
    void* f5180();                                     // 0x01005180 ret 0
};
struct NounMgrStub {
    void* FUN_00b25f40(int id);                        // 0x00b25f40 ret 4
    void* FUN_00b25ca0();                              // 0x00b25ca0 GetCivilizationList ret 0
    void* FUN_00b25fb0();                              // 0x00b25fb0 GetPlayerCivilization ret 0
};
struct ActivePlanetStub {
    void* FUN_00c71e30();                              // 0x00c71e30 ret 0
    char pad04[0x13c - 0x04];
    int   m13c;                                        // +0x13c
};
struct DamageStub {
    int FUN_008e7f80();                                // 0x008e7f80 GetDamageState ret 0
};
struct ActionCircleStub {
    void* FUN_00af9ff0(u32 slot);                      // 0x00af9ff0 SlotAt ret 4
    char bytes[0x28];                                  // real cActionCircle extent
};
struct SlotObjStub {
    void* FUN_00fcc210();                              // 0x00fcc210 ret 0
};
struct PropObjStub {
    void** vt;                                         // +0x00 (+0x04, +0x0c, +0x18, +0x24, +0x2c, +0x30)
};
struct ToolMgrStub {
    void UseToolStart(void* slot, float* pos, int a, int b, int c, int d);
};
void* __cdecl SP_RelationshipManager();                // 0x00b3d2c0
struct CivStub {
    int* FUN_00bf9770(int key);                        // 0x00bf9770 GetModelTypeKey ret 4
    void FUN_00bf9780(int key);                        // 0x00bf9780 ret 4
    void FUN_00bef830();                               // 0x00bef830 ret 0
    int  FUN_00bef950();                               // 0x00bef950 ret 0
    void* FUN_00bf1780(int a);                         // 0x00bf1780 ret 4
    void** vt;                                         // +0x00
    char pad04[0x298 - 0x04];
    int  m298;                                         // +0x298
};
struct TimerStub {
    void FUN_00bc3110();                               // 0x00bc3110 Stop
    void FUN_00bc3130();                               // 0x00bc3130 Restart
    u64  FUN_00bc3190();                               // 0x00bc3190 GetElapsedTime
};
struct PlanetObjStub {
    void* FUN_00b81630();                              // 0x00b81630 ret 0
    float FUN_00b83620();                              // 0x00b83620 ret 0
};
struct Tuning2Stub {
    float FUN_01029b90();                              // 0x01029b90 GetCityAngerTime ret 0
};
struct SimUniverseStub {
    void FUN_01014a80(int a, int b);                   // 0x01014a80 AdjustAwareness ret 8
};
struct RefObj3 {
    void AddRef();                                     // 0x00a02c30 (cAnimatingCreature)
    void Release();                                    // 0x00a05270
};
struct CStub {
    void** vt;                                         // +0x00
    char pad04[0x70 - 0x04];
    u8*  m70;                                          // +0x70 point-vector begin
    u8*  m74;                                          // +0x74 point-vector end
    char pad78[0x120 - 0x78];
    void* m120;                                        // +0x120 transform sub-object
    char pad124[0x220 - 0x124];
    float m220;                                        // +0x220 anger timer
    char pad224[0x274 - 0x224];
    u8   m274[0x14];                                   // +0x274 byte grid
    char pad288[0x2f0 - 0x288];
    void* m2f0;                                        // +0x2f0
    char pad2f4[0x304 - 0x2f4];
    float m304;                                        // +0x304
    char pad308[0x320 - 0x308];
    void* m320;                                        // +0x320
    void* m324;                                        // +0x324 zone
    char pad328[0x32c - 0x328];
    float m32c;                                        // +0x32c
    float m330;                                        // +0x330
    float m334;                                        // +0x334
    char pad338[0x340 - 0x338];
    int* m340;                                         // +0x340 map begin
    int* m344;                                         // +0x344 map end
    char pad348[0x354 - 0x348];
    int* m354;                                         // +0x354 vector begin
    int* m358;                                         // +0x358 vector end
    char pad35c[0x3ec - 0x35c];
    ActionCircleStub m3ec;                             // +0x3ec civic-object layout
    char pad414[0x508 - 0x414];    void* m508;                                        // +0x508
    char pad50c[0x53c - 0x50c];
    float m53c;                                        // +0x53c
    int   m540;                                        // +0x540
    char pad544[0x590 - 0x544];
    CivStub* m590;                                     // +0x590 civilization
    char pad594[0x640 - 0x594];
    int   m640;                                        // +0x640
    int   m644;                                        // +0x644
    u8    m648;                                        // +0x648
    char pad649[0x764 - 0x649];
    void* m764;                                        // +0x764 cAnimatingCreature
    char pad768[0x790 - 0x768];
    TimerStub m790;                                    // +0x790 cSPTimer
    int   m7b0;                                        // +0x7b0 effect id
    int   m7b4;                                        // +0x7b4 effect id

    void  FUN_00bdb3b0(int a, int b);                  // 0x00bdb3b0 ret 8
    u8    FUN_00bdb470(int key);                       // 0x00bdb470 ret 4
    int   FUN_00bdb590(int* key, int* out);            // 0x00bdb590 ret 8
    void  FUN_00bdb7f0(int obj, int kind);             // 0x00bdb7f0 ret 8
    u8    FUN_00bdb880(int spec);                      // 0x00bdb880 ret 4
    u8    FUN_00bdb930(int spec, int arg);             // 0x00bdb930 ret 8
    float FUN_00bdb960();                              // 0x00bdb960
    float FUN_00bdba80();                              // 0x00bdba80
    void  FUN_00bdbaa0();                              // 0x00bdbaa0
    void  FUN_00bdbbb0();                              // 0x00bdbbb0
    void  FUN_00bdbc20(int* flag);                     // 0x00bdbc20 ret 4
    void  FUN_00bdbe50();                              // 0x00bdbe50
    void  FUN_00bdbf10();                              // 0x00bdbf10
    void  FUN_00bdc050();                              // 0x00bdc050
    void  FUN_00bdc1a0(int kind, int param);           // 0x00bdc1a0 ret 8
    void  FUN_00bd9dd0();                              // 0x00bd9dd0 ret 0 (callee, ecx=this)
};
extern void* g_1654c05_s00bd_b3b0;                                // 0x01654c05 game-mode token
struct RelMgrStub {
    void FUN_00d06240(int a, int b, int c);            // 0x00d06240 RecordEvent ret 0xc
};
static inline char* vpt(void* o) { return *(char**)o; }
struct Matrix33Ctor {
    void FUN_0041cb40(void* src);                      // 0x0041cb40 ret 4
};
static inline void  timerRestart(void* p) { ((TimerStub*)p)->FUN_00bc3130(); }
static inline void  timerStop(void* p)    { ((TimerStub*)p)->FUN_00bc3110(); }
static inline void* nounMgr()             { return SP_NounManager(); }
// ---- items of slice s00bdb3b0 end

// ---- items of slice s00bdd380 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier(void);
extern "C" void FUN_00f47380(void *);
extern "C" void FUN_00ae6970();
extern "C" void FUN_00ad92d0();
extern "C" void FUN_00bdc770();
extern "C" void FUN_00b184c0();
extern "C" void FUN_00bdca30();
extern "C" void FUN_00bf57b0();
extern "C" void FUN_00b7f250();
extern "C" void FUN_00c88530();
extern "C" void FUN_009a9600();
extern "C" void FUN_00bda710();
extern "C" void FUN_00a05270();
extern "C" void FUN_00ac0520();
extern "C" void FUN_00c8a420();
extern "C" void FUN_00afbad0();
#pragma intrinsic(_ReadWriteBarrier)
struct CRefCounted {
    void **m_vtbl;                     // +0x00
    void AddRef()  { ((void (__thiscall *)(CRefCounted *))m_vtbl[0xbc / 4])(this); }
    void Release() { ((void (__thiscall *)(CRefCounted *))m_vtbl[0xc0 / 4])(this); }
};
struct CElementSub {
    void *m_vtbl;                      // +0x00
    u32   m_u04;                       // +0x04
    u32   m_u08;                       // +0x08
    u32   m_u0c;                       // +0x0c
    u32   m_u10;                       // +0x10
    u32   m_u14;                       // +0x14
    u8    m_u18;                       // +0x18
    u8    m_pad19[3];                  // +0x19
    u32   m_u1c;                       // +0x1c
};
struct CElement {
    u32 m_u00;                         // +0x00
    u32 m_u04;                         // +0x04
    u32 m_u08;                         // +0x08
    u32 m_u0c;                         // +0x0c
    u32 m_u10;                         // +0x10
    u32 m_u14;                         // +0x14
    u32 m_u18;                         // +0x18
    u32 m_u1c;                         // +0x1c
    u8  m_u20;                         // +0x20
    u8  m_pad21[3];                    // +0x21
    float m_f24;                       // +0x24
    float m_f28;                       // +0x28
    float m_f2c;                       // +0x2c
    CElementSub m_a;                   // +0x30
    CElementSub m_b;                   // +0x50
    CRefCounted *m_p70;                // +0x70
    u8  m_u74;                         // +0x74
    u8  m_pad75[3];                    // +0x75
    CRefCounted *m_p78;                // +0x78
    u8  m_pad7c[4];                    // +0x7c

    __declspec(noinline) CElement *CopyConstructFrom(const CElement &src);   // 0x00bdd380
    __declspec(noinline) CElement *CopyAssignFrom(const CElement &src);      // 0x00bdd470
};
#define VTBL_SUB_BASE ((void *)g_1465d54)
#define VTBL_SUB_DERIVED ((void *)g_1464450)
static __forceinline void CopySub(CElementSub &d, const CElementSub &s)
{
    d.m_vtbl = VTBL_SUB_BASE;
    d.m_u04 = 0;
    d.m_u08 = s.m_u08;
    d.m_u0c = s.m_u0c;
    d.m_u10 = s.m_u10;
    d.m_u14 = s.m_u14;
    d.m_u18 = s.m_u18;
    d.m_u1c = s.m_u1c;
    d.m_vtbl = VTBL_SUB_DERIVED;
}
struct CVtblObj {
    void **m_vtbl;                     // +0x00
    void Slot1() { ((void (__thiscall *)(CVtblObj *))m_vtbl[1])(this); }
    int Call70(void *out) {
        return ((int (__thiscall *)(CVtblObj *, void *))m_vtbl[0x70 / 4])(this, out);
    }
};
struct CVec3 {
    float x, y, z;
};
struct CGonzagoTimer {
    u8 m_pad[0x20];
};
struct CEastlVec12 {
    void *m_begin;                     // +0x00
    void *m_end;                       // +0x04
    void *m_cap;                       // +0x08
};
struct CVector4 {
    void *m_begin;                     // +0x00
    void *m_end;                       // +0x04
    void *m_cap;                       // +0x08
};
typedef CEastlVec12 CVector12;
struct CGameDataBase {
    void *m_vtbl0;                     // +0x00
    void *m_vtbl4;                     // +0x04
    u8 m_pad08[0x2c];                  // +0x08
    void *m_vtbl34;                    // +0x34
    u8 m_pad38[4];                     // +0x38
};
struct CDerivedGameData : CGameDataBase {
    void *m_p3c;                       // +0x3c
    u8 m_pad40[0x18];                  // +0x40
    void *m_p58;                       // +0x58
    u8 m_pad5c[0x14];                  // +0x5c
    void *m_p70;                       // +0x70
    u8 m_pad74[0x10];                  // +0x74
    CEastlVec12 m_vec84;               // +0x84
    u8 m_pad90[0x20];                  // +0x90
    CGonzagoTimer m_timerB0;           // +0xb0
    CEastlVec12 m_vecD0;               // +0xd0
    u8 m_padDC[8];                     // +0xdc
    CEastlVec12 m_vecE4;               // +0xe4
    u8 m_padF0[8];                     // +0xf0
    u8 *m_arrF8;                       // +0xf8
    u8 m_padFC[4];                     // +0xfc
    u8 *m_arrF8End;                    // +0x100
    u8 m_pad104[4];                    // +0x104
    u8 *m_arr108;                      // +0x108
    u8 m_pad10C[4];                    // +0x10c
    u8 *m_arr108End;                   // +0x110
    u8 m_pad114[8];                    // +0x114
    CVtblObj *m_p11c;                  // +0x11c
};
extern "C" void FUN_00b638b0_s00bd_d380();
struct CRBTree {
    u8 m_header[0x0c];
    void *m_root;                      // +0x0c
};
struct CSpatialBlock {
    void *m_vtbl;                      // +0x00
    u8 m_pad04[0xd0];                  // +0x04
};
struct CPaintBlock {
    void *m_vtbl;                      // +0x00
    u8 m_pad04[0x14];                  // +0x04
    void *m_vtbl18;                    // +0x18
};
struct CCity : CDerivedGameData {
    CSpatialBlock m_spatial120;        // +0x120
    CPaintBlock m_paint1f4;            // +0x1f4
    u8 *m_arr210;                      // +0x210
    u8 m_pad214[4];                    // +0x214
    u8 *m_arr218;                      // +0x218
    u8 m_pad21c[0x14];                 // +0x21c
    CGonzagoTimer m_t230;              // +0x230
    CGonzagoTimer m_t250;              // +0x250
    CGonzagoTimer m_t270;              // +0x270
    u8 m_pad290[8];                    // +0x290
    CVtblObj *m_p298;                  // +0x298
    u8 m_pad29c[8];                    // +0x29c
    void *m_p2a4;                      // +0x2a4
    u8 m_pad2a8[0x10];                 // +0x2a8
    void *m_p2b8;                      // +0x2b8
    u8 m_pad2bc[0x4c];                 // +0x2bc
    CVector4 m_vec308;                 // +0x308
    u8 m_pad314[0xc];                  // +0x314
    CVtblObj *m_p320;                  // +0x320
    CVtblObj *m_p324;                  // +0x324
    CVtblObj *m_p328;                  // +0x328
    u8 m_pad32c[0x14];                 // +0x32c
    CVector4 m_vec340;                 // +0x340
    u8 m_pad34c[8];                    // +0x34c
    CVector4 m_vec354;                 // +0x354
    void *m_p360;                      // +0x360
    void *m_p364;                      // +0x364
    u8 m_pad368[0x84];                 // +0x368
    u8 m_action3ec[0x64];              // +0x3ec
    u8 m_action450[0x64];              // +0x450
    u8 m_action4b4[0x64];              // +0x4b4
    u8 m_pad518[0x10];                 // +0x518
    void *m_p528;                      // +0x528
    u8 m_pad52c[0x1c];                 // +0x52c
    CVector4 m_vec548;                 // +0x548
    u8 m_pad554[8];                    // +0x554
    CVector12 m_vec55c;                // +0x55c
    u8 m_pad568[8];                    // +0x568
    CRBTree m_tree570;                 // +0x570
    u8 m_pad580[0x10];                 // +0x580
    CVtblObj *m_p590;                  // +0x590
    u8 m_pad594[0xc];                  // +0x594
    CRBTree m_tree5a0;                 // +0x5a0
    u8 m_pad5b0[0xc];                  // +0x5b0
    CRBTree m_tree5bc;                 // +0x5bc
    u8 m_pad5cc[0xc];                  // +0x5cc
    CRBTree m_tree5d8;                 // +0x5d8
    u8 m_pad5e8[0x10];                 // +0x5e8
    CGonzagoTimer m_t5f8;              // +0x5f8
    CVector4 m_vec618;                 // +0x618
    u8 m_pad624[8];                    // +0x624
    CVector4 m_vec62c;                 // +0x62c
    u8 m_pad638[0x4c];                 // +0x638
    void *m_p684;                      // +0x684
    u8 m_pad688[0x18];                 // +0x688
    CGonzagoTimer m_t6a0;              // +0x6a0
    u8 m_pad6c0[8];                    // +0x6c0
    CGonzagoTimer m_t6c8;              // +0x6c8
    CGonzagoTimer m_t6e8;              // +0x6e8
    CGonzagoTimer m_t708;              // +0x708
    CGonzagoTimer m_t728;              // +0x728
    u8 m_pad748[0x1c];                 // +0x748
    void *m_p764;                      // +0x764
    CVtblObj *m_p768;                  // +0x768
    u8 m_pad76c[4];                    // +0x76c
    CGonzagoTimer m_t770;              // +0x770
    CGonzagoTimer m_t790;              // +0x790
    u8 m_pad7b0[8];                    // +0x7b0
    CRBTree m_tree7b8;                 // +0x7b8
    u8 m_pad7c8[0xc];                  // +0x7c8
    CVtblObj *m_p7d4;                  // +0x7d4
    u8 m_pad7d8[0x20];                 // +0x7d8
    void *m_p7f8;                      // +0x7f8
    u8 m_pad7fc[0x14];                 // +0x7fc
    CVtblObj *m_p810;                  // +0x810

    int FUN_00bddda0(int a1, int a2, int a3, int a4, int a5, int a6);
};
static __forceinline void FreeChecked(void *p)
{
    if (p != 0 && ((u32 *)p)[-1] != 0)
        FUN_00f47380(p);
}
static __forceinline void DestroyTree(CRBTree &t)
{
    void *node = t.m_root;
    while (node != 0) {
        ((void (__thiscall *)(CRBTree *, void *))FUN_009a9600)(&t, ((void **)node)[0]);
        void *next = ((void **)node)[1];
        FUN_00f47380(node);
        node = next;
    }
}
static __forceinline void DestroyObjVector4(CVector4 &v)
{
    for (void **p = (void **)v.m_begin; p < (void **)v.m_end; ++p) {
        CVtblObj *o = (CVtblObj *)*p;
        if (o != 0)
            o->Slot1();
    }
}
static __forceinline void DestroySlot64(CVector4 &v)
{
    for (void **p = (void **)v.m_begin; p < (void **)v.m_end; ++p) {
        CVtblObj *o = (CVtblObj *)*p;
        if (o != 0)
            ((void (__thiscall *)(CVtblObj *))o->m_vtbl[0x64 / 4])(o);
    }
}
static __forceinline void DestroyStride12(CVector12 &v)
{
    for (u8 *p = (u8 *)v.m_begin; p < (u8 *)v.m_end; p += 0xc) {
        CVtblObj *a = *(CVtblObj **)(p + 4);
        if (a != 0)
            a->Slot1();
        CVtblObj *b = *(CVtblObj **)p;
        if (b != 0)
            b->Slot1();
    }
}
// ---- items of slice s00bdd380 end

// ---- items of slice s00be30e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kZeroEpsilon;                            // 0x013ec4b8
extern const float kRepairFraction;                         // 0x01470f1c
extern const float kGrowFraction;                           // 0x01485544
extern const float kOne;                                    // 0x01485720
extern const float kNegOne;                                 // 0x013eb1bc
struct cVec3 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
};
struct cMat4 {
    float m[16];                                            // +0x00
};
struct cPtrList {
    void**           mpBegin;                               // +0x00
    void**           mpEnd;                                 // +0x04
    void**           mpCap;                                 // +0x08
};
struct cRefList {
    void**           mpBegin;                               // +0x00
    void**           mpEnd;                                 // +0x04
    void**           mpCap;                                 // +0x08
    void**  erase(void** pFirst, void** pLast);             // 0x00e25bd0
};
struct cUIntMap {
    uint8_t   mPad00[0xac];                                 // +0x00 .. +0xab
    uint32_t* operator[](const uint32_t& nKey);             // 0x00643a40
};
struct cSpatial {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
    virtual cVec3* GetPosition();                           // +0x2c
virtual void v030();
virtual void v034();
    virtual void SetPosition(const cVec3* pPosition);       // +0x38
    virtual void SetOrientation(const cMat4* pMatrix);      // +0x3c
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
    virtual void* v05c(void* pOut);                         // +0x5c
virtual void v060();
virtual void v064();
    virtual void* v068();                                   // +0x68
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
    virtual void SetKey(const ResourceKey* pKey);           // +0x94
};
struct cCombatant {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
    virtual cVec3* GetPosition();                           // +0x2c
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
    virtual float v058();                                   // +0x58 (health fraction)
    virtual void* v05c(void* pOut);                         // +0x5c

    int32_t GetDamageState();                               // 0x008e7f80
    void    PartialRepair(float fAmount);                   // 0x00bfd1a0
    bool    IsDeadOrDying();                                // 0x00bfc600
};
struct cIDSource {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
    virtual uint32_t v04c();                                // +0x4c
};
struct cNoun {
    virtual void v000();                                    // +0x00 (on destroy)
    virtual void v004();                                    // +0x04 (release)
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
    virtual uint32_t GetTypeID();                           // +0x38
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
    virtual void v094(const ResourceKey* pKey);             // +0x94
    uint8_t      mPad004[0x30];                             // +0x004 .. +0x033
    cSpatial     mSpatial;                                  // +0x34
    uint8_t      mPad058[0xe8];                             // +0x38 .. +0x11f
    cCombatant   mCombatant;                                // +0x120

    int32_t GetTimerA();                                    // 0x00bcc800
    int32_t GetTimerB();                                    // 0x00bcd250
    bool    IsSpecial();                                    // 0x00c3f540
};
struct cSlotMgr {
    uint8_t  mPad00[0x64];                                  // +0x00 .. +0x63

    void  RemoveAgent(void* pAgent);                        // 0x00afae50
    void* FindSlot(void* pKey);                             // 0x00afad70
    void* SlotAt(uint32_t nSlot);                           // 0x00af9ff0
};
struct cSPTimer_s00be_30e0 {
    uint8_t  mPad00[0x20];                                  // +0x00 .. +0x1f

    bool     IsRunning();                                   // 0x00feba90
    uint64_t GetElapsedTime();                              // 0x00bc3190
    void     Stop();                                        // 0x00bc3110
};
struct cPlanetModel_s00be_30e0 {
    cMat4* BuildSurfaceOrientation2();                      // 0x00b7f250
};
struct cGameNounManager_s00be_30e0 {
    uint8_t mPad00[0x04];                                   // +0x00
    void RemoveNoun();                                      // 0x00b225d0
};
struct cEffectEmitter {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
    virtual void v060(uint32_t nEffect, const void* pA, const void* pB);   // +0x60
};
void* __cdecl FUN_00bd98c0();                               // 0x00bd98c0
void* __cdecl FUN_00be1fb0();                               // 0x00be1fb0
void  __cdecl FUN_00be2440(void* pThis, int32_t nA, int32_t nB);   // 0x00be2440
void  __cdecl FUN_00be2b10(const char* pKey, cPtrList* pOut);      // 0x00be2b10
void  __cdecl FUN_00be2070(void* pNoun, int32_t nFlags);    // 0x00be2070
char  __cdecl FUN_00c004c0(int32_t nArg);                   // 0x00c004c0
void  __cdecl FUN_00be10d0();                               // 0x00be10d0
void  __cdecl FUN_00d5aae0(void* pContainer, void** ppOut, void* pArg);   // 0x00d5aae0
void  __cdecl FUN_00afa030(void* pSlot, void* pNoun);       // 0x00afa030
void  __cdecl FUN_009360d0();                               // 0x009360d0
void* __cdecl operator_new(uint32_t nSize, const char* pFile, int32_t a, int32_t b,
                           const char* pAlloc, int32_t nLine);      // 0x00f473a0
void  __cdecl operator_delete_array(void* pBlock);          // 0x00f47380
void  __cdecl eastl_copy_impl(void** pFirst, void** pLast, void** pDest);   // 0x006782c0
void  __cdecl SP_SetKeyKind(ResourceKey* pKey, uint32_t nKind, uint32_t nAux);   // 0x0068c6d0
cPlanetModel_s00be_30e0* __cdecl SP_PlanetModel(const void* pA, const void* pB, const void* pC);   // 0x00b3d350
cGameNounManager_s00be_30e0* __stdcall SP_NounManager(void* pNoun);    // 0x00b3d300
void  __cdecl SP_NormalizedSafe(const void* pIn, void* pOut);   // 0x00449c20
void  __cdecl SlotConstruct(void* pValue);                  // 0x00bdd470
void  __cdecl SlotDestroy(void* pValue);                    // 0x00bdd380
void* __cdecl SlotCopyRange(void* pFirst, void* pLast, void* pDest);   // 0x00bdd5c0
void  __cdecl SlotDestroyRange(void* pFirst, void* pLast, void* pUnused);   // 0x00bd8480
void  __cdecl SlotMoveBackward(void* pPos, void* pFirst, void* pLast);   // 0x00bdd640
struct cSlotVector {
    uint8_t* mpBegin;                                       // +0x00
    uint8_t* mpEnd;                                         // +0x04
    uint8_t* mpCap;                                         // +0x08

    void Insert(uint8_t* pPos, const uint8_t* pValue);      // 0x00be30e0
};
struct cAgentAction {
    virtual void v000();
    virtual void v004();
    virtual void v008();
    virtual void v00c();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01c();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02c();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03c();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04c();
    virtual void v050();
    virtual void v054();
    virtual cVec3* v058(cVec3* pOut);                       // +0x58 (world position)

    uint8_t      mPad004[0x64];                             // +0x004 .. +0x06b (align pad + 0x60)
    uint8_t      mField6c;                                  // +0x06c
    uint8_t      mPad06d[0x77];                             // +0x06d .. +0x0e3
    cRefList     mRefs0e4;                                  // +0x0e4
    uint8_t      mPad0f0[0x30];                             // +0x0f0 .. +0x11f
    cCombatant   mComponent120;                             // +0x120
    uint8_t      mPad124[0xbc];                             // +0x124 .. +0x1df
    uint32_t*    mpIDs1e0;                                  // +0x1e0
    uint32_t*    mpIDs1e4;                                  // +0x1e4
    uint8_t      mPad1e8[0x48];                             // +0x1e8 .. +0x22f
    cSPTimer_s00be_30e0     mTimer230;                                 // +0x230
    cSPTimer_s00be_30e0     mTimer250;                                 // +0x250
    cSPTimer_s00be_30e0     mTimer270;                                 // +0x270
    uint64_t     mTimestamp290;                             // +0x290
    uint8_t      mPad298[0x70];                             // +0x298 .. +0x307
    uint8_t      mField308[0x38];                           // +0x308 .. +0x33f
    cPtrList     mAgents340;                                // +0x340
    uint8_t      mPad348[0x0c];                             // +0x348 .. +0x353
    cPtrList     mAgents354;                                // +0x354
    uint8_t      mPad35c[0x88];                             // +0x35c .. +0x3eb
    cSlotMgr     mCircleA3ec;                               // +0x3ec
    cSlotMgr     mCircleB450;                               // +0x450
    cSlotMgr     mCircleC4b4;                               // +0x4b4
    uint8_t      mPad518[0x78];                             // +0x518 .. +0x58f
    cIDSource*   mpField590;                                // +0x590
    uint8_t      mPad594[0x0c];                             // +0x594 .. +0x59f
    cUIntMap     mMap5a0;                                   // +0x5a0 .. +0x649
    int32_t      mField64c;                                 // +0x64c
    float        mField650;                                 // +0x650
    uint8_t      mPad654[0x19c];                            // +0x654 .. +0x7ef
    int32_t      mField7f0;                                 // +0x7f0
    int32_t      mField7f4;                                 // +0x7f4
    uint8_t      mPad7f8[0x18];                             // +0x7f8 .. +0x80f
    cNoun*       mpField810;                                // +0x810

    bool  RemoveID(uint32_t nID);                           // 0x00be3230
    void  IncrementCounter();                               // 0x00be32b0
    void  IncrementCounterBy(int32_t nTimes);               // 0x00be32f0
    bool  RemoveAgent(void* pAgent);                        // 0x00be3350
    void  DestroyAgent(cNoun* pNoun);                       // 0x00be33e0
    void  DestroyAgentsOfType(uint32_t nUnused, int32_t nType);   // 0x00be3420
    void  RemoveSlotAgent(cNoun* pNoun);                    // 0x00be34a0
    void  RemoveAgentAndFlag(cNoun* pNoun);                 // 0x00be34e0
    bool  SpawnAgent(cNoun* pNoun, bool bNotify);           // 0x00be3500
    bool  FaceTarget();                                     // 0x00be3850
    bool  FaceSlot(uint32_t nSlot);                         // 0x00be3990
    void  UpdateRepair();                                   // 0x00be3ad0
    void  UpdateTimers();                                   // 0x00be3de0
    void  AdvanceFloatCounter(float fDelta);                // 0x00be3f00
    cRefList* ClearRefs();                                  // 0x00be3fe0
};
// ---- items of slice s00be30e0 end

// ---- items of slice s00be9d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(size_t, void* p) throw() { return p; }
void operator delete[](void* p);                                         // 0x00f47380
namespace SP {
struct Vector3_s00be_9d60 {
    float x, y, z;
    __forceinline Vector3_s00be_9d60() {}
    __forceinline Vector3_s00be_9d60(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline Vector3_s00be_9d60 operator-(const Vector3_s00be_9d60& v) const { return Vector3_s00be_9d60(x - v.x, y - v.y, z - v.z); }
    __forceinline Vector3_s00be_9d60 operator+(const Vector3_s00be_9d60& v) const { return Vector3_s00be_9d60(x + v.x, y + v.y, z + v.z); }
    __forceinline Vector3_s00be_9d60 operator*(float s) const { return Vector3_s00be_9d60(x * s, y * s, z * s); }
    __forceinline Vector3_s00be_9d60& operator+=(const Vector3_s00be_9d60& v) { x += v.x; y += v.y; z += v.z; return *this; }
    __forceinline float Length() const { return sqrtf(x * x + y * y + z * z); }
};
}
namespace SP {
template <class T> __forceinline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }
}
namespace SP {
template <class It, class T> __forceinline It find(It first, It last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}
}
namespace SP {
struct sp_vector_allocator {
    uint32_t mData[2];
};
}
namespace SP {
__forceinline void SpFree(void* p)
{
    if (((uint32_t*)p)[-1] != 0)
        operator delete[](p);
}
}
namespace SP {
struct UintVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    sp_vector_allocator mAllocator;

    __forceinline UintVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~UintVector() { if (mpBegin) SpFree(mpBegin); }
    void DoInsertValue(uint32_t* position, const uint32_t& value);       // 0x004558a0
    __forceinline void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) uint32_t(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace SP {
struct cLaneInfo_s00be_9d60 {
    Vector3_s00be_9d60 mPosition;              // +0x0
    UintVector mConnections;        // +0xc
};
}
namespace SP {
cLaneInfo_s00be_9d60* CopyLanes(cLaneInfo_s00be_9d60* first, cLaneInfo_s00be_9d60* last, cLaneInfo_s00be_9d60* dest);  // 0x00be0e80 (eastl::copy)
}
namespace SP {
struct LaneVector {
    cLaneInfo_s00be_9d60* mpBegin;
    cLaneInfo_s00be_9d60* mpEnd;
    cLaneInfo_s00be_9d60* mpCapacity;
    sp_vector_allocator mAllocator;

    void DestroyValues(cLaneInfo_s00be_9d60* first, cLaneInfo_s00be_9d60* last);               // 0x00bdc770
    void DoInsertValue(cLaneInfo_s00be_9d60* position, const cLaneInfo_s00be_9d60& value);     // 0x00be7aa0
    __forceinline cLaneInfo_s00be_9d60* erase(cLaneInfo_s00be_9d60* first, cLaneInfo_s00be_9d60* last)
    {
        cLaneInfo_s00be_9d60* const pNewEnd = CopyLanes(last, mpEnd, first);
        DestroyValues(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void clear() { erase(mpBegin, mpEnd); }
    __forceinline cLaneInfo_s00be_9d60& push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) cLaneInfo_s00be_9d60();
        else
            DoInsertValue(mpEnd, cLaneInfo_s00be_9d60());
        return *(mpEnd - 1);
    }
    __forceinline cLaneInfo_s00be_9d60& back() { return *(mpEnd - 1); }
};
}
namespace SP {
struct LaneCenter {                 // building centre and keep-out radius
    Vector3_s00be_9d60 mPosition;
    float mRadius;
    __forceinline LaneCenter() {}
};
}
namespace SP {
struct LanePoint {                  // one of the 6 ring points around a building
    Vector3_s00be_9d60 mPosition;              // +0x0
    int mMergedInto;                // +0xc  index of the point this one was merged into, or -1
    int mLaneIndex;                 // +0x10 index into mLanes
    int mLink;                      // +0x14 linked point of another ring, or -1
    bool mbInside;                  // +0x18 inside the walls' inner radius
    __forceinline LanePoint() {}
};
}
namespace SP {
struct CenterFixedVector {
    LaneCenter* mpBegin;
    LaneCenter* mpEnd;
    LaneCenter* mpCapacity;
    uint32_t mOverflowAllocator;
    void* mpPoolBegin;
    uint32_t mPad;
    LaneCenter mBuffer[32];

    __forceinline CenterFixedVector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 32;
    }
    __forceinline ~CenterFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(LaneCenter* position, const LaneCenter& value);   // 0x00bded00
    __forceinline LaneCenter& push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) LaneCenter();
        else
            DoInsertValue(mpEnd, LaneCenter());
        return *(mpEnd - 1);
    }
};
}
namespace SP {
struct PointFixedVector {
    LanePoint* mpBegin;
    LanePoint* mpEnd;
    LanePoint* mpCapacity;
    uint32_t mOverflowAllocator;
    void* mpPoolBegin;
    uint32_t mPad;
    LanePoint mBuffer[192];

    __forceinline PointFixedVector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 192;
    }
    __forceinline ~PointFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(LanePoint* position, const LanePoint& value);     // 0x00bdee20
    __forceinline LanePoint& push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) LanePoint();
        else
            DoInsertValue(mpEnd, LanePoint());
        return *(mpEnd - 1);
    }
    __forceinline LanePoint& back() { return *(mpEnd - 1); }
};
}
namespace SP {
class cSpatialObject_s00be_9d60 {
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
    virtual const Vector3_s00be_9d60& GetPosition();                                // 0x2c
virtual void v30();
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
    virtual Vector3_s00be_9d60 GetDirection(float f);                               // 0x5c
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void v70();
    virtual float GetFootprintRadius();                                  // 0x74
};
}
namespace SP {
class cBuilding_s00be_9d60 {
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
virtual void v2c();
virtual void v30();
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
    virtual const Vector3_s00be_9d60& func8Ch();                                    // 0x8c (ModAPI cBuilding)

    uint32_t mGameData[0x34 / 4 - 1];
    cSpatialObject_s00be_9d60 mSpatial;                                             // +0x34
};
}
namespace SP {
class cCityWalls_s00be_9d60 {
public:
    uint32_t pad0[0x258 / 4];
    float mInnerRadius;                                                  // +0x258
    uint32_t pad25c[(0x274 - 0x25c) / 4];
    bool mBuildingLinks[14][14];                                         // +0x274
};
}
namespace SP {
struct cLayoutSlot_s00be_9d60 {
    bool mIsOccupied;
    void* mpObject;
    int field_8;
    Vector3_s00be_9d60 mPosition;                                                   // +0xc
};
}
namespace SP {
class cCommunityLayout_s00be_9d60 {
public:
    cCommunityLayout_s00be_9d60();                                                  // 0x00afba10
    ~cCommunityLayout_s00be_9d60();                                                 // (atexit stub 0x013c31e0)
    void SetCenter(const Vector3_s00be_9d60& pos, float radius, const Vector3_s00be_9d60& dir);   // 0x00af9cf0
    void GenerateSlots(float a, float b, int count);                     // 0x00afd6d0
    int GetSlotIndex(cBuilding_s00be_9d60* object);                                 // 0x00afad30

    uint32_t pad0[0x50 / 4];
    cLayoutSlot_s00be_9d60* mSlotsBegin;                                            // +0x50 (mSlots.mpBegin)
    uint32_t pad54[(0x64 - 0x54) / 4];
};
}
namespace SP {
extern float g_LaneMergeDistance;    // 0x0156e140 (8.0)
}
namespace SP {
extern float g_LanePushStrength;     // 0x0156e144 (0.2)
}
namespace SP {
class cCity_s00be_9d60 {
public:
    void UpdateLanes();

    uint32_t pad0[0x84 / 4];
    LaneVector mLanes;                                                   // +0x84
    uint32_t pad98[(0x120 - 0x98) / 4];
    cSpatialObject_s00be_9d60 mSpatial;                                             // +0x120
    uint32_t pad124[(0x320 - 0x124) / 4];
    cBuilding_s00be_9d60* mpCityHall;                                               // +0x320
    cCityWalls_s00be_9d60* mpCityWalls;                                             // +0x324
    uint32_t pad328[(0x340 - 0x328) / 4];
    cBuilding_s00be_9d60** mBuildingsBegin;                                         // +0x340 (mBuildings)
    cBuilding_s00be_9d60** mBuildingsEnd;                                           // +0x344
    uint32_t pad348[(0x3ec - 0x348) / 4];
    cCommunityLayout_s00be_9d60 mBuildingLayout;                                    // +0x3ec
};
}
namespace SP {
__forceinline void AddConnection(UintVector& connections, uint32_t id)
{
    if (find(connections.mpBegin, connections.mpEnd, id) == connections.mpEnd)
        connections.push_back(id);
}
}
// ---- items of slice s00be9d60 end

// ---- items of slice s0132abc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0132_abc0; 
}
typedef eastl::string8_s0132_abc0 string8_s0132_abc0;
typedef bool (*ReadFunction_t)(void*, void*);
typedef bool (*WriteFunction_t)(void*, void*);
typedef void (*ReadTextFunction_t)(const string8_s0132_abc0&, void*);
typedef void (*WriteTextFunction_t)(char*, void*);
typedef bool (*ValidateFunction_t)();
typedef bool (*ToXmlFunction_t)(void*, const char*, int);
typedef void* (*OffsetFunction_t)(void*);
typedef void (*SetDefaultFunction_t)(void*);
void* DefaultOffset(void* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
struct Attribute
{
    // Offset is written last, after every callback slot -- matches the binary.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized by the constructor
    /* 10h */ int field_10;   // not initialized by the constructor
    /* 14h */ int field_14;   // not initialized by the constructor
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
struct TGateIndex{}; struct TAttackStateIdx{}; struct TAttackStateTime{}; struct TAttackerPoliticalID{}; struct TAttackers{}; struct THitSphere{};
template<typename T> bool Valid();                                    // 0x00b1fbf0
template<typename T> bool Read4(void*, void*);                        // 0x00572810
template<typename T> bool Write4(void*, void*);                       // 0x00572840
template<typename T> void ReadTextT(const string8_s0132_abc0&, void*);           // 0x00692ff0
template<typename T> void WriteTextT(char*, void*);                   // 0x00694ee0
template<typename T> bool ToXmlT(void*, const char*, int);            // 0x0057cde0
bool ToXml_00ac8050(void*, const char*, int);                         // 0x00ac8050
bool Read_00bb9cd0(void*, void*);                                     // 0x00bb9cd0
bool Write_00bb9d00(void*, void*);                                    // 0x00bb9d00
void ReadText_00693070(const string8_s0132_abc0&, void*);                        // 0x00693070
void WriteText_00694f80(char*, void*);                                // 0x00694f80
bool ToXml_00595a50(void*, const char*, int);                         // 0x00595a50
void ReadText_00693090(const string8_s0132_abc0&, void*);                        // 0x00693090
void WriteText_00694f00(char*, void*);                                // 0x00694f00
bool ToXml_00675ca0(void*, const char*, int);                         // 0x00675ca0
bool Read_00be0810(void*, void*);                                     // 0x00be0810
bool Write_00aca730(void*, void*);                                    // 0x00aca730
bool Valid_00b6f860();                                                // 0x00b6f860
bool ToXml_00c6c390(void*, const char*, int);                         // 0x00c6c390
bool Read_00bd0cb0(void*, void*);                                     // 0x00bd0cb0
bool Write_00bca960(void*, void*);                                    // 0x00bca960
bool Valid_00b6f550();                                                // 0x00b6f550
struct AttrSlot { uint32_t d[15]; };
#define ADD_ATTR(TABLE, IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&TABLE[IDX] = a; }
extern AttrSlot sCityAttributes[6];
// ---- items of slice s0132abc0 end

// ---- items of slice s0132d6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void fn_00572810();
extern "C" void fn_00572840();
extern "C" void fn_0057cde0();
extern "C" void fn_0057ce00();
extern "C" void fn_00675ca0();
extern "C" void fn_00692ca0();
extern "C" void fn_00692fb0();
extern "C" void fn_00692ff0();
extern "C" void fn_00693090();
extern "C" void fn_006930b0();
extern "C" void fn_00693150();
extern "C" void fn_00694ee0();
extern "C" void fn_00694f00();
extern "C" void fn_00694fa0();
extern "C" void fn_00694fc0();
extern "C" void fn_00695080();
extern "C" void fn_00ac8050();
extern "C" void fn_00ac8750();
extern "C" void fn_00ac8780();
extern "C" void fn_00ac88f0();
extern "C" void fn_00aca730();
extern "C" void fn_00acbb80();
extern "C" void fn_00ae3310();
extern "C" void fn_00ae3430();
extern "C" void fn_00ae3450();
extern "C" void fn_00ae3470();
extern "C" void fn_00ae3490();
extern "C" void fn_00ae5720();
extern "C" void fn_00aeacc0();
extern "C" void fn_00b03fd0();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00b6f550();
extern "C" void fn_00b6f860();
extern "C" void fn_00ba7590();
extern "C" void fn_00bab620();
extern "C" void fn_00bca960();
extern "C" void fn_00bda470();
extern "C" void fn_00bda500();
extern "C" void fn_00bda590();
extern "C" void fn_00bda5d0();
extern "C" void fn_00bda660();
extern "C" void fn_00bdc690();
extern "C" void fn_00bdc6c0();
extern "C" void fn_00bdc6f0();
extern "C" void fn_00bdc740();
extern "C" void fn_00be08f0();
extern "C" void fn_00be09d0();
extern "C" void fn_00be0ab0();
extern "C" void fn_00be0b90();
extern "C" void fn_00be2c00();
extern "C" void fn_00be2d80();
extern "C" void fn_00be6180();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00c6c390();
extern "C" void fn_00d011e0();
extern "C" void fn_00f29650();
extern "C" void fn_00fe4be0();
typedef void (*PropFn)();
struct PropDesc {
    const char* mpName;
    uint32_t    mnId;
    uint32_t    mnOffset;
    uint32_t    mUnset[3];   // never written by the original initializer (stack garbage copied)
    uint32_t    mnZero0;
    uint32_t    mnZero1;
    PropFn      mpFn[7];
};
extern PropDesc g_156ea28;
extern PropDesc g_156ea64;
extern PropDesc g_156eaa0;
extern PropDesc g_156eadc;
extern PropDesc g_156eb18;
extern PropDesc g_156eb54;
extern PropDesc g_156eb90;
extern PropDesc g_156ebcc;
extern PropDesc g_156ec08;
extern PropDesc g_156ec44;
extern PropDesc g_156ec80;
extern PropDesc g_156ecbc;
extern PropDesc g_156ecf8;
extern PropDesc g_156ed34;
extern PropDesc g_156ed70;
extern PropDesc g_156edac;
extern PropDesc g_156ede8;
extern PropDesc g_156ee24;
extern PropDesc g_156ee60;
extern PropDesc g_156ee9c;
extern PropDesc g_156eed8;
extern PropDesc g_156ef14;
extern PropDesc g_156ef50;
extern PropDesc g_156ef8c;
extern PropDesc g_156efc8;
extern PropDesc g_156f004;
extern PropDesc g_156f040;
extern PropDesc g_156f07c;
extern PropDesc g_156f0b8;
extern PropDesc g_156f0f4;
extern PropDesc g_156f130;
extern PropDesc g_156f16c;
extern PropDesc g_156f1a8;
extern PropDesc g_156f1e4;
extern PropDesc g_156f220;
extern PropDesc g_156f25c;
extern PropDesc g_156f298;
extern PropDesc g_156f2d4;
extern PropDesc g_156f310;
extern PropDesc g_156f34c;
extern PropDesc g_156f388;
extern PropDesc g_156f3c4;
extern PropDesc g_156f400;
extern PropDesc g_156f43c;
extern PropDesc g_156f478;
extern PropDesc g_156f4b4;
// ---- items of slice s0132d6d0 end

// ---- items of slice s00bd5ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100)
typedef unsigned int   uint;
typedef int   (__thiscall* Fn_i_v)(void*);
#define VT(p, off)     (*(void**)((char*)(*(void**)(p)) + (off)))
struct IRef {
  virtual int AddRef();
  virtual int Release();
};
namespace SP {
class cGameData_s00bd_5ea0 : public IRef {
 public:
  char  pad04[8];
  void* mpNext;                  // +0x0c
  void* mpPrev;                  // +0x10
  bool  mIsDestroyed;            // +0x14
  char  pad15[3];
  uint  mID;                     // +0x18
  uint  mDefinitionID;           // +0x1c
  bool  mb20;                    // +0x20
  bool  mb21;                    // +0x21
  char  pad22[2];
  uint  m24;                     // +0x24
  void* mView;                   // +0x28
  IRef* mpGameDataOwner;         // +0x2c
  uint  mPoliticalID;            // +0x30

  cGameData_s00bd_5ea0();                                            // 0x00b18660
  int GetFieldValues(void* vec);                         // 0x00b18420
  uint GetPoliticalID() const;                            // 0x00804830
  uint GetNounID() const;                                 // vtable slot 0x20
  uint GetNounKey() const;                                // vtable slot 0x4c
  void WriteData(void* s) const;                          // 0x00b18590
  void ReadData(void* s);                                 // 0x00b18600
  void WriteTagged(void* s);                              // 0x00bd6230
  void DtorBody();                                        // 0x00b184c0
  void* AsInterfaceQuery(uint id);                        // 0x00b18460
};
}
namespace SP {
class cSpatialObject_s00bd_5ea0 {
 public:
  virtual ~cSpatialObject_s00bd_5ea0();
  bool WriteSpatial(void* s) const;                 // 0x00c88a90
  bool ReadSpatial(void* s);                        // 0x00c88b00
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
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

  cSpatialObject_s00bd_5ea0();                                 // 0x00c89630
  void DtorBody();                                  // 0x00c8a420
  void* AsInterfaceQuery(uint id);                  // 0x00c884f0
  char pad80[0x6c];
  bool mbSpatialFlag;                               // +0x70 (retail)
  char pad71[0x63];                                 // -> retail size 0xd4
};
}
namespace SP {
class cInteractionTarget_s00bd_5ea0 {
 public:
  virtual ~cInteractionTarget_s00bd_5ea0();
  virtual void* AsInterface(uint id);
  virtual void RemoveInteraction(void* i);
  virtual void AddInteraction(void* i);
  virtual void Shutdown();
  virtual int Release();
  cInteractionTarget_s00bd_5ea0();                             // 0x00ac03d0
  void DtorBody();                                  // 0x00ac0520
  void* QueryInterfaceHere(uint id);                // 0x00ac0320
  char pad04[0x14];                                 // -> retail size 0x18
};
}
namespace SP {
class cCheatObject : public cGameData_s00bd_5ea0, public cSpatialObject_s00bd_5ea0, public cInteractionTarget_s00bd_5ea0 {
 public:
  cCheatObject();                                   // 0x00bd6a80
  ~cCheatObject();                                  // 0x00bd6c10
  void BindCheatHandlers();                         // 0x00bd6c60
  void DtorBases();                                 // 0x00bd6750
  void* QueryInterface(uint id);                    // 0x00bd6770
  void WriteBody(void* s) const;                    // 0x00bd67c0
  void ReadBody(void* s);                           // 0x00bd6810
  int GetFieldValuesAll(void* vec);                 // 0x00bd6b10
  IRef* mpDataObject;                               // +0x120
  bool  mFlag124;                                   // +0x124
  char  pad125[3];
};
}
using SP::cGameData_s00bd_5ea0;
using SP::cCheatObject;
#define gStr_1467f50 ((const wchar_t*)g_1467f50)   // 0x01467f50
#define gStr_1467f48 ((const wchar_t*)g_1467f48)   // 0x01467f48
#define gStr_1467f40 ((const wchar_t*)g_1467f40)   // 0x01467f40
struct cCityInputStrategy {                        // singleton at 0x0168bd4c
  void Begin();                                    // 0x00b7d390
  void AddNode(const wchar_t* name, int id, int flags); // 0x00b7d2e0
  void SelectNode(void* obj, void* arg);           // 0x00b7cc60
};
#define kCityInputStrategy ((cCityInputStrategy*)g_168bd4c)
#define gStrEnergy ((const wchar_t*)g_1467f90)         // 0x01467f90
#define gStrEntertainment ((const wchar_t*)g_1467f74)  // 0x01467f74
#define gStrHappiness ((const wchar_t*)g_1467f60)      // 0x01467f60
#define gStrAll ((const wchar_t*)g_1467f58)            // 0x01467f58
#define gStrHunger ((const wchar_t*)g_1467fb0)   // 0x01467fb0
#define gStrHealth ((const wchar_t*)g_1467fa0)   // 0x01467fa0
#define gStrSetMotive ((const wchar_t*)g_1468350)   // 0x01468350
#define gStrHappinessW ((const wchar_t*)g_1468324)  // 0x01468324
#define gStrToggleId ((const wchar_t*)g_1468300)    // 0x01468300
#define gStrMaxVehicles ((const wchar_t*)g_14682dc) // 0x014682dc
// ---- items of slice s00bd5ea0 end

// ---- items of slice s00bda190 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cPtrVec {
    void*    mpBegin;                                       // +0x00
    void*    mpEnd;                                         // +0x04
    void*    mpCapacity;                                    // +0x08
};
struct cCulturalTarget_s00bd_a190;
struct cHallTarget;
struct cGameData_s00bd_a190 {
    virtual void       AddRef();                            // +0x00
    virtual void       Release();                           // +0x04
    virtual void       v08();                               // +0x08
    virtual cGameData_s00bd_a190* Cast(uint32_t nType);                // +0x0c
    virtual void       v10();                               // +0x10
    virtual void       v14();                               // +0x14
    virtual void       v18();                               // +0x18
    virtual void       v1c();                               // +0x1c
    virtual int32_t    GetDefinitionID();                   // +0x20
    virtual void       v24();                               // +0x24
    virtual void       v28();                               // +0x28
    virtual void       v2c();                               // +0x2c
    virtual void       v30();                               // +0x30
    virtual void       v34();                               // +0x34
    virtual void       v38();                               // +0x38
    virtual void       v3c();                               // +0x3c
    virtual void       v40();                               // +0x40
    virtual void       v44();                               // +0x44
    virtual void       v48();                               // +0x48
    virtual int32_t    GetPoliticalID();                    // +0x4c
virtual void       v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void       v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void       v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void       v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void       v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void       va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void       vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
    virtual void       ReleaseGameData();                   // +0xc0
};
struct cSpatialVtbl {
    void*    mpSlots00[0xb];                                // +0x00 .. +0x2b
    Vector3* (*pGetPosition)(void* pThis, const Vector4* pParams);   // +0x2c
    void*    mpSlots30[2];                                  // +0x30 .. +0x37
    void     (*pSetPosition)(void* pThis, const Vector3* pValue);     // +0x38
    void     (*pSetOrientation)(void* pThis, const Quaternion* pValue);  // +0x3c
    void*    mpSlots40[6];                                  // +0x40 .. +0x57
    void*    (*pGetPlanetPosition)(void* pThis, void* pOut);   // +0x58
    void*    mpSlots5C[1];                                  // +0x5c
};
struct cSpatialObject_s00bd_a190 {
    cSpatialVtbl* mVtbl;                                    // +0x00

    int32_t  GetObjectCount();                              // 0x008e7f80
    Vector3* GetPosition(const Vector4* pParams) { return mVtbl->pGetPosition(this, pParams); }
    void     SetPosition(const Vector3* pValue) { mVtbl->pSetPosition(this, pValue); }
    void     SetOrientation(const Quaternion* pValue) { mVtbl->pSetOrientation(this, pValue); }
    void*    GetPlanetPosition(void* pOut) { return mVtbl->pGetPlanetPosition(this, pOut); }
};
struct cPlanetObjectVtbl {
    void*    mpSlots00[0xb];                                // +0x00 .. +0x2b
    Vector3* (*pGetPosition)(void* pThis);                  // +0x2c
    void*    mpSlots30[0xa];                                // +0x30 .. +0x57
    bool     (*pIsOccupied)(void* pThis);                   // +0x58
    void*    mpSlots5C[4];                                  // +0x5c .. +0x6b
    void*    (*pGetTerrainSphere)(void* pThis);             // +0x6c
};
struct cPlanetObject {
    cPlanetObjectVtbl* mpVtbl;                              // +0x00
};
struct cPlanetModel_s00bd_a190 {
    cPlanetObject* FindObjectAt(const Vector3* pPosition);  // 0x00b894a0
};
cPlanetModel_s00bd_a190* __cdecl PlanetModel_s00bd_a190();                        // 0x00b3d350
class cCombatant_s00bd_a190 {
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
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
};
struct cAutoRefData {
    virtual void AddRef();                                  // +0x00
    virtual void Release();                                 // +0x04
};
struct cAutoRef12 {
    cAutoRefData* mpFirst;                                  // +0x00
    cAutoRefData* mpSecond;                                 // +0x04
    uint32_t      mField08;                                 // +0x08
};
struct cRefOps {
    cRefOps*    AssignRefPairObj(const cAutoRef12* pSrc);   // 0x00bda760
    void        CopyTransform50Obj(const void* pSrc);       // 0x00bda7d0
    void        DestroyGonzagoTimerObj();                   // 0x00b638b0 (~SP::cGonzagoTimer)
};
inline void DestroyGonzagoTimer(void* pTimer)
{
    ((cRefOps*)pTimer)->DestroyGonzagoTimerObj();
}
struct cCulturalTarget_s00bd_a190 {
    cGameData_s00bd_a190      mGameData;                               // +0x000
    char           mPad004[0x34];                           // +0x004 .. +0x037
    cCombatant_s00bd_a190     mCombatant;                              // +0x038
    char           mPad03c[0xc4];                           // +0x03c .. +0x0ff
    char           mPad100[0xd4];                           // +0x100 .. +0x1d3
    int8_t         mGateIndex;                              // +0x1d4
    char           mPad1d5[3];                              // +0x1d5
    int32_t        mAttackState;                            // +0x1d8
    uint32_t       mAttackerPoliticalID;                    // +0x1dc
    cPtrVec        mAttackOrders;                           // +0x1e0 .. +0x1eb (vector<int>)
    char           mPad1ec[8];                              // +0x1ec .. +0x1f3
    cPtrVec        mAttackers;                              // +0x1f4 .. +0x1ff (vector<AutoRefCount>)
    char           mPad200[8];                              // +0x200 .. +0x207
    cGameData_s00bd_a190*     mpHitSphere;                             // +0x208
    float          mLastDancingCrowdFraction;               // +0x20c
    float          mLastAngryCrowdFraction;                 // +0x210
    int32_t        mAngerLevel;                             // +0x214

    cSpatialObject_s00bd_a190* GetSpatial() { return (cSpatialObject_s00bd_a190*)((char*)this + 0x100); }

    ~cCulturalTarget_s00bd_a190();                                     // 0x00bdace0
    bool RemoveAttacker(cGameData_s00bd_a190* pTarget);                // 0x00bdad60
};
typedef char cCulturalTargetSizeCheck[(sizeof(cCulturalTarget_s00bd_a190) == 0x218) ? 1 : -1];
struct cCityCivVtbl {
    void*    mpSlots00[0x13];                               // +0x00 .. +0x4b
    int32_t  (__thiscall* pGetPoliticalID)(void* pThis);    // +0x4c
};
struct cCityCiv {
    cCityCivVtbl* mpVtbl;                                   // +0x00

    int32_t GetPoliticalID() { return mpVtbl->pGetPoliticalID(this); }
};
struct cTradePartnerCity {
    char           mPad000[0x120];                          // +0x000 .. +0x11f
    cSpatialObject_s00bd_a190 mSpatial;                                // +0x120
    char           mPad124[0x46c];                          // +0x124 .. +0x58f
    cCityCiv*      mpCivilization;                          // +0x590
};
struct cCity_s00bd_a190 {
    char           mPad000[0x120];                          // +0x000 .. +0x11f
    cSpatialObject_s00bd_a190 mSpatial120;                             // +0x120
    char           mPad124[0x21c];                          // +0x124 .. +0x33f
    cPtrVec        mBuildings;                              // +0x340 .. +0x34b
    char           mPad34c[0x210];                          // +0x34c .. +0x55b
    cPtrVec        mTradePartners;                          // +0x55c .. +0x567
    char           mPad568[0xb0];                           // +0x568 .. +0x617
    cPtrVec        mCultureTargetInfo;                      // +0x618 .. +0x623
    char           mPad624[8];                              // +0x624 .. +0x62b
    cCulturalTarget_s00bd_a190* mCulturalTargets[4];                   // +0x62c .. +0x63b

    int32_t CountBuildings(int32_t nDefinitionID, int32_t nPoliticalID);   // 0x00bda190
    bool    HasTradePartnerCiv(int32_t nNounID);            // 0x00bdb200
    cCity_s00bd_a190*  FindTradePartnerCity(int32_t nNounID);          // 0x00bdb280
};
struct cHallTransform {
virtual void      v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void      v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void      v20();
virtual void v24();
virtual void v28();
    virtual Vector3*  GetPosition();                        // +0x2c
virtual void      v30();
virtual void v34();
virtual void v38();
virtual void      v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void      v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void*     MakeTransform(void* pOut);            // +0x5c
virtual void      v60();
virtual void v64();
    virtual cHallTarget* GetTarget();                       // +0x68
    virtual void      v6c();
    virtual float     GetRadius();                          // +0x70
};
struct cHallTarget {
    char  mPad000[0x14];                                    // +0x000 .. +0x013
    float mScale;                                           // +0x014
    char  mPad018[0x220];                                   // +0x018 .. +0x237
    float mRadius;                                          // +0x238
};
struct cCityHall {
    char           mPad000[0x34];                           // +0x000 .. +0x033
    cHallTransform mTransform34;                            // +0x034
    char           mPad0b4[0x290];                          // +0x0b4 .. +0x343
    cHallTarget*   mpTarget344;                             // +0x344

    cHallTarget* GetHallTarget();                           // 0x00bebdb0
};
struct cCityWalls_s00bd_a190 {
    char  mPad000[0x25c];                                   // +0x000 .. +0x25b
    float mRadius;                                          // +0x25c
};
struct cSimObject {
    char           mPad000[0x120];                          // +0x000 .. +0x11f
    cSpatialObject_s00bd_a190 mSpatial120;                             // +0x120
    char           mPad124[0x178];                          // +0x124 .. +0x29b
    int32_t        mContextState;                           // +0x29c
    char           mPad2a0[0x46];                           // +0x2a0 .. +0x2e5
    uint8_t        mbField2E6;                              // +0x2e6
    char           mPad2e7[0x39];                           // +0x2e7 .. +0x31f
    cCityHall*     mpCityHall;                              // +0x320
    cCityWalls_s00bd_a190*    mpCityWalls;                             // +0x324
    char           mPad328[0x304];                          // +0x328 .. +0x62b
    cCulturalTarget_s00bd_a190* mCulturalTargets[4];                   // +0x62c .. +0x63b

    void UpdateAggregationRadius();                         // 0x00bdaea0
    void FillCulturalTargetPoints();                        // 0x00bdaf50
    void EmitCulturalEffect();                              // 0x00bdb0b0
};
struct cDispatcherVtbl {
    void*    mpSlots00[0x18];                               // +0x00 .. +0x5f
    void     (*pFire)(void* pThis, uint32_t nEffectID, const Vector3* pPosition, void* pTransform);   // +0x60
};
struct cDispatcher {
    cDispatcherVtbl* mpVtbl;                                // +0x00
};
cDispatcher* __cdecl GetDispatcher();                       // 0x00b3d240
struct tCultureTargetInfo_s00bd_a190 {
    int32_t mBucketMaxPopulation[2];                        // +0x00
    int32_t mBucketPopulation[2];                           // +0x08
    int32_t mBucketEmigration[2];                           // +0x10
    int32_t mBucketImmigration[2];                          // +0x18
    uint8_t mbClearEverything;                              // +0x20
    char    mPad21[3];                                      // +0x21
    float   mAngryCrowdFraction;                            // +0x24
    float   mDancingCrowdFraction;                          // +0x28
    float   mIndifferentCrowdFraction;                      // +0x2c
    char    mConvertCheckTimer[0x20];                       // +0x30 .. +0x4f
    char    mConvertedTimer[0x20];                          // +0x50 .. +0x6f
    cGameData_s00bd_a190*    mpAttackTarget;                           // +0x70
    uint8_t mbAttackTargetChanged;                          // +0x74
    char    mPad75[3];                                      // +0x75
    cGameData_s00bd_a190* mpCultureObject;                             // +0x78
    char    mPad7c[4];                                      // +0x7c
};

void* __cdecl GetCurrentGameMode();                         // 0x00b5b800
void  __cdecl FillPoints(void* pOut);                       // 0x00bed3c0
void* __cdecl BuildSurfaceOrientation2(void* pOut, const Vector3* pDirection, const Vector3* pPosition);  // 0x00b7f250
void  __cdecl DestroySpatialObject(void* pObject);          // 0x00c8a420 (~cSpatialObject)
void  __cdecl DestroyCombatant(void* pObject);              // 0x00bfcd00 (~cCombatant)
void  __cdecl DestroyGameData(void* pObject);               // 0x00b184c0 (~cGameData)
void  __cdecl DestroyAutoRefVector(void* pVector);          // 0x00ae6970 (~eastl::vector<AutoRefCount>)
const float    kSqrtEpsilon_s00bd_a190       = 1.0e-8f;                // 0x013ec4b8 (0x322bcc77)
const float    kCultureScaleSpace = 1.3f;                   // 0x013ef578 (0x3fa66666)
const float    kCultureScalePlanet = 0.8f;                  // 0x01486374 (0x3f4ccccd)
const float    kFloatMax_s00bd_a190          = 3.402823466e38f;        // 0x0146847c (0x7f7fffff)
const uint32_t kSpaceGameModeID   = 0x01654c05;
const uint32_t kCulturalEffect0   = 0x04aef54c;
const uint32_t kCulturalEffect1   = 0x05f2281e;
const uint32_t kCulturalEffect2   = 0x05f22835;
const uint32_t kCultureTargetCastType = 0x0137e8e0;
namespace Simulator {
struct CGameDataPart {
    void* volatile mpVtbl;  // +0x00
    void Ctor();            // 0x00b18660
};
}
namespace Simulator {
struct CCombatantPart {
    void* volatile mpVtbl;  // +0x00
    void Ctor();            // 0x00bfd4e0
};
}
namespace Simulator {
struct CSpatialPart {
    void* volatile mpVtbl;  // +0x00
    void Ctor();            // 0x00c89630
};
}
namespace Simulator {
struct VPtrVec {
    void* volatile mpBegin;     // +0x00
    void* volatile mpEnd;       // +0x04
    void* volatile mpCapacity;  // +0x08
};
}
namespace Simulator {
struct cCulturalTarget_s00bd_a190 {
    CGameDataPart  mGameData;                           // +0x000
    void* volatile mpVtbl04;                            // +0x004
    char           mPad008[0x30];                       // +0x008 .. +0x037
    CCombatantPart mCombatant;                          // +0x038
    char           mPad03c[0xc4];                       // +0x03c .. +0x0ff
    CSpatialPart   mSpatial;                            // +0x100
    char           mPad104[0xd0];                       // +0x104 .. +0x1d3
    uint8_t        volatile mGateIndex;                 // +0x1d4
    char           mPad1d5[3];                          // +0x1d5 .. +0x1d7
    int32_t        volatile mAttackState;               // +0x1d8
    uint32_t       volatile mAttackerPoliticalID;       // +0x1dc
    VPtrVec        mAttackOrders;                       // +0x1e0
    char           mPad1ec[8];                          // +0x1ec .. +0x1f3
    VPtrVec        mAttackers;                          // +0x1f4
    char           mPad200[8];                          // +0x200 .. +0x207
    void*          volatile mpHitSphere;                // +0x208
    float          mLastDancingCrowdFraction;           // +0x20c
    float          mLastAngryCrowdFraction;             // +0x210
    int32_t        volatile mAngerLevel;                // +0x214

    cCulturalTarget_s00bd_a190();
};
}
namespace Simulator {
typedef char cCulturalTargetSizeCheck[(sizeof(cCulturalTarget_s00bd_a190) == 0x218) ? 1 : -1];
}
// ---- items of slice s00bda190 end

// ---- items of slice s00bdc350 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (__thiscall *Void0)(void*);
typedef void (__thiscall *Void1)(void*, void*);
typedef int  (__thiscall *Int1)(void*, int);
struct Obj2f0 {
    char pad00[0x70];
    char* mp70;                 // +0x70
    char pad74[0x320 - 0x74];
    int m320;                   // +0x320
    char pad324[0x51c - 0x324];
    int m51c;                   // +0x51c (float bits)
    int m520;                   // +0x520 (float bits)
    int m524;                   // +0x524 (float bits)
    void __thiscall Notify();   // 0x00bdbaa0
};
struct Object7b0 {
    char pad00[0x34];
    int mSub;                   // +0x34
};
struct Vector3_s00bd_c350 { float x, y, z; };
struct Quaternion_s00bd_c350 { float x, y, z, w; };
struct Matrix3 { float m[9]; };
struct XformMsg_s00bd_c350 {                       // ctor 0x00434040, 0x38 bytes
    u16 mFlags;                         // +0x00
    short mCount;                       // +0x02
    Vector3_s00bd_c350 mPosition;                  // +0x04
    float mScale;                       // +0x10
    Matrix3 mRotation;                  // +0x14
    XformMsg_s00bd_c350();
    void SetPos(const Vector3_s00bd_c350& v) { mPosition = v; mFlags |= 4; ++mCount; }
    void SetRot(const Matrix3& m) { mRotation = m; mFlags |= 2; ++mCount; }
};
struct IEffect {
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
    virtual void Start(int flags);      // +0x08
    virtual void Stop(int flags);       // +0x0c
    virtual void v10();                 // +0x10
    virtual void v14();                 // +0x14
    virtual void SetTransform(XformMsg_s00bd_c350* msg);  // +0x18
};
struct EffectsMgr {
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
    virtual bool CreateEffect(u32 id, int flags, IEffect** out);  // +0x2c
};
struct Obj590 {
    char padC4[0xc4];
    Vector3_s00bd_c350 mC4;                        // +0xc4
    char* __thiscall F00bef950();       // 0x00bef950
};
struct Timer {
    char m[0x20];
    void __thiscall Restart();          // 0x00bc3130
};
struct SelfB {
    char pad00[0x120];
    void* m120Vtbl;                     // +0x120 (inline subobject)
    char pad124[0x220 - 0x124];
    float m220;                         // +0x220
    char pad224[0x2cc - 0x224];
    int m2cc;                           // +0x2cc
    int m2d0;                           // +0x2d0
    char pad2d4[0x320 - 0x2d4];
    void* m320;                         // +0x320
    char pad324[0x58c - 0x324];
    u8 m58c;                            // +0x58c
    char pad58d[0x590 - 0x58d];
    Obj590* m590;                       // +0x590
    char pad594[0x64c - 0x594];
    int m64c;                           // +0x64c
    char pad650[0x758 - 0x650];
    float m758;                         // +0x758
    int m75c;                           // +0x75c
    char pad760[0x764 - 0x760];
    int m764;                           // +0x764
    IEffect* m768;                      // +0x768
    char pad76c[4];
    Timer m770;                         // +0x770
    char pad790[0x7d4 - 0x790];
    IEffect* m7d4;                      // +0x7d4

    void __thiscall F00bdbc20(void* p); // 0x00bdbc20
    void __thiscall F00bdbf10();        // 0x00bdbf10
    int __thiscall F00bf01e0();         // helper on the noun result
    bool __thiscall FUN_00bdc4a0(char enable);
    void __thiscall FUN_00bdc8a0(u64 delta);
    void __thiscall FUN_00bdd120(float amount, int key);
};
EffectsMgr* __cdecl EffectsManager();                    // 0x0067ddd0
Matrix3& __cdecl Matrix3FromQuaternion(Matrix3& out, const Quaternion_s00bd_c350& q); // 0x0059c190
int __cdecl GetPlayerEmpireID_s00bd_c350();                         // 0x01021090
void __cdecl DoCommunityReaction(void* self, float f, const Vector3_s00bd_c350& pos); // 0x00ff5270
void* __cdecl RelationshipManager();                     // 0x00b3d2c0
struct RelationshipMgr {
    float __thiscall RecordEvent(int a, int b, u32 ev, float amount); // 0x00d06240
};
struct RandomGlobal {
    double __thiscall RandomDouble();        // 0x009360d0
};
// ---- items of slice s00bdc350 end

// ---- items of slice s00bdde70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyW[2];                                             // 0x01667bac
extern char       gAppNameTag;            // 0x01654c05
extern float      kTickLimit;             // 0x013ec5b4
extern float      kEmpty3[3];             // 0x0168bd70
extern float      kC1, kC2;               // 0x0156e15c / 0x013ec4d0
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);   // 0x00F473A0
enum
{
    kGameModeCiv   = 0x01654c04,
    kGameModeSpace = 0x01654c05,
};
struct WStr {  // eastl::basic_string<wchar_t> (begin, end, capacity-end)
    wchar_t *b, *e, *cap;
};
struct Variant {  // EA::Variant
    char data[0x10];
    unsigned short mFlags;
    unsigned short mTypeId;
    void Set(int type, int kind, const void* p, int size, int copy);   // 0x0093dd80
    void Destruct(int);                                                // 0x0093db80
};
struct cString {  // SP::cString
    char d[0x14];
    cString();                                                         // 0x006b5060
    ~cString();                                                        // 0x006b5240
    void Load(unsigned int tableId, unsigned int instanceId, int flag); // 0x006b54b0 (ret 0xc)
    const wchar_t* GetText();                                          // 0x006b55c0
};
struct IColorable {  // interface cast out of a window (typeID 0xf15f4bd)
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
    virtual void SetColor(unsigned int argb);                          // +0x28
};
struct IWindow {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual IColorable* Cast(unsigned int typeID);                     // +0x0c
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
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
    virtual IWindow* FindWindow(unsigned int id, int recurse);         // +0xf0
};
class cSPUIRolloverCivCityHall
{ public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void Refresh();                                            // +0x20
    char pad04[0x78 - 0x4];
    IWindow* GetRootWindow();                                          // 0x00828100
    void ClearEntries();                                               // 0x00e2adb0
    void AddEntry(int slot, int count, unsigned int argb);             // 0x00e2c840 (ret 0xc)
    void SelectEntry(int slot);                                        // 0x00e2ab10 (ret 4)
    void SetProp(unsigned int id, Variant* v, int a, int b);           // 0x00828c30 (ret 0x10)
    void SetSpecialtyIcon(unsigned int id);                            // 0x00e2a7b0 (ret 4)
    void SetOwnerButtonState(bool b);                                  // 0x00e2a600 (ret 4)
};
struct cColor3c { unsigned int GetARGB(); };                           // 0x00b6f310 (on civ+0x3c)
struct cCivilization_s00bd_de70
{
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
virtual void v40();
virtual void v44();
virtual void v48();
    virtual int GetRelationshipEmpire(int empireId);                   // +0x4c
    char pad04[0x3c - 0x4];
    cColor3c mColor;                                                   // +0x3c
};
struct cGameNounManager_s00bd_de70
{
    cCivilization_s00bd_de70* FindCivilization(unsigned int empireId);            // 0x00b25f40 (ret 4)
    cCivilization_s00bd_de70* GetPlayerCivilization();                            // 0x00b25fb0
    int GetPlayerEmpireOrMinus1();                                     // 0x00b1f9d0 (does not use this)
};
struct cCivModeStrategy { void SetSelectedCity(void* city); };         // 0x00cfe780 (ret 4)
extern cCivModeStrategy* gCivModeStrategy;                             // 0x0169d3c8
struct ICityName
{
    virtual void v00();
    virtual const wchar_t* GetName();                                  // +0x4
};
struct RBNode { RBNode* mpRight; RBNode* mpLeft; RBNode* mpParent; int mColor; unsigned int mKey; int mValue; };
RBNode* RBTreeIncrement(RBNode* p);                                    // 0x00921580 (cdecl)
struct cCombatant_s00bd_de70 { int GetDamageState(); };                           // 0x008e7f80
struct cCitizen { char pad[0x588]; cCombatant_s00bd_de70 mCombatant; };           // +0x588
cGameNounManager_s00bd_de70* NounManager_s00bd_de70();                                       // 0x00b3d300
int GetCurrentGameMode_s00bd_de70();                                              // 0x00b5b800
float GetRelationshipValue(int otherEmpire, int myEmpire);             // 0x00d00d00 (cdecl, float in st0)
static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct cSPTimer_s00bd_de70 {
    long long GetElapsedTime();               // 0x00bc3190 (returns edx:eax)
    void Restart();                           // 0x00bc3130
};
struct cCity_s00bd_de70
{
    char pad000[0x34];
    ICityName mName;                                                   // +0x34 (embedded, own vtable)
    char pad038[0x120 - 0x38];
    void* mpSpaceGame;                                                 // +0x120 (Simulator space-game object)
    char pad124[0x304 - 0x124];
    float mfHappiness;                                                 // +0x304
    char pad308[0x32c - 0x308];
    float mPosX;                                                       // +0x32c (Vector3 position)
    float mPosY;                                                       // +0x330
    float mPosZ;                                                       // +0x334
    char pad338[0x33c - 0x338];
    bool mbIsPlayerCity;                                               // +0x33c
    char pad33d[0x354 - 0x33d];
    cCitizen** mCitizensBegin;                                         // +0x354
    cCitizen** mCitizensEnd;                                           // +0x358
    char pad35c[0x540 - 0x35c];
    int mVehicleSpecialty;                                             // +0x540
    char pad544[0x590 - 0x544];
    cCivilization_s00bd_de70* mpCivilization;                                     // +0x590
    char pad594[0x5a4 - 0x594];
    RBNode* mAllegianceAnchorRight;                                    // +0x5a4 (map<uint,int> anchor)
    RBNode* mAllegianceBegin;                                          // +0x5a8
    char pad5ac[0x668 - 0x5ac];
    int mHappyCount;                                                   // +0x668
    int mUnhappyCount;                                                 // +0x66c
    char pad670[0x678 - 0x670];
    int mFinalIncome;                                                  // +0x678
    char pad67c[0x698 - 0x67c];
    bool mPartyOn;                                                     // +0x698
    char pad699[0x6c0 - 0x699];
    bool mRiotOn;                                                      // +0x6c0
    char pad6c1[0x708 - 0x6c1];
    cSPTimer_s00bd_de70 mTimer;                                                   // +0x708

    int GetHousingAmount();                                            // 0x00bd8960
    void UpdateCityHallRollover(cSPUIRolloverCivCityHall* pUI);
    int* FUN_00bde4a0();                                               // 0x00bde4a0 (__fastcall, this in ecx)
};
static __forceinline int CharStrlen(const wchar_t* p)
{
    const wchar_t* q = p;
    while (*q)
        ++q;
    return (int)(q - p);
}
static __forceinline void MakeWStr(WStr& s, const wchar_t* p)
{
    s.b = s.e = s.cap = 0;
    const wchar_t* pEnd = p + CharStrlen(p);
    int n = (int)(pEnd - p);
    unsigned int sz = n + 1;
    wchar_t* buf;
    if (sz > 1) {
        buf = (wchar_t*)operator new(sz * 2, "Simulator", 0, 0, kEastlFile, 0xd1);
        s.b = buf;
        s.cap = (wchar_t*)((char*)buf + sz * 2);
    } else {
        buf = gEmptyW;
        s.b = gEmptyW;
        s.cap = gEmptyW + 1;
    }
    s.e = buf;
    memcpy(buf, p, n * 2);
    s.e = buf + n;
    *s.e = 0;
}
static __forceinline void FreeWStr(WStr& s)
{
    if ((int)(((char*)s.cap - (char*)s.b) & ~1) > 2 && s.b)
        operator delete[](s.b);
}
static __forceinline void SetStringProp(cSPUIRolloverCivCityHall* pUI, unsigned int id, WStr& s)
{
    Variant v;
    v.mFlags = 0;
    v.mTypeId = 0;
    v.Set(0x13, 9, &s, 0x10, 1);
    pUI->SetProp(id, &v, 1, 0);
    if (v.mFlags & 4)
        v.Destruct(0);
}
static __forceinline void SetFloatProp(cSPUIRolloverCivCityHall* pUI, unsigned int id, float f)
{
    Variant v;
    v.mTypeId = 0xd;
    v.mFlags = 0;
    *(float*)v.data = f;
    pUI->SetProp(id, &v, 2, 0);
    if (v.mFlags & 4)
        v.Destruct(0);
}
struct EmptyBubble {                // SP::cEmptyBubble  (0x14): 4 floats + an id
    float f00, f04, f08, f0c;
    int   f10;
};
struct EmptyBubbleRaw { int f00, f04, f08, f0c, f10; };   // trivial-view for eastl::copy
struct CityBubble {                 // 0x50-byte element (Simulator bubble)
    int f00, f04, f08, f0c, f10, f14, f18, f1c;
    int f20, f24, f28, f2c, f30, f34, f38, f3c;
    int f40, f44, f48, f4c;
};
struct RunInfo {                    // EA::Text::Typesetter::RunInfo (0x10)
    float a, b, c, d;
};
struct RunInfoRaw { int a, b, c, d; };   // trivial-view for eastl::copy
template <class T> struct Vec3 { T* b; T* e; T* cap; void DoInsertValue(T* pos, T* value); };
extern void* operator new(unsigned int, const char*, int, int, const char*, int);   // 0x00F473A0
void __cdecl FUN_00c50ad0(void* first, void* last, void* dst);      // 0x00c50ad0 (copy_backward, 0x14 elems)
void* __cdecl FUN_00bda850(void* src, void* dst, void* out);        // 0x00bda850 (uninitialized_copy, 0x14 elems)
void* __cdecl FUN_00bdaa00(void* src, void* dst, void* out);        // 0x00bdaa00 (uninitialized_copy, 0x50 elems)
void* __cdecl FUN_00b115c0(void* src, void* dst, void* out);        // 0x00b115c0 (uninitialized_copy, 0x10 elems)
void __cdecl FUN_00edba80(void* first, void* last, void* dst);      // 0x00edba80 (copy_backward, RunInfo)
struct CityVec50 { char pad[4]; CityBubble* e; CityBubble* cap;
    CityBubble* CopyBack(CityBubble* dst, CityBubble* src); };
struct CityElem60 { char pad[0x60]; };
typedef void (__thiscall *CopyCtorFn)(void* self, const void* src);   // 0x00bda7d0, ret 4
struct Vec50 { CityBubble* b; CityBubble* e; CityBubble* cap;
    void DoInsertValue(CityBubble* pos, CityBubble* value); };
struct Vec10 { RunInfo* b; RunInfo* e; RunInfo* cap;
    void DoInsertValue(RunInfo* pos, RunInfo* value); };
struct Key3  { int a, b, c; };
struct CivVec { void** b; void** e; };
struct CivView {                         // SP::cCivilization field view
    char   pad000[0xb0];
    CivVec cities;                       // +0xb0 (vector of city pointers)
    char   pad0b8[0x298 - 0xb8];
    int    field298;                     // +0x298
    char   pad29c[0x4b0 - 0x29c];
    float  field4b0;                     // +0x4b0
};
struct CityObj {                         // SP::city field view (generic)
    char   pad000[0x32c];
    float  posX;                         // +0x32c
    float  posY;                         // +0x330
    float  posZ;                         // +0x334
    char   pad338[0x540 - 0x338];
    int    specialty;                    // +0x540
    char   pad544[0xb1c - 0x544];
    int    fieldb1c;                     // +0xb1c
    int    fieldb20;                     // +0xb20
};
struct CityKind {                        // result of FUN_00ca71d0
    void*  owner;                        // +0x00
    char   pad04[0x10 - 0x4];
    int    kind;                         // +0x10
};
struct SpaceObj {
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
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
};
struct RandomLCG { unsigned RandomUint32Uniform(unsigned n); };   // 0x00a68fb0
struct cTerrainEditor { void* GetCurrentTerrainSphere(); };       // 0x00f67d90
extern RandomLCG* gMathRandom;            // 0x01601760
bool   __cdecl FUN_00bef870(void* civ);                                  // 0x00bef870
bool   __cdecl Vector3_NotEqual(const float* a, const float* b);         // 0x0041dd30
int    __cdecl FUN_00c75420(void* sphere);                               // 0x00c75420
bool   __cdecl FUN_00c004c0(void* city, int which);                      // 0x00c004c0
CityKind* __cdecl FUN_00ca71d0(void* obj);                               // 0x00ca71d0
CivVec* __cdecl FUN_00bef6c0(void* civ);                                 // 0x00bef6c0
void*  __cdecl PlanetModel(void* pos);                                   // 0x00b3d350
int    __cdecl FUN_00b88590(void* planet);                               // 0x00b88590
float  __cdecl FUN_00b81470(void* planet, void* a, void* b);             // 0x00b81470
float  __cdecl FUN_00b7e4d0(void* planet);                               // 0x00b7e4d0
bool   __cdecl FUN_00bdb880(int which);                                  // 0x00bdb880
float  __cdecl FUN_00bf2170(void* civ, int specialty, int which);        // 0x00bf2170
int    __cdecl FUN_00bf2100(void* civ, int specialty);                   // 0x00bf2100
int    __cdecl FUN_00c9e6d0(int specialty, int which);                   // 0x00c9e6d0
int*   __cdecl FUN_00bf9770(void* civ, void* keyPos);                    // 0x00bf9770
int*   __cdecl FUN_00bddda0(void* city, int specialty, int which, Key3 key, int isTag); // 0x00bddda0
void*  __cdecl FUN_00cac000(void* obj, int a, int b);                    // 0x00cac000
// ---- items of slice s00bdde70 end

// ---- items of slice s00bdee20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator_new(uint32_t size);                              // 0x00f473a0
void  operator_delete2(void* p);                                // 0x00f47380
void* FUN_00bdaa90(void* src, void* dst, void* dstend);         // range move
void* FUN_00bdaa40(void* a, void* b, void* c, void* d, void* e); // range move
void* FUN_00ad8220(void* a, void* b, void* c);
void* FUN_00c8ee40(void* a, void* b, void* c);
void* FUN_00c8eeb0(void* a, void* b, void* c);
void* FUN_00bdc7b0(void* a, void* b, void* c, void* d, void* e);
void* RBTreeIncrement(void* node);                              // 0x00921580
void* memcpy(void* dst, const void* src, unsigned n);           // 0x011e0744
void* SP_PlanetModel();                                          // 0x00b3d350
void* FUN_00b86790(void* a, void* b);
void* FUN_00b7e360(void* a);
void  SP_cGameNounManager_RemoveNoun(void* self, void* noun);    // 0x00b225d0
void* SP_basic_string_sprintf(void* self, const char* fmt, ...); // 0x00472fe0
void* EA_IO_WriteUint32(void* a, void* b, void* c, void* d);     // 0x0093aa70
void* FUN_00afad30(void* self, void* a);                         // cActionCircle::FindSlot
void* FUN_00af9ff0(void* self, uint32_t slot);                   // cActionCircle::SlotAt
void* FUN_00fcc210(void* self);                                  // 0x00fcc210
void* FUN_00cd0550(void* a, void* b);
void* EA_Random_RandomUint32Uniform(void* self, uint32_t n);     // 0x00a68fb0
void* SP_cPlanetModel_BuildSurfaceOrientation2(void* self, void* a); // 0x00b7f250
struct ElevRecord {
    float mf0, mf1, mf2;            // +0x0 .. +0x8
    uint32_t mu0, mu1, mu2;         // +0xc .. +0x14
    uint8_t mb0;                    // +0x18
    uint8_t mPad[3];
};
struct ElevVec {
    ElevRecord* mpBegin;            // +0x0
    ElevRecord* mpEnd;              // +0x4
    ElevRecord* mpCapacity;         // +0x8
    uint32_t    mAllocator;         // +0xc
    ElevRecord* mpSentinel;         // +0x10

    void insert(ElevRecord* pos, const ElevRecord& value);
};
struct WordVec {                    // vector-ish with 3 pointers, fallback buffer
    uint32_t* mpBegin;              // +0x0
    uint32_t* mpEnd;                // +0x4
    uint32_t* mpCapacity;           // +0x8
    void insert(uint32_t* pos, uint32_t* first, uint32_t* last);
};
struct CElement_s00bd_ee20 {
    __declspec(noinline) CElement_s00bd_ee20* CopyAssignFrom(const CElement_s00bd_ee20& src);      // 0x00bdd470
    __declspec(noinline) CElement_s00bd_ee20* CopyConstructFrom(const CElement_s00bd_ee20& src);   // 0x00bdd380
};
struct Serializer {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void* Resolve();                        // +0x20
    virtual void v09();                             // +0x24
    virtual void v0a();                             // +0x28
    virtual void Send(void* obj);                   // +0x2c
};
struct SubSerializer {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void* GetIO();                          // +0x18
};
struct cGameDataT { void Write(void* stream); };                 // 0x00b18590
struct cSpatialObjectT { void Write(void* stream); };            // 0x00c88a90
struct Self00c005b0 { void Run(void* stream); };                 // 0x00c005b0 (ecx=this)
struct cGonzagoTimerT { void Write(void* stream); };             // 0x00b638d0
struct cVarListSerializerT {
    void ctor(void* owner, void* a, uint32_t b);                 // 0x00692f90
    void Serialize(void* stream);                                // 0x00692900
};
struct cRBTT { void Insert(void* key, void* val, void* v); };    // 0x007d0850
struct CityWrite {
    void Write(void* stream);
    void WGonzagoWrite0();
};
struct NounManagerT {
    void* GetPlayerCivilization();                              // 0x00b25fb0
};
struct RelationshipMgrT {
    float GetValue();                                           // 0x00d00d60 (ecx=mgr)
};
void* __stdcall FUN_00b3d2c0(void* civ, void* playerCiv, int one);  // 0x00b3d2c0
struct RelCity {
    void BuildRelationshipString(void* out);
};
struct EmptyBubble_s00bd_ee20 {
    float mCenter[3];               // +0x00, left uninitialized by the default constructor
    float mRadius;                  // +0x0c
    uint32_t mSourceID;              // +0x10
};
struct BubbleVec {
    EmptyBubble_s00bd_ee20* mpBegin;    // +0x0
    EmptyBubble_s00bd_ee20* mpEnd;      // +0x4
    EmptyBubble_s00bd_ee20* mpCapacity; // +0x8
    void push_back();
    void DoInsertValue(EmptyBubble_s00bd_ee20* pos, const EmptyBubble_s00bd_ee20& value); // 0x00bde910, thiscall, ret 8
};
void* FUN_00bda980(void* dst, void* last, void* src);
struct RefCounted {
    void** m_vtbl;
    void Release() { ((void (__thiscall*)(RefCounted*))m_vtbl[4 / 4])(this); }
};
struct RefElemVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    __declspec(noinline) void* erase_last(void* pos);
};
struct RefVecElem {
    RefCounted* m_p0;               // +0x0
    RefCounted* m_p4;               // +0x4
    uint32_t    m_u8;               // +0x8
};
struct RefVec2 {
    RefVecElem* mpBegin;            // +0x0
    RefVecElem* mpEnd;              // +0x4
    RefVecElem* mpCapacity;         // +0x8
    void insert(RefVecElem* pos, const RefVecElem& value);
};
void* FUN_00bdaae0(void* a, void* b, void* c);
void* FUN_00bda760(void* self, void* value);
struct IdVec {                          // vector<unsigned> at +0x1e0
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t  mAlloc;
    void DoInsertValue(uint32_t* pos, const uint32_t& value);   // 0x004558a0
    void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* slot = mpEnd++;
            if (slot) *slot = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
struct IdHost {                         // the object owning the +0x1e0 vector
    char mPad0[0x1d8];
    int mCount1d8;                      // +0x1d8
    int mPad1dc;
    IdVec mIds;                         // +0x1e0
    bool AddUniqueId(uint32_t id);
};
struct PairVec {
    void* mpBegin;                  // +0x0
    void* mpEnd;                    // +0x4
    void* mpCapacity;               // +0x8
    void reserve(uint32_t n);                       // 0x00ac4280 (Vec8::reserve)
    void eraseAt(void* first, void* last);          // 0x00d018d0
    void DoInsertValue(void* pos, void* value);     // 0x00b534c0
};
struct RBNode_s00bd_ee20 {
    RBNode_s00bd_ee20* mpParent;               // +0x0
    RBNode_s00bd_ee20* mpRight;                // +0x4
    RBNode_s00bd_ee20* mpLeft;                 // +0x8
    char pad[0x10 - 0xc];
    uint32_t mKey;                  // +0x10
    uint32_t mValue;                // +0x14
};
struct CityFlatten {
    void Flatten5a4(PairVec* dst);
    void Flatten5c0(PairVec* dst);
    void Flatten5dc(PairVec* dst);
};
struct CreatureHost {
    void RemoveByPointer(void* target);
    void* RemoveById(uint32_t id);
};
struct IdObject {
    void** m_vtbl;
    uint32_t GetId() { return ((uint32_t (__thiscall*)(IdObject*))m_vtbl[0x4c / 4])(this); }
};
struct false_type {};
void   FUN_00829110(void* out, void* first, void* last, void* dest, void* cur); // 0x00829110
void** FUN_006782c0(void** first, void** last, void** dest);    // 0x006782c0
struct LogReporterVec {
    void**   mpBegin;                                           // +0x00
    void**   mpEnd;                                             // +0x04
    void**   mpCapacity;                                        // +0x08
    uint32_t mAllocator;                                        // +0x0c
    void**   mpInline;                                          // +0x10

    void** DoAllocateAndCopy(int n, void** first, void** last); // 0x00b95280
    void   DoDestroyElements(void** first, void** last);        // 0x00b007f0
    void   do_assign(void** first, void** last, false_type tag);
};
// ---- items of slice s00bdee20 end

// ---- items of slice s00bdfd30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned kMaxEntries;                          // 0x01459c68 (= 14)
extern int g_156e880;                                         // 0x0156e880
struct Vec3_s00bd_fd30 {
    float x, y, z;
    Vec3_s00bd_fd30() {}
    Vec3_s00bd_fd30(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3_s00bd_fd30(const Vec3_s00bd_fd30& o) : x(o.x), y(o.y), z(o.z) {}
};
struct PointVec { Vec3_s00bd_fd30* mpBegin; Vec3_s00bd_fd30* mpEnd; Vec3_s00bd_fd30* mpCap; };
struct Combatant {
    int GetDamageState();                                   // 0x008e7f80
};
struct PosIface {
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
    virtual const Vec3_s00bd_fd30* GetPos();                           // +0x2c
};
struct Host {                                               // result of QueryInterface(0xe9cb8ba)
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual uint32_t GetType();                             // +0x20
    char pad04[0x34 - 4];
    PosIface pos;                                           // +0x34
    char pad38[0x120 - 0x38];
    Combatant cmb;                                          // +0x120
    char pad121[0x2c8 - 0x121];
    PointVec* GetPoints();                                  // 0x00bcc6c0 (this+0x2c8)
    PointVec* GetNormals();                                 // 0x00bcc6d0 (this+0x2dc)
};
struct Object {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual Host* QueryInterface(uint32_t type);            // +0x0c
};
struct Entry {                                              // 0x18 bytes
    uint8_t flag;
    char pad[0x17];
    Object* Get();                                          // 0x00fcc210 ([this+4])
};
struct Link {                                               // 0x50 bytes
    int a, b;
    float f0, f1, f2, f3, f4, f5;
    Vec3_s00bd_fd30 pa;                                                // +0x20
    Vec3_s00bd_fd30 pb;                                                // +0x2c
    Vec3_s00bd_fd30 da;                                                // +0x38
    Vec3_s00bd_fd30 db;                                                // +0x44
};
struct LinkVec {
    Link* mpBegin; Link* mpEnd; Link* mpCap;
    void erase(Link* first, Link* last);                    // 0x00bdeb10
    void DoInsertValue(Link* pos, Link& v);                 // 0x00bdeb80
    __forceinline void push_back()
    {
        if (mpEnd < mpCap) {
            mpEnd = mpEnd + 1;
        } else {
            Link tmp;
            DoInsertValue(mpEnd, tmp);
        }
    }
};
int __cdecl NearestIndex(PointVec* v, const Vec3_s00bd_fd30* p);       // 0x00ac08f0
struct MatrixOwner { char pad[0x274]; uint8_t mat[1]; };
struct cCombatLinks {
    char pad000[0x324];
    MatrixOwner* mMatrix;                                   // +0x324
    char pad328[0x43c - 0x328];
    Entry* mEntriesBegin;                                   // +0x43c
    Entry* mEntriesEnd;                                     // +0x440
    char pad444[0x684 - 0x444];
    LinkVec mLinks;                                         // +0x684
    void BuildLinks();                                      // 0x00be0020
};
static __forceinline Vec3_s00bd_fd30 Normalized(const Vec3_s00bd_fd30& d)
{
    float inv = (float)(1.0 / sqrt(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f));
    return Vec3_s00bd_fd30(inv * d.x, d.y * inv, d.z * inv);
}
struct GameTime { bool IsPlayer(void* p); };                  // 0x00ac8d60
GameTime* GameTimeQuery();                                    // 0x00b3d480
int GetPlayerEmpireID_s00bd_fd30();                                      // 0x01021090
void EndThisPlayer(void* self);                               // 0x00bdbf10
namespace EA {
namespace IO {
struct IStream_s00bd_fd30;
}
}
namespace EA {
namespace IO {
void ReadInt32(IStream_s00bd_fd30* s, void* out, int count, int flag);   // 0x0093a780
}
}
struct IStreamObj {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void* V18();                                      // +0x18
};
struct IStreamProvider {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void Close();                                     // +0x1c
    virtual IStreamObj* GetStream();                          // +0x20
};
void* operator_new_simulator(unsigned size);                  // 0x00f473a0
void MoveOverlap(int** first, int** last, int** dst);         // 0x00ae6880
void VectorEraseAutoRef(void* first, void* last);             // 0x00e25bd0
void FUN_00c3f2d0(void* p, int v);                            // 0x00c3f2d0
void FUN_00bfc720(void* p);                                   // 0x00bfc720
struct cGameNounManager_s00bd_fd30 { void RemoveNoun(void* n); };        // 0x00b225d0
cGameNounManager_s00bd_fd30* NounManager_s00bd_fd30();                              // 0x00b3d300
void SPVectorDoInsertPtr(void** pos, void* v);                // 0x00aea5d0
struct AnalysisInfo { int w[8]; };                   // 0x20 bytes
struct AnalysisVec {                                 // eastl::vector<AnalysisInfo, sp_vector_allocator>
    AnalysisInfo* mpBegin; AnalysisInfo* mpEnd; AnalysisInfo* mpCap;
    void insert(AnalysisInfo* pos, const AnalysisInfo& v);   // 0x00c06c30
    void erase(AnalysisInfo* first, AnalysisInfo* last);     // 0x00899420
    void resize(unsigned n);                                 // 0x00f281f0
    __forceinline void push_back(const AnalysisInfo& v) {
        if (mpEnd < mpCap) { *mpEnd = v; ++mpEnd; }
        else insert(mpEnd, v);
    }
};
struct GTClock {
    long long Now();                                 // 0x00b316c0
};
GTClock* GameTimeManager_s00bd_fd30();                          // 0x00b3d380
struct cAnalysisOwner {
    char pad0[0x7f8];
    AnalysisVec m7f8;                                // +0x7f8
    void AddAnalysis(const AnalysisInfo& a, long long delta);   // 0x00be06c0
};
struct EmptyBubble_s00bd_fd30 {
    float x, y, z, w; int id;
    EmptyBubble_s00bd_fd30() {}
    EmptyBubble_s00bd_fd30(float a, float b, float c, float d, int e) : x(a), y(b), z(c), w(d), id(e) {}
};
struct BubbleVec_s00bd_fd30 {                                  // eastl::vector<EmptyBubble, sp_vector_allocator>
    EmptyBubble_s00bd_fd30* mpBegin; EmptyBubble_s00bd_fd30* mpEnd; EmptyBubble_s00bd_fd30* mpCap;
    void DoInsertValue(EmptyBubble_s00bd_fd30* pos, const EmptyBubble_s00bd_fd30& v);   // 0x00bde910
    __forceinline void push_back(const EmptyBubble_s00bd_fd30& v) {
        if (mpEnd < mpCap) { *mpEnd = v; ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};
struct BobbleHost {
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
    virtual const Vec3_s00bd_fd30* GetPos();                    // +0x8c
};
struct cCommunity_s00bd_fd30 {
    char pad0[0x70];
    BubbleVec_s00bd_fd30 mBubbles;                              // +0x70  (begin,end,cap)
    char pad7c[0x2a4 - 0x7c];
    BubbleVec_s00bd_fd30 mBubbles2;                             // +0x2a4
    char pad2b0[0x320 - 0x2b0];
    BobbleHost* mHost;                               // +0x320
    char pad324[0x51c - 0x324];
    float m51c, m520, m524;                          // +0x51c,+0x520,+0x524
    void AddSpecialBubbles();                        // 0x00c01310
    void EmitBubbles();                              // 0x00bdfd30
    void EmitBubbleAt(const Vec3_s00bd_fd30* p, float w, int id);  // 0x00bdff50
    void EndThisPlayer();                            // 0x00bdbf10
};
struct AutoRefObj {
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
    virtual void v25();                                   // +0x64
};
struct RefVecElem_s00bd_fd30 { AutoRefObj* mpA; AutoRefObj* mpB; int pad; };   // 0xc (only +0,+4 written here)
struct RefVec2_s00bd_fd30 {
    RefVecElem_s00bd_fd30* mpBegin; RefVecElem_s00bd_fd30* mpEnd; RefVecElem_s00bd_fd30* mpCap;
    void insert(RefVecElem_s00bd_fd30* pos, const RefVecElem_s00bd_fd30& v);   // 0x00bdf480
    void AddDefault();                                   // 0x00be0730
};
struct MapNode {
    MapNode* mpLeft;      // +0
    MapNode* mpRight;     // +4
    MapNode* mpParent;    // +8   (header sentinel: the root lives here)
    int mPad;             // +0xc
    int mKey;             // +0x10
    char mVal[0x14];      // +0x14
};
struct IntMap {
    int mPad0;                                        // +0
    MapNode mHead;                                    // +4
    int* GetOrInsert(const int* key);                 // 0x00be0790
    void* DoInsert(int** out, void* where, int* kv, int extra);  // 0x00de6a60
};
struct cVarListSerializer {
    cVarListSerializer(void* a, const void* b, int c);               // 0x00692f90
    void Read(void* owner);                                          // 0x00693e10
};
struct PtrVec2 {
    int** mpBegin; int** mpEnd; int** mpCap;
};
struct FloatVec {                                    // 0x14 bytes: 3 pointers + allocator state
    float* mpBegin; float* mpEnd; float* mpCap;
    int mAllocState[2];
    void DoAllocate(unsigned n, const int* alloc);    // 0x004aa350 (sets begin/end/cap)
    FloatVec& operator=(const FloatVec& o);           // 0x0050d4e0
};
struct InfoRec {                                     // 0x20 bytes
    Vec3_s00bd_fd30 pos;
    FloatVec v;
    InfoRec(const InfoRec& o);
};
struct Spatial {
    void Clear();                                    // 0x00c8b2e0
};
struct SimData {
    char pad0[0x38];
    char m38[1];                                     // +0x38
    char pad39[0x100 - 0x39];
    Spatial m100;                                    // +0x100
    char pad104[0x1d8 - 0x104];
    int m1d8;                                        // +0x1d8
    int m1dc;                                        // +0x1dc
    int* m1e0;                                       // +0x1e0 vector begin
    int* m1e4;                                       // +0x1e4 vector end
    char pad1e8[0x1f4 - 0x1e8];
    int* m1f4;                                       // +0x1f4 vector begin
    int* m1f8;                                       // +0x1f8 vector end
    int* m1fc;                                       // +0x1fc vector cap
    char pad200[0x208 - 0x200];
    void* m208;                                      // +0x208
    void RemoveOwner();                              // 0x00be0f20
    bool AddOwner(int* p);                            // 0x00be0fc0
};
// ---- items of slice s00bdfd30 end

// ---- items of slice s00be10d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef          int        i32;
typedef          float      f32;
typedef unsigned __int64    u64_s00be_10d0;
typedef void* (__thiscall* tc0_t)(void*);
typedef void* (__thiscall* tc1_t)(void*, void*);
static inline void* vt0(void* p, int slot) { return ((tc0_t*)(*(void***)p))[slot](p); }
static inline void* vt1p(void* p, int slot, void* a) { return ((tc1_t*)(*(void***)p))[slot](p, a); }
static inline void  addref(void* p) { if (p) vt0(p, 0); }
static inline void  relref(void* p) { if (p) vt0(p, 1); }
void* SP_PendingObject();                                           // 0xb3d480 (-> [0x167eb3c])
void* FUN_00b25fb0();                                               // 0xb25fb0 nounMgr->GetPlayerCivilization
void* FUN_00b20c60(u32 id);                                         // 0xb20c60 nounMgr->CreateNoun
void  FUN_00c41c60(void* a, void* b, int c);                        // 0xc41c60
struct PendingObj { void ac8cd0(void* a, int b); };                 // 0xac8cd0
namespace SP {
struct cGameNounManager_s00be_10d0 {
    void* GetNoun(int id);              // 0xb25f40
    void* CreateNoun(u32 id);           // 0xb20c60
};
}
struct SubVObj { void* mpVtbl; };
typedef void* (__thiscall *MF0B)(void*);
typedef void  (__thiscall *MF0E)(void*, void*);
struct NounObj {
    char    pad00[0x34];
    SubVObj mSub34;
    void    FUN_00bd2310(void* arg);                                // 0xbd2310
};
struct cSPTimer_s00be_10d0 {
    char pad[0x1c];
    void Restart();                                                 // 0xbc3130
    u64_s00be_10d0  GetElapsedTime();                                          // 0xbc3190
};
struct HolderObj { char pad[0x18]; void* mpOwner; };
void* FUN_00b88590(void* model, const void* key);                   // 0xb88590 GetContinent
void  FUN_00be0730(void* refvec2);                                  // 0xbe0730
void* FUN_00be0790(void* tree, const void* key);                    // 0xbe0790
struct Ceeder { void ceed50(void* a, u32* out); };                  // 0xceed50
#define kCeeder ((Ceeder*)0x169c255)
void* FUN_00b8d420(void* p);                                        // 0xb8d420
void  FUN_00b86650(void* a, void* b);                               // 0xb86650
void  FUN_00b866f0(void* a, void* b);                               // 0xb866f0
void* FUN_00bef950(void* out);                                      // 0xbef950 (profile from key)
void  FUN_00e3c7c0(void* a, u32 b);                                 // 0xe3c7c0
void* FUN_00bd9480(void* self, void* out);                          // 0xbd9480
void  FUN_00bd2310(void* noun, void* self);                         // 0xbd2310
void  FUN_00bdbbb0(void* self);                                     // 0xbdbbb0
void* FUN_00e39fb0(void* tree, const void* key);                    // 0xe39fb0 rbtree<int>::find
void* FUN_00921580(void* node);                                     // 0x921580 RBTreeIncrement
void* FUN_00436ce0(const void* a, void* out);                       // 0x436ce0 Vector3_Normalize
char  FUN_0041dd30(const void* a, const void* b);                   // 0x41dd30 Vector3_NotEqual
int   FUN_00bd92d0(void* noun);                                     // 0xbd92d0
extern const f32 kTickThreshold;                                    // 0x169cb60
struct rbNodeBase {
    void* mpNodeRight;                  // +0x00
    void* mpNodeLeft;                   // +0x04
    void* mpNodeParent;                 // +0x08
    char  mColor;                       // +0x0c
    char  pad[3];
};
struct IntMapNode {
    rbNodeBase link;                    // +0x00
    i32 mKey;                           // +0x10
    i32 mValue;                         // +0x14
};
struct IntTreeMap {
    char       pad0[4];                 // +0x00
    rbNodeBase mAnchor;                 // +0x04
    int        mnSize;                  // +0x14
    char       pad18[4];
    int& operator[](const int& k);      // 0x00643a40
};
struct PtrVec {
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCapacity;                  // +0x08
    void   DoInsertPtr(void** position, void* const& value);     // 0xaea5d0
    void   erase(void** first, void** last);                     // 0xe25bd0
};
struct RefVec2Elem {
    void* p0;                           // +0x00
    void* p4;                           // +0x04
    i32   f8;                           // +0x08
};
struct RefVec2_s00be_10d0 {
    RefVec2Elem* mpBegin;               // +0x00
    RefVec2Elem* mpEnd;                 // +0x04
    RefVec2Elem* mpCapacity;            // +0x08
};
struct Vec3_s00be_10d0 { f32 x, y, z; };
extern const Vec3_s00be_10d0 kOrigin;                                          // 0x168bd70 (.70/.74/.78)
class cSPPlanetNoun {
public:
    char   pad00[0x6c];
    u8     mFlag6c;                     // +0x6c  dirty flag

    char   pad6d[0xb3];
    SubVObj mSub120;                    // +0x120 vtbl-bearing sub-object
    char   pad124[0xb4];

    i32    mnLogA;                      // +0x1d8
    i32    mnLogB;                      // +0x1dc
    void*  mpA1e0;                      // +0x1e0
    void*  mpA1e4;                      // +0x1e4
    char   pad1e8[0x0c];
    PtrVec mLogVec1f4;                  // +0x1f4 (erase target; begin@+0x1f4, end@+0x1f8)
    char   pad200[0x0c];
    f32    mf20c;                       // +0x20c
    f32    mf210;                       // +0x210
    i32    mn214;                       // +0x214

    char   pad218[0xf0];
    PtrVec mVec308;                     // +0x308
    char   pad314[0x18];
    Vec3_s00be_10d0   mPos32c;                     // +0x32c
    char   pad338[0x08];
    PtrVec mVec340;                     // +0x340
    char   pad34c[0x08];
    PtrVec mVec354;                     // +0x354
    char   pad360[0x1fc];
    RefVec2_s00be_10d0 mRefVec55c;                 // +0x55c
    char   pad568[0x08];

    IntTreeMap mTree570;                // +0x570 rbtree<int,pair<const int,string>> (anchor @ +0x574)
    char   pad58c[0x04];
    void*  mpLog590;                    // +0x590 ILogReporter*
    char   pad594[0x0c];
    IntTreeMap map1;                    // +0x5a0 (mnSize @ +0x5b4)
    IntTreeMap map2;                    // +0x5bc
    IntTreeMap map3;                    // +0x5d8
    char   pad5f4[0x04];
    cSPTimer_s00be_10d0 mTimer5f8;                 // +0x5f8
    char   pad614[0x38];
    i32    mn64c;                       // +0x64c

    void ResetLog();                                            // 0x00be10d0
    void SetLog(void* r);                                       // 0x00be1150
    void Tick1();                                               // 0x00be11f0
    int  Activate(cSPPlanetNoun* other, int flag);              // 0x00be1340
    void OnNoun(int id);                                        // 0x00be1820
    void* FUN_00bd92d0(void* noun);                             // 0xbd92d0
    void PushVec308(void* r);                                   // 0x00be1e80
    void PushVec340(void* r, int flag);                         // 0x00be1ef0
    void* MakeNoun();                                           // 0x00be1fb0
};
#define VGETID(p) ((int(__thiscall*)(void*))((void**)*(void***)(p))[0x4c / 4])((void*)(p))
// ---- items of slice s00be10d0 end

// ---- items of slice s00be4000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00bd1ab0();                 // 0xbd1ab0
extern "C" void  FUN_00b21340();                 // 0xb21340  cGameNounManager::GetGameDataVector
extern "C" void  FUN_00bf1780();                 // 0xbf1780
extern "C" void* __cdecl FUN_00b3d390(int*, void*, void*, int, int, int, int); // 0xb3d390 erase
extern "C" void  FUN_01050070();                 // 0x1050070 SP::cSPToolManager::UseToolStart
extern "C" void  FUN_00b25ca0();                 // 0xb25ca0  cGameNounManager::GetCivilizationList
extern "C" void* __cdecl FUN_00b3d2c0(int, int); // 0xb3d2c0  SP::RelationshipManager
extern "C" void  FUN_00d06240();                 // 0xd06240  cRelationshipManager::RecordEvent
extern "C" void* __cdecl FUN_00675250(int);      // 0x675250  AchievementsController
extern "C" void  FUN_00676710();                 // 0x676710  AwardAchievement
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
struct S {
  void  FUN_00be4a10(void* civ);                 // 0xbe4a10
  void  FUN_00be4b30(void* civ);                 // 0xbe4b30
  void  FUN_00be41b0();                          // 0xbe41b0
  void  FUN_00be4400();                          // 0xbe4400
  char  FUN_00be4000(int* param_2, char param_3); // 0xbe4000
};
// ---- items of slice s00be4000 end

// ---- items of slice s00be6310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float        DAT_0168c330;                      // +0x0168c330
extern const float        DAT_0168c334;                      // +0x0168c334
extern const float        DAT_0168c338;                      // +0x0168c338
extern const float        DAT_0168c33c;                      // +0x0168c33c
extern const float        DAT_0168c340;                      // +0x0168c340
extern const float        DAT_0168c344;                      // +0x0168c344
extern const float        DAT_0168c348;                      // +0x0168c348
extern const float        DAT_0168c34c;                      // +0x0168c34c
extern const float        DAT_0168c350;                      // +0x0168c350
extern const float        DAT_0168c354;                      // +0x0168c354
extern const float        DAT_0168c358;                      // +0x0168c358
extern const float        DAT_0168c35c;                      // +0x0168c35c
extern const float        DAT_0168bd70;                      // +0x0168bd70
extern const float        DAT_0168bd74;                      // +0x0168bd74
extern const float        DAT_0168bd78;                      // +0x0168bd78
extern const float        DAT_013f1cac;                      // +0x013f1cac  50.0f
extern const float        DAT_01473c70;                      // +0x01473c70  10.0f
extern const float        DAT_013eecd8;                      // +0x013eecd8  20.0f
extern const float DAT_0169c1e0;                              // +0x0169c1e0  per-building scale
extern const float DAT_01471064;                              // +0x01471064  0.5f
extern const float DAT_013eb1c0;                              // +0x013eb1c0  1.2f
extern const float DAT_01465544;                              // +0x01465544  500.0f
extern const float DAT_01470f1c;                              // +0x01470f1c  2.0f
void __cdecl EASTL_allocator_deallocate(void* p);            // 0x00f47380  operator delete[]
struct cCombatant_s00be_6310 {
    int mField00;
    int mField04;
    int mDamageState;                                        // +0x08
    int GetDamageState();                                    // 0x008e7f80  (mov eax,[ecx+8]; ret)
};
struct cFlagHolder {
    unsigned char mRaw000[0x8a];
    unsigned char mFlag8a;                                   // +0x8a
};
struct cRaidParticipant {
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
    virtual float GetWeight();                               // vtable +0x5c
    unsigned char mRaw004[0x120 - 0x04];
    cCombatant_s00be_6310    mCombatant120;                             // +0x120
};
struct cBuildingScore {
    virtual void d00();
    virtual void Release();                                  // vtable +0x04
    unsigned char mRaw004[0x588 - 0x04];
    cCombatant_s00be_6310    mCombatant588;                             // +0x588
    float Score();                                           // 0x00bd0110
};
struct cPointerVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    unsigned Size() const { return (unsigned)(mpEnd - mpBegin); }
    void DoInsertPtr(void** pos, void* const& value);         // 0x00aea5d0
};
struct cElem0c {
    int mField00;
    int mField04;
    int mField08;
};
struct cElem0cVector {
    cElem0c* mpBegin;
    cElem0c* mpEnd;
    cElem0c* mpCapacity;
};
struct cInlinePtrVector {
    void** mpBegin;                                          // +0x00
    void** mpEnd;                                            // +0x04
    void** mpCapacity;                                       // +0x08
    void** mUnused0c;                                        // +0x0c
    void** mpBuffer;                                         // +0x10
    void Reset(void** first, void** last);                   // 0x00e25bd0  eastl::vector::erase
    void Append(void** first, void** last, float f);         // 0x00bdf600
};
struct cActionCircle {
    unsigned char mRaw000[0x64];
    void RemoveAgent(void* agent);                           // 0x00afae50
    void LayoutConstruct();                                  // 0x00afba10
};
struct cSpatialObject_s00be_6310 {
    void* mpVtbl;                                            // +0x000  (cCity+0x120)
    unsigned char mRaw004[0xd0];
    void cSpatialObject_func80h();                           // 0x00c88510
    void FUN_00be6f60();                                     // 0x00be6f60
    cSpatialObject_s00be_6310();                                        // 0x00c89630
};
struct cCityPrefix {
    void* mpVtbl0;                                           // +0x000
    void* mpVtbl1;                                           // +0x004
    unsigned char mRaw008[0x2c];                             // +0x008..+0x033
    void* mpVtbl2;                                           // +0x034
    unsigned char mRaw038[0xe8];                             // +0x038..+0x11f
    cCityPrefix();                                           // 0x00c011c0
};
struct cInteractionTarget {
    void* mpVtbl;                                            // +0x000
    unsigned char mRaw004[0x14];                             // +0x004..+0x017
    void* mpVtbl2;                                           // +0x018
    cInteractionTarget();                                    // 0x00ac03d0
};
struct cTimer {
    unsigned char mRaw[0x20];
    void Construct();                                        // 0x00b63890
    void Start();                                            // 0x00bc30f0
};
struct cStr16 {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
};
struct cRbTree {
    int           mField00;                                  // +0x00  (never touched)
    void*         mpNodeLeft;                                // +0x04
    void*         mpNodeRight;                               // +0x08
    void*         mpNodeParent;                              // +0x0c
    union {
        unsigned int  mColorWord;                            // +0x10  (zeroed as a dword)
        struct {
            unsigned char mColor;                            // +0x10
            unsigned char mPad11[3];                         // +0x11
        };
    };
    unsigned int  mnSize;                                    // +0x14
};
struct cRefCounted;                                          // vtable below
struct cCultureTargetInfo {
    void*         mPtr00[8];                                 // +0x00..+0x1f
    unsigned char mFlag20;                                   // +0x20
    unsigned char mPad21[3];                                 // +0x21
    float         mF24;                                      // +0x24
    float         mF28;                                      // +0x28
    float         mF2c;                                      // +0x2c
    unsigned char mPad30[0x40];                              // +0x30..+0x6f
    cRefCounted*  mPtr70;                                    // +0x70
    unsigned char mFlag74;                                   // +0x74
    unsigned char mPad75[3];                                 // +0x75
    cRefCounted*  mPtr78;                                    // +0x78
    unsigned char mPad7c[4];                                 // +0x7c
};
struct cCultureTargetInfoVector {
    cCultureTargetInfo* mpBegin;                             // +0x00
    cCultureTargetInfo* mpEnd;                               // +0x04
    cCultureTargetInfo* mpCapacity;                          // +0x08
    void Resize(int count);                                  // 0x00be60a0
};
struct Mat3 {
    float m[9];
};
struct cEffectDesc {
    unsigned short mFlags;                                   // +0x00
    short          mCount;                                   // +0x02
    float          mF04;                                     // +0x04
    float          mF08;                                     // +0x08
    float          mF0c;                                     // +0x0c
    float          mF10;                                     // +0x10
    Mat3           mMatrix;                                  // +0x14
};
struct cEffect {
    virtual void d00();                                      // +0x00
    virtual void Release();                                  // +0x04
    virtual void SetVisible(int visible);                    // +0x08
    virtual void d03();                                      // +0x0c
    virtual void d04();                                      // +0x10
    virtual void d05();                                      // +0x14
    virtual void SetDescriptor(cEffectDesc* desc);           // +0x18
};
struct cEffectsManager {
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
    virtual char SpawnEffect(unsigned int id, int flags, cEffect** out);  // +0x2c
};
struct cNounSub70 {
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
    virtual float* GetPosition();                            // +0x2c
    virtual float* GetOrientation();                         // +0x30
virtual void d13();
virtual void d14();
virtual void d15();
    virtual void SetScale(float f);                          // +0x40
    void FUN_00c88530(float f);                              // 0x00c88530
};
struct cNoun_s00be_6310 {
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    virtual void SetVisible(int visible);                    // +0x08
    virtual cNoun_s00be_6310* Cast(unsigned int type);                  // +0x0c
    unsigned char mRaw010[0x60];                             // +0x10..+0x6f
    cNounSub70    mSub70;                                    // +0x70
};
struct cGameNounManager_s00be_6310 {
    cNoun_s00be_6310* CreateNoun(void* archetype);                      // 0x00b20c60
};
cGameNounManager_s00be_6310* NounManager_s00be_6310();                             // 0x00b3d300
cEffectsManager*  EffectsManager_s00be_6310();                          // 0x0067ddd0
struct cSimOrnament {
    void SetStyleModel(void* name, void* style);             // 0x00c6f770
};
struct cCityVtbl_s00be_6310 {
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
    virtual void* Vfn4c(void* p);                            // +0x4c
};
struct cDirectPropertyList {
    int GetIntProperty(unsigned int id) const;               // 0x006a2660
};
struct cRandomGlobal {
    unsigned int RandomUint32Uniform(unsigned int n);        // 0x00a68fb0
};
extern cDirectPropertyList* g_15fd918;                       // 0x015fd918  sAppProperties
extern cRandomGlobal      g_1601760_s00be_6310;                         // 0x01601760
struct cGlobalThing {
    void FUN_00ac8d40(void* p);                               // 0x00ac8d40  (ret 4)
};
cGlobalThing* FUN_00b3d480();                                 // 0x00b3d480  (mov eax,[0x167eb3c]; ret)
struct cRefCounted {
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
virtual void d31();
virtual void d32();
virtual void d33();
virtual void d34();
virtual void d35();
virtual void d36();
virtual void d37();
virtual void d38();
virtual void d39();
virtual void d40();
virtual void d41();
virtual void d42();
virtual void d43();
virtual void d44();
virtual void d45();
virtual void d46();
virtual void d47();
    virtual void Release();                                  // vtable +0xc0
};
struct cCity_s00be_6310 : cCityPrefix, cSpatialObject_s00be_6310 {
    cCity_s00be_6310();                                                  // 0x00be6310
    void  FUN_00be6900(char param2);                          // 0x00be6900
    float FUN_00be6d90();                                     // 0x00be6d90
    void  FUN_00be5180();                                     // 0x00be5180
    void  FUN_00be6f40();                                     // 0x00be6f40
    bool  SetDecoration(void* obj);                           // 0x00bd9660

    cInteractionTarget mInteraction;                          // +0x1f4
    cStr16           mName;                                   // +0x210
    unsigned char    mPad21c[4];                              // +0x21c
    float            mF220;                                   // +0x220
    int              mI224;                                   // +0x224
    int              mI228;                                   // +0x228
    unsigned char    mPad22c[4];                              // +0x22c
    cTimer           mTimer230;                               // +0x230
    cTimer           mTimer250;                               // +0x250
    cTimer           mTimer270;                               // +0x270
    unsigned char    mPad290[8];                              // +0x290
    int              mI298;                                   // +0x298
    int              mI29c;                                   // +0x29c
    unsigned char    mB2a0;                                   // +0x2a0
    unsigned char    mPad2a1[3];                              // +0x2a1
    cPointerVector   mVec2a4;                                 // +0x2a4
    unsigned char    mPad2b0[8];                              // +0x2b0
    cPointerVector   mVec2b8;                                 // +0x2b8
    unsigned char    mPad2c4[8];                              // +0x2c4
    int              mI2cc;                                   // +0x2cc
    int              mI2d0;                                   // +0x2d0
    unsigned char    mPad2d4[12];                             // +0x2d4
    unsigned char    mB2e0[7];                                // +0x2e0..+0x2e6
    unsigned char    mPad2e7[1];                              // +0x2e7
    int              mI2e8;                                   // +0x2e8
    int              mI2ec;                                   // +0x2ec
    int              mI2f0;                                   // +0x2f0
    int              mI2f4;                                   // +0x2f4
    int              mI2f8;                                   // +0x2f8
    unsigned char    mB2fc;                                   // +0x2fc
    unsigned char    mPad2fd[3];                              // +0x2fd
    float            mF300;                                   // +0x300
    float            mF304;                                   // +0x304
    cPointerVector   mVec308;                                 // +0x308  mCivicObjects
    unsigned char    mPad314[12];                             // +0x314
    int              mI320;                                   // +0x320  mpCityHall
    int              mI324;                                   // +0x324  mpCityWalls
    int              mI328;                                   // +0x328  mpCityTerritory
    float            mF32c;                                   // +0x32c
    float            mF330;                                   // +0x330
    float            mF334;                                   // +0x334
    float            mF338;                                   // +0x338  mFrameRate
    unsigned char    mPad33c[4];                              // +0x33c
    cPointerVector   mVec340;                                 // +0x340  mBuildings
    unsigned char    mPad34c[8];                              // +0x34c
    cInlinePtrVector mVec354;                                 // +0x354  mTurrets
    unsigned char    mPad368[4];                              // +0x368
    void*            mInlineBuf36c[32];                       // +0x36c..+0x3eb
    cActionCircle    mAction3ec;                              // +0x3ec  mBuildingsLayout
    cActionCircle    mAction450;                              // +0x450
    cActionCircle    mAction4b4;                              // +0x4b4
    unsigned char    mFlag518;                                // +0x518
    unsigned char    mB519;                                   // +0x519
    unsigned char    mPad51a[14];                             // +0x51a..+0x527
    cElem0cVector    mVec528;                                 // +0x528
    unsigned char    mPad534[8];                              // +0x534
    float            mF53c;                                   // +0x53c
    int              mI540;                                   // +0x540
    int              mI544;                                   // +0x544
    cPointerVector   mVec548;                                 // +0x548
    unsigned char    mPad554[8];                              // +0x554
    cPointerVector   mVec55c;                                 // +0x55c
    unsigned char    mPad568[8];                              // +0x568
    cRbTree          mRb570;                                  // +0x570
    unsigned char    mPad588[4];                              // +0x588
    unsigned char    mB58c;                                   // +0x58c
    unsigned char    mPad58d[3];                              // +0x58d
    cFlagHolder*     mPtr590;                                 // +0x590
    int              mI594;                                   // +0x594
    float            mF598;                                   // +0x598
    int              mI59c;                                   // +0x59c
    cRbTree          mRb5a0;                                  // +0x5a0
    unsigned char    mPad5b8[4];                              // +0x5b8
    cRbTree          mRb5bc;                                  // +0x5bc
    unsigned char    mPad5d4[4];                              // +0x5d4
    cRbTree          mRb5d8;                                  // +0x5d8
    unsigned char    mPad5f0[8];                              // +0x5f0
    cTimer           mTimer5f8;                               // +0x5f8
    cCultureTargetInfoVector mCultureTargetInfo;              // +0x618
    unsigned char    mPad624[8];                              // +0x624
    cPointerVector   mVec62c;                                 // +0x62c
    unsigned char    mPad638[0x10];                           // +0x638..+0x647
    unsigned char    mB648;                                   // +0x648
    unsigned char    mPad649[3];                              // +0x649
    int              mI64c;                                   // +0x64c
    float            mF650;                                   // +0x650
    int              mI654;                                   // +0x654
    int              mI658;                                   // +0x658
    int              mI65c;                                   // +0x65c
    int              mI660;                                   // +0x660
    int              mI664;                                   // +0x664
    int              mI668;                                   // +0x668
    int              mI66c;                                   // +0x66c
    int              mI670;                                   // +0x670
    int              mI674;                                   // +0x674
    int              mI678;                                   // +0x678
    int              mI67c;                                   // +0x67c
    int              mI680;                                   // +0x680
    cPointerVector   mVec684;                                 // +0x684
    unsigned char    mPad690[8];                              // +0x690
    unsigned char    mB698;                                   // +0x698
    unsigned char    mPad699[7];                              // +0x699..+0x69f
    cTimer           mTimer6a0;                               // +0x6a0
    unsigned char    mB6c0;                                   // +0x6c0
    unsigned char    mPad6c1[7];                              // +0x6c1
    cTimer           mTimer6c8;                               // +0x6c8
    cTimer           mTimer6e8;                               // +0x6e8
    cTimer           mTimer708;                               // +0x708
    cTimer           mTimer728;                               // +0x728
    float            mF748;                                   // +0x748
    int              mI74c;                                   // +0x74c
    float            mF750;                                   // +0x750
    int              mI754;                                   // +0x754
    float            mF758;                                   // +0x758
    int              mI75c;                                   // +0x75c
    unsigned char    mB760;                                   // +0x760
    unsigned char    mB761;                                   // +0x761
    unsigned char    mB762;                                   // +0x762
    unsigned char    mPad763[1];                              // +0x763
    int              mI764;                                   // +0x764
    int              mI768;                                   // +0x768
    unsigned char    mPad76c[4];                              // +0x76c
    cTimer           mTimer770;                               // +0x770
    cTimer           mTimer790;                               // +0x790
    unsigned char    mPad7b0[8];                              // +0x7b0
    cRbTree          mRb7b8;                                  // +0x7b8
    unsigned char    mPad7d0[4];                              // +0x7d0
    int              mI7d4;                                   // +0x7d4
    unsigned char    mPad7d8[0x18];                           // +0x7d8..+0x7ef
    int              mI7f0;                                   // +0x7f0
    int              mI7f4;                                   // +0x7f4
    int              mI7f8;                                   // +0x7f8
    int              mI7fc;                                   // +0x7fc
    int              mI800;                                   // +0x800
    unsigned char    mPad804[8];                              // +0x804
    unsigned char    mB80c;                                   // +0x80c
    unsigned char    mPad80d[3];                              // +0x80d
    int              mI810;                                   // +0x810
};
// ---- items of slice s00be6310 end

// ---- items of slice s00be6f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char NounNameB[];
extern const char NounNameC[];
extern char kSimulatorTag[];                         // 0x013f09b4 "Simulator"
struct Vec3_s00be_6f90 { float x, y, z; Vec3_s00be_6f90() {} Vec3_s00be_6f90(const Vec3_s00be_6f90& o) : x(o.x), y(o.y), z(o.z) {} };
struct Key  { u32 a, b, c; Key() {} Key(const Key& o) : a(o.a), b(o.b), c(o.c) {} };
struct RefObj { virtual void AddRef(); virtual void Release(); };
template <class T> struct AutoRef {
    T* p;
    AutoRef() : p(0) {}
    ~AutoRef() { if (p) p->Release(); }
    T** __thiscall AsPPTypeParam();      // 0xa16f40 (declared only: stays an out-of-line call)
};
struct PropList : RefObj {};
struct Fx : RefObj {
    virtual void Start(int);                         // 0x08
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void SetTransform(const struct XformMsg_s00be_6f90* m);   // 0x18
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
    virtual void SetParam(int which, const void* v, int n);   // 0x44
};
struct XformMsg_s00be_6f90 {                                    // 0x38 bytes
    u16  flags, count;
    Vec3_s00be_6f90 pos;
    u32  pad10;
    Mat3 mat;
    XformMsg_s00be_6f90();                                      // 0x434040
    void __thiscall SetPosition(const Vec3_s00be_6f90* p);      // 0x571d40
};
struct PropMgr {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual void s10();
    virtual bool Get(u32 owner, u32 id, PropList** out);         // 0x2c
};
struct EffMgr {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual void s10();
    virtual bool Create(u32 id, int flags, Fx** out);            // 0x2c
};
PropMgr* __cdecl PropertyManager();                  // 0x67de30
EffMgr*  __cdecl EffectsManager_s00be_6f90();                   // 0x67ddd0
bool     __cdecl GetPropertyAsUint32(PropList* l, u32 key, u32* out);   // 0x4af210
Mat3*    __cdecl Matrix3A(Mat3* out, const void* q); // 0x4a9b40
Mat3*    __cdecl Matrix3FromQuaternion(Mat3* out, const void* q);       // 0x59c190
struct Obj120 {                                      // this - 0xec
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual void s10();
    virtual Vec3_s00be_6f90* GetPosition();                     // 0x2c
    virtual void* GetOrientation();                  // 0x30
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
    virtual bool IsReady();                          // 0x58
};
struct Sub { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
    virtual u32* Flags();                            // 0xac
};
struct Obj118 {                                      // this[0x118]
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
    virtual u32 GetB();                              // 0x64
    virtual void s26();
    virtual u32 GetA();                              // 0x6c
    char pad[0x34 - 4];
};
struct Obj118S : Obj118 { Sub sub; };
struct Node {
    u32   __thiscall Type();                         // 0xfc7e50
    void* __thiscall GetAllocator();                 // 0x7f54d0
};
u32 __cdecl AllocKey(void* alloc, u32 type);         // 0xc9e6d0
struct ModelHolder { char pad[0xc4]; Vec3_s00be_6f90 pos; Key* __thiscall GetModelTypeKey(u32 x); };  // 0xbf9770
struct Q {
    void __thiscall A(Node* n);                      // 0xa110b0
    void __thiscall B(u32 v);                        // 0xc9eae0
};
struct Vec3f { float x, y, z; };
struct Ctx {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
    virtual Vec3f* GetPosition();                    // +0x2c
virtual void s12();
virtual void s13();
    virtual void Fn38(void* v);                      // +0x38
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual Vec3f* Fn5C(Vec3f* out);                 // +0x5c
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
    virtual Ctx* FnB8(u32 key);                      // +0xb8
    virtual void s47();
    virtual void FnC0();                             // +0xc0
    void FnBD0000();                                 // 0x00bd0000
    bool __thiscall CanOccupy(const Vec3f* pos);     // 0x00c9e940 (ret 4)
};
struct Thing2F0 {
    void Fn(void* owner, u32 v);                     // 0x00ff2810 (ret 8)
};
struct Thing320 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
    virtual u32 Fn8C();                              // +0x8c
    char pad04[0x34 - 4];
    Ctx ctx;                                         // +0x34
};
struct Thing324 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
    virtual void Fn60(u32 v);                        // +0x60
    char pad04[0x34 - 4];
    Ctx ctx;                                         // +0x34
    char pad38[0x108 - 0x38];
    u8  f108;                                        // +0x108
    char pad109[0x25c - 0x109];
    float f25c;                                      // +0x25c
    char pad260[0x34c - 0x260];
    u32 f34c;                                        // +0x34c
};
struct PlanetRec { char pad[0x13c]; u32 f13c; };
struct Thing590 {
    void Fn(void* owner);                            // 0x00bf2660 (ret 4)
};
PlanetRec* __cdecl Fn1021260();                      // 0x01021260
u32 __cdecl FnBebc90(u32 a, u32 b);                  // 0x00bebc90
struct City {
    char pad[0x29c];
    u32  f29c;
    char pad2[0x2f0 - 0x2a0];
    Thing2F0* f2f0;                          // +0x2f0
    char pad2f4[0x320 - 0x2f4];
    Thing320* f320;                          // +0x320
    Thing324* f324;                          // +0x324
    char pad328[0x354 - 0x328];
    Ctx** f354;                              // +0x354 (vector begin)
    Ctx** f358;                              // +0x358 (vector end)
    char pad35c[0x44c - 0x35c];
    Q*   dummy;
    char pad450[0x540 - 0x450];
    u32  f540;                               // +0x540
    char pad544[0x590 - 0x544];
    Thing590* f590;                          // +0x590
    char pad594[0x761 - 0x594];
    u8   f761;                               // +0x761
    Q* __thiscall AddThing(u32 a, u32 type, Key k, int z);   // 0xbddda0
    void __thiscall F73d0(u32 a, u8 b);             // 0xbe73d0
    u32  __thiscall OverwriteNounsFromNounManager(u32 id);   // 0xbe7370
    u32  __thiscall Fn53b0(const char* name, u32 id);        // 0xbe53b0
    void __thiscall FnBDaf50();                     // 0x00bdaf50
    void __thiscall FnBD9710();                     // 0x00bd9710
    void __thiscall FnBDbaa0();                     // 0x00bdbaa0
    void __thiscall FnBDaea0();                     // 0x00bdaea0
    void __thiscall FnBD88c0();                     // 0x00bd88c0
    void __thiscall Fn6f90();                       // 0x00be6f90
    void __thiscall FnBe5180();                     // 0xbe5180
    void __thiscall FnBe5dd0();                     // 0xbe5dd0
};
struct Civ { char pad[0x44c]; City* city; };
struct NounMgr { Civ* __thiscall GetPlayerCivilization(); };    // 0xb25fb0
NounMgr* __cdecl NounManager_s00be_6f90();                      // 0xb3d300
struct TimeMgr { void __thiscall DecPauseGate(u32 g); };        // 0xb32250
TimeMgr* __cdecl GameTimeManager_s00be_6f90();                  // 0xb3d380
struct CivStrategy {
    void __thiscall A();                             // 0xcfa120
    bool __thiscall CanBuildSeaVehicles();           // 0xcf75d0
    void __thiscall B();                             // 0xcf8e00
    void __thiscall C();                             // 0xcf7520
};
CivStrategy* __cdecl CivModeStrategyGet();           // 0xcf74c0
void* __cdecl GetActivePlanetRecord();               // 0x10212a0
void  __cdecl PlanetHook(City* c, u32 a, void* rec); // 0xbe2440
struct Msg {
    u32 pad0, pad4;
    u32 data;        // +8
    u32 padc;
    Node* f10;
    u32 pad14;
    u32 f18;
};
static __forceinline void StartFx(Obj120* o, Fx* fx, const Vec3_s00be_6f90* pos)
{
    XformMsg_s00be_6f90 m;
    m.SetPosition(o->GetPosition());
    Mat3 tmp;
    m.mat = *Matrix3A(&tmp, o->GetOrientation());
    m.flags |= 2;
    m.count++;
    fx->SetTransform(&m);
    fx->SetParam(5, pos, 3);
    fx->Start(0);
}
struct CityListener {
    char pad0[0xe4];
    u32  fE4;
    char pad1[0x118 - 0xe8];
    Obj118S* f118;
    char pad2[0x334 - 0x11c];
    u32  f334;
    char pad3[0x384 - 0x338];
    ModelHolder* f384;

    bool __thiscall HandleMessage(u32 id, Msg* msg);        // 0xbe7470
};
struct FloatVec_s00be_6f90 {                                    // 0x14 bytes
    float* mpBegin; float* mpEnd; float* mpCap;
    int mAllocState[2];
    FloatVec_s00be_6f90& operator=(const FloatVec_s00be_6f90& o);          // 0x0050d4e0
};
struct InfoRec_s00be_6f90 {                                     // 0x20 bytes
    Vec3_s00be_6f90 pos;
    FloatVec_s00be_6f90 v;
    InfoRec_s00be_6f90(const InfoRec_s00be_6f90& o);                       // 0x00be0d70
};
InfoRec_s00be_6f90* __cdecl CopyInfoRecs(InfoRec_s00be_6f90* first, InfoRec_s00be_6f90* last, InfoRec_s00be_6f90* dst);     // 0x00be0dd0
InfoRec_s00be_6f90* __cdecl CopyInfoRecsBwd(InfoRec_s00be_6f90* first, InfoRec_s00be_6f90* last, InfoRec_s00be_6f90* dst);  // 0x00be0ed0
void* __cdecl MoveInfoRecs(InfoRec_s00be_6f90* first, InfoRec_s00be_6f90* last, InfoRec_s00be_6f90* dst);        // 0x00bda890
void* __cdecl EAAllocate(u32 n, const char* tag, int a, int b, int file, int line);  // 0x00f473a0
void  __cdecl EFree(void* p);                                                    // 0x00f47380
extern char kEastlFile_s00be_6f90[];                            // 0x013ebb38 "...EASTL/allocator.h"
struct InfoRecVec {
    InfoRec_s00be_6f90* mpBegin;                                // +0
    InfoRec_s00be_6f90* mpEnd;                                  // +4
    InfoRec_s00be_6f90* mpCap;                                  // +8
    void __thiscall Insert(InfoRec_s00be_6f90* pos, InfoRec_s00be_6f90* value);   // 0x00be7aa0
};
struct CtxVec { Ctx** mpBegin; Ctx** mpEnd; Ctx** mpCap; };       // {begin,end,cap}
struct SlotVec { u32* mpBegin; u32* mpEnd; u32* mpCap; };
class cActionCircle_s00be_6f90 {
 public:
    class tSlot {
     public:
        bool mOccupied;                              // +0x0
        char _pad0[3];
        void* mpReserving;                           // +0x4
        u32   mReservingId;                          // +0x8
        Vec3f mPos;                                  // +0xc
        void __thiscall Reserve(Ctx* noun);          // 0x00afa030
    };
    struct RawVec { void* b; void* e; void* c; int a[2]; };
    Vec3f mFacing;                                   // +0x0
    float mRadius;                                   // +0xc
    float mSlotRadius;                               // +0x10
    Vec3f mCenter;                                   // +0x14
    float mAltitude;                                 // +0x20
    int   mPacking;                                  // +0x24
    bool  mbRelative;                                // +0x28
    char  _pad28[3];
    float mOrientation[4];                           // +0x2c
    RawVec mAgents;                                  // +0x3c
    RawVec mSlots;                                   // +0x50

    cActionCircle_s00be_6f90();                                 // 0x00afba10
    ~cActionCircle_s00be_6f90();                                // 0x00afbad0
    void __thiscall SetAtCenter(const Vec3f* center, float radius,
                                const Vec3f* facing, float altitude);   // 0x00af9cf0
    tSlot* __thiscall SlotAt(u32 index);             // 0x00af9ff0
    void __thiscall FnAfef10(int mode, float v);     // 0x00afef10
    void __thiscall FnAfeff0(const Vec3f* p, SlotVec* out);  // 0x00afeff0
};
struct AgentMgr {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
    virtual void __thiscall FindAgents(const Vec3f* center, float radius,
                                       CtxVec* out, int a, int b, int c);   // +0x48
};
AgentMgr* __cdecl FnB3d240();                        // 0x00b3d240
struct Callback { void __thiscall FnAc8d40(); };     // 0x00ac8d40
Callback* __stdcall FnB3d480(City* c);               // 0x00b3d480 (ret 4)
struct SimSingleton {                                // 0xc8 bytes
    char pad0[0xa8];
    u8   f0a8;                                       // +0xa8
    SimSingleton();                                  // 0x00ae5c30
    static SimSingleton* Create(void* mem) { return new (mem) SimSingleton(); }
};
extern char gAppNameTag_s00be_6f90[];                           // 0x01654c05
extern SimSingleton* gSimSingleton;                  // 0x0167a60c
void  __cdecl FUN_00cac360(float x, float y, float z, float r);  // 0x00cac360
// ---- items of slice s00be6f90 end

// ---- items of slice s00be9850 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char DAT_01654c05;                   // 0x01654c05
struct IntTreeMap_s00be_9850 {                     // sizeof 0x1c
    char       pad0[4];                 // +0x00
    rbNodeBase mAnchor;                 // +0x04
    int        mnSize;                  // +0x14
    char       pad18[4];                // +0x18
    int& operator[](const int& k);          // 0x00643a40
    void DoNukeSubtree(void* pNode);        // 0x009a9600
    void reset() {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear() { DoNukeSubtree(mAnchor.mpNodeParent); reset(); }
};
struct cCivilization_s00be_9850 {
    float GetMoney();                       // 0x00bef6d0
    void  SpendMoney(float amount);         // 0x00bef710
};
struct Avatar {
    void FUN00ffa900(void* a, int b);       // 0x00ffa900
};
struct cGameNounManager_s00be_9850 {
    void*   GetPlayerCivilization();        // 0x00b25fb0
    void*   FUN00b25f40(int key);           // 0x00b25f40
    Avatar* GetAvatar();                    // 0x00b1fdb0
};
cGameNounManager_s00be_9850* GetNounManager();         // 0x00b3d300
cGameNounManager_s00be_9850* SpaceGameGet();           // 0x01002bd0
int   GetPlayerEmpireID_s00be_9850();                  // 0x01021090
struct cCivModeStrategy_s00be_9850 {
    void FUN00cf9040(void* a, unsigned b, unsigned c, void* d);   // 0x00cf9040
};
cCivModeStrategy_s00be_9850* GetCivModeStrategy();     // 0x00cf74c0
struct RandomLCG_s00be_9850 {
    double RandomDoubleUniform();           // 0x009360d0
};
extern RandomLCG_s00be_9850 _sMathRandom;              // 0x01601760
struct Obj {
    char  pad0[0x38];
    int   f38;                              // +0x38
    float f3c;                              // +0x3c
    char  pad1[0x184 - 0x40];
    void* f184;                             // +0x184
    char  pad2[0x194 - 0x188];
    int   f194;                             // +0x194
    float FUN00b7e0a0();                    // 0x00b7e0a0
    int   FUN00a1ad10();                    // 0x00a1ad10
    void  FUN00ff03b0(int v);               // 0x00ff03b0
    void  FUN00ff03c0(float v);             // 0x00ff03c0
    int   FUN00b8dab0();                    // 0x00b8dab0
    void* FUN00b8de30();                    // 0x00b8de30
};
float FUN_00bd9a80(Obj* o);                 // 0x00bd9a80 (cdecl, returns float)
void  FUN_00c8d060(void* p);                // 0x00c8d060 (cdecl)
class Sim {
public:
    char       pad0[0x98];
    int        f98;                         // +0x98
    int        f9c;                         // +0x9c
    char       pad1[0x120 - 0xa0];
    void*      vptr120;                     // +0x120
    char       pad2[0x320 - 0x124];
    void*      p320;                        // +0x320
    char       pad3[0x590 - 0x324];
    void*      p590;                        // +0x590
    char       pad4[0x5a0 - 0x594];
    IntTreeMap_s00be_9850 map1;                        // +0x5a0
    IntTreeMap_s00be_9850 map2;                        // +0x5bc
    IntTreeMap_s00be_9850 map3;                        // +0x5d8
    char       pad5[0x64c - 0x5f4];
    int        f64c;                        // +0x64c
    char       pad6[0x748 - 0x650];
    float      f748;                        // +0x748
    int        f74c;                        // +0x74c

    void  sub_be9850(int a1, float a2);             // 0x00be9850
    void  sub_be9980(int a1);                       // 0x00be9980
    void  sub_be9cb0(int a1, int a2, int a3, int a4);// 0x00be9cb0
    float FUN00be9250(int a1);                      // 0x00be9250
    void  sub_be92e0(int, int, int, int, int);      // 0x00be92e0
    void  sub_bd9a00(void*);                        // 0x00bd9a00
    void  FUN00bd7d10(int iv, float v);             // 0x00bd7d10
};
#define VCALL(p,slot) ((void**)*(void***)(p))[(slot) / 4]
#define V120M3(p,slot,a,b,c) ((void*(__thiscall*)(void*,int,int,int))VCALL((char*)(p) + 0x120, slot))((void*)((char*)(p) + 0x120), (a), (b), (c))
#define V120M1(p,slot,a)     ((void*(__thiscall*)(void*,int))VCALL((char*)(p) + 0x120, slot))((void*)((char*)(p) + 0x120), (a))
// ---- items of slice s00be9850 end

// ---- items of slice s00bea930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __cdecl S_b3d380();                // 0x00b3d380
extern char DAT_01654c04;                       // 0x01654c04
extern char DAT_0168c398;                       // 0x0168c398
extern int DAT_0169cbe0;                        // 0x0169cbe0
extern void FUN_00cd7d10();                     // 0x00cd7d10
extern void FUN_00d3d420();                     // 0x00d3d420
extern void FUN_00acdff0();                     // 0x00acdff0
extern void FUN_00b1e500();                     // 0x00b1e500
struct IntTreeMap_s00be_a930 {                     // sizeof 0x1c
    char       pad0[4];                 // +0x00
    rbNodeBase mAnchor;                 // +0x04
    int        mnSize;                  // +0x14
    char       pad18[4];                // +0x18
    int* Find(const int* key, int* out);    // 0x00e5c780  (thiscall on the map)
    int& operator[](const int& k);          // 0x00643a40
    void DoNukeSubtree(void* pNode);        // 0x009a9600
    void reset() {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear() { DoNukeSubtree(mAnchor.mpNodeParent); reset(); }
};
struct Clock { unsigned __int64 getTime(); };   // 0x00b316c0
struct cSPTimer_s00be_a930 {                               // 0x20 bytes (embedded in Slot80 at +0x30/+0x50)
    char pad[0x20];
    bool             FUN_feba90();              // 0x00feba90
    unsigned __int64 FUN_bc3190();              // 0x00bc3190
    void             FUN_bc30f0();              // 0x00bc30f0
    void             FUN_bc3130();              // 0x00bc3130
};
struct cCivModeStrategy_s00be_a930 { void PostFeedback(void*, unsigned, unsigned, void*, int, int, int); };
cCivModeStrategy_s00be_a930* GetCivModeStrategy_s00be_a930();         // 0x00cf74c0
class Veh;
struct GameVec {                                 // returned by cGameNounManager::GetGameDataVector
    int  pad0;                                  // +0x00
    Veh** begin;                                // +0x04
    Veh** end;                                  // +0x08
};
struct cGameNounManager_s00be_a930 {
    void* GetPlayerCivilization();              // 0x00b25fb0
    void* FUN00b25f40(int key);                 // 0x00b25f40
    GameVec* GetGameDataVector(void*, void*, void*, void*, void*);  // 0x00b21340
};
cGameNounManager_s00be_a930* GetNounManager_s00be_a930();             // 0x00b3d300
class Veh {
public:
    char  pad0[0x1d8];
    int   f1d8;                                 // +0x1d8
    int   f1dc;                                 // +0x1dc
    char  pad1[0x20c - 0x1e0];
    float f20c;                                 // +0x20c
    float f210;                                 // +0x210
    int   f214;                                 // +0x214
    char  pad2[0x762 - 0x218];
    char  f762;                                 // +0x762

    void sub_be9cb0(int, int, int, int);         // 0x00be9cb0
    unsigned int FUN_00bd85c0(float*, int*);    // 0x00bd85c0
    void FUN_00ca8120(int);                     // 0x00ca8120
};
struct Elem { int type; int _4; unsigned __int64 time; float f; int _14; int v; int _1c; };
struct Slot80 {
    int      w[9];                              // +0x00 .. +0x20
    float    f24;                               // +0x24 q
    float    f28;                               // +0x28 l30
    float    f2c;                               // +0x2c 1 - (q + l30)
    cSPTimer_s00be_a930 t30;                               // +0x30
    cSPTimer_s00be_a930 t50;                               // +0x50
    int      obj70;                             // +0x70
    char     pad74[0xc];                        // +0x74
};
struct Matrix33T { int v[9]; };
Matrix33T& Matrix3FromQuaternion(Matrix33T& dst, const void* q);   // 0x0059c190
struct XformMsg_s00be_a930 {
    unsigned short flags;                       // +0x00
    short          count;                       // +0x02
    int            pos[3];                      // +0x04 (float triple, copied as dwords)
    int            unk10;                       // +0x10
    Matrix33T      mat;                         // +0x14
    void ctor();                                // 0x00434040
};
struct InteractCtx {
    void FUN_00cee8e0(float, int, float*);        // 0x00cee8e0
    void FUN_00cee920(void*, int, float, int, float*);  // 0x00cee920
    void FUN_00cee9c0(float, float, float*);      // 0x00cee9c0
    void FUN_00ceea20(float, float*, float*);     // 0x00ceea20
    void FUN_00ceedb0(float, int*);               // 0x00ceedb0
    void FUN_00ceea90(float, float*);             // 0x00ceea90
};
struct cPlanetModel_s00be_a930 {
    char  pad0[0x24];
    float FUN_00b7e4d0();                       // 0x00b7e4d0
};
cPlanetModel_s00be_a930* __cdecl S_b3d350();               // 0x00b3d350 (SP::PlanetModel)
struct Noun590 {                                // object at Sim::p590
    char  pad0[0xc4];
    float f0c4;                                 // +0xc4
    float f0c8;                                 // +0xc8
    float f0cc;                                 // +0xcc
    void FUN_00bef890();                        // 0x00bef890
};
void* FUN_0067ddd0();                           // 0x0067ddd0  EffectsManagerPtr
class Sim_s00be_a930 {
public:
    char       pad0[0x120];
    void*      vptr120;                         // +0x120
    char       pad1[0x590 - 0x124];
    void*      p590;                            // +0x590
    char       pad2[0x5a0 - 0x594];
    IntTreeMap_s00be_a930 map1;                            // +0x5a0
    IntTreeMap_s00be_a930 map2;                            // +0x5bc
    IntTreeMap_s00be_a930 map3;                            // +0x5d8
    char       pad3[0x618 - 0x5f4];
    char*      arr618;                          // +0x618
    char       pad4[0x62c - 0x61c];
    Veh**      vehBegin;                        // +0x62c
    Veh**      vehEnd;                          // +0x630
    char       pad5[0x64c - 0x634];
    int        f64c;                            // +0x64c
    char       pad6[0x750 - 0x650];
    float      f750;                            // +0x750
    int        f754;                            // +0x754
    float      f758;                            // +0x758
    int        i75c;                            // +0x75c
    char       pad7[0x770 - 0x760];
    cSPTimer_s00be_a930   timer770;                        // +0x770
    char       padTimer770[0x88 - 0x20];        // +0x790 .. +0x7f8 (timer770 spans 0x88)
    uint8_t*   begin;                           // +0x7f8
    uint8_t*   end;                             // +0x7fc

    void FUN00bda0a0();                         // 0x00bda0a0
    void FUN00be9cb0(int, int, int, int);       // 0x00be9cb0
    void FUN00c00b00(int, int);                 // 0x00c00b00
    void sub_be92e0(int, int, int, int, int);   // 0x00be92e0
    void sub_bd9a00(void*);                     // 0x00bd9a00
    void sub_bea930();
    void sub_beaa30();
    void sub_beabb0();
    void sub_beb090(int id, int count);  // 0x00beb090 (Sim::sub_beb090)
    void sub_beb1c0(int idx, int p);
    void sub_beb5c0();
    void sub_bd9ed0(int);                       // 0x00bd9ed0
    void sub_be11f0();                          // 0x00be11f0
};
#define V120M(p,slot) ((void*(__thiscall*)(void*))VCALL((char*)(p) + 0x120, slot))((void*)((char*)(p) + 0x120))
// ---- items of slice s00bea930 end

// ---- items of slice s00beb6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g13eb1bc;      // 0x013eb1bc  -1.0f
struct Vector3_s00be_b6d0 {
    float x, y, z;
    Vector3_s00be_b6d0() {}
    Vector3_s00be_b6d0(const Vector3_s00be_b6d0& o) : x(o.x), y(o.y), z(o.z) {}
};
struct SpVector {
    Vector3_s00be_b6d0* mpBegin;
    Vector3_s00be_b6d0* mpEnd;
    Vector3_s00be_b6d0* mpCapacity;
    uint8_t  mAllocator[8];
};
struct IObj_s00be_b6d0 {
    virtual void AddRef();
    virtual void Release();
};
struct ISub34 {
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
    virtual Vector3_s00be_b6d0* v2c();                       // 0x2c  position
    virtual void v30();
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
    virtual void v5c(void* arg);                  // 0x5c
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual float v70();                          // 0x70
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual void v90();
    virtual void v94(void* arg);                  // 0x94
};
void*    __cdecl NounManager_s00be_b6d0();                                    // 0x00b3d300
int      __cdecl GetPlayerEmpireOrMinus1();                        // 0x00b1f9d0
void*    __cdecl EventLog(uint32_t id, int a, uint32_t b);         // 0x00b3d3e0
uint32_t __cdecl FNV1_String16(const void* s, uint32_t hash, int len); // 0x00932f30
float    __cdecl FUN_00b685e0(void* obj);                          // 0x00b685e0
void     __cdecl FUN_00b69930(void* obj, float f, int a);          // 0x00b69930
struct TimerOps {                           // cSPTimer
    uint64_t Elapsed();                     // 0x00bc3190
};
struct TreeOps {                            // eastl rbtree node nuke
    void Nuke(void* node);                  // 0x009a9600
};
struct IdHash {                             // FUN_00bd8660
    void* FindId(uint32_t id);
};
struct SimOps {                             // Sim
    void sub_beabb0();                      // 0x00beabb0
    void sub_bea930();                      // 0x00bea930
    void FUN_00bdbe50();                    // 0x00bdbe50
};
struct EventLogOps {                        // cSPUIEventLog
    void RemoveAllEventsOfSameType();       // 0x00dd7620
};
struct Sim_s00be_b6d0 {
    uint8_t pad_000[0x34];
    uint8_t sub_034[1];                // 0x034
    uint8_t pad_035[0xb0 - 0x35];
    uint8_t timer[1];                  // 0x0b0
    uint8_t pad_0b1[0x340 - 0xb1];
    void**  f340;                      // 0x340
    void**  f344;                      // 0x344
    uint8_t pad_348[0x354 - 0x348];
    void**  f354;                      // 0x354
    void**  f358;                      // 0x358
    uint8_t pad_35c[0x5bc - 0x35c];
    uint8_t tree0[0x1c];               // 0x5bc
    uint8_t tree1[0x1c];               // 0x5d8
    uint8_t* m618;                     // 0x618
    uint8_t pad_61c[0x10];
    void*   m62c;                      // 0x62c

    void sub_beb6d0();
};
static inline void ClearTree(uint8_t* tree)
{
    ((TreeOps*)tree)->Nuke(*(void**)(tree + 0x0c));
    *(void**)(tree + 0x08) = tree + 4;
    *(void**)(tree + 0x0c) = 0;
    tree[0x10] = 0;
    *(uint32_t*)(tree + 0x14) = 0;
    *(void**)(tree + 0x04) = tree + 4;
}
struct cCityWalls_s00be_b6d0 {
    void*    vtbl_a;             // 0x000
    void*    vtbl_b;             // 0x004
    uint8_t  pad_008[0x2c - 8];
    void*    vfptr_rc;           // 0x02c
    uint8_t  pad_030[0x34 - 0x30];
    uint8_t  sub34[1];           // 0x034  cSpatialObject
    uint8_t  pad_035[0x10c - 0x35];
    uint32_t field_10c;          // 0x10c
    SpVector mDockSlots;         // 0x110
    SpVector field_124;          // 0x124
    uint8_t  pad_138[0x198 - 0x138];
    SpVector field_198;          // 0x198
    uint8_t  pad_1ac[0x254 - 0x1ac];
    uint32_t field_254;          // 0x254
    float    mInnerRadius;       // 0x258
    float    mOuterRadius;       // 0x25c
    float    field_260;          // 0x260
    uint32_t field_264;          // 0x264  cCity*
    uint8_t  pad_268[0x344 - 0x268];
    uint32_t mStyle;             // 0x344
    uint8_t  pad_348[0x354 - 0x348];
    uint32_t field_354;          // 0x354

    ISub34* Sub() const { return (ISub34*)sub34; }
    ISub34* CitySub() const { return (ISub34*)(field_264 + 0x120); }

    void    FUN_00bec060();                       // 0x00bec060
    uint32_t PointInsideWall(const Vector3_s00be_b6d0& p);            // 0x00bec0f0
    uint32_t PointInsideInnerWall(const Vector3_s00be_b6d0& p);       // 0x00bec140
    Vector3_s00be_b6d0 GetCenter();                                  // 0x00bec190
    Vector3_s00be_b6d0 GetInnerGatePosition(int idx);                // 0x00bec1c0
    Vector3_s00be_b6d0 GetGatePosition(int idx);                     // 0x00bec2d0
    Vector3_s00be_b6d0* RequestGatePosition(Vector3_s00be_b6d0* out, int idx, int kind);  // 0x00bec460
    Vector3_s00be_b6d0* FindNearestPosition(Vector3_s00be_b6d0* out, const Vector3_s00be_b6d0* ref, int kind); // 0x00bec660
    void    UpdateGatePosition(int idx);                  // 0x00bec790
    bool GetIsWallBuilt();                                // 0x00bec860
};
// ---- items of slice s00beb6d0 end

// @ 0x00bd68c0
void FUN_00bd68c0(cCheatObject* obj)
{
  kCityInputStrategy->Begin();
  kCityInputStrategy->AddNode(gStr_1467f50, 0x1f41, 0);
  kCityInputStrategy->AddNode(gStr_1467f48, 0x1f43, 0);
  kCityInputStrategy->AddNode(gStr_1467f40, 0x1f42, 0);
  kCityInputStrategy->SelectNode(obj ? (char*)obj + 0x34 : 0, 0);
}

// @ 0x00bd6940
void FUN_00bd6940(cCheatObject* obj)
{
  kCityInputStrategy->Begin();
  kCityInputStrategy->AddNode(gStrEnergy, 0x1f47, 0);
  kCityInputStrategy->AddNode(gStrEntertainment, 0x1f49, 0);
  kCityInputStrategy->AddNode(gStrHappiness, 0x1f4a, 0);
  kCityInputStrategy->AddNode(gStrAll, 0x1f4b, 0);
  kCityInputStrategy->SelectNode(obj ? (char*)obj + 0x34 : 0, 0);
}

// @ 0x00bd69d0
void FUN_00bd69d0(cCheatObject* obj)
{
  kCityInputStrategy->Begin();
  kCityInputStrategy->AddNode(gStrHunger, 0x1f46, 0);
  kCityInputStrategy->AddNode(gStrEnergy, 0x1f47, 0);
  kCityInputStrategy->AddNode(gStrHealth, 0x1f48, 0);
  kCityInputStrategy->AddNode(gStrAll, 0x1f4b, 0);
  kCityInputStrategy->SelectNode(obj ? (char*)obj + 0x34 : 0, 0);
}

// @ 0x00bd6e00
void FUN_00bd6e00(cCheatObject* obj)
{
  kCityInputStrategy->Begin();
  kCityInputStrategy->AddNode(gStrSetMotive, 0x1f40, 0);
  kCityInputStrategy->AddNode(gStrHappinessW, 0x1f44, 0);
  kCityInputStrategy->AddNode(gStrToggleId, 0x1f4c, 0);
  kCityInputStrategy->AddNode(gStrMaxVehicles, 0x1f4d, 0);
  IRef* p = obj->mpDataObject;
  if (p) {
    int v = ((Fn_i_v)VT(p, 0x38))(p);
    if (v == (int)0xee9b2232)
      kCityInputStrategy->AddNode((const wchar_t*)g_14682ac, 0x1f45, 0);
  }
  kCityInputStrategy->SelectNode((SP::cSpatialObject_s00bd_5ea0*)obj, 0);
}

// @ 0x00bd8140
void __fastcall FUN_00bd8140(cCity* ecx_this, void* edx, int v)
{
    ecx_this->u2f4 = v;
    if (v < 0) {
        ecx_this->u2f4 = 0;
    }
}

// @ 0x00bd8170
void __fastcall FUN_00bd8170(cCity* ecx_this, void* edx, int v)
{
    ecx_this->u2f8 = v;
    if (v < 0) {
        ecx_this->u2f8 = 0;
    }
}

// @ 0x00bd8200
void __cdecl FUN_00bd8200()
{
    if (g_168d248 == 3) {
        return;
    }
    FUN_00c004a0();
}

// @ 0x00bd8210
void __fastcall FUN_00bd8210(IObj* ecx_this, void* edx)
{
    Float3 buf;
    ((cPlanetModel*)FUN_00b3d350())->GetContinent(ecx_this->Slot58(&buf));
}

// @ 0x00bd8240
int __fastcall FUN_00bd8240(cCity* ecx_this, void* edx)
{
    if (ecx_this->mTimer230.IsRunning() == 0) {
        return 0;
    }
    if ((unsigned long long)ecx_this->mTimer230.GetElapsedTime() < 120000ULL) {
        return 1;
    }
    return 0;
}

// @ 0x00bd8280
int __fastcall FUN_00bd8280(cCity* ecx_this, void* edx)
{
    if (ecx_this->mTimer250.IsRunning() == 0) {
        return 0;
    }
    if ((unsigned long long)ecx_this->mTimer250.GetElapsedTime() < 30000ULL) {
        return 1;
    }
    return 0;
}

// @ 0x00bd82c0
int __fastcall FUN_00bd82c0(cCity* ecx_this, void* edx)
{
    if (ecx_this->mTimer270.IsRunning() != 0) {
        unsigned long long t = (unsigned long long)ecx_this->mTimer270.GetElapsedTime();
        if (t < ecx_this->Timer270End()) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00bd8300
void __fastcall FUN_00bd8300(cCity* ecx_this, void* edx, int ms)
{
    cSPTimer* t = &ecx_this->mTimer270;
    if (t->IsRunning() != 0) {
        unsigned long long limit = ecx_this->Timer270End();
        unsigned long long e = (unsigned long long)t->GetElapsedTime();
        if (e <= limit) {
            unsigned long long sum = (unsigned long long)(long long)(ms * 1000) + limit;
            ecx_this->u290 = (u32)sum;
            ecx_this->u294 = (u32)(sum >> 32);
            return;
        }
    }
    t->Restart();
    int prod = ms * 1000;
    long long v = prod;
    ecx_this->u290 = (u32)v;
    ecx_this->u294 = (u32)((unsigned long long)v >> 32);
}

// @ 0x00bd8380
void __fastcall FUN_00bd8380(cCity* ecx_this, void* edx, char flag, float v)
{
    ecx_this->b2fc = (u8)flag;
    ecx_this->f300 = v;
}

// @ 0x00bd83c0
void __fastcall FUN_00bd83c0(void** ecx_this, void* edx)
{
    void* p = *ecx_this;
    *ecx_this = 0;
    if (p != 0) {
        (*(void(__fastcall**)(void*))(*(int*)p + 0xc0))(p);
    }
}

// @ 0x00bd8480
void* __cdecl FUN_00bd8480(void* first, void* last, void* out)
{
    while (first != last) {
        Entry80* e = (Entry80*)first;
        void* p78 = e->mp78;
        if (p78 != 0) {
            (*(void(__fastcall**)(void*))(*(int*)p78 + 0xc0))(p78);
        }
        void* p70 = e->mp70;
        if (p70 != 0) {
            (*(void(__fastcall**)(void*))(*(int*)p70 + 0xc0))(p70);
        }
        FUN_00b638b0((char*)first + 0x50);
        FUN_00b638b0((char*)first + 0x30);
        first = (char*)first + 0x80;
        out = (char*)out + 0x80;
    }
    return out;
}

// @ 0x00bd84e0
u32 __fastcall FUN_00bd84e0(IObj* ecx_this, void* edx)
{
    IObj* p = (IObj*)ecx_this->v30();
    if (p != 0) {
        return (u32)p->Cast(0xee9b2232);
    }
    return 0;
}

// @ 0x00bd8500
void __fastcall FUN_00bd8500(cCity* ecx_this, void* edx, char flag, void* owner)
{
    ecx_this->SetGameDataOwner2(owner);
    ecx_this->b1d4 = (u8)flag;
    IObj* made = ((cGameNounManager*)FUN_00b3d300())->CreateNoun(0x2e72cae);
    IObj* old = ecx_this->mp208;
    if (made != old) {
        if (made != 0) {
            made->v00();
        }
        ecx_this->mp208 = made;
        if (old != 0) {
            old->v04();
        }
    }
    ecx_this->mp208->SetEffectId((int)&g_168bd70, 5.0f);
    ecx_this->mp208->DoF3d2(ecx_this);
    ecx_this->mRegion38.AsSlot38()->DoC470(1);
}

// @ 0x00bd8590
void __fastcall FUN_00bd8590(cCommunity* ecx_this, void* edx, void* a)
{
    ecx_this->func54h(a);
    cCom108* o = ecx_this->mp108;
    o->mFwd70.Call38(a);
}

// @ 0x00bd85c0
void __fastcall FUN_00bd85c0(cCity* ecx_this, void* edx, float* out, int* count)
{
    int n = (int)(ecx_this->mEnd1f8 - ecx_this->mBeg1f4);
    int i = 0;
    *count = n;
    if (n > 0) {
        cElem1f4** p = ecx_this->mBeg1f4;
        do {
            *out += ((*p++)->f0c50 + 0.5f) * 0.6666667f;
            ++i;
        } while (i < *count);
    }
}

// @ 0x00bd8630
int __fastcall FUN_00bd8630(cCity* ecx_this, void* edx)
{
    if (ecx_this->i1d8 == 2) {
        cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
        int e = nm->GetPlayerEmpireOrMinus1();
        if (ecx_this->i1dc == e) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00bd8660
IObj* __fastcall FUN_00bd8660(cCity* ecx_this, void* edx)
{
    ecx_this->mRegion38.mObj100.GetPosition();
    cElem1f4* found = 0;
    int pass = 0;
    do {
        if (ecx_this->mBeg1f4 != ecx_this->mEnd1f8) {
            float bestD = g_146847c;
            for (cElem1f4** it = ecx_this->mBeg1f4; it != ecx_this->mEnd1f8; ++it) {
                cElem1f4* e = *it;
                IX508* io = &e->mObj508;
                if (io->GetFileCount() == 2) {
                    continue;
                }
                IX54* q = io->Slot54();
                if ((q == 0 || q->Slot5c(0x3d5c477) == 0) && pass <= 0) {
                    continue;
                }
                float d = io->Distance();
                if (bestD > d) {
                    bestD = d;
                    found = e;
                }
            }
            if (found != 0) {
                return (IObj*)found;
            }
        }
        ++pass;
    } while (pass < 2);
    return (IObj*)found;
}

// @ 0x00bd8750
void __cdecl FUN_00bd8750(Float3* out, Float3* target)
{
    cPlanetModel* pm = (cPlanetModel*)FUN_00b3d350();
    Float3 a;
    Float3 b;
    if (pm->Probe(target, g_1468454, &a) == 0) {
        Float3* p = pm->Sample(&b);
        a.x = p->x - target->x;
        a.y = p->y - target->y;
        a.z = p->z - target->z;
    }
    float inv = (float)(1.0 / sqrt(a.y * a.y + a.z * a.z + a.x * a.x + g_13ec4b8));
    out->x = inv * a.x;
    out->y = inv * a.y;
    out->z = inv * a.z;
}

// @ 0x00bd8810
char __fastcall FUN_00bd8810(cCity* ecx_this, void* edx, void* param)
{
    if (FUN_00b183f0(ecx_this, 0, param) == 0) {
        return 0;
    }
    cPlanetModel* pm = (cPlanetModel*)FUN_00b3d350();
    if (pm != 0) {
        int n = (int)(ecx_this->mEnd560 - ecx_this->mBeg55c);
        if (n > 0) {
            cElem55c* e = ecx_this->mBeg55c;
            do {
                if (e->kind == 0 && e->p4->p11c == ecx_this) {
                    pm->Despawn(e->p4);
                } else if (e->kind == 1) {
                    pm->Spawn(ecx_this, e->p0);
                } else if (e->kind == 2) {
                    pm->SpawnAlt(ecx_this, e->p0);
                }
                ++e;
                --n;
            } while (n != 0);
        }
    }
    return 1;
}

// @ 0x00bd88c0
void __fastcall FUN_00bd88c0(cCity* ecx_this, void* edx)
{
    int n = (int)(ecx_this->mEnd560 - ecx_this->mBeg55c);
    if (n <= 0) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (ecx_this->mBeg55c[i].p4 != 0) {
            if (FUN_00b3d350() != 0) {
                ((cPlanetModel*)FUN_00b3d350())->Attach(ecx_this->mBeg55c[i].p4);
                cElem55c* pe = &ecx_this->mBeg55c[i];
                pe->p4->AddEntry(ecx_this, pe->p0, 1);
                ((cPlanetModel*)FUN_00b3d350())->Despawn(ecx_this->mBeg55c[i].p4);
            }
        }
    }
}

// @ 0x00bd8960
int __fastcall FUN_00bd8960(cCity* ecx_this, void* edx)
{
    cCombatCarrier** it = ecx_this->mBeg340;
    cCombatCarrier** end = ecx_this->mEnd344;
    int n = 0;
    while (it != end) {
        if (((*it)->GetTypeId() == 0xff10521 || (*it)->GetTypeId() == 0x1007ae63) && (*it)->b289 != 0) {
            ++n;
        }
        ++it;
    }
    return (int)g_169c088 * n;
}

// @ 0x00bd89c0
int __fastcall FUN_00bd89c0(cCity* ecx_this, void* edx)
{
    int r = 0xc;
    IObj* p = ecx_this->mp324;
    if (p != 0) {
        u32 v = p->Slot6c();
        switch (v) {
        case 0:
            r = 6;
            break;
        case 1:
            r = 0xc;
            break;
        case 2:
            r = 6;
            break;
        case 3:
            r = 0xc;
            break;
        }
    }
    return r;
}

// @ 0x00bd8a00
int __fastcall FUN_00bd8a00(cCity* ecx_this, void* edx)
{
    IObj* p = ecx_this->mp324;
    int v = 0xc;
    if (p != 0) {
        u32 s = p->Slot6c();
        switch (s) {
        case 0:
            v = 6;
            break;
        case 1:
            v = 0xc;
            break;
        case 2:
            v = 6;
            break;
        case 3:
            v = 0xc;
            break;
        }
    }
    int lo = v;
    if (FUN_00b5b800() == (u32)&g_1654c05) {
        void* lu = FUN_010212a0();
        if (((cPlanetRecord*)lu)->GameMode() == 5) {
            void* tf = FUN_00b3d430(0);
            int b = ((cTerraformingMgr*)tf)->TerraformCount();
            b -= (int)(((char*)ecx_this->mEnd358 - (char*)ecx_this->mBeg354) >> 2);
            const int& m = (lo < b) ? lo : b;
            return m;
        }
    }
    return lo;
}

// @ 0x00bd8aa0
int __fastcall FUN_00bd8aa0(cCity* ecx_this, void* edx)
{
    switch (ecx_this->i540) {
    case 0:
        return (-(int)(ecx_this->b519 != 0) & 0xfffffffd) + 8;
    case 1:
        return (ecx_this->b519 == 0) * 2 + 4;
    case 2:
        return (ecx_this->b519 == 0) + 3;
    }
    if (((cPlanetRecord*)FUN_010212a0())->GameMode() == 5) {
        return 8;
    }
    int r = 0;
    return r;
}

// @ 0x00bd8b10
int __fastcall FUN_00bd8b10(cCity* ecx_this, void* edx)
{
    typedef int (__fastcall *FT)(cCity*);
    int v = ((FT)FUN_00bd8aa0)(ecx_this);
    int lo = v;
    if (FUN_00b5b800() == (u32)&g_1654c05) {
        void* lu = FUN_010212a0();
        if (((cPlanetRecord*)lu)->GameMode() == 5) {
            void* tf = FUN_00b3d430(0);
            int b = ((cTerraformingMgr*)tf)->TerraformCount();
            b -= (int)(((char*)ecx_this->mEnd344 - (char*)ecx_this->mBeg340) >> 2);
            const int& m = (lo < b) ? lo : b;
            return m;
        }
    }
    return lo;
}

// @ 0x00bd8b80
int __fastcall FUN_00bd8b80(cCity* ecx_this, void* edx)
{
    if (FUN_00b5b800() != (u32)&g_1654c05) {
        int v = ecx_this->i678;
        if (ecx_this->b698 != 0 && ecx_this->f304 > g_13f1cac) {
            v = v + v;
        }
        if (ecx_this->b6c0 != 0 && g_13f1cac > ecx_this->f304) {
            v = v / 2;
        }
        return v;
    }
    return ecx_this->i678;
}

// @ 0x00bd8bd0
void __fastcall FUN_00bd8bd0(cCity* ecx_this, void* edx)
{
    if (FUN_00b5b800() == (u32)&g_1654c05) {
        return;
    }
    if (ecx_this->b698 != 0) {
        long long t = ecx_this->mTimer6a0.GetElapsedTime();
        u32 hi = (u32)((unsigned long long)t >> 32);
        u32 lo = (u32)t;
        if (hi != 0 || lo > 60000) {
            ecx_this->b698 = 0;
            ecx_this->mTimer6a0.Restart();
        } else if (FUN_00c004c0(ecx_this, 0, 0) == 0 && FUN_00c004c0(ecx_this, 0, 1) != 0) {
            ecx_this->b698 = 0;
            ecx_this->mTimer6a0.Restart();
        }
    } else {
        long long t = ecx_this->mTimer6a0.GetElapsedTime();
        u32 hi = (u32)((unsigned long long)t >> 32);
        u32 lo = (u32)t;
        if ((hi != 0 || lo > 10000) &&
            FUN_00c004c0(ecx_this, 0, 0) == 0 && FUN_00c004c0(ecx_this, 0, 1) == 0) {
            int thresh = (int)(ecx_this->f304 - g_13f1cac);
            if (ecx_this->f304 == g_13ec4d0) {
                thresh += 10;
            }
            u32 r = RandomUint32Uniform(&g_1601760, 0, 200);
            if ((int)r < thresh) {
                FUN_00bd7d90(ecx_this, 0);
            } else {
                ecx_this->mTimer6a0.Restart();
            }
        }
    }
    if (ecx_this->b6c0 != 0) {
        long long t = ecx_this->mTimer6c8.GetElapsedTime();
        u32 hi = (u32)((unsigned long long)t >> 32);
        u32 lo = (u32)t;
        if (hi != 0 || lo > 60000) {
            ecx_this->b6c0 = 0;
            ecx_this->mTimer6c8.Restart();
        }
    } else {
        long long t = ecx_this->mTimer6c8.GetElapsedTime();
        u32 hi = (u32)((unsigned long long)t >> 32);
        u32 lo = (u32)t;
        if (hi != 0 || lo > 5000) {
            int thresh = (int)(g_13f1cac - ecx_this->f304);
            u32 r = RandomUint32Uniform(&g_1601760, 0, 200);
            if ((int)r < thresh) {
                ecx_this->b6c0 = 1;
                ecx_this->mTimer6c8.Restart();
            }
        }
    }
}

// @ 0x00bd8d70
void* __fastcall FUN_00bd8d70(cCity* ecx_this, void* edx, cCombatCarrier* carrier)
{
    if (ecx_this->v2c() != 0) {
        return 0;
    }
    u32 start = 0;
    u32 stop = 3;
    if (carrier->iB1c == 1) {
        start = 3;
        stop = 4;
    }
    float best = g_146847c;
    Float3* pf = carrier->mObj34.GetPosition();
    float fx = pf->x, fy = pf->y, fz = pf->z;
    void* target = carrier->mObj508.Slot10();
    void* chosen = 0;
    for (u32 i = start; i < stop; ++i) {
        cCity* e = ecx_this->mBeg62c[i];
        char isTwo = (char)(e->i1d8 == 2);
        char isTarget = (char)(e->i1dc == (int)target);
        char has = 0;
        cCity** it = e->mBeg1e0;
        cCity** end = e->mEnd1e4;
        if (it != end) {
            do {
                if (has != 0) {
                    break;
                }
                has = (char)(*it == target);
                ++it;
            } while (it != end);
        }
        if (isTarget != 0) {
            chosen = e;
            break;
        }
        if (isTwo == 0) {
            if (has != 0) {
                chosen = e;
                break;
            }
            Float3* q = e->mRegion38.mObj100.GetPosition();
            float dz = fz - q->z;
            float dy = fy - q->y;
            float dx = fx - q->x;
            float d = dz * dz + dy * dy + dx * dx;
            if (d < best) {
                chosen = e;
                best = d;
            }
        }
    }
    return chosen;
}

// @ 0x00bd8f30
char __fastcall FUN_00bd8f30(cCity* ecx_this, void* edx)
{
    cCity** it = ecx_this->mBeg62c;
    cCity** end = ecx_this->mEnd630;
    char r = 0;
    while (it != end) {
        if (r != 0) {
            break;
        }
        cCity* o = *it;
        r = (o->i1d8 == 2);
        ++it;
    }
    return r;
}

// @ 0x00bd8f60
char __fastcall FUN_00bd8f60(cCity* ecx_this, void* edx)
{
    cCombatCarrier** it = ecx_this->mBeg340;
    cCombatCarrier** end = ecx_this->mEnd344;
    bool r = false;
    while (it != end) {
        if (r) {
            break;
        }
        cCombatCarrier* o = *it;
        if (o->i290 > 0 || o->mSlot120.Test() != 0) {
            r = true;
        }
        ++it;
    }
    cCombatCarrier** it2 = ecx_this->mBeg354;
    cCombatCarrier** end2 = ecx_this->mEnd358;
    while (it2 != end2) {
        if (r) {
            break;
        }
        cCombatCarrier* o = *it2;
        if (o->i684 > 0 || o->mSlot588.Test() != 0) {
            r = true;
        }
        ++it2;
    }
    return r;
}

// @ 0x00bd8fe0
void __fastcall FUN_00bd8fe0(cCity* ecx_this, void* edx, void* a, void* b)
{
    cPlanet* planet = (cPlanet*)FUN_01021260();
    if (planet == 0) {
        return;
    }
    cCivData* civ = planet->GetCiv(a);
    cCivData* other = planet->GetCiv(b);
    if (civ == 0 || other == 0) {
        return;
    }
    int n = (int)(civ->mEnd40 - civ->mBeg3c);
    int i = 0;
    if (n > 0) {
        do {
            int** cities = civ->GetCities();
            if ((*cities)[i] == (int)ecx_this->u2f0) {
                break;
            }
            ++i;
        } while (i < n);
    }
    if (i != n) {
        civ->RemoveAt(i, other);
    }
}

// @ 0x00bd9060
void __fastcall FUN_00bd9060(cCity* ecx_this, void* edx, IObj* other)
{
    ecx_this->b2e3 = 0;
    FUN_00bebdd0(ecx_this->mp324, 0, (char*)other + 0xc4);
    cTriggerMgr* tm = (cTriggerMgr*)FUN_00b3d4d0();
    if (tm->mMode2c != 1 && tm->mMode2c != 2) {
        void* r = FUN_00b3d480(ecx_this);
        (void)r;
        char g = FUN_00ac8d60(ecx_this, 0, other);
        if (g == 0) {
            return;
        }
    }
    IObj* p = (IObj*)(*(void*(__fastcall**)(cCity*, int))(*(int*)ecx_this + 0x6c))(ecx_this, 0);
    (*(void(__fastcall**)(IObj*, int))(*(int*)p + 0x6c))(p, 0);
}

// @ 0x00bd9140
void __fastcall FUN_00bd9140(cCity* ecx_this, void* edx, IObj* other)
{
    int i = 0;
    ecx_this->b2e5 = (u8)i;
    int n = (int)(((char*)ecx_this->mEnd344 - (char*)ecx_this->mBeg340) >> 2);
    if (i < n) {
        do {
            cCombatCarrier* e = ecx_this->mBeg340[i];
            void* mgr = FUN_00b3d240();
            IObj* o = &e->mObj34;
            u32 a = other->Slot4c(0xffffffff, 1.0f);
            Float3 tmp;
            u32 b = o->Slot5c(&tmp, a);
            u32 c = (u32)(*(void*(__fastcall**)(IObj*, u32))(*(int*)o + 0x2c))(o, b);
            (*(void(__fastcall**)(void*, u32, u32))(*(int*)mgr + 0x5c))(mgr, 0x5f4d3ce, c);
            ++i;
        } while (i < n);
    }
}

// @ 0x00bd91e0
void cCity_s00bd_91e0::ShowTransitionWarning()
{
    switch (mVehicleSpecialty) {
    case 0:
        if (mContextState == 1)
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningTraderHostile);
        else
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningTrader);
        break;
    case 1:
        if (mContextState == 2)
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningMilitaryHostile);
        else
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningMilitary);
        break;
    case 2:
        if (mContextState == 0)
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningEcoHostile);
        else
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningEco);
        break;
    }
    cGameTimeManager* pTimeManager = GameTimeManager();
    pTimeManager->IncPauseGate(0x4bf38a7);
}

// @ 0x00bd9260
bool cCity_s00bd_91e0::HasTradePartner(uint32_t nEmpireID)
{
    for (uint32_t i = 0; i < mTradePartners.size(); ++i) {
        if ((uint32_t)mTradePartners[i].mpInterCityRoad == nEmpireID)
            return true;
    }
    return false;
}

// @ 0x00bd92d0
cCity_s00bd_91e0* cCity_s00bd_91e0::FindNearestCity(int32_t nReason)
{
    cCity_s00bd_91e0* pBest = 0;
    float fBestDistance = kFloatMax;
    for (int32_t nPass = 0; nPass < 2; ++nPass) {
        cVec<cCity_s00bd_91e0*>* pCities = GetCityList(nReason);
        for (uint32_t i = 0; i < pCities->size(); ++i) {
            cCity_s00bd_91e0* pOther = (*pCities)[i];
            if (pOther == this)
                continue;
            if (pOther->mVehicleSpecialty != 2 && nPass <= 0)
                continue;
            Vector3* pOtherPosition = pOther->mSpatial.GetPosition(0);
            Vector3* pOwnPosition = mSpatial.GetPosition(0);
            float fDeltaY = pOwnPosition->y - pOtherPosition->y;
            float fDeltaZ = pOwnPosition->z - pOtherPosition->z;
            float fDeltaX = pOwnPosition->x - pOtherPosition->x;
            float fDistance = (fDeltaY * fDeltaY + fDeltaZ * fDeltaZ) + fDeltaX * fDeltaX;
            Vector3 ownKey;
            Vector3 otherKey;
            Vector3* pOwnKey = (Vector3*)mSpatial.GetPlanetPosition(&ownKey);
            int32_t nOwnContinent = PlanetModel()->GetContinent(pOwnKey);
            Vector3* pOtherKey = (Vector3*)pOther->mSpatial.GetPlanetPosition(&otherKey);
            int32_t nOtherContinent = PlanetModel()->GetContinent(pOtherKey);
            if (nOwnContinent != nOtherContinent)
                fDistance *= kTenFold;
            if (fDistance < fBestDistance) {
                fBestDistance = fDistance;
                pBest = pOther;
            }
        }
        if (pBest)
            break;
    }
    return pBest;
}

// @ 0x00bd9470
float cCity_s00bd_91e0::GetCityRadius()
{
    return mpLayoutWalls->mRadius;
}

// @ 0x00bd9480
Vector3* cCity_s00bd_91e0::GetWallsCenter(Vector3* pOut)
{
    mpCityWalls->GetCenter(pOut);
    return pOut;
}

// @ 0x00bd94a0
void cCity_s00bd_91e0::UpdateTurretLayout(void* pOwner)
{
    float fRadius = mpCityWalls->mRadius;
    Vector3 facing;
    mSpatial.v5c(&facing, 0.0f);
    Vector3* pCenter = mSpatial.GetPosition(0);
    mTurretsLayout.SetAtCenter(pCenter, fRadius, &facing);
    mTurretsLayout.EmitCopy(pOwner, kEmitScale);
    int32_t nCount = (int32_t)mTurrets.size();
    for (int32_t i = 0; i < nCount; ++i) {
        cTurret* pTurret = mTurrets[i];
        cLayoutSlot* pSlot = mTurretsLayout.FindSlotAt(pTurret->mObject34.GetPosition());
        if (!pSlot)
            continue;
        pSlot->Reserve((cGameData*)pTurret);
        Vector3 slotPosition = pSlot->mPosition;
        pTurret->mObject34.SetPosition(&slotPosition);
        Vector3 planetKey;
        Vector3* pPlanetPosition = (Vector3*)mpVtbl->pGetPlanetPosition(this, &planetKey);
        Vector3 delta;
        delta.x = slotPosition.x - pPlanetPosition->x;
        delta.y = slotPosition.y - pPlanetPosition->y;
        delta.z = slotPosition.z - pPlanetPosition->z;
        Quaternion orientation;
        PlanetModel()->BuildSurfaceOrientation2(&orientation, &delta, &slotPosition);
        pTurret->mObject34.SetOrientation(&orientation);
    }
}

// @ 0x00bd9620
void cCity_s00bd_91e0::SetField51C(const cVec<Vector3>* pPositions)
{
    if ((int32_t)pPositions->size() > 0)
        mPendingPosition = (*pPositions)[0];
}

// @ 0x00bd9660
bool cCity_s00bd_91e0::SetDecoration(cCityObject* pObject)
{
    cLayoutSlot* pSlot = mDecorationsLayout.FindSlotAt(pObject->mSpatial120.GetPosition(0));
    if (pSlot) {
        pSlot->Reserve((cGameData*)pObject);
        pObject->mSpatial120.SetPosition(&pSlot->mPosition);
        Quaternion orientation;
        PlanetModel()->BuildSurfaceOrientation(&orientation, &pSlot->mPosition);
        pObject->mSpatial120.SetOrientation(&orientation);
        return true;
    }
    pObject->mSpatial120.SetPosition(mpCityHall->mObject34.GetPosition());
    pObject->mSpatial120.SetOrientation(mpCityHall->mObject34.GetOrientation());
    return false;
}

// @ 0x00bd9710
void cCity_s00bd_91e0::UpdateCityPosition()
{
    if (mpCityWalls->GetState() != 2 && mpCityWalls->GetState() != 3) {
        mCityPosition = kDefaultCityPosition;
        return;
    }
    Vector3 request;
    Vector3* pRequested = mpCityWalls->RequestPosition(&request, 3);
    mCityPosition = *pRequested;
    Vector3 wallsCenter;
    mpCityWalls->GetCenter(&wallsCenter);
    float fDeltaX = mCityPosition.x - wallsCenter.x;
    float fDeltaY = mCityPosition.y - wallsCenter.y;
    float fDeltaZ = mCityPosition.z - wallsCenter.z;
    float fScale = 1.0f / sqrtf(fDeltaZ * fDeltaZ + fDeltaY * fDeltaY + fDeltaX * fDeltaX + kSqrtEpsilon);
    Vector3 step;
    step.x = fDeltaX * fScale * kGrowStep;
    step.y = fDeltaY * fScale * kGrowStep;
    step.z = fDeltaZ * fScale * kGrowStep;
    mCityPosition.x += step.x;
    mCityPosition.y += step.y;
    mCityPosition.z += step.z;
    int32_t nTries = 0;
    while (!IsOnTerraformedGround(1, &mCityPosition)) {
        mCityPosition.x += step.x;
        mCityPosition.y += step.y;
        mCityPosition.z += step.z;
        if (++nTries >= 8)
            break;
    }
    Vector3 surface;
    Vector3* pSurface = PlanetModel()->GetSurfacePosition(&surface, &mCityPosition);
    mCityPosition = *pSurface;
}

// @ 0x00bd99e0
void* cCity_s00bd_91e0::GetCivilizationData()
{
    if (mpCivilization)
        return &mpCivilization->mDataC4;
    return (void*)&kDefaultCivilizationData;
}

// @ 0x00bd9a80
float __cdecl GetForeignCityMood(void* pObject)
{
    float fValue;
    cGameNounManager_s00bd_91e0* pNouns = ((cProtectorSource*)pObject)->GetNounManager();
    fValue = 0.0f;
    if (((cProtectorSource*)pObject)->GetCategory() == 5) {
        if (pNouns->GetAvatar() != GetPlayerEmpireID()) {
            cStarEmpire* pEmpire = StarManager()->GetEmpireByID((int32_t)pNouns->GetAvatar());
            cGameData* pEmpireData = StarManager()->GetEmpireData(pEmpire);
            if (HasTerraformEvent(pObject) || TerraformingManager()->HasEvent(pObject))
                GetPropertyFloat(pEmpireData, 0x68086e9, &fValue);
            else
                GetPropertyFloat(pEmpireData, 0x68086f3, &fValue);
        }
    }
    return fValue;
}

// @ 0x00bd9b70
int32_t cCity_s00bd_91e0::CountEmptyTurrets()
{
    int32_t nCount = 0;
    cTurret** pIter = mTurrets.mpBegin;
    cTurret** pEnd = mTurrets.mpEnd;
    if (pIter != pEnd) {
        do {
            cTurret* pTurret = (*pIter);
            if (pTurret->mSpatial588.GetObjectCount() == 0)
                nCount = nCount + 1;
            ++pIter;
        } while (pIter != pEnd);
    }
    return nCount;
}

// @ 0x00bd9bb0
int32_t cCity_s00bd_91e0::CountEmptyBuildings()
{
    int32_t nCount = 0;
    cCityObject** pIter = mBuildings.mpBegin;
    cCityObject** pEnd = mBuildings.mpEnd;
    if (pIter != pEnd) {
        do {
            cCityObject* pBuilding = (*pIter);
            if (pBuilding->mSpatial120.GetObjectCount() == 0)
                nCount = nCount + 1;
            ++pIter;
        } while (pIter != pEnd);
    }
    return nCount;
}

// @ 0x00bd9c00
bool cCity_s00bd_91e0::ContainsPoint(const Vector3* pPoint)
{
    if (mpCityWalls) {
        if (mpCityWalls->ContainsPoint(pPoint))
            return true;
    }
    return false;
}

// @ 0x00bd9c30
bool cCity_s00bd_91e0::IsWithinRadius(const Vector3& rPoint, float fExtra)
{
    if (mpCityWalls) {
        Vector3 center;
        mpCityWalls->GetCenter(&center);
        float fDeltaX = rPoint.x - center.x;
        float fDeltaY = rPoint.y - center.y;
        float fDeltaZ = rPoint.z - center.z;
        float fDistance = (float)sqrt(fDeltaZ * fDeltaZ + fDeltaY * fDeltaY + fDeltaX * fDeltaX);
        if (fDistance < mpCityWalls->mRadius + fExtra)
            return true;
    }
    return false;
}

// @ 0x00bd9ca0
Vector3* cCity_s00bd_91e0::GetCenter(Vector3* pOut)
{
    cCityObject* pHall = mpCityHall;
    if (pHall) {
        Vector3* pPosition = pHall->mpVtbl->pGetPosition(pHall);
        pOut->x = pPosition->x;
        pOut->y = pPosition->y;
        pOut->z = pPosition->z;
        return pOut;
    }
    mpCityWalls->GetCenter(pOut);
    return pOut;
}

// @ 0x00bd9cf0
void* cCity_s00bd_91e0::GetPlayerTerrainSphere()
{
    cCivilization* pCivilization = mpCivilization;
    if (pCivilization == NounManager()->GetPlayerCivilization())
        return NounManager()->GetCurrentTerrainSphere();
    return 0;
}

// @ 0x00bd9d70
void* __cdecl CreateCityObject(void* pPosition, void* pParams)
{
    cGameNounManager_s00bd_91e0* pNouns = NounManager();
    cGameData* pNoun = pNouns->CreateNoun(0x18c43e8);
    cCityObject* pCity = pNoun ? (cCityObject*)pNoun->Cast(0xee9b2232) : 0;
    if (pParams)
        pCity->mObject34.v00(pParams);
    pCity->mSpatial120.SetPosition((const Vector3*)pPosition);
    return pCity;
}

// @ 0x00bd9dd0
void cCity_s00bd_91e0::ClearCreature()
{
    ReleaseCreature();
}

// @ 0x00bd9e50
void cCity_s00bd_91e0::NotifySectionObject()
{
    if (!mpSection2F0)
        return;
    cGameModeSection* pSection = GetGameModeSection();
    mpSection2F0->OnCityChanged(this, pSection->mField13C);
}

// @ 0x00bd9fa0
int32_t cCity_s00bd_91e0::IsCultureActive()
{
    bool bConverted = false;
    cCulturalTarget** pIter = mCulturalTargets.mpBegin;
    cCulturalTarget** pEnd = mCulturalTargets.mpEnd;
    if (pIter != pEnd) {
        do {
            if (bConverted)
                return 1;
            bConverted = (*pIter)->mState == 2;
            ++pIter;
        } while (pIter != pEnd);
        if (bConverted)
            return 1;
    }
    if (!IsFestivalActive() && !HasCultureEvent(false))
        return 0;
    return 1;
}

// @ 0x00bda0a0
void cCity_s00bd_91e0::ClearCultureState()
{
    ReleaseCreature();
    if (mpObject768) {
        mpObject768->Cast(0);
        cGameData* pReleased = mpObject768;
        mpObject768 = 0;
        if (pReleased)
            pReleased->Release();
    }
    mMessiahTimer.Stop();
}

// @ 0x00bda6d0
void __stdcall DestroyRefPairs(cAutoRef12* pFirst, cAutoRef12* pLast)
{
    for (; pFirst < pLast; pFirst += 1) {
        cAutoRefData* pSecond = pFirst->mpSecond;
        if (pSecond)
            pSecond->Release();
        cAutoRefData* pFirst0 = pFirst->mpFirst;
        if (pFirst0)
            pFirst0->Release();
    }
}

// @ 0x00bda710
void __stdcall DestroyCultureTargetInfo(tCultureTargetInfo_s00bd_a190* pFirst, tCultureTargetInfo_s00bd_a190* pLast)
{
    for (; pFirst < pLast; pFirst += 1) {
        cGameData_s00bd_a190* pCulture = pFirst->mpCultureObject;
        if (pCulture)
            pCulture->ReleaseGameData();
        cGameData_s00bd_a190* pTarget = pFirst->mpAttackTarget;
        if (pTarget)
            pTarget->ReleaseGameData();
        DestroyGonzagoTimer(pFirst->mConvertedTimer);
        DestroyGonzagoTimer(pFirst->mConvertCheckTimer);
    }
}

// @ 0x00bda760
cRefOps* __thiscall cRefOps::AssignRefPairObj(const cAutoRef12* pSrc)
{
    cAutoRef12* pDst = (cAutoRef12*)this;
    cAutoRefData* pNew = pSrc->mpFirst;
    cAutoRefData* pOld = pDst->mpFirst;
    if (pNew != pOld) {
        if (pNew)
            pNew->AddRef();
        pDst->mpFirst = pNew;
        if (pOld)
            pOld->Release();
    }
    pNew = pSrc->mpSecond;
    pOld = pDst->mpSecond;
    if (pNew != pOld) {
        if (pNew)
            pNew->AddRef();
        pDst->mpSecond = pNew;
        if (pOld)
            pOld->Release();
    }
    pDst->mField08 = pSrc->mField08;
    return this;
}

// @ 0x00bda7d0
void __thiscall cRefOps::CopyTransform50Obj(const void* pSrc)
{
    void* pDst = this;
    const uint32_t* pS = (const uint32_t*)pSrc;
    uint32_t* pD = (uint32_t*)pDst;
    pD[0] = pS[0];
    pD[1] = pS[1];
    for (int32_t n = 2; n < 0x14; ++n)
        ((float*)pD)[n] = ((const float*)pS)[n];
}

// @ 0x00bda850
void CopyBucket20(uint8_t* pSrc, uint8_t* pEnd, uint8_t* pDst)
{
    while (pSrc != pEnd) {
        if (pDst) {
            *(float*)(pDst + 0x00) = *(const float*)(pSrc + 0x00);
            *(float*)(pDst + 0x04) = *(const float*)(pSrc + 0x04);
            *(float*)(pDst + 0x08) = *(const float*)(pSrc + 0x08);
            *(float*)(pDst + 0x0c) = *(const float*)(pSrc + 0x0c);
            *(uint32_t*)(pDst + 0x10) = *(const uint32_t*)(pSrc + 0x10);
        }
        pSrc += 0x14;
        pDst += 0x14;
    }
}

// @ 0x00bda8d0
cAutoRef12* CopyRefPairs(cAutoRef12* pSrc, cAutoRef12* pEnd, cAutoRef12* pDst)
{
    while (pSrc != pEnd) {
        if (pDst) {
            cAutoRefData* pFirst = pSrc->mpFirst;
            pDst->mpFirst = pFirst;
            if (pFirst)
                pFirst->AddRef();
            cAutoRefData* pSecond = pSrc->mpSecond;
            pDst->mpSecond = pSecond;
            if (pSecond)
                pSecond->AddRef();
            pDst->mField08 = pSrc->mField08;
        }
        ++pSrc;
        ++pDst;
    }
    return pDst;
}

// @ 0x00bda930
cAutoRef12* DestroyRefPairsReturn(cAutoRef12* pSrc, cAutoRef12* pEnd, cAutoRef12* pDst)
{
    while (pSrc != pEnd) {
        cAutoRefData* pSecond = pSrc->mpSecond;
        if (pSecond)
            pSecond->Release();
        cAutoRefData* pFirst = pSrc->mpFirst;
        if (pFirst)
            pFirst->Release();
        ++pSrc;
        ++pDst;
    }
    return pDst;
}

// @ 0x00bda980
cAutoRef12* AssignRefPairRange(cAutoRef12* pSrc, cAutoRef12* pEnd, cAutoRef12* pDst)
{
    while (pSrc != pEnd) {
        cAutoRefData* pNew = pSrc->mpFirst;
        cAutoRefData* pOld = pDst->mpFirst;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pDst->mpFirst = pNew;
            if (pOld)
                pOld->Release();
        }
        pNew = pSrc->mpSecond;
        pOld = pDst->mpSecond;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pDst->mpSecond = pNew;
            if (pOld)
                pOld->Release();
        }
        pDst->mField08 = pSrc->mField08;
        ++pSrc;
        ++pDst;
    }
    return pDst;
}

// @ 0x00bdaa90
uint8_t* CopyBucket28(uint8_t* pSrc, uint8_t* pEnd, uint8_t* pDst)
{
    while (pSrc != pEnd) {
        if (pDst) {
            *(float*)(pDst + 0x00) = *(const float*)(pSrc + 0x00);
            *(float*)(pDst + 0x04) = *(const float*)(pSrc + 0x04);
            *(float*)(pDst + 0x08) = *(const float*)(pSrc + 0x08);
            *(uint32_t*)(pDst + 0x0c) = *(const uint32_t*)(pSrc + 0x0c);
            *(uint32_t*)(pDst + 0x10) = *(const uint32_t*)(pSrc + 0x10);
            *(uint32_t*)(pDst + 0x14) = *(const uint32_t*)(pSrc + 0x14);
            *(pDst + 0x18) = *(pSrc + 0x18);
        }
        pSrc += 0x1c;
        pDst += 0x1c;
    }
    return pDst;
}

// @ 0x00bdaae0
cAutoRef12* AssignRefPairRangeBackward(cAutoRef12* pFirst, cAutoRef12* pLast, cAutoRef12* pDstEnd)
{
    if (pLast == pFirst)
        return pDstEnd;
    do {
        cAutoRefData* pNew = (pLast - 1)->mpFirst;
        cAutoRefData* pOld = (pDstEnd - 1)->mpFirst;
        --pLast;
        --pDstEnd;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pDstEnd->mpFirst = pNew;
            if (pOld)
                pOld->Release();
        }
        pNew = pLast->mpSecond;
        pOld = pDstEnd->mpSecond;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pDstEnd->mpSecond = pNew;
            if (pOld)
                pOld->Release();
        }
        pDstEnd->mField08 = pLast->mField08;
    } while (pLast != pFirst);
    return pDstEnd;
}

// @ 0x00bdab60
namespace Simulator {
cCulturalTarget_s00bd_a190::cCulturalTarget_s00bd_a190()
{
    mGameData.Ctor();
    mCombatant.Ctor();
    mSpatial.Ctor();

    mAttackState = 0;

    mGameData.mpVtbl = (void*)g_1468618;
    mpVtbl04 = (void*)g_1468608;
    mCombatant.mpVtbl = (void*)g_14685a0;
    mSpatial.mpVtbl = (void*)g_14684d8;

    mGateIndex = 0xff;
    mAttackerPoliticalID = 0xffffffff;

    mAttackOrders.mpBegin = 0;
    mAttackOrders.mpEnd = 0;
    mAttackOrders.mpCapacity = 0;
    mAttackers.mpBegin = 0;
    mAttackers.mpEnd = 0;
    mAttackers.mpCapacity = 0;
    mpHitSphere = 0;
    mAngerLevel = 0;
    mLastDancingCrowdFraction = 0.0f;
    mLastAngryCrowdFraction = 0.0f;
}
}  // namespace Simulator

// @ 0x00bdace0
cCulturalTarget_s00bd_a190::~cCulturalTarget_s00bd_a190()
{
    cCombatant_s00bd_a190* pCombatant = &mCombatant;
    cSpatialObject_s00bd_a190* pSpatial = (cSpatialObject_s00bd_a190*)((char*)this + 0x100);
    cGameData_s00bd_a190* pHitSphere = mpHitSphere;
    if (pHitSphere)
        pHitSphere->Release();
    DestroyAutoRefVector(&mAttackers);
    void* pOrders = mAttackOrders.mpBegin;
    if (pOrders && ((int32_t*)pOrders)[-1] != 0)
        operator_delete(pOrders);
    DestroySpatialObject(pSpatial);
    DestroyCombatant(pCombatant);
    DestroyGameData((cGameData_s00bd_a190*)this);
}

// @ 0x00bdad60
bool cCulturalTarget_s00bd_a190::RemoveAttacker(cGameData_s00bd_a190* pTarget)
{
    uint32_t nKey = pTarget ? (uint32_t)pTarget->Cast(kCultureTargetCastType) : 0;
    int32_t nCount = (int32_t)(((char*)mAttackers.mpEnd - (char*)mAttackers.mpBegin) >> 2);
    int32_t nIndex = -1;
    uint8_t bResult = 0;
    if (nCount > 0) {
        for (int32_t i = 0; i < nCount; ++i) {
            if (nIndex >= 0)
                break;
            if (((uint32_t*)mAttackers.mpBegin)[i] == nKey)
                nIndex = i;
        }
        if (nIndex >= 0) {
            for (; nIndex < nCount - 1; ++nIndex) {
                cGameData_s00bd_a190** pSlot = &((cGameData_s00bd_a190**)mAttackers.mpBegin)[nIndex];
                cGameData_s00bd_a190* pNew = pSlot[1];
                cGameData_s00bd_a190* pOld = pSlot[0];
                if (pNew != pOld) {
                    if (pNew)
                        pNew->AddRef();
                    pSlot[0] = pNew;
                    if (pOld)
                        pOld->Release();
                }
            }
            mAttackers.mpEnd = (char*)mAttackers.mpEnd - 4;
            cGameData_s00bd_a190* pLast = *(cGameData_s00bd_a190**)mAttackers.mpEnd;
            if (pLast)
                pLast->Release();
            bResult = 1;
        }
    }
    if (mAttackState != 0) {
        if (mAttackers.mpBegin == mAttackers.mpEnd) {
            mAttackState = 1;
            mAttackerPoliticalID = 0xffffffff;
            return bResult;
        }
        mAttackState = 2;
        cGameData_s00bd_a190* pFirst = *(cGameData_s00bd_a190**)mAttackers.mpBegin;
        cCityCiv* pCiv = (cCityCiv*)((char*)pFirst + 0x508);
        mAttackerPoliticalID = (uint32_t)pCiv->GetPoliticalID();
    }
    return bResult;
}

// @ 0x00bdaea0
void cSimObject::UpdateAggregationRadius()
{
    if (!mpCityHall)
        return;
    if (!mpCityHall->GetHallTarget())
        return;
    if (GetCurrentGameMode() == (void*)kSpaceGameModeID) {
        float fRadius = mpCityHall->mTransform34.GetRadius() * kCultureScaleSpace;
        mpCityHall->GetHallTarget()->mRadius = fRadius;
        return;
    }
    float fWallRadius = mpCityWalls->mRadius;
    mpCityHall->GetHallTarget()->mRadius = sqrtf(fWallRadius * fWallRadius) * kCultureScalePlanet;
}

// @ 0x00bdaf50
void cSimObject::FillCulturalTargetPoints()
{
    cPtrVec points;
    points.mpBegin = 0;
    points.mpEnd = 0;
    points.mpCapacity = 0;
    FillPoints(&points);
    uint32_t nOffset = 0;
    uint32_t nIndex = 0;
    do {
        cCulturalTarget_s00bd_a190* pTarget = mCulturalTargets[nIndex];
        Vector3* pPoint = (Vector3*)((char*)points.mpBegin + nOffset);
        pTarget->GetSpatial()->SetPosition(pPoint);
        Vector3 planetPosition;
        mSpatial120.GetPlanetPosition(&planetPosition);
        float fDeltaX = pPoint->x - planetPosition.x;
        float fDeltaY = pPoint->y - planetPosition.y;
        float fDeltaZ = pPoint->z - planetPosition.z;
        float fInvLen = 1.0f / sqrtf((fDeltaY * fDeltaY + fDeltaZ * fDeltaZ) + fDeltaX * fDeltaX + kSqrtEpsilon_s00bd_a190);
        Vector3 direction;
        direction.x = fInvLen * fDeltaX;
        direction.y = fInvLen * fDeltaY;
        direction.z = fInvLen * fDeltaZ;
        cCulturalTarget_s00bd_a190* pTarget2 = mCulturalTargets[nIndex];
        Quaternion orientation;
        PlanetModel_s00bd_a190();
        BuildSurfaceOrientation2(&orientation, &direction, pPoint);
        pTarget2->GetSpatial()->SetOrientation(&orientation);
        nOffset += 0xc;
        ++nIndex;
    } while (nIndex < 4);
    if (points.mpBegin && ((int32_t*)points.mpBegin)[-1] != 0)
        operator_delete(points.mpBegin);
}

// @ 0x00bdb0b0
void cSimObject::EmitCulturalEffect()
{
    cCityHall* pHall = mpCityHall;
    mbField2E6 = 0;
    if (!pHall)
        return;
    uint32_t nEffectID;
    if (mContextState == 0)
        nEffectID = kCulturalEffect0;
    else if (mContextState == 1)
        nEffectID = kCulturalEffect1;
    else if (mContextState == 2)
        nEffectID = kCulturalEffect2;
    else
        nEffectID = 0;
    cHallTransform* pTransform = &pHall->mTransform34;
    cHallTarget* pTarget = pTransform->GetTarget();
    Vector3* pPosition = pTransform->GetPosition();
    float fScale = pTarget->mScale;
    float fInvLen = 1.0f / sqrtf((pPosition->x * pPosition->x + pPosition->y * pPosition->y) +
                                 pPosition->z * pPosition->z + kSqrtEpsilon_s00bd_a190);
    Vector3 offset;
    offset.x = fScale * (fInvLen * pPosition->x);
    offset.y = fScale * (pPosition->y * fInvLen);
    offset.z = fScale * (pPosition->z * fInvLen);
    Vector3* pBase = pTransform->GetPosition();
    Vector3 position;
    position.x = offset.x + pBase->x;
    position.y = offset.y + pBase->y;
    position.z = offset.z + pBase->z;
    cDispatcher* pDispatcher = GetDispatcher();
    void* pXform = pTransform->MakeTransform(&offset);
    pDispatcher->mpVtbl->pFire(pDispatcher, nEffectID, &position, pXform);
}

// @ 0x00bdb200
bool cCity_s00bd_a190::HasTradePartnerCiv(int32_t nNounID)
{
    uint32_t nCount = (uint32_t)(((char*)mTradePartners.mpEnd - (char*)mTradePartners.mpBegin) / 0xc);
    if (nCount != 0) {
        uint32_t nIndex = 0;
        do {
            cTradePartnerCity* pPartner =
                *(cTradePartnerCity**)((char*)mTradePartners.mpBegin + nIndex * 0xc);
            if (pPartner->mpCivilization->GetPoliticalID() == nNounID)
                return true;
            ++nIndex;
            nCount = (uint32_t)(((char*)mTradePartners.mpEnd - (char*)mTradePartners.mpBegin) / 0xc);
        } while (nIndex < nCount);
    }
    return false;
}

// @ 0x00bdb280
cCity_s00bd_a190* cCity_s00bd_a190::FindTradePartnerCity(int32_t nNounID)
{
    float fBestDistance = kFloatMax_s00bd_a190;
    cCity_s00bd_a190* pBest = 0;
    uint32_t nCount = (uint32_t)(((char*)mTradePartners.mpEnd - (char*)mTradePartners.mpBegin) / 0xc);
    if (nCount != 0) {
        uint32_t nIndex = 0;
        do {
            cTradePartnerCity* pPartner =
                *(cTradePartnerCity**)((char*)mTradePartners.mpBegin + nIndex * 0xc);
            if (pPartner->mpCivilization->GetPoliticalID() == nNounID) {
                Vector3* pPartnerPosition = pPartner->mSpatial.GetPosition(0);
                Vector3* pOwnPosition = mSpatial120.GetPosition(0);
                float fDeltaX = pOwnPosition->x - pPartnerPosition->x;
                float fDeltaY = pOwnPosition->y - pPartnerPosition->y;
                float fDeltaZ = pOwnPosition->z - pPartnerPosition->z;
                float fDistance = sqrtf((fDeltaZ * fDeltaZ + fDeltaY * fDeltaY) + fDeltaX * fDeltaX);
                if (fDistance < fBestDistance) {
                    fBestDistance = fDistance;
                    pBest = (cCity_s00bd_a190*)pPartner;
                }
            }
            ++nIndex;
            nCount = (uint32_t)(((char*)mTradePartners.mpEnd - (char*)mTradePartners.mpBegin) / 0xc);
        } while (nIndex < nCount);
    }
    return pBest;
}

// @ 0x00bdb3b0
void CStub::FUN_00bdb3b0(int a, int b)
{
    m648 = 1;
    m640 = a;
    m644 = b;
    if (SP_GetCurrentGameMode() == (void*)0x1654c04) {
        CivStub* civ = m590;
        if (b != 0 &&
            (**(u8(__thiscall**)(void*))(vpt((void*)(b + 0x34)) + 0x58))((char*)b + 0x34) != 0) {
            if (a == 0 && civ != 0) {
                void* pl = ((NounMgrStub*)nounMgr())->FUN_00b25fb0();
                if (civ != pl)
                    civ->FUN_00bef830();
            }
        } else {
            if ((**(u8(__thiscall**)(void*))(vpt(m120) + 0x58))((char*)this + 0x120) != 0) {
                void* p = (**(void*(__thiscall**)(void*))(vpt((void*)(b + 0x508)) + 0x10))((char*)b + 0x508);
                void* r = ((NounMgrStub*)nounMgr())->FUN_00b25f40((int)p);
                if (a == 0 && r != 0)
                    ((CivStub*)r)->FUN_00bef830();
            }
        }
    }
}

// @ 0x00bdb470
u8 CStub::FUN_00bdb470(int key)
{
    int i = 0;
    if (key == 0x436f315) {
        int n = (int)((char*)m358 - (char*)m354) >> 2;
        if (n > 0) {
            do {
                int obj = (int)m354[i];
                void* c = obj ? (void*)(obj + 0x588) : 0;
                if (((DamageStub*)c)->FUN_008e7f80() == 2) {
                    (**(void(__thiscall**)(void*, int))(vpt(c) + 0x2c))(c, 0);
                    if (m2f0 == 0)
                        return 1;
                    ActivePlanetStub* pl = (ActivePlanetStub*)FUN_01021260();
                    FUN_00ff2810(this, (void*)pl->m13c);
                    return 1;
                }
                ++i;
            } while (i < n);
        }
    } else {
        int n = (int)((char*)m344 - (char*)m340) >> 2;
        if (n > 0) {
            do {
                void* p = (void*)m340[i];
                if ((**(int(__thiscall**)(void*))(vpt(p) + 0x38))(p) == key &&
                    ((DamageStub*)((char*)p + 0x120))->FUN_008e7f80() == 2) {
                    (**(void(__thiscall**)(void*, int))(vpt((char*)p + 0x120) + 0x2c))((char*)p + 0x120, 0);
                    if (m2f0 == 0)
                        return 1;
                    ActivePlanetStub* pl = (ActivePlanetStub*)FUN_01021260();
                    FUN_00ff2810(this, (void*)pl->m13c);
                    return 1;
                }
                ++i;
            } while (i < n);
        }
    }
    return 0;
}

// @ 0x00bdb590
int CStub::FUN_00bdb590(int* key, int* out)
{
    int best = 0;
    int bestScore = 0;
    int slotIdx = 0;
    int flag = 0;
    for (;;) {
        void* slot = m3ec.FUN_00af9ff0((u32)slotIdx);
        if (slot != 0) {
            void* prop = ((SlotObjStub*)slot)->FUN_00fcc210();
            if (prop != 0) {
                void* sub = (**(void*(__thiscall**)(void*, int))(vpt(prop) + 0xc))(prop, 0xe9cb8ba);
                if (sub != 0 && ((DamageStub*)((char*)sub + 0x120))->FUN_008e7f80() != 2)
                    goto nextSlot;
            }
            if (FUN_00bda000(this, slotIdx)) {
                int score = 0;
                for (u32 j = 0; j < 0xe; ++j) {
                    int cur = score;
                    if ((u32)slotIdx != j) {
                        int base = (**(int(__thiscall**)(CStub*))(vpt(this) + 0x6c))(this);
                        if (((u8*)(flag + base + 0x274))[j] != 0) {
                            void* s2 = m3ec.FUN_00af9ff0(j);
                            if (s2 != 0) {
                                void* p2 = ((SlotObjStub*)s2)->FUN_00fcc210();
                                if (p2 != 0) {
                                    void* sub2 = (**(void*(__thiscall**)(void*, int))(vpt(p2) + 0xc))(p2, 0xe9cb8ba);
                                    if (sub2 != 0) {
                                        int mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                        if (key == (int*)0x18ea2cc) {
                                            if (mt != 0x18eb106) {
                                                mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                if (mt != 0x18ea1eb) {
                                                    mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                    if (mt == 0x1a56aba)
                                                        cur = score - 10;
                                                    goto store;
                                                }
                                            }
                                            if (FUN_00bd8b80(this))
                                                cur = score + 50;
                                            else
                                                cur = score + 80;
                                        } else if (key == (int*)0x1a56aba) {
                                            if (mt != 0x18eb106) {
                                                mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                if (mt != 0x18ea1eb) {
                                                    mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                    if (mt == 0x18ea2cc)
                                                        cur = score - 10;
                                                    goto store;
                                                }
                                            }
                                            cur = score + (0x5a - (int)m304);
                                            if (FUN_00bd7e20(this))
                                                cur += 0x14;
                                        } else if (key == (int*)0x18eb106) {
                                            if (mt == 0x18ea2cc) {
                                                if (FUN_00bd8b80(this))
                                                    cur = score + 50;
                                                else
                                                    cur = score + 80;
                                            } else {
                                                mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                if (mt == 0x1a56aba) {
                                                    cur = score + (0x5a - (int)m304);
                                                    if (FUN_00bd7e20(this))
                                                        cur += 0x14;
                                                }
                                            }
                                        }
                                    }
                                    if (key == (int*)0x18eb106)
                                        cur = score + 10;
                                }
                            }
                        }
                    }
                store:
                    score = cur;
                }
                if (bestScore < score) {
                    bestScore = score;
                    best = (int)slot;
                }
            }
        }
    nextSlot:
        flag += 0xe;
        ++slotIdx;
        if ((u32)flag >= 0xc4) {
            if (out)
                *out = bestScore;
            return best;
        }
    }
}

// @ 0x00bdb7f0
void CStub::FUN_00bdb7f0(int obj, int kind)
{
    int model;
    switch (kind) {
    case 0x1a55e4d: model = 0x72c49181; break;
    case 0xecade42: model = 0x47c10953; break;
    case 0x1007ae63: model = 0x99e92f05; break;
    default: model = 0x4e3f7777; break;
    }
have:
    CivStub* civ = m590;
    if (civ != 0) {
        if (*civ->FUN_00bf9770(model) == 0)
            civ->FUN_00bf9780(model);
        void* v = *(void**)(obj + 0x34);
        void* base = (char*)obj + 0x34;
        (**(void(__thiscall**)(void*, int*))(vpt(v) + 0x94))(base, civ->FUN_00bf9770(model));
    }
}

// @ 0x00bdb880
u8 CStub::FUN_00bdb880(int spec)
{
    switch (spec) {
    case 2: {
        bool b = m590->m298 >= 3;
        return b;
    }
    case 1:
        if ((m32c != g_168bd70 || m330 != g_168bd74 || m334 != g_168bd78) &&
            m590->m298 >= 2)
            return 1;
        return 0;
    case 0: {
        bool b = m590->m298 >= 1;
        return b;
    }
    }
    return 0;
}

// @ 0x00bdb930
u8 CStub::FUN_00bdb930(int spec, int arg)
{
    if (spec == 4)
        return 1;
    if (spec == -1)
        return 0;
    if (m540 != spec)
        return 0;
    return FUN_00bdb880(arg);
}

// @ 0x00bdb960
float CStub::FUN_00bdb960()
{
    float fBase = 10.0f;
    float fPer = 30.0f;
    PropObjStub* prop = 0;
    void* pm = SP_PropertyManager();
    if ((**(u8(__thiscall**)(void*, int, PropObjStub**))(vpt(pm) + 0x30))(pm, 0x6b3f727b, &prop) != 0
        && prop != 0) {
        int* got;
        if ((**(u8(__thiscall**)(PropObjStub*, int, int**))(vpt(prop) + 0x24))(prop, 0x39d48e7, &got) != 0
            && *(short*)((char*)got + 0x12) == 0xd)
            fBase = *(float*)got;
        if ((**(u8(__thiscall**)(PropObjStub*, int, int**))(vpt(prop) + 0x24))(prop, 0x78aeaf4b, &got) != 0
            && *(short*)((char*)got + 0x12) == 0xd)
            fPer = *(float*)got;
    }
    int n = (int)((char*)m344 - (char*)m340) >> 2;
    float f = (float)n * fPer + fBase;
    if (prop)
        (**(void(__thiscall**)(PropObjStub*))(vpt(prop) + 4))(prop);
    return f;
}

// @ 0x00bdba80
float CStub::FUN_00bdba80()
{
    return FUN_00bdb960() * sqrtf(m53c + 1.0f);
}

// @ 0x00bdbaa0
void CStub::FUN_00bdbaa0()
{
    int cnt = (int)((m74 - m70) / 0x14);
    if ((u32)cnt < 4)
        return;
    if (m324 == 0)
        return;
    void* pts = 0;
    FUN_00bed3c0(&pts);
    int* src = (int*)pts;
    int* dst = (int*)m70;
    for (int g = 0; g < 4; ++g) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        *(float*)(dst + 3) = 5.0f;
        src += 3;
        dst += 5;
    }
    if (pts != 0 && *((int*)pts - 1) != 0)
        operator_delete(pts);
}

// @ 0x00bdbbb0
void CStub::FUN_00bdbbb0()
{
    float acc = 0.0f;
    for (int i = 10; i != 0; --i) {
        float f = FUN_00bdb960();
        float tmp[3];
        int m = (**(int(__thiscall**)(CStub*, float*, float))(vpt(this) + 0x5c))(this, tmp, f);
        PlanetObjStub* pl = (PlanetObjStub*)SP_PlanetModel(m);
        acc += pl->FUN_00b83620();
    }
    m53c = acc * 0.1f;
}

// @ 0x00bdbc20
void CStub::FUN_00bdbc20(int* flag)
{
    if (m764 != 0) {
        FUN_00bd9dd0();
        return;
    }
    timerRestart(&m790);
    void* sp = FUN_00b3d240();
    void* a = (**(void*(__thiscall**)(void*))(vpt(sp) + 0x74))(sp);
    if (*flag == 0)
        flag = (int*)(m590->FUN_00bef950() + 0x504);
    void* cr = (**(void*(__thiscall**)(void*, int*, int, void*, void*, int))(vpt(a) + 0x30))
        (a, flag, 2, &g_168bd70, &g_156e16c, 1);
    void* old = m764;
    if (cr != old) {
        if (cr)
            ((RefObj3*)cr)->AddRef();
        m764 = cr;
        if (old)
            ((RefObj3*)old)->Release();
    }
    if (m764 != 0) {
        FUN_00a04c80(m764, 6);
        void* c = m764;
        void* p1 = (**(void*(__thiscall**)(void*))(vpt(m320) + 0x2c))((char*)m320 + 0x34);
        *(float*)((char*)c + 4) = ((float*)p1)[0];
        *(float*)((char*)c + 8) = ((float*)p1)[1];
        *(float*)((char*)c + 0xc) = ((float*)p1)[2];
        void* q = (**(void*(__thiscall**)(void*))(vpt(m320) + 0x30))((char*)m320 + 0x34);
        float* qf = (float*)q;
        c = m764;
        *(float*)((char*)c + 0x10) = qf[1];
        *(float*)((char*)c + 0x14) = -qf[0];
        *(float*)((char*)c + 0x18) = qf[3];
        *(float*)((char*)c + 0x1c) = -qf[2];
        *(float*)((char*)m764 + 0x3c) = 60.0f;
        float* civ = (float*)((char*)m590 + 0xc4);
        void* cc = m764;
        *(float*)((char*)cc + 0x74) = civ[0];
        *(float*)((char*)cc + 0x78) = civ[1];
        *(float*)((char*)cc + 0x7c) = civ[2];
        *(float*)((char*)cc + 0x80) = 1.0f;
        int e1 = (**(int(__thiscall**)(void*, int, int))(vpt(m764) + 8))(m764, 0x8bff672a, 0);
        m7b0 = e1;
        (**(void(__thiscall**)(void*, int, int))(vpt(m764) + 0xc))(m764, e1, 1);
        (**(void(__thiscall**)(void*, int))(vpt(m764) + 0x18))(m764, e1);
        int e2 = (**(int(__thiscall**)(void*, int, int))(vpt(m764) + 4))(m764, 0x8ff6177c, 0);
        (**(void(__thiscall**)(void*, int, int))(vpt(m764) + 0x24))(m764, e2, *(int*)&g_1468468);
        int e3 = (**(int(__thiscall**)(void*, int, int))(vpt(m764) + 4))(m764, 0x64be2be, 0);
        m7b4 = e3;
        FUN_00a047d0(m764, 1);
    }
}

// @ 0x00bdbf10
void CStub::FUN_00bdbf10()
{
    if (((MissionMgrStub*)SP_GetMissionManager(FUN_01021260()))->DoMissionsPreventHostility(&g_168bda0))
        return;
    if (SP_GetCurrentGameMode() == &g_1654c05_s00bd_b3b0) {
        ((SimGameStub*)SP_SpaceGameGet(0x13))->f5180();
        if (m220 <= 0.0f) {
            PropObjStub* eff = 0;
            void* em = SP_EffectsManager();
            u8 found = (**(u8(__thiscall**)(void*, int, int, PropObjStub**))(vpt(em) + 0x2c))(em, 0x4dbd616, 0, &eff);
            if (found) {
                XformMsg msg;
                XformMsg_ctor(&msg);
                void* pos = 0;
                FUN_00bec190(&pos);
                *(u16*)msg.m |= 4;
                ++*(u16*)(msg.m + 2);
                *(void**)(msg.m + 4) = *(void**)pos;
                *(void**)(msg.m + 8) = *((void**)pos + 1);
                *(void**)(msg.m + 0xc) = *((void**)pos + 2);
                (**(void(__thiscall**)(PropObjStub*, void*))(vpt(eff) + 0x18))(eff, msg.m);
                (**(void(__thiscall**)(PropObjStub*, int))(vpt(eff) + 8))(eff, 0);
            }
            void* ap = FUN_01021260();
            if (ap != 0) {
                void* sub = ((ActivePlanetStub*)ap)->FUN_00c71e30();
                if (sub != 0)
                    ((SimUniverseStub*)g_16dc798)->FUN_01014a80(*(int*)((char*)sub + 0x84), 0);
            }
            if (eff)
                (**(void(__thiscall**)(PropObjStub*))(vpt(eff) + 4))(eff);
        }
    }
    m220 = ((Tuning2Stub*)SP_GetSpaceCombatTuning())->FUN_01029b90();
}

// @ 0x00bdc050
void CStub::FUN_00bdc050()
{
    PropObjStub* eff = 0;
    void* em = SP_EffectsManager();
    u8 found = (**(u8(__thiscall**)(void*, int, PropObjStub**))(vpt(em) + 0x2c))(em, 0x3d6fa45, &eff);
    if (!found)
        return;
    char buf[0x50];
    *(float*)(buf + 0x0c) = g_168c354;
    *(float*)(buf + 0x10) = g_168c358;
    *(float*)(buf + 0x14) = g_168c35c;
    *(u16*)(buf + 0x00) = 0;
    *(float*)(buf + 0x18) = 1.0f;
    ((Matrix33Ctor*)(buf + 0x1c))->FUN_0041cb40(&g_168c330);
    void* tr = (**(void*(__thiscall**)(void*))(vpt(m120) + 0x2c))((char*)this + 0x120);
    *(float*)(buf + 0x10) = ((float*)tr)[0];
    *(float*)(buf + 0x14) = ((float*)tr)[1];
    *(float*)(buf + 0x18) = ((float*)tr)[2];
    *(u16*)(buf + 0x0c) |= 4;
    ++*(u16*)(buf + 0x0e);
    void* q = (**(void*(__thiscall**)(void*))(vpt(m120) + 0x30))((char*)this + 0x120);
    float m[9];
    int* r = SP_Matrix3FromQuaternion(m, q);
    for (int i = 0; i < 9; ++i)
        ((int*)(buf + 0x1c))[i] = r[i];
    *(u16*)(buf + 0x14) |= 2;
    ++*(u16*)(buf + 0x16);
    float f = FUN_00bdb960() * g_13ef580;
    ++*(u16*)(buf + 0x02);
    *(float*)(buf + 0x1c) = f;
    (**(void(__thiscall**)(PropObjStub*, char*))(vpt(eff) + 0x18))(eff, buf);
    (**(void(__thiscall**)(PropObjStub*, int))(vpt(eff) + 8))(eff, 0);
    if (eff)
        (**(void(__thiscall**)(PropObjStub*))(vpt(eff) + 4))(eff);
}

// @ 0x00bdc1a0
void CStub::FUN_00bdc1a0(int kind, int param)
{
    void* tgt = m590->FUN_00bf1780(param);
    timerStop((char*)tgt + 0x88);
    float v[6];
    FUN_00bda200(v, kind, param);
    float len = 1.0f / sqrtf(v[0] * v[0] + (v[1] * v[1] + v[2] * v[2]) + g_13ec4b8);
    float scale = g_146869c[kind];
    float dx = scale * (len * v[0]);
    float dy = scale * (v[1] * len);
    float dz = scale * (v[2] * len);
    float pos[3];
    PlanetObjStub* pl = (PlanetObjStub*)SP_PlanetModel1(pos);
    float* base = (float*)pl->FUN_00b81630();
    pos[0] = base[0] + dx;
    pos[1] = base[1] + dy;
    pos[2] = base[2] + dz;
    float* circ = m320 ? (float*)((char*)m320 + 0x34) : 0;
    ((ToolMgrStub*)tgt)->UseToolStart(circ, pos, -1, 0, 0, 1);
    if (kind == 1) {
        void** list = (void**)((NounMgrStub*)nounMgr())->FUN_00b25ca0();
        void** begin = (void**)*list;
        int n = (int)((char*)list[1] - (char*)*list) >> 2;
        for (int i = 0; i < n; ++i) {
            void* civ = begin[i];
            if (civ == m590)
                continue;
            int id1 = (**(int(__thiscall**)(void*, int, int))(vpt(m590) + 0x4c))(m590, 0x5776d99, *(int*)&g_1485720);
            int id2 = (**(int(__thiscall**)(void*, int))(vpt(civ) + 0x4c))(civ, id1);
            ((RelMgrStub*)SP_RelationshipManager())->FUN_00d06240(id2, id1, *(int*)&g_1485720);
        }
    }
}

// @ 0x00bdc350
void __fastcall FUN_00bdc350(SelfB* self)
{
    if (self->m764 != 0) {
        if (self->m768 != 0) {
            self->m768->Stop(0);
            IEffect* old = self->m768;
            self->m768 = 0;
            if (old != 0)
                old->Release();
        }
        self->m770.Restart();
        return;
    }

    char* p = self->m590->F00bef950();
    self->F00bdbc20(p + 0x504);

    if (self->m768 == 0) {
        EffectsMgr* mgr = EffectsManager();
        IEffect* old = self->m768;
        if (old != 0) {
            self->m768 = 0;
            old->Release();
        }
        if (mgr->CreateEffect(0xb332de96, 0, &self->m768)) {
            XformMsg_s00bd_c350 msg;
            Vector3_s00bd_c350* pos = ((Vector3_s00bd_c350* (__thiscall*)(void*))
                            (*(void***)&self->m120Vtbl)[0x2c / 4])
                           (&self->m120Vtbl);
            msg.SetPos(*pos);
            Quaternion_s00bd_c350* q = ((Quaternion_s00bd_c350* (__thiscall*)(void*))
                             (*(void***)((char*)self->m320 + 0x34))[0x30 / 4])
                            ((char*)self->m320 + 0x34);
            Matrix3 rot;
            Matrix3FromQuaternion(rot, *q);
            msg.SetRot(rot);
            self->m768->SetTransform(&msg);
            self->m768->Start(0);
        }
    }
    self->m770.Restart();
}

// @ 0x00bdc7b0
int** __cdecl FUN_00bdc7b0(int** out, Object7b0** first, Object7b0** last, int value)
{
    *out = (int*)value;
    while (first != last) {
        if (*out != 0) {
            Object7b0* obj = *first;
            int* sub = obj ? (int*)((char*)obj + 0x34) : 0;
            *(*out) = (int)sub;
            if (sub != 0)
                ((Void0)(*(void***)sub)[0xbc / 4])(sub);
        }
        *out = *out + 1;
        ++first;
    }
    return out;
}

// @ 0x00bdc8a0
void __thiscall SelfB::FUN_00bdc8a0(u64 delta)
{
    SelfB* self = this;
    if (self->m2cc == 2 || self->m2d0 < 1) {
        if (self->m2cc != 0 && self->m2d0 == 0)
            self->m2cc = 0;
    } else {
        if (self->m64c <= self->m2d0) {
            self->m2cc = 2;
            int empire = ((int (__thiscall*)(void*))
                          (*(void***)self)[0x4c / 4])(self);
            if (empire != GetPlayerEmpireID_s00bd_c350()) {
                float f = ((RelationshipMgr*)RelationshipManager())
                          ->RecordEvent(((int (__thiscall*)(void*))
                                         (*(void***)self)[0x4c / 4])(self),
                                        GetPlayerEmpireID_s00bd_c350(), 0x526e52d, 1.0f);
                Vector3_s00bd_c350* pos = ((Vector3_s00bd_c350* (__thiscall*)(void*))
                                (*(void***)&self->m120Vtbl)[0x2c / 4])
                               (&self->m120Vtbl);
                DoCommunityReaction(self, f, *pos);
                self->F00bdbf10();
            }
            void* obj = FUN_00b3d240();
            char buf[12];
            void* value = ((void* (__thiscall*)(void*, char*, void*))
                           (*(void***)self)[0x5c / 4])(self, buf,
                                                       (void*)0x0168bd70);
            ((void (__thiscall*)(void*, u32, void*))
             (*(void***)obj)[0x60 / 4])(obj, 0x2df3697, value);
        }
        if (self->m2cc == 1) {
            double r = ((RandomGlobal*)0x01601760)->RandomDouble();
            if (r < *(float*)0x01471064)
                ++self->m2d0;
        }
    }

    if (self->m220 > 0.0f)
        self->m220 -= (float)delta * 0.001f;
    if (self->m220 < 0.0f)
        self->m220 = 0.0f;
}

// @ 0x00bdd2f0
void __fastcall FUN_00bdd2f0(Obj2f0* self)
{
    if (self->m320 == 0)
        return;

    self->Notify();

    struct Transform2f0 {
        int mX;                 // +0x50
        int mY;                 // +0x54
        int mZ;                 // +0x58
        float mW;               // +0x5c
        int mE;                 // +0x60
        Transform2f0(int x, int y, int z, float w, int e)
            : mX(x), mY(y), mZ(z), mW(w), mE(e) {}
    };
    int zero = 0;
    *(Transform2f0*)(self->mp70 + 0x50) =
        Transform2f0(self->m51c, self->m520, self->m524,
                     *(float*)0x013eeda0, zero);
}

// @ 0x00bdd350
bool __cdecl FUN_00bdd350(void* self, void** other)
{
    int value = 0;
    void* obj = *other;
    if (obj != 0)
        value = ((Int1)(*(void***)obj)[0xb8 / 4])(obj, 0x179c807);

    ((Void1)(*(void***)self)[0x2c / 4])(self, (void*)value);
    return true;
}

// @ 0x00bdd380
CElement *CElement::CopyConstructFrom(const CElement &src)
{
    m_u00 = src.m_u00;
    m_u04 = src.m_u04;
    m_u08 = src.m_u08;
    m_u0c = src.m_u0c;
    m_u10 = src.m_u10;
    m_u14 = src.m_u14;
    m_u18 = src.m_u18;
    m_u1c = src.m_u1c;
    m_u20 = src.m_u20;
    m_f24 = src.m_f24;
    m_f28 = src.m_f28;
    m_f2c = src.m_f2c;

    CopySub(m_a, src.m_a);
    CopySub(m_b, src.m_b);

    m_p70 = src.m_p70;
    if (m_p70 != 0)
        m_p70->AddRef();
    m_u74 = src.m_u74;
    m_p78 = src.m_p78;
    if (m_p78 != 0)
        m_p78->AddRef();
    return this;
}

// @ 0x00bdd470
CElement *CElement::CopyAssignFrom(const CElement &src)
{
    m_u00 = src.m_u00;
    m_u04 = src.m_u04;
    m_u08 = src.m_u08;
    m_u0c = src.m_u0c;
    m_u10 = src.m_u10;
    m_u14 = src.m_u14;
    m_u18 = src.m_u18;
    m_u1c = src.m_u1c;
    m_u20 = src.m_u20;
    m_f24 = src.m_f24;
    m_f28 = src.m_f28;
    m_f2c = src.m_f2c;

    m_a.m_u08 = src.m_a.m_u08;
    m_a.m_u0c = src.m_a.m_u0c;
    m_a.m_u10 = src.m_a.m_u10;
    m_a.m_u14 = src.m_a.m_u14;
    m_a.m_u18 = src.m_a.m_u18;
    m_a.m_u1c = src.m_a.m_u1c;

    m_b.m_u08 = src.m_b.m_u08;
    m_b.m_u0c = src.m_b.m_u0c;
    m_b.m_u10 = src.m_b.m_u10;
    m_b.m_u14 = src.m_b.m_u14;
    m_b.m_u18 = src.m_b.m_u18;
    m_b.m_u1c = src.m_b.m_u1c;

    _ReadWriteBarrier();
    CRefCounted *new70 = src.m_p70;
    CRefCounted *old70 = m_p70;
    if (new70 != old70) {
        if (new70 != 0)
            new70->AddRef();
        m_p70 = new70;
        if (old70 != 0)
            old70->Release();
    }

    m_u74 = src.m_u74;

    _ReadWriteBarrier();
    CRefCounted *new78 = src.m_p78;
    CRefCounted *old78 = m_p78;
    if (new78 != old78) {
        if (new78 != 0)
            new78->AddRef();
        m_p78 = new78;
        if (old78 != 0)
            old78->Release();
    }
    return this;
}

// @ 0x00bdd580
CElement **__cdecl FUN_00bdd580(CElement **cursor, CElement *first, CElement *last, CElement *dest)
{
    *cursor = dest;
    while (first != last) {
        if (*cursor != 0)
            (*cursor)->CopyConstructFrom(*first);
        *cursor += 1;
        ++first;
    }
    return cursor;
}

// @ 0x00bdd5c0
CElement *__cdecl FUN_00bdd5c0(CElement *first, CElement *last, CElement *dest)
{
    while (first != last) {
        if (dest != 0)
            dest->CopyConstructFrom(*first);
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x00bdd600
CElement *__cdecl FUN_00bdd600(CElement *first, CElement *last, CElement *dest)
{
    while (first != last) {
        dest->CopyAssignFrom(*first);
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x00bdd640
CElement *__cdecl FUN_00bdd640(CElement *first, CElement *last, CElement *dest)
{
    while (last != first) {
        --last;
        --dest;
        dest->CopyAssignFrom(*last);
    }
    return dest;
}

// @ 0x00bdd680
void __fastcall FUN_00bdd680(CDerivedGameData *self)
{
    if (self->m_p11c != 0)
        self->m_p11c->Slot1();

    int n108 = (int)(((u32)self->m_arr108End - (u32)self->m_arr108) & 0xfffffffeu);
    if (n108 > 2 && self->m_arr108 != 0)
        FUN_00f47380(self->m_arr108);

    int nF8 = (int)(((u32)self->m_arrF8End - (u32)self->m_arrF8) & 0xfffffffeu);
    if (nF8 > 2 && self->m_arrF8 != 0)
        FUN_00f47380(self->m_arrF8);

    ((void (__thiscall *)(void *))FUN_00ae6970)(&self->m_vecE4);
    ((void (__thiscall *)(void *))FUN_00ad92d0)(&self->m_vecD0);
    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_timerB0);

    ((void (__thiscall *)(void *, void *, void *))FUN_00bdc770)(
        &self->m_vec84, self->m_vec84.m_begin, self->m_vec84.m_end);

    if (self->m_vec84.m_begin != 0 &&
        ((u32 *)self->m_vec84.m_begin)[-1] != 0)
        FUN_00f47380(self->m_vec84.m_begin);

    if (self->m_p70 != 0 && ((u32 *)self->m_p70)[-1] != 0)
        FUN_00f47380(self->m_p70);

    if (self->m_p58 != 0 && ((u32 *)self->m_p58)[-1] != 0)
        FUN_00f47380(self->m_p58);

    if (self->m_p3c != 0 && ((u32 *)self->m_p3c)[-1] != 0)
        FUN_00f47380(self->m_p3c);

    ((void (__thiscall *)(void *))FUN_00b184c0)(self);
}

// @ 0x00bdd780
void __fastcall FUN_00bdd780(CCity *self)
{
    self->m_vtbl0 = (void *)0x14687d8;
    self->m_vtbl4 = (void *)0x14687c4;
    self->m_vtbl34 = (void *)0x1469cc0;
    self->m_spatial120.m_vtbl = (void *)0x1468700;
    self->m_paint1f4.m_vtbl = (void *)0x14686e4;
    self->m_paint1f4.m_vtbl18 = (void *)0x14686d4;

    if (self->m_p810 != 0)
        self->m_p810->Slot1();
    FreeChecked(self->m_p7f8);
    if (self->m_p7d4 != 0)
        self->m_p7d4->Slot1();
    DestroyTree(self->m_tree7b8);

    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t790);
    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t770);
    if (self->m_p768 != 0)
        self->m_p768->Slot1();
    if (self->m_p764 != 0)
        ((void (__thiscall *)(void *))FUN_00a05270)(self->m_p764);

    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t728);
    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t708);
    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t6e8);
    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t6c8);
    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t6a0);

    FreeChecked(self->m_p684);
    DestroyObjVector4(self->m_vec62c);
    FreeChecked(self->m_vec62c.m_begin);

    ((void (__thiscall *)(void *, void *, void *))FUN_00bda710)(
        &self->m_vec618, self->m_vec618.m_begin, self->m_vec618.m_end);
    FreeChecked(self->m_vec618.m_begin);

    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t5f8);

    DestroyTree(self->m_tree5d8);
    DestroyTree(self->m_tree5bc);
    DestroyTree(self->m_tree5a0);
    if (self->m_p590 != 0)
        self->m_p590->Slot1();
    DestroyTree(self->m_tree570);

    DestroyStride12(self->m_vec55c);
    FreeChecked(self->m_vec55c.m_begin);
    DestroySlot64(self->m_vec548);
    FreeChecked(self->m_vec548.m_begin);
    FreeChecked(self->m_p528);

    ((void (__thiscall *)(void *))FUN_00afbad0)(&self->m_action4b4);
    ((void (__thiscall *)(void *))FUN_00afbad0)(&self->m_action450);
    ((void (__thiscall *)(void *))FUN_00afbad0)(&self->m_action3ec);

    DestroyObjVector4(self->m_vec354);
    if (self->m_vec354.m_begin != 0 && self->m_vec354.m_begin != self->m_p364)
        FUN_00f47380(self->m_vec354.m_begin);
    DestroyObjVector4(self->m_vec340);
    FreeChecked(self->m_vec340.m_begin);

    if (self->m_p328 != 0)
        self->m_p328->Slot1();
    if (self->m_p324 != 0)
        self->m_p324->Slot1();
    if (self->m_p320 != 0)
        self->m_p320->Slot1();

    DestroyObjVector4(self->m_vec308);
    FreeChecked(self->m_vec308.m_begin);
    FreeChecked(self->m_p2b8);
    FreeChecked(self->m_p2a4);

    if (self->m_p298 != 0)
        ((void (__thiscall *)(void *))self->m_p298->m_vtbl[0xc0 / 4])(self->m_p298);

    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t270);
    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t250);
    ((void (__thiscall *)(void *))FUN_00b638b0_s00bd_d380)(&self->m_t230);

    {
        int n = (int)(((u32)self->m_arr218 - (u32)self->m_arr210) & 0xfffffffeu);
        if (n > 2 && self->m_arr210 != 0)
            FUN_00f47380(self->m_arr210);
    }

    self->m_paint1f4.m_vtbl18 = (void *)0x13eb394;
    ((void (__thiscall *)(void *))FUN_00ac0520)(&self->m_paint1f4);
    ((void (__thiscall *)(void *))FUN_00c8a420)(&self->m_spatial120);

    FUN_00bdd680((CDerivedGameData *)self);
}

// @ 0x00bddda0
int CCity::FUN_00bddda0(int a1, int a2, int a3, int a4, int a5, int a6)
{
    if (m_p590 == 0)
        return 0;

    CVec3 local28;
    CVec3 local1c;
    CVec3 local10;

    ((void (__thiscall *)(CCity *, CVec3 *, int))FUN_00bdca30)(this, &local28, a2);

    int obj = ((int (__thiscall *)(void *, int, int, int, int, int, CVec3 *, int))FUN_00bf57b0)(
        m_p590, a1, a2, a3, a4, a5, &local28, a6);
    if (obj == 0)
        return 0;

    void *sub = (void *)(obj + 0x34);
    void **vtbl = *(void ***)(obj + 0x34);

    int u = m_p324->Call70(&local1c);

    void *model = FUN_00b3d350();
    int orient = ((int (__thiscall *)(void *, CVec3 *, CVec3 *, int))FUN_00b7f250)(
        model, &local10, &local28, u);

    ((void (__thiscall *)(void *, int))vtbl[0x3c / 4])(sub, orient);

    void **vtbl2 = *(void ***)(obj + 0x34);
    ((void (__thiscall *)(void *, float))vtbl2[0x40 / 4])(sub, *(float *)0x1488874);

    ((void (__thiscall *)(void *, float))FUN_00c88530)(sub, 1.0f);

    return obj;
}

// @ 0x00bdde70
void cCity_s00bd_de70::UpdateCityHallRollover(cSPUIRolloverCivCityHall* pUI)
{
    IWindow* pRoot = pUI->GetRootWindow();
    int slot = 0;
    pUI->ClearEntries();
    for (RBNode* pNode = mAllegianceBegin; pNode != (RBNode*)&mAllegianceAnchorRight; pNode = RBTreeIncrement(pNode)) {
        int count = pNode->mValue;
        unsigned int empireId = pNode->mKey;
        if (count > 0) {
            cCivilization_s00bd_de70* pCiv = NounManager_s00bd_de70()->FindCivilization(empireId);
            if (pCiv) {
                pUI->AddEntry(slot, count, pCiv->mColor.GetARGB());
                if (pCiv == mpCivilization)
                    pUI->SelectEntry(slot);
                ++slot;
            }
        }
    }

    int mode = GetCurrentGameMode_s00bd_de70();
    unsigned int titleId = mode == kGameModeSpace ? 0x68c71fb : 0x653ea92;
    gCivModeStrategy->SetSelectedCity(this);
    cString title;
    title.Load(0xdc351566, titleId, 0);
    WStr titleText;
    MakeWStr(titleText, title.GetText());
    SetStringProp(pUI, 0x2cf2f74, titleText);

    IWindow* pWindow = pRoot->FindWindow(0x2cf2f74, 1);
    IColorable* pIncomeText = pWindow ? pWindow->Cast(0xf15f4bd) : 0;

    int income = mFinalIncome;
    if (GetCurrentGameMode_s00bd_de70() != kGameModeSpace) {
        if (mPartyOn && mfHappiness > 50.0f)
            income = income * 2;
        if (mRiotOn && mfHappiness < 50.0f)
            income = income / 2;
    }
    if (income > 0) {
        if (mPartyOn && mfHappiness > 50.0f)
            pIncomeText->SetColor(0xff00ff00);
        else if (mRiotOn && mfHappiness < 50.0f)
            pIncomeText->SetColor(0xffff0000);
        else
            pIncomeText->SetColor(0xff00ffff);
    } else {
        pIncomeText->SetColor(0xffffffff);
    }

    int diff = mHappyCount - mUnhappyCount;
    for (int i = 0; i < 5; ++i) {
        float f = 0.0f;
        if (diff > 0) {
            if (i < diff)
                f = 100.0f;
        } else if (diff < 0) {
            if (i < -diff)
                f = 50.0f;
        }
        SetFloatProp(pUI, i + 0x4fe1aa0, f);
    }

    int healthy = 0;
    for (cCitizen** it = mCitizensBegin; it != mCitizensEnd; ++it) {
        if ((*it)->mCombatant.GetDamageState() == 0)
            ++healthy;
    }
    for (int i = 0; i < 5; ++i) {
        float f = 0.0f;
        if (i < healthy)
            f = 100.0f;
        SetFloatProp(pUI, i + 0x4fe38f0, f);
    }

    cCivilization_s00bd_de70* pCiv = mpCivilization;
    float relation;
    if (pCiv == NounManager_s00bd_de70()->GetPlayerCivilization()) {
        relation = 50.0f;
    } else {
        int myEmpire = NounManager_s00bd_de70()->GetPlayerEmpireOrMinus1();
        relation = GetRelationshipValue(pCiv->GetRelationshipEmpire(myEmpire), myEmpire);
    }
    SetFloatProp(pUI, 0x46adf86, relation);

    {
        Variant v;
        v.mTypeId = 9;
        v.mFlags = 0;
        *(int*)v.data = GetHousingAmount();
        pUI->SetProp(0x199a7d2, &v, 1, 0);
        if (v.mFlags & 4)
            v.Destruct(0);
    }

    {
        WStr nameText;
        MakeWStr(nameText, mName.GetName());
        SetStringProp(pUI, 0x2cf2f44, nameText);
        FreeWStr(nameText);
    }

    if (GetCurrentGameMode_s00bd_de70() == kGameModeCiv) {
        unsigned int icon;
        switch (mVehicleSpecialty) {
        case 0: icon = 0x2cf2f38; break;
        case 1: icon = 0x2cf2f34; break;
        case 2: icon = 0x2cf2f30; break;
        default: icon = 0; break;
        }
        pUI->SetSpecialtyIcon(icon);
    } else if (GetCurrentGameMode_s00bd_de70() == kGameModeSpace) {
        pUI->SetSpecialtyIcon(0);
    }

    pUI->SetOwnerButtonState(!mbIsPlayerCity);
    pUI->Refresh();
    FreeWStr(titleText);
}

// @ 0x00bde4a0
int* cCity_s00bd_de70::FUN_00bde4a0()
{
    CivView* civ = (CivView*)mpCivilization;
    if (civ->field4b0 < kTickLimit)
        return (int*)civ;

    if (NounManager_s00bd_de70() && NounManager_s00bd_de70()->GetPlayerCivilization()) {
        if (!FUN_00bef870(NounManager_s00bd_de70()->GetPlayerCivilization()))
            return 0;
    }

    long long t = mTimer.GetElapsedTime();
    unsigned lo = (unsigned)(t & 0xffffffffu);
    unsigned hi = (unsigned)((unsigned long long)t >> 32);
    if (hi != 0 || lo > 90000) {
        mTimer.Restart();
        return (int*)this;
    }

    cTerrainEditor* te = (cTerrainEditor*)NounManager_s00bd_de70();
    int tkind = FUN_00c75420(te->GetCurrentTerrainSphere());
    if (tkind == 0) {
        if (gMathRandom->RandomUint32Uniform(100) != 0)
            return 0;
    } else if (tkind == 1) {
        if (gMathRandom->RandomUint32Uniform(10) != 0)
            return 0;
    }

    unsigned n;
    if (!FUN_00c004c0(this, 0) && !FUN_00c004c0(this, 1))
        n = 0x3c;
    else
        n = 0x14;
    if (gMathRandom->RandomUint32Uniform(n) != 0)
        return 0;

    // scan the civilization's city list for the viewer city
    bool bVar2 = false, bVar16 = false;
    CityKind* chosen = 0;
    void** pb = civ->cities.b;
    void** pe = civ->cities.e;
    for (void** it = pb; it != pe; ++it) {
        CityObj* c = (CityObj*)*it;
        if (!c)
            continue;
        if (c->fieldb20 != 0 && c->fieldb20 != 1)
            continue;
        CityKind* k = FUN_00ca71d0(c);
        if (k->kind != 7)
            continue;
        k = FUN_00ca71d0(c);
        if (k->owner != this)
            continue;
        if (c->fieldb1c == 0)
            bVar2 = true;
        else if (c->fieldb1c == 1)
            bVar16 = true;
    }
    if (bVar2) {
        if (bVar16)
            return (int*)chosen;
        if (!Vector3_NotEqual(&mPosX, kEmpty3))
            return 0;
    }
    bool flag2 = !bVar2;
    bool flag16 = bVar16;
    CityObj* local_30 = 0;
    float local_2c = 0.0f;
    if (flag2 && !flag16) {
        if (Vector3_NotEqual(&mPosX, kEmpty3) &&
            gMathRandom->RandomUint32Uniform(3) == 0)
            flag2 = false;
    }

    CivVec* list = FUN_00bef6c0(mpCivilization);
    int count = (int)((char*)list->e - (char*)list->b) / 4;
    for (int i = 0; i < count; ++i) {
        CityObj* c = (CityObj*)list->b[i];
        int spec = c->specialty;
        if (spec != 0 && spec != 1)
            continue;
        bool near;
        if (flag2) {
            SpaceObj* a = (SpaceObj*)this;
            SpaceObj* b = (SpaceObj*)c;
            void* pa = 0; void* pb2 = 0;
            ((void(__thiscall*)(SpaceObj*, void*))(*(void***)a)[0x58 / 4])(a, &pa);
            int ca = FUN_00b88590(PlanetModel(pa));
            ((void(__thiscall*)(SpaceObj*, void*))(*(void***)b)[0x58 / 4])(b, &pb2);
            int cb = FUN_00b88590(PlanetModel(pb2));
            near = (ca == cb);
        } else {
            near = !(c->posX == kEmpty3[0] && c->posY == kEmpty3[1] &&
                     c->posZ == kEmpty3[2]);
        }
        if (near) {
            void* outa = 0;
            ((void(__thiscall*)(SpaceObj*, void*))(*(void***)((SpaceObj*)this))[0x2c / 4])((SpaceObj*)this, &outa);
            void* outb = 0;
            ((void(__thiscall*)(SpaceObj*, void*))(*(void***)((SpaceObj*)c))[0x2c / 4])((SpaceObj*)c, &outb);
            float d = FUN_00b81470(PlanetModel(outb), outb, outa);
            float scale = FUN_00b7e4d0(PlanetModel(outa));
            float score = (2.0f - d / (scale * kC1)) * kC2;
            if (local_2c < score) {
                local_30 = c;
                local_2c = score;
            }
        }
    }

    if (local_30) {
        int rank = civ->field298;
        int which;
        if (rank >= 2 && !flag2) {
            which = 1;
        } else {
            if (rank < 1)
                return 0;
            if (!flag2)
                return 0;
            which = 0;
        }
        int spec = local_30->specialty;
        if (spec != 4 && spec != -1) {
            if (!FUN_00bdb880(which))
                return 0;
        }
        float fv = FUN_00bf2170(mpCivilization, spec, which);
        if (civ->field4b0 < fv)
            return 0;
        int add = FUN_00bf2100(mpCivilization, local_30->specialty);
        if (add <= 0)
            return 0;
        int spec2 = local_30->specialty;
        Key3 key;
        int* kp = FUN_00bf9770(mpCivilization, (void*)(long)FUN_00c9e6d0(spec2, which));
        key.a = kp[0]; key.b = kp[1]; key.c = kp[2];
        int isTag = (GetCurrentGameMode_s00bd_de70() == (int)(long)&gAppNameTag);
        int* city = FUN_00bddda0(local_30, spec2, which, key, isTag);
        if (!city)
            return 0;
        FUN_00cac000(city, 7, 0);
        civ->field4b0 -= (float)(int)local_2c;
    }
    return (int*)local_30;
}

// @ 0x00bde910
template <> void Vec3<EmptyBubble>::DoInsertValue(EmptyBubble* pos, EmptyBubble* value)
{
    EmptyBubble* end = e;
    if (end != cap) {
        if (pos <= value && value < end)
            value = value + 1;
        if (end) {
            end->f00 = end[-1].f00;
            end->f04 = end[-1].f04;
            end->f08 = end[-1].f08;
            end->f0c = end[-1].f0c;
            end->f10 = end[-1].f10;
        }
        FUN_00c50ad0(pos, e - 1, e);
        *(EmptyBubbleRaw*)pos = *(EmptyBubbleRaw*)value;        ++e;
        return;
    }
    unsigned n = (unsigned)((char*)end - (char*)b) / 0x14;
    EmptyBubble* nb = 0;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0)
            nb = 0;
    }
    if (nb == 0 && n != 0)
        nb = (EmptyBubble*)operator new(n * 0x14, "Simulator", 0, 0, kEastlFile, 0xd1);
    EmptyBubble* p = (EmptyBubble*)FUN_00bda850(b, pos, nb);
    if (p) {
        p->f00 = value->f00; p->f04 = value->f04; p->f08 = value->f08;
        p->f0c = value->f0c; p->f10 = value->f10;
    }
    EmptyBubble* ne = (EmptyBubble*)FUN_00bda850(pos, e, p + 1);
    if (b && *(int*)((char*)b - 4) != 0)
        operator delete[](b);
    b = nb;
    e = ne;
    cap = nb + n;
}

// @ 0x00bdeb10
CityBubble* CityVec50::CopyBack(CityBubble* dst, CityBubble* src)
{
    CityBubble* end = e;
    CityBubble* d = dst;
    CityBubble* s = src;
    while (s != end) {
        *d = *s;
        d = (CityBubble*)((char*)d + 0x50);
        s = (CityBubble*)((char*)s + 0x50);
    }
    e = (CityBubble*)((char*)e + ((int)((char*)dst - (char*)src) / (int)0x50) * 0x50);
    return dst;
}

// @ 0x00bdeb80
void Vec50::DoInsertValue(CityBubble* pos, CityBubble* value)
{
    CityBubble* end = e;
    if (end != cap) {
        if (pos <= value && value < end)
            value = value + 1;
        if (end)
            ((CopyCtorFn)0x00bda7d0)(end, end - 1);
        CityBubble* s = end - 1;
        CityBubble* d = end - 1;
        while (s != pos) {
            s = s - 1;
            d = d - 1;
            *d = *s;
        }
        *pos = *value;
        ++e;
        return;
    }
    unsigned n = (unsigned)((char*)end - (char*)b) / 0x50;
    CityBubble* nb = 0;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0)
            nb = 0;
    }
    if (nb == 0 && n != 0)
        nb = (CityBubble*)operator new(n * 0x50, "Simulator", 0, 0, kEastlFile, 0xd1);
    CityBubble* p = (CityBubble*)FUN_00bdaa00(b, pos, nb);
    if (p)
        ((CopyCtorFn)0x00bda7d0)(p, value);
    CityBubble* ne = (CityBubble*)FUN_00bdaa00(pos, e, p + 1);
    if (b && *(int*)((char*)b - 4) != 0)
        operator delete[](b);
    b = nb;
    e = ne;
    cap = nb + n;
}

// @ 0x00bdecb0
void __stdcall FUN_00bdecb0(CityElem60* b, CityElem60* e)
{
    for (; b < e; b = (CityElem60*)((char*)b + 0x60)) {
        char* p = *(char**)((char*)b + 0x50);
        if (*(int*)((char*)b + 0x58) - (int)p > 1 && p)
            operator delete[](p);
        char* q = *(char**)((char*)b + 0x40);
        if (*(int*)((char*)b + 0x48) - (int)q > 1 && q)
            operator delete[](q);
    }
}

// @ 0x00bded00
void Vec10::DoInsertValue(RunInfo* pos, RunInfo* value)
{
    RunInfo* end = e;
    if (end != cap) {
        if (pos <= value && value < end)
            value = value + 1;
        if (end) {
            end->a = end[-1].a;
            end->b = end[-1].b;
            end->c = end[-1].c;
            end->d = end[-1].d;
        }
        FUN_00edba80(pos, e - 1, e);
        *(RunInfoRaw*)pos = *(RunInfoRaw*)value;
        ++e;
        return;
    }
    unsigned n = (unsigned)((char*)end - (char*)b) / 0x10;
    RunInfo* nb = 0;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0)
            nb = 0;
    }
    if (nb == 0 && n != 0)
        nb = (RunInfo*)operator new(n * 0x10, "Simulator", 0, 0, kEastlFile, 0xd1);
    RunInfo* p = (RunInfo*)FUN_00b115c0(b, pos, nb);
    if (p)
        *p = *value;
    RunInfo* ne = (RunInfo*)FUN_00b115c0(pos, e, p + 1);
    if (b && *(int*)((char*)b - 4) != 0)
        operator delete[](b);
    b = nb;
    e = ne;
    cap = nb + n;
}

// @ 0x00bdee20
void ElevVec::insert(ElevRecord* pos, const ElevRecord& value)
{
    ElevRecord* end = mpEnd;
    if (end == mpCapacity) {
        int n = (int)((char*)end - (char*)mpBegin) / (int)sizeof(ElevRecord);
        int newCap = n != 0 ? n * 2 : 1;
        ElevRecord* buf = 0;
        if (newCap != 0)
            buf = (ElevRecord*)operator_new((uint32_t)newCap * sizeof(ElevRecord));
        ElevRecord* mid = (ElevRecord*)FUN_00bdaa90(mpBegin, pos, buf);
        if (mid != 0) {
            mid->mf0 = value.mf0;
            mid->mf1 = value.mf1;
            mid->mf2 = value.mf2;
            mid->mu0 = value.mu0;
            mid->mu1 = value.mu1;
            mid->mu2 = value.mu2;
            mid->mb0 = value.mb0;
        }
        ElevRecord* newEnd = (ElevRecord*)FUN_00bdaa90(pos, mpEnd,
                                                       (char*)mid + sizeof(ElevRecord));
        ElevRecord* old = mpBegin;
        if (old != 0 && old != mpSentinel)
            operator_delete2(old);
        mpBegin = buf;
        mpEnd = newEnd;
        mpCapacity = (ElevRecord*)((char*)buf + (uint32_t)newCap * sizeof(ElevRecord));
        return;
    }

    ElevRecord* tpos = pos;
    if (pos >= (ElevRecord*)0 && pos < end)
        tpos = (ElevRecord*)((char*)pos + sizeof(ElevRecord));

    if (end != 0) {
        end->mf0 = end[-1].mf0;
        end->mf1 = end[-1].mf1;
        end->mf2 = end[-1].mf2;
        end->mu0 = end[-1].mu0;
        end->mu1 = end[-1].mu1;
        end->mu2 = end[-1].mu2;
        end->mb0 = end[-1].mb0;
    }

    ElevRecord* dst = (ElevRecord*)((char*)mpEnd - sizeof(ElevRecord));
    while (dst != pos) {
        dst = (ElevRecord*)((char*)dst - sizeof(ElevRecord));
        memcpy((char*)dst + sizeof(ElevRecord), dst, sizeof(ElevRecord));
    }
    memcpy(pos, tpos, sizeof(ElevRecord));
    mpEnd = (ElevRecord*)((char*)mpEnd + sizeof(ElevRecord));
}

// @ 0x00bdefa0
void WordVec::insert(uint32_t* pos, uint32_t* first, uint32_t* last)
{
    if (first == last)
        return;
    uint32_t* end = mpEnd;
    uint32_t n = (uint32_t)(end - mpBegin);
    uint32_t count = (uint32_t)(last - first);
    if (count > n) {
        // Grow to max(2n, count+n).
        uint32_t newCap = n * 2 > count + n ? n * 2 : count + n;
        if (n == 0)
            newCap = count + n;
        uint32_t* buf = 0;
        if (newCap != 0)
            buf = (uint32_t*)operator_new(newCap * 4);
        uint32_t* p = (uint32_t*)memcpy(buf, mpBegin, (uint32_t)((char*)pos - (char*)mpBegin));
        FUN_00bdc7b0(p, pos, last, 0, 0);       // copy range after the split
        memcpy((char*)p + (int)((char*)pos - (char*)mpBegin),
               pos, (uint32_t)((char*)end - (char*)pos));
        uint32_t* old = mpBegin;
        if (old != 0 && old[-1] != 0)
            operator_delete2(old);
        *this = WordVec();
        mpBegin = buf;
        mpCapacity = buf + newCap;
        return;
    }
    uint32_t prefix = (uint32_t)((char*)pos - (char*)mpBegin) / 4;
    if (count < prefix) {
        uint32_t* mid = end - count;
        FUN_00bdaa40(this, mid, end, end, last);
        mpEnd = (uint32_t*)((char*)mpEnd + count * 4);
        FUN_00ad8220(first, mid, end);
        FUN_00c8ee40(pos, last, first);
        return;
    }
    uint32_t* mid = mpBegin + (int)count;
    FUN_00bdc7b0(this, mid, last, end, pos);
    mpEnd = (uint32_t*)((char*)mpEnd + (count - prefix) * 4);
    FUN_00bdaa40(this, first, end, mpEnd, pos);
    mpEnd = (uint32_t*)((char*)mpEnd + prefix * 4);
    FUN_00c8eeb0(pos, mid, first + prefix);
}

// @ 0x00bdf170
void __cdecl CopyAssignRange80(CElement_s00bd_ee20* first, CElement_s00bd_ee20* last, const CElement_s00bd_ee20* src)
{
    while (first != last) {
        first->CopyAssignFrom(*src);
        first = (CElement_s00bd_ee20*)((char*)first + 0x80);
    }
}

// @ 0x00bdf1a0
void __cdecl CopyConstructRange80(CElement_s00bd_ee20* first, unsigned count, const CElement_s00bd_ee20* src)
{
    if (count != 0) {
        do {
            if (first != 0)
                first->CopyConstructFrom(*src);
            count--;
            first = (CElement_s00bd_ee20*)((char*)first + 0x80);
        } while (count != 0);
    }
}

// @ 0x00bdf1f0
void CityWrite::Write(void* stream)
{
    Serializer* s = (Serializer*)stream;
    void* sub = s->Resolve();                      // vt[0x20]() -> sub-serializer
    uint32_t tag = 0xee9b2232;
    SubSerializer* subser = (SubSerializer*)sub;
    EA_IO_WriteUint32(subser->GetIO(), &tag, (void*)1, 0);   // vt[0x18]() -> EA::IO

    ((cGameDataT*)this)->Write(stream);
    ((cSpatialObjectT*)((char*)this + 0x120))->Write(stream);
    ((Self00c005b0*)this)->Run(stream);            // 0x00c005b0

    // Insert three map entries (1,2,3) into the cRBT at +0x7b8.
    cRBTT* rbt = (cRBTT*)((char*)this + 0x7b8);
    uint32_t zero = 0;
    uint32_t one = 1;
    rbt->Insert(&zero, &one, &one);
    zero = 0; uint32_t two = 2;
    rbt->Insert(&zero, &two, &two);
    zero = 0; uint32_t three = 3;
    rbt->Insert(&zero, &three, &three);

    // vt[0x2c](self[0x590]).
    s->Send(*(void**)((char*)this + 0x590));

    ((cGonzagoTimerT*)((char*)this + 0x5f8))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x6a0))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x6c8))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x6e8))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x708))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x728))->Write(stream);

    void* p654 = *(void**)((char*)this + 0x654);
    if (p654 != 0) {
        uint32_t* src = (uint32_t*)((char*)p654 + 0x504);
        *(uint32_t*)((char*)this + 0x658) = src[0];
        *(uint32_t*)((char*)this + 0x65c) = src[1];
        *(uint32_t*)((char*)this + 0x660) = src[2];
    } else {
        *(uint32_t*)((char*)this + 0x658) = 0;
        *(uint32_t*)((char*)this + 0x65c) = 0;
        *(uint32_t*)((char*)this + 0x660) = 0;
    }

    char serBuf[0xa18];
    cVarListSerializerT* ser = (cVarListSerializerT*)serBuf;
    ser->ctor(this, (void*)0x0156ea28, 0x01a80d26);
    ser->Serialize(stream);
}

// @ 0x00bdf380
void RelCity::BuildRelationshipString(void* out)
{
    NounManagerT* nm = (NounManagerT*)SP_NounManager();
    void* playerCiv = nm->GetPlayerCivilization();
    uint32_t civ = *(uint32_t*)((char*)this + 0x470);
    float value;
    if (civ != (uint32_t)playerCiv) {
        RelationshipMgrT* mgr = (RelationshipMgrT*)FUN_00b3d2c0((void*)civ, playerCiv, 1);
        value = mgr->GetValue();
    } else {
        value = 10.0f;
    }
    SP_basic_string_sprintf(out, "City\nRelationship To Player = %.1f", (double)value);
}

// @ 0x00bdf3e0
void BubbleVec::push_back()
{
    EmptyBubble_s00bd_ee20* end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = end + 1;
        if (end != 0) {
            end->mRadius = 0.0f;
            end->mSourceID = 0;
        }
        return;
    }
    EmptyBubble_s00bd_ee20 tmp;
    tmp.mRadius = 0.0f;
    tmp.mSourceID = 0;
    DoInsertValue(end, tmp);
}

// @ 0x00bdf430
void* RefElemVec::erase_last(void* pos)
{
    char* cur = (char*)pos + 0xc;
    if (cur < mpEnd)
        FUN_00bda980(cur, mpEnd, pos);
    mpEnd -= 0xc;
    char* last = mpEnd;
    RefCounted* a = *(RefCounted**)(last + 4);
    if (a != 0)
        a->Release();
    RefCounted* b = *(RefCounted**)last;
    if (b != 0)
        b->Release();
    return pos;
}

// @ 0x00bdf480
void RefVec2::insert(RefVecElem* pos, const RefVecElem& value)
{
    RefVecElem* end = mpEnd;
    if (end == mpCapacity) {
        int n = (int)((char*)end - (char*)mpBegin) / 0xc;
        int newCap = n * 2 / 3;            // 0x2aaaaaab magic -> n*2/3? (see disasm)
        // The original expands capacity then adds the new element; capacity
        // math follows eastl's get_new_capacity.
        newCap = n + (n >> 1);
        if (newCap == 0)
            newCap = 1;
        RefVecElem* buf = (RefVecElem*)operator_new((uint32_t)newCap * 0xc);
        // ... (growth path; reconstructed behaviourally, not byte-exact)
        (void)buf;
        return;
    }
    // Fast path.
    RefVecElem* tpos = pos;
    if (pos >= (RefVecElem*)0 && pos < end)
        tpos = (RefVecElem*)((char*)pos + 0xc);
    if (end != 0) {
        end->m_p0 = end[-1].m_p0;
        if (end->m_p0 != 0)
            ((void (__thiscall*)(RefCounted*))end->m_p0->m_vtbl[0])(end->m_p0);
        end->m_p4 = end[-1].m_p4;
        if (end->m_p4 != 0)
            ((void (__thiscall*)(RefCounted*))end->m_p4->m_vtbl[0])(end->m_p4);
        end->m_u8 = end[-1].m_u8;
    }
    FUN_00bdaae0((char*)mpEnd - 0xc, pos, mpEnd);
    FUN_00bda760(tpos, 0);
    mpEnd = (RefVecElem*)((char*)mpEnd + 0xc);
}

// @ 0x00bdf600
void LogReporterVec::do_assign(void** first, void** last, false_type)
{
    void** begin = mpBegin;
    int n = (int)(last - first);
    if ((unsigned)n > (unsigned)(int)(mpCapacity - begin)) {
        void** buf = DoAllocateAndCopy(n, first, last);
        DoDestroyElements(mpBegin, mpEnd);
        if (mpBegin != 0 && mpBegin != mpInline)
            operator_delete2(mpBegin);
        void** e = buf + n;
        mpBegin = buf;
        mpEnd = e;
        mpCapacity = e;
        return;
    }
    int have = (int)(mpEnd - begin);
    if ((unsigned)n <= (unsigned)have) {
        void** newEnd = FUN_006782c0(first, last, begin);
        DoDestroyElements(newEnd, mpEnd);
        mpEnd = newEnd;
        return;
    }
    void** mid = (void**)((char*)first + have * 4);
    FUN_006782c0(first, mid, begin);
    FUN_00829110(mid, &last, last, mpEnd, last);
    mpEnd = last;
}

// @ 0x00bdf6d0
bool IdHost::AddUniqueId(uint32_t id)
{
    IdVec* vec = &mIds;
    bool result = false;
    bool found = false;
    uint32_t* p = mIds.mpBegin;
    uint32_t* e = mIds.mpEnd;
    for (; p != e && !found; ++p)
        found = (*p == id);
    if (!found) {
        vec->push_back(id);
        result = true;
    }
    if (mCount1d8 < 1)
        mCount1d8 = 1;
    return result;
}

// @ 0x00bdf750
void CityFlatten::Flatten5a4(PairVec* dst)
{
    dst->reserve(*(uint32_t*)((char*)this + 0x5b4));
    dst->eraseAt(dst->mpBegin, dst->mpEnd);
    RBNode_s00bd_ee20* node = *(RBNode_s00bd_ee20**)((char*)this + 0x5a8);
    RBNode_s00bd_ee20* sentinel = (RBNode_s00bd_ee20*)((char*)this + 0x5a4);
    while (node != sentinel) {
        uint32_t key = node->mKey;
        uint32_t val = node->mValue;
        if (dst->mpEnd < dst->mpCapacity) {
            uint32_t* slot = (uint32_t*)dst->mpEnd;
            dst->mpEnd = (char*)dst->mpEnd + 8;
            if (slot != 0) {
                slot[0] = key;
                slot[1] = val;
            }
        } else {
            uint32_t tmp[2]; tmp[0] = key; tmp[1] = val;
            dst->DoInsertValue(dst->mpEnd, tmp);
        }
        node = (RBNode_s00bd_ee20*)RBTreeIncrement(node);
    }
}

// @ 0x00bdf7e0
void CityFlatten::Flatten5c0(PairVec* dst)
{
    dst->reserve(*(uint32_t*)((char*)this + 0x5d0));
    dst->eraseAt(dst->mpBegin, dst->mpEnd);
    RBNode_s00bd_ee20* node = *(RBNode_s00bd_ee20**)((char*)this + 0x5c4);
    RBNode_s00bd_ee20* sentinel = (RBNode_s00bd_ee20*)((char*)this + 0x5c0);
    while (node != sentinel) {
        uint32_t val = node->mValue;
        uint32_t key = node->mKey;
        if (val != 0) {
            if (dst->mpEnd < dst->mpCapacity) {
                uint32_t* slot = (uint32_t*)dst->mpEnd;
                dst->mpEnd = (char*)dst->mpEnd + 8;
                if (slot != 0) {
                    slot[0] = key;
                    slot[1] = val;
                }
            } else {
                uint32_t tmp[2]; tmp[0] = key; tmp[1] = val;
                dst->DoInsertValue(dst->mpEnd, tmp);
            }
        }
        node = (RBNode_s00bd_ee20*)RBTreeIncrement(node);
    }
}

// @ 0x00bdf880
void CityFlatten::Flatten5dc(PairVec* dst)
{
    dst->reserve(*(uint32_t*)((char*)this + 0x5ec));
    dst->eraseAt(dst->mpBegin, dst->mpEnd);
    RBNode_s00bd_ee20* node = *(RBNode_s00bd_ee20**)((char*)this + 0x5e0);
    RBNode_s00bd_ee20* sentinel = (RBNode_s00bd_ee20*)((char*)this + 0x5dc);
    while (node != sentinel) {
        uint32_t val = node->mValue;
        uint32_t key = node->mKey;
        if (val != 0) {
            if (dst->mpEnd < dst->mpCapacity) {
                uint32_t* slot = (uint32_t*)dst->mpEnd;
                dst->mpEnd = (char*)dst->mpEnd + 8;
                if (slot != 0) {
                    slot[0] = key;
                    slot[1] = val;
                }
            } else {
                uint32_t tmp[2]; tmp[0] = key; tmp[1] = val;
                dst->DoInsertValue(dst->mpEnd, tmp);
            }
        }
        node = (RBNode_s00bd_ee20*)RBTreeIncrement(node);
    }
}

// @ 0x00bdf920
struct NounObj_00bdf920 {
    virtual void v00(); virtual void Release(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual bool IsPersistent();        // +0x2c
};
struct AutoRef_00bdf920 {
    NounObj_00bdf920* p;
    AutoRef_00bdf920& operator=(NounObj_00bdf920* q)
    {
        if (q != p) {
            NounObj_00bdf920* old = p;
            p = q;
            if (old) old->Release();
        }
        return *this;
    }
    NounObj_00bdf920* operator->() const { return p; }
    operator NounObj_00bdf920*() const { return p; }
};
struct RefElem_00bdf920 { AutoRef_00bdf920 p0; AutoRef_00bdf920 p4; uint32_t u8; };
struct PlanetModel_00bdf920 {
    void RemoveEdge(void* a, void* b);  // 0x00b86790
    void Remove(void* obj);             // 0x00b7e360
};
struct NounMgr_00bdf920 { void RemoveNoun(void* noun); };   // 0x00b225d0
void CreatureHost::RemoveByPointer(void* target)
{
    RefElem_00bdf920* it = *(RefElem_00bdf920**)((char*)this + 0x55c);
    RefElem_00bdf920* end = *(RefElem_00bdf920**)((char*)this + 0x560);
    RefElemVec* vec = (RefElemVec*)((char*)this + 0x55c);
    for (; it != end; ++it)
        if (it->p0.p == target)
            break;
    if (it != end && it->p0.p == target) {
        if (NounObj_00bdf920* p = it->p0.p) {
            it->p0.p = 0;
            p->Release();
        }
        if (SP_PlanetModel()) {
            ((PlanetModel_00bdf920*)SP_PlanetModel())->RemoveEdge(this, target);
            ((PlanetModel_00bdf920*)SP_PlanetModel())->Remove(it->p4);
        }
        if (it->p4 && !it->p4->IsPersistent())
            ((NounMgr_00bdf920*)SP_NounManager())->RemoveNoun(it->p4);
        if (NounObj_00bdf920* p = it->p4.p) {
            it->p4.p = 0;
            p->Release();
        }
        vec->erase_last(it);
    }
}

// @ 0x00bdf9e0
void* CreatureHost::RemoveById(uint32_t id)
{
    RefElemVec* vec = (RefElemVec*)((char*)this + 0x55c);
    char* it = vec->mpBegin;
    void* result = 0;
    if (it == vec->mpEnd)
        return 0;
    do {
        IdObject* obj = *(IdObject**)it;
        if (obj == 0 || obj->GetId() != id) {
            it += 0xc;
            continue;
        }
        result = *(void**)it;
        if (result != 0) {
            *(void**)it = 0;
            ((RefCounted*)result)->Release();
        }
        if (SP_PlanetModel() != 0) {
            FUN_00b86790(this, result);
            FUN_00b7e360(*(void**)(it + 4));
        }
        RefCounted* p4 = *(RefCounted**)(it + 4);
        if (p4 != 0) {
            if (!((bool (*)(void*))((void**)p4->m_vtbl)[0x2c / 4])(p4)) {
                void* nm = SP_NounManager();
                SP_cGameNounManager_RemoveNoun(nm, p4);
            }
        }
        RefCounted* p4b = *(RefCounted**)(it + 4);
        if (p4b != 0) {
            *(void**)(it + 4) = 0;
            p4b->Release();
        }
        // Erase this element (shift the tail down, then release the last).
        char* next = it + 0xc;
        char* end = vec->mpEnd;
        if (next < end)
            FUN_00bda980(next, end, it);
        vec->mpEnd -= 0xc;
        char* last = vec->mpEnd;
        RefCounted* a = *(RefCounted**)(last + 4);
        if (a != 0) a->Release();
        RefCounted* b = *(RefCounted**)last;
        if (b != 0) b->Release();
        ((CreatureHost*)result)->RemoveByPointer(this);   // FUN_00bdf920(ecx=obj, arg=self)
        break;
    } while (it != vec->mpEnd);
    return result;
}

// @ 0x00bdfb00
uint32_t __fastcall DamageCombatantsInRadius(void* self, void* entity, void* outTransform)
{
    void* slotVec[14];
    void** begin = slotVec;
    void** end = slotVec;

    uint32_t slot = (uint32_t)FUN_00afad30((char*)self + 0x3ec, entity);
    if (slot == 0xffffffff) {
        goto cleanup_false;
    }
    {
        uint32_t i = 0;
        do {
            if (i != slot &&
                *(char*)(*(int*)((char*)self + 0x324) + slot * 0xe + 0x274 + i) != 0) {
                void* s = FUN_00af9ff0((char*)self + 0x3ec, i);
                if (s != 0) {
                    void* o = FUN_00fcc210(s);
                    if (o != 0) {
                        void* q = ((void* (*)(void*, uint32_t))((void**)*(void**)o)[0xc / 4])(*(void**)o, 0xe9cb8ba);
                        if (q != 0) {
                            if ((char*)end < (char*)slotVec + sizeof(slotVec)) {
                                *end = q;
                                end++;
                            } else {
                                FUN_00cd0550(end, &q);
                            }
                        }
                    }
                }
            }
            i++;
        } while (i < 0xe);
    }
    if (begin == end) {
        goto cleanup_false;
    }
    {
        float* p = (float*)((void* (*)(void*))((void**)*(void**)entity)[0x2c / 4])(entity);
        // The original reads *entity's sub-object at +0x34, vt[0x2c]() -> Vec3.
        float base[3];
        base[0] = p[0]; base[1] = p[1]; base[2] = p[2];
        uint32_t n = (uint32_t)(end - begin);
        uint32_t idx = (uint32_t)EA_Random_RandomUint32Uniform((void*)0x01601760, n);
        void* chosen = begin[idx];
        float* q = (float*)(void* (*)(void*))((void**)*(void**)chosen)[0x2c / 4];

        float dx = q[0] - base[0];
        float dy = q[1] - base[1];
        float dz = q[2] - base[2];
        float inv = 1.0f / (float)sqrt((double)(dx*dx + dy*dy + dz*dz + 1e-8f));
        float dir[3];
        dir[0] = inv * dx;
        dir[1] = dy * inv;
        dir[2] = dz * inv;

        float* m = (float*)SP_cPlanetModel_BuildSurfaceOrientation2(SP_PlanetModel(), dir);
        uint32_t* out = (uint32_t*)outTransform;
        out[0] = *(uint32_t*)&m[0];
        out[1] = *(uint32_t*)&m[1];
        out[2] = *(uint32_t*)&m[2];
        out[3] = *(uint32_t*)&m[3];
    }
    if (begin != 0 && begin != slotVec)
        operator_delete2(begin);
    return 1;

cleanup_false:
    if (begin != 0 && begin != slotVec)
        operator_delete2(begin);
    return 0;
}

// @ 0x00bdfd30
void cCommunity_s00bd_fd30::EmitBubbles()
{
    AddSpecialBubbles();
    if (!mHost)
        return;
    Vec3_s00bd_fd30 p = *mHost->GetPos();
    mBubbles.push_back(EmptyBubble_s00bd_fd30(p.x, p.y, p.z, 8.0f, 0));
    mBubbles.push_back(EmptyBubble_s00bd_fd30(p.x, p.y, p.z, 8.0f, 0));
    mBubbles.push_back(EmptyBubble_s00bd_fd30(p.x, p.y, p.z, 8.0f, 0));
    mBubbles.push_back(EmptyBubble_s00bd_fd30(p.x, p.y, p.z, 8.0f, 0));
    mBubbles.push_back(EmptyBubble_s00bd_fd30(m51c, m520, m524, 8.0f, 0));
}

// @ 0x00bdff50
void cCommunity_s00bd_fd30::EmitBubbleAt(const Vec3_s00bd_fd30* p, float w, int id)
{
    GameTime* t = GameTimeQuery();                   // 0x00b3d480
    if (t->IsPlayer(this))                           // 0x00ac8d60
    {
        EmptyBubble_s00bd_fd30 b;
        b.w = 0.0f;
        b.id = 0;
        mBubbles2.push_back(b);
        EmptyBubble_s00bd_fd30* d = mBubbles2.mpEnd - 1;
        d->x = p->x;
        d->y = p->y;
        d->z = p->z;
        d->w = w;
        d->id = id;
        return;
    }
    if (id == GetPlayerEmpireID_s00bd_fd30())                   // 0x01021090
        EndThisPlayer();                             // 0x00bdbf10
}

// @ 0x00be0020
void cCombatLinks::BuildLinks()
{
    mLinks.erase(mLinks.mpBegin, mLinks.mpEnd);
    unsigned total = (unsigned)(mEntriesEnd - mEntriesBegin);
    const unsigned& cnt = (total > 14) ? kMaxEntries : total;
    int n = (int)cnt;
    if (n == 0)
        return;
    for (int i = 0; i < n - 1; i++) {
        Object* oa = mEntriesBegin[i].Get();
        if (!oa)
            continue;
        Host* ha = oa->QueryInterface(0xe9cb8ba);
        if (!ha)
            continue;
        if (ha->cmb.GetDamageState() == 2)
            continue;
        for (int j = i + 1; j < n; j++) {
            if (!mMatrix->mat[i * 14 + j])
                continue;
            if (!mEntriesBegin[j].flag)
                continue;
            Object* ob = mEntriesBegin[j].Get();
            if (!ob)
                continue;
            Host* hb = ob->QueryInterface(0xe9cb8ba);
            if (!hb)
                continue;
            if (hb->cmb.GetDamageState() == 2)
                continue;

            float f0 = 0.0f, f1 = 0.0f, f2 = 0.0f, f3 = 0.0f, f4 = 0.0f, f5 = 0.0f;
            uint32_t ta = ha->GetType();
            uint32_t tb = hb->GetType();
            bool ba = (ta == 0x18ea1eb || ta == 0x18eb106);
            bool bb = (tb == 0x18ea1eb || tb == 0x18eb106);
            if (ta == 0x18ea2cc) {
                if (bb) {
                    f0 = 1.0f;
                    goto L224;
                }
                if (tb != 0x1a56aba)
                    goto L224;
                f2 = 1.0f;
            L24e:
                if (ba)
                    f4 = 1.0f;
            } else {
                if (ta == 0x1a56aba && bb)
                    f1 = 1.0f;
            L224:
                if (tb == 0x18ea2cc) {
                    if (ba)
                        f3 = 1.0f;
                    else if (ta == 0x1a56aba)
                        f5 = 1.0f;
                } else if (tb == 0x1a56aba) {
                    goto L24e;
                }
            }

            mLinks.push_back();
            Link* l = mLinks.mpEnd - 1;
            l->a = i;
            l->b = j;
            l->f0 = f0; l->f1 = f1; l->f2 = f2; l->f3 = f3; l->f4 = f4; l->f5 = f5;

            Vec3_s00bd_fd30 pa = *ha->pos.GetPos();
            Vec3_s00bd_fd30 pb = *hb->pos.GetPos();
            Vec3_s00bd_fd30 d1 = Vec3_s00bd_fd30(pb.x - pa.x, pb.y - pa.y, pb.z - pa.z);
            l->da = Normalized(d1);
            l->pa.x = pa.x + l->da.x;
            l->pa.y = l->da.y + pa.y;
            l->pa.z = l->da.z + pa.z;
            Vec3_s00bd_fd30 d2 = Vec3_s00bd_fd30(pa.x - pb.x, pa.y - pb.y, pa.z - pb.z);
            l->db = Normalized(d2);
            l->pb.x = pb.x + l->db.x;
            l->pb.y = l->db.y + pb.y;
            l->pb.z = l->db.z + pb.z;

            PointVec* pts = ha->GetPoints();
            PointVec* nrm = ha->GetNormals();
            if (pts->mpBegin != pts->mpEnd) {
                int k = NearestIndex(pts, &pb);
                Vec3_s00bd_fd30 p = pts->mpBegin[k];
                Vec3_s00bd_fd30 q = nrm->mpBegin[k];
                l->pa = p;
                l->da = q;
            }
            PointVec* pts2 = hb->GetPoints();
            PointVec* nrm2 = hb->GetNormals();
            if (pts2->mpBegin != pts2->mpEnd) {
                int k = NearestIndex(pts2, &pa);
                Vec3_s00bd_fd30 p = pts2->mpBegin[k];
                Vec3_s00bd_fd30 q = nrm2->mpBegin[k];
                l->pb = p;
                l->db = q;
            }
        }
    }
}

// @ 0x00be06c0
void cAnalysisOwner::AddAnalysis(const AnalysisInfo& a, long long delta)
{
    GTClock* g = GameTimeManager_s00bd_fd30();
    long long now = g->Now();
    m7f8.push_back(a);
    *(long long*)((char*)m7f8.mpEnd - 0x18) = now + delta;
}

// @ 0x00be0730
void RefVec2_s00bd_fd30::AddDefault()
{
    if (mpEnd < mpCap) {
        RefVecElem_s00bd_fd30* p = mpEnd;
        mpEnd = mpEnd + 1;
        if (p) {
            p->mpA = 0;
            p->mpB = 0;
        }
        return;
    }
    RefVecElem_s00bd_fd30 v;
    v.mpA = 0;
    v.mpB = 0;
    insert(mpEnd, v);
    if (v.mpB)
        v.mpB->v01();
    if (!v.mpA)
        return;
    return v.mpA->v01();
}

// @ 0x00be0790
int* IntMap::GetOrInsert(const int* key)
{
    MapNode* header = &mHead;                         // +4
    MapNode* lb = header;
    MapNode* node = mHead.mpParent;                   // root at +0xc
    while (node) {
        if (node->mKey < *key) {
            node = node->mpLeft;
        } else {
            lb = node;
            node = node->mpRight;
        }
    }
    if (lb != header && *key <= lb->mKey)
        return (int*)(lb->mVal);
    int kv[2];
    kv[0] = *key;
    kv[1] = 0;
    int* out = (int*)((unsigned)key & 0xffffff00u);
    DoInsert(&out, lb, kv, (int)(intptr_t)out);       // 0x00de6a60
    return (int*)((char*)out + 0x14);
}

// @ 0x00be0b90
void RebuildAnalysisFromStream(IStreamProvider* owner, AnalysisVec* vec)
{
    vec->erase(vec->mpBegin, vec->mpEnd);
    unsigned count = 0;
    EA::IO::IStream_s00bd_fd30* s = (EA::IO::IStream_s00bd_fd30*)owner->GetStream()->V18();
    EA::IO::ReadInt32(s, &count, 1, 0);
    vec->resize(count);
    for (unsigned i = 0; i < count; i++) {
        AnalysisInfo a;
        cVarListSerializer ser(a.w, &g_156e880, 0x1a80d26);
        ser.Read(owner);
        vec->push_back(a);
    }
    owner->Close();
}

// @ 0x00be0c80
bool RemoveItem(PtrVec2* vec, int** key)
{
    for (int** it = vec->mpBegin; it != vec->mpEnd; ++it) {
        if (*it == *key) {
            if (it + 1 < vec->mpEnd)
                MoveOverlap(it + 1, vec->mpEnd, it);        // 0x00ae6880
            vec->mpEnd = vec->mpEnd - 1;
            AutoRefObj* e = (AutoRefObj*)*vec->mpEnd;
            if (e)
                e->v25();
            return true;
        }
    }
    return false;
}

// @ 0x00be0d70
InfoRec::InfoRec(const InfoRec& o)
: pos(o.pos)
{
    unsigned n = (unsigned)(o.v.mpEnd - o.v.mpBegin);
    v.DoAllocate(n, o.v.mAllocState);                 // 0x004aa350
    memcpy(v.mpBegin, o.v.mpBegin, n * 4);
    v.mpEnd = v.mpBegin + n;
}

// @ 0x00be0dd0
void CopyInfoRecs(InfoRec* first, InfoRec* last, InfoRec* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst) {
            dst->pos = first->pos;
            unsigned n = (unsigned)(first->v.mpEnd - first->v.mpBegin);
            float* p = n ? (float*)operator_new_simulator(n * 4) : 0;   // 0x00f473a0
            dst->v.mpBegin = p;
            dst->v.mpEnd = p;
            dst->v.mpCap = p + n;
            memcpy(p, first->v.mpBegin, (char*)first->v.mpEnd - (char*)first->v.mpBegin);
            dst->v.mpEnd = p + n;
        }
    }
}

// @ 0x00be0e80
InfoRec* CopyInfoRecsFwd(InfoRec* first, InfoRec* last, InfoRec* dst)
{
    for (; first != last; ++first, ++dst)
        *dst = *first;
    return dst;
}

// @ 0x00be0ed0
InfoRec* CopyInfoRecsBwd(InfoRec* first, InfoRec* last, InfoRec* dst)
{
    while (last != first) {
        --last;
        --dst;
        *dst = *last;
    }
    return dst;
}

// @ 0x00be0f20
void SimData::RemoveOwner()
{
    memcpy(m1e0, m1e4, 0);
    m1e4 += (m1e0 - m1e4);
    VectorEraseAutoRef(m1f4, m1f8);                  // 0x00e25bd0
    FUN_00c3f2d0(m208, 0);
    cGameNounManager_s00bd_fd30* nm = NounManager_s00bd_fd30();            // 0x00b3d300
    nm->RemoveNoun(m208);                            // 0x00b225d0
    if (m208) {
        void* old = m208;
        m208 = 0;
        (*(void (**)(void))((*(int*)old) + 4))();
    }
    m100.Clear();
    FUN_00bfc720(m38);                               // tail call
}

// @ 0x00be0fc0
bool SimData::AddOwner(int* p)
{
    bool result = false;
    if (p) {
        int* q = (int*)(*(void** (__thiscall*)(void*, int))(*(int*)p + 0xc))(p, 0x137e8e0);
        if (q) {
            bool found = false;
            int** it = (int**)m1f4;
            int** end = (int**)m1f8;
            while (it != end) {
                if (found)
                    return result;
                found = (*it == q);
                ++it;
            }
            if (!found) {
                (*(void (**)(void))(*q))();
                if ((int*)m1f8 < (int*)m1fc) {
                    int* slot = (int*)m1f8;
                    m1f8 = (int*)((char*)m1f8 + 4);
                    if (slot) {
                        *slot = (int)q;
                        (*(void (**)(void))(*q))();
                    }
                } else {
                    SPVectorDoInsertPtr((void**)&m1f8, q);   // 0x00aea5d0
                }
                if (q)
                    (*(void (**)(void))((*q) + 4))();
                result = true;
            }
        }
    }
    if (m1d8 != 0) {
        if (m1f4 == m1f8) {
            m1d8 = 1;
            m1dc = -1;
            return result;
        }
        m1d8 = 2;
        int e = *m1f4;
        m1dc = (*(int (**)(void))((*(int*)(e + 0x508)) + 0x10))();
    }
    return result;
}

// @ 0x00be10d0
void cSPPlanetNoun::ResetLog()
{
    mnLogA = 0;
    mnLogB = -1;
    void* end = mpA1e4;
    void* begin = mpA1e0;
    memcpy(begin, end, 0);                       // retail: size = (char*)end - (char*)end == 0
    mpA1e4 = (char*)end - ((char*)end - (char*)begin);
    mLogVec1f4.erase(mLogVec1f4.mpBegin, mLogVec1f4.mpEnd);
    mf20c = 0.0f;
    mf210 = 0.0f;
    mn214 = 0;
}

// @ 0x00be1150
void cSPPlanetNoun::SetLog(void* r)
{
    void* old = mpLog590;
    if (r != old) {
        addref(r);
        mpLog590 = r;
        relref(old);
    }
    if (r != 0) {
        if (map1.mnSize == 0) {
            int id = VGETID(mpLog590);
            int v = mn64c;
            map1[id] = v;
            ((PendingObj*)SP_PendingObject())->ac8cd0(this, 1);
        }
        ((void(__thiscall*)(cSPPlanetNoun*, int))((void**)*(void***)this)[0x48 / 4])(this, VGETID(mpLog590));
    }
}

// @ 0x00be11f0
void cSPPlanetNoun::Tick1()
{
    u64_s00be_10d0 t = mTimer5f8.GetElapsedTime();
    double elapsed = (double)t;
    if (!(elapsed > (double)kTickThreshold))
        return;
    mTimer5f8.Restart();
    int base = VGETID(mpLog590);
    IntMapNode* anchor = (IntMapNode*)&map1.mAnchor;     // +0x5a4
    for (IntMapNode* node = (IntMapNode*)map1.mAnchor.mpNodeLeft; node != anchor;
         node = (IntMapNode*)FUN_00921580(node)) {
        int key = node->mKey;
        int* val = &node->mValue;
        if (key != base && *val >= 1) {
            void* nobj = ((SP::cGameNounManager_s00be_10d0*)SP_NounManager())->GetNoun(key);
            if (nobj == 0) {
                map1[base] += *val;
                *val = 0;
            } else {
                u32 out = 0;
                kCeeder->ceed50(this, &out);
                if ((int)out > 0) {
                    int take = (int)out;
                    if (take > *val)
                        take = *val;
                    map1[base] += take;
                    map3[key] += take;
                    *val -= take;
                    ((PendingObj*)SP_PendingObject())->ac8cd0(this, 0);
                }
            }
        }
    }
}

// @ 0x00be1340
int cSPPlanetNoun::Activate(cSPPlanetNoun* other, int flag)
{
    VGETID(mpLog590);
    int otherId = VGETID(other->mpLog590);
    int* found = (int*)FUN_00e39fb0(&mTree570, &otherId);
    if (*(void**)found == (void*)&mTree570.mAnchor) {
        float* slot = (float*)FUN_00be0790(&mTree570, &otherId);
        *slot = 0.0f;
    }
    if (SP_PlanetModel() != 0 && flag == 0) {
        Vec3_s00be_10d0 pa, pb;
        Vec3_s00be_10d0* r = (Vec3_s00be_10d0*)((void*(__thiscall*)(cSPPlanetNoun*, Vec3_s00be_10d0*))((void**)*(void***)this)[0x58 / 4])(this, &pa);
        int ca = (int)FUN_00b88590(SP_PlanetModel(), r);
        Vec3_s00be_10d0* r2 = (Vec3_s00be_10d0*)((void*(__thiscall*)(cSPPlanetNoun*, Vec3_s00be_10d0*))((void**)*(void***)other)[0x58 / 4])(other, &pb);
        int cb = (int)FUN_00b88590(SP_PlanetModel(), r2);
        if (ca != cb) {
            Vec3_s00be_10d0 va = mPos32c;                    // a-side position (fStack_30/2c/28)
            Vec3_s00be_10d0 vb = other->mPos32c;             // b-side position (fStack_3c/38/34)
            if ((va.x == kOrigin.x && va.y == kOrigin.y && va.z == kOrigin.z) ||
                FUN_0041dd30(&vb, &kOrigin) == 0) {
                flag = 2;
            } else {
                Vec3_s00be_10d0 na, nb;
                Vec3_s00be_10d0* pf = (Vec3_s00be_10d0*)FUN_00bd9480(this, &na);
                na.x = mPos32c.x - pf->x;
                na.y = mPos32c.y - pf->y;
                na.z = mPos32c.z - pf->z;
                Vec3_s00be_10d0* nn = (Vec3_s00be_10d0*)FUN_00436ce0(&na, &nb);
                va.x = nn->x * 15.0f + va.x;
                va.y = nn->y * 15.0f + va.y;
                va.z = nn->z * 15.0f + va.z;
                Vec3_s00be_10d0* qf = (Vec3_s00be_10d0*)FUN_00bd9480(other, &nb);
                na.x = other->mPos32c.x - qf->x;
                na.y = other->mPos32c.y - qf->y;
                na.z = other->mPos32c.z - qf->z;
                Vec3_s00be_10d0* qn = (Vec3_s00be_10d0*)FUN_00436ce0(&na, &nb);
                vb.x = qn->x * 15.0f + vb.x;
                vb.y = qn->y * 15.0f + vb.y;
                vb.z = qn->z * 15.0f + vb.z;
                int ia = (int)FUN_00b88590(SP_PlanetModel(), &va);
                int ib = (int)FUN_00b88590(SP_PlanetModel(), &vb);
                flag = (ia != ib) + 1;
            }
        }
    }
    void* obj = 0;
    if (flag == 0) {
        void* n = FUN_00b20c60(0x2b8a4e7);
        if (n != 0) {
            void* x = ((void*(__thiscall*)(void*, u32))((void**)*(void***)n)[0x0c / 4])(n, 0x2bca14b);
            obj = x;
            if (x != 0)
                FUN_00c41c60(this, other, 1);
        }
    }
    FUN_00be0730(&mRefVec55c);
    RefVec2Elem* endA = mRefVec55c.mpEnd;
    {
        RefVec2Elem* slotA = endA - 1;
        void* old = slotA->p0;
        if (slotA->p0 != (void*)this) {
            addref(this);
            slotA->p0 = this;
            relref(old);
        }
        void* old2 = slotA->p4;
        if (obj != old2) {
            addref(obj);
            slotA->p4 = obj;
            relref(old2);
        }
        slotA->f8 = flag;
    }
    FUN_00be0730(&other->mRefVec55c);
    RefVec2Elem* endB = other->mRefVec55c.mpEnd;
    {
        RefVec2Elem* slotB = endB - 1;
        void* old = slotB->p0;
        if (slotB->p0 != (void*)this) {
            addref(this);
            slotB->p0 = this;
            relref(old);
        }
        void* old2 = slotB->p4;
        if (obj != old2) {
            addref(obj);
            slotB->p4 = obj;
            relref(old2);
        }
        slotB->f8 = flag;
    }
    if (SP_PlanetModel() != 0) {
        if (flag == 0)
            FUN_00b8d420(endA[-1].p4);
        else if (flag == 1)
            FUN_00b86650(this, other);
        else if (flag == 2)
            FUN_00b866f0(this, other);
    }
    char a = *(char*)(*(int*)((char*)this + 0x590) + 0x89);
    int ol = *(int*)((char*)other + 0x590);
    void* k1; void* k2;
    if (a == 0) {
        if (*(char*)(ol + 0x89) == 0)
            return flag;
        k1 = *(void**)((char*)this + 0x590 + 0x40);
        k2 = *(void**)((char*)FUN_00b25fb0() + 0x40);
    } else {
        if (*(char*)(ol + 0x89) == 0) {
            k1 = *(void**)(ol + 0x40);
            k2 = *(void**)((char*)FUN_00b25fb0() + 0x40);
        } else {
            return flag;
        }
    }    {
        Vec3_s00be_10d0 zero = { 0.0f, 0.0f, 0.0f };
        void* key;
        FUN_00bef950(&zero);
        void* p = FUN_00bef950(&zero);
        void* civ = FUN_00b25fb0();
        FUN_00e3c7c0((void*)0x3f5a88f8, (u32)p);
    }
    (void)k1; (void)k2; (void)obj;
    return flag;
}

// @ 0x00be1820
void cSPPlanetNoun::OnNoun(int id)
{
    void* n = ((SP::cGameNounManager_s00be_10d0*)SP_NounManager())->GetNoun(id);
    if (n == 0)
        return;
    void* d = this->FUN_00bd92d0(n);
    if (d == 0)
        return;
    Activate((cSPPlanetNoun*)d, 0);
}

// @ 0x00be1e80
void cSPPlanetNoun::PushVec308(void* r)
{
    if (r == 0)
        return;
    addref(r);
    PtrVec& v = mVec308;
    void** end = v.mpEnd;
    if (end < v.mpCapacity) {
        v.mpEnd = end + 1;
        if (end != 0) {
            *end = r;
            addref(r);
        }
    } else {
        void* tmp = r;
        v.DoInsertPtr(end, tmp);
        r = tmp;
    }
    relref(r);
}

// @ 0x00be1ef0
void cSPPlanetNoun::PushVec340(void* r, int flag)
{
    void* tmp = r;
    if (r != 0)
        addref(r);
    void** end = mVec340.mpEnd;
    if (end < mVec340.mpCapacity) {
        mVec340.mpEnd = end + 1;
        if (end != 0) {
            *end = r;
            if (r == 0)
                goto done;
            addref(r);
        }
    } else {
        mVec340.DoInsertPtr(end, tmp);
        tmp = r;
    }
    relref(tmp);
done:
    mFlag6c = 1;
    if (r != 0) {
        HolderObj* holder = (HolderObj*)(void*)vt1p(r, 3, (void*)0x135b1e8);
        if (holder != 0) {
            void* old = holder->mpOwner;
            if (old != this) {
                addref(this);
                holder->mpOwner = this;
                if (old != 0)
                    relref(old);
            }
        }
    }
    if (flag == 0)
        FUN_00bdbbb0(this);
}

// @ 0x00be1fb0
void* cSPPlanetNoun::MakeNoun()
{
    void* n = ((SP::cGameNounManager_s00be_10d0*)SP_NounManager())->CreateNoun(0x436f342);
    if (n == 0)
        return 0;
    void* esi = ((void*(__thiscall*)(void*, u32))((void**)*(void***)n)[0x0c / 4])(n, 0x436f315);
    if (esi != 0) {
        void* tmp = esi;
        addref(esi);
        void** end = mVec354.mpEnd;
        if (end < mVec354.mpCapacity) {
            mVec354.mpEnd = end + 1;
            if (end != 0) {
                *end = esi;
                addref(esi);
            }
        } else {
            mVec354.DoInsertPtr(end, tmp);
            tmp = tmp;
        }
        relref(tmp);
        ((NounObj*)esi)->FUN_00bd2310(this);
        NounObj* obj = (NounObj*)esi;
        SubVObj* sub34 = &obj->mSub34;
        void* sub34vt = sub34->mpVtbl;
        void* r = ((MF0B)((void**)mSub120.mpVtbl)[0x2c / 4])(&mSub120);
        ((MF0E)((void**)sub34vt)[0x38 / 4])(sub34, r);
    }
    return esi;
}

// @ 0x00be30e0
void cSlotVector::Insert(uint8_t* pPos, const uint8_t* pValue)
{
    if (mpEnd == mpCap) {
        int32_t nCount = (int32_t)(mpEnd - mpBegin) >> 7;
        int32_t nNewCount = nCount > 0 ? nCount * 2 : 1;
        uint8_t* pNew = 0;
        if (nNewCount != 0)
            pNew = (uint8_t*)operator_new((uint32_t)nNewCount << 7, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        uint8_t* pBegin = mpBegin;
        uint8_t* pSplit = (uint8_t*)SlotCopyRange(pBegin, pPos, pNew);
        SlotDestroyRange(pBegin, pPos, pNew);
        if (pSplit != 0)
            SlotConstruct((void*)pValue);
        uint8_t* pResult = (uint8_t*)SlotCopyRange(pPos, mpEnd, pSplit + 0x80);
        SlotDestroyRange(pPos, mpEnd, pSplit + 0x80);
        if (pBegin && ((int32_t*)pBegin)[-1] != 0)
            operator_delete_array(pBegin);
        mpBegin = pNew;
        mpEnd = pResult;
        mpCap = pNew + ((uint32_t)nNewCount << 7);
        return;
    }
    uint8_t* pSource = (uint8_t*)pValue;
    if (pPos <= pValue && pValue < mpEnd)
        pSource = (uint8_t*)pValue + 0x80;
    if (mpEnd != 0)
        SlotDestroy(mpEnd - 0x80);
    SlotMoveBackward(pPos, mpEnd - 0x80, mpEnd);
    SlotConstruct(pSource);
    mpEnd = mpEnd + 0x80;
}

// @ 0x00be3230
bool cAgentAction::RemoveID(uint32_t nID)
{
    bool bResult = false;
    int32_t nCount = (int32_t)((uint8_t*)mpIDs1e4 - (uint8_t*)mpIDs1e0) >> 2;
    if (nCount > 0) {
        int32_t nIndex = -1;
        for (int32_t i = 0; i < nCount; ++i) {
            if (mpIDs1e0[i] == nID)
                nIndex = i;
        }
        if (nIndex >= 0) {
            for (int32_t i = nIndex; i < nCount - 1; ++i)
                mpIDs1e0[i] = mpIDs1e0[i + 1];
            mpIDs1e4 = (uint32_t*)((uint8_t*)mpIDs1e4 - 4);
            bResult = true;
        }
    }
    if (mpIDs1e4 == mpIDs1e0)
        FUN_00be10d0();
    return bResult;
}

// @ 0x00be32b0
void cAgentAction::IncrementCounter()
{
    if (mField64c > 99) {
        return;
    }
    ++mField64c;
    if (mpField590)
        ++*mMap5a0[mpField590->v04c()];
}

// @ 0x00be32f0
void cAgentAction::IncrementCounterBy(int32_t nTimes)
{
    if (nTimes > 0) {
        for (int32_t i = nTimes; i != 0; --i) {
            if (mField64c > 99)
                continue;
            ++mField64c;
            if (mpField590)
                ++*mMap5a0[mpField590->v04c()];
        }
    }
}

// @ 0x00be3350
bool cAgentAction::RemoveAgent(void* pAgent)
{
    bool bResult = false;
    void** pEnd = mAgents340.mpEnd;
    void** it = mAgents340.mpBegin;
    if (it != pEnd) {
        do {
            if (*it == pAgent)
                break;
            ++it;
        } while (it != pEnd);
        if (it != pEnd) {
            if (it + 1 < mAgents340.mpEnd)
                eastl_copy_impl(it + 1, mAgents340.mpEnd, it);
            mAgents340.mpEnd = mAgents340.mpEnd - 1;
            cNoun* pRemoved = (cNoun*)*mAgents340.mpEnd;
            if (pRemoved)
                pRemoved->v004();
            mCircleA3ec.RemoveAgent(pAgent);
            bResult = true;
        }
    }
    FUN_00be2440(this, 0, 0);
    return bResult;
}

// @ 0x00be33e0
void cAgentAction::DestroyAgent(cNoun* pNoun)
{
    if (!pNoun)
        return;
    pNoun->v000();
    SP_NounManager(pNoun)->RemoveNoun();
    RemoveAgent(pNoun);
    pNoun->v004();
}

// @ 0x00be3420
void cAgentAction::DestroyAgentsOfType(uint32_t nUnused, int32_t nType)
{
    (void)nUnused;
    int32_t nCount = (int32_t)((uint8_t*)mAgents340.mpEnd - (uint8_t*)mAgents340.mpBegin) >> 2;
    for (int32_t i = 0; i < nCount; ++i) {
        cNoun* pNoun = (cNoun*)mAgents340.mpBegin[i];
        if ((int32_t)pNoun->GetTypeID() == nType && !pNoun->IsSpecial()) {
            pNoun->v000();
            SP_NounManager(pNoun)->RemoveNoun();
            RemoveAgent(pNoun);
            pNoun->v004();
            return;
        }
    }
}

// @ 0x00be34a0
void cAgentAction::RemoveSlotAgent(cNoun* pNoun)
{
    cNoun* pResult;
    FUN_00d5aae0(mField308, (void**)&pResult, pNoun);
    cNoun* pAgent = pResult;
    mCircleB450.RemoveAgent(pAgent);
    SP_NounManager(pAgent)->RemoveNoun();
}

// @ 0x00be34e0
void cAgentAction::RemoveAgentAndFlag(cNoun* pNoun)
{
    if (RemoveAgent(pNoun))
        mField6c = 1;
}

// @ 0x00be3500
bool cAgentAction::SpawnAgent(cNoun* pNoun, bool bNotify)
{
    void* pSlot = mCircleA3ec.FindSlot(pNoun->mSpatial.GetPosition());
    if (!pSlot)
        return false;

    FUN_00afa030(pSlot, pNoun);

    cVec3 position;
    position.x = *(float*)((uint8_t*)pSlot + 0x0c);
    position.y = *(float*)((uint8_t*)pSlot + 0x10);
    position.z = *(float*)((uint8_t*)pSlot + 0x14);
    pNoun->mSpatial.SetPosition(&position);

    cVec3 normal;
    cVec3 out;
    if (pNoun->GetTypeID() == 0x18ea1eb) {
        out = *(cVec3*)mComponent120.v05c(&out);
    } else if (mField7f4 == 1) {
        cVec3* pOrigin = mComponent120.GetPosition();
        normal.x = pOrigin->x - position.x;
        normal.y = pOrigin->y - position.y;
        normal.z = pOrigin->z - position.z;
        SP_NormalizedSafe(&normal, &out);
    } else if (mField7f4 == 2) {
        mComponent120.v05c(&out);
        FUN_009360d0();
        SP_NormalizedSafe(&out, &normal);
        mComponent120.v05c(&normal);
    }
    cMat4 orientation;
    pNoun->mSpatial.SetOrientation(SP_PlanetModel(&out, &normal, &orientation)->BuildSurfaceOrientation2());
    if (bNotify)
        FUN_00be2440(this, 0, 0);
    return true;
}

// @ 0x00be3720
void __stdcall AgentCommand(uint32_t nAction, uint32_t nA, uint32_t nB, uint32_t nC)
{
    cPtrList list;
    list.mpBegin = 0;
    list.mpEnd = 0;
    list.mpCap = 0;
    switch (nAction) {
    case 0x4e3f7777: FUN_00be2b10((const char*)0x18eb106, &list); break;
    case 0x99e92f05: FUN_00be2b10((const char*)0x18ea1eb, &list); break;
    case 0x47c10953: FUN_00be2b10((const char*)0x18ea2cc, &list); break;
    case 0x72c49181: FUN_00be2b10((const char*)0x1a56aba, &list); break;
    }
    int32_t nCount = (int32_t)((uint8_t*)list.mpEnd - (uint8_t*)list.mpBegin) >> 2;
    for (int32_t i = 0; i < nCount; ++i) {
        cNoun* pNoun = (cNoun*)list.mpBegin[i];
        if (!pNoun)
            continue;
        ResourceKey key;
        pNoun->v094(&key);
        if (pNoun->mCombatant.GetDamageState() == 2) {
            ResourceKey newKey = key;
            newKey.mInstanceID = nA;
            newKey.mGroupID = nB;
            newKey.mTypeID = nC;
            SP_SetKeyKind(&newKey, 0x7e, 0);
            pNoun->v094(&newKey);
        }
    }
    for (void** it = list.mpBegin; it < list.mpEnd; ++it) {
        if (*it)
            ((cNoun*)*it)->v004();
    }
    if (list.mpBegin && ((int32_t*)list.mpBegin)[-1] != 0)
        operator_delete_array(list.mpBegin);
}

// @ 0x00be3850
bool cAgentAction::FaceTarget()
{
    cNoun* pNoun = (cNoun*)FUN_00bd98c0();
    if (!pNoun)
        return false;

    cNoun* pData = (cNoun*)FUN_00be1fb0();
    FUN_00afa030(pData, pNoun);
    cVec3 position;
    position.x = *(float*)((uint8_t*)pNoun + 0x0c);
    position.y = *(float*)((uint8_t*)pNoun + 0x10);
    position.z = *(float*)((uint8_t*)pNoun + 0x14);
    pData->mSpatial.SetPosition(&position);

    cVec3 origin;
    cVec3* pRef = v058(&origin);
    cVec3 normal;
    normal.x = position.x - pRef->x;
    normal.y = position.y - pRef->y;
    normal.z = position.z - pRef->z;
    float fInv = 1.0f / sqrtf(normal.x * normal.x + normal.y * normal.y
                              + normal.z * normal.z + kZeroEpsilon);
    cVec3 dir;
    dir.x = normal.x * fInv;
    dir.y = normal.y * fInv;
    dir.z = normal.z * fInv;
    cMat4 orientation;
    pData->mSpatial.SetOrientation(SP_PlanetModel(&dir, &origin, &orientation)->BuildSurfaceOrientation2());

    if (mpField810) {
        void* pActive = FUN_01021260();
        FUN_00ff2810(this, *(void**)((uint8_t*)pActive + 0x13c));
    }
    return true;
}

// @ 0x00be3990
bool cAgentAction::FaceSlot(uint32_t nSlot)
{
    uint8_t* pSlot = (uint8_t*)mCircleC4b4.SlotAt(nSlot);
    if (!pSlot || *pSlot != 0)
        return false;

    cNoun* pData = (cNoun*)FUN_00be1fb0();
    FUN_00afa030(pData, pSlot);
    cVec3 position;
    position.x = *(float*)(pSlot + 0x0c);
    position.y = *(float*)(pSlot + 0x10);
    position.z = *(float*)(pSlot + 0x14);
    pData->mSpatial.SetPosition(&position);

    cVec3 origin;
    cVec3* pRef = v058(&origin);
    cVec3 normal;
    normal.x = position.x - pRef->x;
    normal.y = position.y - pRef->y;
    normal.z = position.z - pRef->z;
    float fInv = 1.0f / sqrtf(normal.x * normal.x + normal.y * normal.y
                              + normal.z * normal.z + kZeroEpsilon);
    cVec3 dir;
    dir.x = normal.x * fInv;
    dir.y = normal.y * fInv;
    dir.z = normal.z * fInv;
    cMat4 orientation;
    pData->mSpatial.SetOrientation(SP_PlanetModel(&dir, &origin, &orientation)->BuildSurfaceOrientation2());
    return true;
}

// @ 0x00be3ad0
void cAgentAction::UpdateRepair()
{
    if (FUN_00c004c0(0))
        return;
    if (++mField7f0 >= 2)
        mField7f0 = 0;

    int32_t nCount = (int32_t)((uint8_t*)mAgents340.mpEnd - (uint8_t*)mAgents340.mpBegin) >> 2;
    for (int32_t i = 0; i < nCount; ++i) {
        cNoun* pNoun = (cNoun*)mAgents340.mpBegin[i];
        if (pNoun->mCombatant.GetDamageState() == 2) {
            if (pNoun->GetTimerA() <= 30000 || pNoun->IsSpecial())
                continue;
            DestroyAgent(pNoun);
            continue;
        }
        float fThreshold = *(float*)((uint8_t*)pNoun + 0x158);
        if (fThreshold < pNoun->mCombatant.v058()) {
            pNoun->mCombatant.PartialRepair(kRepairFraction);
            if (mField7f0 != 0)
                continue;
            cVec3* pOrigin = pNoun->mSpatial.GetPosition();
            cVec3 normal;
            normal.x = pOrigin->x;
            normal.y = pOrigin->y;
            normal.z = pOrigin->z;
            float fInv = 1.0f / sqrtf(normal.x * normal.x + normal.y * normal.y
                                      + normal.z * normal.z + kZeroEpsilon);
            float fScale = *(float*)pNoun->mSpatial.v068() * kGrowFraction;
            normal.x = normal.x * fInv * fScale + normal.x;
            normal.y = normal.y * fInv * fScale + normal.y;
            normal.z = normal.z * fInv * fScale + normal.z;
            cEffectEmitter* pEmitter = (cEffectEmitter*)FUN_00b3d240();
            ResourceKey exclusions;
            void* pArg = pNoun->mSpatial.v05c(&exclusions);
            pEmitter->v060(0x3704925, &normal, pArg);
        }
    }

    int32_t nCount2 = (int32_t)((uint8_t*)mAgents354.mpEnd - (uint8_t*)mAgents354.mpBegin) >> 2;
    for (int32_t i = 0; i < nCount2; ++i) {
        cNoun* pNoun = (cNoun*)mAgents354.mpBegin[i];
        if (pNoun->mCombatant.GetDamageState() == 2) {
            if (pNoun->GetTimerB() <= 120000)
                continue;
            FUN_00be2070(pNoun, 0);
            continue;
        }
        float fThreshold = *(float*)((uint8_t*)pNoun + 0x5c0);
        if (fThreshold < pNoun->mCombatant.v058()) {
            pNoun->mCombatant.PartialRepair(kOne);
            if (mField7f0 != 0)
                continue;
            cEffectEmitter* pEmitter = (cEffectEmitter*)FUN_00b3d240();
            ResourceKey exclusions;
            cVec3* pOrigin = pNoun->mSpatial.GetPosition();
            void* pArg = pNoun->mSpatial.v05c(&exclusions);
            pEmitter->v060(0x3704925, pOrigin, pArg);
        }
    }
}

// @ 0x00be3de0
void cAgentAction::UpdateTimers()
{
    if (mTimer230.IsRunning()) {
        if (!mTimer230.IsRunning() || mTimer230.GetElapsedTime() >= 120000) {
            int32_t nCount = (int32_t)((uint8_t*)mAgents340.mpEnd - (uint8_t*)mAgents340.mpBegin) >> 2;
            for (int32_t i = 0; i < nCount; ++i) {
                if (((cNoun*)mAgents340.mpBegin[i])->mCombatant.IsDeadOrDying())
                    break;
            }
            mTimer230.Stop();
            if (mpField810) {
                cNoun* pNoun = mpField810;
                mpField810 = 0;
                if (pNoun)
                    pNoun->v004();
            }
            FUN_00be2440(this, 0, 0);
        }
    }
    if (mTimer250.IsRunning()) {
        if (!mTimer250.IsRunning() || mTimer250.GetElapsedTime() >= 30000)
            mTimer250.Stop();
    }
    if (mTimer270.IsRunning()) {
        if (!mTimer270.IsRunning() || mTimer270.GetElapsedTime() >= mTimestamp290)
            mTimer270.Stop();
    }
}

// @ 0x00be3f00
void cAgentAction::AdvanceFloatCounter(float fDelta)
{
    mField650 += fDelta;
    if (mField650 >= kOne) {
        do {
            if (mField64c <= 99) {
                ++mField64c;
                if (mpField590)
                    ++*mMap5a0[mpField590->v04c()];
            }
            mField650 -= kOne;
        } while (mField650 >= kOne);
    }
    if (mField650 <= kNegOne) {
        do {
            if (mField64c > 0 && mField64c > 20)
                --mField64c;
            mField650 += kOne;
        } while (mField650 <= kNegOne);
    }
}

// @ 0x00be3fe0
cRefList* cAgentAction::ClearRefs()
{
    mRefs0e4.erase(mRefs0e4.mpBegin, mRefs0e4.mpEnd);
    return &mRefs0e4;
}

// @ 0x00be41b0
void S::FUN_00be41b0()
{
  char* self = (char*)this;
  int u = ((int (__thiscall*)(void*))VFn(this, 0x4c))(this);
  void* nm = FUN_00b3d300();
  int* v = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      nm, 0xcd7d10, 0xd3d420, 0xacdff0, 0xb1e500, 0x18c43e8);
  int n = (*(int*)((char*)v + 8) - *(int*)((char*)v + 4)) >> 2;
  int* tool = (int*)((void* (__thiscall*)(void*, int))FUN_00bf1780)(*(void**)(self + 0x590), 2);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    int* elem = ((int**)((char*)v + 4))[i];
    if (((int (__thiscall*)(void*))VFn(elem, 0x4c))(elem) != u) {
      char* sub = (char*)elem + 0x120;
      float* p = (float*)((void* (__thiscall*)(void*))VFn(sub, 0x2c))(sub);
      float x = p[0], y = p[1], z = p[2];
      float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-08f);
      float* q = (float*)((void* (__thiscall*)(void*))VFn(sub, 0x2c))(sub);
      float vec[3];
      vec[0] = q[0] + x * inv * 10.0f;
      vec[1] = q[1] + y * inv * 10.0f;
      vec[2] = q[2] + z * inv * 10.0f;
      char* t = *(char**)(self + 0x320);
      if (t) t += 0x34;
      void* r = FUN_00b3d390(tool, t, vec, -1, 0, 0, 1);
      ((void (__thiscall*)(void*))FUN_01050070)(r);
      ++count;
      ((char*)elem)[0x762] = 1;
    }
  }
  void* nm2 = FUN_00b3d300();
  int* civs = (int*)((int* (__thiscall*)(void*))FUN_00b25ca0)(nm2);
  int m = (civs[1] - civs[0]) >> 2;
  for (int i = 0; i < m; ++i) {
    int* civ = ((int**)civs[0])[i];
    int* me = *(int**)(self + 0x590);
    if (civ != me) {
      int a = ((int (__thiscall*)(void*, int, float))VFn(me, 0x4c))(me, 0x5776d99, 1.0f);
      int b = ((int (__thiscall*)(void*))VFn(civ, 0x4c))(civ);
      void* rm = FUN_00b3d2c0(b, a);
      ((void (__thiscall*)(void*))FUN_00d06240)(rm);
    }
  }
  char c = ((char (__thiscall*)(void*))VFn((char*)self + 0x120, 0x58))((char*)self + 0x120);
  if (c != 0 && count > 0) {
    void* ctrl = FUN_00675250(0x1696afcf);
    ((void (__thiscall*)(void*))FUN_00676710)(ctrl);
  }
}

// @ 0x00be4400
void S::FUN_00be4400()
{
  char* self = (char*)this;
  int u = ((int (__thiscall*)(void*))VFn(this, 0x4c))(this);
  void* nm = FUN_00b3d300();
  int* v = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      nm, 0xcd7d10, 0xd3d420, 0xacdff0, 0xb1e500, 0x18c43e8);
  int n = (*(int*)((char*)v + 8) - *(int*)((char*)v + 4)) >> 2;
  for (int i = 0; i < n; ++i) {
    int* elem = ((int**)((char*)v + 4))[i];
    if (((int (__thiscall*)(void*))VFn(elem, 0x4c))(elem) != u) {
      int* tool = (int*)((void* (__thiscall*)(void*, int))FUN_00bf1780)(*(void**)(self + 0x590), 8);
      char* sub = (char*)elem + 0x120;
      float* p = (float*)((void* (__thiscall*)(void*))VFn(sub, 0x2c))(sub);
      float x = p[0], y = p[1], z = p[2];
      float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-08f);
      float* q = (float*)((void* (__thiscall*)(void*))VFn(sub, 0x2c))(sub);
      float vec[3];
      vec[0] = q[0] + x * inv * 60.0f;
      vec[1] = q[1] + y * inv * 60.0f;
      vec[2] = q[2] + z * inv * 60.0f;
      char* t = *(char**)(self + 0x320);
      if (t) t += 0x34;
      void* r = FUN_00b3d390(tool, t, vec, -1, 0, 0, 1);
      ((void (__thiscall*)(void*))FUN_01050070)(r);
      ((char*)elem)[0x762] = 1;
    }
  }
}

// ---- s00be4000 additions: externs not already declared above, and thiscall stubs for names the TU declares as cdecl
extern "C" void  FUN_00be3720();                 // 0xbe3720
extern "C" void  FUN_00bce5c0();                 // 0xbce5c0
extern "C" void  FUN_00be2e60();                 // 0xbe2e60
extern "C" void  FUN_00b25f40();                 // 0xb25f40
extern "C" void  FUN_00ae6d20();                 // 0xae6d20  vector grow
extern "C" void  FUN_00ae6a70();                 // 0xae6a70  cCitySimulator ctor
extern "C" void  FUN_00ae7100();                 // 0xae7100  AddSubsystem
extern "C" void* __cdecl FUN_00f473a0(unsigned, const char*, int, int, int, int); // 0xf473a0 EAAllocate
extern "C" void  FUN_00c9f250();                 // 0xc9f250
extern "C" int*  DAT_0167a690;                   // 0x167a690
struct Be4kThis {
  Key3* FUN_00bf9770(unsigned key);              // 0xbf9770 (thiscall twin of the cdecl declaration above)
  int*  FUN_00ca71d0();                          // 0xca71d0
  void  FUN_00cac000(int a, int b, int c);       // 0xcac000
};

// @ 0x00be4000
char S::FUN_00be4000(int* param_2, char param_3)
{
  void* nm = FUN_00b3d300();
  int* v = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      nm, 0xcd7d10, 0xd3d420, 0xae72d0, 0xb1e500, 0x18c6de8);
  int** p = *(int***)((char*)v + 4);
  int** end = *(int***)((char*)v + 8);
  for (;;) {
    if (p == end)
      return 0;
    int* elem = *p;
    char b;
    if (param_3 == 0)
      b = ((int (__thiscall*)(void*))VFn(elem, 0x4c))(elem)
          != ((int (__thiscall*)(void*))VFn(param_2, 0x4c))(param_2);
    else
      b = ((int (__thiscall*)(void*))VFn(elem, 0x4c))(elem)
          == ((int (__thiscall*)(void*))VFn(param_2, 0x4c))(param_2);
    if (b) {
      int* pi = (int*)((Be4kThis*)elem)->FUN_00ca71d0();
      int type = pi[4];
      if (type == 1) {
        int* a = *(void**)pi ? (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0xe9cb8ba) : 0;
        int* d = *(void**)pi ? (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0x436f315) : 0;
        if (a && ((int (__thiscall*)(void*))VFn(a, 0x84))(a) == (int)this)
          return 1;
        if (d) {
          int r = ((int (__thiscall*)(void*))FUN_00bce5c0)(d);
          if (r == (int)this)
            return 1;
        }
      }
      else if (type == 2) {
        if (*(void**)pi) {
          int r = ((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0xee9b2232);
          if (r && r == (int)this)
            return 1;
        }
      }
      else if (type == 3) {
        int r1 = *(void**)pi ? ((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0xee9b2232) : 0;
        int* r2 = *(void**)pi ? (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0x3d5c477) : 0;
        if (r1 && r1 == (int)this)
          return 1;
        if (r2) {
          int* r3 = (int*)((int (__thiscall*)(void*))VFn(r2, 0x30))(r2);
          int r4 = r3 ? ((int (__thiscall*)(void*, int))VFn(r3, 0xc))(r3, 0xee9b2232) : 0;
          if (r4 == (int)this)
            return 1;
        }
      }
    }
    ++p;
  }
}

// @ 0x00be4a10
void S::FUN_00be4a10(void* civ)
{
  if (civ != 0) {
    Key3 k = *((Be4kThis*)civ)->FUN_00bf9770(0x99e92f05);
    if (k.a != 0)
      ((void (__thiscall*)(void*, unsigned, Key3))FUN_00be3720)(this, 0x99e92f05, k);
    k = *((Be4kThis*)civ)->FUN_00bf9770(0x4e3f7777);
    if (k.a != 0)
      ((void (__thiscall*)(void*, unsigned, Key3))FUN_00be3720)(this, 0x4e3f7777, k);
    k = *((Be4kThis*)civ)->FUN_00bf9770(0x47c10953);
    if (k.a != 0)
      ((void (__thiscall*)(void*, unsigned, Key3))FUN_00be3720)(this, 0x47c10953, k);
    k = *((Be4kThis*)civ)->FUN_00bf9770(0x72c49181);
    if (k.a != 0)
      ((void (__thiscall*)(void*, unsigned, Key3))FUN_00be3720)(this, 0x72c49181, k);
  }
}

// @ 0x00be4b30
void S::FUN_00be4b30(void* civ)
{
  char* self = (char*)this;
  self[0x2e2] = 0;
  void* u = ((void* (__thiscall*)(void*))(*(void***)civ)[0x4c / 4])(civ);

  int n = (*(int*)(self + 0x344) - *(int*)(self + 0x340)) >> 2;
  for (int i = 0; i < n; ++i) {
    void* e = ((void**)*(void**)(self + 0x340))[i];
    ((void (__thiscall*)(void*, void*))VFn(e, 0x48))(e, u);
  }

  n = (*(int*)(self + 0x358) - *(int*)(self + 0x354)) >> 2;
  for (int i = 0; i < n; ++i) {
    void* e = ((void**)*(void**)(self + 0x354))[i];
    ((void (__thiscall*)(void*, void*))VFn(e, 0x48))(e, u);
  }

  n = (*(int*)(self + 0x30c) - *(int*)(self + 0x308)) >> 2;
  for (int i = 0; i < n; ++i) {
    void* e = ((void**)*(void**)(self + 0x308))[i];
    ((void (__thiscall*)(void*, void*))VFn(e, 0x48))(e, u);
  }

  FUN_00be4a10(civ);
  ((void (__thiscall*)(void*, int))FUN_00bd1ab0)(*(void**)(self + 0x320), 1);
}

// @ 0x00be6310
cCity_s00be_6310::cCity_s00be_6310()
: cCityPrefix(), cSpatialObject_s00be_6310(), mInteraction()
{
    // Seven vtable installs (the listener interface at +0x20c is written twice).
    mInteraction.mpVtbl2 = (void*)0x13eb384;                  // +0x20c  cListenerBase
    mInteraction.mpVtbl  = (void*)0x14686e4;                  // +0x1f4  cCity (interaction)
    mpVtbl0              = (void*)0x14687d8;                  // +0x000
    mpVtbl1              = (void*)0x14687c4;                  // +0x004
    mpVtbl2              = (void*)0x1469cc0;                  // +0x034
    static_cast<cSpatialObject_s00be_6310&>(*this).mpVtbl = (void*)0x1468700;  // +0x120
    mInteraction.mpVtbl2 = (void*)0x14686d4;                  // +0x20c  cCity (listener)

    // Empty eastl::string16.
    mName.mpBegin    = (void*)0x1667bac;                      // +0x210
    mName.mpEnd      = (void*)0x1667bac;                      // +0x214
    mName.mpCapacity = (void*)0x1667bae;                      // +0x218

    mF220 = 0.0f;                                             // +0x220
    mI224 = 0;                                                // +0x224
    mI228 = 0;                                                // +0x228
    mTimer230.Construct();                                    // +0x230
    mTimer250.Construct();                                    // +0x250
    mTimer270.Construct();                                    // +0x270

    mI298 = 0;                                                // +0x298
    mB2a0 = 0;                                                // +0x2a0
    mI29c = -1;                                               // +0x29c
    mVec2a4.mpBegin = 0; mVec2a4.mpEnd = 0; mVec2a4.mpCapacity = 0;   // +0x2a4
    mVec2b8.mpBegin = 0; mVec2b8.mpEnd = 0; mVec2b8.mpCapacity = 0;   // +0x2b8
    mF300 = 0.0f;                                             // +0x300
    mF304 = DAT_013f1cac;                                     // +0x304  50.0f
    mI2cc = 0;                                                // +0x2cc
    mI2d0 = 0;                                                // +0x2d0
    mB2e0[0] = 0; mB2e0[1] = 0; mB2e0[2] = 0; mB2e0[3] = 0;   // +0x2e0
    mB2e0[4] = 0; mB2e0[5] = 0; mB2e0[6] = 0;
    mI2e8 = 0;                                                // +0x2e8
    mI2ec = 0;                                                // +0x2ec
    mI2f0 = 0;                                                // +0x2f0
    mI2f4 = 0;                                                // +0x2f4
    mI2f8 = 0;                                                // +0x2f8
    mB2fc = 0;                                                // +0x2fc
    mVec308.mpBegin = 0; mVec308.mpEnd = 0; mVec308.mpCapacity = 0;   // +0x308
    mI320 = 0;                                                // +0x320  mpCityHall
    mI324 = 0;                                                // +0x324  mpCityWalls
    mI328 = 0;                                                // +0x328  mpCityTerritory
    mF32c = DAT_0168bd70;                                     // +0x32c
    mF330 = DAT_0168bd74;                                     // +0x330
    mF334 = DAT_0168bd78;                                     // +0x334
    mF338 = DAT_01473c70;                                     // +0x338  10.0f
    mVec340.mpBegin = 0; mVec340.mpEnd = 0; mVec340.mpCapacity = 0;   // +0x340

    // 32-slot inline turret vector; the buffer sits at +0x36c and its end is the
    // address of mAction3ec.
    mVec354.mpBegin    = mInlineBuf36c;                       // +0x354
    mVec354.mpEnd      = mInlineBuf36c;                       // +0x358
    mVec354.mpCapacity = mInlineBuf36c + 32;                  // +0x35c
    mVec354.mpBuffer   = mInlineBuf36c;                       // +0x364

    mAction3ec.LayoutConstruct();                             // +0x3ec
    mAction450.LayoutConstruct();                             // +0x450
    mAction4b4.LayoutConstruct();                             // +0x4b4

    mFlag518 = 1;                                             // +0x518
    mB519 = 0;                                                // +0x519
    mVec528.mpBegin = 0; mVec528.mpEnd = 0; mVec528.mpCapacity = 0;   // +0x528
    mI540 = -1;                                               // +0x540
    mF53c = 0.0f;                                             // +0x53c
    mVec548.mpBegin = 0; mVec548.mpEnd = 0; mVec548.mpCapacity = 0;   // +0x548
    mVec55c.mpBegin = 0; mVec55c.mpEnd = 0; mVec55c.mpCapacity = 0;   // +0x55c

    // Red-black tree at +0x570 (anchor at +0x574).
    mRb570.mpNodeRight  = 0;
    mRb570.mpNodeParent = 0;
    mRb570.mColorWord   = 0;
    mRb570.mpNodeParent = 0;
    mRb570.mColor       = 0;
    mRb570.mnSize       = 0;
    mRb570.mpNodeLeft   = &mRb570.mpNodeLeft;
    mRb570.mpNodeRight  = &mRb570.mpNodeLeft;

    mB58c = 0;                                                // +0x58c
    mPtr590 = 0;                                              // +0x590
    mI594 = 0x2d;                                             // +0x594
    mF598 = DAT_013eecd8;                                     // +0x598  20.0f
    mI59c = 0;                                                // +0x59c

    // Red-black tree at +0x5a0.
    mRb5a0.mpNodeRight  = 0;
    mRb5a0.mpNodeParent = 0;
    mRb5a0.mColorWord   = 0;
    mRb5a0.mpNodeParent = 0;
    mRb5a0.mColor       = 0;
    mRb5a0.mnSize       = 0;
    mRb5a0.mpNodeLeft   = &mRb5a0.mpNodeLeft;
    mRb5a0.mpNodeRight  = &mRb5a0.mpNodeLeft;

    // Red-black tree at +0x5bc (anchor at +0x5c0).
    mRb5bc.mpNodeRight  = 0;
    mRb5bc.mpNodeParent = 0;
    mRb5bc.mColorWord   = 0;
    mRb5bc.mpNodeLeft   = &mRb5bc.mpNodeLeft;
    mRb5bc.mpNodeRight  = &mRb5bc.mpNodeLeft;
    mRb5bc.mpNodeParent = 0;
    mRb5bc.mColor       = 0;
    mRb5bc.mnSize       = 0;

    // Red-black tree at +0x5d8.
    mRb5d8.mpNodeRight  = 0;
    mRb5d8.mpNodeParent = 0;
    mRb5d8.mColorWord   = 0;
    mRb5d8.mpNodeLeft   = &mRb5d8.mpNodeLeft;
    mRb5d8.mpNodeRight  = &mRb5d8.mpNodeLeft;
    mRb5d8.mpNodeParent = 0;
    mRb5d8.mColor       = 0;
    mRb5d8.mnSize       = 0;

    mTimer5f8.Construct();                                    // +0x5f8

    mCultureTargetInfo.mpBegin = 0; mCultureTargetInfo.mpEnd = 0;
    mCultureTargetInfo.mpCapacity = 0;                        // +0x618
    mVec62c.mpBegin = 0; mVec62c.mpEnd = 0; mVec62c.mpCapacity = 0;   // +0x62c
    mI64c = 0;                                                // +0x64c
    mF650 = 0.0f;                                             // +0x650
    mI654 = 0;                                                // +0x654
    mI658 = 0;                                                // +0x658
    mI65c = 0;                                                // +0x65c
    mI660 = 0;                                                // +0x660
    mI664 = 0;                                                // +0x664
    mI668 = 0;                                                // +0x668
    mI66c = 0;                                                // +0x66c
    mI670 = 0;                                                // +0x670
    mI674 = 0;                                                // +0x674
    mI678 = 0;                                                // +0x678
    mI67c = 0;                                                // +0x67c
    mI680 = 0;                                                // +0x680
    mVec684.mpBegin = 0; mVec684.mpEnd = 0; mVec684.mpCapacity = 0;   // +0x684
    mB698 = 0;                                                // +0x698
    mTimer6a0.Construct();                                    // +0x6a0
    mB6c0 = 0;                                                // +0x6c0
    mTimer6c8.Construct();                                    // +0x6c8
    mTimer6e8.Construct();                                    // +0x6e8
    mTimer708.Construct();                                    // +0x708
    mTimer728.Construct();                                    // +0x728

    mF748 = 0.0f; mI74c = -1;                                 // +0x748
    mF750 = 0.0f; mI754 = -1;                                 // +0x750
    mF758 = 0.0f; mI75c = -1;                                 // +0x758
    mB760 = 0;                                                // +0x760
    mB761 = 0;                                                // +0x761
    mB762 = 0;                                                // +0x762
    mI764 = 0;                                                // +0x764
    mI768 = 0;                                                // +0x768
    mTimer770.Construct();                                    // +0x770
    mTimer790.Construct();                                    // +0x790

    // Red-black tree at +0x7b8 (anchor at +0x7bc).
    mRb7b8.mpNodeRight  = 0;
    mRb7b8.mpNodeParent = 0;
    mRb7b8.mColorWord   = 0;
    mRb7b8.mpNodeLeft   = &mRb7b8.mpNodeLeft;
    mRb7b8.mpNodeRight  = &mRb7b8.mpNodeLeft;
    mRb7b8.mpNodeParent = 0;
    mRb7b8.mColor       = 0;
    mRb7b8.mnSize       = 0;

    mI7d4 = 0;                                                // +0x7d4
    mI7f0 = 0;                                                // +0x7f0
    mI7f8 = 0;                                                // +0x7f8
    mI7fc = 0;                                                // +0x7fc
    mI800 = 0;                                                // +0x800
    mB80c = 0;                                                // +0x80c

    mI810 = 0;                                                // +0x810
    mI544 = (int)g_1601760_s00be_6310.RandomUint32Uniform(3);            // +0x544  random specialty

    mTimer5f8.Start();
    mTimer6a0.Start();
    mTimer6c8.Start();
    mTimer6e8.Start();
    mTimer708.Start();
    mTimer728.Start();

    mCultureTargetInfo.Resize(4);                             // 0x00be60a0

    // Initialise the four 0x80-byte culture-target records.
    for (int i = 0; i < 4; ++i) {
        cCultureTargetInfo* t = mCultureTargetInfo.mpBegin + i;
        for (int k = 0; k < 8; ++k)
            t->mPtr00[k] = 0;
        t->mFlag20 = 0;
        t->mF24 = 0.0f;
        t->mF28 = 0.0f;
        t->mF2c = 0.0f;
        if (t->mPtr70 != 0) {
            cRefCounted* p = t->mPtr70;
            t->mPtr70 = 0;
            p->Release();
        }
        t->mFlag74 = 0;
        if (t->mPtr78 != 0) {
            cRefCounted* p = t->mPtr78;
            t->mPtr78 = 0;
            p->Release();
        }
    }

    mB648 = 0;                                                // +0x648
    mI7f4 = (int)g_1601760_s00be_6310.RandomUint32Uniform(3);            // +0x7f4
}

// @ 0x00be6900
void cCity_s00be_6310::FUN_00be6900(char param2)
{
    int count = g_15fd918->GetIntProperty(0x6414d84);
    for (int a0 = 0; a0 < 0x24; a0 += 0xc) {
        for (int i = count; i > 0; --i) {
            // Create the decoration noun and cast it to the ornament interface.
            cGameNounManager_s00be_6310* mgr = NounManager_s00be_6310();
            cNoun_s00be_6310* noun = mgr->CreateNoun((void*)0x18c88e4);
            cNoun_s00be_6310* orn = noun ? noun->Cast(0x175cdc9) : 0;

            // Pick the style model for this turret row and apply it.
            void* elem = *(void**)((char*)mVec528.mpBegin + a0);
            void* style = ((cCityVtbl_s00be_6310*)this)->Vfn4c(elem);
            ((cSimOrnament*)orn)->SetStyleModel((void*)0x2ae5ba7, style);

            // Reset the ornament's transform sub-object.
            orn->mSub70.SetScale(1.0f);
            orn->mSub70.FUN_00c88530(1.0f);

            // Insert into mCivicObjects (SPVector<AutoRefCount>): the temporary holds
            // one reference, the vector element another; the temporary is then dropped.
            void* tmp = orn;
            if (orn != 0)
                orn->AddRef();
            if (mVec308.mpEnd < mVec308.mpCapacity) {
                void** slot = mVec308.mpEnd;
                mVec308.mpEnd = slot + 1;
                if (slot != 0) {
                    *slot = orn;
                    if (orn != 0)
                        orn->AddRef();
                }
            } else {
                mVec308.DoInsertPtr(mVec308.mpEnd, tmp);
            }
            if (tmp != 0)
                orn->Release();

            mAction450.RemoveAgent(orn);                      // +0x450
            if (mFlag518 != 0)
                FUN_00be5180();
            SetDecoration(orn);

            if (param2 != 0) {
                cEffect* effect = 0;
                cEffectsManager* effects = EffectsManager_s00be_6310();
                if (effect != 0) {
                    effect->Release();
                    effect = 0;
                }
                if (effects->SpawnEffect(0xaec03934, 0, &effect)) {
                    cEffectDesc desc;
                    desc.mF04 = DAT_0168c354;
                    desc.mF08 = DAT_0168c358;
                    desc.mF0c = DAT_0168c35c;
                    desc.mF10 = 1.0f;

                    Mat3 base;
                    base.m[0] = DAT_0168c330;
                    base.m[1] = DAT_0168c334;
                    base.m[2] = DAT_0168c338;
                    base.m[3] = DAT_0168c33c;
                    base.m[4] = DAT_0168c340;
                    base.m[5] = DAT_0168c344;
                    base.m[6] = DAT_0168c348;
                    base.m[7] = DAT_0168c34c;
                    base.m[8] = DAT_0168c350;
                    desc.mFlags = 0;
                    desc.mCount = 0;
                    desc.mMatrix = base;

                    // Position from the ornament transform.
                    float* pos = orn->mSub70.GetPosition();
                    desc.mF04 = pos[0];
                    desc.mF08 = pos[1];
                    desc.mF0c = pos[2];
                    desc.mFlags |= 4;
                    desc.mCount = (short)(desc.mCount + 1);

                    // Orientation quaternion -> rotation matrix.
                    float* q = orn->mSub70.GetOrientation();
                    float x = q[0];
                    float y = q[1];
                    float z = q[2];
                    float w = q[3];
                    Mat3 rot;
                    rot.m[0] = 1.0f - (z * z + y * y) * 2.0f;
                    rot.m[1] = (w * z + y * x) * 2.0f;
                    rot.m[2] = (z * x - w * y) * 2.0f;
                    rot.m[3] = (y * x - w * z) * 2.0f;
                    rot.m[4] = 1.0f - (z * z + x * x) * 2.0f;
                    rot.m[5] = (w * x + z * y) * 2.0f;
                    rot.m[6] = (w * y + z * x) * 2.0f;
                    rot.m[7] = (z * y - w * x) * 2.0f;
                    rot.m[8] = 1.0f - (y * y + x * x) * 2.0f;
                    desc.mMatrix = rot;
                    desc.mFlags |= 2;
                    desc.mCount = (short)(desc.mCount + 1);

                    effect->SetDescriptor(&desc);             // vtable +0x18
                    effect->SetVisible(0);                    // vtable +0x08
                }
                if (effect != 0)
                    effect->Release();
            }
        }
    }
}

// @ 0x00be6d90
float cCity_s00be_6310::FUN_00be6d90()
{
    float scale = (float)mVec308.Size() * DAT_0169c1e0;

    void* buf[32];
    cInlinePtrVector buildings;
    buildings.mpBegin    = buf;
    buildings.mpEnd      = buf;
    buildings.mpCapacity = buf + 32;
    buildings.mpBuffer   = buf;
    if (&buildings != &mVec354) {
        buildings.Reset(buf, buf);
        buildings.Append(mVec354.mpBegin, mVec354.mpEnd, scale);
    }

    float buildingScore = 0.0f;
    for (void** it = buildings.mpBegin; it != buildings.mpEnd; ++it) {
        cBuildingScore* b = (cBuildingScore*)*it;
        if (b->mCombatant588.GetDamageState() != 2)
            buildingScore = buildingScore + b->Score() * DAT_01471064;
    }

    float raidScore = 0.0f;
    for (void** it = mVec340.mpBegin; it != mVec340.mpEnd; ++it) {
        cRaidParticipant* r = (cRaidParticipant*)*it;
        if (r->mCombatant120.GetDamageState() != 2)
            raidScore = raidScore + r->GetWeight() * DAT_013eb1c0;
    }

    float result = raidScore + buildingScore + scale + DAT_01465544;
    if (mPtr590->mFlag8a == 0)
        result = result * DAT_01470f1c;

    // Release the local building list and hand its buffer back (the original does this with
    // explicit code rather than a class destructor, so the function needs no unwind frame).
    for (void** it = buildings.mpBegin; it != buildings.mpEnd; ++it) {
        cBuildingScore* b = (cBuildingScore*)*it;
        if (b != 0)
            b->Release();
    }
    if (buildings.mpBegin != 0 && buildings.mpBegin != buildings.mpEnd)
        EASTL_allocator_deallocate(buildings.mpBegin);

    return result;
}

// @ 0x00be6f40
void cCity_s00be_6310::FUN_00be6f40()
{
    FUN_00be5180();
    mFlag518 = 1;
}

// @ 0x00be6f60
void cSpatialObject_s00be_6310::FUN_00be6f60()
{
    cSpatialObject_func80h();
    // The cSpatialObject sub-object sits at cCity + 0x120; the owning cCity is reached by
    // rebinding the base pointer.  Written explicitly because MSVC's implicit base-to-derived
    // conversion (static_cast) would insert a redundant null guard the original does not have.
    cCity_s00be_6310* city = (cCity_s00be_6310*)((unsigned char*)this - 0x120);
    city->FUN_00be5180();
    FUN_00b3d480()->FUN_00ac8d40(city);
}

// @ 0x00be6f90
void __thiscall City::Fn6f90()
{
    FnBDaf50();
    FnBD9710();
    FnBDbaa0();
    FnB3d480(this)->FnAc8d40();
    FnBDaea0();
    FnBD88c0();

    if (GetCurrentGameMode() == (void*)gAppNameTag_s00be_6f90) {
        if (gSimSingleton == 0) {
            void* mem = EAAllocate(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
            gSimSingleton = mem ? SimSingleton::Create(mem) : 0;
        }
        gSimSingleton->f0a8 = 1;
    }

    if (f320 != 0) {
        Thing320* t = f320;
        u32 r = t->Fn8C();
        t->ctx.Fn38((void*)r);
    }

    CtxVec candidates = { 0, 0, 0 };
    float radius = f324->f25c + 16.0f;
    Ctx* ctx = &f324->ctx;
    Vec3f center = *ctx->GetPosition();
    {
        cActionCircle_s00be_6f90 circle;
        Vec3f facingOut;
        circle.SetAtCenter(&center, radius, ctx->Fn5C(&facingOut), 0.0f);
        circle.FnAfef10(1, 8.0f);

        AgentMgr* mgr = FnB3d240();
        mgr->FindAgents(&center, radius, &candidates, 0, 0, 0);

        int n = (int)(candidates.mpEnd - candidates.mpBegin);
        for (int i = 0; i < n; ++i) {
            Ctx* noun = candidates.mpBegin[i];
            Ctx* id;
            if (noun != 0 && (id = noun->FnB8(0x137e8e0)) != 0) {
                Vec3f target;
                SlotVec slots = { 0, 0, 0 };
                Vec3f* pos = noun->GetPosition();
                float dx = pos->x - center.x;
                float dy = pos->y - center.y;
                float dz = pos->z - center.z;
                float len2 = dx * dx + dy * dy + dz * dz + 1e-8f;
                float len = sqrtf(len2);
                float inv = 1.0f / len;
                target.x = (inv * dx) * radius + center.x;
                target.y = (inv * dy) * radius + center.y;
                target.z = (inv * dz) * radius + center.z;
                circle.FnAfeff0(&target, &slots);

                int m = (int)(slots.mpEnd - slots.mpBegin);
                int j = 0;
                if (m > 0) {
                    do {
                        cActionCircle_s00be_6f90::tSlot* slot = circle.SlotAt(slots.mpBegin[j]);
                        if (slot != 0 && !slot->mOccupied && id->CanOccupy(&slot->mPos)) {
                            slot->Reserve(id);
                            noun->Fn38(&slot->mPos);
                            break;
                        }
                        ++j;
                    } while (j < m);
                }
                if (j == m)
                    noun->Fn38(&target);
                if (slots.mpBegin != 0 && ((int*)slots.mpBegin)[-1] != 0)
                    EFree(slots.mpBegin);
            }
        }

        FUN_00cac360(center.x, center.y, center.z, radius);
        if (f761 != 0) {
            FnBe5dd0();
            f761 = 0;
        }
    }

    Ctx** end = candidates.mpEnd;
    for (Ctx** p = candidates.mpBegin; p < end; ++p) {
        if (*p != 0)
            (*p)->FnC0();
    }
    if (candidates.mpBegin != 0 && ((int*)candidates.mpBegin)[-1] != 0)
        EFree(candidates.mpBegin);
}

// @ 0x00be7370
u32 __thiscall City::OverwriteNounsFromNounManager(u32 id)
{
    const char* name;
    switch (id) {
    case 0x1a55e4d: name = ((const char*)0x01a56aba); break;
    case 0xecade42: name = NounNameB; break;
    default:        name = NounNameC; break;
    }
    u32 r = Fn53b0(name, id);
    if (f2f0 != 0) {
        PlanetRec* p = Fn1021260();
        f2f0->Fn(this, p->f13c);
    }
    return r;
}

// @ 0x00be73d0
void __thiscall City::F73d0(u32 planet, u8 flag)
{
    if (planet != f540) {
        f540 = planet;
        if (f324) {
            f324->f108 = flag;
            Thing324* p = f324;
            p->Fn60(FnBebc90(planet, p->f34c));
        }
        FnBe5180();
        FnBe5dd0();
    }
    int n = (int)(f358 - f354);
    for (int i = 0; i < n; ++i) {
        Ctx* c = f354[i];
        if (c)
            c->FnBD0000();
    }
    if (f590)
        f590->Fn(this);
}

// @ 0x00be7470
bool __thiscall CityListener::HandleMessage(u32 id, Msg* msg)
{
#define CITY ((City*)((char*)this - 0x20c))
#define OBJ ((Obj120*)((char*)this - 0xec))
    switch (id) {
    case 0x5416d55: {
        if (msg->data != (u32)CITY) return 0;
        Node* n = msg->f10;
        u32 mem = msg->f18;
        u32 t = AllocKey(n->GetAllocator(), n->Type());
        u32 w = f334;
        Key* k = f384->GetModelTypeKey(t);
        Q* q = CITY->AddThing(w, n->Type(), *k, 0);
        q->A(n);
        q->B(mem);
        return 0;
    }
    case 0x40fafdf: {
        NounMgr* nm = NounManager_s00be_6f90();
        if (!nm) return 0;
        City* pc = nm->GetPlayerCivilization()->city;
        if (pc != CITY) return 0;
        if (msg->data == 0x5107b1a) {
            u32 kind = f118->GetA();
            u32 la = f118->GetB();
            CITY->F73d0(((City*)pc)->f29c, 1);
            u32 lb = f118->GetB();
            u32 k0 = 0, k1 = 0;
            switch (kind) {
            case 0: k0 = 0x5f77883; k1 = 0x5f779c3; break;
            case 1: k0 = 0x5f779b2; k1 = 0x5f779c8; break;
            case 2: k0 = 0x5f779b8; k1 = 0x5f779cd; break;
            case 3: k0 = 0x5f779bd; k1 = 0x5f779d2; break;
            }
            Vec3_s00be_6f90 pos = f384->pos;
            AutoRef<PropList> list;
            if (PropertyManager()->Get(la, 0x2e4b4cc, list.AsPPTypeParam())) {
                u32 id = 0;
                if (GetPropertyAsUint32(list.p, k0, &id)) {
                    AutoRef<Fx> fx;
                    if (EffectsManager_s00be_6f90()->Create(id, 0, fx.AsPPTypeParam())) {
                        StartFx(OBJ, fx.p, &pos);
                        AutoRef<PropList> list2;
                        if (PropertyManager()->Get(lb, 0x2e4b4cc, list2.AsPPTypeParam())) {
                            u32 id2 = 0;
                            if (GetPropertyAsUint32(list2.p, k1, &id2)) {
                                AutoRef<Fx> fx2;
                                if (EffectsManager_s00be_6f90()->Create(id2, 0, fx2.AsPPTypeParam()))
                                    StartFx(OBJ, fx2.p, &pos);
                            }
                        }
                    }
                }
            }
        }
        GameTimeManager_s00be_6f90()->DecPauseGate(0x4bf38a7);
        CivModeStrategyGet()->A();
        if (!CivModeStrategyGet()->CanBuildSeaVehicles()) return 0;
        CivModeStrategyGet()->B();
        CivModeStrategyGet()->C();
        return 1;
    }
    case 0x56e50f1:
        if (msg->data != (u32)CITY || fE4 == 0) return 0;
        PlanetHook(CITY, fE4, GetActivePlanetRecord());
        return 0;
    case 0x6787056: {
        AutoRef<Fx> fx;
        EffMgr* em = EffectsManager_s00be_6f90();
        if (fx.p) { Fx* old = fx.p; fx.p = 0; old->Release(); }
        if (em->Create(0xea04f48c, 0, &fx.p)) {
            XformMsg_s00be_6f90 m;
            const Vec3_s00be_6f90* p = OBJ->GetPosition();
            m.pos.x = p->x; m.pos.y = p->y; m.pos.z = p->z;
            m.flags |= 4;
            m.count++;
            Mat3 tmp;
            m.mat = *Matrix3FromQuaternion(&tmp, OBJ->GetOrientation());
            m.flags |= 2;
            m.count++;
            fx.p->SetTransform(&m);
            fx.p->Start(0);
        }
        return 0;
    }
    case 0x5f74817:
        if (OBJ->IsReady() && msg->data == 1) {
            Obj118S* p = f118;
            u32* fl = p->sub.Flags();
            if (fl) fl[1] |= 1;
        }
        return 0;
    }
    return 0;
#undef CITY
#undef OBJ
}

// @ 0x00be7aa0
void __thiscall InfoRecVec::Insert(InfoRec_s00be_6f90* pos, InfoRec_s00be_6f90* value)
{
    InfoRec_s00be_6f90* end = mpEnd;
    if (end != mpCap) {
        InfoRec_s00be_6f90* v = value;
        if (v >= pos && v < end)
            v += 1;
        if (end)
            new (end) InfoRec_s00be_6f90(*(end - 1));
        CopyInfoRecsBwd(pos, mpEnd - 1, mpEnd);
        pos->pos = v->pos;
        pos->v = v->v;
        mpEnd = mpEnd + 1;
        return;
    }
    u32 count = (u32)(mpEnd - mpBegin);
    u32 n;
    if (count > 0)
        n = count * 2;
    else
        n = 1;
    InfoRec_s00be_6f90* nd = 0;
    if (n != 0)
        nd = (InfoRec_s00be_6f90*)EAAllocate(n << 5, kSimulatorTag, 0, 0, (int)kEastlFile_s00be_6f90, 0xd1);
    else
        nd = 0;
    InfoRec_s00be_6f90* first = mpBegin;
    InfoRec_s00be_6f90* dst = CopyInfoRecs(first, pos, nd);
    MoveInfoRecs(first, pos, nd);
    if (dst)
        new (dst) InfoRec_s00be_6f90(*value);
    InfoRec_s00be_6f90* last = mpEnd;
    dst += 1;
    InfoRec_s00be_6f90* ni = CopyInfoRecs(pos, last, dst);
    MoveInfoRecs(pos, last, dst);
    InfoRec_s00be_6f90* old = mpBegin;
    if (old != 0 && ((int*)old)[-1] != 0)
        EFree(old);
    mpBegin = nd;
    mpEnd = ni;
    mpCap = (InfoRec_s00be_6f90*)((char*)nd + (n << 5));
}

// @ 0x00be9850
void Sim::sub_be9850(int a1, float a2)
{
    int id = VGETID(this->p590);
    if (a1 == id)
        return;
    cCivilization_s00be_9850* noun = (cCivilization_s00be_9850*)GetNounManager()->FUN00b25f40(a1);
    if (a2 == 0.0f)
        a2 = this->FUN00be9250(a1);
    if (0.0f > a2)
        return;
    if (noun->GetMoney() < a2)
        return;
    noun->SpendMoney(a2);
    this->map1.clear();
    this->map2.clear();
    this->map3.clear();
    int v = this->f64c;
    this->map1[a1] = v;
    this->sub_be92e0(a1, 2, 0, 0, 0);
}

// @ 0x00be9980
void Sim::sub_be9980(int a1)
{
    int id = VGETID(this->p590);
    int key = this->f74c;
    if (key == -1)
        return;
    if (key == id)
        return;
    if (!(this->f748 >= 100.0f))
        return;
    void* noun = GetNounManager()->FUN00b25f40(key);
    void* civ  = GetNounManager()->GetPlayerCivilization();
    if (civ == this->p590) {
        GetCivModeStrategy()->FUN00cf9040(this, 0xedd4a52f, 0x2bb7aff, V120M3(this, 0x2c, 0, 1, 0));
    } else if (noun == civ) {
        GetCivModeStrategy()->FUN00cf9040(this, 0x43d2843c, 0x2bb7aff, V120M3(this, 0x2c, 0, 1, 0));
    } else if (*((char*)noun + 0x8a) == 0) {
        this->sub_bd9a00(noun);
    }
    this->map1.clear();
    this->map2.clear();
    this->map3.clear();
    int v = this->f64c;
    this->map1[key] = v;
    this->f98 = 0;
    this->f9c = 0;
    this->sub_be92e0(key, 0, 0, a1, 0);
    if (this->p320 != 0)
        V120M1(this->p320, 0x2c, 0);
}

// @ 0x00be9b20
void FUN_00be9b20(Obj* a1, Sim* sim, Obj* alt, int a4, float a5, int a6, int a7)
{
    float fv;
    int   iv;
    if (sim != 0) {
        fv = sim->f748;
        iv = sim->f74c;
    } else {
        fv = alt->FUN00b7e0a0();
        iv = alt->FUN00a1ad10();
    }
    if (a6 == -1)
        return;
    if (a6 == a4)
        return;
    float delta = a5 * 0.1f;
    int iv2 = iv;
    if (iv2 == -1)
        iv2 = a6;
    iv = iv2;
    float nv;
    if (iv == a6)
        nv = fv + delta;
    else
        nv = fv - delta;
    if (nv < 0.0f) {
        nv = -nv;
        iv = a6;
    }
    if (nv > 100.0f)
        nv = 100.0f;
    if (sim != 0) {
        sim->FUN00bd7d10(iv, nv);
    } else if (alt != 0) {
        alt->FUN00ff03b0(iv);
        alt->FUN00ff03c0(nv);
    }
    if (GetCurrentGameMode() != (void*)&DAT_01654c05
        || (a1->FUN00b8dab0() == 4 && a6 != GetPlayerEmpireID_s00be_9850())) {
        sim->sub_be9980(a7);
        return;
    }
    if (nv < 100.0f)
        return;
    if (GetCurrentGameMode() == (void*)&DAT_01654c05 && sim != 0 && iv == GetPlayerEmpireID_s00be_9850()) {
        float r = FUN_00bd9a80(a1);
        if (r > 0.0f && (float)_sMathRandom.RandomDoubleUniform() < r)
            SpaceGameGet()->GetAvatar()->FUN00ffa900(sim, iv);
    }
    FUN_00c8d060(a1->FUN00b8de30());
}

// @ 0x00be9cb0
void Sim::sub_be9cb0(int a1, int a2, int a3, int a4)
{
    this->map1.clear();
    this->map2.clear();
    this->map3.clear();
    int v = this->f64c;
    this->map1[a1] = v;
    this->sub_be92e0(a1, a2, a3, 0, a4);
}

// @ 0x00be9d60
namespace SP {
void cCity_s00be_9d60::UpdateLanes()
{
    mLanes.clear();

    const int numBuildings = (int)(mBuildingsEnd - mBuildingsBegin);
    const int numPoints = numBuildings * 6;

    CenterFixedVector centers;
    PointFixedVector points;

    const float innerRadius = mpCityWalls->mInnerRadius;

    // 2. building centres and their 6-point rings
    for (int i = 0; i < numBuildings; ++i) {
        LaneCenter& center = centers.push_back();
        center.mPosition = mBuildingsBegin[i]->func8Ch();
        if (mBuildingsBegin[i] == mpCityHall)
            center.mRadius = 15.0f;
        else
            center.mRadius = min_alt(mBuildingsBegin[i]->mSpatial.GetFootprintRadius(), 8.0f);

        static cCommunityLayout_s00be_9d60 sLayout;
        sLayout.SetCenter(center.mPosition, center.mRadius, mSpatial.GetDirection(0.0f));
        sLayout.GenerateSlots(1.0f, 1.0f, 6);

        for (int k = 0; k < 6; ++k) {
            points.push_back().mPosition = sLayout.mSlotsBegin[k].mPosition;
            points.back().mMergedInto = -1;
            points.back().mLaneIndex = -1;
            points.back().mLink = -1;
            points.back().mbInside = (sLayout.mSlotsBegin[k].mPosition - mSpatial.GetPosition()).Length() < innerRadius;
        }
    }

    // 3. push the points out of the buildings
    const float pushStrength = g_LanePushStrength;
    for (int pass = 0; pass < 4; ++pass) {
        for (int p = 0; p < numPoints; ++p) {
            const Vector3_s00be_9d60 pos = points.mpBegin[p].mPosition;
            for (int b = 0; b < numBuildings; ++b) {
                const Vector3_s00be_9d60 d = pos - centers.mpBegin[b].mPosition;
                const float len = d.Length();
                float depth = len - centers.mpBegin[b].mRadius;
                if (depth < 8.0f) {
                    const Vector3_s00be_9d60 dir = d * (1.0f / len);
                    if (depth < 1.52587890625e-05f)
                        depth = 0.01f;
                    points.mpBegin[p].mPosition += dir * ((8.0f - depth) * pushStrength);
                }
            }
        }
    }

    for (int p = 0; p < numPoints; ++p)
        points.mpBegin[p].mbInside = (points.mpBegin[p].mPosition - mSpatial.GetPosition()).Length() < innerRadius;

    // 4. merge close points of later rings
    const int numMergeable = numPoints - 6;
    int nextRing = 6;
    const float mergeDistance = g_LaneMergeDistance;
    for (int i = 0; i < numMergeable; ++i) {
        if (points.mpBegin[i].mbInside && points.mpBegin[i].mMergedInto == -1) {
            Vector3_s00be_9d60 pos = points.mpBegin[i].mPosition;
            for (int j = i + nextRing; j < numPoints; ++j) {
                LanePoint& other = points.mpBegin[j];
                if (other.mbInside && other.mMergedInto == -1) {
                    const Vector3_s00be_9d60 d = pos - other.mPosition;
                    if (d.Length() < mergeDistance) {
                        other.mMergedInto = i;
                        pos = (other.mPosition + pos) * 0.5f;
                    }
                }
            }
            points.mpBegin[i].mPosition = pos;
        }
        if (nextRing == 1)
            nextRing = 6;
        else
            --nextRing;
    }

    // 5. link the rings of buildings the walls connect
    int slots[14];
    for (int i = 0; i < numBuildings; ++i)
        slots[i] = mBuildingLayout.GetSlotIndex(mBuildingsBegin[i]);

    for (int i = 0; i < numBuildings; ++i) {
        const int iBase = i * 6;
        for (int j = i + 1; j < numBuildings; ++j) {
            const int jBase = j * 6;
            if (!mpCityWalls->mBuildingLinks[slots[i]][slots[j]])
                continue;

            int k;
            for (k = 0; k < 6; ++k) {
                const int merged = points.mpBegin[jBase].mMergedInto;
                if (merged >= iBase && merged < iBase + 6)
                    break;
            }
            if (k != 6)
                continue;

            int bestI = -1;
            int bestJ = -1;
            float bestDistI = 3.4028234663852886e+38f;
            float bestDistJ = 3.4028234663852886e+38f;
            for (int m = 0; m < 6; ++m) {
                const LanePoint& a = points.mpBegin[iBase + m];
                if (a.mbInside && a.mLink == -1) {
                    const float dist = (a.mPosition - centers.mpBegin[j].mPosition).Length();
                    if (dist < bestDistI) {
                        bestDistI = dist;
                        bestI = iBase + m;
                    }
                }
                const LanePoint& b = points.mpBegin[jBase + m];
                if (b.mbInside && b.mLink == -1) {
                    const float dist = (b.mPosition - centers.mpBegin[i].mPosition).Length();
                    if (dist < bestDistJ) {
                        bestDistJ = dist;
                        bestJ = jBase + m;
                    }
                }
            }
            if (bestI != -1 && bestJ != -1) {
                points.mpBegin[bestI].mLink = bestJ;
                points.mpBegin[bestJ].mLink = bestI;
            }
        }
    }

    // 6. one lane per unmerged inside point
    int numLanes = 0;
    for (int p = 0; p < numPoints; ++p) {
        LanePoint& pt = points.mpBegin[p];
        if (pt.mbInside) {
            if (pt.mMergedInto == -1) {
                mLanes.push_back();
                mLanes.back().mPosition = pt.mPosition;
                pt.mLaneIndex = numLanes++;
            } else {
                pt.mLaneIndex = points.mpBegin[pt.mMergedInto].mLaneIndex;
            }
        }
    }

    // connect each point's lane to its ring neighbours and to its link
    int corner = 0;
    for (int p = 0; p < numPoints; ++p) {
        const LanePoint& pt = points.mpBegin[p];
        if (pt.mbInside) {
            cLaneInfo_s00be_9d60& lane = mLanes.mpBegin[pt.mLaneIndex];
            const LanePoint& next = points.mpBegin[(corner == 5) ? p - 5 : p + 1];
            if (next.mbInside)
                AddConnection(lane.mConnections, next.mLaneIndex);
            const LanePoint& prev = points.mpBegin[(corner == 0) ? p + 5 : p - 1];
            if (prev.mbInside)
                AddConnection(lane.mConnections, prev.mLaneIndex);
            if (pt.mLink != -1)
                AddConnection(lane.mConnections, points.mpBegin[pt.mLink].mLaneIndex);
        }
        if (corner == 5)
            corner = 0;
        else
            ++corner;
    }
}
}  // namespace SP

// @ 0x00bea930
void Sim_s00be_a930::sub_bea930()
{
    unsigned __int64 now = ((Clock*)S_b3d380())->getTime();
    unsigned int i = 0;
    unsigned int off = 0;
    while (i < (unsigned int)((int)(this->end - this->begin) >> 5)) {
        Elem* e = (Elem*)(this->begin + off);
        if (e->time <= now) {
            if (e->type == 0x5f601f4) {
                float f = e->f;
                int v = e->v;
                if (f > 100.0f) {
                    this->i75c = -1;
                    this->f758 = 0.0f;
                    this->FUN00be9cb0(v, 2, 0, 0);
                } else {
                    this->i75c = v;
                    this->f758 = f;
                }
            }
            *(Elem*)(this->begin + off) = *(Elem*)(this->end - 32);
            this->end -= 32;
        } else {
            ++i;
            off += 32;
        }
    }
}

// @ 0x00beaa30
void Sim_s00be_a930::sub_beaa30()
{
    int key = this->f754;
    if (key == -1)
        return;
    if (key == VGETID(this->p590))
        return;
    if (this->f750 < 100.0f)
        return;
    if ((void*)GetCurrentGameMode() == (void*)&DAT_01654c04) {
        cGameNounManager_s00be_a930* nm = GetNounManager_s00be_a930();
        void* civ = nm->GetPlayerCivilization();
        if (civ == this->p590) {
            GetCivModeStrategy_s00be_a930()->PostFeedback(this, 0x784a4055, 0x2bb7aff, V120M(this, 0x2c), 0, 1, 0);
        } else {
            void* r = GetNounManager_s00be_a930()->FUN00b25f40(key);
            if (r == civ) {
                GetCivModeStrategy_s00be_a930()->PostFeedback(this, 0x493b63b0, 0x2bb7aff, V120M(this, 0x2c), 0, 1, 0);
            } else if (*((char*)r + 0x8a) == 0) {
                this->sub_bd9a00(r);
            }
        }
    }
    this->map1.clear();
    this->map2.clear();
    this->map3.clear();
    this->map1[key] = this->f64c;
    this->sub_be92e0(key, 1, 0, 0, 0);
}

// @ 0x00beabb0
void Sim_s00be_a930::sub_beabb0()
{
    if (!this->timer770.FUN_feba90())
        return;

    unsigned __int64 ticks = this->timer770.FUN_bc3190();
    float secs = ticks * 0.001f;

    if (secs < 20.0f) {
        float ang = secs * 0.05f * 1.5707964f;
        float* fwd = (float*)V120M(this, 0x2c);
        float fx = fwd[0], fy = fwd[1], fz = fwd[2];
        float inv = (float)(1.0 / sqrt((double)(fx * fx + fy * fy + fz * fz + 1e-8f)));
        float nx = -(fx * inv), ny = -(fy * inv), nz = -(fz * inv);
        cPlanetModel_s00be_a930* pm = S_b3d350();
        float s = (float)((1.0 - cos(ang)) * pm->FUN_00b7e4d0()) * 2.1f;
        float ox = nx * s, oy = ny * s, oz = nz * s;
        float* pos = (float*)V120M(this, 0x2c);
        float px = ox + pos[0], py = oy + pos[1], pz = oz + pos[2];

        GameVec* vec = GetNounManager_s00be_a930()->GetGameDataVector(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
            (void*)FUN_00b1e500, (void*)0x018c43e8);
        int cnt = (int)(vec->end - vec->begin);
        int me = VGETID(this);
        float negnx = -nx, negny = -ny, negnz = -nz;
        for (int i = 0; i < cnt; ++i) {
            Veh* v = vec->begin[i];
            if (VGETID(v) != me) {
                float* q = (float*)V120M(v, 0x2c);
                float dx = q[0] - px, dz = q[2] - pz, dy = q[1] - py;
                float d = (float)(1.0 / sqrt((double)(dx * dx + dz * dz + dy * dy + 1e-8f)));
                if (0.0f < d * dx * negnx + dz * d * negnz + dy * d * negny) {
                    v->f762 = 1;
                    void* listener = 0;
                    void* fxmgr = FUN_0067ddd0();
                    char ok = ((char(__thiscall*)(void*, unsigned, int, void**))VCALL(fxmgr, 0x2c))
                                  (fxmgr, 0xbbc37988, 0, &listener);
                    if (ok) {
                        XformMsg_s00be_a930 ev;
                        ev.ctor();
                        float* q2 = (float*)V120M(v, 0x2c);
                        ((int*)ev.pos)[0] = ((int*)q2)[0];
                        ((int*)ev.pos)[1] = ((int*)q2)[1];
                        ((int*)ev.pos)[2] = ((int*)q2)[2];
                        ev.flags |= 4;
                        ev.count += 1;
                        Matrix33T m;
                        Matrix3FromQuaternion(m, (const void*)V120M(v, 0x30));
                        ev.mat = m;
                        ev.flags |= 2;
                        ev.count += 1;
                        ((void(__thiscall*)(void*, XformMsg_s00be_a930*))VCALL(listener, 0x18))
                            (listener, &ev);
                        Noun590* pl = (Noun590*)this->p590;
                        float snap[3];
                        snap[0] = pl->f0c4;
                        snap[1] = pl->f0c8;
                        snap[2] = pl->f0cc;
                        ((void(__thiscall*)(void*, int, float*, int))VCALL(listener, 0x44))
                            (listener, 5, snap, 3);
                        ((void(__thiscall*)(void*, int))VCALL(listener, 8))(listener, 0);
                    }
                    v->sub_be9cb0(me, 1, 0, 0);
                    if (listener)
                        ((void(__thiscall*)(void*))VCALL(listener, 4))(listener);
                }
            }
        }
        return;
    }

    this->FUN00bda0a0();
    GameVec* vec = GetNounManager_s00be_a930()->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
        (void*)FUN_00b1e500, (void*)0x018c43e8);
    int cnt = (int)(vec->end - vec->begin);
    int me = VGETID(this);
    for (int i = 0; i < cnt; ++i) {
        Veh* v = vec->begin[i];
        if (VGETID(v) != me)
            v->sub_be9cb0(me, 1, 0, 0);
    }
}

// @ 0x00beb1c0
void Sim_s00be_a930::sub_beb1c0(int idx, int p)
{
    Veh*    veh = this->vehBegin[idx];
    int     u   = veh->f1dc;
    Slot80* sl  = (Slot80*)(this->arr618 + idx * 0x80);

    ((Noun590*)this->p590)->FUN_00bef890();
    this->FUN00c00b00(1, u);

    int   slot;
    int   n     = 0;
    int*  it    = this->map1.Find(&slot, &u);
    if (*it != (int)((char*)this + 0x5a4))
        n = this->map1[u];

    float g = 0.0f;
    int   h = 0;
    veh->FUN_00bd85c0(&g, &h);
    float A = 0.0f;
    ((InteractCtx*)0x0169c255)->FUN_00cee8e0(g, h, &A);
    float B = 0.0f;
    ((InteractCtx*)0x0169c255)->FUN_00cee920(this, n, A, p, &B);

    int span = sl->w[0] - sl->w[2];
    int fi   = 0;
    if (0 < span) {
        float frac = 0.0f;
        ((InteractCtx*)0x0169c255)->FUN_00cee9c0(B, A, &frac);
        frac = __max(frac, 0.0f);
        frac = __min(frac, 1.0f);
        fi = (int)((float)this->f64c * frac * 0.25f);
        if (span < fi) fi = span;
    }

    float l30 = 0.0f;
    float q   = 0.0f;
    ((InteractCtx*)0x0169c255)->FUN_00ceea20(B, &q, &l30);
    q = __max(q, 0.0f);
    q = __min(q, 1.0f);
    l30 = __max(l30, 0.0f);
    l30 = __min(l30, 1.0f);
    if (1.0f < q + l30) { l30 *= 0.5f; q *= 0.5f; }
    sl->f24 = q;
    sl->f28 = l30;
    sl->f2c = 1.0f - (q + l30);
    veh->f20c = l30;
    veh->f210 = q;

    int l2c = 0;
    if (!sl->t30.FUN_feba90()) {
        sl->t30.FUN_bc30f0();
    } else {
        unsigned __int64 t = sl->t30.FUN_bc3190();
        if ((int)(t >> 32) != 0 || 1000 < (unsigned int)t) {
            ((InteractCtx*)0x0169c255)->FUN_00ceedb0(B, &l2c);
            sl->t30.FUN_bc3130();
        }
    }

    int extra = (l2c - sl->w[2]) - fi;
    if (0 < extra) l2c -= extra;
    int flag = 0;
    if (sl->w[3] == 0) {
        if (l2c < 1) goto L;
        sl->t50.FUN_bc3130();
    } else {
        unsigned __int64 t2 = sl->t50.FUN_bc3190();
        if (t2 <= (unsigned __int64)(long long)DAT_0169cbe0) goto L;
        flag = 1;
        sl->t50.FUN_bc3130();
    }
L:
    sl->w[6]   = fi;
    sl->w[7]   = l2c;
    sl->w[3]  += l2c - flag;
    sl->w[2]  += fi - l2c;
    sl->w[4]   = l2c;
    sl->w[5]   = flag;
    if (0 < l2c)
        this->sub_beb090(u, l2c);

    if (sl->obj70 != 0) {
        float pf = 0.0f;
        ((InteractCtx*)0x0169c255)->FUN_00ceea90(B, &pf);
        Veh* obj = 0;
        if (sl->obj70 != 0)
            obj = (Veh*)((void*(__thiscall*)(void*, int))VCALL((void*)sl->obj70, 0xb8))
                      ((void*)sl->obj70, 0x137e8e0);
        if (0.0f < pf) {
            void* inner = (void*)((char*)obj + 0x508);
            void* r = ((void*(__thiscall*)(void*, int, void*, int))VCALL(this->p590, 0x4c))
                          (this->p590, 1, &DAT_0168c398, 0);
            ((void(__thiscall*)(void*, float, void*))VCALL(inner, 0x18))(inner, pf, r);
        }
        obj->FUN_00ca8120(0);
    }
}

// @ 0x00beb5c0
void Sim_s00be_a930::sub_beb5c0()
{
    int n = (int)((char*)this->vehEnd - (char*)this->vehBegin) >> 2;
    int count = 0;
    bool any = false;
    for (unsigned j = 0; j < (unsigned)n; ++j)
        count += (this->vehBegin[j]->f1d8 == 2);
    for (unsigned j = 0; j < (unsigned)n; ++j) {
        this->vehBegin[j]->f214 = (int)(this->vehBegin[j]->f214 * 0.8f);
        if (this->vehBegin[j]->f1d8 == 2) {
            this->sub_beb1c0(j, count);
            any = true;
        } else {
            this->sub_bd9ed0(j);
        }
    }
    if (!any)
        this->sub_be11f0();
}

// @ 0x00beb6d0
void Sim_s00be_b6d0::sub_beb6d0()
{
    ClearTree(tree0);
    ClearTree(tree1);

    uint8_t* base = m618;
    void*    ids  = m62c;
    int i = 0;
    int off = 0x10;
    do {
        uint8_t* rec = base + i;
        *(uint32_t*)(rec + off + 8)    = 0;
        *(uint32_t*)(rec + off)        = 0;
        rec[0x20]                      = 0;
        *(uint32_t*)(rec + off + 0x0c) = 0;
        *(uint32_t*)(rec + off + 4)    = 0;
        rec[0x20]                      = 0;

        void* old  = *(void**)(base + i + 0x70);
        void* slot = *(void**)((char*)ids + (i >> 2) * 4);
        void* nu   = 0;
        void* r    = ((IdHash*)slot)->FindId((uint32_t)(uintptr_t)slot);
        if (r) {
            void* fn = *(void**)(*(uint32_t*)r + 0x0c);
            nu = ((void* (__thiscall*)(void*, uint32_t))fn)(r, 0x01186577);
        }
        void** p = (void**)(base + i + 0x70);
        void* cur = *p;
        if (nu != cur) {
            if (nu) ((IObj_s00be_b6d0*)nu)->AddRef();
            *p = nu;
            if (cur) ((IObj_s00be_b6d0*)cur)->Release();
        }
        *(uint8_t*)(base + i + 0x74) = (old != *(void**)(base + i + 0x70));
        i += 0x80;
        off += 0x80;
    } while (off < 0x210);

    NounManager_s00be_b6d0();
    int empire = GetPlayerEmpireOrMinus1();
    int self_emp = ((int (__thiscall*)(void*))*(void**)(*(uint32_t*)this + 0x4c))(this);
    if (self_emp == empire) {
        uint64_t t = ((TimerOps*)timer)->Elapsed() - 0x36b1;
        if ((uint32_t)(t >> 32) == 0 && (uint32_t)t <= 999) {
            void* s = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)sub_034 + 4))(sub_034);
            uint32_t h = FNV1_String16(s, 0x811c9dc5, 1);
            ((EventLogOps*)EventLog(0x38320b95, 0, h))->RemoveAllEventsOfSameType();
        }
    }

    if (GetCurrentGameMode() != (void*)0x01654c05) {
        for (void** p = f340; p != f344; ++p) {
            void* o = *p;
            float f = FUN_00b685e0(o);
            if (f < 1.0f && 0.0f < f)
                FUN_00b69930(o, g13eb1bc, 0);
        }
        for (void** p = f354; p != f358; ++p) {
            void* o = *p;
            float f = FUN_00b685e0(o);
            if (f < 1.0f && 0.0f < f)
                FUN_00b69930(o, g13eb1bc, 0);
        }
    }

    ((SimOps*)this)->sub_beabb0();
    ((SimOps*)this)->FUN_00bdbe50();
    ((SimOps*)this)->sub_bea930();
}

// @ 0x00bebc90
uint32_t GetClassId(int a, int b)
{
    switch (a) {
    case 1:
        switch (b) {
        case 1: return 0x1c67c10a;
        case 2: return 0x1c67c10b;
        default: return 0x1844dce8;
        }
    case 2:
        switch (b) {
        case 1: return 0xd18d8db;
        case 2: return 0xd18d8da;
        default: return 0xf2a53913;
        }
    default:
        switch (b) {
        case 1: return 0xff301c01;
        case 2: return 0xff301c00;
        default: return 0x7b29ee1;
        }
    }
}

// @ 0x00bebd00
uint32_t GetIID(int a)
{
    switch (a) {
    case 0: return 0xc5c4bf13;
    case 1: return 0x7b2047fb;
    case 2: return 0xd513545d;
    case 3: return 0x4dc37ba5;
    default: return 0xc5c4bf13;
    }
}

// @ 0x00bec0f0
uint32_t cCityWalls_s00be_b6d0::PointInsideWall(const Vector3_s00be_b6d0& p)
{
    Vector3_s00be_b6d0* c = Sub()->v2c();
    float dx = p.x - c->x;
    float dy = p.y - c->y;
    float dz = p.z - c->z;
    if ((float)sqrt((double)(dx * dx + dy * dy + dz * dz)) < mOuterRadius)
        return true;
    return false;
}

// @ 0x0132cb50
void FUN_0132cb50()
{
    ADD_ATTR(sCityAttributes, 0, "mGateIndex", 0x03dea810, 0x1d4, Read_00bb9cd0, Write_00bb9d00, ReadText_00693070, WriteText_00694f80, Valid<TGateIndex>, ToXml_00595a50)
    ADD_ATTR(sCityAttributes, 1, "mAttackState", 0x03df32d5, 0x1d8, Read4<TAttackStateIdx>, Write4<TAttackStateIdx>, ReadTextT<TAttackStateIdx>, WriteTextT<TAttackStateIdx>, Valid<TAttackStateIdx>, ToXmlT<TAttackStateIdx>)
    ADD_ATTR(sCityAttributes, 2, "mAttackState", 0x03df32d6, 0x1d8, Read4<TAttackStateTime>, Write4<TAttackStateTime>, ReadTextT<TAttackStateTime>, WriteTextT<TAttackStateTime>, Valid<TAttackStateTime>, ToXmlT<TAttackStateTime>)
    ADD_ATTR(sCityAttributes, 3, "mAttackerPoliticalID", 0x03dad664, 0x1dc, Read4<TAttackerPoliticalID>, Write4<TAttackerPoliticalID>, ReadText_00693090, WriteText_00694f00, Valid<TAttackerPoliticalID>, ToXml_00675ca0)
    ADD_ATTR(sCityAttributes, 4, "mAttackers", 0x03e0c0b0, 0x1f4, Read_00be0810, Write_00aca730, ReadTextT<TAttackers>, WriteTextT<TAttackers>, Valid_00b6f860, ToXml_00c6c390)
    ADD_ATTR(sCityAttributes, 5, "mpHitSphere", 0x03df010d, 0x208, Read_00bd0cb0, Write_00bca960, ReadTextT<THitSphere>, WriteTextT<THitSphere>, Valid_00b6f550, ToXml_00ac8050)
}

// @ 0x0132d6d0
void _E445()
{
    PropDesc d;
    d.mpName = "miHousingAmount";
    d.mnId = 0x3067d12;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x31c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156ea28 = d;
    d.mpName = "mFrameRate";
    d.mnId = 0x3067d14;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00ac88f0;
    d.mpFn[3] = fn_006930b0;
    d.mpFn[4] = fn_00694fc0;
    d.mnOffset = 0x338;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00acbb80;
    g_156ea64 = d;
    d.mpName = "mbIsPlayerCity";
    d.mnId = 0x3067d18;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00ac8750;
    d.mpFn[2] = fn_00ac8780;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694fa0;
    d.mnOffset = 0x33c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057ce00;
    g_156eaa0 = d;
    d.mpName = "mBuildingPlacementAngleDelta";
    d.mnId = 0x3067d19;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x594;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156eadc = d;
    d.mpName = "mBuildingPlacementRadius";
    d.mnId = 0x3067d1a;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00ac88f0;
    d.mpFn[3] = fn_006930b0;
    d.mpFn[4] = fn_00694fc0;
    d.mnOffset = 0x598;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00acbb80;
    g_156eb18 = d;
    d.mpName = "mAngle";
    d.mnId = 0x3067d1b;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x59c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156eb54 = d;
    d.mpName = "mpCityHall";
    d.mnId = 0x3067d1c;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00bdc690;
    d.mpFn[2] = fn_00bca960;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x320;
    d.mpFn[5] = fn_00b6f550;
    d.mpFn[6] = fn_00ac8050;
    g_156eb90 = d;
    d.mpName = "mpCityWalls";
    d.mnId = 0x3067d1d;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00bdc6c0;
    d.mpFn[2] = fn_00bca960;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x324;
    d.mpFn[5] = fn_00b6f550;
    d.mpFn[6] = fn_00ac8050;
    g_156ebcc = d;
    d.mpName = "mBuildings";
    d.mnId = 0x3067d1f;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00be08f0;
    d.mpFn[2] = fn_00aca730;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x340;
    d.mpFn[5] = fn_00b6f860;
    d.mpFn[6] = fn_00c6c390;
    g_156ec08 = d;
    d.mpName = "mTradePartners";
    d.mnId = 0x455e96b;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00be2c00;
    d.mpFn[2] = fn_00bda470;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x55c;
    d.mpFn[5] = fn_00bdc6f0;
    d.mpFn[6] = fn_00aeacc0;
    g_156ec44 = d;
    d.mpName = "mAllegianceBucket";
    d.mnId = 0x3067d23;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00bab620;
    d.mpFn[2] = fn_00ba7590;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x5a0;
    d.mpFn[5] = fn_00d011e0;
    d.mpFn[6] = fn_00fe4be0;
    g_156ec80 = d;
    d.mpName = "mAllegianceConversionDeltas";
    d.mnId = 0x4f67a4d;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00bab620;
    d.mpFn[2] = fn_00ba7590;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x5bc;
    d.mpFn[5] = fn_00d011e0;
    d.mpFn[6] = fn_00fe4be0;
    g_156ecbc = d;
    d.mpName = "mAllegianceUnconversionDeltas";
    d.mnId = 0x3f19daa;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00bab620;
    d.mpFn[2] = fn_00ba7590;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x5d8;
    d.mpFn[5] = fn_00d011e0;
    d.mpFn[6] = fn_00fe4be0;
    g_156ecf8 = d;
    d.mpName = "mRoboPopulation";
    d.mnId = 0x3067d25;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x64c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156ed34 = d;
    d.mpName = "mSpeciesKey";
    d.mnId = 0x3f65134;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00ae3430;
    d.mpFn[2] = fn_00ae3450;
    d.mpFn[3] = fn_00693150;
    d.mpFn[4] = fn_00695080;
    d.mnOffset = 0x658;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00ae5720;
    g_156ed70 = d;
    d.mpName = "mpCityTerritory";
    d.mnId = 0x3067d27;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00bdc740;
    d.mpFn[2] = fn_00bca960;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x328;
    d.mpFn[5] = fn_00b6f550;
    d.mpFn[6] = fn_00ac8050;
    g_156edac = d;
    d.mpName = "mVehicleSpecialty";
    d.mnId = 0x3067d29;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x540;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156ede8 = d;
    d.mpName = "mWaterFraction";
    d.mnId = 0x3d06556;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00ac88f0;
    d.mpFn[3] = fn_006930b0;
    d.mpFn[4] = fn_00694fc0;
    d.mnOffset = 0x53c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00acbb80;
    g_156ee24 = d;
    d.mpName = "mCulturalTargets";
    d.mnId = 0x3d5d0d0;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00be09d0;
    d.mpFn[2] = fn_00aca730;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x62c;
    d.mpFn[5] = fn_00b6f860;
    d.mpFn[6] = fn_00c6c390;
    g_156ee60 = d;
    d.mpName = "mbSmallCity";
    d.mnId = 0x43f1165;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00ac8750;
    d.mpFn[2] = fn_00ac8780;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694fa0;
    d.mnOffset = 0x519;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057ce00;
    g_156ee9c = d;
    d.mpName = "mTurrets";
    d.mnId = 0x45040f1;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00be0ab0;
    d.mpFn[2] = fn_00aca730;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x354;
    d.mpFn[5] = fn_00b6f860;
    d.mpFn[6] = fn_00c6c390;
    g_156eed8 = d;
    d.mpName = "mCultureTargetInfo";
    d.mnId = 0x47fac1e;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00be6180;
    d.mpFn[2] = fn_00bda500;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x618;
    d.mpFn[5] = fn_00bda590;
    d.mpFn[6] = fn_00b03fd0;
    g_156ef14 = d;
    d.mpName = "mCivicObjects";
    d.mnId = 0x4ac8b00;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00be2d80;
    d.mpFn[2] = fn_00aca730;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x308;
    d.mpFn[5] = fn_00b6f860;
    d.mpFn[6] = fn_00c6c390;
    g_156ef50 = d;
    d.mpName = "mMoneyCount";
    d.mnId = 0x4ee8234;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x664;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156ef8c = d;
    d.mpName = "mHappyCount";
    d.mnId = 0x4ee8232;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x668;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156efc8 = d;
    d.mpName = "mUnhappyCount";
    d.mnId = 0x4ee8233;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x66c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156f004 = d;
    d.mpName = "mNewBuildings";
    d.mnId = 0x4b6fccb;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x670;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156f040 = d;
    d.mpName = "mUnused2";
    d.mnId = 0x4d95950;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x674;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156f07c = d;
    d.mpName = "mFinalIncome";
    d.mnId = 0x4b6fccc;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x678;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156f0b8 = d;
    d.mpName = "mUnused3";
    d.mnId = 0x4b6fccd;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x67c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156f0f4 = d;
    d.mpName = "mUnused4";
    d.mnId = 0x4b6fcce;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x680;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156f130 = d;
    d.mpName = "mPartyOn";
    d.mnId = 0x4c82b62;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00ac8750;
    d.mpFn[2] = fn_00ac8780;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694fa0;
    d.mnOffset = 0x698;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057ce00;
    g_156f16c = d;
    d.mpName = "mRiotOn";
    d.mnId = 0x4c82b63;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00ac8750;
    d.mpFn[2] = fn_00ac8780;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694fa0;
    d.mnOffset = 0x6c0;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057ce00;
    g_156f1a8 = d;
    d.mpName = "mCapturePercent";
    d.mnId = 0x4c82b64;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00ac88f0;
    d.mpFn[3] = fn_006930b0;
    d.mpFn[4] = fn_00694fc0;
    d.mnOffset = 0x748;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00acbb80;
    g_156f1e4 = d;
    d.mpName = "mCaptureID";
    d.mnId = 0x4c82b65;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694f00;
    d.mnOffset = 0x74c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00675ca0;
    g_156f220 = d;
    d.mpName = "mConvertPercent";
    d.mnId = 0x4c82b66;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00ac88f0;
    d.mpFn[3] = fn_006930b0;
    d.mpFn[4] = fn_00694fc0;
    d.mnOffset = 0x750;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00acbb80;
    g_156f25c = d;
    d.mpName = "mConvertID";
    d.mnId = 0x4c82b67;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694f00;
    d.mnOffset = 0x754;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00675ca0;
    g_156f298 = d;
    d.mpName = "mBuyPercent";
    d.mnId = 0x4c82b68;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00ac88f0;
    d.mpFn[3] = fn_006930b0;
    d.mpFn[4] = fn_00694fc0;
    d.mnOffset = 0x758;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00acbb80;
    g_156f2d4 = d;
    d.mpName = "mBuyID";
    d.mnId = 0x4c82b69;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694f00;
    d.mnOffset = 0x75c;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00675ca0;
    g_156f310 = d;
    d.mpName = "mFirstHarvester";
    d.mnId = 0x51de1d1;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00ac8750;
    d.mpFn[2] = fn_00ac8780;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694fa0;
    d.mnOffset = 0x760;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057ce00;
    g_156f34c = d;
    d.mpName = "mDeferredEvents";
    d.mnId = 0x664d7a7;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00be0b90;
    d.mpFn[2] = fn_00bda5d0;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x7f8;
    d.mpFn[5] = fn_00bda660;
    d.mpFn[6] = fn_00f29650;
    g_156f388 = d;
    d.mpName = "mNpcBuildingAlignment";
    d.mnId = 0x670adc1;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00692ff0;
    d.mpFn[4] = fn_00694ee0;
    d.mnOffset = 0x7f4;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057cde0;
    g_156f3c4 = d;
    d.mpName = "mModificationHandleLevel";
    d.mnId = 0x689d1c0;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694f00;
    d.mnOffset = 0x2e8;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00675ca0;
    g_156f400 = d;
    d.mpName = "mModificationHandleTexture";
    d.mnId = 0x689d1c1;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00572810;
    d.mpFn[2] = fn_00572840;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694f00;
    d.mnOffset = 0x2ec;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_00675ca0;
    g_156f43c = d;
    d.mpName = "mbSkipCaptureCinematic";
    d.mnId = 0x68dd9cc;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00ac8750;
    d.mpFn[2] = fn_00ac8780;
    d.mpFn[3] = fn_00693090;
    d.mpFn[4] = fn_00694fa0;
    d.mnOffset = 0x762;
    d.mpFn[5] = fn_00b1fbf0;
    d.mpFn[6] = fn_0057ce00;
    g_156f478 = d;
    d.mpName = "mMessiahTimer";
    d.mnId = 0x68dda9f;
    d.mnZero0 = 0; d.mnZero1 = 0;
    d.mpFn[0] = fn_00692ca0;
    d.mpFn[1] = fn_00ae3470;
    d.mpFn[2] = fn_00ae3490;
    d.mpFn[3] = fn_00c2e4e0;
    d.mpFn[4] = fn_00692fb0;
    d.mnOffset = 0x770;
    d.mpFn[5] = fn_00ae3310;
    d.mpFn[6] = fn_00ac8050;
    g_156f4b4 = d;
}

struct Be4kVec { void** begin; void** cur; void** cap; };

static void Be4kVecPush(Be4kVec* v, void* obj)
{
  if (v->cur < v->cap) {
    void** slot = v->cur;
    v->cur = slot + 1;
    if (slot) {
      *slot = obj;
      if (obj) ((void (__thiscall*)(void*))VFn(obj, 0xc))(obj);
    }
  } else {
    void* tmp = obj;
    ((void (__thiscall*)(void*, void**, void**))FUN_00ae6d20)(v, v->cur, &tmp);
    obj = tmp;
  }
  if (obj) ((void (__thiscall*)(void*))VFn(obj, 8))(obj);
}

// @ 0x00be45b0
void FUN_00be45b0(int param_1, int param_2)
{
  void* mgr = FUN_00b3d300();
  int* v = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      mgr, 0xcd7d10, 0xd3d420, 0xbe2e60, 0xb1e500, 0x24270c5);
  int n = (*(int*)((char*)v + 8) - *(int*)((char*)v + 4)) >> 2;
  Be4kVec vec;
  vec.begin = 0;
  vec.cur = 0;
  vec.cap = 0;
  for (int i = 0; i < n; ++i) {
    int* elem = ((int**)((char*)v + 4))[i];
    if (param_2 == 0) {
      int* p = *(int**)(*(int*)((char*)elem + 0x518) + 0x114);
      if (p) {
        int* q = (int*)((int (__thiscall*)(void*, int))VFn(p, 0xb8))(p, 0x137e8e0);
        if (q && (*(int*)((char*)q + 0xb20) == 0 || *(int*)((char*)q + 0xb20) == 1)) {
          if (param_1 != 0) {
            int u = ((int (__thiscall*)(void*))VFn((char*)q + 0x508, 0x10))((char*)q + 0x508);
            if (((int (__thiscall*)(void*, int))FUN_00b25f40)(FUN_00b3d300(), u) != param_1)
              continue;
          }
          void* obj = (char*)elem + 0x504;
          if (obj) ((void (__thiscall*)(void*))VFn(obj, 0xc))(obj);
          Be4kVecPush(&vec, obj);
        }
      }
    } else {
      int* p5 = *(int**)((char*)elem + 0x5d8);
      if (p5) {
        int* q = (int*)((int (__thiscall*)(void*, int))VFn(p5, 0xb8))(p5, 0x17f243b);
        if (q) {
          int* a = (int*)((int (__thiscall*)(void*, int))VFn(q, 0xc))(q, 0xe9cb8ba);
          int* d = (int*)((int (__thiscall*)(void*, int))VFn(q, 0xc))(q, 0x436f315);
          if ((a && ((int (__thiscall*)(void*))VFn(a, 0x84))(a) == param_2) ||
              (d && ((int (__thiscall*)(void*))FUN_00bce5c0)(d) == param_2)) {
            void* obj = (char*)elem + 0x504;
            if (obj) ((void (__thiscall*)(void*))VFn(obj, 0xc))(obj);
            Be4kVecPush(&vec, obj);
          }
        }
      }
    }
  }
  int m = (int)((char*)vec.cur - (char*)vec.begin) >> 2;
  for (int i = 0; i < m; ++i) {
    int* obj = ((int**)vec.begin)[i];
    if (DAT_0167a690 == 0) {
      void* p = FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
      if (p == 0)
        DAT_0167a690 = 0;
      else
        DAT_0167a690 = (int*)((int* (__thiscall*)(void*))FUN_00ae6a70)(p);
    }
    ((void (__thiscall*)(void*, void*))FUN_00ae7100)(DAT_0167a690, obj);
  }
  void* mgr2 = FUN_00b3d300();
  int* v2 = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      mgr2, 0xcd7d10, 0xd3d420, 0xae72d0, 0xb1e500, 0x18c6de8);
  int n2 = (*(int*)((char*)v2 + 8) - *(int*)((char*)v2 + 4)) >> 2;
  for (int i = 0; i < n2; ++i) {
    int* elem = ((int**)((char*)v2 + 4))[i];
    int t = *(int*)((char*)elem + 0xb20);
    if (t == 0 || t == 1) {
      if (param_1 != 0) {
        int u = ((int (__thiscall*)(void*))VFn((char*)elem + 0x508, 0x10))((char*)elem + 0x508);
        if (((int (__thiscall*)(void*, int))FUN_00b25f40)(FUN_00b3d300(), u) != param_1)
          continue;
      }
      int* pi = (int*)((Be4kThis*)elem)->FUN_00ca71d0();
      if (pi[4] == (t != 0) + 2) {
        int* r2 = 0;
        if (*(void**)pi) r2 = (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0x3d5c477);
        if (param_2 == 0 || *(int*)pi == param_2) {
          ((void (__thiscall*)(void*))FUN_00c9f250)(elem);
          ((Be4kThis*)elem)->FUN_00cac000(0, 0xc, 0);
        } else if (r2) {
          int* r3 = (int*)((int (__thiscall*)(void*))VFn(r2, 0x30))(r2);
          int ok;
          if (r3 == 0)
            ok = (param_2 == 0);
          else
            ok = (((int (__thiscall*)(void*, int))VFn(r3, 0xc))(r3, 0xee9b2232) == param_2);
          if (ok) {
            ((void (__thiscall*)(void*))FUN_00c9f250)(elem);
            ((Be4kThis*)elem)->FUN_00cac000(0, 0xc, 0);
          }
        }
      } else if (pi[4] == 1) {
        int* a = 0;
        int* d = 0;
        if (*(void**)pi) a = (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0xe9cb8ba);
        if (*(void**)pi) d = (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0x436f315);
        if (a && ((int (__thiscall*)(void*))VFn(a, 0x84))(a) == param_2) {
          ((void (__thiscall*)(void*))FUN_00c9f250)(elem);
          ((Be4kThis*)elem)->FUN_00cac000(0, 0xc, 0);
        } else if (d && ((int (__thiscall*)(void*))FUN_00bce5c0)(d) == param_2) {
          ((void (__thiscall*)(void*))FUN_00c9f250)(elem);
          ((Be4kThis*)elem)->FUN_00cac000(0, 0xc, 0);
        }
      }
    }
  }
  for (void** pp = vec.begin; pp != vec.cur; ++pp) {
    void* o = *pp;
    if (o) ((void (__thiscall*)(void*))VFn(o, 8))(o);
  }
  if (vec.begin && ((int*)vec.begin)[-1] != 0)
    FUN_00f47380(vec.begin);
}

