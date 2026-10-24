// =============================================================================================
// SporeApp.exe slice s00b45ca0  (batch gold7, worker 5)
//
// 1 routine from the Simulator physics area:
//
//   0x00b45ca0  cThing::Update - per-frame planetary position/velocity integration
//
// Layout: offsets are taken from the disassembly of this build. Every touched field is named.
// Flags: /O2 /Ob2 /MD /Gy /TP /arch:SSE /GS-
// =============================================================================================
#include "types.h"

// ---------------------------------------------------------------------------------------------
// external helpers (retail addresses; not defined here)
// ---------------------------------------------------------------------------------------------
void*   __cdecl PlanetModel();                                          // 0x00b3d350
void*   __cdecl Vector3Normalize(void* pOut, const void* pIn);          // 0x00436ce0
void*   __cdecl Matrix3FromQuaternion(void* pOut, const void* pQuat);   // 0x0059c190
void*   __cdecl FUN_00b81630(void* pOut, const void* pIn);              // 0x00b81630
void*   __cdecl BuildSurfaceOrientation2(void* pDst, void* pA, void* pB); // 0x00b7f1f0
void    __cdecl ApplyPlanetCorrection(void* pOut, void* pPhysics);      // 0x00b444c0

// ---------------------------------------------------------------------------------------------
// image constants
// ---------------------------------------------------------------------------------------------
extern float    g_fVecC;                                                // 0x0167eb8c
extern float    g_fVecD;                                                // 0x0167eb90
extern float    g_fVecE;                                                // 0x0167eb94
extern float    g_fOne8b0;                                              // 0x013eb8b0
extern float    g_fSmall54;                                             // 0x01461154
extern float    g_fHalf064;                                             // 0x01471064
extern float    g_fOne5720;                                             // 0x01485720

// small asm helper: the original emits an x87 fsqrt for the vector lengths
float __declspec(noinline) SqrtD(float f)
{
    __asm {
        fld   f
        fsqrt
        fstp  f
    }
    return f;
}

// ---------------------------------------------------------------------------------------------
// the planet model produced by PlanetModel()
// ---------------------------------------------------------------------------------------------
class cPlanetModel {
public:
    float   FUN_00b7e490();                                 // 0x00b7e490
    void*   GetNormalAt(void* pOut, const void* pIn);       // 0x00b7e3b0
    float   GetWaterHeight();                               // 0x00b7e390
    float   GetRadiusAt(const void* pIn);                   // 0x00b7ef70
};

// ---------------------------------------------------------------------------------------------
// the physics/proxy object at +0x40 (its vtable exposes the methods below)
// ---------------------------------------------------------------------------------------------
class cPhysicsProxy {
public:
    virtual void     v00();
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
    virtual void     v28();
    virtual void*    v2c(void* pOut);                       // +0x2c
    virtual void     v30();
    virtual void     v34();
    virtual void     v38(const void* pIn);                  // +0x38
    virtual void     v3c(const void* pIn);                  // +0x3c
    virtual void     v40();
    virtual void     v44();
    virtual void     v48();
    virtual void     v4c();
    virtual void     v50();
    virtual void     v54();
    virtual void     v58();
    virtual void     v5c();
    virtual void     v60();
    virtual void     v64();
    virtual void     v68();
    virtual void     v6c();
    virtual void     v70();
    virtual void     v74();
    virtual void     v78();
    virtual void     v7c();
    virtual void     v80();
    virtual void     v84();
    virtual void     v88();
    virtual void     v8c();
    virtual void     v90();
    virtual void     v94();
    virtual void     v98();
    virtual void     v9c();
    virtual void     va0();
    virtual void     va4();
    virtual void     va8();
    virtual void     vac();
    virtual void     vb0();
    virtual void     vb4();
    virtual void     vb8();
    virtual void     vbc();
    virtual void     vc0();
    virtual void     vc4();
    virtual float    vc8();                                 // +0xc8

    // direct (non-virtual) helpers reached through the proxy pointer
    void     FUN_00c41d60(const void* pIn);                 // 0x00c41d60
    void     FUN_00c41d90(const void* pIn);                 // 0x00c41d90
};

// ---------------------------------------------------------------------------------------------
// the simulated thing being updated
// ---------------------------------------------------------------------------------------------
class cThing {
public:
    uint8_t  mPad00[0x04];                                  // +0x00
    int32_t  mnMode;                                        // +0x04
    uint8_t  mPad08[0x14];                                  // +0x08
    float    mfPosX;                                        // +0x1c
    float    mfPosY;                                        // +0x20
    float    mfPosZ;                                        // +0x24
    float    mfVelX;                                        // +0x28
    float    mfVelY;                                        // +0x2c
    float    mfVelZ;                                        // +0x30
    uint8_t  mbFlag34;                                      // +0x34
    uint8_t  mPad35;                                        // +0x35
    uint8_t  mbFlag36;                                      // +0x36
    uint8_t  mPad37[0x40 - 0x37];                           // +0x37
    cPhysicsProxy* mpPhys;                                  // +0x40
    uint8_t  mPad44[0xa4 - 0x44];                           // +0x44
    float    mfRotXX;                                       // +0xa4
    float    mfRotXY;                                       // +0xa8
    float    mfRotXZ;                                       // +0xac
    float    mfRotYX;                                       // +0xb0
    float    mfRotYY;                                       // +0xb4
    float    mfRotYZ;                                       // +0xb8
    float    mfRotZX;                                       // +0xbc
    float    mfRotZY;                                       // +0xc0
    float    mfRotZZ;                                       // +0xc4
    float    mfAccX;                                        // +0xc8
    float    mfAccY;                                        // +0xcc
    float    mfAccZ;                                        // +0xd0
    float    mfGravX;                                       // +0xd4
    float    mfGravY;                                       // +0xd8
    float    mfGravZ;                                       // +0xdc
    float    mfPrevAccX;                                    // +0xe0
    float    mfPrevAccY;                                    // +0xe4
    float    mfPrevAccZ;                                    // +0xe8
    float    mfOldX;                                        // +0xec
    float    mfOldY;                                        // +0xf0
    float    mfOldZ;                                        // +0xf4

    float FUN_00b3dcd0();                                   // 0x00b3dcd0
    void FUN_00b3d9c0(void* pOut);                          // 0x00b3d9c0
    void FUN_00b3dda0(const void* pA, const void* pB);      // 0x00b3dda0
    void FUN_00b3f940();                                    // 0x00b3f940
    void FUN_00b3f300(void* pOut);                          // 0x00b3f300
    void FUN_00b3f420(void* pOut);                          // 0x00b3f420
    void FUN_00b43290();                                    // 0x00b43290

    void Update(float fDelta);                              // 0x00b45ca0
};

// @ 0x00b45ca0
void cThing::Update(float fDelta)
{
    float fStep = FUN_00b3dcd0();
    if (fStep <= 0.0f)
        return;

    cPlanetModel* pPlanet = (cPlanetModel*)PlanetModel();
    float fScale = pPlanet->FUN_00b7e490();

    float afPos[3];
    FUN_00b3d9c0(afPos);

    float afDir[3];
    if (mnMode == 1) {
        if (mbFlag34 == 0) {
            float fLen = (float)SqrtD(afPos[0] * afPos[0] + afPos[1] * afPos[1] + afPos[2] * afPos[2]);
            if (fLen <= g_fSmall54)
                goto lab_ea4;
            float fInv = g_fOne5720 / fLen;
            afDir[0] = fInv * afPos[0] * fScale;
            afDir[1] = fInv * afPos[1] * fScale;
            afDir[2] = fInv * afPos[2] * fScale;
        } else {
            if (mfPosX == g_fVecC && mfPosY == g_fVecD && mfPosZ == g_fVecE)
                goto lab_ea4;
            float afN[3];
            pPlanet->GetNormalAt(afN, afPos);
            Vector3Normalize(afDir, afN);
            const float* pN2 = (const float*)Vector3Normalize(afN, afPos);
            float fD = (-afDir[0] * (pN2[0] * fScale) - afDir[2] * (pN2[2] * fScale))
                     - afDir[1] * (pN2[1] * fScale);
            const float* pN3 = (const float*)Vector3Normalize(afN, &mfPosX);
            afDir[0] = -pN3[0] * fD;
            afDir[1] = -pN3[1] * fD;
            afDir[2] = -pN3[2] * fD;
        }
        FUN_00b3dda0(afPos, afDir);
    }

lab_ea4:
    FUN_00b3f940();

    mfAccX = mfPrevAccX * fStep;
    mfAccY = mfPrevAccY * fStep;
    mfAccZ = mfPrevAccZ * fStep;

    mfGravX = (mfRotYX * mfOldY + mfRotZX * mfOldZ) + mfOldX * mfRotXX;
    mfGravY = (mfRotXY * mfOldX + mfRotYY * mfOldY) + mfRotZY * mfOldZ;
    mfGravZ = (mfRotXZ * mfOldX + mfRotYZ * mfOldY) + mfRotZZ * mfOldZ;

    float fHalf = (fDelta * fDelta) * 0.5f;
    afPos[0] = mfPosX * fDelta + mfAccX * fHalf + afPos[0];
    afPos[1] = mfPosY * fDelta + mfAccY * fHalf + afPos[1];
    afPos[2] = mfPosZ * fDelta + mfAccZ * fHalf + afPos[2];

    float afQ[4];
    FUN_00b3f300(afQ);

    float fVX = mfVelX;
    float fVY = mfVelY;
    float fVZ = mfVelZ;
    float qx = afQ[0];
    float qy = afQ[1];
    float qz = afQ[2];
    float qw = afQ[3];

    float n0 = ((qw * 0.0f - ((qy * fVZ + qx * fVY) + qz * fVX)) * 0.5f) * fDelta + qw;
    float n1 = ((qx * 0.0f + qw * fVZ) + (qy * fVY - fVX * qz)) * 0.5f * fDelta + qx;
    float n2 = ((qy * 0.0f + qw * fVX) + (fVZ * qz - qy * fVY)) * 0.5f * fDelta + qy;
    float n3 = ((qz * 0.0f + qw * fVY) + (qx * fVZ - qy * fVZ)) * 0.5f * fDelta + qz;
    float fInv = 1.0f / (float)SqrtD(n3 * n3 + (n2 * n2 + (n1 * n1 + n0 * n0)));
    afQ[0] = n3 * fInv;
    afQ[1] = n1 * fInv;
    afQ[2] = n0 * fInv;

    mfPosX = mfGravX * fDelta + mfPosX;
    mfPosY = mfGravY * fDelta + mfPosY;
    mfPosZ = mfGravZ * fDelta + mfPosZ;

    afQ[3] = fInv * n3;

    float afBounds[9];
    afBounds[0] = 3.402823466e38f;
    afBounds[1] = -3.402823466e38f;
    afBounds[2] = -3.402823466e38f;
    afBounds[3] = 3.402823466e38f;
    afBounds[4] = 3.402823466e38f;
    afBounds[5] = -3.402823466e38f;
    afBounds[6] = -3.402823466e38f;
    afBounds[7] = -3.402823466e38f;
    afBounds[8] = -3.402823466e38f;

    mfPosX = mfAccZ * fDelta + mfPosX;
    mfPosY = mfAccY * fDelta + mfPosY;
    mfPosZ = mfAccZ * fDelta + mfPosZ;

    FUN_00b3f420(afBounds);

    float afCenter[3];
    afCenter[0] = (afBounds[2] + afBounds[0]) * 0.5f;
    afCenter[1] = (afBounds[5] + afBounds[3]) * 0.5f;
    afCenter[2] = (afBounds[6] + afBounds[4]) * 0.5f;

    const float* pMat = (const float*)Matrix3FromQuaternion(afBounds, afQ);
    afPos[0] = afPos[0] - ((pMat[6] * afCenter[2] + pMat[3] * afCenter[1]) + afCenter[0] * pMat[0]);
    afPos[1] = afPos[1] - ((pMat[7] * afCenter[2] + pMat[4] * afCenter[1]) + pMat[1] * afCenter[0]);
    afPos[2] = afPos[2] - ((pMat[8] * afCenter[2] + pMat[5] * afCenter[1]) + pMat[2] * afCenter[0]);

    if (mnMode == 0) {
        mpPhys->FUN_00c41d60(&mfPosX);
        mpPhys->FUN_00c41d90(&mfVelX);
        float fH = mpPhys->vc8();
        if (fH == 0.0f)
            mpPhys->v3c(afQ);
        ApplyPlanetCorrection(afPos, mpPhys);
    } else if (mnMode == 1) {
        mpPhys->v38(afPos);
        mpPhys->v3c(afQ);
        if (mbFlag34 == 0) {
            float fWater = pPlanet->GetWaterHeight();
            float fRadius = pPlanet->GetRadiusAt(afPos);
            float fRef = (fWater <= fRadius) ? fWater : fRadius;
            mbFlag34 = (fRef - (float)SqrtD(afPos[0] * afPos[0] + afPos[1] * afPos[1] + afPos[2] * afPos[2]))
                       < g_fSmall54;
            if (!mbFlag34)
                goto lab_c2;
        }
        void* pOutA = FUN_00b81630(afQ, afPos);
        mpPhys->v38(pOutA);
        void* pOutB = mpPhys->v2c(afQ);
        pOutB = BuildSurfaceOrientation2(afBounds, pOutB, afQ);
        mpPhys->v3c(pOutB);
        if (g_fSmall54 < (mfVelX * mfVelX + mfVelY * mfVelY) + mfVelZ * mfVelZ
            || g_fSmall54 < (mfPosX * mfPosX + mfPosY * mfPosY) + mfPosZ * mfPosZ)
            mbFlag36 = 1;
        else
            mbFlag36 = 0;
    }

lab_c2:
    mfAccX = g_fVecC;
    mfAccY = g_fVecD;
    mfAccZ = g_fVecE;
    mfGravX = g_fVecC;
    mfGravY = g_fVecD;
    mfGravZ = g_fVecE;
    mfPrevAccX = g_fVecC;
    mfPrevAccY = g_fVecD;
    mfPrevAccZ = g_fVecE;
    mfOldX = g_fVecC;
    mfOldY = g_fVecD;
    mfOldZ = g_fVecE;
    FUN_00b43290();
}
