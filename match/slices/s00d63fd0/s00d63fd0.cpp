// Creature behavior-tree handlers (nSPBehaviorTree) at 0x00d63fd0..0x00d65250.
// The frozen batch lists this whole 4733-byte span as a single function, but it is four
// separate functions packed back to back (each ends in `ret` followed by padding and a jump
// table):  0x00d63fd0 (Tick, 4 states), 0x00d64200 (Tick, 5 states), 0x00d64a90 (Tick,
// 11 states, the avatar interaction) and 0x00d65150 (a one-arg cleanup/reset routine).
// The Tick functions have the PDB signature
//   bool Tick(void* creature, double, uint, uint, behavior_memory_block*, void*, float dt)
// All three read state from the memory block (first dword is the state index).
//
// Virtual calls are written through VT() because the vtable layouts are not reconstructed.
// Flags: default /O2-ish with /arch:SSE (movss for vector math, x87 for float returns).

#include <math.h>
#include <float.h>
typedef unsigned int uint32_t;

#define VT(o, off) ((*(void***)(o))[(off) / 4])
#define FIELD(T, o, off) (*(T*)((char*)(o) + (off)))

struct Vec3 { float x, y, z; };

struct Stimuli;
struct IdleAnim { uint32_t pad[3]; int id; };   // +0xc is the animation slot
struct Stimuli {
    IdleAnim* PlayIdleAnimation(int a, int b);           // 0x00bc96a0
    void ClearAll(int a, int b);                           // 0x00bc98f0
    void SetStimulus(int a, int b, float strength, int c); // 0x00bc97f0
};

struct Brain {
    char pad[0x1d8];
    uint32_t hash;                                 // +0x1d8
    Stimuli* Stim() { return (Stimuli*)((char*)this + 8); }
};

struct Loco {   // cLocomotiveObject sub-object at cSPCreatureBase+0xc0
    bool IsNearGoal();                                         // 0x00c42e20
    Vec3* GetPosition() { return ((Vec3*(__thiscall*)(Loco*))VT(this, 0x2c))(this); }
    float Slot74() { return ((float(__thiscall*)(Loco*))VT(this, 0x74))(this); }
    Vec3* GetDirection(Vec3* buf) { return ((Vec3*(__thiscall*)(Loco*, Vec3*))VT(this, 0x5c))(this, buf); }
    void Slot40(float f) { ((void(__thiscall*)(Loco*, float))VT(this, 0x40))(this, f); }
    bool Slot58() { return ((bool(__thiscall*)(Loco*))VT(this, 0x58))(this); }
    void SlotEC() { ((void(__thiscall*)(Loco*))VT(this, 0xec))(this); }
    void SlotDC(void* p) { ((void(__thiscall*)(Loco*, void*))VT(this, 0xdc))(this, p); }
};

struct cSPCreatureBase;
struct GroupData {                  // result of FUN_00c04590
    char pad0[0x104];
    int f104;
    char pad1[0x5c];
    cSPCreatureBase* f164;
};

struct cSPCreatureBase {
    Loco* L() { return (Loco*)((char*)this + 0xc0); }
    Brain* B() { return FIELD(Brain*, this, 0xb4c); }
    // non-virtual members
    bool AnimationFinished(int h);                              // 0x00c12400
    bool AnimationFinishedId(uint32_t id);                      // 0x00c123f0
    int PlayAnimation(uint32_t id, int a, int b);               // 0x00c12190
    int PlayAnimationWithTarget(uint32_t id, void* p, int x);   // 0x00c14910
    int StartAnimationAt(uint32_t id, void* p, int x);          // 0x00c14990
    uint32_t GetCurrentAnimationGUID();                         // 0x00c0e040
    bool FUN_00c0e070(int h);
    cSPCreatureBase* GetTargetAsCreature();                     // 0x00c0ee70
    void MoveToPointAtSpeed(int mode, Vec3* p, float speed, float arg);                    // 0x00c1c1d0
    void MoveToPointAndFacingAtSpeed(int mode, Vec3* p, Vec3* f, float speed, float arg);  // 0x00c1c5c0
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
    cSPCreatureBase* GetOwner();              // 0x00ff0420
};

struct TuningObj {
    uint32_t GetActive();                     // 0x004d3d40
    void* FUN_004d3d20();
};

struct ARef { cSPCreatureBase* p; ARef& operator=(cSPCreatureBase* x); };   // 0x00b5f950

struct Pred { bool Test(void* elem); };       // 0x00c02600
struct Iter {                                 // filter iterator over the group member list
    void** cur;
    void** end;
    Pred pred;
    Iter(void* container, char* tag);          // 0x00b41a40
    void Next();                               // 0x00b3d850
};
struct Elem { char pad[8]; void* obj; };

struct cPlanetModel {
    void MakeRandomWorldPosition(Vec3* out, Vec3* center, float r0, float r1);  // 0x00b81780
    bool FUN_00b7e3e0(Vec3* p);
    void FUN_00b81630(Vec3* out, Vec3* in);
    void FindClosestWater(Vec3* pos, float maxDist, Vec3* out);                 // 0x00b8bb70
    Vec3* DirectionToSurfacePosition(Vec3* out, Vec3* in);                      // 0x00b815a0
};
cPlanetModel* PlanetModel();                  // 0x00b3d350
struct cGameNounManager { cSPCreatureBase* GetAvatar(); };   // 0x00b1fdb0
cGameNounManager* NounManager();              // 0x00b3d300
struct RandomLC { uint32_t RandomUint32Uniform(uint32_t n); };   // 0x00a68fb0
extern RandomLC g_Random;                     // 0x01601760
struct PosseSim { void FUN_00d52e40(int a); };
PosseSim* cPosseSimulator_Instance();         // 0x00d539d0
Node* FUN_00d51660();
uint32_t* FUN_00d2e340();
void* cCreatureModeStrategy_Instance();       // 0x00d38840
void FUN_00d2e4a0(int a, int b);
struct Obj67c { void FUN_0067c830(void* p); };
Obj67c* FUN_0067cac0();
void FUN_00449c20(Vec3* out, Vec3* in);       // SP::normalized_safe (cdecl)
float FUN_00572a10(float lo, float hi);       // random float in range (cdecl)
cSPCreatureBase* interface_cast_Creature(void* p);   // 0x00ac8960 (cdecl)
Vec3* FUN_00c6acc0(GroupData* g);
void EASTL_dealloc(void* p);                  // 0x00f47380 (cdecl)

namespace nSPBehaviorTree { struct behavior_memory_block { int state; }; }
using nSPBehaviorTree::behavior_memory_block;

// ---------------------------------------------------------------------------------------------
// Memory block layouts (derived per handler)
struct MB1 : behavior_memory_block { int f04; int f08; int anim; };                       // 0x00d63fd0
struct MB2 : behavior_memory_block { float timer; int anim; ARef target; };               // 0x00d64200
struct MB3 : behavior_memory_block { int idx; int f08; int f0c; int anim; float timer; char flag; };  // 0x00d64a90

// @ 0x00d63fd0
// (caller-scored PDB candidate name: SP::BABY_DRINK_Tick)
bool BehaviorTick_00d63fd0(cSPCreatureBase* c, double d, unsigned a, unsigned b,
                           behavior_memory_block* mem, void* x, float dt)
{
    MB1* m = (MB1*)mem;
    Node* n = FUN_00d51660();
    if (!((n->flags >> 4) & 1))
        return false;
    cSPCreatureBase* owner = n->GetOwner();
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

// @ 0x00d64200
bool BehaviorTick_00d64200(cSPCreatureBase* c, double d, unsigned a, unsigned b,
                           behavior_memory_block* mem, void* x, float dt)
{
    MB2* m = (MB2*)mem;
    cSPCreatureBase* tgt = c->FUN_00c04590()->f164;
    if (!tgt)
        return false;
    if (tgt->B()->hash != 0x2d852f1)
        return false;
    if (c->B()->Stim()->PlayIdleAnimation(0, 0x2000)) {
        m->state = 3;
        return true;
    }
    Loco* loco = c->L();
    switch (m->state) {
    case 0: {
        if (!loco->IsNearGoal())
            return true;
        int r = (int)g_Random.RandomUint32Uniform(1000);
        if (r < 200 && c->FUN_00c04590()->f104 > 1) {
            char tag;
            Iter it(&FIELD(char, c, 0x1124), &tag);
            if (it.cur == it.end)
                return true;
            cSPCreatureBase* other;
            for (;;) {
                Elem* e = (Elem*)*it.cur;
                other = interface_cast_Creature(e->obj);
                if (other && other->FUN_00c04590() == c->FUN_00c04590() && !other->FUN_00c0b770()
                    && other->B()->hash == 0x510c229)
                    break;
                it.Next();
                if (it.cur == it.end)
                    return true;
            }
            m->target = other;
            cSPCreatureBase* P = m->target.p;
            void* mine = (char*)c + 0x5a8;
            int v = ((int(__thiscall*)(void*))VT(mine, 0xc))(mine);
            P->B()->Stim()->SetStimulus(0, 0x2000, 5.0f, v);
            P->V84(mine, 1, 0);
            c->V84((char*)other + 0x5a8, 1, 0);
            Loco* ol = other->L();
            Vec3 out;
            PlanetModel()->MakeRandomWorldPosition(&out, ol->GetPosition(), ol->Slot74(), ol->Slot74() * 1.5f);
            c->MoveToPointAtSpeed(2, &out, 1.0f, 2.0f);
            m->state = 4;
            return true;
        }
        if (r < 600 && PlanetModel()->FUN_00b7e3e0(loco->GetPosition())) {
            m->state = 1;
            float f = loco->Slot74();
            Vec3 buf;
            Vec3* dir = loco->GetDirection(&buf);
            Vec3 t;
            t.x = dir->x * f; t.y = dir->y * f; t.z = dir->z * f;
            Vec3* pos = loco->GetPosition();
            Vec3 q;
            q.x = pos->x + t.x; q.y = pos->y + t.y; q.z = pos->z + t.z;
            Vec3 out;
            PlanetModel()->FUN_00b81630(&out, &q);
            c->StartAnimationAt(0x27079bb, &out, -1);
            m->anim = c->PlayAnimationWithTarget(0x27079c1, &out, -1);
            return true;
        }
        m->state = 3;
        m->anim = c->PlayAnimation(0x55bd71b, 1, -1);
        return true;
    }
    case 1: {
        if (!c->AnimationFinishedId(0x27079bb))
            return true;
        m->state = 2;
        m->timer = FUN_00572a10(3.0f, 5.0f);
        if (c->GetCurrentAnimationGUID() == 0x27079c1)
            return true;
        float f = loco->Slot74();
        Vec3 buf;
        Vec3* dir = loco->GetDirection(&buf);
        Vec3 t;
        t.x = dir->x * f; t.y = dir->y * f; t.z = dir->z * f;
        Vec3* pos = loco->GetPosition();
        Vec3 q;
        q.x = pos->x + t.x; q.y = pos->y + t.y; q.z = pos->z + t.z;
        Vec3 out;
        PlanetModel()->FUN_00b81630(&out, &q);
        m->anim = c->PlayAnimationWithTarget(0x27079c1, &out, -1);
        return true;
    }
    case 2: {
        float tm = m->timer - dt;
        m->timer = tm;
        if (!(tm < 0.0f))
            return true;
        m->state = 3;
        float f = loco->Slot74();
        Vec3 buf;
        Vec3* dir = loco->GetDirection(&buf);
        Vec3 t;
        t.x = dir->x * f; t.y = dir->y * f; t.z = dir->z * f;
        Vec3* pos = loco->GetPosition();
        Vec3 q;
        q.x = pos->x + t.x; q.y = pos->y + t.y; q.z = pos->z + t.z;
        Vec3 out;
        PlanetModel()->FUN_00b81630(&out, &q);
        m->anim = c->PlayAnimationWithTarget(0x27079c3, &out, -1);
        return true;
    }
    case 3: {
        if (!c->AnimationFinished(m->anim))
            return true;
        m->state = 0;
        c->V84(0, 0, 0);
        Loco* tl = tgt->L();
        Vec3 rp;
        PlanetModel()->MakeRandomWorldPosition(&rp, tl->GetPosition(), tl->Slot74(), tl->Slot74() + 3.0f);
        Vec3 water = rp;
        PlanetModel()->FindClosestWater(&rp, 20.0f, &water);
        Vec3* pc = loco->GetPosition();
        Vec3 d3;
        d3.x = water.x - pc->x; d3.y = water.y - pc->y; d3.z = water.z - pc->z;
        Vec3 nd;
        FUN_00449c20(&nd, &d3);
        float f = loco->Slot74();
        Vec3 p2;
        p2.x = nd.x * f + water.x;
        p2.y = nd.y * f + water.y;
        p2.z = nd.z * f + water.z;
        Vec3 sp;
        Vec3* res = PlanetModel()->DirectionToSurfacePosition(&sp, &p2);
        Vec3 dest = *res;
        c->MoveToPointAtSpeed(2, &dest, 1.0f, 2.0f);
        c->FUN_00c14750(0);
        return true;
    }
    case 4: {
        if (loco->IsNearGoal()) {
            if (PlanetModel()->FUN_00b7e3e0(loco->GetPosition())) {
                cSPCreatureBase* T = m->target.p;
                m->anim = c->PlayAnimationWithTarget(0x510d6cd, T->L()->GetPosition(), -1);
                T = m->target.p;
                T->StartAnimationAt(0x55bd713, loco->GetPosition(), -1);
            }
            m->target.p->B()->Stim()->ClearAll(0, 0x2000);
            cSPCreatureBase* r = m->target.p;
            if (r) {
                m->target.p = 0;
                ((void(__thiscall*)(void*))VT(r, 4))(r);
            }
            m->state = 3;
            return true;
        }
        Loco* tl = m->target.p->L();
        Vec3 out;
        PlanetModel()->MakeRandomWorldPosition(&out, tl->GetPosition(), tl->Slot74(), tl->Slot74() * 1.5f);
        c->MoveToPointAtSpeed(2, &out, 1.0f, 2.0f);
        return true;
    }
    }
    return true;
}

// @ 0x00d64a90
bool BehaviorTick_00d64a90(cSPCreatureBase* c, double d, unsigned a, unsigned b,
                           behavior_memory_block* mem, void* x, float dt)
{
    MB3* m = (MB3*)mem;
    cSPCreatureBase* avatar = NounManager()->GetAvatar();
    Node* n = FUN_00d51660();
    if (!(((n->flags >> 4) & 1) && n->GetOwner() == c)) {
        // not yet in the interaction: walk toward a point near the avatar
        Vec3* pc = c->L()->GetPosition();
        Loco* al = avatar->L();
        Vec3* pa = al->GetPosition();
        Vec3 dv;
        dv.x = pa->x - pc->x; dv.y = pa->y - pc->y; dv.z = pa->z - pc->z;
        float inv = (float)(1.0 / sqrt(dv.x * dv.x + dv.y * dv.y + dv.z * dv.z + 1e-8f));
        Vec3 nv;
        nv.x = inv * dv.x; nv.y = dv.y * inv; nv.z = dv.z * inv;
        float f = al->Slot74();
        f = (f + f) + 3.0f;
        Vec3 off;
        off.x = nv.x * f; off.y = nv.y * f; off.z = nv.z * f;
        Vec3* ap = al->GetPosition();
        Vec3 p2;
        p2.x = ap->x - off.x; p2.y = ap->y - off.y; p2.z = ap->z - off.z;
        Vec3 sp;
        PlanetModel()->DirectionToSurfacePosition(&sp, &p2);
        c->MoveToPointAndFacingAtSpeed(2, &sp, &nv, 1.0f, 2.0f);
        m->state = 10;
    } else if ((unsigned)m->state > 10) {
        return true;
    }
    switch (m->state) {
    case 0:
        if (FIELD(char, avatar, 0x135) == 0)
            return true;
        if (avatar->B()->hash != 0x9413edeb)
            return true;
        m->f0c = avatar->PlayAnimation(0xf41bb04c, 1, -1);
        m->anim = c->PlayAnimation(0xb52c67f7, 1, -1);
        m->state = 2;
        return true;
    case 2:
        if (!avatar->FUN_00c0e070(m->f0c) && !avatar->AnimationFinished(m->f0c))
            return true;
        avatar->L()->Slot40(avatar->V80(0));
        m->state = 1;
        return true;
    case 1:
        if (!avatar->AnimationFinished(m->f0c))
            return true;
        if (!c->AnimationFinished(m->anim))
            return true;
        c->L()->SlotEC();
        m->anim = c->PlayAnimation(0x341b7a96, 1, -1);
        avatar->PlayAnimation(0x141b7a5c, 1, -1);
        m->state = 3;
        return true;
    case 3:
    case 7:
    case 8:
        if (c->AnimationFinished(m->anim)) {
            m->anim = 0;
            m->state = 4;
        }
        return true;
    case 4: {
        unsigned count = avatar->VB0();
        void* o = 0;
        for (; (unsigned)m->idx < count; m->idx++) {
            o = avatar->VB4(m->idx);
            if (o && FIELD(char, o, 0x115)) {
                uint32_t id = FIELD(uint32_t, o, 8);
                uint32_t* bits = (uint32_t*)((char*)FUN_00d2e340() + 0x38);
                if (id >= 0x58 || !(bits[id >> 5] & (1 << (id & 0x1f))))
                    goto found;
            }
        }
        if (m->state == 6)
            return true;
        m->anim = c->PlayAnimation(0x341b7a08, 1, -1);
        avatar->FUN_00c03190(0, 0x10, FLT_MAX, -1, 0, 0, 0);
        {
            char tag;
            Iter it(&FIELD(char, c, 0x1124), &tag);
            if (it.cur != it.end) {
                do {
                    Elem* e = (Elem*)*it.cur;
                    cSPCreatureBase* other = (cSPCreatureBase*)e->obj;
                    if (other->VD0() && !other->L()->Slot58()) {
                        other->B()->Stim()->SetStimulus(0, 0x10, 5.0f, 0);
                        other->B()->Stim()->PlayIdleAnimation(0, 0x10)->id = 0x341b7a08;
                    }
                    for (;;) {
                        ++it.cur;
                        if (it.cur == it.end)
                            goto done;
                        if (it.pred.Test(*it.cur))
                            break;
                    }
                } while (it.cur != it.end);
            }
        }
    done:
        m->state = 9;
        return true;
    found:
        {
            TuningObj* t = (TuningObj*)o;
            m->anim = c->PlayAnimation(t->GetActive(), 1, -1);
            void* r = t->FUN_004d3d20();
            if (r)
                FUN_0067cac0()->FUN_0067c830(r);
            cCreatureModeStrategy_Instance();
            FUN_00d2e4a0(FIELD(int, t, 0xc), 1);
            if (m->f08 != m->idx)
                m->f08 = m->idx;
            m->state = 6;
            return true;
        }
    }
    case 6:
        if (!c->AnimationFinished(m->anim))
            return true;
        m->anim = 0;
        m->state = 5;
        m->timer = 3.0f;
        m->flag = 0;
        return true;
    case 5: {
        m->timer = m->timer - dt;
        IdleAnim* r = c->B()->Stim()->PlayIdleAnimation(0, 0x10);
        if (r) {
            int v = r->id;
            if (v == m->idx) {
                m->anim = c->PlayAnimation(0xf41b7ae7, 1, -1);
                m->state = 7;
                if (m->f08 != -1)
                    m->f08 = -1;
                m->idx++;
            } else if (v == -1) {
                m->flag = 1;
            } else {
                m->anim = c->PlayAnimation(0xb41b7ade, 1, -1);
                m->state = 8;
            }
            c->B()->Stim()->ClearAll(0, 0x10);
            return true;
        }
        if (m->flag != 0)
            return true;
        if (!(m->timer <= 0.0f))
            return true;
        m->state = 4;
        return true;
    }
    case 9:
        if (c->AnimationFinished(m->anim)) {
            avatar->VE8(1);
            PosseSim* ps = cPosseSimulator_Instance();
            if (ps)
                ps->FUN_00d52e40(1);
            m->state = 10;
        }
        // fallthrough
    case 10: {
        Vec3* g = FUN_00c6acc0(avatar->FUN_00c04590());
        Vec3* ap = avatar->L()->GetPosition();
        float dz = ap->z - g->z;
        float dy = ap->y - g->y;
        float dx = ap->x - g->x;
        if (dz * dz + dy * dy + dx * dx > 25.0f)
            return false;
        if (avatar->GetTargetAsCreature() != c)
            return true;
        return false;
    }
    }
    return true;
}

// Per-creature parameter block handed to the locomotion object's vslot 0xdc (0x78 bytes).
struct MoveParams {
    void* data;            // heap array (freed with the header-count check below)
    int u1, u2, u3;        // +4..+0xc
    int pad10;
    float g0, g1, g2, h;   // +0x14..+0x20
    char pad24[4];
    int z28;               // +0x28
    char pad2c[0x24];
    char b50;              // +0x50
    char pad51[3];
    float zf0, zf1, zf2;   // +0x54..+0x5c
    int i60;               // +0x60
    float k64;             // +0x64
    char pad68[4];
    float big;             // +0x6c
    float zero70;          // +0x70
    int i74;               // +0x74
};
extern float g_Const169ec8c, g_Const169ec90, g_Const169ec94;   // a Vector3 constant in .data

// @ 0x00d65150
void ResetBehavior_00d65150(cSPCreatureBase* c)
{
    c->FUN_00c0ba10();
    MoveParams p;
    p.data = 0;
    p.u1 = 0; p.u2 = 0; p.u3 = 0;
    p.g0 = g_Const169ec8c;
    p.g1 = g_Const169ec90;
    p.g2 = g_Const169ec94;
    p.h = 1.0f;
    p.z28 = 0;
    p.b50 = 0;
    p.zf0 = 0.0f; p.zf1 = 0.0f; p.zf2 = 0.0f;
    p.i60 = 2;
    p.k64 = 0.9f;
    p.i60 = 0;
    p.big = FLT_MAX;
    p.zero70 = 0.0f;
    p.i74 = 0;
    c->L()->SlotDC(&p);
    if (p.data && ((int*)p.data)[-1] != 0)
        EASTL_dealloc(p.data);
    c->B()->Stim()->ClearAll(0, 0x10);
    c->FUN_00c0b370(-1);
}
