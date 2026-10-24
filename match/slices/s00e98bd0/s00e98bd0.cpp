// s00e98bd0 -- the flying-saucer visual effect (cSPUFOGfx): the two mission
// lookups that gate the saucer missions, the terraforming key check, the
// visibility switch, the nearest-noun / nearest-position searches, the
// effect-info copy helpers, the trail update and the object's constructor and
// factory.
//
//   0x00e98bd0 mission lookup A        0x00e99010 nearest position
//   0x00e98c80 mission lookup B        0x00e990f0 effect-info copy
//   0x00e98d30 terraforming key check  0x00e99140 effect-info assign copy
//   0x00e98db0 SetVisible              0x00e991b0 property gate
//   0x00e98f60 nearest noun           0x00e99280 trail point
//   0x00e993c0 ctor                    0x00e994f0 factory
//   0x00e99550 UpdateTrail
#include "types.h"
#include <math.h>

#define nullptr 0

// ---------------------------------------------------------------------------
// engine types
// ---------------------------------------------------------------------------

struct Vector3 {
    float x;
    float y;
    float z;
};

// the resource-manager key triple
struct Key {
    uint32_t m_nGroup;
    uint32_t m_nType;
    uint32_t m_nInstance;
};

// the reference-counted base every effect object implements
class cIUnknown {
public:
    virtual void AddRef();                       // +0x00
    virtual void Release();                      // +0x04
};

// ---------------------------------------------------------------------------
// mission types
// ---------------------------------------------------------------------------

// a mission; only the two reached slots are named, the rest keep their offset
class cMission {
public:
    virtual void M000();  virtual void M004();  virtual void M008();
    virtual void* M00c(uint32_t nKey);           // +0x0c
    virtual void M010();  virtual void M014();  virtual void M018();  virtual void M01c();
    virtual void M020();  virtual void M024();  virtual void M028();  virtual void M02c();
    virtual void M030();  virtual void M034();  virtual void M038();  virtual void M03c();
    virtual void M040();  virtual void M044();  virtual void M048();  virtual void M04c();
    virtual void M050();  virtual void M054();  virtual void M058();  virtual void M05c();
    virtual void M060();  virtual void M064();  virtual void M068();  virtual void M06c();
    virtual void M070();  virtual void M074();  virtual void M078();  virtual void M07c();
    virtual void M080();  virtual void M084();  virtual void M088();  virtual void M08c();
    virtual void M090();  virtual void M094();  virtual void M098();  virtual void M09c();
    virtual void M0a0();  virtual void M0a4();  virtual void M0a8();  virtual void M0ac();
    virtual void M0b0();  virtual void M0b4();  virtual void M0b8();  virtual void M0bc();
    virtual void M0c0();  virtual void M0c4();  virtual void M0c8();  virtual void M0cc();
    virtual void M0d0();  virtual void M0d4();  virtual void M0d8();  virtual void M0dc();
    virtual void M0e0();  virtual void M0e4();  virtual void M0e8();  virtual void M0ec();
    virtual void M0f0();  virtual void M0f4();
    virtual bool M0f8();                         // +0xf8

    bool IsActive();                             // 0x00c44c80
    void* GetTargetPlanet();                     // 0x00970b30
};

// the mission fetch object the mission hands out
class cSPMissionFetch {
public:
    bool CheckTargetPlanet(void* pA, void* pB);  // 0x00c5eb50
    bool VerifyTargetPlanet(void* pA, void* pB); // 0x00c54f90
};

// the manager's mission vector ({begin, end})
class cMissionList {
public:
    cMission** m_pBegin;                         // +0x00
    cMission** m_pEnd;                           // +0x04
};

class cSPMissionManager {
public:
    cMissionList* GetMissionList();              // 0x00fedd50
};

class cPlanet {
public:
    uint8_t m_pad[8];
};

// ---------------------------------------------------------------------------
// the saucer's world objects
// ---------------------------------------------------------------------------

// the model object a spatial view owns (only the reached slots are named)
class cSpatialObject {
public:
    virtual void P00();  virtual void P04();  virtual void P08();  virtual void P0c();
    virtual void P10();  virtual void P14();  virtual void P18();  virtual void P1c();
    virtual void P20();  virtual void P24();  virtual void P28();  virtual void P2c();
    virtual void P30();  virtual void P34();  virtual void P38();  virtual void P3c();
    virtual void P40();  virtual void P44();  virtual void P48();  virtual void P4c();
    virtual void P50();  virtual void P54();  virtual void P58();  virtual void P5c();
    virtual void P60();  virtual void P64();  virtual void P68();  virtual void P6c();
    virtual void P70();  virtual void P74();  virtual void P78();  virtual void P7c();
    virtual void P80();  virtual void P84();  virtual void P88();  virtual void P8c();
    virtual void P90();  virtual void P94();  virtual void P98();  virtual void P9c();
    virtual void Pa0();  virtual void Pa4();  virtual void Pa8();  virtual void Pac();
    virtual void Pb0();  virtual void Pb4();
    virtual void* Pb8(uint32_t nId);             // +0xb8

    uint8_t m_pad0bc[0x714 - 0xbc];              // +0x0bc
    int32_t m_nKind714;                          // +0x714
    uint8_t m_pad718[0x74c - 0x718];             // +0x718
    uint8_t m_bFlag74c;                          // +0x74c
    uint8_t m_pad74d[0x76c - 0x74d];             // +0x74d
    int32_t m_nMode76c;                          // +0x76c
};

// the model the view hands out through slot +0x2c: its flags live at +0x04
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

// a visual effect handle
class cIVisualEffect {
public:
    virtual void V00();                          // +0x00
    virtual void V04();                          // +0x04
    virtual void V08(bool bFlag);                // +0x08
    virtual void V0c(bool bFlag);                // +0x0c
    virtual void V10();  virtual void V14();
    virtual void V18(void* pSample);             // +0x18
    virtual void V1c();  virtual void V20();  virtual void V24();  virtual void V28();
    virtual void V2c();  virtual void V30();  virtual void V34();  virtual void V38();
    virtual void V3c();  virtual void V40();
    virtual void V44(int32_t nSlot, const float* pValue, int32_t nCount);  // +0x44
    virtual void V48();  virtual void V4c();  virtual void V50();  virtual void V54();
    virtual void V58();  virtual void V5c();
    virtual int32_t V60();                       // +0x60
};

// the effects manager
class cEffectsManager {
public:
    virtual void V00();  virtual void V04();  virtual void V08();  virtual void V0c();
    virtual void V10();  virtual void V14();  virtual void V18();  virtual void V1c();
    virtual void V20();  virtual void V24();  virtual void V28();
    virtual void CreateV2c(uint32_t nId, int32_t nMode, cIVisualEffect** ppOut);  // +0x2c
};

// the world the saucer lives in
class cGonzagoWorld {
public:
    virtual void V00();  virtual void V04();  virtual void V08();  virtual void V0c();
    virtual void V10();  virtual void V14();  virtual void V18();  virtual void V1c();
    virtual void V20();  virtual void V24();  virtual void V28();  virtual void V2c();
    virtual void V30();  virtual void V34();  virtual void V38();  virtual void V3c();
    virtual void V40();  virtual void V44();  virtual void V48();  virtual void V4c();
    virtual void V50();  virtual void V54();  virtual void V58();  virtual void V5c();
    virtual void V60();  virtual void V64();  virtual void V68();  virtual void V6c();
    virtual void V70();  virtual void V74();  virtual void V78();  virtual void V7c();
    virtual void V80();  virtual void V84();  virtual void V88();  virtual void V8c();
    virtual void V90();  virtual void V94();  virtual void V98();  virtual void V9c();
    virtual void Va0();  virtual void Va4();  virtual void Va8();  virtual void Vac();
    virtual void Vb0();  virtual void Vb4();  virtual void Vb8();  virtual void Vbc();
    virtual void Vc0();
    virtual void SetRenderVc4(void* pRender, bool bFlag, bool bOther, int32_t nMode);  // +0xc4
};

// the object the saucer model derives from, reached through the model's +0x34
class cLocomotiveObject {
public:
    virtual void V00();  virtual void V04();  virtual void V08();  virtual void V0c();
    virtual void V10();  virtual void V14();  virtual void V18();  virtual void V1c();
    virtual void V20();  virtual void V24();  virtual void V28();
    virtual Vector3* GetPositionV2c();           // +0x2c
    virtual void V30();
    virtual float GetScaleV34();                 // +0x34

    Vector3* GetVelocity();                      // 0x00d20610
};

// the audio system
class cAudioSystem {
public:
    virtual void V00();  virtual void V04();  virtual void V08();  virtual void V0c();
    virtual void V10();  virtual void V14();  virtual void V18();  virtual void V1c();
    virtual cIVisualEffect* GetEffectV20();      // +0x20
};

// ---------------------------------------------------------------------------
// the spatial view base and the saucer effect object
// ---------------------------------------------------------------------------

class cSpatialObjectView {
public:
    virtual void S00();  virtual void S04();  virtual void S08();  virtual void S0c();
    virtual void S10();  virtual void S14();  virtual void S18();  virtual void S1c();
    virtual void S20();
    virtual void S24(void* pOwner);              // +0x24
    virtual void S28();                           // +0x28
    virtual cRenderInstance* GetRenderS2c();      // +0x2c

    uint8_t m_pad04[8];                          // +0x04
    cSpatialObject* m_pObject;                   // +0x0c
    uint8_t m_pad10[8];                          // +0x10

    void SetIsVisible(bool bVisible);            // 0x00e889f0
};

// the flying-saucer effect
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

// the saucer's key object (reached through a noun's +0xa4)
class cUFOKeys {
public:
    uint8_t m_pad000[0x504];                     // +0x000
    Key m_key;                                   // +0x504
};

// a noun the saucer collides with
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

// the pair of {begin, end} arrays the searches walk
class cNounVector {
public:
    void** m_pBegin;                             // +0x00
    void** m_pEnd;                               // +0x04
};

// the "nearest noun" helper object
class cNearNoun {
public:
    Vector3* GetPosition();                      // 0x00c6acc0
};

// the terraforming key holder
class cTerraformingInfo {
public:
    Key* FUN_00bbc510();                         // 0x00bbc510
};

// the property gate object
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
    virtual void V00();  virtual void V04();  virtual void V08();  virtual void V0c();
    virtual void V10();  virtual void V14();  virtual void V18();  virtual void V1c();
    virtual void V20();  virtual void V24();  virtual void V28();
    virtual void GetV2c(uint32_t nProp, uint32_t nKey, cIUnknown** ppOut);   // +0x2c
};

// the effect-info record the trail keeps
struct cEffectInfo {
    float m_fX;
    float m_fY;
    float m_fZ;
    cIUnknown* m_pEffect;
};

// the same record with the auto-refcount member the copy-assign uses
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

// a trail sample appended to the effect
struct cTrailSample {
    uint16_t m_nFlags;                           // +0x00
    uint16_t m_nCount;                           // +0x02
    float m_fX;                                  // +0x04
    float m_fY;                                  // +0x08
    float m_fZ;                                  // +0x0c
    float m_fScale;                              // +0x10
    float m_aMatrix[9];                          // +0x14
};

// ---------------------------------------------------------------------------
// imports
// ---------------------------------------------------------------------------

extern Vector3 gDefaultTrailOffset;              // 0x016c6350
extern int32_t gkSpaceEffects[16];               // 0x016c6340
extern int32_t gkPlanetEffects[16];              // 0x016c6380
extern char gGameModeSpace;                      // 0x01654c10

cPlanet* __cdecl SP_GetActivePlanet();           // 0x01021260
cSPMissionManager* __cdecl SP_GetMissionManager(); // 0x00feb9f0
cTerraformingInfo* __stdcall SP_TerraformingManager(Key* pOut);  // 0x00b3d430
int32_t __cdecl SP_GetUniverseContext();         // 0x01021080
cGonzagoWorld* __cdecl SP_GonzagoModelWorld();   // 0x00b3d520
cAudioSystem* __cdecl EA_Audio_GetSystemAT();    // 0x00a206f0
cEffectsManager* __cdecl SP_EffectsManagerPtr(); // 0x0067ddd0
cPropertyManager* __cdecl SP_PropertyManager();  // 0x0067de30
void __cdecl SP_GetPropertyAsKey(cIUnknown* pValue, uint32_t nKey, Key* pOut);
                                                 // 0x006a1250
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
void __cdecl Matrix3_Assign(void* pOut, const void* pIn);          // 0x0041cb40
cPlanet* __cdecl SP_GetCurrentGameMode();        // 0x00b5b800
void* __cdecl operator_new(uint32_t nSize, const char* pType,
                           uint32_t a, uint32_t b, uint32_t c,
                           uint32_t d);          // 0x00f473a0
void __cdecl SP_PlanetModel(void* pOut, const Vector3* pDir);      // 0x00b3d350
void __cdecl SP_Matrix3FromQuaternion(void* pOut, const void* pQuat);
                                                 // 0x0059c190

// the planet model
class cPlanetModel {
public:
    void BuildSurfaceOrientation(void* pQuat, const Vector3* pDir);  // 0x00b7f190
};

// the base-object constructors the saucer ctor chains to
void __cdecl cSpatialObjectView_Construct();     // 0x00e92af0
void __cdecl cGonzagoTimer_Construct();          // 0x00b63890

// ---------------------------------------------------------------------------
// the mission lookups
// ---------------------------------------------------------------------------

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
void* FUN_00e98f60(cNounVector* pNouns, const Vector3* pPos,
                   char (*pFilter)(void*))
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
cEffectInfo* FUN_00e990f0(cEffectInfo* pSrc, cEffectInfo* pEnd,
                          cEffectInfo* pDst)
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
cEffectRecord* FUN_00e99140(cEffectRecord* pSrc, cEffectRecord* pEnd,
                            cEffectRecord* pDst)
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
