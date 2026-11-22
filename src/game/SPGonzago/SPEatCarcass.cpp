// src/game/SPGonzago/SPEatCarcass.cpp -- migrated from slice(s) s00d70fe0, s00d70080 by tools/migrate/rewrite.py
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
#include "SP/cSPCreatureCitizen.h"
#include "SP/cTribe.h"

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

// ---- items of slice s00d70fe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float   g_f01582e30;          // 0x01582e30
extern float   g_f01687a00;          // 0x01687a00
extern float   g_f0148fddc;          // 0x0148fddc (1.5258789e-05)
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
struct Vector3 {
    float x, y, z;
};
extern Vector3 g_v0169ee40;          // 0x0169ee40, unit Z
bool  Vector3Equal(const Vector3* a, const Vector3* b);        // 0x004232c0
bool  Vector3_NotEqual(const Vector3* a, const Vector3* b);    // 0x0041dd30
void  normalized_safe(Vector3* out, const Vector3* in);        // 0x00449c20
class cPlanetModel {
public:
    void ToSurface(Vector3* out, const Vector3* in);            // 0x00b81630
    void DirectionToSurfacePosition(Vector3* out, const Vector3* in);  // 0x00b815a0
};
cPlanetModel* PlanetModel();                                   // 0x00b3d350
class Stimuli {
public:
    void ClearAll(int mask, int flags);    // 0x00bc98f0
    void* Play(int flags, int a);          // 0x00bc96a0
    void* Make(int a, int b, float c, int d);  // 0x00bc97f0
    void ClearStimulus(int a);             // 0x00bc9770
};
class cSim5a8 {
public:
    float NodeRatio();                     // 0x00bfc490
};
class cLocomotiveObject {
public:
virtual void v00();
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
    virtual void* v2c();                    // +0x2c  GetPosition
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
    virtual bool v58();                     // +0x58
    virtual void* v5c(Vector3* out);        // +0x5c
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void v70();
    virtual float v74();                    // +0x74  facing angle
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
    virtual void vec();                     // +0xec
    virtual void vf0();

    bool IsNearGoal();                      // 0x00c42e20
};
class cTribe;
class cSPCreatureBase {
public:
virtual void v00();
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
virtual bool v2c();
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
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
    virtual void v80();
    virtual void v84(int a, int b, int c);               // +0x84
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8(int a);
virtual void vec();
virtual void vf0();

    void* GetTargetAsCreature();                         // 0x00c0ee70
    void  UpdateLocomotion(int a);                       // 0x00c14750
    bool  AnimationFinished(int anim);                   // 0x00c12400
    int   PlayAnimation(int id, int a, int b);           // 0x00c12190
    int   PlayAnimationWithTargetObj(int id, void* target, int a, int b);  // 0x00c14940
    void  Attack(cSPCreatureBase* target, int a);        // 0x00c1e460
    void  MoveToPointAndFacingAtSpeed(int speed, Vector3* pos, Vector3* facing, float a, float b);
                                                         // 0x00c1c5c0
    void  MoveToPointAtSpeed(int speed, Vector3* pos, float a, float b);   // 0x00c1c1d0
    void* GetFieldE7C();                                 // 0x00c0ee60
    bool  BehaviourFlag();                               // 0x00c0b780
    bool  AnimValid(int anim);                           // 0x00c0e070
    bool  SomeBool();                                    // 0x00c0b770
    float SomeRatio();                                   // 0x00c0b9c0
    float SomeValue();                                   // 0x00c0bb10
    void* SomeObj();                                     // 0x00c0bc00
    bool  CanSee(Vector3* pos, Vector3* out);            // 0x00a04d20
    void* PickAttackTarget(int, int, int, int, int, int, int);  // 0x00c12410

    char pad004[0x34 - 0x004];
    void* mpField34;         // +0x34
    char pad038[0x110 - 0x038];
    u32  mFlags110;          // +0x110
    char pad114[0x135 - 0x114];
    u8   mb135;              // +0x135
    char pad136[0x137 - 0x136];
    u8   mb137;              // +0x137
    char pad138[0x1e8 - 0x138];
    int  mField1e8;          // +0x1e8
    char pad1ec[0x1f4 - 0x1ec];
    void* mpField1f4;        // +0x1f4
    char pad1f8[0x5a8 - 0x1f8];
    cSim5a8 mObj5a8;         // +0x5a8
    char pad5a9[0x5e0 - 0x5a9];
    float mField5e0;         // +0x5e0
    char pad5e4[0xb20 - 0x5e4];
    void* mpFieldB20;        // +0xb20
    char pad_b24[0xb4c - 0xb24];
    void* mpStimuliMgr;      // +0xb4c
    cSPCreatureBase* mpTarget;  // +0xb50
    void* mpFieldB54;        // +0xb54
    u32  mFlagsB58;          // +0xb58
    char pad_b5c[0xb5e - 0xb5c];
    u8   mbB5e;              // +0xb5e
    u8   mbB5f;              // +0xb5f
    char pad_b60[0x1014 - 0xb60];
    cTribe* mpTribe;         // +0x1014
};
class cTribe {
public:
    void SetStimuli(int a, int b, float c, void* d);     // 0x00c8f470
};
struct AutoRef {
    cSPCreatureBase* mp;
    AutoRef& operator=(cSPCreatureBase* v);              // 0x00b5f950
};
struct CarcassCtx {
    int      mState;        // +0x00
    AutoRef  mTarget;       // +0x04
    u8       mbField08;     // +0x08
    u8       mbField09;     // +0x09
    u16      pad0a;
    int      mAnimId;       // +0x0c
    int      mAnimArgA;     // +0x10
    int      mAnimArgB;     // +0x14
};
struct AchievementCtx {
    cSPCreatureBase* mpSelf;
    cSPCreatureBase* mpTarget;
    int              mField08;
};
class cStimulusPayload {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cSPCreatureBase* Lookup(int id);             // +0x0c
};
class cStimulus {
public:
    char pad00[0x0c];
    int  mField0c;                                       // +0x0c
    char pad10[0x1c];
    cStimulusPayload* mpPayload;                         // +0x2c
};
void   FUN_00d85540(cSPCreatureBase* self);              // 0x00d85540
void   FUN_00d70b10(float dt, cSPCreatureBase* self, void* ctx);  // 0x00d70b10
void   FUN_00d39360(int event, void* data);              // 0x00d39360
void   NotifyEvent(float f);                             // 0x00d2e8a0
void   FUN_00d52e40(int a);                              // 0x00d52e40
void*  cPosseSimulatorInstance();                        // 0x00d539d0
void*  Achievements();                                   // 0x00675250
void*  AchievementsAccessor(void* c);                    // 0x00675370
bool   AchievementsHas(void* c, int id);                 // 0x00675e80
void   AchievementsClear(void* c);                       // 0x00675770
void   AchievementsAutoTest(void* c, int id, int v);      // 0x00676e90
struct DeactivateCtx {
    char pad00[4];
    cSPCreatureBase* mpTarget;    // +0x04
};
// ---- items of slice s00d70fe0 end

// @ 0x00d70ab0
bool SP::PUKE_Activate(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
{
    int handle = -1;
    SP::Stimulus* stim = self->mpBehaviorTree->mStimuli.Play(0, 0x20000000);
    if (stim)
        handle = stim->m0c;
    st[0] = self->PlayAnimation(0x931fdcda, 1, handle);
    bool on = ((self->mFlags.raw >> 9) & 1) != 0;
    if (on) {
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

// @ 0x00d70fe0
void FUN_00d70fe0(cSPCreatureBase* self, int, int, int, int, DeactivateCtx* ctx)
{
    cSPCreatureBase* target = ctx->mpTarget;
    if (target != 0)
    {
        if (target->mpTarget == self)
        {
            cSPCreatureBase* held = *(cSPCreatureBase* volatile*)&target->mpTarget;
            if (held != 0)
            {
                target->mpTarget = 0;
                held->v04();
            }
        }
    }
    cSPCreatureBase* target2 = ctx->mpTarget;
    if (target2 == (cSPCreatureBase*)self->GetTargetAsCreature())
        self->v84(0, 0, 0);
    Stimuli* stimuli = (Stimuli*)((char*)self->mpStimuliMgr + 8);
    stimuli->ClearAll(0x40000, 0);
    cSPCreatureBase* target3 = ctx->mpTarget;
    if (target3)
        target3->v04();
}

// @ 0x00d71060
bool EAT_CARCASS_Tick(cSPCreatureBase* self, int, int, int, int, CarcassCtx* ctx, int, float dt)
{
    if (!ctx->mTarget.mp || !ctx->mTarget.mp->mbB5e || !ctx->mTarget.mp->mb135)
        return false;

    cSPCreatureBase* found = (cSPCreatureBase*)self->GetTargetAsCreature();
    if (found && found->mbB5e && found->mb135 && found != ctx->mTarget.mp)
    {
        ctx->mState = 0;
        cSPCreatureBase* old = ctx->mTarget.mp;
        if (old && old->mpTarget)
        {
            cSPCreatureBase* held = old->mpTarget;
            old->mpTarget = 0;
            held->v04();
        }
        ctx->mTarget = found;
    }

    if (ctx->mTarget.mp->mpTarget != self)
    {
        if (((self->mFlagsB58 >> 9) & 1) == 0 && ctx->mTarget.mp->mpTarget != 0)
            return false;
        ctx->mTarget = self;
    }

    cLocomotiveObject* loco = (cLocomotiveObject*)((char*)self + 0xc0);

    switch (ctx->mState)
    {
    case 0:
    {
        float startAngle;
        if ((ctx->mTarget.mp->mFlags110 & 0x1000) == 0)
            startAngle = loco->v74();
        else
            startAngle = *(float*)((char*)self->mpFieldB20 + 0x55c);

        cSPCreatureBase* target = ctx->mTarget.mp;
        if (target->mpFieldB54)
        {
            Vector3 spot;
            Vector3* p = (Vector3*)loco->v2c();
            if (!target->CanSee(p, &spot))
                spot = *(Vector3*)loco->v2c();

            Vector3 surface;
            PlanetModel()->ToSurface(&surface, &spot);

            Vector3 dir;
            Vector3* here = (Vector3*)loco->v2c();
            dir.x = surface.x - here->x;
            dir.y = surface.y - here->y;
            dir.z = surface.z - here->z;

            Vector3 dirN;
            normalized_safe(&dirN, &dir);

            Vector3 facing;
            if (Vector3Equal(&dirN, &g_v0169ee40))
            {
                Vector3 tmp;
                facing = *(Vector3*)loco->v5c(&tmp);
            }
            else
            {
                Vector3 surfN;
                normalized_safe(&surfN, &surface);
                float d = dirN.x * surfN.x + dirN.y * surfN.y + dirN.z * surfN.z;
                Vector3 perp;
                perp.x = dirN.x - surfN.x * d;
                perp.y = dirN.y - surfN.y * d;
                perp.z = dirN.z - surfN.z * d;
                if (Vector3_NotEqual(&perp, &g_v0169ee40))
                    facing = perp;
                else
                    facing = dirN;
            }

            float angle = loco->v74() + startAngle;
            self->MoveToPointAndFacingAtSpeed(2, &spot, &facing, angle, angle);
            ctx->mState = 1;
            return true;
        }

        float angle = loco->v74() + startAngle;
        cLocomotiveObject* tloco = (cLocomotiveObject*)((char*)target + 0xc0);
        Vector3* spot = (Vector3*)tloco->v2c();
        self->MoveToPointAtSpeed(2, spot, angle, angle);
        ctx->mState = 1;
        return true;
    }

    case 1:
        if (!loco->IsNearGoal())
            return true;

        loco->vec();
        ctx->mState = 2;
        FUN_00d85540(self);
        {
            void* animTarget = ctx->mTarget.mp ? (void*)((char*)ctx->mTarget.mp + 0xc0) : 0;
            ctx->mAnimId = self->PlayAnimationWithTargetObj(ctx->mAnimArgA, animTarget,
                                                            ctx->mAnimArgB, -1);
        }
        if (((self->mFlagsB58 >> 9) & 1) == 0)
            return true;
        if (ctx->mTarget.mp->mbB5f)
            return true;
        if (!self->BehaviourFlag())
            return true;
        ctx->mTarget.mp->mbB5f = 1;
        ctx->mbField08 = 1;
        NotifyEvent(g_f01582e30);
        {
            AchievementCtx ac;
            ac.mpSelf = self;
            ac.mpTarget = ctx->mTarget.mp;
            ac.mField08 = 0;
            FUN_00d39360(0xd335362d, &ac);

            void* ctrl = Achievements();
            void* acc = AchievementsAccessor(ctrl);
            if (AchievementsHas(acc, 0xe25acf0e))
            {
                AchievementsClear(acc);
                return true;
            }
            AchievementsAutoTest(ctrl, 0xe25acf0e, 1);
        }
        return true;

    case 2:
        if (self->BehaviourFlag() && self->AnimValid(ctx->mAnimId))
            FUN_00d70b10(dt, self, ctx);
        if (self->AnimationFinished(ctx->mAnimId))
            ctx->mState = 3;
        return true;

    case 3:
    {
        Stimuli* s = (Stimuli*)((char*)self->mpStimuliMgr + 8);
        void* stim = s->Play(0x400, 0);
        if (stim)
        {
            cStimulusPayload* payload = ((cStimulus*)stim)->mpPayload;
            if (payload)
            {
                cSPCreatureBase* animal = payload->Lookup(0xd0036e08);
                if (animal && animal->mb135)
                {
                    int anim = self->PlayAnimationWithTargetObj(0xb20c5df2,
                                                               (char*)animal + 0xc0, -1, -1);
                    ctx->mAnimId = anim;
                    ctx->mState = 5;
                    s->ClearAll(0, 1);
                }
            }
        }

        if (!self->BehaviourFlag())
        {
            void* s2 = s->Make(0, 0x20000000, 0x40a00000, 0);
            ((cStimulus*)s2)->mField0c = -1;
            ctx->mState = 4;
            return true;
        }

        if (ctx->mState != 5)
            FUN_00d70b10(dt, self, ctx);
        ctx->mbField08 = 0;

        float v = self->SomeRatio();
        bool ready = v >= g_f01687a00 &&
                     (ctx->mbField09 == 0 || self->mObj5a8.NodeRatio() >= 1.0f);
        if (ready)
        {
            if (((self->mFlagsB58 >> 9) & 1) != 0 && !self->SomeBool())
            {
                self->ve8(1);
                if (cPosseSimulatorInstance())
                    FUN_00d52e40(1);
            }
            ctx->mState = 4;
            return true;
        }

        float w = self->SomeValue();
        if (w < g_f0148fddc)
        {
            ctx->mState = 4;
            return true;
        }
        ctx->mState = 1;
        return true;
    }

    case 4:
        return false;

    case 5:
        if (self->AnimationFinished(ctx->mAnimId))
            ctx->mState = 3;
        return true;

    default:
        return true;
    }
}
