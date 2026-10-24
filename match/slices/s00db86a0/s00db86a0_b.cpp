// slice s00db86a0 (part b): idle behaviour tick nodes.
//   0x00db90c0  free __cdecl trampoline that ticks every 0x250-byte group record with a
//               cGroupFollower (0x00db86a0) at +0x04; bit 30 of a record's flags ends the
//               record, bit 31 of the next record's flags skips it.
//   0x00db9130  SP::IDLE_memory_block::EnterWalk (thiscall): release the tribe reserve spot,
//               resume locomotion, and walk to a point near the tribe home (or the current
//               position when already inside the tribe radius).
//   0x00db9280  SP::IDLE_Tick (cdecl behaviour node tick): 0 -> conjure food / enter walk,
//               1 -> wait for the animation / loop count / timer, 2 -> arrived -> new activity.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
typedef unsigned char  u8;
typedef unsigned int   u32;

struct Vec3 { float x, y, z; };

struct Follower {
    char pad[0x24c];
    void Update(float dt);                       // 0x00db86a0
};

// 0x250-byte record in the global group array (0x159d548/0x159d54c/0x159d55c).
struct GroupRecord {
    u32     mFlags;                              // +0x00
    Follower mFollower;                          // +0x04
};

extern GroupRecord* gGroupBegin;                 // 0x0159d548
extern GroupRecord* gGroupEnd;                   // 0x0159d54c
extern u32          gGroupFirst;                 // 0x0159d55c

struct Tribe;

// embedded locomotive sub-object at creature+0xc0
struct Locomotive {
    virtual void v00();                          // +0x00
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual Vec3* GetPosition();                 // +0x2c
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual u8   V_58();                         // +0x58
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual float V_74();                        // +0x74
    bool  IsNearGoal();                          // 0x00c42e20
};

struct Creature;

struct Sub120 {
    void* vptr;                                  // +0x00
    Vec3* V_2c()      { return (*(Vec3* (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
};

struct Sub558 {
    void* vptr;                                  // +0x00
    void FUN_00cc7f90(u32 a);                    // 0x00cc7f90
};

struct Tribe {
    void* vptr;                                  // +0x000
    char  pad004[0x60 - 0x004];
    float V_60()      { return (*(float (__thiscall**)(void*))(*(char**)this + 0x60))(this); }
    char  pad060[0x120 - 0x060];
    Sub120 mSub120;                              // +0x120
    char  pad124[0x558 - 0x124];
    Sub558 mSub558;                              // +0x558
};

struct Creature {
    void* vptr;                                  // +0x000
    char  pad004[0xc0 - 0x004];
    Locomotive mLoco;                            // +0x0c0
    char  pad0c4[0xf90 - 0x0c0 - sizeof(Locomotive)];
    u8    mByteF90;                              // +0xf90

    Tribe* GetTribe();                           // 0x00c22f50
    void   UpdateLocomotion(int a);              // 0x00c14750
    bool   AnimationFinished(u32 id);            // 0x00c123f0
    u32    PlayAnimation(u32 id, int a, int b);  // 0x00c12190
    void   MoveToPointAtSpeed(int a, const Vec3* p, float s0, float s1);   // 0x00c1c1d0
    int    FUN_00c26120();                       // 0x00c26120
    bool   FUN_00c25480(int a, int b);           // 0x00c25480
};

// behaviour-node persistent block (idle node); PDB: SP::IDLE_memory_block, size 0x18
struct IdleBlock {
    u32  mState;                                 // +0x00
    u32  mReservedSpot;                          // +0x04
    u32  mAnimationID;                           // +0x08
    int  mLoopCount;                             // +0x0c
    float mTimer;                                // +0x10
    Creature* mpTribeMember;                     // +0x14

    void   EnterWalk();
    Vec3*  FUN_00db7d60(Vec3* out, const Vec3* in);   // 0x00db7d60
    void   PickNewActivity();                    // 0x00da7cc0
};

// @ 0x00db90c0
void FUN_00db90c0(float dt)
{
    GroupRecord* p = gGroupFirst < 0x3fffffffu ? &gGroupBegin[gGroupFirst] : gGroupEnd;
    GroupRecord* last = gGroupEnd;
    if (last == p)
        return;
    do {
        p->mFollower.Update(dt);
        u32 f;
        do {
            f = p->mFlags;
            ++p;
        } while (!((u8)(f >> 30) & 1) && ((u8)(p->mFlags >> 31) & 1));
    } while (last != p);
}

// @ 0x00db9130
void IdleBlock::EnterWalk()
{
    u32 invalid = 0xffffffffu;
    if (mReservedSpot != invalid) {
        Tribe* t = mpTribeMember->GetTribe();
        t->mSub558.FUN_00cc7f90(mReservedSpot);
        mReservedSpot = invalid;
    }
    mpTribeMember->UpdateLocomotion(1);

    Vec3* pos;
    if (mpTribeMember->mLoco.V_58()) {
        Tribe* t = mpTribeMember->GetTribe();
        float r = mpTribeMember->mLoco.V_74();
        r = r + t->V_60() + 5.0f;
        Vec3* home = t->mSub120.V_2c();
        Vec3* self = mpTribeMember->mLoco.GetPosition();
        float dx = self->x - home->x;
        float dy = self->y - home->y;
        float dz = self->z - home->z;
        float d2 = dx * dx;
        d2 = d2 + dy * dy;
        d2 = d2 + dz * dz;
        if (d2 < r * r)
            pos = mpTribeMember->mLoco.GetPosition();
        else
            pos = 0;
    } else {
        pos = 0;
    }

    Vec3 buf;
    mpTribeMember->MoveToPointAtSpeed(2, FUN_00db7d60(&buf, pos), 1.0f, 2.0f);
    mState = 2;
}

// @ 0x00db9280
bool FUN_00db9280(Creature* self, int, int, u32 flags, int, IdleBlock* mem, int, float dt)
{
    switch (mem->mState) {
    case 0:
        if (self->FUN_00c25480(self->FUN_00c26120(), 0))
            mem->EnterWalk();
        break;
    case 1:
        if (!self->AnimationFinished(mem->mAnimationID))
            return true;
        if (mem->mLoopCount == 0) {
            mem->mTimer -= dt;
            if (mem->mTimer < 0.0f) {
                mem->mState = self->mLoco.V_58() ? 2 : 0;
                return true;
            }
        } else {
            --mem->mLoopCount;
            if (mem->mAnimationID != 0xffffffffu) {
                self->PlayAnimation(mem->mAnimationID, 1, -1);
                return true;
            }
            self->UpdateLocomotion(0);
            return true;
        }
        break;
    case 2:
        if (self->mLoco.IsNearGoal() && (self->mByteF90 || (flags & 0x1800) != 0))
            mem->PickNewActivity();
        break;
    }
    return true;
}
