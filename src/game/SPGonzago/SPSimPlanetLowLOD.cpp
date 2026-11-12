// src/game/SPGonzago/SPSimPlanetLowLOD.cpp -- migrated from slice(s) s00c830f0, s00c7e1c0, s00c7d120, s00c829e0, s00c81ab0, s00c7ff90, s00c7f060 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSimPlanetLowLOD.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "SP/cPlanet.h"
#include "SP/cSimPlanetLowLOD.h"
#include "SP/cTerrainDistributeInfo.h"
#include "SP/cVarListSerializer.h"
#include <intrin.h>
#include "SP/cCubeSim.h"
#include "SP/cCelestialBody.h"
#include "SP/cEmpire.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cHitSphere.h"
#include "SP/cISerializableObject.h"
#include "SP/cPlanetRecord.h"
#include "SP/cPropertyList.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPTimer.h"
#include "SP/cSolarSystem.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTribe.h"

// ---- items of slice s00c7f060 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef void*  (__thiscall *TFp)(void*);
typedef void*  (__thiscall *TFpu)(void*, u32);
void*  __cdecl FUN_00b3d350(void);   // 0x00b3d350 SP::PlanetModel
void*  __cdecl FUN_00b3d440(void);   // 0x00b3d440
void   __cdecl FUN_00f929c0(int a, s32 b, s32 c, s32 d, void* e, void* f); // 0x00f929c0
s32    __fastcall FUN_00b7e3e0(void* self, void* dummy, void* a); // 0x00b7e3e0 (thiscall)
void*  __cdecl FUN_00feb9f0(void);   // 0x00feb9f0 SP::GetMissionManager
void*  __cdecl FUN_01021260(void);   // 0x01021260
u8     __cdecl FUN_01044640(void);   // 0x01044640
void   __cdecl FUN_01041c50(void* a, u32 b, int c); // 0x01041c50
void*  __cdecl FUN_00fc1fa0(int a);  // 0x00fc1fa0 SP::GetTerraformRadius
void   __cdecl FUN_00fc20e0(void* out, float a, float b); // 0x00fc20e0 TerraBlend
void*  __cdecl FUN_01049a10(void);   // 0x01049a10
void*  __cdecl FUN_00b3d430(void);   // 0x00b3d430 SP::TerraformingManager
s32    __cdecl FUN_00bbc670(void* self, void* a); // 0x00bbc670 TerraformingManager::F670 (thiscall, returns count)
float  __cdecl FUN_011e08f0(float base, float exp); // 0x011e08f0 _CIpow (x87 st0/st1)
s32    __cdecl FUN_00b8dab0(void* self); // 0x00b8dab0
void*  __cdecl FUN_00b8de30(void* self); // 0x00b8de30 BioProtectorSort::operator()
void*  __cdecl FUN_00b1fdb0(void* self); // 0x00b1fdb0 cGameNounManager::GetAvatar
void*  __cdecl FUN_00b3d2a0(void);   // 0x00b3d2a0 SP::StarManager
void*  __cdecl FUN_00885c90(void* self); // 0x00885c90
void   __cdecl FUN_00705250(void* dst, void* src, void* out); // 0x00705250 copy
void   __cdecl FUN_00f47380(void* p); // 0x00f47380 operator_delete_array
struct HtC { void DoFreeNodes(void* a, void* b); }; // FUN_007611f0 _ht_DoFreeNodes (thiscall)
struct FindC { void* Find(void* key); };            // FUN_00c7eaf0 (thiscall, ecx=container)
struct MMC { void* GetMissionList(); };             // FUN_00fedd50 (thiscall, ecx=mission manager)
struct MissionC { void* GetTargetPlanet(); };       // FUN_00970b30 (thiscall, ecx=mission)
struct NukeC { void DoNukeSubtree(void* node); };   // FUN_009a9600 DoNukeSubtree (thiscall)
struct GonzagoC { void Dtor(); };                   // FUN_00b638b0 ~cGonzagoTimer (thiscall)
struct GameDataC { void Dtor(); };                  // FUN_00b184c0 ~cGameData (thiscall)
void   __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e); // 0x00571db0 RemoveHandler
struct AMdC { u8 F24(u32 key, void* out); };  // property-list vtable slot 0x24
struct TuneC {
  float GetBullseyeTimeScale();
  float GetBullseyeMarbleMass();
  float GetBullseyeMarbleDragCoeff();
  float GetBullseyeMarbleDamping();
  float GetWaterDivergenceRate();
  float GetAtmosphereDivergenceRate();
  float GetBullseyeSteepnessPower();
  float GetFloraBullseyeRadius();
  float GetFloraBullseyeForceScalar();
};
struct TerraMgrC { u8 F670(void* a); void* F870(void* out, int i, u32 key, void* planet); }; // FUN_00bbc670 / FUN_00bbc870
// ---- items of slice s00c7f060 end

// ---- items of slice s00c7ff90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
struct tSpeciesKey {
    uint32_t mField0;                                    // +0x00
    uint32_t mField4;                                    // +0x04
    uint32_t mField8;                                    // +0x08

    tSpeciesKey& operator=(const tSpeciesKey& other)
    {
        mField0 = other.mField0;
        mField4 = other.mField4;
        mField8 = other.mField8;
        return *this;
    }
};
class cSpeciesList {
public:
    uint8_t       pad000[0xbc];                          // +0x000 .. +0x0bb
    tSpeciesKey*  mpBegin;                               // +0x0bc
    tSpeciesKey*  mpEnd;                                 // +0x0c0
};
class cPlantSpecies;
class cTerrainDistributeInfo_s00c7_ff90;
class cPlantSpeciesManager {
public:
    cPlantSpecies* GetSpeciesFromID(tSpeciesKey* pKey);   // 0x00b90410
};
class cTerrainDistributeInfo_s00c7_ff90 {
public:
    void SetInfoFromProps();                             // 0x00b2bbe0
};
class cPlanet_s00c7_ff90 {
public:
    void PushKeyBC(tSpeciesKey* pKey);                   // 0x00c73270

    uint8_t        pad000[0x13c];                        // +0x000 .. +0x13b
    cSpeciesList*  mpSpeciesList;                        // +0x13c
};
extern cPlantSpeciesManager* __cdecl           FUN_00b3d420();   // 0x00b3d420
extern cTerrainDistributeInfo_s00c7_ff90* __cdecl         FUN_00b3d3b0();   // 0x00b3d3b0
struct SpeciesKeyNode {
    tSpeciesKey key;
    int32_t value;
    SpeciesKeyNode* next;
};
struct SpeciesKeyInsertResult {
    SpeciesKeyNode* node;
    SpeciesKeyNode** bucket;
    bool inserted;
};
struct SpeciesKeyPair {
    tSpeciesKey key;
    int32_t value;
};
struct SpeciesKeyInsertTag {
    bool value;
};
namespace SP {
class cSpeciesKeyTable {
public:
    uint32_t pad0;
    SpeciesKeyNode** mpBuckets;
    uint32_t mnBuckets;

    SpeciesKeyInsertResult* Find(SpeciesKeyInsertResult* out, const tSpeciesKey* pKey); // 0x00833840
    SpeciesKeyInsertResult* Insert(SpeciesKeyInsertResult* out, const SpeciesKeyPair* pPair, SpeciesKeyInsertTag tag); // 0x00a26e10
    __declspec(noinline) int32_t* FUN_00c80110(tSpeciesKey* pKey); // 0x00c80110
};
}
namespace SP {
class cSimPlanetLowLOD_s00c7_ff90 {
public:
    cSimPlanetLowLOD_s00c7_ff90();
    void FUN_00c80180();
    void FUN_00c805b0();
    void FUN_00c80680();
    void FUN_00c80780();
    bool AddPlantSpecies(tSpeciesKey* pKey);  // 0x00c809d0 (SP::cSimPlanetLowLOD::AddPlantSpecies)
    void FUN_00c80a80();

    uint8_t            pad000[0x4c];                     // +0x000 .. +0x04b
    cPlanet_s00c7_ff90*           mpPlanet;                         // +0x04c
    uint8_t            pad050[0x2060 - 0x50];            // +0x050 .. +0x205f
    cSpeciesKeyTable   mSpeciesTable;                    // +0x2060
};
}
// ---- items of slice s00c7ff90 end

// ---- items of slice s00c81ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl SP_PlanetModel();                        // 0x00b3d350 SP::PlanetModel
void  __cdecl FUN_00b3d450();                          // 0x00b3d450
void  __cdecl FUN_00b3d420(void* a);                   // 0x00b3d420
void  __cdecl FUN_00b3d3b0(void* a);                   // 0x00b3d3b0 (also 0-arg overload)
void  __cdecl FUN_00b2bbe0();                          // 0x00b2bbe0
void* __cdecl FUN_00b90410(void* cell);                // 0x00b90410
s32   __cdecl FUN_00b8f860();                          // 0x00b8f860
u32   __cdecl FUN_00b2a750(u32 a);                     // 0x00b2a750
s32   __cdecl FUN_00401090(void* key);                 // 0x00401090 GetSetting9
void* __cdecl FUN_004df550(void* key);                 // 0x004df550 GetProfile (thiscall, ecx=key)
void  __cdecl FUN_00c732c0(void* key);                 // 0x00c732c0
void* __cdecl FUN_00c80110(void* p);                   // 0x00c80110
void* __cdecl FUN_0103de50(void* p);                   // 0x0103de50
void  __cdecl FUN_00c7ff60(void* p);                   // 0x00c7ff60 (thiscall, ecx=p)
void  __cdecl FUN_00c805b0(void* self, void* pos, void* vec, u32 a); // 0x00c805b0 (thiscall)
u8    __cdecl FUN_00c772c0(void* self, void* id);      // 0x00c772c0 (thiscall, bool)
void* __cdecl FUN_00b3d300();                          // 0x00b3d300 SP::NounManager
u32   __cdecl FUN_00936090();                          // 0x00936090 SetSeed (thiscall)
u32   __cdecl FUN_00a68fb0(void* self, u32 n);         // 0x00a68fb0 RandomUint32Uniform
double __cdecl FUN_a68fd0(void* self);                 // 0x00a68fd0 RandomDoubleUniform
void __fastcall FUN_00c81f40(void* self, void* /*edx*/, void* arg);
void __fastcall FUN_00c821b0(void* self, void* /*edx*/, void* a, void* b, int c, void* d);
// ---- items of slice s00c81ab0 end

// ---- items of slice s00c829e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cPlanet_s00c8_29e0;
}
namespace SP {
struct tPlanetKey {
    int32_t mIndex;                                      // +0x00
};
}
namespace SP {
struct tPlanetEntry {
    uint8_t pad000[0xa0];                                // +0x000 .. +0x09f
    bool    mFieldA0;                                    // +0x0a0
    bool    mFieldA1;                                    // +0x0a1
};
}
namespace SP {
class cPlanetEntryTable {
public:
    tPlanetEntry* FUN_00ba4e60(tPlanetKey* pKey);        // 0x00ba4e60
};
}
namespace SP {
extern void* __cdecl GetUniverseContext();               // 0x01021080
}
namespace SP {
extern volatile uint32_t gStubSink;                      // keeps stub calls alive
}
namespace SP {
class cSimPlanetLowLOD_s00c8_29e0 {
public:
    void FUN_00c829e0();  // 0x00c829e0 (SP::cSimPlanetLowLOD::FUN_00c829e0)
    __declspec(noinline) void FUN_00c82d50(cPlanet_s00c8_29e0* pPlanet, bool bValue);
    void FUN_00c82ea0();  // 0x00c82ea0 (SP::cSimPlanetLowLOD::FUN_00c82ea0)
    void FUN_00c82f00();
    void FUN_00c82f80();  // 0x00c82f80 (SP::cSimPlanetLowLOD::FUN_00c82f80)
    void FUN_00c83050(cPlanet_s00c8_29e0* pOld, cPlanet_s00c8_29e0* pNew, bool bValue);  // 0x00c83050 (SP::cSimPlanetLowLOD::FUN_00c83050)
    void FUN_00c83090(tPlanetKey key, bool bValue);  // 0x00c83090 (SP::cSimPlanetLowLOD::FUN_00c83090)
    bool FUN_00c830b0(tPlanetKey key);  // 0x00c830b0 (SP::cSimPlanetLowLOD::FUN_00c830b0)
    void FUN_00c830d0(tPlanetKey key, bool bValue);  // 0x00c830d0 (SP::cSimPlanetLowLOD::FUN_00c830d0)
    void UpdateBackgroundPlanet(cPlanet_s00c8_29e0* pPlanet, bool bValue); // 0x00c817e0

    uint8_t            pad000[0x4c];                     // +0x0000 .. +0x004b
    cPlanet_s00c8_29e0*           mpPlanet;                         // +0x004c
    uint8_t            pad050[0x11c0 - 0x50];            // +0x0050 .. +0x11bf
    cPlanetEntryTable  mEntryTable;                      // +0x11c0
};
}
// ---- items of slice s00c829e0 end

// ---- items of slice s00c7d120 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTargetList {
    void** vptr;            // +0x000
    void*  mp04;            // +0x004  raw block ([p-4] holds an allocation count)
    char   pad08[0x10];     // +0x008..+0x017
    u32    m18;             // +0x018
    char   pad1c[0x08];     // +0x01c..+0x023
    u32    m24;             // +0x024
    char   pad28[0x10];     // +0x028..+0x037
    u32*   m38;             // +0x038
    u32*   m3c;             // +0x03c
    u32*   m40;             // +0x040
    char   pad44[0x08];     // +0x044..+0x04b
    u8     m4c;             // +0x04c
    char   pad4d[0x03];     // +0x04d..+0x04f
    u32*   m50;             // +0x050
    u32*   m54;             // +0x054
    u32*   m58;             // +0x058
    char   pad5c[0x08];     // +0x05c..+0x063
    u8     m64;             // +0x064
    char   pad65[0x03];     // +0x065..+0x067
    void** m68;             // +0x068
    void** m6c;             // +0x06c
    void** m70;             // +0x070
    char   pad74[0x08];     // +0x074..+0x07b
    u32    m7c;             // +0x07c
    char   m80[0x200];      // +0x080 inline storage for m68
    void** m280;            // +0x280
    void** m284;            // +0x284
    void** m288;            // +0x288
    char   pad28c[0x08];    // +0x28c..+0x293
    u32    m294;            // +0x294
    char   m298[0x200];     // +0x298 inline storage for m280
    float  m498;            // +0x498
    void*  m49c;            // +0x49c

    cTargetList();                          // 0x00c7d700
    ~cTargetList();                         // 0x00c7d650
    bool Has(u32 key);                      // 0x00c7d6d0
    void* FindTarget(void* ctx);            // 0x00c7d7a0
    void* FindTargetThunk();                // 0x00c7d930
    bool HasKey(void* obj);                 // 0x00c7da70
    void ClearAll();                        // 0x00c7dba0
    void ClearOne();                        // 0x00c7dc20
    bool UpdateTarget(void* target);        // 0x00c7d240
    void Update();                          // 0x00c7dcb0
    bool Write(void* stream);               // 0x00c7dfe0
    bool Read(void* stream);                // 0x00c7e0a0
    void* Get(int* idx);                    // 0x00c7e1a0
};
struct cVarListSerializer {
    char m[0xa14];
    cVarListSerializer* Construct(void* src, void* generic, unsigned id);   // 0x00692f90
    bool Serialize(void* stream);                                          // 0x00692900
    bool Serialize2(void* stream);                                         // 0x00693e10
};
// ---- items of slice s00c7d120 end

// ---- items of slice s00c7e1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float    g_01694c08;
extern uint32_t g_01694c0c;
extern float    g_01579a08;
extern uint32_t g_01579a10, g_01579a14;
struct CS;
void*   GetSetting9_00401090();
void*   GetUniverseContext_01021080();
void*   GetActivePlanet_01021260();
void*   TerraformingManager_00b3d430();
void*   GetMissionManager_00feb9f0();
int     WrapCubeFace_00684ca0(int, int*, int*, int*, int, int);
float*  FUN_00684c50_00(float*, int, int*);
void    ReadInt32_0093a780(void*, void*, int, int);
int     ResourceMan_opne_005f78f0(int*, int*);
void    RemoveHandler_00571db0(void*, void*, void*, void*, void*);
void*   operator_new_array_011e073e(void*, int, int);
void __stdcall vector_ctor_iterator_00401930(void*, unsigned, int, void*);
float   GetTerraformRadius_00fc1fa0(int);
bool     __fastcall cSPTimer_IsRunning_00feba90(void*);
uint64_t __fastcall cSPTimer_GetElapsedTime_00bc3190(void*);
float    __fastcall cTerraformTuning_GetFloraBullseyeRadius_01049c90(void*);
uint32_t __fastcall cSPMission_GetMissionID_01030e10(void*);
void*    __fastcall cSPMission_GetTargetPlanet_00970b30(void*);
void*    __fastcall cSPMissionManager_GetMissionList_00fedd50(void*);
struct SpeciesMgr  { void* GetProfile(int* key); };
struct TerraMgrObj { int F670(int); bool FUN_00bbe370(int); };
struct Ser {
    uint8_t buf[0xa14];
    void ctor(void*, void*, int);   // 0x692f90
    char Serialize(void*);          // 0x692900
    char Read(void*);               // 0x693e10
};
struct CubeCell {                       // 0x54 bytes
    uint32_t pad00[8];                  // 0x00
    uint8_t  m1F9C;                     // 0x20  (absolute 0x1f9c in cell #0x5f)
    uint8_t  pad21[0x33];               // 0x21..0x53
    void FUN_00c7dfe0(void* s);         // 0xc7dfe0
    void FUN_00c7e0a0(void* s);         // 0xc7e0a0
};
struct CubeElem {                       // 0x54 bytes (face grid element, ctor)
    uint32_t m00;                       // 0x00
    uint32_t mVec0[0x30 / 4];           // 0x04
    uint32_t mVec1[0x20 / 4];           // 0x34
};
struct CS {
    union {
        struct {
            uint32_t pad00[0x18 / 4];   // 0x00
            void*    mp18;              // 0x18
            uint32_t pad1C[4];          // 0x1c
            void*    mp2C;              // 0x2c
            uint32_t pad30;             // 0x30
            void*    mp34;              // 0x34
            void*    mp38;              // 0x38
            void*    mp3C;              // 0x3c
            void*    mp40;              // 0x40
            void*    mp44;              // 0x44
            void*    mp48;              // 0x48
            void*    mp4C;              // 0x4c
            CubeCell mCells[0x60];      // 0x50
            uint32_t pad1FD0;           // 0x1fd0
            float    m1FD4;             // 0x1fd4
            float    m1FD8;             // 0x1fd8
            uint32_t pad1FDC[5];        // 0x1fdc
            uint8_t  timer1FF0[0x20];   // 0x1ff0
            uint8_t  timer2010[0x20];   // 0x2010
            uint8_t  m2030;             // 0x2030
            uint8_t  m2031;             // 0x2031
            uint8_t  pad2032[6];        // 0x2032
            uint8_t  timer2038[0x28];   // 0x2038
        } h;
        CubeElem mElems[0x60];          // 0x00 (overlaps h)
    };

    void*     ctor_00c7ea70();
    void      FUN_00c7ead0(int* out);
    void      FUN_00c7e280(void* a);
    void      FUN_00c7e2f0(char b);
    void      FUN_00c7e5d0(int a2, int a3, int a4, int a5, void* cb, int a7, int a8);
    void      FUN_00c7e780(int a2, void* cb, int a4, int a5);
    bool      FUN_00c7e8f0(void* s);
    bool      FUN_00c7e950(void* s);
    bool      FUN_00c7e9b0(int msg, int unk);
    CubeElem* FUN_00c7eaf0(float* p);
    void      FUN_00c7ecb0();
    void      FUN_00c7ed00(int* a, int* b);
    bool      FUN_00c7ee50();
};
// ---- items of slice s00c7e1c0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __stdcall FUN_00c7e530(int a, int b, int p, int d, int* e);  // 0x00c7e530 (stays in the slice: not this object's)

// ---- items of slice s00c830f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_ColonyReason[];                                // 0x01694bac
extern bool g_TerraformDisabled;                             // 0x016e06dc
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);                                   // 0x00f473a0
void operator delete[](void* p);                                                 // 0x00f47380
struct Property {
    uint32_t pad00[4];
    short    pad10;
    short    mnType;            // +0x12 (0xd = float)
    float* GetFloat();          // 0x0041ea70
};
struct PropertyList {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
PropertyList** GetTerraformTuning();                         // 0x01049a10
struct IMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void PostMSG(uint32_t id, int a, int b);             // +0x14
    virtual void SendMSG(uint32_t id, int a, int b, int c);      // +0x18
};
IMessageServer* MessageServer();                             // 0x0067dcc0
struct IVisualEffect {
    virtual int AddRef();
    virtual int Release();                                   // +0x04
    virtual bool Start(int flags);                           // +0x08
};
struct IEffectsManager {
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
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect** dst);  // +0x2c
};
IEffectsManager* EffectsManager();                           // 0x0067ddd0
template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    // releases the current object and hands out the slot for an out parameter
    T** reset_out()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
struct IAudioSystem {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual int GetRecorderState();                          // +0x20
};
IAudioSystem* GetAudioSystemAT();                            // 0x00a206f0 (EA::Audio::GetSystemAT)
inline int GetRecorderState()
{
    IAudioSystem* a = GetAudioSystemAT();
    return a ? a->GetRecorderState() : 0;
}
void PlayTerraformAudio(uint32_t id, int recorderState);    // 0x00435ed0 (labelled KillSetiEffects)
struct cEmpire_s00c8_30f0 {
    uint32_t pad00[0x84 / 4];
    uint32_t mPoliticalID;      // +0x84
};
struct cPlanetRecord_s00c8_30f0 {
    struct Elem12 { uint32_t a, b, c; };
    uint32_t pad00[0x2c / 4];
    uint32_t mFlags;            // +0x2c
    uint32_t pad30[(0xd0 - 0x30) / 4];
    Elem12*  mpPlantsBegin;     // +0xd0
    Elem12*  mpPlantsEnd;       // +0xd4
    uint32_t GetID();           // 0x00ce6950
    uint32_t PlantCount() { return (uint32_t)(mpPlantsEnd - mpPlantsBegin); }
};
void*          GetUniverseContext();                         // 0x01021080
struct cPlanet_s00c8_30f0* GetActivePlanet_s00c8_30f0();                           // 0x01021260
cPlanetRecord_s00c8_30f0* GetActivePlanetRecord();                      // 0x010212a0
cEmpire_s00c8_30f0*       GetPlayerEmpire();                            // 0x01021300
uint32_t       GetPlayerEmpireID();                          // 0x01021090
int            GetCurrentGameMode();                         // 0x00b5b800
struct cRelationshipManager_s00c8_30f0 {
    float RecordEvent(uint32_t politicalID, uint32_t otherID, uint32_t eventID, float scale);  // 0x00d06240
};
cRelationshipManager_s00c8_30f0* RelationshipManager();                 // 0x00b3d2c0
struct cSPUIEventLog {
    void PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);   // 0x00dd8640
};
cSPUIEventLog* EventLog();                                   // 0x00b3d3e0
struct cTutorial {
    void TerraformLevelChanged(int level, int oldLevel);     // 0x010681e0
    void Trigger(uint32_t id);                               // 0x0106dcd0
};
cTutorial* GetTutorial();                                    // 0x010666a0
struct cTribe_s00c8_30f0 { void FUN_00fe5430(int a, int b); };          // 0x00fe5430
struct cSpaceGame {
    void    FUN_01005180(int a);                             // 0x01005180
    cTribe_s00c8_30f0* GetPlayerTribe();                                // 0x00bfc5f0
};
cSpaceGame* SpaceGameGet();                                  // 0x01002bd0
struct Z3 { int a, b, c; Z3() : a(0), b(0), c(0) {} };
void FUN_00e39ab0(uint32_t key, cEmpire_s00c8_30f0* emp, Z3* d, Z3* c, uint32_t id, int zero, Z3* b, Z3* a);  // 0x00e39ab0
struct cTimeline { void FUN_00acd4a0(); };                   // 0x00acd4a0
cTimeline* FUN_00b3d480();                                   // 0x00b3d480
struct ByteVector {                                          // eastl::vector, sp_vector_allocator
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    const char* mpAllocName;
    ~ByteVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
};
struct ResourceKey;
struct cPlanet_s00c8_30f0 {
    uint32_t pad00[0x13c / 4];
    cPlanetRecord_s00c8_30f0* mpPlanetRecord;   // +0x13c
    ResourceKey* FUN_00c713e0();     // 0x00c713e0
    int      GetTScore();             // 0x00c70880
    float    GetAtmosphereScore();    // 0x00c709d0
    float    GetTemperatureScore();   // 0x00c70a20
    bool     FUN_00c70a70();          // 0x00c70a70
    void     FUN_00c70aa0(float f);   // 0x00c70aa0
    void     SetNeedsReset(int b);    // 0x00c70de0
    int      GetTechLevel();          // 0x00c70e00
    void     SetEcosystemStage(int s);// 0x00c71550
    float    GetWaterScore();         // 0x00c71d30
    cEmpire_s00c8_30f0* GetOwner();              // 0x00c71e30
    ByteVector GetCities();           // 0x00c73520
};
struct cTerrainEntry {
    uint32_t pad00[0xa0 / 4];
    signed char mInitialLevel;        // +0xa0
    signed char mInitialPlants;       // +0xa1
};
struct cTerrainEntryMap {
    cTerrainEntry& operator[](const uint32_t& key);   // 0x00ba4e60
};
struct cTerrainSphere_s00c8_30f0 {
    uint32_t pad00[0x11c0 / 4];
    cTerrainEntryMap mEntries;        // +0x11c0
    void SetTerraformLevel(uint32_t planetID, int level);   // 0x00c83090
    bool HasMusic(uint32_t id);       // 0x00c772c0
    void PlayMusic(uint32_t id);      // 0x00c77bf0
};
struct cGameData_s00c8_30f0;
struct ILocatorSub {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void v14();
    virtual void SetTerraformState(float f, uint32_t empireID, int a, void* reason, int b);   // +0x18
};
struct cCreatureLike {
    uint32_t pad00[0x120 / 4];
    ILocatorSub mSub;                 // +0x120
    uint32_t pad124[(0x158 - 0x124) / 4];
    float    mF158;                   // +0x158
};
struct cGameData_s00c8_30f0 {
    virtual int AddRef();
    virtual int Release();            // +0x04
virtual void v08();
virtual void* v0c(uint32_t type);
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
    virtual cCreatureLike* AsCreature();   // +0xac
    void FUN_00bdc050();              // 0x00bdc050
};
struct GDIter {
    cGameData_s00c8_30f0** mp;
    __forceinline GDIter(cGameData_s00c8_30f0** p) : mp(p) {}
    __forceinline GDIter(const GDIter& x) : mp(x.mp) {}
};
struct false_type {};
GDIter FUN_00829110(GDIter first, GDIter last, GDIter dest, false_type);   // 0x00829110 uninitialized_copy (AddRefs)
struct sp_allocator { const char* mpName; };
struct GameDataPtrVector {
    cGameData_s00c8_30f0** mpBegin;
    cGameData_s00c8_30f0** mpEnd;
    cGameData_s00c8_30f0** mpCapacity;
    sp_allocator mAllocator;

    void DoInit(int n, const sp_allocator& a);   // 0x00b93c60 (VectorBase(n, allocator), out of line)

    __forceinline GameDataPtrVector(const GameDataPtrVector& x, int)
    {
        DoInit((int)(x.mpEnd - x.mpBegin), x.mAllocator);
        mpEnd = FUN_00829110(GDIter(x.mpBegin), GDIter(x.mpEnd), GDIter(mpBegin), false_type()).mp;
    }
    __forceinline GameDataPtrVector(const GameDataPtrVector& x)
    {
        int n = (int)(x.mpEnd - x.mpBegin);
        mpBegin = n ? (cGameData_s00c8_30f0**)operator new(n * sizeof(cGameData_s00c8_30f0*), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1) : 0;
        mpEnd = FUN_00829110(GDIter(x.mpBegin), GDIter(x.mpEnd), GDIter(mpBegin), false_type()).mp;
        mpCapacity = mpBegin + n;
    }
    __forceinline ~GameDataPtrVector()
    {
        for (cGameData_s00c8_30f0** p = mpBegin; p < mpEnd; ++p)
            if (*p) (*p)->Release();
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct tGameDataVector_s00c8_30f0 {
    bool              mbDirty;   // +0x0
    GameDataPtrVector mData;     // +0x4
};
void FUN_00cd7d10();   // 0x00cd7d10
void FUN_00d3d420();   // 0x00d3d420
void FUN_00accbb0();   // 0x00accbb0
void FUN_00acdff0();   // 0x00acdff0
void FUN_00b1e500();   // 0x00b1e500
struct cGameNounManager_s00c8_30f0 {
    tGameDataVector_s00c8_30f0* GetGameDataVector(void (*create)(), void (*f2)(), void (*filter)(), void (*f4)(),
                                       uint32_t typeID);   // 0x00b21340
    void RemoveNoun(cGameData_s00c8_30f0* noun);                       // 0x00b225d0
    cGameData_s00c8_30f0* CreateNoun(uint32_t typeID);                 // 0x00b20c60
    void RemoveNounsOfType(uint32_t typeID);                // 0x00b22650
    void FUN_00b25ee0();                                    // 0x00b25ee0
    cTerrainSphere_s00c8_30f0* GetCurrentTerrainSphere();              // 0x00f67d90
};
cGameNounManager_s00c8_30f0* NounManager();                            // 0x00b3d300
struct cTerraformingManager {
    int  GetTerraformLevel(cPlanetRecord_s00c8_30f0* record);          // 0x00bbc670
    bool DestroyEcosystemLevel(int level, cPlanet_s00c8_30f0* planet); // 0x00bbcb90
    void UpdatePlanetScores(cPlanet_s00c8_30f0* planet, float atmosphere, float temperature, bool b);  // 0x00bbcf00
    void FUN_00bbe740(cPlanet_s00c8_30f0* planet);                     // 0x00bbe740
    void FUN_00bc1450(cPlanet_s00c8_30f0* planet);                     // 0x00bc1450
};
cTerraformingManager* TerraformingManager();                // 0x00b3d430
struct cSPTimer_s00c8_30f0 {
    uint32_t data[0x40 / 4];
    void     Restart();             // 0x00bc3130
    void     Stop();                // 0x00bc3170
    uint64_t GetElapsedTime();      // 0x00bc3190
    bool     IsRunning();           // 0x00feba90
};
struct rbtree_node;
struct ExtinctionMap {
    uint32_t     mCompare;          // +0x00
    rbtree_node* mpNodeRight;       // +0x04 (anchor)
    rbtree_node* mpNodeLeft;        // +0x08
    rbtree_node* mpNodeParent;      // +0x0c
    char         mColor;            // +0x10
    uint32_t     mnSize;            // +0x14

    void DoNukeSubtree(rbtree_node* p);   // 0x009a9600
    void clear()
    {
        DoNukeSubtree(mpNodeParent);
        mpNodeRight = (rbtree_node*)&mpNodeRight;
        mpNodeLeft = (rbtree_node*)&mpNodeRight;
        mpNodeParent = 0;
        mColor = 0;
        mnSize = 0;
    }
};
__forceinline cTerrainEntry& TerrainEntry(cPlanetRecord_s00c8_30f0* record)
{
    uint32_t planetID = record->GetID();
    cTerrainSphere_s00c8_30f0* sphere = NounManager()->GetCurrentTerrainSphere();
    return sphere->mEntries[planetID];
}
namespace SP {
struct cSimPlanetLowLOD_s00c8_30f0 { private:
public:
    uint32_t pad000[0x4c / 4];
    cPlanet_s00c8_30f0* mpPlanet;                   // +0x4c
    uint32_t pad050[(0x1fd0 - 0x50) / 4];
    bool     mbScoresDirty;              // +0x1fd0
    uint8_t  pad1fd1[3];
    float    mF1fd4;                     // +0x1fd4
    float    mF1fd8;                     // +0x1fd8
    float    mLastAtmosphere;            // +0x1fdc
    float    mLastTemperature;           // +0x1fe0
    float    mLastWater;                 // +0x1fe4
    int      mLastTerraformLevel;        // +0x1fe8
    uint32_t pad1fec;
    cSPTimer_s00c8_30f0 mCollapseTimer;             // +0x1ff0
    bool     mbFinishPending;            // +0x2030
    bool     mb2031;                     // +0x2031
    uint8_t  pad2032[0x2058 - 0x2032];
    uint8_t  mbPlanetKeyLoaded_2058;     // +0x2058
    uint8_t  pad2059[0x20a0 - 0x2059];
    ExtinctionMap mExtinctionMap;        // +0x20a0

    void FUN_00c7f060();                 // 0x00c7f060
    void FUN_00c82870();                 // 0x00c82870
    bool FUN_00c7ee50();                 // 0x00c7ee50
    void FUN_00c7fab0(int arg);          // 0x00c7fab0

    void UpdateTerraforming(int arg);  // 0x00c830f0 (SP::cSimPlanetLowLOD::UpdateTerraforming)
};  // namespace SP
}
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
// ---- items of slice s00c830f0 end

// @ 0x00c7dfe0
bool cTargetList::Write(void* stream)
{
    cVarListSerializer ser1;
    cVarListSerializer ser2;
    ser1.Construct(this, (void*)0x1579c58, 0x1a80d26u);
    bool ok = ser1.Serialize(stream);
    if (ok) {
        char* p = (char*)this + 0x04;
        for (int i = 0; i < 3; ++i) {
            ser2.Construct(p, (void*)0x1579ae8, 0x1a80d26u);
            ser2.Serialize(stream);
            p += 0x10;
        }
        p = (char*)this + 0x34;
        for (int i = 0; i < 2; ++i) {
            ser2.Construct(p, (void*)0x1579ba0, 0x1a80d26u);
            ser2.Serialize(stream);
            p += 0x10;
        }
    }
    return ok;
}

// @ 0x00c7e0a0
bool cTargetList::Read(void* stream)
{
    cVarListSerializer ser1;
    cVarListSerializer ser2;
    ser1.Construct(this, (void*)0x1579c58, 0x1a80d26u);
    bool ok = ser1.Serialize2(stream);
    if (ok) {
        char* p = (char*)this + 0x04;
        for (int i = 0; i < 3; ++i) {
            ser2.Construct(p, (void*)0x1579ae8, 0x1a80d26u);
            ser2.Serialize2(stream);
            p += 0x10;
        }
        p = (char*)this + 0x34;
        for (int i = 0; i < 2; ++i) {
            ser2.Construct(p, (void*)0x1579ba0, 0x1a80d26u);
            ser2.Serialize2(stream);
            p += 0x10;
        }
    }
    return ok;
}

// @ 0x00c7e1c0
bool __stdcall FUN_00c7e1c0(int* a, int* b)
{
    b[0] = a[0]; b[1] = a[1]; b[2] = a[2]; b[0] -= 1;
    b[3] = a[0]; b[4] = a[1]; b[5] = a[2]; b[3] += 1;
    b[6] = a[0]; b[7] = a[1]; b[8] = a[2]; b[7] -= 1;
    b[9] = a[0]; b[10] = a[1]; b[11] = a[2]; b[10] += 1;
    if (a[0] > 0 && a[0] < 3 && a[1] > 0 && a[1] < 3) return false;
    int* p = b + 2;
    for (int i = 4; i != 0; --i, p += 3) {
        int t = *p;
        WrapCubeFace_00684ca0(4, &t, p - 2, p - 1, 0, 0);
        *p = t;
    }
    return true;
}

// @ 0x00c7e370
int __stdcall FUN_00c7e370(int a1, int* key, int p3, int p4, int p5, int p6, int p7)
{
    (void)a1;
    void* prof = ((SpeciesMgr*)GetSetting9_00401090())->GetProfile(key);
    if (prof == 0) return 0;
    if (*(int*)((char*)prof + 0x608) == 0) {
        if (*(int*)((char*)prof + 0x60c) != 0) {
            int* q = (int*)(p4 + 0x10);
            for (int i = 0; i < 3; ++i, q += 4) {
                if (*(int*)(p3 + 0x10 + i * 0x10) != 0) return 1;
                if (q[0] != 0) return 1;
                if (*(int*)(p6 + 0x10 + i * 0x10) != 0) return 1;
                if (*(int*)(p7 + 0x10 + i * 0x10) != 0) return 1;
                if (*(int*)(p5 + 0x10 + i * 0x10) != 0) return 1;
            }
        }
    } else {
        if (*(int*)(p3 + 0x40) != 0) {
            if (*(int*)(p3 + 0x34) != key[0] || *(int*)(p3 + 0x38) != key[1] ||
                *(int*)(p3 + 0x3c) != key[2]) return 1;
        }
        if (*(int*)(p4 + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(p4 + 0x34), key)) return 1;
        if (*(int*)(p6 + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(p6 + 0x34), key)) return 1;
        if (*(int*)(p7 + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(p7 + 0x34), key)) return 1;
        if (*(int*)(p5 + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(p5 + 0x34), key)) return 1;
    }
    return 0;
}

// @ 0x00c7e5d0
void CS::FUN_00c7e5d0(int a2, int a3, int a4, int a5, void* cb, int a7, int a8)
{
    (void)a7; (void)a8;
    int i1 = a3, i2 = a4, i3 = a5;

    int local_2c = i2 + 1;
    int p4 = i1, p5 = i3;
    WrapCubeFace_00684ca0(4, &p4, &local_2c, &p5, 0, 0);
    CubeCell* local_10 = &h.mCells[local_2c + (p5 + p4 * 4) * 4];

    int p3 = i2 - 1; p4 = i1; p5 = i3;
    WrapCubeFace_00684ca0(4, &p4, &p3, &p5, 0, 0);
    CubeCell* local_c = &h.mCells[p3 + (p5 + p4 * 4) * 4];

    p5 = i3 + 1; p3 = i2; p4 = i1;
    WrapCubeFace_00684ca0(4, &p4, &p3, &p5, 0, 0);
    CubeCell* local_8 = &h.mCells[p3 + (p5 + p4 * 4) * 4];

    p5 = i3 - 1; p3 = i2; p4 = i1;
    WrapCubeFace_00684ca0(4, &p4, &p3, &p5, 0, 0);
    CubeCell* local_4 = &h.mCells[p3 + (p5 + p4 * 4) * 4];

    (void)local_10; (void)local_c; (void)local_8; (void)local_4;

    int coord[3];
    coord[0] = i2; coord[1] = i3; coord[2] = i1;
    float local_1c[3];
    float* res = FUN_00684c50_00(local_1c, 4, coord);
    ((void(__thiscall*)(void*, int, void*))cb)((char*)this + a7, a2, (void*)res);
}

// @ 0x00c7e780
void CS::FUN_00c7e780(int a2, void* cb, int a4, int a5)
{
    CubeCell* base = &h.mCells[5];          // this + 0x1f4
    for (int i4 = 0; i4 < 6; ++i4) {
        int n30 = 1;
        CubeCell* i3 = base;
        do {
            CubeCell* i1 = i3;
            int i5 = 1;
            do {
                i1 = i3;
                int coord[3];
                coord[0] = i5; coord[1] = n30; coord[2] = i4;
                float out[3];
                float* res = FUN_00684c50_00(out, 4, coord);
                ((void(__thiscall*)(void*, int, void*))cb)((char*)this + a4, a2, (void*)res);
                ++i5;
                i3 = i1 + 1;
            } while (i5 < 3);
            ++n30;
            i3 = i1 + 3;                    // iVar1 + 0xfc
        } while (n30 < 3);
        int k = 1;
        do {
            FUN_00c7e5d0(a2, i4, 0, k, cb, a4, a5);
            FUN_00c7e5d0(a2, i4, 3, k, cb, a4, a5);
            ++k;
        } while (k < 3);
        k = 0;
        do {
            FUN_00c7e5d0(a2, i4, k, 0, cb, a4, a5);
            FUN_00c7e5d0(a2, i4, k, 3, cb, a4, a5);
            ++k;
        } while (k < 4);
        base += 0x540 / 0x54;               // +16 cells
    }
}

// @ 0x00c7e8f0
bool CS::FUN_00c7e8f0(void* s)
{
    for (int i = 0x60; i != 0; --i)
        h.mCells[0x60 - i].FUN_00c7dfe0(s);
    Ser ser;
    ser.ctor(this, (void*)0x1579cd0, 0x1a80d26);
    return ser.Serialize(s) != 0;
}

// @ 0x00c7e950
bool CS::FUN_00c7e950(void* s)
{
    for (int i = 0x60; i != 0; --i)
        h.mCells[0x60 - i].FUN_00c7e0a0(s);
    Ser ser;
    ser.ctor(this, (void*)0x1579cd0, 0x1a80d26);
    return ser.Read(s) != 0;
}

// @ 0x00c7e9b0
bool CS::FUN_00c7e9b0(int msg, int unk)
{
    (void)unk;
    if (msg != 0x44448ed) return false;
    if (GetUniverseContext_01021080() == 0) {
        if (h.mp18 == GetActivePlanet_01021260())
            h.mCells[0x5f].m1F9C = 1;
    }
    return true;
}

// @ 0x00c7e9f0
bool __cdecl FUN_00c7e9f0(void* io, void** out)
{
    void* a = ((void*(__thiscall*)(void*))(*(void***)io)[0x20 / 4])(io);
    void* b = ((void*(__thiscall*)(void*))(*(void***)a)[0x18 / 4])(a);
    int x;
    ReadInt32_0093a780(b, &x, 1, 0);
    *out = (void*)x;
    return true;
}

// @ 0x00c7ea30
void __cdecl FUN_00c7ea30(int* a, int* b, int* out)
{
    while (a != b) {
        if (out != 0) { out[0] = a[0]; out[1] = a[1]; out[2] = a[2]; out[3] = a[3]; }
        a += 4;
        out += 4;
    }
}

// @ 0x00c7ea70
void* CS::ctor_00c7ea70()
{
    CubeElem* p = mElems;
    int n = 0x5f;
    do {
        p->m00 = 0;
        vector_ctor_iterator_00401930(&p->mVec0, 0x10, 3, (void*)0xfaed90);
        vector_ctor_iterator_00401930(&p->mVec1, 0x10, 2, (void*)0xfaed90);
        p += 1;
    } while (--n >= 0);
    operator_new_array_011e073e(this, 0, 0x1f80);
    return this;
}

// @ 0x00c7ead0
void CS::FUN_00c7ead0(int* out)
{
    out[2] = 0; out[0] = 0; out[1] = 0; out[3] = (int)this;
}

// @ 0x00c7eaf0
CubeElem* CS::FUN_00c7eaf0(float* p)
{
    float x = p[0];
    volatile float ax = (float)fabs((double)x);
    float y = p[1];
    volatile float ay = (float)fabs((double)y);
    float z = p[2];
    volatile float az = (float)fabs((double)z);
    int i7, i8, i9;
    if (az < ax || az < ay) {
        if (ay < ax) {
            float t = y / x;
            t = (t + 1.0f) * 2.0f;
            i7 = (int)t;
            t = z / ax;
            t = (t + 1.0f) * 2.0f;
            i8 = (int)t;
            i9 = (x < 0.0f) ? 3 : 2;
        } else {
            float t = z / y;
            t = (t + 1.0f) * 2.0f;
            i7 = (int)t;
            t = x / ay;
            t = (t + 1.0f) * 2.0f;
            i8 = (int)t;
            i9 = (y < 0.0f) ? 5 : 4;
        }
    } else {
        float t = x / z;
        t = (t + 1.0f) * 2.0f;
        i7 = (int)t;
        t = y / az;
        t = (t + 1.0f) * 2.0f;
        i8 = (int)t;
        i9 = (z < 0.0f) ? 1 : 0;
    }
    if (i7 == 4) i7 = 3;
    if (i8 == 4) i8 = 3;
    return &mElems[i7 + (i8 + i9 * 4) * 4];
}

// @ 0x00c7ecb0
void CS::FUN_00c7ecb0()
{
    void* p = h.mp38;
    if (p != 0) {
        void* a2 = h.mp3C;
        void* a3 = h.mp40;
        void* a4 = h.mp44;
        void* a5 = h.mp48;
        h.mp38 = 0;
        RemoveHandler_00571db0(p, a2, a3, a4, a5);
    }
    h.mp4C = (void*)0;
    if (h.mp2C != (void*)0) {
        void* q = h.mp2C;
        h.mp2C = (void*)0;
        ((void(__thiscall*)(void*))(*(void***)q)[1])(q);
    }
}

// @ 0x00c7ed00
void CS::FUN_00c7ed00(int* a, int* b)
{
    int local[6];
    local[0] = a[0]; local[1] = a[1]; local[2] = a[2];
    local[3] = b[0]; local[4] = b[1]; local[5] = b[2];
    FUN_00c7e780(0, (void*)FUN_00c7e530, 0, (int)local);
}

// @ 0x00c7ed50
void __stdcall FUN_00c7ed50(int a1, int a2, int p, int a4, int* e)
{
    (void)a1; (void)a2; (void)a4;
    int n0 = (e[1] - e[0]) / 0xc;
    int n1 = (e[0xb] - e[0xa]) / 0xc;
    for (int k = 0; k < 3; ++k) {
        int* q = (int*)(p + 4 + k * 0x10);
        for (int i = 0; i < n0; ++i) {
            int* r = (int*)(e[0] + i * 0xc);
            if (q[0] == r[0] && q[1] == r[1] && q[2] == r[2]) {
                int* s = (int*)(e[5] + i * 0xc);
                q[0] = s[0]; q[1] = s[1]; q[2] = s[2];
            }
        }
    }
    for (int k = 0; k < 2; ++k) {
        int* q = (int*)(p + 0x34 + k * 0x10);
        for (int i = 0; i < n1; ++i) {
            int* r = (int*)(e[0xa] + i * 0xc);
            if (q[0] == r[0] && q[1] == r[1] && q[2] == r[2]) {
                int* s = (int*)(e[0xf] + i * 0xc);
                q[0] = s[0]; q[1] = s[1]; q[2] = s[2];
            }
        }
    }
}

// @ 0x00c7ee50
bool CS::FUN_00c7ee50()
{
    if (h.m2031 == 0) {
        if (cSPTimer_IsRunning_00feba90(h.timer2038)) {
            uint64_t t = cSPTimer_GetElapsedTime_00bc3190(h.timer2038);
            uint64_t limit = ((uint64_t)g_01579a14 << 32) | g_01579a10;
            if (t > limit) h.m2031 = 1;
        }
        return false;
    }

    float flora = cTerraformTuning_GetFloraBullseyeRadius_01049c90(FUN_01049a10());
    if ((g_01694c0c & 1) == 0) {
        float half = flora * 0.5f;
        float cap = 0.02f;
        g_01694c0c |= 1;
        g_01694c08 = (cap <= half) ? cap : half;
    }

    int obj = *(int*)((char*)h.mp4C + 0x13c);
    float radius = (float)((TerraMgrObj*)TerraformingManager_00b3d430())->F670(obj);

    if (radius == 0.0f) {
        float bx = *(float*)((char*)obj + 0xb0);
        if (fabsf(bx) < g_01694c08 || fabsf(bx - 1.0f) < g_01694c08) {
            if (g_01694c08 <= fabsf(*(float*)((char*)obj + 0xb4)) &&
                g_01694c08 <= fabsf(*(float*)((char*)obj + 0xb4) - 1.0f))
                return false;
            return true;
        }
    } else {
        if (((TerraMgrObj*)TerraformingManager_00b3d430())->FUN_00bbe370(obj)) {
            void* vec = cSPMissionManager_GetMissionList_00fedd50(GetMissionManager_00feb9f0());
            int* it = *(int**)vec;
            int* end = ((int**)vec)[1];
            for (; it != end; ++it) {
                void* mission = (void*)*it;
                if (mission == 0) continue;
                if (cSPMission_GetMissionID_01030e10(mission) != 0x311cc10f) continue;
                if (cSPMission_GetTargetPlanet_00970b30(mission) == h.mp4C) return false;
            }
            float gr = GetTerraformRadius_00fc1fa0(*(int*)&radius);
            float dx = *(float*)((char*)obj + 0xb0) - 0.5f;
            float dy = *(float*)((char*)obj + 0xb4) - 0.5f;
            if (fabsf((float)sqrt((double)(dx * dx + dy * dy)) - (gr - flora)) < g_01694c08 &&
                fabsf(h.m1FD4) < g_01579a08 &&
                fabsf(h.m1FD8) < g_01579a08)
                return true;
            return false;
        }
    }
    return false;
}

// @ 0x00c7f060
void __fastcall FUN_00c7f060(void* self)
{
  float fTop;
  void* pm = FUN_00b3d350();
  if (*(void**)((char*)pm + 0x24) == 0) return;
  {
    void* obj = *(void**)((char*)pm + 0x24);
    float* f = (float*)((TFp)(*(void***)obj)[0xc / 4])(obj);
    fTop = f[0x3c / 4];
    {
      s32 i7 = 0, i9 = 0, i8 = 0;
      float* pu = (float*)((char*)self + 0x50);
      for (;;) {
        float a, b;
        FUN_00f929c0(2, i7, i9, i8, &a, &b);
        if (pu == 0) break;
        if (fTop <= a) {
          if (fTop <= b) pu[0] = 2.0f;
          else pu[0] = 1.0f;
        } else {
          pu[0] = 3.0f;
        }
        i9++;
        pu = (float*)((char*)pu + 0x54);
        if (i9 < 4) continue;
        i9 = 0;
        i8++;
        if (i8 < 4) continue;
        i8 = 0;
        i7++;
        if (i7 >= 6) break;
      }
    }
  }
  {
    void* mgr = FUN_00b3d440();
    void* it = *(void**)((char*)mgr + 0x1e5f0);
    if (it == *(void**)((char*)mgr + 0x1e5f4)) return;
    void* end = *(void**)((char*)mgr + 0x1e5f4);
    float* pf = (float*)((char*)it + 0x10);
    do {
      float* pv = pf - 2;
      if (FUN_00b7e3e0(pv, 0, 0) == 0) {
        float fx = pv[0];
        float fy = pf[-1];
        float fz = pf[0];
        float ax = fx < 0 ? -fx : fx;
        float ay = fy < 0 ? -fy : fy;
        float az = fz < 0 ? -fz : fz;
        s32 i8, i4, i5;
        if (az < ax || az < ay) {
          if (ay < ax) {
            i8 = (s32)((fy / fx + 1.0f) * 2.0f);
            i4 = (s32)((fz / ax + 1.0f) * 2.0f);
            i5 = 2;
            if (fx < 0.0f) i5 = 3;
          } else {
            i8 = (s32)((fz / fy + 1.0f) * 2.0f);
            i4 = (s32)((fx / ay + 1.0f) * 2.0f);
            i5 = (fy < 0.0f) ? 5 : 4;
          }
        } else {
          i8 = (s32)((fx / fz + 1.0f) * 2.0f);
          i4 = (s32)((fy / az + 1.0f) * 2.0f);
          i5 = (fz < 0.0f) ? 1 : 0;
        }
        if (i8 == 4) i8 = 3;
        if (i4 == 4) i4 = 3;
        *(s32*)((char*)self + (i4 + i5 * 4) * 4 * 0x54 + i8 * 0x54 + 0x50) = 3;
      }
      it = (char*)it + 0x19a8;
      pf = (float*)((char*)pf + 0x19a8);
    } while (it != end);
  }
}

// @ 0x00c7f300
u8 __fastcall FUN_00c7f300(void* self, void* dummy, u32* key, float x, float y, float z)
{
  (void)dummy;
  if (x == *(float*)0x1694bac) {
    if (y == *(float*)0x1694bb0) {
      if (z == *(float*)0x1694bb4) goto done;
    }
  }
  if (*key != 0) {
    u32* kp = key;
    void* e = ((FindC*)((char*)self + 0x50))->Find(&x);
    u32 k0 = kp[0];
    s32 i = 0;
    s32* p = (s32*)((char*)e + 0xc);
    do {
      if (p[-2] == (s32)k0 && p[-1] == (s32)kp[1] && p[0] == (s32)kp[2] && p[1] > 0)
        return 1;
      i++;
      p += 4;
    } while (i < 3);
  }
done:
  return 0;
}

// @ 0x00c7f390
void __cdecl FUN_00c7f390(void)
{
  void* mm = FUN_00feb9f0();
  void* list = ((MMC*)mm)->GetMissionList();
  s32 n = (*(s32*)((char*)list + 4) - *(s32*)list) >> 2;
  s32 i = 0;
  if (n > 0) {
    for (;;) {
      void* m = *(void**)((char*)(*(void**)list) + i * 4);
      void* tp = ((MissionC*)m)->GetTargetPlanet();
      void* ap = FUN_01021260();
      if (tp == ap && m != 0) {
        void* o = ((TFpu)(*(void***)m)[0xc / 4])(m, 0x35988ee);
        if (o != 0 && ((*(u32*)((char*)o + 0x130) >> 3) & 1)) break;
      }
      i++;
      if (i >= n) return;
    }
    if (FUN_01044640() != 0) {
      FUN_01041c50((void*)0x1473368, 0x9fc86b19, 1);
    }
  }
}

// @ 0x00c7f430
u8 __fastcall FUN_00c7f430(void* self, void* dummy, s32* keyword, float* coords)
{
  (void)dummy;
  float x = coords[0];
  if (x == *(float*)0x1694bac) {
    float y = coords[1];
    if (y == *(float*)0x1694bb0) {
      float z = coords[2];
      if (z == *(float*)0x1694bb4) goto done;
    }
  }
  if (*keyword != 0) {
    s32* kp = keyword;
    void* e = ((FindC*)((char*)self + 0x50))->Find(coords);
    s32 k0 = kp[0];
    s32 i = 0;
    s32* p = (s32*)((char*)e + 0x3c);
    do {
      if (p[-2] == k0 && p[-1] == kp[1] && p[0] == kp[2] && p[1] > 0) return 1;
      i++;
      p += 4;
    } while (i < 2);
  }
done:
  return 0;
}

// @ 0x00c7f4c0
s32 __fastcall FUN_00c7f4c0(void* self, void* dummy, s32* key)
{
  (void)dummy;
  s32 result = 0;
  char* cell = (char*)self + 0x50;
  s32 i4 = 0, i3 = 0, i8 = 0;
  for (;;) {
    if (cell == 0) return result;
    s32 i2 = 0;
    s32* p = (s32*)(cell + 0x3c);
    do {
      if (p[-2] == key[0] && p[-1] == key[1] && p[0] == key[2]) {
        if (i2 == 0) result = 1;
        else if (i2 == 1) result = 2;
        break;
      }
      i2++;
      p += 4;
    } while (i2 < 2);
    i4++;
    cell += 0x54;
    if (i4 > 3) {
      i3++;
      i4 = 0;
      if (i3 > 3) {
        i8++;
        i3 = 0;
        if (i8 > 5) return result;
      }
    }
  }
}

// @ 0x00c7f560
void** __fastcall FUN_00c7f560(void* self, void* dummy, void** out, u32* key)
{
  (void)dummy;
  void* node = *(void**)((char*)self + 0xc);
  void* best = (char*)self + 4;
  if (node != 0) {
    do {
      u32* p = (u32*)node;
      u8 less;
      if (p[4] != key[0]) less = (u8)(p[4] < key[0]);
      else if (p[6] != key[2]) less = (u8)(p[6] < key[2]);
      else less = (u8)(p[5] < key[1]);
      if (!less) {
        best = node;
        node = *(void**)((char*)node + 4);
      } else {
        node = *(void**)((char*)node);
      }
    } while (node != 0);
  }
  *out = best;
  return out;
}

// @ 0x00c7f5b0
void* __fastcall FUN_00c7f5b0(void* self, void* dummy, void* out, void* planet, float* coords)
{
  float* pf = (float*)out;
  void* pm = FUN_01049a10();
  void* tm = FUN_00b3d430();
  s32 r = FUN_00bbc670(tm, planet);
  float dx = coords[0] - *(float*)0x1471064;
  float dy = coords[1] - *(float*)0x1471064;
  float len2 = dx * dx + dy * dy;
  float len;
  if (len2 <= 1.5258789e-05f) {
    len = 0.0f;
    dx = 0.0f;
    dy = 0.0f;
  } else {
    len = sqrtf(len2);
    dx = (1.0f / len) * dx;
    dy = (1.0f / len) * dy;
  }
  float wdr = ((TuneC*)pm)->GetWaterDivergenceRate();
  float adr = ((TuneC*)pm)->GetAtmosphereDivergenceRate();
  float steep = (float)pow((double)len, (double)((TuneC*)pm)->GetBullseyeSteepnessPower());
  float force = (dx * (wdr * dx) + dy * (adr * dy)) * steep;
  float flRadius = ((TuneC*)pm)->GetFloraBullseyeRadius();
  float flScalar = ((TuneC*)pm)->GetFloraBullseyeForceScalar();
  s32 counts[3];
  counts[0] = 0; counts[1] = 0; counts[2] = 0;
  {
    void* mgr = FUN_00b3d430();
    if (mgr != 0) {
      s32 i = 1;
      s32* c = counts;
      do {
        s32* p;
        p = (s32*)((TerraMgrC*)mgr)->F870(&len, i, 0x6d60a1cc, planet);
        if (p[0] != *(s32*)0x1694bb8 || p[1] != *(s32*)0x1694bbc || p[2] != *(s32*)0x1694bc0)
          (*c)++;
        p = (s32*)((TerraMgrC*)mgr)->F870(&len, i, 0x29c388a, planet);
        if (p[0] != *(s32*)0x1694bb8 || p[1] != *(s32*)0x1694bbc || p[2] != *(s32*)0x1694bc0)
          (*c)++;
        p = (s32*)((TerraMgrC*)mgr)->F870(&len, i, 0x3a8be428, planet);
        if (p[0] != *(s32*)0x1694bb8 || p[1] != *(s32*)0x1694bbc || p[2] != *(s32*)0x1694bc0)
          (*c)++;
        i++;
        c++;
      } while (i < 4);
    }
  }
  if (r > 0) {
    s32 i = 0;
    do {
      s32 cnt = counts[i];
      if (cnt > 0) {
        float radius = *(float*)FUN_00fc1fa0(i + 1) - flRadius;
        if (radius < len) {
          float hi = radius + flRadius;
          float mid = len;
          if (mid <= radius) mid = radius;
          if (hi <= mid) mid = hi;
          float t = (mid - radius) / (hi - radius);
          force = force - (((3.0f - t * 2.0f) * t) * t) * ((float)cnt * flScalar);
        }
      }
      i++;
    } while (i < r);
  }
  pf[0] = force * dx;
  pf[1] = force * dy;
  float lc = 0.0f;
  {
    u32 sel;
    void* p = pm ? *(void**)((char*)pm + 0x24) : 0;
    if (p != 0 && ((AMdC*)p)->F24(0x5a72fa9, &sel)) {
      if (*(u16*)((char*)sel + 0x12) == 0xd) {
        if ((*(u32*)((char*)sel + 0x10) & 0x30) != 0) sel = *(u32*)sel;
        lc = *(float*)sel;
      }
    }
  }
  float py = 0.0f;
  {
    u32 sel;
    void* p = pm ? *(void**)((char*)pm + 0x24) : 0;
    if (p != 0 && ((AMdC*)p)->F24(0x5a72fad, &sel)) {
      if (*(u16*)((char*)sel + 0x12) == 0xd) {
        if ((*(u32*)((char*)sel + 0x10) & 0x30) != 0) sel = *(u32*)sel;
        py = *(float*)sel;
      }
    }
  }
  float pz = 0.0f;
  {
    u32 sel;
    void* p = pm ? *(void**)((char*)pm + 0x24) : 0;
    if (p != 0 && ((AMdC*)p)->F24(0x5a72fb0, &sel)) {
      if (*(u16*)((char*)sel + 0x12) == 0xd) {
        if ((*(u32*)((char*)sel + 0x10) & 0x30) != 0) sel = *(u32*)sel;
        pz = *(float*)sel;
      }
    }
  }
  u32 flags = *(u32*)((char*)planet + 0x2c);
  if (((flags >> 0xc) & 1) == 0) {
    if (((flags >> 0xd) & 1) != 0) {
      pf[0] = pf[0] - ((coords[0] * pz + py) * coords[0] + lc);
    }
  } else {
    pf[0] = ((1.0f - coords[0]) * pz + py) * (1.0f - coords[0]) + lc + pf[0];
  }
  if (FUN_00b8dab0(planet) == 5) {
    void* av = FUN_00b1fdb0(FUN_00b8de30(planet));
    void* sm = FUN_00b3d2a0();
    if (av == FUN_00885c90(sm)) {
      if (*(float*)((char*)planet + 0xb0) > *(float*)0x1471064) {
        pf[1] = ((1.0f - coords[1]) * pz + py) * (1.0f - coords[1]) + lc + pf[1];
        return out;
      }
      pf[1] = pf[1] - (coords[1] * pz + py) * coords[1] - lc;
    }
  }
  return out;
}

// @ 0x00c7fab0
void __fastcall FUN_00c7fab0(void* self, void* dummy, s32 dt)
{
  (void)dummy;
  void* target = *(void**)((char*)self + 0x4c);
  void* tune = FUN_01049a10();
  void* obj = *(void**)((char*)target + 0x13c);
  float timeScale = ((TuneC*)tune)->GetBullseyeTimeScale();
  float dtf = (float)dt;
  float t = (dtf * timeScale) * *(float*)0x13f9428;
  float mass = ((TuneC*)tune)->GetBullseyeMarbleMass();
  float coords[2];
  coords[0] = *(float*)((char*)obj + 0xb4);
  coords[1] = *(float*)((char*)obj + 0xb0);
  float fx, fy;
  FUN_00c7f5b0(self, 0, &fx, obj, coords);
  float invMass = 1.0f / mass;
  float nvx = (fx * invMass) * t + *(float*)((char*)self + 0x1fd8);
  float nvy = (fy * invMass) * t + *(float*)((char*)self + 0x1fd4);
  *(float*)((char*)self + 0x1fd8) = nvx;
  *(float*)((char*)self + 0x1fd4) = nvy;
  if (*(float*)((char*)obj + 0xb4) >= *(float*)0x1486cd8 && nvx > 0.0f) {
    *(float*)((char*)self + 0x1fd8) = 0.0f;
  }
  if (*(float*)((char*)obj + 0xb4) <= *(float*)0x13f9428 && nvx <= 0.0f && nvx != 0.0f) {
    *(float*)((char*)self + 0x1fd8) = 0.0f;
  }
  if (*(float*)((char*)obj + 0xb0) >= *(float*)0x1486cd8 && nvy > 0.0f) {
    *(float*)((char*)self + 0x1fd4) = 0.0f;
  }
  if (*(float*)((char*)obj + 0xb0) <= *(float*)0x13f9428 && nvy <= 0.0f && nvy != 0.0f) {
    *(float*)((char*)self + 0x1fd4) = 0.0f;
  }
  {
    float cur = *(float*)((char*)self + 0x1fd4);
    float absCur = cur < 0 ? -cur : cur;
    float drag = ((TuneC*)tune)->GetBullseyeMarbleDragCoeff();
    *(float*)((char*)self + 0x1fd4) = cur - ((drag * cur) * absCur) * t;
  }
  {
    float cur = *(float*)((char*)self + 0x1fd8);
    float absCur = cur < 0 ? -cur : cur;
    float drag = ((TuneC*)tune)->GetBullseyeMarbleDragCoeff();
    *(float*)((char*)self + 0x1fd8) = cur - ((drag * cur) * absCur) * t;
  }
  *(float*)((char*)obj + 0xb0) = t * *(float*)((char*)self + 0x1fd4) + *(float*)((char*)obj + 0xb0);
  *(float*)((char*)obj + 0xb4) = *(float*)((char*)self + 0x1fd8) * t + *(float*)((char*)obj + 0xb4);
  {
    float base = 1.0f - ((TuneC*)tune)->GetBullseyeMarbleDamping();
    float p = FUN_011e08f0(base, t);
    *(float*)((char*)self + 0x1fd4) *= p;
  }
  {
    float base = 1.0f - ((TuneC*)tune)->GetBullseyeMarbleDamping();
    float p = FUN_011e08f0(base, t);
    *(float*)((char*)self + 0x1fd8) *= p;
  }
  {
    float v = *(float*)((char*)obj + 0xb0);
    if (v <= 0.0f) v = 0.0f;
    if (v >= 1.0f) v = 1.0f;
    *(float*)((char*)obj + 0xb0) = v;
  }
  {
    float v = *(float*)((char*)obj + 0xb4);
    if (v <= 0.0f) v = 0.0f;
    if (v >= 1.0f) v = 1.0f;
    *(float*)((char*)obj + 0xb4) = v;
  }
  if (*(float*)((char*)obj + 0xb8) >= 0.0f) {
    float out[2];
    out[0] = *(float*)((char*)obj + 0xb4);
    FUN_00fc20e0(out, *(float*)((char*)obj + 0xb0), out[0]);
    float cur = *(float*)((char*)obj + 0xb8);
    if (out[0] >= cur) cur = out[0];
    if (out[1] <= cur) cur = out[1];
    *(float*)((char*)obj + 0xb8) = cur;
  }
}

// @ 0x00c7fdd0
void __fastcall FUN_00c7fdd0(void* self, void* dummy)
{
  (void)dummy;
  *(void**)self = (void*)0x14733a8;
  *(void**)((char*)self + 4) = (void*)0x1473398;
  *(void**)((char*)self + 0x34) = (void*)0x1473388;
  {
    NukeC* tree = (NukeC*)((char*)self + 0x20a0);
    void* node = ((void**)((char*)self + 0x20a0))[3];
    tree->DoNukeSubtree(node);
  }
  {
    char* ht = (char*)self + 0x2080;
    ((HtC*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(void**)(ht + 0xc) = 0;
    if (*(u32*)(ht + 8) > 1) FUN_00f47380(*(void**)(ht + 4));
  }
  {
    char* ht = (char*)self + 0x2060;
    ((HtC*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(void**)(ht + 0xc) = 0;
    if (*(u32*)(ht + 8) > 1) FUN_00f47380(*(void**)(ht + 4));
  }
  ((GonzagoC*)((char*)self + 0x2038))->Dtor();
  ((GonzagoC*)((char*)self + 0x2010))->Dtor();
  ((GonzagoC*)((char*)self + 0x1ff0))->Dtor();
  {
    void* h = *(void**)((char*)self + 0x38);
    if (h != 0) {
      void* a = *(void**)((char*)self + 0x3c);
      void* b = *(void**)((char*)self + 0x40);
      void* c = *(void**)((char*)self + 0x44);
      void* d = *(void**)((char*)self + 0x48);
      *(void**)((char*)self + 0x38) = 0;
      FUN_00571db0(h, a, b, c, d);
    }
  }
  *(void**)((char*)self + 0x34) = (void*)0x13eb394;
  ((GameDataC*)self)->Dtor();
}

// @ 0x00c7ff00
void __fastcall FUN_00c7ff00(void* self, void* dummy)
{
  (void)dummy;
  {
    char* ht = (char*)self + 0x28;
    ((HtC*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(void**)(ht + 0xc) = 0;
    if (*(u32*)(ht + 8) > 1) FUN_00f47380(*(void**)(ht + 4));
  }
  {
    char* ht = (char*)self + 8;
    ((HtC*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(void**)(ht + 0xc) = 0;
    if (*(u32*)(ht + 8) > 1) FUN_00f47380(*(void**)(ht + 4));
  }
}

// @ 0x00c7ff60
void* __fastcall FUN_00c7ff60(void* self, void* dummy, void* p)
{
  (void)dummy;
  u32 next = (u32)p + 0x10;
  u32 end = *(u32*)((char*)self + 4);
  if (next < end) {
    FUN_00705250((void*)next, (void*)end, p);
  }
  *(u32*)((char*)self + 4) -= 0x10;
  return p;
}

// @ 0x00c7ff90
void __fastcall cSimPlanetLowLODCtorSTUB(void* this_, int unused)
{
    (void)this_;
}

// @ 0x00c80110
__declspec(noinline) int32_t* __thiscall SP::cSpeciesKeyTable::FUN_00c80110(tSpeciesKey* pKey)
{
    SpeciesKeyInsertResult result;
    Find(&result, pKey);
    if (result.node == mpBuckets[mnBuckets]) {
        SpeciesKeyPair pair;
        pair.key = *pKey;
        pair.value = 0;
        SpeciesKeyInsertTag tag = {};
        Insert(&result, &pair, tag);
    }
    return &result.node->value;
}

// @ 0x00c80180
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c80180()
{
}

// @ 0x00c805b0
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c805b0()
{
}

// @ 0x00c80680
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c80680()
{
}

// @ 0x00c80780
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c80780()
{
}

// @ 0x00c809d0
bool __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::AddPlantSpecies(tSpeciesKey* pKey)
{
    cSpeciesList* pList = mpPlanet->mpSpeciesList;
    int32_t count = (int32_t)(pList->mpEnd - pList->mpBegin);
    tSpeciesKey* pEntry = pList->mpBegin;
    for (int32_t i = 0; i < count; ++i) {
        if (pEntry->mField0 == pKey->mField0 &&
            pEntry->mField4 == pKey->mField4 &&
            pEntry->mField8 == pKey->mField8)
            return false;
        ++pEntry;
    }
    if (!FUN_00b3d420()->GetSpeciesFromID(pKey))
        return false;
    if (count >= 9)
        return false;
    mpPlanet->PushKeyBC(pKey);
    *mSpeciesTable.FUN_00c80110(pKey) = 0;
    FUN_00b3d3b0()->SetInfoFromProps();
    return true;
}

// @ 0x00c80a80
void __thiscall SP::cSimPlanetLowLOD_s00c7_ff90::FUN_00c80a80()
{
}

// @ 0x00c81ab0
u32 __fastcall FUN_00c81ab0(void* self, void* /*edx*/, void* arg1, float* pos, char flag)
{
  char* p = (char*)self;
  int* key = (int*)arg1;              // species/resource key (3 dwords)
  float x = pos[0];
  float y = pos[1];
  float z = pos[2];

  // Early-out: exact match against the "invalid position" sentinel.
  if (x == *(float*)0x01694bac) {
    if (y == *(float*)0x01694bb0) {
      if (z == *(float*)0x01694bb4) {
        return 1;
      }
    }
  }
  // Early-out: key equals sentinel.
  if (key[0] == *(int*)0x01694bb8 && key[1] == *(int*)0x01694bbc &&
      key[2] == *(int*)0x01694bc0) {
    return 1;
  }

  // iVar15 = cell array base (mCubeSim at +0x4c, +0x13c -> array).
  int* arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  int lo = arr[0xbc / 4];
  int hi = arr[0xc0 / 4];
  int cubeCount = (hi - lo) / 12;

  float ax = (float)fabs(x);
  float ay = (float)fabs(y);
  float az = (float)fabs(z);

  int local_20, local_1c, local_18;
  if (az < ax || az < ay) {
    if (ay < ax) {
      local_20 = (int)((y / x + 1.0) * 2.0);
      local_1c = (int)((z / ax + 1.0) * 2.0);
      local_18 = (x < 0.0f) ? 3 : 2;
    } else {
      local_20 = (int)((z / y + 1.0) * 2.0);
      local_1c = (int)((x / ay + 1.0) * 2.0);
      local_18 = (y < 0.0f) ? 5 : 4;
    }
  } else {
    local_20 = (int)((x / z + 1.0) * 2.0);
    local_1c = (int)((y / az + 1.0) * 2.0);
    local_18 = (z < 0.0f) ? 1 : 0;
  }
  if (local_20 == 4) local_20 = 3;
  if (local_1c == 4) local_1c = 3;

  int* dens = &arr[(local_1c + local_18 * 4) * 4 + local_20];

  int* vec = 0;
  int* vecEnd = 0;
  u32 vecCap = 0;
  ((void(__thiscall*)(void*, void*, void*, u32))FUN_00c805b0)(p + 0x50, pos, &vec, 0);
  if ((u32)((char*)vecEnd - (char*)vec) / 16 < 3) {
    ((void(__thiscall*)(void*, void*, void*, u32))FUN_00c805b0)(p + 0x50, pos, &vec, 1);
  }
  if (vec != vecEnd && vec[0] == local_20 && vec[1] == local_1c &&
      vec[2] == local_18 && (int*)vec[3] == dens) {
    ((void(__thiscall*)(void*))FUN_00c7ff60)(vec);
  }
  int* first = vec;
  FUN_00c821b0(p, 0, dens, key, 1, 0);  // SetPlantDensity
  if (*dens < 3 && first != vecEnd) {
    int* dens2 = (int*)first[3];
    ((void(__thiscall*)(void*))FUN_00c7ff60)(first);
    FUN_00c821b0(p, 0, dens2, key, 1, 0);
    first = vec;
  }

  FUN_00b3d3b0(0);
  FUN_00b2bbe0();
  FUN_00b3d420(key);
  u32 ret = 0;
  char* cell = (char*)FUN_00b90410(key);
  if (cell != 0) {
    u32 kind = 0;
    s32 k = FUN_00b8f860();
    if (k == 0x29c388a) kind = 2;
    else if (k == 0x3a8be428) kind = 4;
    else if (k == 0x6d60a1cc) kind = 1;
    FUN_00b3d3b0((void*)kind);
    ret = FUN_00b2a750(kind);
  }

  if (flag != 0) {
    int n = *(int*)((char*)arr + 0xc0) - *(int*)((char*)arr + 0xbc);
    u32 cnt = (u32)(n / 12);
    if ((u32)((hi - lo) / 12) < cnt && (cnt % 3 == 0) &&
        (*(u32*)((char*)arr + 0x2c) & 0x800) == 0) {
      *(u32*)(p + 0x1f8) = 1;   // mExtinctionInfoMap field
      char* nm = (char*)FUN_00b3d300();
      void* sphere = (void*)0;
      (void)nm; (void)sphere;
      // UI feedback event path.
      FUN_00c772c0(nm, (void*)0x541a716);
    }
  }
  if (first != 0 && first[-1] != 0) {
    FUN_00f47380(first);
  }
  return ret;
}

// @ 0x00c81f40
void __fastcall FUN_00c81f40(void* self, void* /*edx*/, void* arg)
{
  char* p = (char*)self;
  int* key = (int*)arg;
  if (key[0] == 1) return;

  int* arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  int n = (*(int*)((char*)arr + 0xc0) - *(int*)((char*)arr + 0xbc)) / 12;
  if (n == 0) return;

  FUN_00b3d420(0);
  u32 r6 = FUN_00a68fb0((void*)0x01694c00, 3);
  u32 r7 = FUN_00a68fb0((void*)0x01694c00, 3);
  u32 r8 = FUN_00a68fb0((void*)0x01694c00, 3);

  int vecA = *(int*)((char*)arr + 0x114) - *(int*)((char*)arr + 0x110);
  int vecB = *(int*)((char*)arr + 0xfc) - *(int*)((char*)arr + 0xf8);
  if ((vecA >> 2) == n && (vecB >> 2) == n) {
    double d15 = FUN_a68fd0((void*)0x01694c04);
    double d16 = FUN_a68fd0((void*)0x01694c04);
    double d17 = FUN_a68fd0((void*)0x01694c04);
    for (int i = 0; i < n; ++i) {
      char* cell = (char*)(*(int*)((char*)arr + 0xbc) + i * 12);
      float fv = *(float*)(*(int*)((char*)arr + 0x110) + i * 4);
      int  iv = *(int*)(*(int*)((char*)arr + 0xf8) + i * 4);
      float sc = *(float*)((char*)arr + 0x10c);
      FUN_00b90410(cell);
      s32 k = FUN_00b8f860();
      double dv = d16; u32 rv = r7;
      if (k == 0x29c388a) { /* default */ }
      else if (k == 0x3a8be428) { dv = d17; rv = r8; }
      else if (k == 0x6d60a1cc) { dv = d15; rv = r6; }
      else continue;
      if (iv == (int)rv && (float)dv < fv * sc) {
        FUN_00c821b0(p, 0, key, cell, 1, 0);
      }
    }
    return;
  }

  int la = 0, lb = 0, lc = 0;
  for (int i = 0; i < n; ++i) {
    char* cell = (char*)(*(int*)((char*)arr + 0xbc) + i * 12);
    FUN_00b90410(cell);
    s32 k = FUN_00b8f860();
    int hit = 0;
    if (k == 0x29c388a) { hit = (la == (int)r7); ++la; }
    else if (k == 0x3a8be428) { hit = (lb == (int)r8); ++lb; }
    else if (k == 0x6d60a1cc) { hit = (lc == (int)r6); ++lc; }
    if (hit) {
      FUN_00c821b0(p, 0, key, cell, 1, 0);
    }
  }
}

// @ 0x00c821b0
void __fastcall FUN_00c821b0(void* self, void* /*edx*/, void* a2, void* a3, int a4, void* a5)
{
  char* p = (char*)self;
  int* dens = (int*)a2;     // density record ptr
  int* key = (int*)a3;      // species key
  int pi = a4;
  int* out = (int*)a5;

  int* arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  int* begin = *(int**)((char*)arr + 0xd0);
  int* end = *(int**)((char*)arr + 0xd4);
  int* found = begin;
  while (found != end) {
    if (found[0] == key[0] && found[1] == key[1] && found[2] == key[2]) break;
    found += 3;
  }
  if (found == end && (u32)((char*)end - (char*)begin) / 12 < 9) {
    FUN_00401090(key);
    if (FUN_004df550(key) != 0) {
      FUN_00c732c0(key);
      u32* slot = (u32*)FUN_00c80110(key);
      *slot = 0;
    }
  }

  FUN_00401090(key);
  void* prof = FUN_004df550(key);
  int hasProf = (prof != 0 && *(int*)((char*)prof + 0x608) != 0) ? 1 : 0;
  int off = hasProf * 0x10;

  int* rec = (int*)((char*)dens + off + 0x34);
  int oldv0 = rec[0], oldv1 = rec[1], oldv2 = rec[2], oldv3 = rec[3];
  rec[0] = key[0]; rec[1] = key[1]; rec[2] = key[2]; rec[3] = pi;

  if (rec[0] != oldv0 || rec[1] != oldv1 || rec[2] != oldv2 || oldv3 != pi) {
    if (pi > 0 && (rec[0] != *(int*)0x01694bb8 || rec[1] != *(int*)0x01694bbc ||
                   rec[2] != *(int*)0x01694bc0)) {
      int* c = (int*)FUN_00c80110(rec);
      *c = *c + 1;
    }
    if (oldv3 > 0 && (oldv0 != *(int*)0x01694bb8 || oldv1 != *(int*)0x01694bbc ||
                      oldv2 != *(int*)0x01694bc0)) {
      int tmp[3];
      tmp[0] = oldv0; tmp[1] = oldv1; tmp[2] = oldv2;
      int* c = (int*)FUN_00c80110(tmp);
      *c = *c - 1;
      if (*c == 0) {
        if (out != 0) {
          int cntr = out[1] - out[0];
          int total = cntr >> 4;
          for (int i = 0; i < total; ++i) {
            int* e = *(int**)((char*)out[0] + i * 16 + 12);
            int* r = e + hasProf * 4 + 0xd;
            if (*e > 1) {
              if (r[3] == 0) {
                r[0] = tmp[0]; r[3] = oldv3; r[1] = oldv1; r[2] = oldv2;
                int* c2 = (int*)FUN_00c80110(tmp);
                *c2 = *c2 + 1;
                return;
              }
              int* c2 = (int*)FUN_00c80110(r);
              if (*c2 > 1) {
                if (r[3] > 0 && (r[0] != *(int*)0x01694bb8 ||
                                 r[1] != *(int*)0x01694bbc ||
                                 r[2] != *(int*)0x01694bc0)) {
                  int* c3 = (int*)FUN_00c80110(r);
                  *c3 = *c3 - 1;
                }
                r[0] = tmp[0]; r[3] = oldv3; r[1] = oldv1; r[2] = oldv2;
                int* c4 = (int*)FUN_00c80110(tmp);
                *c4 = *c4 + 1;
                return;
              }
            }
          }
        }
        u32* t = (u32*)FUN_0103de50(tmp);
        *t = 0x388deb10;
      }
    }
  }
  (void)found;
}

// @ 0x00c82870
void __fastcall FUN_00c82870(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  int* pm = *(int**)((char*)SP_PlanetModel() + 0x24);
  if (pm == 0) {
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c00, 0);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c04, 0);
  } else {
    u32 s = (*(u32(__thiscall**)(int*))(*(int**)pm + 0x18 / 4))(pm);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c00, s);
    s = (*(u32(__thiscall**)(int*))(*(int**)pm + 0x18 / 4))(pm);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c04, s);
  }

  char* cell = p + 0x50;
  if (cell != 0) {
    int outer = 0, mid = 0, inner = 0;
    do {
      ((void(__thiscall*)(void*, void*))FUN_00c81f40)(p, cell);
      ++inner; cell += 0x54;
      if (inner > 3) {
        ++mid; inner = 0;
        if (mid > 3) {
          ++outer; mid = 0;
          if (outer > 5) break;
        }
      }
    } while (cell != 0);
  }
}

// @ 0x00c82900
void __fastcall FUN_00c82900(void* self, void* /*edx*/, void* arg)
{
  char* p = (char*)self;
  int* arr;
  int* begin;
  int* end;
  int count;
  int off;
  int cA;
  int cB;
  u32 r6;
  u32 r3;

  FUN_00b3d450();
  r6 = ((u32(__thiscall*)(void*, u32))FUN_00a68fb0)((void*)0x01601760, 6);
  r3 = ((u32(__thiscall*)(void*, u32))FUN_00a68fb0)((void*)0x01601760, 3);

  arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  begin = *(int**)((char*)arr + 0xd0);
  end = *(int**)((char*)arr + 0xd4);
  count = (int)((char*)end - (char*)begin) / 12;

  off = 0;
  cA = 0;
  cB = 0;
  if (count > 0) {
    do {
      char* key = (char*)((char*)begin + off);
      int kk = FUN_00401090(key);
      void* prof = FUN_004df550((void*)kk);
      if (prof != 0) {
        int hit;
        if (*(int*)((char*)prof + 0x608) != 0) {
          hit = (cA == (int)r3);
          ++cA;
        } else {
          hit = (cB == (int)r6);
          ++cB;
        }
        if (hit) {
          FUN_00c821b0(p, 0, key, arg, 1, 0);
        }
      }
      off += 0xc;
      --count;
    } while (count != 0);
  }
}

// @ 0x00c829e0
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c829e0()
{
}

// @ 0x00c82d50
__declspec(noinline) void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c82d50(SP::cPlanet_s00c8_29e0* pPlanet, bool bValue)
{
    SP::gStubSink = pad000[0];                               // side effect keeps the call
}

// @ 0x00c82ea0
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c82ea0()
{
    cSimPlanetLowLOD_s00c8_30f0* self = (cSimPlanetLowLOD_s00c8_30f0*)this;
    if ((self->mpPlanet->mpPlanetRecord->mFlags & 0x800) == 0) {
        char* cell = (char*)self->pad050;
        int face = 0, column = 0, row = 0;
        do {
            if (cell == 0)
                return;
            ((void(__thiscall*)(void*, void*))FUN_00c82900)(this, cell);
            ++column;
            cell += 0x54;
            if (column >= 4) {
                ++row;
                column = 0;
                if (row >= 4) {
                    ++face;
                    row = 0;
                    if (face >= 6)
                        break;
                }
            }
        } while (true);
    }
}

struct cPlanetModelG { const ResourceKey& GetPlanetKey(); }; // 0x00b7e380
// @ 0x00c82f00
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c82f00()
{
    cSimPlanetLowLOD_s00c8_30f0* self = (cSimPlanetLowLOD_s00c8_30f0*)this;
    if (self->mbPlanetKeyLoaded_2058 != 0)
        return;
    if (SP::GetUniverseContext() != 0)
        return;
    if ((void*)mpPlanet != (void*)GetActivePlanet_s00c8_30f0())
        return;

    if (((cPlanet_s00c8_30f0*)mpPlanet)->FUN_00c713e0()->groupID != ((cPlanetModelG*)SP_PlanetModel())->GetPlanetKey().groupID)
        return;
    cPlanetModelG* model = (cPlanetModelG*)SP_PlanetModel();
    const ResourceKey* key = &model->GetPlanetKey();
    ResourceKey* cur = ((cPlanet_s00c8_30f0*)mpPlanet)->FUN_00c713e0();
    if (cur->instanceID != key->instanceID)
        return;

    self->mbPlanetKeyLoaded_2058 = 1;
    self->FUN_00c7f060();
    self->FUN_00c82870();
    FUN_00c82ea0();
}

// @ 0x00c82f80
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c82f80()
{
}

// @ 0x00c83050
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c83050(SP::cPlanet_s00c8_29e0* pOld, SP::cPlanet_s00c8_29e0* pNew, bool bValue)
{
    if (pOld == pNew) {
        if (!SP::GetUniverseContext()) {
            FUN_00c82d50(pNew, bValue);
            return;
        }
    }
    UpdateBackgroundPlanet(pNew, bValue);
}

// @ 0x00c83090
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c83090(SP::tPlanetKey key, bool bValue)
{
    mEntryTable.FUN_00ba4e60(&key)->mFieldA0 = bValue;
}

// @ 0x00c830b0
bool __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c830b0(SP::tPlanetKey key)
{
    return mEntryTable.FUN_00ba4e60(&key)->mFieldA1;
}

// @ 0x00c830d0
void __thiscall SP::cSimPlanetLowLOD_s00c8_29e0::FUN_00c830d0(SP::tPlanetKey key, bool bValue)
{
    mEntryTable.FUN_00ba4e60(&key)->mFieldA1 = bValue;
}

// @ 0x00c830f0
namespace SP {
void cSimPlanetLowLOD_s00c8_30f0::UpdateTerraforming(int arg)
{
    cTerraformingManager* terraform;
    cPlanetRecord_s00c8_30f0* record = mpPlanet->mpPlanetRecord;
    terraform = TerraformingManager();

    if (mLastTerraformLevel < 0)
        mLastTerraformLevel = mpPlanet->GetTScore() - 2;

    if (!g_TerraformDisabled && mbFinishPending && GetCurrentGameMode() == 0x1654c05) {
        FUN_00c7fab0(arg);
        if (FUN_00c7ee50()) {
            mbFinishPending = false;
            mb2031 = false;
            mF1fd4 = 0.0f;
            mF1fd8 = 0.0f;
            if (mpPlanet != 0 && !mpPlanet->FUN_00c70a70())
                mpPlanet->FUN_00c70aa0(mpPlanet->GetWaterScore());
            SpaceGameGet()->FUN_01005180(1);
        }
    }

    int level = terraform->GetTerraformLevel(record);
    bool isActive = GetUniverseContext() == 0 && mpPlanet == GetActivePlanet_s00c8_30f0();
    bool collapsePending = false;

    if (TerrainEntry(record).mInitialLevel == -1)
        TerrainEntry(record).mInitialLevel = (signed char)level;
    if (TerrainEntry(record).mInitialPlants == -1) {
        uint32_t plants = record->PlantCount();
        TerrainEntry(record).mInitialPlants = (signed char)(plants / 3);
    }

    if (level != mLastTerraformLevel) {
        if (mpPlanet->GetTScore() >= 2) {
            switch (level) {
            case 0: mpPlanet->SetEcosystemStage(2); break;
            case 1: mpPlanet->SetEcosystemStage(3); break;
            case 2: mpPlanet->SetEcosystemStage(4); break;
            case 3: mpPlanet->SetEcosystemStage(5); break;
            default: mpPlanet->SetEcosystemStage(2); break;
            }
        }

        if (isActive) {
            MessageServer()->SendMSG(0x490d429, 0, 0, 0);
            uint32_t effectID = 0xc5be3f36;
            if (level <= mLastTerraformLevel)
                effectID = 0x95857906;
            intrusive_ptr<IVisualEffect> effect;
            if (EffectsManager()->CreateVisualEffect(effectID, 0, effect.reset_out()))
                effect->Start(0);
        }

        if (level < mLastTerraformLevel) {
            if (isActive)
                mCollapseTimer.Restart();
            else
                collapsePending = true;
        } else {
            mCollapseTimer.Stop();
        }

        if (mbFinishPending) {
            bool aiOwned;
            cEmpire_s00c8_30f0* owner = mpPlanet->GetOwner();
            if (owner == 0 || owner == GetPlayerEmpire()) {
                aiOwned = false;
            } else {
                uint32_t pid = owner->mPoliticalID;
                aiOwned = true;
                if (level < mLastTerraformLevel)
                    RelationshipManager()->RecordEvent(pid, GetPlayerEmpireID(), 0x526e531, 1.0f);
                else
                    RelationshipManager()->RecordEvent(pid, GetPlayerEmpireID(), 0x526e535, 1.0f);
            }

            if (isActive) {
                GetTutorial()->TerraformLevelChanged(level, mLastTerraformLevel);
                if (level < mLastTerraformLevel)
                    PlayTerraformAudio(0x5877dcf4, GetRecorderState());
                else
                    PlayTerraformAudio(0xb1cdbbcf, GetRecorderState());

                if (!aiOwned) {
                    if (level > TerrainEntry(record).mInitialLevel) {
                        NounManager()->GetCurrentTerrainSphere()->SetTerraformLevel(record->GetID(), level);
                        SpaceGameGet()->GetPlayerTribe()->FUN_00fe5430(3, 1);
                        Z3 a, b, c, d;
                        FUN_00e39ab0(0xecc0fff3, 0, &d, &c, GetActivePlanetRecord()->GetID(), 0, &b, &a);
                    }
                    if (level > mLastTerraformLevel && !(record->mFlags & 0x800)) {
                        cTerrainSphere_s00c8_30f0* sphere = NounManager()->GetCurrentTerrainSphere();
                        if (sphere != 0 && !sphere->HasMusic(0x4d7f97a)) {
                            sphere->PlayMusic(0x4d7f97a);
                            GetTutorial()->Trigger(0xb010e8b);
                        }
                    }
                }
            }
        }
        mLastTerraformLevel = level;
    }

    bool collapse = false;
    if (mCollapseTimer.IsRunning()) {
        float seconds = (float)mCollapseTimer.GetElapsedTime() * 0.001f;
        float delay = 0.0f;
        PropertyList* tuning = *GetTerraformTuning();
        Property* prop;
        if (tuning != 0 && tuning->GetProperty(0x3c5e2f2, prop) && prop->mnType == 0xd)
            delay = *prop->GetFloat();
        if (level == 0 || seconds > delay) {
            mCollapseTimer.Stop();
            collapse = true;
        }
    }
    if (collapse || collapsePending) {
        bool destroyed = false;
        if (level == 0 || !(mpPlanet->mpPlanetRecord->mFlags & 0x800)) {
            for (int i = 3; i > level; --i) {
                if (terraform->DestroyEcosystemLevel(i, mpPlanet))
                    destroyed = true;
            }
            if (destroyed) {
                cEmpire_s00c8_30f0* owner = mpPlanet->GetOwner();
                if (owner != 0 && owner != GetPlayerEmpire())
                    RelationshipManager()->RecordEvent(owner->mPoliticalID, GetPlayerEmpireID(), 0x526e537, 1.0f);
                if (isActive)
                    EventLog()->PostFeedbackEvent(0x752e35a4, 0x131a9f54, 0, 0, 1, 0);
                mExtinctionMap.clear();
                TerraformingManager()->FUN_00bbe740(mpPlanet);
            }
        }
        TerraformingManager()->FUN_00bc1450(mpPlanet);

        if (level == 0) {
            if (isActive) {
                FUN_00b3d480()->FUN_00acd4a0();
                cGameNounManager_s00c8_30f0* nouns = NounManager();
                GameDataPtrVector creatures(nouns->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0,
                                                                     FUN_00b1e500, 0x18c6d19)->mData, 0);
                int count = creatures.size();
                for (int i = 0; i < count; i++) {
                    cCreatureLike* c = creatures.mpBegin[i]->AsCreature();
                    if (c != 0)
                        c->mSub.SetTerraformState(c->mF158, GetPlayerEmpireID(), 0, g_ColonyReason, 0);
                }
                if (mpPlanet->GetTechLevel() == 4) {
                    GameDataPtrVector colonies(nouns->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0,
                                                                        FUN_00b1e500, 0x18c43e8)->mData);
                    int n = colonies.size();
                    for (int i = 0; i < n; i++) {
                        cGameData_s00c8_30f0* colony = colonies.mpBegin[i];
                        colony->FUN_00bdc050();
                        nouns->RemoveNoun(colony);
                    }
                }
                nouns->RemoveNounsOfType(0x18c84a9);
                tGameDataVector_s00c8_30f0* left = nouns->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0,
                                                                 FUN_00b1e500, 0x18c43e8);
                if (left->mData.mpBegin == left->mData.mpEnd) {
                    nouns->RemoveNounsOfType(0x18c6de8);
                    nouns->FUN_00b25ee0();
                    mpPlanet->SetNeedsReset(1);
                }
            } else {
                bool none;
                {
                    ByteVector cities = mpPlanet->GetCities();
                    none = cities.mpBegin == cities.mpEnd;
                }
                if (none)
                    mpPlanet->SetNeedsReset(1);
                return;
            }
        }
    }

    if (isActive) {
        if (fabsf(mpPlanet->GetAtmosphereScore() - mLastAtmosphere) > 0.0f ||
            fabsf(mpPlanet->GetTemperatureScore() - mLastTemperature) > 0.0f ||
            fabsf(mpPlanet->GetWaterScore() - mLastWater) > 0.0f) {
            terraform->UpdatePlanetScores(mpPlanet, mpPlanet->GetAtmosphereScore(),
                                          mpPlanet->GetTemperatureScore(), mbFinishPending);
            MessageServer()->PostMSG(0x1c3d2e0, 1, 0);
            mLastAtmosphere = mpPlanet->GetAtmosphereScore();
            mLastTemperature = mpPlanet->GetTemperatureScore();
            if (mLastWater != mpPlanet->GetWaterScore()) {
                mbScoresDirty = true;
                mLastWater = mpPlanet->GetWaterScore();
            }
        }
        if (mbScoresDirty)
            FUN_00c7f060();
    }
}
}  // namespace SP
