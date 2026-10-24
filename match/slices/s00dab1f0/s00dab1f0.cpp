// Slice s00dab1f0 -- three functions from the Spore "tribe behaviour" module:
//   SP::TRIBE_GET_TOOL_Tick (0x00DAB1F0, 800 bytes, __cdecl)
//   FUN_00dabc30           (0x00DABC30, 211 bytes, __cdecl)
//   FUN_00dabd10           (0x00DABD10, 215 bytes, __cdecl)
// Types/offsets follow the sibling slice s00db0130 (same Tribe/Citizen/TaskMgr machinery).
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// ---- spatial / locomotive sub-object (embedded at Citizen+0x34 and +0xc0) ------------------
struct Spatial {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();             // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual bool vf58();                           // +0x58
    PV(23) PV(24) PV(25) PV(26)
    virtual const float* FUN_v6c(float* out);      // +0x6c (six-float box)
    PV(28)
    virtual float GetRadius();                     // +0x74
    bool IsNearGoal();                             // 0x00c42e20
};

struct Citizen;
struct Tribe {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21) PV(22) PV(23)
    virtual float FUN_v60();                       // +0x60
    float* FUN_00c986d0(uint32_t param, int* out, Citizen* c);   // 0x00c986d0, ret 0xc
    uint32_t pad04[(0x120 - 4) / 4];
    Spatial  mPos;                                 // +0x120
};

// ---- animation ----------------------------------------------------------------------------
struct AnimCtl {
    uint32_t PlayIdleAnimation(int id, int flags);              // 0x00bc96a0, ret 8
    void FUN_00bc97f0(int a, int b, float c, int d);            // ret 0x10
};
struct AnimOwner {
    uint32_t pad[2];
    AnimCtl  mCtl;                                 // +0x08
};

// ---- creature -----------------------------------------------------------------------------
struct Citizen {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool vf2c();                           // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    virtual void vf84(void* part, int a, int b);   // +0x84

    Tribe* GetTribe();                             // 0x00c22f50
    int    FUN_00bf3a90();                         // 0x00bf3a90
    void   FUN_00c9d150();                         // 0x00c9d150
    bool   AnimationFinished(int id);              // 0x00c12400, ret 4
    int    PlayAnimationWithTarget(int id, Vec3* p, int a);   // 0x00c14910, ret 0xc
    void   MoveToPointAndFacingAtSpeed(int mode, Vec3* p, Vec3* d, float a, float b); // 0x00c1c5c0, ret 0x14

    uint32_t  pad04[(0x34 - 4) / 4];
    Spatial   mBundle;                             // +0x34
    uint32_t  pad38[(0xc0 - 0x38) / 4];
    Spatial   mLoco;                               // +0xc0
    uint32_t  padc4[(0x120 - 0xc4) / 4];
    uint8_t   mPart120[16];                        // +0x120
    uint32_t  pad130[(0xb48 - 0x130) / 4];
    void*     mpB48;                               // +0xb48
    AnimOwner* mpAnim;                             // +0xb4c
};

// ---- behaviour state block for the "get tool" tool behaviour --------------------------------
struct GetToolState {
    Citizen* mpOther;   // +0x00
    float    mPosX;     // +0x04
    float    mPosY;     // +0x08
    float    mPosZ;     // +0x0c
    uint32_t mTribe;    // +0x10
    int      mState;    // +0x14
    int      miResult;  // +0x18
    int      miAnim;    // +0x1c
};

// ---- task manager --------------------------------------------------------------------------
struct ToolNode {
    uint32_t pad[0x1b0 / 4];
    Vec3     mPos;                                 // +0x1b0
};
struct TaskMgr {
    ToolNode* Find(uint32_t kind, void* fn, void* key);   // 0x00bca620, ret 0xc
};
TaskMgr* FUN_00bc9b00();                                   // 0x00bc9b00

// ---- iterator used by FUN_00dabd10 ---------------------------------------------------------
struct IteratorB9 {
    bool     FUN_00bc9b50();                       // 0x00bc9b50
    Citizen* FUN_00bc9b10();                       // 0x00bc9b10
};

namespace SP {
Vec3* normalized_safe(Vec3* out, const Vec3* in);          // 0x00449c20

// @ 0x00dab1f0
bool TRIBE_GET_TOOL_Tick(Citizen* c, int p2, float p3, int p4, int p5, GetToolState* st)
{
    if (!st->mpOther) return false;
    if (st->mpOther->vf2c()) return false;

    const Vec3* p = st->mpOther->mBundle.GetPosition();
    float dx = p->x - st->mPosX;
    float dy = p->y - st->mPosY;
    float dz = p->z - st->mPosZ;
    if (dx * dx + dy * dy + dz * dz > 1.0f) return false;

    if (st->mpOther->FUN_00bf3a90() > 0) {
        if (c->mLoco.vf58()) return false;
    }

    if (st->mState == 0) {
        float radius = c->mLoco.GetRadius() + st->mpOther->mBundle.GetRadius();
        float* v = st->mpOther->GetTribe()->FUN_00c986d0(st->mTribe, &st->miResult, c);
        if (st->miResult < 0) {
            st->mpOther->FUN_00c9d150();
            return false;
        }
        void* part = st->mpOther ? (void*)st->mpOther->mPart120 : (void*)0;
        c->vf84(part, 1, 4);

        const Vec3* q = st->mpOther->mBundle.GetPosition();
        Vec3 delta;
        delta.x = v[0] - q->x;
        delta.y = v[1] - q->y;
        delta.z = v[2] - q->z;
        Vec3 dir;
        SP::normalized_safe(&dir, &delta);

        float d = radius + 0.1f;
        float offX = dir.x * d;
        float offY = dir.y * d;
        float offZ = dir.z * d;
        const Vec3* r = st->mpOther->mBundle.GetPosition();
        Vec3 target;
        target.x = r->x + offX;
        target.y = r->y + offY;
        target.z = r->z + offZ;
        Vec3 facing;
        facing.x = -dir.x;
        facing.y = -dir.y;
        facing.z = -dir.z;
        c->MoveToPointAndFacingAtSpeed(2, &target, &facing, 1.0f, 2.0f);
        st->mState = 1;
        return true;
    }

    if (st->mState == 1) {
        if (!c->mLoco.IsNearGoal()) return true;
        st->mState = 2;
        float box[6];
        const float* m = st->mpOther->mBundle.FUN_v6c(box);
        Vec3 mid;
        mid.x = (m[0] + m[3]) * 0.5f;
        mid.y = (m[4] + m[1]) * 0.5f;
        mid.z = (m[5] + m[2]) * 0.5f;
        st->miAnim = c->PlayAnimationWithTarget(0x51c73a5, &mid, -1);
        return true;
    }

    if (st->mState == 2) {
        if (c->AnimationFinished(st->miAnim)) {
            st->mpOther->FUN_00c9d150();
            return false;
        }
        return true;
    }
    return true;
}
} // namespace SP

// @ 0x00dabc30
bool FUN_00dabc30(Citizen* c)
{
    if (c->mpAnim->mCtl.PlayIdleAnimation(0, 0x80) != 0) return false;

    struct Key { Tribe* mTribe; Citizen* mCitizen; } key;
    key.mTribe = c->GetTribe();
    key.mCitizen = c;

    ToolNode* task = FUN_00bc9b00()->Find(0x567cb99, (void*)0xdabbe0, &key);
    if (task) {
        Vec3 n;
        n.x = -task->mPos.x;
        n.y = -task->mPos.y;
        n.z = -task->mPos.z;
        c->MoveToPointAndFacingAtSpeed(2, (Vec3*)c->mLoco.GetPosition(), &n, 1.0f, 2.0f);
    }
    return task != 0;
}

// @ 0x00dabd10
bool FUN_00dabd10(IteratorB9* param_1, Citizen* param_2)
{
    if (param_1->FUN_00bc9b50()) return false;

    Citizen* other = param_1->FUN_00bc9b10();
    if (other->GetTribe() != param_2->GetTribe()) return false;

    float r = other->GetTribe()->FUN_v60();
    float rr = r + r;

    const Vec3* a = param_2->mLoco.GetPosition();
    const Vec3* b = other->mLoco.GetPosition();
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    float d2 = dx * dx + dy * dy + dz * dz;

    if (d2 < rr * rr) return true;
    return false;
}