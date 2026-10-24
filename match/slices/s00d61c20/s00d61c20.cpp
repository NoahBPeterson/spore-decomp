// Slice s00d61c20 -- 0x00d61c20 .. 0x00d624f0 (10 functions).
//
// Baby-creature behaviour-tree callbacks acting on a cSPCreatureBase: the idle
// wait/play actives (00d61c20 / 00d61cb0 / 00d61d10), three "is the parent busy"
// float deciders (00d61d90 / 00d61dc0 / 00d61e00) that read the creature's owner
// object, the fight active (00d61e40 / BABY_FIGHT_Tick @ 00d62010) and the flee
// active (BABY_FLEE_Activate @ 00d624f0), plus one generic keyed-list find
// (00d61ce0).
//
// The behaviour nodes were __cdecl with the shared six-slot signature
// (creature, a, b, c, d, int* state): argument 1 lives at [esp+4], the state
// word at [esp+0x18]; the middle four are unused here.  Callee conventions were
// taken from the call sites (PlanetModel() takes no argument - the pushed
// pointers belong to the DirectionToSurfacePosition / MakeRandomWorldPosition
// that follow it).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;
typedef float          f32;

// anonymous virtual filler for the many vtable slots we never call
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vec3 { f32 x, y, z; };

// ---------------------------------------------------------------------------
// retail read-only constants (address in the comment)
// ---------------------------------------------------------------------------
extern const f32 g_f13ec4b8;   // 0x013ec4b8  1.0e-8f  (normalise epsilon)
extern const f32 g_f13f08e4;   // 0x013f08e4  1.25f
extern const f32 g_f1470f1c;   // 0x01470f1c  2.0f
extern const f32 g_f147bbdc;   // 0x0147bbdc  15.0f
extern const f32 g_f1485544;   // 0x01485544  0.75f
extern const f32 g_f1485720;   // 0x01485720  1.0f
extern const f32 g_f1486110;   // 0x01486110  5.0f
extern const f32 g_f1488874;   // 0x01488874  0.1f

// ---------------------------------------------------------------------------
// engine helpers / objects reached by the retail code (address in the comment)
// ---------------------------------------------------------------------------
struct cBehaviorTreeData;
struct HomeInfo;
struct cPlanetModel;

class cSPCreatureBase;
struct Combatant;

// the global EA random generator living at 0x01601760
struct RandomLCG {
    u32 RandomUint32Uniform(u32 range);       // 0x00a68fb0 (ret 4)
};

// the avatar of the game noun manager (0x00b1fdb0 result)
struct cAvatar {
    void* FUN_00d51660();                     // 0x00d51660 lazy cDramaManager singleton
};
struct cDramaManager {
    char mPad00[0x6c];
    u32  mMode6c;                             // +0x6c  bit 4 = "idle actives allowed"
};
struct cGameNounManager {
    cAvatar* GetAvatar();                     // 0x00b1fdb0
};

cGameNounManager* __cdecl NounManager();                  // 0x00b3d300
void*             __cdecl FUN_00d51660();                 // 0x00d51660
cSPCreatureBase*  __cdecl FUN_00d999d0(void* block);      // 0x00d999d0 WatchMemoryBlock
cSPCreatureBase*  __cdecl FUN_00d99500(void* owner);      // 0x00d99500 (ret 4 -> cdecl, 1 arg)
s32               __cdecl FUN_00d99470(cSPCreatureBase* c);// 0x00d99470
cPlanetModel*     __cdecl PlanetModel();                  // 0x00b3d350 (0 args)
Vec3*             __cdecl normalized_safe(Vec3* out, const Vec3* in);  // 0x00449c20

// behaviour_stimuli sits at cBehaviorTreeData+0x08
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

// ---------------------------------------------------------------------------
// creature sub-objects
// ---------------------------------------------------------------------------
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

// the owner/registration object returned by cSPCreatureBase::FUN_00c04590
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

// the planet model behind PlanetModel(): DirectionToSurfacePosition and
// MakeRandomWorldPosition are __thiscall members that clean their own stack.
struct cPlanetModel {
    void DirectionToSurfacePosition(Vec3* out, const Vec3* pos);              // 0x00b815a0 (ret 8)
    void MakeRandomWorldPosition(Vec3* out, const Vec3* center, f32 minR, f32 maxR);  // 0x00b81780 (ret 0x10)
};

// ---------------------------------------------------------------------------
// behaviour nodes
// ---------------------------------------------------------------------------

// @ 0x00d61c20
bool __cdecl FUN_00d61c20(cSPCreatureBase* c, int, int, int, int, int* st)
{
    cGameNounManager* nouns = NounManager();
    nouns->GetAvatar();
    cDramaManager* dm = (cDramaManager*)FUN_00d51660();
    if (((u8)(dm->mMode6c >> 4) & 1) == 0)
        return false;
    switch (*st) {
    case 0:
        if (c->mLoco.IsNearGoal())
            *st = 1;
        break;
    case 1: {
        AnimPlayRes* r = c->mpBTree->mStimuli.Play(0, 0x10);
        if (r != 0)
            c->PlayAnimation(r->mAnimId, 1, -1);
        c->mpBTree->mStimuli.ClearAll(0, 0x10);
        return true;
    }
    default:
        break;
    }
    return true;
}

// @ 0x00d61cb0
void __cdecl FUN_00d61cb0(cSPCreatureBase* c)
{
    c->FUN_00c0b370(-1);
    c->mpBTree->mStimuli.ClearAll(0, 0x10);
}

// @ 0x00d61ce0
// Keyed-list find: walk the node chain from `begin` until the entry whose
// +8 key equals *key (or the end sentinel), write the node through `out` and
// hand the out slot back in eax (the retail epilogue leaves arg1 in eax).
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

// @ 0x00d61d90
f32 __cdecl FUN_00d61d90(cSPCreatureBase* c)
{
    HomeInfo* h = c->FUN_00c04590();
    void** ownerSlot = &h->mOwner;
    void* owner = *ownerSlot;
    if (FUN_00d99500(owner) == 0)
        return 0.0f;
    return 1.0f;
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

// @ 0x00d61e00
f32 __cdecl FUN_00d61e00(cSPCreatureBase* c)
{
    HomeInfo* h = c->FUN_00c04590();
    void** ownerSlot = &h->mOwner;
    cSPCreatureBase* owner = (cSPCreatureBase*)*ownerSlot;
    if (owner != 0) {
        void* r = owner->mpBTree->mPtr600;
        if (r != 0 && *(u32*)((char*)r + 8) == 0x2d852e6)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d61e40
bool __cdecl FUN_00d61e40(cSPCreatureBase* c, int, int, int, int, int* st)
{
    HomeInfo* h = c->FUN_00c04590();
    void** ownerSlot = &h->mOwner;
    cSPCreatureBase* owner = (cSPCreatureBase*)*ownerSlot;

    f32 r = c->mLoco.GetFootprintRadius() * g_f13f08e4;
    f32 len = sqrtf(r * ((f32)c->FUN_00c04590()->m104 * r));
    f32 back = owner->mLoco.GetFootprintRadius() + len;

    Vec3 dirTmp;
    Vec3* dir = owner->mLoco.GetDirection(&dirTmp);
    f32 inv = 1.0f / sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z + g_f13ec4b8);
    Vec3 n;
    n.x = dir->x * inv;
    n.y = dir->y * inv;
    n.z = dir->z * inv;

    Vec3 want;
    Vec3* pos = owner->mLoco.GetPosition();
    want.x = pos->x - n.x * back;
    want.y = pos->y - n.y * back;
    want.z = pos->z - n.z * back;

    Vec3 surf;
    PlanetModel()->DirectionToSurfacePosition(&surf, &want);

    Vec3 rnd;
    PlanetModel()->MakeRandomWorldPosition(&rnd, &surf, 0.0f, len);

    cSPCreatureBase* tc = owner->GetTargetAsCreature();
    c->v84(tc != 0 ? (void*)((char*)tc + 0x5a8) : 0, 1, 0);
    c->MoveToPointAtSpeed(2, &rnd, 1.0f, g_f1470f1c);

    st[0] = 0;
    st[1] = 0;
    return true;
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