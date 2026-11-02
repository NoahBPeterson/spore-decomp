// src/game/SPGonzago/_at_00dd0000.cpp -- migrated from slice(s) s00ddf990, s00ddcdc0, s00ddbe40, s00dda3b0, s00dd9510, s00dd0230 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00dd0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cGameNounManager.h"
#include "SP/cCity.h"
#include "SP/cCombatant.h"
#include "SP/cMilitaryAttackCityOrder.h"
#include "SP/cSpatialObject.h"
#include "SP/cString.h"
#include "SP/cVehicle.h"
#include "SP/cVehicleGroupOrder.h"

// unnamed retail callees and globals (address in the comment)
extern wchar_t gEmptyString16[];                            // 0x01667bac
extern float gMinusOneFloat;                                        // 0x013eb1bc = -1.0f
#include <math.h>
#include <new>
#include "EA/Stopwatch.h"
#include <intrin.h>
#include "SP/FunctionalMatch/Constraint.h"

// ---- items of slice s00dd0230 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct cSPVector3_s00dd_0230 {
    float x, y, z;
    cSPVector3_s00dd_0230() {}
    cSPVector3_s00dd_0230(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3_s00dd_0230(const cSPVector3_s00dd_0230& v) { x = v.x; y = v.y; z = v.z; }
};
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void operator delete[](void* p);                                                   // 0x00f47380
struct IRefCounted {
    virtual void AddRef();                     // +0x00
    virtual void Release();                    // +0x04
};
class cSpatialObject : public IRefCounted {
public:
    virtual void* v08();                                // +0x08 (slot 2)
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void v28();
    virtual const cSPVector3_s00dd_0230& GetPosition();            // +0x2c (slot 11)
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual bool v50();                                 // +0x50 (slot 20)
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
    virtual void* Cast();                               // +0xb8 (slot 46)
    virtual void vb8();                                 // +0xbc (slot 47)
    virtual void vc0();                                 // +0xc0 (slot 48)
    cSpatialObject* CastObject();                       // +0xb8 (typed form)
};
class cLocomotive : public cSpatialObject {
public:
virtual void vbc();
virtual void vc0();
virtual void vc4();
    virtual void MoveTo(const cSPVector3_s00dd_0230& dst, float a, float b, bool rel);   // +0xe0
    virtual void MoveAround(const cSPVector3_s00dd_0230& c, float r);                    // +0xe4
    virtual void MoveTowards(const cSPVector3_s00dd_0230& dst);                          // +0xe8
};
class cCombatant : public IRefCounted {
public:
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual float GetRadius();                          // +0x14
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
    virtual void v50(void* pTarget);                    // +0x50 (slot 20)
    float GetStat();                                    // 0x00bfc400 (thiscall)
};
class cCity : public IRefCounted {
public:
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void v28();
    virtual bool v2c();                                 // vtable +0x2c (slot 11)
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual uint32_t v4c();                             // vtable +0x4c (slot 19)
    char pad04[0x120 - 4];
    struct cCityDisplay {                               // embedded object at +0x120
        char pad00[0x50];
        uint32_t mFlags;                                // +0x50 (absolute +0x170)
    } mDisplay;                                         // +0x120
    char pad174[0x44c - 0x174];
    void* mpSomething_44c;                              // +0x44c
    cCity* GetCivilization();                           // 0x00bd9bf0
};
class cVehicle {
public:
    char pad00[0x34];
    cLocomotive mLoco;                                  // +0x34
    char padLoco[0x508 - 0x34 - sizeof(cLocomotive)];
    cCombatant mCombatant;                              // +0x508
    char padCombat[0xb1c - 0x508 - sizeof(cCombatant)];
    uint32_t mLocomotion;                               // +0xb1c
    char padB20[0xb7c - 0xb1c - 4];
    cSpatialObject* mpChaseTargetRef;                   // +0xb7c

    void* GetTreeData();                                // 0x00ca71d0 (thiscall)
    void Log(const char* msg);                          // 0x00ca7250 (thiscall)
    void Flush();                                       // 0x00caa900 (thiscall)
    void SetTarget(void* pTarget);                      // 0x00dc4d00 (thiscall, ret 4)
};
class cVehicleGroupOrder : public IRefCounted {
public:
    virtual void v08();
    virtual void* FindOrderByType(uint32_t type);       // vtable +0x0c (slot 3)
    char pad04[0x50 - 4];
    cVehicle** mVehiclesBegin;                          // +0x50
    cVehicle** mVehiclesEnd;                            // +0x54
};
class cMilitaryAttackCityOrder : public cVehicleGroupOrder {
public:
    char pad58[0x80 - 0x58];
    uint32_t mBanner_80;                                // +0x80
    uint32_t mMode;                                     // +0x84 (1..5 selector)
    uint32_t mBanner_88;                                // +0x88
    uint32_t mField_8c;                                 // +0x8c
    float mStatScale;                                   // +0x90
    cCity* mpCity;                                      // +0x94
    uint32_t mAttackerId;                               // +0x98
    char pad9c[0xac - 0x9c];

    cSpatialObject* GetCurrentTarget(cVehicle* pVehicle);        // 0x00dcfc90
    uint32_t GetCityBannerId();                                  // 0x00dd0550
    void* QueryInterface(uint32_t type);                         // 0x00dd0590
    bool IsInSimulatorContext();                                 // 0x00dd05e0
    bool IsActive();                                             // 0x00dd0600
    void* QueryInterface2(uint32_t type);                        // 0x00dd0610
    uint32_t GetIconKey();                                       // 0x00dd0650
    uint32_t GetPaletteItemPriority();                           // 0x00641770
    uint32_t GetMissionKey();                                    // 0x00dd06a0
    void SetupOrder(cVehicle* pVehicle);                         // 0x00dc8c00 (thiscall, ret 4)
    void ResetOrder(cVehicle* pVehicle);                         // 0x00dcc350 (thiscall, ret 4)
    bool OnTick(float dt);                                       // 0x00dd0380 (override, slot 20)
};
struct StarManagerObj;
struct EmpiresObj;
struct StarManagerObj {
    uint32_t GetBannerId(uint32_t id);                   // 0x00ba6dc0 (thiscall)
    EmpiresObj* GetEmpireByID(uint32_t id);              // 0x00ba9370 (thiscall, ret 4)
};
struct EmpiresObj {
    void* GetCities();                                   // 0x005c65e0 (thiscall)
};
struct CivNameSource {
    const wchar_t* mpName;                               // +0x00
};
struct SceneKey {
    uint32_t mTag;                                       // +0x00
    uint32_t mId;                                        // +0x04
    uint32_t mFlags;                                     // +0x08
};
StarManagerObj* __cdecl StarManager();                   // 0x00b3d2a0
int __cdecl GetUniverseContext();                                    // 0x1021080
uint32_t __cdecl GetPaletteItemPriority();                          // 0x00641770
bool __cdecl FUN_00b6e250();                                         // 0x00b6e250
uint32_t __cdecl FUN_00b6f0d0(uint32_t id);                          // 0x00b6f0d0
void* __cdecl NounManager();                                         // 0x00b3d300
struct GameNounManagerObj {
    void* GetPlayerCivilization();                                   // 0x00b25fb0 (thiscall)
};
struct CivModeStrategyObj {
    bool IsValid();                                                  // 0x00cf7a90 (thiscall)
};
CivModeStrategyObj* __cdecl CivModeStrategy();                       // 0x00cf74c0
struct cString_s006b_47a0 {                             // SP::cString, retail 0x14 bytes
    uint32_t d[5];
    cString_s006b_47a0();                               // 0x006b5060
    ~cString_s006b_47a0();                              // 0x006b5240
    void Construct() { CtorImpl(); }                    // 0x006b5060 (thiscall, named wrapper)
    void CtorImpl();                                    // 0x006b5060
    void Load(uint32_t table, uint32_t id, int flag, const wchar_t* name);  // 0x006b54b0
    const wchar_t* GetText();                           // 0x006b55c0
};
struct UI_ScenarioInner {
    uint32_t mField00;                                  // +0x00
    uint32_t mField04;                                  // +0x04
    uint32_t mField08;                                  // +0x08
    uint32_t mField0c;                                  // +0x0c
    uint32_t mField10;                                  // +0x10
    uint32_t mField14;                                  // +0x14
    uint32_t mField18;                                  // +0x18
    uint32_t mField1c;                                  // +0x1c
    uint32_t mField20;                                  // +0x20
    void*    mpField24;                                // +0x24
    uint32_t mField28;                                  // +0x28
    float    mField2c;                                  // +0x2c
};
struct UI_ScenarioPayload {
    char pad00[0x0c];
    UI_ScenarioInner* mpInner;                          // +0x0c
};
struct UI_ScenarioDataSrc {
    char pad00[0x0c];
    UI_ScenarioPayload* mpPayload;                      // +0x0c
};
struct eastl_wstring {
    wchar_t* mpBegin;                                   // +0x00
    wchar_t* mpEnd;                                     // +0x04
    void*    mpCapacity;                                // +0x08
    void Append(const wchar_t* pText);                  // 0x005c3d90
    void Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    void DeallocateSelf();                              // 0x00933960
};
void __cdecl WString_FromCStr(eastl_wstring* pOut, const wchar_t* pText);   // 0x0041df50 (ret 8)
struct eastl_u32vec {
    uint32_t* mpBegin;                                  // +0x00
    uint32_t* mpEnd;                                    // +0x04
    uint32_t* mpCapacity;                               // +0x08
    void DoInsertValue(uint32_t* pos, const uint32_t& value);   // 0x004558a0
    void push_back(uint32_t v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p != 0)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
struct IPropertyHandle {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
};
struct IPropertyManager {
    PV8 PV4
    virtual void GetProperty(uint32_t key, void** ppOut);     // +0x30 (slot 12)
};
struct IResourceManager {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual bool LoadKey(const void* pKey, int a, int b, int c, int d, int e);   // +0x0c (slot 3)
};
struct IMgr67de40 {
    PV8 PV8
    virtual IPropertyHandle* v20();                     // +0x20 (slot 8)
};
struct IHaveProp12 {
    PV8 PV4
    virtual void GetPropertyAt12(void* a, void* b, int c);   // +0x30 (slot 12)
};
void* __cdecl Mgr67de40();                              // 0x0067de40
void* __cdecl ResourceManager();                        // 0x0067dcd0
void* __cdecl PropertyManager();                        // 0x0067de30
void* __cdecl GetPropertyAsKey(void* pHandle, uint32_t key, void* pOut);   // 0x006a1250
void* __fastcall FUN_00b8d8e0(void* p);                        // 0x00b8d8e0 (ecx=this)
void* __cdecl FUN_00b8d8f0(void* p);                        // 0x00b8d8f0
void* __fastcall FUN_00b8de30(void* p);                        // 0x00b8de30 (ecx=p)
void* __fastcall FUN_00bb9de0(void* p);                        // 0x00bb9de0 (ecx=p)
void* __cdecl FUN_00bb9ae0(void* p);                        // 0x00bb9ae0
void* __cdecl StarManager_GetEmpireByID(void* pStar, uint32_t id);         // 0x00ba9370
void* __cdecl CivData_GetCities(void* pCiv);                              // 0x005c65e0
struct AvatarNameObj;
struct AvatarNameObj {
    uint32_t* GetName();                                 // 0x00ecdba0 (thiscall)
};
struct TerrainSphereObj {
    void* Find(uint32_t id);                            // 0x00c756e0 (thiscall, ret 4)
};
struct NounObj {
    void* GetTerrainSphere();                           // 0x00f67d90 (thiscall)
};
void* __cdecl GameNounManager_GetAvatar(void* pNoun);                     // 0x00b1fdb0
void* __cdecl GetStringFromId(void* out, uint32_t id, int flag, void* pString);   // 0x00b6ec50
void* __cdecl FUN_00401090(void* pData);                    // 0x00401090
void* __fastcall FUN_004df400(void* pData);                 // 0x004df400 (ecx=pData)
unsigned char __cdecl FUN_004eb930(void* pA);               // 0x004eb930
extern wchar_t gEmptyString16[];                            // 0x01667bac
class AssetDiscovery_Data {
public:
    uint32_t mField_04;                                 // +0x04
    uint32_t mField_08;                                 // +0x08
    uint32_t mField_0c;                                 // +0x0c
    char pad10[0x78 - 0x10];
    uint32_t mField_78;                                 // +0x78
    uint32_t mField_7c;                                 // +0x7c
    uint32_t mField_80;                                 // +0x80
    uint32_t mField_84;                                 // +0x84
    uint32_t mField_88;                                 // +0x88
    int32_t  mEnumValue;                                // +0x8c
    float    mField_90;                                 // +0x90
    void*    mpField_94;                                // +0x94
    UI_ScenarioPayload* mpPayload;                      // +0x98

virtual void v04();
virtual void v08();
    virtual void* v0c();                                // +0x0c (slot 3)
    PV8 PV8 PV8 PV8 PV4 PV PV                          // slots 3..40
    virtual void vA4(uint32_t owner);                   // +0xa4 (slot 41)
    virtual void vA8();                                 // +0xa8 (slot 42)
    virtual void vAC(uint32_t owner);                   // +0xac (slot 43)
    PV2
    virtual void* vB8();                                // +0xb8 (slot 46)
    virtual void vbc();                                 // +0xbc (slot 47)
    virtual void vC0();                                 // +0xc0 (slot 48)
    virtual void vC4();                                 // +0xc4 (slot 49)

    void AssignFromScenario(void* pSrc, uint32_t owner);         // 0x00dd0710
    void UpdateEnumValue();                                      // 0x00dd07f0
    uint32_t GetAvatarName();                                    // 0x00dd0940
    uint32_t GetCreatureName();                                  // 0x00dd0960
    void GetSceneKey(uint32_t* pOut);                            // 0x00dd0990
    uint32_t* GetSceneKeyOut(uint32_t* pOut);                    // 0x00dd0a00
    uint32_t* GetStatKeyOut(uint32_t* pOut);                     // 0x00dd0ac0
    uint64_t GetField78();                                       // 0x00dd0b30
    void* ConstructBase();                                       // 0x00dd0b50
    void* ConstructPlain();                                      // 0x00dd0da0
    bool CollectTerrainKeys(eastl_u32vec* pOut);                 // 0x00dd1070
    bool CollectTerrainKeysBase(eastl_u32vec* pOut);             // 0x00642700 (TimelineSporepediaCardData)
};
class AssetDiscovery_DataCStr : public AssetDiscovery_Data {
public:
    cString_s006b_47a0 mString;                         // +0x9c

    void AssignCityName(eastl_wstring* pOut);                    // 0x00dd0c00
    void* ConstructString();                                    // 0x00dd0ca0
    void* Delete(unsigned char flags);                          // 0x00dd0cf0
    const wchar_t* GetDisplayText();                            // 0x00dd0e10
};
void __fastcall TimelineSporepediaCardData_Ctor(void* pThis);        // 0x00642100 (ecx=this)
void __fastcall TimelineSporepediaCardData_Dtor(void* pThis);        // 0x00642190 (ecx=this)
extern float gMinusOneFloat;                                        // 0x013eb1bc = -1.0f
struct cVGO_PredView {
    PV2 PV
    virtual void* PredSlot3();
};
struct SomeObj {
    char pad[0x28];
    uint32_t mKey_28;                                   // +0x28
    uint8_t  mFlag_2c;                                  // +0x2c
    void SetKeyAgain(uint32_t arg);                     // 0x00dd1240 (thiscall, 1 stack arg)
};
// ---- items of slice s00dd0230 end

// ---- items of slice s00dd9510 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc(void);
extern "C" void _ReadWriteBarrier(void);
extern "C" double __cdecl acos(double);                          // 0x011e08c8
extern "C" void __cdecl Start3dSoundByName(unsigned int soundId, unsigned int objectId,
                                           float x, float y, float z);
extern char  g_16a0b04;                                          // 0x016a0b04
extern float g_16a1078;                                          // 0x016a1078
extern float g_15a2cec;                                          // 0x015a2cec
extern float g_16a0ba4, g_16a0ba8, g_16a0bac;                    // 0x016a0ba4 (Vec3 axis)
extern float g_16a0b0c, g_16a0b10, g_16a0b14;                    // 0x016a0b0c (Vec3)
#pragma intrinsic(__rdtsc)
#pragma intrinsic(_ReadWriteBarrier)
struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Vec4 { float x, y, z, w; };
union LARGE_INTEGER {
    struct { unsigned int LowPart; int HighPart; } u;
    long long QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpCount);
extern "C" Vec4* MakeRotation(const Vec3* axis, const Vec3* in, Vec4* out);
extern Vec4  g_m48;                                              // 0x015a2d2c (aliases the four above)
struct Timer {
    unsigned int mLo;      // +0x00 (element +0xb0)
    unsigned int mHi;      // +0x04
    unsigned int mZ1;      // +0x08
    unsigned int mZ2;      // +0x0c
    int mMode;             // +0x10 (element +0xc0)
    float mfCoef;          // +0x14 (element +0xc4)
};
namespace EA {
class Stopwatch_s00dd_9510 {
public:
    unsigned __int64 mnStartTime;                // +0x00
    unsigned __int64 mnTotalElapsedTime;         // +0x08
    int mnUnits;                                 // +0x10
    float mfCoefficient;                         // +0x14
    Stopwatch_s00dd_9510(int units, bool useCycles);        // 0x0093a560
    void Restart();                              // 0x00571e80
    long long GetElapsedTimeFloat();  // 0x0093a3a0 (EA::Stopwatch::GetElapsedTimeFloat)
};
}
struct Boid {
    void*  mResA;          // +0x00
    void*  mResB;          // +0x04
    void*  mEffect;        // +0x08
    Vec3   mPos;           // +0x0c
    Vec3   mV18;           // +0x18
    Vec3   mV24;           // +0x24
    Vec3   mV30;           // +0x30
    Vec3   mV3C;           // +0x3c
    Vec4   mM48[5];        // +0x48
    float  m98;            // +0x98
    float  m9C;            // +0x9c
    float  mA0;            // +0xa0
    float  mA4;            // +0xa4
    float  mA8;            // +0xa8
    int    mAC;            // +0xac
    Timer  mTimer;         // +0xb0
    int    mC8;            // +0xc8
    int    mCC;            // +0xcc
    int    mD0;            // +0xd0
    char   mD4;            // +0xd4
    char   mD5;            // +0xd5
    char   mD6;            // +0xd6
    char   mD7;            // +0xd7
    char   mD8;            // +0xd8
    char   mD9[3];         // +0xd9
    float  mDC;            // +0xdc
    float  mE0;            // +0xe0
    float  mE4;            // +0xe4
    float  mE8;            // +0xe8
    float  mEC;            // +0xec
    float  mF0;            // +0xf0
    int    mF4;            // +0xf4
    int    mF8;            // +0xf8
    int    mFC;            // +0xfc

    Boid();                                                          // 0x00dd9510
};
struct Swarm {
    Boid** mpBegin;        // +0x00
    Boid** mpEnd;          // +0x04
    Boid** mpCapacity;     // +0x08
    int    pad0C[2];       // +0x0c
    void*  mpMgr;          // +0x14

    int   FUN_00dda060(int id);                                      // 0x00dda060
    void  FUN_00dda090(int id, char v);                              // 0x00dda090
    void  FUN_00dda0d0(int id);                                      // 0x00dda0d0
    void  FUN_00dd9750(Boid* e);                                     // 0x00dd9750
    int   FUN_00dda380();                                            // 0x00dda380
    bool  FUN_00dd97a0(Boid* p, int unused);                         // 0x00dd97a0
    bool  FUN_00dd9860(Boid* b, int unused);                         // 0x00dd9860
    void  FUN_00dd9a10(Boid* b);                                     // 0x00dd9a10
    bool  FUN_00dd9c10(Boid* b, int unused);                         // 0x00dd9c10
    float FUN_00dda160(const Vec3* p, int group);                    // 0x00dda160
};
// ---- items of slice s00dd9510 end

// ---- items of slice s00dda3b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_016a0b0c, DAT_016a0b10, DAT_016a0b14, DAT_016a0b58;
extern float DAT_016a0ba4, DAT_016a0ba8, DAT_016a0bac, DAT_016a0ff8;
extern float DAT_016a0fd8, DAT_016a0fe8, DAT_016a1018, DAT_016a1028;
extern float DAT_016a0b28[9];
extern void  EASTL_allocator_deallocate(void*);         // 0x00f47380  cdecl
extern void* FUN_0067dd50();                            // 0x0067dd50
extern void* FUN_0067dd10();                            // 0x0067dd10
extern void* FUN_0067cb40();                            // 0x0067cb40
extern float* FUN_00dd93d0();                           // 0x00dd93d0
extern float* FUN_00dd91b0();                           // 0x00dd91b0
extern void  FUN_00dd9080();                            // 0x00dd9080
extern float FUN_00572a10(float, float);                // 0x00572a10
class ObjA;
extern ObjA* DAT_016a0b08;                              // 0x016a0b08  ObjA singleton
struct GlobalTimer {
    double FUN_009360d0();                              // 0x009360d0
    int    FUN_00a68fb0(int);                           // 0x00a68fb0
};
#define G_TIMER ((GlobalTimer*)0x1601760)
struct IvObj {
    void FUN_00dde590(void* q);                         // 0x00dde590
};
class Matrix3 { public: void Assign(const void* src); };
struct Dest {
    void  FUN_004e39a0(int a, int b);                   // 0x004e39a0  destroy a temp
    void  FUN_006bac90(void* src);                      // 0x006bac90
    void  FUN_006b9440(void* arg);                      // 0x006b9440
    void* FUN_00558830(int z);                          // 0x00558830  build, returns the out buffer
    void* FUN_00558960(int a, int b, int c);            // 0x00558960  build, returns the out buffer
};
#define VT(o)       (*(void***)(o))
#define VSLOT(o, n) (VT(o)[(n) / 4])
static __forceinline char  vc0_char(void* o, int n)
{ return ((char(__thiscall*)(void*))VSLOT(o, n))(o); }
static __forceinline void  vc1_void(void* o, int n, int a)
{ ((void(__thiscall*)(void*, int))VSLOT(o, n))(o, a); }
static __forceinline void* vc1_ret(void* o, int n, int a)
{ return ((void*(__thiscall*)(void*, int))VSLOT(o, n))(o, a); }
static __forceinline void* vc2_ret(void* o, int n, int a, int b)
{ return ((void*(__thiscall*)(void*, int, int))VSLOT(o, n))(o, a, b); }
static __forceinline void* vc0_ret(void* o, int n)
{ return ((void*(__thiscall*)(void*))VSLOT(o, n))(o); }
struct Mat3 {
    float m[9];                       // +0x00 (0x24 bytes)
    void copy(const void* src);       // 0x0041cb40  thiscall (dst=ecx, src=stack)
};
class Rel { public: virtual void vf0(); virtual void vf1(); };
class ObjA {
public:
    void* p00;      // +0x00
    int   f04;      // +0x04
    int   f08;      // +0x08
    char  gap0c[8]; // +0x0c
    Rel*  p14;      // +0x14
    Rel*  p18;      // +0x18
    Rel*  p1c;      // +0x1c
    Rel*  p20;      // +0x20
    void* p24;      // +0x24
    int   f28;      // +0x28
    int   f2c;      // +0x2c
    char  gap30[8]; // +0x30
    short w38;      // +0x38
    short w3a;      // +0x3a
    float f3c;      // +0x3c
    float f40;      // +0x40
    float f44;      // +0x44
    float f48;      // +0x48
    Mat3  m4c;      // +0x4c
    Rel*  p70;      // +0x70

    ObjA* FUN_00dda920();
    void  FUN_00dda9a0();
    float FUN_00dda160(void* pt3, int z);   // 0x00dda160
};
struct CObj {
    char          pad00[0x0c];
    float         f0c;                  // +0x0c
    float         f10;                  // +0x10
    float         f14;                  // +0x14
    char          pad18[0x24 - 0x18];
    float         f24;                  // +0x24
    float         f28;                  // +0x28
    float         f2c;                  // +0x2c
    char          pad30[0x48 - 0x30];
    float         f48;                  // +0x48
    float         f4c;                  // +0x4c
    float         f50;                  // +0x50
    float         f54;                  // +0x54
    char          pad58[0x98 - 0x58];
    float         f98;                  // +0x98
    char          pad9c[0xa8 - 0x9c];
    float         fa8;                  // +0xa8
    char          padac[0xb0 - 0xac];
    unsigned      b0;                   // +0xb0
    unsigned      b4;                   // +0xb4
    unsigned      b8;                   // +0xb8
    unsigned      bc;                   // +0xbc
    int           c0;                   // +0xc0
    float         c4;                   // +0xc4
    char          padc8[0xd5 - 0xc8];
    unsigned char d5;                   // +0xd5
    char          padd6[0xd8 - 0xd6];
    unsigned char d8;                   // +0xd8
    float         dc;                   // +0xdc
    float         e0;                   // +0xe0
    float         e4;                   // +0xe4
    float         e8;                   // +0xe8
    float         ec;                   // +0xec
    float         f0;                   // +0xf0
    void*         f4;                   // +0xf4
};
class CB {
public:
    char  pad00[0x14];
    void* p14;                          // +0x14
    void* p18;                          // +0x18
    void* p1c;                          // +0x1c
    void  m3b0(char param_2);
};
struct Q {                              // 0x00dda500 normalised pose
    short a, b;
    float x, y, z, w;
    float m[9];
};
struct S9 { int v[9]; };                // 0x00ddaf70 nine-dword payload
struct Vec12 { char* b; char* e; char* c; };
typedef void (__cdecl* CB34)(void*, void*, S9, S9);
// ---- items of slice s00dda3b0 end

// ---- items of slice s00ddbe40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_angle;                                                  // 0x015a2d00
extern float g_maxAngle;                                               // 0x016a0b58
extern float g_scaleLo, g_scaleHi;                                     // 0x016a0fd8 / 0x016a0fe8
extern float g_dHi, g_dLo;                                             // 0x016a1018 / 0x016a1028
extern float g_z;                                                      // 0x016a1038
extern float g_maxE0;                                                  // 0x013eecd8
extern char  g_boidGlobal;                                             // 0x016a0c00
extern const float k_range50;                                          // 0x0147d244
extern const float k_min35;                                            // 0x0147d240
extern uint32_t      g_scanInit;                         // 0x016a0c78 (bit 0 = scratch list initialised)
extern "C" int   atexit(void (*fn)(void));               // 0x011e07ef (lib_crt)
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);   // 0x011e0744 (lib_crt)
typedef unsigned int uint;
struct Key { uint a, b, c; };
struct KeyVec
{
    Key* mpBegin; Key* mpEnd; Key* mpCapacity;
    ~KeyVec() { if (mpBegin && ((uint*)mpBegin)[-1]) operator delete[](mpBegin); }
};
struct Vec3_s00dd_be40 { float x, y, z; };
static __forceinline Vec4 MakeV4(float x, float y, float z, float w)
{
    Vec4 v; v.x = x; v.y = y; v.z = z; v.w = w; return v;
}
struct Quat
{
    float x, y, z, w;
    void Assign(const Quat* o) { x = o->x; y = o->y; z = o->z; w = o->w; }
};
static __forceinline Quat MakeQuat(float x, float y, float z, float w)
{
    Quat q; q.x = x; q.y = y; q.z = z; q.w = w; return q;
}
Quat* QuatMul(Quat* out, const Quat* a, const Quat* b);                // 0x007dcb00 (cdecl)
struct RandomLinearCongruential
{
    double RandomDoubleUniform();                                      // 0x009360d0
};
extern RandomLinearCongruential g_Random;                              // 0x01601760
float RandomFloatRange(float lo, float hi);                            // 0x00572a10 (cdecl)
static __forceinline float RandInline(float lo, float hi)
{
    double dlo = lo;
    double dhi = hi;
    double u = g_Random.RandomDoubleUniform();
    double r = u * (dhi - dlo) + dlo;
    if (r < dhi)
        return (float)(dlo > r ? dlo : r);
    return (float)dhi;
}
struct KeyUtil
{
    bool IsValid(const Key* k);                                        // 0x00b7d4f0 (ret 4)
    void MakeVariants(Key k, Key* p4, Key* p5, Key* p6, void* p7, Key* p8, Key* p9);   // 0x00b7d440 (ret 0x24)
};
KeyUtil* GetKeyUtil();                                                 // 0x00b3d360 (returns [0x167eafc])
struct KeyTree
{
    void GetKeys(KeyVec* out);                                         // 0x00de7530 (ret 4)
    void Remove(Key* k);                                               // 0x00de74c0 (ret 4)
};
struct ResMgr { uint32_t pad[0x3c / 4]; KeyTree tree; };
extern ResMgr* g_resMgr;                                               // [0x016a1344]
extern uint g_nextKey;                                                 // [0x016a0c60]
static __declspec(noinline) void SplitKey(const Key* k, Key* a, Key* b)
{
    if (GetKeyUtil()->IsValid(k))
    {
        Key kk = *k;
        GetKeyUtil()->MakeVariants(kk, 0, 0, 0, 0, a, b);
    }
    else
    {
        a->a = 0; a->b = 0; a->c = 0;
        b->a = 0; b->b = 0; b->c = 0;
    }
}
struct IEff
{
virtual void Slot0();
virtual void Slot1();
virtual void Slot2(int a);
};
struct EffectsMgr
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
    virtual void Find(uint hash, int zero, IEff** out);                // +0x2c (ret 0xc)
};
EffectsMgr* EffectsManager();                                          // 0x0067ddd0
uint FNV1_String16(const wchar_t* s, uint seed, int mode);             // 0x00932f30 (cdecl)
struct StrRange { const wchar_t* mpBegin; const wchar_t* mpEnd; };
extern StrRange g_effectName;                                          // 0x016a109c
struct Stopwatch                                                       // 0x18 bytes
{
    void SetUnits(int u);                                              // 0x0093a1a0 (ret 4)
    uint32_t mStartLo;          // +0x00
    uint32_t mStartHi;          // +0x04
    uint32_t pad08;             // +0x08
    uint32_t pad0c;             // +0x0c
    int      mUnits;            // +0x10 (1 = rdtsc, otherwise QueryPerformanceCounter)
    float    mScale;            // +0x14
};
struct Resource { uint32_t pad0; uint32_t mFlags; uint32_t pad[(0x40 - 8) / 4]; int mRef; };
struct HolderObj;
struct MapMgr
{
virtual void v00();
virtual void v04();
virtual void v08();
    virtual Resource* Create(uint a, uint b, uint c);                  // +0x0c (ret 0xc)
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
    virtual void Attach(Resource* r, HolderObj* h, int idx);           // +0xa4 (ret 0xc)
};
template <class T> struct PtrVec
{
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
};
struct TransformDesc                                                   // vtable 0x01453948
{
    virtual void d0();
    uint16_t mKind;             // +4
    uint16_t mCount;            // +6
    float*   mpMatrix;          // +8
    Vec4     mRow[4];           // +0xc  (4x4 identity)
    uint32_t pad[(0x10c - 0x4c) / 4];
    TransformDesc() : mKind(0x206), mCount(0x100), mpMatrix(&mRow[0].x) {}
};
struct HolderObj
{
    void* vtbl;
    int   mRef;
    PtrVec<TransformDesc*> mVec;                                       // +8   DoInsertValue 0x004558a0
    HolderObj();                                                       // 0x0077d1d0 (fastcall ctor)
};
struct Boid_s00dd_be40                                                            // 0x100 bytes
{
    Resource* mResA;            // +0x00
    Resource* mResB;            // +0x04
    IEff*     mEffect;          // +0x08
    Vec3_s00dd_be40      mPos;             // +0x0c
    Vec3_s00dd_be40      mV18;
    Vec3_s00dd_be40      mV24;
    Vec3_s00dd_be40      mV30;             // +0x30
    Vec3_s00dd_be40      mStartPos;        // +0x3c
    Quat      mRot;             // +0x48
    uint32_t  pad58[8];         // +0x58
    Quat      mV78;             // +0x78
    Quat      mV88;             // +0x88
    float     m98;              // +0x98
    uint32_t  pad9c[3];         // +0x9c
    float     mA8;              // +0xa8
    uint32_t  padac;            // +0xac
    Stopwatch mWatch;           // +0xb0
    int       mC8;              // +0xc8
    int       mCC;              // +0xcc
    int       mD0;              // +0xd0
    char      mD4;              // +0xd4
    char      mD5;              // +0xd5
    char      mD6;              // +0xd6
    char      mD7;              // +0xd7
    char      padd8[4];         // +0xd8
    float     mDC;              // +0xdc
    float     mE0;              // +0xe0
    uint32_t  pade4;            // +0xe4
    Vec3_s00dd_be40      mAxis;            // +0xe8
    uint32_t  padf4;            // +0xf4
    void*     mpF8;             // +0xf8
    int       mFC;              // +0xfc
    Boid_s00dd_be40();                                                            // 0x00dd9510 (fastcall ctor)
};
extern Vec3_s00dd_be40 g_v0b0c;                                                   // 0x016a0b0c
extern Vec3_s00dd_be40 g_v0ba4;                                                   // 0x016a0ba4
extern Vec3_s00dd_be40 g_axis;                                                    // 0x016a0c3c
static __declspec(noinline) Vec3_s00dd_be40* RandomOffset(Vec3_s00dd_be40* out)
{
    static float range = k_range50;
    static float minLen = k_min35;
    int i = 0;
    do
    {
        out->x = RandInline(-range, range);
        out->y = RandInline(-range, range);
        out->z = 0.0f;
        float len = sqrtf((out->x * out->x + out->y * out->y) + out->z * out->z);
        if (!(len < minLen && len > range))
            break;
    } while (i++ < 1000);
    return out;
}
struct ITimer;                                                         // defined with the gold7 block below
struct Swarm_s00dd_be40 : PtrVec<Boid_s00dd_be40*>
{
    uint32_t pad[2];
    MapMgr*  mpMgr;                                                    // +0x14
    MapMgr*  mpMgr2;                                                   // +0x18 (second resource manager; slot 0x0c = Create)
    uint32_t pad1c[(0x70 - 0x1c) / 4];
    ITimer*  mpTimer;                                                  // +0x70 (slot 0x24 takes the step + a flag)
    float    FindNearest(const Vec3_s00dd_be40* p, int group);                    // 0x00dda160 (ret 8)
    void     SpawnOne();                                               // 0x00ddbe40
    void     FUN_00ddb600(Boid_s00dd_be40* b);                                    // 0x00ddb600 (ret 4)
    bool     FUN_00ddb0d0(Boid_s00dd_be40* b, uint32_t ticks);                    // 0x00ddb0d0 (ret 8)
    Boid_s00dd_be40*    FUN_00ddc4a0();                                           // 0x00ddc4a0 (ret 0)
    void     FUN_00ddc820(uint32_t key);                               // 0x00ddc820 (ret 4)
    void     FUN_00ddc6d0(uint32_t ticks);                             // 0x00ddc6d0 (ret 4)
    void     FUN_00ddc910(const Vec3_s00dd_be40* pos, const Vec3_s00dd_be40* dir, unsigned char a, unsigned char b);  // 0x00ddc910 (ret 0x10)
    void     FUN_00ddcad0(const Vec3_s00dd_be40* pos, const Vec3_s00dd_be40* dir);           // 0x00ddcad0 (ret 8)
};
#define VS1(p)  virtual void p##_a();
#define VS2(p)  VS1(p##0) VS1(p##1)
#define VS4(p)  VS2(p##0) VS2(p##1)
#define VS8(p)  VS4(p##0) VS4(p##1)
struct ITimer
{
    VS8(v0)                                              // +0x00 (slots 0x00..0x1c)
    VS1(v1)                                              // +0x20
    virtual void SetStep(float dt, int flag);            // +0x24 (ret 8)
};
template <class T> struct SPVec4
{
    T* mpBegin;                                          // +0x00
    T* mpEnd;                                            // +0x04
    T* mpCapacity;                                       // +0x08
    void DoInsertKey4(T* pos, const T& v);               // 0x00b96600 (ret 8)
    void push_back(const T& v)                           // SPVector 4-byte push shape
    {
        if (mpEnd < mpCapacity)
        {
            T* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot != 0)
                *slot = v;
        }
        else
        {
            DoInsertKey4(mpEnd, v);
        }
    }
};
extern SPVec4<Boid_s00dd_be40*> g_scanList;                         // 0x016a0c64 (scratch list rebuilt each step)
void FUN_013c5f50();                                     // 0x013c5f50 (scratch-list teardown)
struct ObjA_s00dd_be40
{
    void FUN_00ddb790();                                 // 0x00ddb790 (ret 0)
    void FUN_00dda9a0();                                 // 0x00dda9a0 (ret 0)
};
extern ObjA_s00dd_be40* g_objA;                                     // [0x016a0b08]
// ---- items of slice s00ddbe40 end

// ---- items of slice s00ddcdc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t kLayerName[];               // 0x0147d2d8
extern const char* gName15a2db0;     // 0x015a2db0
extern const char* gName15a2db4;     // 0x015a2db4
extern const char* gName15a2dbc;     // 0x015a2dbc
extern const char* gName15a2dc8;     // 0x015a2dc8
extern const char* gName15a2dcc;     // 0x015a2dcc
extern const char* gName15a2dd0;     // 0x015a2dd0
extern const char* gName15a2dd4;     // 0x015a2dd4
extern const char* gName15a2dd8;     // 0x015a2dd8
extern const char* gName15a2ddc;     // 0x015a2ddc
extern uint32_t gPropKey;            // 0x015a2df8
#pragma intrinsic(memcpy)
#define V1(n) virtual void n();
#define V4(p) V1(p##0) V1(p##1) V1(p##2) V1(p##3)
#define V16(p) V4(p##0) V4(p##1) V4(p##2) V4(p##3)
template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    AutoRef& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
    T** AsOutParam()
    {
        if (mp) {
            T* t = mp;
            mp = 0;
            t->Release();
        }
        return &mp;
    }
    ~AutoRef() { if (mp) mp->Release(); }
};
struct IRef {
    virtual int AddRef();       // +0x00
    virtual int Release();      // +0x04
};
struct ILight : IRef {
    V4(l0) V4(l1) V1(l2) V1(l3)                                   // slots 2..11
    virtual void SetName(uint32_t id);                            // +0x30
};
struct ILayer : IRef {
    V4(y0) V1(y1)                                                 // slots 2..6
    virtual void AddModel(void* model, int a, int b, int c, int d);   // +0x1c
};
struct IModelWorld {
    V16(w0) V1(w1) V1(w2) V1(w3)                                  // slots 0..18
    virtual void SetModelType(int type);                          // +0x4c
};
struct IModel : IRef {
    V16(m0) V16(m1) V16(m2) V16(m3) V4(m4) V4(m5) V1(m6) V1(m7) V1(m8)   // slots 2..76
    virtual void SetFlag(int on);                                 // +0x134
    V1(m9)                                                        // +0x138
    virtual int GetModelType(int a, int b);                       // +0x13c
    virtual void Attach(ILight* light, int a, int b);             // +0x140
};
struct ILightMgr {
    V4(a0) V1(a1) V1(a2)                                          // slots 0..5
    virtual ILight* GetLight(uint32_t key, int a, int b);         // +0x18
};
struct IModelMgr {
    V4(a0) V1(a1)                                                 // slots 0..4
    virtual IModel* GetModel(uint32_t key, int a, int b);         // +0x14
};
struct ILayerMgr {
    V4(a0) V4(a1)                                                 // slots 0..7
    virtual ILayer* GetLayer(const wchar_t* name);                // +0x20
};
ILightMgr* LightingManager();                    // 0x0067dd90
IModelMgr* ModelManager();                       // 0x0067dd80
IModelWorld* ModelWorld();                       // 0x0067dd50
ILayerMgr* LayerManager();                       // 0x0067cb20
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
};
inline void FreeArray(void* p)
{
    if (p) {
        if (((int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
}
template <class T>
struct PtrVecBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    static T* copy_memcpy(T* first, T* last, T* result)
    {
        return (T*)((last - first) * sizeof(T) + (char*)memcpy(result, first, (char*)last - (char*)first));
    }
    T* erase(T* first, T* last)
    {
        T* position = copy_memcpy(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct NameVec : PtrVecBase<const char**> {
    void DoInsertValue(const char*** pos, const char** const& value);   // 0x00b96600
    void push_back(const char** const& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) const char**(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct ValueVec : PtrVecBase<uint32_t> {
    void DoInsertValue(uint32_t* pos, const uint32_t& value);           // 0x004558a0
    void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) uint32_t(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
namespace SP {
namespace FunctionalMatch {
struct Constraint_s00dd_cdc0;
}
}
struct ConstraintVec {
    SP::FunctionalMatch::Constraint_s00dd_cdc0* mpBegin;
    SP::FunctionalMatch::Constraint_s00dd_cdc0* mpEnd;
    SP::FunctionalMatch::Constraint_s00dd_cdc0* mpCapacity;
    sp_vector_allocator mAllocator;
    ConstraintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ConstraintVec();
    void DoDestroyValues(SP::FunctionalMatch::Constraint_s00dd_cdc0* first, SP::FunctionalMatch::Constraint_s00dd_cdc0* last);  // 0x004e39a0
    void DoInsertValue(SP::FunctionalMatch::Constraint_s00dd_cdc0* pos, const SP::FunctionalMatch::Constraint_s00dd_cdc0& v);   // 0x004e39d0
    void push_back(const SP::FunctionalMatch::Constraint_s00dd_cdc0& value);
};
namespace SP {
namespace FunctionalMatch {
enum EqualConstraint_s00dd_cdc0 { kEquals_s00dd_cdc0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s00dd_cdc0 {
    unsigned int mParameter;
    int mType;
    int mMin;
    int mMax;
    ConstraintVec mConstraints;
    Constraint_s00dd_cdc0(unsigned int param, EqualConstraint_s00dd_cdc0, int value);   // 0x00558960
    Constraint_s00dd_cdc0(const Constraint_s00dd_cdc0& other);                          // 0x00606880
    ~Constraint_s00dd_cdc0()
    {
        mConstraints.DoDestroyValues(mConstraints.mpBegin, mConstraints.mpEnd);
        FreeArray(mConstraints.mpBegin);
    }
};
}
}
inline void ConstraintVec::push_back(const SP::FunctionalMatch::Constraint_s00dd_cdc0& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) SP::FunctionalMatch::Constraint_s00dd_cdc0(value);
    else
        DoInsertValue(mpEnd, value);
}
inline ConstraintVec::~ConstraintVec()
{
    DoDestroyValues(mpBegin, mpEnd);
    FreeArray(mpBegin);
}
struct ResourceKey {
    uint32_t mInstanceID, mTypeID, mGroupID;
};
struct KeyVec_s00dd_cdc0 {
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    sp_vector_allocator mAllocator;
    KeyVec_s00dd_cdc0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~KeyVec_s00dd_cdc0() { FreeArray(mpBegin); }
};
class cISPObjectTemplateDB_s00dd_cdc0 {
public:
    V4(d0) V4(d1) V4(d2) V1(d3) V1(d4)                            // slots 0..13
    virtual void FindAssets(KeyVec_s00dd_cdc0& results, const ConstraintVec& query);   // +0x38
};
cISPObjectTemplateDB_s00dd_cdc0* ObjectTemplateDB();                         // 0x0067cb40
struct IPropertyManager_s00dd_cdc0 {
    V4(p0) V4(p1) V1(p2) V1(p3) V1(p4)                            // slots 0..10
    virtual bool GetPropertyList(uint32_t id, uint32_t group, IRef** out);   // +0x2c
};
IPropertyManager_s00dd_cdc0* PropertyManager_s00dd_cdc0();                              // 0x0067de30
bool GetPropertyAsUint32Array(IRef* list, uint32_t id, int* count, uint32_t** data);   // 0x006a0840
extern NameVec gNames0bb0;           // 0x016a0bb0
extern NameVec gNames0bc4;           // 0x016a0bc4
extern NameVec gNames0bd8;           // 0x016a0bd8
extern NameVec gNames0bec;           // 0x016a0bec
extern NameVec gNames0c00;           // 0x016a0c00
extern NameVec gNames0c14;           // 0x016a0c14
extern NameVec gNames0c28;           // 0x016a0c28
extern ValueVec gValues0b90; // 0x016a0b90
struct cModelSetup {
    uint32_t pad0[0x14 / 4];
    AutoRef<IModel> mModelC;         // +0x14
    AutoRef<IModel> mModelA;         // +0x18
    AutoRef<IModel> mModelB;         // +0x1c
    AutoRef<ILight> mLight;          // +0x20
    uint32_t pad24[(0x70 - 0x24) / 4];
    AutoRef<ILayer> mLayer;          // +0x70

    void Setup();
};
// ---- items of slice s00ddcdc0 end

// ---- items of slice s00ddf990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gInterfaceValue;
extern float gInterfaceBlend;
extern float gInterfaceAngle;
extern float gInterfaceAlpha;
extern float gInterfaceTargetX;
extern float gInterfaceTargetY;
extern float gInterfaceTargetZ;
extern float gInterfaceStep;
extern float gInterfaceSpeed;
#define nullptr 0
struct Vec3_s00dd_f990 {
    float mX;
    float mY;
    float mZ;
};
struct cMethodTable {
    void* mSlots[0x40];
};
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, uint32_t nArg2) {
        return ((void* (*)(void*, uint32_t, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1, nArg2);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, void* pArg1, int nArg2) {
        return ((void* (*)(void*, void*, int))mpMethods->mSlots[nSlot >> 2])(this, pArg1, nArg2);
    }
};
class cInterfaceState {
public:
    cInterfaceState(cDispatchObject* pTarget);
    ~cInterfaceState();
    bool ResetDefaults();
    void PushMatrix(uint32_t nKey);
    void UpdateTransition(unsigned int nElapsed, uint32_t nFlags);
    void UpdateFade(float fDelta);
    void UpdateSequence(int nDelta);
    void UpdateAlpha(int nDelta);
    void BeginSequence(uint8_t bFirst, uint8_t bSecond);
    void ResetSequence();
    void NotifySequence();
    bool IsIdle();

    uint32_t mpVftable;                         // 0x00
    int mnTimer;                                // 0x04
    uint8_t mPad08[0x18];                       // 0x08
    float mfValue20;                            // 0x20
    float mfValue24;                            // 0x24
    float mfValue28;                            // 0x28
    float mfValue2c;                            // 0x2c
    float mfValue30;                            // 0x30
    float mfTolerance;                          // 0x34
    float mfStart38;                            // 0x38
    float mfStart3c;                            // 0x3c
    uint8_t mbFlag40;                           // 0x40
    uint8_t mPad41[0x03];                       // 0x41
    float mfTo44;                               // 0x44
    float mfTo48;                               // 0x48
    float mfTo4c;                               // 0x4c
    float mfFrom50;                             // 0x50
    float mfFrom54;                             // 0x54
};
struct cInterfaceDefaults {
    float mfUnknown00;                          // 0x00
    float mfUnknown04;                          // 0x04
    float mfX;                                  // 0x08
    float mfY;                                  // 0x0c
    float mfZ;                                  // 0x10
};
extern cDispatchObject* gInterfaceNotifier;
extern cInterfaceDefaults gInterfaceFrom;
extern uint32_t gInterfaceTimer;
extern uint8_t gInterfaceStarted;
extern Vec3_s00dd_f990 gInterfaceCameraA;
extern Vec3_s00dd_f990 gInterfaceCameraB;
extern uint8_t gInterfaceVtable[0x40];
void* MessageServer();
void SetCameraPitch(float fPitch);
void SetCameraYaw(float fYaw);
void SetCameraRoll(float fRoll);
void SetCameraTransform(const float* pMatrix);
void ResetCameraNotifier(uint32_t nMode);
void InterpolateGlobals(float fAlpha);
void PostInterfaceMessage(uint32_t nId, int nValue);
// ---- items of slice s00ddf990 end

// @ 0x00dd0380
bool cMilitaryAttackCityOrder::OnTick(float)
{
    if (mVehiclesBegin == mVehiclesEnd)
        return false;
    cCity* pCity = mpCity;
    if (pCity == 0 || pCity->v2c())
        return false;
    if (mpCity->GetCivilization()->v2c())
        return false;
    if (CivModeStrategy()->IsValid()) {
        void* pPlayerCity = ((GameNounManagerObj*)NounManager())->GetPlayerCivilization();
        if (((cCity*)pPlayerCity)->mpSomething_44c == mpCity)
            return false;
    }
    if (mpCity->GetCivilization()->v4c() == mAttackerId)
        return false;

    bool bAnyTarget = false;
    bool bAnyCityOrder = false;
    cVehicle** it = mVehiclesBegin;
    cVehicle** pEnd = mVehiclesEnd;
    while (it != pEnd) {
        cVehicle* pVehicle = *it;
        cSpatialObject* pTarget = GetCurrentTarget(pVehicle);
        if (pTarget != 0) {
            pVehicle->SetTarget(pTarget->v08());
            if (pVehicle->mLocomotion != 2) {
                const cSPVector3_s00dd_0230& a = ((cSpatialObject*)pTarget->v08())->GetPosition();
                const cSPVector3_s00dd_0230& b = pVehicle->mLoco.GetPosition();
                float d = (float)sqrt(((double)a.z - b.z) * ((double)a.z - b.z)
                                    + ((double)a.y - b.y) * ((double)a.y - b.y)
                                    + ((double)a.x - b.x) * ((double)a.x - b.x));
                cCombatant* pCombatant = &pVehicle->mCombatant;
                if (pCombatant->GetStat() > d)
                    pCombatant->v50(pTarget);
            }
            bAnyTarget = true;
        } else {
            if (pVehicle->mpChaseTargetRef != 0) {
                cSpatialObject* pOld = pVehicle->mpChaseTargetRef;
                pVehicle->mpChaseTargetRef = 0;
                pOld->vc0();
            }
        }
        if (pVehicle->mLoco.v50())
            bAnyCityOrder = true;
        ++it;
    }
    if (!bAnyTarget)
        return false;
    if (bAnyCityOrder)
        mpCity->mDisplay.mFlags |= 0x800;
    return true;
}

// @ 0x00dd0550
uint32_t cMilitaryAttackCityOrder::GetCityBannerId()
{
    StarManagerObj* pStar = StarManager();
    if (pStar != 0 && mBanner_80 != 0)
        return pStar->GetBannerId(mBanner_80);
    return 0;
}

// @ 0x00dd0590
void* cMilitaryAttackCityOrder::QueryInterface(uint32_t type)
{
    if (type <= 0x93d55b46u) {
        if (type == 0x93d55b46u || type == 0x13d55dc8u || type == 0x13d6b42bu)
            return (char*)this - 0x10;
        goto fail;
    }
    if (type != 0xee3f516eu)
        goto fail;
    return ((char*)this - 0x10) != 0 ? (void*)this : 0;
fail:
    return 0;
}

// @ 0x00dd05e0
bool cMilitaryAttackCityOrder::IsInSimulatorContext()
{
    if (GetUniverseContext() == 1 || GetUniverseContext() == 2)
        return true;
    return false;
}

// @ 0x00dd0600
bool cMilitaryAttackCityOrder::IsActive()
{
    return ((cVGO_PredView*)this)->PredSlot3() != 0;
}

// @ 0x00dd0610
void* cMilitaryAttackCityOrder::QueryInterface2(uint32_t type)
{
    if (type <= 0x13d6b42bu) {
        if (type == 0x13d6b42bu || type == 0x5b6b834u || type == 0x13d55dc8u)
            return (char*)this - 0x10;
        goto fail;
    }
    if (type == 0x93d55b46u)
        return (char*)this - 0x10;
    if (type != 0xee3f516eu)
        goto fail;
    return ((char*)this - 0x10) != 0 ? (void*)this : 0;
fail:
    return 0;
}

// @ 0x00dd0650
uint32_t cMilitaryAttackCityOrder::GetIconKey()
{
    uint32_t mode = mMode;
    --mode;
    switch (mode) {
    case 0: return 0x9ea3031au;
    case 1: return 0x372e2c04u;
    case 3: return 0xccc35c46u;
    case 4: return 0x65672adeu;
    }
    return GetPaletteItemPriority();
}

// @ 0x00dd06a0
uint32_t cMilitaryAttackCityOrder::GetMissionKey()
{
    if (mMode == 1)
        return (mBanner_88 == 2) ? 0xfffff045u : (0xff577f34u + 0xfffff045u);
    if (mBanner_88 != 0xff576f79u && FUN_00b6e250())
        return FUN_00b6f0d0(mBanner_88);
    return 0xff576f79u;
}

// @ 0x00dd0710
void AssetDiscovery_Data::AssignFromScenario(void* pSrc, uint32_t owner)
{
    UI_ScenarioDataSrc* pScenario = (UI_ScenarioDataSrc*)pSrc;
    if (pScenario->mpPayload != 0) {
        mpPayload = pScenario->mpPayload;
        mField_78 = pScenario->mpPayload->mpInner->mField00;
        mField_08 = pScenario->mpPayload->mpInner->mField04;
        mField_04 = pScenario->mpPayload->mpInner->mField08;
        mField_0c = pScenario->mpPayload->mpInner->mField0c;
        mField_7c = pScenario->mpPayload->mpInner->mField10;
        mField_80 = pScenario->mpPayload->mpInner->mField14;
        mField_84 = pScenario->mpPayload->mpInner->mField18;
        mField_88 = pScenario->mpPayload->mpInner->mField1c;
        mpField_94 = pScenario->mpPayload->mpInner->mpField24;
        mField_90 = pScenario->mpPayload->mpInner->mField2c;
        vC4();
        vA4(owner);
        vA8();
    }
    vAC(owner);
}

// @ 0x00dd07f0
void AssetDiscovery_Data::UpdateEnumValue()
{
    UI_ScenarioPayload* pPayload = mpPayload;
    if (pPayload == 0)
        return;
    if (pPayload->mpInner->mField10 == 6) {
        mEnumValue = -2;
        return;
    }
    mEnumValue = 3;
    uint32_t state = pPayload->mpInner->mField20;
    if (state == 0xffffffffu) {
        mEnumValue = -3;
        return;
    }
    switch (mField_84) {
    case 1:
        switch (state) {
        case 1: mEnumValue = 2; return;
        case 6: case 7:
            {
                unsigned char r = FUN_004eb930(FUN_004df400(FUN_00401090(&mField_04)));
                mEnumValue = (-(uint32_t)(r != 0) & 0x7ffffffau) + 5;
            }
            return;
        case 0: case 3: mEnumValue = 3; return;
        case 2: mEnumValue = 1; return;
        case 4: mEnumValue = 4; return;
        case 5: mEnumValue = 0; return;
        default: return;
        }
    case 2: case 4: case 5:
        switch (state) {
        case 0: mEnumValue = 0; return;
        case 1: mEnumValue = 1; return;
        case 2: mEnumValue = 3; return;
        case 3: mEnumValue = 4; return;
        case 4:
            mEnumValue = (-(uint32_t)(mField_88 != 0x53dbcf1u) & 0x80000006u) + 0x7fffffffu;
            return;
        default: return;
        }
    }
}

// @ 0x00dd0940
uint32_t AssetDiscovery_Data::GetAvatarName()
{
    void* p = vB8();
    if (p != 0) {
        uint32_t* pRef = ((AvatarNameObj*)p)->GetName();
        return *pRef;
    }
    return 0;
}

// @ 0x00dd0960
uint32_t AssetDiscovery_Data::GetCreatureName()
{
    uint32_t result = 0;
    void* p = vB8();
    if (p != 0) {
        void* q = FUN_00b8de30(p);
        if (q != 0) {
            uint32_t* pRef = (uint32_t*)FUN_00bb9de0(q);
            result = *pRef;
        }
    }
    return result;
}

// @ 0x00dd0990
void AssetDiscovery_Data::GetSceneKey(uint32_t* pOut)
{
    uint32_t mode = mField_84;
    pOut[0] = 0;
    pOut[1] = 0x2f7d0004u;
    pOut[2] = 0xca14de92u;
    switch (mode) {
    case 1: pOut[0] = 0xe04dd8b1u; return;
    case 2: pOut[0] = 0x3f185edbu; return;
    case 4: pOut[0] = 0xdc1b3879u; return;
    case 5: pOut[0] = 0x89b74761u; return;
    }
}

// @ 0x00dd0a00
uint32_t* AssetDiscovery_Data::GetSceneKeyOut(uint32_t* pOut)
{
    pOut[0] = 0;
    pOut[1] = 0;
    pOut[2] = 0;
    void* p = vB8();
    if (p != 0) {
        uint32_t* pv = (uint32_t*)FUN_00b8d8e0(p);
        SceneKey* pk = (SceneKey*)pOut;
        *(SceneKey*)pOut = *(SceneKey*)pv;
        pk->mId = 0x2f7d0004u;
        pk->mFlags = (pk->mFlags & 0xffffff01u) | 1u;
    }
    IResourceManager* pMgr = (IResourceManager*)ResourceManager();
    if (!pMgr->LoadKey(pOut, 0, 0, 0, 0, 0)) {
        IPropertyHandle* prop = 0;
        IPropertyManager* pm = (IPropertyManager*)PropertyManager();
        if (prop != 0) {
            IPropertyHandle* pOld = prop;
            prop = 0;
            pOld->Release();
        }
        pm->GetProperty(0x120b89ceu, (void**)&prop);
        GetPropertyAsKey(prop, 0x287652bu, pOut);
        if (prop != 0)
            prop->Release();
    }
    return pOut;
}

// @ 0x00dd0ac0
uint32_t* AssetDiscovery_Data::GetStatKeyOut(uint32_t* pOut)
{
    IPropertyHandle* prop = 0;
    IPropertyManager* pm = (IPropertyManager*)PropertyManager();
    if (prop != 0) {
        IPropertyHandle* pOld = prop;
        prop = 0;
        pOld->Release();
    }
    pm->GetProperty(0x120b89ceu, (void**)&prop);
    pOut[0] = 0;
    pOut[1] = 0;
    pOut[2] = 0;
    GetPropertyAsKey(prop, 0x1a0553ceu, pOut);
    if (prop != 0)
        prop->Release();
    return pOut;
}

// @ 0x00dd0b30
uint64_t AssetDiscovery_Data::GetField78()
{
    return mField_78;
}

// @ 0x00dd0b50
void* AssetDiscovery_Data::ConstructBase()
{
    TimelineSporepediaCardData_Ctor(this);
    float fMinusOne = gMinusOneFloat;
    mField_78 = 0;
    mField_7c = 0;
    mField_84 = 0;
    mField_88 = 0;
    mpPayload = 0;
    ((void**)this)[0] = (void*)0x147c9f8;
    ((void**)this)[4] = (void*)0x147c9e8;
    ((void**)this)[5] = (void*)0x147cc78;
    mField_80 = 0xffffffffu;
    mEnumValue = 0x7fffffff;
    mField_90 = fMinusOne;
    return this;
}

// @ 0x00dd0c00
void AssetDiscovery_DataCStr::AssignCityName(eastl_wstring* pOut)
{
    EmpiresObj* pEmpire = StarManager()->GetEmpireByID((uint32_t)(uintptr_t)mpField_94);
    if (pEmpire == 0)
        return;
    CivNameSource* pSrc = (CivNameSource*)pEmpire->GetCities();
    const wchar_t* first = pSrc->mpName;
    const wchar_t* pIt = first;
    while (*pIt)
        ++pIt;
    pOut->Assign(first, first + (pIt - first));
}

// @ 0x00dd0c50
void* __cdecl CreateAssetDiscoveryDataTag()
{
    AssetDiscovery_Data* p = (AssetDiscovery_Data*)operator new(0x9c, "Spui", 0, 0, 0, 0);
    if (p != 0) {
        p->ConstructBase();
        ((void**)p)[0] = (void*)0x147cac0;
        ((void**)p)[4] = (void*)0x147cc88;
        ((void**)p)[5] = (void*)0x147cc78;
        return p;
    }
    return 0;
}

// @ 0x00dd0ca0
void* AssetDiscovery_DataCStr::ConstructString()
{
    ConstructBase();
    ((void**)this)[0] = (void*)0x147cbb0;
    ((void**)this)[4] = (void*)0x147cba0;
    ((void**)this)[5] = (void*)0x147cb90;
    mString.Construct();
    return this;
}

// @ 0x00dd0cf0
void* AssetDiscovery_DataCStr::Delete(unsigned char flags)
{
    ((void**)this)[0] = (void*)0x147cbb0;
    ((void**)this)[4] = (void*)0x147cba0;
    ((void**)this)[5] = (void*)0x147cb90;
    mString.~cString_s006b_47a0();
    ((void**)this)[0] = (void*)0x147c9f8;
    ((void**)this)[4] = (void*)0x147c9e8;
    ((void**)this)[5] = (void*)0x147cc78;
    TimelineSporepediaCardData_Dtor(this);
    if (flags & 1)
        operator delete[](this);
    return this;
}

// @ 0x00dd0d50
void* __cdecl CreateAssetDiscoveryData()
{
    AssetDiscovery_DataCStr* p = (AssetDiscovery_DataCStr*)operator new(0xb0, "Spui", 0, 0, 0, 0);
    if (p != 0) {
        p->ConstructBase();
        cString_s006b_47a0* pStr = &p->mString;
        ((void**)p)[0] = (void*)0x147cbb0;
        ((void**)p)[4] = (void*)0x147cba0;
        ((void**)p)[5] = (void*)0x147cb90;
        pStr->Construct();
        return p;
    }
    return 0;
}

// @ 0x00dd0da0
void* AssetDiscovery_Data::ConstructPlain()
{
    ConstructBase();
    ((void**)this)[0] = (void*)0x147c9f8;
    ((void**)this)[4] = (void*)0x147cc88;
    ((void**)this)[5] = (void*)0x147cc78;
    return this;
}

// @ 0x00dd0e10
const wchar_t* AssetDiscovery_DataCStr::GetDisplayText()
{
    eastl_wstring* pText = (eastl_wstring*)v0c();
    if (pText == 0)
        return 0;

    switch (mField_84) {
    case 1:
        {
            eastl_wstring local;
            local.mpBegin = gEmptyString16;
            local.mpEnd = gEmptyString16;
            local.mpCapacity = (void*)0x1667bae;
            if (mField_88 == 2) {
                local.Append(pText->mpBegin);
                mString.Load(0xad56080c, 0x95b72bu, 0, L"~Epic");
            } else if (mField_88 == 3) {
                local.Append(pText->mpBegin);
                mString.Load(0xad56080c, 0x94acb6f7u, 0, L"~MiniBoss");
            } else {
                return 0;
            }
            {
                IMgr67de40* pMgr = (IMgr67de40*)Mgr67de40();
                IPropertyHandle* pH = pMgr->v20();
                ((IHaveProp12*)pH)->GetPropertyAt12(&mString, 0, 1);
            }
            return mString.GetText();
        }
    case 2:
        {
            eastl_wstring local;
            WString_FromCStr(&local, pText->mpBegin);
            if (mField_88 == 0x53dbcf1u || mField_88 == 0x53dbcf3u)
                GetStringFromId(&local, mField_88, 0xe, &mString);
            else
                GetStringFromId(&local, mField_88, 0, &mString);
            local.DeallocateSelf();
            return mString.GetText();
        }
    case 4:
        {
            eastl_wstring local;
            WString_FromCStr(&local, pText->mpBegin);
            if (mField_88 == 0x53dbcf1u || mField_88 == 0x53dbcf3u)
                GetStringFromId(&local, mField_88, 0xd, &mString);
            else
                GetStringFromId(&local, mField_88, 1, &mString);
            local.DeallocateSelf();
            return mString.GetText();
        }
    case 5:
        {
            void* p = vB8();
            if (p == 0)
                return 0;
            FUN_00b8d8f0(p);
            void* q = FUN_00b8de30(p);
            if (q == 0)
                return 0;
            if ((uint32_t)(uintptr_t)FUN_00bb9ae0(q) != 5)
                return 0;
            void* pAvatar = GameNounManager_GetAvatar(q);
            void* pStar = StarManager();
            void* pCiv = StarManager_GetEmpireByID(pStar, (uint32_t)(uintptr_t)pAvatar);
            if (pCiv == 0)
                return 0;
            return *(const wchar_t**)CivData_GetCities(pCiv);
        }
    }
    return pText->mpBegin;
}

// @ 0x00dd1070
bool AssetDiscovery_Data::CollectTerrainKeys(eastl_u32vec* pOut)
{
    if (mEnumValue == 0x7fffffff) {
        if (mField_08 == 0x2b978c46u) {
            void* pSphere = ((NounObj*)NounManager())->GetTerrainSphere();
            uint32_t v;
            if ((int)mField_84 >= 1)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0xa426730bu);
            else
                v = 0;
            pOut->push_back(v);
            if ((int)mField_84 >= 2)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0xad56080cu);
            else
                v = 0;
            pOut->push_back(v);
            if ((int)mField_84 >= 4)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0xf71fa311u);
            else
                v = 0;
            pOut->push_back(v);
            if ((int)mField_84 >= 5)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0xbeb528cbu);
            else
                v = 0;
            pOut->push_back(v);
            if ((int)mField_84 >= 5)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0x2db6dad3u);
            else
                v = 0;
            pOut->push_back(v);
            return true;
        }
    } else if (mEnumValue != -3) {
        return false;
    }
    return CollectTerrainKeysBase(pOut);
}

// @ 0x00dd1240
void SomeObj::SetKeyAgain(uint32_t)
{
    mKey_28 = 0x1510d07u;
    mFlag_2c = 1;
}

// @ 0x00dd9750
void Swarm::FUN_00dd9750(Boid* e)
{
    LARGE_INTEGER li;
    if (e->mTimer.mMode == 1) {
        li.QuadPart = (long long)__rdtsc();
        e->mTimer.mLo = li.u.LowPart;
    } else {
        QueryPerformanceCounter(&li);
        e->mTimer.mLo = li.u.LowPart;
    }
    e->mTimer.mZ2 = 0;
    e->mTimer.mZ1 = 0;
    e->mTimer.mHi = (unsigned int)li.u.HighPart;
}

// @ 0x00dd97a0
bool Swarm::FUN_00dd97a0(Boid* p, int unused)
{
    bool r = true;
    p->mV18 = Vec3(0.0f, 0.0f, 0.0f);
    p->mV24 = Vec3(0.0f, 0.0f, 0.0f);
    p->mM48[2] = g_m48;
    EA::Stopwatch_s00dd_9510* w = (EA::Stopwatch_s00dd_9510*)&p->mTimer;
    if ((double)w->GetElapsedTimeFloat() * w->mfCoefficient > 1.0) {
        g_16a0b04 = r;
    }
    return r;
}

// @ 0x00dd9860
bool Swarm::FUN_00dd9860(Boid* b, int unused)
{
    bool r = true;
    float dx = b->mV30.x - b->mPos.x;
    float dy = b->mV30.y - b->mPos.y;
    float dz = b->mV30.z - b->mPos.z;
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
    if (10.0f > dist) {
        b->mC8 = 3;
        ((EA::Stopwatch_s00dd_9510*)&b->mTimer)->Restart();
        r = false;
    }
    float f = 0.5f;
    if (b->mFC == 0) {
        f = 0.2f;
    }
    b->mV24.x = ((b->mV3C.x + b->mV30.x) * 0.5f - b->mPos.x) * f;
    b->mV24.y = ((b->mV3C.y + b->mV30.y) * 0.5f - b->mPos.y) * f;
    b->mV24.z = ((b->mV3C.z + b->mV30.z) * 0.5f - b->mPos.z) * f;

    float ax = b->mV3C.x - b->mV30.x;
    float ay = b->mV3C.y - b->mV30.y;
    float az = b->mV3C.z - b->mV30.z;
    float t = 1.0f - dist / sqrtf((az * az + ay * ay) + ax * ax);

    if (b->mFC != 0) {
        float f3 = g_16a1078;
        if (b->mD6 != b->mD7) {
            f3 = 0.05f;
        }
        b->m98 = 1.0f;
        if (f3 <= t) {
            if ((1.0f - f3 < t) && b->mD7 != 0) {
                b->m98 = (1.0f - (t - (1.0f - f3)) / f3) * 0.8f + 0.2f;
            }
        } else if (b->mD6 != 0) {
            b->m98 = (t / f3) * 0.8f + 0.2f;
            b->m98 = b->m98 * 5.0f;
            return r;
        }
        t = b->m98;
    }
    b->m98 = t * 5.0f;
    return r;
}

// @ 0x00dd9a10
void Swarm::FUN_00dd9a10(Boid* b)
{
    b->m9C = sqrtf((b->mV3C.x * b->mV3C.x + b->mV3C.y * b->mV3C.y) + b->mV3C.z * b->mV3C.z);
    b->mA0 = sqrtf((b->mV30.x * b->mV30.x + b->mV30.y * b->mV30.y) + b->mV30.z * b->mV30.z);

    float px = b->mPos.x, py = b->mPos.y, pz = b->mPos.z;
    float ax = b->mV30.x, ay = b->mV30.y, az = b->mV30.z;
    float inv1 = 1.0f / sqrtf((px * px + py * py) + pz * pz + 1e-08f);
    float inv2 = 1.0f / sqrtf((ax * ax + ay * ay) + az * az + 1e-08f);
    float nx1 = px * inv1, ny1 = py * inv1, nz1 = pz * inv1;
    float nx2 = ax * inv2, ny2 = ay * inv2, nz2 = az * inv2;

    float cross = nx1 * ny2 - ny1 * nx2;
    float dot = (nx1 * nx2 + ny1 * ny2) + nz1 * nz2;
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    float ang = (float)acos(dot);
    b->mA4 = ang;
    if (cross < 0.0f) {
        b->mA4 = -ang;
    }
    if (fabsf(b->mA4) < 0.01f) {
        b->mA4 = (b->mA4 >= 0.0f) ? 0.01f : -0.01f;
    }

    Start3dSoundByName(0x44f21a5d, (unsigned int)b->mD0, b->mPos.x, b->mPos.y, b->mPos.z);
}

// @ 0x00dd9c10
bool Swarm::FUN_00dd9c10(Boid* b, int unused)
{
    b->mV24.x = g_16a0b0c;
    b->mV24.y = g_16a0b10;
    b->mV24.z = g_16a0b14;

    float px = b->mPos.x, py = b->mPos.y, pz = b->mPos.z;
    float inv1 = 1.0f / sqrtf((px * px + py * py) + pz * pz + 1e-08f);
    float ux = px * inv1;
    float uy = py * inv1;
    float uz = pz * inv1;

    float ax = b->mV30.x, ay = b->mV30.y, az = b->mV30.z;
    float inv2 = 1.0f / sqrtf((az * az + ay * ay) + ax * ax + 1e-08f);
    float wx = ax * inv2;
    float wy = ay * inv2;
    float wz = az * inv2;

    float cross = wy * ux - uy * wx;
    float dot = (wx * ux + wy * uy) + wz * uz;
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    float ang = (float)acos(dot);
    if (cross < 0.0f) {
        ang = -ang;
    }

    float t = 1.0f - ang / b->mA4;
    float blend = (b->mA0 - b->m9C) * t + b->m9C;
    b->mPos.x = ux * blend;
    b->mPos.y = uy * blend;
    b->mPos.z = uz * blend;

    float e = b->mA4 * 0.5f;
    e = (ang - e) / e;
    if (e > 0.99f) {
        e = 0.99f;
    } else if (e < -1.0f) {
        b->mV18.x = g_16a0b0c;
        b->mV18.y = g_16a0b10;
        b->mV18.z = g_16a0b14;
        return false;
    }
    float s = 1.0f - fabsf(e);
    s = (s > 0.0f) ? sqrtf(s) : -sqrtf(-s);
    if (s >= 0.0f && s < 0.1f) {
        s = 0.1f;
    } else if (s <= 0.0f && -0.1f < s) {
        s = -0.1f;
    }

    float c1 = uz * g_16a0ba8 - uy * g_16a0bac;
    float c2 = uy * g_16a0ba4 - ux * g_16a0ba8;
    float c3 = ux * g_16a0bac - uz * g_16a0ba4;
    float inv3 = 1.0f / sqrtf((c3 * c3 + c2 * c2) + c1 * c1 + 1e-08f);
    float r1 = c1 * inv3;
    float r2 = c2 * inv3;
    float r3 = c3 * inv3;
    if (cross < 0.0f) {
        r1 = -r1;
        r2 = -r2;
        r3 = -r3;
    }
    b->mV18.x = (r1 * g_15a2cec) * s;
    b->mV18.y = (r3 * g_15a2cec) * s;
    b->mV18.z = (r2 * g_15a2cec) * s;

    Vec4 out;
    Vec4* q = MakeRotation((const Vec3*)&g_16a0ba4, &b->mV18, &out);
    b->mM48[0] = *q;

    if (g_16a1078 <= t) {
        float g = 1.0f;
        if (1.0f - g_16a1078 < t) {
            g = 1.0f - (t - (1.0f - g_16a1078)) / g_16a1078;
        }
        b->m98 = g;
    } else {
        b->m98 = t / g_16a1078;
    }
    b->m98 = b->m98 * 5.0f;
    return true;
}

// @ 0x00dda060
int Swarm::FUN_00dda060(int id)
{
    int n = 0;
    Boid** p = mpBegin;
    unsigned int c = (unsigned int)(mpEnd - mpBegin);
    if (c > 0) {
        do {
            if ((*p)->mFC == id) {
                ++n;
            }
            ++p;
            --c;
        } while (c != 0);
    }
    return n;
}

// @ 0x00dda090
void Swarm::FUN_00dda090(int id, char v)
{
    unsigned int c = (unsigned int)(mpEnd - mpBegin);
    unsigned int i = 0;
    if (c > 0) {
        do {
            Boid* e = mpBegin[i];
            if (e->mFC == id) {
                e->mD8 = v;
            }
            ++i;
        } while (i < c);
    }
}

// @ 0x00dda0d0
void Swarm::FUN_00dda0d0(int id)
{
    int zero = 0;
    unsigned int i = 0;
    unsigned int c = (unsigned int)(mpEnd - mpBegin);
    if (c > zero) {
        do {
            Boid* e = mpBegin[i];
            if (e->mFC == id) {
                e->mD5 = 1;
                Timer* w = &mpBegin[i]->mTimer;
                if (w->mMode == 1) {
                    unsigned long long t = __rdtsc();
                    w->mLo = (unsigned int)t;
                    w->mHi = (unsigned int)(t >> 32);
                } else {
                    LARGE_INTEGER li;
                    QueryPerformanceCounter(&li);
                    w->mLo = li.u.LowPart;
                    w->mHi = (unsigned int)li.u.HighPart;
                }
                w->mZ1 = zero;
                w->mZ2 = zero;
            }
            ++i;
        } while (i < c);
    }
}

// @ 0x00dda160
float Swarm::FUN_00dda160(const Vec3* p, int group)
{
    float best = -1.0f;
    unsigned int n = (unsigned int)(mpEnd - mpBegin);
    unsigned int i = 0;
    for (; i < n; ++i) {
        Boid* e = mpBegin[i];
        if (e->mFC == group) {
            float dy = e->mPos.y - p->y;
            float dx = e->mPos.x - p->x;
            float dz = e->mPos.z - p->z;
            float d2 = (dx * dx + dy * dy) + dz * dz;
            if (d2 < best || best < 0.0f) {
                best = d2;
            }
        }
    }
    return sqrtf(best);
}

// @ 0x00dda380
int Swarm::FUN_00dda380()
{
    int n = 0;
    Boid** p = mpBegin;
    unsigned int c = (unsigned int)(mpEnd - mpBegin);
    if (c > 0) {
        do {
            if ((*p)->mC8 == 100) {
                ++n;
            }
            ++p;
            --c;
        } while (c != 0);
    }
    return n;
}

// @ 0x00dda3b0
void CB::m3b0(char param_2)
{
    void* v = this->p18;
    if (param_2 == 0) {
        if (vc0_char(v, 0x138) != 0) {
            vc1_void(this->p1c, 0x134, 0);
            vc1_void(this->p14, 0x134, 0);
            vc1_void(this->p18, 0x134, 0);
            vc1_void(FUN_0067dd50(), 0x50, 0x14);
            vc1_void(FUN_0067dd50(), 0x50, 0x0d);
            vc1_void(FUN_0067dd50(), 0x50, 0x1a);
            return;
        }
    } else {
        if (vc0_char(v, 0x138) == 0) {
            vc1_void(this->p1c, 0x134, 1);
            vc1_void(this->p18, 0x134, 1);
            vc1_void(this->p14, 0x134, 1);
            vc1_void(FUN_0067dd50(), 0x4c, (int)vc2_ret(this->p18, 0x13c, 0x14, 0));
            vc1_void(FUN_0067dd50(), 0x4c, (int)vc2_ret(this->p14, 0x13c, 0x0d, 0));
            vc1_void(FUN_0067dd50(), 0x4c, (int)vc2_ret(this->p1c, 0x13c, 0x1a, 0));
        }
    }
}

// @ 0x00dda500
void FUN_00dda500(void* edi)
{
    void* p = FUN_0067dd10();
    p = vc0_ret(p, 0x50);
    p = vc0_ret(p, 0x38);
    int iv = 0;
    if (p != 0) {
        vc1_ret(p, 0x0c, 0x7ba6612);
        iv = (int)vc1_ret(p, 0x0c, 0x7ba65f3);
    }

    Q q;
    q.a = 0;
    q.b = 0;
    q.x = DAT_016a0b0c;
    q.y = DAT_016a0b10;
    q.z = DAT_016a0b14;
    q.w = 1.0f;
    ((Matrix3*)q.m)->Assign(DAT_016a0b28);

    if (iv != 0) {
        ((IvObj*)iv)->FUN_00dde590(&q);
        float r = 1.0f / sqrt(q.x * q.x + q.y * q.y + q.z * q.z + 1e-8f);
        float v1 = q.y * r * DAT_016a0bac - q.z * r * DAT_016a0ba8;
        float v2 = q.z * r * DAT_016a0ba4 - DAT_016a0bac * q.x * r;
        float v3 = DAT_016a0ba8 * q.x * r - q.y * r * DAT_016a0ba4;
        if (0.01 < sqrt(v1 * v1 + v2 * v2 + v3 * v3)) {
            float* s = FUN_00dd91b0();
            float* out = (float*)((char*)edi + 0x48);
            out[0] = s[0];
            out[1] = s[1];
            out[2] = s[2];
            out[3] = s[3];
        }
    }
}

// @ 0x00dda6d0
void __stdcall FUN_00dda6d0(CObj* param_1)
{
    int n = 0;
    float fx, fy;
    unsigned z;
    float local[3];
    while (1) {
        float* pf = FUN_00dd93d0();
        fy = pf[1];
        fx = pf[0];
        z = 0xc4160000u;                // local[2] = -600.0f  (kept as raw bits below)
        local[0] = fx;
        local[1] = fy;
        local[2] = *(float*)&z;
        if (35.0f <= sqrt(pf[2] * pf[2] + fx * fx + fy * fy) &&
            30.0f <= DAT_016a0b08->FUN_00dda160(local, 0))
            break;
        n = n + 1;
        if (999 < n)
            return;
    }
    if (n < 1000) {
        double t = G_TIMER->FUN_009360d0();
        double v = (t + 1.0) * 20.0;
        float f;
        if (10.0 <= v)
            f = 10.0f;
        else if (5.0 <= v)
            f = (float)v;
        else
            f = 5.0f;
        param_1->e0 = f;
        param_1->f0c = fx;
        param_1->f10 = fy;
        param_1->d5 = 0;
        *(unsigned*)&param_1->f14 = z;
        float r = FUN_00572a10(DAT_016a0fd8, DAT_016a0fe8);
        param_1->fa8 = r;
        param_1->f98 = r;
        param_1->dc = FUN_00572a10(DAT_016a1028, DAT_016a1018);
    }
}

// @ 0x00dda920
ObjA* ObjA::FUN_00dda920()
{
    p00 = 0;
    f04 = 0;
    f08 = 0;
    p14 = 0;
    p18 = 0;
    p1c = 0;
    p20 = 0;
    p24 = 0;
    f28 = 0;
    f2c = 0;
    _ReadWriteBarrier();
    w38 = 0;
    w3a = 0;
    f3c = DAT_016a0b0c;
    f40 = DAT_016a0b10;
    f44 = DAT_016a0b14;
    f48 = 1.0f;
    m4c.copy(DAT_016a0b28);
    p70 = 0;
    return this;
}

// @ 0x00dda9a0
void ObjA::FUN_00dda9a0()
{
    Rel* r70 = p70;
    if (r70 != 0)
        r70->vf1();
    if (p24 != 0 && *(int*)((char*)p24 - 4) != 0)
        EASTL_allocator_deallocate(p24);
    Rel* r20 = p20;
    if (r20 != 0)
        r20->vf1();
    Rel* r1c = p1c;
    if (r1c != 0)
        r1c->vf1();
    Rel* r18 = p18;
    if (r18 != 0)
        r18->vf1();
    Rel* r14 = p14;
    if (r14 != 0)
        r14->vf1();
    if (p00 != 0 && *(int*)((char*)p00 - 4) != 0)
        EASTL_allocator_deallocate(p00);
}

// @ 0x00ddaa20
void FUN_00ddaa20(void* self, void* arg)
{
    if (arg == 0)
        return;

    void* r = ((void*(__thiscall*)(void*, int, void*))VSLOT(self, 0xa8))(self, -1, arg);
    if (r == 0)
        return;

    void* sub = *(void**)((char*)r + 8);

    Q q;
    q.a = 0;
    q.b = 0;
    q.x = DAT_016a0b0c;
    q.y = DAT_016a0b10;
    q.z = DAT_016a0b14;
    q.w = 1.0f;
    ((Matrix3*)q.m)->Assign(DAT_016a0b28);

    Q q2;
    q2.a = 0;
    q2.b = 0;
    q2.x = 0.0f;
    q2.y = 0.0f;
    q2.z = 0.0f;
    q2.w = 1.0f;
    ((Dest*)&q)->FUN_006bac90(&q2);
    ((Dest*)&q2)->FUN_006b9440(sub);
}

// @ 0x00ddab10
char __stdcall FUN_00ddab10(CObj* p, float dt)
{
    float f7 = p->f4c;
    float f1 = p->f48;
    float ang = p->dc * DAT_016a0b58 * dt * 0.5f;
    float s = sin(ang);
    float c = cos(ang);
    float a = p->ec * s;
    float b = p->e8 * s;
    float d = p->f0 * s;
    float f2 = p->f50;
    float f3 = p->f54;
    p->f48 = f3 * b + c * f1 + (f7 * d - f2 * a);
    p->f4c = f3 * a + f7 * c + (f2 * b - d * f1);
    p->f50 = f3 * d + f2 * c + (a * f1 - f7 * b);
    p->f54 = p->f54 * c - (f2 * d + f7 * a + f1 * b);

    float len = p->f0c * p->f0c + p->f10 * p->f10 + p->f14 * p->f14;
    if (1.0f < len) {
        float inv = DAT_016a0ff8 / len;
        float x = p->f0c;
        float n = 1.0f / sqrt(x * x + p->f10 * p->f10 + p->f14 * p->f14 + 1e-8f);
        p->f24 = -(x * n) * inv;
        p->f28 = -(p->f10 * n) * inv;
        p->f2c = -(p->f14 * n) * inv;
    }
    FUN_00dd9080();
    return 1;
}

// @ 0x00ddada0
int __stdcall FUN_00ddada0(CObj* p, float dt)
{
    float f1 = p->f4c;
    float f2 = p->f48;
    float ang = p->dc * DAT_016a0b58 * dt * 0.5f;
    float s = sin(ang);
    float c = cos(ang);
    float a = p->ec * s;
    float d = p->f0 * s;
    float f3 = p->f50;
    float b = s * p->e8;
    float f4 = p->f54;
    p->f48 = f4 * b + f2 * c + (f1 * d - f3 * a);
    p->f4c = f4 * a + f1 * c + (f3 * b - f2 * d);
    p->f50 = f4 * d + f3 * c + (f2 * a - f1 * b);
    p->f54 = p->f54 * c - (f3 * d + f1 * a + f2 * b);

    if (p->e0 <= p->f14 && p->f14 != p->e0)
        FUN_00dda6d0(p);
    return 1;
}

// @ 0x00ddaf70
void* FUN_00ddaf70(void* param_1, int param_2)
{
    Vec12 v;
    v.b = 0;
    v.e = 0;
    v.c = 0;
    void* obj = FUN_0067cb40();

    S9 t1, t2;
    ((Dest*)&t1)->FUN_00558830(0);
    ((Dest*)&t2)->FUN_00558960(0x2dc9d1e, 0, param_2);

    CB34 fn = (CB34)VSLOT(obj, 0x34);
    fn(obj, &v, t1, t2);
    ((Dest*)&t2)->FUN_004e39a0(0, 0);
    ((Dest*)&t1)->FUN_004e39a0(0, 0);

    if (v.b == v.e) {
        *(int*)param_1 = 0;
        ((int*)param_1)[1] = 0;
        ((int*)param_1)[2] = 0;
        if (v.b != 0 && *(int*)(v.b - 4) != 0)
            EASTL_allocator_deallocate(v.b);
    } else {
        unsigned n = (unsigned)G_TIMER->FUN_00a68fb0(0x7fffffff);
        n = n % (unsigned)((v.e - v.b) / 0xc);
        char* src = v.b + n * 0xc;
        ((int*)param_1)[0] = ((int*)src)[0];
        ((int*)param_1)[1] = ((int*)src)[1];
        ((int*)param_1)[2] = ((int*)src)[2];
        if (v.b != 0 && *(int*)(v.b - 4) != 0)
            EASTL_allocator_deallocate(v.b);
    }
    return param_1;
}

// @ 0x00ddbe40
void Swarm_s00dd_be40::SpawnOne()
{
    KeyVec keys = { 0, 0, 0 };
    g_resMgr->tree.GetKeys(&keys);
    if (keys.mpBegin != keys.mpEnd)
    {
        uint n = (uint)(keys.mpEnd - keys.mpBegin);
        if (g_nextKey >= n)
            g_nextKey = 0;
        Key kB = { 0, 0, 0 };
        Key kA = { 0, 0, 0 };
        SplitKey(keys.mpBegin + g_nextKey, &kA, &kB);
        Resource* resA = mpMgr->Create(kA.a, kA.c, 0);
        if (resA)
        {
            resA->mRef++;
            resA->mFlags |= 0x12;

            TransformDesc* td = new("Simulator", 0, 0, 0, 0) TransformDesc();
            td->mRow[0] = MakeV4(1.0f, 0.0f, 0.0f, 0.0f);
            td->mRow[1] = MakeV4(0.0f, 1.0f, 0.0f, 0.0f);
            td->mRow[2] = MakeV4(0.0f, 0.0f, 1.0f, 0.0f);
            td->mRow[3] = MakeV4(0.0f, 0.0f, 0.0f, 1.0f);

            HolderObj* holder = new("Simulator", 0, 0, 0, 0) HolderObj();
            TransformDesc* pTd = td;
            holder->mVec.push_back(pTd);
            mpMgr->Attach(resA, holder, -1);

            Boid_s00dd_be40* boid = new("Simulator", 0, 0, 0, 0) Boid_s00dd_be40();
            Boid_s00dd_be40* pBoid = boid;
            boid->mResA = resA;
            boid->mFC = 0;
            boid->mResB = mpMgr->Create(kB.a, kB.c, 0);
            boid->mResB->mRef++;
            boid->mWatch.SetUnits(5);
            boid->mC8 = 0;
            boid->mD5 = 0;
            boid->mCC = 0;
            boid->mpF8 = &g_boidGlobal;
            boid->mAxis = g_v0ba4;
            boid->mD0 = 0;
            boid->mV18 = g_v0b0c;
            boid->mV24 = g_v0b0c;
            boid->mV30 = g_v0b0c;

            IEff* eff = 0;
            if (g_effectName.mpBegin != g_effectName.mpEnd)
            {
                EffectsMgr* em = EffectsManager();
                em->Find(FNV1_String16(g_effectName.mpBegin, 0x811c9dc5, 1), 0, &eff);
                if (eff)
                {
                    eff->Slot0();
                    eff->Slot2(0);
                }
            }
            boid->mEffect = eff;

            float half = g_angle * 0.5f;
            float s = sinf(half);
            float c = cosf(half);
            boid->mRot = MakeQuat(s * g_axis.x, s * g_axis.y, s * g_axis.z, c);

            float half2 = RandomFloatRange(0.0f, g_maxAngle) * 0.5f;
            float s2 = sinf(half2);
            float c2 = cosf(half2);
            Quat q2 = MakeQuat(boid->mAxis.x * s2, boid->mAxis.y * s2, boid->mAxis.z * s2, c2);
            Quat tmp;
            boid->mRot.Assign(QuatMul(&tmp, &boid->mRot, &q2));

            int cnt = 0;
            Vec3_s00dd_be40 off;
            float len;
            do
            {
                boid->mPos = *RandomOffset(&off);
                len = sqrtf((boid->mPos.x * boid->mPos.x + boid->mPos.y * boid->mPos.y) + boid->mPos.z * boid->mPos.z);
                boid->mPos.z = RandInline(-600.0f, boid->mE0);
            } while (len < k_min35 && FindNearest(&boid->mPos, 0) < 30.0f && cnt++ < 1000);

            boid->mE0 = RandomFloatRange(0.0f, g_maxE0);
            float r = RandomFloatRange(g_scaleLo, g_scaleHi);
            boid->mA8 = r;
            boid->m98 = r;
            boid->mD4 = 0;
            boid->mDC = RandomFloatRange(g_dLo, g_dHi);
            boid->mV18.x = 0.0f; boid->mV18.y = 0.0f; boid->mV18.z = g_z;
            push_back(pBoid);
        }
        else
        {
            g_resMgr->tree.Remove(keys.mpBegin + g_nextKey);
        }
        g_nextKey++;
    }
}

// @ 0x00ddc6d0
void Swarm_s00dd_be40::FUN_00ddc6d0(uint32_t ticks)
{
    float cap = 0.2f;
    float secs = ticks * 0.001;
    float& step = (secs <= cap) ? secs : cap;      // min(secs, cap), taken by reference
    mpTimer->SetStep(step, 0);

    if ((g_scanInit & 1) == 0)
    {
        g_scanInit |= 1;
        g_scanList.mpBegin = 0;
        g_scanList.mpEnd = 0;
        g_scanList.mpCapacity = 0;
        atexit(FUN_013c5f50);
    }

    unsigned count = (unsigned)(mpEnd - mpBegin);
    for (unsigned i = 0; i < count; ++i)
    {
        Boid_s00dd_be40* b = mpBegin[i];
        if (!FUN_00ddb0d0(b, ticks))
            g_scanList.push_back(b);
    }

    count = (unsigned)(g_scanList.mpEnd - g_scanList.mpBegin);
    for (unsigned i = 0; i < count; ++i)
        FUN_00ddb600(g_scanList.mpBegin[i]);

    // the scratch list's own erase(mpBegin, mpEnd): nothing shifts, only mpEnd moves back
    Boid_s00dd_be40** first = g_scanList.mpBegin;
    Boid_s00dd_be40** last  = g_scanList.mpEnd;
    memcpy(first, last, 0);
    g_scanList.mpEnd = g_scanList.mpEnd - (last - first);
}

// @ 0x00ddc820
void Swarm_s00dd_be40::FUN_00ddc820(uint32_t key)
{
    unsigned count = (unsigned)(mpEnd - mpBegin);
    SPVec4<Boid_s00dd_be40*> hits = { 0, 0, 0 };
    for (unsigned i = 0; i < count; ++i)
    {
        if (mpBegin[i]->mFC == key)
            hits.push_back(mpBegin[i]);
    }
    for (Boid_s00dd_be40** it = hits.mpEnd; it != hits.mpBegin; )
    {
        --it;
        FUN_00ddb600(*it);
    }
    if (hits.mpBegin != 0 && hits.mpBegin[-1] != 0)
        operator delete[](hits.mpBegin);
}

// @ 0x00ddc8d0
void FUN_00ddc8d0()
{
    if (g_objA != 0)
    {
        g_objA->FUN_00ddb790();
        if (g_objA != 0)
        {
            ObjA_s00dd_be40* p = g_objA;
            g_objA->FUN_00dda9a0();
            operator delete[](p);
        }
        g_objA = 0;
    }
}

// @ 0x00ddd1a0
void cModelSetup::Setup()
{
    IModelMgr* modelMgr = ModelManager();
    ILightMgr* lightMgr = LightingManager();
    mLight = lightMgr->GetLight(0x07b6877f, 0, 0);
    mLight->SetName(0x74d2735b);

    mModelA = modelMgr->GetModel(0x07b6877e, 0, 0);
    IModelWorld* w1 = ModelWorld(); w1->SetModelType(mModelA->GetModelType(0x14, 0));
    mModelA->SetFlag(1);
    mModelA->Attach(mLight.mp, 0, 1);

    mModelB = modelMgr->GetModel(0x07d23d15, 0, 0);
    IModelWorld* w2 = ModelWorld(); w2->SetModelType(mModelB->GetModelType(0x1a, 0));
    mModelB->SetFlag(1);
    mModelB->Attach(mLight.mp, 0, 1);

    mModelC = modelMgr->GetModel(0x07d23d13, 0, 0);
    IModelWorld* w3 = ModelWorld(); w3->SetModelType(mModelC->GetModelType(0xd, 0));
    mModelC->SetFlag(1);
    mModelC->Attach(mLight.mp, 0, 1);

    mLayer = LayerManager()->GetLayer(kLayerName);
    mLayer->AddModel(mModelA.mp, 1, 1, 1, 0);

    const char** n;
    gNames0bb0.clear();
    n = &gName15a2dc8; gNames0bb0.push_back(n);
    gNames0bd8.clear();
    n = &gName15a2dcc; gNames0bd8.push_back(n);
    gNames0bec.clear();
    n = &gName15a2dd4; gNames0bec.push_back(n);
    gNames0c00.clear();
    n = &gName15a2dd8; gNames0c00.push_back(n);
    gNames0c14.clear();
    n = &gName15a2db4; gNames0c14.push_back(n);
    n = &gName15a2ddc; gNames0c14.push_back(n);
    n = &gName15a2dbc; gNames0c14.push_back(n);
    gNames0c28.clear();
    n = &gName15a2dc8; gNames0c28.push_back(n);
    n = &gName15a2db0; gNames0c28.push_back(n);
    gNames0bc4.clear();
    n = &gName15a2dd0; gNames0bc4.push_back(n);

    ConstraintVec query;
    query.push_back(SP::FunctionalMatch::Constraint_s00dd_cdc0(0x02dd90af, SP::FunctionalMatch::kEquals_s00dd_cdc0, 0x2b978c46));
    query.push_back(SP::FunctionalMatch::Constraint_s00dd_cdc0(0x54a32960, SP::FunctionalMatch::kEquals_s00dd_cdc0, 1));
    KeyVec_s00dd_cdc0 results;
    ObjectTemplateDB()->FindAssets(results, query);

    AutoRef<IRef> propList;
    if (PropertyManager_s00dd_cdc0()->GetPropertyList(gPropKey, 0, propList.AsOutParam())) {
        int count;
        uint32_t* data;
        if (GetPropertyAsUint32Array(propList.mp, 0x7a35112f, &count, &data)) {
            gValues0b90.clear();
            for (int i = 0; i < count; ++i)
                gValues0b90.push_back(data[i]);
        }
    }
}

// @ 0x00ddf990
cInterfaceState::cInterfaceState(cDispatchObject* pTarget)
{
    mpVftable = 0;
    mnTimer = 0;
    mfValue20 = 1.0f;
    mfValue24 = 0.0f;
    mfValue28 = 0.0f;
    mfValue2c = -1.0f;
    mfValue30 = -1.0f;
    mfTolerance = 0.0f;
    mfStart38 = -1.0f;
    mfStart3c = -1.0f;
    mfTo44 = 0.001f;
    mfTo48 = 20.0f;
    mfTo4c = 0.0f;
    mfFrom50 = 0.0f;
    mfFrom54 = 0.0f;
    mbFlag40 = 0;

    (void)pTarget;

    gInterfaceSpeed = 0.01f;
    gInterfaceFrom.mfX = 0.0f;
    gInterfaceFrom.mfY = 0.0f;
    gInterfaceFrom.mfZ = 0.0f;
    gInterfaceValue = 0.0f;
    gInterfaceBlend = 0.0f;
    gInterfaceAngle = 0.0f;
    gInterfaceTimer = 20;

    if (gInterfaceNotifier != nullptr)
        ResetCameraNotifier(0);
}

// @ 0x00ddfaa0
cInterfaceState::~cInterfaceState()
{
    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x04);
}

// @ 0x00ddfaf0
bool cInterfaceState::ResetDefaults()
{
    Vec3_s00dd_f990 position;
    position.mX = 0.0f;
    position.mY = 0.0f;
    position.mZ = -100.0f;
    gInterfaceCameraA = position;
    gInterfaceCameraB = position;
    gInterfaceNotifier = (cDispatchObject*)&gInterfaceVtable[0];
    return false;
}

// @ 0x00ddfbe0
void cInterfaceState::UpdateTransition(unsigned int nElapsed, uint32_t nFlags)
{
    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x00, nElapsed, nFlags);

    float fTime = (float)nElapsed;
    mfValue20 = ((gInterfaceTargetX - mfValue20) * fTime) * 0.001f + mfValue20;
    mfValue24 = ((gInterfaceAngle - mfValue24) * fTime) * 0.01f + mfValue24;

    if (mbFlag40 != 0) {
        gInterfaceAlpha = ((gInterfaceTargetX - mfValue20) * gInterfaceSpeed) * 0.0025f;
        gInterfaceTargetZ = -(((gInterfaceAngle - mfValue24) * gInterfaceStep) * 0.0025f);
    }

    cDispatchObject* pAudio = (cDispatchObject*)MessageServer();
    if (pAudio != nullptr) {
        pAudio->Call(0x38, 0x3cdd1a9);
        pAudio->Call(0x40, 0x34753a7, 0x6f62c88d);
        pAudio->Call(0x3c, 0x34753aa);
        pAudio->Call(0x58);
    }

    if (0.0f < mfValue28)
        SetCameraPitch(mfValue28 * 57.29578f);
    if (0.0f < mfStart38)
        SetCameraYaw(mfStart38);
    if (0.0f < mfStart3c)
        SetCameraRoll(mfStart3c);

    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x04, (void*)&mfTo44);
    SetCameraTransform(&mfTo44);

    float fCurrent = mfValue28;
    if (fCurrent == -1.0f && 0.0f < mfValue2c) {
        mfValue28 = mfValue2c;
        return;
    }
    if (mfValue2c == -1.0f && 0.0f < fCurrent) {
        mfValue2c = fCurrent;
        return;
    }
    float fDelta = mfValue2c - mfValue28;
    if (fDelta < 0.0f)
        fDelta = -fDelta;
    if (fDelta < mfTolerance) {
        mfValue28 = mfValue2c;
        return;
    }
    mfValue28 = (mfValue2c - mfValue28) * 0.1f + mfValue28;
}

// @ 0x00ddfef0
void cInterfaceState::UpdateFade(float fDelta)
{
    mnTimer = mnTimer + (int)fDelta;
    float fElapsed = (float)mnTimer;
    if (mnTimer < 0)
        fElapsed = fElapsed + 4294967296.0f;
    float fDuration = gInterfaceSpeed + gInterfaceSpeed;
    fElapsed = fElapsed / (fDuration * 1000.0f);

    if (mfTo4c == 0.0f || mfFrom50 == 0.0f) {
        if (1.0f < fElapsed) {
            PostInterfaceMessage(0x625e26a, 1);
            if (mfTo4c == 0.0f)
                mfTo4c = 1.0f;
            else
                gInterfaceStarted = 0;
            fElapsed = 1.0f;
        }
        if (mfFrom50 == 0.0f)
            fElapsed = 1.0f - fElapsed;

        float fBlend = fElapsed;
        InterpolateGlobals(fElapsed);
        mfValue28 = (mfValue2c - mfValue24) * fBlend + mfValue24;
        mfValue20 = (-0.43633232f - mfValue2c) * fBlend + mfValue2c;
        mfTolerance = mfFrom54 + (mfTo44 - mfFrom54) * fBlend;
        mfStart38 = mfValue30 + (mfTo48 - mfValue30) * fBlend;
        mfStart3c = mfValue2c + (mfTo4c - mfValue2c) * fBlend;
        gInterfaceTargetX = mfValue20;
        gInterfaceTargetY = mfValue30;
        gInterfaceTargetZ = mfValue28;
    }
}
