// src/game/SPGonzago/SPCreaturePosseBehavior.cpp -- migrated from slice(s) s00d70080, s00d6f1c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreaturePosseBehavior.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cGameNounManager.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include <math.h>
#pragma warning(disable : 4100)

// ---- items of slice s00d6f1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cBehaviorStimuli {
    uint8_t pad000[8];                                  // +0x00 .. +0x07

    void ClearAll(uint32_t mask, uint32_t flags);        // 0x00bc98f0
};
}
namespace SP {
struct cBehaviorTree {
    uint8_t        pad000[8];                           // +0x00 .. +0x07
    cBehaviorStimuli mStimuli;                          // +0x08
};
}
namespace SP {
class cBehaviorActor {
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
    virtual void v080();
    virtual void PushTargetAction(void* pTarget, int mode, int flags); // +0x84

    uint8_t        pad004[0xb48];                       // +0x004 .. +0xb4b
    cBehaviorTree* mpBehavior;                          // +0xb4c
};
}
namespace SP {
struct cActionStatus {
    int32_t mResult;                                    // +0x00
    int32_t mDetail;                                    // +0x04
};
}
namespace SP {
void __cdecl CRY_TO_AVATAR_Tick(cBehaviorActor* pActor, cActionStatus* pStatus);        // 0x00d6f800
}
namespace SP {
void __cdecl AVATAR_PARTY_Tick(cBehaviorActor* pActor, cActionStatus* pStatus);         // 0x00d6f910
}
namespace SP {
void __cdecl POSSE_PARTY_Tick(cBehaviorActor* pActor, cActionStatus* pStatus);          // 0x00d6fa60
}
// ---- items of slice s00d6f1c0 end

// ---- items of slice s00d70080 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV  virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
class cSPCreatureBase_s00d7_0080;
}
namespace SP {
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
}
namespace SP {
union FlagWord {
    uint32_t raw;
    struct { unsigned :8; unsigned f8:1; unsigned f9:1; unsigned f10:1; unsigned :21; } bits;
};
}
namespace SP {
struct Combatant {
    PV8 PV8 PV4 PV2                                   // 0x00 .. 0x54 (vtable slots 0..21)
    virtual float GetHealth();                        // +0x58
    uint32_t pad04[13];                               // 0x04 .. 0x38
    float    m38;                                     // +0x38 == creature +0x5e0
    void PartialRepair(float);                        // 0x00bfd1a0
    void FUN_00f924e0(float);                         // 0x00f924e0
};
}
namespace SP {
struct Stimulus { uint32_t m00, m04, m08; int m0c; };  // +0x0c = handle
}
namespace SP {
struct BehaviorStimuli {
    uint32_t pad[0x1d0 / 4];
    Stimulus* Play(int a, unsigned flags);            // 0x00bc96a0
    void      ClearAll(int a, unsigned flags);        // 0x00bc98f0
    void      Slot7f0(int a, int b, float f, void* c);// 0x00bc97f0
};
}
namespace SP {
struct BehaviorTree {
    uint32_t pad0[2];                                 // 0x00
    BehaviorStimuli mStimuli;                         // 0x08
    int m1d8;                                         // 0x1d8 (retail behaviour id)
};
}
namespace SP {
struct SpatialObj { uint32_t pad[0x34 / 4]; Loco mLoco; };   // loco embedded at +0x34
}
namespace SP {
struct HomeInfo {
    uint32_t pad0[0x40 / 4];
    int* m40;                                         // +0x40
    int* m44;                                         // +0x44
    uint32_t pad_48[(0x104 - 0x48) / 4];
    int m104;                                         // +0x104
    uint32_t pad_108[(0x160 - 0x108) / 4];
    SpatialObj* m160;                                 // +0x160
    cSPCreatureBase_s00d7_0080* m164;                            // +0x164
    Vec3* GetPosition();                              // 0x00c6acc0 (cNearNoun::GetPosition)
};
}
namespace SP {
struct Obj590 { uint32_t pad[0x590 / 4]; float m590; };   // reaches +0x590 (mpB20 target)
}
namespace SP {
class cSPCreatureBase_s00d7_0080 {
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

    cSPCreatureBase_s00d7_0080* GetTargetAsCreature();           // 0x00c0ee70
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
}
namespace SP {
struct cGameNounManager_s00d7_0080 {
    cSPCreatureBase_s00d7_0080* GetAvatar();                     // 0x00b1fdb0
};
}
namespace SP {
struct WARN_AVATAR_memory_block {
    Vec3* FindAnimTargetPosition(Vec3* out, cSPCreatureBase_s00d7_0080* self);
};
}
namespace SP {
cGameNounManager_s00d7_0080* NounManager();                                  // 0x00b3d300
}
namespace SP {
Vec3* FUN_0059aed0(Vec3* out, const void* basis, void* x);        // 0x0059aed0
}
namespace SP {
extern const float kEps_13ec4b8;   // 0x13ec4b8
}
namespace SP {
extern const float kZero;          // 0x1485378
}
namespace SP {
extern const float kFive;          // 0x1486110
}
namespace SP {
extern const char  gBasis_169ee04[];   // 0x169ee04
}
namespace SP {
bool WARN_AVATAR_Tick(cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st);
}
namespace SP {
bool AVATAR_PARTY_Activate(cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st);
}
// ---- items of slice s00d70080 end

// @ 0x00d6f800
namespace SP {
void __cdecl CRY_TO_AVATAR_Tick(cBehaviorActor* pActor, cActionStatus* pStatus)
{
    (void)pActor;
    (void)pStatus;
}
}  // namespace SP

// @ 0x00d6f910
namespace SP {
void __cdecl AVATAR_PARTY_Tick(cBehaviorActor* pActor, cActionStatus* pStatus)
{
    (void)pActor;
    (void)pStatus;
}
}  // namespace SP

// @ 0x00d6fa60
namespace SP {
void __cdecl POSSE_PARTY_Tick(cBehaviorActor* pActor, cActionStatus* pStatus)
{
    (void)pActor;
    (void)pStatus;
}
}  // namespace SP

// @ 0x00d6fd70
namespace SP {
void __fastcall FUN_00d6fd70(cBehaviorActor* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00d6fef0
namespace SP {
void __fastcall FUN_00d6fef0(cBehaviorActor* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00d70080
SP::Vec3* SP::WARN_AVATAR_memory_block::FindAnimTargetPosition(SP::Vec3* out, SP::cSPCreatureBase_s00d7_0080* self)
{
    (void)this;
    SP::cSPCreatureBase_s00d7_0080* avatar = SP::NounManager()->GetAvatar();
    SP::Vec3* ap = avatar->mLoco.GetPosition();
    out->x = ap->x;
    out->y = ap->y;
    out->z = ap->z;

    SP::Vec3* sp = self->mLoco.GetPosition();
    SP::Vec3* ap2 = avatar->mLoco.GetPosition();
    float dy = ap2->y - sp->y;
    float dz = ap2->z - sp->z;
    float dx = ap2->x - sp->x;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + SP::kEps_13ec4b8);
    float nx = dx * inv, ny = dy * inv, nz = dz * inv;

    SP::Vec3 face;
    SP::Vec3* fp = self->mLoco.GetDirection(&face);
    float dot = fp->x * nx + fp->y * ny + fp->z * nz;
    if (dot < 0.0f) {
        void* x = self->mLoco.Slot30();
        SP::Vec3 tmp;
        SP::Vec3* v = SP::FUN_0059aed0(&tmp, SP::gBasis_169ee04, x);
        float vx = v->x * SP::kFive;
        float vy = v->y * SP::kFive;
        float vz = v->z * SP::kFive;
        float dot2 = v->x * fp->x + v->y * fp->y + v->z * fp->z;
        SP::Vec3* p = self->mLoco.GetPosition();
        if (dot2 > SP::kZero) {
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

// @ 0x00d70280
bool SP::WARN_AVATAR_Tick(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
{
    SP::Vec3 va, vb;
    switch (*st) {
    case 0:
        if (self->AnimationFinishedHandle(st[1])) {
            *st = 1;
            st[2] = self->PlayAnimationWithTarget(
                0xf403b869,
                ((SP::WARN_AVATAR_memory_block*)st)->FindAnimTargetPosition(&vb, self), -1);
        }
        break;
    case 1: {
        SP::Vec3* p = ((SP::WARN_AVATAR_memory_block*)st)->FindAnimTargetPosition(&va, self);
        self->FUN_00c0d1e0(p);
        if (self->AnimationFinishedHandle(st[2]))
            return false;
        break;
    }
    }
    return true;
}

// @ 0x00d70310
bool SP::AVATAR_PARTY_Activate(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
{
    if (st)
        st[2] = 0;
    self->FUN_00c0b370(0x5406e32d);
    st[1] = 0;
    return true;
}
