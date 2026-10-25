// src/game/SPGonzago/SPCity.cpp -- migrated from slice(s) s0132d6d0, s0132abc0, s00be9d60, s00be30e0, s00bdd380, s00bdb3b0, s00bd91e0, s00bd8140 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCity.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

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
cPlanetModel_s00bd_91e0*         __cdecl PlanetModel();                // 0x00b3d350
cVec<cCity_s00bd_91e0*>*         __fastcall GetCityList(int32_t nReason);   // 0x00bef6c0
bool                  __cdecl IsOnTerraformedGround(int32_t nMode, const Vector3* pPosition);   // 0x00c9e8e0
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
extern float g_168bd70;                                // 0x0168bd70
extern float g_168bd74;                                // 0x0168bd74
extern float g_168bd78;                                // 0x0168bd78
typedef unsigned long long u64;
struct ActionCircleStub {
    void* FUN_00af9ff0(u32 slot);                      // 0x00af9ff0 SlotAt ret 4
    char bytes[0x28];                                  // real cActionCircle extent
};
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
// ---- items of slice s00bdb3b0 end

// ---- items of slice s00bdd380 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier(void);
extern "C" void FUN_00bdca30();
extern "C" void FUN_00bf57b0();
extern "C" void FUN_00b7f250();
extern "C" void FUN_00c88530();
#pragma intrinsic(_ReadWriteBarrier)
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
// ---- items of slice s00bdd380 end

// ---- items of slice s00be30e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
    ecx_this->mp208->SetEffectId(0x168bd70, 5.0f);
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
        float& o = *out;
        for (cElem1f4** p = ecx_this->mBeg1f4; i < *count; ++i, ++p) {
            o += ((*p)->f0c50 + 0.5f) * 0.6666667f;
        }
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

// @ 0x00bdb880
u8 CStub::FUN_00bdb880(int spec)
{
    switch (spec) {
    case 2:
        return m590->m298 >= 3;
    case 1:
        if ((m32c != g_168bd70 || m330 != g_168bd74 || m334 != g_168bd78) &&
            m590->m298 >= 2)
            return 1;
        return 0;
    case 0:
        return m590->m298 >= 1;
    }
    return 0;
}

// @ 0x00bdba80
float CStub::FUN_00bdba80()
{
    return FUN_00bdb960() * sqrtf(m53c + 1.0f);
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

// @ 0x00be3fe0
cRefList* cAgentAction::ClearRefs()
{
    mRefs0e4.erase(mRefs0e4.mpBegin, mRefs0e4.mpEnd);
    return &mRefs0e4;
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
