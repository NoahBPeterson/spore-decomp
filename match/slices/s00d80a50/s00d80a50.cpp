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
    int  PlayAnimation(int id, int a, int b);                     // 0x00c12190
    bool AnimationFinished(int handle);                           // 0x00c12400
    bool AnimationFinishedZero(int handle);                       // 0x00c123f0
    void InterruptAnimation(int id, int a, int b);                // 0x00c12310
    void* CreateBodyEffectByIndex(int idx, int a, int b);         // 0x00c14f70
    bool DetachBodyEffectById(int id, int a);                     // 0x00c15150
    bool FUN_00c0d560(void* target, float a, float b);            // 0x00c0d560
    bool MoveToPointAtSpeed(int mode, Vec3* point, float a, float b); // 0x00c1c1d0
    bool FUN_00c0e0c0(int id);                                    // 0x00c0e0c0
    int  FUN_00c149c0(int id, void* target, int a, int b);        // 0x00c149c0
    void* GetHerd();                                              // 0x00c04590
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

// ===========================================================================
// Behavior ticks around the creature alert/move states.
// ===========================================================================

#define VTFN(p, slot)  ((*(void***)(p))[slot])
typedef int  (__thiscall* TCI)(void*);
typedef unsigned char (__thiscall* TCU8)(void*);
typedef void (__thiscall* TCV)(void*);

struct MoveMem
{
    int    state;                  // +0x00
    void*  target;                 // +0x04
    int    animHandle;             // +0x08
    int    animId;                 // +0x0c
    float  speed;                  // +0x10
};

struct AlertMem
{
    int    state;                  // +0x00
    int    effectIndex;            // +0x04
    int    pad08;                  // +0x08
    int    effectArg;              // +0x0c
    void*  effect;                 // +0x10 AutoRefCount payload
    int    pad14;                  // +0x14
    int    pad18;                  // +0x18
    uint8_t spawnEffect;           // +0x1c
    char   pad1d[3];
    float  timer;                  // +0x20
};

namespace nSPBehaviorTree
{
struct behavior_stimuli
{
    void GetAny();                 // 0x00d997e0
};
}
typedef nSPBehaviorTree::behavior_stimuli Stimuli;

struct StateObj
{
    int FUN_00ba3f90();            // 0x00ba3f90
};

struct EffectRef
{
    void* mpObject;
    void Assign(void* p);          // 0x00b5f950
};

void* FUN_00d99420(void* behavior, int id);       // 0x00d99420
void  FUN_00d996e0(void* a, void* stimuli);       // 0x00d996e0
int   FUN_00d99470(void* p);                      // 0x00d99470
void* __stdcall FUN_00b3d4c0(void* container, void* self, int id); // 0x00b3d4c0

// @ 0x00d81220
bool FUN_00d81220(void* pSelf, int, int, int, int, MoveMem* m, int, float)
{
    Creature* c = (Creature*)pSelf;
    if (m->target == 0 || *(uint8_t*)((char*)m->target + 0xa9) == 0)
        return false;
    if (((TCU8)VTFN(m->target, 0x2c / 4))(m->target) != 0)
        return false;

    if (m->state == 2)
        return false;

    if (m->state == 1) {
        if (m->animHandle == 0) {
            m->animHandle = c->PlayAnimation(m->animId, 1, -1);
            return true;
        }
        if (c->AnimationFinished(m->animHandle)) {
            m->state = 2;
            return true;
        }
        return true;
    }

    if (m->state == 0) {
        const Vec3* a = (const Vec3*)((TCI)VTFN((char*)m->target + 0x34, 0x2c / 4))((char*)m->target + 0x34);
        const Vec3* b = c->mLoco.GetPosition();
        Vec3 delta;
        delta.x = a->x - b->x;
        delta.y = a->y - b->y;
        delta.z = a->z - b->z;

        Vec3 face;
        normalized_safe(&face, &delta);
        c->MoveToPointAndFacingAtSpeed(2, a, &face, m->speed, 2.0f);
        if (c->mLoco.IsNearGoal())
            m->state = 1;
        return true;
    }

    return true;
}

// @ 0x00d81340
bool ALERT_Tick(void* pSelf, int, int, int, int, AlertMem* m, int, float dt)
{
    Creature* c = (Creature*)pSelf;

    switch (m->state) {
    case 0:
        if (((c->mFlagsB58 >> 9) & 1) == 0)
            c->mLoco.StopMoving();

        c->InterruptAnimation(0x265d18b, -1, 0);
        c->PlayAnimation(0x265d18c, 1, -1);

        if (m->spawnEffect != 0) {
            void* effect = c->CreateBodyEffectByIndex(m->effectIndex, m->effectArg, m->effectArg);
            ((EffectRef*)&m->effect)->Assign(effect);
        }
        m->state = 1;
        break;

    case 1:
        if (((BehaviorTree*)(c->mpBehavior + 8))->PlayIdleAnimation(0x800, 0) == 0) {
            m->timer -= dt;
            if (m->timer < 0.0f) {
                m->state = 2;
                return true;
            }
        }
        break;

    case 2:
        if (m->effect != 0) {
            c->DetachBodyEffectById(m->effectArg, 0);
            void* effect = m->effect;
            if (effect != 0) {
                m->effect = 0;
                ((TCV)VTFN(effect, 0x04 / 4))(effect);
            }
        }
        c->PlayAnimation(0x265d18d, 1, -1);
        m->state = 3;
        return true;

    case 3:
        if (c->AnimationFinishedZero(0))
            return false;
        break;
    }
    return true;
}

// Common prologue for the five stimulus-query conditions.
static void* StimulusObject(void* stimuli)
{
    void* obj = *(void**)((char*)stimuli + 4);
    if (obj != 0)
        return ((void* (__thiscall*)(void*, int))VTFN(obj, 0x5c / 4))(obj, 0xce9f6639);
    return 0;
}

// @ 0x00d81670
float FUN_00d81670(void* pSelf, int, int, int, void* stimuli, bool* out, int, void* data)
{
    Creature* c = (Creature*)pSelf;
    if (stimuli != 0)
        ((Stimuli*)stimuli)->GetAny();
    *out = true;

    void* a = FUN_00d99420(c->mpBehavior + 0x1d0, *(int*)((char*)data + 0x2d));
    FUN_00d996e0(a, stimuli);
    void* id = StimulusObject(stimuli);
    int result = FUN_00d99470(id);
    if (result == 0)
        return 0.0f;

    StateObj* state = (StateObj*)FUN_00b3d4c0((char*)c + 0xb28, c, result);
    int r = state->FUN_00ba3f90();
    if (r == 4 || r == 6)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d81700
float FUN_00d81700(void* pSelf, int, int, int, void* stimuli, bool* out, int, void* data)
{
    Creature* c = (Creature*)pSelf;
    if (stimuli != 0)
        ((Stimuli*)stimuli)->GetAny();
    *out = true;

    void* a = FUN_00d99420(c->mpBehavior + 0x1d0, *(int*)((char*)data + 0x2d));
    FUN_00d996e0(a, stimuli);
    void* id = StimulusObject(stimuli);
    int result = FUN_00d99470(id);
    if (result != 0) {
        void* herd = c->GetHerd();
        int herdState = herd ? *(int*)((char*)herd + 0x15c) : 0;
        if (herd == 0 || (herdState != 10 && herdState != 1)) {
            StateObj* state = (StateObj*)FUN_00b3d4c0((char*)c + 0xb28, c, result);
            if (state->FUN_00ba3f90() == 3)
                return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00d817b0
float FUN_00d817b0(void* pSelf, int, int, int, void* stimuli, bool* out, int, void* data)
{
    Creature* c = (Creature*)pSelf;
    if (stimuli != 0)
        ((Stimuli*)stimuli)->GetAny();
    *out = true;

    void* a = FUN_00d99420(c->mpBehavior + 0x1d0, *(int*)((char*)data + 0x2d));
    FUN_00d996e0(a, stimuli);
    void* id = StimulusObject(stimuli);
    if (FUN_00d99470(id) == 0)
        return 0.0f;
    return 1.0f;
}

// @ 0x00d81820
float FUN_00d81820(void* pSelf, int, int, int, void* stimuli, bool* out, int, void* data)
{
    Creature* c = (Creature*)pSelf;
    if (stimuli != 0)
        ((Stimuli*)stimuli)->GetAny();
    *out = true;

    void* a = FUN_00d99420(c->mpBehavior + 0x1d0, *(int*)((char*)data + 0x2d));
    FUN_00d996e0(a, stimuli);
    void* id = StimulusObject(stimuli);
    int result = FUN_00d99470(id);
    if (result != 0) {
        StateObj* state = (StateObj*)FUN_00b3d4c0((char*)c + 0xb28, c, result);
        if (state->FUN_00ba3f90() == 1)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d818b0
float FUN_00d818b0(void* pSelf, int, int, int, void* stimuli, bool* out, int, void* data)
{
    Creature* c = (Creature*)pSelf;
    if (stimuli != 0)
        ((Stimuli*)stimuli)->GetAny();
    *out = true;

    void* a = FUN_00d99420(c->mpBehavior + 0x1d0, *(int*)((char*)data + 0x2d));
    FUN_00d996e0(a, stimuli);
    void* id = StimulusObject(stimuli);
    int result = FUN_00d99470(id);
    if (result == 0)
        return 0.0f;

    StateObj* state = (StateObj*)FUN_00b3d4c0((char*)c + 0xb28, c, result);
    int r = state->FUN_00ba3f90();
    if (r == 2 || r == 5)
        return 1.0f;
    return 0.0f;
}
