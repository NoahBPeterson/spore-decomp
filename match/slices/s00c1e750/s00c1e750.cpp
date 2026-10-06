// Slice s00c1e750 -- SP::cSPCreatureBase::UpdateAttack (0x00c1e750, 3623 bytes).
// ModAPI: Simulator::cCreatureBase::func68h(float) ("called by Update"), vtable slot 0x68.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the local fixed_vector has no EH frame).
//
// Per-frame update of the creature's current attack (mCurrentAttackIdx / mCurrentAttackAnimId):
//  * Rushing (the attack animation is the ability's rushing animation): consume the rush
//    distance by the distance travelled this frame; when the target is reached (targeted charge)
//    or the distance is used up, stop and play the attack animation (or cancel). Otherwise keep
//    accelerating towards the target / facing direction, and, for rushes that do damage, sweep the
//    model world in front of the creature and knock back every new creature hit (once per rush).
//  * Attacking: wait for the animation's hit event. On the event: start the cool-down, mark the
//    ability state, and either throw a spear (tribal spear throw), apply the ability's effect
//    (effect kinds 1 and 3), or deal the hit (single target, or every creature near the target
//    for area kinds) and notify the behavior/tribe tracker. Until then decide hit/miss/raze for
//    the animation from the range to the target.
//  * When the animation is over the attack is reset and the list of rush victims cleared.
// Member names from ModAPI cCreatureBase.h / cCreatureAbility.h / cCombatant.h / cSpatialObject.h.
#include "types.h"
#include <stddef.h>
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define CHECK_OFFSET(T, m, off) typedef char PVCAT(check_, __COUNTER__)[offsetof(T, m) == (off) ? 1 : -1]

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float f) { return Vector3(a.x * f, a.y * f, a.z * f); }

struct Quaternion { float x, y, z, w; };

struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    Vector3 GetCenter() const
    {
        return Vector3((mMin.x + mMax.x) * 0.5f, (mMin.y + mMax.y) * 0.5f, (mMin.z + mMax.z) * 0.5f);
    }
};

Vector3 normalized_safe(const Vector3& v);                                        // 0x00449c20
float VectorLength(const Vector3& v);                                             // 0x0040ae50
namespace checkerlib {
Vector3 QuaternionVectorTransform(const Quaternion& q, const Vector3& v);         // 0x0099c1a0
}

extern Vector3 sZeroVector;          // 0x0168d910 (Vector3::ZERO, this TU's copy)
extern float sAttackRangeSlack;      // 0x01582ef0 (0.15)
extern float sAttackCooldown;        // 0x01582e00 (30.0)
extern uint32_t sAttackHitEventID;   // 0x0157205c
extern char sStopRushMessage;        // 0x016e42d0

enum {
    kTribeTool       = 0x018c8f0c,
    kTribeHut        = 0x01e4daae,
    kCreatureAnimal  = 0x018eb45e,
    kCreatureCitizen = 0x018eb4b7,
    kCreatureBaseType = 0xce9f6639,
};

// Animation "hit result" codes written to the animated creature (four characters, little endian).
enum {
    kAnimResultHit  = 0x00746968,   // "hit"
    kAnimResultHitH = 0x68746968,   // "hith"
    kAnimResultRaze = 0x657a6172,   // "raze"
    kAnimResultMiss = 0x7373696d,   // "miss"
};

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t nLimit);                                // 0x00a68fb0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;                          // 0x01601760

namespace SP {

class cGameData;
class cSPCreatureBase;

class cSpatialObject {
public:
    PV8 PV2 PV                                         // 0x00-0x28
    virtual const Vector3& GetPosition();              // 0x2c
    PV2
    virtual void SetPosition(const Vector3& v);        // 0x38
    PV
    virtual void SetScale(float scale);                // 0x40
    PV4 PV
    virtual bool IsPlayerOwned();                      // 0x58
    virtual Vector3 GetDirection();                    // 0x5c
    PV2 PV
    virtual BoundingBox GetBoundingBox();              // 0x6c
    PV
    virtual float GetFootprintRadius();                // 0x74
};

struct ObjectVector { cGameData** mpBegin; cGameData** mpEnd; };

class cLocomotiveObject : public cSpatialObject {
public:
    PV16 PV4                                           // 0x78-0xc4
    virtual float GetDesiredSpeed();                   // 0xc8

    const Vector3& GetVelocity();                      // 0x00d20610
    void SetVelocity(const Vector3& v);                // 0x00c41d60
    void AddVelocity(const Vector3& v, int flags);     // 0x00c446d0
    ObjectVector* GetNearbyObjects();                  // 0x00c420d0

    uint32_t pad004[(0x4e8 - 4) / 4];
};

class cCombatant {
public:
    PV2
    virtual cSpatialObject* ToSpatialObject();         // 0x08
    virtual cGameData* ToGameData();                   // 0x0c
    virtual uint32_t GetPoliticalID();                 // 0x10

    uint32_t pad004[(0x578 - 4) / 4];
};

class cGameData {
public:
    PV8
    virtual uint32_t GetNounID();                      // 0x20
};

struct cCreatureAbility {
    uint32_t pad00[2];
    int mType;                       // 0x08
    uint32_t pad0c[(0x40 - 0x0c) / 4];
    float mRangedDamage;             // 0x40
    uint32_t pad44[(0x7c - 0x44) / 4];
    int mEffectKind;                 // 0x7c
    uint32_t pad80[(0xa8 - 0x80) / 4];
    float mRange;                    // 0xa8
    uint32_t padac;
    float mSpeed;                    // 0xb0
    uint32_t padb4[(0xf8 - 0xb4) / 4];
    uint32_t mRushingAnimationID;    // 0xf8
    float mRushingSpeed;             // 0xfc
    bool mbRushingTargetedCharge;    // 0x100
    bool mbRushingDoDamage;          // 0x101

    uint32_t GetAnimationID(int index);                // 0x004d3cd0
    float GetScaledValue(bool isBaby);                 // 0x004d3d70
};
CHECK_OFFSET(cCreatureAbility, mbRushingDoDamage, 0x101);

struct cAbilityState {
    bool mbHitEventDone;   // 0x00
    bool mbHit;            // 0x01
    int field_04;
    uint32_t field_08[2];
};

struct HitPoint { uint32_t pad[4]; Vector3 mPosition; uint32_t pad1c[(0x2bc - 0x1c) / 4]; };
struct cAnimModel {
    uint32_t pad00[0x18 / 4];
    Vector3 mPosition;                 // 0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    Quaternion mOrientation;           // 0x3c
    uint32_t pad4c[(0x2e4 - 0x4c) / 4];
    HitPoint* mpHitPoints;             // 0x2e4
};
struct cAnimatedCreature {
    uint32_t pad00[0x170 / 4];
    uint32_t mAttackResult;            // 0x170
    uint32_t pad174[2];
    cAnimModel* mpModel;               // 0x17c
};

struct cTribeTracker {
    void OnAttack(uint64_t flags, float amount, cGameData* pTarget);   // 0x00bc97f0
};
struct cBehaviorData {
    uint32_t pad00[2];
    cTribeTracker mTracker;            // 0x08
};

// eastl::vector<cSPCreatureBase*> (field_E98: creatures already hit by this rush)
template <class T> T* find(T* first, T* last, const T& value);     // 0x005c1cc0 (eastl::find instance)
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk
struct CreatureVector {
    cSPCreatureBase** mpBegin;
    cSPCreatureBase** mpEnd;
    cSPCreatureBase** mpCapacity;
    uint32_t mAllocator;
    void push_back(cSPCreatureBase* const& value);     // 0x00454860
    cSPCreatureBase** erase(cSPCreatureBase** first, cSPCreatureBase** last)
    {
        FUN_011e0744(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

// model-world query results: eastl::fixed_vector<cModel*, 16>
class cModelOwner {
public:
    PV2 PV
    virtual void* Cast(uint32_t typeID);               // 0x0c
};
struct cModel { uint32_t pad[0x64 / 4]; cModelOwner* mpOwner; };
struct ModelVector {
    cModel** mpBegin;
    cModel** mpEnd;
    cModel** mpCapacity;
    uint32_t mOverflowAllocator;
    cModel** mpPoolBegin;
    uint32_t mBufferPad;
    cModel* mBuffer[16];
    ModelVector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mBuffer + 16;
    }
    ~ModelVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
};
struct ModelFilter { uint32_t a, b, c, d, e; bool f; uint8_t g; };
class cGonzagoModelWorld {
public:
    PV8 PV4 PV
    virtual void GetModelsAlongSegment(const Vector3& start, const Vector3& end, ModelVector& dst,
                                       ModelFilter& filter, float radius);   // 0x34
};
cGonzagoModelWorld* GonzagoModelWorld();               // 0x00b3d520

struct cTerrainInfo { uint32_t pad[0x20 / 4]; int mWaterMode; };
cTerrainInfo* TerrainInfo();                           // 0x00b3d310

struct XformMsg {
    XformMsg();                                        // 0x00434040 XformMsg
    uint32_t pad00[4];
    float mScale;                                      // 0x10
    uint32_t pad14[8];
};
class cToolEffect {
public:
    PV8
    virtual void GetTransform(XformMsg* msg);          // 0x20
};
struct cTool { uint32_t pad[0x8c / 4]; cToolEffect* mpEffect; };

class cSPCreatureCitizen {
public:
    uint32_t GetToolID();                              // 0x00c22820
    bool IsCarryingTool();                             // 0x00c232c0
    void SetCurrentToolEffect(int effect, int index);  // 0x00c24f40
};

struct cSpearTarget { void Set(cCombatant* p); };       // 0x00ae6690
class cSpear {
public:
    PV16 PV2
    virtual void SetPoliticalID(uint32_t id);          // 0x48
    PV2 PV
    virtual void Launch(int a, int b, int c, int mode, cCombatant* pOwner);   // 0x58
    uint32_t pad004[(0x34 - 4) / 4];
    cSpatialObject mSpatial;                           // 0x34
    uint32_t pad038[(0x538 - 0x38) / 4];
    float mDamage;                                     // 0x538
    cSpearTarget mTarget;                              // 0x53c
    void SetInitialVelocity(const Vector3& v);         // 0x00cb7040
};
struct cGameNounManager {
    template <class T> T* CreateNoun();
};
template <> cSpear* cGameNounManager::CreateNoun<cSpear>();   // 0x00c0fcd0
cGameNounManager* NounManager();                       // 0x00b3d300

void* GameDataCast(cSPCreatureBase* obj, uint32_t noun);              // 0x00ac80d0
float GetAttackRangeScale(int unused, cSPCreatureBase* creature);     // 0x00d38a30
float DistanceBetween(cSpatialObject* a, cSpatialObject* b, bool edgeToEdge);   // 0x00d99ac0
struct cRushHandler { void OnRushStopped(void* msg); };                // 0x00aef3d0
cRushHandler* GetRushHandler(cLocomotiveObject* obj);                  // 0x00b532b0
bool IsTargetFleeing(cSPCreatureBase* creature);                       // 0x00c0b410
cLocomotiveObject* CombatantToLocomotive(cCombatant* p);               // 0x00bfc6c0
cSPCreatureBase* GameDataToCreature(cGameData* p);                     // 0x00ad26f0
void ComputeLaunchVelocity(const Vector3& start, const Vector3& target, float speed, Vector3& velocity, const Vector3* targetVelocity);   // 0x00c0ca00

class cSPCreatureBase {
public:
    PV8
    virtual uint32_t GetNounID();                      // 0x20
    PV8 PV2
    virtual uint32_t GetPoliticalID();                 // 0x4c
    PV4 PV2
    virtual void UpdateAttack(float deltaTime);        // 0x68
    PV16 PV
    virtual int GetAbilitiesCount();                   // 0xb0
    virtual cCreatureAbility* GetAbility(int index);   // 0xb4
    virtual bool funcB8h(cCombatant* target, int abilityIndex, Vector3* hitPosition);   // 0xb8

    void CancelAttackAnimation(int);                   // 0x00c073a0
    void SetAttackMode(int);                           // 0x00c14750
    void InterruptAnimation(uint32_t animID, int, int);    // 0x00c12310
    bool IsAnimationDone(uint32_t animID);             // 0x00c0e170
    bool WaitForAnimEventOrEnd(uint32_t eventID, int* pEventIndex, uint32_t animID, int, int);   // 0x00c14ef0
    cSPCreatureBase* GetTargetAsCreature();            // 0x00c0ee70
    void OnAttackHitEvent(uint32_t abilityIndex);      // 0x00c197a0
    void ApplyAbilityEffect(uint32_t abilityIndex, int eventIndex, cCombatant* target, int);   // 0x00c15470
    void SetStealthed(bool, bool);                     // 0x00c1aed0
    cTool* GetTool(uint32_t toolID);                   // 0x00c0dfb0
    bool GetBodyPartPosition(Vector3& dst, int part, bool, bool);   // 0x00c17a30

    bool IsBaby() const { return (mGeneralFlags >> 9) & 1; }

    uint32_t pad004[(0xc0 - 4) / 4];
    cLocomotiveObject mLoco;                           // 0xc0
    cCombatant mCombatant;                             // 0x5a8
    int field_B20;                                     // 0xb20
    uint32_t padb24[(0xb4c - 0xb24) / 4];
    cBehaviorData* field_B4C;                          // 0xb4c
    uint32_t padb50;
    cAnimatedCreature* mpAnimatedCreature;             // 0xb54
    uint32_t mGeneralFlags;                            // 0xb58
    uint32_t padb5c[(0xb78 - 0xb5c) / 4];
    float mNoAttackTimer;                              // 0xb78
    uint32_t padb7c[(0xc28 - 0xb7c) / 4];
    cAbilityState* mAbilityStates;                     // 0xc28 (fixed_vector<cAbilityState, 8>::mpBegin)
    uint32_t padc2c[(0xe7c - 0xc2c) / 4];
    cCombatant* mpCombatantTarget;                     // 0xe7c
    uint32_t pade80[3];
    uint32_t mCurrentAttackIdx;                        // 0xe8c
    uint32_t mCurrentAttackAnimId;                     // 0xe90
    float mRushDistanceLeft;                           // 0xe94
    CreatureVector mRushVictims;                       // 0xe98
};
CHECK_OFFSET(cSPCreatureBase, mLoco, 0xc0);
CHECK_OFFSET(cSPCreatureBase, mCombatant, 0x5a8);
CHECK_OFFSET(cSPCreatureBase, field_B20, 0xb20);
CHECK_OFFSET(cSPCreatureBase, mGeneralFlags, 0xb58);
CHECK_OFFSET(cSPCreatureBase, mAbilityStates, 0xc28);
CHECK_OFFSET(cSPCreatureBase, mpCombatantTarget, 0xe7c);
CHECK_OFFSET(cSPCreatureBase, mRushVictims, 0xe98);

// @ 0x00c1e750
void cSPCreatureBase::UpdateAttack(float deltaTime)
{
    if (mNoAttackTimer > 0.0f)
        mNoAttackTimer -= deltaTime;

    uint32_t attackIdx = mCurrentAttackIdx;
    if (attackIdx >= (uint32_t)GetAbilitiesCount())
        return;

    bool bIsBaby = IsBaby();
    cAbilityState* state = &mAbilityStates[attackIdx];
    cCreatureAbility* ability = GetAbility(attackIdx);
    bool bRushing = ability->mRushingAnimationID == mCurrentAttackAnimId;
    float rangeScale = GetAttackRangeScale(0, this);
    cCombatant* target = mpCombatantTarget;

    if (bRushing)
    {
        mRushDistanceLeft -= (mLoco.GetVelocity() * deltaTime).Length();
        float range = ability->mRange * rangeScale;
        float dist;
        if (target)
            dist = DistanceBetween(&mLoco, target->ToSpatialObject(), true);
        else
            dist = 0.0f;

        if ((ability->mbRushingTargetedCharge && range >= dist) || !(mRushDistanceLeft > 0.0f))
        {
            // reached the target (or ran out of rush distance): stop and strike
            mLoco.SetVelocity(sZeroVector);
            cRushHandler* handler = GetRushHandler(&mLoco);
            if (handler)
                handler->OnRushStopped(&sStopRushMessage);
            if (mRushDistanceLeft <= 0.0f)
            {
                CancelAttackAnimation(-1);
                SetAttackMode(0);
            }
            else
            {
                mCurrentAttackAnimId = ability->GetAnimationID(0);
                InterruptAnimation(mCurrentAttackAnimId, -1, 0);
            }
            bRushing = false;
        }
        else
        {
            if (target || !ability->mbRushingTargetedCharge)
            {
                float speed;
                if (TerrainInfo()->mWaterMode == 0)
                    speed = VectorLength(mLoco.GetVelocity());
                else
                    speed = mLoco.GetDesiredSpeed();
                if (ability->mRushingSpeed > speed)
                {
                    Vector3 dir = ability->mbRushingTargetedCharge
                        ? normalized_safe(target->ToSpatialObject()->GetPosition() - mLoco.GetPosition())
                        : mLoco.GetDirection();
                    float boost = ability->mRushingSpeed - speed;
                    Vector3 impulse(dir.x * boost, boost * dir.y, boost * dir.z);
                    mLoco.AddVelocity(impulse, 0);
                }
            }

            if (ability->mbRushingDoDamage)
            {
                // knock back every creature in front of us (once per rush)
                Vector3 dir = (ability->mbRushingTargetedCharge && target)
                    ? normalized_safe(target->ToSpatialObject()->GetPosition() - mLoco.GetPosition())
                    : mLoco.GetDirection();
                Vector3 center = mLoco.GetBoundingBox().GetCenter();
                Vector3 end(dir.x * 2.0f + center.x, dir.y * 2.0f + center.y, dir.z * 2.0f + center.z);
                float radius = mLoco.GetFootprintRadius();
                ModelVector models;
                cGonzagoModelWorld* world = GonzagoModelWorld();
                ModelFilter filter;
                filter.a = 0; filter.b = 0; filter.c = 0; filter.d = 0; filter.e = 0;
                filter.f = false; filter.g = 2;
                world->GetModelsAlongSegment(center, end, models, filter, radius);

                for (cModel** it = models.mpBegin; it != models.mpEnd; ++it)
                {
                    cModelOwner* owner = (*it)->mpOwner;
                    if (!owner)
                        continue;
                    cSPCreatureBase* other = (cSPCreatureBase*)owner->Cast(kCreatureBaseType);
                    if (!other)
                        continue;
                    if (mLoco.IsPlayerOwned() && other->mLoco.IsPlayerOwned())
                        continue;
                    if (target)
                    {
                        uint32_t targetPoliticalID = target->GetPoliticalID();
                        if (other->GetPoliticalID() != targetPoliticalID)
                            continue;
                    }
                    if (other->field_B20 == field_B20)
                        continue;
                    cSPCreatureBase* victim = other;
                    if (find(mRushVictims.mpBegin, mRushVictims.mpEnd, victim) != mRushVictims.mpEnd)
                        continue;
                    mRushVictims.push_back(victim);
                    funcB8h(&other->mCombatant, mCurrentAttackIdx, 0);
                    Vector3 push = normalized_safe(other->mCombatant.ToSpatialObject()->GetPosition()
                                                   - mLoco.GetPosition()) * 10.0f;
                    other->mLoco.AddVelocity(push, 0);
                }
            }
        }
    }
    else if (!state->mbHitEventDone)
    {
        float range = ability->mRange * rangeScale + sAttackRangeSlack;
        ability->GetScaledValue(IsBaby());
        int eventIndex = -1;
        if (!WaitForAnimEventOrEnd(sAttackHitEventID, &eventIndex, mCurrentAttackAnimId, 0, 1))
        {
            // before the hit event: decide what the animation shows
            bool bFleeing = !bIsBaby && IsTargetFleeing(GetTargetAsCreature());
            float dist;
            if (target)
                dist = DistanceBetween(&mLoco, target->ToSpatialObject(), true);
            else
                dist = 3.402823466e+38f;
            if (!bFleeing && target && range >= dist)
            {
                state->mbHit = true;
                uint32_t noun = target->ToGameData()->GetNounID();
                if (noun == kTribeTool || noun == kTribeHut)
                    mpAnimatedCreature->mAttackResult = kAnimResultRaze;
                else
                {
                    int type = ability->mType;
                    if (type == 0x2a || type == 0x3a || type == 0x3b || type == 0x2b)
                        mpAnimatedCreature->mAttackResult = kAnimResultHitH;
                    else
                        mpAnimatedCreature->mAttackResult = kAnimResultHit;
                }
            }
            else
            {
                state->mbHit = false;
                mpAnimatedCreature->mAttackResult = kAnimResultMiss;
            }
        }
        else
        {
            mNoAttackTimer = sAttackCooldown;
            state->mbHitEventDone = true;
            OnAttackHitEvent(mCurrentAttackIdx);
            if (!target)
                goto reset;

            int kind = GetAbility(mCurrentAttackIdx)->mEffectKind;
            if (ability->mType == 0x2b && mCurrentAttackAnimId == 0x02c39370)
            {
                // tribal spear throw
                Vector3 start = mLoco.GetBoundingBox().GetCenter();
                if (eventIndex != -1)
                {
                    cAnimModel* model = mpAnimatedCreature->mpModel;
                    start = checkerlib::QuaternionVectorTransform(model->mOrientation,
                                                                  model->mpHitPoints[eventIndex].mPosition)
                            + model->mPosition;
                }
                cLocomotiveObject* targetLoco = CombatantToLocomotive(target);
                cSpatialObject* targetObj = target->ToSpatialObject();
                Vector3 aim = targetObj->GetBoundingBox().GetCenter();
                cSPCreatureBase* targetCreature = GetTargetAsCreature();
                if (targetCreature)
                {
                    int parts[2] = { 2, 0 };
                    if (!targetCreature->GetBodyPartPosition(aim, parts[sMathRandom.RandomUint32Uniform(2)], true, false))
                        aim = targetObj->GetBoundingBox().GetCenter();
                }
                Vector3 velocity = sZeroVector;
                float speed = ability->mSpeed;
                ComputeLaunchVelocity(start, aim, speed, velocity,
                                      targetLoco ? &targetLoco->GetVelocity() : &sZeroVector);
                float damage = ability->mRangedDamage;
                cSpear* spear = NounManager()->CreateNoun<cSpear>();
                float scale = 1.0f;
                cSPCreatureCitizen* citizen = (cSPCreatureCitizen*)GameDataCast(this, kCreatureCitizen);
                if (citizen)
                {
                    cTool* tool = GetTool(citizen->GetToolID() + 0x2735300);
                    if (tool && tool->mpEffect)
                    {
                        XformMsg msg;
                        tool->mpEffect->GetTransform(&msg);
                        scale = msg.mScale;
                    }
                    citizen->SetCurrentToolEffect(0, -1);
                }
                spear->Launch(0, 0, 0, 2, &mCombatant);
                cSpatialObject* spearObj = &spear->mSpatial;
                spearObj->SetPosition(start);
                spear->SetPoliticalID(GetPoliticalID());
                spear->mTarget.Set(target);
                spear->mDamage = damage;
                spear->SetInitialVelocity(velocity);
                spearObj->SetScale(scale);
                SetStealthed(false, false);
            }
            else if (kind == 1 || kind == 3)
            {
                ApplyAbilityEffect(mCurrentAttackIdx, eventIndex, target, 0);
            }
            else if (state->mbHit)
            {
                uint64_t flags = 0;
                switch (GetNounID())
                {
                case kCreatureAnimal:
                    flags = 0x2000;
                    break;
                case kCreatureCitizen:
                    if (((cSPCreatureCitizen*)GameDataCast(this, kCreatureCitizen))->IsCarryingTool())
                        flags = 0x0008000000000000ULL;
                    break;
                }

                switch (kind)
                {
                case 0:
                    if (funcB8h(target, mCurrentAttackIdx, 0) && flags)
                        field_B4C->mTracker.OnAttack(flags, 10.0f, target->ToGameData());
                    break;
                case 2:
                case 3:
                {
                    ObjectVector* objects = mLoco.GetNearbyObjects();
                    for (cGameData** it = objects->mpBegin; it != objects->mpEnd; ++it)
                    {
                        cSPCreatureBase* other = GameDataToCreature(*it);
                        if (!other)
                            continue;
                        bool bInRange;
                        if (GetAbility(mCurrentAttackIdx)->mEffectKind == 2)
                            bInRange = range >= DistanceBetween(&other->mLoco, &mLoco, true);
                        else
                            bInRange = range >= DistanceBetween(&other->mLoco, target->ToSpatialObject(), true);
                        if (bInRange && funcB8h(&other->mCombatant, mCurrentAttackIdx, 0) && flags)
                            field_B4C->mTracker.OnAttack(flags, 10.0f, target->ToGameData());
                    }
                    break;
                }
                }
            }
            goto reset;
        }
    }

    if (!IsAnimationDone(mCurrentAttackAnimId) || bRushing)
        return;

reset:
    mCurrentAttackIdx = (uint32_t)-1;
    mCurrentAttackAnimId = (uint32_t)-1;
    mRushDistanceLeft = 0.0f;
    mRushVictims.clear();
}

}  // namespace SP
