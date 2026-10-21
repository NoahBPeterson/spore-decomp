// Slice s00ec1830 (gold4 #85).
#include <intrin.h>
// SP::PICK_UP_OBJECT behaviour: the tick state machine (FUN_00ec1830), the idle-animation
// helper (FUN_00ec1f80), the "decider" table factory (FUN_00ec1ff0), the RNG-driven
// cooldown helper (FUN_00ec21c0) with its per-frame update (FUN_00ec2130), and the
// behaviour Reset/Activate entry point (FUN_00ec2220).
// Layout notes: retail offsets come from the disassembly; stub classes carry only what is read.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace SP {

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct Box { Vec3 lo, hi; };

// Pad-virtual helper: B's virtuals first, then N unnamed ones.
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

// ---------------------------------------------------------------------------
// The interaction target (the object being picked up).
struct SpatialObj0 {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10();
    virtual const Vec3* GetPosition();                      // 0x2c
};
struct SpatialObj1 : VPad<15, SpatialObj0> {
    virtual void a_30(); virtual void a_34(); virtual void a_38(); virtual void a_3c();
    virtual void a_40(); virtual void a_44(); virtual void a_48(); virtual void a_4c();
    virtual void a_50(); virtual void a_54(); virtual void a_58(); virtual void a_5c();
    virtual void a_60(); virtual void a_64(); virtual void a_68();
    virtual const Box* GetBoundingBox(Box* tmp);            // 0x6c
};
struct SpatialObj2 : VPad<1, SpatialObj1> {
    virtual float GetRadius();                              // 0x74
};
struct SpatialObj : VPad<1, SpatialObj2> {
    virtual void* QueryInterface(uint32_t id);              // 0xb8
    uint8_t pad_bc[0x10c - 0xbc];
    SpatialObj* mpLinked;                                   // +0x108
};

// Locomotive sub-object embedded at creature+0xc0.
struct Loco0 {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10();
    virtual const Vec3* GetPosition();                      // 0x2c
};
struct Loco1 : VPad<6, Loco0> {
    virtual bool IsNearGoalVirtual();                       // 0x48
};
struct Loco2 : VPad<4, Loco1> {
    virtual const Vec3* GetForward(Vec3* tmp);              // 0x5c
};
struct Loco3 : VPad<5, Loco2> {
    virtual float GetRadius();                              // 0x74
};
struct Loco4 : VPad<1, Loco3> {
    virtual float GetFacingAngle();                         // 0x78
};
struct Loco5 : VPad<27, Loco4> {
    virtual void a_ec();                                    // 0xec
    bool IsNearGoal();                                      // 0xc42e20
    const Vec3* GetVelocity();                              // 0xd20610
    void* FUN_00c1ac70(const Vec3* v, uint32_t a, int b, int c, int d, float e);     // 0xc1ac70
};
typedef Loco5 Loco;

struct AnimTarget { virtual void a0(); virtual void a1(); virtual void a2(); };
struct AnimMgr { AnimTarget* PlayIdleAnimation(int a, int b); };    // 0xbc96a0 (ret 8)
struct AnimOwner { uint8_t pad00[8]; AnimMgr mgr; };               // +8

class cSPCreatureBase;

struct InteractableObject { uint8_t pad00[0x71]; uint8_t mb71; };  // +0x71

// ---------------------------------------------------------------------------
// The behaviour state block (last argument of the tick function at +0x18).
struct PickupState {
    int            mState;          // +0x00
    int            mAnimId;         // +0x04  (hashed animation id, -1 = none)
    SpatialObj*    mpTarget;        // +0x08  (AutoRefCount)
    uint8_t        mbFlag;          // +0x0c
    uint8_t        pad0d[3];
    uint8_t        mbAlt;           // +0x10
};

// The decider table entry (0x88 bytes each).
struct DeciderEntry {
    uint8_t  pad00[0x10];
    uint32_t mFlags10;              // +0x10
    uint8_t  mFlag18;               // +0x18
    uint8_t  pad19[3];
    float    mDelay1c;              // +0x1c
    uint8_t  pad20[0x88 - 0x20];
};
struct DeciderHeader {
    uint8_t       pad00[0x7c];
    int32_t       mCount;           // +0x7c
    DeciderEntry* mpEntries;        // +0x80
    uint8_t       pad84[4];
};

// Per-behaviour cooldown timer (used by FUN_00ec2130/FUN_00ec21c0/FUN_00ec2220).
struct PickupTimer {
    uint8_t active;                 // +0x00
    float   time;                   // +0x04
    void*   anim;                   // +0x08
    uint8_t b0c;                    // +0x0c
    uint8_t pad0d[3];
    float   f10;                    // +0x10
    int     i14;                    // +0x14
};

// ---------------------------------------------------------------------------
// external data (address in the comment)
extern Vec3         g_zeroVec;          // 0x16c74a0
extern float        DAT_01471064;       // 0x1471064 = 0.5f
extern float        DAT_013ec4b8;       // 0x13ec4b8
extern float        DAT_013ec4b4;       // 0x13ec4b4
extern float        DAT_01470f1c;       // 0x1470f1c
extern float        DAT_013f08e4;       // 0x13f08e4
extern float        DAT_013eb8a0;       // 0x13eb8a0
extern float        DAT_013f9428;       // 0x13f9428
extern const char   DAT_01488fa4[];     // 0x1488fa4 "Simulator/decider"
extern void*        gRandomLC;          // 0x1601760
extern int          DAT_015aba20;       // 0x15aba20
extern int          DAT_015aba1c;       // 0x15aba1c
extern DeciderEntry DAT_015ab298;       // 0x15ab298 (entry template block, 12 entries)
extern DeciderEntry DAT_015aaaa0;       // 0x15aaaa0 (per-index entry template)
extern DeciderHeader DAT_015ab8f8;      // 0x15ab8f8 (header template block)
extern DeciderEntry DAT_015ab980;       // 0x15ab980 (sentinel entry template)
extern int          DAT_01488f74[];     // 0x1488f74 index table

// ---------------------------------------------------------------------------
// callees
void*  EAAllocate(uint32_t size, const char* name, int, int, int, int);   // 0xf473a0 cdecl
void   Grid_HasValidIndex(void* q);                                       // 0xbc8fa0 cdecl
void*  FUN_00ec03c0(cSPCreatureBase* c);                                  // 0xec03c0 cdecl
bool   FUN_00c7d090(int obj, int* table);                                // 0xc7d090 cdecl
void*  FUN_00d998d0(void* h, uint32_t id);                                // 0xd998d0 cdecl
void*  FUN_00d7d370(cSPCreatureBase* c, const Vec3* v);                   // 0xd7d370 cdecl
void   FUN_00d7d4a0(void* iface, cSPCreatureBase* c);                     // 0xd7d4a0 cdecl
void*  InterfaceCast(SpatialObj** ref);                                   // 0xd7cf90 cdecl
bool   FUN_00c0f510(float v);                                             // 0xc0f510 cdecl
void*  FUN_00c0f9b0(int id, float* out);                                  // 0xc0f9b0 cdecl
Vec3*  normalized_safe(Vec3* out, const Vec3* in, float a, float b);      // 0x449c20 cdecl
float  VectorLength(const Vec3* v);                                       // 0x40ae50 cdecl
bool   Vector3_NotEqual(const Vec3* a, const Vec3* b);                    // 0x41dd30 cdecl
double __fastcall RandomDoubleUniform(void* rng);                         // 0x9360d0
float  RandomFloatRange(float lo, float hi);                              // 0x572a10 cdecl

class cSPCreatureBase { public:
    uint8_t pad00[0x50];
    uint32_t mFlags50;                                      // +0x50
    uint8_t pad54[0x77 - 0x54];
    uint8_t mb77;                                           // +0x77
    uint8_t pad78[0xc0 - 0x78];
    Loco    mLoco;                                          // +0xc0
    uint8_t pad_c4[0x698 - 0xc4];
    uint8_t mDecider[0x88];                                 // +0x698
    uint8_t pad720[0xb54 - 0x720];
    void*   mpB54;                                          // +0xb54

    int   FUN_00c0f4f0();                                   // 0xc0f4f0
    void* FUN_00c0f8a0(int i);                              // 0xc0f8a0
    void  FUN_00c15bd0(int i, int a, int b);                // 0xc15bd0 (ret 0xc)
    void  FUN_00c14750(int a);                              // 0xc14750 (ret 4)
    void* InterruptAnimationWithTarget(uint32_t id, void* t, int a, int b);   // 0xc149c0 (ret 0x10)
    bool  AnimationFinished2(void* anim);                   // 0xc12400 (ret 4)
    void  MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* facing, float s0, float s1);  // 0xc1c5c0
    void  PlayAnimationWithTarget(uint32_t id, const Vec3* p, void* a);       // 0xc14910
    void  PlayAnimation(uint32_t id, int a, int b);                           // 0xc12190
    bool  AnimationFinished(uint32_t id);                                     // 0xc123f0
    void* GetCurrentAnimationGUID();                                          // 0xc0e040
    void  FUN_00c159c0(float v, int b);                                       // 0xc159c0
};

template <class T> inline const T& mmax(const T& a, const T& b) { return a < b ? b : a; }
template <class T> inline const T& mmin(const T& a, const T& b) { return b < a ? b : a; }

// @ 0x00ec2130
char FUN_00ec2130(cSPCreatureBase* c, PickupTimer* t, float dt)
{
    if (t->active == 0) {
        t->time = t->time - dt;
        if (t->time < 0.0f) {
            void* a = FUN_00ec03c0(c);
            if (a) {
                t->active = 1;
                t->anim = ((cSPCreatureBase*)c)->InterruptAnimationWithTarget(0x26f1f86, a, -1, -1);
            }
            return (char)t->active;
        }
    }
    else {
        if (((cSPCreatureBase*)c)->AnimationFinished2(t->anim)) {
            t->active = 0;
            t->time = RandomFloatRange(1.0f, 2.0f);
        }
    }
    return (char)t->active;
}

// @ 0x00ec21c0
PickupTimer* __fastcall FUN_00ec21c0(PickupTimer* t)
{
    t->active = 1;
    t->time = 0.0f;
    t->anim = 0;
    _ReadWriteBarrier();
    t->b0c = 0;
    double r = RandomDoubleUniform((void*)0x1601760) + 1.0;
    if (r >= 2.0)
        r = 2.0;
    if (r < 1.0)
        r = 1.0;
    t->f10 = (float)r;
    t->i14 = 0;
    return t;
}

// @ 0x00ec2220
char FUN_00ec2220(cSPCreatureBase* c, int, int, int, int, PickupTimer* t)
{
    if (t != 0)
        FUN_00ec21c0(t);
    Loco* loco = &c->mLoco;
    loco->a_ec();
    return 1;
}

// @ 0x00ec1f80
bool FUN_00ec1f80(cSPCreatureBase* c)
{
    int n = c->FUN_00c0f4f0();
    for (int i = 0; i < n; i++) {
        SpatialObj* o = (SpatialObj*)c->FUN_00c0f8a0(i);
        if (!o)
            continue;
        int q = (int)o->QueryInterface(0x17f243b);
        if (!q)
            continue;
        if (FUN_00c7d090(q, (int*)c->mDecider)) {
            c->FUN_00c15bd0(i, 1, 0);
            return true;
        }
    }
    return false;
}

// @ 0x00ec1ff0
DeciderHeader* FUN_00ec1ff0(void* param_1, int* param_2)
{
    if ((*(uint32_t(__thiscall**)(void*))(*(uint32_t*)param_1 + 0x20))(param_1) != 0x18eb45e)
        return 0;

    int n = (param_2[1] - *param_2) >> 5;
    DeciderHeader* h = (DeciderHeader*)EAAllocate((n + 0xe) * 0x88, DAT_01488fa4, 0, 0, 0, 0);

    *(DeciderHeader*)h = DAT_015ab8f8;
    h->mCount = n + 0xd;
    h->mpEntries = (DeciderEntry*)(h + 1);

    DeciderEntry* e = (DeciderEntry*)(h + 1);
    for (int i = 0; i < 12; i++)
        e[i] = *(&DAT_015ab298 + i);

    int* src = (int*)*param_2;
    for (int i = 0; i < n; i++) {
        *e = *(&DAT_015aaaa0 + src[3]);
        e->mFlags10 = (uint32_t)(i << 16) | 1;
        if (src[0] == 6) {
            e->mDelay1c = (float)src[2] * DAT_013f9428;
            e->mFlag18 = 0;
        }
        src += 8;
        e++;
    }
    *e = DAT_015ab980;

    Grid_HasValidIndex(h);
    return h;
}

// @ 0x00ec1830
uint32_t FUN_00ec1830(cSPCreatureBase* c, int, uint32_t param_3, int, float param_5, PickupState* st)
{
    if (st->mpTarget == 0)
        return 0;

    {
        SpatialObj* ref = st->mpTarget;
        int q = (int)ref->QueryInterface(0x398420d);
        if (q != 0) {
            SpatialObj* linked = *(SpatialObj**)(q + 0x108);
            if (linked != 0 && linked != (SpatialObj*)c)
                return 0;
        }
    }

    SpatialObj* target = st->mpTarget;
    Vec3 P = g_zeroVec;
    Vec3 C = g_zeroVec;

    if (target == 0 || *(uint8_t*)((char*)target + 0x75) == 0)
        return 0;

    float radius = target->GetRadius();

    Box bb;
    const Box* b = target->GetBoundingBox(&bb);
    C.x = (b->lo.x + b->hi.x) * 0.5f;
    C.y = (b->lo.y + b->hi.y) * 0.5f;
    C.z = (b->lo.z + b->hi.z) * 0.5f;
    Vec3 Ccopy = C;

    const Vec3* tp = target->GetPosition();
    P.x = tp->x;
    P.y = tp->y;
    P.z = tp->z;

    const Vec3* lp = c->mLoco.GetPosition();
    float mag = sqrtf(lp->x * lp->x + lp->y * lp->y + lp->z * lp->z);
    float inv = 1.0f / sqrtf(P.x * P.x + P.y * P.y + P.z * P.z);
    P.x = (P.x * inv) * mag;
    P.y = (P.y * inv) * mag;
    P.z = (P.z * inv) * mag;

    switch (st->mState) {
    case 0: {
        float speed = c->mLoco.GetRadius() + radius;
        const Vec3* cp = c->mLoco.GetPosition();
        Vec3 d;
        d.x = P.x - cp->x;
        d.y = P.y - cp->y;
        d.z = P.z - cp->z;
        Vec3 out;
        Vec3* dir = normalized_safe(&out, &d, speed, speed);
        c->MoveToPointAndFacingAtSpeed(2, dir, &C, speed, speed);
        if (c->mLoco.IsNearGoal()) {
            C = g_zeroVec;
            float d2 = sqrtf(Ccopy.x * Ccopy.x + Ccopy.y * Ccopy.y + Ccopy.z * Ccopy.z);
            float vl = VectorLength(c->mLoco.GetPosition());
            float diff = d2 - vl;
            float ang = c->mLoco.GetFacingAngle() * DAT_013f08e4;
            if (ang < fabsf(diff)) {
                if (c->mLoco.FUN_00c1ac70(&Ccopy, (st->mbAlt ? 0xb : 0x0b) + (st->mbAlt ? 0 : 0), -1, 0, 0, 1000.0f) == 0) {
                    if (*(uint8_t*)((char*)c + 0x77) == 0 && (*(uint32_t*)((char*)c + 0x50) & 0x1000) == 0)
                        return 1;
                    return 0;
                }
            }
            st->mAnimId = (st->mbAlt ? 0x155929a : 0) + 0x39e4c3a;
            Ccopy = C;
            void* iface = InterfaceCast(&st->mpTarget);
            if (iface)
                ((InteractableObject*)iface)->mb71 = 1;
            st->mState = 1;
            void* animTarget = 0;
            if (c->mLoco.IsNearGoalVirtual() && (param_3 & 0x100000))
                animTarget = FUN_00d7d370(c, &Ccopy);
            if (Vector3_NotEqual(&Ccopy, &g_zeroVec))
                c->PlayAnimationWithTarget(st->mAnimId, &Ccopy, animTarget);
            if (st->mpTarget == 0) { }
            if (st->mAnimId != -1) {
                c->PlayAnimation(st->mAnimId, 1, -1);
                return 1;
            }
        }
        break;
    }
    case 1: {
        void* t15c = *(void**)((char*)c + 0xb54);
        int found = -1;
        uint32_t cnt = *(uint32_t*)((char*)t15c + 0x14c);
        for (uint32_t i = 0; i < cnt; i++) {
            int v = *(int*)((char*)t15c + 0x8c + i * 0xc);
            if (v == DAT_015aba20 || v == DAT_015aba1c) {
                found = *(int*)((char*)t15c + (i * 3 + 0x24) * 4);
                break;
            }
        }
        if (!c->AnimationFinished(st->mAnimId)) {
            void* iface = InterfaceCast(&st->mpTarget);
            if (iface) {
                FUN_00d7d4a0(iface, c);
                return 1;
            }
            break;
        }
        st->mState = 3;
        if (st->mpTarget == 0)
            return 0;
        param_5 = 0.0f;
        if (found != -1) {
            if (FUN_00c0f9b0(found, &param_5) != 0 && !FUN_00c0f510(param_5))
                param_5 = 0.0f;
        }
        c->FUN_00c159c0(param_5, 1);
        return 1;
    }
    case 2:
        if (c->AnimationFinished(st->mAnimId))
            return 0;
        if (c->GetCurrentAnimationGUID() != (void*)st->mAnimId)
            return 0;
        break;
    case 3:
        if (c->AnimationFinished(0))
            return 0;
        break;
    }
    return 1;
}

}   // namespace SP
