// Slice s00d7ff20: SP::ATTACK_Tick, the animal behavior-tree "attack" tick (SPAnimalBehaviorTrees.cpp).
// /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
//
// Each tick: pick the current attack (from the behavior tree or cCreatureBase::mCurrentAttackIdx), compute the
// ability's engagement ranges, then either chase the target (no attack queued) or lead the target, snap the goal
// to the planet surface, face it, and fire the attack when in range and facing it (dot > 0.85).
#include "types.h"
#include <math.h>

namespace nSPBehaviorTree { struct behavior_memory_block { uint32_t Data[32]; }; }
using nSPBehaviorTree::behavior_memory_block;

namespace SP {

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    static const Vector3 ZERO;                                   // 0x169f03c
};

inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline bool NotEqual(const Vector3& a, const Vector3& b) { return a.x != b.x || a.y != b.y || a.z != b.z; }

// Out-of-line copies of the same inlines (cl's inline budget for this function ran out on these call sites).
bool  Vector3_NotEqual(const Vector3& a, const Vector3& b);      // 0x41dd30
float Dot3(const Vector3& a, const Vector3& b);                   // 0x455cc0
Vector3* Vector3_Normalize(Vector3* out, const Vector3* in);     // 0x436ce0
Vector3* normalized_safe(Vector3* out, const Vector3* in);       // 0x449c20

struct ATTACK_memory_block {
    uint32_t mAttackIdx;      // +0x0
    float    mTimer;          // +0x4
    bool     mAttackRoar;     // +0x8
    bool     mDropItems;      // +0x9
    float    mChaseDistance;  // +0xc
};

struct cLocomotionGoal { uint32_t pad[0x5c / 4]; int mState; };   // +0x5c

#define PV(n) virtual void pv##n();
struct cSpatialObject {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                         // 0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual Vector3 GetDirection();                               // 0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetFootprintRadius();                           // 0x74
};

struct cLocomotiveObject : cSpatialObject {
    const Vector3& GetVelocity();                                 // 0xd20610
    bool IsNearGoal();                                            // 0xc42e20
    cLocomotionGoal* GetGoal();                                   // 0xc41ec0
};

struct cCombatant {
    PV(00) PV(01)
    virtual cSpatialObject* ToSpatialObject();                    // 0x08
};

struct cCreatureAbility {
    uint32_t pad00[2];
    int   mType;              // +0x08
    uint32_t pad0c[(0xa8 - 0xc) / 4];
    float mRange;             // +0xa8
    uint32_t padac[(0xf4 - 0xac) / 4];
    float mRushingRange;      // +0xf4
    float GetBound(bool b);                                       // 0x4d3d70 (TuningObj::GetBound)
};

struct BehaviorNode { uint32_t pad[3]; uint32_t mAttackIdx; };  // +0xc
struct cBehaviorTree { BehaviorNode* PlayIdleAnimation(uint32_t mask, uint32_t b); };   // 0xbc96a0
struct cBehaviorTreeData { uint32_t pad[2]; cBehaviorTree mTree; };                    // +8

struct cSPTimer { uint64_t GetElapsedTime(); };                   // 0xbc3190

struct cSPCreatureBase {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    virtual cCreatureAbility* GetAbility(int index);              // 0xb4

    uint32_t pad004[(0xc0 - 0x4) / 4];
    cLocomotiveObject mLoco;                                      // +0xc0
    uint32_t pad0c4[(0xb4c - 0xc4) / 4];
    cBehaviorTreeData* mpBehaviorTreeData;                        // +0xb4c
    uint32_t padb50[2];
    uint32_t mGeneralFlags;                                       // +0xb58
    uint32_t padb5c[(0xb78 - 0xb5c) / 4];
    float mNoAttackTimer;                                         // +0xb78
    uint32_t padb7c[(0xe8c - 0xb7c) / 4];
    uint32_t mCurrentAttackIdx;                                   // +0xe8c
    uint32_t pade90[(0xfc0 - 0xe90) / 4];
    cSPTimer mAttackTimer;                                        // +0xfc0

    cCombatant* GetTarget();                                      // 0xc0ee60
    cSPCreatureBase* GetTargetAsCreature();                       // 0xc0ee70
    float FUN_00c0cfa0(int a, int b);                             // 0xc0cfa0
    void MoveToPointAndFacingAtSpeed(int mode, const Vector3* p, const Vector3* facing, float a, float b);  // 0xc1c5c0
    void PlayAnimation(uint32_t id, int a, int b);                // 0xc12190
    bool AnimationFinished(uint32_t id);                          // 0xc123f0
    bool WaitForAnimEventOrEnd(uint32_t ev, void* p, int a, int b, int c);   // 0xc14ef0
    void FUN_00c19940(int a);                                     // 0xc19940
    void FUN_00c14750(int a);                                     // 0xc14750
    void Attack(uint32_t idx, int* outAnim);                      // 0xc1e460
};
#undef PV

struct cPlanetModel { Vector3* FUN_00b81630(Vector3* out, const Vector3* p); };   // 0xb81630
cPlanetModel* PlanetModel();                                      // 0xb3d350

void* FUN_00d99470(cSPCreatureBase* c);                           // 0xd99470
float FUN_00d38a30(int which, cSPCreatureBase* c);                // 0xd38a30
float FUN_00d99a60(const Vector3& a, float ra, const Vector3& b, float rb, bool f);   // 0xd99a60
cSPCreatureBase* WatchMemoryBlock(BehaviorNode* n);               // 0xd999d0
extern uint32_t g_AttackDropEvent;                                // 0x1590c30
extern float g_AttackRoarDelay;                                   // 0x1687a34

inline bool TestBit(uint32_t v, uint32_t n) { return (v >> n) & 1; }
inline const float& Max(const float& a, const float& b) { return a < b ? b : a; }

// =====================================================================
// @ 0x00d7ff20  SP::ATTACK_Tick
// =====================================================================
bool ATTACK_Tick(void* pSelf, double, uint32_t, uint32_t, behavior_memory_block* pMemory,
                 behavior_memory_block*, float dt)
{
    cSPCreatureBase* creature = (cSPCreatureBase*)pSelf;
    // The memory block is always reached through the parameter (its address is taken below), so it is
    // re-read after every store, as in the original.
#define mem ((ATTACK_memory_block*)pMemory)

    cCombatant* target = creature->GetTarget();
    if (!target) return false;
    cSPCreatureBase* targetCreature = creature->GetTargetAsCreature();
    if (targetCreature && !FUN_00d99470(targetCreature)) return false;

    BehaviorNode* node = creature->mpBehaviorTreeData->mTree.PlayIdleAnimation(0x10, 0);
    if (node) mem->mAttackIdx = node->mAttackIdx;

    uint32_t attackIdx = mem->mAttackIdx;
    if (attackIdx == (uint32_t)-1) attackIdx = creature->mCurrentAttackIdx;
    cCreatureAbility* ability = (attackIdx != (uint32_t)-1) ? creature->GetAbility(attackIdx) : 0;

    const Vector3& targetPos = target->ToSpatialObject()->GetPosition();
    cLocomotiveObject* loco = &creature->mLoco;
    const Vector3& myPos = loco->GetPosition();
    float targetRadius = target->ToSpatialObject()->GetFootprintRadius();
    float myRadius = loco->GetFootprintRadius();
    float radiusSum = myRadius + targetRadius;
    float scale = FUN_00d38a30(0, creature);

    float minRange, maxRange, bound;
    if (ability) {
        bool b = TestBit(creature->mGeneralFlags, 9);
        maxRange = (ability->mRushingRange + ability->mRange) * scale;
        minRange = ability->mRange * scale;
        bound = ability->GetBound(b);
    } else {
        maxRange = 0.0f;
        minRange = 0.0f;
        bound = 0.0f;
    }
    float nearDist = minRange + radiusSum;
    float farDist = nearDist + myRadius;

    if (mem->mAttackIdx != (uint32_t)-1) {
        float dist = FUN_00d99a60(targetPos, targetRadius, myPos, myRadius, true);
        Vector3 goal(targetPos);
        if (targetCreature) {
            float speed = creature->FUN_00c0cfa0(2, 0);
            if (speed > 1.5258789e-05f && dist <= FUN_00d38a30(5, creature)) {
                Vector3 diff = targetPos - myPos;
                Vector3 dir;
                normalized_safe(&dir, &diff);
                Vector3 desired(dir.x * speed, dir.y * speed, dir.z * speed);
                const Vector3& vel = targetCreature->mLoco.GetVelocity();
                Vector3 rel(vel.x - desired.x, vel.y - desired.y, vel.z - desired.z);
                float len = sqrtf(rel.x * rel.x + rel.y * rel.y + rel.z * rel.z);
                if (len > 0.0f) {
                    float t = dist / len;
                    const Vector3& v = targetCreature->mLoco.GetVelocity();
                    goal.x += v.x * t;
                    goal.y += v.y * t;
                    goal.z += v.z * t;
                }
            }
        }
        Vector3 surface;
        goal = *PlanetModel()->FUN_00b81630(&surface, &goal);

        Vector3 toGoal = goal - myPos;
        float invLen = 1.0f / sqrtf(toGoal.x * toGoal.x + toGoal.y * toGoal.y + toGoal.z * toGoal.z + 1e-08f);
        Vector3 facing(invLen * toGoal.x, toGoal.y * invLen, toGoal.z * invLen);
        creature->MoveToPointAndFacingAtSpeed(2, &goal, &facing, nearDist, farDist);

        if (targetCreature) {
            cLocomotiveObject* targetLoco = &targetCreature->mLoco;
            if (NotEqual(targetLoco->GetVelocity(), Vector3::ZERO)) {
                Vector3 n;
                const Vector3* pn = normalized_safe(&n, &targetLoco->GetVelocity());
                Vector3 d = loco->GetDirection();
                if (Dot(d, *pn) > 0.0f)
                    loco->GetGoal()->mState = 2;
            }
        }

        Vector3 toTarget = targetPos - myPos;
        float inv = 1.0f / sqrtf(toTarget.x * toTarget.x + toTarget.y * toTarget.y + toTarget.z * toTarget.z);
        Vector3 fwd(inv * toTarget.x, toTarget.y * inv, toTarget.z * inv);
        facing = fwd;
        float invUp = 1.0f / sqrtf(myPos.x * myPos.x + myPos.y * myPos.y + myPos.z * myPos.z);
        Vector3 up(myPos.x * invUp, myPos.y * invUp, myPos.z * invUp);
        float k = Dot(up, fwd);
        Vector3 tangent(fwd.x - up.x * k, fwd.y - up.y * k, fwd.z - up.z * k);
        if (NotEqual(tangent, Vector3::ZERO)) {
            Vector3 t;
            facing = *Vector3_Normalize(&t, &tangent);
        }

        mem->mChaseDistance = Max(mem->mChaseDistance, minRange);

        if (mem->mDropItems) {
            if (creature->WaitForAnimEventOrEnd(g_AttackDropEvent, &pMemory, -1, 0, 1)
                || creature->AnimationFinished(0x3a74a0b))
                creature->FUN_00c19940(1);
            if (creature->AnimationFinished(0x3a74a0b)) {
                mem->mDropItems = false;
                creature->FUN_00c14750(0);
                return true;
            }
            creature->PlayAnimation(0x3a74a0b, 1, -1);
            return true;
        }

        if (dist <= maxRange && dist >= bound) {
            Vector3 d = loco->GetDirection();
            if (Dot(d, facing) > 0.85f) {
                creature->Attack(mem->mAttackIdx, 0);
                mem->mAttackIdx = (uint32_t)-1;
                if (node) node->mAttackIdx = (uint32_t)-1;
                if (ability->mType == 0x1d) return false;
                return true;
            }
        }

        if (mem->mAttackRoar && creature->mNoAttackTimer <= 0.0f) {
            if ((float)creature->mAttackTimer.GetElapsedTime() * 0.001f > g_AttackRoarDelay) {
                if (creature->AnimationFinished(0x2481df9)) {
                    mem->mAttackRoar = false;
                    creature->FUN_00c14750(0);
                    return true;
                }
                creature->PlayAnimation(0x2481df9, 1, -1);
                return true;
            }
        }

        if (loco->IsNearGoal()) {
            creature->PlayAnimation(0x26ede51, 1, -1);
            return true;
        }
    } else {
        if (creature->mCurrentAttackIdx != (uint32_t)-1) {
            const Vector3& tp = target->ToSpatialObject()->GetPosition();
            const Vector3& mp = loco->GetPosition();
            Vector3 diff = tp - mp;
            Vector3 dir;
            creature->MoveToPointAndFacingAtSpeed(2, &tp, Vector3_Normalize(&dir, &diff), nearDist, farDist);
            if (!targetCreature) return true;
            cLocomotiveObject* targetLoco = &targetCreature->mLoco;
            if (!Vector3_NotEqual(targetLoco->GetVelocity(), Vector3::ZERO)) return true;
            Vector3 n;
            if (Dot3(loco->GetDirection(), *normalized_safe(&n, &targetLoco->GetVelocity())) > 0.0f)
                loco->GetGoal()->mState = 2;
            return true;
        }

        BehaviorNode* watch = creature->mpBehaviorTreeData->mTree.PlayIdleAnimation(2, 0);
        if (node) {
            cSPCreatureBase* watched = WatchMemoryBlock(watch);
            if (watched && watched == targetCreature) return false;
        }

        mem->mTimer -= dt;
        if (mem->mTimer < 0.0f) return false;

        if (creature->AnimationFinished(0) && creature->mCurrentAttackIdx == (uint32_t)-1) {
            if (loco->IsNearGoal())
                creature->PlayAnimation(0x26ede51, 1, -1);
            else
                creature->PlayAnimation(0x39e477b, 1, -1);
        }

        Vector3 diff = targetPos - myPos;
        float chase = mem->mChaseDistance + radiusSum;
        float len = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
        if ((len > chase && loco->GetGoal()->mState != 0)
            || (len > chase + 1.0f && loco->GetGoal()->mState == 0)) {
            float inv = 1.0f / len;
            Vector3 facing(inv * diff.x + 1.5258789e-05f, diff.y * inv + 1.5258789e-05f, diff.z * inv + 1.5258789e-05f);
            creature->MoveToPointAndFacingAtSpeed(2, &targetPos, &facing, chase, chase);
        } else {
            return true;
        }
    }

    creature->PlayAnimation(0x39e477b, 1, -1);
    return true;
#undef mem
}

} // namespace SP
