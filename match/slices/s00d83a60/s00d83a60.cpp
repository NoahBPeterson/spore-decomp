// Creature behavior callbacks (behavior-tree "tick" handlers, 0xd83a60..0xd84c49). Ghidra lumps the whole run
// into one 4585-byte "function"; it is really nine separate cdecl functions with the shape
//   bool Tick(Creature* c, void* a2, void* a3, void* a4, void* a5, State* st [, float dt])
// that drive a small per-handler state machine (st->state: 0 start, 1 running, 2 done, 3 failed).
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };
inline bool TestBit(unsigned v, unsigned n) { return (v >> n) & 1; }

#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
#define VT(p) (*(void***)(p))

typedef float (__thiscall* FnF0)(void*);
typedef void* (__thiscall* FnP0)(void*);
typedef void (__thiscall* FnV0)(void*);
typedef void (__thiscall* FnV2)(void*, void*, void*);
typedef unsigned (__thiscall* FnU0)(void*);

// Result of PlayIdleAnimation (a behavior-tree node record).
struct IdleNode {
    char pad00[0xc];
    int kind;                 // +0x0c (also read as a float radius by one handler)
    Vec3 pt;                  // +0x10
    void* hasPt;              // +0x1c
};

struct BTreePad8 { char pad[8]; };
struct Behaviors {            // behavior tree at creature + 0xb4c (+ 8)
    IdleNode* PlayIdleAnimation(int a, int mask);          // 0xbc96a0
    IdleNode* FUN_00bc97f0(int a, int b, float f, void* o);  // 0xbc97f0
    void ClearAll(int a, int mask);                        // 0xbc98f0
};
struct BTree : BTreePad8, Behaviors {};

struct Loco {                 // locomotion sub-object at creature + 0xc0 (has its own vtable)
    void** vt;
    bool IsNearGoal();        // 0xc42e20
};

struct Creature;
struct Planet {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* p);   // 0xb815a0
    void* BuildSurfaceOrientation(void* out, const Vec3* p);      // 0xb7f190
    bool FUN_00b7e3e0(const Vec3* p);                             // 0xb7e3e0
    bool FUN_00b88770(const Vec3* p, float f, Vec3* out, float one, int a, int b);   // 0xb88770
};

struct Manager {              // FUN_00b3d4d0() result
    char pad00[0x28];
    char b28;
    char b29;
    char pad2a[2];
    int f2c;
    bool FUN_00adb360(void* loco);                        // 0xadb360
};

struct Rng { unsigned RandomUint(unsigned n); };            // EA::Random::RandomLinearCongruential
extern Rng g_Rng;                                           // 0x1601760

struct Sub120 { bool FUN_00bfc480(); };
struct Obj1 { void FUN_00bcf490(unsigned v); void FUN_00bcda90(); void FUN_00ca04a0(); bool FUN_00c9ef20(); void FUN_00ca4320(unsigned v); };
struct Noun { void FUN_00b225d0(); };

struct Creature {
    char pad00[0xc0];
    Loco loco;                // +0xc0
    char pad04[0xb4c - 0xc0 - sizeof(Loco)];
    BTree* mpBehavior;        // +0xb4c

    void PlayAnimation(unsigned id, int a, int b);                         // 0xc12190
    bool AnimationFinished(unsigned id);                                   // 0xc123f0
    bool AnimationFinished2(int handle);                                   // 0xc12400
    int FUN_00c0f570();                                                    // 0xc0f570
    int FUN_00c0f8f0(int id);                                              // 0xc0f8f0
    bool FUN_00c0e0c0(unsigned id);                                        // 0xc0e0c0
    bool WaitForAnimEventOrEnd(int g, void* pc, unsigned id, int a, int b);  // 0xc14ef0
    int PlayAnimationWithTarget(unsigned id, void* center, int handle);    // 0xc14910
    int PlayAnimationWithTarget2(unsigned id, void* tgt, int a, int b);    // 0xc14940
    void MoveToPointAtSpeed(int mode, const Vec3* p, float speed, float f);        // 0xc1c1d0
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* d, float speed, float f);  // 0xc1c5c0
    bool FUN_00c15d50(void* p, int a, int b);                              // 0xc15d50
    void FUN_00c19940(int a);                                              // 0xc19940
    void FUN_00c15150(unsigned id, int a);                                 // 0xc15150
    bool FUN_00c159c0(void* p, int a, int b);                              // 0xc159c0
    void FUN_00c14750(int a);                                              // 0xc14750
    void* FUN_00c04590();                                                  // 0xc04590
    void SetStealthed(int a, int b);                                       // 0xc1aed0
    Creature* GetTargetAsCreature();                                       // 0xc0ee70
    bool FUN_00c0d560(void* obj, float a, float b);                        // 0xc0d560
    bool FUN_00c0b7a0();                                                   // 0xc0b7a0
};

unsigned __cdecl GetCurrentGameMode();
Planet* __cdecl PlanetModel();
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);
Manager* __cdecl FUN_00b3d4d0();
extern Vec3 g_DefaultPoint;                                 // 0x169f03c
extern int g_Handle1590c34;                                 // 0x1590c34
extern int g_Handle1590c38;                                 // 0x1590c38
extern void* g_Game;                                        // 0x16c7aa4

struct MC { Vec3* FUN_00c6acc0(); };

void* __cdecl FUN_00ad2670(void* p);
void* __cdecl FUN_00ac80d0(void* o, unsigned id);
Obj1* __cdecl FUN_00cb4610(void* p);
Obj1* __cdecl FUN_00bd8440(void* p);
unsigned __cdecl FUN_00ebfdc0(void* c);
Noun* __cdecl NounManager(void* v);
float __cdecl FUN_00d38a30(int k, void* c);
void* __cdecl FUN_00d99470(void* c);
float __cdecl FUN_00572a10(float lo, float hi);

struct GameAsset { void FUN_00f1aff0(void* a, void* b); };   // 0xf1aff0

// ---------------------------------------------------------------------------------------------------
struct S1 { int state; int target; };
struct Rec36 { unsigned v[9]; };

// @ 0x00d83a60
bool __cdecl OFFER_ITEM_Tick(Creature* c, void* a2, void* a3, void* a4, void* a5, S1* st)
{
    IdleNode* r = c->mpBehavior->PlayIdleAnimation(0, 0x40000);
    if (r != 0 && st->target != 0 && r->kind == 1) {
        switch (st->state) {
        case 0:
            if (c->FUN_00c0f570() == 0) {
                st->state = 3;
                return false;
            } else {
                unsigned f = (unsigned)-1;
                int idx = c->FUN_00c0f8f0(st->target);
                if (idx != -1)
                    f = AT(unsigned, AT(void*, c, 0xe40), idx * 0x24);
                c->PlayAnimation(0x3a8a036, 1, f);
                st->state = 1;
                return true;
            }
        case 1:
            if (c->FUN_00c0f570() == 0 || !c->FUN_00c0e0c0(0x3a8a036))
                st->state = 3;
            if (c->AnimationFinished(0x3a8a036))
                st->state = 2;
            return true;
        case 2:
            return false;
        case 3:
            return false;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------------------------------
struct CRef { Creature* p; };
struct S2 { int state; char done; char pad5[3]; void* handle; };

// @ 0x00d83b40
bool __cdecl Tick_AnimEvent(CRef h, void* a2, void* a3, void* a4, void* a5, S2* st)
{
    switch (st->state) {
    case 0: {
        Creature* c = h.p;
        if (c->FUN_00c0f570() == 0 && (AT(unsigned, c, 0xb58) & 8) == 0) {
            st->state = 3;
            return false;
        }
        c->PlayAnimation(0x3a74a08, 1, -1);
        st->state = 1;
        return true;
    }
    case 1: {
        Creature* c = h.p;
        bool ev = c->WaitForAnimEventOrEnd(g_Handle1590c34, &h, 0x3a74a08, 0, 1);
        if (st->done == 0 && ev) {
            if (st->handle != 0) {
                c->FUN_00c15d50(st->handle, 0, 0);
            } else {
                c->FUN_00c19940(0);
                if (AT(unsigned, c, 0xb58) & 8) {
                    c->FUN_00c15150(0x3a78161, 1);
                    AT(unsigned, c, 0xb58) &= ~8u;
                }
            }
            st->done = 1;
        }
        if (c->AnimationFinished(0x3a74a08))
            st->state = (st->done == 0) + 2;
        return true;
    }
    case 2:
        return false;
    case 3:
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------------
struct S3 {
    int state;                // +0x00
    float timer;              // +0x04
    float timer2;             // +0x08
    char pad0c[0xc];
    Creature* tgt;            // +0x18
    void* tgtObj;             // +0x1c
    bool flag;                // +0x20
    char pad21[3];
    int arg;                  // +0x24
    int handle;               // +0x28
};

// @ 0x00d83c30
bool __cdecl Tick_Approach(Creature* c, void* a2, void* a3, void* a4, void* a5, S3* st, float dt)
{
    IdleNode* r = c->mpBehavior->PlayIdleAnimation(0, 0x40000);
    if (r == 0) return false;
    Creature* g = st->tgt;
    if (g == 0) return false;
    if (st->tgtObj == 0) return false;
    if (r->kind != 6) return false;

    float lim = 20.0f;
    bool bb = (AT(unsigned, g, 0xb58) >> 9) & 1;
    if (GetCurrentGameMode() == 0x1654c10) {
        lim = 5.0f;
        bb = false;
    }
    if (st->timer > lim && st->state != 2) {
        if (bb) {
            st->state = 3;
        } else {
            void* x = AT(void*, g, 0xb4c);
            if (x != 0 && AT(int, x, 0x1d8) != 0x39f8e85)
                st->state = 3;
        }
    }
    int s = st->state;
    st->timer = st->timer + dt;

    switch (s) {
    case 0: {
        if (c->FUN_00c0f8f0((int)st->tgtObj) == -1) {
            st->state = 3;
            return false;
        }
        Loco* loco = &c->loco;
        if (!loco->IsNearGoal())
            return true;
        ((FnV0)VT(loco)[59])(loco);
        Loco* tl = &st->tgt->loco;
        ((FnP0)VT(loco)[11])(loco);
        ((FnP0)VT(tl)[11])(tl);
        ((FnP0)VT(loco)[26])(loco);
        float box[6];
        float* bx = (float*)((void* (__thiscall*)(void*, float*))VT(&st->tgt->loco)[27])(&st->tgt->loco, box);
        Vec3 center;
        center.x = (bx[0] + bx[3]) * 0.5f;
        center.y = (bx[4] + bx[1]) * 0.5f;
        center.z = (bx[5] + bx[2]) * 0.5f;
        unsigned id = st->flag ? 0x4f7caa9 : 0x39e4c65;
        st->handle = c->PlayAnimationWithTarget(id, &center, st->arg);
        st->state = 1;
        return true;
    }
    case 1: {
        if (c->FUN_00c0f8f0((int)st->tgtObj) == -1)
            st->state = 2;
        else if (st->timer2 > 15.0f)
            st->state = 3;
        if (c->AnimationFinished2(st->handle)) {
            unsigned id = st->flag ? 0x4f7caaa : 0x39e4c68;
            if (!c->FUN_00c0e0c0(id)) {
                float box[6];
                float* bx = (float*)((void* (__thiscall*)(void*, float*))VT(&st->tgt->loco)[27])(&st->tgt->loco, box);
                Vec3 center;
                center.x = (bx[3] + bx[0]) * 0.5f;
                center.y = (bx[4] + bx[1]) * 0.5f;
                center.z = (bx[5] + bx[2]) * 0.5f;
                st->handle = c->PlayAnimationWithTarget(id, &center, st->arg);
            }
        }
        st->timer2 = st->timer2 + dt;
        return true;
    }
    case 2:
        return false;
    case 3:
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------------
// @ 0x00d83f10
bool __cdecl Tick_Interact(Creature* c, void* a2, void* a3, void* a4, void* a5, S3* st, float dt)
{
    IdleNode* r = c->mpBehavior->PlayIdleAnimation(0, 0x40000);
    if (r == 0) return false;
    if (st->tgt == 0) return false;
    if (st->tgtObj == 0) return false;
    if (r->kind != 6) return false;

    int s = st->state;
    st->timer = st->timer + dt;

    switch (s) {
    case 0: {
        if (c->FUN_00c0f8f0((int)st->tgtObj) == -1) {
            st->state = 3;
            return false;
        }
        Loco* loco = &c->loco;
        if (!loco->IsNearGoal())
            return true;
        ((FnV0)VT(loco)[59])(loco);
        ((FnP0)VT(loco)[11])(loco);
        Creature* t = st->tgt;
        ((FnP0)VT(t)[11])(t);
        ((FnP0)VT(loco)[26])(loco);
        float box[6];
        float* bx = (float*)((void* (__thiscall*)(void*, float*))VT(st->tgt)[27])(st->tgt, box);
        Vec3 center;
        center.x = bx[0] + bx[3];
        center.y = bx[4] + bx[1];
        center.z = bx[5] + bx[2];
        unsigned id = st->flag ? 0x4f7caa9 : 0x39e4c65;
        center.x *= 0.5f;
        center.y *= 0.5f;
        center.z *= 0.5f;
        st->handle = c->PlayAnimationWithTarget(id, &center, st->arg);
        st->state = 1;
        Obj1* p = FUN_00cb4610(&st->tgt);
        if (p) p->FUN_00bcda90();
        Obj1* q = FUN_00bd8440(&st->tgt);
        if (q) q->FUN_00ca04a0();
        return true;
    }
    case 1: {
        if (c->AnimationFinished2(st->handle)) {
            void* v = FUN_00ad2670(&st->tgtObj);
            Obj1* r1 = FUN_00cb4610(&st->tgt);
            Obj1* r2 = FUN_00bd8440(&st->tgt);
            if (r1) {
                c->FUN_00c15d50(st->tgtObj, 1, 0);
                if (((Sub120*)((char*)r1 + 0x120))->FUN_00bfc480()) {
                    if (GetCurrentGameMode() == 0x1654c10)
                        ((GameAsset*)AT(void*, g_Game, 0x78))->FUN_00f1aff0(r1, v);
                    NounManager(v)->FUN_00b225d0();
                    st->state = 2;
                } else {
                    r1->FUN_00bcf490((unsigned)v);
                    st->state = 2;
                }
            } else if (r2 != 0) {
                c->FUN_00c15d50(st->tgtObj, 1, 0);
                if (r2->FUN_00c9ef20()) {
                    NounManager(v)->FUN_00b225d0();
                    st->state = 2;
                } else {
                    r2->FUN_00ca4320((unsigned)v);
                    st->state = 2;
                }
            } else {
                st->state = 3;
            }
        }
        st->timer2 = st->timer2 + dt;
        return true;
    }
    case 2:
        return false;
    case 3:
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------------
struct S5 {
    int state;                // +0x00
    Vec3 pt;                  // +0x04
    float timer;              // +0x10
    char done;                // +0x14
    char pad15[3];
    Creature* tgt;            // +0x18
    Creature* tgtObj;         // +0x1c
    bool flag;                // +0x20
    char pad21[3];
    int handle;               // +0x24
};

// @ 0x00d841a0
bool __cdecl Tick_Chase(Creature* c, void* a2, void* a3, void* a4, void* a5, S5* st, float dt)
{
    IdleNode* r = c->mpBehavior->PlayIdleAnimation(0, 0x40000);
    if (r == 0) return false;
    Creature* g = st->tgt;
    if (g == 0) return false;
    if (st->tgtObj == 0) return false;
    if (r->kind != 7) return false;

    float tm = st->timer;
    if (tm > 0.0f && st->state != 2) {
        void* x = AT(void*, g, 0xb4c);
        if (x != 0 && AT(int, x, 0x1d8) != 0x39f6486)
            st->state = 3;
    }
    int s = st->state;
    st->timer = tm + dt;

    switch (s) {
    case 0: {
        Loco* loco = &c->loco;
        if (loco->IsNearGoal()) {
            unsigned id = st->flag ? 0x4f7caf0 : 0x39e4c77;
            st->handle = c->PlayAnimationWithTarget2(id, st->tgtObj, -1, -1);
            st->state = 1;
            return true;
        }
        Vec3* p = (Vec3*)((FnP0)VT(st->tgtObj)[11])(st->tgtObj);
        Vec3 tmp;
        Vec3* d = PlanetModel()->DirectionToSurfacePosition(&tmp, p);
        st->pt = *d;
        Creature* tg = st->tgt;
        Loco* tl = &tg->loco;
        float r1 = ((FnF0)VT(loco)[29])(loco) * 0.3f;
        float r2 = ((FnF0)VT(loco)[29])(loco) + r1;
        float rr = ((FnF0)VT(tl)[29])(tl) + r2;
        Vec3* me = (Vec3*)((FnP0)VT(loco)[11])(loco);
        Vec3 diff;
        diff.x = st->pt.x - me->x;
        diff.y = st->pt.y - me->y;
        diff.z = st->pt.z - me->z;
        Vec3 nrm;
        c->MoveToPointAndFacingAtSpeed(2, &st->pt, normalized_safe(&nrm, &diff), rr, 2.0f);
        return true;
    }
    case 1: {
        unsigned id = st->flag ? 0x4f7caf0 : 0x39e4c77;
        bool ev = c->WaitForAnimEventOrEnd(g_Handle1590c38, &c, id, 0, 1);
        if (st->done == 0) {
            if (ev || c->AnimationFinished2(st->handle)) {
                if (st->tgt->FUN_00c15d50(st->tgtObj, 0, 0)) {
                    if (c->FUN_00c159c0(st->tgtObj, 0, 1))
                        st->done = 1;
                }
            }
        }
        if (st->done != 0) {
            st->state = 2;
            return true;
        }
        if (c->AnimationFinished2(st->handle))
            st->state = 3;
        return true;
    }
    case 2: {
        if (!c->AnimationFinished2(st->handle))
            return true;
        if ((AT(unsigned, c, 0xb58) >> 9) & 1)
            return false;
        void* v = FUN_00ad2670(&st->tgtObj);
        void* o = FUN_00ac80d0(v, 0x2c9cc91);
        if (o != 0) {
            bool k = c->FUN_00c0b7a0();
            if (k) {
                c->mpBehavior->FUN_00bc97f0(1, 0, 60.0f, o);
                return false;
            }
            c->mpBehavior->FUN_00bc97f0(0, 0x8000, 60.0f, 0);
            return false;
        }
        if (((FnU0)VT(v)[8])(v) == 0x2a8fb3f) {
            c->mpBehavior->FUN_00bc97f0(0, 0x8000, 60.0f, 0);
            return false;
        }
        unsigned t = ((FnU0)VT(v)[8])(v);
        if (t != 0x3a2511e)
            return false;
        void* o2 = FUN_00ac80d0(v, t);
        if (o2 == 0)
            return false;
        if (AT(int, o2, 0x110) != 3) {
            c->mpBehavior->FUN_00bc97f0(0, 0x8000, 60.0f, 0);
            return false;
        }
        IdleNode* n = c->mpBehavior->FUN_00bc97f0(0, 0x40000, 60.0f, 0);
        if (n != 0)
            n->kind = 1;
        return false;
    }
    case 3:
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------------
// @ 0x00d84520
bool __cdecl Tick_Stealth(Creature* c)
{
    if (!FUN_00b3d4d0()->FUN_00adb360(c ? (void*)&c->loco : 0)) {
        if (GetCurrentGameMode() == 0x1654c10) {
            unsigned fl = AT(unsigned, c, 0xb58);
            if (TestBit(fl, 8)) {
                void* game = AT(void*, g_Game, 0x78);
                int mode = AT(int, game, 0x90);
                if (mode == 5) {
                    c->PlayAnimation(0x7ba46b7, 1, -1);
                    return true;
                }
                if (mode == 6)
                    return true;
                if (AT(int, game, 0xb0) == 0)
                    c->PlayAnimation(0x7b66a9b, 1, -1);
                else
                    c->PlayAnimation(0x7ba46be, 1, -1);
                return true;
            }
            if (!TestBit(fl, 9)) {
                c->PlayAnimation(FUN_00ebfdc0(c), 1, -1);
                return true;
            }
        } else {
            ((FnV0)VT(&c->loco)[59])(&c->loco);
        }
        c->FUN_00c14750(0);
        return true;
    }
    c->SetStealthed(0, 0);
    return true;
}

// ---------------------------------------------------------------------------------------------------
// @ 0x00d84610
bool __cdecl Tick_Wander(Creature* c)
{
    Manager* m = FUN_00b3d4d0();
    int sv = m->f2c;
    Loco* loco = &c->loco;
    bool run = true;
    void* locoArg = c ? (void*)&c->loco : 0;
    if (!m->FUN_00adb360(locoArg)) {
        IdleNode* r = c->mpBehavior->PlayIdleAnimation(0, 0x2000000);
        Planet* pm = PlanetModel();
        if (r != 0 && c->FUN_00c04590() != 0 && pm != 0) {
            float rad = *(float*)&r->kind;
            Vec3 tgt = r->pt;
            bool hasPt = r->hasPt != 0;
            Vec3* me = ((MC*)c->FUN_00c04590())->FUN_00c6acc0();
            float dx = me->x - tgt.x;
            float dz = me->z - tgt.z;
            float dy = me->y - tgt.y;
            float dist = (float)sqrt((double)(dx * dx + dz * dz + dy * dy));
            if (dist > rad) {
                if (hasPt) {
                    char out[0x10];
                    void* P = pm->BuildSurfaceOrientation(out, me);
                    ((FnV2)VT(loco)[17])(loco, (void*)me, P);
                    ((FnV0)VT(loco)[59])(loco);
                } else {
                    c->MoveToPointAtSpeed(2, me, 1.0f, 2.0f);
                }
            } else {
                if (!(1.52587890625e-05f < dist)) {
                    Vec3* p = (Vec3*)((FnP0)VT(loco)[11])(loco);
                    dx = p->x - tgt.x;
                    dz = p->z - tgt.z;
                    dy = p->y - tgt.y;
                    dist = (float)sqrt((double)(dx * dx + dz * dz + dy * dy));
                }
                float inv = 1.0f / (dist + 9.99999993922529e-09f);
                Vec3 dir;
                dir.y = dy * inv;
                dir.z = dz * inv;
                dir.x = inv * dx;
                Vec3 cand = g_DefaultPoint;
                int i = 0;
                for (;;) {
                    switch (i) {
                    case 0:
                        cand.x = dir.x * rad + tgt.x;
                        cand.y = dir.y * rad + tgt.y;
                        cand.z = dir.z * rad + tgt.z;
                        break;
                    case 1:
                        cand.x = -dir.x * rad + tgt.x;
                        cand.y = -dir.y * rad + tgt.y;
                        cand.z = -dir.z * rad + tgt.z;
                        break;
                    case 2: {
                        float cx = dir.y * tgt.z - dir.z * tgt.y;
                        float cy = dir.z * tgt.x - tgt.z * dir.x;
                        float cz = tgt.y * dir.x - dir.y * tgt.x;
                        cand.x = cx * rad + tgt.x;
                        cand.y = cy * rad + tgt.y;
                        cand.z = cz * rad + tgt.z;
                        break;
                    }
                    case 3: {
                        float cx = dir.y * tgt.z - dir.z * tgt.y;
                        float cy = dir.z * tgt.x - tgt.z * dir.x;
                        float cz = tgt.y * dir.x - dir.y * tgt.x;
                        cand.x = -cx * rad + tgt.x;
                        cand.y = -cy * rad + tgt.y;
                        cand.z = -cz * rad + tgt.z;
                        break;
                    }
                    }
                    if (!pm->FUN_00b7e3e0(&cand))
                        break;
                    Vec3 out2;
                    if (pm->FUN_00b88770(&cand, 10.0f, &out2, 1.0f, 0, 0)) {
                        cand = out2;
                        break;
                    }
                    if (++i >= 4)
                        break;
                }
                if (i >= 4) {
                    Vec3* p = (Vec3*)((FnP0)VT(loco)[11])(loco);
                    cand = *p;
                }
                Vec3 tmp;
                Vec3* d = pm->DirectionToSurfacePosition(&tmp, &cand);
                cand = *d;
                if (hasPt) {
                    char out[0x10];
                    void* P = pm->BuildSurfaceOrientation(out, &cand);
                    ((FnV2)VT(loco)[17])(loco, &cand, P);
                    ((FnV0)VT(loco)[59])(loco);
                } else {
                    c->MoveToPointAtSpeed(2, &cand, 1.0f, 2.0f);
                }
            }
            c->mpBehavior->ClearAll(0, 0x2000000);
            c->FUN_00c14750(0);
        }
    }
    bool two = sv == 2;
    if (GetCurrentGameMode() == 0x1654c10) {
        if (!two && sv != 1)
            return false;
    } else if (!two) {
        return false;
    }
    if (m->b28 != 0)
        return false;
    if (m->b29 != 0 && ((AT(unsigned, c, 0xb58) >> 9) & 1))
        return false;
    return true;
}

// ---------------------------------------------------------------------------------------------------
struct S8 { float timer; int anim; };

// @ 0x00d84b30
bool __cdecl Tick_Look(Creature* c, void* a2, void* a3, void* a4, void* a5, S8* st, float dt)
{
    float a = FUN_00d38a30(1, c);
    float b = FUN_00d38a30(2, c);
    Creature* obj = (Creature*)FUN_00d99470(c->GetTargetAsCreature());
    if (obj == 0)
        return false;
    if (!c->FUN_00c0d560(obj, a, 0.0f)) {
        typedef bool (__thiscall* FnB3)(void*, void*, float, float);
        if (!((FnB3)VT(c)[48])(c, obj, b, 0.0f))
            return false;
    }
    if ((st->anim == 0 && c->AnimationFinished(0)) || c->AnimationFinished(st->anim)) {
        float v = st->timer - dt;
        st->timer = v;
        if (0.0f > v) {
            int n;
            do {
                n = g_Rng.RandomUint(3) + 0x404fc23;
            } while (n == st->anim);
            c->PlayAnimationWithTarget2(n, &obj->loco, -1, -1);
            st->timer = FUN_00572a10(1.0f, 2.0f);
            st->anim = n;
        }
    }
    return true;
}
