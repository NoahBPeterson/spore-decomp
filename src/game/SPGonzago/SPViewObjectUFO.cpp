// src/game/SPGonzago/SPViewObjectUFO.cpp -- migrated from slice(s) s00e998d0, s00e98bd0 by tools/migrate/rewrite.py
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
class cNounVector {
public:
    void** m_pBegin;                             // +0x00
    void** m_pEnd;                               // +0x04
};
class cNearNoun {
public:
    Vector3* GetPosition();                      // 0x00c6acc0
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
extern int32_t gkSpaceEffects[16];               // 0x016c6340
extern int32_t gkPlanetEffects[16];              // 0x016c6380
extern char gGameModeSpace;                      // 0x01654c10
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
extern Vector3 gDefaultTrailOffset;              // 0x016c6350

// ---- items of slice s00e998d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
Matrix3 SP_Matrix3FromQuaternion(const void* quat);                    // @0x59c190
int     SP_FNVHash(const char* str, u32 seed, int mode);           // @0x932e80
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
    void UpdateE9A1F0(cSpatialObj* obj);
    void UpdateShieldEffect(cSpatialObj* obj);  // 0x00e9a360 (cSPUFOGfx::UpdateShieldEffect)
    void UpdateE9A470(cSpatialObj* obj);
    void UpdateCloakEffect(cSpatialObj* obj);  // 0x00e9a590 (cSPUFOGfx::UpdateCloakEffect)
    void UpdateE9A6A0(cSpatialObj* obj);
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
