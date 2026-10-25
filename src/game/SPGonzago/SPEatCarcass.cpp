// src/game/SPGonzago/SPEatCarcass.cpp -- migrated from slice(s) s00d70080 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPEatCarcass.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include <math.h>

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
struct RefObj { PV virtual void Release(); };        // vtable slot 1
}
namespace SP {
struct AutoRefCount { RefObj* mp; void operator=(RefObj* p); };   // 0x00b5f950
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
struct TargetOwner {
    PV8 PV8 PV4 PV2 PV                                // vtable slots 0 .. 22
    virtual cSPCreatureBase_s00d7_0080* GetTargetNPC(unsigned id);   // slot 23 = +0x5c
};
}
namespace SP {
struct TargetHolder { uint32_t m0; TargetOwner* m4; };
}
namespace SP {
cSPCreatureBase_s00d7_0080* GetAnimalFromStimulus(Stimulus* stim);           // 0x00d99980
}
namespace SP {
void EatFood(cSPCreatureBase_s00d7_0080* c, float f, unsigned id, int8_t b); // 0x00d85ad0
}
namespace SP {
void* __stdcall FUN_0067cac0(unsigned id);                        // 0x0067cac0
}
namespace SP {
struct HandleObj { void FUN_0067c830(); };                        // 0x0067c830 (thiscall)
}
namespace SP {
cSPCreatureBase_s00d7_0080* interface_cast_creature(void* p);                // 0x00d57750
}
namespace SP {
Vec3* normalized_safe(Vec3* out, const Vec3* in);                 // 0x00449c20
}
namespace SP {
extern const float kA_1687a40;     // 0x1687a40
}
namespace SP {
extern const float kA_1582e60;     // 0x1582e60
}
namespace SP {
extern const float kZero;          // 0x1485378
}
namespace SP {
extern const float kFive;          // 0x1486110
}
namespace SP {
extern const float kThree;         // 0x13eb95c
}
namespace SP {
extern const float kSeven;         // 0x13f8698
}
namespace SP {
extern unsigned gU_1584100;        // 0x1584100
}
namespace SP {
extern unsigned gU_1584104;        // 0x1584104
}
namespace SP {
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
}
namespace SP {
struct EatCtx { uint32_t m0; cSPCreatureBase_s00d7_0080* m4; int8_t m8; int8_t m9; };  // FUN_00d70b10 arg2
}
namespace SP {
bool PUKE_Activate(cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st);
}
namespace SP {
bool WAIT_FOR_CARCASS_Activate(cSPCreatureBase_s00d7_0080* self, int, int, int, int, int st5, TargetHolder* holder);
}
namespace SP {
bool WAIT_FOR_CARCASS_BABY_Tick(cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st);
}
void  FUN_00d70b10(float dt, SP::cSPCreatureBase_s00d7_0080* self, SP::EatCtx* ctx);             // 0x00d70b10
bool  FUN_00d70ed0(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, SP::EatState* st, SP::TargetHolder* holder);  // 0x00d70ed0
// ---- items of slice s00d70080 end

// @ 0x00d70ab0
bool SP::PUKE_Activate(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
{
    int handle = -1;
    SP::Stimulus* stim = self->mpBehaviorTree->mStimuli.Play(0, 0x20000000);
    if (stim)
        handle = stim->m0c;
    st[0] = self->PlayAnimation(0x931fdcda, 1, handle);
    unsigned fl = self->mFlags.raw;
    if ((fl >> 9) & 1) {
        SP::HandleObj* h = (SP::HandleObj*)SP::FUN_0067cac0(0xec1190b1);
        h->FUN_0067c830();
    }
    return true;
}

// @ 0x00d70b10
void FUN_00d70b10(float dt, SP::cSPCreatureBase_s00d7_0080* self, SP::EatCtx* ctx)
{
    if (ctx && ctx->m4 && self) {
        float f = SP::kA_1687a40 * dt;
        ctx->m4->mB84 -= f;
        SP::EatFood(self, f, 0x333b8596, ctx->m8);
        if (ctx->m9) {
            float v = SP::kA_1582e60 * dt + self->mCombatant.m38;
            float hp = self->mCombatant.GetHealth();
            v = (v > 0.0f) ? v : 0.0f;
            v = (v < hp) ? v : hp;
            self->mCombatant.FUN_00f924e0(v);
        }
    }
}

// @ 0x00d70bf0
bool SP::WAIT_FOR_CARCASS_Activate(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int, SP::TargetHolder* holder)
{
    SP::cSPCreatureBase_s00d7_0080* t = self->GetTargetAsCreature();
    if (!(t && t->m135 && t->mB5e)) {
        if (!holder)
            return false;
        SP::TargetOwner* o = holder->m4;
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

// @ 0x00d70c70
bool SP::WAIT_FOR_CARCASS_BABY_Tick(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
{
    SP::cSPCreatureBase_s00d7_0080* t = self->GetTargetAsCreature();
    if (!(t && t->mB5e)) {
        SP::Stimulus* stim = self->mpBehaviorTree->mStimuli.Play(0x40000, 0);
        if (stim) {
            t = SP::GetAnimalFromStimulus(stim);
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
        SP::Vec3 d;
        SP::Vec3* sp = self->mLoco.GetPosition();
        SP::Vec3* tp = t->mLoco.GetPosition();
        d.x = tp->x - sp->x;
        d.y = tp->y - sp->y;
        d.z = tp->z - sp->z;
        SP::Vec3 nd;
        SP::normalized_safe(&nd, &d);
        self->MoveToPointAndFacingAtSpeed(2, t->mLoco.GetPosition(), &nd, SP::kThree, SP::kFive);
        if (self->mLoco.IsNearGoal()) {
            self->PlayAnimation(0x120c5dd9, 1, -1);
            *st = 1;
        }
        break;
    }
    case 1:
        if (self->AnimationFinished(0)) {
            if (t->mpB50) {
                SP::cSPCreatureBase_s00d7_0080* ia = SP::interface_cast_creature(&t->mpB50);
                if (ia)
                    ia->mpBehaviorTree->mStimuli.Slot7f0(0, 1, SP::kFive, self);
            }
            self->PlayAnimation(0x120c5dd9, 1, -1);
        }
        break;
    case 2:
        if (self->mLoco.IsNearGoal())
            self->PlayAnimation(0x520c5dca, 1, -1);
        break;
    }

    self->MoveToPointAtSpeed(2, t->mLoco.GetPosition(), SP::kFive, SP::kSeven);
    if (self->mLoco.IsNearGoal())
        self->PlayAnimation(0xd1dce195, 1, -1);
    return true;
}

// @ 0x00d70ed0
bool FUN_00d70ed0(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, SP::EatState* st, SP::TargetHolder* holder)
{
    if (st)
        st->m04.mp = 0;
    st->m00 = 0;
    if (st->m04.mp) {
        SP::RefObj* old = st->m04.mp;
        st->m04.mp = 0;
        old->Release();
    }
    st->m08 = 0;
    st->m09 = 1;
    st->m0c = 0;
    float f = self->mpB20->m590;
    st->m10 = (f > SP::kZero) ? (int)SP::gU_1584100 : (int)SP::gU_1584104;
    st->m14 = -1;

    SP::cSPCreatureBase_s00d7_0080* t = self->GetTargetAsCreature();
    if (!(t && t->mB5e && t->m135 && 0.0f < t->FUN_00c0bb10())) {
        if (!holder)
            return false;
        SP::TargetOwner* o = holder->m4;
        if (!o)
            return false;
        t = o->GetTargetNPC(0xce9f6639);
    }
    if (t && t->mB5e && t->m135 && t->FUN_00c0bb10() > 0.0f) {
        self->AssignInteractor(&t->mCombatant, 0, 0);
        st->m04 = (SP::RefObj*)t;
        return true;
    }
    return false;
}
