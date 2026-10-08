// Slice s00d80a50 -- SP::MOVE_WITHIN_RANGE_Tick (0x00d80a50, 1985 bytes): the creature behavior-tree tick
// that walks a creature towards its target (a fruit/creature/avatar object) until it is within range.
// State block (names are Claude-coined; layout from the asm):
//   +0x00 idx      index handed to the creature's vf+0xb4 (tuning lookup)
//   +0x04 mTarget1 ARC<object>; +0x08 mSlot (bit index into target1's +0x48 bit mask)
//   +0x0c mTarget2 ARC<object>; +0x10 mbMoving
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as the other SP::*_Tick behaviors).
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };

#define PV(n) virtual void pv##n();

// Locomotive object (the creature embeds one at +0xc0; the avatar-side lookup returns another).
struct Loco {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3* GetPosition();                            // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a)
    PV(1b) PV(1c)
    virtual float GetFootprintRadius();                           // +0x74
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(3a)
    virtual void StopMoving();                                    // +0xec
    bool IsNearGoal();                                            // 0x00c42e20
    char* GetNavState();                                          // 0x00c41ec0 (+0x64 float, +0x70 flags)
};
struct LocoObj : Loco {                                           // as returned by the avatar lookup
    char pad04[0x75 - 4];
    bool mFlag75;                                                 // +0x75
    const Vec3* GetVelocity();                                    // 0x00d20610 (cLocomotiveObject::GetVelocity)
};

// Avatar-side lookup object.
struct Avatar {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual LocoObj* Find(uint32_t id);                           // +0x5c
};

// Object embedded at target2+0x34 (bounding-box holder).
struct BoxHolder {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a)
    virtual const float* GetBox(float* out);                      // +0x6c  (6 floats: min xyz, max xyz)
    PV(1c)
    virtual float GetRadius();                                    // +0x74
};

struct TargetObj2 {                                               // target2 (creature-like)
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDead();                                        // +0x2c
    char pad04[0x34 - 4];
    BoxHolder mBox;                                               // +0x34
    char pad38[0x16c - 0x38];
    int mState;                                                   // +0x16c
};

struct TargetObj1 {                                               // target1 (fruit-like)
    char pad00[0x10];
    Vec3 mPos;                                                    // +0x10
    char pad1c[0x48 - 0x1c];
    uint64_t mSlotMask;                                           // +0x48
    char pad50[0x6c - 0x50];
    float mRadius;                                                // +0x6c
};

struct ARC1 {
    TargetObj1* p;
    void Assign(TargetObj1* o);      // 0x00b5f950
};
struct ARC2 {
    TargetObj2* p;
    void Assign(TargetObj2* o);      // 0x00b5f950
};

struct MemBlock {
    uint32_t idx;       // +0x00
    ARC1     t1;        // +0x04
    int      slot;      // +0x08
    ARC2     t2;        // +0x0c
    bool     moving;    // +0x10
};

struct Tuning {                                                   // creature tuning (vf+0xb4 result)
    char pad00[0xc];
    int mKind;                                                    // +0x0c
    char pad10[0xa8 - 0x10];
    float mA8;                                                    // +0xa8
    char padac[0xf4 - 0xac];
    float mF4;                                                    // +0xf4
    float GetBound(bool b);                                       // 0x004d3d70
};

// Result of PlayIdleAnimation: a finder object (+0x2c) and a slot (+0x10).
struct IdleFinder {
    PV(00) PV(01) PV(02)
    virtual void* Find(uint32_t id);                              // +0x0c
};
struct IdleResult {
    char pad00[0x10];
    int mSlot;                                                    // +0x10
    char pad14[0x2c - 0x14];
    IdleFinder* mFinder;                                          // +0x2c
};

// Behavior container at creature+0xb4c (+8 inside).
struct BehaviorTree {
    IdleResult* PlayIdleAnimation(uint32_t id, int a);            // 0x00bc96a0
    void ClearAll(uint32_t mask, int a);                          // 0x00bc98f0
};

struct Creature {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20)
    virtual void V84(int a, int b, int c);                        // +0x84
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    virtual Tuning* GetTuning(uint32_t idx);                      // +0xb4
    char pad_04[0xc0 - 4];
    Loco mLoco;                                                   // +0xc0
    char pad_c4[0xb4c - 0xc4];
    char* mpBehavior;                                             // +0xb4c
    char pad_b50[0xb58 - 0xb50];
    uint32_t mFlagsB58;                                           // +0xb58

    Avatar* GetAvatar();                                          // 0x00c0ee60
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing, float speed, float speed2);  // 0x00c1c5c0
    void FUN_00c03190(int a, int b, float f, int c, int d, void* e, int g);   // 0x00c03190
    void FUN_00c03c20(uint32_t idx);                              // 0x00c03c20
};

struct PlanetModelT {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* in);  // 0x00b815a0
    Vec3* FUN_00b81630(Vec3* out, const Vec3* in);                // 0x00b81630
};

extern const float kFltMax;                                       // 0x0147c030
extern const Vec3 kDefaultTarget;                                 // 0x0169f03c
PlanetModelT* PlanetModel();                                      // 0x00b3d350 (cdecl)
Vec3* normalized_safe(Vec3* out, const Vec3* in);                 // 0x00449c20 (cdecl)
float DistanceBetweenBodies(const Vec3* a, float ra, const Vec3* b, float rb, int flag);  // 0x00d99a60 (cdecl)
float FUN_00d38a30(int a, Creature* c);                           // 0x00d38a30 (cdecl)
float FUN_00d99ac0(Loco* loco, Loco* other, int flag);            // 0x00d99ac0 (cdecl)
void  __stdcall FUN_00b02b90(Vec3* out, int idx);                 // 0x00b02b90 (stdcall)
#undef PV

namespace nSPBehaviorTree { struct behavior_memory_block { uint32_t Data[32]; }; }
using nSPBehaviorTree::behavior_memory_block;

// @ 0x00d80a50  SP::MOVE_WITHIN_RANGE_Tick
bool MOVE_WITHIN_RANGE_Tick(void* pSelf, double, uint32_t flags, uint32_t, behavior_memory_block* pMemory,
                            behavior_memory_block*, float dt)
{
    Creature* c = (Creature*)pSelf;
    MemBlock* m = (MemBlock*)pMemory;
    Loco* loco = &c->mLoco;

    LocoObj* avatarObj = 0;
    if (Avatar* av = c->GetAvatar()) avatarObj = av->Find(0x1186577);

    if (!m->t1.p && !m->t2.p && !(avatarObj && avatarObj->mFlag75)) return false;

    if (m->t2.p) {
        if (m->t2.p->mState == 6) return false;
        if (m->t2.p->IsDead()) return false;
    }
    if (m->t1.p) {
        if (((1ULL << m->slot) & m->t1.p->mSlotMask) == 0) return false;
    }

    IdleResult* idle = ((BehaviorTree*)(c->mpBehavior + 8))->PlayIdleAnimation(0x20, 0);
    if (idle) {
        TargetObj2* f2 = idle->mFinder ? (TargetObj2*)idle->mFinder->Find(0x2c9cc8e) : 0;
        bool found = false;
        if (f2) {
            if (m->t2.p != f2) m->t2.Assign(f2);
            found = true;
        } else if (idle->mFinder) {
            TargetObj1* f1 = (TargetObj1*)idle->mFinder->Find(0x581147f);
            if (f1) {
                if (m->t1.p != f1 || m->slot != idle->mSlot) {
                    m->t1.Assign(f1);
                    m->slot = idle->mSlot;
                }
                found = true;
            }
        }
        if (found) c->V84(0, 0, 0);
    }

    Tuning* tune = c->GetTuning(m->idx);

    float speed = 0.01f;
    float slack = 0.0f;
    float minDist = 0.0f;
    float radius = 0.0f;
    float dist;
    Vec3 target = { 0.0f, 0.0f, 0.0f };   // (overwritten from constants below)
    Vec3 dir;
    Vec3 tmp;
    target = kDefaultTarget;

    if (m->t2.p) {
        if (m->t2.p->mState != 0) {
            float box[6];
            const float* r = m->t2.p->mBox.GetBox(box);
            target.x = (r[0] + r[3]) * 0.5f;
            target.y = (r[4] + r[1]) * 0.5f;
            target.z = (r[5] + r[2]) * 0.5f;
            radius = m->t2.p->mBox.GetRadius();
        }
        dist = DistanceBetweenBodies(&target, radius, loco->GetPosition(), loco->GetFootprintRadius(), 1);
        const Vec3* p = loco->GetPosition();
        float dx = p->x - target.x, dy = p->y - target.y, dz = p->z - target.z;
        float inv = 1.0f / sqrtf((dx * dx + (dy * dy + dz * dz)) + 1e-8f);
        dir.x = dx * inv; dir.y = dy * inv; dir.z = dz * inv;
    } else if (m->t1.p) {
        FUN_00b02b90(&target, m->slot);
        target = *PlanetModel()->DirectionToSurfacePosition(&tmp, &target);
        radius = 0.45f;
        dist = DistanceBetweenBodies(&target, radius, loco->GetPosition(), loco->GetFootprintRadius(), 1);
        TargetObj1* t1 = m->t1.p;
        Vec3 d = { target.x - t1->mPos.x, target.y - t1->mPos.y, target.z - t1->mPos.z };
        dir = *normalized_safe(&tmp, &d);
        speed = loco->GetFootprintRadius() * 0.25f;
        float dx = target.x - t1->mPos.x, dy = target.y - t1->mPos.y, dz = target.z - t1->mPos.z;
        float d2 = (dz * dz + dy * dy) + dx * dx;
        float R = m->t1.p->mRadius;
        slack = (R * R > d2) ? R - sqrtf(d2) : 0.0f;
    } else {
        float sc = FUN_00d38a30(0, c);
        dist = FUN_00d99ac0(loco, avatarObj, tune->mKind != 1);
        slack = (tune->mF4 + tune->mA8) * sc;
        minDist = tune->GetBound((c->mFlagsB58 >> 9) & 1);
        target = *avatarObj->GetPosition();
        radius = avatarObj->GetFootprintRadius();
        const Vec3* p = loco->GetPosition();
        Vec3 d = { p->x - target.x, p->y - target.y, p->z - target.z };
        dir = *normalized_safe(&tmp, &d);
    }

    bool move;
    if (m->t1.p) {
        move = !(m->moving && loco->IsNearGoal());
    } else {
        move = (slack + 0.01f < dist) || (dist < minDist - 0.01f);
    }

    if (move) {
        float f = loco->GetFootprintRadius() + radius + slack;
        if (PlanetModel()) {
            target.x = dir.x * f + target.x;
            target.y = dir.y * f + target.y;
            target.z = dir.z * f + target.z;
            target = *PlanetModel()->FUN_00b81630(&tmp, &target);
        }
        Vec3 face = { -dir.x, -dir.y, -dir.z };
        c->MoveToPointAndFacingAtSpeed(2, &target, &face, speed, speed + 0.1f);
        m->moving = true;
        if (m->t1.p) *(float*)(loco->GetNavState() + 0x64) = 0.89f;
        Avatar* av = c->GetAvatar();
        if (av) {
            LocoObj* o = av->Find(0x116dd1b);
            if (o) {
                const Vec3* v = o->GetVelocity();
                if ((v->x * v->x + v->y * v->y) + v->z * v->z > 0.01f)
                    *(uint32_t*)(loco->GetNavState() + 0x70) |= 1;
            }
        }
        return true;
    }

    loco->StopMoving();
    if (m->t2.p) {
        c->FUN_00c03190(1, 0, kFltMax, 0, 0, m->t2.p, 0);
    } else if (m->t1.p) {
        c->FUN_00c03190(1, 0, kFltMax, m->slot, 0, m->t1.p, 0);
    } else if (tune->mKind == 1) {
        c->FUN_00c03c20(m->idx);
    }
    ((BehaviorTree*)(c->mpBehavior + 8))->ClearAll(0x100000, 0);
    return false;
}
