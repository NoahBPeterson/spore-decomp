// Slice s00d922f0 -- SP::CitizenTree citizen/creature behaviour-tree callbacks: wander ticks, a
// mass-reaction activation, the run-from-danger destination chooser, a wild-panic tick, a
// "reached my goal" tick and two small animation helpers.
//
// Subject is the retail citizen/creature object (SP::cSPCreatureCitizen): locomotion sub-object at
// +0xc0, animation component pointer at +0xb4c, stimulus source pointer at +0xb54, owner record
// pointer at +0xfb8, owning city pointer at +0x1010.  Behaviour-tree callbacks are cdecl with the
// creature first and extra stimulus/context arguments trailing.
//
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <math.h>
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// --------------------------------------------------------------------------- opaque services
void normalized_safe(Vec3* out, const Vec3* in);           // 0x00449c20

struct PlanetModel;
PlanetModel* GetPlanetModel();                             // 0x00b3d350
struct PlanetModel {
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* center, float minDist, float maxDist); // 0x00b81780
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* pos);                               // 0x00b815a0
};

void* GetCurrentGameMode();                                // 0x00b5b800
int   GetPlayerEmpireID();                                 // 0x01021090

struct EffectMgr {                                         // 0x00b3d240 returns this
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    virtual void PlayEffect(uint32_t id, const Vec3* pos, const Vec3* dir);   // +0x68
};
EffectMgr* FUN_00b3d240();                                 // 0x00b3d240
void* FUN_00c9f000(void* elem);                            // 0x00c9f000

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);          // 0x00a68fb0
    double   RandomDoubleUniform();                        // 0x009360d0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x01601760

// --------------------------------------------------------------------------- value types
struct AnimState {                                         // cAnimState, returned by cAnimationPlayer::Play
    uint8_t mPad00[0x0c];
    Vec3    mPoint;                                        // +0x0c
    float   mf18;                                          // +0x18
    int     mi1c;                                          // +0x1c
};

struct AnimPlayer {
    uint8_t   mPad00[0x100];
    AnimState* Play(uint32_t anim, uint32_t flags);        // 0x00bc96a0
    void       ClearAll(uint32_t flags, uint32_t mode);    // 0x00bc98f0
};
struct AnimComponent {                                     // at creature + 0xb4c
    uint8_t    mPad00[8];
    AnimPlayer mPlayer;                                    // +0x08
};

struct TimedPoint { float mTime; Vec3 mPoint; };           // +0,+4,+8,+0xc

struct WanderState { int mMode; int mFlag; };              // +0,+4

struct DangerState {                                       // +0,+4,+8,+0x14
    float mf0;
    float mf4;
    Vec3  mCached;                                         // +0x08
    int   mEmpire;                                         // +0x14
};

struct CollisionInfo { uint8_t mPad000[0x258]; float mRadius; };
struct LanePoint { Vec3 mPoint; uint8_t mPad0C[0x20 - 0x0c]; };   // stride 0x20
struct LaneArray { LanePoint* mpBegin; LanePoint* mpEnd; };
struct PtrArray  { void** mpBegin; void** mpEnd; };

struct City;
struct Owner;
struct Creature;

struct CitySub {                                           // city + 0x120
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                     // +0x2c
};

struct City {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual CollisionInfo* GetCollisionInfo();             // +0x6c
    uint8_t mPad004[0x120 - 4];
    CitySub mSub;                                          // +0x120
    uint8_t mPad124[0x2d0 - 0x124];
    int     mCounter2D0;                                   // +0x2d0
    int  F8190();                                          // 0x00bd8190
    void F8170(int value);                                 // 0x00bd8170
    LaneArray* GetLaneInfo();                              // 0x0095fa00
};

struct ActionSlot {
    uint8_t mPad00[0x0c];
    Vec3    mPos;                                          // +0x0c
    void Reserve(Creature* c);                             // 0x00afa030
};
struct ActionCircle {
    uint8_t mPad00[0x14];
    ActionSlot* FindSlot(const Vec3* pos);                 // 0x00afad70
};
struct Owner {                                             // creature + 0xfb8
    uint8_t      mPad000[0xd4];
    ActionCircle mCircle;                                  // +0xd4
    Vec3         mV0E8;                                    // +0xe8
    uint8_t      mPad0F4[0x138 - 0xf4];
    Vec3         mV138;                                    // +0x138
    uint8_t      mPad144[0x1b0 - 0x144];
    Vec3         mV1B0;                                    // +0x1b0
    const Vec3*  FUN_00d579a0(Creature* c);                // 0x00d579a0
};

struct StimulusSource {                                    // creature + 0xb54
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual void GetTargetInfo(int* pAnimId, int a, int* pCount, int b);   // +0x58
};

struct Locomotion {                                        // creature + 0xc0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                     // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual const Vec3* GetForward(Vec3* tmp);             // +0x5c
    PV(24) PV(25) PV(26)
    virtual CollisionInfo* GetCollisionInfo();             // +0x6c
    PV(28)
    virtual float GetScale();                              // +0x74
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
    virtual void StopMoving();                             // +0xec
    bool        IsNearGoal();                              // 0x00c42e20
    PtrArray*   GetNearbyList();                           // 0x00c420d0
};

struct Creature {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual int  GetState();                               // +0x98
    virtual void SetState(int state);                      // +0x9c

    uint8_t        mPad004[0xc0 - 4];
    Locomotion     mLoco;                                  // +0xc0
    uint8_t        mPad0C4[0xb4c - 0xc0 - sizeof(Locomotion)];
    AnimComponent* mAnim;                                  // +0xb4c
    uint8_t        mPad0B50[0xb54 - 0xb50];
    StimulusSource* mpSourceB54;                           // +0xb54
    uint8_t        mPadB58[0xfb8 - 0xb58];
    Owner*         mpOwner;                                // +0xfb8
    uint8_t        mPadFBC[0x1010 - 0xfbc];
    City*          mpCity;                                 // +0x1010

    City* GetCity();                                       // 0x00c23e40
    void InterruptAnimation(uint32_t anim, int a, int b);  // 0x00c12310
    void MoveToPointAtSpeed(int mode, const Vec3* pos, float speed, float turn);   // 0x00c1c1d0
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing,
                                     float speed, float turn);                     // 0x00c1c5c0
    void SetSprinting(int on);                             // 0x00c1ad10
};

// --------------------------------------------------------------------------- forwards
void RunFromDanger_ChooseDestination(Creature* c, Vec3* cached, Vec3* dest);   // 0x00d92990

// --------------------------------------------------------------------------- 0x00d922f0
// Wander tick: keeps the creature oriented towards its owner's anchor point while it is far from
// its goal; once close it plays one of the idle/waving animations depending on the stimulus state.
// @ 0x00d922f0
bool FUN_00d922f0(Creature* c, int, int, uint32_t flags, int, WanderState* st)
{
    if ((flags & 2) != (uint32_t)st->mFlag) {
        return 0;
    }
    if (st->mMode == 0 || st->mMode == 1) {
        if (c->mLoco.IsNearGoal()) {
            c->InterruptAnimation(0x2481de5, -1, 0);
            st->mMode = 2;
        }
        return 1;
    }

    const Vec3* pos = c->mLoco.GetPosition();
    Vec3 delta;
    delta.x = c->mpOwner->mV138.x - pos->x;
    delta.y = c->mpOwner->mV138.y - pos->y;
    delta.z = c->mpOwner->mV138.z - pos->z;

    Vec3 dir;
    normalized_safe(&dir, &delta);

    const Vec3* fwd = c->mLoco.GetForward(&delta);
    if (fwd->y * dir.y + fwd->z * dir.z + fwd->x * dir.x < 0.7f) {
        c->InterruptAnimation(0x2481db0, -1, 0);
        c->MoveToPointAndFacingAtSpeed(2, c->mLoco.GetPosition(), &dir, 1.0f, 2.0f);
        st->mMode = 1;
        return 1;
    }

    StimulusSource* src = c->mpSourceB54;
    if (src == 0) {
        return 1;
    }
    int      iCount;
    uint32_t iAnim;
    src->GetTargetInfo((int*)&iAnim, 0, &iCount, 0);
    if (iCount >= 1 || iAnim == 0x2481de5) {
        if (c->mAnim->mPlayer.Play(0x20, 0) != 0) {
            c->InterruptAnimation(0x2481dd7 + sMathRandom.RandomUint32Uniform(3), -1, 0);
            return 1;
        }
        if (c->mAnim->mPlayer.Play(0x40, 0) != 0) {
            if (sMathRandom.RandomDoubleUniform() < 0.1f) {
                c->InterruptAnimation(0x2481dd4 + sMathRandom.RandomUint32Uniform(3), -1, 0);
            } else {
                c->InterruptAnimation(0x2d5f9bf, -1, 0);
                FUN_00b3d240()->PlayEffect(0x22941e7, c->mLoco.GetPosition(), &c->mpOwner->mV138);
            }
        }
    }
    return 1;
}

// --------------------------------------------------------------------------- 0x00d92560
// UfoWaving_Activate: walk towards the owner's anchor point while facing it.
// @ 0x00d92560
bool FUN_00d92560(Creature* c)
{
    const Vec3* tgt = c->mpOwner->FUN_00d579a0(c);
    Vec3 pos;
    pos.x = tgt->x;
    pos.y = tgt->y;
    pos.z = tgt->z;

    float dy = c->mpOwner->mV138.y - pos.y;
    float dz = c->mpOwner->mV138.z - pos.z;
    float dx = c->mpOwner->mV138.x - pos.x;
    float inv = 1.0f / sqrtf(dy * dy + dz * dz + dx * dx + 1e-8f);

    Vec3 dir;
    dir.x = inv * dx;
    dir.y = inv * dy;
    dir.z = inv * dz;

    c->InterruptAnimation(0x2481db1, -1, 0);
    c->MoveToPointAndFacingAtSpeed(3, &pos, &dir, 1.0f, 6.0f);
    return 1;
}

// --------------------------------------------------------------------------- 0x00d92660
// MassReaction_Tick part: reserve the owner's action slot nearest the creature and walk to it.
// @ 0x00d92660
bool FUN_00d92660(Creature* c, int, int, int, int, int* ctx)
{
    ActionSlot* slot = c->mpOwner->mCircle.FindSlot(c->mLoco.GetPosition());
    slot->Reserve(c);

    float dx = c->mpOwner->mV0E8.x - slot->mPos.x;
    float dy = c->mpOwner->mV0E8.y - slot->mPos.y;
    float dz = c->mpOwner->mV0E8.z - slot->mPos.z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);

    Vec3 dir;
    dir.x = inv * dx;
    dir.y = inv * dy;
    dir.z = inv * dz;

    c->InterruptAnimation(0x2481db0, -1, 0);
    c->MoveToPointAndFacingAtSpeed(2, &slot->mPos, &dir, 1.0f, 2.0f);
    *ctx = 0;
    return 1;
}

// --------------------------------------------------------------------------- 0x00d92880
// MassReaction_Activate: clear the animation stimuli, walk towards the owner's second anchor.
// @ 0x00d92880
bool FUN_00d92880(Creature* c, int, int, int, int, int* ctx)
{
    c->mAnim->mPlayer.ClearAll(1, 0);
    *ctx = 0;

    const Vec3* pos = c->mLoco.GetPosition();
    float dx = c->mpOwner->mV1B0.x - pos->x;
    float dy = c->mpOwner->mV1B0.y - pos->y;
    float dz = c->mpOwner->mV1B0.z - pos->z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);

    Vec3 dir;
    dir.x = inv * dx;
    dir.y = inv * dy;
    dir.z = inv * dz;

    c->InterruptAnimation(0x2481db0, -1, 0);
    c->MoveToPointAndFacingAtSpeed(2, c->mLoco.GetPosition(), &dir, 1.0f, 2.0f);
    return 1;
}

// --------------------------------------------------------------------------- 0x00d92990
// RunFromDanger_ChooseDestination: if the cached destination no longer matches the animation
// position, pick a point six units away from the creature, pulled back inside the city radius and
// projected onto the planet surface; otherwise pick a random city lane point.
// @ 0x00d92990
void RunFromDanger_ChooseDestination(Creature* c, Vec3* cached, Vec3* dest)
{
    AnimState* s = c->mAnim->mPlayer.Play(4, 0);
    Vec3 animPos;
    animPos.x = s->mPoint.x;
    animPos.y = s->mPoint.y;
    animPos.z = s->mPoint.z;

    if (c->GetCity() == 0 || cached == 0 ||
        cached->x != animPos.x || cached->y != animPos.y || cached->z != animPos.z) {
        const Vec3* pos = c->mLoco.GetPosition();
        float dz = pos->z - animPos.z;
        float dy = pos->y - animPos.y;
        float dx = pos->x - animPos.x;
        float inv = 1.0f / sqrtf(dz * dz + dy * dy + dx * dx + 1e-8f);

        float vx = (dx * inv) * 6.0f;
        float vy = (dy * inv) * 6.0f;
        float vz = (dz * inv) * 6.0f;

        const Vec3* pos2 = c->mLoco.GetPosition();
        Vec3 cand;
        cand.x = pos2->x + vx;
        cand.y = pos2->y + vy;
        cand.z = pos2->z + vz;

        City* city = c->GetCity();
        if (city != 0) {
            const Vec3* center = city->mSub.GetPosition();
            float rx = cand.x - center->x;
            float ry = cand.y - center->y;
            float rz = cand.z - center->z;
            float dist = sqrtf(rz * rz + ry * ry + rx * rx);
            float avail = city->GetCollisionInfo()->mRadius - c->mLoco.GetScale();
            if (avail < dist) {
                float t = avail / dist;
                Vec3 step;
                step.x = rx * t;
                step.y = ry * t;
                step.z = rz * t;
                const Vec3* center2 = city->mSub.GetPosition();
                cand.x = center2->x + step.x;
                cand.y = center2->y + step.y;
                cand.z = center2->z + step.z;
            }
        }

        Vec3 surface;
        *dest = *GetPlanetModel()->DirectionToSurfacePosition(&surface, &cand);
        *cached = animPos;
    } else {
        LaneArray* lanes = c->GetCity()->GetLaneInfo();
        if (lanes->mpBegin != lanes->mpEnd) {
            uint32_t i = sMathRandom.RandomUint32Uniform((uint32_t)(lanes->mpEnd - lanes->mpBegin));
            LanePoint* lp = &lanes->mpBegin[i];
            Vec3 lane;
            lane.x = lp->mPoint.x;
            lane.y = lp->mPoint.y;
            lane.z = lp->mPoint.z;
            *dest = lane;
            Vec3 out;
            GetPlanetModel()->MakeRandomWorldPosition(&out, dest, 2.0f, 4.0f);
        }
    }
}

// --------------------------------------------------------------------------- 0x00d92cc0
// RunFromDanger_Activate: choose a destination to flee to, move there, sprint, and (in space
// game mode) count the escape for the local empire.
// @ 0x00d92cc0
bool FUN_00d92cc0(Creature* c, int, int, int, int, DangerState* st)
{
    Vec3 dest;
    RunFromDanger_ChooseDestination(c, &st->mCached, &dest);

    AnimState* s = c->mAnim->mPlayer.Play(4, 0);
    st->mf0 = s->mf18;
    st->mf4 = s->mf18;
    st->mEmpire = s->mi1c;

    c->InterruptAnimation(0x2481dc8 + sMathRandom.RandomUint32Uniform(3), -1, 0);
    c->MoveToPointAtSpeed(2, &dest, 1.0f, 2.0f);
    c->SetSprinting(1);

    if (GetCurrentGameMode() == (void*)0x1654c05) {
        c->SetState(4);
        if (st->mEmpire == GetPlayerEmpireID()) {
            if (c->GetCity() != 0) {
                c->GetCity()->mCounter2D0++;
            }
        }
    }
    return 1;
}

// --------------------------------------------------------------------------- 0x00d92f60
// Stop and play a random idle animation.
// @ 0x00d92f60
bool FUN_00d92f60(Creature* c)
{
    c->mLoco.StopMoving();
    c->InterruptAnimation(0x2481dc8 + sMathRandom.RandomUint32Uniform(3), -1, 0);
    return 1;
}

// --------------------------------------------------------------------------- 0x00d92fb0
// WildPanic_Tick: while panicking and at the goal, pick a random lane point of the creature's
// city, ask the planet model for a position on the surface near it and walk there.
// @ 0x00d92fb0
bool WildPanic_Tick(Creature* c, int, int, uint32_t flags)
{
    if ((flags & 0x400000) == 0) {
        return 0;
    }
    if (!c->mLoco.IsNearGoal()) {
        return 1;
    }
    if (c->GetCity() == 0) {
        return 1;
    }
    LaneArray* lanes = c->GetCity()->GetLaneInfo();
    if (lanes->mpBegin != lanes->mpEnd) {
        uint32_t i = sMathRandom.RandomUint32Uniform((uint32_t)(lanes->mpEnd - lanes->mpBegin));
        LanePoint* lp = &lanes->mpBegin[i];
        Vec3 center;
        center.x = lp->mPoint.x;
        center.y = lp->mPoint.y;
        center.z = lp->mPoint.z;
        Vec3 out;
        GetPlanetModel()->MakeRandomWorldPosition(&out, &center, 2.0f, 4.0f);
        c->InterruptAnimation(0x2481dc8 + sMathRandom.RandomUint32Uniform(3), -1, 0);
        c->MoveToPointAtSpeed(3, &center, 1.0f, 2.0f);
    }
    return 1;
}

// --------------------------------------------------------------------------- 0x00d930b0
// WildPanic_Activate: play the panic start animation and copy the first animation point into the
// caller's timed point record before walking towards it.
// @ 0x00d930b0
bool FUN_00d930b0(Creature* c, int, int, int, int, TimedPoint* out)
{
    AnimState* s = c->mAnim->mPlayer.Play(0x200, 0);
    float px = s->mPoint.x;
    float py = s->mPoint.y;
    float pz = s->mPoint.z;
    Vec3 v;
    v.x = px;
    v.y = py;
    v.z = pz;

    if (c->GetCity() == 0) {
        return 0;
    }
    out->mPoint = v;
    out->mTime = 0.0f;

    c->MoveToPointAtSpeed(2, &v, 5.0f, 10.0f);
    c->InterruptAnimation(0x2481db1, -1, 0);
    return 1;
}

// --------------------------------------------------------------------------- 0x00d93160
// WildPanic_Tick helper: accumulate the time spent at the goal and enter the panic state once the
// timer passes five seconds; otherwise keep walking to the recorded point.
// @ 0x00d93160
bool FUN_00d93160(Creature* c, int, int, int, int, TimedPoint* q, int, float amount)
{
    City* city = c->GetCity();
    if (city == 0) {
        return 0;
    }
    if (c->mLoco.IsNearGoal()) {
        q->mTime += amount;
        if (q->mTime > 5.0f && c->GetState() != 5) {
            c->SetState(5);
            c->InterruptAnimation(0x2481dda + sMathRandom.RandomUint32Uniform(3), -1, 0);
            city->F8170(city->F8190() + 1);
        }
    } else {
        c->MoveToPointAtSpeed(2, &q->mPoint, 5.0f, 10.0f);
        c->InterruptAnimation(0x2481db1, -1, 0);
    }
    return 1;
}
