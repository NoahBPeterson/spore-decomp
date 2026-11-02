// src/game/SPGonzago/SPViewObjectUFO.cpp -- migrated from slice(s) s00e9bb40, s00e9b2b0, s00e9a7c0, s00e97bf0, s00e998d0, s00e98bd0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPViewObjectUFO.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEffectInfo.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSPMission.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyManager.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern int32_t gkSpaceEffects[16];               // 0x016c6340
extern int32_t gkPlanetEffects[16];              // 0x016c6380
extern char gGameModeSpace;                      // 0x01654c10
#include <math.h>
#include "SP/cViewer.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Variant.h"
#include "SP/cEmpire.h"
#include "SP/cModelManager.h"
#include "SP/cModelWorld.h"
#include "SP/cPropertyList.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cStarManager.h"
#include <new>
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cTerrainSphere.h"

// ---- items of slice s00e98bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct Vector3 {
    float x;
    float y;
    float z;
};
struct Key {
    uint32_t m_nGroup;
    uint32_t m_nType;
    uint32_t m_nInstance;
};
class cIUnknown {
public:
    virtual void AddRef();                       // +0x00
    virtual void Release();                      // +0x04
};
class cMission {
public:
virtual void M000();
virtual void M004();
virtual void M008();
    virtual void* M00c(uint32_t nKey);           // +0x0c
virtual void M010();
virtual void M014();
virtual void M018();
virtual void M01c();
virtual void M020();
virtual void M024();
virtual void M028();
virtual void M02c();
virtual void M030();
virtual void M034();
virtual void M038();
virtual void M03c();
virtual void M040();
virtual void M044();
virtual void M048();
virtual void M04c();
virtual void M050();
virtual void M054();
virtual void M058();
virtual void M05c();
virtual void M060();
virtual void M064();
virtual void M068();
virtual void M06c();
virtual void M070();
virtual void M074();
virtual void M078();
virtual void M07c();
virtual void M080();
virtual void M084();
virtual void M088();
virtual void M08c();
virtual void M090();
virtual void M094();
virtual void M098();
virtual void M09c();
virtual void M0a0();
virtual void M0a4();
virtual void M0a8();
virtual void M0ac();
virtual void M0b0();
virtual void M0b4();
virtual void M0b8();
virtual void M0bc();
virtual void M0c0();
virtual void M0c4();
virtual void M0c8();
virtual void M0cc();
virtual void M0d0();
virtual void M0d4();
virtual void M0d8();
virtual void M0dc();
virtual void M0e0();
virtual void M0e4();
virtual void M0e8();
virtual void M0ec();
virtual void M0f0();
virtual void M0f4();
    virtual bool M0f8();                         // +0xf8

    bool IsActive();                             // 0x00c44c80
    void* GetTargetPlanet();                     // 0x00970b30
};
class cSPMissionFetch {
public:
    bool CheckTargetPlanet(void* pA, void* pB);  // 0x00c5eb50
    bool VerifyTargetPlanet(void* pA, void* pB); // 0x00c54f90
};
class cMissionList {
public:
    cMission** m_pBegin;                         // +0x00
    cMission** m_pEnd;                           // +0x04
};
class cSPMissionManager_s00e9_8bd0 {
public:
    cMissionList* GetMissionList();              // 0x00fedd50
};
class cPlanet {
public:
    uint8_t m_pad[8];
};
class cSpatialObject {
public:
virtual void P00();
virtual void P04();
virtual void P08();
virtual void P0c();
virtual void P10();
virtual void P14();
virtual void P18();
virtual void P1c();
virtual void P20();
virtual void P24();
virtual void P28();
virtual void P2c();
virtual void P30();
virtual void P34();
virtual void P38();
virtual void P3c();
virtual void P40();
virtual void P44();
virtual void P48();
virtual void P4c();
virtual void P50();
virtual void P54();
virtual void P58();
virtual void P5c();
virtual void P60();
virtual void P64();
virtual void P68();
virtual void P6c();
virtual void P70();
virtual void P74();
virtual void P78();
virtual void P7c();
virtual void P80();
virtual void P84();
virtual void P88();
virtual void P8c();
virtual void P90();
virtual void P94();
virtual void P98();
virtual void P9c();
virtual void Pa0();
virtual void Pa4();
virtual void Pa8();
virtual void Pac();
virtual void Pb0();
virtual void Pb4();
    virtual void* Pb8(uint32_t nId);             // +0xb8

    uint8_t m_pad0bc[0x714 - 0xbc];              // +0x0bc
    int32_t m_nKind714;                          // +0x714
    uint8_t m_pad718[0x74c - 0x718];             // +0x718
    uint8_t m_bFlag74c;                          // +0x74c
    uint8_t m_pad74d[0x76c - 0x74d];             // +0x74d
    int32_t m_nMode76c;                          // +0x76c
};
class cRenderInstance {
public:
    uint8_t m_pad00[4];                          // +0x00
    uint32_t m_nFlags;                           // +0x04
    uint8_t m_pad08[8];                          // +0x08
    float m_fX;                                  // +0x10
    float m_fY;                                  // +0x14
    float m_fZ;                                  // +0x18
    float m_aMatrix[9];                          // +0x1c
};
class cIVisualEffect {
public:
    virtual void V00();                          // +0x00
    virtual void V04();                          // +0x04
    virtual void V08(bool bFlag);                // +0x08
    virtual void V0c(bool bFlag);                // +0x0c
virtual void V10();
virtual void V14();
    virtual void V18(void* pSample);             // +0x18
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
virtual void V2c();
virtual void V30();
virtual void V34();
virtual void V38();
virtual void V3c();
virtual void V40();
    virtual void V44(int32_t nSlot, const float* pValue, int32_t nCount);  // +0x44
virtual void V48();
virtual void V4c();
virtual void V50();
virtual void V54();
virtual void V58();
virtual void V5c();
    virtual int32_t V60();                       // +0x60
};
class cEffectsManager {
public:
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
    virtual void CreateV2c(uint32_t nId, int32_t nMode, cIVisualEffect** ppOut);  // +0x2c
};
class cGonzagoWorld {
public:
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
virtual void V2c();
virtual void V30();
virtual void V34();
virtual void V38();
virtual void V3c();
virtual void V40();
virtual void V44();
virtual void V48();
virtual void V4c();
virtual void V50();
virtual void V54();
virtual void V58();
virtual void V5c();
virtual void V60();
virtual void V64();
virtual void V68();
virtual void V6c();
virtual void V70();
virtual void V74();
virtual void V78();
virtual void V7c();
virtual void V80();
virtual void V84();
virtual void V88();
virtual void V8c();
virtual void V90();
virtual void V94();
virtual void V98();
virtual void V9c();
virtual void Va0();
virtual void Va4();
virtual void Va8();
virtual void Vac();
virtual void Vb0();
virtual void Vb4();
virtual void Vb8();
virtual void Vbc();
    virtual void Vc0();
    virtual void SetRenderVc4(void* pRender, bool bFlag, bool bOther, int32_t nMode);  // +0xc4
};
class cLocomotiveObject {
public:
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
    virtual Vector3* GetPositionV2c();           // +0x2c
    virtual void V30();
    virtual float GetScaleV34();                 // +0x34

    Vector3* GetVelocity();                      // 0x00d20610
};
class cAudioSystem {
public:
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
    virtual cIVisualEffect* GetEffectV20();      // +0x20
};
class cSpatialObjectView {
public:
virtual void S00();
virtual void S04();
virtual void S08();
virtual void S0c();
virtual void S10();
virtual void S14();
virtual void S18();
virtual void S1c();
    virtual void S20();
    virtual void S24(void* pOwner);              // +0x24
    virtual void S28();                           // +0x28
    virtual cRenderInstance* GetRenderS2c();      // +0x2c

    uint8_t m_pad04[8];                          // +0x04
    cSpatialObject* m_pObject;                   // +0x0c
    uint8_t m_pad10[8];                          // +0x10

    void SetIsVisible(bool bVisible);            // 0x00e889f0
};
class cSPUFOGfx : public cSpatialObjectView {
public:
    float m_fScaleA;                             // +0x18
    float m_fScaleB;                             // +0x1c
    float m_fScaleC;                             // +0x20
    uint32_t m_nHash;                            // +0x24
    int32_t m_nMode;                             // +0x28
    int32_t m_nModeB;                            // +0x2c
    uint8_t m_pad30[0x78 - 0x30];                // +0x30
    uint8_t m_bShadowed;                         // +0x78
    uint8_t m_pad79[0x7c - 0x79];                // +0x79
    cIVisualEffect* m_pRingEffect;               // +0x7c
    cIVisualEffect* m_pFilterRangeEffect;        // +0x80
    cIVisualEffect* m_pSelectionEffect;          // +0x84
    cIVisualEffect* m_pRolloverEffect;           // +0x88
    uint8_t m_pad8c[0x94 - 0x8c];                // +0x8c
    cLocomotiveObject* m_pLocomotive;            // +0x94
    uint8_t m_pad98[0xd4 - 0x98];                // +0x98
    int32_t m_nTrailId;                          // +0xd4

    void SetVisible(bool bVisible);              // 0x00e98db0
    void UpdateTrail();                          // 0x00e99550
    cSPUFOGfx* Construct();                      // 0x00e993c0
};
class cUFOKeys {
public:
    uint8_t m_pad000[0x504];                     // +0x000
    Key m_key;                                   // +0x504
};
class cTrailObject {
public:
    uint8_t m_pad000[0xb5e];                     // +0x000
    uint8_t m_bFlag;                             // +0xb5e
};
class cNounHolder {
public:
    uint8_t m_pad00[0x40];                       // +0x00
    cTrailObject** m_pObjBegin;                  // +0x40
    cTrailObject** m_pObjEnd;                    // +0x44
    uint8_t m_pad48[0xa4 - 0x48];                // +0x48
    cUFOKeys* m_pUFOKeys;                        // +0xa4
};
class cNounVector {
public:
    void** m_pBegin;                             // +0x00
    void** m_pEnd;                               // +0x04
};
class cNearNoun {
public:
    Vector3* GetPosition();                      // 0x00c6acc0
};
class cTerraformingInfo {
public:
    Key* FUN_00bbc510();                         // 0x00bbc510
};
class cPropertyObject {
public:
    uint8_t m_pad000[0x64c];                     // +0x000
    uint32_t m_nProp64c;                         // +0x64c
    uint32_t m_nProp650;                         // +0x650
    uint32_t m_nProp654;                         // +0x654
    uint32_t m_nKind658;                         // +0x658
};
class cPropertyManager {
public:
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
    virtual void GetV2c(uint32_t nProp, uint32_t nKey, cIUnknown** ppOut);   // +0x2c
};
struct cEffectInfo {
    float m_fX;
    float m_fY;
    float m_fZ;
    cIUnknown* m_pEffect;
};
class cAutoEffect {
public:
    cAutoEffect& operator=(const cAutoEffect& other)
    {
        void* pNew = other.m_pObject;
        void* pOld = m_pObject;
        if (pNew != pOld) {
            if (pNew != nullptr)
                ((cIUnknown*)pNew)->AddRef();
            m_pObject = pNew;
            if (pOld != nullptr)
                ((cIUnknown*)pOld)->Release();
        }
        return *this;
    }

    void* m_pObject;
};
struct cEffectRecord {
    Vector3 m_vPos;
    cAutoEffect m_effect;
};
struct cTrailSample {
    uint16_t m_nFlags;                           // +0x00
    uint16_t m_nCount;                           // +0x02
    float m_fX;                                  // +0x04
    float m_fY;                                  // +0x08
    float m_fZ;                                  // +0x0c
    float m_fScale;                              // +0x10
    float m_aMatrix[9];                          // +0x14
};
extern Vector3 gDefaultTrailOffset;              // 0x016c6350
cPlanet* __cdecl SP_GetActivePlanet();           // 0x01021260
cSPMissionManager_s00e9_8bd0* __cdecl SP_GetMissionManager(); // 0x00feb9f0
cTerraformingInfo* __stdcall SP_TerraformingManager(Key* pOut);  // 0x00b3d430
int32_t __cdecl SP_GetUniverseContext();         // 0x01021080
cGonzagoWorld* __cdecl SP_GonzagoModelWorld();   // 0x00b3d520
cAudioSystem* __cdecl EA_Audio_GetSystemAT();    // 0x00a206f0
cEffectsManager* __cdecl SP_EffectsManagerPtr(); // 0x0067ddd0
cPropertyManager* __cdecl SP_PropertyManager();  // 0x0067de30
void __cdecl SP_GetPropertyAsKey(cIUnknown* pValue, uint32_t nKey, Key* pOut);
void __cdecl SP_Start3dSoundByName(uint32_t nName, cIVisualEffect* pEffect,
                                   float fX, float fY, float fZ);   // 0x00571f80
void __cdecl FUN_00572020(cIVisualEffect* pEffect, int32_t nMode);  // 0x00572020
void __cdecl FUN_00b3d460();                     // 0x00b3d460
int32_t __cdecl FUN_00e98a40(cSpatialObject* pModel);  // 0x00e98a40
int32_t __cdecl FUN_00c37360();                  // 0x00c37360
char __cdecl FUN_00c37500();                     // 0x00c37500
float __cdecl FUN_00c37510();                    // 0x00c37510
float __cdecl FUN_00c37520();                    // 0x00c37520
float __cdecl FUN_00c37530();                    // 0x00c37530
float __cdecl FUN_00c37540();                    // 0x00c37540
cPlanet* __cdecl SP_GetCurrentGameMode();        // 0x00b5b800
void* __cdecl operator_new(uint32_t nSize, const char* pType,
                           uint32_t a, uint32_t b, uint32_t c,
                           uint32_t d);          // 0x00f473a0
void __cdecl SP_PlanetModel(void* pOut, const Vector3* pDir);      // 0x00b3d350
void __cdecl SP_Matrix3FromQuaternion(void* pOut, const void* pQuat);
class cPlanetModel {
public:
    void BuildSurfaceOrientation(void* pQuat, const Vector3* pDir);  // 0x00b7f190
};
void __cdecl cSpatialObjectView_Construct();     // 0x00e92af0
void __cdecl cGonzagoTimer_Construct();          // 0x00b63890
// ---- items of slice s00e98bd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s00e998d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double sqrt(double);
extern float   g_distEpsilon;        // @0x15a8b4c
extern float   g_normEpsilon;        // @0x13ec4b8
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          i16;
typedef int            i32;
struct Vector3_s00e9_98d0 { float x, y, z; };
struct Matrix3 {
    u32 m[9];
    void Set(const void* src);       // @0x41cb40 Matrix3::Assign
};
struct IEffect {                     // EA::Swarm::cIVisualEffect instance
    virtual void v00();
    virtual void Release();                  // 0x04
    virtual void Start(int flag);            // 0x08
    virtual void Stop(int flag);             // 0x0c
    virtual bool IsActive();                 // 0x10
    virtual void v14();                      // 0x14
    virtual void SetTransform(void* msg);    // 0x18
virtual void v1c();
virtual void v20();
};
template <class T> struct AutoRefCount {     // intrusive ref-count handle
    T* mpObject;                             // +0x00
    void Clear();
};
template <class T> void AutoRefCount<T>::Clear()
{
    T* p = mpObject;
    if (p) {
        mpObject = 0;
        p->Release();
    }
}
struct XformMsg {                    // 0x38 bytes; ctor @0x434040
    u16 flags;                       // +0x00  |4 = has position, |2 = has matrix
    i16 count;                       // +0x02
    Vector3_s00e9_98d0 pos;                     // +0x04
    u32 f10;                         // +0x10  (1.0f from the ctor)
    Matrix3 mat;                     // +0x14
    XformMsg();                      // defined out of slice @0x434040
};
struct EffectsMgr {                  // SP::EffectsManager (singleton)
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
    virtual bool CreateEffect(int key, int unused, IEffect** out);   // +0x2c
};
EffectsMgr* SP_EffectsManager();             // @0x67ddd0
struct cTransformSub {               // embedded spatial transform, at target+0x34
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
virtual void t20();
virtual void t24();
virtual void t28();
    virtual Vector3_s00e9_98d0* GetPosition();              // +0x2c
    virtual void*    GetOrientation();           // +0x30
virtual void t34();
virtual void t38();
virtual void t3c();
virtual void t40();
virtual void t44();
virtual void t48();
virtual void t4c();
virtual void t50();
virtual void t54();
virtual void t58();
    virtual void     GetLocalPoint(Vector3_s00e9_98d0* out); // +0x5c
};
struct cContactState {               // embedded collision state, at target+0x508
    u8 opaque[0x20c];
    u8 IsLatched();                  // @0xbfc480
    u8 IsConnected();                // @0xbfc600
};
struct cSpatialObj {                 // creature / flying-saucer spatial object
    u8            pad00[0x34];       // +0x000
    cTransformSub m_transform;       // +0x034
    u8            pad38[0x4d0];      // +0x038
    cContactState m_contact;         // +0x508  (0x20c bytes)
    i32           m_state714;        // +0x714  motion/UI state
    float         m_v718;            // +0x718  local position
    float         m_v71c;            // +0x71c
    float         m_v720;            // +0x720
    u8            pad724[0x28];      // +0x724
    u8            m_flag74c;         // +0x74c  "use city position"

    u8   HasFlag(int id);            // @0xc38990
    void SetFlag(int id, int value); // @0xc389c0
};
struct cViewer {                     // SP::cViewer
    void GetCameraLocationInfo(Vector3_s00e9_98d0* pos, Vector3_s00e9_98d0* dir, int a, int b); // @0x7c3d30
};
extern Vector3_s00e9_98d0 g_camDefault;         // @0x16c6350
extern Vector3_s00e9_98d0 g_spawnOffset;        // @0x16c6934
extern Matrix3 g_baseRotation;       // @0x16c6910
extern Vector3_s00e9_98d0 g_upAxis;             // @0x15a8b08
int     SP_GetUniverseContext_s00e9_98d0();                                   // @0x1021080
void*   SP_App();                                                  // @0x67dd10
void*   SP_PlanetModel(void* in);                                  // @0xb3d350
void*   SP_PlanetModel(void* out, void* in);                       // @0xb3d350
void    SP_FUN_b81630(void* self, void* out, void* in);            // @0xb81630
char    SP_FUN_b7e3e0(void* in);                                   // @0xb7e3e0
float   SP_VectorLength(void* in);                                 // @0x40ae50
void    SP_Vector3_Normalize(Vector3_s00e9_98d0* dest, Vector3_s00e9_98d0* src);         // @0x436ce0
Vector3_s00e9_98d0* SP_normalized_safe(Vector3_s00e9_98d0* out, Vector3_s00e9_98d0* in);            // @0x449c20
Matrix3 SP_Matrix3FromFacingAndUp(const void* facing, const void* up); // @0x69b440
Matrix3 SP_Matrix3FromQuaternion(const void* quat);                    // @0x59c190
int     SP_FNVHash(const char* str, u32 seed, int mode);           // @0x932e80
void*   SP_GetUFOSimulator();                                      // @0xffbe50
float   SP_GetMaxTravelDistance(void* self);                       // @0xffbfc0
float   SP_GetMaxZ(void* self);                                    // @0xffbfd0
void*   SP_IsArchived();                                           // @0x1021240
Vector3_s00e9_98d0* SP_GetCities(void* self);                                 // @0x5c65e0
int     SP_FUN_1046fc0(int id);                                    // @0x1046fc0
char    SP_FUN_10449e0(int value);                                 // @0x10449e0
void    SP_FUN_e99280(void* obj, void* msg);                       // @0xe99280
struct cSPUFOGfx_s00e9_98d0 {
    u8      pad00[0x0c];                 // +0x000
    void*   m_pObj0c;                    // +0x00c render subject
    u8      pad10[0x68];                 // +0x010
    u8      m_flag78;                    // +0x078 effects-enabled flag
    u8      pad79[0x0b];                 // +0x079
    AutoRefCount<IEffect> m_84;          // +0x084 shadow
    AutoRefCount<IEffect> m_88;          // +0x088 spare-phase A
    AutoRefCount<IEffect> m_8c;          // +0x08c spare-phase B
    u8      pad90[0x0c];                 // +0x090
    AutoRefCount<IEffect> m_9c;          // +0x09c AOE repair
    AutoRefCount<IEffect> m_a0;          // +0x0a0 rally call
    AutoRefCount<IEffect> m_a4;          // +0x0a4 shield
    AutoRefCount<IEffect> m_a8;          // +0x0a8 cloak
    AutoRefCount<IEffect> m_ac;          // +0x0ac unlock notice
    u8      padB0[0x04];                 // +0x0b0
    AutoRefCount<IEffect> m_b4;          // +0x0b4
    u8      padB8[0x04];                 // +0x0b8
    AutoRefCount<IEffect> m_bc;          // +0x0bc re-entry streak

    void UpdateShadow();
    void UpdateSpacePhase(void* unused);
    void UpdateAOERepairEffect(cSpatialObj* obj);  // 0x00e99f90 (cSPUFOGfx::UpdateAOERepairEffect)
    void UpdateRallyCallEffect(cSpatialObj* obj);  // 0x00e9a0c0 (cSPUFOGfx::UpdateRallyCallEffect)
    void UpdateE9A1F0(cSpatialObj* obj);  // 0x00e9a1f0 (cSPUFOGfx::UpdateE9A1F0)
    void UpdateShieldEffect(cSpatialObj* obj);  // 0x00e9a360 (cSPUFOGfx::UpdateShieldEffect)
    void UpdateE9A470(cSpatialObj* obj);  // 0x00e9a470 (cSPUFOGfx::UpdateE9A470)
    void UpdateCloakEffect(cSpatialObj* obj);  // 0x00e9a590 (cSPUFOGfx::UpdateCloakEffect)
    void UpdateE9A6A0(cSpatialObj* obj);  // 0x00e9a6a0 (cSPUFOGfx::UpdateE9A6A0)
};
#define DROP_EFFECT(ref)                                        \
    do {                                                        \
        if ((ref).mpObject) {                                   \
            IEffect* _drop = (ref).mpObject;                    \
            (ref).mpObject = 0;                                 \
            _drop->Release();                                   \
        }                                                       \
    } while (0)
// ---- items of slice s00e998d0 end

// ---- items of slice s00e97bf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl GetActivePlanet();                       // 0x01021260
extern "C" float gDetailRatioHalf;                    // 0x01471064 (0.5f)
extern "C" float gDetailRatioThird;                   // 0x013ef568 (0.33f)
extern "C" float gDetailRatioFifth;                   // 0x013ec480 (0.2f)
extern "C" void* __cdecl GetMissionMgr();             // 0x00feb9f0
extern "C" uint32_t __cdecl FUN_00c4cb90(void* a, void* b);   // 0x00c4cb90
struct SimPlanetOrbitView;
struct IOrbitRadius
{
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
    virtual float GetRadius();                        // +0x58
};
struct SimPlanetOrbitView
{
    char         mPad00[0x508];
    IOrbitRadius mOrbit508;      // +0x508 (embedded object; vtable first)
    char         mPad50c[0x540 - 0x50c];
    float        mOrbitRadius540; // +0x540
};
struct cSPMission;
struct cSPMissionVtbl
{
virtual void v00();
virtual void v01();
virtual void v02();
    virtual void* GetItem(uint32_t key);              // +0x0c
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
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
virtual void v48();
virtual void v49();
virtual void v50();
virtual void v51();
virtual void v52();
virtual void v53();
virtual void v54();
virtual void v55();
virtual void v56();
virtual void v57();
virtual void v58();
virtual void v59();
virtual void v60();
virtual void v61();
    virtual bool IsFlagged();                         // +0xf8
};
struct cSPMission : cSPMissionVtbl
{
    void* vfuncF8() { return (void*)(uint32_t)IsFlagged(); }
    bool  IsActive();                                 // 0x00c44c80
    void* GetTargetPlanet();                          // 0x00970b30
    void* GetItemKey(uint32_t key);                   // vtable +0x0c
};
struct MissionList
{
    cSPMission** mpBegin;            // +0x00
    cSPMission** mpEnd;              // +0x04
};
struct cSPMissionManager
{
    MissionList* GetMissionList();                    // 0x00fedd50
};
struct cSPMissionEradicate
{
    uint32_t GetClosestDiseasedAnimal(void* a, void* b);   // 0x00c50300
};
// ---- items of slice s00e97bf0 end

// ---- items of slice s00e9a7c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t kRadarTimerHandlers[2];                            // 0x01486fb0
extern const uint32_t kUfoDefaultKeyGroup;                               // 0x015a8b3c
extern const char kEastlAllocatorFile[];                                 // 0x013ebb38
#pragma warning(disable: 4100 4355)
void operator delete[](void* p);                                         // 0x00f47380
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0
struct Vector3_s00e9_a7c0 { float x, y, z; };
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct IRefObject {
    virtual void AddRef();                    // 0x00
    virtual void Release();                   // 0x04
};
template <class T> struct AutoRef {          // reference holder as used by the original (AsPointer idiom)
    T* mpObject;
    __forceinline AutoRef() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    __forceinline ~AutoRef() { if (mpObject) mpObject->Release(); }
    __forceinline T** AsPointer()
    {
        if (mpObject) {
            T* t = mpObject;
            mpObject = 0;
            t->Release();
        }
        return &mpObject;
    }
};
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;
    uint16_t mFlags2;
    __forceinline Variant() { mFlags = 0; mFlags2 = 0; }
    __forceinline ~Variant() { if (mFlags & 4) Destruct(0); }
    void Set(int type, int a, const void* data, int size, int count);    // 0x0093dd80 (ret 0x14)
    void Destruct(int arg);                                             // 0x0093db80 (ret 4)
    void SetU32(const uint32_t* value);                                  // 0x00422eb0 (ret 4)
};
class cPropertyList {
public:
    cPropertyList();                                                     // 0x006a1c40
    virtual void AddRef();                                               // 0x00
    virtual void Release();                                              // 0x04
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void SetProperty(uint32_t id, const Variant* value);         // 0x14 (ret 8)
    void SetParent(cPropertyList* parent);                               // 0x006a1710 (ret 4)
    uint32_t mData[(0x38 - 4) / 4];
};
class cPropertyManager_s00e9_a7c0 {
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
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** ppList);   // 0x2c
    virtual void v30();
    virtual void AddPropertyList(cPropertyList* list, uint32_t instance, uint32_t group);      // 0x34
};
cPropertyManager_s00e9_a7c0* PropertyManager();                                     // 0x0067de30
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    static wchar_t kEmpty[];                                             // 0x01667bac
    __forceinline WStr() : mpBegin(kEmpty), mpEnd(kEmpty), mpCapacity(kEmpty + 1) {}
    __forceinline WStr(int, int) : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~WStr()
    {
        if ((mpCapacity - mpBegin) * 2 > 2 && mpBegin)
            operator delete[](mpBegin);
    }
    void RangeInitialize(const wchar_t* psz);                            // 0x00579a90 (ret 4)
};
bool GetPropertyAsString16(cPropertyList* list, uint32_t id, WStr* out); // 0x006a1400 (cdecl)
struct IWinText : IRefObject {
    const wchar_t* GetText();                                            // 0x00414e10
};
struct AutoRefText {                                                      // EA::AutoRefCount<IWinText>
    IWinText* mpObject;
    __forceinline AutoRefText() : mpObject(0) {}
    AutoRefText& operator=(IWinText* p);                                 // 0x00b5f950 (ret 4)
};
struct IResource {
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                                 // 0x0c
};
class IResourceManager {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual bool GetResource(const ResourceKey* key, IResource** out, int a, int b, int c, int d);   // 0x0c
};
IResourceManager* GetManager();                                          // 0x0067dcd0
class IMessageBus {
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
    virtual void Post(const ResourceKey* key, const void* message);      // 0x4c
};
IMessageBus* GetMessageBus();                                            // 0x00401010 (returns global 0x015d0c04)
class IEffect_s00e9_a7c0 {
public:
    virtual void AddRef();                                               // 0x00
    virtual void Release();                                              // 0x04
    virtual void v08(int arg);                                           // 0x08
    virtual void Stop(int arg);                                          // 0x0c
virtual void v10();
virtual void v14();
    virtual void SendMessage(const void* message);                       // 0x18
};
class IEffectsManager {
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
    virtual void CreateEffect(uint32_t id, int a, IEffect_s00e9_a7c0** out);        // 0x2c
};
IEffectsManager* EffectsManager();                                       // 0x0067ddd0
class cGameModelOwner {
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
virtual void vf0();
virtual void vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10c();
virtual void v110();
virtual void v114();
virtual void v118();
virtual void v11c();
virtual void v120();
virtual void v124();
virtual void v128();
virtual void v12c();
virtual void v130();
virtual void v134();
virtual void v138();
virtual void v13c();
virtual void v140();
virtual void v144();
virtual void v148();
virtual void v14c();
virtual void v150();
virtual void v154();
virtual void v158();
virtual void v15c();
virtual void v160();
virtual void v164();
virtual void v168();
virtual void v16c();
    virtual void DisposeModel(class cGameModel* model, bool flag);       // 0x170 (ret 8)
};
class cGameModel {
public:
    cGameModelOwner* mpOwner;                // +0x00
    uint32_t mFlags;                         // +0x04 (bit 31, 14: see below)
    uint32_t pad08[(0x40 - 0x08) / 4];
    int mRefCount;                           // +0x40
    uint32_t mMask[2];                       // +0x44, +0x48
    Vector3_s00e9_a7c0 mColor;                          // +0x4c
    uint32_t pad58[(0x64 - 0x58) / 4];
    IRefObject* mpEffect;                    // +0x64
    uint32_t pad68[(0x70 - 0x68) / 4];
    Vector3_s00e9_a7c0 mEffectPos;                      // +0x70
    uint32_t pad7c[(0x90 - 0x7c) / 4];
    cPropertyList* mpPropertyList;           // +0x90
};
class cModelWorld {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cGameModel* LoadModel(uint32_t instance, uint32_t group, int flag);         // 0x0c
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
    virtual void SetModelParam(cGameModel* model, int id, const float* value, int a, int b);   // 0xc8 (ret 0x14)
};
cModelWorld* GonzagoModelWorld();                                        // 0x00b3d520
class cModelManager {
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
    virtual uint32_t GetBitIndex(uint32_t hash, int arg);                // 0x28
};
cModelManager* ModelManager();                                           // 0x0067dd80
class cEmpire { public: void GetColor(Vector3_s00e9_a7c0* out); };                  // 0x00c32cd0
class cStarManager { public: cEmpire* GetEmpireByID(int id); };          // 0x00ba9370 (ret 4)
cStarManager* StarManager();                                             // 0x00b3d2a0
uint32_t GetCurrentGameMode();                                           // 0x00b5b800
int GetUniverseContext();                                                // 0x01021080
class cSpatialObject_s00e9_a7c0 {
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
    virtual void SetEffectPos(const Vector3_s00e9_a7c0* pos, float scale);          // 0x64
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
    virtual IRefObject* Cast(uint32_t typeID);                           // 0xb8
    uint32_t pad04;                                                      // +0x04
    uint16_t pad08;                                                      // +0x08
    uint16_t mChangeCount;                                               // +0x0a bumped whenever the transform changes
    uint32_t pad0c[3];                                                   // +0x0c
    float mTransformScale;                                               // +0x18
    uint32_t pad1c[(0x50 - 0x1c) / 4];
    uint32_t mFlags;                                                     // +0x50
};
struct Quaternion { float x, y, z, w; };
struct Matrix33T { float m[9]; };
Matrix33T& Matrix3FromQuaternion(Matrix33T& out, const Quaternion& q);   // 0x0059c190
struct XformMsg_s00e9_a7c0 {
    uint16_t mFlags;                                                     // +0x00 bit 1 = matrix valid
    uint16_t mVersion;                                                   // +0x02
    uint32_t mPad04[3];                                                  // +0x04
    float mScale;                                                        // +0x10
    Matrix33T mMatrix;                                                   // +0x14
    XformMsg_s00e9_a7c0();                                                          // 0x00434040
    void SetTarget(const void* target);                                  // 0x00571d40 (ret 4)
};
class cUfoTransform {
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
    virtual const Vector3_s00e9_a7c0* GetPosition();                                // 0x2c
    virtual const Quaternion* GetOrientation();                          // 0x30
    virtual float GetScale();                                            // 0x34
};
class cSPGameDataUFO {
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
    virtual int GetEmpireID();                                           // 0x4c
    uint32_t pad04[(0x34 - 4) / 4];
    cUfoTransform mTransform;                                            // +0x34
    uint32_t pad38[(0x714 - 0x38) / 4];
    int mMode;                                                           // +0x714
    uint32_t pad718[(0x77c - 0x718) / 4];
    bool mbVisible;                                                      // +0x77c
    bool GetVisible();                                                   // 0x00c37170
    void Refresh();                                                      // 0x00c3b4d0
    void SetName(const WStr* name);                                      // 0x00c3dac0 (ret 4)
};
class IGameObject {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void* Cast(uint32_t typeID);                                 // 0x0c
};
struct UFOModelMessage {
    uint32_t mID;
    uint16_t mA;
    uint16_t mB;
};
class cSpatialObjectView_s00e9_a7c0 {
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
    void Init(void* object);                                             // 0x00e92910 (ret 4)
};
class IMessageServer {
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
    virtual void AddListener(const void* owner, uint32_t handler);       // 0x24 (ret 8)
};
IMessageServer* MessageServer();                                         // 0x0067dcc0
struct cServerBinding {
    const uint32_t* mpHandlers;                                          // +0x00 (0x01486fb0)
    int32_t mRefCount;                                                   // +0x04
    uint32_t mState;                                                     // +0x08
};
class cSPUFOGfx_s00e9_a7c0;
class cUfoListener {
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
    bool HandleMessage(uint32_t interfaceId, void* arg);                 // 0x00e9a7c0 (ret 8)
    cSPUFOGfx_s00e9_a7c0* Parent();                                                 // this - 0x3c
};
class cSPUFOGfx_s00e9_a7c0 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual IGameObject* GetGameObject();                                // 0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual cSpatialObject_s00e9_a7c0* v2c();                                       // 0x2c
    virtual void SetModel(cGameModel* model, cModelWorld* world);        // 0x30

    void SetVisible(bool v);                                             // 0x00e98db0 (ret 4)
    void SetUFOModel(ResourceKey* key, bool announce);                   // 0x00e9a940 (ret 8)
    void Init(void* object);                                             // 0x00e9b1a0 (ret 4)

    uint32_t pad04[2];
    cSpatialObject_s00e9_a7c0* mpObject;                                            // +0x0c
    uint32_t pad10[2];
    Vector3_s00e9_a7c0 mColor;                                                      // +0x18
    uint32_t pad24[(0x30 - 0x24) / 4];
    bool mbModelVisible;                                                 // +0x30
    uint8_t pad31[0x3c - 0x31];
    cUfoListener mListener;                                              // +0x3c
    IMessageServer* mpMessageServer;                                     // +0x40
    const void* mpMessageServerCookie;                                   // +0x44 (= &mListener)
    cServerBinding mServerBinding;                                       // +0x48
    uint8_t pad54[0x80 - 0x54];
    IEffect_s00e9_a7c0* mFilterRangeEffect;                                         // +0x80
    IEffect_s00e9_a7c0* mSelectionEffect;                                           // +0x84
    IEffect_s00e9_a7c0* mRolloverEffect;                                            // +0x88
    IEffect_s00e9_a7c0* mRadarEffect;                                               // +0x8c
    uint32_t pad90[(0xb8 - 0x90) / 4];
    IEffect_s00e9_a7c0* mContextEffect;                                             // +0xb8
};
__forceinline cSPUFOGfx_s00e9_a7c0* cUfoListener::Parent()
{
    return (cSPUFOGfx_s00e9_a7c0*)((char*)this - 0x3c);
}
__forceinline void EnsureEffect(IEffect_s00e9_a7c0*& slot, uint32_t id)
{
    if (slot == 0) {
        IEffectsManager* mgr = EffectsManager();
        IEffect_s00e9_a7c0* old = slot;
        if (old) {
            slot = 0;
            old->Release();
        }
        mgr->CreateEffect(id, 0, &slot);
    } else {
        slot->Stop(1);
    }
}
void __fastcall FUN_00c37230(cSPGameDataUFO* ufo, void* dummy,
                             ResourceKey* key, bool* flag);              // 0x00c37230 (ret 8)
struct AssetInfo {
    float mPosition[3];                                                  // +0x00
    IRefObject* mpObject;                                                // +0x0c AddRef'd when copied
    __forceinline AssetInfo() : mpObject(0) {}
    __forceinline AssetInfo(const AssetInfo& src)
    {
        mPosition[0] = src.mPosition[0];
        mPosition[1] = src.mPosition[1];
        mPosition[2] = src.mPosition[2];
        mpObject = src.mpObject;
        if (mpObject)
            mpObject->AddRef();
    }
    AssetInfo& operator=(const AssetInfo& src);                          // 0x0065cd70 (ret 4)
};
AssetInfo* FUN_0065ce10(AssetInfo* first, AssetInfo* last, AssetInfo* dest);  // 0x0065ce10
AssetInfo* FUN_00e990f0(AssetInfo* first, AssetInfo* last, AssetInfo* dest);  // 0x00e990f0
void FUN_0065c750(AssetInfo* first, AssetInfo* last, AssetInfo* dest);        // 0x0065c750
class AssetInfoVector {
public:
    void Insert(AssetInfo* pos, const AssetInfo* value);                  // 0x00e9b030 (ret 8)
    AssetInfo* mpBegin;                                                   // +0x00
    AssetInfo* mpEnd;                                                     // +0x04
    AssetInfo* mpCapacity;                                                // +0x08
};
// ---- items of slice s00e9a7c0 end

// ---- items of slice s00e9b2b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100)
struct Vector3_s00e9_b2b0 {
    float x, y, z;
    Vector3_s00e9_b2b0() {}
    Vector3_s00e9_b2b0(const Vector3_s00e9_b2b0& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00e9_b2b0(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
struct Matrix3_s00e9_b2b0 {
    Vector3_s00e9_b2b0 row[3];
    Matrix3_s00e9_b2b0() {}
};
extern const Vector3_s00e9_b2b0 kZeroVec;                  // 0x016c6934
extern const Matrix3_s00e9_b2b0 kIdentityMat;              // 0x016c6910
extern const Vector3_s00e9_b2b0 kUpAxis;                   // 0x015a8afc
const Matrix3_s00e9_b2b0* Matrix3FromQuaternion(Matrix3_s00e9_b2b0* out, const Quaternion* q);                          // 0x0059c190 (cdecl)
Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3_s00e9_b2b0* facing, const Vector3_s00e9_b2b0* up); // 0x0069b600 (cdecl)
struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3_s00e9_b2b0 mOffset;
    float mfScale;
    Matrix3_s00e9_b2b0 mRotation;
    __forceinline Transform() : mnFlags(0), mnTransformCount(0), mOffset(kZeroVec), mfScale(1.0f)
    {
        Vector3_s00e9_b2b0 a(kIdentityMat.row[0]);
        mRotation.row[0] = a;
        Vector3_s00e9_b2b0 b(kIdentityMat.row[1]);
        mRotation.row[1] = b;
        Vector3_s00e9_b2b0 c(kIdentityMat.row[2]);
        mRotation.row[2] = c;
    }
    Transform& SetOffset(const Vector3_s00e9_b2b0& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; return *this; }
    Transform& SetRotation(const Matrix3_s00e9_b2b0& r) { mRotation = r; mnFlags |= 2; mnTransformCount++; return *this; }
};
struct cIVisualEffect_s00e9_b2b0 {
    virtual int AddRef();
    virtual int Release();
    virtual void Start(int hardStart);
    virtual int Stop(int hardStop);
    virtual bool IsRunning();                   // +0x10
    virtual void SetRigidTransform(const Transform& t);
    virtual void SetSourceTransform(const Transform& t);   // +0x18
};
struct UFOCollisionEffectInfo {
    Vector3_s00e9_b2b0 mOffset;                            // +0x00, offset from the UFO centre
    cIVisualEffect_s00e9_b2b0* mpEffect;                   // +0x0c
    ~UFOCollisionEffectInfo() { cIVisualEffect_s00e9_b2b0* p = mpEffect; if (p) p->Release(); }
};
UFOCollisionEffectInfo* DoCopy(UFOCollisionEffectInfo* first, UFOCollisionEffectInfo* last, UFOCollisionEffectInfo* dest);
struct cLocomotiveIface {
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
    virtual const Vector3_s00e9_b2b0* GetPosition();       // +0x2c
    virtual const Quaternion* GetOrientation(); // +0x30
};
struct cSPGameDataUFO_s00e9_b2b0 {
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
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual int GetEmpireID();                  // +0x4c
    uint32_t pad04[(0x34 - 4) / 4];
    cLocomotiveIface mLoco;                     // +0x34
};
struct cSpatialObject_s00e9_b2b0 {
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
virtual void v0b();
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
virtual void v17();
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
    virtual void* Cast(uint32_t typeID);        // +0xb8
};
__forceinline Vector3_s00e9_b2b0 Rotate(const Quaternion* q, const Vector3_s00e9_b2b0& v)
{
    float x = q->x, y = q->y, z = q->z, w = q->w;
    Vector3_s00e9_b2b0 r;
    r.x = ((w * y + z * x) * v.z + (y * x - w * z) * v.y) * 2.0f + (1.0f - (z * z + y * y) * 2.0f) * v.x;
    r.y = ((w * z + y * x) * v.x + (z * y - w * x) * v.z) * 2.0f + (1.0f - (z * z + x * x) * 2.0f) * v.y;
    r.z = ((z * x - w * y) * v.x + (w * x + z * y) * v.y) * 2.0f + (1.0f - (y * y + x * x) * 2.0f) * v.z;
    return r;
}
struct VecUFO {
    UFOCollisionEffectInfo* mpBegin;            // +0x00
    UFOCollisionEffectInfo* mpEnd;              // +0x04
    UFOCollisionEffectInfo* mpCapacity;         // +0x08
    UFOCollisionEffectInfo* erase(UFOCollisionEffectInfo* first,
                                  UFOCollisionEffectInfo* last); // 0x0065DED0 (thiscall, ret 8)
};
class cSPUFOGfx_s00e9_b2b0 {
public:
    uint32_t pad00[3];                          // +0x00
    cSpatialObject_s00e9_b2b0* mpObject;                   // +0x0c
    uint32_t pad10[0x0c];                       // +0x10..+0x3f
    void*    mpHandler;                         // +0x40
    uint32_t mHandler44;                        // +0x44
    uint32_t mHandler48;                        // +0x48
    uint32_t mHandler4c;                        // +0x4c
    uint32_t mHandler50;                        // +0x50
    uint32_t pad54[0x0b];                       // +0x54..+0x7f
    cIVisualEffect_s00e9_b2b0* mFilterRangeEffect;         // +0x80
    cIVisualEffect_s00e9_b2b0* mSelectionEffect;           // +0x84
    cIVisualEffect_s00e9_b2b0* mRolloverEffect;            // +0x88
    cIVisualEffect_s00e9_b2b0* mRadarEffect;               // +0x8c
    cIVisualEffect_s00e9_b2b0* mAOERepairEffect;           // +0x90
    cIVisualEffect_s00e9_b2b0* mRallyCallEffect;           // +0x94
    uint32_t pad98[0x04];                       // +0x98..+0xa7
    cIVisualEffect_s00e9_b2b0* mEffectA8;                  // +0xa8
    cIVisualEffect_s00e9_b2b0* mEffectAc;                  // +0xac
    cIVisualEffect_s00e9_b2b0* mEffectB0;                  // +0xb0
    uint32_t padB4;                             // +0xb4
    cIVisualEffect_s00e9_b2b0* mEffectB8;                  // +0xb8
    cIVisualEffect_s00e9_b2b0* mEffectBc;                  // +0xbc
    VecUFO mEffects;                            // +0xc0

    void SetVisible(bool visible);              // 0x00E98DB0
    void erase(UFOCollisionEffectInfo* position)
    {
        if (position + 1 < mEffects.mpEnd)
            DoCopy(position + 1, mEffects.mpEnd, position);
        --mEffects.mpEnd;
        mEffects.mpEnd->~UFOCollisionEffectInfo();
    }
    unsigned size() const { return (unsigned)(mEffects.mpEnd - mEffects.mpBegin); }
    void UpdateHitEffects();                    // 0x00e9b2b0
    void ClearEffects();                        // 0x00e9b8e0
};
void RemoveHandler(void* handler, void* arg1, void* arg2, void* arg3, void* arg4); // 0x00571DB0 (cdecl)
__forceinline void ReleaseEffect(cIVisualEffect_s00e9_b2b0*& slot)
{
    cIVisualEffect_s00e9_b2b0* effect = slot;
    if (effect != 0) {
        void* vtable = *(void**)effect;
        void* stop = ((void**)vtable)[0x0c / 4];
        ((void (__thiscall*)(void*, int))stop)(effect, 0);
        effect = slot;
        if (effect != 0) {
            slot = 0;
            vtable = *(void**)effect;
            void* release = ((void**)vtable)[0x04 / 4];
            ((void (__thiscall*)(void*))release)(effect);
        }
    }
}
// ---- items of slice s00e9b2b0 end

// ---- items of slice s00e9bb40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
struct Vector3_s00e9_bb40 {
    float x, y, z;
    Vector3_s00e9_bb40() {}
    Vector3_s00e9_bb40(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00e9_bb40(const Vector3_s00e9_bb40& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00e9_bb40 operator-(const Vector3_s00e9_bb40& b) const { return Vector3_s00e9_bb40(x - b.x, y - b.y, z - b.z); }
    static const Vector3_s00e9_bb40 ZERO;     // 0x016c6934
};
struct Matrix3_s00e9_bb40 {
    float m[9];
    Matrix3_s00e9_bb40() {}
    Matrix3_s00e9_bb40(const Matrix3_s00e9_bb40& o)
    {
        m[0] = o.m[0]; m[1] = o.m[1]; m[2] = o.m[2];
        m[3] = o.m[3]; m[4] = o.m[4]; m[5] = o.m[5];
        m[6] = o.m[6]; m[7] = o.m[7]; m[8] = o.m[8];
    }
    static const Matrix3_s00e9_bb40 IDENTITY; // 0x016c6910
};
extern const Vector3_s00e9_bb40 kUFOUpAxis;   // 0x015a8afc  (0, 1, 0)
inline Vector3_s00e9_bb40 RotateByQuaternion(const Quaternion& q, const Vector3_s00e9_bb40& v)
{
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float xy = q.y * q.x;
    float yz = q.z * q.y;
    float yw = q.y * q.w;
    float zz = q.z * q.z;
    float zw = q.z * q.w;
    float zx = q.z * q.x;
    float xw = q.x * q.w;
    return Vector3_s00e9_bb40(
        ((xy - zw) * v.y + (yw + zx) * v.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * v.x,
        ((yz - xw) * v.z + (zw + xy) * v.x) * 2.0f + (1.0f - (zz + xx) * 2.0f) * v.y,
        ((xw + yz) * v.y + (zx - yw) * v.x) * 2.0f + (1.0f - (yy + xx) * 2.0f) * v.z);
}
inline Vector3_s00e9_bb40 MulMatrix(const Matrix3_s00e9_bb40& r, const Vector3_s00e9_bb40& v)
{
    return Vector3_s00e9_bb40(r.m[2] * v.z + r.m[1] * v.y + r.m[0] * v.x,
                   r.m[5] * v.z + r.m[4] * v.y + r.m[3] * v.x,
                   r.m[8] * v.z + r.m[7] * v.y + r.m[6] * v.x);
}
const Matrix3_s00e9_bb40* Matrix3FromQuaternion(Matrix3_s00e9_bb40* out, const Quaternion* q);                    // 0x0059c190
const Matrix3_s00e9_bb40* Matrix3FromFacingAndUp(Matrix3_s00e9_bb40* out, const Vector3_s00e9_bb40* facing, const Vector3_s00e9_bb40* up); // 0x0069b440
const Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3_s00e9_bb40* facing, const Vector3_s00e9_bb40* up); // 0x0069b600
Vector3_s00e9_bb40 OrthogonalVector(const Vector3_s00e9_bb40& v);                                                  // 0x006985b0
struct Transform_s00e9_bb40 {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3_s00e9_bb40 mOffset;
    float mfScale;
    Matrix3_s00e9_bb40 mRotation;
    __forceinline Transform_s00e9_bb40() : mnFlags(0), mnTransformCount(0), mOffset(Vector3_s00e9_bb40::ZERO), mfScale(1.0f)
    {
        mRotation = Matrix3_s00e9_bb40(Matrix3_s00e9_bb40::IDENTITY);
    }
    Transform_s00e9_bb40& SetOffset(const Vector3_s00e9_bb40& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; return *this; }
    Transform_s00e9_bb40& SetRotation(const Matrix3_s00e9_bb40& r) { mRotation = r; mnFlags |= 2; mnTransformCount++; return *this; }
};
struct IVisualEffect {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void Start(int hardStart) = 0;
    virtual int Stop(int hardStop) = 0;
    virtual int IsRunning() = 0;
    virtual void SetRigidTransform(const Transform_s00e9_bb40& t) = 0;
    virtual void SetSourceTransform(const Transform_s00e9_bb40& t) = 0;
};
struct IReleasable {
    virtual void v00();
    virtual int Release();                              // +0x04
};
namespace EA {
namespace Messaging {
void RemoveHandler(void* handler, int p1, int p2, int p3, int p4);   // 0x00571db0
}
}
template <class T> struct AutoRefCount_s00e9_bb40 {
    T* mpObject;
    AutoRefCount_s00e9_bb40() : mpObject(0) {}
    AutoRefCount_s00e9_bb40(const AutoRefCount_s00e9_bb40& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s00e9_bb40() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T** AsPPTypeParam()
    {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
struct IEffectsManager_s00e9_bb40 {
    virtual bool Initialize() = 0;
    virtual bool Dispose() = 0;
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void SetResources(void*) = 0;
    virtual void* Resources() = 0;
    virtual void SetRenderer(void*) = 0;
    virtual void* Renderer() = 0;
    virtual void SetDecalManager(void*, int) = 0;
    virtual void* DecalManager(int) = 0;
    virtual bool HasVisualEffect(uint32_t instanceID, uint32_t groupID) const = 0;
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect** dst) = 0;
};
namespace SP {
 IEffectsManager_s00e9_bb40* EffectsManager_s00e9_bb40();   // 0x0067ddd0
}
struct cPlanetModel_s00e9_bb40 {
    Vector3_s00e9_bb40 GetSurfaceNormal(const Vector3_s00e9_bb40& pos);       // 0x00b7e3b0 (sret, ret 8)
};
namespace SP {
 cPlanetModel_s00e9_bb40* PlanetModel();   // 0x00b3d350
}
struct cLocomotiveIface_s00e9_bb40 {
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
    virtual const Vector3_s00e9_bb40* GetPosition();           // +0x2c
    virtual const Quaternion* GetOrientation();     // +0x30
};
namespace SP {
class cSPGameDataUFO_s00e9_bb40 { public:
    char pad00[0x34];
    cLocomotiveIface_s00e9_bb40 mLoco;                             // +0x34
    char pad38[0x714 - 0x38];
    int mbShielded;                                     // +0x714
    bool HasCollisions();                               // 0x00c38260 (list at +0x770 not empty)
    int GetNextCollision(Vector3_s00e9_bb40* pos);                 // 0x00c3c4d0
};
}
namespace SP {
struct cGameObject {
    // vtable slot 0xb8: Cast(id)
virtual void* v00();
virtual void* v01();
virtual void* v02();
virtual void* v03();
virtual void* v04();
virtual void* v05();
virtual void* v06();
virtual void* v07();
virtual void* v08();
virtual void* v09();
virtual void* v10();
virtual void* v11();
virtual void* v12();
virtual void* v13();
virtual void* v14();
virtual void* v15();
virtual void* v16();
virtual void* v17();
virtual void* v18();
virtual void* v19();
virtual void* v20();
virtual void* v21();
virtual void* v22();
virtual void* v23();
virtual void* v24();
virtual void* v25();
virtual void* v26();
virtual void* v27();
virtual void* v28();
virtual void* v29();
virtual void* v30();
virtual void* v31();
virtual void* v32();
virtual void* v33();
virtual void* v34();
virtual void* v35();
virtual void* v36();
virtual void* v37();
virtual void* v38();
virtual void* v39();
virtual void* v40();
virtual void* v41();
virtual void* v42();
virtual void* v43();
virtual void* v44();
virtual void* v45();
    virtual void* Cast(uint32_t typeID);                // +0xb8
};
}
namespace SP {
struct HitEffect {
    Vector3_s00e9_bb40 mOffset;
    AutoRefCount_s00e9_bb40<IVisualEffect> mpEffect;
};
}
namespace SP {
struct HitEffectVector {
    HitEffect* mpBegin;
    HitEffect* mpEnd;
    HitEffect* mpCapacity;
    ~HitEffectVector();                                          // 0x0065cd30
    void DoInsertValue(HitEffect* pos, const HitEffect& value);   // 0x00e9b030
    void push_back(const HitEffect& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) HitEffect(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace SP {
struct EffectID { uint32_t instanceID; uint32_t groupID; };
}
namespace SP {
class cSpatialObjectView_s00e9_bb40 {
public:
    virtual ~cSpatialObjectView_s00e9_bb40();                      // 0x00e92660
    char pad04[0x8];
    cGameObject* mpObject;                              // +0x0c
    char pad10[0x24];                                   // +0x10 .. +0x33
};
}
namespace SP {
class cContentValidationSummarizer {                     // +0x34
public:
    virtual ~cContentValidationSummarizer() {}
    int mField38;                                       // +0x38
};
}
namespace SP {
class PaintSystem {                                     // +0x3c
public:
    virtual ~PaintSystem() {}
};
}
namespace SP {
struct cMessageHandler {
    void* mpHandler;                                    // +0x40
    int mParam1;                                        // +0x44
    int mParam2;                                        // +0x48
    int mParam3;                                        // +0x4c
    int mParam4;                                        // +0x50
    ~cMessageHandler()
    {
        void* handler = mpHandler;
        if (handler) {
            mpHandler = 0;
            EA::Messaging::RemoveHandler(handler, mParam1, mParam2, mParam3, mParam4);
        }
    }
};
}
namespace SP {
class cGonzagoTimer_s00e9_bb40 {
public:
    char mData[0x28];                                   // +0x58 .. +0x7f
    ~cGonzagoTimer_s00e9_bb40();                                   // 0x00b638b0
};
}
namespace SP {
class cSPUFOGfx_s00e9_bb40 : public cSpatialObjectView_s00e9_bb40,
                  public cContentValidationSummarizer,
                  public PaintSystem {
public:
    virtual ~cSPUFOGfx_s00e9_bb40();                               // 0x00e9c530
    void CreateHitEffects();                            // 0x00e9bb40
    void ClearEffects();                                // 0x00e9b8e0
    cMessageHandler mHandler;                           // +0x40
    char pad54[4];                                      // +0x54
    cGonzagoTimer_s00e9_bb40 mTimer;                               // +0x58
    AutoRefCount_s00e9_bb40<IReleasable> mRef00;                   // +0x80
    AutoRefCount_s00e9_bb40<IReleasable> mRef01;                   // +0x84
    AutoRefCount_s00e9_bb40<IReleasable> mRef02;                   // +0x88
    AutoRefCount_s00e9_bb40<IReleasable> mRef03;                   // +0x8c
    AutoRefCount_s00e9_bb40<IReleasable> mRef04;                   // +0x90
    AutoRefCount_s00e9_bb40<IReleasable> mRef05;                   // +0x94
    AutoRefCount_s00e9_bb40<IReleasable> mRef06;                   // +0x98
    AutoRefCount_s00e9_bb40<IReleasable> mRef07;                   // +0x9c
    AutoRefCount_s00e9_bb40<IReleasable> mRef08;                   // +0xa0
    AutoRefCount_s00e9_bb40<IReleasable> mRef09;                   // +0xa4
    AutoRefCount_s00e9_bb40<IReleasable> mRef10;                   // +0xa8
    AutoRefCount_s00e9_bb40<IReleasable> mRef11;                   // +0xac
    AutoRefCount_s00e9_bb40<IReleasable> mRef12;                   // +0xb0
    AutoRefCount_s00e9_bb40<IReleasable> mRef13;                   // +0xb4
    AutoRefCount_s00e9_bb40<IReleasable> mRef14;                   // +0xb8
    AutoRefCount_s00e9_bb40<IReleasable> mRef15;                   // +0xbc
    HitEffectVector mHitEffects;                        // +0xc0
};
}
namespace SP {
void cSPUFOGfx_s00e9_bb40::CreateHitEffects()
{
    cGameObject* object = mpObject;
    cSPGameDataUFO_s00e9_bb40* ufo = object ? (cSPGameDataUFO_s00e9_bb40*)object->Cast(0xb033b403) : 0;
    while (ufo->HasCollisions()) {
        Vector3_s00e9_bb40 hitPos;
        int type = ufo->GetNextCollision(&hitPos);
        Vector3_s00e9_bb40 up = RotateByQuaternion(*ufo->mLoco.GetOrientation(), kUFOUpAxis);

        EffectID hullEffects[11] = {
            { 0, 0 }, { 0x3d6f33c, 0 }, { 0x5131c8c, 0 }, { 0x5131c8f, 0 },
            { 0x5131c93, 0 }, { 0x5131c94, 0 }, { 0x5131c96, 0 }, { 0x5131c98, 0 },
            { 0x5131c9a, 0 }, { 0x5131c9c, 0 }, { 0x5131c9d, 0 },
        };
        EffectID shieldEffects[11] = {
            { 0, 0 }, { 0x693320c, 0 }, { 0x693320d, 0 }, { 0x693320e, 0 },
            { 0x693320f, 0 }, { 0x6933210, 0 }, { 0x6933211, 0 }, { 0x6933212, 0 },
            { 0x6933213, 0 }, { 0x6933214, 0 }, { 0x6933215, 0 },
        };
        EffectID id;
        if (ufo->mbShielded == 0)
            id = hullEffects[type];
        else
            id = shieldEffects[type];

        if (type == 1) {
            Vector3_s00e9_bb40 normal = PlanetModel()->GetSurfaceNormal(hitPos);
            AutoRefCount_s00e9_bb40<IVisualEffect> effect;
            if (EffectsManager_s00e9_bb40()->CreateVisualEffect(0x3d6f334, 0, effect.AsPPTypeParam())) {
                Vector3_s00e9_bb40 facingUp = hitPos;
                if ((float)fabs(hitPos.x * normal.x + normal.z * hitPos.z + normal.y * hitPos.y) < 1.5258789e-05f)
                    facingUp = OrthogonalVector(normal);
                Transform_s00e9_bb40 t;
                t.SetOffset(hitPos);
                Matrix3_s00e9_bb40 rot;
                t.SetRotation(*Matrix3FromFacingAndUp(&rot, &normal, &facingUp));
                effect->SetSourceTransform(t);
                effect->Start(0);
            }
        }

        if (id.instanceID != 0 || id.groupID != 0) {
            HitEffect hit;
            if (EffectsManager_s00e9_bb40()->CreateVisualEffect(id.instanceID, id.groupID, hit.mpEffect.AsPPTypeParam())) {
                const Vector3_s00e9_bb40& pos = *ufo->mLoco.GetPosition();
                Matrix3_s00e9_bb40 tmp;
                Matrix3_s00e9_bb40 orient;
                orient = *Matrix3FromQuaternion(&tmp, ufo->mLoco.GetOrientation());
                hit.mOffset = MulMatrix(orient, hitPos - pos);
                Transform_s00e9_bb40 t;
                t.SetOffset(pos);
                Vector3_s00e9_bb40 facing = hitPos - pos;
                Quaternion q;
                QuaternionFromFacingAndUp(&q, &facing, &up);
                t.SetRotation(*Matrix3FromQuaternion(&tmp, &q));
                hit.mpEffect->SetSourceTransform(t);
                hit.mpEffect->Start(0);
                mHitEffects.push_back(hit);
            }
        }
    }
}
}
namespace SP {
void EastlDeallocate(void* pBlock);                      // 0x00f47380
}
namespace SP {
inline void FreeVectorStorage(void* pBlock)
{
    if (pBlock && static_cast<uint32_t*>(pBlock)[-1] != 0)
        EastlDeallocate(pBlock);
}
}
namespace SP {
template <class T> inline void Construct(T* p, const T& value)
{
    if (p)
        ::new((void*)p) T(value);
}
}
namespace SP {
template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { FreeVectorStorage(mpBegin); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            Construct(mpEnd++, value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(T* pos, const T& value);          // 0x004b5ad0
};
}
namespace SP {
struct Vector3List {
    Vector3_s00e9_bb40* mpBegin;
    Vector3_s00e9_bb40* mpEnd;
    Vector3_s00e9_bb40* mpCapacity;
    Vector3List() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vector3List() { FreeVectorStorage(mpBegin); }
    void push_back(const Vector3_s00e9_bb40& value);                // 0x004739d0
};
}
namespace SP {
class cPropertyObject_s00e9_bb40 {
public:
    char pad00[0x34];
    cLocomotiveIface_s00e9_bb40 mLoco;                              // +0x34
};
}
namespace SP {
bool FUN_00e991b0(cPropertyObject_s00e9_bb40* pObject);             // 0x00e991b0
}
namespace SP {
struct NounVector {
    void* mpUnused;                                      // +0x00
    cPropertyObject_s00e9_bb40** mpBegin;                           // +0x04
    cPropertyObject_s00e9_bb40** mpEnd;                             // +0x08
};
}
namespace SP {
class cGameDataObject {
public:
    char pad00[0x70];
    cLocomotiveIface_s00e9_bb40 mLoco;                              // +0x70
    char pad74[0x228 - 0x74];
    uint32_t mTypeID;                                    // +0x228
};
}
namespace SP {
struct NounObjectVector {
    cGameDataObject** mpBegin;                           // +0x00
    cGameDataObject** mpEnd;                             // +0x04
};
}
namespace SP {
class cTerrainSphere_s00e9_bb40 {
public:
    bool FUN_00c772c0(uint32_t id);                      // 0x00c772c0
};
}
namespace SP {
class cSPMission_s00e9_bb40 {
public:
virtual void* v00();
virtual void* v01();
virtual void* v02();
    virtual cSPMission_s00e9_bb40* GetMissionContext(uint32_t id);  // +0x0c
virtual void* v04();
virtual void* v05();
virtual void* v06();
virtual void* v07();
virtual void* v08();
virtual void* v09();
virtual void* v10();
virtual void* v11();
virtual void* v12();
virtual void* v13();
virtual void* v14();
virtual void* v15();
virtual void* v16();
virtual void* v17();
virtual void* v18();
virtual void* v19();
virtual void* v20();
virtual void* v21();
virtual void* v22();
virtual void* v23();
virtual void* v24();
virtual void* v25();
virtual void* v26();
virtual void* v27();
virtual void* v28();
virtual void* v29();
virtual void* v30();
virtual void* v31();
virtual void* v32();
virtual void* v33();
virtual void* v34();
virtual void* v35();
virtual void* v36();
virtual void* v37();
virtual void* v38();
virtual void* v39();
virtual void* v40();
virtual void* v41();
virtual void* v42();
virtual void* v43();
virtual void* v44();
virtual void* v45();
virtual void* v46();
virtual void* v47();
virtual void* v48();
virtual void* v49();
virtual void* v50();
virtual void* v51();
virtual void* v52();
virtual void* v53();
virtual void* v54();
virtual void* v55();
virtual void* v56();
virtual void* v57();
virtual void* v58();
virtual void* v59();
virtual void* v60();
virtual void* v61();
    virtual bool IsFlagged();                            // +0xf8
    bool IsActive();                                     // 0x00c44c80
    void* FUN_00c5f3d0();                                // 0x00c5f3d0
    void* FUN_00c5f3b0();                                // 0x00c5f3b0
};
}
namespace SP {
class cSPMissionManager_s00e9_bb40 {
public:
    cSPMission_s00e9_bb40* GetMissionByID(int id);                  // 0x00fee480
};
}
namespace SP {
cSPMissionManager_s00e9_bb40* GetMissionManager();                  // 0x00feb9f0
}
namespace SP {
typedef bool (*NounFilterFn)(cPropertyObject_s00e9_bb40*);
}
namespace SP {
bool NounFilter_00cd7d10(cPropertyObject_s00e9_bb40* pObject);
}
namespace SP {
bool NounFilter_00d3d420(cPropertyObject_s00e9_bb40* pObject);
}
namespace SP {
bool NounFilter_00ad4930(cPropertyObject_s00e9_bb40* pObject);
}
namespace SP {
bool NounFilter_00b1e500(cPropertyObject_s00e9_bb40* pObject);
}
namespace SP {
class cGameNounManager_s00e9_bb40 {
public:
    NounVector* GetGameDataVector(NounFilterFn f1, NounFilterFn f2,
                                  NounFilterFn f3, NounFilterFn f4,
                                  uint32_t typeID);      // 0x00b21340
    cTerrainSphere_s00e9_bb40* GetCurrentTerrainSphere();           // 0x00f67d90
    NounObjectVector* FUN_00c5fd60();                    // 0x00c5fd60
};
}
namespace SP {
cGameNounManager_s00e9_bb40* NounManager();                         // 0x00b3d300
}
namespace SP {
void* GetUniverseContext_s00e9_bb40();                              // 0x01021080
}
namespace SP {
void* GetActivePlanetRecord();                           // 0x010212a0
}
namespace SP {
Vector3_s00e9_bb40 FUN_00c4bdc0(void* pVector, int param);          // 0x00c4bdc0
}
// ---- items of slice s00e9bb40 end

// @ 0x00e98a40
int __cdecl GetCreatureDetailLevel(SimPlanetOrbitView* planet)
{
    float orbitRadius = planet->mOrbitRadius540;
    float reference = planet->mOrbit508.GetRadius();
    float ratio = orbitRadius / reference;
    if (gDetailRatioHalf <= ratio)
        return 0;
    float r = ratio;
    if (gDetailRatioThird <= r)
        return 1;
    if (r >= gDetailRatioFifth)
        return 2;
    return 3;
}

// @ 0x00e98ae0
char __cdecl sGetClosestDiseasedCreature(void* param_1, void* param_2)
{
    void* activePlanet = GetActivePlanet();
    if (activePlanet == 0)
        return 0;

    void* local_c = 0;
    void* local_8 = 0;

    cSPMissionManager* mgr = (cSPMissionManager*)GetMissionMgr();
    MissionList* list = mgr->GetMissionList();
    int count = (int)(list->mpEnd - list->mpBegin);
    for (int i = 0; i < count; ++i)
    {
        cSPMission* mission = list->mpBegin[i];
        if (mission->IsActive())
        {
            if (!mission->IsFlagged())
            {
                if (mission->GetTargetPlanet() == activePlanet)
                {
                    if (local_c == 0)
                        local_c = mission->GetItemKey(0x2f9998c);
                    if (local_8 == 0)
                        local_8 = mission->GetItemKey(0x437443d);
                }
            }
        }
    }

    if (local_c != 0)
        return ((cSPMissionEradicate*)local_c)->GetClosestDiseasedAnimal(param_1, param_2);
    if (local_8 != 0)
        return FUN_00c4cb90(param_1, param_2);
    return 0;
}

// @ 0x00e98bd0
bool FUN_00e98bd0(void* pArg1, void* pArg2)
{
    cPlanet* pPlanet = SP_GetActivePlanet();
    if (pPlanet == nullptr)
        return false;

    cSPMissionFetch* pFound = nullptr;
    cMissionList* pList = SP_GetMissionManager()->GetMissionList();
    int32_t nCount = (int32_t)(pList->m_pEnd - pList->m_pBegin);
    for (int32_t i = 0; i < nCount; i++) {
        if (pFound != nullptr)
            break;
        cMission* pMission = pList->m_pBegin[i];
        if (!pMission->IsActive())
            continue;
        if (pMission->M0f8())
            continue;
        if (pMission->GetTargetPlanet() != pPlanet)
            continue;
        pFound = (cSPMissionFetch*)pMission->M00c(0x3470926);
    }

    bool bResult = false;
    if (pFound != nullptr)
        bResult = pFound->CheckTargetPlanet(pArg1, pArg2);
    return bResult;
}

// @ 0x00e98c80
bool FUN_00e98c80(void* pArg1, void* pArg2)
{
    cPlanet* pPlanet = SP_GetActivePlanet();
    if (pPlanet == nullptr)
        return false;

    cSPMissionFetch* pFound = nullptr;
    cMissionList* pList = SP_GetMissionManager()->GetMissionList();
    int32_t nCount = (int32_t)(pList->m_pEnd - pList->m_pBegin);
    for (int32_t i = 0; i < nCount; i++) {
        if (pFound != nullptr)
            break;
        cMission* pMission = pList->m_pBegin[i];
        if (!pMission->IsActive())
            continue;
        if (pMission->M0f8())
            continue;
        if (pMission->GetTargetPlanet() != pPlanet)
            continue;
        pFound = (cSPMissionFetch*)pMission->M00c(0x2afd27e);
    }

    bool bResult = false;
    if (pFound != nullptr)
        bResult = pFound->VerifyTargetPlanet(pArg1, pArg2);
    return bResult;
}

// @ 0x00e98d30
bool FUN_00e98d30(cNounHolder* pNoun)
{
    Key info;
    Key* pInfo = &info;
    Key* pKey = SP_TerraformingManager(pInfo)->FUN_00bbc510();
    const Key& key = pNoun->m_pUFOKeys->m_key;
    if (key.m_nGroup == pKey->m_nGroup && key.m_nType == pKey->m_nType
        && key.m_nInstance == pKey->m_nInstance) {
        int32_t nCount = (int32_t)(pNoun->m_pObjEnd - pNoun->m_pObjBegin);
        cTrailObject** pCur = pNoun->m_pObjBegin;
        for (int32_t i = 0; i < nCount; i++) {
            if ((*pCur)->m_bFlag == 0)
                return true;
            pCur++;
        }
    }
    return false;
}

// @ 0x00e98db0
void cSPUFOGfx::SetVisible(bool bVisible)
{
    void* pModel;
    if (m_pObject == nullptr)
        pModel = nullptr;
    else
        pModel = m_pObject->Pb8(0xb033b403);

    SetIsVisible(bVisible);

    cRenderInstance* pRender = GetRenderS2c();
    m_bShadowed = bVisible ? 1 : 0;
    if (bVisible)
        pRender->m_nFlags |= 1;
    else
        pRender->m_nFlags &= ~1u;

    SP_GonzagoModelWorld()->SetRenderVc4(pRender, bVisible, bVisible, 0);

    if (!bVisible) {
        if (m_pRingEffect != nullptr) {
            FUN_00572020(m_pRingEffect, 0);
            m_pRingEffect = nullptr;
        }
        if (m_pFilterRangeEffect != nullptr)
            m_pFilterRangeEffect->V0c(true);
        if (m_pSelectionEffect != nullptr)
            m_pSelectionEffect->V0c(true);
        if (m_pRolloverEffect != nullptr)
            m_pRolloverEffect->V0c(true);
        return;
    }

    cSpatialObject* pObj = (cSpatialObject*)pModel;
    int32_t nKind = pObj->m_nKind714;
    if (nKind != 0 && m_pRingEffect == nullptr
        && (SP_GetUniverseContext() == 0 || nKind != 3)) {
        Vector3* pPos = ((cLocomotiveObject*)((uint8_t*)pObj + 0x34))
                            ->GetPositionV2c();
        cAudioSystem* pAudio = EA_Audio_GetSystemAT();
        cIVisualEffect* pEffect;
        if (pAudio == nullptr)
            pEffect = nullptr;
        else
            pEffect = pAudio->GetEffectV20();
        m_pRingEffect = pEffect;
        uint32_t nName = (nKind != 0) ? 0xf61417b3 : 0x51766452;
        SP_Start3dSoundByName(nName, pEffect, pPos->x, pPos->y, pPos->z);
    }

    if (pObj->m_nKind714 == 0 && m_pFilterRangeEffect != nullptr)
        m_pFilterRangeEffect->V08(false);

    if (SP_GetUniverseContext() == 0) {
        if (m_pSelectionEffect != nullptr)
            m_pSelectionEffect->V08(false);
    } else if (m_pSelectionEffect != nullptr) {
        m_pSelectionEffect->V0c(true);
    }

    if (SP_GetUniverseContext() == 2) {
        if (m_pRolloverEffect != nullptr)
            m_pRolloverEffect->V08(false);
        return;
    }
    if (m_pRolloverEffect != nullptr)
        m_pRolloverEffect->V0c(true);
}

// @ 0x00e98f60
void* FUN_00e98f60(cNounVector* pNouns, const Vector3* pPos, char (*pFilter)(void*))
{
    void* pBest = nullptr;
    float fBest = 3.402823466e38f;
    void** pCur = pNouns->m_pBegin;
    void** pEnd = pNouns->m_pEnd;
    for (; pCur != pEnd; pCur++) {
        void* pNoun = *pCur;
        if (pFilter(pNoun)) {
            Vector3* pNounPos = ((cNearNoun*)pNoun)->GetPosition();
            float fY = pNounPos->y - pPos->y;
            float fX = pNounPos->x - pPos->x;
            float fZ = pNounPos->z - pPos->z;
            float fDist = (fX * fX + fY * fY) + fZ * fZ;
            if (fDist < fBest) {
                pBest = pNoun;
                fBest = fDist;
            }
        }
    }
    return pBest;
}

// @ 0x00e99010
void FUN_00e99010(Vector3* pOut, cNounVector* pList, const Vector3* pPos)
{
    pOut->x = gDefaultTrailOffset.x;
    pOut->y = gDefaultTrailOffset.y;
    pOut->z = gDefaultTrailOffset.z;
    float fBest = 3.402823466e38f;

    Vector3* pCur = (Vector3*)pList->m_pBegin;
    Vector3* pEnd = (Vector3*)pList->m_pEnd;
    for (; pCur != pEnd; pCur++) {
        Vector3 p;
        p.x = pCur->x;
        p.y = pCur->y;
        p.z = pCur->z;
        float fX = p.x - pPos->x;
        float fY = p.y - pPos->y;
        float fZ = p.z - pPos->z;
        float fDist = (fX * fX + fY * fY) + fZ * fZ;
        if (fDist < fBest) {
            *pOut = p;
            fBest = fDist;
        }
    }
}

// @ 0x00e990f0
cEffectInfo* FUN_00e990f0(cEffectInfo* pSrc, cEffectInfo* pEnd, cEffectInfo* pDst)
{
    for (; pSrc != pEnd; pSrc++, pDst++) {
        if (pDst != nullptr) {
            pDst->m_fX = pSrc->m_fX;
            pDst->m_fY = pSrc->m_fY;
            pDst->m_fZ = pSrc->m_fZ;
            pDst->m_pEffect = pSrc->m_pEffect;
            if (pDst->m_pEffect != nullptr)
                pDst->m_pEffect->AddRef();
        }
    }
    return pDst;
}

// @ 0x00e99140
cEffectRecord* FUN_00e99140(cEffectRecord* pSrc, cEffectRecord* pEnd, cEffectRecord* pDst)
{
    for (; pSrc != pEnd; pSrc++, pDst++) {
        *pDst = *pSrc;
    }
    return pDst;
}

// @ 0x00e991b0
bool FUN_00e991b0(cPropertyObject* pObject)
{
    if (pObject == nullptr)
        return false;
    if (pObject->m_nKind658 != 4)
        return true;

    cPropertyManager* pManager = SP_PropertyManager();
    cIUnknown* pValue = nullptr;
    pManager->GetV2c(pObject->m_nProp64c, 0x34d97fa, &pValue);

    Key key;
    key.m_nGroup = 0;
    key.m_nType = 0;
    key.m_nInstance = 0;
    SP_GetPropertyAsKey(pValue, 0x34f1a4f, &key);

    if (key.m_nGroup != 0x7ecbe6f5) {
        if (pValue != nullptr)
            pValue->Release();
        return false;
    }
    if (pValue != nullptr)
        pValue->Release();
    return true;
}

// @ 0x00e99280
void FUN_00e99280(cSPUFOGfx* pGfx, cTrailSample* pSample)
{
    cLocomotiveObject* pObject = (cLocomotiveObject*)((uint8_t*)pGfx + 0x34);
    Vector3* pPos = pObject->GetPositionV2c();
    float fX = pPos->x;
    float fY = pPos->y;
    float fZ = pPos->z;

    float fInvLen = 1.0f / sqrtf(fX * fX + (fZ * fZ + fY * fY));
    float fNx = fInvLen * fX;
    float fNy = fInvLen * fY;
    float fNz = fInvLen * fZ;

    Vector3* pVel = pObject->GetVelocity();
    float fScale = pVel->y;
    pSample->m_nFlags |= 4;
    pSample->m_nCount++;

    Vector3 offset;
    offset.x = fScale * fNx + fX;
    offset.y = fScale * fNy + fY;
    offset.z = fScale * fNz + fZ;
    pSample->m_fX = offset.x;
    pSample->m_fY = offset.y;
    pSample->m_fZ = offset.z;

    uint8_t quat[16];
    SP_PlanetModel(quat, &offset);
    ((cPlanetModel*)quat)->BuildSurfaceOrientation(quat, &offset);

    float matrix[9];
    SP_Matrix3FromQuaternion(matrix, quat);
    pSample->m_nFlags |= 2;
    pSample->m_nCount++;
    for (int32_t i = 0; i < 9; i++)
        pSample->m_aMatrix[i] = matrix[i];
}

// @ 0x00e993c0
cSPUFOGfx* cSPUFOGfx::Construct()
{
    cSpatialObjectView_Construct();
    m_pObject = nullptr;
    m_fScaleA = 1.0f;
    m_fScaleB = 1.0f;
    m_fScaleC = 1.0f;
    m_nHash = 0x9d5db21a;
    m_nMode = 0;
    m_nModeB = 0;
    m_bShadowed = 0;
    m_pRingEffect = nullptr;
    m_pFilterRangeEffect = nullptr;
    m_pSelectionEffect = nullptr;
    m_pRolloverEffect = nullptr;
    m_pLocomotive = nullptr;
    m_nTrailId = -1;
    cGonzagoTimer_Construct();
    return this;
}

// @ 0x00e994f0
cSPUFOGfx* __stdcall FUN_00e994f0(void* pOwner)
{
    cSPUFOGfx* pMemory = (cSPUFOGfx*)operator_new(0xd8, "Simulator/cUFOGfx", 0,
                                                  0, 0, 0);
    cSPUFOGfx* pGfx;
    if (pMemory != nullptr)
        pGfx = pMemory->Construct();
    else
        pGfx = nullptr;

    pGfx->S24(pOwner);
    cRenderInstance* pRender = pGfx->GetRenderS2c();
    if (SP_GetCurrentGameMode() != (cPlanet*)&gGameModeSpace)
        pRender->m_nFlags |= 0x20;
    return pGfx;
}

// @ 0x00e99550
void cSPUFOGfx::UpdateTrail()
{
    void* pModel;
    if (m_pObject == nullptr)
        pModel = nullptr;
    else
        pModel = m_pObject->Pb8(0xb033b403);

    cSpatialObject* pObj = (cSpatialObject*)pModel;
    bool bInSpace = pObj->m_nKind714 != 0;
    FUN_00b3d460();
    int32_t nContext = SP_GetUniverseContext();
    int32_t nEffectId = 0;

    if (!bInSpace || nContext == 2)
        nEffectId = gkPlanetEffects[FUN_00e98a40(pObj)];
    if (!bInSpace && nContext == 2) {
        switch (pObj->m_nMode76c) {
        case 0:
        case 1:
        case 4:
            nEffectId = gkPlanetEffects[FUN_00e98a40(pObj)];
            break;
        case 2:
            nEffectId = 0x5c95b24;
            break;
        case 3:
            nEffectId = 0x5c95b28;
            break;
        default:
            break;
        }
    }
    if (bInSpace && nContext != 2)
        nEffectId = gkSpaceEffects[FUN_00e98a40(pObj)];

    int32_t nCurrent = 0;
    if (m_pFilterRangeEffect != nullptr)
        nCurrent = m_pFilterRangeEffect->V60();

    if (nEffectId == nCurrent) {
        if (!m_bShadowed)
            return;
    } else {
        if (m_pFilterRangeEffect != nullptr) {
            m_pFilterRangeEffect->V0c(false);
            m_pFilterRangeEffect = nullptr;
        }
        if (nEffectId != 0) {
            cEffectsManager* pManager = SP_EffectsManagerPtr();
            m_pFilterRangeEffect = nullptr;
            pManager->CreateV2c(nEffectId, 0, &m_pFilterRangeEffect);
        }
        if (!m_bShadowed) {
            if (m_pFilterRangeEffect != nullptr)
                m_pFilterRangeEffect->V0c(true);
            return;
        }
    }

    if (m_pFilterRangeEffect == nullptr)
        return;

    FUN_00c37360();
    if (!FUN_00c37500() && pObj->m_bFlag74c != 0) {
        m_pFilterRangeEffect->V0c(false);
        return;
    }

    Vector3 color;
    color.x = 0.0f;
    color.y = 0.0f;
    color.z = 0.0f;
    m_pFilterRangeEffect->V44(5, &color.x, 3);
    m_pFilterRangeEffect->V08(false);

    float fScale = 1.0f;
    switch (nContext) {
    case 0:
    case -1:
        FUN_00c37360();
        fScale = FUN_00c37510();
        break;
    case 1:
        FUN_00c37360();
        fScale = FUN_00c37520();
        break;
    case 2:
        FUN_00c37360();
        fScale = FUN_00c37530();
        break;
    default:
        break;
    }
    if (fScale <= 1.5258789e-05f)
        fScale = 1.0f;

    cLocomotiveObject* pLoco = (cLocomotiveObject*)((uint8_t*)this + 0x34);
    float fLoco = pLoco->GetScaleV34();
    Vector3* pVel = pLoco->GetVelocity();
    float fSpeed = sqrtf((pVel->x * pVel->x + pVel->y * pVel->y)
                         + pVel->z * pVel->z) / fScale;
    FUN_00c37360();
    float fMin = FUN_00c37540();
    if (fSpeed <= fMin)
        fSpeed = fMin;
    if (fSpeed >= 1.0f)
        fSpeed = 1.0f;

    cRenderInstance* pRender = GetRenderS2c();

    cTrailSample sample;
    sample.m_nFlags = 0;
    sample.m_nCount = 0;
    sample.m_fX = 0.0f;
    sample.m_fY = 0.0f;
    sample.m_fZ = 0.0f;
    sample.m_fScale = 1.0f;
    for (int32_t i = 0; i < 9; i++)
        sample.m_aMatrix[i] = 0.0f;

    sample.m_fX = pRender->m_fX;
    sample.m_fY = pRender->m_fY;
    sample.m_fZ = pRender->m_fZ;
    sample.m_fScale = fSpeed * fLoco;
    for (int32_t i = 0; i < 9; i++)
        sample.m_aMatrix[i] = pRender->m_aMatrix[i];
    sample.m_nFlags |= 6;
    sample.m_nCount += 3;

    m_pFilterRangeEffect->V18(&sample);
    m_pFilterRangeEffect->V44(0, &sample.m_fX, 1);
}

// @ 0x00e998d0
void cSPUFOGfx_s00e9_98d0::UpdateShadow()
{
    cSpatialObj* uni = 0;
    if (m_pObj0c != 0)
        uni = (cSpatialObj*)(*(void* (__thiscall**)(void*, i32))(*(void***)m_pObj0c)[0xb8 / 4])(m_pObj0c, (i32)0xb033b403);

    if (SP_GetUniverseContext_s00e9_98d0() != 0) {
        if (m_84.mpObject) m_84.mpObject->Stop(1);
        return;
    }

    void* app     = SP_App();
    void* app2    = (*(void* (__thiscall**)(void*))(*(void***)app)[0x50 / 4])(app);
    cViewer* view = (cViewer*)(*(void* (__thiscall**)(void*))(*(void***)app2)[0x1c / 4])(app2);

    Vector3_s00e9_98d0 camPos = g_camDefault;
    Vector3_s00e9_98d0 camDir = g_camDefault;
    if (view != 0)
        view->GetCameraLocationInfo(&camPos, &camDir, 0, 0);

    cTransformSub* xf = &uni->m_transform;
    Vector3_s00e9_98d0* p0 = xf->GetPosition();
    float facing = p0->z * camPos.z + p0->y * camPos.y + p0->x * camPos.x;
    if (facing < 0.0f || m_flag78 == 0) {
        if (m_84.mpObject) m_84.mpObject->Stop(1);
        return;
    }

    Vector3_s00e9_98d0 surface;
    SP_PlanetModel(&surface, p0);
    SP_FUN_b81630(&surface, &surface, p0);

    if (SP_GetUniverseContext_s00e9_98d0() == 0) {
        SP_PlanetModel(p0);
        if (SP_FUN_b7e3e0(p0) != 0) {
            float dist = SP_VectorLength(p0) -
                         (float)sqrt(surface.x * surface.x + surface.y * surface.y +
                                     surface.z * surface.z);
            if (dist < g_distEpsilon) {
                if (!m_84.mpObject->IsActive())
                    m_84.mpObject->Start(0);

                Vector3_s00e9_98d0 edge;
                xf->GetLocalPoint(&edge);
                Vector3_s00e9_98d0* p1 = xf->GetPosition();
                Vector3_s00e9_98d0 dir;
                SP_Vector3_Normalize(&dir, p1);

                Vector3_s00e9_98d0 normal;
                SP_PlanetModel(&normal, &dir);
                SP_FUN_b81630(&normal, &normal, &dir);

                Vector3_s00e9_98d0 tangent, up;
                tangent.x = edge.y * dir.z - edge.z * dir.y;
                tangent.y = edge.z * dir.x - edge.x * dir.z;
                tangent.z = edge.x * dir.y - edge.y * dir.x;
                Vector3_s00e9_98d0* nt = SP_normalized_safe(&tangent, &tangent);
                up.x = nt->y * dir.z - nt->z * dir.y;
                up.y = nt->z * dir.x - nt->x * dir.z;
                up.z = nt->x * dir.y - nt->y * dir.x;
                SP_normalized_safe(&up, &up);

                XformMsg msg;
                msg.pos = *p1;
                msg.flags |= 4; msg.count += 1;
                Matrix3 basis = SP_Matrix3FromFacingAndUp(&dir, &up);
                msg.mat = basis;
                msg.flags |= 2; msg.count += 1;
                m_84.mpObject->SetTransform(&msg);
                return;
            }
        }
    }

    if (m_84.mpObject->IsActive())
        m_84.mpObject->Stop(0);
}

// @ 0x00e99c50
void cSPUFOGfx_s00e9_98d0::UpdateSpacePhase(void* /*unused*/)
{
    cSpatialObj* uni = 0;
    if (m_pObj0c != 0)
        uni = (cSpatialObj*)(*(void* (__thiscall**)(void*, i32))(*(void***)m_pObj0c)[0xb8 / 4])(m_pObj0c, (i32)0xb033b403);

    if (uni->m_state714 == 0 && SP_GetUniverseContext_s00e9_98d0() == 2) {
        bool entering = SP_FUN_10449e0(SP_FUN_1046fc0(5));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(0));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(1));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(4));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(2));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(3));
        if (entering) {
            if (!m_88.mpObject->IsActive() && m_flag78 != 0)
                m_88.mpObject->Start(0);
            (*(void (__thiscall**)(void*))(*(void***)this)[0x2c / 4])(this);

            XformMsg msg;
            msg.pos = g_spawnOffset;
            msg.f10 = 0x3f800000;
            msg.mat.Set(&g_baseRotation);
            if (uni->m_flag74c == 0) {
                msg.pos.x = uni->m_v718;
                msg.pos.y = uni->m_v71c;
                msg.pos.z = uni->m_v720;
            } else {
                Vector3_s00e9_98d0* city = SP_GetCities(SP_IsArchived());
                msg.pos = *city;
            }
            msg.flags |= 4; msg.count += 1;

            Vector3_s00e9_98d0 fwd;
            float proj = (-uni->m_v71c) * g_upAxis.y +
                         (-uni->m_v720) * g_upAxis.z +
                         (-uni->m_v718) * g_upAxis.x;
            fwd.z = -uni->m_v720 - proj * g_upAxis.z;
            fwd.y = -uni->m_v71c - proj * g_upAxis.y;
            fwd.x = -uni->m_v718 - proj * g_upAxis.x;
            float inv = 1.0f / (float)sqrt(fwd.x * fwd.x + fwd.y * fwd.y +
                                           fwd.z * fwd.z + g_normEpsilon);
            fwd.x *= inv; fwd.y *= inv; fwd.z *= inv;
            Matrix3 basis = SP_Matrix3FromFacingAndUp(&fwd, &g_upAxis);
            msg.mat = basis;
            msg.flags |= 2; msg.count += 1;

            void* sim = SP_GetUFOSimulator();
            msg.f10 = (u32)(float)SP_GetMaxTravelDistance(sim);
            msg.count += 1;
            m_88.mpObject->SetTransform(&msg);

            if (!m_8c.mpObject->IsActive() && m_flag78 != 0)
                m_8c.mpObject->Start(0);
            void* sim2 = SP_GetUFOSimulator();
            msg.f10 = (u32)(float)SP_GetMaxZ(sim2);
            msg.count += 1;
            m_8c.mpObject->SetTransform(&msg);
            return;
        }
    }

    m_88.mpObject->Stop(1);
    m_8c.mpObject->Stop(1);
}

// @ 0x00e99f90
void cSPUFOGfx_s00e9_98d0::UpdateAOERepairEffect(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (obj->HasFlag(2)) {
        obj->SetFlag(2, 0);
        i32 key = obj->m_state714 != 0 ? (i32)(0xa0018993 + 0xb8438bce)
                                       : (i32)0xa0018993;
        DROP_EFFECT(m_9c);
        EffectsMgr* mgr = SP_EffectsManager();
        DROP_EFFECT(m_9c);
        mgr->CreateEffect(key, 0, &m_9c.mpObject);
        if (m_9c.mpObject)
            m_9c.mpObject->Start(0);
    }

    if (m_9c.mpObject) {
        if (m_9c.mpObject->IsActive()) {
            XformMsg msg;
            Vector3_s00e9_98d0* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_9c.mpObject->SetTransform(&msg);
            return;
        }
        DROP_EFFECT(m_9c);
    }
}

// @ 0x00e9a0c0
void cSPUFOGfx_s00e9_98d0::UpdateRallyCallEffect(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (obj->HasFlag(3)) {
        obj->SetFlag(3, 0);
        i32 key = obj->m_state714 != 0 ? (i32)(0x2c860712 + 0xf3ab5d75)
                                       : (i32)0x2c860712;
        DROP_EFFECT(m_a0);
        EffectsMgr* mgr = SP_EffectsManager();
        DROP_EFFECT(m_a0);
        mgr->CreateEffect(key, 0, &m_a0.mpObject);
        if (m_a0.mpObject)
            m_a0.mpObject->Start(0);
    }

    if (m_a0.mpObject) {
        if (m_a0.mpObject->IsActive()) {
            XformMsg msg;
            Vector3_s00e9_98d0* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_a0.mpObject->SetTransform(&msg);
            return;
        }
        DROP_EFFECT(m_a0);
    }
}

// @ 0x00e9a1f0
void cSPUFOGfx_s00e9_98d0::UpdateE9A1F0(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    int key = 0;
    if (obj->HasFlag(7)) {
        obj->SetFlag(7, 0);
        key = SP_FNVHash("UI_unlock_space_rare", 0x811c9dc5, 1);
    } else if (obj->HasFlag(5)) {
        obj->SetFlag(5, 0);
        key = SP_FNVHash("UI_unlock_space_tool", 0x811c9dc5, 1);
    } else if (obj->HasFlag(6)) {
        obj->SetFlag(6, 0);
    }

    if (key != 0) {
        EffectsMgr* mgr = SP_EffectsManager();
        DROP_EFFECT(m_ac);
        mgr->CreateEffect(key, 0, &m_ac.mpObject);
        if (m_ac.mpObject) {
            XformMsg msg;
            SP_FUN_e99280(obj, &msg);
            m_ac.mpObject->SetTransform(&msg);
            m_ac.mpObject->Start(0);
        }
    }

    if (m_ac.mpObject) {
        if (m_ac.mpObject->IsActive()) {
            XformMsg msg;
            SP_FUN_e99280(obj, &msg);
            m_ac.mpObject->SetTransform(&msg);
            return;
        }
        DROP_EFFECT(m_ac);
    }
}

// @ 0x00e9a360
void cSPUFOGfx_s00e9_98d0::UpdateShieldEffect(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (!obj->m_contact.IsLatched() || obj->m_state714 == 1) {
        if (m_a4.mpObject) {
            m_a4.mpObject->Stop(0);
            DROP_EFFECT(m_a4);
        }
    } else if (m_a4.mpObject == 0) {
        // An AutoRefCount::Clear() here, not the DROP_EFFECT macro: the macro
        // would be folded away (the guard already implies the slot is null).
        m_a4.Clear();
        EffectsMgr* mgr = SP_EffectsManager();
        m_a4.Clear();
        mgr->CreateEffect((i32)0xdc08f952, 0, &m_a4.mpObject);
        if (m_a4.mpObject)
            m_a4.mpObject->Start(0);
    }

    if (m_a4.mpObject) {
        if (m_a4.mpObject->IsActive()) {
            XformMsg msg;
            Vector3_s00e9_98d0* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_a4.mpObject->SetTransform(&msg);
        }
    }
}

// @ 0x00e9a470
void cSPUFOGfx_s00e9_98d0::UpdateE9A470(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (obj->m_contact.IsConnected()) {
        if (m_bc.mpObject == 0) {
            EffectsMgr* mgr = SP_EffectsManager();
            DROP_EFFECT(m_bc);
            mgr->CreateEffect((i32)0x46cca23c, 0, &m_bc.mpObject);
            if (m_bc.mpObject)
                m_bc.mpObject->Start(0);
        }
    } else if (m_bc.mpObject) {
        m_bc.mpObject->Stop(0);
        DROP_EFFECT(m_bc);
    }

    if (m_bc.mpObject) {
        if (m_bc.mpObject->IsActive()) {
            XformMsg msg;
            Vector3_s00e9_98d0* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;

            void* q = obj->m_transform.GetOrientation();
            Matrix3 basis = SP_Matrix3FromQuaternion(q);
            msg.mat = basis;
            msg.flags |= 2; msg.count += 1;
            m_bc.mpObject->SetTransform(&msg);
        }
    }
}

// @ 0x00e9a590
void cSPUFOGfx_s00e9_98d0::UpdateCloakEffect(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (!obj->HasFlag(1) && obj->m_state714 != 5) {
        if (m_a8.mpObject) {
            m_a8.mpObject->Stop(0);
            DROP_EFFECT(m_a8);
        }
    } else if (m_a8.mpObject == 0) {
        // AutoRefCount::Clear() rather than DROP_EFFECT; see UpdateShieldEffect.
        m_a8.Clear();
        EffectsMgr* mgr = SP_EffectsManager();
        m_a8.Clear();
        mgr->CreateEffect((i32)0xaa0ddbdf, 0, &m_a8.mpObject);
        if (m_a8.mpObject)
            m_a8.mpObject->Start(0);
    }

    if (m_a8.mpObject) {
        if (m_a8.mpObject->IsActive()) {
            XformMsg msg;
            Vector3_s00e9_98d0* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_a8.mpObject->SetTransform(&msg);
        }
    }
}

// @ 0x00e9a6a0
void cSPUFOGfx_s00e9_98d0::UpdateE9A6A0(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (obj->HasFlag(8)) {
        obj->SetFlag(8, 0);
        EffectsMgr* mgr = SP_EffectsManager();
        DROP_EFFECT(m_b4);
        mgr->CreateEffect((i32)0x4338a32d, 0, &m_b4.mpObject);
        if (m_b4.mpObject) {
            XformMsg msg;
            SP_FUN_e99280(obj, &msg);
            m_b4.mpObject->SetTransform(&msg);
            m_b4.mpObject->Start(0);
        }
    }

    if (m_b4.mpObject) {
        if (m_b4.mpObject->IsActive()) {
            XformMsg msg;
            Vector3_s00e9_98d0* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_b4.mpObject->SetTransform(&msg);
            return;
        }
        DROP_EFFECT(m_b4);
    }
}

// @ 0x00e9a7c0
bool cUfoListener::HandleMessage(uint32_t interfaceId, void* arg)
{
    if (interfaceId == 0x604c6f4) {
        // "the UFO moved": copy the live transform's scale onto the view and bump its counter
        cSpatialObject_s00e9_a7c0* pTarget = Parent()->v2c();
        cSPGameDataUFO* ufo = Parent()->mpObject
                            ? (cSPGameDataUFO*)Parent()->mpObject->Cast(0xb033b403) : 0;
        pTarget->mTransformScale = ufo->mTransform.GetScale();
        pTarget->mChangeCount++;
        return true;
    }
    if (interfaceId != 0x6834927)
        return false;

    // "send the UFO transform to the glow effect"
    if (Parent()->mpObject == 0)
        return true;
    cSPGameDataUFO* ufo = (cSPGameDataUFO*)Parent()->mpObject->Cast(0xb033b403);
    if (ufo == 0 || ufo->mMode != 0)
        return true;

    AutoRef<IEffect_s00e9_a7c0> effect;
    EffectsManager()->CreateEffect(0xbb1ceb80, 0, effect.AsPointer());
    if (effect.mpObject == 0)
        return true;

    XformMsg_s00e9_a7c0 msg;
    msg.SetTarget(ufo->mTransform.GetPosition());
    Matrix33T matrix;
    Matrix3FromQuaternion(matrix, *ufo->mTransform.GetOrientation());
    msg.mScale = ufo->mTransform.GetScale();
    msg.mVersion++;
    msg.mMatrix = matrix;
    msg.mFlags |= 2;
    msg.mVersion++;
    effect.mpObject->SendMessage(&msg);
    effect.mpObject->v08(0);
    return true;
}

// @ 0x00e9a940
void cSPUFOGfx_s00e9_a7c0::SetUFOModel(ResourceKey* key, bool announce)
{
    const ResourceKey origKey = *key;
    cModelWorld* world = GonzagoModelWorld();
    IGameObject* gameObject = GetGameObject();
    cSPGameDataUFO* ufo = gameObject ? (cSPGameDataUFO*)gameObject->Cast(0xb033b403) : 0;
    const bool isMode0 = ufo->mMode == 0;

    if (announce) {
        UFOModelMessage msg;
        msg.mID = 0x2ea8fb98;
        msg.mA = 0;
        if (isMode0) {
            msg.mB = 0;
            msg.mA = 1;
        } else {
            msg.mB = 3;
        }
        GetMessageBus()->Post(key, &msg);
    }

    if (isMode0 || GetUniverseContext() == 2) {
        cPropertyList* list = new ("Simulator", 0, 0, 0, 0) cPropertyList();
        if (list)
            list->AddRef();
        AutoRef<cPropertyList> parent;
        if (PropertyManager()->GetPropertyList(key->instanceID, key->groupID, parent.AsPointer()))
            list->SetParent(parent.mpObject);
        {
            Variant value;
            float colour[4];
            colour[0] = 10000.0f;
            colour[1] = 10000.0f;
            colour[2] = 10000.0f;
            colour[3] = 10000.0f;
            value.Set(0x33, 0, colour, 0x10, 1);
            list->SetProperty(0x2e33a81, &value);
        }
        if (isMode0) {
            Variant value;
            uint32_t zero = 0;
            value.SetU32(&zero);
            list->SetProperty(0x2a907b8, &value);
        }
        key->groupID = (key->groupID & 0xffff72ff) | 0x7200;
        PropertyManager()->AddPropertyList(list, key->instanceID, key->groupID);
        list->Release();
    }

    cGameModel* model = world->LoadModel(key->instanceID, key->groupID, 0);
    if (model) {
        model->mRefCount++;
        SetModel(model, world);
        if (GetCurrentGameMode() != 0x1654c10)
            model->mFlags |= 0x20;
        model->mFlags |= 0x10;
        model->mMask[0] = 0;
        model->mMask[1] = 0;
        uint32_t bit = ModelManager()->GetBitIndex(0x64ac354, 0);
        if (bit < 0x40)
            model->mMask[bit >> 5] &= ~(1 << (bit & 0x1f));

        IRefObject* effect = 0;
        if (mpObject)
            effect = mpObject->Cast(0x17f243b);
        IRefObject* oldEffect = model->mpEffect;
        if (effect != oldEffect) {
            if (effect)
                effect->AddRef();
            model->mpEffect = effect;
            if (oldEffect)
                oldEffect->Release();
        }

        if (StarManager()->GetEmpireByID(ufo->GetEmpireID()) && ufo->mMode != 0 && ufo->mMode != 5) {
            Vector3_s00e9_a7c0 colour;
            StarManager()->GetEmpireByID(ufo->GetEmpireID())->GetColor(&colour);
            mColor = colour;
            model->mFlags |= 4;
            model->mColor = mColor;
        }

        if (isMode0) {
            float zero = 0.0f;
            world->SetModelParam(model, 0x13, &zero, 1, 0);
        }

        ufo->Refresh();
        const bool visible = !((model->mFlags >> 14) & 1);
        mbModelVisible = visible;
        if (visible)
            mpObject->mFlags |= 0x10;
        else
            mpObject->mFlags &= ~0x10u;
        if (!mbModelVisible)
            mpObject->SetEffectPos(&model->mEffectPos, 1.0f);
    }

    EnsureEffect(mFilterRangeEffect, 0x3d6f0bf);
    EnsureEffect(mContextEffect, 0x628a6b8e);
    EnsureEffect(mSelectionEffect, 0x3d6f0d2);
    EnsureEffect(mRolloverEffect, 0x829c3007);
    EnsureEffect(mRadarEffect, 0xdec8dff8);
    SetVisible(ufo->GetVisible());

    if (model) {
        if (model->mpPropertyList) {
            AutoRef<IResource> resource;
            AutoRefText text;
            ResourceKey textKey;
            textKey.instanceID = origKey.instanceID;
            textKey.typeID = 0x30bdee3;
            textKey.groupID = origKey.groupID;
            IResourceManager* manager = GetManager();
            if (manager->GetResource(&textKey, (IResource**)resource.AsPointer(), 0, 0, 0, 0)) {
                text = resource.mpObject ? (IWinText*)resource.mpObject->Cast(0x30bdee3) : 0;
            }
            if (text.mpObject) {
                WStr name(0, 0);
                name.RangeInitialize(text.mpObject->GetText());
                ufo->SetName(&name);
                text.mpObject->Release();
            } else {
                WStr name;
                GetPropertyAsString16(model->mpPropertyList, 0x43afa7e, &name);
                ufo->SetName(&name);
            }
        }
        if (model->mRefCount > 1)
            model->mRefCount--;
        else
            model->mpOwner->DisposeModel(model, (model->mFlags >> 31) & 1);
    }
}

// @ 0x00e9b030
void AssetInfoVector::Insert(AssetInfo* pos, const AssetInfo* value)
{
    AssetInfo* pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        // a value that lives inside the vector moves when the tail is shifted
        const AssetInfo* src = value;
        if (value >= pos && value < pEnd)
            src = value + 1;
        ::new ((void*)pEnd) AssetInfo(pEnd[-1]);
        FUN_0065ce10(pos, pEnd - 1, pEnd);
        *pos = *src;
        mpEnd++;
        return;
    }

    const size_t nSize = (size_t)(mpEnd - mpBegin);
    size_t nNewCapacity = nSize ? nSize * 2 : 1;
    AssetInfo* pNew = 0;
    if (nNewCapacity != 0)
        pNew = (AssetInfo*)operator new(nNewCapacity * sizeof(AssetInfo), "Simulator", 0, 0,
                                        kEastlAllocatorFile, 0xd1);

    AssetInfo* pNewPos = FUN_00e990f0(mpBegin, pos, pNew);
    FUN_0065c750(mpBegin, pos, pNew);
    ::new ((void*)pNewPos) AssetInfo(*value);
    AssetInfo* pNewEnd = FUN_00e990f0(pos, mpEnd, pNewPos + 1);
    FUN_0065c750(pos, mpEnd, pNewPos + 1);

    if (mpBegin != 0 && ((int32_t*)mpBegin)[-1] != 0)
        operator delete[](mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCapacity = pNew + nNewCapacity;
}

// @ 0x00e9b1a0
void cSPUFOGfx_s00e9_a7c0::Init(void* object)
{
    bool announce = true;
    ResourceKey key;
    key.instanceID = 0;
    key.typeID = 0;
    key.groupID = 0;

    cSPGameDataUFO* ufo = 0;
    if (object != 0) {
        ufo = (cSPGameDataUFO*)((IGameObject*)object)->Cast(0xb033b403);
        if (ufo != 0) {
            FUN_00c37230(ufo, 0, &key, &announce);
            if (key.instanceID == 0 && key.typeID == 0 && key.groupID == 0) {
                key.typeID = 0x476a98c7;
                key.groupID = kUfoDefaultKeyGroup;
                key.instanceID = 0x9d5db21a;
                announce = true;
            }
        }
    }

    reinterpret_cast<cSpatialObjectView_s00e9_a7c0*>(this)->Init(object);
    SetUFOModel(&key, announce);
    SetVisible(ufo->GetVisible());

    const void* cookie = this ? &mListener : 0;
    IMessageServer* server = MessageServer();
    mpMessageServer = server;
    mpMessageServerCookie = cookie;
    mServerBinding.mpHandlers = kRadarTimerHandlers;
    mServerBinding.mRefCount = 2;
    mServerBinding.mState = 0;
    if (server != 0 && cookie != 0) {
        for (const uint32_t* p = kRadarTimerHandlers; p < kRadarTimerHandlers + 2; ++p)
            server->AddListener(cookie, *p);
    }
}

// @ 0x00e9b2b0
void cSPUFOGfx_s00e9_b2b0::UpdateHitEffects()
{
    cSPGameDataUFO_s00e9_b2b0* ufo = mpObject ? (cSPGameDataUFO_s00e9_b2b0*)mpObject->Cast(0xb033b403) : 0;

    unsigned i = 0;
    while (i < size()) {
        if (!mEffects.mpBegin[i].mpEffect->IsRunning()) {
            erase(mEffects.mpBegin + i);
        } else {
            Transform t;
            cLocomotiveIface* loco = &ufo->mLoco;
            const Vector3_s00e9_b2b0* ufoPos = loco->GetPosition();
            const Quaternion* q = loco->GetOrientation();

            Vector3_s00e9_b2b0 rotated = Rotate(q, mEffects.mpBegin[i].mOffset);
            Vector3_s00e9_b2b0 pos(ufoPos->x + rotated.x, ufoPos->y + rotated.y, ufoPos->z + rotated.z);
            t.SetOffset(pos);

            Vector3_s00e9_b2b0 up = Rotate(q, kUpAxis);
            Vector3_s00e9_b2b0 facing(pos.x - ufoPos->x, pos.y - ufoPos->y, pos.z - ufoPos->z);
            Quaternion orient;
            QuaternionFromFacingAndUp(&orient, &facing, &up);
            Matrix3_s00e9_b2b0 mat;
            t.SetRotation(*Matrix3FromQuaternion(&mat, &orient));

            mEffects.mpBegin[i].mpEffect->SetSourceTransform(t);
            ++i;
        }
    }
}

// @ 0x00e9b8e0
void cSPUFOGfx_s00e9_b2b0::ClearEffects()
{
    SetVisible(false);

    VecUFO& vector = mEffects;
    int count = (int)(vector.mpEnd - vector.mpBegin);
    if (count > 0) {
        int offset = 0;
        do {
            cIVisualEffect_s00e9_b2b0* effect =
                *(cIVisualEffect_s00e9_b2b0**)((uint8_t*)vector.mpBegin + offset + 0x0c);
            void* vtable = *(void**)effect;
            void* stop = ((void**)vtable)[0x0c / 4];
            ((void (__thiscall*)(void*, int))stop)(effect, 1);
            effect = *(cIVisualEffect_s00e9_b2b0**)((uint8_t*)vector.mpBegin + offset + 0x0c);
            if (effect != 0) {
                *(cIVisualEffect_s00e9_b2b0**)((uint8_t*)vector.mpBegin + offset + 0x0c) = 0;
                vtable = *(void**)effect;
                void* release = ((void**)vtable)[0x04 / 4];
                ((void (__thiscall*)(void*))release)(effect);
            }
            offset += 0x10;
            --count;
        } while (count != 0);
    }

    vector.erase(vector.mpBegin, vector.mpEnd);

    ReleaseEffect(mEffectA8);
    ReleaseEffect(mFilterRangeEffect);
    ReleaseEffect(mEffectB8);
    ReleaseEffect(mSelectionEffect);
    ReleaseEffect(mRolloverEffect);
    ReleaseEffect(mRadarEffect);
    ReleaseEffect(mAOERepairEffect);
    ReleaseEffect(mRallyCallEffect);
    ReleaseEffect(mEffectB0);
    ReleaseEffect(mEffectAc);
    ReleaseEffect(mEffectBc);

    void* handler = mpHandler;
    if (handler != 0) {
        void* arg1 = (void*)mHandler44;
        void* arg2 = (void*)mHandler48;
        void* arg3 = (void*)mHandler4c;
        void* arg4 = (void*)mHandler50;
        mpHandler = 0;
        RemoveHandler(handler, arg1, arg2, arg3, arg4);
    }
}

// @ 0x00e9c530
namespace SP {
cSPUFOGfx_s00e9_bb40::~cSPUFOGfx_s00e9_bb40()
{
    ClearEffects();
}
}  // namespace SP

// @ 0x00e9c6d0
namespace SP {
bool GetAbductedNounsCenter(int param, Vector3_s00e9_bb40* out)
{
    cGameNounManager_s00e9_bb40* manager = NounManager();
    NounVector* nouns = manager->GetGameDataVector(
        NounFilter_00cd7d10, NounFilter_00d3d420, NounFilter_00ad4930,
        NounFilter_00b1e500, 0x2dd8c42);
    int count = (int)(nouns->mpEnd - nouns->mpBegin);
    SpVector<Vector3_s00e9_bb40> positions;
    for (int i = 0; i < count; ++i) {
        cPropertyObject_s00e9_bb40* noun = nouns->mpBegin[i];
        if (FUN_00e991b0(noun))
            positions.push_back(*noun->mLoco.GetPosition());
    }
    if (positions.mpBegin == positions.mpEnd)
        return false;
    *out = FUN_00c4bdc0(&positions, param);
    return true;
}
}  // namespace SP

// @ 0x00e9c7f0
namespace SP {
bool GetMissionObjectCenter(int param, Vector3_s00e9_bb40* out)
{
    cSPMission_s00e9_bb40* mission = GetMissionManager()->GetMissionByID(0x7bdbb97d);
    if (!mission)
        return false;
    cSPMission_s00e9_bb40* context = mission->GetMissionContext(0x422227e);
    if (!context)
        return false;
    if (!context->IsActive())
        return false;
    if (context->IsFlagged())
        return false;
    if (GetUniverseContext_s00e9_bb40())
        return false;
    void* planetRecord = GetActivePlanetRecord();
    if (planetRecord != context->FUN_00c5f3d0()
        || NounManager()->GetCurrentTerrainSphere()->FUN_00c772c0(0x4922e21)) {
        if (planetRecord != context->FUN_00c5f3b0()
            || NounManager()->GetCurrentTerrainSphere()->FUN_00c772c0(0x4922e1f))
            return false;
    }
    NounObjectVector* objects = NounManager()->FUN_00c5fd60();
    int count = (int)(objects->mpEnd - objects->mpBegin);
    Vector3List positions;
    for (int i = 0; i < count; ++i) {
        cGameDataObject* object = objects->mpBegin[i];
        if (object && (object->mTypeID == 0x611a05e || object->mTypeID == 0x611a05f))
            positions.push_back(*object->mLoco.GetPosition());
    }
    if (positions.mpBegin == positions.mpEnd)
        return false;
    *out = FUN_00c4bdc0(&positions, param);
    return true;
}
}  // namespace SP
