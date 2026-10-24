// Slice s00c17de0: SP::cSPCreatureBase look-at update helpers.
//
//  - 00c17de0  cSPCreatureBase::LookAtUpdate(float)
//  - 00c18370  cSPCreatureBase::UpdateNetDirection()
//  - 00c18740  cSPCreatureBase::UpdateWaveMotion(float, uint32_t)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// math value types
// ---------------------------------------------------------------------------
class cVector3 {
public:
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
    cVector3() {}
    cVector3(float fValue) : x(fValue), y(fValue), z(fValue) {}
};

class cVector4 {
public:
    float x;
    float y;
    float z;
    float w;
};

class cQuaternion {
public:
    float x;
    float y;
    float z;
    float w;
};

bool Vector3Equal(const cVector3* a, const cVector3* b);      // 0x004232c0
bool Vector3_NotEqual(const cVector3* a, const cVector3* b);  // 0x0041dd30
float* normalized_safe(float* out, const float* v);           // 0x00449c20

namespace checkerlib
{
    float* QuaternionVectorTransform(float* out, const float* quat, const float* v);  // 0x0099c1a0
}

namespace SP
{
    cVector3 const kNoDirection;        // 0x0168d910
}

extern float const kLookAtScale;        // 0x01473c70  (10.0f)
extern float const kZero;               // 0x01485378
extern float const kEpsilon;            // 0x013ec4b8  (1e-8f)
extern float const kTwoPow32;           // 0x013f4fd0
extern float const kMilli;              // 0x013f9428  (0.001f)
extern float const kNetScaleA;          // 0x01571728
extern float const kNetScaleB;          // 0x0157172c
extern bool const gUseGroundMotion;     // 0x0169e381
extern float const gGravityScale;       // 0x0169e384
extern cVector3 const gGravityDirection;  // 0x0169e388
extern cVector3 gStoredDirection;       // 0x0169e3b4

// ---------------------------------------------------------------------------
// animation data
// ---------------------------------------------------------------------------
class cAnimNode;      // per-bone pose entry (stride 0x2bc)
class cPose;

class cBonePose
{
public:
    uint32_t pad00[(0x10) / 4];
    cVector3 mLocalPosition;          // +0x10
    uint32_t pad1c[(0x2bc - 0x1c) / 4];
};

class cPose
{
public:
    uint32_t pad00[(0x18) / 4];
    cVector3 mPosition;               // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    cQuaternion mRotation;            // +0x3c
    uint32_t pad4c[(0x17c - 0x4c) / 4];
    cPose* mpParent;                  // +0x17c
    uint32_t pad180[(0x2e4 - 0x180) / 4];
    cBonePose* mpBones;               // +0x2e4
};

class cAnimTarget
{
public:
    virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
    virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
    virtual void t08(); virtual void t09(); virtual void t10(); virtual void t11();
    virtual void t12(); virtual void t13(); virtual void t14(); virtual void t15();
    virtual void t16(); virtual void t17(); virtual void t18(); virtual void t19();
    virtual void t20(); virtual void t21();
    virtual void GetCurrentAnimation(uint32_t* out, int a, int b, int c);   // +0x58
    virtual void t23();

    uint32_t pad04[(0x154 - 0x04) / 4];
    int      mState;                  // +0x154
    int      mSubState;               // +0x158
    cPose*   mpPose;                  // +0x15c
    int      mBoneIndex;              // +0x160
    cVector3 mLookAtPoint;            // +0x164

    bool      IsOrientIdleAnim(uint32_t nGUID);                  // 0x00a027a0
    int       GetBodyPartIndex(int nPart, int nSide);            // 0x00c17580
    cVector3* GetBodyPartPosition(cVector3* out, int a, int b, int c);  // 0x00c17a30
};

// animation stream data stored inside the locomotive sub-object
class cAnimData
{
public:
    uint32_t pad00[(0x14) / 4];
    cVector3 mOffset;                 // +0x14
    uint32_t pad20[(0x5c - 0x20) / 4];
    cAnimTarget* mpTarget;            // +0x5c
};

// animation player reached through creature+0xb4c (virtual base prefix 8 bytes)
class cPlayPrefix
{
public:
    uint32_t mHandle;                 // +0x00
    uint32_t mFlags;                  // +0x04
};

class cAnimationPlayer
{
public:
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    uint32_t pad14[(0x1c0 - 0x14) / 4];
    cAnimData* mpCurrent;             // +0x1c0
    cAnimData* mpPending;             // +0x1c4

    cAnimData* Play(int nFlags, int nMode);                       // 0x00bc96a0
};

class cAnimPlayer : public cPlayPrefix, public cAnimationPlayer
{
};

// ---------------------------------------------------------------------------
// locomotion sub-object embedded at creature+0xc0
// ---------------------------------------------------------------------------
class cLocomotiveObject
{
public:
    virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03();
    virtual void l04(); virtual void l05(); virtual void l06(); virtual void l07();
    virtual void l08(); virtual void l09(); virtual void l10();
    virtual cVector3* GetPosition();                              // +0x2c
    virtual void l12(); virtual void l13(); virtual void l14(); virtual void l15();
    virtual void l16();
    virtual bool IsOrientationLocked();                           // +0x48
    virtual void l19(); virtual void l20(); virtual void l21();
    virtual bool IsFacingValid();                                 // +0x58
    virtual cVector3* GetForward();                               // +0x5c

    uint32_t pad60[(0x1f4 - 0x60) / 4];
    cAnimData* GetAnimData();                                     // 0x00c41ec0
    uint32_t pad1f8[(0x548 - 0x1f8) / 4];

    cVector3* GetVelocity();                                      // 0x00d20610
    void OffsetPosition(cVector3& vDelta, int nMode);             // 0x00c446d0
};

class cSpecies
{
public:
    uint32_t pad000[(0x548) / 4];
    float    mLookAtRadius;           // +0x548
    uint32_t pad54c[(0x698 - 0x54c) / 4];
    int      mWaveCount;              // +0x698
};

// ---------------------------------------------------------------------------
// SP::cSPCreatureBase
// ---------------------------------------------------------------------------
class cSPCreatureBase
{
public:
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
    virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
    virtual void c28();
    virtual void SetAnimData(cAnimData* pData);                   // +0x74
    virtual void c30(); virtual void c31(); virtual void c32(); virtual void c33();
    virtual void c34(); virtual void c35(); virtual void c36(); virtual void c37();
    virtual void c38(); virtual void c39(); virtual void c40(); virtual void c41();
    virtual void c42(); virtual void c43(); virtual void c44();
    virtual void* GetPartData(int nIndex);                        // +0xb4

    uint8_t  pad04[(0xc0 - 0x04) / 4 * 4];
    cLocomotiveObject mLocomotion;    // +0xc0
    uint8_t  padc4[(0x137 - 0xc4)];
    bool     mbSteering;              // +0x137
    uint8_t  pad138[(0x2b0 - 0x138)];
    int      mSteerState;             // +0x2b0
    uint8_t  pad2b4[(0xb20 - 0x2b4)];
    cSpecies* mpSpecies;              // +0xb20
    uint8_t  padb24[(0xb4c - 0xb24)];
    cAnimPlayer* mpAnimPlayer;        // +0xb4c
    cAnimTarget* mpAnimTarget;        // +0xb54
    uint32_t mFlags;                  // +0xb58
    uint8_t  padb5c[(0xb5e - 0xb5c)];
    bool     mbHasPartFlag;           // +0xb5e
    uint8_t  padb5f[(0xb66 - 0xb5f)];
    bool     mbLookAtEnabled;         // +0xb66
    uint8_t  padb67[(0xe58 - 0xb67)];
    float    mWaveHeight;             // +0xe58
    uint8_t  pade5c[(0xe62 - 0xe5c)];
    bool     mbWaveFinished;          // +0xe62
    uint8_t  pade63[(0xe7c - 0xe63)];
    class cGameNounManager* mpNounManager;   // +0xe7c
    uint8_t  pade80[(0xeac - 0xe80)];
    int      mLookAtState;            // +0xeac

    void      LookAtUpdate(float fBlend);                         // 0x00c17de0
    void      UpdateNetDirection();                               // 0x00c18370
    void      UpdateWaveMotion(float fBlend, uint32_t nAmount);    // 0x00c18740
    void      SetLookAt(cSPCreatureBase* pTarget, int nPart);      // 0x00c0d200
    void      ClearLookAt();                                      // 0x00c0d240
    void      LookAtTo(float fBlend, cVector3& vPoint, int nMode); // 0x00c133d0
    uint32_t  GetCurrentAnimationGUID();                          // 0x00c0e040
    int       FindIndex(int nID);                                 // 0x00c0c080
    void      ApplyWave(float fAmount);                           // 0x00c15dc0
    void      InterruptAnimation(uint32_t nID, int nA, int nB);    // 0x00c12310
};

class cPlanetModel
{
public:
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13();
    virtual cVector3* GetSurfaceOffset(cVector3* out, int nMode, cVector3 vDir);  // +0x38

    cVector3* DirectionToSurfacePosition(cVector3* out, const cVector3* dir);  // 0x00b815a0
    float GetLookAtRange();                                       // 0x00b7e500
};

class cMessageServer
{
public:
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04();
    virtual void PostMessage(uint32_t nID, int nA, int nB);       // +0x14
};

cMessageServer* MessageServer();                                  // 0x0067dcc0
cPlanetModel* PlanetModel();                                      // 0x00b3d350
void* FUN_00b3d240();                                             // 0x00b3d240
void* WatchMemoryBlock(void* pBlock);                             // 0x00d999d0
void* FUN_00ac80d0(cSPCreatureBase* pCreature, uint32_t nID);    // 0x00ac80d0

class cGameNounManager
{
public:
    virtual void n00(); virtual void n01(); virtual void n02(); virtual void n03();
    virtual void n04(); virtual void n05(); virtual void n06(); virtual void n07();
    virtual void n08(); virtual void n09(); virtual void n10(); virtual void n11();
    virtual void n12(); virtual void n13(); virtual void n14(); virtual void n15();
    virtual void n16(); virtual void n17(); virtual void n18(); virtual void n19();
    virtual void n20(); virtual void n21(); virtual void n22();
    virtual cSPCreatureBase* FindCreature(uint32_t nID);           // +0x5c
};

// ===========================================================================
// @ 0x00c17de0  SP::cSPCreatureBase::LookAtUpdate
// ===========================================================================
void __declspec(noinline) cSPCreatureBase::LookAtUpdate(float fBlend)
{
    cVector3 vTarget;
    cVector3 vScale;
    cVector3 vPos;
    cVector3 vForward;

    if (!mpAnimTarget)
        return;
    if (!mLocomotion.IsOrientationLocked())
        return;
    if (mLookAtState != 2)
        return;

    vTarget = SP::kNoDirection;

    if (mbLookAtEnabled)
    {
        if (mpNounManager)
        {
            cSPCreatureBase* pFound = mpNounManager->FindCreature(0xce9f6639);
            if (pFound)
            {
                if (pFound->mpAnimTarget)
                {
                    if (pFound->mbHasPartFlag)
                        SetLookAt(pFound, pFound->mpAnimTarget->GetBodyPartIndex(1, 0));
                    else
                        SetLookAt(pFound, pFound->mpAnimTarget->GetBodyPartIndex(2, 0));
                    goto UpdateState;
                }
            }
        }
    }

    if (mLocomotion.IsFacingValid())
    {
        if ((mFlags & 0x200) != 0)
        {
            if (gUseGroundMotion)
            {
                cVector3* pForward = mLocomotion.GetForward();
                vScale.x = pForward->x * kLookAtScale;
                vScale.y = pForward->y * kLookAtScale;
                vScale.z = pForward->z * kLookAtScale;
                cVector3* pPosition = mLocomotion.GetPosition();
                vPos.x = pPosition->x + vScale.x;
                vPos.y = pPosition->y + vScale.y;
                vPos.z = pPosition->z + vScale.z;
                cPlanetModel* pModel = PlanetModel();
                vTarget = *pModel->DirectionToSurfacePosition(&vPos, &vForward);
            }
            else
            {
                cPlanetModel* pModel = (cPlanetModel*)FUN_00b3d240();
                cVector3 vOffset = SP::kNoDirection;
                vTarget = *pModel->GetSurfaceOffset(&vPos, 1, vOffset);
            }

            if (Vector3Equal(&vTarget, &SP::kNoDirection))
            {
                cVector3* pForward = mLocomotion.GetForward();
                vScale.x = pForward->x * kLookAtScale;
                vScale.y = pForward->y * kLookAtScale;
                vScale.z = pForward->z * kLookAtScale;
                cVector3* pPosition = mLocomotion.GetPosition();
                vPos.x = pPosition->x + vScale.x;
                vPos.y = pPosition->y + vScale.y;
                vPos.z = pPosition->z + vScale.z;
                cPlanetModel* pModel = PlanetModel();
                vTarget = *pModel->DirectionToSurfacePosition(&vPos, &vForward);
            }
        }
        else if (mLocomotion.IsOrientationLocked())
        {
            cAnimData* pData = mLocomotion.GetAnimData();
            if (pData->mpTarget)
            {
                vTarget = pData->mOffset;
            }
            else
            {
                cVector3* pForward = mLocomotion.GetForward();
                vScale.x = pForward->x * kLookAtScale;
                vScale.y = pForward->y * kLookAtScale;
                vScale.z = pForward->z * kLookAtScale;
                cVector3* pPosition = mLocomotion.GetPosition();
                vPos.x = pPosition->x + vScale.x;
                vPos.y = pPosition->y + vScale.y;
                vPos.z = pPosition->z + vScale.z;
                cPlanetModel* pModel = PlanetModel();
                vTarget = *pModel->DirectionToSurfacePosition(&vPos, &vForward);
            }
        }
    }
    else
    {
        ClearLookAt();

        if (FUN_00ac80d0(this, 0x18eb45e))
        {
            cAnimData* pData = mpAnimPlayer->Play(0x4000000, 0);
            if (pData)
            {
                cSPCreatureBase* pCreature = (cSPCreatureBase*)WatchMemoryBlock(pData);
                if (pCreature)
                {
                    if (pCreature->mpAnimTarget)
                        pCreature->mpAnimTarget->GetBodyPartPosition(&vTarget, 2, 1, -1);
                }
            }
        }
    }

UpdateState:
    switch (mpAnimTarget->mState)
    {
    case 0:
        {
            cPose* pSource = mpAnimTarget->mpPose;
            if (pSource && pSource->mpParent && mpAnimTarget->mSubState == 2)
            {
                cPose* pPose = pSource->mpParent;
                cVector3 vLocal;
                cVector3* pRotated = (cVector3*)checkerlib::QuaternionVectorTransform(
                    (float*)&vLocal, (float*)&pPose->mRotation,
                    (float*)&pPose->mpBones[mpAnimTarget->mBoneIndex].mLocalPosition);
                mpAnimTarget->mLookAtPoint.x = pRotated->x + pPose->mPosition.x;
                mpAnimTarget->mLookAtPoint.y = pRotated->y + pPose->mPosition.y;
                mpAnimTarget->mLookAtPoint.z = pRotated->z + pPose->mPosition.z;
            }
        }
        break;
    case 1:
        if (Vector3_NotEqual(&vTarget, &SP::kNoDirection))
            LookAtTo(fBlend, vTarget, 0);
        break;
    case 2:
        if (!mbLookAtEnabled)
        {
            uint32_t nGUID = GetCurrentAnimationGUID();
            cAnimData* pData = mLocomotion.GetAnimData();
            if (mpAnimTarget->IsOrientIdleAnim(nGUID) && pData->mpTarget)
            {
                SetAnimData(pData);
                return;
            }
            if (!Vector3_NotEqual(&vTarget, &SP::kNoDirection))
            {
                ClearLookAt();
                return;
            }
            LookAtTo(fBlend, vTarget, 1);
        }
        break;
    }
}

// ===========================================================================
// @ 0x00c18370  SP::cSPCreatureBase::UpdateNetDirection
// ===========================================================================
void __declspec(noinline) cSPCreatureBase::UpdateNetDirection()
{
    cVector3 vDir;
    cVector3 vVel;

    vDir = SP::kNoDirection;

    uint32_t nFlags = mFlags;
    bool bSteering = mbSteering;

    if ((nFlags & 0x200) != 0)
    {
        MessageServer()->PostMessage(0x7c66a67, 0, 0);

        if (gUseGroundMotion)
        {
            cVector3* pVel = mLocomotion.GetVelocity();
            float fLenSq = pVel->x * pVel->x + pVel->y * pVel->y + pVel->z * pVel->z;
            if (fLenSq == kZero)
            {
                vDir.x = gGravityDirection.x * gGravityScale;
                vDir.y = gGravityDirection.y * gGravityScale;
                vDir.z = gGravityDirection.z * gGravityScale;
            }
        }
    }

    float fRadius = mpSpecies->mLookAtRadius;

    if (!bSteering)
    {
        cVector3* pVel = mLocomotion.GetVelocity();
        vVel = *pVel;

        cVector3 vUp;
        cVector3* pPos = mLocomotion.GetPosition();
        float fInv = 1.0f / sqrtf(pPos->x * pPos->x + pPos->y * pPos->y + pPos->z * pPos->z
                                   + kEpsilon);
        vUp.x = pPos->x * fInv;
        vUp.y = pPos->y * fInv;
        vUp.z = pPos->z * fInv;

        float fVelSq = vVel.x * vVel.x + vVel.y * vVel.y + vVel.z * vVel.z;
        if (kZero < fVelSq)
        {
            float fDot = vUp.x * vVel.x + vUp.z * vVel.z + vUp.y * vVel.y;
            cVector3 vProj;
            vProj.x = vUp.x * fDot;
            vProj.y = vUp.y * fDot;
            vProj.z = vUp.z * fDot;
            if (kZero > (vProj.x * vUp.x + vProj.z * vUp.z + vProj.y * vUp.y))
                fRadius = sqrtf(vProj.z * vProj.z + (vProj.y * vProj.y + vProj.x * vProj.x))
                          + fRadius;
        }
    }

    cVector3* pPos2 = mLocomotion.GetPosition();
    float fInv2 = 1.0f / sqrtf(pPos2->x * pPos2->x + pPos2->y * pPos2->y + pPos2->z * pPos2->z
                               + kEpsilon);
    cVector3 vPush;
    vPush.x = pPos2->x * fInv2;
    vPush.y = pPos2->y * fInv2;
    vPush.z = pPos2->z * fInv2;
    vDir.x = vPush.x * fRadius * kNetScaleA + vDir.x;
    vDir.y = vPush.y * fRadius * kNetScaleA + vDir.y;
    vDir.z = vPush.z * fRadius * kNetScaleA + vDir.z;

    mLocomotion.OffsetPosition(vDir, 0);

    void* pPart = GetPartData(FindIndex(0x53));
    ApplyWave(*(float*)((char*)pPart + 0x104));

    if (bSteering)
    {
        uint32_t nCheck = mFlags;

        mSteerState = 3;
        mbSteering = false;

        if ((nCheck & 0x200) != 0)
        {
            cVector3* pPos3 = mLocomotion.GetPosition();
            gStoredDirection = *pPos3;
        }

        InterruptAnimation(0x772ff58, -1, 0);
        mbWaveFinished = true;
        return;
    }

    if (mpSpecies->mWaveCount > 0)
        InterruptAnimation(0x77300ff, -1, 0);
    else
        InterruptAnimation(0x5485a4c, -1, 0);
}

// ===========================================================================
// @ 0x00c18740  SP::cSPCreatureBase::UpdateWaveMotion
// ===========================================================================
void __declspec(noinline) cSPCreatureBase::UpdateWaveMotion(float fBlend, uint32_t nAmount)
{
    cVector3* pPos = mLocomotion.GetPosition();
    float fDist = sqrtf(pPos->x * pPos->x + pPos->y * pPos->y + pPos->z * pPos->z);
    float fRange = PlanetModel()->GetLookAtRange();

    if (fDist > fRange)
    {
        mbWaveFinished = false;
        InterruptAnimation(0x7982fb2, -1, 0);
    }

    if ((nAmount & 0xff) == 0)
    {
        uint32_t nAnim = 0;
        if (mpAnimTarget)
        {
            mpAnimTarget->GetCurrentAnimation(&nAnim, 0, 0, 0);
            if (nAnim == 0x772ff58)
                return;
        }
        mbWaveFinished = false;
        InterruptAnimation(0x7982fb2, -1, 0);
        return;
    }

    void* pPart = GetPartData(FindIndex(0x53));
    float fAmount = *(float*)((char*)pPart + 0x104) * (float)(uint32_t)nAmount * kMilli;

    if (mWaveHeight > fAmount)
    {
        ApplyWave(fAmount);

        cVector3 vDir;
        cVector3 vVel;

        vDir = SP::kNoDirection;

        uint32_t nFlags = mFlags;
        bool bSteering = mbSteering;

        if ((nFlags & 0x200) != 0 && gUseGroundMotion)
        {
            cVector3* pVelocity = mLocomotion.GetVelocity();
            float fLenSq = pVelocity->x * pVelocity->x + pVelocity->y * pVelocity->y
                           + pVelocity->z * pVelocity->z;
            if (fLenSq == kZero)
            {
                vDir.x = gGravityDirection.x * gGravityScale;
                vDir.y = gGravityDirection.y * gGravityScale;
                vDir.z = gGravityDirection.z * gGravityScale;
            }
        }

        float fRadius = mpSpecies->mLookAtRadius;

        if (!bSteering)
        {
            cVector3* pVelocity = mLocomotion.GetVelocity();
            vVel = *pVelocity;

            cVector3 vUp;
            cVector3* pPosition = mLocomotion.GetPosition();
            normalized_safe((float*)&vUp, (float*)pPosition);

            float fVelSq = vVel.x * vVel.x + vVel.y * vVel.y + vVel.z * vVel.z;
            if (kZero < fVelSq)
            {
                float fDot = vUp.x * vVel.x + vUp.z * vVel.z + vUp.y * vVel.y;
                cVector3 vProj;
                vProj.x = vUp.x * fDot;
                vProj.y = vUp.y * fDot;
                vProj.z = vUp.z * fDot;
                if (kZero > (vProj.x * vUp.x + vProj.z * vUp.z + vProj.y * vUp.y))
                    fRadius = sqrtf(vProj.z * vProj.z + (vProj.y * vProj.y + vProj.x * vProj.x))
                              + fRadius;
            }
        }

        cVector3* pPos2 = mLocomotion.GetPosition();
        float fInv = 1.0f / sqrtf(pPos2->x * pPos2->x + pPos2->y * pPos2->y + pPos2->z * pPos2->z
                                  + kEpsilon);
        cVector3 vPush;
        vPush.x = pPos2->x * fInv;
        vPush.y = pPos2->y * fInv;
        vPush.z = pPos2->z * fInv;
        vDir.x = vPush.x * fRadius * fBlend * kMilli * kNetScaleB + vDir.x;
        vDir.y = vPush.y * fRadius * fBlend * kMilli * kNetScaleB + vDir.y;
        vDir.z = vPush.z * fRadius * fBlend * kMilli * kNetScaleB + vDir.z;

        mLocomotion.OffsetPosition(vDir, 0);
        return;
    }

    mbWaveFinished = false;
    InterruptAnimation(0x7982fb2, -1, 0);
}
