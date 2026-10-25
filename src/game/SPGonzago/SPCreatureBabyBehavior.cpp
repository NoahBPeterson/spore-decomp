// src/game/SPGonzago/SPCreatureBabyBehavior.cpp -- migrated from slice(s) s00d61c20 by tools/migrate/rewrite.py
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
