// SP::TRIBE_FIGHT_Tick: per-tick behavior of a tribe creature in the "fight" behavior-tree node.
#include "types.h"
#include <math.h>

namespace SP {

struct Vec3 { float x, y, z; };

struct LocoState {
    uint32_t pad00[0x5c / 4];
    int      mHasPath;      // +0x5c
    uint32_t pad60[(0x70 - 0x60) / 4];
    uint32_t mMoveFlags;    // +0x70
    Vec3* GetPos();         // FUN_00c423c0
};

// sub-object embedded in the creature at +0xc0 (own vtable)
struct Loco {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual Vec3* GetPosition();                       // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual bool IsMovingFast();                       // +0x58
    virtual Vec3* GetFacing(Vec3* out);                // +0x5c
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74
    LocoState* GetState();                             // FUN_00c41ec0
};

struct IdleRes { uint32_t pad[3]; int mId; };

struct BehStim {
    IdleRes* PlayIdleAnimation(uint32_t a, uint32_t b);
    void ClearAll(uint32_t a, uint32_t b);
};

struct Big { uint32_t pad[0x1a4 / 4]; int m1a4; void FUN_00bc9b10(); };

struct Behav {
    uint32_t pad0[2];
    uint32_t pad1[(0x1c8 - 8) / 4];
    uint32_t mFlags;                                   // +0x1c8
    uint32_t pad2[(0x600 - 0x1cc) / 4];
    Big*     mBig;                                     // +0x600
};

struct Obj {
    virtual void s00(); virtual void s01();
    virtual Obj* GetOwner();                           // +0x08
    virtual int  GetHandle();                          // +0x0c
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual Vec3* GetPosition();                       // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74
    uint32_t pad04[2];
    int      m0c;
    uint32_t pad10[(0x7c - 0x10) / 4];
    int      m7c;
    uint32_t pad80[(0xa8 - 0x80) / 4];
    float    mA8;
    uint32_t padac[(0xf4 - 0xac) / 4];
    float    mF4;
    uint32_t padf8[(0x130 - 0xf8) / 4];
    int      m130;
    bool  FUN_00c0b000();
    float GetBound(int);                               // TuningObj::GetBound
    void  FUN_00aca360();
    void  FUN_00acd2d0();
};

struct CitSub { int FUN_00bca0c0(int a, int b, int c, int d); };
struct Citizen {
    uint32_t pad[0xb48 / 4];
    CitSub*  mSub;                                     // +0xb48
    int GetTribe();
};

struct StratMgr {
    int  FUN_00bc2240(int hash, Vec3 pos);
    void FUN_00bc23d0(int handle, Vec3 pos);
    void FUN_00bc2180(int handle);
};
struct TribeStrategy { uint32_t pad[0x1c8 / 4]; StratMgr* mMgr; };

struct RefSlot { void* mp; void Assign(int v); };       // FUN_00ae6690

struct FightState {
    int      mTarget;      // +0x00
    int      mId;          // +0x04
    int      mSlot;        // +0x08
    int      mStratHandle; // +0x0c
    float    mTimer0;      // +0x10
    float    mTimer1;      // +0x14
    float    mTimer2;      // +0x18
    float    mAttackTimer; // +0x1c
    float    mAttackReset; // +0x20
    bool     mB24;         // +0x24
    bool     mB25;         // +0x25
    bool     mNoRetarget;  // +0x26
    int      mEventAnim;   // +0x28
    int      mAnim;        // +0x2c
    int      mHintArg;     // +0x30
    RefSlot  mRef;         // +0x34
};

struct cSPCreatureBase {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32();
    virtual void SetTarget(Obj* o, int a, int b);      // +0x84
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44();
    virtual Obj* GetObjectById(int id);                // +0xb4
    virtual void s46(); virtual void s47();
    virtual bool CanReach(Obj* o, float a, float b);   // +0xc0

    uint32_t pad04[(0xc0 - 4) / 4];
    Loco     mLoco;                                    // +0xc0
    uint32_t padc4[(0xb4c - 0xc4) / 4];
    Behav*   mBehav;                                   // +0xb4c
    uint32_t padb50[(0xb5c - 0xb50) / 4];
    uint8_t  mFlag5c;                                  // +0xb5c
    uint8_t  padb5d[3];
    uint32_t padb60[(0xb80 - 0xb60) / 4];
    float    mTurnRate;                                // +0xb80
    uint32_t padb84[(0xc28 - 0xb84) / 4];
    char*    mNeighbors;                               // +0xc28
    uint32_t padc2c[(0xe8c - 0xc2c) / 4];
    int      mActiveTarget;                            // +0xe8c

    Obj* GetTargetObj();                               // FUN_00c0ee60
    int  GetTargetAsCreature();
    int  GetMode();                                    // FUN_00c22dc0
    bool AnimationFinished(int id);                    // 0xc12400
    bool AnimationFinished2(int id);                   // 0xc123f0
    bool WaitForAnimEventOrEnd(int id, int* out, int a, int b, int c);
    void FUN_00c26c80();
    bool FUN_00c26c90(int a, int b);                   // thiscall, ret 8
    int  InterruptAnimation(int id, int a, int b);
    int  PlayAnimation(int id, int a, int b);
    bool FUN_00c0c130();
    float FUN_00c0c070();
    bool FUN_00c0d560(int tgt, float a, float b);
    void FUN_00c073a0(int a);
    void FUN_00c14750(int a);
    int  FUN_00c23750();
    int  FUN_00c22a70();
    bool FUN_00c0e0c0(int id);
    int  FUN_00c12410(uint32_t* mask, float range, int a, int b, int c, int d, int e);
    void Attack(int tgt, int a);
    void MoveToPointAtSpeed(int a, const Vec3* p, float s0, float s1);
};

// callees
Citizen* FUN_00d994c0(int creature);
void*    FUN_00d998d0(IdleRes* idle, int hash);
bool     FUN_00da6270(cSPCreatureBase* c, int id);
int      FUN_00d998f0(const void* p);
float    FUN_004df2d0(const void* tuning);
float    FUN_00d38a30(int which, cSPCreatureBase* c);
Obj*     CheckForNewTarget(cSPCreatureBase* c, Obj* o, int hint);
Obj*     FUN_00b3d480(int handle);
void     FUN_00d66e10(cSPCreatureBase* c, int slot);
void     FindGroup(cSPCreatureBase* c);
void     FUN_00da8370(cSPCreatureBase* c, int id, int handle);
TribeStrategy* Instance();                             // cTribeModeStrategy::Instance
bool     FUN_0064f350(int p, uint32_t hash, int z);
Obj*     FUN_00c9cec0(int which);
Vec3*    normalized_safe(Vec3* out, const Vec3* in);
char     Vector3Equal(const Vec3* a, const Vec3* b);
void     FUN_00d99e20(Vec3* pos, Vec3* res);
bool     GetFightSlots(cSPCreatureBase* c, int* slot, int arg);
float    GetPropertyT_float(int props, uint32_t hash, float def);   // 0x004e1c70 SP::GetPropertyT<float>
LocoState* LocoGetState(Loco* l);

extern float DAT_0157206c;
extern float DAT_01582ea8;
extern int   DAT_01581288;
extern char  DAT_01581254[];
extern char  DAT_0158124c[];
extern char  DAT_01581244[];
extern Vec3  DAT_0169ecbc;

static inline const float& MaxRef(const float& a, const float& b) { return (a > b) ? a : b; }
static inline const float& MinRef(const float& a, const float& b) { return (a > b) ? b : a; }

// @ 0x00d697a0
bool TRIBE_FIGHT_Tick(cSPCreatureBase* self, int, int, int, int, FightState* st, int, float dt)
{
    Obj* targetObj = self->GetTargetObj();
    int mode = self->GetMode();

    if (!targetObj) {
        if (st->mNoRetarget) return false;
        return FUN_00da6270(self, st->mId);
    }

    Obj* myObj = targetObj->GetOwner();
    int tgtCreature = self->GetTargetAsCreature();
    Citizen* citizen = FUN_00d994c0(tgtCreature);
    BehStim* stim = (BehStim*)((char*)self->mBehav + 8);
    IdleRes* idle = stim->PlayIdleAnimation(0, 0x400000);

    bool checkCitizen = true;
    if (idle != 0 && citizen) {
        void* r = FUN_00d998d0(idle, 0x4f396a66);
        if (r && (int)r == citizen->GetTribe()) {
            ((BehStim*)((char*)self->mBehav + 8))->ClearAll(0, 0x400000);
            return FUN_00da6270(self, st->mId);
        }
    } else if (idle != 0) {
        checkCitizen = false;
    }
    if (checkCitizen && citizen && citizen->mSub->FUN_00bca0c0(0, 2, 0, 0) != -1)
        return false;

    if (st->mAnim) {
        if (!self->AnimationFinished(st->mAnim)) return true;
        if (st->mNoRetarget) return false;
        return FUN_00da6270(self, st->mId);
    }

    if (!self->FUN_00c26c90(0x6000e, 1)) return true;

    if (st->mEventAnim) {
        int tmp = 0;
        if (!self->WaitForAnimEventOrEnd(0x7d7502fc, &tmp, -1, 0, 1)) return true;
        self->FUN_00c26c80();
        st->mEventAnim = 0;
    }

    st->mTimer0 = st->mTimer0 - dt;
    st->mTimer1 = st->mTimer1 - dt;
    st->mTimer2 = st->mTimer2 - dt;
    st->mAttackTimer = st->mAttackTimer - dt;

    if (!self->mLoco.IsMovingFast() && st->mAttackTimer < 0.0f) {
        st->mAnim = self->InterruptAnimation(0x5b93649, -1, 0);
        ((BehStim*)((char*)self->mBehav + 8))->ClearAll(0x400, 0);
        return true;
    }

    if (!st->mB24) {
        st->mB24 = (FUN_00d998f0(targetObj) == 0);
        if (st->mB24) {
            st->mTimer0 = FUN_004df2d0(DAT_01581254) + 2.0f;
            st->mTimer2 = 0.0f;
        }
    }

    {
        Obj* ao;
        if (self->mActiveTarget == -1
            || !(ao = self->GetObjectById(self->mActiveTarget))
            || !ao->FUN_00c0b000())
            self->mFlag5c = 1;
    }

    if (!self->FUN_00c0c130())
        self->mTurnRate = self->FUN_00c0c070() * DAT_01582ea8;

    Vec3* pos  = self->mLoco.GetPosition();
    Vec3* tpos = myObj->GetPosition();
    float objRadius = myObj->GetRadius();
    float sum = self->mLoco.GetRadius() + objRadius;
    float dx = tpos->x - pos->x;
    float dy = tpos->y - pos->y;
    float dz = tpos->z - pos->z;
    float dist = (float)(sqrt((double)(dz * dz + dy * dy + dx * dx)) - sum);
    if (!(dist >= 0.0f)) dist = 0.0f;

    float scale1 = FUN_00d38a30(1, self);
    float scale2 = FUN_00d38a30(2, self);

    bool inRange;
    if (!st->mB24 && !self->mLoco.IsMovingFast()
        && (tgtCreature == 0
            || (!self->FUN_00c0d560(tgtCreature, scale1, dist)
                && !self->CanReach((Obj*)tgtCreature, scale2, dist))))
        inRange = false;
    else
        inRange = true;

    st->mRef.Assign(FUN_00d998f0(st->mRef.mp));

    if (st->mRef.mp == 0) {
        if (mode == 9) return FUN_00da6270(self, st->mId);
        if (self->mActiveTarget == -1 && (st->mTimer2 <= 0.0f || !inRange)) {
            st->mTimer2 = FUN_004df2d0(DAT_01581254) + 1.0f;
            if (!st->mNoRetarget) {
                Obj* newT = CheckForNewTarget(self, targetObj, st->mHintArg);
                if (newT) {
                    if (self->mLoco.IsMovingFast()) {
                        FUN_00b3d480(targetObj->GetHandle())->FUN_00aca360();
                        FUN_00b3d480(newT->GetHandle())->FUN_00acd2d0();
                    }
                    self->SetTarget(newT, 1, 1);
                    st->mB24 = false;
                    st->mTimer0 = 0.0f;
                    st->mTimer1 = 0.0f;
                    FUN_00d66e10(self, st->mSlot);
                    FindGroup(self);
                    FUN_00da8370(self, st->mId, newT->GetHandle());
                }
            }
        }
    }

    if (st->mB24) {
        if (0.0f <= st->mTimer0) return true;
        return FUN_00da6270(self, st->mId);
    }

    if (self->mLoco.IsMovingFast()) {
        if (self->FUN_00c23750()) {
            Vec3 p = *self->mLoco.GetPosition();
            if (st->mStratHandle == 0) {
                st->mStratHandle = Instance()->mMgr->FUN_00bc2240(0xad1a17d, p);
            } else {
                Instance()->mMgr->FUN_00bc23d0(st->mStratHandle, p);
            }
        } else if (st->mStratHandle) {
            Instance()->mMgr->FUN_00bc2180(st->mStratHandle);
            st->mStratHandle = 0;
        }
    }

    Big* big = self->mBehav->mBig;
    big->FUN_00bc9b10();

    if ((uint64_t)self->mBehav->mFlags & 0x10000000ULL) {
        IdleRes* res = ((BehStim*)((char*)self->mBehav + 8))->PlayIdleAnimation(0x10000000, 0);
        int id = res->mId;
        Obj* o = self->GetObjectById(id);
        if (o && o->m0c == 1
            && *(float*)(self->mNeighbors + id * 16 + 4) >= 1.0f) {
            st->mTarget = id;
            st->mTimer0 = -1.0f;
            st->mTimer1 = -1.0f;
            self->FUN_00c073a0(-1);
            self->FUN_00c14750(0);
        }
        ((BehStim*)((char*)self->mBehav + 8))->ClearAll(0x10000000, 0);
    }

    Loco* loco = &self->mLoco;

    if (self->mActiveTarget != -1) {
        Obj* o = self->GetObjectById(self->mActiveTarget);
        if (loco->GetState()->mHasPath == 0 && o && !o->FUN_00c0b000()) {
            float scale0 = FUN_00d38a30(0, self);
            float a = (o->mF4 + o->mA8) * scale0;
            float b = o->GetBound(0);
            float total = MaxRef(a, b) + sum;
            float speed = total * 0.98f;
            if (speed < dist) {
                Vec3* p = myObj->GetPosition();
                self->MoveToPointAtSpeed(2, p, speed, total);
                loco->GetState()->mMoveFlags |= 3;
            }
        }
        goto done;
    }

    if (mode == 3 && self->FUN_00c22a70() != 3 && self->AnimationFinished2(0x2c39370)) {
        st->mEventAnim = self->InterruptAnimation(0x56d43de, -1, 0);
        return true;
    }
    if (st->mB25 == 1 && !self->FUN_00c0e0c0(0x67378dd))
        self->PlayAnimation(0x67378dd, 1, -1);

    {
        uint32_t mask[3];
        mask[0] = 0; mask[1] = 0; mask[2] = 0;
        uint32_t i = 0;
        do {
            mask[i] = ~mask[i];
            i = i + 1;
        } while (i < 3);
        mask[2] &= 0xffffff;
        int tid = st->mTarget;
        if (((1 << (mode & 31)) & 0xa0e) != 0) {
            mask[0] &= 0xbfffffff;
            mask[1] &= 0xfffffffd;
        }
        if (tid == -1) {
            bool found = false;
            if (mode == 3) {
                uint32_t m2[3];
                m2[0] = 0; m2[1] = 0x800; m2[2] = 0;
                tid = self->FUN_00c12410(m2, dist, 1, 0, 0, 1, 0);
                Obj* o = self->GetObjectById(tid);
                if (o && ((o->mF4 + o->mA8) - sum) * 0.25f < dist && tid != -1)
                    found = true;
            }
            if (!found) {
                tid = self->FUN_00c12410(mask, dist, 0, 0, 0, 0, 0);
                if (tid == -1)
                    tid = self->FUN_00c12410(mask, dist, 1, 0, 0, 1, 0);
            }
        }

        Obj* tobj = 0;
        float scaleA = FUN_00d38a30(0, self);
        float rngInner = 0.0f;
        float approach = 0.0f;
        float rngOuter = 0.0f;
        bool canMelee = true;
        if (tid != -1) {
            tobj = self->GetObjectById(tid);
            rngOuter = (tobj->mF4 + tobj->mA8) * scaleA;
            rngInner = tobj->GetBound(0);
            rngOuter = MaxRef(rngOuter, rngInner);
            float x3 = rngOuter * 0.98f + sum;
            float y = (dist + rngInner) + sum;
            approach = MinRef(x3, y);
            canMelee = FUN_0064f350(tobj->m130, 0xffa5839d, 0);
        }
        if (mode == 3) {
            Obj* t = *(Obj**)((char*)FUN_00c9cec0(3) + 0x24);
            float A = (t->mF4 + t->mA8) * scaleA;
            rngInner = t->GetBound(0);
            approach = A * 0.98f + sum;
            rngOuter = A;
            canMelee = false;
        }

        if (0.0f <= st->mTimer0 || tid == -1
            || *(float*)(self->mNeighbors + tid * 16 + 4) < 1.0f) {
            // not ready to attack: keep positioning
            if (st->mTimer1 < 0.0f) {
                st->mTimer1 = FUN_004df2d0(DAT_0158124c);
                if (mode == 3) {
                    self->MoveToPointAtSpeed(2, tpos, approach, rngOuter);
                    loco->GetState()->mMoveFlags |= 1;
                } else if (!GetFightSlots(self, &st->mSlot, big->m1a4)) {
                    float prop = GetPropertyT_float(DAT_01581288, 0x5753ef17, 5.0f);
                    if (dist <= prop) {
                        loco->GetState()->mMoveFlags |= 1;
                    } else {
                        self->MoveToPointAtSpeed(2, tpos, prop + sum, prop + sum);
                        loco->GetState()->mMoveFlags |= 1;
                    }
                } else if (1.5258789e-05f < dist) {
                    self->MoveToPointAtSpeed(2, tpos, approach, approach + 0.2f);
                    loco->GetState()->mMoveFlags |= 4;
                    loco->GetState()->mMoveFlags |= 1;
                } else {
                    float x = rngOuter * 0.98f + sum;
                    Vec3 d;
                    d.x = pos->x - tpos->x;
                    d.y = pos->y - tpos->y;
                    d.z = pos->z - tpos->z;
                    Vec3 tmp;
                    Vec3* n = normalized_safe(&tmp, &d);
                    Vec3 res;
                    res.x = tpos->x + x * n->x;
                    res.y = tpos->y + n->y * x;
                    res.z = tpos->z + n->z * x;
                    FUN_00d99e20(pos, &res);
                    self->MoveToPointAtSpeed(2, &res, 0.2f, dt);
                    loco->GetState()->mMoveFlags |= 1;
                }
            }
            goto done;
        }

        // ready: aim and attack
        Vec3 d;
        d.x = tpos->x - pos->x;
        d.y = tpos->y - pos->y;
        d.z = tpos->z - pos->z;
        Vec3 u;
        normalized_safe(&u, &d);
        Vec3 p;
        normalized_safe(&p, pos);
        float dot = (p.x * u.x + u.y * p.y) + u.z * p.z;
        Vec3 w;
        w.x = u.x - p.x * dot;
        w.y = u.y - dot * p.y;
        w.z = u.z - dot * p.z;
        if (Vector3Equal(&w, &DAT_0169ecbc)) {
            w = u;
        } else {
            Vec3 t2;
            Vec3* nn = normalized_safe(&t2, &w);
            w = *nn;
        }
        Vec3 facingTmp;
        Vec3* facing = loco->GetFacing(&facingTmp);
        bool aligned = 0.9f < (facing->z * w.z + facing->y * w.y) + w.x * facing->x;
        bool slotWait;
        if (canMelee == true && st->mSlot == -1) slotWait = true;
        else slotWait = false;

        if (dist <= rngOuter && rngInner <= dist && aligned && !slotWait) {
            st->mAttackTimer = st->mAttackReset;
            self->Attack(tid, 0);
            st->mTarget = -1;
            st->mTimer0 = FUN_004df2d0(DAT_01581244);
            st->mB25 = true;
            goto done;
        }

        float lx = tpos->x - pos->x;
        float lz = tpos->z - pos->z;
        float ly = tpos->y - pos->y;
        float rr = rngOuter + sum;
        if (aligned && !((lx * lx + lz * lz) + ly * ly > rr * rr) && !slotWait)
            goto done;

        LocoState* ls = loco->GetState();
        if (ls->mHasPath != 0) {
            Vec3* cp = ls->GetPos();
            float ex = cp->x - tpos->x;
            float ey = cp->y - tpos->y;
            float ez = cp->z - tpos->z;
            float rad = myObj->GetRadius();
            if ((ex * ex + ez * ez) + ey * ey <= rad * rad)
                goto done;
        }

        if (mode == 3 || tobj->m7c == 1 || tobj->m7c == 3) {
            self->MoveToPointAtSpeed(2, tpos, approach, approach + DAT_0157206c);
            loco->GetState()->mMoveFlags |= 2;
        } else if (GetFightSlots(self, &st->mSlot, big->m1a4)) {
            if (!tobj->FUN_00c0b000()) {
                self->MoveToPointAtSpeed(2, tpos, approach, approach + 0.2f);
                loco->GetState()->mMoveFlags |= 4;
                loco->GetState()->mMoveFlags |= 1;
                goto done;
            }
            self->MoveToPointAtSpeed(2, tpos, sum, sum + 0.2f);
            loco->GetState()->mMoveFlags |= 2;
        } else {
            float prop = GetPropertyT_float(DAT_01581288, 0x5753ef17, 5.0f);
            if (prop < dist) {
                self->MoveToPointAtSpeed(2, tpos, prop + sum, prop + sum);
                loco->GetState()->mMoveFlags |= 1;
                goto done;
            }
            if (dist < prop * 0.25f
                && (tgtCreature == 0 || tgtCreature != self->GetTargetAsCreature())) {
                float x = prop + sum;
                Vec3 d3;
                d3.x = pos->x - tpos->x;
                d3.y = pos->y - tpos->y;
                d3.z = pos->z - tpos->z;
                Vec3 tmp;
                Vec3* n = normalized_safe(&tmp, &d3);
                Vec3 res;
                res.x = tpos->x + n->x * x;
                res.y = tpos->y + n->y * x;
                res.z = tpos->z + n->z * x;
                FUN_00d99e20(pos, &res);
                self->MoveToPointAtSpeed(2, &res, 0.2f, dt);
                loco->GetState()->mMoveFlags |= 1;
                goto done;
            }
        }
        loco->GetState()->mMoveFlags |= 1;
    }
done:
    if (!st->mB25 && loco->GetState()->mHasPath != 0) {
        st->mB25 = true;
        self->InterruptAnimation(0x4cffb, -1, 0);
    }
    return true;
}

} // namespace SP
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct SP {
    void GetPropertyT_float(int, unsigned int, float); // 0x004e1c70
};
}
