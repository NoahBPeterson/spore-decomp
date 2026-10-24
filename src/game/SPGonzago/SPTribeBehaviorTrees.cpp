// src/game/SPGonzago/SPTribeBehaviorTrees.cpp -- migrated from slice(s) s00e11ab0, s00db9380, s00db3e90, s00db2fd0, s00db2060, s00daf820, s00dae980, s00dacd40, s00dabdf0, s00dab1f0, s00daa530, s00da9600, s00da8630, s00da7780, s00da6880, s00d9dce0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeBehaviorTrees.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cTribe.h"
#include "nSPBehaviorTree/behavior_memory_block.h"
#include "nSPBehaviorTree/decider.h"
#include "nSPBehaviorTree/decider_state.h"
#include <math.h>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cSPCreatureBase.h"
#include <intrin.h>
#include "SP/cPlanetModel.h"
#include "SP/cActionCircle.h"
#include "SP/cGameNounManager.h"
#include <new>

// ---- items of slice s00d9dce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct cMethodTable {
    void* mpSlots[0x100];                       // 0x000
};
class cDispatchObject {
public:
    void* Call(int nSlot) {
        return ((void* (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    char CallChar(int nSlot) {
        return ((char (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoid(int nSlot) {
        ((void (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    cMethodTable* mpTable;                      // 0x000
};
class cBehaviorStimuli {
public:
    void ClearAll(uint32_t nFlags, uint32_t nValue);
    void* Play(uint32_t nFlags, uint32_t nValue);
};
class nBehaviorTree {
public:
    uint8_t mPad000[0x08];                      // 0x000
    cBehaviorStimuli mStimuli;                  // 0x008

    uint8_t mPad_600[0x600 - 0x008 - sizeof(cBehaviorStimuli)];
    void* mpCurrentTask;                        // 0x600
};
struct cLeaderChoice {
    void* mpLeader;                             // 0x000
    uint32_t mnAnimId;                          // 0x004
    uint8_t mbChanged;                          // 0x008
};
class cLocationComponent {
public:
    void* GetObject();
    void* GetOwner();
};
class cSimCreature {
public:
    void* GetCombatTarget();
    void* GetTargetCreature();
    void* GetActionObject();
    int32_t GetBehaviorPhase();
    char IsGroupLeader();
    int32_t InterruptAnimation(uint32_t nAnimId, int32_t nA, int32_t nB);
    char AnimationFinished(uint32_t nAnimId);
    char WaitForAnimEvent(uint32_t nEventId, void* pData, int32_t nA,
                          uint32_t nAnimId, int32_t nB);
    void SetCombatEngaged(char bEngaged);
    void StopLocomotion(int32_t nA, int32_t nB);
    void* GetTargetData();
    void UpdatePose();
    void ResetPose();
    void UpdateTargetPose();
    void UpdateAttackTarget();
    void NotifyTargetLost();
    void UpdateWorldTarget();
    void* GetTargetRecord();

    uint8_t mPad000[0x34];                      // 0x000
    cLocationComponent mLocation;               // 0x034
    uint8_t mPad038[0x88];                      // 0x038
    cDispatchObject mMovement;                  // 0x0c0
    uint8_t mPad0c4[0xa88];                     // 0x0c4
    nBehaviorTree* mpBehaviorTree;              // 0xb4c
};
class cPoolObject {
public:
    virtual void Destroy(char bFree);           // slot 0x00
    virtual void AddRef();                      // slot 0x04
};
class cGroupMovement {
public:
    char PickLeader(cSimCreature* pCreature, void* pA, void* pB, void* pC,
                    void* pD, cLeaderChoice* pChoice);

    uint8_t mPad000[0x214];                     // 0x000
};
// ---- items of slice s00d9dce0 end

// ---- items of slice s00da6880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_f147c218;          // 0x0147c218
extern const float g_f147c21c;          // 0x0147c21c
extern const float g_f1473c70;          // 0x0147c21c-family duration (20.0f)
extern const float g_f13ec4d0;          // 0x013ec4d0 (100.0f)
extern const float g_f13eecd8;          // 0x013eecd8 (20.0f)
extern const float g_f1486110;          // 0x01486110 (5.0f)
extern const float g_f1687a0c;          // 0x01687a0c
extern const float g_f1687a10;          // 0x01687a10
extern const float g_f1687a14;          // 0x01687a14
extern const float g_f169f408;          // 0x0169f408
typedef unsigned char  u8;
typedef unsigned int   u32;
struct cSPCreatureCitizen;
struct cTribe;
struct behavior_stimuli;
struct cBehaviorTreeData;
struct cTool;
void* __cdecl FUN_00d999d0(void* block);                        // 0x00d999d0 WatchMemoryBlock
void* __cdecl FUN_00d998d0(void* block, u32 key);               // 0x00d998d0
void* __cdecl FUN_00ac80d0(void* block, u32 key);               // 0x00ac80d0
void* __stdcall FUN_00b3d2c0(int a, int b, int c);                // 0x00b3d2c0 RelationshipManager
void* __stdcall FUN_00af13b0(void* c, int n, float* out);        // 0x00af13b0
struct Obj50g {                                                  // FUN_00b3d480 result
virtual void g00();
virtual void g04();
virtual void g08();
virtual void g0c();
virtual void g10();
virtual void g14();
virtual void g18();
virtual void g1c();
virtual void g20();
virtual void g24();
virtual void g28();
virtual void g2c();
virtual void g30();
virtual void g34();
virtual void g38();
virtual void g3c();
virtual void g40();
virtual void g44();
virtual void g48();
virtual void g4c();
    virtual void v50(void* p);                                   // +0x50
};
Obj50g* __cdecl FUN_00b3d480();                                  // 0x00b3d480
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
struct CeeObj {                                                  // object returned by 0x00cee330
    char  mPad000[0x12c];
    u32   mState12c;                                             // +0x12c
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
struct behavior_stimuli {
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
struct cBehaviorTreeData {
    char             mPad00[8];
    behavior_stimuli mStimuli;                                   // +0x08
    char             mPad1c[0x1c8 - 0x08 - sizeof(behavior_stimuli)];
    u32              mFlags1c8;                                  // +0x1c8
    char             mPad1cc[0x1d8 - 0x1cc];
    u32              mKey1d8;                                    // +0x1d8

    void PopFront();                                             // 0x00bcaf40
};
struct cTool {                                                   // a tool object (has a combatant)
    char      mPad000[0x120];
    Combatant mCombat;                                           // +0x120
};
struct cTribe : VF16 {                                            // +0x60 slot60, +0xac slotac
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

    cSPCreatureCitizen* GetChieftain();                          // 0x00c8fd30
    cTool*              GetToolOfType(int type);                 // 0x00c8f6e0
};
struct RelMgr {                                                  // FUN_00b3d2c0 result
    int FUN_d00a70();                                            // 0x00d00a70
};
struct cAgentOrderManager {
    int FindSlot(int a, int b, int c, int d);                    // 0x00bca0c0
};
struct LayoutMgr {
    char LookupB();                                               // 0x00af0bd0
};
struct ResAnim : VF8 {
virtual void a20();
virtual void a24();
virtual void a28();
virtual void a2c();
virtual void a30();
virtual void a34();
virtual void a38();
virtual void a3c();
virtual void a40();
virtual void a44();
virtual void a48();
virtual void a4c();
virtual void a50();
virtual void a54();
    virtual int  v58();                                          // +0x58
};
struct cSPCreatureCitizen : Crt {
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
    cBehaviorTreeData*  mpBTree;                                 // +0xb4c
    char      mPadb50[0xb58 - 0xb50];
    u32       mFlagsB58;                                         // +0xb58
    char      mPadb5c[0xb5e - 0xb5c];
    u8        mbDead;                                            // +0xb5e

    cTribe* GetTribe();                                          // 0x00c22f50
    int     FUN_c22dc0();                                        // 0x00c22dc0
    float   FUN_c0b9c0();                                        // 0x00c0b9c0
    int     FUN_c0ee60();                                        // 0x00c0ee60
    char    FUN_bc9b50();                                        // 0x00bc9b50
    cSPCreatureCitizen* FUN_bc9b10();                            // 0x00bc9b10
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
extern const u32   g_a147c220[10];      // 0x0147c220 tool-type table
// ---- items of slice s00da6880 end

// ---- items of slice s00da7780 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 1)
#pragma pack(pop)
typedef unsigned short u16;
typedef int            i32;
typedef float          f32;
struct Creature;
struct cTribe_s00da_7780;
struct Strategy;
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
struct CCB;
struct Strategy {
    void* vptr;                            // +0x00
    void* V_6c_a()      { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x6c))(this); }
    CCB*  V_6c_b(Creature* p) { return (*(CCB* (__thiscall**)(void*, Creature*))(*(char**)this + 0x6c))(this, p); }
};
struct Manager0 {
    void* vptr;                            // +0x00
    void* FUN_00ac79d0();
    void  FUN_00ac7de0(void* q, void* c);
};
struct Mgr310 {
    void* vptr;                            // +0x00
    void FUN_00b453a0();
    void FUN_00b45410();
};
struct CCB {
    void FUN_00ccbb60();
};
struct EventLog {
    void PostFeedbackEvent();
};
struct Out9 { f32 f0; f32 f4; f32 f8; f32 fc; u8 b10; u8 b11; };
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
extern f32 g_14853bc;
extern f32 g_1485720;
extern f32 g_13eb95c;
extern u8  g_169f3b8;
Strategy* FUN_00cd40b0();
Manager0* FUN_00b3d2b0();
Mgr310* __stdcall FUN_00b3d310(void* o);
EventLog* __stdcall FUN_00b3d3e0(u32 a, u32 b, void* c, u32 d, u32 e, u32 f);
// ---- items of slice s00da7780 end

// ---- items of slice s00da8630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_f400;         // 0x013f0e84  400.0
extern "C" int   g_flag169f3b4;                              // 0x0169f3b4
extern "C" float g_dist169f3b0;                              // 0x0169f3b0
typedef long double    float10;
struct Vec3 { float x, y, z; };
struct PlayObj {
    void* Play(int a, int flags);                     // 0x00bc96a0 (thiscall)
    void  ClearAll(int a, int flags);                 // 0x00bc98f0 (thiscall)
};
void* GetAny(void* stimuli);                          // 0x00d997e0 (thiscall on stimuli)
struct Stimuli { void GetAny(); };                    // 0x00d997e0 thiscall
// ---- items of slice s00da8630 end

// ---- items of slice s00da9600 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef          int   s32;
#define F10 float
typedef float* (__thiscall *TFV)(void*);
typedef float  (__thiscall *TFF)(void*);
typedef int    (__thiscall *TFI)(void*);
typedef void*  (__thiscall *TFVU)(void*, u32);
typedef char   (__thiscall *TFCFF)(void*, float, float);
typedef u32    (__thiscall *TFU)(void*);
typedef char   (__thiscall *TFCI)(void*, int, float, float);
typedef s32    (__thiscall *TCi_p)(void*);
typedef void*  (__thiscall *TCp_p)(void*);
typedef s32    (__thiscall *TCi_pu)(void*, u32);
typedef s32    (__thiscall *TClookup)(void*, u32, void*);        // FUN_00af0bd0 (ecx = mgr)
float  __cdecl FUN_00c0b9c0(void* self);              // 0x00c0b9c0 (thiscall)
float  __cdecl FUN_00bfc490(void* self);              // 0x00bfc490 (thiscall)
void*  __cdecl FUN_00c22f50(void* self);              // 0x00c22f50 GetTribe (thiscall)
s32    __cdecl FUN_00c22dc0(void* self);              // 0x00c22dc0 (thiscall)
s32    __cdecl FUN_00c22dd0(void* self);              // 0x00c22dd0 (thiscall)
s32    __cdecl FUN_00c0b780(void* self);              // 0x00c0b780 (thiscall)
s32    __cdecl FUN_00c0b7a0(void* self);              // 0x00c0b7a0 (thiscall)
s32    __cdecl FUN_00c0d560(void* self, float a, float b); // 0x00c0d560 (thiscall)
void*  __cdecl FUN_00c420d0();                       // 0x00c420d0 (thiscall: ecx = self+0xc0)
void*  __cdecl FUN_00d99470(void* a);                 // 0x00d99470
void*  __cdecl FUN_00d994c0(void* a);                 // 0x00d994c0
void*  __cdecl FUN_00d99420(void* a, u32 b);          // 0x00d99420
void*  __cdecl FUN_00d996e0(void* a, void* b);        // 0x00d996e0
void*  __cdecl FUN_00d997e0(void* self);              // 0x00d997e0 behavior_stimuli::GetAny (thiscall)
s32    __cdecl FUN_00c8f730(void* self, u32 a);       // 0x00c8f730 (thiscall)
void   __cdecl FUN_00c8f470(void* self, u32 a, u32 b, u32 c, void* d); // 0x00c8f470 SetStimuli (thiscall)
s32    __cdecl FUN_00c8f6e0(void* self, u32 a);       // 0x00c8f6e0 GetToolOfType (thiscall)
void*  __cdecl FUN_00c8fe20(void* self);              // 0x00c8fe20 GetClosestWater (thiscall)
void   __cdecl FUN_00c24680(u32 a, u32 b, float c, u32 d, u32 e, u32 f); // 0x00c24680
void*  __cdecl FUN_00bc96a0(void* self, u32 a, u32 b); // 0x00bc96a0 Play (thiscall)
void   __cdecl FUN_00bc97f0(u32 a, u32 b, void* c, void* d); // 0x00bc97f0
void   __cdecl FUN_00bc98f0(void* self, u32 a, u32 b); // 0x00bc98f0 ClearAll (thiscall)
float  __cdecl FUN_00da82f0(void* tribe, u32 key);    // 0x00da82f0
float  __cdecl FUN_00da83b0(void* tribe, void* a);    // 0x00da83b0
s32    __cdecl FUN_00d00a70(void* a, void* b, u32 c);  // 0x00d00a70
char   __cdecl FUN_00da6b10(void* a, void* b);        // 0x00da6b10
void*  __cdecl FUN_00af13b0(void* a, u32 b, void* c);  // 0x00af13b0 CreateLayoutManager
s32    __cdecl FUN_00af0bd0(void* a, u32 b, void* c);  // 0x00af0bd0 LayoutMgr::LookupB
void*  __cdecl FUN_00b3d2c0(void);                    // 0x00b3d2c0 RelationshipManager
void*  __cdecl FUN_00b5b800(void);                    // 0x00b5b800 SP::GetCurrentGameMode
void*  __cdecl FUN_00ffbe50(void);                    // 0x00ffbe50 SP::GetUFOSimulator
void*  __cdecl FUN_00a1ad60(void* self);              // 0x00a1ad60 GetPlayerInventory (thiscall)
s32    __cdecl FUN_00c38990(void* self, u32 a);       // 0x00c38990 (thiscall)
void   __cdecl FUN_00c238b0(void* self);              // 0x00c238b0 UpdateCreatureToolInteractions
void*  __cdecl FUN_010407c0(void);                    // 0x010407c0 SP::GetSpaceRelationshipTuning
s32    __cdecl FUN_00b1fbf0(void* self);              // 0x00b1fbf0 (thiscall) predicate
// ---- items of slice s00da9600 end

// ---- items of slice s00daa530 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned int DAT_015d1164;  // 0x015d1164
extern void*  __cdecl FUN_00d99420(void* owner, uint32_t v);   // 0x00d99420
extern void*  __cdecl FUN_00d99500(void* a);                   // 0x00d99500
extern void*  __cdecl FUN_00d99a10(void* a);                   // 0x00d99a10
extern void*  __cdecl FUN_00b3d4d0(void);                      // 0x00b3d4d0 GetTriggerMgr
extern long long __cdecl FUN_00da6090(uint32_t v);             // 0x00da6090
#define PVN(n) virtual void pv##n();
struct behavior_stimuli_s00da_a530 {
    int32_t  mStimulusID;        // +0x00
    void*    mTarget;            // +0x04
    void*    mValue;             // +0x08
    float    mF0c;               // +0x0c
    float    mF10;               // +0x10
    float    mF14;               // +0x14
    uint32_t mF18;               // +0x18
    void*    mF1c;               // +0x1c
    uint32_t mF20;               // +0x20

    void GetAny();               // 0x00d997e0 (thiscall)
};
union AV { float f; uint32_t u; void* p; };
struct AnimPlayRes_s00da_a530 {
    char pad000[8];
    AV   mF08;                   // +0x08
    AV   mF0c;                   // +0x0c
    AV   mF10;                   // +0x10
    AV   mF14;                   // +0x14
    AV   mF18;                   // +0x18
};
struct StimuliMgr {
    char  mPad[0x1c0];                                                 // +0x00

    AnimPlayRes_s00da_a530* Play(uint32_t lo, uint32_t hi);                       // 0x00bc96a0
    void  ClearAll(uint32_t lo, uint32_t hi);                          // 0x00bc98f0
    void  PlayWith(uint32_t lo, uint32_t hi, float v, void* t);        // 0x00bc97f0
};
struct StimOwner { int32_t mId; };   // stimuli owner block at btree+0x1d0
struct cBehaviorTreeData_s00da_a530 {
    char        pad004[8];
    StimuliMgr  mStimuli;                        // +0x08
    char        pad010[0x1c8 - 0x10];
    uint32_t    mFlags1c8;                       // +0x1c8
    uint32_t    mFlags1cc;                       // +0x1cc   (0x80000 tested)
    StimOwner   mOwner1d0;                       // +0x1d0
    char        pad1d4[0x1d8 - 0x1d4];
    uint32_t    mKey1d8;                         // +0x1d8
    char        pad1dc[0x5fc - 0x1dc];
    uint32_t    mFlags5fc;                       // +0x5fc   (0x800000 tested)

    void* FirstPending();                        // 0x00bca2c0
    void  PopFront();                            // 0x00bcaf40
};
struct Sub58_s00da_a530 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6)
    virtual char    s1c();                       // +0x1c
    virtual void*   s20();                       // +0x20
    PVN(9)
    virtual void*   s28();                       // +0x28
};
struct PosObj {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual Vec3* v2c();                         // +0x2c
    PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    virtual int32_t v58();                       // +0x58
    PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28)
    virtual float v74();                         // +0x74

    void* FUN_00c420d0();                        // 0x00c420d0 (non-virtual)
};
struct Tribe {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21) PVN(22) PVN(23)
    virtual float v60();                         // +0x60
    PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30) PVN(31) PVN(32) PVN(33) PVN(34)
    PVN(35)
    virtual void* v90();                         // +0x90
    char        pad004[0x120 - 0x04];
    PosObj      mObj120;                         // +0x120 (embedded)
    char        pad124[0x26c - 0x124];
    int32_t     mToolId26c;                      // +0x26c
};
struct Creature_s00da_a530 {
    void**               mpVtbl;                 // +0x00
    char                 pad004[0x58 - 0x04];
    Sub58_s00da_a530                mSub58;                 // +0x58
    char                 pad05c[0xc0 - 0x5c];
    PosObj               mC0;                    // +0xc0
    char                 padC4[0xb20 - 0xc4];
    int32_t              mIdB20;                 // +0xb20
    char                 padB24[0xb4c - 0xb24];
    cBehaviorTreeData_s00da_a530*   mpB4C;                  // +0xb4c

    Tribe* GetTribe();                           // 0x00c22f50
    void   FUN_00c26450();                       // 0x00c26450
    int32_t FUN_00c12400(uint32_t id);           // 0x00c12400 AnimationFinished
    int32_t FUN_00c12190(uint32_t id, int32_t a, int32_t b);  // 0x00c12190 PlayAnimation
    int32_t FUN_00c22a70();                      // 0x00c22a70
    int32_t FUN_00c22dc0();                      // 0x00c22dc0
    char    FUN_00c0ba30();                      // 0x00c0ba30
    char    FUN_00c0b770();                      // 0x00c0b770
};
struct Has5C {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21) PVN(22)
    virtual void* v5c(uint32_t hash);            // +0x5c
};
struct Has34 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12)
    char  pad004[0x34 - 0x04];
    PosObj m34;                                  // +0x34
};
struct HasB8 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30)
    PVN(31) PVN(32) PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40)
    PVN(41) PVN(42) PVN(43) PVN(44) PVN(45)
    virtual Creature_s00da_a530* v_b8(uint32_t hash);       // +0xb8
};
struct CrtVt {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30)
    PVN(31) PVN(32) PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40)
    PVN(41) PVN(42) PVN(43) PVN(44)
    virtual void* v45(uint32_t hash);            // +0xb4
};
struct Obj70 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6)
    virtual int32_t o1c();                       // +0x1c
    PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17)
    PVN(18) PVN(19) PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27)
    char    pad004[0x70 - 0x04];
    int32_t m70;                                 // +0x70
};
struct TgtE {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual char  e2c();                         // +0x2c
    PVN(12)
    char    pad004[0x34 - 0x04];
    PosObj m34;                                  // +0x34

    char FUN_00c38990(int32_t a);                // 0x00c38990
};
struct ObjC {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7)
    virtual void* v20();                         // +0x20

    char FUN_00c0c0e0();                         // 0x00c0c0e0
};
struct ResObj {
    PVN(0) PVN(1)
    virtual void* v08();                         // +0x08
    virtual void* v0c();                         // +0x0c
    PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13)
    PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21) PVN(22) PVN(23)
    virtual void v60();                          // +0x60
    virtual void v64();                          // +0x64
};
struct SelObj0 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual Vec3* v2c();                         // +0x2c
    PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30) PVN(31)
    PVN(32) PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40) PVN(41)
    PVN(42) PVN(43) PVN(44) PVN(45) PVN(46)
    virtual void mbc();                          // +0xbc
    virtual void mc0();                          // +0xc0
};
struct SelObj {
    char    pad000[0x1c];
    void**  mpBegin;                             // +0x1c
    void**  mpEnd;                               // +0x20
    char    pad024[0x18c - 0x24];
    void*   mpBest;                              // +0x18c
    char    pad190[0x194 - 0x190];
    float   mX;                                  // +0x194
    float   mY;                                  // +0x198
    float   mZ;                                  // +0x19c
};
struct PState { char pad00[0x2d]; uint32_t m2d; };              // 00daa530 arg8
struct StateAC {
    Obj70*   mpObj;          // +0x00
    int32_t  mPad04;         // +0x04
    uint8_t  mFlag08;        // +0x08
    char     mPad09[0x10 - 0x09];
    long long mVal10;        // +0x10  (used as two int32 halves)
};
struct StateF0 { int32_t m00; float m04; uint8_t mFlag08; };     // 00daadf0
struct StateEC { TgtE*   pObj; float mRadius2; };                // 00daaec0
struct State60 { int32_t m00; float m04; float m08; };           // 00daaf60
struct OrderSub {                       // lives at record+0x39
    uint32_t* mObj;         // +0x00
    char      pad004[0x0c];
    uint8_t   mFlag;        // +0x10
    char      pad011[1];
    int16_t   mShort;       // +0x12
};
struct OrderRec_s00da_a530 {
    int32_t  mType;          // +0x00
    char     pad004[0x35];
    OrderSub mSub;           // +0x39
};
struct SimB {
    int32_t  FUN_00bc3db0(uint32_t id);                 // 0x00bc3db0
    int32_t* FUN_00bc7610(uint32_t a, uint32_t b);      // 0x00bc7610
};
struct RandomLCG {
    double RandomDoubleUniform();                       // 0x009360d0
};
extern SimB*  __cdecl FUN_00b3d4e0(void);                      // 0x00b3d4e0
// ---- items of slice s00daa530 end

// ---- items of slice s00dab1f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct Spatial {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();             // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual bool vf58();                           // +0x58
    PV(23) PV(24) PV(25) PV(26)
    virtual const float* FUN_v6c(float* out);      // +0x6c (six-float box)
    PV(28)
    virtual float GetRadius();                     // +0x74
    bool IsNearGoal();                             // 0x00c42e20
};
struct Citizen;
struct Tribe_s00da_b1f0 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21) PV(22) PV(23)
    virtual float FUN_v60();                       // +0x60
    float* FUN_00c986d0(uint32_t param, int* out, Citizen* c);   // 0x00c986d0, ret 0xc
    uint32_t pad04[(0x120 - 4) / 4];
    Spatial  mPos;                                 // +0x120
};
struct AnimCtl {
    uint32_t PlayIdleAnimation(int id, int flags);              // 0x00bc96a0, ret 8
    void FUN_00bc97f0(int a, int b, float c, int d);            // ret 0x10
};
struct AnimOwner {
    uint32_t pad[2];
    AnimCtl  mCtl;                                 // +0x08
};
struct Citizen {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool vf2c();                           // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    virtual void vf84(void* part, int a, int b);   // +0x84

    Tribe_s00da_b1f0* GetTribe();                             // 0x00c22f50
    int    FUN_00bf3a90();                         // 0x00bf3a90
    void   FUN_00c9d150();                         // 0x00c9d150
    bool   AnimationFinished(int id);              // 0x00c12400, ret 4
    int    PlayAnimationWithTarget(int id, Vec3* p, int a);   // 0x00c14910, ret 0xc
    void   MoveToPointAndFacingAtSpeed(int mode, Vec3* p, Vec3* d, float a, float b); // 0x00c1c5c0, ret 0x14

    uint32_t  pad04[(0x34 - 4) / 4];
    Spatial   mBundle;                             // +0x34
    uint32_t  pad38[(0xc0 - 0x38) / 4];
    Spatial   mLoco;                               // +0xc0
    uint32_t  padc4[(0x120 - 0xc4) / 4];
    uint8_t   mPart120[16];                        // +0x120
    uint32_t  pad130[(0xb48 - 0x130) / 4];
    void*     mpB48;                               // +0xb48
    AnimOwner* mpAnim;                             // +0xb4c
};
struct GetToolState {
    Citizen* mpOther;   // +0x00
    float    mPosX;     // +0x04
    float    mPosY;     // +0x08
    float    mPosZ;     // +0x0c
    uint32_t mTribe;    // +0x10
    int      mState;    // +0x14
    int      miResult;  // +0x18
    int      miAnim;    // +0x1c
};
struct ToolNode {
    uint32_t pad[0x1b0 / 4];
    Vec3     mPos;                                 // +0x1b0
};
struct TaskMgr {
    ToolNode* Find(uint32_t kind, void* fn, void* key);   // 0x00bca620, ret 0xc
};
TaskMgr* FUN_00bc9b00();                                   // 0x00bc9b00
struct IteratorB9 {
    bool     FUN_00bc9b50();                       // 0x00bc9b50
    Citizen* FUN_00bc9b10();                       // 0x00bc9b10
};
namespace SP {
Vec3* normalized_safe(Vec3* out, const Vec3* in);          // 0x00449c20
}
// ---- items of slice s00dab1f0 end

// ---- items of slice s00dabdf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01572070;
extern float DAT_0157206c;
extern float DAT_01581298;
extern float DAT_015812a0;
extern float DAT_0158129c;
extern float DAT_01687a00;
extern float DAT_01485720;
typedef unsigned char  byte;
#define VT(o, off)  (*(void***)(o))[(off) / 4]
typedef void  (__thiscall *Fn_v) (void*);
typedef void* (__thiscall *Fn_p) (void*);
typedef bool  (__thiscall *Fn_b) (void*);
typedef float (__thiscall *Fn_f) (void*);
typedef void* (__thiscall *Fn_p1)(void*, void*);
typedef float (__thiscall *Fn_f1)(void*, float);
typedef void* (__thiscall *Fn_ac)(void*);
struct Vec3_s00da_bdf0
{
    float x, y, z;

    void FUN_00c8ef20();         // in-place normalize, this = vector
};
struct Citizen_s00da_bdf0;
struct CTribe;
struct CTool;
struct CBehaviour;
struct LayoutMgr_s00da_bdf0;
struct CTool34                    // secondary object carried at +0x34
{
    void** mpVtbl;               // +0x00 of the subobject
};
struct CTool
{
    void**   mpVtbl;             // +0x00
    char     pad04[0x30];
    CTool34  m34;                // +0x34
    char     pad38[0x12c - 0x38];
    int      m12c;               // +0x12c
    char     pad130[0x21c - 0x130];
    int      m21c;               // +0x21c
};
struct CSelf34
{
    float FUN_00cee380();        // this = citizen + 0x34
};
struct CreatureBase              // primary base of Citizen, +0x00..+0xbf
{
    char     pad00[0x34];
    CSelf34  m34;                // +0x34
    char     pad38[0xc0 - 0x38];
};
struct C41Obj
{
    char pad00[0x5c];
    int  m5c;                    // +0x5c

    Vec3_s00da_bdf0* FUN_00c423c0();        // this = object returned by FUN_00c41ec0
};
struct CLoco                     // secondary base of Citizen at +0xc0
{
    void**  mpVtbl;              // +0xc0 (absolute)
    char    pad04[0x50 - 0x04];
    int     m110;                // +0x110 (absolute)
    char    pad54[0x270 - 0x54];

    bool    IsNearGoal();
    C41Obj* FUN_00c41ec0();
};
struct CCombatant
{
    int  mDummy[2];

    void PartialRepair(float amount);
};
struct CB54Obj
{
    char  pad00[0x80];
    float mf80;                  // +0x80
};
struct CNeighborInfo
{
    char     pad00[0x10];
    unsigned mi10;               // +0x10
    char     pad14[0x1a4 - 0x14];
    unsigned mi1a4;              // +0x1a4
};
struct CB4CObj
{
    char           pad00[0x600];
    CNeighborInfo* mp600;        // +0x600
};
struct Citizen_s00da_bdf0 : CreatureBase, CLoco
{
    int        m330;             // +0x330
    char       pad334[0x5a8 - 0x334];
    CCombatant mCombat;          // +0x5a8
    char       pad5b0[0xb4c - 0x5b0];
    CB4CObj*   mpB4C;            // +0xb4c
    char       padB50[4];
    CB54Obj*   mpB54;            // +0xb54
    int        mB58;             // +0xb58

    CTribe* GetTribe();
    void    FUN_00c14750(int a);
    void    FUN_00c0ba10();
    bool    FUN_00c25480(int a, int b);
    void    MoveToPointAtSpeed(int mode, const Vec3_s00da_bdf0* point, float s1, float s2);
    void    MoveToPointAndFacingAtSpeed(int mode, const Vec3_s00da_bdf0* point,
                                        const Vec3_s00da_bdf0* facing, float s1, float s2);
    int     FUN_00c22820();
    void    PlayAnimationWithTarget(unsigned anim, void* target, int a, int b);
    bool    WaitForAnimEventOrEnd(unsigned id, bool* out, int a, int b, int c);
    bool    AnimationFinished(int a);
    void    PlayAnimation(unsigned anim, int a, int b);
    int     FUN_00c22c40(int a);
    void    SetCurrentToolEffect(int a, int b);
    float   FUN_00c0b9c0();
    void    FUN_00c0b9d0(float f);
    bool    FUN_00c0b770();
};
struct CTribe120
{
    void** mpVtbl;               // +0x120 (absolute)
};
struct CTribe20c
{
    CTool* FUN_00cee330();       // this = tribe + 0x20c
};
struct CTribe
{
    char      pad00[0x120];
    CTribe120 m120;              // +0x120
    char      pad124[0x20c - 0x124];
    CTribe20c m20c;              // +0x20c
    char      pad210[0x260 - 0x210];
    CTool*    mp260;             // +0x260
    char      pad264[0x100];

    int   FUN_00c97ca0(int id, Citizen_s00da_bdf0* c);
    int   FUN_00c97c40(int id, Citizen_s00da_bdf0* c);
    void  FUN_00c97d40(int id, Citizen_s00da_bdf0* c);
    void  FUN_00c979e0(Vec3_s00da_bdf0* out, int id, Citizen_s00da_bdf0* c);
    void  FUN_00c97b10(Vec3_s00da_bdf0* out, int id, Citizen_s00da_bdf0* c);
    Vec3_s00da_bdf0* FUN_00c986d0(int id, int* out, Citizen_s00da_bdf0* c);
};
struct CBehaviour
{
    bool FUN_00ac7ef0(Citizen_s00da_bdf0* self, CTool* target);
    void FUN_00ac7d10(float f, int a, CTribe* tribe);
};
struct LayoutMgr_s00da_bdf0
{
    bool FUN_00af0bd0();
};
struct CXY
{
    void FUN_00cc5170();
};
struct EatTickState
{
    int    mi00;                 // +0x00
    int    mi04;                 // +0x04
    int    mi08;                 // +0x08
    CTool* mp0c;                 // +0x0c
    int    mi10;                 // +0x10
};
struct HiveState
{
    int   mi00;                  // +0x00
    int   mi04;                  // +0x04
    int   mi08;                  // +0x08
    float mf0c;                  // +0x0c
    float mf10;                  // +0x10
};
CBehaviour* FUN_00b3d2b0_s00da_bdf0();                        // cdecl, no args
bool        FUN_00da6270(Citizen_s00da_bdf0* self, int a);    // cdecl
CXY*        FUN_00cc8b10(Citizen_s00da_bdf0* self);           // __stdcall
LayoutMgr_s00da_bdf0*  FUN_00af13b0(Citizen_s00da_bdf0* self, int a, int b); // __stdcall
extern "C" void* __stdcall FUN_00b3d310_s00da_bdf0(CLoco* p);
Vec3_s00da_bdf0 normalized_safe(const Vec3_s00da_bdf0& v);               // struct return (hidden ptr)
struct C580Ref
{
    virtual void r00();
    virtual void r04();
};
struct C580Obj
{
    char    pad00[0x120];
    C580Ref* mp120;              // +0x120
};
struct C580
{
    char     pad00[4];
    void*    m04;                // +0x04
    char     pad08[0xc];
    C580Obj* mp14;               // +0x14

    void FUN_00dac580();
};
struct C90
{
    char pad00[8];
    int  m08;                    // +0x08
};
struct C5d0Obj
{
    char  pad00[0x64];
    void* mp64;                  // +0x64
    char  pad68[0x90 - 0x68];
    C90*  mp90;                  // +0x90
};
struct C05Vt
{
    virtual void  a00();
    virtual void  a04();
    virtual void  a08();
    virtual void* a0c(int id);
};
struct C05Result
{
    char  pad00[0xb5e];
    byte  mb5e;                  // +0xb5e
    char  padB5f[0xb84 - 0xb5f];
    float mfB84;                 // +0xb84
};
struct St630
{
    byte  mb0;                   // +0x00
    char  pad1[3];
    int   mi4;                   // +0x04
    int   mi8;                   // +0x08
};
struct St730
{
    byte  mb0;                   // +0x00
    char  pad1[3];
    int   mi4;                   // +0x04
};
struct Cb3d310Res
{
    void FUN_00b453a0();
    void FUN_00b45410();
};
// ---- items of slice s00dabdf0 end

// ---- items of slice s00dacd40 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3_s00da_cd40 { float x, y, z; Vec3_s00da_cd40() {} Vec3_s00da_cd40(float a, float b, float c) : x(a), y(b), z(c) {} };
}
namespace SP {
struct Quat { float x, y, z, w; };
}
namespace SP {
#define PV(n) virtual void pv##n();
}
namespace SP {
class cSPCreatureCitizen_s00da_cd40;
}
namespace SP {
class cTribe_s00da_cd40;
}
namespace SP {
struct Loco {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3_s00da_cd40* GetPosition();                       // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual const Vec3_s00da_cd40* GetFacing();                         // +0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetRadius();                               // +0x74
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(3a)
    virtual void vfec();                                     // +0xec
    char pad00[0x50 - 0x04];                                 // to +0x50 (vptr is +0x00)
    unsigned mFlags50;                                       // +0x50
    bool IsNearGoal();                                       // 0xc42e20 (direct call, this = loco)
};
}
namespace SP {
struct Obj5a8 {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual float GetFloat();                                // +0x58
    char pad00[0x80 - 0x04];                                 // to +0x80
    void FUN_00f924e0(float f);                              // 0xf924e0 (thiscall, float)
    void FUN_00bfc460(int a);                                // 0xbfc460 (thiscall, int)
};
}
namespace SP {
struct AnimState { char pad00[0x80]; float mWeight; };       // +0x80
}
namespace SP {
struct TribeSlot { Vec3_s00da_cd40 mPos; int mUnk0c; bool mbOccupied; };
}
namespace SP {
struct ToolObj {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3_s00da_cd40* GetPosition();                       // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetRadius();                               // +0x74
};
}
namespace SP {
struct TribeTool {
    char pad00[0x34];
    ToolObj mTool;                                           // +0x34
    char pad34[0x244 - 0x34 - sizeof(ToolObj)];
    int  mToolFlags;                                         // +0x244 (checked by FUN_00bf3a90)
};
}
namespace SP {
struct VignetteDef {
    char pad00[4];
    int  mKey;                                               // +0x04
    char pad08[0x7b4 - 8];
};
}
namespace SP {
struct VignetteRange { VignetteDef* mpBegin; VignetteDef* mpEnd; };
}
namespace SP {
struct VignetteMgr {
    VignetteRange* Find(unsigned key, int a);                // 0xbc7610 (ret 8)
    void* FUN_00bc3db0(int id);                              // 0xbc3db0 (ret 4)
    bool  FUN_00bc3df0(int id);                              // 0xbc3df0 (ret 4)
    bool  FUN_00bc4900(int id, cSPCreatureCitizen_s00da_cd40* c, int a);// 0xbc4900 (ret 0xc)
    void  FUN_00bc52a0(int id, cSPCreatureCitizen_s00da_cd40* c);       // 0xbc52a0 (ret 8)
    int   FUN_00bc65f0(const void* a, const Vec3_s00da_cd40* b, const Vec3_s00da_cd40* c);   // 0xbc65f0 (ret 0xc)
};
}
namespace SP {
struct VignetteList {
    void* FUN_00bcb0b0(unsigned key, int id, void* tag, const char* name);   // 0xbcb0b0 (ret 0x10)
};
}
namespace SP {
struct VignetteNode {
    char  pad00[0x10];
    int   mState10;                                          // +0x10 (1 while the vignette is running)
    char  pad14[0x1a4 - 0x14];
    int   mSlot;                                             // +0x1a4 (claimed tribe slot)
    int   mHandle;                                           // +0x1a8 (handle inside the vignette table)
    float mTimer;                                            // +0x1ac (time left, in seconds)
};
}
namespace SP {
struct BehaviorEnv {
    char pad00[8];
    struct Sub {
        void FUN_00bc97b0();                                 // 0xbc97b0 (clears the agent's order deque)
        void FUN_00bc97f0(int a, int b, float c, cSPCreatureCitizen_s00da_cd40* d);   // 0xbc97f0
        char pad[0x1f0];
    } mSub;                                                  // +0x08
    char pad1f8[0x600 - 0x1f8];
    VignetteNode* mpVignette;                                // +0x600
    char pad604[0x60c - 0x604];
    void* mpOrderHead;                                       // +0x60c (first pending agent order)
    void  FUN_00bcb430();                                    // 0xbcb430 (drops the vignette)
    void  FUN_00bcb480(VignetteNode* node, cSPCreatureCitizen_s00da_cd40* c, int a, int b);  // 0xbcb480
    void* FirstPending();                                    // 0xbca2c0 (first pending agent order, or 0)
};
}
namespace SP {
struct CorralVector {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3_s00da_cd40* GetPosition();                       // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual const Vec3_s00da_cd40* GetFacing(Vec3_s00da_cd40* out);                // +0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetRadius();                               // +0x74
};
}
namespace SP {
struct Corral { char pad00[0x70]; CorralVector mVec; };
}
namespace SP {
class cTribe_s00da_cd40 { public:
    char pad00[0x294];
    TribeSlot* mpSlotsBegin;                                 // +0x294
    TribeSlot* mpSlotsEnd;                                   // +0x298
    char pad29c[0x2c8 - 0x29c];
    float mTimer;                                            // +0x2c8
    char pad2cc[0x556 - 0x2cc];
    bool  mbFlag556;                                         // +0x556
    char pad557[0x19c4 - 0x557];
    Corral* mpCorral;                                        // +0x19c4

    TribeTool* GetToolOfType(int type);                      // 0xc8f6e0 (thiscall, ret 4)
    void       FUN_00c95cc0(cSPCreatureCitizen_s00da_cd40* c);          // 0xc95cc0 (thiscall, ret 4)
    Corral*    GetCorral();                                  // 0xc8fed0 (thiscall)
};
}
namespace SP {
class cPlanetModel_s00da_cd40 { public:
    void  DirectionToSurfacePosition(Vec3_s00da_cd40* out, const Vec3_s00da_cd40* in);      // 0xb815a0 (ret 8)
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3_s00da_cd40* pos);        // 0xb7f190 (ret 8)
    void  MakeRandomWorldPosition(Vec3_s00da_cd40* out, float a, float b);       // 0xb81780
};
}
namespace SP {
struct PlanetObj {
    void FUN_00b453a0(Loco* loco);                           // 0xb453a0 (thiscall, ret 4)
};
}
namespace SP {
struct ToolState {                                           // behavior memory block of CHIEFTAIN_TOOL_INSPECT
    int  mAnimId;                                            // +0x00 (running inspect animation)
    int  mState;                                             // +0x04 (0 walk, 1 inspect, 2 wait)
    int  mAnim;                                              // +0x08 (animation handle written by the helper)
    int  mToolType;                                          // +0x0c
    Vec3_s00da_cd40 mToolPos;                                           // +0x10
    int  mPad1c;                                             // +0x1c
};
}
namespace SP {
struct VignetteMem {                                         // behavior memory block of IDLE_VIGNETTE_*
    int   mActive;                                           // +0x00 (vignette node, 0 until activated)
    char  pad04[4];
    int   mField08;                                          // +0x08
    int   mKey;                                              // +0x0c
    void* mSkip10;                                           // +0x10
    char  pad14[4];
    int   mVignetteIndex;                                    // +0x18
    int   mSlot;                                             // +0x1c
    unsigned mTableKey;                                      // +0x20
};
}
namespace SP {
struct DomesticateState {                                    // behavior memory block of TRIBE_DOMESTICATE
    int mState;                                              // +0x00
    int mAnimId;                                             // +0x04
    int mAnimId2;                                            // +0x08
    int mNoun;                                               // +0x0c
};
}
namespace SP {
class cSPCreatureCitizen_s00da_cd40 { public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23)
    virtual void vf90();                                     // +0x90
    char pad04[0xc0 - 0x04];                                 // to +0xc0 (vptr is +0x00)
    Loco mLoco;                                              // +0xc0
    char padc4[0x12f - 0xc0 - sizeof(Loco)];
    bool mbF12f;                                             // +0x12f
    char pad130[0x330 - 0x130];
    unsigned mFlags330;                                      // +0x330 (bit 0: movement finished)
    char pad334[0x5a8 - 0x334];
    Obj5a8    mObj5a8;                                       // +0x5a8
    char pad5ac[0xb20 - 0x5a8 - sizeof(Obj5a8)];
    void* mpSpecies;                                         // +0xb20
    char padb24[0xb4c - 0xb24];
    BehaviorEnv* mpEnv;                                      // +0xb4c
    char padb50[0xb54 - 0xb50];
    AnimState* mpAnim;                                       // +0xb54
    unsigned   mFlagsB58;                                    // +0xb58
    char padb5c[0xb5e - 0xb5c];
    bool       mbB5e;                                        // +0xb5e

    cTribe_s00da_cd40*  GetTribe();                                     // 0xc22f50
    void     FUN_00c14750(int a);                            // 0xc14750
    void     SetCurrentToolEffect(int effect, int a);        // 0xc24f40
    bool     AnimationFinished(unsigned id);                 // 0xc12400
    unsigned InterruptAnimation(unsigned id, int a, int b);  // 0xc12310
    unsigned PlayAnimation(unsigned id, int a, int b);       // 0xc12190
    unsigned PlayAnimationWithTarget(unsigned id, const Vec3_s00da_cd40* target, int a);               // 0xc14910
    unsigned PlayAnimationWithTarget2(unsigned id, const Vec3_s00da_cd40* target, int a, int b);       // 0xc14940
    unsigned InterruptAnimationWithTarget(unsigned id, const Vec3_s00da_cd40* target, int a, int b);   // 0xc149c0
    bool     WaitForAnimEventOrEnd(unsigned ev, int* out, int a, int b, int c);             // 0xc14ef0
    void     MoveToPointAtSpeed(int mode, const Vec3_s00da_cd40* p, float s0, float s1);                // 0xc1c1d0
    void     MoveToPointAndFacingAtSpeed(int mode, const Vec3_s00da_cd40* p, const Vec3_s00da_cd40* facing, float s0, float s1); // 0xc1c5c0
    bool     FUN_00c25480(int a, int b);                     // 0xc25480
    unsigned FUN_00c22820();                                 // 0xc22820
    void     TryJumpToTarget(int a, const Vec3_s00da_cd40* p, void* b, float c, int d);                // 0xc190e0
    void     d0c0(unsigned a, char b);                       // 0xc0d0c0 (CCB highlight)
};
}
namespace SP {
VignetteMgr*    FUN_00b3d4e0_s00da_cd40();                              // 0xb3d4e0 -> 0x0167eb54
}
namespace SP {
VignetteList*   FUN_00bc9b00_s00da_cd40();                              // 0xbc9b00 -> 0x0168b56c
}
namespace SP {
cPlanetModel_s00da_cd40*   PlanetModel();                               // 0xb3d350 -> 0x0167eaf8
}
namespace SP {
PlanetObj*      FUN_00b3d310();                              // 0xb3d310 -> 0x0167eae8
}
namespace SP {
Vec3_s00da_cd40*           normalized_safe(Vec3_s00da_cd40* out, const Vec3_s00da_cd40* in);  // 0x449c20
}
namespace SP {
Vec3_s00da_cd40*           FUN_0059aed0(Vec3_s00da_cd40* out, const Quat* a, const Quat* b);   // 0x59aed0
}
namespace SP {
void*           FUN_00d99500(int noun);                      // 0xd99500
}
namespace SP {
void            FUN_00da61e0(cSPCreatureCitizen_s00da_cd40* c, int noun);// 0xda61e0
}
namespace SP {
unsigned        FUN_00da6270(cSPCreatureCitizen_s00da_cd40* c, int noun);// 0xda6270
}
namespace SP {
float*          FUN_00c986d0(cTribe_s00da_cd40* tribe, int toolType, int* out, cSPCreatureCitizen_s00da_cd40* c);  // 0xc986d0
}
namespace SP {
void            FUN_00d9a4a0(Vec3_s00da_cd40* out, cSPCreatureCitizen_s00da_cd40* c, ToolObj* tool);                // 0xd9a4a0
}
namespace SP {
unsigned        RandomUint32Uniform(unsigned n);             // 0xa68fb0 (thiscall on gMathRandom)
}
namespace SP {
float           RandomFloatRange(float lo, float hi);        // 0x572a10
}
namespace SP {
void*           FUN_00c41ec0(Loco* loco);                    // 0xc41ec0 -> loco+0x1f4
}
namespace SP {
void*           FUN_00c423c0(void* p);                       // 0xc423c0
}
namespace SP {
extern float gMinSpeed;                                      // 0x01572070 (0.4f)
}
namespace SP {
extern float gMaxSpeed;                                      // 0x0157206c (0.6f)
}
namespace SP {
extern float gFloatMax;                                      // 0x0142ef7c (FLT_MAX)
}
// ---- items of slice s00dacd40 end

// ---- items of slice s00dae980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float    g_147c218, g_1581368, g_1581378, g_1485378;
extern float    g_1486110, g_169f3b8_s00da_e980, g_169f3bc, g_169f3c0;
extern float    g_13eecd8, g_1470f1c;
extern uint32_t g_1581288;
extern uint8_t  g_1581374;
#define PV_s00da_e980(n) virtual void v##n();
struct PtrList { int* mpBegin; int* mpEnd; };
struct GObj {
    virtual void Slot0();                    // 0x00
    virtual void Release();                  // 0x04
    PV_s00da_e980(2) PV_s00da_e980(3) PV_s00da_e980(4)
    virtual void Slot5();                    // 0x14
    PV_s00da_e980(6)
    virtual int32_t Slot7();                 // 0x1c
    PV_s00da_e980(8) PV_s00da_e980(9)
    virtual GObj* Slot10();                  // 0x28
    virtual Vec3* Slot11();                  // 0x2c
    PV_s00da_e980(12)
    virtual void Slot13();                   // 0x34
    PV_s00da_e980(14) PV_s00da_e980(15) PV_s00da_e980(16) PV_s00da_e980(17) PV_s00da_e980(18)
    virtual void* Slot19();                   // 0x4c
    PV_s00da_e980(20) PV_s00da_e980(21)
    virtual uint8_t Slot22();                // 0x58
    virtual GObj* Slot23(int);               // 0x5c
    virtual float Slot24f();                 // 0x60
    PV_s00da_e980(25) PV_s00da_e980(26) PV_s00da_e980(27) PV_s00da_e980(28)
    virtual float Slot29f();                 // 0x74
    PV_s00da_e980(30) PV_s00da_e980(31) PV_s00da_e980(32)
    virtual void Slot33(void*, int, int);    // 0x84
    PV_s00da_e980(34) PV_s00da_e980(35)
    virtual PtrList* Slot36();               // 0x90
    PV_s00da_e980(37) PV_s00da_e980(38) PV_s00da_e980(39) PV_s00da_e980(40) PV_s00da_e980(41) PV_s00da_e980(42) PV_s00da_e980(43) PV_s00da_e980(44)
    virtual int32_t Slot45(int);             // 0xb4
    virtual GObj* Slot46(int);               // 0xb8
    PV_s00da_e980(47) PV_s00da_e980(48) PV_s00da_e980(49) PV_s00da_e980(50) PV_s00da_e980(51) PV_s00da_e980(52) PV_s00da_e980(53) PV_s00da_e980(54) PV_s00da_e980(55) PV_s00da_e980(56)
    PV_s00da_e980(57) PV_s00da_e980(58)
    virtual void Slot59();                   // 0xec

    void Func_c17350(int, int);
    PtrList* FUN_00c420d0();                 // 0x00c420d0 (thiscall, non-virtual)
    uint8_t  IsNearGoal();                   // 0x00c42e20 (thiscall, non-virtual)
};
struct Sub5 {
    PV_s00da_e980(0) PV_s00da_e980(1) PV_s00da_e980(2) PV_s00da_e980(3) PV_s00da_e980(4) PV_s00da_e980(5) PV_s00da_e980(6) PV_s00da_e980(7) PV_s00da_e980(8) PV_s00da_e980(9) PV_s00da_e980(10)
    PV_s00da_e980(11) PV_s00da_e980(12) PV_s00da_e980(13) PV_s00da_e980(14) PV_s00da_e980(15) PV_s00da_e980(16) PV_s00da_e980(17) PV_s00da_e980(18) PV_s00da_e980(19) PV_s00da_e980(20) PV_s00da_e980(21)
    virtual float Slot22f();                 // 0x58
};
struct VObj0 { virtual void Slot0(int); };   // slot 0 takes one argument here
struct Slot250 {
    int32_t mFlags;                          // +0x000
    VObj0   mObj;                            // +0x004
    char    pad008[0x250 - 0x008];
};
struct SlotTable {
    int* mpBase;                             // +0x000
    int  FUN_00daed20(int idx);
};
struct Holder {
    void* FirstPending();                    // 0x00bca2c0 (thiscall)
    char  pad000[0x600];
    void* mp600;                             // +0x600 (tribe behaviour-tree node state)
};
struct TribeObj;
struct Sub34 {
    void* FUN_00cee330();                    // 0x00cee330 (thiscall)
};
struct CC {
    GObj    base;                            // +0x000
    char    pad004[0x034 - 0x004];
    Sub34   m34;                             // +0x034
    char    pad038[0x058 - 0x038];
    GObj    m58;                             // +0x058
    char    pad05c[0x0c0 - 0x05c];
    GObj    mC0;                             // +0x0c0
    char    pad0c4[0x120 - 0x0c4];
    GObj    m120;                            // +0x120
    char    pad124[0x556 - 0x124];
    uint8_t m556;                            // +0x556
    char    pad557[0x5a8 - 0x557];
    uint8_t m5a8[0x5e0 - 0x5a8];
    float   m5e0;                            // +0x5e0
    char    pad5e4[0xb20 - 0x5e4];
    void*   mpB20;                           // +0xb20
    char    padB24[0xb4c - 0xb24];
    Holder* mpB4C;                           // +0xb4c
    char    padB50[0xb58 - 0xb50];
    uint32_t mFlagsB58;                      // +0xb58
    uint8_t mByteB5c;                        // +0xb5c
    uint8_t padB5d;
    uint8_t mByteB5e;                        // +0xb5e

    bool AnimationFinished(int);             // 0x00c12400
    int32_t InterruptAnimation(int, int, int);// 0x00c12310
    void PlayAnimation(int, int, int);
    void Func_c14750(int);
    void RebuildCitizenOrderListDefault();   // 0x00c26c80
    int  FUN_00c22dc0();                     // 0x00c22dc0
    bool IsLeader();                         // 0x00c232d0
    TribeObj* GetTribe();                    // 0x00c22f50
    void MoveToPointAtSpeed(int, Vec3*, float, float);   // 0x00c1c1d0
};
struct State780 { GObj* mp0; };              // +0x00
struct State270 { GObj* mp0; GObj* mp4; };
struct S5 { char pad00[4]; uint8_t mb04; char pad05[0x0c - 0x05]; GObj* mp0c; };
struct Out { int32_t f0, f4, f8, fC, f10; };
struct A6 {
    char     pad00[4];
    GObj*    mp4;                            // +0x04
    char     pad08[0x18 - 0x08];
    uint32_t m18;                            // +0x18
};
struct ActState { GObj* mp0; float mf4; };   // +0x00, +0x04
uint32_t FUN_00da6270(CC*, int);             // 0x00da6270 (cdecl)
struct RefHolder { char pad0[4]; void Assign(void*); };    // 0x00b5f950 (thiscall)
struct NodeState980 {
    char      pad000[0x1a4];
    int32_t   mMode;                                       // +0x1a4
    RefHolder mpRef1a8;                                    // +0x1a8
    uint8_t   mFlag1ac;                                    // +0x1ac
    uint8_t   FUN_00a75010();                              // 0x00a75010 (thiscall)
};
struct RelMgr_s00da_e980 {
    float CalculateRelationshipAbsolute(void*, void*);
    void  FUN_00d00780(float);
    void  RecordEvent(void*, void*);
};
struct NounMgrX {
    int   GetPlayerEmpireOrMinus1();
    void* SetGameDataOwner2();
};
struct StimuliMgr_s00da_e980 {
    int  PlayIdleAnimation(int, int);        // 0x00bc96a0
    void FUN_00bc97f0(int, int, float, void*);
};
struct RandObj {
    uint32_t Next(uint32_t);                 // 0x00a68fb0
};
struct Container {
    void* getContainer();
    void  FUN_00ac7de0(void*, void*);
};
struct TribeObj : GObj {
    char    pad004[0x120 - 0x004];
    GObj    m120;                                          // +0x120
    char    pad124[0x2cc - 0x124];
    float   m2cc;                                          // +0x2cc
    char    pad2d0[0x556 - 0x2d0];
    uint8_t m556;                                          // +0x556
};
struct StateFlee { int32_t mMode; float mTimer; uint8_t mFlag8; };
RelMgr_s00da_e980*   RelationshipManager();                           // 0x00b3d2c0 (cdecl)
NounMgrX* NounManager();                                   // 0x00b3d300 (cdecl)
void*     NounByTag(int, float);                           // 0x00b3d300 with args
void*     FUN_00b3d2b0_s00da_e980();                                  // 0x00b3d2b0 (cdecl)
void      FUN_00da63e0(void*, void*);                      // 0x00da63e0 (cdecl)
float     GetPropertyT(int, int, float);                   // 0x004e1c70 (cdecl)
Vec3*     normalized_safe(Vec3*, Vec3*);                   // 0x00449c20 (cdecl)
Vec3*     FUN_0059aed0(Vec3*, Vec3*, Vec3*);               // 0x0059aed0 (cdecl)
float     RandomFloatRange(float, float);                  // 0x00572a10 (cdecl)
Vec3*     MakeRandomWorldPosition(Vec3*, void*, float, float);   // 0x00b81780
Vec3*     DirectionToSurfacePosition(Vec3*, Vec3*);        // 0x00b815a0
#define RAND_1601760 ((RandObj*)0x1601760)
// ---- items of slice s00dae980 end

// ---- items of slice s00daf820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t    DAT_01654c02;   // 0x01654c02
extern "C" void* __stdcall FUN_00cd3440(uint32_t guid); // 0x00cd3440
extern "C" void* __stdcall FUN_00cd40b0(uint32_t guid); // 0x00cd40b0 Instance
#define PV_s00da_f820(n) virtual void pv##n();
class IWin;
struct Vector3 { float x, y, z; };
class IWin {
 public:
    PV_s00da_f820(0)                                      // +0x00 AddRef
    PV_s00da_f820(1)                                      // +0x04 Release
};
class cLoco : public IWin {                    // creature +0xc0
 public:
    PV_s00da_f820(2) PV_s00da_f820(3) PV_s00da_f820(4) PV_s00da_f820(5) PV_s00da_f820(6) PV_s00da_f820(7) PV_s00da_f820(8) PV_s00da_f820(9) PV_s00da_f820(10)
    virtual float* pv11();                     // +0x2c  world position
    PV_s00da_f820(12) PV_s00da_f820(13) PV_s00da_f820(14) PV_s00da_f820(15) PV_s00da_f820(16) PV_s00da_f820(17) PV_s00da_f820(18) PV_s00da_f820(19) PV_s00da_f820(20) PV_s00da_f820(21)
    virtual char   pv22();                     // +0x58
    PV_s00da_f820(23) PV_s00da_f820(24) PV_s00da_f820(25) PV_s00da_f820(26) PV_s00da_f820(27) PV_s00da_f820(28) PV_s00da_f820(29) PV_s00da_f820(30) PV_s00da_f820(31) PV_s00da_f820(32)
    PV_s00da_f820(33) PV_s00da_f820(34) PV_s00da_f820(35) PV_s00da_f820(36) PV_s00da_f820(37) PV_s00da_f820(38) PV_s00da_f820(39) PV_s00da_f820(40) PV_s00da_f820(41) PV_s00da_f820(42)
    PV_s00da_f820(43) PV_s00da_f820(44) PV_s00da_f820(45) PV_s00da_f820(46) PV_s00da_f820(47) PV_s00da_f820(48) PV_s00da_f820(49) PV_s00da_f820(50) PV_s00da_f820(51) PV_s00da_f820(52)
    PV_s00da_f820(53) PV_s00da_f820(54) PV_s00da_f820(55) PV_s00da_f820(56) PV_s00da_f820(57) PV_s00da_f820(58)
    virtual void   pv59();                     // +0xec
    PV_s00da_f820(60) PV_s00da_f820(61)
    virtual char   pv62();                     // +0xf8
    char FUN_00c42e20();                       // 0x00c42e20 IsNearGoal
};
class cM120 : public IWin {                    // object +0x120
 public:
    PV_s00da_f820(2) PV_s00da_f820(3) PV_s00da_f820(4) PV_s00da_f820(5) PV_s00da_f820(6) PV_s00da_f820(7) PV_s00da_f820(8) PV_s00da_f820(9) PV_s00da_f820(10)
    virtual float* pv11();                     // +0x2c
    PV_s00da_f820(12) PV_s00da_f820(13) PV_s00da_f820(14) PV_s00da_f820(15) PV_s00da_f820(16) PV_s00da_f820(17) PV_s00da_f820(18) PV_s00da_f820(19) PV_s00da_f820(20) PV_s00da_f820(21)
    PV_s00da_f820(22) PV_s00da_f820(23)
    virtual double pv24();                     // +0x60
};
class cSpat34 : public IWin {                  // object +0x34
 public:
    PV_s00da_f820(2) PV_s00da_f820(3) PV_s00da_f820(4) PV_s00da_f820(5) PV_s00da_f820(6) PV_s00da_f820(7) PV_s00da_f820(8) PV_s00da_f820(9) PV_s00da_f820(10)
    virtual Vector3* pv11();                   // +0x2c
};
class cM5a8 : public IWin {                    // creature +0x5a8
 public:
    PV_s00da_f820(2) PV_s00da_f820(3) PV_s00da_f820(4) PV_s00da_f820(5) PV_s00da_f820(6) PV_s00da_f820(7) PV_s00da_f820(8) PV_s00da_f820(9) PV_s00da_f820(10)
    PV_s00da_f820(11) PV_s00da_f820(12) PV_s00da_f820(13) PV_s00da_f820(14) PV_s00da_f820(15) PV_s00da_f820(16) PV_s00da_f820(17) PV_s00da_f820(18) PV_s00da_f820(19) PV_s00da_f820(20)
    PV_s00da_f820(21)
    virtual double pv22();                     // +0x58
    void PartialRepair(float f);               // 0x00bfd1a0
};
class cMAnimPlayer {
 public:
    void* Play(int a, int b);                  // 0x00bc96a0
};
class cOrderMgr : public IWin {                // creature +0xb4c
 public:
    uint8_t      pad04[4];                     // +0x04
    cMAnimPlayer mAnim;                        // +0x08
    void FUN_00bcb480(void* node, void* a, int b, int c);    // 0x00bcb480
};
class cTribe_s00da_f820 : public IWin {                   // beast / tribe node object
 public:
    PV_s00da_f820(2)
    virtual IWin*  pv3(uint32_t id);           // +0x0c
    PV_s00da_f820(4) PV_s00da_f820(5) PV_s00da_f820(6) PV_s00da_f820(7) PV_s00da_f820(8) PV_s00da_f820(9) PV_s00da_f820(10)
    PV_s00da_f820(11) PV_s00da_f820(12) PV_s00da_f820(13) PV_s00da_f820(14) PV_s00da_f820(15) PV_s00da_f820(16) PV_s00da_f820(17) PV_s00da_f820(18) PV_s00da_f820(19) PV_s00da_f820(20)
    PV_s00da_f820(21)
    virtual IWin*  pv22();                     // +0x58
    PV_s00da_f820(23)
    virtual double pv24();                     // +0x60
    PV_s00da_f820(25) PV_s00da_f820(26) PV_s00da_f820(27) PV_s00da_f820(28) PV_s00da_f820(29) PV_s00da_f820(30) PV_s00da_f820(31) PV_s00da_f820(32)
    PV_s00da_f820(33) PV_s00da_f820(34) PV_s00da_f820(35) PV_s00da_f820(36) PV_s00da_f820(37) PV_s00da_f820(38) PV_s00da_f820(39) PV_s00da_f820(40) PV_s00da_f820(41) PV_s00da_f820(42)
    virtual void*  pv43();                     // +0xac
    uint8_t  pad04[0x30];                      // +0x04..+0x34
    cSpat34  m34;                              // +0x34
    uint8_t  pad38[0xe8];                      // +0x38..+0x120
    cM120    m120;                             // +0x120
    void  FUN_00c9d010();                      // 0x00c9d010
    void  FUN_00c9d020();                      // 0x00c9d020
    void* GetToolOfType(int t);                // 0x00c8f6e0
    void  FindSpot(void* a, int b);            // 0x00c98750
};
class cTribeModeStrategy : public IWin {
 public:
    void* FUN_00b6fa60();                      // 0x00b6fa60
    void  FUN_00cd6980();                      // 0x00cd6980
};
struct RefText {
    IWin* mpRef;
    RefText& operator=(IWin* p);               // 0x00b5f950 (out of line)
};
class cCreature : public IWin {                // cSPCreatureCitizen
 public:
    PV_s00da_f820(2) PV_s00da_f820(3) PV_s00da_f820(4) PV_s00da_f820(5) PV_s00da_f820(6) PV_s00da_f820(7) PV_s00da_f820(8) PV_s00da_f820(9) PV_s00da_f820(10)
    PV_s00da_f820(11) PV_s00da_f820(12) PV_s00da_f820(13) PV_s00da_f820(14) PV_s00da_f820(15) PV_s00da_f820(16) PV_s00da_f820(17) PV_s00da_f820(18) PV_s00da_f820(19) PV_s00da_f820(20)
    PV_s00da_f820(21) PV_s00da_f820(22) PV_s00da_f820(23) PV_s00da_f820(24) PV_s00da_f820(25) PV_s00da_f820(26) PV_s00da_f820(27) PV_s00da_f820(28) PV_s00da_f820(29) PV_s00da_f820(30)
    PV_s00da_f820(31) PV_s00da_f820(32)
    virtual void pv33(void* a, int b, int c);  // +0x84
    uint8_t  pad04[0xbc];                      // +0x04..+0xc0
    cLoco    mLoco_c0;                         // +0xc0
    uint8_t  padc4[0x4e4];                     // +0xc4..+0x5a8
    cM5a8    m5a8;                             // +0x5a8
    uint8_t  pad5ac[0x34];                     // +0x5ac..+0x5e0
    float    m5e0;                             // +0x5e0
    uint8_t  pad5e4[0x568];                    // +0x5e4..+0xb4c
    cOrderMgr* mB4c;                           // +0xb4c
    double FUN_00c0b9c0();                     // 0x00c0b9c0
    char   PutAwayToolExceptFor(int t);        // 0x00c22ca0
    void   SetToolOnAnimEvent(int);            // 0x00c263e0
    void   FUN_00c14750(bool v);               // 0x00c14750
    void   FUN_00c17350(uint32_t a, void* b);  // 0x00c17350
    cTribe_s00da_f820* GetTribe();                        // 0x00c22f50
    char   FUN_00c123f0(int anim);             // 0x00c123f0 AnimationFinished
    void   FUN_00c12190(int anim, int a, int b);   // 0x00c12190 PlayAnimation
    void   FUN_00c12310(int anim, int a, int b);   // 0x00c12310 InterruptAnimation
    char   FUN_00c0e0c0(int anim);             // 0x00c0e0c0
    void   MoveToPointAtSpeed(int a, const Vector3* p, float f1, float f2); // 0x00c1c1d0
    void*  FUN_00c22dd0();                     // 0x00c22dd0
    void*  FUN_00c22dc0();                     // 0x00c22dc0
    void   FUN_00c24f40(int a, int b);         // 0x00c24f40 SetCurrentToolEffect
    void   FUN_00c0b970(float f);              // 0x00c0b970
    void   FUN_00c26310(int a);                // 0x00c26310
};
struct CharState {                     // FUN_00dafc80 arg 6
    int32_t m00;                       // +0x00
    RefText m04;                       // +0x04
    Vector3 m08;                       // +0x08
    uint8_t m14;                       // +0x14
    uint8_t pad15[3];
    int32_t m18;                       // +0x18
};
struct GetState {                      // FUN_00dafc00 arg 6
    RefText m00;                       // +0x00
    uint8_t pad04[0xc];                // +0x04..+0x10
    void*   m10;                       // +0x10
    uint8_t pad14[4];                  // +0x14..+0x18
    int32_t m18;                       // +0x18
};
struct DeactState {                    // TRIBE_GET_TOOL_Deactivate arg 6
    uint8_t pad00[4];                  // +0x00..+0x04
    RefText m04;                       // +0x04
    uint8_t pad08[0xc];                // +0x08..+0x14
    uint8_t m14;                       // +0x14
    uint8_t pad15[3];
    int32_t m18;                       // +0x18
};
static void RefAssign(void** pp, void* p)
{
    void* old = *pp;
    if (p != old)
    {
        if (p != 0) ((IWin*)p)->pv0();
        *pp = p;
        if (old != 0) ((IWin*)old)->pv1();
    }
}
struct A7Obj {                       // owner object passed as arg 7
    uint8_t pad00[8];
    cTribe_s00da_f820* m08;                     // +0x08
};
// ---- items of slice s00daf820 end

// ---- items of slice s00db2060 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void *SP__EffectsManager();
extern "C" void *FUN_00b3d350(void *pOut, const void *pIn);
extern "C" void  operator_delete_array(void *p);
extern "C" float  sqrtf(float);
extern "C" float FUN_0104bdb0(void);
extern "C" void *FUN_00c9d9e0();
extern "C" void *SP__cPlanetModel__MakeRandomWorldPosition(void *pThis, void *a, void *b, float f1, float f2);
extern "C" void  cNavigationGoal__InitAt(void *pThis, void *pSrc);
extern "C" void  FUN_007a41a0(void *pThis);
typedef void  (__thiscall *F0v)(void *);
typedef void *(__thiscall *F0p)(void *);
typedef void  (__thiscall *F1p)(void *, void *);
typedef void  (__thiscall *F1u)(void *, u32);
typedef void  (__thiscall *F3p)(void *, void *, void *, int);
typedef int   (__thiscall *F1i_r)(void *, u32);
typedef void *(__thiscall *F1u_p)(void *, u32);
static inline void *VS(void *o, int off) { return *(void **)((char *)(*(void **)o) + off); }
static inline void *vc_p(void *o, int off) { return ((F0p)VS(o, off))(o); }
static inline void  vc_v(void *o, int off) { ((F0v)VS(o, off))(o); }
static inline void RefStore(void **ppDst, void *pNew)
{
    void *pOld = *ppDst;
    if (pNew == pOld)
        return;
    if (pNew != 0)
        vc_v(pNew, 0);
    *ppDst = pNew;
    if (pOld != 0)
        vc_v(pOld, 4);
}
struct TaskCtx {
    int   mState;    // +0x00
    void *mpRefA;    // +0x04
    void *mpRefB;    // +0x08
    void *mpRefC;    // +0x0c
    float mPosX;     // +0x10
    float mPosY;     // +0x14
    float mPosZ;     // +0x18
    char  mFlag1c;   // +0x1c
    char  mFlag1d;   // +0x1d
    int   mSpotIndex;// +0x20
    float mTimer;    // +0x24
};
extern "C" void *FUN_00da6270_s00db_2060(void *pTask, int code);
#define TCAL __fastcall
extern "C" void *TCAL SP__PlayIdleAnimation(void *pThis, int d, u32 a, u32 b);
extern "C" void  TCAL SP__InterruptAnimation(void *pThis, int d, u32 a, u32 b, u32 c);
extern "C" void  TCAL SP__PlayAnimation(void *pThis, int d, u32 a, u32 b, u32 c);
extern "C" void  TCAL SP__MoveToPointAtSpeed(void *pThis, int d, int a, void *pPos, float f1, float f2);
extern "C" void  TCAL SP__MoveToPointAndFacing(void *pThis, int d, int a, void *pPos,
                                               const void *pDir, float f1, float f2);
extern "C" char  TCAL SP__AnimationFinished(void *pThis, int d, int a);
extern "C" char  TCAL SP__IsNearGoal(void *pThis, int d);
extern "C" void *TCAL SP__CCM_e0c0(void *pThis, int d, int a);
extern "C" void  TCAL SP__CCB_cff0(void *pThis, int d, int a);
extern "C" void  TCAL SP__FUN_00c14750(void *pThis, int d, int a);
extern "C" char  TCAL SP__FUN_00c25480(void *pThis, int d, int a, int b);
extern "C" void *TCAL SP__FUN_00c41ec0(void *pThis, int d);
extern "C" void *TCAL SP__FUN_00c423c0(void *pThis, int d);
extern "C" float TCAL SP__FUN_00bfc490(void *pThis, int d);
extern "C" void  TCAL SP__FUN_00c9cf90(void *pThis, int d, int a);
extern "C" void  TCAL SP__FUN_00c9bef0(void *pThis, int d, int a);
extern "C" void *TCAL SP__FUN_00c986d0(void *pThis, int d, void *pOut, void *pB);
extern "C" void  TCAL SP__FindSpot(void *pThis, int d, int a, int b);
extern "C" void  TCAL SP__FUN_00f924e0(void *pThis, int d, float f);
extern "C" void *TCAL SP__FUN_00bca2c0(void *pThis, int d);
extern "C" void *TCAL SP__FUN_00b02b90(void *pThis, int d, int a);
static inline void *PlayIdleAnimation(void *p, u32 a, u32 b) { return SP__PlayIdleAnimation(p, 0, a, b); }
static inline void  InterruptAnimation(void *p, u32 a, u32 b, u32 c) { SP__InterruptAnimation(p, 0, a, b, c); }
static inline void  PlayAnimation(void *p, u32 a, u32 b, u32 c) { SP__PlayAnimation(p, 0, a, b, c); }
static inline void  MoveToPointAtSpeed(void *p, int a, void *q, float f1, float f2) { SP__MoveToPointAtSpeed(p, 0, a, q, f1, f2); }
static inline void  MoveToPointAndFacing(void *p, int a, void *q, const void *r, float f1, float f2) { SP__MoveToPointAndFacing(p, 0, a, q, r, f1, f2); }
static inline char  AnimationFinished(void *p, int a) { return SP__AnimationFinished(p, 0, a); }
static inline char  IsNearGoal(void *p) { return SP__IsNearGoal(p, 0); }
static inline void *CCM_e0c0(void *p, int a) { return SP__CCM_e0c0(p, 0, a); }
static inline void  CCB_cff0(void *p, int a) { SP__CCB_cff0(p, 0, a); }
static inline void  FUN_00c14750(void *p, int a) { SP__FUN_00c14750(p, 0, a); }
static inline char  FUN_00c25480(void *p, int a, int b) { return SP__FUN_00c25480(p, 0, a, b); }
static inline void *FUN_00c41ec0_s00db_2060(void *p) { return SP__FUN_00c41ec0(p, 0); }
static inline void *FUN_00c423c0_s00db_2060(void *p) { return SP__FUN_00c423c0(p, 0); }
static inline float FUN_00bfc490_s00db_2060(void *p) { return SP__FUN_00bfc490(p, 0); }
static inline void  FUN_00c9cf90(void *p, int a) { SP__FUN_00c9cf90(p, 0, a); }
static inline void  FUN_00c9bef0(void *p, int a) { SP__FUN_00c9bef0(p, 0, a); }
static inline void *FUN_00c986d0_s00db_2060(void *p, void *q, void *r) { return SP__FUN_00c986d0(p, 0, q, r); }
static inline void  FindSpot(void *p, int a, int b) { SP__FindSpot(p, 0, a, b); }
static inline void  FUN_00f924e0(void *p, float f) { SP__FUN_00f924e0(p, 0, f); }
static inline void *FUN_00bca2c0(void *p) { return SP__FUN_00bca2c0(p, 0); }
static inline void *FUN_00b02b90(void *p, int a) { return SP__FUN_00b02b90(p, 0, a); }
extern "C" void *normalized_safe_s00db_2060(void *pOut, const void *pIn);
struct EffectBlock {
    u32   mPad00[9];   // +0x00
    float mMat0;       // +0x24
    float mMat1;       // +0x28
    float mMat2;       // +0x2c
    float mMat3;       // +0x30
    float mMat4;       // +0x34
    float mMat5;       // +0x38
    float mMat6;       // +0x3c
    float mMat7;       // +0x40
    float mMat8;       // +0x44
    float mMat9;       // +0x48
    u32   mPad4c;      // +0x4c
    u16   mFlags;      // +0x50
    u16   mCount;      // +0x52
    float mPosX;       // +0x54
    float mPosY;       // +0x58
    float mPosZ;       // +0x5c
    float mOne;        // +0x60
    u32   mBody[9];    // +0x64
};
// ---- items of slice s00db2060 end

// ---- items of slice s00db2fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kPropDefaultA;                                // 0x013ec5b4
extern const float kPropDefaultB;                                // 0x01473c70
extern const float kSpeedScale;                                  // 0x0140e968
extern const float kProbeStep;                                  // 0x01470f1c
extern const float kInvalidPos;                                  // 0x0169f3b8
extern const char  kAllocFile[];                                 // 0x013ebb38
extern const char  kAllocTag[];                                  // 0x013f09b4
#define PV_s00db_2fd0(n) virtual void pv##n();
struct Vector3f { float x, y, z; };
class cPropSet;
enum { kPoolSlotStride = 0x250 };                                // bytes per pool slot
class IWin_s00db_2fd0 {
 public:
    PV_s00db_2fd0(0)
    virtual void  Release();                                     // +0x04
    virtual void  pv02(int a);                                   // +0x08
    virtual void* pv03(int index);                               // +0x0c
    virtual char  pv04();                                        // +0x10
    PV_s00db_2fd0(5)
    virtual void  pv06(void* msg);                               // +0x18
    PV_s00db_2fd0(7) PV_s00db_2fd0(8) PV_s00db_2fd0(9) PV_s00db_2fd0(10)
    virtual void* pv11();                                        // +0x2c
    virtual void* pv12();                                        // +0x30
    virtual void* pv13();                                        // +0x34
    virtual void  pv14(void* p);                                 // +0x38
    PV_s00db_2fd0(15) PV_s00db_2fd0(16) PV_s00db_2fd0(17) PV_s00db_2fd0(18) PV_s00db_2fd0(19) PV_s00db_2fd0(20) PV_s00db_2fd0(21) PV_s00db_2fd0(22)
    virtual void* pv23(float* out);                              // +0x5c
    PV_s00db_2fd0(24) PV_s00db_2fd0(25) PV_s00db_2fd0(26) PV_s00db_2fd0(27)
    virtual double pv28();                                       // +0x70
    PV_s00db_2fd0(29) PV_s00db_2fd0(30) PV_s00db_2fd0(31) PV_s00db_2fd0(32)
    virtual void  pv33();                                        // +0x84
    PV_s00db_2fd0(34) PV_s00db_2fd0(35) PV_s00db_2fd0(36) PV_s00db_2fd0(37) PV_s00db_2fd0(38) PV_s00db_2fd0(39) PV_s00db_2fd0(40) PV_s00db_2fd0(41) PV_s00db_2fd0(42) PV_s00db_2fd0(43) PV_s00db_2fd0(44)
    virtual cPropSet* pv45(void* a);                             // +0xb4

    void FUN_00bcb960(int a);                                    // 0x00bcb960
    void FUN_00bcc010();                                         // 0x00bcc010
};
class AutoRefCountText {
 public:
    AutoRefCountText& operator=(IWin_s00db_2fd0* p);                         // 0x00b5f950

    IWin_s00db_2fd0* mpRef;                                                 // +0x00
};
class cPropSet {
 public:
    uint8_t pad00[0x130];
    void*   mpProps_130;                                         // +0x130
};
class cSporeNounManager {
 public:
    IWin_s00db_2fd0* FUN_00daed70();                                        // 0x00daed70
};
class cPlanetModel {
 public:
    double FUN_00b7e4d0();                                       // 0x00b7e4d0
    char   RayCast(float* ray);                                  // 0x00b88770
    char   FUN_00b88f60(float dist, float* from, float* out);    // 0x00b88f60
};
class cSimLoco {
 public:
    PV_s00db_2fd0(0) PV_s00db_2fd0(1) PV_s00db_2fd0(2) PV_s00db_2fd0(3) PV_s00db_2fd0(4) PV_s00db_2fd0(5) PV_s00db_2fd0(6) PV_s00db_2fd0(7) PV_s00db_2fd0(8) PV_s00db_2fd0(9) PV_s00db_2fd0(10)
    virtual void* pv11(float a, void* b, float c, int d, int e); // +0x2c
    virtual void* pv12();                                        // +0x30

    char IsNearGoal();                                           // 0x00c42e20
};
class cSPCreatureBase : public IWin_s00db_2fd0 {
 public:
    void* PlayAnimation(int animId, int a, int b);               // 0x00c12190
    char  WaitForAnimEventOrEnd(int ev, int* out, int a, int anim, int b); // 0x00c14ef0
    char  AnimationFinished(int anim);                           // 0x00c12400
    void  SetCurrentToolEffect(int a, int b);                    // 0x00c24f40
    void  FUN_00c196a0(void* a, int b, int c);                   // 0x00c196a0
    void  MoveToPointAndFacingAtSpeed(int a, void* b, float c, float d); // 0x00c1c5c0
    void* InterruptAnimation(int a, int b, int c);               // 0x00c12310
    void* FUN_00c22820();                                        // 0x00c22820
    void  FUN_00c26310(int a);                                   // 0x00c26310

    uint8_t pad00[0xbc];                                         // IWin's vptr occupies +0x00..+0x04
    cSimLoco mLoco_c0;                                           // +0xc0
};
class cEffectsManager {
 public:
    PV_s00db_2fd0(0) PV_s00db_2fd0(1) PV_s00db_2fd0(2) PV_s00db_2fd0(3) PV_s00db_2fd0(4) PV_s00db_2fd0(5) PV_s00db_2fd0(6) PV_s00db_2fd0(7) PV_s00db_2fd0(8) PV_s00db_2fd0(9) PV_s00db_2fd0(10)
    virtual char AddEffect(int id, int a, void* out);             // +0x2c
};
class XformMsg {
 public:
    XformMsg();                                                  // 0x00434040
    void FUN_00571d40(const float* pos);                         // 0x00571d40

    uint16_t mFlags_00;                                          // +0x00
    uint16_t mCount_02;                                          // +0x02
    uint8_t  pad04[0x0c];                                        // +0x04
    float    mScale_10;                                          // +0x10
    float    mMatrix_14[9];                                      // +0x14
};
void* FUN_00f473a0(uint32_t size, const char* name, int a, uint32_t b,
                   const char* file, int line);                  // 0x00f473a0
void  FUN_00f47380(void* p);                                     // 0x00f47380
void  FUN_00da61e0(void* a, int b);                              // 0x00da61e0
void  FUN_00da6240(void* a, uint32_t b, int c);                  // 0x00da6240
float GetPropertyT_float(void* mgr, uint32_t id, float def);     // 0x004e1c70
cPlanetModel* FUN_00b3d350();                                    // 0x00b3d350
cSporeNounManager* NounManager_s00db_2fd0();                                // 0x00b3d300
cEffectsManager* EffectsManagerPtr();                            // 0x0067ddd0
void  SpawnLocatingCallResponse(void* a, void* b);               // 0x00d38cc0
char  Vector3_NotEqual(const float* a, const float* b);          // 0x0041dd30
float* normalized_safe(float* out, const float* in);             // 0x00449c20
void   Matrix3FromQuaternion(float* out, const float* q);        // 0x0059c190
class cGroupMovement_s00db_2fd0 {
 public:
    virtual void FUN_vtbl0(int a);                               // +0x00
};
struct cPoolSlotBits {
    uint32_t mNext : 30;                                         // index of next free slot
    uint32_t mUsed : 1;                                          // +0x1e
    uint32_t mFree : 1;                                          // +0x1f
};
struct cPoolSlot {
    union {
        uint32_t      mLink_00;                                  // +0x00
        cPoolSlotBits mBits;
    };
    cGroupMovement_s00db_2fd0 mObject;                                      // +0x04
};
struct cPoolNode {
    union {
        cPoolNode* mpFreeLink_00;                                // +0x00 free-list link
        uint32_t   mValue_00;                                    // +0x00 payload
    };
    uint32_t   mValue_04;                                        // +0x04
    uint32_t   mValue_08;                                        // +0x08
    uint32_t   mValue_0c;                                        // +0x0c
    cPoolNode* mpNext_10;                                        // +0x10
};
struct cPoolFind {
    cPoolNode* mpNode_00;                                        // +0x00
    cPoolNode** mpSlot_04;                                       // +0x04
};
class cResizableObjectPoolT {
 public:
    cGroupMovement_s00db_2fd0* GetObject(uint32_t index);                   // 0x00db3c40
    void  ReleaseSlot(uint32_t index);                           // 0x00db3c90
    cPoolFind* FindFreeSlot(cPoolFind* out, cPoolNode* node,
                            cPoolNode** head);                   // 0x00db3da0
    void  AllocNode(cPoolNode* src);                             // 0x00db3e30
    uint32_t FUN_00daed20(uint32_t index);                       // 0x00daed20

    uint8_t*       mpBegin_00;                                   // +0x00
    uint8_t*       mpEnd_04;                                     // +0x04
    uint8_t        pad08[4];                                     // +0x08
    int32_t        mCount_0c;                                    // +0x0c
    uint8_t        pad10[4];                                     // +0x10
    uint32_t       mIndex_14;                                    // +0x14
    uint32_t       mFreeHead_18;                                 // +0x18
    cPoolNode*     mpFreeList_1c;                                // +0x1c
    uint8_t        pad20[4];                                     // +0x20
    cPoolNode*     mpDeleteBegin_24;                             // +0x24
    cPoolNode*     mpDeleteEnd_28;                               // +0x28
    uint32_t       mNodeSize_2c;                                 // +0x2c
    cPoolNode*     mpSentinel_30;                                // +0x30
};
struct REACT_State {
    IWin_s00db_2fd0*            mpObj_00;                                   // +0x00 target
    int32_t          mPhase_04;                                  // +0x04 phase 0..6
    int32_t          mAnim_08;                                   // +0x08 animation handle
    AutoRefCountText mText_0c;                                   // +0x0c <IWinText> reference
};
struct SimuState {
    IWin_s00db_2fd0*   mpObj_00;                                            // +0x00
    int32_t mPhase_04;                                           // +0x04 phase 0, 2..9
    float   mPos_08[3];                                          // +0x08 destination
    int32_t mAnim_14;                                            // +0x14 animation handle
    IWin_s00db_2fd0*   mpEffect_18;                                         // +0x18 visual effect
};
// ---- items of slice s00db2fd0 end

// ---- items of slice s00db3e90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gSocialQueryManager;
extern void* gPlanetModelPointer;
extern float gMaxFloat;
typedef int intptr_t;
struct Vec3_s00db_3e90 {
    float mX;
    float mY;
    float mZ;
};
struct Vec4 {
    float mX;
    float mY;
    float mZ;
    float mW;
};
class IRefCounted {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void* Query(const void* pType);
    virtual void v10();
};
struct cMethodTable_s00db_3e90 {
    void* mSlots[0x100];
};
struct cObject {
    cMethodTable_s00db_3e90* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, void* pArg2) {
        return ((void* (*)(void*, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(this, nArg1, pArg2);
    }
    void* Call(int nSlot, void* pArg1, void* pArg2) {
        return ((void* (*)(void*, void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1, pArg2);
    }
    float CallFloat(int nSlot) {
        return ((float (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    char CallChar(int nSlot) {
        return ((char (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
};
class cPlanetModel_s00db_3e90 {
public:
    Vec3_s00db_3e90* DirectionToSurfacePosition(Vec3_s00db_3e90* pOut, const Vec3_s00db_3e90* pDirection);  // 0x00b815a0 (cPlanetModel::DirectionToSurfacePosition)
    float GetWaterHeight();  // 0x00b7e390 (cPlanetModel::GetWaterHeight)
};
class cGameNounManager : public IRefCounted {
public:
    void* GetNounByKey(uint32_t nKey);
};
class cBehaviorStimuli_s00db_3e90 {
public:
    void* GetAny();
    void* mPointers[8];                         // 0x00
};
struct cSocialTarget {
    cObject* mpObject;                          // 0x00
    float mfValue;                              // 0x04
    float mfX;                                  // 0x08
    float mfY;                                  // 0x0c
    float mfZ;                                  // 0x10
};
struct cGroupMovement_s00db_3e90 {
    uint8_t mPad000[0x18c];                     // 0x000
    float mfCooldown;                           // 0x18c
    float mfValue2;                             // 0x190
    float mfX;                                  // 0x194
    float mfY;                                  // 0x198
    float mfZ;                                  // 0x19c
    uint8_t mPad1a0[0x20];                      // 0x1a0
    float mfRangeSq;                            // 0x1c0
    cObject* mpOwner;                           // 0x1c4

    void Stop();
};
struct cActionState {
    void* mpTarget;                             // 0x00
    int mnState;                                // 0x04
    int mnAnimation;                            // 0x08
    int mnLoopCount;                            // 0x0c
    int mnEffectId;                             // 0x10
};
struct cSocialData {
    cObject* mpOwner;                           // 0x00
    uint8_t mPad04[0x08];                       // 0x04
    uint32_t mnHandle;                          // 0x0c
    float mfOffset;                             // 0x10
    float mfX;                                  // 0x14
    float mfY;                                  // 0x18
    float mfZ;                                  // 0x1c
    Vec4 mRotation;                             // 0x20
    uint8_t mbSnap;                             // 0x30
};
class cSocialActionHost {
public:
    bool CheckSocialTarget(cSocialTarget* pTarget);
    bool ResolveTarget(cActionState* pState);
    void ReleaseTarget(cActionState* pState);
    int Start(cActionState* pState);
    int Update(cActionState* pState);
    float TryTribeTool(uint32_t nA, uint32_t nB, uint32_t nFlags,
                       cBehaviorStimuli_s00db_3e90* pStimuli, uint8_t* pbFlag);
    int Cancel();
    void PlaceTargets(cSocialData* pData, bool bSnap);

    uint8_t mPad000[0x0c];                      // 0x000
    cObject* mpSocialQuery;                     // 0x00c
    uint8_t mPad010[0x48];                      // 0x010
    void** mpBuckets;                           // 0x058
    uint32_t mnBucketCount;                     // 0x05c
    uint8_t mPad060[0x144];                     // 0x060
    uint32_t mnGroupHandle;                     // 0x1a4
    uint8_t mPad1a8[0x84];                      // 0x1a8
};
class cGroupMovementPool {
public:
    void* GetObject(uint32_t nHandle);
    void ReleaseObject(uint32_t nHandle);
};
class cTribe_s00db_3e90 {
public:
    void* GetToolOfType(int nType);  // 0x00c8f6e0 (cTribe::GetToolOfType)
};
class cCombatant {
public:
    int GetDamageState();
};
void operator_delete__(void* pMemory);
void* ResizablePoolGet(uint32_t nHandle);
char IsSocialQueryActive();
cObject* GetSocialQueryObject();
void* GetSocialQueryManager();
void* GetTribe();
void* CreateSocialEffect(void* pThis);
char IsLeader(void* pCreature);
void PlaceTargetsEntry(void* pThis, cSocialData* pData, bool bSnap);
bool PlayIdleAnimation(cObject* pCreature, int nA, uint32_t nFlags);
void* WatchMemoryBlock(void* pAnimation);
int StartAnimation(cSocialActionHost* pHost, uint32_t nAnimId);
void ConfigureSocialQuery(cSocialActionHost* pHost, uint8_t* pBuffer, const char* pName);
void ResetGroupMovement(uint32_t nHandle);
void* GetCurrentActionTarget(cSocialActionHost* pHost, uint32_t nKey);
void BeginAnimation(cObject* pCreature, int nA, int nB);
void* FindNearbyObjects(cSocialActionHost* pHost, float fRadius, uint32_t nFlags,
                        void* pCallback, int nMode);
int InterruptAnimation(cObject* pCreature, uint32_t nAnimId, uint32_t nFlags, int nMode);
char AnimationFinished(cObject* pCreature, int nAnimation);
char WaitForAnimEventOrEnd(cObject* pCreature, uint32_t nEventId, int* pOut,
                           int nA, int nAnimation, int nB);
void SetCurrentToolEffect(cSocialActionHost* pHost, int nEffect, int nType);
void ClearStimuli(cObject* pCreature, int nA, uint32_t nFlags);
int PressBehaviourButton(int nA, uint32_t nFlags, float fValue, int nB);
int FinishAction(cSocialActionHost* pHost, int nState);
void* LookupToolByKey(uint32_t nKey);
char SpendTribePoints(int nCost, int nMode);
float RandomRange(float fMin, float fMax);
float GetCreativeCreatureRate();
void SetSocialTargetPointers(cBehaviorStimuli_s00db_3e90* pStimuli, int nValue);
void AddSocialTarget(cObject* pObject, uint32_t nKey, const Vec3_s00db_3e90* pPosition,
                     const Vec3_s00db_3e90* pDirection, cObject* pOwner, const Vec3_s00db_3e90* pFacing);
float GetNearbyRadius(cObject* pObject);
void* GetNearbyEntry(int nIndex);
int GetCombatantDamageState(cObject* pCombatant);
void Matrix3FromQuaternion(float* pOut, const Vec4* pQuaternion);
extern uint8_t gEmptySocialTarget[0x20];
extern cGroupMovementPool gGroupMovementPool;
// ---- items of slice s00db3e90 end

// ---- items of slice s00db9380 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3_s00db_9380 { float x, y, z; Vec3_s00db_9380() {} Vec3_s00db_9380(float a, float b, float c) : x(a), y(b), z(c) {} };
}
namespace SP {
struct Vec2 { float x, y; Vec2() {} Vec2(float a, float b) : x(a), y(b) {} };
}
namespace SP {
struct Loco_s00db_9380 {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3_s00db_9380* GetPosition();                       // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual bool IsAlive();                                  // +0x58
    virtual const Vec3_s00db_9380* GetFacing(Vec3_s00db_9380* out);                // +0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetRadius();                               // +0x74
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(3a)
    virtual void vfec();                                     // +0xec
};
}
namespace SP {
struct cCombatObj {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d)
    PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual float GetMaxHealth();                            // +0x58
    char pad00[0x38 - 0x04];
    float mHealth;                                           // +0x38
    void  PartialRepair(float fAmount);                      // 0xbfd1a0 (thiscall)
};
}
namespace SP {
class cHealTuningRecord;
}
namespace SP {
class cMotionQueue {
  public:
    void Play(int nA, int nB, float fC, void* pD);             // 0xbc97f0 (thiscall, cleans 0x10)
};
}
namespace SP {
class cCreatureEnv {
  public:
    void*        mpField00;                                    // +0x00
    int          mField04;                                     // +0x04
    cMotionQueue mMotion;                                      // +0x08
};
}
namespace SP {
class cAutoRefTarget {
  public:
    virtual void AddRef();                                     // +0x00
    virtual void Release();                                    // +0x04
};
}
namespace SP {
class cAutoRefCount {
  public:
    void Init(cAutoRefTarget* pObject);                        // 0x572660
    void Destroy()
    {
        if (mpObject)
            mpObject->Release();
    }

    cAutoRefTarget* mpObject;                                  // +0x00
};
}
namespace SP {
class cAutoRefVector {
  public:
    void PushBack(cAutoRefCount* pRef);                        // 0xe1c7f0

    cAutoRefCount* mpBegin;                                    // +0x00
    cAutoRefCount* mpEnd;                                      // +0x04
    cAutoRefCount* mpCapacity;                                 // +0x08
};
}
namespace SP {
struct cHealActionState {
    int  mToolId;                                            // +0x00 (tribe tool / noun handle)
    int  mStep;                                              // +0x04
    int  mAnimId;                                            // +0x08
    cHealTuningRecord* mpTuning;                             // +0x0c
    bool mbDone;                                             // +0x10
};
}
namespace SP {
class cRefCounted {
  public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d)
    PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b)
    PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e)
    virtual void AddRef();                                   // +0xbc
    virtual void Release();                                  // +0xc0
};
}
namespace SP {
class cSPCreatureCitizen_s00db_9380 {
  public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d)
    PV(0e) PV(0f) PV(10) PV(11)
    virtual void v48(int nArg);                              // +0x48
    virtual int  v4c();                                      // +0x4c
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b)
    PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b)
    virtual cHealTuningRecord* GetToolTuning(int nToolId);   // +0xb4

    // --- direct entry points used by this slice ---
    bool     HasAnim(unsigned nAnimationId);                 // 0xc0e0c0
    void     CancelToolAnim(int nArg);                       // 0xc14750
    unsigned InterruptAnimation(unsigned nAnimationId, int nVariant, int nFlags);          // 0xc12310
    unsigned PlayAnimation(unsigned nAnimationId, int nBlend, int nVariant);               // 0xc12190
    void     InterruptAnimationWithTarget(unsigned nAnimationId, void* pTarget, int nA, int nB); // 0xc149c0
    bool     AnimationFinished(unsigned nAnimationId);       // 0xc12400
    unsigned GetCurrentAnimationGUID();                      // 0xc0e040
    unsigned GetAnimationVariant();                          // 0xc22820
    bool     WaitForAnimEventOrEnd(unsigned nEvent, int* pOutValue, int nArg, int nAnimationId, int nFlag); // 0xc14ef0
    void     SetCurrentToolEffect(int nEffect, int nArg);    // 0xc24f40
    void     SetToolState(int nArg);                         // 0xc26310
    void     CancelTool(int nToolId, bool bA, bool bB);      // 0xc196a0
    void     MoveToPointAtSpeed(int nMode, const Vec3_s00db_9380* pPoint);   // 0xc1c1d0
    void     SetFlag(int nId, void* pArg);                   // 0xc0b370

    char     pad00[0x24 - 0x04];
    int      mSpeciesKey;                                    // +0x24
    char     pad28[0xc0 - 0x28];
    Loco_s00db_9380     mLoco;                                          // +0xc0
    char     padc4[0x5a8 - 0xc0 - sizeof(Loco_s00db_9380)];
    cCombatObj mCombat;                                      // +0x5a8
    char     pad5ac[0xb20 - 0x5a8 - sizeof(cCombatObj)];
    void*    mpSpecies;                                      // +0xb20
    char     padb24[0xb4c - 0xb24];
    cCreatureEnv* mpEnv;                                     // +0xb4c
    char     padb50[0xb58 - 0xb50];
    unsigned mFlagsB58;                                      // +0xb58
    char     padb5c[0xb5e - 0xb5c];
    bool     mbB5e;                                          // +0xb5e
};
}
namespace SP {
class cIdVector {
  public:
    int* mpBegin;                                            // +0x00
    int* mpEnd;                                              // +0x04
    int* mpCapacity;                                         // +0x08
};
}
namespace SP {
class cHealTuningRecord {
  public:
    int GetAt(uint32_t nIndex);                              // 0x4d3cd0

    char        pad00[8];
    int         mId;                                         // +0x08
    char        pad0c[0x3c];
    cIdVector   mAnimIds;                                    // +0x48
    char        pad58[0xa8 - 0x58];
    float       mHoldDistance;                               // +0xa8
    char        padac[0xf4 - 0xac];
    float       mRadius;                                     // +0xf4
    char        padf8[0x130 - 0xf8];
    void*       mpProperties;                                // +0x130
};
}
namespace SP {
class cGrowArray {
  public:
    void Copy(const cGrowArray& src);                        // 0xb45c10
    cGrowArray& operator=(const cGrowArray& src);            // 0xc1b790

    void*    mpBegin;                                        // +0x00
    void*    mpEnd;                                          // +0x04
    void*    mpCapacity;                                     // +0x08
    void*    mpAllocator;                                    // +0x0c
    unsigned mCount;                                         // +0x10
};
}
namespace SP {
class cSmallList {
  public:
    cSmallList& operator=(const cSmallList& src);            // 0xdb5b30

    void Init()                                              // empty small list backed by the inline buffer
    {
        void** pInline = mInline;
        void** pCapacity = (void**)((char*)pInline + 8 * sizeof(void*));
        mpBegin = pInline;
        mpEnd = pInline;
        mCount = 0;
        mpCapacity = pCapacity;
    }

    void*    mpBegin;                                        // +0x00
    void*    mpEnd;                                          // +0x04
    void*    mpCapacity;                                     // +0x08
    void*    mpField0c;                                      // +0x0c
    void*    mpField10;                                      // +0x10
    unsigned mCount;                                         // +0x14
    void*    mInline[8];                                     // +0x18
};
}
namespace SP {
class cHealTrack {
  public:
    void Copy(const cHealTrack& src);                        // 0xdb7fc0
    cHealTrack& operator=(const cHealTrack& src);            // 0xdb5e20

    char mBody[0x138];
};
}
namespace SP {
class cActionCircle_s00db_9380 {
  public:
    cActionCircle_s00db_9380() {}
    void Copy(const cActionCircle_s00db_9380& src);                     // 0x00c278e0 (copy construction)
    cActionCircle_s00db_9380& operator=(const cActionCircle_s00db_9380& src);      // 0x00d5d4b0

    int mBody[0x19];
};
}
namespace SP {
class cHealOtherBase {
  public:
    cHealOtherBase() {}
    cHealOtherBase(const cHealOtherBase& src) : mFlags(src.mFlags) {}

    virtual void v00();

    int mFlags;                                              // +0x04
};
}
namespace SP {
union cHealCounter {
    int   mValue;
    float mValueAsFloat;
};
}
namespace SP {
class cHealOtherData : public cHealOtherBase {
  public:
    __declspec(nothrow) cHealOtherData(const cHealOtherData& src);
    cHealOtherData& operator=(const cHealOtherData& src);

    cGrowArray    mEntries;                                  // +0x008
    cSmallList    mTargets;                                  // +0x01c
    cHealTrack    mTrack;                                    // +0x054
    cRefCounted*  mpSubject;                                 // +0x18c
    cRefCounted*  mpObject;                                  // +0x190
    // copied as plain integers by the assignment but as floats by the copy constructor
    cHealCounter   mCounters[6];                             // +0x194
    float          mRadii[8];                                // +0x1ac
    int           mAnimIndex;                                // +0x1cc
    bool          mbFlag1d0;                                 // +0x1d0
    bool          mbFlag1d1;                                 // +0x1d1
    cActionCircle_s00db_9380 mCircle;                                   // +0x1d4
    int           mRandSeed;                                 // +0x238
    bool          mbFlag23c;                                 // +0x23c
    int           mTuningIndex;                              // +0x240
    bool          mbFlag244;                                 // +0x244
    int           mSubAnim;                                  // +0x248
};
}
namespace SP {
struct cHealOtherEntry {
    int            mFlags;
    cHealOtherData mData;
};
}
namespace SP {
struct cMathRandom {                                          // 0x01601760
    unsigned RandomUint32Uniform(unsigned nRange);            // 0xa68fb0
};
}
namespace SP {
extern cMathRandom gMathRandom;
}
namespace SP {
extern void*  gpTribeProperties;                              // 0x01581288
}
namespace SP {
class cPlanetModel_s00db_9380 {
  public:
    const Vec3_s00db_9380* DirectionToSurfacePosition(Vec3_s00db_9380* pOut, const Vec3_s00db_9380* pIn, float fA, float fB); // 0xb815a0
};
}
namespace SP {
cPlanetModel_s00db_9380* PlanetModel_s00db_9380();                                  // 0xb3d350
}
namespace SP {
class cSpeciesCounterMap {
  public:
    int* Find(const int& nKey);                               // 0x564a10
};
}
namespace SP {
class cTribeModeStrategy_s00db_9380 {
  public:
    char               pad00[0x7c];
    cSpeciesCounterMap mCounters;                             // +0x7c
    char               pad80[0x94 - 0x80];
    cAutoRefVector     mHealTargets;                          // +0x94
    char               pad98[0x1a0 - 0xa0];
    float              mHealAmount;                           // +0x1a0
};
}
namespace SP {
cTribeModeStrategy_s00db_9380* cTribeModeStrategy_Instance();            // 0xcd40b0
}
namespace SP {
float GetPropertyT(void* pProperties, unsigned nPropertyId, float fDefault);   // 0x4e1c70
}
namespace SP {
Vec2  GetPropertyAsVector2(void* pProperties, unsigned nPropertyId, Vec2 vDefault); // 0x6a10c0
}
namespace SP {
int   GetCurrentGameMode();                                   // 0xb5b800
}
namespace SP {
void* AchievementsController();                               // 0x675250
}
namespace SP {
bool  HasAchievement(void* pController, unsigned nAchievement); // 0x675e80
}
namespace SP {
unsigned GetAchievementTarget(unsigned nAchievement);         // 0x6766e0
}
namespace SP {
void  AwardAchievement(void* pController, unsigned nAchievement); // 0x676710
}
namespace SP {
void* ResolveNoun(int nHandle);                               // 0xd99470
}
namespace SP {
float GetSeparation(Loco_s00db_9380* pA, Loco_s00db_9380* pB, int nFlags);          // 0xd99ac0
}
namespace SP {
const Vec3_s00db_9380* NormalizeSafe(Vec3_s00db_9380* pOut, const Vec3_s00db_9380* pIn);       // 0x449c20
}
namespace SP {
int   CreatureStateCode(void* pCreature);                     // 0xc0ee60
}
namespace SP {
bool  FUN_00da6270(cSPCreatureCitizen_s00db_9380* c, int nArg);          // 0xda6270
}
namespace SP {
void  FUN_00db2c00(cHealActionState* pState);                 // 0xdb2c00
}
namespace SP {
void  FUN_00dae730(cHealActionState* pState);                 // 0xdae730
}
namespace SP {
void  FUN_00db9f60(cHealActionState* pState, const Vec3_s00db_9380* pPos); // 0xdb9f60
}
namespace SP {
extern const float gHealTimeLimit;                            // 0x147c218 (FLT_MAX)
}
namespace SP {
extern const float kHalfDegree;                               // 0x145cff0 (0.008726646)
}
// ---- items of slice s00db9380 end

// ---- items of slice s00e11ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
    float GetWidth() const { return x2 - x1; }
    float GetHeight() const { return y2 - y1; }
};
}
class IWindow;
class IWinProc {
public:
    virtual int AddRef();
    virtual int Release();
};
class Object {
public:
    virtual int AddRef();                        // 0x00
    virtual int Release();                       // 0x04
    virtual void v08();                          // 0x08
    virtual void* Cast(uint32 typeID) const;     // 0x0c
};
class IWindow : public Object {
public:
    virtual IWindow* GetParent() const;                        // 0x10
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual const Math::Rectangle& GetRealArea() const;        // 0x38
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void SetControlID(uint32 controlID);               // 0x50
    virtual void v54();
    virtual void v58();
    virtual void SetShadeColor(uint32 color);                  // 0x5c
    virtual void SetArea(const Math::Rectangle& area);         // 0x60
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void SetFlag(uint32 flag, bool value);             // 0x7c
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual int Invalidate();                                  // 0x90
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
    virtual void AddWindow(IWindow* pWindow);                  // 0xd8
    virtual void vdc();
    virtual void DisposeWindowFamily(IWindow* pChild);         // 0xe0
    virtual void ve4();
    virtual void BringToFront(IWindow* pWindow);               // 0xe8
    virtual void vec();
    virtual IWindow* FindWindowByID(uint32 controlID, bool bRecursive);  // 0xf0
    virtual void vf4();
    virtual void vf8();
    virtual void vfc();
    virtual void v100();
    virtual void AddWinProc(IWinProc* pWinProc);               // 0x104
};
class Image {
public:
    virtual int AddRef();
    virtual int Release();
};
class UILayout;
template <class T> class AutoRefCount_s00e1_1ab0 {
public:
    T* mpObject;
    AutoRefCount_s00e1_1ab0() : mpObject(0) {}
    ~AutoRefCount_s00e1_1ab0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s00e1_1ab0& operator=(T* p);                   // out of line (0x00b5f950)
    T* get() const { return mpObject; }
};
template <class T> inline T* object_cast(Object* p, uint32 typeID) {
    return p ? (T*)p->Cast(typeID) : 0;
}
namespace SPUIHelpers {
Image* GetImageFromLayout(UILayout* pLayout, uint32 controlID);
}
namespace SPUIHelpers {
void SetDrawableImage(IWindow* pWindow, Image* pImage, int index);
}
namespace SPUIHelpers {
void AnchorWindowToWindow(IWindow* pAnchor, IWindow* pWindow, uint32 flags, int offset);
}
namespace SPUIHelpers {
float GetElapsedSeconds();
}
class ICoreAllocator;
ICoreAllocator* GetUIAllocator();                                  // 0x009512c0
void* operator new(size_t size, size_t align, const char* pName, ICoreAllocator* pAlloc);  // 0x009512d0
class WinPrimary {
public:
    virtual void p00();
};
class cSPUIImageWin : public WinPrimary, public IWindow {
public:
    cSPUIImageWin();                                               // 0x007f3160
    uint32 pad[(0x20c - 8) / 4];
};
class cSPUIAnimatedIconWin;
class IAnimatedIcon {
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
    virtual void SetPeriod(int msec);                          // 0x8c
    void SetImage(Image* pImage, int columns, int rows, int frames);   // 0x007f59e0
};
class cSPUIAnimatedIconWin : public WinPrimary, public IWindow {
public:
    cSPUIAnimatedIconWin();                                        // 0x007f5c20
    uint32 pad[(0x2c8 - 8) / 4];
};
class IBehaviorAction {
public:
    virtual void a00();
};
class IBehaviorEventBase {
public:
virtual void e00();
virtual void e04();
virtual void e08();
virtual void e0c();
virtual void e10();
virtual void e14();
virtual void e18();
virtual void e1c();
virtual void e20();
virtual void e24();
virtual void e28();
virtual void e2c();
    virtual void AddAction(IBehaviorAction* pAction);          // 0x30
};
class cSPUIBehaviorWinBoolStateEvent : public Object {
public:
    cSPUIBehaviorWinBoolStateEvent(int state, uint32 eventID, uint32 controlID, int flags);  // 0x007ff470
    uint32 pad04[(0x18 - 4) / 4];
    IBehaviorEventBase mEvents;                                    // +0x18
    uint32 pad1c[(0x90 - 0x1c) / 4];
};
class cSPUIBehaviorWinInterpolatorScale {
public:
    cSPUIBehaviorWinInterpolatorScale();                           // 0x007ff620
virtual void i00();
virtual void i04();
virtual void i08();
virtual void i0c();
virtual void i10();
virtual void i14();
virtual void i18();
virtual void i1c();
virtual void i20();
virtual void i24();
virtual void i28();
virtual void i2c();
    virtual void SetRange(float from, float to);              // 0x30
    uint32 pad[(0x24 - 4) / 4];
};
class cSPUIBehaviorTimeFunctionDampedPeriodic {
public:
    cSPUIBehaviorTimeFunctionDampedPeriodic(int mode);             // 0x007fd610
    void SetParameters(float period, float phase, float offset, float amplitude,
                       float damping, int repeat);                 // 0x007fd650
    uint32 pad[0x50 / 4];
};
class cSPUIBehaviorActionWinInterpolator : public IBehaviorAction {
public:
    cSPUIBehaviorActionWinInterpolator();                          // 0x007fdab0
    void SetTimeFunction(cSPUIBehaviorTimeFunctionDampedPeriodic* pFunc);   // 0x007fdb60
    void SetInterpolator(cSPUIBehaviorWinInterpolatorScale* pInterp);       // 0x007fdb90
    uint32 pad[(0x60 - 4) / 4];
};
class cGameModeManager {
public:
    uint32 GetActiveModeID();                                      // 0x00a42730
};
cGameModeManager* GameModeManager();                               // 0x00b3d320
namespace SP {
uint32 GetCurrentGameMode_s00e1_1ab0();                                       // 0x00b5b800
}
namespace SP {
class cCivilization_s00e1_1ab0;
}
namespace SP {
class cGameNounManager_s00e1_1ab0 {
public:
    cCivilization_s00e1_1ab0* GetPlayerCivilization();                        // 0x00b25fb0
    uint32 GetPlayerEmpireOrMinus1();                              // 0x00b1f9d0
};
}
namespace SP {
cGameNounManager_s00e1_1ab0* NounManager_s00e1_1ab0();                                   // 0x00b3d300
}
static const uint32 kModeEditor = 0x1654c05;
static const uint32 kModeCiv    = 0x1654c04;
class IVisibility {
public:
virtual void q00();
virtual void q04();
virtual void q08();
virtual void q0c();
virtual void q10();
virtual void q14();
virtual void q18();
virtual void q1c();
virtual void q20();
virtual void q24();
virtual void q28();
virtual void q2c();
virtual void q30();
virtual void q34();
virtual void q38();
virtual void q3c();
virtual void q40();
virtual void q44();
virtual void q48();
virtual void q4c();
virtual void q50();
virtual void q54();
    virtual bool IsVisible();                                  // 0x58
};
struct cMapObject {                    // a city / vehicle that owns a minimap icon
    uint32 pad[0x34 / 4];
    IVisibility mVisibility;           // +0x34
};
struct cPlacedObject {                 // result of the 0x00ac86d0 lookup
    uint32 pad[0x120 / 4];
    IVisibility mVisibility;           // +0x120
};
void* LookupMinimapObjectA(uint32 key);                            // 0x00ac8730 (cdecl)
cPlacedObject* LookupMinimapObjectB(uint32 key);                   // 0x00ac86d0 (cdecl)
struct KeyVector { uint32* mpBegin; uint32* mpEnd; };
struct cKeyListOwner {
    KeyVector& GetKeys();                                          // 0x00bef6c0
};
struct FeedbackFlags { uint32 m0; bool mbSeen; };
struct FeedbackFlagsMap {
    FeedbackFlags& operator[](const uint32& key);                  // 0x00e11910
};
extern FeedbackFlagsMap gMinimapFeedbackFlags;
struct cIconInfo;
struct MinimapMsg {
    void* vtable;
    int mRefCount;
    uint32 mKey;          // +0x08 object / control id
    uint32 m0c;
    uint32 mValue;        // +0x10 color / id
    uint32 m14;
    uint32 mType;         // +0x18 (also a cIconInfo* for 0x1c8c174)
    uint32 m1c;
    uint32 mEmpireID;     // +0x20
};
class RefObject {
public:
    virtual int AddRef();
    virtual int Release();
};
struct cIconInfo {                     // size 0x24
    uint32 mType;                      // +0x00
    float mX, mY, mZ;                  // +0x04
    uint32 mFlags;                     // +0x10
    AutoRefCount_s00e1_1ab0<RefObject> mpObject;  // +0x14
    float mTimeout;                    // +0x18
    uint32 mAnimState;                 // +0x1c
    uint32 m20;                        // +0x20
    cIconInfo(const cIconInfo& other);                             // 0x00e0bd70
};
struct IconMapNode {
    IconMapNode* mpNodeRight;
    IconMapNode* mpNodeLeft;
    IconMapNode* mpNodeParent;
    char mColor;
    uint32 mKey;                       // +0x10
    cIconInfo mValue;                  // +0x14
};
IconMapNode* RBTreeIncrement(const IconMapNode* pNode);            // 0x00921580 (cdecl)
struct IconMapIterator {
    IconMapNode* mpNode;
    IconMapIterator() : mpNode(0) {}
    IconMapIterator(IconMapNode* p) : mpNode(p) {}
    IconMapIterator(const IconMapIterator& x) : mpNode(x.mpNode) {}
    cIconInfo* operator->() const { return &mpNode->mValue; }
    IconMapIterator& operator++() { mpNode = RBTreeIncrement(mpNode); return *this; }
    bool operator==(const IconMapIterator& x) const { return mpNode == x.mpNode; }
    bool operator!=(const IconMapIterator& x) const { return mpNode != x.mpNode; }
};
struct IconMap {                       // eastl::map<uint32, cIconInfo>
    uint32 mCompare;                   // +0x00
    IconMapNode* mAnchorRight;         // +0x04 anchor
    IconMapNode* mAnchorLeft;          // +0x08
    IconMapNode* mAnchorParent;        // +0x0c
    char mAnchorColor;                 // +0x10
    uint32 mnSize;
    uint32 mAllocator;
    IconMapIterator find(const uint32& key);                       // 0x00e5c780
    IconMapIterator begin() { return IconMapIterator(mAnchorLeft); }
    IconMapIterator end() { return IconMapIterator((IconMapNode*)&mAnchorRight); }
};
class IHandlerRC {
public:
    virtual int AddRef();
    virtual int Release();
    virtual bool HandleMessage(uint32 messageID, void* pMessage);
};
class MinimapWinPrimary {
public:
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
virtual void w28();
virtual void w2c();
virtual void w30();
virtual void w34();
virtual void w38();
virtual void w3c();
virtual void w40();
virtual void w44();
virtual void w48();
virtual void w4c();
virtual void w50();
virtual void w54();
virtual void w58();
virtual void w5c();
virtual void w60();
virtual void w64();
virtual void w68();
virtual void w6c();
virtual void w70();
virtual void w74();
virtual void w78();
virtual void w7c();
virtual void w80();
virtual void w84();
virtual void w88();
    virtual void RebuildLayout();                              // 0x8c
};
class MinimapWindowPart : public IWindow {
public:
    uint32 padWindow[(0x214 - 8) / 4];
};
class cSPUIMinimapWin : public MinimapWinPrimary, public MinimapWindowPart, public IHandlerRC {
public:
    bool HandleMessage(uint32 messageID, void* pMessage);

    void RemoveIcon(uint32 id, bool bRemoveWindow, int flags);     // 0x00e0f9c0
    void AddIcon(uint32 id, const cIconInfo& info, int a, int b);  // 0x00e10580
    void SetIconColor(uint32 id, uint32 color);                    // 0x00e0c490
    void UpdateMapTexture();                                       // 0x00e0e1a0

    void ShowAttackIcon(IWindow* pWin, IconMapIterator it, uint32 id, uint32 color,
                        uint32 imageID, float decay, float duration);
    void ShowCommIcon(IWindow* pWin, IconMapIterator it, uint32 id, uint32 color,
                      uint32 imageID, float width, float height, int rows, int frames);

    uint32 padHandler[(0x24 - 4) / 4];
    bool mbPaused;                                 // +0x238 (handler +0x24)
    uint32 pad239[(0x38 - 0x28) / 4];
    AutoRefCount_s00e1_1ab0<RefObject> mpPendingTexture;      // +0x24c (handler +0x38)
    uint32 pad250[(0x44 - 0x3c) / 4];
    UILayout* mpLayout;                            // +0x258 (handler +0x44)
    uint32 pad25c[(0x108 - 0x48) / 4];
    IconMap mIconInfos;                            // +0x31c (handler +0x108)
    uint32 pad338[(0x148 - 0x124) / 4];
    uint32 mPendingFlags;                          // +0x35c (handler +0x148)
};
static inline void ReleaseRef(AutoRefCount_s00e1_1ab0<RefObject>& p) {
    RefObject* old = p.mpObject;
    if (old) {
        p.mpObject = 0;
        old->Release();
    }
}
__forceinline void cSPUIMinimapWin::ShowAttackIcon(IWindow* pWin, IconMapIterator it, uint32 id,
                                            uint32 color, uint32 imageID, float decay,
                                            float duration) {
    IWindow* pIcon = pWin->GetParent()->FindWindowByID(id, false);
    if (!pIcon) {
        AutoRefCount_s00e1_1ab0<Image> image;
        image = SPUIHelpers::GetImageFromLayout(mpLayout, imageID);

        pIcon = new (4, "UI/CivMinimap/AttackIcon", GetUIAllocator()) cSPUIImageWin();
        SPUIHelpers::SetDrawableImage(pIcon, image.get(), -1);

        float width = pWin->GetRealArea().GetWidth();
        float height = pWin->GetRealArea().GetHeight();
        pIcon->SetControlID(id);
        pIcon->SetArea(Math::Rectangle(0.0f, 0.0f, width, height));
        pIcon->SetFlag(1, true);
        pIcon->SetFlag(0x10, true);
        pWin->GetParent()->AddWindow(pIcon);
        SPUIHelpers::AnchorWindowToWindow(pWin, pIcon, 0x300, 0);
        if (!(it->mFlags & 1)) {
            pIcon->GetParent()->BringToFront(pIcon);
        }
        pIcon->SetShadeColor(color);

        cSPUIBehaviorWinBoolStateEvent* pEvent =
            new (4, "CivMinimap/AttackAnimation", GetUIAllocator())
                cSPUIBehaviorWinBoolStateEvent(1, 0x25a5f84, id, 0);
        pIcon->AddWinProc(object_cast<IWinProc>(pEvent, 0x2f009dd0));
        it->mAnimState = 0;

        cSPUIBehaviorWinInterpolatorScale* pScale =
            new (4, "CivMinimap/AttackAnimation", GetUIAllocator()) cSPUIBehaviorWinInterpolatorScale();
        pScale->SetRange(1.5f, 2.5f);

        cSPUIBehaviorTimeFunctionDampedPeriodic* pTime =
            new (4, "CivMinimap/AttackAnimation", GetUIAllocator()) cSPUIBehaviorTimeFunctionDampedPeriodic(1);
        pTime->SetParameters(100.0f, 0.0f, 0.0f, 2.0f, 0.0f, -1);
        pTime->SetParameters(decay, 0.0f, 0.0f, 2.0f, 1e-5f, -1);

        cSPUIBehaviorActionWinInterpolator* pAction =
            new (8, "CivMinimap/AttackAnimation", GetUIAllocator()) cSPUIBehaviorActionWinInterpolator();
        pAction->SetInterpolator(pScale);
        pAction->SetTimeFunction(pTime);
        pEvent->mEvents.AddAction(pAction);
    }
    it->mTimeout = SPUIHelpers::GetElapsedSeconds() + duration;
    pIcon->Invalidate();
}
__forceinline void cSPUIMinimapWin::ShowCommIcon(IWindow* pWin, IconMapIterator it, uint32 id,
                                          uint32 color, uint32 imageID, float width,
                                          float height, int rows, int frames) {
    IWindow* pIcon = pWin->GetParent()->FindWindowByID(id, false);
    if (!pIcon) {
        AutoRefCount_s00e1_1ab0<Image> image;
        image = SPUIHelpers::GetImageFromLayout(mpLayout, imageID);

        pIcon = new (8, "UI/CivMinimap/CommIcon", GetUIAllocator()) cSPUIAnimatedIconWin();
        pIcon->SetControlID(id);
        pIcon->SetArea(Math::Rectangle(0.0f, 0.0f, width, height));
        pIcon->SetFlag(1, true);
        pIcon->SetFlag(0x10, true);
        pWin->GetParent()->AddWindow(pIcon);
        SPUIHelpers::AnchorWindowToWindow(pWin, pIcon, 0x300, 0);
        if (!(it->mFlags & 1)) {
            pIcon->GetParent()->BringToFront(pIcon);
        }
        pIcon->SetShadeColor(color);

        IAnimatedIcon* pAnim = (IAnimatedIcon*)pIcon->Cast(0x106f146);
        pAnim->SetImage(image.get(), 4, rows, frames);
        pAnim->SetPeriod(500);
    }
    pIcon->Invalidate();
}
// ---- items of slice s00e11ab0 end

// @ 0x00d9e460
char cGroupMovement::PickLeader(cSimCreature* pCreature, void* pA, void* pB, void* pC, void* pD, cLeaderChoice* pChoice)
{
    if (pChoice != nullptr)
        pChoice->mpLeader = nullptr;
    pChoice->mbChanged = 0;

    if (!pCreature->mMovement.CallChar(0x58)) {
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x6578211, -1, 0);
        return 1;
    }

    if (pCreature->IsGroupLeader()) {
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x6578207, -1, 0);
        void* pStimuli = pCreature->mpBehaviorTree->mStimuli.Play(0x800000, 0);
        void* pLeader = nullptr;
        if (pStimuli != nullptr)
            pLeader = ((cDispatchObject*)pStimuli)->Call(0x0c);
        void* pPrevious = pChoice->mpLeader;
        if (pLeader != pPrevious) {
            if (pLeader != nullptr)
                ((cPoolObject*)pLeader)->AddRef();
            pChoice->mpLeader = pLeader;
            if (pPrevious != nullptr)
                ((cPoolObject*)pPrevious)->Destroy(0);
        }
        return 1;
    }

    switch (pCreature->GetBehaviorPhase()) {
    case 4:
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x657820b, -1, 0);
        return 1;
    case 5:
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x657820e, -1, 0);
        return 1;
    case 6:
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x6578208, -1, 0);
        return 1;
    default:
        break;
    }
    pChoice->mnAnimId = pCreature->InterruptAnimation(0x6578211, -1, 0);
    return 1;
}

// @ 0x00da6920
float __cdecl FUN_00da6920(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags)
{
    if ((flags & 2) != 0) {
        c->GetTribe();
        AnimPlayRes* p = c->mpBTree->mStimuli.Play(0, 0x24000);
        if (p != 0) {
            cSPCreatureCitizen* q = (cSPCreatureCitizen*)FUN_00d998d0(p, 0xce9f6639);
            if (q != 0 && q->mFlag135 != 0) {
                AnimPlayRes* r = q->mpBTree->mStimuli.Play(0x200000, 0);
                if (r != 0) {
                    if (FUN_00d998d0(r, 0xee02c7) != 0)
                        return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00da69e0
float __cdecl FUN_00da69e0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags)
{
    if ((flags & 2) != 0) {
        c->GetTribe();
        AnimPlayRes* p = c->mpBTree->mStimuli.Play(0, 0x20000);
        if (p != 0) {
            cSPCreatureCitizen* q = (cSPCreatureCitizen*)FUN_00d998d0(p, 0xce9f6639);
            if (q != 0 && q->mFlag135 != 0) {
                if (q->v20() == 0x18eb45e)
                    return 1.0f;
                AnimPlayRes* r = q->mpBTree->mStimuli.Play(0x200000, 0);
                if (r != 0)
                    return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00da6aa0
float __cdecl FUN_00da6aa0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    c->GetTribe();
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0, 0x20000);
    if (play != 0) {
        cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(play);
        if (s != 0 && s->mbDead == 0) {
            if (stim != 0)
                stim->GetAny();
            stim->mTarget = &s->mCombat;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00da6b10
u8 __cdecl FUN_00da6b10(cSPCreatureCitizen* a, cSPCreatureCitizen* b)
{
    bool set = false;
    int id1 = a->v4c();
    int id2 = b->v4c();
    if (id1 == id2)
        return set;
    if (b->mpOrders->FindSlot(0, 2, 0, 0) != -1 ||
        b->mpOrders->FindSlot(1, 2, 0, 0) != -1 ||
        b->mpBTree->mKey1d8 == 0xd59a3b60)
        set = true;
    u32 v = ((RelMgr*)FUN_00b3d2c0(id1, id2, 1))->FUN_d00a70();
    if (set || v > 1)
        return 0;
    return 1;
}

// @ 0x00da6bb0
float __cdecl FUN_00da6bb0(cSPCreatureCitizen* c)
{
    cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(c->mpBTree->mStimuli.Play(0, 0x4000));
    if (s != 0) {
        if (s->v2c() == 0 && s->mFlag135 != 0 && s->mbDead == 0) {
            if (c->Proximity(s, 1.0f, 0.0f) != 0 || c->vc0(s, 1.0f, 0.0f) != 0) {
                void* r = FUN_00ac80d0(s, 0x18eb45e);
                if (r != 0) {
                    c->mpBTree->mStimuli.PlayWith(0x8000, 0, g_f147c218, r);
                    return 0.0f;
                }
                void* r2 = FUN_00ac80d0(s, 0x18eb4b7);
                if (r2 != 0)
                    c->mpBTree->mStimuli.PlayWith(0x400, 0, g_f147c218, r2);
            }
        }
    }
    return 0.0f;
}

// @ 0x00da6cb0
float __cdecl FUN_00da6cb0(cSPCreatureCitizen* c)
{
    if (c->FUN_c0b9c0() < g_f147c21c)
        return 0.0f;
    return c->mCombat.GetHealthPct() * g_f13ec4d0 < g_f1687a14 ? 1.0f : 0.0f;
}

// @ 0x00da6d10
float __cdecl FUN_00da6d10(cSPCreatureCitizen* c)
{
    if (c->FUN_c0b9c0() < g_f147c21c)
        return 0.0f;
    return c->mCombat.GetHealthPct() * g_f13ec4d0 < g_f1687a10 ? 1.0f : 0.0f;
}

// @ 0x00da6d70
float __cdecl FUN_00da6d70(cSPCreatureCitizen* c)
{
    if (c->GetTribe()->mTimer20c.GetTimer() > 0.0f ||
        c->mTimer34.GetTimer() > 0.0f) {
        if (c->FUN_c0b9c0() < g_f1687a14 && c->mpBTree->mKey1d8 != 0x461300f)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00da6de0
float __cdecl FUN_00da6de0(cSPCreatureCitizen* c)
{
    if (c->GetTribe()->mTimer20c.GetTimer() > 0.0f ||
        c->mTimer34.GetTimer() > 0.0f) {
        if (c->FUN_c0b9c0() < g_f1687a10 && c->mpBTree->mKey1d8 != 0x461300f)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00da6e50
float __cdecl FUN_00da6e50(cSPCreatureCitizen* c)
{
    float r;
    if (c->GetTribe()->mTimer20c.GetTimer() == 0.0f &&
        c->mTimer34.GetTimer() == 0.0f &&
        c->FUN_c0b9c0() < g_f1687a0c)
        r = 1.0f;
    else
        r = 0.0f;
    return r;
}

// @ 0x00da6ed0
float __cdecl FUN_00da6ed0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    float v = 0.0f;
    if ((flags & 1) == 0) {
        if (c->GetTribe()->mTimer20c.GetTimer() > 0.0f ||
            c->mTimer34.GetTimer() > 0.0f) {
            LayoutMgr* mgr = (LayoutMgr*)FUN_00af13b0(c, 1, &v);
            if (mgr->LookupB() != 0) {
                c->GetTribe();
                if (stim != 0)
                    stim->GetAny();
                stim->mF18 = 1;
                *out = 1;
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00da6f60
float __cdecl FUN_00da6f60(cSPCreatureCitizen* c)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0x40, 0);
    ResAnim* r = (ResAnim*)FUN_00d998d0(play, 0x116d858);
    float res;
    if (r->v58() == 1 || r->v58() == 2 || r->v58() == 3)
        res = 1.0f;
    else
        res = 0.0f;
    return res;
}

// @ 0x00da6fe0
float __cdecl FUN_00da6fe0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0, 0x80);
    cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(play);
    if (s != 0 && s->mbDead == 0) {
        if (c->mCombat.GetHealthPct() * g_f13ec4d0 < g_f1687a10) {
            if (stim != 0)
                stim->GetAny();
            stim->mTarget = &s->mCombat;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00da7060
float __cdecl FUN_00da7060(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0, 0x80);
    cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(play);
    if (s != 0 && s->mbDead == 0) {
        if (stim != 0)
            stim->GetAny();
        stim->mTarget = &s->mCombat;
        *out = 1;
        return 1.0f;
    }
    return 0.0f;
}

// @ 0x00da70c0
float __cdecl FUN_00da70c0(void* a)
{
    FUN_00b3d480()->v50(a);
    return 0.0f;
}

// @ 0x00da70e0
float __cdecl FUN_00da70e0(cSPCreatureCitizen* c)
{
    c->mpBTree->mStimuli.ClearAll(0, 0x800000);
    int v = c->FUN_c22dc0();
    if (v == 0 || v == 0xb)
        return 0.0f;
    cTool* tool = c->GetTribe()->GetToolOfType(v);
    if (tool != 0 && tool->mCombat.GetDamageState() != 2)
        return 0.0f;
    return 1.0f;
}

// @ 0x00da7140
u8 __cdecl FUN_00da7140(cSPCreatureCitizen* a, cSPCreatureCitizen* b)
{
    if (a->FUN_bc9b50() == 0) {
        cSPCreatureCitizen* x = a->FUN_bc9b10();
        if (x->GetTribe() == b->GetTribe())
            return 1;
    }
    return 0;
}

// @ 0x00da7180
float __cdecl FUN_00da7180(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    if ((flags & 1) == 0) {
        cTribe* t = c->GetTribe();
        if (t != 0) {
            cTool* tool = t->vac();
            if (tool != 0) {
                if (tool->mCombat.GetDamageState() != 2 &&
                    tool->mCombat.GetHealthPct() < 1.0f) {
                    if (stim != 0)
                        stim->GetAny();
                    stim->mValue = tool;
                    *out = 1;
                    return 1.0f;
                }
            }
            for (u32 i = 0; i < 0x28; i += 4) {
                cTool* tl = t->GetToolOfType(g_a147c220[i >> 2]);
                if (tl != 0) {
                    if (tl->mCombat.GetDamageState() != 2 &&
                        tl->mCombat.GetHealthPct() < 1.0f) {
                        if (stim != 0)
                            stim->GetAny();
                        stim->mValue = tl;
                        *out = 1;
                        return 1.0f;
                    }
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00da7270
u8 __cdecl FUN_00da7270(cSPCreatureCitizen* c)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(1, 0);
    if (play == 0 || play->mAnimId == 1)
        c->mSub58.v34();
    c->mpBTree->mStimuli.ClearAll(1, 0);
    return 0;
}

// @ 0x00da72c0
u8 __cdecl FUN_00da72c0(cSPCreatureCitizen* c)
{
    c->mpBTree->mStimuli.ClearAll(0x4000, 0);
    return 0;
}

// @ 0x00da72e0
unsigned __cdecl FUN_00da72e0(cSPCreatureCitizen* c)
{
    return c->mSub58.v20() != 0;
}

// @ 0x00da7300
u8 __cdecl FUN_00da7300(cSPCreatureCitizen* c)
{
    return c->mSub58.v20() != 0;
}

// @ 0x00da7320
void __cdecl FUN_00da7320(cSPCreatureCitizen* c)
{
    c->mSub58.v34();
}

// @ 0x00da7330
void __cdecl FUN_00da7330(cSPCreatureCitizen* c)
{
    c->FUN_c14750(0);
}

// @ 0x00da73e0
u32 __cdecl FUN_00da73e0(cSPCreatureCitizen* c)
{
    u32 r;
    if (c->mSubC0.IsNearGoal() != 0 || (c->mFlag330 & 1) != 0)
        r = 0;
    else
        r = 1;
    return r;
}

// @ 0x00da7410
void __cdecl FUN_00da7410(cSPCreatureCitizen* c)
{
    c->mpBTree->mStimuli.PlayWith(0, 0x8000, g_f1473c70, 0);
    c->FUN_c14750(0);
}

// @ 0x00da7450
u8 __cdecl FUN_00da7450(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, float* out)
{
    *out = g_f13eecd8;
    return 1;
}

// @ 0x00da7470
u8 __cdecl FUN_00da7470(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, void* p5, float* out, float unused7, float delta)
{
    cTribe* t = c->GetTribe();
    if (t != 0 && t->mFlag556 != 0) {
        float n = *out - delta;
        *out = n;
        if (n < 0.0f) {
            c->mCombat.v18(g_f147c218, -1, 2, (void*)&g_f169f408, 0);
            return 0;
        }
    }
    return 1;
}

// @ 0x00da74e0
void __cdecl FUN_00da74e0(cSPCreatureCitizen* c)
{
    char v = c->mSubC0.vf8();
    c->FUN_c14750(v == 0);
    if ((c->mpBTree->mFlags1c8 & 0x2000000) == 0)
        c->mpBTree->mStimuli.ClearAll(0, 0x20);
}

// @ 0x00da7530
u32 __cdecl FUN_00da7530(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, void* p5, float* out, float unused7, float delta)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0, 8);
    if (play != 0) {
        *out = g_f1486110;
        c->InterruptAnimation(play->mAnimId, -1, 0);
        c->PlayAnimation(play->mAnim, 1, -1);
        c->mpBTree->mStimuli.ClearAll(0, 8);
    }
    float n = *out - delta;
    *out = n;
    return n > 0.0f;
}

// @ 0x00da75c0
void __cdecl FUN_00da75c0(cSPCreatureCitizen* c)
{
    if (c->mbDead == 0 && c->mFlag135 != 0)
        c->FUN_c14750(0);
}

// @ 0x00da75e0
u8 __cdecl FUN_00da75e0(cSPCreatureCitizen* a, cSPCreatureCitizen* b)
{
    if (a->FUN_bc9b50() == 0) {
        cSPCreatureCitizen* x = a->FUN_bc9b10();
        if (b != 0 && x != 0) {
            cTribe* tb = b->GetTribe();
            cTribe* tx = x->GetTribe();
            int cb = b->FUN_c0ee60();
            int cx = x->FUN_c0ee60();
            if (tx == tb && cb == cx)
                return 1;
        }
    }
    return 0;
}

// @ 0x00da7640
u8 __cdecl FUN_00da7640(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, void* p5, u32* out)
{
    c->mpBTree->PopFront();
    c->mpBTree->mStimuli.ClearAll(0x1d3fbffa, 0x81240a0);
    c->ForceOrdersUpdate();
    *out = c->InterruptAnimation(0x575f108, -1, 0);
    c->FUN_c279a0(0);
    c->SetCurrentToolEffect(0, -1);
    return 1;
}

// @ 0x00da76a0
u8 __cdecl FUN_00da76a0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, void* p5, u32* out)
{
    if (*out != 0) {
        if (c->AnimationFinished(*out) == 0)
            return 1;
    }
    return 0;
}

// @ 0x00da76c0
float __cdecl FUN_00da76c0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    cTribe* t = c->GetTribe();
    if (t != 0) {
        void* p = t->mTimer20c.GetPtr340();
        if (p != 0) {
            if (stim != 0)
                stim->GetAny();
            stim->mValue = p;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00da7710
u8 __cdecl FUN_00da7710(cSPCreatureCitizen* c)
{
    c->mFlagsB58 |= 0x8000;
    return 1;
}

// @ 0x00da7730
void __cdecl FUN_00da7730(cSPCreatureCitizen* c)
{
    c->mFlagsB58 &= 0xffff7fff;
    c->mpBTree->mStimuli.ClearAll(0, 2);
}

// @ 0x00da7760
float __cdecl FUN_00da7760(cSPCreatureCitizen* c)
{
    CeeObj* p = (CeeObj*)c->mTimer34.GetPtr330();
    if (p != 0 && p->mState12c != 1)
        return 1.0f;
    return 0.0f;
}

// @ 0x00da7780
f32 FUN_00da7780(Creature* p)
{
    Ret7780* q = p->mLoco.FUN_00cee330();
    if (q == 0)
        return 0.0f;
    i32 v = q->mField12c;
    if (v == 3 || v == 0)
        return 0.0f;
    return 1.0f;
}

// @ 0x00da77b0
f32 FUN_00da77b0(Creature* p)
{
    Ret7780* q = p->mLoco.FUN_00cee330();
    if (q != 0 && q->mField12c != 2)
        return 1.0f;
    return 0.0f;
}

// @ 0x00da77d0
f32 FUN_00da77d0(Creature* p)
{
    OrderRec* q = p->mpAgentOrders->FirstPending();
    if (q != 0 && q->mField00 == 8)
        return 0.0f;
    return 1.0f;
}

// @ 0x00da77f0
bool FUN_00da77f0(Creature* p, i32, i32, i32, i32 mode)
{
    Ret7780* q = p->mLoco.FUN_00cee330();
    if (q != 0) {
        if (mode == 0) {
            void* c = FUN_00b3d2b0()->FUN_00ac79d0();
            FUN_00b3d2b0()->FUN_00ac7de0(q, c);
        } else if (mode == 1) {
            p->InterruptAnimation(0x4ffb325, -1, 0);
            return 1;
        }
    }
    return 0;
}

// @ 0x00da7850
void FUN_00da7850(Creature* p, i32, i32, i32, i32 mode)
{
    if (p->mLoco.FUN_00cee330() != 0 && mode == 1) {
        void* c = FUN_00b3d2b0()->FUN_00ac79d0();
        FUN_00b3d2b0()->FUN_00ac7de0(p->mLoco.FUN_00cee330(), c);
    }
}

// @ 0x00da7890
bool FUN_00da7890(Creature* p)
{
    Ret7780* q = p->mLoco.FUN_00cee330();
    if (q != 0) {
        u32 local = 0xffffffffu;
        if (p->WaitForAnimEventOrEnd(0xbfa50b5a, &local, 0x4ffb325, 0, 1) != 0)
            FUN_00b3d2b0()->FUN_00ac7de0(q, FUN_00b3d2b0()->FUN_00ac79d0());
    }
    return p->FUN_00c0e0c0(0x4ffb325);
}

// @ 0x00da7900
bool FUN_00da7900(Creature* p, i32, i32, i32, i32, u32* out)
{
    u32 anim = p->mpAgentOrders->mStimuli.Play(0, 0x4000000);
    if (anim != 0) {
        *out = p->PlayAnimation(0x5f73e48, 1, -1);
        return 1;
    }
    return 0;
}

// @ 0x00da7940
void FUN_00da7940(Creature* p)
{
    p->FUN_00c14750(0);
    p->mpAgentOrders->mStimuli.ClearAll(0, 0x4000000);
}

// @ 0x00da7970
bool FUN_00da7970(Creature* p, i32, i32, i32, i32, Out9* out)
{
    void* sub = (p != 0) ? (void*)&p->mObjC0 : 0;
    FUN_00b3d310(sub)->FUN_00b45410();
    p->V_8c();
    p->mByte12f = 0;
    if (p->GetTribe() != 0)
        p->GetTribe()->FUN_00c950f0(p);
    p->mObjC0.V_ec();
    p->mObjC0.V_54(0);
    p->mObjC0.FUN_00c41d60(&g_169f3b8);
    p->mObjC0.FUN_00c41d90(&g_169f3b8);
    if (p->mObjC0.V_58() != 0) {
        Strategy* st = FUN_00cd40b0();
        if (st != 0 && st->V_6c_a() != 0)
            st->V_6c_b(p)->FUN_00ccbb60();
    }
    out->f0 = (p->mObjC0.V_58() != 0) ? g_14853bc : g_14007f4;
    f32 c = g_13eb95c;
    out->f4 = c;
    out->f8 = c;
    out->fc = g_1485720;
    out->b10 = 0;
    out->b11 = 0;
    if (p->FUN_00c0b760() == 0 && p->mObjC0.V_58() != 0)
        FUN_00b3d3e0(0xee0e963f, 0x182cd6ce, p->mObjC0.V_2c(), 0, 1, 0)->PostFeedbackEvent();
    if (p->GetTribe() != 0)
        p->GetTribe()->V_9c(p, 0);
    return 1;
}

// @ 0x00da9160
void InitNearHutForReaction(int self)
{
    (void)self;
}

// @ 0x00da9220
bool FUN_00da9220(int self, void* stimuli, char* out, int a4, int a5)
{
    PlayObj* po = (PlayObj*)((char*)*(void**)(self + 0xb4c) + 8);
    void* ent = po->Play(a4, a5);
    if (ent) {
        if ((g_flag169f3b4 & 1) == 0) {
            g_flag169f3b4 |= 1;
            g_dist169f3b0 = g_f400;
        }
        Vec3* pos = (Vec3*)(*(void*(**)(int))(*(int*)(self + 0xc0) + 0x2c))(self + 0xc0);
        float dx = pos->x - *(float*)((char*)ent + 0x14);
        float dy = pos->y - *(float*)((char*)ent + 0x18);
        float dz = pos->z - *(float*)((char*)ent + 0x1c);
        float dist = dx * dx + dy * dy + dz * dz;
        if (g_dist169f3b0 > dist) {
            if (stimuli)
                ((Stimuli*)stimuli)->GetAny();
            *out = 1;
            *(int*)((char*)stimuli + 0x18) = *(int*)((char*)ent + 0xc);
            *(int*)((char*)stimuli + 0x1c) = *(int*)((char*)ent + 0x10);
            *(int*)((char*)stimuli + 0xc)  = *(int*)((char*)ent + 0x14);
            *(int*)((char*)stimuli + 0x10) = *(int*)((char*)ent + 0x18);
            *(int*)((char*)stimuli + 0x14) = *(int*)((char*)ent + 0x1c);
            po->ClearAll(a4, a5);
            return 1;
        }
        po->ClearAll(a4, a5);
    }
    return 0;
}

// @ 0x00da9330
float10 f00da9330(int a1, int a2, int a3, int a4, int a5, int a6)
{
    if (FUN_00da9220(a1, (void*)a5, (char*)a6, 0, 1))
        return (float10)1;
    return (float10)0;
}

// @ 0x00da9360
float10 f00da9360(int a1, int a2, int a3, int a4, int a5, int a6)
{
    if (FUN_00da9220(a1, (void*)a5, (char*)a6, 0, 4))
        return (float10)1;
    return (float10)0;
}

// @ 0x00da9390
float10 f00da9390(int self, int a2)
{
    (void)self; (void)a2;
    return (float10)0;
}

// @ 0x00da94c0
void f00da94c0(int self)
{
    (void)self;
}

// @ 0x00da9600
F10 __cdecl FUN_00da9600(void* p)
{
  int* piVar2 = (int*)FUN_00c22f50(p);
  if (piVar2 == 0) return 0.0f;

  int pi48 = piVar2[0x48];
  float* pfVar3 = ((TFV)(*(void***)pi48)[0x2c / 4])((void*)pi48);
  F10 fVar13 = ((TFF)(*(void***)piVar2)[0x60 / 4])((void*)piVar2);
  int iVar4 = ((TFI)(*(void***)piVar2)[0x4c / 4])((void*)piVar2);

  int* piTmp = (int*)FUN_00c420d0();
  int* piEnd = (int*)piTmp[1];
  int* piCur = (int*)*piTmp;
  if (piCur != piEnd) {
    do {
      void* uVar6;
      if ((void*)*piCur == 0) {
        uVar6 = 0;
      } else {
        void* obj = (void*)*piCur;
        uVar6 = (void*)((TFVU)(*(void***)obj)[0xb8 / 4])(obj, 0xce9f6639);
      }
      int* piVar7 = (int*)FUN_00d99470(uVar6);
      if (piVar7 != 0) {
        int iVar8 = ((TFI)(*(void***)piVar7)[0x4c / 4])((void*)piVar7);
        if (iVar8 != iVar4) {
          char cVar1 = (char)FUN_00c0d560(piVar7, 1.0f, 0.0f);
          if (cVar1 == 0) {
            cVar1 = ((TFCFF)(*(void***)p)[0xc0 / 4])(p, 1.0f, 0.0f);
            if (cVar1 == 0) goto LAB_00da97b3;
          }
          void* puVar9 = ((TFV)(*(void***)piVar7)[0x20 / 4])((void*)piVar7);
          float fVar14;
          if (puVar9 == (void*)0x018eb45e) {
            int pi30 = piVar7[0x30];
            float* pfVar10 = ((TFV)(*(void***)pi30)[0x2c / 4])((void*)pi30);
            fVar14 = ((pfVar10[1] - pfVar3[1]) * (pfVar10[1] - pfVar3[1]) +
                      (*pfVar10 - *pfVar3) * (*pfVar10 - *pfVar3)) +
                     (pfVar10[2] - pfVar3[2]) * (pfVar10[2] - pfVar3[2]);
          } else {
            void* puVar11 = ((TFV)(*(void***)piVar7)[0x20 / 4])((void*)piVar7);
            if (puVar11 != (void*)0x018eb4b7) goto LAB_00da97b3;
            char cVar2 = (char)FUN_00da6b10(p, piVar7);
            if (cVar2 == 0) goto LAB_00da97b3;
            int pi30 = piVar7[0x30];
            float* pfVar10 = ((TFV)(*(void***)pi30)[0x2c / 4])((void*)pi30);
            fVar14 = ((pfVar10[2] - pfVar3[2]) * (pfVar10[2] - pfVar3[2]) +
                      (pfVar10[1] - pfVar3[1]) * (pfVar10[1] - pfVar3[1])) +
                     (*pfVar10 - *pfVar3) * (*pfVar10 - *pfVar3);
          }
          // LAB_00da97a8:
          if (fVar14 < fVar13 * fVar13) {
            void* pcVar12 = FUN_00c22f50(p);
            FUN_00c8f470(pcVar12, 0, 0x4000, 0x40a00000, piVar7);
            break;
          }
        }
      }
    LAB_00da97b3:
      piCur = piCur + 1;
      if (piCur == piEnd) return 0.0f;
    } while (1);
  }
  return 0.0f;
}

// @ 0x00da9800
F10 __cdecl FUN_00da9800(void* p)
{
  F10 fVar11 = (F10)FUN_00c0b9c0(p);
  if (fVar11 < (F10)1.5258789e-05f) return 0.0f;
  fVar11 = (F10)FUN_00bfc490((char*)p + 0x5a8);
  if (fVar11 * (F10)100.0f >= (F10)*(float*)0x01687a14) return 0.0f;

  int iVar7 = (int)FUN_00c22f50(p);
  float* pfVar8 = ((TFV)(*(void***)(iVar7 + 0x120))[0x2c / 4])((void*)(iVar7 + 0x120));
  float* pfVar9 = ((TFV)(*(void***)((char*)p + 0xc0))[0x2c / 4])((char*)p + 0xc0);
  float fVar1 = *pfVar9;
  float fVar2 = *pfVar8;
  float fVar3 = pfVar9[1];
  float fVar4 = pfVar8[1];
  float fVar5 = pfVar9[2];
  float fVar6 = pfVar8[2];
  int* piVar10 = (int*)FUN_00c22f50(p);
  F10 fVar13 = (F10)((TFF)(*(void***)piVar10)[0x60 / 4])((void*)piVar10);
  if (((fVar5 - fVar6) * (fVar5 - fVar6) + (fVar1 - fVar2) * (fVar1 - fVar2)) +
      (fVar3 - fVar4) * (fVar3 - fVar4) < fVar13 * fVar13) {
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00da9900
F10 __cdecl FUN_00da9900(void* p)
{
  float fStack_4 = 0.0f;
  void* mgr = FUN_00af13b0(p, 2, &fStack_4);
  if ((char)((TClookup)FUN_00af0bd0)(mgr, 2, &fStack_4) == 0) return 0.0f;
  void* tribe = FUN_00c22f50(p);
  F10 fVar2 = (F10)FUN_00da82f0(tribe, 0x4611758);
  if (fVar2 < (F10)fStack_4) return 1.0f;
  return 0.0f;
}

// @ 0x00da9a00
F10 __cdecl FUN_00da9a00(void* p, u32, u32, u8 param_4, void* stim, u8* outflag)
{
  void* gm = FUN_00b5b800();
  if (gm == (void*)0x01654c02) return 0.0f;

  float fStack_4 = 0.0f;
  if ((char)FUN_00c0b7a0(p) == 0) return 0.0f;

  void* mgr = FUN_00af13b0(p, 4, &fStack_4);
  if ((char)((TClookup)FUN_00af0bd0)(mgr, 4, &fStack_4) == 0) return 0.0f;

  void* tribe = FUN_00c22f50(p);
  F10 fVar5 = (F10)FUN_00da82f0(tribe, 0x569236e);
  int iVar4 = FUN_00c22dc0(p);
  if (iVar4 == 7) goto LAB_00da9a97;
  if ((param_4 & 1) == 0) {
    iVar4 = FUN_00c8f6e0(tribe, 7);
    if (iVar4 == 0 && (float)fVar5 < fStack_4) goto LAB_00da9a97;
  }
  return 0.0f;

LAB_00da9a97:
  if ((param_4 & 1) == 0) {
    if (stim != 0) {
      FUN_00d997e0(stim);
    }
    *(int*)((char*)stim + 0x18) = 1;
    *outflag = 1;
  }
  return 1.0f;
}

// @ 0x00da9ad0
F10 __cdecl FUN_00da9ad0(void* p, u32, u32, u8 param_4)
{
  void* gm = FUN_00b5b800();
  if (gm == (void*)0x01654c02) return 0.0f;

  float fStack_4 = 0.0f;
  void* tribe = FUN_00c22f50(p);
  if ((char)FUN_00b1fbf0(tribe) == 0) return 0.0f;

  float* pfVar4 = (float*)FUN_00c8fe20(tribe);
  if (*pfVar4 == *(float*)0x0169f3b8 &&
      pfVar4[1] == *(float*)0x0169f3bc &&
      pfVar4[2] == *(float*)0x0169f3c0) {
    return 0.0f;
  }

  void* mgr = FUN_00af13b0(p, 5, &fStack_4);
  if ((char)((TClookup)FUN_00af0bd0)(mgr, 5, &fStack_4) == 0) return 0.0f;

  if (FUN_00c22dc0(p) == 8) goto LAB_00da9bb0;
  if ((param_4 & 1) != 0) return 0.0f;
  if (FUN_00c8f6e0(tribe, 8) != 0) return 0.0f;
  {
    void* q = (void*)*(u32*)0x0169ef30;
    u32 uVar8 = ((TFU)(*(void***)q)[0x1c / 4])(q);
    F10 fVar6 = (F10)FUN_00da83b0(tribe, (void*)uVar8);
    if (fVar6 >= (F10)fStack_4) return 0.0f;
  }
LAB_00da9bb0:
  {
    u32 q = *(u32*)0x0169ef30;
    float fv = *(float*)0x0147c218;
    FUN_00c24680(0, 0x800, fv, q, 0, 0);
  }
  {
    void* e = (char*)p + 0xb4c;
    void* played = FUN_00bc96a0((void*)(*(u32*)e + 8), 0, 0x800);
    *(u32*)((char*)played + 0x14) = 1;
    FUN_00bc98f0((void*)(*(u32*)e + 8), 1, 0);
  }
  return 1.0f;
}

// @ 0x00da9c10
F10 __cdecl FUN_00da9c10(void* p, u32, u32, u8 param_4)
{
  if ((char)((TCi_p)FUN_00c0b780)(p) == 0) return 0.0f;
  void* gm = FUN_00b5b800();
  if (gm == (void*)0x01654c02) return 0.0f;

  void* fStack = 0;
  void* mgr = FUN_00af13b0(p, 3, &fStack);
  if ((char)((TClookup)FUN_00af0bd0)(mgr, 3, &fStack) == 0) return 0.0f;

  if (((TCi_p)FUN_00c22dd0)(p) == 1) goto LAB_00da9c93;
  {
    void* tribe = ((TCp_p)FUN_00c22f50)(p);
    char cVar2 = (char)((TCi_pu)FUN_00c8f730)(tribe, 1);
    if ((param_4 & 1) == 0 && cVar2 != 0) {
      F10 fVar5 = (F10)FUN_00da82f0(tribe, 0x5218bb3);
      if (fVar5 < (F10)(float)(int)fStack) goto LAB_00da9c93;
    }
  }
  return 0.0f;
LAB_00da9c93:
  return 1.0f;
}

// @ 0x00da9ca0
F10 __cdecl FUN_00da9ca0(int* p)
{
  if (*(int*)(p[0x2d3] + 0x1d8) == 0x5218bb3) return 0.0f;

  void* uVar8 = FUN_00bc96a0((void*)(p[0x2d3] + 8), 0, 0x80);
  int iVar9 = (int)FUN_00d999d0(uVar8);
  if (iVar9 != 0 && *(char*)(iVar9 + 0xb5e) == 0) {
    int i0 = *(int*)(iVar9 + 0xc0);
    float* pfVar10 = ((TFV)(*(void***)i0)[0x2c / 4])((void*)i0);
    int p30 = p[0x30];
    float* pfVar11 = ((TFV)(*(void***)p30)[0x2c / 4])((void*)p30);
    float fVar1 = *pfVar11;
    float fVar2 = *pfVar10;
    float fVar3 = pfVar11[1];
    float fVar4 = pfVar10[1];
    float fVar5 = pfVar11[2];
    float fVar6 = pfVar10[2];
    F10 fVar12 = (F10)((TFF)(*(void***)i0)[0x74 / 4])((void*)i0);
    F10 fVar13 = (F10)((TFF)(*(void***)p30)[0x74 / 4])((void*)p30);
    float dist = (float)fVar12;
    F10 d = (F10)(
        (float)sqrtf(
            ((fVar5 - fVar6) * (fVar5 - fVar6) + (fVar3 - fVar4) * (fVar3 - fVar4)) +
            (fVar1 - fVar2) * (fVar1 - fVar2)) -
        (fVar13 + (float)dist));
    char cVar7 = (char)FUN_00c0d560((void*)iVar9, 1.0f, (float)d);
    if (cVar7 == 0) {
      cVar7 = ((TFCI)(*(void***)p)[0xc0 / 4])(p, iVar9, 1.0f, (float)d);
      if (cVar7 == 0) return 0.0f;
    }
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00da9db0
F10 __cdecl FUN_00da9db0(int* p, double param_2, u32 param_3, u32, u32, int in20)
{
  char cVarA = (*(char(__thiscall**)(void*))(*(void***)p[0x30] + 0x48 / 4))((void*)p[0x30]);
  if ((cVarA == 0) && ((param_3 & 0x300) != 0)) return 0.0f;
  if (*(int*)(in20 + 0xd) == -1) return 0.0f;
  u32 uVar3 = *(int*)(in20 + 0x2d) + 1;
  if (uVar3 >= 6) return 0.0f;

  int iVar5 = p[0x2d3];
  int iVar4 = uVar3 * 0xac;
  double dVar1 = *(double*)(iVar4 + 0x1f0 + iVar5);
  char cVarB = (*(char(__thiscall**)(void*))(*(void***)p[0x30] + 0x58 / 4))((void*)p[0x30]);
  if (cVarB != 0 &&
      !(*(int*)(iVar4 + 0x1e0 + iVar5) == *(int*)(p[0x2d3] + 0x1d0) && 10.0 < param_2 - dVar1)) {
    return 0.0f;
  }

  FUN_00b3d2c0();
  int iVarBase = ((TFI)(*(void***)p)[0x4c / 4])((void*)p);
  int* piVar6 = (int*)FUN_00c420d0();
  int* piVar10 = (int*)*piVar6;
  piVar6 = (int*)piVar6[1];
  if (piVar10 != piVar6) {
    do {
      int* piVar7;
      if ((void*)*piVar10 != 0 &&
          (piVar7 = (int*)((TFVU)(*(void***)(void*)*piVar10)[0xb8 / 4])((void*)*piVar10, 0x4f176642),
           piVar7 != 0) &&
          ((iVar4 = ((TFI)(*(void***)piVar7)[0x4c / 4])((void*)piVar7), iVar4 == iVarBase) ||
           (iVar4 = FUN_00d00a70((void*)iVarBase, (void*)iVar4, 1), 2 < iVar4))) {
        int iVar4b = (int)FUN_00bc96a0((void*)(piVar7[0x2d3] + 8), 0, 0x80);
        if (iVar4b != 0) {
          void* uVar8 = FUN_00d999d0((void*)iVar4b);
          int* piVar7b = (int*)FUN_00d994c0(uVar8);
          if (piVar7b == 0 ||
              ((TFI)(*(void***)piVar7b)[0x4c / 4])((void*)piVar7b) != iVarBase) {
            FUN_00bc97f0(0, 0x80, *(void**)(iVar4b + 8), *(void**)(iVar4b + 0x2c));
            break;
          }
        }
      }
      piVar10 = piVar10 + 1;
      if (piVar10 == piVar6) return 0.0f;
    } while (1);
  }
  return 0.0f;
}

// @ 0x00da9f40
F10 __cdecl FUN_00da9f40(int* p, u32, u32, u32 param_4)
{
  char cVar1 = (*(char(__thiscall**)(void*))(*(void***)p[0x30] + 0x48 / 4))((void*)p[0x30]);
  if ((cVar1 == 0) && ((param_4 & 0x300) == 0)) return 0.0f;

  FUN_00b3d2c0();
  int iVar2 = ((TFI)(*(void***)p)[0x4c / 4])((void*)p);
  int* piVar3 = (int*)FUN_00c420d0();
  int* piVar8 = (int*)*piVar3;
  piVar3 = (int*)piVar3[1];
  if (piVar8 != piVar3) {
    do {
      int* piVar4;
      if ((void*)*piVar8 != 0 &&
          (piVar4 = (int*)((TFVU)(*(void***)(void*)*piVar8)[0xb8 / 4])((void*)*piVar8, 0x4f176642),
           piVar4 != 0) &&
          (((TFI)(*(void***)piVar4)[0x4c / 4])((void*)piVar4) == iVar2 ||
           FUN_00d00a70((void*)iVar2, (void*)((TFI)(*(void***)piVar4)[0x4c / 4])((void*)piVar4), 1) > 2)) {
        int iVar5 = (int)FUN_00bc96a0((void*)(piVar4[0x2d3] + 8), 0, 0x80);
        if (iVar5 != 0) {
          void* uVar6 = FUN_00d999d0((void*)iVar5);
          int* piVar7 = (int*)FUN_00d994c0(uVar6);
          if (piVar7 == 0 ||
              ((TFI)(*(void***)piVar7)[0x4c / 4])((void*)piVar7) != iVar2) {
            iVar5 = (int)FUN_00bc96a0((void*)(piVar4[0x2d3] + 8), 0, 0x80);
            if (iVar5 != 0) {
              FUN_00bc97f0(0, 0x80, *(void**)(iVar5 + 8), *(void**)(iVar5 + 0x2c));
              break;
            }
          }
        }
      }
      piVar8 = piVar8 + 1;
      if (piVar8 == piVar3) return 0.0f;
    } while (1);
  }
  return 0.0f;
}

// @ 0x00daa070
F10 __cdecl FUN_00daa070(void* p, u32, u32, u32 param_4)
{
  if ((param_4 & 2) == 0) return 0.0f;

  int* piVar8 = (int*)FUN_00c22f50(p);
  int iVar9 = ((TFI)(*(void***)piVar8)[0xac / 4])((void*)piVar8);

  int q0 = *(int*)(iVar9 + 0x34);
  float* pfVar10 = ((TFV)(*(void***)q0)[0x2c / 4])((void*)(iVar9 + 0x34));
  int p0 = *(int*)((char*)p + 0xc0);
  float* pfVar11 = ((TFV)(*(void***)p0)[0x2c / 4])((char*)p + 0xc0);
  float fVar2 = *pfVar11;
  float fVar3 = *pfVar10;
  float fVar4 = pfVar11[1];
  float fVar5 = pfVar10[1];
  float fVar6 = pfVar11[2];
  float fVar7 = pfVar10[2];
  F10 fVar12 = (F10)((TFF)(*(void***)q0)[0x70 / 4])((void*)(iVar9 + 0x34));
  F10 fVar13 = (F10)((TFF)(*(void***)p0)[0x70 / 4])((char*)p + 0xc0);
  float diff = (float)((float)fVar12 - (float)fVar13);
  if (diff * diff < ((fVar6 - fVar7) * (fVar6 - fVar7) + (fVar4 - fVar5) * (fVar4 - fVar5)) +
                        (fVar2 - fVar3) * (fVar2 - fVar3)) {
    FUN_00c238b0(p);
  }
  u32* puVar1 = (u32*)(*(int*)((char*)p + 0xb4c) + 0x5fc);
  *puVar1 = *puVar1 & 0xffffff7f;
  return 0.0f;
}

// @ 0x00daa170
F10 __cdecl FUN_00daa170(int* p, u32, u32, u32, void* stim, u8* outflag)
{
  int* piVar5 = 0;
  void* pvVar1 = 0;
  void* pvVar2 = 0;
  void* pvVar3 = 0;
  int iVar4 = (int)FUN_00bc96a0((void*)(p[0x2d3] + 8), 0x400000, 0);
  if (iVar4 != 0) {
    piVar5 = (int*)FUN_00d999d0((void*)iVar4);
    if (piVar5 != 0) {
      int iVar6 = ((TFI)(*(void***)piVar5)[0x4c / 4])((void*)piVar5);
      if (iVar6 != -1) {
        pvVar1 = *(void**)(iVar4 + 0xc);
        pvVar2 = *(void**)(iVar4 + 0x10);
        pvVar3 = *(void**)(iVar4 + 0x14);
        int pq = piVar5[0x30];
        float* pfVar7 = ((TFV)(*(void***)pq)[0x2c / 4])((void*)pq);
        float fVar11 = (float)(int)pvVar3 - pfVar7[2];
        float fVar10 = (float)(int)pvVar2 - pfVar7[1];
        float fVar9 = (float)(int)pvVar1 - *pfVar7;
        if ((fVar11 * fVar11 + fVar10 * fVar10) + fVar9 * fVar9 <= 1.0f) {
          FUN_00b3d2c0();
          int iVar4b = ((TFI)(*(void***)p)[0x4c / 4])((void*)p);
          if (iVar4b == iVar6) goto LAB_00daa278;
          if (FUN_00d00a70((void*)iVar4b, (void*)iVar6, 1) > 2) goto LAB_00daa278;
          if (FUN_00d00a70((void*)iVar6, (void*)iVar4b, 1) > 2) goto LAB_00daa278;
        }
      }
    }
  }
  FUN_00bc98f0((void*)(p[0x2d3] + 8), 0x400000, 0);
  return 0.0f;

LAB_00daa278:
  if (stim != 0) {
    FUN_00d997e0(stim);
  }
  *outflag = 1;
  *(void**)((char*)stim + 0x0) = pvVar1;
  *(int**)((char*)stim + 0x4) = piVar5 + 0x16a;
  *(void**)((char*)stim + 0x8) = pvVar2;
  *(void**)((char*)stim + 0xc) = pvVar3;
  FUN_00bc98f0((void*)(p[0x2d3] + 8), 0x400000, 0);
  return 1.0f;
}

// @ 0x00daa2f0
F10 __cdecl FUN_00daa2f0(int param_1, u32, u32, u32, void* stim, u8* outflag)
{
  int iVar8 = (int)FUN_010407c0();
  if (*(char*)(iVar8 + 0x4c) == 0) return 0.0f;

  iVar8 = (int)FUN_00ffbe50();
  if (iVar8 == 0) return 0.0f;
  void* pcVar9 = FUN_00ffbe50();
  iVar8 = (int)FUN_00a1ad60(pcVar9);
  if (iVar8 == 0) return 0.0f;
  char cVar7 = (char)FUN_00c38990((void*)iVar8, 1);
  if (cVar7 != 0) return 0.0f;

  int q0 = *(int*)(iVar8 + 0x34);
  float* pfVar10 = ((TFV)(*(void***)q0)[0x2c / 4])((void*)(iVar8 + 0x34));
  int p0 = *(int*)(param_1 + 0xc0);
  float* pfVar11 = ((TFV)(*(void***)p0)[0x2c / 4])((void*)(param_1 + 0xc0));
  float fVar1 = *pfVar11;
  float fVar2 = *pfVar10;
  float fVar3 = pfVar11[1];
  float fVar4 = pfVar10[1];
  float fVar5 = pfVar11[2];
  float fVar6 = pfVar10[2];
  int iVar12 = (int)FUN_010407c0();
  float r = *(float*)(iVar12 + 0x44);
  if (((fVar5 - fVar6) * (fVar5 - fVar6) + (fVar3 - fVar4) * (fVar3 - fVar4)) +
      (fVar1 - fVar2) * (fVar1 - fVar2) >= r * r) {
    return 0.0f;
  }
  if (stim != 0) {
    FUN_00d997e0(stim);
  }
  *outflag = 1;
  *(int*)((char*)stim + 0x4) = iVar8 + 0x508;
  iVar8 = (int)FUN_010407c0();
  *(void**)((char*)stim + 0xc) = (void*)(int)*(float*)(iVar8 + 0x44);
  return 1.0f;
}

// @ 0x00daa420
F10 __cdecl FUN_00daa420(int param_1, u32, u32, u32, void* stim, u8* outflag, int in20)
{
  if (stim != 0) {
    FUN_00d997e0(stim);
  }
  *outflag = 1;
  void* uVar6 = FUN_00d99420((void*)(*(int*)(param_1 + 0xb4c) + 0x1d0), *(u32*)(in20 + 0x2d));
  FUN_00d996e0(uVar6, stim);
  float fVar5 = (float)(int)*(void**)((char*)stim + 0xc);
  if ((int)*(void**)((char*)stim + 0xc) < 0) {
    fVar5 = fVar5 + 4.2949673e+09f;
  }
  int* piVar4 = *(int**)((char*)stim + 0x4);
  int iVar7;
  if (piVar4 == 0) {
    iVar7 = 0;
  } else {
    iVar7 = (*(int(__thiscall**)(void*, u32))(*(void***)piVar4 + 0x5c / 4))(piVar4, 0xb033b403);
  }
  int q0 = *(int*)(iVar7 + 0x34);
  float* pfVar8 = ((TFV)(*(void***)q0)[0x2c / 4])((void*)(iVar7 + 0x34));
  float fVar1 = *pfVar8;
  float fVar2 = pfVar8[1];
  float fVar3 = pfVar8[2];
  int p0 = *(int*)(param_1 + 0xc0);
  pfVar8 = ((TFV)(*(void***)p0)[0x2c / 4])((void*)(param_1 + 0xc0));
  if (((pfVar8[2] - fVar3) * (pfVar8[2] - fVar3) + (pfVar8[1] - fVar2) * (pfVar8[1] - fVar2)) +
      (*pfVar8 - fVar1) * (*pfVar8 - fVar1) < (fVar5 * 0.5f) * (fVar5 * 0.5f)) {
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00daa530
float __cdecl FUN_00daa530(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, behavior_stimuli_s00da_a530* stim, uint8_t* out, uint32_t, PState* in20)
{
    if (stim != 0) stim->GetAny();
    *out = 1;
    void* uVar6 = FUN_00d99420(&c->mpB4C->mOwner1d0, in20->m2d);
    FUN_00d996e0(uVar6, stim);
    float fVar5 = (float)stim->mF18;

    Has34* pObj;
    Has5C* piVar4 = (Has5C*)stim->mTarget;
    if (piVar4 == 0) {
        pObj = 0;
    } else {
        pObj = (Has34*)piVar4->v5c(0xb033b403);
    }

    Vec3* pt = pObj->m34.v2c();
    float tx = pt->x;
    float ty = pt->y;
    float tz = pt->z;

    Vec3* pm = c->mC0.v2c();
    float dx = pm->x - tx;
    float dy = pm->y - ty;
    float dz = pm->z - tz;

    if (dz * dz + dy * dy + dx * dx < fVar5 * fVar5) return 1.0f;
    return 0.0f;
}

// @ 0x00daa640
float __cdecl FUN_00daa640(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, behavior_stimuli_s00da_a530* stim, uint8_t* out)
{
    void* puVar2 = c->mC0.FUN_00c420d0();
    HasB8** piVar5 = (HasB8**)(*(void**)puVar2);
    HasB8** piVar1 = (HasB8**)(*((void**)puVar2 + 1));
    for (;;) {
        if (piVar5 == piVar1) return 0.0f;
        if (*piVar5 != 0) {
            Creature_s00da_a530* iVar3 = (*piVar5)->v_b8(0xce9f6639);
            if (iVar3 != 0) {
                Creature_s00da_a530* iVar4 = (Creature_s00da_a530*)FUN_00d99500(iVar3);
                if (iVar4 == 0) {
                    iVar3 = (Creature_s00da_a530*)FUN_00d994c0(iVar3);
                    if (iVar3 != 0 && c->mIdB20 != iVar3->mIdB20 &&
                        iVar3->mpB4C->mStimuli.Play(0x1000, 0) != 0) {
                        if (stim != 0) stim->GetAny();
                        stim->mTarget = (char*)iVar3 + 0x5a8;
                        *out = 1;
                        return 1.0f;
                    }
                } else if ((iVar4->mpB4C->mFlags5fc & 0x800000) != 0) {
                    if (stim != 0) stim->GetAny();
                    stim->mTarget = (char*)iVar4 + 0x5a8;
                    *out = 1;
                    return 1.0f;
                }
            }
        }
        piVar5++;
    }
}

// @ 0x00daa740
float __cdecl FUN_00daa740(Creature_s00da_a530* c)
{
    AnimPlayRes_s00da_a530* iVar4 = c->mpB4C->mStimuli.Play(0x2000000, 0);
    void* uVar5 = FUN_00d999d0(iVar4);
    Creature_s00da_a530* iVar6 = (Creature_s00da_a530*)FUN_00d994c0(uVar5);
    if (iVar6 != 0 && iVar6 != c) {
        int32_t iVar2 = (int32_t)c->mpB4C->mKey1d8;
        int32_t iVar3 = (int32_t)iVar6->mpB4C->mKey1d8;
        if (((iVar2 != 0x461300f && iVar2 != 0x4623e0c) ||
             (iVar3 != 0x461300f && iVar3 != 0x4623e0c)) &&
            (iVar2 != 0x4611758 || iVar3 != 0x4611758)) {
            float fVar9  = iVar4->mF0c.f;
            float fVar1  = iVar4->mF18.f;
            float fVar10 = iVar4->mF10.f;
            float fVar11 = iVar4->mF14.f;
            Vec3* pfVar7 = c->mC0.v2c();
            fVar9  -= pfVar7->x;
            fVar10 -= pfVar7->y;
            fVar11 -= pfVar7->z;
            fVar1 = c->mC0.v74() + fVar1;
            if ((fVar11 * fVar11 + fVar10 * fVar10) + fVar9 * fVar9 < fVar1 * fVar1)
                return 1.0f;
        }
    }
    c->mpB4C->mStimuli.ClearAll(0x2000000, 0);
    return 0.0f;
}

// @ 0x00daa8c0
float __cdecl FUN_00daa8c0(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, behavior_stimuli_s00da_a530* stim, uint8_t* out)
{
    Tribe* psiVar4 = c->GetTribe();
    int32_t* piVar5 = (int32_t*)FUN_00b3d4d0();
    if (piVar5[0x2c / 4] == 1) return 0.0f;

    AnimPlayRes_s00da_a530* piVar8 = c->mpB4C->mStimuli.Play(0, 0x40);
    void* pvVar1 = piVar8->mF14.p;
    uint32_t uVar2 = piVar8->mF0c.u;
    uint32_t uVar5 = piVar8->mF10.u;

    if (pvVar1 == (void*)0x7dcc4e7e) {
        char cVar3 = c->FUN_00c0b770();
        if (cVar3 != 0 && psiVar4->mToolId26c == -1) return 0.0f;
    }
    c->mpB4C->mStimuli.ClearAll(0, 0x40);

    int32_t iVar4 = psiVar4->mToolId26c;
    if (iVar4 != -1) {
        iVar4 = FUN_00b3d4e0()->FUN_00bc3db0(iVar4);
        if (iVar4 == 0) return 0.0f;
    }
    int32_t* piVar6 = FUN_00b3d4e0()->FUN_00bc7610((uint32_t)pvVar1, 0);
    if (uVar2 <= (uint32_t)((piVar6[1] - piVar6[0]) / 0x7b4)) {
        if (stim != 0) stim->GetAny();
        stim->mF1c = pvVar1;
        stim->mF18 = (uVar5 << 0x10) | (uVar2 & 0xffff);
        *out = 1;
        return 1.0f;
    }
    return 0.0f;
}

// @ 0x00daa9b0
float __cdecl FUN_00daa9b0(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, behavior_stimuli_s00da_a530* stim, uint8_t* out)
{
    AnimPlayRes_s00da_a530* iVar4 = c->mpB4C->mStimuli.Play(0, 0x80000);
    float uVar1 = iVar4->mF08.f;
    ResObj* piVar5 = (ResObj*)FUN_00d99a10(iVar4);
    if (piVar5 != 0) piVar5->v60();
    c->mpB4C->mStimuli.ClearAll(0, 0x80000);
    if (piVar5 == 0) return 0.0f;

    if (stim != 0) stim->GetAny();
    *out = 1;
    stim->mF18 = 0x2cc62c6;

    ObjC* piVar6 = (ObjC*)piVar5->v0c();
    if (piVar6 != 0) {
        if (piVar6->v20() == (void*)0x18eb45e && piVar6->FUN_00c0c0e0() != 0)
            stim->mF18 = 0x65e6623;
    }
    stim->mF1c = (void*)3;
    stim->mF20 = 0x33;

    PosObj* piVar7 = (PosObj*)piVar5->v08();
    Vec3* puVar8 = piVar7->v2c();
    stim->mF0c = puVar8->x;
    stim->mF10 = puVar8->y;
    stim->mF14 = puVar8->z;

    void* piVar9 = c->GetTribe()->v90();
    Creature_s00da_a530** ppc = (Creature_s00da_a530**)(*(void**)piVar9);
    Creature_s00da_a530** ppEnd = (Creature_s00da_a530**)(*((void**)piVar9 + 1));
    for (; ppc != ppEnd; ppc++) {
        Creature_s00da_a530* pcVar2 = *ppc;
        if (pcVar2 != c) {
            Vec3* pfVar10 = pcVar2->mC0.v2c();
            float fVar12 = pfVar10->x - stim->mF0c;
            float fVar13 = pfVar10->y - stim->mF10;
            float fVar14 = pfVar10->z - stim->mF14;
            if ((fVar12 * fVar12 + fVar13 * fVar13) + fVar14 * fVar14 < 400.0f &&
                (pcVar2->mpB4C->mFlags1cc & 0x80000) == 0) {
                void* uVar11 = piVar5->v0c();
                c->mpB4C->mStimuli.PlayWith(0, 0x80000, uVar1, uVar11);
            }
        }
    }
    piVar5->v64();
    return 1.0f;
}

// @ 0x00daab90
float __cdecl FUN_00daab90(Creature_s00da_a530* c)
{
    OrderRec_s00da_a530* piVar2 = (OrderRec_s00da_a530*)c->mpB4C->FirstPending();
    if (piVar2 != 0 && piVar2->mType == 0x16) {
        OrderSub* pSub = &piVar2->mSub;
        int16_t sVar1 = pSub->mShort;
        uint32_t* puVar3;
        if (sVar1 == 10 || sVar1 == 0x10) {
            if ((pSub->mFlag & 0x30) == 0)
                puVar3 = (uint32_t*)(-(int32_t)(sVar1 != 0) & (int32_t)(intptr_t)pSub);
            else
                puVar3 = pSub->mObj;
        } else {
            puVar3 = (uint32_t*)&DAT_015d1164;
        }
        int32_t iVar4 = (int32_t)((CrtVt*)c)->v45(*puVar3);
        if (iVar4 != 0 && *(int32_t*)(iVar4 + 8) == 0x37) return 1.0f;
    }
    return 0.0f;
}

// @ 0x00daac00
uint8_t __cdecl FUN_00daac00(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, uint32_t, StateAC* out)
{
    if (out->mpObj != 0) {
        if (c->mSub58.s1c() != 0) {
            Obj70* pB = (Obj70*)c->mSub58.s28();
            Obj70* pS = (Obj70*)c->mSub58.s20();
            if (pB != 0) {
                if (pB->o1c() == out->mpObj->o1c() && pB->m70 != 0) return 1;
            }
            if (pS != 0) {
                if (pS->o1c() == out->mpObj->o1c() && pS->m70 != 0) return 1;
            }
        }
    }

    int32_t lVal10Lo = (int32_t)out->mVal10;
    int32_t lVal10Hi = (int32_t)(out->mVal10 >> 32);
    out->mFlag08 = 1;
    int32_t* puVar9 = (int32_t*)c->mpB4C->FirstPending();
    long long r = 0;
    if (puVar9 != 0) r = FUN_00da6090((uint32_t)*puVar9);
    if (puVar9 == 0 || r != out->mVal10) {
        c->mpB4C->mStimuli.ClearAll(lVal10Lo, lVal10Hi);
    } else {
        c->mpB4C->PopFront();
        c->mpB4C->mStimuli.ClearAll(0x1d3fbffa, 0x8124080);
    }
    c->FUN_00c26450();
    return 0;
}

// @ 0x00daad10
uint32_t __fastcall FUN_00daad10(SelObj* p)
{
    float local = g_f147c218;
    void** piVar1 = p->mpEnd;
    void** piVar5 = p->mpBegin;
    for (; piVar5 != piVar1; piVar5++) {
        SelObj0* piVar2 = (SelObj0*)*piVar5;
        Vec3* pfVar4 = piVar2->v2c();
        float dx = p->mX - pfVar4->x;
        float dy = p->mY - pfVar4->y;
        float dz = p->mZ - pfVar4->z;
        float d2 = (dz * dz + dy * dy) + dx * dx;
        if (d2 < local) {
            SelObj0* piVar3 = (SelObj0*)p->mpBest;
            local = d2;
            if (piVar2 != piVar3) {
                piVar2->mbc();
                p->mpBest = piVar2;
                if (piVar3 != 0) piVar3->mc0();
            }
        }
    }
    return (uint32_t)(uintptr_t)p->mpBest;
}

// @ 0x00daadf0
uint32_t __cdecl FUN_00daadf0(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, uint32_t, StateF0* out)
{
    out->m00 = 0;
    out->m04 = 0.0f;
    Tribe* piVar1 = c->GetTribe();
    float fVar4 = piVar1->v60();
    c->mpB4C->mStimuli.ClearAll(0x200000, 0);
    Vec3* pfVar2 = piVar1->mObj120.v2c();
    Vec3* pfVar3 = c->mC0.v2c();
    float dy = pfVar3->y - pfVar2->y;
    float dz = pfVar3->z - pfVar2->z;
    float dx = pfVar3->x - pfVar2->x;
    if ((dx * dx + dy * dy) + dz * dz < fVar4 * fVar4) {
        out->mFlag08 = 1;
        return 1;
    }
    out->mFlag08 = 0;
    return 1;
}

// @ 0x00daaec0
uint32_t __cdecl FUN_00daaec0(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, uint32_t, StateEC* out)
{
    if ((char)out->pObj->e2c() != 0) return 0;
    if ((char)out->pObj->FUN_00c38990(1) != 0) return 0;
    Vec3* pfVar2 = out->pObj->m34.v2c();
    Vec3* pfVar3 = c->mC0.v2c();
    float dy = pfVar3->y - pfVar2->y;
    float dz = pfVar3->z - pfVar2->z;
    float dx = pfVar3->x - pfVar2->x;
    if ((dx * dx + dy * dy) + dz * dz < out->mRadius2) return 1;
    return 0;
}

// @ 0x00daaf60
uint8_t __cdecl FUN_00daaf60(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, State60* out)
{
    out->m04 = 0.0f;
    double fVar1 = ((RandomLCG*)0x1601760)->RandomDoubleUniform();
    double fVar2 = 1.0;
    if (fVar1 < 1.0 && (fVar2 = fVar1, fVar1 < 0.0)) {
        out->m00 = 0;
        out->m08 = 0.0;
        return 1;
    }
    out->m00 = 0;
    out->m08 = (float)fVar2;
    return 1;
}

// @ 0x00dab1f0
namespace SP {
bool TRIBE_GET_TOOL_Tick(Citizen* c, int p2, float p3, int p4, int p5, GetToolState* st)
{
    if (!st->mpOther) return false;
    if (st->mpOther->vf2c()) return false;

    const Vec3* p = st->mpOther->mBundle.GetPosition();
    float dx = p->x - st->mPosX;
    float dy = p->y - st->mPosY;
    float dz = p->z - st->mPosZ;
    if (dx * dx + dy * dy + dz * dz > 1.0f) return false;

    if (st->mpOther->FUN_00bf3a90() > 0) {
        if (c->mLoco.vf58()) return false;
    }

    if (st->mState == 0) {
        float radius = c->mLoco.GetRadius() + st->mpOther->mBundle.GetRadius();
        float* v = st->mpOther->GetTribe()->FUN_00c986d0(st->mTribe, &st->miResult, c);
        if (st->miResult < 0) {
            st->mpOther->FUN_00c9d150();
            return false;
        }
        void* part = st->mpOther ? (void*)st->mpOther->mPart120 : (void*)0;
        c->vf84(part, 1, 4);

        const Vec3* q = st->mpOther->mBundle.GetPosition();
        Vec3 delta;
        delta.x = v[0] - q->x;
        delta.y = v[1] - q->y;
        delta.z = v[2] - q->z;
        Vec3 dir;
        SP::normalized_safe(&dir, &delta);

        float d = radius + 0.1f;
        float offX = dir.x * d;
        float offY = dir.y * d;
        float offZ = dir.z * d;
        const Vec3* r = st->mpOther->mBundle.GetPosition();
        Vec3 target;
        target.x = r->x + offX;
        target.y = r->y + offY;
        target.z = r->z + offZ;
        Vec3 facing;
        facing.x = -dir.x;
        facing.y = -dir.y;
        facing.z = -dir.z;
        c->MoveToPointAndFacingAtSpeed(2, &target, &facing, 1.0f, 2.0f);
        st->mState = 1;
        return true;
    }

    if (st->mState == 1) {
        if (!c->mLoco.IsNearGoal()) return true;
        st->mState = 2;
        float box[6];
        const float* m = st->mpOther->mBundle.FUN_v6c(box);
        Vec3 mid;
        mid.x = (m[0] + m[3]) * 0.5f;
        mid.y = (m[4] + m[1]) * 0.5f;
        mid.z = (m[5] + m[2]) * 0.5f;
        st->miAnim = c->PlayAnimationWithTarget(0x51c73a5, &mid, -1);
        return true;
    }

    if (st->mState == 2) {
        if (c->AnimationFinished(st->miAnim)) {
            st->mpOther->FUN_00c9d150();
            return false;
        }
        return true;
    }
    return true;
}
}  // namespace SP

// @ 0x00dabc30
bool FUN_00dabc30(Citizen* c)
{
    if (c->mpAnim->mCtl.PlayIdleAnimation(0, 0x80) != 0) return false;

    struct Key { Tribe_s00da_b1f0* mTribe; Citizen* mCitizen; } key;
    key.mTribe = c->GetTribe();
    key.mCitizen = c;

    ToolNode* task = FUN_00bc9b00()->Find(0x567cb99, (void*)0xdabbe0, &key);
    if (task) {
        Vec3 n;
        n.x = -task->mPos.x;
        n.y = -task->mPos.y;
        n.z = -task->mPos.z;
        c->MoveToPointAndFacingAtSpeed(2, (Vec3*)c->mLoco.GetPosition(), &n, 1.0f, 2.0f);
    }
    return task != 0;
}

// @ 0x00dabd10
bool FUN_00dabd10(IteratorB9* param_1, Citizen* param_2)
{
    if (param_1->FUN_00bc9b50()) return false;

    Citizen* other = param_1->FUN_00bc9b10();
    if (other->GetTribe() != param_2->GetTribe()) return false;

    float r = other->GetTribe()->FUN_v60();
    float rr = r + r;

    const Vec3* a = param_2->mLoco.GetPosition();
    const Vec3* b = other->mLoco.GetPosition();
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    float d2 = dx * dx + dy * dy + dz * dz;

    if (d2 < rr * rr) return true;
    return false;
}

// @ 0x00dabdf0
bool FUN_00dabdf0(Citizen_s00da_bdf0* self, int a2, int a3, int a4, int a5, EatTickState* st)
{
    CBehaviour* beh = FUN_00b3d2b0_s00da_bdf0();
    CTool* target = st->mp0c;

    if (target == 0 ||
        ((Fn_b)VT(target, 0x2c))(target) ||
        !beh->FUN_00ac7ef0(self, target))
    {
        CTribe* t = self->GetTribe();
        CTool* tool = t->m20c.FUN_00cee330();
        if (tool == 0)
            return FUN_00da6270(self, 0);

        CTool* old = st->mp0c;
        if (tool != old)
        {
            ((Fn_v)VT(tool, 0))(tool);
            st->mp0c = tool;
            if (old != 0)
                ((Fn_v)VT(old, 4))(old);
        }
        target = tool;
    }

    if (!beh->FUN_00ac7ef0(self, target))
        return FUN_00da6270(self, 0);

    switch (st->mi08)
    {
    case 0:
        if (self->m34.FUN_00cee380() > 0.0f)
        {
            self->FUN_00c14750(0);
            st->mi08 = 3;
            return true;
        }
        self->FUN_00c25480(0, 1);
        ((Fn_v)VT(&static_cast<CLoco&>(*self), 0xec))(&static_cast<CLoco&>(*self));
        st->mi08 = 4;
        return true;

    case 1:
        if (!self->FUN_00c25480(0, 0))
            break;
        if (!static_cast<CLoco&>(*self).IsNearGoal())
            break;
        {
            int u = self->FUN_00c22820();
            self->PlayAnimationWithTarget(0x2796b31, &target->m34, -1, u);
            st->mi08 = 2;
            return true;
        }

    case 2:
        {
            bool flag = false;
            if (self->WaitForAnimEventOrEnd(0xbfa50b5a, &flag, -1, 0, 1))
            {
                int id  = target->m12c;
                int eff = self->FUN_00c22c40(id);
                self->SetCurrentToolEffect(eff, -1);
                st->mi08 = 3;
                return true;
            }
        }
        break;

    case 3:
        if (self->AnimationFinished(0))
        {
            int u = self->FUN_00c22820();
            self->PlayAnimation(0x2796b38, 1, u);
            int id  = target->m12c;
            int eff = self->FUN_00c22c40(id);
            self->SetCurrentToolEffect(eff, -1);
            st->mi08 = 6;
            return true;
        }
        break;

    case 4:
        {
            CTribe* t = self->GetTribe();
            Vec3_s00da_bdf0 vec;
            t->FUN_00c979e0(&vec, 0xd, self);

            CLoco* loco = static_cast<CLoco*>(self);
            C41Obj* obj = loco->FUN_00c41ec0();
            bool far = true;
            if (obj->m5c != 0)
            {
                Vec3_s00da_bdf0* pp = obj->FUN_00c423c0();
                Vec3_s00da_bdf0  d;
                d.x = pp->x - vec.x;
                d.y = pp->y - vec.y;
                d.z = pp->z - vec.z;
                float dist2 = d.x * d.x + d.y * d.y + d.z * d.z;
                far = DAT_01572070 < dist2;
            }
            if (far)
            {
                float sc = ((Fn_f)VT(loco, 0x74))(loco);
                self->MoveToPointAtSpeed(2, &vec, sc * 3.0f, sc * 4.0f);
            }

            self->FUN_00c25480(0, 0);

            if (loco->IsNearGoal())
            {
                self->mpB4C->mp600->mi1a4++;

                int v = t->FUN_00c97ca0(0xd, self);
                st->mi00 = v;

                Vec3_s00da_bdf0 vec2;
                t->FUN_00c97b10(&vec2, 0xd, self);

                CTool* tool = self->GetTribe()->mp260;
                Vec3_s00da_bdf0*  cam  = (Vec3_s00da_bdf0*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);

                Vec3_s00da_bdf0 dir;
                dir.x = cam->x - vec2.x;
                dir.y = cam->y - vec2.y;
                dir.z = cam->z - vec2.z;
                Vec3_s00da_bdf0 n = normalized_safe(dir);

                self->MoveToPointAndFacingAtSpeed(2, &vec2, &n,
                                                  DAT_01572070, DAT_0157206c);
                st->mi08 = 5;
                return true;
            }
        }
        break;

    case 5:
        {
            self->FUN_00c25480(0, 0);

            CTribe* t = self->GetTribe();
            bool changed = false;

            int v = t->FUN_00c97c40(0xd, self);
            if (v != st->mi00)
            {
                st->mi00 = v;
                changed = true;
            }

            CNeighborInfo* nb = self->mpB4C->mp600;

            if (st->mi00 == 0)
            {
                if (changed)
                    goto movement;

                if ((nb->mi10 >> 1) <= nb->mi1a4 &&
                    static_cast<CLoco&>(*self).IsNearGoal())
                {
                    Vec3_s00da_bdf0* pt = t->FUN_00c986d0(0xd, &st->mi10, self);
                    if (st->mi10 < 0)
                        return true;

                    st->mi00 = -1;
                    t->FUN_00c97d40(0xd, self);

                    CTool* tool = self->GetTribe()->mp260;
                    Vec3_s00da_bdf0*  cam  = (Vec3_s00da_bdf0*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);

                    Vec3_s00da_bdf0 dir;
                    dir.x = pt->x - cam->x;
                    dir.y = pt->y - cam->y;
                    dir.z = pt->z - cam->z;
                    Vec3_s00da_bdf0 n = normalized_safe(dir);

                    Vec3_s00da_bdf0 neg;
                    neg.x = -n.x;
                    neg.y = -n.y;
                    neg.z = -n.z;

                    self->MoveToPointAndFacingAtSpeed(2, pt, &neg,
                                                      DAT_01572070, DAT_0157206c);
                    st->mi08 = 1;
                    return true;
                }
            }
            else if (changed)
            {
                goto movement;
            }

            if (st->mi00 == 0 && (self->m330 & 1) != 0)
            {
                st->mi00 = -1;
                t->FUN_00c97d40(0xd, self);
                st->mi08 = 0;
                return true;
            }
            break;

        movement:
            {
                CTribe* t2 = self->GetTribe();
                Vec3_s00da_bdf0 vec;
                t2->FUN_00c97b10(&vec, 0xd, self);

                CTool* tool = t2->mp260;
                Vec3_s00da_bdf0*  cam  = (Vec3_s00da_bdf0*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);

                Vec3_s00da_bdf0 dir;
                dir.x = cam->x - vec.x;
                dir.y = cam->y - vec.y;
                dir.z = cam->z - vec.z;
                Vec3_s00da_bdf0 n = normalized_safe(dir);

                self->MoveToPointAndFacingAtSpeed(2, &vec, &n,
                                                  DAT_01572070, DAT_0157206c);
                return true;
            }
        }

    case 6:
        if (self->AnimationFinished(0))
        {
            CTribe* t = self->GetTribe();
            beh->FUN_00ac7d10(DAT_01581298, 0, t);
            self->mCombat.PartialRepair(DAT_015812a0 * DAT_01581298);

            float f = self->FUN_00c0b9c0();
            self->FUN_00c0b9d0(DAT_0158129c * DAT_01581298 + f);

            st->mi08 = (st->mi10 >= 0) ? 1 : 0;
            self->SetCurrentToolEffect(0, -1);
        }

        if ((st->mi04 & 0xff) == 0)
        {
            float f = self->FUN_00c0b9c0();
            if (DAT_01687a00 <= f)
            {
                if (!self->FUN_00c0b770())
                    FUN_00cc8b10(self)->FUN_00cc5170();

                CTribe* t = self->GetTribe();
                Vec3_s00da_bdf0*  p = (Vec3_s00da_bdf0*)((Fn_p)VT(&t->m120, 0x2c))(&t->m120);
                self->MoveToPointAtSpeed(2, p, 7.5f, 10.0f);
                st->mi08 = 7;
                return true;
            }
        }
        else
        {
            if (self->FUN_00c0b770())
                self->FUN_00c0b9d0(DAT_01687a00);

            LayoutMgr_s00da_bdf0* mgr = FUN_00af13b0(self, 1, 0);
            if (mgr->FUN_00af0bd0())
                return true;

            if (!self->FUN_00c0b770())
                FUN_00cc8b10(self)->FUN_00cc5170();

            CTribe* t = self->GetTribe();
            Vec3_s00da_bdf0*  p = (Vec3_s00da_bdf0*)((Fn_p)VT(&t->m120, 0x2c))(&t->m120);
            self->MoveToPointAtSpeed(2, p, 7.5f, 10.0f);
            st->mi08 = 7;
            return true;
        }
        break;

    case 7:
        if (static_cast<CLoco&>(*self).IsNearGoal() || (self->m330 & 1) != 0)
            return FUN_00da6270(self, 0);
        break;
    }

    return true;
}

// @ 0x00dac580
void C580::FUN_00dac580()
{
    C580Obj* o = mp14;
    if (o != 0)
    {
        C580Ref* p = o->mp120;
        if (p == m04 && p != 0)
        {
            o->mp120 = 0;
            p->r04();
        }
    }

    C580Obj* o2 = mp14;
    if (o2 != 0)
    {
        mp14 = 0;
        ((C580Ref*)o2)->r04();
    }
}

// @ 0x00dac5d0
bool FUN_00dac5d0(C5d0Obj* p)
{
    if (p->mp64 != 0 && (p->mp90 == 0 || p->mp90->m08 != 0x2e81370))
    {
        _ReadWriteBarrier();
        if (p->mp64 != 0)
        {
            C05Result* r =
                (C05Result*)((C05Vt*)p->mp64)->a0c(0xd0036e08);
            if (r != 0 && r->mb5e != 0 && r->mfB84 > 0.0f)
                return 1;
        }
        return 0;
    }
    return 0;
}

// @ 0x00dac630
bool FUN_00dac630(Citizen_s00da_bdf0* self, int a2, int a3, int a4, int a5, St630* st)
{
    st->mb0 = 0;
    st->mi4 = -1;

    self->FUN_00c14750(0);

    CTribe* t = self->GetTribe();
    CTool*  o = (CTool*)((Fn_ac)VT(t, 0xac))(t);
    CTool34* p = &o->m34;

    float sp = ((Fn_f)VT(p, 0x74))(p);

    float tmp[3];
    Vec3_s00da_bdf0* dir = (Vec3_s00da_bdf0*)((Fn_p1)VT(p, 0x5c))(p, tmp);

    float dx = dir->x * sp;
    float dy = dir->y * sp;
    float dz = dir->z * sp;

    Vec3_s00da_bdf0* pos = (Vec3_s00da_bdf0*)((Fn_p)VT(p, 0x2c))(p);

    Vec3_s00da_bdf0 dst;
    dst.x = pos->x + dx;
    dst.y = pos->y + dy;
    dst.z = pos->z + dz;

    float f1 = ((Fn_f)VT(t, 0x60))(t);
    float f2 = ((Fn_f1)VT(t, 0x60))(t, f1);

    self->MoveToPointAtSpeed(2, &dst, f2, f1);

    st->mi8 = 0;
    return true;
}

// @ 0x00dac730
void FUN_00dac730(Citizen_s00da_bdf0* self, int a2, int a3, int a4, int a5, St730* st)
{
    self->FUN_00c0ba10();

    self->mB58 &= 0xfffff7ff;
    self->mpB54->mf80 = DAT_01485720;

    if (st->mb0 != 0)
    {
        if (self->GetTribe() != 0)
        {
            CTribe* t = self->GetTribe();
            CTool* o = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            if (o != 0)
            {
                CTribe* t2 = self->GetTribe();
                CTool* o2 = (CTool*)((Fn_ac)VT(t2, 0xac))(t2);
                int* q = &o2->m21c;
                (*q)--;
            }
        }
    }

    if (st->mi4 != -1)
    {
        self->GetTribe()->FUN_00c97d40(0xc, self);
    }

    self->m110 &= 0xffffff7f;

    CLoco&      loco = static_cast<CLoco&>(*self);
    Cb3d310Res* r    = (Cb3d310Res*)FUN_00b3d310_s00da_bdf0(&loco);
    r->FUN_00b453a0();
    _ReadWriteBarrier();
}

// @ 0x00dac7e0
bool FUN_00dac7e0(Citizen_s00da_bdf0* self, int a2, int a3, int a4, int a5, HiveState* st)
{
    switch (st->mi08)
    {
    case 0:
        if (static_cast<CLoco&>(*self).IsNearGoal())
            st->mi08 = 1;
        break;

    case 1:
        {
            CTribe* t = self->GetTribe();
            Vec3_s00da_bdf0 vec;
            t->FUN_00c979e0(&vec, 0xc, self);

            CLoco* loco = static_cast<CLoco*>(self);
            C41Obj* obj = loco->FUN_00c41ec0();
            bool far = true;
            if (obj->m5c != 0)
            {
                Vec3_s00da_bdf0* pp = obj->FUN_00c423c0();
                Vec3_s00da_bdf0  d;
                d.x = pp->x - vec.x;
                d.y = pp->y - vec.y;
                d.z = pp->z - vec.z;
                float dist2 = d.x * d.x + d.y * d.y + d.z * d.z;
                far = DAT_01572070 < dist2;
            }
            if (far)
            {
                float sc = ((Fn_f)VT(loco, 0x74))(loco);
                self->MoveToPointAtSpeed(2, &vec, sc * 4.0f, sc * 6.0f);
            }

            if (loco->IsNearGoal())
            {
                st->mi04 = t->FUN_00c97ca0(0xc, self);
                st->mi08 = 2;
                return true;
            }
        }
        break;

    case 2:
        {
            CTribe* t = self->GetTribe();
            CLoco*  loco = static_cast<CLoco*>(self);

            int  v = t->FUN_00c97c40(0xc, self);
            bool changed = (v != st->mi04);
            if (changed)
                st->mi04 = v;

            if (st->mi04 == 0)
            {
                if (changed)
                    goto movement;

                if (loco->IsNearGoal() || (self->m330 & 1) != 0)
                {
                    st->mi04 = -1;
                    t->FUN_00c97d40(0xc, self);
                    st->mi08 = 3;
                    return true;
                }
            }
            else if (changed)
            {
                goto movement;
            }
            break;

        movement:
            {
                CTribe* t2 = self->GetTribe();
                float s = ((Fn_f)VT(loco, 0x74))(loco);

                Vec3_s00da_bdf0 vec;
                t2->FUN_00c97b10(&vec, 0xc, self);
                self->MoveToPointAtSpeed(2, &vec, s + DAT_01572070, s + s);
                return true;
            }
        }

    case 3:
        {
            CLoco* loco = static_cast<CLoco*>(self);
            if (!loco->IsNearGoal())
                break;

            CLoco* lp = self ? static_cast<CLoco*>(self) : 0;
            Cb3d310Res* r = (Cb3d310Res*)FUN_00b3d310_s00da_bdf0(lp);
            r->FUN_00b45410();

            self->m110 |= 0x80;

            CTribe* t = self->GetTribe();
            CTool* tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            Vec3_s00da_bdf0*  p = (Vec3_s00da_bdf0*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);
            self->MoveToPointAtSpeed(2, p, DAT_01572070, DAT_0157206c);
            st->mi08 = 4;

            t = self->GetTribe();
            tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            Vec3_s00da_bdf0* toolp = (Vec3_s00da_bdf0*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);
            Vec3_s00da_bdf0* locop = (Vec3_s00da_bdf0*)((Fn_p)VT(loco, 0x2c))(loco);

            float dx = toolp->x - locop->x;
            float dy = toolp->y - locop->y;
            float dz = toolp->z - locop->z;
            st->mf0c = sqrtf(dx * dx + dy * dy + dz * dz);

            t = self->GetTribe();
            tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            float sc = ((Fn_f)VT(&tool->m34, 0x74))(&tool->m34);
            float d  = (st->mf0c - sc) + 1.0f;

            st->mf10 = 1.0f / ((d <= 1.0f) ? 1.0f : d);
            return true;
        }

    case 4:
        {
            CLoco* loco = static_cast<CLoco*>(self);

            if (loco->IsNearGoal())
            {
                st->mi08 = 5;
                ((Fn_v)VT(loco, 0xec))(loco);

                CTribe* t = self->GetTribe();
                CTool* tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
                int* q = &tool->m21c;
                (*q)++;

                st->mi00 = 1;
                st->mi08 = 5;
            }

            CTribe* t = self->GetTribe();
            CTool* tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            Vec3_s00da_bdf0* toolp = (Vec3_s00da_bdf0*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);
            Vec3_s00da_bdf0* locop = (Vec3_s00da_bdf0*)((Fn_p)VT(loco, 0x2c))(loco);

            float dx = locop->x - toolp->x;
            float dy = locop->y - toolp->y;
            float dz = locop->z - toolp->z;
            float d  = (st->mf0c - sqrtf(dx * dx + dy * dy + dz * dz)) * st->mf10;

            float a = (d >= 1.0f) ? 1.0f : d;
            float r = 1.0f - a;
            if (r >= 1.0f)
                r = 1.0f;

            self->mB58 |= 0x800;
            self->mpB54->mf80 = r;
            return true;
        }

    case 5:
        {
            LayoutMgr_s00da_bdf0* mgr = FUN_00af13b0(self, 2, 0);
            if (!mgr->FUN_00af0bd0())
            {
                st->mi00 = 0;

                CTribe* t = self->GetTribe();
                CTool* tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
                int* q = &tool->m21c;
                (*q)--;

                CLoco* loco = static_cast<CLoco*>(self);
                float s = ((Fn_f)VT(loco, 0x74))(loco);

                Vec3_s00da_bdf0 v;
                Vec3_s00da_bdf0* r = (Vec3_s00da_bdf0*)((Fn_p1)VT(t, 0xac))(t, &v);
                r->FUN_00c8ef20();

                self->MoveToPointAtSpeed(2, &v, s + s, s + s);
                st->mi08 = 6;
                return true;
            }
        }
        break;

    case 6:
        if (static_cast<CLoco&>(*self).IsNearGoal())
            return FUN_00da6270(self, 6);
        break;
    }

    return true;
}

// @ 0x00dacd40
namespace SP {
void FUN_00dacd40(cSPCreatureCitizen_s00da_cd40* c)
{
    Obj5a8* o = &c->mObj5a8;
    cTribe_s00da_cd40* tribe = c->GetTribe();
    if (!tribe->mbFlag556) {
        if (tribe->mTimer > 0.0f) {
            tribe->mTimer = 0.0f;
            o->FUN_00f924e0(o->GetFloat());
            o->FUN_00bfc460(0);
            c->vf90();
            tribe->FUN_00c95cc0(c);
        }
        c->mpEnv->mSub.FUN_00bc97b0();
        c->mFlagsB58 &= ~0x800u;
        c->mpAnim->mWeight = 1.0f;
        c->FUN_00c14750(1);
        c->mbF12f = true;
        FUN_00b3d310()->FUN_00b453a0(&c->mLoco);
        c->mLoco.mFlags50 &= ~0x80u;
        c->SetCurrentToolEffect(0x11, -1);
    }
}
}  // namespace SP

// @ 0x00dace20
namespace SP {
bool CHIEFTAIN_TOOL_INSPECT_Tick(cSPCreatureCitizen_s00da_cd40* c, int, int, int, int, ToolState* mem)
{
    cTribe_s00da_cd40* tribe = c->GetTribe();
    TribeTool* tool = tribe->GetToolOfType(mem->mToolType);
    if (!tool)
        return false;
    if (tool->mToolFlags > 0)
        return false;

    const Vec3_s00da_cd40* p = tool->mTool.GetPosition();
    float dx = p->x - mem->mToolPos.x;
    float dy = p->y - mem->mToolPos.y;
    float dz = p->z - mem->mToolPos.z;
    if (dx * dx + dy * dy + dz * dz > 1.0f)
        return false;

    switch (mem->mState) {
    case 0: {
        mem->mState = 1;
        float radius = tool->mTool.GetRadius() + c->mLoco.GetRadius();
        float* target = FUN_00c986d0(tribe, mem->mToolType, &mem->mAnim, c);
        if (mem->mAnim < 0)
            return false;
        const Vec3_s00da_cd40* tpos = tool->mTool.GetPosition();
        Vec3_s00da_cd40 diff;
        diff.x = target[0] - tpos->x;
        diff.y = target[1] - tpos->y;
        diff.z = target[2] - tpos->z;
        Vec3_s00da_cd40 dir;
        normalized_safe(&dir, &diff);
        float dist = radius + 0.1f;
        Vec3_s00da_cd40 goal(dir.x * dist, dir.y * dist, dir.z * dist);
        const Vec3_s00da_cd40* base = tool->mTool.GetPosition();
        Vec3_s00da_cd40 dest(base->x + goal.x, base->y + goal.y, base->z + goal.z);
        Vec3_s00da_cd40 facing(-dir.x, -dir.y, -dir.z);
        c->MoveToPointAndFacingAtSpeed(2, &dest, &facing, gMinSpeed, gMaxSpeed);
        break;
    }
    case 1:
        if (c->mLoco.IsNearGoal()) {
            unsigned anim = 0x4c70750 + RandomUint32Uniform(3);
            Vec3_s00da_cd40 out;
            FUN_00d9a4a0(&out, c, &tool->mTool);
            mem->mAnimId = c->PlayAnimationWithTarget(anim, &out, -1);
            mem->mState = 2;
            return true;
        }
        break;
    case 2:
        if (c->AnimationFinished(mem->mAnimId))
            return false;
        break;
    }
    return true;
}
}  // namespace SP

// @ 0x00dad0c0
namespace SP {
bool IDLE_VIGNETTE_Activate(cSPCreatureCitizen_s00da_cd40* c, int, int, int, int, int, VignetteMem* mem)
{
    c->mLoco.vfec();
    VignetteNode* node = (VignetteNode*)mem->mActive;
    if (!node) {
        cTribe_s00da_cd40* tribe = c->GetTribe();
        unsigned slot = (unsigned)mem->mSlot;
        if (slot >= (unsigned)((tribe->mpSlotsEnd - tribe->mpSlotsBegin) / 5))
            return false;
        TribeSlot* s = &tribe->mpSlotsBegin[slot];
        s->mbOccupied = true;

        Vec3_s00da_cd40 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &s->mPos);

        VignetteRange* range = FUN_00b3d4e0_s00da_cd40()->Find(mem->mTableKey, 0);
        VignetteDef* def = (VignetteDef*)((char*)range->mpBegin + mem->mVignetteIndex * 0x7b4);

        node = (VignetteNode*)FUN_00bc9b00_s00da_cd40()->FUN_00bcb0b0(0x55241ec, def->mKey, (void*)0x18eb4b7, "IdleVignette");
        int* fields = &node->mSlot;
        if (fields) {
            node->mSlot = -1;
            node->mHandle = -1;
        }

        Quat q;
        PlanetModel()->BuildSurfaceOrientation(&q, &surf);
        Vec3_s00da_cd40 dir;
        FUN_0059aed0(&dir, (const Quat*)0x169f408, &q);
        node->mHandle = FUN_00b3d4e0_s00da_cd40()->FUN_00bc65f0(def, &dir, &surf);
        node->mTimer = 20.0f;
        node->mSlot = slot;
    }
    c->mpEnv->FUN_00bcb480(node, c, 0, 0);
    bool ok = FUN_00b3d4e0_s00da_cd40()->FUN_00bc4900(node->mHandle, c, 0);
    c->d0c0(6, ok);
    return ok;
}
}  // namespace SP

// @ 0x00dad260
namespace SP {
void FUN_00dad260(cSPCreatureCitizen_s00da_cd40* c)
{
    VignetteNode* node = c->mpEnv->mpVignette;
    if (node) {
        FUN_00b3d4e0_s00da_cd40()->FUN_00bc52a0(node->mHandle, c);
        if (node->mState10 == 1) {
            cTribe_s00da_cd40* tribe = c->GetTribe();
            unsigned slot = (unsigned)node->mSlot;
            if (slot < (unsigned)(tribe->mpSlotsEnd - tribe->mpSlotsBegin))
                tribe->mpSlotsBegin[slot].mbOccupied = false;
            node->mSlot = 0;
        }
    }
    c->mLoco.vfec();
    c->FUN_00c14750(1);
    c->mpEnv->FUN_00bcb430();
    c->d0c0(6, 0);
}
}  // namespace SP

// @ 0x00dad320
namespace SP {
bool FUN_00dad320(cSPCreatureCitizen_s00da_cd40* c, int, int, int, int, int, int, float dt)
{
    VignetteNode* node = c->mpEnv->mpVignette;
    if (node->mHandle == -1)
        return false;
    VignetteMgr* mgr = FUN_00b3d4e0_s00da_cd40();
    if (mgr->FUN_00bc3db0(node->mHandle)) {
        node->mTimer = node->mTimer - dt;
        if (node->mTimer < 0.0f)
            return false;
    }
    return !mgr->FUN_00bc3df0(node->mHandle);
}
}  // namespace SP

// @ 0x00dad390
namespace SP {
unsigned TRIBE_DOMESTICATE_Tick(cSPCreatureCitizen_s00da_cd40* c, int, int, int, int, DomesticateState* mem)
{
    cSPCreatureCitizen_s00da_cd40* animal = (cSPCreatureCitizen_s00da_cd40*)FUN_00d99500(mem->mNoun);
    if (!animal)
        return FUN_00da6270(c, 0x19);

    switch (mem->mState) {
    case 0: {
        c->mpEnv->mSub.FUN_00bc97f0(4, 0, gFloatMax, c);
        c->FUN_00c14750(1);
        animal->mLoco.vfec();
        float radius = animal->mLoco.GetRadius() + c->mLoco.GetRadius();
        const Vec3_s00da_cd40* p = animal->mLoco.GetPosition();
        c->MoveToPointAtSpeed(2, p, radius + gMinSpeed, radius + gMaxSpeed);
        mem->mState = 1;
        return 1;
    }
    case 1: {
        if (!c->mLoco.IsNearGoal())
            return 1;
        const Vec3_s00da_cd40* here = c->mLoco.GetPosition();
        const Vec3_s00da_cd40* there = animal->mLoco.GetPosition();
        Vec3_s00da_cd40 diff(there->x - here->x, there->y - here->y, there->z - here->z);
        Vec3_s00da_cd40 dir;
        normalized_safe(&dir, &diff);
        Vec3_s00da_cd40 neg(-dir.x, -dir.y, -dir.z);
        c->MoveToPointAndFacingAtSpeed(2, c->mLoco.GetPosition(), &dir, 1.0f, 2.0f);
        animal->MoveToPointAndFacingAtSpeed(2, animal->mLoco.GetPosition(), &neg, 1.0f, 2.0f);
        c->FUN_00c14750(1);
        mem->mState = 2;
        return 1;
    }
    case 2: {
        if (!c->mLoco.IsNearGoal() || !animal->mLoco.IsNearGoal())
            return 1;
        mem->mAnimId = c->PlayAnimation(0x5654d97, 1, c->FUN_00c22820());
        mem->mAnimId2 = animal->InterruptAnimation(0x5bace5e, -1, 0);
        mem->mState = 3;
        return 1;
    }
    case 3: {
        int ev = -1;
        if (!c->WaitForAnimEventOrEnd(0x7d7502fc, &ev, 0, mem->mAnimId, 1))
            return 1;
        c->SetCurrentToolEffect(0xc, ev);
        mem->mAnimId = c->PlayAnimationWithTarget2(0x5654df6, animal->mLoco.GetPosition(), -1, -1);
        mem->mState = 4;
        return 1;
    }
    case 4: {
        if (!c->AnimationFinished(mem->mAnimId))
            return 1;
        mem->mAnimId = c->PlayAnimationWithTarget2(0x5654df7, animal->mLoco.GetPosition(), -1, -1);
        mem->mState = 5;
        int* pending = (int*)c->mpEnv->FirstPending();
        if (pending && *pending == 0x19)
            *(unsigned*)((char*)pending + 0x39) = (unsigned)mem;
        return 1;
    }
    case 5: {
        if (!c->FUN_00c25480(0xc, 0) || !c->AnimationFinished(mem->mAnimId))
            return 1;
        c->GetTribe();
        Corral* corral = c->GetTribe()->GetCorral();
        CorralVector* vec = &corral->mVec;
        const Vec3_s00da_cd40* apos = animal->mLoco.GetPosition();
        float radius = animal->mLoco.GetRadius() + vec->GetRadius() + 1.5f;
        Vec3_s00da_cd40 fbuf;
        const Vec3_s00da_cd40* facing = vec->GetFacing(&fbuf);
        Vec3_s00da_cd40 scaled(facing->x * radius, facing->y * radius, facing->z * radius);
        const Vec3_s00da_cd40* vpos = vec->GetPosition();
        Vec3_s00da_cd40 target(vpos->x - scaled.x, vpos->y - scaled.y, vpos->z - scaled.z);
        Vec3_s00da_cd40 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &target);
        animal->MoveToPointAndFacingAtSpeed(2, &surf, vec->GetFacing(&fbuf), 1.0f, 2.0f);
        if (((unsigned*)c->mpSpecies)[0x544 / 4] < ((unsigned*)animal->mpSpecies)[0x544 / 4])
            c->d0c0(6, 1);
        mem->mAnimId = c->InterruptAnimationWithTarget(0x5654df8, vec->GetFacing(&fbuf), -1, -1);
        mem->mState = 6;
        (void)apos;
        return 1;
    }
    case 6: {
        const Vec3_s00da_cd40* self = c->mLoco.GetPosition();
        float radius = animal->mLoco.GetRadius() + c->mLoco.GetRadius();
        void* goal = FUN_00c41ec0(&c->mLoco);
        if (*(int*)((char*)goal + 0x5c)) {
            const Vec3_s00da_cd40* mine = c->mLoco.GetPosition();
            const Vec3_s00da_cd40* theirs = (const Vec3_s00da_cd40*)FUN_00c423c0(goal);
            float dx = theirs->x - mine->x;
            float dy = theirs->y - mine->y;
            float dz = theirs->z - mine->z;
            float d = radius + 2.0f;
            if (d * d < dx * dx + dy * dy + dz * dz)
                goto near;
        }
        {
            float r = -(RandomFloatRange(0.0f, 1.0f) + radius);
            const Vec3_s00da_cd40* facing = c->mLoco.GetFacing();
            Vec3_s00da_cd40 off(facing->x * r, facing->y * r, facing->z * r);
            const Vec3_s00da_cd40* p = c->mLoco.GetPosition();
            Vec3_s00da_cd40 target(p->x + off.x, p->y + off.y, p->z + off.z);
            Vec3_s00da_cd40 surf;
            PlanetModel()->DirectionToSurfacePosition(&surf, &target);
            c->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        }
    near:
        if (!(animal->mLoco.IsNearGoal() || (animal->mFlags330 & 1))
            || !(c->mLoco.IsNearGoal() || (c->mFlags330 & 1)))
            return 1;
        c->GetTribe();
        CorralVector* vec = &c->GetTribe()->GetCorral()->mVec;
        float d2 = vec->GetRadius() - c->mLoco.GetRadius() * 2.0f;
        float keep = d2 > 0.0f ? d2 : 0.0f;
        Vec3_s00da_cd40 rnd;
        PlanetModel()->MakeRandomWorldPosition(&rnd, keep, 0.0f);
        animal->TryJumpToTarget(0, &rnd, (void*)0x169f3b8, 0.0f, 1);
        animal->MoveToPointAtSpeed(2, &rnd, 1.0f, 2.0f);
        animal->d0c0(6, 0);
        c->MoveToPointAtSpeed(2, self, 1.0f, 2.0f);
        mem->mAnimId = c->PlayAnimation(0x5654df9, 1, -1);
        mem->mState = 7;
        FUN_00da61e0(c, 0x19);
        return 1;
    }
    case 7: {
        if (!c->AnimationFinished(mem->mAnimId))
            return 1;
        mem->mAnimId = c->PlayAnimation(0x5654df4, 1, -1);
        mem->mState = 8;
        return 1;
    }
    case 8: {
        int ev = -1;
        if (!c->WaitForAnimEventOrEnd(0xbfa50b5a, &ev, 0, mem->mAnimId, 1))
            return 1;
        mem->mState = 0;
        return FUN_00da6270(c, 0x19);
    }
    }
    return 1;
}
}  // namespace SP

// @ 0x00dae980
uint8_t __cdecl FUN_00dae980(CC* self, int a1, int a2, int a3, int a4, int* a5)
{
    NodeState980* st = (NodeState980*)self->mpB4C->mp600;
    if (st->FUN_00a75010() != 0)
        return 0;

    if (self->IsLeader() && self->mC0.Slot22() != 0) {
        int32_t mode = st->mMode;
        if (mode == 0) {
            a5[1] = self->InterruptAnimation(0xb4eab72c, -1, 0);
            st->mMode = 1;
            return 1;
        }
        if (mode == 1) {
            if (self->AnimationFinished(a5[1])) {
                st->mMode = 2;
                return 1;
            }
            return 1;
        }
        if (mode == 2) {
            ((StimuliMgr_s00da_e980*)((char*)self->mpB4C + 8))->FUN_00bc97f0(0, 0x20, g_147c218, 0);
            return FUN_00da6270(self, 0x16);
        }
        return 1;
    }

    switch (*a5) {
    case 0:
        if (self->mC0.Slot22() == 0 && st->mFlag1ac == 0) {
            st->mFlag1ac = 1;
            int empire = NounManager()->GetPlayerEmpireOrMinus1();
            void* o1 = self->base.Slot19();
            float f1 = RelationshipManager()->CalculateRelationshipAbsolute(o1, (void*)(uint32_t)empire);
            RelationshipManager()->FUN_00d00780(f1);
            float d = g_1581368 - f1;
            if (d > 0.0f) {
                NounByTag(0x530cf07, d);
                int e2 = NounManager()->GetPlayerEmpireOrMinus1();
                void* o2 = self->base.Slot19();
                RelationshipManager()->RecordEvent(o2, (void*)(uint32_t)e2);
            }
            st->mpRef1a8.Assign(self->GetTribe());
            if (g_1581374 != 0) {
                TribeObj* tr = self->GetTribe();
                tr->m2cc = g_1581378;
                TribeObj* pt = (TribeObj*)NounManager()->SetGameDataOwner2();
                PtrList* l1 = self->GetTribe()->Slot36();
                for (int* p = l1->mpBegin; p != l1->mpEnd; ++p) {
                    CC* o = (CC*)*p;
                    FUN_00da63e0(o, pt);
                    ((StimuliMgr_s00da_e980*)((char*)o->mpB4C + 8))->FUN_00bc97f0(0, 0x400000, g_1486110, pt);
                }
                PtrList* l2 = pt->Slot36();
                for (int* p = l2->mpBegin; p != l2->mpEnd; ++p) {
                    CC* o = (CC*)*p;
                    FUN_00da63e0(o, self->GetTribe());
                    ((StimuliMgr_s00da_e980*)((char*)o->mpB4C + 8))->FUN_00bc97f0(0, 0x400000, g_1486110, self->GetTribe());
                }
            }
        }
        a5[1] = self->InterruptAnimation(0x54eacd7d, -1, 0);
        *a5 = 1;
        return 1;
    case 1:
        if (self->AnimationFinished(a5[1])) {
            a5[1] = self->InterruptAnimation(0x57e0105, -1, 0);
            *a5 = 2;
            return 1;
        }
        return 1;
    case 2:
        if (self->AnimationFinished(a5[1]))
            return 0;
        return 1;
    }
    return 1;
}

// @ 0x00daeca0
uint8_t __cdecl FUN_00daeca0(CC* self, int a1, int a2, int a3, int a4, Out* a5)
{
    int* p = (int*)self->mpB4C->FirstPending();
    if (p != 0 && *p == 0x16) {
        char* q = (char*)p + 0x39;
        uint16_t s = *(uint16_t*)(q + 0x12);
        int32_t* src;
        if (s == 0x0a || s == 0x10) {
            if ((*(uint8_t*)(q + 0x10) & 0x30) != 0)
                src = *(int32_t**)q;
            else
                src = (int32_t*)(s ? q : 0);
        } else {
            src = (int32_t*)0x15d1164;
        }
        int32_t v = *src;
        a5->f0 = v;
        a5->f4 = 0;
        a5->f8 = 0;
        a5->fC = 0;
        a5->f10 = -1;
        return (uint8_t)(self->base.Slot45(v) != 0 ? 1 : 0);
    }
    return 0;
}

// @ 0x00daed20
int SlotTable::FUN_00daed20(int idx)
{
    int* base = mpBase;
    uint32_t* p = (uint32_t*)((char*)base + idx * 0x250);
    uint32_t u = *p;
    do {
        if (u >> 0x1e & 1)
            return 0x3fffffff;
        u = p[0x94];
        p += 0x94;
        ++idx;
    } while (u >> 0x1f & 1);
    return idx;
}

// @ 0x00daeea0
void __stdcall FUN_00daeea0(Slot250* a, Slot250* b)
{
    for (; a < b; a = (Slot250*)((char*)a + 0x250)) {
        if ((((uint32_t)a->mFlags >> 31) & 1) == 0)
            a->mObj.Slot0(0);
    }
}

// @ 0x00daeee0
long double __cdecl FUN_00daeee0(CC* self, int a1, int a2, int a3, void* a4, uint8_t* a5)
{
    if (self->FUN_00c22dc0() != 9)
        return 0.0;

    uint32_t count = (uint32_t)self->base.Slot19();
    Vec3* pos = self->mC0.Slot11();
    void* best = 0;
    float prop = GetPropertyT((int)g_1581288, 0x9c37dc, g_13eecd8);
    float fMax = prop * prop;

    PtrList* list = self->mC0.FUN_00c420d0();
    for (int* p = list->mpBegin; p != list->mpEnd; ++p) {
        CC* c = (CC*)*p;
        GObj* o = (c != 0) ? c->base.Slot46(0xce9f6639) : 0;
        CC* cand = (CC*)FUN_00d99470(o);
        if (cand == 0)
            continue;
        if ((uint32_t)cand->base.Slot19() != count)
            continue;
        float f9 = ((Sub5*)&cand->m5a8)->Slot22f();
        if (!(cand->m5e0 < f9))
            continue;
        Vec3* cp = cand->mC0.Slot11();
        float dx = pos->x - cp->x;
        float dy = pos->y - cp->y;
        float dz = pos->z - cp->z;
        float dist = dx * dx + dy * dy + dz * dz;
        if (!(dist < fMax))
            continue;
        fMax = dist;
        best = cand;
    }
    if (best == 0)
        return 0.0;
    if (a4 != 0)
        FUN_00d997e0(a4);
    ((int*)a4)[1] = (int)(uint32_t)((char*)best + 0x5a8);
    *a5 = 1;
    return 1.0;
}

// @ 0x00daf270
void __cdecl FUN_00daf270(CC* self, int a1, int a2, int a3, int a4, State270* a5)
{
    if (a5->mp0 != 0) {
        GObj* p = self->m58.Slot10();
        if (p != 0) {
            int32_t x = a5->mp0->Slot7();
            if (p->Slot7() == x)
                self->m58.Slot13();
        }
    }
    GObj* p4 = a5->mp4;
    if (p4 != 0)
        p4->Slot5();
    if (a5->mp0 != 0)
        a5->mp0->Release();
}

// @ 0x00daf2e0
uint8_t __cdecl FUN_00daf2e0(CC* self, int a1, int a2, int a3, int a4, StateFlee* a5, int a6, float dt)
{
    if (a5->mTimer > 7.0f)
        return 0;
    a5->mTimer = a5->mTimer + dt;

    switch (a5->mMode) {
    case 0: {
        int iVar2 = ((StimuliMgr_s00da_e980*)((char*)self->mpB4C + 8))->PlayIdleAnimation(0, 0x8000);
        int id;
        if (iVar2 != 0 && *(int*)(iVar2 + 0xc) == 0x5f0abb4) {
            id = 0x5f0abb4;
        } else if (a4 == 1) {
            id = (int)RAND_1601760->Next(3) + 0x2481dc8;
        } else {
            id = 0x2c38d92;
        }
        self->InterruptAnimation(id, -1, 0);

        TribeObj* tribe = self->GetTribe();
        float radius = tribe->Slot24f();
        Vec3 wpos;
        if (tribe->m556 == 0) {
            float ang = self->mC0.Slot29f() + radius;
            MakeRandomWorldPosition(&wpos, tribe->m120.Slot11(), radius, ang);
        } else {
            Vec3* pfVar4 = self->mC0.Slot11();
            Vec3* pfVar5 = tribe->m120.Slot11();
            Vec3 dir;
            dir.x = pfVar4->x - pfVar5->x;
            dir.y = pfVar4->y - pfVar5->y;
            dir.z = pfVar4->z - pfVar5->z;
            Vec3 nrm;
            normalized_safe(&nrm, &dir);

            float ang = RandomFloatRange(-1.4f, 1.4f);
            Vec3 axis;
            normalized_safe(&axis, pfVar4);

            float s = (float)sin((double)ang * 0.5);
            float c = (float)cos((double)ang * 0.5);

            Vec3 quat[2];                    // {nrm*s, c}
            quat[0].x = nrm.x * s;
            quat[0].y = nrm.y * s;
            quat[0].z = nrm.z * s;
            quat[1].x = c;

            Vec3 rot;
            FUN_0059aed0(&rot, &nrm, (Vec3*)quat);
            (void)axis;

            Vec3 dirpos;
            dirpos.x = pfVar4->x + rot.x * radius;
            dirpos.y = pfVar4->y + rot.y * radius;
            dirpos.z = pfVar4->z + rot.z * radius;
            DirectionToSurfacePosition(&wpos, &dirpos);
        }
        self->MoveToPointAtSpeed(3, &wpos, 1.0f, g_1470f1c);

        void* cont = self->m34.FUN_00cee330();
        if (cont != 0) {
            Container* g = (Container*)FUN_00b3d2b0_s00da_e980();
            void* holder = g->getContainer();
            Container* g2 = (Container*)FUN_00b3d2b0_s00da_e980();
            g2->FUN_00ac7de0(cont, holder);
        }
        a5->mMode = 1;
        break;
    }
    case 1:
        if (self->mC0.IsNearGoal() != 0) {
            if (a5->mFlag8 == 0)
                return 0;
            a5->mMode = 0;
            return 1;
        }
        break;
    }
    return 1;
}

// @ 0x00daf620
bool __cdecl TRIBE_COWER_Activate(CC* self, int a1, int a2, int a3, int a4, ActState* a5, A6* a6)
{
    if (a5 != 0)
        a5->mp0 = 0;
    GObj* m = a6->mp4;
    GObj* o;
    if (m != 0)
        o = m->Slot23(0xb033b403);
    else
        o = 0;
    GObj* old = a5->mp0;
    if (o != old) {
        if (o != 0)
            o->Slot0();
        a5->mp0 = o;
        if (old != 0)
            old->Release();
    }
    float f = (float)a6->m18;
    a5->mf4 = f * f;
    self->InterruptAnimation(0x2481dce, -1, 0);
    return a5->mp0 != 0;
}

// @ 0x00daf6b0
void __cdecl FUN_00daf6b0(CC* self, int a1, int a2, int a3, int a4, void** p)
{
    self->Func_c14750(0);
    if (p != 0 && *p != 0)
        ((GObj*)*p)->Release();
}

// @ 0x00daf6e0
uint8_t __cdecl FUN_00daf6e0(CC* self, int a1, int a2, int a3, int a4, GObj** a5, A6* a6)
{
    if (a5 != 0)
        *a5 = 0;
    GObj* m = a6->mp4;
    GObj* o;
    if (m != 0)
        o = m->Slot23(0xce9f6639);
    else
        o = 0;
    GObj* old = *a5;
    if (o != old) {
        if (o != 0)
            o->Slot0();
        *a5 = o;
        if (old != 0)
            old->Release();
    }
    if (*a5 != 0) {
        self->RebuildCitizenOrderListDefault();
        GObj* q = *a5;
        void* arg = (q != 0) ? (void*)((char*)q + 0x5a8) : 0;
        self->base.Slot33(arg, 1, 4);
        return 1;
    }
    return (uint8_t)FUN_00da6270(self, 5);
}

// @ 0x00daf780
void __cdecl FUN_00daf780(CC* self, int a1, int a2, int a3, int a4, State780* a5)
{
    GObj* o = a5->mp0;
    if (o != 0)
        o->Func_c17350(0x562d214, 0);
    self->base.Slot33(0, 0, 0);
    self->mC0.Slot59();
    if (self->mByteB5e == 0)
        self->Func_c14750(0);
    GObj* o2 = a5->mp0;
    if (o2 != 0)
        o2->Release();
}

// @ 0x00daf7f0
void __cdecl FUN_00daf7f0(CC* self, int a1, int a2, int a3, int a4, S5* a5)
{
    if (a5->mb04 != 0)
        self->PlayAnimation(0x2796b28, 1, -1);
    GObj* o = a5->mp0c;
    if (o != 0)
        o->Release();
}

// @ 0x00dafc00
void FUN_00dafc00(cCreature* a1, void* a2, void* a3, void* a4, void* a5, GetState* a6)
{
    a1->FUN_00c14750(a1->mLoco_c0.pv62() == 0);
    a1->pv33(0, 0, 0);
    cTribe_s00da_f820* t = a1->GetTribe();
    if (t != 0 && a6->m18 >= 0 && a6->m00.mpRef != 0)
        t->FindSpot(a6->m10, a6->m18);
    if (a6 != 0 && a6->m00.mpRef != 0)
        a6->m00.mpRef->pv1();
}

// @ 0x00dafc80
char FUN_00dafc80(cCreature* a1, void* a2, void* a3, void* a4, void* a5, CharState* a6, A7Obj* a7)
{
    if (a6 != 0)
        a6->m04.mpRef = 0;
    void* play = a1->mB4c->mAnim.Play(0x40, 0);
    a6->m00 = 2;
    RefAssign((void**)&a6->m04.mpRef, FUN_00d998d0(play, 0x116d858));
    a6->m18 = -1;
    if (a7 != 0)
    {
        cTribe_s00da_f820* o = a7->m08;
        IWin* nb = o != 0 ? o->pv3(0x116d858) : (IWin*)0;
        RefAssign((void**)&a6->m04.mpRef, nb);
    }
    ((cTribe_s00da_f820*)a6->m04.mpRef)->FUN_00c9d010();
    Vector3* p = ((cTribe_s00da_f820*)a6->m04.mpRef)->m34.pv11();
    a6->m08 = *p;
    a6->m14 = 0;
    a1->pv33(a6->m04.mpRef != 0 ? (void*)&((cTribe_s00da_f820*)a6->m04.mpRef)->m120 : 0, 1, 0);
    a1->FUN_00c14750(1);
    return 1;
}

// @ 0x00dafd90
void FUN_00dafd90(cCreature* a1, void* a2, void* a3, void* a4, void* a5, DeactState* a6)
{
    a1->FUN_00c14750(0);
    a1->FUN_00c17350(0x55559ef, 0);
    a1->pv33(0, 0, 0);
    if (a6->m04.mpRef != 0)
        ((cTribe_s00da_f820*)a6->m04.mpRef)->FUN_00c9d020();
    if (a6->m14 != 0 && FUN_00b5b800() == &DAT_01654c02 && a1->mLoco_c0.pv22() != 0)
    {
        if (((cTribeModeStrategy*)FUN_00cd3440(0x7d7315c8))->FUN_00b6fa60() != 0)
            ((cTribeModeStrategy*)FUN_00cd40b0(0x7d7315c8))->FUN_00cd6980();
    }
    cTribe_s00da_f820* t = a1->GetTribe();
    if (t != 0 && a6->m18 >= 0)
        t->FindSpot(((cTribe_s00da_f820*)a6->m04.mpRef)->pv22(), a6->m18);
    cTribe_s00da_f820* s = (cTribe_s00da_f820*)a6->m04.mpRef;
    if (s != 0)
        s->pv1();
}

// @ 0x00db2060
char FUN_00db2060(void *pCreature, TaskCtx *pCtx)
{
    void *pAnimMgr = (char *)*(void **)((char *)pCreature + 0xb4c) + 8;
    void *pPlay = PlayIdleAnimation(pAnimMgr, 0x10000, 0);
    if (pPlay == 0)
        return 0;

    char isVariantA = (*(int *)((char *)pPlay + 0xc) == 1);
    pCtx->mFlag1c = isVariantA;
    u32 animA = *(u32 *)((char *)pPlay + 0x14);
    pCtx->mState = animA;
    pCtx->mState = *(int *)((char *)pPlay + 0x18);

    u32 chosen;
    if (isVariantA != 0) {
        InterruptAnimation(pCreature, animA, 0xffffffff, 0);
        chosen = *(u32 *)((char *)pPlay + 0x18);
    } else {
        chosen = 0x2481e14;
    }
    PlayAnimation(pCreature, chosen, 1, 0xffffffff);

    char buf[0x74];
    *(float *)(buf + 0x54) = *(float *)0x0169f3b8;
    *(float *)(buf + 0x58) = *(float *)0x0169f3bc;
    *(float *)(buf + 0x5c) = *(float *)0x0169f3c0;
    *(float *)(buf + 0x60) = 1.0f;
    *(float *)(buf + 0x24) = *(float *)0x0169f414;
    *(float *)(buf + 0x28) = *(float *)0x0169f418;
    *(float *)(buf + 0x2c) = *(float *)0x0169f41c;
    *(float *)(buf + 0x30) = *(float *)0x0169f420;
    *(float *)(buf + 0x34) = *(float *)0x0169f424;
    *(float *)(buf + 0x38) = *(float *)0x0169f428;
    *(float *)(buf + 0x10) = *(float *)0x1470f1c;
    *(float *)(buf + 0x6c) = *(float *)0x13ec4b4;
    *(float *)(buf + 0x40) = *(float *)0x0169f42c;
    *(float *)(buf + 0x44) = *(float *)0x0169f430;
    *(float *)(buf + 0x48) = *(float *)0x0169f434;
    *(u32 *)(buf + 0x0c) = 0;
    *(u32 *)(buf + 0x14) = 0;
    *(u32 *)(buf + 0x18) = 0;
    *(u32 *)(buf + 0x34) = 0;
    buf[0x5c] = 0;
    *(float *)(buf + 0x60) = 0.0f;
    *(float *)(buf + 0x64) = 0.0f;
    *(float *)(buf + 0x68) = 0.0f;
    *(u32 *)(buf + 0x6c) = 0;
    *(float *)(buf + 0x78) = *(float *)0x147c218;
    *(float *)(buf + 0x7c) = 0.0f;
    *(u32 *)(buf + 0x80) = 0;

    void *pSys = VS((char *)pCreature + 0xc0, 0xdc);
    ((F1p)pSys)((char *)pCreature + 0xc0, buf);

    void *pArr = *(void **)(buf + 0x0c);
    if (pArr != 0 && *(int *)((char *)pArr - 4) != 0)
        operator_delete_array(pArr);
    return 1;
}

// @ 0x00db21b0
char FUN_00db21b0(void *pCreature, u32 a2, u32 a3, u32 a4, u32 a5, TaskCtx *pCtx, void *pTask, u32 a8, u32 a9)
{
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a8; (void)a9;
    if (pCtx != 0) {
        pCtx->mpRefA = 0;
        pCtx->mpRefB = 0;
        pCtx->mpRefC = 0;
    }

    void *pAnimMgr = (char *)*(void **)((char *)pCreature + 0xb4c) + 8;
    void *pPlay = PlayIdleAnimation(pAnimMgr, 0x1000000, 0);
    void *pRef1 = pPlay;
    pCtx->mState = 1;

    RefStore(&pCtx->mpRefB, FUN_00d998d0(pPlay, 0x116d858));
    RefStore(&pCtx->mpRefA, FUN_00d998d0(pPlay, 0xee02c7));
    void *pRef3 = FUN_00d998d0(pPlay, 0x4f396a66);

    if (pTask != 0) {
        void *pOwner = *(void **)((char *)pTask + 8);
        if (pOwner == 0)
            RefStore(&pCtx->mpRefB, 0);
        else
            RefStore(&pCtx->mpRefB, ((F1u_p)VS(pOwner, 0xc))(pOwner, 0x116d858));

        pOwner = *(void **)((char *)pTask + 8);
        if (pOwner == 0)
            RefStore(&pCtx->mpRefA, 0);
        else
            RefStore(&pCtx->mpRefA, ((F1u_p)VS(pOwner, 0xc))(pOwner, 0xee02c7));
    }

    if (pCtx->mpRefB == 0 && pCtx->mpRefA == 0 && pRef3 != 0) {
        void *pWin = vc_p(pRef3, 0xac);
        RefStore(&pCtx->mpRefA, pWin);
    }

    void *pUse;
    if (pCtx->mpRefB != 0) {
        RefStore(&pCtx->mpRefC, FUN_00c9d9e0());
        pCtx->mFlag1c = 1;
        pUse = (pCtx->mpRefB != 0) ? (char *)pCtx->mpRefB + 0x120 : 0;
    } else {
        pCtx->mFlag1c = 0;
        if (pCtx->mpRefA == 0)
            return 0;
        void *pOuter = ((F0p)VS(pCtx->mpRefA, 0x58))(pCtx->mpRefA);
        RefStore(&pCtx->mpRefC, pOuter);
        pUse = (pCtx->mpRefA != 0) ? (char *)pCtx->mpRefA + 0x120 : 0;
    }

    ((F3p)VS(pCreature, 0x84))(pCreature, pUse, (void *)1, (int)3);

    void *pPos = ((F0p)VS((char *)pUse + 0x34, 0x2c))((char *)pUse + 0x34);
    pCtx->mPosX = *(float *)pPos;
    pCtx->mPosY = *(float *)((char *)pPos + 4);
    pCtx->mPosZ = *(float *)((char *)pPos + 8);
    pCtx->mSpotIndex = -1;
    pCtx->mTimer = 0.0f;
    pCtx->mFlag1d = 0;
    return 1;
}

// @ 0x00db2410
void FUN_00db2410(void *pCreature, u32 a2, u32 a3, u32 a4, u32 a5, TaskCtx *pCtx)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    FUN_00c14750(pCreature, 0);
    ((F3p)VS(pCreature, 0x84))(pCreature, 0, 0, 0);

    if (pCtx->mState == 5) {
        if (pCtx->mFlag1c)
            FUN_00c9cf90(pCtx->mpRefB, 0);
        else
            FUN_00c9bef0(pCtx->mpRefA, 0);
    }

    if (pCtx->mSpotIndex >= 0) {
        if (pCtx->mFlag1c) {
            u32 id = (u32)((F0p)VS(pCtx->mpRefB, 0x58))(pCtx->mpRefB);
            FindSpot(pCtx->mpRefC, id, pCtx->mSpotIndex);
        } else {
            FindSpot(pCtx->mpRefC, 0xc, pCtx->mSpotIndex);
        }
    }

    if (pCtx->mpRefC != 0)
        vc_v(pCtx->mpRefC, 4);
    if (pCtx->mpRefB != 0)
        vc_v(pCtx->mpRefB, 4);
    if (pCtx->mpRefA != 0)
        vc_v(pCtx->mpRefA, 4);
}

// @ 0x00db24c0
char SP__TRIBE_REPAIR_Tick(void *pCreature, TaskCtx *pCtx, float dt)
{
    if (pCtx->mpRefB == 0 && pCtx->mpRefA == 0) {
        FUN_00da6270_s00db_2060(pCreature, 0x18);
        return 1;
    }
    float f0c = (float)(int)*(u32 *)&dt;
    (void)f0c;
    pCtx->mTimer = pCtx->mTimer - dt;

    float tPosX, tPosY, tPosZ, tRadius;
    void *pActive;

    if (pCtx->mFlag1c) {
        void *pObj = pCtx->mpRefB;
        void *pPos = ((F0p)VS((char *)pObj + 0x34, 0x2c))((char *)pObj + 0x34);
        tPosX = *(float *)pPos;
        tPosY = *(float *)((char *)pPos + 4);
        tPosZ = *(float *)((char *)pPos + 8);
        tRadius = ((float (__thiscall *)(void *))VS((char *)pObj + 0x34, 0x74))((char *)pObj + 0x34);
        pActive = (pObj != 0) ? ((F0p)VS(pObj, 0x58))(pObj) : 0;
    } else {
        void *pObj = pCtx->mpRefA;
        void *pPos = ((F0p)VS((char *)pObj + 0x34, 0x2c))((char *)pObj + 0x34);
        tPosX = *(float *)pPos;
        tPosY = *(float *)((char *)pPos + 4);
        tPosZ = *(float *)((char *)pPos + 8);
        tRadius = ((float (__thiscall *)(void *))VS((char *)pObj + 0x34, 0x74))((char *)pObj + 0x34);
        pActive = (pObj != 0) ? (char *)pObj + 0x120 : 0;
    }

    float dx = tPosX - pCtx->mPosX;
    float dy = tPosY - pCtx->mPosY;
    float dz = tPosZ - pCtx->mPosZ;
    if (dx * dx + dy * dy + dz * dz > 1.0f)
        return 0;

    float someRadius = FUN_00bfc490_s00db_2060(pActive);
    char bl = (FUN_0104bdb0() <= someRadius);
    void *pLoco = (char *)pCreature + 0xc0;
    float locoR = ((float (__thiscall *)(void *))VS(pLoco, 0x74))(pLoco);
    float reach = (locoR + tRadius) + 12.0f;
    float reachSq = reach * reach;

    switch (pCtx->mState - 1) {
    case 0: {
        FUN_00c25480(pCreature, (!bl) + 0x13, 0);
        void *pInfo = FUN_00c41ec0_s00db_2060((char *)pCreature + 0xc0);
        char doMove = (*(int *)((char *)pInfo + 0x5c) == 0);
        if (!doMove) {
            float *pAim = (float *)FUN_00c423c0_s00db_2060(pInfo);
            float ax = pAim[0] - tPosX;
            float ay = pAim[1] - tPosY;
            float az = pAim[2] - tPosZ;
            if (ax * ax + ay * ay + az * az > *(float *)0x1572070)
                doMove = 1;
        }
        if (doMove) {
            float spd1 = *(float *)0x1470f1c;
            MoveToPointAtSpeed(pCreature, 2, (void *)&tPosX, 1.0f, spd1);
        }
        void *pPos2 = ((F0p)VS(pLoco, 0x2c))(pLoco);
        float bx = *(float *)pPos2 - tPosX;
        float by = *(float *)((char *)pPos2 + 4) - tPosY;
        float bz = *(float *)((char *)pPos2 + 8) - tPosZ;
        if (bx * bx + by * by + bz * bz < reachSq)
            pCtx->mState = 2;
        break;
    }
    case 1: {
        FUN_00c25480(pCreature, (!bl) + 0x13, 0);
        float *pSpot = (float *)FUN_00c986d0_s00db_2060(pActive, &pCtx->mSpotIndex, pCreature);
        if (pCtx->mSpotIndex < 0) {
            FUN_00da6270_s00db_2060(pCreature, 0x18);
            return 1;
        }
        float locoR2 = ((float (__thiscall *)(void *))VS(pLoco, 0x74))(pLoco);
        float aimDist = (locoR2 + tRadius) + 0.1f;
        float dirX = pSpot[0] - tPosX;
        float dirY = pSpot[1] - tPosY;
        float dirZ = pSpot[2] - tPosZ;
        float nrm[3];
        normalized_safe_s00db_2060(nrm, &dirX);
        float goalX = nrm[0] * aimDist + tPosX;
        float goalY = nrm[1] * aimDist + tPosY;
        float goalZ = nrm[2] * aimDist + tPosZ;
        float faceX = -nrm[0];
        float faceY = -nrm[1];
        float faceZ = -nrm[2];
        float p1 = *(float *)0x157206c;
        float p2 = *(float *)0x1572070;
        MoveToPointAndFacing(pCreature, 2, &goalX, &faceX, p2, p1);
        pCtx->mState = 3;
        return 1;
    }
    case 2: {
        char ok = FUN_00c25480(pCreature, (!bl) + 0x13, 0);
        if (ok) {
            pCtx->mFlag1d = bl;
            if (IsNearGoal(pLoco)
                && AnimationFinished(pCreature, 0)
                && !CCM_e0c0(pCreature, 0x562bd84)
                && !CCM_e0c0(pCreature, 0x563e05c)) {
                ((F0v)VS(pLoco, 0xec))(pLoco);
                if (pCtx->mFlag1d)
                    PlayAnimation(pCreature, 0x563e05c, 1, 0xffffffff);
                else {
                    PlayAnimation(pCreature, 0x562bd7f, 1, 0xffffffff);
                    PlayAnimation(pCreature, 0x562bd84, 1, 0xffffffff);
                }
                if (pCtx->mFlag1c)
                    FUN_00c9cf90(pCtx->mpRefB, 1);
                else
                    FUN_00c9bef0(pCtx->mpRefA, 1);
                pCtx->mState = 5;
                return 1;
            }
        }
        break;
    }
    case 3: {
        if (AnimationFinished(pCreature, 0)) {
            float locoR3 = ((float (__thiscall *)(void *))VS(pLoco, 0x74))(pLoco);
            float spawnDist = (locoR3 + tRadius) + 4.0f;
            ((F3p)VS(pCreature, 0x84))(pCreature, 0, 0, 0);
            float distIn[4];
            distIn[0] = 1.0f;
            distIn[1] = spawnDist + 2.0f;
            distIn[2] = 1.0f;
            distIn[3] = 2.0f;
            float rotOut[3];
            float rotIn[3];
            rotIn[0] = 0.0f;
            rotIn[1] = 0.0f;
            rotIn[2] = 0.0f;
            void *pModel = FUN_00b3d350(rotOut, rotIn);
            void *pWorld = SP__cPlanetModel__MakeRandomWorldPosition(pModel, rotOut, rotIn,
                                                                     distIn[1], 2.0f);
            char navGoal[0x80];
            cNavigationGoal__InitAt(navGoal, pWorld);
            void *pGoal = ((F0p)VS(pLoco, 0xdc))(pLoco);
            FUN_007a41a0(navGoal);
            CCB_cff0(pCreature, 2);
            FindSpot(pActive, pCtx->mSpotIndex, 0);
            pCtx->mSpotIndex = -1;
            FUN_00da6270_s00db_2060(pCreature, 0x18);
            return 1;
        }
        break;
    }
    case 4: {
        if (pCtx->mFlag1d && !CCM_e0c0(pCreature, 0x563e05c))
            PlayAnimation(pCreature, 0x563e05c, 1, 0xffffffff);
        if (bl != pCtx->mFlag1d) {
            if (pCtx->mFlag1c)
                FUN_00c9cf90(pCtx->mpRefB, 0);
            else
                FUN_00c9bef0(pCtx->mpRefA, 0);
            if (!pCtx->mFlag1d)
                PlayAnimation(pCreature, 0x562bd89, 1, 0xffffffff);
            pCtx->mState = 3;
        }
        float f = FUN_00bfc490_s00db_2060(pActive);
        if (f != 1.0f && pActive && *(float *)((char *)pActive + 0x38) > 0.0f) {
            float a = ((float (__thiscall *)(void *))VS(pActive, 0x58))(pActive);
            float b = *(float *)((char *)pActive + 0x38);
            float c = ((float (__thiscall *)(void *))VS(pActive, 0x58))(pActive);
            float v = (c * *(float *)0x1581284) * dt + b;
            float *pMin = (a <= v) ? &a : &v;
            FUN_00f924e0(pActive, *pMin);
            return 1;
        }
        if (pCtx->mFlag1c)
            FUN_00c9cf90(pCtx->mpRefB, 0);
        else
            FUN_00c9bef0(pCtx->mpRefA, 0);
        pCtx->mState = 4;
        return 1;
    }
    }
    return 1;
}

// @ 0x00db2c00
void FUN_00db2c00(void *pThis)
{
    void **pIt = *(void ***)((char *)pThis + 0x14);
    void **pEnd = *(void ***)((char *)pThis + 0x18);
    if (pIt == pEnd)
        return;

    do {
        void *pObj = *pIt;
        u32 key = *(u32 *)((char *)pObj + 0x58);
        u32 effectId = 0;
        if (key == 0x29c388a)
            effectId = *(u32 *)0x0159d564;
        else if (key == 0x3a8be428)
            effectId = *(u32 *)0x0159d568;
        else if (key == 0x6d60a1cc)
            effectId = *(u32 *)0x0159d56c;

        void *pRef = 0;
        void *pMgr = SP__EffectsManager();
        char ok = ((char (__thiscall *)(void *, u32, int, void **))VS(pMgr, 0x2c))(pMgr, effectId, 0, &pRef);
        if (ok) {
            EffectBlock blk;
            blk.mPosX = *(float *)0x0169f438;
            blk.mPosY = *(float *)0x0169f43c;
            blk.mPosZ = *(float *)0x0169f440;
            blk.mOne = 1.0f;
            blk.mMat0 = *(float *)0x0169f414;
            blk.mMat1 = *(float *)0x0169f418;
            blk.mMat2 = *(float *)0x0169f41c;
            blk.mMat3 = *(float *)0x0169f420;
            blk.mMat4 = *(float *)0x0169f424;
            blk.mMat5 = *(float *)0x0169f428;
            blk.mMat6 = *(float *)0x0169f42c;
            blk.mMat7 = *(float *)0x0169f430;
            blk.mMat8 = *(float *)0x0169f434;
            blk.mCount = 0;
            blk.mFlags = 0;
            blk.mMat9 = *(float *)0x0169f438;
            blk.mPad4c = *(u32 *)0x0169f43c;

            float base[3];
            FUN_00b02b90(base, 0);

            float px = *(float *)((char *)pObj + 0x10);
            float py = *(float *)((char *)pObj + 0x14);
            float pz = *(float *)((char *)pObj + 0x18);
            float dx = px - base[0];
            float dy = py - base[1];
            float dz = pz - base[2];
            float dist = sqrtf(dz * dz + dy * dy + dx * dx);
            float invLen = 1.0f / sqrtf(px * px + py * py + pz * pz + 1e-08f);
            float fx = px + (px * invLen) * dist;
            float fy = py + (py * invLen) * dist;
            float fz = pz + (pz * invLen) * dist;

            blk.mPosX = fx;
            blk.mPosY = fy;
            blk.mPosZ = fz;
            for (int k = 0; k < 9; k++)
                blk.mBody[k] = *(u32 *)((char *)pObj + 0x20 + k * 4);
            blk.mCount += 2;
            blk.mFlags |= 4;
            blk.mFlags |= 2;
            blk.mPosX = fx;
            blk.mPosY = fy;
            blk.mPosZ = fz;
            ((F1p)VS(pRef, 0x18))(pRef, &blk.mFlags);
            ((F1u)VS(pRef, 8))(pRef, 0);
        }
        if (pRef != 0)
            vc_v(pRef, 4);
        pIt++;
    } while (pIt != *(void ***)((char *)pThis + 0x18));
}

// @ 0x00db2f10
char FUN_00db2f10(void *pObj, u32 a2, u32 a3, u32 a4, u32 a5, TaskCtx *pCtx)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    if (pCtx != 0)
        pCtx->mpRefC = 0;

    void *pOrder = FUN_00bca2c0(*(void **)((char *)pObj + 0xb4c));
    if (pOrder == 0)
        return 0;
    if (*(int *)pOrder != 0x16)
        return 0;

    char *pData = (char *)pOrder + 0x39;
    u16 kind = *(u16 *)(pData + 0x12);
    void *pKeyObj;
    if (kind == 0xa || kind == 0x10) {
        if (pData[0x10] & 0x30)
            pKeyObj = *(void **)pData;
        else
            pKeyObj = (kind != 0) ? (void *)pData : 0;
    } else {
        pKeyObj = (void *)0x015d1164;
    }

    u32 key = *(u32 *)pKeyObj;
    pCtx->mState = key;
    pCtx->mpRefA = 0;
    pCtx->mpRefB = 0;

    int found = ((F1i_r)VS(pObj, 0xb4))(pObj, key);
    return (char)(found != 0);
}

// @ 0x00db2fa0
void FUN_00db2fa0(TaskCtx *p1, u32 a2, u32 a3, u32 a4, u32 a5, TaskCtx *pCtx)
{
    (void)p1; (void)a2; (void)a3; (void)a4; (void)a5;
    if (pCtx->mpRefC != 0) {
        void *p = pCtx->mpRefC;
        pCtx->mpRefC = 0;
        vc_v(p, 4);
    }
    if (pCtx != 0 && pCtx->mpRefC != 0)
        vc_v(pCtx->mpRefC, 4);
}

// @ 0x00db2fd0
char FUN_00db2fd0(cSPCreatureBase* creature, void* a2, void* a3, void* a4, void* a5, REACT_State* state)
{
    switch (state->mPhase_04)
    {
    case 0:
    {
        creature->FUN_00c196a0(state->mpObj_00, 1, 0);
        FUN_00da61e0(creature, 0x16);
        creature->pv45(state->mpObj_00);
        state->mAnim_08 = (int)creature->PlayAnimation(0x60db980, 1, -1);
        state->mPhase_04 = 1;
        break;
    }
    case 1:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0xe95450e, &out, 0, state->mAnim_08, 1))
        {
            creature->SetCurrentToolEffect(0, out);
            state->mPhase_04 = 2;
            return 1;
        }
        break;
    }
    case 2:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0x81d12704, &out, 0, state->mAnim_08, 1))
        {
            IWin_s00db_2fd0* text = NounManager_s00db_2fd0()->FUN_00daed70();
            state->mText_0c = text;
            IWin_s00db_2fd0* sub = (IWin_s00db_2fd0*)((char*)text + 0x34);
            IWin_s00db_2fd0* loco = (IWin_s00db_2fd0*)&creature->mLoco_c0;

            float t = (float)loco->pv28();
            t = t + (float)sub->pv28();

            Vector3f probe;
            float* dir = (float*)loco->pv23(&probe.x);
            Vector3f off;
            off.x = dir[0] * t;
            off.y = dir[1] * t;
            off.z = dir[2] * t;

            float* base = (float*)loco->pv11();
            Vector3f vec;
            vec.x = off.x + base[0];
            vec.y = off.y + base[1];
            vec.z = off.z + base[2];

            text->FUN_00bcb960(0);
            sub->pv14(&vec);
            sub->pv33();
            state->mPhase_04 = 3;
            return 1;
        }
        break;
    }
    case 3:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0xbfa50b5a, &out, 0, state->mAnim_08, 1))
        {
            IWin_s00db_2fd0* text = state->mText_0c.mpRef;
            text->FUN_00bcb960(1);
            ((IWin_s00db_2fd0*)((char*)text + 0x34))->pv33();
            state->mPhase_04 = 4;
            return 1;
        }
        break;
    }
    case 4:
    {
        if (creature->AnimationFinished(state->mAnim_08))
        {
            void* a = creature->FUN_00c22820();
            state->mAnim_08 = (int)creature->PlayAnimation(0x2c39200, 1, (int)a);
            state->mPhase_04 = 5;
            return 1;
        }
        break;
    }
    case 5:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0x7d7502fc, &out, 0, state->mAnim_08, 1))
        {
            creature->FUN_00c26310(out);
            state->mPhase_04 = 6;
            return 1;
        }
        break;
    }
    case 6:
    {
        if (creature->AnimationFinished(state->mAnim_08))
        {
            IWin_s00db_2fd0* text = state->mText_0c.mpRef;
            text->FUN_00bcb960(2);
            text->FUN_00bcc010();
            FUN_00da6240(creature, 0x10000000, 0);
            return 0;
        }
        break;
    }
    }
    return 1;
}

// @ 0x00db3390
void FUN_00db3390(cSPCreatureBase* a1, void* a2, void* a3, void* a4, void* a5, SimuState* state)
{
    if (state->mpEffect_18 != 0)
    {
        state->mpEffect_18->pv03(0);
        if (state->mpEffect_18 != 0)
        {
            IWin_s00db_2fd0* old = state->mpEffect_18;
            state->mpEffect_18 = 0;
            old->Release();
        }
    }
    if (state->mpEffect_18 != 0)
        state->mpEffect_18->Release();
}

// @ 0x00db33d0
char FUN_00db33d0(cSPCreatureBase* creature, void* a2, void* a3, void* a4, void* a5, SimuState* state)
{
    cSimLoco* loco = &creature->mLoco_c0;

    switch (state->mPhase_04)
    {
    case 0:
    {
        creature->FUN_00c196a0(state->mpObj_00, 1, 0);
        FUN_00da61e0(creature, 0x16);

        cPropSet* prop = creature->pv45(state->mpObj_00);
        float v1 = GetPropertyT_float(prop->mpProps_130, 0xc492c89f, kPropDefaultA);
        float v2 = GetPropertyT_float(prop->mpProps_130, 0x191dcad8, kPropDefaultB);
        float range = (float)(FUN_00b3d350()->FUN_00b7e4d0() * v2 * kSpeedScale);
        cPlanetModel* pm = FUN_00b3d350();

        Vector3f probe;
        Vector3f dest;
        Vector3f hit;

        float* pos = (float*)loco->pv11(v1, &probe.x, 1.0f, 1, (int)range);
        if (pm->RayCast(pos))
        {
            if (pm->RayCast(&dest.x))
            {
                Vector3f normal;
                if (!pm->FUN_00b88f60(v2, &hit.x, &normal.x))
                {
                    Vector3f delta;
                    delta.x = hit.x - dest.x;
                    delta.y = hit.y - dest.y;
                    delta.z = hit.z - dest.z;
                    float* n = normalized_safe(&normal.x, &delta.x);
                    normal.x = n[0];
                    normal.y = n[1];
                    normal.z = n[2];
                }

                Vector3f back;
                back.x = -normal.x;
                back.y = -normal.y;
                back.z = -normal.z;

                state->mPos_08[0] = back.x * v2 + hit.x;
                state->mPos_08[1] = back.y * v2 + hit.y;
                state->mPos_08[2] = back.z * v2 + hit.z;

                void* p = loco->pv11(1.0f, &back.x, kProbeStep, 0, 0);
                creature->MoveToPointAndFacingAtSpeed(2, p, 1.0f, 2.0f);
            }
        }

        void* anim = creature->FUN_00c22820();
        state->mAnim_14 = (int)creature->InterruptAnimation(0x6006755, (int)anim, 0);
        state->mPhase_04 = 2;
        return 1;
    }
    case 2:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0xe95450e, &out, 0, state->mAnim_14, 1))
        {
            creature->SetCurrentToolEffect(0, out);
            state->mAnim_14 = (int)creature->PlayAnimation(0x6006752, 1, -1);
            state->mPhase_04 = 3;
            return 1;
        }
        break;
    }
    case 3:
    {
        // Walk to the goal until the animation ends and the loco is close enough.
        if (!loco->IsNearGoal() || !creature->AnimationFinished(state->mAnim_14))
            break;

        IWin_s00db_2fd0* goal = state->mpObj_00;
        cPropSet* prop = creature->pv45(state->mpObj_00);
        float v2 = GetPropertyT_float(prop->mpProps_130, 0x84f97568, kPropDefaultB);

        float* cur = (float*)((IWin_s00db_2fd0*)loco)->pv11();
        float dx = state->mPos_08[0] - cur[0];
        float dy = state->mPos_08[1] - cur[1];
        float dz = state->mPos_08[2] - cur[2];

        // Inside the arrival radius of the goal, and the goal is a real position.
        if (Vector3_NotEqual(state->mPos_08, &kInvalidPos) &&
            v2 * v2 <= dx * dx + dy * dy + dz * dz)
        {
            SpawnLocatingCallResponse(creature, state->mPos_08);

            // Effect 0xa86f8d7e: place the "travelling" visual effect at the goal
            // position, oriented by the loco's current quaternion.
            cEffectsManager* fx = EffectsManagerPtr();
            if (fx->AddEffect(0xa86f8d7e, 0, state->mpEffect_18))
            {
                XformMsg msg;
                msg.FUN_00571d40(state->mPos_08);
                float mat[9];
                Matrix3FromQuaternion(mat, (float*)loco->pv12());
                for (int i = 0; i < 9; i++)
                    msg.mMatrix_14[i] = mat[i];
                msg.mFlags_00 |= 2;
                msg.mCount_02 = msg.mCount_02 + 2;
                msg.mScale_10 = 1.0f;
                state->mpEffect_18->pv06(&msg);
                state->mpEffect_18->pv02(0);
            }

            // Effect 0x6d8f14ef: second visual effect, anchored on the loco.
            cEffectsManager* fx2 = EffectsManagerPtr();
            if (fx2->AddEffect(0x6d8f14ef, 0, state->mpEffect_18))
            {
                XformMsg msg;
                msg.FUN_00571d40((float*)((IWin_s00db_2fd0*)loco)->pv11());
                float mat[9];
                Matrix3FromQuaternion(mat, (float*)loco->pv12());
                for (int i = 0; i < 9; i++)
                    msg.mMatrix_14[i] = mat[i];
                msg.mFlags_00 |= 2;
                msg.mCount_02 = msg.mCount_02 + 2;
                msg.mScale_10 = 1.0f;
                goal->pv06(&msg);
                state->mpEffect_18->pv02(0);
            }

            void* anim = creature->FUN_00c22820();
            state->mAnim_14 = (int)creature->PlayAnimation(0x60ca7f9, 1, (int)anim);
            state->mPhase_04 = 4;
            if (goal != 0)
            {
                goal->Release();
                return 1;
            }
        }
        break;
    }
    case 4:
    {
        if (creature->AnimationFinished(state->mAnim_14))
        {
            state->mPhase_04 = 5;
            return 1;
        }
        break;
    }
    case 5:
    {
        if ((state->mpEffect_18 == 0 || !state->mpEffect_18->pv04()) &&
            creature->AnimationFinished(state->mAnim_14))
        {
            void* anim = creature->FUN_00c22820();
            state->mAnim_14 = (int)creature->PlayAnimation(0x60ca7fb, 1, (int)anim);
            state->mPhase_04 = 6;
            return 1;
        }
        break;
    }
    case 6:
    {
        if (creature->AnimationFinished(state->mAnim_14))
        {
            void* anim = creature->FUN_00c22820();
            state->mAnim_14 = (int)creature->PlayAnimation(0x609ea41, 1, (int)anim);
            state->mPhase_04 = 8;
        }
        break;
    }
    case 7:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0xe95450e, &out, 0, state->mAnim_14, 1))
        {
            creature->SetCurrentToolEffect(0, out);
            state->mPhase_04 = 8;
            return 1;
        }
        break;
    }
    case 8:
    {
        int out = -1;
        if (creature->WaitForAnimEventOrEnd(0x7d7502fc, &out, 0, state->mAnim_14, 1))
        {
            creature->FUN_00c26310(out);
            state->mPhase_04 = 9;
            return 1;
        }
        break;
    }
    case 9:
    {
        if (creature->AnimationFinished(state->mAnim_14))
        {
            FUN_00da6240(creature, 0x10000000, 0);
            return 0;
        }
        break;
    }
    }
    return 1;
}

// @ 0x00db3c40
cGroupMovement_s00db_2fd0* cResizableObjectPoolT::GetObject(uint32_t index)
{
    uint32_t i = index & 0xbfffffff;
    int32_t  count = (int32_t)(mpEnd_04 - mpBegin_00) / kPoolSlotStride;

    if (i < (uint32_t)count)
    {
        bool free = ((cPoolSlot*)(mpBegin_00 + i * kPoolSlotStride))->mBits.mFree;
        if (!free)
            return &((cPoolSlot*)(mpBegin_00 + i * kPoolSlotStride))->mObject;
    }
    return 0;
}

// @ 0x00db3c90
void cResizableObjectPoolT::ReleaseSlot(uint32_t index)
{
    cPoolSlot* slot = (cPoolSlot*)(mpBegin_00 + index * kPoolSlotStride);

    slot->mObject.FUN_vtbl0(0);
    slot->mLink_00 = (slot->mLink_00 & 0xc0000000) |
                     (mFreeHead_18 & 0x3fffffff) | 0x80000000;
    mFreeHead_18 = index;
    if (mIndex_14 == index)
        mIndex_14 = FUN_00daed20(index);
}

// @ 0x00db3da0
cPoolFind* cResizableObjectPoolT::FindFreeSlot(cPoolFind* out, cPoolNode* node, cPoolNode** head)
{
    cPoolNode* p = node->mpNext_10;
    out->mpSlot_04 = head;
    out->mpNode_00 = p;
    while (p == 0)
    {
        out->mpSlot_04 += 1;
        p = *out->mpSlot_04;
        out->mpNode_00 = p;
    }

    cPoolNode* cur = *head;
    if (cur == node)
    {
        // cur == node here; the free-list head is unlinked in one step.
        *head = node->mpNext_10;
    }
    else
    {
        cPoolNode* prev = cur;
        cPoolNode* q = prev->mpNext_10;
        while (q != node)
        {
            prev = q;
            q = prev->mpNext_10;
        }
        prev->mpNext_10 = q->mpNext_10;
    }

    if (node != mpSentinel_30)
    {
        if (node >= mpDeleteBegin_24 && node < mpDeleteEnd_28)
        {
            node->mpFreeLink_00 = mpFreeList_1c;
            mpFreeList_1c = node;
            mCount_0c--;
            return out;
        }
        FUN_00f47380(node);
    }
    mCount_0c--;
    return out;
}

// @ 0x00db3e30
void cResizableObjectPoolT::AllocNode(cPoolNode* src)
{
    cPoolNode* node = mpFreeList_1c;

    if (node != 0)
        mpFreeList_1c = node->mpFreeLink_00;
    else
    {
        uint32_t size = mNodeSize_2c;
        node = (cPoolNode*)FUN_00f473a0(size, kAllocTag, 0, 0, kAllocFile, 0xd1);
    }

    if (node != 0)
    {
        node->mValue_00 = src->mValue_00;
        node->mValue_04 = src->mValue_04;
        node->mValue_08 = src->mValue_08;
        node->mValue_0c = src->mValue_0c;
    }
    node->mpNext_10 = 0;
}

// @ 0x00db3e90
bool cSocialActionHost::CheckSocialTarget(cSocialTarget* pTarget)
{
    if (IsSocialQueryActive() != 0)
        return false;

    cObject* pObject = pTarget->mpObject;
    float fValue = pTarget->mfValue;
    cGroupMovement_s00db_3e90* pGroup = (cGroupMovement_s00db_3e90*)ResizablePoolGet(mnGroupHandle);

    cObject* pOther = nullptr;
    if (pGroup->mfCooldown == 0.0f) {
        if (mpSocialQuery != nullptr && mpSocialQuery != gSocialQueryManager)
            return false;
        pOther = GetSocialQueryObject();
    } else {
        if (pGroup->mpOwner == nullptr)
            return false;
        pOther = (cObject*)LookupToolByKey(0xce9f6639);
    }

    if (pOther != nullptr) {
        if (pObject->Call(0x20) == pOther->Call(0x20)) {
            if (pObject->Call(0x4c) == pOther->Call(0x4c)) {
                Vec3_s00db_3e90* pMine = (Vec3_s00db_3e90*)pObject->Call(0x2c);
                Vec3_s00db_3e90* pTheirs = (Vec3_s00db_3e90*)pOther->Call(0x2c);
                float fDx = pTheirs->mX - pMine->mX;
                float fDy = pTheirs->mY - pMine->mY;
                float fDz = pTheirs->mZ - pMine->mZ;
                if (fDz * fDz + (fDx * fDx + fDy * fDy) < 5625.0f) {
                    if (fValue != 0.0f)
                        return pGroup->mfValue2 == fValue;
                    float gx = pGroup->mfX - pTarget->mfX;
                    float gy = pGroup->mfY - pTarget->mfY;
                    float gz = pGroup->mfZ - pTarget->mfZ;
                    if (gz * gz + (gx * gx + gy * gy) < pGroup->mfRangeSq)
                        return true;
                    return false;
                }
            }
        }
    }
    return false;
}

// @ 0x00db4050
bool cSocialActionHost::ResolveTarget(cActionState* pState)
{
    if (pState != nullptr) {
        pState->mnLoopCount = 0;
        pState->mnEffectId = 0;
        *(uint32_t*)((uint8_t*)pState + 0x18) = 0;
        *(uint32_t*)((uint8_t*)pState + 0x1c) = 0;
    }

    cGameNounManager* pNouns = (cGameNounManager*)GetSocialQueryManager();
    if (pNouns == nullptr || *(uint32_t*)pNouns != 0x16)
        return false;

    int16_t nKind = *(int16_t*)((uint8_t*)pNouns + 0x4b);
    uint32_t* pKey;
    if (nKind == 10 || nKind == 0x10) {
        if ((*(uint8_t*)((uint8_t*)pNouns + 0x49) & 0x30) == 0)
            pKey = (uint32_t*)(nKind != 0 ? ((uint8_t*)pNouns + 0x39) : 0);
        else
            pKey = *(uint32_t**)((uint8_t*)pNouns + 0x39);
    } else {
        pKey = (uint32_t*)&gEmptySocialTarget[0];
    }

    uint32_t nKey = *pKey;
    pState->mpTarget = (void*)(intptr_t)nKey;
    pState->mnState = 0;
    pState->mnAnimation = 0;
    *(uint8_t*)((uint8_t*)pState + 0x14) = 0;

    void* pObject = *(void**)((uint8_t*)this + 0xb4);
    (void)pObject;
    void* pFound = nullptr;
    (void)pFound;
    return pState->mnLoopCount != 0;
}

// @ 0x00db40f0
void ReleaseSocialTargetState(void* pArg1, void* pArg2, void* pArg3, void* pArg4, void* pArg5, cActionState* pState)
{
    (void)pArg1;
    (void)pArg2;
    (void)pArg3;
    (void)pArg4;
    (void)pArg5;
    if (pState == nullptr)
        return;

    void* pBlock = *(void**)((uint8_t*)pState + 0x14);
    if (pBlock != nullptr) {
        int nRefs = *(int*)((uint8_t*)pBlock - 4);
        if (nRefs != 0)
            operator_delete__(pBlock);
    }

    cObject* pTarget = (cObject*)*(void**)((uint8_t*)pState + 0x0c);
    if (pTarget == nullptr)
        return;
    int nRefs = *(int*)((uint8_t*)pTarget + 4);
    *(int*)((uint8_t*)pTarget + 4) = nRefs - 1;
    if (nRefs - 1 == 0) {
        *(int*)((uint8_t*)pTarget + 4) = 1;
        pTarget->Call(0x00, (uint32_t)1);
    }
}

// @ 0x00db4140
int cSocialActionHost::Start(cActionState* pState)
{
    void* pAnimation = nullptr;
    (void)pAnimation;

    ConfigureSocialQuery(this, nullptr, nullptr);
    BeginAnimation((cObject*)this, 0, 0);

    if (IsLeader(this) != 0 && ((cObject*)this)->CallChar(0x58) != 0) {
        void* pBuffer = nullptr;
        (void)pBuffer;
        ConfigureSocialQuery(this, (uint8_t*)0x20, "SocialPower");
        int nQuery = StartAnimation(this, 0x10000000);

        *(uint32_t*)((uint8_t*)(intptr_t)nQuery + 0x1a8) = 0;
        *(uint32_t*)((uint8_t*)(intptr_t)nQuery + 0x1a4) = 0;
        *(uint8_t*)((uint8_t*)(intptr_t)nQuery + 0x1ac) = 0;
        *(void**)((uint8_t*)(intptr_t)nQuery + 0x224) = (void*)&PlaceTargetsEntry;

        cObject* pManager = (cObject*)GetSocialQueryManager();
        if (pManager != nullptr && *(uint32_t*)pManager == 0x16) {
            cObject* pQuery = (cObject*)GetCurrentActionTarget(this, 0);
            void* pFound = *(void**)((uint8_t*)pQuery + 0xb4);
            if (pFound != nullptr && *(int*)((uint8_t*)pFound + 8) == 0x38) {
                PressBehaviourButton(0, 1, 0.0f, 0);
                FinishAction((cSocialActionHost*)this, 0x16);

                void* pListA = nullptr;
                void* pListB = nullptr;
                (void)FindNearbyObjects(this, *(float*)((uint8_t*)pFound + 0xa8), 0,
                                        (void*)0, 0);
                for (; pListA != pListB; pListA = (uint8_t*)pListA + 4) {
                    cObject* pEntry = *(cObject**)pListA;
                    if (pEntry == nullptr)
                        continue;
                    cObject* pComp = (cObject*)pEntry->Call(0xb8, 0x4f176642);
                    if (pComp == nullptr)
                        continue;
                    if (GetCombatantDamageState(pComp) == 0)
                        continue;
                    if (pComp == (cObject*)this)
                        continue;
                    void* pAnim = (void*)(intptr_t)PressBehaviourButton(0, 0x10000000,
                                                                       10.0f, 0);
                    if (pAnim == nullptr)
                        continue;
                    *(uint32_t*)((uint8_t*)pAnim + 0x0c) = 1;
                }
            }
        }
    } else {
        int nAnim = PlayIdleAnimation((cObject*)this, 0, 0x10000000);
        if (nAnim != 0) {
            void* pBlock = WatchMemoryBlock((void*)(intptr_t)nAnim);
            intptr_t nOffset = pBlock == nullptr ? 0 : (intptr_t)pBlock + 0x5a8;
            ((cObject*)this)->Call(0x84, (void*)nOffset, (void*)(intptr_t)1);
        }
    }

    ResetGroupMovement(0);
    ((cObject*)this)->Call(0xec);
    pState->mpTarget = nullptr;
    pState->mnState = 0;
    return 1;
}

// @ 0x00db4370
int cSocialActionHost::Update(cActionState* pState)
{
    switch (pState->mnState) {
    case 0:
        {
            void* pTarget = *(void**)((uint8_t*)this + 0xb4);
            (void)pTarget;
            PressBehaviourButton(*(int*)((uint8_t*)pState), 1, 0.0f, 0);
            FinishAction((cSocialActionHost*)this, 0x16);
            int nAnimation = InterruptAnimation((cObject*)this, 0x6006753, 0xffffffff, 0);
            pState->mnAnimation = nAnimation;
            pState->mnState = 1;
        }
        break;

    case 1:
        {
            char bFinished = AnimationFinished((cObject*)this, pState->mnAnimation);
            if (bFinished == 0) {
                int nEvent = -1;
                if (WaitForAnimEventOrEnd((cObject*)this, 0x7d7502fc, &nEvent, 0,
                                          pState->mnAnimation, 1) != 0) {
                    SetCurrentToolEffect((cSocialActionHost*)this, 0x16, nEvent);
                    pState->mnEffectId = nEvent;
                }
                nEvent = -1;
                if (WaitForAnimEventOrEnd((cObject*)this, 0xe95450e, &nEvent, 0,
                                          pState->mnAnimation, 1) != 0) {
                    SetCurrentToolEffect((cSocialActionHost*)this, 0, nEvent);
                    pState->mnLoopCount = pState->mnLoopCount + 1;
                    pState->mnEffectId = -1;
                }
            }
            if (3 < pState->mnLoopCount) {
                void* pEffect = CreateSocialEffect(this);
                (void)pEffect;
                pState->mnState = 2;
                return 1;
            }
            if (bFinished != 0) {
                pState->mnState = (pState->mnLoopCount < 1) + 2;
                return 1;
            }
        }
        break;

    case 2:
        {
            int nAnim = PlayIdleAnimation((cObject*)this, 0, 0x10000000);
            char bFinished = AnimationFinished((cObject*)this, pState->mnAnimation);
            if ((nAnim != 0 && *(int*)((uint8_t*)nAnim + 0x0c) == 2) || bFinished != 0) {
                void* pTarget = *(void**)((uint8_t*)this + 0xb4);
                (void)pTarget;

                void* pListA = nullptr;
                void* pListB = nullptr;
                int nState = PressBehaviourButton(*(int*)((uint8_t*)pState), 1, 0.0f, 0);
                (void)nState;
                if (pTarget != nullptr) {
                    void* pOwner = (void*)(intptr_t)pTarget;
                    (void)FindNearbyObjects(this, *(float*)((uint8_t*)pOwner + 0xf4) +
                                            *(float*)((uint8_t*)pOwner + 0xa8),
                                            (uint32_t)pListA, (void*)0, 0);
                    uint32_t nCount = (uint32_t)(((uint8_t*)pListB - (uint8_t*)pListA) >> 2);
                    for (uint32_t i = 0; i < nCount; ++i) {
                        cObject* pEntry = ((cObject**)pListA)[i];
                        if (pEntry == nullptr)
                            continue;
                        cObject* pStimuli = (cObject*)pEntry->Call(0xb8, 0x013f94d4);
                        if (pStimuli == nullptr)
                            continue;
                        if (pStimuli == (cObject*)&gEmptySocialTarget[0])
                            continue;
                        if (pEntry->CallChar(0x58) != 0)
                            continue;
                        if (RandomRange(0.0f, 1.0f) <= 0.0f)
                            continue;

                        void* pAnimTarget = *(void**)((uint8_t*)pOwner + 0x3c);
                        Vec3_s00db_3e90* pMine = (Vec3_s00db_3e90*)pEntry->Call(0x2c);
                        Vec3_s00db_3e90* pOwnerPos = (Vec3_s00db_3e90*)((cObject*)this)->Call(0x2c);
                        Vec3_s00db_3e90 direction;
                        direction.mX = pOwnerPos->mX - pMine->mX;
                        direction.mY = pOwnerPos->mY - pMine->mY;
                        direction.mZ = pOwnerPos->mZ - pMine->mZ;

                        Vec3_s00db_3e90 normalised;
                        Matrix3FromQuaternion((float*)&normalised, (const Vec4*)&direction);
                        void* pFacing = (void*)0x4c;
                        (void)pFacing;
                        ((cObject*)this)->Call(0x4c, &normalised);
                        AddSocialTarget(pEntry, (uint32_t)(intptr_t)pAnimTarget,
                                        (const Vec3_s00db_3e90*)&normalised, (const Vec3_s00db_3e90*)&normalised,
                                        (cObject*)this, (const Vec3_s00db_3e90*)&normalised);

                        void* pResult;
                        if (SpendTribePoints(0x10, 0x10000) != 0)
                            pResult = (void*)0;
                        else
                            pResult = (void*)(intptr_t)GetCreativeCreatureRate();
                        (void)pResult;
                    }
                }
                ClearStimuli((cObject*)this, 0, 0x10000000);
                pState->mnState = 3;
                return 1;
            }
        }
        break;

    case 3:
        if (AnimationFinished((cObject*)this, pState->mnAnimation) != 0) {
            PressBehaviourButton(0, 0x20, gMaxFloat, 0);
            return FinishAction((cSocialActionHost*)this, 0x16);
        }
        break;

    default:
        break;
    }
    return 1;
}

// @ 0x00db4900
float cSocialActionHost::TryTribeTool(uint32_t nA, uint32_t nB, uint32_t nFlags, cBehaviorStimuli_s00db_3e90* pStimuli, uint8_t* pbFlag)
{
    (void)nA;
    (void)nB;
    if (*(uint8_t*)((uint8_t*)this + 0xf90) == 0 || (nFlags & 0x400) != 0)
        return 0.0f;

    cTribe_s00db_3e90* pTribe = (cTribe_s00db_3e90*)GetTribe();
    int aTools[9];
    aTools[0] = 1;
    aTools[1] = 2;
    aTools[2] = 3;
    aTools[3] = 4;
    aTools[4] = 5;
    aTools[5] = 6;
    aTools[6] = 7;
    aTools[7] = 8;
    aTools[8] = 9;

    for (uint32_t i = 0; i < 9; ++i) {
        void* pTool = pTribe->GetToolOfType(aTools[i]);
        if (pTool == nullptr)
            continue;
        if ((*(uint8_t*)((uint8_t*)pTool + 0x84) & 0x10) != 0)
            continue;
        int nDamage = ((cCombatant*)((uint8_t*)pTool + 0x120))->GetDamageState();
        if (nDamage == 2)
            continue;
        if (SpendTribePoints(0, 0) != 0)
            continue;

        if (pStimuli != nullptr)
            pStimuli->GetAny();
        SetSocialTargetPointers(pStimuli, aTools[i]);
        *pbFlag = 1;
        return RandomRange(0.1f, 1.0f) * 0.5f;
    }
    return 0.0f;
}

// @ 0x00db4a20
uint8_t CancelSocialAction(void* pThis)
{
    uint32_t nHandle = *(uint32_t*)((uint8_t*)pThis + 0x1a4);
    if (nHandle > 0) {
        cGroupMovement_s00db_3e90* pGroup = (cGroupMovement_s00db_3e90*)gGroupMovementPool.GetObject(nHandle);
        pGroup->Stop();
        gGroupMovementPool.ReleaseObject(nHandle & 0xbfffffff);
    }
    return 1;
}

// @ 0x00db4a60
void cSocialActionHost::PlaceTargets(cSocialData* pData, bool bSnap)
{
    cObject* pOwner = pData->mpOwner;
    uint32_t nHandle = pData->mnHandle;
    float fOffset = pData->mfOffset;
    (void)fOffset;
    (void)pOwner;

    uint32_t* pListA = nullptr;
    uint32_t* pListB = nullptr;
    (void)pListA;
    (void)pListB;

    if (bSnap)
        AddSocialTarget((cObject*)pOwner, 0x1f, (const Vec3_s00db_3e90*)&pData->mfX, nullptr,
                        nullptr, nullptr);

    float rotation[9];
    Matrix3FromQuaternion(rotation, &pData->mRotation);

    cPlanetModel_s00db_3e90* pPlanet = (cPlanetModel_s00db_3e90*)gPlanetModelPointer;
    float fWaterHeight = pPlanet->GetWaterHeight();

    int nIndex = 0;
    for (;;) {
        void* pEntry = GetNearbyEntry(nIndex);
        if (pEntry == nullptr) {
            for (uint32_t* p = pListA; p != pListB; ++p) {
                if (*(void**)(intptr_t)*p != nullptr)
                    (*(cObject**)(intptr_t)*p)->Call(0xc0);
            }
            if (pListA != nullptr && *(pListA - 1) != 0)
                operator_delete__(pListA);
            if (pListB != nullptr && *(pListB - 1) != 0)
                operator_delete__(pListB);
            return;
        }

        ++nIndex;
        if (*(uint8_t*)pEntry != 0 && *(int*)((uint8_t*)pEntry + 8) != 0)
            PressBehaviourButton(0, 0, 0.0f, 0);

        float fX = *(float*)((uint8_t*)pEntry + 0x0c);
        float fY = *(float*)((uint8_t*)pEntry + 0x10);
        float fZ = *(float*)((uint8_t*)pEntry + 0x14);

        if (pData->mbSnap != 0) {
            Vec3_s00db_3e90 position;
            position.mX = pData->mfX + (rotation[0] * fX + rotation[6] * fY + rotation[3] * fZ);
            position.mY = pData->mfY + (rotation[1] * fX + rotation[7] * fY + rotation[4] * fZ);
            position.mZ = pData->mfZ + (rotation[2] * fX + rotation[5] * fY + rotation[8] * fZ);
            Vec3_s00db_3e90* pSurface = pPlanet->DirectionToSurfacePosition(&position, &position);
            fX = pSurface->mX;
            fY = pSurface->mY;
            fZ = pSurface->mZ;
        }

        if (bSnap) {
            if (fWaterHeight * fWaterHeight < fX * fX + fZ * fZ + fY * fY) {
                for (uint32_t* p = pListA; p != pListB; ++p) {
                    uint8_t* pObject = (uint8_t*)(intptr_t)*p;
                    float fRadius = *(float*)(pObject + 0x44);
                    float dx = fX - *(float*)(pObject + 0x38);
                    float dy = fY - *(float*)(pObject + 0x3c);
                    float dz = fZ - *(float*)(pObject + 0x40);
                    if (dx * dx + dz * dz + dy * dy < fRadius * fRadius)
                        PressBehaviourButton(1, 0, 0.0f, 0);
                }
            } else {
                PressBehaviourButton(1, 0, 0.0f, 0);
            }
            continue;
        }

        for (uint32_t* p = pListA; p != pListB; ++p) {
            cObject* pObject = (cObject*)(intptr_t)*p;
            uint32_t nKey = 0;
            if (pObject != nullptr)
                nKey = (uint32_t)(intptr_t)pObject->Call(0xb8, 0x116dd1b);
            uint32_t nBucket = nKey % mnBucketCount;
            float fRadius = GetNearbyRadius(pObject);
            (void)nBucket;
            (void)fRadius;
            PressBehaviourButton(2, 0, 0.0f, 0);
        }
    }
}

// @ 0x00db97f0
namespace SP {
cHealOtherData::cHealOtherData(const cHealOtherData& src)
: cHealOtherBase(src)
{
    mEntries.Copy(src.mEntries);

    mTargets.Init();
    mTargets = src.mTargets;

    mTrack.Copy(src.mTrack);

    mpSubject = src.mpSubject;
    if (mpSubject)
        mpSubject->AddRef();

    mpObject = src.mpObject;
    if (mpObject)
        mpObject->AddRef();

    for (int i = 0; i < 6; ++i)
        mCounters[i].mValueAsFloat = src.mCounters[i].mValueAsFloat;
    for (int i = 0; i < 8; ++i)
        mRadii[i] = src.mRadii[i];

    mAnimIndex = src.mAnimIndex;
    mbFlag1d0 = src.mbFlag1d0;
    mbFlag1d1 = src.mbFlag1d1;
    mCircle.Copy(src.mCircle);
    mRandSeed = src.mRandSeed;
    mbFlag23c = src.mbFlag23c;
    mTuningIndex = src.mTuningIndex;
    mbFlag244 = src.mbFlag244;
    mSubAnim = src.mSubAnim;
}
}  // namespace SP

// @ 0x00db99a0
namespace SP {
cHealOtherEntry* FUN_00db99a0(cHealOtherEntry* pFirst, cHealOtherEntry* pLast, cHealOtherEntry* pDst)
{
    if (pFirst != pLast) {
        do {
            if (pDst) {
                pDst->mFlags = pFirst->mFlags;
                bool bEmpty = ((unsigned)pFirst->mFlags >> 31) & 1;
                if (!bEmpty && &pDst->mData)
                    ::new (static_cast<void*>(&pDst->mData)) cHealOtherData(pFirst->mData);
            }
            ++pFirst;
            ++pDst;
        } while (pFirst != pLast);
    }
    return pDst;
}
}  // namespace SP

// @ 0x00db9b30
namespace SP {
bool TRIBE_HEAL_OTHER_Tick(cSPCreatureCitizen_s00db_9380* c, int, int, int, int, cHealActionState* st, float fHealScale)
{
    cSPCreatureCitizen_s00db_9380* pSubject = (cSPCreatureCitizen_s00db_9380*)ResolveNoun(st->mToolId);
    if (!pSubject)
        return FUN_00da6270(c, 5);

    if (pSubject->mCombat.mHealth >= pSubject->mCombat.GetMaxHealth())
        return FUN_00da6270(c, 5);

    Loco_s00db_9380* pSubj = &pSubject->mLoco;
    Loco_s00db_9380* pSelf = &c->mLoco;

    float fReach = pSubj->GetRadius() + pSelf->GetRadius();
    float fSeparation = GetSeparation(pSelf, pSubj, 1);

    Vec2 vRange = GetPropertyAsVector2(gpTribeProperties, 0x1e6bcc1d, Vec2(1.0f, 5.0f));
    float fStartFraction = GetPropertyT(gpTribeProperties, 0xd21a82b1, 1.0f);

    float fMaxRange = vRange.y;
    float fMinRange = vRange.x;
    float fFullReach = (fMaxRange - fSeparation) * 0.5f + fSeparation + fStartFraction;

    bool bInReach = fMaxRange > fSeparation;
    Vec3_s00db_9380 facing;
    pSubj->GetFacing(&facing);

    Vec3_s00db_9380 approach(pSubj->GetPosition()->x - facing.x * fSeparation,
                  pSubj->GetPosition()->y - facing.y * fSeparation,
                  pSubj->GetPosition()->z - facing.z * fSeparation);

    bool bHealing = c->HasAnim(0x562cfbf);
    if (!bInReach) {
        if (bHealing)
            c->CancelToolAnim(0);
    } else {
        if (!bHealing)
            c->InterruptAnimationWithTarget(0x562cfbf, pSubj, -1, -1);

        pSubject->mCombat.PartialRepair(fFullReach * fHealScale);

        if (pSubject->mCombat.mHealth >= pSubject->mCombat.GetMaxHealth() && pSelf->IsAlive()
            && pSubj->IsAlive() && GetCurrentGameMode() == 0x1654c02) {
            void* pController = AchievementsController();
            if (!HasAchievement(pController, 0x90ec8983)) {
                int* pCounter = cTribeModeStrategy_Instance()->mCounters.Find(pSubject->mSpeciesKey);
                ++*pCounter;
                if (*pCounter >= GetAchievementTarget(0x90ec8983))
                    AwardAchievement(pController, 0x90ec8983);
            }
            c->mpEnv->mMotion.Play(0, 0x20, gHealTimeLimit, 0);
        }

        if (CreatureStateCode(pSubject)) {
            float fCosLimit = cosf(GetPropertyT(gpTribeProperties, 0x362cc818, 45.0f) * kHalfDegree);
            const Vec3_s00db_9380* pSubjPos = pSubj->GetPosition();
            const Vec3_s00db_9380* pSelfPos = pSelf->GetPosition();
            Vec3_s00db_9380 toSelf(pSelfPos->x - pSubjPos->x, pSelfPos->y - pSubjPos->y,
                        pSelfPos->z - pSubjPos->z);
            Vec3_s00db_9380 toSelfDir;
            NormalizeSafe(&toSelfDir, &toSelf);
            Vec3_s00db_9380 subjFacing;
            pSubj->GetFacing(&subjFacing);
            float fDot = toSelfDir.z * -subjFacing.z + toSelfDir.y * -subjFacing.y
                       + toSelfDir.x * -subjFacing.x;
            if (fDot <= fCosLimit)
                goto Move_Closer;
        }

        if (fSeparation <= (fMaxRange - fStartFraction) * 0.75f + fStartFraction)
            return true;
    }

Move_Closer:
    {
        Vec3_s00db_9380 surf;
        PlanetModel_s00db_9380()->DirectionToSurfacePosition(&surf, &approach, 1.0f, 2.0f);
        c->MoveToPointAtSpeed(2, &surf);
    }
    return true;
}
}  // namespace SP

// @ 0x00dba000
namespace SP {
bool FUN_00dba000(cSPCreatureCitizen_s00db_9380* c, int, int, int, int, cHealActionState* st)
{
    switch (st->mStep) {
    case 0: {
        c->CancelTool(st->mToolId, true, false);

        cIdVector* pAnimIds = &st->mpTuning->mAnimIds;
        unsigned nAnimCount = pAnimIds->mpEnd - pAnimIds->mpBegin;
        unsigned nIndex = nAnimCount > 0 ? gMathRandom.RandomUint32Uniform(nAnimCount) : 0;
        st->mAnimId = c->InterruptAnimation(st->mpTuning->GetAt(nIndex), -1, 0);

        if (st->mpTuning->mId == 0x35) {
            FUN_00db9f60(st, c->mLoco.GetPosition());
            FUN_00dae730(st);
        }
        st->mStep = 1;
        return true;
    }
    case 1:
        if (c->AnimationFinished(st->mAnimId)) {
            FUN_00db2c00(st);
            st->mbDone = true;
            st->mStep = 2;
            return true;
        }
        break;
    case 2:
        if (st->mpTuning->mId == 0x35 && !st->mbDone) {
            FUN_00db2c00(st);
            st->mbDone = true;
        }
        c->mpEnv->mMotion.Play(0, 0x20, gHealTimeLimit, 0);
        return FUN_00da6270(c, 0x16);
    }
    return true;
}
}  // namespace SP

// @ 0x00dba120
namespace SP {
cHealOtherData& cHealOtherData::operator=(const cHealOtherData& src)
{
    mFlags = src.mFlags;
    mEntries = src.mEntries;
    mTargets = src.mTargets;
    mTrack = src.mTrack;

    if (src.mpSubject != mpSubject) {
        cRefCounted* pNew = src.mpSubject;
        cRefCounted* pOld = mpSubject;
        if (pNew)
            pNew->AddRef();
        mpSubject = pNew;
        if (pOld)
            pOld->Release();
    }
    if (src.mpObject != mpObject) {
        cRefCounted* pNew = src.mpObject;
        cRefCounted* pOld = mpObject;
        if (pNew)
            pNew->AddRef();
        mpObject = pNew;
        if (pOld)
            pOld->Release();
    }

    for (int i = 0; i < 6; ++i)
        mCounters[i].mValue = src.mCounters[i].mValue;
    for (int i = 0; i < 8; ++i)
        mRadii[i] = src.mRadii[i];

    mAnimIndex = src.mAnimIndex;
    mbFlag1d0 = src.mbFlag1d0;
    mbFlag1d1 = src.mbFlag1d1;
    mCircle = src.mCircle;

    mRandSeed = src.mRandSeed;
    mbFlag23c = src.mbFlag23c;
    mTuningIndex = src.mTuningIndex;
    mbFlag244 = src.mbFlag244;
    mSubAnim = src.mSubAnim;
    return *this;
}
}  // namespace SP

// @ 0x00e11ab0
bool cSPUIMinimapWin::HandleMessage(uint32 messageID, void* pMessage)
{
    MinimapMsg* msg = (MinimapMsg*)pMessage;
    IWindow* attackWin;
    IconMapIterator attackIt;
    uint32 attackID;
    uint32 attackColor;

    switch (messageID) {
    case 0x19d6324:
        SetIconColor(msg->mKey, msg->mValue);
        break;

    case 0x164b4eb:
        if (msg) {
            uint32 color = msg->mValue;
            IWindow* pWin = FindWindowByID(msg->mKey, false);
            if (pWin) {
                pWin->SetShadeColor(color);
            }
        }
        break;

    case 0x1c3d2e0:
        mPendingFlags |= (uint32)pMessage;
        break;

    case 0x1c8c174:
        if (msg) {
            RemoveIcon(msg->mKey, true, 0);
            uint32 id = msg->mValue;
            cIconInfo info(*(const cIconInfo*)msg->mType);
            AddIcon(id, info, 0, 0);
        }
        break;

    case 0x1e8c9df:
        RemoveIcon(msg->mKey, true, 0);
        break;

    case 0x354b9e8: {
        if (GameModeManager()->GetActiveModeID() == kModeEditor) break;
        uint32 key = msg->mKey;
        uint32 color = msg->mValue;
        cMapObject* pObject = (cMapObject*)key;
        if (GameModeManager()->GetActiveModeID() != kModeEditor && pObject &&
            !pObject->mVisibility.IsVisible())
            break;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        break;
    }

    case 0x30aa01b: {
        if (!msg) break;
        void* pA = LookupMinimapObjectA(msg->mKey);
        cPlacedObject* pB = LookupMinimapObjectB(msg->mKey);
        if (!pA && !pB) break;
        uint32 color = msg->mValue;
        uint32 key = pA ? (uint32)pA : (uint32)pB;
        uint32 empireID = msg->mEmpireID;
        SP::cCivilization_s00e1_1ab0* pCiv = pA ? 0 : SP::NounManager_s00e1_1ab0()->GetPlayerCivilization();
        if (GameModeManager()->GetActiveModeID() != kModeEditor && pB && pCiv &&
            !pB->mVisibility.IsVisible()) {
            if (SP::NounManager_s00e1_1ab0()->GetPlayerEmpireOrMinus1() != empireID) break;
        }
        if (msg->mType == 1) {
            IconMapIterator it = mIconInfos.find(key);
            if (it == mIconInfos.end()) break;
            IWindow* pWin = FindWindowByID(key, true);
            if (!pWin) break;
            if (!(it->mFlags & 1)) {
                BringToFront(pWin);
            }
            attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        } else {
            IconMapIterator it = mIconInfos.find(key);
            if (it == mIconInfos.end()) break;
            IWindow* pWin = FindWindowByID(key, true);
            if (!pWin) break;
            if (!(it->mFlags & 1)) {
                BringToFront(pWin);
            }
            attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        }
        break;
    }

    case 0x3ac86ad:   // game paused: freeze attack animations
        if (SP::GetCurrentGameMode_s00e1_1ab0() == kModeCiv && !mbPaused) {
            mbPaused = true;
            float now = SPUIHelpers::GetElapsedSeconds();
            IWindow* pChild = 0;
            for (IconMapIterator it = mIconInfos.begin(); it != mIconInfos.end(); ++it) {
                uint32 key = it.mpNode->mKey;
                if (it->mFlags & 0x40103) {
                    IWindow* pWin = FindWindowByID(key, true);
                    if (pWin) {
                        pChild = pWin->GetParent()->FindWindowByID(key + 1, true);
                    }
                    if (pChild) {
                        pChild->SetFlag(1, false);
                        it->mTimeout -= now;
                    }
                    if (pWin) {
                        pChild = pWin->GetParent()->FindWindowByID(key + 3, true);
                    }
                    if (pChild) {
                        pWin->GetParent()->DisposeWindowFamily(pChild);
                    }
                }
            }
        }
        break;

    case 0x3ac86b5:   // game resumed
        if (SP::GetCurrentGameMode_s00e1_1ab0() == kModeCiv && mbPaused) {
            mbPaused = false;
            float now = SPUIHelpers::GetElapsedSeconds();
            IWindow* pChild = 0;
            for (IconMapIterator it = mIconInfos.begin(); it != mIconInfos.end(); ++it) {
                uint32 key = it.mpNode->mKey;
                if (it->mFlags & 0x40103) {
                    IWindow* pWin = FindWindowByID(key, true);
                    if (pWin) {
                        pChild = pWin->GetParent()->FindWindowByID(key + 1, true);
                    }
                    if (pChild) {
                        it->mTimeout += now;
                    }
                    if (pWin) {
                        pChild = pWin->GetParent()->FindWindowByID(key + 3, true);
                    }
                    if (pChild) {
                        pWin->GetParent()->DisposeWindowFamily(pChild);
                    }
                }
            }
        }
        break;

    case 0x44448ed: {
        uint32 mode = SP::GetCurrentGameMode_s00e1_1ab0();
        if (mode == kModeEditor || mode == kModeCiv) {
            mPendingFlags |= 2;
        }
        break;
    }

    case 0x44edd9c:
        ReleaseRef(mpPendingTexture);
        Invalidate();
        RebuildLayout();
        mPendingFlags |= 4;
        UpdateMapTexture();
        break;

    case 0x53039b6: {
        if (GameModeManager()->GetActiveModeID() == kModeEditor) break;
        uint32 color = msg->mValue;
        uint32 key = msg->mKey;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        ShowAttackIcon(pWin, it, key + 1, color, 0x5e51b9d, 50.0f, 10.0f);
        break;
    }

    case 0x55d55d9: {
        if (!msg) break;
        uint32 key = msg->mKey;
        if (!key) break;
        uint32 color = msg->mValue;
        cMapObject* pObject = (cMapObject*)key;
        if (GameModeManager()->GetActiveModeID() != kModeEditor && pObject &&
            !pObject->mVisibility.IsVisible())
            break;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        break;
    }

    case 0x58b817b: {
        if (!msg) break;
        uint32 key = msg->mKey;
        if (!key) break;
        uint32 color = msg->mValue;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        ShowCommIcon(pWin, it, key + 3, color, 0x5e51bed, 42.0f, 42.0f, 4, 0xf);
        break;
    }

    case 0x58b8189: {
        if (!msg) break;
        uint32 key = msg->mKey;
        if (!key) break;
        uint32 color = msg->mValue;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        ShowCommIcon(pWin, it, key + 3, color, 0x5e51bdf, 65.0f, 43.0f, 2, 7);
        break;
    }

    case 0x58b8f28: {
        if (!msg) break;
        cKeyListOwner* pOwner = (cKeyListOwner*)msg->mKey;
        if (!pOwner) break;
        uint32 color = msg->mValue;
        KeyVector& keys = pOwner->GetKeys();
        for (uint32* pKey = keys.mpBegin; pKey != keys.mpEnd; ++pKey) {
            uint32 key = *pKey;
            IconMapIterator it = mIconInfos.find(key);
            if (it == mIconInfos.end()) continue;
            IWindow* pWin = FindWindowByID(key, true);
            if (!pWin) continue;
            if (!(it->mFlags & 1)) {
                BringToFront(pWin);
            }
            ShowCommIcon(pWin, it, key + 3, color, 0x5e51bdf, 65.0f, 43.0f, 2, 7);
        }
        break;
    }

    case 0x5c3bed8: {
        uint32 color = msg->mValue;
        uint32 key = msg->mKey;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        break;
    }

    case 0x66603cd:
        gMinimapFeedbackFlags[msg->mKey].mbSeen = true;
        break;
    }
    return false;

show_attack:
    // the common attack-icon tail shared by 0x354b9e8, 0x30aa01b, 0x55d55d9 and 0x5c3bed8
    ShowAttackIcon(attackWin, attackIt, attackID, attackColor, 0x5e51b8c, 10.0f, 2.0f);
    return false;
}
