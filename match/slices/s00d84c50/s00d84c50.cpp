// Slice s00d84c50: the friendly/idle-tick, epic-bite, stalk-avatar, loudness,
// held-object and alpha-fade creature behaviour callbacks plus their helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------------------------
// float constants (retail addresses in comments)
// ---------------------------------------------------------------------------------------------
extern float g_kZero;       // 0x01485378 _HK_REAL_ZERO 0.0f
extern float g_kOne;        // 0x01485720 _HK_REAL_ONE  1.0f
extern float g_kTwo;        // 0x01470f1c 2.0f
extern float g_kThree;      // 0x013eb95c 3.0f
extern float g_kFive;       // 0x01486110 5.0f
extern float g_kTiny;       // 0x0147c034 1.52587890625e-05f
extern float g_kMax;        // 0x0147c030 FLT_MAX
extern float g_kSign;       // 0x013eb8b0 0x80000000 sign mask
extern float g_kQuarter;    // 0x013eb8a0 0.25f
extern float g_kEps;        // 0x013ec4b8 1e-08f
extern float g_kTwenty;     // 0x013eecd8 20.0f
extern float g_kThirty;     // 0x014853bc 30.0f
extern float g_kZeroV;      // 0x0169f03c
extern float g_kZeroV2;     // 0x0169f040
extern float g_kZeroV3;     // 0x0169f044

// ---------------------------------------------------------------------------------------------
// writable globals
// ---------------------------------------------------------------------------------------------
extern uint32_t g_1590c3c;  // 0x01590c3c animation event key handed to WaitForAnimEventOrEnd

// ---------------------------------------------------------------------------------------------
// engines / free helpers
// ---------------------------------------------------------------------------------------------
void* __cdecl NounManager();                                    // 0x00b3d300
void* __cdecl FUN_00d51660();                                   // 0x00d51660
void* __cdecl FUN_00d99470(void* pObject);                      // 0x00d99470
void* __cdecl FUN_00d998f0(void* pObject);                      // 0x00d998f0
int32_t __fastcall FUN_008e7f80(void* pCombatant);               // 0x008e7f80 damage state
float __cdecl FUN_00d38a30(int32_t nIndex, void* pCreature);    // 0x00d38a30
float __cdecl RandomFloatRange(float fA, float fB);             // 0x00572a10
// the stimuli set hanging off the behaviour tree at +0x08
class behavior_stimuli {
public:
    uint32_t mPad00;                                                    // +0x00
    void FUN_00bc97f0(int32_t nA, int32_t nB, float fC, int32_t nD);   // 0x00bc97f0
    void ClearAll(int32_t nFlags, int32_t nMask);                       // 0x00bc98f0
};

// the behaviour tree; the stimuli set is its second word block
class cBehaviorTree {
public:
    uint32_t         mPad00[2];         // +0x000
    behavior_stimuli  mStimuli;         // +0x008
    uint8_t          mPad0c[0x1d8 - 0x00c];
    int32_t          mn1d8;             // +0x1d8 interaction state
};

struct Vector3 {
    float x;                    // +0x00
    float y;                    // +0x04
    float z;                    // +0x08
};

// a plain uniform random generator living at a fixed address
class cRandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t nRange);              // 0x00a68fb0
};

extern cRandomLinearCongruential g_mathRandom;                  // 0x01601760

// the loudness stimulus record: rate/cap/current plus its source object
class tLoudnessStim {
public:
    float   mf00;               // +0x00 loudness this tick
    float   mf04;               // +0x04 loudness rate
    float   mf08;               // +0x08 loudness cap
    float   mf0c;               // +0x0c current loudness
    uint8_t mPad10[0x2c];       // +0x10
    void*   mpObj3c;            // +0x3c loudness source object
};

// the held-object / alpha-fade stimulus record
class tHeldStim {
public:
    float   mf00;               // +0x00 remaining alpha
    uint8_t mPad04[0x3c];       // +0x04
    void*   mpObj40;            // +0x40 held object
};

// the component id the stimuli look the creature up by
static const uint32_t kCreatureClassId = 0xd0036e08u;

// the component lookup the hold/loudness stimuli share: null in, null out
static inline void* GetComponent(void* pObj)
{
    if (pObj == 0)
        return 0;
    return ((void* (__thiscall*)(void*, uint32_t))((*(void***)pObj)[0x0c / 4]))(
        pObj, kCreatureClassId);
}

// ---------------------------------------------------------------------------------------------
// the spatial sub-object at +0x0c0
// ---------------------------------------------------------------------------------------------
class cSpatialObject {
public:
    virtual void*     v00();            // +0x00
    virtual void*     v04();            // +0x04
    virtual void*     v08();            // +0x08
    virtual void*     v0c();            // +0x0c
    virtual void*     v10();            // +0x10
    virtual void*     v14();            // +0x14
    virtual void*     v18();            // +0x18
    virtual void*     v1c();            // +0x1c
    virtual void*     v20();            // +0x20
    virtual void*     v24();            // +0x24
    virtual void*     v28();            // +0x28
    virtual Vector3*  v2c();            // +0x2c position
    virtual void*     v30();            // +0x30
    virtual void*     v34();            // +0x34
    virtual void*     v38();            // +0x38
    virtual void*     v3c();            // +0x3c
    virtual void*     v40();            // +0x40
    virtual void*     v44();            // +0x44
    virtual bool      v48();            // +0x48
    virtual void*     v4c();            // +0x4c
    virtual void*     v50();            // +0x50
    virtual void*     v54();            // +0x54
    virtual void*     v58();            // +0x58
    virtual Vector3*  v5c(Vector3* pOut);// +0x5c orientation
    virtual void*     v60();            // +0x60
    virtual void*     v64();            // +0x64
    virtual void*     v68();            // +0x68
    virtual void*     v6c();            // +0x6c
    virtual void*     v70();            // +0x70
    virtual float     v74();            // +0x74 radius
    virtual void*     v78();            // +0x78
    virtual void*     v7c();            // +0x7c
    virtual void*     v80();            // +0x80
    virtual void*     v84();            // +0x84
    virtual void*     v88();            // +0x88
    virtual void*     v8c();            // +0x8c
    virtual void*     v90();            // +0x90
    virtual void*     v94();            // +0x94
    virtual void*     v98();            // +0x98
    virtual void*     v9c();            // +0x9c
    virtual void*     va0();            // +0xa0
    virtual void*     va4();            // +0xa4
    virtual void*     va8();            // +0xa8
    virtual void*     vac();            // +0xac
    virtual void*     vb0();            // +0xb0
    virtual void*     vb4();            // +0xb4
    virtual void*     vb8();            // +0xb8
    virtual void*     vbc();            // +0xbc
    virtual void*     vc0();            // +0xc0
    virtual void*     vc4();            // +0xc4
    virtual void*     vc8();            // +0xc8
    virtual void*     vcc();            // +0xcc
    virtual void*     vd0();            // +0xd0
    virtual void*     vd4();            // +0xd4
    virtual void*     vd8();            // +0xd8
    virtual void*     vdc();            // +0xdc
    virtual void*     ve0();            // +0xe0
    virtual void*     ve4();            // +0xe4
    virtual void*     ve8();            // +0xe8
    virtual void      vec();            // +0xec
    virtual void*     vf0();            // +0xf0
    virtual void*     vf4();            // +0xf4
    virtual bool      vf8();            // +0xf8
};

// the combat sub-object at +0x5a8
struct cCombatant {
    uint32_t mVtable;                   // +0x00
};

// a plain object carrying a virtual at +0x2c (the offset those joined objects share)
class cSpatialHolder {
public:
    virtual void*    v00();  virtual void* v04();  virtual void* v08();  virtual void* v0c();
    virtual void*    v10();  virtual void* v14();  virtual void* v18();  virtual void* v1c();
    virtual void*    v20();  virtual void* v24();  virtual void* v28();
    virtual Vector3* v2c();             // +0x2c
};

// the behaviour-context object hung off +0x1698
class cBehaviorObj {
public:
    virtual void*    v00();             // +0x00
    virtual void*    v04();             // +0x04
    virtual void*    v08();             // +0x08
    virtual void*    v0c();             // +0x0c
    virtual int32_t  v10();             // +0x10
};

// the property value a "GetValue" lookup hands back
class cProperty {
public:
    uint8_t  mPad00[0x12];              // +0x00
    uint16_t mnType;                    // +0x12
    float*   GetFloat();                // 0x0041ea70
};

// the property holder hanging off an object at +0x130
class cPropertyHolder {
public:
    virtual void* v00();  virtual void* v04();  virtual void* v08();  virtual void* v0c();
    virtual void* v10();  virtual void* v14();  virtual void* v18();  virtual void* v1c();
    virtual void* v20();                // +0x20
    virtual bool  GetValue(uint32_t nKey, void** ppOut);   // +0x24
};

class cGameNounManager {
public:
    void* GetAvatar();                  // 0x00b1fdb0
    void* FUN_00b25f40(uint32_t nId);   // 0x00b25f40
};

class cPlanetModel {
public:
    void FUN_00b81630();                // 0x00b81630
};

cPlanetModel* __cdecl PlanetModel(Vector3* pOut, Vector3* pIn); // 0x00b3d350

class cAgentOrderManager {
public:
    void Activate(int32_t nA, int32_t nB, void* pSim, float fVal,
                  void* pVec, void* pObj);          // 0x00bca810
};

class cNearNoun {
public:
    uint8_t mPad00[0x160];              // +0x00
    void*   mpSubObj160;                // +0x160
};

cNearNoun* __fastcall FUN_00c04590(void* pThis);    // 0x00c04590

// ---------------------------------------------------------------------------------------------
// the creature base: the virtual slots this slice calls, then its data
// ---------------------------------------------------------------------------------------------
class cSPCreatureBase {
public:
    virtual void*   v00();  virtual void* v04();  virtual void* v08();  virtual void* v0c();
    virtual void*   v10();  virtual void* v14();  virtual void* v18();  virtual void* v1c();
    virtual void*   v20();  virtual void* v24();  virtual void* v28();  virtual void* v2c();
    virtual void*   v30();  virtual void* v34();  virtual void* v38();  virtual void* v3c();
    virtual void*   v40();  virtual void* v44();
    virtual void    v48(void* pArg);                            // +0x048
    virtual void*   v4c();  virtual void* v50();  virtual void* v54();  virtual void* v58();
    virtual void*   v5c();  virtual void* v60();  virtual void* v64();  virtual void* v68();
    virtual void*   v6c();  virtual void* v70();  virtual void* v74();  virtual void* v78();
    virtual void*   v7c();  virtual void* v80();
    virtual void    v84(void* pArg, int32_t nA, int32_t nB);    // +0x084
    virtual void*   v88();
    virtual void    v8c();                                      // +0x08c
    virtual void*   v90();  virtual void* v94();  virtual void* v98();  virtual void* v9c();
    virtual void*   va0();  virtual void* va4();  virtual void* va8();  virtual void* vac();
    virtual void*   vb0();
    virtual int32_t vb4(int32_t nIdx);                          // +0x0b4
    virtual void*   vb8();
    virtual void*   vbc();
    virtual bool    vc0(void* pTarget, float fA, float fB);     // +0x0c0
    virtual void*   vc4();
    virtual void    vc8(int32_t nFlag);                         // +0x0c8
    virtual void*   vcc();  virtual void* vd0();  virtual void* vd4();  virtual void* vd8();
    virtual void*   vdc();  virtual void* ve0();
    virtual void    ve4(void* pArg);                            // +0x0e4
    virtual void*   ve8();  virtual void* vec();  virtual void* vf0();  virtual void* vf4();
    virtual void*   vf8();  virtual void* vfc();  virtual void* v100(); virtual void* v104();

    uint8_t        mPad004[0x0c0 - 0x004];  // +0x004
    cSpatialObject mLoco;                   // +0x0c0 spatial/placement sub-object
    uint8_t        mPad0c4[0x130 - 0x0c4];  // +0x0c4
    void*          mpPropHolder130;         // +0x130 property holder
    uint8_t        mPad134[0x5a8 - 0x134];  // +0x134
    cCombatant     mCombatant;              // +0x5a8
    uint8_t        mPad5ac[0x5e0 - 0x5ac];  // +0x5ac
    float          mf5e0;                   // +0x5e0 previous health
    uint8_t        mPad5e4[0xb48 - 0x5e4];  // +0x5e4
    void*          mpAgentOrderB48;         // +0xb48 agent order manager
    cBehaviorTree* mpBehaviorTreeB4c;       // +0xb4c behaviour tree (its stimuli set sits at +8)
    uint8_t        mPadb50[0xe40 - 0xb50];  // +0xb50
    void*          mpArrayE40;              // +0xe40 lookup array, stride 36 bytes
    uint8_t        mPade44[0x1000 - 0xe44]; // +0xe44
    float          mf1000;                  // +0x1000 accumulated loudness
    uint8_t        mPad1004[0x1698 - 0x1004];
    void*          mpField1698;             // +0x1698 behaviour context object
    float          mf169c;                  // +0x169c

    void*    FUN_00c04590();                                    // 0x00c04590
    int32_t  FUN_00c0c140();                                    // 0x00c0c140
    uint32_t FUN_00c0f780();   // FindFirstValid                 // 0x00c0f780
    void*    FUN_00c0f8a0(uint32_t nIdx);  // GetAt               // 0x00c0f8a0
    void     FUN_00c0d950(int32_t nFlag);                       // 0x00c0d950
    void     FUN_00c0b370(uint32_t nKey);                       // 0x00c0b370
    void     FUN_00c14750(bool bFlag);                          // 0x00c14750
    void     FUN_00c17350(uint32_t nKey, int32_t nFlag);        // 0x00c17350
    int32_t  PlayAnimation(uint32_t nAnim, int32_t nA, int32_t nB);   // 0x00c12190
    void     PlayAnimationWithTarget(uint32_t nAnim, void* pTarget, int32_t nA,
                                     int32_t nB);               // 0x00c14940
    bool     WaitForAnimEventOrEnd(uint32_t nEvent, int32_t* pnOut, int32_t nA,
                                   int32_t nB, int32_t nC);     // 0x00c14ef0
    bool     AnimationFinished(uint32_t nAnim);                 // 0x00c123f0
    bool     IsAnimFinished(uint32_t nAnim);                    // 0x00c12400
    bool     FUN_00c0d560(void* pTarget, float fA, float fB);   // 0x00c0d560
    bool     FUN_00c0c130();                                    // 0x00c0c130
    void*    GetTargetAsCreature();                             // 0x00c0ee70
    void     MoveToPointAtSpeed(int32_t nMode, Vector3* pPoint, float fA, float fB); // 0x00c1c1d0
    void     MoveToPointAndFacingAtSpeed(int32_t nMode, Vector3* pPoint, Vector3* pDir,
                                         float fA, float fB);  // 0x00c1c5c0
};

// the creature seen through its own "+0x48" one-argument notify slot
class cCreatureNotify {
public:
    virtual void* v00();  virtual void* v04();  virtual void* v08();  virtual void* v0c();
    virtual void* v10();  virtual void* v14();  virtual void* v18();  virtual void* v1c();
    virtual void* v20();  virtual void* v24();  virtual void* v28();  virtual void* v2c();
    virtual void* v30();  virtual void* v34();  virtual void* v38();  virtual void* v3c();
    virtual void* v40();  virtual void* v44();
    virtual void  v48(void* pArg);                              // +0x048
};

// ---------------------------------------------------------------------------------------------
// behaviour contexts
// ---------------------------------------------------------------------------------------------
class tFriendlyCtx {
public:
    float   mf00;               // +0x00 countdown
    int32_t mn04;               // +0x04 current animation id
};

class tEpicCtx {
public:
    int32_t mn00;               // +0x00 fired animation handle
    bool    mb04;               // +0x04 started
    uint8_t mPad05[0x03];       // +0x05
    int32_t mn08;               // +0x08 valid index
};

// ---------------------------------------------------------------------------------------------
// @ 0x00d84c50 SP::FRIENDLY_Tick
// ---------------------------------------------------------------------------------------------
bool __cdecl FRIENDLY_Tick(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                           tFriendlyCtx* pCtx, uint32_t, float fDelta)
{
    float fNear = FUN_00d38a30(1, pCreature);
    float fFar  = FUN_00d38a30(2, pCreature);

    void* pTarget = FUN_00d99470(pCreature->GetTargetAsCreature());
    if (pTarget != 0)
    {
        if (pCreature->FUN_00c0d560(pTarget, fNear, 0.0f) ||
            pCreature->vc0(pTarget, fFar, 0.0f))
        {
            if ((pCtx->mn04 == 0 && pCreature->AnimationFinished(0)) ||
                pCreature->AnimationFinished((uint32_t)pCtx->mn04))
            {
                float fPrev = pCtx->mf00;
                pCtx->mf00 = fPrev - fDelta;
                if (pCtx->mf00 < 0.0f)
                {
                    uint32_t nAnim;
                    do
                    {
                        nAnim = g_mathRandom.RandomUint32Uniform(4) + 0x4001125;
                    }
                    while ((int32_t)nAnim == pCtx->mn04);

                    pCreature->PlayAnimationWithTarget(nAnim,
                        (void*)((char*)pTarget + 0x0c0), -1, -1);
                    pCtx->mf00 = RandomFloatRange(1.0f, g_kTwo);
                    pCtx->mn04 = (int32_t)nAnim;
                }
            }
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d84d70 SP::EPIC_BITE_HELD_CREATURE_Activate
// ---------------------------------------------------------------------------------------------
bool __cdecl EPIC_BITE_HELD_CREATURE_Activate(cSPCreatureBase* pCreature,
                                              uint32_t, uint32_t, uint32_t, uint32_t,
                                              tEpicCtx* pCtx)
{
    uint32_t nIdx = pCreature->FUN_00c0f780();
    pCtx->mn08 = (int32_t)nIdx;

    int32_t nAnim = -1;
    if (nIdx != 0xffffffffu)
        nAnim = *(int32_t*)((char*)pCreature->mpArrayE40 + nIdx * 36);

    pCtx->mn00 = pCreature->PlayAnimation(0x4bc0476, 1, nAnim);
    pCtx->mb04 = false;
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d84dc0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d84dc0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tEpicCtx* pCtx)
{
    bool bResult = !pCreature->IsAnimFinished((uint32_t)pCtx->mn00);

    if (pCtx->mb04)
        return bResult;

    int32_t nEvent = 0;
    if (!pCreature->WaitForAnimEventOrEnd(g_1590c3c, &nEvent, -1, 0, 1))
        return bResult;

    pCtx->mb04 = true;

    void* pObj = pCreature->FUN_00c0f8a0((uint32_t)pCtx->mn08);
    if (pObj == 0)
        return bResult;

    void* pDamage = ((void*(__thiscall*)(void*, uint32_t))(
                        (*(void***)pObj)[0xb8 / 4]))(pObj, 0x13f94d4);
    if (pDamage == 0)
        return bResult;

    void* pSim = (pCreature != 0) ? (void*)((char*)pCreature + 0x5a8) : 0;

    Vector3 vDir;
    pCreature->mLoco.v5c(&vDir);

    Vector3 vNeg;
    vNeg.x = -vDir.x;
    vNeg.y = -vDir.y;
    vNeg.z = -vDir.z;

    float fDamage = ((float(__thiscall*)(void*, int32_t, int32_t, Vector3*, void*))(
                        (*(void***)pDamage)[0x58 / 4]))(pDamage, -1, 2, &vNeg, pSim);
    ((void(__thiscall*)(void*, float))(
        (*(void***)pDamage)[0x18 / 4]))(pDamage, fDamage * g_kQuarter);

    return bResult;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d84ec0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d84ec0(cSPCreatureBase* pCreature)
{
    cBehaviorObj* pBehavior = (cBehaviorObj*)pCreature->mpField1698;
    if (pBehavior == 0)
        return false;

    void* pOther = pBehavior->v08();

    Vector3* pA = pCreature->mLoco.v2c();
    Vector3* pB = ((cSpatialHolder*)pOther)->v2c();

    float fDx = pB->x - pA->x;
    float fDy = pB->y - pA->y;
    float fDz = pB->z - pA->z;

    float fLen = sqrtf(fDx * fDx + fDy * fDy + fDz * fDz + g_kEps);
    float fInv = 1.0f / fLen;

    Vector3 vDir;
    vDir.x = fInv * fDx;
    vDir.y = fInv * fDy;
    vDir.z = fInv * fDz;

    pCreature->MoveToPointAndFacingAtSpeed(2, pCreature->mLoco.v2c(), &vDir, 1.0f, g_kTwo);

    int32_t nIdx = pBehavior->v10();
    pCreature->v48((void*)nIdx);

    void* pObj = ((cGameNounManager*)NounManager())->FUN_00b25f40((uint32_t)nIdx);
    if (pObj != 0)
    {
        pCreature->ve4((void*)((char*)pObj + 0xc4));
        pCreature->FUN_00c0d950(1);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d85000
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d85000(cSPCreatureBase* pCreature)
{
    cBehaviorObj* pBehavior = (cBehaviorObj*)pCreature->mpField1698;
    if (pBehavior == 0)
        return false;

    int32_t nIdx = pBehavior->v10();
    pCreature->v48((void*)nIdx);

    void* pObj = ((cGameNounManager*)NounManager())->FUN_00b25f40((uint32_t)nIdx);
    if (pObj != 0)
    {
        pCreature->ve4((void*)((char*)pObj + 0xc4));
        pCreature->FUN_00c0d950(1);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d85060
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d85060(cSPCreatureBase* pCreature)
{
    if (g_kZero < pCreature->mf169c)
    {
        void* pObj = FUN_00d998f0(pCreature->mpField1698);
        if (pObj != 0)
        {
            if (FUN_008e7f80(pObj) != 2)
                return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d850a0 SP::STALK_AVATAR_Activate
// ---------------------------------------------------------------------------------------------
bool __cdecl STALK_AVATAR_Activate(cSPCreatureBase* pCreature)
{
    cSPCreatureBase* pAvatar = (cSPCreatureBase*)((cGameNounManager*)NounManager())->GetAvatar();

    void* pSim = (pAvatar != 0) ? (void*)((char*)pAvatar + 0x5a8) : 0;
    pCreature->v84(pSim, 1, 0);

    float fReach = pCreature->mLoco.v74();
    float fTotal = pAvatar->mLoco.v74() + fReach + g_kThree;

    Vector3 vOri;
    pAvatar->mLoco.v5c(&vOri);

    Vector3* pPos = pAvatar->mLoco.v2c();
    Vector3 vOut;
    vOut.x = pPos->x + vOri.x * fTotal;
    vOut.y = pPos->y + vOri.y * fTotal;
    vOut.z = pPos->z + vOri.z * fTotal;

    pCreature->MoveToPointAtSpeed(2, &vOut, g_kOne, g_kTwo);
    pCreature->FUN_00c0b370(0x337d8b6b);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d851c0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d851c0(cSPCreatureBase* pCreature)
{
    void* pInfo = FUN_00d51660();
    if (((char*)pInfo)[0x10] == 0)
    {
        pCreature->mpBehaviorTreeB4c->mStimuli.ClearAll(0, 0x80000000);
        return false;
    }

    cSPCreatureBase* pAvatar = (cSPCreatureBase*)((cGameNounManager*)NounManager())->GetAvatar();

    Vector3* pA = pCreature->mLoco.v2c();
    Vector3* pB = pAvatar->mLoco.v2c();

    float fDx = pB->x - pA->x;
    float fDy = pB->y - pA->y;
    float fDz = pB->z - pA->z;

    float fTotal = pAvatar->mLoco.v74() + pCreature->mLoco.v74() + g_kThree;

    if (fDx * fDx + fDy * fDy + fDz * fDz > fTotal + g_kTwo)
    {
        Vector3 vOri;
        pAvatar->mLoco.v5c(&vOri);

        Vector3* pPos = pAvatar->mLoco.v2c();
        Vector3 vOut;
        vOut.x = pPos->x + vOri.x * fTotal;
        vOut.y = pPos->y + vOri.y * fTotal;
        vOut.z = pPos->z + vOri.z * fTotal;

        pCreature->MoveToPointAtSpeed(2, &vOut, g_kOne, g_kTwo);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d85370 SP::AddLoudness
// ---------------------------------------------------------------------------------------------
bool __cdecl AddLoudness(tLoudnessStim* pStim)
{
    cSPCreatureBase* pComp = (cSPCreatureBase*)GetComponent(pStim->mpObj3c);
    if (pComp != 0)
    {
        pComp->mf1000 = pComp->mf1000 + pStim->mf00;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d853b0 SP::RemoveLoudness
// ---------------------------------------------------------------------------------------------
bool __cdecl RemoveLoudness(tLoudnessStim* pStim)
{
    cSPCreatureBase* pComp = (cSPCreatureBase*)GetComponent(pStim->mpObj3c);
    if (pComp != 0)
    {
        pComp->mf1000 = pComp->mf1000 - (pStim->mf0c + pStim->mf00);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d85400 SP::UpdateLoudness
// ---------------------------------------------------------------------------------------------
bool __cdecl UpdateLoudness(tLoudnessStim* pStim, float fDelta)
{
    cSPCreatureBase* pComp = (cSPCreatureBase*)GetComponent(pStim->mpObj3c);
    if (pComp != 0)
    {
        float fCur = pStim->mf0c;
        float fTmp = pStim->mf04 * fDelta + fCur;
        float fMax = pStim->mf08;
        float* pfVal = (fMax < fTmp) ? &fMax : &fTmp;
        float fVal = *pfVal;
        pStim->mf0c = fVal;
        pComp->mf1000 = pComp->mf1000 + (fVal - fCur);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d85480 SP::AddHeldObject
// ---------------------------------------------------------------------------------------------
bool __cdecl AddHeldObject(tHeldStim* pStim)
{
    if (pStim->mpObj40 != 0)
    {
        cSPCreatureBase* pComp = (cSPCreatureBase*)GetComponent(pStim->mpObj40);

        pComp->mpBehaviorTreeB4c->mStimuli.FUN_00bc97f0(0, 0x4000000, g_kMax, 0);
        pComp->mpBehaviorTreeB4c->mStimuli.ClearAll(0x400000, 0);
        pComp->FUN_00c17350(0x4f26350b, 0);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d854f0 SP::AddAlphaFade
// ---------------------------------------------------------------------------------------------
bool __cdecl AddAlphaFade(tHeldStim* pStim, float fDelta)
{
    cSPCreatureBase* pComp = (cSPCreatureBase*)GetComponent(pStim->mpObj40);
    if (pComp != 0)
    {
        pStim->mf00 = pStim->mf00 - fDelta;
        if (0.0f <= pStim->mf00 || pComp->mpBehaviorTreeB4c->mn1d8 == 0x341bd4be)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d85540
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d85540(cSPCreatureBase* pCreature)
{
    float f0xc96f8475 = g_kFive;
    float f0x59d21726 = g_kOne;
    float f0x5c542ce7 = g_kOne;
    float f0x34bcf3d4 = g_kFive;

    int32_t nIdx = pCreature->FUN_00c0c140();
    if (nIdx != -1)
    {
        cSPCreatureBase* pTool = (cSPCreatureBase*)pCreature->vb4(nIdx);
        if (pTool != 0)
        {
            cPropertyHolder* pHolder = (cPropertyHolder*)pTool->mpPropHolder130;
            if (pHolder != 0)
            {
                void* h;
                if (pHolder->GetValue(0xc96f8475, &h) && ((cProperty*)h)->mnType == 0xd)
                    f0xc96f8475 = *((cProperty*)h)->GetFloat();
                if (pHolder->GetValue(0x59d21726, &h) && ((cProperty*)h)->mnType == 0xd)
                    f0x59d21726 = *((cProperty*)h)->GetFloat();
                if (pHolder->GetValue(0x5c542ce7, &h) && ((cProperty*)h)->mnType == 0xd)
                    f0x5c542ce7 = *((cProperty*)h)->GetFloat();
                if (pHolder->GetValue(0x34bcf3d4, &h) && ((cProperty*)h)->mnType == 0xd)
                    f0x34bcf3d4 = *((cProperty*)h)->GetFloat();
            }
        }
    }

    float vec4[4];
    vec4[0] = f0x59d21726;
    vec4[1] = f0x5c542ce7;
    vec4[2] = f0x34bcf3d4;
    vec4[3] = 0.0f;

    ((cAgentOrderManager*)pCreature->mpAgentOrderB48)->Activate(
        0, 1, (void*)pCreature, f0xc96f8475, (void*)vec4, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d856e0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d856e0(cSPCreatureBase* pCreature)
{
    cSPCreatureBase* pAvatar = (cSPCreatureBase*)((cGameNounManager*)NounManager())->GetAvatar();

    Vector3* pA = pCreature->mLoco.v2c();
    Vector3* pB = pAvatar->mLoco.v2c();

    float fDx = pB->x - pA->x;
    float fDy = pB->y - pA->y;
    float fDz = pB->z - pA->z;

    float fLen = sqrtf(fDx * fDx + fDy * fDy + fDz * fDz);
    Vector3 vDir;
    vDir.x = fDx; vDir.y = fDy; vDir.z = fDz;
    if (fLen > g_kTiny)
    {
        float fInv = g_kOne / fLen;
        vDir.x = fDx * fInv;
        vDir.y = fDy * fInv;
        vDir.z = fDz * fInv;
    }

    if (fLen > g_kThirty && !pCreature->mLoco.v48())
    {
        pCreature->v8c();
        pCreature->vc8(0);
        return true;
    }

    Vector3* pPos = pCreature->mLoco.v2c();
    Vector3 vOut;
    vOut.x = pPos->x - vDir.x * g_kTwenty;
    vOut.y = pPos->y - vDir.y * g_kTwenty;
    vOut.z = pPos->z - vDir.z * g_kTwenty;

    pCreature->MoveToPointAtSpeed(2, &vOut, g_kOne, g_kTwo);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d858a0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d858a0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          float* pOut)
{
    cNearNoun* pNoun = FUN_00c04590(pCreature);
    void* pSub = pNoun->mpSubObj160;                 // +0x160
    cSpatialObject* pNounLoco = (cSpatialObject*)((char*)pSub + 0x34);

    pCreature->FUN_00c14750(!pCreature->mLoco.vf8());

    Vector3* pA = pNounLoco->v2c();
    Vector3* pB = pCreature->mLoco.v2c();

    float fDx = pB->x - pA->x;
    float fDy = pB->y - pA->y;
    float fDz = pB->z - pA->z;

    float fInv = g_kOne / sqrtf(fDx * fDx + fDy * fDy + fDz * fDz + g_kEps);
    Vector3 vDir;
    vDir.x = fInv * fDx;
    vDir.y = fInv * fDy;
    vDir.z = fInv * fDz;

    if (vDir.x == g_kZeroV && vDir.y == g_kZeroV2 && vDir.z == g_kZeroV3)
        pCreature->mLoco.v5c(&vDir);

    float fTotal = pNounLoco->v74() + pCreature->mLoco.v74();

    Vector3* pPos = pNounLoco->v2c();
    Vector3 vOut;
    vOut.x = pPos->x + vDir.x * fTotal;
    vOut.y = pPos->y + vDir.y * fTotal;
    vOut.z = pPos->z + vDir.z * fTotal;

    Vector3 vRand;
    PlanetModel(&vOut, &vRand)->FUN_00b81630();
    pCreature->MoveToPointAtSpeed(2, &vOut, g_kOne, g_kTwo);

    cSPCreatureBase* pAvatar = (cSPCreatureBase*)((cGameNounManager*)NounManager())->GetAvatar();
    void* pSim = (pAvatar != 0) ? (void*)((char*)pAvatar + 0x5a8) : 0;
    pCreature->v84(pSim, 1, 0);

    *pOut = g_kFive;
    return true;
}