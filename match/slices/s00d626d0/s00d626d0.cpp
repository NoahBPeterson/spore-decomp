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
    uint32_t* FUN_00c41ec0();                          // 0x00c41ec0, pointer to a state word (+0x70 used)
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
    PV8 PV8 PV8 PV8 PV                                 // 0x00 .. 0x80
    virtual void SetFocusObject(void* p, int a, int b);   // +0x84
    uint32_t padc4[(0xc0 - 4) / 4];
    Loco mLoco;                                        // +0xc0
    uint8_t padc4_5a8[0x5a8 - 0xc4];                   // +0xc4
    uint32_t mFocus5a8;                                // +0x5a8, sub-object handed to SetFocusObject
    uint8_t pad5ac_b58[0xb58 - 0x5ac];                 // +0x5ac
    uint32_t mB58;                                     // +0xb58

    cSPCreatureBase* GetTargetAsCreature();            // 0x00c0ee70
    bool FUN_00c0e0c0(int id);                         // ret 4
    int PlayAnimation(int id, int a, int b);           // 0x00c12190 (ret 12)
    void MoveToPointAtSpeed(int a, const Vec3* p, float s0, float s1);   // 0x00c1c1d0 (ret 16)
    void MoveToPointAndFacingAtSpeed(int a, const Vec3* p, const Vec3* facing,
                                     float s0, float s1);                // 0x00c1c5c0 (ret 20)
    void FUN_00c0b370(uint32_t state);                 // 0x00c0b370, 1 stack arg
    void FUN_00c0b970(float v);                        // 0x00c0b970, 1 float stack arg
    HomeInfo* FUN_00c04590();                          // helper object
};

// ---- behaviour plumbing (learn / baby behaviours) ----
struct BehaviourState                                 // 0x1c bytes, passed as the last tick argument
{
    int   mState;                                      // +0x00
    int   mValue04;                                    // +0x04
    int   mValue08;                                    // +0x08
    int   mAnimationId;                                // +0x0c
    int   mValue10;                                    // +0x10
    float mTimer;                                      // +0x14
    bool  mFlag;                                       // +0x18
};

struct cGameNounManager {
    cSPCreatureBase* GetAvatar();                      // 0x00b1fdb0
};
cGameNounManager* NounManager();                       // 0x00b3d300

class cUIHints {
public:
    void UpdateHints(bool a, bool b);                  // 0x0067c350 (ret 8)
};
cUIHints* FUN_0067cac0();                              // 0x0067cac0

// The learnables context the action reads its focus creature from.
class cSPLearnContext {
public:
    cSPCreatureBase* GetFocusCreature();               // 0x00ff0420
};
cSPLearnContext* FUN_00d51660();                       // 0x00d51660

bool FUN_00d62d90(cSPCreatureBase* self, int, int, int, int, BehaviourState* st);          // 0x00d62d90
bool LEARN_ABILITIES_Activate(cSPCreatureBase* self, int, int, int, BehaviourState* st);   // 0x00d62f60
bool BABY_IDLE_Tick(cSPCreatureBase* self, int, int, int, int, BehaviourState* st);        // 0x00d630c0

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

namespace {
// d / |d| with the +1e-8 guard of the engine's vector helpers (x87, as in the original).
__forceinline void Normalize(Vec3& out, const Vec3& d)
{
    // component order and the +1e-8 guard as in the engine's inline vector helper
    float inv = 1.0f / sqrtf(d.y * d.y + d.x * d.x + d.z * d.z + 1e-8f);
    out.x = d.x * inv;
    out.y = d.y * inv;
    out.z = d.z * inv;
}
}

// Learns-by-watching behaviour: walk to a point `reach` in front of the avatar, facing the avatar,
// flag the locomotive object, then reset the behaviour state and refresh the UI hints.
// @ 0x00d62d90
bool SP::FUN_00d62d90(cSPCreatureBase* self, int, int, int, int, BehaviourState* st)
{
    cSPCreatureBase* avatar = NounManager()->GetAvatar();

    Vec3* pSelf = self->mLoco.GetPosition();
    Vec3* pAvatar = avatar->mLoco.GetPosition();
    Vec3 d; SubTo(d, pAvatar, pSelf);
    Vec3 dir;
    Normalize(dir, d);

    float reach = self->mLoco.GetFootprintRadius() * 2.0f + 0.5f;
    Vec3 off(dir.x * reach, dir.y * reach, dir.z * reach);

    Vec3* pa = avatar->mLoco.GetPosition();
    Vec3 target(pa->x - off.x, pa->y - off.y, pa->z - off.z);
    Vec3 surf;
    PlanetModel()->DirectionToSurfacePosition(&surf, &target);
    self->MoveToPointAndFacingAtSpeed(2, &surf, &dir, 1.0f, 2.0f);

    uint32_t* pFlags = self->mLoco.FUN_00c41ec0();
    *pFlags |= 2;

    self->FUN_00c0b370(0x341b7b33);

    st->mState = 0;
    st->mValue04 = 0;
    st->mValue08 = -1;
    st->mValue10 = 0;
    st->mAnimationId = 0;
    st->mTimer = 0.0f;
    st->mFlag = false;

    FUN_0067cac0()->UpdateHints(false, true);
    return true;
}

// Learn-abilities activation: turn towards the focused creature and start the "listening" animation
// when the ability-learned flag of the creature is set.
// @ 0x00d62f60
bool SP::LEARN_ABILITIES_Activate(cSPCreatureBase* self, int, int, int, BehaviourState* st)
{
    cSPCreatureBase* focus = FUN_00d51660()->GetFocusCreature();
    if (focus == 0)
        return false;

    st->mAnimationId = 0;
    st->mValue04 = 0;
    self->FUN_00c0b370(0xf4165aa3);

    Vec3* pSelf = self->mLoco.GetPosition();
    Vec3* pFocus = focus->mLoco.GetPosition();
    Vec3 d; SubTo(d, pFocus, pSelf);
    Vec3 dir;
    Normalize(dir, d);
    self->MoveToPointAndFacingAtSpeed(2, self->mLoco.GetPosition(), &dir, 1.0f, 2.0f);

    if (((self->mB58 >> 8) & 1) != 0)
    {
        st->mAnimationId = self->PlayAnimation(0xf41bb04c, 1, -1);
        st->mState = 1;
    }
    else
        st->mState = 2;

    self->FUN_00c0b970(0.0f);
    return true;
}

// Baby idle tick: the avatar is handed to the creature as its focus object, then it either wanders to a
// random point around the avatar (far away) or stands a little in front of it (near), and the state is reset.
// @ 0x00d630c0
bool SP::BABY_IDLE_Tick(cSPCreatureBase* self, int, int, int, int, BehaviourState* st)
{
    cSPCreatureBase* avatar = NounManager()->GetAvatar();
    self->SetFocusObject(avatar != 0 ? &avatar->mFocus5a8 : 0, 1, 0);
    self->FUN_00c0b370(0x341b7b33);

    Vec3* pSelf = self->mLoco.GetPosition();
    Vec3* pAvatar = avatar->mLoco.GetPosition();
    Vec3 d; SubTo(d, pAvatar, pSelf);
    float dist2 = d.y * d.y + d.x * d.x + d.z * d.z;
    float reach = self->mLoco.GetFootprintRadius() * 2.0f + 5.0f;

    if (dist2 > 100.0f)
    {
        // far: pick a point 2*radius+5..2*radius+5 around the avatar and face away from it
        Vec3 rand;
        PlanetModel()->MakeRandomWorldPosition(&rand, pAvatar, reach, reach);
        Vec3* pa = avatar->mLoco.GetPosition();
        Vec3 dr; SubTo(dr, pa, &rand);
        Vec3 dir;
        Normalize(dir, dr);
        self->MoveToPointAndFacingAtSpeed(2, &rand, &dir, 1.0f, 2.0f);
    }
    else
    {
        // near: stand `reach` in front of the avatar on the surface, facing the avatar
        float inv = 1.0f / dist2;
        Vec3 off(d.x * inv * reach, d.y * inv * reach, d.z * inv * reach);
        Vec3* pa = avatar->mLoco.GetPosition();
        Vec3 target(pa->x - off.x, pa->y - off.y, pa->z - off.z);
        Vec3 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &target);
        Vec3 dir;
        Normalize(dir, d);
        self->MoveToPointAndFacingAtSpeed(2, &surf, &dir, 1.0f, 2.0f);
    }

    st->mState = 0;
    return true;
}
