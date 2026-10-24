// match/slices/s00d885a0/s00d885a0.cpp
// Behaviour-tree Activate/Tick callbacks for the "posse" / alert creature behaviours.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;
typedef float          f32;
typedef double         f64;

struct Vec3 { f32 x, y, z; };

// ---------------------------------------------------------------------------
// Placeholder-struct methods: every ecx-passed callee is declared here as a
// member so the call site emits `mov ecx, <this>` + `call rel32`.
// ---------------------------------------------------------------------------
struct COps {
    void* FUN_00c04590();                        // 0x00c04590 Get()
    void* FUN_00b1fdb0();                        // 0x00b1fdb0 cGameNounManager::GetAvatar
    void* FUN_00c0ee70();                        // 0x00c0ee70 GetTargetAsCreature
    bool  FUN_00c0c130();                        // 0x00c0c130
    void  FUN_00c12310(u32, s32, u32);           // 0x00c12310 InterruptAnimation
    void  FUN_00c17350(u32, u32);                // 0x00c17350
    void  FUN_00c6ac90(u32);                     // 0x00c6ac90
    bool  FUN_00bc98f0(u32, u32);                // 0x00bc98f0 ClearAll
    void* FUN_00bc97f0(u32, u32, f32, void*);    // 0x00bc97f0 Set
    u32   FUN_00bc96a0(u32, u32);                // 0x00bc96a0 Play
    void  FUN_00c13a30(u32);                     // 0x00c13a30 Hover
    f32   FUN_009360d0();                        // 0x009360d0 RandomDoubleUniform
    bool  FUN_00c42e20();                        // 0x00c42e20 IsNearGoal
    bool  FUN_00c12400(u32);                     // 0x00c12400 AnimationFinished
    bool  FUN_00c0e0c0(s32);                     // 0x00c0e0c0
    void  FUN_00c14940(u32, void*, s32, s32);    // 0x00c14940 PlayAnimationWithTarget
    void  FUN_00c1c1d0(u32, Vec3*, f32, f32);    // 0x00c1c1d0 MoveToPointAtSpeed
    bool  FUN_00c0d560(void*, f32, f32);         // 0x00c0d560
    void* FUN_00c41ec0();                        // 0x00c41ec0
    void* FUN_00ac9850();                        // 0x00ac9850 cLocomotionRequest ctor
    void  FUN_007a41a0();                        // 0x007a41a0 dtor
    Vec3* FUN_00b815a0(Vec3*, Vec3*);            // 0x00b815a0 DirectionToSurfacePosition
    bool  FUN_00b7e3e0(void*);                   // 0x00b7e3e0
    void* FUN_0041cb40(void*);                   // 0x0041cb40 Matrix3::Assign
};

#define MOPS(p) ((COps*)(p))
#define VT(p)   (*(void***)(p))

// ---------------------------------------------------------------------------
// Free (cdecl) callees, addressed by their absolute VA.
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b3d300();                          // 0x00b3d300 NounManager
void* __cdecl FUN_00d999d0(void*);                     // 0x00d999d0 WatchMemoryBlock
void  __cdecl FUN_00d88c70(void* node, void* creature); // 0x00d88c70
void* __cdecl FUN_00d99470(void*);                     // 0x00d99470
void  __cdecl FUN_00d7d540(void*, f32, f32, void*);    // 0x00d7d540 StayBetween
f32   __cdecl FUN_00d99ac0(void*, void*, u32);         // 0x00d99ac0
f32   __cdecl FUN_00d38a30(u32, void*);                // 0x00d38a30
void* __cdecl FUN_00b3d350(Vec3*, Vec3*);              // 0x00b3d350 PlanetModel
void* __cdecl FUN_0059aed0(void*, void*);              // 0x0059aed0
void  __cdecl FUN_0059c190(void*, void*);              // 0x0059c190 Matrix3FromQuaternion
void  __cdecl FUN_00f47380(void*);                     // 0x00f47380 operator_delete_array
void* __cdecl FUN_0067ddd0();                          // 0x0067ddd0 EffectsManagerPtr
bool  __cdecl FUN_00b7e3e0(void*);                     // 0x00b7e3e0

// ---------------------------------------------------------------------------
// Field layouts of the retail objects touched by this slice.
// ---------------------------------------------------------------------------
struct Creature {
    u8    pad000[0xb4c];
    void* mpStimuliMgr;      // 0xb4c
    u8    padB50[0xb5c - 0xb50];
    u8    mbFlag5c;          // 0xb5c
};

// Behaviour-tree node state for the ALERT action.
struct AlertNode {
    f32   mF_00;             // 0x00
    f32   mF_04;             // 0x04
    u32   mU_08;             // 0x08
    u32   mU_0c;             // 0x0c
    u32   mU_10;             // 0x10
    void* mpTarget;          // 0x14
    u32   mU_18;             // 0x18
};

// Behaviour-tree node state for the CALLED_TO_AVATAR action.
struct AvatarNode {
    f32   mRandom;           // 0x00
    void* mpTarget;          // 0x04
};

// Behaviour-tree node state for the POSSE behaviours.
struct PosseNode {
    f32   mTimer;            // 0x00
    f32   mTimer2;           // 0x04
    f32   mRadius;           // 0x08
    u8    mB_0c;             // 0x0c
    u8    mFlagD;            // 0x0d
    u8    mFlagE;            // 0x0e
    u8    mPad0f;            // 0x0f
    u32   mAnim;             // 0x10
};

// The object returned by cSPCreatureBase::Get(): tracks a current creature and
// a linked list head that points at itself when empty.
struct CreatureManager {
    u8    pad000[0x164];
    void* mpOwner;           // 0x164
    void* mpListHead;        // 0x168
};

// Spatial query record filled by the slot-0xdc callback.
struct SpatialQuery {
    void* mpResult;          // 0x00
    u32   mU_04;             // 0x04
    u32   mU_08;             // 0x08
    u32   mU_0c;             // 0x0c
    u32   mU_10;             // 0x10
    f32   mF_14;             // 0x14
    f32   mF_18;             // 0x18
    f32   mF_1c;             // 0x1c
    f32   mF_20;             // 0x20
    u32   mU_24;             // 0x24
    u8    mPad28[0x4c - 0x28]; // 0x28
    u8    mB_4c;             // 0x4c
    u8    mPad4d[0x50 - 0x4d]; // 0x4d
    f32   mF_50;             // 0x50
    f32   mF_54;             // 0x54
    f32   mF_58;             // 0x58
    u32   mU_5c;             // 0x5c
    f32   mF_60;             // 0x60
    f32   mF_64;             // 0x64
    f32   mF_68;             // 0x68
    f32   mF_6c;             // 0x6c
    u32   mU_70;             // 0x70
};

extern f32 gF_013eb95c;      // 0x013eb95c
extern f32 gF_01486110;      // 0x01486110
extern f32 gF_0169f03c;      // 0x0169f03c
extern f32 gF_0169f040;      // 0x0169f040
extern f32 gF_0169f044;      // 0x0169f044
extern f32 gF_1470f1c;       // 0x01470f1c
extern f32 gF_1485720;       // 0x01485720 (_HK_REAL_ONE)
extern f32 gF_13ec4b4;       // 0x013ec4b4 (0.9)
extern f32 gF_13ec4b8;       // 0x013ec4b8 (1e-8)
extern f32 gF_147c030;       // 0x0147c030 (FLT_MAX)
extern f32 gF_169f0ec;       // 0x0169f0ec
extern f32 gF_1471064;       // 0x01471064
extern f32 gF_13eb8c8;       // 0x013eb8c8 (0.3)
extern f32 gF_1476b54;       // 0x01476b54 (350.0)
extern f32 gF_169f0d4;       // 0x0169f0d4
extern f32 gF_169f0d8;       // 0x0169f0d8
extern f32 gF_169f0dc;       // 0x0169f0dc
extern f32 gF_1590bd8;       // 0x01590bd8
extern f32 gF_169f0b0;       // 0x0169f0b0 (identity matrix block)

// ---------------------------------------------------------------------------
// 0x00d888b0: ALERT activate -- acquire the alert target, copy its position
// into the node, then notify the creature's spatial subobject.
// ---------------------------------------------------------------------------
// @ 0x00d888b0
u8 __cdecl FUN_00d888b0(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, AlertNode* node, void* ctx)
{
    u8 result = 0;
    if (node != 0)
        node->mpTarget = 0;
    void* creature = *(void**)((u8*)ctx + 4);
    if (creature != 0) {
        void* target = ((void* (__thiscall*)(void*, u32))VT(creature)[0x5c / 4])(creature, 0xce9f6639);
        if (target != 0) {
            void* old = node->mpTarget;
            if (target != old) {
                ((void (__thiscall*)(void*))VT(target)[0])(target);
                node->mpTarget = target;
                if (old != 0)
                    ((void (__thiscall*)(void*))VT(old)[1])(old);
            }
            Vec3* pos = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)target + 0xc0)[0x2c / 4])((u8*)target + 0xc0);
            node->mU_08 = *(u32*)&pos->x;
            node->mU_0c = *(u32*)&pos->y;
            node->mU_10 = *(u32*)&pos->z;
            node->mF_00 = gF_013eb95c;
            node->mF_04 = gF_01486110;
            node->mU_18 = 0;
            ((void (__thiscall*)(void*))VT((u8*)p1 + 0xc0)[0xec / 4])((u8*)p1 + 0xc0);
            result = 1;
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00d88e50: CALLED_TO_AVATAR activate -- start the idle animation, remember
// its handle, then hover and interrupt into the "called to avatar" animation.
// ---------------------------------------------------------------------------
// @ 0x00d88e50
u8 __cdecl FUN_00d88e50(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, AvatarNode* node)
{
    if (node != 0)
        node->mpTarget = 0;
    Creature* c = (Creature*)p1;
    u32 anim = MOPS((u8*)c->mpStimuliMgr + 8)->FUN_00bc96a0(0, 4);
    if (anim == 0)
        return 0;
    void* ref = FUN_00d999d0((void*)anim);
    if (ref == 0)
        return 0;
    node->mRandom = MOPS((void*)0x1601760)->FUN_009360d0();
    void* old = node->mpTarget;
    if (ref != old) {
        ((void (__thiscall*)(void*))VT(ref)[0])(ref);
        node->mpTarget = ref;
        if (old != 0)
            ((void (__thiscall*)(void*))VT(old)[1])(old);
    }
    MOPS(p1)->FUN_00c13a30(1);
    MOPS(p1)->FUN_00c12310(0x724e4024, -1, 0);
    FUN_00d88c70(node, p1);
    return 1;
}


// ---------------------------------------------------------------------------
// 0x00d88ef0: clear the behaviour stimuli, then release the node's target.
// ---------------------------------------------------------------------------
// @ 0x00d88ef0
void __cdecl FUN_00d88ef0(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, void* node)
{
    void* mgr = *(void**)((u8*)p1 + 0xb4c);
    MOPS((u8*)mgr + 8)->FUN_00bc98f0(0, 4);
    if (node != 0) {
        void* obj = *(void**)((u8*)node + 4);
        if (obj != 0)
            ((void (__thiscall*)(void*))VT(obj)[1])(obj);
    }
}

// ---------------------------------------------------------------------------
// 0x00d88970: release the node target, notify the spatial subobject, then set
// the current behaviour.
// ---------------------------------------------------------------------------
// @ 0x00d88970
void __cdecl FUN_00d88970(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, void* node)
{
    if (node != 0) {
        void* obj = *(void**)((u8*)node + 0x14);
        if (obj != 0)
            ((void (__thiscall*)(void*))VT(obj)[1])(obj);
    }
    ((void (__thiscall*)(void*))VT((u8*)p1 + 0xc0)[0xec / 4])((u8*)p1 + 0xc0);
    MOPS(p1)->FUN_00c17350(0x12007c90, 0);
}

// ---------------------------------------------------------------------------
// 0x00d88c10: look up the interaction object, and if it is not "in use" tell
// it to move to the stored index.
// ---------------------------------------------------------------------------
// @ 0x00d88c10
u8 __cdecl FUN_00d88c10(void* p1)
{
    if (*(void**)((u8*)p1 + 0x1a0) != 0) {
        u32 idx = *(u32*)((u8*)p1 + 0x1b0);
        void* o = *(void**)((u8*)p1 + 0x1a0);
        if (o != 0) {
            void* r = ((void* (__thiscall*)(void*, u32))VT(o)[0xc / 4])(o, 0x52aa6117);
            if (r != 0 && idx != 0xffffffff) {
                if (!((bool (__thiscall*)(void*))VT(r)[0x2c / 4])(r)) {
                    MOPS(r)->FUN_00c6ac90(idx);
                    return 1;
                }
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00d88f20: once the creature is near its goal, update its move request.
// ---------------------------------------------------------------------------
// @ 0x00d88f20
u8 __cdecl FUN_00d88f20(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, void* p6)
{
    if (MOPS((u8*)p1 + 0xc0)->FUN_00c42e20())
        FUN_00d88c70(p6, p1);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d885a0: POSSE stay-with-target tick.  Counts down the node timers, picks
// (or re-picks) a posse target and steers the creature towards it.
// ---------------------------------------------------------------------------
// @ 0x00d885a0
u8 __cdecl FUN_00d885a0(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, PosseNode* node, u32 a7, f32 dt)
{
    CreatureManager* gm = (CreatureManager*)MOPS(p1)->FUN_00c04590();
    if (p1 == gm->mpOwner) {
        gm = (CreatureManager*)MOPS(p1)->FUN_00c04590();
        if (gm->mpListHead != (void*)((u8*)gm + 0x168))
            node->mFlagE = 1;
    }
    node->mTimer -= dt;
    if (node->mAnim != 0)
        return (u8)(!MOPS(p1)->FUN_00c12400(node->mAnim));

    void* t = FUN_00d99470(MOPS(p1)->FUN_00c0ee70());
    if (t == 0)
        return 0;
    if (MOPS(p1)->FUN_00c0c130()) {
        MOPS((u8*)((Creature*)p1)->mpStimuliMgr + 8)->FUN_00bc97f0(0x1000000, 0, 10.0f, t);
        return 0;
    }
    ((Creature*)p1)->mbFlag5c = 1;
    if (node->mRadius != 0.0f)
        FUN_00d7d540(p1, 1.0f, node->mRadius, (u8*)t + 0xc0);
    if (!MOPS(p1)->FUN_00c0e0c0(0x2481dfc))
        MOPS(p1)->FUN_00c14940(0x2481dfc, (u8*)t + 0xc0, -1, -1);

    FUN_00d99ac0((u8*)p1 + 0xc0, (u8*)t + 0xc0, 1);

    if (node->mTimer >= 0.0f) {
        if (node->mFlagD != 0) {
            void* r = MOPS(p1)->FUN_00c41ec0();
            if (((u32*)r)[0x17] != 0) {
                f32* pf = (f32*)((u8*)r + 0x14);
                if (*(u32*)r != ((u32*)r)[1])
                    pf = (f32*)(((u32*)r)[1] - 0x3c);
                Vec3* tp = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)t + 0xc0)[0x2c / 4])((u8*)t + 0xc0);
                f32 d2 = (tp->z - pf[2]) * (tp->z - pf[2])
                       + (tp->y - pf[1]) * (tp->y - pf[1])
                       + (tp->x - pf[0]) * (tp->x - pf[0]);
                f32 thr = ((f32 (__thiscall*)(void*))VT((u8*)t + 0xc0)[0x74 / 4])((u8*)t + 0xc0);
                if (d2 <= thr)
                    return 1;
            }
            if (node->mFlagE != 0)
                return 1;
            Vec3* tp = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)t + 0xc0)[0x2c / 4])((u8*)t + 0xc0);
            MOPS(p1)->FUN_00c1c1d0(2, tp, 1.0f, 2.0f);
        }
        return 1;
    }

    node->mTimer2 -= dt;
    f32 near1 = FUN_00d38a30(1, p1);
    f32 near2 = FUN_00d38a30(2, p1);
    Vec3* sp = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)p1 + 0xc0)[0x2c / 4])((u8*)p1 + 0xc0);
    Vec3* tp = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)t + 0xc0)[0x2c / 4])((u8*)t + 0xc0);
    f32 dx = tp->x - sp->x, dy = tp->y - sp->y, dz = tp->z - sp->z;
    f32 dist = sqrtf(dx * dx + dy * dy + dz * dz);
    if (dist < 0.0f)
        dist = 0.0f;
    u8 hit = (u8)MOPS(p1)->FUN_00c0d560(t, near1, dist);
    if (!hit)
        hit = (u8)((bool (__thiscall*)(void*, void*, f32, f32))VT(p1)[0xc0 / 4])(p1, t, near2, dist);
    if (node->mTimer2 < 0.0f) {
        u8 req[0x74];
        MOPS(req)->FUN_00ac9850();
        ((void (__thiscall*)(void*, void*))VT((u8*)t + 0xc0)[0xdc / 4])((u8*)t + 0xc0, req);
        MOPS(req)->FUN_007a41a0();
        return 0;
    }
    return hit;
}

// ---------------------------------------------------------------------------
// 0x00d889b0: JOIN_POSSE activate -- drop the avatar's follow behaviour,
// interrupt the current animation and spawn the join-posse effect.
// ---------------------------------------------------------------------------
// @ 0x00d889b0
u8 __cdecl FUN_00d889b0(void* p1)
{
    void* mgr = FUN_00b3d300();
    void* avatar = MOPS(mgr)->FUN_00b1fdb0();
    if (avatar != 0)
        ((void (__thiscall*)(void*, void*, u32, u32))VT(p1)[0x84 / 4])(p1, (u8*)avatar + 0x5a8, 1, 0);
    MOPS(p1)->FUN_00c12310(0xb225328f, -1, 0);

    void* effect = 0;
    void* em = FUN_0067ddd0();
    if (effect != 0) {
        void* tmp = effect;
        effect = 0;
        ((void (__thiscall*)(void*))VT(tmp)[1])(tmp);
    }
    if (((bool (__thiscall*)(void*, u32, u32, void*))VT(em)[0x2c / 4])(em, 0x33adb87, 0, &effect)) {
        if (effect != 0) {
            ((void (__thiscall*)(void*, void*))VT(em)[0x18 / 4])(em, &effect);
            ((void (__thiscall*)(void*))VT(effect)[8 / 4])(effect);
        }
    }
    if (effect != 0)
        ((void (__thiscall*)(void*))VT(effect)[1])(effect);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d88c70: steer the creature towards the node target, offset by a
// quaternion-rotated surface normal and scaled by the distance.
// ---------------------------------------------------------------------------
// @ 0x00d88c70
void __cdecl FUN_00d88c70(void* node, void* creature)
{
    void* target = *(void**)((u8*)node + 4);
    if (target == 0)
        return;
    Vec3* p = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)target + 0xc0)[0x2c / 4])((u8*)target + 0xc0);
    f32 nx = p->x, ny = p->y, nz = p->z;
    f32 inv = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz + gF_13ec4b8);
    nx *= inv;
    ny *= inv;
    nz *= inv;
    f32 ang = (*(f32*)node * gF_169f0ec) * 0.5f;
    f32 s = sinf(ang);
    f32 c = cosf(ang);
    f32 q[4];
    q[0] = nx * s;
    q[1] = ny * s;
    q[2] = nz * s;
    q[3] = c;
    Vec3 axis;
    void* rot = ((void* (__thiscall*)(void*, void*, Vec3*))VT((u8*)target + 0xc0)[0x5c / 4])((u8*)target + 0xc0, &axis, (Vec3*)q);
    Vec3* r = (Vec3*)FUN_0059aed0((u8*)q + 0x10, rot);
    f32 tx = ((r->x - nx) * gF_13eb8c8 + nx) * gF_1476b54;
    f32 ty = ((r->y - ny) * gF_13eb8c8 + ny) * gF_1476b54;
    f32 tz = ((r->z - nz) * gF_13eb8c8 + nz) * gF_1476b54;
    Vec3* sp = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)creature + 0xc0)[0x2c / 4])((u8*)creature + 0xc0);
    Vec3 dest;
    dest.x = tx + sp->x;
    dest.y = ty + sp->y;
    dest.z = tz + sp->z;
    MOPS(creature)->FUN_00c1c1d0(3, &dest, 1.0f, 2.0f);
}

// ---------------------------------------------------------------------------
// 0x00d88f50: run the spatial query at slot 0xdc and free any returned array.
// ---------------------------------------------------------------------------
// @ 0x00d88f50
u8 __cdecl FUN_00d88f50(void* p1)
{
    SpatialQuery q;
    q.mpResult = 0;
    q.mU_04 = 0;
    q.mU_08 = 0;
    q.mF_14 = gF_0169f03c;
    q.mF_18 = gF_0169f040;
    q.mF_1c = gF_0169f044;
    q.mF_20 = gF_1485720;
    q.mU_24 = 0;
    q.mB_4c = 0;
    q.mF_50 = 0.0f;
    q.mF_54 = 0.0f;
    q.mF_58 = 0.0f;
    q.mU_5c = 0;
    q.mF_60 = gF_1470f1c;
    q.mF_64 = gF_13ec4b4;
    q.mF_68 = gF_147c030;
    q.mF_6c = 0.0f;
    q.mU_70 = 0;
    ((void (__thiscall*)(void*, SpatialQuery*))VT((u8*)p1 + 0xc0)[0xdc / 4])((u8*)p1 + 0xc0, &q);
    if (q.mpResult != 0 && *(u32*)((u8*)q.mpResult - 4) != 0)
        FUN_00f47380(q.mpResult);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d89030: POSSE_FIND_FOOD tick.  While near the goal, sample a random
// offset on the planet surface until a valid (non-ocean) point is found.
// ---------------------------------------------------------------------------
// @ 0x00d89030
u8 __cdecl FUN_00d89030(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, void* node)
{
    u32 anim = MOPS((u8*)((Creature*)p1)->mpStimuliMgr + 8)->FUN_00bc96a0(0x20000000, 0);
    if (anim == 0)
        return 0;
    if (!MOPS((u8*)p1 + 0xc0)->FUN_00c42e20())
        return 1;

    Vec3 surf;
    for (u32 i = 0; i < 8; i++) {
        void* mgr = FUN_00b3d300();
        void* avatar = MOPS(mgr)->FUN_00b1fdb0();
        Vec3* av = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)avatar + 0xc0)[0x2c / 4])((u8*)avatar + 0xc0);
        Vec3* me = (Vec3*)((Vec3* (__thiscall*)(void*))VT((u8*)p1 + 0xc0)[0x2c / 4])((u8*)p1 + 0xc0);
        f32 dx = me->x - av->x, dy = me->y - av->y, dz = me->z - av->z;
        f32 inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + gF_13ec4b8);
        dx *= inv;
        dy *= inv;
        dz *= inv;
        f32 r = MOPS((void*)0x1601760)->FUN_009360d0();
        f32 d = (r + 1.0f) * 10.0f;
        if (d < 10.0f)
            d = 10.0f;
        if (d > 20.0f)
            d = 20.0f;
        Vec3 p;
        p.x = me->x + dx * d;
        p.y = me->y + dy * d;
        p.z = me->z + dz * d;
        void* pm = FUN_00b3d350(&surf, &p);
        MOPS(pm)->FUN_00b815a0(&surf, &p);
        if (!FUN_00b7e3e0(&surf))
            break;
    }
    MOPS(p1)->FUN_00c1c1d0(2, &surf, 1.0f, 20.0f);
    return 1;
}
