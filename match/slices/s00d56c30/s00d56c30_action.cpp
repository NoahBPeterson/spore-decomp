// Slice s00d56c30 - SP::cBehaviorSpaceTurret::Action (custom /O2 SSE code).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// Per-tick air-raid behaviour of the city space turret.  The behaviour owns two
// slot vectors inherited from cInteraction (+0x0c = target list, +0x2c = agent
// list), a cInteractionAgent* -> cTurretState map at +0x74, the life timer at
// +0x90 (its cached "next action" time sits at +0xb0), the city centre it aims
// from at +0xbc, the beam lifetime at +0xc8, the re-attack delay at +0xd0 and
// the latched siren state at +0xd8.
//
// The tick first decides whether the air raid is still relevant (planet
// attackable / mission active / global alert, folded together with
// UpdateAirRaidSiren), then either tears every turret's effect down (siren off)
// or runs the weapon logic: pick the nearest creature in front of the city,
// spread the available shots over the agent slots (UpdateFirePattern) and give
// each turret a target when it is in range and facing it.

#include <math.h>

typedef unsigned int u32;
typedef unsigned char u8;
typedef long long i64;
typedef unsigned long long u64;

// ---------------------------------------------------------------------------
// Shared value types
// ---------------------------------------------------------------------------
struct Vec3f {
    float x, y, z;

    Vec3f operator-(const Vec3f& other) const
    {
        Vec3f r;
        r.x = x - other.x;
        r.y = y - other.y;
        r.z = z - other.z;
        return r;
    }
};

struct Matrix3Rows {
    float mRows[9];
};

struct cSlotEntry;

// ---------------------------------------------------------------------------
// spstl deque of 128-entry blocks behind a block pointer array
// ---------------------------------------------------------------------------
struct cSlotBlock;

struct cSlotEntry {
    void* mpObject;                                    // +0x00 AutoRefCount payload
    u32   mnFlags;                                     // +0x04
};

struct cSlotBlock {
    u32        mnHeader;                               // +0x00
    cSlotEntry mEntries[128];                          // +0x04
};

struct cSlotIterator {
    u8* mpBase;                                        // +0x00 address of the owning vector
    u32 mnIndex;                                       // +0x04

    void Increment();                                  // 0x00abe9b0

    bool operator!=(const cSlotIterator& other) const
    {
        return mpBase + mnIndex != other.mpBase + other.mnIndex;
    }

    bool operator==(const cSlotIterator& other) const
    {
        return mpBase + mnIndex == other.mpBase + other.mnIndex;
    }
};

struct cSlotVector {
    cSlotBlock** mpBlocks;                             // +0x00
    cSlotBlock** mpEnd;                                // +0x04
    u32          mn08;                                 // +0x08
    u32          mn0c;                                 // +0x0c
    u32          mn10;                                 // +0x10
    u32          mnFreeChain;                          // +0x14
    u32          mnIndex;                              // +0x18
    u32          mnPad1c;                              // +0x1c

    u32 Size();                                        // 0x00abefd0
    cSlotIterator* Begin(cSlotIterator* pOut);         // 0x00abeaf0

    u32 EndIndex() const
    {
        return ((int)((char*)mpEnd - (char*)mpBlocks) >> 2) * 0x80 - 0x7f
               + mnFreeChain;
    }

    cSlotIterator End() const
    {
        cSlotIterator it;
        it.mpBase = (u8*)this;
        it.mnIndex = EndIndex();
        return it;
    }

    cSlotEntry& At(const cSlotIterator& it)
    {
        return mpBlocks[it.mnIndex >> 7]->mEntries[it.mnIndex & 0x7f];
    }
};

// ---------------------------------------------------------------------------
// Foreign interface stubs (only the slots this file calls are named)
// ---------------------------------------------------------------------------
class cSpatialObject {
public:
    virtual void s00(); virtual void s01(); virtual void s02();   // +0x00..+0x08
    virtual void s03(); virtual void s04(); virtual void s05();   // +0x0c..+0x14
    virtual void s06(); virtual void s07(); virtual void s08();   // +0x18..+0x20
    virtual void s09(); virtual void s10();                       // +0x24..+0x28
    virtual Vec3f* GetPosition();                                 // +0x2c
    char mPad04[0x48];
};

struct XformMsg {
    XformMsg();                                                   // 0x00434040
    void SetPosition(const Vec3f* pPosition);                      // 0x00571d40

    char           mPad00[0x0c];                                  // +0x00
    unsigned short mFlags;                                        // +0x0c
    unsigned short mPad0e;                                        // +0x0e
    unsigned short mSeq;                                          // +0x10
    char           mPad12[0x0e];                                  // +0x12..+0x1f
    Matrix3Rows    mOrientation;                                  // +0x20
    char           mPad44[0x30];                                  // +0x44
};

class cVisualEffect {
public:
    virtual void e00();                                           // +0x00
    virtual void Release();                                       // +0x04
    virtual void e08(int nValue);                                 // +0x08
    virtual void e0c(int nValue);                                 // +0x0c
    virtual bool IsActive();                                      // +0x10
    virtual void e14();                                           // +0x14
    virtual void SetXform(XformMsg* pMsg);                        // +0x18
};

// AutoRefCount<cIVisualEffect> stored inline in the turret
class cEffectRef {
public:
    cVisualEffect** AsPPTypeParam();                              // 0x00a16f40
    cVisualEffect*  mpObject;                                     // +0x00
};

class cEffectManager {
public:
    virtual void m00(); virtual void m01(); virtual void m02();    // +0x00..+0x08
    virtual void m03(); virtual void m04(); virtual void m05();    // +0x0c..+0x14
    virtual void m06(); virtual void m07(); virtual void m08();    // +0x18..+0x20
    virtual void m09(); virtual void m10();                        // +0x24..+0x28
    virtual bool CreateEffect(const void* pTypeId, int nFlags,
                              cVisualEffect** ppEffect);           // +0x2c
};

cEffectManager* EffectsManagerPtr();                              // 0x0067ddd0

// The weapon data owned by a turret (SP::cSPSpaceToolData).
class cSpaceToolData {
public:
    int    GetCooldown();                                          // 0x0104bde0
    float  GetMinRange();                                          // 0x0104be20
    float  GetMaxRange();                                          // 0x0104be30
    float  GetField1e8();                                          // 0x00e21850
};

class cCombatant {
public:
    virtual void c00(); virtual void c01();                        // +0x00..+0x04
    virtual cSpatialObject* GetSpatial();                          // +0x08
    virtual void c03(); virtual void c04(); virtual void c05();    // +0x0c..+0x14
    virtual void c06(); virtual void c07(); virtual void c08();    // +0x18..+0x20
    virtual void c09(); virtual void c10(); virtual void c11();    // +0x24..+0x2c
    virtual void c12(); virtual void c13(); virtual void c14();    // +0x30..+0x38
    virtual void c15(); virtual void c16(); virtual void c17();    // +0x3c..+0x44
    virtual void c18(); virtual void c19();                        // +0x48..+0x4c
    virtual void SetTarget(const Vec3f* pTarget);                  // +0x50

    int  GetDamageState();                                         // 0x008e7f80
    bool IsHostileAlive();                                         // 0x00bfc600

    char mPad04[0xf4];                                             // +0x04
};

class cTurret {
public:
    virtual void t00();                                            // +0x00
    virtual void t01(); virtual void t02(); virtual void t03();    // +0x04..+0x0c
    virtual void t04(); virtual void t05(); virtual void t06();    // +0x10..+0x18
    virtual void t07(); virtual void t08(); virtual void t09();    // +0x1c..+0x24
    virtual void t10(); virtual void t11(); virtual void t12();    // +0x28..+0x30
    virtual void t13(); virtual void t14(); virtual void t15();    // +0x34..+0x3c
    virtual void t16(); virtual void t17(); virtual void t18();    // +0x40..+0x48
    virtual void OnTargetSelected();                               // +0x4c

    cSpaceToolData* GetToolData694();                              // 0x00bce3f0
    cSpaceToolData* GetToolData698();                              // 0x00bce3d0
    cSpaceToolData* GetToolData69c();                              // 0x00bce3e0
    void FaceAtTarget(const Vec3f* pTarget);                       // 0x00bce480
    bool AcceptTarget(int nMode);                                  // 0x00c38990

    char           mPad04[0x30];                                   // +0x04..+0x33
    cSpatialObject mSpatial;                                       // +0x34
    char           mPad80[0xa0];                                   // +0x80..+0x11f
    cSpatialObject mBody;                                          // +0x120
    char           mPad16c[0x39c];                                 // +0x16c..+0x507
    Vec3f          mTargetPos;                                     // +0x508
    char           mPad514[0x74];                                  // +0x514..+0x587
    cCombatant     mCombatant;                                     // +0x588
    cEffectRef     mAirRaidEffect;                                 // +0x680
    char           mPad684[0xc4];                                  // +0x684..+0x747
    float          mField748;                                      // +0x748
};

class cInteractionAgent {
public:
    virtual void a00();                                            // +0x00
    virtual cTurret* GetTargetInterface(const void* pTypeId);      // +0x04
    virtual cTurret* GetTurretInterface(const void* pTypeId);      // +0x08
};

class cPlanet {
public:
    int GetToolMode();                                             // 0x00c70e00
};

class cCivilization;

class cGameNounManager {
public:
    cCivilization* GetPlayerCivilization();                        // 0x00b25fb0
};

class cSPToolManager {
public:
    void UseToolStart(cSpaceToolData* pTool, cCombatant* pActor,
                      const Vec3f* pPosition, int nMode, int nFlags,
                      cSpatialObject* pOwner, int nCount);          // 0x01050070
    void UseToolStop(cSpaceToolData* pTool);                        // 0x0104fa90
};

cSPToolManager* ToolManager();                                      // 0x00b3d390

class cSPTimer {
public:
    i64 GetElapsedTime();                                           // 0x00bc3190
    char mPad00[0x20];                                              // +0x00..+0x1f
    i64  mNextEventTime;                                            // +0x20
};

struct cTurretState {
    char mPad00[8];                                                 // +0x00
    i64  mLastFireTime;                                             // +0x08
    i64  mNextFireTime;                                             // +0x10
    i64  mNextEffectTime;                                           // +0x18
    int  mnFlag;                                                    // +0x20
};

// cInteractionAgent* -> cTurretState map rooted at cBehaviorSpaceTurret+0x74
class cTurretStateTree {
public:
    cTurretState* Find(cInteractionAgent* const* ppAgent);          // 0x00d56510
    char mPad00[0x24];
};

struct cFireSlot {
    float x, y, z;
};

struct cFirePattern {
    cFireSlot* mpBegin;
    cFireSlot* mpEnd;
    cFireSlot* mpCapacity;
};

// ---------------------------------------------------------------------------
// Free helpers of this subsystem
// ---------------------------------------------------------------------------
namespace SP {

void* GetCurrentGameMode();                                         // 0x00b5b800

class cSPLivingUniverse {
public:
    static cPlanet* GetActivePlanet();                              // 0x01021260
};

cGameNounManager* NounManager();                                    // 0x00b3d300

void ClearAllTargets(cSlotVector* pAgents);                         // 0x00d54c10
bool IsPlanetAttackableByPlayer(const void* pTarget);               // 0x01029950
bool IsMissionOfTypeActiveAtPlanet(cPlanet* pPlanet);               // 0x0102ae60
bool FUN_01041cf0();                                                // 0x01041cf0
bool UpdateAirRaidSiren(cCivilization* pCiv, const void* pTarget);   // 0x00d54940
void StopAirRaidEffect();                                           // 0x00d54760

cTurret* ResolveTurret(cInteractionAgent* pAgent);                   // 0x00d546f0
cTurret* ResolveSlotTurret(cSlotEntry* pSlot);                       // 0x00d54710
cTurret* FindNearestCreature(Vec3f vProbe, bool bModeA, bool bModeB); // 0x00cc26a0
void UpdateFirePattern(cFirePattern* pPattern, int nCount,
                       cTurret* pTarget);                           // 0x00d56070
void DestroyFirePattern(cFirePattern* pPattern);                    // 0x00540520

Vec3f* Vec3_Normalize(Vec3f* pOut, const Vec3f* pIn);                // 0x00436ce0
Vec3f* OrthogonalVector(Vec3f* pOut, const Vec3f* pIn);              // 0x006985b0
float Dot3(const Vec3f* pA, const Vec3f* pB);                        // 0x00455cc0
Matrix3Rows* Matrix3FromFacingAndUp(Matrix3Rows* pOut,
                                    const Vec3f* pFacing,
                                    const Vec3f* pUp);               // 0x0069b440

// ---------------------------------------------------------------------------
// The behaviour object itself
// ---------------------------------------------------------------------------
class cInteraction {
public:
    void*        mpVtbl;                                            // +0x00
    void*        mpVtbl04;                                          // +0x04
    u32          mn08;                                              // +0x08
    cSlotVector  mTargetList;                                       // +0x0c
    cSlotVector  mAgentList;                                        // +0x2c
};

class cBehaviorSpaceTurret : public cInteraction {
public:
    int  Action();
    int  GetActiveTurretCount();                                    // 0x00d54ce0
    int  CountAttackableTurrets();                                  // 0x00d54d90
    void UpdateWeaponData();                                        // 0x00d547e0
    void FUN_00d56630();                                            // 0x00d56630
    void FUN_00d56870();                                            // 0x00d56870

    char            mPad4c[0x28];                                   // +0x4c..+0x73
    cTurretStateTree mStateTree;                                    // +0x74
    cSPTimer        mLifeTimer;                                     // +0x90
    u32             mnB8;                                           // +0xb8
    Vec3f           mCityCenter;                                    // +0xbc
    int             mnSdrBeamLifetime;                              // +0xc8
    u32             mnCc;                                           // +0xcc
    i64             mReattackDelay;                                 // +0xd0
    bool            mbAirRaidOn;                                    // +0xd8
    char            mPadD9[7];                                      // +0xd9..+0xdf
    cSPTimer        mAirRaidTimer;                                  // +0xe0
};

extern float gAirRaidHealthLimit;                                   // 0x013ec4d0

// ---------------------------------------------------------------------------
// 0x00d56c30  SP::cBehaviorSpaceTurret::Action
// ---------------------------------------------------------------------------
// @ 0x00d56c30
int cBehaviorSpaceTurret::Action()
{
    if (GetCurrentGameMode() == (void*)0x1654c05) {
        if (cSPLivingUniverse::GetActivePlanet()->GetToolMode() == 4)
            return 1;
    }
    if (mAgentList.mnIndex == 0x3fffffff) {
        ClearAllTargets(&mAgentList);
        return 0;
    }
    if (GetActiveTurretCount() == 0) {
        ClearAllTargets(&mAgentList);
        return 0;
    }
    if (mTargetList.Size() == 0) {
        ClearAllTargets(&mAgentList);
        return 0;
    }

    cCivilization* pCiv = NounManager()->GetPlayerCivilization();

    // The turret this behaviour currently watches is the head of the target list.
    cTurret* pTarget = 0;
    {
        cInteractionAgent* pAgent0 =
            (cInteractionAgent*)mTargetList.mpBlocks[mTargetList.mnIndex >> 7]
                ->mEntries[mTargetList.mnIndex & 0x7f].mpObject;
        if (pAgent0 != 0) {
            pTarget = pAgent0->GetTargetInterface((void*)0xee9b2232);
            if (pTarget != 0)
                pTarget->OnTargetSelected();
        }
    }

    bool bAttack = false;
    if (IsPlanetAttackableByPlayer(pTarget))
        bAttack = true;
    bool bMission = false;
    if (IsMissionOfTypeActiveAtPlanet(cSPLivingUniverse::GetActivePlanet()))
        bMission = true;
    if (pTarget->mField748 >= gAirRaidHealthLimit)
        bMission = false;
    if (FUN_01041cf0())
        bAttack = true;

    if (!mbAirRaidOn) {
        if (bAttack)
            bAttack = UpdateAirRaidSiren(pCiv, pTarget);
        else
            StopAirRaidEffect();
    } else if (!bAttack) {
        StopAirRaidEffect();
    }
    bool bRaid = bAttack || bMission || FUN_01041cf0();

    if (!mbAirRaidOn && bRaid)
        FUN_00d56630();
    mbAirRaidOn = bRaid;

    if (!bRaid) {
        // Raid over: drop the effect on every turret that still owns one.
        FUN_00d56870();
        cSlotIterator it;
        mAgentList.Begin(&it);
        while (it != mAgentList.End()) {
            cInteractionAgent* pAgent = (cInteractionAgent*)mAgentList.At(it).mpObject;
            if (pAgent != 0) {
                cTurret* pTurret = pAgent->GetTurretInterface((void*)0x436f315);
                if (pTurret != 0 && pTurret->mAirRaidEffect.mpObject != 0)
                    pTurret->mAirRaidEffect.mpObject->e0c(0);
            }
            it.Increment();
        }
        return 1;
    }

    UpdateWeaponData();
    i64 tNow = mLifeTimer.GetElapsedTime();
    if (tNow > mLifeTimer.mNextEventTime) {
        cSlotIterator fireIt;
        mAgentList.Begin(&fireIt);
        cTurret* pShooter = ResolveSlotTurret(&mAgentList.At(fireIt));
        cSpaceToolData* pWeapon = pShooter->GetToolData69c();
        mLifeTimer.mNextEventTime = tNow + pWeapon->GetCooldown();

        cTurret* pCreature = FindNearestCreature(
            *pTarget->mBody.GetPosition(), bAttack, bMission);
        if (pCreature != 0 && !pCreature->AcceptTarget(1)) {
            Vec3f creaturePos = *pCreature->mSpatial.GetPosition();
            Vec3f toCreature = creaturePos - mCityCenter;
            pWeapon->GetField1e8();
            pWeapon->GetMaxRange();
            Vec3f nToCreature;
            Vec3f nCenter;
            if (Dot3(Vec3_Normalize(&nToCreature, &toCreature),
                     Vec3_Normalize(&nCenter, &mCityCenter)) >= 0.0f) {
                int nShots = (GetActiveTurretCount() - CountAttackableTurrets())
                             * mnSdrBeamLifetime;
                cFirePattern pattern;
                pattern.mpBegin = 0;
                pattern.mpEnd = 0;
                pattern.mpCapacity = 0;
                UpdateFirePattern(&pattern, nShots, pCreature);
                int nSlots = (int)(pattern.mpEnd - pattern.mpBegin);
                cSlotIterator it2;
                mAgentList.Begin(&it2);
                cFireSlot* pSlot = &pattern.mpBegin[nSlots - 1];
                for (; nSlots > 0; --nSlots, --pSlot) {
                    cInteractionAgent* pAgent = (cInteractionAgent*)mAgentList.At(it2).mpObject;
                    cTurret* pTurret = ResolveTurret(pAgent);
                    if (pTurret->mCombatant.GetDamageState() != 2
                        && !pTurret->mCombatant.IsHostileAlive()) {
                        Vec3f position;
                        position.x = pSlot->x;
                        position.y = pSlot->y;
                        position.z = pSlot->z;
                        cSpaceToolData* pTool = pTurret->GetToolData69c();
                        ToolManager()->UseToolStart(
                            pTool, pTurret != 0 ? &pTurret->mCombatant : (cCombatant*)0,
                            &position, -1, 0, &pCreature->mSpatial, 1);
                        ToolManager()->UseToolStop(pTool);
                    }
                    it2.Increment();
                    if (it2 == mAgentList.End())
                        mAgentList.Begin(&it2);
                }
                DestroyFirePattern(&pattern);
            }
        }
    }

    cSlotIterator it;
    mAgentList.Begin(&it);
    while (it != mAgentList.End()) {
        cInteractionAgent* pAgent = (cInteractionAgent*)mAgentList.At(it).mpObject;
        cTurret* pTurret = 0;
        if (pAgent != 0)
            pTurret = pAgent->GetTurretInterface((void*)0x436f315);
        cTurretState* pState = mStateTree.Find(&pAgent);
        cCombatant* pCombatant = &pTurret->mCombatant;

        const Vec3f* pAim = 0;
        if (pCombatant->GetDamageState() != 2 && !pCombatant->IsHostileAlive()) {
            cSpaceToolData* pPrimary = pTurret->GetToolData698();
            cSpaceToolData* pSecondary = pTurret->GetToolData694();
            bool bFired = false;
            if (tNow > pState->mLastFireTime) {
                pState->mLastFireTime += pPrimary->GetCooldown();
                bFired = true;
            }
            if (pState->mNextEffectTime == 0) {
                pState->mNextEffectTime = tNow + mReattackDelay;
                pState->mNextFireTime = tNow + pSecondary->GetCooldown();
            }

            if (tNow > pState->mNextFireTime - 1000) {
                if (pState->mnFlag == 1 && pTurret->mAirRaidEffect.mpObject == 0) {
                    cEffectManager* pEffects = EffectsManagerPtr();
                    if (pEffects->CreateEffect((void*)0xc19e6439, 0,
                                               pTurret->mAirRaidEffect.AsPPTypeParam())) {
                        XformMsg msg;
                        msg.mFlags |= 2;
                        msg.mSeq += 1;
                        Matrix3Rows orientation;
                        Vec3f nFacing;
                        Vec3f nUp;
                        Vec3_Normalize(&nFacing, pTurret->mSpatial.GetPosition());
                        OrthogonalVector(&nUp, &nFacing);
                        Vec3_Normalize(&nUp, &nUp);
                        Matrix3FromFacingAndUp(&orientation, &nFacing, &nUp);
                        msg.mOrientation = orientation;
                        msg.SetPosition(pTurret->mSpatial.GetPosition());
                        pTurret->mAirRaidEffect.mpObject->SetXform(&msg);
                        pTurret->mAirRaidEffect.mpObject->e08(0);
                    }
                }
            } else if (tNow > pState->mNextEffectTime) {
                cVisualEffect* pEffect = pTurret->mAirRaidEffect.mpObject;
                if (pEffect != 0 && pEffect->IsActive())
                    pEffect->e0c(0);
                cVisualEffect* pOld = pTurret->mAirRaidEffect.mpObject;
                if (pOld != 0) {
                    pTurret->mAirRaidEffect.mpObject = 0;
                    pOld->Release();
                }
            }

            if (tNow > pState->mNextFireTime) {
                pState->mNextEffectTime = tNow + mReattackDelay;
                pState->mNextFireTime = tNow + pSecondary->GetCooldown();
                pState->mnFlag = (pState->mnFlag == 0);
            }

            cTurret* pCreature = FindNearestCreature(
                *pTarget->mBody.GetPosition(), bAttack, bMission);
            if (pCreature != 0 && !pCreature->AcceptTarget(1)) {
                Vec3f creaturePos = *pCreature->mSpatial.GetPosition();
                Vec3f toCreature = creaturePos - mCityCenter;
                Vec3f nToCreature;
                Vec3f nCenter;
                bool bFacing =
                    Dot3(Vec3_Normalize(&nToCreature, &toCreature),
                         Vec3_Normalize(&nCenter, &mCityCenter)) >= 0.0f;
                pTurret->FaceAtTarget(&pCreature->mTargetPos);

                Vec3f* pTurretPos = pCombatant->GetSpatial()->GetPosition();
                float dx = creaturePos.x - pTurretPos->x;
                float dy = creaturePos.y - pTurretPos->y;
                float dz = creaturePos.z - pTurretPos->z;
                float fDist = sqrtf(dz * dz + dy * dy + dx * dx);

                bool bAim;
                if (fDist <= pPrimary->GetMinRange()
                    || fDist >= pPrimary->GetMaxRange()) {
                    bAim = fDist < pSecondary->GetMaxRange()
                           && tNow < pState->mNextEffectTime && bFacing
                           && pState->mnFlag == 0;
                } else {
                    bAim = bFired && bFacing;
                }
                if (bAim)
                    pAim = &pCreature->mTargetPos;
            }
        }
        pCombatant->SetTarget(pAim);
        it.Increment();
    }
    return 1;
}

} // namespace SP
