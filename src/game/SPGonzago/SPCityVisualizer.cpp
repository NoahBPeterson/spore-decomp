// src/game/SPGonzago/SPCityVisualizer.cpp -- migrated from slice(s) s00d60ce0, s00d5a260, s00d5b0c0, s00d59b00, s00d56c30, s00beb6d0, s00af9aa0, s00ad0510, s00ace5a0, s00acc140, s00ac7ab0, s00d5fb60, s00d5e730, s00d5d880, s00d5ccf0, s00d5bfa0, s00d58a80, s00d57b50, s00ad20e0, s00acf4c0, s00acd4a0, s00ac8d00, s00ac4060 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityVisualizer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_167a3d0[];

#include "game/types.h"
struct RefPtr; struct RefPtrVector;   // used by the forward prototype of EraseRefValue (0x00d5aae0) before s00d5a260's stubs

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
#include "SP/cHerd.h"
#include "SP/cSpeciesArchetype.h"
#include "SP/cVarListSerializer.h"
#include "cSPVector3.h"
#include "SP/cGameData.h"
#include "SP/cSpatialObject.h"
#include "SP/cCityTerritory.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cLocomotiveObject.h"
#include "cSPQuaternion.h"

struct CastingArchiveStreamHolder {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void* GetStream(); // +0x18
};
struct CastingArchive {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7();
    virtual CastingArchiveStreamHolder* GetStreamHolder(); // +0x20
};
extern SP::cDataSerializerGeneric gCastingSerializerList[]; // 0x01565d68

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
struct CGSub { void FUN_00d57a60(void* v); };
struct CGSub2 { void FUN_00d61880(); };
struct CCity { void* GetCivilization(int a); };
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
extern "C" void  ReadInt32(void* s, void* v, int one, int zero);     // 0x93a780
extern "C" void* SP_NounManager();                                   // 0xb3d300
extern "C" void  SP_cGameNounManager_RemoveNoun(void* mgr, int noun);// 0xb225d0
extern "C" void* SP_cSPLivingUniverse_GetActivePlanet();             // 0x1021260
extern "C" void* SP_GetCurrentGameMode();                            // 0xb5b800
extern "C" void* FUN_00b33f40();                                     // 0xb33f40
extern "C" void  FUN_00a02c30(void* p);                              // 0xa02c30
extern "C" void  SP_cAnimatingCreature_Release(void* p);            // 0xa05270
extern "C" void  FUN_009cb4f0(void* p);                              // 0x9cb4f0
extern "C" void  FUN_00acc9b0(int n);                                // 0xacc9b0
extern "C" void  SP_cVarListSerializer_ctor(void* s, void* a, void* b, int c); // 0x692f90
extern "C" char  SP_cVarListSerializer_Serialize(void* s, void* p);   // 0x693e10
extern "C" void  SP_cGonzagoSubsystem_dtor(void* p);                 // 0xb5b9a0
extern "C" int   FUN_00ac9310(int a, void* b, bool c);               // 0xac9310
extern "C" int   FUN_00acbed0(int* a, int* b);                       // 0xacbed0
extern "C" int   FUN_00acbf30(int* a, int n, void* v);               // 0xacbf30
extern "C" void  FUN_00acb490(void* a);                              // 0xacb490
extern "C" int   FUN_00acc8c0(int* a, void* b, int c);               // 0xacc8c0
extern "C" void  FUN_00accd70(int* a, int* b);                       // 0xaccd70
extern "C" void  FUN_00ac9d30(int* a, void* b);                      // 0xac9d30
extern "C" void  FUN_00aca7b0(int* a, int* b);                       // 0xaca7b0
extern "C" void  FUN_00aca820(int* a, int* b);                       // 0xaca820
extern "C" void  FUN_00ae6970(void* a);                              // 0xae6970
extern "C" void  FUN_00ac9d90(void* p);                              // 0xac9d90
extern "C" void  FUN_00b95070(void* a);                              // 0xb95070
extern "C" int   FUN_007c4900(void* a, void* b);                     // 0x7c4900
extern float DAT_0167a390, DAT_0167a394, DAT_0167a398;
extern "C" int* eastl_copy_dummy(int* a, int* b, int* c);   // 0x6782c0
extern "C" void FUN_01008600(void* p);   // 0x1008600
extern "C" int  FUN_00ac9480(int* p);    // 0xac9480
extern "C" void* FUN_00c70c10(void* planet);   // 0xc70c10
extern int DAT_01565cfc;
extern "C" char FUN_00d58460(void* p);                // 0xd58460
extern "C" int  FUN_00acb190(void* a, int* b);        // 0xacb190
extern "C" void FUN_00d5fb60(void* self, int a, int b);   // 0xd5fb60
extern "C" void FUN_00d60f00(void* self, int c);          // 0xd60f00
extern "C" void* SP_cGameNounManager_GetGameDataVector(void* mgr, void* a, void* b, void* c, void* d, void* e); // 0xb21340
extern int DAT_0168d248;
typedef unsigned int   uint32;
typedef unsigned char  byte;
struct RCObj { virtual void AddRef(); virtual void Release(); };
struct Pair {
    void* mpVtbl;   // +0x00
    byte  mb4;      // +0x04
    char  pad[3];
    RCObj* mp8;     // +0x08
};
extern "C" void* SP_App_s00ac_d4a0();                                           // 0x67dd10
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
struct Vec3_s00ac_d4a0 {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    void FUN_00acd920(unsigned n);
};
struct CSet {
    char pad0[4];
    int*  mp4;      // +0x04
    int   m8;       // +0x08
    int FUN_00ace170(int* p);
};
struct GonzagoSub2 {
virtual void g00();
virtual void g04();
virtual void g08();
virtual void g0c();
    void FUN_00ace320();
};
struct CCityOwner {
    char pad0[0xa4];
    void* mpA4;      // +0xa4
    void FUN_00ace4e0(void* param_2);
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
extern "C" void*   __cdecl App();                       // 0x0067dd10
extern "C" void*   __cdecl GetCurrentGameModeAlt();     // 0x00b5b820
extern "C" void*   __cdecl MessageServer();             // 0x0067dcc0
extern "C" void*   __cdecl FUN_00b3d320();              // 0x00b3d320
extern "C" void*   __stdcall FUN_00ad11f0(void*);      // 0x00ad11f0
extern "C" void*   __cdecl GetUniverseContext();        // 0x1021080
extern "C" void    __cdecl FUN_00951bf0(void*, void*, void*); // 0x00951bf0
extern int   g_167a4b8;   // 0x0167a4b8  (lazy-init bitfield)
extern int   g_167a4b4;   // 0x0167a4b4
extern int   g_167a4b0;   // 0x0167a4b0
extern int   g_1565d08;   // 0x01565d08
extern int   g_1565d00;   // 0x01565d00
extern int   g_167a37c;   // 0x0167a37c
extern int   g_167a380;   // 0x0167a380
extern int   g_167a384;   // 0x0167a384
extern float kf_1565d5c;  // 0x01565d5c
extern float kf_1565d60;  // 0x01565d60
typedef unsigned char uchar;
typedef void* (__thiscall *TC_p0)(void*);
typedef void  (__thiscall *TC_v1)(void*, void*);
typedef void* (__thiscall *TC_p1)(void*, void*);
typedef void  (__thiscall *TC_v5)(void*, void*, void*, void*, void*);
#define VTC(obj, off, type) ((type)(*(void***)(obj))[((off) >> 2)])
extern void* g_15fd918_s00ad_20e0;   // 0x015fd918  (property-list pointer)
struct Vec3 { float x, y, z; };
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
struct Vec14 {                // the +0x20 vector
    Element14* begin;
    Element14* end;
    Element14* cap;
    void insert(Element14*, Element14*);  // 0x00acb680
};
struct Sub88 {                // embedded registry accessor at +0x88
    RegList* get(void* ctx);  // 0x00ad0ca0
};
struct B1de80 { void* fn2(); };        // 0x00b1de80
struct Rel    { void release(void*); }; // 0x00c96e80 (this=arg0, 1 stack arg)
struct CDPL   { int GetIntProperty(void*); }; // 0x006a2660
struct VTag {
virtual void  d0();
virtual void  d1();
virtual void  d2();
virtual void  d3();
virtual void  d4();
virtual void  d5();
virtual void  d6();
virtual void  d7();
    virtual void* v8();       // +0x20
};
struct ElemObj { int get(); };   // 0x00c0b760 (ecx = element)
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
struct cViewer2 { void GetCameraLocationInfo(Vec3*, int, int, int); }; // 0x007c3d30
struct VMsg   { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
                virtual void d8(); virtual void v9(void*, void*); };   // slot 9 (+0x24)
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
u32   __cdecl FUN_00a68fb0(void* self, u32 n);         // 0x00a68fb0 RandomUint32Uniform (thiscall)
s32   __cdecl FUN_00c0b780(void* self);                // 0x00c0b780 (thiscall)
s32   __cdecl FUN_00c0b7a0(void* self);                // 0x00c0b7a0 (thiscall)
s32   __cdecl FUN_008e7f80(void* self);                // 0x008e7f80 GetFileCount (thiscall)
void  __cdecl FUN_00ae6690(void* p);                   // 0x00ae6690
void* __cdecl FUN_00b3d350();                          // 0x00b3d350 SP::PlanetModel
void  __cdecl FUN_00b7f250(void* pm, void* out, void* pos, void* dir); // 0x00b7f250 BuildSurfaceOrientation2
char  __cdecl FUN_00ac0730(void* a, void* b);          // 0x00ac0730
void* __cdecl FUN_0067de30();                          // 0x0067de30 PropertyManager
float* __cdecl FUN_0041ea70(void* p);                  // 0x0041ea70 Property::GetFloat (thiscall)
// ---- items of slice s00d57b50 end

// ---- items of slice s00d58a80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char   gAbandonedVtbl;   // 0x0147b9ec
extern float  gConst77FBC;      // 0x01477fbc (200.0f)
extern float  gConst853E0;      // 0x014853e0 (4.0f)
typedef unsigned int uintptr_t;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vector3_s00d5_8a80 {
    float x, y, z;
    Vector3_s00d5_8a80() {}
    Vector3_s00d5_8a80(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
struct IObj {
    virtual void Slot0();               // 0x00
    virtual void Slot4();               // 0x04
    virtual void Slot8();               // 0x08
    virtual void* SlotC();              // 0x0c
};
struct ISpat2 {
    PV8 PV2 PV                                  // 0x00..0x28
    virtual Vector3_s00d5_8a80* Get2c();                   // 0x2c
    PV8 PV4 PV2 PV                              // 0x30..0x68
    virtual void* Get6c();                      // 0x6c (object with a float at +0x25c)
    PV                                          // 0x70
    virtual float Get74();                      // 0x74
    PV4 PV                                      // 0x78..0x88
    virtual Vector3_s00d5_8a80* Get8c();                   // 0x8c
    PV8 PV4 PV2                                 // 0x90..0xc4
    virtual void SlotC8(int a);                 // 0xc8
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
struct Rec1C {
    uint32_t m00;                               // +0x00
    uint8_t  m04;                               // +0x04
    uint8_t  pad05[3];                          // +0x05..+0x07
    int*     mp08;                              // +0x08
    int*     mp0C;                              // +0x0c
    uint8_t  pad10[0x0c];                       // +0x10..+0x1b
};
struct CityCircle {
    uint8_t  pad00[0x50];
    uint8_t* mBegin50;                          // +0x50
    uint8_t* mEnd54;                            // +0x54
};
struct CityVis {
    void FUN_00d590b0(int param_2, Vector3_s00d5_8a80* param_3, float param_4);   // 0x00d590b0
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
struct Creature {
    uint8_t   pad00[0x58];
    uint32_t  mField58;                         // +0x58
    uint8_t   pad5C[0x64];                      // +0x5c..+0xbf
    uint8_t   mLocoC0[0x50];                    // +0xc0 (cLocomotiveObject)
    uint32_t  mFlags110;                        // +0x110
    uint8_t   pad114[0xa38];                    // +0x114..+0xb4b
    void*     mpB4C;                            // +0xb4c
    uint8_t   padB50[0x0e];                     // +0xb50..+0xb5d
    uint8_t   mByteB5E;                         // +0xb5e
    uint8_t   padB5F[0x459];                    // +0xb5f..+0xfb7
    uint32_t  mFB8;                             // +0xfb8
    uint8_t   mFBC;                             // +0xfbc
};
struct CVec {
    void**   mpBegin;                           // +0x00
    void**   mpEnd;                             // +0x04
    void**   mpCap;                             // +0x08
    uint32_t m0C;                               // +0x0c
    uint32_t m10;                               // +0x10
};
struct VecP {
    uint32_t m00;                               // +0x00
    void**   mpBegin;                           // +0x04
    void**   mpEnd;                             // +0x08
};
void*       operator_new(int size, const char* category, int a, int b,
                         const char* file, int line);                      // 0x00f473a0
void*       SP_BehaviorManager();                                          // 0x00b3d260
void*       FUN_00b3d310(void);                                            // 0x00b3d310
void        FUN_00b48770(void);                                            // 0x00b48770
void        FUN_00c0d3a0(void);                                            // 0x00c0d3a0
void        FUN_00bcb660(void);                                            // 0x00bcb660
void*       FUN_00c0bbd0(void);                                            // 0x00c0bbd0
void*       FUN_00c14350(void);                                            // 0x00c14350
void        FUN_00c421b0(void);                                            // 0x00c421b0
void        FUN_00d584b0(void);                                            // 0x00d584b0 (cCitizenLocomotion ctor)
void*       FUN_00bd7f40(void);                                            // 0x00bd7f40
void*       FUN_00fcc210(void);                                            // 0x00fcc210
uint32_t    FUN_00a68fb0(void);                                            // 0x00a68fb0 (RandomUint32Uniform)
void*       FUN_00c8e810(void);                                            // 0x00c8e810 (cTribe::GetMembers)
int         FUN_008e7f80(void);                                            // 0x008e7f80 (GetDamageState)
void        FUN_00bd9480(void* out);                                      // 0x00bd9480
void*       FUN_00bd9b40(void);                                            // 0x00bd9b40 (cCity::GetCityHall)
char        FUN_00c0b7a0(void);                                            // 0x00c0b7a0
void        FUN_00c42140(void (*fn)());                                    // 0x00c42140
void        FUN_00b4c7c0(void);                                            // 0x00b4c7c0
void*       FUN_00bc97f0(void);                                            // 0x00bc97f0
void        FUN_00829110(void* out, void* a, void* b, void* c, void* d);   // 0x00829110
void        FUN_00951740(void* out, void* a, void* b, void* c, void* d);   // 0x00951740
int         FUN_00ac0730_s00d5_8a80(void* a, void* b);                                // 0x00ac0730
void        FUN_00d587e0(void);                                            // 0x00d587e0
struct Thiscall {
    void*    FUN_00b3d310(void* a, int b);               // 0x00b3d310
    void     FUN_00b48770();                             // 0x00b48770
    void     FUN_00c0d3a0();                             // 0x00c0d3a0
    void     FUN_00bcb660(void* a);                      // 0x00bcb660
    void*    FUN_00c0bbd0();                             // 0x00c0bbd0
    void*    FUN_00c14350();                             // 0x00c14350
    void     FUN_00c421b0(void* a);                      // 0x00c421b0
    void*    FUN_00bd7f40();                             // 0x00bd7f40
    void*    FUN_00fcc210();                             // 0x00fcc210
    uint32_t FUN_00a68fb0(int n);                        // 0x00a68fb0
    void*    FUN_00c8e810();                             // 0x00c8e810
    void     FUN_00b93c60(int count, void* data);        // 0x00b93c60
    void     FUN_00d584b0(void* a);                      // 0x00d584b0
    void*    FUN_00c0b7a0();                             // 0x00c0b7a0 (returns char)
    void*    FUN_008e7f80();                             // 0x008e7f80
};
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
class IGameObject {
public:
    virtual void* Slot00();                         // +0x000
    virtual void Release();                         // +0x004
    virtual void SetActive(bool bActive);           // +0x008
    virtual void* Slot0c(int32_t nFlags);           // +0x00c
    virtual void* Slot10();                         // +0x010
    virtual void Slot14();                          // +0x014
    virtual void Slot18();                          // +0x018
    virtual void Slot1c();                          // +0x01c
    virtual void Slot20();                          // +0x020
    virtual void Slot24();                          // +0x024
    virtual void Slot28();                          // +0x028
    virtual void* Slot2c();                         // +0x02c
    virtual void Slot30();                          // +0x030
    virtual void* Slot34();                         // +0x034
    virtual void Slot38();                          // +0x038
    virtual void Slot3c();                          // +0x03c
    virtual void* Slot40();                         // +0x040
    virtual void Slot44();                          // +0x044
    virtual void Slot48();                          // +0x048
    virtual void* Slot4c();                         // +0x04c
    virtual void Slot50();                          // +0x050
    virtual void Slot54();                          // +0x054
    virtual void Slot58();                          // +0x058
    virtual void* Slot5c();                         // +0x05c
    virtual void Slot60();                          // +0x060
    virtual void Slot64();                          // +0x064
    virtual void Slot68();                          // +0x068
    virtual void Slot6c();                          // +0x06c
    virtual void Slot70();                          // +0x070
    virtual void* Slot74();                         // +0x074
    virtual void Slot78();                          // +0x078
    virtual void Slot7c();                          // +0x07c
    virtual void Slot80();                          // +0x080
    virtual void Slot84();                          // +0x084
    virtual void Slot88();                          // +0x088
    virtual void Slot8c();                          // +0x08c
    virtual void Slot90();                          // +0x090
    virtual void Slot94();                          // +0x094
    virtual void Slot98();                          // +0x098
    virtual void Slot9c();                          // +0x09c
    virtual void SlotA0();                          // +0x0a0
    virtual void SlotA4();                          // +0x0a4
    virtual void SlotA8();                          // +0x0a8
    virtual void SlotAc();                          // +0x0ac
    virtual void SlotB0();                          // +0x0b0
    virtual void SlotB4();                          // +0x0b4
    virtual void SlotB8();                          // +0x0b8
    virtual void SlotBc();                          // +0x0bc
    virtual void* SlotC0();                         // +0x0c0
    virtual void SlotC4();                          // +0x0c4
    virtual void SlotC8();                          // +0x0c8
    virtual void SlotCc();                          // +0x0cc
    virtual void SlotD0();                          // +0x0d0
    virtual void SlotD4();                          // +0x0d4
    virtual void SlotD8();                          // +0x0d8
    virtual void SlotDc();                          // +0x0dc
    virtual void SlotE0();                          // +0x0e0
    virtual void SlotE4();                          // +0x0e4
    virtual void SlotE8();                          // +0x0e8
    virtual void SlotEc();                          // +0x0ec
    virtual void SlotF0();                          // +0x0f0
    virtual void SlotF4();                          // +0x0f4
    virtual void SlotF8();                          // +0x0f8
    virtual void SlotFc();                          // +0x0fc
    virtual void Slot100();                         // +0x100
    virtual void Slot104();                         // +0x104
    virtual void Slot108();                         // +0x108
    virtual void Slot10c();                         // +0x10c
    virtual void Slot110();                         // +0x110
    virtual void Slot114();                         // +0x114
    virtual void Slot118();                         // +0x118
    virtual void Slot11c();                         // +0x11c
    virtual void* Slot120();                        // +0x120
};
class cSPTimer {
public:
    int64_t GetElapsedTime();       // 0x00bc3190
    void Restart();                 // 0x00bc3130
    uint8_t mPad00[0x10];
};
class cCity_s00d5_d880 {
public:
    IGameObject* GetCivilization();     // 0x00d2f9a0 region
};
class IGameObject;
static inline cCity_s00d5_d880* AsCity(IGameObject* pObject)
{
    return (cCity_s00d5_d880*)pObject;
}
struct Vector3_s00d5_d880 {
    float x;
    float y;
    float z;
};
class cPlanetModel_s00d5_d880 {
public:
    Vector3_s00d5_d880* DirectionToSurfacePosition(Vector3_s00d5_d880* pOut, const Vector3_s00d5_d880* pDir);  // 0x00b815a0 (cPlanetModel::DirectionToSurfacePosition)
};
class cActionCircle_s00d5_d880 {
public:
    void RemoveAgent(void* pAgent);  // 0x00afae50 (cActionCircle::RemoveAgent)
};
class cGameNounManager_s00d5_d880 {
public:
    void** GetGameDataVector(int32_t nFilter, void* pA, void* pB, void* pC, uint32_t nKey);  // 0x00b21340 (cGameNounManager::GetGameDataVector)
};
class cAudioSystem {
public:
    IGameObject* GetSystemAT();
};
void __cdecl operator_delete(void* pBlock);         // 0x00f47380
class FixedVector3s {
public:
    FixedVector3s()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 100;
    }

    ~FixedVector3s()
    {
        if (mpBegin != mBuffer && mpBegin != nullptr)
            operator_delete(mpBegin);
    }

    void push_back(const Vector3_s00d5_d880& rValue)
    {
        if (mpEnd < mpCapacity) {
            *mpEnd = rValue;
            ++mpEnd;
        }
    }

    Vector3_s00d5_d880* mpBegin;           // +0x000
    Vector3_s00d5_d880* mpEnd;             // +0x004
    Vector3_s00d5_d880* mpCapacity;        // +0x008
    Vector3_s00d5_d880 mBuffer[100];       // +0x00c
};
class IntVector {
public:
    int32_t* mpBegin;
    int32_t* mpEnd;
    int32_t* mpCapacity;
    uint8_t mAllocator[0x0c];
};
void* __cdecl operator_new(size_t nSize, const char* pName, int32_t nA,
                           int32_t nB, const char* pFile, int32_t nLine);   // 0x00f473a0
IGameObject* __cdecl EffectsManager();              // 0x0067ddd0
IGameObject* __cdecl NounManager_s00d5_d880();                 // 0x00b25f40 region
IGameObject* __cdecl PlanetModel_s00d5_d880(Vector3_s00d5_d880* pOut, IGameObject* pTarget);       // 0x00b81630
bool __cdecl FUN_00cf74c0();                        // 0x00cf74c0
bool __cdecl FUN_00cf7a90();                        // 0x00cf7a90
void __cdecl FUN_00bdf750(IntVector* pIds);         // 0x00bdf750
IGameObject* __cdecl FUN_00b25f40(void* pNoun);     // 0x00b25f40
void* __cdecl FUN_00d5d430(void* pKey);             // 0x00d5d430
bool __cdecl FUN_00bec0f0(IGameObject* pOwner);     // 0x00bec0f0
IGameObject* __cdecl FUN_00bd7f50();                // 0x00bd7f50
IGameObject* __cdecl FUN_00af9f60();                // 0x00af9f60
int32_t __cdecl FUN_00afad30(IGameObject* pAgent);  // 0x00afad30
void __cdecl FUN_00c70110(IGameObject* pObject);    // 0x00c70110
void __cdecl FUN_00af9cf0(IGameObject* pOwner, const Vector3_s00d5_d880* pDir, int32_t nA,
                          void* pOut);              // 0x00af9cf0
void __cdecl FUN_00afd6d0(uint32_t nA, uint32_t nB, int32_t nC);            // 0x00afd6d0
double __cdecl RandomDoubleUniform();                                       // 0x00b3d3a0
extern Vector3_s00d5_d880 gEmptyPoint;                     // 0x0169ec28
class cCityVisualizer_s00d5_d880 {
public:
    void AllegianceUpdate();            // 0x00d5d880
    void UpdateArtifacts();             // 0x00d5de40
    int32_t SpaceOnlyTick();            // 0x00d5e0c0

    uint8_t mPad000[0x138];         // +0x0000
    float mDestX;                   // +0x0138
    float mDestY;                   // +0x013c
    float mDestZ;                   // +0x0140
    uint8_t mPad144[0x64];          // +0x0144
    int32_t mnArtifactTick;         // +0x01a8
    uint32_t mnSoundId;             // +0x01ac
    float mNewX;                    // +0x01b0
    float mNewY;                    // +0x01b4
    float mNewZ;                    // +0x01b8
    uint8_t mPad1bc[0x8a8];         // +0x01bc
    void** mppSirenIds;             // +0x0a64
    void** mppSirenEnd;             // +0x0a68
    uint8_t mPadA6c[0x84];          // +0x0a6c
    IGameObject* mpCity;            // +0x0af0
    uint8_t mPadAf4[0x02];          // +0x0af4
    bool mbArtifactReady;           // +0x0af6
    uint8_t mPadAf7[0x01];          // +0x0af7
    float mPacking;                 // +0x0af8
    void* mpAudioHandle;            // +0x0afc
    uint8_t mPadB00[0x4c];          // +0x0b00
    cAudioSystem* mpAudioSystem;    // +0x0b4c
    uint8_t mPadB50[0x0c];          // +0x0b50
    IGameObject* mpParticleEffect;  // +0x0b5c
    uint8_t mPadB60[0x100];         // +0x0b60
    int32_t mnWorshipCountdown;     // +0x0c60
    uint8_t mPadC64[0x04];          // +0x0c64
    cSPTimer mArtifactTimer;        // +0x0c68
};
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

// ---- items of slice s00ac7ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  WriteUint32(void* stream, void* pValue, int one, int zero); // 0x93aa70
extern "C" void* operator_new6(int size, const char* tag, int a, int b, int c, int d); // 0xf473a0
extern "C" void  LoadArithmeticaFile(int a, int b, void* p);              // 0x7f2240
extern "C" void* FUN_00b95050(void* self);                     // 0xb95050
extern "C" void* FUN_00b93810(void* self, float a, float b);   // 0xb93810
extern "C" void* FUN_00b93840(void* self, float a, float b);   // 0xb93840
extern "C" void* FUN_00b94a90(void* self, float a, float b);   // 0xb94a90
extern "C" void  FUN_00b981a0(void* self, int idx, void* v);   // 0xb981a0
extern "C" void FUN_00d59200(void* p);                                        // 0xd59200
extern "C" void SP_cVarListSerializer_ctor(void* self, void* a, void* b, int c);  // 0x692f90
extern "C" char SP_cVarListSerializer_Serialize(void* self, void* p);              // 0x692900
extern "C" char FUN_00b930c0(void* p);                                             // 0xb930c0
extern "C" char FUN_00c24560(void* p);                       // 0xc24560
extern "C" float FUN_00572a10(float a, float b);             // 0x572a10
extern "C" void SP_cSPCreatureCitizen_GiveOrder(void* self, int order, int a, int b); // 0xc275b0
extern "C" void FUN_00c0ba10(void* p);                       // 0xc0ba10
extern "C" void* SP_cSPCreatureCitizen_GetTribe(void* p);    // 0xc22f50
extern "C" float FUN_00c91c80(void* tribe);                  // 0xc91c80
extern float  DAT_0167a364, DAT_0167a368, DAT_0167a36c, DAT_0167a370, DAT_0167a374;
extern "C" void FUN_00d5bfa0(int v);                          // 0xd5bfa0
#pragma intrinsic(_ReadWriteBarrier)
struct IObj_s00ac_7ab0 {                                  // +0x00 arg char, +0x18 ret ptr, +0x20 ret int
    virtual char  b00(void* v);
    virtual char  b04(void* v);
    virtual char  b08();
    virtual char  b0c(wchar_t* v);
    virtual void  b10();
    virtual void  b14();
    virtual void* b18();
    virtual void  b1c();
    virtual int   b20();
};
struct CVis {
    char  pad0[0xa4];
    void* mpA4;                 // +0xa4
    char  pad1[0xbc - 0xa8];
    void* mpBC;                 // +0xbc
    char  pad1b[0x12c - 0xc0];
    int   m12c;                 // +0x12c
    char  pad2[0x160 - 0x130];
    int   m160;                 // +0x160
    int*  FUN_00ac84d0(int which);
    void  FUN_00ac86b0(int v);
    void  FUN_00ac8130();
    void  FUN_00ac84f0(IObj_s00ac_7ab0* p);
    void  FUN_00ac8cd0(int a, int b);
};
struct CCityVis2 { void CitizenNeedsRemoval(IObj_s00ac_7ab0* p); };
struct CReceiver  { void FUN_00d59200(IObj_s00ac_7ab0* p); };
struct CG         { void FUN_00d5bfa0(int b); };
struct CDirectPropertyList {
    void GetIntProperty(int id);          // 0x6a2660
};
extern CDirectPropertyList* g_15fd918;
extern uint32 DAT_0167a38c;
extern uint32 DAT_0167a388;
// ---- items of slice s00ac7ab0 end

// ---- items of slice s00acc140 begin (TODO(rewrite): local stubs, replace by canonical classes)
static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }
struct StageRec {                       // 0x0c record in a sorted map node
    int   mPad0;                        // +0x00
    uchar mActive;                      // +0x04
    uchar mPad5[3];
    void* mpStage;                      // +0x08
};
struct MapNode {                        // 0x20 sorted key node at this+0x88
    int        mKey;                    // +0x00
    uchar      mPad04[4];               // +0x04
    uchar      mFlag8;                  // +0x08
    uchar      mFlag9;                  // +0x09
    uchar      mPad0a[2];
    StageRec*  mpRecordsBegin;          // +0x0c
    StageRec*  mpRecordsEnd;            // +0x10
    StageRec*  mpRecordsCap;            // +0x14
    uchar      mPad18[8];               // +0x18
};
struct HashNode {                       // 0x6c bucket-chain node at this+0xc4
    uchar       mPad00[0x54];           // +0x00
    void**      mpBegin;                // +0x54
    void**      mpEnd;                  // +0x58
    void**      mpCap;                  // +0x5c
    uchar       mPad60[8];              // +0x60
    HashNode*   mpNext;                 // +0x68
};
struct StageList {                      // 0x18 block in the vector at this+0xa8
    void*   mpOwner;                    // +0x00
    void**  mpBegin;                    // +0x04
    void**  mpEnd;                      // +0x08
    void**  mpCap;                      // +0x0c
    uchar   mPad10[8];                  // +0x10
};
struct PtrVecHdr {                      // begin/end/cap triple
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCap;                       // +0x08
};
struct CountMap {
    uchar mOpaque[4];                   // map at this+0xe0; only its address is used
    int*  slot(int* key);               // 0x007c3a90
    void  erase(int* key);              // 0x00a460d0
};
struct StageTemp {                      // 0x74 temporary built by 0x00ac9850
    void* mpAllocated;                  // +0x00
    uint  mRest[0x1c];                  // +0x04
    void  ctor();                       // 0x00ac9850
};
typedef void  (__thiscall *VoidFn)(void*);
typedef void* (__thiscall *PtrFn)(void*);
typedef int   (__thiscall *IntFn)(void*);
typedef void  (__thiscall *Void1Fn)(void*, void*);
typedef void* (__thiscall *PtrIntFn)(void*, int);
typedef void  (__thiscall *VoidFloatFn)(void*, float);
typedef void  (__thiscall *Void2Fn)(void*, void*, void*);
static int   objType(void* o)                 { return ((IntFn)vc(o, 0x20))(o); }
static void  objAddRef(void* o)               { ((VoidFn)vc(o, 0x00))(o); }
static void  objRelease(void* o)              { ((VoidFn)vc(o, 0x04))(o); }
static void* objFind(void* o, int id)         { return ((PtrIntFn)vc(o, 0x0c))(o, id); }
static void  vcall0(void* o, int slot)        { ((VoidFn)vc(o, slot))(o); }
static void* vcall0p(void* o, int slot)       { return ((PtrFn)vc(o, slot))(o); }
static void  vcall1(void* o, int slot, void* a) { ((Void1Fn)vc(o, slot))(o, a); }
static void  vcall2(void* o, int slot, void* a, void* b) { ((Void2Fn)vc(o, slot))(o, a, b); }
static void  vcallf(void* o, int slot, float a) { ((VoidFloatFn)vc(o, slot))(o, a); }
void  __cdecl FUN_00ac97f0(void* a, void* b, void* c);
void  __cdecl FUN_00ac89a0(void* a, void* b, void* c);
void* __cdecl FUN_00ac95a0(void* a, void* b, void* c);
MapNode* __cdecl FUN_00aca1f0(MapNode* begin, MapNode* end, int* key, int mode);
void* __cdecl FUN_00b3d260();
void* __cdecl FUN_00b3d310();
struct CStage {
    uchar mPad00[0x24];               // +0x000 (vtable pointer and unknown fields)
    int   mKey24;                     // +0x024
    uchar mPad28[0x49];               // +0x028..+0x070
    uchar mFlag71;                    // +0x071
    uchar mPad72[3];                  // +0x072..+0x074
    uchar mFlag75;                    // +0x075
    uchar mPad76[0x4a];               // +0x076..+0x0bf
    uchar mSubC0[4];                  // +0x0c0 subobject with its own vtable
    uchar mPadC4[0xa90];              // +0x0c4..+0xb53
    void* mpFieldB54;                 // +0xb54
    uchar mPadB58[0x2fc];             // +0xb58..+0xe53
    uint  mCountE54;                  // +0xe54

    char  canDo();                    // 0x00c0c0e0
    void* getFrame();                 // 0x00c0bc00
    char  hasA();                     // 0x00c232b0
    char  hasB();                     // 0x00c232c0
    void* getHerd();                  // 0x00c04590
    void  setHerd(void* p);           // 0x00c045a0
};
struct Herd {
    uchar mPad00[0x40];               // +0x00
    int*  mpVecBegin;                 // +0x40 (vector header address)
    uchar mPad44[0x20];               // +0x44..+0x63
    uchar mFlag64;                    // +0x64
};
struct LinkObj {                      // object returned through stage vtable +0xac
    void* mpOwner;                    // +0x00
    uint  mFlags;                     // +0x04
};
struct Singleton {                    // object returned by 0x00b3d310
    uchar mPad00[0x20];               // +0x00
    int   mValue20;                   // +0x20
};
struct AllocHeader { int mSize; };    // eastl allocation header (at mem-4)
struct CUnknown48770 { void apply(void* p, int one); };   // 0x00b48770
struct CUnknownCff0  { void set(int a); };                // 0x00c0cff0
struct CUnknown2b00  { void set(int a); };                // 0x00a02b00
struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    void   pushSlow(void** end, void** value);            // 0x00aea5d0
};
struct XC {
    void  FUN_00acbd90();
    void  FUN_01011cc0(void*);
    void  FUN_00ac97f0(void*, void*);
    void  FUN_00ac89a0(void*, void*);
    void* FUN_00ac95a0(void*);
    void  FUN_00acb680(void*, void*);
    void  FUN_00acb810(void*);
    void  FUN_00acb930(void*, int, void*);
    void  FUN_00acb7c0(void*, void*);
    void  FUN_00c232b0();
    void  FUN_00c232c0();
    int   FUN_00c0c0e0();
    void* FUN_00c0bc00();
    void  FUN_00a05270();
};
struct VO {
    int* v;                        // +0x00
    uchar  mPad04[0x84];           // +0x04
    MapNode* mpMapBegin;           // +0x88
    MapNode* mpMapEnd;             // +0x8c
    uchar  mPad90[0x0c];           // +0x90
    uchar  mMapMode;               // +0x9c
    uchar  mPad9d[0x0b];           // +0x9d
    StageList* mpListsBegin;       // +0xa8
    StageList* mpListsEnd;         // +0xac
    uchar  mPadB0[0x14];           // +0xb0
    HashNode** mpBuckets;          // +0xc4
    uint   mBucketEnd;             // +0xc8
    uchar  mPadCC[0x14];           // +0xcc
    CountMap mCountMap;            // +0xe0

    void  FUN_00acc140(uchar* pos, uchar* val);
    void  FUN_00acc610(void* p);
    void  FUN_00acc700(void* p, float a, float b);
    void  FUN_00acc770();
    void  FUN_00acc9b0(uint n);
    void  FUN_00acc390();
    bool  FUN_00accf80(void* p);
    void  FUN_00acd210();
    void  FUN_00acd2d0(void* p);
    void  FUN_00acd410(void* p);
    void  FUN_00ac84f0(void* p);   // 0x00ac84f0, defined in another slice
    int*  FUN_00acbd90(int* other);   // 0x00acbd90 (vector copy-assign; `this` is the vector)
};
void* FUN_00accec0(uchar* p, uchar* end, uchar* out);
// declaration-only alias of the function defined below (0x00accec0): s00ad0510's FUN_00ad08f0 calls it out of line in the
// retail build; the definition in this TU lets cl inline it
extern "C" void* __cdecl FUN_00accec0_s00ad_0510(void*, void*, void*);          // 0x00accec0
void* FUN_00accf20(int end, int begin, int out);
bool  FUN_00acca00(int* vec, int* val);
// ---- items of slice s00acc140 end

// ---- items of slice s00ace5a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gTimer;       // 0x0167a490
extern float gThreshold;   // 0x01565ce0
extern int gStat0, gStat1, gStat2;   // 0x0167a37c, 0x0167a380, 0x0167a384
extern int gCurrentID;     // 0x0169e370
extern int gMaxPerTick;    // 0x01565d04
extern const char kSimulatorName[];      // 0x013f09b4  "Simulator"
extern const char kAllocatorFile[];      // 0x013ebb38  "allocator.h"
extern const char kCityVisualizerName[]; // 0x0145a270  "Simulator/cCityVisualizer"
extern const char kAbandonedName[];      // 0x0145a248  "Simulator/cAbandonedCitizenVisualizer"
extern void* g_EmptyBuckets;          // 0x0154df28  empty bucket array (1 bucket)
extern const float kOne;              // 0x01485720
extern const float kTwo;              // 0x01470f1c
extern const float kHalf;             // 0x01471064
extern const float kQuarter;          // 0x013eb8a0
extern const float kZero;             // 0x01485378
extern const wchar_t kEmptyString16[];// 0x01667bac  eastl empty string
struct Quat4 { float x, y, z, w; };
struct Sphere { float x, y, z, r2a, r2b; };   // 0x14 bytes
#define PV_s00ac_e5a0(n) virtual void s##n();
struct Ref {   // refcounted noun handle
    PV_s00ac_e5a0(0)
    virtual void Release();          // slot 1
    PV_s00ac_e5a0(2) PV_s00ac_e5a0(3) PV_s00ac_e5a0(4) PV_s00ac_e5a0(5) PV_s00ac_e5a0(6) PV_s00ac_e5a0(7) PV_s00ac_e5a0(8) PV_s00ac_e5a0(9) PV_s00ac_e5a0(10)
    virtual bool IsDead();           // slot 11 (0x2c)
};
struct Placement {   // returned by FUN_00ad7360; slot 11 = position, slot 12 = rotation
    PV_s00ac_e5a0(0) PV_s00ac_e5a0(1) PV_s00ac_e5a0(2) PV_s00ac_e5a0(3) PV_s00ac_e5a0(4) PV_s00ac_e5a0(5) PV_s00ac_e5a0(6) PV_s00ac_e5a0(7) PV_s00ac_e5a0(8) PV_s00ac_e5a0(9) PV_s00ac_e5a0(10)
    virtual const Vec3* GetPosition();
    virtual const Quat4* GetRotation();
};
struct SubLock {     // embedded at +0xC0 of the type-2 objects
    PV_s00ac_e5a0(0) PV_s00ac_e5a0(1) PV_s00ac_e5a0(2) PV_s00ac_e5a0(3) PV_s00ac_e5a0(4) PV_s00ac_e5a0(5) PV_s00ac_e5a0(6) PV_s00ac_e5a0(7) PV_s00ac_e5a0(8) PV_s00ac_e5a0(9) PV_s00ac_e5a0(10)
    virtual const Vec3* GetPosition();   // 0x2c
    PV_s00ac_e5a0(12) PV_s00ac_e5a0(13) PV_s00ac_e5a0(14) PV_s00ac_e5a0(15) PV_s00ac_e5a0(16) PV_s00ac_e5a0(17) PV_s00ac_e5a0(18) PV_s00ac_e5a0(19) PV_s00ac_e5a0(20) PV_s00ac_e5a0(21)
    virtual bool IsLocked();             // 0x58
};
struct SubHidden {   // embedded at +0x34 of the LOD object's helper
    PV_s00ac_e5a0(0) PV_s00ac_e5a0(1) PV_s00ac_e5a0(2) PV_s00ac_e5a0(3) PV_s00ac_e5a0(4) PV_s00ac_e5a0(5) PV_s00ac_e5a0(6) PV_s00ac_e5a0(7) PV_s00ac_e5a0(8) PV_s00ac_e5a0(9) PV_s00ac_e5a0(10) PV_s00ac_e5a0(11) PV_s00ac_e5a0(12) PV_s00ac_e5a0(13) PV_s00ac_e5a0(14) PV_s00ac_e5a0(15) PV_s00ac_e5a0(16) PV_s00ac_e5a0(17)
    virtual bool IsHidden();             // 0x48
};
struct LodHelper {
    char pad[0x34];
    SubHidden mSub;
    char pad2[0x120 - 0x38];
    uint8_t mbFlag;
};
struct NounObj1 {      // type 0x36be27e
    PV_s00ac_e5a0(0) PV_s00ac_e5a0(1) PV_s00ac_e5a0(2) PV_s00ac_e5a0(3) PV_s00ac_e5a0(4) PV_s00ac_e5a0(5) PV_s00ac_e5a0(6) PV_s00ac_e5a0(7) PV_s00ac_e5a0(8) PV_s00ac_e5a0(9) PV_s00ac_e5a0(10)
    virtual bool IsRemoved();                // 0x2c
    char pad04[0x84 - 4]; uint32_t mFlags;
    char pad88[0xa9 - 0x88]; uint8_t mbSpawned;
    char padaa[0x10c - 0xaa]; uint32_t mTypeID; uint32_t mField110;
    char pad114[0x1a4 - 0x114]; Ref* mpNoun; Vec3 mPos; Quat4 mRot; uint8_t mbDone;
};
struct NounObj2 {      // type 0x18eb45e
    PV_s00ac_e5a0(0) PV_s00ac_e5a0(1) PV_s00ac_e5a0(2) PV_s00ac_e5a0(3) PV_s00ac_e5a0(4) PV_s00ac_e5a0(5) PV_s00ac_e5a0(6) PV_s00ac_e5a0(7) PV_s00ac_e5a0(8) PV_s00ac_e5a0(9) PV_s00ac_e5a0(10)
    virtual bool IsRemoved();                // 0x2c
    PV_s00ac_e5a0(12) PV_s00ac_e5a0(13) PV_s00ac_e5a0(14) PV_s00ac_e5a0(15) PV_s00ac_e5a0(16) PV_s00ac_e5a0(17) PV_s00ac_e5a0(18)
    virtual int GetOwnerID();                // 0x4c
    PV_s00ac_e5a0(20) PV_s00ac_e5a0(21) PV_s00ac_e5a0(22) PV_s00ac_e5a0(23) PV_s00ac_e5a0(24) PV_s00ac_e5a0(25) PV_s00ac_e5a0(26) PV_s00ac_e5a0(27) PV_s00ac_e5a0(28) PV_s00ac_e5a0(29) PV_s00ac_e5a0(30) PV_s00ac_e5a0(31) PV_s00ac_e5a0(32) PV_s00ac_e5a0(33) PV_s00ac_e5a0(34) PV_s00ac_e5a0(35)
    PV_s00ac_e5a0(36) PV_s00ac_e5a0(37) PV_s00ac_e5a0(38) PV_s00ac_e5a0(39) PV_s00ac_e5a0(40) PV_s00ac_e5a0(41) PV_s00ac_e5a0(42) PV_s00ac_e5a0(43) PV_s00ac_e5a0(44) PV_s00ac_e5a0(45) PV_s00ac_e5a0(46) PV_s00ac_e5a0(47) PV_s00ac_e5a0(48) PV_s00ac_e5a0(49)
    virtual void Activate(bool b);           // 0xc8
    bool Func_c0c0e0();   // 0x00c0c0e0
    char pad04[0x24 - 4]; uint32_t mKey;
    char pad28[0xc0 - 0x28]; SubLock mSub;
    char padc4[0x135 - 0xc4]; uint8_t mbFlag135;
    char pad136[0xb67 - 0x136]; uint8_t mbFlagB67;
};
struct NounObj3 {      // type 0x1be418e
    PV_s00ac_e5a0(0) PV_s00ac_e5a0(1) PV_s00ac_e5a0(2) PV_s00ac_e5a0(3) PV_s00ac_e5a0(4) PV_s00ac_e5a0(5) PV_s00ac_e5a0(6) PV_s00ac_e5a0(7) PV_s00ac_e5a0(8) PV_s00ac_e5a0(9) PV_s00ac_e5a0(10)
    virtual bool IsRemoved();                // 0x2c
    char pad04[0x84 - 4]; uint8_t mbFlag84;
    char pad85[0x88 - 0x85]; uint32_t mOwnerSpeciesKey;    // 0x88
    char pad8c[0xf0 - 0x8c]; uint32_t mUsedFallback;       // 0xf0
    char padf4[0x108 - 0xf4]; float mSpawnTime;            // 0x108
    char pad10c[0x120 - 0x10c]; int mRangeMin; int mRangeMax; uint8_t mbNear;
    char pad129[0x160 - 0x129]; LodHelper* mpHelper;
    bool Func_c6a020();
    void Func_c6ace0(bool b);
    const Vec3* Func_c6acc0();
    bool Func_c6a030();
    void Func_c6b540();
    void UpdateFromArchetype(void* pArchetype, int b);   // 0x00c6e200
};
struct Tribe {
    PV_s00ac_e5a0(0) PV_s00ac_e5a0(1) PV_s00ac_e5a0(2) PV_s00ac_e5a0(3) PV_s00ac_e5a0(4) PV_s00ac_e5a0(5) PV_s00ac_e5a0(6) PV_s00ac_e5a0(7) PV_s00ac_e5a0(8) PV_s00ac_e5a0(9) PV_s00ac_e5a0(10) PV_s00ac_e5a0(11) PV_s00ac_e5a0(12) PV_s00ac_e5a0(13) PV_s00ac_e5a0(14) PV_s00ac_e5a0(15) PV_s00ac_e5a0(16) PV_s00ac_e5a0(17) PV_s00ac_e5a0(18)
    virtual int GetID();   // 0x4c
};
template<class T> struct PtrVec_s00ac_e5a0 { T** mpBegin; T** mpEnd; T** begin() const { return mpBegin; } T** end() const { return mpEnd; } };
template<class T> struct VecOut { char pad[4]; PtrVec_s00ac_e5a0<T> mVec; };
class NounVisibility;
struct NounManager {
    Tribe* GetPlayerTribe();                                       // 0x00bfc5f0
    void* GetGameDataVector(void (*)(), void (*)(), void (*)(), void (*)(), uint32_t);   // 0x00b21340
    void RemoveNoun(Ref* pNoun);                                   // 0x00b225d0
};
struct HIter { void* mpNode; void** mpBucket; HIter() {} HIter(const HIter& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {} };
struct HTable {
    char pad[4]; void** mpBucketArray; uint32_t mnBucketCount;
    void* End() const { return mpBucketArray[mnBucketCount]; }
    HIter find(const uint32_t& key);                               // 0x00645ed0
};
struct ModeInfo { char pad[0x2c]; int mMode; };
NounManager* GetNounManager();            // 0x00b3d300
ModeInfo* GetModeInfo();                  // 0x00b3d4d0
Placement* FindPlacement(Ref** ppNoun);   // 0x00ad7360 (cdecl)
void ActivateObj(NounObj1* p, int a, int b);   // 0x00b931c0 (cdecl)
void F_cd7d10();
void F_d3d420();
void F_b1e500();
void F_ace070();
void F_ace0f0();
void F_accc30();
extern Vec3 gPoint;        // 0x0167ea30
class NounVisibility {
public:
    char pad00[0x20];
    Sphere* mpSpheresBegin;      // 0x20
    Sphere* mpSpheresEnd;        // 0x24
    char pad28[0xe0 - 0x28];
    HTable mTable;               // 0xe0
    bool Func_ac8d80(const Vec3* p);   // 0x00ac8d80
    bool Func_ac8df0(const Vec3* p);   // 0x00ac8df0
    void Update(int unused, uint32_t dt);
};
static inline void ReleaseNoun(Ref*& r)
{
    Ref* p = r;
    if (p) { r = 0; p->Release(); }
}
struct IRefCounted {
    virtual int AddRef();      // +0x00
    virtual int Release();     // +0x04
};
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x)
    {
        T* const pObject = x.mpObject;
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct sp_vector_allocator { const char* mpName; uint32_t mFlags; };
template <class T> struct SpVector {
    T* mpBegin;                       // +0x00
    T* mpEnd;                         // +0x04
    T* mpCapacity;                    // +0x08
    sp_vector_allocator mAllocator;   // +0x0c
    void DoInsertValue(T* pos, const T& value);
    SpVector& operator=(const SpVector& x);
};
struct cTribeEntry {                                  // 0x18 bytes
    AutoRefCount<IRefCounted> mpTribe;                // +0x00
    SpVector<AutoRefCount<IRefCounted> > mMembers;    // +0x04
};
template <> SpVector<AutoRefCount<IRefCounted> >&
    SpVector<AutoRefCount<IRefCounted> >::operator=(const SpVector<AutoRefCount<IRefCounted> >& x);   // 0x1011cc0
cTribeEntry* __cdecl FUN_00acaab0(cTribeEntry* first, cTribeEntry* last, cTribeEntry* dst);   // 0xacaab0
void         __cdecl FUN_00acab70(cTribeEntry* first, cTribeEntry* last, cTribeEntry* dst);   // 0xacab70
int*         __cdecl FUN_00acc330(int* dstEnd, int* srcEnd, int* srcBegin);                   // 0xacc330
struct EntryOps { cTribeEntry* FUN_00aca970(cTribeEntry* src); };   // 0xaca970
void* __cdecl operator_new(size_t size, const char* name, int a, int b, const char* file, int line);   // 0x00f473a0
struct TileNode_s00ac_e5a0 {                     // value starts at +0x04
    uint32_t mKey;                    // +0x00
    Vec3     mPos;                    // +0x04
    float    mDist;                   // +0x10
};
struct HFind { void* mpNode; void* mpBucket; };
struct CellMap {                      // 0x20 bytes
    void*    mpUnused00;              // +0x00
    void**   mpBucketArray;           // +0x04  (empty -> g_EmptyBuckets)
    uint32_t mnBucketCount;           // +0x08
    uint32_t mUnused0c;               // +0x0c
    float    mLoadFactor;             // +0x10
    float    mGrowFactor;             // +0x14
    uint32_t mSize;                   // +0x18
    uint32_t mUnused1c;               // +0x1c
    HFind* Find(HFind* out, const uint32_t* key);   // 0x00ac9d30
    TileNode_s00ac_e5a0* TileAt(const uint32_t* key);          // 0x00ace170
};
struct PlanetModel {
    float    GetWaterHeight();                          // 0x00b7e390
    float    GetRadiusAt(const Vec3* dir);              // 0x00b7ef70
    Vec3*    SnapToSurface(Vec3* out, const Vec3* dir); // 0x00b81630
};
PlanetModel* SP_PlanetModel_s00ac_e5a0();          // 0x00b3d350
void*        GetActivePlanet_s00ac_e5a0();         // 0x01021260
struct ResourceKey { uint32_t mA; uint32_t mB; };
struct cSpeciesArchetype { char pad[0x10]; uint32_t mSpeciesKey; };
struct SpeciesManager_s00ac_e5a0 {
    cSpeciesArchetype* GetSpeciesArchetype(uint32_t id, uint32_t level);   // 0x004e0050
    void*              GetProfile(const ResourceKey* key);                 // 0x004df550
};
SpeciesManager_s00ac_e5a0* FUN_00401090_s00ac_e5a0();         // 0x00401090 (cdecl, returns the editor species manager)
struct cPollOwner { void UpdateProperty(uint32_t id, const Vec3* key); };   // 0x0060d860
cPollOwner* GetPollinator();                                                // 0x0067cb30
struct Publication { IRefCounted* mpObj; };
void __fastcall FUN_00e1c7f0(void* pVector, void* unused, IRefCounted** ppRef);   // 0x00e1c7f0 (thiscall ret 4)
struct RawVec3 { uint32_t x, y, z; };
extern RawVec3 g_NoPosition;                          // 0x0167a39c
struct CtorNoArg { void FUN_00b5b960(); void FUN_00b95050(); };             // 0x00b5b960 / 0x00b95050
struct VisCtor   { void* FUN_00d5e730(); void* FUN_00d59580(); };           // 0x00d5e730 / 0x00d59580
class cCastingManager {
public:
    void*    mpVtbl0;              // +0x000
    void*    mpVtbl4;              // +0x004
    char     pad008[0x14];         // +0x008
    void*    mpVtbl1c;             // +0x01c
    void*    mpInlineBegin;        // +0x020
    void*    mpInlineEnd;          // +0x024
    void*    mpInlineCap;          // +0x028
    char     pad02c[0x08];         // +0x02c
    int      mField34;             // +0x034
    char     mInlineBuf[0x50];     // +0x038
    uint32_t mField88;             // +0x088
    uint32_t mField8c;             // +0x08c
    uint32_t mField90;             // +0x090
    char     pad094[0x0c];         // +0x094
    int      mFieldA0;             // +0x0a0
    void*    mpCityVisualizer;     // +0x0a4
    void*    mpTribesBegin;        // +0x0a8
    void*    mpTribesEnd;          // +0x0ac
    void*    mpTribesCapacity;     // +0x0b0
    char     pad0b4[0x08];         // +0x0b4
    void*    mpAbandonedVisualizer;// +0x0bc
    CellMap  mCells;               // +0x0c0
    CellMap  mCells2;              // +0x0e0
    uint8_t  mField100;            // +0x100
    uint8_t  mField101;            // +0x101
    char     pad102[0x02];         // +0x102
    const wchar_t* mpString104;    // +0x104
    const wchar_t* mpString108;    // +0x108
    const wchar_t* mpString10c;    // +0x10c
    char     pad110[0x04];         // +0x110
    uint8_t  mField114;            // +0x114
    char     pad115[0x03];         // +0x115
    void*    mpField118;           // +0x118
    void*    mpField11c;           // +0x11c
    void*    mpField120;           // +0x120
    char     pad124[0x08];         // +0x124
    char     mSub12c[0x34];        // +0x12c
    char     mSub160[0x34];        // +0x160

    bool Write(SP::cIObjectDatabaseOStream& archive) const;        // 0x00ac8550
    bool Read(SP::cIObjectDatabaseIStream& archive);               // 0x00ad0b30
    void Reset();                                                // 0x00ad08f0
    cCastingManager* Construct();                                  // 0x00acf230
    void  InsertTribe(cTribeEntry* pos, const cTribeEntry& value);  // (unused helper slot)
    void  CastNoun(NounObj3* pNoun, char bFlag);                   // 0x00acebd0
    void  SpawnHerdFromProfile(Vec3* pPos, void* pMgr);            // 0x00acf3e0
};
struct NounManagerSpawn {
    NounObj3* CreateNoun(float* pPos, void* profile, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00b23940
};
// ---- items of slice s00ace5a0 end

// ---- items of slice s00ad0510 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*  __fastcall CreateNoun(void*, int, void*);                 // 0x00b20c60
extern "C" void   __fastcall RemoveNoun(void*, int, void*);                 // 0x00b225d0
extern "C" void   __fastcall FUN_00c8fc50(void*, int, int);                 // 0x00c8fc50
extern "C" void   __fastcall FUN_00c0bf00(void*, int, int);                 // 0x00c0bf00
extern "C" void   __fastcall FUN_00d5bb30(void*, int);                      // 0x00d5bb30
extern "C" void*  __cdecl FUN_00copy_Rec20(void*, void*, void*);            // 0x00951bf0
extern "C" bool   __cdecl FUN_00b98c00(void*);                              // 0x00b98c00
extern "C" void*  __cdecl FUN_00acc2d0(void*, void*, void*);                // clear helper (tribe)
extern "C" void*  __cdecl FUN_00ac9740(void*, void*, void*);                // destroy range
extern int  g_167a378;        // 0x0167a378
extern char g_167a390;        // 0x0167a390
typedef void  (__thiscall *TC_v0)(void*);
typedef void  (__thiscall *TC_v3)(void*, void*, void*, void*);
struct RegElem_s00ad_0510 {              // 0x0c-byte entry of a record's vector
    void* vt;                 // +0x00
    u8    flag4;              // +0x04
    char  pad5[3];            // +0x05
    void* ptr8;               // +0x08
};
struct RegVec {               // eastl vector of RegElem (0x14 bytes)
    RegElem_s00ad_0510* begin;           // +0x00
    RegElem_s00ad_0510* end;             // +0x04
    RegElem_s00ad_0510* cap;             // +0x08
    int      alloc0;          // +0x0c
    int      alloc1;          // +0x10

    void FUN_00aca9d0(const RegVec* src);   // 0x00aca9d0 (copy-construct)
    void FUN_00acbd90(const RegVec* src);   // 0x00acbd90 (copy-assign)
    void FUN_00ac8ec0();                    // 0x00ac8ec0 (destructor)
};
struct RegList_s00ad_0510 {              // record payload, starts at element+4
    void*   vt;               // +0x04  (0x0145a164)
    u8      b8;               // +0x08
    u8      b9;               // +0x09
    char    pad0a[2];         // +0x0a
    RegVec  vec;              // +0x0c  (0x14 bytes)
};
struct Elem20 {               // 0x20-byte sorted-vector element
    int     key;              // +0x00
    RegList_s00ad_0510 list;             // +0x04
};
struct ElemVec {              // sorted registry vector header (0x18 bytes)
    Elem20* begin;            // +0x00
    Elem20* end;              // +0x04
    Elem20* cap;              // +0x08
    char    pad0c[8];         // +0x0c
    u8      less;             // +0x14
    char    pad15[3];         // +0x15

    RegList_s00ad_0510* get(int* key);   // 0x00ad0ca0
    Elem20* FUN_00ad0890(Elem20* pos, Elem20* val);  // 0x00ad0890 (insert)
};
struct AutoRef {              // 0x04-byte intrusive reference
    void* p;
};
struct AutoRefVec {           // eastl vector of AutoRef (0x14 bytes)
    AutoRef* begin;
    AutoRef* end;
    AutoRef* cap;
    int      alloc0;
    int      alloc1;
};
struct TribeEntry {           // 0x18-byte entry of the +0xa8 vector
    AutoRef    primary;       // +0x00
    AutoRefVec refs;          // +0x04
};
struct TribeVec {             // eastl vector of TribeEntry
    TribeEntry* begin;
    TribeEntry* end;
    TribeEntry* cap;
};
struct Rec20_s00ad_0510 {                // 0x14-byte element of the +0x20 vector
    int v[5];
};
struct RecVec {
    Rec20_s00ad_0510* begin;
    Rec20_s00ad_0510* end;
    Rec20_s00ad_0510* cap;
};
struct FieldC0 {              // auxiliary record at +0xc0
    int   a0;
    void* a4;
    void* a8;
    int   ac;
};
struct FieldE0 {              // eastl hashtable at +0xe0
    void* a0;
    void* a4;
    void* a8;
    int   ac;
};
struct cCityVisualizer_s00ad_0510;
struct VignetteObj {          // object reached from tag 0x116dd1b
    char pad00[0x71];
    u8   f71;                 // +0x71
    char pad72[3];
    u8   f75;                 // +0x75
};
struct cCityVisualizer_s00ad_0510 {
    char        pad00[0x1c];
    void*       msg1c;        // +0x1c
    RecVec      rec;          // +0x20
    char        pad2c[0x88 - 0x2c];
    ElemVec     registry;     // +0x88
    int         f_a0;         // +0xa0
    void*       mp_city;      // +0xa4
    TribeVec    tribes;       // +0xa8
    char        pad_b4[8];
    void*       p_bc;         // +0xbc
    FieldC0     field_c0;     // +0xc0
    char        pad_d0[0xe0 - 0xd0];
    FieldE0     hash_e0;      // +0xe0
    u8          f_100;        // +0x100

    void* UpdateVignettes(void* tag);   // 0x00ad11f0
};
void __fastcall FUN_00ad08f0(cCityVisualizer_s00ad_0510* self, int);  // 0x00ad08f0 (defined below; used by a stub's inline body)
void __fastcall FUN_00ad1000(cCityVisualizer_s00ad_0510* self, int, void* tag, int count);  // 0x00ad1000 (defined below; used by a stub's inline body)
struct CityOps {
    void FUN_00ad1000(void* tag, int count);   // 0x00ad1000
    void FUN_00ac8a80(RegList_s00ad_0510* list, int i);   // 0x00ac8a80
    void FUN_00d60f00_s00ad_0510(void* city);             // 0x00d60f00
    void FUN_00d5bb30();                       // 0x00d5bb30
    void FUN_00ad08f0();                       // 0x00ad08f0
};
extern "C" void*  __cdecl NounManager_s00ad_0510();                                    // 0x00b3d300
extern "C" void   __fastcall FUN_00d60f00_s00ad_0510(void*, int, void*);               // 0x00d60f00 (SetCity)
extern "C" int    __cdecl ReadInt32_s00ad_0510(void*, int*, int, int);                 // 0x0093a780
extern "C" void*  __cdecl FUN_00f473a0(uint, const char*, int, int, const char*, int); // operator new
extern "C" Elem20* __cdecl FUN_00aca1f0_s00ad_0510(Elem20*, Elem20*, int*, u8);        // lower_bound
extern "C" Elem20* __fastcall FUN_00ad0890(void*, int, Elem20*, Elem20*);   // record insert
extern "C" Elem20* __cdecl FUN_00acbb20(Elem20*, Elem20*, Elem20*);         // move-construct range
extern "C" void   __cdecl FUN_00aca2f0(Elem20*, Elem20*, Elem20*);          // destroy moved-from range
extern "C" void   __fastcall FUN_00aca9d0(RegVec*, int, const RegVec*);     // vector copy-construct
extern "C" void   __fastcall FUN_00acbd90(RegVec*, int, const RegVec*);     // vector copy-assign
extern "C" void   __fastcall FUN_00ac8ec0(RegVec*, int);                    // vector destructor
extern "C" void   __fastcall FUN_00aca820_s00ad_0510(void*, int, void*, void*);        // clear helper (tribe)
extern "C" void   __fastcall FUN_00aca7b0_s00ad_0510(void*, int, void*, void*);        // clear helper (record)
extern "C" void   __fastcall FUN_00acccb0(TribeVec*, int, int);             // reserve
extern "C" void   __fastcall FUN_00aca970(TribeEntry*, int, const TribeEntry*); // copy-construct entry
extern "C" void   __fastcall FUN_00acf0b0(TribeVec*, int, const TribeEntry*);   // push_back (grow)
extern "C" void   __fastcall FUN_00acd920(RegVec*, int, int);               // resize record vector
extern "C" void   __fastcall FUN_00ad0590(ElemVec*, int, Elem20*, Elem20*); // record insert
extern "C" void   __fastcall FUN_00ac8a80(cCityVisualizer_s00ad_0510*, int, RegList_s00ad_0510*, int); // erase entry
extern "C" void   __fastcall FUN_00acd4a0(cCityVisualizer_s00ad_0510*, int);           // reset action circle
extern "C" void   __fastcall FUN_00accf80(cCityVisualizer_s00ad_0510*, int, void*);    // SetupCultureStages
extern "C" void   __fastcall FUN_00accd70_s00ad_0510(FieldC0*, int, void*, void*);     // clear field at +0xc0
extern "C" void   __fastcall FUN_00acc770(cCityVisualizer_s00ad_0510*, int);           // reset field at +0xc0
extern "C" void   __fastcall FUN_00693230(FieldE0*, int, void*, void*);     // hashtable free buckets
extern u8   g_1565cfc;        // 0x01565cfc
struct CVarListSerializer {
    char pad[0xa10];
    void ctor(const void* owner, void* descriptor, uint tag);    // 0x00692f90
    bool Read(void* stream);                                     // 0x00693e10
};
static void destroyRegVec(RegVec* v)
{
    for (RegElem_s00ad_0510* p = v->begin; p != v->end; ++p)
        VTC(p, 0x00, TC_v1)(p, 0);
    if (v->begin)
        FUN_00f47380(v->begin);
    v->begin = 0;
    v->end = 0;
    v->cap = 0;
}
static void destroyTribeEntry(TribeEntry* e)
{
    if (e->primary.p)
        VTC(e->primary.p, 0x04, TC_v0)(e->primary.p);
    for (AutoRef* p = e->refs.begin; p != e->refs.end; ++p)
        if (p->p)
            VTC(p->p, 0x04, TC_v0)(p->p);
    if (e->refs.begin && ((int*)e->refs.begin)[-1] != 0)
        FUN_00f47380(e->refs.begin);
}
// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
void** __fastcall FUN_00d58510(void* self, void* /*edx*/, void* out, void* obj, float* pos);   // defined at 0x00d58510, called earlier in the TU
void FUN_00d592e0(int* array, int count, int param_3, int start, IObj* obj, int a6, int a7, int a8);   // defined at 0x00d592e0, called earlier in the TU
void __stdcall FUN_00d595d0(void* begin, void* end);   // defined at 0x00d595d0, called earlier in the TU
int __cdecl EraseRefValue(RefPtrVector* vec, const RefPtr* pValue);   // defined at 0x00d5aae0, called earlier in the TU

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

// 0x00ac8130: not byte-exact; the byte-exact version is the lifted one in match/slices/s00ac8130/s00ac8130.cpp
void CVis::FUN_00ac8130()
{
    void* a = operator_new6(0x34, "Simulator", 0, 0, 0, 0);
    void* ta = a ? FUN_00b95050(a) : 0;
    void* b = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    void* tb = b ? FUN_00b93810(b, 0x41a00000, 0x41f00000) : 0;
    FUN_00b981a0(ta, 1, tb);
    void* c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    void* tc = c ? FUN_00b93840(c, 0x40a00000, 0x41000000) : 0;
    FUN_00b981a0(ta, 3, tc);
    FUN_00b981a0(ta, 1, tb);
    a = operator_new6(0x34, "Simulator", 0, 0, 0, 0);
    ta = a ? FUN_00b95050(a) : 0;
    b = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tb = b ? FUN_00b93810(b, 0x41700000, 0x41a00000) : 0;
    FUN_00b981a0(ta, 1, tb);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93840(c, 0x40800000, 0x41000000) : 0;
    FUN_00b981a0(ta, 6, tc);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b94a90(c, 0x40800000, 0x40c00000) : 0;
    FUN_00b981a0(ta, 6, tc);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93810(c, 0x40400000, 0x40e00000) : 0;
    FUN_00b981a0(ta, 1, tc);
    FUN_00b981a0(ta, 1, tb);
    a = operator_new6(0x34, "Simulator", 0, 0, 0, 0);
    ta = a ? FUN_00b95050(a) : 0;
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93810(c, 0x40400000, 0x40e00000) : 0;
    FUN_00b981a0(ta, 1, tc);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b94a90(c, 0x40800000, 0x40c00000) : 0;
    FUN_00b981a0(ta, 4, tc);
    FUN_00b981a0(ta, 1, tb);
    a = operator_new6(0x34, "Simulator", 0, 0, 0, 0);
    ta = a ? FUN_00b95050(a) : 0;
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93810(c, 0x41700000, 0x41a00000) : 0;
    FUN_00b981a0(ta, 1, tc);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93840(c, 0x41000000, 0x40c00000) : 0;
    FUN_00b981a0(ta, 6, tc);
    FUN_00b981a0(ta, 1, tb);
}

// @ 0x00ac84d0
int* CVis::FUN_00ac84d0(int which)
{
    int* r = (int*)((char*)this + 0x12c);
    if (which != 1) r = (int*)((char*)this + 0x160);
    return r;
}

// @ 0x00ac84f0
void CVis::FUN_00ac84f0(IObj_s00ac_7ab0* p)
{
    if (p && p->b20() == (int)0x18eb4b7) {
        ((CCityVis2*)mpA4)->CitizenNeedsRemoval(p);
        ((CReceiver*)mpBC)->FUN_00d59200(p);
    }
}

// @ 0x00ac8550
bool cCastingManager::Write(SP::cIObjectDatabaseOStream& archive) const
{
    CastingArchiveStreamHolder* __restrict holder = reinterpret_cast<CastingArchive*>(&archive)->GetStreamHolder();
    uint32_t version = 0x01f73e49;
    void* stream = holder->GetStream();
    WriteUint32(stream, &version, 1, 0);
    SP::cVarListSerializer serializer(this, gCastingSerializerList, SP::cVarListSerializer::kSignature);
    if (serializer.Serialize(archive) && FUN_00b930c0(&archive))
        return true;
    return false;
}

// @ 0x00ac8660
void FUN_00ac8660(void)
{
    LoadArithmeticaFile(0x25e94602, 0x24a4f5a, (void*)g_167a3d0);
}

// @ 0x00ac8690
void FUN_00ac8690(void)
{
    g_15fd918->GetIntProperty(0x625bf68);
}

// @ 0x00ac8a80
void FUN_00ac8a80(int self, int idx)
{
    byte* base = *(byte**)(self + 8);
    base[idx * 0xc + 4] = 1;
    int* p = *(int**)(base + idx * 0xc + 8);
    if (*(char*)(self + 5) != 0) {
        int* bm = (int*)SP_BehaviorManager();
        int v = 0;
        if (p) v = (*(int (__thiscall*)(int*, uint32))((char*)*(void**)p + 0xc))(p, 0x11c0ba3);
        (*(void (__thiscall*)(int*, int))((char*)*(void**)bm + 0x38))(bm, v);
    }
    if (*(char*)(self + 4) != 0) {
        if (!p) return;
        int* q = (int*)(*(int (__thiscall*)(int*, uint32))((char*)*(void**)p + 0xc))(p, 0x116dd1b);
        if (q) {
            q[0x14] &= ~0x1000;
            *(byte*)((char*)q + 0x71) = 0;
            *(byte*)((char*)q + 0x75) = 1;
            *(byte*)((char*)q + 0x70) = 1;
            *(byte*)((char*)q + 0x6f) = 1;
            *(byte*)((char*)q + 0x77) = 1;
            int* r = (int*)(*(int (__thiscall*)(int*))((char*)*(void**)q + 0xac))(q);
            if (r) {
                r[1] |= 1;
                (*(void (__thiscall*)(int*, int))((char*)*(void**)r + 0x16c))(r, 1);
            }
        }
    }
    if (p && (*(int (__thiscall*)(int*, uint32))((char*)*(void**)p + 0xc))(p, 0xce9f6639)) {
        int* w = (int*)(*(int (__thiscall*)(int*, uint32))((char*)*(void**)p + 0xc))(p, 0xce9f6639);
        if (*(int*)((char*)w + 0xb54)) {
            *(byte*)(*(int*)((char*)w + 0xb54) + 0x64) = 1;
        }
    }
}

// @ 0x00ac8b60
void __stdcall FUN_00ac8b60(void* self)
{
    if (!self) return;
    if (!FUN_00c24560(self)) return;
    if ((int)DAT_0167a38c >= (int)DAT_0167a388) return;
    float f = FUN_00572a10(0.0f, 1.0f);
    if (f < DAT_0167a364) {
        SP_cSPCreatureCitizen_GiveOrder(self, 10, 0, 0);
        DAT_0167a38c++;
        return;
    }
    if (f < DAT_0167a368 + DAT_0167a364) {
        FUN_00c0ba10(self);
        SP_cSPCreatureCitizen_GiveOrder(self, 0, 0, 0);
        DAT_0167a38c++;
        return;
    }
    if (f < (DAT_0167a36c + DAT_0167a368) + DAT_0167a364) {
        FUN_00c0ba10(self);
        SP_cSPCreatureCitizen_GiveOrder(self, 6, 0, 0);
        DAT_0167a38c++;
        return;
    }
    if (((DAT_0167a370 + DAT_0167a36c) + DAT_0167a368) + DAT_0167a364 <= f) {
        if (f < (((DAT_0167a374 + DAT_0167a370) + DAT_0167a36c) + DAT_0167a368) + DAT_0167a364) {
            FUN_00c0ba10(self);
            SP_cSPCreatureCitizen_GiveOrder(self, 0xb, 0, 0);
            DAT_0167a38c++;
            return;
        }
    } else {
        void* tribe = SP_cSPCreatureCitizen_GetTribe(self);
        if (FUN_00c91c80(tribe) < 100.0f) {
            FUN_00c0ba10(self);
            SP_cSPCreatureCitizen_GiveOrder(self, 1, 0, 0);
            DAT_0167a38c++;
            return;
        }
    }
}

// @ 0x00ac8cd0
void CVis::FUN_00ac8cd0(int a, int b)
{
    void* g = mpA4;
    if (g && *(int*)((char*)g + 0xaf0) == a) {
        ((CG*)g)->FUN_00d5bfa0(b);
    }
}

// @ 0x00ac8d00
void CT::FUN_00ac8d00(int city, int a)
{
    if ((mpA4) && *(int*)((char*)(mpA4) + 0xaf0) == city) {
        void* u = ((CCity*)city)->GetCivilization(a);
        ((CGSub*)(mpA4))->FUN_00d57a60(u);
    }
}

// @ 0x00ac8d40
void CT::FUN_00ac8d40(int a)
{
    void* g = mpA4;
    if (g && *(int*)((char*)g + 0xaf0) == a) {
        ((CGSub2*)g)->FUN_00d61880();
    }
}

// @ 0x00ac8d60
bool CT::FUN_00ac8d60(int a)
{
    int r = 0;
    if (mpA4) {
        r = *(int*)((char*)mpA4 + 0xaf0);
        if (r == a) return true;
    }
    return false;
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

// @ 0x00accec0
void* FUN_00accec0(uchar* p, uchar* end, uchar* out)
{
    if (p != end) {
        uchar* d = out + 9;
        uchar* s = p + 9;
        do {
            *(int*)out = *(int*)p;
            d[-1] = s[-1];
            d[0] = s[0];
            ((VO*)(d + 3))->FUN_00acbd90((int*)(s + 3));
            p += 0x20; out += 0x20;
            d += 0x20; s += 0x20;
        } while (p != end);
    }
    return out;
}

// @ 0x00accf20
void* FUN_00accf20(int end, int begin, int out)
{
    if (end != begin) {
        uchar* s = (uchar*)(end + 9);
        uchar* d = (uchar*)(out + 9);
        do {
            *(int*)(out - 0x20) = *(int*)(end - 0x20);
            end -= 0x20; out -= 0x20;
            d[-0x21] = s[-0x21];
            d[-0x20] = s[-0x20];
            ((XC*)(d - 0x1d))->FUN_00acbd90();
            s -= 0x20; d -= 0x20;
        } while (end != begin);
        return d;
    }
    return (void*)out;
}

// Body of 0x00acca00 (another object's function; s00acc140 defines it ahead of 0x00accf80, so cl sees through it there):
// an unmarked local copy keeps the codegen of 0x00accf80 the slice's.
bool FUN_00acca00_s00ac_c140(int* vec, int* val) {
    int* p = (int*)*vec;
    int* end = (int*)vec[1];
    if (p != end) {
        do {
            if (*p == *val) {
                if (p + 1 < end) {
                    int* d = p;
                    int* s = p + 1;
                    for (; s < end; s++, d++) *d = *s;
                }
                vec[1] -= 4;
                int* last = (int*)vec[1];
                if (*last) ((void (__thiscall*)(void*))vc((void*)*last, 4))((void*)*last);
                return 1;
            }
            p++;
        } while (p != end);
    }
    return 0;
}

// @ 0x00accf80
bool VO::FUN_00accf80(void* p)
{
    if (!p) return false;

    int key = objType(p);
    MapNode* found = FUN_00aca1f0(mpMapBegin, mpMapEnd, &key, mMapMode);
    MapNode* node = mpMapEnd;
    if (found != mpMapEnd && found->mKey <= key) node = found;
    if (node == mpMapEnd) return false;

    int n = (int)(node->mpRecordsEnd - node->mpRecordsBegin);
    if (n <= 0) return false;

    StageRec* rec = node->mpRecordsBegin;
    for (int i = 0; i < n; i++, rec++) {
        if (rec->mpStage != p) continue;

        rec->mActive = 0;

        if (node->mFlag9) {
            void* child = p ? objFind(p, 0x11c0ba3) : 0;
            vcall0(child, 0x34);
            void* bm = FUN_00b3d260();
            vcall1(bm, 0x3c, child);
        }

        if (node->mFlag8) {
            void* child = objFind(p, 0x116dd1b);
            if (child) {
                ((CStage*)child)->mFlag71 = 1;
                ((CStage*)child)->mFlag75 = 0;
                vcall1(child, 0x38, (void*)0x167a390);

                StageTemp temp;
                temp.ctor();
                vcall1(child, 0xdc, &temp);
                void* mem = temp.mpAllocated;
                if (mem && ((AllocHeader*)mem)[-1].mSize != 0)
                    operator_delete(mem);

                void* q = ((PtrIntFn)vc(child, 0xb8))(child, 0xce9f6639);
                if (q)
                    ((CUnknownCff0*)q)->set(0);
                else
                    vcallf(child, 0xc4, 0.0f);

                vcall0(child, 0xf4);

                void* r = vcall0p(child, 0xac);
                if (r) {
                    LinkObj* link = (LinkObj*)r;
                    link->mFlags &= 0xfffffffeu;
                    vcall2(link->mpOwner, 0x16c, r, (void*)0);
                }

                void* s = FUN_00b3d310();
                if (((Singleton*)s)->mValue20 == 1) {
                    void* s2 = FUN_00b3d310();
                    ((CUnknown48770*)s2)->apply(p, 1);
                }
            }
        }

        if (p) {
            void* q = objFind(p, 0xce9f6639);
            if (q) {
                vcall0(q, 0xc4);
                Herd* h = (Herd*)((CStage*)q)->mpFieldB54;
                if (h) {
                    h->mFlag64 = 0;
                    ((CUnknown2b00*)h)->set(1);
                }
                ++((CStage*)q)->mCountE54;
            }

            if (objType(p) == 0x18eb45e) {
                objAddRef(p);
                Herd* herd = (Herd*)((CStage*)p)->getHerd();
                if (herd) {
                    objAddRef(herd);
                    FUN_00acca00_s00ac_c140((int*)&herd->mpVecBegin, (int*)&p);
                    ((CStage*)p)->setHerd(0);
                    objRelease(herd);
                }
                objRelease(p);
            }
        }
        return true;
    }
    return false;
}

// @ 0x00acd210
void VO::FUN_00acd210()
{
    int key = 0x18eb4b7;
    MapNode* found = FUN_00aca1f0(mpMapBegin, mpMapEnd, &key, mMapMode);
    MapNode* node = mpMapEnd;
    if (found != mpMapEnd && found->mKey <= key) node = found;
    if (node == mpMapEnd) return;

    int n = (int)(node->mpRecordsEnd - node->mpRecordsBegin);
    if (n <= 0) return;

    StageRec* rec = node->mpRecordsBegin;
    for (int i = 0; i < n; i++, rec++) {
        void* stage = rec->mpStage;
        void* q = stage ? objFind(stage, 0x4f176642) : 0;
        if (((CStage*)q)->hasA())
            FUN_00accf80(stage);
    }
}

// @ 0x00acd2d0
void VO::FUN_00acd2d0(void* p)
{
    switch (objType(p)) {
    case 0x18eb45e: {
        int key = ((CStage*)p)->mKey24;
        int* slot = mCountMap.slot(&key);
        ++*slot;
        return;
    }
    case 0x18eb4b7:
        if (((CStage*)p)->hasA()) {
            FUN_00ac84f0(p);
            return;
        }
        if (!((CStage*)p)->hasB()) return;

        {
            int n = (int)(mpListsEnd - mpListsBegin);
            for (int i = 0; i < n; i++) {
                StageList* b = mpListsBegin + i;
                PtrVecHdr* vec = (PtrVecHdr*)vcall0p(b->mpOwner, 0x90);
                void** a = vec->mpBegin;
                void** e = vec->mpEnd;
                while (a != e && *a != p) a++;
                if (a == e) continue;

                void* tmp = p;
                objAddRef(p);
                if (b->mpEnd < b->mpCap) {
                    *b->mpEnd++ = p;
                    objAddRef(p);
                } else {
                    ((PtrVec*)&b->mpBegin)->pushSlow(b->mpEnd, &tmp);
                }
                if (tmp) objRelease(tmp);
                return;
            }
        }
        return;
    default:
        return;
    }
}

// The staged object's type query is virtual slot 8 (+0x20).
struct ITypedObj_acd410 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int  GetType();                                  // +0x20
};

// @ 0x00acd410
void VO::FUN_00acd410(void* p)
{
    switch (((ITypedObj_acd410*)p)->GetType()) {
    case 0x18eb45e: {
        int key = ((CStage*)p)->mKey24;
        mCountMap.erase(&key);
        break;
    }
    case 0x18eb4b7:
        if (((CStage*)p)->hasA()) {
            FUN_00ac84f0(p);
            FUN_00accf80(p);
            return;
        }
        if (((CStage*)p)->hasB()) {
            FUN_00acc610(p);
            FUN_00accf80(p);
            return;
        }
        break;
    default:
        break;
    }
    FUN_00accf80(p);
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

// @ 0x00acd920
void Vec3_s00ac_d4a0::FUN_00acd920(unsigned n)
{
    unsigned cnt = (unsigned)((mpEnd - mpBegin) / 0xc);
    if (cnt < n) {
        Pair tmp;
        tmp.mpVtbl = (void*)0x145a158;
        tmp.mb4 = 0;
        tmp.mp8 = 0;
        FUN_00acbf30((int*)mpEnd, (int)(n - cnt), &tmp);
    } else {
        FUN_00acbed0((int*)(mpBegin + n * 0xc), (int*)mpEnd);
    }
}

// @ 0x00acda30
void FUN_00acda30(int* self, int* p)
{
    FUN_00accd70((int*)*(int*)((char*)p + 4), (int*)*(int*)((char*)p + 8));
    *(int*)((char*)p + 0xc) = 0;
    uint32 count = 0;
    int* q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
    ReadInt32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &count, 1, 0);
    for (uint32 i = 0; i < count; ++i) {
        Pair rec;
        rec.mpVtbl = (void*)0x145a184;
        rec.mb4 = 0;
        rec.mp8 = 0;
        // full 0x68-byte record body omitted: reads int32 then serializes
        int one = 0;
        q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
        ReadInt32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &one, 1, 0);
        (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
        char srl[0xa14];
        SP_cVarListSerializer_ctor(srl, &rec, (void*)0x15661a8, 0x1a80d26);
        SP_cVarListSerializer_Serialize(srl, self);
        (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
        int tmp[2];
        FUN_00acc8c0(tmp, &one, 0);
        (void)tmp;
    }
    (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
}

// @ 0x00ace170
int CSet::FUN_00ace170(int* p)
{
    int found[3];
    FUN_00ac9d30(found, p);
    if (found[0] == (int)(mp4)[m8]) {
        Pair rec;
        rec.mpVtbl = (void*)0x145a184;
        rec.mb4 = 0;
        rec.mp8 = 0;
        FUN_00acb490(&rec);
        FUN_00acc8c0(found, p, 0);
        FUN_00ae6970(&rec);
    }
    return found[0] + 4;
}

// @ 0x00ace320
void GonzagoSub2::FUN_00ace320()
{
    *(void**)this = (void*)0x145a1c8;
    *((void**)this + 1) = (void*)0x145a1c4;
    *((void**)this + 7) = (void*)0x145a1bc;
    int* g = *(int**)((char*)this + 0xa4);
    if (g) {
        (*(void (__thiscall*)(int*, int))(*g))(g, 1);
        *(void**)((char*)this + 0xa4) = 0;
    }
    int* b = *(int**)((char*)this + 0xbc);
    if (b) {
        (*(void (__thiscall*)(int*, int))(*b))(b, 1);
        *(void**)((char*)this + 0xbc) = 0;
    }
    FUN_00b95070((char*)this + 0x160);
    FUN_00b95070((char*)this + 0x12c);
    FUN_00ac9d90((char*)this + 0x118);
    int* p104 = *(int**)((char*)this + 0x104);
    int d = *(int*)((char*)this + 0x10c) - (int)p104;
    if ((d & 0xfffffffe) > 2 && p104) operator_delete(p104);
    FUN_00aca820((int*)((char*)this + 0xe0), (int*)*(int*)((char*)this + 0xe8));
    *(int*)((char*)this + 0xec) = 0;
    if (*(uint32*)((char*)this + 0xe8) > 1) operator_delete(*(void**)((char*)this + 0xe4));
    FUN_00accd70((int*)((char*)this + 0xc0), (int*)*(int*)((char*)this + 0xc8));
    *(int*)((char*)this + 0xcc) = 0;
    if (*(uint32*)((char*)this + 0xc8) > 1) operator_delete(*(void**)((char*)this + 0xc4));
    FUN_00aca7b0((int*)((char*)this + 0xa8), (int*)*(int*)((char*)this + 0xac));
    if (*(void**)((char*)this + 0xa8)) operator_delete(*(void**)((char*)this + 0xa8));
    FUN_00aca7b0((int*)((char*)this + 0x88), (int*)*(int*)((char*)this + 0x8c));
    if (*(void**)((char*)this + 0x88)) operator_delete(*(void**)((char*)this + 0x88));
    void* e = *(void**)((char*)this + 0x20);
    if (e && *(int*)((char*)e - 4)) operator_delete(e);
    *(void**)((char*)this + 0x1c) = (void*)0x13eb394;
    (*((void (__thiscall*)(void*))SP_cGonzagoSubsystem_dtor))(this);
}

// @ 0x00ace4e0
void CCityOwner::FUN_00ace4e0(void* param_2)
{
    int* app = (int*)SP_App_s00ac_d4a0();
    int* a = (int*)(*(int (__thiscall*)(int*))((char*)*app + 0x50))(app);
    (*(void (__thiscall*)(int*))((char*)*a + 0x1c))(a);
    int st1[3], st2[3];
    FUN_007c4900(st1, st2);
    void* mgr = SP_NounManager();
    int vec = (int)SP_cGameNounManager_GetGameDataVector(mgr, (void*)0xcd7d10, (void*)0xd3d420, (void*)0xacdff0, (void*)0xb1e500, (void*)0x18c43e8);
    int city = FUN_00ac9310(vec + 4, st1, false);
    int* g = (int*)mpA4;
    if (city != *(int*)((char*)g + 0xaf0)) {
        FUN_00d60f00(g, city);
    }
    FUN_00d5fb60(g, (int)param_2, 0);
    int* gg = *(int**)((char*)g + 0xaf0);
    if (gg && DAT_0168d248) {
        (*(void (__thiscall*)(int*))((char*)*gg + 0x78))(gg);
    }
}

// @ 0x00ace5a0
void NounVisibility::Update(int unused, uint32_t dt)
{
    if (dt > 0) {
        gTimer += (float)dt * 0.001f;
        if (gTimer < gThreshold)
            return;
        gTimer = 0.0f;
    }
    NounManager* pMgr = GetNounManager();
    gStat2 = 0;
    gStat1 = 0;
    gStat0 = 0;
    bool bModeA = (int)GetCurrentGameMode() == 0x1654c01;
    bool bModeB = (int)GetCurrentGameMode() == 0x1654c01;
    int playerID;
    if (pMgr->GetPlayerTribe())
        playerID = pMgr->GetPlayerTribe()->GetID();
    else
        playerID = -1;

    // pass 1
    {
        VecOut<NounObj1>* pVec = (VecOut<NounObj1>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_ace070, F_b1e500, 0x36be27e);
        const PtrVec_s00ac_e5a0<NounObj1>& vec = pVec->mVec;
        NounObj1** it = vec.begin();
        NounObj1** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj1* p = *it;
            if (p->IsRemoved() || p->mTypeID == 0 || p->mField110 == 0 || p->mbDone != 0)
                continue;
            Ref** ppNoun = &p->mpNoun;
            if (*ppNoun && (*ppNoun)->IsDead()) {
                p->mbDone = 1;
                ReleaseNoun(*ppNoun);
                continue;
            }
            if (p->mTypeID == 0x1be418e) {
                if (*ppNoun == 0)
                    ActivateObj(p, -1, -1);
                continue;
            }
            if (p->mFlags & 0x100)
                continue;
            if (p->mbSpawned != 0) {
                Placement* pPlace = FindPlacement(ppNoun);
                const Vec3* pPos;
                if (pPlace)
                    pPos = pPlace->GetPosition();
                else
                    pPos = &p->mPos;
                if (Func_ac8d80(pPos)) {
                    if (*ppNoun) {
                        if (pPlace) {
                            const Vec3* v = pPlace->GetPosition();
                            p->mPos = *v;
                            const Quat4* q = pPlace->GetRotation();
                            p->mRot = *q;
                        }
                        pMgr->RemoveNoun(*ppNoun);
                        ReleaseNoun(*ppNoun);
                    }
                    p->mbSpawned = 0;
                } else if (*ppNoun == 0) {
                    if (Func_ac8df0(&p->mPos))
                        ActivateObj(p, -1, -1);
                }
            } else {
                if (Func_ac8df0(&p->mPos)) {
                    p->mbSpawned = 1;
                    if (*ppNoun == 0)
                        ActivateObj(p, -1, -1);
                }
            }
        }
    }

    // pass 2
    ModeInfo* pMode = GetModeInfo();
    int mode = pMode->mMode;
    if (mode != 1 && mode != 2) {
        VecOut<NounObj2>* pVec = (VecOut<NounObj2>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_ace0f0, F_b1e500, 0x18eb45e);
        const PtrVec_s00ac_e5a0<NounObj2>& vec = pVec->mVec;
        NounObj2** it = vec.begin();
        NounObj2** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj2* p = *it;
            if (p->IsRemoved() || p->mbFlag135 == 0 || p->mbFlagB67 == 0)
                continue;
            if (!(bModeB == 1 || !p->Func_c0c0e0()))
                continue;
            HTable& tbl = mTable;
            uint32_t key = p->mKey;
            void* pEnd = tbl.End();
            if (tbl.find(key).mpNode != pEnd)
                continue;
            if (p->mSub.IsLocked())
                continue;
            int id = p->GetOwnerID();
            if (id != -1 && id == playerID)
                continue;
            if (Func_ac8d80(p->mSub.GetPosition()))
                p->Activate(true);
        }
    }

    // pass 3
    {
        int nCount = 0;
        VecOut<NounObj3>* pVec = (VecOut<NounObj3>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e);
        const PtrVec_s00ac_e5a0<NounObj3>& vec = pVec->mVec;
        NounObj3** it = vec.begin();
        NounObj3** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj3* p = *it;
            if (p->IsRemoved())
                continue;
            if (p->mbFlag84 == 0 && bModeA && gCurrentID >= 0 && (gCurrentID < p->mRangeMin || gCurrentID > p->mRangeMax)) {
                p->Func_c6ace0(false);
                if (p->mpHelper)
                    p->mpHelper->mbFlag = 1;
                continue;
            }
            bool bActivate = false;
            if (p->Func_c6a020()) {
                bool bInside = false;
                if (p->mbFlag84 == 0) {
                    const Vec3* pPos = p->Func_c6acc0();
                    for (Sphere* s = mpSpheresBegin; s != mpSpheresEnd; ++s) {
                        float dx = pPos->x - s->x, dy = pPos->y - s->y, dz = pPos->z - s->z;
                        if (s->r2b > dz * dz + dy * dy + dx * dx) { bInside = true; break; }
                    }
                } else {
                    bInside = true;
                }
                if (!bInside) {
                    p->Func_c6ace0(false);
                } else {
                    const Vec3* pPos = p->Func_c6acc0();
                    float dx = pPos->x - gPoint.x, dy = pPos->y - gPoint.y, dz = pPos->z - gPoint.z;
                    bool bNear = 400.0f > dz * dz + dy * dy + dx * dx;
                    if (p->mpHelper)
                        bNear = p->mpHelper->mSub.IsHidden();
                    p->mbNear = !bNear;
                }
            } else {
                if (p->mbFlag84 != 0) {
                    bActivate = true;
                } else if (nCount < gMaxPerTick) {
                    const Vec3* pPos = p->Func_c6acc0();
                    for (Sphere* s = mpSpheresBegin; s != mpSpheresEnd; ++s) {
                        float dx = pPos->x - s->x, dy = pPos->y - s->y, dz = pPos->z - s->z;
                        if (s->r2a >= dz * dz + dy * dy + dx * dx) {
                            if (p->Func_c6a030())
                                bActivate = true;
                            break;
                        }
                    }
                }
                if (bActivate) {
                    p->Func_c6ace0(true);
                    if (p->mpHelper)
                        p->mpHelper->mbFlag = 1;
                    p->Func_c6b540();
                    ++nCount;
                }
            }
        }
    }
}

// @ 0x00acebd0
void cCastingManager::CastNoun(NounObj3* pNoun, char bFlag)
{
    PlanetModel* pModel = SP_PlanetModel_s00ac_e5a0();
    if (pModel == 0)
        return;

    const Vec3* p = pNoun->Func_c6acc0();
    float nx = p->x;
    float ny = p->y;
    float nz = p->z;
    float ax = fabsf(nx);
    float ay = fabsf(ny);
    float az = fabsf(nz);

    int idxU;
    int idxV;
    unsigned face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            idxU = (int)((ny / nx + kOne) * kTwo);
            idxV = (int)((nz / ax + kOne) * kTwo);
            face = (nx < kZero) ? 3 : 2;
        } else {
            idxU = (int)((nz / ny + kOne) * kTwo);
            idxV = (int)((nx / ay + kOne) * kTwo);
            face = (ny < kZero) ? 5 : 4;
        }
    } else {
        idxU = (int)((nx / nz + kOne) * kTwo);
        idxV = (int)((ny / az + kOne) * kTwo);
        face = (nz < kZero) ? 1 : 0;
    }
    if (idxU == 4)
        idxU = 3;
    if (idxV == 4)
        idxV = 3;

    uint32_t key = (uint32_t)(idxU + (idxV + (int)face * 4) * 4);

    HFind found;
    CellMap* pCells = &mCells;
    pCells->Find(&found, &key);

    if (found.mpNode == pCells->mpBucketArray[pCells->mnBucketCount]) {
        PlanetModel* pModel2 = SP_PlanetModel_s00ac_e5a0();
        float water = pModel2->GetWaterHeight();
        float fcU = (float)idxU;
        float fcV = (float)idxV;
        uint32_t cellKey = (uint32_t)idxU + ((uint32_t)idxV + face * 4) * 4;

        TileNode_s00ac_e5a0* pNode = pCells->TileAt(&cellKey);

        float u = (fcU + kHalf) * kHalf - kOne;
        float v = (fcV + kHalf) * kHalf - kOne;
        float len = kOne / sqrtf(v * v + u * u + kOne);
        float sl = len;
        if (face & 1)
            sl = -len;
        const uint8_t* ax3 = &g_FaceAxes[(face >> 1) * 4];
        float dir[3];
        dir[ax3[0]] = sl * u;
        dir[ax3[1]] = len * v;
        dir[ax3[2]] = sl;

        float rad = pModel2->GetRadiusAt((Vec3*)dir);
        float r = rad > water ? rad : water;

        float u2 = (fcU * kQuarter) * kTwo - kOne;
        float v2 = (fcV * kQuarter) * kTwo - kOne;
        float len2 = kOne / sqrtf(v2 * v2 + u2 * u2 + kOne);
        float sl2 = len2;
        if (face & 1)
            sl2 = -len2;
        float dir2[3];
        dir2[ax3[0]] = sl2 * u2;
        dir2[ax3[1]] = len2 * v2;
        dir2[ax3[2]] = sl2;

        float other[3];
        pModel2->SnapToSurface((Vec3*)other, (Vec3*)dir2);

        pNode->mPos.x = dir[0] * r;
        pNode->mPos.y = dir[1] * r;
        pNode->mPos.z = dir[2] * r;
        float dx = pNode->mPos.x - other[0];
        float dy = pNode->mPos.y - other[1];
        float dz = pNode->mPos.z - other[2];
        pNode->mDist = sqrtf(dy * dy + (dz * dz + dx * dx));

        pCells->Find(&found, &key);
    }

    if (found.mpNode != pCells->mpBucketArray[pCells->mnBucketCount]) {
        Publication pub;
        pub.mpObj = (IRefCounted*)(void*)pNoun;
        if (bFlag == 0) {
            if (pub.mpObj)
                pub.mpObj->AddRef();
            FUN_00e1c7f0((char*)found.mpNode + 0x40, 0, &pub.mpObj);
        } else {
            if (pub.mpObj)
                pub.mpObj->AddRef();
            FUN_00e1c7f0((char*)found.mpNode + 0x54, 0, &pub.mpObj);
        }
        if (pub.mpObj)
            pub.mpObj->Release();
    }
}

// @ 0x00acf0b0
template <> void SpVector<cTribeEntry>::DoInsertValue(cTribeEntry* pos, const cTribeEntry& value)
{
    if (mpEnd != mpCapacity) {
        cTribeEntry* v = const_cast<cTribeEntry*>(&value);
        if (v >= pos && v < mpEnd)
            v += 1;

        if (mpEnd)
            ((EntryOps*)(void*)mpEnd)->FUN_00aca970(mpEnd - 1);

        FUN_00acc330((int*)pos, (int*)(mpEnd - 1), (int*)mpEnd);

        pos->mpTribe = v->mpTribe;
        pos->mMembers = v->mMembers;

        mpEnd += 1;
        return;
    }

    unsigned n = (unsigned)(mpEnd - mpBegin);
    cTribeEntry* newBuf;
    if (n != 0) {
        n *= 2;
        if (n == 0) {
            newBuf = 0;
            goto L;
        }
    } else {
        n = 1;
    }
    newBuf = (cTribeEntry*)operator_new(n * 0x18, kSimulatorName, 0, 0, kAllocatorFile, 0xd1);
L:
    {
        cTribeEntry* p = mpBegin;
        cTribeEntry* mid = FUN_00acaab0(p, pos, newBuf);
        FUN_00acab70(p, pos, newBuf);

        if (mid)
            ((EntryOps*)(void*)mid)->FUN_00aca970(const_cast<cTribeEntry*>(&value));

        cTribeEntry* pLast = mpEnd;
        cTribeEntry* pNewEnd = FUN_00acaab0(pos, pLast, mid + 1);
        FUN_00acab70(pos, pLast, mid + 1);

        cTribeEntry* pOld = mpBegin;
        if (pOld && ((int*)pOld)[-1] != 0)
            operator_delete(pOld);

        mpEnd = pNewEnd;
        mpBegin = newBuf;
        mpCapacity = (cTribeEntry*)((char*)newBuf + n * 0x18);
    }
}

// @ 0x00acf230
cCastingManager* cCastingManager::Construct()
{
    ((CtorNoArg*)this)->FUN_00b5b960();
    mpVtbl1c = (void*)0x13eb394;
    mpVtbl0  = (void*)0x145a1c8;
    mpVtbl4  = (void*)0x145a1c4;
    mpVtbl1c = (void*)0x145a1bc;

    mField34 = 0;
    mpInlineBegin = (char*)this + 0x38;
    mpInlineEnd   = (char*)this + 0x38;
    mpInlineCap   = (char*)mpInlineBegin + 0x50;
    mField88 = 0;
    mField8c = 0;
    mField90 = 0;
    mFieldA0 = -1;
    mpCityVisualizer = 0;
    mpTribesBegin = 0;
    mpTribesEnd = 0;
    mpTribesCapacity = 0;
    mpAbandonedVisualizer = 0;

    const float kLoad = kOne;
    const float kGrow = kTwo;
    void** const pEmptyBuckets = (void**)&g_EmptyBuckets;
    mCells.mLoadFactor = kLoad;
    mCells.mGrowFactor = kGrow;
    mCells.mUnused0c = 0;
    mCells.mSize = 0;
    mCells.mnBucketCount = 1;
    mCells.mpBucketArray = pEmptyBuckets;

    mCells2.mLoadFactor = kLoad;
    mCells2.mGrowFactor = kGrow;
    mCells2.mpBucketArray = pEmptyBuckets;
    mCells2.mnBucketCount = 1;
    mCells2.mUnused0c = 0;
    mCells2.mSize = 0;

    mField100 = 0;
    mField101 = 0;
    mpString104 = kEmptyString16;
    mpString108 = kEmptyString16;
    mpString10c = kEmptyString16 + 1;
    mField114 = 0;
    mpField118 = 0;
    mpField11c = 0;
    mpField120 = 0;

    ((CtorNoArg*)&mSub12c)->FUN_00b95050();
    ((CtorNoArg*)&mSub160)->FUN_00b95050();

    void* pVis = operator_new(0xc88, kCityVisualizerName, 0, 0, 0, 0);
    void* pCity = pVis ? ((VisCtor*)pVis)->FUN_00d5e730() : 0;
    mpCityVisualizer = pCity;

    void* pAband = operator_new(0x18, kAbandonedName, 0, 0, 0, 0);
    if (pAband)
        mpAbandonedVisualizer = ((VisCtor*)pAband)->FUN_00d59580();
    else
        mpAbandonedVisualizer = 0;

    return this;
}

// @ 0x00acf3e0
void cCastingManager::SpawnHerdFromProfile(Vec3* pPos, void* pMgr)
{
    GetActivePlanet_s00ac_e5a0();
    cSpeciesArchetype* pArch = FUN_00401090_s00ac_e5a0()->GetSpeciesArchetype(0x2615134d, 0);

    const RawVec3* rp = (const RawVec3*)pPos;
    if (rp->x != g_NoPosition.x || rp->y != g_NoPosition.y || rp->z != g_NoPosition.z) {
        void* pProfile = FUN_00401090_s00ac_e5a0()->GetProfile((const ResourceKey*)pPos);
        NounObj3* pHerd = ((NounManagerSpawn*)GetNounManager())->CreateNoun(&pPos->x, pProfile, 1, 0, 0, 0);
        if (pHerd) {
            pHerd->Func_c6ace0(1);
            pHerd->mOwnerSpeciesKey = pArch->mSpeciesKey;
            pHerd->mUsedFallback = 0;
            pHerd->UpdateFromArchetype(pArch, 1);
            pHerd->mSpawnTime = g_SpawnTime;
            pHerd->Func_c6b540();
            CastNoun(pHerd, 1);
            GetPollinator()->UpdateProperty(0xef7163ab, pPos);
        }
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

// @ 0x00ad0590
void __fastcall FUN_00ad0590(ElemVec* self, int, Elem20* pos, Elem20* val)
{
    Elem20* last = self->end;
    if (last != self->cap) {
        if (pos <= val && val < last)
            ++val;
        if (last) {
            last->key       = last[-1].key;
            last->list.vt   = (void*)0x0145a164;
            last->list.b8   = last[-1].list.b8;
            last->list.b9   = last[-1].list.b9;
            FUN_00aca9d0(&last->list.vec, 0, &last[-1].list.vec);
        }
        FUN_00accf20((int)pos, (int)(last - 1), (int)last);
        pos->key     = val->key;
        pos->list.b8 = val->list.b8;
        pos->list.b9 = val->list.b9;
        FUN_00acbd90(&pos->list.vec, 0, &val->list.vec);
        self->end = last + 1;
        return;
    }

    int n = (int)(last - self->begin);
    int newcap;
    if (n == 0)
        newcap = 1;
    else
        newcap = n * 2;

    Elem20* buf = 0;
    if (newcap) {
        buf = (Elem20*)FUN_00f473a0((uint)newcap * 0x20, "Simulator", 0, 0,
                                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                    0xd1);
    }

    Elem20* mid = FUN_00acbb20(self->begin, pos, buf);
    FUN_00aca2f0(self->begin, pos, buf);
    if (mid) {
        mid->key     = val->key;
        mid->list.vt = (void*)0x0145a164;
        mid->list.b8 = val->list.b8;
        mid->list.b9 = val->list.b9;
        FUN_00aca9d0(&mid->list.vec, 0, &val->list.vec);
    }
    Elem20* newEnd = FUN_00acbb20(pos, last, mid + 1);
    FUN_00aca2f0(pos, last, mid + 1);
    if (self->begin)
        FUN_00f47380(self->begin);
    self->end   = newEnd;
    self->begin = buf;
    self->cap   = buf + newcap;
}

// @ 0x00ad0710
void __cdecl FUN_00ad0710(void* stream, TribeVec* vec)
{
    TribeEntry* b = vec->begin;
    TribeEntry* e = vec->end;
    void* cleared = FUN_00acc2d0(e, e, b);
    FUN_00aca820_s00ad_0510(vec, 0, cleared, vec->end);
    vec->end = vec->begin;

    int count = 0;
    void* obj = VTC(stream, 0x20, TC_p0)(stream);
    void* io  = VTC(obj, 0x18, TC_p0)(obj);
    ReadInt32_s00ad_0510(io, &count, 1, 0);
    FUN_00acccb0(vec, 0, count);

    for (int i = 0; i < count; ++i) {
        TribeEntry tmp;
        tmp.primary.p   = 0;
        tmp.refs.begin  = 0;
        tmp.refs.end    = 0;
        tmp.refs.cap    = 0;
        tmp.refs.alloc0 = 0;
        tmp.refs.alloc1 = 0;

        CVarListSerializer ser;
        ser.ctor(&tmp, (void*)0x015660f0, 0x1a80d26);
        ser.Read(stream);

        if (vec->end < vec->cap) {
            TribeEntry* slot = vec->end;
            vec->end = slot + 1;
            if (slot)
                FUN_00aca970(slot, 0, &tmp);
        } else {
            FUN_00acf0b0(vec, 0, &tmp);
        }
        destroyTribeEntry(&tmp);
    }

    VTC(stream, 0x1c, TC_v0)(stream);
}

// @ 0x00ad08f0
void __fastcall FUN_00ad08f0(cCityVisualizer_s00ad_0510* self, int)
{
    void* nouns = NounManager_s00ad_0510();
    g_1565cfc = 0;
    g_167a378 = 0;
    FUN_00acd4a0(self, 0);
    FUN_00accd70_s00ad_0510(&self->field_c0, 0, self->field_c0.a4, self->field_c0.a8);
    self->field_c0.ac = 0;

    int tribeCount = (int)(self->tribes.end - self->tribes.begin);
    for (int i = 0; i < tribeCount; ++i)
        FUN_00c8fc50(&self->tribes.begin[i], 0, 0);

    TribeEntry* tb = self->tribes.begin;
    TribeEntry* te = self->tribes.end;
    void* cleared = FUN_00acc2d0(te, te, tb);
    FUN_00aca820_s00ad_0510(&self->tribes, 0, cleared, self->tribes.end);
    self->tribes.end = (TribeEntry*)((char*)self->tribes.end - tribeCount * 0x18);

    for (Elem20* rec = self->registry.begin; rec != self->registry.end; ++rec) {
        int n = (int)(rec->list.vec.end - rec->list.vec.begin);
        for (int i = 0; i < n; ++i) {
            RegElem_s00ad_0510* r = &rec->list.vec.begin[i];
            if (r->flag4)
                FUN_00accf80(self, 0, r->ptr8);
            if (r->ptr8) {
                void* v = VTC(r->ptr8, 0x0c, TC_p1)(r->ptr8, (void*)0xce9f6639);
                if (v)
                    VTC(v, 0x44, TC_v0)(v);
            }
            if (nouns)
                RemoveNoun(nouns, 0, r->ptr8);
        }
        RegElem_s00ad_0510* rb = rec->list.vec.begin;
        RegElem_s00ad_0510* re = rec->list.vec.end;
        RegElem_s00ad_0510* ri = (RegElem_s00ad_0510*)FUN_00ac9740(re, re, rb);
        while (ri < re) {
            VTC(ri, 0x00, TC_v1)(ri, 0);
            ++ri;
        }
        rec->list.vec.end = (RegElem_s00ad_0510*)((char*)rec->list.vec.end - (int)(re - rb) * 0x0c);
    }

    Elem20* eb = self->registry.begin;
    Elem20* ee = self->registry.end;
    void* ec = FUN_00accec0_s00ad_0510(ee, ee, eb);
    FUN_00aca7b0_s00ad_0510(&self->registry, 0, ec, self->registry.end);
    self->registry.end = (Elem20*)((char*)self->registry.end - (int)(ee - eb) * 0x20);

    FUN_00693230(&self->hash_e0, 0, self->hash_e0.a4, self->hash_e0.a8);
    self->hash_e0.ac = 0;
    FUN_00acc770(self, 0);
    self->f_100 = 0;
}

// @ 0x00ad0b30
bool cCastingManager::Read(SP::cIObjectDatabaseIStream& archive)
{
    if (mField88 != mField8c)
        Reset();
    void* stream = reinterpret_cast<CastingArchive*>(&archive)->GetStreamHolder()->GetStream();
    int version;
    ReadInt32_s00ad_0510(stream, &version, 1, 0);
    SP::cVarListSerializer serializer(this, gCastingSerializerList, SP::cVarListSerializer::kSignature);
    if (serializer.Serialize(archive) && FUN_00b98c00(&archive))
        return true;
    return false;
}

// @ 0x00ad0bd0
void __fastcall FUN_00ad0bd0(cCityVisualizer_s00ad_0510* self, int)
{
    void* ms = MessageServer();
    if (ms) {
        VTC(ms, 0x2c, TC_v3)(ms, self ? &self->msg1c : 0, (void*)0x1a0219e, (void*)-0x270f);
        VTC(ms, 0x2c, TC_v3)(ms, self ? &self->msg1c : 0, (void*)0x6130eb9, (void*)-0x270f);
    }
    if (self->mp_city)
        ((CityOps*)self->mp_city)->FUN_00d60f00_s00ad_0510(0);
    if (self->p_bc)
        ((CityOps*)self->p_bc)->FUN_00d5bb30();
    ((CityOps*)self)->FUN_00ad08f0();

    Rec20_s00ad_0510* rb = self->rec.begin;
    Rec20_s00ad_0510* re = self->rec.end;
    FUN_00copy_Rec20(re, re, rb);
    self->rec.end = (Rec20_s00ad_0510*)((char*)self->rec.end - (int)(re - rb) * 0x14);
    self->f_a0 = -1;
}

// @ 0x00ad0ca0
RegList_s00ad_0510* ElemVec::get(int* key)
{
    Elem20* last = end;
    Elem20* it = FUN_00aca1f0_s00ad_0510(begin, last, key, less);
    if (it == last || *key < it->key) {
        RegVec empty;
        empty.begin = 0;
        empty.end   = 0;
        empty.cap   = 0;

        Elem20 value;
        value.key     = *key;
        value.list.vt = (void*)0x0145a164;
        value.list.b8 = 0;
        value.list.b9 = 0;
        value.list.vec.FUN_00aca9d0(&empty);

        Elem20* e = end;
        Elem20* lo;
        Elem20* hi;
        if (it != e && value.key < it->key) {
            lo = begin;
            hi = it;
        } else {
            lo = it;
            hi = e;
        }
        it = FUN_00aca1f0_s00ad_0510(lo, hi, &value.key, less);
        if (it == end || value.key < it->key)
            it = FUN_00ad0890(it, &value);
        value.list.vec.FUN_00ac8ec0();
        empty.FUN_00ac8ec0();
    }
    return &it->list;
}

// @ 0x00ad0d90
void __cdecl FUN_00ad0d90(void* stream, ElemVec* vec)
{
    Elem20* vb = vec->begin;
    Elem20* ve = vec->end;
    void* cleared = FUN_00accec0((uchar*)ve, (uchar*)ve, (uchar*)vb);
    FUN_00aca7b0_s00ad_0510(vec, 0, cleared, vec->end);
    vec->end = vec->begin;

    int count = 0;
    void* obj = VTC(stream, 0x20, TC_p0)(stream);
    void* io  = VTC(obj, 0x18, TC_p0)(obj);
    ReadInt32_s00ad_0510(io, &count, 1, 0);

    for (int i = 0; i < count; ++i) {
        Elem20 entry;
        entry.list.vt = (void*)0x0145a164;
        entry.list.b8 = 0;
        entry.list.b9 = 0;
        entry.list.vec.begin  = 0;
        entry.list.vec.end    = 0;
        entry.list.vec.cap    = 0;
        entry.list.vec.alloc0 = 0;
        entry.list.vec.alloc1 = 0;

        void* o2 = VTC(stream, 0x20, TC_p0)(stream);
        void* i2 = VTC(o2, 0x18, TC_p0)(o2);
        ReadInt32_s00ad_0510(i2, &entry.key, 1, 0);
        VTC(stream, 0x1c, TC_v0)(stream);

        CVarListSerializer ser;
        ser.ctor(&entry, (void*)0x01566000, 0x1a80d26);
        ser.Read(stream);
        VTC(stream, 0x1c, TC_v0)(stream);

        Elem20 value;
        value.key     = entry.key;
        value.list.vt = (void*)0x0145a164;
        value.list.b8 = entry.list.b8;
        value.list.b9 = entry.list.b9;
        value.list.vec.begin  = 0;
        value.list.vec.end    = 0;
        value.list.vec.cap    = 0;
        value.list.vec.alloc0 = 0;
        value.list.vec.alloc1 = 0;
        FUN_00aca9d0(&value.list.vec, 0, &entry.list.vec);

        Elem20* last = vec->end;
        Elem20* it = FUN_00aca1f0_s00ad_0510(vec->begin, last, &value.key, vec->less);
        bool fresh;
        Elem20* slot;
        if (it != last && value.key >= it->key) {
            fresh = false;
            slot  = it;
        } else {
            if (it == last && last != vec->cap) {
                Elem20* e = last;
                vec->end = e + 1;
                if (e) {
                    e->key     = value.key;
                    e->list.vt = (void*)0x0145a164;
                    e->list.b8 = value.list.b8;
                    e->list.b9 = value.list.b9;
                    FUN_00aca9d0(&e->list.vec, 0, &value.list.vec);
                }
            } else {
                FUN_00ad0590(vec, 0, it, &value);
            }
            slot  = vec->begin + (int)(it - vec->begin);
            fresh = true;
        }

        destroyRegVec(&value.list.vec);
        if (!fresh) {
            slot->list.b8 = entry.list.b8;
            slot->list.b9 = entry.list.b9;
            FUN_00acbd90(&slot->list.vec, 0, &entry.list.vec);
        }
        destroyRegVec(&entry.list.vec);
    }

    VTC(stream, 0x1c, TC_v0)(stream);
}

// @ 0x00ad1000
void __fastcall FUN_00ad1000(cCityVisualizer_s00ad_0510* self, int, void* tag, int count)
{
    if (count <= 0)
        return;

    RegList_s00ad_0510* list = self->registry.get((int*)&tag);
    int have = (int)(list->vec.end - list->vec.begin);
    void* nouns = NounManager_s00ad_0510();

    if (have < count) {
        FUN_00acd920(&list->vec, 0, count);
        for (int i = have; i < count; ++i) {
            RegElem_s00ad_0510* r = &list->vec.begin[i];
            void* noun = CreateNoun(nouns, 0, tag);
            void* old  = r->ptr8;
            if (noun != old) {
                if (noun)
                    VTC(noun, 0x00, TC_v0)(noun);
                r->ptr8 = noun;
                if (old)
                    VTC(old, 0x04, TC_v0)(old);
            }
            r->flag4 = 0;
        }
    } else if (count < have) {
        for (int i = count; i < have; ++i)
            RemoveNoun(nouns, 0, list->vec.begin[i].ptr8);
        FUN_00acd920(&list->vec, 0, count);
    }

    void* first = list->vec.begin[0].ptr8;
    list->b8 = VTC(first, 0x0c, TC_p1)(first, (void*)0x116dd1b) != 0;
    if (list->b8 && have < count) {
        for (int i = have; i < count; ++i) {
            void* o = list->vec.begin[i].ptr8;
            if (!o)
                continue;
            void* v = VTC(o, 0x0c, TC_p1)(o, (void*)0x116dd1b);
            if (!v)
                continue;
            VignetteObj* vo = (VignetteObj*)v;
            vo->f75 = 0;
            VTC(v, 0x38, TC_v1)(v, &g_167a390);
            vo->f71 = 1;
        }
    }

    list->b9 = VTC(first, 0x0c, TC_p1)(first, (void*)0x11c0ba3) != 0;
    void* third = VTC(first, 0x0c, TC_p1)(first, (void*)0xce9f6639);
    if (third && have < count) {
        for (int i = have; i < count; ++i) {
            void* o = list->vec.begin[i].ptr8;
            if (!o)
                continue;
            void* v = VTC(o, 0x0c, TC_p1)(o, (void*)0xce9f6639);
            if (v)
                FUN_00c0bf00(v, 0, 1);
        }
    }
}

// ---- items of slice s00ad0510 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void*  __cdecl FUN_00f473a0(uint, const char*, int, int, const char*, int); // operator new
// ---- items of slice s00ad0510 end

// ---- items of slice s00af9aa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
class IRefCounted_s00af_9aa0 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace EA {
template <class T>
class AutoRefCount_s00af_9aa0 {
 public:
  T* mpObject;
  AutoRefCount_s00af_9aa0() : mpObject(0) {}
  AutoRefCount_s00af_9aa0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s00af_9aa0(const AutoRefCount_s00af_9aa0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s00af_9aa0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s00af_9aa0& operator=(T* p) {
    if (p != mpObject) {
      T* const old = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace SP {
struct cSPVector3_s00af_9aa0 { float mX, mY, mZ; };
}
namespace SP {
struct cSPQuaternion_s00af_9aa0 { float x, y, z, w; };
}
namespace SP {
class cGameData_s00af_9aa0 : public EA::IRefCounted_s00af_9aa0 {};
}
namespace SP {
class cInteractionAgent_s00af_9aa0 : public EA::IRefCounted_s00af_9aa0 {};
}
namespace SP {
class cActionCircle_s00af_9aa0 {
 public:
  class tSlot { public:
    bool mOccupied;                                 // +0x0
    char _pad0[3];
    EA::AutoRefCount_s00af_9aa0<cGameData_s00af_9aa0> mpReservingNoun;    // +0x4
    unsigned int mReservingId;                      // +0x8
    cSPVector3_s00af_9aa0 mPos;                                // +0xc

    void Reserve(cGameData_s00af_9aa0* noun);                  // 0xafa030
    void ReserveId(unsigned int id);                // 0xafa070
    void Clear();                                   // 0xafa0a0
    tSlot* CopyConstruct(const tSlot* src);         // 0xafa110
    tSlot* Assign(const tSlot* src);                // 0xafa230
  };

  cSPVector3_s00af_9aa0 mFacing;                               // +0x0
  float mRadius;                                    // +0xc
  float mSlotRadius;                                // +0x10
  cSPVector3_s00af_9aa0 mCenter;                               // +0x14
  float mAltitude;                                  // +0x20
  int mPacking;                                     // +0x24
  bool mbRelative;                                  // +0x28
  char _pad28[3];
  cSPQuaternion_s00af_9aa0 mOrientation;                       // +0x2c
  struct SlotVec {                                  // eastl::sp_vector<Agent> at +0x3c
    EA::AutoRefCount_s00af_9aa0<cInteractionAgent_s00af_9aa0>* mpBegin;
    EA::AutoRefCount_s00af_9aa0<cInteractionAgent_s00af_9aa0>* mpEnd;
    EA::AutoRefCount_s00af_9aa0<cInteractionAgent_s00af_9aa0>* mpCapacity;
    int mAllocator[2];
  } mAgents;
  struct SlotVector {                               // eastl::sp_vector<tSlot> at +0x50
    tSlot* mpBegin;
    tSlot* mpEnd;
    tSlot* mpCapacity;
    int mAllocator[2];
  } mSlots;

  void SetAtCenter(const cSPVector3_s00af_9aa0* center, float radius, const cSPVector3_s00af_9aa0* facing, float altitude);  // 0xaf9cf0
  void SetRelative(const cSPVector3_s00af_9aa0* center, const cSPQuaternion_s00af_9aa0* orient, float radius);              // 0xaf9d60
  int IsNonDefault() const;                          // 0xaf9ee0
  tSlot* FindFreeSlot();                             // 0xaf9f30
  int CountFreeSlots();                              // 0xaf9f60
  int CountOccupiedSlots();                          // 0xaf9fa0
  tSlot* SlotAt(unsigned int index);                 // 0xaf9ff0
  int FindClosestFreeSlot(const cSPVector3_s00af_9aa0* p);      // 0xafa5d0
  int FindClosestFreeSlotWeighted(const cSPVector3_s00af_9aa0* p, const cSPVector3_s00af_9aa0* q, float weight);  // 0xafa7c0
};
}
using SP::cSPVector3_s00af_9aa0;
using SP::cSPQuaternion_s00af_9aa0;
using SP::cActionCircle_s00af_9aa0;
using SP::cGameData_s00af_9aa0;
// ---- items of slice s00af9aa0 end

// ---- items of slice s00beb6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00be_b6d0 {
    float x, y, z;
    Vector3_s00be_b6d0() {}
    Vector3_s00be_b6d0(const Vector3_s00be_b6d0& o) : x(o.x), y(o.y), z(o.z) {}
};
struct SpVector_s00be_b6d0 {
    Vector3_s00be_b6d0* mpBegin;
    Vector3_s00be_b6d0* mpEnd;
    Vector3_s00be_b6d0* mpCapacity;
    uint8_t  mAllocator[8];
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
struct cCityWalls {
    void*    vtbl_a;             // 0x000
    void*    vtbl_b;             // 0x004
    uint8_t  pad_008[0x2c - 8];
    void*    vfptr_rc;           // 0x02c
    uint8_t  pad_030[0x34 - 0x30];
    uint8_t  sub34[1];           // 0x034  cSpatialObject
    uint8_t  pad_035[0x10c - 0x35];
    uint32_t field_10c;          // 0x10c
    SpVector_s00be_b6d0 mDockSlots;         // 0x110
    SpVector_s00be_b6d0 field_124;          // 0x124
    uint8_t  pad_138[0x198 - 0x138];
    SpVector_s00be_b6d0 field_198;          // 0x198
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

// ---- items of slice s00d56c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
struct RandomLinearCongruential {
    uint   RandomUint32Uniform(uint nRange);     // 0x00a68fb0
    double RandomDouble();                       // 0x009360d0
};
}
extern EA::RandomLinearCongruential g_random;    // 0x01601760
struct CGridQueue;                               // 0x01593270 (s_TribeQueue)
struct CModel {
    char mPad00[4];
    uint mFlags;                                 // +0x04, 0x800 = hidden
};
struct CAnimatingCreature {                      // CCitizen::mpAnim (+0xb54)
    char mPad00[0x64];
    bool mbField64;                              // +0x64
    char mPad65[0x180 - 0x65];
    CModel* mpModel;                             // +0x180
    bool Detach(int nMode);                      // 0x00a02b00
};
struct CVisualSub;                               // CCitizen sub-object at +0xc0
struct CCitizenBase {                            // virtual slots 0x00..0xe8
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
    virtual void SetState(int nState);                                               // +0x48
    virtual int  GetState();                                                         // +0x4c
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
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
    virtual void s56();                                                              // +0xe0
    virtual void SetInfo(void* pInfo);                                               // +0xe4
    virtual void InitFrom(void* pCity, int nMode, int nFlags, int nExtra);            // +0xe8
};
struct CVisualSub {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual void* Resolve();                                                         // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
    virtual void SetAngle(float fAngle);                                             // +0x40
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
    virtual void s21();                                                              // +0x54
    virtual bool IsReady();                                                          // +0x58
    char mData[0x4c];
};
struct CRecord12 { char mData[12]; };
struct CEntry {
    char mPad00[4];
    int  mnCount;                                // +0x04
    char mPad08[0x198 - 0x08];
};
struct CBehaviorOwner { char mData[0x68]; };
struct CGrid;
struct CTribe;
struct CCitizen : CCitizenBase {
    char mPad004[0x58 - 0x04];                   // +0x004
    CBehaviorOwner mBehavior;                    // +0x058
    CVisualSub mVisual;                          // +0x0c0
    uint mFlags;                                 // +0x110
    char mPad114[0xb4c - 0x114];
    CGrid* mpGrid;                               // +0xb4c
    char mPadB50[4];
    CAnimatingCreature* mpAnim;                  // +0xb54
    char mPadB58[0xf90 - 0xb58];
    bool mbFieldF90;                             // +0xf90
    char mPadF91[0xfb8 - 0xf91];
    CTribe* mpTribe;                             // +0xfb8
    bool mbFieldFBC;                             // +0xfbc
    char mPadFBD[0xff0 - 0xfbd];
    int  mnState;                                // +0xff0 (last state applied to the model)

    void SetSpecializedTool(int nTool);          // 0x00c279a0
    void SetFlag(int nFlag);                     // 0x00c0d950
    void UpdateEntry(int nEntry);                // 0x00c227a0
    void ClearEntry();                           // 0x00c227c0
};
struct CTribe {
    char mPad000[0x390];
    CEntry mEntries[4];                          // +0x390, stride 0x198
    char mPad9F0[0xaf0 - 0x9f0];
    void* mpCity;                                // +0xaf0

    CEntry* GetEntry(int nIndex);                // 0x00d576b0
};
// 0x00d576b0 belongs to another object; its slice body, visible here so that PlaceCitizen (0x00d57800) inlines it as in the slice
inline CEntry* CTribe::GetEntry(int nIndex)
{
    return &mEntries[nIndex];
}
struct CGridRange {
    char mData[0x14];
    void SetRange(uint nId, int nArg, float fMax, int nArg2);   // 0x00bc97f0
};
struct CGrid {
    char mPad00[8];
    CGridRange mRange;                           // +0x08
    char mPad1C[0x5fc - 0x1c];
    int  mnField5fc;                             // +0x5fc
    void ResetQueue(CGridQueue* pQueue);         // 0x00bcb660
    void ResetQueue();                           // 0x00bcb3d0
};
extern CGridQueue g_cityQueue;                   // 0x01592928
void __cdecl UpdateTimeScaled(CCitizen* pCitizen);                  // 0x00c0d3a0
struct CAnimShortcut {
    void SetTarget(CCitizen* pCitizen, int nMode);                  // 0x00b48770
};
CAnimShortcut* __cdecl GetAnimShortcut();                           // 0x00b3d310
namespace SP {
struct cCity_s00d5_6c30;
}
namespace SP {
struct BehaviorManager {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
    virtual void Attach(void* pOwner);                                               // +0x3c
};
}
namespace SP {
BehaviorManager* __cdecl GetBehaviorManager();                      // 0x00b3d260
}
namespace SP {
struct cCityVisualizer_s00d5_6c30;
}
namespace SP {
cCityVisualizer_s00d5_6c30* __cdecl GetVisualizer();                           // 0x00b3d480
}
namespace SP {
struct cDirectPropertyList_s00d5_6c30 {
    float GetFloatProperty(uint nPropertyId) const;                 // 0x006a2710
};
}
namespace SP {
extern cDirectPropertyList_s00d5_6c30* g_pAppProperties;                       // 0x015fd918
}
namespace SP {
struct cCityVisualizer_s00d5_6c30 {
    char mPad000[0xaf0];
    cCity_s00d5_6c30* mpCity;                               // +0xaf0
    int ComputeVisualizedPopulation();           // 0x00d57a00
    void SetupCultureStages(CCitizen* pTemplate);// 0x00accf80
};
}
namespace SP {
struct cCity_s00d5_6c30 {
    int GetCreatureCount();                      // 0x00bd8120
};
}
struct CInfoSub { char mData[0x40]; };
struct CCitizenInfo {
    char mPad00[0x89];
    bool mbFlag89;                               // +0x89
    char mPad8A[0xc4 - 0x8a];
    CInfoSub mSub;                               // +0xc4
};
extern CInfoSub g_defaultInfo;                   // 0x01583e08
struct CCitizenManager {
    char mPad000[0xa64];
    CCitizen** mpCitizens;                       // +0xa64
    CCitizen** mpCitizensEnd;                    // +0xa68
    char mPadA6C[0xb6c - 0xa6c];
    CRecord12* mpRecords;                        // +0xb6c

    CRecord12* FindSlot(CCitizen* pCitizen);                       // 0x00d579a0
    void ApplyToAll(CCitizen* pTemplate, CCitizenInfo* pInfo);     // 0x00d57a60
};
template <class T> const T& MaxValue(const T& a, const T& b)
{
    return a < b ? b : a;
}
struct Elem16 {
    uint  mnId;                                  // +0x00
    float mf0;                                   // +0x04
    float mf1;                                   // +0x08
    float mf2;                                   // +0x0c
};
// ---- items of slice s00d56c30 end

// ---- items of slice s00d59b00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_szSimulator[];        // 0x013f09b4 "Simulator"
extern const char g_szAllocatorH[];       // 0x013ebb38 eastl allocator.h path
extern const float g_HK_REAL_ZERO;        // 0x01485378
extern const float g_HK_REAL_ONE;         // 0x01485720
extern const float g_zero_13eb1bc;        // 0x013eb1bc (0.0f)
extern const float g_acos_one;            // 0x0169ec80 quaternion/axis constant fed to FUN_0059aed0
void* __cdecl operator_new(uint32 size, const char* pName, int a, int b, const char* pAlloc, uint32 line); // 0x00f473a0
struct QuatPair {
    float q[4];      // +0x00
    Vec3  v;         // +0x10
};
struct cSteerObj {
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
    virtual const QuatPair* GetOrientation();          // +0x30
    virtual void v34();
    virtual void v38();
    virtual void SetOrientation(const QuatPair* q);    // +0x3c
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual const Vec3* GetDirection(Vec3* out);       // +0x5c
};
struct IRefCounted_s00d5_9b00 {
    virtual void AddRef();                 // slot 0
    virtual void Release();                // slot 1
};
struct IntrusivePtr {
    IRefCounted_s00d5_9b00* mpPtr;
    IntrusivePtr() : mpPtr(0) {}
    IntrusivePtr(IRefCounted_s00d5_9b00* p) : mpPtr(p) { if (mpPtr) mpPtr->AddRef(); }
    IntrusivePtr(const IntrusivePtr& o) : mpPtr(o.mpPtr) { if (mpPtr) mpPtr->AddRef(); }
    ~IntrusivePtr() { if (mpPtr) mpPtr->Release(); }
    IntrusivePtr& operator=(const IntrusivePtr& o)
    {
        if (mpPtr != o.mpPtr)
        {
            if (o.mpPtr) o.mpPtr->AddRef();
            IRefCounted_s00d5_9b00* old = mpPtr;
            mpPtr = o.mpPtr;
            if (old) old->Release();
        }
        return *this;
    }
};
void* __stdcall FUN_00d58510(QuatPair* pOut, void* pA, void* pB);      // 0x00d58510  (ret 0xc)
Vec3* __cdecl FUN_0059aed0(Vec3* out, const float* q, const Vec3* v);  // 0x0059aed0  rotate vector by quat
QuatPair __cdecl FUN_005b2500(const QuatPair* a, const QuatPair* b, float t); // 0x005b2500 Slerp
bool  __cdecl FUN_00b3d550(const QuatPair* q);                         // 0x00b3d550
void  __cdecl FUN_00b2af00(void* pA, void* pB);                        // 0x00b2af00
void  __cdecl FUN_00d597b0(int* first, int* last, Vec3 origin);        // 0x00d597b0 make_heap
void  __cdecl FUN_00d592e0(int* first, void* comp, int len, int hole, IntrusivePtr value, Vec3 origin); // 0x00d592e0 adjust_heap
void  __cdecl FUN_00d59820(int* first, int* last, Vec3 origin);        // 0x00d59820 sort_heap
void  __cdecl FUN_00edba80(void* first, void* last, void* dst);        // 0x00edba80 copy_backward (ret 0xc)
void* __cdecl FUN_00d577b0(void* first, void* last, void* dst);        // 0x00d577b0 16-byte copy loop
void* __cdecl FUN_004554f0(void* first, void* last, void* dst);        // 0x004554f0 8-byte copy loop
struct Elem8;
struct Elem16_s00d5_9b00;
struct VecHeader {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* mpPad0c;      // +0x0c (unused by these routines)
    void* mpInline;     // +0x10 (inline buffer start; mpBegin == this means inline storage)
    void* __thiscall Insert8(Elem8* pos, const Elem8* pValue);      // 0x00d59f00
    void* __thiscall Insert16(Elem16_s00d5_9b00* pos, const Elem16_s00d5_9b00* pValue);   // 0x00d5a140
    void* __thiscall Assign12(void** src);                          // 0x00d5a010
    void* __thiscall Grow12(uint32 n, const char* first, const char* last); // 0x00d59410 (this = vector)
};
struct Elem8 {
    uint32 a;      // +0x00
    uint32 b;      // +0x04
};
struct Elem16_s00d5_9b00 {
    uint32 a;      // +0x00
    float  b;      // +0x04
    float  c;      // +0x08
    float  d;      // +0x0c
};
struct OriginCompare {
    Vec3 mPosition;        // +0x00 (ECX points at the origin)
    bool __thiscall Compare(void* pA, void* pB);   // 0x00ac0730 (ret 8)
};
static inline void* PosOf(const int* pSlot)
{
    return *pSlot ? (void*)(*pSlot + 0xc0) : 0;
}
// ---- items of slice s00d59b00 end

// ---- items of slice s00d5b0c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_14853e0;                   // 0x014853e0  decal scale
template <class R> static inline R VC0_s00d5_b0c0(void* o, int slot) {
    typedef R(__thiscall * Fn)(void*);
    return ((Fn)(*(void***)o)[slot])(o);
}
template <class R, class A> static inline R VC1_s00d5_b0c0(void* o, int slot, A a) {
    typedef R(__thiscall * Fn)(void*, A);
    return ((Fn)(*(void***)o)[slot])(o, a);
}
struct Timer_s00d5_b0c0 {
    u64  GetElapsedTime();          // 0x00bc3190
    void Restart();                 // 0x00bc3130
};
struct AudioSystem {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual u32  Create();                           // 0x20
    virtual void v24();
    virtual bool IsPlaying(u32 h);                   // 0x28
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void Begin(u32 id);                      // 0x38
    virtual void v3c();
    virtual void SetParam(u32 id, u32 value);        // 0x40
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual void Commit();                           // 0x58
};
AudioSystem* GetSystemAT();                          // 0x00a206f0
struct NounMgr { int GetPlayerEmpireOrMinus1(); };   // 0x00b1f9d0
NounMgr* __cdecl NounManager();                      // 0x00b3d300
struct CivStrategy { bool FUN_00cf7a90(); };         // 0x00cf7a90
CivStrategy* __cdecl CivModeStrategyGet();           // 0x00cf74c0
struct CityEntryList;
struct City_s00d5_b0c0 {
    bool  FUN_00bd7df0();                            // 0x00bd7df0
    float FUN_00bd7d00();                            // 0x00bd7d00
    bool  FUN_00c004c0(int);                         // 0x00c004c0
    bool  FUN_00bd8f30();                            // 0x00bd8f30
    void* FUN_00bd8d60(int i);                       // 0x00bd8d60
    void  FUN_00bd9480(Vec3* out);                   // 0x00bd9480
    void  FUN_00c00510(int);                         // 0x00c00510
    struct Vec* GetMembers();                        // 0x00c8e810
    CityEntryList* FUN_00bd7f40();                   // 0x00bd7f40  patrol entry list
    int   GetVehicleSpecialty();                     // 0x00bd81d0
};
struct Vec { int begin, end; };
struct Creature_s00d5_b0c0 {
    void StartIndependentSound(u32 snd, void* pos, void* handles);   // 0x00c1db40
};
struct SimGlobal_s00d5_b0c0 {
    char pad[0x2c];
    int mode;                                        // +0x2c
};
u32 SP_GetCurrentGameMode_s00d5_b0c0();                         // 0x00b5b800
SimGlobal_s00d5_b0c0* FUN_00b3d4d0_s00d5_b0c0();                           // 0x00b3d4d0
void __cdecl FUN_00572020(u32 handle, int);          // 0x00572020
void __cdecl Start3dSoundByName(u32 snd, u32 handle, float x, float y, float z);   // 0x00571f80
void __cdecl KillSetiEffects(u32 a, u32 handle);     // 0x00435ed0
extern u32 g_tab147ba00[];                           // 0x0147ba00
extern u32 g_tab147b9f4[];                           // 0x0147b9f4
extern u32 g_tab01583e6c[];                          // 0x01583e6c
static inline void StopSounds(Vec* hv)
{
    int i = 0;
    if (((hv->end - hv->begin) & ~3) > 0) {
        do {
            u32 hh = ((u32*)hv->begin)[i];
            AudioSystem* at = GetSystemAT();
            if (at) {
                at->Begin(0x347536b);
                at->SetParam(0x3475385, hh);
                at->SetParam(0x34753a0, 0);
                at->Commit();
            }
            i++;
        } while (i < (hv->end - hv->begin) >> 2);
    }
    u32* last = (u32*)hv->end;
    u32* first = (u32*)hv->begin;
    memcpy(first, last, (char*)last - (char*)last);
    hv->end += -((((int)last - (int)first) >> 2)) * 4;
}
struct Viz_s00d5_b0c0 {
    void UpdateBackgroundNoise();                    // 0x00d5b0c0
    int  FUN_00d5b6c0();                             // 0x00d5b6c0
    void FUN_00d5b8d0();                             // 0x00d5b8d0
    void FUN_00d5b9f0();                             // 0x00d5b9f0
};
#define CITY F<City_s00d5_b0c0*>(this, 0xaf0)
void __cdecl operator_delete__(void* p);        // 0x00f47380  operator delete
struct CityEntry {                              // 0x18-byte entry in the city list
    char  mFlag00;                              // +0x00  skip when set
    char  mPad01[0x0b];                         // +0x01
    Vec3  mPosition;                            // +0x0c
};
struct CityEntryList {                          // returned by cCity::FUN_00bd7f40
    char        mPad00[0x50];                   // +0x00
    CityEntry*  mpBegin;                        // +0x50
    CityEntry*  mpEnd;                          // +0x54
};
struct Vec3Vector {                             // eastl vector<Vector3> with the sp allocator
    Vec3* mpBegin;                              // +0x00
    Vec3* mpEnd;                                // +0x04
    Vec3* mpCap;                                // +0x08
    Vec3Vector() : mpBegin(0), mpEnd(0), mpCap(0) {}
    void DoInsertValue(Vec3* pos, const Vec3& value);       // 0x004b5ad0
    void push_back(const Vec3& value)
    {
        if (mpEnd < mpCap) {
            *mpEnd = value;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    ~Vec3Vector()
    {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator_delete__((void*)mpBegin);
    }
};
struct cActionCircle_s00d5_b0c0 {
    void SetAtCenter(void* which, Vec3* center, float radius, void* info);   // 0x00af9cf0
    void EmitCopy(void* points, float scale);                                // 0x00afec00
};
struct RefObj_s00d5_b0c0 {                                  // reference-counted object
    virtual void Slot00();
    virtual void Release();                      // +0x04
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2c();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3c();
    virtual void Slot40();
    virtual void Slot44();
    virtual void StopAll(void* unused);          // +0x48
};
void FUN_00c0d3a0(void* o);                      // 0x00c0d3a0
void FUN_00bcb3d0(void* h);                      // 0x00bcb3d0
void FUN_00accf80(void* o);                      // 0x00accf80
void FUN_00c227c0(void* o);                      // 0x00c227c0
void* FUN_00b3d480(void* o);                     // 0x00b3d480
struct ObjVector {                               // eastl vector of AutoRefCount pointers
    RefObj_s00d5_b0c0** mpBegin;                            // +0x00
    RefObj_s00d5_b0c0** mpEnd;                              // +0x04
    RefObj_s00d5_b0c0** mpCap;                              // +0x08
};
struct CultureSlot {                             // 0x198-byte staged scene slot
    unsigned      mFlag00;                       // +0x00  cleared when emptied
    unsigned char mPad04[0xa78];                 // +0x04
};
RefObj_s00d5_b0c0** CopyObjectRange(RefObj_s00d5_b0c0** dst, RefObj_s00d5_b0c0** first, RefObj_s00d5_b0c0** last);   // 0x006782c0
struct TimeOfDay { int FUN_00bc2b80(); };        // 0x00bc2b80
TimeOfDay* FUN_00bc30b0(int unused);             // 0x00bc30b0
void* __stdcall FUN_00bd9480(City_s00d5_b0c0* c, Vec3* out);// 0x00bd9480
struct FixedIntVec16 {                           // eastl::fixed_vector<int,16>
    int  mBuffer[16];                            // +0x00
    int* mpEnd;                                  // +0x40
    void push_back(const int* value) { *mpEnd++ = *value; }   // 0x00422380
};
struct RandomLCG {                               // EA::RandomLinearCongruential
    u32 RandomUint32Uniform(u32 range);          // 0x00a68fb0
};
extern RandomLCG g_randomGlobal;                 // 0x01601760
struct CityVehicles {
    float         mMinBand;         // +0x78c
    float         mMaxBand;         // +0x790
    int           mSpecialty;       // +0x794
    int           mSize;            // +0x798
    unsigned char mFlags;           // +0x79c
    int           mTier;            // +0x7a0
};
struct SlotRange {
    void* mpBegin;                               // +0x00
    void* mpEnd;                                 // +0x04
    void* mpCap;                                 // +0x08
    void Assign(const SlotRange* src);           // 0x00d5bdb0
};
void* AllocSlotRange(unsigned n, void* first, void* last);              // 0x00d596f0
void* AskCopySlots(void* dst, void* first, void* last);                 // 0x00afa430
void  DestroySlotRange(void* first, void* end);                         // 0x00afa150
void  SlotCopyCtorWrap(void* result, void* srcEnd, void* dstEnd);       // 0x00c266c0
struct Vec3Slots {
    Vec3* mpBegin;                               // +0x00
    Vec3* mpEnd;                                 // +0x04
    Vec3* mpCap;                                 // +0x08
    char  mAlloc[0x10];                          // +0x0c
    void DoInsertValue(unsigned index, const Vec3* value);   // 0x00d5bc30
};
void* DoInsertGrow(unsigned n, const Vec3* value, void* alloc);         // 0x00d596a0
void  AssignTempGuard(Vec3Slots* self, void* result);                   // 0x00d5acc0
void  FillVec3Range(void* first, void* last, const Vec3* value);        // 0x00a177f0
void  CopyVec12(void* dst, unsigned count, const void* src);            // 0x006a4100
void  CopyVec3Range(void* dst, unsigned n, const Vec3* value);          // 0x00cca0e0
void* EraseVec3(Vec3Slots* self, Vec3* first, Vec3* last);              // 0x009e0480
// ---- items of slice s00d5b0c0 end

// ---- items of slice s00d5a260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gDefaultDstX;                                 // 0x0169ec28 (default request position)
extern float gDefaultDstY;                                 // 0x0169ec2c
extern float gDefaultDstZ;                                 // 0x0169ec30
extern const float gMaxApproach;                           // 0x01583e68
extern const float kTrailMoveThreshold;                    // 0x014853e0
extern const float kTrailNormalizeEpsilon;                 // 0x013ec4b8
#pragma intrinsic(sqrt)
void __cdecl operator delete[](void* p);                   // 0x00f47380
struct Waypoint { float f[15]; };                          // 0x3c bytes
struct LocRequest {
    Waypoint* mpBegin;                                     // +0x00 waypoint vector
    Waypoint* mpEnd;                                       // +0x04
    char      pad08[0x14 - 0x08];
    Vec3      mDst;                                        // +0x14 (start of the current 0x3c-byte waypoint)
    float     mGoalStopDistance;                           // +0x20
    char      pad24[0x50 - 0x24];
    Vec3      mField50;                                    // +0x50 (reference direction)
    int       mType;                                       // +0x5c (0 none, 1/3 follow, 2 hold)
    float     mAcceptableStopDistance;                     // +0x60
    float     mField64;                                    // +0x64 (alignment threshold)
    float     mPrevDistance;                               // +0x68
    float     mElapsed;                                    // +0x6c
    int       mField70;                                    // +0x70

    LocRequest(const LocRequest& o);                       // 0x00b46d90 (copy ctor, thiscall ret 4)
    LocRequest() {}
    ~LocRequest()                                          // heap block freed through the array cookie check
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    void EraseWaypoint(const Waypoint* pos);               // 0x00b47520 (vector::erase, thiscall ret 4)
};
struct cLocoObj {
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
    virtual const Vec3* GetPosition();                     // 0x2c
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual const Vec3* GetDirection(Vec3* out);           // 0x5c
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
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
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void v2e();
virtual void v2f();
    virtual void v30();
    virtual void SetDesiredSpeed(float speed, int flag);   // 0xc4
    virtual float GetDesiredSpeed();                       // 0xc8
    virtual float v33();
    virtual float funcD0h();                               // 0xd0
virtual void v35();
virtual void v36();
    virtual void SetRequest(const LocRequest& r);          // 0xdc

    char pad04[0x1e8 - 4];
    float mTurnRate;                                       // +0x1e8
    Vec3* GetVelocity();                                   // 0x00d20610 (lea eax,[ecx+0x1c8])
    void  GetSteerDirection(Vec3* out);                    // 0x00c44080
    LocRequest* GetRequest();                              // 0x00c41ec0 (lea eax,[ecx+0x1f4])
};
struct cWalkerInfo { char pad[0x698]; unsigned mState; };
struct cCreature {
    char pad0[0x2b0];
    int  mAnimMode;                                        // +0x2b0
    char pad2b4[0xb20 - 0x2b4];
    cWalkerInfo* mpInfo;                                   // +0xb20
    void InterruptAnimation(unsigned id, int a, int b);    // 0x00c12310
};
struct cPlanetModel_s00d5_a260 {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* dir);   // 0x00b815a0
};
cPlanetModel_s00d5_a260* __cdecl PlanetModel();                       // 0x00b3d350
Vec3* __cdecl NormalizedSafe(Vec3* out, const Vec3* in);   // 0x00449c20
struct cSteerCtx {
    Vec3  out;                                             // +0x00 steering velocity written here
    char  pad0c[4];
    float dt;                                              // +0x10
    cLocoObj* obj;                                         // +0x14
};
struct cFollowBehavior {
    char pad0[0x10];
    cCreature* mpCreature;                                 // +0x10
    bool mbRun;                                            // +0x14
    float Approach(cLocoObj* obj, const Vec3* target, float dt, float speed, float turn);  // 0x00d59b00
    void Update(cSteerCtx* ctx);                           // 0x00d5a260
};
void __cdecl operator delete(void* p);                     // 0x00f47380
typedef uint32_t u32_s00d5_a260;
struct RefCounted
{
    virtual void AddRef();                                 // slot 0
    virtual void Release();                                // slot 1
};
struct RefPtr
{
    RefCounted* mpObject;                                  // +0x00

    RefPtr& operator=(const RefPtr& other)
    {
        if (mpObject != other.mpObject)
        {
            if (other.mpObject != 0)
                other.mpObject->AddRef();
            RefCounted* old = mpObject;
            mpObject = other.mpObject;
            if (old != 0)
                old->Release();
        }
        return *this;
    }
};
struct RefPtrVector
{
    RefPtr* mpBegin;                                       // +0x00
    RefPtr* mpEnd;                                         // +0x04
    RefPtr* mpCapacity;                                    // +0x08

    void erase(RefPtr* first, RefPtr* last);               // 0x00e25bd0
};
int __cdecl EraseRefValue(RefPtrVector* vec, const RefPtr* pValue);
struct Vec3AllocVector
{
    Vec3* mpBegin;                                         // +0x00
    Vec3* mpEnd;                                           // +0x04
    Vec3* mpCapacity;                                      // +0x08
    uint32_t mAllocTag;                                    // +0x0c
    Vec3* mpInlineBuffer;                                  // +0x10
    uint32_t mAllocField14;                                // +0x14

    void CopyConstruct(const Vec3AllocVector& src);        // 0x00d59750
    Vec3AllocVector& operator=(const Vec3AllocVector& src);// 0x00d5a010
    void swap(Vec3AllocVector& other);                     // 0x00d5acc0
};
struct Vec4
{
    uint32_t mKey;                                         // +0x00
    float y, z, w;                                         // +0x04
};
struct Vec4Vector
{
    Vec4* mpBegin;                                         // +0x00
    Vec4* mpEnd;                                           // +0x04
    Vec4* mpCapacity;                                      // +0x08

    void InsertGrow(Vec4* pos, const Vec4* value);         // 0x00d5a140
    Vec4* insert(Vec4* pos, const Vec4& value);            // 0x00d5ad40
};
struct AudioSystem_s00d5_a260
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual u32_s00d5_a260  Create();                                 // 0x20
    virtual void v24();
    virtual bool IsPlaying(u32_s00d5_a260 h);                         // 0x28
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void Begin(u32_s00d5_a260 id);                            // 0x38
    virtual void v3c();
    virtual void SetParam(u32_s00d5_a260 id, u32_s00d5_a260 value);              // 0x40
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual void Commit();                                 // 0x58
};
AudioSystem_s00d5_a260* GetSystemAT_s00d5_a260();                                // 0x00a206f0
struct SoundHandleList
{
    int mBegin;                                            // +0x00
    int mEnd;                                              // +0x04
};
namespace SP
{
    void StopAndClearSoundList(SoundHandleList* handles);  // 0x00d5adf0
}
struct TribeVirtualCreature
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
    virtual Vec3* GetPosition();                           // +0x2c
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
    virtual float GetSpeed();                              // +0x70
};
struct TribeCreature
{
    char mPad00[0x34];                                     // +0x00
    TribeVirtualCreature mVirtual;                         // +0x34
};
struct TribeMemberList
{
    TribeCreature** mpBegin;                               // +0x00
    TribeCreature** mpEnd;                                 // +0x04
    int Size() const { return (int)(mpEnd - mpBegin); }
    TribeCreature* operator[](int i) const { return mpBegin[i]; }
};
struct TribeObject
{
    TribeMemberList* GetMembers();                         // 0x00c8e810
};
struct Vec3TrailVector
{
    Vec3* mpBegin;                                         // +0x00
    Vec3* mpEnd;                                           // +0x04
    Vec3* mpCapacity;                                      // +0x08
    uint32_t mAllocTag;                                    // +0x0c
    Vec3* mpInlineBuffer;                                  // +0x10

    void erase(Vec3* first, Vec3* last);                   // 0x0050f740
    void DoInsertValue(Vec3* pos, const Vec3* value);      // 0x004b5ad0
    void push_back(const Vec3& value)
    {
        Vec3* end = mpEnd;
        if (end < mpCapacity)
        {
            mpEnd = end + 1;
            if (end != 0)
            {
                end->x = value.x;
                end->y = value.y;
                end->z = value.z;
            }
        }
        else
        {
            DoInsertValue(end, &value);
        }
    }
};
struct TribeTrailOwner
{
    char mPad00[0x138];                                    // +0x000
    Vec3 mCurrentPosition;                                 // +0x138
    Vec3TrailVector mTrail;                                // +0x144
    Vec3 mPreviousPosition;                                // +0x158
    char mPad164[0xaf0 - 0x164];                           // +0x164
    TribeObject* mpTribe;                                  // +0xaf0

    void UpdateTrail();                                    // 0x00d5ae80
};
// ---- items of slice s00d5a260 end

// ---- items of slice s00d60ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // thunk 0x011e0744
extern char g_Init169ec25;     // 0x0169ec25
extern float g_eps_13ec4b8;   // 0x013ec4b8
extern float g_c1470f1c;      // 0x01470f1c
extern float g_c1471064;      // 0x01471064
extern float g_c147b9a4;      // 0x0147b9a4
template <class R> static inline R VC0_s00d6_0ce0(void* o, int slot) {
    typedef R(__thiscall * Fn)(void*);
    return ((Fn)(*(void***)o)[slot])(o);
}
template <class R, class A> static inline R VC1_s00d6_0ce0(void* o, int slot, A a) {
    typedef R(__thiscall * Fn)(void*, A);
    return ((Fn)(*(void***)o)[slot])(o, a);
}
struct IRef {
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void Destroy(int flag);
};
struct Vec3_s00d6_0ce0 { u32 x, y, z; };
struct Rec18 { u32 d[6]; };
struct Rec20 { u32 d[5]; };
template <class T> struct SpVec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    u32 mAllocator[2];
};
IRef** CopyRefs(IRef** first, IRef** last, IRef** dst);      // 0x006782c0
Rec18* CopyRec18(Rec18* first, Rec18* last, Rec18* dst);     // 0x00afa430
struct Rec18Dtor { void FUN_007455d0(); };                   // 0x007455d0 (thiscall on the element)
struct Timer_s00d6_0ce0 {
    void Restart();                     // 0x00bc3130
};
struct Timer2 { void FUN_00bc3170(); }; // 0x00bc3170
struct SimA { void FUN_00accf80(void* creature); };   // ret 4
SimA* FUN_00b3d480_s00d6_0ce0();                                   // 0x00b3d480 (no args)
struct SimB_s00d6_0ce0 { void FUN_00bc5040(u32 id); };            // ret 4
SimB_s00d6_0ce0* FUN_00b3d4e0_s00d6_0ce0();                                   // 0x00b3d4e0 (no args)
void  FUN_00bc8fa0(const void* p);                      // cdecl, one arg
struct HostB { void FUN_00bcb3d0(); };                  // 0x00bcb3d0
struct Creature_s00d6_0ce0 { void FUN_00c227c0(); };               // 0x00c227c0
void  StopAndClearSoundList(void* list);                // 0x00d5adf0 cdecl
struct AudioSystem_s00d6_0ce0 {
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
    virtual void Begin(u32 id);                      // 0x38
    virtual void v3c();
    virtual void SetParam(u32 id, u32 value);        // 0x40
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual void Commit();                           // 0x58
};
AudioSystem_s00d6_0ce0* GetSystemAT_s00d6_0ce0();                          // 0x00a206f0
struct City_s00d6_0ce0;
struct Viz_s00d6_0ce0;
struct City_s00d6_0ce0 {
    int   GetCreatureCount();       // 0x00bd8120
    float FUN_00bd7d00();           // 0x00bd7d00
    void  FUN_00bd9e80(int i);      // ret 4
    u32   GetMembers();             // 0x00c8e810 (as cTribe)
    u32   FUN_00bd8130();           // 0x00bd8130
    struct Layout* FUN_00bd7f40();  // 0x00bd7f40 (returns this+0x3ec)
    Vec3f* FUN_00bd9480(Vec3f* out);// 0x00bd9480 (ret 4)
    void  FUN_00bd7f70(Vec3f* a, Vec3f* b);  // 0x00bd7f70 (ret 8)
};
struct Circle {
    char pad0[0x3c];
    SpVec<IRef*> mAgents;       // +0x3c
    SpVec<Rec18> mSlots;        // +0x50
};
struct Stage {
    u32 mActive, mReserved, mRequested, mElapsed, m10;
    char mTimer[0x20];          // +0x14
    Circle mGate;               // +0x34
    Circle mGroup[2];           // +0x98
    SpVec<IRef*> mParticipants[2];   // +0x160
    int mDeltaIn[2];
    int mDeltaOut[2];
};
struct VigInfo { u32 id; char pad4; char flag5; char pad6[2]; u32 rest[5]; };
struct Viz_s00d6_0ce0 {
    void FUN_00d57940(void* x);                 // ret 4
    void FUN_00d5b8d0();  // 0x00d5b8d0 (Viz::FUN_00d5b8d0)
    void StopVignetteInstance(VigInfo* v);      // 0x00d57f80
    void FUN_00d5bfa0(int a);                   // 0x00d5bfa0
    void FUN_00d5c8c0();
    void UpdateSlotCircles();                   // 0x00d60ce0
    void LayoutChanged();                       // 0x00d61880
    void SetupVignetteSpots(int a);             // 0x00d57b50
    void UpdateArtifacts();                     // 0x00d5de40
    void FUN_00d5c720();
    void FUN_01011cc0_dummy();
    void SetCity(City_s00d6_0ce0* city);                   // 0x00d60f00
};
struct RefVec : SpVec<IRef*> {
    void erase(IRef** first, IRef** last);      // 0x00e25bd0
};
struct VigVec : SpVec<VigInfo> {
    void FUN_00d595d0(VigInfo* newEnd, VigInfo* oldEnd);   // ret 8
};
struct Vec3Vec : SpVec<Vec3_s00d6_0ce0> {
    void DoInsertN(Vec3_s00d6_0ce0* pos, u32 n, const Vec3_s00d6_0ce0& v);       // 0x00479330 (ret 0xc)
};
struct CountVec : SpVec<u32> {
    void FUN_01011cc0(u32 v);                   // ret 4 (assign/append)
};
VigInfo* CopyVig(VigInfo* first, VigInfo* last, VigInfo* dst);   // 0x00d5bf00 cdecl
extern u32  g_PosX_s00d6_0ce0;   // 0x0169ec28 (invalid position sentinel)
extern u32  g_PosY_s00d6_0ce0;   // 0x0169ec2c
extern u32  g_PosZ_s00d6_0ce0;   // 0x0169ec30
static inline void ClearRefs(SpVec<IRef*>* v)
{
    IRef**& rend = v->mpEnd;
    IRef** b = v->mpBegin;
    IRef** e = rend;
    IRef** it = CopyRefs(e, e, b);
    IRef** end = rend;
    for (; it < end; ++it)
        if (*it)
            (*it)->Release();
    rend -= (e - b);
}
template <class T> static inline void ErasePod(SpVec<T>* v, T* first, T* last)
{
    T* end = v->mpEnd;
    T* d = first;
    for (T* s = last; s != end; ++s, ++d)
        *d = *s;
    for (T* q = d; q < v->mpEnd; ++q)
        ;
    v->mpEnd -= (last - first);
}
static inline void ClearRec18(SpVec<Rec18>* v)
{
    Rec18*& rend = v->mpEnd;
    Rec18* b = v->mpBegin;
    Rec18* e = rend;
    Rec18* it = CopyRec18(e, e, b);
    Rec18* end = rend;
    for (; it < end; ++it)
        ((Rec18Dtor*)it)->FUN_007455d0();
    rend -= (e - b);
}
static inline void DestroyRefMember(void* viz, int off)
{
    IRef* p = F<IRef*>(viz, off);
    if (p) {
        p->Destroy(1);
        p = F<IRef*>(viz, off);
        if (p) {
            F<IRef*>(viz, off) = 0;
            p->Release();
        }
    }
}
static inline void ReleaseAudioHandle(void* viz, int off)
{
    u32 h = F<u32>(viz, off);
    if (h != 0) {
        AudioSystem_s00d6_0ce0* at = GetSystemAT_s00d6_0ce0();
        if (at) {
            at->Begin(0x347536b);
            at->SetParam(0x3475385, h);
            at->SetParam(0x34753a0, 0);
            at->Commit();
        }
        F<u32>(viz, off) = 0;
    }
}
struct ACircle {
    u32 d[0x19];
    void ctor();                                                 // 0x00afba10
    void dtor();                                                 // 0x00afbad0
    void FUN_00afd6d0(float a, float b, int c);                  // 0x00afd6d0
    void SetAtCenter(const Vec3f* center, float radius,
                     const Vec3f* facing, float altitude);       // 0x00af9cf0 (ret 0x10)
};
struct CircleVec {
    ACircle* mpBegin;
    ACircle* mpEnd;
    ACircle* mpCapacity;
    u32 mAlloc[2];
    ACircle* erase(ACircle* first, ACircle* last);               // 0x00d5edc0 (ret 8)
    void FUN_00d5ee20(ACircle* pos, ACircle* val);               // 0x00d5ee20 (ret 8)
};
struct SlotElem {
    void* GetOccupant();                                         // 0x00fcc210
};
struct Layout {
    u32 pad0[4];
    float mField10;          // +0x10
    u32 pad14[0xf];
    void* mpSlotBegin;       // +0x50
    void* mpSlotEnd;         // +0x54
    void* SlotAt(u32 i);                                         // 0x00af9ff0 (ret 4)
};
struct PtrVec_s00d6_0ce0 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    u32 mAlloc[2];
    void Assign(void* other);                                    // 0x01011cc0 (ret 4)
};
void FUN_00d5b9f0();          // 0x00d5b9f0
// ---- items of slice s00d60ce0 end

// @ 0x00ad11f0
__declspec(noinline) void* cCityVisualizer_s00ad_0510::UpdateVignettes(void* tag)
{
    RegList_s00ad_0510* list = registry.get((int*)&tag);
    int count = (int)(list->vec.end - list->vec.begin);
    for (int i = 0; i < count; ++i) {
        if (list->vec.begin[i].flag4 == 0) {
            ((CityOps*)this)->FUN_00ac8a80(list, i);
            return list->vec.begin[i].ptr8;
        }
    }
    if (tag == (void*)0x18eb45e) {
        ((CityOps*)this)->FUN_00ad1000((void*)0x18eb45e, count * 2);
        ((CityOps*)this)->FUN_00ac8a80(list, count);
        return list->vec.begin[count].ptr8;
    }
    return 0;
}

// @ 0x00ad20e0
void* cMain::findEntry(int a, int b)
{
    void* ctx[2];
    ctx[0] = (void*)0x18eb45e;
    ctx[1] = this;
    RegList* list = ((Sub88*)((char*)this + 0x88))->get(ctx);
    int count = (int)(list->end - list->begin);
    int idx = -1;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            RegElem* e = &list->begin[i];
            if (e->flag4 != 0)
                continue;
            void* p = e->p8;
            if (p == 0)
                continue;
            if (((VTag*)p)->v8() != (void*)0x18eb45e)
                continue;
            idx = i;
            if (*(int*)((char*)p + 0xb20) != a)
                continue;
            if (((ElemObj*)p)->get() == b)
                break;
        }
        if (idx != -1) {
            removeE(list, idx);
            return list->begin[idx].p8;
        }
    }
    int mode = (int)GetCurrentGameMode();
    if ((uint)(mode + 0xfe9ab3ff) > 1u)
        return 0;
    setup((void*)0x18eb45e, count * 2);
    removeE(list, count);
    return list->begin[count].p8;
}

// @ 0x00ad2200
void __fastcall FUN_00ad2200(cMain* self)
{
    if (self->f_100 != 0)
        return;
    if (GetCurrentGameMode() != (void*)0x1654c01) {
        int flags = g_167a4b8;
        if ((flags & 1) == 0) {
            g_167a4b8 = flags | 1;
            g_167a4b4 = g_1565d08 * 20;
        }
        if ((flags & 2) == 0) {
            g_167a4b8 = flags | 2;
            int v = ((CDPL*)g_15fd918_s00ad_20e0)->GetIntProperty((void*)0x625bf68);
            g_167a4b0 = v + 0x8c;
        }
        int cap = g_167a4b4;
        int other = g_167a4b0;
        if (other < cap) other = cap;
        self->setup((void*)0x18eb4b7, other);
    }
    self->setup((void*)0x18eb45e, g_1565d00);
    self->f_100 = 1;
    int m1 = (int)GetCurrentGameMode();
    void* m2 = GetCurrentGameModeAlt();
    int c = (m1 == 0x1654c01 || m1 == 0x1654c02) ? 1 : 0;
    self->f_101 = (char)c;
    if (c == 0) {
        int c2 = ((int)m2 == 0x1654c01 || (int)m2 == 0x1654c02) ? 1 : 0;
        self->f_101 = (char)c2;
    }
    g_167a37c = 0;
    g_167a380 = 0;
    g_167a384 = 0;
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

// @ 0x00ad23c0
void cMain::f_23c0(void* tag, int a, int b)
{
    void* app = App();
    void* x = VTC(app, 0x50, TC_p0)(app);
    void* viewer = VTC(x, 0x1c, TC_p0)(x);
    Vec3 cam;
    ((cViewer2*)viewer)->GetCameraLocationInfo(&cam, 0, 0, 0);

    float f1 = kf_1565d5c;
    float f2 = kf_1565d60;
    Element14 tmp;
    tmp.x = cam.x; tmp.y = cam.y; tmp.z = cam.z;
    tmp.s1 = f1 * f1; tmp.s2 = f2 * f2;

    if (vecEnd < vecCap) {
        vecEnd = (Element14*)((char*)vecEnd + 0x14);
    } else {
        ((Vec14*)((char*)this + 0x20))->insert(vecEnd, &tmp);
    }
    Element14* e = (Element14*)((char*)vecEnd - 0x14);
    e->x = cam.x; e->y = cam.y; e->z = cam.z;
    e->s1 = f1 * f1; e->s2 = f2 * f2;

    if (tag == (void*)0x1654c01) {
        f_e5a0(a, b);
    } else if (tag == (void*)0x1654c02) {
        f_e4e0((void*)b);
        f_12a0();
        f_e5a0(a, b);
    } else if (tag == (void*)0x1654c04) {
        f_e4e0((void*)b);
        if (p_bc)
            ((VMsg*)p_bc)->v9((void*)b, 0);
        f_12a0();
        f_f4c0(a, b);
    } else {
        if (GetUniverseContext() == 0) {
            f_e4e0((void*)b);
            if (p_bc)
                ((VMsg*)p_bc)->v9((void*)b, 0);
            f_12a0();
            f_f4c0(a, b);
        }
    }

    Element14* sb = vecBegin;
    Element14* se = vecEnd;
    FUN_00951bf0(se, se, sb);
    int count = (int)((char*)se - (char*)sb) / 20;
    vecEnd = (Element14*)((char*)vecEnd - count * 20);
}

// @ 0x00ad2560
void cMain::f_2560(int arg)
{
    if (arg == f_a0)
        return;
    if (f_a0 != -1)
        f_0bd0();
    void* ms = MessageServer();
    if (ms != 0) {
        ((VMsg*)ms)->v9((char*)this + 0x1c, (void*)0x1a0219e);
        ((VMsg*)ms)->v9((char*)this + 0x1c, (void*)0x6130eb9);
    }
    void* t = FUN_00b3d320();
    void* v = ((B1de80*)t)->fn2();
    f_98e0(v);
    f_8130();
    FUN_00ad2200(this);
    f_a0 = arg;
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

// @ 0x00af9f60
int SP::cActionCircle_s00af_9aa0::CountFreeSlots()
{
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (!mSlots.mpBegin[i].mOccupied) count++;
  }
  return count;
}

// @ 0x00af9fa0
int SP::cActionCircle_s00af_9aa0::CountOccupiedSlots()
{
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  int c = 0;
  tSlot* p = mSlots.mpBegin;
  for (int i = 0; i < n; i++) {
    if (!p->mOccupied) c++;
    p++;
  }
  return (int)(mSlots.mpEnd - mSlots.mpBegin) - c;
}

// @ 0x00bec1c0
Vector3_s00be_b6d0 cCityWalls::GetInnerGatePosition(int idx)
{
    Vector3_s00be_b6d0* slot = (Vector3_s00be_b6d0*)field_198.mpBegin + idx;
    Vector3_s00be_b6d0* c = CitySub()->v2c();
    float dx = slot->x - c->x;
    float dy = slot->y - c->y;
    float dz = slot->z - c->z;
    float inv = 1.0f / (float)sqrt((double)(dx * dx + (dz * dz + dy * dy)));
    float s = mInnerRadius;
    Vector3_s00be_b6d0* c2 = CitySub()->v2c();
    Vector3_s00be_b6d0 out;
    out.x = c2->x + dx * inv * s;
    out.y = c2->y + dy * inv * s;
    out.z = c2->z + dz * inv * s;
    return out;
}

// @ 0x00bec2d0
Vector3_s00be_b6d0 cCityWalls::GetGatePosition(int idx)
{
    Vector3_s00be_b6d0* slot = (Vector3_s00be_b6d0*)field_198.mpBegin + idx;
    Vector3_s00be_b6d0* c = CitySub()->v2c();
    Vector3_s00be_b6d0 out;
    if (slot->x == c->x && slot->y == c->y && slot->z == c->z) {
        Vector3_s00be_b6d0* c2 = CitySub()->v2c();
        out.x = c2->x;
        out.y = c2->y;
        out.z = c2->z;
        return out;
    }
    Vector3_s00be_b6d0* c3 = CitySub()->v2c();
    float dx = slot->x - c3->x;
    float dy = slot->y - c3->y;
    float dz = slot->z - c3->z;
    float inv = 1.0f / (float)sqrt((double)(dx * dx + (dz * dz + dy * dy)));
    float s = mOuterRadius;
    out.x = c3->x + dx * inv * s;
    out.y = c3->y + dy * inv * s;
    out.z = c3->z + dz * inv * s;
    return out;
}

// @ 0x00d577b0
void __cdecl CopyElems16(const Elem16* pFirst, const Elem16* pLast, Elem16* pDest)
{
    for (; pFirst != pLast; ++pFirst, ++pDest) {
        if (pDest != 0) {
            pDest->mnId = pFirst->mnId;
            pDest->mf0 = pFirst->mf0;
            pDest->mf1 = pFirst->mf1;
            pDest->mf2 = pFirst->mf2;
        }
    }
}

// @ 0x00d57800
void __cdecl PlaceCitizen(CCitizen* pCitizen, CTribe* pTribe, int nUnusedA, int nState, int nEntry, int nExtra, float fBase, float fRange, float fScale)
{
    (void)nUnusedA;
    pCitizen->InitFrom(pTribe->mpCity, 0, 1, nExtra);
    pCitizen->mFlags |= 0x80;
    GetAnimShortcut()->SetTarget(pCitizen, 1);
    pCitizen->mbFieldFBC = true;
    double fRand = g_random.RandomDouble();
    float fAngle = (float)((fBase + fRand * fRange - fRange * 0.5) * fScale);
    pCitizen->mVisual.SetAngle(fAngle);
    pCitizen->SetState(nState);
    pCitizen->mnState = nState;
    if (!pCitizen->mVisual.IsReady())
        pCitizen->mpAnim->mpModel->mFlags |= 0x800;
    pCitizen->UpdateEntry(nEntry);
    SP::GetBehaviorManager()->Attach(&pCitizen->mBehavior);
    pCitizen->mpTribe = pTribe;
    UpdateTimeScaled(pCitizen);
    pCitizen->mpGrid->ResetQueue(&g_cityQueue);
    pCitizen->mpGrid->mnField5fc = 0;
    if (pCitizen->mpAnim != 0) {
        pCitizen->mpAnim->mbField64 = false;
        pCitizen->mpAnim->Detach(1);
    }
    pTribe->GetEntry(nEntry)->mnCount++;
    pCitizen->mbFieldF90 = false;
}

// @ 0x00d57940
void __stdcall DeactivateCitizen(CCitizen* pCitizen)
{
    pCitizen->SetState(-1);
    if (pCitizen->mpAnim != 0) {
        CModel* pModel = pCitizen->mpAnim->mpModel;
        if (pModel != 0)
            pModel->mFlags &= ~0x800;
    }
    UpdateTimeScaled(pCitizen);
    pCitizen->mpGrid->ResetQueue();
    SP::GetVisualizer()->SetupCultureStages(pCitizen);
    pCitizen->ClearEntry();
}

// @ 0x00d579a0
CRecord12* CCitizenManager::FindSlot(CCitizen* pCitizen)
{
    int nCount = (int)(mpCitizensEnd - mpCitizens);
    int i = 0;
    if (nCount > 0) {
        CCitizen** pCitizen2 = *(CCitizen** volatile*)&mpCitizens;
        do {
            if (*pCitizen2 == pCitizen)
                return &mpRecords[i];
            ++i;
            ++pCitizen2;
        } while (i < nCount);
    }
    return (CRecord12*)pCitizen->mVisual.Resolve();
}

// @ 0x00d57a00
int SP::cCityVisualizer_s00d5_6c30::ComputeVisualizedPopulation()
{
    float fRatio = g_pAppProperties->GetFloatProperty(0x5cad54a);
    int nCount = (int)((float)mpCity->GetCreatureCount() * fRatio);
    return MaxValue(nCount, 15);
}

// @ 0x00d57a60
void CCitizenManager::ApplyToAll(CCitizen* pTemplate, CCitizenInfo* pInfo)
{    int nState = pTemplate->GetState();
    CInfoSub* pSub = &pInfo->mSub;
    bool bHide = pInfo->mbFlag89;
    int nCount = (int)(mpCitizensEnd - mpCitizens);
    for (int i = 0; i < nCount; ++i) {
        CCitizen* pCitizen = mpCitizens[i];
        pCitizen->SetState(nState);
        pCitizen->mnState = nState;
        if (!bHide) {
            pCitizen->SetInfo(pSub);
            pCitizen->SetFlag(1);
            pCitizen->mpAnim->mpModel->mFlags |= 0x800;
        } else {
            pCitizen->SetInfo(&g_defaultInfo);
            pCitizen->SetFlag(0);
            pCitizen->mpAnim->mpModel->mFlags &= ~0x800;
        }
    }}

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

// @ 0x00d57ef0
void __fastcall FUN_00d57ef0(void* self, void* /*edx*/, void* arg)
{
  char* p = (char*)self;
  int e = *(int*)(p + 0xaf0);
  if (*(char*)(e + 0x648) == 0 || *(char*)(e + 0x2a0) != 0) {
    *(u32*)(p + 0x9f4) = 0;
    return;
  }
  *(u8*)(e + 0x648) = 0;
  struct Pair_d57ef0 { int a; int b; };
  Pair_d57ef0 v = *(Pair_d57ef0*)(*(int*)(p + 0xaf0) + 0x640);
  switch (v.a) {
    case 0: {
      u32 r = g_randomGlobal.RandomUint32Uniform(3);
      *(u32*)(p + 0x9f4) = r + 1;
      return;
    }
    case 1: {
      u32 r = g_randomGlobal.RandomUint32Uniform(2);
      *(u32*)(p + 0x9f4) = r + 3;
      return;
    }
    default:
      return;
  }
}

// @ 0x00d57f80
void __fastcall FUN_00d57f80(void* self, void* /*edx*/, void* arg)
{
  char* p = (char*)self;
  char* lst = (char*)arg;
  int n = (*(int*)(lst + 0xc) - *(int*)(lst + 8)) >> 2;
  for (int i = 0; i < n; ++i) {
    void** slot = (void**)(*(int*)(lst + 8) + i * 4);
    void* o = *slot;
    if (o == 0 ||
        (*(void* (__thiscall**)(void*, u32))(*(void***)o + 0xc / 4))(o, 0x4f176642) == 0) {
      void* o2 = *(void**)(*(int*)(lst + 8) + i * 4);
      if (o2 != 0) {
        void* c = (*(void* (__thiscall**)(void*, u32))(*(void***)o2 + 0xc / 4))(o2, 0xd0036e08);
        if (c != 0) {
          ((void(__thiscall*)(void*, u32, s32, u32))0x00c12310)(c, 0x2481db0, -1, 0);
          void** vc = (void**)(p + 0xaf0);
          void* pi = *vc;
          if (pi != 0 &&
              (*(u8(__thiscall**)(void*))(*(void***)pi + 0x2c / 4))(pi) == 0) {
            void* hall = (void*)((void*(__thiscall*)(void*))0x00bd9b40)(pi);
            float f = 2.0f;
            float g = 1.0f;
            void* pt = (*(void* (__thiscall**)(void*, float, float))(*(void***)hall + 0x8c / 4))(hall, g, f);
            ((void(__thiscall*)(void*, int, void*, float, float))0x00c1c1d0)(c, 2, pt, g, f);
          }
        }
      }
    } else {
      FUN_00bc97f0(0x800, 0, 3.402823466e38f, 0);
    }
  }
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

// @ 0x00d581b0
void __fastcall FUN_00d581b0(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  if (*(void**)(p + 0xa58) != 0) {
    void* pi = *(void**)(p + 0xa58);
    void* q = (*(void* (__thiscall**)(void*))(*(void***)pi + 0xc / 4))(pi);
    if ((*(u8(__thiscall**)(void*))(*(void***)q + 0x2c / 4))(q) != 0 ||
        FUN_008e7f80(*(void**)(p + 0xa58)) == 2) {
      void* old = *(void**)(p + 0xa58);
      *(u32*)(p + 0xa58) = 0;
      if (old != 0) {
        (*(void(__thiscall**)(void*))(*(void***)old + 0x64 / 4))(old);
      }
    }
  }
  if (*(u32*)(p + 0xa58) == 0) {
    int n = (*(int*)(p + 0xacc) - *(int*)(p + 0xac8)) >> 2;
    int i = 0;
    if (n > 0) {
      do {
        char* o = *(char**)(*(int*)(p + 0xac8) + i * 4);
        if (o != 0 &&
            (*(u8(__thiscall**)(char*))(*(void***)o + 0x2c / 4))(o) == 0 &&
            FUN_008e7f80(o + 0x5a8) != 2 &&
            (*(u32*)(*(int*)(o + 0xb4c) + 0x5fc) & 0x80000) != 0) {
          FUN_00ae6690(o + 0x5a8);
          break;
        }
        ++i;
      } while (i < n);
    }
  }
  if (*(u32*)(p + 0xa58) == 0) {
    int n = (*(int*)(p + 0xae0) - *(int*)(p + 0xadc)) >> 2;
    int i = 0;
    if (n > 0) {
      do {
        char* o = *(char**)(*(int*)(p + 0xadc) + i * 4);
        if (o != 0 &&
            (*(u8(__thiscall**)(char*))(*(void***)o + 0x2c / 4))(o) == 0 &&
            FUN_008e7f80(o + 0x5a8) != 2 &&
            FUN_00c0b780(o) != 0 &&
            FUN_00c0b7a0(o) == 0) {
          void* old = *(void**)(p + 0xa58);
          void* np = o + 0x5a8;
          if (np != old) {
            if (np != 0) {
              (*(void(__thiscall**)(void*))(*(void***)np + 0x60 / 4))(np);
            }
            *(void**)(p + 0xa58) = np;
            if (old != 0) {
              (*(void(__thiscall**)(void*))(*(void***)old + 0x64 / 4))(old);
            }
          }
          break;
        }
        ++i;
      } while (i < n);
    }
  }
  *(u32*)(p + 0xa60) = (*(int*)(p + 0xa58) != 0) ? 0 : 5;
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

// 0x00d58610: not byte-exact; the byte-exact version is the lifted one in match/slices/s00d58610/s00d58610.cpp
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
    PtrVec14* v = &self->mVec170 + 1;
    for (int i = 1; i >= 0; --i) {
        --v;
        void** e = v->mpEnd;
        void** p = v->mpBegin;
        for (; p < e; ++p)
            if (*p)
                ((IObj*)*p)->Slot4();
        if (v->mpBegin && ((uint32_t*)v->mpBegin)[-1] != 0)
            operator_delete_array(v->mpBegin);
    }
    ActionCircle* c = (ActionCircle*)((char*)self + 0x15c);
    for (int i = 1; i >= 0; --i) {
        c = (ActionCircle*)((char*)c - 0x64);
        c->Dtor();
    }
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

// @ 0x00d58c50
void __fastcall FUN_00d58c50(CityVis* self, void* edx, Creature* p)
{
    (void)edx;
    p->mFlags110 |= 0x80;
    void* r = FUN_00b3d310();
    (void)r;
    FUN_00b48770();
    p->mFBC = 1;
    ((IBehaviorManager*)SP_BehaviorManager())->Slot3c(&p->mField58);
    p->mFB8 = (uint32_t)(uintptr_t)self;
    FUN_00c0d3a0();
    FUN_00bcb660();
    *(uint32_t*)((char*)p->mpB4C + 0x5fc) = 0;
    void* prof = FUN_00c0bbd0();
    (void)prof;
    FUN_00c14350();
    (void)0;
}

// @ 0x00d58d50
void __fastcall FUN_00d58d50(CityVis* self, void* edx)
{
    (void)edx;
    CityCircle* circle = (CityCircle*)FUN_00bd7f40();
    int count = (int)(circle->mEnd54 - circle->mBegin50) / 0x18;
    if (count == 0)
        return;
    if (self->mIndexA44 != -1 && self->mIndexA44 < count) {
        void* slot = ((ActionCircle*)circle)->SlotAt((uint32_t)self->mIndexA44);
        void* obj = (void*)FUN_00fcc210();
        (void)slot;
        if (obj) {
            void* gd = (void*)((IObj*)obj)->SlotC();
            (void)gd;
        }
    }
    self->mIndexA44 = -1;
    for (int i = 0; i < 8; ++i) {
        uint32_t r = (uint32_t)(uintptr_t)FUN_00a68fb0();
        void* slot = ((ActionCircle*)circle)->SlotAt(r);
        void* obj = (void*)FUN_00fcc210();
        (void)slot;
        if (obj) {
            void* gd = (void*)((IObj*)obj)->SlotC();
            (void)gd;
        }
        (void)r;
    }
    self->mByteA48 = 0;
    void* members = FUN_00c8e810();
    (void)members;
}

// @ 0x00d58ea0
void __fastcall FUN_00d58ea0(CityVis* self, void* edx)
{
    (void)edx;
    int count = (int)((char*)self->mpVecAE0 - (char*)self->mpVecADC) / 4;
    if (count <= 0)
        return;
    Vector3_s00d5_8a80 hallPos;
    FUN_00bd9480(&hallPos);
    void* hall = FUN_00bd9b40();
    (void)hall;
    int i = 0;
    while (i < count) {
        Creature* e = (Creature*)self->mpVecADC[i];
        if (FUN_00c0b7a0()) {
            Vector3_s00d5_8a80* pos = ((ISpat2*)((char*)e + 0xc0))->Get2c();
            float d = sqrtf((pos->x - hallPos.x) * (pos->x - hallPos.x) +
                            (pos->y - hallPos.y) * (pos->y - hallPos.y) +
                            (pos->z - hallPos.z) * (pos->z - hallPos.z));
            if (d <= gConst853E0) {
                ((ISpat2*)e)->SlotC8(1);
                FUN_00c42140(FUN_00b4c7c0);
                void* cur = self->mpVecADC[i];
                void* last = self->mpVecAE0[-1];
                if (cur != last) {
                    if (cur)
                        ((IObj*)cur)->Slot0();
                    self->mpVecAE0[-1] = cur;
                    if (last)
                        ((IObj*)last)->Slot4();
                }
                self->mpVecAE0 -= 1;
                if (*self->mpVecAE0)
                    ((IObj*)*self->mpVecAE0)->Slot4();
                --count;
                continue;
            }
        }
        ++i;
    }
}

// @ 0x00d590b0
void CityVis::FUN_00d590b0(int param_2, Vector3_s00d5_8a80* param_3, float param_4)
{
    CityVis* self = this;
    void** p = self->mpVecA64;
    void** end = self->mpVecA68;
    for (; p != end; ++p) {
        Creature* e = (Creature*)*p;
        Vector3_s00d5_8a80* pos = ((ISpat2*)((char*)e + 0xc0))->Get2c();
        float dx = pos->x - param_3->x;
        float dy = pos->y - param_3->y;
        float dz = pos->z - param_3->z;
        if (sqrtf(dx * dx + dy * dy + dz * dz) < param_4) {
            void* it = (void*)(uintptr_t)FUN_00bc97f0();
            *(float*)((char*)it + 0x0c) = param_3->x;
            *(float*)((char*)it + 0x10) = param_3->y;
            *(float*)((char*)it + 0x14) = param_3->z;
            *(int*)((char*)it + 0x18) = param_2;
        }
    }
}

// @ 0x00d59170
int __fastcall FUN_00d59170(CityVis* self, void* edx, int id)
{
    (void)edx;
    uint n = (uint)((int)((char*)self->mpVecBC0 - (char*)self->mpVecBBC) / 0x1c);
    if (n != 0) {
        Rec1C* rec = (Rec1C*)self->mpVecBBC;
        uint i = 0;
        do {
            if (rec->m04 == 1 && rec->mp08 != rec->mp0C) {
                int* p = rec->mp08;
                int* e = rec->mp0C;
                while (p != e) {
                    if (*p == id)
                        return id;
                    ++p;
                }
            }
            ++i;
            rec = (Rec1C*)((char*)rec + 0x1c);
        } while (i < n);
    }
    return 0;
}

// @ 0x00d59200
void __fastcall FUN_00d59200(VecP* self, void* edx, int id)
{
    (void)edx;
    int* begin = (int*)self->mpBegin;
    int* end = (int*)self->mpEnd;
    uint n = (uint)(end - begin);
    uint i = 0;
    if (n != 0) {
        while (id != begin[i]) {
            ++i;
            if (n <= i)
                return;
        }
        int last = end[-1];
        int cur = begin[i];
        if (last != cur) {
            if (last)
                ((IObj*)(uintptr_t)last)->Slot0();
            begin[i] = last;
            if (cur)
                ((IObj*)(uintptr_t)cur)->Slot4();
        }
        self->mpEnd = (void**)(end - 1);
        if (*self->mpEnd)
            ((IObj*)*self->mpEnd)->Slot4();
    }
}

// @ 0x00d59280
CVec* __fastcall FUN_00d59280(CVec* self, void* edx, int count, void* src)
{
    (void)edx;
    self->m10 = *(uint32_t*)((char*)src + 4);
    void** p;
    if (count != 0)
        p = (void**)operator_new(count * 0xc, "Simulator", 0, 0, "EASTL/allocator.h", 0xd1);
    else
        p = 0;
    self->mpBegin = p;
    self->mpEnd = p;
    self->mpCap = (void**)((char*)p + count * 0xc);
    return self;
}

// @ 0x00d592e0
void FUN_00d592e0(int* array, int count, int param_3, int start, IObj* obj, int a6, int a7, int a8)
{
    int idx = start;
    int iVar3 = 0;
    int childIndex = 0;
    while (true) {
        iVar3 = idx * 2;
        childIndex = iVar3 + 2;
        if (count <= childIndex)
            break;
        void* cl = array[childIndex - 1]
                       ? (void*)((char*)(uintptr_t)array[childIndex - 1] + 0xc0)
                       : 0;
        void* cr = (void*)((char*)(uintptr_t)array[childIndex] + 0xc0);
        if (FUN_00ac0730_s00d5_8a80(cr, cl) != 0)
            childIndex = iVar3 + 1;
        void* v1 = (void*)(uintptr_t)array[childIndex];
        void* v2 = (void*)(uintptr_t)array[idx];
        if (v1 != v2) {
            if (v1)
                ((IObj*)v1)->Slot0();
            array[idx] = (int)(uintptr_t)v1;
            if (v2)
                ((IObj*)v2)->Slot4();
        }
        idx = childIndex;
    }
    if (childIndex == count) {
        void* v1 = (void*)(uintptr_t)array[childIndex - 1];
        void* v2 = (void*)(uintptr_t)array[idx];
        if (v1 != v2) {
            if (v1)
                ((IObj*)v1)->Slot0();
            array[idx] = (int)(uintptr_t)v1;
            if (v2)
                ((IObj*)v2)->Slot4();
        }
        idx = iVar3 + 1;
    }
    (void)param_3;
    (void)a6;
    (void)a7;
    (void)a8;
    if (obj)
        obj->Slot0();
    FUN_00d587e0();
    if (obj)
        obj->Slot4();
}

// @ 0x00d59520
void __fastcall FUN_00d59520(CityVis* self, void* edx, Vector3_s00d5_8a80* pos)
{
    (void)edx;
    if (self->mpCityAF0) {
        void* ctx = (void*)((char*)self->mpCityAF0 + 0x120);
        Vector3_s00d5_8a80* p = ((ISpat2*)ctx)->Get2c();
        float dx = p->x - pos->x;
        float dy = p->y - pos->y;
        float dz = p->z - pos->z;
        float d = sqrtf(dy * dy + (dx * dx + dz * dz));
        if (d < gConst77FBC)
            self->FUN_00d590b0(0, pos, d);
    }
}

// @ 0x00d59580
void* __fastcall FUN_00d59580(void* self, void* edx)
{
    (void)edx;
    *(void**)self = &gAbandonedVtbl;
    *(uint32_t*)((char*)self + 4) = 0;
    *(uint32_t*)((char*)self + 8) = 0;
    *(uint32_t*)((char*)self + 0x0c) = 0;
    return self;
}

// @ 0x00d595d0
void __stdcall FUN_00d595d0(void* begin, void* end)
{
    Rec1C* r = (Rec1C*)begin;
    Rec1C* last = (Rec1C*)end;
    for (; r < last; ++r) {
        int** p = (int**)r->mp08;
        int** e = (int**)r->mp0C;
        for (; p < e; ++p)
            if (*p)
                ((IObj*)*p)->Slot4();
        void* buf = r->mp08;
        if (buf && ((uint32_t*)buf)[-1] != 0)
            operator_delete_array(buf);
    }
}

// @ 0x00d59630
void* __fastcall FUN_00d59630(void* self, void* edx, void* src)
{
    (void)edx;
    int* s = (int*)src;
    *(uint32_t*)self = (uint32_t)s[0];
    *(uint8_t*)((char*)self + 4) = *(uint8_t*)((char*)src + 4);
    *(uint8_t*)((char*)self + 5) = *(uint8_t*)((char*)src + 5);
    *(uint8_t*)((char*)self + 6) = *(uint8_t*)((char*)src + 6);
    ((Thiscall*)((char*)self + 8))->FUN_00b93c60((s[3] - s[2]) >> 2, (void*)((char*)src + 0x14));
    void* out;
    FUN_00829110(&out, (void*)(uintptr_t)s[2], (void*)(uintptr_t)s[3],
                 *(void**)((char*)self + 8), src);
    *(void**)((char*)self + 0x0c) = out;
    return self;
}

// 0x00d596a0: not byte-exact; the byte-exact version is the lifted one in match/slices/s00d596a0/s00d596a0.cpp
void* __fastcall FUN_00d596a0(CVec* self, void* edx, int count, Vector3_s00d5_8a80* src, void* alloc)
{
    (void)edx;
    FUN_00d59280(self, 0, count, alloc);
    void* p = self->mpBegin;
    for (int i = count; i > 0; --i) {
        if (p) {
            *(Vector3_s00d5_8a80*)p = *src;
        }
        p = (char*)p + 0xc;
    }
    self->mpEnd = (void**)((char*)self->mpBegin + count * 0xc);
    return self;
}

// @ 0x00d59750
CVec* __fastcall FUN_00d59750(CVec* self, void* edx, void* src)
{
    (void)edx;
    int* s = (int*)src;
    int count = (int)((char*)(uintptr_t)s[1] - (char*)(uintptr_t)s[0]) / 0xc;
    FUN_00d59280(self, 0, count, (char*)src + 0xc);
    void* out;
    FUN_00951740(&out, (void*)(uintptr_t)s[0], (void*)(uintptr_t)s[1],
                 (void*)self->mpBegin, src);
    self->mpEnd = (void**)out;
    return self;
}

// @ 0x00d598d0
void* FUN_00d598d0(void* begin, void* end, void* out)
{
    if (begin == end)
        return out;
    Rec1C* r = (Rec1C*)begin;
    Rec1C* last = (Rec1C*)end;
    char* cur = (char*)out;
    for (;;) {
        int** p = (int**)r->mp08;
        int** e = (int**)r->mp0C;
        for (; p < e; ++p)
            if (*p)
                ((IObj*)*p)->Slot4();
        void* buf = r->mp08;
        if (buf && ((uint32_t*)buf)[-1] != 0)
            operator_delete_array(buf);
        ++r;
        cur += 0x1c;
        if (r == last)
            break;
    }
    return cur;
}

// @ 0x00d59940
void* __fastcall FUN_00d59940(void* self, void* edx)
{
    (void)edx;
    ((GonzagoTimer*)((char*)self + 0x10))->Ctor();
    ((ActionCircle*)((char*)self + 0x30))->CtorAC();
    ActionCircle* ac = (ActionCircle*)((char*)self + 0x94);
    int n = 1;
    do {
        ac->CtorAC();
        ac = (ActionCircle*)((char*)ac + 0x64);
    } while (--n >= 0);
    *(uint32_t*)((char*)self + 0x15c) = 0;
    *(uint32_t*)((char*)self + 0x160) = 0;
    *(uint32_t*)((char*)self + 0x164) = 0;
    *(uint32_t*)((char*)self + 0x170) = 0;
    *(uint32_t*)((char*)self + 0x174) = 0;
    *(uint32_t*)((char*)self + 0x178) = 0;
    return self;
}

// @ 0x00d599a0
bool __fastcall FUN_00d599a0(CityVis* self, void* edx, void* param_2)
{
    (void)edx;
    void* city = self->mpCityAF0;
    void* q = ((ISpat2*)city)->Get6c();
    (void)q;
    Vector3_s00d5_8a80* pos = ((ISpat2*)((char*)param_2 + 0xc0))->Get2c();
    Vector3_s00d5_8a80 saved = *pos;
    (void)saved;
    return false;
}

// @ 0x00d59b00
float __stdcall cFollowBehavior_Approach(void* pThis, const void* pTarget, float dt, float speed, float turn)
{
    QuatPair target;
    FUN_00d58510(&target, pThis, (void*)pTarget);

    Vec3 dir;
    ((cSteerObj*)pThis)->GetDirection(&dir);

    Vec3 rotated;
    FUN_0059aed0(&rotated, &g_acos_one, (const Vec3*)&target);

    float dot = dir.x * rotated.x + dir.y * rotated.y + dir.z * rotated.z;
    if (dot > g_HK_REAL_ONE)
        dot = g_HK_REAL_ONE;
    if (dot < g_zero_13eb1bc)
        dot = g_zero_13eb1bc;

    float result = dot * speed;
    float angle = (float)acos((double)dot);
    if (angle < 3.402823466e+38f)
    {
        float t;
        if (angle <= g_HK_REAL_ZERO)
        {
            t = g_HK_REAL_ONE;
        }
        else
        {
            t = (dt * turn) / angle;
            if (t > g_HK_REAL_ONE)
                t = g_HK_REAL_ONE;
        }
        QuatPair q = FUN_005b2500(((cSteerObj*)pThis)->GetOrientation(), &target, t);
        if (FUN_00b3d550(&q))
            ((cSteerObj*)pThis)->SetOrientation(&q);
    }
    return result;
}

// @ 0x00d59d00
int* __cdecl FUN_00d59d00(int* first, int* last, IntrusivePtr pOwner, Vec3 origin)
{
    for (;;)
    {
        while (((OriginCompare*)&origin)->Compare(PosOf(first),
                                                  pOwner.mpPtr ? (void*)((char*)pOwner.mpPtr + 0xc0) : 0))
        {
            ++first;
        }
        for (;;)
        {
            --last;
            void* elemPos = PosOf(last);
            void* ownerPos = pOwner.mpPtr ? (void*)((char*)pOwner.mpPtr + 0xc0) : 0;
            if (!((OriginCompare*)&origin)->Compare(ownerPos, elemPos))
                break;
        }
        if (first >= last)
            break;
        FUN_00b2af00(first, last);
        ++first;
    }
    return first;
}

// @ 0x00d59da0
void __cdecl FUN_00d59da0(int* begin, int* middle, int* last, Vec3 pos)
{
    FUN_00d597b0(begin, middle, pos);
    for (int* p = middle; p < last; ++p)
    {
        if (((OriginCompare*)&pos)->Compare(PosOf(p), PosOf(begin)))
        {
            IntrusivePtr* pp = (IntrusivePtr*)p;
            IntrusivePtr* bp = (IntrusivePtr*)begin;
            IntrusivePtr value(*pp);
            *pp = *bp;
            FUN_00d592e0(begin, 0, (int)(middle - begin), 0, value, pos);
        }
    }
    FUN_00d59820(begin, middle, pos);
}

// @ 0x00d59f00
void* VecHeader::Insert8(Elem8* pos, const Elem8* pValue)
{
    Elem8* const end = (Elem8*)mpEnd;
    if (end != (Elem8*)mpCapacity)
    {
        const Elem8* value = pValue;
        if (value >= pos && value < end)
            value = value + 1;
        if (end)
            *end = end[-1];
        Elem8* q = (Elem8*)mpEnd;
        Elem8* s = q - 1;
        while (s != pos)
        {
            *--q = *--s;
        }
        uint32 a = value->a;
        pos->a = a;
        pos->b = value->b;
        mpEnd = (Elem8*)mpEnd + 1;
        return (void*)(uintptr_t)a;
    }
    else
    {
        uint32 n = (uint32)(int)(end - (Elem8*)mpBegin);
        if (n > 0)
            n = n * 2;
        else
            n = 1;
        Elem8* pNew;
        if (n)
            pNew = (Elem8*)operator_new(n * 8, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);
        else
            pNew = 0;
        Elem8* p = (Elem8*)FUN_004554f0(mpBegin, pos, pNew);
        if (p)
            *p = *pValue;
        p = (Elem8*)FUN_004554f0(pos, mpEnd, p + 1);
        if (mpBegin != 0 && mpBegin != mpInline)
            operator_delete(mpBegin);
        mpBegin = pNew;
        mpEnd = p;
        mpCapacity = (char*)pNew + n * 8;
    }
}

void* __cdecl FUN_00b84c80(const void* first, const void* last, void* dst);      // 0x00b84c80 (ret 0xc)

// eastl vector<12-byte element>::Assign(const vector&).
// @ 0x00d5a010
void* VecHeader::Assign12(void** src)
{
    if (src == (void**)this)
        return this;
    char* srcBegin = (char*)src[0];
    int n = (int)(((char*)src[1] - srcBegin) / 12);
    char* selfBegin = (char*)mpBegin;
    if ((uint32)n > (uint32)(int)(((char*)mpCapacity - selfBegin) / 12))
    {
        void* buf = Grow12((uint32)n, srcBegin, (const char*)src[1]);
        if (selfBegin != 0 && selfBegin != (char*)mpInline)
            operator_delete(selfBegin);
        mpCapacity = (char*)buf + n * 12;
        mpBegin = buf;
        mpEnd = (char*)buf + n * 12;
        return this;
    }
    int have = (int)(((char*)mpEnd - selfBegin) / 12);
    if ((uint32)n > (uint32)have)
    {
        FUN_00b84c80(srcBegin, srcBegin + have * 12, selfBegin);
        char* pout = (char*)src[1];
        char* mid = (char*)mpBegin + (int)(((char*)mpEnd - (char*)mpBegin) / 12) * 12;
        FUN_00951740((void*)&pout, mid, pout, (char*)mpEnd, (char*)src[1]);
        mpEnd = (char*)mpBegin + n * 12;
        return this;
    }
    FUN_00b84c80(srcBegin, src[1], selfBegin);
    mpEnd = (char*)mpBegin + n * 12;
    return this;
}

// @ 0x00d5a140
void* VecHeader::Insert16(Elem16_s00d5_9b00* pos, const Elem16_s00d5_9b00* pValue)
{    Elem16_s00d5_9b00* const end = (Elem16_s00d5_9b00*)mpEnd;
    if (end != (Elem16_s00d5_9b00*)mpCapacity)
    {
        const Elem16_s00d5_9b00* value = pValue;
        if (value >= pos && value < end)
            value = value + 1;
        if (end)
        {
            end->a = end[-1].a;
            _ReadWriteBarrier();
            end->b = end[-1].b;
            end->c = end[-1].c;
            end->d = end[-1].d;
        }
        FUN_00edba80(pos, (Elem16_s00d5_9b00*)mpEnd - 1, (Elem16_s00d5_9b00*)mpEnd);
        *(uint32*)&pos->a = *(const uint32*)&value->a;
        uint32 b = *(const uint32*)&value->b;
        *(uint32*)&pos->b = b;
        *(uint32*)&pos->c = *(const uint32*)&value->c;
        *(uint32*)&pos->d = *(const uint32*)&value->d;
        mpEnd = (Elem16_s00d5_9b00*)mpEnd + 1;
        return (void*)(uintptr_t)b;
    }
    else
    {
        uint32 n = (uint32)(int)(end - (Elem16_s00d5_9b00*)mpBegin);
        if (n > 0)
            n = n * 2;
        else
            n = 1;
        Elem16_s00d5_9b00* pNew;
        if (n)
            pNew = (Elem16_s00d5_9b00*)operator_new(n << 4, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);
        else
            pNew = 0;
        Elem16_s00d5_9b00* oldBegin;
        if ((uintptr_t)pNew & 1) { oldBegin = (Elem16_s00d5_9b00*)mpBegin; goto doCopy1; }
        oldBegin = (Elem16_s00d5_9b00*)mpBegin;
    doCopy1:
        Elem16_s00d5_9b00* p = (Elem16_s00d5_9b00*)FUN_00d577b0(oldBegin, pos, pNew);
        if (p)
        {
            p->a = pValue->a;
            p->b = pValue->b;
            p->c = pValue->c;
            p->d = pValue->d;
        }
        Elem16_s00d5_9b00* oldEnd = (Elem16_s00d5_9b00*)mpEnd;
        p = (Elem16_s00d5_9b00*)FUN_00d577b0(pos, oldEnd, p + 1);
        if (mpBegin != 0 && mpBegin != mpInline)
            operator_delete(mpBegin);
        mpEnd = p;
        mpCapacity = (char*)pNew + (n << 4);
        mpBegin = pNew;
    }}

// @ 0x00d5a260
void cFollowBehavior::Update(cSteerCtx* ctx)
{
    cLocoObj* obj = ctx->obj;
    obj->funcD0h();
    obj->GetVelocity();
    Vec3 dir;
    obj->GetSteerDirection(&dir);
    float dirLen = (float)sqrt(dir.y * dir.y + dir.z * dir.z + dir.x * dir.x);
    if (1.52587890625e-05f <= dirLen) {
        float inv = 1.0f / dirLen;
        dir.x = inv * dir.x;
        dir.y = dir.y * inv;
        dir.z = dir.z * inv;
    } else {
        Vec3 tmp;
        const Vec3* d = obj->GetDirection(&tmp);
        dir.x = d->x * 0.1f;
        dir.y = d->y * 0.1f;
        dir.z = d->z * 0.1f;
    }

    const Vec3* pp = obj->GetPosition();
    Vec3 pos;
    pos.x = pp->x;
    pos.y = pp->y;
    pos.z = pp->z;
    Vec3 fwd;
    obj->GetDirection(&fwd);
    float speed = obj->GetDesiredSpeed();
    float turn = obj->mTurnRate;
    LocRequest* req = obj->GetRequest();
    PlanetModel();

    int type = req->mType;
    float dist;
    if (type == 0) {
        dist = 0.0f;
    } else {
        float dz = pos.z - req->mDst.z, dy = pos.y - req->mDst.y, dx = pos.x - req->mDst.x;
        dist = (float)sqrt(dz * dz + dy * dy + dx * dx);
    }
    bool notHold3 = type != 3;
    bool stop = false;
    if (type == 0) {
        speed = 0.0f;
    } else if (type != 2) {
        float prev = req->mPrevDistance;
        bool progressed = false;
        if (dist >= prev) {
            req->mElapsed = ctx->dt + req->mElapsed;
            progressed = true;
        }
        if (req->mGoalStopDistance > dist) {
            stop = true;
        } else if (ctx->dt * speed < dist) {
            if (progressed && req->mAcceptableStopDistance > dist)
                stop = true;
        } else {
            speed = (dist / ctx->dt) * 0.95f;
        }
        req->mPrevDistance = dist;
        if (stop) {
            if (req->mpBegin == req->mpEnd) {
                speed = 0.0f;
            } else {
                req->mElapsed = 0.0f;
                Waypoint* first = req->mpBegin;
                *(Waypoint*)&req->mDst = *first;
                req->EraseWaypoint(first);
                stop = false;
                float dz = pos.z - req->mDst.z, dy = pos.y - req->mDst.y, dx = pos.x - req->mDst.x;
                dist = (float)sqrt(dz * dz + dy * dy + dx * dx);
            }
        }
    }

    if (req->mType != 0 && dist < (speed / turn) * 2.0f) {
        float dz = req->mDst.z - pos.z, dy = req->mDst.y - pos.y, dx = req->mDst.x - pos.x;
        float inv = 1.0f / (float)sqrt(dz * dz + dy * dy + dx * dx + 1e-08f);
        float dot = fwd.z * (dz * inv) + fwd.y * (dy * inv) + (inv * dx) * fwd.x;
        if (dot < 0.5f) {
            float cap = (dist * turn) * 0.5f;
            const float* p = &cap;
            if (speed <= cap) p = &speed;
            speed = *p;
        }
    }

    Vec3 target;
    target.z = pos.z + dir.z;
    target.x = pos.x + dir.x;
    target.y = pos.y + dir.y;
    float moved = Approach(ctx->obj, &target, ctx->dt, speed, turn);
    if (moved <= 0.0f) {
        mpCreature->mAnimMode = 0;
        ctx->out.x = 0.0f;
        ctx->out.y = 0.0f;
        ctx->out.z = 0.0f;
    } else {
        mpCreature->mAnimMode = 5;
        ctx->out.x = dir.x * speed;
        ctx->out.y = dir.y * speed;
        ctx->out.z = dir.z * speed;
        bool oldRun = mbRun;
        if (!oldRun) {
            if (dist > 6.0f) mbRun = true;
        } else {
            if (3.0f > dist) mbRun = false;
        }
        float dt = ctx->dt;
        Vec3 next;
        next.x = dt * ctx->out.x + pos.x;
        next.y = dt * ctx->out.y + pos.y;
        next.z = dt * ctx->out.z + pos.z;
        Vec3 ground;
        PlanetModel()->DirectionToSurfacePosition(&ground, &next);
        float h = (float)sqrt(next.x * next.x + next.z * next.z + next.y * next.y) -
                  (float)sqrt(ground.x * ground.x + ground.y * ground.y + ground.z * ground.z);
        Vec3 nbuf;
        const Vec3* nd;
        float amount;
        if (!mbRun) {
            if (0.0f <= h) {
                float t = (h / ctx->dt) * -1.0f;
                float lo = -1.0f;
                const float* p = &t;
                if (t <= -1.0f) p = &lo;
                nd = NormalizedSafe(&nbuf, &next);
                amount = *p;
            } else {
                float t = (h / ctx->dt) * -1.0f;
                nd = NormalizedSafe(&nbuf, &next);
                amount = t;
            }
        } else {
            if (0.0f <= h) {
                float t = (6.0f - h) / ctx->dt;
                const float* p = &t;
                if (gMaxApproach <= t) p = &gMaxApproach;
                nd = NormalizedSafe(&nbuf, &next);
                amount = *p;
            } else {
                float t = ((h - 0.1f) / ctx->dt) * -1.0f;
                nd = NormalizedSafe(&nbuf, &next);
                amount = t;
            }
        }
        ctx->out.x = nd->x * amount + ctx->out.x;
        ctx->out.z = nd->z * amount + ctx->out.z;
        ctx->out.y = nd->y * amount + ctx->out.y;
        if (mbRun != oldRun) {
            cCreature* c = mpCreature;
            if (!mbRun)
                c->InterruptAnimation(0x2481db0, -1, 0);
            else if (c->mpInfo->mState <= 0)
                c->InterruptAnimation(0x5261d78, -1, 0);
            else
                c->InterruptAnimation(0x77300fb, -1, 0);
        }
    }

    if (!notHold3) {
        Vec3 q2;
        const Vec3* q = obj->GetDirection(&q2);
        float d = q->z * req->mField50.z + q->y * req->mField50.y + q->x * req->mField50.x;
        notHold3 = true;
        if (!(d > req->mField64))
            notHold3 = false;
    }

    if (stop) {
        if (notHold3) {
            LocRequest goal;
            goal.mpBegin = 0;
            ((int*)&goal)[1] = 0;
            ((int*)&goal)[2] = 0;
            goal.mDst.x = gDefaultDstX;
            goal.mDst.y = gDefaultDstY;
            goal.mDst.z = gDefaultDstZ;
            goal.mGoalStopDistance = 1.0f;
            *(int*)&goal.pad24[0] = 0;
            *(char*)&goal.pad24[0x28] = 0;
            goal.mField50.x = 0.0f;
            goal.mField50.y = 0.0f;
            goal.mField50.z = 0.0f;
            goal.mType = 0;
            goal.mAcceptableStopDistance = 2.0f;
            goal.mField64 = 0.9f;
            goal.mPrevDistance = 3.402823466e+38f;
            goal.mElapsed = 0.0f;
            goal.mField70 = 0;
            ctx->obj->SetRequest(goal);
            ctx->obj->SetDesiredSpeed(0.0f, 1);
            ctx->out.x = 0.0f;
            ctx->out.y = 0.0f;
            ctx->out.z = 0.0f;
        } else {
            LocRequest goal(*ctx->obj->GetRequest());
            goal.mDst.x = pos.x;
            goal.mDst.y = pos.y;
            goal.mDst.z = pos.z;
            ctx->obj->SetRequest(goal);
        }
    }
}

// @ 0x00d5aae0
int __cdecl EraseRefValue(RefPtrVector* vec, const RefPtr* pValue)
{
    RefPtr* first = vec->mpBegin;
    RefPtr* last = vec->mpEnd;
    RefCounted* target = pValue->mpObject;
    if (first != last)
    {
        do
        {
            if (first->mpObject == target)
                break;
            ++first;
        } while (first != last);
    }

    RefPtr* newEnd = first;
    if (first != last)
    {
        do
        {
            if (first->mpObject != pValue->mpObject)
                *newEnd++ = *first;
            ++first;
        } while (first != last);

        if (newEnd != last)
        {
            vec->erase(newEnd, last);
            return (int)(last - newEnd);
        }
    }
    return 0;
}

// @ 0x00d5acc0
void Vec3AllocVector::swap(Vec3AllocVector& other)
{
    if (&mAllocTag == &other.mAllocTag)
    {
        Vec3* ob = other.mpBegin;
        Vec3* tb = mpBegin;
        mpBegin = ob;
        other.mpBegin = tb;
        _ReadWriteBarrier();
        Vec3* te = mpEnd;
        _ReadWriteBarrier();
        Vec3* oe = other.mpEnd;
        mpEnd = oe;
        other.mpEnd = te;
        _ReadWriteBarrier();
        Vec3* oc = other.mpCapacity;
        Vec3* tc = mpCapacity;
        mpCapacity = oc;
        other.mpCapacity = tc;
        return;
    }

    Vec3AllocVector tmp;
    tmp.CopyConstruct(*this);
    *this = other;
    other = tmp;
    if (tmp.mpBegin != 0 && tmp.mpBegin != tmp.mpInlineBuffer)
        operator delete(tmp.mpBegin);
}

// @ 0x00d5ad40
Vec4* Vec4Vector::insert(Vec4* pos, const Vec4& value)
{
    int index = (int)(pos - mpBegin);
    Vec4* end = mpEnd;
    if (pos == end && end != mpCapacity)
    {
        mpEnd = end + 1;
        if (end != 0)
        {
            end->mKey = value.mKey;
            end->y = value.y;
            end->z = value.z;
            end->w = value.w;
        }
    }
    else
    {
        InsertGrow(pos, &value);
    }
    return mpBegin + index;
}

// @ 0x00d5adf0
void SP::StopAndClearSoundList(SoundHandleList* handles)
{
    int i = 0;
    u32_s00d5_a260 handle;
    if (((handles->mEnd - handles->mBegin) & ~3) > 0)
    {
        do
        {
            handle = ((u32_s00d5_a260*)handles->mBegin)[i];
            AudioSystem_s00d5_a260* audio = GetSystemAT_s00d5_a260();
            if (audio)
            {
                audio->Begin(0x347536b);
                audio->SetParam(0x3475385, handle);
                audio->SetParam(0x34753a0, 0);
                audio->Commit();
            }
            i++;
        } while (i < (handles->mEnd - handles->mBegin) >> 2);
    }

    u32_s00d5_a260* last = (u32_s00d5_a260*)handles->mEnd;
    u32_s00d5_a260* first = (u32_s00d5_a260*)handles->mBegin;
    memcpy(first, last, (char*)last - (char*)last);
    handles->mEnd += -((((int)last - (int)first) >> 2)) * 4;
}

// @ 0x00d5ae80
void TribeTrailOwner::UpdateTrail()
{
    float dz = mPreviousPosition.z - mCurrentPosition.z;
    float dy = mPreviousPosition.y - mCurrentPosition.y;
    float dx = mPreviousPosition.x - mCurrentPosition.x;
    if (dz * dz + dy * dy + dx * dx > kTrailMoveThreshold)
    {
        mPreviousPosition = mCurrentPosition;

        mTrail.erase(mTrail.mpBegin, mTrail.mpEnd);

        Vec3 ground;
        PlanetModel()->DirectionToSurfacePosition(&ground, &mCurrentPosition);

        TribeMemberList* members = mpTribe->GetMembers();
        for (uint32_t i = 0; i < (uint32_t)members->Size(); ++i)
        {
            TribeCreature* creature = (*members)[i];
            float speed = creature->mVirtual.GetSpeed();
            const Vec3* pos = creature->mVirtual.GetPosition();

            float mdz = pos->z - ground.z;
            float mdy = pos->y - ground.y;
            float mdx = pos->x - ground.x;
            float inv = 1.0f / (float)sqrt(mdz * mdz + mdy * mdy + mdx * mdx + kTrailNormalizeEpsilon);

            float vx = (inv * mdx) * speed;
            float vy = (mdy * inv) * speed;
            float vz = (mdz * inv) * speed;

            const Vec3* pos2 = creature->mVirtual.GetPosition();
            Vec3 target;
            target.x = pos2->x + vx;
            target.y = pos2->y + vy;
            target.z = pos2->z + vz;

            Vec3 tmp;
            Vec3 surface = *PlanetModel()->DirectionToSurfacePosition(&tmp, &target);
            mTrail.push_back(surface);
        }
    }
}

// @ 0x00d5b0c0
void Viz_s00d5_b0c0::UpdateBackgroundNoise()
{
    if (F<int>(this, 0xa64) == F<int>(this, 0xa68)) return;

    int  noise = 1;
    bool haveVec = false;
    Vec3 v = { 0.0f, 0.0f, 0.0f };
    Vec3 tmp;

    if (CITY->FUN_00bd7df0()) noise = 2;
    if (CITY->FUN_00bd7d00() > F<float>(this, 0xb18)) noise = 3;

    if (F<int>(this, 0xb20) < 8) {
        float delta = CITY->FUN_00bd7d00() - F<float>(this, 0xb58);
        F<float>(this, 0xb58) = CITY->FUN_00bd7d00();
        if (delta > 2.0f) {
            F<int>(this, 0xb20) = 5;
            F<u32>(this, 0xb48) = 3000;
            ((Timer_s00d5_b0c0*)((char*)this + 0xb28))->Restart();
        } else if (delta < -2.0f) {
            F<int>(this, 0xb20) = 6;
            F<u32>(this, 0xb48) = 3000;
            ((Timer_s00d5_b0c0*)((char*)this + 0xb28))->Restart();
        } else if (F<int>(this, 0x38c) != 0) {
            F<int>(this, 0xb20) = 7;
            F<u32>(this, 0xb48) = 2000;
            ((Timer_s00d5_b0c0*)((char*)this + 0xb28))->Restart();
        }
        if (CITY->FUN_00c004c0(0)) noise = 4;
    }

    if (CITY->FUN_00bd8f30()) {
        int pid = NounManager()->GetPlayerEmpireOrMinus1();
        int found = -1, other = -1;
        bool sawOwn = false;
        for (int i = 0; i < 4; i++) {
            void* c = CITY->FUN_00bd8d60(i);
            if (F<int>(c, 0x1d8) == 2) {
                if (i == F<int>(this, 0xb1c)) sawOwn = true;
                if (F<int>(c, 0x1dc) == pid) found = i;
                else other = i;
            }
        }
        if (found > -1) other = found;
        else if (sawOwn) other = F<int>(this, 0xb1c);
        F<int>(this, 0xb1c) = other;
        void* c2 = CITY->FUN_00bd8d60(other);
        if (F<float>(c2, 0x20c) > 0.85f) {
            noise = 0xb;
        } else if (F<float>(c2, 0x210) > 0.85f) {
            noise = 0xc;
        } else {
            goto noVec;
        }
        {
            haveVec = true;
            Vec3* p = VC0_s00d5_b0c0<Vec3*>((char*)c2 + 0x100, 0x2c / 4);
            ((u32*)&v)[0] = ((u32*)p)[0]; ((u32*)&v)[1] = ((u32*)p)[1]; ((u32*)&v)[2] = ((u32*)p)[2];
        }
    } else {
        F<int>(this, 0xb1c) = -1;
    }

noVec:
    Vec* members = CITY->GetMembers();
    if ((u32)((members->end - members->begin) >> 2) < 2 && SP_GetCurrentGameMode_s00d5_b0c0() == 0x1654c05)
        noise = 0;

    u32 h = F<u32>(this, 0xb50);
    if (h != 0) {
        AudioSystem* at = GetSystemAT();
        if (at == 0 || !at->IsPlaying(h)) {
            F<u32>(this, 0xb50) = 0;
            F<bool>(this, 0xb54) = false;
        }
    }
    if (F<u32>(this, 0xb50) != 0 && F<bool>(this, 0xb54)) {
        int mode = FUN_00b3d4d0_s00d5_b0c0()->mode;
        if (mode != 1 && mode != 2) {
            FUN_00572020(F<u32>(this, 0xb50), 0);
            F<bool>(this, 0xb54) = false;
            F<u32>(this, 0xb50) = 0;
        }
    }

    if (F<char>(CITY, 0x2a0) != 0) {
        int mode = FUN_00b3d4d0_s00d5_b0c0()->mode;
        bool indoors = (mode == 1 || mode == 2);
        F<int>(this, 0xb20) = F<int>(CITY, 0x29c) + 8;
        F<u32>(this, 0xb48) = 10000;
        ((Timer_s00d5_b0c0*)((char*)this + 0xb28))->Restart();
        AudioSystem* at = GetSystemAT();
        u32 nh = at ? at->Create() : 0;
        F<u32>(this, 0xb50) = nh;
        if (indoors) {
            KillSetiEffects(g_tab147ba00[F<int>(CITY, 0x29c)], nh);
            F<bool>(this, 0xb54) = true;
        } else if (!VC0_s00d5_b0c0<bool>((char*)CITY + 0x120, 0x58 / 4)) {
            CITY->FUN_00bd9480(&tmp);
            Start3dSoundByName(g_tab147b9f4[F<int>(CITY, 0x29c)], F<u32>(this, 0xb50), tmp.x, tmp.y, tmp.z);
        }
    }

    u64 elapsed = ((Timer_s00d5_b0c0*)((char*)this + 0xb28))->GetElapsedTime();
    if (elapsed < (u64)F<u32>(this, 0xb48) && F<int>(this, 0xb20) != 0)
        noise = F<int>(this, 0xb20);
    else
        F<int>(this, 0xb20) = 0;

    if (noise != F<int>(this, 0xb14)) {
        Vec* hv = (Vec*)((char*)this + 0xb00);
        F<int>(this, 0xb14) = noise;
        if (hv->begin != hv->end)
            StopSounds(hv);
        if (noise != 0) {
            Vec3* pos;
            if (haveVec) pos = &v;
            else pos = VC1_s00d5_b0c0<Vec3*, Vec3*>(CITY, 0x58 / 4, &tmp);
            ((Creature_s00d5_b0c0*)F<void*>(F<void*>(this, 0xa64), 0))->StartIndependentSound(g_tab01583e6c[noise], pos, hv);
        }
    }

    if (CivModeStrategyGet()->FUN_00cf7a90())
        CITY->FUN_00c00510(0);

    if (CITY->FUN_00c004c0(0)) {
        if (F<u32>(this, 0xb4c) == 0) {
            AudioSystem* at = GetSystemAT();
            F<u32>(this, 0xb4c) = at ? at->Create() : 0;
            CITY->FUN_00bd9480(&tmp);
            Start3dSoundByName(0xc0ba2669, F<u32>(this, 0xb4c), tmp.x, tmp.y, tmp.z);
        }
    } else if (F<u32>(this, 0xb4c) != 0) {
        u32 bh = F<u32>(this, 0xb4c);
        AudioSystem* at = GetSystemAT();
        if (at) {
            at->Begin(0x347536b);
            at->SetParam(0x3475385, bh);
            at->SetParam(0x34753a0, 0);
            at->Commit();
        }
        F<u32>(this, 0xb4c) = 0;
    }
}

// @ 0x00d5b6c0
int Viz_s00d5_b0c0::FUN_00d5b6c0()
{
    int prev = F<int>(this, 0xc3c);
    if (prev >= 0) {
        F<int>(this, 0xc3c) = -1;
        return prev;
    }

    City_s00d5_b0c0* city = CITY;
    float dist = city->FUN_00bd7d00();
    int specialty = city->GetVehicleSpecialty() + 1;
    Vec3 pos;
    void* tod = FUN_00bd9480(city, &pos);
    int time = FUN_00bc30b0((int)tod)->FUN_00bc2b80();
    int tierWant = (time != 0) + 1;
    int sizeWant = F<unsigned char>(city, 0x2a0) ? F<int>(city, 0x29c) + 1 : 0;
    unsigned char flagWant = city->FUN_00bd7df0() ? 1 : 0;
    CivStrategy* strat = CivModeStrategyGet();
    bool active = strat->FUN_00cf7a90();
    if (!active || F<unsigned char>(city, 0x2a0)) {
        int n = (int)(F<int>(this, 0xbac) - F<int>(this, 0xba8)) / (int)sizeof(CityVehicles);        FixedIntVec16 found;
        found.mpEnd = found.mBuffer;
        for (int i = 0; i < n; ++i) {
            CityVehicles* v = (CityVehicles*)(F<int>(this, 0xba8) + i * (int)sizeof(CityVehicles));
            if (v->mMinBand <= dist && dist <= v->mMaxBand
                && (v->mSpecialty == 0 || v->mSpecialty == specialty)
                && (v->mTier == 0 || v->mTier == tierWant)
                && v->mSize == sizeWant
                && v->mFlags == flagWant)
                found.push_back(&i);
        }
        if (found.mpEnd != found.mBuffer) {
            int pick = found.mBuffer[g_randomGlobal.RandomUint32Uniform(
                            ((u32)found.mpEnd - (u32)found.mBuffer) >> 2)];
            if (found.mBuffer != 0 && found.mBuffer != (int*)&found)
                operator_delete__(found.mBuffer);
            return pick;
        }
        if (found.mBuffer != 0 && found.mBuffer != (int*)&found)
            operator_delete__(found.mBuffer);
    } else {
        flagWant = 0;
    }
    return -1;
}

// @ 0x00d5b8d0
void Viz_s00d5_b0c0::FUN_00d5b8d0()
{
    if (!F<unsigned char>(this, 0xaf5))
        return;

    FUN_00b3d480(this);                          // 0x00b3d480
    CultureSlot* slot = (CultureSlot*)((char*)this + 0x394);
    for (int i = 0; i < 4; ++i) {
        ObjVector* v = (ObjVector*)((char*)this + 0xa7c + i * 0x14);
        if (v->mpBegin != v->mpEnd) {
            for (RefObj_s00d5_b0c0** it = v->mpBegin; it != v->mpEnd; ++it) {
                RefObj_s00d5_b0c0* o = *it;
                o->StopAll((void*)0xffffffff);
                if (F<void*>(o, 0xb54) != 0) {
                    void* p = F<void*>(F<void*>(o, 0xb54), 0x180);
                    if (p != 0)
                        F<u32>(p, 4) &= 0xfffff7ff;
                }
                FUN_00c0d3a0(o);                 // 0x00c0d3a0
                FUN_00bcb3d0(F<void*>(o, 0xb4c));// 0x00bcb3d0
                FUN_00accf80(FUN_00b3d480(o));   // 0x00b3d480, 0x00accf80
                FUN_00c227c0(o);                 // 0x00c227c0
            }
            slot->mFlag00 = 0;
            RefObj_s00d5_b0c0** first = v->mpBegin;
            RefObj_s00d5_b0c0** last = v->mpEnd;
            RefObj_s00d5_b0c0** q = CopyObjectRange(last, first, first);   // 0x006782c0
            for (; q < v->mpEnd; ++q) {
                if (*q != 0)
                    (*q)->Release();
            }
            v->mpEnd += -(((int)last - (int)first) >> 2) * 4;
        }
        slot = (CultureSlot*)((char*)slot + 0x198);
    }
    F<unsigned char>(this, 0xaf5) = 0;
}

// @ 0x00d5b9f0
void Viz_s00d5_b0c0::FUN_00d5b9f0()
{
    Vec3Vector pts;

    CityEntryList* list = CITY->FUN_00bd7f40();
    int count = (int)(list->mpEnd - list->mpBegin) / (int)sizeof(CityEntry);
    for (int i = 0; i < count; ++i) {
        CityEntry* e = (CityEntry*)((char*)list->mpBegin + i * sizeof(CityEntry));
        if (e->mFlag00 == 0)
            pts.push_back(e->mPosition);
    }

    void* cityInfo = VC0_s00d5_b0c0<void*>(CITY, 0x6c / 4);
    float radius = *(float*)((char*)cityInfo + 0x258);

    Vec3 center1, center2;
    void* sub = (char*)CITY + 0x120;
    typedef void* (__thiscall* SubGet)(void*, Vec3*, float);
    typedef void* (__thiscall* CityGet)(void*, Vec3*, float, void*);
    void* r1 = ((SubGet)(*(void***)sub)[0x5c / 4])(sub, &center1, 0.0f);
    void* r2 = ((CityGet)(*(void***)CITY)[0x58 / 4])(CITY, &center2, radius, r1);

    ((cActionCircle_s00d5_b0c0*)((char*)this + 0xbd4))->SetAtCenter(r2, &center2, radius, r1);
    ((cActionCircle_s00d5_b0c0*)((char*)this + 0xbd4))->EmitCopy(&pts, g_14853e0);
}

// @ 0x00d5bc30
void Vec3Slots::DoInsertValue(unsigned index, const Vec3* value)
{
    void* mem[4];
    unsigned capCount = (unsigned)((int)((char*)mpCap - (char*)mpBegin) / 12);
    if (index > capCount) {
        mem[0] = DoInsertGrow(index, value, mAlloc);
        AssignTempGuard(this, mem);
        if (mem[0] != 0 && mem[0] != mem[2])
            operator_delete__(mem[0]);
        return;
    }
    unsigned endCount = (unsigned)((int)((char*)mpEnd - (char*)mpBegin) / 12);
    if (index > endCount) {
        FillVec3Range(mpBegin, mpEnd, value);
        int have = (int)((char*)mpEnd - (char*)mpBegin) / 12;
        CopyVec12(mpEnd, index - have, value);
        mpEnd = (Vec3*)((char*)mpEnd + (index - have) * 12);
        return;
    }
    CopyVec3Range(mpBegin, index, value);
    EraseVec3(this, (Vec3*)((char*)mpBegin + index * 12), mpEnd);
}

// @ 0x00d5bdb0
void SlotRange::Assign(const SlotRange* src)
{
    if (src == this)
        return;
    unsigned n = (unsigned)((char*)src->mpEnd - (char*)src->mpBegin) / 0x18;
    if ((unsigned)((char*)mpCap - (char*)mpBegin) / 0x18 < n) {
        void* mem = AllocSlotRange(n, src->mpBegin, src->mpEnd);
        DestroySlotRange(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpCap = (char*)mem + n * 0x18;
        mpBegin = mem;
        mpEnd = (char*)mem + n * 0x18;
        return;
    }
    unsigned have = (unsigned)((char*)mpEnd - (char*)mpBegin) / 0x18;
    if (have < n) {
        AskCopySlots(mpBegin, src->mpBegin, (char*)src->mpBegin + have * 0x18);
        SlotCopyCtorWrap(src->mpEnd, (char*)src->mpBegin + have * 0x18, mpEnd);
        mpEnd = (char*)mpBegin + n * 0x18;
        return;
    }
    AskCopySlots(mpBegin, src->mpBegin, src->mpEnd);
    DestroySlotRange((char*)mpBegin + n * 0x18, mpEnd);
    mpEnd = (char*)mpBegin + n * 0x18;
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

// @ 0x00d5ccf0
void FUN_00d5ccf0(void)
{}

// @ 0x00d5cfd0
void FUN_00d5cfd0(void)
{}

// @ 0x00d5d360
void FUN_00d5d360(void)
{}

// @ 0x00d5d430
void FUN_00d5d430(void)
{}

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

// @ 0x00d5d5b0
void FUN_00d5d5b0(void)
{}

// @ 0x00d5d880
void cCityVisualizer_s00d5_d880::AllegianceUpdate()
{
    if (mpParticleEffect == nullptr) {
        IGameObject* pEffects = EffectsManager();
        IGameObject* pOld = mpParticleEffect;
        if (pOld != nullptr) {
            mpParticleEffect = nullptr;
            pOld->Release();
        }
        if (pEffects->Slot2c() != 0) {
            FixedVector3s points;
            points.push_back(gEmptyPoint);
            mpParticleEffect->Slot40();
            mpParticleEffect->Slot40();
        }
        if (mpParticleEffect == nullptr)
            return;
    }

    int32_t nSirens = 0;
    FUN_00cf74c0();
    if (!FUN_00cf7a90() && mppSirenIds != mppSirenEnd) {
        IntVector sirenIds;
        FUN_00bdf750(&sirenIds);
        FixedVector3s positions;
        FixedVector3s targets;
        for (int32_t i = 0; i < (int32_t)((uint8_t*)sirenIds.mpEnd - (uint8_t*)sirenIds.mpBegin) / 8; ++i) {
            void* pNoun = (void*)((int32_t*)sirenIds.mpBegin)[i * 2];
            IGameObject* pObject = FUN_00b25f40(pNoun);
            if (pObject != nullptr) {
                Vector3_s00d5_d880* pPoint = (Vector3_s00d5_d880*)FUN_00d5d430((uint8_t*)sirenIds.mpBegin + i * 8);
                pPoint->x = *(float*)((uint8_t*)pObject + 0xc4);
                pPoint->y = *(float*)((uint8_t*)pObject + 0xc8);
                pPoint->z = *(float*)((uint8_t*)pObject + 0xcc);
            }
        }

        int32_t nCount = 0;
        IGameObject* pCiv = AsCity(mpCity)->GetCivilization();
        IGameObject* pEmpire = (IGameObject*)pCiv->Slot4c();
        int32_t* pSiren = (int32_t*)mppSirenIds;
        int32_t* pSirenEnd = (int32_t*)mppSirenEnd;
        FixedVector3s targets2;
        while (pSiren != pSirenEnd && nCount < 100) {
            int32_t nNoun = *pSiren;
            IGameObject* pObject = *(IGameObject**)(nNoun + 0xff0);
            if (pObject != pEmpire) {
                Vector3_s00d5_d880 pos;
                pos.x = *(float*)((uint8_t*)pObject + 0xc4);
                pos.y = *(float*)((uint8_t*)pObject + 0xc8);
                pos.z = *(float*)((uint8_t*)pObject + 0xcc);
                float fRadius = *(float*)((uint8_t*)pObject + 0xd0)
                              - *(float*)((uint8_t*)pObject + 0xd4) + 2.0f;
                float fScale = 1.0f / (float)(sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) + 1e-08);
                Vector3_s00d5_d880 target;
                target.x = fScale * pos.x * fRadius + pos.x;
                target.y = fScale * pos.y * fRadius + pos.y;
                target.z = fScale * pos.z * fRadius + pos.z;
                positions.push_back(target);
                targets2.push_back(*(const Vector3_s00d5_d880*)FUN_00d5d430(&pObject));
                nCount = nCount + 1;
            }
            ++pSiren;
        }

        int32_t nFill = 100 - nCount;
        while (nFill != 0) {
            positions.push_back(gEmptyPoint);
            targets2.push_back(gEmptyPoint);
            --nFill;
        }
        if (nCount > 0) {
            mpParticleEffect->Slot40();
            mpParticleEffect->Slot40();
        }
        if (nCount > 0) {
            if (mpParticleEffect->Slot10())
                return;
            mpParticleEffect->SetActive(false);
            return;
        }
    }
    mpParticleEffect->Slot0c(0);
}

// @ 0x00d5de40
void cCityVisualizer_s00d5_d880::UpdateArtifacts()
{
    mpCity->Slot6c();

    IGameObject* pEvent = *(IGameObject**)((uint8_t*)this + 0x0c70);
    if (pEvent != nullptr) {
        if (!FUN_00bec0f0((IGameObject*)pEvent->Slot2c())) {
            pEvent = *(IGameObject**)((uint8_t*)this + 0x0c70);
            *(IGameObject**)((uint8_t*)this + 0x0c70) = nullptr;
            if (pEvent != nullptr)
                pEvent->Release();
        }
    }

    cActionCircle_s00d5_d880* pCircles = (cActionCircle_s00d5_d880*)FUN_00bd7f50();
    if (FUN_00af9f60() == 0)
        return;

    void** pList = ((cGameNounManager_s00d5_d880*)NounManager_s00d5_d880())->GetGameDataVector(
        (int32_t)0xcd7d10, (void*)0xd3d420, (void*)0xad4930, (void*)0xb1e500, 0x2dd8c42);
    void** ppAgentsEnd = *(void***)((uint8_t*)pList + 8);
    void** ppAgents = *(void***)((uint8_t*)pList + 4);
    int32_t nCount = (int32_t)(ppAgentsEnd - ppAgents);
    for (int32_t i = 0; i < nCount; ++i) {
        int32_t* pAgent = (int32_t*)ppAgents[i];
        if (pAgent[0x658 / 4] != 4)
            continue;

        IGameObject* pAgentObject = (IGameObject*)((uint8_t*)pAgent + 0x34);
        bool bAlive = FUN_00bec0f0((IGameObject*)pAgentObject->Slot2c());
        int32_t nSlot = FUN_00afad30((IGameObject*)pAgent);
        bool bHasSlot = nSlot != -1;

        if (!bAlive) {
            if (bHasSlot)
                pCircles->RemoveAgent(pAgent);
        } else if (*(IGameObject**)((uint8_t*)this + 0x0c70) == nullptr) {
            if (bHasSlot) {
                if (mPacking == 0.0f && RandomDoubleUniform() < 0.1) {
                    FUN_00c70110((IGameObject*)pAgent);
                    Vector3_s00d5_d880 dir;
                    IGameObject* pCircle = mpCity;
                    pCircle->Slot5c();
                    Vector3_s00d5_d880 out;
                    out.x = -dir.x;
                    out.y = -dir.y;
                    out.z = -dir.z;
                    float fRadius = (float)(size_t)((IGameObject*)pCircle)->Slot74() + 1.0f;
                    FUN_00af9cf0((IGameObject*)pCircle->Slot2c(), &out, 0, &dir);
                    FUN_00afd6d0(0x40000000, 0x3f000000, 4);
                    (void)fRadius;
                }
            } else {
                IGameObject* pOwner = (IGameObject*)pAgentObject->Slot2c();
                Vector3_s00d5_d880 out;
                Vector3_s00d5_d880* pSurface = ((cPlanetModel_s00d5_d880*)PlanetModel_s00d5_d880(&out, pOwner))
                                        ->DirectionToSurfacePosition(&out, (const Vector3_s00d5_d880*)pOwner->Slot2c());
                const Vector3_s00d5_d880* pPos = (const Vector3_s00d5_d880*)pAgentObject->Slot2c();
                float dx = pPos->x - pSurface->x;
                float dy = pPos->y - pSurface->y;
                float dz = pPos->z - pSurface->z;
                if (sqrtf(dx * dx + dy * dy + dz * dz) < 0.1f)
                    ((IGameObject*)pAgent)->Slot00();
            }
        }
    }
}

// declarations s00d5d880's SpaceOnlyTick (0x00d5e0c0) needs
// the slice's SP::cSPTimer stub (signed 64-bit GetElapsedTime, non-const): the canonical header's unsigned const one
// compiles the `>> 32` test differently
class cSPTimer_s00d5_d880 {
public:
    int64_t GetElapsedTime();       // 0x00bc3190
    void Restart();                 // 0x00bc3130
};
extern float gGateRadii[7];                     // 0x0147bb94
void __cdecl FUN_00bc97f0_s00d5_d880(int32_t nA, int32_t nB, uint32_t nC, int32_t nD); // 0x00bc97f0 (slice spelling: the bits of the float priority as an integer)
extern float gWorshipChances[7][3];             // 0x0147bb40
class cSPSimulatorSpaceGame {
public:
    IGameObject* GetPlayerInventory();
};
Vector3_s00d5_d880* __cdecl FUN_00b81630(const Vector3_s00d5_d880* pDir, IGameObject* pPlanetModel);  // 0x00b81630
void* __cdecl FUN_00ffbe50();                       // 0x00ffbe50
void __cdecl FUN_00bef8e0();                        // 0x00bef8e0
int32_t __cdecl FUN_00fc8380();                     // 0x00fc8380
void __cdecl FUN_00d5ae80();                        // 0x00d5ae80
bool __cdecl FUN_01062ea0(void* pA, void* pB, void* pC);                    // 0x01062ea0
void __cdecl FUN_00bc97b0();                        // 0x00bc97b0
void __cdecl Start3dSoundByName_s00d5_d880(int32_t nSoundId, IGameObject* pAudio,
                                int32_t nA, int32_t nB, int32_t nC);        // 0x00bd5b30 region
uint32_t __cdecl RandomUint32Uniform(uint32_t nRange);                      // 0x00b3d360
class cSPLivingUniverse_s00d5_d880 {
public:
    int32_t GetPlayerEmpire();
    IGameObject* GetActivePlanet();
};
IGameObject* __cdecl GetActivePlanet_s00d5_d880();             // 0x00c71e30 region
IGameObject* __cdecl FUN_01015df0();                // 0x01015df0
int32_t __cdecl FUN_00c71e30();                     // 0x00c71e30
bool __cdecl FUN_00a98020(IGameObject* pNode);      // 0x00a98020
void __cdecl FUN_00b3d2c0(int32_t nA, int32_t nB, int32_t nC);              // 0x00b3d2c0
double __cdecl FUN_00d00a10(int32_t nA, int32_t nB, int32_t nC);            // 0x00d00a10
void __cdecl ActivateWorshipPosture();              // 0x00d5bf50 region

// @ 0x00d5e0c0
int32_t cCityVisualizer_s00d5_d880::SpaceOnlyTick()
{
    int32_t nResult = 0;

    if ((int32_t)(((cSPTimer_s00d5_d880*)&mArtifactTimer)->GetElapsedTime() >> 32) != 0
        || (uint32_t)((cSPTimer_s00d5_d880*)&mArtifactTimer)->GetElapsedTime() > 1000) {
        ((cSPTimer_s00d5_d880*)&mArtifactTimer)->Restart();
        UpdateArtifacts();
    }

    IGameObject* pNode = (IGameObject*)FUN_01015df0();
    if (FUN_00a98020(pNode)) {
        IGameObject* pParent = (IGameObject*)((IGameObject*)FUN_01015df0())->Slot00();
        if (pParent == nullptr)
            goto use_player_inventory;
        pParent = (IGameObject*)((IGameObject*)FUN_01015df0())->Slot00();
        Vector3_s00d5_d880* pPos = (Vector3_s00d5_d880*)pParent->SlotC0();
        mDestX = pPos->x;
        mDestY = pPos->y;
        mDestZ = pPos->z;
    } else {
    use_player_inventory:
        IGameObject* pGame = (IGameObject*)FUN_00ffbe50();
        IGameObject* pInventory = ((cSPSimulatorSpaceGame*)pGame)->GetPlayerInventory();
        IGameObject* pItem = (IGameObject*)pInventory->Slot34();
        Vector3_s00d5_d880 pos;
        IGameObject* pModel = PlanetModel_s00d5_d880(&pos, (IGameObject*)pItem->Slot2c());
        Vector3_s00d5_d880* pPoint = (Vector3_s00d5_d880*)FUN_00b81630(&pos, pModel);
        mDestX = pPoint->x;
        mDestY = pPoint->y;
        mDestZ = pPoint->z;
    }

    int32_t nPackingMode = -1;
    Vector3_s00d5_d880* pCityPos = (Vector3_s00d5_d880*)mpCity->Slot120();
    float dx = pCityPos->x - mDestX;
    float dy = pCityPos->y - mDestY;
    float dz = pCityPos->z - mDestZ;
    if (sqrtf(dx * dx + dy * dy + dz * dz) < 60.0f) {
        IGameObject* pCiv = AsCity(mpCity)->GetCivilization();
        FUN_00bef8e0();
        int32_t nState = FUN_00fc8380();
        if (nState == 0) {
            nPackingMode = 2;
            nResult = nPackingMode;
        } else if (nState == 1) {
            nPackingMode = 0x10;
            nResult = nPackingMode;
        }
    }

    FUN_00d5ae80();
    if ((int32_t)(((cSPTimer*)((uint8_t*)this + 0x0c80))->GetElapsedTime() >> 32) != 0
        || (uint32_t)((cSPTimer*)((uint8_t*)this + 0x0c80))->GetElapsedTime() > 5000) {
        mPacking = (float)RandomUint32Uniform(3);
        ((cSPTimer*)((uint8_t*)this + 0x0c80))->Restart();
    }

    int32_t nOwner = (int32_t)mpCity->Slot4c();
    int32_t nPlayer = ((cSPLivingUniverse_s00d5_d880*)GetActivePlanet_s00d5_d880())->GetPlayerEmpire();
    nPlayer = *(int32_t*)((uint8_t*)nPlayer + 0x84);
    float fChance;
    if (nOwner == nPlayer) {
        fChance = 10.0f;
    } else {
        FUN_00b3d2c0(nOwner, nPlayer, 0);
        fChance = (float)FUN_00d00a10(nOwner, nPlayer, 0);
    }

    if (nPackingMode == 2) {
        if (fabsf(mPacking - fChance) <= 0.5f)
            goto worship_countdown;
        mPacking = fChance;
    } else {
        if (mPacking == 0.0f)
            goto worship_countdown;
        mPacking = 1.0f;
        mnWorshipCountdown = 3;
    }

worship_countdown:
    if (mnWorshipCountdown >= 0) {
        if (mnWorshipCountdown == 3) {
            ActivateWorshipPosture();
            ((cSPTimer*)((uint8_t*)this + 0x0c68 + 0x18))->Restart();
        }

        int32_t nStage = 0;
        int32_t nIndex = 0;
        do {
            nStage = nIndex;
            if (fChance <= gGateRadii[nIndex])
                break;
            ++nIndex;
            nStage = 0;
        } while (nIndex < 7);

        int32_t nSirens = (int32_t)(mppSirenEnd - mppSirenIds);
        IGameObject* pPlanet = ((cSPLivingUniverse_s00d5_d880*)GetActivePlanet_s00d5_d880())->GetActivePlanet();
        int32_t nAudio = FUN_00c71e30() != 0;

        for (int32_t i = 0; i < nSirens; ++i) {
            if ((float)(i & 0xf) == (float)mnWorshipCountdown) {
                float fRand = (float)RandomDoubleUniform();
                int32_t nSlot = 0;
                if (gWorshipChances[nStage][0] <= fRand) {
                    if (gWorshipChances[nStage][0] + gWorshipChances[nStage][1] <= fRand)
                        nSlot = nAudio == 0 ? 0x80 : 0x20;
                    else
                        nSlot = 0;
                } else {
                    nSlot = nAudio == 0 ? 0x10 : 0x40;
                }
                FUN_00bc97b0();
                if (nSlot != 0)
                    FUN_00bc97f0_s00d5_d880(nSlot, 0, 0x7f7fffff, 0);
            }
        }
        --mnWorshipCountdown;
    }

    Vector3_s00d5_d880 outPos;
    int32_t nType = 0;
    AsCity(mpCity)->GetCivilization();
    FUN_00bef8e0();
    if (FUN_01062ea0(&nType, &outPos, nullptr)) {
        if (mpAudioSystem == nullptr) {
            mpAudioHandle = nullptr;
        } else {
            mpAudioHandle = mpAudioSystem->GetSystemAT();
        }
        FUN_00bd9480(&mpAudioHandle);
        Start3dSoundByName_s00d5_d880((int32_t)mnSoundId, mpAudioSystem->GetSystemAT(), 0, 0, 0);
    }
    return nResult;
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

// 0x00d5edc0: not byte-exact; the byte-exact version is the lifted one in match/slices/s00d5edc0/s00d5edc0.cpp
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
                        if (dy * dy + (dx * dx + dz * dz) < 10000.0f) {
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

// @ 0x00d60ce0
void Viz_s00d6_0ce0::UpdateSlotCircles()
{
    CircleVec* circles = (CircleVec*)((char*)this + 0x220);
    circles->erase(circles->mpBegin, circles->mpEnd);

    Layout* lay = F<City_s00d6_0ce0*>(this, 0xaf0)->FUN_00bd7f40();
    float base = F<float>(lay, 0x10);
    int n = (int)((char*)F<void*>(lay, 0x54) - (char*)F<void*>(lay, 0x50)) / 0x18;

    for (int i = 0; i < n; ++i) {
        void* slot = lay->SlotAt(i);
        void* occ = ((SlotElem*)slot)->GetOccupant();
        float radius;
        if (occ) {
            void* item = VC1_s00d6_0ce0<void*, u32>(occ, 3, 0x1186577);
            if (item) radius = VC0_s00d6_0ce0<float>(item, 29);
            else radius = base;
        } else {
            radius = base;
        }

        float* pv = (float*)((char*)F<void*>(lay, 0x50) + i * 0x18 + 0xc);
        Vec3f pos;
        pos.x = pv[0];
        pos.y = pv[1];
        pos.z = pv[2];

        if (circles->mpEnd < circles->mpCapacity) {
            ACircle* e = circles->mpEnd;
            circles->mpEnd = e + 1;
            if (e) e->ctor();
        } else {
            ACircle tmp;
            tmp.ctor();
            circles->FUN_00d5ee20(circles->mpEnd, &tmp);
            tmp.dtor();
        }

        Vec3f outv;
        Vec3f* ctr = F<City_s00d6_0ce0*>(this, 0xaf0)->FUN_00bd9480(&outv);
        float dy = ctr->y - pos.y;
        float dz = ctr->z - pos.z;
        float dx = ctr->x - pos.x;
        float inv = 1.0f / sqrtf(dy * dy + dz * dz + dx * dx + g_eps_13ec4b8);
        Vec3f dir;
        dir.x = inv * dx;
        dir.y = inv * dy;
        dir.z = inv * dz;

        ACircle* last = circles->mpEnd - 1;
        last->SetAtCenter(&pos, radius, &dir, 0.0f);
        last->FUN_00afd6d0(g_c1470f1c, 1.0f, 12);
    }
}

// @ 0x00d60f00
void Viz_s00d6_0ce0::SetCity(City_s00d6_0ce0* city)
{
    F<int>(this, 0xc3c) = -1;
    F<int>(this, 0xa4c) = -1;
    if (!g_Init169ec25) {
        FUN_00bc8fa0((const void*)0x1592928);
        FUN_00bc8fa0((const void*)0x1592d00);
        g_Init169ec25 = 1;
    }
    F<bool>(this, 0xaf4) = true;
    FUN_00b3d480_s00d6_0ce0();

    City_s00d6_0ce0* old = F<City_s00d6_0ce0*>(this, 0xaf0);
    if (city != old) {
        if (old != 0) {
            if (city == 0) {
                DestroyRefMember(this, 0xb60);
                DestroyRefMember(this, 0xb64);
                DestroyRefMember(this, 0xb68);
                DestroyRefMember(this, 0xb5c);
            }
            // cached citizens
            RefVec* citizens = (RefVec*)((char*)this + 0xa64);
            int n = citizens->mpEnd - citizens->mpBegin;
            for (int i = 0; i < n; ++i)
                FUN_00d57940(citizens->mpBegin[i]);
            citizens->erase(citizens->mpBegin, citizens->mpEnd);

            // vignette creature instances
            SpVec<char*>* inst = (SpVec<char*>*)((char*)this + 0xac8);
            int m = inst->mpEnd - inst->mpBegin;
            for (int i = 0; i < m; ++i) {
                char* c = inst->mpBegin[i];
                VC1_s00d6_0ce0<void, int>(c, 18, -1);
                char* t = F<char*>(c, 0xb54);
                if (t) {
                    char* u = F<char*>(t, 0x180);
                    if (u)
                        F<u32>(u, 4) &= 0xfffff7ff;
                }
                FUN_00c0d3a0(c);
                ((HostB*)F<void*>(c, 0xb4c))->FUN_00bcb3d0();
                FUN_00b3d480_s00d6_0ce0()->FUN_00accf80(c);
                ((Creature_s00d6_0ce0*)c)->FUN_00c227c0();
            }
            ClearRefs((SpVec<IRef*>*)((char*)this + 0xac8));
            FUN_00d5b8d0();
            ClearRefs((SpVec<IRef*>*)((char*)this + 0x364));
            ClearRefs((SpVec<IRef*>*)((char*)this + 0x378));

            IRef* o = F<IRef*>(this, 0x38c);
            F<IRef*>(this, 0x38c) = 0;
            if (o)
                VC0_s00d6_0ce0<void>(o, 48);

            // sound list
            char* sounds = (char*)this + 0xb00;
            StopAndClearSoundList(sounds);
            {
                SpVec<u32>* v = (SpVec<u32>*)sounds;
                u32* first = v->mpBegin;
                u32* last = v->mpEnd;
                memmove(first, last, (char*)v->mpEnd - (char*)last);
                v->mpEnd -= (last - first);
            }
            F<u32>(this, 0xb14) = 0;
            ReleaseAudioHandle(this, 0xb4c);
            {
                u32 h = F<u32>(this, 0xb50);
                if (h != 0) {
                    AudioSystem_s00d6_0ce0* at = GetSystemAT_s00d6_0ce0();
                    if (at) {
                        at->Begin(0x347536b);
                        at->SetParam(0x3475385, h);
                        at->SetParam(0x34753a0, 0);
                        at->Commit();
                    }
                    F<u32>(this, 0xb50) = 0;
                    F<char>(this, 0xb54) = 0;
                }
            }

            // culture stages: actor lists
            Stage* stages = (Stage*)((char*)this + 0x38c);
            for (int g = 0; g < 4; ++g) {
                F<City_s00d6_0ce0*>(this, 0xaf0)->FUN_00bd9e80(g);
                for (int j = 0; j < 2; ++j) {
                    ClearRefs(&stages[g].mParticipants[j]);
                    ClearRec18(&stages[g].mGroup[j].mSlots);
                }
            }
            if (F<int>(F<City_s00d6_0ce0*>(this, 0xaf0), 0x2cc) == 0)
                F<int>(F<City_s00d6_0ce0*>(this, 0xaf0), 0x2cc) = 1;

            // vignette instances
            VigVec* vig = (VigVec*)((char*)this + 0xbbc);
            for (int i = 0; i < (int)(vig->mpEnd - vig->mpBegin); ++i) {
                VigInfo* p = vig->mpBegin + i;
                StopVignetteInstance(p);
                if (p->flag5)
                    F<char>(this, 0xa40) = 0;
                FUN_00b3d4e0_s00d6_0ce0()->FUN_00bc5040(p->id);
            }
            {
                VigInfo* b = vig->mpBegin;
                VigInfo* e = vig->mpEnd;
                VigInfo* it = CopyVig(e, e, b);
                vig->FUN_00d595d0(it, vig->mpEnd);
                vig->mpEnd -= (e - b);
            }
            F<u32>(this, 0xae4) = 0;
            F<u32>(this, 0xae0) = 0;
            F<u32>(this, 0xadc) = 0;
            {
                IRef* a = F<IRef*>(this, 0xa54);
                F<IRef*>(this, 0xa54) = 0;
                if (a)
                    a->Release();
                F<char>(this, 0xa51) = 0;
                IRef* b2 = F<IRef*>(this, 0xa58);
                F<IRef*>(this, 0xa58) = 0;
                if (b2)
                    VC0_s00d6_0ce0<void>(b2, 25);
                F<u32>(this, 0xa60) = 0;
                F<u32>(this, 0xa5c) = 0;
            }
        }
        City_s00d6_0ce0* cur = F<City_s00d6_0ce0*>(this, 0xaf0);
        if (city != cur) {
            if (city)
                VC0_s00d6_0ce0<void>(city, 0);
            F<City_s00d6_0ce0*>(this, 0xaf0) = city;
            if (cur)
                VC0_s00d6_0ce0<void>(cur, 1);
        }
    }

    if (F<City_s00d6_0ce0*>(this, 0xaf0) == 0)
        return;

    City_s00d6_0ce0* c = F<City_s00d6_0ce0*>(this, 0xaf0);
    u32 want = c->GetCreatureCount();
    F<float>(this, 0xb58) = F<City_s00d6_0ce0*>(this, 0xaf0)->FUN_00bd7d00();
    ((Timer_s00d6_0ce0*)((char*)this + 0xb28))->Restart();
    F<u32>(this, 0xb20) = 0;
    ((CountVec*)((char*)this + 0x364))->FUN_01011cc0(F<City_s00d6_0ce0*>(this, 0xaf0)->GetMembers());
    ((CountVec*)((char*)this + 0x378))->FUN_01011cc0(F<City_s00d6_0ce0*>(this, 0xaf0)->FUN_00bd8130());
    FUN_00d5bfa0(1);
    F<u32>(this, 0xa28) = 0;
    F<u32>(this, 0xa30) = 0;
    F<u32>(this, 0xc38) = 1;
    ((Timer_s00d6_0ce0*)((char*)this + 0xc40))->Restart();
    F<char>(this, 0xa40) = 0;
    FUN_00d5c8c0();
    F<u32>(this, 0x158) = g_PosX_s00d6_0ce0;
    F<u32>(this, 0x15c) = g_PosY_s00d6_0ce0;
    F<u32>(this, 0x160) = g_PosZ_s00d6_0ce0;
    F<int>(this, 0xa44) = -1;

    // resize the per-citizen slot vector to the creature count
    {
        Vec3Vec* v = (Vec3Vec*)((char*)this + 0xb6c);
        u32 size = v->mpEnd - v->mpBegin;
        if (want > size) {
            Vec3_s00d6_0ce0 tmp;
            v->DoInsertN(v->mpEnd, want - size, tmp);
        } else {
            ErasePod(v, v->mpBegin + want, v->mpEnd);
        }
    }

    Stage* stages = (Stage*)((char*)this + 0x38c);
    for (int g = 0; g < 4; ++g) {
        F<City_s00d6_0ce0*>(this, 0xaf0)->FUN_00bd9e80(g);
        for (int j = 0; j < 2; ++j) {
            stages[g].mReserved = 0;
            stages[g].mRequested = 0;
            stages[g].mElapsed = 0;
            stages[g].m10 = 0;
            ((Timer2*)stages[g].mTimer)->FUN_00bc3170();
            ClearRec18(&stages[g].mGate.mSlots);
        }
    }
    UpdateSlotCircles();
    SetupVignetteSpots(0);
    UpdateArtifacts();
    ((Timer_s00d6_0ce0*)((char*)this + 0xc68))->Restart();
    FUN_00d5c720();

    {
        char* cc = F<char*>(this, 0xaf0);
        SpVec<Rec20>* v = (SpVec<Rec20>*)(cc + 0x2a4);
        ErasePod(v, v->mpBegin, v->mpEnd);
    }
    {
        char* cc = F<char*>(this, 0xaf0);
        SpVec<Rec20>* v = (SpVec<Rec20>*)(cc + 0x2b8);
        ErasePod(v, v->mpBegin, v->mpEnd);
    }
    {
        char* cc = F<char*>(this, 0xaf0);
        F<u32>(cc, 0x2d4) = g_PosX_s00d6_0ce0;
        F<u32>(cc, 0x2d8) = g_PosY_s00d6_0ce0;
        F<u32>(cc, 0x2dc) = g_PosZ_s00d6_0ce0;
    }
    F<u32>(F<char*>(this, 0xaf0), 0x2cc) = 0;
    F<u32>(F<char*>(this, 0xaf0), 0x2d0) = 0;
    F<u32>(this, 0xa38) = 0;
    F<u32>(this, 0xa3c) = 0;
}

// @ 0x00d61880
void Viz_s00d6_0ce0::LayoutChanged()
{
    F<bool>(this, 8) = true;

    IRef* old = F<IRef*>(this, 0x38c);
    F<IRef*>(this, 0x38c) = 0;
    if (old) VC0_s00d6_0ce0<void>(old, 48);

    int flag = 4;
    City_s00d6_0ce0* city = F<City_s00d6_0ce0*>(this, 0xaf0);
    PtrVec_s00d6_0ce0* members = (PtrVec_s00d6_0ce0*)city->GetMembers();
    PtrVec_s00d6_0ce0* others = (PtrVec_s00d6_0ce0*)city->FUN_00bd8130();

    {
        u32* it = (u32*)members->mpBegin;
        u32* end = (u32*)members->mpEnd;
        for (; it != end; ++it) {
            u32* g = (u32*)F<void*>(this, 0x364);
            u32* ge = (u32*)F<void*>(this, 0x368);
            while (g != ge && *g != *it) ++g;
            if (g != ge) continue;

            IRef* obj = *it ? (IRef*)(*it + 0x34) : 0;
            IRef* prev = F<IRef*>(this, 0x38c);
            if (obj != prev) {
                if (obj) VC0_s00d6_0ce0<void>(obj, 47);
                F<IRef*>(this, 0x38c) = obj;
                if (prev) VC0_s00d6_0ce0<void>(prev, 48);
            }
            flag = 0xc;
        }
    }

    if (F<void*>(this, 0x38c) == 0) {
        u32* it = (u32*)others->mpBegin;
        u32* end = (u32*)others->mpEnd;
        for (; it != end; ++it) {
            u32* g = (u32*)F<void*>(this, 0x378);
            u32* ge = (u32*)F<void*>(this, 0x37c);
            while (g != ge && *g != *it) ++g;
            if (g != ge) continue;

            IRef* obj = *it ? (IRef*)(*it + 0x70) : 0;
            IRef* prev = F<IRef*>(this, 0x38c);
            if (obj != prev) {
                if (obj) VC0_s00d6_0ce0<void>(obj, 47);
                F<IRef*>(this, 0x38c) = obj;
                if (prev) VC0_s00d6_0ce0<void>(prev, 48);
            }
        }
    }

    char* obj = F<char*>(this, 0x38c);
    if (obj) {
        Vec3f tmp;
        Vec3f* p = VC1_s00d6_0ce0<Vec3f*, Vec3f*>(obj, 23, &tmp);
        Vec3f neg;
        neg.x = -p->x;
        neg.y = -p->y;
        neg.z = -p->z;
        float r = VC1_s00d6_0ce0<float, Vec3f*>(obj, 29, &neg) + 1.0f;
        Vec3f* ctr = VC1_s00d6_0ce0<Vec3f*, float>(obj, 11, r);
        ACircle* circ = (ACircle*)((char*)this + 0x1bc);
        circ->SetAtCenter(ctr, r, &neg, 0.0f);
        circ->FUN_00afd6d0(g_c1470f1c, g_c1471064, flag);
    }

    ((PtrVec_s00d6_0ce0*)((char*)this + 0x364))->Assign(members);
    ((PtrVec_s00d6_0ce0*)((char*)this + 0x378))->Assign(others);
    SetupVignetteSpots(1);

    Vec3f a, b;
    F<City_s00d6_0ce0*>(this, 0xaf0)->FUN_00bd7f70(&a, &b);
    float dx = F<float>(this, 0x20) - a.x;
    float dy = F<float>(this, 0x24) - b.z;
    float dz = F<float>(this, 0x28) - b.x;
    if (sqrtf(dz * dz + dy * dy + dx * dx) <= g_c147b9a4)
        FUN_00d5b9f0();
    else
        FUN_00d5c8c0();
    UpdateSlotCircles();
}
