// Slice s00d626d0 -- SP::BABY_FLEE_Tick (0x00d626d0, 1725 bytes, /O2 /arch:SSE /fp:fast, __cdecl, returns bool).
//
// Per-tick behaviour of a baby creature fleeing from a threat (the tick of the "baby flee" behaviour node).
// The third state word *st drives a tiny state machine:
//   0 waiting until the creature has reached its goal, then run away from the threat and the parent,
//   1 running; once the threat is nearer than the parent (distance to threat > distance to parent)
//     go to state 2,
//   2 hide next to the parent: stand `len` metres behind the parent (opposite its facing).
// The parent ("owner") is FUN_00d99500(FUN_00c04590()->m164); no parent means the tick fails.
// Callee conventions were taken from the call sites: PlanetModel() takes no argument (the pushed
// pointers belong to the DirectionToSurfacePosition / MakeRandomWorldPosition that follow it).
// In states 0 and 1 the original passes the surface position (not the random one) to MoveToPointAtSpeed
// and drops the MakeRandomWorldPosition result; state 2 passes the random point.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

namespace SP {

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };

struct Loco {                                          // sub-object at creature+0xc0 (own vtable)
    PV8 PV2 PV                                         // 0x00 .. 0x28
    virtual Vec3* GetPosition();                       // +0x2c
    PV8 PV2 PV                                         // 0x30 .. 0x58
    virtual Vec3* GetDirection(Vec3* out);             // +0x5c
    PV4 PV                                             // 0x60 .. 0x70
    virtual float GetFootprintRadius();                // +0x74
    bool IsNearGoal();                                 // 0x00c42e20
};

struct HomeInfo {                                      // FUN_00c04590() result
    uint32_t pad[0x104 / 4];
    int m104;                                          // +0x104
    uint32_t pad108[(0x164 - 0x108) / 4];
    void* m164;                                        // +0x164
    void** M164() { return &m164; }
};

class cSPCreatureBase {
public:
    PV PV PV PV
    uint32_t padc4[(0xc0 - 4) / 4];
    Loco mLoco;                                        // +0xc0

    cSPCreatureBase* GetTargetAsCreature();            // 0x00c0ee70
    bool FUN_00c0e0c0(int id);                         // ret 4
    int PlayAnimation(int id, int a, int b);           // 0x00c12190 (ret 12)
    void MoveToPointAtSpeed(int a, const Vec3* p, float s0, float s1);   // 0x00c1c1d0 (ret 16)
    HomeInfo* FUN_00c04590();                          // helper object
};

class cPlanetModel {
public:
    void DirectionToSurfacePosition(Vec3* out, const Vec3* in);          // 0x00b815a0, ret 8
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* center, float minR, float maxR);   // 0x00b81780, ret 16
};

bool BABY_FLEE_Tick(cSPCreatureBase* self, int, int, int, int, int* st);

cSPCreatureBase* FUN_00d99500(void* p);                         // parent lookup
int FUN_00d99470(cSPCreatureBase* c);
float FUN_00d99a60(Vec3* a, float ra, Vec3* b, float rb, bool clamp);   // DistanceBetweenBodies
cPlanetModel* PlanetModel();                                    // 0x00b3d350
Vec3* normalized_safe(Vec3* out, const Vec3* in);               // 0x00449c20

}  // namespace SP

using namespace SP;

namespace {
__forceinline void SubTo(Vec3& d, const Vec3* a, const Vec3* b)
{
    d.x = a->x - b->x; d.y = a->y - b->y; d.z = a->z - b->z;
}

// Direction away from the threat and the parent, 15 m from the creature, run to there.
__forceinline void RunAway(cSPCreatureBase* self, cSPCreatureBase* parent, cSPCreatureBase* threat)
{
    Vec3 n1, n2;
    Vec3* a = self->mLoco.GetPosition();
    Vec3* b = parent->mLoco.GetPosition();
    Vec3 d1; SubTo(d1, b, a);
    normalized_safe(&n1, &d1);
    Vec3* c = threat->mLoco.GetPosition();
    Vec3* e = self->mLoco.GetPosition();
    Vec3 d2; SubTo(d2, e, c);
    normalized_safe(&n2, &d2);
    Vec3 sum(n1.x + n2.x, n1.y + n2.y, n1.z + n2.z);
    Vec3 n3;
    Vec3* dp = normalized_safe(&n3, &sum);
    Vec3 step(dp->x * 15.0f, dp->y * 15.0f, dp->z * 15.0f);
    Vec3* p = self->mLoco.GetPosition();
    Vec3 want(step.x + p->x, p->y + step.y, p->z + step.z);
    Vec3 surf, rnd;
    PlanetModel()->DirectionToSurfacePosition(&surf, &want);
    PlanetModel()->MakeRandomWorldPosition(&rnd, &surf, 0.1f, 3.0f);
    self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
}
}

// @ 0x00d626d0
bool SP::BABY_FLEE_Tick(cSPCreatureBase* self, int, int, int, int, int* st)
{
    cSPCreatureBase* parent = FUN_00d99500(*self->FUN_00c04590()->M164());
    if (!parent)
        return false;
    if (*st == 2 && self->mLoco.IsNearGoal())
        return false;

    cSPCreatureBase* threat = self->GetTargetAsCreature();
    if (!FUN_00d99470(threat))
        *st = 2;
    if (!self->FUN_00c0e0c0(0x566b36b))
        self->PlayAnimation(0x566b36b, 1, -1);

    switch (*st) {
    case 0:
        if (self->mLoco.IsNearGoal()) {
            RunAway(self, parent, threat);
            *st = 1;
        }
        break;
    case 1: {
        float dThreat = FUN_00d99a60(self->mLoco.GetPosition(), self->mLoco.GetFootprintRadius(),
                                     threat->mLoco.GetPosition(), threat->mLoco.GetFootprintRadius(), true);
        float dParent = FUN_00d99a60(self->mLoco.GetPosition(), self->mLoco.GetFootprintRadius(),
                                     parent->mLoco.GetPosition(), parent->mLoco.GetFootprintRadius(), true);
        RunAway(self, parent, threat);
        if (dThreat > dParent) {
            *st = 2;
            return true;
        }
        break;
    }
    case 2: {
        float r = self->mLoco.GetFootprintRadius() * 1.25f;
        float len = sqrtf(r * ((float)self->FUN_00c04590()->m104 * r));
        float r2 = parent->mLoco.GetFootprintRadius() + len;
        Vec3 dirTmp, nd;
        Vec3* dir = normalized_safe(&nd, parent->mLoco.GetDirection(&dirTmp));
        Vec3 off(r2 * dir->x, r2 * dir->y, r2 * dir->z);
        Vec3 want; SubTo(want, parent->mLoco.GetPosition(), &off);
        Vec3 surf, rnd;
        PlanetModel()->DirectionToSurfacePosition(&surf, &want);
        PlanetModel()->MakeRandomWorldPosition(&rnd, &surf, 0.0f, len);
        self->MoveToPointAtSpeed(2, &rnd, 1.0f, 2.0f);
        return true;
    }
    }
    return true;
}
