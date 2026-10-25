// src/game/SPGonzago/SPCityVisualizer.cpp -- migrated from slice(s) s00d5fb60, s00d5e730, s00d5d880, s00d5ccf0, s00d5bfa0, s00d58a80, s00d57b50, s00ad20e0, s00acf4c0, s00acd4a0, s00ac8d00, s00ac4060 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityVisualizer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
extern "C" void  __cdecl EASTL_allocator_deallocate(void*); // 0x00f47380
extern char sz_name_13f09b4[]; // 0x013f09b4 "Simulator"
extern char sz_file_13ebb38[]; // 0x013ebb38 "...allocator.h"
#include <string.h>
#include "SP/cITerrainSphere.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "SP/cViewer.h"
#include <math.h>
#include <intrin.h>
#include "SP/cSpeciesProfile.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cActionCircle.h"
#include "SP/cCity.h"
#include "SP/cCityVisualizer.h"
#include "SP/cSPTimer.h"
#include <new>
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "EA/Stopwatch.h"
#include <float.h>

// ---- items of slice s00ac4060 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  uint;
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
extern "C" void  __cdecl EASTL_allocator_deallocate(void*); // 0x00f47380
extern char sz_name_13f09b4[]; // 0x013f09b4 "Simulator"
extern char sz_file_13ebb38[]; // 0x013ebb38 "...allocator.h"
#define EA_ALLOC(sz) EASTL_allocator_allocate((sz), sz_name_13f09b4, 0, 0, sz_file_13ebb38, 0xd1)
#define EA_FREE(p)   EASTL_allocator_deallocate(p)
struct T3c {
    uint d[15];
    void CopyFrom(const T3c& src);   // 0x00ac1ff0
};
extern "C" T3c* __cdecl copy_2130(T3c* first, T3c* last, T3c* dst); // 0x00ac2130
struct Vec3f { float x, y, z; };
struct Vec12 {
    Vec3f* mpBegin; Vec3f* mpEnd; Vec3f* mpCapacity; int mAlloc; Vec3f* mpPool;
    void DoAssignValues(Vec3f* position, const Vec3f& value);
};
// ---- items of slice s00ac4060 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" T3c* __cdecl copy_2130(T3c* first, T3c* last, T3c* dst); // 0x00ac2130

// ---- items of slice s00ac8d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CT {
    char  pad0[0x20];
    float* mpSphereBegin;     // +0x20
    float* mpSphereEnd;       // +0x24
    char  pad1[0xa4 - 0x28];
    void* mpA4;               // +0xa4
    char  pad2[0xbc - 0xa8];
    void* mpBC;               // +0xbc
    void  FUN_00ac8d00(int city, int a);
    void  FUN_00ac8d40(int a);
    bool  FUN_00ac8d60(int a);
    bool  FUN_00ac8d80(float* p);
    bool  FUN_00ac8df0(float* p);
    void  FUN_00ac8e90();
};
// ---- items of slice s00ac8d00 end

// ---- items of slice s00acd4a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_NounManager();                                   // 0xb3d300
extern "C" void  SP_cGameNounManager_RemoveNoun(void* mgr, int noun);// 0xb225d0
extern "C" void* SP_cSPLivingUniverse_GetActivePlanet();             // 0x1021260
extern "C" void* SP_GetCurrentGameMode();                            // 0xb5b800
extern "C" void* FUN_00b33f40();                                     // 0xb33f40
extern "C" void  FUN_00a02c30(void* p);                              // 0xa02c30
extern "C" void  SP_cAnimatingCreature_Release(void* p);            // 0xa05270
extern "C" void  FUN_009cb4f0(void* p);                              // 0x9cb4f0
extern "C" void  FUN_00acc9b0(int n);                                // 0xacc9b0
extern float DAT_0167a390, DAT_0167a394, DAT_0167a398;
extern "C" int* eastl_copy_dummy(int* a, int* b, int* c);   // 0x6782c0
extern "C" void FUN_01008600(void* p);   // 0x1008600
extern "C" int  FUN_00ac9480(int* p);    // 0xac9480
extern "C" void* FUN_00c70c10(void* planet);   // 0xc70c10
extern int DAT_01565cfc;
extern "C" char FUN_00d58460(void* p);                // 0xd58460
extern "C" int  FUN_00acb190(void* a, int* b);        // 0xacb190
typedef unsigned int   uint32;
typedef unsigned char  byte;
struct RCObj { virtual void AddRef(); virtual void Release(); };
struct Rec {
    int   f00;                        // +0x00
    char  pad04[0x18 - 4];
    int*  p18;                        // +0x18
    int*  p1c;                        // +0x1c
    char  pad20[0x2c - 0x20];
    void** p2c;                       // +0x2c
    int*  p30;                        // +0x30
    char  pad34[0x40 - 0x34];
    int*  p40;                        // +0x40
    int*  p44;                        // +0x44
    char  pad48[0x54 - 0x48];
    int*  p54;                        // +0x54
    int*  p58;                        // +0x58
    char  pad5c[0x68 - 0x5c];
    int   p68;                        // +0x68
};
struct COwner {
    char pad0[0xc4];
    void** mpMap;    // +0xc4
    int    mIndex;   // +0xc8
    void FUN_00acd4a0();
};
struct CSys {
    char pad0[0xa0];
    void* mpA0;      // +0xa0
    byte FUN_00acd6c0(int msg, int* p);
};
struct CCreature {
    char pad0[0x64];
    byte  mb64;        // +0x64
    char  pad65[0x88 - 0x65];
    uint32 mFlags88;   // +0x88
    char pad8c[0x118 - 0x8c];
    int*  mpVec118;    // +0x118
    char pad11c[0x17c - 0x11c];
    int*  mp17c;       // +0x17c
    void FUN_00acd790();
};
struct CPlanet {
    char pad[0x13c];
    int* mTree;   // +0x13c
};
// ---- items of slice s00acd4a0 end

// ---- items of slice s00acf4c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_ViewStamp;        // 0x167a378
extern uint32_t g_CurStamp;         // 0x16881e4
extern float g_ElapsedSec;          // 0x167a494
extern char g_ForceRefresh;         // 0x1565cfc
extern float g_RefreshPeriod;       // 0x1565ce0
extern float g_DensityMax;          // 0x1565ce4
extern float g_DensityThresh;       // 0x1565ce8
extern float g_SpawnTime;           // 0x1565cec
extern uint32_t g_SpawnTries;       // 0x1565cf0
extern float g_PlantRadiusBias;     // 0x1565cf8
extern float g_RingMin;             // 0x1565d54
extern float g_RingMax;             // 0x1565d58
extern float g_CullRadiusX;         // 0x1565d5c
extern float g_CullRadiusZ;         // 0x1565d60
extern uint8_t g_FaceAxes[];        // 0x145a090 : 3 axis indices per cube-face pair, stride 4
extern void* g_ModeSpecial;         // 0x1654c04
struct Vector3 { float x, y, z; };
struct RefObj {
    virtual void AddRef();
    virtual void Release();
};
struct PosHolder {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
    virtual Vector3* GetPosition();
};
struct NounInfo { char pad[0x504]; Vector3 spawnPos; };   // +0x504
struct PlantModel {
    char pad0[0x34];
    PosHolder holder;                   // +0x34
    char pad38[0x25c - 0x38];
    float radius;                       // +0x25c
};
struct Plant : RefObj {
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
    virtual PlantModel* GetModel();     // slot 27 (+0x6c)
    char pad04[0x40 - 4];
    void* childBegin;                   // +0x40
    void* childEnd;                     // +0x44
    char pad48[0xa4 - 0x48];
    NounInfo* info;                     // +0xa4
    char pada8[0xf4 - 0xa8];
    uint32_t fadeTime;                  // +0xf4
    char padf8[0x108 - 0xf8];
    float spawnTime;                    // +0x108
    char pad10c[0x192 - 0x10c];
    char flag192;                       // +0x192
    Vector3* __thiscall GetPlantPosition();     // 0xc6acc0
    char __thiscall PlantIsBusy();              // 0xc6a020
    void __thiscall SetPlantFlag(bool b);       // 0xc6ace0
};
struct IRefVec {
    RefObj** begin; RefObj** end; RefObj** cap;
    void __thiscall Append(RefObj** where, uint32_t n, RefObj** val);      // 0xbabb70
};
struct TileNode {
    uint32_t key;                       // +0x00
    Vector3 pos;                        // +0x04
    float dist;                         // +0x10
    char pad14[0x28 - 0x14];
    IRefVec plants;                     // +0x28 (AutoRefCount<Plant>)
    char pad34[0x3c - 0x34];
    IRefVec extras;                     // +0x3c
    char pad48[0x68 - 0x48];
    TileNode* next;                     // +0x68
};
struct TileMap {
    char pad[4];
    TileNode** buckets;                 // +4
    uint32_t bucketCount;               // +8
};
struct CullEntry { float x, y, z, rx2, rz2; };   // 0x14 bytes
struct CullVec { CullEntry* begin; CullEntry* end; CullEntry* cap; };
struct cViewer {
    void __thiscall GetCameraLocationInfo(Vector3* pos, Vector3* dir, void* a, void* b);   // 0x7c3d30
};
struct IViewerSource {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
    virtual cViewer* GetViewer();       // +0x1c
};
struct IApp {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
    virtual IViewerSource* GetViewerSource();   // +0x50
};
struct ISphereData { char pad[8]; int dim; char pad2[4]; uint8_t* data; };   // +8 dim, +0x10 data
struct ISphereLevel { char pad[0xc]; ISphereData* d; };
struct ISphereIface {
virtual void p0();
virtual void p1();
virtual void p2();
    virtual ISphereLevel* GetLevel();   // +0xc
};
struct cPlanetModel {
    char pad[0x24];
    ISphereIface* mpISphere;                                                       // +0x24
    float   __thiscall GetWaterHeight();                                            // 0xb7e390
    Vector3* __thiscall FUN_00b81630(Vector3* out, Vector3* in);                    // 0xb81630
    void    __thiscall FUN_00b82060(Vector3* out, Vector3* cam, Vector3* dir);      // 0xb82060
    float   __thiscall GetRadiusAt(Vector3* dir);                                   // 0xb7ef70
    Vector3* __thiscall DirectionToSurfacePosition(Vector3* out, Vector3* dir);     // 0xb815a0
    Vector3* __thiscall MakeRandomWorldPosition(Vector3* out, Vector3* center, float r0, float r1); // 0xb81780
    uint32_t __thiscall GetAverageRadius(Vector3* pos);                             // 0xb7e840
    Plant*   __thiscall FindPlantNear(Vector3* pos);                                // 0xb894a0
};
struct cTerrainCameraController { Vector3* __thiscall GetAnchorDirection0(); };    // 0xb10200
struct cPlanet {
    char pad[0x13c];
    char* pTreeData;                                                                // +0x13c
    int __thiscall PlantSpeciesToTypeIndex(void* species);                          // 0xc70d70
    char* __thiscall GetTileBase();                                                 // 0x8414c0
};
struct cGameNounManager {
    void __thiscall RemoveNoun(Plant* noun);                                        // 0xb225d0
    Plant* __thiscall CreateNoun(Vector3* pos, void* profile, uint32_t scale, int a, int b, int c); // 0xb23940
};
struct cDirectPropertyList { int __thiscall GetIntProperty(uint32_t id); };         // 0x6a2660
IApp*             SP_App();                                         // 0x67dd10
cPlanetModel*     SP_PlanetModel();                                 // 0xb3d350
cGameNounManager* SP_NounManager_s00ac_f4c0();                                 // 0xb3d300
cTerrainCameraController* GetTerrainCameraController();             // 0xb3d280
cPlanet*          GetActivePlanet();                                // 0x1021260
void*             GetCurrentGameMode();                             // 0xb5b800
void*             __stdcall GetSpeciesManagerFor(void* key);        // 0x401090
struct SpeciesManager {
    void* __thiscall GetProfile();                                   // 0x4df550
};
void __cdecl operator_delete_array(void* p);                        // 0xf47380
extern Vector3 g_InvalidPos;        // 0x167a390
extern cDirectPropertyList* g_AppProperties;   // 0x15fd918
struct FixedFloatVec {
    float* begin; float* end; float* cap;
    void __thiscall Fill(float* where, uint32_t n, const float* val);   // 0x4b0a10
};
struct cPlantSpawner {
    char pad0[0x20];
    CullVec cull;                       // +0x20
    char pad2c[0xc0 - 0x2c];
    TileMap tiles;                      // +0xc0

    TileNode* __thiscall TileAt(uint32_t* key);                                  // 0xace170 (operator[])
    void __thiscall UpdateCullCenter(Vector3* v, float rx, float rz);            // 0xacc700
    void __thiscall GrowCull(CullEntry* where, CullEntry* val);                  // 0xacb680
    void __thiscall Tail(uint32_t a, uint32_t b);                                // 0xace5a0
    void Update(uint32_t dt, uint32_t dtAlt);
};
// ---- items of slice s00acf4c0 end

// ---- items of slice s00ad20e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*   __cdecl GetCurrentGameModeAlt();     // 0x00b5b820
extern "C" void*   __stdcall FUN_00ad11f0(void*);      // 0x00ad11f0
extern "C" void* __cdecl FUN_00ad2320(void*);           // 0x00ad2320 (slice-local)
typedef unsigned char uchar;
typedef void* (__thiscall *TC_p0)(void*);
typedef void  (__thiscall *TC_v1)(void*, void*);
typedef void* (__thiscall *TC_p1)(void*, void*);
typedef void  (__thiscall *TC_v5)(void*, void*, void*, void*, void*);
#define VTC(obj, off, type) ((type)(*(void***)(obj))[((off) >> 2)])
struct RegElem {              // 0x0c bytes
    int   pad0;
    uchar flag4;
    char  pad5[3];
    void* p8;
};
struct RegList {              // returned by the registry lookup
    char     pad0[8];
    RegElem* begin;           // +0x08
    RegElem* end;             // +0x0c
};
struct Element14 {            // 0x14-byte element of the +0x20 vector
    float x, y, z;
    float s1, s2;
};
struct Rel    { void release(void*); }; // 0x00c96e80 (this=arg0, 1 stack arg)
struct cMain {
    char    pad00[0x1c];
    void*   msg1c;             // +0x1c  (message target)
    Element14* vecBegin;       // +0x20
    Element14* vecEnd;         // +0x24
    Element14* vecCap;         // +0x28
    char    pad2c[0x88 - 0x2c];
    char    sub88[4];          // +0x88  (Sub88 accessor)
    char    pad8c[0xa0 - 0x8c];
    int     f_a0;              // +0xa0
    char    padA4[0xbc - 0xa4];
    void*   p_bc;              // +0xbc
    char    padC0[0x100 - 0xc0];
    char    f_100;             // +0x100
    char    f_101;             // +0x101

    void* findEntry(int a, int b);          // 0x00ad20e0
    void  init100();                        // 0x00ad2200
    void  f_23c0(void* tag, int a, int b);  // 0x00ad23c0
    void  f_2560(int arg);                  // 0x00ad2560
    void  f_25e0(void* a, void* b);         // 0x00ad25e0
    void  setup(void* tag, int cap);        // 0x00ad1000
    void  removeE(RegList* list, int idx);  // 0x00ac8a80
    void  f_12a0();                         // 0x00ad12a0
    void  f_e4e0(void* arg);                // 0x00ace4e0
    void  f_f4c0(int a, int b);             // 0x00acf4c0
    void  f_e5a0(int a, int b);             // 0x00ace5a0
    void  f_98e0(void* v);                  // 0x00ac98e0
    void  f_8130();                         // 0x00ac8130
    void  f_0bd0();                         // 0x00ad0bd0
    void  release(void* obj);               // 0x00c96e80
};
// ---- items of slice s00ad20e0 end

// ---- items of slice s00d57b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
typedef unsigned long long u64;
typedef          long long s64;
void* __cdecl FUN_00bd9e80(void* self, u32 idx);       // 0x00bd9e80 (thiscall)
void  __cdecl FUN_00bd9ea0(void* self, int a, int b, int c);  // 0x00bd9ea0 (thiscall)
void* __cdecl FUN_00bd9480(void* self, void* out);     // 0x00bd9480 (thiscall)
void  __cdecl FUN_00af9cf0(void* pos, float r, void* f, float alt); // 0x00af9cf0 SetAtCenter
void  __cdecl FUN_00afdfe0(void* self, float r);       // 0x00afdfe0 EmitRing (thiscall)
void  __cdecl FUN_00bc3170(void* p);                   // 0x00bc3170
void  __cdecl FUN_00bc97f0(u32 a, u32 b, float c, u32 d); // 0x00bc97f0
float __cdecl FUN_00bc9980(float f);                   // 0x00bc9980
void* __cdecl FUN_00b3d380();                          // 0x00b3d380 GameTimeManager
u64   __cdecl FUN_00b316c0(void* self);                // 0x00b316c0 (thiscall)
void* __cdecl FUN_00d995f0(float f, double d, u32 a, void* b, void* c, u32 d2, u32 e, u32 g); // 0x00d995f0
void* __cdecl FUN_00b3d350();                          // 0x00b3d350 SP::PlanetModel
void  __cdecl FUN_00b7f250(void* pm, void* out, void* pos, void* dir); // 0x00b7f250 BuildSurfaceOrientation2
char  __cdecl FUN_00ac0730(void* a, void* b);          // 0x00ac0730
void* __cdecl FUN_0067de30();                          // 0x0067de30 PropertyManager
float* __cdecl FUN_0041ea70(void* p);                  // 0x0041ea70 Property::GetFloat (thiscall)
// ---- items of slice s00d57b50 end

// ---- items of slice s00d58a80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uintptr_t;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct IObj {
    virtual void Slot0();               // 0x00
    virtual void Slot4();               // 0x04
    virtual void Slot8();               // 0x08
    virtual void* SlotC();              // 0x0c
};
struct IBehaviorManager {
    PV8 PV4 PV2                                 // 0x00..0x34
    virtual void Slot38(void* a);               // 0x38
    virtual void Slot3c(void* a);               // 0x3c
};
struct ActionCircle {
    void  CtorAC();                             // 0x00afba10
    void  Dtor();                               // 0x00afbad0
    void* SlotAt(uint32_t i);                   // 0x00af9ff0
};
struct GonzagoTimer {
    void Ctor();                                // 0x00b63890
    void Dtor();                                // 0x00b638b0
};
struct PtrVec14 {
    void**   mpBegin;                           // +0x00
    void**   mpEnd;                             // +0x04
    void**   mpCap;                             // +0x08
    uint32_t m0C;                               // +0x0c
    uint32_t m10;                               // +0x10
};
struct CityVis {
    uint8_t   pad00[0x10];                      // +0x00
    uint8_t   mTimer[0x20];                      // +0x10 (cGonzagoTimer)
    uint8_t   mCircle30[0x64];                  // +0x30
    uint8_t   mCircle94[0x64];                  // +0x94
    uint8_t   mCircleF8[0x64];                  // +0xf8
    PtrVec14  mVec15C;                          // +0x15c
    PtrVec14  mVec170;                          // +0x170
    uint8_t   pad184[0x8c0];                    // +0x184..+0xa43
    int32_t   mIndexA44;                        // +0xa44
    uint8_t   mByteA48;                         // +0xa48
    uint8_t   padA49[0x1b];                     // +0xa49..+0xa63
    void**    mpVecA64;                         // +0xa64
    void**    mpVecA68;                         // +0xa68
    uint8_t   padA6C[0x5c];                     // +0xa6c..+0xac7
    void**    mpVecAC8;                         // +0xac8
    void**    mpVecACC;                         // +0xacc
    uint8_t   padAD0[0x0c];                     // +0xad0..+0xadb
    void**    mpVecADC;                         // +0xadc
    void**    mpVecAE0;                         // +0xae0
    uint8_t   padAE4[0x0c];                     // +0xae4..+0xaef
    void*     mpCityAF0;                        // +0xaf0
    uint8_t   padAF4[0xc8];                     // +0xaf4..+0xbbb
    void**    mpVecBBC;                         // +0xbbc
    void**    mpVecBC0;                         // +0xbc0
};
void*       SP_BehaviorManager();                                          // 0x00b3d260
// ---- items of slice s00d58a80 end

// ---- items of slice s00d5bfa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_c0x13ec4b8;                                 // sqrt epsilon
extern float g_c0x13ec480;                                 // 0.2
extern float g_c0x13f7674;
extern float g_c0x1471064;
extern float g_c0x1470f1c;
extern float g_c0x1485548;                                 // 1.5
extern float g_c0x1485720;                                 // 1.0
extern void* g_p0x1583e08;                                 // 0x01583e08 message id
struct cCityVisualizer;
template <class R> static inline R VC0(void* o, int slot) {
    typedef R (__thiscall * Fn)(void*);
    return ((Fn)(*(void***)o)[slot])(o);
}
template <class R, class A> static inline R VC1(void* o, int slot, A a) {
    typedef R (__thiscall * Fn)(void*, A);
    return ((Fn)(*(void***)o)[slot])(o, a);
}
template <class R, class A, class B, class C, class D> static inline R VC4(void* o, int slot,
                                                                        A a, B b, C c, D d) {
    typedef R (__thiscall * Fn)(void*, A, B, C, D);
    return ((Fn)(*(void***)o)[slot])(o, a, b, c, d);
}
struct SPEditorSpeciesManager {
    void* GetAvatarProfile();                              // 0x004df420
};
SPEditorSpeciesManager* __cdecl FUN_00401090();             // 0x00401090 (setting 9)
struct cSim {
    void* UpdateVignettes(int id);                         // 0x00ad11f0 (ret 4)
};
cSim* __cdecl FUN_00b3d480();                              // 0x00b3d480
struct cNounManager {
    int GetPlayerEmpireOrMinus1();                         // 0x00b1f9d0
};
cNounManager* __cdecl FUN_00b3d300();                      // 0x00b3d300
struct RandomLC {
    u32    RandomUint32Uniform(u32 n);                     // 0x00a68fb0 (ret 4)
    double RandomDoubleUniform();                          // 0x009360d0
};
extern RandomLC g_Random;                                  // 0x01601760
struct SimB {
    int  FUN_00bc3db0(void* id);                           // 0x00bc3db0 (ret 4)
    void FUN_00bc52a0(void* id, void* arg);                // 0x00bc52a0 (ret 8)
    char FUN_00bc4900(void* id, void* a, void* b);         // 0x00bc4900 (ret 0xc)
};
SimB* __cdecl FUN_00b3d4e0();                              // 0x00b3d4e0
struct RefCount {
    virtual void AddRef();
    virtual void Release();
};
struct ArrayHeader { u32 mPad; u32 mAlloc; };
struct Vec3 { float x, y, z; };
struct SubObj { void* mVtbl; };
struct cActionCircle {
    float mX, mY, mZ;                                      // +0x00 (direction / centre)
    float mPad0c[2];                                       // +0x0c
    float mA, mB, mC;                                      // +0x14
    u8    mPad20[0x64 - 0x20];
    void SetAtCenter(const void* center, float radius, const void* facing, float altitude); // 0xaf9cf0 (ret 0x10)
    void FUN_00afef10(int n, float f);                     // 0xafef10 (ret 8)
    void FUN_00afd6d0(float a, float b, int n);            // 0xafd6d0 (ret 0xc)
};
struct SPVec {
    void** mBegin;                                         // +0x00
    void** mEnd;                                           // +0x04
    void** mCap;                                           // +0x08
    u32    mTag;                                           // +0x0c
    u32    mAlloc;                                         // +0x10
    void DoInsertPtr(void** pos, void* const& val);        // 0xaea5d0 (ret 8)
    void erase(void* first, void* last);                   // 0xe25bd0 (ret 8)
    void FUN_00b93c60(int count, void* alloc);             // 0x00b93c60 (ret 8)
};
struct Elem28 {
    void* mId;                                             // +0x00
    u8    mFlag;                                           // +0x04
    u8    mPad05[3];                                       // +0x05
    SPVec mVec;                                            // +0x08
};
struct Entity {
    u8    pad_00[0x20];
    float m20, m24, m28;                                   // +0x20
    u8    pad_2c[0x34 - 0x2c];
    SubObj mSub34;                                         // +0x34
    u8    pad_38[0xc0 - 0x38];
    SubObj mSubC0;                                         // +0xc0
    u8    pad_c4[0xb4c - 0xc4];
    void* mB4c;                                            // +0xb4c
    u8    pad_b50[0xb54 - 0xb50];
    void* mB54;                                            // +0xb54
    u8    pad_b58[0xb62 - 0xb58];
    u8    mB62;                                            // +0xb62
    u8    pad_b63[0xff0 - 0xb63];
    void* mFF0;                                            // +0xff0
    // methods
    void* GetSpeciesProfile();                             // 0xc0bbd0
    void  FUN_00c222f0(void* prof);                        // 0xc222f0 (ret 4)
    void  FUN_00c0d950(int v);                             // 0xc0d950 (ret 4)
    void  SetCurrentToolEffect(int a, int b);              // 0xc24f40 (ret 8)
};
struct StimSet {
    void FUN_00bc97f0(int type, int a, float prio, int b); // 0xbc97f0 (ret 0x10)
};
struct cCity {
    void* FUN_00bd9e40();                                  // 0x00bd9e40 (avatar creature)
    void* GetCivilization();                               // 0x00bd9bf0
    void* GetCityHall();                                   // 0x00bd9b40
    void* FUN_00bd99e0();                                  // 0x00bd99e0
    int   FUN_00bd8160();                                  // 0x00bd8160
    void* GetMembers();                                    // 0x00c8e810
    void  FUN_00bd7f70(void* out1, void* out2);            // 0x00bd7f70 (ret 8)
    void  FUN_00bdf750(void* vec);                         // 0x00bdf750 (ret 4)
    u8    pad_00[0x120];
    SubObj mSub120;                                        // +0x120
    u8    pad_124[0x2a0 - 0x124];
    u8    m2a0;                                            // +0x2a0
};
struct SlotEntry { void* mPtr; int mCount; };
struct SlotVecBuf { SlotEntry mEntries[128]; };
struct FlagOwner  { u32 mPad; u32 mFlags; };
struct Holder180  { u8 mPad[0x180]; FlagOwner* mOwner; };
struct cCityVisualizer {
    u8    pad_00[0x0c];
    cActionCircle mCircle0c;                               // +0x0c  (ends +0x70)
    cActionCircle mCircle70;                               // +0x70  (ends +0xd4)
    cActionCircle mCircleD4;                               // +0xd4  (ends +0x138)
    u8    pad_138[0x234 - 0x138];
    cActionCircle mCircle234;                              // +0x234 (ends +0x298)
    cActionCircle mCircle298;                              // +0x298 (ends +0x2fc)
    cActionCircle mCircle2fc;                              // +0x2fc
    u8    pad_360[0xa64 - 0x360];
    void** mCitizenBegin;                                  // +0xa64
    void** mCitizenEnd;                                    // +0xa68
    void** mCitizenCap;                                    // +0xa6c
    u32    mAllocA70;                                      // +0xa70
    u32    mAllocA74;                                      // +0xa74
    SPVec  mVignetteVec[4];                                // +0xa78 (stride 0x14)
    u8    pad_acc[0xaf0 - 0xac8];
    cCity* mCity;                                          // +0xaf0
    u8    mFlagAf4;                                        // +0xaf4
    u8    mFlagAf5;                                        // +0xaf5
    u8    pad_af6[0xbbc - 0xaf6];
    Elem28* mElemBegin;                                    // +0xbbc
    Elem28* mElemEnd;                                      // +0xbc0
    u8    pad_bc4[0xbd0 - 0xbc4];
    int   mCountBd0;                                       // +0xbd0
    // methods
    char  FUN_00d5c470(void* a, void* b);
    void  FUN_00d5c580(void* citizen);
    void  FUN_00d5c620(void* vec, int count);
    void  FUN_00d5c720();
    void  FUN_00d5c8c0();
    void  FUN_00d5bfa0(char enable);
    // external member callees
    int   FUN_00d57a00();                                  // 0x00d57a00 ComputeVisualizedPopulation
    void  FUN_00d57940(void* p);                           // 0x00d57940 (ret 4)
    void  FUN_00d58c50(void* p);                           // 0x00d58c50 (ret 4)
    void  FUN_00d5b9f0();                                  // 0x00d5b9f0 (ret 0)
};
void __cdecl FUN_00d588a0(void* profile, float* a, float* b, float* c);                 // 0x00d588a0
void __cdecl FUN_00d57800(void* effect, cCityVisualizer* viz, void* profile, int empire,
                          int idx, void* pos, float a, float b, float c);                // 0x00d57800
void __cdecl FUN_00d5aae0(void* container, void** out, void* val);                      // 0x00d5aae0
void __cdecl FUN_00d5bb50(void* a, void* b, float f0, float f1, float f2);               // 0x00d5bb50
void __cdecl FUN_00829110(void* out, void* first, void* last, void* dest, void* param);  // 0x00829110
void __cdecl FUN_00f47380(void* p);                                                      // 0x00f47380 (operator delete[])
struct VecBuilder {                                          // 0x00b93c60 (thiscall, 2 args, ret 8)
    void* mBegin;                                          // +0x00
    void* mEnd;                                            // +0x04
    void* mCap;                                            // +0x08
    u32   mTag;                                            // +0x0c
    u32   mAlloc;                                          // +0x10
    VecBuilder(int n, void* alloc);
};
// ---- items of slice s00d5bfa0 end

// ---- items of slice s00d5ccf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct tVec3 { float x, y, z; };
struct tQuat { float x, y, z, w; };
struct VecAgents { char m[0x14]; VecAgents& operator=(const VecAgents& o); };
struct VecSlots  { char m[0x0c]; VecSlots&  operator=(const VecSlots&  o); };
struct cActionCircle_s00d5_ccf0 {
    tVec3 mFacing;        // +0x00
    float mRadius;        // +0x0c
    float mSlotRadius;    // +0x10
    tVec3 mCenter;        // +0x14
    float mAltitude;      // +0x20
    int   mPacking;       // +0x24
    bool  mbRelative;     // +0x28
    char  pad29[3];
    tQuat mOrientation;   // +0x2c
    VecAgents mAgents;    // +0x3c
    VecSlots  mSlots;     // +0x50
    cActionCircle_s00d5_ccf0& operator=(const cActionCircle_s00d5_ccf0& o);
};
// ---- items of slice s00d5ccf0 end

// ---- items of slice s00d5d880 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
void __cdecl operator_delete(void* pBlock);         // 0x00f47380
void* __cdecl operator_new(size_t nSize, const char* pName, int32_t nA,
                           int32_t nB, const char* pFile, int32_t nLine);   // 0x00f473a0
class SlotPayload {
public:
    SlotPayload& operator=(const SlotPayload& rOther);      // 0x01011cc0
    uint8_t mPad00[0x14];
};
class CitySlot {
public:
    uint32_t mnId;              // +0x00
    bool mbA;                   // +0x04
    bool mbB;                   // +0x05
    bool mbC;                   // +0x06
    SlotPayload mPayload;       // +0x08  (the 0x07 byte is tail padding)
};
void __stdcall DestroySlot(CitySlot* pSlot);                        // 0x00d59630
void __cdecl MoveBackwardSlots(CitySlot* pPos, CitySlot* pFirst, CitySlot* pLast);  // 0x00d5bf50
CitySlot* __cdecl UninitializedCopySlots(CitySlot* pFirst, CitySlot* pLast, CitySlot* pOut);    // 0x00d59890
void __cdecl DestroyRangeSlots(CitySlot* pFirst, CitySlot* pLast, CitySlot* pOut);              // 0x00d598d0
class SlotVector {
public:
    void Insert(CitySlot* pPos, const CitySlot* pValue);    // 0x00d5e5c0

    CitySlot* mpBegin;          // +0x00
    CitySlot* mpEnd;            // +0x04
    CitySlot* mpCapacity;       // +0x08
};
// ---- items of slice s00d5d880 end

// ---- items of slice s00d5e730 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct StarVec {                                        // eastl::vector<AutoRefCount<cStarRecord>>
    void* mBegin;                                       // +0x00
    void* mEnd;                                         // +0x04
    void* mCap;                                         // +0x08
    StarVec() : mBegin(0), mEnd(0), mCap(0) {}
    ~StarVec();
};
struct Elem1C {                                         // 0x1c-byte element
    void*   m00;                                        // +0x00 (uninitialised POD)
    void*   m04;                                        // +0x04
    StarVec v;                                          // +0x08
    void*   m14;                                        // +0x14 (uninitialised POD)
    void*   m18;                                        // +0x18
    Elem1C() {}
};
struct Elem1CVec {
    Elem1C* mBegin;                                     // +0x00
    Elem1C* mEnd;                                       // +0x04
    Elem1C* mCap;                                       // +0x08
    void DoInsertValue(Elem1C* pos, Elem1C* value);     // 0xd5e5c0
    void push_back();
};
struct cActionCircle_s00d5_e730 {                                  // 100-byte element
    uint32_t m00;
    char     pad[96];
    ~cActionCircle_s00d5_e730();                                   // 0xafbad0
};
struct ActionCircleVec {
    cActionCircle_s00d5_e730* mBegin;                              // +0x00
    cActionCircle_s00d5_e730* mEnd;                                // +0x04
    cActionCircle_s00d5_e730* mCap;                                // +0x08
    cActionCircle_s00d5_e730* erase(cActionCircle_s00d5_e730* first, cActionCircle_s00d5_e730* last);
};
cActionCircle_s00d5_e730* FUN_00d5d530(cActionCircle_s00d5_e730* first, cActionCircle_s00d5_e730* last, cActionCircle_s00d5_e730* result); // 0xd5d530
// ---- items of slice s00d5e730 end

// ---- items of slice s00d5fb60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int SP_GetPlayerEmpireID();          // 0x1021090
extern void SP_SetUpCitizenBodyScaleRanges(void* profile, float* a, float* b, float* c);  // 0xd588a0
extern void FUN_00d995f0(float dt, double gameTime, int a, void* creature, void* b, int c, int flags, int t);
extern void FUN_00aea5d0_push(void* vec, void** pos, void** val);   // 0xaea5d0 (thiscall vector grow-insert)
extern float g_PosX;  // 0x169ec28 (invalid-position sentinel)
    extern float g_PosY; // 0x0169ec2c
    extern float g_PosZ; // 0x0169ec30
template <class T> static inline T& F(void* p, int off) { return *(T*)((char*)p + off); }
template <class R> static inline R VC0_s00d5_fb60(void* o, int slot) {
    typedef R(__thiscall * Fn)(void*);
    return ((Fn)(*(void***)o)[slot])(o);
}
template <class R, class A> static inline R VC1_s00d5_fb60(void* o, int slot, A a) {
    typedef R(__thiscall * Fn)(void*, A);
    return ((Fn)(*(void***)o)[slot])(o, a);
}
template <class R, class A, class B> static inline R VC2(void* o, int slot, A a, B b) {
    typedef R(__thiscall * Fn)(void*, A, B);
    return ((Fn)(*(void***)o)[slot])(o, a, b);
}
struct Stopwatch {
    void Restart();                // 0x571e80
    u64 GetElapsedTime();          // 0x93a5e0
};
struct Timer {
    bool IsRunning();              // 0xfeba90
    u64 GetElapsedTime();          // 0xbc3190
    void Restart();                // 0xbc3130
};
struct Stim {                      // blackboard written by the stimulus system
    float pad[3];
    float x, y, z;                 // +0xc
    float radius;                  // +0x18
    int id;                        // +0x1c
};
struct StimSet_s00d5_fb60 {                   // behavior_stimuli at creature+0xb4c -> +8
    Stim* FUN_00bc97f0(int type, int a, float prio, int b);   // 0xbc97f0
    void ClearAll(int type, int a);                           // 0xbc98f0
    int FUN_00bc9980(float dt);                               // 0xbc9980
};
struct GameTimeMgr { u64 FUN_00b316c0(); };                   // 0xb316c0
struct Rand { double RandomDoubleUniform(); };                // 0x9360d0
struct Avatar { void* FUN_00ff5b80(); };                      // 0xff5b80 (returns list head)
struct SpaceGame { Avatar* GetAvatar(); };                    // 0xb1fdb0
struct Profile { void* GetAvatarProfile(); };                 // 0x4df420
struct EffMgr { void* FUN_00ad11f0(int); };                   // 0xad11f0
struct SimGlobal {                                            // FUN_00b3d4d0 result
    char pad[0x28];
    bool b28;
    char pad2[3];
    int mode;                                                 // +0x2c
};
struct City {
    int GetCreatureCount();        // 0xbd8120
    bool FUN_00bd7df0();
    bool FUN_00bd8240();
    bool FUN_00bd8280();
    bool FUN_00bd82c0();
    void FUN_00bdf7e0(void* v);
    void FUN_00bdf880(void* v);
    void* FUN_00bd9e40();
    void* GetCivilization();       // 0xbd9bf0
    void* FUN_00bd8d60(int i);
};
struct Viz {
    void FUN_00d5bfa0(int a);
    void FUN_00d57e20(int a);
    int FUN_00d57ef0(int a);
    void FUN_00d5ef80();
    void FUN_00d581b0();
    void FUN_00d58d50();
    u32 SpaceOnlyTick();           // 0xd5e0c0
    void AllegianceUpdate();       // 0xd5d880
    bool FUN_00d599a0(void* creature);
    void FUN_00d58ea0();
    void UpdateBackgroundNoise();  // 0xd5b0c0
    void Update(u64 elapsed);
};
extern u32 SP_GetCurrentGameMode_s00d5_fb60();         // 0xb5b800
extern SimGlobal* FUN_00b3d4d0();
extern void FUN_00b4b040(void* p, u32 t, int one);
extern SpaceGame* SP_SpaceGameGet();        // 0x1002bd0
extern GameTimeMgr* SP_GameTimeManager();   // 0xb3d380
extern void* FUN_00b3d480_s00d5_fb60();
extern Profile* FUN_00401090_s00d5_fb60();
extern void FUN_00d57800(void* effect, Viz* viz, void* profile, int civ, int idx, Vec3* pos, float a, float b, float c);
extern Rand sMathRandom;                    // 0x1601760
// ---- items of slice s00d5fb60 end

// @ 0x00ac4720
void Vec12::DoAssignValues(Vec3f* position, const Vec3f& value)
{
    if (mpEnd != mpCapacity) {
        const Vec3f* pv = &value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd)
            *mpEnd = *(mpEnd - 1);
        Vec3f* p = mpEnd - 1;
        while (p != position) {
            *p = *(p - 1);
            --p;
        }
        *position = *pv;
        ++mpEnd;
        return;
    }
    uint oldSize = (uint)(mpEnd - mpBegin);
    uint cap = (oldSize == 0) ? 1 : oldSize * 2;
    Vec3f* nb;
    if (cap == 0) nb = 0;
    else nb = (Vec3f*)EA_ALLOC(cap * sizeof(Vec3f));
    Vec3f* p = (Vec3f*)copy_2130((T3c*)mpBegin, (T3c*)position, (T3c*)nb);
    if (p)
        *p = value;
    ++p;
    p = (Vec3f*)copy_2130((T3c*)position, (T3c*)mpEnd, (T3c*)p);
    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
        EA_FREE(mpBegin);
    mpBegin = nb;
    mpEnd = p;
    mpCapacity = nb + cap;
}

// @ 0x00ac8d80
bool CT::FUN_00ac8d80(float* p)
{
    float* pf = mpSphereBegin;
    float* end = mpSphereEnd;
    if (pf != end) {
        float x = p[0], y = p[1], z = p[2];
        do {
            float dx = x - pf[0];
            float dy = y - pf[1];
            float dz = z - pf[2];
            float sum = dx * dx + dy * dy + dz * dz;
            if (pf[4] > sum) return false;
            pf += 5;
        } while (pf != end);
    }
    return true;
}

// @ 0x00acd4a0
void COwner::FUN_00acd4a0()
{
    SP_NounManager();
    void** p = mpMap;
    Rec* rec = (Rec*)*p;
    if (!rec) {
        ++p;
        while (*p == 0) ++p;
        rec = (Rec*)*p;
    }
    Rec* end = (Rec*)mpMap[mIndex];
    while (rec != end) {
        int n1 = (rec->p1c - rec->p18) >> 2;
        int n2 = (rec->p30 - (int*)rec->p2c) >> 2;
        int n3 = (rec->p44 - rec->p40) >> 2;
        int n4 = (rec->p58 - rec->p54) >> 2;
        int i = 0;
        if (rec->p18 != rec->p1c) {
            do {
                if (n1 <= i) break;
                (*(void (__thiscall*)(void*, int))((char*)*(void**)(rec->p1c - 1) + 0xc8))(*(void**)(rec->p1c - 1), 1);
                ++i;
            } while (rec->p18 != rec->p1c);
        }
        i = 0;
        if (n2 > 0) {
            do {
                int v = (int)rec->p2c[i];
                if (v) SP_cGameNounManager_RemoveNoun(0, v);
                ++i;
            } while (i < n2);
        }
        { int* b = (int*)rec->p2c; int* e = rec->p30; eastl_copy_dummy(e, e, b); }
        { int* q = rec->p30; for (int* it = q; it < rec->p30; ++it) { if (*it) ((RCObj*)*it)->Release(); } }
        rec->p30 = (int*)((char*)rec->p30 - n2*4);
        i = 0;
        if (n3 > 0) { do { SP_cGameNounManager_RemoveNoun(0, rec->p40[i]); ++i; } while (i < n3); }
        eastl_copy_dummy(rec->p44, rec->p44, rec->p40);
        { int* q = rec->p44; for (; q < rec->p44; ++q) { if (*q) ((RCObj*)*q)->Release(); } }
        rec->p44 = (int*)((char*)rec->p44 - n3*4);
        i = 0;
        if (n4 > 0) { do { SP_cGameNounManager_RemoveNoun(0, rec->p54[i]); ++i; } while (i < n4); }
        eastl_copy_dummy(rec->p58, rec->p58, rec->p54);
        { int* q = rec->p58; for (; q < rec->p58; ++q) { if (*q) ((RCObj*)*q)->Release(); } }
        rec->p58 = (int*)((char*)rec->p58 - n4*4);
        rec = (Rec*)rec->p68;
        while (!rec) { ++p; rec = (Rec*)*p; }
    }
}

// @ 0x00acd6c0
byte CSys::FUN_00acd6c0(int msg, int* p)
{
    if (msg == 0x1a0219e) {
        if (p[2] == 3) {
            int v = (*(int (__thiscall*)(void*))*(void**)((char*)*(void**)p[4] + 0x20))((void*)p[4]);
            if (v == (int)0x18c43e8 || v == (int)0x18c6d19) DAT_01565cfc = 1;
        } else if (p[2] == 4 && p[4]) {
            int v = (*(int (__thiscall*)(void*, uint32))*(void**)((char*)*(void**)p[4] + 0xc))((void*)p[4], 0x4f396a66);
            if (v) {
                byte* b = (byte*)((char*)this + 0x8c);
                if (*(void**)((char*)this + 0x8c) != *(void**)((char*)this + 0x90)) {
                    FUN_00ac9480((int*)(*(int*)((char*)this + 0x90) - 0x18));
                    FUN_01008600((int*)(*(int*)((char*)this + 0x90) - 0x14));
                    FUN_00acb190((void*)b, 0);
                }
            }
        }
    } else if (msg == 0x6130eb9) {
        FUN_00d58460(mpA0);
    }
    return 0;
}

// @ 0x00acd790
void CCreature::FUN_00acd790()
{
    CPlanet* planet = (CPlanet*)SP_cSPLivingUniverse_GetActivePlanet();
    int* tree = (int*)planet->mTree;
    int count = (*(int*)((char*)tree + 0xd4) - *(int*)((char*)tree + 0xd0)) / 0xc;
    int mode = (int)SP_GetCurrentGameMode();
    if (mode == (int)0x1654c04) count = 5;
    else if (count < 1) return;
    int* vec = (int*)((char*)this + 0x118);
    FUN_00acc9b0(count);
    int k = 0;
    for (int i = 0; i < count; ++i) {
        int base = *(int*)((char*)tree + 0xd0);
        int* mgr = (int*)FUN_00b33f40();
        int* v = vec;
        int off = k * 4;
        int obj = (*(int (__thiscall*)(void*, int, int, void*, void*, int))((char*)*mgr + 0x30))(
                      mgr, base + i * 0xc, 4, &DAT_0167a390, (void*)0x1565d20, 1);
        int old = *(int*)(*v + off);
        if (obj != old) {
            if (obj) FUN_00a02c30((void*)obj);
            *(int*)(*v + off) = obj;
            if (old) SP_cAnimatingCreature_Release((void*)old);
        }
        if (*(int*)(*v + off) == 0) {
            int sp = (int)FUN_00c70c10(planet);
            mgr = (int*)FUN_00b33f40();
            int obj2 = (*(int (__thiscall*)(void*, int, int, void*, void*, int))((char*)*mgr + 0x30))(
                           mgr, sp + 0x504, 4, &DAT_0167a390, (void*)0x1565d20, 1);
            old = *(int*)(*v + off);
            if (obj2 != old) {
                if (obj2) FUN_00a02c30((void*)obj2);
                *(int*)(*v + off) = obj2;
                if (old) SP_cAnimatingCreature_Release((void*)old);
            }
        }
        int rec = *(int*)(*v + off);
        *(uint32*)(rec + 0x88) &= ~1;
        *(byte*)(rec + 0x64) = 0;
        if (*(int*)(rec + 0x17c)) FUN_009cb4f0(*(void**)(rec + 0x17c));
        k += 0xc;
    }
}

// @ 0x00acf4c0
void cPlantSpawner::Update(uint32_t dt, uint32_t dtAlt)
{
    // drop any previous culling regions
    cull.end = cull.begin;

    cPlanetModel* model = SP_PlanetModel();
    float waterHeight = model->GetWaterHeight();
    float cullRX = g_CullRadiusX;
    float cullRZ = g_CullRadiusZ;

    Vector3 camPos, camDir;
    cViewer* viewer = SP_App()->GetViewerSource()->GetViewer();
    viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);

    Vector3 tmp;
    cTerrainCameraController* ctl = GetTerrainCameraController();
    if (ctl) {
        Vector3 a = *ctl->GetAnchorDirection0();
        if (a.x != g_InvalidPos.x || a.y != g_InvalidPos.y || a.z != g_InvalidPos.z) {
            Vector3 t;
            Vector3* r = model->FUN_00b81630(&t, &a);
            a = *r;
            UpdateCullCenter(&a, cullRX, cullRZ);
        }
    } else {
        Vector3 d;
        model->FUN_00b82060(&d, &camPos, &camDir);
        if (d.x != g_InvalidPos.x || d.y != g_InvalidPos.y || d.z != g_InvalidPos.z)
            UpdateCullCenter(&d, cullRX, cullRZ);
    }

    {
        Vector3* r = model->FUN_00b81630(&tmp, &camPos);
        camPos = *r;
    }
    float hx = cullRX * 0.5f;
    float hz = cullRZ * 0.5f;
    if (cull.end < cull.cap)
        ++cull.end;
    else {
        CullEntry scratch;
        GrowCull(cull.end, &scratch);
    }
    CullEntry* e = cull.end - 1;
    e->x = camPos.x; e->y = camPos.y; e->z = camPos.z;
    e->rx2 = hx * hx;
    e->rz2 = hz * hz;

    if (g_ViewStamp != g_CurStamp) {
        g_ViewStamp = g_CurStamp;
        g_ForceRefresh = 1;
    }

    uint32_t ms = dtAlt ? dtAlt : dt;
    g_ElapsedSec = g_ElapsedSec + (float)ms * 0.001f;

    if (g_ElapsedSec > g_RefreshPeriod || g_ForceRefresh) {
        g_ElapsedSec = 0.0f;

        cGameNounManager* nouns = SP_NounManager_s00ac_f4c0();
        cPlanet* planet = GetActivePlanet();
        char* tileBase = planet->GetTileBase();
        char* treeData = *(char**)((char*)planet + 0x13c);
        bool singlePerCell = ((*(uint32_t*)(treeData + 0x2c) >> 11) & 1) != 0;
        uint32_t plantTypes = (uint32_t)((*(int*)(treeData + 0xd4) - *(int*)(treeData + 0xd0)) / 12);
        if (GetCurrentGameMode() == g_ModeSpecial)
            plantTypes = 5;

        ISphereLevel* lvl = model->mpISphere->GetLevel();
        uint8_t* texels = lvl->d->data;
        int dim = lvl->d->dim;
        int faceSize = dim * dim;
        float densityThresh = g_DensityThresh;

        int densityCap = (int)g_DensityMax;
        int density = g_AppProperties->GetIntProperty(0x4a5bf9e);
        int perCell = density < densityCap ? density : densityCap;
        uint32_t spawnLimit;
        if (singlePerCell) {
            uint32_t d1 = plantTypes > 1 ? plantTypes : 1;
            uint32_t q = (uint32_t)perCell / d1;
            spawnLimit = q > 1 ? q : 1;
        } else {
            spawnLimit = perCell / 2;
        }

        for (int face = 0; face < 6; ++face) {
            for (int ty = 0; ty < 4; ++ty) {
                for (int tx = 0; tx < 4; ++tx) {
                    uint32_t cell = (uint32_t)((ty + face * 4) * 4 + tx);
                    char* cellData = tileBase + cell * 0x54 + 0x50;

                    // look the tile up; create and initialize it if it doesn't exist yet
                    uint32_t bc = tiles.bucketCount;
                    TileNode* n = tiles.buckets[cell % bc];
                    while (n && n->key != cell)
                        n = n->next;
                    if (!n) {
                        uint32_t k = cell;
                        TileNode* node = TileAt(&k);
                        float fu = (float)ty;
                        float fv = (float)tx;
                        float u = (fu + 0.5f) * 0.5f - 1.0f;
                        float v = (fv + 0.5f) * 0.5f - 1.0f;
                        float len = 1.0f / sqrt(v * v + u * u + 1.0f);
                        float sl = len;
                        if (face & 1) sl = -len;
                        const uint8_t* ax = &g_FaceAxes[(face >> 1) * 4];
                        float dir[3];
                        dir[ax[0]] = sl * v;
                        dir[ax[1]] = len * u;
                        dir[ax[2]] = sl;
                        float rad = model->GetRadiusAt((Vector3*)dir);
                        float r = rad > waterHeight ? rad : waterHeight;
                        float u2 = (fu * 0.25f) * 2.0f - 1.0f;
                        float v2 = (fv * 0.25f) * 2.0f - 1.0f;
                        float len2 = 1.0f / sqrt(v2 * v2 + u2 * u2 + 1.0f);
                        float sl2 = len2;
                        if (face & 1) sl2 = -len2;
                        float dir2[3];
                        dir2[ax[0]] = sl2 * v2;
                        dir2[ax[1]] = len2 * u2;
                        dir2[ax[2]] = sl2;
                        Vector3 other;
                        model->FUN_00b81630(&other, (Vector3*)dir2);
                        node->pos.x = dir[0] * r;
                        node->pos.y = dir[1] * r;
                        node->pos.z = dir[2] * r;
                        float dx = node->pos.x - other.x;
                        float dy = node->pos.y - other.y;
                        float dz = node->pos.z - other.z;
                        node->dist = sqrt(dy * dy + (dz * dz + dx * dx));
                    }

                    uint32_t key2 = cell;
                    TileNode* node = TileAt(&key2);

                    if (!singlePerCell) {
                        // make sure the plant slot vector has at least plantTypes entries
                        IRefVec* pv = &node->plants;
                        if ((uint32_t)(pv->end - pv->begin) < plantTypes) {
                            uint32_t sz = (uint32_t)(pv->end - pv->begin);
                            if (plantTypes > sz) {
                                RefObj* nul = 0;
                                pv->Append(pv->end, plantTypes - sz, &nul);
                            } else {
                                RefObj** newEnd = pv->begin + plantTypes;
                                for (RefObj** p = newEnd; p < pv->end; ++p)
                                    if (*p) (*p)->Release();
                                pv->end = newEnd;
                            }
                        }
                        uint32_t have = (uint32_t)(pv->end - pv->begin);
                        uint32_t n = have >= plantTypes ? have : plantTypes;

                        // fixed_vector<float,32>, zero-filled
                        struct { int hdr; float buf[32]; } store;
                        store.hdr = 0;
                        FixedFloatVec acc;
                        acc.begin = store.buf;
                        acc.end = store.buf;
                        acc.cap = store.buf + 32;
                        float zero = 0.0f;
                        if (n != 0)
                            acc.Fill(store.buf, n, &zero);
                        else
                            acc.end = acc.begin;

                        // accumulate the two species weights of this cell
                        int* sp = (int*)(cellData + 0x40);
                        for (int j = 2; j != 0; --j) {
                            int idx = planet->PlantSpeciesToTypeIndex(sp - 3);
                            if (idx >= 0 && (uint32_t)idx < n)
                                acc.begin[idx] = (float)*sp + acc.begin[idx];
                            sp += 4;
                        }

                        for (uint32_t i = 0; i < n; ++i) {
                            RefObj** slot = &node->plants.begin[i];
                            Plant* noun = (Plant*)*slot;
                            bool removeIt = false;
                            if (acc.begin[i] > 0.0f) {
                                Vector3* key = (Vector3*)(*(char**)(treeData + 0xd0) + i * 12);
                                if (noun) {
                                    Vector3* np = noun->GetPlantPosition();
                                    NounInfo* info = noun->info;
                                    bool differs = !(info->spawnPos.x == key->x && info->spawnPos.y == key->y &&
                                                     info->spawnPos.z == key->z);
                                    if (np->x == g_InvalidPos.x && np->y == g_InvalidPos.y && np->z == g_InvalidPos.z) {
                                        if (differs) removeIt = true;
                                        else noun->fadeTime = spawnLimit;
                                    } else if (differs) {
                                        removeIt = true;
                                    } else {
                                        Vector3 sp2;
                                        Vector3* s = model->DirectionToSurfacePosition(&sp2, np);
                                        float d2 = (np->x - s->x) * (np->x - s->x) +
                                                   (np->z - s->z) * (np->z - s->z) +
                                                   (np->y - s->y) * (np->y - s->y);
                                        if (d2 > 1.0f) {
                                            removeIt = true;
                                        } else {
                                            Plant* near1 = model->FindPlantNear(np);
                                            if (near1) {
                                                float rr = near1->GetModel()->radius + g_PlantRadiusBias;
                                                Vector3* q = near1->GetModel()->holder.GetPosition();
                                                float d3 = (np->x - q->x) * (np->x - q->x) +
                                                           (np->z - q->z) * (np->z - q->z) +
                                                           (np->y - q->y) * (np->y - q->y);
                                                if (rr * rr > d3) removeIt = true;
                                            }
                                            if (!removeIt) noun->fadeTime = spawnLimit;
                                        }
                                    }
                                } else {
                                    // no plant here yet: try to spawn one
                                    SpeciesManager* mgr = (SpeciesManager*)GetSpeciesManagerFor(key);
                                    void* profile = mgr->GetProfile();
                                    if (profile) {
                                        bool placed = false;
                                        Vector3 cand;
                                        uint32_t t = 0;
                                        bool again;
                                        do {
                                            Vector3 tmpv;
                                            Vector3* pr = model->MakeRandomWorldPosition(&tmpv, &node->pos,
                                                node->dist * g_RingMin, node->dist * g_RingMax);
                                            cand = *pr;
                                            uint32_t flags = model->GetAverageRadius(&cand);
                                            if ((flags & 0x98000000) == 0) {
                                                float h = (float)dim * 0.5f;
                                                float axx = fabs(cand.x);
                                                float ayy = fabs(cand.y);
                                                float azz = fabs(cand.z);
                                                int iu, iv, f;
                                                if (azz < axx || azz < ayy) {
                                                    if (ayy < axx) {
                                                        iu = (int)((cand.y / cand.x + 1.0f) * h);
                                                        iv = (int)((cand.z / axx + 1.0f) * h);
                                                        f = 2;
                                                        if (cand.x < 0.0f) f = 3;
                                                    } else {
                                                        iu = (int)((cand.z / cand.y + 1.0f) * h);
                                                        iv = (int)((cand.x / ayy + 1.0f) * h);
                                                        if (cand.y < 0.0f) f = 5; else f = 4;
                                                    }
                                                } else {
                                                    iu = (int)((cand.x / cand.z + 1.0f) * h);
                                                    iv = (int)((cand.y / azz + 1.0f) * h);
                                                    if (cand.z < 0.0f) f = 1; else f = 0;
                                                }
                                                if (iu == dim) iu = iu - 1;
                                                if (iv == dim) iv = iv - 1;
                                                if ((float)texels[3 + (iv * dim + f * faceSize + iu) * 4] * 0.3921569f <= densityThresh) {
                                                    Plant* near2 = model->FindPlantNear(&cand);
                                                    bool blocked = false;
                                                    if (near2) {
                                                        float rr = near2->GetModel()->radius + g_PlantRadiusBias;
                                                        Vector3* q = near2->GetModel()->holder.GetPosition();
                                                        float d3 = (cand.x - q->x) * (cand.x - q->x) +
                                                                   (cand.z - q->z) * (cand.z - q->z) +
                                                                   (cand.y - q->y) * (cand.y - q->y);
                                                        if (d3 < rr * rr) blocked = true;
                                                    }
                                                    if (!blocked) {
                                                        placed = true;
                                                        goto doCreate;
                                                    }
                                                }
                                            }
                                            again = t < g_SpawnTries;
                                            ++t;
                                        } while (again);
                                        cand = g_InvalidPos;
                                    doCreate:
                                        Plant* np2 = nouns->CreateNoun(&cand, profile, spawnLimit, 0, 0, 0);
                                        if (np2) {
                                            np2->SetPlantFlag(placed);
                                            np2->spawnTime = g_SpawnTime;
                                            RefObj** s2 = &node->plants.begin[i];
                                            RefObj* old = *s2;
                                            if (np2 != (Plant*)old) {
                                                np2->AddRef();
                                                *s2 = np2;
                                                if (old) old->Release();
                                            }
                                        }
                                    }
                                }
                            } else {
                                removeIt = noun != 0;
                            }
                            if (removeIt && noun) {
                                nouns->RemoveNoun(noun);
                                RefObj** s3 = &node->plants.begin[i];
                                RefObj* old = *s3;
                                if (old) {
                                    *s3 = 0;
                                    old->Release();
                                }
                            }
                        }

                        if (acc.begin && *((int*)acc.begin - 1) != 0)
                            operator_delete_array(acc.begin);
                    }

                    // reap finished extra objects
                    for (uint32_t i = 0; i < (uint32_t)(node->extras.end - node->extras.begin); ++i) {
                        Plant* ex = (Plant*)node->extras.begin[i];
                        if (ex && ex->flag192 && !ex->PlantIsBusy() && ex->childBegin == ex->childEnd) {
                            nouns->RemoveNoun(ex);
                            RefObj** slot = &node->extras.begin[i];
                            RefObj* last = node->extras.end[-1];
                            RefObj* old = *slot;
                            if (last != old) {
                                if (last) last->AddRef();
                                *slot = last;
                                if (old) old->Release();
                            }
                            --node->extras.end;
                            if (*node->extras.end) (*node->extras.end)->Release();
                        }
                    }
                }
            }
        }
    }
    g_ForceRefresh = 0;
    Tail(dt, dtAlt ? dtAlt : dt);
}

// @ 0x00ad2320
void* __cdecl FUN_00ad2320(void* param)
{
    void* edi = 0;
    void* v = FUN_00ad11f0((void*)0x18eb4b7);
    if (v != 0)
        edi = VTC(v, 0xc, TC_p1)(v, (void*)0x4f176642);
    else
        edi = 0;
    void* embParam = (char*)param + 0x120;
    void* r1 = VTC(embParam, 0x2c, TC_p0)(embParam);
    VTC(edi, 0xe8, TC_v5)(edi, 0, param, 0, r1);
    void* emb2 = (char*)edi + 0xc0;
    void* r2 = VTC(embParam, 0x2c, TC_p0)(embParam);
    VTC(emb2, 0x38, TC_v1)(emb2, r2);
    void* r3 = VTC(embParam, 0x30, TC_p0)(embParam);
    VTC(emb2, 0x3c, TC_v1)(emb2, r3);
    ((Rel*)param)->release(edi);
    return edi;
}

// @ 0x00ad25e0
void cMain::f_25e0(void* a, void* b)
{
    if (GetCurrentGameMode() == (void*)0x1654c10)
        return;
    void* mode = GetCurrentGameMode();
    if (mode == (void*)0x1654c06)
        mode = GetCurrentGameModeAlt();
    f_23c0(mode, (int)a, (int)b);
}

// @ 0x00d57b50
void __fastcall FUN_00d57b50(void* self, void* /*edx*/, char flag)
{
  char* p = (char*)self;
  char* esi = p + 0x488;
  for (int i = 0; i < 4; ++i) {
    char* e = (char*)FUN_00bd9e80(*(void**)(p + 0xaf0), (u32)i);
    if (*(int*)(e + 0x78) != 0) {
      float* o = (float*)(*(float*(__thiscall**)(void*))(*(void***)*(void**)(e + 0x78) + 0x2c / 4))(*(void**)(e + 0x78));
      float cx = o[0], cy = o[1], cz = o[2];
      u8 tmp[12];
      float* b = (float*)FUN_00bd9480(*(void**)(p + 0xaf0), tmp);
      float dx = cx - b[0];
      float dy = cy - b[1];
      float dz = cz - b[2];
      float inv = 1.0f / (float)sqrt((double)(dx * dx + (dy * dy + dz * dz)) + 1e-08);
      float nx = dx * inv;
      float ny = dy * inv;
      float nz = dz * inv;
      float px = nx * -5.0f + cx;
      float py = ny * -5.0f + cy;
      float pz = nz * -5.0f + cz;
      FUN_00af9cf0(&px, 3.0f, &nx, 0.0f);
      FUN_00afdfe0(esi, 1.5f);
      px = nx * -7.0f + px;
      py = ny * -7.0f + py;
      pz = nz * -7.0f + pz;
      FUN_00af9cf0(&px, 7.0f, &nx, 0.0f);
      FUN_00afdfe0(esi - 0x64, 1.5f);

      FUN_00bd9ea0(*(void**)(p + 0xaf0), (u32)i,
                   (*(int*)(esi - 0x14) - *(int*)(esi - 0x18)) / 0x18,
                   (*(int*)(esi + 0x54) - *(int*)(esi + 0x50)) / 0x18);

      int* dst = (int*)(esi + 0x8c);
      int* src = (int*)(e + 8);
      for (int k = 0; k < 2; ++k) {
        if (flag == 0) {
          dst[0] = 0;
          dst[2] = 0;
        } else {
          dst[0] = src[0];
        }
        ++src;
        ++dst;
      }
      *(u32*)(esi - 0xf8) = 0;
      *(u32*)(esi - 0xf0) = 0;
      *(u32*)(esi - 0xec) = 0;
      FUN_00bc3170(esi - 0xe8);
      FUN_00af9cf0(&px, 7.0f, &nx, 0.0f);
      FUN_00afdfe0(esi - 0xc8, 1.5f);
    }
    esi += 0x198;
  }
}

// @ 0x00d57e20
void __fastcall FUN_00d57e20(void* self, void* /*edx*/, char flag)
{
  char* p = (char*)self;
  *(u32*)(p + 0x9f0) = 0;
  if (*(char*)(*(int*)(p + 0xaf0) + 0x2a0) != 0) return;

  int local_4 = 0;
  char* iVar5 = p + 0x390;
  do {
    char* e = (char*)((void*(__thiscall*)(void*, int))FUN_00bd9e80)(*(void**)(p + 0xaf0), local_4);
    if (*(int*)(e + 0x78) != 0) {
      int iVar3 = 0;
      do {
        if (*(char*)(e + 0x20) == 0) {
          int iVar4 = *(int*)(e + 8 + iVar3 * 4);
          int iVar6 = 0;
          if (flag == 0) {
            iVar4 = *(int*)(e + 0x18 + iVar3 * 4);
            iVar6 = *(int*)(e + 0x10 + iVar3 * 4);
            if (iVar4 > 0 && iVar3 == 0) {
              *(int*)(p + 0x9f0) += iVar4;
            }
          } else {
            *(int*)(p + 0x9f0) += iVar4;
            iVar6 = 0;
          }
          *(int*)(iVar5 + 0x184 + iVar3 * 4) += iVar4;
          *(int*)(iVar5 + 0x18c + iVar3 * 4) += iVar6;
        } else {
          *(u32*)(iVar5 + 0x184 + iVar3 * 4) = 0;
          *(u32*)(iVar5 + 0x18c + iVar3 * 4) = 0;
        }
        ++iVar3;
      } while (iVar3 < 2);
    }
    ++local_4;
    iVar5 += 0x198;
  } while (local_4 < 4);
}

// @ 0x00d58080
void __fastcall FUN_00d58080(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  int outer = 0;
  int total = (*(int*)(p + 0xbc0) - *(int*)(p + 0xbbc)) / 0x1c;
  if (total <= 0) return;
  int off = 0;
  do {
    char* e = (char*)(*(int*)(p + 0xbbc) + off);
    int cnt = *(int*)(e + 0xc) - *(int*)(e + 8);
    if ((cnt & 0xfffffffc) > 0) {
      int k = 0;
      do {
        FUN_00bc97f0(0x8000, 0, 1.0f, 0);
        ++k;
      } while (k < (*(int*)(e + 0xc) - *(int*)(e + 8)) >> 2);
    }
    off += 0x1c;
    ++outer;
  } while (outer < (*(int*)(p + 0xbc0) - *(int*)(p + 0xbbc)) / 0x1c);
}

// @ 0x00d58330
void __fastcall FUN_00d58330(void* self, void* /*edx*/, s32 p2, u32 p3)
{
  char* p = (char*)self;
  int n = (*(int*)(p + 8) - *(int*)(p + 4)) >> 2;
  float dt = (float)((double)(s64)(((u64)p2 | ((u64)p3 << 32)) & 0x7fffffffffffffffULL) *
                     0.001);
  (void)dt;
  float f = (float)((double)p3 * 0.001);
  if (n <= 0) return;
  for (int i = 0; i < n; ++i) {
    char* c = *(char**)(*(int*)(p + 4) + i * 4);
    if (*(char*)(c + 0xb63) == 0 && *(int*)(*(int*)(c + 0xb4c)) != 0) {
      u32 r = (u32)FUN_00bc9980(f);
      void* gt = FUN_00b3d380();
      u64 t = FUN_00b316c0(gt);
      int* q = *(int**)(c + 0xb4c);
      FUN_00d995f0(f, (double)t * 0.0010000000474974513, (u32)q[0], c, q + 0x74,
                   (u32)(*(u32*)((char*)q + 0x5e8)), (u32)0, (u32)r);
    }
  }
}

// @ 0x00d58460
void __fastcall FUN_00d58460(void* self, void* /*edx*/)
{
  u32 i = 0;
  char* p = (char*)self;
  int n = *(int*)(p + 8) - *(int*)(p + 4);
  if ((u32)(n >> 2) == 0) return;
  do {
    char* o = *(char**)(*(int*)(p + 4) + i * 4);
    if (*(char*)(o + 0x137) == 0) {
      (*(void(__thiscall**)(char*, int))(*(void***)o + 0xc8 / 4))(o, 1);
    } else {
      ++i;
    }
  } while (i < (u32)((*(int*)(p + 8) - *(int*)(p + 4)) >> 2));
}

// @ 0x00d584b0
void* __fastcall FUN_00d584b0(void* self, void* /*edx*/, void* arg)
{
  char* p = (char*)self;
  void* old = 0;
  *(u32*)(p + 8) = 0x13ec458;
  *(u32*)(p + 0xc) = (u32)old;
  *(u32*)p = 0x147b9bc;
  *(u32*)(p + 8) = 0x147b9ac;
  *(u32*)(p + 0x10) = (u32)old;
  if (arg != old) {
    if (arg != 0) {
      (*(void(__thiscall**)(void*))(*(void***)arg + 0))(arg);
    }
    *(void**)(p + 0x10) = arg;
    if (old != 0) {
      (*(void(__thiscall**)(void*))(*(void***)old + 1))(old);
    }
  }
  *(u8*)(p + 0x14) = 0;
  return p;
}

// @ 0x00d58510
void** __fastcall FUN_00d58510(void* self, void* /*edx*/, void* out, void* obj, float* pos)
{
  (void)self;
  float dot = pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2];
  if (dot > 0.0f) {
    float* o = (float*)(*(float*(__thiscall**)(void*))(*(void***)obj + 0x2c / 4))(obj);
    float dz = pos[2] - o[2];
    float dx = pos[0] - o[0];
    float dy = pos[1] - o[1];
    float d2 = dz * dz + dy * dy + dx * dx;
    if (d2 > 0.0f) {
      float dir[3];
      dir[0] = dx; dir[1] = dy; dir[2] = dz;
      float* o2 = (float*)(*(float*(__thiscall**)(void*, float*))(*(void***)obj + 0x2c / 4))(obj, dir);
      void* pm = FUN_00b3d350();
      FUN_00b7f250(out, pm, pos, dir);
      return (void**)out;
    }
  }
  float* m = (float*)(*(float*(__thiscall**)(void*))(*(void***)obj + 0x30 / 4))(obj);
  ((float*)out)[0] = m[0];
  ((float*)out)[1] = m[1];
  ((float*)out)[2] = m[2];
  ((float*)out)[3] = m[3];
  return (void**)out;
}

// @ 0x00d58610
void __cdecl FUN_00d58610(void** lo, void** hi)
{
  void** p = lo;
  if (lo == hi) return;
  u32 cmpobj;
  while (1) {
    p = p + 1;
    if (p == hi) break;
    void* v = *p;
    void** q;
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
    }
    q = p;
    for (; q != lo; --q) {
      void* c1 = q[-1];
      void* a = c1 ? (char*)c1 + 0xc0 : 0;
      void* b = v ? (char*)v + 0xc0 : 0;
      if (((char(__thiscall*)(void*, void*, void*))FUN_00ac0730)(&cmpobj, b, a) == 0) break;
      void* up = q[-1];
      void* cur = *q;
      if (up != cur) {
        if (up != 0) {
          (*(void(__thiscall**)(void*))(*(void***)up + 0))(up);
        }
        *q = up;
        if (cur != 0) {
          (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
        }
      }
    }
    void* cur = *q;
    if (v != cur) {
      if (v != 0) {
        (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
      }
      *q = v;
      if (cur != 0) {
        (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
      }
    }
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 1))(v);
    }
  }
}

// @ 0x00d58700
void __fastcall FUN_00d58700(void* self, void* /*edx*/, void** lo, void** hi)
{
  (void)self;
  void** p = lo;
  if (lo == hi) return;
  while (1) {
    void* v = *p;
    void** q = p;
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
    }
    while (1) {
      void* c1 = q[-1];
      void* a = (c1 == 0) ? 0 : (char*)c1 + 0xc0;
      void* b = (v == 0) ? 0 : (char*)v + 0xc0;
      if (FUN_00ac0730(b, a) == 0) break;
      void* up = q[-1];
      void* cur = *q;
      if (up != cur) {
        if (up != 0) {
          (*(void(__thiscall**)(void*))(*(void***)up + 0))(up);
        }
        *q = up;
        if (cur != 0) {
          (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
        }
      }
      --q;
    }
    void* cur = *q;
    if (v != cur) {
      if (v != 0) {
        (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
      }
      *q = v;
      if (cur != 0) {
        (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
      }
    }
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 1))(v);
    }
    ++p;
    if (p == hi) break;
  }
}

// @ 0x00d587e0
void __fastcall FUN_00d587e0(void* self, void* /*edx*/, void** base, s32 lo, s32 hi, void* v)
{
  (void)self;
  void** arr = base;
  while (hi > lo) {
    s32 parent = (hi - 1) >> 1;
    void* a = (v == 0) ? 0 : (char*)v + 0xc0;
    void* up = arr[parent];
    void* b = (up == 0) ? 0 : (char*)up + 0xc0;
    if (FUN_00ac0730(b, a) == 0) break;
    void* pv = arr[parent];
    void* cur = arr[hi];
    if (pv != cur) {
      if (pv != 0) {
        (*(void(__thiscall**)(void*))(*(void***)pv + 0))(pv);
      }
      arr[hi] = pv;
      if (cur != 0) {
        (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
      }
    }
    hi = parent;
  }
  void* cur = arr[hi];
  if (v != cur) {
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
    }
    arr[hi] = v;
    if (cur != 0) {
      (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
    }
  }
  if (v != 0) {
    (*(void(__thiscall**)(void*))(*(void***)v + 1))(v);
  }
}

// @ 0x00d588a0
namespace SP {
void SetUpCitizenBodyScaleRanges(cSpeciesProfile const * obj, float & out, float & a3, float & a4)
{
  float local_c = *(float*)((char*)obj + 0x554);
  float local_8 = *(float*)((char*)obj + 0x558);
  float local_10 = (local_8 <= local_c) ? local_c : local_8;
  float local_18 = 0.75f;
  float val = *(float*)0x013f08e4;      // default property value
  float e = 0.0f;                        // prop 0x4dbf459 result
  void* holder = 0;
  int* pm = (int*)FUN_0067de30();
  if (holder != 0) {
    holder = 0;
    (*(void(__thiscall**)(void*))(*(void***)holder + 1))(holder);
  }
  if (holder != 0) {
    holder = 0;
    (*(void(__thiscall**)(void*))(*(void***)holder + 1))(holder);
  }
  if ((*(u8(__thiscall**)(int*, u32, void**))(*(int**)pm + 0x30 / 4))(pm, 0xb6a5c63d, &holder) != 0 &&
      holder != 0) {
    int* p1 = 0;
    if ((*(u8(__thiscall**)(void*, u32, int**))(*(int**)holder + 0x24 / 4))(holder, 0x4dbf457, &p1) != 0 &&
        *(short*)((char*)p1 + 0x12) == 0xd) {
      float* f = FUN_0041ea70(p1);
      out = *f;
    }
    if (holder != 0) {
      int* p2 = 0;
      if ((*(u8(__thiscall**)(void*, u32, int**))(*(int**)holder + 0x24 / 4))(holder, 0x4dbf458, &p2) != 0 &&
          *(short*)((char*)p2 + 0x12) == 0xd) {
        float* f = FUN_0041ea70(p2);
        val = *f;
      }
      if (holder != 0) {
        int* p3 = 0;
        if ((*(u8(__thiscall**)(void*, u32, int**))(*(int**)holder + 0x24 / 4))(holder, 0x4dbf459, &p3) != 0 &&
            *(short*)((char*)p3 + 0x12) == 0xd) {
          float* f = FUN_0041ea70(p3);
          e = *f;
        }
        if (holder != 0) {
          int* p4 = 0;
          if ((*(u8(__thiscall**)(void*, u32, int**))(*(int**)holder + 0x24 / 4))(holder, 0x4dbf45a, &p4) != 0 &&
              *(short*)((char*)p4 + 0x12) == 0xd) {
            float* f = FUN_0041ea70(p4);
            val = *f;
          }
        }
      }
    }
  }
  if (local_10 <= local_18) {
    if (val < local_18) {
      out = val / local_18;
    }
  } else {
    out = e / local_18;
  }
  if (holder != 0) {
    (*(void(__thiscall**)(void*))(*(void***)holder + 1))(holder);
  }
}
}  // namespace SP

// @ 0x00d58a80
void __fastcall FUN_00d58a80(CityVis* self, void* edx)
{
    (void)edx;
    PtrVec14* v = &self->mVec170;
    for (int i = 0; i < 2; ++i, --v) {
        void** p = v->mpBegin;
        void** e = v->mpEnd;
        for (; p < e; ++p)
            if (*p)
                ((IObj*)*p)->Slot4();
        if (v->mpBegin && ((uint32_t*)v->mpBegin)[-1] != 0)
            operator_delete_array(v->mpBegin);
    }
    for (int i = 0; i < 2; ++i)
        ((ActionCircle*)((char*)self + 0xf8 - i * 0x64))->Dtor();
    ((ActionCircle*)((char*)self + 0x30))->Dtor();
    ((GonzagoTimer*)((char*)self + 0x10))->Dtor();
}

// @ 0x00d58b10
void __fastcall FUN_00d58b10(CityVis* self, void* edx, uint32_t id)
{
    (void)edx;
    {
        void** begin = self->mpVecA64;
        void** end = self->mpVecA68;
        int n = (int)(end - begin);
        for (uint i = 0; i < (uint)n; ++i) {
            if ((uint32_t)(uintptr_t)begin[i] == id) {
                void* last = end[-1];
                void* cur = begin[i];
                if (last != cur) {
                    if (last)
                        ((IObj*)last)->Slot0();
                    begin[i] = last;
                    if (cur)
                        ((IObj*)cur)->Slot4();
                }
                self->mpVecA68 = end - 1;
                if (*self->mpVecA68)
                    ((IObj*)*self->mpVecA68)->Slot4();
                break;
            }
        }
    }
    {
        void** begin = self->mpVecAC8;
        void** end = self->mpVecACC;
        int n = (int)(end - begin);
        for (uint i = 0; i < (uint)n; ++i) {
            if ((uint32_t)(uintptr_t)begin[i] == id) {
                void* last = end[-1];
                void* cur = begin[i];
                if (last != cur) {
                    if (last)
                        ((IObj*)last)->Slot0();
                    begin[i] = last;
                    if (cur)
                        ((IObj*)cur)->Slot4();
                }
                self->mpVecACC = end - 1;
                if (*self->mpVecACC)
                    ((IObj*)*self->mpVecACC)->Slot4();
                break;
            }
        }
    }
    void* p = id ? (void*)(uintptr_t)(id + 0x58) : 0;
    ((IBehaviorManager*)SP_BehaviorManager())->Slot38(p);
}

// @ 0x00d5bfa0
void cCityVisualizer::FUN_00d5bfa0(char enable)
{
    if (mCity == 0) return;
    int n = (int)(mCitizenEnd - mCitizenBegin);
    int pop = FUN_00d57a00();
    int mag = pop - n;
    bool grow = n < pop;
    if (mag < 0) mag = -mag;
    void* prof = mCity->FUN_00bd9e40();
    if (prof == 0) prof = FUN_00401090()->GetAvatarProfile();
    if (mag != 0) {
        cSim* sim = FUN_00b3d480();
        if (grow) {
            float f1 = g_c0x1485720;
            float f2 = g_c0x13ec480;
            float f3 = g_c0x1485548;
            FUN_00d588a0(prof, &f1, &f2, &f3);
            Vec3 range; Vec3 pos;
            mCity->FUN_00bd7f70(&range, &pos);
            void** members = (void**)mCity->GetMembers();
            for (int i = 0; i < mag; ++i) {
                void* r = sim->UpdateVignettes(0x18eb4b7);
                if (r == 0) continue;
                void* vin = VC1<void*, int>(r, 3, 0x4f176642);
                if (vin == 0) continue;
                float sx, sy, sz;
                if (members[0] == members[1]) {
                    sx = pos.x; sy = pos.y; sz = pos.z;
                } else {
                    u32 k = g_Random.RandomUint32Uniform((u32)(((char*)members[1] - (char*)members[0]) >> 2));
                    float* v = VC0<float*>(&((SubObj*)((char*)members[k] + 0x34))->mVtbl, 11);
                    sx = v[0]; sy = v[1]; sz = v[2];
                }
                Vec3 vpos;
                vpos.x = sx; vpos.y = sy; vpos.z = sz;
                RefCount* rc = (RefCount*)vin;
                if (rc) rc->AddRef();
                if (mCitizenEnd < mCitizenCap) {
                    void** slot = mCitizenEnd;
                    mCitizenEnd = slot + 1;
                    if (slot) {
                        *slot = vin;
                        if (rc) rc->AddRef();
                    }
                } else {
                    ((SPVec*)&mCitizenBegin)->DoInsertPtr(mCitizenEnd, vin);
                }
                if (rc) rc->Release();
                VC4<void, void*, int, int, void*>(vin, 58, mCity, 0, 1, &vpos);   // slot 0xe8
                FUN_00d58c50(vin);
                double rnd = g_Random.RandomDoubleUniform();
                float value = (float)(((rnd * range.y + range.z) - range.y * 0.5f) * pos.x);
                VC1<void, float>((char*)vin + 0xc0, 16, value);                    // slot 0x40
                int emp3 = VC0<int>(mCity->GetCivilization(), 19);
                VC1<void, int>(vin, 18, emp3);                                     // slot 0x48
                ((Entity*)vin)->mFF0 = (void*)emp3;
                if (!VC0<char>((char*)vin + 0xc0, 22)) {                           // slot 0x58
                    Holder180* h = (Holder180*)((Entity*)vin)->mB54;
                    h->mOwner->mFlags |= 0x800;
                }
            }
        } else if (pop >= 0 && pop < (int)(mCitizenEnd - mCitizenBegin)) {
            SPVec* v = (SPVec*)&mCitizenBegin;
            void** it = mCitizenBegin + pop;
            for (; it != mCitizenEnd; ++it) FUN_00d57940(*it);
            v->erase(mCitizenBegin + pop, mCitizenEnd);
        }
    }
    int cnt = (int)(mCitizenEnd - mCitizenBegin);
    for (int i = 0; i < cnt; ++i) {
        Entity* cr = (Entity*)mCitizenBegin[i];
        if (cr->GetSpeciesProfile() != prof) cr->FUN_00c222f0(prof);
    }
    if (enable != 0) {
        SlotVecBuf buf;
        SPVec vec;
        vec.mBegin = (void**)buf.mEntries;
        vec.mCap   = (void**)buf.mEntries;
        mCity->FUN_00bdf750(&vec);
        int cnt2 = (int)(mCitizenEnd - mCitizenBegin);
        void* curPtr = 0;
        int curCnt = 0;
        void* emp2 = VC0<void*>(mCity->GetCivilization(), 19);
        cNounManager* nm = FUN_00b3d300();
        int player = nm->GetPlayerEmpireOrMinus1();
        int mine = (emp2 == (void*)player) ? 1 : 0;
        for (int i = 0; i < cnt2; ++i) {
            if (curCnt == 0) {
                SlotEntry* end = (SlotEntry*)vec.mEnd;
                SlotEntry* bot = (SlotEntry*)vec.mBegin;
                while (end != bot) {
                    SlotEntry* e = end - 1;
                    void* p = e->mPtr;
                    int   c = e->mCount;
                    end = e;
                    vec.mEnd = (void**)end;
                    curPtr = p;
                    curCnt = c;
                    if (c != 0) break;
                }
                if (end == bot) {
                    curPtr = emp2;
                    curCnt = 999;
                }
            }
            Entity* cr = (Entity*)mCitizenBegin[i];
            VC1<void, void*>(cr, 18, emp2);                                   // slot 0x48
            cr->mFF0 = curPtr;
            if (mine) {
                VC1<void, void*>(cr, 57, &g_p0x1583e08);                      // slot 0xe4
                cr->FUN_00c0d950(0);
            } else {
                void* m = mCity->FUN_00bd99e0();
                VC1<void, void*>(cr, 57, m);
                cr->FUN_00c0d950(1);
            }
            --curCnt;
        }
        if (vec.mBegin && ((ArrayHeader*)vec.mBegin)[-1].mAlloc != 0) FUN_00f47380(vec.mBegin);
    }
    int k = mCity->FUN_00bd8160();
    int cnt3 = (int)(mCitizenEnd - mCitizenBegin);
    for (int i = 0; i < cnt3; ++i) {
        ((Entity*)mCitizenBegin[i])->mB62 = (i < k);
    }
}

// @ 0x00d5c470
char cCityVisualizer::FUN_00d5c470(void* a, void* b)
{
    char flag = mCity->m2a0;
    int n = (int)(mElemEnd - mElemBegin);
    if (n <= 0) return 0;
    int off = 0;
    for (int i = 0; i < n; ++i, off += 0x1c) {
        Elem28* e = (Elem28*)((char*)mElemBegin + off);
        if (FUN_00b3d4e0()->FUN_00bc3db0(e->mId) != 0 &&
            (flag == 0 || e->mFlag != 0)) {
            if (FUN_00b3d4e0()->FUN_00bc4900(e->mId, a, b) != 0) {
                --mCountBd0;
                RefCount* r = (RefCount*)a;
                if (r) r->AddRef();
                if (e->mVec.mEnd < e->mVec.mCap) {
                    void** slot = e->mVec.mEnd;
                    e->mVec.mEnd = slot + 1;
                    if (slot) {
                        *slot = r;
                        if (r) r->AddRef();
                    }
                } else {
                    e->mVec.DoInsertPtr(e->mVec.mEnd, r);
                }
                if (r) r->Release();
                return 1;
            }
        }
    }
    return 0;
}

// @ 0x00d5c580
void cCityVisualizer::FUN_00d5c580(void* citizen)
{
    ((Entity*)citizen)->SetCurrentToolEffect(0, -1);
    int n = (int)(mElemEnd - mElemBegin);
    if (n <= 0) return;
    int off = 0;
    do {
        Elem28* e = (Elem28*)((char*)mElemBegin + off);
        void** it = e->mVec.mBegin;
        void** end = e->mVec.mEnd;
        while (it != end) {
            if (*it == citizen) break;
            ++it;
        }
        if (it != end) {
            FUN_00b3d4e0()->FUN_00bc52a0(e->mId, citizen);
            FUN_00d5aae0(&e->mVec, &citizen, citizen);
        }
        off += 0x1c;
    } while (--n != 0);
}

// @ 0x00d5c620
void cCityVisualizer::FUN_00d5c620(void* vec, int count)
{
    VecBuilder tmp((int)(mCitizenEnd - mCitizenBegin), &mAllocA70);
    void* out;
    FUN_00829110(&out, mCitizenBegin, mCitizenEnd, tmp.mBegin, vec);
    FUN_00d5bb50(tmp.mBegin, out, ((float*)vec)[0], ((float*)vec)[1], ((float*)vec)[2]);
    int cnt = (int)((char*)out - (char*)tmp.mBegin) >> 2;
    if (cnt > 0) {
        int i = 0;
        do {
            if (count <= 0) break;
            Entity* cr = ((Entity**)tmp.mBegin)[i];
            StimSet* ss = (StimSet*)((char*)cr->mB4c + 8);
            ss->FUN_00bc97f0(0x2000, 0, 0.25f, 0);
            ++i;
            --count;
        } while (i < cnt);
    }
    for (void** it = (void**)tmp.mBegin; it < (void**)out; ++it) {
        if (*it) ((RefCount*)*it)->Release();
    }
    if (tmp.mBegin && ((ArrayHeader*)tmp.mBegin)[-1].mAlloc != 0) FUN_00f47380(tmp.mBegin);
}

// @ 0x00d5c720
void cCityVisualizer::FUN_00d5c720()
{
    if (mFlagAf5 != 0) return;
    cSim* sim  = FUN_00b3d480();
    void* prof = mCity->FUN_00bd9e40();
    int   emp  = VC0<int>(mCity->GetCivilization(), 19);
    if (prof == 0) prof = FUN_00401090()->GetAvatarProfile();
    float f1 = g_c0x1485720;                               // 1.0
    float f2 = g_c0x13ec480;                               // 0.2
    float f3 = g_c0x1485548;                               // 1.5
    FUN_00d588a0(prof, &f1, &f2, &f3);
    float* pos = VC0<float*>(&mCity->mSub120, 11);
    float px = pos[0], py = pos[1], pz = pos[2];
    for (int i = 0; i < 4; ++i) {
        void* r = sim->UpdateVignettes(0x18eb4b7);
        if (r == 0) continue;
        void* vin = VC1<void*, int>(r, 3, 0x4f176642);
        if (vin == 0) continue;
        FUN_00d57800(vin, this, prof, emp, i, &px, f1, f2, f3);
        RefCount* rc = (RefCount*)vin;
        if (rc) rc->AddRef();
        SPVec* v = &mVignetteVec[i];
        if (v->mEnd < v->mCap) {
            void** slot = v->mEnd;
            v->mEnd = slot + 1;
            if (slot) {
                *slot = rc;
                if (rc) rc->AddRef();
            }
        } else {
            v->DoInsertPtr(v->mEnd, rc);
        }
        if (rc) rc->Release();
    }
    mFlagAf5 = 1;
}

// @ 0x00d5c8c0
void cCityVisualizer::FUN_00d5c8c0()
{
    Vec3 hall; float r;
    mCity->FUN_00bd7f70(&hall, &r);
    void* ch = mCity->GetCityHall();
    float* hp = VC0<float*>(ch, 35);                       // vtable slot 0x8c
    float dx = hp[0] - hall.x;
    float dy = hp[1] - hall.y;
    float dz = hp[2] - hall.z;
    float inv = 1.0f / (float)sqrt((double)(dz * dz + (dx * dx + dy * dy) + g_c0x13ec4b8));

    float d1 = dx * inv, d2 = dy * inv, d3 = dz * inv;
    mCircle0c.SetAtCenter(&hall, r, &d1, 0.0f);
    mCircle0c.FUN_00afef10(3, 2.0f);
    mCircle0c.SetAtCenter(&hall, r, &mCircle0c.mX, 0.0f);
    mCircle0c.FUN_00afd6d0(1.0f, 1.0f, 12);

    float n1 = -mCircle0c.mX;
    float n2 = -mCircle0c.mY;
    float n3 = -mCircle0c.mZ;
    mCircle0c.SetAtCenter(&hall, r, &n1, 0.0f);
    mCircle0c.FUN_00afef10(4, 1.0f);

    float ax = mCircle0c.mA, ay = mCircle0c.mB, az = mCircle0c.mC;
    float ainv = 1.0f / (float)sqrt((double)(ax * ax + ay * ay + az * az) + g_c0x13ec4b8);
    float ux = ax * ainv, uy = ay * ainv, uz = az * ainv;

    float cx = mCircle0c.mB * uz - mCircle0c.mC * uy;
    float cy = mCircle0c.mC * ux - mCircle0c.mX * uz;
    float cz = mCircle0c.mX * uy - mCircle0c.mB * ux;

    float e1 = -cx, e2 = -cy, e3 = -cz;
    float half = r * 0.5f;
    float s1 = cx * half + ax;
    float s2 = cy * half + ay;
    float s3 = cz * half + az;
    float p1 = s1, p2 = s2, p3 = s3;
    mCircle2fc.SetAtCenter(&p1, r * 2.0f, &e1, 0.0f);
    mCircle2fc.FUN_00afef10(4, 1.0f);

    float q1 = ax - cx * half;
    float q2 = ay - cy * half;
    float q3 = az - cz * half;
    mCircle234.SetAtCenter(&q1, r * 2.0f, &cx, 0.0f);
    mCircle234.FUN_00afef10(4, 1.0f);

    void* ch2 = mCity->GetCityHall();
    if (ch2 != 0) {
        Vec3 q;
        VC1<void, void*>(&((SubObj*)((char*)ch2 + 0x34))->mVtbl, 23, &q);      // slot 0x5c
        Vec3 n;
        n.x = -q.x;
        n.y = -q.y;
        n.z = -q.z;
        void* center = VC1<void*, void*>(ch2, 35, &n);                          // slot 0x8c
        mCircleD4.SetAtCenter(center, g_c0x13f7674, &n, 0.0f);
        mCircleD4.FUN_00afd6d0(g_c0x1470f1c, g_c0x1471064, 20);
    }
    FUN_00d5b9f0();
}

// @ 0x00d5d4b0
cActionCircle_s00d5_ccf0& cActionCircle_s00d5_ccf0::operator=(const cActionCircle_s00d5_ccf0& o)
{
    mFacing = o.mFacing;
    mRadius = o.mRadius;
    mSlotRadius = o.mSlotRadius;
    mCenter = o.mCenter;
    mAltitude = o.mAltitude;
    mPacking = o.mPacking;
    mbRelative = o.mbRelative;
    mOrientation = o.mOrientation;
    mAgents = o.mAgents;
    mSlots = o.mSlots;
    return *this;
}

// @ 0x00d5e5c0
void SlotVector::Insert(CitySlot* pPos, const CitySlot* pValue)
{
    if (mpEnd != mpCapacity) {
        const CitySlot* pSource = pValue;
        if (pSource >= pPos && pSource < mpEnd)
            pSource = pSource + 1;

        if (mpEnd != nullptr)
            DestroySlot(&mpEnd[-1]);
        MoveBackwardSlots(pPos, &mpEnd[-1], mpEnd);
        *pPos = *pSource;
        mpEnd = mpEnd + 1;
        return;
    }

    uint32_t nNewCapacity = (uint32_t)(mpEnd - mpBegin);
    if (nNewCapacity == 0) {
        nNewCapacity = 1;
    } else {
        nNewCapacity = nNewCapacity * 2;
    }

    CitySlot* pNew = nullptr;
    if (nNewCapacity != 0) {
        pNew = (CitySlot*)operator_new(nNewCapacity * sizeof(CitySlot), "Simulator", 0, 0,
                                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL"
                                       "\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }

    CitySlot* pPrevBegin = mpBegin;
    CitySlot* pGapEnd = UninitializedCopySlots(pPrevBegin, pPos, pNew);
    DestroyRangeSlots(pPrevBegin, pPos, pNew);
    if (pGapEnd != nullptr)
        DestroySlot((CitySlot*)pValue);

    CitySlot* pPrevEnd = mpEnd;
    CitySlot* pNewEnd = UninitializedCopySlots(pPos, pPrevEnd, pGapEnd + 1);
    DestroyRangeSlots(pPos, pPrevEnd, pGapEnd + 1);

    if (mpBegin != nullptr && *(int32_t*)((uint8_t*)mpBegin - 4) != 0)
        operator_delete(mpBegin);

    mpEnd = pNewEnd;
    mpBegin = pNew;
    mpCapacity = (CitySlot*)((uint8_t*)pNew + nNewCapacity * sizeof(CitySlot));
}

// @ 0x00d5ed70
void Elem1CVec::push_back()
{
    if (mEnd < mCap) {
        Elem1C* p = mEnd;
        mEnd = p + 1;
        new (p) Elem1C();
    } else {
        Elem1C tmp;
        DoInsertValue(mEnd, &tmp);
    }
}

// @ 0x00d5edc0
cActionCircle_s00d5_e730* ActionCircleVec::erase(cActionCircle_s00d5_e730* first, cActionCircle_s00d5_e730* last)
{
    cActionCircle_s00d5_e730* newEnd = FUN_00d5d530(last, mEnd, first);
    cActionCircle_s00d5_e730* e = mEnd;
    while (newEnd < e) {
        newEnd->~cActionCircle_s00d5_e730();
        ++newEnd;
    }
    mEnd -= (last - first);
    return first;
}

// @ 0x00d5fb60
void Viz::Update(u64 t)
{
    City* city = F<City*>(this, 0xaf0);
    if (!city) return;

    int n = (F<int>(this, 0xa68) - F<int>(this, 0xa64)) >> 2;
    if (n != city->GetCreatureCount()) {
        FUN_00d5bfa0(0);
        n = (F<int>(this, 0xa68) - F<int>(this, 0xa64)) >> 2;
    }
    float dt = (float)t * 0.001f;
    SimGlobal* g = FUN_00b3d4d0();

    if (F<char>(city, 0x192) ||
        ((g->mode == 1 || g->mode == 2) && !g->b28 && F<int>(g, 0x160) != 0 && F<int>(g, 0x160) != 2)) {
        if (!F<bool>(this, 0xa10)) {
            ((Stopwatch*)((char*)this + 0x9f8))->Restart();
            F<bool>(this, 0xa10) = true;
        }
        t = ((Stopwatch*)((char*)this + 0x9f8))->GetElapsedTime();
        dt = (float)t * 0.001f;
        ((Stopwatch*)((char*)this + 0x9f8))->Restart();
        if (t != 0) {
            for (u32 i = 0; i < (u32)((F<int>(this, 0xa68) - F<int>(this, 0xa64)) >> 2); i++) {
                void* cr = F<void**>(this, 0xa64)[i];
                FUN_00b4b040(cr ? (char*)cr + 0xc0 : 0, (u32)t, 1);
                VC1_s00d5_fb60<void, u32>(cr, 24, (u32)t);
            }
            n = (F<int>(this, 0xa68) - F<int>(this, 0xa64)) >> 2;
            void* p = FUN_00b33f40();
            if (p) VC2<void, float, int>(p, 9, dt, 0);
        }
    } else {
        F<bool>(this, 0xa10) = false;
    }

    F<bool>(this, 0xaf6) = false;
    u32 flags = 0;
    if (g->mode == 1 || g->mode == 2) flags = 0x8000000;
    if (F<bool>(this, 0xaf4)) flags |= 1;
    if (city->FUN_00bd7df0() && !F<bool>(city, 0x2a0))
        F<int>(this, 0xa3c) = (F<int>(this, 0xc4) - F<int>(this, 0xc0)) / 12;
    else
        F<int>(this, 0xa3c) = 0;
    FUN_00d57e20(F<bool>(this, 0xaf4));
    FUN_00d57ef0(F<bool>(this, 0xaf4));
    bool b16 = F<int>(this, 0xc3c) > -1;
    bool b17 = F<int>(this, 0xa4c) != -1;
    FUN_00d5ef80();
    FUN_00d581b0();
    if (city->FUN_00bd8240()) flags |= 0x400000;
    if (city->FUN_00bd8280()) flags |= 0x2000000;
    if (city->FUN_00bd82c0()) flags |= 0x4000000;
    bool b14 = false;
    F<int>(this, 0xa2c) = 0;
    F<int>(this, 0xa34) = n / 2;
    city->FUN_00bdf7e0((char*)this + 0xb80);
    bool b15 = F<int>(this, 0xb80) != F<int>(this, 0xb84);
    FUN_00d58d50();
    if (F<int>(this, 0xa44) != -1) flags |= 0x10000;
    if (F<bool>(this, 0xa48)) flags |= 0x20000;

    u32 mode = SP_GetCurrentGameMode_s00d5_fb60();
    if (mode == 0x1654c04) {
        city = F<City*>(this, 0xaf0);
        city->FUN_00bdf880((char*)this + 0xb94);
        b14 = F<int>(this, 0xb94) != F<int>(this, 0xb98);
        AllegianceUpdate();
    } else if (mode == 0x1654c05) {
        flags |= SpaceOnlyTick();
        F<int>(this, 0xa3c) = 0;
    }

    Vec3 pos;
    float speed;
    void* owner = F<void*>(F<void*>(this, 0xaf0), 0x298);
    if (owner) {
        Vec3* pp = VC0_s00d5_fb60<Vec3*>(owner, 11);
        pos.x = pp->x; pos.y = pp->y; pos.z = pp->z;
        owner = F<void*>(F<void*>(this, 0xaf0), 0x298);
        F<float>(this, 0xa24) = VC0_s00d5_fb60<float>(owner, 29);
        float d = dt;
        if (F<float>(this, 0xa14) == g_PosX && F<float>(this, 0xa18) == g_PosY && F<float>(this, 0xa1c) == g_PosZ) {
            speed = 0.0f;
        } else {
            float dx = pos.x - F<float>(this, 0xa14);
            float dy = pos.y - F<float>(this, 0xa18);
            float dz = pos.z - F<float>(this, 0xa1c);
            speed = sqrtf(dx * dx + dy * dy + dz * dz) / d;
        }
        flags |= 0x4000;
        F<float>(this, 0xa14) = pos.x;
        F<float>(this, 0xa18) = pos.y;
        F<float>(this, 0xa1c) = pos.z;
    } else {
        F<float>(this, 0xa14) = g_PosX;
        F<float>(this, 0xa18) = g_PosY;
        F<float>(this, 0xa1c) = g_PosZ;
        speed = 0.0f;
        F<float>(this, 0xa24) = 0.0f;
    }
    F<float>(this, 0xa20) = speed;

    float height = (SP_GetCurrentGameMode_s00d5_fb60() == 0x1654c05) ? 15.0f : 3.0f;

    if (dt > 0.0f) {
        for (int i = 0; i < n; i++) {
            void* cr = F<void**>(this, 0xa64)[i];
            if (!VC0_s00d5_fb60<bool>(cr, 11)) {
                StimSet_s00d5_fb60* st = (StimSet_s00d5_fb60*)(F<char*>(cr, 0xb4c) + 8);
                if (F<bool>(this, 0xaf6))
                    st->FUN_00bc97f0(1, 0, FLT_MAX, 0);
                if (F<int>(this, 0x38c))
                    st->FUN_00bc97f0(0x400, 0, 3.0f, 0);
                void* c1 = F<void*>(this, 0xaf0);
                int m = (F<int>(c1, 0x2a8) - F<int>(c1, 0x2a4)) / 20;
                void* sub = (char*)cr + 0xc0;
                Vec3* sp = VC0_s00d5_fb60<Vec3*>(sub, 11);
                Vec3 q;
                q.x = sp->x; q.y = sp->y; q.z = sp->z;
                for (int j = 0; j < m; j++) {
                    float* it = (float*)(F<char*>(F<void*>(this, 0xaf0), 0x2a4) + j * 20);
                    float ix = it[0], iy = it[1], iz = it[2];
                    float dx = ix - q.x, dz = iz - q.z, dy = iy - q.y;
                    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
                    if (it[3] > dist) {
                        Stim* s = st->FUN_00bc97f0(4, 0, 15.0f, 0);
                        if (s) {
                            s->x = ix; s->y = iy; s->z = iz;
                            s->radius = height;
                            s->id = *(int*)(F<char*>(F<void*>(this, 0xaf0), 0x2a4) + j * 20 + 0x10);
                        }
                        break;
                    }
                }
                c1 = F<void*>(this, 0xaf0);
                m = (F<int>(c1, 0x2bc) - F<int>(c1, 0x2b8)) / 20;
                for (int j = 0; j < m; j++) {
                    float* it = (float*)(F<char*>(c1, 0x2b8) + j * 20);
                    float dx = it[0] - q.x, dz = it[2] - q.z, dy = it[1] - q.y;
                    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
                    if (it[3] > dist) {
                        st->ClearAll(4, 0);
                        break;
                    }
                }
                if (SP_GetCurrentGameMode_s00d5_fb60() == 0x1654c05 && SP_SpaceGameGet() && SP_SpaceGameGet()->GetAvatar()) {
                    void* head = SP_SpaceGameGet()->GetAvatar()->FUN_00ff5b80();
                    for (float** node = *(float***)head; node != (float**)head; node = (float**)*node) {
                        void* rp = (char*)F<void*>(this, 0xaf0) + 0x120;
                        Vec3* r = VC0_s00d5_fb60<Vec3*>(rp, 11);
                        float dx = ((float*)node)[3] - r->x;
                        float dz = ((float*)node)[5] - r->z;
                        float dy = ((float*)node)[4] - r->y;
                        if (dx * dx + dz * dz + dy * dy < 10000.0f) {
                            Stim* s = st->FUN_00bc97f0(0x200, 0, 100.0f, 0);
                            if (s) {
                                s->x = ((float*)node)[3];
                                s->y = ((float*)node)[4];
                                s->z = ((float*)node)[5];
                            }
                            float prob = 0.7f;
                            if (VC0_s00d5_fb60<int>(cr, 38) != 5) prob = 0.1387f;
                            double v = sMathRandom.RandomDoubleUniform() * 100.0;
                            if (v < 100.0) {
                                if (v < 0.0) v = 0.0;
                            } else {
                                v = 100.0;
                            }
                            if (prob > v) {
                                Stim* s2 = st->FUN_00bc97f0(4, 0, 100.0f, 0);
                                if (s2) {
                                    s2->x = ((float*)node)[3];
                                    s2->y = ((float*)node)[4];
                                    s2->radius = 100.0f;
                                    s2->z = ((float*)node)[5];
                                    s2->id = SP_GetPlayerEmpireID();
                                }
                            }
                        }
                    }
                }
                c1 = F<void*>(this, 0xaf0);
                if (F<float>(c1, 0x2d4) != g_PosX || F<float>(c1, 0x2d8) != g_PosY || F<float>(c1, 0x2dc) != g_PosZ) {
                    float dx = F<float>(c1, 0x2d4) - q.x;
                    float dy = F<float>(c1, 0x2d8) - q.y;
                    float dz = F<float>(c1, 0x2dc) - q.z;
                    if (sqrtf(dx * dx + dy * dy + dz * dz) < 10.0f) {
                        Stim* s = st->FUN_00bc97f0(0x100, 0, 5.0f, 0);
                        if (s) {
                            s->x = F<float>(F<void*>(this, 0xaf0), 0x2d4);
                            s->y = F<float>(F<void*>(this, 0xaf0), 0x2d8);
                            s->z = F<float>(F<void*>(this, 0xaf0), 0x2dc);
                        }
                    }
                }
                u32 fl = flags;
                if (F<int>(this, 0xa38) < F<int>(this, 0xa3c)) fl |= 4;
                if (F<int>(this, 0x9f0)) fl |= 8;
                if (b14) fl |= 0x40;
                if (b15) fl |= 0x80;
                if (F<int>(this, 0x9f4)) fl |= 0x100;
                if (F<int>(this, 0xbd0)) {
                    if (b16 || b17 || F<bool>(F<void*>(this, 0xaf0), 0x2a0))
                        fl |= 0x800;
                    else if (F<bool>(this, 0xa50))
                        fl |= 0x100000;
                    else
                        fl |= 0x400;
                }
                if (F<int>(this, 0xa28) < F<int>(this, 0xa2c)) fl |= 0x2000;
                if (F<int>(this, 0xa5c) < F<int>(this, 0xa60)) fl |= 0x200000;
                if (F<bool>(cr, 0xfbc))
                    fl |= 0x1000;
                else if (F<int>(this, 0xa30) < F<int>(this, 0xa34))
                    fl |= 0x1000000;
                if (F<bool>(this, 8)) {
                    fl |= 0x200;
                    if (!FUN_00d599a0(cr)) fl |= 0x20;
                }
                char* sp2 = F<char*>(cr, 0xb4c);
                if (*(int*)sp2 != 0) {
                    int tt = ((StimSet_s00d5_fb60*)(sp2 + 8))->FUN_00bc9980(dt);
                    u64 gt = SP_GameTimeManager()->FUN_00b316c0();
                    sp2 = F<char*>(cr, 0xb4c);
                    FUN_00d995f0(dt, (double)gt * 0.001f, (u32)(*(int*)sp2), cr, sp2 + 0x1d0, (u32)(*(int*)(sp2 + 0x5e8)), (u32)fl, (u32)tt);
                }
                void* x = F<void*>(cr, 0xb54);
                if (x) F<int>(x, 0x14c) = 0;
            }
        }

        int m2 = (F<int>(this, 0xacc) - F<int>(this, 0xac8)) >> 2;
        for (int j = 0; j < m2; j++) {
            void* inst = F<void**>(this, 0xac8)[j];
            char* sp2 = F<char*>(inst, 0xb4c);
            if (*(int*)sp2 != 0) {
                int tt = ((StimSet_s00d5_fb60*)(sp2 + 8))->FUN_00bc9980(dt);
                u64 gt = SP_GameTimeManager()->FUN_00b316c0();
                sp2 = F<char*>(inst, 0xb4c);
                FUN_00d995f0(dt, (double)gt * 0.001f, (u32)(*(int*)sp2), inst, sp2 + 0x1d0, (u32)(*(int*)(sp2 + 0x5e8)),
                             (u32)(*(int*)(sp2 + 0x5fc)), (u32)tt);
            }
        }

        void* effMgrOwner = FUN_00b3d480_s00d5_fb60();
        void* profile = F<City*>(this, 0xaf0)->FUN_00bd9e40();
        void* civ = F<City*>(this, 0xaf0)->GetCivilization();
        int civv = VC0_s00d5_fb60<int>(civ, 19);
        if (!profile) profile = FUN_00401090_s00d5_fb60()->GetAvatarProfile();
        float s1 = 1.0f, s2 = 0.2f, s3 = 1.5f;
        SP_SetUpCitizenBodyScaleRanges(profile, &s1, &s2, &s3);
        void* rp = (char*)F<void*>(this, 0xaf0) + 0x120;
        Vec3* rv = VC0_s00d5_fb60<Vec3*>(rp, 11);
        Vec3 rpos;
        rpos.x = rv->x; rpos.y = rv->y; rpos.z = rv->z;

        char* gate = (char*)this + 0x39c;
        char* vecs = (char*)this + 0xa7c;
        for (int k = 0; k < 4; k++, gate += 0x198, vecs += 0x14) {
            if (F<int>(gate, -8) < F<int>(gate, -4)) {
                Timer* tm = (Timer*)(gate + 4);
                if (tm->IsRunning()) {
                    u64 el = tm->GetElapsedTime();
                    if (el <= (u64)F<u32>(gate, 0)) continue;
                }
                void* mgr = ((EffMgr*)effMgrOwner)->FUN_00ad11f0(0x18eb4b7);
                if (mgr) {
                    void* eff = VC1_s00d5_fb60<void*, u32>(mgr, 3, 0x4f176642);
                    if (eff) {
                        FUN_00d57800(eff, this, profile, civv, k, &rpos, s1, s2, s3);
                        VC0_s00d5_fb60<void>(eff, 0);                    // AddRef (temp AutoRefCount)
                        void* tmp = eff;
                        void** endp = F<void**>(vecs, 0);
                        if (endp < F<void**>(vecs, 4)) {
                            F<void**>(vecs, 0) = endp + 1;
                            if (endp) {
                                *endp = eff;
                                VC0_s00d5_fb60<void>(eff, 0);            // AddRef
                            }
                        } else {
                            FUN_00aea5d0_push(vecs - 4, endp, &tmp);
                        }
                        if (tmp) VC0_s00d5_fb60<void>(tmp, 1);           // Release temp
                        F<int>(gate, 0) = 100;
                        tm->Restart();
                    }
                }
            }
        }

        u32 flags2 = flags | 0x8000;
        char* gate2 = (char*)this + 0x398;
        char* vecs2 = (char*)this + 0xa7c;
        for (int k = 0; k < 4; k++, gate2 += 0x198, vecs2 += 0x14) {
            char* gp = (char*)F<City*>(this, 0xaf0)->FUN_00bd8d60(k);
            if (F<int>(gp, 0x1d8) == 2 || F<int>(gate2, -8) > 0) {
                F<int>(gate2, 0) = 10;
                void** it = F<void**>(vecs2, -4);
                void** end = F<void**>(vecs2, 0);
                for (; it != end; it++) {
                    void* cr = *it;
                    if (F<bool>(this, 8)) flags2 |= 0x200;
                    char* sp2 = F<char*>(cr, 0xb4c);
                    if (*(int*)sp2 != 0) {
                        int tt = ((StimSet_s00d5_fb60*)(sp2 + 8))->FUN_00bc9980(dt);
                        u64 gt = SP_GameTimeManager()->FUN_00b316c0();
                        sp2 = F<char*>(cr, 0xb4c);
                        FUN_00d995f0(dt, (double)gt * 0.001f, (u32)(*(int*)sp2), cr, sp2 + 0x1d0, (u32)(*(int*)(sp2 + 0x5e8)),
                                     (u32)flags2, (u32)tt);
                    }
                }
            }
        }
    }

    FUN_00d58ea0();
    UpdateBackgroundNoise();
    F<bool>(F<void*>(this, 0xaf0), 0x2a0) = false;
    {
        char* c = (char*)F<void*>(this, 0xaf0);
        // eastl::vector<20-byte>::clear(): erase(begin, end) -> end = begin
        F<int>(c, 0x2a8) += ((F<int>(c, 0x2a4) - F<int>(c, 0x2a8)) / 20) * 20;
        c = (char*)F<void*>(this, 0xaf0);
        F<int>(c, 0x2bc) += ((F<int>(c, 0x2b8) - F<int>(c, 0x2bc)) / 20) * 20;
    }
    {
        char* c = (char*)F<void*>(this, 0xaf0);
        F<float>(c, 0x2d4) = g_PosX;
        F<float>(c, 0x2d8) = g_PosY;
        F<float>(c, 0x2dc) = g_PosZ;
    }
    F<bool>(this, 0xaf4) = false;
    F<bool>(this, 8) = false;
    void* old = F<void*>(this, 0x38c);
    F<void*>(this, 0x38c) = 0;
    if (old) VC0_s00d5_fb60<void>(old, 48);
}
