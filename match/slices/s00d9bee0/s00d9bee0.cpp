// Slice s00d9bee0 -- SPGonzago/SPSocial.obj (SP::SOCIAL_RESPOND / EAT_BUNDLE / CONJURE_FOOD
// creature-behaviour actions plus their small helpers).
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail layout of
// cSPCreatureBase is shifted, so the members used here are declared at their retail offsets with
// named fields and padN gaps, and vtable slots are reached through stub interfaces that declare
// the slot at its index (VPad<N,B>).
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <math.h>

#pragma warning(disable : 4100)

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// vtable / container helpers
// ---------------------------------------------------------------------------------------------
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

struct Vec3 {
    float x, y, z;
};

// ---------------------------------------------------------------------------------------------
// retail callees
// ---------------------------------------------------------------------------------------------
extern "C" {
void* __cdecl FUN_00b3d300();                       // SP::NounManager
void* __stdcall FUN_00b3d480(void* p);
void* __cdecl FUN_00b5b800();                       // SP::GetCurrentGameMode
int   __cdecl FUN_00d99470(void* p);
void* __cdecl FUN_00d994c0(void* p);
void* __cdecl FUN_00d99500(void* p);
void* __cdecl FUN_00d999d0(void* p);                // SP::WatchMemoryBlock
float __cdecl FUN_00d99ac0(void* a, void* b, int c);
void  __cdecl FUN_00da6270(void* c, int a);
void* __cdecl FUN_00c8ea70(void* p);
void* __cdecl FUN_00b3d2b0(void* a, u32 b);
void* __cdecl FUN_00b3d4c0(int a, void* b, void* c);
}

// ---------------------------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------------------------
extern "C" {
float g_1470f1c;    // 0x01470f1c  2.0f
float g_13ec480;    // 0x013ec480  0.2f
float g_13ec4b8;    // 0x013ec4b8  1e-8f
float g_1468908;    // 0x01468908  2.1f
float g_1486110;    // 0x01486110  5.0f
float g_1485720;    // 0x01485720  1.0f
float g_147c190;    // 0x0147c190  FLT_MAX
float g_147c194;    // 0x0147c194  1.5258789e-05
float g_1473c70;    // 0x01473c70  10.0f
float g_1471064;    // 0x01471064  0.5f
float g_1582f18;    // 0x01582f18
}

// ---------------------------------------------------------------------------------------------
// forward declarations
// ---------------------------------------------------------------------------------------------
struct cSPCreatureBase;

// ---------------------------------------------------------------------------------------------
// cSPCreatureBase virtual table (only the slots this slice calls are named)
// ---------------------------------------------------------------------------------------------
struct IRefCount {
    virtual void AddRef();                               // +0x00 (slot 0)
    virtual void Release();                              // +0x04 (slot 1)
};
struct ICreatureNoun : VPad<6, IRefCount> {              // slots 0x08..0x1c
    virtual u32 GetNounID();                             // +0x20 (slot 8)
};
struct ICreatureVerb : VPad<24, ICreatureNoun> {         // slots 0x24..0x80
    virtual void* FUN_84(void* p, int a, int b);         // +0x84 (slot 33)
};
struct ICreatureCombat : VPad<11, ICreatureVerb> {       // slots 0x88..0xb0
    virtual void* FUN_b4(int slot);                      // +0xb4 (slot 45)
};
struct ICreatureMisc : VPad<7, ICreatureCombat> {        // slots 0xb8..0xd0
    virtual bool FUN_d4();                               // +0xd4 (slot 53)
};

// ---------------------------------------------------------------------------------------------
// cLocomotiveObject -- the subobject at creature+0xc0
// ---------------------------------------------------------------------------------------------
struct ILocoPos : VPad<11, IEmpty> {
    virtual const Vec3* GetPosition();                   // +0x2c (slot 11)
};
struct ILocoRadius : VPad<17, ILocoPos> {
    virtual float GetRadius();                           // +0x74 (slot 29)
};
struct cLocomotiveObject : VPad<29, ILocoRadius> {
    virtual void FUN_ec();                               // +0xec (slot 59)

    bool  IsNearGoal();                                  // 0x00c42e20
    void* FUN_00c41ec0();                                // 0x00c41ec0  -> object with flags at +0x70
};

struct cLocoGoal {                                       // object returned by FUN_00c41ec0
    u8  pad000[0x70];
    u32 mFlags_70;                                       // +0x70
};

struct cEatTarget : IRefCount {                          // EAT_BUNDLE target object
    u8                pad04[0x34 - 0x04];
    cLocomotiveObject mLoco_34;                          // +0x34
    u8                pad38[0x128 - 0x38];
    u32               mField_128;                        // +0x128
};

// ---------------------------------------------------------------------------------------------
// behaviour tree + the per-tree memory block
// ---------------------------------------------------------------------------------------------
struct behavior_stimuli {
    void* Play(int a, int b);                            // 0x00bc96a0
    void  FUN_00bc97f0(int a, int b, float c, void* d);  // 0x00bc97f0
    void  ClearAll(int a, int b);                        // 0x00bc98f0
    void* GetAny();                                      // 0x00d997e0
};

struct cMemoryBlockSlot {                                // stride 0xc
    bool  mbUsed;                                        // +0x00
    u8    pad01[3];
    void* mpObject;                                      // +0x04
    u32   mExtra;                                        // +0x08
};

struct cMemoryBlock {
    u8              pad000[0x18];
    u32             mCount;                              // +0x18
    u8              pad01c[0x04];
    cMemoryBlockSlot mSlots_20[0x21];                    // +0x20 .. 0x1ac
    cSPCreatureBase* mpOwner;                            // +0x1ac
};

struct cBehaviorTree {
    void*            mpVtbl;                             // +0x00
    u8               pad04[0x04];
    behavior_stimuli mStimuli_08;                        // +0x08
    u8               pad09[0x600 - 0x09];
    cMemoryBlock*    mpBlock_600;                        // +0x600

    void PopFront();                                     // 0x00bcaf40
};

// ---------------------------------------------------------------------------------------------
// cSPCreatureBase (retail member offsets)
// ---------------------------------------------------------------------------------------------
struct cCreatureCombatPart {                             // subobject at creature+0x34
    u8    pad00[0x01];
    void* FUN_00cee330();                                // 0x00cee330
};

struct cSPCreatureBase : ICreatureMisc {
    u8                  pad04[0x34 - 0x04];
    cCreatureCombatPart mCombatPart_34;                  // +0x34
    u8                  pad35[0xc0 - 0x35];
    cLocomotiveObject   mLoco_c0;                        // +0xc0
    u8                  padc4[0xb4c - 0xc4];
    cBehaviorTree*      mpTree_b4c;                      // +0xb4c
    u32                 padb50[0x02];
    u32                 mFlags_b58;                      // +0xb58
    u8                  padb5c[0xfc8 - 0xb5c];
    u32                 mStealthTime_fc8;                // +0xfc8

    void*                  ApplyCombatTarget();          // 0x00c0ee90
    cSPCreatureBase*       GetTargetAsCreature();        // 0x00c0ee70
    void*                  GetSocialGoal();              // 0x00c0e6a0
    void                   MoveToPointAtSpeed(int mode, const Vec3* p, float a, float b);       // 0x00c1c1d0
    void                   MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* dir,
                                                        float a, float b);                        // 0x00c1c5c0
    void*                  PlayAnimation(u32 id, int a, int b);                                  // 0x00c12190
    bool                   AnimationFinished(void* h);                                            // 0x00c12400
    void*                  PlayAnimationWithTarget(u32 id, void* target, int a, int b);           // 0x00c14940
    void*                  PlayAnimationWithTargetPos(u32 id, const Vec3* p, int a);              // 0x00c14910
    void*                  FindSlotByCombatant(int slot, u32* out);                                // 0x00c0fa10
    void                   ApplyWave(float f);                                                    // 0x00c15dc0
};

// ---------------------------------------------------------------------------------------------
// other objects
// ---------------------------------------------------------------------------------------------
struct cGameNounManager {
    cSPCreatureBase* GetAvatar();                        // 0x00b1fdb0
};
struct cNounManager {
    void* GetItemID();                                   // 0x00b1f9c0
};
struct cCargoManager {
    void FUN_00aca360();                                 // 0x00aca360
    void FUN_00acd2d0();                                 // 0x00acd2d0
};
struct cSpeciesDB {
    int FindField10(u32 key);                            // 0x004d4750
};
struct cTuningObj {
    int GetAt(int i);                                    // 0x004d3cd0
};
struct cAgentOrderManager {
    void FUN_00ac79e0();                                 // 0x00ac79e0  (result of FUN_00b3d2b0)
    void FUN_00ba48b0();                                 // 0x00ba48b0  (result of FUN_00b3d4c0)
};

struct IListItemVtbl : VPad<45, IEmpty> {
    virtual void* FUN_b4(int idx);                       // +0xb4 (slot 45)
};
struct cListItem : IListItemVtbl {
    u8         pad04[0xb20 - 0x04];
    cSpeciesDB* mpDB_b20;                                // +0xb20
};

struct IAbilityVtbl : VPad<45, IEmpty> {
    virtual void* FUN_b4(int idx);                       // +0xb4 (slot 45)
};
struct cAbility {                                        // TuningObj-ish, only fields used
    u8    pad000[0x08];
    int   mField_08;                                     // +0x08
    u8    pad0c[0x04];
    u32   mField_10;                                     // +0x10
    u8    pad14[0x104 - 0x14];
    float mFloat_104;                                    // +0x104

    int   GetAt(int i);                                  // 0x004d3cd0
};

struct cCombatTarget {                                   // result of cCreatureCombatPart::FUN_00cee330
    u8  pad000[0x12c];
    int mType_12c;                                       // +0x12c
    u8  pad130[0x04];
    u8  mSlot_134[0x01];                                 // +0x134
};

struct cCombatSlot {                                     // the packed "slot" value at cAbility+0x34
    cCombatTarget* mpTarget;                             // +0x00
};

// ---------------------------------------------------------------------------------------------
// action state records
// ---------------------------------------------------------------------------------------------
struct SOCIAL_RESPOND_memory_block {
    int              mState;                             // +0x00
    cSPCreatureBase* mpTarget;                           // +0x04
    void*            mAnimHandle;                        // +0x08
    int              mSocialIdx;                         // +0x0c
    int              mAbilityType;                       // +0x10
    int              mExpectedAbilityType;               // +0x14
    float            mCountdown;                         // +0x18

    float FUN_00d9c100(cSPCreatureBase* c, cAbility* ability);   // 0x00d9c100
    int   CalculateGroupContribution(cSPCreatureBase* c);        // 0x00d9c020
    static u32 MoveToTarget(cSPCreatureBase* c, u32 idx, int* param3, int* param4);  // 0x00d9bee0
};

struct EAT_BUNDLE_state {
    int              mState;                             // +0x00
    void*            mAnimHandle;                        // +0x04
    cEatTarget*      mpTarget;                           // +0x08
    u8               pad0c[0x0c];
    int              mCount_18;                          // +0x18
    int              mField_1c;                          // +0x1c
    int              mField_20;                          // +0x20

    void* GetAny();                                      // 0x00d997e0
};

struct CONJURE_FOOD_out {
    int   mState;                                        // +0x00
    void* mAnimHandle;                                   // +0x04
    int   mField_08;                                     // +0x08
};

// ---------------------------------------------------------------------------------------------
// 00d9bee0  SP::SOCIAL_RESPOND_memory_block::MoveToTarget
// ---------------------------------------------------------------------------------------------
// @ 0x00d9bee0  SP::SOCIAL_RESPOND_memory_block::MoveToTarget
u32 SOCIAL_RESPOND_memory_block::MoveToTarget(cSPCreatureBase* c, u32 idx, int* param3, int* param4) {
    int entries = *param4;                                     // *param_4 : array of creature ptrs
    int recs = *param3;                                        // *param_3 : array of 0x20-byte records
    u32 off = idx << 5;
    cSPCreatureBase* cur = *(cSPCreatureBase**)(entries + *(int*)(recs + off) * 4);

    while (cur != 0) {
        float fr = *(float*)(recs + off + 0x1c);
        const Vec3* p = cur->mLoco_c0.GetPosition();
        float dz = p->z - *(float*)(recs + off + 0x18);
        float dx = p->x - *(float*)(recs + off + 0x10);
        float dy = p->y - *(float*)(recs + off + 0x14);
        if (!((dz * dz + dx * dx) + dy * dy <= fr + g_13ec480))
            break;
        idx = idx + 1;
        off = off + 0x20;
        if (idx > 2)
            return 0xffffffff;
        recs = *param3;
        entries = *param4;
        cur = *(cSPCreatureBase**)(entries + *(int*)(recs + off) * 4);
    }

    off = idx << 5;
    int k = *(int*)(*param3 + off);
    int tbl = *param4;
    cSPCreatureBase* old = *(cSPCreatureBase**)(tbl + k * 4);
    if (c != old) {
        if (c != 0)
            c->AddRef();
        *(cSPCreatureBase**)(tbl + k * 4) = c;
        if (old != 0)
            old->Release();
    }
    c->MoveToPointAtSpeed(2, (const Vec3*)(*param3 + off + 0x10), 1.0f, g_1470f1c);
    return *(u32*)(*param3 + off);
}

// ---------------------------------------------------------------------------------------------
// 00d9c020  SP::SOCIAL_RESPOND_memory_block::CalculateGroupContribution
// ---------------------------------------------------------------------------------------------
// @ 0x00d9c020  SOCIAL_RESPOND_memory_block::CalculateGroupContribution
int SOCIAL_RESPOND_memory_block::CalculateGroupContribution(cSPCreatureBase* c) {
    cLocomotiveObject* thisLoco = &c->mLoco_c0;
    cLocomotiveObject* tgtLoco = &mpTarget->mLoco_c0;
    (void)thisLoco->GetPosition();
    (void)tgtLoco->GetPosition();
    float tr = tgtLoco->GetRadius();
    float sr = thisLoco->GetRadius();
    float s = sr + tr + g_1470f1c;
    if ((c->mFlags_b58 >> 8) & 1) {
        cSPCreatureBase* av = ((cGameNounManager*)FUN_00b3d300())->GetAvatar();
        float ar = av->mLoco_c0.GetRadius();
        s = ar + ar + s;
    }
    sr = thisLoco->GetRadius();
    float r = sr + s;
    const Vec3* p = tgtLoco->GetPosition();
    c->MoveToPointAtSpeed(2, p, s, r);
    cLocoGoal* g = (cLocoGoal*)thisLoco->FUN_00c41ec0();
    g->mFlags_70 |= 2;
    return (int)&g->mFlags_70;
}

// ---------------------------------------------------------------------------------------------
// 00d9c100  helper: group "food sharing" bonus
// ---------------------------------------------------------------------------------------------
// @ 0x00d9c100  SOCIAL_RESPOND_memory_block::FUN_00d9c100
float SOCIAL_RESPOND_memory_block::FUN_00d9c100(cSPCreatureBase* c, cAbility* ability) {
    u32 fl = c->mFlags_b58;
    if ((fl >> 9) & 1) {
        float r = *(float*)((u8*)ability + 0x3c);
        void* v = ((cNounManager*)FUN_00b3d300())->GetItemID();
        cListItem** begin = *(cListItem***)v;
        cListItem** end = *(cListItem***)((u8*)v + 4);
        for (cListItem** it = begin; it != end; ++it) {
            cListItem* e = *it;
            int f = e->mpDB_b20->FindField10(ability->mField_10);
            if (f != -1 && e->FUN_b4(f))
                r += *(float*)((u8*)ability + 0x3c) * g_1582f18;
        }
        return r;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// 00d9c1a0  SP::SOCIAL_RESPOND_Tick
// ---------------------------------------------------------------------------------------------
// @ 0x00d9c1a0  SP::SOCIAL_RESPOND_Tick
bool __cdecl SOCIAL_RESPOND_Tick(cSPCreatureBase* c, int, int, int, int,
                                 SOCIAL_RESPOND_memory_block* b, int, float dt) {
    if (c->GetTargetAsCreature() != b->mpTarget || FUN_00d99470(b->mpTarget) == 0)
        return false;
    if ((c->mFlags_b58 >> 8) & 1) {
        cSPCreatureBase* av = ((cGameNounManager*)FUN_00b3d300())->GetAvatar();
        if (av->GetTargetAsCreature() != b->mpTarget)
            return false;
    }
    switch (b->mState) {
    case 0: {                                       // kToTarget
        float t = b->mCountdown - dt;
        b->mCountdown = t;
        bool arrived = false;
        if (t < 0.0f) {
            b->mCountdown = g_1471064;
            b->CalculateGroupContribution(c);
            arrived = true;
        }
        cSPCreatureBase* tg = b->mpTarget;
        void* tl = tg ? (void*)&tg->mLoco_c0 : 0;
        float d = FUN_00d99ac0(&c->mLoco_c0, tl, 1);
        if (d < g_1468908 || (arrived && c->mLoco_c0.IsNearGoal())) {
            c->mLoco_c0.FUN_ec();
            if ((c->mFlags_b58 >> 9) & 1) {
                if (FUN_00b5b800() == (void*)0x1654c10)
                    b->mAnimHandle = c->PlayAnimation(0x7a3d058, 1, -1);
                else
                    b->mAnimHandle = c->PlayAnimation(0xb4212a07, 1, -1);
                b->mState = 1;
                return true;
            }
            b->mState = 2;
            return true;
        }
        break;
    }
    case 1:                                         // kInitiating
        if (c->AnimationFinished(b->mAnimHandle)) {
            b->mAnimHandle = 0;
            cBehaviorTree* tt = b->mpTarget->mpTree_b4c;
            tt->mStimuli_08.FUN_00bc97f0(0x10000, 0, g_1486110, c);
            void* p = tt->mStimuli_08.Play(0x10000, 0);
            *(int*)((u8*)p + 0xc) = 1;
            if (b->mpTarget->FUN_d4() && b->mpTarget->GetSocialGoal() == 0)
                return false;
            b->mState = 2;
            return true;
        }
        break;
    case 2: {                                       // kWatching
        void* p = c->mpTree_b4c->mStimuli_08.Play(0x10000000, 0);
        if (p == 0 || *(int*)((u8*)p + 0xc) != 0)
            break;
        u32 social = *(u32*)((u8*)p + 0x10);
        b->mSocialIdx = (int)social;
        if (social == 0xffffffff) {
            c->mpTree_b4c->mStimuli_08.ClearAll(0x10000000, 0);
            return true;
        }
        cAbility* ab = (cAbility*)c->FUN_b4((int)social);
        b->mAnimHandle = c->PlayAnimation(ab->GetAt(0), 1, -1);
        b->mAbilityType = ab->mField_08;
        b->mExpectedAbilityType = (int)ab->mField_10;
        b->mState = 3;
        if ((c->mFlags_b58 >> 9) & 1) {
            c->ApplyWave(ab->mFloat_104);
            cBehaviorTree* tt = b->mpTarget->mpTree_b4c;
            tt->mStimuli_08.FUN_00bc97f0(0x10000000, 0, g_147c190, 0);
            void* np = tt->mStimuli_08.Play(0x10000000, 0);
            *(int*)((u8*)np + 0xc) = 1;
            *(int*)((u8*)np + 0x10) = ab->mField_08;
            *(int*)((u8*)np + 0x14) = (int)ab->mField_10;
            *(float*)((u8*)np + 0x18) = b->FUN_00d9c100(c, ab);
            *(void**)((u8*)np + 0x1c) = b->mAnimHandle;
            void* v = ((cNounManager*)FUN_00b3d300())->GetItemID();
            cListItem** it = *(cListItem***)v;
            cListItem** end = *(cListItem***)((u8*)v + 4);
            for (; it != end; ++it) {
                cListItem* e = *it;
                int f = e->mpDB_b20->FindField10(ab->mField_10);
                if (f != -1) {
                    tt->mStimuli_08.FUN_00bc97f0(0x10000000, 0, g_1470f1c, 0);
                    void* np2 = tt->mStimuli_08.Play(0x10000000, 0);
                    *(int*)((u8*)np2 + 0xc) = 0;
                    *(int*)((u8*)np2 + 0x10) = f;
                }
            }
        }
        c->mpTree_b4c->mStimuli_08.ClearAll(0x10000000, 0);
        return true;
    }
    case 3:                                         // kResponding
        if (c->AnimationFinished(b->mAnimHandle)) {
            if ((c->mFlags_b58 >> 9) & 1) {
                cBehaviorTree* tt = b->mpTarget->mpTree_b4c;
                tt->mStimuli_08.FUN_00bc97f0(0x10000000, 0, g_147c190, 0);
                void* np = tt->mStimuli_08.Play(0x10000000, 0);
                *(int*)((u8*)np + 0xc) = 2;
                *(int*)((u8*)np + 0x10) = b->mAbilityType;
                *(int*)((u8*)np + 0x14) = b->mExpectedAbilityType;
            }
            b->mSocialIdx = 0;
            b->mState = 2;
            b->mAnimHandle = 0;
        }
        break;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// 00d9c6f0  SP::CONJURE_FOOD_Activate
// ---------------------------------------------------------------------------------------------
// @ 0x00d9c6f0  FUN_00d9c6f0
bool __cdecl FUN_00d9c6f0(cSPCreatureBase* c, int, int, int, int, CONJURE_FOOD_out* out) {
    void* h = c->mpTree_b4c->mStimuli_08.Play(0x8000000, 0);
    if (h == 0) {
        FUN_00da6270(c, 0x14);
        return false;
    }
    void* r = FUN_00d99500(FUN_00d999d0(h));
    if (r == 0) {
        FUN_00da6270(c, 0x14);
        return false;
    }
    c->FUN_84((u8*)r + 0x5a8, 1, 2);
    ((cCargoManager*)FUN_00b3d480(r))->FUN_00acd2d0();

    cMemoryBlock* mb = c->mpTree_b4c->mpBlock_600;
    mb->mpOwner = c;
    for (u32 i = 0; i < mb->mCount; ++i) {
        cMemoryBlockSlot* s = &mb->mSlots_20[i];
        if (s->mbUsed && s->mpObject != c) {
            cBehaviorTree* t = ((cSPCreatureBase*)s->mpObject)->mpTree_b4c;
            t->PopFront();
            t->mStimuli_08.ClearAll(0x1d3fbffa, 0x8124080);
        }
    }

    cCombatTarget* ct = (cCombatTarget*)c->mCombatPart_34.FUN_00cee330();
    if (ct == 0) {
        out->mAnimHandle = c->PlayAnimation(0x2c39200, 1, c->mStealthTime_fc8);
        out->mState = 1;
        out->mField_08 = 0;
        return true;
    }
    if (ct->mType_12c != 6) {
        u32 mask = c->mStealthTime_fc8;
        void* slot = c->FindSlotByCombatant((int)((u8*)ct + 0x34), 0);
        if (slot != 0)
            mask = *(u32*)slot;
        out->mAnimHandle = c->PlayAnimation(0x4ffb325, 1, (int)mask);
        out->mState = 0;
        out->mField_08 = 0;
        return true;
    }
    // close enough: align, then face and approach
    const Vec3* tp = c->GetTargetAsCreature()->mLoco_c0.GetPosition();
    const Vec3* sp = c->mLoco_c0.GetPosition();
    float dx = tp->x - sp->x;
    float dy = tp->y - sp->y;
    float dz = tp->z - sp->z;
    float inv = 1.0f / sqrtf((dz * dz + dy * dy) + dx * dx + g_13ec4b8);
    Vec3 dir;
    dir.x = inv * dx;
    dir.y = inv * dy;
    dir.z = inv * dz;
    float r2 = c->GetTargetAsCreature()->mLoco_c0.GetRadius();
    float r1 = c->mLoco_c0.GetRadius();
    float rad = r1 + r2 + g_1485720;
    c->MoveToPointAndFacingAtSpeed(2, tp, &dir, rad, rad);
    out->mState = 2;
    out->mField_08 = 0;
    return true;
}

// ---------------------------------------------------------------------------------------------
// 00d9c960  detach / stop the current group member order
// ---------------------------------------------------------------------------------------------
// @ 0x00d9c960  FUN_00d9c960
void __cdecl FUN_00d9c960(cSPCreatureBase* c) {
    void* r = FUN_00d99500(c->ApplyCombatTarget());
    if (r != 0)
        ((cCargoManager*)FUN_00b3d480(r))->FUN_00aca360();

    cMemoryBlock* mb = c->mpTree_b4c->mpBlock_600;
    if (mb != 0 && mb->mpOwner == c)
        mb->mpOwner = 0;

    c->FUN_84(0, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// 00d9c9c0  SP::EAT_BUNDLE_Tick
// ---------------------------------------------------------------------------------------------
// @ 0x00d9c9c0  EAT_BUNDLE_Tick
bool __cdecl EAT_BUNDLE_Tick(cSPCreatureBase* c, int, int, int, int, EAT_BUNDLE_state* s, bool* out) {
    switch (s->mState) {
    case 0:
        if (c->mLoco_c0.IsNearGoal()) {
            void* t = s->mpTarget ? (void*)((u8*)s->mpTarget + 0x34) : 0;
            s->mAnimHandle = c->PlayAnimationWithTarget(0x7204469e, t, -1, -1);
            s->mState = 1;
        }
        break;
    case 1:
        if (c->AnimationFinished(s->mAnimHandle)) {
            void* t = s->mpTarget ? (void*)((u8*)s->mpTarget + 0x34) : 0;
            s->mAnimHandle = c->PlayAnimationWithTarget(0x720446a7, t, -1, -1);
            s->mState = 2;
            return true;
        }
        break;
    case 2:
        if (c->AnimationFinished(s->mAnimHandle)) {
            Vec3 pos = *s->mpTarget->mLoco_34.GetPosition();
            ((cAgentOrderManager*)FUN_00b3d2b0(s->mpTarget, s->mpTarget->mField_128))->FUN_00ac79e0();
            if (s->mpTarget != 0) {
                cEatTarget* old = s->mpTarget;
                s->mpTarget = 0;
                old->Release();
            }
            ((cAgentOrderManager*)FUN_00b3d4c0(3, (u8*)c + 0xb28, c))->FUN_00ba48b0();
            s->mAnimHandle = c->PlayAnimationWithTargetPos(0xd20446b0, &pos, -1);
            s->mState = 3;
            return true;
        }
        break;
    case 3:
        if (c->AnimationFinished(s->mAnimHandle)) {
            s->mState = 4;
            return true;
        }
        break;
    case 4:
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// 00d9ccc0  creature-space "scale step" helper
// ---------------------------------------------------------------------------------------------
// Dynamically sized vector of float pairs (element = 8 bytes); push_back at 0x00e315f0.
struct cFloatVec {
    u8    pad00[0x10];
    void* mpData_10;                                     // +0x10  element base
    int   mCount_14;                                     // +0x14  element count
    int   mCap_18;                                       // +0x18  capacity

    void push_back(float a, float b);                    // 0x00e315f0
};

struct cScaleHelper {
    u8    pad000[0x0c];
    void* mpField_0c;                                    // +0x0c  -> object whose +0x550 is read
    u8    pad10[0x34 - 0x10];
    float mFloat_34;                                     // +0x34
    float mFloat_38;                                     // +0x38
    u8    pad3c[0xe8 - 0x3c];
    cFloatVec* mpVec_e8;                                 // +0xe8  spd vector of float pairs
    int   mField_ec;                                     // +0xec

    void FUN_00d9ccc0(float a, float b);                 // 0x00d9ccc0
};

// @ 0x00d9ccc0  FUN_00d9ccc0
void cScaleHelper::FUN_00d9ccc0(float a, float b) {
    mFloat_34 = a + mFloat_34;
    void* p = *(void**)((u8*)mpField_0c + 0x550);
    if (p == 0)
        return;
    u8* r = (u8*)FUN_00c8ea70(p);
    float f = *(float*)(r + 0x94);
    if (mField_ec == 1)
        f = *(float*)(r + 0x90);
    if (f > g_147c194) {
        if (mpVec_e8 != 0) {
            a = a / f;
            mpVec_e8->push_back(a, a / b);
        }
        float ten = g_1473c70;
        float t = (mFloat_34 / f) * ten;
        float* p = (t > ten) ? &ten : &t;
        mFloat_38 = *p;
    }
}