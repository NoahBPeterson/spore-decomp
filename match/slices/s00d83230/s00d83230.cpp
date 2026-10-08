// Slice s00d83230 (cl2 #373): 0x00d83370 SP::FIND_STUFF_Tick, a creature behavior-tree "tick" handler
// (cdecl, same shape as the handlers in s00d83a60):
//   bool Tick(Creature* c, void* a2, void* a3, unsigned flags, void* a5, State* st, void* a7, float dt)
// st->state: 0 start, 1/2 running (moving to the item), 3 done.
// Flags (match neighbour s00d83a60): /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct Vec3 { float x, y, z; };

#define AT(T, p, off) (*(T*)((char*)(p) + (off)))

struct PosHolder {                       // object with a vtable whose slot 0x2c returns a position
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vec3* GetPosition();         // 0x2c
};

struct Loco {                            // locomotion sub-object at creature + 0xc0
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vec3* GetPosition();         // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4();
    virtual bool vf8();                  // 0xf8
    bool IsNearGoal();                   // 0xc42e20
    struct GoalInfo* FUN_00c41ec0();     // 0xc41ec0
    Vec3* FUN_00c421f0();                // 0xc421f0
};

struct GoalInfo {
    char pad[0x5c];
    int f5c;
    Vec3* FUN_00c423c0();                // 0xc423c0
};

struct IdleNode {                        // result of PlayIdleAnimation
    char pad00[8];
    float f08;                           // +0x08
    char pad0c[0x2c - 0x0c];
    void* f2c;                           // +0x2c
};

struct Behaviors {                       // behavior tree at creature + 0xb4c (+ 8)
    IdleNode* PlayIdleAnimation(int a, int mask);               // 0xbc96a0
    void FUN_00bc97f0(int a, int b, float f, void* o);          // 0xbc97f0
    void ClearAll(int a, int mask);                             // 0xbc98f0
};
struct BTreePad8 { char pad[8]; };
struct BTree : BTreePad8, Behaviors {
    bool FUN_00bca2a0();                                        // 0xbca2a0 (called on creature+0xb4c)
    bool FUN_00bcb510(struct Creature* c, void* st, int z);     // 0xbcb510
};

struct CreatureBase;
struct Node1;
struct Creature {
    char pad00[0xc0];
    Loco loco;                           // +0xc0 (vptr only used)
    char pad04[0xb4c - 0xc0 - 4];
    BTree* mpBehavior;                   // +0xb4c
    char pad50[0xb5e - 0xb50];
    char b5e;                            // +0xb5e

    void SetStealthed(int a, int b);                            // 0xc1aed0
    void* FUN_00c04590();                                       // 0xc04590
    int FUN_00c0b750();                                         // 0xc0b750
    bool FUN_00c0b7c0(Creature* o);                             // 0xc0b7c0
    bool FUN_00c0c130();                                        // 0xc0c130
    void FUN_00c14750(int a);                                   // 0xc14750
    void FUN_00c122c0(unsigned id, float a, float b);           // 0xc122c0
    void InterruptAnimation(unsigned id, int a, int b);         // 0xc12310
    void MoveToPointAtSpeed(int mode, const Vec3* p, float speed, float f);   // 0xc1c1d0
};

struct Planet {
    Vec3* FUN_00b81630(Vec3* out, const Vec3* p);               // 0xb81630
};
Planet* __cdecl PlanetModel();                                  // 0xb3d350

struct Tgt {                             // behavior->+0x600 target record
    char pad[0x1a4];
    Vec3 dest;                           // +0x1a4
    bool FUN_00a75010();                                        // 0xa75010
    Creature* FUN_00bc9b10();                                   // 0xbc9b10
};

struct Item { char pad[0x34]; PosHolder h34; };

struct Node1 {                           // d998d0(r, 0x4f396a66)
    char pad[0x120];
    PosHolder h120;                      // +0x120
    char pad2[0x210 - 0x120 - sizeof(PosHolder)];
    Creature** begin;                    // +0x210
    Creature** end;                      // +0x214
    Vec3* FUN_00c91190(Vec3* tmp, int one);                     // 0xc91190
};

struct Node2 {                           // d998d0(r, 0x4ffcdeda)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool vcall2c();              // 0x2c
    char pad[0x34 - 4];
    PosHolder h34;                       // +0x34
};

struct MC { Vec3* FUN_00c6acc0(); };                            // 0xc6acc0

Creature* __cdecl WatchMemoryBlock(void* p);                    // 0xd999d0
void* __cdecl FUN_00d998d0(void* r, unsigned id);               // 0xd998d0
bool __cdecl FindForageDestination(Creature* c, Vec3* out);     // 0xd7cfb0
extern float kCreatureFoodSearchTravelDistance;                 // 0x1582e8c

struct State { int state; float timer; float radius; };

static inline float DistSqA(const Vec3* a, const Vec3* b) {
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;
    return dx * dx + dy * dy + dz * dz;
}
static inline float DistSq(const Vec3* a, const Vec3* b) {
    float dz = a->z - b->z;
    float dy = a->y - b->y;
    float dx = a->x - b->x;
    return dz * dz + dy * dy + dx * dx;
}

// @ 0x00d83370
bool __cdecl FIND_STUFF_Tick(Creature* c, void* a2, void* a3, unsigned flags, void* a5, State* st, void* a7, float dt)
{
    Tgt* tgt = AT(Tgt*, c->mpBehavior, 0x600);
    if (tgt == 0 || tgt->FUN_00a75010())
        return false;

    unsigned stealthFlag = flags & 0x10000;
    if (stealthFlag)
        c->SetStealthed(1, 1);

    Creature* other = tgt->FUN_00bc9b10();
    if (other != c) {
        Loco* loco = &c->loco;
        Vec3* pos = loco->GetPosition();
        Vec3* tpos = &tgt->dest;
        IdleNode* r = other->mpBehavior->PlayIdleAnimation(0x80000000, 0);
        if (r != 0) {
            Creature* w = WatchMemoryBlock(r);
            if (w != 0 && w->b5e == 0)
                c->mpBehavior->FUN_00bc97f0(0x80000000, 0, r->f08, r->f2c);
        }
        GoalInfo* gi = loco->FUN_00c41ec0();
        float r2 = st->radius * st->radius;
        Vec3* goal = pos;
        if (gi->f5c != 0)
            goal = gi->FUN_00c423c0();
        if (DistSqA(goal, tpos) > r2) {
            int mode = 2;
            int m = other->FUN_00c0b750();
            if (m != 0) mode = m;
            Vec3 tmp;
            c->MoveToPointAtSpeed(mode, PlanetModel()->FUN_00b81630(&tmp, tpos), st->radius, st->radius);
            if (!loco->vf8())
                c->FUN_00c14750(0);
            st->state = 2;
        } else if (loco->IsNearGoal() && st->state == 2) {
            c->FUN_00c122c0(0x715be665, 0.5f, 0.0f);
            st->state = 3;
        }
        return true;
    }

    if (st->state > 1)
        st->state = 0;
    BTree* bt = c->mpBehavior;
    if (!bt->FUN_00bca2a0() && bt->FUN_00bcb510(c, st, 0))
        return true;
    st->timer = st->timer - dt;
    if (st->state != 0)
        return true;

    Loco* loco = &c->loco;
    Vec3* pos = loco->GetPosition();
    float R = kCreatureFoodSearchTravelDistance;
    if (AT(float, c->FUN_00c04590(), 0x108) > 1.52587890625e-05f)
        R = AT(float, c->FUN_00c04590(), 0x108);
    R = R * R;
    bool found = false;
    bool nearGoal = loco->IsNearGoal();
    if (!nearGoal && (flags & 0x10))
        c->SetStealthed(1, 0);

    Vec3 dest;
    IdleNode* r = c->mpBehavior->PlayIdleAnimation(0x80000000, 0);
    if (r != 0) {
        Creature* w = WatchMemoryBlock(r);
        if (w != 0 && w->b5e == 0) {
            if (stealthFlag != 0 || R > DistSq(w->loco.GetPosition(), pos)) {
                dest = *w->loco.GetPosition();
                found = true;
                if (w->FUN_00c0c130())
                    dest = *((MC*)c->FUN_00c04590())->FUN_00c6acc0();
            }
        }
    }

    r = c->mpBehavior->PlayIdleAnimation(0, 0x100);
    if (r != 0) {
        Node1* n = (Node1*)FUN_00d998d0(r, 0x4f396a66);
        if (n != 0) {
            dest = *n->h120.GetPosition();
            Creature** it = n->begin;
            Creature** end = n->end;
            for (; it != end; ++it) {
                Item* item = (Item*)*it;
                if (c->FUN_00c0b7c0((Creature*)item)) {
                    dest = *item->h34.GetPosition();
                    goto have_dest;
                }
            }
            Vec3 tmp2;
            dest = *n->FUN_00c91190(&tmp2, 1);
        } else {
            Node2* n2 = (Node2*)FUN_00d998d0(r, 0x4ffcdeda);
            if (n2 == 0 || n2->vcall2c()) {
                c->mpBehavior->ClearAll(0, 0x100);
                return false;
            }
            dest = *n2->h34.GetPosition();
        }
    have_dest:
        found = true;
    }

    if (!nearGoal) {
        if (!found) return true;
    } else {
        st->timer = 30.0f;
        if (!found) {
            found = FindForageDestination(c, &dest);
            if (DistSq(&dest, c->loco.GetPosition()) < 1.0f || !found)
                dest = *((MC*)c->FUN_00c04590())->FUN_00c6acc0();
        }
    }

    tgt->dest = dest;
    bool far = nearGoal && DistSq(&dest, c->loco.GetPosition()) > 1.0f;
    if (!nearGoal) {
        float rad = st->radius;
        if (!(DistSq(loco->FUN_00c421f0(), &dest) > rad * rad))
            return true;
    } else if (!far) {
        return true;
    }
    c->MoveToPointAtSpeed(2, &dest, 1.0f, 2.0f);
    if (!c->loco.vf8())
        c->InterruptAnimation(0x2481de5, -1, 0);
    return true;
}
