// Slice s00db9380 -- the tribe "heal other" behavior: the seven-step heal tick, the payload of the
// heal action together with its copy constructor / copy assignment / range copy, the nearest injured
// creature query and the heal-other behavior tick.
//
//   0x00db9380  unnamed                        -- seven-step heal animation/effect state machine.
//   0x00db97f0  unnamed                        -- cHealOtherData copy constructor.
//   0x00db99a0  unnamed                        -- copy a range of 0x250-byte heal entries into raw storage.
//   0x00db9a00  unnamed                        -- nearest injured noun within the heal radius.
//   0x00db9b30  SP::TRIBE_HEAL_OTHER_Tick      -- heals the selected tribesman while in reach.
//   0x00dba000  unnamed                        -- two-step heal animation tick.
//   0x00dba120  unnamed                        -- cHealOtherData copy assignment.
//
// The behavior runtime calls the three tick entries with the creature first and the behavior memory
// block (cHealActionState) on the stack, so they are plain seven/five-argument cdecl functions.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"
#include <math.h>
#include <new>

namespace SP {

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Vec2 { float x, y; Vec2() {} Vec2(float a, float b) : x(a), y(b) {} };

#define PV(n) virtual void pv##n();

// ---------------------------------------------------------------------------
// spatial / locomotive sub-object (creature+0xc0); own vtable.
// ---------------------------------------------------------------------------
struct Loco {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3* GetPosition();                       // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual bool IsAlive();                                  // +0x58
    virtual const Vec3* GetFacing(Vec3* out);                // +0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetRadius();                               // +0x74
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(3a)
    virtual void vfec();                                     // +0xec
};

// health bookkeeping of a creature (creature+0x5a8); own vtable.
struct cCombatObj {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d)
    PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual float GetMaxHealth();                            // +0x58
    char pad00[0x38 - 0x04];
    float mHealth;                                           // +0x38
    void  PartialRepair(float fAmount);                      // 0xbfd1a0 (thiscall)
};

class cHealTuningRecord;

// ---------------------------------------------------------------------------
// the animation queue reached through the creature environment (creature+0xb4c -> +0x08)
// ---------------------------------------------------------------------------
class cMotionQueue {
  public:
    void Play(int nA, int nB, float fC, void* pD);             // 0xbc97f0 (thiscall, cleans 0x10)
};

class cCreatureEnv {
  public:
    void*        mpField00;                                    // +0x00
    int          mField04;                                     // +0x04
    cMotionQueue mMotion;                                      // +0x08
};

// ref-counted spatial object handed around the action system (AddRef = slot 0, Release = slot 1)
class cAutoRefTarget {
  public:
    virtual void AddRef();                                     // +0x00
    virtual void Release();                                    // +0x04
};

// handle that keeps a reference alive for the lifetime of the scope
class cAutoRefCount {
  public:
    void Init(cAutoRefTarget* pObject);                        // 0x572660
    void Destroy()
    {
        if (mpObject)
            mpObject->Release();
    }

    cAutoRefTarget* mpObject;                                  // +0x00
};

class cAutoRefVector {
  public:
    void PushBack(cAutoRefCount* pRef);                        // 0xe1c7f0

    cAutoRefCount* mpBegin;                                    // +0x00
    cAutoRefCount* mpEnd;                                      // +0x04
    cAutoRefCount* mpCapacity;                                 // +0x08
};

// The behavior memory block of the heal behaviors, passed as the sixth argument.
struct cHealActionState {
    int  mToolId;                                            // +0x00 (tribe tool / noun handle)
    int  mStep;                                              // +0x04
    int  mAnimId;                                            // +0x08
    cHealTuningRecord* mpTuning;                             // +0x0c
    bool mbDone;                                             // +0x10
};

// ref-counted object reached through the action payload (AddRef at +0xbc, Release at +0xc0).
class cRefCounted {
  public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d)
    PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b)
    PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e)
    virtual void AddRef();                                   // +0xbc
    virtual void Release();                                  // +0xc0
};

// ---------------------------------------------------------------------------
// creature
// ---------------------------------------------------------------------------
class cSPCreatureCitizen {
  public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d)
    PV(0e) PV(0f) PV(10) PV(11)
    virtual void v48(int nArg);                              // +0x48
    virtual int  v4c();                                      // +0x4c
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b)
    PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b)
    virtual cHealTuningRecord* GetToolTuning(int nToolId);   // +0xb4

    // --- direct entry points used by this slice ---
    bool     HasAnim(unsigned nAnimationId);                 // 0xc0e0c0
    void     CancelToolAnim(int nArg);                       // 0xc14750
    unsigned InterruptAnimation(unsigned nAnimationId, int nVariant, int nFlags);          // 0xc12310
    unsigned PlayAnimation(unsigned nAnimationId, int nBlend, int nVariant);               // 0xc12190
    void     InterruptAnimationWithTarget(unsigned nAnimationId, void* pTarget, int nA, int nB); // 0xc149c0
    bool     AnimationFinished(unsigned nAnimationId);       // 0xc12400
    unsigned GetCurrentAnimationGUID();                      // 0xc0e040
    unsigned GetAnimationVariant();                          // 0xc22820
    bool     WaitForAnimEventOrEnd(unsigned nEvent, int* pOutValue, int nArg, int nAnimationId, int nFlag); // 0xc14ef0
    void     SetCurrentToolEffect(int nEffect, int nArg);    // 0xc24f40
    void     SetToolState(int nArg);                         // 0xc26310
    void     CancelTool(int nToolId, bool bA, bool bB);      // 0xc196a0
    void     MoveToPointAtSpeed(int nMode, const Vec3* pPoint);   // 0xc1c1d0
    void     SetFlag(int nId, void* pArg);                   // 0xc0b370

    char     pad00[0x24 - 0x04];
    int      mSpeciesKey;                                    // +0x24
    char     pad28[0xc0 - 0x28];
    Loco     mLoco;                                          // +0xc0
    char     padc4[0x5a8 - 0xc0 - sizeof(Loco)];
    cCombatObj mCombat;                                      // +0x5a8
    char     pad5ac[0xb20 - 0x5a8 - sizeof(cCombatObj)];
    void*    mpSpecies;                                      // +0xb20
    char     padb24[0xb4c - 0xb24];
    cCreatureEnv* mpEnv;                                     // +0xb4c
    char     padb50[0xb58 - 0xb50];
    unsigned mFlagsB58;                                      // +0xb58
    char     padb5c[0xb5e - 0xb5c];
    bool     mbB5e;                                          // +0xb5e
};

// ---------------------------------------------------------------------------
// heal tuning record (state+0x0c and the result of cSPCreatureCitizen::GetToolTuning)
// ---------------------------------------------------------------------------
class cIdVector {
  public:
    int* mpBegin;                                            // +0x00
    int* mpEnd;                                              // +0x04
    int* mpCapacity;                                         // +0x08
};

class cHealTuningRecord {
  public:
    int GetAt(uint32_t nIndex);                              // 0x4d3cd0

    char        pad00[8];
    int         mId;                                         // +0x08
    char        pad0c[0x3c];
    cIdVector   mAnimIds;                                    // +0x48
    char        pad58[0xa8 - 0x58];
    float       mHoldDistance;                               // +0xa8
    char        padac[0xf4 - 0xac];
    float       mRadius;                                     // +0xf4
    char        padf8[0x130 - 0xf8];
    void*       mpProperties;                                // +0x130
};

// ---------------------------------------------------------------------------
// the action payload (0x24c bytes, polymorphic)
// ---------------------------------------------------------------------------
class cGrowArray {
  public:
    void Copy(const cGrowArray& src);                        // 0xb45c10
    cGrowArray& operator=(const cGrowArray& src);            // 0xc1b790

    void*    mpBegin;                                        // +0x00
    void*    mpEnd;                                          // +0x04
    void*    mpCapacity;                                     // +0x08
    void*    mpAllocator;                                    // +0x0c
    unsigned mCount;                                         // +0x10
};

class cSmallList {
  public:
    cSmallList& operator=(const cSmallList& src);            // 0xdb5b30

    void Init()                                              // empty small list backed by the inline buffer
    {
        void** pInline = mInline;
        void** pCapacity = (void**)((char*)pInline + 8 * sizeof(void*));
        mpBegin = pInline;
        mpEnd = pInline;
        mCount = 0;
        mpCapacity = pCapacity;
    }

    void*    mpBegin;                                        // +0x00
    void*    mpEnd;                                          // +0x04
    void*    mpCapacity;                                     // +0x08
    void*    mpField0c;                                      // +0x0c
    void*    mpField10;                                      // +0x10
    unsigned mCount;                                         // +0x14
    void*    mInline[8];                                     // +0x18
};

class cHealTrack {
  public:
    void Copy(const cHealTrack& src);                        // 0xdb7fc0
    cHealTrack& operator=(const cHealTrack& src);            // 0xdb5e20

    char mBody[0x138];
};

class cActionCircle {
  public:
    cActionCircle() {}
    void Copy(const cActionCircle& src);                     // 0x00c278e0 (copy construction)
    cActionCircle& operator=(const cActionCircle& src);      // 0x00d5d4b0

    int mBody[0x19];
};

class cHealOtherBase {
  public:
    cHealOtherBase() {}
    cHealOtherBase(const cHealOtherBase& src) : mFlags(src.mFlags) {}

    virtual void v00();

    int mFlags;                                              // +0x04
};

// A counter that the copy constructor duplicates through its float view and the assignment
// operator through its integer view (that is what the two retail functions really do).
union cHealCounter {
    int   mValue;
    float mValueAsFloat;
};

class cHealOtherData : public cHealOtherBase {
  public:
    __declspec(nothrow) cHealOtherData(const cHealOtherData& src);
    cHealOtherData& operator=(const cHealOtherData& src);

    cGrowArray    mEntries;                                  // +0x008
    cSmallList    mTargets;                                  // +0x01c
    cHealTrack    mTrack;                                    // +0x054
    cRefCounted*  mpSubject;                                 // +0x18c
    cRefCounted*  mpObject;                                  // +0x190
    // copied as plain integers by the assignment but as floats by the copy constructor
    cHealCounter   mCounters[6];                             // +0x194
    float          mRadii[8];                                // +0x1ac
    int           mAnimIndex;                                // +0x1cc
    bool          mbFlag1d0;                                 // +0x1d0
    bool          mbFlag1d1;                                 // +0x1d1
    cActionCircle mCircle;                                   // +0x1d4
    int           mRandSeed;                                 // +0x238
    bool          mbFlag23c;                                 // +0x23c
    int           mTuningIndex;                              // +0x240
    bool          mbFlag244;                                 // +0x244
    int           mSubAnim;                                  // +0x248
};

// one entry of the heal action array (0x250 bytes); bit 31 of mFlags marks an empty slot
struct cHealOtherEntry {
    int            mFlags;
    cHealOtherData mData;
};

// ---------------------------------------------------------------------------
// singletons and out-of-slice helpers
// ---------------------------------------------------------------------------
struct cMathRandom {                                          // 0x01601760
    unsigned RandomUint32Uniform(unsigned nRange);            // 0xa68fb0
};
extern cMathRandom gMathRandom;

extern void*  gpTribeProperties;                              // 0x01581288
extern char   gNounQueryOptions;                              // 0x018ebadc

class cPlanetModel {
  public:
    const Vec3* DirectionToSurfacePosition(Vec3* pOut, const Vec3* pIn, float fA, float fB); // 0xb815a0
};
cPlanetModel* PlanetModel();                                  // 0xb3d350

struct cNoun;
struct cNounRange { void* mpOwner; cNoun** mpBegin; cNoun** mpEnd; };
class cGameNounManager {
  public:
    cNounRange* GetGameDataList(bool (*pf0)(cNoun*), bool (*pf1)(cNoun*), bool (*pf2)(cNoun*),
                                bool (*pf3)(cNoun*), char* pOptions);   // 0xb21340
};
cGameNounManager* NounManager();                              // 0xb3d300

struct cNoun {
    bool IsHealBlocked(int nKind);                            // 0xc38990
    char pad00[0x34];
    Loco mSpatial;                                            // +0x34
};

bool NounFilterSpecies(cNoun* pNoun);                         // 0xcd7d10
bool NounFilterAlive(cNoun* pNoun);                           // 0xd3d420
bool NounFilterKind(cNoun* pNoun);                            // 0xad48b0
bool NounFilterStation(cNoun* pNoun);                         // 0xb1e500

struct behavior_stimuli {
    void GetAny();                                            // 0xd997e0
    void* mpObject;                                           // +0x00
    void* mpTarget;                                           // +0x04
    char  pad08[0x10];
    int   mnDistance;                                         // +0x18
};

class cActionSystem {
  public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d)
    PV(0e) PV(0f) PV(10) PV(11)
    virtual bool v48(const Vec3* pPos, float fRadius, void* pOut, int nFlags,
                     float (*pfnSeparation)(Loco*, Loco*, int), void* pCreature);   // +0x48
};
cActionSystem* GetActionSystem();                             // 0xb3d240

class cSpeciesCounterMap {
  public:
    int* Find(const int& nKey);                               // 0x564a10
};

class cTribeModeStrategy {
  public:
    char               pad00[0x7c];
    cSpeciesCounterMap mCounters;                             // +0x7c
    char               pad80[0x94 - 0x80];
    cAutoRefVector     mHealTargets;                          // +0x94
    char               pad98[0x1a0 - 0xa0];
    float              mHealAmount;                           // +0x1a0
};
cTribeModeStrategy* cTribeModeStrategy_Instance();            // 0xcd40b0

class cSpatialObjectList {
  public:
    void*    mpBegin;                                         // +0x00
    void*    mpEnd;                                           // +0x04
    void*    mpCapacity;                                      // +0x08
    void*    mpField0c;                                       // +0x0c
    void*    mpField10;                                       // +0x10
    unsigned mCount;                                          // +0x14
    void*    mInline[8];                                      // +0x18
};

float GetPropertyT(void* pProperties, unsigned nPropertyId, float fDefault);   // 0x4e1c70
Vec2  GetPropertyAsVector2(void* pProperties, unsigned nPropertyId, Vec2 vDefault); // 0x6a10c0
int   GetTutorialToolPrice(void* pProperties, unsigned nPropertyId, int nDefault); // 0x4e1c30

int   GetCurrentGameMode();                                   // 0xb5b800
void* AchievementsController();                               // 0x675250
bool  HasAchievement(void* pController, unsigned nAchievement); // 0x675e80
unsigned GetAchievementTarget(unsigned nAchievement);         // 0x6766e0
void  AwardAchievement(void* pController, unsigned nAchievement); // 0x676710

void* ResolveNoun(int nHandle);                               // 0xd99470
float GetSeparation(Loco* pA, Loco* pB, int nFlags);          // 0xd99ac0
const Vec3* NormalizeSafe(Vec3* pOut, const Vec3* pIn);       // 0x449c20
int   CreatureStateCode(void* pCreature);                     // 0xc0ee60
bool  CreatureFlag388(void* pCreature);                       // 0xc0c0e0
bool  CreatureIsIdle(void* pCreature);                        // 0xc0b770
void  CreatureSnapshot(void* pCreature);                      // 0xc0d3a0
void  CreatureSetField(void* pCreature, unsigned nValue);     // 0xc0b370
void* ResolveCreature(void* pHandle);                         // 0xb4d960
void  FUN_00da61e0(cSPCreatureCitizen* c, int nFx);           // 0xda61e0
bool  FUN_00da6270(cSPCreatureCitizen* c, int nArg);          // 0xda6270
void  FUN_00db2c00(cHealActionState* pState);                 // 0xdb2c00
void  FUN_00dae730(cHealActionState* pState);                 // 0xdae730
void  FUN_00db9f60(cHealActionState* pState, const Vec3* pPos); // 0xdb9f60
int   FUN_00bcb660(cCreatureEnv* pEnv, unsigned nEvent);      // 0xbcb660
void  FUN_00c7dc70(void** pBegin, void** pEnd, Vec3 vPos);    // 0xc7dc70
void  FUN_00ad92d0(void* pVector);                            // 0xad92d0
void  FUN_00d01790(void* pVector, int nCount);                // 0xd01790
void  FUN_00ebf480(void* pVector, void** pOut);               // 0xebf480
void  FUN_00da61e0x();

extern const float gHealTimeLimit;                            // 0x147c218 (FLT_MAX)
extern const double gHealMaxDistance;                         // 0x147c2d0 (2900.0)
extern const float kHalfDegree;                               // 0x145cff0 (0.008726646)

// ---------------------------------------------------------------------------
// 0x00db9380 -- the seven-step heal tick
// ---------------------------------------------------------------------------
// @ 0x00db9380
bool FUN_00db9380(cSPCreatureCitizen* c, int, int, int, int, cHealActionState* st)
{
    switch (st->mStep) {
    case 0: {
        unsigned nAnimId = c->InterruptAnimation(0x6006755, c->GetAnimationVariant(), 0);
        ++st->mStep;
        st->mAnimId = nAnimId;
        return true;
    }

    case 1: {
        int nTool = -1;
        if (c->WaitForAnimEventOrEnd(0xe95450e, &nTool, 0, st->mAnimId, 1)) {
            c->SetCurrentToolEffect(0, nTool);
            ++st->mStep;
        }
        return true;
    }

    case 2: {
        int nTool = -1;
        if (c->WaitForAnimEventOrEnd(0x7d7502fc, &nTool, 0, st->mAnimId, 1)) {
            c->SetCurrentToolEffect(0x15, nTool);
            ++st->mStep;
            st->mAnimId = c->PlayAnimation(0x609ea47, 1, c->GetAnimationVariant());
        }
        return true;
    }

    case 3: {
        if (c->GetCurrentAnimationGUID() != 0x609ea47)
            return true;
        ++st->mStep;
        st->mAnimId = c->PlayAnimation(0x609ea41, 1, c->GetAnimationVariant());
        c->CancelTool(st->mToolId, true, false);
        FUN_00da61e0(c, 0x16);

        cHealTuningRecord* pTuning = c->GetToolTuning(st->mToolId);
        Loco* pSelf = &c->mLoco;
        const Vec3* pSelfPos = pSelf->GetPosition();

        cSpatialObjectList candidates;
        candidates.mpBegin = candidates.mInline;
        candidates.mpEnd = candidates.mInline;
        candidates.mCount = 0;
        candidates.mpCapacity = candidates.mInline + 8;

        cActionSystem* pSystem = GetActionSystem();
        if (!pSystem->v48(pSelf->GetPosition(), pTuning->mRadius + pTuning->mHoldDistance,
                          &candidates, 0, &GetSeparation, c))
            return true;

        float fHealAmount = GetPropertyT(pTuning->mpProperties, 0x83028513, 60.0f);
        cTribeModeStrategy* pStrategy = cTribeModeStrategy_Instance();
        pStrategy->mHealAmount = fHealAmount;

        int nBudget = GetTutorialToolPrice(pTuning->mpProperties, 0x217997f4, 4);
        int nToolCount = pStrategy->mHealTargets.mpEnd - pStrategy->mHealTargets.mpBegin;
        nBudget -= nToolCount;

        FUN_00c7dc70((void**)candidates.mpBegin, (void**)candidates.mpEnd, *pSelfPos);

        cAutoRefCount ref;
        unsigned nCount = (unsigned)((void**)candidates.mpEnd - (void**)candidates.mpBegin);
        for (unsigned i = 0; i < nCount; ++i) {
            if (nBudget <= 0)
                break;
            void* pVictim = ResolveCreature(((void**)candidates.mpBegin)[i]);
            if (!pVictim)
                continue;
            if (CreatureFlag388(pVictim))
                continue;
            if (((cSPCreatureCitizen*)pVictim)->mbB5e)
                continue;
            if (!CreatureIsIdle(pVictim))
                continue;
            ref.Init((cAutoRefTarget*)pVictim);
            cTribeModeStrategy_Instance()->mHealTargets.PushBack(&ref);
            ref.Destroy();
            CreatureSnapshot(pVictim);
            cSPCreatureCitizen* pTarget = (cSPCreatureCitizen*)pVictim;
            FUN_00bcb660(pTarget->mpEnv, 0x1590b30);
            pTarget->v48(c->v4c());
            pTarget->mpEnv->mMotion.Play(4, 0, 5.0f, c);
            ((cSPCreatureCitizen*)pVictim)->mLoco.vfec();
            ((cSPCreatureCitizen*)pVictim)->InterruptAnimation(0x609ea4c, -1, 0);
            CreatureSetField(pVictim, 0x609ea52);
            ((cSPCreatureCitizen*)pVictim)->mFlagsB58 |= 0x4000;
            --nBudget;
        }
        FUN_00ad92d0(&candidates);
        return true;
    }

    case 4: {
        int nTool = -1;
        if (c->WaitForAnimEventOrEnd(0xe95450e, &nTool, 0, st->mAnimId, 1)) {
            c->SetCurrentToolEffect(0, nTool);
            ++st->mStep;
        }
        return true;
    }

    case 5: {
        int nTool = -1;
        if (c->WaitForAnimEventOrEnd(0x7d7502fc, &nTool, 0, st->mAnimId, 1)) {
            c->SetToolState(nTool);
            ++st->mStep;
        }
        return true;
    }

    case 6:
        if (c->AnimationFinished(st->mAnimId)) {
            c->mpEnv->mMotion.Play(0, 0x20, gHealTimeLimit, 0);
            return false;
        }
        break;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00db97f0 -- cHealOtherData copy constructor
// ---------------------------------------------------------------------------
// @ 0x00db97f0
cHealOtherData::cHealOtherData(const cHealOtherData& src) : cHealOtherBase(src)
{
    mEntries.Copy(src.mEntries);

    mTargets.Init();
    mTargets = src.mTargets;

    mTrack.Copy(src.mTrack);

    mpSubject = src.mpSubject;
    if (mpSubject)
        mpSubject->AddRef();

    mpObject = src.mpObject;
    if (mpObject)
        mpObject->AddRef();

    for (int i = 0; i < 6; ++i)
        mCounters[i].mValueAsFloat = src.mCounters[i].mValueAsFloat;
    for (int i = 0; i < 8; ++i)
        mRadii[i] = src.mRadii[i];

    mAnimIndex = src.mAnimIndex;
    mbFlag1d0 = src.mbFlag1d0;
    mbFlag1d1 = src.mbFlag1d1;
    mCircle.Copy(src.mCircle);
    mRandSeed = src.mRandSeed;
    mbFlag23c = src.mbFlag23c;
    mTuningIndex = src.mTuningIndex;
    mbFlag244 = src.mbFlag244;
    mSubAnim = src.mSubAnim;
}

// ---------------------------------------------------------------------------
// 0x00db99a0 -- copy a range of heal entries into raw storage
// ---------------------------------------------------------------------------
// @ 0x00db99a0
cHealOtherEntry* FUN_00db99a0(cHealOtherEntry* pFirst, cHealOtherEntry* pLast, cHealOtherEntry* pDst)
{
    if (pFirst != pLast) {
        do {
            if (pDst) {
                pDst->mFlags = pFirst->mFlags;
                bool bEmpty = ((unsigned)pFirst->mFlags >> 31) & 1;
                if (!bEmpty && &pDst->mData)
                    ::new (static_cast<void*>(&pDst->mData)) cHealOtherData(pFirst->mData);
            }
            ++pFirst;
            ++pDst;
        } while (pFirst != pLast);
    }
    return pDst;
}

// ---------------------------------------------------------------------------
// 0x00db9a00 -- nearest injured noun within the heal radius
// ---------------------------------------------------------------------------
// @ 0x00db9a00
float FUN_00db9a00(void* pSource, void*, void*, unsigned nFlags, behavior_stimuli* pStimuli,
                   bool* pbFound)
{
    if ((nFlags & 1) != 0)
        return 0.0f;

    PlanetModel();

    const Vec3* pSourcePos = ((cSPCreatureCitizen*)pSource)->mLoco.GetPosition();
    cNoun* pBest = 0;
    float fBestDistance = 2900.0f;

    cNounRange& range = *NounManager()->GetGameDataList(NounFilterSpecies, NounFilterAlive,
                                                        NounFilterKind, NounFilterStation,
                                                        &gNounQueryOptions);
    for (cNoun** it = range.mpBegin; it != range.mpEnd; ++it) {
        cNoun* pNoun = *it;
        if (pNoun->IsHealBlocked(1))
            continue;
        const Vec3* pNounPos = pNoun->mSpatial.GetPosition();
        float fDx = pNounPos->x - pSourcePos->x;
        float fDy = pNounPos->y - pSourcePos->y;
        float fDz = pNounPos->z - pSourcePos->z;
        float fDistance = fDz * fDz + fDx * fDx + fDy * fDy;
        if (fBestDistance > fDistance) {
            pBest = pNoun;
            fBestDistance = fDistance;
        }
    }

    if (!pBest)
        return 0.0f;

    if (pStimuli)
        pStimuli->GetAny();

    *pbFound = true;
    pStimuli->mpTarget = (char*)pBest + 0x508;
    pStimuli->mnDistance = (int)(float)sqrt(2900.0);
    return 1.0f;
}

// ---------------------------------------------------------------------------
// 0x00db9b30  SP::TRIBE_HEAL_OTHER_Tick
// ---------------------------------------------------------------------------
// @ 0x00db9b30
bool TRIBE_HEAL_OTHER_Tick(cSPCreatureCitizen* c, int, int, int, int, cHealActionState* st,
                           float fHealScale)
{
    cSPCreatureCitizen* pSubject = (cSPCreatureCitizen*)ResolveNoun(st->mToolId);
    if (!pSubject)
        return FUN_00da6270(c, 5);

    if (pSubject->mCombat.mHealth >= pSubject->mCombat.GetMaxHealth())
        return FUN_00da6270(c, 5);

    Loco* pSubj = &pSubject->mLoco;
    Loco* pSelf = &c->mLoco;

    float fReach = pSubj->GetRadius() + pSelf->GetRadius();
    float fSeparation = GetSeparation(pSelf, pSubj, 1);

    Vec2 vRange = GetPropertyAsVector2(gpTribeProperties, 0x1e6bcc1d, Vec2(1.0f, 5.0f));
    float fStartFraction = GetPropertyT(gpTribeProperties, 0xd21a82b1, 1.0f);

    float fMaxRange = vRange.y;
    float fMinRange = vRange.x;
    float fFullReach = (fMaxRange - fSeparation) * 0.5f + fSeparation + fStartFraction;

    bool bInReach = fMaxRange > fSeparation;
    Vec3 facing;
    pSubj->GetFacing(&facing);

    Vec3 approach(pSubj->GetPosition()->x - facing.x * fSeparation,
                  pSubj->GetPosition()->y - facing.y * fSeparation,
                  pSubj->GetPosition()->z - facing.z * fSeparation);

    bool bHealing = c->HasAnim(0x562cfbf);
    if (!bInReach) {
        if (bHealing)
            c->CancelToolAnim(0);
    } else {
        if (!bHealing)
            c->InterruptAnimationWithTarget(0x562cfbf, pSubj, -1, -1);

        pSubject->mCombat.PartialRepair(fFullReach * fHealScale);

        if (pSubject->mCombat.mHealth >= pSubject->mCombat.GetMaxHealth() && pSelf->IsAlive()
            && pSubj->IsAlive() && GetCurrentGameMode() == 0x1654c02) {
            void* pController = AchievementsController();
            if (!HasAchievement(pController, 0x90ec8983)) {
                int* pCounter = cTribeModeStrategy_Instance()->mCounters.Find(pSubject->mSpeciesKey);
                ++*pCounter;
                if (*pCounter >= GetAchievementTarget(0x90ec8983))
                    AwardAchievement(pController, 0x90ec8983);
            }
            c->mpEnv->mMotion.Play(0, 0x20, gHealTimeLimit, 0);
        }

        if (CreatureStateCode(pSubject)) {
            float fCosLimit = cosf(GetPropertyT(gpTribeProperties, 0x362cc818, 45.0f) * kHalfDegree);
            const Vec3* pSubjPos = pSubj->GetPosition();
            const Vec3* pSelfPos = pSelf->GetPosition();
            Vec3 toSelf(pSelfPos->x - pSubjPos->x, pSelfPos->y - pSubjPos->y,
                        pSelfPos->z - pSubjPos->z);
            Vec3 toSelfDir;
            NormalizeSafe(&toSelfDir, &toSelf);
            Vec3 subjFacing;
            pSubj->GetFacing(&subjFacing);
            float fDot = toSelfDir.z * -subjFacing.z + toSelfDir.y * -subjFacing.y
                       + toSelfDir.x * -subjFacing.x;
            if (fDot <= fCosLimit)
                goto Move_Closer;
        }

        if (fSeparation <= (fMaxRange - fStartFraction) * 0.75f + fStartFraction)
            return true;
    }

Move_Closer:
    {
        Vec3 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &approach, 1.0f, 2.0f);
        c->MoveToPointAtSpeed(2, &surf);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00dba000 -- the heal animation tick
// ---------------------------------------------------------------------------
// @ 0x00dba000
bool FUN_00dba000(cSPCreatureCitizen* c, int, int, int, int, cHealActionState* st)
{
    switch (st->mStep) {
    case 0: {
        c->CancelTool(st->mToolId, true, false);

        cIdVector* pAnimIds = &st->mpTuning->mAnimIds;
        unsigned nAnimCount = pAnimIds->mpEnd - pAnimIds->mpBegin;
        unsigned nIndex = nAnimCount > 0 ? gMathRandom.RandomUint32Uniform(nAnimCount) : 0;
        st->mAnimId = c->InterruptAnimation(st->mpTuning->GetAt(nIndex), -1, 0);

        if (st->mpTuning->mId == 0x35) {
            FUN_00db9f60(st, c->mLoco.GetPosition());
            FUN_00dae730(st);
        }
        st->mStep = 1;
        return true;
    }
    case 1:
        if (c->AnimationFinished(st->mAnimId)) {
            FUN_00db2c00(st);
            st->mbDone = true;
            st->mStep = 2;
            return true;
        }
        break;
    case 2:
        if (st->mpTuning->mId == 0x35 && !st->mbDone) {
            FUN_00db2c00(st);
            st->mbDone = true;
        }
        c->mpEnv->mMotion.Play(0, 0x20, gHealTimeLimit, 0);
        return FUN_00da6270(c, 0x16);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00dba120 -- cHealOtherData copy assignment
// ---------------------------------------------------------------------------
// @ 0x00dba120
cHealOtherData& cHealOtherData::operator=(const cHealOtherData& src)
{
    mFlags = src.mFlags;
    mEntries = src.mEntries;
    mTargets = src.mTargets;
    mTrack = src.mTrack;

    if (src.mpSubject != mpSubject) {
        cRefCounted* pNew = src.mpSubject;
        cRefCounted* pOld = mpSubject;
        if (pNew)
            pNew->AddRef();
        mpSubject = pNew;
        if (pOld)
            pOld->Release();
    }
    if (src.mpObject != mpObject) {
        cRefCounted* pNew = src.mpObject;
        cRefCounted* pOld = mpObject;
        if (pNew)
            pNew->AddRef();
        mpObject = pNew;
        if (pOld)
            pOld->Release();
    }

    for (int i = 0; i < 6; ++i)
        mCounters[i].mValue = src.mCounters[i].mValue;
    for (int i = 0; i < 8; ++i)
        mRadii[i] = src.mRadii[i];

    mAnimIndex = src.mAnimIndex;
    mbFlag1d0 = src.mbFlag1d0;
    mbFlag1d1 = src.mbFlag1d1;
    mCircle = src.mCircle;

    mRandSeed = src.mRandSeed;
    mbFlag23c = src.mbFlag23c;
    mTuningIndex = src.mTuningIndex;
    mbFlag244 = src.mbFlag244;
    mSubAnim = src.mSubAnim;
    return *this;
}

} // namespace SP
