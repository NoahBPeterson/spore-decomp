// src/game/SPGonzago/_at_00da0000.cpp -- migrated from slice(s) s00da8630, s00da7780, s00da6880, s00da5900 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00da0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
extern const float g_f169f394;                      // 0x0169f394
extern const float g_f169f398;                      // 0x0169f398
extern const float g_f169f39c;                      // 0x0169f39c
extern const float g_f169f3a0;                      // 0x0169f3a0
extern const float g_f169f3a4;                      // 0x0169f3a4
extern const float g_f169f3a8;                      // 0x0169f3a8
extern const float g_f169f3ac;                      // 0x0169f3ac
extern const float _HK_REAL_ONE;                    // 0x01485720 = 1.0f
#include <new>
#include <math.h>
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"

// ---- items of slice s00da5900 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef unsigned __int64   u64;
struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Quat { float x, y, z, w; };
void* __cdecl FUN_00b3d510();                      // 0x00b3d510: returns a global
void* __cdecl FUN_00b5b800();                      // 0x00b5b800: GetCurrentGameMode
void* __cdecl FUN_01021080();                      // 0x01021080: GetUniverseContext
void* __cdecl FUN_00d994c0(void* block);           // 0x00d994c0
void* __cdecl FUN_00d999d0(void* block);           // 0x00d999d0: WatchMemoryBlock
void* __cdecl FUN_00d99a10(void* block);           // 0x00d99a10
void* __cdecl FUN_00d998f0(void* block);           // 0x00d998f0
void* __cdecl FUN_00d998d0(void* block, u32 key);  // 0x00d998d0
Vec3* __cdecl FUN_0059aed0(Vec3* out, void* v, void* q);                  // 0x0059aed0 RotateByQuat
void* __cdecl FUN_00b0fd00(void* out, void* v, void* dir, float f);       // 0x00b0fd00 RotateTowards
Quat* __cdecl FUN_0069b600(Quat* out, const Vec3* f, const Vec3* u);      // 0x0069b600 QuaternionFromFacingAndUp
void  __cdecl FUN_00da62d0(void* c, void* tribe, u32 lo, u32 hi);         // 0x00da62d0 (this slice)
void  __cdecl FUN_00da6270(void* c, int order);                           // 0x00da6270 (this slice)
u64   __cdecl FUN_00da6090(u32 index);            // 0x00da6090 (this slice)
extern const float g_f169f394;                      // 0x0169f394
extern const float g_f169f398;                      // 0x0169f398
extern const float g_f169f39c;                      // 0x0169f39c
extern const float g_f169f3a0;                      // 0x0169f3a0
extern const float g_f169f3a4;                      // 0x0169f3a4
extern const float g_f169f3a8;                      // 0x0169f3a8
extern const float g_f169f3ac;                      // 0x0169f3ac
extern const float _HK_REAL_ONE;                    // 0x01485720 = 1.0f
struct cTribe;
struct cSPCreatureCitizen;
struct HRes {
virtual void h00();
virtual void h01();
virtual void h02();
virtual void h03();
virtual void h04();
virtual void h05();
virtual void h06();
virtual void h07();
virtual void h08();
virtual void h09();
virtual void h10();
    virtual Vec3* GetPos();                        // slot +0x2c
    virtual Vec3* GetDir();                        // slot +0x30
    char  mPad[0x38 - 4];                          // vfptr + pad
    float mf38;                                    // +0x38
};
struct AppA {
virtual void a00();
virtual void a01();
virtual void a02();
    virtual HRes* GetByHash(u32 hash);             // +0x0c
virtual void a04();
virtual void a05();
virtual void a06();
virtual void a07();
virtual void a08();
virtual void a09();
virtual void a10();
    virtual bool Available();                      // +0x2c (returns a char)
};
struct Spat {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual Vec3* GetPos();                        // +0x2c
    virtual void s12();                            // +0x30
    virtual void s13();                            // +0x34
    virtual void SetFacing(Vec3* v);               // +0x38
    virtual void SetOrientation(Quat* q);          // +0x3c
};
struct SpatialPos {
virtual void p00();
virtual void p01();
virtual void p02();
virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
virtual void p08();
virtual void p09();
virtual void p10();
    virtual Vec3* GetPos();                        // +0x2c
};
struct CombatSub {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void c21();
    virtual float GetMaxHealth();                  // +0x58
};
struct Res58 {
virtual void r00();
virtual void r01();
virtual void r02();
virtual void r03();
virtual void r04();
virtual void r05();
virtual void r06();
virtual void r07();
virtual void r08();
virtual void r09();
virtual void r10();
virtual void r11();
virtual void r12();
virtual void r13();
virtual void r14();
virtual void r15();
virtual void r16();
virtual void r17();
virtual void r18();
virtual void r19();
virtual void r20();
virtual void r21();
    virtual cTribe* GetTribeField();               // +0x58
};
struct ResTribe {
    char    mPad00[0x1f8];
    cTribe* mpTribe;                               // +0x1f8
    cTribe* Get();                                 // 0x00c9d9e0
};
struct ResBlock {
    char    mPad00[0xc];
    cTribe* mpTribe;                               // +0xc
};
struct ResId {
virtual void i00();
virtual void i01();
virtual void i02();
virtual void i03();
virtual void i04();
virtual void i05();
virtual void i06();
virtual void i07();
    virtual int GetId();                           // +0x20
};
struct ResNode {
virtual void n00();
virtual void n01();
virtual void n02();
    virtual ResId* GetSub();                       // +0x0c
};
struct ResTime {
    int GetValue();                                // 0x00cee340
};
struct Res4f {
    char    mPad00[0x20c];
    ResTime mTime;                                 // +0x20c
};
struct behavior_stimuli {
    int   mStimulusID;                             // +0x0
    void* mTarget;                                 // +0x4
    int   mValue;                                  // +0x8 (duration)
    char  mPad0c[0x18 - 0xc];
    int   mF18;                                    // +0x18

    void  ClearAll(u32 lo, u32 hi);                // 0x00bc98f0 (ret 8)
    void* Play(u32 lo, u32 hi);                    // 0x00bc96a0 (ret 8)
    void  PlayWith(u32 lo, u32 hi, float duration, void* target);   // 0x00bc97f0 (ret 0x10)
    void  GetAny();                                // 0x00d997e0
};
struct AgentNode;
struct behavior_stimuli;
struct cBehaviorTreeData {
    char             mPad00[8];
    behavior_stimuli mStimuli;                     // +0x08
    char             mPad[0x60c - 0x8 - sizeof(behavior_stimuli)];
    int*   FirstPending();                         // 0x00bca2c0
    void   PopFront();                             // 0x00bcaf40
    void   OrderOp(AgentNode* node, cSPCreatureCitizen* c, void* a, void* fn);  // 0x00bcb480
};
struct cSPCreatureCitizen {
virtual void v00();
virtual void v01();
virtual void v02();
    virtual cSPCreatureCitizen* GetByHash(u32 hash);   // +0x0c
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
    virtual AppA* GetApp();                        // +0x30

    char               mPad04[0x34 - 4];
    Spat               mSpat;                      // +0x34
    char               mPad34[0xc0 - 0x34 - sizeof(Spat)];
    SpatialPos         mPos;                       // +0xc0
    char               mPadc0[0x5a8 - 0xc0 - sizeof(SpatialPos)];
    CombatSub          mCombat;                    // +0x5a8
    char               mPad5a8[0x5e0 - 0x5a8 - sizeof(CombatSub)];
    float              mF5e0;                      // +0x5e0
    char               mPad5e0[0xb4c - 0x5e0 - 4];
    cBehaviorTreeData* mpBTree;                    // +0xb4c
    char               mPadb4c[0xb5e - 0xb4c - 4];
    bool               mbDead;                     // +0xb5e

    cTribe* GetTribe();                            // 0x00c22f50
    bool    IsLeader();                            // 0x00c232d0
    void    ForceOrdersUpdate();                   // 0x00c26450
    cSPCreatureCitizen* GetTargetAsCreature();     // 0x00c0ee70
    void    SetInteractionTarget(float f);         // 0x00c0b970
};
struct cTribe {
    char  mPad00[0x2c8];
    float mF2c8;                                   // +0x2c8
    char  mPad2cc[0x556 - 0x2cc];
    u8    mF556;                                   // +0x556
    u32   GetAdultPopulation();                    // 0x00c8f370
};
struct AgentNode {
    char mPad000[0x1a8];
    u32  mBand;                                    // +0x1a8
    char mPad1ac[0x224 - 0x1ac];
    void* mFn224;                                  // +0x224
    void* mFn228;                                  // +0x228
};
struct HelperB71 {
    void Run(void* p);                             // 0x00b71af0 (thiscall, ret 4)
};
// ---- items of slice s00da5900 end

// ---- items of slice s00da6880 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPCreatureCitizen_s00da_6880;
struct cTribe_s00da_6880;
struct behavior_stimuli_s00da_6880;
struct cBehaviorTreeData_s00da_6880;
struct cTool;
struct VF8 {                                                     // 8 filler virtual slots
virtual void f00();
virtual void f01();
virtual void f02();
virtual void f03();
virtual void f04();
virtual void f05();
virtual void f06();
virtual void f07();
};
struct VF16 : VF8 {
virtual void f08();
virtual void f09();
virtual void f10();
virtual void f11();
virtual void f12();
virtual void f13();
virtual void f14();
virtual void f15();
};
struct Crt : VF8 {
    virtual int   v20();                                         // +0x20
virtual void  d24();
virtual void d28();
    virtual char  v2c();                                         // +0x2c
virtual void  d30();
virtual void d34();
virtual void d38();
virtual void d3c();
virtual void  d40();
virtual void d44();
virtual void d48();
    virtual int   v4c();                                         // +0x4c
virtual void  d50();
virtual void d54();
virtual void  d58();
virtual void d5c();
virtual void d60();
virtual void d64();
virtual void  d68();
virtual void d6c();
virtual void d70();
virtual void d74();
virtual void  d78();
virtual void d7c();
virtual void d80();
virtual void d84();
virtual void  d88();
virtual void d8c();
virtual void d90();
virtual void d94();
virtual void  d98();
virtual void d9c();
virtual void da0();
virtual void da4();
virtual void  da8();
virtual void dac();
virtual void db0();
virtual void db4();
virtual void  db8();
virtual void dbc();
    virtual char  vc0(void*, float, float);                      // +0xc0
};
struct Sub58 {                                                   // embedded sub-object at citizen+0x58
virtual void  s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void  s10();
virtual void s14();
virtual void s18();
virtual void s1c();
    virtual int   v20();                                         // +0x20
virtual void  d24();
virtual void d28();
virtual void d2c();
virtual void d30();
    virtual void  v34();                                         // +0x34
};
struct StimTimer {                                               // sub-object with a stim timer
    char  mData[4];
    float GetTimer();                                            // 0x00cee380
    void* GetPtr330();                                           // 0x00cee330
    void* GetPtr340();                                           // 0x00cee340
};
struct Combatant {                                               // combat sub-object (+0x120 / +0x5a8)
virtual void c00();
virtual void c04();
virtual void c08();
virtual void c0c();
virtual void c10();
virtual void c14();
    virtual void v18(float, int, int, void*, int);               // +0x18
virtual void c1c();
virtual void c20();
virtual void c24();
virtual void c28();
    virtual int  v2c(float);                                     // +0x2c
    int   GetDamageState();                                      // 0x008e7f80
    float GetHealthPct();                                        // 0x00bfc490
};
struct SpatC0 {                                                  // embedded sub-object at citizen+0xc0
virtual void  p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void  p10();
virtual void p14();
virtual void p18();
virtual void p1c();
virtual void  p20();
virtual void p24();
virtual void p28();
virtual void p2c();
virtual void  p30();
virtual void p34();
virtual void p38();
virtual void p3c();
virtual void  p40();
virtual void p44();
virtual void p48();
virtual void p4c();
virtual void  p50();
virtual void p54();
    virtual char  v58();                                         // +0x58
virtual void  d5c();
virtual void d60();
virtual void d64();
virtual void d68();
virtual void  d6c();
virtual void d70();
    virtual float v74(float);                                    // +0x74
virtual void  d78();
virtual void d7c();
virtual void d80();
virtual void d84();
virtual void  d88();
virtual void d8c();
virtual void d90();
virtual void d94();
virtual void  d98();
virtual void d9c();
virtual void da0();
virtual void da4();
virtual void  da8();
virtual void dac();
virtual void db0();
virtual void db4();
virtual void  db8();
virtual void dbc();
virtual void dc0();
virtual void dc4();
virtual void  dc8();
virtual void dcc();
virtual void dd0();
virtual void dd4();
virtual void  dd8();
virtual void ddc();
virtual void de0();
virtual void de4();
virtual void  de8();
virtual void dec();
virtual void df0();
virtual void df4();
    virtual char  vf8();                                         // +0xf8
    char  IsNearGoal();                                          // 0x00c42e20
    void* FUN_c41ec0();                                          // 0x00c41ec0
};
struct AnimPlayRes {
    char  mPad000[0xc];
    u32   mAnimId;                                               // +0xc
    u32   mAnim;                                                 // +0x10
};
struct behavior_stimuli_s00da_6880 {
    int   mStimulusID;                                           // +0x0
    void* mTarget;                                               // +0x4
    void* mValue;                                                // +0x8
    char  mPad0c[0x18 - 0xc];
    int   mF18;                                                  // +0x18

    void   ClearAll(u32 lo, u32 hi);                             // 0x00bc98f0
    AnimPlayRes* Play(u32 lo, u32 hi);                           // 0x00bc96a0
    void   PlayWith(u32 lo, u32 hi, float dur, void* target);    // 0x00bc97f0
    void   GetAny();                                             // 0x00d997e0
};
struct cBehaviorTreeData_s00da_6880 {
    char             mPad00[8];
    behavior_stimuli_s00da_6880 mStimuli;                                   // +0x08
    char             mPad1c[0x1c8 - 0x08 - sizeof(behavior_stimuli_s00da_6880)];
    u32              mFlags1c8;                                  // +0x1c8
    char             mPad1cc[0x1d8 - 0x1cc];
    u32              mKey1d8;                                    // +0x1d8

    void PopFront();                                             // 0x00bcaf40
};
struct cTool {                                                   // a tool object (has a combatant)
    char      mPad000[0x120];
    Combatant mCombat;                                           // +0x120
};
struct cTribe_s00da_6880 : VF16 {                                            // +0x60 slot60, +0xac slotac
virtual void  d40();
virtual void d44();
virtual void d48();
virtual void d4c();
virtual void  d50();
virtual void d54();
virtual void d58();
virtual void d5c();
    virtual float v60();                                         // +0x60
virtual void  d64();
virtual void d68();
virtual void d6c();
virtual void d70();
virtual void  d74();
virtual void d78();
virtual void d7c();
virtual void d80();
virtual void  d84();
virtual void d88();
virtual void d8c();
virtual void d90();
virtual void  d94();
virtual void d98();
virtual void d9c();
virtual void da0();
virtual void  da4();
virtual void da8();
    virtual cTool* vac();                                        // +0xac

    char      mPad004[0x120 - 4];                                // +0x04
    Combatant mCombat;                                           // +0x120
    char      mPad124[0x20c - 0x124];                            // +0x124
    StimTimer mTimer20c;                                         // +0x20c
    char      mPad210[0x556 - 0x210];                            // +0x210
    u8        mFlag556;                                          // +0x556

    cSPCreatureCitizen_s00da_6880* GetChieftain();                          // 0x00c8fd30
    cTool*              GetToolOfType(int type);                 // 0x00c8f6e0
};
struct cAgentOrderManager {
    int FindSlot(int a, int b, int c, int d);                    // 0x00bca0c0
};
struct cSPCreatureCitizen_s00da_6880 : Crt {
    char      mPad004[0x34 - 0x04];                              // +0x04
    StimTimer mTimer34;                                          // +0x34
    char      mPad038[0x58 - 0x38];                              // +0x38
    Sub58     mSub58;                                            // +0x58
    char      mPad05c[0xc0 - 0x5c];                              // +0x5c
    SpatC0    mSubC0;                                            // +0xc0
    char      mPad0c4[0x135 - 0xc4];                             // +0xc4
    u8        mFlag135;                                          // +0x135
    char      mPad136[0x330 - 0x136];                            // +0x136
    u8        mFlag330;                                          // +0x330
    char      mPad331[0x5a8 - 0x331];                            // +0x331
    Combatant mCombat;                                           // +0x5a8
    char      mPad5ac[0xb48 - 0x5ac];                            // +0x5ac
    cAgentOrderManager* mpOrders;                                // +0xb48
    cBehaviorTreeData_s00da_6880*  mpBTree;                                 // +0xb4c
    char      mPadb50[0xb58 - 0xb50];
    u32       mFlagsB58;                                         // +0xb58
    char      mPadb5c[0xb5e - 0xb5c];
    u8        mbDead;                                            // +0xb5e

    cTribe_s00da_6880* GetTribe();                                          // 0x00c22f50
    int     FUN_c22dc0();                                        // 0x00c22dc0
    float   FUN_c0b9c0();                                        // 0x00c0b9c0
    int     FUN_c0ee60();                                        // 0x00c0ee60
    char    FUN_bc9b50();                                        // 0x00bc9b50
    cSPCreatureCitizen_s00da_6880* FUN_bc9b10();                            // 0x00bc9b10
    char    Proximity(void* t, float a, float b);                // 0x00c0d560
    u32     InterruptAnimation(u32 id, int a, int b);            // 0x00c12310
    void    PlayAnimation(u32 id, int a, int b);                 // 0x00c12190
    void    FUN_c14750(int a);                                   // 0x00c14750
    void    FUN_c279a0(int a);                                   // 0x00c279a0
    void    SetCurrentToolEffect(int a, int b);                  // 0x00c24f40
    void    ForceOrdersUpdate();                                 // 0x00c26450
    void    MoveToPointAtSpeed(int a, void* p, float b, float c);// 0x00c1c1d0
    char    AnimationFinished(u32 id);                           // 0x00c12400
};
// ---- items of slice s00da6880 end

// ---- items of slice s00da7780 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 1)
#pragma pack(pop)
typedef unsigned short u16;
typedef int            i32;
typedef float          f32;
struct Creature;
struct cTribe_s00da_7780;
struct IdleBlock;
struct PtrVec { Creature** mBegin; Creature** mEnd; };
struct AutoRefCount {
    u32  mPtr;
    void operator=(void* p);
};
struct OrderSub39 {
    u32          mField00;                 // +0x39 +0x00
    u8           pad_04[0xc];
    u8           mByte10;                  // +0x49 (sub +0x10)
    u8           pad_11[1];
    u16          mField12;                 // +0x4b (sub +0x12)
};
struct OrderRec {
    u32          mField00;                 // +0x00
    u8           pad_04[0x24];
    AutoRefCount mRef28;                   // +0x28
    u8           pad_2c[0xd];
    OrderSub39   mSub39;                   // +0x39
    u8           pad_4d[0x2b];
    u32          mField78;                 // +0x78
    u32          mField7c;                 // +0x7c
    u8           pad_80[0x2c];
};
struct BehaviorStimuli {
    u32   mField00;                        // +0x00
    void* mField04;                        // +0x04
    u8    pad_08[0x38];
    u32 Play(u32 a, u32 flags);
    u32 ClearAll(u32 a, u32 flags);
    void GetAny();
};
struct AgentOrderManager {
    u8 pad_00[8];
    BehaviorStimuli mStimuli;              // +0x08
    u8 pad_48[0x118];
    OrderRec mRecs[1];                     // +0x160
    OrderRec* FirstPending();
    u32 FUN_00bc5040(u32 a);
    u32 FUN_00bc3db0(u32 a);
    u32 FUN_00bc3df0(u32 a);
};
struct SubObj58 {
    void* vptr;
    i32 V_2c() { return (*(i32 (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
};
struct Ret7780 {
    u8  pad_000[0x12c];
    i32 mField12c;
};
struct Locomotive {
    u8  pad_00[0x24];
    SubObj58 mSub58;                       // creature +0x58
    u8  pad_28[0x64];
    Ret7780* FUN_00cee330();
};
struct AnimObj {
    void* V_8()        { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x08))(this); }
    void* V_c()        { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x0c))(this); }
    void* V_20()       { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x20))(this); }
    f32*  V_2c()       { return (*(f32* (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
    void* V_5c(u32 a)  { return (*(void* (__thiscall**)(void*, u32))(*(char**)this + 0x5c))(this, a); }
};
struct Obj0xc0 {
    void* vptr;                            // +0x00
    u8    pad_04[0x4c];
    u8    V_58()      { return (*(u8 (__thiscall**)(void*))(*(char**)this + 0x58))(this); }
    u8    V_f8()      { return (*(u8 (__thiscall**)(void*))(*(char**)this + 0xf8))(this); }
    void  V_ec()      { (*(void (__thiscall**)(void*))(*(char**)this + 0xec))(this); }
    void  V_54(u32 a) { (*(void (__thiscall**)(void*, u32))(*(char**)this + 0x54))(this, a); }
    void* V_2c()      { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
    void  FUN_00c41d60(void* p);
    void  FUN_00c41d90(void* p);
};
struct cSPTimer {
    u8 mData[0x20];
    void Restart();
};
struct cSub558 {
    u8 mData[0x10];
    void FUN_00cc7f90(u32 a);
};
struct cTribe_s00da_7780 {
    void* vptr;                            // +0x00
    u8  pad_004[0x268];
    i32 mField26c;                         // +0x26c
    cSPTimer mTimer270;                    // +0x270
    u8  pad_290[0x2c8];
    cSub558 mSub558;                       // +0x558
    void FindSpot(u32 a, u32 b);
    void FUN_00c950f0(Creature* p);
    void V_9c(Creature* p, u32 a) { (*(void (__thiscall**)(void*, Creature*, u32))(*(char**)this + 0x9c))(this, p, a); }
};
struct TriggerMgr {
    void* vptr;                            // +0x00
    u8  pad_004[0x28];
    i32 mField2c;                          // +0x2c
    u8  FUN_00adb360(void* o);
    void goExit();
};
struct RandomLCG {
    u32 RandomUint32Uniform(u32 n);
};
struct Obj9cec0 { u8 pad_00[0x28]; i32 mField28; };
struct IdleBlock {
    i32 mField00;                          // +0x00
    i32 mField04;                          // +0x04
    i32 mField08;                          // +0x08
    i32 mField0c;                          // +0x0c
    f32 mField10;                          // +0x10
    Creature* mpCreature14;                // +0x14
    void PickNewActivity();
};
struct S19 { u8 pad0[4]; i32 mField04; u8 mByte08; };
struct Creature {
    void* vptr;                            // +0x000
    u8  pad_004[0x30];                     // 0x004..0x034
    Locomotive mLoco;                      // +0x034
    Obj0xc0 mObjC0;                        // +0x0c0
    u32 mFlags110;                         // +0x110
    u8  pad_114[0x1b];                     // 0x114..0x12f
    u8  mByte12f;                          // +0x12f
    u8  pad_130[0x7];                      // 0x130..0x137
    u8  mByte137;                          // +0x137
    u8  pad_138[0xa14];                    // 0x138..0xb4c
    AgentOrderManager* mpAgentOrders;      // +0xb4c
    u8  pad_b50[0xe];                      // 0xb50..0xb5e
    u8  mByte_b5e;                         // +0xb5e

    // vtable dispatch helpers
    void  V_8c()      { (*(void (__thiscall**)(void*))(*(char**)this + 0x8c))(this); }
    void  V_84(u32 a, u32 b, u32 c) { (*(void (__thiscall**)(void*, u32, u32, u32))(*(char**)this + 0x84))(this, a, b, c); }
    void* V_b4(void* a) { return (*(void* (__thiscall**)(void*, void*))(*(char**)this + 0xb4))(this, a); }
    PtrVec* V_90()    { return (*(PtrVec* (__thiscall**)(void*))(*(char**)this + 0x90))(this); }

    // methods (extern)
    cTribe_s00da_7780* GetTribe();
    Creature* FUN_00bc9b10();
    u32   FUN_00c0ee60();
    void  FUN_00c14750(i32 a);
    u8    FUN_00c0e0c0(u32 a);
    u32   PlayAnimation(u32 a, i32 b, i32 c);
    u32   InterruptAnimation(u32 a, i32 b, i32 c);
    u8    WaitForAnimEventOrEnd(u32 a, u32* out, u32 b, void* c, u32 d);
    u8    AnimationFinished(u32 a);
    u32   FUN_00c0b760();
    u8    FUN_00c0b770();
    void* FUN_00c22a70();
    void* FUN_00c22dc0();
    void* FUN_00c26120();
    u8    FUN_00c25480(void* a, u32 b);
    void  SetCurrentToolEffect(u32 a, i32 b);
    void  RebuildCitizenOrderListDefault();
    void  d0c0(u32 a, i32 b);
    void  ForceOrdersUpdate();
    u8    FUN_00c04710();
    void  FUN_00c0bf10(u32 a0, u32 a1, u32 a2, u32 a3, f32 f4, u32 a5, u32 a6, u32 a7, u32 a8, u32 a9, u32 a10);
};
extern f32 g_14007f4;
extern f32 g_1473c70;
extern f32 g_1486110;
extern f32 g_14774d0;
extern RandomLCG g_MathRandom;
void* FUN_00c9cec0(void* p);
void* FUN_00d99a10(u32 h);
TriggerMgr* FUN_00b3d4d0();
// ---- items of slice s00da7780 end

// ---- items of slice s00da8630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_half;         // 0x01471064  0.5
typedef long double    float10;
struct Vec3_s00da_8630 { float x, y, z; };
void* GetTribe(void* c);                              // 0x00c22f50 (thiscall)
void* GetChieftain(void* tribe);                      // 0x00c8fd30 (thiscall)
double RandomDoubleUniform(void* rng);                // 0x009360d0
struct Rng { double RandomDoubleUniform(); };         // 0x009360d0 (thiscall, ecx=rng)
// ---- items of slice s00da8630 end

// @ 0x00da5c80
bool __cdecl FUN_00da5c80(void* p)
{
    ((HelperB71*)FUN_00b3d510())->Run(p);
    return true;
}

// @ 0x00da5ca0
float __cdecl FUN_00da5ca0(cSPCreatureCitizen* c)
{
    AppA* app = c->GetApp();
    if (app != 0 && !app->Available()) {
        HRes* res = app->GetByHash(0x13f94d4);
        if (res != 0 && 1.5258789e-05f >= res->mf38)
            return 1.0f;
        return 0.0f;
    }
    return 1.0f;
}

// @ 0x00da5cf0
bool __cdecl FUN_00da5cf0(cSPCreatureCitizen* c, void* a, void* b, void* d, void* e, float* out)
{
    AppA* app = c->GetApp();
    if (app != 0)
        app->GetByHash(0x1186577);
    float k = 10.0f;
    out[0] = k;
    float x1 = g_f169f398;
    float x2 = g_f169f39c;
    float x3 = g_f169f3a0;
    out[1] = x1 * k;
    out[2] = x2 * k;
    out[3] = x3 * k;
    return true;
}

// @ 0x00da5d60
bool __cdecl FUN_00da5d60(cSPCreatureCitizen* c, void* a2, void* a3, void* a4, void* a5, float* pOut, void* a7, float angle)
{
    AppA* app = c->GetApp();
    HRes* hres = 0;
    if (app != 0)
        hres = app->GetByHash(0x1186577);
    hres->GetPos();

    float ha = (g_f169f394 * angle) * 0.5f;
    float s  = (float)sin(ha);
    float cq = (float)cos(ha);

    Quat q;
    q.x = s * g_f169f3a4;
    q.y = s * g_f169f3a8;
    q.z = s * g_f169f3ac;
    q.w = cq;

    Vec3 v;
    FUN_0059aed0(&v, pOut + 1, &q);
    pOut[1] = v.x;
    pOut[2] = v.y;
    pOut[3] = v.z;

    Vec3  dir = *hres->GetDir();
    Vec3  r2;
    FUN_0059aed0(&r2, pOut + 1, hres->GetDir());

    Vec3  pos = *hres->GetPos();
    float px = r2.x + pos.x;
    float py = r2.y + pos.y;
    float pz = r2.z + pos.z;

    Vec3  here = *c->mSpat.GetPos();
    float dx = px - here.x;
    float dy = py - here.y;
    float dz = pz - here.z;
    float inv = 1.0f / (float)sqrt(dx * dx + dy * dy + dz * dz);
    dx *= inv;
    dy *= inv;
    dz *= inv;

    hres->GetPos();
    FUN_00b0fd00(&dir, &dir, &dir, 2.0f);

    if ((float)sqrt(dx * dx + dy * dy + dz * dz) > 1.5258789e-05f) {
        if ((float)sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z) > 1.5258789e-05f) {
            if (FUN_01021080() == 0) {
                Vec3 f = *hres->GetPos();
                float n = 1.0f / (float)sqrt(f.x * f.x + f.y * f.y + f.z * f.z);
                dir.x = f.x * n;
                dir.y = f.y * n;
                dir.z = f.z * n;
            }
            Quat out;
            FUN_0069b600(&out, &dir, &dir);
            c->mSpat.SetOrientation(&out);
        }
    }
    return true;
}

// @ 0x00da62d0
void __cdecl FUN_00da62d0(cSPCreatureCitizen* c, cTribe* tribe, u32 lo, u32 hi)
{
    void* block = c->mpBTree->mStimuli.Play(lo, hi);
    if (block == 0)
        return;

    cSPCreatureCitizen* other = (cSPCreatureCitizen*)FUN_00d994c0(FUN_00d999d0(block));
    void* r1 = FUN_00d998d0(block, 0x116d858);
    void* r2 = FUN_00d998d0(block, 0xee02c7);
    void* r3 = FUN_00d998d0(block, 0x4f396a66);

    if ((other != 0 && other->GetTribe() == tribe)
        || (r3 != 0 && (cTribe*)r3 == tribe)
        || (r2 != 0 && ((Res58*)r2)->GetTribeField() == tribe)
        || (r1 != 0 && ((ResTribe*)r1)->Get() == tribe))
    {
        c->mpBTree->mStimuli.ClearAll(lo, hi);
        int* p = c->mpBTree->FirstPending();
        if (p != 0 && FUN_00da6090((u32)*p) == (((u64)hi << 32) | lo)) {
            c->mpBTree->PopFront();
            c->mpBTree->mStimuli.ClearAll(0x1d3fbffa, 0x8124080);
        }
    }
}

// @ 0x00da6470
float __cdecl FUN_00da6470(cSPCreatureCitizen* c)
{
    return (c->mF5e0 <= 1.5258789e-05f) ? _HK_REAL_ONE : 0.0f;
}

// @ 0x00da64b0
float __cdecl FUN_00da64b0(cSPCreatureCitizen* c)
{
    if (c->mF5e0 <= 1.5258789e-05f && !c->mbDead) {
        cTribe* t = c->GetTribe();
        if (t != 0)
            return (t->GetAdultPopulation() < 2) ? _HK_REAL_ONE : 0.0f;
    }
    return 0.0f;
}

// @ 0x00da6510
float __cdecl FUN_00da6510(cSPCreatureCitizen* c)
{
    if (FUN_00b5b800() != (void*)0x1654c02)
        return 0.0f;
    cTribe* t = c->GetTribe();
    if (t == 0)
        return 0.0f;
    return (c->mF5e0 <= 1.5258789e-05f || t->mF2c8 > 0.0f) ? _HK_REAL_ONE : 0.0f;
}

// @ 0x00da6570
float __cdecl FUN_00da6570(cSPCreatureCitizen* c)
{
    void* block = c->mpBTree->mStimuli.Play(0x100000, 0);
    if (block != 0 && ((ResBlock*)block)->mpTribe == c->GetTribe())
        return 1.0f;
    return 0.0f;
}

// @ 0x00da65b0
float __cdecl FUN_00da65b0(cSPCreatureCitizen* c)
{
    void* block = c->mpBTree->mStimuli.Play(0x100000, 0);
    c->GetTargetAsCreature();
    if (block != 0 && ((ResBlock*)block)->mpTribe == c->GetTribe())
        return 1.0f;
    return 0.0f;
}

// @ 0x00da65f0
float __cdecl FUN_00da65f0(cSPCreatureCitizen* c)
{
    c->mpBTree->mStimuli.ClearAll(0x4000, 0);
    return 1.0f;
}

// @ 0x00da6610
float __cdecl FUN_00da6610(cSPCreatureCitizen* c)
{
    return (float)(u8)c->GetTribe()->mF556;
}

// @ 0x00da6630
float __cdecl FUN_00da6630(cSPCreatureCitizen* c, void* a, void* b, void* d, behavior_stimuli* stimuli, u8* out)
{
    void* block = c->mpBTree->mStimuli.Play(0x8000, 0);
    void* n1 = FUN_00d99a10(block);
    if (n1 != 0) {
        ResNode* n2 = (ResNode*)FUN_00d998f0(n1);
        if (n2 != 0) {
            ResId* n3 = n2->GetSub();
            if (n3->GetId() != 0x2a034cd) {
                if (stimuli != 0)
                    stimuli->GetAny();
                stimuli->mTarget = n2;
                *out = 1;
                return 1.0f;
            }
        }
    } else {
        c->mpBTree->mStimuli.ClearAll(0x8000, 0);
    }
    return 0.0f;
}

// @ 0x00da66c0
float __cdecl FUN_00da66c0(cSPCreatureCitizen* c, void* a, void* b, void* d, behavior_stimuli* stimuli, u8* out)
{
    void* block = c->mpBTree->mStimuli.Play(0x100, 0);
    cSPCreatureCitizen* other = (cSPCreatureCitizen*)FUN_00d999d0(block);
    if (other != 0 && !other->mbDead) {
        float val = other->mF5e0;
        float health = other->mCombat.GetMaxHealth();
        if (val < health) {
            if (stimuli != 0)
                stimuli->GetAny();
            stimuli->mTarget = &other->mCombat;
            *out = 1;
            return 1.0f;
        }
    }
    FUN_00da6270(c, 5);
    return 0.0f;
}

// @ 0x00da6750
float __cdecl FUN_00da6750(cSPCreatureCitizen* c, void* a, void* b, void* d, behavior_stimuli* stimuli, u8* out)
{
    void* n1 = FUN_00d99a10(c->mpBTree->mStimuli.Play(0x400, 0));
    void* n2 = FUN_00d998f0(n1);
    if (n2 != 0) {
        if (stimuli != 0)
            stimuli->GetAny();
        stimuli->mTarget = n2;
        stimuli->mF18 = 7;
        *out = 1;
        return 1.0f;
    }
    c->mpBTree->mStimuli.ClearAll(0x400, 0);
    return 0.0f;
}

// @ 0x00da67c0
float __cdecl FUN_00da67c0(cSPCreatureCitizen* c, void* a, void* b, void* d, behavior_stimuli* stimuli, u8* out)
{
    void* r = FUN_00d998d0(c->mpBTree->mStimuli.Play(0x800, 0), 0x4f396a66);
    if (r != 0) {
        int v = ((Res4f*)r)->mTime.GetValue();
        if (v != 0) {
            if (stimuli != 0)
                stimuli->GetAny();
            stimuli->mValue = v;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00da6880
float __cdecl FUN_00da6880(cSPCreatureCitizen_s00da_6880* c, u32 a, u32 b, u8 flags, behavior_stimuli_s00da_6880* stim, u8* out)
{
    cSPCreatureCitizen_s00da_6880* ch = c->GetTribe()->GetChieftain();
    if (ch != 0) {
        AnimPlayRes* play = ch->mpBTree->mStimuli.Play(0, 0x80);
        if (play != 0) {
            cSPCreatureCitizen_s00da_6880* s = (cSPCreatureCitizen_s00da_6880*)FUN_00d999d0(play);
            if (s != 0 && s->mbDead == 0) {
                if (s->v20() == 0x18eb45e || s->mSubC0.v58() != 0) {
                    if (stim != 0)
                        stim->GetAny();
                    stim->mTarget = &s->mCombat;
                    stim->mF18 = 7;
                    *out = 1;
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00da7af0
bool FUN_00da7af0(Creature* p)
{
    if (p->mByte_b5e == 0) {
        Obj0xc0* o = &p->mObjC0;
        if (FUN_00b3d4d0()->FUN_00adb360(o) == 0) {
            o->V_ec();
            p->FUN_00c14750(0);
        }
    }
    return 1;
}

// @ 0x00da7b40
bool FUN_00da7b40()
{
    return FUN_00b3d4d0()->mField2c == 2;
}

// @ 0x00da7b60
void FUN_00da7b60(Creature* p)
{
    if (p->mByte_b5e == 0) {
        p->mObjC0.V_ec();
        p->FUN_00c14750(0);
    }
}

// @ 0x00da7b90
bool FUN_00da7b90(Creature* p)
{
    u32 f = p->mFlags110;
    if ((f & 0x100) != 0) {
        if (p->FUN_00c0e0c0(0x48601c0) == 0)
            p->PlayAnimation(0x48601c0, 1, -1);
        return 1;
    }
    if (p->mByte137 == 0 && (f & 0x1000) == 0) {
        if (p->FUN_00c0e0c0(0x493840c) == 0)
            p->PlayAnimation(0x493840c, 1, -1);
        return 1;
    }
    p->FUN_00c0bf10(0, 0x10000, 0, 0x10000, g_1486110, 0, 0, 0, 0, 0, 0);
    return 0;
}

// @ 0x00da7c30
void FUN_00da7c30(Creature* p)
{
    if (p->mByte_b5e == 0)
        p->FUN_00c14750(0);
}

// @ 0x00da7cc0
void IdleBlock::PickNewActivity()
{
    Creature* c = mpCreature14;
    i32 a = 0;
    i32 b;
    if (c->FUN_00c0b770() != 0) {
        b = g_MathRandom.RandomUint32Uniform(3) + 0x2c39001;
        a = g_MathRandom.RandomUint32Uniform(2) + 2;
        if (c->FUN_00c22a70() != 0) {
            void* t = c->FUN_00c22dc0();
            if (t != 0) {
                Obj9cec0* u = (Obj9cec0*)FUN_00c9cec0(t);
                if (u->mField28 != 0) {
                    b = u->mField28;
                    a = 1;
                }
            }
        }
    } else {
        b = g_MathRandom.RandomUint32Uniform(5) + 0x2fc3661;
    }
    mField00 = 1;
    mField08 = b;
    mField0c = a;
    mpCreature14->PlayAnimation(b, 1, -1);
    mField10 = (mpCreature14->mObjC0.V_58() != 0) ? g_14007f4 : g_1473c70;
}

// @ 0x00da7d90
bool FUN_00da7d90(Creature* p, i32, i32, i32, i32, IdleBlock* s)
{
    s->mpCreature14 = p;
    s->mField00 = 0;
    s->mField04 = -1;
    s->mField08 = -1;
    s->mField0c = 0;
    p->d0c0(6, 1);
    return 1;
}

// @ 0x00da7e70
bool FUN_00da7e70(Creature* p, i32, i32, i32, i32, S19* s)
{
    if (p->mpAgentOrders->mStimuli.Play(0, 0x10000) == 0)
        return 0;
    if (s->mByte08 != 0) {
        if (p->AnimationFinished(s->mField04) != 0) {
            p->mpAgentOrders->mStimuli.ClearAll(0, 0x10000);
            return 0;
        }
    } else {
        if (p->FUN_00c0e0c0(0x2481e14) == 0)
            p->PlayAnimation(0x2481e14, 1, -1);
    }
    return 1;
}

// @ 0x00da7ef0
void FUN_00da7ef0(Creature* p)
{
    p->FUN_00c14750(0);
    p->ForceOrdersUpdate();
}

// @ 0x00da7f10
void FUN_00da7f10(Creature* p)
{
    p->V_84(0, 0, 0);
    p->FUN_00c14750(0);
    p->ForceOrdersUpdate();
}

// @ 0x00da7f40
void FUN_00da7f40(Creature* p)
{
    if (p->mByte_b5e != 0)
        return;
    p->d0c0(6, 0);
    p->V_84(0, 0, 0);
    u8 b = (p->mObjC0.V_f8() == 0);
    p->FUN_00c14750(b);
    p->ForceOrdersUpdate();
}

// @ 0x00da7fa0
bool FUN_00da7fa0(Creature* p)
{
    p->mpAgentOrders->mStimuli.ClearAll(0, 0x10);
    return false;
}

// @ 0x00da8430
f32 FUN_00da8430(Creature* p)
{
    u32 h = p->mpAgentOrders->mStimuli.Play(0, 0x4000000);
    if (h != 0) {
        AnimObj* a = (AnimObj*)FUN_00d99a10(h);
        if (a != 0) {
            if (a->V_8() != 0) {
                AnimObj* b = (AnimObj*)a->V_8();
                f32* f1 = b->V_2c();
                f32* f2 = (f32*)p->mObjC0.V_2c();
                f32 dx = f2[0] - f1[0];
                f32 dy = f2[1] - f1[1];
                f32 dz = f2[2] - f1[2];
                f32 d2 = dx * dx;
                d2 = d2 + dy * dy;
                d2 = d2 + dz * dz;
                if (d2 < g_14774d0)
                    return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00da8580
f32 FUN_00da8580(Creature* p, i32, i32, i32, BehaviorStimuli* s, u8* out)
{
    AnimObj* a = (AnimObj*)FUN_00d99a10(p->mpAgentOrders->mStimuli.Play(0x8000, 0));
    if (a != 0) {
        AnimObj* b = (AnimObj*)FUN_00d998f0(a);
        if (b != 0) {
            void* c = b->V_5c(0xd0036e08);
            AnimObj* d = (AnimObj*)b->V_c();
            if (d->V_20() != (void*)0x2a034cd) {
                if (c != 0 && ((Creature*)c)->FUN_00c04710() != 0)
                    goto clear;
                if (s != 0)
                    s->GetAny();
                s->mField04 = b;
                *out = 1;
                return 1.0f;
            }
        }
    }
clear:
    p->mpAgentOrders->mStimuli.ClearAll(0x8000, 0);
    return 0.0f;
}

// @ 0x00da8630
void FUN_00da8630(int self)
{
    (void)self;
}

// @ 0x00da8a40
void FUN_00da8a40(int self)
{
    (void)self;
}

// @ 0x00da8c40
void FUN_00da8c40(int self)
{
    (void)self;
}

// @ 0x00da8e20
void FUN_00da8e20(int self)
{
    (void)self;
}

// @ 0x00da8f20
float10 f00da8f20(int creature)
{
    void* chief = GetChieftain(GetTribe((void*)creature));
    if (!chief)
        return (float10)-1;
    Vec3_s00da_8630* a = (Vec3_s00da_8630*)(*(void*(**)(int))(*(int*)(creature + 0xc0) + 0x2c))(creature + 0xc0);
    Vec3_s00da_8630* b = (Vec3_s00da_8630*)(*(void*(**)(int))(*(int*)((char*)chief + 0xc0) + 0x2c))((int)chief + 0xc0);
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    float d = dx * dx + dy * dy + dz * dz;
    float f = *(float*)((char*)chief + 0xcc) - *(float*)(creature + 0xcc);
    return (float10)(d * f);
}

// @ 0x00da8fe0
float10 f00da8fe0(void)
{
    float10 fVar1 = (float10)((Rng*)0x01601760)->RandomDoubleUniform();
    float10 fVar2 = (float10)0.1;
    float10 fVar3 = fVar1 * (float10)0.9 + fVar2;
    fVar1 = (float10)1;
    if (fVar3 < fVar1) {
        fVar1 = fVar3;
        if (fVar3 < fVar2)
            return fVar2 * (float10)g_half;
    }
    return fVar1 * (float10)g_half;
}
