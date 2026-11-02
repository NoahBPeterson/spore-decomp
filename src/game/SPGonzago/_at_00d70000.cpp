// src/game/SPGonzago/_at_00d70000.cpp -- migrated from slice(s) s00d78ad0, s00d77360, s00d75400, s00d70080 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00d70000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include <math.h>
#include "SP/cModelWorld.h"
#include "SP/cSpatialObject.h"
#include "SP/cSPCreatureCitizen.h"

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
cSPCreatureBase_s00d7_0080* GetAnimalFromStimulus(Stimulus* stim);           // 0x00d99980
}
namespace SP {
cSPCreatureBase_s00d7_0080* FUN_00d99500(void* p);                           // 0x00d99500
}
namespace SP {
void* __stdcall FUN_00af13b0(cSPCreatureBase_s00d7_0080* self, int a, int b); // 0x00af13b0
}
namespace SP {
void  FUN_00f47380_operator_delete_array(void* p);                // 0x00f47380
}
namespace SP {
extern const float kA_13ec4b4;     // 0x13ec4b4
}
namespace SP {
extern const float kA_169edd0;     // 0x169edd0
}
namespace SP {
extern const float kA_169edd4;     // 0x169edd4
}
namespace SP {
extern const float kA_169edd8;     // 0x169edd8
}
namespace SP {
extern const float kA_147bcd8;     // 0x147bcd8
}
namespace SP {
extern const float kOne;           // 0x1485720
}
namespace SP {
extern const float kTwo;           // 0x1470f1c
}
namespace SP {
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
}
namespace SP {
bool WARN_AVATAR_Activate(cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st);
}
void FUN_00d70340(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st);      // 0x00d70340
float FUN_00d704f0(SP::cSPCreatureBase_s00d7_0080* self);                                    // 0x00d704f0
bool  FUN_00d70510(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st);       // 0x00d70510
// ---- items of slice s00d70080 end

// ---- items of slice s00d75400 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double x);
#pragma intrinsic(sqrt)
#define PV_s00d7_5400(n) virtual void pv##n();
class IWin;
struct Vector3 { float x, y, z; };
class cGameObject;
class cObject;
class IWin {
 public:
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    PV_s00d7_5400(2)
    virtual cGameObject* pv03(uint32_t id);                  // +0x0c
    PV_s00d7_5400(4) PV_s00d7_5400(5) PV_s00d7_5400(6) PV_s00d7_5400(7) PV_s00d7_5400(8)
    virtual char pv09(uint32_t id, void** out);              // +0x24
    PV_s00d7_5400(10)
    virtual float* pv11();                                   // +0x2c
    PV_s00d7_5400(12) PV_s00d7_5400(13) PV_s00d7_5400(14) PV_s00d7_5400(15) PV_s00d7_5400(16) PV_s00d7_5400(17) PV_s00d7_5400(18) PV_s00d7_5400(19) PV_s00d7_5400(20) PV_s00d7_5400(21)
    virtual char pv22();                                     // +0x58
    PV_s00d7_5400(23) PV_s00d7_5400(24) PV_s00d7_5400(25)
    virtual void* pv26();                                    // +0x68
    PV_s00d7_5400(27) PV_s00d7_5400(28)
    virtual double pv29();                                   // +0x74
};
class RefText {
 public:
    RefText& operator=(IWin* p);                             // 0x00b5f950

    IWin* mpRef;                                             // +0x00
};
static void RefClear(IWin** pp)
{
    IWin* p = *pp;
    if (p != 0)
    {
        *pp = 0;
        p->Release();
    }
}
static void RefRelease(IWin** pp)
{
    if (*pp != 0)
        (*pp)->Release();
}
class cPlanetMgr {                                           // creature->mB20
 public:
    uint8_t pad00[0x590];
    float   mField590;                                       // +0x590
};
class cSubQuery {                                            // creature->mSub5c
 public:
    PV_s00d7_5400(0)
};
class cSpatialObject : public IWin {                         // creature->mSpatial34
 public:
    void*  FUN_00cee330();                                   // 0x00cee330
    double FUN_00cee380();                                   // 0x00cee380
};
class cOrderRecord;
class cAgentOrderManager {                                   // creature->mB4c
 public:
    cOrderRecord* FirstPending();                            // 0x00bca2c0
};
struct cOrderRecord {
    uint32_t mType00;                                        // +0x00
    uint8_t  pad04[0x0c];
    Vector3  mPos10;                                         // +0x10
    uint8_t  pad1c[0x0c];
    IWin*    mpOwner28;                                      // +0x28
    float    mX2c;                                           // +0x2c
    float    mY30;                                           // +0x30
    float    mZ34;                                           // +0x34
    uint8_t  pad38[0x34];
    float    mField6c;                                       // +0x6c
};
class cObject {                                              // generic engine handle
 public:
    void         FUN_00ac79e0(void* p);                      // 0x00ac79e0
    void         FindSpot();                                 // 0x00c98750
    void         FUN_00c97d40();                             // 0x00c97d40
    void         FUN_00c97020();                             // 0x00c97020
};
class cSimLoco : public IWin {
};
class cGameObject : public IWin {
 public:
    void           FUN_00c25f80();                           // 0x00c25f80
    char           FUN_00c22850();                           // 0x00c22850
    void           FUN_00c22860(int a);                      // 0x00c22860
    void           FUN_00c227f0(Vector3 v);                  // 0x00c227f0
    void           FUN_00c15150(int a, int b);               // 0x00c15150
    void           FUN_00c14750(int a);                      // 0x00c14750
    void           PerformSocialAction(uint32_t a, int b);   // 0x00c23300
    cObject*       GetTribe(int a, void* b);                 // 0x00c22f50
    cObject*       GetTribe();                               // 0x00c22f50
    void           MoveToPointAtSpeed(int a, void* p);       // 0x00c1c1d0
    void           GetFruitPos(float* out, uint32_t index);  // 0x00b02b90
    double         GetFruitHeight();                         // 0x00aff240
    cGameObject*   FUN_00b058a0();                           // 0x00b058a0
    char           FUN_00c1ac70(float* pos, int kind, int a, int b,
                                int c, float d);             // 0x00c1ac70

    uint8_t        pad04[0x0c];                              // +0x04..+0x10
    Vector3        mPos10;                                   // +0x10
    uint8_t        pad1c[0x18];                              // +0x1c..+0x34
    cSpatialObject mSpatial34;                               // +0x34
    uint8_t        pad38[0x10];                              // +0x38..+0x48
    uint64_t       mMask48;                                  // +0x48
    uint8_t        pad50[0x08];                              // +0x50..+0x58
    RefText        mField58;                                 // +0x58
    cSubQuery      mSub5c;                                   // +0x5c
    uint8_t        pad60[0x08];                              // +0x60..+0x68
    RefText        m68;                                      // +0x68
    float          m6c;                                      // +0x6c
    uint8_t        pad70[0x0c];                              // +0x70..+0x7c
    uint8_t        m7c;                                      // +0x7c
    uint8_t        pad7d[0x43];                              // +0x7d..+0xc0
    cSimLoco       mLoco_c0;                                 // +0xc0
    uint8_t        padc4[0x44];                              // +0xc4..+0x108
    RefText        m108;                                     // +0x108
    uint8_t        pad10c[0x14];                             // +0x10c..+0x120
    RefText        m120;                                     // +0x120
    uint8_t        pad124[0x48];                             // +0x124..+0x16c
    uint32_t       m16c;                                     // +0x16c
    uint8_t        pad170[0x9b0];                            // +0x170..+0xb20
    cPlanetMgr*    mB20;                                     // +0xb20
    uint8_t        padb24[0x28];                             // +0xb24..+0xb4c
    cAgentOrderManager* mB4c;                                // +0xb4c
};
struct FruitState {
    uint32_t m00;                                            // +0x00
    RefText  m04;                                            // +0x04
    RefText  m08;                                            // +0x08
    uint32_t m0c;                                            // +0x0c
    float    m10;                                            // +0x10
    float    m14;                                            // +0x14
    void*    m18;                                            // +0x18
    uint8_t  m1c;                                            // +0x1c
    uint8_t  m1d;                                            // +0x1d
    uint8_t  pad1e[2];                                       // +0x1e
    uint32_t m20;                                            // +0x20
    RefText  m24;                                            // +0x24

    ~FruitState();                                           // 0x00d75450
};
// ---- items of slice s00d75400 end

// ---- items of slice s00d77360 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
struct VtblObj {
    void** mVtbl;   // +0x00
};
struct At34 {
    u32 mValue;              // +0x00 (placeholder keeps the sub-object 4 bytes)
    int Func_cee330();       // 0x00cee330
};
struct Creature {
    void** mVtbl;            // +0x00
    u8  mPad04[0x30];        // +0x04
    At34 mAt34;              // +0x34
    u8  mPad38[0x88];        // +0x38
    VtblObj mVec;            // +0xc0
    u8  mPadC4[0xa88];       // +0xc4
    void* mOrderMgr;         // +0xb4c
    u8  mPadB50[0x08];       // +0xb50
    u32 mFlags;              // +0xb58

    void* GetTribe();                // 0x00c22f50
    bool  Func_c0ba30();             // 0x00c0ba30
    void  Func_c17350(int, int);     // 0x00c17350
    void  Func_c0b970(float);        // 0x00c0b970
    void  Func_c0d0c0(int, int);     // 0x00c0d0c0
    void  SetCurrentToolEffect(int, int); // 0x00c24f40
    void  Func_c1d460(int, int);     // 0x00c1d460
    void  Func_c14750(int);          // 0x00c14750
};
struct Tribe {
    void** mVtbl;            // +0x00
    u8  mPad04[0x11c];       // +0x04
    VtblObj mPos120;         // +0x120

    bool IsAvailableInCurrentPlanet(); // 0x00b1e4d0
    void Func_c8e6b0();                // 0x00c8e6b0
};
struct OrderMgr {
    void* FirstPending();                        // 0x00bca2c0
    void* FindNode(int, void*, void*);           // 0x00bca620
    void* Func_bcb0b0(int, int, int, const char*); // 0x00bcb0b0
    void  Func_bcb480(void*, void*, void*, void*); // 0x00bcb480
};
struct PendingOrder {
    u32 m0;                  // +0x00
};
struct TribeTail {
    void Func_c8e6c0();      // 0x00c8e6c0
};
struct Ctx {
    u8  mPad00[4];           // +0x00
    void* m4;                // +0x04
};
struct PtrB770 {
    bool  Func_c0b770();     // 0x00c0b770
    void* GetTribe();        // 0x00c22f50
};
struct Arg1 {
    void* Func_bc9b10();     // 0x00bc9b10
};
// ---- items of slice s00d77360 end

// ---- items of slice s00d78ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00F47380(void* p);                        // operator delete (cdecl-1)
extern "C" void  __stdcall FUN_00436CE0(void* pOut, const void* pIn);  // callee pops
extern float gFloat_147B9F0;      // 0x147b9f0
extern float gFloat_1470F1C;      // 0x1470f1c  (2.0f)
extern float gFloat_1572070;      // 0x1572070
typedef unsigned char    U8;
typedef unsigned int     U32;
struct Vector3_s00d7_8ad0 { float mX; float mY; float mZ; };
struct VT {
    virtual void  q00();                       // +0x00
    virtual void* q01(int id);                 // +0x04
    virtual void* q02(int id);                 // +0x08
    virtual void  q03();                       // +0x0c
    virtual void  q04();                       // +0x10
    virtual void  q05();                       // +0x14
    virtual void  q06();                       // +0x18
    virtual void  q07();                       // +0x1c
    virtual void  q08();                       // +0x20
    virtual void  q09();                       // +0x24
    virtual void  q10();                       // +0x28
    virtual void* q11();                       // +0x2c  -> Vector3*
    virtual U32   q12();                       // +0x30
    virtual void  q13();                       // +0x34
    virtual void  q14();                       // +0x38
    virtual void  q15();                       // +0x3c
    virtual void  q16();                       // +0x40
    virtual void  q17();                       // +0x44
    virtual void  q18();                       // +0x48
    virtual void  q19();                       // +0x4c
    virtual void  q20();                       // +0x50
    virtual void  q21();                       // +0x54
    virtual void* q22();                       // +0x58
    virtual void  q23();                       // +0x5c
    virtual void  q24();                       // +0x60
    virtual void  q25();                       // +0x64
    virtual void  q26();                       // +0x68
    virtual void  q27();                       // +0x6c
    virtual void  q28();                       // +0x70
    virtual float q29();                       // +0x74
    virtual void  q30();                       // +0x78
    virtual void  q31();                       // +0x7c
    virtual void  q32();                       // +0x80
    virtual void  q33();                       // +0x84
    virtual void  q34();                       // +0x88
    virtual void  q35();                       // +0x8c
    virtual void  q36();                       // +0x90
    virtual void  q37();                       // +0x94
    virtual void  q38();                       // +0x98
    virtual void  q39();                       // +0x9c
    virtual void  q40();                       // +0xa0
    virtual void  q41();                       // +0xa4
    virtual void  q42();                       // +0xa8
    virtual void* q43();                       // +0xac
    virtual void  q44();                       // +0xb0
    virtual void  q45();                       // +0xb4
    virtual void  q46();                       // +0xb8
    virtual void  q47();                       // +0xbc
    virtual void  q48();                       // +0xc0
    virtual void  q49();                       // +0xc4
    virtual void  q50();                       // +0xc8
    virtual void  q51();                       // +0xcc
    virtual void  q52();                       // +0xd0
    virtual void  q53();                       // +0xd4
    virtual void  q54();                       // +0xd8
    virtual void  q55(void* pGoal);            // +0xdc
    virtual void  q56();                       // +0xe0
    virtual void  q57();                       // +0xe4
    virtual void  q58();                       // +0xe8
    virtual void  q59();                       // +0xec
    virtual void  q60();                       // +0xf0
    virtual void  q61();                       // +0xf4
    virtual char  q62();                       // +0xf8
    virtual void  q63();                       // +0xfc
};
struct FnC0BA30  { char   __thiscall f(); };
struct FnC263E0  { void   __thiscall f(int); };
struct FnC22A70  { U32    __thiscall f(); };
struct FnC22F50  { void*  __thiscall f(); };
struct FnC22F50B { void*  __thiscall f(void* pOut, int unused); };
struct FnC91190  { void*  __thiscall f(); };
struct FnC14750  { void   __thiscall f(int); };
struct FnC0CFF0  { void   __thiscall f(int); };
struct FnC0E0C0  { char   __thiscall f(int); };
struct FnC12190  { void   __thiscall f(int, int, int); };
struct FnC42E20  { char   __thiscall f(); };
extern "C" void* FUN_0059AED0(void* pOut, const void* pTable, U32 key);
extern U8    gTable169EFD4;       // 0x169efd4
extern U8    gTable169EFE0;       // 0x169efe0
struct SpatialObject : VT {};
struct Creature_s00d7_8ad0 : VT {
    U8            mPad04[0xc0 - 0x04];
    SpatialObject mSpatial;          // +0xc0
    U8            mPadC4[0xb58 - 0xc4];
    U32           mFlagsB58;         // +0xb58
};
struct TribeSub : VT {};
struct TribeObj : VT {
    U8       mPad04[0x34 - 0x04];
    TribeSub mSub34;                 // +0x34
};
struct NavigationGoal {
    void* mpBuffer;                  // +0x00  owned keyed-vector buffer
    U8    mPad04[0x54];
    void __thiscall InitToward(const Vector3_s00d7_8ad0* pFrom, const Vector3_s00d7_8ad0* pTo,
                               float speed, float turn);
};
// ---- items of slice s00d78ad0 end

// @ 0x00d70340
void FUN_00d70340(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
{
    self->FUN_00c0b370(0xffffffff);
    self->mpBehaviorTree->mStimuli.ClearAll(0, 0x40000000);
    void* saved = (void*)st[2];
    void* cur = self->ApplyCombatTarget();
    if (saved == cur)
        self->AssignInteractor(0, 0, 0);
    SP::RefObj* r = (SP::RefObj*)st[2];
    if (r)
        r->Release();
}

// @ 0x00d703a0
bool SP::WARN_AVATAR_Activate(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
{
    SP::Stimulus* stim = self->mpBehaviorTree->mStimuli.Play(0, 0x80);
    if (stim) {
        SP::cSPCreatureBase_s00d7_0080* a = SP::GetAnimalFromStimulus(stim);
        SP::cSPCreatureBase_s00d7_0080* c = SP::FUN_00d99500(a);
        if (c) {
            self->AssignInteractor(&c->mCombatant, 1, 0);

            SP::SlotDCArg arg;
            arg.m00 = 0;
            arg.m04 = 0;
            arg.m08 = 0;
            arg.m14 = SP::kA_169edd0;
            arg.m18 = SP::kA_169edd4;
            arg.m1c = SP::kA_169edd8;
            arg.m20 = SP::kOne;
            arg.m24 = 0;
            arg.m4c = 0;
            arg.m50 = 0;
            arg.m54 = 0;
            arg.m58 = 0;
            arg.m5c = 0;
            arg.m60 = SP::kTwo;
            arg.m64 = SP::kA_13ec4b4;
            arg.m68 = SP::kA_147bcd8;
            arg.m6c = 0.0f;
            arg.m70 = 0.0f;
            self->mLoco.SlotDC(&arg);

            if (arg.m00 && *(int*)((char*)arg.m00 - 4) != 0)
                SP::FUN_00f47380_operator_delete_array(arg.m00);

            int h = self->InterruptAnimation(0x92314082, -1, 0);
            st[1] = h;
            st[0] = 0;
            return true;
        }
    }
    return false;
}

// @ 0x00d704f0
float FUN_00d704f0(SP::cSPCreatureBase_s00d7_0080* self)
{
    void* m = SP::FUN_00af13b0(self, 2, 0);
    if (((SP::LayoutMgr*)m)->LookupA())
        return 1.0f;
    return 0.0f;
}

// @ 0x00d70510
bool FUN_00d70510(SP::cSPCreatureBase_s00d7_0080* self, int, int, int, int, int* st)
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

// @ 0x00d75450
FruitState::~FruitState()
{
    // body: reset the two target slots (the inlined intrusive-pointer clear)
    RefClear(&m04.mpRef);
    RefClear(&m08.mpRef);
    // implicit member destructors, emitted in reverse declaration order
    RefRelease(&m24.mpRef);
    RefRelease(&m08.mpRef);
    RefRelease(&m04.mpRef);
}

// @ 0x00d77360
void FUN_00d77360(Creature* self)
{
    ((void (__thiscall*)(Creature*, int, int, int))self->mVtbl[0x84 / 4])(self, 0, 0, 0);
    self->mFlags &= ~0x10u;
    void* tribe = self->GetTribe();
    self->Func_c17350(0x9005e011, 0);
    void* pending = ((OrderMgr*)self->mOrderMgr)->FirstPending();
    if (pending != 0 && ((PendingOrder*)pending)->m0 == 0xb)
        return;
    ((TribeTail*)tribe)->Func_c8e6c0();
}

// @ 0x00d773c0
bool FUN_00d773c0(void* a1, void* a2)
{
    void* p = ((Ctx*)a2)->m4;
    if (((PtrB770*)p)->Func_c0b770()) {
        void* x = ((Arg1*)a1)->Func_bc9b10();
        void* t1 = ((PtrB770*)x)->GetTribe();
        void* t2 = ((PtrB770*)p)->GetTribe();
        if (t1 == t2)
            return true;
    }
    return false;
}

// @ 0x00d77400
float FUN_00d77400(Creature* self)
{
    if (self->mAt34.Func_cee330() == 0) {
        if (!self->Func_c0ba30()) {
            Tribe* tribe = (Tribe*)self->GetTribe();
            if (tribe->IsAvailableInCurrentPlanet()) {
                float* a = ((float* (__thiscall*)(VtblObj*))tribe->mPos120.mVtbl[0x2c / 4])(&tribe->mPos120);
                float* b = ((float* (__thiscall*)(VtblObj*))self->mVec.mVtbl[0x2c / 4])(&self->mVec);
                float dx = b[0] - a[0];
                float dy = b[1] - a[1];
                float dz = b[2] - a[2];
                float radius = ((float (__thiscall*)(Tribe*))tribe->mVtbl[0x60 / 4])(tribe);
                if ((dz * dz + dx * dx) + dy * dy < radius * radius) {
                    self->mFlags |= 0x10u;
                    tribe->Func_c8e6b0();
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00d78ad0
char FUN_00d78ad0(Creature_s00d7_8ad0* pCreature, U32 a2, U32 a3, U32 a4, U32 a5, U32* pState)
{
    if (((pCreature->mFlagsB58 >> 4) & 1) == 0) {
        return 0;
    }
    if (((FnC0BA30*)pCreature)->f() != 0) {
        return 0;
    }
    if (*pState == 0) {
        ((FnC263E0*)pCreature)->f(0);
        if (((FnC22A70*)pCreature)->f() != 0) {
            return 1;
        }
        void* pTribe = ((FnC22F50*)pCreature)->f();
        TribeObj* pObj = (TribeObj*)((VT*)pTribe)->q43();
        TribeSub* pSub = &pObj->mSub34;

        Vector3_s00d7_8ad0 a = *((Vector3_s00d7_8ad0*)pSub->q11());
        pSub->q29();
        Vector3_s00d7_8ad0 r1;
        FUN_0059AED0(&r1, &gTable169EFD4, pSub->q12());
        Vector3_s00d7_8ad0 r2;
        FUN_0059AED0(&r2, &gTable169EFE0, pSub->q12());

        float d0 = ((r2.mX + r1.mX) * gFloat_147B9F0 + a.mX) - a.mX;
        float d1 = ((r2.mY + r1.mY) * gFloat_147B9F0 + a.mY) - a.mY;
        float d2 = ((r2.mZ + r1.mZ) * gFloat_147B9F0 + a.mZ) - a.mZ;
        if ((d0 * r1.mX + d2 * r1.mZ) + d1 * r1.mY < 0.0f) {
            float s = ((d0 * r1.mX + d2 * r1.mZ) + d1 * r1.mY) * gFloat_1470F1C;
            d0 -= r1.mX * s;
            d1 -= r1.mY * s;
            d2 -= r1.mZ * s;
        }
        Vector3_s00d7_8ad0 d;
        d.mX = d0 + a.mX;
        d.mY = d1 + a.mY;
        d.mZ = d2 + a.mZ;

        Vector3_s00d7_8ad0 pos;
        ((FnC22F50B*)pCreature)->f(&pos, 0);
        Vector3_s00d7_8ad0 src = *((Vector3_s00d7_8ad0*)((FnC91190*)pTribe)->f());
        Vector3_s00d7_8ad0 dir;
        dir.mX = src.mX - d.mX;
        dir.mY = src.mY - d.mY;
        dir.mZ = src.mZ - d.mZ;
        Vector3_s00d7_8ad0 norm;
        FUN_00436CE0(&norm, &dir);

        NavigationGoal goal;
        goal.mpBuffer = 0;
        goal.InitToward(&d, &norm, gFloat_1572070, 2.0f);
        ((FnC14750*)pCreature)->f(1);
        ((VT*)&pCreature->mSpatial)->q55(&goal);
        ((FnC0CFF0*)pCreature)->f(2);
        *pState = 1;
        if (goal.mpBuffer != 0 && ((U32*)goal.mpBuffer)[-1] != 0) {
            FUN_00F47380(goal.mpBuffer);
        }
        return 1;
    }
    if (*pState - 1 <= 1) {
        if (((FnC42E20*)&pCreature->mSpatial)->f() != 0) {
            if (((FnC0E0C0*)pCreature)->f(0x915f7deb) == 0) {
                ((FnC12190*)pCreature)->f(0x915f7deb, 1, -1);
            }
        }
        *pState = 2;
    }
    return 1;
}
