// Slice s00d7f790 - SP::THROW_OBJECT_Tick (PDB candidate): the creature "throw object" action state
// machine.  Cdecl tick function of an action table entry (table at 0x1586e50); the last argument is
// the action's state block.  States: 0 = walk to the throw spot, 1 = wait until near the goal and
// play the throw animation, 2 = wait for the release event, apply the impulse, wait for the end.
// Layout notes: retail offsets come from the disassembly; stub classes carry only what is read.
#include "types.h"
#include <math.h>

namespace SP {

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct Box {
    Vec3 lo, hi;
};

// Pad-virtual helper: B's virtuals first, then N unnamed ones.
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

// Any spatial object (target of the throw): vslot 0x2c = position, 0x6c = bounding box, 0xb8 = QueryInterface.
struct SpatialObj0 {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10();
    virtual const Vec3* GetPosition();                      // 0x2c
};
struct SpatialObj1 : VPad<15, SpatialObj0> {
    virtual const Box* GetBoundingBox(Box* tmp);            // 0x6c
};
struct SpatialObj : VPad<18, SpatialObj1> {
    virtual void* QueryInterface(uint32_t id);              // 0xb8
};

// Object returned by the animation-handle cast (FUN_00d99a10); slot 2 = current target.
struct AnimTarget {
    virtual void a0(); virtual void a1();
    virtual SpatialObj* GetTarget();                        // 0x08
    uint8_t pad04[0x38 - 4];
    float   mWeight;                                        // +0x38
};

// Locomotive sub-object embedded at creature+0xc0 (its vptr is the first dword).
struct Loco0 {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10();
    virtual const Vec3* GetPosition();                      // 0x2c
};
struct Loco1 : VPad<11, Loco0> {
    virtual const Vec3* GetForward(Vec3* tmp);              // 0x5c
};
struct Loco2 : VPad<5, Loco1> {
    virtual float GetHeight();                              // 0x74
};
struct Loco : VPad<24, Loco2> {
    virtual float GetSpeed();                               // 0xd8
    bool IsNearGoal();                                      // 0xc42e20
    const Vec3* GetVelocity();                              // 0xd20610
};

struct AnimMgr {
    AnimTarget* PlayIdleAnimation(int a, int b);            // 0xbc96a0 (ret 8)
};
struct AnimOwner {
    uint8_t pad00[8];
    AnimMgr mgr;                                            // +8
};

struct InteractableSub {
    void Notify(void* timer);                               // 0xae6690 (ret 4)
};
struct cInteractableObject {
    uint8_t pad00[0x10c];
    InteractableSub mSub;                                   // +0x10c
};

struct cPlanetModel {
    void DirectionToSurfacePosition(Vec3* out, const Vec3* pos);    // 0xb815a0 (ret 8)
    float GetRadius();                                              // 0xb7e490
};

struct cImpulseSystem {                                             // singleton at 0xb3d310
    uint8_t pad00[0x20];
    int     mField20;                                               // +0x20
    void ApplyImpulse(SpatialObj* target, const Vec3* impulse, int flag);   // 0xb452f0 (ret 0xc)
    void Follow(Loco* loco, SpatialObj* target, float t);                   // 0xb4c600 (ret 0xc)
};

struct cSPCreatureBase {
    uint8_t     pad00[0xc0];
    Loco        mLoco;                                      // +0xc0
    uint8_t     pad_c4[0x137 - 0xc4];
    bool        mbCanMove;                                  // +0x137
    uint8_t     pad_138[0x5a8 - 0x138];
    uint32_t    mNoAttackTimer[4];                          // +0x5a8
    uint8_t     pad_5b8[0xb4c - 0x5b8];
    AnimOwner*  mpAnimOwner;                                // +0xb4c
    bool        IsCreature();                                               // 0xc0c0e0
    bool        WaitForAnimEventOrEnd(uint32_t ev, float* t, uint32_t anim, int a, int b);   // 0xc14ef0 (ret 0x14)
    void        FUN_00c15d50(SpatialObj* target, int a, int b);             // 0xc15d50 (ret 0xc)
    void        PlayAnimationWithTarget(uint32_t anim, const Vec3* pos, int arg);       // 0xc14910 (ret 0xc)
    void        MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing, float speed, float arg);   // 0xc1c5c0
    bool        AnimationFinished(uint32_t anim);                           // 0xc123f0
};

template <class T> struct AutoRefCount {
    T* mpObject;
};

// Action state block (last argument of the tick function).
struct ThrowState {
    int      mState;                                        // +0x00
    bool     mbDone;                                        // +0x04
    uint8_t  pad05[3];
    AutoRefCount<SpatialObj> mTarget;                       // +0x08
    bool     mbAlt;                                         // +0x0c
    uint8_t  pad0d[3];
    int      mArg;                                          // +0x10
};

extern Vec3     g_defaultThrowPos;                          // 0x169f03c
extern uint32_t g_throwEvent;                               // 0x1590c2c

cPlanetModel*   PlanetModel();                              // 0xb3d350
cImpulseSystem* GetImpulseSystem();                         // 0xb3d310
SpatialObj*     FUN_00d998d0(AnimTarget* h, uint32_t id);   // cdecl
AnimTarget*     FUN_00d99a10(AnimTarget* h);                // cdecl
void*           FUN_00ad2670(AutoRefCount<SpatialObj>* r);  // cdecl
void            FUN_00f20ba0(void* a, cSPCreatureBase* c);  // cdecl
cInteractableObject* InterfaceCast(AutoRefCount<SpatialObj>* r);   // 0xd7cf90 cdecl
void            ManageInteractiveOrnamentEventSFX(void* iface, cSPCreatureBase* c);   // 0xd7d4a0
Vec3*           normalized_safe(Vec3* out, const Vec3* in); // 0x449c20 cdecl
float           VectorLength(const Vec3* v);                // 0x40ae50 cdecl

template <class T> inline const T& max(const T& a, const T& b) { return a < b ? b : a; }
template <class T> inline const T& min(const T& a, const T& b) { return b < a ? b : a; }

inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

inline uint32_t ThrowAnimID(const ThrowState* st)
{
    return (st->mbAlt ? 0x1485642 : 0) + 0x3ab8894;
}

// @ 0x00d7f790
bool THROW_OBJECT_Tick(cSPCreatureBase* c, int, int, int, int, ThrowState* st)
{
    AnimTarget* idle = c->mpAnimOwner->mgr.PlayIdleAnimation(0, 0x40000);
    AutoRefCount<SpatialObj>* ref = &st->mTarget;
    if (!ref->mpObject)
        return false;

    SpatialObj* cast = 0;
    if (idle)
        cast = FUN_00d998d0(idle, 0x1186577);
    Vec3 pos = g_defaultThrowPos;

    if (cast && cast != ref->mpObject) {
        Box tmp;
        const Box* b = cast->GetBoundingBox(&tmp);
        Vec3 center((b->lo.x + b->hi.x) * 0.5f, (b->hi.y + b->lo.y) * 0.5f, (b->hi.z + b->lo.z) * 0.5f);
        pos = center;
    }
    else {
        bool found = false;
        if (c->IsCreature()) {
            AnimTarget* h2 = c->mpAnimOwner->mgr.PlayIdleAnimation(0x400, 0);
            if (h2) {
                AnimTarget* at = FUN_00d99a10(h2);
                if (at && at->mWeight > 0.0f) {
                    SpatialObj* cur = ref->mpObject;
                    if (cur != at->GetTarget()) {
                        const Vec3* p = at->GetTarget()->GetPosition();
                        pos.x = p->x;
                        pos.y = p->y;
                        pos.z = p->z;
                        found = true;
                    }
                }
            }
        }
        if (!found) {
            Loco* L = &c->mLoco;
            float h = L->GetHeight() + 50.0f;
            Vec3 ftmp;
            const Vec3* f = L->GetForward(&ftmp);
            float inv = 1.0f / sqrtf(f->x * f->x + f->y * f->y + f->z * f->z + 1e-8f);
            Vec3 off((inv * f->x) * h, (inv * f->y) * h, (inv * f->z) * h);
            const Vec3* lp = L->GetPosition();
            pos = Vec3(lp->x + off.x, lp->y + off.y, lp->z + off.z);
        }
    }

    switch (st->mState) {
    case 0:
        if (c->mbCanMove) {
            const Vec3* lp = c->mLoco.GetPosition();
            Vec3 cp(lp->x, lp->y, lp->z);
            Vec3 surf;
            PlanetModel()->DirectionToSurfacePosition(&surf, &pos);
            Vec3 d(surf.x - cp.x, surf.y - cp.y, surf.z - cp.z);
            Vec3 n;
            normalized_safe(&n, &d);
            Vec3 p2(n.x + cp.x, n.y + cp.y, n.z + cp.z);
            c->MoveToPointAndFacingAtSpeed(2, &p2, &n, 1.0f, 2.0f);
            st->mState = 1;
        }
        break;
    case 1:
        if (c->mLoco.IsNearGoal()) {
            c->PlayAnimationWithTarget(ThrowAnimID(st), &pos, st->mArg);
            st->mState = 2;
            return true;
        }
        break;
    case 2: {
        float evt;
        bool released = c->WaitForAnimEventOrEnd(g_throwEvent, &evt, ThrowAnimID(st), 0, 1);
        if (!st->mbDone && released) {
            FUN_00f20ba0(FUN_00ad2670(ref), c);
            c->FUN_00c15d50(ref->mpObject, 0, 0);
            cInteractableObject* io = InterfaceCast(ref);
            if (io)
                io->mSub.Notify(&c->mNoAttackTimer);
            float radius = PlanetModel()->GetRadius();
            Loco* L = &c->mLoco;
            float v = L->GetSpeed() * 0.05f;
            v = max(v, 10.0f);
            if (c->IsCreature()) {
                v = min(v, 20.0f);
            }
            else if (GetImpulseSystem()->mField20 == 0) {
                v = Clamp(v, 10.0f, 30.0f);
            }
            Box tmp1;
            const Box* b1 = ref->mpObject->GetBoundingBox(&tmp1);
            Vec3 c1((b1->lo.x + b1->hi.x) * 0.5f, (b1->hi.y + b1->lo.y) * 0.5f, (b1->hi.z + b1->lo.z) * 0.5f);
            Vec3 d(pos.x - c1.x, pos.y - c1.y, pos.z - c1.z);
            float len = sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
            float f = 1.0f / (len + 1.5258789e-05f);
            Vec3 dir(d.x * f, d.y * f, d.z * f);
            float speed = VectorLength(L->GetVelocity()) + v;
            float t = -(len / v * 0.5f * radius);
            float h = min(t, v);
            Box tmp2;
            const Box* b2 = ref->mpObject->GetBoundingBox(&tmp2);
            Vec3 c2((b2->lo.x + b2->hi.x) * 0.5f, (b2->hi.y + b2->lo.y) * 0.5f, (b2->hi.z + b2->lo.z) * 0.5f);
            Vec3 n2;
            const Vec3* nn = normalized_safe(&n2, &c2);
            Vec3 impulse(dir.x * speed + nn->x * h, dir.y * speed + nn->y * h, dir.z * speed + nn->z * h);
            GetImpulseSystem()->ApplyImpulse(ref->mpObject, &impulse, 1);
            GetImpulseSystem()->Follow(L, ref->mpObject, 0.5f);
            st->mbDone = true;
        }
        else {
            SpatialObj* t = ref->mpObject;
            if (t) {
                void* iface = t->QueryInterface(0x398420d);
                if (iface)
                    ManageInteractiveOrnamentEventSFX(iface, c);
            }
        }
        if (c->AnimationFinished(ThrowAnimID(st)))
            return false;
        break;
    }
    }
    return true;
}

} // namespace SP
