// Slice s00d8a2a0 -- SP creature behaviour-tree activate/tick/deactivate callbacks (retail).
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// Every entry point is a cdecl behaviour-tree script callback.  The first argument is always the
// creature, the following four are the generic callback slots, then comes the per-behaviour state
// block (owned by the tree node) and, for ticks, an "out" pair and/or the frame delta time.
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- shared constants (.rdata)
extern const float  kEffect14;      // 0x0169f03c  0.029203802
extern const float  kEffect18;      // 0x0169f040  0.043026950
extern const float  kEffect1c;      // 0x0169f044  0.047665816
extern const float  kOne;           // 0x01485720  1.0
extern const float  kTwo;           // 0x01470f1c  2.0
extern const double kTwoDouble;     // 0x013f1298  2.0 (double)
extern const float  kPointNine;     // 0x013ec4b4  0.9
extern const float  kPointThree;    // 0x013eb8c8  0.3
extern const float  kPointZeroOne;  // 0x013eb960  0.01
extern const float  kFloatMax;      // 0x0147c030  FLT_MAX
extern const float  kFourHundred;   // 0x013f0e84  400.0
extern const float  kTen;           // 0x01473c70  10.0
extern const float  kEatFoodRate;   // 0x01687a44

// ---------------------------------------------------------------- generic ref-counted object view
// One vtable-shaped view over every interface this slice pokes at; only the slots that are actually
// called carry a name.  Slot offsets: +0x00 AddRef, +0x04 Release, +0x14 Query(id), +0x2c
// GetPosition, +0x5c vf5c(id), +0x70 vf70, +0x74 GetRadius, +0x84 vf84, +0xbc AddRefBundle,
// +0xc0 ReleaseBundle.
class cRefObject {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    PV(2) PV(3) PV(4)
    virtual int  Query(uint32_t id);              // +0x14
    PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();            // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual int  vf5c(uint32_t id);               // +0x5c
    PV(24) PV(25) PV(26) PV(27)
    virtual float vf70();                         // +0x70
    virtual float GetRadius();                    // +0x74
    PV(30) PV(31) PV(32)
    virtual void vf84(void* obj, int a, int b);   // +0x84
    PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
    virtual void AddRefBundle();                  // +0xbc
    virtual void ReleaseBundle();                 // +0xc0
};

// Spatial/positional sub-object: embedded in creatures (+0xc0), bundles (+0x34) and spots (+0x260).
class cSpatialObject {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();            // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
    PV(24) PV(25) PV(26) PV(27)
    virtual float vf70();                         // +0x70
    virtual float GetRadius();                    // +0x74
};

// Locomotive object (creature +0xc0): the spatial view plus the goal/effect entry points.
class cLocomotiveObject : public cSpatialObject {
public:
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
    PV(54)
    virtual void PlayEffectSpec(void* spec);      // +0xdc
    bool __thiscall IsNearGoal();                 // 0x00c42e20
    float __thiscall FUN_00c422c0();              // 0x00c422c0
};

// Behaviour-tree interface (a base sub-object eight bytes into the tree object).
class BehaviorTreeHead {
public:
    cRefObject* __thiscall Play(unsigned id, int flags);   // 0x00bc96a0, ret 8
    void __thiscall ClearAll(unsigned a, unsigned mask);    // 0x00bc98f0, ret 8
};

// Behaviour tree stored at creature +0xb4c; both entry points are invoked on this + 8.
struct nSPBehaviorTree {
    uint32_t pad00[2];                             // +0x00..+0x07
    BehaviorTreeHead mHead;                        // +0x08
};

// Record handed back by Play(): +0x0c is a kind tag for RECEIVE_ITEM and an animation length
// elsewhere, +0x10 a value the caller interprets per behaviour.
class cAnimNode {
public:
    uint32_t pad00[3];                            // +0x00
    union { int mKind; float mf0c; };             // +0x0c
    float    mf10;                                // +0x10
};

// Object at creature +0xb20 whose +0x590 float is tested for "already eaten".
class cCreatureSettings {
public:
    uint32_t pad00[0x590 / 4];                    // +0x000
    float    mf590;                               // +0x590
};

// Effect request built on the stack and filled in by cLocomotiveObject::PlayEffectSpec.
struct LocoEffectSpec {
    void*    mpData;                              // +0x00  owned heap buffer
    void*    mpEnd;                               // +0x04
    void*    mpCap;                               // +0x08
    uint32_t pad0c[2];                            // +0x0c..+0x13 (never touched)
    float    mf14;                                // +0x14
    float    mf18;                                // +0x18
    float    mf1c;                                // +0x1c
    float    mf20;                                // +0x20
    int      m24;                                 // +0x24
    uint32_t pad28[9];                            // +0x28..+0x4b
    uint8_t  mb4c;                                // +0x4c
    uint8_t  pad4d[3];                            // +0x4d..+0x4f
    float    mf50;                                // +0x50
    float    mf54;                                // +0x54
    float    mf58;                                // +0x58
    int      m5c;                                 // +0x5c
    float    mf60;                                // +0x60
    float    mf64;                                // +0x64
    float    mf68;                                // +0x68
    float    mf6c;                                // +0x6c
    int      m70;                                 // +0x70
};

inline void InitLocoEffectSpec(LocoEffectSpec* s)
{
    s->mpData = 0;
    s->mpEnd = 0;
    s->mpCap = 0;
    s->mf14 = kEffect14;
    s->mf18 = kEffect18;
    s->mf1c = kEffect1c;
    s->mf20 = kOne;
    s->m24 = 0;
    s->mb4c = 0;
    s->mf50 = 0.0f;
    s->mf54 = 0.0f;
    s->mf58 = 0.0f;
    s->m5c = 0;
    s->mf60 = kTwo;
    s->mf64 = kPointNine;
    s->mf68 = kFloatMax;
    s->mf6c = 0.0f;
    s->m70 = 0;
}

extern "C" void __cdecl OperatorDeleteArray(void* p);   // 0x00f47380

// eastl teardown of the buffer the effect call may have allocated: the allocation header sits four
// bytes in front of the payload and only a real (non-default) allocation is returned to the heap.
inline void FreeOwnedBuffer(void* p)
{
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        OperatorDeleteArray(p);
}

// ---------------------------------------------------------------- creature
// The driven object: a citizen creature with the locomotive sub-object at +0xc0 and the behaviour
// tree at +0xb4c (same layout as the SP::TRIBE_* slice s00db10d0).
struct Citizen {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    virtual void vf84(void* obj, int a, int b);   // +0x84
    uint32_t pad04[0xc0 / 4 - 1];                 // +0x04..+0xbf
    cLocomotiveObject   mLoco;                    // +0xc0 (vtable view, 4 bytes)
    uint32_t padLoco[(0x74 - 4) / 4];             // +0xc4..+0x133  rest of the locomotive object
    uint32_t pad1a0[(0xb20 - 0x134) / 4];         // +0x134..+0xb1f
    cCreatureSettings*  mpEatenState;             // +0xb20
    uint32_t padB24[(0xb4c - 0xb24) / 4];         // +0xb24..+0xb4b
    nSPBehaviorTree*    mpBehavior;               // +0xb4c
    uint32_t padB50[2];                           // +0xb50..+0xb57
    uint8_t  mbB58[6];                            // +0xb58..+0xb5d
    uint8_t  mbB5e;                               // +0xb5e

    bool __thiscall FUN_00c13c60(void* obj, int a, int b);            // 0x00c13c60, ret 0xc
    bool __thiscall FUN_00c0f5f0();                                   // 0x00c0f5f0, ret 0
    void __thiscall FUN_00c15bd0(int a, int b, int c);                // 0x00c15bd0, ret 0xc
    void __thiscall FUN_00c14750(int a);                              // 0x00c14750, ret 4
    void __thiscall FUN_00c0cff0(int a);                              // 0x00c0cff0, ret 4
    void __thiscall FUN_00c0d240();                                   // 0x00c0d240, ret 0
    void __thiscall SetStealthed(int a, int b);                       // 0x00c1aed0, ret 8
    void __thiscall Hover(int a);                                     // 0x00c13a30, ret 4
    void __thiscall InterruptAnimation(unsigned id, int a, int b);    // 0x00c12310, ret 0xc
    int  __thiscall PlayAnimation(unsigned id, int a, int b);         // 0x00c12190, ret 0xc
    bool __thiscall AnimationFinished(int handle);                    // 0x00c12400, ret 4
    int  __thiscall PlayAnimationWithTarget(unsigned id, const Vec3* p, int handle);  // 0x00c14910, ret 0xc
    void __thiscall MoveToPointAtSpeed(int mode, const Vec3* p, float f1, float f2);  // 0x00c1c1d0, ret 0x10
    void __thiscall MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* facing,
                                               float f1, float f2);   // 0x00c1c5c0, ret 0x14
};

// ---------------------------------------------------------------- behaviour target objects
// Object referenced by the behaviour state: a ref-counted clump/citizen with an embedded spatial
// bundle at +0x34 and a spot handle at +0x128.  Its +0x2c slot is a "finished" predicate (not the
// position getter cRefObject exposes at the same offset).
class cTargetObject {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    PV(2) PV(3) PV(4)
    virtual int  Query(uint32_t id);              // +0x14
    PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsFinished();                    // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    uint32_t pad04[0xc];                          // +0x04..+0x33
    cSpatialObject mBundle;                       // +0x34 (vtable view, 4 bytes)
    uint32_t padAc[(0x108 - 0x38) / 4];           // +0x38..+0x107
    int      mState108;                           // +0x108  (2..4 = interactable)
    uint32_t pad10c[7];                           // +0x10c..+0x127
    cRefObject* mpSpot;                           // +0x128
    uint32_t pad12c[2];                           // +0x12c..+0x133
    float    mf134;                               // +0x134
};

// Object kept at creature +0xb4c+... : group of creatures with At()/IndexOf() over a record table.
class cGroup : public cRefObject {
public:
    uint32_t pad04[(0xc0 - 4) / 4];               // +0x04..+0xbf
    cSpatialObject mLoco;                         // +0xc0
    void* __thiscall At(unsigned idx);            // 0x00c0f8a0, ret 4
    int   __thiscall IndexOf(const void* p);      // 0x00c0f8f0, ret 4
};

class cAsset : public cRefObject {                // ref-counted bundle asset (acts as behaviour target)
public:
    uint32_t pad04[0x34 / 4 - 1];                 // +0x04..+0x33
    cSpatialObject mBundle;                       // +0x34
};

// Intrusive reference holder at behaviour-state +0x1c (assign/release through 0xc70110).
class cAutoRef {
public:
    cAsset* mp;
    void __thiscall Assign(cAsset* p);            // 0x00c70110, ret 4
};

// Object returned by cRefObject::Query(0x4f396a66): a tribe-side spot holder.
class cSpotServer : public cRefObject {
public:
    uint32_t pad04[(0x260 - 4) / 4];              // +0x04..+0x25f
    cTargetObject* mp260;                         // +0x260
    void __thiscall FindSpot(int kind, int idx);  // 0x00c98750, ret 8
    const Vec3* __thiscall FUN_00c986d0(Vec3* out, int kind, Citizen* c);  // 0x00c986d0, ret 0xc
};

class cGameMgr {
public:
    cRefObject* __thiscall GetContainer();        // 0x00ac79d0 (only used as an identity token)
    float __thiscall FUN_00ac7d10(float f, void* spot, void* node);  // 0x00ac7d10, ret 0xc
};

// Planet model.
class cPlanetModel {
public:
    const Vec3* __thiscall DirectionToSurfacePosition(Vec3* out, const Vec3* p);  // 0x00b815a0, ret 8
};

// ---------------------------------------------------------------- free functions / globals
cRefObject*  __cdecl FUN_00d998d0(const void* node, unsigned id);   // 0x00d998d0
cPlanetModel* __cdecl PlanetModel(Vec3* out, const Vec3* p);        // 0x00b3d350
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);           // 0x00449c20
float __cdecl FUN_00572a10(float lo, float hi);                     // 0x00572a10
void  __cdecl FUN_00bcbc80();                                       // 0x00bcbc80
cGameMgr* __cdecl FUN_00b3d2b0();                                   // 0x00b3d2b0
void  __cdecl EatFood(Citizen* c, float amount, unsigned id, unsigned flags);  // 0x00d85ad0
float __cdecl GetPropertyTf(void* props, unsigned id, float def);   // 0x004e1c70

class cRandomLC {
public:
    float __thiscall RandomDoubleUniform();       // 0x009360d0
};
extern cRandomLC g_Random;                        // 0x01601760

class cArchetypeOwner {
public:
    uint32_t pad00[0x130 / 4];                    // +0x000
    void*    mpProps;                             // +0x130
};
class cSpeciesArchetype {
public:
    uint32_t pad00[0x1c / 4];                     // +0x000
    cArchetypeOwner* mpOwner;                     // +0x01c
};
cSpeciesArchetype* __cdecl FUN_00d1e660();        // 0x00d1e660

// ---------------------------------------------------------------- behaviour state blocks
struct StateReceiveItem {                          // 0xd8a2a0 / 0xd8a500
    int      m0;                                   // +0x00
    Vec3     mTarget;                              // +0x04
    float    mf10;                                 // +0x10
    uint8_t  mb14;                                 // +0x14
    uint8_t  pad15[3];                             // +0x15
    cGroup*  mp18;                                 // +0x18
    cAutoRef m1c;                                  // +0x1c
    uint8_t  mb20;                                 // +0x20
    uint8_t  pad21[3];                             // +0x21
    int      m24;                                  // +0x24
};

struct StateUfoClump {                             // 0xd8a750 / 0xd8a8c0
    int   m0;                                      // +0x00
    cAsset* mp4;                                   // +0x04
};

struct StateEnterSpot {                            // 0xd8aa40
    cTargetObject* mp0;                            // +0x00
    uint32_t pad04[2];                             // +0x04..+0x0b
    int      m0c;                                  // +0x0c
};

struct StateSneak {                                // 0xd8ab30
    cTargetObject* mp0;                            // +0x00
    float    mf04;                                 // +0x04
    int      m08;                                  // +0x08
    int      m0c;                                  // +0x0c
};

struct StateBundle {                               // 0xd8ac30 / 0xd8af20 / 0xd8b1a0
    cTargetObject* mp0;                            // +0x00
    int      m04;                                  // +0x04  animation handle
    int      m08;                                  // +0x08  phase
    float    mf0c;                                 // +0x0c  remaining amount
    float    mf10;                                 // +0x10  total amount
    int      m14;                                  // +0x14  spot index
};

// "out" pair written by the Ufo ticks (float value + zero flag word).
struct TickOut {
    float mf0;                                     // +0x00
    int   m4;                                      // +0x04
};

// ===========================================================================
// @ 0x00d8a2a0
// SP::RECEIVE_ITEM_Activate
// ===========================================================================
bool __cdecl FUN_00d8a2a0(Citizen* c, void*, void*, void*, void*, StateReceiveItem* st)
{
    if (st != 0) {
        st->mp18 = 0;
        st->m1c.mp = 0;
    }
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0, 0x40000);
    if (node == 0 || node->mKind != 7)
        return false;

    unsigned index = (unsigned)node->mf10;
    cGroup* grp = (cGroup*)FUN_00d998d0(node, 0xd0036e08);
    cGroup* old = st->mp18;
    if (grp != old) {
        if (grp != 0)
            grp->AddRef();
        st->mp18 = grp;
        if (old != 0)
            old->Release();
    }
    st->m1c.Assign((cAsset*)st->mp18->At(index));

    if (st->mp18 == 0 || st->m1c.mp == 0)
        return false;
    if (!c->FUN_00c13c60(st->m1c.mp, 1, 0))
        return false;
    if (c->FUN_00c0f5f0()) {
        c->FUN_00c15bd0(0, 0, 0);
        if (c->FUN_00c0f5f0())
            return false;
    }
    if (st->mp18->IndexOf(st->m1c.mp) == -1)
        return false;

    const Vec3* pos = st->m1c.mp->GetPosition();
    Vec3 tmp;
    cPlanetModel* planet = PlanetModel(&tmp, pos);
    st->mTarget = *planet->DirectionToSurfacePosition(&tmp, pos);

    float speed = c->mLoco.GetRadius() * kPointThree;
    speed = c->mLoco.GetRadius() + speed;
    speed = st->mp18->mLoco.GetRadius() + speed;

    Vec3 diff;
    Vec3 facing;
    const Vec3* lp = c->mLoco.GetPosition();
    diff.x = st->mTarget.x - lp->x;
    diff.y = st->mTarget.y - lp->y;
    diff.z = st->mTarget.z - lp->z;
    c->MoveToPointAndFacingAtSpeed(2, &st->mTarget, normalized_safe(&facing, &diff), speed, kTwo);
    c->FUN_00c14750(1);
    c->vf84(0, 0, 0);
    st->mf10 = 0.0f;
    st->mb14 = 0;
    st->mb20 = (c->mpEatenState->mf590 == 0.0f);
    st->m24 = 0;
    st->m0 = 0;
    return true;
}

// ===========================================================================
// @ 0x00d8a500
// SP::RECEIVE_ITEM_Deactivate
// ===========================================================================
void __cdecl FUN_00d8a500(Citizen* c, void*, void*, void*, void*, StateReceiveItem* st)
{
    c->mpBehavior->mHead.ClearAll(0, 0x40000);
    if (st != 0) {
        cAsset* asset = st->m1c.mp;
        if (asset != 0)
            asset->ReleaseBundle();
        cGroup* grp = st->mp18;
        if (grp != 0)
            grp->Release();
    }
}

// ===========================================================================
// @ 0x00d8a550
// SP::STUN_Activate
// ===========================================================================
void __cdecl FUN_00d8a550(Citizen* c)
{
    c->mpBehavior->mHead.ClearAll(0, 0x2000000);
    if (c->mbB5e != 0)
        return;
    LocoEffectSpec spec;
    InitLocoEffectSpec(&spec);
    c->mLoco.PlayEffectSpec(&spec);
    FreeOwnedBuffer(spec.mpData);
    c->FUN_00c0cff0(0);
    c->FUN_00c14750(0);
}

// ===========================================================================
// @ 0x00d8a660
// SP::HELD_PANIC_Activate
// ===========================================================================
bool __cdecl FUN_00d8a660(Citizen* c)
{
    c->InterruptAnimation(0x48601c0, -1, 0);
    LocoEffectSpec spec;
    InitLocoEffectSpec(&spec);
    c->mLoco.PlayEffectSpec(&spec);
    FreeOwnedBuffer(spec.mpData);
    return true;
}

// ===========================================================================
// @ 0x00d8a750
// SP::HOLD_BUNDLE_Tick
// ===========================================================================
bool __cdecl FUN_00d8a750(Citizen* c, void*, void*, void*, void*, TickOut* out,
                          StateUfoClump* st)
{
    if (st == 0 || st->mp4 == 0)
        return false;
    c->vf84(st->mp4, 1, 0);
    if (st->mp4 != 0 && st->mp4->vf5c(0x1186577) != 0)
        c->InterruptAnimation(0x2481de5, -1, 0);

    out->mf0 = FUN_00572a10(kOne, kTwo);
    out->m4 = 0;

    LocoEffectSpec spec;
    InitLocoEffectSpec(&spec);
    c->mLoco.PlayEffectSpec(&spec);
    FreeOwnedBuffer(spec.mpData);
    return true;
}

// ===========================================================================
// @ 0x00d8a8c0
// SP::CitizenTree::UfoOpenClump_Tick
// ===========================================================================
bool __cdecl FUN_00d8a8c0(Citizen* c, void*, void*, void*, void*, TickOut* out,
                          StateUfoClump* st)
{
    if (st->mp4 == 0)
        return false;
    c->vf84(st->mp4, 1, 0);
    if (st->mp4 != 0 && st->mp4->vf5c(0x1186577) != 0)
        c->InterruptAnimation(0x2481de5, -1, 0);

    float v = g_Random.RandomDoubleUniform() + 1.0f;
    if (v < (float)kTwoDouble) {
        if (v <= kOne)
            v = kOne;
    } else {
        v = (float)kTwoDouble;
    }
    out->mf0 = v;
    out->m4 = 0;

    LocoEffectSpec spec;
    InitLocoEffectSpec(&spec);
    c->mLoco.PlayEffectSpec(&spec);
    FreeOwnedBuffer(spec.mpData);
    c->Hover(1);
    return true;
}

// ===========================================================================
// @ 0x00d8aa40
// SP::ENTER_SPOT_Tick
// ===========================================================================
bool __cdecl FUN_00d8aa40(Citizen* c, void*, void*, void*, void*, StateEnterSpot* st)
{
    if (st != 0)
        st->mp0 = 0;
    bool ok = false;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0, 0x100);
    if (node != 0) {
        cTargetObject* tgt = (cTargetObject*)FUN_00d998d0(node, 0x61494bd);
        cTargetObject* old = st->mp0;
        if (tgt != old) {
            if (tgt != 0)
                tgt->AddRef();
            st->mp0 = tgt;
            if (old != 0)
                old->Release();
        }
        if (st->mp0 != 0) {
            int state = st->mp0->mState108;
            if (state >= 2 && state <= 4) {
                float radius = c->mLoco.GetRadius();
                // Retail computes this approach speed and then discards it.
                float speed = radius + st->mp0->mBundle.vf70() + kPointZeroOne;
                (void)speed;
                st->m0c = 0;
                c->FUN_00c14750(0);
                c->MoveToPointAtSpeed(2, st->mp0->mBundle.GetPosition(), radius, radius);
                ok = true;
            }
        }
    }
    return ok;
}

// ===========================================================================
// @ 0x00d8ab30
// SP::SNEAK_Tick
// ===========================================================================
bool __cdecl FUN_00d8ab30(Citizen* c, void*, void*, void*, void*, StateSneak* st, void*,
                          float dt)
{
    if (st->mp0 == 0
        || st->mp0->IsFinished()
        || st->mp0->mState108 < 2
        || st->mp0->mState108 > 4)
        return false;

    switch (st->m0c) {
    case 0:
        if (c->mLoco.IsNearGoal()) {
            st->mf04 = GetPropertyTf(FUN_00d1e660()->mpOwner->mpProps, 0x62dca9c8, kTen);
            c->SetStealthed(0, 0);
            st->m0c = 1;
        }
        break;

    case 1:
        st->mf04 = st->mf04 - dt;
        if (st->mf04 <= 0.0f) {
            st->m08 = 0;
            FUN_00bcbc80();
        }
        if (c->AnimationFinished(st->m08)) {
            st->m08 = c->PlayAnimation(0x65d1437, 1, -1);
            return true;
        }
        break;

    default:
        return false;
    }
    return true;
}

// ===========================================================================
// @ 0x00d8ac30
// SP::TRIBE_SAVE_BUNDLE_Activate
// ===========================================================================
void __cdecl FUN_00d8ac30(Citizen* c, void*, void*, void*, void*, StateBundle* st)
{
    if (st != 0 && st->mp0 != 0)
        st->mp0->Release();
    if (c->mbB5e == 0) {
        c->FUN_00c0d240();
        c->FUN_00c14750(0);
        c->SetStealthed(0, 0);
    }
}

// ===========================================================================
// @ 0x00d8af20
// SP::TRIBE_SAVE_BUNDLE_Tick
// ===========================================================================
bool __cdecl FUN_00d8af20(Citizen* c, void*, void*, void*, void*, StateBundle* st, void*,
                          float dt)
{
    cTargetObject* tgt = st->mp0;
    if (tgt == 0 || tgt->IsFinished()) {
        c->mpBehavior->mHead.ClearAll(0, 0x100);
        return false;
    }
    cRefObject* container = FUN_00b3d2b0()->GetContainer();
    if (st->mp0->mpSpot != container) {
        cRefObject* spot0 = st->mp0->mpSpot;
        if (spot0 == 0 || spot0->Query(0x4f396a66) == 0) {
            c->mpBehavior->mHead.ClearAll(0, 0x100);
            return false;
        }
    }
    cSpotServer* spot = 0;
    if (st->mp0->mpSpot != 0)
        spot = (cSpotServer*)st->mp0->mpSpot->Query(0x4f396a66);

    switch (st->m08) {
    case 0:
        if (c->mLoco.FUN_00c422c0() <= kFourHundred)
            c->SetStealthed(1, 0);
        if (c->mLoco.IsNearGoal())
            st->m08 = 1;
        break;

    case 1: {
        c->SetStealthed(0, 0);
        float ratio = st->mf0c / st->mf10;
        EatFood(c, kEatFoodRate * ratio * dt, 0x133b8599, 0);
        cTargetObject* node = st->mp0;
        float before = node->mf134;
        float delta = ratio * dt;
        st->mf0c = st->mf0c - delta;
        st->mf10 = st->mf10 - dt;
        cGameMgr* mgr = FUN_00b3d2b0();
        mgr->FUN_00ac7d10(delta, node->mpSpot, node);
        if (before - delta <= 0.0f || st->mf0c <= 0.0f) {
            st->m08 = 2;
            return true;
        }
        if (st->m04 != 0 && !c->AnimationFinished(st->m04))
            return true;
        unsigned id = (spot != 0) ? 0x6568320 : 0x6568374;
        st->m04 = c->PlayAnimationWithTarget(id, node->mBundle.GetPosition(), -1);
        break;
    }

    case 2:
        if (st->mp0 != 0) {
            if (spot != 0)
                spot->FindSpot(0xd, st->m14);
            st->m14 = -1;
            cTargetObject* ref = st->mp0;
            if (ref != 0) {
                st->mp0 = 0;
                ref->Release();
            }
        }
        if (st->m04 != 0 && !c->AnimationFinished(st->m04))
            return true;
        c->mpBehavior->mHead.ClearAll(0, 0x100);
        return false;

    default:
        break;
    }
    return true;
}

// ===========================================================================
// @ 0x00d8b1a0
// SP::TRIBE_SAVE_BUNDLE_Deactivate
// ===========================================================================
void __cdecl FUN_00d8b1a0(Citizen* c, void*, void*, void*, void*, StateBundle* st)
{
    if (st != 0 && st->mp0 != 0)
        st->mp0->Release();
    if (st->mp0 != 0) {
        cRefObject* spot0 = st->mp0->mpSpot;
        if (spot0 != 0) {
            cSpotServer* spot = (cSpotServer*)spot0->Query(0x4f396a66);
            if (spot != 0)
                spot->FindSpot(0xd, st->m14);
        }
        st->m14 = -1;
    }
    if (c->mbB5e == 0) {
        c->FUN_00c0d240();
        c->FUN_00c14750(0);
        c->SetStealthed(0, 0);
    }
}
