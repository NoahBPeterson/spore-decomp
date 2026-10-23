// Slice s00ce1390: SP tribe-planner plan handlers (retail module SPGonzago/SPTribePlanner.obj).
// Each plan is a {planHash, Activate, Tick, Deactivate} record; here the Activate/Tick pairs for six
// plans.  All callees are __thiscall members of the game objects below; unused parameters are 4-byte
// dummies (the planner entry points take the context, four dead words, the plan state, a worker
// filter and the frame delta).
//
// Names: only some of these carry a caller-scored dev-PDB name (STEAL_CONGREGATE, STEALING_FOOD,
// GIFTING, HUNTING, GATHERING); the 0x58b725f pair (order 1 to the closest water) is named
// PLANNER_WATERING_* here by analogy.
//
// Layouts are retail (the planner itself keeps its plan map behind +0x14/+0x18, the order manager
// pointer at +0x10).  Iterators wrap a {begin,end} pair of worker pointers; the predicate object is
// embedded at +8 of the iterator.
#include "types.h"
#include <math.h>

#define VSLOT(n) virtual void _v##n();

#define VSLOTS_0_3   VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
#define VSLOTS_4_7   VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
#define VSLOTS_8_11  VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11)
#define VSLOTS_12_15 VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
#define VSLOTS_16_19 VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19)
#define VSLOTS_20_23 VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
#define VSLOTS_24_27 VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27)
#define VSLOTS_28_31 VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31)
#define VSLOTS_32_35 VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35)
#define VSLOTS_36_39 VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39)
#define VSLOTS_40_43 VSLOT(40) VSLOT(41) VSLOT(42) VSLOT(43)
#define VSLOTS_44_47 VSLOT(44) VSLOT(45) VSLOT(46) VSLOT(47)
#define VSLOTS_0_10  VSLOTS_0_3 VSLOTS_4_7 VSLOT(8) VSLOT(9) VSLOT(10)
#define VSLOTS_0_18  VSLOTS_0_10 VSLOT(11) VSLOTS_12_15 VSLOT(16) VSLOT(17) VSLOT(18)
#define VSLOTS_0_23  VSLOTS_0_18 VSLOT(19) VSLOTS_20_23
#define VSLOTS_0_45  VSLOTS_0_23 VSLOTS_24_27 VSLOTS_28_31 VSLOTS_32_35 VSLOTS_36_39 \
                     VSLOTS_40_43 VSLOT(44) VSLOT(45)
#define VSLOTS_0_47  VSLOTS_0_45 VSLOT(46) VSLOT(47)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

extern unsigned g_defaultUInt;      // 0x015d1164
extern bool     g_bool_01581374;    // 0x01581374
extern float    g_zero;             // 0x01485378
extern float    g_two;              // 0x01470f1c
extern float    g_f_01473c70;       // 0x01473c70
extern float    g_fltMax;           // 0x01477928
extern float    g_f_01486114;       // 0x01486114

// App::Variant-like 0x14-byte value (data, flags at +0x10, type at +0x12).
#pragma pack(push, 1)
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;
    uint16_t mType;
    void* GetStorage() { if (mFlags & 0x30) { return *(void**)mData; } else if (mType) return this; return 0; }
    unsigned* GetUInt()
    {
        if (mType == 10 || mType == 0x10) { return (unsigned*)GetStorage(); }
        return &g_defaultUInt;
    }
    Variant& SetInt(const int* v);          // 0x00427fd0
    Variant& SetFloat(const float* v);      // 0x00428060
    Variant& SetVec3(const void* v);        // 0x006a3570
    void Destruct(bool reset);              // 0x0093db80
    ~Variant() { if (mFlags & 4) { Destruct(false); } }
};
#pragma pack(pop)

struct IInterface {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* AsInterface(uint32_t id);         // +0x0c, 0x4f396a66 = cTribe
};
struct IGetPos {
    VSLOTS_0_10
    virtual Vector3* GetPosition();                 // +0x2c
};
struct IBool11 {
    VSLOTS_0_10
    virtual bool IsBusy();                          // +0x2c
};
struct IGetId {
    VSLOTS_0_18
    virtual int GetId();                            // +0x4c
};
struct IGetRadius {
    VSLOTS_0_23
    virtual float GetRadius();                      // +0x60
};
struct ICast46 {
    VSLOTS_0_45
    virtual void* Cast(uint32_t id);                // +0xb8
};
struct IProx48 {
    VSLOTS_0_47
    virtual bool IsNear(void* pOther, float a, float b);   // +0xc0
};

struct Vector3;
struct PtrList {                                    // pair of pointers
    void** mpBegin;                                 // +0x00
    void** mpEnd;                                   // +0x04
};
struct Vec3List {
    Vector3* mpBegin;                               // +0x00
    Vector3* mpEnd;                                 // +0x04
};
struct IGetRandomPos {
    VSLOTS_0_10
    virtual Vector3* GetRandomPos(float d0, float d1);     // +0x2c
};
// object embedded at +0xc0 of a creature: position + attackable list
struct C0Obj {
    VSLOTS_0_10
    virtual Vector3* GetPosition();                 // +0x2c
    PtrList* GetAttackables();                      // 0x00c420d0
};

struct cAgentOrder;
struct cCreature;
struct cTribe;
struct cTribePlanData;

struct cAgentOrderManager {
    cAgentOrder* FirstPending();                    // 0x00bca2c0
    char mPad[0x1cc];
    unsigned mFlags1CC;                             // +0x1cc
};

struct cAgentOrder {
    int mType;                                      // +0x00
    char mPad0[0x24];
    IInterface* mpTarget;                           // +0x28
    Vector3 mPosition;                              // +0x2c
    char mPad1[1];                                  // +0x38
    Variant mParam;                                 // +0x39
    Variant mOption;                                // +0x4d
};

struct WorkerList {
    cCreature** mpBegin;                            // +0x00
    cCreature** mpEnd;                              // +0x04
};

struct cTribePlanData {
    int mPad0;
    int mState;                                     // +0x04
    char mPad1[0x14];
    WorkerList mWorkers;                            // +0x1c
};

struct cTribePlanner {
    char mPad0[0x10];
    cAgentOrderManager* mpOrderManager;             // +0x10
    char mPad1[4];
    cTribePlanData* GetPlanData(int orderType, unsigned key);   // 0x00ce0e60
};

struct cTribePlannerContext {
    cTribe* mpTribe;                                // +0x00
    cTribePlanner* mpTribePlanner;                  // +0x04
    unsigned mToolsMask;                            // +0x08
    int mNumAdults;                                 // +0x0c
    int mMaxAdults;                                 // +0x10
    float mCurrentFood;                             // +0x14
    int mAttitudeToTarget;                          // +0x18
    int mTargetPopulation;                          // +0x1c
    IInterface* mpTarget;                           // +0x20
};

struct WorkerFilter {
    bool Pass(cCreature* c);                        // 0x00cdfea0
};

struct WorkerIter {
    cCreature** mCur;                               // +0x00
    cCreature** mEnd;                               // +0x04
    WorkerFilter mFilter;                           // +0x08
    WorkerIter() {}
    WorkerIter(WorkerList* w) : mCur(w->mpBegin), mEnd(w->mpEnd) {}
    WorkerIter& Init(WorkerList* w, void* p);       // 0x00ce0b20
    WorkerIter& Advance();                          // 0x00cdff70
};

struct cCreature {
    char mPad0[0xb34];
    int  mFlagB34;                                  // +0xb34
    char mPad1[0xb4c - 0xb38];
    cAgentOrderManager* mpOrderManager;             // +0xb4c
    char mPad2[0xb5e - 0xb50];
    char mFlagB5E;                                  // +0xb5e
    char mPad3[0xb80 - 0xb5f];
    float mRadiusB80;                               // +0xb80
    char mPad4[0x3c];                               // +0xb84
    char mPosC0[0x60];                              // +0xc0 embedded position object
    char mPos120[0x60];                             // +0x120 embedded position object

    cAgentOrder* GiveOrder(int orderType, void* pTarget, Variant* pParam);   // 0x00c275b0
    bool AnimationFinished(uint32_t id);                                     // 0x00c123f0
    void InterruptAnimation(uint32_t id, int a, bool b);                     // 0x00c12310
    bool IsFlagB34() { return mFlagB34 == 1; }                               // 0x00c0b770
    bool HasSubFlag388() {                                                   // 0x00c0c0e0
        char* p = *(char**)((char*)this + 0xe84);
        return p && p[0x388];
    }
    bool IsNearSelf(cCreature* pOther, float a, float b) {                   // 0x00c0d560
        return ((IProx48*)this)->IsNear(pOther, a, b);
    }
};

struct cTribe {
    IGetId* AsGetId() { return (IGetId*)this; }
    float GetRadius() { return ((IGetRadius*)this)->GetRadius(); }
    Vector3* GetClosestWater();                     // 0x00c8fe20
    Vec3List* GetPoints();                          // 0x00c97020
};

struct cRelationshipManager {
    float d00a10(int a, int b, int c);              // 0x00d00a10 (ret 0xc)
    int   d00780(float f);                          // 0x00d00780 (ret 4)
};
cRelationshipManager* RelationshipManager();        // 0x00b3d2c0

struct cPlanetModel {
    Vector3* DirectionToSurfacePosition(const Vector3* v);   // 0x00b815a0
    Vector3* MakeRandomWorldPosition(const Vector3* v);      // 0x00b81780
};
cPlanetModel* PlanetModel();                        // 0x00b3d350

struct cEventLog {
    int PostFeedbackEvent(unsigned a, unsigned b, int c, int d, int e, int f);   // 0x00dd8640
};
cEventLog* EventLog();                              // 0x00b3d3e0

struct RandomLinearCongruential {
    unsigned RandomUint32Uniform(unsigned n);       // 0x00a68fb0
};
extern RandomLinearCongruential g_random;           // 0x01601760

bool HasPendingOrder(cTribePlanData* plan, int orderType);   // 0x00ce0b60
void* FUN_00ac80d0(void* p, uint32_t type);                  // 0x00ac80d0
void* FUN_00d99500(void* p);                                 // 0x00d99500

// plan states, all reached through the planner's per-plan state block
struct CongState { int mOrderType; int mOrderId; int mPhase; float mTimer; };
struct StealState { int mOrderType; int mOrderId; float mTimer; };
struct GiftState { int mOrderType; int mOrderId; float mTimer; };
struct HuntState { int mOrderType; int mOrderId; Vector3 mTargetPos; float mTimer; };
struct GatherState { int mOrderType; int mOrderId; float mTimer; };
struct WaterState { int mOrderType; int mOrderId; float mTimer; };

// @ 0x00ce1390
bool PLANNER_STEAL_CONGREGATE_Activate(cTribePlannerContext* ctx, int, int, int, int, CongState* st)
{
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        st->mOrderType = order->mType;
        unsigned key = *order->mParam.GetUInt();
        st->mOrderId = key;
        cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
        if (plan) {
            void* tgt = order->mpTarget;
            if (tgt) {
                cTribe* target = (cTribe*)((IInterface*)tgt)->AsInterface(0x4f396a66);
                if (target) {
                    plan->mState = 4;
                    int four = 4;
                    order->mOption.SetInt(&four);
                    st->mTimer = 0.0f;
                    st->mPhase = 0;
                    float radius = target->GetRadius() + g_f_01473c70;
                    WorkerIter it(&plan->mWorkers);
                    for (; it.mCur != it.mEnd; it.Advance()) {
                        if (it.mFilter.Pass(*it.mCur)) break;
                    }
                    while (it.mCur != it.mEnd) {
                        cCreature* c = *it.mCur;
                        Variant v;
                        v.SetFloat(&radius);
                        c->GiveOrder(4, target, &v);
                        it.Advance();
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00ce1510
bool PLANNER_STEAL_CONGREGATE_Tick(cTribePlannerContext* ctx, int, int, int, int, CongState* st,
                                   WorkerFilter* pFilter, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (!ctx->mpTribePlanner->mpOrderManager->FirstPending()) return true;
    cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
    switch (st->mPhase) {
    case 1: {
        WorkerIter it;
        it.Init(&plan->mWorkers, &it.mFilter);
        for (; it.mCur != it.mEnd; it.Advance()) {
            if (!(*it.mCur)->AnimationFinished(0x5dcc520)) return true;
        }
        return false;
    }
    case 0: {
        WorkerIter it;
        it.Init(&plan->mWorkers, pFilter);
        for (; it.mCur != it.mEnd; it.Advance()) {
            cAgentOrder* o = (*it.mCur)->mpOrderManager->FirstPending();
            if (o && o->mType == 4) return true;
        }
        st->mPhase = 1;
        WorkerIter it2(&plan->mWorkers);
        for (; it2.mCur != it2.mEnd; it2.Advance()) {
            if (it2.mFilter.Pass(*it2.mCur)) break;
        }
        while (it2.mCur != it2.mEnd) {
            (*it2.mCur)->InterruptAnimation(0x5dcc520, -1, false);
            it2.Advance();
        }
        return true;
    }
    }
    return true;
}

// @ 0x00ce1690
bool PLANNER_STEALING_FOOD_Activate(cTribePlannerContext* ctx, int, int, int, int, StealState* st)
{
    cTribe* pTribe = ctx->mpTribe;
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        st->mOrderType = order->mType;
        unsigned key = *order->mParam.GetUInt();
        st->mOrderId = key;
        cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
        if (plan) {
            void* tgt = order->mpTarget;
            if (tgt) {
                cTribe* target = (cTribe*)((IInterface*)tgt)->AsInterface(0x4f396a66);
                if (target) {
                    if (g_bool_01581374) {
                        float score = RelationshipManager()->d00a10(
                            pTribe->AsGetId()->GetId(), target->AsGetId()->GetId(), 1);
                        if (RelationshipManager()->d00780(score) >= 2) return false;
                    }
                    int four = 4;
                    plan->mState = four;
                    Variant* pOpt = &order->mOption;
                    pOpt->SetInt(&four);
                    st->mTimer = 0.0f;
                    WorkerIter it(&plan->mWorkers);
                    for (; it.mCur != it.mEnd; it.Advance()) {
                        (*it.mCur)->GiveOrder(8, target, 0);
                    }
                    EventLog()->PostFeedbackEvent(0xb87901de, 0x182cd6ce, 0, 0, 1, 0);
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00ce1810
bool PLANNER_STEALING_FOOD_Tick(cTribePlannerContext* ctx, int, int, int, int, StealState* st,
                                WorkerFilter*, float dt)
{
    cTribe* ourTribe = ctx->mpTribe;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
        if (plan) {
            void* tgt = order->mpTarget;
            if (tgt) {
                cTribe* target = (cTribe*)((IInterface*)tgt)->AsInterface(0x4f396a66);
                if (target) {
                    if (g_bool_01581374) {
                        float score = RelationshipManager()->d00a10(
                            ourTribe->AsGetId()->GetId(), target->AsGetId()->GetId(), 1);
                        if (RelationshipManager()->d00780(score) >= 2) return false;
                    }
                }
            }
        }
    }
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (!order) return false;
    return HasPendingOrder((cTribePlanData*)0, 8);
}

// @ 0x00ce18f0
bool PLANNER_GIFTING_Activate(cTribePlannerContext* ctx, int, int, int, int, GiftState* st)
{
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        st->mOrderType = order->mType;
        unsigned key = *order->mParam.GetUInt();
        st->mOrderId = key;
        cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
        if (plan) {
            if (order->mpTarget) {
                cTribe* target = (cTribe*)order->mpTarget->AsInterface(0x4f396a66);
                if (target) {
                    plan->mState = 4;
                    int four = 4;
                    order->mOption.SetInt(&four);
                    st->mTimer = 0.0f;
                    WorkerIter it(&plan->mWorkers);
                    for (; it.mCur != it.mEnd; it.Advance()) {
                        (*it.mCur)->GiveOrder(9, target, 0);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00ce1a20
bool PLANNER_GIFTING_Tick(cTribePlannerContext* ctx, int, int, int, int, GiftState* st,
                          WorkerFilter*, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (ctx->mpTribePlanner->mpOrderManager->FirstPending()) {
        cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
        return HasPendingOrder(plan, 9);
    }
    return false;
}

// @ 0x00ce1a90
bool PLANNER_HUNTING_Activate(cTribePlannerContext* ctx, int, int, int, int, HuntState* st)
{
    cTribe* pTribe = ctx->mpTribe;
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (!order) return false;
    st->mOrderType = order->mType;
    unsigned key = *order->mParam.GetUInt();
    st->mOrderId = key;
    cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
    if (!plan) return false;
    int four = 4;
    plan->mState = four;
    order->mOption.SetInt(&four);
    st->mTimer = 0.0f;
    Vec3List* list;
    if (ctx->mAttitudeToTarget == 2 && ctx->mpTarget) {
        cTribe* other = (cTribe*)ctx->mpTarget->AsInterface(0x4f396a66);
        if (other) list = other->GetPoints();
        else list = pTribe->GetPoints();
    }
    else list = pTribe->GetPoints();
    Vector3 pos;
    if (list->mpBegin == list->mpEnd) {
        float radius = pTribe->GetRadius();
        pos = *PlanetModel()->MakeRandomWorldPosition(
            ((IGetRandomPos*)((char*)pTribe + 0x120))->GetRandomPos(radius + radius,
                                                                   radius * g_f_01486114));
    }
    else {
        unsigned n = (unsigned)(list->mpEnd - list->mpBegin);
        pos = *PlanetModel()->DirectionToSurfacePosition(
            &list->mpBegin[g_random.RandomUint32Uniform(n)]);
    }
    WorkerIter it(&plan->mWorkers);
    for (; it.mCur != it.mEnd; it.Advance()) {
        cCreature* c = *it.mCur;
        if (((IBool11*)c)->IsBusy()) continue;
        cAgentOrder* o = c->GiveOrder(0x1c, 0, 0);
        o->mParam.SetVec3(&pos);
    }
    return true;
}

// @ 0x00ce1c90
bool PLANNER_HUNTING_Tick(cTribePlannerContext* ctx, int, int, int, int, HuntState* st,
                          WorkerFilter*, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (!ctx->mpTribePlanner->mpOrderManager->FirstPending()) return false;
    cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
    if (!plan) return false;
    WorkerIter it(&plan->mWorkers);
    for (; it.mCur != it.mEnd; it.Advance()) {
        if (it.mFilter.Pass(*it.mCur)) break;
    }
    if (it.mCur == it.mEnd) return false;
    unsigned n = (unsigned)(plan->mWorkers.mpEnd - plan->mWorkers.mpBegin);
    cCreature* hunter = plan->mWorkers.mpBegin[g_random.RandomUint32Uniform(n)];
    if (((IBool11*)hunter)->IsBusy()) return true;
    if (hunter->mFlagB5E) return true;
    C0Obj* me = (C0Obj*)((char*)hunter + 0xc0);
    Vector3* myPos = me->GetPosition();
    int myId = ((IGetId*)hunter)->GetId();
    float best = g_fltMax;
    cCreature* target = 0;
    PtrList* cand = me->GetAttackables();
    for (void** p = cand->mpBegin; p != cand->mpEnd; ++p) {
        cCreature* c = (cCreature*)*p;
        if (!c) continue;
        void* iface = ((ICast46*)c)->Cast(0x17f243b);
        if (!iface) continue;
        void* obj = FUN_00ac80d0(iface, 0x18eb45e);
        if (!obj) continue;
        cCreature* other = (cCreature*)FUN_00d99500(obj);
        if (!other) continue;
        if (!other->IsFlagB34()) continue;
        if (other->HasSubFlag388()) continue;
        if (((IGetId*)other)->GetId() == myId) continue;
        Vector3* oPos = ((IGetPos*)((char*)other + 0xc0))->GetPosition();
        float dx = myPos->x - oPos->x, dy = myPos->y - oPos->y, dz = myPos->z - oPos->z;
        float d2 = dx * dx + dy * dy + dz * dz;
        if (!(best > d2)) continue;
        float d = sqrtf(d2);
        if (!hunter->IsNearSelf(other, 1.0f, d)) {
            if (!((IProx48*)hunter)->IsNear(other, 1.0f, d)) continue;
        }
        best = d2;
        target = other;
    }
    if (!target) return true;
    WorkerIter it2;
    it2.Init(&plan->mWorkers, &it2.mFilter);
    for (; it2.mCur != it2.mEnd; it2.Advance()) {
        cCreature* c = *it2.mCur;
        cAgentOrder* o = c->mpOrderManager->FirstPending();
        if (o && o->mType == 0xa) continue;
        c->GiveOrder(0xa, target, 0);
    }
    return true;
}

// @ 0x00ce1f60
bool PLANNER_GATHERING_Activate(cTribePlannerContext* ctx, int, int, int, int, GatherState* st)
{
    cTribe* pTribe = ctx->mpTribe;
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (!order) return false;
    st->mOrderType = order->mType;
    unsigned key = *order->mParam.GetUInt();
    st->mOrderId = key;
    cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
    if (!plan) return false;
    int four = 4;
    plan->mState = four;
    order->mOption.SetInt(&four);
    st->mTimer = 0.0f;
    cTribe* src = pTribe;
    if (ctx->mAttitudeToTarget == 2 && ctx->mpTarget) {
        cTribe* other = (cTribe*)ctx->mpTarget->AsInterface(0x4f396a66);
        if (other) src = other;
    }
    Vec3List* list = src->GetPoints();
    if (list->mpBegin == list->mpEnd) return false;
    unsigned n = (unsigned)(list->mpEnd - list->mpBegin);
    Vector3 pos = *PlanetModel()->DirectionToSurfacePosition(
        &list->mpBegin[g_random.RandomUint32Uniform(n)]);
    WorkerIter it(&plan->mWorkers);
    for (; it.mCur != it.mEnd; it.Advance()) {
        cCreature* c = *it.mCur;
        if (((IBool11*)c)->IsBusy()) continue;
        cAgentOrder* o = c->GiveOrder(2, 0, 0);
        o->mPosition = pos;
    }
    return true;
}

// @ 0x00ce20d0
bool PLANNER_GATHERING_Tick(cTribePlannerContext* ctx, int, int, int, int, GatherState* st,
                            WorkerFilter*, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (ctx->mpTribePlanner->mpOrderManager->FirstPending()) {
        cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
        return HasPendingOrder(plan, 2);
    }
    return false;
}

// @ 0x00ce2140
bool PLANNER_WATERING_Activate(cTribePlannerContext* ctx, int, int, int, int, WaterState* st)
{
    cTribe* pTribe = ctx->mpTribe;
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        st->mOrderType = order->mType;
        unsigned key = *order->mParam.GetUInt();
        st->mOrderId = key;
        cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
        if (plan) {
            int four = 4;
            plan->mState = four;
            order->mOption.SetInt(&four);
            st->mTimer = 0.0f;
            Vector3 water = *pTribe->GetClosestWater();
            if (ctx->mAttitudeToTarget == 2 && ctx->mpTarget) {
                cTribe* other = (cTribe*)ctx->mpTarget->AsInterface(0x4f396a66);
                if (other) water = *other->GetClosestWater();
            }
            WorkerIter it(&plan->mWorkers);
            for (; it.mCur != it.mEnd; it.Advance()) {
                cCreature* c = *it.mCur;
                if (((IBool11*)c)->IsBusy()) continue;
                Variant v;
                v.SetVec3(&water);
                c->GiveOrder(1, 0, &v);
            }
            return true;
        }
    }
    return false;
}

// @ 0x00ce22c0
bool PLANNER_WATERING_Tick(cTribePlannerContext* ctx, int, int, int, int, WaterState* st,
                           WorkerFilter*, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (ctx->mpTribePlanner->mpOrderManager->FirstPending()) {
        cTribePlanData* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
        return HasPendingOrder(plan, 1);
    }
    return false;
}
