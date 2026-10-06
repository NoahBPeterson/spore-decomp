// 0x00d67d30: per-tick update of a creature's "fight" behavior (creature game / space-creature mode).
// Probably the retail SP::FIGHT_Tick: it sits between FIGHT_Activate (0xd679e0) and TRIBE_FIGHT_Tick
// (0xd697a0), uses GetFightSlots and the FIGHT_memory_block group, and has the 8-arg behavior-tick
// signature. (The PDB pairing labels it GROWL_TIMER_Tick, "caller-scored", but its memory block is far
// larger than GROWL_TIMER_memory_block.) The callee at 0xd65c40 is paired with "FIGHT_Tick" in the PDB
// table; here it is called with (mem, self, target) as a sub-step, so it is named by address.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (same module as TRIBE_FIGHT_Tick).
#include "types.h"
#include <math.h>

namespace SP {

struct Vec3 { float x, y, z; };

static inline Vec3 operator-(const Vec3& a, const Vec3& b) { Vec3 r = { a.x - b.x, a.y - b.y, a.z - b.z }; return r; }
static inline Vec3 operator+(const Vec3& a, const Vec3& b) { Vec3 r = { a.x + b.x, a.y + b.y, a.z + b.z }; return r; }
static inline Vec3 operator*(const Vec3& a, float s) { Vec3 r = { s * a.x, s * a.y, s * a.z }; return r; }
static inline Vec3 operator-(const Vec3& a) { Vec3 r = { -a.x, -a.y, -a.z }; return r; }
static inline float Dot(const Vec3& a, const Vec3& b) { return a.y * b.y + a.z * b.z + b.x * a.x; }
static inline float DistSq(const Vec3& a, const Vec3& b)
{
    Vec3 d = a - b;
    return d.z * d.z + d.y * d.y + d.x * d.x;
}

// EASTL min/max (return references)
static inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
static inline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }

Vec3  normalized_safe(const Vec3& v);                  // 0x449c20 (sret)
Vec3  Vector3_Normalize(const Vec3& v);                // 0x436ce0 (sret)
float Length(const Vec3& v);                           // 0x4885d0
bool  operator!=(const Vec3& a, const Vec3& b);        // 0x41dd30
extern Vec3 kZeroVec;                                  // 0x169ecbc

// Movement / steering state of a locomotive object (FUN_00c41ec0 result)
struct LocoState {
    char     pad00[0x5c];
    int      mHasPath;                                 // +0x5c
    char     pad60[0x70 - 0x60];
    uint32_t mMoveFlags;                               // +0x70
    const Vec3* GetGoal();                             // 0xc423c0
};

struct cLocomotiveObject {
    const Vec3& GetVelocity();                         // 0xd20610
};

// Spatial/locomotive sub-object of a creature (at +0xc0), own vtable
struct Loco {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual const Vec3* GetPosition();                 // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual bool IsMoving();                           // +0x58
    virtual const Vec3* GetFacing(Vec3* out);          // +0x5c
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual float Slot70();                            // +0x70
    virtual float GetRadius();                         // +0x74
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
    virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
    virtual bool SlotF8();                             // +0xf8
    LocoState* GetState();                             // 0xc41ec0
    bool IsNearGoal();                                 // 0xc42e20
};

// The owner object of a target (target->GetOwner()); a spatial object
typedef Loco Spatial;

struct Handle { char pad[0x24]; int m24; };

// The object returned by cSPCreatureBase::GetTargetObj (0xc0ee60)
struct TargetObj {
    virtual void s00(); virtual void s01();
    virtual Spatial* GetOwner();                       // +0x08
    virtual Handle*  GetHandle();                      // +0x0c
};

// Ability / attack tuning object (vtable slot 0xb4 of the creature)
struct Ability {
    char  pad00[0x7c];
    int   m7c;                                         // +0x7c
    char  pad80[0x9c - 0x80];
    float mCooldown;                                   // +0x9c
    float mA0;                                         // +0xa0
    char  padA4[0xa8 - 0xa4];
    float mRange;                                      // +0xa8
    char  padAC[0xf4 - 0xac];
    float mF4;                                         // +0xf4
    int   mF8;                                         // +0xf8
    float GetBound(bool b);                            // TuningObj::GetBound 0x4d3d70
};

struct cSPCreatureBase;

struct GroupMember { bool mActive; cSPCreatureBase* mpCreature; int m8; };

// Fight group shared by several creatures (behavior +0x600)
struct FightGroup {
    char        pad00[0x14];
    int         mLeaderIdx;                            // +0x14
    uint32_t    mCount;                                // +0x18
    char        pad1c[4];
    GroupMember mMembers[(0x1a4 - 0x20) / 12];         // +0x20
    int         m1a4;                                  // +0x1a4
    char        pad1a8[4];
    Vec3        mLeaderPos;                            // +0x1ac
    bool        FUN_00a75010();
};

struct IdleRes;
struct BehStim {
    IdleRes* PlayIdleAnimation(uint32_t a, uint32_t b);           // 0xbc96a0
    void SetStimulus(int a, uint32_t b, float c, void* who);      // 0xbc97f0
};
struct Behav {
    char      pad00[8];
    BehStim   mStim;                                   // +0x08
    char      pad09[0x600 - 9];
    FightGroup* mpGroup;                               // +0x600
};

struct Herd {
    char  pad[0x164];
    cSPCreatureBase* mpLeader;                         // +0x164
    struct ListNode { ListNode* next; ListNode* prev; } mList;     // +0x168
    bool HasMembers() { return mList.next != &mList; }
};

struct cSPTimer { uint64_t GetElapsedTime(); };       // 0xbc3190

struct Sim { char pad[0x4c8]; bool mUseOtherTargeting; };     // FUN_00c04750 result

struct TargetQuery { virtual void s0(); virtual void s1(); virtual void s2(); virtual void* Get(const void* id); };
struct TargetSrc { TargetQuery* FUN_00c7d930(); };

struct SimSingleton {
    static SimSingleton* Get();                        // 0xc03260
    void* FindTarget(void* who, float a, float b);     // 0xf30cc0
};

struct KeyPair { int a, b; };
struct HandleSet { KeyPair insert(const int& key); }; // 0xa18440

struct Tuning { char pad[0x58c]; float m58c; };

struct AttackEntry { int m0; float mReadiness; int m8, mc; };

struct cSPCreatureBase {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual uint32_t GetTypeId();                      // +0x20
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32();
    virtual void SetTarget(void* o, int a, int b);     // +0x84
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44();
    virtual Ability* GetAbility(int idx);              // +0xb4
    virtual void s46(); virtual void s47();
    virtual bool CanReach(void* o, float a, float b);  // +0xc0

    char      pad004[0xc0 - 4];
    Loco      mLoco;                                   // +0xc0
    char      pad0c4[0x330 - 0xc4];
    uint8_t   mFlags330;                               // +0x330
    char      pad331[0x5a8 - 0x331];
    char      mTargetable[0x5b4 - 0x5a8];              // +0x5a8
    HandleSet mSeenHandles;                            // +0x5b4
    char      pad5b5[0x670 - 0x5b5];
    TargetSrc mTargetSrc;                              // +0x670
    char      pad671[0xb20 - 0x671];
    Tuning*   mpTuning;                                // +0xb20
    char      padb24[0xb4c - 0xb24];
    Behav*    mpBehav;                                 // +0xb4c
    char      padb50[0xb58 - 0xb50];
    uint32_t  mStateFlags;                             // +0xb58
    uint8_t   mbFlagB5C;                               // +0xb5c
    char      padb5d[0xc28 - 0xb5d];
    AttackEntry* mpAttacks;                            // +0xc28
    char      padc2c[0xe8c - 0xc2c];
    int       mActiveTarget;                           // +0xe8c
    char      pade90[0xfc0 - 0xe90];
    cSPTimer  mTimer;                                  // +0xfc0

    TargetObj* GetTargetObj();                         // 0xc0ee60
    int   GetTargetAsCreature();                       // 0xc0ee70
    cSPCreatureBase* GetTargetCreature();              // 0xc0ee90
    Sim*  FUN_00c04750();
    Herd* FUN_00c04590();
    bool  FUN_00c0c0e0();
    bool  FUN_00c0b780();
    bool  AnimationFinished(int id);                   // 0xc12400
    bool  AnimationFinished2(int id);                  // 0xc123f0
    int   InterruptAnimation(int id, int a, int b);    // 0xc12310
    int   PlayAnimation(int id, int a, int b);         // 0xc12190
    bool  FUN_00c0e0c0(int id);
    void  FUN_00c14750(int a);
    void  Attack(int idx, int* outAnim);               // 0xc1e460
    void  MoveToPointAtSpeed(int mode, const Vec3& p, float s0, float s1);                        // 0xc1c1d0
    void  MoveToPointAndFacingAtSpeed(int mode, const Vec3& p, const Vec3& f, float s0, float s1); // 0xc1c5c0
    void  TryJumpToTarget(int a, const Vec3& p, const Vec3& vel, float r, int b);                // 0xc190e0
};

// Map<int attackIdx, float cooldown> (eastl::map, rbtree anchor at +4)
struct CooldownNode { CooldownNode* mpNodeRight; CooldownNode* mpNodeLeft; CooldownNode* mpNodeParent; int mColor; int first; float second; };
CooldownNode* RBTreeIncrement(const CooldownNode* p);  // eastl::RBTreeIncrement 0x921580
struct CooldownIter {
    CooldownNode* mpNode;
    CooldownIter(CooldownNode* p) : mpNode(p) {}
    CooldownIter(const CooldownIter& x) : mpNode(x.mpNode) {}
    CooldownIter& operator++() { mpNode = RBTreeIncrement(mpNode); return *this; }
    bool operator!=(const CooldownIter& x) const { return mpNode != x.mpNode; }
};
struct CooldownMap {
    int          mCompare;                             // +0x00
    CooldownNode mAnchor;                              // +0x04 (only right/left/parent/color used)
    CooldownIter begin() { return CooldownIter(mAnchor.mpNodeLeft); }
    CooldownIter end()   { return CooldownIter(&mAnchor); }
    CooldownIter erase(CooldownIter it);               // 0x8dae70
    float& operator[](const int& key);                 // 0xc8c550
};

// The fight behavior's per-creature memory block (retail layout; the 2008 PDB's
// FIGHT_memory_block is an older, smaller version)
struct FightMem {
    float    m00;
    float    mEvalTimer;                               // +0x04
    float    mMoveTimer;                               // +0x08
    float    mNoActivityTimer;                         // +0x0c
    float    m10;                                      // +0x10
    float    m14;                                      // +0x14
    int      mState;                                   // +0x18
    float    mDistance;                                // +0x1c
    int      m20;
    short    mStandardAttackCounter;                   // +0x24
    char     pad26[0x2c - 0x26];
    int      mFirstHitAnim;                            // +0x2c
    int      mAttackAnim;                              // +0x30
    int      mFrustrationAnim;                         // +0x34
    int      m38;
    int      m3c;                                      // +0x3c
    float    m40;                                      // +0x40
    bool     m44;                                      // +0x44
    char     pad45[0x4e - 0x45];
    bool     m4e;                                      // +0x4e
    bool     mbAttackOnSight;                          // +0x4f
    float    m50;                                      // +0x50
    float    m54;                                      // +0x54
    float    mFrustrationTimer;                        // +0x58
    float    mAbilityTimer;                            // +0x5c
    int      mAbilityIdx;                              // +0x60
    CooldownMap mCooldowns;                            // +0x64
    bool FUN_00d678d0(bool b);
};

struct PropertyList;
struct cCreatureModeStrategy { char pad[0xb4]; PropertyList* mpProps; };
extern cCreatureModeStrategy* g_CreatureModeStrategy;  // 0x169e294
float GetPropertyT_float(PropertyList* p, uint32_t hash, float def);  // SP::GetPropertyT<float> 0x4e1c70

struct PlanetModelT { Vec3 ProjectToSurface(const Vec3* p); };       // 0xb81630
PlanetModelT* PlanetModel();                           // 0xb3d350

struct RandomLinearCongruential { double RandomDoubleUniform(); };
extern RandomLinearCongruential sMathRandom;          // 0x1601760

extern char g_CreatureGameMode;                        // 0x1654c10
extern int  DAT_01582ee8;
extern char DAT_013f94d4[];
void* GetCurrentGameMode();                            // 0xb5b800

const uint32_t kTypeCreatureAnimal = 0x18eb4b7;
const uint32_t kTypeA = 0x18ebadc;
const uint32_t kTypeB = 0x18c6de8;

struct CastObj { char pad[0xb1c]; int mb1c; };

// callees (cdecl)
cSPCreatureBase* FUN_00d99470(int creature);
int        FUN_00d99500(cSPCreatureBase* c);
float      FUN_00d99ac0(Loco* me, Spatial* other, int a);
bool       FUN_00d659e0(FightMem* m, cSPCreatureBase* c, int flags, TargetObj* t, cSPCreatureBase* tc);
bool       FUN_00d65c40(FightMem* m, cSPCreatureBase* c, TargetObj* t);
float      FUN_00f264b0(cSPCreatureBase* c);
int        FUN_00d998f0(const void* p);
int        FUN_00d66710(FightMem* m, cSPCreatureBase* c, TargetObj* t, int* prevIdx, float* maxR, float* minR);
float      FUN_00d65530(float base, bool b);
cSPCreatureBase* FUN_00d66600(cSPCreatureBase* c, int tgt);
cSPCreatureBase* FUN_00d655d0(cSPCreatureBase* c, int tgt, float a, float b);
cSPCreatureBase* FUN_00d66400(cSPCreatureBase* c, void* animal, float a, float b);
void*      FUN_00ac80d0(const void* o, uint32_t type);
void*      FUN_00ae6740(TargetQuery* q);
void*      FUN_00d99a10(IdleRes* idle);
float      FUN_00d38a30(int which, cSPCreatureBase* c);
Vec3       FUN_00d65580(cSPCreatureBase* c, const Vec3& p);
bool       GetFightSlots(cSPCreatureBase* c, FightMem* m, int arg);       // 0xd66370
bool       FUN_00d65fe0(FightMem* m, cSPCreatureBase* c, TargetObj* t, float minR, float maxR);
cLocomotiveObject* FUN_00b33e40(Spatial* s);
cLocomotiveObject* FUN_00bfc6c0(TargetObj* t);

static __forceinline bool IsCreatureGame() { return GetCurrentGameMode() == &g_CreatureGameMode; }

// @ 0x00d67d30
bool FIGHT_Tick(cSPCreatureBase* self, int, int, uint32_t flags, uint32_t flags2, FightMem* mem, int, float dt)
{
    TargetObj* target = self->GetTargetObj();
    cSPCreatureBase* targetCreature = FUN_00d99470(self->GetTargetAsCreature());
    int targetCitizen = FUN_00d99500(targetCreature);

    Spatial* targetOwner = 0;
    float dist = 0.0f;
    if (target) {
        targetOwner = target->GetOwner();
        if (targetOwner)
            dist = FUN_00d99ac0(self ? &self->mLoco : 0, targetOwner, 1);
    }

    int* attackAnim = &mem->mAttackAnim;
    float* pDist = &mem->mDistance;
    *pDist = dist;
    if ((*attackAnim == 0 || self->AnimationFinished(*attackAnim))
        && FUN_00d659e0(mem, self, flags2, target, targetCreature))
        return false;

    if (IsCreatureGame()) {
        if (*pDist > FUN_00f264b0(self)) {
            mem->mFrustrationTimer = dt + mem->mFrustrationTimer;
            if (mem->mFrustrationTimer > 5.0f && mem->mFrustrationAnim == 0)
                mem->mFrustrationAnim = self->InterruptAnimation(0x3238f953, -1, 0);
        } else {
            mem->mFrustrationTimer = 0.0f;
        }

        if (target)
            mem->mFirstHitAnim = targetCitizen ? DAT_01582ee8 : 0x20;

        if (mem->mbAttackOnSight) {
            self->mbFlagB5C = 1;
            self->SetTarget(target, 1, 0);
            bool targetValid = FUN_00d998f0(target) != 0;
            int prevIdx = -1;
            float maxR = 0.0f, minR = 0.0f;
            int idx = FUN_00d66710(mem, self, target, &prevIdx, &maxR, &minR);
            if (targetValid && maxR >= *pDist && *pDist >= minR) {
                Loco* loco = &self->mLoco;
                const Vec3* myPos = loco->GetPosition();
                const Vec3* tgtPos = targetOwner->GetPosition();
                Vec3 toTarget = normalized_safe(*tgtPos - *myPos);
                Vec3 facingBuf;
                const Vec3* facing = loco->GetFacing(&facingBuf);
                if (Dot(*facing, toTarget) > 0.85f && idx != -1)
                    self->Attack(idx, attackAnim);
                return true;
            }
            void* newTarget;
            if (!self->FUN_00c04750()->mUseOtherTargeting) {
                newTarget = SimSingleton::Get()->FindTarget(self->mTargetable, 0.0f, 0.0f);
            } else {
                TargetQuery* q = self->mTargetSrc.FUN_00c7d930();
                newTarget = q ? q->Get(DAT_013f94d4) : 0;
            }
            self->SetTarget(newTarget, 1, 0);
            return true;
        }
    }

    FightGroup* group = self->mpBehav->mpGroup;
    mem->mEvalTimer = mem->mEvalTimer - dt;
    mem->mMoveTimer = mem->mMoveTimer - dt;
    mem->mNoActivityTimer = mem->mNoActivityTimer - dt;

    if (self->FUN_00c0c0e0() && mem->m3c == 0 && self->mTimer.GetElapsedTime() < 3000)
        mem->m40 = mem->m40 + dt;

    {
        int at = self->mActiveTarget;
        Ability* ab;
        if (at == -1 || (ab = self->GetAbility(at)) == 0 || !(ab->mF4 > 0.0f) || ab->mF8 == -1)
            self->mbFlagB5C = 1;
    }

    if (FUN_00d65c40(mem, self, target))
        return true;

    uint32_t mustSee = flags & 8;
    if (!mustSee && targetCreature && targetCreature->GetTypeId() == kTypeCreatureAnimal) {
        const Vec3* tp = targetCreature->mLoco.GetPosition();
        const Vec3* mp = self->mLoco.GetPosition();
        if (DistSq(*mp, *tp) < 400.0f)
            targetCreature->mpBehav->mStim.SetStimulus(0, 0x100, 30.0f, self);
    }

    if (mem->mEvalTimer < 0.0f) {
        mem->mEvalTimer = FUN_00d65530(1.0f, self->FUN_00c0c0e0());
        void* newTarget = 0;
        if (!IsCreatureGame()) {
            cSPCreatureBase* found;
            if (targetCitizen) {
                if (flags2 & 4)
                    found = FUN_00d66600(self, targetCitizen);
                else {
                    if (self->mLoco.IsMoving() || (flags & 0x1000) || !mustSee)
                        goto noRetarget;
                    found = FUN_00d655d0(self, targetCitizen, mem->m50, mem->m54);
                }
            } else {
                found = FUN_00d66400(self, FUN_00ac80d0(targetCreature, kTypeCreatureAnimal), mem->m50, mem->m54);
            }
            if (!found)
                goto noRetarget;
            newTarget = found->mTargetable;
        } else {
            if (((self->mStateFlags >> 9) & 1) || ((self->mStateFlags >> 8) & 1) || !(self->mFlags330 & 0x21))
                goto noRetarget;
            int h = target->GetHandle()->m24;
            self->mSeenHandles.insert(h);
            if (self->FUN_00c04750()->mUseOtherTargeting)
                newTarget = FUN_00ae6740(self->mTargetSrc.FUN_00c7d930());
            else
                newTarget = SimSingleton::Get()->FindTarget(self->mTargetable, 0.0f, 0.0f);
            if (!newTarget || newTarget == target)
                goto noRetarget;
        }
        if (newTarget) {
            self->SetTarget(newTarget, 1, 0);
            mem->FUN_00d678d0(false);
            return true;
        }
    }
noRetarget:

    if (group) {
        IdleRes* idle = self->mpBehav->mStim.PlayIdleAnimation(0x400, 0);
        if (idle) {
            TargetObj* o = (TargetObj*)FUN_00d998f0(FUN_00d99a10(idle));
            if (o && o == group->mMembers[group->mLeaderIdx].mpCreature->GetTargetObj())
                group->mLeaderPos = *o->GetOwner()->GetPosition();
        }
    }

    switch (mem->mState) {
    case 0: {
        if (mem->mMoveTimer < 0.0f) {
            bool targeted = false;
            IdleRes* idle = self->mpBehav->mStim.PlayIdleAnimation(0x400, 0);
            if (idle) {
                int o = FUN_00d998f0(FUN_00d99a10(idle));
                if (o) {
                    self->SetTarget((void*)o, 0, 0);
                    targeted = true;
                }
            }
            if (!mem->FUN_00d678d0(targeted))
                mem->mMoveTimer = FUN_00d65530(1.0f, self->FUN_00c0c0e0());
        }
        return true;
    }
    case 1:
        break;
    default:
        return true;
    }

    // state 1: engaged
    if (!group || group->FUN_00a75010())
        return false;

    bool specialTarget = false;
    if (!targetCreature && targetOwner) {
        void* h = target->GetHandle();
        if (h) {
            if (FUN_00ac80d0(h, kTypeA))
                specialTarget = true;
            else {
                CastObj* c = (CastObj*)FUN_00ac80d0(h, kTypeB);
                if (c) {
                    if (c->mb1c == 2)
                        specialTarget = true;
                    else if (c->mb1c == 1)
                        specialTarget = true;
                }
            }
        }
    }

    int prevIdx = -1;
    float maxR = 0.0f, minR = 0.0f;
    int idx = FUN_00d66710(mem, self, target, &prevIdx, &maxR, &minR);

    if (IsCreatureGame()) {
        if (mem->mAbilityIdx != idx) {
            mem->mAbilityIdx = idx;
            mem->mAbilityTimer = 0.0f;
            Ability* ab = self->GetAbility(idx);
            if (ab)
                mem->mAbilityTimer = (1.0f - self->mpAttacks[idx].mReadiness) * ab->mCooldown + 5.0f;
        }
        if (mem->mAbilityIdx != -1) {
            mem->mAbilityTimer = mem->mAbilityTimer - dt;
            if (mem->mAbilityTimer < 0.0f) {
                mem->mAbilityIdx = -1;
                mem->mAbilityTimer = 0.0f;
                mem->mCooldowns[idx] = 30.0f;
            }
        }
        for (CooldownIter it = mem->mCooldowns.begin(); it != mem->mCooldowns.end(); ) {
            it.mpNode->second = it.mpNode->second - dt;
            if (0.0f < it.mpNode->second)
                ++it;
            else
                it = mem->mCooldowns.erase(it);
        }
    }

    Spatial* owner = targetOwner;
    Vec3 targetPos = PlanetModel()->ProjectToSurface(owner->GetPosition());
    Loco* loco = &self->mLoco;
    float radii = owner->GetRadius();
    radii = loco->GetRadius() + radii;

    if (self->mActiveTarget != -1) {
        // an ability is being used: stay in its range
        if (loco->GetState()->mHasPath != 0)
            return true;
        Ability* ab = self->GetAbility(self->mActiveTarget);
        float scale = FUN_00d38a30(0, self);
        bool b = (self->mStateFlags >> 9) & 1;
        float bound = ab->GetBound(b) * scale;
        if (IsCreatureGame() && bound > *pDist) {
            // too close: back off to the edge of the range
            Vec3 away = Vector3_Normalize(*loco->GetPosition() - targetPos);
            float over = bound - *pDist;
            Vec3 off = { over * away.x, away.y * over, away.z * over };
            Vec3 dest = *loco->GetPosition() + off;
            self->MoveToPointAndFacingAtSpeed(2, dest, normalized_safe(targetPos - *loco->GetPosition()), 1.0f, 2.0f);
            return true;
        }
        float ownerR = owner->GetRadius();
        float myR = loco->GetRadius();
        float sumR = myR + ownerR;
        float speed = (ab ? ab->mRange * scale : 0.0f) + sumR;
        float speedMax = speed + myR;
        Vec3 goal = FUN_00d65580(self, targetPos);
        float dsq = DistSq(goal, targetPos);
        if (dsq > 1.5258789e-05f) {
            float d = sqrtf(dsq);
            speed = speed + d;
            speedMax = d + speedMax;
        }
        self->MoveToPointAndFacingAtSpeed(2, goal, normalized_safe(targetPos - *loco->GetPosition()), speed, speedMax);
        cLocomotiveObject* ol = FUN_00b33e40(owner);
        if (!ol)
            return true;
        if (Length(ol->GetVelocity()) > 0.01f)
            loco->GetState()->mMoveFlags |= 1;
        return true;
    }

    bool mutualTarget;
    if (targetCreature && targetCreature->GetTargetCreature() == self && targetCreature->mActiveTarget != -1)
        mutualTarget = true;
    else
        mutualTarget = false;

    bool engaged = self->mActiveTarget != -1;
    if (!engaged && targetCreature && targetCreature->mLoco.IsMoving()) {
        for (uint32_t i = 0; i < group->mCount; ++i) {
            GroupMember& m = group->mMembers[i];
            if (m.mActive && m.mpCreature && m.mpCreature->mActiveTarget != -1) {
                engaged = true;
                break;
            }
        }
    }
    if (mutualTarget || engaged)
        mem->m10 = mem->m14;

    bool canAct;
    if (self->FUN_00c04590()->mpLeader == self
        && self->FUN_00c04590()->HasMembers()
        && !self->mpBehav->mStim.PlayIdleAnimation(0x400, 0))
        canAct = false;
    else
        canAct = true;

    if (mem->mMoveTimer < 0.0f && !mutualTarget && !engaged && idx != -1
        && self->mpAttacks[idx].mReadiness >= 1.0f && canAct) {
        // ready to attack
        bool slotted = GetFightSlots(self, mem, group->m1a4);
        if (FUN_00d65fe0(mem, self, target, minR, maxR))
            return false;
        bool targetValid = FUN_00d998f0(target) != 0;
        Vec3 toTarget = normalized_safe(targetPos - *loco->GetPosition());
        Vec3 up = normalized_safe(*loco->GetPosition());
        float d = up.x * toTarget.x + toTarget.y * up.y + toTarget.z * up.z;
        Vec3 flat = { toTarget.x - d * up.x, toTarget.y - d * up.y, toTarget.z - d * up.z };
        if (flat != kZeroVec)
            toTarget = normalized_safe(flat);

        Vec3 facingBuf;
        if (targetValid && maxR >= *pDist && *pDist >= minR
            && Dot(*loco->GetFacing(&facingBuf), toTarget) > 0.85f) {
            if (IsCreatureGame()) {
                mem->mAbilityIdx = -1;
                mem->mAbilityTimer = 0.0f;
            }
            self->Attack(idx, attackAnim);
            mem->m4e = false;
            mem->m44 = false;
            if (idx == prevIdx)
                mem->mStandardAttackCounter = 0;
            else
                ++mem->mStandardAttackCounter;
            mem->m10 = mem->m14;
            bool b = self->FUN_00c0c0e0();
            mem->mMoveTimer = FUN_00d65530(self->GetAbility(idx)->mA0, b);
            mem->mNoActivityTimer = 0.0f;
            return true;
        }

        float scale = FUN_00d38a30(0, self);
        Ability* ab = self->GetAbility(idx);
        float maxRange = (ab->mF4 + ab->mRange) * scale;
        bool b = (self->mStateFlags >> 9) & 1;
        float bound = ab->GetBound(b) * scale;
        bool moved;
        if (IsCreatureGame() && bound > *pDist) {
            // too close: back off to a quarter of the way into the range
            Vec3 away = Vector3_Normalize(*loco->GetPosition() - targetPos);
            float over = ((maxRange - bound) * 0.25f + bound) - *pDist;
            Vec3 off = { over * away.x, over * away.y, over * away.z };
            Vec3 dest = *loco->GetPosition() + off;
            self->MoveToPointAndFacingAtSpeed(2, dest, normalized_safe(targetPos - *loco->GetPosition()), 1.0f, 2.0f);
            moved = loco->SlotF8();
        } else {
            float jumpChance = GetPropertyT_float(g_CreatureModeStrategy->mpProps, 0x4f7cf2c, 0.25f);
            if (!self->FUN_00c0c0e0() && self->mpTuning->m58c > 1.5258789e-05f
                && (((self->mStateFlags >> 8) & 1) || self->FUN_00c0b780())
                && jumpChance > sMathRandom.RandomDoubleUniform()
                && targetCreature && self->CanReach(targetCreature, mem->m54, 0.0f)) {
                Loco* tl = &targetCreature->mLoco;
                self->TryJumpToTarget(0, targetPos, ((cLocomotiveObject*)tl)->GetVelocity(), tl->GetRadius(), 0);
                return true;
            }

            float approach = maxRange;
            if (self->GetAbility(idx)->m7c == 1)
                approach = Min(approach, Max(*pDist, minR));
            approach = approach + radii;
            float approachMax = loco->GetRadius() + approach;

            LocoState* st = loco->GetState();
            bool needMove = true;
            if (st->mHasPath != 0 && !(*pDist < 40.0f)) {
                const Vec3* g = loco->GetState()->GetGoal();
                float gd = DistSq(*g, targetPos);
                float r = owner->Slot70();
                if (!(gd > owner->Slot70() * r))
                    needMove = false;
            }
            if (needMove) {
                if (slotted) {
                    self->MoveToPointAtSpeed(2, targetPos, approach, approachMax);
                    loco->GetState()->mMoveFlags |= 4;
                } else {
                    Vec3 goal = FUN_00d65580(self, targetPos);
                    float dsq = DistSq(targetPos, goal);
                    if (dsq > 1.5258789e-05f) {
                        float d2 = sqrtf(dsq);
                        approach = approach + d2;
                        approachMax = d2 + approachMax;
                    }
                    self->MoveToPointAndFacingAtSpeed(2, goal, normalized_safe(goal - *loco->GetPosition()), approach, approachMax);
                }
            }
            cLocomotiveObject* tl = FUN_00bfc6c0(self->GetTargetObj());
            if (tl && Length(tl->GetVelocity()) > 0.01f)
                loco->GetState()->mMoveFlags |= 1;
            moved = loco->SlotF8();
        }
        if (!moved)
            self->FUN_00c14750(0);
        return true;
    }

    // not ready to attack: circle / approach
    bool slotted = GetFightSlots(self, mem, group->m1a4);
    float closeDist = GetPropertyT_float(g_CreatureModeStrategy->mpProps, 0x8b034ce0, 1.0f);
    if (!specialTarget
        && !(targetCreature && targetCreature->GetTargetCreature() == self)
        && (mem->mNoActivityTimer < 0.0f || *pDist > closeDist)) {
        float extra = GetPropertyT_float(g_CreatureModeStrategy->mpProps, 0xf290181f, 1.0f);
        float timerBase = GetPropertyT_float(g_CreatureModeStrategy->mpProps, 0x2140064f, 1.0f);
        float keep = extra + radii + minR;
        mem->mNoActivityTimer = FUN_00d65530(timerBase, self->FUN_00c0c0e0());
        if (slotted) {
            self->MoveToPointAtSpeed(2, targetPos, keep, keep + 0.2f);
            loco->GetState()->mMoveFlags |= 4;
        } else {
            Vec3 dir = normalized_safe(targetPos - *loco->GetPosition());
            Vec3 off = -dir * keep;
            const Vec3* op = owner->GetPosition();
            Vec3 dest = { off.x + op->x, op->y + off.y, op->z + off.z };
            dest = FUN_00d65580(self, dest);
            self->MoveToPointAtSpeed(2, dest, loco->GetRadius() * 0.5f, loco->GetRadius());
        }
        if (!loco->SlotF8())
            self->FUN_00c14750(0);
    }
    if (!self->AnimationFinished2(0))
        return true;
    int anim = 0x26ede51;
    if (!loco->IsNearGoal())
        anim = 0x39e477b;
    if (self->FUN_00c0e0c0(anim))
        return true;
    self->PlayAnimation(anim, 1, -1);
    return true;
}

} // namespace SP
