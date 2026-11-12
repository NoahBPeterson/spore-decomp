// src/game/SPGonzago/_at_00bf0000.cpp -- migrated from slice(s) s00bfec30, s00bfd9f0, s00bfcc80, s00bfbbf0, s00bfb020, s00bf78d0, s00bf6cb0, s00bf5cb0, s00bf51d0, s00bf4170, s00bf2ce0, s00bf1ba0, s00bf0be0, s00befc40 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00bf0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"

// unnamed retail callees and globals (address in the comment)
extern float g_1485720;                                // 0x1485720 1.0f
extern float g_146935c;                                // 0x146935c 1200.0f
extern float g_1471064;                                // 0x1471064
extern void* g_169d3c8;                                // 0x169d3c8 CommEventMgr
extern int   g_1570840[256];                           // 0x1570840 tuning weights
#include <math.h>
#include "SP/cGameNounManager.h"
#include "SP/cGameData.h"
#include "SP/cTerrainSphere.h"
#include "SP/cPlanetModel.h"
#include <float.h>
#include "SP/cCivilization.h"
#include "SP/cCommunity.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cRelationshipManager.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCombatant.h"
#include <stddef.h>
#include <string.h>
#include <intrin.h>

// ---- items of slice s00befc40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
void* __cdecl SP_NounManager();                        // 0x00b3d300
void* __cdecl SP_RelationshipManager();                // 0x00b3d2c0
void* __cdecl SP_CommManager();                        // 0x00b3d4a0
void* __cdecl SP_ActivePlanet();                       // 0x01021260
struct PhaseRatioStub { float FUN_00bfdea0(); };        // 0x00bfdea0 (ret 0)
void  __cdecl FUN_00be9850(int a, int b);              // 0x00be9850 ret 8
struct NoopStub { void FUN_00bef850(); };               // 0x00bef850 ret 0
struct NounMgrStub {
    void* FUN_00b21410(void* a);                       // 0x00b21410 ret 4
    int   FUN_00b20790(int id);                        // 0x00b20790 ClassifyById ret 4
    void  FUN_00b23560(void* a);                       // 0x00b23560 ret 4
    void* FUN_00b25f40(int id);                        // 0x00b25f40 ret 4
    void* FUN_00b25ca0();                              // 0x00b25ca0 GetCivilizationList ret 0
    void* FUN_00b25fb0();                              // 0x00b25fb0 GetPlayerCivilization ret 0
};
struct CityStub {
    int FUN_00bd8210();                                // 0x00bd8210 GetContinent ret 0
    int FUN_00bd81d0();                                // 0x00bd81d0 GetVehicleSpecialty ret 0
    int FUN_00bd9bf0();                                // 0x00bd9bf0 GetCivilization ret 0
    void* FUN_00bd92d0();                              // 0x00bd92d0 ret 0
    u8  FUN_00bdb880(int a);                           // 0x00bdb880 ret 4
};
struct TimerStub {
    void      FUN_00bc3130();                          // 0x00bc3130 cSPTimer::Restart
    void      FUN_00bc3170();                          // 0x00bc3170 reset
    long long FUN_00bc3190();                          // 0x00bc3190 GetElapsedTime
};
struct CommMgrStub {
    u8    FUN_00ae9f10(void* a);                       // 0x00ae9f10 SpaceTool::MatchesCiv ret 4
    u8    FUN_00ae9390();                              // 0x00ae9390 ret 0
    void  FUN_00aeb760(int a, void* b, void* c, int d, int e, int f); // 0xaeb760 ret 0x18
};
struct StarRefStub {
    void* FUN_00ce6950(int a, int b, int c);           // 0x00ce6950 GetCommContext ret 0xc
};
struct RelMgrStub {
    float FUN_00d00a10(int a, int b, int c);           // 0x00d00a10 ret 0xc
};
struct TuningStub {
    void FUN_00cfe7a0(int a, int v);                   // 0x00cfe7a0 ret 8
};
struct CommEventMgrStub {
    void FUN_00cf9040(int a, int b, int c, void* d);   // 0x00cf9040 ret 0x10
};
void* __cdecl FUN_00cf74c0(int a, int b, int c, void* d); // 0x00cf74c0 ret 0x10
struct RefObj {
    virtual void AddRef();           // +0x00
    virtual void Release();          // +0x04
};
struct CivObject {
    void** vt;                                         // +0x00 (+0x48 get-id, +0x4c get-specialty)
    char pad04[0x8d - 0x04];
    u8   m8d;                                          // +0x8d
    char pad8e[0x1ec - 0x8e];
    int  m1ec;                                         // +0x1ec
    char pad1f0[0x234 - 0x1f0];
    int  m234;                                         // +0x234
};
struct CityObj {
    void** vt;
    char pad04[0x120 - 0x04];
    void* m120;                                        // +0x120
};
struct CStub {
    void** vt;                                         // +0x00
    char pad04[0x38 - 0x04];
    void* m38;                                         // +0x38
    char pad3c[0x40 - 0x3c];
    int  m40;                                          // +0x40
    char pad44[0x89 - 0x44];
    u8   m89;                                          // +0x89
    u8   m8a;                                          // +0x8a
    char pad8b[0x98 - 0x8b];
    float m98;                                         // +0x98
    int  m9c;                                          // +0x9c city-vector begin
    int  ma0;                                          // +0xa0 city-vector end
    char pada4[0xc4 - 0xa4];
    float mc4;                                         // +0xc4
    float mc8;                                         // +0xc8
    float mcc;                                         // +0xcc
    char pad_d0[0x274 - 0xd0];
    void* m274;                                        // +0x274
    char pad278[0x2a0 - 0x278];
    int     m2a0;                                      // +0x2a0
    RefObj* m2a4;                                      // +0x2a4
    RefObj* m2a8;                                      // +0x2a8
    RefObj* m2ac;                                      // +0x2ac
    char    m2b0[0x20];                                // +0x2b0 cSPTimer
    RefObj* m2d0;                                      // +0x2d0
    char    pad2d4[0x2d8 - 0x2d4];
    char    m2d8[0x20];                                // +0x2d8 cSPTimer
    RefObj* m2f8;                                      // +0x2f8
    char    pad2fc[0x300 - 0x2fc];
    char    m300[0x20];                                // +0x300 cSPTimer
    char    m320;                                      // +0x320
    char    pad321[0x328 - 0x321];
    char    m328[0x20];                                // +0x328 cSPTimer
    char    m348;                                      // +0x348
    char    pad349[0x350 - 0x349];
    char    m350[0x20];                                // +0x350 cSPTimer
    char    m370;                                      // +0x370
    char    pad371[0x378 - 0x371];
    char    m378[0x20];                                // +0x378 cSPTimer
    char    m398;                                      // +0x398
    char    pad399[0x3a0 - 0x399];
    char    m3a0[0x20];                                // +0x3a0 cSPTimer
    char    m3c0;                                      // +0x3c0
    char    pad3c1[0x3c8 - 0x3c1];
    char    m3c8[0x20];                                // +0x3c8 cSPTimer
    char    m3e8;                                      // +0x3e8
    char    pad3e9[0x3f0 - 0x3e9];
    char    m3f0[0x20];                                // +0x3f0 cSPTimer
    char    pad410[0x434 - 0x410];
    unsigned m434;                                     // +0x434
    void*    m438;                                     // +0x438
    int      m43c;                                     // +0x43c
    void*    m440;                                     // +0x440
    int      m444;                                     // +0x444
    float    m448;                                     // +0x448

    void  FUN_00befc40(CivObject* src);                // 0x00befc40
    void  FUN_00befd80(float f, u8 flag);              // 0x00befd80
    void* FUN_00befee0(float* pos, int skip);          // 0x00befee0
    u8    FUN_00beff90(float* pos, int specialty);     // 0x00beff90
    u8    FUN_00bf00a0(int continent, int specialty);  // 0x00bf00a0
    u8    FUN_00bf0110(void* a, int city);            // 0x00bf0110
    u8    FUN_00bf0130(CStub* other);                  // 0x00bf0130
    int   FUN_00bf01f0(int specialty, u8 flag);        // 0x00bf01f0
    int   FUN_00bf0260(int arg);                       // 0x00bf0260
    void  FUN_00bf02b0(void* arg, int b, int c, int d); // 0x00bf02b0
    void  FUN_00bf0330(void* city);                    // 0x00bf0330
    void  FUN_00bf03e0(CivObject* city, float f);      // 0x00bf03e0
    void  FUN_00bf04c0(u8 enable);                     // 0x00bf04c0
    float FUN_00bf0640(CivObject* object);             // 0x00bf0640
    float FUN_00bf06d0(int arg);                       // 0x00bf06d0
    void  FUN_00bf0710(int index, RefObj* a, RefObj* b);// 0x00bf0710
    void  FUN_00bf07c0();                              // 0x00bf07c0
    void  FUN_00bf0810(void* a, ...);                  // 0x00bf0810 caller cleans
    void  FUN_00bf08b0();                              // 0x00bf08b0
    void  FUN_00bf0a60(RefObj* p);                     // 0x00bf0a60
    void  FUN_00bf0b00(RefObj* p);                     // 0x00bf0b00
    void  FUN_00bf0b70(RefObj* p);                     // 0x00bf0b70

    int cityCount() { return (ma0 - m9c) >> 2; }
};
static inline void timerReset(void* p) { ((TimerStub*)p)->FUN_00bc3170(); }
extern float g_1485720;                                // 0x1485720 1.0f
extern float g_146935c;                                // 0x146935c 1200.0f
extern float g_1471064;                                // 0x1471064
extern void* g_169d3c8;                                // 0x169d3c8 CommEventMgr
extern int   g_1570840[256];                           // 0x1570840 tuning weights
// ---- items of slice s00befc40 end

// ---- items of slice s00bf0be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_civAttributes;                          // 0x0156faa8
extern int g_civUpdateCounter;                            // 0x0168cb50
extern float g_civConst1;                                 // 0x01485378
extern int   g_civSuperweaponMode;                        // 0x01654c04
struct Vec3 { float x, y, z; };
struct RandomLCG { uint32_t RandomUint32Uniform(uint32_t limit); };   // 0x00a68fb0
extern RandomLCG sMathRandom;                                          // 0x01601760
struct SPTimer
{
    unsigned __int64 GetElapsedTime();   // 0x00bc3190
    void Restart();                      // 0x00bc3130
    bool IsRunning();                    // 0x00feba90
    uint32_t pad00[0x20 / 4];            // the object is 0x20 bytes (array stride)
};
struct TimerOwner { int FUN_0104bde0(); };                 // 0x0104bde0 (ret, int)
class RCObject
{
public:
    virtual int   AddRef();                                  // +0x00
    virtual int   Release();                                 // +0x04
    virtual void  v08();                                     // +0x08
    virtual void* Cast(unsigned type);                       // +0x0c
virtual void  v10();
virtual void  v14();
virtual void  v18();
virtual void  v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
    virtual bool  IsDestroyed();                             // +0x2c
virtual void  v30();
virtual void  v34();
virtual void  v38();
virtual void  v3c();
virtual void  v40();
virtual void  v44();
virtual void  v48();
    virtual int   GetPoliticalID();                          // +0x4c
};
struct SpatialSub { void* vptr; };                       // slots 0x2c = GetPosition, 0x50 = v50
class cCivilization;
class cNounEntity
{
public:
    void**     mvptr;                        // +0x00
    uint32_t   pad04[(0x34 - 0x04) / 4];     // +0x04..0x33
    SpatialSub mSpatial34;                   // +0x34
    uint32_t   pad38[(0x120 - 0x38) / 4];    // +0x38..0x11f
    SpatialSub mSpatial120;                  // +0x120
    uint32_t   pad124[(0xb1c - 0x124) / 4];  // +0x124..0xb1b
    int        mFieldB1C;                    // +0xb1c
    int        mKindB20;                     // +0xb20

    // Functions at fixed addresses, declared as members of the placeholder class so cl emits
    // `call rel32` with `this` already in ecx (docs/codegen.md 11 / matching.md).
    int   GetCreatureCount();                // 0x00bd8120
    int   GetVehicleSpecialty();             // 0x00bd81d0
    cCivilization* FUN_00bd9bf0();           // 0x00bd9bf0 (GetCivilization)
    cNounEntity*   FUN_00bd84e0();           // 0x00bd84e0
    bool  FUN_00bdb200(void* ctx);           // 0x00bdb200 (ret 4)
    int   FUN_00bd7fc0(int pid);             // 0x00bd7fc0 (ret 4)
    void  FUN_00be9850(int pid, float v);    // 0x00be9850 (ret 8)
    int   FUN_00c9fee0();                    // 0x00c9fee0 (ret)
};
class cCivilization : public RCObject
{
public:
    void  FUN_00bf0be0(void* noun);                       // 0x00bf0be0
    int   FUN_00bf0c60(int spec, int continent, int flag, int zero);  // 0x00bf0c60
    int   FUN_00bf0cf0(int continent, int flag, int zero);            // 0x00bf0cf0
    int   FUN_00bf0d10(cNounEntity* v);                   // 0x00bf0d10
    bool  FUN_00bf0db0(void* c);                          // 0x00bf0db0
    int   Write(void* stream) const;                      // 0x00bf0e00
    int   FUN_00bf0f10();                                 // 0x00bf0f10
    int   FUN_00bf0f40();                                 // 0x00bf0f40
    void  UpdateCityMusicPosition();                      // 0x00bf0f90
    void  FUN_00bf1070();                                 // 0x00bf1070
    void  FUN_00bf1170();                                 // 0x00bf1170
    void  FUN_00bf1270();                                 // 0x00bf1270
    void  FUN_00bf14b0();                                 // 0x00bf14b0
    __declspec(noinline) bool  SuperweaponOnCooldown(int w);   // 0x00bf1790
    __declspec(noinline) float GetSuperweaponCooldown(int w);  // 0x00bf17f0
    float FUN_00bf1880(float which);                      // 0x00bf1880
    bool  FUN_00bf19c0(cCivilization* civ);               // 0x00bf19c0
    int   FUN_00bf01f0(int a, int b);                     // 0x00bf01f0 (ret 8)
    int   FUN_00bf0130(int flag);                         // 0x00bf0130 (ret 4)
    void  FUN_00bf0a60(void* noun);                       // 0x00bf0a60 (ret 4)
    int   FUN_00bfdf80();                                 // 0x00bfdf80 (ret)

    // data (retail offsets). The 4 bytes before pad50 are the inherited vptr.
    uint32_t  pad50[(0x9c - 0x04) / 4];       // +0x04..0x9b
    cNounEntity** mCitiesBegin;               // +0x9c
    cNounEntity** mCitiesEnd;                 // +0xa0
    uint32_t  mCitiesCap;                     // +0xa4
    uint32_t  padA8[(0xb0 - 0xa8) / 4];       // +0xa8..0xaf
    cNounEntity** mVehiclesBegin;             // +0xb0
    cNounEntity** mVehiclesEnd;               // +0xb4
    uint32_t  mVehiclesCap;                   // +0xb8
    uint32_t  padBC[(0xc4 - 0xbc) / 4];       // +0xbc
    float     mPrimaryColor[3];               // +0xc4 (r,g,b)
    uint32_t  padD0[(0x208 - 0xd0) / 4];      // +0xd0..0x207
    SPTimer   mTimer208;                      // +0x208
    SPTimer   mTimer228;                      // +0x228
    uint32_t  pad248[(0x274 - 0x248) / 4];    // +0x248..0x273
    void*     mpCityMusic;                    // +0x274
    uint32_t  pad278[(0x2f8 - 0x278) / 4];    // +0x278..0x2f7
    void*     mp2f8;                          // +0x2f8
    uint32_t  pad2fc;                         // +0x2fc
    SPTimer   mTimer300;                      // +0x300
    uint32_t  pad320[(0x454 - 0x320) / 4];    // +0x320..0x453
    void*     mp454;                          // +0x454
    uint32_t  pad458[(0x46c - 0x458) / 4];    // +0x458..0x46b
    cCivilization* mNemesisCiv;               // +0x46c
    TimerOwner** mpField470;                  // +0x470 (one timer owner per superweapon)
    uint32_t  pad474[(0x490 - 0x474) / 4];    // +0x474..0x48f
    SPTimer*  mSuperweaponCooldown;           // +0x490 (array of SPTimer, stride 0x20)
    uint32_t  pad494[(0x4b8 - 0x494) / 4];    // +0x494..0x4b7
    int       mForceMinDiploCount;            // +0x4b8
    int       pad4bc;                         // +0x4bc
    int       mMilitaryCaptureCount;          // +0x4c0
    int       mReligiousCaptureCount;         // +0x4c4
    int       mEconomicCaptureCount;          // +0x4c8
};
class CityMusic
{
public:
virtual void u00();
virtual void u04();
virtual void u08();
virtual void u0c();
virtual void u10();
virtual void u14();
virtual void u18();
virtual void u1c();
virtual void u20();
virtual void u24();
virtual void u28();
    virtual void v2c(unsigned v);             // +0x2c
    virtual void v30(void* v);                // +0x30
};
class Obj454
{
public:
    void**     mvptr;                        // +0x00
    uint32_t   pad04[(0x120 - 0x04) / 4];
    SpatialSub mSpatial120;                  // +0x120
};
struct NounList   { cCivilization** begin; cCivilization** end; };// 0x00b25ca0
struct NounMgr
{
    cCivilization*  GetPlayerCivilization();  // 0x00b25fb0
    void*           GetCurrentTerrainSphere();// 0x00f67d90
    NounList*       GetCivList();             // 0x00b25ca0 (returns ptr to {begin,end})
};
NounMgr* NounManager();                       // 0x00b3d300
struct RelMgr
{
    int   FUN_00ae2e20(int a, int b);                       // 0x00ae2e20
    void  FUN_00d01b80(int a, int b, int c);                // 0x00d01b80 (ret 0xc)
    float CalculateRelationshipAbsolute(int a, int b, int c);// 0x00d05a20 (ret 0xc, float in st0)
};
RelMgr* RelationshipManager();                            // 0x00b3d2c0
int GetPlayerEmpireOrMinus1();                            // 0x00b1f9d0
int GetCurrentGameMode();                                 // 0x00b5b800
int FUN_00c9fee0(void* e);                                // 0x00c9fee0
struct PlanetMdl
{
    int   GetContinent(const Vec3* p);                    // 0x00b88590
};
PlanetMdl* PlanetModel();                                 // 0x00b3d350
struct CommMgr
{
    int  FUN_00ae9390();                                  // 0x00ae9390
    void ShowCommEvent(int a, void* ctx, int id1, int id2, int e, int f); // 0x00aeb760 (ret 0x18)
};
CommMgr* CommManager();                                   // 0x00b3d4a0
struct cVarListSerializer
{
    cVarListSerializer(cCivilization* self, unsigned h, unsigned id);   // 0x00692f90 (ret 0xc)
    int  Serialize(void* stream);                                       // 0x00692900 (ret 4)
    uint32_t pad00[0xa18 / 4 - 2];
};
class Writer
{
public:
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
    virtual void* v18();                     // +0x18
};
class Stream
{
public:
virtual void o00();
virtual void o04();
virtual void o08();
virtual void o0c();
virtual void o10();
virtual void o14();
    virtual void o18();
    virtual void o1c();
    virtual Writer* v20();                   // +0x20
};
class StarCtx
{
public:
    uint32_t pad00[0x184 / 4];
    void*    mField184;                      // +0x184
};
class NounInfo
{
public:
    void*    mpObject;                       // +0x00
    uint32_t pad04[3];                       // +0x04..0x0f
    int      mKind;                          // +0x10
};
struct SubObject3c { int Serialize(void* stream); };              // 0x00b6e2d0 (ret 4)
int WriteGameData(void* civ, void* stream);                       // 0x00b18590 (ret 4)
class Cty2
{
public:
    void**     mvptr;                        // +0x00
    uint32_t   pad04[(0xb20 - 0x04) / 4];
    int        mKindB20;                     // +0xb20
    cCivilization* GetCiv();                 // 0x00bd9bf0
    cNounEntity*   FUN_00bd84e0();           // 0x00bd84e0
};
struct LivingUniverse { StarCtx* mpCtx; };                        // +0x13c
struct WTextRef   { void* p; };
LivingUniverse* FUN_01021260();                                   // 0x01021260
void  AutoRefCountAssignWText(WTextRef* dst, void* p);            // 0x00b5f950
int   FUN_00c75420(void* sphere);                                 // 0x00c75420
int   FUN_00ca71d0(void* self);                                   // 0x00ca71d0
void* GetSystemAT();                                              // 0x00a206f0
int   EA_IO_WriteUint32(void* s, const void* v, int a, int b);    // 0x0093aa70
void* FUN_00befee0(cCivilization* civ, const Vec3* pos, int b);   // 0x00befee0 (ret 8)
typedef void* (__fastcall* VFP)(void*);
typedef int   (__fastcall* VFI)(void*);
typedef char  (__fastcall* VFC)(void*);
static inline const Vec3* GetPos(SpatialSub* s) { return (const Vec3*)((VFP)((*(void***)s)[0x2c / 4]))(s); }
static inline int         Slot50(SpatialSub* s) { return ((VFC)((*(void***)s)[0x50 / 4]))(s); }
static inline int         Slot08(SpatialSub* s) { return ((VFI)((*(void***)s)[0x08 / 4]))(s); }
static inline int         Slot2c(void* o) { return ((VFI)((*(void***)o)[0x2c / 4]))(o); }
// ---- items of slice s00bf0be0 end

// ---- items of slice s00bf1ba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  g_civStarCountScale; // 0x0169cb64
extern "C" int  g_cityHousingDiv;    // 0x0169c088
extern "C" int  DAT_0167a60c;        // 0x0167a60c  Simulator::SimSingleton*
extern "C" char DAT_0145f924[];      // 0x0145f924  "Simulator/SimSingleton"
extern "C" int  g_specialtyTable[];  // 0x01469298  int[?][3]
typedef unsigned char byte;
typedef unsigned int  uint;
struct IntVec { int* begin; int* end; int* cap; };
void* __cdecl EAAllocate(uint size, const char* file, int a, int b, const char* alloc, int line); // 0x00f473a0
void  __cdecl operator_delete(void* p);                     // 0x00f47380
void* __cdecl RBTreeIncrement(void* node);                  // 0x00921580
void  __cdecl RBTreeInsert(void* node, void* anchor, void* header, int side); // 0x009216a0
int   __cdecl WriteUint32(void* stream, const void* data, int count, int a);  // 0x0093aa70
int   __cdecl ReadInt32(void* stream, void* data, int count, int a);          // 0x0093a780
int   __cdecl FUN_00555e80(int begin, IntVec* vec);          // 0x00555e80
struct StarNode
{
    StarNode* mpLeft;                      // +0x00
    StarNode* mpParent;                    // +0x04
    StarNode* mpRight;                     // +0x08
    int       mField0c;                    // +0x0c
};
struct StarTree
{
    int  mParent;                          // +0x00
    StarNode mAnchor;                      // +0x04
    uint mSize;                            // +0x14
    StarNode** find(StarNode** out, const int& key); // 0x00e39fb0
    bool ContainsMap(int key);             // 0x00bf2c80
};
void* __fastcall FUN_041ea70(void* propObj);                 // 0x0041ea70  SP::GetPropertyAsValue
void* __cdecl FUN_0102f810();                               // 0x0102f810
int   __fastcall cGameNounManager_CreateNoun(void* self, int edx, int typeKey); // 0x00b20c60
void* __fastcall cGameNounManager_GetCivilizationList(void* self);       // 0x00b25ca0
void* __fastcall cTerrainEditor_GetCurrentTerrainSphere(void* self);     // 0x00f67d90
int   __fastcall cCivilization_CountSpecialty(int self, int edx, int spec, int excl); // 0x00bf01f0
int   __fastcall cCity_UnknownBef980(void* self, int edx, int id);       // 0x00bef980
int   __fastcall cGonzagoTimer_Write(void* self, int edx, void* stream); // 0x00b638d0
int   __fastcall cGameData_Read(void* self, int edx, void* stream);      // 0x00b18600
int   __fastcall FUN_00b6e340(void* self, int edx, void* stream);        // 0x00b6e340 (this = civ+0x3c)
void* __fastcall cVarListSerializer_ctor(void* self, int edx, void* host, void* attrs, int id); // 0x00692f90
int   __fastcall cVarListSerializer_Serialize(void* self, int edx, void* stream); // 0x00693e10
void* __cdecl EA_ResourceMan_GetManager();                               // 0x0067dcd0
void* __cdecl SP_MessageServer();                                        // 0x0067dcc0
void* __cdecl SP_PropertyManager();                                      // 0x0067de30
void  __fastcall SimSingleton_ctor(void* self);                          // 0x00ae5c30
int   __cdecl SP_GetCurrentGameMode();                                   // 0x00b5b800
int   __cdecl SP_GetPlayerEmpireID();                                    // 0x01021090
int   __fastcall cSPSpaceEconomyTuning_GetVehicleCost(void* self);       // 0x0102fbb0
float __cdecl FUN_00bcdea0(int pid);                                     // 0x00bcdea0
float __cdecl FUN_00bcde40(int pid);                                     // 0x00bcde40
float __cdecl FUN_00bcde70(int pid);                                     // 0x00bcde70
int   __fastcall FUN_00bf0f40(void* self);                               // 0x00bf0f40
void  __fastcall UpdateCityMusicPosition(void* self);                    // 0x00bf0f90
IntVec* __fastcall cTribe_GetMembers(void* self);                        // 0x00c8e810
int   __fastcall cCity_GetVehicleSpecialty(void* self);                  // 0x00bd81d0
extern "C" byte DAT_0168bd6c;        // 0x0168bd6c
extern "C" int  g_civAttributes_s00bf_1ba0;     // 0x0156faa8
class cCity;
class Noun
{
public:
    void**  mvptr;                         // +0x00
    byte    pad04[0x89 - 0x04];            // +0x04..0x88
    bool    mField89;                      // +0x89
    bool    mField8a;                      // +0x8a
    byte    pad8b[0x98 - 0x8b];            // +0x8b..0x97
    float   mField98;                      // +0x98
    Noun**  mListBegin;                    // +0x9c  (mCities / mMembers)
    Noun**  mListEnd;                      // +0xa0
    uint    mListCap;                      // +0xa4

    int   GetVehicleSpecialty();           // 0x00bd81d0
    int   GetHousingAmount();              // 0x00bd8960
    int   GetMemberCount();                // 0x00c8e810 inline: (mListEnd - mListBegin) >> 2
    Noun* GetMember(int i);                // inline: mListBegin[i]
};
class cCity : public Noun
{
public:
    byte  padA8[0x519 - 0xa8];             // +0xa8..0x518
    byte  mCounterConvBusy;                // +0x519
    byte  pad51a[0x540 - 0x51a];           // +0x51a..0x53f
    int   mVehicleSpecialty;               // +0x540
};
class cSimulatorPlayerUFO
{
public:
    uint  pad00[0xb1c / 4];                // +0x00..0xb1b
    int   mFieldB1c;                       // +0xb1c
    int   mFieldB20;                       // +0xb20
};
class cSPSimulatorSpaceGame : public Noun
{
public:
    uint  padA8[(0xb0 - 0xa8) / 4];        // +0xa8..0xaf
    Noun** mNPCUFOBegin;                   // +0xb0
    Noun** mNPCUFOEnd;                     // +0xb4
    uint  padB8[(0x274 - 0xb8) / 4];       // +0xb8..0x273
    void* mpCityMusic;                     // +0x274
    uint  pad278[(0x454 - 0x278) / 4];     // +0x278..0x453
    void* mp454;                           // +0x454
    uint  pad458[(0x4ac - 0x458) / 4];     // +0x458..0x4ab
    float mField4ac;                       // +0x4ac
    float mField4b0;                       // +0x4b0
    int   GetPoliticalID();                // vtable slot 0x4c

    int   SpaceTelemetry_Add(uint species);   // 0x00bf2100
    float FUN_00bf2ae0();                     // 0x00bf2ae0
};
class cCivilization_s00bf_1ba0 : public Noun
{
public:
    uint   padA8[(0xb0 - 0xa8) / 4];       // +0xa8..0xaf
    Noun** mVehicleBegin;                  // +0xb0
    Noun** mVehicleEnd;                    // +0xb4
    uint   padB8[(0x274 - 0xb8) / 4];      // +0xb8..0x273
    void*  mpCityMusic;                    // +0x274
    uint   pad278[(0x454 - 0x278) / 4];    // +0x278..0x453
    void*  mp454;                          // +0x454
    uint   pad458[(0x4ac - 0x458) / 4];    // +0x458..0x4ab
    float  mField4ac;                      // +0x4ac
    float  mField4b0;                      // +0x4b0
    uint   pad4b4[(0x4c4 - 0x4b4) / 4];    // +0x4b4..0x4c3
    uint   pad4c4[(0x4fc - 0x4c4) / 4];    // +0x4c4..0x4fb
    int    GetPoliticalID();               // vtable slot 0x4c

    int   FUN_00bf1ba0();                                 // 0x00bf1ba0
    void  FUN_00bf1cf0(IntVec* timers);                   // 0x00bf1cf0
    int   FUN_00bf1e20();                                 // 0x00bf1e20
    void  FUN_00bf1f40(void* music);                      // 0x00bf1f40 (ret 4)
    int   FUN_00bf1fd0(int specialty);                    // 0x00bf1fd0 (ret 4)
    float FUN_00bf2170(int a, int b);                     // 0x00bf2170 (ret 8)
};
class cGameData
{
public:
    void** mvptr0;                         // +0x00
    void** mvptr1;                         // +0x04
    int    mnRefCount;                     // +0x08
    void*  mpNext;                         // +0x0c
    void*  mpPrev;                         // +0x10
    void*  mpView;                         // +0x14
    void*  mpScenarioMarker;               // +0x18
    int    mScenarioClassIndex;            // +0x1c
    byte   mField20;                       // +0x20
    byte   mIsDestroyed21;                 // +0x21
    byte   pad22[2];                       // +0x22..0x23
    uint   mID;                            // +0x24
    uint   mDefinitionID;                  // +0x28
    void*  mpGameDataOwner;                // +0x2c
    uint   mPoliticalID;                   // +0x30

    // retail cGameData extends past 0x34: its own city/tribe/vehicle lists and markers.
    Noun** mTribeBegin;                    // +0x34
    Noun** mTribeEnd;                      // +0x38
    Noun** mVehicleBegin;                  // +0x3c
    Noun** mVehicleEnd;                    // +0x40
    uint   pad44[(0x9c - 0x44) / 4];       // +0x44..0x9b
    Noun** mListBegin;                     // +0x9c
    Noun** mListEnd;                       // +0xa0
    uint   padA4[(0x484 - 0xa4) / 4];      // +0xa4..0x483

    int   Read(void* stream);              // 0x00b18600
    void* func40h();                       // 0x00bf23d0
    void* FUN_00bf2660(int);               // 0x00bf2660
    bool  StarMapContainsMap2(int value);  // 0x00bf2cb0
    int   FUN_00bf2a60();                  // 0x00bf2a60
};
class ISimulatorSerializable : public cGameData
{
public:
    uint  pad34[(0x3c - 0x34) / 4];        // +0x34..0x3b
    byte  mSub3c[0xa18];                   // +0x3c  embedded cVarListSerializer host
    int   mFieldC4;                        // +0xc4
    int   mFieldC8;                        // +0xc8
    int   mFieldCC;                        // +0xcc

    byte  ReadSerialized(void* stream);    // 0x00bf2270
};
struct StarRecord
{
    int   vptr;                            // +0x00
    int   pad04;                           // +0x04
    int   f08;                             // +0x08
    int   f0c;                             // +0x0c
    int   f10;                             // +0x10
    int   f14;                             // +0x14
    byte  f18;                             // +0x18
    int   f1c;                             // +0x1c
};
struct RanNode                          // eastl rbtree node of the functor map
{
    void* mLeft;                           // +0x00
    RanNode* mParent;                      // +0x04
    void* mRight;                          // +0x08
    void* pad0c;                           // +0x0c
    int   mField14;                        // +0x14 (the resource-man handle in the value)
    void* mField18;                        // +0x18
    int   mField1c;                        // +0x1c
};
static int MapSpecialty(int s)
{
    if (s == 1)
        return 2;
    if (s == 2)
        return 1;
    if (s == 0)
        return 0;
    return -1;
}
static int CitySpecialty(Noun* c)
{
    if (!((uint)((char*)c->mListEnd - (char*)c->mListBegin) & 0xfffffffc))
        return 0;
    Noun* first = c->mListBegin[0];
    if (first == 0)
        return 0;
    return MapSpecialty(cCity_GetVehicleSpecialty((void*)first));
}
static int SpecialtySlots(int kind)
{
    switch (kind)
    {
    case 1: case 4: case 7: return 4;
    case 2: case 5: case 8: return 6;
    case 6: case 0xb:       return 2;
    default:                return 1;
    }
}
static int CivPoliticalID(void* self)
{
    return (*(int(__fastcall**)(void*))((char*)*(int*)self + 0x4c))(self);
}
struct OtherNode
{
    void* mLeft;                           // +0x00
    OtherNode* mParent;                    // +0x04
    void* mRight;                          // +0x08
    void* pad0c;                           // +0x0c
    int   mField14;                        // +0x14
    void* mField18;                        // +0x18
    int   mField1c;                        // +0x1c
};
struct StarTreeOps
{
    void** MapInsert4(void** outIt, void* anchor, int* value, char hint);        // 0x00bf1d90
    void** MapInsertPtrFloat(void** outIt, void* anchor, int* value, char hint); // 0x00bf27a0
};
// ---- items of slice s00bf1ba0 end

// ---- items of slice s00bf2ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float DAT_0168c514;      // 0x0168c514
extern "C" float DAT_0168c518;      // 0x0168c518
extern "C" float DAT_0168c51c;      // 0x0168c51c
extern "C" int   DAT_018ea2cc;      // 0x018ea2cc
extern "C" short DAT_0145ba48[];    // 0x0145ba48  L"EA::ResourceMan::Key"
extern "C" char  DAT_013f6254;      // 0x013f6254  empty wchar buffer
extern "C" int   vtbl_014693b8[];   // 0x014693b8
extern "C" int   vtbl_014693a4[];   // 0x014693a4
extern "C" int   vtbl_0146938c[];   // 0x0146938c
extern "C" int   vtbl_0146937c[];   // 0x0146937c
extern "C" int   vtbl_01469360[];   // 0x01469360
extern "C" int   vtbl_013eb394[];   // 0x013eb394
void* __cdecl    do_copy(void* first, void* last, void* dst);                  // 0x006782c0
void* __cdecl    EAAllocate(uint size, const char* file, int a, int b, int c, int line); // 0x00f473a0
void* __cdecl    SP_BehaviorManager();                                         // 0x00b3d260
void* __cdecl    CommManager_s00bf_2ce0();                                                // 0x00b3d4a0
void* __cdecl    FUN_01021260_s00bf_2ce0();                                               // 0x01021260
int   __cdecl    FUN_00b26930();                                               // 0x00b26930
void  __fastcall FUN_00bf1b60(void* self);                                     // 0x00bf1b60
void* __fastcall GetPlayerCivilization(void* self);                            // 0x00b25fb0
void* __fastcall GetCivilizationList(void* self);                              // 0x00b25ca0
int   __fastcall CommScreen_IsActive(void* self);                              // 0x00ae9390
void* __fastcall GetCommContext(void* self, int dummy, int a, int b, int c);   // 0x00ce6950
void  __fastcall cCommManager_ShowCommEvent(void* self, int dummy, void* a, void* b, void* c, int d); // 0x00aeb760
int   __fastcall FUN_00bef620(void* self, int dummy, int a);                   // 0x00bef620
uint  __fastcall RandomUint32Uniform(void* self, int dummy, int range);        // 0x00a68fb0
void  __fastcall FUN_00ba95a0(void* self, int dummy, void* list);              // 0x00ba95a0
int   __fastcall FUN_00bd9b60(void* self);                                     // 0x00bd9b60
int*  __fastcall cCity_GetPositionPtr(void* self);                             // 0x00fa0e00
void  __fastcall FUN_00ae6970(void* self);                                     // 0x00ae6970
void  __fastcall FUN_00aed92d0(void* self);                                    // 0x00ad92d0
void  __fastcall cGonzagoTimer_dtor(void* self);                               // 0x00b638b0
void  __fastcall FUN_00b6edf0(void* self);                                     // 0x00b6edf0
void  __fastcall cGameData_dtor(void* self);                                   // 0x00b184c0
void  __fastcall SetSerializer_or_release(void* self);                         // 0x00c2e4e0
void* __cdecl    ConvertToString16(void* dst, int str, int len);              // 0x0093c5a0
int   __cdecl    FUN_00ae5530(void* a, int b, void* c, void* d);              // 0x00ae5530
typedef int (__thiscall *T0)(void*);          // virtual call, no stack args
typedef int (__thiscall *T1)(void*, int);     // virtual call, one stack arg
struct Tri { int a, b, c; };
struct Eng {
	void  Sub3b50(int noun);                              // 0x00bf3b50
	void  RemoveNoun(void* noun);                         // 0x00b225d0
	void  Eb6280(void* a);                                // 0x00eb6280
	void  NukeSubtree(void* node);                        // 0x009a9600
	void  E2ed0(void* out);                               // 0x00ae2ed0
	int   B2b10(int tag, int** out);                      // 0x00be2b10
	int   Bf2710(void* a, void* b, int c);                // 0x00bf2710
	int   Bf2e70(void* a, void* b, int c);                // 0x00bf2e70
	void* Bf2da0(void* out, void* where, void* key, int flag); // 0x00bf2da0
	void* Bf9700(int key);                                // 0x00bf9700
	int*  FindEmb(int* out, int* key);                    // 0x00e39fb0
	void* GetCommCtx(int a, int b, int c, int d);         // 0x00ce6950
	void  ShowCommEvent(void* a, void* b, void* c, int d); // 0x00aeb760
	int   RelCheck(int a);                                // 0x00bef620
	uint  RandomUniform(int range);                       // 0x00a68fb0
	void  ListCopy(void* list);                            // 0x00ba95a0
	int   AddKey(void* a, void* b, int c);                // 0x00ae5530
	void* ToString16(int a, int b);                       // 0x0093c5a0
	void  RangeInit(int a);                               // 0x00579a90
	void  WstringCtor(void* src);                          // 0x0056e2d0
};
// ---- items of slice s00bf2ce0 end

// ---- items of slice s00bf4170 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
class cCity_s00bf_4170;
class cCommunityEditor;
class cTerrainSphere;
class cPlayerCityMusic;
void operator_delete__(void* pMemory);
cPlayerCityMusic* CreateMusicForSpecialty(int nSpecialty);
void MapInsertNode(int* pParent, uint32_t key, const void* pValue);
struct Vec3_s00bf_4170 {
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
class cGameData_s00bf_4170 : public IRefCounted {
public:
    uint8_t mPad14[0x20];
};
class cEditorObject : public cGameData_s00bf_4170 {
public:
    Vec3_s00bf_4170 mPosition;                 // 0x34
    uint8_t mPad40[0x10];
    void* GetIcon();                // 0x50
    uint8_t mPad54[0xac8];
    int mCityKind;                  // 0xb1c
    int mCityLevel;                 // 0xb20
};
class cCity_s00bf_4170 : public cEditorObject {
public:
    int GetVehicleSpecialty();      // 0x94 via terrain sphere, direct here 0x00bd81d0
    void* GetCityHall();            // 0xa4 0x00bd9b40
};
class cPlayerCityMusic : public IRefCounted {
public:
    cPlayerCityMusic();
    void PlayMelody(int bLoop);
    uint8_t mPad14[0x20c];
};
class cTerrainEditor : public IRefCounted {
public:
    cTerrainSphere* GetCurrentTerrainSphere();
};
class cTerrainSphere {
public:
    uint8_t mPad00[0x1150];         // 0x00
    uint32_t mModelKind;            // 0x1150
    uint32_t mModelA;               // 0x1154
    uint32_t mModelB;               // 0x1158
    Vec3_s00bf_4170 mModelPosition;            // 0x115c
    uint32_t mModelFlags;           // 0x1168
};
class cGameNounManager : public IRefCounted {
public:
    cCommunityEditor* GetPlayerCivilization();
    void RemoveNoun(void* pNoun);
};
class cBehaviorManager {
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
    virtual void AddRemoveObject(void* pObject);   // 0x3c
};
class cSPUIEventLog {
public:
    void RemoveAllEventsOfSameType(int type);
};
cSPUIEventLog* EventLog(int type, ...);
cGameNounManager* NounManager_s00bf_4170();
cGameNounManager* NounManager_s00bf_4170(int type);
cBehaviorManager* BehaviorManager();
void* GetCurrentGameMode_s00bf_4170();
void* GetTerrainEditorObject();
extern uint8_t gGameModeCivilization;
extern uint8_t gGameModeSpace;
class cVector3Map {
public:
    uint8_t mPad00[0x04];           // 0x00
    int* mpRoot;                    // 0x04
    int* mpNil;                     // 0x08
    int* mpHead;                    // 0x0c
    uint8_t mPad10[0x08];           // 0x10
    int mCount;                     // 0x18

    Vec3_s00bf_4170* FindOrInsert(uint32_t key);   // 0x00bf5050
};
class cCommunityEditor : public cEditorObject {
public:
    // Editor flags used by the city-reduction paths.
    uint8_t mBadgeToasterShown;      // 0x89
    uint8_t mCityBadgeReady;         // 0x8a
    uint8_t mOneCityBadgeShown;      // 0x8b
    uint8_t mPad8c[0x06];
    uint8_t mCitiesInitialized;      // 0x92
    uint8_t mPad93[0x09];
    cCity_s00bf_4170** mpCitiesBegin;           // 0x9c
    cCity_s00bf_4170** mpCitiesEnd;             // 0xa0
    cCity_s00bf_4170** mpCitiesCap;             // 0xa4
    uint8_t mPadA8[0x08];
    void** mpRemovedBegin;           // 0xb0
    void** mpRemovedEnd;             // 0xb4
    uint8_t mPadB8[0x0c];
    Vec3_s00bf_4170 mSpawnPosition;             // 0xc4
    uint8_t mPadD0[0x1a4];
    cPlayerCityMusic* mpCityMusicEditor;  // 0x274
    uint8_t mPad278[0x1e0];
    IRefCounted* mpTrackedRefA;      // 0x458
    IRefCounted* mpTrackedRefB;      // 0x45c
    IRefCounted* mpTrackedRefC;      // 0x460
    uint8_t mPad464[0x6c];
    int mMaxCityCount;               // 0x4d0

    void InsertCityAt(int* pPosition, cCity_s00bf_4170* pCity, int nCount);   // 0x00bf4170
    cCommunityEditor* AttachCity(cCity_s00bf_4170* pCity);                     // 0x00bf4350
    void ReduceCitiesOnPlanet(cCity_s00bf_4170* pCity);                        // 0x00bf4370
    void DetachCity(cCity_s00bf_4170* pCity, int bRemoving);                   // 0x00bf45f0
    void NotifySubEditor();                                         // 0x00bf49e0
    void CreateVehicleFromModelType(cCity_s00bf_4170* pCity, const Vec3_s00bf_4170* pPosition);  // 0x00bf4b10
    void RemoveAllCities(cCity_s00bf_4170* pCity);                             // 0x00bf4e50
    void RebuildCityFromTerrainSphere();                            // 0x00bf4eb0
    void CreateVehicleFromTerrainSphere();                          // 0x00bf4fc0
};
void CityAddRef(cCity_s00bf_4170* pCity);
void CityRelease(cCity_s00bf_4170* pCity);
void CompanionReleaseContents(void* pObject);
void CityListAppend(cCommunityEditor* pEditor, cCity_s00bf_4170** pPosition, cCity_s00bf_4170* pCity);
void CityVectorShift(cCity_s00bf_4170** pSource, cCity_s00bf_4170** pDest, cCity_s00bf_4170** pEnd);
void CityVectorCopyFill(cCity_s00bf_4170** pDest, cCity_s00bf_4170** pSource, cCity_s00bf_4170** pEnd);
void CityVectorShiftDown(cCity_s00bf_4170** pDest, cCity_s00bf_4170** pSource, cCity_s00bf_4170** pEnd, cCity_s00bf_4170** pSlot);
void SetModelTypeKey(int* pKey, const Vec3_s00bf_4170* pValue);         // 0x00bf4a60
void ResetVector3Map(cCommunityEditor* pEditor);              // 0x00bf4a90
void ReduceCitiesForPlanet(cCommunityEditor* pEditor);        // 0x00be1150
void RefreshCityBadges();                                     // 0x00bf0f90
void RefreshCityCount();                                      // 0x00bf23d0
void RefreshCityStatistics(cCommunityEditor* pEditor);        // 0x00bf3b50
void RecomputeCommunityScore(cCommunityEditor* pEditor);      // 0x00be45b0
uint32_t GetCityCountTarget();                                // 0x00befd30
void SetCityDensity(int nDensity);                            // 0x00bef770
void ClearCitySelection();                                    // 0x00cf74c0
void ShowCityLimitToast();                                    // 0x00cf7510
void ShowCityLimitToastLong();                                // 0x00cf7500
void ShowOneCityBadge();                                      // 0x00cf7920
void UpdateCityInfoPanel(cCommunityEditor* pEditor);          // 0x00e06630
void UpdateCityBoundaries(uint32_t id);                       // 0x00c77bf0
int GetActivePlanetTier();                                    // 0x00b8dab0
int GetCityHallIcon();                                        // 0x00c710c0
void* GetCityHallEntry(int nIndex);                           // 0x00c71030
void* GetNodeParent(void* pNode);                             // 0x00c710c0
void RemoveCityHallEntry(int nIndex);                         // 0x00c71150
void UpdateCommunityCamera(cCommunityEditor* pEditor);        // 0x00e052d0
void MessageServerPost(uint32_t msgId, void* pMessage);       // inlined message post
void* SpaceGameGet();
bool IsSpaceLevelReady();                                     // 0x00b18e40
void CityVehicleCreateHook(void* pUnused);                    // 0x00be4a10
// ---- items of slice s00bf4170 end

// ---- items of slice s00bf51d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00f473a0(int size, const char* name, int a, int b,
const char* file, int line);            // 0x00f473a0
extern "C" void  __cdecl FUN_00f47380(void* p);                                // 0x00f47380
extern "C" void  __cdecl FUN_00bf4a90(void);                                   // 0x00bf4a90
extern "C" void  __cdecl FUN_00bf49e0(void* handle);                           // 0x00bf49e0
extern "C" void* __cdecl FUN_00b3d300(void);                                   // 0x00b3d300 NounManager
extern "C" void* __cdecl FUN_00b3d260(void);                                   // 0x00b3d260 BehaviorManager
extern "C" void* __cdecl FUN_00b3d350(void);                                   // 0x00b3d350 PlanetModel
extern "C" void* __cdecl FUN_00b3d4a0(void);                                   // 0x00b3d4a0 CommManager
extern "C" void* __cdecl FUN_00bf2960(void* first, void* last, void* out);      // 0x00bf2960 uninitialized copy
extern "C" void  __cdecl FUN_00befb80(void* first, void* last, void* out);      // 0x00befb80 destroy range
extern "C" void  __cdecl FUN_00bf28f0(void* dst, unsigned count, const void* value, void* pos); // 0x00bf28f0
extern "C" void  __cdecl FUN_00bf2840(void* out, void* a, void* b, void* c, void* d);           // 0x00bf2840
extern "C" void  __cdecl FUN_00bf28b0(void* a, void* b, void* c);               // 0x00bf28b0
extern "C" void  __cdecl FUN_00bf2a10(void* dst, void* first, void* last);      // 0x00bf2a10 move
extern "C" void* __cdecl FUN_00bf29c0(void* a, void* b, void* c);               // 0x00bf29c0 erase move
extern "C" void FUN_006a46a0();   // 0x006a46a0 VecC::InitValue
extern "C" void FUN_009a9600();   // 0x009a9600 rbtree::DoNukeSubtree
extern "C" void FUN_00a110b0();   // 0x00a110b0
extern "C" void FUN_00ae9390();   // 0x00ae9390 CommScreen::IsActive
extern "C" void FUN_00b20c60();   // 0x00b20c60 cGameNounManager::CreateNoun
extern "C" void FUN_00aea5d0();   // 0x00aea5d0 SPVector<AutoRefCount>::DoInsertPtr
extern "C" void FUN_00bab900();   // 0x00bab900 SPVector<AutoRefCount> insert (slow path)
extern "C" void FUN_00b25ca0();   // 0x00b25ca0 cGameNounManager::GetCivilizationList
extern "C" void FUN_00b638b0();   // 0x00b638b0 cGonzagoTimer::~cGonzagoTimer
extern "C" void FUN_00b81470();   // 0x00b81470 cPlanetModel::DistanceBetweenPoints
extern "C" void FUN_00bd9bf0();   // 0x00bd9bf0 cCity::GetCivilization
extern "C" void FUN_00be5be0();   // 0x00be5be0 city event dispatch
extern "C" void FUN_00bf0f90();   // 0x00bf0f90 UpdateCityMusicPosition
extern "C" void FUN_00bf5050();   // 0x00bf5050 cVector3Map::FindOrInsert
extern "C" void FUN_00c71040();   // 0x00c71040
extern "C" void FUN_00c9eae0();   // 0x00c9eae0
extern "C" void FUN_00ca6630();   // 0x00ca6630 cVehicle::Init
extern "C" void FUN_00ff0db0();   // 0x00ff0db0 cSpatialSnapshot::Init
extern "C" void FUN_00ff2d20();   // 0x00ff2d20
extern "C" void* __cdecl FUN_01021260_s00bf_51d0(void);                                   // 0x01021260 GetActivePlanet
static const char kAllocatorPath[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static inline void* _vt(void* obj, int byteOffset)
{
    return ((void**)*(void***)obj)[byteOffset / 4];
}
struct GonzagoTimer
{
    void*         m_vtable;          // +0x00
    int           m_refCount;        // +0x04
    unsigned int  mElapsedTimeLo;    // +0x08
    unsigned int  mElapsedTimeHi;    // +0x0c
    unsigned int  mBaseTimeLo;       // +0x10
    unsigned int  mBaseTimeHi;       // +0x14
    unsigned char mRunning;          // +0x18
    void*         mTimeFn;           // +0x1c
};
struct TimerVec
{
    GonzagoTimer* m_begin;           // +0x00
    GonzagoTimer* m_end;             // +0x04
    GonzagoTimer* m_cap;             // +0x08

    // 0x00bf51d0 erase [first, last)
    GonzagoTimer* eraseRange(GonzagoTimer* first, GonzagoTimer* last);
    // 0x00bf5220 insert <count> copies of value at pos
    void insertN(GonzagoTimer* pos, unsigned count, const GonzagoTimer* value);
    // 0x00bf5420 insert one copy of value at pos
    void insertOne(GonzagoTimer* pos, const GonzagoTimer* value);
};
struct PtrVecAt
{
    void** m_begin;                  // +0x00
    void** m_end;                    // +0x04
    void** m_cap;                    // +0x08
};
struct FeedbackSink
{
    void**  m_vtable;                // +0x00
    char    m_pad4[0xb0 - 0x04];     // +0x04 .. +0xaf
    PtrVecAt m_events;               // +0xb0
    char    m_padBC[0xd4 - 0xbc];    // +0xbc .. +0xd3
    PtrVecAt m_sounds;               // +0xd4

    void AddPair(void* obj);         // 0x00bf5630
};
struct Vector3Map
{
    char m_bytes[0x10];
};
struct CityThing
{
    char       m_pad0[0x9c];         // +0x000
    void**     m_citiesBegin;        // +0x09c
    void**     m_citiesEnd;          // +0x0a0
    char       m_padA4[0x410 - 0xa4];// +0x0a4
    Vector3Map m_map;                // +0x410

    void  UpdateDistances();         // 0x00bf59d0
    float GetDistance(void* key);    // 0x00bf5b90
};
struct CityEventSub
{
    char          m_pad0[0x51];      // +0x000
    unsigned char m_flag51;          // +0x051
    char          m_pad52[0x46c - 0x52]; // +0x052
    void*         m_civ;             // +0x46c
    int           m_soundId;         // +0x470

    bool OnEvent(int eventId, void* data); // 0x00bf5be0
};
struct VehicleFactory
{
    void* CreateVehicle(void* p2, void* p3, void* p4, void* p5,
                        void* p6, void* p7);  // 0x00bf57b0
};
struct VecC
{
    Vec3* m_data;                    // +0x00
    int   m_count;                   // +0x04
    int   m_cap;                     // +0x08
};
struct VehicleSnapshot
{
    void* m_alloc;                   // +0x00
    char  m_pad4[0x0c];              // +0x04
    Vec3  m_pos;                     // +0x10
    char  m_pad1C[0x24 - 0x1c];      // +0x1c
    float m_f24;                     // +0x24
    char  m_pad28[0x70 - 0x28];      // +0x28
    float m_f70;                     // +0x70
    float m_f74;                     // +0x74
    char  m_pad78[0x7c - 0x78];      // +0x78
    float m_f7c;                     // +0x7c
    float m_f80;                     // +0x80
    int   m_i84;                     // +0x84
};
// ---- items of slice s00bf51d0 end

// ---- items of slice s00bf5cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kRadiusScale;              // 0x156f89c
struct Entity;
struct Pos {
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
    virtual Vec3* GetPos();            // slot 11 (+0x2c)
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
    virtual Entity* GetOwnerObject();  // slot 21 (+0x54)
    virtual bool IsActive();           // slot 22 (+0x58)
};
struct Inter {
    Entity* target;
    char pad[0xc];
    int type;
};
struct Civ {
    char pad0[0x89];
    bool b89;
    bool b8a;
    char pad1[3];
    bool b8e;
    bool b8f;
};
struct Entity {
virtual void s0();
virtual void s1();
virtual void s2();
    virtual Entity* Cast(unsigned id);        // slot 3
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
    virtual bool IsDestroyed();               // slot 11
    virtual Entity* GetLinked();              // slot 12
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
    virtual void s18();
    virtual int GetPlayerID();                // slot 19
virtual void s20();
virtual void s21();
virtual void s22();
    virtual Entity* Cast2(unsigned id);       // slot 23

    char pad04[0x34 - 4];
    Pos pos34;                                // +0x34
    char pad38[0xb0 - 0x34 - 4];
    Entity** vecBegin;                        // +0xb0 (sub-entity list)
    Entity** vecEnd;                          // +0xb4
    char padb8[0x120 - 0xb8];
    Pos pos120;                               // +0x120
    char pad124[0x508 - 0x124];
    Pos pos508;                               // +0x508
    char pad50c[0xb1c - 0x50c];
    unsigned mId;                             // +0xb1c
    int mState;                               // +0xb20

    Inter* GetInter();                        // 0xca71d0
    void Order(Entity* target, int type, int z);   // 0xcac000
    Entity** GetHostiles();                   // 0xc9e860 (vector begin/end at +0/+4)
    bool CanOccupyTerrain(Vec3* p);           // 0xc9e960
    bool CanReach();                          // 0xc9f410
    bool CanTarget(Entity* t);                // 0xca8340
    bool CanTargetCity(Entity* c);            // 0xc9fe40
    void SetCount(int n);                     // 0xc9ee30
    void MoveTo(Vec3 p, int z);               // 0xcac0e0
    Civ* GetCivilization();                   // 0xbd9bf0
    Civ* GetCivOf();                          // 0xbfdf80
    Entity* GetCityOf();                      // 0xbd84e0
    int GetCapacity();                        // 0xbd9b70
    float GetFactor();                        // 0xbd7d00
    int GetBase();                            // 0xbd8960
    void GetPoint(Vec3* out, unsigned id);    // 0xbdca30
};
struct RelMgr_s00bf_5cb0 {
    int GetRelation(int a, int b, int c);     // 0xd00a70
    bool IsAllied(int a, int b);              // 0xae2e20
};
struct Timer {
    unsigned long long GetElapsedTime();      // 0xbc3190
    void Restart();                           // 0xbc3130
};
struct VecHolder { int pad; Entity** begin; Entity** end; };
struct PairVec { Entity** begin; Entity** end; };
struct NounMgr_s00bf_5cb0 {
    PairVec* GetEmpires();                    // 0xb25ca0
    int GetPlayerEmpireOrMinus1();            // 0xb1f9d0
    VecHolder* GetGameDataVector(void* a, void* b, void* c, void* d, unsigned int typeTag);  // 0xb21340
    struct Sphere* GetCurrentTerrainSphere(); // 0xf67d90
};
struct Sphere { int GetKind(); };             // 0xc75420
struct PlanetMdl_s00bf_5cb0 {
    float DistanceBetweenPoints(Vec3* a, Vec3* b);   // 0xb81470
    float GetRadius();                        // 0xb7e4d0
};
struct Rand { unsigned RandomUint32Uniform(unsigned n); };  // 0xa68fb0
struct Seed { int GetValue(); };              // 0xac15e0
RelMgr_s00bf_5cb0* RelationshipManager_s00bf_5cb0();                // 0xb3d2c0
NounMgr_s00bf_5cb0* NounManager_s00bf_5cb0();                       // 0xb3d300
PlanetMdl_s00bf_5cb0* PlanetModel_s00bf_5cb0();                     // 0xb3d350
Seed* GetSeed();                              // 0xb3d290
bool IsValidFireTarget(Pos* mine, Pos* theirs);   // 0xdc4e20 (cdecl, anonymous namespace)
extern Rand sMathRandom_s00bf_5cb0;                      // 0x1601760
void FnA();   // 0xb1e500
void FnB();   // 0xacdff0
void FnC();   // 0xd3d420
void FnD();   // 0xcd7d10
struct TribeAI {
virtual void t0();
virtual void t1();
virtual void t2();
virtual void t3();
virtual void t4();
virtual void t5();
virtual void t6();
virtual void t7();
virtual void t8();
virtual void t9();
virtual void t10();
virtual void t11();
virtual void t12();
virtual void t13();
virtual void t14();
virtual void t15();
virtual void t16();
virtual void t17();
virtual void t18();
    virtual int GetPlayerID();                // slot 19
    char pad04[0x8a - 4];
    bool mFlag8a;
    char pad8b[0x92 - 0x8b];
    bool mFlag92;
    char pad93[0x9c - 0x93];
    Entity** mListBegin;                      // +0x9c
    Entity** mListEnd;                        // +0xa0
    char pada4[0xb0 - 0xa4];
    Entity** mVehBegin;                       // +0xb0
    Entity** mVehEnd;                         // +0xb4
    char padb8[0xe8 - 0xb8];
    Timer mTimer;                             // +0xe8
    char pad_e9[0x458 - 0xe9];
    Entity* mCityA;                           // +0x458
    Entity* mCityB;                           // +0x45c
    char pad460[4];
    Entity* mCityC;                           // +0x464 (field index 0x119)

    int GetLimit(int a);                      // 0xbf1fd0
    void Update();
};
static inline bool Active(Entity* v) { return v && (v->mState == 0 || v->mState == 1); }
// ---- items of slice s00bf5cb0 end

// ---- items of slice s00bf6cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt)
typedef uint32_t u32;
typedef uint8_t  u8_s00bf_6cb0;
typedef int32_t  i32;
#define PI(p, off) (*(int*)((char*)(p) + (off)))
#define PU(p, off) (*(u32*)((char*)(p) + (off)))
#define PB(p, off) (*(u8_s00bf_6cb0*)((char*)(p) + (off)))
#define PF(p, off) (*(float*)((char*)(p) + (off)))
#define PS(p, off) ((char*)(p) + (off))
void* FUN_00b3d2c0(u32 a);                  // 0x00b3d2c0  SP::RelationshipManager
void* FUN_00b3d350(u32 a);                  // 0x00b3d350  SP::PlanetModel
void* FUN_00b3d390(u32* a, void* b);        // 0x00b3d390  vector<AutoRefCount<cPropertyList>>::erase
int   FUN_00b1f9d0();                       // 0x00b1f9d0  GetPlayerEmpireOrMinus1
void* FUN_01021260_s00bf_6cb0();                       // 0x1021260   SP::cSPLivingUniverse::GetActivePlanet
u32   FUN_00b5b800();                       // 0x00b5b800  SP::GetCurrentGameMode
int   FUN_00c70e00(void* self);             // 0x00c70e00  living-universe state query
struct ThTimer {                            // SP::cGonzagoTimer (0x20 bytes)
  void* FUN_00b63890();                     // 0x00b63890  ctor
  void  FUN_00b638b0();                     // 0x00b638b0  dtor
  void  FUN_00b63930(void* other);          // 0x00b63930  assign/copy
};
void  FUN_0093a780(void* stream, int a, int b, int c);  // 0x0093a780  EA::IO::ReadInt32
int   FUN_00b88590(void* self, u32 a);      // 0x00b88590  cPlanetModel::GetContinent
int   FUN_00b7e3e0(void* self, u32 a);      // 0x00b7e3e0  cPlanetModel continent-owner test
void  FUN_00caa610(void* self, int a);      // 0x00caa610  cVehicle::DisbandUnit
void  FUN_00cfe7a0(int a, int b);           // 0x00cfe7a0
void* FUN_00ce6950(void* self, u32 a, u32 b, int c);  // 0x00ce6950  cStarRecordRef::GetCommContext
void  FUN_00aeb760(void* self, void* a, void* b, u32 c, u32 d, u32 e);  // 0x00aeb760 cCommManager::ShowCommEvent
int   FUN_00ae9390_s00bf_6cb0();                       // 0x00ae9390  CommScreen::IsActive
u8_s00bf_6cb0    FUN_00ae2e20(void* self, u32 a);      // 0x00ae2e20  relationship/empire test
int   FUN_00d00a70(void* self, u32 a);         // 0x00d00a70  relationship level
u32   FUN_00bc3190(void* self, u32* hi);    // 0x00bc3190  SP::cSPTimer::GetElapsedTime
void  FUN_00bc3130(void* self);             // 0x00bc3130  SP::cSPTimer::Restart
int   FUN_00bf4170(void* self, int n, void* val);   // 0x00bf4170
void* FUN_00bf51d0(void* self, void* a, void* b);   // 0x00bf51d0
void  FUN_00bf5220(void* self, void* a, int n, void* val);  // 0x00bf5220
void  FUN_00bf5420(void* self, void* val);  // 0x00bf5420
void  FUN_00bf40d0(void* self, int n);      // 0x00bf40d0
struct ThNounMgr {
  void  GetGameDataVector(void* out, void* a, void* b, void* c, void* d, u32 tag);  // 0xb21340
  void* GetPlayerCivilization();            // 0xb25fb0
  void* FUN_00f67d90();                     // 0xf67d90 GetCurrentTerrainSphere
};
struct ThSphere { int FUN_00c75420(); };    // 0xc75420 GetKind
struct ThObj { int FUN_00bf0f40(); };        // 0xbf0f40 terrain-editor mode
struct ThVec2 {
  void* FUN_00bf51d0(void* a, void* b);           // 0xbf51d0
  void  FUN_00bf5220(void* a, int n, void* val);  // 0xbf5220
  void  FUN_00bf5420(void* val);                  // 0xbf5420
  void  FUN_00bf40d0(int n);                      // 0xbf40d0
};
struct ThVehl { void* FUN_00ca71d0(); };    // 0xca71d0 pony/mode getter
struct ThVec { void* FUN_004e4410(void* src); };
void  FUN_00bf5c2170(void* self, void* a, void* b);  // 0x5c2170 sp_ref_vector::erase
struct ThToolMgr { void FUN_0104e340(void* slot); };   // 0x104e340 CreateToolFromToolID
struct AI {
  char pad0[0x89];
  u8_s00bf_6cb0   mFlag89;                             // +0x89
  u8_s00bf_6cb0   mFlag8a;                             // +0x8a
  char pad8b[0x94 - 0x8b];
  u8_s00bf_6cb0   mFlag94;                             // +0x94
  char pad95[0x98 - 0x95];
  float mScore98;                           // +0x98
  void** mListBegin;                        // +0x9c
  void** mListEnd;                          // +0xa0
  char pada4[0xb0 - 0xa4];
  void** mVehBegin;                         // +0xb0
  void** mVehEnd;                           // +0xb4
  char padb8[0x1e8 - 0xb8];
  char mTimer1e8[0x470 - 0x1e8];            // +0x1e8 SP::cSPTimer (embedded)
  void** mToolBegin;                        // +0x470
  void** mToolEnd;                          // +0x474
  char pad478[0x4ac - 0x478];
  float mRadius4ac;                         // +0x4ac
  float mRadius4b0;                         // +0x4b0
  int   mTick4b4;                           // +0x4b4

  float FUN_00bf6cb0(int type);
  void  FUN_00bf6ee0();
  float FUN_00bf6fa0(u8_s00bf_6cb0 phase);
  u8_s00bf_6cb0    FUN_00bf7050();
  u8_s00bf_6cb0    FUN_00bf5720(u32 a);
  u8_s00bf_6cb0    FUN_00bf70b0(u32 a);
  int   FUN_00bf7150();
  void  FUN_00bf71d0();
  void  FUN_00bf7230();
  void  FUN_00bf7390();
  u32   FUN_00bf74a0();
  int   FUN_00bf7730(int type);
  void  FUN_00bf7760(u32 n);
  void  FUN_00bf77d0(void* stream);
  void  FUN_00befd80(float r);
};
struct Community {
  void* GetNoun();                          // 0x00bfdf80
  float ReadPhase(u8_s00bf_6cb0 phase);                // 0x00bfde50
};
// ---- items of slice s00bf6cb0 end

// ---- items of slice s00bf78d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char    DAT_01654c04;
extern char    DAT_01654c05;
extern int     DAT_0156f898;        // round-robin index into the 0x1c table
extern char    DAT_0168caf0[];      // table of 0x1c-byte records
extern char    DAT_0168cb0c[];      // &DAT_0168caf0[1]
extern wchar_t gEmptyString16[];    // 0x01667bac
extern wchar_t gEmptyString16b[];   // 0x01667bae
extern char  DAT_018c43e8;                  // table descriptor handed to GetGameDataVector
typedef unsigned char    uint8;
typedef unsigned int     uint32;
void*  MessageServer();                        // 0x0067dcc0
void*  GetCurrentGameMode_s00bf_78d0();                   // 0x00b5b800
int    FUN_00b6e050();                         // 0x00b6e050
void*  FUN_00b6f0c0(int key);                  // 0x00b6f0c0
void*  FUN_01021260_s00bf_78d0();                         // 0x01021260  GetActivePlanet
void*  FUN_01021370();                         // 0x01021370  GetPlayerHomePlanet
void*  FUN_00b26930_s00bf_78d0();                         // 0x00b26930
void*  __stdcall FUN_00b3d2a0(int id);         // 0x00b3d2a0  StarManager (callee pops)
void*  EASTLAlloc(uint32 n, const char* pName, int a, int b, const char* c, int d);  // 0x00f473a0
void   FUN_00829110(void* dst, void* first, void* last, void* a, void* b);  // 0x00829110
void   FUN_00cd7d10();                         // table entries handed to GetGameDataVector
void   FUN_00d3d420();
void   FUN_00acdff0();
void   FUN_00b1e500();
void   FUN_00ae5ea0();
void   FUN_00bf6d80();
class cCity_s00bf_78d0;
class cCivilization_s00bf_78d0;
class cGameData_s00bf_78d0;
class cGameNounManager_s00bf_78d0;
class BaseV { public: virtual void b0(); };
class ObjectBase {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void vdtor();           // 0x08
    virtual void Cast();            // 0x0c
    virtual void Write();           // 0x10
    virtual void Read();            // 0x14
    virtual void func18h();         // 0x18
    virtual void WriteToXML();      // 0x1c
    virtual int  GetNounID();       // 0x20
};
class cGameData_s00bf_78d0 : public ObjectBase, public BaseV {
public:
    virtual void SetDefinitionID();             // 0x24
    virtual void SetGameDataOwner();            // 0x28
    virtual bool IsDestroyed();                 // 0x2c
    virtual void* GetGameDataOwner();           // 0x30
    virtual void SetGameDataOwner2();           // 0x34
    virtual void* GetCastID();                  // 0x38
    virtual char cGameData_func3Ch(int param);  // 0x3c
    virtual void func40h();                     // 0x40 0x00bf23d0
    virtual void RemoveOwner();                 // 0x44
    virtual void SetPoliticalID(int id);        // 0x48 0x00804820
    virtual int  GetPoliticalID();              // 0x4c
    virtual void WriteAsText();                 // 0x50

    char FUN_00bd7c60(int owner);    // 0x00bd7c60
    void FUN_00be10d0();             // 0x00be10d0

    char mPad08[0x34 - 8];
};
class cCommunity : public cGameData_s00bf_78d0 {
public:
    void FUN_00bff750();             // 0x00bff750
    void Deactivate();               // 0x00bfe4d0
    char mPad34[0x214 - 0x34];
    cGameData_s00bf_78d0* m214;                 // +0x214
};
class Base34 { public: virtual void b0(); };
class IMessageListener {
public:
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
virtual void m28();
virtual void m2c();
};
class Base3C {
public:
    virtual void b0();
    void FUN_00c2e4e0();             // 0x00c2e4e0
    void FUN_00b6ee10();             // 0x00b6ee10
};
class cGonzagoTimer {
public:
    char mData[0x20];
    cGonzagoTimer();                                 // 0x00b63890
    ~cGonzagoTimer();                                // 0x00b638b0
    void Start();                                    // 0x00bc30f0
    unsigned __int64 GetElapsedTime();               // 0x00bc3190
    void Restart();                                  // 0x00bc3130
};
class TreeAnchor {
public:
    TreeAnchor* mpNodeLeft;          // +0x00
    TreeAnchor* mpNodeRight;         // +0x04
    TreeAnchor* mpNodeParent;        // +0x08
    char        mColor;              // +0x0c
    TreeAnchor() : mpNodeRight(0), mpNodeParent(0), mColor(0) { mpNodeLeft = this; }
};
class RBTree {
public:
    TreeAnchor mAnchor;              // +0x00
    int        mnSize;               // +0x10
    RBTree() : mnSize(0) {}
};
class Map6C {
public:
    int        mUnknown;             // +0x00
    TreeAnchor mAnchor;              // +0x04
    int        mnSize;               // +0x14
    int        mPad18;               // +0x18
    Map6C() : mnSize(0) {}
    void FUN_00bf3460(void* p);      // 0x00bf3460
    void FUN_00bf4350(void* p);      // 0x00bf4350
};
template <class T>
class Vec {
public:
    T* mpBegin;                      // +0x00
    T* mpEnd;                        // +0x04
    T* mpCap;                        // +0x08
    Vec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    T* erase(T* first, T* last);     // 0x00b48e40
    void resize(int n);
};
template <class T>
class AutoRefCount {
public:
    T* mpObject;                     // +0x00
    AutoRefCount() : mpObject(0) {}
    void Set(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
    }
};
class cGameDataVector {
public:
    char        pad00[4];
    cGameData_s00bf_78d0** mpBegin;             // +0x04
    cGameData_s00bf_78d0** mpEnd;               // +0x08
    cGameData_s00bf_78d0** mpCap;               // +0x0c
    void*       mpAlloc;             // +0x10
};
class cCivList {
public:
    cCivilization_s00bf_78d0** mpBegin;         // +0x00
    cCivilization_s00bf_78d0** mpEnd;           // +0x04
};
class cGameNounManager_s00bf_78d0 {
public:
    cCivList* GetCivilizationList();                                   // 0x00b25ca0
    cGameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
    void RemoveNoun(void* p);                                          // 0x00b225d0
    void FUN_00b21410(cCivilization_s00bf_78d0* civ);                             // 0x00b21410
    int  ClassifyById(int id);                                         // 0x00b20790
    void FUN_00b23560(cCivilization_s00bf_78d0* civ);                             // 0x00b23560
    void* GetCurrentTerrainSphere();                                   // 0x00f67d90
};
class cMessageServer {
public:
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
    virtual void m20(void* listener, int msg) {}
virtual void m24();
virtual void m28();
    virtual void m2c(void* listener, int msg, int a) {}
};
class StarManager {
public:
    int   FUN_00ba6630();                    // 0x00ba6630
    void* GetEmpireByID();                   // 0x00ba9370
};
class Empire {
public:
    void* FUN_00bce4c0();                    // 0x00bce4c0
};
class SomeAE {
public:
    char FUN_00ae3600();                     // 0x00ae3600
};
class PlanetStub {
public:
    char mPad13C[0x13c];
    volatile int m13C;                       // +0x13c
};
class TerrainSphere {
public:
    int FUN_00c75420();                      // 0x00c75420
};
class cCity_s00bf_78d0 : public cCommunity {
public:
    int  GetContinent(int def);              // 0x00bd8210
    char mPad218[0x519 - 0x218];             // +0x218
    char m519;                               // +0x519
};
class cRelationshipManager {
public:
    int   FUN_00d00a70(int a, int b, int c);              // 0x00d00a70
    float CalculateRelationshipPersonality(cCivilization_s00bf_78d0* a, cCivilization_s00bf_78d0* b);  // 0x00d02050
};
class cCivilization_s00bf_78d0 : public cGameData_s00bf_78d0, public Base34, public IMessageListener, public Base3C {
public:
    cCivilization_s00bf_78d0();                                 // 0x00bf78d0
    char cGameData_func3Ch(int param);               // 0x00bf8140 override
    void RemoveOwner();                              // 0x00bf7d80 override
    void FUN_00bf8170(int ownerId, char playerOwned, int key, char flag);  // 0x00bf8170
    void FUN_00bf8440();                             // 0x00bf8440

    void FUN_00bf23d0();                             // 0x00bf23d0
    void RebuildToolPages();                         // 0x00bf6ee0
    void FUN_00bf4eb0();                             // 0x00bf4eb0
    void FUN_00bf45f0(void* p, int a);               // 0x00bf45f0
    void FUN_00bf3b50(void* p);                      // 0x00bf3b50
    int  CommunityScoreSum();                        // 0x00bf7150
    int  FUN_00bf0f40();                             // 0x00bf0f40
    char city_on_continent(int continent);           // 0x00bf00a0

    int         m40;                                 // +0x40
    char        mPad44[0x1c];                        // +0x44
    Vec3        m60;                                 // +0x60
    Map6C       m6C;                                 // +0x6c
    uint8       m88, m89, m8A, m8B, m8C, m8D, m8E, m8F, m90, m91, m92, m93, m94;  // +0x88
    char        mPad95[3];                           // +0x95
    float       m98;                                 // +0x98
    Vec<cCity_s00bf_78d0*> mCities;                             // +0x9c
    char        mPadA8[8];                           // +0xa8
    Vec<void*>  mUnits;                              // +0xb0
    char        mPadBC[8];                           // +0xbc
    Vec3        mC4;                                 // +0xc4
    int         mD0;                                 // +0xd0
    Vec<void*>  mD4Vec;                              // +0xd4
    char        mPadE0[8];                           // +0xe0
    cGonzagoTimer mTimers[12];                       // +0xe8
    int         m268, m26C, m270;                    // +0x268
    AutoRefCount<cGameData_s00bf_78d0> mp274;                   // +0x274
    void*       mp278; void* mp27C; void* mp280;     // +0x278  mName
    char        mPad284[4];                          // +0x284
    void*       mp288; void* mp28C; void* mp290;     // +0x288  mDescription
    char        mPad294[4];                          // +0x294
    int         m298;                                // +0x298
    int         m29C;                                // +0x29c
    int         m2A0;                                // +0x2a0
    int         m2A4, m2A8;                          // +0x2a4
    AutoRefCount<cGameData_s00bf_78d0> mp2AC;                   // +0x2ac
    cGonzagoTimer mT1;                               // +0x2b0
    AutoRefCount<cGameData_s00bf_78d0> mF1; char mPad2D4[4];    // +0x2d0
    cGonzagoTimer mT2;                               // +0x2d8
    AutoRefCount<cGameData_s00bf_78d0> mF2; char mPad2FC[4];    // +0x2f8
    cGonzagoTimer mT3;                               // +0x300
    uint8       mF3; char mPad321[7];                // +0x320
    cGonzagoTimer mT4;                               // +0x328
    uint8       mF4; char mPad349[7];                // +0x348
    cGonzagoTimer mT5;                               // +0x350
    uint8       mF5; char mPad371[7];                // +0x370
    cGonzagoTimer mT6;                               // +0x378
    uint8       mF6; char mPad399[7];                // +0x398
    cGonzagoTimer mT7;                               // +0x3a0
    uint8       mF7; char mPad3C1[7];                // +0x3c0
    cGonzagoTimer mT8;                               // +0x3c8
    uint8       mF8; char mPad3E9[7];                // +0x3e8
    cGonzagoTimer mT9;                               // +0x3f0
    char        mPad410[4];                          // +0x410
    RBTree      m414;                                // +0x414  (mnSize at +0x424)
    char        mPad428[4];                          // +0x428
    void*       mp42C;                               // +0x42c
    uint8       m430, m431;                          // +0x430
    char        mPad432[2];                          // +0x432
    int         m434, m438, m43C, m440, m444;        // +0x434
    float       m448;                                // +0x448
    int         m44C, m450, m454, m458, m45C, m460;  // +0x44c
    void*       mp464;                               // +0x464
    void*       mp468;                               // +0x468
    AutoRefCount<cCivilization_s00bf_78d0> mp46C;               // +0x46c
    void*       mp470;                               // +0x470
    void*       mp474;                               // +0x474
    void*       mp478;                               // +0x478
    char        mPad47C[8];                          // +0x47c
    int         m484, m488, m48C;                    // +0x484
    Vec<cGonzagoTimer> mSuperTimers;                 // +0x490
    char        mPad49C[8];                          // +0x49c
    void*       mp4A4;                               // +0x4a4
    int         m4A8;                                // +0x4a8
    float       m4AC, m4B0;                          // +0x4ac
    int         m4B4, m4B8;                          // +0x4b4
    char        mPad4BC[4];                          // +0x4bc
    int         m4C0, m4C4, m4C8;                    // +0x4c0
    uint8       m4CC;                                // +0x4cc
    char        mPad4CD[3];                          // +0x4cd
    int         m4D0;                                // +0x4d0
};
void* FUN_01062ee0(void* p);                // 0x01062ee0
class BehaviorManager_s00bf_78d0 {
public:
virtual void b00();
virtual void b04();
virtual void b08();
virtual void b0c();
virtual void b10();
virtual void b14();
virtual void b18();
virtual void b1c();
virtual void b20();
virtual void b24();
virtual void b28();
virtual void b2c();
virtual void b30();
virtual void b34();
virtual void b38();
    virtual void b3c(void* p);
};
class TempVec {
public:
    void* mpBegin;                           // +0x00
    void* mpEnd;                             // +0x04
    void* mpCap;                             // +0x08
    void* mpAlloc;                           // +0x0c
    void FUN_00b93c60(int count, void* alloc);   // 0x00b93c60
};
// ---- items of slice s00bf78d0 end

// ---- items of slice s00bfb020 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Key { uint32_t a, b, c; };
struct Pos_s00bf_b020 {
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
    virtual Vec3* GetPos();            // slot 11 (+0x2c)
};
struct Inter_s00bf_b020 {
    struct Entity_s00bf_b020* target;             // +0x00
    char pad[0xc];
    int type;                          // +0x10
};
struct Entity_s00bf_b020 {
    char pad00[0x34];
    Pos_s00bf_b020 pos34;                         // +0x34
    char pad38[0x120 - 0x38];
    Pos_s00bf_b020 pos120;                        // +0x120
    char pad124[0xb1c - 0x124];
    unsigned mId;                      // +0xb1c
    int mState;                        // +0xb20

    Inter_s00bf_b020* GetInter();                         // 0x00ca71d0
    bool CanTargetCity(Entity_s00bf_b020* c);             // 0x00c9fe40
    void Order(Entity_s00bf_b020* target, int type, int z); // 0x00cac000
    bool CanTarget(Entity_s00bf_b020* t);                 // 0x00ca8340
    void MoveTo(Vec3 p, int z);                // 0x00cac0e0
    float FUN_00bfdea0();                      // 0x00bfdea0 (ret 0)
    int GetVehicleSpecialty();                 // 0x00bd81d0
    bool FUN_00bd9260(Entity_s00bf_b020* other);          // 0x00bd9260 (ret 4)
    int FUN_00bd8210();                        // 0x00bd8210 (ret 0)
    Vec3* FUN_00fa0e00();                      // 0x00fa0e00 (ret 0; position)
    bool FUN_00bdb930(int a, int b);           // 0x00bdb930 (ret 8)
    void GetPoint(Vec3* out, unsigned id);     // 0x00bdca30 (ret 8)
    Entity_s00bf_b020* FUN_00bddda0(int specialty, int index, Key key, bool spaceStage); // 0x00bddda0 (ret 0x18)
    int FUN_00bd9b60();                        // 0x00bd9b60 (ret 0)
    void SetJustEyeCandy(bool eyeCandy);       // 0x00c9ecb0 (ret 4)
};
struct Rel { float FUN_00ceee30(Entity_s00bf_b020* a, struct Game* g); };   // 0x00ceee30 (ret 8), object 0x169c254
extern Rel g_Rel;                      // 0x0169c254
struct Timer_s00bf_b020 {
    uint32_t pad[8];
    unsigned long long GetElapsedTime();   // 0x00bc3190
    void Restart();                        // 0x00bc3130
};
struct Reg {
    uint32_t pad[12];
    Key* FUN_00bf9700(int type);           // 0x00bf9700 (ret 4)
};
struct PlanetMdl_s00bf_b020 {
    float DistanceBetweenPoints(Vec3* a, Vec3* b);   // 0x00b81470 (ret 8)
    float GetRadius();                               // 0x00b7e4d0
    int GetContinent(Vec3* p);                       // 0x00b88590 (ret 4)
};
extern Rand sMathRandom_s00bf_b020;               // 0x01601760
extern Vec3 g_ZeroVec;                 // 0x0168c514
struct Game;
struct PairVec_s00bf_b020 { Game** begin; Game** end; };
struct NounMgr_s00bf_b020 { PairVec_s00bf_b020* GetEmpires(); };         // 0x00b25ca0
NounMgr_s00bf_b020* NounManager_s00bf_b020();                            // 0x00b3d300
PlanetMdl_s00bf_b020* PlanetModel_s00bf_b020();                          // 0x00b3d350
int __cdecl FUN_00c9e6d0(int specialty, int index);    // 0x00c9e6d0: vehicle type of (specialty, index)
struct Game {
    char pad00[0x6c];
    Reg mReg;                          // +0x6c
    Entity_s00bf_b020** mCitiesBegin;             // +0x9c
    Entity_s00bf_b020** mCitiesEnd;               // +0xa0
    uint32_t pada4[3];
    Entity_s00bf_b020** mUfoBegin;                // +0xb0
    Entity_s00bf_b020** mUfoEnd;                  // +0xb4
    uint32_t padb8[52];
    Timer_s00bf_b020 mTimer;                      // +0x188
    uint32_t pad1a8[175];
    Entity_s00bf_b020* mpTargetCity;              // +0x464
    uint32_t pad468[18];
    float mBudget;                     // +0x4b0

    void Tick();
    float GetMoney();                  // 0x00bef6d0 (ret 0)
    int SpaceTelemetry_Add(int flag);  // 0x00bf2100 (ret 4)
    float FUN_00bf2170(int specialty, int index);   // 0x00bf2170 (ret 8): vehicle cost
    __forceinline void Buy(Entity_s00bf_b020* city, int index, float cost);
};
__forceinline void Game::Buy(Entity_s00bf_b020* city, int index, float cost)
{
    int type = FUN_00c9e6d0(2, index);
    Key* pKey = mReg.FUN_00bf9700(type);
    bool inSpace = GetCurrentGameMode() == 0x1654c05;
    city->FUN_00bddda0(2, index, *pKey, inSpace);
    mBudget = mBudget - cost;
}
namespace eastl
{
template <typename T>
inline const T& min(const T& a, const T& b) { return b < a ? b : a; }
}
struct CivHelper
{
    uint32_t m_pad[7];                       // +0x00 (size 0x1c)
    void BuildConstraints(int key);          // 0x00bf9300
    Key* GetOrCreatePosition(int key);       // 0x00bf9700 (ret 4)
};
struct PlanetTool
{
    int GetToolMode();                       // 0x00c70e00
};
PlanetTool* GetActivePlanet();               // 0x01021260
struct Civ_s00bf_b020
{
    char pad00[0x6c];
    CivHelper mHelper;                       // +0x6c
    char pad88[0x9c - 0x88];
    Entity_s00bf_b020** mCitiesBegin;                   // +0x9c
    Entity_s00bf_b020** mCitiesEnd;                     // +0xa0
    char pada4[0xb0 - 0xa4];
    Entity_s00bf_b020** mVehiclesBegin;                 // +0xb0
    Entity_s00bf_b020** mVehiclesEnd;                   // +0xb4

    int FUN_00bf2f00(int mode);              // 0x00bf2f00 (ret 4)
    void SubTick1();                         // 0x00bfb930
};
// ---- items of slice s00bfb020 end

// ---- items of slice s00bfbbf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int  Lookup_c9e6d0(int specialty, int zero);   // cdecl
extern int gStrategyTable[];                   // 0x01469284
struct Color4 { float r, g, b, a; };
struct Triple {
    uint32_t a, b, c;
    Triple() { a = 0; b = 0; c = 0; }
};
struct Pos_s00bf_bbf0 {
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
    virtual Vec3* GetPosition();       // slot 11 (+0x2c): lea eax,[ecx+4]; ret
};
struct CityMusic_s00bf_bbf0 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
    virtual void Start(Vec3* pos);     // slot 9 (+0x24)
    virtual void Stop();               // slot 10
    virtual void Pause(bool pause);    // slot 11 (+0x2c)
    virtual void SetPosition(Vec3*);   // slot 12
    virtual int  IsPlaying();          // slot 13 (+0x34)
};
struct City {
    virtual void AddRef();             // slot 0
    virtual void Release();            // slot 1 (+4)
    char pad04[0x120 - 4];
    Pos_s00bf_bbf0 pos120;                        // +0x120 (cSpatialObject base)

    int  GetVehicleSpecialty();        // 0xbd81d0
    void SetupVehicle(int specialty, int zero, Triple t, bool flag);   // 0xbddda0, ret 0x18
    void Tick1();                      // 0xbe5740
    void Tick2();                      // 0xbde4a0
    bool IsMusicActive();              // 0xbd9fa0
};
struct CultureSet {
    char pad[0x1c];
    Triple* LookupColor(int specialty);   // 0xbf9700, ret 4
};
struct Civ_s00bf_bbf0;
struct GameData {
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
    virtual int GetPoliticalID();      // slot 19 (+0x4c)
    void AddRelated(int id);           // 0xbdf9e0, ret 4
};
struct Civ_s00bf_bbf0 {
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
    virtual int GetPoliticalID();      // slot 19 (+0x4c)
    char pad04[0x40 - 4];
    int  mId40;                        // +0x40
    char pad44[0x6c - 0x44];
    CultureSet mCultureSet;            // +0x6c
    char pad88[0x8a - 0x88];
    bool mIsNeutral;                   // +0x8a
    char pad8b;
    bool mCommNotifiedWarning;         // +0x8c
    bool mHasDeveloped;                // +0x8d
    char pad8e[0x9c - 0x8e];
    City** mCitiesBegin;               // +0x9c
    City** mCitiesEnd;                 // +0xa0
    char pada4[0xb0 - 0xa4];
    void** mVehiclesBegin;             // +0xb0
    void** mVehiclesEnd;               // +0xb4
    char padb8[0xc4 - 0xb8];
    float mColorR, mColorG, mColorB;   // +0xc4
    char padd0[0x274 - 0xd0];
    CityMusic_s00bf_bbf0* mCityMusic;             // +0x274
    char pad278[0x2a0 - 0x278];
    int  mCommEventId;                 // +0x2a0
    char pad2a4[0x450 - 0x2a4];
    int  mLastRelation;                // +0x450
    City* mMusicCity;                  // +0x454
    char pad458[0x460 - 0x458];
    City* mAttackCity;                 // +0x460

    void SubTick1();                   // 0xbfb930
    void SubTick2();                   // 0xbf1070
    void SubTick3();                   // 0xbf71d0
    void SubTick4();                   // 0xbf8440
    float GetMoney();                  // 0xbef6d0
    float GetFloat6fa0(int a);         // 0xbf6fa0, ret 4
    void Step7230();                   // 0xbf7230
    void ChooseUFOAndBuyVehicle();     // 0xbf9820
    void Step();                       // 0xbf9e70
    void Step_a660(int a);             // 0xbfa660, ret 4
    void Step8710();                   // 0xbf8710
    void UpdateCivAI();                // 0xbfb020
    void Step5cb0();                   // 0xbf5cb0
    void Step7390();                   // 0xbf7390
    void Step1170();                   // 0xbf1170
    void Step08b0();                   // 0xbf08b0
    void Step0710(int a, Civ_s00bf_bbf0* c, int b);   // 0xbf0710, ret 0xc
    void Step07c0();                   // 0xbf07c0
    void Step74a0();                   // 0xbf74a0
    void Step1270();                   // 0xbf1270
    void Step14b0();                   // 0xbf14b0
    void Step3180();                   // 0xbf3180
    int  GetSize0f10();                // 0xbf0f10
    float GetSize2ae0();               // 0xbf2ae0
    int  GetLevel7150();               // 0xbf7150
    char* GetBlock();                  // 0xbef950 (callers add 0x504)

    void Update();                     // @ 0x00bfbbf0
};
struct PairVec_s00bf_bbf0 { Civ_s00bf_bbf0** begin; Civ_s00bf_bbf0** end; };
struct GdVec { GameData** begin; GameData** end; };
struct VecHolder_s00bf_bbf0 { int pad; GdVec vec; };
struct NounMgr_s00bf_bbf0 {
    PairVec_s00bf_bbf0* GetCivilizations();       // 0xb25ca0
    Civ_s00bf_bbf0* GetPlayerCivilization();      // 0xb25fb0
    int GetPlayerEmpireOrMinus1();     // 0xb1f9d0
    VecHolder_s00bf_bbf0* GetGameDataVector(void* a, void* b, void* c, void* d, unsigned int typeTag);  // 0xb21340, ret 0x14
    Sphere* GetCurrentTerrainSphere(); // 0xf67d90
};
struct RelMgr_s00bf_bbf0 {
    int GetRelation(int a, int b, int c);   // 0xd00a70, ret 0xc
};
struct StrategyMgr {
    int Apply(Civ_s00bf_bbf0* civ, int tableEntry, unsigned key, Vec3* pos, Color4* color, int zero, int pid);   // 0xcf90a0, ret 0x1c
};
extern unsigned GetCurrentGameMode_s00bf_bbf0();          // 0xb5b800
extern NounMgr_s00bf_bbf0* NounManager_s00bf_bbf0();                 // 0xb3d300
extern RelMgr_s00bf_bbf0* RelationshipManager_s00bf_bbf0();          // 0xb3d2c0
extern StrategyMgr* GetStrategyMgr();          // 0xcf74c0 (returns a singleton)
extern void Notify_e3c7c0(unsigned key, void* a, void* b, const Triple& zero, int p1, int p2, int p3);   // cdecl
extern void Final_ba5d30(Civ_s00bf_bbf0* civ);            // cdecl
extern Rand sMathRandom_s00bf_bbf0;                       // 0x1601760
// ---- items of slice s00bfbbf0 end

// ---- items of slice s00bfcc80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void cSpatialObject_LocalToWorldTransform(void* self, const void* m); // 0x00C897E0
#pragma pack(push, 1)
#pragma pack(pop)
struct Vector3 { float x, y, z; };                              // 0x0c
struct Matrix3 { float m[9]; };                                 // 0x24 (column-major rows)
struct SpVec3 {                                                 // eastl-style vector of Vector3
    Vector3* begin;                                             // +0x00
    Vector3* end;                                               // +0x04
    Vector3* cap;                                               // +0x08
    void erase(Vector3* first, Vector3* last);                  // 0x0050F740
    void DoInsertValue(Vector3* pos, const Vector3* v);         // 0x004B5AD0
};
struct GameData_s00bf_cc80 {
    void**   vftable;                                           // +0x00
    uint32_t pad04[0x15];                                       // +0x04..+0x58
    SpVec3   mDefs;                                             // +0x58 definition-id vector
    uint32_t pad64[2];                                          // +0x64
    unsigned char mFlag6c;                                      // +0x6c

    void SetDefinitionID();                                     // 0x00BFD800
    float* SetGameDataOwner(float* out, int index);             // 0x00BFD840
    void Cleanup();                                             // 0x00BFD610
};
char   FUN_006a0990(void* a, unsigned key, float* out, void** arr); // 0x006A0990
void   Matrix3_Assign(void* self, const void* src);             // 0x0041CB40
struct RandomLCG_s00bf_cc80 { unsigned RandomUint32Uniform(unsigned n); };  // 0x00A68FB0
extern RandomLCG_s00bf_cc80 gRandomLCG;                                    // 0x01601760
struct RcSlotList {                                         // object at cGameData + an accessor result
    void** vftable;                                         // +0x00
    unsigned char pad04[0x8c];                              // +0x04..+0x90
    void*  mData90;                                         // +0x90
};
struct WorldTransform {                                     // filled by cSpatialObject::LocalToWorldTransform
    unsigned short flags;                                   // +0x00
    unsigned char pad02[0x12];                              // +0x02..+0x14
    Matrix3 m;                                              // +0x14
};
typedef void* (*GetAccessor)(void*);
typedef float (*GetFloat)(void*);
// ---- items of slice s00bfcc80 end

// ---- items of slice s00bfd9f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_1601760[16];                                   // 0x1601760 sMathRandom RNG object
extern float g_168cb6c;                                          // 0x168cb6c
extern float g_168cb70;                                          // 0x168cb70
extern float g_168cb74;                                          // 0x168cb74
extern unsigned char g_168d12c[64];                              // 0x168d12c identity matrix source
extern unsigned char g_168d181;                                  // 0x168d181
extern float g_13ec4d0;                                          // 0x13ec4d0
extern float g_169cc08;                                          // 0x169cc08
extern float g_14007f4;                                          // 0x14007f4
extern unsigned char g_13ebb38;                                  // 0x13ebb38 allocator
extern char g_13f09b4;                                           // 0x13f09b4 "Simulator"
extern char g_169c253;                                           // 0x169c253
extern void* g_1570a60;                                          // 0x1570a60
void* __cdecl Alloc(unsigned size, void* allocator, int a, int b, const char* tag, unsigned n); // 0xf473a0 EAAllocate
void  __cdecl Free(void* p);                                    // 0xf47380 operator delete
void* __cdecl WriteUint32(void* s, void* v, int a, int b);      // 0x93aa70 EA::IO::WriteUint32
void* __cdecl GetFloatProp(unsigned* prop);                     // 0x41ea70
void* __cdecl RandomUint32Uniform(void* rng, int n);            // 0xa68fb0
void* __cdecl FUN_00bfd610();                                    // 0xbfd610
void* __cdecl FUN_00bfd3e0(void*);                               // 0xbfd3e0
void* __cdecl FUN_00bfd490(void*, void*, void*);                 // 0xbfd490
void* __cdecl FUN_00bfd430(void*, void*, void*);                 // 0xbfd430
void* __cdecl FUN_00bfc6e0(void*, void*, void*);                 // 0xbfc6e0
void* __cdecl Matrix3_Assign(void* dst, void* src);              // 0x41cb40 Matrix3::Assign
struct C_THISCALL {
  void* __thiscall FUN_00bfc380(void* id);                       // 0xbfc380 (this = sub-object)
  void* __thiscall FUN_00bfc720();                               // 0xbfc720 (this = sub-object)
  void* __thiscall FUN_00c884f0(void* id);                       // 0xc884f0 (this = sub-object)
  void* __thiscall FUN_00b18460(void* id);                       // 0xb18460
  void* __thiscall FUN_00c3f2d0(void* a);                        // 0xc3f2d0
  void* __thiscall FUN_00c3f160(void* a);                        // 0xc3f160
  void  __thiscall FUN_00c897e0();                               // 0xc897e0 LocalToWorldTransform
  void* __thiscall FUN_00c88670(void* a);                        // 0xc88670 cCommunity::func54h
  void* __thiscall FUN_00b7e3e0(void* a);                        // 0xb7e3e0
  void* __thiscall FUN_00b81630(void* a, void* b);               // 0xb81630
  int   __thiscall FUN_00b88590();                               // 0xb88590 cPlanetModel::GetContinent
  int   __thiscall FUN_00b18590(void* stream);                   // 0xb18590 cGameData::Write
  int   __thiscall FUN_00b183f0(void* arg);                      // 0xb183f0 vtableSlot40
  void* __thiscall FUN_00b25f40(int id);                         // 0xb25f40 (this call takes one stack arg, ret 4)
  void* __thiscall FUN_00b20c60(int id);                         // 0xb20c60 CreateNoun
  void  __thiscall FUN_00b225d0(void* noun);                     // 0xb225d0 RemoveNoun
  int   __thiscall FUN_00c88a90(void* stream);                   // 0xc88a90 cSpatialObject::Write
  bool __thiscall FUN_00c8a550(void* arg);              // 0xc8a550 cSpatialObject::LoadModel
  void  __thiscall FUN_00c899a0(void* a);                        // 0xc899a0 cSpatialObject::func7Ch
  void  __thiscall FUN_00bc3130();                               // 0xbc3130 cSPTimer::Restart
  long long __thiscall FUN_00bc3190();                           // 0xbc3190 cSPTimer::GetElapsedTime (edx:eax)
  void  __thiscall FUN_00b63890();                               // 0xb63890 cGonzagoTimer ctor
  void  __thiscall FUN_00b638b0();                               // 0xb638b0 cGonzagoTimer dtor
  void  __thiscall FUN_00c8b2e0();                               // 0xc8b2e0
  void  __thiscall FUN_00ceefd0(float v, float* out1, float* out2); // 0xceefd0 (this = RNG global)
  void  __thiscall FUN_00b83c40(void* pos, float f, int a, int b);  // 0xb83c40
  void* __thiscall FUN_00cVarListSerializer_Construct(void* self, void* g, unsigned n); // 0x692f90 (this = &serializer)
  int   __thiscall FUN_cVarListSerializer_Serialize(void* stream); // 0x692900 (this = &serializer)
};
void* __cdecl FUN_0059aed0(void*, void*, void*);                 // 0x59aed0 (free: obj, key, out)
struct CStub899a0 {
  void __thiscall FUN_00c899a0(void* a, void* b);                // 0xc899a0
};
struct CStub230 {
  void __thiscall FUN_00bfe230(char* a, char* b);                // 0xbfe230
};
struct SeqIter {
  RefObj** cur;                    // +0x00
  RefObj** begin;                  // +0x04
  RefObj** end;                    // +0x08
  RefObj*** bucket;                // +0x0c
};
struct cCommunity_s00bf_d9f0 {
  char pad000[0x2c];
  RefObj* m2c;                     // +0x2c
  int m30;                         // +0x30
  void* m34;                       // +0x34 cSpatialObject base
  char pad038[0x58 - 0x38];
  int m58;                         // +0x58 noun vector begin
  int m5c;                         // +0x5c noun vector end (0xc-byte stride)
  char pad060[0x6c - 0x60];
  char m6c;                        // +0x6c
  char pad06d[0x9c - 0x6d];
  void* m9c;                       // +0x9c
  char pad0a0[0xd0 - 0xa0];
  void* mD0;                       // +0xd0
  char pad0d4[0x108 - 0xd4];
  char m108[0x9c];                 // +0x108 sub-object (own vector at +0x00)
  void* m1a4;                      // +0x1a4
  char pad1a8[0x1d0 - 0x1a8];
  float m1d0;                      // +0x1d0 phase accumulator
  float m1d4;                      // +0x1d4 phase limit
  void* m1d8;                      // +0x1d8
  void* m1dc;                      // +0x1dc
  RefObj* m1e0;                    // +0x1e0
  unsigned char m1e4;              // +0x1e4 scenery-init guard
  char pad1e5[0x1ec - 0x1e5];
  int m1ec;                        // +0x1ec timer state byte
  char m1f0[0x20];                 // +0x1f0 cSPTimer
  int m210;                        // +0x210
  int m214;                        // +0x214
  char pad218[0x230 - 0x218];
  char m230[0x28];                 // +0x230 timer record table (begin/end/cap)
  char pad258[0x288 - 0x258];
  void* m288;                      // +0x288 shared value object

  // ---- members, retail VAs in the comment above each definition ----
  void  Push(void* lo, void* hi);                       // 0x00bfdc50
  void  EnsureTimer(void* key);                         // 0x00bfddc0
  float ReadPhase(unsigned char save);                  // 0x00bfde50
  float GetPhaseRatio();                                // 0x00bfdea0
  void* ResolveID(int id);                              // 0x00bfdeb0
  float GetScaledFloat();                               // 0x00bfdf00
  void  AdvancePhase(float dt);                         // 0x00bfdf20
  void  SetID(int v);                                   // 0x00bfdf60
  void* GetNoun();                                      // 0x00bfdf80
  void  SetState(int v);                                // 0x00bfdfb0
  float GetProgress();                                  // 0x00bfdff0
  int   HasNoun();                                      // 0x00bfe0c0
  unsigned char Write(void* stream);                    // 0x00bfe0f0
  void* FillPair(char* obj);                            // 0x00bfe260
  void  Activate(int a, RefObj* b);                     // 0x00bfe450
  void  Deactivate();                                   // 0x00bfe4d0
  void  SetupScenery();                                 // 0x00bfe530
  unsigned char Read(void* arg);                        // 0x00bfe5d0
  bool  LoadModel(void* arg);                           // 0x00bfe690
  void  ReleaseTable();                                 // 0x00bfe6c0
  void  SpawnAt(float* pos);                            // 0x00bfe900
  void  Teardown();                                     // 0x00bfea10
  void  InitScenery();                                  // 0x00bfeb00
  void* Front();                                        // 0x00bfec10
  void  GetNounID(float* out);                          // 0x00bfd9f0
};
// ---- items of slice s00bfd9f0 end

// ---- items of slice s00bfec30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_1469b08;      // cGameData vtable
extern char vtbl_1469af4;      // DefaultRefCounted vtable
extern char vtbl_1469a30;      // cSpatialObject vtable
extern char vtbl_14699c8;      // vtbl_Simulator::cCommodityNode
struct V4 { int a, b, c, d; };
V4*   __cdecl FUN_00bfe7c0(V4* ret, V4, V4, int* key);
void  __cdecl FUN_00ca09f0(int);
void  __fastcall FUN_00bfcd00(void* self);
void  __fastcall FUN_00bfeb00(void* self);
void  __fastcall FUN_00bfe530(void* self);
void* __cdecl   SP_GonzagoModelWorld();
void  __fastcall FUN_00c8a420(void* self);
void  __fastcall FUN_00b184c0(void* self);
void  __fastcall FUN_00abf900(void* self);
struct TG   { void ctor(); };
struct TS   { void ctor(); };
struct TC   { void ctor(); };
struct TMR  { void Restart(); };
struct TMS  { void Start(); };
struct TDT  { void dtor(); };
struct Iter {
    int*  cur;
    int*  begin;
    int*  end;
    int** arr;
};
struct Container {
    void* m00;
    void* m04;
    Iter  begin;
    Iter  end;
    V4    FUN_00c95660(Iter iter);
    void  FUN_00c92b70();
    void  FUN_00c92bd0(RefObj** p);
};
struct CommodityNode {
    void* vt0;                    // +0x000
    void* vt1;                    // +0x004
    char  pad0[0x34 - 8];
    void* vt2;                    // +0x034 (cSpatialObject)
    char  pad2[0x108 - 0x38];
    void* vt3;                    // +0x108 (cCombatant)
    char  pad3[0x1d0 - 0x10c];
    float m1d0;                   // +0x1d0 resource points
    float m1d4;                   // +0x1d4 max resource points
    void* m1d8;                   // +0x1d8
    void* m1dc;                   // +0x1dc
    void* m1e0;                   // +0x1e0
    u8    m1e4, m1e5, m1e6, m1e7, m1e8, m1e9;
    char  pad4[2];
    int   m1ec;                   // +0x1ec mine state
    char  timer1[0x20];           // +0x1f0 cSPTimer
    int   m210;                   // +0x210
    int   m214, m218, m21c, m220;
    float m224, m228, m22c;
    Container m230;               // +0x230
    char  pad5[8];
    int   m260, m264;             // +0x260
    char  timer2[0x20];           // +0x268 cGonzagoTimer
    void* m288;                   // +0x288

    __declspec(noinline) void FUN_00bff2d0(int a, int b);
    void FUN_00bff140(RefObj* obj);
    void FUN_00bff290(int key);
    void FUN_00bff6e0(int a);
    void FUN_00bff750();
};
// ---- items of slice s00bfec30 end

// @ 0x00bf00a0
u8 CStub::FUN_00bf00a0(int continent, int specialty)
{
    int n = cityCount();
    for (int i = 0; i < n; ++i) {
        CityObj* city = (CityObj*)*(int*)(m9c + i * 4);
        if (((CityStub*)city)->FUN_00bd8210() == continent) {
            if (specialty == -1) return 1;
            if (((CityStub*)city)->FUN_00bd81d0() == specialty) return 1;
        }
    }
    return 0;
}

// @ 0x00bf0110
u8 CStub::FUN_00bf0110(void* a, int city)
{
    return FUN_00bf00a0(((CityStub*)a)->FUN_00bd8210(), city);
}

// @ 0x00bf0130
u8 CStub::FUN_00bf0130(CStub* other)
{
    int nA = cityCount();
    for (int i = 0; i < nA; ++i) {
        int contA = ((CityStub*)*(int*)(m9c + i * 4))->FUN_00bd8210();
        int nB = other->cityCount();
        for (int j = 0; j < nB; ++j) {
            if (((CityStub*)*(int*)(other->m9c + j * 4))->FUN_00bd8210() == contA)
                return 1;
        }
    }
    return 0;
}

// @ 0x00bf01f0
int CStub::FUN_00bf01f0(int specialty, u8 flag)
{
    int count = 0;
    int n = cityCount();
    for (int i = 0; i < n; ++i) {
        CityObj* city = (CityObj*)*(int*)(m9c + i * 4);
        if (city == 0) continue;
        if (((CityStub*)city)->FUN_00bd81d0() != specialty) continue;
        if (flag != 0 && *(u8*)((char*)city + 0x519) != 0) continue;
        ++count;
    }
    return count;
}

// @ 0x00bf0260
int CStub::FUN_00bf0260(int arg)
{
    int count = 0;
    int n = cityCount();
    for (int i = 0; i < n; ++i) {
        CityObj* city = (CityObj*)*(int*)(m9c + i * 4);
        if (city == 0) continue;
        if (((CityStub*)city)->FUN_00bdb880(arg)) ++count;
    }
    return count;
}

// @ 0x00bf02b0
void CStub::FUN_00bf02b0(void* arg, int b, int c, int d)
{
    (void)b; (void)c; (void)d;
    NounMgrStub* nm = (NounMgrStub*)SP_NounManager();
    void* src = nm->FUN_00b25f40((int)arg);
    nm = (NounMgrStub*)SP_NounManager();
    void* player = nm->FUN_00b25fb0();

    if ((**(u8(__thiscall**)(CStub*))(*(void***)this + 0x2c / 4))(this)) return;
    if (src == 0) return;
    if ((**(u8(__thiscall**)(void*))(*(void***)src + 0x2c / 4))(src)) return;

    if (this == player) {
        *(u8*)((char*)src + 0x398) = 1;
        ((TimerStub*)((char*)src + 0x3a0))->FUN_00bc3130();
        return;
    }
    if (src == player)
        ((NoopStub*)this)->FUN_00bef850();
}

// @ 0x00bf0330
void CStub::FUN_00bf0330(void* city)
{
    if (!(**(u8(__thiscall**)(int))(*(int*)((char*)city + 0x120) + 0x58))((int)city + 0x120)) return;
    if (m434 <= 4) return;
    if (m438 != 0) return;

    void* cm = SP_CommManager();
    m434 = 0;
    m438 = city;

    void* edi = ((CityStub*)city)->FUN_00bd92d0();
    if (edi == 0) edi = (void*)(**(int(__thiscall**)(CStub*, int))(*(void***)this + 0xc / 4))(this, 0x17f243b);
    else {
        void* r = (**(void*(__thiscall**)(void*, int))(*(void***)edi + 0xc / 4))(edi, 0x17f243b);
        edi = r;
        if (r == 0) edi = (void*)(**(int(__thiscall**)(CStub*, int))(*(void***)this + 0xc / 4))(this, 0x17f243b);
    }

    void* planet = SP_ActivePlanet();
    void* ctx = ((StarRefStub*)((char*)planet + 0x13c))->FUN_00ce6950(0xdbf385bf, 0x832b3aa4, 0);
    ((CommMgrStub*)cm)->FUN_00aeb760((int)edi, city, ctx, 0xdbf385bf, 0x832b3aa4, 0);
}

// @ 0x00bf03e0
void CStub::FUN_00bf03e0(CivObject* city, float f)
{
    if (m440 != 0) return;
    if ((**(u8(__thiscall**)(void*))(*(int*)((char*)city + 0x120) + 0x58))(city)) {
        m440 = city;
        return;
    }

    void* cm = SP_CommManager();
    void* mgr = g_169d3c8;
    ((TuningStub*)mgr)->FUN_00cfe7a0(0, 0x7d00);
    ((TuningStub*)mgr)->FUN_00cfe7a0(1, 0x5dc0);
    ((TuningStub*)mgr)->FUN_00cfe7a0(2, 0x3e80);
    ((TuningStub*)mgr)->FUN_00cfe7a0(3, 0x1f40);
    ((TuningStub*)mgr)->FUN_00cfe7a0(4, 0x0fa0);
    m444 = 0;
    m448 = f;

    void* planet = SP_ActivePlanet();
    void* ctx = ((StarRefStub*)((char*)planet + 0x13c))->FUN_00ce6950(0xdbf385bf, 0xe05d0481, 0);
    int civ = ((CityStub*)city)->FUN_00bd9bf0();
    ((CommMgrStub*)cm)->FUN_00aeb760(civ, city, ctx, 0xdbf385bf, 0xe05d0481, 0);
    m440 = city;
}

// @ 0x00bf04c0
void CStub::FUN_00bf04c0(u8 enable)
{
    void* target = m440;
    if (target == 0) return;

    if (enable != 0) {
        float v = (float)m444;
        int id = (**(int(__thiscall**)(CStub*, float))(*(void***)this + 0x4c / 4))(this, v);
        FUN_00be9850((int)target, id);
        if (m89 != 0) {
            float pos[4];
            pos[0] = mc4; pos[1] = mc8; pos[2] = mcc; pos[3] = g_1485720;
            void* p = (**(void*(__thiscall**)(int, float*, int, int))(*(int*)((char*)m440 + 0x120) + 0x2c))((int)m440 + 0x120, pos, 0, 0);
            void* strat = FUN_00cf74c0((int)m440, 0x664d26ce, 0xaa9a8ed7, p);
            ((CommEventMgrStub*)strat)->FUN_00cf9040((int)m440, 0x664d26ce, 0xaa9a8ed7, p);
        }
    } else {
        *(int*)((char*)target + 0x75c) = -1;
        *(float*)((char*)target + 0x758) = 0.0f;
        if (m89 != 0) {
            float pos[4];
            pos[0] = mc4; pos[1] = mc8; pos[2] = mcc; pos[3] = g_1485720;
            void* p = (**(void*(__thiscall**)(int, float*, int, int))(*(int*)((char*)m440 + 0x120) + 0x2c))((int)m440 + 0x120, pos, 0, 0);
            void* strat = FUN_00cf74c0((int)m440, 0x1e920e12, 0xaa9a8ed7, p);
            ((CommEventMgrStub*)strat)->FUN_00cf9040((int)m440, 0x1e920e12, 0xaa9a8ed7, p);
        }
    }

    m43c = -1;
    m440 = 0;
    m444 = 0;
    m448 = 0.0f;
}

// @ 0x00bf0640
float CStub::FUN_00bf0640(CivObject* object)
{
    int id = (**(int(__thiscall**)(CivObject*))(*(void***)object + 0x4c / 4))(object);
    if (id == -1) return 0.0f;

    int mine = (**(int(__thiscall**)(CStub*, int))(*(void***)this + 0x4c / 4))(this, 1);
    int theirs = (**(int(__thiscall**)(CivObject*, int))(*(void***)object + 0x4c / 4))(object, mine);
    void* rel = SP_RelationshipManager();
    float v = ((RelMgrStub*)rel)->FUN_00d00a10(theirs, mine, 1);
    float w = v * 100.0f + g_146935c;
    float base;
    if (w > 0.0f) {
        base = w;
    } else {
        base = 0.0f;
    }
    float t = ((PhaseRatioStub*)(size_t)object)->FUN_00bfdea0();
    return (t + g_1485720) * g_1471064 * base;
}

// @ 0x00bf06d0
float CStub::FUN_00bf06d0(int arg)
{
    int n = (ma0 - m9c) >> 2;
    float weight = (float)(n * 600 + 0x578);
    float t = ((PhaseRatioStub*)(size_t)arg)->FUN_00bfdea0();
    return (t + g_1485720) * g_1471064 * weight;
}

// @ 0x00bf0710
void CStub::FUN_00bf0710(int index, RefObj* a, RefObj* b)
{
    void* cm = SP_CommManager();
    if (((CommMgrStub*)cm)->FUN_00ae9f10(this)) return;
    if (m2a0 != -1 && g_1570840[m2a0] > g_1570840[index]) return;

    m2a0 = index;
    if (a != m2a4) {
        if (a) a->AddRef();
        RefObj* old = m2a4;
        m2a4 = a;
        if (old) old->Release();
    }
    if (b != m2a8) {
        if (b) b->AddRef();
        RefObj* old = m2a8;
        m2a8 = b;
        if (old) old->Release();
    }
}

// @ 0x00bf07c0
void CStub::FUN_00bf07c0()
{
    int none = -1;
    m2a0 = none;
    _ReadWriteBarrier();
    RefObj* a = m2a4;
    m2a4 = 0;
    if (a) a->Release();
    RefObj* b = m2a8;
    m2a8 = 0;
    if (b) b->Release();
}

// @ 0x00bf0810
void CStub::FUN_00bf0810(void* a, ...)
{
    void* cm = SP_CommManager();
    if (((CommMgrStub*)cm)->FUN_00ae9390()) return;

    int index = m2a0;
    RefObj* pa = m2a4;
    RefObj* pb = m2a8;
    int what = -1;

    if (index == 0) {
        what = 0x822e8de4;
    } else if (index == 1) {
        what = 0xa1566b04;
    } else if (index == 2) {
        what = 0x2ab3e3ad;
        m3e8 = 0;
        timerReset(m3f0);
    } else {
        pa = (RefObj*)this;
        pb = 0;
    }

    void* planet = SP_ActivePlanet();
    void* ctx = ((StarRefStub*)((char*)planet + 0x13c))->FUN_00ce6950(0xdbf385bf, what, 0);
    ((CommMgrStub*)cm)->FUN_00aeb760((int)pa, pb, ctx, 0xdbf385bf, what, 0);
}

// @ 0x00bf08b0
void CStub::FUN_00bf08b0()
{
    long long t;

    t = ((TimerStub*)m2b0)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        RefObj* vm2ac = m2ac; if (vm2ac) { m2ac = 0; vm2ac->Release(); }
        ((TimerStub*)m2b0)->FUN_00bc3170();
    }

    t = ((TimerStub*)m2d8)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        RefObj* vm2d0 = m2d0; if (vm2d0) { m2d0 = 0; vm2d0->Release(); }
        ((TimerStub*)m2d8)->FUN_00bc3170();
    }

    t = ((TimerStub*)m300)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        RefObj* vm2f8 = m2f8; if (vm2f8) { m2f8 = 0; vm2f8->Release(); }
        ((TimerStub*)m300)->FUN_00bc3170();
    }

    t = ((TimerStub*)m328)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m320 = 0;
        ((TimerStub*)m328)->FUN_00bc3170();
    }

    t = ((TimerStub*)m350)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m348 = 0;
        ((TimerStub*)m350)->FUN_00bc3170();
    }

    t = ((TimerStub*)m378)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m370 = 0;
        ((TimerStub*)m378)->FUN_00bc3170();
    }

    t = ((TimerStub*)m3a0)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m398 = 0;
        ((TimerStub*)m3a0)->FUN_00bc3170();
    }

    t = ((TimerStub*)m3c8)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m3c0 = 0;
        ((TimerStub*)m3c8)->FUN_00bc3170();
    }

    if (m3e8 == 0 || m2a0 == 2) {
        t = ((TimerStub*)m3f0)->FUN_00bc3190();
        if ((unsigned)(t >> 32) == 0 && (unsigned)t <= 0x927c0)
            return;
    }
    m3e8 = 0;
    ((TimerStub*)m3f0)->FUN_00bc3170();
}

// @ 0x00bf0a60
void CStub::FUN_00bf0a60(RefObj* p)
{
    if (m2ac == p) {
        RefObj* v = m2ac;
        if (v) { m2ac = 0; v->Release(); }
        ((TimerStub*)m2b0)->FUN_00bc3170();
    }
    if (m2d0 == p) {
        RefObj* v = m2d0;
        if (v) { m2d0 = 0; v->Release(); }
        ((TimerStub*)m2d8)->FUN_00bc3170();
    }
    if (m2f8 == p) {
        RefObj* v = m2f8;
        if (v) { m2f8 = 0; v->Release(); }
        ((TimerStub*)m300)->FUN_00bc3170();
    }
}

// @ 0x00bf0b00
void CStub::FUN_00bf0b00(RefObj* p)
{
    NounMgrStub* nm = (NounMgrStub*)SP_NounManager();
    int* list = (int*)nm->FUN_00b25ca0();
    int* it = (int*)*list;
    int* end = (int*)list[1];
    for (; it != end; ++it)
        ((CStub*)*it)->FUN_00bf0a60(p);

    RefObj* old = m2ac;
    if (p != old) {
        if (p) p->AddRef();
        m2ac = p;
        if (old) old->Release();
    }
    ((TimerStub*)m2b0)->FUN_00bc3130();
}

// @ 0x00bf0b70
void CStub::FUN_00bf0b70(RefObj* p)
{
    NounMgrStub* nm = (NounMgrStub*)SP_NounManager();
    int* list = (int*)nm->FUN_00b25ca0();
    int* it = (int*)*list;
    int* end = (int*)list[1];
    for (; it != end; ++it)
        ((CStub*)*it)->FUN_00bf0a60(p);

    RefObj* old = m2d0;
    if (p != old) {
        if (p) p->AddRef();
        m2d0 = p;
        if (old) old->Release();
    }
    ((TimerStub*)m2d8)->FUN_00bc3130();
}

// @ 0x00bf0be0
void cCivilization::FUN_00bf0be0(void* noun)
{
    NounList* list = NounManager()->GetCivList();
    cCivilization** it = list->begin;
    cCivilization** end = list->end;
    for (; it != end; ++it)
        (*it)->FUN_00bf0a60(noun);

    void* old = mp2f8;
    if (noun != old) {
        if (noun) ((RCObject*)noun)->AddRef();
        mp2f8 = noun;
        if (old) ((RCObject*)old)->Release();
    }
    mTimer300.Restart();
}

// @ 0x00bf0c60
int cCivilization::FUN_00bf0c60(int spec, int continent, int flag, int zero)
{
    cNounEntity** end = mVehiclesEnd;
    cNounEntity** it = mVehiclesBegin;
    int count = 0;
    for (; it != end; ++it) {
        cNounEntity* v = *it;
        if (v->mKindB20 != spec) continue;
        if (continent != -1 && PlanetModel()->GetContinent(GetPos(&v->mSpatial34)) != continent) continue;
        if (flag != -1 && v->mFieldB1C != flag) continue;
        if (zero && Slot50(&v->mSpatial34) != 1) continue;
        ++count;
    }
    return count;
}

// @ 0x00bf0cf0
int cCivilization::FUN_00bf0cf0(int continent, int flag, int zero)
{
    return FUN_00bf0c60(continent, flag, zero, 1);
}

// @ 0x00bf0d10
int cCivilization::FUN_00bf0d10(cNounEntity* v)
{
    cNounEntity** it = mVehiclesBegin;
    cNounEntity** end = mVehiclesEnd;
    int count = 0;
    while (it != end) {
        int x = Slot08(&v->mSpatial120);
        if ((*it)->FUN_00c9fee0() == x) ++count;
        ++it;
    }
    return count;
}

// @ 0x00bf0db0
bool cCivilization::FUN_00bf0db0(void* c)
{
    int n = (int)(mCitiesEnd - mCitiesBegin);
    for (int i = 0; i < n; ++i)
        if (mCitiesBegin[i]->FUN_00bdb200(c)) return true;
    return false;
}

// @ 0x00bf0e00
int cCivilization::Write(void* stream) const
{
    // bl = SP_WriteGameData(this, stream)  (0x00b18590, thiscall, ret 4)
    int bl = WriteGameData((void*)this, stream);
    // al = serializer embedded at this+0x3c -> Serialize(stream)  (0x00b6e2d0, ret 4)
    int al = ((SubObject3c*)((char*)this + 0x3c))->Serialize(stream);
    int ok = 0;
    if (al && bl) ok = 1;

    Stream* s = (Stream*)stream;
    void* w = s->v20()->v18();
    EA_IO_WriteUint32(w, &mPrimaryColor[0], 1, 0);
    EA_IO_WriteUint32(w, &mPrimaryColor[1], 1, 0);
    EA_IO_WriteUint32(w, &mPrimaryColor[2], 1, 0);

    cVarListSerializer ser((cCivilization*)this, g_civAttributes, 0x1a80d26);
    if (ser.Serialize(stream)) ok = 1;
    return ok;
}

// @ 0x00bf0f10
int cCivilization::FUN_00bf0f10()
{
    int total = 0;
    cNounEntity** end = mCitiesEnd;
    for (cNounEntity** it = mCitiesBegin; it != end; ++it)
        total += (*it)->GetCreatureCount();
    return total;
}

// @ 0x00bf0f40
int cCivilization::FUN_00bf0f40()
{
    int n = (int)mCitiesEnd - (int)mCitiesBegin;
    if (n & 0xfffffffc) {
        cNounEntity* c = *mCitiesBegin;
        if (c != 0) {
            switch (c->GetVehicleSpecialty()) {
            case 0: return 0;
            case 1: return 2;
            case 2: return 1;
            default: return -1;
            }
        }
    }
    return 0;
}

// @ 0x00bf0f90
void cCivilization::UpdateCityMusicPosition()
{
    void* sys = GetSystemAT();
    if (mpCityMusic == 0) return;
    if (mCitiesBegin == mCitiesEnd) return;
    if (sys == 0) return;

    const Vec3* p = (const Vec3*)((VFP)((*(void***)sys)[0x10 / 4]))(sys);
    Vec3 pos;
    pos.x = p->x;
    pos.y = p->y;
    pos.z = p->z;

    AutoRefCountAssignWText((WTextRef*)&mp454, FUN_00befee0(this, &pos, 0));
    Obj454* o = (Obj454*)mp454;
    if (o == 0) return;

    CityMusic* mus = (CityMusic*)mpCityMusic;
    mus->v30((void*)GetPos(&o->mSpatial120));
    if (GetCurrentGameMode() == g_civSuperweaponMode)
        mus->v2c(Slot08(&o->mSpatial120));
}

// @ 0x00bf1070
void cCivilization::FUN_00bf1070()
{
    cCivilization* self = this;
    if (mForceMinDiploCount > 0) --mForceMinDiploCount;

    int pid = GetPoliticalID();
    int player = GetPlayerEmpireOrMinus1();
    if (pid != player)
        RelationshipManager()->CalculateRelationshipAbsolute(pid, player, 0);

    NounList* l1 = NounManager()->GetCivList();
    int civCount = ((int)l1->end - (int)l1->begin) >> 2;
    if (++g_civUpdateCounter < civCount + 1) return;

    g_civUpdateCounter = 0;
    NounList* list = NounManager()->GetCivList();
    cCivilization** it = list->begin;
    cCivilization** end = list->end;
    for (; it != end; ++it) {
        cCivilization* o = *it;
        if (o == self) continue;
        int e = GetPlayerEmpireOrMinus1();
        int opid = o->GetPoliticalID();
        if (opid != e)
            RelationshipManager()->CalculateRelationshipAbsolute(pid, opid, 0);
    }
}

// @ 0x00bf1170
void cCivilization::FUN_00bf1170()
{
    if (((char*)this)[0x8a]) return;
    cCivilization* p = NounManager()->GetPlayerCivilization();
    if (p != 0 && !((char*)p)[0x8d]) return;

    NounList* list = NounManager()->GetCivList();
    int n = (int)(list->end - list->begin) >> 2;
    for (int i = 0; i < n; ++i) {
        cCivilization* o = list->begin[i];
        if (o == this) continue;
        if (((char*)o)[0x89]) continue;
        int m = (int)(o->mCitiesEnd - o->mCitiesBegin) >> 2;
        for (int j = 0; j < m; ++j) {
            cNounEntity* c = o->mCitiesBegin[j];
            int pid = GetPoliticalID();
            if (c->FUN_00bd7fc0(pid))
                c->FUN_00be9850(pid, 0.0f);
        }
    }
}

// @ 0x00bf1270
void cCivilization::FUN_00bf1270()
{
    if (((int)(mCitiesEnd - mCitiesBegin) & 0xfffffffc) <= 4) return;
    cNounEntity* first = *mCitiesBegin;
    if (first == 0) return;
    if (((char*)this)[0x8a]) return;

    cCivilization* p = NounManager()->GetPlayerCivilization();
    if (p == 0 || !((char*)p)[0x8d]) return;

    int player = GetPlayerEmpireOrMinus1();
    if (!RelationshipManager()->FUN_00ae2e20(GetPoliticalID(), player)) return;

    NounList* list = NounManager()->GetCivList();
    int n = (int)(list->end - list->begin) >> 2;
    cCivilization* best = 0;
    int bestScore = 0;
    for (int i = 0; i < n; ++i) {
        cCivilization* o = list->begin[i];
        if (o == this) continue;
        if (((char*)o)[0x8a]) continue;
        if (((char*)o)[0x89]) continue;
        if (((int)(o->mCitiesEnd - o->mCitiesBegin) & 0xfffffffc) <= 4) continue;
        if (!o->FUN_00bf0db0((void*)GetPlayerEmpireOrMinus1())) continue;
        if (!RelationshipManager()->FUN_00ae2e20(o->GetPoliticalID(), GetPoliticalID())) continue;
        int r = sMathRandom.RandomUint32Uniform(100);
        if (o->mNemesisCiv == this) r += 100;
        if (r > bestScore) { bestScore = r; best = o; }
    }
    if (best == 0) return;
    cNounEntity* target = best->mCitiesBegin[0];
    if (target == 0) return;
    if (mTimer208.GetElapsedTime() <= 50000) return;
    if (CommManager()->FUN_00ae9390()) { mTimer208.Restart(); return; }
    unsigned lim = 1;
    int t = FUN_00c75420(NounManager()->GetCurrentTerrainSphere());
    if (t == 0) lim = 12; else if (t == 1) lim = 9; else if (t == 2) lim = 6;
    if (sMathRandom.RandomUint32Uniform(lim) == 0) {
        CommMgr* cm = CommManager();
        LivingUniverse* lu = FUN_01021260();
        int cc = (int)lu->mpCtx->mField184;
        cm->ShowCommEvent((int)first, target, 0xdbf385bf, 0x1aa5bff0, cc, 0);
    }
    mTimer208.Restart();
}

// @ 0x00bf14b0
void cCivilization::FUN_00bf14b0()
{
    if (((int)(mCitiesEnd - mCitiesBegin) & 0xfffffffc) <= 4) return;
    cNounEntity* first = *mCitiesBegin;
    if (first == 0) return;
    if (((char*)this)[0x8a]) return;

    cCivilization* p = NounManager()->GetPlayerCivilization();
    if (p == 0) return;
    if (!((char*)p)[0x8d]) return;
    if (((int)(p->mCitiesEnd - p->mCitiesBegin) & 0xfffffffc) <= 4) return;

    if (RelationshipManager()->FUN_00ae2e20(GetPoliticalID(), GetPlayerEmpireOrMinus1())) return;
    RelationshipManager()->FUN_00d01b80(GetPoliticalID(), GetPlayerEmpireOrMinus1(), (int)0x0526e4f8);

    NounList* list = NounManager()->GetCivList();
    int n = (int)(list->end - list->begin) >> 2;
    cCivilization* best = 0;
    int bestScore = 0;
    int mode = 0;
    for (int i = 0; i < n; ++i) {
        cCivilization* o = list->begin[i];
        if (o == this) continue;
        if (((char*)o)[0x8a]) continue;
        if (((char*)o)[0x89]) continue;
        if (((int)(o->mCitiesEnd - o->mCitiesBegin) & 0xfffffffc) <= 4) continue;
        if (!RelationshipManager()->FUN_00ae2e20(o->GetPoliticalID(), GetPoliticalID())) continue;
        if (!RelationshipManager()->FUN_00ae2e20(o->GetPoliticalID(), GetPlayerEmpireOrMinus1())) continue;
        if (!o->FUN_00bf0130(mode) && !FUN_00bf0130(mode)) continue;
        int r = sMathRandom.RandomUint32Uniform(100);
        if (o->mNemesisCiv == this) r += 100;
        if (r > bestScore) { bestScore = r; best = o; }
    }
    if (best == 0) return;
    cNounEntity* target = best->mCitiesBegin[0];
    if (target == 0) return;
    if (mTimer228.GetElapsedTime() <= 60000) return;
    if (CommManager()->FUN_00ae9390()) { mTimer228.Restart(); return; }
    unsigned lim = 1;
    int t = FUN_00c75420(NounManager()->GetCurrentTerrainSphere());
    if (t == 0) lim = 16; else if (t == 1) lim = 12; else if (t == 2) lim = 8;
    if (sMathRandom.RandomUint32Uniform(lim) == 0) {
        CommMgr* cm = CommManager();
        LivingUniverse* lu = FUN_01021260();
        int cc = (int)lu->mpCtx->mField184;
        cm->ShowCommEvent((int)first, target, 0xdbf385bf, 0x18371572, cc, 0);
    }
    mTimer228.Restart();
}

// @ 0x00bf1790
bool cCivilization::SuperweaponOnCooldown(int w)
{
    SPTimer* t = mSuperweaponCooldown + w;
    if (t->IsRunning()) {
        unsigned __int64 limit = (unsigned __int64)(unsigned)(mpField470[w])->FUN_0104bde0();
        return t->GetElapsedTime() < limit;
    }
    return false;
}

// @ 0x00bf17f0
float cCivilization::GetSuperweaponCooldown(int w)
{
    if (!SuperweaponOnCooldown(w)) return 0.0f;
    float elapsed = (float)(mSuperweaponCooldown + w)->GetElapsedTime();
    float total = (float)mpField470[w]->FUN_0104bde0();
    return elapsed / total;
}

// @ 0x00bf1880
float cCivilization::FUN_00bf1880(float which)
{
    float a = (float)mMilitaryCaptureCount;
    float b = (float)mReligiousCaptureCount;
    float c = (float)mEconomicCaptureCount;
    float m = (b > a) ? b : a;
    if (c > m) m = c;
    if (m == g_civConst1) {
        a = (float)FUN_00bf01f0(0, 0);
        b = (float)FUN_00bf01f0(1, 0);
        c = (float)FUN_00bf01f0(2, 0);
        m = (b > a) ? b : a;
        if (c > m) m = c;
    }
    if (m == g_civConst1) return 0.0f;
    if (which == (float)0x0a35d0f5) return a / m;
    if (which == (float)0x3360727f) return c / m;
    if (which == (float)0x6aeb96a1) return b / m;
    return which;
}

// @ 0x00bf19c0
bool cCivilization::FUN_00bf19c0(cCivilization* civ)
{
    for (cNounEntity** it = mVehiclesBegin; it != mVehiclesEnd; ++it) {
        cNounEntity* v = *it;
        if (v == 0) continue;
        int k = v->mKindB20;
        if (k != 0 && k != 1) continue;

        NounInfo* ni = (NounInfo*)FUN_00ca71d0(v);
        if (ni->mKind == 1) {
            if (ni->mpObject == 0) continue;
            void* c = ((RCObject*)ni->mpObject)->Cast(0x0403df5f);
            if (c == 0) continue;
            if (((cCivilization*)c)->FUN_00bfdf80() == (int)civ) return 0;
            continue;
        }

        NounInfo* n2 = (NounInfo*)FUN_00ca71d0(v);
        int twoOrThree = (n2->mKind == 2 && n2->mpObject != 0);
        if (!twoOrThree) {
            NounInfo* n3 = (NounInfo*)FUN_00ca71d0(v);
            if (n3->mKind != 3) continue;
            if (n3->mpObject == 0) continue;
        }

        NounInfo* n4 = (NounInfo*)FUN_00ca71d0(v);
        if (n4->mpObject == 0) continue;
        Cty2* city = (Cty2*)((RCObject*)n4->mpObject)->Cast(0xee9b2232);
        if (city != 0 && !Slot2c(city) && city->GetCiv() == civ) return 0;

        NounInfo* n5 = (NounInfo*)FUN_00ca71d0(v);
        if (n5->mpObject == 0) continue;
        cNounEntity* ent = (cNounEntity*)((RCObject*)n5->mpObject)->Cast(0x03d5c477);
        if (ent == 0) continue;
        RCObject* sub = (RCObject*)Slot08(&ent->mSpatial34);
        if (sub == 0) continue;
        RCObject* c2 = (RCObject*)sub->Cast(0xee9b2232);
        if (c2 == 0) continue;
        if (!Slot2c(c2) && ent->FUN_00bd84e0()->FUN_00bd9bf0() == civ) return 0;
    }
    return true;
}

// @ 0x00bf1ba0
int cCivilization_s00bf_1ba0::FUN_00bf1ba0()
{
    int* noun = (int*)cGameNounManager_CreateNoun((void*)this, 0, 0x018c6de8);
    if (noun == 0)
        return 0;
    return (*(int(__fastcall**)(void*, int))((char*)*(int*)noun + 0xc))(noun, 0x0137e8e0);
}

// @ 0x00bf1cf0
void cCivilization_s00bf_1ba0::FUN_00bf1cf0(IntVec* timers)
{
    void* owner = (*(void*(__fastcall**)(void*))((char*)*(int*)this + 0x20))((void*)this);
    void* writer = (*(void*(__fastcall**)(void*))((char*)*(int*)owner + 0x18))((void*)owner);
    int count = (int)((timers->end - timers->begin) >> 5);
    WriteUint32((void*)writer, &count, 1, 0);

    for (int* p = timers->begin; p != timers->end; p += 8)
        cGonzagoTimer_Write((void*)p, 0, (void*)this);
    (*(void(__fastcall**)(void*))((char*)*(int*)this + 0x1c))((void*)this);
}

// @ 0x00bf1d90
void** StarTreeOps::MapInsert4(void** outIt, void* anchor, int* value, char hint)
{
    int side = 0;
    if (hint == 0 && anchor != (char*)this + 4 && *value >= *(int*)((char*)anchor + 0x10))
        side = 1;

    void* node = EAAllocate(0x20, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int* slot = (int*)((char*)node + 0x10);
    if (slot != 0)
    {
        slot[0] = value[0];
        slot[1] = value[1];
        slot[2] = value[2];
        slot[3] = value[3];
    }
    RBTreeInsert(node, anchor, (char*)this + 4, side);
    ++*(int*)((char*)this + 0x14);
    *outIt = node;
    return outIt;
}

// @ 0x00bf1e20
int cCivilization_s00bf_1ba0::FUN_00bf1e20()
{
    if (mField89)
        return 0;

    int count = 0;
    IntVec* list = (IntVec*)cGameNounManager_GetCivilizationList(SP_NounManager());
    for (Noun** p = (Noun**)list->begin; p != (Noun**)list->end; ++p)
    {
        Noun* other = *p;
        if (other->mField8a != mField8a)
            continue;
        int specOther = CitySpecialty(other);
        int specThis = CitySpecialty(this);
        if (specOther != specThis)
            continue;
        if (other == (Noun*)this)
            return count;
        ++count;
    }
    return 0;
}

// @ 0x00bf1f40
void cCivilization_s00bf_1ba0::FUN_00bf1f40(void* music)
{
    if (mpCityMusic != 0)
        (*(void(__fastcall**)(void*))((char*)*(int*)mpCityMusic + 0x28))(mpCityMusic);

    void* old = mpCityMusic;
    if (music != old)
    {
        if (music != 0)
            (*(void(__fastcall**)(void*))((char*)*(int*)music))(music);
        mpCityMusic = music;
        if (old != 0)
            (*(void(__fastcall**)(void*))((char*)*(int*)old + 4))(old);
    }

    UpdateCityMusicPosition((void*)this);

    if (mpCityMusic != 0 && mp454 != 0)
    {
        int* sub = (int*)((char*)mp454 + 0x120);
        int arg = (*(int(__fastcall**)(void*))((char*)*sub + 0x2c))(sub);
        int vt = *(int*)mpCityMusic;
        (*(void(__fastcall**)(void*, int))((char*)vt + 0x24))(mpCityMusic, arg);
    }
}

// @ 0x00bf1fd0
int cCivilization_s00bf_1ba0::FUN_00bf1fd0(int specialty)
{
    if (specialty == 4)
        return 1;

    int score = 0;
    if (!mField8a && MapSpecialty(FUN_00bf0f40((void*)this)) == specialty)
        score = 3;

    score += (cCivilization_CountSpecialty((int)this, 0, specialty, 1) +
              cCivilization_CountSpecialty((int)this, 0, specialty, 0)) * g_civStarCountScale;

    Noun** city = *(Noun***)((char*)this + 0x9c);
    Noun** cityEnd = *(Noun***)((char*)this + 0xa0);
    for (; city != cityEnd; ++city)
    {
        cCity* c = *(cCity**)city;
        if (c->GetVehicleSpecialty() != specialty)
            continue;
        int age = c->GetHousingAmount() / g_cityHousingDiv;
        int chosen;
        if (!c->mCounterConvBusy)
        {
            if (mField89)
                continue;
            chosen = age > 6 ? age : 6;
        }
        else
        {
            if (mField89)
                continue;
            chosen = age > 3 ? age : 3;
        }
        score += chosen;
    }

    return score < 0x25 ? score : specialty;
}

// @ 0x00bf2170
float cCivilization_s00bf_1ba0::FUN_00bf2170(int a, int b)
{
    if (a == 4)
        return 0.0f;

    float value = 0.0f;
    void* propMgr = SP_PropertyManager();
    void* prop = 0;
    int ok = ((int(__fastcall*)(void*, int, void**))(*(int*)(*(int*)propMgr + 0x30)))(propMgr, 0xb6a5c63d, &prop);
    if (ok)
    {
        int tbl = g_specialtyTable[a + b * 3];
        if (prop != 0)
        {
            if ((*(int(__fastcall**)(void*, int, void**))((char*)*(int*)prop + 0x24))(prop, tbl, &prop))
            {
                if (*(unsigned short*)((char*)prop + 0x12) == 0xd)
                    value = *(float*)FUN_041ea70(prop);
            }
        }
    }

    if (prop != 0)
        (*(void(__fastcall**)(void*))((char*)*(int*)prop + 4))(prop);

    if (CivPoliticalID((void*)this) != SP_GetPlayerEmpireID() || SP_GetCurrentGameMode() != 0x1654c05)
        return value;

    int cost = cSPSpaceEconomyTuning_GetVehicleCost(FUN_0102f810());
    return (float)cost;
}

// @ 0x00bf2270
byte ISimulatorSerializable::ReadSerialized(void* stream)
{
    int ok1 = cGameData_Read((void*)this, 0, stream);
    int ok2 = FUN_00b6e340((char*)this + 0x3c, 0, stream);
    bool ok = ok1 != 0 && ok2 != 0;

    void* w = (*(void*(__fastcall**)(void*))((char*)*(int*)stream + 0x20))(stream);
    void* dst = (*(void*(__fastcall**)(void*))((char*)*(int*)w + 0x18))(w);
    ReadInt32(dst, &mFieldC4, 1, 0);

    w = (*(void*(__fastcall**)(void*))((char*)*(int*)stream + 0x20))(stream);
    dst = (*(void*(__fastcall**)(void*))((char*)*(int*)w + 0x18))(w);
    ReadInt32(dst, &mFieldC8, 1, 0);

    w = (*(void*(__fastcall**)(void*))((char*)*(int*)stream + 0x20))(stream);
    dst = (*(void*(__fastcall**)(void*))((char*)*(int*)w + 0x18))(w);
    ReadInt32(dst, &mFieldCC, 1, 0);

    char serializer[0xa18];
    cVarListSerializer_ctor(serializer, 0, (void*)this, (void*)&g_civAttributes_s00bf_1ba0, 0x1a80d26);
    int ok3 = cVarListSerializer_Serialize(serializer, 0, stream);
    ok = ok && ok3 != 0;

    void* host = (void*)0;
    if (this != 0)
        host = (char*)this + 0x38;
    void* server = SP_MessageServer();
    (*(void(__fastcall**)(void*, void*, int))((char*)*(int*)server + 0x20))(server, host, 0x20c089c);
    UpdateCityMusicPosition((void*)this);
    return ok ? 1 : 0;
}

// @ 0x00bf2380
static bool __fastcall ReleaseDeadResources(void* map, int edx)
{
    for (RanNode* n = *(RanNode**)((char*)map + 8); n != (RanNode*)((char*)map + 4);
         n = (RanNode*)RBTreeIncrement(n))
    {
        if (n->mField14 == 0)
            continue;
        int* mgr = (int*)EA_ResourceMan_GetManager();
        char ok = (*(char(__fastcall**)(void*, int, void**, int, int, int, int, int))((char*)*mgr + 0xc))
                      (mgr, 0, (void**)&n->mField14, 0, 0, 0, 0, 0);
        if (!ok)
        {
            n->mField14 = 0;
            n->mField18 = 0;
            n->mField1c = 0;
        }
    }
    return true;
}

// @ 0x00bf23d0
void* cGameData::func40h()
{
    byte* self = (byte*)this;
    *(int*)(self + 0x484) = 0;
    *(int*)(self + 0x488) = 0;
    *(int*)(self + 0x48c) = 0;

    IntVec list = {0, 0, 0};
    void* sphere = cTerrainEditor_GetCurrentTerrainSphere(SP_NounManager());
    if (sphere != 0)
    {
        FUN_00555e80(*(int*)((char*)sphere + 0x10fc), &list);
        FUN_00555e80(*(int*)((char*)sphere + 0x1100), &list);
        FUN_00555e80(*(int*)((char*)sphere + 0x1104), &list);
    }

    bool anyBiped = false;
    uint n = (uint)((list.end - list.begin) >> 2);
    if (n != 0)
    {
        for (uint i = 0; i < n; ++i)
        {
            int kind = cCity_UnknownBef980((void*)this, 0, list.begin[i]);
            if (kind == 2 || kind == 5 || kind == 8)
                anyBiped = true;
            if (kind != -1)
            {
                int need = SpecialtySlots(kind);
                if (need <= (int)((mListEnd - mListBegin) >> 2) || DAT_0168bd6c != 0)
                    self[0x484 + kind] = 1;
            }
        }

        if (anyBiped)
            goto done;
    }

    {
        int spec = CitySpecialty((Noun*)this);
        int kind;
        if (spec == 0)
            kind = 2;
        else if (spec == 1)
            kind = 8;
        else if (spec == 2)
            kind = 5;
        else
            goto done;

        if ((int)((mListEnd - mListBegin) >> 2) >= SpecialtySlots(kind))
            self[0x484 + kind] = 1;
    }

done:
    int cityCount = (int)((mListEnd - mListBegin) >> 2);
    if (DAT_0167a60c == 0)
    {
        int obj = (int)EAAllocate(200, DAT_0145f924, 0, 0, 0, 0);
        if (obj != 0)
        {
            SimSingleton_ctor((void*)obj);
            DAT_0167a60c = obj;
        }
        else
            DAT_0167a60c = 0;
    }
    if (cityCount == *(int*)(DAT_0167a60c + 0xac))
    {
        self[0x486] = 0;
        self[0x48c] = 0;
        self[0x489] = 0;
    }

    if (list.begin != 0 && *(int*)((char*)list.begin - 4) != 0)
        operator_delete(list.begin);
    return list.begin;
}

// @ 0x00bf2660
void* cGameData::FUN_00bf2660(int)
{
    return func40h();
}

// @ 0x00bf2670
bool CallSlot1cForEach(void* arg, void* map)
{
    for (OtherNode* n = *(OtherNode**)((char*)map + 8); n != (OtherNode*)((char*)map + 4);
         n = (OtherNode*)RBTreeIncrement(n))
    {
        void* obj = *(void**)((char*)n + 0x10);
        if (obj != 0)
            (*(void(__thiscall**)(void*, void*))((char*)*(int*)obj + 0x1c))(obj, arg);
    }
    return true;
}

// @ 0x00bf2840
StarRecord* StarCopyCtorRange(StarRecord** out, StarRecord* first, StarRecord* last, StarRecord* dst)
{
    *out = dst;
    if (first != last)
    {
        do
        {
            if (dst != 0)
            {
                ((StarRecord*)dst)->vptr = 0x01465d54;
                ((StarRecord*)dst)->pad04 = 0;
                *(int*)((char*)dst + 8) = *(int*)((char*)first + 8);
                *(int*)((char*)dst + 0xc) = *(int*)((char*)first + 0xc);
                *(int*)((char*)dst + 0x10) = *(int*)((char*)first + 0x10);
                *(int*)((char*)dst + 0x14) = *(int*)((char*)first + 0x14);
                *(byte*)((char*)dst + 0x18) = *(byte*)((char*)first + 0x18);
                *(int*)((char*)dst + 0x1c) = *(int*)((char*)first + 0x1c);
                ((StarRecord*)dst)->vptr = 0x01464450;
            }
            first = (StarRecord*)((char*)first + 0x20);
            dst = (StarRecord*)((char*)dst + 0x20);
        } while (first != last);
        *out = dst;
    }
    return (StarRecord*)out;
}

// @ 0x00bf28b0
void StarAssignForward(void* dst, void* last, void* src)
{
    for (; dst != last; dst = (char*)dst + 0x20)
    {
        *(int*)((char*)dst + 8) = *(int*)((char*)src + 8);
        *(int*)((char*)dst + 0xc) = *(int*)((char*)src + 0xc);
        *(int*)((char*)dst + 0x10) = *(int*)((char*)src + 0x10);
        *(int*)((char*)dst + 0x14) = *(int*)((char*)src + 0x14);
        *(byte*)((char*)dst + 0x18) = *(byte*)((char*)src + 0x18);
        *(int*)((char*)dst + 0x1c) = *(int*)((char*)src + 0x1c);
    }
}

// @ 0x00bf28f0
void StarFillN(void* dst, uint n, void* src)
{
    if (n <= 0)
        return;
    StarRecord* d = (StarRecord*)((char*)dst + 8);
    StarRecord* s = (StarRecord*)src;
    do
    {
        StarRecord* rec = (StarRecord*)((char*)d - 8);
        if (rec != 0)
        {
            rec->vptr = 0x01465d54;
            rec->pad04 = 0;
            rec->f08 = s->f08;
            rec->f0c = s->f0c;
            rec->f10 = s->f10;
            rec->f14 = s->f14;
            rec->f18 = s->f18;
            rec->f1c = s->f1c;
            rec->vptr = 0x01464450;
        }
        --n;
        d = (StarRecord*)((char*)d + 0x20);
    } while (n > 0);
}

// @ 0x00bf2960
StarRecord* StarCopyCtorRange2(StarRecord* first, StarRecord* last, StarRecord* dst)
{
    for (; first != last; first = (StarRecord*)((char*)first + 0x20), dst = (StarRecord*)((char*)dst + 0x20))
    {
        if (dst != 0)
        {
            *(int*)((char*)dst + 0) = 0x01465d54;
            *(int*)((char*)dst + 4) = 0;
            *(int*)((char*)dst + 8) = *(int*)((char*)first + 8);
            *(int*)((char*)dst + 0xc) = *(int*)((char*)first + 0xc);
            *(int*)((char*)dst + 0x10) = *(int*)((char*)first + 0x10);
            *(int*)((char*)dst + 0x14) = *(int*)((char*)first + 0x14);
            *(byte*)((char*)dst + 0x18) = *(byte*)((char*)first + 0x18);
            *(int*)((char*)dst + 0x1c) = *(int*)((char*)first + 0x1c);
            *(int*)((char*)dst + 0) = 0x01464450;
        }
    }
    return dst;
}

// @ 0x00bf29c0
StarRecord* StarAssignForward2(StarRecord* first, StarRecord* last, StarRecord* dst)
{
    for (; first != last; first = (StarRecord*)((char*)first + 0x20), dst = (StarRecord*)((char*)dst + 0x20))
    {
        *(int*)((char*)dst + 8) = *(int*)((char*)first + 8);
        *(int*)((char*)dst + 0xc) = *(int*)((char*)first + 0xc);
        *(int*)((char*)dst + 0x10) = *(int*)((char*)first + 0x10);
        *(int*)((char*)dst + 0x14) = *(int*)((char*)first + 0x14);
        *(byte*)((char*)dst + 0x18) = *(byte*)((char*)first + 0x18);
        *(int*)((char*)dst + 0x1c) = *(int*)((char*)first + 0x1c);
    }
    return dst;
}

// @ 0x00bf2a10
StarRecord* StarAssignBackward(StarRecord* last, StarRecord* first, StarRecord* dstEnd)
{
    while (first != last)
    {
        first = (StarRecord*)((char*)first - 0x20);
        dstEnd = (StarRecord*)((char*)dstEnd - 0x20);
        dstEnd->f08 = first->f08;
        dstEnd->f0c = first->f0c;
        dstEnd->f10 = first->f10;
        dstEnd->f14 = first->f14;
        dstEnd->f18 = first->f18;
        dstEnd->f1c = first->f1c;
    }
    return dstEnd;
}

// @ 0x00bf2a60
int cGameData::FUN_00bf2a60()
{
    for (Noun** t = mListBegin; t != mListEnd; ++t)
    {
        IntVec* members = (IntVec*)cTribe_GetMembers(*t);
        for (void** m = (void**)members->begin; m != (void**)members->end; ++m)
            (*(void(__fastcall**)(void*))((char*)*(int*)*m + 0x40))(*m);
    }
    for (Noun** v = mVehicleBegin; v != mVehicleEnd; ++v)
        (*(void(__fastcall**)(void*))((char*)*(int*)*v + 0x40))(*v);
    ReleaseDeadResources((char*)this + 0x6c, 0);
    return 1;
}

// @ 0x00bf2ae0
float cSPSimulatorSpaceGame::FUN_00bf2ae0()
{
    float total = mField98;
    if (!mField89)
    {
        float x = mField4ac;
        total = x + total;
        x = mField4b0;
        total = x + total;
    }

    for (Noun** p = mNPCUFOBegin; p != mNPCUFOEnd; ++p)
    {
        cSimulatorPlayerUFO* ufo = (cSimulatorPlayerUFO*)*p;
        int b1c = ufo->mFieldB1c;
        int b20 = ufo->mFieldB20;
        total = ((cCivilization_s00bf_1ba0*)this)->FUN_00bf2170(b20, b1c) + total;
    }

    for (Noun** city = mListBegin; city != mListEnd; ++city)
    {
        IntVec* members = cTribe_GetMembers(*city);
        int n = (int)((members->end - members->begin) >> 2);
        for (int i = 0; i < n; ++i)
        {
            void* obj = (void*)members->begin[i];
            if (obj == 0)
                continue;
            if ((*(int(__fastcall**)(void*, int))((char*)*(int*)obj + 0xc))(obj, 0x1a55e4d))
            {
                int pid = CivPoliticalID((void*)this);
                total = FUN_00bcdea0(pid) + total;
            }
            else if ((*(int(__fastcall**)(void*, int))((char*)*(int*)obj + 0xc))(obj, 0xecade42))
            {
                int pid = CivPoliticalID((void*)this);
                total = FUN_00bcde40(pid) + total;
            }
            else if ((*(int(__fastcall**)(void*, int))((char*)*(int*)obj + 0xc))(obj, 0xff10521))
            {
                int pid = CivPoliticalID((void*)this);
                total = FUN_00bcde70(pid) + total;
            }
        }
    }
    return total;
}

// @ 0x00bf2c60
StarTree* __fastcall StarMapInit(StarTree* map)
{
    StarNode* nil = &map->mAnchor;
    int zero = 0;
    nil->mpParent = (StarNode*)zero;
    nil->mpRight = (StarNode*)zero;
    nil->mField0c = zero;
    nil->mpLeft = nil;
    *(volatile int*)((char*)map + 8) = (int)nil;
    *(volatile int*)((char*)map + 0xc) = zero;
    *(volatile byte*)((char*)map + 0x10) = (byte)zero;
    *(volatile int*)((char*)map + 0x14) = zero;
    return map;
}

// @ 0x00bf2c80
bool StarTree::ContainsMap(int key)
{
    StarNode* result;
    StarNode** out = find(&result, key);
    return *out != &mAnchor;
}

// @ 0x00bf2cb0
bool cGameData::StarMapContainsMap2(int value)
{
    StarTree* tree = (StarTree*)((char*)this + 0x6c);
    int key = value;
    StarNode* result;
    StarNode** out = tree->find(&result, key);
    return *out != &tree->mAnchor;
}

// @ 0x00bf2ce0
void __cdecl FUN_00bf2ce0(int* stream, int* set)
{
	int* obj = (int*)((T0)(*(int*)(*stream + 0x20)))((void*)stream);
	int writer = ((T0)(*(int*)(*obj + 0x18)))((void*)obj);
	int key = set[5];
	WriteUint32((void*)writer, &key, 1, 0);

	for (int node = set[2]; node != (int)set + 4; node = (int)RBTreeIncrement((void*)node))
	{
		int id = 0;
		int* p = *(int**)(node + 0x10);
		if (p != 0)
			id = ((T1)(*(int*)(*p + 0xc)))((void*)p, 0x179c807);

		((T1)(*(int*)(*stream + 0x2c)))((void*)stream, id);
		((T0)(*(int*)(*stream + 0x1c)))((void*)stream);

		int* o2 = (int*)((T0)(*(int*)(*stream + 0x20)))((void*)stream);
		int w2 = ((T0)(*(int*)(*o2 + 0x18)))((void*)o2);
		int star = *(int*)(node + 0x14);
		WriteUint32((void*)w2, &star, 1, 0);
		((T0)(*(int*)(*stream + 0x1c)))((void*)stream);
	}
	((T0)(*(int*)(*stream + 0x1c)))((void*)stream);
}

// @ 0x00bf2f00
int __fastcall FUN_00bf2f00(int self, int dummy, int mode)
{
	int* it = (int*)*(int*)(self + 0x9c);
	int* end = (int*)*(int*)(self + 0xa0);
	int total = 0;
	int limit = 0xf;

	if (it != end)
	{
		do
		{
			int obj = *it;
			int count = 3;
			if (mode == 0)
			{
				int* v[3] = { 0, 0, 0 };
				((Eng*)obj)->B2b10((int)&DAT_018ea2cc, v);
				count = (int)((((int)v[1] - (int)v[0]) >> 2) + 1U) >> 1;
				limit = 0xf;
				for (int** p = (int**)v[0]; (int)p < (int)v[1]; p++)
					if (*p != 0)
						(*(T0*)(*(int*)*p + 4))((void*)*p);
				if (v[0] != 0 && v[0][-1] != 0)
					operator_delete(v[0]);
			}
			else if (mode == 1)
			{
				int* pos = cCity_GetPositionPtr((void*)obj);
				if (*(float*)pos != DAT_0168c514 || *(float*)((char*)pos + 4) != DAT_0168c518
				    || *(float*)((char*)pos + 8) != DAT_0168c51c)
				{
					int* v[3] = { 0, 0, 0 };
					((Eng*)obj)->B2b10((int)&DAT_018ea2cc, v);
					count = (int)((uint)(((int)v[1] - (int)v[0]) >> 2) >> 1);
					limit = 0xa;
					FUN_00ae6970(v);
				}
			}
			else if (mode == 2)
			{
				int n = FUN_00bd9b60((void*)obj);
				count = (n + 1) / 2;
				limit = 0xf;
			}
			total += count < 3 ? count : 3;
			it++;
		} while (it != end);
	}
	return total < limit ? total : limit;
}

// @ 0x00bf30b0
void __fastcall FUN_00bf30b0(int self, int dummy, int key, Tri* out)
{
	int mapped = -1;
	switch (key)
	{
	case 0x441cd3e6:
	case 0x8f963dcb:
		mapped = 0x7d433fad;
		break;
	case 0x1f2a25b6:
	case 0x449c040f:
		mapped = 0x9ad7d4aa;
		break;
	case 0x1a4e0708:
	case 0x2a5147a9:
		mapped = 0xf670aa43;
		break;
	case 0x4e3f7777:
	case 0x47c10953:
	case 0x72c49181:
		mapped = 0x99e92f05;
		break;
	}

	int slot;
	int arg = mapped;
	int** res = (int**)((Eng*)self)->FindEmb(&slot, &arg);
	if (*res != (int*)(self + 4))
	{
		Tri* v = (Tri*)((Eng*)self)->Bf9700(mapped);
		out->a = v->a;
		out->b = v->b;
		out->c = v->c;
		return;
	}

	Tri t;
	t.a = -1;
	t.b = -1;
	t.c = -1;
	*out = t;
}

// @ 0x00bf3180
void __fastcall FUN_00bf3180(int* self)
{
	if ((*(int*)((char*)self + 0xa0) - *(int*)((char*)self + 0x9c)) & 0xfffffffc)
	{
		if (DAT_0167a60c == 0)
		{
			int p = (int)EAAllocate(0xc8, DAT_0145f924, 0, 0, 0, 0);
			if (p != 0)
			{
				SimSingleton_ctor((void*)p);
				DAT_0167a60c = p;
			}
			else
			{
				DAT_0167a60c = 0;
			}
		}

		if (*(int*)(DAT_0167a60c + 0xb0) <= 0)
		{
			int* civ = (int*)self[0x27];
			if (civ != 0)
			{
				int* player = (int*)GetPlayerCivilization(SP_NounManager());
				if (player != 0 && *(char*)((char*)player + 0x8d) != 0 && player[0xa6] >= 3
				    && *(char*)((char*)player + 0x4cc) == 0)
				{
					if (CommScreen_IsActive(CommManager_s00bf_2ce0()) == 0 && *(char*)((char*)self + 0x90) == 0)
					{
						if (*(char*)((char*)self + 0x91) != 0)
						{
							int* ctx = (int*)GetCommContext((void*)(*(int*)((char*)FUN_01021260_s00bf_2ce0() + 0x13c)), 0,
							                                0xdbf385bf, 0xd9597cc9, 0);
							cCommManager_ShowCommEvent(CommManager_s00bf_2ce0(), 0, (void*)civ, (void*)civ, ctx, 0);
							*(char*)((char*)self + 0x90) = 1;
						}

						if (RandomUint32Uniform((void*)0x1601760, 0, 0x14) == 0)
						{
							int a = (*(T0*)(*(int*)player + 0x4c))((void*)player);
							int b = (*(T1*)(*self + 0x4c))((void*)self, a);
							if (FUN_00bef620(SP_RelationshipManager(), 0, b) != 0)
							{
								int* list = 0;
								FUN_00ba95a0((void*)GetCivilizationList(SP_NounManager()), 0, &list);
								int* begin = list;
								int count = (int)((char*)list - (char*)begin) >> 2;
								int n = (int)((char*)list - (char*)begin);
								(void)n;
								int total = 0;
								for (int i = 0; i < count; i++)
								{
									int* c = (int*)((int*)begin)[i];
									if (c == self || c == player
									    || FUN_00bef620(SP_RelationshipManager(), 0,
									                     (*(T1*)(*(int*)c + 0x4c))((void*)c,
									                        (*(T0*)(*(int*)player + 0x4c))((void*)player))) != 0)
										total += (*(int*)((char*)c + 0xa0) - *(int*)((char*)c + 0x9c)) >> 2;
								}
								if (total == *(int*)(FUN_00b26930() + 0xac))
								{
									int* ctx = (int*)GetCommContext((void*)(*(int*)((char*)FUN_01021260_s00bf_2ce0() + 0x13c)), 0,
									                                0xdbf385bf, 0x6b6ad65e, 0);
									cCommManager_ShowCommEvent(CommManager_s00bf_2ce0(), 0, (void*)civ, (void*)civ, ctx, 0);
									*(char*)((char*)self + 0x90) = 1;
								}
								FUN_00ae6970(&list);
								return;
							}

							if (((*(int*)((char*)self + 0xa0) - *(int*)((char*)self + 0x9c)) & 0xfffffffc) == 4)
							{
								int n2 = (*(int*)((char*)player + 0xa0) - *(int*)((char*)player + 0x9c)) >> 2;
								if (n2 + 1 == *(int*)(FUN_00b26930() + 0xac))
								{
									int* ctx = (int*)GetCommContext((void*)(*(int*)((char*)FUN_01021260_s00bf_2ce0() + 0x13c)), 0,
									                                0xdbf385bf, 0xd9597cc9, 0);
									cCommManager_ShowCommEvent(CommManager_s00bf_2ce0(), 0, (void*)civ, (void*)civ, ctx, 0);
									*(char*)((char*)self + 0x90) = 1;
								}
							}
						}
					}
				}
			}
		}
	}
}

// @ 0x00bf3420
int __fastcall FUN_00bf3420(int* v, int dummy, int pos)
{
	if ((uint)(pos + 4) < (uint)v[1])
		do_copy((void*)(pos + 4), (void*)v[1], (void*)pos);

	v[1] -= 4;
	int* end = (int*)v[1];
	int obj = *end;
	if (obj != 0)
		(*(T0*)(*(int*)obj + 4))((void*)obj);
	return pos;
}

// @ 0x00bf34f0
void __fastcall FUN_00bf34f0(int* self, int dummy, int* map)
{
	((Eng*)map)->NukeSubtree((void*)map[3]);

	int* anchor = (int*)((char*)map + 4);
	*anchor = (int)anchor;
	map[2] = (int)anchor;
	map[3] = 0;
	*(char*)((char*)map + 0x10) = 0;
	map[5] = 0;

	int count = 0;
	int* w = (int*)((T0)(*(int*)(*self + 0x20)))((void*)self);
	int stream = ((T0)(*(int*)(*w + 0x18)))((void*)w);
	ReadInt32((void*)stream, &count, 1, 0);

	for (uint i = 0; i < (uint)count; i++)
	{
		int key = 0;
		int world[3] = { 0, 0, 0 };

		int* w2 = (int*)((T0)(*(int*)(*self + 0x20)))((void*)self);
		int s2 = ((T0)(*(int*)(*w2 + 0x18)))((void*)w2);
		ReadInt32((void*)s2, &key, 1, 0);
		((T0)(*(int*)(*self + 0x1c)))((void*)self);
		((Eng*)self)->E2ed0(world);
		((T0)(*(int*)(*self + 0x1c)))((void*)self);

		int slot = 0;
		int inserted = ((Eng*)map)->Bf2710(&key, world, 0);
		if (inserted == 0)
		{
			*(int*)(slot + 0x14) = world[0];
			*(int*)(slot + 0x18) = world[1];
			*(int*)(slot + 0x1c) = world[2];
		}
	}

	((T0)(*(int*)(*self + 0x1c)))((void*)self);
}

// @ 0x00bf36f0
void __fastcall FUN_00bf36f0(int* self)
{
	int* p = (int*)self[0x10b];
	int* sub = (int*)((char*)self + 0x3c);

	self[0] = (int)vtbl_014693b8;
	self[1] = (int)vtbl_014693a4;
	self[0xd] = (int)vtbl_0146938c;
	self[0xe] = (int)vtbl_0146937c;
	self[0xf] = (int)vtbl_01469360;

	if (p != 0)
	{
		SetSerializer_or_release((void*)p);
		operator_delete(p);
	}
	*(volatile int*)(self + 0x10b) = 0;
	int* q = (int*)*(volatile int*)(self + 0x129);

	if (q != 0)
		(*(T0*)(*(int*)q + 4))((void*)q);
	FUN_00bf1b60((void*)((char*)self + 0x490));
	FUN_00aed92d0((void*)((char*)self + 0x470));

	if ((int*)self[0x11b] != 0)
		(*(T0*)(*(int*)self[0x11b] + 4))((void*)self[0x11b]);
	if ((int*)self[0x11a] != 0)
		(*(T0*)(*(int*)self[0x11a] + 4))((void*)self[0x11a]);
	if ((int*)self[0x119] != 0)
		(*(T0*)(*(int*)self[0x119] + 4))((void*)self[0x119]);
	if ((int*)self[0x118] != 0)
		(*(T0*)(*(int*)self[0x118] + 4))((void*)self[0x118]);
	if ((int*)self[0x117] != 0)
		(*(T0*)(*(int*)self[0x117] + 4))((void*)self[0x117]);
	if ((int*)self[0x116] != 0)
		(*(T0*)(*(int*)self[0x116] + 4))((void*)self[0x116]);
	if ((int*)self[0x115] != 0)
		(*(T0*)(*(int*)self[0x115] + 4))((void*)self[0x115]);

	Eng* eng = (Eng*)((char*)self + 0x410);
	eng->Eb6280((void*)*(volatile int*)(self + 0x107));

	cGonzagoTimer_dtor((void*)((char*)self + 0x3f0));
	cGonzagoTimer_dtor((void*)((char*)self + 0x3c8));
	cGonzagoTimer_dtor((void*)((char*)self + 0x3a0));
	cGonzagoTimer_dtor((void*)((char*)self + 0x378));
	cGonzagoTimer_dtor((void*)((char*)self + 0x350));
	cGonzagoTimer_dtor((void*)((char*)self + 0x328));
	cGonzagoTimer_dtor((void*)((char*)self + 0x300));

	if ((int*)self[0xbe] != 0)
		(*(T0*)(*(int*)self[0xbe] + 4))((void*)self[0xbe]);

	cGonzagoTimer_dtor((void*)((char*)self + 0x2d8));

	if ((int*)self[0xb4] != 0)
		(*(T0*)(*(int*)self[0xb4] + 4))((void*)self[0xb4]);

	cGonzagoTimer_dtor((void*)((char*)self + 0x2b0));

	if ((int*)self[0xab] != 0)
		(*(T0*)(*(int*)self[0xab] + 4))((void*)self[0xab]);
	if ((int*)self[0xaa] != 0)
		(*(T0*)(*(int*)self[0xaa] + 4))((void*)self[0xaa]);
	if ((int*)self[0xa9] != 0)
		(*(T0*)(*(int*)self[0xa9] + 4))((void*)self[0xa9]);

	int e = self[0xa2];
	if ((int)((self[0xa4] - e) & 0xfffffffe) > 2 && e != 0)
		operator_delete((void*)e);

	e = self[0x9e];
	if ((int)((self[0xa0] - e) & 0xfffffffe) > 2 && e != 0)
		operator_delete((void*)e);

	if ((int*)self[0x9d] != 0)
		(*(T0*)(*(int*)self[0x9d] + 4))((void*)self[0x9d]);

	cGonzagoTimer_dtor((void*)((char*)self + 0x248));
	cGonzagoTimer_dtor((void*)((char*)self + 0x228));
	cGonzagoTimer_dtor((void*)((char*)self + 0x208));
	cGonzagoTimer_dtor((void*)((char*)self + 0x1e8));
	cGonzagoTimer_dtor((void*)((char*)self + 0x1c8));
	cGonzagoTimer_dtor((void*)((char*)self + 0x1a8));
	cGonzagoTimer_dtor((void*)((char*)self + 0x188));
	cGonzagoTimer_dtor((void*)((char*)self + 0x168));
	cGonzagoTimer_dtor((void*)((char*)self + 0x148));
	cGonzagoTimer_dtor((void*)((char*)self + 0x128));
	cGonzagoTimer_dtor((void*)((char*)self + 0x108));
	cGonzagoTimer_dtor((void*)((char*)self + 0xe8));

	FUN_00aed92d0((void*)((char*)self + 0xd4));
	FUN_00ae6970((void*)((char*)self + 0xb0));
	FUN_00ae6970((void*)((char*)self + 0x9c));
	Eng* sub2 = (Eng*)((char*)self + 0x6c);
	sub2->NukeSubtree((void*)*(volatile int*)(self + 0x1e));
	FUN_00b6edf0((void*)sub);
	self[0xe] = (int)vtbl_013eb394;
	cGameData_dtor((void*)self);
}

// @ 0x00bf3b50
void __fastcall FUN_00bf3b50(int self, int dummy, int noun)
{
	int* p = (int*)*(int*)(self + 0xb0);
	int* e = (int*)*(int*)(self + 0xb4);

	for (; p != e; p++)
	{
		if (*p != noun)
			continue;

		if ((int*)(p + 1) < (int*)*(int*)(self + 0xb4))
			do_copy(p + 1, (void*)*(int*)(self + 0xb4), p);
		*(int*)(self + 0xb4) -= 4;
		int obj = **(int**)(self + 0xb4);
		if (obj != 0)
			(*(T0*)(*(int*)obj + 4))((void*)obj);
		break;
	}

	uint count = (uint)((*(int*)(self + 0xd8) - *(int*)(self + 0xd4)) >> 2);
	int* cur = *(int**)(self + 0xd4);
	for (uint i = 0; i < count; i++, cur++)
	{
		int key = noun != 0 ? noun + 0x34 : 0;
		if (*cur != key)
			continue;

		int* arr = (int*)*(int*)(self + 0xd4);
		int elem = arr[i];
		int last = arr[count - 1];
		if (last != elem)
		{
			if (last != 0)
				(*(T0*)(*(int*)last + 0xbc))((void*)last);
			arr[i] = last;
			if (elem != 0)
				(*(T0*)(*(int*)elem + 0xc0))((void*)elem);
		}
		*(int*)(self + 0xd8) -= 4;
		int obj = **(int**)(self + 0xd8);
		if (obj != 0)
			(*(T0*)(*(int*)obj + 0xc0))((void*)obj);
		return;
	}
}

// @ 0x00bf3c50
void __fastcall FUN_00bf3c50(int self, int dummy, int noun)
{
	byte* arg;
	if (noun != 0)
	{
		(*(T0*)(*(int*)noun))((void*)noun);
		arg = (byte*)(noun + 0x5d0);
	}
	else
	{
		arg = 0;
	}

	int* bm = (int*)SP_BehaviorManager();
	(*(T1*)(*(int*)bm + 0x3c))((void*)bm, (int)arg);
	((Eng*)self)->Sub3b50(noun);
	((Eng*)SP_NounManager())->RemoveNoun((void*)noun);
	if (noun != 0)
		(*(T0*)(*(int*)noun + 4))((void*)noun);
}

// @ 0x00bf3cb0
void* __fastcall FUN_00bf3cb0(int* map, int dummy, int* key)
{
	int* parent = map + 1;
	int* node = (int*)map[3];
	int* where = parent;

	if (node != 0)
	{
		int k = *key;
		while (node != 0)
		{
			if (node[4] < k)
			{
				node = (int*)*node;
			}
			else
			{
				where = node;
				node = (int*)node[1];
			}
		}
	}

	if (where != parent && where[4] <= *key)
		return (char*)where + 0x14;

	int k[4] = { *key, 0, 0, 0 };
	int inserted = 0;
	((Eng*)map)->Bf2da0(&inserted, (void*)where, k, (int)key & 0xffffff00);
	return (char*)inserted + 0x14;
}

// @ 0x00bf3d40
byte __cdecl FUN_00bf3d40(int* stream, int id, int* map)
{
	byte ok = 1;
	if (map[5] != 0)
	{
		int* src;
		int tmp[3];

		if (id != 0)
		{
			src = (int*)ConvertToString16(tmp + 1, id, -1);
		}
		else
		{
			tmp[0] = 0;
			tmp[1] = 0;
			tmp[2] = 0;
			((Eng*)tmp)->RangeInit(0);
			src = tmp;
		}

		int str[3];
		((Eng*)str)->WstringCtor(src);
		if (id == 0 && ((tmp[1] - tmp[0]) & 0xfffffffe) > 2 && tmp[0] != 0)
			operator_delete((void*)tmp[0]);
		if (id != 0 && ((tmp[2] - tmp[1]) & 0xfffffffe) > 2 && tmp[1] != 0)
			operator_delete((void*)tmp[1]);

		void* text = str[0] != str[1] ? (void*)str[0] : (void*)&DAT_013f6254;
		(*(void (__thiscall*)(void*, void*))(*(int*)stream))((void*)stream, text);

		for (int node = map[2]; node != (int)map + 4; node = (int)RBTreeIncrement((void*)node))
		{
			if (ok != 0)
			{
				int r = FUN_00ae5530((void*)stream, 0, (void*)(node + 0x14), (void*)DAT_0145ba48);
				ok = (byte)(r != 0);
			}
			else
			{
				ok = 0;
			}
		}

		void* text2 = str[0] != str[1] ? (void*)str[0] : (void*)&DAT_013f6254;
		(*(void (__thiscall*)(void*, void*))(*(int*)stream + 4))((void*)stream, text2);
		if (((str[1] - str[0]) & 0xfffffffe) > 2 && str[0] != 0)
			operator_delete((void*)str[0]);
	}
	return ok;
}

// @ 0x00bf3f80
void __cdecl FUN_00bf3f80(int* stream, int* map)
{
	((Eng*)map)->Eb6280((void*)map[3]);

	int* anchor = (int*)((char*)map + 4);
	*anchor = (int)anchor;
	map[2] = (int)anchor;
	map[3] = 0;
	*(char*)((char*)map + 0x10) = 0;
	map[5] = 0;

	int count = 0;
	int* w = (int*)((T0)(*(int*)(*stream + 0x20)))((void*)stream);
	int s = ((T0)(*(int*)(*w + 0x18)))((void*)w);
	ReadInt32((void*)s, &count, 1, 0);

	for (uint i = 0; i < (uint)count; i++)
	{
		int key = 0;
		float value = 0.0f;
		int obj = 0;

		(*(void (__thiscall*)(void*, int, int*, int))(*(int*)(*stream + 0x28)))(
		    (void*)stream, (int)0xee9b2232, &key, 0);
		((T0)(*(int*)(*stream + 0x1c)))((void*)stream);

		int* w2 = (int*)((T0)(*(int*)(*stream + 0x20)))((void*)stream);
		int s2 = ((T0)(*(int*)(*w2 + 0x18)))((void*)w2);
		ReadInt32((void*)s2, &value, 1, 0);
		((T0)(*(int*)(*stream + 0x1c)))((void*)stream);

		if (obj != 0)
			(*(T0*)(*(int*)obj))((void*)obj);

		int slot = ((Eng*)map)->Bf2e70(&key, &value, 0);
		if (obj != 0)
			(*(T0*)(*(int*)obj + 4))((void*)obj);

		*(float*)(slot + 0x14) = value;

		if (obj != 0)
			(*(T0*)(*(int*)obj + 4))((void*)obj);
	}

	((T0)(*(int*)(*stream + 0x1c)))((void*)stream);
}

// @ 0x00bf4170
void cCommunityEditor::InsertCityAt(int* pPosition, cCity_s00bf_4170* pCity, int nCount)
{
    uint32_t nCapacityLeft = (uint32_t)(mpCitiesCap - mpCitiesBegin);
    if (nCapacityLeft < (uint32_t)nCount) {
        uint32_t nSize = (uint32_t)(mpCitiesEnd - mpCitiesBegin);
        uint32_t nGrow = nSize * 2;
        if (nSize == 0)
            nGrow = 1;
        uint32_t nNewCap = nSize + (uint32_t)nCount;
        if (nNewCap < nGrow)
            nNewCap = nGrow;

        cCity_s00bf_4170** pNew = nullptr;
        if (nNewCap != 0)
            pNew = (cCity_s00bf_4170**)new uint8_t[nNewCap * 4];

        cCity_s00bf_4170** pSlot = pNew + ((cCity_s00bf_4170**)pPosition - mpCitiesBegin);
        for (cCity_s00bf_4170** pCur = mpCitiesBegin; pCur != (cCity_s00bf_4170**)pPosition; ++pCur)
            *pSlot++ = *pCur;

        for (int i = 0; i < nCount; ++i)
            *pSlot++ = pCity;

        for (cCity_s00bf_4170** pCur = (cCity_s00bf_4170**)pPosition; pCur != mpCitiesEnd; ++pCur)
            *pSlot++ = *pCur;

        if (mpCitiesBegin != nullptr)
            operator_delete__(mpCitiesBegin);

        mpCitiesBegin = pNew;
        mpCitiesEnd = pSlot;
        mpCitiesCap = pNew + nNewCap;
        return;
    }

    if (nCount == 0)
        return;

    CityAddRef(pCity);

    uint32_t nTail = (uint32_t)(mpCitiesEnd - (cCity_s00bf_4170**)pPosition);
    if ((uint32_t)nCount < nTail) {
        cCity_s00bf_4170** pMove = mpCitiesEnd - nCount;
        CityVectorShift(pMove, mpCitiesEnd, mpCitiesEnd);
        mpCitiesEnd += nCount;
        CityVectorCopyFill((cCity_s00bf_4170**)pPosition + nCount, (cCity_s00bf_4170**)pPosition, pMove);
        CityVectorShiftDown((cCity_s00bf_4170**)pPosition, (cCity_s00bf_4170**)pPosition + nCount, pMove, (cCity_s00bf_4170**)pPosition);
    } else {
        for (int i = 0; i < nCount - (int)nTail; ++i)
            mpCitiesEnd[i] = pCity;
        mpCitiesEnd += nCount - nTail;
        CityVectorShift((cCity_s00bf_4170**)pPosition, mpCitiesEnd, mpCitiesEnd);
        mpCitiesEnd += nTail;
        CityVectorCopyFill((cCity_s00bf_4170**)pPosition, (cCity_s00bf_4170**)pPosition + nCount, mpCitiesEnd);
    }

    if (pCity != nullptr)
        CityRelease(pCity);
}

// @ 0x00bf4350
cCommunityEditor* cCommunityEditor::AttachCity(cCity_s00bf_4170* pCity)
{
    CityAddRef(pCity);
    return this;
}

// @ 0x00bf4370
void cCommunityEditor::ReduceCitiesOnPlanet(cCity_s00bf_4170* pCity)
{
    if (pCity == nullptr)
        return;

    if (mpCityMusicEditor == nullptr) {
        if (mBadgeToasterShown == 0) {
            cPlayerCityMusic* pMusic = new cPlayerCityMusic();
            mpCityMusicEditor = pMusic;
        } else {
            int nSpecialty = pCity->GetVehicleSpecialty();
            mpCityMusicEditor = (cPlayerCityMusic*)CreateMusicForSpecialty(nSpecialty);
        }
    }

    if (mpCitiesBegin == mpCitiesEnd) {
        if (mpCityMusicEditor != nullptr)
            mpCityMusicEditor->PlayMelody(0);
    }

    CityAddRef(pCity);

    if (mpCitiesEnd < mpCitiesCap) {
        *mpCitiesEnd++ = pCity;
    } else {
        CityListAppend(this, mpCitiesEnd, pCity);
    }

    CityRelease(pCity);

    ReduceCitiesForPlanet(this);
    RefreshCityBadges();

    if (mpCityMusicEditor != nullptr && mpCityMusicEditor->Query((void*)0x4223298) != nullptr)
        mpCityMusicEditor->PlayMelody(0);

    uint32_t nCount = (uint32_t)(mpCitiesEnd - mpCitiesBegin);
    uint32_t nTarget = GetCityCountTarget();
    if (nCount < nTarget) {
        if (nCount > 3)
            SetCityDensity(3);
        else if (nCount != 0)
            SetCityDensity(2);
    } else {
        SetCityDensity(4);
    }

    if (GetCurrentGameMode_s00bf_4170() == &gGameModeCivilization) {
        void* pCityHall = pCity->GetCityHall();
        IRefCounted* pIcon = nullptr;
        if (pCityHall != nullptr)
            pIcon = (IRefCounted*)GetCityHallIcon();
        ClearCitySelection();
        ShowCityLimitToastLong();

        cGameNounManager* pNouns = NounManager_s00bf_4170();
        cCommunityEditor* pPlayer = pNouns->GetPlayerCivilization();
        if (pPlayer != this && mOneCityBadgeShown == 0 && (mpCitiesEnd - mpCitiesBegin) == 2) {
            mOneCityBadgeShown = 1;
            ClearCitySelection();
            ShowCityLimitToast();
            UpdateCityInfoPanel(this);
            uint32_t nSphere = (uint32_t)GetTerrainEditorObject();
            UpdateCityBoundaries(nSphere);
            pNouns = NounManager_s00bf_4170();
            pPlayer = pNouns->GetPlayerCivilization();
            if (pPlayer->mpCitiesBegin != pPlayer->mpCitiesEnd) {
                ClearCitySelection();
                ShowOneCityBadge();
            }
        }
    }

    mCitiesInitialized = 1;

    if (GetCurrentGameMode_s00bf_4170() != &gGameModeCivilization) {
        if (GetActivePlanetTier() != 4)
            goto done;
    }
    RefreshCityCount();

done:
    if (mMaxCityCount < (mpCitiesEnd - mpCitiesBegin))
        mMaxCityCount = (int)(mpCitiesEnd - mpCitiesBegin);
}

// @ 0x00bf45f0
void cCommunityEditor::DetachCity(cCity_s00bf_4170* pCity, int bRemoving)
{
    if (this != nullptr)
        AddRef();

    if (pCity == nullptr) {
        Release();
        return;
    }

    if (mpTrackedRefA == pCity) {
        IRefCounted* pOld = mpTrackedRefA;
        mpTrackedRefA = nullptr;
        pOld->Release();
    }
    if (mpTrackedRefB == pCity) {
        IRefCounted* pOld = mpTrackedRefB;
        mpTrackedRefB = nullptr;
        pOld->Release();
    }
    if (mpTrackedRefC == pCity) {
        IRefCounted* pOld = mpTrackedRefC;
        mpTrackedRefC = nullptr;
        pOld->Release();
    }

    if (GetCurrentGameMode_s00bf_4170() == &gGameModeCivilization && bRemoving == 0 &&
        (mpCitiesEnd - mpCitiesBegin) == 1) {
        static const int sEventIds[5] = {0, 0, 0, 0, 0};
        for (int i = 0; i < 5; ++i) {
            uint32_t nId = (uint32_t)sEventIds[i];
            uint32_t nTag = (uint32_t)(intptr_t)this->Query((void*)0x4c);
            EventLog((int)nId, 0, (int)nTag)->RemoveAllEventsOfSameType((int)nId);
        }
    }

    cCity_s00bf_4170** pSlot = mpCitiesBegin;
    while (pSlot != mpCitiesEnd && *pSlot != pCity)
        ++pSlot;
    if (pSlot != mpCitiesEnd) {
        for (cCity_s00bf_4170** pCur = pSlot; pCur + 1 != mpCitiesEnd; ++pCur)
            *pCur = pCur[1];
        --mpCitiesEnd;
    }

    ReduceCitiesForPlanet(this);

    CityAddRef(pCity);
    const void* pKey = (const void*)pCity;
    (void)pKey;
    CityRelease(pCity);

    if (mpCitiesBegin == mpCitiesEnd && GetCurrentGameMode_s00bf_4170() != &gGameModeSpace)
        RefreshCityCount();

    if (mpCitiesBegin == mpCitiesEnd && mpTrackedRefC != nullptr)
        CompanionReleaseContents(mpTrackedRefC);
    else
        RefreshCityBadges();

    if (bRemoving == 0) {
        if (mpCitiesBegin != mpCitiesEnd)
            RefreshCityStatistics(this);

        RecomputeCommunityScore(this);
        if (mpCitiesBegin == mpCitiesEnd && mpRemovedBegin != mpRemovedEnd) {
            while (mpRemovedBegin != mpRemovedEnd) {
                void* pNoun = mpRemovedEnd[-1];
                void* pTarget = nullptr;
                if (pNoun != nullptr) {
                    ((IRefCounted*)pNoun)->AddRef();
                    pTarget = (uint8_t*)pNoun + 0x5d0;
                }
                BehaviorManager()->AddRemoveObject(pTarget);
                RefreshCityStatistics((cCommunityEditor*)pNoun);
                NounManager_s00bf_4170()->RemoveNoun(pTarget);
                if (pNoun != nullptr)
                    ((IRefCounted*)pNoun)->Release();
            }
        }

        if (mpCitiesBegin == mpCitiesEnd && mBadgeToasterShown == 0) {
            ClearCitySelection();
            ShowCityLimitToast();
            UpdateCommunityCamera(this);

            if (GetCurrentGameMode_s00bf_4170() == &gGameModeSpace) {
                int nCount = GetCityHallIcon();
                for (int i = 0; i < nCount; ++i) {
                    void* pNode = GetCityHallEntry(i);
                    void* pParent = GetNodeParent(pNode);
                    if (pParent == this->Query((void*)0x4c)) {
                        RemoveCityHallEntry(i);
                        break;
                    }
                }
            }

            uint32_t msgId = 0x4b33710;
            MessageServerPost(msgId, this);
            NounManager_s00bf_4170()->RemoveNoun(this);
        }
    }

    Release();
}

// @ 0x00bf49e0
void cCommunityEditor::NotifySubEditor()
{
    if (this == nullptr)
        return;
    void* pSub = Query((void*)0xee9b2232);
    if (pSub != nullptr) {
        int bFlag = 0;
        if (GetCurrentGameMode_s00bf_4170() == &gGameModeSpace) {
            SpaceGameGet();
            bFlag = IsSpaceLevelReady() ? 1 : 0;
        }
        ((cCommunityEditor*)pSub)->DetachCity((cCity_s00bf_4170*)this, bFlag);
        return;
    }
    void* pOther = Query((void*)0x137e8e0);
    if (pOther != nullptr)
        RefreshCityStatistics((cCommunityEditor*)pOther);
}

// @ 0x00bf4a60
void SetModelTypeKey(int* pKey, const Vec3_s00bf_4170* pValue)
{
    Vec3_s00bf_4170* pSlot = ((cVector3Map*)pKey)->FindOrInsert((uint32_t)pKey);
    *pSlot = *pValue;
}

// @ 0x00bf4a90
void ResetVector3Map(cCommunityEditor* pEditor)
{
    cVector3Map* pMap = (cVector3Map*)pEditor;
    pMap->mpRoot = nullptr;
    pMap->mpHead = (int*)&pMap->mpRoot;
    pMap->mpNil = (int*)&pMap->mpRoot;
    pMap->mPad10[0] = 0;
    pMap->mCount = 0;

    for (uint32_t nKey = 0; nKey < 5; ++nKey) {
        Vec3_s00bf_4170 zero;
        zero.mX = 0.0f;
        zero.mY = 0.0f;
        zero.mZ = 0.0f;
        SetModelTypeKey((int*)nKey, &zero);
    }
    for (uint32_t nKey = 5; nKey < 18; ++nKey) {
        Vec3_s00bf_4170 zero;
        zero.mX = 0.0f;
        zero.mY = 0.0f;
        zero.mZ = 0.0f;
        SetModelTypeKey((int*)nKey, &zero);
    }
}

// @ 0x00bf4e50
void cCommunityEditor::RemoveAllCities(cCity_s00bf_4170* pCity)
{
    CityAddRef(pCity);
    int nCount = (int)(mpCitiesEnd - mpCitiesBegin);
    for (int i = 0; i < nCount; ++i)
        CityVehicleCreateHook(this);
}

// @ 0x00bf4eb0
void cCommunityEditor::RebuildCityFromTerrainSphere()
{
    cTerrainEditor* pTerrain = (cTerrainEditor*)NounManager_s00bf_4170();
    cTerrainSphere* pSphere = pTerrain->GetCurrentTerrainSphere();
    if (pSphere->mModelB == 0)
        return;

    Vec3_s00bf_4170 position;
    position.mX = (float)pSphere->mModelKind;
    position.mY = (float)pSphere->mModelA;
    position.mZ = (float)pSphere->mModelB;
    SetModelTypeKey((int*)0x99e92f05, &position);

    RemoveAllCities((cCity_s00bf_4170*)0x9c);

    Vec3_s00bf_4170 stored;
    stored.mX = (float)pSphere->mModelKind;
    stored.mY = (float)pSphere->mModelA;
    stored.mZ = (float)pSphere->mModelB;
    SetModelTypeKey((int*)0x99e92f05, &stored);
}

// @ 0x00bf4fc0
void cCommunityEditor::CreateVehicleFromTerrainSphere()
{
    cTerrainEditor* pTerrain = (cTerrainEditor*)NounManager_s00bf_4170();
    cTerrainSphere* pSphere = pTerrain->GetCurrentTerrainSphere();
    if (pSphere->mModelPosition.mZ == 0.0f)
        return;

    NounManager_s00bf_4170();
    cCity_s00bf_4170* pCity = (cCity_s00bf_4170*)GetTerrainEditorObject();
    int nSpecialty = pCity->GetVehicleSpecialty();

    uint32_t nModel;
    if (nSpecialty == 0)
        nModel = 0x7d433fad;
    else if (nSpecialty == 1)
        nModel = 0x9ad7d4aa;
    else
        nModel = 0xf670aa43;

    CreateVehicleFromModelType((cCity_s00bf_4170*)(intptr_t)nModel, &pSphere->mModelPosition);

    Vec3_s00bf_4170 stored = pSphere->mModelPosition;
    SetModelTypeKey((int*)nModel, &stored);
}

// @ 0x00bf5050
Vec3_s00bf_4170* cVector3Map::FindOrInsert(uint32_t key)
{
    int* pHeader = (int*)&mpRoot;
    int* pLower = pHeader;

    if (mpHead != nullptr) {
        int* pNode = mpHead;
        do {
            int* pNext;
            if ((uint32_t)pNode[4] < key) {
                pNext = (int*)*pNode;
            } else {
                pNext = (int*)pNode[1];
                pLower = pNode;
            }
            pNode = pNext;
        } while (pNode != nullptr);
    }

    if (pLower == pHeader || key < (uint32_t)pLower[4]) {
        Vec3_s00bf_4170 value;
        value.mX = 0.0f;
        value.mY = 0.0f;
        value.mZ = 0.0f;
        MapInsertNode(pLower, key, &value);
    }
    return (Vec3_s00bf_4170*)(pLower + 5);
}

// @ 0x00bf51d0
GonzagoTimer* TimerVec::eraseRange(GonzagoTimer* first, GonzagoTimer* last)
{
    GonzagoTimer* newEnd = (GonzagoTimer*)FUN_00bf29c0(last, m_end, first);

    for (GonzagoTimer* p = newEnd; p < m_end; ++p)
        ((void (__thiscall*)(GonzagoTimer*, int))_vt(p, 0))(p, 0);

    m_end = (GonzagoTimer*)((char*)m_end +
                            (((char*)last - (char*)first) >> 5) * -0x20);
    return first;
}

// @ 0x00bf5220
void TimerVec::insertN(GonzagoTimer* pos, unsigned count, const GonzagoTimer* value)
{
    unsigned freeSlots = (unsigned)((char*)m_cap - (char*)m_end) >> 5;

    if (freeSlots < count) {
        unsigned size    = (unsigned)((char*)m_end - (char*)m_begin) >> 5;
        unsigned newCap  = size * 2;
        if (size == 0)
            newCap = 1;
        unsigned need = size + count;
        if (need < newCap)
            need = newCap;

        GonzagoTimer* block = 0;
        if (need != 0)
            block = (GonzagoTimer*)FUN_00f473a0((int)(need << 5), "Simulator",
                                                0, 0, kAllocatorPath, 0xd1);

        GonzagoTimer* oldBegin = m_begin;
        GonzagoTimer* oldPos   = pos;
        GonzagoTimer* newMid   = (GonzagoTimer*)FUN_00bf2960(oldBegin, oldPos, block);
        FUN_00befb80(oldBegin, oldPos, block);
        FUN_00bf28f0(newMid, count, value, newMid);

        GonzagoTimer* afterInsert =
            (GonzagoTimer*)((char*)newMid + (count << 5));
        GonzagoTimer* oldEnd = m_end;
        GonzagoTimer* newEnd = (GonzagoTimer*)FUN_00bf2960(oldPos, oldEnd, afterInsert);
        FUN_00befb80(oldPos, oldEnd, afterInsert);

        if (m_begin != 0 && *(int*)((char*)m_begin - 4) != 0)
            FUN_00f47380(m_begin);

        m_end   = newEnd;
        m_begin = block;
        m_cap   = (GonzagoTimer*)((char*)block + (need << 5));
    }
    else if (count != 0) {
        GonzagoTimer local;
        local.mElapsedTimeLo = value->mElapsedTimeLo;
        local.mElapsedTimeHi = value->mElapsedTimeHi;
        local.mBaseTimeLo    = value->mBaseTimeLo;
        local.mBaseTimeHi    = value->mBaseTimeHi;
        local.mRunning       = value->mRunning;
        local.mTimeFn        = value->mTimeFn;
        local.m_refCount     = 0;
        local.m_vtable       = (void*)0x01464450;

        GonzagoTimer* oldEnd = m_end;
        unsigned tail = (unsigned)((char*)oldEnd - (char*)pos) >> 5;

        if (tail <= count) {
            unsigned extra = count - tail;
            FUN_00bf28f0(oldEnd, extra, &local, pos);
            m_end = (GonzagoTimer*)((char*)m_end + (extra << 5));
            FUN_00bf2840(&pos, pos, oldEnd, m_end, pos);
            m_end = (GonzagoTimer*)((char*)m_end + (tail << 5));
            FUN_00bf28b0(pos, oldEnd, &local);
            ((void (__thiscall*)(GonzagoTimer*))FUN_00b638b0)(&local);
            return;
        }

        unsigned countBytes = count << 5;
        GonzagoTimer* split = (GonzagoTimer*)((char*)oldEnd - countBytes);
        ((void (__cdecl*)(void*, void*, void*, void*))FUN_00bf2840)
            (&value, split, oldEnd, oldEnd);
        GonzagoTimer* oldPos = pos;
        m_end = (GonzagoTimer*)((char*)m_end + countBytes);
        FUN_00bf2a10(pos, split, oldEnd);
        FUN_00bf28b0(oldPos, (char*)oldPos + countBytes, &local);
        ((void (__thiscall*)(GonzagoTimer*))FUN_00b638b0)(&local);
    }
}

// @ 0x00bf5420
void TimerVec::insertOne(GonzagoTimer* pos, const GonzagoTimer* value)
{
    if (m_end != m_cap) {
        if (pos <= value && value < m_end)
            value = (GonzagoTimer*)((char*)value + 0x20);

        if (m_end != 0) {
            GonzagoTimer* prev = m_end - 1;
            m_end->m_vtable       = (void*)0x01465d54;
            m_end->m_refCount     = 0;
            m_end->mElapsedTimeLo = prev->mElapsedTimeLo;
            m_end->mElapsedTimeHi = prev->mElapsedTimeHi;
            m_end->mBaseTimeLo    = prev->mBaseTimeLo;
            m_end->mBaseTimeHi    = prev->mBaseTimeHi;
            m_end->mRunning       = prev->mRunning;
            m_end->mTimeFn        = prev->mTimeFn;
            m_end->m_vtable       = (void*)0x01464450;
        }

        FUN_00bf2a10(pos, (char*)m_end - 0x20, m_end);
        pos->mElapsedTimeLo = value->mElapsedTimeLo;
        pos->mElapsedTimeHi = value->mElapsedTimeHi;
        pos->mBaseTimeLo    = value->mBaseTimeLo;
        pos->mBaseTimeHi    = value->mBaseTimeHi;
        pos->mRunning       = value->mRunning;
        pos->mTimeFn        = value->mTimeFn;
        m_end = (GonzagoTimer*)((char*)m_end + 0x20);
        return;
    }

    unsigned size = (unsigned)((char*)m_end - (char*)m_begin) >> 5;
    unsigned newCap;
    if (size == 0)
        newCap = 1;
    else {
        newCap = size * 2;
        if (newCap == 0)
            newCap = 0;
    }

    GonzagoTimer* block = 0;
    if (newCap != 0)
        block = (GonzagoTimer*)FUN_00f473a0((int)(newCap << 5), "Simulator",
                                            0, 0, kAllocatorPath, 0xd1);

    GonzagoTimer* oldBegin = m_begin;
    GonzagoTimer* mid = (GonzagoTimer*)FUN_00bf2960(oldBegin, pos, block);
    FUN_00befb80(oldBegin, pos, block);

    if (mid != 0) {
        mid->m_vtable       = (void*)0x01465d54;
        mid->m_refCount     = 0;
        mid->mElapsedTimeLo = value->mElapsedTimeLo;
        mid->mElapsedTimeHi = value->mElapsedTimeHi;
        mid->mBaseTimeLo    = value->mBaseTimeLo;
        mid->mBaseTimeHi    = value->mBaseTimeHi;
        mid->mRunning       = value->mRunning;
        mid->mTimeFn        = value->mTimeFn;
        mid->m_vtable       = (void*)0x01464450;
    }

    GonzagoTimer* oldEnd = m_end;
    GonzagoTimer* newEnd =
        (GonzagoTimer*)FUN_00bf2960(pos, oldEnd, (char*)mid + 0x20);
    FUN_00befb80(pos, oldEnd, (char*)mid + 0x20);

    if (m_begin != 0 && *(int*)((char*)m_begin - 4) != 0)
        FUN_00f47380(m_begin);

    m_begin = block;
    m_end   = newEnd;
    m_cap   = (GonzagoTimer*)((char*)block + (newCap << 5));
}

// @ 0x00bf55d0
void FUN_00bf55d0()
{
    ((void (__thiscall*)(void*))FUN_00bf4a90)((void*)0x0168caf0);

    unsigned char* tree = (unsigned char*)0x0168cb0c;
    do {
        unsigned char* node = *(unsigned char**)(tree + 0x0c);
        while (node != 0) {
            unsigned char* next = *(unsigned char**)(node + 4);
            ((void (__thiscall*)(void*, void*))FUN_009a9600)(tree, *(void**)node);
            FUN_00f47380(node);
            node = next;
        }

        unsigned char* head = tree + 4;
        *(void**)(tree + 0x08) = head;
        *(void**)(tree + 0x0c) = 0;
        *(unsigned char*)(tree + 0x10) = 0;
        *(int*)(tree + 0x14) = 0;
        tree += 0x1c;
        *(void**)head = head;
    } while ((int)tree < 0x0168cb44);
}

// @ 0x00bf5630
void FeedbackSink::AddPair(void* obj)
{
    void* value = obj;

    if (obj != 0)
        ((void (__thiscall*)(void*))_vt(obj, 0))(obj);

    if (m_events.m_end < m_events.m_cap) {
        void** slot = m_events.m_end;
        m_events.m_end = slot + 1;
        if (slot != 0) {
            *slot = obj;
            if (obj != 0)
                ((void (__thiscall*)(void*))_vt(obj, 0))(obj);
        }
    }
    else {
        ((void (__thiscall*)(void*, void**, void* const&))FUN_00aea5d0)
            (&m_events, m_events.m_end, value);
    }

    if (value != 0)
        ((void (__thiscall*)(void*))_vt(value, 4))(value);

    void* entry = obj;
    void* id = ((void* (__thiscall*)(void*))_vt(this, 0x4c))(this);
    ((void (__thiscall*)(void*, void*))_vt(entry, 0x48))(entry, id);

    void* other = ((void* (__thiscall*)(void*, void*))_vt(obj, 0x0c))(obj, (void*)0x01186577);
    if (other != 0) {
        ((void (__thiscall*)(void*))_vt(other, 0xbc))(other);

        if (m_sounds.m_end < m_sounds.m_cap) {
            void** slot = m_sounds.m_end;
            m_sounds.m_end = slot + 1;
            if (slot != 0) {
                *slot = other;
                ((void (__thiscall*)(void*))_vt(other, 0xbc))(other);
            }
        }
        else {
            ((void (__thiscall*)(void*, void**, void* const&))FUN_00bab900)
                (&m_sounds, m_sounds.m_end, other);
        }

        ((void (__thiscall*)(void*))_vt(other, 0xc0))(other);
    }
}

// @ 0x00bf57b0
void* VehicleFactory::CreateVehicle(void* p2, void* p3, void* p4, void* p5, void* p6, void* p7)
{
    void* mgr = FUN_00b3d300();
    void* noun = ((void* (__thiscall*)(void*, void*))FUN_00b20c60)
                    (mgr, (void*)0x018c6de8);

    void* vehicle = 0;
    if (noun != 0) {
        vehicle = ((void* (__thiscall*)(void*, int))_vt(noun, 0x0c))(noun, 0x137e8e0);
        if (vehicle != 0)
            ((void (__thiscall*)(void*))_vt(vehicle, 0))(vehicle);
    }

    ((FeedbackSink*)this)->AddPair(vehicle);

    Vec3 pos;
    pos.x = *(float*)&p4;
    pos.y = *(float*)&p5;
    pos.z = *(float*)&p6;
    ((void (__thiscall*)(void*, void*, void*, Vec3))FUN_00ca6630)
        (vehicle, p3, p2, pos);

    void* spatial = (char*)vehicle + 0x34;
    ((void (__thiscall*)(void*, void*))_vt(spatial, 0x38))(spatial, p7);

    VehicleSnapshot snap;
    snap.m_alloc = 0;
    snap.m_pos.x = *(float*)0x0168c514;
    snap.m_pos.y = *(float*)0x0168c518;
    snap.m_pos.z = *(float*)0x0168c51c;
    snap.m_f24 = *(float*)0x01485720;
    snap.m_f70 = *(float*)0x01470f1c;
    snap.m_f74 = *(float*)0x013ec4b4;
    snap.m_f7c = *(float*)0x0146933c;
    snap.m_f80 = 0.0f;
    snap.m_i84 = 0;

    ((void (__thiscall*)(void*, VehicleSnapshot*))_vt(spatial, 0xdc))(spatial, &snap);

    if (snap.m_alloc != 0 && *(int*)((char*)snap.m_alloc - 4) != 0)
        FUN_00f47380(snap.m_alloc);

    ((void (__thiscall*)(void*, int, float))_vt(spatial, 0xc4))(spatial, 0, 0.0f);

    void* behavior = FUN_00b3d260();
    ((void (__thiscall*)(void*, void*))_vt(behavior, 0x38))
        (behavior, (char*)vehicle + 0x5d0);

    ((void (__thiscall*)(void*, void*))_vt(vehicle, 0x0c))(vehicle, (void*)0x01186577);

    if ((unsigned char)(int)p2 != 0) {
        void* planet = FUN_01021260_s00bf_51d0();
        if (planet != 0) {
            void* id = ((void* (__thiscall*)(void*))_vt(this, 0x4c))(this);
            void* planetData = ((void* (__thiscall*)(void*, void*))FUN_00c71040)
                                   (planet, id);
            if (planetData != 0) {
                void* recorder = FUN_00f473a0(0x14, "Simulator/cVehicleData", 0, 0, 0, 0);
                void* snapshot = 0;
                if (recorder != 0)
                    snapshot = ((void* (__thiscall*)(void*, void*))FUN_00ff0db0)
                                   (recorder, vehicle);

                ((void (__thiscall*)(void*, void*))FUN_00ff2d20)(planetData, snapshot);
                ((void (__thiscall*)(void*, void*))FUN_00c9eae0)(vehicle, planetData);
                ((void (__thiscall*)(void*, void*))FUN_00a110b0)(vehicle, snapshot);
            }
        }
    }

    ((void (__thiscall*)(void*))_vt(vehicle, 4))(vehicle);
    return vehicle;
}

// @ 0x00bf59d0
void CityThing::UpdateDistances()
{
    VecC pts;
    unsigned char flag;
    int count = (int)((char*)m_citiesEnd - (char*)m_citiesBegin) >> 2;

    ((VecC* (__thiscall*)(VecC*, unsigned, unsigned char*))FUN_006a46a0)
        (&pts, (unsigned)count, &flag);

    if (count > 0) {
        Vec3* dst = pts.m_data;
        for (int i = 0; i < count; ++i) {
            void* city = m_citiesBegin[i];
            void* sub = (char*)city + 0x120;
            Vec3* src = (Vec3*)((void* (__thiscall*)(void*))_vt(sub, 0x2c))(sub);
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            ++dst;
        }
    }

    void* model = FUN_00b3d350();
    void* mgr = FUN_00b3d300();
    void** civVec = (void**)((void* (__thiscall*)(void*))FUN_00b25ca0)(mgr);

    void** civIt  = (void**)*civVec;
    void** civEnd = (void**)civVec[1];

    for (; civIt != civEnd; ++civIt) {
        void* civ = *civIt;
        if (civ == this)
            continue;

        void** cityIt  = *(void***)((char*)civ + 0x9c);
        void** cityEnd = *(void***)((char*)civ + 0xa0);
        for (; cityIt != cityEnd; ++cityIt) {
            void* city = *cityIt;
            void* sub = (char*)city + 0x120;
            Vec3* src = (Vec3*)((void* (__thiscall*)(void*))_vt(sub, 0x2c))(sub);

            Vec3 cur;
            cur.x = src->x;
            cur.y = src->y;
            cur.z = src->z;

            float best = 3.402823466e38f;
            for (int i = 0; i < count; ++i) {
                float d = ((float (__thiscall*)(void*, Vec3*, Vec3*))FUN_00b81470)
                              (model, &cur, &pts.m_data[i]);
                if (d < best)
                    best = d;
            }

            ((void (__thiscall*)(void*))_vt(city, 0))(city);
            void* key = city;
            float* slot = ((float* (__thiscall*)(void*, void*))FUN_00bf5050)
                              (&m_map, &key);
            *slot = best;
            ((void (__thiscall*)(void*))_vt(city, 4))(city);
        }
    }

    if (pts.m_data != 0 && *(int*)((char*)pts.m_data - 4) != 0)
        FUN_00f47380(pts.m_data);
}

// @ 0x00bf5b90
float CityThing::GetDistance(void* key)
{
    if (key != 0)
        ((void (__thiscall*)(void*))_vt(key, 0))(key);

    void* local = key;
    float* slot = ((float* (__thiscall*)(void*, void*))FUN_00bf5050)(&m_map, &local);
    float value = *slot;

    if (key != 0)
        ((void (__thiscall*)(void*))_vt(key, 4))(key);

    return value;
}

// @ 0x00bf5be0
bool CityEventSub::OnEvent(int eventId, void* data)
{
    if (eventId == 0x1a0219e) {
        if (*(void**)((char*)data + 0x10) != 0 && *(int*)((char*)data + 8) == 4)
            FUN_00bf49e0(*(void**)((char*)data + 0x10));
    }
    else if (eventId == 0x20c089c) {
        void* comm = FUN_00b3d4a0();
        if (((unsigned char (__thiscall*)(void*))FUN_00ae9390)(comm) == 0) {
            ((void (__thiscall*)(void*))FUN_00bf0f90)((char*)this - 0x38);
            return true;
        }
    }
    else if (eventId == 0x6524f8f) {
        if (m_civ != 0) {
            int civ = ((int (__thiscall*)(void*))FUN_00bd9bf0)(m_civ);
            if (civ == (int)((char*)this - 0x38) && m_flag51 != 0 && m_soundId != -1)
                ((void (__thiscall*)(void*, int, void*))FUN_00be5be0)
                    (m_civ, m_soundId, (void*)0x0168c514);
        }

        void* old = m_civ;
        m_civ = 0;
        if (old != 0)
            ((void (__thiscall*)(void*))_vt(old, 4))(old);
        m_soundId = -1;
        return true;
    }
    return true;
}

// @ 0x00bf5cb0
void TribeAI::Update()
{
    // 1. re-check orders aimed at allied / non-hostile targets
    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
        Entity* v = *it;
        if (!Active(v)) continue;
        bool go = false;
        if (v->GetInter()->type == 1) {
            Entity* t = v->GetInter()->target;
            if (!t) continue;
            Entity* c = t->Cast(0x403df5f);
            if (!c) continue;
            int other = c->GetPlayerID();
            int self = GetPlayerID();
            if (RelationshipManager_s00bf_5cb0()->GetRelation(self, other, 1) < 2) continue;
            if (!c->GetCivOf()) continue;
            if (c->GetCivOf()->b8a == 0) v->Order(0, 0, 0);
            continue;
        }
        if (v->GetInter()->type == 2) {
            if (v->GetInter()->target) go = true;
        }
        if (!go) {
            if (v->GetInter()->type != 3) continue;
            if (!v->GetInter()->target) continue;
        }
        Entity* t = v->GetInter()->target;
        if (t) {
            Entity* city = t->Cast(0xee9b2232);
            if (city) {
                if (!city->IsDestroyed()) {
                    int other = city->GetPlayerID();
                    int self = GetPlayerID();
                    if (RelationshipManager_s00bf_5cb0()->GetRelation(self, other, 1) >= 2) {
                        if (city->GetCivilization()->b8a == 0) v->Order(0, 0, 0);
                    }
                }
            }
        }
        Entity* t2 = v->GetInter()->target;
        if (!t2) continue;
        Entity* u = t2->Cast(0x3d5c477);
        if (!u) continue;
        Entity* o = u->GetLinked();
        if (!o) continue;
        if (!o->Cast(0xee9b2232)) continue;
        Entity* o2 = u->GetLinked();
        Entity* c3 = o2 ? o2->Cast(0xee9b2232) : 0;
        if (c3->IsDestroyed()) continue;
        Entity* cc = u->GetCityOf();
        int aid = cc->GetPlayerID();
        int self = GetPlayerID();
        if (RelationshipManager_s00bf_5cb0()->IsAllied(self, aid)) continue;
        if (u->GetCityOf()->GetCivilization()->b8a == 0) v->Order(0, 0, 0);
    }

    // 2. idle vehicles: fire at hostiles that target our owner
    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
        Entity* v = *it;
        if (!Active(v)) continue;
        if (v->GetInter()->type != 0) continue;
        Entity** h = v->GetHostiles();
        Entity** hb = (Entity**)((int*)h)[0];
        Entity** he = (Entity**)((int*)h)[1];
        for (Entity** p = hb; p != he; ++p) {
            Entity* e = *p;
            if (!e) continue;
            Entity* ev = e->Cast2(0x137e8e0);
            if (!ev) continue;
            Entity* tgt = ev->pos508.GetOwnerObject();
            if (!tgt) continue;
            Entity* owner = tgt->Cast2(0x17f243b);
            if (!owner) continue;
            if (owner->GetPlayerID() == GetPlayerID() && IsValidFireTarget(&v->pos508, &ev->pos508)) {
                v->Order(ev, 1, 0);
                break;
            }
        }
    }

    // 3. occasionally pick the nearest enemy vehicle to attack
    bool lucky = sMathRandom_s00bf_5cb0.RandomUint32Uniform(20) == 0;
    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
        Entity* v = *it;
        if (!Active(v)) continue;
        if (v->GetInter()->type != 0) continue;
        if (!lucky && !v->CanReach()) continue;
        Entity* best = 0;
        float bestD = FLT_MAX;
        PairVec* empires = NounManager_s00bf_5cb0()->GetEmpires();
        for (Entity** pe = empires->begin; pe != empires->end; ++pe) {
            Entity* emp = *pe;
            for (Entity** q = emp->vecBegin; q != emp->vecEnd; ++q) {
                Entity* e = *q;
                if (!e) continue;
                Entity* tgt = e->pos508.GetOwnerObject();
                if (!tgt) continue;
                Entity* owner = tgt->Cast2(0x17f243b);
                if (!owner) continue;
                if (owner->GetPlayerID() != GetPlayerID()) continue;
                if (!IsValidFireTarget(&v->pos508, &e->pos508)) continue;
                if (!v->CanOccupyTerrain(e->pos34.GetPos())) continue;
                Vec3* a = e->pos34.GetPos();
                Vec3* b = v->pos34.GetPos();
                float dx = b->x - a->x, dy = b->y - a->y, dz = b->z - a->z;
                float d = sqrtf(dz * dz + dy * dy + dx * dx);
                if (d < bestD) { best = e; bestD = d; }
            }
        }
        if (best) {
            v->Order(best, 1, 0);
            break;
        }
    }

    // 4. now and then send a vehicle to a city of the player's empire if nothing is defending
    if (!mFlag8a) {
        if (sMathRandom_s00bf_5cb0.RandomUint32Uniform(3) == 0) {
            unsigned long long el = mTimer.GetElapsedTime();
            if (el > 120000) {
                int pe = NounManager_s00bf_5cb0()->GetPlayerEmpireOrMinus1();
                int self = GetPlayerID();
                if (RelationshipManager_s00bf_5cb0()->GetRelation(self, pe, 1) <= 1) {
                    bool defended = false;
                    int idle = 0;
                    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                        Entity* v = *it;
                        if (!Active(v)) continue;
                        if (v->GetInter()->type == 0) ++idle;
                        if (v->GetInter()->type != 2 && v->GetInter()->type != 3) continue;
                        Entity* t = v->GetInter()->target;
                        if (t) {
                            Entity* c = t->Cast(0xee9b2232);
                            if (c) {
                                if (c->pos120.IsActive()) defended = true;
                            }
                        }
                        Entity* t2 = v->GetInter()->target;
                        if (t2) {
                            Entity* u = t2->Cast(0x3d5c477);
                            if (u) {
                                Entity* o = u->GetLinked();
                                if (o) {
                                    if (o->Cast(0xee9b2232)) {
                                        Entity* o2 = u->GetLinked();
                                        Entity* c3 = o2 ? o2->Cast(0xee9b2232) : 0;
                                        if (c3->pos120.IsActive()) defended = true;
                                    }
                                }
                            }
                        }
                    }
                    if (!defended && idle > 0) {
                        Entity* best = 0;
                        int bestR = 0;
                        VecHolder* gd = NounManager_s00bf_5cb0()->GetGameDataVector((void*)FnD, (void*)FnC, (void*)FnB, (void*)FnA, 0x18c43e8);
                        int n = gd->end - gd->begin;
                        if (n > 0) {
                            for (int i = 0; i < n; ++i) {
                                Entity* e = gd->begin[i];
                                if (e->pos120.IsActive()) {
                                    int r = (int)sMathRandom_s00bf_5cb0.RandomUint32Uniform(100);
                                    if (bestR < r + 1) { best = e; bestR = r + 1; }
                                }
                            }
                            if (best) {
                                for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                                    Entity* v = *it;
                                    if (!Active(v)) continue;
                                    if (!v->CanTarget(best)) continue;
                                    if (v->GetInter()->type != 0) continue;
                                    mTimer.Restart();
                                    v->Order(best, (v->mState != 0) + 2, 0);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // 5. city C: keep two idle vehicles on it
    if (mCityC) {
        bool skip = false;
        if (mCityA) {
            if (!mFlag92) skip = true;
            else if (mCityC->GetCivOf()->b8a == 0) {
                if (mCityA->GetCivilization()->b8a != 0) skip = true;
            }
        }
        if (!skip) {
            int n = 0;
            bool done = false;
            if (mVehBegin != mVehEnd) {
                for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                    Entity* v = *it;
                    if (!Active(v)) continue;
                    if (v->GetInter()->type == 1) {
                        if (v->GetInter()->target == mCityC) ++n;
                    }
                }
                if (n > 1) done = true;
            }
            if (!done) {
                for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                    Entity* v = *it;
                    if (!Active(v)) continue;
                    if (!v->CanTargetCity(mCityC)) continue;
                    if (v->GetInter()->type != 0) continue;
                    v->Order(mCityC, 1, 0);
                    ++n;
                    if (n == 2) break;
                }
            }
        }
    } else {
        for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
            Entity* v = *it;
            if (!Active(v)) continue;
            if (v->GetInter()->type != 1) continue;
            Entity* t = v->GetInter()->target;
            if (!t) continue;
            if (t->Cast(0x403df5f)) v->Order(0, 0, 0);
        }
    }

    // 6. city A
    if (mCityA) {
        int cntA = 0, cntB = 0;
        for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
            Entity* v = *it;
            if (!v || v->mState != 0) continue;
            if (!v->CanTarget(mCityA)) continue;
            if (v->GetInter()->type == 0) ++cntA;
            else if (!mFlag92) {
                if (v->GetInter()->type == 1) {
                    Entity* t = v->GetInter()->target;
                    if (t && t->Cast(0x403df5f)) ++cntA;
                }
            }
            if (v->GetInter()->type == 2) {
                if (v->GetInter()->target == mCityA) ++cntB;
            }
        }
        int size = (int)(mListEnd - mListBegin);
        int x = GetLimit(0) - size;
        int lim = mCityA->GetCapacity() + 3;
        x = (x < lim) ? x : lim;
        int k = NounManager_s00bf_5cb0()->GetCurrentTerrainSphere()->GetKind();
        int vmax = (k == 1) ? 0xb : (k == 2) ? 0xf : 6;
        int y = vmax - 1;
        x = (y < x) ? y : x;
        int r = GetSeed()->GetValue();
        bool assign;
        if (cntA + cntB < x) {
            assign = false;
            if (mCityA->GetCivilization()->b89 != 0) {
                if (mCityA->GetCivilization()->b8e == 0) assign = true;
            }
        } else {
            assign = true;
        }
        if (assign && cntB < vmax) {
            for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                Entity* v = *it;
                if (!v || v->mState != 0) continue;
                if (!v->CanTarget(mCityA)) continue;
                bool ok = false;
                if (v->GetInter()->type == 0) ok = true;
                else if (!mFlag92) {
                    if (v->GetInter()->type == 1) {
                        Entity* t = v->GetInter()->target;
                        if (t && t->Cast(0x403df5f)) ok = true;
                    }
                }
                if (ok) {
                    v->Order(mCityA, 2, 0);
                    v->SetCount(r);
                }
            }
        }
    }

    // 7. city B
    if (mCityB) {
        int cntA = 0, cntB = 0;
        for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
            Entity* v = *it;
            if (!v || v->mState != 1) continue;
            if (!v->CanTarget(mCityB)) continue;
            if (v->GetInter()->type == 0) ++cntA;
            if (v->GetInter()->type == 3) {
                bool match = false;
                Entity* t = v->GetInter()->target;
                if (t) {
                    Entity* u = t->Cast(0x3d5c477);
                    if (u) {
                        Entity* o = u->GetLinked();
                        if (o && o->Cast(0xee9b2232)) {
                            Entity* o2 = u->GetLinked();
                            Entity* c3 = o2 ? o2->Cast(0xee9b2232) : 0;
                            if (c3 == mCityB) match = true;
                        }
                    }
                }
                if (!match) match = (v->GetInter()->target == mCityB);
                if (match) ++cntB;
            }
        }
        int size = (int)(mListEnd - mListBegin);
        int x = GetLimit(1) - size;
        int ft = (int)mCityB->GetFactor();
        int base = mCityB->GetBase();
        int lim = (base + ft) / 0x29 + 2;
        x = (x < lim) ? x : lim;
        int k = NounManager_s00bf_5cb0()->GetCurrentTerrainSphere()->GetKind();
        int vmax = (k == 1) ? 0xb : (k == 2) ? 0xf : 6;
        int y = vmax - 1;
        x = (y < x) ? y : x;
        int r = GetSeed()->GetValue();
        bool skip = false;
        if (cntA + cntB < x) {
            if (mCityB->GetCivilization()->b89 == 0) skip = true;
            else if (mCityB->GetCivilization()->b8f != 0) skip = true;
        }
        if (!skip && cntB < vmax) {
            for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                Entity* v = *it;
                if (!v || v->mState != 1) continue;
                if (!v->CanTarget(mCityB)) continue;
                if (v->GetInter()->type != 0) continue;
                v->Order(mCityB, 3, 0);
                v->SetCount(r);
            }
        }
    }

    // 8. idle vehicles: head for the best-scoring target in the list
    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
        Entity* v = *it;
        if (!Active(v)) continue;
        if (v->GetInter()->type != 0) continue;
        int n = (int)(mListEnd - mListBegin);
        Entity* best = 0;
        float bestScore = 0.0f;
        for (int i = 0; i < n; ++i) {
            Entity* o = mListBegin[i];
            if (!v->CanTarget(o)) continue;
            Vec3* pv = v->pos34.GetPos();
            Vec3* po = o->pos120.GetPos();
            float dist = PlanetModel_s00bf_5cb0()->DistanceBetweenPoints(po, pv);
            float score = (2.0f - dist / (PlanetModel_s00bf_5cb0()->GetRadius() * kRadiusScale)) * 100.0f;
            if (bestScore < score) { best = o; bestScore = score; }
        }
        if (best) {
            Vec3* a = best->pos120.GetPos();
            Vec3* b = v->pos34.GetPos();
            float dx = b->x - a->x, dy = b->y - a->y, dz = b->z - a->z;
            float d = sqrtf(dz * dz + dy * dy + dx * dx);
            if (120.0f < d) {
                Vec3 p;
                best->GetPoint(&p, v->mId);
                v->MoveTo(p, 0);
            }
        }
    }
}

// @ 0x00bf6cb0
float AI::FUN_00bf6cb0(int param_2)
{
  switch (param_2) {
  case 0: case 6: case 0xb: return 4000.0f;
  case 1: case 4: case 7: return 16000.0f;
  case 2: case 5: case 8: break;
  default: return 2000.0f;
  }
  int iVar2;
  {
    void* nm = FUN_00b3d300();
    int iVar0;
    ((ThNounMgr*)nm)->GetGameDataVector(&iVar0, (void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xacdff0, (void*)0xb1e500, 0x18c43e8);
    iVar2 = iVar0;
  }
  int local_4 = 1;
  int* piVar3 = &param_2;
  if (((PI(iVar2, 8) - PI(iVar2, 4)) >> 2) - ((PI(this, 0xa0) - PI(this, 0x9c)) >> 2) < 2) {
    piVar3 = &local_4;
  }
  return (float)*piVar3 * 12000.0f;
}

// @ 0x00bf6e80
void FUN_00bf6e80(u32* param_1, u32* param_2, u32* param_3)
{
  if (param_1 != param_2) {
    u32* dst = param_1;
    do {
      dst[0] = param_3[0];
      dst[1] = param_3[1];
      dst[2] = param_3[2];
      dst[3] = param_3[3];
      dst[2] = param_3[2];
      dst[3] = param_3[3];
      ((ThVec*)((char*)dst + 0x10))->FUN_004e4410((char*)param_3 + 0x10);  // eastl::vector<TreeItem>::operator=
      dst = (u32*)((char*)dst + 0x24);
    } while (dst != param_2);
  }
}

// @ 0x00bf6ee0
void AI::FUN_00bf6ee0()
{
  if (PB(this, 0x89) == 0) return;
  void** base = (void**)PS(this, 0x470);                 // sp_ref_vector@+0x470
  int n = (int)((char*)base[1] - (char*)base[0]) >> 2;
  if ((u32)n < 0xc) {
    int zero = 0;
    FUN_00bf4170(base, 0xc - n, &zero);                  // thiscall, 3 stack args
  } else {
    FUN_00bf5c2170(base, (char*)base[0] + 0x30, base[1]); // sp_ref_vector::erase
  }
  for (int off = 0; off < 0x30; off += 4) {
    void** slot = (void**)((char*)base[0] + off);
    void* old = *slot;
    if (old != 0) {
      *slot = 0;
      ((void(__thiscall*)(void*))(*(void***)old)[2])(old);   // slot 2 (+8)
    }
    u32 id = PU((void*)0x1469430, off);
    void* mgr = FUN_00b3d390(&id, slot);
    ((ThToolMgr*)mgr)->FUN_0104e340(slot);
    PB(*slot, 0x150) = 1;
  }
}

// @ 0x00bf6fa0
float AI::FUN_00bf6fa0(u8_s00bf_6cb0 param_2)
{
  volatile float acc = 0.0f;
  for (void** p = mListBegin; p != mListEnd; ++p) {
    int r = ((int(__thiscall*)(void*))(*(void***)*p)[0x0])(*p);
    acc += (float)r;
  }
  int iv;
  {
    void* nm = FUN_00b3d300();
    ((ThNounMgr*)nm)->GetGameDataVector(&iv, (void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
  }
  void** cur = *(void***)(iv + 4);
  void** end = *(void***)(iv + 8);
  while (cur != end) {
    void* comm = *cur;
    void* noun = ((Community*)comm)->GetNoun();
    if (noun == this) {
      acc += ((Community*)comm)->ReadPhase(param_2);
    }
    ++cur;
  }
  return acc;
}

// @ 0x00bf7050
u8_s00bf_6cb0 AI::FUN_00bf7050()
{
  int n = (PI(this, 0xa0) - PI(this, 0x9c)) >> 2;
  for (int i = 0; i < n; ++i) {
    void* obj = *(void**)(PI(this, 0x9c) + i * 4);
    int local_c[3];
    int uVar2 = ((int(__thiscall*)(void*, void*))(*(void***)obj)[0x5c / 4])(obj, local_c);
    if (FUN_00bf5720(uVar2)) return 1;
  }
  return 0;
}

// @ 0x00bf7150
int AI::FUN_00bf7150()
{
  int local_4 = 0;
  int iv;
  {
    void* nm = FUN_00b3d300();
    ((ThNounMgr*)nm)->GetGameDataVector(&iv, (void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
  }
  void** cur = *(void***)(iv + 4);
  void** end = *(void***)(iv + 8);
  if (cur != end) {
    do {
      void* e = *cur;
      int a = ((int(__thiscall*)(void*))(*(void***)e)[0x4c / 4])(e);
      int b = ((int(__thiscall*)(void*))(*(void***)this)[0x4c / 4])(this);
      if (a == b) ++local_4;
      ++cur;
    } while (cur != end);
    return local_4;
  }
  return 0;
}

// @ 0x00bf71d0
void AI::FUN_00bf71d0()
{
  u32 gm = FUN_00b5b800();
  if (gm == 0x1654c05) {
    void* planet = FUN_01021260_s00bf_6cb0();
    int iVar2 = FUN_00c70e00(planet);
    if (iVar2 == 5) return;
  }
  mTick4b4 += 1;
  if (mTick4b4 >= 6) {
    mTick4b4 -= 6;
    float f = FUN_00bf6fa0(1);
    FUN_00befd80(f * 0.1f);
  }
}

// @ 0x00bf7230
void AI::FUN_00bf7230()
{
  float fVar6 = mScore98;
  if (fVar6 > 0.0f) {
    float fVar4 = 1.0f;
    if (PB(this, 0x94) == 0 && PB(this, 0x8a) == 0) {
      if (mRadius4ac <= 2000.0f) {
        int iVar3 = ((ThObj*)this)->FUN_00bf0f40();
        if (iVar3 == 1 || FUN_00bf7050() == 0) fVar4 = 0.8f;
        else fVar4 = 0.6f;
      } else {
        fVar4 = 0.0f;
      }
    }
    float fVar5 = fVar4 * fVar6 + mRadius4ac;
    float fv4 = (fVar6 - fVar4 * fVar6) + mRadius4b0;
    fVar6 = mScore98 - fVar6;
    mRadius4ac = fVar5;
    mRadius4b0 = fv4;
    mScore98 = fVar6;
    if (PB(this, 0x89) == 0 && fVar6 < 0.0f) {
      mScore98 = (fVar5 + fVar6) + fv4;
      mRadius4ac = 0.0f;
      mRadius4b0 = 0.0f;
    }
    mFlag94 = 0;
  }
  {
    void* nm = FUN_00b3d300();
    void* sp = ((ThNounMgr*)nm)->FUN_00f67d90();
    int kind = ((ThSphere*)sp)->FUN_00c75420();
    float lim;
    if (kind == 1) lim = 9000.0f;
    else if (kind == 2) lim = 27000.0f;
    else lim = 3000.0f;
    if (mRadius4ac > lim) mRadius4ac = lim;
    if (mRadius4b0 > lim) mRadius4b0 = lim;
  }
}

// @ 0x00bf7390
void AI::FUN_00bf7390()
{
  void** p = mVehBegin;
  void** e = mVehEnd;
  if (p == e) return;
  do {
    void* veh = *p;
    if (veh != 0) {
      if (((u8_s00bf_6cb0(__thiscall*)(void*))(*(void***)veh)[0x2c / 4])(veh) == 0) {
        int a = ((int(__thiscall*)(void*))(*(void***)veh)[0x4c / 4])(veh);
        int b = ((int(__thiscall*)(void*))(*(void***)this)[0x4c / 4])(this);
        if (a == b && PI(veh, 0xb1c) == 0) {
          void* sp = ((ThVehl*)veh)->FUN_00ca71d0();
          if (PI(sp, 0x10) != 7) {
            void* sub = PS(veh, 0x34);
            u32 u = ((int(__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
            void* pm = FUN_00b3d350(u);
            if (FUN_00b7e3e0(pm, u) == 0) {
              u32 u2 = ((int(__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
              void* pm2 = FUN_00b3d350(u2);
              int cont = FUN_00b88590(pm2, u2);
              void* pm3 = FUN_00b3d350(0);
              if (PB((void*)((char*)0 + cont + PI(pm3, 0x64)), 0) != 0) {
                u32 u3 = ((int(__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
                if (FUN_00bf5720(u3) == 0) {
                  u32 u4 = ((int(__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
                  if (FUN_00bf70b0(u4) == 0) {
                    FUN_00caa610(veh, 1);
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
    ++p;
  } while (p != e);
}

// @ 0x00bf74a0
u32 AI::FUN_00bf74a0()
{
  u32 n = (PU(this, 0xa0) - PU(this, 0x9c)) & 0xfffffffc;
  if ((int)n <= 4) return n;
  void* obj = *(void**)PS(this, 0x9c);
  if (obj == 0) return (u32)(uintptr_t)obj;
  if (PB(this, 0x8a) != 0) return (u32)(uintptr_t)obj;
  void* nm = FUN_00b3d300();
  void* civ = ((ThNounMgr*)nm)->GetPlayerCivilization();
  if (civ == 0) return 0;
  if (PB(civ, 0x8d) == 0) return (u32)(uintptr_t)civ;
  void* nm2 = FUN_00b3d300();
  int emp = FUN_00b1f9d0();
  u32 id = ((u32(__thiscall*)(void*, int))(*(void***)this)[0x4c / 4])(this, emp);
  void* rm = FUN_00b3d2c0(id);
  u8_s00bf_6cb0 r = (u8_s00bf_6cb0)FUN_00ae2e20(rm, id);
  if (r != 0) return (u32)r;
  {
    void* nm3 = FUN_00b3d300();
    int emp2 = FUN_00b1f9d0();
    u32 id2 = ((u32(__thiscall*)(void*, int))(*(void***)this)[0x4c / 4])(this, emp2);
    void* rm2 = FUN_00b3d2c0(id2);
    int k = FUN_00d00a70(rm2, id2);
    if (k == 4) return 4;
  }
  u32 fv1 = (u32)(i32)PF(civ, 0x98);              // cvttss2si ecx,[ebp+0x98]
  int cnt1 = (PI(civ, 0xa0) - PI(civ, 0x9c)) >> 2;
  int cnt2 = (PI(this, 0xa0) - PI(this, 0x9c)) >> 2;
  u32 r1 = ((u32(__thiscall*)(void*, int))(*(void***)0x1601760)[0])((void*)0x1601760, 5);
  u32 r2 = ((u32(__thiscall*)(void*, int))(*(void***)0x1601760)[0])((void*)0x1601760, 5);
  float fv2 = PF(civ, 0x98);
  int n1 = FUN_00bf7150();
  int half = n1 / 2;
  int n2 = FUN_00bf7150();
  int d10 = (int)fv2 / 10 - 200;
  int lim = (n2 + half + (int)r2 + (int)r1 + cnt2 + cnt1) * 200 + d10;
  int t18 = (int)fv1;
  if (lim < t18) t18 = lim;
  int round = t18 / 100 * 100;                      // MSVC emits imul 0x51eb851f; sar 5
  if (round < 100) return (u32)t18 * 0x51eb851f;    // low 32 bits, as the original returns eax
  {
    u32 hiw;
    u32 el = FUN_00bc3190(PS(this, 0x1e8), &hiw);
    if (hiw == 0 && el <= 0x11170) return el;
  }
  void* cm = FUN_00b3d4a0();
  if (FUN_00ae9390_s00bf_6cb0() != 0) { FUN_00bc3130(PS(this, 0x1e8)); return 0; }
  int span = 1;
  int mode = ((ThObj*)civ)->FUN_00bf0f40();
  if (mode == 0) span = 0x10;
  else if (mode == 1) span = 8;
  else if (mode == 2) span = 0xc;
  {
    void* nm4 = FUN_00b3d300();
    void* sp = ((ThNounMgr*)nm4)->FUN_00f67d90();
    int kind = ((ThSphere*)sp)->FUN_00c75420();
    if (kind == 0) { span = span * 2; span = span * 2; }
    else if (kind == 1) span = span * 3;
    else if (kind == 2) { span = span * 2; }
  }
  u32 roll = ((u32(__thiscall*)(void*, int))(*(void***)0x1601760)[0])((void*)0x1601760, span);
  if (roll == 0) {
    void* cm2 = FUN_00b3d4a0();
    int gm = *(int*)0x169d3c8;
    FUN_00cfe7a0(0, round);
    void* planet = FUN_01021260_s00bf_6cb0();
    void* ctx = FUN_00ce6950(*(void**)PS(planet, 0x13c), 0xdbf385bf, 0x6eeceef0, 0);
    FUN_00aeb760(cm2, ctx, ctx, 0xdbf385bf, 0x6eeceef0, 0);
  }
  FUN_00bc3130(PS(this, 0x1e8));
  return 0;
}

// @ 0x00bf7730
int AI::FUN_00bf7730(int param_2)
{
  float fVar1 = FUN_00bf6cb0(param_2);
  if (fVar1 <= mScore98) return 1;
  return 0;
}

// @ 0x00bf7760
void AI::FUN_00bf7760(u32 param_2)
{
  void** vec = (void**)this;
  void* begin = vec[0];
  void* end = vec[1];
  int count = (int)((char*)end - (char*)begin) >> 5;
  if ((u32)count < param_2) {
    struct Timer20 { u32 w[8]; } local_20;      // 0x20-byte cGonzagoTimer (no /GS cookie)
    ((ThTimer*)&local_20)->FUN_00b63890();
    ((ThVec2*)this)->FUN_00bf5220(end, param_2 - count, &local_20);
    ((ThTimer*)&local_20)->FUN_00b638b0();
    return;
  }
  ((ThVec2*)this)->FUN_00bf51d0((char*)begin + param_2 * 0x20, end);
}

// @ 0x00bf77d0
void AI::FUN_00bf77d0(void* param_2)
{
  ((ThVec2*)this)->FUN_00bf51d0(*(void**)param_2, *((void**)param_2 + 1));
  u32 count = 0;
  void* p0 = (void*)((int(__thiscall*)(void*))(*(void***)param_2)[0x20 / 4])(param_2);
  void* out = (void*)((int(__thiscall*)(void*))(*(void***)p0)[0x18 / 4])(p0);
  FUN_0093a780(out, (int)&count, 1, 0);
  ((ThVec2*)this)->FUN_00bf40d0((int)count);
  u32 i = 0;
  if (count != 0) {
    do {
      struct Timer20 { u32 w[8]; } t;              // 0x20-byte cGonzagoTimer (no /GS cookie)
      ((ThTimer*)&t)->FUN_00b63890();
      ((ThTimer*)&t)->FUN_00b63930(param_2);
      void** base = (void**)PS(this, 0);
      void* dst = base[1];
      if (dst < base[2]) {
        base[1] = (char*)dst + 0x20;
        if (dst != 0) {
          u32* d = (u32*)dst;
          d[0] = 0x1465d54;
          d[1] = 0;
          d[2] = PU(&t, 0);
          d[3] = PU(&t, 4);
          d[4] = PU(&t, 8);
          d[5] = PU(&t, 0xc);
          PB(d, 0x18) = PB(&t, 0x18);
          d[7] = PU(&t, 0x1c);
          d[0] = 0x1464450;
        }
      } else {
        ((ThVec2*)this)->FUN_00bf5420(&t);
      }
      ((ThTimer*)&t)->FUN_00b638b0();
      ++i;
    } while (i < count);
  }
  ((void(__thiscall*)(void*))(*(void***)param_2)[0x1c / 4])(param_2);
}

// @ 0x00bf78d0
cCivilization_s00bf_78d0::cCivilization_s00bf_78d0()
: m88(0), m89(0), m8A(0), m8B(0), m8C(0), m8D(0), m8E(0), m8F(0), m90(0), m91(0),
      m92(1), m93(1), m94(1), m98(0.0f),
      mD0(0),
      m268(0), m26C(0), m270(0),
      mp278(gEmptyString16), mp27C(gEmptyString16), mp280(gEmptyString16b),
      mp288(gEmptyString16), mp28C(gEmptyString16), mp290(gEmptyString16b),
      m298(1), m29C(-1), m2A0(-1), m2A4(0), m2A8(0),
      mF3(0), mF4(0), mF5(0), mF6(0), mF7(0), mF8(0),
      mp42C(0), m430(0), m431(0),
      m434(-1), m438(0), m43C(-1), m440(0), m444(0), m448(0.0f),
      m44C(0), m450(-1), m454(0), m458(0), m45C(0), m460(0),
      mp464(0), mp468(0), mp470(0), mp474(0), mp478(0),
      m484(0), m488(0), m48C(0), mp4A4(0), m4A8(-1), m4AC(0.0f), m4B0(0.0f),
      m4B4(0), m4B8(0), m4C0(0), m4C4(0), m4C8(0), m4CC(0), m4D0(0)
{
    for (int i = 0; i < 12; ++i)
        mTimers[i].Start();

    void* p = EASTLAlloc(0x18, "Simulator", 0, 0, 0, 0);
    mp42C = p ? FUN_01062ee0(p) : 0;

    m484 = 0;
    m488 = 0;
    m48C = 0;
    mSuperTimers.resize(12);
}

// @ 0x00bf7d80
void cCivilization_s00bf_78d0::RemoveOwner()
{
    IMessageListener* listener = (IMessageListener*)((char*)this + 0x38);
    ((cMessageServer*)MessageServer())->m2c(listener, 0x1a0219e, 0xffffd8f1);
    listener = (IMessageListener*)((char*)this + 0x38);
    ((cMessageServer*)MessageServer())->m2c(listener, 0x20c089c, 0xffffd8f1);
    listener = (IMessageListener*)((char*)this + 0x38);
    ((cMessageServer*)MessageServer())->m2c(listener, 0x6524f8f, 0xffffd8f1);

    mD4Vec.erase(mD4Vec.mpBegin, mD4Vec.mpEnd);
    mp2AC.Set(0);
    mF1.Set(0);
    mF2.Set(0);
    while (mCities.mpBegin != mCities.mpEnd) {
        cCity_s00bf_78d0* city = mCities.mpEnd[-1];
        if (city) city->AddRef();
        FUN_00bf45f0(city, 1);
        ((cGameNounManager_s00bf_78d0*)SP_NounManager())->RemoveNoun(city);
        if (city) city->Release();
    }
    mp274.Set(0);
    while (mUnits.mpBegin != mUnits.mpEnd) {
        cGameData_s00bf_78d0* unit = (cGameData_s00bf_78d0*)mUnits.mpEnd[-1];
        void* behavior = 0;
        if (unit) {
            unit->AddRef();
            behavior = (char*)unit + 0x5d0;
        }
        ((BehaviorManager_s00bf_78d0*)SP_BehaviorManager())->b3c(behavior);
        FUN_00bf3b50(unit);
        ((cGameNounManager_s00bf_78d0*)SP_NounManager())->RemoveNoun(unit);
        if (unit) unit->Release();
    }
    mD4Vec.erase(mD4Vec.mpBegin, mD4Vec.mpEnd);

    void* pNounManager = SP_NounManager();
    int owner = GetPoliticalID();
    cGameDataVector* v1 = ((cGameNounManager_s00bf_78d0*)pNounManager)->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00bf6d80,
        (void*)FUN_00b1e500, (void*)0x3d5c325);

    TempVec tmp1;
    tmp1.FUN_00b93c60((int)(v1->mpEnd - v1->mpBegin), (char*)v1 + 0x10);
    FUN_00829110(&tmp1, v1->mpBegin, v1->mpEnd, tmp1.mpEnd, tmp1.mpBegin);
    for (cGameData_s00bf_78d0** it = (cGameData_s00bf_78d0**)tmp1.mpBegin; it != (cGameData_s00bf_78d0**)tmp1.mpEnd; ++it) {
        if ((*it)->FUN_00bd7c60(owner))
            (*it)->FUN_00be10d0();
    }

    cGameDataVector* v2 = ((cGameNounManager_s00bf_78d0*)pNounManager)->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00ae5ea0,
        (void*)FUN_00b1e500, (void*)0x403df5c);
    int n = (int)(v2->mpEnd - v2->mpBegin);
    cCommunity** arr;
    if (n == 0) {
        arr = 0;
    } else {
        arr = (cCommunity**)EASTLAlloc(n * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    TempVec tmp2;
    FUN_00829110(&tmp2, v2->mpBegin, v2->mpEnd, arr, tmp1.mpBegin);
    for (cCommunity** it = arr; it != (cCommunity**)tmp2.mpBegin; ++it) {
        cCommunity* item = *it;
        if (item->GetPoliticalID() == owner)
            item->FUN_00bff750();
        if ((int)item->m214 == owner)
            item->Deactivate();
    }

    ((Base3C*)((char*)this + 0x3c))->FUN_00b6ee10();
    ((cGameNounManager_s00bf_78d0*)SP_NounManager())->FUN_00b21410(this);
    mp468 = 0;
    mp464 = 0;

    for (cCommunity** it = arr; it != (cCommunity**)tmp2.mpBegin; ++it) {
        if (*it) (*it)->Release();
    }
    if (arr != 0 && ((int*)arr)[-1] != 0)
        operator_delete(arr);
    for (cGameData_s00bf_78d0** it = (cGameData_s00bf_78d0**)tmp1.mpBegin; it != (cGameData_s00bf_78d0**)tmp1.mpEnd; ++it) {
        if (*it) (*it)->Release();
    }
    if (tmp1.mpBegin != 0 && ((int*)tmp1.mpBegin)[-1] != 0)
        operator_delete(tmp1.mpBegin);
}

// @ 0x00bf8140
char cCivilization_s00bf_78d0::cGameData_func3Ch(int param)
{
    char result = cGameData_s00bf_78d0::cGameData_func3Ch(param);
    FUN_00bf23d0();
    RebuildToolPages();
    return result;
}

// @ 0x00bf8170
void cCivilization_s00bf_78d0::FUN_00bf8170(int ownerId, char playerOwned, int key, char flag)
{
    cGameNounManager_s00bf_78d0* pNounManager = (cGameNounManager_s00bf_78d0*)SP_NounManager();
    pNounManager->GetCivilizationList();
    pNounManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
        (void*)FUN_00acdff0, (void*)FUN_00b1e500, &DAT_018c43e8);

    if (m88)
        return;
    m88 = 1;
    m89 = playerOwned;
    if (GetCurrentGameMode_s00bf_78d0() == &DAT_01654c04)
        m8A = (m89 == 0);
    else
        m8A = 0;

    IMessageListener* listener = (IMessageListener*)((char*)this + 0x38);
    ((cMessageServer*)MessageServer())->m20(listener, 0x1a0219e);
    if (playerOwned)
        ((cMessageServer*)MessageServer())->m20(listener, 0x6524f8f);
    ((Base3C*)((char*)this + 0x3c))->FUN_00c2e4e0();

    if (key == 0x53dbcf2 && playerOwned) {
        m40 = 0x53dbcf1;
        Vec3* p = (Vec3*)FUN_00b6f0c0(0x53dbcf1);
        mC4 = *p;
        Vec3 tmp = { mC4.x, mC4.y, mC4.z };
        m60 = tmp;
    } else {
        int k = (key == 0x53dbcf2) ? FUN_00b6e050() : key;
        m40 = k;
        Vec3* p = (Vec3*)FUN_00b6f0c0(k);
        mC4 = *p;
    }

    SetPoliticalID(ownerId);
    if (!playerOwned) {
        if (GetCurrentGameMode_s00bf_78d0() != &DAT_01654c05) {
            if (FUN_01021260_s00bf_78d0() == 0
                || ((PlanetStub*)FUN_01021260_s00bf_78d0())->m13C != (int)FUN_01021370()) {
                DAT_0156f898 = 1;
                m6C.FUN_00bf3460(&DAT_0168cb0c);
            } else {
                int index;
                if (flag && ((SomeAE*)FUN_00b26930_s00bf_78d0())->FUN_00ae3600()) {
                    index = 1;
                    DAT_0156f898 = 1;
                } else {
                    index = DAT_0156f898++;
                }
                m6C.FUN_00bf4350(DAT_0168caf0 + index * 0x1c);
            }
            if (DAT_0156f898 == 3)
                DAT_0156f898 = 1;
        }
    } else {
        m6C.FUN_00bf3460(&DAT_0168caf0);
        FUN_00bf4eb0();
    }

    if (ownerId == -1)
        ownerId = ((StarManager*)FUN_00b3d2a0(0))->FUN_00ba6630();

    ((cMessageServer*)MessageServer())->m20(listener, 0x20c089c);
    if (pNounManager->ClassifyById(ownerId) == 5) {
        Empire* empire = (Empire*)((StarManager*)FUN_00b3d2a0(ownerId))->GetEmpireByID();
        mp274.Set((cGameData_s00bf_78d0*)empire->FUN_00bce4c0());
    }
    if (pNounManager->ClassifyById(ownerId) <= 4)
        pNounManager->FUN_00b23560(this);
    RebuildToolPages();
}

// @ 0x00bf8440
void cCivilization_s00bf_78d0::FUN_00bf8440()
{
    if (m89) {
        TerrainSphere* sphere =
            (TerrainSphere*)((cGameNounManager_s00bf_78d0*)SP_NounManager())->GetCurrentTerrainSphere();
        if (sphere->FUN_00c75420() <= 0)
            return;
    }

    cGonzagoTimer* pTimer = (cGonzagoTimer*)((char*)this + 0x248);
    if (pTimer->GetElapsedTime() <= 60000)
        return;

    cCivilization_s00bf_78d0* oldSelected = mp46C.mpObject;
    mp46C.Set(0);

    cCivilization_s00bf_78d0* best = 0;
    float bestScore = 0.0f;

    if (mCities.mpEnd - mCities.mpBegin > 1) {
        cCivList* list = ((cGameNounManager_s00bf_78d0*)SP_NounManager())->GetCivilizationList();
        cCivilization_s00bf_78d0** it = list->mpBegin;
        cCivilization_s00bf_78d0** end = list->mpEnd;
        if (it != end) {
            do {
                cCivilization_s00bf_78d0* other = *it;
                if (other != this && other->m8A == 0 && other->m89 == 0) {
                    int myId = GetPoliticalID();
                    int hisId = other->GetPoliticalID();
                    if (((cRelationshipManager*)SP_RelationshipManager())->FUN_00d00a70(hisId, myId, 1) < 4
                        && other->mCities.mpEnd - other->mCities.mpBegin > 1) {
                        float score = -((cRelationshipManager*)SP_RelationshipManager())
                                            ->CalculateRelationshipPersonality(other, this);
                        score += (float)(other->mCities.mpEnd - other->mCities.mpBegin) * 2.0f;
                        score += (float)other->CommunityScoreSum() * 0.5f;
                        int count = (int)(other->mCities.mpEnd - other->mCities.mpBegin);
                        for (int i = 0; i < count; ++i) {
                            cCity_s00bf_78d0* city = other->mCities.mpBegin[i];
                            if (city_on_continent(city->GetContinent(-1))) {
                                if (city->m519) {
                                    if (FUN_00bf0f40() == 1)
                                        score += 0.75f;
                                    else
                                        score += 3.0f;
                                } else {
                                    if (FUN_00bf0f40() == 1)
                                        score += 1.0f;
                                    else
                                        score += 4.0f;
                                }
                            }
                        }
                        if (oldSelected == other)
                            score += 5.0f;
                        if (score > bestScore) {
                            best = other;
                            bestScore = score;
                        }
                    }
                }
                ++it;
            } while (it != end);
        }
    }

    mp46C.Set(best);
    pTimer->Restart();
}

// @ 0x00bfb020
void Game::Tick()
{
    Entity_s00bf_b020* u;
    Entity_s00bf_b020** end = mUfoEnd;
    Entity_s00bf_b020** it = mUfoBegin;
    if (mpTargetCity) {
        for (; it != end; ++it) {
            u = *it;
            if (u && u->mState == 2 && u->GetInter()->type == 0xb) {
                if (u->GetInter()->target == mpTargetCity)
                    goto checkTimer;
            }
        }
        for (it = mUfoBegin, end = mUfoEnd; it != end; ++it) {
            u = *it;
            if (u && u->mState == 2 && u->CanTargetCity(mpTargetCity) && u->GetInter()->type != 0xb) {
                int n = (int)(mCitiesEnd - mCitiesBegin) * 600 + 0x578;
                float nf = (float)n;
                if ((mpTargetCity->FUN_00bfdea0() + 1.0f) * 0.5f * nf <= GetMoney()) {
                    u->Order(mpTargetCity, 0xb, 0);
                    break;
                }
            }
        }
    } else {
        for (; it != end; ++it) {
            u = *it;
            if (u && u->mState == 2 && u->GetInter()->type == 0xb)
                u->Order(0, 0, 0);
        }
    }

checkTimer:
    if (mTimer.GetElapsedTime() > 60000ull) {
        if (SpaceTelemetry_Add(2) > 0) {
            PlanetMdl_s00bf_b020* pm = PlanetModel_s00bf_b020();
            Entity_s00bf_b020* best = 0;
            int bestScore = 0;
            Entity_s00bf_b020** cit = mCitiesBegin;
            Entity_s00bf_b020** cend = mCitiesEnd;
            for (; cit != cend; ++cit) {
                Entity_s00bf_b020* city = *cit;
                if (city->GetVehicleSpecialty() == 2) {
                    int score = sMathRandom_s00bf_b020.RandomUint32Uniform(100);
                    PairVec_s00bf_b020* emp = NounManager_s00bf_b020()->GetEmpires();
                    Game** e = emp->begin;
                    Game** eEnd = emp->end;
                    for (; e != eEnd; ++e) {
                        Game* g = *e;
                        if (g != this) {
                            Entity_s00bf_b020** c = g->mCitiesBegin;
                            Entity_s00bf_b020** ce = g->mCitiesEnd;
                            for (; c != ce; ++c) {
                                if (*c != city && (*c)->FUN_00bd9260(city))
                                    score += 10;
                            }
                        }
                    }
                    if (score > bestScore) {
                        best = city;
                        bestScore = score;
                    }
                }
            }
            if (best) {
                int same = 0;
                int contin = 0;
                int total = 0;
                PairVec_s00bf_b020* emp = NounManager_s00bf_b020()->GetEmpires();
                Game** eit = emp->begin;
                Game** eend = emp->end;
                for (; eit != eend; ++eit) {
                    Game* g = *eit;
                    if (g == this)
                        continue;
                    Entity_s00bf_b020** c = g->mCitiesBegin;
                    Entity_s00bf_b020** ce = g->mCitiesEnd;
                    for (; c != ce; ++c) {
                        Entity_s00bf_b020* c2 = *c;
                        if (c2->FUN_00bd9260(best) || g_Rel.FUN_00ceee30(c2, this) == 1.0f) {
                            if (c2->FUN_00bd8210() == best->FUN_00bd8210())
                                ++same;
                            Vec3* p1 = c2->FUN_00fa0e00();
                            if (p1->x != g_ZeroVec.x || p1->y != g_ZeroVec.y || p1->z != g_ZeroVec.z) {
                                Vec3* p2 = best->FUN_00fa0e00();
                                if (p2->x != g_ZeroVec.x || p2->y != g_ZeroVec.y || p2->z != g_ZeroVec.z) {
                                    int k1 = pm->GetContinent(c2->FUN_00fa0e00());
                                    int k2 = pm->GetContinent(best->FUN_00fa0e00());
                                    if (k1 == k2)
                                        ++contin;
                                }
                            }
                            ++total;
                        }
                    }
                }
                if (total > 0 && best->FUN_00bdb930(2, 2)) {
                    float cost = FUN_00bf2170(2, 2);
                    if (mBudget < cost)
                        goto restart;
                    Buy(best, 2, cost);
                } else if (contin > same && best->FUN_00bdb930(2, 1)) {
                    float cost = FUN_00bf2170(2, 1);
                    if (mBudget < cost)
                        goto restart;
                    Buy(best, 1, cost);
                } else if (same > 0 && best->FUN_00bdb930(2, 0)) {
                    float cost = FUN_00bf2170(2, 0);
                    if (mBudget < cost)
                        goto restart;
                    Buy(best, 0, cost);
                }
            }
        }
restart:
        mTimer.Restart();
    }

    // Idle UFOs: pick a (own city, rival city) pair to attack.
    {
        Entity_s00bf_b020** ue = mUfoEnd;
        for (Entity_s00bf_b020** ui = mUfoBegin; ui != ue; ++ui) {
            u = *ui;
            if (u && u->mState == 2 && u->GetInter()->type == 0) {
                Entity_s00bf_b020* bestA = 0;
                Entity_s00bf_b020* bestB = 0;
                int bestScore = 0;
                Entity_s00bf_b020** cit = mCitiesBegin;
                Entity_s00bf_b020** cend = mCitiesEnd;
                for (; cit != cend; ++cit) {
                    Entity_s00bf_b020* city = *cit;
                    if (u->CanTarget(city)) {
                        PairVec_s00bf_b020* emp = NounManager_s00bf_b020()->GetEmpires();
                        Game** eit = emp->begin;
                        Game** eend = emp->end;
                        for (; eit != eend; ++eit) {
                            Game* g = *eit;
                            if (g == this)
                                continue;
                            Entity_s00bf_b020** c = g->mCitiesBegin;
                            Entity_s00bf_b020** ce = g->mCitiesEnd;
                            for (; c != ce; ++c) {
                                Entity_s00bf_b020* c2 = *c;
                                if (u->CanTarget(c2)) {
                                    if (c2->FUN_00bd9260(city) || g_Rel.FUN_00ceee30(c2, this) == 1.0f) {
                                        int score = sMathRandom_s00bf_b020.RandomUint32Uniform(100);
                                        if (c2->FUN_00bd9260(city))
                                            score += 10;
                                        if (score > bestScore) {
                                            bestA = city;
                                            bestB = c2;
                                            bestScore = score;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (bestA && bestB) {
                    if (bestB->FUN_00bd9260(bestA))
                        u->Order(bestB, 5, 0);
                    else
                        u->Order(bestB, 9, 0);
                }
            }
        }
    }

    // Still-idle UFOs: fly toward the nearest own city when it is far away.
    {
        Entity_s00bf_b020** ue = mUfoEnd;
        for (Entity_s00bf_b020** ui = mUfoBegin; ui != ue; ++ui) {
            u = *ui;
            if (u && u->mState == 2 && u->GetInter()->type == 0) {
                int n = (int)(mCitiesEnd - mCitiesBegin);
                Entity_s00bf_b020* bestC = 0;
                float bestScore = 0.0f;
                for (int i = 0; i < n; ++i) {
                    Entity_s00bf_b020* c = mCitiesBegin[i];
                    if (u->CanTarget(c)) {
                        Vec3* pu = u->pos34.GetPos();
                        Vec3* pc = c->pos120.GetPos();
                        float d = PlanetModel_s00bf_b020()->DistanceBetweenPoints(pc, pu);
                        float score = (2.0f - d / (PlanetModel_s00bf_b020()->GetRadius() * kRadiusScale)) * 100.0f;
                        if (score > bestScore) {
                            bestC = c;
                            bestScore = score;
                        }
                    }
                }
                if (bestC) {
                    Vec3* pc = bestC->pos120.GetPos();
                    Vec3* pu = u->pos34.GetPos();
                    float dx = pu->x - pc->x;
                    float dy = pu->y - pc->y;
                    float dz = pu->z - pc->z;
                    float dist = (float)sqrt((dz * dz + dy * dy) + dx * dx);
                    if (120.0f < dist) {
                        Vec3 pt;
                        bestC->GetPoint(&pt, u->mId);
                        u->MoveTo(pt, 0);
                    }
                }
            }
        }
    }
}

// @ 0x00bfb930
void Civ_s00bf_b020::SubTick1()
{
    if (GetActivePlanet()->GetToolMode() != 5)
        return;

    int n = (int)(mCitiesEnd - mCitiesBegin);
    if (n == 0)
        return;

    Entity_s00bf_b020* city = mCitiesBegin[sMathRandom_s00bf_b020.RandomUint32Uniform((unsigned)n)];

    // FUN_00bf2f00(this, 2), inlined by the original compiler.
    int limit;
    int total = 0;
    {
        Entity_s00bf_b020** it = mCitiesBegin;
        Entity_s00bf_b020** end = mCitiesEnd;
        if (it != end)
        {
            limit = 0xf;
            do
            {
                int count = (it[0]->FUN_00bd9b60() + 1) / 2;
                total += eastl::min(3, count);
                ++it;
            } while (it != end);
        }
    }
    int cap = eastl::min(total, limit);

    Entity_s00bf_b020** v = mVehiclesBegin;
    Entity_s00bf_b020** vend = mVehiclesEnd;
    int used = 0;
    for (; v != vend; ++v)
    {
        Entity_s00bf_b020* e = *v;
        if (e->mState == 2 && e->mId == 2)
            ++used;
    }

    Key pos;
    int index;
    if (cap - used > 0 && city->FUN_00bd9b60() > 0)
    {
        pos = *mHelper.GetOrCreatePosition(0x2090a11b);
        if (pos.a == 0)
        {
            mHelper.BuildConstraints(0x2090a11b);
            pos = *mHelper.GetOrCreatePosition(0x2090a11b);
        }
        index = 2;
    }
    else
    {
        v = mVehiclesBegin;
        vend = mVehiclesEnd;
        used = 0;
        for (; v != vend; ++v)
        {
            Entity_s00bf_b020* e = *v;
            if (e->mState == 2 && e->mId == 0)
                ++used;
        }
        if (FUN_00bf2f00(0) - used > 0)
        {
            pos = *mHelper.GetOrCreatePosition((int)0xbc1041e6u);
            if (pos.a == 0)
            {
                mHelper.BuildConstraints((int)0xbc1041e6u);
                pos = *mHelper.GetOrCreatePosition((int)0xbc1041e6u);
            }
            index = 0;
        }
        else
        {
            v = mVehiclesBegin;
            vend = mVehiclesEnd;
            used = 0;
            for (; v != vend; ++v)
            {
                Entity_s00bf_b020* e = *v;
                if (e->mState == 2 && e->mId == 1)
                    ++used;
            }
            int count = FUN_00bf2f00(1);
            int remaining = count - used;
            Vec3* p = city->FUN_00fa0e00();
            bool nonZero = p->x != g_ZeroVec.x || p->y != g_ZeroVec.y
                        || p->z != g_ZeroVec.z;
            if (!(remaining > 0 && nonZero))
                return;
            pos = *mHelper.GetOrCreatePosition((int)0xc15695dau);
            if (pos.a == 0)
            {
                mHelper.BuildConstraints((int)0xc15695dau);
                pos = *mHelper.GetOrCreatePosition((int)0xc15695dau);
            }
            index = 1;
        }
    }
    city->FUN_00bddda0(2, index, pos, true)->SetJustEyeCandy(true);
}

// @ 0x00bfbbf0
void Civ_s00bf_bbf0::Update()
{
    if (GetCurrentGameMode_s00bf_bbf0() == 0x1654c05)
        SubTick1();
    SubTick2();
    SubTick3();
    SubTick4();

    if (this == NounManager_s00bf_bbf0()->GetPlayerCivilization()) {
        // The player's own civ: sometimes buy a vehicle for the first city.
        if (GetCurrentGameMode_s00bf_bbf0() != 0x1654c05 && sMathRandom_s00bf_bbf0.RandomUint32Uniform(10) == 0) {
            if (NounManager_s00bf_bbf0()->GetCurrentTerrainSphere()->GetKind() <= 0
                && ((int)mVehiclesEnd - (int)mVehiclesBegin & ~3) == 0
                && GetMoney() < 1000.0f
                && GetFloat6fa0(0) == 0.0f) {
                City* city = *mCitiesBegin;
                if (city) {
                    int spec = Lookup_c9e6d0(city->GetVehicleSpecialty(), 0);
                    Triple* color = mCultureSet.LookupColor(spec);
                    city->SetupVehicle(city->GetVehicleSpecialty(), 0, *color,
                                       GetCurrentGameMode_s00bf_bbf0() == 0x1654c05);
                }
            }
        }
    } else {
        PairVec_s00bf_bbf0* civs = NounManager_s00bf_bbf0()->GetCivilizations();
        NounMgr_s00bf_bbf0* nm = NounManager_s00bf_bbf0();
        GdVec& gd = nm->GetGameDataVector(FnD, FnC, FnB, FnA, 0x18c43e8)->vec;
        int nGameData = (int)(gd.end - gd.begin);
        int nCivs = (int)(civs->end - civs->begin);
        for (int i = 0; i < nCivs; i++) {
            Civ_s00bf_bbf0* other = civs->begin[i];
            if (other != this) {
                int otherId = other->GetPoliticalID();
                int myId = GetPoliticalID();
                if (RelationshipManager_s00bf_bbf0()->GetRelation(myId, otherId, 1) <= 1) {
                    for (int j = 0; j < nGameData; j++) {
                        GameData* item = gd.begin[j];
                        if (item->GetPoliticalID() == GetPoliticalID())
                            item->AddRelated(other->GetPoliticalID());
                    }
                }
            }
        }

        Step7230();
        int n = (int)(mCitiesEnd - mCitiesBegin);
        for (int i = 0; i < n; i++)
            mCitiesBegin[i]->Tick1();
        n = (int)(mCitiesEnd - mCitiesBegin);
        for (int i = 0; i < n; i++)
            mCitiesBegin[i]->Tick2();
        ChooseUFOAndBuyVehicle();
        Step();
        Step_a660(0);
        Step_a660(1);
        Step8710();
        UpdateCivAI();
        Step5cb0();
        Step7390();
        Step1170();

        if (GetCurrentGameMode_s00bf_bbf0() == 0x1654c04) {
            Step08b0();
            if (!mIsNeutral) {
                int playerEmpire = NounManager_s00bf_bbf0()->GetPlayerEmpireOrMinus1();
                int myId = GetPoliticalID();
                if (RelationshipManager_s00bf_bbf0()->GetRelation(myId, playerEmpire, 1) <= 1) {
                    if (!mCommNotifiedWarning && mCommEventId == -1) {
                        mCommNotifiedWarning = true;
                        Step0710(1, this, 0);
                    }
                } else {
                    if (mCommEventId == 1)
                        Step07c0();
                    if (mCommNotifiedWarning)
                        mCommNotifiedWarning = false;
                }
            }
            if (sMathRandom_s00bf_bbf0.RandomUint32Uniform(1000) == 0) {
                City* c = mAttackCity;
                if (c != 0) {
                    mAttackCity = 0;
                    c->Release();
                }
            }
            Step74a0();
            Step1270();
            Step14b0();
            int playerEmpire = NounManager_s00bf_bbf0()->GetPlayerEmpireOrMinus1();
            int myId = GetPoliticalID();
            int rel = RelationshipManager_s00bf_bbf0()->GetRelation(myId, playerEmpire, 1);
            if (!mIsNeutral && mHasDeveloped && mLastRelation != rel && mLastRelation != -1) {
                int cur = mLastRelation;
                int idx = -1;
                if (rel == 4) {
                    if (cur < 4) idx = 4;
                } else if (rel < 4 && cur == 4) {
                    idx = 3;
                }
                if (rel > 1) {
                    if (cur < 2) idx = 2;
                } else {
                    if (cur > 1) idx = 1;
                }
                if (idx != -1) {
                    City* city = *mCitiesBegin;
                    Color4 color;
                    color.r = mColorR;
                    color.g = mColorG;
                    color.b = mColorB;
                    color.a = 1.0f;
                    GetStrategyMgr()->Apply(this, gStrategyTable[idx], 0xaa9a8ed7,
                                            city->pos120.GetPosition(), &color, 0, GetPoliticalID());
                    if (idx == 1) {
                        int id40 = mId40;
                        Civ_s00bf_bbf0* player = NounManager_s00bf_bbf0()->GetPlayerCivilization();
                        Notify_e3c7c0(0xf0963675, NounManager_s00bf_bbf0()->GetPlayerCivilization()->GetBlock() + 0x504,
                                      GetBlock() + 0x504, Triple(), player->mId40, id40, 0);
                    } else if (idx == 2) {
                        int id40 = mId40;
                        Civ_s00bf_bbf0* player = NounManager_s00bf_bbf0()->GetPlayerCivilization();
                        Notify_e3c7c0(0x27d48cfb, NounManager_s00bf_bbf0()->GetPlayerCivilization()->GetBlock() + 0x504,
                                      GetBlock() + 0x504, Triple(), player->mId40, id40, 0);
                    }
                }
            }
            mLastRelation = rel;
            Step3180();
            Final_ba5d30(this);
        }
    }

    // Re-evaluate mHasDeveloped from the terrain stage and the civ's size.
    if (!mHasDeveloped) {
        int cityBytes = (int)mCitiesEnd - (int)mCitiesBegin & ~3;
        int vehBytes = (int)mVehiclesEnd - (int)mVehiclesBegin & ~3;
        int stage = NounManager_s00bf_bbf0()->GetCurrentTerrainSphere()->GetKind();
        if (stage == 0) {
            if (!(cityBytes <= 8 && vehBytes <= 0x18 && GetSize0f10() <= 0x3c
                  && GetSize2ae0() <= 40000.0f && GetLevel7150() <= 4))
                mHasDeveloped = true;
        } else if (stage == 1) {
            if (!(cityBytes <= 4 && vehBytes <= 0xc && GetSize0f10() <= 0x1e
                  && GetSize2ae0() <= 20000.0f && GetLevel7150() <= 2))
                mHasDeveloped = true;
        } else if (stage == 2) {
            if (!(cityBytes <= 4 && vehBytes <= 8 && GetSize0f10() <= 0x14
                  && GetSize2ae0() <= 10000.0f && GetLevel7150() <= 1))
                mHasDeveloped = true;
        }
    }

    // City music follows the civ's music city while it owns cities.
    if (mCityMusic && mMusicCity && ((int)mCitiesEnd - (int)mCitiesBegin & ~3) != 0) {
        if (mCityMusic->IsPlaying() == 0)
            mCityMusic->Start(mMusicCity->pos120.GetPosition());
        mCityMusic->Pause(mMusicCity->IsMusicActive());
    }
}

// @ 0x00bfd610
void GameData_s00bf_cc80::Cleanup()
{
    mDefs.erase(mDefs.begin, mDefs.end);
    void* obj = ((GetAccessor)(*(void***)this)[2])(this);
    void* slot = ((GetAccessor)(*(void***)obj)[0x2b])(obj);
    if (slot != 0) {
        void* src = ((RcSlotList*)slot)->mData90;
        if (src != 0) {
            float count = 0;
            void* arr = 0;
            char ok = FUN_006a0990(src, 0x519e304, &count, &arr);
            if (ok) {
                for (int i = 0; i < (int)count; ++i) {
                    Vector3 val = ((Vector3*)arr)[i];
                    if (mDefs.end < mDefs.cap) {
                        *mDefs.end = val;
                        ++mDefs.end;
                    } else {
                        mDefs.DoInsertValue(mDefs.end, &val);
                    }
                }
            }
            mFlag6c = 0;
        }
    }
    if (mDefs.begin == mDefs.end) {
        void* o2 = ((GetAccessor)(*(void***)this)[2])(this);
        float t = ((GetFloat)(*(void***)o2)[0xd])(o2);
        Vector3 v;
        if (t <= 0.01f) {
            v.x = *(float*)0x168cb6c;
            v.y = *(float*)0x168cb70;
            v.z = *(float*)0x168cb74;
        } else {
            void* o3 = ((GetAccessor)(*(void***)this)[2])(this);
            float* m = ((float* (*)(void*))(*(void***)o3)[0x1a])(o3);
            float inv = 1.0f / t;
            v.x = ((m[3] + m[0]) * 0.5f) * inv;
            v.y = ((m[4] + m[1]) * 0.5f) * inv;
            v.z = ((m[5] + m[2]) * 0.5f) * inv;
        }
        if (mDefs.end < mDefs.cap) {
            *mDefs.end = v;
            ++mDefs.end;
        } else {
            mDefs.DoInsertValue(mDefs.end, &v);
        }
    }
}

// @ 0x00bfd800
void GameData_s00bf_cc80::SetDefinitionID()
{
    if (mDefs.begin == mDefs.end || mFlag6c != 0)
        Cleanup();
    RandomLCG_s00bf_cc80* rng = &gRandomLCG;
    int n = (int)((char*)mDefs.end - (char*)mDefs.begin) / 12;
    rng->RandomUint32Uniform(n);
}

// @ 0x00bfd840
float* GameData_s00bf_cc80::SetGameDataOwner(float* out, int index)
{
    if (mDefs.begin == mDefs.end || mFlag6c != 0)
        Cleanup();
    int count = (int)((char*)mDefs.end - (char*)mDefs.begin) / 12;
    if (index > count || index == -1)
        index = 0;
    Vector3 v = ((Vector3*)mDefs.begin)[index];
    out[0] = v.x;
    out[1] = v.y;
    out[2] = v.z;

    Matrix3 basis;
    Matrix3_Assign(&basis, (const void*)0x168d12c);

    WorldTransform wt;
    wt.flags = 0;
    void* sp = ((GetAccessor)(*(void***)this)[2])(this);
    cSpatialObject_LocalToWorldTransform(sp, &wt);
    sp = ((GetAccessor)(*(void***)this)[2])(this);
    float scale = ((GetFloat)(*(void***)sp)[0xd])(sp);
    if (wt.flags & 2) {
        float x = out[0], y = out[1], z = out[2];
        out[0] = x * wt.m.m[0] + y * wt.m.m[3] + z * wt.m.m[6];
        out[1] = x * wt.m.m[1] + y * wt.m.m[4] + z * wt.m.m[7];
        out[2] = x * wt.m.m[2] + y * wt.m.m[5] + z * wt.m.m[8];
    }
    out[0] = out[0] * scale + basis.m[0];
    out[1] = out[1] * scale + basis.m[1];
    out[2] = out[2] * scale + basis.m[2];
    return out;
}

// @ 0x00bfd9f0
void cCommunity_s00bf_d9f0::GetNounID(float* out)
{
  char* s = (char*)this;
  if (s != 0) {
    unsigned char ok = ((unsigned char(__thiscall*)(void*, int))(((void**)*(void**)s)[0x5c / 4]))(s, 0x116dd1b);
    if (ok) {
      out[0] = g_168cb6c;
      out[1] = g_168cb70;
      out[2] = g_168cb74;
      return;
    }
  }
  if (*(int*)(s + 0x58) == *(int*)(s + 0x5c) || *(char*)(s + 0x6c) != 0) FUN_00bfd610();
  {
    int n = (*(int*)(s + 0x5c) - *(int*)(s + 0x58)) / 0xc;
    unsigned idx = (unsigned)(size_t)RandomUint32Uniform(g_1601760, n);
    float* e = (float*)(*(int*)(s + 0x58) + idx * 0xc);
    float ax = e[0], ay = e[1], az = e[2];
    float bx = g_168cb6c, by = g_168cb70, bz = g_168cb74;
    char m[0x28];
    memset(m, 0, 0x28);
    *(float*)(m + 0x14) = bx;
    *(float*)(m + 0x18) = by;
    *(float*)(m + 0x1c) = bz;
    Matrix3_Assign(m + 0x18, &g_168d12c);
    {
      void* o = ((void*(__thiscall*)(void*, void*))(((void**)*(void**)s)[8 / 4]))(s, m);
      ((C_THISCALL*)o)->FUN_00c897e0();
    }
    {
      void* o = ((void*(__thiscall*)(void*))(((void**)*(void**)s)[8 / 4]))(s);
      float f = ((float(__thiscall*)(void*))(((void**)*(void**)o)[0x34 / 4]))(o);
      *(float*)(m + 0x20) = f;
    }
    if (*(unsigned char*)(m + 0x10) & 2) {
      float px = *(float*)(m + 0x30) * ax + *(float*)(m + 0x24) * ay + *(float*)(m + 0x3c) * az;
      float py = *(float*)(m + 0x34) * ay + *(float*)(m + 0x28) * ax + *(float*)(m + 0x40) * az;
      float pz = *(float*)(m + 0x38) * ay + *(float*)(m + 0x2c) * ax + *(float*)(m + 0x44) * az;
      ax = px; ay = py; az = pz;
    }
    float q = *(float*)(m + 0x20);
    q = q * ax + *(float*)(m + 0x14);
    float q1 = *(float*)(m + 0x18) + q;
    float q2 = *(float*)(m + 0x1c);
    (void)q1; (void)q2;
    {
      void* o = ((void*(__thiscall*)(void*))(((void**)*(void**)s)[8 / 4]))(s);
      float* p = (float*)((void*(__thiscall*)(void*))(((void**)*(void**)o)[0x2c / 4]))(o);
      out[0] = ax - p[0];
      out[1] = ay - p[1];
      out[2] = az - p[2];
    }
  }
}

// @ 0x00bfdc50
void cCommunity_s00bf_d9f0::Push(void* lo, void* hi)
{
  char* vec = (char*)this;
  char* end = *(char**)(vec + 4);
  if (end != *(char**)(vec + 8)) {
    if ((char*)hi >= (char*)lo && (char*)hi < end) hi = (char*)hi + 0x28;
    if (end) FUN_00bfd3e0(end - 0x28);
    FUN_00bfd490(lo, *(char**)(vec + 4) - 0x28, *(char**)(vec + 4));
    memcpy((char*)lo + 8, (char*)hi + 8, 0x18);
    *(char**)(vec + 4) += 0x28;
    return;
  }
  {
    int n = (int)(end - *(char**)vec) / 0x28;
    int cap = n ? 2 * n : 1;
    char* mem = 0;
    if (cap) mem = (char*)Alloc(0xd1, &g_13ebb38, 0, 0, &g_13f09b4, cap * 0x28);
    char* begin = *(char**)vec;
    char* e2 = (char*)FUN_00bfd430(0, mem, begin);
    (void)FUN_00bfc6e0(0, mem, begin);
    if (e2) FUN_00bfd3e0(e2);
    char* p1 = mem + 0x28;
    FUN_00bfd430(0, p1, *(char**)vec);
    char* e3 = (char*)FUN_00bfc6e0(0, p1, *(char**)vec);
    char* old = *(char**)vec;
    if (old && *(int*)(old - 4)) Free(old);
    *(char**)(vec + 4) = e3;
    *(char**)vec = mem;
    *(char**)(vec + 8) = mem + cap * 0x28;
  }
}

// @ 0x00bfddc0
void cCommunity_s00bf_d9f0::EnsureTimer(void* key)
{
  char* v = (char*)this + 0x84;
  char* p = *(char**)(v + 0);
  char* e0 = *(char**)(v + 4);
  for (; p != e0; p += 0x28)
    if (*(void**)(p + 0x20) == key) { ((C_THISCALL*)p)->FUN_00bc3130(); return; }
  {
    char* e = *(char**)(v + 4);
    if (e < *(char**)(v + 8)) {
      *(char**)(v + 4) = e + 0x28;
      if (e) ((C_THISCALL*)e)->FUN_00b63890();
    } else {
      uint32_t tmp[0x28 / 4];
      ((C_THISCALL*)tmp)->FUN_00b63890();
      ((cCommunity_s00bf_d9f0*)((char*)this + 0x84))->Push(*(void**)(v + 4), tmp);
      ((C_THISCALL*)tmp)->FUN_00b638b0();
    }
    *(void**)(*(char**)(v + 4) - 8) = key;
    ((C_THISCALL*)(*(char**)(v + 4) - 0x28))->FUN_00bc3130();
  }
}

// @ 0x00bfde50
float cCommunity_s00bf_d9f0::ReadPhase(unsigned char save)
{
  float a, b;
  ((C_THISCALL*)(void*)&g_169c253)->FUN_00ceefd0(this->m1d0, &a, &b);
  if (save) this->m1d0 = a;
  return b;
}

// @ 0x00bfdea0
float cCommunity_s00bf_d9f0::GetPhaseRatio()
{ return this->m1d0 / this->m1d4; }

// @ 0x00bfdeb0
void* cCommunity_s00bf_d9f0::ResolveID(int id)
{
  if (id == 0x403df5f) return this;
  void* r = (void*)((C_THISCALL*)((char*)this + 0x34))->FUN_00c884f0((void*)id);
  if (r) return r;
  r = (void*)((C_THISCALL*)((char*)this + 0x108))->FUN_00bfc380((void*)id);
  if (r) return r;
  return (void*)((C_THISCALL*)this)->FUN_00b18460((void*)id);
}

// @ 0x00bfdf00
float cCommunity_s00bf_d9f0::GetScaledFloat()
{
  char* o = (char*)this;
  float f = *(float*)(o + 0x5c);
  return ((float(__thiscall*)(void*))(*(void***)o)[0x34 / 4])(o) * f;
}

// @ 0x00bfdf20
void cCommunity_s00bf_d9f0::AdvancePhase(float dt)
{
  float v = g_169cc08 * dt + this->m1d0;
  this->m1d0 = v;
  if (v > this->m1d4) this->m1d0 = this->m1d4;
}

// @ 0x00bfdf60
void cCommunity_s00bf_d9f0::SetID(int v)
{
  this->m30 = v;
  void* s = this->m288;
  if (s) *(int*)s = v;
}

// @ 0x00bfdf80
void* cCommunity_s00bf_d9f0::GetNoun()
{
  int id = ((int(__thiscall*)(void*))(((void**)*(void**)this)[0x4c / 4]))(this);
  void* r = 0;
  if (id != -1) {
    r = (void*)((C_THISCALL*)FUN_00b3d300())->FUN_00b25f40(id);
  }
  return r;
}

// @ 0x00bfdfb0
void cCommunity_s00bf_d9f0::SetState(int v)
{
  if (this->m1ec != v) {
    this->m1ec = v;
    ((C_THISCALL*)((char*)this + 0x1f0))->FUN_00bc3130();
  }
  void* s = this->m288;
  if (s) *(int*)((char*)s + 4) = v;
}

// @ 0x00bfdff0
float cCommunity_s00bf_d9f0::GetProgress()
{
  unsigned long long t = (unsigned long long)((C_THISCALL*)((char*)this + 0x1f0))->FUN_00bc3190();
  double frac = (double)t / (double)(unsigned)this->m210;
  float f = (float)(frac * g_13ec4d0);
  if (!(f > 0.0f)) f = 0.0f;
  if (f > g_13ec4d0) f = g_13ec4d0;
  return f;
}

// @ 0x00bfe0c0
int cCommunity_s00bf_d9f0::HasNoun()
{
  int id = ((int(__thiscall*)(void*))(((void**)*(void**)this)[0x4c / 4]))(this);
  void* r = 0;
  if (id != -1) {
    r = (void*)((C_THISCALL*)FUN_00b3d300())->FUN_00b25f40(id);
  }
  return r != 0;
}

// @ 0x00bfe0f0
unsigned char cCommunity_s00bf_d9f0::Write(void* stream)
{
  void* o = ((void*(__thiscall*)(void*))(((void**)*(void**)stream)[0x20 / 4]))(stream);
  int id = ((int(__thiscall*)(void*))(((void**)*(void**)o)[0x18 / 4]))(o);
  unsigned t = 0x403df5f;
  WriteUint32((void*)id, &t, 1, 0);
  unsigned char ok = 0;
  if (((C_THISCALL*)this)->FUN_00b18590(stream)) {
    if (((C_THISCALL*)((char*)this + 0x34))->FUN_00c88a90(stream)) ok = 1;
  }
  char vs[0x18];
  ((C_THISCALL*)vs)->FUN_00cVarListSerializer_Construct(this, &g_1570a60, 0x1a80d26);
  if (ok) {
    if (((C_THISCALL*)vs)->FUN_cVarListSerializer_Serialize(stream)) return 1;
  }
  return 0;
}

// @ 0x00bfe230
void CStub230::FUN_00bfe230(char* a, char* b)
{
  ((CStub899a0*)this)->FUN_00c899a0(a, b);
  *(float*)(b + 4) = *(float*)(b + 4) - g_14007f4;
}

// @ 0x00bfe260
void* cCommunity_s00bf_d9f0::FillPair(char* obj)
{
  int v = ((int(__thiscall*)(void*))(((void**)*(void**)(obj + 0x108))[0x10 / 4]))(obj + 0x108);
  *(int*)((char*)this + 0) = v;
  *(int*)((char*)this + 4) = *(int*)(obj + 0x1ec);
  return this;
}

// @ 0x00bfe310
void FUN_00bfe310(char* a)
{
  char* r = ((char*(__cdecl*)(void*))(((void**)a)[0x20 / 4]))(a);
  *r = g_168d181;
}

// @ 0x00bfe450
void cCommunity_s00bf_d9f0::Activate(int a, RefObj* b)
{
  char* s = (char*)this;
  *(int*)(s + 0x210) = 0x1388;
  *(int*)(s + 0x214) = a;
  RefObj* old = this->m1e0;
  if (b != old) {
    if (b) ((void(__thiscall*)(void*))(((void**)*(void**)b)[0]))(b);
    this->m1e0 = b;
    if (old) ((void(__thiscall*)(void*))(((void**)*(void**)old)[1]))(old);
  }
  if (this->m1ec != 1) { this->m1ec = 1; ((C_THISCALL*)(s + 0x1f0))->FUN_00bc3130(); }
  void* sh = this->m288;
  if (sh) *(int*)((char*)sh + 4) = 1;
}

// @ 0x00bfe4d0
void cCommunity_s00bf_d9f0::Deactivate()
{
  char* s = (char*)this;
  *(int*)(s + 0x210) = 0;
  *(int*)(s + 0x214) = -1;
  _ReadWriteBarrier();
  RefObj* e = this->m1e0;
  if (e) { this->m1e0 = 0; ((void(__thiscall*)(void*))(((void**)*(void**)e)[1]))(e); }
  if (this->m1ec != 0) { this->m1ec = 0; ((C_THISCALL*)(s + 0x1f0))->FUN_00bc3130(); }
  void* sh = this->m288;
  if (sh) *(int*)((char*)sh + 4) = 0;
}

// @ 0x00bfe530
void cCommunity_s00bf_d9f0::SetupScenery()
{
  void* sub = (char*)this + 0x34;
  void* r = ((void*(__thiscall*)(void*))(((void**)*(void**)sub)[0x98 / 4]))(sub);
  if (*(int*)r != 0) return;
  float one = 1.0f;
  ((void(__thiscall*)(void*, int, float))(((void**)*(void**)sub)[0x40 / 4]))(sub, 0, one);
  void* pm = FUN_00b3d350();
  int cont = ((C_THISCALL*)pm)->FUN_00b88590();
  void* p2 = FUN_00b3d350();
  unsigned char b = *(unsigned char*)(cont + *(int*)((char*)p2 + 0x64));
  if (b) {
    unsigned k = 0x4728435;
    ((void(__thiscall*)(void*, unsigned*))(((void**)*(void**)sub)[0x94 / 4]))(sub, &k);
  } else {
    unsigned k = 0xa6b33a2f;
    ((void(__thiscall*)(void*, unsigned*))(((void**)*(void**)sub)[0x94 / 4]))(sub, &k);
  }
}

// @ 0x00bfe5d0
unsigned char cCommunity_s00bf_d9f0::Read(void* arg)
{
  unsigned char ok = (unsigned char)((C_THISCALL*)this)->FUN_00b183f0(arg);
  if (!ok) return ok;
  if (*(int*)((char*)this + 0xd0) == 0) return ok;
  int id = ((int(__thiscall*)(void*))(((void**)*(void**)this)[0x4c / 4]))(this);
  void* r = (void*)((C_THISCALL*)FUN_00b3d300())->FUN_00b25f40(id);
  float* src;
  float tmpv[3];
  if (id != -1 && r != 0) {
    src = (float*)((char*)r + 0xc4);
  } else {
    tmpv[0] = tmpv[1] = tmpv[2] = g_1471064;
    src = tmpv;
  }
  void* dst = (char*)this->mD0 + 0x4c;
  ((float*)dst)[0] = src[0];
  ((float*)dst)[1] = src[1];
  ((float*)dst)[2] = src[2];
  return ok;
}

struct CommunityModelFlagsView {
  void* mWorld;                     // +0x00, cMWObject prefix
  unsigned mFlags;                  // +0x04
};

// @ 0x00bfe690
bool cCommunity_s00bf_d9f0::LoadModel(void* arg)
{
  bool loaded = ((C_THISCALL*)this)->FUN_00c8a550(arg);
  if (loaded) {
    CommunityModelFlagsView* model = (CommunityModelFlagsView*)m9c;
    if (model)
      model->mFlags |= 4;
  }
  return loaded;
}

// @ 0x00bfe6c0
void cCommunity_s00bf_d9f0::ReleaseTable()
{
  char* s = (char*)this;                       // this == &community->m230
  RefObj** a = *(RefObj***)(s + 8);
  if (*(int*)(s + 0x14) == *(int*)(s + 0x24)) {
    RefObj** e = *(RefObj***)(s + 0x18);
    for (; a < e; ++a) { RefObj* p = *a; if (p) p->Release(); }
  } else {
    RefObj** e1 = *(RefObj***)(s + 0x10);
    for (; a < e1; ++a) { RefObj* p = *a; if (p) p->Release(); }
    RefObj** b = *(RefObj***)(s + 0x1c);
    RefObj** e2 = *(RefObj***)(s + 0x18);
    for (; b < e2; ++b) { RefObj* p = *b; if (p) p->Release(); }
    if (*(void**)(s + 0x1c)) Free(*(char**)(s + 0x1c));
  }
  char* b0 = *(char**)(s + 0x14) + 4;
  if (b0 < *(char**)(s + 0x24)) {
    do {
      RefObj*** blk = *(RefObj****)b0;
      RefObj** q = *blk;
      RefObj** qe = q + 0x40;
      for (; q < qe; ++q) { RefObj* p = *q; if (p) p->Release(); }
      if (*blk) Free((char*)*blk);
      b0 += 4;
    } while (b0 < *(char**)(s + 0x24));
  }
  *(void**)(s + 0x18) = *(void**)(s + 8);
  *(void**)(s + 0x1c) = *(void**)(s + 0xc);
  *(void**)(s + 0x20) = *(void**)(s + 0x10);
  *(void**)(s + 0x24) = *(void**)(s + 0x14);
}

// @ 0x00bfe7c0
void FUN_00bfe7c0(SeqIter* out, RefObj*** bucketLo, RefObj** cur, RefObj** end, void** key)
{
  RefObj*** bl = bucketLo;
  void* k = *key;
  if (cur == end) {
    out->cur = cur;
    out->bucket = (RefObj***)bl;
    return;
  }
  for (;;) {
    if (*cur == (RefObj*)k) break;
    cur++;
    if (cur == end) {
      bl++;
      RefObj** q = *bl;
      end = q + 0x40;
      cur = q;
    }
  }
  out->cur = cur;
  out->begin = (RefObj**)bl;
  out->end = end;
  out->bucket = (RefObj***)(cur);
}

// @ 0x00bfe840
void FUN_00bfe840(SeqIter* out, SeqIter* a, SeqIter* b)
{
  RefObj** ay = a->cur;
  RefObj** by = b->cur;
  if (ay == a->begin) goto result;
  for (;;) {
    if (ay == b->cur) {
      RefObj*** bp = a->bucket - 1;
      a->bucket = bp;
      ay = *bp;
      a->begin = ay;
      a->end = ay + 0x40;
    }
    ay = ay - 1;
    a->cur = ay;
    if (by == b->begin) {
      RefObj*** bp = b->bucket - 1;
      b->bucket = bp;
      by = *bp;
      b->begin = by;
      b->end = by + 0x40;
    }
    by = by - 1;
    b->cur = by;
    {
      RefObj* nv = *ay;
      RefObj* ov = *by;
      if (nv != ov) {
        if (nv) nv->AddRef();
        *by = nv;
        if (ov) ov->Release();
      }
    }
    if (ay != a->end) continue;
    break;
  }
result:
  out->cur = by;
  out->begin = a->begin;
  out->end = a->end;
  out->bucket = (RefObj***)by;
}

// @ 0x00bfe900
void cCommunity_s00bf_d9f0::SpawnAt(float* pos)
{
  float p[3];
  p[0] = pos[0];
  p[1] = pos[1];
  p[2] = pos[2];
  {
    void* pm = FUN_00b3d350();
    if (((C_THISCALL*)pm)->FUN_00b7e3e0(p)) {
      void* r = ((C_THISCALL*)FUN_00b3d350())->FUN_00b81630(p, 0);
      p[0] = ((float*)r)[0];
      p[1] = ((float*)r)[1];
      p[2] = ((float*)r)[2];
    }
  }
  if (*(void**)((char*)this + 0x1a4) == 0) {
    void* nm = FUN_00b3d300();
    void* n = ((C_THISCALL*)nm)->FUN_00b20c60(0x2e72cae);
    void* obj = 0;
    if (n) obj = (void*)((void*(__thiscall*)(void*, int))(((void**)*(void**)n)[0xc / 4]))(n, 0x2e71a5a);
    void* old = *(void**)((char*)this + 0x1a4);
    if (obj != old) {
      if (obj) ((void(__thiscall*)(void*))(((void**)*(void**)obj)[0]))(obj);
      *(void**)((char*)this + 0x1a4) = obj;
      if (old) ((void(__thiscall*)(void*))(((void**)*(void**)old)[1]))(old);
    }
    void* cur = *(void**)((char*)this + 0x1a4);
    if (cur) ((C_THISCALL*)cur)->FUN_00c3f2d0((char*)this - 0x34);
  }
  ((C_THISCALL*)this)->FUN_00c88670(p);
  {
    void* obj = *(void**)((char*)this + 0x1a4);
    void* r = ((void*(__thiscall*)(void*))(((void**)*(void**)this)[0x2c / 4]))(this);
    ((C_THISCALL*)obj)->FUN_00c3f160(r);
  }
}

// @ 0x00bfeb00
void cCommunity_s00bf_d9f0::InitScenery()
{
  char* s = (char*)this;
  if (s[0x1e4]) return;
  void* p = *(void**)(s + 0xd0);
  float v[3];
  if (*(void**)((char*)p + 0x90)) {
    void* pl = *(void**)((char*)p + 0x90);
    FUN_0059aed0(pl, (void*)0x51cae56, v);
    void* pl2 = *(void**)((char*)p + 0x90);
    if (pl2) {
      float* r = 0;
      if (((unsigned char(__thiscall*)(void*, int, float**))(((void**)*(void**)pl2)[0x24 / 4]))(pl2, 0x51cae57, &r)) {
        if (*(short*)((char*)r + 0x12) == 0xd) {
          r = (float*)GetFloatProp((unsigned*)r);
          v[0] = *r;
        }
      }
    }
  }
  {
    void* pm = FUN_00b3d350();
    char* sub = s + 0x34;
    float* a = (float*)((void*(__thiscall*)(void*))(((void**)*(void**)sub)[0x2c / 4]))(sub);
    int b = ((int(__thiscall*)(void*))(((void**)*(void**)sub)[0x30 / 4]))(sub);
    float t[3];
    FUN_0059aed0((void*)b, (void*)0, t);
    float x = a[0] + t[0];
    float y = a[1] + t[1];
    float z = a[2] + t[2];
    float wx = v[0] + x, wy = v[1] + y, wz = v[2] + z;
    ((C_THISCALL*)pm)->FUN_00b83c40(&wx, 0.0f, 0x10000000, 0);
  }
  s[0x1e4] = 1;
}

// @ 0x00bfec10
void* cCommunity_s00bf_d9f0::Front()
{
  struct View {
    char pad238[0x238];
    int* a;                        // +0x238
    char pad23c[0x248 - 0x23c];
    int* b;                        // +0x248
  };
  View* v = (View*)this;
  int* a = v->a;
  if (a == v->b) return 0;
  return (void*)*a;
}

// @ 0x00bfec30
bool __cdecl FUN_00bfec30(void* cont, int* key)
{
    V4 end;
    end.a = *(int*)((char*)cont + 0x18);
    end.b = *(int*)((char*)cont + 0x1c);
    end.c = *(int*)((char*)cont + 0x20);
    end.d = *(int*)((char*)cont + 0x24);
    V4 begin;
    begin.a = *(int*)((char*)cont + 8);
    begin.b = *(int*)((char*)cont + 0xc);
    begin.c = *(int*)((char*)cont + 0x10);
    begin.d = *(int*)((char*)cont + 0x14);
    V4 r;
    V4* rp = FUN_00bfe7c0(&r, begin, end, key);
    return rp->a != *(int*)((char*)cont + 0x18);
}

// @ 0x00bfed50
void __fastcall FUN_00bfed50(CommodityNode* n)
{
    n->vt0 = &vtbl_1469b08;
    n->vt1 = &vtbl_1469af4;
    n->vt2 = &vtbl_1469a30;
    n->vt3 = &vtbl_14699c8;
    ((TDT*)n->timer2)->dtor();
    FUN_00abf900(&n->m230);
    ((TDT*)n->timer1)->dtor();
    if (n->m1e0 != 0)
        ((RefObj*)n->m1e0)->Release();
    void* p = n->m1dc;
    if (p != 0) {
        int c = *(int*)((char*)p + 0x40);
        if (c > 1) {
            *(int*)((char*)p + 0x40) = c - 1;
        } else {
            typedef void (__thiscall* Fn)(void*, unsigned);
            unsigned flag = (*(unsigned*)((char*)p + 4) >> 31) & 1;
            (*(Fn)(*(char**)*(char**)p + 0x170))(p, flag);
        }
    }
    if (n->m1d8 != 0)
        ((RefObj*)n->m1d8)->Release();
    FUN_00bfcd00(&n->vt3);
    FUN_00c8a420(&n->vt2);
    FUN_00b184c0(n);
}

// @ 0x00bff010
CommodityNode* __fastcall FUN_00bff010(CommodityNode* n)
{
    ((TG*)n)->ctor();
    ((TS*)&n->vt2)->ctor();
    ((TC*)&n->vt3)->ctor();
    n->vt3 = &vtbl_14699c8;
    n->vt2 = &vtbl_1469a30;
    n->vt0 = &vtbl_1469b08;
    n->vt1 = &vtbl_1469af4;
    n->m1d0 = 100.0f;
    n->m1d4 = 100.0f;
    n->m1d8 = 0;
    n->m1dc = 0;
    n->m1e0 = 0;
    n->m1e4 = 0;
    n->m1e5 = 0;
    n->m1e6 = 0;
    n->m1e7 = 0;
    n->m1e8 = 0;
    n->m1e9 = 0;
    n->m1ec = 0;
    ((TG*)n->timer1)->ctor();
    n->m210 = 0;
    n->m224 = 0.0f;
    n->m228 = 0.0f;
    n->m22c = 0.0f;
    n->m214 = -1;
    n->m218 = -1;
    n->m21c = -1;
    n->m220 = -1;
    Container* c = &n->m230;
    c->m00 = 0;
    c->m04 = 0;
    c->begin.cur = 0;
    c->begin.begin = 0;
    c->begin.end = 0;
    c->begin.arr = 0;
    c->end.cur = 0;
    c->end.begin = 0;
    c->end.end = 0;
    c->end.arr = 0;
    FUN_00ca09f0(0);
    n->m260 = 0;
    n->m264 = 0;
    ((TG*)n->timer2)->ctor();
    n->m288 = 0;
    ((TMS*)n->timer1)->Start();
    return n;
}

// @ 0x00bff140
void CommodityNode::FUN_00bff140(RefObj* obj)
{
    CommodityNode* n = this;
    Container* c = &n->m230;
    if (FUN_00bfec30(c, (int*)&obj))
        return;
    RefObj* p = obj;
    if (p != 0)
        p->AddRef();
    int** cur = (int**)c->end.cur;
    if (cur + 1 != (int**)c->end.end) {
        c->end.cur = (int*)(cur + 1);
        if (cur != 0) {
            *cur = (int*)p;
            if (p != 0)
                p->AddRef();
        }
    } else {
        c->FUN_00c92bd0(&obj);
    }
    if (p != 0)
        p->Release();
}

// @ 0x00bff220
bool __cdecl FUN_00bff220(Container* c, int* key)
{
    int* cur   = c->begin.cur;
    int* last  = c->end.cur;
    int* begin = c->begin.begin;
    int* end   = c->begin.end;
    int** arr  = c->begin.arr;
    if (cur != last) {
        int k = *key;
        do {
            if (*cur == k) {
                Iter it;
                it.cur = cur;
                it.begin = begin;
                it.end = end;
                it.arr = arr;
                (void)c->FUN_00c95660(it);
                return true;
            }
            ++cur;
            if (cur == end) {
                begin = arr[1];
                ++arr;
                end = begin + 0x40;
                cur = begin;
            }
        } while (cur != last);
    }
    return false;
}

// @ 0x00bff290
void CommodityNode::FUN_00bff290(int key)
{
    Container* c = &m230;
    if (m230.begin.cur != m230.end.cur && key == *m230.begin.cur) {
        c->FUN_00c92b70();
        return;
    }
    FUN_00bff220(c, &key);
}

// @ 0x00bff2d0
void __fastcall FUN_00bff7a0(CommodityNode* n)
{
    (void)n;
}

// @ 0x00bff6e0
void CommodityNode::FUN_00bff6e0(int a)
{
    CommodityNode* n = this;
    n->FUN_00bff2d0(a, -1);
    FUN_00bfe530(n);
    void** vt = *(void***)&n->vt2;
    void* world = SP_GonzagoModelWorld();
    (*(void (__thiscall*)(void*, void*))vt[0x28])(&n->vt2, world);
    FUN_00bfeb00(n);
    if (n->m1ec != 3) {
        n->m1ec = 3;
        ((TMR*)n->timer1)->Restart();
    }
    if (n->m288 != 0)
        *(int*)((char*)n->m288 + 4) = 3;
}

// @ 0x00bff750
void CommodityNode::FUN_00bff750()
{
    CommodityNode* n = this;
    n->m1e7 = 0;
    n->FUN_00bff2d0(-1, -1);
    n->m210 = 0x9c4;
    if (n->m1ec != 5) {
        n->m1ec = 5;
        ((TMR*)n->timer1)->Restart();
    }
    if (n->m288 != 0)
        *(int*)((char*)n->m288 + 4) = 5;
}
