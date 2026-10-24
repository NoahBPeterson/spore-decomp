// Slice s00ffd220: the player UFO simulator cluster - the hit-sphere lookup,
// the planet-target refresh, InitForPlanet, the destination-handle swap, the
// planet-validity test, CalculateMaxHealth / CalculateMaxEnergy and the
// FlyToPlanet / paired-effect beam emitters.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; comparison masks call targets)
// ---------------------------------------------------------------------------------------------
extern "C" void*        __cdecl FUN_01021260(void);   // 0x01021260 GetActivePlanet
extern "C" void*        __cdecl FUN_01021240(void);   // 0x01021240 GetPlayerCiv
extern "C" void*        __cdecl FUN_01021300(void);   // 0x01021300 GetPlayerEmpire
extern "C" void*        __cdecl FUN_0102f810(void);   // 0x0102f810
extern "C" void*        __cdecl SpaceGameGet(void);   // 0x01002bd0
extern "C" void*        __cdecl NounManager(void);    // 0x00b3d300
extern "C" void*        __cdecl App(void);            // 0x0067dd10
extern "C" void*        __cdecl EffectsManagerPtr(void); // 0x0067ddd0
extern "C" void*        __cdecl MessageServer(void);  // 0x0067dcc0
extern "C" void*        __cdecl GetSpaceCombatTuning(void); // 0x01029940
extern "C" void*        __cdecl FUN_00b3d230(void);   // 0x00b3d230
extern "C" bool         __cdecl FUN_0102af80(int uId, void* pObj); // 0x0102af80
extern "C" uint32_t     __cdecl FUN_00932e80(const char* s, uint32_t seed, int flag); // 0x00932e80 FNV
extern "C" void         __cdecl FUN_010424c0(void* pDst, const void* pSrc); // 0x010424c0
extern "C" void*        __cdecl FUN_0059aed0(void* pOut, const void* pV, const void* pQ); // 0x0059aed0
extern "C" void*        __cdecl QuaternionFromFacingAndUp(void* pOut, const void* pFacing, const void* pUp); // 0x0069b600
extern "C" float        __cdecl sqrtf(float);         // CRT intrinsic -> fsqrt

// thiscall callees, declared as members of a host class so `this` travels in ecx
class tHost {
public:
    void*  __thiscall FUN_00c71e30();                              // 0x00c71e30
    void*  __thiscall FUN_00a1ad60();                              // 0x00a1ad60 GetPlayerInventory
    int    __thiscall FUN_0102f8d0(void* pA, void* pOut);          // 0x0102f8d0
    void   __thiscall FUN_00c31a00(int n);                         // 0x00c31a00
    float  __thiscall FUN_00c389f0(float f);                       // 0x00c389f0
    float  __thiscall FUN_00c75c30(uint32_t key);                  // 0x00c75c30
    float  __thiscall FUN_01005c60(int n);                         // 0x01005c60
    float  __thiscall FUN_0104be30();                              // 0x0104be30
    float  __thiscall FUN_00ce6930();                              // 0x00ce6930
    float* __thiscall FUN_0041ea70();                              // 0x0041ea70 Property::GetFloat
    void*  __thiscall FUN_005c65e0();                              // 0x005c65e0 cCivData::GetCities
    void*  __thiscall FUN_00f67d90();                              // 0x00f67d90 GetCurrentTerrainSphere
    void   __thiscall FUN_00c77bf0(uint32_t key);                  // 0x00c77bf0
    void   __thiscall FUN_00c3c190(void* pPlanet);                 // 0x00c3c190 SetDestination
    void   __thiscall FUN_00bc3130();                              // 0x00bc3130 cSPTimer::Restart
    void   __thiscall FUN_00bc3170();                              // 0x00bc3170
    void   __thiscall FUN_00b5cde0(uint32_t key);                  // 0x00b5cde0
    void   __thiscall FUN_01017000();                              // 0x01017000
    void   __thiscall FUN_010170e0();                              // 0x010170e0
    void*  __thiscall FUN_00bce5c0();                              // 0x00bce5c0
    void   __thiscall FUN_00ffc350(const float* pV, int a, int b, int c, int d); // 0x00ffc350
    void   __thiscall FUN_00ffc6d0();                              // 0x00ffc6d0
    float  __thiscall FUN_00ffc7f0(void* pCities);                 // 0x00ffc7f0
    void   __thiscall FUN_00434040();                              // 0x00434040 XformMsg::XformMsg
    void   __thiscall FUN_0041cb40(const void* pSrc);              // 0x0041cb40 Matrix3::Assign
};

// ---------------------------------------------------------------------------------------------
// data globals (retail addresses in comments)
// ---------------------------------------------------------------------------------------------
extern const float kRealOne;         // 0x01485720 1.0f
extern const float kRealZero;        // 0x01485378 0.0f
extern const float kFallbackDist;    // 0x01488874 0.1f
extern const float kDirEps;          // 0x014950e4
extern const float kNormEps;         // 0x013ec4b8
extern const float kFive;            // 0x01486110
extern const float kThousand;        // 0x013ec5b4
extern const float kHundred;         // 0x013ec4d0

extern const float kRefMatrix[9];    // 0x016dc018 Matrix3 source
extern const float kMsgX;            // 0x016dc03c
extern const float kMsgY;            // 0x016dc040
extern const float kMsgZ;            // 0x016dc044
extern const float kFwdX;            // 0x016dc0c8
extern const float kFwdY;            // 0x016dc0cc
extern const float kFwdZ;            // 0x016dc0d0
extern const float kBaseX;           // 0x016dba18
extern const float kBaseY;           // 0x016dba1c
extern const float kBaseZ;           // 0x016dba20

extern uint32_t kInterplanetaryDrive; // 0x016dba90 interplanetary-drive tool key
extern uint32_t kHealthUpgrade10;  // 0x016dbebc
extern uint32_t kHealthUpgrade9;   // 0x016dbeb0
extern uint32_t kHealthUpgrade8;   // 0x016dbea4
extern uint32_t kHealthUpgrade7;   // 0x016dbe98
extern uint32_t kHealthUpgrade6;   // 0x016dbe8c
extern uint32_t kHealthUpgrade5;   // 0x016dbe80
extern uint32_t kHealthUpgrade4;   // 0x016dbe74
extern uint32_t kHealthUpgrade3;   // 0x016dbe68
extern uint32_t kHealthUpgrade2;   // 0x016dbe5c
extern uint32_t kHealthUpgrade1;   // 0x016dbe50
extern uint32_t kEnergyUpgrade10;  // 0x016dbe14
extern uint32_t kEnergyUpgrade9;   // 0x016dbe08
extern uint32_t kEnergyUpgrade8;   // 0x016dbdfc
extern uint32_t kEnergyUpgrade7;   // 0x016dbdf0
extern uint32_t kEnergyUpgrade6;   // 0x016dbde4
extern uint32_t kEnergyUpgrade5;   // 0x016dbdd8
extern uint32_t kEnergyUpgrade4;   // 0x016dbdcc
extern uint32_t kEnergyUpgrade3;   // 0x016dbdc0
extern uint32_t kEnergyUpgrade2;   // 0x016dbdb4
extern uint32_t kEnergyUpgrade1;   // 0x016dbda8

extern char g_szReticleGotoScreen[]; // 0x01495114 "UI_common_reticle_goto_screen"

// ---------------------------------------------------------------------------------------------
// types
// ---------------------------------------------------------------------------------------------
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))

// The UFO's cached simulation data (retail layout != PDB layout).
class cSPGameDataUFO {
public:
    uint8_t mPad000[0x5ec];   // +0x000
    float   mf5ec;            // +0x5ec
    uint8_t mPad5f0[0x04];    // +0x5f0
    float   mf5f4;            // +0x5f4 facing x
    float   mf5f8;            // +0x5f8 facing y
    float   mf5fc;            // +0x5fc facing z
    uint8_t mPad600[0x04];    // +0x600
    float   mf604;            // +0x604
    uint8_t mPad608[0x04];    // +0x608
    float   mf60c;            // +0x60c
    float   mf610;            // +0x610
    float   mf614;            // +0x614
    uint8_t mPad618[0x30];    // +0x618
    uint8_t mTimer648[0x1c];  // +0x648 cSPTimer
    uint8_t mPad664[0x04];    // +0x664
    uint8_t mTimer668[0x1c];  // +0x668 cSPTimer
    uint8_t mPad684[0xac];    // +0x684
    float   mf730[4];         // +0x730 quaternion
    uint8_t mPad740[0x08];    // +0x740
};

// The "planet" object the UFO destination handle points at.
class tPlanet {
public:
    uint8_t mPad00[0x748];    // +0x000
    float   mf748;            // +0x748
    int32_t mn74c;            // +0x74c empire id
};

// A line/xform message posted to an effect handle (Matrix3 trailing payload).
struct tXformMsg {
    uint16_t mFlags;   // +0x00
    uint16_t mCount;   // +0x02
    float    mf04;     // +0x04
    float    mf08;     // +0x08
    float    mf0c;     // +0x0c
    float    mf10;     // +0x10
    uint8_t  mMat[0x24]; // +0x14 Matrix3 (9 floats)
};

class cSPSimulatorPlayerUFO {
public:
    void*   mpVtable;         // +0x00
    uint8_t mPad04[0x18];     // +0x04
    void*   mpPlanetRecord;   // +0x1c
    uint8_t mPad20[0x20];     // +0x20
    void*   mpGameDataUFO;    // +0x40
    uint8_t mPad44[0x04];     // +0x44
    float   mf48;             // +0x48
    float   mf4c;             // +0x4c
    uint8_t mPad50[0x08];     // +0x50
    void*   mpHitSphereBegin; // +0x58
    void*   mpHitSphereEnd;   // +0x5c
    uint8_t mPad60[0x48];     // +0x60
    void*   mpEffectA;        // +0xa8
    void*   mpEffectB;        // +0xac
    uint8_t mPadB0[0x08];     // +0xb0
    float   mfb8;             // +0xb8
    float   mfbc;             // +0xbc
    float   mfc0;             // +0xc0
    float   mfc4;             // +0xc4
    float   mfc8;             // +0xc8
    uint8_t mPadCc[0x08];     // +0xcc
    void*   mpD4;             // +0xd4
    void*   mpD8;             // +0xd8
    void*   mpDc;             // +0xdc

    float __thiscall FUN_00ffd220(int nId);
    void  __thiscall FUN_00ffd280();
    void  __thiscall InitForPlanet();
    void  __thiscall FUN_00ffd710(int nUid, void* pObj);
    void  __thiscall FUN_00ffd830(void* pPlanet);
    float __thiscall CalculateMaxHealth();
    float __thiscall CalculateMaxEnergy();
    bool  __thiscall FUN_00ffdbb0();
    void  __thiscall FlyToPlanet(void* pPlanet);
    void  __thiscall FUN_00ffdde0(int nKind, float fX, float fY, float fZ);
};

// ---------------------------------------------------------------------------------------------
// helper: fetch the item from a cSimInventory-like object by key (vtable +0x68)
// ---------------------------------------------------------------------------------------------
static void* InventoryFind(void* pInv, const uint32_t* pKey)
{
    return ((void*(__thiscall*)(void*, const uint32_t*))VFN(pInv, 0x68))(pInv, pKey);
}

// ---------------------------------------------------------------------------------------------
// 0x00ffd220: look up the hit-sphere entry with the given id, else a 0.1 default
// ---------------------------------------------------------------------------------------------
// @ 0x00ffd220
float __thiscall cSPSimulatorPlayerUFO::FUN_00ffd220(int nId)
{
    void** pIt = (void**)mpHitSphereBegin;
    while (pIt != (void**)mpHitSphereEnd) {
        char* pEntry = (char*)*pIt;
        if (*(void**)(pEntry + 0x64) != 0) {
            void* pObj = *(void**)(pEntry + 0x64);
            if (pObj != 0) {
                int nFound = ((int(__thiscall*)(void*, uint32_t))VFN(pObj, 0x0c))(pObj, 0x3e4353b);
                if (nFound != 0) {
                    if (nFound == nId)
                        return *(float*)(pEntry + 0x18);
                    ++pIt;
                    continue;
                }
            }
        }
        ++pIt;
    }
    return kFallbackDist;
}

// ---------------------------------------------------------------------------------------------
// 0x00ffd280: refresh the planet-target timer
// ---------------------------------------------------------------------------------------------
// @ 0x00ffd280
void __thiscall cSPSimulatorPlayerUFO::FUN_00ffd280()
{
    void* pObj = ((tHost*)((tHost*)FUN_01021260())->FUN_00c71e30());
    float fLocal = 0.0f;
    int nId = ((tHost*)FUN_0102f810())->FUN_0102f8d0(pObj, &fLocal);
    if (fLocal > kRealZero) {
        ((tHost*)FUN_01021300())->FUN_00c31a00(-nId);
        ((tHost*)mpGameDataUFO)->FUN_00c389f0(fLocal);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ffd390: cSPSimulatorPlayerUFO::InitForPlanet
// ---------------------------------------------------------------------------------------------
// @ 0x00ffd390
void __thiscall cSPSimulatorPlayerUFO::InitForPlanet()
{
    float vUp[3];
    float vPos[3];
    float vConj[4];
    float vRes[3];
    float vFacing[3];
    float vQuat[4];

    vUp[0] = kRealOne;
    vUp[1] = kRealOne;
    vUp[2] = 0.0f;

    tHost* pApp = (tHost*)App();
    tHost* pA = (tHost*)((void*(__thiscall*)(void*))VFN(pApp, 0x50))(pApp);
    void* pB = ((void*(__thiscall*)(void*))VFN(pA, 0x38))(pA);
    if (pB != 0) {
        void* pC = ((void*(__thiscall*)(void*, uint32_t))VFN(pB, 0x0c))(pB, 0x303154cc);
        if (pC != 0) {
            FUN_010424c0(vPos, (char*)pC + 0x68);

            void* pPlanet = FUN_01021260();
            void* pQuat = ((void*(__thiscall*)(void*))VFN(pPlanet, 0x30))(pPlanet);
            float q0 = *(float*)((char*)pQuat + 0x00);
            float q1 = *(float*)((char*)pQuat + 0x04);
            float q2 = *(float*)((char*)pQuat + 0x08);
            float q3 = *(float*)((char*)pQuat + 0x0c);
            float fInv = kRealOne / (q3 * q3 + q2 * q2 + q1 * q1 + q0 * q0);
            vConj[3] = q3 * fInv;
            vConj[1] = -(q1 * fInv);
            vConj[2] = -(q2 * fInv);
            vConj[0] = -(q0 * fInv);
            FUN_0059aed0(vRes, vPos, vConj);
            if (sqrtf(vRes[0] * vRes[0] + vRes[1] * vRes[1] + vRes[2] * vRes[2]) > kDirEps) {
                vUp[0] = vRes[0];
                vUp[1] = vRes[1];
                vUp[2] = vRes[2];
            }
        }
    }

    float fNorm = kRealOne / sqrtf(vUp[0] * vUp[0] + vUp[1] * vUp[1] + vUp[2] * vUp[2] + kNormEps);
    vUp[0] = fNorm * vUp[0];
    vUp[1] = vUp[1] * fNorm;
    vUp[2] = vUp[2] * fNorm;

    ((tHost*)this)->FUN_00ffc350(vUp, 0, 1, 0, 0);

    float f0 = vUp[2] * kFwdY - vUp[1] * kFwdZ;
    float f1 = kFwdZ * vUp[0] - vUp[2] * kFwdX;
    float f2 = vUp[1] * kFwdX - kFwdY * vUp[0];
    vFacing[0] = f2 * vUp[1] - f1 * vUp[2];
    vFacing[1] = vUp[2] * f0 - f2 * vUp[0];
    vFacing[2] = f1 * vUp[0] - vUp[1] * f0;

    QuaternionFromFacingAndUp(vQuat, vFacing, vUp);

    cSPGameDataUFO* pData = (cSPGameDataUFO*)mpGameDataUFO;
    pData->mf730[0] = vQuat[0];
    pData->mf730[1] = vQuat[1];
    pData->mf730[2] = vQuat[2];
    pData->mf730[3] = vQuat[3];
    pData->mf5f4 = vFacing[0];
    pData->mf5f8 = vFacing[1];
    pData->mf5fc = vFacing[2];

    ((tHost*)&pData->mTimer648)->FUN_00bc3130();
    pData->mf604 = 0.0f;
    pData->mf5ec = 0.0f;
    ((tHost*)&pData->mTimer668)->FUN_00bc3170();
    pData->mf60c = kBaseX;
    pData->mf610 = kBaseY;
    pData->mf614 = kBaseZ;

    ((tHost*)FUN_00b3d230())->FUN_00b5cde0(0x1103193);

    tHost* pApp2 = (tHost*)App();
    tHost* pA2 = (tHost*)((void*(__thiscall*)(void*))VFN(pApp2, 0x50))(pApp2);
    void* pB2 = ((void*(__thiscall*)(void*))VFN(pA2, 0x38))(pA2);
    if (pB2 != 0) {
        void* pC2 = ((void*(__thiscall*)(void*, uint32_t))VFN(pB2, 0x0c))(pB2, 0x303154cd);
        if (pC2 != 0)
            ((tHost*)pC2)->FUN_010170e0();
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ffd710: swap the sim-object handle pair (ref-counted)
// ---------------------------------------------------------------------------------------------
// @ 0x00ffd710
void __thiscall cSPSimulatorPlayerUFO::FUN_00ffd710(int nUid, void* pObj)
{
    if (mpD4 != 0) {
        void* pA = ((void*(__thiscall*)(void*))VFN(mpD4, 0x08))(mpD4);
        ((void(__thiscall*)(void*, int))VFN(pA, 0x54))(pA, 0);
    }

    if (pObj == 0)
        goto lbReleaseD8;
    {
        void* pA = ((void*(__thiscall*)(void*))VFN(pObj, 0x08))(pObj);
        ((void(__thiscall*)(void*, int))VFN(pA, 0x54))(pA, 1);
        void* pKey = ((void*(__thiscall*)(void*))VFN(pObj, 0x0c))(pObj);
        if (!FUN_0102af80(nUid, pKey))
            goto lbReleaseD8;
        void* pOld = mpD8;
        if (pObj == pOld)
            goto lbD4;
        ((void(__thiscall*)(void*))VFN(pObj, 0x60))(pObj);
        mpD8 = pObj;
        if (pOld == 0)
            goto lbD4;
        ((void(__thiscall*)(void*))VFN(pOld, 0x64))(pOld);
    }
    goto lbD4;

lbReleaseD8:
    {
        void* pOld = mpD8;
        if (pOld != 0) {
            mpD8 = 0;
            ((void(__thiscall*)(void*))VFN(pOld, 0x64))(pOld);
        }
    }

lbD4:
    {
        void* pOld = mpD4;
        if (pObj != pOld) {
            if (pObj != 0)
                ((void(__thiscall*)(void*))VFN(pObj, 0x60))(pObj);
            mpD4 = pObj;
            if (pOld != 0)
                ((void(__thiscall*)(void*))VFN(pOld, 0x64))(pOld);
        }
    }

    if (mpD4 != 0 && mpDc != 0) {
        if (mpD4 != 0) {
            void* pO = ((void*(__thiscall*)(void*, uint32_t))VFN(mpD4, 0x5c))(mpD4, 0x436f315);
            if (pO != 0 && ((tHost*)pO)->FUN_00bce5c0() == mpDc)
                return;
        }
        void* pHold = mpDc;
        if (pHold != 0) {
            mpDc = 0;
            ((void(__thiscall*)(void*))VFN(pHold, 0x04))(pHold);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ffd830: set/adopt the destination planet (ref-counted)
// ---------------------------------------------------------------------------------------------
// @ 0x00ffd830
void __thiscall cSPSimulatorPlayerUFO::FUN_00ffd830(void* pPlanet)
{
    tPlanet* pNew = (tPlanet*)pPlanet;

    if (pNew != 0) {
        cSPGameDataUFO* pData = (cSPGameDataUFO*)mpGameDataUFO;
        int32_t nEmpire = ((int32_t(__thiscall*)(void*))VFN(pData, 0x4c))(pData);
        if (pNew->mn74c == nEmpire && pNew->mf748 >= kHundred)
            return;
    }

    void* pOld = mpDc;
    if (pNew != pOld) {
        if (pNew != 0)
            ((void(__thiscall*)(void*))VFN(pNew, 0x00))(pNew);
        mpDc = pNew;
        if (pOld != 0)
            ((void(__thiscall*)(void*))VFN(pOld, 0x04))(pOld);
    }

    if (mpD4 != 0 && mpDc != 0) {
        if (mpD4 != 0) {
            void* pO = ((void*(__thiscall*)(void*, uint32_t))VFN(mpD4, 0x5c))(mpD4, 0x436f315);
            if (pO != 0 && ((tHost*)pO)->FUN_00bce5c0() == mpDc)
                return;
        }
        FUN_00ffd710(0, 0);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ffd8e0: cSPSimulatorPlayerUFO::CalculateMaxHealth
// ---------------------------------------------------------------------------------------------
// @ 0x00ffd8e0
float __thiscall cSPSimulatorPlayerUFO::CalculateMaxHealth()
{
    float fScale = kRealOne;
    float fBonus;

    void* pInv = ((tHost*)SpaceGameGet())->FUN_00a1ad60();
    if (pInv != 0) {
        void* pItem = InventoryFind(pInv, &kHealthUpgrade10);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade9);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade8);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade7);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade6);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade5);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade4);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade3);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade2);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade1);
        if (pItem != 0) {
            char* pSub = (char*)pItem + 0x0c;
            void* pRes = ((void*(__thiscall*)(void*, uint32_t))VFN(pSub, 0x0c))(pSub, 0x707459f0);
            fScale = ((tHost*)pRes)->FUN_0104be30();
        }
    }

    if ((*(uint8_t*)((char*)SpaceGameGet() + 0xc4) & 8) != 0) {
        fScale = ((tHost*)SpaceGameGet())->FUN_01005c60(3) * fScale;
    }

    float fRate = ((tHost*)((tHost*)NounManager())->FUN_00f67d90())->FUN_00c75c30(0xc045ed0d);
    fScale = fRate * fScale;
    fBonus = kThousand;

    void* pTun = GetSpaceCombatTuning();
    void* pSpace = *(void**)((char*)pTun + 0x08);
    if (pSpace != 0) {
        void* pProp;
        if (((bool(__thiscall*)(void*, uint32_t, void**))VFN(pSpace, 0x24))(pSpace, 0x2fa794e, &pProp)) {
            if (*(uint16_t*)((char*)pProp + 0x12) == 0x0d) {
                fBonus = *((tHost*)pProp)->FUN_0041ea70();
            }
        }
    }
    return fBonus * fScale;
}

// ---------------------------------------------------------------------------------------------
// 0x00ffda80: cSPSimulatorPlayerUFO::CalculateMaxEnergy
// ---------------------------------------------------------------------------------------------
// @ 0x00ffda80
float __thiscall cSPSimulatorPlayerUFO::CalculateMaxEnergy()
{
    float fScale = kRealOne;

    void* pInv = ((tHost*)SpaceGameGet())->FUN_00a1ad60();
    if (pInv != 0) {
        void* pItem = InventoryFind(pInv, &kEnergyUpgrade10);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade9);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade8);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade7);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade6);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade5);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade4);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade3);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade2);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade1);
        if (pItem != 0) {
            char* pSub = (char*)pItem + 0x0c;
            void* pRes = ((void*(__thiscall*)(void*, uint32_t))VFN(pSub, 0x0c))(pSub, 0x707459f0);
            fScale = ((tHost*)pRes)->FUN_0104be30();
        }
    }

    uint8_t* pFlags = (uint8_t*)SpaceGameGet() + 0xc4;
    if ((*pFlags & 1) != 0) {
        float fAdd = ((tHost*)SpaceGameGet())->FUN_01005c60(0);
        return (fAdd * fScale) * kHundred;
    }
    return fScale * kHundred;
}

// ---------------------------------------------------------------------------------------------
// 0x00ffdbb0: is the planet's stored energy below the UFO's energy?
// ---------------------------------------------------------------------------------------------
// @ 0x00ffdbb0
bool __thiscall cSPSimulatorPlayerUFO::FUN_00ffdbb0()
{
    if (mpPlanetRecord != 0)
        goto haveRecord;
    ((tHost*)this)->FUN_00ffc6d0();
    if (mpPlanetRecord != 0)
        goto haveRecord;
    mf48 = 0.0f;
    mf4c = kFive;
    return false;
haveRecord:
    {
        void* pCities = ((tHost*)FUN_01021240())->FUN_005c65e0();
        mf48 = ((tHost*)this)->FUN_00ffc7f0(pCities);
        mf4c = ((tHost*)mpPlanetRecord)->FUN_00ce6930();
        float fMax = ((tHost*)mpPlanetRecord)->FUN_0104be30();
        return mf48 < fMax;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ffdc20: cSPSimulatorPlayerUFO::FlyToPlanet
// ---------------------------------------------------------------------------------------------
// @ 0x00ffdc20
void __thiscall cSPSimulatorPlayerUFO::FlyToPlanet(void* pPlanet)
{
    void* pInv = ((tHost*)SpaceGameGet())->FUN_00a1ad60();
    if (((bool(__thiscall*)(void*, uint32_t))VFN(pInv, 0x74))(pInv, (uint32_t)&kInterplanetaryDrive)) {
        cSPGameDataUFO* pData = (cSPGameDataUFO*)mpGameDataUFO;
        ((tHost*)pData)->FUN_00c3c190(pPlanet);
        ((tHost*)&pData->mTimer648)->FUN_00bc3170();
        ((tHost*)((tHost*)NounManager())->FUN_00f67d90())->FUN_00c77bf0(0x56e2b88);

        uint32_t nKey = FUN_00932e80(g_szReticleGotoScreen, 0x811c9dc5, 1);

        tXformMsg msg;
        void* pHandle = 0;
        {
            void* pOld = pHandle;
            if (pOld != 0) {
                pHandle = 0;
                ((void(__thiscall*)(void*))VFN(pOld, 0x04))(pOld);
            }
        }
        void* pEm = EffectsManagerPtr();
        if (((bool(__thiscall*)(void*, uint32_t, int, void**))VFN(pEm, 0x2c))(pEm, nKey, 0, &pHandle)) {
            msg.mf04 = kMsgX;
            msg.mf08 = kMsgY;
            msg.mf0c = kMsgZ;
            msg.mCount = 0;
            msg.mf10 = kRealOne;
            ((tHost*)msg.mMat)->FUN_0041cb40(kRefMatrix);
            msg.mFlags = 0;

            void* pPos = ((void*(__thiscall*)(void*))VFN(pPlanet, 0x2c))(pPlanet);
            msg.mf04 = *(float*)((char*)pPos + 0x00);
            msg.mf08 = *(float*)((char*)pPos + 0x04);
            msg.mf0c = *(float*)((char*)pPos + 0x08);
            msg.mFlags |= 4;
            msg.mCount++;

            ((void(__thiscall*)(void*, tXformMsg*))VFN(pHandle, 0x18))(pHandle, &msg);
            ((void(__thiscall*)(void*, int))VFN(pHandle, 0x08))(pHandle, 0);
        }

        tHost* pApp = (tHost*)App();
        tHost* pA = (tHost*)((void*(__thiscall*)(void*))VFN(pApp, 0x50))(pApp);
        void* pB = ((void*(__thiscall*)(void*, uint32_t))VFN(pA, 0x40))(pA, 0x1103192);
        if (pB != 0) {
            void* pC = ((void*(__thiscall*)(void*, uint32_t))VFN(pB, 0x0c))(pB, 0x303154cc);
            if (pC != 0)
                ((tHost*)pC)->FUN_01017000();
        }

        void* pMsg = MessageServer();
        ((void(__thiscall*)(void*, uint32_t, int, int, int))VFN(pMsg, 0x18))(pMsg, 0x490d429, 0, 0, 0);

        if (pHandle != 0)
            ((void(__thiscall*)(void*))VFN(pHandle, 0x04))(pHandle);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ffdde0: emit the paired effect beams for a warp/jump event
// ---------------------------------------------------------------------------------------------
// @ 0x00ffdde0
void __thiscall cSPSimulatorPlayerUFO::FUN_00ffdde0(int nKind, float fX, float fY, float fZ)
{
    {
        void* pE = mpEffectA;
        if (pE != 0 && ((bool(__thiscall*)(void*))VFN(pE, 0x10))(pE)) {
            void* pE2 = mpEffectA;
            ((void(__thiscall*)(void*, int))VFN(pE2, 0x0c))(pE2, 1);
            if (mpEffectA != 0) {
                mpEffectA = 0;
                ((void(__thiscall*)(void*))VFN(pE2, 0x04))(pE2);
            }
        }
    }
    {
        void* pE = mpEffectB;
        if (pE != 0 && ((bool(__thiscall*)(void*))VFN(pE, 0x10))(pE)) {
            void* pE2 = mpEffectB;
            ((void(__thiscall*)(void*, int))VFN(pE2, 0x0c))(pE2, 1);
            if (mpEffectB != 0) {
                mpEffectB = 0;
                ((void(__thiscall*)(void*))VFN(pE2, 0x04))(pE2);
            }
        }
    }

    uint32_t nKey1;
    uint32_t nKey2;
    switch (nKind) {
    case 4:  nKey1 = 0x03d6ef4d; nKey2 = 0;                  break;
    case 5:  nKey1 = 0x03d6ef59; nKey2 = 0;                  break;
    case 6:  nKey1 = 0x03d6ef67; nKey2 = 0;                  break;
    case 7:  nKey1 = 0x03d6ef59; nKey2 = 0x03d6ef59;         break;
    case 8:  nKey1 = 0x03d6ef59; nKey2 = 0x03d6ef59 - 0x0c;  break;
    case 9:  nKey1 = 0x03d6ef59; nKey2 = 0x03d6ef59 + 0x0e;  break;
    case 10: nKey1 = 0x03d6ef4d; nKey2 = 0x03d6ef4d;         break;
    case 11: nKey1 = 0x03d6ef4d; nKey2 = 0x03d6ef4d + 0x1a;  break;
    case 12: nKey1 = 0x03d6ef67; nKey2 = 0x03d6ef67;         break;
    default: return;
    }

    tXformMsg msgA;
    msgA.mf04 = kMsgX;
    msgA.mf08 = kMsgY;
    msgA.mf0c = kMsgZ;
    msgA.mCount = 0;
    msgA.mf10 = kRealOne;
    ((tHost*)msgA.mMat)->FUN_0041cb40(kRefMatrix);
    msgA.mFlags = 0;
    msgA.mf08 = fX;
    msgA.mFlags |= 4;
    msgA.mCount += 2;
    msgA.mf04 = fY;
    msgA.mf0c = fZ;
    msgA.mf10 = mfb8;

    tHost* pEm = (tHost*)EffectsManagerPtr();
    {
        void* pOld = mpEffectA;
        if (pOld != 0) {
            mpEffectA = 0;
            ((void(__thiscall*)(void*))VFN(pOld, 0x04))(pOld);
        }
    }
    if (((bool(__thiscall*)(void*, uint32_t, int, void**))VFN(pEm, 0x2c))(pEm, nKey1, 0, &mpEffectA)) {
        if (nKey2 != 0) {
            tHost* pEm2 = (tHost*)EffectsManagerPtr();
            {
                void* pOld = mpEffectB;
                if (pOld != 0) {
                    mpEffectB = 0;
                    ((void(__thiscall*)(void*))VFN(pOld, 0x04))(pOld);
                }
            }
            if (((bool(__thiscall*)(void*, uint32_t, int, void**))VFN(pEm2, 0x2c))(pEm2, nKey2, 0, &mpEffectB)) {
                tXformMsg msgB;
                ((tHost*)&msgB)->FUN_00434040();
                msgB.mf04 = fY + mfc0;
                msgB.mf08 = fX + mfc4;
                msgB.mf0c = fZ + mfc8;
                msgB.mf10 = mfbc;
                msgB.mFlags |= 4;
                msgB.mCount += 2;
                ((void(__thiscall*)(void*, tXformMsg*))VFN(mpEffectB, 0x14))(mpEffectB, &msgB);
                ((void(__thiscall*)(void*, int))VFN(mpEffectB, 0x08))(mpEffectB, 0);

                msgA.mFlags |= 4;
                msgA.mCount++;
                msgA.mf04 = fY - mfc0;
                msgA.mf08 = fX - mfc4;
                msgA.mf0c = fZ - mfc8;
            }
        }
        ((void(__thiscall*)(void*, tXformMsg*))VFN(mpEffectA, 0x14))(mpEffectA, &msgA);
        ((void(__thiscall*)(void*, int))VFN(mpEffectA, 0x08))(mpEffectA, 0);
    }
}