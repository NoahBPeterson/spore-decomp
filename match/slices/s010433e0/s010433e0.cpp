// Slice s010433e0 -- space-stage reticle / zoo-marker and path-sampling helpers (retail).
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// The retail build computes every "scalar" helper (path interpolation, 2D distances, ray sampling,
// basis normalisation) in x87 extended precision, so those functions return `long double` and the
// float operands are widened explicitly.  Everything else is SSE single precision.
#include "types.h"
#include <math.h>
#include <string.h>

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// 3x3 row-major basis.  The copy constructor is out of line in retail (0x0041cb40, ret 4).
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& src);                       // 0x0041cb40
};
Matrix3& Matrix3FromQuaternion(Matrix3& result, const Quat& q);   // 0x0059c190

// ---- shared .rdata constants (values verified against the image) -------------------------------
extern const float   kEps;              // 0x013ec4b8  1e-8f
extern const float   kHalf;             // 0x01471064  0.5f
extern const float   kOne;              // 0x01485720  1.0f
extern const Matrix3 kIdentityMatrix;   // 0x016e00a4  identity basis
extern const Vec3    kZeroPosition;     // 0x016e00c8  (0,0,0)

// ===========================================================================
// 0x010433e0 -- path parameter lookup (returns the normalised position along a sampled path)
// ===========================================================================
struct PathSample { float mV[4]; };

struct PathData {
    float*   mpData;     // +0x00  PathSample[] (16-byte stride)
    uint32_t mu04;       // +0x04
    int      mnCount;    // +0x08
    uint32_t mu0c;       // +0x0c
    uint16_t mFlags;     // +0x10  bit 0x30 = "has a sampled path"
    uint16_t mbValid;    // +0x12
    uint32_t mu14;       // +0x14
};

class cPathSource {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual PathData* GetPathData(float fT);          // +0x28
};

// @ 0x010433e0
long double FUN_010433e0(cPathSource* pSource, float fT, int iColumn)
{
    if (!pSource)
        return 0.0;
    PathData* pPath = pSource->GetPathData(fT);
    // Retail materialises the element pointer before the flag test (the second arm is dead code:
    // it only yields a non-null pointer when the flag bits are absent).
    float* pData = (pPath->mFlags & 0x30) ? pPath->mpData : (pPath->mbValid ? (float*)pPath : 0);
    if ((pPath->mFlags & 0x30) == 0)
        return 0.0;
    int n = pPath->mnCount;
    if (n <= 1)
        return 0.0;
    int i1 = 0;
    int i2 = 0;
    for (int i = 0; i < n - 1; ++i) {
        float a = pData[i * 4 + iColumn];
        float b = pData[(i + 1) * 4 + iColumn];
        if (fT > a) {
            if (b < fT)
                continue;
            i1 = i;
            i2 = i + 1;
        } else {
            if (a < fT)
                continue;
            if (fT <= b)
                continue;
            i1 = i + 1;
            i2 = i;
        }
        if (i1 != i2) {
            const float* pA = &pData[i1 * 4 + iColumn];
            const float* pB = &pData[i2 * 4 + iColumn];
            return ((long double)i1 - ((long double)fT - (long double)*pA) /
                                       ((long double)*pB - (long double)*pA)) /
                   ((long double)n - 1.0f);
        }
    }
    return 1.0;
}

// ===========================================================================
// 0x010434c0 / 0x010434e0 -- squared / plain 2D distance
// ===========================================================================
// @ 0x010434c0
long double FUN_010434c0(float* pA, float* pB)
{
    long double fDx = (long double)pA[0] - (long double)pB[0];
    long double fDy = (long double)pA[1] - (long double)pB[1];
    return fDy * fDy + fDx * fDx;
}

// @ 0x010434e0
long double FUN_010434e0(float* pA, float* pB)
{
    long double fDx = (long double)pA[0] - (long double)pB[0];
    long double fDy = (long double)pA[1] - (long double)pB[1];
    return sqrt(fDy * fDy + fDx * fDx);
}

// ===========================================================================
// Effects vocabulary (only the virtual slots this slice touches are named)
// ===========================================================================
class IEffect;
class cEffectsManager;

struct EffectTransform {
    uint16_t mFlags;        // +0x00  |4 = position, |2 = orientation
    int16_t  mCount;        // +0x02  number of valid blocks
    Vec3     mPosition;     // +0x04
    float    mScale;        // +0x10
    Matrix3  mOrientation;  // +0x14
    EffectTransform() : mFlags(0), mCount(0), mPosition(kZeroPosition), mScale(kOne),
                        mOrientation(kIdentityMatrix) {}
};

class IEffect {
public:
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void Start(int iFlag);                      // +0x08
    virtual void Stop(int iFlag);                       // +0x0c
    virtual bool IsPlaying();                           // +0x10
    PV(5)
    virtual void SetTransform(const EffectTransform* pMsg);   // +0x18
    PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23)
    virtual uint64_t GetKey();                          // +0x60
};

template <typename T>
struct AutoRefCount {
    T* mpObject;                                        // +0x00
    T** AsPPTypeParam();                                // 0x00a16f40 (out of line)
    void Clear()
    {
        T* pOld = mpObject;
        mpObject = 0;
        if (pOld)
            pOld->Release();
    }
};

class cEffectsManager {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool CreateEffect(uint32_t uEffectId, int iParam, IEffect** ppEffect);   // +0x2c
};

cEffectsManager* EffectsManager();                      // 0x0067ddd0

// @ 0x01043500
bool FUN_01043500(uint32_t uEffectId, int iParam)
{
    IEffect* pEffect = 0;
    cEffectsManager* pManager = EffectsManager();
    if (pEffect) {
        IEffect* pOld = pEffect;
        pEffect = 0;
        pOld->Release();
    }
    if (pManager->CreateEffect(uEffectId, iParam, &pEffect)) {
        pEffect->Start(0);
        return true;
    }
    if (pEffect)
        pEffect->Release();
    return false;
}

// ===========================================================================
// Target objects (ship / reticle target)
// ===========================================================================
class cTargetObject {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool IsTargetable();                        // +0x24
    PV(10)
    virtual const Vec3* GetPosition();                  // +0x2c
    virtual const Quat* GetOrientation();               // +0x30
    virtual float GetScale();                           // +0x34
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual bool IsSelected();                          // +0x50
    PV(21)
    virtual bool IsHostile();                           // +0x58
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
    virtual uint32_t GetProperty(uint32_t uPropertyId);  // +0xb8
};

// ===========================================================================
// 0x01043580 -- orthonormal basis from two points plus an up axis, written as a 4x4 matrix
// ===========================================================================
// @ 0x01043580
void FUN_01043580(float* pFrom, float* pTo, float* pAxis, float* pOut)
{
    float fDx = pTo[0] - pFrom[0];
    float fDy = pTo[1] - pFrom[1];
    float fDz = pTo[2] - pFrom[2];
    float fInvLen = (float)(1.0 / sqrt((long double)fDz * fDz + (long double)fDx * fDx +
                                       (long double)fDy * fDy + kEps));
    float fNz = fDz * fInvLen;
    float fNx = fInvLen * fDx;
    float fNy = fInvLen * fDy;
    float f7 = pAxis[2] * fNy - pAxis[1] * fNz;
    float f8 = pAxis[1] * fNx - pAxis[0] * fNy;
    float f6 = pAxis[0] * fNz - pAxis[2] * fNx;
    float fInvSide = (float)(1.0 / sqrt((long double)f8 * f8 + (long double)f6 * f6 +
                                        (long double)f7 * f7 + kEps));
    float f8n = f8 * fInvSide;
    float f6n = f6 * fInvSide;
    float f7n = fInvSide * f7;
    pOut[0] = f7n;
    pOut[1] = f6n;
    pOut[2] = f8n;
    pOut[3] = 0.0f;
    pOut[4] = fNx;
    pOut[5] = fNy;
    pOut[6] = fNz;
    pOut[7] = 0.0f;
    pOut[8] = f6n * fNz - f8n * fNy;
    pOut[9] = f8n * fNx - f7n * fNz;
    pOut[10] = f7n * fNy - f6n * fNx;
    pOut[11] = 0.0f;
    pOut[12] = pFrom[0];
    pOut[13] = pFrom[1];
    pOut[14] = pFrom[2];
    pOut[15] = 1.0f;
}

// ===========================================================================
// 0x01043770 -- push the target's transform into the effect message receiver
// ===========================================================================
// @ 0x01043770
void FUN_01043770(cTargetObject* pTarget, AutoRefCount<IEffect>* pEffect)
{
    float fScale = pTarget->GetScale();
    EffectTransform msg;
    msg.mPosition = *pTarget->GetPosition();
    msg.mFlags |= 4;
    msg.mCount += 1;
    Matrix3 orientation;
    msg.mOrientation = Matrix3FromQuaternion(orientation, *pTarget->GetOrientation());
    msg.mFlags |= 2;
    msg.mCount++;
    msg.mCount++;
    msg.mScale = fScale;
    pEffect->mpObject->SetTransform(&msg);
}

// ===========================================================================
// Space-stage support services used by the two reticle helpers
// ===========================================================================
class cSpatialObject {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                  // +0x2c
};

class cPlayerInventory {
public:
    uint32_t pad00[0x34 / 4];                           // +0x00
    cSpatialObject mPlayerShip;                         // +0x34
};

class cSPSimulatorSpaceGame {
public:
    cPlayerInventory* GetPlayerInventory();             // 0x00a1ad60
};

cSPSimulatorSpaceGame* GetUFOSimulator();               // 0x00ffbe50
cSPSimulatorSpaceGame* SpaceGameGet();                  // 0x01002bd0

class cSpaceCombatTuning {
public:
    float GetReticleRange();                            // 0x0102a450
};
cSpaceCombatTuning* GetSpaceCombatTuning();             // 0x01029940

class cUniverseState {
public:
    bool IsInCutscene();                                // 0x00a98020
};
cUniverseState* FUN_01015df0();                         // 0x01015df0
void* GetUniverseContext();                             // 0x01021080
void* FUN_00ff3f00(cPlayerInventory* pInventory);       // 0x00ff3f00
bool  FUN_0102af80(void* pContext, uint32_t uId);       // 0x0102af80
uint32_t SPIDFromName(const char* pName);               // 0x00571cf0

// Target-specific player filter helpers.
class cSpaceTarget {
public:
    uint32_t pad000[0x714 / 4];                         // +0x000
    int32_t  mnState;                                   // +0x714
};
cSpaceTarget* FUN_00ad2730(cTargetObject* pTarget);     // 0x00ad2730
uint32_t FUN_00ae66d0(cTargetObject* pTarget);          // 0x00ae66d0

// ===========================================================================
// 0x01043860 -- "target in air" reticle
// ===========================================================================
// @ 0x01043860
void FUN_01043860(cTargetObject* pTarget, AutoRefCount<IEffect>* pEffect, bool bForce)
{
    if (!pTarget)
        return;
    bool bShow = false;
    uint32_t uReticle = 0;
    if (!bForce && pTarget->IsSelected()) {
        bool bHostile = pTarget->IsHostile();
        cPlayerInventory* pInventory = GetUFOSimulator()->GetPlayerInventory();
        const Vec3* pPlayerPos = pInventory->mPlayerShip.GetPosition();
        const Vec3* pTargetPos = pTarget->GetPosition();
        float fDx = pTargetPos->x - pPlayerPos->x;
        float fDy = pTargetPos->y - pPlayerPos->y;
        float fDz = pTargetPos->z - pPlayerPos->z;
        float fDist = (float)sqrt((long double)fDz * fDz + (long double)fDy * fDy +
                                  (long double)fDx * fDx);
        float fRange = GetSpaceCombatTuning()->GetReticleRange();
        bool bInRange = fRange > fDist;
        void* pShip = FUN_00ff3f00(SpaceGameGet()->GetPlayerInventory());
        uint32_t uWeapon = pTarget->GetProperty(0x017f243b);
        bool bArmed = FUN_0102af80(pShip, uWeapon);
        if (!bHostile && bInRange && !FUN_01015df0()->IsInCutscene() &&
            (bArmed || !GetUniverseContext())) {
            uint32_t uTarget = SPIDFromName("UI_common_reticle_targetInAir_SPGPlanet");
            uint32_t uAttack = SPIDFromName("UI_common_reticle_attackInAir_SPGPlanet");
            uReticle = bArmed ? uAttack : uTarget;
            bShow = true;
        }
    }
    if (bShow) {
        if (pEffect->mpObject) {
            if (pEffect->mpObject->GetKey() != uReticle) {
                pEffect->mpObject->Stop(0);
                pEffect->Clear();
            }
        }
        if (!pEffect->mpObject) {
            if (EffectsManager()->CreateEffect(uReticle, 0, &pEffect->mpObject))
                pEffect->mpObject->Start(0);
        }
    } else {
        if (pEffect->mpObject && pEffect->mpObject->IsPlaying()) {
            pEffect->mpObject->Stop(0);
            pEffect->Clear();
        }
    }
    if (pEffect->mpObject)
        FUN_01043770(pTarget, pEffect);
}

// ===========================================================================
// 0x01043a50 -- "pre-target in air" reticle
// ===========================================================================
// @ 0x01043a50
void FUN_01043a50(cTargetObject* pTarget, AutoRefCount<IEffect>* pEffect, bool bForce)
{
    if (!pTarget)
        return;
    bool bShow = false;
    uint32_t uReticle = 0;
    if (!bForce && pTarget->IsTargetable() && !pTarget->IsSelected() && !GetUniverseContext()) {
        cSpaceTarget* pSpace = FUN_00ad2730(pTarget);
        bool bHostile = pTarget->IsHostile();
        bool bArmed = bHostile || (pSpace && pSpace->mnState == 3);
        cPlayerInventory* pInventory = GetUFOSimulator()->GetPlayerInventory();
        const Vec3* pPlayerPos = pInventory->mPlayerShip.GetPosition();
        const Vec3* pTargetPos = pTarget->GetPosition();
        float fDx = pTargetPos->x - pPlayerPos->x;
        float fDy = pTargetPos->y - pPlayerPos->y;
        float fDz = pTargetPos->z - pPlayerPos->z;
        float fDist = (float)sqrt((long double)fDz * fDz + (long double)fDy * fDy +
                                  (long double)fDx * fDx);
        float fRange = GetSpaceCombatTuning()->GetReticleRange();
        bool bInRange = fRange > fDist;
        void* pShip = FUN_00ff3f00(SpaceGameGet()->GetPlayerInventory());
        bool bArmedTarget = FUN_0102af80(pShip, FUN_00ae66d0(pTarget));
        if (!bArmed && bInRange && !FUN_01015df0()->IsInCutscene()) {
            uint32_t uTarget = SPIDFromName("UI_common_reticle_preTargetInAir_SPGPlanet");
            uint32_t uAttack = SPIDFromName("UI_common_reticle_preAttackInAir_SPGPlanet");
            uReticle = bArmedTarget ? uAttack : uTarget;
            bShow = true;
        }
    }
    if (bShow) {
        if (pEffect->mpObject) {
            if (pEffect->mpObject->GetKey() != uReticle) {
                pEffect->mpObject->Stop(0);
                pEffect->Clear();
            }
        }
        if (!pEffect->mpObject) {
            if (EffectsManager()->CreateEffect(uReticle, 0, &pEffect->mpObject))
                pEffect->mpObject->Start(0);
        }
    } else {
        if (pEffect->mpObject && pEffect->mpObject->IsPlaying()) {
            pEffect->mpObject->Stop(0);
            pEffect->Clear();
        }
    }
    if (pEffect->mpObject)
        FUN_01043770(pTarget, pEffect);
}

// ===========================================================================
// Zoo markers (minimap pins)
// ===========================================================================
struct ResourceKey {
    uint32_t mType;         // +0x00
    uint32_t mInstance;     // +0x04
    uint32_t mGroup;        // +0x08
};

struct ZooMarker {
    uint32_t    mu00;       // +0x00
    Vec3        mPosition;  // +0x04
    uint16_t    mu10;       // +0x10
    uint8_t     mu12;       // +0x12
    uint8_t     mu13;       // +0x13
    float       mu14;       // +0x14
    uint32_t    mu18;       // +0x18
    ResourceKey mKey;       // +0x1c  creature key the marker follows
    uint8_t     mFlags;     // +0x28  bit 0x40 = live marker
    uint8_t     mu29[3];    // +0x29
};

struct ResourceKeyVector {
    ResourceKey* mpBegin;                               // +0x00
    ResourceKey* mpEnd;                                 // +0x04
    ResourceKey* mpCap;                                 // +0x08
    ResourceKey* DoInsertValue(ResourceKey* pEnd, const ResourceKey* pKey);   // 0x004e3e10
    ResourceKey* push_back(const ResourceKey& key)
    {
        if (mpEnd < mpCap) {
            ResourceKey* pSlot = mpEnd++;
            if (pSlot)
                *pSlot = key;
            return pSlot;
        }
        return DoInsertValue(mpEnd, &key);
    }
};

struct ZooMarkerVector {
    ZooMarker* mpBegin;                                 // +0x00
    ZooMarker* mpEnd;                                   // +0x04
    ZooMarker* mpCap;                                   // +0x08
    ZooMarker* DoInsertValue(ZooMarker* pEnd, const ZooMarker* pMarker);   // 0x00acb810
    void       RemoveMarker(ZooMarker* pMarker);        // 0x00b8e540
    ZooMarker* push_back(const ZooMarker& marker)
    {
        if (mpEnd < mpCap) {
            ZooMarker* pSlot = mpEnd++;
            if (pSlot)
                *pSlot = marker;
            return pSlot;
        }
        return DoInsertValue(mpEnd, &marker);
    }
};

class cZooMarkerMgr {
public:
    uint32_t pad000[0xd0 / 4];                          // +0x000
    ResourceKeyVector mKeys;                            // +0x0d0
    uint32_t pad0dc[22];                                // +0x0dc
    ZooMarkerVector mMarkers;                           // +0x134
};

ResourceKey* FindKey(ResourceKey* pBegin, ResourceKey* pEnd, const ResourceKey* pKey);  // 0x00ac0d80
void FUN_00b8e540(ZooMarker* pMarker);                  // 0x00b8e540

class cIconTarget {
public:
    PV(0) PV(1) PV(2)
    virtual void* FindNoun(uint32_t uNounId);           // +0x0c
};

struct MinimapEntry {
    uint32_t pad00[5];                                  // +0x00
    cIconTarget* mpIcon;                                // +0x14
};

class cSPUIMinimapWin {
public:
    MinimapEntry* FindEntry(uint32_t uId);              // 0x00e0df30
    bool              HasIcon(uint32_t uId, const Vec3* pPos, int iFlags);   // 0x00e0df70
    void              RemoveIcon(uint32_t uId, int iFlags, int iUnused);      // 0x00e0f9c0
    void              AddIcon(uint32_t uId, const void* pIcon, int iFlags, int iUnused);  // 0x00e10580
};

class cMinimapHost {
public:
    cSPUIMinimapWin* GetWindow();                       // 0x01067e60
};
cMinimapHost* FUN_010666a0();                           // 0x010666a0

class cGameNounManager;
cGameNounManager* NounManager();                        // 0x00b3d300

class cGameNounManager {
public:
    void RemoveNoun(void* pNoun);                       // 0x00b225d0
};

// @ 0x01043c60
void FUN_01043c60(cZooMarkerMgr* pMgr, const ResourceKey* pKey)
{
    ZooMarkerVector* pMarkers = &pMgr->mMarkers;
    for (ZooMarker* pMarker = pMarkers->mpBegin; pMarker != pMarkers->mpEnd; ++pMarker) {
        if ((pMarker->mFlags & 0x40) != 0) {
            if (pMarker->mKey.mType == pKey->mType && pMarker->mKey.mInstance == pKey->mInstance &&
                pMarker->mKey.mGroup == pKey->mGroup) {
                pMarkers->RemoveMarker(pMarker);
                break;
            }
        }
    }
    cSPUIMinimapWin* pWin = FUN_010666a0()->GetWindow();
    uint32_t uId = pKey->mType;
    MinimapEntry* pEntry = pWin->FindEntry(uId);
    if (pEntry) {
        cIconTarget* pIcon = pEntry->mpIcon;
        if (pIcon) {
            void* pNoun = pIcon->FindNoun(0x01b92b27);
            if (pNoun)
                NounManager()->RemoveNoun(pNoun);
        }
    }
    pWin->RemoveIcon(uId, 1, 0);
}

// ===========================================================================
// 0x01043d10 -- sample a straight segment into a float buffer (xyz triples)
// ===========================================================================
struct FloatVector {
    float* mpBegin;                                     // +0x00
    float* mpEnd;                                       // +0x04
    float* mpCap;                                       // +0x08
    void   reserve(uint32_t n);                         // 0x004e0880
    void*  DoPushBack(float* pEnd, const float* pValue); // 0x00455660
    void   clear()
    {
        memcpy(mpBegin, mpEnd, 0);
        mpEnd -= (mpEnd - mpBegin);
    }
    void push_back(float fValue)
    {
        if (mpEnd < mpCap) {
            float* pSlot = mpEnd++;
            if (pSlot)
                *pSlot = fValue;
        } else {
            DoPushBack(mpEnd, &fValue);
        }
    }
};

// @ 0x01043d10
void FUN_01043d10(float* pFrom, float* pTo, float fStep, FloatVector* pOut)
{
    float fDx = pTo[0] - pFrom[0];
    float fDy = pTo[1] - pFrom[1];
    float fDz = pTo[2] - pFrom[2];
    long double fLen = sqrt((long double)fDz * fDz + (long double)fDy * fDy + (long double)fDx * fDx);
    float fScale = fStep / (float)fLen;
    float fDirX = fDx * fScale;
    float fDirY = fDy * fScale;
    float fDirZ = fDz * fScale;
    int iSegments = (int)floorf((float)(fLen / fStep * kHalf));
    pOut->clear();
    int n = iSegments * 2 + 2;
    pOut->reserve(n * 3);
    for (int i = 0; i < n; ++i) {
        float fPx;
        float fPy;
        float fPz;
        if (i <= iSegments) {
            float fK = (float)i;
            fPx = pFrom[0] + fDirX * fK;
            fPy = fDirY * fK + pFrom[1];
            fPz = pFrom[2] + fDirZ * fK;
        } else {
            float fK = (float)(n - 1 - i);
            fPx = pTo[0] - fDirX * fK;
            fPy = pTo[1] - fDirY * fK;
            fPz = pTo[2] - fDirZ * fK;
        }
        pOut->push_back(fPx);
        pOut->push_back(fPy);
        pOut->push_back(fPz);
    }
}

// ===========================================================================
// 0x01043fd0 -- SP::SetZooMarker
// ===========================================================================
class cRefObject {
public:
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
};

class cSpeciesProfile;
class cCreature {
public:
    uint32_t pad000[0xa4 / 4];                          // +0x000
    uint32_t mSpeciesId;                                // +0x0a4
    uint32_t pad0a8[(0xf4 - 0xa8) / 4];                 // +0x0a8
    int32_t  mnState;                                   // +0x0f4
    uint32_t pad0f8[(0x160 - 0xf8) / 4];                // +0x0f8
    cRefObject* mpNest;                                 // +0x160
    uint32_t pad164[(0x192 - 0x164) / 4];               // +0x164
    uint8_t  mbMarked;                                  // +0x192
    uint8_t  pad193[3];                                 // +0x193
    uint32_t pad194[(0xb20 - 0x194) / 4];               // +0x194
    uint32_t mCreatureTypeId;                           // +0xb20

    cCreature* GetCurrent();                            // 0x00c04590
};

class cSpaceNoun {
public:
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void* Query(uint32_t uId);                  // +0x0c
};

class cSpeciesManager {
public:
    cSpeciesProfile* GetProfile(const ResourceKey& key);       // 0x004df550
};
cSpeciesManager* GetSetting9(const ResourceKey& key);          // 0x00401090

void*       FUN_00b3d480(cSpeciesProfile* pProfile, const Vec3* pPos);   // 0x00b3d480
cCreature*  FUN_00ad0510(void* pObject, cSpeciesProfile* pProfile);      // 0x00ad0510
void        FUN_00c6aab0(cRefObject* pNest, const Vec3* pPos);           // 0x00c6aab0 (MoveNest)
cRefObject* FUN_00b20e40(cGameNounManager* pManager, const Vec3* pPos);  // 0x00b20e40
uint32_t*   FUN_00b21340(cGameNounManager* pManager, void* a1, void* a2, void* a3, void* a4,
                         uint32_t uId);                     // 0x00b21340 GetGameDataVector

struct NounArray {
    uint32_t mu00;                                      // +0x00
    cCreature** mpBegin;                                // +0x04
    cCreature** mpEnd;                                  // +0x08
};

struct MinimapIcon {
    uint32_t mu00;                                      // +0x00
    Vec3     mPosition;                                 // +0x04
    uint32_t mu10;                                      // +0x10
    uint32_t mColor;                                    // +0x14
    AutoRefCount<cRefObject> mpEffect;                  // +0x18
    float    mf1c;                                      // +0x1c
    uint32_t mu20;                                      // +0x20
};

namespace SP {

// @ 0x01043fd0
void SetZooMarker(cZooMarkerMgr* pMgr, const ResourceKey* pKey, const Vec3* pPos, cSpaceNoun* pNoun)
{
    ResourceKey* pEnd = pMgr->mKeys.mpEnd;
    if (FindKey(pMgr->mKeys.mpBegin, pEnd, pKey) == pEnd)
        pMgr->mKeys.push_back(*pKey);

    cSpeciesProfile* pProfile = GetSetting9(*pKey)->GetProfile(*pKey);
    cCreature* pCreature;
    cCreature* pQueried = pNoun ? (cCreature*)pNoun->Query(0xd0036e08) : 0;
    if (pQueried) {
        pCreature = pQueried;
    } else {
        pCreature = FUN_00ad0510(FUN_00b3d480(pProfile, pPos), pProfile);
    }
    cCreature* pCurrent = pCreature->GetCurrent();
    pCurrent->mbMarked = 0;
    pCurrent->mnState = 3;
    NounArray* pArray = (NounArray*)FUN_00b21340(NounManager(), (void*)0x00cd7d10, (void*)0x00d3d420,
                                                 (void*)0x00accc30, (void*)0x00b1e500, 0x01be418e);
    for (cCreature** ppCreature = pArray->mpBegin; ppCreature != pArray->mpEnd; ++ppCreature) {
        cCreature* pFound = *ppCreature;
        if (pFound->mSpeciesId != pCreature->mCreatureTypeId)
            continue;
        if (pFound->mbMarked != 0)
            continue;
        if (pFound == pCreature->GetCurrent())
            continue;
        cRefObject* pNest = pFound->mpNest;
        pFound->mbMarked = 1;
        if (!pNest)
            break;
        if (pNest != pCurrent->mpNest) {
            pNest->AddRef();
            pCurrent->mpNest = pNest;
            if (pNest != 0)
                pNest->Release();
        }
        cRefObject* pOwn = pFound->mpNest;
        if (pOwn) {
            pFound->mpNest = 0;
            pOwn->Release();
        }
        FUN_00c6aab0(pCurrent->mpNest, pPos);
        break;
    }
    if (!pCurrent->mpNest)
        pCurrent->mpNest = FUN_00b20e40(NounManager(), pPos);

    bool bPlaced = false;
    for (ZooMarker* pMarker = pMgr->mMarkers.mpBegin; pMarker != pMgr->mMarkers.mpEnd; ++pMarker) {
        if ((pMarker->mFlags & 0x40) && pMarker->mKey.mType == pKey->mType &&
            pMarker->mKey.mInstance == pKey->mInstance && pMarker->mKey.mGroup == pKey->mGroup) {
            pMarker->mPosition = *pPos;
            bPlaced = true;
            break;
        }
    }
    if (!bPlaced) {
        ZooMarker marker;
        marker.mKey = *pKey;
        marker.mPosition = *pPos;
        marker.mu18 = 0;
        marker.mFlags = 0x60;
        pMgr->mMarkers.push_back(marker);
    }

    cSPUIMinimapWin* pWin = FUN_010666a0()->GetWindow();
    uint32_t uId = pKey->mType;
    if (!pWin->HasIcon(uId, pPos, 0)) {
        MinimapIcon icon;
        icon.mPosition = *pPos;
        icon.mu00 = 0;
        icon.mu10 = 0x20;
        icon.mf1c = 0.0f;
        icon.mu20 = 0;
        icon.mpEffect.mpObject = pCurrent->mpNest;
        if (icon.mpEffect.mpObject)
            icon.mpEffect.mpObject->AddRef();
        icon.mColor = 0xff64c864;
        pWin->AddIcon(uId, &icon, 0, 0);
        if (icon.mpEffect.mpObject)
            icon.mpEffect.mpObject->Release();
    }
}

}   // namespace SP
