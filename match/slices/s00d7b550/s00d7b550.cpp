// Slice s00d7b550: creature behaviour callbacks - the idle/rest/celebrate/greet/confused/roar
// behaviour-tree activations, ticks and deactivations, plus the small table and iterator helpers
// that walk a creature's behaviour context.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// float constants (retail addresses in comments)
// ---------------------------------------------------------------------------------------------
extern float g_kOne;            // 0x01485720 1.0f
extern float g_kOneHalf;        // 0x01485548 1.5f
extern float g_kTwo;            // 0x01470f1c 2.0f
extern float g_kTwoHalf;        // 0x01486114 2.5f
extern float g_kThree;          // 0x013eb95c 3.0f
extern float g_kFive;           // 0x01486110 5.0f
extern float g_kTen;            // 0x01473c70 10.0f
extern float g_kSixty;          // 0x013ebc4c 60.0f
extern float g_kMilli;          // 0x013f9428 0.001f
extern float g_kFourGiga;       // 0x013f4fd0 4294967296.0f
extern float g_kTiny;           // 0x0147c034 1.52587890625e-05f
extern float g_kGreetTimer;     // 0x0147c038 3.66666675f

// ---------------------------------------------------------------------------------------------
// writable globals
// ---------------------------------------------------------------------------------------------
extern float    g_fIdleHold;    // 0x01582e9c idle hold time handed to the behaviour context
extern float    g_fRepairRate;  // 0x01687a24 resting repair multiplier
extern uint32_t g_nGameTime;    // 0x01582e24 game clock, milliseconds

// ---------------------------------------------------------------------------------------------
// engines
// ---------------------------------------------------------------------------------------------
void* __cdecl NounManager();                                    // 0x00b3d300
void* __cdecl GetAnimalFromStimulus(void* pStimulus);           // 0x00d99980
void* __cdecl FUN_00d998d0(void* pStimulus, uint32_t nKey);     // 0x00d998d0
void* __cdecl WatchMemoryBlock(void* pStimulus);                // 0x00d999d0
void* __cdecl FUN_00d99500(void* pObject);                      // 0x00d99500
float __cdecl FUN_00d38a30(int32_t nIndex, void* pCreature);    // 0x00d38a30
void* __stdcall FUN_00d539d0(void* pCreature);                  // 0x00d539d0 (cPosseSimulator::Instance)

struct Vector3 {
    float x;                    // +0x00
    float y;                    // +0x04
    float z;                    // +0x08
};

class cSPCreatureBase;
class cNearNoun;

// a plain uniform random generator living at a fixed address
class cRandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t nRange);              // 0x00a68fb0
};

extern cRandomLinearCongruential g_mathRandom;                  // 0x01601760

// ---------------------------------------------------------------------------------------------
// the spatial sub-object shared by creatures and nouns: one virtual per vtable byte offset
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
    virtual float     v34();            // +0x34
    virtual void*     v38();            // +0x38
    virtual void*     v3c();            // +0x3c
    virtual void*     v40();            // +0x40
    virtual void*     v44();            // +0x44
    virtual void*     v48();            // +0x48
    virtual void*     v4c();            // +0x4c
    virtual void*     v50();            // +0x50
    virtual void*     v54();            // +0x54
    virtual float     v58();            // +0x58
    virtual void*     v5c();            // +0x5c
    virtual void*     v60();            // +0x60
    virtual void*     v64();            // +0x64
    virtual void*     v68();            // +0x68
    virtual void*     v6c();            // +0x6c
    virtual void*     v70();            // +0x70
    virtual float     v74();            // +0x74
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

    bool IsNearGoal();                  // 0x00c42e20
};

// the same spatial object seen through the ranged lookup the confused behaviour uses
class cSpatialObjectRanged {
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
    virtual Vector3*  v2c(float fRadius, float fDistance);  // +0x2c
};

// the combat sub-object at +0x5a8
class cCombatant {
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
    virtual void*     v2c();            // +0x2c
    virtual void*     v30();            // +0x30
    virtual void*     v34();            // +0x34
    virtual void*     v38();            // +0x38
    virtual void*     v3c();            // +0x3c
    virtual void*     v40();            // +0x40
    virtual void*     v44();            // +0x44
    virtual void*     v48();            // +0x48
    virtual void*     v4c();            // +0x4c
    virtual void*     v50();            // +0x50
    virtual void*     v54();            // +0x54
    virtual float     v58();            // +0x58 health

    void PartialRepair(float fAmount);              // 0x00bfd1a0
    void FUN_00bfc430(int32_t nFlag);               // 0x00bfc430
};

// the stimulus record a behaviour-tree behaviour is started from
class tStimulus {
public:
    uint32_t mn00;              // +0x00
    uint32_t mn04;              // +0x04
    float    mf08;              // +0x08 timestamp
    int32_t  mn0c;              // +0x0c animation / interaction id
};

// the stimuli set hanging off the behaviour tree at +0x08
class behavior_stimuli {
public:
    void* Play(uint32_t nFlagsA, uint32_t nFlagsB);             // 0x00bc96a0
    void  ClearAll(uint32_t nFlags, int32_t nMask);             // 0x00bc98f0
};

// the behaviour tree; the stimuli set is its second word block
class cBehaviorTree {
public:
    uint32_t        mPad00[2];          // +0x000
    behavior_stimuli mStimuli;          // +0x008

    void FUN_00bcb430();                // 0x00bcb430
};

class cNearNoun {
public:
    Vector3* GetPosition();             // 0x00c6acc0
};

// a noun with the spatial sub-object at +0x34
class cAnimalNoun {
public:
    uint32_t       mnVtable;            // +0x000
    uint8_t        mPad04[0x30];        // +0x004
    cSpatialObject mSpatial;            // +0x034
};

class cGameNounManager {
public:
    cSPCreatureBase* GetAvatar();       // 0x00b1fdb0
};

class cPlanetModel {
public:
    void MakeRandomWorldPosition(Vector3* pOut, Vector3* pIn);  // 0x00b81780
};

cPlanetModel* __cdecl PlanetModel(Vector3* pOut, Vector3* pIn); // 0x00b3d350

class cCreatureModeStrategy {
public:
    static cCreatureModeStrategy* Instance(int32_t nTag);       // 0x00d38840
    void SignalCreatureEvent();                                // 0x00d3cdc0
};

class cPosseSimulator {
public:
    void RemovePosseSlot();                                     // 0x00d53330
};

// ---------------------------------------------------------------------------------------------
// the creature base: the virtual slots this slice calls, then its data
// ---------------------------------------------------------------------------------------------
class cSPCreatureBase {
public:
    virtual void* v00(); virtual void* v04(); virtual void* v08(); virtual void* v0c();
    virtual void* v10(); virtual void* v14(); virtual void* v18(); virtual void* v1c();
    virtual void* v20(); virtual void* v24(); virtual void* v28(); virtual void* v2c();
    virtual void* v30(); virtual void* v34(); virtual void* v38(); virtual void* v3c();
    virtual void* v40(); virtual void* v44(); virtual void* v48(); virtual void* v4c();
    virtual void* v50(); virtual void* v54(); virtual void* v58(); virtual void* v5c();
    virtual void* v60(); virtual void* v64(); virtual void* v68(); virtual void* v6c();
    virtual void* v70(); virtual void* v74(); virtual void* v78(); virtual void* v7c();
    virtual void* v80();                                        // +0x080
    virtual void  v84(void* pObject, int32_t nA, int32_t nB);   // +0x084
    virtual void* v88(); virtual void* v8c(); virtual void* v90(); virtual void* v94();
    virtual void* v98(); virtual void* v9c(); virtual void* va0(); virtual void* va4();
    virtual void* va8(); virtual void* vac(); virtual void* vb0();
    virtual int32_t vb4(int32_t nAnimation);                    // +0x0b4
    virtual void* vb8(); virtual void* vbc();
    virtual bool  vc0(void* pTarget, float fA, float fB);       // +0x0c0
    virtual void* vc4(); virtual void* vc8(); virtual void* vcc();
    virtual bool  vd0();                                        // +0x0d0
    virtual void* vd4();
    virtual void* vd8();                                        // +0x0d8

    uint8_t        mPad04[0xbc];            // +0x004
    cSpatialObject mLoco;                   // +0x0c0 locomotion
    uint8_t        mPadc4[0x4e4];           // +0x0c4
    cCombatant     mCombatant;              // +0x5a8
    uint8_t        mPad5ac[0x34];           // +0x5ac
    float          mf5e0;                   // +0x5e0 previous health
    uint8_t        mPad5e4[0x53c];          // +0x5e4
    int32_t        mnB20;                   // +0xb20 noun id used to match creatures
    uint8_t        mPadb24[0x28];           // +0xb24
    cBehaviorTree* mpBehaviorTree;          // +0xb4c
    uint8_t        mPadb50[0x08];           // +0xb50
    uint32_t       mnFlags;                 // +0xb58 behaviour flags
    uint8_t        mPadb5c[0x02];           // +0xb5c
    bool           mbB5e;                   // +0xb5e
    uint8_t        mPadb5f[0x2d9];          // +0xb5f
    bool           mbE38;                   // +0xe38
    uint8_t        mPade39[0x17f];          // +0xe39
    bool           mbFB8;                   // +0xfb8 resting
    bool           mbFB9;                   // +0xfb9 greeting
    uint8_t        mPadfba[0x66a];          // +0xfba
    void*          mp1624;                  // +0x1624 animation request queue

    bool     FUN_00c0c130();                                        // 0x00c0c130
    int32_t  CountValid();                                          // 0x00c0f570
    uint32_t FUN_00c0ee60(int32_t nA, int32_t nB);                  // 0x00c0ee60
    void     FUN_00c0cff0(int32_t nObject);                         // 0x00c0cff0
    int32_t  InterruptAnimation(uint32_t nAnim, int32_t nA, int32_t nB); // 0x00c12310
    bool     WaitForAnimEventOrEnd(uint32_t nEvent, int32_t* pnOut, int32_t nA,
                                   int32_t nB, int32_t nC);         // 0x00c14ef0
    void     FUN_00c1d460(uint32_t nKeyA, uint32_t nKeyB);          // 0x00c1d460
    int32_t  PlayAnimation(uint32_t nAnim, int32_t nA, int32_t nB); // 0x00c12190
    void     FUN_00c1d5e0(int32_t nA, uint32_t nKeyA, uint32_t nKeyB); // 0x00c1d5e0
    void     FUN_00c17350(uint32_t nKey, int32_t nFlag);            // 0x00c17350
    void     FUN_00c14750(bool bFlag);                              // 0x00c14750
    void     FUN_00c0ba10();                                        // 0x00c0ba10
    void     FUN_00c0d0c0(uint32_t nMode, int32_t nFlag);           // 0x00c0d0c0
    void     FUN_00c122c0(int32_t nAnim, float fA, float fB);       // 0x00c122c0
    void     MoveToPointAtSpeed(int32_t nMode, Vector3* pPoint, float fA, float fB); // 0x00c1c1d0
    bool     IsAnimFinished(uint32_t nAnim);                        // 0x00c12400
    bool     AnimationFinished(uint32_t nAnim);                     // 0x00c123f0
    bool     FUN_00c0d560(void* pTarget, float fA, float fB);       // 0x00c0d560
    void*    GetTargetAsCreature();                                 // 0x00c0ee70
    cNearNoun* FUN_00c04590(float fRadius, float fDistance);        // 0x00c04590
    void     PlayAnimationWithTarget(uint32_t nAnim, void* pTarget, int32_t nA,
                                     int32_t nB);                   // 0x00c14940
};

// the same creature seen through its single-argument "+0x84" notify slot
class cCreatureNotify {
public:
    virtual void* v00(); virtual void* v04(); virtual void* v08(); virtual void* v0c();
    virtual void* v10(); virtual void* v14(); virtual void* v18(); virtual void* v1c();
    virtual void* v20(); virtual void* v24(); virtual void* v28(); virtual void* v2c();
    virtual void* v30(); virtual void* v34(); virtual void* v38(); virtual void* v3c();
    virtual void* v40(); virtual void* v44(); virtual void* v48(); virtual void* v4c();
    virtual void* v50(); virtual void* v54(); virtual void* v58(); virtual void* v5c();
    virtual void* v60(); virtual void* v64(); virtual void* v68(); virtual void* v6c();
    virtual void* v70(); virtual void* v74(); virtual void* v78(); virtual void* v7c();
    virtual void* v80();                                        // +0x080
    virtual void  v84(void* pArgument);                         // +0x084
};

// the animation request queue behind +0x1624
class cAnimRequests {
public:
    void FUN_00bc9d40(uint32_t nChannel, float fTime, void* pTarget, int32_t nFlag); // 0x00bc9d40
    bool FUN_00bc9a00(uint32_t nChannel);                                            // 0x00bc9a00
};

// the creature iterator the two matching helpers walk
class cCreatureIterator {
public:
    bool             AtBegin() const;       // 0x00bc9b50
    cSPCreatureBase* FUN_00bc9b10();        // 0x00bc9b10
};

// ---------------------------------------------------------------------------------------------
// behaviour contexts
// ---------------------------------------------------------------------------------------------
// the context the idle behaviours carry
class tIdleCtx {
public:
    int32_t mn00;               // +0x00 animation id
    float   mf04;               // +0x04 idle hold time
    bool    mb08;               // +0x08 startled
    bool    mb09;               // +0x09 has valid offspring
    uint8_t mPad0a[0x02];       // +0x0a
    float   mf0c;               // +0x0c idle hold reset
};

// the two-int context the animation state machines carry
class tAnimCtx {
public:
    int32_t mn00;               // +0x00 state
    int32_t mn04;               // +0x04 animation id
    int32_t mn08;               // +0x08
};

// the context the lost-target behaviours carry
class tConfusedCtx {
public:
    float   mf00;               // +0x00 countdown
    Vector3 mPos;               // +0x04 target position
    int32_t mn10;               // +0x10 animation id
};

// the context the greet behaviour carries
class tGreetCtx {
public:
    bool    mb00;               // +0x00
    uint8_t mPad01[0x03];       // +0x01
    float   mf04;               // +0x04
    int32_t mn08;               // +0x08
    Vector3 mPos;               // +0x0c avatar position
    int32_t mn18;               // +0x18
};

// a lookup entry (stride 0x0c) of the shared find table
class tFindEntry {
public:
    uint32_t mn00;              // +0x00
    bool     mb04;              // +0x04 entry holds a name
    uint8_t  mPad05[0x03];      // +0x05
    int32_t  mn08;              // +0x08 key
};

class tFindTable {
public:
    uint8_t     mPad00[0x18];   // +0x000
    uint32_t    mnCount;        // +0x018
    tFindEntry  mEntries[1];    // +0x01c first entry of the trailing array
};

// ---------------------------------------------------------------------------------------------
// @ 0x00d7b550
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7b550(cSPCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x20000, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7b570
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7b570(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tIdleCtx* pCtx)
{
    pCtx->mf04 = g_kFive;

    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x10, 0);
    if (pStim != 0)
    {
        pCtx->mn00 = pStim->mn0c;
        int32_t nStartled = ((pCreature->mnFlags >> 9) & 1) != 0 && !pCreature->FUN_00c0c130();
        pCtx->mb08 = nStartled != 0;
        pCtx->mb09 = nStartled != 0 && pCreature->CountValid() > 0;
        pCtx->mf0c = g_fIdleHold;

        pCreature->mnFlags |= 0x2000;
        pCreature->mCombatant.FUN_00bfc430(1);
        ((cCreatureNotify*)pCreature)->v84((void*)pCreature->FUN_00c0ee60(1, 1));
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7b630
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7b630(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x8000, 0);
    if (pStim != 0)
    {
        int32_t nAnim = pStim->mn0c;
        pCtx->mn00 = nAnim;
        pCtx->mn04 = 0;
        pCtx->mn08 = 0;
        return pCreature->vb4(nAnim) != 0;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7b6a0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7b6a0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x400000, 0);
    if (pStim != 0)
    {
        cSPCreatureBase* pAnimal = (cSPCreatureBase*)GetAnimalFromStimulus(pStim);
        if (pAnimal != 0)
        {
            pCreature->v84(&pAnimal->mCombatant, 1, 0);
            pCtx->mn00 = 0;
            pCtx->mn04 = pCreature->InterruptAnimation(0x35387528, -1, 0);
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7b710
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7b710(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx)
{
    int32_t nEvent;
    switch (pCtx->mn00)
    {
    case 0:
        {
            if (pCreature->WaitForAnimEventOrEnd(0xbfa50b5a, &nEvent, -1, pCtx->mn04, 1))
            {
                pCreature->FUN_00c1d460(0x4f26350b, 0x4f26350b);
                pCreature->mpBehaviorTree->mStimuli.ClearAll(0x400000, 0);
                pCtx->mn04 = pCreature->PlayAnimation(0xb346511c, 1, -1);
                pCtx->mn00 = 1;
            }
        }
        break;
    case 1:
        if (pCreature->IsAnimFinished(pCtx->mn04))
            return false;
        break;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7b7a0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7b7a0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tConfusedCtx*)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x20000, 0);
    cAnimalNoun* pNoun = 0;
    if (pStim != 0 && (pNoun = (cAnimalNoun*)FUN_00d998d0(pStim, 0x1b92b27)) != 0)
    {
        if ((pCreature->mnFlags >> 9) & 1)
        {
            pCreature->MoveToPointAtSpeed(2, pNoun->mSpatial.v2c(), g_kOne, g_kTwo);
        }
        else
        {
            cSPCreatureBase* pAvatar = ((cGameNounManager*)NounManager())->GetAvatar();
            float fReach = pCreature->mLoco.v74();
            if ((pCreature->mnFlags >> 8) & 1)
                fReach = pAvatar->mLoco.v74() + fReach;

            float fRadius = pNoun->mSpatial.v74() + pCreature->mLoco.v74() * g_kTwo;
            Vector3* pPoint = ((cSpatialObjectRanged*)&pNoun->mSpatial)
                                  ->v2c(pNoun->mSpatial.v74(), fRadius);
            Vector3 vSpot;
            PlanetModel(&vSpot, pPoint)->MakeRandomWorldPosition(&vSpot, pPoint);
            pCreature->MoveToPointAtSpeed(2, &vSpot, fReach * g_kOneHalf, fReach * g_kThree);
        }
    }
    else
    {
        float fRadius = pCreature->mLoco.v74();
        pCreature->MoveToPointAtSpeed(
            2, pCreature->FUN_00c04590(fRadius, fRadius * g_kTwo)->GetPosition(),
            fRadius, fRadius * g_kTwo);
    }

    if (pCreature->mLoco.IsNearGoal())
        return false;
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x400, 0);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7b970
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7b970(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t,
                          int32_t nObject, tAnimCtx*)
{
    if (pCreature->mLoco.IsNearGoal())
        return false;

    if (nObject != 0)
        pCreature->FUN_00c0cff0(nObject);

    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x400, 0);
    if (pStim != 0)
    {
        bool bTalked = false;
        tStimulus* pTalk = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x20000, 0);
        if (pTalk != 0)
            bTalked = pTalk->mn0c != 0;

        cSPCreatureBase* pWatcher = (cSPCreatureBase*)WatchMemoryBlock(pStim);
        if (!bTalked && pWatcher != 0 && !pWatcher->mbB5e)
            return false;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7ba00
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7ba00(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx)
{
    pCreature->PlayAnimation(0x261fc45, 1, -1);
    pCtx->mn00 = 0;
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7ba20 SP::REST_Tick
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7ba20(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx, uint32_t, float fRate)
{
    if (pCreature->mbFB8)
        pCreature->mCombatant.PartialRepair(pCreature->mCombatant.v58() * g_fRepairRate * fRate);

    switch (pCtx->mn00)
    {
    case 0:
        if (pCreature->AnimationFinished(0x261fc45))
        {
            if ((pCreature->mnFlags >> 9) & 1)
                cCreatureModeStrategy::Instance(0x135dd8ba)->SignalCreatureEvent();
            pCreature->mbE38 = true;
            pCreature->PlayAnimation(0x261faae, 1, -1);
            pCtx->mn00 = 1;
        }
        break;
    case 1:
        {
            float fPrevious = pCreature->mf5e0;
            pCreature->mbFB8 = true;
            if (pCreature->mCombatant.v58() <= fPrevious)
                return false;
        }
        break;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7baf0 SP::REST_Deactivate
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7baf0(cSPCreatureBase* pCreature)
{
    pCreature->mbE38 = false;
    pCreature->mbFB8 = false;
    pCreature->PlayAnimation(0x261fc47, 1, -1);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bb20
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bb20(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c1d5e0(1, 0x6f623ffa, 0x12007c9a);
    return pCreature->AnimationFinished(0x52314083) ? false : true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bb50
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7bb50(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c17350(0x12007c9a, 0);
    pCreature->v84((void*)0, 0, 0);
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 8);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bb90
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bb90(cSPCreatureBase* pCreature)
{
    if (pCreature->AnimationFinished(0))
    {
        pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x20);
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bbc0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7bbc0(cSPCreatureBase* pCreature)
{
    pCreature->v84((void*)0, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bbe0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bbe0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0, 0x8000000);
    if (pStim != 0)
    {
        cSPCreatureBase* pAnimal = (cSPCreatureBase*)GetAnimalFromStimulus(pStim);
        if (pAnimal != 0)
            pCreature->v84(&pAnimal->mCombatant, 1, 0);

        int32_t nAnim = pStim->mn0c;
        pCtx->mn00 = nAnim;
        pCreature->FUN_00c122c0(nAnim, 2.5f, 1.5f);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bc60
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bc60(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx)
{
    return pCreature->AnimationFinished(pCtx->mn00) ? false : true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bc80
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7bc80(cSPCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x8000000);
    pCreature->v84((void*)0, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bcb0
// ---------------------------------------------------------------------------------------------
int32_t __stdcall FUN_00d7bcb0(tFindTable* pTable, int32_t nKey)
{
    uint32_t nCount = pTable->mnCount;
    for (uint32_t i = 0; i < nCount; ++i)
    {
        tFindEntry* pEntry = &pTable->mEntries[i];
        if (nKey != pEntry->mn08 && pEntry->mb04 && pEntry->mn08 != 0)
            return pEntry->mn08;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bd00
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7bd00(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c0d0c0(6, 0);
    pCreature->mpBehaviorTree->FUN_00bcb430();
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x40000000, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bd40
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bd40(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tGreetCtx* pCtx)
{
    pCtx->mb00 = false;
    pCtx->mn08 = 0;

    cSPCreatureBase* pAvatar = ((cGameNounManager*)NounManager())->GetAvatar();
    pCtx->mPos = *pAvatar->mLoco.v2c();
    pCtx->mn18 = 0;
    pCtx->mf04 = 0.0f;

    pCreature->FUN_00c14750(true);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bda0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7bda0(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c14750(true);
    return ((cPosseSimulator*)FUN_00d539d0(pCreature))->RemovePosseSlot();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bdc0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bdc0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tConfusedCtx* pCtx)
{
    pCtx->mf00 = 0.0f;
    int32_t nTime = (int32_t)g_mathRandom.RandomUint32Uniform(10);
    pCtx->mPos.x = (float)(nTime + 5);
    pCreature->FUN_00c0ba10();
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7be00
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7be00(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c14750(!pCreature->mLoco.vf8());
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7be30
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7be30(cCreatureIterator* pIterator, cSPCreatureBase* pTarget)
{
    if (!pIterator->AtBegin())
    {
        cSPCreatureBase* pCreature = pIterator->FUN_00bc9b10();
        if (pCreature->mnB20 == pTarget->mnB20 &&
            (pTarget->FUN_00c0d560(pCreature, 1.0f, 0.0f) ||
             pTarget->vc0(pCreature, 1.0f, 0.0f)))
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bea0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bea0(cCreatureIterator* pIterator, cSPCreatureBase* pTarget)
{
    if (!pIterator->AtBegin())
    {
        cSPCreatureBase* pCreature = pIterator->FUN_00bc9b10();
        if (pCreature->mnB20 == pTarget->mnB20)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bee0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bee0(cSPCreatureBase*, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx)
{
    pCtx->mn00 = 0;
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bef0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bef0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tAnimCtx* pCtx)
{
    if (pCtx->mn00 != 0 && pCreature->IsAnimFinished(pCtx->mn00))
        return false;

    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x2000, 0);
    if (pCtx->mn00 != 0)
        return true;
    if (pStim != 0)
    {
        float fElapsed = (float)g_nGameTime;
        if (pStim->mf08 <= 10.0f - fElapsed * 0.001f)
            return true;
    }
    pCtx->mn00 = pCreature->InterruptAnimation(0x2481df9, -1, 0);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bf80
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7bf80(cSPCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x2000, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7bfa0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7bfa0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tConfusedCtx* pCtx)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x1000000, 0);
    if (pStim == 0)
        return false;

    cSPCreatureBase* pTarget = (cSPCreatureBase*)FUN_00d99500(GetAnimalFromStimulus(pStim));
    if (pTarget != 0 && pTarget->FUN_00c0c130())
    {
        pCtx->mf00 = g_kThree;
        pCtx->mPos = *pTarget->mLoco.v2c();
        pCreature->FUN_00c1d460(0xc46ed8ab, 0xc46ed8ab);
        pCreature->MoveToPointAtSpeed(2, &pCtx->mPos, 1.0f, 2.0f);
        pCreature->v84(&pTarget->mCombatant, 0, 0);
        pCtx->mn10 = pCreature->PlayAnimation(0x3139a5d, 1, -1);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7c090
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d7c090(cSPCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x1000000, 0);
    pCreature->FUN_00c17350(0xc46ed8ab, 0);
    pCreature->mLoco.vec();
    pCreature->FUN_00c14750(true);
    pCreature->v84((void*)0, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7c0f0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7c0f0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tConfusedCtx* pCtx, uint32_t, float fDelta)
{
    cSPCreatureBase* pTarget =
        (cSPCreatureBase*)FUN_00d99500(pCreature->GetTargetAsCreature());
    if (pTarget == 0)
        return false;

    float fA = FUN_00d38a30(1, pCreature);
    float fB = FUN_00d38a30(2, pCreature);
    if (pCreature->FUN_00c0d560(pTarget, fA, 0.0f))
        return false;
    if (pCreature->vc0(pTarget, fB, 0.0f))
        return false;

    if (pCreature->mLoco.IsNearGoal())
    {
        pCtx->mf00 -= fDelta;
        if (g_kTiny > pCtx->mf00)
            return false;
    }

    if (pCreature->IsAnimFinished(pCtx->mn10))
        pCtx->mn10 = pCreature->PlayAnimation(0x3139a5d, 1, -1);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7c1d0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7c1d0(cSPCreatureBase* pCreature)
{
    pCreature->PlayAnimation(0x915f7deb, 1, -1);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7c1f0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7c1f0(cSPCreatureBase* pCreature)
{
    cSPCreatureBase* pAvatar = ((cGameNounManager*)NounManager())->GetAvatar();
    if (pAvatar != 0)
    {
        ((cAnimRequests*)pCreature->mp1624)->FUN_00bc9d40(0x80, g_kSixty, pAvatar, 0);
        pCreature->mbFB9 = false;
        pCreature->v84(&pAvatar->mCombatant, 1, 0);
        pCreature->PlayAnimationWithTarget(0x5295983c, &pAvatar->mLoco, -1, -1);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7c270
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7c270(cSPCreatureBase* pCreature)
{
    cSPCreatureBase* pAvatar = ((cGameNounManager*)NounManager())->GetAvatar();
    if (pAvatar == 0 || pAvatar->mbB5e)
        return 0.0f;

    if (pAvatar->mpBehaviorTree->mStimuli.Play(0, 0x1000000) != 0)
        return 1.0f;

    if (pCreature->mbFB9)
    {
        if (((cAnimRequests*)pCreature->mp1624)->FUN_00bc9a00(0x80))
            pCreature->mbFB9 = false;
    }
    if (!((cAnimRequests*)pCreature->mp1624)->FUN_00bc9a00(0x80) && pCreature->mbFB9 &&
        pCreature->mpBehaviorTree->mStimuli.Play(0x4000000, 0) != 0)
        return 1.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d7c310
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d7c310(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t,
                          tGreetCtx*)
{
    uint32_t nAnim = 0x5295983c;
    if (!pCreature->vd0())
        nAnim = 0x26f1f86;
    return pCreature->AnimationFinished(nAnim) ? false : true;
}
