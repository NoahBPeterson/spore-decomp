// Slice s00da3b90 -- SOCIAL_RESPOND activation step (0x00da3b90, 2157 bytes).
//
// One step of a "respond to a social partner" behavior: the owner (mOwner) and a partner
// (mPartner) both stand on the planet. If the "keep away" flag (0x20) is set, the partner is
// nudged toward a point on the line from the owner to the creature, and the activation is
// aborted (-1). Otherwise, unless creature `c` already is the registered target in slot
// `slot`, three candidate stand points are built around the owner (the direction toward the
// partner rotated about the owner's up axis by two fixed angles, and its opposite), projected
// onto the planet, sorted by squared distance to the creature, and handed to
// MoveToTarget; if nothing was chosen the creature is walked toward the owner when close.
// Module flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    Vec3& operator=(const Vec3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

struct Quat {
    float x, y, z, w;
    Quat() {}
    Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    Quat(const Quat& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};

Vec3 QuatRotate(const Vec3& v, const Quat& q);   // 0x0059aed0

extern const float kAngleA;   // 0x01593470 (pi/4)
extern const float kAngleB;   // 0x01593474 (pi/2)
extern const float kAngleC;   // 0x01593478 (pi)

// Rotation of `angle` radians about the unit vector `axis`.
inline Quat AxisAngle(const Vec3& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quat(axis.x * s, axis.y * s, axis.z * s, c);
}

// Locomotion sub-object at creature + 0xc0 (has its own vtable).
struct Loco {
    PV8 PV2 PV                       // slots 0..10
    virtual const Vec3* GetPosition();   // slot 11 (+0x2c)
    PV8 PV8 PV                       // slots 12..28
    virtual float GetRadius();           // slot 29 (+0x74)
    PV8 PV8 PV8 PV4 PV               // slots 30..58
    virtual void Stop();                 // slot 59 (+0xec)
};

struct Vec3F { Vec3 v; };

struct Obj {
    virtual int pv_0();
    virtual int Release();
};

struct Creature;
struct Planet {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* p);   // 0x00b815a0
};
Planet* __cdecl PlanetModel();                                    // 0x00b3d350

struct Creature {
    char pad00[0xc0];
    Loco loco;                                                     // +0xc0
    void MoveToPointAtSpeed(int mode, const Vec3* p, float speed, float f);   // 0x00c1c1d0
};

// A candidate stand point (32 bytes).
struct Cand {
    int kind;
    Vec3 dir;
    Vec3 pos;
    float dist2;
};

// fixed_vector<Cand, 3> with an overflow allocator.
struct CandVec {
    Cand* mpBegin;
    Cand* mpEnd;
    Cand* mpCapacity;
    int mAlloc;
    Cand* mpPool;
    void Resize(unsigned n);                                       // 0x00da1db0
};
void __cdecl SortCands(Cand* first, Cand* last, bool (__cdecl* less)(const Cand*, const Cand*));   // 0x00da1e00
// Comparator passed to the sort (the original is the 11-byte function at 0x00d9b2b0).
bool __cdecl CandLess(const Cand* a, const Cand* b) { return a->dist2 < b->dist2; }
void __cdecl operator_delete_array(void* p);                        // 0x00f47380

struct SocialRespond;
int __cdecl MoveToTarget(Creature* c, unsigned pick, CandVec* cands, Obj*** targets);   // 0x00d9bee0

inline Vec3 Target(const Vec3& origin, const Vec3& dir, float scale)
{
    return Vec3(dir.x * scale + origin.x, origin.y + dir.y * scale, origin.z + dir.z * scale);
}

struct SocialGoalRuntime;
struct SocialRespond {
    Creature* mOwner;                // +0x00
    Creature* mPartner;              // +0x04
    uint32_t mStartTime;             // +0x08 (number of proposed socials)
    uint32_t pad0c[3];               // +0x0c..+0x14
    float mDuration;                 // +0x18
    float mProposalTime;             // +0x1c
    uint32_t pad20[2];               // +0x20,+0x24
    float mResponseTime;             // +0x28
    uint32_t pad2c[3];               // +0x2c..+0x34
    SocialGoalRuntime* mRuntime;     // +0x38
    int mSocialGoal;                 // +0x3c
    uint32_t pad40[4];               // +0x40..+0x4f
    uint32_t mCount;                 // +0x50
    uint32_t pad54;                  // +0x54
    uint32_t mFlags;                 // +0x58
    Obj** mTargets;                  // +0x5c

    int Activate(Creature* c, int slot);
    void Deactivate();               // 0x00d9f7e0
};

// @ 0x00da3b90
int SocialRespond::Activate(Creature* c, int slot)
{
    Vec3 p0 = *mOwner->loco.GetPosition();
    float rr = c->loco.GetRadius() + 1.0f;
    float t = rr + rr;
    float r5 = t + 5.0f;
    float sq = r5 * r5;
    Vec3 b = *c->loco.GetPosition();
    Planet* planet = PlanetModel();

    if (mFlags & 0x20) {
        float dx = b.x - p0.x, dy = b.y - p0.y, dz = b.z - p0.z;
        float d2 = (dz * dz + dy * dy) + dx * dx;
        if (sq > d2) {
            float inv = 1.0f / sqrtf(d2 + 1e-8f);
            Vec3 tgt(dx * inv * sq + p0.x, p0.y + dy * inv * sq, p0.z + dz * inv * sq);
            Vec3 out;
            planet->DirectionToSurfacePosition(&out, &tgt);
            c->MoveToPointAtSpeed(2, &out, 1.0f, 2.0f);
            if (slot != -1) {
                Obj** pp = &mTargets[slot];
                Obj* o = *pp;
                if (o) {
                    *pp = 0;
                    o->Release();
                    return -1;
                }
            }
        } else {
            c->loco.Stop();
        }
        return -1;
    }

    if (slot != -1 && mTargets[slot] == (Obj*)c)
        return slot;

    Cand stackBuf[3];
    CandVec cands;
    cands.mpBegin = stackBuf;
    cands.mpEnd = stackBuf;
    cands.mpCapacity = stackBuf + 3;
    cands.mpPool = stackBuf;
    cands.Resize(3);

    Creature* partner = mPartner;
    const Vec3* po = mOwner->loco.GetPosition();
    const Vec3* pp = partner->loco.GetPosition();
    float fx = pp->x - po->x;
    float fz = pp->z - po->z;
    float fy = pp->y - po->y;
    float inv1 = 1.0f / sqrtf((fy * fy + (fz * fz + fx * fx)) + 1e-8f);
    Vec3 fwd(inv1 * fx, inv1 * fy, inv1 * fz);

    const Vec3* up = mOwner->loco.GetPosition();
    float inv2 = 1.0f / sqrtf(((up->x * up->x + up->y * up->y) + up->z * up->z) + 1e-8f);
    Vec3 axis(inv2 * up->x, inv2 * up->y, inv2 * up->z);
    Quat q1 = AxisAngle(axis, kAngleB + kAngleA);
    Quat q2 = AxisAngle(axis, kAngleC + kAngleA);

    Cand* cd = cands.mpBegin;
    cd[0].kind = 0;
    cd[0].dir = QuatRotate(fwd, q1);
    Vec3 tg0 = Target(p0, cd[0].dir, t);
    Vec3 s0;
    cd[0].pos = *planet->DirectionToSurfacePosition(&s0, &tg0);
    {
        float ex = b.x - cd[0].pos.x, ez = b.z - cd[0].pos.z, ey = b.y - cd[0].pos.y;
        cd[0].dist2 = (ex * ex + ez * ez) + ey * ey;
    }

    cd[1].kind = 1;
    cd[1].dir = QuatRotate(fwd, q2);
    Vec3 tg1 = Target(p0, cd[1].dir, t);
    Vec3 s1;
    cd[1].pos = *planet->DirectionToSurfacePosition(&s1, &tg1);
    {
        float ex = b.x - cd[1].pos.x, ez = b.z - cd[1].pos.z, ey = b.y - cd[1].pos.y;
        cd[1].dist2 = (ex * ex + ez * ez) + ey * ey;
    }

    cd[2].kind = 2;
    {
        float inv3 = 1.0f / sqrtf(((fwd.x * fwd.x + fwd.z * fwd.z) + fwd.y * fwd.y) + 1e-8f);
        cd[2].dir.y = -(inv3 * fwd.y);
        cd[2].dir.x = -(inv3 * fwd.x);
        cd[2].dir.z = -(inv3 * fwd.z);
    }
    Vec3 tg2 = Target(p0, cd[2].dir, t);
    Vec3 s2;
    cd[2].pos = *planet->DirectionToSurfacePosition(&s2, &tg2);
    {
        float ex = b.x - cd[2].pos.x, ez = b.z - cd[2].pos.z, ey = b.y - cd[2].pos.y;
        cd[2].dist2 = (ex * ex + ez * ez) + ey * ey;
    }

    SortCands(cands.mpBegin, cands.mpEnd, CandLess);

    unsigned pick = 0;
    for (unsigned i = 0; i < 3; ++i) {
        if (mCount > 2 || cands.mpBegin[i].kind != 2) {
            pick = i;
            break;
        }
    }
    int result = MoveToTarget(c, pick, &cands, &mTargets);
    if (result == -1) {
        float dx = b.x - p0.x, dz = b.z - p0.z, dy = b.y - p0.y;
        float d2 = (dx * dx + dz * dz) + dy * dy;
        if (d2 < sq) {
            float inv = 1.0f / sqrtf(d2 + 1e-8f);
            Vec3 tgt(inv * dx * sq + p0.x, p0.y + inv * dy * sq, p0.z + inv * dz * sq);
            Vec3 out;
            planet->DirectionToSurfacePosition(&out, &tgt);
            c->MoveToPointAtSpeed(2, &out, 1.0f, 2.0f);
        }
    }
    if (cands.mpBegin && cands.mpBegin != cands.mpPool)
        operator_delete_array(cands.mpBegin);
    return result;
}

// ---------------------------------------------------------------------------
// SOCIAL_PROPOSE_Activate (0x00da4400, 0x5e5 bytes)
//
// The propose behaviour picks the social target from the owner's current
// animation/stimulus state, builds a SOCIAL_PROPOSE block (embedded at +0x1a4
// in the behaviour allocation), chooses the proposed social entries and their
// timing, and either starts the proposal or falls back to SOCIAL_RESPOND.
// ---------------------------------------------------------------------------

struct CreatureEx;
struct LocoEx;
struct BehaviorBlock;
struct BehaviorMemory;
struct AnimState;
struct OrderState;
struct AnimRecord;
struct SocialGoal;
struct SocialGoalRuntime;
struct StimulusRef;
struct StimulusObject;
struct ObjEx;
struct NounManager;
struct TerrainSphere;
struct UIHints;
struct SocialProposalContext;
struct CreatureModeStrategy;
struct SocialGoalContext;
struct SomeGlobal;

struct LocoVtbl {
    void* mSlots[22];                                      // +0x00..+0x54
    bool  (__thiscall* mIsMoving)(LocoEx*);                // +0x58
    void* mSlots23[36];                                    // +0x5c..+0xe8
    void  (__thiscall* mStop)(LocoEx*);                    // +0xec
};

struct LocoEx {
    LocoVtbl* mVtable;
};

struct CreatureVtbl {
    void* mSlots[33];                                      // +0x00..+0x80
    void (__thiscall* mSetSocialTarget)(CreatureEx*, void*, int, int); // +0x84
};

struct IntVector {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    unsigned int Count() const { return (unsigned int)(mpEnd - mpBegin); }
    void Resize(unsigned int count);
};

struct PtrVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
};

struct RandomLCG {
    unsigned int RandomUint32Uniform(unsigned int count);
};
extern RandomLCG gMathRandom;                 // 0x01601760 SP::sMathRandom

struct AnimRecord {
    char pad00[0x0c];
    int mStatus;                              // +0x0c
};

struct AnimTarget {
    AnimRecord* PlayIdleAnimation(int id, int flags);                       // 0x00bc96a0
    void PlaySocialAnimation(int id, int flags, float amount, CreatureEx* owner); // 0x00bc97f0
    void ClearAll(int id, int flags);                                       // 0x00bc98f0
};

struct OrderState {
    char pad00[0x08];
    AnimTarget mAnimTarget;                   // +0x08
    void InitializeBehavior(BehaviorBlock* block, CreatureEx* owner, int flags, void* callback); // 0x00bcb480
};

struct SocialEntry {
    char pad00[0x3c];
    float mWeight;                            // +0x3c
};

struct AnimState {
    char pad00[0x6d4];
    SocialEntry** mSocialEntries;             // +0x6d4
    char pad6d8[0x7a4 - 0x6d8];
    IntVector mSocialIds;                     // +0x7a4
};

struct SocialGoal {
    char pad00[0x424];
    unsigned int mProposalStart;              // +0x424
    float mField428;                          // +0x428
    float mField42c;                          // +0x42c
    int mMaxProposals;                        // +0x430
};

struct SocialGoalRuntime {
    void Initialize();                        // 0x00e33ce0
    void SetActive(int active);               // 0x00e31a10
    void SetCount(unsigned int count);        // 0x00e31b20
    void SetValue(void* value);               // 0x00e31cb0
};

struct ProposeResult {
    unsigned int mField00;                    // +0x00
    unsigned int mField04;                    // +0x04
    bool mActive;                             // +0x08
    char pad09[3];
    int mSlot;                                // +0x0c
};

struct StimulusRef {
    void* mObject;                            // +0x00
};

struct StimulusObject {
    void* pad00[2];
    void* mSubObject;                         // +0x08
};

struct ObjExVtbl {
    void* mSlots[8];
    unsigned int (__thiscall* mGetType)(void*); // +0x20
};

struct ObjEx {
    ObjExVtbl* mVtable;
};

struct BehaviorBlock {
    char pad00[0x1a4];
    SocialRespond mPropose;                   // +0x1a4
    char pad204[0x228 - 0x204];
    void* mVtable;                            // +0x228
};

struct BehaviorMemory {
    BehaviorBlock* Construct();               // 0x00bcb0b0
    BehaviorBlock* Lookup();                  // 0x00bca620
};

struct CreatureEx {
    CreatureVtbl* mVtable;                    // +0x000
    char pad04[0xbc];                         // +0x004..+0x0bf
    LocoEx mLoco;                             // +0x0c0
    char padC4[0x5a8 - 0xc4];
    void* mCaster;                            // +0x5a8
    char pad5ac[0xb20 - 0x5ac];
    AnimState* mAnimState;                    // +0xb20
    Vec3 mPosition;                           // +0xb28
    char padB34[0xb4c - 0xb34];
    OrderState* mOrders;                      // +0xb4c
    char padB50[0xb58 - 0xb50];
    unsigned char mFlagsB58;                  // +0xb58
    char padB59[0x1020 - 0xb59];
    IntVector mProposedSocials;               // +0x1020
    char pad102c[0x1124 - 0x102c];
    PtrVector mSocialStimuli;                 // +0x1124

    SocialGoal* GetSocialGoal();              // 0x00c0c1a0
    int GetSocialGoalType();                  // 0x00c0e6a0
    bool IsSocialActive();                    // 0x00c0b770
};

struct TerrainSphere {
    bool IsSomething();                       // 0x00c772c0
};

struct NounManager {
    TerrainSphere* GetCurrentTerrainSphere(); // 0x00f67d90
};

struct UIHints {
    void Show();                              // 0x0067c830
};

struct SocialProposalContext {
    void* GetValue();                         // 0x00ba3f90
};

struct SocialGoalContext {
    SocialGoalRuntime* GetRuntime();          // 0x00d2ba50
};

struct CreatureModeStrategy {
    char pad00[0x68];
    SocialGoalContext mContext;               // +0x68
};

struct SomeGlobal {
    char pad00[0x6c];
    void* mObject;                            // +0x6c
};
extern SomeGlobal* gSomeGlobal;               // 0x016c7aa4

extern unsigned int gSocialTimeA;             // 0x01582f14
extern unsigned int gSocialTimeB;             // 0x01582f10

void* GetAnimalFromStimulus(AnimRecord* anim);                    // 0x00d99980
CreatureEx* FUN_00d99500(void* animal);                            // 0x00d99500
BehaviorMemory* FUN_00bc9b00(int id, int size, int type, void* callback); // 0x00bc9b00
BehaviorMemory* FUN_00bc9b00_lookup(void* target, void* callback, int id); // 0x00bc9b00 (3-arg path)
void FUN_00b5f950(Creature** ref, Creature* value);               // 0x00b5f950
void FUN_00da1010(Obj*** targets, int count);                     // 0x00da1010
void* FUN_00b3d4c0(Vec3* position, CreatureEx* owner, CreatureEx* partner); // 0x00b3d4c0
NounManager* FUN_00b3d300(int nounType);                          // 0x00b3d300
void* FUN_005e1fc0(void* object);                                 // 0x005e1fc0
CreatureModeStrategy* FUN_00d38840();                             // 0x00d38840
void* GetCurrentGameMode();                                       // 0x00b5b800
UIHints* FUN_0067cac0(int hintId);                                // 0x0067cac0

// @ 0x00da4400
bool __cdecl SocialProposeActivate(CreatureEx* owner, int, int, int, int, ProposeResult* out)
{
    if (out) {
        out->mField00 = 0;
        out->mField04 = 0;
        out->mActive = false;
        out->mSlot = -1;
    }

    AnimRecord* anim = owner->mOrders->mAnimTarget.PlayIdleAnimation(0x10000, 0);
    if (anim && anim->mStatus == 1)
        out->mActive = true;

    if (!out->mActive)
    {
        // No active proposal: attach SOCIAL_RESPOND to the current stimulus
        // target and let the respond state machine take over.
        CreatureEx* target = FUN_00d99500(GetAnimalFromStimulus(anim));
        if (!target)
            return false;

        BehaviorMemory* mem = FUN_00bc9b00_lookup(target, (void*)0x00d9ba30, 0x14fcf96e);
        BehaviorBlock* block = mem->Lookup();
        if (!block)
            return false;

        SocialRespond* self = &block->mPropose;
        if (self->mFlags & 0x20) {
            owner->mOrders->mAnimTarget.ClearAll(0x10000, 0);
            return false;
        }

        owner->mOrders->InitializeBehavior(block, owner, 0, (void*)0x00d9ba30);

        CreatureEx* partner = (CreatureEx*)self->mPartner;
        void* targetArg = partner ? &partner->mCaster : 0;
        owner->mVtable->mSetSocialTarget(owner, targetArg, 0, 2);
        out->mSlot = self->Activate((Creature*)owner, out->mSlot);

        owner->mOrders->mAnimTarget.ClearAll(0x10000, 0);
        return true;
    }

    // Active proposal path.
    CreatureEx* target = FUN_00d99500(GetAnimalFromStimulus(anim));
    if (!target)
        return false;

    SocialGoal* goal = owner->GetSocialGoal();
    if (!goal)
        return false;

    unsigned int socialIdCount = owner->mAnimState->mSocialIds.Count();
    if (socialIdCount == 0)
        return false;

    int goalType = owner->GetSocialGoalType();
    if (goalType == 0)
        return false;

    BehaviorMemory* mem = FUN_00bc9b00(0x14fcf96e, 0x20, 0x18eb45e, (void*)0x0147c1d0);
    BehaviorBlock* block = mem->Construct();
    block->mVtable = (void*)0x00dd3d10;

    owner->mOrders->InitializeBehavior(block, owner, 0, (void*)0x00d9ba30);

    SocialRespond* self = &block->mPropose;
    self->Deactivate();
    FUN_00b5f950(&self->mOwner, (Creature*)owner);
    FUN_00b5f950(&self->mPartner, (Creature*)target);
    self->mSocialGoal = goalType;

    if (goalType == 4) {
        self->mCount = 0;
    } else {
        const int limit = goal->mMaxProposals - 1;
        self->mCount = (limit >= 0) ? (unsigned int)limit : 0;
    }

    FUN_00da1010(&self->mTargets, 3);
    for (unsigned int i = 0; i < 3; ++i) {
        Obj* obj = self->mTargets[i];
        if (obj) {
            self->mTargets[i] = 0;
            obj->Release();
        }
    }

    self->mStartTime = goal->mProposalStart;
    if (!owner->IsSocialActive()) {
        unsigned int t = self->mStartTime - gSocialTimeA;
        if (t < 1)
            t = 1;
        self->mStartTime = t;
    } else if (owner->mFlagsB58 & 1) {
        self->mStartTime += gSocialTimeB;
    }

    int weightSum = 0;
    const unsigned int proposedCount = owner->mProposedSocials.Count();
    if (proposedCount != self->mStartTime) {
        owner->mProposedSocials.Resize(self->mStartTime);
        for (unsigned int i = 0; i < self->mStartTime; ++i) {
            const unsigned int r = gMathRandom.RandomUint32Uniform(socialIdCount);
            const int id = owner->mAnimState->mSocialIds.mpBegin[r];
            owner->mProposedSocials.mpBegin[i] = id;
            SocialEntry* entry = owner->mAnimState->mSocialEntries[id];
            weightSum += (int)entry->mWeight;
        }
    } else if (self->mStartTime > 0) {
        for (unsigned int i = 0; i < self->mStartTime; ++i) {
            const int id = owner->mProposedSocials.mpBegin[i];
            SocialEntry* entry = owner->mAnimState->mSocialEntries[id];
            weightSum += (int)entry->mWeight;
        }
    }

    if (self->mCount > 0) {
        bool found = false;
        for (void** it = owner->mSocialStimuli.mpBegin; it != owner->mSocialStimuli.mpEnd; ++it) {
            StimulusRef* ref = (StimulusRef*)*it;
            if (!ref || !ref->mObject)
                continue;

            StimulusObject* stimulus = (StimulusObject*)ref->mObject;
            void* sub = stimulus->mSubObject;
            if (!sub)
                continue;

            ObjEx* obj = (ObjEx*)sub;
            if (obj->mVtable->mGetType(sub) != 0x18eb45e)
                continue;

            CreatureEx* other = FUN_00d99500(sub);
            if (!other || other == owner)
                continue;
            if (other->mLoco.mVtable->mIsMoving(&other->mLoco))
                continue;
            if (other->mPosition.x != owner->mPosition.x)
                continue;
            if (other->mPosition.y != owner->mPosition.y)
                continue;
            if (other->mPosition.z != owner->mPosition.z)
                continue;

            other->mOrders->mAnimTarget.PlaySocialAnimation(0x10000, 0, 10.0f, owner);
            AnimRecord* rec = other->mOrders->mAnimTarget.PlayIdleAnimation(0x10000, 0);
            rec->mStatus = 2;
            found = true;
        }
        if (!found)
            self->mCount = 0;
    }

    const float duration = (float)(unsigned int)weightSum;
    const unsigned int startTime = self->mStartTime;

    void* mode = GetCurrentGameMode();
    SocialGoalRuntime* runtime;
    if (mode == (void*)0x01654c10) {
        runtime = (SocialGoalRuntime*)FUN_005e1fc0(gSomeGlobal->mObject);
    } else {
        CreatureModeStrategy* strategy = FUN_00d38840();
        runtime = strategy->mContext.GetRuntime();
    }

    self->mRuntime = runtime;
    runtime->Initialize();
    runtime->SetActive(0);
    runtime->SetCount(startTime);

    self->mDuration = duration + duration;
    self->mProposalTime = goal->mField42c;
    self->mResponseTime = goal->mField428;

    CreatureEx* partner = (CreatureEx*)self->mPartner;
    SocialProposalContext* context =
        (SocialProposalContext*)FUN_00b3d4c0(&owner->mPosition, owner, partner);
    runtime->SetValue(context->GetValue());
    runtime->SetActive(1);

    NounManager* nouns = FUN_00b3d300((int)0x34220e8e);
    TerrainSphere* terrain = nouns->GetCurrentTerrainSphere();
    if (!terrain->IsSomething()) {
        UIHints* hints = FUN_0067cac0((int)0x1ea83595);
        hints->Show();
    }

    void* targetArg = partner ? &partner->mCaster : 0;
    owner->mVtable->mSetSocialTarget(owner, targetArg, 1, 2);
    owner->mLoco.mVtable->mStop(&owner->mLoco);

    owner->mOrders->mAnimTarget.ClearAll(0x10000, 0);
    return true;
}
