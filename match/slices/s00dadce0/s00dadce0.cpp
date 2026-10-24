// Slice s00dadce0: one spawn-placement test (0x00dadfb0). Looks up a region on the input's
// owner, has the host attach to it, picks a random radius in [1,2] from the shared math RNG,
// copies the input position into the output record, and returns true when the region's
// position lies strictly within distance 1 of that position.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (scalar SSE float math, x87 for the double RNG).
#include "types.h"

namespace EA {
namespace Random {
class RandomLinearCongruential {
public:
    uint32_t mnSeed;
    double RandomDoubleUniform();
};
}
}
extern EA::Random::RandomLinearCongruential sMathRandomA;   // 0x1601760

#define VFILL(n) virtual void vs##n() {}

// Object reached through SpawnIn::owner; vtable slot 0x5c (index 23) finds a region by key.
struct RegionOwner {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10) VFILL(11) VFILL(12) VFILL(13) VFILL(14) VFILL(15)
    VFILL(16) VFILL(17) VFILL(18) VFILL(19) VFILL(20) VFILL(21) VFILL(22)
    virtual struct Region* FindRegion(uint32_t key);
};

// Embedded sub-object at Region+0xc0; vtable slot 0x2c (index 11) returns a float[3] position.
struct RegionPosition {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10)
    virtual float* GetPosition();
};

struct Region {
    char pad0[0xc0];
    RegionPosition sub;                                   // +0xc0
    char pad1[0x5a8 - 0xc0 - sizeof(RegionPosition)];
    char target[4];                                       // +0x5a8, address handed to the host
};

// Host object; vtable slot 0x84 (index 33) attaches a target pointer with two flags.
struct SpawnHost {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10) VFILL(11) VFILL(12) VFILL(13) VFILL(14) VFILL(15)
    VFILL(16) VFILL(17) VFILL(18) VFILL(19) VFILL(20) VFILL(21) VFILL(22) VFILL(23)
    VFILL(24) VFILL(25) VFILL(26) VFILL(27) VFILL(28) VFILL(29) VFILL(30) VFILL(31)
    VFILL(32)
    virtual void Attach(void* p, bool a, bool b);
};

struct SpawnIn {
    int32_t pad0;
    RegionOwner* owner;                                   // +0x4
    int32_t pad1;
    float x, y, z;                                        // +0xc, +0x10, +0x14
};

struct SpawnOut {
    int32_t zero0;                                        // +0x0
    float radius;                                         // +0x4
    float x, y, z;                                        // +0x8, +0xc, +0x10
    int32_t zero1;                                        // +0x14
};

// Clamp to [1,2]. Not NaN-safe in the same way as the original's branch order, but the RNG never yields NaN.
static inline double ClampRadius(double v)
{
    if (2.0 <= v)
        return 2.0;
    if (v < 1.0)
        return 1.0;
    return v;
}

// @ 0x00dadfb0  cdecl; four of the seven stack arguments are never read.
bool SpawnPlacementTest(SpawnHost* host, int32_t, int32_t, int32_t, int32_t, SpawnOut* out, SpawnIn* in)
{
    RegionOwner* owner = in->owner;
    if (owner != 0) {
        Region* region = owner->FindRegion(0xce9f6639);
        if (region != 0) {
            host->Attach(region->target, true, false);
            out->zero0 = 0;
            out->radius = (float)ClampRadius(sMathRandomA.RandomDoubleUniform() + 1.0);
            *(uint32_t*)&out->x = *(uint32_t*)&in->x;     // integer copies, as in the original
            *(uint32_t*)&out->y = *(uint32_t*)&in->y;
            *(uint32_t*)&out->z = *(uint32_t*)&in->z;
            out->zero1 = 0;
            const float* p = region->sub.GetPosition();
            float dx = out->x - p[0];
            float dy = out->y - p[1];
            float dz = out->z - p[2];
            float d2 = dx * dx;
            d2 += dy * dy;
            d2 += dz * dz;
            return 1.0f > d2;
        }
    }
    return false;
}


// =====================================================================================
// gold7 slice s00dadce0: the SP citizen behaviour-tree callbacks for the awareness
// (attack/greet), tribe-vignette, worship-artifact and domestication behaviours.  Each
// entry point is a cdecl behaviour callback: the creature, four unused callback
// arguments, the per-behaviour state block owned by the tree node and (for the vignette)
// the caller's request word.  Helpers keep their FUN_ addresses; the record layouts are
// the retail ones the disassembly reads.
// =====================================================================================
namespace SP {

struct Vec3 {
    float x, y, z;
};

#define PV(n) virtual void pv##n();

template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

// ---- constants (only the addresses are known; identities from the using code) --------
extern const float g_1473c70;           // 0x01473c70  10.0  vignette timeout
extern const float g_1486110;           // 0x01486110  20.0  attack stimulus value
extern const float g_1470f1c;           // 0x01470f1c  2.0   upper bound / speed
extern const float g_1486114;           // 0x01486114  height jitter bound
extern const float g_1485720;           // 0x01485720  1.0
extern const float g_147c218;           // 0x0147c218  "no target" stimulus value
extern const float g_13ebc4c;           // 0x013ebc4c  60.0  worship stimulus value
extern const uint32_t g_15d1164;        // 0x015d1164  default order payload word

float FUN_00572a10(float lo, float hi);                 // 0x00572a10  RandomFloatRange
void* WatchMemoryBlock(uint32_t block);                 // 0x00d999d0

// ---- spatial / locomotion chain ------------------------------------------------------
// Slots used here: +0x2c position, +0x58 at-goal, +0x70 speed/height, +0x74 distance,
// +0xbc/+0xc0 reference bundle, +0xec refresh.
struct RefA {
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                              // +0x2c
};
struct RefB : VPad<10, RefA> { virtual bool IsAtGoal(); };          // +0x58
struct RefC : VPad<5, RefB> { virtual float GetSpeed(); };          // +0x70
struct RefD : RefC { virtual float GetDistance(); };                // +0x74
struct RefE : VPad<17, RefD> {
    virtual void AddRefBundle();                                    // +0xbc
    virtual void ReleaseBundle();                                   // +0xc0
};
struct RefObj : VPad<10, RefE> { virtual void NotifyEc(); };        // +0xec

struct Loco : RefObj {
    bool IsNearGoal();                                             // 0x00c42e20
    void* FUN_00c420d0();                                          // 0x00c420d0  nearby list
};

// ---- the 0x58 query of creature +0xb54 -----------------------------------------------
struct cTargetV0 { virtual void q00(); };
struct cTargetQuery : VPad<21, cTargetV0> {
    virtual void Query(int* id, int a, int* count, int b);          // +0x58
};

// ---- creature chain (the creature and the block WatchMemoryBlock returns) ------------
struct cCreatureV0 {
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
    virtual void pv2();                                             // +0x08
    virtual void* GetAnimEvent();                                   // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsTargetable();                                    // +0x2c
};
struct cCreatureV1 : VPad<7, cCreatureV0> { virtual void* GetRid(); };            // +0x4c
struct cCreatureV2 : VPad<13, cCreatureV1> {
    virtual void Notify(void* p, int a, int b);                     // +0x84
};
struct cCreatureV3 : VPad<11, cCreatureV2> { virtual void* LookupOrder(uint32_t key); };  // +0xb4

// Order value record returned by LookupOrder; +0x08 is the tag the behaviours compare.
struct cOrderValue {
    uint32_t pad00;                                                 // +0x00
    uint32_t pad04;                                                 // +0x04
    int32_t  mTag;                                                  // +0x08
};

class cAnimNode {                                                   // result of Play()
public:
    uint32_t pad00[3];                                              // +0x00..+0x0b
    int32_t  mKind;                                                 // +0x0c
};

struct BehaviorStimuli {
    cAnimNode* Play(uint32_t id, int flags);                        // 0x00bc96a0
    void       ClearAll(uint32_t a, uint32_t mask);                 // 0x00bc98f0
    void       SetStimulus(uint32_t a, uint32_t b, float f, void* d);   // 0x00bc97f0
};

struct cBundleQuery {                                               // creature +0x34
    void* FUN_00cee330();                                           // 0x00cee330
};

// Object reached through the bundle query; only its +0x134 float is read.
struct cBundleObj {
    uint8_t pad00[0x134];                                           // +0x000..+0x133
    float   mf134;                                                  // +0x134
};

struct cSPTimer {                                                   // creature +0xfd0
    void Restart();                                                 // 0x00bc3130
};

struct cTribe;
struct cTribeVec;
struct cOrderNode;
struct cAgentOrder;
struct nSPBehaviorTree;
struct cArtifact;

class cSPCreatureBase : public cCreatureV3 {
public:
    uint32_t pad04[(0x34 - 4) / 4];                                 // +0x004..+0x033
    cBundleQuery mBundle;                                           // +0x034
    uint8_t  pad35[0xc0 - 0x35];                                    // +0x035..+0x0bf
    Loco     mLoco;                                                 // +0x0c0
    uint8_t  padC4[0x135 - 0xc4];                                   // +0x0c4..+0x134
    uint8_t  mb135;                                                 // +0x135  targetable flag
    uint8_t  pad136[0x5a8 - 0x136];                                 // +0x136..+0x5a7
    uint8_t  mb5a8;                                                 // +0x5a8  handed to Notify
    uint8_t  pad5a9[0xb4c - 0x5a9];                                 // +0x5a9..+0xb4b
    nSPBehaviorTree* mpBehavior;                                    // +0xb4c
    cTargetQuery* mpB54;                                            // +0xb54
    uint8_t  padB58[0xfd0 - 0xb58];                                 // +0xb58..+0xfcf
    cSPTimer mTimer;                                                // +0xfd0

    char     FUN_00c0e0c0(uint32_t id);                             // 0x00c0e0c0
    void     FUN_00c0d0c0(uint32_t a, char b);                      // 0x00c0d0c0
    void*    GetTargetAsCreature();                                 // 0x00c0ee70
    bool     AnimationFinished(uint32_t handle);                    // 0x00c12400
    uint32_t PlayAnimationWithTargetObj(uint32_t id, void* target, int a, int b);    // 0x00c14940
    uint32_t InterruptAnimationWithTargetObj(uint32_t id, void* target, int a, int b); // 0x00c149c0
    void     MoveToPointAtSpeed(int mode, const Vec3* pos, float a, float b);        // 0x00c1c1d0
    void     ForceOrdersUpdate();                                   // 0x00c26450
    cTribe*  GetTribe();                                            // 0x00c22f50
    bool     IsLeader();                                            // 0x00c232d0
};

// ---- tribe ---------------------------------------------------------------------------
struct cTribeVec {                                                  // {begin, end} of dwords
    uint32_t* begin;
    uint32_t* end;
};

// Embedded object with the {+0x2c, +0x5c} query pair (tribe +0x120, artifact +0x34).
struct cSlotObjBase {
    virtual void q00(); virtual void q04(); virtual void q08(); virtual void q0c();
    virtual void q10(); virtual void q14(); virtual void q18(); virtual void q1c();
    virtual void q20(); virtual void q24(); virtual void q28();
    virtual void* Slot2c(void* a);                                  // +0x2c
};
struct cSlotObj : VPad<11, cSlotObjBase> {
    virtual void* Slot5c(void* out);                                // +0x5c
};

struct cTribeV0 { virtual void t00(); };
struct cTribe : VPad<35, cTribeV0> {
    uint32_t pad04[(0x120 - 4) / 4];                                // +0x004..+0x11f
    cSlotObj mSub;                                                  // +0x120
    uint8_t  pad124[0x20c - 0x124];                                 // +0x124..+0x20b
    uint8_t  m20c;                                                  // +0x20c
    uint8_t  pad20d[0x26c - 0x20d];                                 // +0x20d..+0x26b
    int32_t  m26c;                                                  // +0x26c  cached vignette id

    virtual cTribeVec* GetMembers();                                // +0x90
    void FUN_00c94b50(float v);                                     // 0x00c94b50
};

struct cVecRange {                                                  // generic {begin, end}
    uint32_t* begin;
    uint32_t* end;
};

// Element of the nearby-object list; only the 0xb8 query is used.
struct cListItemV0 { virtual void q00(); };
struct cListItem : VPad<45, cListItemV0> {
    virtual void* Query(uint32_t id);                               // +0xb8
};

// Artifact object: rare flag at +0xab, the {0x2c, 0x5c} slot pair at +0x34.
struct cArtifactV0 {
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
};
struct cArtifact : cArtifactV0 {
    uint8_t  pad04[0x34 - 4];                                       // +0x004..+0x033
    cSlotObj mSub;                                                  // +0x034
    uint8_t  pad35[0xab - 0x35];                                    // +0x035..+0x0aa
    uint8_t  mbab;                                                  // +0x0ab

    bool IsRare();                                                  // 0x00c74ca0
};

// ---- order tree ----------------------------------------------------------------------
class cOrderNode {
public:
    uint32_t  pad00[4];                                             // +0x000..+0x00f
    int       mState;                                               // +0x010
    uint8_t   pad14[0x1a0 - 0x14];                                  // +0x014..+0x19f
    cArtifact* mpObject;                                            // +0x1a0

    uint32_t GetId1(int a);                                         // 0x00bc9be0  (ret 4)
    uint32_t GetId3(int a, void* b, int c);                         // 0x00bc9be0  (ret 0xc)
    bool     IsDone();                                              // 0x00bc9b50
    void     FUN_00bc9bf0(int a, void* b);                          // 0x00bc9bf0  (ret 8)
};

#pragma pack(push, 1)
struct cOrderPayload {
    uint32_t mValue;                                                // +0x00
    uint8_t  pad04[0x10 - 4];                                       // +0x04..+0x0f
    uint8_t  mFlags10;                                              // +0x10  pointer/value tag bits
    uint8_t  pad11;                                                 // +0x11
    uint16_t mTag12;                                                // +0x12
    uint32_t* FUN_005727b0();                                       // 0x005727b0 (thiscall)
};

struct cAgentOrder {
    uint32_t mTag;                                                  // +0x00  0x16 = order record
    uint8_t  pad04[0x39 - 4];                                       // +0x04..+0x38
    cOrderPayload mPayload;                                         // +0x39
};
#pragma pack(pop)

class cAgentOrderManager {
public:
    cOrderNode* FindNode(uint32_t id, void* fn, cSPCreatureBase* c);                 // 0x00bca620
    cOrderNode* CreateNode(uint32_t id, int count, uint32_t token, const char* name); // 0x00bcb0b0
};

cAgentOrderManager* GetOrderManager();                              // 0x00bc9b00

struct nSPBehaviorTree {
    uint32_t pad00[2];                                              // +0x000..+0x007
    BehaviorStimuli mStimuli;                                       // +0x008
    uint8_t  pad0c[0x600 - 0x0c];                                   // +0x00c..+0x5ff
    cOrderNode* mpNode;                                             // +0x600
    int32_t  m604;                                                  // +0x604

    cAgentOrder* FirstPending();                                    // 0x00bca2c0
    void Attach(void* node, cSPCreatureBase* c, void* block, void* fn);  // 0x00bcb480
    void Refresh();                                                 // 0x00bcb430
};

// ---- lookup / economy helpers (manager objects keyed by a raw word) -------------------
struct cSomeMgr {
    cVecRange* FUN_00bc7610();                                      // 0x00bc7610
    uint32_t   FUN_00bc65f0();                                      // 0x00bc65f0
    bool       FUN_00bc3df0(uint32_t id);                           // 0x00bc3df0 (ret 4)
    bool       FUN_00bc3df0();                                      // 0x00bc3df0 (no stack args)
    void       FUN_00bc5040();                                      // 0x00bc5040 (no stack args)
    uint32_t   FUN_00bc4900(uint32_t id);                           // 0x00bc4900 (ret 4)
    uint32_t   FUN_00bc4900(void* id, void* c, bool flag);          // 0x00bc4900 (ret 0xc)
    uint32_t   FUN_00bc64a0(uint32_t a, uint32_t b, void* x, void* y);  // 0x00bc64a0
    int32_t    FUN_00bc3db0(uint32_t x);                            // 0x00bc3db0
};

// 0x00b3d4e0 is one helper reached with several different argument counts here.
cSomeMgr* __stdcall FUN_00b3d4e0_a(uint32_t id);                     // (id)
cSomeMgr* __stdcall FUN_00b3d4e0_b(uint32_t id, void* b);            // (id, ptr)
cSomeMgr* FUN_00b3d4e0_d();                                         // (handle left in ecx)

struct cRelationshipMgr {
    uint32_t FUN_00d00a70(uint32_t a, uint32_t b, int one);         // 0x00d00a70
};
cRelationshipMgr* FUN_00b3d2c0();                                   // 0x00b3d2c0

struct cEconomyMgr {
    void FUN_00ac7eb0(void* a, void* b);                            // 0x00ac7eb0
};
cEconomyMgr* FUN_00b3d2b0();                                        // 0x00b3d2b0

struct cSlotFiller {
    void FillSlots();                                               // 0x00b033b0
};
cSlotFiller* __stdcall FUN_00b3d440(void* p);                       // 0x00b3d440

struct cPlanetQuery {
    void FUN_00b45410();                                            // 0x00b45410
};
cPlanetQuery* __stdcall FUN_00b3d310(void* p);                      // 0x00b3d310

void FUN_00da80f0();                                                // 0x00da80f0  worship order fn

// ---- behaviour state blocks ----------------------------------------------------------
struct AwarenessAttackBlock {                                       // attack tick / deactivate
    uint32_t mId;                                                   // +0x00
    int32_t  mCount;                                                // +0x04
};

struct GreetBlock {                                                 // AWARENESS_GREET
    uint32_t mOrder;                                                // +0x00
};

struct ChaseBlock {                                                 // pursuit of one target
    uint32_t mState;                                                // +0x00
    float    mfTimer;                                               // +0x04
    Vec3     mPos;                                                  // +0x08
    uint32_t mHandle;                                               // +0x14
};

struct VignetteBlock {
    float    mfTimeout;                                             // +0x00
    uint8_t  mb4;                                                   // +0x04
    uint8_t  pad5[3];                                               // +0x05
    int32_t  mVignette;                                             // +0x08
};

struct DomesticationBlock {
    uint32_t mId;                                                   // +0x00
    uint8_t  mb4;                                                   // +0x04
    uint8_t  pad5[3];                                               // +0x05
};

struct OrderValueBlock {
    uint32_t mValue;                                                // +0x00
    uint32_t mZero4;                                                // +0x04
    uint32_t mZero8;                                                // +0x08
};

// The vignette request word handed in as the last argument: the low half of +0x18 is a
// vignette index, its high half a flag; +0x1c is the tribe key.
struct VignetteRequest {
    uint8_t  pad00[0x18];                                           // +0x00..+0x17
    uint32_t mIndex;                                                // +0x18
    uint32_t mKey;                                                  // +0x1c
};

struct SlotList {                                                   // +0x14 begin, +0x18 end
    uint8_t  pad00[0x14];                                           // +0x00..+0x13
    uint32_t* mpBegin;                                              // +0x14
    uint32_t* mpEnd;                                                // +0x18
};

// =====================================================================================
// @ 0x00dadce0
// SP::AWARENESS_ATTACK_Tick: start the attack idle animation, then either bark at the
// current target (three or more attackers are on it) or play the face-target animation.
// =====================================================================================
bool AWARENESS_ATTACK_Tick(cSPCreatureBase* c, int, int, int, int, AwarenessAttackBlock* st,
                           int)
{
    cAnimNode* anim = c->mpBehavior->mStimuli.Play(0, 0x2000);
    if (anim == 0)
        return false;
    cSPCreatureBase* blk = (cSPCreatureBase*)WatchMemoryBlock((uint32_t)anim);
    if (blk == 0)
        return false;

    if (c->mLoco.IsNearGoal()) {
        st->mId = 0;
        st->mCount = 0;
        c->mpB54->Query((int*)&st->mId, 0, &st->mCount, 0);
        if (st->mId == 0x4cff8) {
            if (st->mCount >= 3) {
                c->mpBehavior->mStimuli.SetStimulus(0, 0x80, g_1486110, blk->GetAnimEvent());
                return false;
            }
        }
        else if (!c->FUN_00c0e0c0(0x4cff8)) {
            c->mTimer.Restart();
            c->PlayAnimationWithTargetObj(0x4cff8, &blk->mLoco, -1, -1);
        }
    }
    return true;
}

// =====================================================================================
// @ 0x00daddd0
// SP::AWARENESS_GREET_Activate: walk up to the greeted creature and pick the greeting
// order from how the two creatures are related.
// =====================================================================================
bool AWARENESS_GREET_Activate(cSPCreatureBase* c, int, int, int, int, GreetBlock* st, int)
{
    cAnimNode* anim = c->mpBehavior->mStimuli.Play(0, 0x1000);
    if (anim == 0)
        return false;
    cSPCreatureBase* blk = (cSPCreatureBase*)WatchMemoryBlock((uint32_t)anim);
    if (blk == 0)
        return false;

    c->mLoco.GetPosition();
    blk->mLoco.GetPosition();
    c->MoveToPointAtSpeed(2, c->mLoco.GetPosition(), 1.0f, g_1470f1c);

    cRelationshipMgr* rm = FUN_00b3d2c0();
    uint32_t relation = rm->FUN_00d00a70((uint32_t)c->GetRid(), (uint32_t)blk->GetRid(), 1);

    int arg;
    if (relation <= 1) {
        st->mOrder = 0x3603ac2;
        arg = 1;
    }
    else if (relation == 2) {
        st->mOrder = 0x3603ac1;
        arg = 0;
    }
    else {
        st->mOrder = 0x3603ac1;
        arg = 2;
    }
    c->Notify(&blk->mb5a8, 1, arg);
    return true;
}

// =====================================================================================
// @ 0x00daded0
// Attack/approach deactivate: once in range, either acknowledge the target (three or more
// attackers) or interrupt the animation when the target changed.
// =====================================================================================
bool FUN_00daded0(cSPCreatureBase* c, int, int, int, int, uint32_t* st, int)
{
    if (!c->mLoco.IsNearGoal())
        return true;

    uint32_t id = 0;
    int count = 0;
    c->mpB54->Query((int*)&id, 0, &count, 0);

    if (id == *st) {
        if (count < 3)
            return true;
        c->mTimer.Restart();
        c->mpBehavior->mStimuli.ClearAll(0, 0x1000);
        c->ForceOrdersUpdate();
        return false;
    }

    if (c->FUN_00c0e0c0(*st))
        return true;

    cAnimNode* anim = c->mpBehavior->mStimuli.Play(0, 0x1000);
    if (anim == 0)
        return false;
    cSPCreatureBase* blk = (cSPCreatureBase*)WatchMemoryBlock((uint32_t)anim);
    if (blk == 0)
        return false;
    c->InterruptAnimationWithTargetObj(*st, &blk->mLoco, -1, -1);
    return true;
}

// =====================================================================================
// @ 0x00dae0b0
// Chase tick: approach the target, wait out the arrival timer and then play the attack
// animation on it.  States: 0 approach, 1 wait near the target, 2 wait for the animation.
// =====================================================================================
bool FUN_00dae0b0(cSPCreatureBase* c, int, int, int, int, ChaseBlock* st, float dt)
{
    cSPCreatureBase* tgt = (cSPCreatureBase*)c->GetTargetAsCreature();
    if (tgt == 0 || tgt->IsTargetable() || tgt->mb135 == 0)
        goto fail;

    {
        const Vec3* p = tgt->mLoco.GetPosition();
        float dx = p->x - st->mPos.x;
        float dy = p->y - st->mPos.y;
        float dz = p->z - st->mPos.z;
        float d2 = dx * dx + dy * dy + dz * dz;
        if (d2 > g_1485720)
            goto fail;
    }

    switch (st->mState) {
    case 0: {
        c->FUN_00c0d0c0(6, 1);
        float height = c->mLoco.GetSpeed() * FUN_00572a10(1.0f, g_1486114)
                       + tgt->mLoco.GetSpeed();
        float dist = c->mLoco.GetDistance();
        c->MoveToPointAtSpeed(2, &st->mPos, dist, height + dist);
        st->mState = 1;
        break;
    }
    case 1:
        if (c->mLoco.IsNearGoal()) {
            st->mfTimer -= dt;
            if (st->mfTimer < 0.0f) {
                st->mHandle = c->PlayAnimationWithTargetObj(0x2c3900c, &tgt->mLoco, -1, -1);
                st->mState = 2;
            }
        }
        break;
    case 2:
        if (c->AnimationFinished(st->mHandle)) {
            st->mState = 1;
            st->mfTimer = FUN_00572a10(1.0f, g_1470f1c);
        }
        break;
    default:
        break;
    }
    return true;

fail:
    c->mpBehavior->mStimuli.SetStimulus(0, 0x20, g_147c218, 0);
    return false;
}

// =====================================================================================
// @ 0x00dae2a0
// SP::TRIBE_VIGNETTE_Activate: look up (and cache on the tribe) the vignette named by the
// request word, aim the tribe's camera object at it and start the vignette.
// =====================================================================================
uint32_t TRIBE_VIGNETTE_Activate(cSPCreatureBase* c, int, int, int, int, VignetteBlock* st,
                                 VignetteRequest* req)
{
    st->mfTimeout = g_1473c70;
    st->mb4 = 0;
    st->mVignette = -1;

    uint32_t index = req->mIndex & 0xffff;
    uint32_t key = req->mKey;
    bool flag = (req->mIndex & 0xffff0000) != 0;

    cTribe* tribe = c->GetTribe();
    if (tribe->m26c == -1) {
        cVecRange* list = FUN_00b3d4e0_b(key, 0)->FUN_00bc7610();
        if (list != 0) {
            uint32_t count = (uint32_t)((char*)list->end - (char*)list->begin) / 0x7b4;
            if (index < count) {
                uint32_t elem = (uint32_t)((char*)list->begin + index * 0x7b4);
                Vec3 tmp;
                void* a = tribe->mSub.Slot5c(&tmp);
                void* b = tribe->mSub.Slot2c(a);
                tribe->m26c = (int32_t)FUN_00b3d4e0_b(elem, b)->FUN_00bc65f0();
            }
        }
        if (tribe->m26c == -1)
            return 0;
    }

    cBundleObj* bundle = (cBundleObj*)c->mBundle.FUN_00cee330();
    if (bundle != 0) {
        cTribe* t1 = c->GetTribe();
        t1->FUN_00c94b50(bundle->mf134);
        cTribe* t2 = c->GetTribe();
        void* arg = t2 != 0 ? (void*)&t2->m20c : 0;
        FUN_00b3d2b0()->FUN_00ac7eb0(bundle, arg);
    }

    c->mLoco.NotifyEc();
    FUN_00b3d310(&c->mLoco)->FUN_00b45410();

    uint32_t id = (uint32_t)tribe->m26c;
    st->mVignette = (int32_t)id;
    return FUN_00b3d4e0_d()->FUN_00bc4900((void*)id, c, flag);
}

// =====================================================================================
// @ 0x00dae420
// SP::WORSHIP_ARTIFACT_Decide: pick a rare artifact to worship.  When the leader already
// owns the domesticate order, just resume it; otherwise take the first rare artifact from
// the nearby-object list, create the order and attach it.
// =====================================================================================
float WORSHIP_ARTIFACT_Decide(cSPCreatureBase* c, int, int, int, int, int*, int*)
{
    if (c->mpBehavior->mStimuli.Play(0, 0x40000) != 0)
        return 0.0f;

    cTribe* tribe = c->GetTribe();
    if (tribe != 0) {
        cTribeVec* v = tribe->GetMembers();
        if ((uint32_t)(v->end - v->begin) < 8)
            return 0.0f;
    }

    cSomeMgr* mgr = FUN_00b3d4e0_d();
    cOrderNode* node = GetOrderManager()->FindNode(0x5e3a55f, (void*)&FUN_00da80f0, c);
    if (node != 0) {
        if (node->IsDone())
            return 0.0f;
        if (mgr->FUN_00bc3df0(node->GetId1(0)))
            return 0.0f;
        c->mLoco.NotifyEc();
        c->mpBehavior->Attach(node, c, 0, 0);
        mgr->FUN_00bc4900(node->GetId3(0, c, 0));
        return 1.0f;
    }

    cVecRange* list = (cVecRange*)c->mLoco.FUN_00c420d0();
    for (uint32_t* it = list->begin; it != list->end; ++it) {
        uint32_t raw = *it;
        if (raw == 0)
            continue;
        cArtifact* art = (cArtifact*)((cListItem*)raw)->Query(0x2dd8c33);
        if (art == 0)
            continue;
        if (!art->IsRare())
            continue;
        if (art->mbab == 0)
            continue;

        uint8_t tmp[12];
        void* a = art->mSub.Slot5c(tmp);
        void* b = art->mSub.Slot2c(a);
        uint32_t target = mgr->FUN_00bc64a0(0xd2ebf76c, 0xa080e6cd, b, a);
        int32_t count = mgr->FUN_00bc3db0(target);

        cOrderNode* created = GetOrderManager()->CreateNode(0x5e3a55f, count, 0x18eb4b7,
                                                           "Domesticate");
        c->mLoco.NotifyEc();
        c->mpBehavior->Attach(created, c, 0, 0);
        created->FUN_00bc9bf0(0, (void*)target);

        cArtifact* old = created->mpObject;
        if (art != old) {
            art->AddRef();
            created->mpObject = art;
            if (old != 0)
                old->Release();
        }
        mgr->FUN_00bc4900(created->GetId3(0, c, 0));
        return 1.0f;
    }
    return 0.0f;
}

// =====================================================================================
// @ 0x00dae630
// Domestication activate: remember the current order id and report whether the order
// source is still running.
// =====================================================================================
bool FUN_00dae630(cSPCreatureBase* c, int, int, int, int, DomesticationBlock* st, int)
{
    st->mId = 0;
    st->mb4 = 0;
    cOrderNode* node = c->mpBehavior->mpNode;
    if (node != 0) {
        uint32_t id = node->GetId1(0);
        st->mId = id;
        if (!FUN_00b3d4e0_a(id)->FUN_00bc3df0()) {
            st->mb4 = 1;
            return true;
        }
    }
    return false;
}

// =====================================================================================
// @ 0x00dae680
// Domestication deactivate: when the order reached its last state, finish the domesticate
// order and tell every tribe member to stop worshipping.
// =====================================================================================
void FUN_00dae680(cSPCreatureBase* c, int, int, int, int, DomesticationBlock* st, int)
{
    cOrderNode* node = c->mpBehavior->mpNode;
    if (node != 0) {
        uint32_t id = st->mId;
        if (node->GetId1(0) == id) {
            if (node->mState == 1) {
                FUN_00b3d4e0_a(id)->FUN_00bc5040();
                if (st->mb4 != 0) {
                    cTribe* tribe = c->GetTribe();
                    if (tribe != 0) {
                        cTribeVec* v = tribe->GetMembers();
                        for (uint32_t* it = v->begin; it != v->end; ++it)
                            ((cSPCreatureBase*)*it)->mpBehavior->mStimuli
                                .SetStimulus(0, 0x40000, g_13ebc4c, 0);
                    }
                }
            }
            c->mpBehavior->Refresh();
        }
    }
}

// =====================================================================================
// @ 0x00dae730
// Refill the resource slots of every entry of the list at container +0x14 / +0x18.
// =====================================================================================
void FUN_00dae730(SlotList* list)
{
    for (uint32_t* it = list->mpBegin; it != list->mpEnd; ++it)
        FUN_00b3d440((void*)*it)->FillSlots();
}

// =====================================================================================
// @ 0x00dae760
// Ready-to-domesticate test: the leader stands still with a pending order for the current
// target (order value tag 0x34).
// =====================================================================================
float FUN_00dae760(cSPCreatureBase* c)
{
    if (!c->IsLeader())
        return 0.0f;
    if (!c->mLoco.IsAtGoal())
        return 0.0f;
    cAgentOrder* order = c->mpBehavior->FirstPending();
    if (order == 0 || order->mTag != 0x16)
        return 0.0f;
    uint32_t id = *order->mPayload.FUN_005727b0();
    cOrderValue* value = (cOrderValue*)c->LookupOrder(id);
    if (value != 0 && value->mTag == 0x34)
        return 1.0f;
    return 0.0f;
}

// =====================================================================================
// @ 0x00dae7d0
// Same test for the second domestication variant (order value tag 0x36).
// =====================================================================================
float FUN_00dae7d0(cSPCreatureBase* c)
{
    if (!c->IsLeader())
        return 0.0f;
    if (!c->mLoco.IsAtGoal())
        return 0.0f;
    cAgentOrder* order = c->mpBehavior->FirstPending();
    if (order == 0 || order->mTag != 0x16)
        return 0.0f;
    uint32_t id = *order->mPayload.FUN_005727b0();
    cOrderValue* value = (cOrderValue*)c->LookupOrder(id);
    if (value != 0 && value->mTag == 0x36)
        return 1.0f;
    return 0.0f;
}

// =====================================================================================
// @ 0x00dae840
// Resolve the pending order's payload word into the state block and check whether the
// creature knows that order value.
// =====================================================================================
bool FUN_00dae840(cSPCreatureBase* c, int, int, int, int, OrderValueBlock* st, int)
{
    cAgentOrder* order = c->mpBehavior->FirstPending();
    if (order == 0 || order->mTag != 0x16)
        return false;

    cOrderPayload* pl = &order->mPayload;
    uint16_t tag = pl->mTag12;
    uint32_t* src;
    if (tag == 0xa || tag == 0x10) {
        if ((pl->mFlags10 & 0x30) != 0)
            src = *(uint32_t**)pl;
        else
            src = tag != 0 ? (uint32_t*)pl : 0;
    }
    else {
        src = (uint32_t*)&g_15d1164;
    }

    uint32_t value = *src;
    st->mValue = value;
    st->mZero4 = 0;
    st->mZero8 = 0;
    return c->LookupOrder(st->mValue) != 0;
}

// =====================================================================================
// @ 0x00dae8c0
// Start-domestication test: a leader standing still is ready when no order node exists and
// the pending order names an order value of tag 0x38; otherwise a free animation slot and
// a still-running order source decide.
// =====================================================================================
float FUN_00dae8c0(cSPCreatureBase* c)
{
    cOrderNode* node = GetOrderManager()->FindNode(0x74eab7f8, 0, c);
    if (c->IsLeader() && c->mLoco.IsAtGoal()) {
        if (node != 0)
            return 0.0f;
        cAgentOrder* order = c->mpBehavior->FirstPending();
        if (order != 0 && order->mTag == 0x16) {
            uint32_t id = *order->mPayload.FUN_005727b0();
            cOrderValue* value = (cOrderValue*)c->LookupOrder(id);
            if (value != 0 && value->mTag == 0x38)
                return 1.0f;
        }
        return 0.0f;
    }

    cAnimNode* anim = c->mpBehavior->mStimuli.Play(0, 0x10000000);
    if (anim != 0 && anim->mKind != 1)
        return 0.0f;
    if (node == 0)
        return 0.0f;
    if (!node->IsDone())
        return 1.0f;
    return 0.0f;
}

} // namespace SP
