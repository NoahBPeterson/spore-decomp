// Slice s00d63560: FUN_00d63560 -- herd "follow the leader" tick for a creature (tribe/herd member).
// The member walks behind the herd leader: while the leader moves it chases the creature in front of it
// in the herd list (or the leader itself) with a lookahead of the target's velocity; when the leader stands
// still it parks near the leader (behind it, in front of its facing). Writes the chosen move into
// the creature via MoveToPointAtSpeed / MoveToPointAndFacingAtSpeed and sets bit 0 of the goal's move flags.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

namespace SP {

struct Vec3 { float x, y, z; };

struct Goal {                       // returned by Loco::GetState (FUN_00c41ec0)
    uint32_t pad00[0x5c / 4];
    int      mHasPath;              // +0x5c
    uint32_t pad60[(0x70 - 0x60) / 4];
    uint32_t mMoveFlags;            // +0x70
};

// locomotive sub-object embedded in the creature at +0xc0 (own vtable)
class Loco {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual Vec3* GetPosition();                       // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual Vec3* GetFacing(Vec3* out);                // +0x5c
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
    virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
    virtual bool PrepareMove();                        // +0xf8

    const Vec3& GetVelocity();                         // 0x00d20610
    Goal* GetState();                                  // 0x00c41ec0
    Vec3* GetGoalPosition();                           // 0x00c421f0
};

class CreatureHead {                                   // bytes 0x00..0xbf of the creature
public:
    virtual void h00();
    uint32_t pad04[(0xc0 - 4) / 4];
};

struct Herd;

class cSPCreatureBase : public CreatureHead, public Loco {
public:
    Herd* GetHerd();                                   // 0x00c04590
    cSPCreatureBase* FUN_00c0ee90();                   // 0x00c0ee90 (thiscall, no args)
    void FUN_00c14750(int a);                          // 0x00c14750 (thiscall, ret 4)
    void MoveToPointAtSpeed(int mode, const Vec3* p, float s0, float s1);                        // 0x00c1c1d0
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* facing, float s0, float s1);   // 0x00c1c5c0

    uint32_t padc4[(0x330 - 0xc4) / 4];
    uint32_t mFlags330;
};

// herd member list: circular doubly linked list, sentinel at herd+0x168
struct ListNode {
    ListNode* mpNext;
    ListNode* mpPrev;
    cSPCreatureBase* mValue;
};
struct ListIter {
    ListNode* mpNode;
    ListIter() {}
    ListIter(ListNode* n) : mpNode(n) {}
    ListIter(const ListIter& x) : mpNode(x.mpNode) {}
};

struct Herd {
    uint32_t pad00[0x164 / 4];
    cSPCreatureBase* mpLeader;                         // +0x164
    ListNode mMembers;                                 // +0x168 (sentinel; mpNext = first)
};

struct FollowState {
    char mActive;                                      // +0
    char pad01[3];
    Vec3 mAnchor;                                      // +4
};

// callees
int   FUN_00d99500(cSPCreatureBase* c);                // cdecl
float FUN_00d99ac0(Loco* a, Loco* b, int flag);        // cdecl, x87 return
void  FindInList(ListIter* out, ListIter first, ListIter last, cSPCreatureBase* const* value);   // 0x00d61ce0 (cdecl)
Vec3* normalized_safe(Vec3* out, const Vec3* in);      // 0x00449c20 (cdecl)

class cPlanetModel {
public:
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* dir);   // 0x00b815a0
};
cPlanetModel* PlanetModel();                           // 0x00b3d350

extern float DAT_01582e04;                             // follow distance (10.0)

// @ 0x00D63560
bool FUN_00d63560(cSPCreatureBase* self, int, int, int, int, FollowState* st, int, float lookahead)
{
    cSPCreatureBase* me = self;
    Herd* herd = self->GetHerd();
    cSPCreatureBase* leader = herd->mpLeader;
    if (!FUN_00d99500(leader))
        return false;

    float dist = FUN_00d99ac0(leader, self, 1);
    Vec3* leaderPos = leader->GetPosition();
    const Vec3& lv = leader->GetVelocity();

    if (lv.x * lv.x + lv.y * lv.y + lv.z * lv.z > 0.1f && leader->FUN_00c0ee90() != self) {
        if (st->mActive == 0) {
            float dx = leaderPos->x - st->mAnchor.x;
            float dy = leaderPos->y - st->mAnchor.y;
            float dz = leaderPos->z - st->mAnchor.z;
            float distSq = dx * dx + dy * dy + dz * dz;
            float r = leader->GetRadius();
            if (!(distSq > r * r) && dist < DAT_01582e04)
                goto stopped;
        }
        {
            st->mActive = 1;
            if (!self->PrepareMove())
                self->FUN_00c14750(1);

            cSPCreatureBase* target = leader;
            ListNode* sentinel = &herd->mMembers;
            ListIter found;
            FindInList(&found, ListIter(sentinel->mpNext), ListIter(sentinel), &me);
            if (found.mpNode != sentinel && found.mpNode != sentinel->mpNext)
                target = found.mpNode->mpPrev->mValue;

            int mode = 2;
            if (FUN_00d99ac0(target, self, 1) >= DAT_01582e04)
                mode = 3;

            const Vec3& tv = target->GetVelocity();
            Vec3 off;
            off.x = tv.x * lookahead;
            off.y = tv.y * lookahead;
            off.z = tv.z * lookahead;
            Vec3* tp = target->GetPosition();
            Vec3 pred;
            pred.x = tp->x + off.x;
            pred.y = tp->y + off.y;
            pred.z = tp->z + off.z;
            Vec3 surf;
            PlanetModel()->DirectionToSurfacePosition(&surf, &pred);

            float radius = target->GetRadius();
            Vec3 res;
            if (target == leader) {
                float k = radius + radius;
                Vec3 tmp;
                Vec3* n = normalized_safe(&tmp, &target->GetVelocity());
                res.x = surf.x - n->x * k;
                res.y = surf.y - n->y * k;
                res.z = surf.z - n->z * k;
            } else {
                float k = radius;
                Vec3 tmp;
                Vec3* n = normalized_safe(&tmp, &target->GetVelocity());
                res.x = surf.x - n->x * k;
                res.y = surf.y - n->y * k;
                res.z = surf.z - n->z * k;
            }
            Vec3 buf;
            Vec3 dest = *PlanetModel()->DirectionToSurfacePosition(&buf, &res);
            self->MoveToPointAtSpeed(mode, &dest, 1.0f, 2.0f);
            goto done;
        }
    }

stopped:
    if (st->mActive == 0 && dist < DAT_01582e04) {
        if (self->GetState()->mHasPath != 0 && (self->mFlags330 & 1) == 0)
            return true;
        Vec3* lp = leader->GetPosition();
        Vec3* sp = self->GetPosition();
        Vec3 d;
        d.x = sp->x - lp->x;
        d.y = sp->y - lp->y;
        d.z = sp->z - lp->z;
        Vec3 fb;
        Vec3* f = leader->GetFacing(&fb);
        if (!(f->z * d.z + f->y * d.y + f->x * d.x > 0.0f))
            return true;
        if (leader->FUN_00c0ee90() == self)
            return true;
        st->mAnchor = *leader->GetPosition();
        if (!self->PrepareMove())
            self->FUN_00c14750(1);
        float lr = leader->GetRadius();
        float twoR = lr + lr;
        Vec3 fb2;
        Vec3* n = normalized_safe(&fb2, leader->GetFacing(&fb));
        Vec3 t0;
        t0.x = leaderPos->x - n->x * twoR;
        t0.y = leaderPos->y - n->y * twoR;
        t0.z = leaderPos->z - n->z * twoR;
        Vec3 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &t0);
        Vec3 fb3;
        self->MoveToPointAndFacingAtSpeed(2, &surf, leader->GetFacing(&fb3), 1.0f, 2.0f);
        goto done;
    }

    st->mActive = 0;
    {
        st->mAnchor = *leader->GetPosition();
        if (!self->PrepareMove())
            self->FUN_00c14750(1);
        int mode = 2;
        if (dist >= DAT_01582e04)
            mode = 3;
        float lr = leader->GetRadius();
        float twoR = lr + lr;
        Vec3 fb;
        Vec3* f = leader->GetFacing(&fb);
        float inv = 1.0f / sqrtf(f->x * f->x + f->y * f->y + f->z * f->z + 1e-8f);
        Vec3 t0;
        t0.x = leaderPos->x - f->x * inv * twoR;
        t0.y = leaderPos->y - f->y * inv * twoR;
        t0.z = leaderPos->z - f->z * inv * twoR;
        Vec3 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &t0);
        if (self->GetState()->mHasPath != 0) {
            Vec3* g = self->GetGoalPosition();
            float gx = g->x - surf.x;
            float gy = g->y - surf.y;
            float gz = g->z - surf.z;
            if (gz * gz + gy * gy + gx * gx <= DAT_01582e04 * DAT_01582e04)
                return true;
        }
        self->MoveToPointAtSpeed(mode, &surf, 1.0f, 2.0f);
    }
done:
    self->GetState()->mMoveFlags |= 1;
    return true;
}

}  // namespace SP
