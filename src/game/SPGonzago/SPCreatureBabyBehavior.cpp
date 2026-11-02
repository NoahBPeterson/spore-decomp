// src/game/SPGonzago/SPCreatureBabyBehavior.cpp -- migrated from slice(s) s00d63fd0, s00d63560, s00d61c20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureBabyBehavior.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLocomotiveObject.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include <math.h>
#include "nSPBehaviorTree/behavior_memory_block.h"
#include <float.h>

// ---- items of slice s00d61c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            s32;
typedef float          f32;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vec3 { f32 x, y, z; };
extern const f32 g_f13ec4b8;   // 0x013ec4b8  1.0e-8f  (normalise epsilon)
extern const f32 g_f13f08e4;   // 0x013f08e4  1.25f
extern const f32 g_f1470f1c;   // 0x01470f1c  2.0f
extern const f32 g_f147bbdc;   // 0x0147bbdc  15.0f
extern const f32 g_f1485544;   // 0x01485544  0.75f
extern const f32 g_f1486110;   // 0x01486110  5.0f
extern const f32 g_f1488874;   // 0x01488874  0.1f
struct cBehaviorTreeData;
struct HomeInfo;
struct cPlanetModel;
class cSPCreatureBase;
struct Combatant;
struct RandomLCG {
    u32 RandomUint32Uniform(u32 range);       // 0x00a68fb0 (ret 4)
};
cSPCreatureBase*  __cdecl FUN_00d999d0(void* block);      // 0x00d999d0 WatchMemoryBlock
cSPCreatureBase*  __cdecl FUN_00d99500(void* owner);      // 0x00d99500 (ret 4 -> cdecl, 1 arg)
s32               __cdecl FUN_00d99470(cSPCreatureBase* c);// 0x00d99470
cPlanetModel*     __cdecl PlanetModel();                  // 0x00b3d350 (0 args)
Vec3*             __cdecl normalized_safe(Vec3* out, const Vec3* in);  // 0x00449c20
struct AnimPlayRes {
    char mPad00[0xc];
    u32  mAnimId;                             // +0x0c
};
struct Stimuli {
    AnimPlayRes* Play(u32 lo, u32 hi);        // 0x00bc96a0 (ret 8)
    void         ClearAll(u32 lo, u32 hi);    // 0x00bc98f0 (ret 8)
};
struct cBehaviorTreeData {
    char    mPad00[8];
    Stimuli mStimuli;                         // +0x08
    char    mPad09[0x1d8 - 9];
    u32     mKey1d8;                          // +0x1d8
    char    mPad1dc[0x600 - 0x1dc];
    void*   mPtr600;                          // +0x600
};
struct Loco {                                 // embedded at cSPCreatureBase+0xc0
    PV8 PV2 PV
    virtual Vec3* GetPosition();              // vtable +0x2c
    PV8 PV2 PV
    virtual Vec3* GetDirection(Vec3* out);    // vtable +0x5c
    PV4 PV
    virtual f32   GetFootprintRadius();       // vtable +0x74

    bool IsNearGoal();                        // 0x00c42e20
};
struct Combatant {                            // embedded at cSPCreatureBase+0x5a8
    f32 GetHealthPct();                       // 0x00bfc490
};
struct HomeInfo {
    char mPad000[0x104];
    s32  m104;                                // +0x104
    char mPad108[0x164 - 0x108];
    void* mOwner;                             // +0x164  (the "owner" creature)
};
class cSPCreatureBase {
public:
    PV8 PV8 PV8 PV8 PV                        // vtable 0x00 .. 0x80
    virtual void v84(void*, int, int);        // vtable +0x84

    char  mPad04[0xc0 - 4];                   // +0x04
    Loco  mLoco;                              // +0xc0
    char  mPadc4[0xb4c - 0xc4];               // +0xc4
    cBehaviorTreeData* mpBTree;               // +0xb4c
    char  mPadb50[0xb58 - 0xb50];             // +0xb50
    u32   mFlagsB58;                          // +0xb58
    char  mPadb5c[0xf90 - 0xb5c];             // +0xb5c
    u8    mFlagF90;                           // +0xf90

    void*   FUN_00c0b370(s32 id);             // 0x00c0b370 (ret 4)
    HomeInfo* FUN_00c04590();                 // 0x00c04590
    cSPCreatureBase* GetTargetAsCreature();   // 0x00c0ee70
    u32     PlayAnimation(u32 id, int a, int b);   // 0x00c12190 (ret 0x0c)
    bool    AnimationFinished(u32 id);        // 0x00c12400 (ret 4)
    void    MoveToPointAtSpeed(int a, const Vec3* p, f32 s0, f32 s1);  // 0x00c1c1d0 (ret 0x10)
};
struct cPlanetModel {
    void DirectionToSurfacePosition(Vec3* out, const Vec3* pos);              // 0x00b815a0 (ret 8)
    void MakeRandomWorldPosition(Vec3* out, const Vec3* center, f32 minR, f32 maxR);  // 0x00b81780 (ret 0x10)
};
// ---- items of slice s00d61c20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const f32 g_f13ec4b8;   // 0x013ec4b8  1.0e-8f  (normalise epsilon)
extern const f32 g_f13f08e4;   // 0x013f08e4  1.25f
extern const f32 g_f1470f1c;   // 0x01470f1c  2.0f
extern const f32 g_f147bbdc;   // 0x0147bbdc  15.0f
extern const f32 g_f1485544;   // 0x01485544  0.75f
extern const f32 g_f1486110;   // 0x01486110  5.0f
extern const f32 g_f1488874;   // 0x01488874  0.1f

// ---- items of slice s00d63560 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV_s00d6_3560 virtual void CAT_(_pv, __COUNTER__)();
#define PV2_s00d6_3560 PV_s00d6_3560 PV_s00d6_3560
#define PV4_s00d6_3560 PV2_s00d6_3560 PV2_s00d6_3560
#define PV8_s00d6_3560 PV4_s00d6_3560 PV4_s00d6_3560
#define PV16 PV8_s00d6_3560 PV8_s00d6_3560
namespace SP {
struct Vec3_s00d6_3560 { float x, y, z; };
}
namespace SP {
struct Goal {                       // returned by Loco::GetState (FUN_00c41ec0)
    uint32_t pad00[0x5c / 4];
    int      mHasPath;              // +0x5c
    uint32_t pad60[(0x70 - 0x60) / 4];
    uint32_t mMoveFlags;            // +0x70
};
}
namespace SP {
class Loco_s00d6_3560 {
public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual Vec3_s00d6_3560* GetPosition();                       // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual Vec3_s00d6_3560* GetFacing(Vec3_s00d6_3560* out);                // +0x5c
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
virtual void s60();
virtual void s61();
    virtual bool PrepareMove();                        // +0xf8

    const Vec3_s00d6_3560& GetVelocity();                         // 0x00d20610
    Goal* GetState();                                  // 0x00c41ec0
    Vec3_s00d6_3560* GetGoalPosition();                           // 0x00c421f0
};
}
namespace SP {
class CreatureHead {                                   // bytes 0x00..0xbf of the creature
public:
    virtual void h00();
    PV4_s00d6_3560 PV8_s00d6_3560 PV16 PV4_s00d6_3560                       // slots 1..32
    virtual void FinishAction(int, int, int); // +0x84 (slot 33)
    uint8_t pad04[0xad6];
    uint8_t mFieldB5e;                     // +0xb5e
    uint8_t padB5f[0x61];
};
}
namespace SP {
struct Herd;
}
namespace SP {
class cSPCreatureBase_s00d6_3560 : public CreatureHead, public Loco_s00d6_3560 {
public:
    Herd* GetHerd();                                   // 0x00c04590
    cSPCreatureBase_s00d6_3560* FUN_00c0ee90();                   // 0x00c0ee90 (thiscall, no args)
    void FUN_00c14750(int a);                          // 0x00c14750 (thiscall, ret 4)
    void MoveToPointAtSpeed(int mode, const Vec3_s00d6_3560* p, float s0, float s1);                        // 0x00c1c1d0
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3_s00d6_3560* p, const Vec3_s00d6_3560* facing, float s0, float s1);   // 0x00c1c5c0
    int PlayAnimationWithTarget(int anim, void* target, int flags); // 0x00c14910 (thiscall, ret 0xc)

    uint32_t padc4[(0x330 - 0xc4) / 4];
    uint32_t mFlags330;
};
}
namespace SP {
struct ListNode {
    ListNode* mpNext;
    ListNode* mpPrev;
    cSPCreatureBase_s00d6_3560* mValue;
};
}
namespace SP {
struct ListIter {
    ListNode* mpNode;
    ListIter() {}
    ListIter(ListNode* n) : mpNode(n) {}
    ListIter(const ListIter& x) : mpNode(x.mpNode) {}
};
}
namespace SP {
struct Herd {
    uint32_t pad00[0x164 / 4];
    cSPCreatureBase_s00d6_3560* mpLeader;                         // +0x164
    ListNode mMembers;                                 // +0x168 (sentinel; mpNext = first)
};
}
namespace SP {
struct FollowState {
    char mActive;                                      // +0
    char pad01[3];
    Vec3_s00d6_3560 mAnchor;                                      // +4
};
}
namespace SP {
int   FUN_00d99500(cSPCreatureBase_s00d6_3560* c);                // cdecl
}
namespace SP {
float FUN_00d99ac0(Loco_s00d6_3560* a, Loco_s00d6_3560* b, int flag);        // cdecl, x87 return
}
namespace SP {
void  FindInList(ListIter* out, ListIter first, ListIter last, cSPCreatureBase_s00d6_3560* const* value);   // 0x00d61ce0 (cdecl)
}
namespace SP {
Vec3_s00d6_3560* normalized_safe_s00d6_3560(Vec3_s00d6_3560* out, const Vec3_s00d6_3560* in);      // 0x00449c20 (cdecl)
}
namespace SP {
class cPlanetModel_s00d6_3560 {
public:
    Vec3_s00d6_3560* DirectionToSurfacePosition(Vec3_s00d6_3560* out, const Vec3_s00d6_3560* dir);   // 0x00b815a0
    void MakeRandomWorldPosition();                                // 0x00b81780
    void FindClosestWater();                                       // 0x00b8bb70
    void PrepareSurface();                                         // 0x00b81630
};
}
namespace SP {
cPlanetModel_s00d6_3560* PlanetModel_s00d6_3560();                                   // 0x00b3d350
}
namespace SP {
cPlanetModel_s00d6_3560* PlanetModel_s00d6_3560(Vec3_s00d6_3560* out, const Vec3_s00d6_3560* pos);          // 0x00b3d350 (two-pointer form)
}
namespace SP {
cPlanetModel_s00d6_3560* PlanetModel_s00d6_3560(Vec3_s00d6_3560* out, float radius, const Vec3_s00d6_3560* pos); // 0x00b3d350 (radius form)
}
namespace SP {
extern float DAT_01582e04;                             // follow distance (10.0)
}
namespace SP {
struct NavOutput {
    Vec3_s00d6_3560     mPosition;      // +0x00
    uint32_t mField0c;       // +0x0c
};
}
namespace SP {
struct RefCounted {
    virtual void r00();
    virtual void Release();  // +0x04
};
}
namespace SP {
struct CreatureActionArgs {
    int         mState;      // +0x00
    int         mPad04;      // +0x04
    int         mPad08;      // +0x08
    RefCounted* mpObject;    // +0x0c
};
}
// ---- items of slice s00d63560 end

// ---- items of slice s00d63fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VT(o, off) ((*(void***)(o))[(off) / 4])
#define FIELD(T, o, off) (*(T*)((char*)(o) + (off)))
struct Vec3_s00d6_3fd0 { float x, y, z; };
struct Stimuli_s00d6_3fd0;
struct IdleAnim { uint32_t pad[3]; int id; };   // +0xc is the animation slot
struct Stimuli_s00d6_3fd0 {
    IdleAnim* PlayIdleAnimation(int a, int b);           // 0x00bc96a0
    void ClearAll(int a, int b);                           // 0x00bc98f0
    void SetStimulus(int a, int b, float strength, int c); // 0x00bc97f0
};
struct Brain {
    char pad[0x1d8];
    uint32_t hash;                                 // +0x1d8
    Stimuli_s00d6_3fd0* Stim() { return (Stimuli_s00d6_3fd0*)((char*)this + 8); }
};
struct Loco_s00d6_3fd0 {   // cLocomotiveObject sub-object at cSPCreatureBase+0xc0
    bool IsNearGoal();                                         // 0x00c42e20
    Vec3_s00d6_3fd0* GetPosition() { return ((Vec3_s00d6_3fd0*(__thiscall*)(Loco_s00d6_3fd0*))VT(this, 0x2c))(this); }
    float Slot74() { return ((float(__thiscall*)(Loco_s00d6_3fd0*))VT(this, 0x74))(this); }
    Vec3_s00d6_3fd0* GetDirection(Vec3_s00d6_3fd0* buf) { return ((Vec3_s00d6_3fd0*(__thiscall*)(Loco_s00d6_3fd0*, Vec3_s00d6_3fd0*))VT(this, 0x5c))(this, buf); }
    void Slot40(float f) { ((void(__thiscall*)(Loco_s00d6_3fd0*, float))VT(this, 0x40))(this, f); }
    bool Slot58() { return ((bool(__thiscall*)(Loco_s00d6_3fd0*))VT(this, 0x58))(this); }
    void SlotEC() { ((void(__thiscall*)(Loco_s00d6_3fd0*))VT(this, 0xec))(this); }
    void SlotDC(void* p) { ((void(__thiscall*)(Loco_s00d6_3fd0*, void*))VT(this, 0xdc))(this, p); }
};
struct cSPCreatureBase_s00d6_3fd0;
struct GroupData {                  // result of FUN_00c04590
    char pad0[0x104];
    int f104;
    char pad1[0x5c];
    cSPCreatureBase_s00d6_3fd0* f164;
};
struct cSPCreatureBase_s00d6_3fd0 {
    Loco_s00d6_3fd0* L() { return (Loco_s00d6_3fd0*)((char*)this + 0xc0); }
    Brain* B() { return FIELD(Brain*, this, 0xb4c); }
    // non-virtual members
    bool AnimationFinished(int h);                              // 0x00c12400
    bool AnimationFinishedId(uint32_t id);                      // 0x00c123f0
    int PlayAnimation(uint32_t id, int a, int b);               // 0x00c12190
    int PlayAnimationWithTarget(uint32_t id, void* p, int x);   // 0x00c14910
    int StartAnimationAt(uint32_t id, void* p, int x);          // 0x00c14990
    uint32_t GetCurrentAnimationGUID();                         // 0x00c0e040
    bool FUN_00c0e070(int h);
    cSPCreatureBase_s00d6_3fd0* GetTargetAsCreature();                     // 0x00c0ee70
    void MoveToPointAtSpeed(int mode, Vec3_s00d6_3fd0* p, float speed, float arg);                    // 0x00c1c1d0
    void MoveToPointAndFacingAtSpeed(int mode, Vec3_s00d6_3fd0* p, Vec3_s00d6_3fd0* f, float speed, float arg);  // 0x00c1c5c0
    void FUN_00c14750(int a);
    GroupData* FUN_00c04590();
    bool FUN_00c0b770();
    void FUN_00c03190(int a, int b, float f, int c, int d, int e, int g);
    void FUN_00c0ba10();
    void FUN_00c0b370(int a);
    // virtuals
    float V80(int a) { return ((float(__thiscall*)(void*, int))VT(this, 0x80))(this, a); }
    void V84(void* p, int a, int b) { ((void(__thiscall*)(void*, void*, int, int))VT(this, 0x84))(this, p, a, b); }
    uint32_t VB0() { return ((uint32_t(__thiscall*)(void*))VT(this, 0xb0))(this); }
    void* VB4(uint32_t i) { return ((void*(__thiscall*)(void*, uint32_t))VT(this, 0xb4))(this, i); }
    bool VD0() { return ((bool(__thiscall*)(void*))VT(this, 0xd0))(this); }
    void VE8(int a) { ((void(__thiscall*)(void*, int))VT(this, 0xe8))(this, a); }
};
struct Node {                                // FUN_00d51660 result
    char pad[0x6c];
    uint32_t flags;                           // +0x6c, bit 4 = valid
    cSPCreatureBase_s00d6_3fd0* GetOwner();              // 0x00ff0420
};
struct TuningObj {
    uint32_t GetActive();                     // 0x004d3d40
    void* FUN_004d3d20();
};
Node* FUN_00d51660();
uint32_t* FUN_00d2e340();
namespace nSPBehaviorTree {
 struct behavior_memory_block_s00d6_3fd0 { int state; }; 
}
using nSPBehaviorTree::behavior_memory_block_s00d6_3fd0;
struct MB1 : behavior_memory_block_s00d6_3fd0 { int f04; int f08; int anim; };                       // 0x00d63fd0
// ---- items of slice s00d63fd0 end

// @ 0x00d61ce0
void* __cdecl FUN_00d61ce0(void** out, void* begin, void* end, u32* key)
{
    while (begin != end && ((u32*)begin)[2] != *key)
        begin = *(void**)begin;
    *out = begin;
    return out;
}

// @ 0x00d61d10
bool __cdecl FUN_00d61d10(cSPCreatureBase* c, int, int, int, int, int* st)
{
    st[0] = 0;
    st[1] = 0;
    if (c->mFlagF90 != 0) {
        s32 r = (s32)((RandomLCG*)0x01601760)->RandomUint32Uniform(1000);
        if (r < 0x15e) {
            st[1] = (int)c->PlayAnimation(0x315be650, 1, -1);
            return true;
        }
        if (r < 0x2bc) {
            st[1] = (int)c->PlayAnimation(0x315be65a, 1, -1);
            return true;
        }
        st[1] = (int)c->PlayAnimation(0x715be665, 1, -1);
        return true;
    }
    return true;
}

// @ 0x00d61dc0
f32 __cdecl FUN_00d61dc0(cSPCreatureBase* c)
{
    HomeInfo* h = c->FUN_00c04590();
    void** ownerSlot = &h->mOwner;
    cSPCreatureBase* owner = (cSPCreatureBase*)*ownerSlot;
    if (owner != 0 && owner->mpBTree->mKey1d8 == 0x2d852f1 &&
        (owner->mFlagsB58 & 0x400) != 0)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d62010
bool __cdecl FUN_00d62010(cSPCreatureBase* c, int, int, int, int, int* st)
{
    HomeInfo* h = c->FUN_00c04590();
    void** ownerSlot = &h->mOwner;
    cSPCreatureBase* owner = (cSPCreatureBase*)*ownerSlot;
    if (owner == 0)
        return false;
    if (FUN_00d99500(owner) == 0)
        return false;
    if (FUN_00d99470(owner->GetTargetAsCreature()) == 0)
        return false;
    {
        void* r = owner->mpBTree->mPtr600;
        if (r != 0 && *(u32*)((char*)r + 8) != 0x2d852e6)
            return false;
    }

    cSPCreatureBase* other = owner->GetTargetAsCreature();
    Combatant* selfCombat = (Combatant*)((char*)owner + 0x5a8);
    Combatant* otherCombat = (Combatant*)((char*)other + 0x5a8);
    bool strong;
    if (selfCombat->GetHealthPct() > g_f1485544)
        strong = true;
    else
        strong = selfCombat->GetHealthPct() > otherCombat->GetHealthPct();

    if (*st == 0) {
        if (c->mLoco.IsNearGoal()) {
            f32 r = c->mLoco.GetFootprintRadius() * g_f13f08e4;
            f32 len = sqrtf(r * ((f32)c->FUN_00c04590()->m104 * r));
            f32 scale = strong ? 1.0f : g_f13f08e4;
            f32 back = (owner->mLoco.GetFootprintRadius() + len) * scale;

            Vec3 dirTmp;
            Vec3* dir = owner->mLoco.GetDirection(&dirTmp);
            Vec3 nd;
            normalized_safe(&nd, dir);

            Vec3 want;
            Vec3* pos = owner->mLoco.GetPosition();
            want.x = pos->x - nd.x * back;
            want.y = pos->y - nd.y * back;
            want.z = pos->z - nd.z * back;

            Vec3 surf;
            PlanetModel()->DirectionToSurfacePosition(&surf, &want);

            Vec3 rnd;
            PlanetModel()->MakeRandomWorldPosition(&rnd, &surf, 0.0f, len);

            cSPCreatureBase* tc = other->GetTargetAsCreature();
            c->v84(tc != 0 ? (void*)((char*)tc + 0x5a8) : 0, 1, 0);
            c->MoveToPointAtSpeed(2, &rnd, 1.0f, g_f1470f1c);
            *st = 0;
            return true;
        }
        return true;
    }
    if (*st == 1) {
        if (!c->AnimationFinished((u32)st[1]))
            return true;

        f32 r = c->mLoco.GetFootprintRadius() * g_f13f08e4;
        f32 len = sqrtf(r * ((f32)c->FUN_00c04590()->m104 * r));
        f32 scale = strong ? 1.0f : g_f13f08e4;
        f32 back = (owner->mLoco.GetFootprintRadius() + len) * scale;

        Vec3 dirTmp;
        Vec3* dir = owner->mLoco.GetDirection(&dirTmp);
        Vec3 nd;
        normalized_safe(&nd, dir);

        Vec3 want;
        Vec3* pos = owner->mLoco.GetPosition();
        want.x = pos->x - nd.x * back;
        want.y = pos->y - nd.y * back;
        want.z = pos->z - nd.z * back;

        Vec3 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &want);

        Vec3 d;
        d.x = pos->x - surf.x;
        d.y = pos->y - surf.y;
        d.z = pos->z - surf.z;

        if (d.z * d.z + d.y * d.y + d.x * d.x > len * len) {
            Vec3 rnd;
            PlanetModel()->MakeRandomWorldPosition(&rnd, &surf, 0.0f, len);

            cSPCreatureBase* tc = other->GetTargetAsCreature();
            c->v84(tc != 0 ? (void*)((char*)tc + 0x5a8) : 0, 1, 0);
            c->MoveToPointAtSpeed(2, &rnd, 1.0f, g_f1470f1c);
            *st = 0;
            return true;
        }

        if (strong) {
            st[1] = (int)c->PlayAnimation(0x566b3a0, 1, -1);
        } else {
            if (((RandomLCG*)0x01601760)->RandomUint32Uniform(100) > 0x5a)
                st[1] = (int)c->PlayAnimation(0xd1dce195, 1, -1);
            else
                st[1] = (int)c->PlayAnimation(0x566b326, 1, -1);
        }
        st[0] = 1;
        return true;
    }
    return true;
}

// @ 0x00d624f0
bool __cdecl FUN_00d624f0(cSPCreatureBase* c, int, int, int, int, int* st)
{
    *st = 0;

    cSPCreatureBase* blk = 0;
    AnimPlayRes* r = c->mpBTree->mStimuli.Play(0, 2);
    if (r != 0)
        blk = FUN_00d999d0(r);
    c->mpBTree->mStimuli.ClearAll(0, 2);
    if (blk == 0)
        return false;

    c->PlayAnimation(0x566b36b, 1, -1);
    c->v84((void*)((char*)blk + 0x5a8), 0, 0);

    Vec3* b = c->mLoco.GetPosition();
    Vec3* a = blk->mLoco.GetPosition();
    f32 dx = b->x - a->x;
    f32 dy = b->y - a->y;
    f32 dz = b->z - a->z;
    f32 inv = 1.0f / sqrtf(dy * dy + dx * dx + dz * dz + g_f13ec4b8);

    Vec3 want;
    Vec3* p = c->mLoco.GetPosition();
    want.x = p->x + dx * inv * g_f147bbdc;
    want.y = p->y + dy * inv * g_f147bbdc;
    want.z = p->z + dz * inv * g_f147bbdc;

    Vec3 surf;
    PlanetModel()->DirectionToSurfacePosition(&surf, &want);

    Vec3 rnd;
    PlanetModel()->MakeRandomWorldPosition(&rnd, &surf, g_f1488874, g_f1486110);

    c->MoveToPointAtSpeed(2, &rnd, 1.0f, g_f1470f1c);
    return true;
}

// @ 0x00d63560
namespace SP {
bool FUN_00d63560(cSPCreatureBase_s00d6_3560* self, int, int, int, int, FollowState* st, int, float lookahead)
{
    cSPCreatureBase_s00d6_3560* me = self;
    Herd* herd = self->GetHerd();
    cSPCreatureBase_s00d6_3560* leader = herd->mpLeader;
    if (!FUN_00d99500(leader))
        return false;

    float dist = FUN_00d99ac0(leader, self, 1);
    Vec3_s00d6_3560* leaderPos = leader->GetPosition();
    const Vec3_s00d6_3560& lv = leader->GetVelocity();

    if (lv.x * lv.x + lv.y * lv.y + lv.z * lv.z > 0.1f && leader->FUN_00c0ee90() != self) {
        if (st->mActive == 0) {
            float dx = leaderPos->x - st->mAnchor.x;
            float dy = leaderPos->y - st->mAnchor.y;
            float dz = leaderPos->z - st->mAnchor.z;
            float distSq = dx * dx + dy * dy + dz * dz;
            float r = leader->GetRadius();
            if (!(distSq > r * r) && dist < DAT_01582e04)
                goto stopped;
        }
        {
            st->mActive = 1;
            if (!self->PrepareMove())
                self->FUN_00c14750(1);

            cSPCreatureBase_s00d6_3560* target = leader;
            ListNode* sentinel = &herd->mMembers;
            ListIter found;
            FindInList(&found, ListIter(sentinel->mpNext), ListIter(sentinel), &me);
            if (found.mpNode != sentinel && found.mpNode != sentinel->mpNext)
                target = found.mpNode->mpPrev->mValue;

            int mode = 2;
            if (FUN_00d99ac0(target, self, 1) >= DAT_01582e04)
                mode = 3;

            const Vec3_s00d6_3560& tv = target->GetVelocity();
            Vec3_s00d6_3560 off;
            off.x = tv.x * lookahead;
            off.y = tv.y * lookahead;
            off.z = tv.z * lookahead;
            Vec3_s00d6_3560* tp = target->GetPosition();
            Vec3_s00d6_3560 pred;
            pred.x = tp->x + off.x;
            pred.y = tp->y + off.y;
            pred.z = tp->z + off.z;
            Vec3_s00d6_3560 surf;
            PlanetModel_s00d6_3560()->DirectionToSurfacePosition(&surf, &pred);

            float radius = target->GetRadius();
            Vec3_s00d6_3560 res;
            if (target == leader) {
                float k = radius + radius;
                Vec3_s00d6_3560 tmp;
                Vec3_s00d6_3560* n = normalized_safe_s00d6_3560(&tmp, &target->GetVelocity());
                res.x = surf.x - n->x * k;
                res.y = surf.y - n->y * k;
                res.z = surf.z - n->z * k;
            } else {
                float k = radius;
                Vec3_s00d6_3560 tmp;
                Vec3_s00d6_3560* n = normalized_safe_s00d6_3560(&tmp, &target->GetVelocity());
                res.x = surf.x - n->x * k;
                res.y = surf.y - n->y * k;
                res.z = surf.z - n->z * k;
            }
            Vec3_s00d6_3560 buf;
            Vec3_s00d6_3560 dest = *PlanetModel_s00d6_3560()->DirectionToSurfacePosition(&buf, &res);
            self->MoveToPointAtSpeed(mode, &dest, 1.0f, 2.0f);
            goto done;
        }
    }

stopped:
    if (st->mActive == 0 && dist < DAT_01582e04) {
        if (self->GetState()->mHasPath != 0 && (self->mFlags330 & 1) == 0)
            return true;
        Vec3_s00d6_3560* lp = leader->GetPosition();
        Vec3_s00d6_3560* sp = self->GetPosition();
        Vec3_s00d6_3560 d;
        d.x = sp->x - lp->x;
        d.y = sp->y - lp->y;
        d.z = sp->z - lp->z;
        Vec3_s00d6_3560 fb;
        Vec3_s00d6_3560* f = leader->GetFacing(&fb);
        if (!(f->z * d.z + f->y * d.y + f->x * d.x > 0.0f))
            return true;
        if (leader->FUN_00c0ee90() == self)
            return true;
        st->mAnchor = *leader->GetPosition();
        if (!self->PrepareMove())
            self->FUN_00c14750(1);
        float lr = leader->GetRadius();
        float twoR = lr + lr;
        Vec3_s00d6_3560 fb2;
        Vec3_s00d6_3560* n = normalized_safe_s00d6_3560(&fb2, leader->GetFacing(&fb));
        Vec3_s00d6_3560 t0;
        t0.x = leaderPos->x - n->x * twoR;
        t0.y = leaderPos->y - n->y * twoR;
        t0.z = leaderPos->z - n->z * twoR;
        Vec3_s00d6_3560 surf;
        PlanetModel_s00d6_3560()->DirectionToSurfacePosition(&surf, &t0);
        Vec3_s00d6_3560 fb3;
        self->MoveToPointAndFacingAtSpeed(2, &surf, leader->GetFacing(&fb3), 1.0f, 2.0f);
        goto done;
    }

    st->mActive = 0;
    {
        st->mAnchor = *leader->GetPosition();
        if (!self->PrepareMove())
            self->FUN_00c14750(1);
        int mode = 2;
        if (dist >= DAT_01582e04)
            mode = 3;
        float lr = leader->GetRadius();
        float twoR = lr + lr;
        Vec3_s00d6_3560 fb;
        Vec3_s00d6_3560* f = leader->GetFacing(&fb);
        float inv = 1.0f / sqrtf(f->x * f->x + f->y * f->y + f->z * f->z + 1e-8f);
        Vec3_s00d6_3560 t0;
        t0.x = leaderPos->x - f->x * inv * twoR;
        t0.y = leaderPos->y - f->y * inv * twoR;
        t0.z = leaderPos->z - f->z * inv * twoR;
        Vec3_s00d6_3560 surf;
        PlanetModel_s00d6_3560()->DirectionToSurfacePosition(&surf, &t0);
        if (self->GetState()->mHasPath != 0) {
            Vec3_s00d6_3560* g = self->GetGoalPosition();
            float gx = g->x - surf.x;
            float gy = g->y - surf.y;
            float gz = g->z - surf.z;
            if (gz * gz + gy * gy + gx * gx <= DAT_01582e04 * DAT_01582e04)
                return true;
        }
        self->MoveToPointAtSpeed(mode, &surf, 1.0f, 2.0f);
    }
done:
    self->GetState()->mMoveFlags |= 1;
    return true;
}
}  // namespace SP

// @ 0x00d63c90
namespace SP {
bool FUN_00d63c90(cSPCreatureBase_s00d6_3560* self, int, int, int, int, NavOutput* out)
{
    if (out != 0)
        out->mField0c = 0;

    Herd* herd = self->GetHerd();
    cSPCreatureBase_s00d6_3560* leader = herd->mpLeader;
    Loco_s00d6_3560* loco = leader;                       // Loco sub-object at leader+0xc0

    out->mPosition.x = 0.0f;
    out->mPosition.y = 0.0f;
    out->mPosition.z = 0.0f;

    float baseRadius = loco->GetRadius();
    float searchRadius = baseRadius + 3.0f;
    float radius = loco->GetRadius();
    Vec3_s00d6_3560* leaderPos = loco->GetPosition();

    Vec3_s00d6_3560 randomPos = *leaderPos;
    cPlanetModel_s00d6_3560* planet = PlanetModel_s00d6_3560(&randomPos, leaderPos);
    planet->MakeRandomWorldPosition();

    Vec3_s00d6_3560 water = randomPos;
    planet = PlanetModel_s00d6_3560(&water, 20.0f, &randomPos);
    planet->FindClosestWater();

    Vec3_s00d6_3560* selfPos = self->GetPosition();
    float dx = water.x - selfPos->x;
    float dy = water.y - selfPos->y;
    float dz = water.z - selfPos->z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);

    Vec3_s00d6_3560 target;
    target.x = water.x + dx * inv * radius;
    target.y = water.y + dy * inv * radius;
    target.z = water.z + dz * inv * radius;

    Vec3_s00d6_3560 surf = target;
    planet = PlanetModel_s00d6_3560(&surf, &target);
    Vec3_s00d6_3560* dest = planet->DirectionToSurfacePosition(&surf, &target);
    Vec3_s00d6_3560 moveTo = *dest;
    self->MoveToPointAtSpeed(2, &moveTo, 1.0f, 2.0f);
    self->FUN_00c14750(0);

    (void)searchRadius;
    return true;
}
}  // namespace SP

// @ 0x00d63ea0
namespace SP {
void FUN_00d63ea0(cSPCreatureBase_s00d6_3560* self, int, int, int, int, CreatureActionArgs* args)
{
    if (self->mFieldB5e == 0) {
        int state = args->mState;
        if (state == 1 || state == 2) {
            Loco_s00d6_3560* loco = self;
            float radius = loco->GetRadius();
            Vec3_s00d6_3560 facing;
            Vec3_s00d6_3560* f = loco->GetFacing(&facing);
            Vec3_s00d6_3560* pos = loco->GetPosition();

            Vec3_s00d6_3560 target;
            target.x = pos->x + f->x * radius;
            target.y = pos->y + f->y * radius;
            target.z = pos->z + f->z * radius;

            Vec3_s00d6_3560 surface = target;
            cPlanetModel_s00d6_3560* planet = PlanetModel_s00d6_3560(&surface, &target);
            planet->PrepareSurface();
            self->PlayAnimationWithTarget(0x27079c3, &surface, -1);
        } else {
            self->FUN_00c14750(0);
        }
        self->FinishAction(0, 0, 0);
    }

    if (args != 0 && args->mpObject != 0)
        args->mpObject->Release();
}
}  // namespace SP

// @ 0x00d63fd0
bool BehaviorTick_00d63fd0(cSPCreatureBase_s00d6_3fd0* c, double d, unsigned a, unsigned b, behavior_memory_block_s00d6_3fd0* mem, void* x, float dt)
{
    MB1* m = (MB1*)mem;
    Node* n = FUN_00d51660();
    if (!((n->flags >> 4) & 1))
        return false;
    cSPCreatureBase_s00d6_3fd0* owner = n->GetOwner();
    if (!owner)
        return false;
    switch (m->state) {
    case 0:
        if (c->AnimationFinished(m->anim)) {
            m->state = 2;
            return true;
        }
        break;
    case 1:
        if (c->FUN_00c0e070(m->anim) || c->AnimationFinished(m->anim)) {
            c->L()->Slot40(c->V80(0));
            m->state = 0;
            return true;
        }
        break;
    case 2: {
        IdleAnim* r = c->B()->Stim()->PlayIdleAnimation(0, 0x10);
        if (r) {
            int v = r->id;
            m->f04 = v;
            if (v == -1) {
                m->state = 4;
                m->anim = c->PlayAnimation(0xd41b79ed, 1, -1);
                return true;
            }
            TuningObj* t = ((TuningObj**)FIELD(void*, FIELD(void*, c, 0xb20), 0x6d4))[v];
            m->anim = c->PlayAnimation(t->GetActive(), 1, -1);
            c->B()->Stim()->ClearAll(0, 0x10);
            m->state = 3;
            if ((FIELD(uint32_t, c, 0xb58) >> 9) & 1) {
                uint32_t idx = FIELD(uint32_t, t, 8);
                uint32_t* bits = (uint32_t*)((char*)FUN_00d2e340() + 0x38);
                if (idx < 0x58)
                    bits[idx >> 5] |= 1 << (idx & 0x1f);
                owner->B()->Stim()->SetStimulus(0, 0x10, FLT_MAX, 0);
                owner->B()->Stim()->PlayIdleAnimation(0, 0x10)->id = -1;
                return true;
            }
        }
        break;
    }
    case 3:
        if (c->AnimationFinished(m->anim)) {
            if ((FIELD(uint32_t, c, 0xb58) >> 9) & 1) {
                owner->B()->Stim()->SetStimulus(0, 0x10, FLT_MAX, 0);
                owner->B()->Stim()->PlayIdleAnimation(0, 0x10)->id = m->f04;
            }
            m->f04 = 0;
            m->anim = 0;
            m->state = 2;
        }
        break;
    }
    return true;
}
