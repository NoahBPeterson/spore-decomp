// Slice s00dbe140: SP::MOVE_Activate (0x00dbe520, 1801 bytes), __cdecl, 7 stack args.
// Creature behaviour "Move": takes the move target from the animation state or from the caller's
// parameter block, creates / reuses the per-creature move state (pooled), and fills the result block.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};

#define SLOT(n) virtual void s##n();

// A spatial game object (the move target). Vtable slots as used by the move behaviour.
struct SpatialObj {
    SLOT(0) SLOT(1) SLOT(2)
    virtual void* Cast(uint32_t typeId);                       // +0xc
    SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
    virtual const Vec3* GetPosition();                         // +0x2c
    SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21)
    SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    virtual float GetRadius();                                 // +0x74
    SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40)
    SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45)
    virtual void* QueryComponent(uint32_t id);                 // +0xb8
    virtual void AddRef2();                                    // +0xbc
    virtual void Release2();                                   // +0xc0
};

struct AnimEntry {
    char pad0[0xc];
    float mValue;                  // +0xc
    char pad10[0x1c];
    SpatialObj* mpObject;          // +0x2c
};
struct AnimSub {
    AnimEntry* PlayIdleAnimation(uint32_t a, uint32_t b);       // 0x00bc96a0 (ret 8)
};
struct AnimRecord {
    uint32_t mType;
    char pad4[0x4c - 4];
};
struct MoveState {
    char pad0[0x190];
    char mObjPtr[4];               // +0x190 (cGameObjectPtr)
    float mDestX, mDestY, mDestZ;  // +0x194..
    char pad1a0[0x1a4 - 0x1a0];
    int mMoveHandle;               // +0x1a4
    char pad1a8[0x1b4 - 0x1a8];
    float mF1b4;
    float mF1b8;
    float mF1bc;
    float mF1c0;
    char pad1c4[4];
    float mF1c8;
    char pad1cc[0x224 - 0x1cc];
    void* mpFunc224;               // +0x224
    char pad228[0x238 - 0x228];
    void* mpFunc;                  // +0x238
    char mb23c;                    // +0x23c
    char pad23d[0x244 - 0x23d];
    char mb244;                    // +0x244
    char pad245[3];
    int mI248;                     // +0x248
    void FUN_00c70110(SpatialObj* p);                           // cGameObjectPtr::operator= (on +0x190)
    void FUN_00db6ef0(void* loco);                              // ret 4
};
struct MoveStateOwner {
    char pad[0x1a4];
    int mMoveHandle;               // +0x1a4
};
struct MovePool {
    int CreateObject();                                         // 0x00dbe4e0
    MoveState* GetObject(int handle);                           // 0x00db3c40 (ret 4)
};
extern MovePool gMovePool;                                      // 0x0159d548

struct MoveFinder {
    MoveState* FUN_00bca620(uint32_t type, void* fn, void* blk);                       // ret 0xc
    MoveState* FUN_00bcb0b0(uint32_t type, uint32_t size, uint32_t nounId, const char* name);  // ret 0x10
};

struct Tribe { char pad[0x268]; float mField268; };
struct Locomotion {
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
    SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21)
    virtual bool IsActive();                                    // +0x58
    SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    virtual float GetRadius();                                  // +0x74
};
struct CreatureSub { int FUN_00cee330(); };                     // citizen+0x34
struct BoundsHelper {
    void FUN_00acd2d0(void* o);                                 // ret 4
    int FUN_00ac79d0();
    void FUN_00ac7de0(int a, int b);                            // ret 8
};
struct NounMgr { Tribe* FUN_00bfc5f0(); };

struct AuxStruct {
    char pad0[0x61c];
    int mField61c;
};

struct AnimMgr {
    char pad0[8];
    AnimSub mSub;                                               // +8
    char pad9[0x600 - 9];
    MoveStateOwner* mpOwner;                                    // +0x600
    AnimRecord* FUN_00bca2c0();                                 // plain thiscall
    void FUN_00bcb480(MoveState* st, void* creature, void* res, void* fn);   // ret 0x10
};

struct Citizen;
struct Creature {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
    virtual uint32_t GetNounID();                               // +0x20
    SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
    SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
    SLOT(31) SLOT(32)
    virtual void SetTarget(void* o, int a, int b);              // +0x84
    char pad4[0x34 - 4];
    CreatureSub mSub34;                                         // +0x34
    char pad38[0xc0 - 0x38];
    Locomotion mLoco;                                           // +0xc0 (own vtable)
    char padc4[0xb20 - 0xc4];
    AuxStruct* mpAux;                                           // +0xb20
    char padb24[0xb4c - 0xb24];
    AnimMgr* mpAnimMgr;                                         // +0xb4c
    char padb50[0xb64 - 0xb50];
    char mbB64;                                                 // +0xb64
    Tribe* GetTribe();                                          // 0x00c22f50 (citizen)
    int FUN_00c0c160();
    void FUN_00c14750(int v);                                   // ret 4
    char FUN_00c0b700();
};

struct MoveParams {
    char pad0[8];
    SpatialObj* mpTarget;       // +8
    Vec3 mDest;                 // +0xc
    uint32_t mA;                // +0x18
    int mB;                     // +0x1c
    uint32_t mC;                // +0x20
};
struct MoveResult {
    float mF0;
    float mF4;
    float mF8;
    float mFC;
    uint8_t mB10;
    uint8_t mB11;
    char pad12[6];
    int mState;                 // +0x18
    SpatialObj* mpObject;       // +0x1c
};
struct MoveBlock {
    Creature* mpCreature;
    SpatialObj* mpTarget;
    Vec3 mDest;
};

extern const Vec3 kNoDest;      // 0x0169f3b8
extern const float kF1572070;   // 0x01572070
extern const float kF147c21c;   // 0x0147c21c
extern const float kF147c218;   // 0x0147c218
extern const float kF1485720;   // 0x01485720
extern const float kF1471064;   // 0x01471064
extern const float kF13eedb8;   // 0x013eedb8
extern char kMoveName[];        // "Move" 0x0147c2d8
extern char kStrA[];            // 0x01581234
extern char kStrB[];            // 0x0158123c

MoveFinder* __cdecl FUN_00bc9b00();                             // behaviour manager (global)
BoundsHelper* __cdecl FUN_00b3d2b0();
BoundsHelper* __cdecl FUN_00b3d480();
NounMgr* __cdecl NounManager();                                 // 0x00b3d300
float __cdecl FUN_004df2d0(const char* v);
bool __cdecl FUN_00da6270(Citizen* c, int state);
struct Vec3Holder { const Vec3* FUN_00cce910(); };              // thiscall on rec+0x39

static const uint32_t kNounCitizen = 0x18eb4b7;

// @ 0x00dbe520
bool __cdecl FUN_00dbe520(Creature* a1, int a2, int a3, int a4, unsigned flags, MoveResult* res, MoveParams* mp)
{
    (void)a2; (void)a3; (void)a4;
    if (res) res->mpObject = 0;
    Creature* const self = a1;
    Creature* citizen;
    if (self) {
        uint32_t const id = self->GetNounID();
        citizen = self;
        if (id != kNounCitizen) citizen = 0;
    } else {
        citizen = 0;
    }
    Vec3 dest(kNoDest);
    float f18 = 0.0f;
    float f10 = kF1572070;
    float f14 = kF1572070;
    float f1c = kF147c21c;
    SpatialObj* target = 0;
    int ebp = 0;

    if (self->GetNounID() == kNounCitizen) {
        AnimEntry* r = self->mpAnimMgr->mSub.PlayIdleAnimation(0x80, 0);
        if (r) {
            f10 = r->mValue;
            target = r->mpObject;
            goto haveTarget;
        }
        r = self->mpAnimMgr->mSub.PlayIdleAnimation(0, 0x8000000);
        if (r) {
            f10 = r->mValue;
            target = r->mpObject;
            goto haveTarget;
        }
    }
    if (mp) {
        target = mp->mpTarget;
        dest = mp->mDest;
        f18 = (float)mp->mA;
        ebp = mp->mB;
        if (mp->mC > 0) f1c = (float)mp->mC;
    }
haveTarget:
    AnimRecord* const rec = self->mpAnimMgr->FUN_00bca2c0();
    SpatialObj* const tgt = target ? (SpatialObj*)target->Cast(0x1186577) : 0;
    res->mState = 4;
    if (rec) {
        int t = rec->mType;
        if (t == 4 || t == 0x1c) res->mState = t;
    }
    if (tgt) {
        SpatialObj* const old = res->mpObject;
        if (tgt != old) {
            tgt->AddRef2();
            res->mpObject = tgt;
            if (old) old->Release2();
        }
        dest = *tgt->GetPosition();
        f14 = tgt->GetRadius();
        if (flags & 2) {
            void* o = tgt->QueryComponent(0x13f94d4);
            self->SetTarget(o, 1, ebp);
        }
        if (self->mLoco.IsActive()) {
            void* o2 = tgt->QueryComponent(0x17f243b);
            if (o2) FUN_00b3d480()->FUN_00acd2d0(o2);
        }
    } else if (rec && rec->mType == (uint32_t)res->mState && *(uint16_t*)((char*)rec + 0x4b) == 0x31) {
        Vec3 tmp(*((Vec3Holder*)((char*)rec + 0x39))->FUN_00cce910());
        dest = tmp;
    } else {
        if (dest.x == kNoDest.x && dest.y == kNoDest.y && dest.z == kNoDest.z) {
            if (!citizen) return false;
            return FUN_00da6270((Citizen*)citizen, res->mState);
        }
        goto haveDest;
    }
    if (dest.x == kNoDest.x && dest.y == kNoDest.y && dest.z == kNoDest.z) return false;
haveDest:
    if (citizen) {
        CreatureSub* const sub = &citizen->mSub34;
        if (sub->FUN_00cee330()) {
            if (citizen->mpAnimMgr->mSub.PlayIdleAnimation(0x1208d40, 0)) {
                int const a = FUN_00b3d2b0()->FUN_00ac79d0();
                int const b = sub->FUN_00cee330();
                FUN_00b3d2b0()->FUN_00ac7de0(b, a);
            }
        }
    }

    MoveStateOwner* const owner = self->mpAnimMgr->mpOwner;
    int handle;
    MoveResult* resOut;
    if (owner) {
        handle = owner->mMoveHandle;
        if (handle == 0) {
            handle = gMovePool.CreateObject();
            owner->mMoveHandle = handle;
            MoveState* gm = gMovePool.GetObject(handle);
            Tribe* tribe = NounManager()->FUN_00bfc5f0();
            if (citizen) tribe = citizen->GetTribe();
            float spd;
            if (tribe)
                spd = tribe->mField268 * kF1471064;
            else
                spd = self->mLoco.GetRadius() * kF13eedb8;
            gm->mF1b4 = spd + kF1485720;
            gm->mpFunc = (void*)0xdb4a60;
            gm->FUN_00c70110(tgt);
            gm->mF1bc = (f14 + f10) + f18;
            gm->mDestX = dest.x;
            gm->mDestY = dest.y;
            gm->mF1c0 = f1c;
            gm->mF1b8 = f14 + f18;
            gm->mDestZ = dest.z;
            gm->mF1c8 = kF147c218;
            gm->mb244 = self->FUN_00c0c160() != -1;
            gm->mb23c = 0;
        }
        gMovePool.GetObject(handle)->FUN_00db6ef0(&self->mLoco);
        resOut = res;
    } else {
        MoveBlock blk;
        blk.mpCreature = self;
        blk.mpTarget = tgt;
        blk.mDest = dest;
        MoveState* st = FUN_00bc9b00()->FUN_00bca620(0x4eb9c78, (void*)0xdb3e90, &blk);
        if (!st) {
            st = FUN_00bc9b00()->FUN_00bcb0b0(0x4eb9c78, 0x20, self->GetNounID(), kMoveName);
            st->mpFunc224 = (void*)0xdb4a20;
            int const h = gMovePool.CreateObject();
            st->mMoveHandle = h;
            MoveState* gm = gMovePool.GetObject(h);
            float spd;
            if (citizen)
                spd = citizen->GetTribe()->mField268 * kF1471064;
            else
                spd = self->mLoco.GetRadius() * kF13eedb8;
            gm->mF1b4 = spd + kF1485720;
            gm->mpFunc = (void*)0xdb4a60;
            gm->FUN_00c70110(tgt);
            gm->mF1bc = (f14 + f10) + f18;
            gm->mDestX = dest.x;
            gm->mDestY = dest.y;
            gm->mF1c0 = f1c;
            gm->mF1b8 = f14 + f18;
            gm->mDestZ = dest.z;
            gm->mF1c8 = kF147c218;
            gm->mb244 = self->FUN_00c0c160() != -1;
            gm->mI248 = 0;
        }
        resOut = res;
        self->mpAnimMgr->FUN_00bcb480(st, self, resOut, (void*)0xdb3e90);
        gMovePool.GetObject(st->mMoveHandle)->FUN_00db6ef0(&self->mLoco);
    }

    self->FUN_00c14750(1);
    resOut->mF4 = FUN_004df2d0(self->mpAux->mField61c ? kStrA : kStrB);
    resOut->mF8 = 0.0f;
    resOut->mFC = 0.0f;
    resOut->mB10 = self->FUN_00c0b700();
    resOut->mB11 = 0;
    resOut->mF0 = kF1485720;
    self->mbB64 = 0;
    return true;
}
