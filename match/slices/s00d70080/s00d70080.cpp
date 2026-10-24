// Slice s00d70080 -- behaviour-node functions of the SPGonzago creature modules
//   SPCreaturePosseBehavior: WARN_AVATAR_* + AVATAR_PARTY_*
//   SPCreatureSleep:         SLEEP_*
//   SPEatCarcass:            PUKE_* + WAIT_FOR_CARCASS_* + helpers
//
// All behaviour-tree node callbacks are __cdecl with the owning creature as arg0, several unused
// ints, the node state pointer (usually arg5) and sometimes an extra "interactable" holder
// pointer (arg6).  Calls into the creature / locomotion / combatant / behaviour tree are recovered
// __thiscall members (callee pops the stack).  Unknown callees keep their retail address in a
// trailing comment; the equivalence checker resolves those comments to the original addresses.
//
// Deliberately NO raw-offset pointer arithmetic: every touched field is a named member whose
// ordinal position reproduces the retail layout.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV  virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

namespace SP {

struct Vec3 { float x, y, z; };

class cSPCreatureBase;

// ---- locomotion sub-object at creature+0xc0 (own vtable) --------------------------
struct Loco {
    PV8 PV2 PV                                        // 0x00 .. 0x28
    virtual Vec3* GetPosition();                      // +0x2c
    virtual void* Slot30();                           // +0x30
    PV8 PV2                                           // 0x34 .. 0x5c
    virtual Vec3* GetDirection(Vec3* out);            // +0x5c
    PV4 PV                                            // 0x60 .. 0x70
    virtual float GetFootprintRadius();               // +0x74
    PV16 PV8 PV                                       // 0x78 .. 0xd8
    virtual void SlotDC(void* out);                   // +0xdc
    PV4 PV2                                           // 0xe0 .. 0xf4
    virtual bool SlotF8();                            // +0xf8
    bool IsNearGoal();                                // 0x00c42e20
};

// ---- AutoRefCount-like 4-byte handle wrapper ------------------------------------
struct RefObj { PV virtual void Release(); };        // vtable slot 1
struct AutoRefCount { RefObj* mp; void operator=(RefObj* p); };   // 0x00b5f950

// flags word at creature+0xb58: some sites read raw masks, bit 8/9 read as bitfields
union FlagWord {
    uint32_t raw;
    struct { unsigned :8; unsigned f8:1; unsigned f9:1; unsigned f10:1; unsigned :21; } bits;
};

// ---- cCombatant sub-object at creature+0x5a8 (own vtable) -------------------------
struct Combatant {
    PV8 PV8 PV4 PV2                                   // 0x00 .. 0x54 (vtable slots 0..21)
    virtual float GetHealth();                        // +0x58
    uint32_t pad04[13];                               // 0x04 .. 0x38
    float    m38;                                     // +0x38 == creature +0x5e0
    void PartialRepair(float);                        // 0x00bfd1a0
    void FUN_00f924e0(float);                         // 0x00f924e0
};

// ---- the creature's behaviour-stimuli registry (tree +8) --------------------------
struct Stimulus { uint32_t m00, m04, m08; int m0c; };  // +0x0c = handle

struct BehaviorStimuli {
    uint32_t pad[0x1d0 / 4];
    Stimulus* Play(int a, unsigned flags);            // 0x00bc96a0
    void      ClearAll(int a, unsigned flags);        // 0x00bc98f0
    void      Slot7f0(int a, int b, float f, void* c);// 0x00bc97f0
};

struct BehaviorTree {
    uint32_t pad0[2];                                 // 0x00
    BehaviorStimuli mStimuli;                         // 0x08
    int m1d8;                                         // 0x1d8 (retail behaviour id)
};

// ---- the "home" record returned by cSPCreatureBase::GetHomeInfo -------------------
struct SpatialObj { uint32_t pad[0x34 / 4]; Loco mLoco; };   // loco embedded at +0x34

struct HomeInfo {
    uint32_t pad0[0x40 / 4];
    int* m40;                                         // +0x40
    int* m44;                                         // +0x44
    uint32_t pad_48[(0x104 - 0x48) / 4];
    int m104;                                         // +0x104
    uint32_t pad_108[(0x160 - 0x108) / 4];
    SpatialObj* m160;                                 // +0x160
    cSPCreatureBase* m164;                            // +0x164
    Vec3* GetPosition();                              // 0x00c6acc0 (cNearNoun::GetPosition)
};

struct Obj590 { uint32_t pad[0x590 / 4]; float m590; };   // reaches +0x590 (mpB20 target)

class cSPCreatureBase {
public:
    PV8 PV16 PV8 PV                                   // vtable slots 0 .. 32
    virtual void AssignInteractor(Combatant* c, int a, int b);   // slot 33 = +0x84

    uint8_t  pad_004[0xc0 - 0x004];                   // 0x004 .. 0xc0
    Loco     mLoco;                                   // 0xc0
    uint8_t  pad_c4[0x135 - 0xc4];                    // 0xc4 .. 0x135
    int8_t   m135;                                    // 0x135
    uint8_t  pad_136[0x5a8 - 0x136];                  // 0x136 .. 0x5a8
    Combatant mCombatant;                             // 0x5a8
    uint8_t  pad_5e4[0xb20 - 0x5e4];                  // 0x5e4 .. 0xb20
    Obj590*  mpB20;                                   // 0xb20
    uint8_t  pad_b24[0x28];                           // 0xb24 .. 0xb4c
    BehaviorTree* mpBehaviorTree;                     // 0xb4c
    void*    mpB50;                                   // 0xb50
    void*    mpB54;                                   // 0xb54
    FlagWord mFlags;                                  // 0xb58
    uint8_t  pad_b5c[2];                              // 0xb5c .. 0xb5e
    int8_t   mB5e;                                    // 0xb5e
    uint8_t  pad_b5f[0xb84 - 0xb5f];                  // 0xb5f .. 0xb84
    float    mB84;                                    // 0xb84
    uint8_t  pad_b88[0xe38 - 0xb88];                  // 0xb88 .. 0xe38
    int8_t   mE38;                                    // 0xe38
    uint8_t  pad_e39[0xf90 - 0xe39];                  // 0xe39 .. 0xf90
    int8_t   mF90;                                    // 0xf90

    cSPCreatureBase* GetTargetAsCreature();           // 0x00c0ee70
    void* ApplyCombatTarget();                        // 0x00c0ee90
    bool  FUN_00c0b770();                             // 0x00c0b770
    HomeInfo* GetHomeInfo();                          // 0x00c04590
    float FUN_00c0bb10();                             // 0x00c0bb10
    float FUN_00c0b9c0();                             // 0x00c0b9c0
    int   CountValid();                               // 0x00c0f570
    void  FUN_00c14750(int a);                        // 0x00c14750
    void  FUN_00c19940(int a);                        // 0x00c19940
    void  FUN_00c0d1e0(const Vec3* p);                // 0x00c0d1e0
    void  FUN_00c0b370(unsigned id);                  // 0x00c0b370
    int   PlayAnimation(unsigned id, int a, int b);                       // 0x00c12190
    int   InterruptAnimation(unsigned id, int a, int b);                  // 0x00c12310
    bool  AnimationFinished(int x) const;                                 // 0x00c123f0
    bool  AnimationFinishedHandle(int x) const;                           // 0x00c12400
    int   PlayAnimationWithTarget(unsigned id, const Vec3* t, int b);     // 0x00c14910
    int   PlayAnimationWithTarget2(unsigned id, void* t, int a, int b);   // 0x00c14940
    bool  WaitForAnimEventOrEnd(unsigned a, unsigned& out, unsigned id, void* h, bool b);  // 0x00c14ef0
    void  MoveToPointAtSpeed(int stt, const Vec3* p, float f0, float f1);                   // 0x00c1c1d0
    void  MoveToPointAndFacingAtSpeed(int stt, const Vec3* p, const Vec3* d, float f0, float f1); // 0x00c1c5c0
};

struct cGameNounManager {
    cSPCreatureBase* GetAvatar();                     // 0x00b1fdb0
};

struct LayoutMgr { bool LookupA(); };                 // 0x00af0af0 (thiscall, no stack args)
struct RandomLCG { int RandomUint32Uniform(unsigned n); };  // 0x00a68fb0

// the interaction-target holder (creature+... passed as arg6)
struct TargetOwner {
    PV8 PV8 PV4 PV2 PV                                // vtable slots 0 .. 22
    virtual cSPCreatureBase* GetTargetNPC(unsigned id);   // slot 23 = +0x5c
};
struct TargetHolder { uint32_t m0; TargetOwner* m4; };

struct WARN_AVATAR_memory_block {
    Vec3* FindAnimTargetPosition(Vec3* out, cSPCreatureBase* self);
};

// ---- free helpers (address = comment) -------------------------------------------
cGameNounManager* NounManager();                                  // 0x00b3d300
struct cPlanetModel {
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* c, float lo, float hi);  // 0x00b81780
};
cPlanetModel* PlanetModel();                                      // 0x00b3d350
cSPCreatureBase* GetAnimalFromStimulus(Stimulus* stim);           // 0x00d99980
cSPCreatureBase* FUN_00d99500(void* p);                           // 0x00d99500
void EatFood(cSPCreatureBase* c, float f, unsigned id, int8_t b); // 0x00d85ad0
Vec3* FUN_0059aed0(Vec3* out, const void* basis, void* x);        // 0x0059aed0
void* __stdcall FUN_0067cac0(unsigned id);                        // 0x0067cac0
struct HandleObj { void FUN_0067c830(); };                        // 0x0067c830 (thiscall)
void* __stdcall FUN_00af13b0(cSPCreatureBase* self, int a, int b); // 0x00af13b0
void  FUN_00f47380_operator_delete_array(void* p);                // 0x00f47380
cSPCreatureBase* interface_cast_creature(void* p);                // 0x00d57750
Vec3* normalized_safe(Vec3* out, const Vec3* in);                 // 0x00449c20

// ---- retail globals (address = comment) -----------------------------------------
extern const float kEps_13ec4b8;   // 0x13ec4b8
extern const float kA_13ec4b4;     // 0x13ec4b4
extern const float kA_1687a0c;     // 0x1687a0c
extern const float kA_1687a20;     // 0x1687a20
extern const float kA_1687a28;     // 0x1687a28
extern const float kA_1687a40;     // 0x1687a40
extern const float kA_1582e60;     // 0x1582e60
extern const float kA_169edd0;     // 0x169edd0
extern const float kA_169edd4;     // 0x169edd4
extern const float kA_169edd8;     // 0x169edd8
extern const float kA_147bcd8;     // 0x147bcd8
extern const float kA_13f08e4;     // 0x13f08e4  (1.25)
extern const float kZero;          // 0x1485378
extern const float kOne;           // 0x1485720
extern const float kFive;          // 0x1486110
extern const float kThree;         // 0x13eb95c
extern const float kTwo;           // 0x1470f1c
extern const float kSeven;         // 0x13f8698
extern const float kThree2;        // 0x13eb8c8  (0.3)
extern const char  gBasis_169ee04[];   // 0x169ee04
extern unsigned gU_15840fc;        // 0x15840fc
extern unsigned gU_1584100;        // 0x1584100
extern unsigned gU_1584104;        // 0x1584104
extern RandomLCG gRand_1601760;    // 0x1601760

// ---- state records ---------------------------------------------------------------
struct EatState {                    // FUN_00d70ed0 / FUN_00d70b10 node state
    int         m00;                 // +0x00
    AutoRefCount m04;                // +0x04
    int8_t      m08;                 // +0x08
    int8_t      m09;                 // +0x09
    uint8_t     pad0a[2];
    int         m0c;                 // +0x0c
    int         m10;                 // +0x10
    int         m14;                 // +0x14
};
struct EatCtx { uint32_t m0; cSPCreatureBase* m4; int8_t m8; int8_t m9; };  // FUN_00d70b10 arg2

// argument block built for the locomotion virtual slot +0xdc
struct SlotDCArg {
    RefObj*  m00;                     // +0x00 (filled in by slot 0xdc)
    uint32_t m04, m08, m0c, m10;
    float    m14, m18, m1c, m20;
    uint32_t m24;
    uint32_t pad28[(0x4c - 0x28) / 4];
    int8_t   m4c;
    uint8_t  pad4d[3];
    uint32_t m50, m54, m58, m5c;
    float    m60, m64, m68, m6c, m70;
};

bool WARN_AVATAR_Tick(cSPCreatureBase* self, int, int, int, int, int* st);
bool AVATAR_PARTY_Activate(cSPCreatureBase* self, int, int, int, int, int* st);
bool WARN_AVATAR_Activate(cSPCreatureBase* self, int, int, int, int, int* st);
bool SLEEP_Tick(cSPCreatureBase* self, int, int, int, unsigned a3, int* st, int, float dt);
void SLEEP_Deactivate(cSPCreatureBase* self, int, int, int, int, int* st);
bool PUKE_Activate(cSPCreatureBase* self, int, int, int, int, int* st);
bool WAIT_FOR_CARCASS_Activate(cSPCreatureBase* self, int, int, int, int, int st5, TargetHolder* holder);
bool WAIT_FOR_CARCASS_BABY_Tick(cSPCreatureBase* self, int, int, int, int, int* st);

}  // namespace SP

using namespace SP;

void FUN_00d70340(cSPCreatureBase* self, int, int, int, int, int* st);      // 0x00d70340
float FUN_00d704f0(cSPCreatureBase* self);                                    // 0x00d704f0
bool  FUN_00d70510(cSPCreatureBase* self, int, int, int, int, int* st);       // 0x00d70510
void  SP::SLEEP_Deactivate(cSPCreatureBase* self, int, int, int, int, int* st); // 0x00d70560
float FUN_00d705b0(cSPCreatureBase* self);                                    // 0x00d705b0
void  FUN_00d70b10(float dt, cSPCreatureBase* self, EatCtx* ctx);             // 0x00d70b10
bool  FUN_00d70ed0(cSPCreatureBase* self, int, int, int, int, EatState* st, TargetHolder* holder);  // 0x00d70ed0

// ==================================================================================
// @ 0xd70080
Vec3* SP::WARN_AVATAR_memory_block::FindAnimTargetPosition(Vec3* out, cSPCreatureBase* self)
{
    (void)this;
    cSPCreatureBase* avatar = NounManager()->GetAvatar();
    Vec3* ap = avatar->mLoco.GetPosition();
    out->x = ap->x;
    out->y = ap->y;
    out->z = ap->z;

    Vec3* sp = self->mLoco.GetPosition();
    Vec3* ap2 = avatar->mLoco.GetPosition();
    float dy = ap2->y - sp->y;
    float dz = ap2->z - sp->z;
    float dx = ap2->x - sp->x;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + kEps_13ec4b8);
    float nx = dx * inv, ny = dy * inv, nz = dz * inv;

    Vec3 face;
    Vec3* fp = self->mLoco.GetDirection(&face);
    float dot = fp->x * nx + fp->y * ny + fp->z * nz;
    if (dot < 0.0f) {
        void* x = self->mLoco.Slot30();
        Vec3 tmp;
        Vec3* v = FUN_0059aed0(&tmp, gBasis_169ee04, x);
        float vx = v->x * kFive;
        float vy = v->y * kFive;
        float vz = v->z * kFive;
        float dot2 = v->x * fp->x + v->y * fp->y + v->z * fp->z;
        Vec3* p = self->mLoco.GetPosition();
        if (dot2 > kZero) {
            out->x = p->x + vx;
            out->y = p->y + vy;
            out->z = p->z + vz;
        } else {
            out->x = p->x - vx;
            out->y = p->y - vy;
            out->z = p->z - vz;
        }
    }
    return out;
}

// ==================================================================================
// @ 0xd70280
bool SP::WARN_AVATAR_Tick(cSPCreatureBase* self, int, int, int, int, int* st)
{
    Vec3 va, vb;
    switch (*st) {
    case 0:
        if (self->AnimationFinishedHandle(st[1])) {
            *st = 1;
            st[2] = self->PlayAnimationWithTarget(
                0xf403b869,
                ((WARN_AVATAR_memory_block*)st)->FindAnimTargetPosition(&vb, self), -1);
        }
        break;
    case 1: {
        Vec3* p = ((WARN_AVATAR_memory_block*)st)->FindAnimTargetPosition(&va, self);
        self->FUN_00c0d1e0(p);
        if (self->AnimationFinishedHandle(st[2]))
            return false;
        break;
    }
    }
    return true;
}

// ==================================================================================
// @ 0xd70310
bool SP::AVATAR_PARTY_Activate(cSPCreatureBase* self, int, int, int, int, int* st)
{
    if (st)
        st[2] = 0;
    self->FUN_00c0b370(0x5406e32d);
    st[1] = 0;
    return true;
}

// ==================================================================================
// @ 0xd70340
void FUN_00d70340(cSPCreatureBase* self, int, int, int, int, int* st)
{
    self->FUN_00c0b370(0xffffffff);
    self->mpBehaviorTree->mStimuli.ClearAll(0, 0x40000000);
    void* saved = (void*)st[2];
    void* cur = self->ApplyCombatTarget();
    if (saved == cur)
        self->AssignInteractor(0, 0, 0);
    RefObj* r = (RefObj*)st[2];
    if (r)
        r->Release();
}

// ==================================================================================
// @ 0xd703a0
bool SP::WARN_AVATAR_Activate(cSPCreatureBase* self, int, int, int, int, int* st)
{
    Stimulus* stim = self->mpBehaviorTree->mStimuli.Play(0, 0x80);
    if (stim) {
        cSPCreatureBase* a = GetAnimalFromStimulus(stim);
        cSPCreatureBase* c = FUN_00d99500(a);
        if (c) {
            self->AssignInteractor(&c->mCombatant, 1, 0);

            SlotDCArg arg;
            arg.m00 = 0;
            arg.m04 = 0;
            arg.m08 = 0;
            arg.m14 = kA_169edd0;
            arg.m18 = kA_169edd4;
            arg.m1c = kA_169edd8;
            arg.m20 = kOne;
            arg.m24 = 0;
            arg.m4c = 0;
            arg.m50 = 0;
            arg.m54 = 0;
            arg.m58 = 0;
            arg.m5c = 0;
            arg.m60 = kTwo;
            arg.m64 = kA_13ec4b4;
            arg.m68 = kA_147bcd8;
            arg.m6c = 0.0f;
            arg.m70 = 0.0f;
            self->mLoco.SlotDC(&arg);

            if (arg.m00 && *(int*)((char*)arg.m00 - 4) != 0)
                FUN_00f47380_operator_delete_array(arg.m00);

            int h = self->InterruptAnimation(0x92314082, -1, 0);
            st[1] = h;
            st[0] = 0;
            return true;
        }
    }
    return false;
}

// ==================================================================================
// @ 0xd704f0
float FUN_00d704f0(cSPCreatureBase* self)
{
    void* m = FUN_00af13b0(self, 2, 0);
    if (((LayoutMgr*)m)->LookupA())
        return 1.0f;
    return 0.0f;
}

// ==================================================================================
// @ 0xd70510
bool FUN_00d70510(cSPCreatureBase* self, int, int, int, int, int* st)
{
    if (self->CountValid() > 0) {
        st[0] = 0;
        st[1] = self->PlayAnimation(0x3a74a08, 1, -1);
        return true;
    }
    st[0] = 1;
    st[1] = 0;
    return true;
}

// ==================================================================================
// @ 0xd70560
void SP::SLEEP_Deactivate(cSPCreatureBase* self, int, int, int, int, int* st)
{
    self->mFlags.raw &= 0xfffffbff;
    self->mE38 = 0;
    if (!self->mB5e && st[0] == 4)
        self->InterruptAnimation(0x565220a, -1, 0);
    self->FUN_00c14750(0);
}

// ==================================================================================
// @ 0xd705b0
float FUN_00d705b0(cSPCreatureBase* self)
{
    cSPCreatureBase* c = self->GetHomeInfo()->m164;
    if (c && c->mpBehaviorTree->m1d8 == 0x2d852f4 && (c->mFlags.raw & 0x400))
        return 1.0f;
    return 0.0f;
}

// ==================================================================================
// @ 0xd705f0
bool SP::SLEEP_Tick(cSPCreatureBase* self, int, int, int, unsigned a3, int* st, int, float dt)
{
    if (self->mE38) {
        float hp = self->mCombatant.GetHealth();
        unsigned fl = self->mFlags.raw;
        float mult = ((fl >> 8) & 1) ? kA_1687a28 : kA_1687a20;
        self->mCombatant.PartialRepair(hp * mult * dt);
    }

    if (!self->FUN_00c0b770()) {
        cSPCreatureBase* c = (cSPCreatureBase*)self->GetHomeInfo()->m164;
        if (!c || c->mpBehaviorTree->m1d8 != 0x2d852f4)
            return false;
    } else {
        if (!((LayoutMgr*)FUN_00af13b0(self, 2, 0))->LookupA())
            return false;
    }

    Vec3 pt;
    switch (*st) {
    case 0: {
        unsigned tmp;
        if (self->WaitForAnimEventOrEnd(gU_15840fc, tmp, 0x3a74a08, 0, 1))
            self->FUN_00c19940(0);
        if (self->AnimationFinishedHandle(st[1])) {
            self->FUN_00c14750(0);
            *st = 2;
            return true;
        }
        break;
    }
    case 1: {
        if (!self->FUN_00c0b770()) {
            // near the home: look at the creature currently there
            cSPCreatureBase* c = (cSPCreatureBase*)self->GetHomeInfo()->m164;
            float tR = c->mLoco.GetFootprintRadius();
            float sr = self->mLoco.GetFootprintRadius();
            int count = self->GetHomeInfo()->m104;
            float lo = tR * tR;
            float hi = sqrtf((float)count * sr * sr + tR);
            Vec3 ctr = *c->mLoco.GetPosition();
            cPlanetModel* pm = PlanetModel();
            pm->MakeRandomWorldPosition(&pt, &ctr, lo, hi);
        } else {
            HomeInfo* h = self->GetHomeInfo();
            int count = (int)(h->m44 - h->m40) - h->m104;
            if (count < 0)
                count = 0;
            SpatialObj* so = self->GetHomeInfo()->m160;
            float f40 = (so != 0) ? so->mLoco.GetFootprintRadius() : 0.0f;
            float sr = self->mLoco.GetFootprintRadius();
            float sum = sr + f40;
            float r125 = self->mLoco.GetFootprintRadius() * kA_13f08e4;
            float dist = sqrtf(sum * sum + (float)count * r125 * r125);
            Vec3 ctr = *self->GetHomeInfo()->GetPosition();
            cPlanetModel* pm = PlanetModel();
            pm->MakeRandomWorldPosition(&pt, &ctr, f40, dist);
        }
        if (!self->mLoco.SlotF8())
            self->FUN_00c14750(0);
        self->MoveToPointAtSpeed(2, &pt, kThree2, kTwo);
        *st = 2;
        return true;
    }
    case 2:
        if (self->mLoco.IsNearGoal()) {
            *st = 3;
            st[1] = self->PlayAnimation(0x5652208, 1, -1);
            return true;
        }
        break;
    case 3:
        if (self->AnimationFinishedHandle(st[1])) {
            *st = 4;
            self->mFlags.raw |= 0x400;
            self->mE38 = 1;
            return true;
        }
        break;
    case 4:
        if ((self->mF90 || (a3 & 0x180000)) && self->AnimationFinishedHandle(st[1]))
            st[1] = self->InterruptAnimation(0x5652209, -1, 0);
        break;
    }
    return true;
}

// ==================================================================================
// @ 0xd70ab0
bool SP::PUKE_Activate(cSPCreatureBase* self, int, int, int, int, int* st)
{
    int handle = -1;
    Stimulus* stim = self->mpBehaviorTree->mStimuli.Play(0, 0x20000000);
    if (stim)
        handle = stim->m0c;
    st[0] = self->PlayAnimation(0x931fdcda, 1, handle);
    unsigned fl = self->mFlags.raw;
    if ((fl >> 9) & 1) {
        HandleObj* h = (HandleObj*)FUN_0067cac0(0xec1190b1);
        h->FUN_0067c830();
    }
    return true;
}

// ==================================================================================
// @ 0xd70b10
void FUN_00d70b10(float dt, cSPCreatureBase* self, EatCtx* ctx)
{
    if (ctx && ctx->m4 && self) {
        float f = kA_1687a40 * dt;
        ctx->m4->mB84 -= f;
        EatFood(self, f, 0x333b8596, ctx->m8);
        if (ctx->m9) {
            float v = kA_1582e60 * dt + self->mCombatant.m38;
            float hp = self->mCombatant.GetHealth();
            v = (v > 0.0f) ? v : 0.0f;
            v = (v < hp) ? v : hp;
            self->mCombatant.FUN_00f924e0(v);
        }
    }
}

// ==================================================================================
// @ 0xd70bf0
bool SP::WAIT_FOR_CARCASS_Activate(cSPCreatureBase* self, int, int, int, int, int, TargetHolder* holder)
{
    cSPCreatureBase* t = self->GetTargetAsCreature();
    if (!(t && t->m135 && t->mB5e)) {
        if (!holder)
            return false;
        TargetOwner* o = holder->m4;
        if (!o)
            return false;
        t = o->GetTargetNPC(0xce9f6639);
    }
    if (t && t->m135 && t->mB5e) {
        self->AssignInteractor(&t->mCombatant, 1, 0);
        return true;
    }
    return false;
}

// ==================================================================================
// @ 0xd70c70
bool SP::WAIT_FOR_CARCASS_BABY_Tick(cSPCreatureBase* self, int, int, int, int, int* st)
{
    cSPCreatureBase* t = self->GetTargetAsCreature();
    if (!(t && t->mB5e)) {
        Stimulus* stim = self->mpBehaviorTree->mStimuli.Play(0x40000, 0);
        if (stim) {
            t = GetAnimalFromStimulus(stim);
            if (!t)
                return false;
            if (t->mB5e)
                self->AssignInteractor(&t->mCombatant, 1, 0);
        }
    }
    if (!t || !t->mB5e || !t->m135)
        return false;

    switch (*st) {
    case 0: {
        Vec3 d;
        Vec3* sp = self->mLoco.GetPosition();
        Vec3* tp = t->mLoco.GetPosition();
        d.x = tp->x - sp->x;
        d.y = tp->y - sp->y;
        d.z = tp->z - sp->z;
        Vec3 nd;
        normalized_safe(&nd, &d);
        self->MoveToPointAndFacingAtSpeed(2, t->mLoco.GetPosition(), &nd, kThree, kFive);
        if (self->mLoco.IsNearGoal()) {
            self->PlayAnimation(0x120c5dd9, 1, -1);
            *st = 1;
        }
        break;
    }
    case 1:
        if (self->AnimationFinished(0)) {
            if (t->mpB50) {
                cSPCreatureBase* ia = interface_cast_creature(&t->mpB50);
                if (ia)
                    ia->mpBehaviorTree->mStimuli.Slot7f0(0, 1, kFive, self);
            }
            self->PlayAnimation(0x120c5dd9, 1, -1);
        }
        break;
    case 2:
        if (self->mLoco.IsNearGoal())
            self->PlayAnimation(0x520c5dca, 1, -1);
        break;
    }

    self->MoveToPointAtSpeed(2, t->mLoco.GetPosition(), kFive, kSeven);
    if (self->mLoco.IsNearGoal())
        self->PlayAnimation(0xd1dce195, 1, -1);
    return true;
}

// ==================================================================================
// @ 0xd70ed0
bool FUN_00d70ed0(cSPCreatureBase* self, int, int, int, int, EatState* st, TargetHolder* holder)
{
    if (st)
        st->m04.mp = 0;
    st->m00 = 0;
    if (st->m04.mp) {
        RefObj* old = st->m04.mp;
        st->m04.mp = 0;
        old->Release();
    }
    st->m08 = 0;
    st->m09 = 1;
    st->m0c = 0;
    float f = self->mpB20->m590;
    st->m10 = (f > kZero) ? (int)gU_1584100 : (int)gU_1584104;
    st->m14 = -1;

    cSPCreatureBase* t = self->GetTargetAsCreature();
    if (!(t && t->mB5e && t->m135 && 0.0f < t->FUN_00c0bb10())) {
        if (!holder)
            return false;
        TargetOwner* o = holder->m4;
        if (!o)
            return false;
        t = o->GetTargetNPC(0xce9f6639);
    }
    if (t && t->mB5e && t->m135 && t->FUN_00c0bb10() > 0.0f) {
        self->AssignInteractor(&t->mCombatant, 0, 0);
        st->m04 = (RefObj*)t;
        return true;
    }
    return false;
}