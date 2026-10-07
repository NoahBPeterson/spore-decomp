// Slice s00d824a0 -- SP::POSSE_IDLE_Tick (0x00d824a0), behavior-tree tick of a creature that is a member
// of the avatar's posse while it idles (creature / space-creature game).
//
// While the avatar moves (and the creature was already following, or the avatar moved more than
// sqrt(3) from the last recorded spot, or the creature is far behind), the creature follows: it picks a
// point beside/behind the avatar (perpendicular to its velocity, on the side away from the creature),
// snaps it to the planet surface and walks/hovers/jumps there. Otherwise it settles: it re-registers
// with the posse simulator and walks to its slot (or behind the avatar), and once arrived plays idle
// animations.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (same module as the other SP::*_Tick behaviors).
#include "types.h"
#include <math.h>

namespace SP {

struct Vec3 { float x, y, z; };

// Clamp to [lo, hi]: the original uses the SSE maxss/minss helper.
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

// EASTL min (returns a reference).
static inline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }

// Movement / steering state of a locomotive object (cLocomotiveObject 0xc41ec0 result).
struct LocoState {
    char pad00[0x5c];
    int  mHasPath;                                     // +0x5c
    const Vec3* GetGoal();                             // 0xc423c0
};

// Spatial/locomotive sub-object of a creature (at +0xc0), own vtable.
struct Loco {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual const Vec3* GetPosition();                 // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual const Vec3* GetFacing(Vec3* out);          // +0x5c
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
    virtual bool SlotF8();                             // +0xf8
    const Vec3& GetVelocity();                         // cLocomotiveObject::GetVelocity 0xd20610
    LocoState* GetState();                             // 0xc41ec0
    bool IsNearGoal();                                 // cLocomotiveObject::IsNearGoal 0xc42e20
};

struct Sub5a8 { float FUN_00bfc490(); };              // 0xbfc490

struct CreatureTuning {                                // creature + 0xb20
    char  pad00[0x54c];
    float mHoverSpeed;                                 // +0x54c
    char  pad550[0x61c - 0x550];
    uint32_t mCanHover;                                // +0x61c
};

struct cSPCreatureBase {
    char      pad00[0xc0];
    Loco      mLoco;                                   // +0xc0
    char      padC4[0x110 - 0xc4];
    uint32_t  mFlags;                                  // +0x110
    char      pad114[0x137 - 0x114];
    bool      mbFlying;                                // +0x137
    char      pad138[0x5a8 - 0x138];
    Sub5a8    m5a8;                                    // +0x5a8
    char      pad5a9[0xb20 - 0x5a9];
    CreatureTuning* mpTuning;                          // +0xb20

    int  FUN_00c029b0();                                                  // 0xc029b0
    int  FUN_00c0b750();                                                  // 0xc0b750
    int  PlayAnimation(uint32_t id, int a, int b);                        // 0xc12190
    void InterruptAnimation(uint32_t id, int a, int b);                   // 0xc12310
    bool AnimationFinished(uint32_t id);                                  // 0xc123f0
    bool AnimationFinished(int handle);                                   // 0xc12400
    void Hover(bool b);                                                   // 0xc13a30
    void FUN_00c14750(bool b);                                            // 0xc14750
    void TryJumpToTarget(int a, const Vec3* p, const Vec3* d, float f, int b);  // 0xc190e0
    void MoveToPointAtSpeed(int mode, const Vec3* p, float speed, float f);     // 0xc1c1d0
};

struct cGameNounManager { cSPCreatureBase* GetAvatar(); };   // 0xb1fdb0
struct cPlanetModel {
    float GetRadiusAt(const Vec3* p);                            // 0xb7ef70
    const Vec3* FUN_00b82b40(Vec3* out, const Vec3* p, int a);   // 0xb82b40 (surface snap)
};
struct cPosseSimulator {
    static cPosseSimulator* Instance();                          // 0xd539d0
    void* FUN_00d53b50(cSPCreatureBase* c, Vec3* outPos);         // 0xd53b50
};

void* __cdecl GetCurrentGameMode();                              // 0xb5b800
cGameNounManager* __cdecl NounManager();                         // 0xb3d300
cPlanetModel* __cdecl PlanetModel();                             // 0xb3d350
float __cdecl FUN_00d99ac0(Loco* a, Loco* b, bool c);           // 0xd99ac0
float __cdecl FUN_00c29530(const Vec3* p, const Vec3* v, float s);   // 0xc29530

extern char g_GameModeCreature;                                  // 0x1654c10
extern float g_PosseFollowDist;                                  // 0x1582e04
extern float g_PosseMaxFollowDist;                               // 0x1582e0c
extern float g_PosseHoverDist;                                   // 0x1582fc0
extern float g_PosseIdleChance;                                  // 0x1687a14
extern Vec3 g_JumpDefault;                                       // 0x169f03c

struct POSSE_IDLE_memory_block {
    bool  mbFollowing;      // +0x00
    float mTimer;           // +0x04
    cSPCreatureBase** mpSlot;  // +0x08 (posse slot; first field is the member)
    Vec3  mAvatarPos;       // +0x0c
    int   mAnimHandle;      // +0x18
};

static __forceinline float InvLen(float lsq) { return 1.0f / sqrtf(lsq + 1e-8f); }

// @ 0x00d824a0
bool __cdecl POSSE_IDLE_Tick(cSPCreatureBase* self, int, int, int, int, POSSE_IDLE_memory_block* mem,
                             int, float dt)
{
    bool isCreatureGame = GetCurrentGameMode() == &g_GameModeCreature;
    cSPCreatureBase* avatar = NounManager()->GetAvatar();
    float dist = FUN_00d99ac0(avatar ? &avatar->mLoco : 0, self ? &self->mLoco : 0, true);
    Loco* aloco = &avatar->mLoco;
    const Vec3* avatarPos = aloco->GetPosition();
    float far2 = g_PosseFollowDist * 2.0f;
    float farDist = Min(far2, g_PosseMaxFollowDist) + 1.0f;

    const Vec3& av = aloco->GetVelocity();
    if (av.x * av.x + av.y * av.y + av.z * av.z > 0.1f) {
        bool follow = mem->mbFollowing;
        if (!follow) {
            const Vec3* p = aloco->GetPosition();
            float dz = p->z - mem->mAvatarPos.z;
            float dx = p->x - mem->mAvatarPos.x;
            float dy = p->y - mem->mAvatarPos.y;
            follow = (dz * dz + dx * dx) + dy * dy > 3.0f || !(dist < g_PosseFollowDist);
        }
        if (follow) {
            // Follow the moving avatar.
            mem->mbFollowing = true;
            self->FUN_00c14750(!self->mLoco.SlotF8());
            float t = mem->mTimer - dt;
            mem->mAnimHandle = 0;
            mem->mTimer = t;
            if (self->mLoco.GetState()->mHasPath != 0 && !(0.0f > mem->mTimer))
                return true;
            mem->mTimer = 0.5f;

            int mode = avatar->FUN_00c0b750();
            if (!(dist < g_PosseFollowDist))
                mode = 3;
            else if (mode == 0)
                mode = 2;

            const Vec3& v = aloco->GetVelocity();
            Vec3 dir;
            float inv = InvLen((v.x * v.x + v.y * v.y) + v.z * v.z);
            dir.x = v.x * inv;
            dir.y = inv * v.y;
            dir.z = inv * v.z;
            Vec3 up;
            float invU = InvLen((avatarPos->x * avatarPos->x + avatarPos->y * avatarPos->y) +
                                avatarPos->z * avatarPos->z);
            up.x = avatarPos->x * invU;
            up.y = invU * avatarPos->y;
            up.z = invU * avatarPos->z;

            if (aloco->GetState()->mHasPath != 0) {
                const Vec3* goal = aloco->GetState()->GetGoal();
                float gx = goal->x - avatarPos->x;
                float gz = goal->z - avatarPos->z;
                float gy = goal->y - avatarPos->y;
                float invG = InvLen((gx * gx + gz * gz) + gy * gy);
                dir.x = invG * gx;
                dir.y = invG * gy;
                dir.z = invG * gz;
            }

            // Side direction: the movement direction without its vertical part.
            float dp = (up.z * dir.z + up.y * dir.y) + up.x * dir.x;
            float tx = dir.x - dp * up.x;
            float tz = dir.z - dp * up.z;
            float ty = dir.y - dp * up.y;
            float lsq = (tz * tz + ty * ty) + tx * tx;
            if (lsq < 1.5258789e-05f)
                return true;
            float invS = InvLen(lsq);
            Vec3 side;
            side.x = invS * tx;
            side.y = invS * ty;
            side.z = invS * tz;
            Vec3 cr;
            cr.x = side.z * up.y - side.y * up.z;
            cr.y = side.x * up.z - up.x * side.z;
            cr.z = up.x * side.y - side.x * up.y;

            // Keep the perpendicular on the far side from the creature.
            const Vec3* sp = self->mLoco.GetPosition();
            float ez = avatarPos->z - sp->z;
            float ey = avatarPos->y - sp->y;
            float ex = avatarPos->x - sp->x;
            float invE = InvLen((ez * ez + ey * ey) + ex * ex);
            if (((invE * ez) * cr.z + (invE * ey) * cr.y) + (invE * ex) * cr.x > 0.0f) {
                cr.x = cr.x * -1.0f;
                cr.y = cr.y * -1.0f;
                cr.z = cr.z * -1.0f;
            }

            float sideOff;
            float fwdOff;
            bool inSpace = false;
            if (isCreatureGame && !(avatar->mFlags & 0x1000)) {
                float len = sqrtf((avatarPos->x * avatarPos->x + avatarPos->y * avatarPos->y) +
                                  avatarPos->z * avatarPos->z);
                if (len > PlanetModel()->GetRadiusAt(avatarPos)) {
                    sideOff = -aloco->GetRadius();
                    fwdOff = self->mLoco.GetRadius();
                    inSpace = true;
                }
            }
            if (!inSpace) {
                sideOff = 20.0f;
                float a = self->mLoco.GetRadius();
                fwdOff = aloco->GetRadius() + a + 1.0f;
            }

            bool hover;
            if (!avatar->mbFlying && !(avatar->mFlags & 0x1000) && self->mbFlying)
                hover = true;
            else
                hover = false;

            Vec3 target;
            if (isCreatureGame && hover) {
                float hoverSpeed = avatar->mpTuning->mHoverSpeed;
                const Vec3& hv = aloco->GetVelocity();
                float hdp = (hv.z * up.z + hv.x * up.x) + hv.y * up.y;
                Vec3 lat;
                lat.x = hv.x - hdp * up.x;
                lat.y = hv.y - hdp * up.y;
                lat.z = hv.z - hdp * up.z;
                float k = FUN_00c29530(avatarPos, &aloco->GetVelocity(), hoverSpeed);
                float speed;
                if (hoverSpeed > 0.0f)
                    speed = g_PosseHoverDist;
                else
                    speed = sqrtf((lat.z * lat.z + lat.y * lat.y) + lat.x * lat.x);
                float off = Clamp(speed * k, 2.0f, 10.0f);
                target.x = lat.x * off + avatarPos->x;
                target.y = avatarPos->y + off * lat.y;
                target.z = avatarPos->z + off * lat.z;
            } else {
                target.x = (side.x * sideOff + avatarPos->x) + cr.x * fwdOff;
                target.y = (avatarPos->y + side.y * sideOff) + cr.y * fwdOff;
                target.z = (avatarPos->z + side.z * sideOff) + cr.z * fwdOff;
            }
            Vec3 snapped;
            Vec3 dest = *PlanetModel()->FUN_00b82b40(&snapped, &target, 0);

            if (hover) {
                if (avatar->mpTuning->mCanHover != 0 && self->mpTuning->mCanHover != 0) {
                    self->MoveToPointAtSpeed(mode, &dest, 1.0f, 2.0f);
                    self->Hover(true);
                    return true;
                }
                self->TryJumpToTarget(0, &dest, &g_JumpDefault, 0.0f, 0);
                return true;
            }
            self->Hover(false);
            self->MoveToPointAtSpeed(mode, &dest, 1.0f, 2.0f);
            return true;
        }
    }

    if (!mem->mbFollowing && !(dist > farDist) && (mem->mpSlot == 0 || *mem->mpSlot == self)) {
        // Settled at the slot: idle animations.
        if (!self->mLoco.IsNearGoal())
            return true;
        if (!self->mbFlying)
            return true;
        if (g_PosseIdleChance > self->m5a8.FUN_00bfc490() * 100.0f && self->AnimationFinished(0xd1dce195u)) {
            self->InterruptAnimation(0xd1dce195u, -1, 0);
            return true;
        }
        if (!self->AnimationFinished(mem->mAnimHandle))
            return true;
        switch (self->FUN_00c029b0()) {
        case 1:
            mem->mAnimHandle = self->PlayAnimation(0x2481e15, 1, -1);
            return true;
        case 2:
            mem->mAnimHandle = self->PlayAnimation(0x2481e16, 1, -1);
            return true;
        case 3:
            mem->mAnimHandle = self->PlayAnimation(0x2481e17, 1, -1);
            return true;
        }
        return true;
    }

    // (Re)join the posse: walk to the slot the posse simulator assigns, or behind the avatar.
    mem->mbFollowing = false;
    mem->mAvatarPos = *aloco->GetPosition();
    self->FUN_00c14750(!self->mLoco.SlotF8());
    mem->mTimer = 0.0f;
    mem->mAnimHandle = 0;
    int mode = 2;
    if (!(dist < g_PosseFollowDist))
        mode = 3;

    Vec3 dest;
    mem->mpSlot = (cSPCreatureBase**)cPosseSimulator::Instance()->FUN_00d53b50(self, &dest);
    if (mem->mpSlot == 0) {
        float a = self->mLoco.GetRadius();
        float r = aloco->GetRadius() + a;
        r = r + r;
        Vec3 facingBuf;
        const Vec3* f = aloco->GetFacing(&facingBuf);
        float inv = InvLen((f->x * f->x + f->y * f->y) + f->z * f->z);
        Vec3 target;
        target.x = avatarPos->x + r * (f->x * inv);
        target.y = avatarPos->y + (f->y * inv) * r;
        target.z = avatarPos->z + (f->z * inv) * r;
        Vec3 snapped;
        dest = *PlanetModel()->FUN_00b82b40(&snapped, &target, 0);
    }

    if (isCreatureGame && !(avatar->mFlags & 0x1000)) {
        float len = sqrtf((avatarPos->x * avatarPos->x + avatarPos->y * avatarPos->y) +
                          avatarPos->z * avatarPos->z);
        if (len > PlanetModel()->GetRadiusAt(avatarPos)) {
            float dz = dest.z - avatarPos->z;
            float dy = dest.y - avatarPos->y;
            float dx = dest.x - avatarPos->x;
            float inv = InvLen((dz * dz + dy * dy) + dx * dx);
            Vec3 n;
            n.x = inv * dx;
            n.y = dy * inv;
            n.z = dz * inv;
            float a = self->mLoco.GetRadius();
            float r = aloco->GetRadius() + a;
            dest.x = avatarPos->x + r * n.x;
            dest.y = avatarPos->y + r * n.y;
            dest.z = avatarPos->z + r * n.z;
        }
    }

    if (!avatar->mbFlying && !(avatar->mFlags & 0x1000) && aloco->GetState()->mHasPath != 0) {
        self->TryJumpToTarget(0, &dest, &g_JumpDefault, 0.0f, 0);
        return true;
    }
    self->MoveToPointAtSpeed(mode, &dest, 1.0f, 2.0f);
    return true;
}

}  // namespace SP
