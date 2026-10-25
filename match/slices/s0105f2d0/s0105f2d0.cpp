// Slice s0105f2d0: SP::cUFOLocomotion solar/galaxy locomotion.
//
// The three routines evaluate the UFO's solar-system locomotion: the galaxy
// course/steering update, the avoidance/sinusoidal displacement, and the final
// placement of the visible solar body.  All of them operate on the shipping
// cUFOShipState (the "solar system UFO" game-data object whose collection of
// navigation fields starts at +0x628) and are driven from
// cUFOLocomotion::UpdateLocomotion.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// small value types touched by the locomotion code
// ---------------------------------------------------------------------------
class cSPVector3 {
public:
    float mX;                    // +0x00
    float mY;                    // +0x04
    float mZ;                    // +0x08
};

class cSPVector4 {
public:
    float mX;                    // +0x00
    float mY;                    // +0x04
    float mZ;                    // +0x08
    float mW;                    // +0x0c
};

// ---------------------------------------------------------------------------
// constants in .data / .rdata (values read from the shipping image)
// ---------------------------------------------------------------------------
extern cSPVector3 g_vSolarAxisX;          // 0x015b8d9c = (1, 0, 0)
extern cSPVector3 g_vSolarAxisY;          // 0x015b8da8 = (0, 1, 0)
extern cSPVector3 g_vSolarAxisZ;          // 0x015b8db4 = (0, 0, 1)

extern float g_fSolarZeroX;               // 0x016e2114 (zero-initialised)
extern float g_fSolarZeroY;               // 0x016e2118
extern float g_fSolarZeroZ;               // 0x016e211c
extern uint8_t g_bSolarAvoidEnabled;      // 0x015b8e24
extern float g_fSolarArrivePlanet;        // 0x015b8e20 = 0.5f
extern float g_fSolarArriveStar;          // 0x015b8e1c = 0.001f
extern float g_fSolarBodyRadius;          // 0x015b8e28 = 20.0f

// ---------------------------------------------------------------------------
// placeholder helpers used through the cSPTimer in the ship state
// ---------------------------------------------------------------------------
class cSPTimer {
public:
    void Restart();                                      // 0x00bc3130
    uint64_t GetElapsedTime();                           // 0x00bc3190
    uint8_t mnPad000[0x48];                              // opaque timer payload
};

class cUFODockState {                                    // lives at ship + 0x628
public:
    void UpdateDockedParent();                           // 0x00bc3170
    uint8_t mnPad000[0x20];
};

class cUFOWaypoint {                                     // referenced by +0x75c
public:
    cSPVector3* GetPosition();                           // vtable slot +0x2c
};

class cCivData {                                         // referenced by +0x764
public:
    cSPVector3* GetCities();                             // 0x005c65e0
};

// ---------------------------------------------------------------------------
// the solar-system UFO game data ("ship state"); field map derived from the
// three routines below.
// ---------------------------------------------------------------------------
class cUFOShipState {
public:
    uint8_t mnPad000[0x628];        // +0x000
    cUFODockState mDockState;       // +0x628
    cSPTimer mTimer;                // +0x648 (0x48 bytes)
    bool mbSolarActive;             // +0x690
    uint8_t mnPad691[0x83];         // +0x691
    int32_t mnSolarTarget;          // +0x714
    cSPVector3 mSolarPosition;      // +0x718
    cSPVector3 mSolarVelocity;      // +0x724
    cSPVector4 mSolarHeading;       // +0x730
    bool mbSolarArrived;            // +0x74c
    uint8_t mnPad74d[3];            // +0x74d
    cSPVector3 mSolarDestination;   // +0x750
    cUFOWaypoint* mpSolarWaypoint;  // +0x75c
    uint32_t mnPad760;              // +0x760
    cCivData* mpCivData;            // +0x764
    uint32_t mnPad768;              // +0x768
    int32_t mnWarpGroup;            // +0x76c

    bool PopToDestination();                             // 0x00c37e60
};

// ---------------------------------------------------------------------------
// the simulator/tuning objects reached from the routines
// ---------------------------------------------------------------------------
class cSPSimulatorSpaceGame {
public:
    void* GetPlayerInventory();                          // 0x00a1ad60
    void OnStarMoveDone();                               // 0x00fff6a0
    void OnPlanetMoveDone();                             // 0x01000520
};

class cUFOKinestheticsTuning {
public:
    uint8_t mnPad000[0x114];        // +0x000
    float mGalaxyMaxPlump;          // +0x114
    float mGalaxyMinPlumpDistance;  // +0x118
    float mGalaxyMaxPlumpDistance;  // +0x11c
    float mBaseUFODamagePush;       // +0x120
    float GetGalaxyWarpMultiplier(int32_t nWarpGroup, int32_t nTarget);  // 0x00c3b880
};

class cGameContext {
public:
    uint8_t mnPad000[0x2c];         // +0x000
    int32_t mnGameMode;             // +0x2c
    uint8_t mnPad030[0x118];        // +0x030
    int32_t mnModeToken;            // +0x148
};

class cUniverseContext {
public:
    bool IsPlayerControlled();                           // 0x00c8b800
};

// the wrapper handed to the locomotion update; its +0x14 pointer addresses the
// base sub-object of the ship state (ship + 0x34).
class cUFOState {
public:
    uint8_t mnPad000[0x10];         // +0x000
    float mDeltaSeconds;            // +0x10
    void* mpShipBase;               // +0x14

    cSPSimulatorSpaceGame* GetSimulator();               // 0x00ffbe50
};

// camera/view object used by the final push-out call.
struct cUFOViewVTable {
    uint8_t mnPad000[0xc8];          // +0x000
    void (__thiscall* mpPushBody)(void* pThis, cSPVector3* pDirection,
                                  float fDistance, int32_t nMode);       // +0x0c8
};

class cUFOView {
public:
    cUFOViewVTable* mpVTable;        // +0x00
};

// generic game-data object; only its collision-position accessor is needed.
class cGameDataObject {
public:
    uint8_t mnPad000[0x34];          // +0x000
    void* mpVTableHolder;            // +0x34
    cSPVector3* GetCollisionPosition();                          // vtable slot +0x2c
};

// object handed to GetGameDataVector; only its first two pointers (the
// begin/end of the object vector) are read.
struct cGameDataVector {
    intptr_t* mpBegin;               // +0x00
    intptr_t* mpEnd;                 // +0x04
};

extern void* g_ufoBodyFilter;        // 0x018ebadc

// ---------------------------------------------------------------------------
// free helpers / entry points
// ---------------------------------------------------------------------------
cGameDataVector* __cdecl FindGameDataVector(void* pContext, void* pFilter); // 0x00b21340
void* __cdecl FindGameDataContext();                                      // 0x00b3d300
cUFOKinestheticsTuning* __cdecl GetKinestheticsTuning();                  // 0x00c37360
int32_t __cdecl GetUniverseContext();                                     // 0x01021080
cUniverseContext* __cdecl GetUniverseContextObject();                     // 0x01021230
cGameContext* __cdecl GetGameContext();                                   // 0x00b3d4d0

void __cdecl PhysicsMoveUFO(cSPVector3* pPosition, cSPVector3* pVelocity,
                            const cSPVector3* pTarget, float fMaxPlump,
                            float fPush, float fDeltaSeconds);            // 0x010426a0
cSPVector3* __cdecl RotateVectorByQuaternion(cSPVector3* pOut,
                                             const cSPVector3* pAxis,
                                             const cSPVector4* pQuat);     // 0x0059aed0
cSPVector4* __cdecl QuaternionFromFacingAndUp(cSPVector4* pOut,
                                              const cSPVector3* pFacing,
                                              const cSPVector3* pUp);      // 0x0069b600
cSPVector3* __cdecl RotateVectorInPlace(cSPVector3* pVector,
                                        const cSPVector4* pQuat);          // 0x00799320
cSPVector4* __cdecl SlerpHeading(const cSPVector4* pFrom, cSPVector4* pOut,
                                 const cSPVector3* pDirection,
                                 float fScale);                            // 0x005b26f0
cSPVector4* __cdecl SlerpHeadingSlow(const cSPVector3* pDirection,
                                     const cSPVector4* pFrom,
                                     const cSPVector4* pTo,
                                     float fScale);                        // 0x005b2500
cSPVector3* __cdecl NormalizeVectorGuarded(cSPVector3* pOut,
                                           const cSPVector3* pIn);         // 0x00449c20
cSPVector3* __cdecl NormalizeVector(cSPVector3* pOut,
                                    const cSPVector3* pIn);                // 0x00436ce0
cSPVector3* __cdecl ClosestPointOnSegment(cSPVector3* pOut,
                                          const cSPVector3* pA,
                                          const cSPVector3* pB,
                                          const cSPVector3* pP);           // 0x00698e00
cUFOView* __cdecl GetSolarView();                                         // 0x0067de00

// ---------------------------------------------------------------------------
// SP::cUFOLocomotion
// ---------------------------------------------------------------------------
class cUFOLocomotion {
public:
    void UpdateSolarGalaxyLocomotion(cUFOState* pState, int32_t nDeltaMs);   // @ 0x0105f2d0
    void UpdateCourse(cUFOState* pState, int32_t nDeltaMs);                  // 0x0105e290
    void AvoidSolarObstacles(cUniverseContext* pUniverse, cUFOShipState* pShip,
                             cSPVector3* pTarget);                           // 0x0105eeb0
    void UpdateSolarCourse(cUFOShipState* pShip, cSPVector3* pTarget);       // 0x0105d200
};

void UpdateSolarAvoidance(cUFOShipState* pShip, float fAmplitude,
                          int32_t nDeltaMs);                             // @ 0x0105f760
cSPVector3* __stdcall UpdateSolarBody(cSPVector3* pOut,
                                      cUFOShipState* pShip);             // @ 0x0105fbc0

// ---------------------------------------------------------------------------
// SP::cUFOLocomotion::UpdateSolarGalaxyLocomotion
// @ 0x0105f2d0
// ---------------------------------------------------------------------------
void cUFOLocomotion::UpdateSolarGalaxyLocomotion(cUFOState* pState, int32_t nDeltaMs)
{
    float fDeltaSeconds = (float)(uint32_t)nDeltaMs * 0.001f;

    cUFOShipState* pShip;
    if (pState->mpShipBase == 0)
        pShip = 0;
    else
        pShip = (cUFOShipState*)((char*)pState->mpShipBase - 0x34);

    cSPSimulatorSpaceGame* pSimulator = pState->GetSimulator();
    void* pPlayer = pSimulator->GetPlayerInventory();
    bool bIsPlayer = (pShip == pPlayer);
    cUFOKinestheticsTuning* pTuning = GetKinestheticsTuning();

    cSPVector3 target;
    target.mX = g_fSolarZeroX;
    target.mY = g_fSolarZeroY;
    target.mZ = g_fSolarZeroZ;

    float fAccel = fDeltaSeconds * 5.0f;
    float fOne = 1.0f;
    float* pfSpeedScale = &fAccel;
    if (fOne <= fAccel)
        pfSpeedScale = &fOne;
    float fSpeedScale = *pfSpeedScale;

    int32_t nContext = GetUniverseContext();

    if (nContext == 1) {
        cUniverseContext* pUniverse = GetUniverseContextObject();
        if (!pUniverse->IsPlayerControlled()) {
            cGameContext* pContext = GetGameContext();
            int32_t nMode = pContext->mnGameMode;
            if ((nMode == 1 || nMode == 2) &&
                GetGameContext()->mnModeToken == 0x2f7c7bda)
                return;
            this->UpdateCourse(pState, nDeltaMs);
            return;
        }
        if (pShip->mpSolarWaypoint != 0) {
            cSPVector3* pPos = pShip->mpSolarWaypoint->GetPosition();
            pShip->mSolarDestination.mX = pPos->mX;
            pShip->mSolarDestination.mY = pPos->mY;
            pShip->mSolarDestination.mZ = pPos->mZ;
        }
        target.mX = pShip->mSolarDestination.mX;
        target.mY = pShip->mSolarDestination.mY;
        target.mZ = pShip->mSolarDestination.mZ;
        this->AvoidSolarObstacles(pUniverse, pShip, &target);
    }
    else {
        if (pShip->mpCivData != 0) {
            cSPVector3* pCity = pShip->mpCivData->GetCities();
            pShip->mSolarDestination.mX = pCity->mX;
            pShip->mSolarDestination.mY = pCity->mY;
            pShip->mSolarDestination.mZ = pCity->mZ;
        }
        target.mX = pShip->mSolarDestination.mX;
        target.mY = pShip->mSolarDestination.mY;
        target.mZ = pShip->mSolarDestination.mZ;
    }

    if (pShip->mbSolarArrived) {
        pShip->PopToDestination();
        pShip->mDockState.UpdateDockedParent();
        pShip->mnWarpGroup = 0;
        return;
    }

    float fMaxPlump;
    float fPush;
    if (nContext == 1) {
        fMaxPlump = pTuning->mGalaxyMaxPlump;
        fPush = pTuning->mGalaxyMinPlumpDistance;
    }
    else {
        this->UpdateSolarCourse(pShip, &target);
        float fMultiplier = pTuning->GetGalaxyWarpMultiplier(pShip->mnWarpGroup,
                                                             pShip->mnSolarTarget);
        fMaxPlump = pTuning->mGalaxyMaxPlumpDistance * fMultiplier;
        fPush = pTuning->mBaseUFODamagePush * fMultiplier;
    }

    PhysicsMoveUFO(&pShip->mSolarPosition, &pShip->mSolarVelocity, &target,
                   fMaxPlump, fPush, fDeltaSeconds);

    float fDeltaX = target.mX - pShip->mSolarPosition.mX;
    float fDeltaY = target.mY - pShip->mSolarPosition.mY;
    float fDeltaZ = target.mZ - pShip->mSolarPosition.mZ;
    float fLengthSq = fDeltaX * fDeltaX + fDeltaY * fDeltaY + fDeltaZ * fDeltaZ;
    if (1.5258789e-05f < fLengthSq) {
        float fInvLength = 1.0f / sqrtf(fLengthSq);

        cSPVector3 directionA;
        directionA.mX = fDeltaX * fInvLength;
        directionA.mY = fDeltaY * fInvLength;
        directionA.mZ = fDeltaZ * fInvLength;

        cSPVector3 directionB;
        directionB.mX = fDeltaX * fInvLength;
        directionB.mY = fDeltaY * fInvLength;
        directionB.mZ = fDeltaZ * fInvLength;

        float fAxisDot = directionB.mX * g_vSolarAxisZ.mX
                       + directionB.mY * g_vSolarAxisZ.mY
                       + directionB.mZ * g_vSolarAxisZ.mZ;
        if (fabsf(fAxisDot) < 0.999f) {
            cSPVector4 quat;
            QuaternionFromFacingAndUp(&quat, &directionB, &g_vSolarAxisZ);
            RotateVectorInPlace(&directionA, &quat);
            SlerpHeading(&quat, &pShip->mSolarHeading, &directionA, fSpeedScale);
        }
    }

    float fDistX = pShip->mSolarPosition.mX - target.mX;
    float fDistY = pShip->mSolarPosition.mY - target.mY;
    float fDistZ = pShip->mSolarPosition.mZ - target.mZ;
    float fDistance = sqrtf(fDistX * fDistX + fDistY * fDistY + fDistZ * fDistZ);

    float fArriveThreshold;
    if (nContext == 1)
        fArriveThreshold = g_fSolarArrivePlanet;
    else
        fArriveThreshold = g_fSolarArriveStar;

    if (fDistance < fArriveThreshold) {
        pShip->mbSolarArrived = true;
        pShip->mTimer.Restart();
        if (bIsPlayer) {
            if (nContext == 1)
                pSimulator->OnPlanetMoveDone();
            else if (nContext == 2)
                pSimulator->OnStarMoveDone();
        }
    }

    cUFOView* pView = GetSolarView();
    pView->mpVTable->mpPushBody(pView, &target, 500.0f, 1);
}

// ---------------------------------------------------------------------------
// SP::cUFOLocomotion::UpdateSolarAvoidance
// @ 0x0105f760
// ---------------------------------------------------------------------------
void UpdateSolarAvoidance(cUFOShipState* pShip, float fAmplitude, int32_t nDeltaMs)
{
    if (!g_bSolarAvoidEnabled) {
        pShip->mSolarPosition.mX = pShip->mSolarDestination.mX;
        pShip->mSolarPosition.mY = pShip->mSolarDestination.mY;
        pShip->mSolarPosition.mZ = pShip->mSolarDestination.mZ;
        return;
    }

    float fSwing = fAmplitude * 1.5f;
    float fTime = (float)pShip->mTimer.GetElapsedTime() * 0.001f;

    cSPVector3 vAxisY;
    RotateVectorByQuaternion(&vAxisY, &g_vSolarAxisY, &pShip->mSolarHeading);
    cSPVector3 vAxisX;
    RotateVectorByQuaternion(&vAxisX, &g_vSolarAxisX, &pShip->mSolarHeading);
    cSPVector3 vAxisZ;
    RotateVectorByQuaternion(&vAxisZ, &g_vSolarAxisZ, &pShip->mSolarHeading);

    float fSinY = sinf(fTime * 0.23f);
    float fSinX = sinf(fTime * 0.61f);
    float fSinZ = sinf(fTime * 1.01f);

    float fOffsetZ = fSinY * (fAmplitude * 0.75f);
    float fOffsetY = fSwing * fSinZ;
    float fOffsetX = fSwing * fSinX;

    pShip->mSolarPosition.mX = pShip->mSolarDestination.mX
                             + vAxisZ.mX * fOffsetZ
                             + vAxisY.mX * fOffsetY
                             + vAxisX.mX * fOffsetX;
    pShip->mSolarPosition.mY = pShip->mSolarDestination.mY
                             + vAxisZ.mY * fOffsetZ
                             + vAxisY.mY * fOffsetY
                             + vAxisX.mY * fOffsetX;
    pShip->mSolarPosition.mZ = pShip->mSolarDestination.mZ
                             + vAxisZ.mZ * fOffsetZ
                             + vAxisY.mZ * fOffsetY
                             + vAxisX.mZ * fOffsetX;

    int32_t nContext = GetUniverseContext();
    if (nContext == 1 || nContext == 2) {
        float fStep = (float)(uint32_t)nDeltaMs * 0.002f;
        float fOne = 1.0f;
        float* pfScale = &fStep;
        if (fOne <= fStep)
            pfScale = &fOne;

        cSPVector3 vFacing;
        RotateVectorByQuaternion(&vFacing, &g_vSolarAxisY, &pShip->mSolarHeading);

        float fPlaneDot = vFacing.mX * g_vSolarAxisZ.mX
                        + vFacing.mY * g_vSolarAxisZ.mY
                        + vFacing.mZ * g_vSolarAxisZ.mZ;

        cSPVector3 vDirection;
        vDirection.mX = vFacing.mX - g_vSolarAxisZ.mX * fPlaneDot;
        vDirection.mY = vFacing.mY - g_vSolarAxisZ.mY * fPlaneDot;
        vDirection.mZ = vFacing.mZ - g_vSolarAxisZ.mZ * fPlaneDot;

        float fLength = sqrtf(vDirection.mX * vDirection.mX
                            + vDirection.mY * vDirection.mY
                            + vDirection.mZ * vDirection.mZ);
        float fInvLength = 1.0f / fLength;
        vDirection.mX *= fInvLength;
        vDirection.mY *= fInvLength;
        vDirection.mZ *= fInvLength;

        cSPVector4 quat;
        QuaternionFromFacingAndUp(&quat, &vDirection, &g_vSolarAxisZ);

        float fQuatLength = sqrtf(quat.mX * quat.mX + quat.mY * quat.mY
                                + quat.mZ * quat.mZ + quat.mW * quat.mW);
        float fInvQuat = 1.0f / fQuatLength;
        quat.mX *= fInvQuat;
        quat.mY *= fInvQuat;
        quat.mZ *= fInvQuat;
        quat.mW *= fInvQuat;

        SlerpHeadingSlow(&vDirection, &pShip->mSolarHeading, &quat, *pfScale);
    }
}

// ---------------------------------------------------------------------------
// UpdateSolarBody
// @ 0x0105fbc0
// ---------------------------------------------------------------------------
cSPVector3* __stdcall UpdateSolarBody(cSPVector3* pOut, cUFOShipState* pShip)
{
    pOut->mX = pShip->mSolarDestination.mX;
    pOut->mY = pShip->mSolarDestination.mY;
    pOut->mZ = pShip->mSolarDestination.mZ;

    if (pShip->mnSolarTarget == 0 || pShip->mbSolarActive)
        return pOut;

    float fDistX = pOut->mX - pShip->mSolarPosition.mX;
    float fDistY = pOut->mY - pShip->mSolarPosition.mY;
    float fDistZ = pOut->mZ - pShip->mSolarPosition.mZ;
    float fDistance = sqrtf(fDistX * fDistX + fDistY * fDistY + fDistZ * fDistZ);
    if (fDistance <= 1.0f)
        return pOut;

    // walk every game-data object that shares our parent collection
    void* context = FindGameDataContext();                    // 0x00b3d300
    cGameDataVector* pCollection = FindGameDataVector(context, &g_ufoBodyFilter);

    intptr_t* pIt = pCollection->mpBegin;
    intptr_t* pEnd = pCollection->mpEnd;
    while (pIt != pEnd) {
        cGameDataObject* pOther = (cGameDataObject*)*pIt;
        if (pOther != (cGameDataObject*)pShip) {
            cSPVector3* pOtherPos = pOther->GetCollisionPosition();  // vtable +0x2c

            float fOtherX = pOtherPos->mX - pShip->mSolarPosition.mX;
            float fOtherY = pOtherPos->mY - pShip->mSolarPosition.mY;
            float fOtherZ = pOtherPos->mZ - pShip->mSolarPosition.mZ;
            float fOutX = pOut->mX - pShip->mSolarPosition.mX;
            float fOutY = pOut->mY - pShip->mSolarPosition.mY;
            float fOutZ = pOut->mZ - pShip->mSolarPosition.mZ;
            float fAlong = fOutX * fOtherX + fOutY * fOtherY + fOutZ * fOtherZ;

            if (0.0f < fAlong) {
                cSPVector3 closest;
                ClosestPointOnSegment(&closest, pOtherPos,
                                      &pShip->mSolarPosition, pOut);

                float fPosLength = sqrtf(pShip->mSolarPosition.mX
                                             * pShip->mSolarPosition.mX
                                       + pShip->mSolarPosition.mY
                                             * pShip->mSolarPosition.mY
                                       + pShip->mSolarPosition.mZ
                                             * pShip->mSolarPosition.mZ);
                float fClosestLength = sqrtf(closest.mX * closest.mX
                                           + closest.mY * closest.mY
                                           + closest.mZ * closest.mZ
                                           + 1e-8f);
                float fInvClosest = 1.0f / fClosestLength;

                cSPVector3 vRadial;
                vRadial.mX = closest.mX * fInvClosest * fPosLength - pOtherPos->mX;
                vRadial.mY = closest.mY * fInvClosest * fPosLength - pOtherPos->mY;
                vRadial.mZ = closest.mZ * fInvClosest * fPosLength - pOtherPos->mZ;

                float fRadialLength = sqrtf(vRadial.mX * vRadial.mX
                                          + vRadial.mY * vRadial.mY
                                          + vRadial.mZ * vRadial.mZ);
                if (fRadialLength < g_fSolarBodyRadius) {
                    cSPVector3 vDelta;
                    vDelta.mX = pOut->mX - pOtherPos->mX;
                    vDelta.mY = pOut->mY - pOtherPos->mY;
                    vDelta.mZ = pOut->mZ - pOtherPos->mZ;
                    if (vDelta.mX * vDelta.mX + vDelta.mY * vDelta.mY
                            + vDelta.mZ * vDelta.mZ < 1.5258789e-05f) {
                        vDelta.mX = pOut->mX - pShip->mSolarPosition.mX;
                        vDelta.mY = pOut->mY - pShip->mSolarPosition.mY;
                        vDelta.mZ = pOut->mZ - pShip->mSolarPosition.mZ;
                    }

                    cSPVector3 vDeltaNormalized;
                    NormalizeVectorGuarded(&vDeltaNormalized, &vDelta);

                    float fDot = vRadial.mX * vDeltaNormalized.mX
                               + vRadial.mY * vDeltaNormalized.mY
                               + vRadial.mZ * vDeltaNormalized.mZ;
                    cSPVector3 vTangential;
                    vTangential.mX = vRadial.mX - vDeltaNormalized.mX * fDot;
                    vTangential.mY = vRadial.mY - vDeltaNormalized.mY * fDot;
                    vTangential.mZ = vRadial.mZ - vDeltaNormalized.mZ * fDot;

                    cSPVector3 vOtherNormalized;
                    NormalizeVector(&vOtherNormalized, pOtherPos);

                    float fDot2 = vTangential.mX * vOtherNormalized.mX
                                + vTangential.mY * vOtherNormalized.mY
                                + vTangential.mZ * vOtherNormalized.mZ;
                    cSPVector3 vPlane;
                    vPlane.mX = vTangential.mX - vOtherNormalized.mX * fDot2;
                    vPlane.mY = vTangential.mY - vOtherNormalized.mY * fDot2;
                    vPlane.mZ = vTangential.mZ - vOtherNormalized.mZ * fDot2;

                    cSPVector3 vPlaneNormalized;
                    NormalizeVectorGuarded(&vPlaneNormalized, &vPlane);

                    cSPVector3 vPush;
                    vPush.mX = vPlaneNormalized.mX * g_fSolarBodyRadius
                             + pOtherPos->mX - pShip->mSolarPosition.mX;
                    vPush.mY = vPlaneNormalized.mY * g_fSolarBodyRadius
                             + pOtherPos->mY - pShip->mSolarPosition.mY;
                    vPush.mZ = vPlaneNormalized.mZ * g_fSolarBodyRadius
                             + pOtherPos->mZ - pShip->mSolarPosition.mZ;

                    cSPVector3 vPushNormalized;
                    NormalizeVectorGuarded(&vPushNormalized, &vPush);

                    cSPVector3 target;
                    target.mX = vPushNormalized.mX * fDistance
                              + pShip->mSolarPosition.mX;
                    target.mY = vPushNormalized.mY * fDistance
                              + pShip->mSolarPosition.mY;
                    target.mZ = vPushNormalized.mZ * fDistance
                              + pShip->mSolarPosition.mZ;

                    float fOutLength = sqrtf(pOut->mX * pOut->mX
                                           + pOut->mY * pOut->mY
                                           + pOut->mZ * pOut->mZ);

                    cSPVector3 vTargetNormalized;
                    NormalizeVector(&vTargetNormalized, &target);

                    pOut->mX = vTargetNormalized.mX * fOutLength;
                    pOut->mY = vTargetNormalized.mY * fOutLength;
                    pOut->mZ = vTargetNormalized.mZ * fOutLength;
                }
            }
        }
        ++pIt;
    }

    return pOut;
}
