// src/game/SPGonzago/SPCreatureSleep.cpp -- migrated from slice(s) s00d70080 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureSleep.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
struct LayoutMgr { bool LookupA(); };                 // 0x00af0af0 (thiscall, no stack args)
}
namespace SP {
struct cPlanetModel_s00d7_0080 {
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* c, float lo, float hi);  // 0x00b81780
};
}
namespace SP {
cPlanetModel_s00d7_0080* PlanetModel();                                      // 0x00b3d350
}
namespace SP {
void* __stdcall FUN_00af13b0(cSPCreatureBase_s00d7_0080* self, int a, int b); // 0x00af13b0
}
namespace SP {
extern const float kA_1687a20;     // 0x1687a20
}
namespace SP {
extern const float kA_1687a28;     // 0x1687a28
}
namespace SP {
extern const float kA_13f08e4;     // 0x13f08e4  (1.25)
}
namespace SP {
extern const float kTwo;           // 0x1470f1c
}
namespace SP {
extern const float kThree2;        // 0x13eb8c8  (0.3)
}
namespace SP {
extern unsigned gU_15840fc;        // 0x15840fc
}
namespace SP {
bool SLEEP_Tick(cSPCreatureBase_s00d7_0080* self, int, int, int, unsigned a3, int* st, int, float dt);
}
namespace SP {
void SLEEP_Deactivate(cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st);
}
void  SP::SLEEP_Deactivate(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st); // 0x00d70560
float FUN_00d705b0(SP::cSPCreatureBase_s00d7_0080* self);                                    // 0x00d705b0
// ---- items of slice s00d70080 end

// @ 0x00d70560
void SP::SLEEP_Deactivate(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
{
    self->mFlags.raw &= 0xfffffbff;
    self->mE38 = 0;
    if (!self->mB5e && st[0] == 4)
        self->InterruptAnimation(0x565220a, -1, 0);
    self->FUN_00c14750(0);
}

// @ 0x00d705b0
float FUN_00d705b0(SP::cSPCreatureBase_s00d7_0080* self)
{
    SP::cSPCreatureBase_s00d7_0080* c = self->GetHomeInfo()->m164;
    if (c && c->mpBehaviorTree->m1d8 == 0x2d852f4 && (c->mFlags.raw & 0x400))
        return 1.0f;
    return 0.0f;
}

// @ 0x00d705f0
bool SP::SLEEP_Tick(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, unsigned a3, int* st, int, float dt)
{
    if (self->mE38) {
        float hp = self->mCombatant.GetHealth();
        unsigned fl = self->mFlags.raw;
        float mult = ((fl >> 8) & 1) ? SP::kA_1687a28 : SP::kA_1687a20;
        self->mCombatant.PartialRepair(hp * mult * dt);
    }

    if (!self->FUN_00c0b770()) {
        SP::cSPCreatureBase_s00d7_0080* c = (SP::cSPCreatureBase_s00d7_0080*)self->GetHomeInfo()->m164;
        if (!c || c->mpBehaviorTree->m1d8 != 0x2d852f4)
            return false;
    } else {
        if (!((SP::LayoutMgr*)SP::FUN_00af13b0(self, 2, 0))->LookupA())
            return false;
    }

    SP::Vec3 pt;
    switch (*st) {
    case 0: {
        unsigned tmp;
        if (self->WaitForAnimEventOrEnd(SP::gU_15840fc, tmp, 0x3a74a08, 0, 1))
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
            SP::cSPCreatureBase_s00d7_0080* c = (SP::cSPCreatureBase_s00d7_0080*)self->GetHomeInfo()->m164;
            float tR = c->mLoco.GetFootprintRadius();
            float sr = self->mLoco.GetFootprintRadius();
            int count = self->GetHomeInfo()->m104;
            float lo = tR * tR;
            float hi = sqrtf((float)count * sr * sr + tR);
            SP::Vec3 ctr = *c->mLoco.GetPosition();
            SP::cPlanetModel_s00d7_0080* pm = SP::PlanetModel();
            pm->MakeRandomWorldPosition(&pt, &ctr, lo, hi);
        } else {
            SP::HomeInfo* h = self->GetHomeInfo();
            int count = (int)(h->m44 - h->m40) - h->m104;
            if (count < 0)
                count = 0;
            SP::SpatialObj* so = self->GetHomeInfo()->m160;
            float f40 = (so != 0) ? so->mLoco.GetFootprintRadius() : 0.0f;
            float sr = self->mLoco.GetFootprintRadius();
            float sum = sr + f40;
            float r125 = self->mLoco.GetFootprintRadius() * SP::kA_13f08e4;
            float dist = sqrtf(sum * sum + (float)count * r125 * r125);
            SP::Vec3 ctr = *self->GetHomeInfo()->GetPosition();
            SP::cPlanetModel_s00d7_0080* pm = SP::PlanetModel();
            pm->MakeRandomWorldPosition(&pt, &ctr, f40, dist);
        }
        if (!self->mLoco.SlotF8())
            self->FUN_00c14750(0);
        self->MoveToPointAtSpeed(2, &pt, SP::kThree2, SP::kTwo);
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
