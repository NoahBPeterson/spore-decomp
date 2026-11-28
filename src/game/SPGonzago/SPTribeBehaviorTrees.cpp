// src/game/SPGonzago/SPTribeBehaviorTrees.cpp -- migrated from slice(s) s00dbaa40, s00db7fc0, s00db7d60, s00db09c0, s00dbe140, s00dba2f0, s00db86a0, s00db7b60, s00db6e60, s00db5e80, s00db10d0, s00db0130, s00dadce0, s00da5900, s00e11ab0, s00db9380, s00db3e90, s00db2fd0, s00db2060, s00daf820, s00dae980, s00dacd40, s00dabdf0, s00dab1f0, s00daa530, s00da9600, s00da8630, s00da7780, s00da6880, s00d9dce0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeBehaviorTrees.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_147c2c4[];

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
#include "SP/cAgentOrder.h"
#include "SP/cSPPlanetaryArtifact.h"
#include "SP/cSPTimer.h"
#include <string.h>
#include <stddef.h>
#include "SP/cReservationGrid.h"

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
struct cBehaviorTask {
    int32_t mnState;                            // 0x000
    uint32_t mnAnimId;                          // 0x004
};
struct cLeaderChoice {
    void* mpLeader;                             // 0x000
    uint32_t mnAnimId;                          // 0x004
    uint8_t mbChanged;                          // 0x008
};
struct cActionCircleLink {
    uint8_t mPad000[0x20c];                     // 0x000
    uint32_t mnLink;                            // 0x20c
};
struct cTargetData {
    uint8_t mPad000[0x43c];                     // 0x000
    int32_t mnCount;                            // 0x43c
};
class cLocationComponent {
public:
    void* GetObject();
    void* GetOwner();
};
class cActionObject;
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
class cActionObject {
public:
    float GetRadius();
    void* GetBounds();
    void SetTarget(float fValue);
    void MoveTowards(float fValue);
};
class cNounManager {
public:
    void* GetInfo(void* pObject);
    void SetInfo(void* pObject, void* pInfo);
    float GetDistance(void* pObject, float fValue, int32_t nMode);
    void MoveTo(void* pObject, void* pTarget, float fValue, int32_t nMode);
};
class cWorldManager {
public:
    void* FindObject(void* pObject);
    void* GetObjectData(void* pObject);
};
class cEpisodeObject {
public:
    void* GetRecord();
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
void* NounManager_s00d9_dce0();
void* WorldManager();
char IsValidCombatTarget(void* pTarget);
void SetBehaviorState(cSimCreature* pCreature, int32_t nState);
int32_t GetUniverseConstant(int32_t nValue, uint32_t nSalt, int32_t nDefault);
void* CreateEpisodeObject(void* pA, void* pB);
static uint32_t* GetActionLink(cSimCreature* pCreature)
{
    cActionCircleLink* pLink = (cActionCircleLink*)pCreature->GetActionObject();
    if (pLink == nullptr)
        return nullptr;
    return &pLink->mnLink;
}
static void AttachTargetInfo(cSimCreature* pCreature, void* pTarget,
                             void* pLocation)
{
    cNounManager* pManager = (cNounManager*)NounManager_s00d9_dce0();
    void* pInfo = pManager->GetInfo(pLocation);
    ((cNounManager*)NounManager_s00d9_dce0())->SetInfo(pTarget, pInfo);
}
// ---- items of slice s00d9dce0 end

// ---- items of slice s00da6880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_f147c218;          // 0x0147c218
extern const float g_f147c21c;          // 0x0147c21c
extern const float g_f1473c70;          // 0x01473c70 duration (20.0f), next to the 0x0147c21c family
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
    void    FUN_c14750(bool a);                                  // 0x00c14750
    void    FUN_c279a0(int a);                                   // 0x00c279a0
    void    SetCurrentToolEffect(int a, int b);                  // 0x00c24f40
    void    ForceOrdersUpdate();                                 // 0x00c26450
    void    MoveToPointAtSpeed(int a, void* p, float b, float c);// 0x00c1c1d0
    char    AnimationFinished(u32 id);                           // 0x00c12400
};
extern const u32   g_a147c220[10];      // 0x0147c220 tool-type table
void  __cdecl FUN_00b81780(void* model);                        // 0x00b81780 MakeRandomWorldPosition
struct MoveGoal {                                                // FUN_00c41ec0() result (flags word at +0x70)
    char mPad0[0x70];
    u32 mFlags70;                                                // +0x70
};
// ---- items of slice s00da6880 end

// ---- items of slice s00da7780 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
#pragma pack(push, 1)
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
#pragma pack(pop)
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
    void ReleaseSpot(void* reservation, u32 index); // 0x00c98750
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
struct Elem250 {
    u32   mFlags;                          // +0x00
    void* mpObj;                           // +0x04
    u8    pad_08[0x248];
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
    void  d0c0(u32 a, i32 b);                      // 0x00c0d0c0
    void SetActionLocked(bool locked);             // 0x00c14750
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
typedef void (__thiscall *ElemFn0)(void*, u32);
// ---- items of slice s00da7780 end

// (struct definitions hoisted so VA-ordered functions can use them)
// Retail citizen exposes the combatant as a secondary interface at +0x5a8.
struct StimulusCitizenPrefix {
    virtual void v00();
    char pad004[0x5a8 - 4];
};
struct StimulusCombatantCitizen : StimulusCitizenPrefix, Combatant {};
struct TribeReservationState {
    u32 mState;
    u32 mReservation;
    u32 mUnknown08, mUnknown0c, mUnknown10;
    Creature* mpOwner;
};
struct TribeSpotState {
    u32 mState;
    u32 mUnknown04;
    u32 mIndex;
    void* mpReservation;
};
struct TribeMemberStateInterface {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28();
    virtual int GetState(); // slot 0x2c
};

// ---- items of slice s00da8630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_f400;         // 0x013f0e84  400.0
extern "C" int   g_flag169f3b4;                              // 0x0169f3b4
extern "C" float g_dist169f3b0;                              // 0x0169f3b0
typedef unsigned int   uint;
typedef long double    float10;
struct Vec3 { float x, y, z; };
struct PlayObj {
    void* Play(int a, int flags);                     // 0x00bc96a0 (thiscall)
    void  ClearAll(int a, int flags);                 // 0x00bc98f0 (thiscall)
};
void* GetAny(void* stimuli);                          // 0x00d997e0 (thiscall on stimuli)
struct Stimuli
{
    char  pad00[8];
    void* mp08;                  // +0x08
    char  pad0c[0x18 - 0x0c];
    int   mi18;                  // +0x18
    void  GetAny();              // 0x00d997e0 thiscall
};
void* GetAnimalFromStimulus(void* s);                 // 0x00d99980
struct CreatureBase_s00da_8630 { bool IsSomething(); };          // 0x00c0b780 thiscall -> bool
void* FUN_00d998d0(void* anim, uint id);              // 0x00d998d0
void  FUN_00da6270(int self, int a);                  // 0x00da6270
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
    char     pad38[0xbc - 0x38];
    void*    mpBcu;              // +0xbc
    char     padC0[0x12c - 0xc0];
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

    void* V_Ac() { return ((Fn_p)VT(this, 0xac))(this); }

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

// vtable-only view of an interface object (slot +0x0c returns a C05Result).
struct C05Iface
{
    virtual void  a00();
    virtual void  a04();
    virtual void  a08();
    virtual C05Result* a0c(int id);
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
extern const float kDot01;        // 0x013eb960  0.01f
extern const float kDot001;       // 0x013f9428  0.001f
extern const float kTwo;          // 0x01470f1c  2.0f
extern const float kFive;         // 0x01486110  5.0f
extern uint8_t    DAT_01654c02;   // 0x01654c02
extern "C" void* FUN_00b3d260();                       // 0x00b3d260 BehaviourManager
extern "C" void* __stdcall FUN_00cd3440(uint32_t guid); // 0x00cd3440
extern "C" void* __stdcall FUN_00cd40b0(uint32_t guid); // 0x00cd40b0 Instance
#define PV_s00da_f820(n) virtual void pv##n();
class IWin;
extern IWin*      g_pPropertyMgr; // 0x0158128c
extern "C" double GetPropFloat(IWin* mgr, uint32_t id, float def); // 0x004e1c70 cdecl
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
class cPlanetModel_s00da_f820 : public IWin {
 public:
    void MakeRandomWorldPosition();            // 0x00b81780
};
extern "C" cPlanetModel_s00da_f820* __stdcall PlanetModel(Vector3* out, float* pos, float a, float b); // 0x00b3d350
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
struct HealState {                     // SP::TRIBE_HEAL_SELF_Tick arg 6
    int32_t  m00;                      // +0x00 state
    uint8_t  m04;                      // +0x04
    uint8_t  pad05[3];
    float    m08;                      // +0x08
    cTribe_s00da_f820*  m0c;                      // +0x0c
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
class cBehaviorMgr : public IWin {             // SP::BehaviorManager()
 public:
    PV_s00da_f820(2) PV_s00da_f820(3)
    virtual uint32_t pv4();                    // +0x10
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
extern char   gNounQueryOptions;                              // 0x018ebadc
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
struct cNoun;
}
namespace SP {
struct cNounRange { void* mpOwner; cNoun** mpBegin; cNoun** mpEnd; };
}
namespace SP {
class cGameNounManager_s00db_9380 {
  public:
    cNounRange* GetGameDataList(bool (*pf0)(cNoun*), bool (*pf1)(cNoun*), bool (*pf2)(cNoun*),
                                bool (*pf3)(cNoun*), char* pOptions);   // 0xb21340
};
}
namespace SP {
cGameNounManager_s00db_9380* NounManager_s00db_9380();                              // 0xb3d300
}
namespace SP {
struct cNoun {
    bool IsHealBlocked(int nKind);                            // 0xc38990
    char pad00[0x34];
    Loco_s00db_9380 mSpatial;                                            // +0x34
};
}
namespace SP {
bool NounFilterSpecies(cNoun* pNoun);                         // 0xcd7d10
}
namespace SP {
bool NounFilterAlive(cNoun* pNoun);                           // 0xd3d420
}
namespace SP {
bool NounFilterKind(cNoun* pNoun);                            // 0xad48b0
}
namespace SP {
bool NounFilterStation(cNoun* pNoun);                         // 0xb1e500
}
namespace SP {
struct behavior_stimuli_s00db_9380 {
    void GetAny();                                            // 0xd997e0
    void* mpObject;                                           // +0x00
    void* mpTarget;                                           // +0x04
    char  pad08[0x10];
    int   mnDistance;                                         // +0x18
};
}
namespace SP {
class cActionSystem {
  public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d)
    PV(0e) PV(0f) PV(10) PV(11)
    virtual bool v48(const Vec3_s00db_9380* pPos, float fRadius, void* pOut, int nFlags,
                     float (*pfnSeparation)(Loco_s00db_9380*, Loco_s00db_9380*, int), void* pCreature);   // +0x48
};
}
namespace SP {
cActionSystem* GetActionSystem();                             // 0xb3d240
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
class cSpatialObjectList {
  public:
    void*    mpBegin;                                         // +0x00
    void*    mpEnd;                                           // +0x04
    void*    mpCapacity;                                      // +0x08
    void*    mpField0c;                                       // +0x0c
    void*    mpField10;                                       // +0x10
    unsigned mCount;                                          // +0x14
    void*    mInline[8];                                      // +0x18
};
}
namespace SP {
float GetPropertyT(void* pProperties, unsigned nPropertyId, float fDefault);   // 0x4e1c70
}
namespace SP {
Vec2  GetPropertyAsVector2(void* pProperties, unsigned nPropertyId, Vec2 vDefault); // 0x6a10c0
}
namespace SP {
int   GetTutorialToolPrice(void* pProperties, unsigned nPropertyId, int nDefault); // 0x4e1c30
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
bool  CreatureFlag388(void* pCreature);                       // 0xc0c0e0
}
namespace SP {
bool  CreatureIsIdle(void* pCreature);                        // 0xc0b770
}
namespace SP {
void  CreatureSnapshot(void* pCreature);                      // 0xc0d3a0
}
namespace SP {
void  CreatureSetField(void* pCreature, unsigned nValue);     // 0xc0b370
}
namespace SP {
void* ResolveCreature(void* pHandle);                         // 0xb4d960
}
namespace SP {
void  FUN_00da61e0(cSPCreatureCitizen_s00db_9380* c, int nFx);           // 0xda61e0
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
int   FUN_00bcb660(cCreatureEnv* pEnv, unsigned nEvent);      // 0xbcb660
}
namespace SP {
void  FUN_00c7dc70(void** pBegin, void** pEnd, Vec3_s00db_9380 vPos);    // 0xc7dc70
}
namespace SP {
void  FUN_00ad92d0(void* pVector);                            // 0xad92d0
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

// ---- items of slice s00da5900 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned __int64   u64;
struct Vec3_s00da_5900 { float x, y, z; Vec3_s00da_5900() {} Vec3_s00da_5900(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Quat_s00da_5900 { float x, y, z, w; };
void  __cdecl FUN_00da62d0(void* c, void* tribe, u32 lo, u32 hi);         // 0x00da62d0 (this slice)
void  __cdecl FUN_00da6270(void* c, int order);                           // 0x00da6270 (this slice)
u64   __cdecl FUN_00da6090_s00da_5900(u32 index);            // 0x00da6090 (this slice)
struct cTribe_s00da_5900;
struct cSPCreatureCitizen_s00da_5900;
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
    virtual Vec3_s00da_5900* GetPos();                        // slot +0x2c
    virtual Vec3_s00da_5900* GetDir();                        // slot +0x30
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
    virtual Vec3_s00da_5900* GetPos();                        // +0x2c
    virtual void s12();                            // +0x30
    virtual void s13();                            // +0x34
    virtual void SetFacing(Vec3_s00da_5900* v);               // +0x38
    virtual void SetOrientation(Quat_s00da_5900* q);          // +0x3c
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
    virtual Vec3_s00da_5900* GetPos();                        // +0x2c
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
struct behavior_stimuli_s00da_5900 {
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
struct behavior_stimuli_s00da_5900;
struct cBehaviorTreeData_s00da_5900 {
    char             mPad00[8];
    behavior_stimuli_s00da_5900 mStimuli;                     // +0x08
    char             mPad[0x60c - 0x8 - sizeof(behavior_stimuli_s00da_5900)];
    int*   FirstPending();                         // 0x00bca2c0
    void   PopFront();                             // 0x00bcaf40
    void   OrderOp(AgentNode* node, cSPCreatureCitizen_s00da_5900* c, void* a, void* fn);  // 0x00bcb480
};
struct cSPCreatureCitizen_s00da_5900 {
virtual void v00();
virtual void v01();
virtual void v02();
    virtual cSPCreatureCitizen_s00da_5900* GetByHash(u32 hash);   // +0x0c
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
    cBehaviorTreeData_s00da_5900* mpBTree;                    // +0xb4c
    char               mPadb4c[0xb5e - 0xb4c - 4];
    bool               mbDead;                     // +0xb5e

    cTribe_s00da_5900* GetTribe();                            // 0x00c22f50
    bool    IsLeader();                            // 0x00c232d0
    void    ForceOrdersUpdate();                   // 0x00c26450
    cSPCreatureCitizen_s00da_5900* GetTargetAsCreature();     // 0x00c0ee70
    void    SetInteractionTarget(float f);         // 0x00c0b970
};
struct cTribe_s00da_5900 {
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
// ---- items of slice s00da5900 end

// ---- items of slice s00dadce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Random {
class RandomLinearCongruential_s00da_dce0 {
public:
    uint32_t mnSeed;
    double RandomDoubleUniform();  // 0x009360d0 (EA::Random::RandomLinearCongruential::RandomDoubleUniform)
};
}
}
extern EA::Random::RandomLinearCongruential_s00da_dce0 sMathRandomA;   // 0x1601760
#define VFILL(n) virtual void vs##n() {}
struct RegionOwner {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10) VFILL(11) VFILL(12) VFILL(13) VFILL(14) VFILL(15)
    VFILL(16) VFILL(17) VFILL(18) VFILL(19) VFILL(20) VFILL(21) VFILL(22)
    virtual struct Region* FindRegion(uint32_t key);
};
struct RegionPosition {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10)
    virtual float* GetPosition();
};
struct RegionBase_s00da_dfb0 {                            // primary base, +0x000..+0x5a7
    virtual void v00();
    char pad4[0xc0 - 4];
    RegionPosition sub;                                   // +0xc0
    char pad1[0x5a8 - 0xc0 - sizeof(RegionPosition)];
};
struct RegionTarget_s00da_dfb0 { virtual void v00(); };   // +0x5a8, the interface handed to the host
struct Region : RegionBase_s00da_dfb0, RegionTarget_s00da_dfb0 {};
struct SpawnHost {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10) VFILL(11) VFILL(12) VFILL(13) VFILL(14) VFILL(15)
    VFILL(16) VFILL(17) VFILL(18) VFILL(19) VFILL(20) VFILL(21) VFILL(22) VFILL(23)
    VFILL(24) VFILL(25) VFILL(26) VFILL(27) VFILL(28) VFILL(29) VFILL(30) VFILL(31)
    VFILL(32)
    virtual void Attach(struct RegionTarget_s00da_dfb0* p, bool a, bool b);
};
struct SpawnIn {
    int32_t pad0;
    RegionOwner* owner;                                   // +0x4
    int32_t pad1;
    float x, y, z;                                        // +0xc, +0x10, +0x14
};
struct SpawnOut {
    int32_t zero0;                                        // +0x0
    float radius;                                         // +0x4
    float x, y, z;                                        // +0x8, +0xc, +0x10
    int32_t zero1;                                        // +0x14
};
static double ClampRadius(double v)
{
    if (2.0 <= v)
        return 2.0;
    if (v < 1.0)
        return 1.0;
    return v;
}
namespace SP {
struct Vec3_s00da_dce0 {
    float x, y, z;
};
}
namespace SP {
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
}
namespace SP {
template <class B> struct VPad<0, B> : B {};
}
namespace SP {
extern const float g_1473c70;           // 0x01473c70  10.0  vignette timeout
}
namespace SP {
extern const float g_1486110_s00da_dce0;           // 0x01486110  20.0  attack stimulus value
}
namespace SP {
extern const float g_1470f1c_s00da_dce0;           // 0x01470f1c  2.0   upper bound / speed
}
namespace SP {
extern const float g_1486114;           // 0x01486114  height jitter bound
}
namespace SP {
extern const float g_1485720_s00da_dce0;           // 0x01485720  1.0
}
namespace SP {
extern const float g_147c218_s00da_dce0;           // 0x0147c218  "no target" stimulus value
}
namespace SP {
extern const float g_13ebc4c;           // 0x013ebc4c  60.0  worship stimulus value
}
namespace SP {
float FUN_00572a10(float lo, float hi);                 // 0x00572a10  RandomFloatRange
}
namespace SP {
void* WatchMemoryBlock(uint32_t block);                 // 0x00d999d0
}
namespace SP {
struct RefA {
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3_s00da_dce0* GetPosition();                              // +0x2c
};
}
namespace SP {
struct RefB : VPad<10, RefA> { virtual bool IsAtGoal(); };          // +0x58
}
namespace SP {
struct RefC : VPad<5, RefB> { virtual float GetSpeed(); };          // +0x70
}
namespace SP {
struct RefD : RefC { virtual float GetDistance(); };                // +0x74
}
namespace SP {
struct RefE : VPad<17, RefD> {
    virtual void AddRefBundle();                                    // +0xbc
    virtual void ReleaseBundle();                                   // +0xc0
};
}
namespace SP {
struct RefObj : VPad<10, RefE> { virtual void NotifyEc(); };        // +0xec
}
namespace SP {
struct Loco_s00da_dce0 : RefObj {
    bool IsNearGoal();                                             // 0x00c42e20
    void* FUN_00c420d0();                                          // 0x00c420d0  nearby list
};
}
namespace SP {
struct cTargetV0 { virtual void q00(); };
}
namespace SP {
struct cTargetQuery : VPad<21, cTargetV0> {
    virtual void Query(int* id, int a, int* count, int b);          // +0x58
};
}
namespace SP {
struct cCreatureV0 {
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
    virtual void pv2();                                             // +0x08
    virtual void* GetAnimEvent(uint32_t eventId);                    // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsTargetable();                                    // +0x2c
};
}
namespace SP {
struct cCreatureV1 : VPad<7, cCreatureV0> { virtual void* GetRid(); };            // +0x4c
}
namespace SP {
struct cCreatureV2 : VPad<13, cCreatureV1> {
    virtual void Notify(void* p, int a, int b);                     // +0x84
};
}
namespace SP {
struct cCreatureV3 : VPad<11, cCreatureV2> { virtual void* LookupOrder(uint32_t key); };  // +0xb4
}
namespace SP {
struct cOrderValue {
    uint32_t pad00;                                                 // +0x00
    uint32_t pad04;                                                 // +0x04
    int32_t  mTag;                                                  // +0x08
};
}
namespace SP {
class cAnimNode {                                                   // result of Play()
public:
    uint32_t pad00[3];                                              // +0x00..+0x0b
    int32_t  mKind;                                                 // +0x0c
};
}
namespace SP {
struct BehaviorStimuli_s00da_dce0 {
    cAnimNode* Play(uint32_t id, int flags);                        // 0x00bc96a0
    void       ClearAll(uint32_t a, uint32_t mask);                 // 0x00bc98f0
    void       SetStimulus(uint32_t a, uint32_t b, float f, void* d);   // 0x00bc97f0
};
}
namespace SP {
struct cBundleQuery {                                               // creature +0x34
    void* FUN_00cee330();                                           // 0x00cee330
};
}
namespace SP {
struct cBundleObj {
    uint8_t pad00[0x134];                                           // +0x000..+0x133
    float   mf134;                                                  // +0x134
};
}
namespace SP {
struct cSPTimer_s00da_dce0 {                                                   // creature +0xfd0
    void Restart();                                                 // 0x00bc3130
};
}
namespace SP {
struct cTribe_s00da_dce0;
}
namespace SP {
struct cTribeVec;
}
namespace SP {
struct cOrderNode;
}
namespace SP {
struct cAgentOrder_s00da_dce0;
}
namespace SP {
struct nSPBehaviorTree;
}
namespace SP {
struct cArtifact;
}
namespace SP {
class cSPCreatureBase_s00da_dce0 : public cCreatureV3 {
public:
    uint32_t pad04[(0x34 - 4) / 4];                                 // +0x004..+0x033
    cBundleQuery mBundle;                                           // +0x034
    uint8_t  pad35[0xc0 - 0x35];                                    // +0x035..+0x0bf
    Loco_s00da_dce0     mLoco;                                                 // +0x0c0
    uint8_t  padC4[0x135 - 0xc4];                                   // +0x0c4..+0x134
    uint8_t  mb135;                                                 // +0x135  targetable flag
    uint8_t  pad136[0x5a8 - 0x136];                                 // +0x136..+0x5a7
    uint8_t  mb5a8;                                                 // +0x5a8  handed to Notify
    uint8_t  pad5a9[0xb4c - 0x5a9];                                 // +0x5a9..+0xb4b
    nSPBehaviorTree* mpBehavior;                                    // +0xb4c
    uint32_t padB50;                                                // +0xb50
    cTargetQuery* mpB54;                                            // +0xb54
    uint8_t  padB58[0xfd0 - 0xb58];                                 // +0xb58..+0xfcf
    cSPTimer_s00da_dce0 mTimer;                                                // +0xfd0

    char     FUN_00c0e0c0(uint32_t id);                             // 0x00c0e0c0
    void     FUN_00c0d0c0(uint32_t a, char b);                      // 0x00c0d0c0
    void*    GetTargetAsCreature();                                 // 0x00c0ee70
    bool     AnimationFinished(uint32_t handle);                    // 0x00c12400
    uint32_t PlayAnimationWithTargetObj(uint32_t id, void* target, int a, int b);    // 0x00c14940
    uint32_t InterruptAnimationWithTargetObj(uint32_t id, void* target, int a, int b); // 0x00c149c0
    void     MoveToPointAtSpeed(int mode, const Vec3_s00da_dce0* pos, float a, float b);        // 0x00c1c1d0
    void     ForceOrdersUpdate();                                   // 0x00c26450
    cTribe_s00da_dce0*  GetTribe();                                            // 0x00c22f50
    bool     IsLeader();                                            // 0x00c232d0
};
}
namespace SP {
struct cTribeVec {                                                  // {begin, end} of dwords
    uint32_t* begin;
    uint32_t* end;
};
}
namespace SP {
struct cSlotObjBase {
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
    virtual void* Slot2c(void* a);                                  // +0x2c
};
}
namespace SP {
struct cSlotObj : VPad<11, cSlotObjBase> {
    virtual void* Slot5c(void* out);                                // +0x5c
};
}
namespace SP {
struct cTribeV0 { virtual void t00(); };
}
namespace SP {
struct cTribe_s00da_dce0 : VPad<35, cTribeV0> {
    uint32_t pad04[(0x120 - 4) / 4];                                // +0x004..+0x11f
    cSlotObj mSub;                                                  // +0x120
    uint8_t  pad124[0x20c - 0x124];                                 // +0x124..+0x20b
    uint8_t  m20c;                                                  // +0x20c
    uint8_t  pad20d[0x26c - 0x20d];                                 // +0x20d..+0x26b
    int32_t  m26c;                                                  // +0x26c  cached vignette id

    virtual cTribeVec* GetMembers();                                // +0x90 0x00c8e810
    void FUN_00c94b50(float v);                                     // 0x00c94b50
};
}
namespace SP {
struct cVecRange {                                                  // generic {begin, end}
    uint32_t* begin;
    uint32_t* end;
};
}
namespace SP {
struct cListItemV0 { virtual void q00(); };
}
namespace SP {
struct cListItem : VPad<45, cListItemV0> {
    virtual void* Query(uint32_t id);                               // +0xb8
};
}
namespace SP {
struct cArtifactV0 {
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
};
}
namespace SP {
struct cArtifact : cArtifactV0 {
    uint8_t  pad04[0x34 - 4];                                       // +0x004..+0x033
    cSlotObj mSub;                                                  // +0x034
    uint8_t  pad35[0xab - 0x35];                                    // +0x035..+0x0aa
    uint8_t  mbab;                                                  // +0x0ab

    bool IsRare();                                                  // 0x00c74ca0
};
}
namespace SP {
class cOrderNode {
public:
    uint32_t  pad00[4];                                             // +0x000..+0x00f
    int       mState;                                               // +0x010
    uint8_t   pad14[0x1a0 - 0x14];                                  // +0x014..+0x19f
    cArtifact* mpObject;                                            // +0x1a0

    uint32_t GetId1(int a);                                         // 0x00bc9be0  (ret 4)
    uint32_t GetId3(int a, void* b, int c);                         // 0x00bc9be0  (ret 0xc)
    bool     IsDone();                                              // 0x00bc9b50
    void     FUN_00bc9bf0(int a, void* b);                          // 0x00bc9bf0  (ret 8)
};
}
namespace SP {
struct cOrderPayload {
    uint32_t mValue;                                                // +0x00
    uint8_t  pad04[0x10 - 4];                                       // +0x04..+0x0f
    uint8_t  mFlags10;                                              // +0x10  pointer/value tag bits
    uint8_t  pad11;                                                 // +0x11
    uint16_t mTag12;                                                // +0x12
    uint32_t* FUN_005727b0();                                       // 0x005727b0 (thiscall)
};
}
namespace SP {
#pragma pack(push, 1)
struct cAgentOrder_s00da_dce0 {
    uint32_t mTag;                                                  // +0x00  0x16 = order record
    uint8_t  pad04[0x39 - 4];                                       // +0x04..+0x38
    cOrderPayload mPayload;                                         // +0x39
};
#pragma pack(pop)
}
namespace SP {
class cAgentOrderManager_s00da_dce0 {
public:
    cOrderNode* FindNode(uint32_t id, void* fn, cSPCreatureBase_s00da_dce0* c);                 // 0x00bca620
    cOrderNode* CreateNode(uint32_t id, int count, uint32_t token, const char* name); // 0x00bcb0b0
};
}
namespace SP {
cAgentOrderManager_s00da_dce0* GetOrderManager();                              // 0x00bc9b00
}
namespace SP {
struct nSPBehaviorTree {
    uint32_t pad00[2];                                              // +0x000..+0x007
    BehaviorStimuli_s00da_dce0 mStimuli;                                       // +0x008
    uint8_t  pad0c[0x600 - 0x0c];                                   // +0x00c..+0x5ff
    cOrderNode* mpNode;                                             // +0x600
    int32_t  m604;                                                  // +0x604

    cAgentOrder_s00da_dce0* FirstPending();                                    // 0x00bca2c0
    void Attach(void* node, cSPCreatureBase_s00da_dce0* c, void* block, void* fn);  // 0x00bcb480
    void Refresh();                                                 // 0x00bcb430
};
}
namespace SP {
struct cSomeMgr {
    cVecRange* FUN_00bc7610(uint32_t key, int zero);                // 0x00bc7610 (ret 8)
    uint32_t   FUN_00bc65f0();                                      // 0x00bc65f0
    bool       FUN_00bc3df0(uint32_t id);                           // 0x00bc3df0 (ret 4)
    void       FUN_00bc5040(uint32_t id);                           // 0x00bc5040 (ret 4)
    uint32_t   FUN_00bc4900(uint32_t id);                           // 0x00bc4900 (ret 4)
    uint32_t   FUN_00bc4900(void* id, void* c, uint32_t flagWord);  // 0x00bc4900 (ret 0xc)
    uint32_t   FUN_00bc64a0(uint32_t a, uint32_t b, void* x, void* y);  // 0x00bc64a0
    int32_t    FUN_00bc3db0(uint32_t x);                            // 0x00bc3db0
};
}
namespace SP {
cSomeMgr* FUN_00b3d4e0_a();                                          // (no stack args)
}
namespace SP {
cSomeMgr* FUN_00b3d4e0_b();                                          // (no stack args)
}
namespace SP {
cSomeMgr* FUN_00b3d4e0_d();                                          // (no stack args)
}
namespace SP {
struct cRelationshipMgr {
    uint32_t FUN_00d00a70(uint32_t a, uint32_t b, int one);         // 0x00d00a70
};
}
namespace SP {
cRelationshipMgr* FUN_00b3d2c0_s00da_dce0();                                   // 0x00b3d2c0
}
namespace SP {
struct cEconomyMgr {
    void FUN_00ac7eb0(void* a, void* b);                            // 0x00ac7eb0
};
}
namespace SP {
cEconomyMgr* FUN_00b3d2b0_s00da_dce0();                                        // 0x00b3d2b0
}
namespace SP {
struct cSlotFiller {
    void FillSlots();                                               // 0x00b033b0
};
}
namespace SP {
cSlotFiller* __stdcall FUN_00b3d440(void* p);                       // 0x00b3d440
}
namespace SP {
struct cPlanetQuery {
    void FUN_00b45410();                                            // 0x00b45410
};
}
namespace SP {
cPlanetQuery* __stdcall FUN_00b3d310_s00da_dce0(void* p);                      // 0x00b3d310
}
namespace SP {
void FUN_00da80f0();                                                // 0x00da80f0  worship order fn
}
namespace SP {
struct AwarenessAttackBlock {                                       // attack tick / deactivate
    uint32_t mId;                                                   // +0x00
    int32_t  mCount;                                                // +0x04
};
}
namespace SP {
struct GreetBlock {                                                 // AWARENESS_GREET
    uint32_t mOrder;                                                // +0x00
};
}
namespace SP {
struct ChaseBlock {                                                 // pursuit of one target
    uint32_t mState;                                                // +0x00
    float    mfTimer;                                               // +0x04
    Vec3_s00da_dce0     mPos;                                                  // +0x08
    uint32_t mHandle;                                               // +0x14
};
}
namespace SP {
struct VignetteBlock {
    float    mfTimeout;                                             // +0x00
    uint8_t  mb4;                                                   // +0x04
    uint8_t  pad5[3];                                               // +0x05
    int32_t  mVignette;                                             // +0x08
};
}
namespace SP {
struct DomesticationBlock {
    uint32_t mId;                                                   // +0x00
    uint8_t  mb4;                                                   // +0x04
    uint8_t  pad5[3];                                               // +0x05
};
}
namespace SP {
struct VignetteRequest {
    uint8_t  pad00[0x18];                                           // +0x00..+0x17
    uint32_t mIndex;                                                // +0x18
    uint32_t mKey;                                                  // +0x1c
};
}
namespace SP {
struct SlotList {                                                   // +0x14 begin, +0x18 end
    uint8_t  pad00[0x14];                                           // +0x00..+0x13
    uint32_t* mpBegin;                                              // +0x14
    uint32_t* mpEnd;                                                // +0x18
};
}
namespace SP {
extern const uint32_t g_15d1164;        // 0x015d1164  default order payload word
}
namespace SP {
struct OrderValueBlock {
    uint32_t mValue;                                                // +0x00
    uint32_t mZero4;                                                // +0x04
    uint32_t mZero8;                                                // +0x08
};
}
// ---- items of slice s00dadce0 end

// ---- items of slice s00db0130 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_pProps1581288;                          // 0x1581288
extern const float kF13ebc5c;                          // 0x013ebc5c
extern const float kF147c218;                          // 0x0147c218
struct Vec3_s00db_0130 { float x, y, z; Vec3_s00db_0130() {} Vec3_s00db_0130(float a, float b, float c) : x(a), y(b), z(c) {} };
#define PV_s00db_0130(n) virtual void pv##n();
struct IRef { virtual void AddRef(); virtual void Release(); };
struct Spatial_s00db_0130 {
    PV_s00db_0130(0) PV_s00db_0130(1) PV_s00db_0130(2) PV_s00db_0130(3) PV_s00db_0130(4) PV_s00db_0130(5) PV_s00db_0130(6) PV_s00db_0130(7) PV_s00db_0130(8) PV_s00db_0130(9) PV_s00db_0130(10)
    virtual const Vec3_s00db_0130* GetPosition();                 // +0x2c
    PV_s00db_0130(12) PV_s00db_0130(13) PV_s00db_0130(14) PV_s00db_0130(15) PV_s00db_0130(16) PV_s00db_0130(17) PV_s00db_0130(18) PV_s00db_0130(19) PV_s00db_0130(20) PV_s00db_0130(21)
    virtual bool vf58();                               // +0x58
    virtual const Vec3_s00db_0130* GetOffset(Vec3_s00db_0130* out);          // +0x5c
    PV_s00db_0130(24) PV_s00db_0130(25) PV_s00db_0130(26) PV_s00db_0130(27) PV_s00db_0130(28)
    virtual float GetRadius();                         // +0x74
    char* __thiscall FUN_00cee330();                   // bundle query: returns the first bundle entry or 0
};
struct IWinTextHolder {                                // EA::AutoRefCount<...> out of line operator=
    IRef* mp;
    void __thiscall Assign(IRef* p);                   // 0x00b5f950, ret 4
};
struct TargetHolder {
    IRef* mp;
    void __thiscall Assign(void* p);                   // 0x00c35d50, ret 4
};
struct Tribe_s00db_0130 {
    PV_s00db_0130(0) PV_s00db_0130(1) PV_s00db_0130(2) PV_s00db_0130(3) PV_s00db_0130(4) PV_s00db_0130(5) PV_s00db_0130(6) PV_s00db_0130(7) PV_s00db_0130(8) PV_s00db_0130(9) PV_s00db_0130(10) PV_s00db_0130(11) PV_s00db_0130(12) PV_s00db_0130(13)
    PV_s00db_0130(14) PV_s00db_0130(15) PV_s00db_0130(16) PV_s00db_0130(17) PV_s00db_0130(18) PV_s00db_0130(19) PV_s00db_0130(20) PV_s00db_0130(21) PV_s00db_0130(22) PV_s00db_0130(23) PV_s00db_0130(24)
    virtual void vf64();                               // +0x64
    uint32_t pad04[(0x120 - 4) / 4];
    Spatial_s00db_0130  mPos;                                     // +0x120
    uint32_t pad124[(0x260 - 0x124) / 4];
    struct Obj260* mpObj;                              // +0x260
    uint32_t pad264[1];
    float    mfRadius;                                 // +0x268
    Vec3_s00db_0130* __thiscall FUN_00c91190(Vec3_s00db_0130* out, int a);   // ret 8
};
struct Obj260 {
    uint32_t pad[0x34 / 4];
    Spatial_s00db_0130  mSpatial;                                 // +0x34
};
struct AnimCtl_s00db_0130 {
    void* __thiscall PlayIdleAnimation(unsigned id, int a);        // 0x00bc96a0, ret 8
    void  __thiscall FUN_00bc97f0(int a, int b, float c, int d);   // ret 0x10
};
struct GiftTask;
struct Citizen_s00db_0130;
struct AnimOwner_s00db_0130 {
    uint32_t pad[2];
    AnimCtl_s00db_0130  mCtl;                                     // +8
    void __thiscall FUN_00bcb480(GiftTask* t, Citizen_s00db_0130* c, int a, int b);   // ret 0x10
};
struct MgrB48 {
    void __thiscall FUN_00bca810(int a, int b, Citizen_s00db_0130* c, float f, int d, int e);   // ret 0x18
};
struct Citizen_s00db_0130 {
    PV_s00db_0130(0) PV_s00db_0130(1) PV_s00db_0130(2) PV_s00db_0130(3) PV_s00db_0130(4) PV_s00db_0130(5) PV_s00db_0130(6) PV_s00db_0130(7) PV_s00db_0130(8) PV_s00db_0130(9) PV_s00db_0130(10) PV_s00db_0130(11) PV_s00db_0130(12) PV_s00db_0130(13)
    PV_s00db_0130(14) PV_s00db_0130(15) PV_s00db_0130(16) PV_s00db_0130(17) PV_s00db_0130(18) PV_s00db_0130(19) PV_s00db_0130(20) PV_s00db_0130(21) PV_s00db_0130(22) PV_s00db_0130(23) PV_s00db_0130(24) PV_s00db_0130(25) PV_s00db_0130(26)
    PV_s00db_0130(27) PV_s00db_0130(28) PV_s00db_0130(29) PV_s00db_0130(30) PV_s00db_0130(31) PV_s00db_0130(32)
    virtual void vf84(void* part, int a, int b);       // +0x84
    Tribe_s00db_0130* __thiscall GetTribe();                      // 0x00c22f50
    uint32_t pad04[(0x34 - 4) / 4];
    Spatial_s00db_0130  mBundle;                                  // +0x34
    uint32_t pad38[(0xc0 - 0x38) / 4];
    Spatial_s00db_0130  mLoco;                                    // +0xc0
    uint32_t padc4[(0xb48 - 0xc4) / 4];
    MgrB48*    mpB48;                                  // +0xb48
    AnimOwner_s00db_0130* mpAnim;                                 // +0xb4c
};
struct Target {
virtual void AddRef();
virtual void Release();
    uint32_t pad04[(0x34 - 4) / 4];
    Spatial_s00db_0130  mSpatial;                                 // +0x34
    uint32_t pad38[(0x128 - 0x38) / 4];
    void*    mp128;                                    // +0x128
};
struct TargetQuery {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual IRef* Query(uint32_t id);                  // +0xc
};
struct ParamObj {
    uint32_t pad[2];
    TargetQuery* mpQuery;                              // +8
};
struct EffectCircle {                                  // 100 bytes, "Simulator/GiftActionCircle"
    uint32_t data[25];
    EffectCircle();                                    // 0x00afba10
    void __thiscall FUN_00af9cf0(const Vec3_s00db_0130* p, float r, const Vec3_s00db_0130* dir, float z);   // ret 0x10
    void __thiscall FUN_00afef10(int a, float s);      // ret 8
};
void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
struct TaskBase0 {
    uint32_t pad0[6];
    int      mCount;                                   // +0x18
    uint32_t pad1c[(0x1a4 - 0x1c) / 4];
    void __thiscall FUN_00bc9b20(Citizen_s00db_0130* c);          // ret 4
};
struct GiftBase {                                      // sub-object at +0x1a4
    Vec3_s00db_0130  pos;                                         // +0
    Vec3_s00db_0130  dir;                                         // +0xc
    int   mi18;
    float f1c;
    bool  mbFlag;                                      // +0x20
    EffectCircle* mpEffect;                            // +0x24
    uint32_t pad28;
    IRef* mpTribe;                                     // +0x2c
    Citizen_s00db_0130* mpOther;                                  // +0x30
};
struct GiftTask : TaskBase0 {
    GiftBase mGift;                                    // +0x1a4
};
struct TaskMgr_s00db_0130 {
    GiftTask* __thiscall Find(uint32_t kind, void* fn, void* key);                          // 0x00bca620, ret 0xc
    GiftTask* __thiscall Create(uint32_t kind, int n, void* p, const char* name);           // 0x00bcb0b0, ret 0x10
};
TaskMgr_s00db_0130* __cdecl FUN_00bc9b00_s00db_0130();
struct Mgr1 {
    void* __thiscall FUN_00ac79d0();
    void  __thiscall FUN_00ac7de0(void* a, void* b);   // ret 8
};
Mgr1* __cdecl FUN_00b3d2b0_s00db_0130();
struct cPlanetModel_s00db_0130 {
    Vec3_s00db_0130* __thiscall DirectionToSurfacePosition(Vec3_s00db_0130* out, const Vec3_s00db_0130* dir);   // 0xB815A0
};
struct GiftState {                                     // behaviour state block
    int            mDone;                              // +0
    IWinTextHolder mHolder4;                           // +4
    Tribe_s00db_0130*         mpTribe;                            // +8 (an AutoRefCount in the source)
    Citizen_s00db_0130*       mpCitizen;                          // +0xc
    Target*        mpTarget;                           // +0x10
    TargetHolder   mHolder14;                          // +0x14
    Vec3_s00db_0130           mTargetPos;                         // +0x18
    int            mi24;
    uint32_t       pad28[(0x34 - 0x28) / 4];
    float          mf34;
};
namespace SP {
cPlanetModel_s00db_0130* __cdecl PlanetModel_s00db_0130();                   // 0xB3D350
}
namespace SP {
Vec3_s00db_0130* __cdecl normalized_safe_s00db_0130(Vec3_s00db_0130* out, const Vec3_s00db_0130* in);   // 0x449C20
}
namespace SP {
bool __cdecl TRIBE_NPC_GIFT_Activate(Citizen_s00db_0130* c, int p2, int p3, int p4, int p5, GiftState* st, ParamObj* prm);
}
Vec3_s00db_0130* __cdecl Vector3_Normalize(Vec3_s00db_0130* out, const Vec3_s00db_0130* in);   // 0x436CE0
IRef* __cdecl FUN_00d998d0_s00db_0130(void* obj, uint32_t id);
float __cdecl GetPropertyFloat(void* props, unsigned id, float def);   // 0x004e1c70
void __cdecl FUN_00d9aa20(EffectCircle* e);
static inline Vec3_s00db_0130 operator-(const Vec3_s00db_0130& a, const Vec3_s00db_0130& b) { return Vec3_s00db_0130(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vec3_s00db_0130 operator*(const Vec3_s00db_0130& a, float k) { return Vec3_s00db_0130(a.x * k, a.y * k, a.z * k); }
static inline void AssignRef(IRef*& slot, IRef* p)
{
    IRef* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}
// ---- items of slice s00db0130 end

// ---- items of slice s00db10d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float k169f3b8, k169f3bc, k169f3c0;        // default facing
extern const float k1470f1c;
extern const float k13ec4b4;
extern const float k147c218;
extern const float k1485378;
extern const float k1473c70;
extern float       k157206c, k1572070;
extern void*       g_p1e1c;                            // 0x0158128c
extern const char  kDomesticate[];                     // 0x0147c260
extern float       k1485720;                           // 0x01485720
#define PV_s00db_10d0(n) virtual void pv##n();
struct Vec3_s00db_10d0 { float x, y, z; Vec3_s00db_10d0() {} Vec3_s00db_10d0(float a, float b, float c) : x(a), y(b), z(c) {} };
struct VAny {
    virtual IRef* AddRef0();                           // 0x00
    virtual void  Rel4();                              // 0x04
    PV_s00db_10d0(2)
    virtual IRef* Query0c(uint32_t id);                // 0x0c
    PV_s00db_10d0(4)
    virtual IRef* Query14(uint32_t id);                // 0x14
    virtual void  AddRef18();                          // 0x18
    virtual void  Rel1c();                             // 0x1c
    PV_s00db_10d0(8) PV_s00db_10d0(9) PV_s00db_10d0(10)
    virtual void* Call2c();                            // 0x2c
    virtual void* Call30();                            // 0x30
    PV_s00db_10d0(13)
    virtual float Call38(int a);                       // 0x38
    PV_s00db_10d0(15) PV_s00db_10d0(16) PV_s00db_10d0(17) PV_s00db_10d0(18) PV_s00db_10d0(19) PV_s00db_10d0(20) PV_s00db_10d0(21) PV_s00db_10d0(22)
    virtual IRef* Query5c(uint32_t id);                // 0x5c
    PV_s00db_10d0(24) PV_s00db_10d0(25) PV_s00db_10d0(26) PV_s00db_10d0(27) PV_s00db_10d0(28)
    virtual float GetRadius();                         // 0x74
    PV_s00db_10d0(30) PV_s00db_10d0(31) PV_s00db_10d0(32) PV_s00db_10d0(33) PV_s00db_10d0(34) PV_s00db_10d0(35) PV_s00db_10d0(36) PV_s00db_10d0(37) PV_s00db_10d0(38) PV_s00db_10d0(39)
    PV_s00db_10d0(40) PV_s00db_10d0(41) PV_s00db_10d0(42) PV_s00db_10d0(43) PV_s00db_10d0(44) PV_s00db_10d0(45) PV_s00db_10d0(46) PV_s00db_10d0(47) PV_s00db_10d0(48) PV_s00db_10d0(49)
    PV_s00db_10d0(50) PV_s00db_10d0(51) PV_s00db_10d0(52) PV_s00db_10d0(53) PV_s00db_10d0(54)
    virtual void  CallDc(void* p);                     // 0xdc
    PV_s00db_10d0(56) PV_s00db_10d0(57) PV_s00db_10d0(58)
    virtual void  CallEc();                            // 0xec
};
struct VSpatial {
    PV_s00db_10d0(0) PV_s00db_10d0(1) PV_s00db_10d0(2) PV_s00db_10d0(3) PV_s00db_10d0(4) PV_s00db_10d0(5) PV_s00db_10d0(6) PV_s00db_10d0(7) PV_s00db_10d0(8) PV_s00db_10d0(9) PV_s00db_10d0(10)
    virtual const Vec3_s00db_10d0* GetPosition();                 // +0x2c
    PV_s00db_10d0(12) PV_s00db_10d0(13) PV_s00db_10d0(14) PV_s00db_10d0(15) PV_s00db_10d0(16) PV_s00db_10d0(17) PV_s00db_10d0(18) PV_s00db_10d0(19) PV_s00db_10d0(20) PV_s00db_10d0(21)
    virtual bool vf58();                               // +0x58
    virtual const Vec3_s00db_10d0* GetOffset(Vec3_s00db_10d0* out);          // +0x5c
    PV_s00db_10d0(24) PV_s00db_10d0(25) PV_s00db_10d0(26) PV_s00db_10d0(27) PV_s00db_10d0(28)
    virtual float GetRadius();                         // +0x74
    PV_s00db_10d0(30) PV_s00db_10d0(31) PV_s00db_10d0(32) PV_s00db_10d0(33) PV_s00db_10d0(34) PV_s00db_10d0(35) PV_s00db_10d0(36) PV_s00db_10d0(37) PV_s00db_10d0(38) PV_s00db_10d0(39)    PV_s00db_10d0(40) PV_s00db_10d0(41) PV_s00db_10d0(42) PV_s00db_10d0(43) PV_s00db_10d0(44) PV_s00db_10d0(45) PV_s00db_10d0(46) PV_s00db_10d0(47) PV_s00db_10d0(48) PV_s00db_10d0(49)
    PV_s00db_10d0(50) PV_s00db_10d0(51) PV_s00db_10d0(52) PV_s00db_10d0(53) PV_s00db_10d0(54)
    virtual void vfDC(void* p);                        // +0xdc
    PV_s00db_10d0(56) PV_s00db_10d0(57) PV_s00db_10d0(58)
    virtual void vfEC();                               // +0xec
    int    __thiscall IsNearGoal();                    // 0x00c42e20
};
struct VLoco : VSpatial { uint32_t pad[(0xc0 - sizeof(VSpatial)) / 4]; };
struct Bundle { uint32_t mDummy; char* __thiscall Get(); };   // 0x00cee330
struct Stimuli_s00db_10d0 {                                       // nSPBehaviorTree behaviour stimuli, at Omgr+8
    void* __thiscall Play(unsigned id, int a);         // 0x00bc96a0
    void  __thiscall ClearAll(int a, int b);           // 0x00bc98f0
};
struct Citizen_s00db_10d0;
struct OrderMgr {
    void  __thiscall FUN_00bcb430();                                   // 0x00bcb430
    void* __thiscall FindNode(int kind, void* fn, Citizen_s00db_10d0* c);         // 0x00bca620
    void* __thiscall Create(int kind, int n, int p, const char* name); // 0x00bcb0b0
    void  __thiscall FUN_00bcb480(void* order, Citizen_s00db_10d0* c, int a, int b);// 0x00bcb480
    void* __thiscall FirstPending();                                   // 0x00bca2c0
    uint32_t pad0[2];
    Stimuli_s00db_10d0 mStimuli;                                  // +8
};
struct GC { void* mp; };
struct Mgr {
    uint32_t pad[0x1c / 4];
    void*    mp1c;
    GC*  __thiscall GetContainer();                    // 0x00ac79d0
    void __thiscall FUN_00ac7de0(void* a, void* b);    // 0x00ac7de0
    void __thiscall FUN_00ac79e0(void* a, void* b);    // 0x00ac79e0
    void __thiscall FUN_00ac7ab0(float f, void* a, int b);  // 0x00ac7ab0
    void*    mp20[8];
};
Mgr* __cdecl Ctx();                                    // 0x00b3d2b0
struct Tribe_s00db_10d0;
struct Citizen_s00db_10d0 {
    virtual void AddRef();
    virtual void Release();
    PV_s00db_10d0(0) PV_s00db_10d0(1) PV_s00db_10d0(2) PV_s00db_10d0(3) PV_s00db_10d0(4) PV_s00db_10d0(5) PV_s00db_10d0(6) PV_s00db_10d0(7) PV_s00db_10d0(8) PV_s00db_10d0(9) PV_s00db_10d0(10) PV_s00db_10d0(11) PV_s00db_10d0(12) PV_s00db_10d0(13)
    PV_s00db_10d0(14) PV_s00db_10d0(15) PV_s00db_10d0(16) PV_s00db_10d0(17) PV_s00db_10d0(18) PV_s00db_10d0(19) PV_s00db_10d0(20) PV_s00db_10d0(21) PV_s00db_10d0(22) PV_s00db_10d0(23) PV_s00db_10d0(24) PV_s00db_10d0(25) PV_s00db_10d0(26)
    PV_s00db_10d0(27) PV_s00db_10d0(28) PV_s00db_10d0(29) PV_s00db_10d0(30)
    virtual void vf84(void* part, int a, int b);       // +0x84
    virtual void vf88();
    virtual void vf8c();
    virtual void vf90();
    uint32_t pad04[(0x34 - 4) / 4];
    Bundle   mBundle;                                  // +0x34
    uint32_t pad38[(0xc0 - 0x38) / 4];
    VLoco    mLoco;                                    // +0xc0 (0xc0 bytes, locomotive object)
    uint32_t pad180[(0xb48 - 0x180) / 4];
    void*    mpB48;                                    // +0xb48
    OrderMgr* mpOrderMgr;                              // +0xb4c
    Citizen_s00db_10d0* mpb50;                                    // +0xb50
    uint32_t padb54[1];
    uint8_t  mb58[6];                                  // +0xb58
    uint8_t  mb5e;                                     // +0xb5e
    uint32_t padb5f[(0xfc4 - 0xb5f) / 4];
    void*    mpFC4;                                    // +0xfc4
    void*    mpFC8;                                    // +0xfc8
    uint32_t padfcc[(0x1002 - 0xfcc) / 4];
    uint8_t  mb1002;                                   // +0x1002
    uint32_t pad1003[(0x1004 - 0x1003)];
    Vec3_s00db_10d0     m1004;                                    // +0x1004
    uint32_t pad1010[(0x1014 - 0x1010) / 4];
    int      m1014;                                    // +0x1014

    Tribe_s00db_10d0* __thiscall GetTribe();                      // 0x00c22f50
    void   __thiscall FUN_00c0d0c0(unsigned a, unsigned b);  // 0x00c0d0c0
    void   __thiscall InterruptAnimation(uint32_t a, int b, int c);  // 0x00c12310
    void   __thiscall FUN_00c14750(int a);             // 0x00c14750
    void   __thiscall FUN_00c26c80();                  // 0x00c26c80
    void*  __thiscall FUN_00c23750();                  // 0x00c23750
    void   __thiscall SetStealthed(int a, int b);      // 0x00c1aed0
    void   __thiscall SetSprinting(int a);             // 0x00c1ad10
    uint8_t __thiscall OrdersLocked();                 // 0x00c22850
    void   __thiscall SetOrdersLocked(char b);         // 0x00c22860
    void   __thiscall SetFacing(float x, float y, float z);  // 0x00c227f0
    void   __thiscall FUN_00c23300(void* bundle, int a);     // 0x00c23300
    void   __thiscall FUN_00c25f80();                  // 0x00c25f80
    int    __thiscall FUN_00c25480(int a, int b);      // 0x00c25480
    void   __thiscall ForceOrdersUpdate();             // 0x00c26450
    void   __thiscall MoveToPointAtSpeed(int a, void* p, float x, float y);  // 0x00c1c1d0
    void   __thiscall MoveToPointAndFacingAtSpeed(int a, void* p, void* r, int b, int c);  // 0x00c1c5c0
    void   __thiscall FUN_00c14990(uint32_t a, void* p, int b);     // 0x00c14990
    int    __thiscall WaitForAnimEventOrEnd(uint32_t a, void* out, int b, int c, int d);  // 0x00c14ef0
    void   __thiscall FUN_00c950f0(Citizen_s00db_10d0* c);        // 0x00c950f0
};
struct Tribe_s00db_10d0 {
    PV_s00db_10d0(0) PV_s00db_10d0(1) PV_s00db_10d0(2) PV_s00db_10d0(3) PV_s00db_10d0(4) PV_s00db_10d0(5) PV_s00db_10d0(6) PV_s00db_10d0(7) PV_s00db_10d0(8) PV_s00db_10d0(9) PV_s00db_10d0(10) PV_s00db_10d0(11) PV_s00db_10d0(12) PV_s00db_10d0(13)
    PV_s00db_10d0(14) PV_s00db_10d0(15)
    void* __thiscall GetToolOfType(int type);          // 0x00c8f6e0
    void  __thiscall FindSpot(int type, int id);       // 0x00c98750
    void  __thiscall ReleaseSpot(int type, void* ref);// 0x00c97d40
};
struct StEat {
    int      m00;      // +0x00
    Citizen_s00db_10d0* mp04;     // +0x04
    int      m08;      // +0x08
    IRef*    mp0c;     // +0x0c
    IRef*    mp10;     // +0x10
    IRef*    mp14;     // +0x14
    IRef*    mp18;     // +0x18
    float    mf1c;     // +0x1c
    uint8_t  mb20;     // +0x20
    uint8_t  pad21[3];
    Vec3_s00db_10d0     vec24;    // +0x24
    int      m30;      // +0x30
    float    mf34;     // +0x34
};
struct StEatD {
    int      m00;      // +0x00
    Citizen_s00db_10d0* mp04;     // +0x04
    int      m08;      // +0x08
    Citizen_s00db_10d0* mp0c;     // +0x0c
    IRef*    mp10;     // +0x10
    IRef*    mp14;     // +0x14
    IRef*    mp18;     // +0x18
    float    mf1c;     // +0x1c
    int      m20;      // +0x20
    Vec3_s00db_10d0     vec24;    // +0x24
    int      m30;      // +0x30
    float    mf34;     // +0x34
};
struct StOrders {
    int      m00;      // +0x00
    float    mf04;     // +0x04
    float    mf08;     // +0x08
    IRef*    mp0c;     // +0x0c
    IRef*    mp10;     // +0x10
    Vec3_s00db_10d0     vec14;    // +0x14
};
struct StTool {
    int      m00;      // +0x00
    void*    mp04;     // +0x04
    int      m08;      // +0x08
    int      m0cTool;  // +0x0c
    Vec3_s00db_10d0     vec10;    // +0x10
};
struct StDom {
    int      m00;      // +0x00
    void*    mp04;     // +0x04
    int      m08;      // +0x08
    Citizen_s00db_10d0* mp0c;     // +0x0c
};
struct ParamObj_s00db_10d0 {
    uint32_t    m0;                                    // +0x00
    VAny*       mp4;                                   // +0x04
    VAny*       mp8;                                   // +0x08
    uint32_t    padc;
    uint32_t    mp18;                                  // +0x18
};
int   __cdecl FUN_00d998d0_s00db_10d0(void* p, uint32_t id);      // 0x00d998d0
void* __cdecl FUN_00d99980(void* p);                   // 0x00d99980
int   __cdecl FUN_00da6270(Citizen_s00db_10d0* c, int a);         // 0x00da6270
float __cdecl FUN_00bc2240(void* a, float x, float y, float z);  // 0x00bc2240
void  __cdecl FUN_00bc2180(void* a);                   // 0x00bc2180
void* __cdecl FUN_005727b0(void* v);                   // 0x005727b0
void  __cdecl Variant_SetInt(void* v, void* p);        // 0x00427fd0
float __cdecl GetPropertyF(int holder, uint32_t id, float def);  // 0x004e1c70
void* __cdecl GetSetting9(int a, int b);               // 0x00401090
void* __cdecl GetSpeciesArchetype(void* p);            // 0x004e0050
void* __cdecl normalized_safe(Vec3_s00db_10d0* out, Vec3_s00db_10d0 d, float a, float b);  // 0x00449c20
void* __cdecl TribeModeInstance();                     // 0x00cd40b0
OrderMgr* __cdecl OrderManager();                      // 0x00bc9b00
struct StEatSub {
    char     pad00[0x21c];
    Citizen_s00db_10d0* mp21c;    // +0x21c
};
struct Loc74 {
    int   m00, m04, m08;
    uint32_t pad0c;
    float f10, f14, f18, f1c, f20;
    uint32_t pad24;
    uint32_t pad28[9];
    uint8_t b4c;
    uint8_t pad4d[3];
    float f50, f54, f58, f5c;
    float f60, f64, f68, f6c;
    uint32_t i70;
};
static void InitLoc74(Loc74* loc)
{
    loc->m00 = 0; loc->m04 = 0; loc->m08 = 0;
    loc->pad0c = 0;
    loc->f10 = k169f3b8; loc->f18 = k169f3bc; loc->f1c = k169f3c0;
    loc->f20 = k1485720;
    loc->pad24 = 0;
    loc->b4c = 0;
    loc->f50 = 0.0f; loc->f54 = 0.0f; loc->f58 = 0.0f; loc->f5c = 0.0f;
    loc->f60 = k1470f1c; loc->f64 = k13ec4b4; loc->f68 = k147c218; loc->f6c = 0.0f; loc->i70 = 0;
}
// ---- items of slice s00db10d0 end

// ---- items of slice s00db5e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define G1581270       (*(const u32*)0x01581270)
#define G1485548       (*(const float*)0x01485548)
#define G169F3B8       (*(const float*)0x0169f3b8)
#define G169F3BC       (*(const float*)0x0169f3bc)
#define G169F3C0       (*(const float*)0x0169f3c0)
#define G13EB8A0       (*(const float*)0x013eb8a0)
#define G1485720       (*(const float*)0x01485720)   // _HK_REAL_ONE
#define G147C21C       (*(const float*)0x0147c21c)
#define G147C218       (*(const float*)0x0147c218)   // FLT_MAX, initial nearest-spot distance
#define VTABLE_147C2C4 ((void*)g_147c2c4)
#define RNG1601760     ((void*)0x01601760)           // EA::Random::RandomLinearCongruential
#define SLIST169B41C   ((void*)0x0169b41c)           // rw::SList singleton
typedef void   (__thiscall* FnV0)(void*);
typedef void   (__thiscall* FnV1)(void*, void*);
typedef char   (__thiscall* FnC0)(void*);
typedef u32    (__thiscall* FnU0)(void*);
typedef float  (__thiscall* FnF0)(void*);
typedef void*  (__thiscall* FnP0)(void*);
typedef float* (__thiscall* FnFP0)(void*);
typedef u32    (__thiscall* FnU3)(void*, int, int, int);
struct Cont2                          // { begin, end } pair returned by several containers
{
    char* mBegin;
    char* mEnd;
};
struct ObjV
{
    void* FUN_00c04590();                        // 0x00c04590  Get() -> herd
    void  FUN_00c045a0(void*);                   // 0x00c045a0  SetHerd
    void* FUN_00c0bbd0();                        // 0x00c0bbd0  GetSpeciesProfile
    void  FUN_00c042e0();                        // 0x00c042e0
    void  FUN_00c0d950(int);                     // 0x00c0d950
    u32   FUN_00c0bc00(void*, u32, int, int);    // 0x00c0bc00
    char  FUN_00c0b770();                        // 0x00c0b770
    char  FUN_00c24560();                        // 0x00c24560
    void* FUN_00c22f50();                        // 0x00c22f50  cSPCreatureCitizen::GetTribe
    char  FUN_00c8e7c0();                         // 0x00c8e7c0
    void* FUN_00c8fee0();                        // 0x00c8fee0
    void  FUN_00c8fef0();                        // 0x00c8fef0  cTribe::InitDomesticatedAnimalsHerd
    void* FUN_00c8e820(int);                     // 0x00c8e820
    char  FUN_00feba90();                        // 0x00feba90  cSPTimer::IsRunning
    long long FUN_00bc3190();                    // 0x00bc3190  cSPTimer::GetElapsedTime
    float FUN_00fc7f80();                        // 0x00fc7f80  GetCost
    int   FUN_00bc2b80(void*);                   // 0x00bc2b80
    int   FUN_00bc3db0(int);                     // 0x00bc3db0
    void* FUN_00bc7610(int, int);                // 0x00bc7610
    u32   FUN_00a68fb0(int);                     // 0x00a68fb0  RandomUint32Uniform
    double FUN_009360d0();                       // 0x009360d0  cRandomGlobal::RandomDouble
    int   FUN_00bca620(u32, void*, void*);       // 0x00bca620  cAgentOrderManager::FindNode
    void* FUN_00d997e0();                        // 0x00d997e0  behavior_stimuli::GetAny
    int   FUN_00d00a70(u32, u32, int);           // 0x00d00a70
    void* FUN_00bfc5f0();                        // 0x00bfc5f0
    void  FUN_00fcc200(u32);                     // 0x00fcc200  rw::SList::SetElementAlignment
    u32   FUN_006766e0(u32);                     // 0x006766e0
    void  FUN_00676710(u32);                     // 0x00676710  AwardAchievement
    void  FUN_0060d860(u32, void*);              // 0x0060d860  UpdateProperty
    void  FUN_00dd8640(u32, u32, void*, int, int, int);  // 0x00dd8640  PostFeedbackEvent
    void  FUN_00cd6980(void*);                   // 0x00cd6980  SignalTribeEvent
    void  FUN_00aea5d0(void*, void*);            // 0x00aea5d0  DoInsertPtr
    // ctor / dtor helpers
    void  FUN_00ac14d0();                        // 0x00ac14d0
    void  FUN_00afba10();                        // 0x00afba10
    void  FUN_00afbad0();                        // 0x00afbad0  cActionCircle::~cActionCircle
    void  FUN_00ad92d0();                        // 0x00ad92d0  eastl vector dtor
    void  FUN_00ac5430();                        // 0x00ac5430  base dtor
    void  FUN_00db5c20(void*, void*);            // 0x00db5c20
    void  FUN_005941f0(void*, void*);            // 0x005941f0
};
char  __cdecl FUN_00c0d3a0(void*);                       // 0x00c0d3a0
void  __cdecl FUN_00acca00(void*, void**);               // 0x00acca00  spstl::remove_1st
u32   __cdecl FUN_00b6f0c0(u32);                         // 0x00b6f0c0
void* __cdecl FUN_00b3d4e0(u32);                         // 0x00b3d4e0
void* __cdecl FUN_00bc9b00_s00db_5e80();                           // 0x00bc9b00  agent-order manager singleton
u8    __cdecl FUN_00da7140(void*, void*);                // 0x00da7140  order-node predicate
float __cdecl FUN_004e1c70(u32, u32, float);             // 0x004e1c70  SP::GetPropertyT<float>
void* __cdecl FUN_00bc30b0(void*);                       // 0x00bc30b0
void* __cdecl FUN_00b3d2c0(void*, void*, int);           // 0x00b3d2c0  RelationshipManager
void* __cdecl FUN_00b3d300();                            // 0x00b3d300  NounManager
void* __cdecl FUN_00675250(u32);                         // 0x00675250  Achievements::Controller
void* __cdecl FUN_0067cb30(u32, void*);                  // 0x0067cb30
void* __cdecl FUN_00e398e0(u32, void*, void*);           // 0x00e398e0
void* __cdecl FUN_00b3d3e0(u32, u32, void*);             // 0x00b3d3e0  EventLog
struct FVecV
{
    u32*  mBegin;        // 0x00
    u32*  mCur;          // 0x04
    u32*  mCap;          // 0x08
    u32*  mFieldC;       // 0x0c
    u32*  mHeapBase;     // 0x10
    u32*  mField14;      // 0x14
    u32   mInline[16];   // 0x18
    void  FUN_004281d0(u32* pos, const u32& v);          // 0x004281d0  DoInsertValue
};
struct VignetteSpot
{
    float x;              // +0x00
    float y;              // +0x04
    float z;              // +0x08
    float mField0C;       // +0x0c
    u8    mFlag10;        // +0x10  non-zero = unusable spot
    u8    mPad11[3];
};
struct VignetteRecord
{
    u8    mPad00[4];
    int   mMaxCitizens04;          // +0x04
    u8    mPad08[0x78c - 0x08];
    float mfMinCost078C;           // +0x78c
    float mfMaxCost0790;           // +0x790
    u8    mPad794[0x7a0 - 0x794];
    int   mnTimeOfDay07A0;         // +0x7a0  0 = any
    int   mnRelation07A4;          // +0x7a4  -1 = any
    u8    mPad7A8[4];
    u32   muToolMask07AC;          // +0x7ac  0 = any
    u8    mPad7B0[4];
};
// ---- items of slice s00db5e80 end

// ---- items of slice s00db6e60 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IEffect {                                                  // an entry in the effect system
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
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
    virtual void* Cast(uint32_t typeId);                         // +0x0b8
    virtual void AddRef();                                       // +0x0bc
    virtual void Release();                                      // +0x0c0
};
class cLocomotiveObject_s00db_6e60 {                                        // the creature's +0xc0 sub-object
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
    virtual bool v058();                                         // +0x058
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
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
    virtual void AddRef();                                       // +0x0bc
    virtual void Release();                                      // +0x0c0
virtual void v0c4();
virtual void v0c8();
virtual void v0cc();
virtual void v0d0();
virtual void v0d4();
virtual void v0d8();
virtual void v0dc();
virtual void v0e0();
virtual void v0e4();
virtual void v0e8();
    virtual void v0ec();                                         // +0x0ec
};
class IGameObject {                                              // cSPCreatureBase's root object
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
    virtual uint32_t GetClassId();                               // +0x020
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
    virtual void v084(int, int, int);                            // +0x084
};
template <class T>
class AutoRefCount_s00db_6e60 {
public:
    T* mpObject;                                                 // +0x00
    AutoRefCount_s00db_6e60(T* object) : mpObject(object) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s00db_6e60(const AutoRefCount_s00db_6e60& other) : mpObject(other.mpObject)
    {
        if (mpObject) mpObject->AddRef();
    }
    ~AutoRefCount_s00db_6e60() { if (mpObject) mpObject->Release(); }
};
class cGroupMovement_s00db_6e60;
class cCurvePoint {                                              // one sample of the group's curve
public:
    float mX;                                                    // +0x00
    float mY;                                                    // +0x04
    float mZ;                                                    // +0x08
    float mW;                                                    // +0x0c
    uint32_t mFlags;                                             // +0x10
    uint32_t mPad14[(0x38 - 0x14) / 4];                          // +0x14
    uint8_t mTail;                                               // +0x38
    uint8_t mPad39[3];                                           // +0x39
    void CopyFrom(const cCurvePoint* src);                       // 0x00ac1ff0 (ret 4)
};
class cCurveVector {                                             // SpVector<cCurvePoint>
public:
    cCurvePoint* mpBegin;                                        // +0x00
    cCurvePoint* mpEnd;                                          // +0x04
    cCurvePoint* mpEndOfStorage;                                 // +0x08
    void DoInsertValue(cCurvePoint* pos, const cCurvePoint* value);   // 0x00ac45e0 (ret 8)
    __forceinline void push_back(const cCurvePoint& value)
    {
        if (mpEnd < mpEndOfStorage) {
            cCurvePoint* slot = mpEnd;
            ++mpEnd;
            if (slot)
                slot->CopyFrom(&value);
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};
template <class T>
class AutoRefVector {                                            // eastl::vector<EA::AutoRefCount<T>>
public:
    AutoRefCount_s00db_6e60<T>* mpBegin;                                    // +0x00
    AutoRefCount_s00db_6e60<T>* mpEnd;                                      // +0x04
    AutoRefCount_s00db_6e60<T>* mpEndOfStorage;                             // +0x08
    void DoInsertValue(AutoRefCount_s00db_6e60<T>* pos, const AutoRefCount_s00db_6e60<T>& value);   // 0x00bab900 (ret 8)
    __forceinline void push_back(const AutoRefCount_s00db_6e60<T>& value)
    {
        if (mpEnd < mpEndOfStorage) {
            AutoRefCount_s00db_6e60<T>* slot = mpEnd;
            ++mpEnd;
            if (slot)
                ::new ((void*)slot) AutoRefCount_s00db_6e60<T>(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
class cEntityInfo {                                              // what the group knows per member
public:
    float mDoneTime;                                             // +0x00
    float mDistanceFromSlot2;                                    // +0x04
    int32_t mSlotIdx;                                            // +0x08
};
class cInfoNode {
public:
    cLocomotiveObject_s00db_6e60* mpKey;                                    // +0x00
    cEntityInfo mInfo;                                           // +0x04
    cInfoNode* mpNext;                                           // +0x10
};
class cMovementIterator {
public:
    cInfoNode* mpNode;                                           // +0x00
    void* mpBucket;                                              // +0x04
};
class cEntityInfoMap {                                           // eastl::hash_map<cLocomotiveObject*, cEntityInfo>
public:
    int32_t mnBucketCount;                                       // +0x00
    cInfoNode** mppBucketArray;                                  // +0x04
    int32_t mnBucket;                                            // +0x08
    uint32_t mPad0c[7];                                          // +0x0c (element count, rehash policy)
    cMovementIterator find(cLocomotiveObject_s00db_6e60* const& key);       // 0x00db4780 (ret 8)
    cMovementIterator erase(cMovementIterator it);               // 0x00db3da0 (ret 0xc)
    cEntityInfo* FindOrAdd(cLocomotiveObject_s00db_6e60* const& key);       // 0x00db5cf0 (ret 4)
};
namespace SP {
class cActionCircle_s00db_6e60 {
public:
    class tSlot {
    public:
        bool mOccupied;                                          // +0x00
        uint32_t mPad04;                                         // +0x04
        uint32_t mReservingId;                                   // +0x08
        float mPos[3];                                           // +0x0c
        void Clear();                                            // 0x00afa0a0
    };
    uint32_t mPad00[0x50 / 4];                                   // +0x00
    tSlot* mpSlotBegin;                                          // +0x50
    uint32_t mSlotCount;                                         // +0x54
    uint32_t mPad58;                                             // +0x58
    tSlot* SlotAt(uint32_t index);                               // 0x00af9ff0 (ret 4)
};  // namespace SP
}
struct Vector3_s00db_6e60 {
    float mX;                                                    // +0x00
    float mY;                                                    // +0x04
    float mZ;                                                    // +0x08
};
class cGroupMovement_s00db_6e60 {                                           // the group object (retail layout)
public:
    uint32_t mPad00[2];                                          // +0x000
    cCurveVector mCurve;                                         // +0x008
    uint32_t mPad14[2];                                          // +0x014
    AutoRefVector<cLocomotiveObject_s00db_6e60> mEntities;                  // +0x01c
    uint32_t mPad28[(0x54 - 0x28) / 4];                          // +0x028
    cEntityInfoMap mInfoMap;                                     // +0x054
    uint32_t mPad7c[(0x190 - 0x7c) / 4];                         // +0x07c
    IEffect* mpObject;                                           // +0x190 (an owned reference)
    Vector3_s00db_6e60 mGoal;                                               // +0x194
    uint32_t mPad1a0[(0x1cc - 0x1a0) / 4];                       // +0x1a0
    int32_t mFlags1cc;                                           // +0x1cc
    bool mbFlag1d0;                                              // +0x1d0
    bool mbFlag1d1;                                              // +0x1d1
    uint8_t mPad1d2[2];                                          // +0x1d2
    SP::cActionCircle_s00db_6e60 mActionCircle;                             // +0x1d4
    uint32_t mPad230[(0x23c - 0x230) / 4];                       // +0x230
    bool mbFlag23c;                                              // +0x23c
    uint32_t mPad240[(0x248 - 0x240) / 4];                       // +0x240
    uint32_t mSoundId248;                                        // +0x248

    void FUN_00db6e60(bool bSkipPoint);                          // 0x00db6e60 (ret 4)
    void FUN_00db6ef0(cLocomotiveObject_s00db_6e60* loco);                  // 0x00db6ef0 (ret 4)
    void FUN_00db6fa0(cLocomotiveObject_s00db_6e60* loco);                  // 0x00db6fa0 (ret 4)
};
struct cGroupMovementPool_s00db_6e60 {
    cGroupMovement_s00db_6e60* GetObject(uint32_t slotRef);                 // 0x00db3c40 (ret 4)
};
extern cGroupMovementPool_s00db_6e60 gGroupMovementPool_s00db_6e60;                    // 0x0159d548
struct cEntryState;
class cLocomotionMgr {                                           // the creature's +0xb4c
public:
    uint32_t mPad000[(0x600 - 0x000) / 4];                       // +0x000
    cEntryState* mpEntry;                                        // +0x600 (an owned reference)
    uint32_t mId604;                                             // +0x604
    void ReleaseEntry();                                         // 0x00bcb430
};
struct cEntryState {                                             // cLocomotionMgr::mpEntry
    uint32_t mPad000[(0x1a4 - 0x000) / 4];                       // +0x000
    uint32_t mGroupSlotRef;                                      // +0x1a4
    void* CurrentId();                                           // 0x00bc9b10
};
struct cSoundSlots {
    void Release(uint32_t slot);                                 // 0x00bc2180 (ret 4)
};
struct cTribeModeStrategy_s00db_6e60 {
    uint32_t mPad000[(0x1c8 - 0x000) / 4];                       // +0x000
    cSoundSlots* mpSoundSlots;                                   // +0x1c8
    static cTribeModeStrategy_s00db_6e60* Instance();                       // 0x00cd40b0
};
struct cEffectPlayer {
    void PlayEffect(IEffect* effect);                            // 0x00aca360 (ret 4)
};
cEffectPlayer* EffectPlayer();                                   // 0x00b3d480
bool RemoveEntity(AutoRefVector<cLocomotiveObject_s00db_6e60>* list,
                  cLocomotiveObject_s00db_6e60** value);                    // 0x00afc4b0
class cSPCreatureBase_s00db_6e60 : public IGameObject {                      // the creature the move driver gets
public:
    uint32_t mPad004[(0xc0 - 0x004) / 4];                        // +0x004
    cLocomotiveObject_s00db_6e60 mLocomotive;                               // +0x0c0
    uint32_t mPadAfterLoco[(0xb4c - 0x0c0 - sizeof(cLocomotiveObject_s00db_6e60)) / 4];
    cLocomotionMgr* mpLocomotionMgr;                             // +0xb4c
    uint32_t mPadB50[(0xb64 - 0xb50) / 4];                       // +0xb50
    bool mbFlagB64;                                              // +0xb64

    void UpdateLocomotion(int);                                  // 0x00c14750 (ret 4)
    void SetSprinting(int);                                      // 0x00c1ad10 (ret 4)
    void Hover(int);                                             // 0x00c13a30 (ret 4)
};
struct cMoveArg {                                                // the payload the move driver receives
    uint32_t mPad00[4];                                          // +0x00
    bool mFlag;                                                  // +0x10
    uint8_t mPad11[0xb];                                         // +0x11
    IEffect* mpEffect;                                           // +0x1c
};
// ---- items of slice s00db6e60 end

// ---- items of slice s00db7b60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefCounted {
  virtual void AddRef();
  virtual void Release();
};
struct IndexSource : RefCounted {
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
  virtual int GetValue();
};
struct Sink : RefCounted {
  void FUN_00c98750(int value, int index);
};
struct Message {
  unsigned int type;     // 0x00
  RefCounted* ref4;      // 0x04
  IndexSource* source;   // 0x08
  Sink* sink;            // 0x0c
  char pad10[0x0c];
  int index;             // 0x1c
};
struct Info {
  char pad0[8];
  float f8;              // 0x08
  char padc[0x20];
  int f2c;               // 0x2c
};
struct Channel {
  Info* FUN_00bc96a0(int a, int b);
  void FUN_00bc97f0(int a, int b, float f, int c);
};
struct Player;
struct Slot {
  bool active;
  Player* player;
  int pad;
};
struct Releaser {
  void FUN_00bc2180(int h);
};
template <class T> struct Ptr {
  T* p;
  T* operator->() { return p; }
};
struct Mgr_s00db_7b60 {
  char pad[0x1c8];
  Ptr<Releaser> rel;
};
Mgr_s00db_7b60* FUN_00cd40b0_s00db_7b60();
struct SubState {
  char pad0[0x18];
  int count;             // 0x18
  char pad1c[0x0c];
  int handle;            // 0x28
  RefCounted* a;         // 0x2c
  RefCounted* b;         // 0x30
};
struct Session {
  char pad0[0x10];
  int mode;              // 0x10
  char pad14[4];
  unsigned int numSlots; // 0x18
  char pad1c[4];
  Slot slots[1];         // 0x20
  Player* FUN_00bc9b10();
};
struct Game {
  char pad0[8];
  Channel channel;       // 0x08
  char pad9[0x600 - 9];
  Session* session;      // 0x600
  void FUN_00bcb430();
};
struct Vec {
  int* mpBegin;
  int* mpEnd;
  int* erase(int* first, int* last) {
    memcpy(first, last, (char*)mpEnd - (char*)last);
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
};
struct Player {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
  virtual void v32();
  virtual void Reset(int a, int b, int c);
  char pad4[0xb4c - 4];
  Game* game;            // 0xb4c
  char padb50[0xe];
  bool flagB5E;          // 0xb5e
  char padb5f[0xe8c - 0xb5f];
  int e8c;
  int e90;
  float e94;
  Vec vec;               // 0xe98
  void FUN_00c26310(int);
  void FUN_00c14750(int);
  bool FUN_00c0c120();
  void FUN_00c1ad10(int);
  void FUN_00c0ba10();
};
// ---- items of slice s00db7b60 end

// ---- items of slice s00db86a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern float gGroupMinSpeed;   // 0x01572070
extern float gGroupMaxSpeed;   // 0x0157206c
#pragma intrinsic(sqrt)
inline float sqrtf_s00db_86a0(float x) { return (float)sqrt((double)x); }
#define PV_s00db_86a0(n) virtual void pad##n();
struct Quaternion {
    float x, y, z, w;
};
struct Matrix3 {
    float m[3][3];
};
bool operator!=(const Vector3& a, const Vector3& b);                     // 0x0041dd30
void Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);           // 0x0059c190
struct Waypoint {
    Vector3 pos;      // 0x00
    float weight;     // 0x0c
    int flags;        // 0x10
    Vector3 v14;      // 0x14
    Vector3 v20;      // 0x20
    Vector3 v2c;      // 0x2c
    bool b38;         // 0x38
    Waypoint(const Vector3& p) : pos(p), weight(1.0f), flags(0), b38(false) {}
    Waypoint(const Waypoint& o);
};
struct WaypointVector {   // eastl::vector<Waypoint>
    Waypoint* mpBegin;
    Waypoint* mpEnd;
    Waypoint* mpCapacity;
    int mAllocator;
    Waypoint* erase(Waypoint* first, Waypoint* last);   // 0x00ac4570
    void push_back(const Waypoint& v);                  // 0x00ac4de0
    void clear() { erase(mpBegin, mpEnd); }
    int size() const { return (int)(mpEnd - mpBegin); }
    Waypoint& operator[](int i) { return mpBegin[i]; }
};
struct CastIface {   // result of Cast(0x017f243b)
    PV_s00db_86a0(0) PV_s00db_86a0(1) PV_s00db_86a0(2) PV_s00db_86a0(3) PV_s00db_86a0(4) PV_s00db_86a0(5) PV_s00db_86a0(6) PV_s00db_86a0(7) PV_s00db_86a0(8) PV_s00db_86a0(9) PV_s00db_86a0(10)
    virtual bool IsBusy();   // 0x2c
};
struct LocoState {
    char pad0[0x5c];
    int mHasGoal;            // 0x5c
    const Vector3* GetGoal();                 // 0x00c423c0
};
struct Object_s00db_86a0;
struct Creature_s00db_86a0 {   // SP::cSPCreatureBase (Cast 0xce9f6639)
    char pad0[0xf90];
    bool bF90;               // 0xf90
    int GetMode();                            // 0x00c0c2f0
    void MoveToPointAtSpeed(int how, const Vector3* pos, float a, float b);   // 0x00c1c1d0
};
struct Object_s00db_86a0 {
    PV_s00db_86a0(0) PV_s00db_86a0(1) PV_s00db_86a0(2) PV_s00db_86a0(3) PV_s00db_86a0(4) PV_s00db_86a0(5) PV_s00db_86a0(6) PV_s00db_86a0(7) PV_s00db_86a0(8) PV_s00db_86a0(9) PV_s00db_86a0(10)
    virtual const Vector3* GetPosition();      // 0x2c
    PV_s00db_86a0(12) PV_s00db_86a0(13) PV_s00db_86a0(14) PV_s00db_86a0(15) PV_s00db_86a0(16) PV_s00db_86a0(17) PV_s00db_86a0(18) PV_s00db_86a0(19) PV_s00db_86a0(20) PV_s00db_86a0(21)
    virtual bool v58(int);                     // 0x58
    PV_s00db_86a0(23) PV_s00db_86a0(24) PV_s00db_86a0(25) PV_s00db_86a0(26) PV_s00db_86a0(27) PV_s00db_86a0(28) PV_s00db_86a0(29) PV_s00db_86a0(30) PV_s00db_86a0(31) PV_s00db_86a0(32)
    PV_s00db_86a0(33) PV_s00db_86a0(34) PV_s00db_86a0(35) PV_s00db_86a0(36) PV_s00db_86a0(37) PV_s00db_86a0(38) PV_s00db_86a0(39) PV_s00db_86a0(40) PV_s00db_86a0(41) PV_s00db_86a0(42)
    PV_s00db_86a0(43) PV_s00db_86a0(44) PV_s00db_86a0(45)
    virtual void* Cast(uint32_t id);           // 0xb8 0x00bef670
    PV_s00db_86a0(47)
    virtual void vc0();                        // 0xc0
    PV_s00db_86a0(49) PV_s00db_86a0(50) PV_s00db_86a0(51) PV_s00db_86a0(52) PV_s00db_86a0(53) PV_s00db_86a0(54) PV_s00db_86a0(55)
    virtual void MoveTo(const Vector3* pos, float a, float b, int c);   // 0xe0
    PV_s00db_86a0(57) PV_s00db_86a0(58)
    virtual void StopMoving();                 // 0xec

    char fpad4[0x75 - 4];
    bool mbAlive;                              // 0x75

    LocoState* GetLoco();                      // 0x00c41ec0
    bool IsNearGoal();                         // 0x00c42e20
};
struct ObjectView {
    PV_s00db_86a0(0) PV_s00db_86a0(1) PV_s00db_86a0(2) PV_s00db_86a0(3) PV_s00db_86a0(4) PV_s00db_86a0(5) PV_s00db_86a0(6) PV_s00db_86a0(7) PV_s00db_86a0(8) PV_s00db_86a0(9) PV_s00db_86a0(10)
    PV_s00db_86a0(11) PV_s00db_86a0(12) PV_s00db_86a0(13) PV_s00db_86a0(14) PV_s00db_86a0(15) PV_s00db_86a0(16) PV_s00db_86a0(17) PV_s00db_86a0(18) PV_s00db_86a0(19) PV_s00db_86a0(20) PV_s00db_86a0(21)
    virtual bool v58();                        // 0x58
};
struct PlanetModel_s00db_86a0 {
    void BuildSurfaceOrientation(Quaternion* out, const Vector3* pos);   // 0x00b7f190
    Vector3 DirectionToSurfacePosition(const Vector3& dir);              // 0x00b815a0
};
PlanetModel_s00db_86a0* GetPlanetModel();                 // 0x00b3d350
struct cGroupFollower;
struct AStarMethod { int unused; };
extern AStarMethod gAStarSearchLandAvoidCities;    // 0x01565b68
struct Pathfinder {
    void Cancel(cGroupFollower* owner);        // 0x00ac4ef0
    void FindPath(AStarMethod* method, const Vector3* start, const Vector3* goal, float a, float b,
                  WaypointVector* out, cGroupFollower* owner, int canSwim);   // 0x00ac65d0
};
Pathfinder* GetPathfinder();                   // 0x00b3d290
struct FormationSlot {   // 0x18 bytes
    bool mbTaken;          // 0x00
    char pad1[7];
    int mOwnerRef;         // 0x08
    Vector3 mOffset;       // 0x0c
    int GetOwner();                            // 0x00fcc210
    void Assign(int who);                      // 0x00afa030
};
struct Formation {
    char pad0[0x14];
    Vector3 mPosition;     // 0x14
    char pad20[0x2c - 0x20];
    Quaternion mOrientation;  // 0x2c
    char pad3c[0x64 - 0x3c];
    bool IsPlaced();                                                      // 0x00af9ee0
    void Place(const Vector3* pos, const Quaternion* q, float spacing);   // 0x00af9d60
    void Layout(int a, float spacing);                                    // 0x00afef10
    void Reset();                                                         // 0x00afafd0
    FormationSlot* GetSlot(int index);                                    // 0x00af9ff0
};
struct MemberInfo {
    float mTimeNear;      // 0x0
    float mDistSq;        // 0x4
    int mSlot;            // 0x8
};
struct MemberMap {   // eastl::hash_map<Object*, MemberInfo>
    char pad[0x20];
    MemberInfo& operator[](Object_s00db_86a0* const& key);   // 0x00db5cf0
};
typedef void (*FollowCallback)(cGroupFollower* self, Formation* f, int b);
template <class T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }
struct cGroupFollower {
    char pad0[8];
    WaypointVector mPath;            // 0x08
    char pad18[4];
    Object_s00db_86a0** mMembersBegin;          // 0x1c
    Object_s00db_86a0** mMembersEnd;            // 0x20
    char pad24[0x54 - 0x24];
    MemberMap mInfo;                 // 0x54
    char pad74[0x18c - 0x74];
    Object_s00db_86a0* mpLeader;                // 0x18c
    Object_s00db_86a0* mpTarget;                // 0x190
    Vector3 mTargetPos;              // 0x194
    Vector3 mPathGoal;               // 0x1a0
    float mRepathTimer;              // 0x1ac
    float mRepathInterval;           // 0x1b0
    float mSpacing;                  // 0x1b4
    float m1b8;                      // 0x1b8
    float mRadius;                   // 0x1bc
    float m1c0;                      // 0x1c0
    float mSpread;                   // 0x1c4
    float mAvgDistSq;                // 0x1c8
    int mState;                      // 0x1cc
    bool mbReset;                    // 0x1d0
    bool mbRepath;                   // 0x1d1
    char pad1d2[2];
    Formation mFormation;            // 0x1d4
    FollowCallback mCallback;        // 0x238
    char pad23c[4];
    int mPathIndex;                  // 0x240

    void ResetMembers();                       // 0x00daad10
    void ApplyFormation(Matrix3* m);           // 0x00db80c0
    void Update(float dt);
};
// ---- items of slice s00db86a0 end

// ---- items of slice s00dba2f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned char g_00ae72d0[];
extern "C" unsigned char g_00b1e500[];
extern "C" unsigned char g_00cd7d10[];
extern "C" unsigned char g_00d3d420[];
extern "C" void* FUN_00b21340(void*, void*, void*, void*, void*, void*);
extern "C" void* FUN_00d997e0();
struct PointerList {
    void** mpBegin;     // +0
    void** mpEnd;       // +4
    void** mpCapacity;  // +8
};
struct GameObjectRef {
    int         mTag;      // +0
    PointerList mObjects;  // +4
};
struct cVehiclePartA {
    char mPad[0x508];
};
struct cVehiclePartB {
    void* mpRecorded;
};
struct cVehicleLayout : cVehiclePartA, cVehiclePartB {
};
typedef bool  (__thiscall* FnBoolVoid)(void*);
typedef void* (__thiscall* FnPtrInt)(void*, int);
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)
struct cHealOtherData_s00db_a2f0 {
    void* mpVtable;                                          // +0x00
    uint32_t mPad04;                                         // +0x04

    void Copy(const cHealOtherData_s00db_a2f0* src);                    // 0x00db97f0
    cHealOtherData_s00db_a2f0& operator=(const cHealOtherData_s00db_a2f0& rhs);    // 0x00dba120
};

struct cHealOther {
    int32_t        mTag;                                     // +0x00
    cHealOtherData_s00db_a2f0 mData;                                    // +0x04

    cHealOther* Assign(const cHealOther* other);
};
static inline bool TagIsNegative(int32_t tag)
{
    return ((uint32_t)tag >> 31) & 1;
}
// ---- items of slice s00dba2f0 end

// ---- items of slice s00dbe140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kF1572070;   // 0x01572070
extern const float kF147c21c;   // 0x0147c21c
extern const float kF1485720;   // 0x01485720
extern const float kF1471064;   // 0x01471064
extern const float kF13eedb8;   // 0x013eedb8
extern char kMoveName[];        // "Move" 0x0147c2d8
extern char kStrA[];            // 0x01581234
extern char kStrB[];            // 0x0158123c
struct Vec3_s00db_e140 {
    float x, y, z;
    Vec3_s00db_e140() {}
    Vec3_s00db_e140(const Vec3_s00db_e140& v) : x(v.x), y(v.y), z(v.z) {}
};
#define SLOT(n) virtual void s##n();
struct SpatialObj {
    SLOT(0) SLOT(1) SLOT(2)
    virtual void* Cast(uint32_t typeId);                       // +0xc
    SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
    virtual const Vec3_s00db_e140* GetPosition();                         // +0x2c
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
struct Tribe_s00db_e140 { char pad[0x268]; float mField268; };
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
struct NounMgr { Tribe_s00db_e140* FUN_00bfc5f0(); };
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
struct Creature_s00db_e140 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
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
    Tribe_s00db_e140* GetTribe();                                          // 0x00c22f50 (citizen)
    int FUN_00c0c160();
    void FUN_00c14750(int v);                                   // ret 4
    char FUN_00c0b700();
};
struct MoveParams {
    char pad0[8];
    SpatialObj* mpTarget;       // +8
    Vec3_s00db_e140 mDest;                 // +0xc
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
    Creature_s00db_e140* mpCreature;
    SpatialObj* mpTarget;
    Vec3_s00db_e140 mDest;
};
extern const Vec3_s00db_e140 kNoDest;      // 0x0169f3b8
MoveFinder* __cdecl FUN_00bc9b00_s00db_e140();                             // behaviour manager (global)
BoundsHelper* __cdecl FUN_00b3d2b0_s00db_e140();
BoundsHelper* __cdecl FUN_00b3d480_s00db_e140();
NounMgr* __cdecl NounManager_s00db_e140();                                 // 0x00b3d300
float __cdecl FUN_004df2d0(const char* v);
bool __cdecl FUN_00da6270(Citizen* c, int state);
struct Vec3Holder { const Vec3_s00db_e140* FUN_00cce910(); };              // thiscall on rec+0x39
static const uint32_t kNounCitizen = 0x18eb4b7;
const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
void* __cdecl ea_operator_new(uint32_t size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl ea_operator_delete(void* p);                              // 0x00f47380
void* __cdecl FUN_00db99a0(void* first, void* last, void* dest);       // copy-construct range
void  __cdecl FUN_00da82a0(void* first, void* last, void* dest);       // destroy source range
void  __cdecl FUN_00dba5f0(void* first, void* last, void* dest);       // move-construct range
struct GmObj {
    char mData[0x24c];
    GmObj* Init();                            // 0x00db6c50
    void   Destroy();                         // 0x00db6db0
    void   CopyFrom(const GmObj* src);        // 0x00db97f0
};
struct SlotEntry {
    uint32_t mId;                             // +0x00  free-list link / flags
    GmObj    mObj;                            // +0x04
    void AssignFrom(const SlotEntry* src);    // 0x00dba580
};
struct GmPayloadVirtual {
    virtual void Destroy(unsigned flags);     // slot 0 (??_G)
};
struct SlotVector {
    SlotEntry* mpBegin;                       // +0x00
    SlotEntry* mpEnd;                         // +0x04
    SlotEntry* mpCapacity;                    // +0x08
    char       mPad0c[8];                     // +0x0c
    uint32_t   mLowestFree;                   // +0x14
    uint32_t   mNextFree;                     // +0x18

    void     Reserve(uint32_t n);                        // 0x00dbe140
    void     Insert(SlotEntry* pos, const SlotEntry* val); // 0x00dbe200
    void     PushDefault();                              // 0x00dbe380
    uint32_t CreateSlot(const GmObj* src);               // 0x00dbe3e0
};
struct GroupMovementPool : SlotVector {
    uint32_t CreateObject();                  // 0x00dbe4e0
};
// ---- items of slice s00dbe140 end

// ---- items of slice s00db86a0_b begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Follower {
    char pad[0x24c];
    void Update(float dt);                       // 0x00db86a0
};
struct GroupRecord {
    u32     mFlags;                              // +0x00
    Follower mFollower;                          // +0x04
};
extern GroupRecord* gGroupBegin;                 // 0x0159d548
extern GroupRecord* gGroupEnd;                   // 0x0159d54c
extern u32          gGroupFirst;                 // 0x0159d55c
struct Tribe_s00db_86a0__b;
struct Locomotive_s00db_86a0__b {
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
struct Creature_s00db_86a0__b;
struct Sub120 {
    void* vptr;                                  // +0x00
    Vec3* V_2c()      { return (*(Vec3* (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
};
struct Sub558 {
    void* vptr;                                  // +0x00
    void FUN_00cc7f90(u32 a);                    // 0x00cc7f90
};
struct Tribe_s00db_86a0__b {
    void* vptr;                                  // +0x000
    char  pad004[0x60 - 0x004];
    float V_60()      { return (*(float (__thiscall**)(void*))(*(char**)this + 0x60))(this); }
    char  pad060[0x120 - 0x060];
    Sub120 mSub120;                              // +0x120
    char  pad124[0x558 - 0x124];
    Sub558 mSub558;                              // +0x558
};
struct Creature_s00db_86a0__b {
    void* vptr;                                  // +0x000
    char  pad004[0xc0 - 0x004];
    Locomotive_s00db_86a0__b mLoco;                            // +0x0c0
    char  pad0c4[0xf90 - 0x0c0 - sizeof(Locomotive_s00db_86a0__b)];
    u8    mByteF90;                              // +0xf90

    Tribe_s00db_86a0__b* GetTribe();                           // 0x00c22f50
    void   UpdateLocomotion(int a);              // 0x00c14750
    bool   AnimationFinished(u32 id);            // 0x00c123f0
    u32    PlayAnimation(u32 id, int a, int b);  // 0x00c12190
    void   MoveToPointAtSpeed(int a, const Vec3* p, float s0, float s1);   // 0x00c1c1d0
    int    FUN_00c26120();                       // 0x00c26120
    bool   FUN_00c25480(int a, int b);           // 0x00c25480
};
struct IdleBlock {
    u32  mState;                                 // +0x00
    u32  mReservedSpot;                          // +0x04
    u32  mAnimationID;                           // +0x08
    int  mLoopCount;                             // +0x0c
    float mTimer;                                // +0x10
    Creature_s00db_86a0__b* mpTribeMember;                     // +0x14

    void   EnterWalk();
    Vec3*  FUN_00db7d60(Vec3* out, const Vec3* in);   // 0x00db7d60
    void   PickNewActivity();                    // 0x00da7cc0
};
// ---- items of slice s00db86a0_b end

// ---- items of slice s00d9cd90 begin (local stubs; names suffixed because the module declares the same callees with other types)
extern "C" void* __cdecl FUN_00b3d300_s00d9_cd90(void);                       // 0x00b3d300 NounManager
extern "C" int   __cdecl FUN_00b1f9d0_s00d9_cd90(void);                       // 0x00b1f9d0 GetPlayerEmpireOrMinus1
extern "C" void* __cdecl FUN_00b3d2c0_s00d9_cd90(int empire);                 // 0x00b3d2c0 RelationshipManager
extern "C" char  __cdecl FUN_00cd5550_s00d9_cd90(void* self);                 // 0x00cd5550
extern "C" void* __cdecl FUN_00bfc5f0_s00d9_cd90(void* nouns);                // 0x00bfc5f0 GetPlayerTribe
extern "C" void* __cdecl FUN_00c00650_s00d9_cd90(void* community);            // 0x00c00650 GetLeader
extern "C" void  __cdecl FUN_00ae0930_s00d9_cd90(void* mgr, const char* trg, int a, int b, int c, int d, int e); // PostTrigger
extern "C" void* __cdecl FUN_00ad7a30_s00d9_cd90(int obj);                    // 0x00ad7a30
extern "C" void  __cdecl FUN_00ae09b0_s00d9_cd90(void* mgr, unsigned id, void* tgt); // PostAction
extern "C" void  __cdecl FUN_00ad7ad0_s00d9_cd90(void);                       // 0x00ad7ad0 dtor
extern "C" void  __cdecl FUN_00cdab10_s00d9_cd90(void* strategy);             // IncrementGoalProgress
extern "C" void  __cdecl FUN_00bc97f0_s00d9_cd90(int a, int b, float d, void* p); // 0x00bc97f0
extern "C" void* __cdecl FUN_00b3d4d0_s00d9_cd90(void);                       // 0x00b3d4d0 GetTriggerMgr
extern "C" int   __cdecl FUN_00d00a70_s00d9_cd90(void* rel, int empire, int b); // 0x00d00a70
extern "C" void* __cdecl FUN_00cd40b0_s00d9_cd90(void);                       // 0x00cd40b0 cTribeModeStrategy::Instance
inline void* VFn_s00d9_cd90(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
struct S_s00d9_cd90 {
  void  FUN_00d9cf70();                              // 0x00d9cf70 AddAgent
};
// ---- items of slice s00d9cd90 end

// ---- items of slice s00db09c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRef_s00db_09c0 {
    virtual void v00();          // +0x00
    virtual void Release();      // +0x04
};
struct IRef1c {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void Release();      // +0x1c
};
struct Spatial_s00db_09c0 {
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
virtual void v2c();
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
    virtual bool IsBundle();     // +0x58
};
struct Tribe_s00db_09c0 {
    void __thiscall FUN_00c97d40(int a, IRef_s00db_09c0* b);   // 0x00c97d40
    void __thiscall FindSpot(int type, int spot);   // 0x00c98750
};
struct AnimNode {
    char  pad00[8];
    float mf08;                  // +0x08 duration
    char  pad0c[0x2c - 0x0c];
    int   mWho;                  // +0x2c
};
struct AnimCtlSub {
    AnimNode* __thiscall Play(int a, int flags);                         // 0x00bc96a0
    void __thiscall Stim(int a, int flags, float f, int who);            // 0x00bc97f0
};
struct AnimPool;
struct AnimCtl_s00db_09c0 {
    char       pad00[0x600];     // +0x08 is the behaviour object AnimCtlSub
    AnimPool*  mpPool;           // +0x600
    void __thiscall FUN_00bcb430();                                       // 0x00bcb430
};
struct PoolEntry {
    unsigned char mbActive;      // +0x00
    char   pad04[3];
    IRef_s00db_09c0*  mpObj;                // +0x04
    char   pad08[4];             // stride 0xc
};
struct PoolNode {
    char   pad00[0x18];
    int    miCount;              // +0x18
    char   pad1c[0x28 - 0x1c];
    void*  mp28;                 // +0x28
    IRef_s00db_09c0*  mp2c;                 // +0x2c
    IRef_s00db_09c0*  mp30;                 // +0x30
};
struct AnimPool {
    char       pad00[0x10];
    int        mi10;             // +0x10
    char       pad14[0x18 - 0x14];
    uint32_t   mi18;             // +0x18
    char       pad1c[0x20 - 0x1c];
    PoolEntry  mEntries;         // +0x20, inline array of mi18 entries
    char       pad2c[0x1a4 - 0x20 - sizeof(PoolEntry)];
    PoolNode   mNode;            // +0x1a4
    PoolNode* GetNode() { return &mNode; }
    void* __thiscall FUN_00bc9b10();                                      // 0x00bc9b10
};
struct Manager {
    void __thiscall FUN_00bc2180(void* a);                                // 0x00bc2180
};
struct Strategy_s00db_09c0 {
    char  pad00[0x1c8];
    Manager* mpMgr;              // +0x1c8
};
Strategy_s00db_09c0* __cdecl TribeModeStrategy_Instance();    // 0x00cd40b0
struct EatState {
    int     mPhase;              // +0x00
    IRef_s00db_09c0*   mpOwner;             // +0x04
    IRef_s00db_09c0*   mpTarget;            // +0x08
    IRef_s00db_09c0*   mp0c;                // +0x0c
    IRef_s00db_09c0*   mp10;                // +0x10
    IRef1c* mp14;                // +0x14
    char    pad18[0x24 - 0x18];
    int     mSpot;               // +0x24
};
struct Citizen_s00db_09c0 {
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
virtual void v2c();
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
    virtual void vf84(int a, int b, int c);       // +0x84

    void __thiscall UpdateLocomotion(int a);      // 0x00c14750
    bool __thiscall FUN_00c0c120();               // 0x00c0c120
    void __thiscall SetSprinting(int a);          // 0x00c1ad10
    Tribe_s00db_09c0* __thiscall GetTribe();                 // 0x00c22f50

    char      pad04[0xc0 - 0x04];
    Spatial_s00db_09c0   mLoco;              // +0xc0
    char      padc4[0xb4c - 0xc0 - sizeof(Spatial_s00db_09c0)];
    AnimCtl_s00db_09c0*  mpAnim;             // +0xb4c
};
// ---- items of slice s00db09c0 end

// ---- items of slice s00db7d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00db7d60 {
    float x;
    float y;
    float z;

    // Retail copies a whole position one float at a time through the x87
    // (fld/fstp), so the type has a user copy assignment; plain copies of it
    // (the initialisation of a local) stay in dword/SSE form.
    Vec3_s00db7d60& operator=(const Vec3_s00db7d60& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
};
struct ReservedSpot_s00db7d60 {
    unsigned mX;
    unsigned mY;
    unsigned mZ;
    unsigned mID;
    bool     mbReserved;
    bool     mbHasCitizen;
    unsigned char mPad12[2];
};
struct ReservedPair_s00db7d60 {
    unsigned mKey;
    ReservedSpot_s00db7d60 mSpot;
};
struct ClusterMap_s00db7d60 {
    ReservedPair_s00db7d60* mpBegin;         // +0x00
    ReservedPair_s00db7d60* mpEnd;           // +0x04
    ReservedPair_s00db7d60* mpCapacityEnd;   // +0x08
    void*                   mpUnk0c;         // +0x0c
    ReservedPair_s00db7d60* mpBuffer;        // +0x10
    void*                   mpUnk14;         // +0x14
    ReservedPair_s00db7d60  mData[121];      // +0x18 (size 0xb58)
    unsigned char mbCompare;                 // +0xb70
    unsigned char mPad[3];

    // Written in the order the retail constructor's inlined stores appear.
    ClusterMap_s00db7d60() {
        mpBuffer = mData;
        mpEnd = mData;
        mpBegin = mData;
        mpCapacityEnd = mData + 121;
    }
    // Teardown is written out rather than left to a destructor: retail has no
    // unwind frame, only the two inlined copies of this check.
    void Destroy() {
        if (mpBegin != 0 && mpBegin != mpBuffer)
            FUN_00f47380(mpBegin);
    }
};
struct ReservationGrid_s00db7d60 {
    unsigned mGridRes;                       // +0x0000
    float    mSquareSize;                    // +0x0004
    unsigned char mReservedSpots[0x97c];     // +0x0008
    unsigned char mKeepClearSpots[0x97c];    // +0x0984
    float mGridMax;                          // +0x1300
    float mGridMin;                          // +0x1304
    float mGridAvg;                          // +0x1308

    void* GetReservedSpots();                                        // 0x0098f5a0
    void* GetKeepClearSpots();                                       // 0x00cc7070
    void  GetRCluster(const Vec3_s00db7d60* pos, ClusterMap_s00db7d60* cluster,
                      unsigned face);                                // 0x00cc8670
    void  FilterRCluster(ClusterMap_s00db7d60* dst, void* src);      // 0x00cc7fa0
    unsigned GetClosestInRVector(ClusterMap_s00db7d60* cluster,
                                 const Vec3_s00db7d60* pos);         // 0x00cc79d0
    bool  ReserveRCoord(unsigned rcoord);                            // 0x00cc8140
    Vec3_s00db7d60* PosFromRCoord(Vec3_s00db7d60* out, unsigned rcoord); // 0x00cc78f0
    void  FreeRCoord(unsigned rcoord);                               // 0x00cc7f90
};
struct Tribe_s00db7d60 {
    void* mpVtbl;                            // +0x0000
    unsigned char mPad004[0x558 - 0x004];
    ReservationGrid_s00db7d60 mGrid;         // +0x0558

    void* V_AC() {
        return (*(void* (__thiscall**)(void*))(*(char**)this + 0xac))(this);
    }
    Vec3_s00db7d60* GetToolPosition(Vec3_s00db7d60* out, int kind);  // 0x00c91190
};
struct Tool_s00db7d60 {
    void* mpVtbl;                            // +0x0000

    int V_74() {
        return (*(int (__thiscall**)(void*))(*(char**)this + 0x74))(this);
    }
};
struct Creature_s00db7d60 {
    void* mpVtbl;                            // +0x0000

    void* GetActiveTool();                                           // 0x00c23290
    Tribe_s00db7d60* GetTribe();                                     // 0x00c22f50
};
struct PlanetModel_s00db7d60 {
    void* mpVtbl;                            // +0x0000

    Vec3_s00db7d60* MakeRandomWorldPosition(Vec3_s00db7d60* out,
                                            const Vec3_s00db7d60* toolPos,
                                            float minOffset,
                                            float maxOffset);        // 0x00b81780
    Vec3_s00db7d60* DirectionToSurfacePosition(Vec3_s00db7d60* out,
                                               const Vec3_s00db7d60* dir); // 0x00b815a0
};
PlanetModel_s00db7d60* PlanetModel_s00db_7d60();        // 0x00b3d350
struct IdleBlock_s00db7d60 {
    unsigned mState;                         // +0x00
    unsigned mReservedSpot;                  // +0x04
    unsigned mAnimationID;                   // +0x08
    int      mLoopCount;                     // +0x0c
    float    mTimer;                         // +0x10
    Creature_s00db7d60* mpTribeMember;       // +0x14

    Vec3_s00db7d60* FUN_00db7d60(Vec3_s00db7d60* out,
                                 const Vec3_s00db7d60* in);
};
// ---- items of slice s00db7d60 end

// ---- items of slice s00db7fc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned FUN_00921340(unsigned n);    // 0x00921340
struct FixedPoolBase_00db7fc0 {
    void* mpHead;                               // +0x00
    void  init(void* pMemory, unsigned int memorySize, unsigned int nodeSize,
               unsigned int alignment, unsigned int alignmentOffset);   // 0x00921260
};
struct TempAlloc_00db7fc0 {                     // temporary allocator on the stack
    FixedPoolBase_00db7fc0 mPool;               // +0x00
    void*   mUnk04;                             // +0x04
    void*   mBegin;                             // +0x08
    void*   mEnd;                               // +0x0c
    unsigned mCount;                            // +0x10
    void*   mExtra;                             // +0x14
};
struct RehashPolicy_00db7fc0 {
    float    mLoadFactor;                       // +0x00
    float    mGrowthFactor;                     // +0x04
    unsigned mnNextResize;                      // +0x08
    unsigned get_next_bucket_count(unsigned n); // 0x009213c0 (inlined)
};
struct Table_00db7fc0 {
    void*  mpUnk00;                             // +0x00
    void*  mpBucketArray;                       // +0x04
    unsigned mnBucketCount;                     // +0x08
    unsigned mnElementCount;                    // +0x0c
    RehashPolicy_00db7fc0 mRehashPolicy;        // +0x10
    int    mF14;                                // +0x14
    int    mF18;                                // +0x18
    char   mPoolPad[0x1c];                      // +0x1c .. +0x33
    void*  mPoolControl;                        // +0x34
    char   mPad38[0x24];                        // +0x38 .. +0x5b
    char   mTempArena[0xa0];                    // +0x5c .. +0xfb

    void   Parse(unsigned int n);               // 0x00921340
    void*  SetBuckets(unsigned int n, void* p2, void* r3, void* r4, void* v5,
                      void* r6, void* temp);    // 0x00db3cf0
    void   Sub_00db5d70(void* a, void* b, void* c, void* d);   // 0x00db5d70
    void   Sub_00daee00(unsigned int n);                       // 0x00daee00

    Table_00db7fc0* Init(void* p2, void* p3);
};
// ---- items of slice s00db7fc0 end

// ---- items of slice s00dbaa40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PickContext;
struct Node;
struct Action;
struct NodeVtable {
    void* unused[0x58 / 4];                            // 0x00 .. 0x54
    int (__thiscall* GetKind)(Node* self);             // 0x58
};
struct Action {
    int GetState();                                    // 0x008e7f80, 2 means unusable
};
struct Node {
    NodeVtable* vtable;                                // 0x000
    unsigned char reserved[0x120 - 4];                 // 0x004 .. 0x11f
    Action action;                                     // 0x120
    int Classify();                                    // 0x00c9d110, 1 for the preferred node
};
struct NodeList {
    Node** begin;                                      // 0x00
    Node** end;                                        // 0x04
};
struct TableIterator {
    int IsValid();                                     // 0x00af9f30, nonzero when the entry is usable
};
struct SelectionTable {
    TableIterator* Find(const int& kind);              // 0x00c27d20
};
struct ContextVtable {
    void* unused0[0xac / 4];                           // 0x00 .. 0xa8
    Node* (__thiscall* GetCurrent)(PickContext* self); // 0xac
    void* unused1[3];                                  // 0xb0 .. 0xb8
    NodeList* (__thiscall* GetNodes)(PickContext* self); // 0xbc
};
struct PickContext {
    ContextVtable* vtable;                             // 0x000
    unsigned char reserved[0x394 - 4];                 // 0x004 .. 0x393
    SelectionTable table;                              // 0x394
};
// ---- items of slice s00dbaa40 end

// @ 0x00d9cf70
void S_s00d9_cd90::FUN_00d9cf70()
{
  char* self = (char*)this;
  void* nouns = FUN_00b3d300_s00d9_cd90();
  int empire = FUN_00b1f9d0_s00d9_cd90();
  int a = ((int (__thiscall*)(void*, int))VFn_s00d9_cd90(self, 0x4c))(self, empire);
  int rel = (int)FUN_00b3d2c0_s00d9_cd90(a);
  int v = FUN_00d00a70_s00d9_cd90((void*)rel, a, 1);
  if (v != 4) return;
  void* strat = FUN_00cd40b0_s00d9_cd90();
  char c = FUN_00cd5550_s00d9_cd90(strat);
  if (c != 0) return;
  void* nm = FUN_00b3d300_s00d9_cd90();
  int community = (int)FUN_00bfc5f0_s00d9_cd90(nm);
  if (community == 0) return;
  int leader = (int)FUN_00c00650_s00d9_cd90((void*)community);
  int cit = 0;
  if (leader != 0) cit = ((int (__thiscall*)(void*, unsigned))VFn_s00d9_cd90((void*)leader, 0xc))((void*)leader, 0x4f176642u);
  int vec = (int)((void* (__thiscall*)(void*))VFn_s00d9_cd90((void*)community, 0x90))((void*)community);
  int i0 = *(int*)vec, i1 = *(int*)(vec + 4);
  for (int it = i0; it != i1; it += 4) FUN_00bc97f0_s00d9_cd90(0x800000, 0, 10.0f, self);
  int vec2 = (int)((void* (__thiscall*)(void*))VFn_s00d9_cd90(self, 0x90))(self);
  int j0 = *(int*)vec2, j1 = *(int*)(vec2 + 4);
  for (int it = j0; it != j1; it += 4) FUN_00bc97f0_s00d9_cd90(0x800000, 0, 10.0f, self);
  void* tm = FUN_00b3d4d0_s00d9_cd90();
  FUN_00ae0930_s00d9_cd90(tm, "TRG_TotemPole_Social", 1, 1, 0, 0, 0);
  int tgt = (cit == 0) ? 0 : cit + 0xc0;
  void* t = FUN_00ad7a30_s00d9_cd90(tgt);
  void* tm2 = FUN_00b3d4d0_s00d9_cd90();
  FUN_00ae09b0_s00d9_cd90(tm2, 0xcd5f0ca4u, t);
  FUN_00ad7ad0_s00d9_cd90();
  void* s2 = FUN_00cd40b0_s00d9_cd90();
  FUN_00cdab10_s00d9_cd90(s2);
}

// @ 0x00d9dce0
char RunCombatBehavior(cSimCreature* pCreature, void* pA, void* pB, void* pC, void* pD, cBehaviorTask* pTask)
{
    uint8_t mEventData[0x44];
    void* pTarget = pCreature->GetCombatTarget();
    if (!IsValidCombatTarget(pTarget)) {
        SetBehaviorState(pCreature, 0x14);
        return 0;
    }

    switch (pTask->mnState) {
    case 0:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            void* pLocation = pCreature->mLocation.GetObject();
            if (pLocation != nullptr)
                AttachTargetInfo(pCreature, pTarget, pLocation);
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId))
            pTask->mnState = 1;
        break;

    case 1:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            pCreature->StopLocomotion(0, -1);
            int32_t nCount = 5;
            void* pData = ((cSimCreature*)pTarget)->GetTargetData();
            if (pData != nullptr)
                nCount = GetUniverseConstant(((cTargetData*)pData)->mnCount,
                                             0xeb69140e, 5);
            void* pLocation = pCreature->mLocation.GetObject();
            uint32_t* pLink = GetActionLink(pCreature);
            float fDistance = ((cNounManager*)NounManager_s00d9_dce0())->GetDistance(
                pLink, (float)nCount, 0);
            if (fDistance < 0.0f) {
                float fRadius = ((cActionObject*)pCreature->GetActionObject())
                                    ->GetRadius();
                ((cNounManager*)NounManager_s00d9_dce0())->MoveTo(
                    pLocation, pLink, pTask->mnAnimId ? fDistance : fRadius, 6);
                SetBehaviorState(pCreature, 0x14);
                return 0;
            }
            pCreature->mMovement.CallVoid(0x2c);
            ((cNounManager*)NounManager_s00d9_dce0())->MoveTo(pLocation, pLink, -fDistance,
                                                   6);
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId))
            pTask->mnState = 2;
        break;

    case 2:
        pCreature->NotifyTargetLost();
        pCreature->ResetPose();
        break;

    case 3:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            void* pLocation = pCreature->mLocation.GetObject();
            if (pLocation != nullptr)
                AttachTargetInfo(pCreature, pTarget, pLocation);
            void* pWorld = WorldManager();
            void* pRecord = ((cWorldManager*)pWorld)->FindObject(pLocation);
            if (pRecord != nullptr) {
                void* pEpisode = ((cWorldManager*)WorldManager())
                                     ->GetObjectData(pRecord);
                if (pEpisode != nullptr)
                    ((cEpisodeObject*)pEpisode)->GetRecord();
            }
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId))
            pTask->mnState = 4;
        break;

    case 4:
        if (pCreature->GetBehaviorPhase() == 1) {
            void* pEpisode = CreateEpisodeObject(pA, pB);
            if (pEpisode != nullptr)
                ((cEpisodeObject*)pEpisode)->GetRecord();
        }
        pCreature->UpdatePose();
        SetBehaviorState(pCreature, 0x14);
        pCreature->UpdateAttackTarget();
        SetBehaviorState(pCreature, 0x14);
        break;

    default:
        break;
    }
    return 1;
}

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

// @ 0x00da6090
u64 __cdecl FUN_00da6090_s00da_5900(u32 index)
{
    switch (index) {
    case 0:  return 8;
    case 1:  return 0x10;
    case 2:  return 0x20;
    case 3:  return 0x40;
    case 4:  return 0x80;
    case 28: return 0x800000000000000;
    case 5:  return 0x100;
    case 6:  return 0x200;
    case 7:  return 0x400;
    case 8:  return 0x800;
    case 9:  return 0x2000;
    case 10: return 0x8000;
    case 11: return 0x20000;
    case 12: return 0x40000;
    case 13: return 0x80000;
    case 14: return 0x100000;
    case 15: return 0x200000;
    case 20: return 0x8000000;
    case 21: return 0x1000;
    case 22: return 0x10000000;
    case 24: return 0x1000000;
    case 25: return 0x10000000000000;
    case 26: return 0x10000;
    case 27: return 0x4000000;
    default: return 0;
    }
}

// @ 0x00da61e0
void __cdecl FUN_00da61e0(cSPCreatureCitizen_s00da_5900* c, int order)
{
    int* p = c->mpBTree->FirstPending();
    if (p != 0 && *p == order) {
        c->mpBTree->PopFront();
        c->mpBTree->mStimuli.ClearAll(0x1d3fbffa, 0x8124080);
        return;
    }
    u64 v = FUN_00da6090_s00da_5900((u32)order);
    c->mpBTree->mStimuli.ClearAll((u32)v, (u32)(v >> 32));
}

// @ 0x00da6240
bool __cdecl FUN_00da6240(cSPCreatureCitizen_s00da_5900* c, u32 lo, u32 hi)
{
    c->mpBTree->mStimuli.ClearAll(lo, hi);
    c->ForceOrdersUpdate();
    return false;
}

// @ 0x00da6270
bool __cdecl FUN_00da6270(cSPCreatureCitizen_s00da_5900* c, int order)
{
    int* p = c->mpBTree->FirstPending();
    if (p != 0 && *p == order) {
        c->mpBTree->PopFront();
        c->mpBTree->mStimuli.ClearAll(0x1d3fbffa, 0x8124080);
    } else {
        u64 v = FUN_00da6090_s00da_5900((u32)order);
        c->mpBTree->mStimuli.ClearAll((u32)v, (u32)(v >> 32));
    }
    c->ForceOrdersUpdate();
    return false;
}

// @ 0x00da63e0
void __cdecl FUN_00da63e0(cSPCreatureCitizen_s00da_5900* c, cTribe_s00da_5900* tribe)
{
    FUN_00da62d0(c, tribe, 0, 0x80);
    FUN_00da62d0(c, tribe, 0x400, 0);
    FUN_00da62d0(c, tribe, 0, 0x2000);
    FUN_00da62d0(c, tribe, 0, 0x20000);
    FUN_00da62d0(c, tribe, 0, 0x4000);
    FUN_00da62d0(c, tribe, 0x800, 0);
    FUN_00da62d0(c, tribe, 0x200000, 0);
    FUN_00da62d0(c, tribe, 0, 0x1000000);
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
            stim->mTarget = static_cast<Combatant*>(reinterpret_cast<StimulusCombatantCitizen*>(s));
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00da6b10
u8 __cdecl FUN_00da6b10(cSPCreatureCitizen* a, cSPCreatureCitizen* b)
{
    u8 set = 0;
    int id1 = a->v4c();
    int id2 = b->v4c();
    if (id1 == id2)
        goto done;
    if (b->mpOrders->FindSlot(0, 2, 0, 0) != -1 ||
        b->mpOrders->FindSlot(1, 2, 0, 0) != -1 ||
        b->mpBTree->mKey1d8 == 0xd59a3b60)
        set = true;
    u32 v = ((RelMgr*)FUN_00b3d2c0(id1, id2, 1))->FUN_d00a70();
    if (set || v > 1)
        return 0;
    return 1;
done:
    return set;
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
    cSPCreatureCitizen* citizen = c;
    if (citizen->FUN_c0b9c0() < g_f147c21c)
        return 0.0f;
    return citizen->mCombat.GetHealthPct() * g_f13ec4d0 < g_f1687a14 ? 1.0f : 0.0f;
}

// @ 0x00da6d10
float __cdecl FUN_00da6d10(cSPCreatureCitizen* c)
{
    cSPCreatureCitizen* citizen = c;
    if (citizen->FUN_c0b9c0() < g_f147c21c)
        return 0.0f;
    return citizen->mCombat.GetHealthPct() * g_f13ec4d0 < g_f1687a10 ? 1.0f : 0.0f;
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
    cSPCreatureCitizen* cCopy = c;
    float r;
    if (cCopy->GetTribe()->mTimer20c.GetTimer() == 0.0f &&
        cCopy->mTimer34.GetTimer() == 0.0f &&
        cCopy->FUN_c0b9c0() < g_f1687a0c)
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
            stim->mTarget = static_cast<Combatant*>(reinterpret_cast<StimulusCombatantCitizen*>(s));
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
        stim->mTarget = static_cast<Combatant*>(reinterpret_cast<StimulusCombatantCitizen*>(s));
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
    cTribe* tribe = c->GetTribe();
    cTool* tool = tribe->GetToolOfType(v);
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

void* __cdecl FUN_00b3d350_s00da_6880(void* out, u32 v);   // 0x00b3d350 PlanetModel

// @ 0x00da7340
u8 __cdecl FUN_00da7340(cSPCreatureCitizen* c)
{
    cTribe* t = c->GetTribe();
    float f10 = t->v60();
    float f9 = c->mSubC0.v74(f10);
    int v = t->mCombat.v2c(f9);
    char buf[12];
    void* pm = FUN_00b3d350_s00da_6880(buf, v);
    FUN_00b81780(pm);
    c->InterruptAnimation(0x2c38d92, -1, 0);
    float d = c->mSubC0.v74(f10);
    c->MoveToPointAtSpeed(3, buf, d, d + d);
    MoveGoal* l = (MoveGoal*)c->mSubC0.FUN_c41ec0();
    l->mFlags70 |= 2;
    return 1;
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
    struct BTreeFlags { char pad[0x1c8]; unsigned __int64 mFlags64; };
    char v = c->mSubC0.vf8();
    c->FUN_c14750(v == 0);
    if ((((BTreeFlags*)c->mpBTree)->mFlags64 & 0x2000000ui64) == 0)
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

// @ 0x00da7c50
void FinishTribeSpot(Creature* pCreature, u32, u32, u32, u32, TribeSpotState* pState)
{
    if (pState->mpReservation && pState->mIndex != 0xffffffffu)
        pCreature->GetTribe()->ReleaseSpot(pState->mpReservation, pState->mIndex);
    if (!pCreature->mByte_b5e) {
        pCreature->mObjC0.V_ec();
        pCreature->SetActionLocked(!pCreature->mObjC0.V_f8());
    }
}

// @ 0x00da7dc0
void ReleaseTribeReservation(Creature* pCreature, u32, u32, u32, u32, TribeReservationState* pState)
{
    pCreature->d0c0(6, 0);
    pCreature->SetActionLocked(!pCreature->mObjC0.V_f8());
    if (pState->mReservation != 0xffffffffu) {
        cTribe_s00da_7780* tribe = pState->mpOwner->GetTribe();
        tribe->mSub558.FUN_00cc7f90(pState->mReservation);
        pState->mReservation = 0xffffffffu;
    }
}

// @ 0x00da82a0
Elem250* FUN_00da82a0(Elem250* first, Elem250* last, Elem250* dst)
{
    if (first != last) {
        Elem250* p = first;
        Elem250* d = dst;
        do {
            if (((u8)(p->mFlags >> 31) & 1) == 0) {
                ElemFn0 fn = *(ElemFn0*)p->mpObj;
                fn(&p->mpObj, 0);
            }
            ++p;
            ++d;
        } while (p != last);
        dst = d;
    }
    return dst;
}

// @ 0x00da82f0
f32 FUN_00da82f0(Creature* p, i32 v)
{
    i32 n = 0;
    PtrVec* vec = p->V_90();
    Creature** it = vec->mBegin;
    Creature** end = vec->mEnd;
    if (it != end) {
        do {
            n += ((*it)->mpAgentOrders->mRecs[0].mField78 == v);
            ++it;
        } while (it != end);
    }
    i32 cnt = (i32)(vec->mEnd - vec->mBegin);
    return (f32)n / (f32)(u32)cnt;
}

// @ 0x00da8370
bool FUN_00da8370(Creature* p, i32 v, void* a)
{
    if (p != 0) {
        OrderRec* q = p->mpAgentOrders->FirstPending();
        if (q != 0 && q->mField00 == (u32)v) {
            q->mRef28.operator=(a);
            return 1;
        }
    }
    return 0;
}

// @ 0x00da83b0
float TribeMemberStateFraction(Creature* pCreature, int state)
{
    int count = 0;
    PtrVec* members = pCreature->V_90();
    Creature** first = members->mBegin;
    Creature** last = members->mEnd;
    for (; first != last; ++first)
        count += (reinterpret_cast<TribeMemberStateInterface*>(&(*first)->mLoco.mSub58)->GetState() == state);
    return (float)count / (unsigned)(members->mEnd - members->mBegin);
}

struct AnimalHead_da8960 { char pad[0x5a8]; };
struct AnimalLink_da8960 { int m0; };
struct AnimalObj_da8960 : AnimalHead_da8960, AnimalLink_da8960 {};

// @ 0x00da8960
float10 FUN_00da8960(int self, int a2, int a3, int a4, void* stimuli, char* out)
{
    void* anim = ((PlayObj*)((char*)*(void**)(self + 0xb4c) + 8))->Play(0x4000000, 0);
    if (((CreatureBase_s00da_8630*)self)->IsSomething()) {
        void* s = GetAnimalFromStimulus(anim);
        if (s && *(char*)((char*)s + 0xb5e) != 0 && *(float*)((char*)s + 0xb84) > 0.0f) {
            if (stimuli)
                ((Stimuli*)stimuli)->GetAny();
            *(AnimalLink_da8960**)((char*)stimuli + 4) = (AnimalObj_da8960*)s;
            *out = 1;
            return (float10)1;
        }
    }
    int* p = (int*)FUN_00d998d0(anim, 0x2a0349a);
    if (p && *(char*)((char*)p + 0xa9) != 0) {
        bool b = ((bool(__thiscall*)(void*))(*(int*)(p[0] + 0x2c)))(p);
        if (!b && p[0x87] == 0) {
            if (stimuli)
                ((Stimuli*)stimuli)->GetAny();
            *(int*)((char*)stimuli + 8) = (int)p;
            *out = 1;
            return (float10)1;
        }
    }
    FUN_00da6270(self, 0x1b);
    return (float10)0;
}

// @ 0x00da9160
static float g_1581224;   // squared search radius
static float g_1581220;   // result timer

float10 InitNearHutForReaction(Citizen_s00da_bdf0* self, Stimuli* stimuli, char* out)
{
    CTool* tool = (CTool*)self->GetTribe()->V_Ac();
    if (tool == 0)
        return (float10)0;

    Vec3_s00da_bdf0* a = (Vec3_s00da_bdf0*)((Fn_p)VT((char*)self + 0xc0, 0x2c))((char*)self + 0xc0);
    Vec3_s00da_bdf0* b = (Vec3_s00da_bdf0*)((Fn_p)VT((char*)tool + 0x34, 0x2c))((char*)tool + 0x34);

    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    float d = (dz * dz + dx * dx) + dy * dy;

    if (d > g_1581224 * g_1581224)
    {
        if (stimuli)
            stimuli->GetAny();
        stimuli->mp08 = tool;
        stimuli->mi18 = (int)g_1581220;
        *out = 1;
        return (float10)1;
    }
    return (float10)0;
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

// 0x00daab90 (byte-exact lifted version: match/slices/s00daab90/s00daab90.cpp)
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
bool __cdecl FUN_00daadf0(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, uint32_t, StateF0* out)
{    out->m00 = 0;
    out->m04 = 0.0f;
    Tribe* piVar1 = c->GetTribe();
    float fVar4 = piVar1->v60();
    c->mpB4C->mStimuli.ClearAll(0x200000, 0);
    Vec3* pfVar2 = piVar1->mObj120.v2c();
    Vec3* pfVar3 = c->mC0.v2c();
    struct V3 {
        float x, y, z;
        V3 operator-(const V3& o) const {
            V3 r;
            r.x = x - o.x;
            r.y = y - o.y;
            r.z = z - o.z;
            return r;
        }
        float LenSq() const { return z * z + (x * x + y * y); }
    };
    V3 d = *(const V3*)pfVar3 - *(const V3*)pfVar2;
    int res = (d.LenSq() < fVar4 * fVar4) ? 1 : 0;
    out->mFlag08 = (uint8_t)res;
    return true;}

// @ 0x00daaec0
bool __cdecl FUN_00daaec0(Creature_s00da_a530* c, uint32_t, uint32_t, uint32_t, uint32_t, StateEC* out)
{    if ((char)out->pObj->e2c() == 0 && (char)out->pObj->FUN_00c38990(1) == 0) {
        Vec3* pfVar2 = out->pObj->m34.v2c();
        Vec3* pfVar3 = c->mC0.v2c();
        struct V3 {
            float x, y, z;
            V3 operator-(const V3& o) const {
                V3 r;
                r.x = x - o.x;
                r.y = y - o.y;
                r.z = z - o.z;
                return r;
            }
            float LenSq() const { return z * z + (x * x + y * y); }
        };
        V3 d = *(const V3*)pfVar3 - *(const V3*)pfVar2;
        return d.LenSq() < out->mRadius2;
    }
    return false;}

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
    if (p->mp64 == 0 || (p->mp90 != 0 && p->mp90->m08 == 0x2e81370))
        return false;
    _ReadWriteBarrier();

    C05Iface* iface = (C05Iface*)p->mp64;
    C05Result* r = 0;
    return iface != 0
        && (r = iface->a0c(0xd0036e08)) != 0
        && r->mb5e != 0
        && r->mfB84 > g_1485378;
}

// @ 0x00dac630
bool FUN_00dac630(Citizen_s00da_bdf0* self, int a2, int a3, int a4, int a5, St630* st)
{
    st->mb0 = 0;
    st->mi4 = -1;

    self->FUN_00c14750(0);

    CTribe* t = self->GetTribe();
    CTool*  o = (CTool*)((Fn_ac)VT(t, 0xac))(t);
    CTool34& q = o->m34;
    CTool34* qp = &q;

    float sp = ((Fn_f)VT(qp, 0x74))(qp);

    float tmp[3];
    Vec3_s00da_bdf0* dir = (Vec3_s00da_bdf0*)((Fn_p1)VT(qp, 0x5c))(qp, tmp);

    float sx = dir->x * sp;
    float sy = dir->y * sp;
    float sz = dir->z * sp;

    Vec3_s00da_bdf0* pos = (Vec3_s00da_bdf0*)((Fn_p)VT(qp, 0x2c))(qp);

    Vec3_s00da_bdf0 dst;
    dst.x = pos->x + sx;
    dst.y = pos->y + sy;
    dst.z = pos->z + sz;

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

// @ 0x00dadce0
namespace SP {
bool AWARENESS_ATTACK_Tick(cSPCreatureBase_s00da_dce0* c, int, int, int, int, AwarenessAttackBlock* st, int)
{
    cAnimNode* anim = c->mpBehavior->mStimuli.Play(0, 0x2000);
    if (anim == 0)
        return false;
    cSPCreatureBase_s00da_dce0* blk = (cSPCreatureBase_s00da_dce0*)WatchMemoryBlock((uint32_t)anim);
    if (blk == 0)
        return false;

    if (c->mLoco.IsNearGoal()) {
        uint32_t id = 0;
        int count = 0;
        c->mpB54->Query((int*)&id, 0, &count, 0);
        if (id == 0x4cff8) {
            if (count >= 3) {
                c->mpBehavior->mStimuli.SetStimulus(0, 0x80, g_1486110_s00da_dce0,
                                                    blk->GetAnimEvent(0xee3f516e));
                return false;
            }
        }
        else if (!c->FUN_00c0e0c0(0x4cff8)) {
            c->mTimer.Restart();
            c->PlayAnimationWithTargetObj(0x4cff8, &blk->mLoco, -1, -1);
        }
    }
    return true;
}
}  // namespace SP

// @ 0x00daddd0
namespace SP {
bool AWARENESS_GREET_Activate(cSPCreatureBase_s00da_dce0* c, int, int, int, int, GreetBlock* st, int)
{
    cAnimNode* anim = c->mpBehavior->mStimuli.Play(0, 0x1000);
    if (anim == 0)
        return false;
    cSPCreatureBase_s00da_dce0* blk = (cSPCreatureBase_s00da_dce0*)WatchMemoryBlock((uint32_t)anim);
    if (blk == 0)
        return false;

    c->mLoco.GetPosition();
    blk->mLoco.GetPosition();
    c->MoveToPointAtSpeed(2, c->mLoco.GetPosition(), 1.0f, g_1470f1c_s00da_dce0);

    cRelationshipMgr* rm = FUN_00b3d2c0_s00da_dce0();
    uint32_t relation = rm->FUN_00d00a70((uint32_t)c->GetRid(), (uint32_t)blk->GetRid(), 1);

    int arg;
    if (relation <= 1) {
        st->mOrder = 0x3603ac2;
        arg = 1;
    }
    else if (relation == 2) {
        st->mOrder = 0x3603ac1;
        arg = 0;
    }
    else {
        st->mOrder = 0x3603ac1;
        arg = 2;
    }
    c->Notify(&blk->mb5a8, 1, arg);
    return true;
}
}  // namespace SP

// @ 0x00daded0
namespace SP {
bool FUN_00daded0(cSPCreatureBase_s00da_dce0* c, int, int, int, int, uint32_t* st, int)
{
    if (!c->mLoco.IsNearGoal())
        return true;

    uint32_t id = 0;
    int count = 0;
    c->mpB54->Query((int*)&id, 0, &count, 0);

    if (id == *st) {
        if (count < 3)
            return true;
        c->mTimer.Restart();
        c->mpBehavior->mStimuli.ClearAll(0, 0x1000);
        c->ForceOrdersUpdate();
        return false;
    }

    if (c->FUN_00c0e0c0(*st))
        return true;

    cAnimNode* anim = c->mpBehavior->mStimuli.Play(0, 0x1000);
    if (anim == 0)
        return false;
    cSPCreatureBase_s00da_dce0* blk = (cSPCreatureBase_s00da_dce0*)WatchMemoryBlock((uint32_t)anim);
    if (blk == 0)
        return false;
    c->InterruptAnimationWithTargetObj(*st, &blk->mLoco, -1, -1);
    return true;
}
}  // namespace SP

// @ 0x00dadfb0
bool SpawnPlacementTest(SpawnHost* host, int32_t, int32_t, int32_t, int32_t, SpawnOut* out, SpawnIn* in)
{
    RegionOwner* owner = in->owner;
    if (owner != 0) {
        Region* region = owner->FindRegion(0xce9f6639);
        if (region != 0) {
            host->Attach(region, true, false);
            out->zero0 = 0;
            out->radius = (float)ClampRadius(sMathRandomA.RandomDoubleUniform() + 1.0);
            *(uint32_t*)&out->x = *(uint32_t*)&in->x;     // integer copies, as in the original
            *(uint32_t*)&out->y = *(uint32_t*)&in->y;
            *(uint32_t*)&out->z = *(uint32_t*)&in->z;
            out->zero1 = 0;
            const float* p = region->sub.GetPosition();
            float dx = out->x - p[0];
            float dy = out->y - p[1];
            float dz = out->z - p[2];
            float d2 = dx * dx;
            d2 += dy * dy;
            d2 += dz * dz;
            return 1.0f > d2;
        }
    }
    return false;
}

// @ 0x00dae0b0
namespace SP {
bool FUN_00dae0b0(cSPCreatureBase_s00da_dce0* c, int, int, int, int, ChaseBlock* st, float dt)
{
    cSPCreatureBase_s00da_dce0* tgt = (cSPCreatureBase_s00da_dce0*)c->GetTargetAsCreature();
    if (tgt == 0 || tgt->IsTargetable() || tgt->mb135 == 0)
        goto fail;

    {
        const Vec3_s00da_dce0* p = tgt->mLoco.GetPosition();
        float dx = p->x - st->mPos.x;
        float dy = p->y - st->mPos.y;
        float dz = p->z - st->mPos.z;
        float d2 = dx * dx + dy * dy + dz * dz;
        if (d2 > g_1485720_s00da_dce0)
            goto fail;
    }

    switch (st->mState) {
    case 0: {
        c->FUN_00c0d0c0(6, 1);
        float height = c->mLoco.GetSpeed() * FUN_00572a10(1.0f, g_1486114)
                       + tgt->mLoco.GetSpeed();
        float dist = c->mLoco.GetDistance();
        c->MoveToPointAtSpeed(2, &st->mPos, dist, height + dist);
        st->mState = 1;
        break;
    }
    case 1:
        if (c->mLoco.IsNearGoal()) {
            st->mfTimer -= dt;
            if (st->mfTimer < 0.0f) {
                st->mHandle = c->PlayAnimationWithTargetObj(0x2c3900c, &tgt->mLoco, -1, -1);
                st->mState = 2;
            }
        }
        break;
    case 2:
        if (c->AnimationFinished(st->mHandle)) {
            st->mState = 1;
            st->mfTimer = FUN_00572a10(1.0f, g_1470f1c_s00da_dce0);
        }
        break;
    default:
        break;
    }
    return true;

fail:
    c->mpBehavior->mStimuli.SetStimulus(0, 0x20, g_147c218_s00da_dce0, 0);
    return false;
}
}  // namespace SP

// @ 0x00dae2a0
namespace SP {
uint32_t TRIBE_VIGNETTE_Activate(cSPCreatureBase_s00da_dce0* c, int, int, int, int, VignetteBlock* st, VignetteRequest* req)
{
    st->mfTimeout = g_1473c70;
    st->mb4 = 0;
    st->mVignette = -1;

    uint32_t index = req->mIndex & 0xffff;
    uint32_t key = req->mKey;
    // The original stores only the low byte (the flag) into an uninitialised stack dword, so
    // its upper three bytes are the 0xcc stack-fill pattern.  Reproduce the whole word: the
    // callee can observe it (a plain dword test reads a "false" flag as true).
    uint32_t flagWord = 0xcccccc00u | (uint32_t)((req->mIndex & 0xffff0000) != 0);

    cTribe_s00da_dce0* tribe = c->GetTribe();
    if (tribe->m26c == -1) {
        cVecRange* list = FUN_00b3d4e0_a()->FUN_00bc7610(key, 0);
        if (list != 0) {
            uint32_t count = (uint32_t)((char*)list->end - (char*)list->begin) / 0x7b4;
            if (index < count) {
                Vec3_s00da_dce0 tmp;
                void* a = tribe->mSub.Slot5c(&tmp);
                void* b = tribe->mSub.Slot2c(a);
                uint32_t elem = (uint32_t)((char*)list->begin + index * 0x7b4);
                tribe->m26c = (int32_t)FUN_00b3d4e0_b()->FUN_00bc65f0();
                (void)elem;
                (void)b;
            }
        }
        if (tribe->m26c == -1)
            return 0;
    }

    cBundleObj* bundle = (cBundleObj*)c->mBundle.FUN_00cee330();
    if (bundle != 0) {
        float v = bundle->mf134;
        cTribe_s00da_dce0* t1 = c->GetTribe();
        t1->FUN_00c94b50(v);
        cTribe_s00da_dce0* t2 = c->GetTribe();
        void* arg = t2 != 0 ? (void*)&t2->m20c : 0;
        FUN_00b3d2b0_s00da_dce0()->FUN_00ac7eb0(bundle, arg);
    }

    c->mLoco.NotifyEc();
    void* loco = &c->mLoco;
    FUN_00b3d310_s00da_dce0(loco)->FUN_00b45410();

    uint32_t id = (uint32_t)tribe->m26c;
    st->mVignette = (int32_t)id;
    return FUN_00b3d4e0_d()->FUN_00bc4900((void*)id, c, flagWord);
}
}  // namespace SP

// @ 0x00dae420
namespace SP {
float WORSHIP_ARTIFACT_Decide(cSPCreatureBase_s00da_dce0* c, int, int, int, int, int*, int*)
{
    if (c->mpBehavior->mStimuli.Play(0, 0x40000) != 0)
        return 0.0f;

    cTribe_s00da_dce0* tribe = c->GetTribe();
    if (tribe != 0) {
        cTribeVec* v = tribe->GetMembers();
        if ((uint32_t)(v->end - v->begin) < 8)
            return 0.0f;
    }

    cSomeMgr* mgr = FUN_00b3d4e0_d();
    cOrderNode* node = GetOrderManager()->FindNode(0x5e3a55f, (void*)&FUN_00da80f0, c);
    if (node != 0) {
        if (node->IsDone())
            return 0.0f;
        if (mgr->FUN_00bc3df0(node->GetId1(0)))
            return 0.0f;
        c->mLoco.NotifyEc();
        c->mpBehavior->Attach(node, c, 0, 0);
        mgr->FUN_00bc4900(node->GetId3(0, c, 0));
        return 1.0f;
    }

    cVecRange* list = (cVecRange*)c->mLoco.FUN_00c420d0();
    for (uint32_t* it = list->begin; it != list->end; ++it) {
        uint32_t raw = *it;
        if (raw == 0)
            continue;
        cArtifact* art = (cArtifact*)((cListItem*)raw)->Query(0x2dd8c33);
        if (art == 0)
            continue;
        if (!art->IsRare())
            continue;
        if (art->mbab == 0)
            continue;

        uint8_t tmp[12];
        void* a = art->mSub.Slot5c(tmp);
        void* b = art->mSub.Slot2c(a);
        uint32_t target = mgr->FUN_00bc64a0(0xd2ebf76c, 0xa080e6cd, b, a);
        int32_t count = mgr->FUN_00bc3db0(target);

        cOrderNode* created = GetOrderManager()->CreateNode(0x5e3a55f, count, 0x18eb4b7,
                                                           "Domesticate");
        c->mLoco.NotifyEc();
        c->mpBehavior->Attach(created, c, 0, 0);
        created->FUN_00bc9bf0(0, (void*)target);

        cArtifact* old = created->mpObject;
        if (art != old) {
            art->AddRef();
            created->mpObject = art;
            if (old != 0)
                old->Release();
        }
        mgr->FUN_00bc4900(created->GetId3(0, c, 0));
        return 1.0f;
    }
    return 0.0f;
}
}  // namespace SP

// @ 0x00dae630
namespace SP {
bool FUN_00dae630(cSPCreatureBase_s00da_dce0* c, int, int, int, int, DomesticationBlock* st, int)
{
    st->mId = 0;
    st->mb4 = 0;
    cOrderNode* node = c->mpBehavior->mpNode;
    if (node != 0) {
        uint32_t id = node->GetId1(0);
        st->mId = id;
        if (!FUN_00b3d4e0_a()->FUN_00bc3df0(id)) {
            st->mb4 = 1;
            return true;
        }
    }
    return false;
}
}  // namespace SP

// @ 0x00dae680
namespace SP {
void FUN_00dae680(cSPCreatureBase_s00da_dce0* c, int, int, int, int, DomesticationBlock* st, int)
{
    cOrderNode* node = c->mpBehavior->mpNode;
    if (node != 0) {
        uint32_t id = st->mId;
        if (node->GetId1(0) == id) {
            if (node->mState == 1) {
                FUN_00b3d4e0_a()->FUN_00bc5040(id);
                if (st->mb4 != 0) {
                    cTribe_s00da_dce0* tribe = c->GetTribe();
                    if (tribe != 0) {
                        cTribeVec* v = tribe->GetMembers();
                        for (uint32_t* it = v->begin; it != v->end; ++it)
                            ((cSPCreatureBase_s00da_dce0*)*it)->mpBehavior->mStimuli
                                .SetStimulus(0, 0x40000, g_13ebc4c, 0);
                    }
                }
            }
            c->mpBehavior->Refresh();
        }
    }
}
}  // namespace SP

// @ 0x00dae730
namespace SP {
void FUN_00dae730(SlotList* list)
{
    for (uint32_t* it = list->mpBegin; it != list->mpEnd; ++it)
        FUN_00b3d440((void*)*it)->FillSlots();
}
}  // namespace SP

// @ 0x00dae760
namespace SP {
float FUN_00dae760(cSPCreatureBase_s00da_dce0* c)
{
    if (!c->IsLeader())
        return 0.0f;
    if (!c->mLoco.IsAtGoal())
        return 0.0f;
    cAgentOrder_s00da_dce0* order = c->mpBehavior->FirstPending();
    if (order == 0 || order->mTag != 0x16)
        return 0.0f;
    uint32_t id = *order->mPayload.FUN_005727b0();
    cOrderValue* value = (cOrderValue*)c->LookupOrder(id);
    if (value != 0 && value->mTag == 0x34)
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00dae7d0
namespace SP {
float FUN_00dae7d0(cSPCreatureBase_s00da_dce0* c)
{
    if (!c->IsLeader())
        return 0.0f;
    if (!c->mLoco.IsAtGoal())
        return 0.0f;
    cAgentOrder_s00da_dce0* order = c->mpBehavior->FirstPending();
    if (order == 0 || order->mTag != 0x16)
        return 0.0f;
    uint32_t id = *order->mPayload.FUN_005727b0();
    cOrderValue* value = (cOrderValue*)c->LookupOrder(id);
    if (value != 0 && value->mTag == 0x36)
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00dae840
namespace SP {
bool FUN_00dae840(cSPCreatureBase_s00da_dce0* c, int, int, int, int, OrderValueBlock* st, int)
{
    cAgentOrder_s00da_dce0* order = c->mpBehavior->FirstPending();
    if (order == 0 || order->mTag != 0x16)
        return false;

    cOrderPayload* pl = &order->mPayload;
    uint16_t tag = pl->mTag12;
    uint32_t* src;
    if (tag == 0xa || tag == 0x10) {
        if ((pl->mFlags10 & 0x30) != 0)
            src = *(uint32_t**)pl;
        else
            src = tag != 0 ? (uint32_t*)pl : 0;
    }
    else {
        src = (uint32_t*)&g_15d1164;
    }

    uint32_t value = *src;
    st->mValue = value;
    st->mZero4 = 0;
    st->mZero8 = 0;
    return c->LookupOrder(st->mValue) != 0;
}
}  // namespace SP

// @ 0x00dae8c0
namespace SP {
float FUN_00dae8c0(cSPCreatureBase_s00da_dce0* c)
{
    cOrderNode* node = GetOrderManager()->FindNode(0x74eab7f8, 0, c);
    if (c->IsLeader() && c->mLoco.IsAtGoal()) {
        if (node != 0)
            return 0.0f;
        cAgentOrder_s00da_dce0* order = c->mpBehavior->FirstPending();
        if (order != 0 && order->mTag == 0x16) {
            uint32_t id = *order->mPayload.FUN_005727b0();
            cOrderValue* value = (cOrderValue*)c->LookupOrder(id);
            if (value != 0 && value->mTag == 0x38)
                return 1.0f;
        }
        return 0.0f;
    }

    cAnimNode* anim = c->mpBehavior->mStimuli.Play(0, 0x10000000);
    if (anim != 0 && anim->mKind != 1)
        return 0.0f;
    if (node == 0)
        return 0.0f;
    if (!node->IsDone())
        return 1.0f;
    return 0.0f;
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
            src = (int32_t*)&SP::g_15d1164;
        }
        int32_t v = *src;
        a5->f0 = v;
        a5->f4 = 0;
        a5->f8 = 0;
        a5->fC = 0;
        a5->f10 = -1;
        return (uint8_t)(self->base.Slot45(a5->f0) != 0 ? 1 : 0);
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
{    typedef void (__thiscall *SlotFn0)(void*, u32);
    for (; a < b; a = (Slot250*)((char*)a + 0x250)) {
        if (((u8)((uint32_t)a->mFlags >> 31) & 1) == 0) {
            SlotFn0 fn = *(SlotFn0*)*(void**)&a->mObj;
            fn(&a->mObj, 0);
        }
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

extern "C" char FUN_00da6270_s00da_f820(void* a, int b);          // 0x00da6270 (cdecl)

// @ 0x00daf820
char SP_TRIBE_HEAL_SELF_Tick(cCreature* a1, void* a2, void* a3, void* a4, void* a5, HealState* a6)
{
    if (a1->FUN_00c0b9c0() == 0.0)
        return FUN_00da6270_s00da_f820(a1, 5);
    switch (a6->m00)
    {
    case 0:
        if (a1->PutAwayToolExceptFor(0) != 0)
        {
            a1->SetToolOnAnimEvent(0);
            return 1;
        }
        {
            cTribe_s00da_f820* t = a6->m0c;
            Vector3 v;
            float* ps = t->m120.pv11();
            float* pw = a1->mLoco_c0.pv11();
            v.x = pw[0] - ps[0];
            v.y = pw[1] - ps[1];
            v.z = pw[2] - ps[2];
            float r = (float)t->pv24();
            if ((v.z * v.z + v.y * v.y) + v.x * v.x <= r * r)
            {
                a1->mLoco_c0.pv59();
                a6->m00 = 1;
                return 1;
            }
            PlanetModel(&v, t->m120.pv11(), kTwo,
                        (float)t->pv24())->MakeRandomWorldPosition();
            a1->MoveToPointAtSpeed(2, &v, 1.0f, kTwo);
            a6->m00 = 1;
            return 1;
        }
    case 1:
        if (a1->mLoco_c0.FUN_00c42e20() == 0)
            return 1;
        {
            float t1 = (float)(a1->m5a8.pv22() * kDot01);
            void* tool = a6->m0c->GetToolOfType(9);
            float    def;
            uint32_t id;
            if (tool != 0) { def = kFive; id = 0xf3faac05u; }
            else           { def = kTwo;  id = 0xa1b01538u; }
            a6->m08 = (float)(GetPropFloat(g_pPropertyMgr, id, def) * t1 * kDot001);
        }
        a1->FUN_00c12310(0x2796b22, -1, 0);
        a1->FUN_00c12190(0x2796b25, 1, -1);
        a6->m00 = 2;
        a6->m04 = 1;
        return 1;
    case 2:
        if (a1->FUN_00c123f0(0x2796b22) == 0)
            return 1;
        if (a1->FUN_00c0e0c0(0x2796b25) == 0)
            a1->FUN_00c12190(0x2796b25, 1, -1);
        a6->m00 = 3;
        return 1;
    case 3:
        {
            uint32_t sv = ((cBehaviorMgr*)FUN_00b3d260())->pv4();
            a1->m5a8.PartialRepair((float)((double)sv * a6->m08));
            float  hp = a1->m5e0;
            double mx = a1->m5a8.pv22();
            if (hp >= mx)
            {
                a1->FUN_00c12190(0x2796b28, 1, -1);
                a6->m00 = 4;
                a6->m04 = 0;
            }
        }
        return 1;
    case 4:
        if (a1->FUN_00c123f0(0x2796b28) == 0)
            return 1;
        return FUN_00da6270_s00da_f820(a1, 5);
    }
    return 1;
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

// @ 0x00db0130
bool __cdecl SP::TRIBE_NPC_GIFT_Activate(Citizen_s00db_0130* c, int, int, int, int, GiftState* st, ParamObj* prm)
{
    ParamObj* pp = prm;
    if (st) {
        st->mHolder4.mp = 0;
        st->mpTribe = 0;
        st->mpCitizen = 0;
        st->mpTarget = 0;
        st->mHolder14.mp = 0;
    }
    void* anim = c->mpAnim->mCtl.PlayIdleAnimation(0x2000, 0);
    if (anim) {
        AssignRef((IRef*&)st->mpTribe, FUN_00d998d0_s00db_0130(anim, 0x4f396a66));
        if (!st->mpTribe) {
            AssignRef((IRef*&)st->mpCitizen, FUN_00d998d0_s00db_0130(anim, 0x4f176642));
            if (st->mpCitizen)
                ((IWinTextHolder*)&st->mpTribe)->Assign((IRef*)st->mpCitizen->GetTribe());
        }
    }
    if (!st->mpTribe)
        return false;

    st->mi24 = -1;
    st->mf34 = 0.0f;
    if (pp) {
        TargetQuery* q = pp->mpQuery;
        IRef* o = q ? q->Query(0x4ffcdeda) : 0;
        AssignRef((IRef*&)st->mpTarget, o);
    }

    Vec3_s00db_0130 vA, vB, vC;
    struct { Tribe_s00db_0130* t; Citizen_s00db_0130* c; } key = { st->mpTribe, st->mpCitizen };
    GiftTask* task = FUN_00bc9b00_s00db_0130()->Find(0x567cb99, (void*)0xdabbe0, &key);
    if (!task) {
        task = FUN_00bc9b00_s00db_0130()->Create(0x567cb99, 0xf, (void*)0x18eb4b7, "TribeNPCGift");
        GiftBase* g = &task->mGift;
        if (g) {
            g->mpTribe = 0;
            g->mpOther = 0;
        }
        float dflt = kF13ebc5c;
        g->mbFlag = false;
        g->mi18 = 0;
        g->f1c = GetPropertyFloat(g_pProps1581288, 0xd9471e5f, dflt);
        AssignRef(g->mpTribe, (IRef*)st->mpTribe);
        AssignRef((IRef*&)g->mpOther, (IRef*)st->mpCitizen);
        if (g->mpOther)
            g->mpOther->mpAnim->mCtl.FUN_00bc97f0(0, 2, 1.0f, 0);

        Spatial_s00db_0130* loco = &c->mLoco;
        float r;
        if (loco->vf58()) {
            if (g->mpOther) {
                st->mi24 = -1;
                Spatial_s00db_0130* other = &g->mpOther->mLoco;
                const Vec3_s00db_0130* p1 = loco->GetPosition();
                const Vec3_s00db_0130* p2v = other->GetPosition();
                vB.x = p2v->x - p1->x;
                vB.y = p2v->y - p1->y;
                vB.z = p2v->z - p1->z;
                SP::normalized_safe_s00db_0130(&vA, &vB);
                g->pos = *g->mpOther->mLoco.GetPosition();
                Vector3_Normalize(&vB, &g->pos);
                float nx = vA.x, ny = vA.y, nz = vA.z;
                float ux = vB.x, uy = vB.y, uz = vB.z;
                float dot = (ny * uy + nz * uz) + ux * nx;
                g->dir.x = nx - ux * dot;
                g->dir.y = ny - uy * dot;
                g->dir.z = nz - uz * dot;
                g->dir = *SP::normalized_safe_s00db_0130(&vC, &g->dir);
            } else {
                st->mi24 = -1;
                Spatial_s00db_0130* sp = &st->mpTribe->mpObj->mSpatial;
                g->pos = *sp->GetPosition();
                g->dir = *st->mpTribe->mpObj->mSpatial.GetOffset(&vC);
            }
        } else {
            st->mpTribe->vf64();
            vB = *st->mpTribe->FUN_00c91190(&vC, 1);
            vA = vB;
            float k = (loco->GetRadius() + 1.0f) * 4.0f;
            const Vec3_s00db_0130* tp = st->mpTribe->mPos.GetPosition();
            vB.x = vB.x - tp->x;
            vB.y = vB.y - tp->y;
            vB.z = vB.z - tp->z;
            const Vec3_s00db_0130* rv = SP::normalized_safe_s00db_0130(&vC, &vB);
            vA.x = rv->x * k + vA.x;
            vA.y = rv->y * k + vA.y;
            vA.z = rv->z * k + vA.z;
            g->pos = *SP::PlanetModel_s00db_0130()->DirectionToSurfacePosition(&vC, &vA);
            const Vec3_s00db_0130* tp2 = st->mpTribe->mPos.GetPosition();
            vB.x = tp2->x - vA.x;
            vB.y = tp2->y - vA.y;
            vB.z = tp2->z - vA.z;
            SP::normalized_safe_s00db_0130(&vA, &vB);
            g->dir = vA;
        }

        if (st->mpTarget) {
            st->mTargetPos = *st->mpTarget->mSpatial.GetPosition();
            st->mHolder14.Assign(st->mpTarget->mp128);
        }

        Vec3_s00db_0130* q;
        if (g->mpOther) {
            float a = c->GetTribe()->mfRadius * 0.5f;
            a = a + a;
            r = (float)sqrt((double)((float)task->mCount * a * a));
            g->mpEffect = new ("Simulator/GiftActionCircle", 0, 0, 0, 0) EffectCircle();
            float rt = g->mpOther->GetTribe()->mfRadius;
            float h = c->GetTribe()->mfRadius + rt + r;
            vB.x = g->dir.x * h;
            vB.y = g->dir.y * h;
            vB.z = g->dir.z * h;
            const Vec3_s00db_0130* op = g->mpOther->mLoco.GetPosition();
            vA.x = op->x - vB.x;
            vA.y = op->y - vB.y;
            vA.z = op->z - vB.z;
            q = &vA;
        } else {
            float rad = st->mpTribe->mpObj->mSpatial.GetRadius();
            float t1 = c->GetTribe()->mfRadius + rad;
            float a = c->GetTribe()->mfRadius * 0.5f;
            a = a + a;
            r = (float)sqrt((double)((float)task->mCount * a * a));
            g->mpEffect = new ("Simulator/GiftActionCircle", 0, 0, 0, 0) EffectCircle();
            float h = r + t1;
            vB.x = g->pos.x - h * g->dir.x;
            vB.y = g->pos.y - g->dir.y * h;
            vB.z = g->pos.z - g->dir.z * h;
            q = &vB;
        }
        SP::PlanetModel_s00db_0130()->DirectionToSurfacePosition(&vC, q);
        g->mpEffect->FUN_00af9cf0(&vC, r, &g->dir, 0.0f);
        g->mpEffect->FUN_00afef10(0, c->GetTribe()->mfRadius * 0.5f + 1.0f);
        FUN_00d9aa20(g->mpEffect);
    }
    c->mpAnim->FUN_00bcb480(task, c, 0, 0);
    char* b = c->mBundle.FUN_00cee330();
    if (b) {
        if (*(int*)(b + 0x12c) == 5 && !task->mGift.mbFlag) {
            task->FUN_00bc9b20(c);
            st->mHolder4.Assign((IRef*)b);
            task->mGift.mbFlag = true;
        } else {
            FUN_00b3d2b0_s00db_0130()->FUN_00ac7de0(b, FUN_00b3d2b0_s00db_0130()->FUN_00ac79d0());
        }
    }
    st->mDone = 1;
    c->mpB48->FUN_00bca810(1, 2, c, kF147c218, 0, 0);
    if (task->mGift.mpOther)
        c->vf84((char*)task->mGift.mpOther + 0x5a8, 0, 2);
    return true;
}

// @ 0x00db09c0
void __cdecl FUN_00db09c0(Citizen_s00db_09c0* c, int, int, int, int, EatState* st)
{
    c->UpdateLocomotion(0);
    c->vf84(0, 0, 0);

    if (st->mPhase == 4) {
        c->GetTribe()->FUN_00c97d40(0xd, (IRef_s00db_09c0*)c);
    } else if (st->mPhase == 5) {
        c->GetTribe()->FindSpot(0xd, st->mSpot);
    } else {
        if (((Spatial_s00db_09c0*)((char*)c + 0xc0))->IsBundle())
            ((Tribe_s00db_09c0*)st->mpTarget)->FindSpot(0xd, st->mSpot);
    }

    AnimPool* pool = c->mpAnim->mpPool;
    if (pool != 0) {
        AnimNode* anim = ((AnimCtlSub*)((char*)c->mpAnim + 8))->Play(0, 0x80);
        if (anim != 0) {
            // The pool keeps its entries in the inline array at +0x20 (stride 0xc),
            // and every entry but this citizen's own is retargeted at the new clip.
            for (uint32_t i = 0; i < pool->mi18; i++) {
                PoolEntry* e = (PoolEntry*)((char*)&pool->mEntries + i * 0xc);
                if (e->mbActive) {
                    IRef_s00db_09c0* obj = e->mpObj;
                    if (obj != (IRef_s00db_09c0*)c) {
                        AnimCtl_s00db_09c0* other = *(AnimCtl_s00db_09c0**)((char*)obj + 0xb4c);
                        ((AnimCtlSub*)((char*)other + 8))->Stim(
                            0, 0x80, anim->mf08, anim->mWho);
                    }
                }
            }
        }

        PoolNode* node = pool->GetNode();
        if ((void*)c == pool->FUN_00bc9b10()) {
            // The manager is reached through a reference to the strategy's
            // pointer member: that keeps the original's "form the member
            // address, then load the manager" sequence.
            Manager*& mgr = TribeModeStrategy_Instance()->mpMgr;
            mgr->FUN_00bc2180(node->mp28);
            node->mp28 = 0;
        }

        if (st->mPhase == 0x12)
            node->miCount--;

        if (pool->mi10 == 1) {
            if (node != 0) {
                IRef_s00db_09c0* a = node->mp30;
                if (a != 0)
                    a->Release();
                IRef_s00db_09c0* b = node->mp2c;
                if (b != 0)
                    b->Release();
            }
        }
        c->mpAnim->FUN_00bcb430();
    }

    if (c->FUN_00c0c120())
        c->SetSprinting(0);

    IRef1c* p14 = st->mp14;
    if (p14 != 0)
        p14->Release();
    IRef_s00db_09c0* p10 = st->mp10;
    if (p10 != 0)
        p10->Release();
    IRef_s00db_09c0* p0c = st->mp0c;
    if (p0c != 0)
        p0c->Release();
    IRef_s00db_09c0* pTarget = st->mpTarget;
    if (pTarget != 0)
        pTarget->Release();
    IRef_s00db_09c0* pOwner = st->mpOwner;
    if (pOwner != 0)
        pOwner->Release();
}

// @ 0x00db10d0
int __cdecl FUN_00db10d0(Citizen_s00db_10d0* c, int, int, int, int aa, StEat* st, ParamObj_s00db_10d0* prm)
{
    if (st != 0) {
        st->mp0c = 0;
        st->mp10 = 0;
        st->mp14 = 0;
        st->mp18 = 0;
    }
    st->m08 = 0;
    st->m30 = -1;
    st->mf1c = 0.0f;
    st->mf34 = 0.0f;

    int anim = (int)c->mpOrderMgr->mStimuli.Play(0x100000, 0);
    if (prm != 0) {
        IRef* o = (prm->mp8 != 0) ? prm->mp8->Query0c(0x4ffcdeda) : 0;
        IRef* old = st->mp14;
        if (o != old) {
            if (o) o->AddRef();
            st->mp14 = o;
            if (old) old->Release();
        }
    } else if (anim != 0) {
        IRef* o = (IRef*)FUN_00d998d0_s00db_10d0((void*)anim, 0x4ffcdeda);
        IRef* old = st->mp14;
        if (o != old) {
            if (o) o->AddRef();
            st->mp14 = o;
            if (old) old->Release();
        }
        if (*(Tribe_s00db_10d0**)(anim + 0xc) == c->GetTribe())
            aa &= 8;
    }

    if (st->mp14 != 0) {
        VAny* mr = (VAny*)st->mp0c;
        int got = mr ? (int)mr->Query14(0x135b1e8) : 0;
        if (got != (int)Ctx()->GetContainer() && st->mp0c != 0) {
            if (((VAny*)st->mp0c)->Query14(0x4f396a66) != 0)
                goto lab1279;
        }
        {
            const Vec3_s00db_10d0* p = ((VSpatial*)((char*)st->mp14 + 0x34))->GetPosition();
            st->vec24 = *p;
        }
        {
            IRef* o = *(IRef**)((char*)st->mp14 + 0x128);
            IRef* old = st->mp0c;
            if (o != old) {
                if (o) ((VAny*)o)->AddRef18();
                st->mp0c = o;
                if (old) ((VAny*)old)->Rel1c();
            }
        }
        {
            char* v = (char*)st->mp14;
            if (*(int*)(v + 0x12c) == 5) {
                Citizen_s00db_10d0* prev = *(Citizen_s00db_10d0**)(v + 0x120);
                if (prev != c) {
                    ((VAny*)c)->AddRef0();
                    *(Citizen_s00db_10d0**)(v + 0x120) = c;
                    if (prev) ((VAny*)prev)->Rel4();
                }
            }
        }
        goto lab12bc;
    }

lab1279:
    if (c->mBundle.Get() != 0)
        goto lab12bc;
    {
        IRef* o = (IRef*)Ctx()->GetContainer();
        IRef* old = st->mp0c;
        if (o != old) {
            if (o) ((VAny*)o)->AddRef18();
            st->mp0c = o;
            if (old) ((VAny*)old)->Rel1c();
        }
    }

lab12bc:
    if (aa & 2) {
        c->SetStealthed(1, 0);
        if (c->FUN_00c23750() != 0) {
            const Vec3_s00db_10d0* p = c->mLoco.GetPosition();
            if (st->mf34 == 0.0f)
                st->mf34 = FUN_00bc2240(*(void**)((char*)TribeModeInstance() + 0x1c8), p->x, p->y, p->z);
        }
    }
    st->mp04 = c;
    st->mb20 = 0;
    st->m00 = 0;
    if (c->mBundle.Get() != 0) {
        if (aa & 2) {
            void* b = c->mBundle.Get();
            if (*(int*)((char*)b + 0x12c) != 7) {
                Ctx()->FUN_00ac7de0(Ctx()->GetContainer(), b);
                return 1;
            }
        }
        st->m00 = 9;
    }
    return 1;
}

// @ 0x00db1390
void __cdecl FUN_00db1390(Citizen_s00db_10d0* c, int, int, int ea, int, StEat* st)
{
    void* bundle = c->mBundle.Get();
    if (c->OrdersLocked() == 0) {
        c->SetFacing(k169f3b8, k169f3bc, k169f3c0);
        c->SetOrdersLocked(1);
        if (bundle == 0)
            goto lab142d;
        c->FUN_00c23300(bundle, -1);
    }
    if (bundle != 0 && *(float*)((char*)bundle + 0x134) == k1485378)
        Ctx()->FUN_00ac79e0(c != 0 ? c->mBundle.Get() : 0, c != 0 ? (char*)c + 0x34 : 0);

lab142d:
    if (ea & 2) {
        c->SetStealthed(0, 0);
        c->SetSprinting(0);
        FUN_00bc2180(*(void**)((char*)TribeModeInstance() + 0x1c8));
        st->mf34 = 0.0f;
    }
    if (st->mp18 != 0 && st->m30 != -1)
        c->GetTribe()->FindSpot(0xd, st->m30);
    if (c->GetTribe() != 0)
        c->GetTribe()->ReleaseSpot(0xd, c);
    c->FUN_00c25f80();
    {
        VAny* o = (VAny*)st->mp14;
        if (o != 0) {
            Citizen_s00db_10d0* p120 = *(Citizen_s00db_10d0**)((char*)o + 0x120);
            if (p120 == st->mp04 && p120 != 0) {
                *(void**)((char*)o + 0x120) = 0;
                ((IRef*)p120)->Release();
            }
        }
    }
    if (st->mp14 != 0) {
        IRef* p = st->mp14;
        st->mp14 = 0;
        p->Release();
    }
    if (st->mp18) st->mp18->Release();
    if (st->mp14) st->mp14->Release();
    if (st->mp10) st->mp10->Release();
    if (st->mp0c) ((VAny*)st->mp0c)->Rel1c();
}

// @ 0x00db1520
int __cdecl FUN_00db1520(Citizen_s00db_10d0* c, int, int, int, int, StOrders* st, ParamObj_s00db_10d0* prm)
{
    IRef* x = 0;
    if (st != 0) {
        st->mp0c = 0;
        st->mp10 = 0;
    }
    if (prm->mp4 != 0)
        x = prm->mp4->Query5c(0xd0036e08);
    {
        IRef* old = st->mp0c;
        if (x != old) {
            if (x) x->AddRef();
            st->mp0c = x;
            if (old) old->Release();
        }
    }
    if (prm->mp8 != 0)
        x = prm->mp8->Query0c(0x2a0349a);
    else
        x = 0;
    {
        IRef* old = st->mp10;
        if (x != old) {
            if (x) x->AddRef();
            st->mp10 = x;
            if (old) old->Release();
        }
    }
    st->mf04 = (st->mp0c != 0 && ((Citizen_s00db_10d0*)((char*)st->mp0c))->mpb50 != 0) ? k1485720 : 0.0f;
    st->m00 = 0;
    void* f84 = 0;
    if (st->mp10 == 0) {
        const Vec3_s00db_10d0* p = ((VLoco*)((char*)st->mp0c + 0xc0))->GetPosition();
        st->vec14 = *p;
        if (st->mp0c != 0)
            f84 = (char*)st->mp0c + 0x5a8;
    } else {
        const Vec3_s00db_10d0* p = ((VSpatial*)((char*)st->mp10 + 0x34))->GetPosition();
        st->vec14 = *p;
        if (st->mp10 != 0)
            f84 = (char*)st->mp10 + 0x120;
    }
    c->vf84(f84, 0, 0);

    st->mf08 = 0.0f;
    {
        char* o = (char*)st->mp10;
        if (o != 0) {
            void* p1f4 = *(void**)(o + 0x1f4);
            st->mf08 = *(float*)(*(int*)((char*)p1f4 + 0xa4) + 0x570);
            void* a = *(void**)((char*)p1f4 + 0x88);
            void* b = *(void**)((char*)p1f4 + 0xf0);
            void* sp = GetSpeciesArchetype(GetSetting9((int)a, (int)b));
            if (sp != 0)
                st->mf08 = *(float*)((char*)sp + 0x368);
        }
    }
    c->mpOrderMgr->mStimuli.ClearAll(0x4000000, 0);
    return (st->mp0c != 0 || st->mp10 != 0) ? 1 : 0;
}

// @ 0x00db16d0
void __cdecl FUN_00db16d0(Citizen_s00db_10d0* c, int, int, int, int, StEatD* st)
{
    Citizen_s00db_10d0* owner = st->mp0c;
    if (owner != 0 && owner->mpb50 == c) {
        Citizen_s00db_10d0* p = owner->mpb50;
        if (p != 0) {
            owner->mpb50 = 0;
            p->Release();
        }
    }
    StEatSub* sub = (StEatSub*)st->mp10;
    if (sub != 0 && sub->mp21c == c) {
        Citizen_s00db_10d0* p = sub->mp21c;
        if (p != 0) {
            sub->mp21c = 0;
            p->Release();
        }
    }
    c->GetTribe()->FindSpot(0xd, st->m20);
    c->GetTribe()->ReleaseSpot(0xd, c);
    c->vf84(0, 0, 0);
    IRef* p10 = st->mp10;
    if (p10 != 0)
        p10->Release();
    Citizen_s00db_10d0* p0c = st->mp0c;
    if (p0c != 0)
        p0c->Release();
}

// @ 0x00db1790
int __cdecl FUN_00db1790(Citizen_s00db_10d0* c, float lim, int, int, int, StEat* st)
{
    int anim = (int)c->mpOrderMgr->mStimuli.Play(0x80000, 0);
    VAny* o = (VAny*)FUN_00d998d0_s00db_10d0((void*)anim, 0x175cdc9);
    if (o->Call2c() != 0)
        return FUN_00da6270(c, 0xd);
    float thresh = GetPropertyF((int)g_p1e1c, 0xd2078a9b, k1473c70);
    VAny* tool = (VAny*)o->Call30();
    if (tool == 0)
        return FUN_00da6270(c, 0xd);
    char* t = (char*)tool->Query0c(0x4f396a66);
    if (t == 0)
        return FUN_00da6270(c, 0xd);
    if (lim > *(float*)(t + 0x2c0))
        return FUN_00da6270(c, 0xd);

    switch (st->m00) {
    case 0: {
        if (c->mpFC4 == c->mpFC8)
            c->FUN_00c25480(0, 0);
        VAny* r1 = (VAny*)((char*)o + 0x70);
        float v0 = r1->GetRadius() + c->mLoco.GetRadius();
        const Vec3_s00db_10d0* p = ((VSpatial*)((char*)o + 0x70))->GetPosition();
        c->MoveToPointAtSpeed(2, (void*)p, v0 + k1572070, v0 + k157206c);
        st->m00 = 1;
        return 1;
    }
    case 1: {
        if (c->mpFC4 == c->mpFC8)
            c->FUN_00c25480(0, 0);
        if (!c->mLoco.IsNearGoal())
            break;
        const Vec3_s00db_10d0* pa = c->mLoco.GetPosition();
        const Vec3_s00db_10d0* pb = ((VSpatial*)((char*)o + 0x70))->GetPosition();
        Vec3_s00db_10d0 d(pb->x - pa->x, pb->y - pa->y, pb->z - pa->z);
        Vec3_s00db_10d0 out;
        Vec3_s00db_10d0* r = (Vec3_s00db_10d0*)normalized_safe(&out, d, 1.0f, 2.0f);
        c->MoveToPointAndFacingAtSpeed(2, (void*)c->mLoco.GetPosition(), r, 0x3f800000, 0x40000000);
        st->m00 = 2;
        return 1;
    }
    case 2: {
        if (c->mpFC4 != c->mpFC8) {
            if (c->FUN_00c25480(0, 0) == 0)
                break;
        } else if (c->FUN_00c25480(0, 0) == 0)
            break;
        if (!c->mLoco.IsNearGoal())
            break;
        int arg = (int)c->mpFC8;
        const Vec3_s00db_10d0* p = ((VSpatial*)((char*)o + 0x70))->GetPosition();
        c->FUN_00c14990(0x2796b30, (void*)p, arg);
        st->m00 = 4;
        return 1;
    }
    case 4: {
        float ev;
        if (!c->WaitForAnimEventOrEnd(0xbfa50b5a, &ev, -1, 0, 1))
            break;
        float a = ((VAny*)&c->mLoco)->Call38(4);
        float b = *(float*)(t + 0x2c0);        float use = (b > a) ? b : a;
        *(float*)(t + 0x2c0) = *(float*)(t + 0x2c0) - use;
        Ctx()->FUN_00ac7ab0(use, (void*)&c->mLoco, 4);
        st->m00 = 5;
        break;
    }
    default:
        break;
    }
    return 1;
}

// @ 0x00db1c10
int __cdecl FUN_00db1c10(Citizen_s00db_10d0* c, int, int, int, int, StEat* st)
{
    c->InterruptAnimation(0x48601c0, -1, 0);
    Loc74 loc;
    InitLoc74(&loc);
    c->mLoco.vfDC(&loc);
    {
        void* p = *(void**)&loc;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            FUN_00f47380(p);
    }
    c->mpOrderMgr->mStimuli.ClearAll(0x1d3fbffa, 0x81240a0);
    c->ForceOrdersUpdate();
    (void)st;
    return 1;
}

// @ 0x00db1d20
char __cdecl FUN_00db1d20(Citizen_s00db_10d0* c, int, int, int, int, StTool* st, ParamObj_s00db_10d0* ctx)
{
    st->m00 = 0;
    st->m08 = -1;
    st->m0cTool = (int)ctx->mp18;
    st->mp04 = 0;
    Loc74 loc;
    InitLoc74(&loc);
    c->mLoco.vfDC(&loc);
    {
        void* p = *(void**)&loc;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            FUN_00f47380(p);
    }
    c->FUN_00c26c80();
    void* tool = c->GetTribe()->GetToolOfType(st->m0cTool);
    if (tool == 0)
        return 0;
    const Vec3_s00db_10d0* v = ((VSpatial*)((char*)tool + 0x34))->GetPosition();
    st->vec10 = *v;
    return 1;
}

// @ 0x00db1e70
char __cdecl FUN_00db1e70(Citizen_s00db_10d0* c, int, int, int, int, StDom* st)
{
    if (st != 0) st->mp0c = 0;
    int anim = (int)c->mpOrderMgr->mStimuli.Play(0, 0x100000);
    void* o = FUN_00d99980((void*)anim);
    void* animal = FUN_00d99500(o);
    if (animal == 0)
        return (char)FUN_00da6270(c, 0x19);
    st->m00 = 0;
    c->vf84((char*)animal + 0x5a8, 1, 2);
    void* task = OrderManager()->FindNode(0x5656480, (void*)0xda7e20, c);
    if (task != 0)
        return (char)FUN_00da6270(c, 0x19);
    {
        Citizen_s00db_10d0* old = st->mp0c;
        if ((Citizen_s00db_10d0*)animal != old) {
            ((Citizen_s00db_10d0*)animal)->AddRef();
            st->mp0c = (Citizen_s00db_10d0*)animal;
            if (old) old->Release();
        }
    }
    st->m08 = 0;
    st->mp04 = 0;
    void* order = OrderManager()->Create(0x5656480, 1, 0x18eb4b7, kDomesticate);
    OrderManager()->FUN_00bcb480(order, c, 0, 0);
    c->mLoco.vfEC();
    void* pend = OrderManager()->FirstPending();
    if (pend != 0 && *(int*)pend == 0x19) {
        if (*(uint16_t*)((char*)pend + 0x4b) == 0xa) {
            st->m00 = *(int*)FUN_005727b0((char*)pend + 0x39);
            return 1;
        }
        Variant_SetInt((char*)pend + 0x39, st);
    }
    return 1;
}

// @ 0x00db1fb0
void __cdecl FUN_00db1fb0(Citizen_s00db_10d0* c, int, int, int, int, StDom* st)
{
    if (FUN_00d99500(st->mp0c) != 0) {
        Citizen_s00db_10d0* related = *(Citizen_s00db_10d0* volatile*)&st->mp0c;
        related->mpOrderMgr->mStimuli.ClearAll(4, 0);
        st->mp0c->FUN_00c0d0c0(6, 0);
    }
    c->mpOrderMgr->FUN_00bcb430();
    if (c->mb5e == 0) {
        c->mLoco.vfEC();
        if (st->m00 != 0) {
            c->InterruptAnimation(0x5654df4, -1, 0);
            c->FUN_00c14750(0);
        }
    }
    c->vf84(0, 0, 0);
    Citizen_s00db_10d0* pRef = st->mp0c;
    if (pRef)
        pRef->Release();
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
    void** slot = (void**)&pCtx->mpRefC;
    if (*slot != 0) {
        void *p = *slot;
        *slot = 0;
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

struct SocialTargetRef {             // refcounted target: slot 0 is the deleting destructor
    virtual void Destroy(uint32_t flags);
    int mnRefCount;                   // +0x04
};

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

    SocialTargetRef* pTarget = *(SocialTargetRef**)((uint8_t*)pState + 0x0c);
    if (pTarget == nullptr)
        return;
    int nRefs = pTarget->mnRefCount;
    pTarget->mnRefCount = nRefs - 1;
    if (nRefs - 1 == 0) {
        pTarget->mnRefCount = 1;
        _ReadWriteBarrier();
        pTarget->Destroy(1);
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

void* __cdecl FUN_00cd40b0_s00db_5e80(void*);                       // 0x00cd40b0  cTribeModeStrategy::Instance

// @ 0x00db5e80
char __cdecl FUN_00db5e80(void* creature_, void* tribe_)
{
    char* creature = (char*)creature_;
    char* tribe    = (char*)tribe_;
    u32   evt      = 0xab6fe2a9;
    char  ret      = 0;
    int   count    = 0;
    char* herd;

    herd = (char*)((ObjV*)tribe_)->FUN_00c8fee0();
    if (herd == 0)
    {
        ((ObjV*)tribe_)->FUN_00c8fef0();
        herd = (char*)((ObjV*)tribe_)->FUN_00c8fee0();
        if (herd == 0)
            goto L_c2;
    }
    if ((char*)((ObjV*)creature_)->FUN_00c04590() == herd)
        goto L_c2;

    {
        char* it  = *(char**)(herd + 0x40);
        char* end = *(char**)(herd + 0x44);
        ret = 1;
        if (it != end)
        {
            do
            {
                char* e = *(char**)it;
                if (e[0xb5e] == 0)
                {
                    count++;
                    if (*(float*)(e + 0xb20) == *(float*)(creature + 0xb20))
                        ret = 0;
                }
                it += 4;
            } while (it != end);
            if (ret == 0)
            {
                evt = 0xbea77fd3;
                goto L_c2;
            }
        }
        if (!((u32)count < G1581270))
        {
            evt = 0xab6fe2a9;
            goto L_c2;
        }
    }

    evt = 0x4f7d2332;
    FUN_00c0d3a0(creature_);
    FUN_00acca00((char*)((ObjV*)creature_)->FUN_00c04590() + 0x40, (void**)&creature_);
    ((ObjV*)creature_)->FUN_00c045a0(herd);

    {   // eastl::vector<EA::AutoRefCount<cSPCreatureBase>>::push_back at herd+0x40
        void*  keep = creature_;
        void** pos;
        void*  rel;
        if (creature_ != 0)
            ((FnV0)(*(void***)creature_)[0])(creature_);          // AddRef
        pos = *(void***)(herd + 0x44);
        rel = creature_;
        if (pos < *(void***)(herd + 0x48))
        {
            *(void***)(herd + 0x44) = pos + 1;
            if (pos != 0)
            {
                *pos = creature_;
                if (creature_ != 0)
                    ((FnV0)(*(void***)creature_)[0])(creature_);  // AddRef
            }
        }
        else
        {
            ((ObjV*)(herd + 0x40))->FUN_00aea5d0(pos, &keep);
            rel = keep;
        }
        if (rel != 0)
            ((FnV0)(*(void***)rel)[1])(rel);                      // Release
    }

    ((ObjV*)creature_)->FUN_00c042e0();
    {
        u32 u12 = FUN_00b6f0c0(*(u32*)(tribe + 0x234));
        ((FnV1)(*(void***)creature_)[0xe4 / 4])(creature_, (void*)u12);
        ((ObjV*)creature_)->FUN_00c0d950(1);
        u32 u13 = ((FnU0)(*(void***)tribe_)[0x4c / 4])(tribe_);
        ((FnV1)(*(void***)creature_)[0x48 / 4])(creature_, (void*)u13);
    }
    ((ObjV*)FUN_00cd40b0_s00db_5e80((void*)0x84f037b0))->FUN_00cd6980((void*)0x84f037b0);

    if (((FnC0)(*(void***)(tribe + 0x120))[0x58 / 4])(tribe + 0x120) != 0)
    {
        u32 n = ((ObjV*)FUN_00675250(0x9073fca4))->FUN_006766e0(0x9073fca4);
        if ((u32)(count + 1) >= n)
            ((ObjV*)FUN_00675250(0x9073fca4))->FUN_00676710(0x9073fca4);

        {
            u32 loc0 = 0;
            u32 loc1 = 0;
            u32 loc2 = 0;
            u32 bc   = ((ObjV*)creature_)->FUN_00c0bc00(&loc0, *(u32*)(tribe + 0x234), 0, 0);
            void* prof = (char*)((ObjV*)creature_)->FUN_00c0bbd0() + 0x504;
            void* r12  = (char*)((ObjV*)tribe_)->FUN_00c8e820(0) + 0x504;
            void* prop;
            FUN_00e398e0(0x7a7d8111, r12, (void*)bc);
            prop = FUN_0067cb30(0x3110f7cf, prof);
            ((ObjV*)prop)->FUN_0060d860(0x3110f7cf, prof);
        }
    }

L_c2:
    if (((FnC0)(*(void***)(tribe + 0x120))[0x58 / 4])(tribe + 0x120) != 0)
    {
        u32   a;
        void* lg;
        ((ObjV*)SLIST169B41C)->FUN_00fcc200(*(u32*)(creature + 0xb20));
        a  = ((FnU3)(*(void***)(creature + 0xc0))[0x2c / 4])(creature + 0xc0, 0, 1, 0);
        lg = FUN_00b3d3e0(evt, 0x182cd6ce, (void*)a);
        ((ObjV*)lg)->FUN_00dd8640(evt, 0x182cd6ce, (void*)a, 0, 1, 0);
    }
    return ret;
}

// @ 0x00db6130
float __cdecl FUN_00db6130(void* citizen_, void* a2, void* a3, void* a4, char* stimuli_, u8* flag_)
{
    char* tribe  = (char*)((ObjV*)citizen_)->FUN_00c22f50();
    void* tribe_ = (void*)tribe;

    if ((char)((ObjV*)tribe)->FUN_00c8e7c0() != 0)
        return 0.0f;

    if ((char)((ObjV*)(tribe + 0x270))->FUN_00feba90() != 0)
    {
        long long et = ((ObjV*)(tribe + 0x270))->FUN_00bc3190();
        if ((float)((double)et * 0.001f) < 60.0f)
            return 0.0f;
    }

    {
        float* pos1 = ((FnFP0)(*(void***)(tribe + 0x120))[0x2c / 4])(tribe + 0x120);
        float  r    = ((FnF0)(*(void***)tribe_)[0x60 / 4])(tribe_);
        float  r2   = r * r;
        float* pos2 = ((FnFP0)(*(void***)((char*)citizen_ + 0xc0))[0x2c / 4])((char*)citizen_ + 0xc0);
        float  dx   = pos2[0] - pos1[0];
        float  dy   = pos2[1] - pos1[1];
        float  dz   = pos2[2] - pos1[2];
        float  d2   = dz * dz + dy * dy + dx * dx;

        if (d2 > r2)
            return 0.0f;

        {
            int rel = *(int*)(tribe + 0x26c);

            if (rel == -1)
            {
                void*  h    = FUN_00b3d4e0(0x55172d5);
                Cont2* cont = (Cont2*)((ObjV*)h)->FUN_00bc7610(0x55172d5, 0);

                if (cont->mBegin != cont->mEnd)
                {
                    int   local60;
                    float cost;
                    int   ncnt = 0;
                    FVecV vec;
                    int   nrec;

                    {
                        void* tm = FUN_00bc30b0(pos1);
                        int   b  = ((ObjV*)tm)->FUN_00bc2b80(pos1);
                        local60  = 2 - (int)(b != 0);
                    }
                    cost = ((ObjV*)tribe_)->FUN_00fc7f80();

                    {
                        Cont2* elems = (Cont2*)((FnP0)(*(void***)tribe_)[0x90 / 4])(tribe_);
                        char** p     = (char**)elems->mBegin;
                        char** pe    = (char**)elems->mEnd;
                        if (p == pe)
                            return 0.0f;
                        for (; p != pe; p++)
                        {
                            char* e = *p;
                            if ((char)((ObjV*)e)->FUN_00c0b770() != 0
                                && *(char*)(e + 0x135) != 0
                                && *(char*)(e + 0xb5e) == 0
                                && (char)((ObjV*)e)->FUN_00c24560() != 0
                                && (*(u8*)(e + 0xb58) & 0x10) == 0)
                            {
                                float* p2 = ((FnFP0)(*(void***)(e + 0xc0))[0x2c / 4])(e + 0xc0);
                                float  ex = p2[0] - pos1[0];
                                float  ey = p2[1] - pos1[1];
                                float  ez = p2[2] - pos1[2];
                                if (r2 > ez * ez + ey * ey + ex * ex)
                                    ncnt++;
                            }
                        }
                    }
                    if (ncnt <= 0)
                        return 0.0f;

                    rel = -1;
                    {
                        int   relv = -1;
                        u32   u20  = ((FnU0)(*(void***)tribe_)[0x4c / 4])(tribe_);
                        void* pt   = ((ObjV*)FUN_00b3d300())->FUN_00bfc5f0();

                        if (pt != 0 && pt != tribe_)
                        {
                            u32   u21 = ((FnU0)(*(void***)pt)[0x4c / 4])(pt);
                            void* mgr = FUN_00b3d2c0((void*)u20, (void*)u21, 1);
                            relv  = ((ObjV*)mgr)->FUN_00d00a70(u20, u21, 1);
                            rel   = relv;
                        }
                        else
                        {
                            rel = relv;
                        }

                        {
                            u32    mask = 0;
                            Cont2* tools = (Cont2*)((FnP0)(*(void***)tribe_)[0xbc / 4])(tribe_);
                            char** q   = (char**)tools->mBegin;
                            char** qe  = (char**)tools->mEnd;
                            for (; q != qe; q++)
                            {
                                u8 b = (u8)((FnC0)(*(void***)(*q))[0x58 / 4])(*q);
                                mask |= 1u << (b & 0x1f);
                            }

                            {
                                Cont2* recs = cont;
                                u32    kval = 0;

                                nrec = (int)(recs->mEnd - recs->mBegin) / 0x7b4;

                                vec.mBegin    = vec.mInline;
                                vec.mCur      = vec.mInline;
                                vec.mCap      = vec.mInline + 16;
                                vec.mHeapBase = vec.mInline;

                                if (nrec > 0)
                                {
                                    for (int k = 0; k < nrec; k++)
                                    {
                                        char* rec = recs->mBegin + k * 0x7b4;
                                        if (*(float*)(rec + 0x78c) <= cost
                                            && cost <= *(float*)(rec + 0x790)
                                            && (*(int*)(rec + 0x7a0) == 0 || *(int*)(rec + 0x7a0) == local60)
                                            && (*(int*)(rec + 0x7a4) == -1 || rel == -1 || *(int*)(rec + 0x7a4) == rel)
                                            && *(int*)(rec + 0x04) <= ncnt
                                            && (*(u32*)(rec + 0x7ac) == 0 || (*(u32*)(rec + 0x7ac) & mask) == *(u32*)(rec + 0x7ac)))
                                        {
                                            kval = (u32)k;
                                            if (vec.mCur < vec.mCap)
                                            {
                                                *vec.mCur = kval;
                                                vec.mCur++;
                                            }
                                            else
                                            {
                                                vec.FUN_004281d0(vec.mCur, kval);
                                            }
                                        }
                                    }

                                    if (vec.mBegin != vec.mCur)
                                    {
                                        u32 u      = ((ObjV*)RNG1601760)->FUN_00a68fb0((int)(vec.mCur - vec.mBegin));
                                        u32 chosen = vec.mBegin[u];
                                        if (stimuli_ != 0)
                                            ((ObjV*)stimuli_)->FUN_00d997e0();
                                        *(u32*)(stimuli_ + 0x18) = chosen;
                                        *(u32*)(stimuli_ + 0x1c) = 0x55172d5;
                                        *flag_ = 1;
                                        if (vec.mBegin != 0 && vec.mBegin != vec.mInline)
                                            FUN_00f47380(vec.mBegin);
                                        return 1.0f;
                                    }
                                    if (vec.mBegin != 0 && vec.mBegin != vec.mInline)
                                        FUN_00f47380(vec.mBegin);
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                void* tm = FUN_00b3d4e0((u32)rel);
                int   rc = ((ObjV*)tm)->FUN_00bc3db0(rel);
                if (rc > 0)
                {
                    if (stimuli_ != 0)
                        ((ObjV*)stimuli_)->FUN_00d997e0();
                    *(u32*)(stimuli_ + 0x18) = 0;
                    *(u32*)(stimuli_ + 0x1c) = 0;
                    *flag_ = 1;
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00db65a0
float __cdecl FUN_00db65a0(void* citizen_, void* a2, void* a3, u32 nFlags, char* stimuli_, u8* flag_)
{
    char* citizen = (char*)citizen_;
    u8    cVar4;
    u32   fBit5 = (nFlags >> 5) & 1;
    u32   evt;

    if (*(char*)(citizen + 0xf90) == 0 || (nFlags & 0x400) != 0)
        return 0.0f;

    cVar4 = (u8)((ObjV*)citizen_)->FUN_00c0b770();

    // A citizen that is already ordered around skips the probability roll entirely.
    if (fBit5 == 0 && cVar4 == 1)
    {
        void* mgr  = FUN_00bc9b00_s00db_5e80();
        int   node = ((ObjV*)mgr)->FUN_00bca620(0x55241ec, (void*)(u8 (__cdecl*)(cSPCreatureCitizen*, cSPCreatureCitizen*))FUN_00da7140, citizen_);

        if (node != 0)
        {
            if (stimuli_ != 0)
                ((ObjV*)stimuli_)->FUN_00d997e0();
            *flag_ = 1;
            *(int*)stimuli_ = node;
            return 1.0f;
        }
    }

    {
        float prob = FUN_004e1c70(*(const u32*)0x01581288, 0x633e78a1, 0.5f);

        if (((ObjV*)RNG1601760)->FUN_009360d0() > (double)prob)
            return 0.0f;
    }

    if (cVar4 == 0)
        evt = 0x7dcc4e7e;
    else
        evt = (fBit5 != 0 ? 0xb546d379u : 0u) + 0x5523ddcu;

    {
        Cont2* cont = (Cont2*)((ObjV*)FUN_00b3d4e0(evt))->FUN_00bc7610((int)evt, 0);

        if (cont->mBegin == cont->mEnd)
            return 0.0f;

        {
            char*  tribe = (char*)((ObjV*)citizen_)->FUN_00c22f50();
            int    nBest = -1;
            float  fBest = G147C218;
            float* pos   = ((FnFP0)(*(void***)(citizen + 0xc0))[0x2c / 4])(citizen + 0xc0);

            {   // nearest unused spot of the tribe
                VignetteSpot* spots  = *(VignetteSpot**)(tribe + 0x294);
                VignetteSpot* spotsE = *(VignetteSpot**)(tribe + 0x298);
                for (int i = 0; i < (int)(spotsE - spots); i++)
                {
                    VignetteSpot& s = spots[i];
                    float dx, dy, dz, d2;

                    if (s.mFlag10 != 0)
                        continue;
                    dx = pos[0] - s.x;
                    dy = pos[1] - s.y;
                    dz = pos[2] - s.z;
                    d2 = dz * dz + dy * dy + dx * dx;
                    if (fBest > d2)
                    {
                        fBest = d2;
                        nBest = i;
                    }
                }
            }

            if (nBest == -1)
                return 0.0f;

            {
                float* tpos    = ((FnFP0)(*(void***)(tribe + 0x120))[0x2c / 4])(tribe + 0x120);
                int    daypart = 2 - (int)(((ObjV*)FUN_00bc30b0(tpos))->FUN_00bc2b80(tpos) != 0);
                float  cost;
                float  r2;
                int    ncnt = 0;
                int    rel  = -1;
                u32    mask = 0;

                cost = ((ObjV*)tribe)->FUN_00fc7f80();

                {
                    float r = ((FnF0)(*(void***)tribe)[0x60 / 4])(tribe);
                    r2 = r * r;
                }

                {   // citizens already in range of the spot
                    Cont2* elems = (Cont2*)((FnP0)(*(void***)tribe)[0x90 / 4])(tribe);
                    char** p     = (char**)elems->mBegin;
                    char** pe    = (char**)elems->mEnd;

                    for (; p != pe; p++)
                    {
                        char* e = *p;

                        if ((char)((ObjV*)e)->FUN_00c0b770() == 0)
                            continue;
                        if (*(char*)(e + 0x135) == 0)
                            continue;
                        if (*(char*)(e + 0xb5e) != 0)
                            continue;
                        if ((char)((ObjV*)e)->FUN_00c24560() == 0)
                            continue;
                        if ((*(u8*)(e + 0xb58) & 0x10) != 0)
                            continue;
                        if (*(u32*)(*(u32*)(e + 0xb4c) + 0x1d8) == 0x5524115)
                            continue;
                        {
                            float* p2 = ((FnFP0)(*(void***)(e + 0xc0))[0x2c / 4])(e + 0xc0);
                            float  ex = p2[0] - tpos[0];
                            float  ey = p2[1] - tpos[1];
                            float  ez = p2[2] - tpos[2];

                            if (r2 > ez * ez + ey * ey + ex * ex)
                                ncnt++;
                        }
                    }
                }

                {   // tool types available to the tribe
                    Cont2* tools = (Cont2*)((FnP0)(*(void***)tribe)[0xbc / 4])(tribe);
                    char** q     = (char**)tools->mBegin;
                    char** qe    = (char**)tools->mEnd;

                    for (; q != qe; q++)
                    {
                        u8 b = (u8)((FnC0)(*(void***)(*q))[0x58 / 4])(*q);
                        mask |= 1u << (b & 0x1f);
                    }
                }

                {   // relationship class towards the player tribe
                    u32   tid = ((FnU0)(*(void***)tribe)[0x4c / 4])(tribe);
                    void* pt  = ((ObjV*)FUN_00b3d300())->FUN_00bfc5f0();

                    if (pt != 0 && pt != (void*)tribe)
                    {
                        u32   oid = ((FnU0)(*(void***)pt)[0x4c / 4])(pt);
                        void* mgr = FUN_00b3d2c0((void*)tid, (void*)oid, 1);
                        rel = ((ObjV*)mgr)->FUN_00d00a70(tid, oid, 1);
                    }
                }

                {
                    int   nrec = (int)((cont->mEnd - cont->mBegin) / 0x7b4);
                    FVecV vec;

                    vec.mBegin    = vec.mInline;
                    vec.mCur      = vec.mInline;
                    vec.mCap      = vec.mInline + 16;
                    vec.mHeapBase = vec.mInline;

                    if (nrec <= 0)
                        return 0.0f;

                    for (int k = 0; k < nrec; k++)
                    {
                        VignetteRecord* r = (VignetteRecord*)(cont->mBegin + k * 0x7b4);
                        u32 kval = (u32)k;

                        if (r->mfMinCost078C > cost)
                            continue;
                        if (cost > r->mfMaxCost0790)
                            continue;
                        if (r->mnTimeOfDay07A0 != 0 && r->mnTimeOfDay07A0 != daypart)
                            continue;
                        if (r->mnRelation07A4 != -1 && rel != -1 && r->mnRelation07A4 != rel)
                            continue;
                        if (r->mMaxCitizens04 > ncnt)
                            continue;
                        if (r->muToolMask07AC != 0 && (r->muToolMask07AC & mask) != r->muToolMask07AC)
                            continue;

                        if (vec.mCur < vec.mCap)
                        {
                            *vec.mCur = kval;
                            vec.mCur++;
                        }
                        else
                        {
                            vec.FUN_004281d0(vec.mCur, kval);
                        }
                    }

                    if (vec.mBegin != vec.mCur)
                    {
                        u32 u      = ((ObjV*)RNG1601760)->FUN_00a68fb0((int)(vec.mCur - vec.mBegin));
                        u32 chosen = vec.mBegin[u];

                        if (stimuli_ != 0)
                            ((ObjV*)stimuli_)->FUN_00d997e0();
                        *(u32*)(stimuli_ + 0x18) = chosen;
                        *(u32*)(stimuli_ + 0x1c) = (u32)nBest;
                        *(u32*)(stimuli_ + 0x20) = evt;
                        *flag_ = 1;
                        if (vec.mBegin != 0 && vec.mBegin != vec.mInline)
                            FUN_00f47380(vec.mBegin);
                        return 1.0f;
                    }
                    if (vec.mBegin != 0 && vec.mBegin != vec.mInline)
                        FUN_00f47380(vec.mBegin);
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00db6c50
void* __fastcall FUN_00db6c50(void* self_)
{
    char* self = (char*)self_;
    u8    b;

    ((ObjV*)self)->FUN_00ac14d0();
    *(void**)self = VTABLE_147C2C4;
    *(u32*)(self + 0x08) = 0;
    *(u32*)(self + 0x0c) = 0;
    *(u32*)(self + 0x10) = 0;
    *(char**)(self + 0x1c) = self + 0x34;
    *(char**)(self + 0x20) = self + 0x34;
    *(char**)(self + 0x24) = self + 0x54;
    *(u32*)(self + 0x30) = 0;
    ((ObjV*)(self + 0x54))->FUN_00db5c20(&b, &b);

    *(void**)(self + 0x18c) = 0;
    *(void**)(self + 0x190) = 0;
    *(float*)(self + 0x194) = G169F3B8;
    *(float*)(self + 0x198) = G169F3BC;
    *(float*)(self + 0x19c) = G169F3C0;
    *(float*)(self + 0x1a0) = G169F3B8;
    *(float*)(self + 0x1a4) = G169F3BC;
    *(float*)(self + 0x1a8) = G169F3C0;
    *(float*)(self + 0x1ac) = 0.0f;
    *(float*)(self + 0x1b0) = G13EB8A0;
    *(float*)(self + 0x1b4) = G1485720;
    *(float*)(self + 0x1b8) = G1485720;
    *(float*)(self + 0x1bc) = G1485548;
    *(float*)(self + 0x1c0) = G147C21C;
    *(float*)(self + 0x1c4) = G1485720;
    *(float*)(self + 0x1c8) = 0.0f;
    *(u32*)(self + 0x1cc) = 1;
    *(u8*)(self + 0x1d0) = 1;
    *(u8*)(self + 0x1d1) = 1;
    ((ObjV*)(self + 0x1d4))->FUN_00afba10();
    *(u32*)(self + 0x238) = 0;
    *(u32*)(self + 0x240) = 0;
    *(u8*)(self + 0x244) = 0;
    *(u32*)(self + 0x248) = 0;
    *(u8*)(self + 0x23c) = 1;
    return self_;
}

// @ 0x00db6db0
void __fastcall FUN_00db6db0(void* self_)
{
    char* self = (char*)self_;

    *(void**)self = VTABLE_147C2C4;
    ((ObjV*)(self + 0x1d4))->FUN_00afbad0();

    {
        void* o = *(void**)(self + 0x190);
        if (o != 0)
            ((FnV0)(*(void***)o)[0xc0 / 4])(o);
    }
    {
        void* o = *(void**)(self + 0x18c);
        if (o != 0)
            ((FnV0)(*(void***)o)[0xc0 / 4])(o);
    }

    {
        char* s  = self + 0x54;
        ObjV* so = (ObjV*)s;
        void* a1 = *(void**)((char*)so + 4);
        void* a2 = *(void**)((char*)so + 8);
        void* p;
        so->FUN_005941f0(a1, a2);
        p = *(void**)(s + 0x04);
        *(u32*)(s + 0x0c) = 0;
        if (*(u32*)(s + 0x08) > 1 && p != *(void**)(s + 0x30))
        {
            if (p < *(void**)(s + 0x24) || p >= *(void**)(s + 0x28))
            {
                FUN_00f47380(p);
            }
            else
            {
                *(void**)p = *(void**)(s + 0x1c);
                *(void**)(s + 0x1c) = p;
            }
        }
    }

    ((ObjV*)(self + 0x1c))->FUN_00ad92d0();
    {
        void* p2 = *(void**)(self + 0x08);
        if (p2 != 0 && *(u32*)((char*)p2 - 4) != 0)
            FUN_00f47380(p2);
    }
    ((ObjV*)self)->FUN_00ac5430();
}

// @ 0x00db6e60
void cGroupMovement_s00db_6e60::FUN_00db6e60(bool bSkipPoint)
{
    if (bSkipPoint)
        return;
    cCurvePoint point;
    point.mX = mGoal.mX;
    point.mY = mGoal.mY;
    point.mZ = mGoal.mZ;
    point.mW = 1.0f;
    point.mFlags = 0;
    point.mTail = 0;
    mCurve.push_back(point);
}

// @ 0x00db6ef0
void cGroupMovement_s00db_6e60::FUN_00db6ef0(cLocomotiveObject_s00db_6e60* loco)
{
    {
        AutoRefCount_s00db_6e60<cLocomotiveObject_s00db_6e60> holder(loco);
        mEntities.push_back(holder);
    }
    cEntityInfo info;
    info.mDoneTime = 0.0f;
    info.mDistanceFromSlot2 = 0.0f;
    info.mSlotIdx = -1;
    *mInfoMap.FindOrAdd(loco) = info;
    mbFlag1d0 = true;
    mFlags1cc = 1;
}

// @ 0x00db6fa0
void cGroupMovement_s00db_6e60::FUN_00db6fa0(cLocomotiveObject_s00db_6e60* loco)
{
    cMovementIterator it = mInfoMap.find(loco);
    cInfoNode* node = it.mpNode;
    if (node != mInfoMap.mppBucketArray[mInfoMap.mnBucket]) {
        int32_t slotIdx = node->mInfo.mSlotIdx;
        if (slotIdx != -1) {
            SP::cActionCircle_s00db_6e60::tSlot* slot = mActionCircle.SlotAt((uint32_t)slotIdx);
            if (slot != 0 && slot->mOccupied && slot->mReservingId == 0)
                slot->Clear();
        }
        mInfoMap.erase(it);
    }
    RemoveEntity(&mEntities, &loco);
    mbFlag1d0 = true;
}

// @ 0x00db7050
void FUN_00db7050(cSPCreatureBase_s00db_6e60* creature, uint32_t a2, int32_t a3, uint32_t a4, uint32_t a5, cMoveArg* arg)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    creature->mbFlagB64 = arg->mFlag;
    creature->mLocomotive.v0ec();
    creature->UpdateLocomotion(0);
    creature->SetSprinting(0);
    creature->Hover(0);
    creature->v084(0, 0, 0);

    cEntryState* entry = creature->mpLocomotionMgr->mpEntry;
    if (entry != 0) {
        cGroupMovement_s00db_6e60* group = gGroupMovementPool_s00db_6e60.GetObject(entry->mGroupSlotRef);
        if (creature->GetClassId() == 0x18eb4b7 && creature == entry->CurrentId() &&
            group->mSoundId248 != 0) {
            cTribeModeStrategy_s00db_6e60* strategy = cTribeModeStrategy_s00db_6e60::Instance();
            strategy->mpSoundSlots->Release(group->mSoundId248);
            group->mSoundId248 = 0;
        }
        group->FUN_00db6fa0(&creature->mLocomotive);
        if (group->mbFlag23c)
            creature->mpLocomotionMgr->ReleaseEntry();
    }

    if (creature->mLocomotive.v058()) {
        if (arg->mpEffect != 0) {
            IEffect* effect = arg->mpEffect;
            if (effect != 0 && effect->Cast(0x17f243b) != 0)
                EffectPlayer()->PlayEffect(effect);
        }
    }
    if (arg->mpEffect != 0)
        arg->mpEffect->Release();
}

// @ 0x00db7b60
void FUN_00db7b60(Player* self, int a2, int a3, int a4, int a5, Message* msg)
{
  if (!self->flagB5E)
    self->FUN_00c26310(-1);
  self->FUN_00c14750(0);
  self->e8c = -1;
  self->e90 = -1;
  self->e94 = 0.0f;
  self->vec.clear();
  self->Reset(0, 0, 0);
  Game* game = self->game;
  Session* session = game->session;
  if (session) {
    SubState* sub = (SubState*)((char*)session + 0x1a4);
    if (msg->type >= 1 && msg->type <= 4) {
      Info* info = game->channel.FUN_00bc96a0(0, 0x80);
      if (info) {
        for (unsigned int i = 0; i < session->numSlots; i++) {
          Slot* s = &session->slots[i];
          if (s->active) { Player* p = s->player; if (p != self)
            p->game->channel.FUN_00bc97f0(0, 0x80, info->f8, info->f2c); }
        }
      }
    }
    if (self == session->FUN_00bc9b10() && sub->handle) {
      FUN_00cd40b0_s00db_7b60()->rel->FUN_00bc2180(sub->handle);
      sub->handle = 0;
    }
    if (msg->type == 3)
      sub->count--;
    if (session->mode == 1 && sub) {
      if (sub->b) sub->b->Release();
      if (sub->a) sub->a->Release();
    }
    self->game->FUN_00bcb430();
  }
  if (self->FUN_00c0c120())
    self->FUN_00c1ad10(0);
  int index = msg->index;
  if (index >= 0) {
    IndexSource* src = msg->source;
    if (src) { Sink* sink = msg->sink; sink->FUN_00c98750(src->GetValue(), index); }
    else msg->sink->FUN_00c98750(12, index);
  }
  self->FUN_00c0ba10();
  { RefCounted* p = msg->sink; if (p) p->Release(); }
  { RefCounted* p = msg->source; if (p) p->Release(); }
  { RefCounted* p = msg->ref4; if (p) p->Release(); }
}

// @ 0x00db7d60
Vec3_s00db7d60* IdleBlock_s00db7d60::FUN_00db7d60(Vec3_s00db7d60* out, const Vec3_s00db7d60* in)
{
    PlanetModel_s00db7d60* pm;
    float radius;
    Vec3_s00db7d60 pos;
    Vec3_s00db7d60 scratch;
    Vec3_s00db7d60 surf;

    Tool_s00db7d60* tool = (Tool_s00db7d60*)mpTribeMember->GetActiveTool();
    radius = (float)tool->V_74() * 0.3f;
    Tribe_s00db7d60* tribe = mpTribeMember->GetTribe();
    if (tribe->V_AC() != 0) {
        pm = PlanetModel_s00db_7d60();

        // The caller's hint wins; otherwise a random spot around the tool.
        // The tool position only exists on that path, in its own scope.
        const Vec3_s00db7d60* src;
        if (in != 0) {
            src = in;
        } else {
            Vec3_s00db7d60 toolPos;
            src = pm->MakeRandomWorldPosition(&scratch,
                                              tribe->GetToolPosition(&toolPos, 0),
                                              0.0f, radius + 2.0f);
        }
        pos.x = src->x;
        pos.y = src->y;
        pos.z = src->z;

        if (mReservedSpot != 0xffffffffu) {
            Tribe_s00db7d60* t = mpTribeMember->GetTribe();
            t->mGrid.FreeRCoord(mReservedSpot);
            mReservedSpot = 0xffffffffu;
        }

        {
            ClusterMap_s00db7d60 cluster;
            ReservationGrid_s00db7d60* grid = &tribe->mGrid;
            grid->GetRCluster(&pos, &cluster, 4);
            grid->FilterRCluster(&cluster, grid->GetReservedSpots());
            grid->FilterRCluster(&cluster, grid->GetKeepClearSpots());

            if (cluster.mpBegin == cluster.mpEnd) {
                if (in != 0) {
                    *out = *in;
                    cluster.Destroy();
                    return out;
                }
            } else {
                unsigned index = grid->GetClosestInRVector(&cluster, &pos);
                if (index != 0xffffffffu && grid->ReserveRCoord(index)) {
                    Vec3_s00db7d60* cell = grid->PosFromRCoord(&scratch, index);
                    Vec3_s00db7d60* s = pm->DirectionToSurfacePosition(&surf, cell);
                    Vec3_s00db7d60 spot = *s;
                    mReservedSpot = index;
                    out->x = spot.x;
                    out->y = spot.y;
                    out->z = spot.z;
                    cluster.Destroy();
                    return out;
                }
            }
            cluster.Destroy();
        }
    }

    tribe->GetToolPosition(out, 0);
    return out;
}

// @ 0x00db7fc0
Table_00db7fc0* Table_00db7fc0::Init(void* p2, void* p3)
{
    TempAlloc_00db7fc0 temp;
    temp.mPool.mpHead = 0;
    temp.mPool.init(mTempArena, 0xa0, 0x14, 4, 0);
    temp.mBegin = mTempArena;
    temp.mEnd = (char*)temp.mBegin + 0xa0;
    temp.mCount = 0x14;
    temp.mExtra = &mPoolControl;
    unsigned buckets = FUN_00921340(9);
    SetBuckets(buckets, p2, (void*)&p3, (void*)&p3, p3, (void*)&p3, &temp);
    RehashPolicy_00db7fc0* policy = (RehashPolicy_00db7fc0*)&temp;
    policy->mLoadFactor = 10000.0f;
    policy->mGrowthFactor = 2.0f;
    policy->mnNextResize = 0;
    mRehashPolicy = *policy;
    unsigned n = policy->get_next_bucket_count(mnElementCount);
    if (n > mnBucketCount)
        Sub_00daee00(n);
    Sub_00db5d70(p2, (void*)p3, p2, (void*)p3);
    return this;
}

// @ 0x00db86a0
void cGroupFollower::Update(float dt)
{
    if (!((mRepathTimer -= dt) < 0.0f || mbRepath))
        return;
    if (mMembersBegin == mMembersEnd)
        return;

    mRepathTimer = mRepathInterval;
    if (mbReset) {
        ResetMembers();
        mbReset = false;
    }

    if (mpTarget) {
        if (!mpTarget->mbAlive) {
            Object_s00db_86a0* t = mpTarget;
            if (t) {
                mpTarget = 0;
                t->vc0();
            }
            return;
        }
        CastIface* ci;
        if (!mpTarget || !(ci = (CastIface*)mpTarget->Cast(0x017f243b)) || !ci->IsBusy()) {
            Vector3 pos = *mpTarget->GetPosition();
            if (mTargetPos != pos) {
                mTargetPos = pos;
                float r = mRadius;
                if (r > 0.0f)
                    r = r * r;
                else
                    r = 100.0f;
                float dz = mPathGoal.z - mTargetPos.z;
                float dy = mPathGoal.y - mTargetPos.y;
                float dx = mPathGoal.x - mTargetPos.x;
                mbRepath = (dz * dz + dy * dy + dx * dx > r) ? true : false;
                if (mbRepath)
                    mPathGoal = pos;
            }
        }
    }

    float spacing = mSpacing * 2.0f;
    bool grew = false;
    float spread = sqrtf_s00db_86a0((float)(int)(mMembersEnd - mMembersBegin) * spacing * spacing);
    if (spread > mSpread) {
        grew = true;
        mSpread = spread;
    }
    spacing += mSpread;

    if (mbRepath) {
        mPathIndex = 0;
        mPath.clear();
        const Vector3* lp = mpLeader->GetPosition();
        float dz = lp->z - mTargetPos.z;
        float dy = lp->y - mTargetPos.y;
        float dx = lp->x - mTargetPos.x;
        if (dz * dz + dy * dy + dx * dx > 10000.0f) {
            GetPathfinder()->Cancel(this);
            Object_s00db_86a0* leader = mpLeader;
            GetPathfinder()->FindPath(&gAStarSearchLandAvoidCities, leader->GetPosition(), &mTargetPos,
                                      m1b8, mRadius, &mPath, this, leader->v58(0));
        } else {
            mPath.push_back(Waypoint(mTargetPos));
        }
        mbRepath = false;
        mState = 1;
    }

    if (mPath.mpBegin == mPath.mpEnd)
        return;

    Vector3 wp = mPath[mPathIndex].pos;
    bool isLast = mPathIndex == mPath.size() - 1;
    if (isLast) {
        wp = mTargetPos;
    } else {
        const Vector3* lp = mpLeader->GetPosition();
        float dx = lp->x - wp.x;
        float dz = lp->z - wp.z;
        float dy = lp->y - wp.y;
        if (spacing * spacing > dx * dx + dz * dz + dy * dy) {
            mPathIndex += 1;
            wp = mPath[mPathIndex].pos;
            mState = 1;
        }
    }

    PlanetModel_s00db_86a0* planet = GetPlanetModel();
    Quaternion orient;
    planet->BuildSurfaceOrientation(&orient, &wp);
    Matrix3 mat;
    Matrix3FromQuaternion(&mat, &orient);

    if (mFormation.IsPlaced() && !grew) {
        Vector3 p = wp;
        mFormation.mPosition = p;
        mFormation.mOrientation = orient;
    } else {
        mFormation.Place(&wp, &orient, spacing);
        mFormation.Layout(0, mSpacing);
    }

    int mode;
    bool flag;
    Creature_s00db_86a0* cr;
    if (mpLeader && (cr = (Creature_s00db_86a0*)mpLeader->Cast(0xce9f6639)) != 0) {
        mode = cr->GetMode();
        flag = cr->bF90;
    } else {
        mode = 2;
        flag = false;
    }
    if (mCallback && (((ObjectView*)mpLeader)->v58() || mode == 2 || (flag && mode == 1)))
        mCallback(this, &mFormation, 1);
    else
        mFormation.Reset();

    if (mState == 2 || mState == 1) {
        ApplyFormation(&mat);
        mState = 0;
    }

    mAvgDistSq = 0.0f;
    float minSpeed = gGroupMinSpeed;
    float maxSpeed = gGroupMaxSpeed;
    if (isLast && mRadius > 1.5258789e-05f) {
        minSpeed = max_(minSpeed, mRadius);
        maxSpeed = max_(maxSpeed, mRadius);
    }

    for (Object_s00db_86a0 **it = mMembersBegin, **itEnd = mMembersEnd; it != itEnd; ++it) {
        Object_s00db_86a0* obj = *it;
        int key;
        if (obj)
            key = (int)obj->Cast(0x017f243b);
        else
            key = 0;
        MemberInfo& info = mInfo[obj];
        Vector3 target = mTargetPos;
        if (info.mSlot == -2) {
            const Vector3* p = obj->GetPosition();
            float dx = p->x - mTargetPos.x;
            float dz = p->z - mTargetPos.z;
            float dy = p->y - mTargetPos.y;
            mAvgDistSq += dx * dx + dz * dz + dy * dy;
        } else {
            FormationSlot* slot;
            if (info.mSlot < 0 || (slot = mFormation.GetSlot(info.mSlot)) == 0) {
                obj->StopMoving();
                mState = 2;
                continue;
            }
            if (slot->mbTaken && (slot->mOwnerRef != 0 || slot->GetOwner() != key)) {
                obj->StopMoving();
                info.mSlot = -1;
                mState = 2;
                mRepathTimer = 0.0f;
                continue;
            }
            slot->Assign(key);
            const Vector3& o = slot->mOffset;
            Vector3 dir;
            dir.x = o.z * mat.m[2][0] + o.y * mat.m[1][0] + o.x * mat.m[0][0] + wp.x;
            dir.y = o.x * mat.m[0][1] + o.z * mat.m[2][1] + o.y * mat.m[1][1] + wp.y;
            dir.z = o.x * mat.m[0][2] + o.z * mat.m[2][2] + o.y * mat.m[1][2] + wp.z;
            target = planet->DirectionToSurfacePosition(dir);
            const Vector3* p = obj->GetPosition();
            float dz = p->z - target.z;
            float dx = p->x - target.x;
            float dy = p->y - target.y;
            float d = dx * dx + dz * dz + dy * dy;
            info.mDistSq = d;
            mAvgDistSq += d;
        }

        if (info.mTimeNear < 1.5258789e-05f) {
            LocoState* loco = obj->GetLoco();
            bool move = true;
            if (loco->mHasGoal != 0) {
                const Vector3* g = loco->GetGoal();
                float dx = g->x - target.x;
                float dz = g->z - target.z;
                float dy = g->y - target.y;
                move = dx * dx + dz * dz + dy * dy > minSpeed * minSpeed;
            }
            if (move) {
                Creature_s00db_86a0* c = (Creature_s00db_86a0*)obj->Cast(0xce9f6639);
                if (c)
                    c->MoveToPointAtSpeed(2, &target, minSpeed, maxSpeed);
                else
                    obj->MoveTo(&target, minSpeed, maxSpeed, 0);
            }
        }
        if (obj->IsNearGoal() && isLast)
            mInfo[obj].mTimeNear += dt;
    }

    mAvgDistSq = mAvgDistSq / (float)(unsigned)(mMembersEnd - mMembersBegin);
}

// @ 0x00db90c0
void FUN_00db90c0(float dt)
{    GroupRecord* p = gGroupFirst < 0x3fffffffu ? &gGroupBegin[gGroupFirst] : gGroupEnd;
    GroupRecord* last = gGroupEnd;
    if (gGroupEnd == p)
        return;
    do {
        p->mFollower.Update(dt);
        u32 f;
        do {
            GroupRecord* cur = p;
            ++p;
            f = cur->mFlags;
        } while (!((u8)(f >> 30) & 1) && ((u8)(p->mFlags >> 31) & 1));
    } while (last != p);}

// @ 0x00db9130
void IdleBlock::EnterWalk()
{
    u32 invalid = 0xffffffffu;
    if (mReservedSpot != invalid) {
        Tribe_s00db_86a0__b* t = mpTribeMember->GetTribe();
        t->mSub558.FUN_00cc7f90(mReservedSpot);
        mReservedSpot = invalid;
    }
    mpTribeMember->UpdateLocomotion(1);

    Vec3* pos;
    if (mpTribeMember->mLoco.V_58()) {
        Tribe_s00db_86a0__b* t = mpTribeMember->GetTribe();
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
bool FUN_00db9280(Creature_s00db_86a0__b* self, int, int, u32 flags, int, IdleBlock* mem, int, float dt)
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

// @ 0x00db9380
namespace SP {
bool FUN_00db9380(cSPCreatureCitizen_s00db_9380* c, int, int, int, int, cHealActionState* st)
{
    switch (st->mStep) {
    case 0: {
        unsigned nAnimId = c->InterruptAnimation(0x6006755, c->GetAnimationVariant(), 0);
        ++st->mStep;
        st->mAnimId = nAnimId;
        return true;
    }

    case 1: {
        int nTool = -1;
        if (c->WaitForAnimEventOrEnd(0xe95450e, &nTool, 0, st->mAnimId, 1)) {
            c->SetCurrentToolEffect(0, nTool);
            ++st->mStep;
        }
        return true;
    }

    case 2: {
        int nTool = -1;
        if (c->WaitForAnimEventOrEnd(0x7d7502fc, &nTool, 0, st->mAnimId, 1)) {
            c->SetCurrentToolEffect(0x15, nTool);
            ++st->mStep;
            st->mAnimId = c->PlayAnimation(0x609ea47, 1, c->GetAnimationVariant());
        }
        return true;
    }

    case 3: {
        if (c->GetCurrentAnimationGUID() != 0x609ea47)
            return true;
        ++st->mStep;
        st->mAnimId = c->PlayAnimation(0x609ea41, 1, c->GetAnimationVariant());
        c->CancelTool(st->mToolId, true, false);
        FUN_00da61e0(c, 0x16);

        cHealTuningRecord* pTuning = c->GetToolTuning(st->mToolId);
        Loco_s00db_9380* pSelf = &c->mLoco;
        const Vec3_s00db_9380* pSelfPos = pSelf->GetPosition();

        cSpatialObjectList candidates;
        candidates.mpBegin = candidates.mInline;
        candidates.mpEnd = candidates.mInline;
        candidates.mCount = 0;
        candidates.mpCapacity = candidates.mInline + 8;

        cActionSystem* pSystem = GetActionSystem();
        if (!pSystem->v48(pSelf->GetPosition(), pTuning->mRadius + pTuning->mHoldDistance,
                          &candidates, 0, &GetSeparation, c))
            return true;

        float fHealAmount = GetPropertyT(pTuning->mpProperties, 0x83028513, 60.0f);
        cTribeModeStrategy_s00db_9380* pStrategy = cTribeModeStrategy_Instance();
        pStrategy->mHealAmount = fHealAmount;

        int nBudget = GetTutorialToolPrice(pTuning->mpProperties, 0x217997f4, 4);
        int nToolCount = pStrategy->mHealTargets.mpEnd - pStrategy->mHealTargets.mpBegin;
        nBudget -= nToolCount;

        FUN_00c7dc70((void**)candidates.mpBegin, (void**)candidates.mpEnd, *pSelfPos);

        cAutoRefCount ref;
        unsigned nCount = (unsigned)((void**)candidates.mpEnd - (void**)candidates.mpBegin);
        for (unsigned i = 0; i < nCount; ++i) {
            if (nBudget <= 0)
                break;
            void* pVictim = ResolveCreature(((void**)candidates.mpBegin)[i]);
            if (!pVictim)
                continue;
            if (CreatureFlag388(pVictim))
                continue;
            if (((cSPCreatureCitizen_s00db_9380*)pVictim)->mbB5e)
                continue;
            if (!CreatureIsIdle(pVictim))
                continue;
            ref.Init((cAutoRefTarget*)pVictim);
            cTribeModeStrategy_Instance()->mHealTargets.PushBack(&ref);
            ref.Destroy();
            CreatureSnapshot(pVictim);
            cSPCreatureCitizen_s00db_9380* pTarget = (cSPCreatureCitizen_s00db_9380*)pVictim;
            FUN_00bcb660(pTarget->mpEnv, 0x1590b30);
            pTarget->v48(c->v4c());
            pTarget->mpEnv->mMotion.Play(4, 0, 5.0f, c);
            ((cSPCreatureCitizen_s00db_9380*)pVictim)->mLoco.vfec();
            ((cSPCreatureCitizen_s00db_9380*)pVictim)->InterruptAnimation(0x609ea4c, -1, 0);
            CreatureSetField(pVictim, 0x609ea52);
            ((cSPCreatureCitizen_s00db_9380*)pVictim)->mFlagsB58 |= 0x4000;
            --nBudget;
        }
        FUN_00ad92d0(&candidates);
        return true;
    }

    case 4: {
        int nTool = -1;
        if (c->WaitForAnimEventOrEnd(0xe95450e, &nTool, 0, st->mAnimId, 1)) {
            c->SetCurrentToolEffect(0, nTool);
            ++st->mStep;
        }
        return true;
    }

    case 5: {
        int nTool = -1;
        if (c->WaitForAnimEventOrEnd(0x7d7502fc, &nTool, 0, st->mAnimId, 1)) {
            c->SetToolState(nTool);
            ++st->mStep;
        }
        return true;
    }

    case 6:
        if (c->AnimationFinished(st->mAnimId)) {
            c->mpEnv->mMotion.Play(0, 0x20, gHealTimeLimit, 0);
            return false;
        }
        break;
    }
    return true;
}
}  // namespace SP

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

// @ 0x00db9a00
namespace SP {
float FUN_00db9a00(void* pSource, void*, void*, unsigned nFlags, behavior_stimuli_s00db_9380* pStimuli, bool* pbFound)
{
    if ((nFlags & 1) != 0)
        return 0.0f;

    PlanetModel_s00db_9380();

    const Vec3_s00db_9380* pSourcePos = ((cSPCreatureCitizen_s00db_9380*)pSource)->mLoco.GetPosition();
    cNoun* pBest = 0;
    float fBestDistance = 2900.0f;

    cNounRange& range = *NounManager_s00db_9380()->GetGameDataList(NounFilterSpecies, NounFilterAlive,
                                                        NounFilterKind, NounFilterStation,
                                                        &gNounQueryOptions);
    for (cNoun** it = range.mpBegin; it != range.mpEnd; ++it) {
        cNoun* pNoun = *it;
        if (pNoun->IsHealBlocked(1))
            continue;
        const Vec3_s00db_9380* pNounPos = pNoun->mSpatial.GetPosition();
        float fDx = pNounPos->x - pSourcePos->x;
        float fDy = pNounPos->y - pSourcePos->y;
        float fDz = pNounPos->z - pSourcePos->z;
        float fDistance = fDz * fDz + fDx * fDx + fDy * fDy;
        if (fBestDistance > fDistance) {
            pBest = pNoun;
            fBestDistance = fDistance;
        }
    }

    if (!pBest)
        return 0.0f;

    if (pStimuli)
        pStimuli->GetAny();

    *pbFound = true;
    pStimuli->mpTarget = (char*)pBest + 0x508;
    pStimuli->mnDistance = (int)(float)sqrt(2900.0);
    return 1.0f;
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

// @ 0x00dba2f0
float FUN_00dba2f0(void* owner, void* unused2, void* unused3, void* unused4, void* stimuli, unsigned char* found)
{
    char* self = (char*)owner + 0xc0;
    if (!((FnBoolVoid)((void**)*(void***)self)[0x48 / 4])(self))
        return 0.0f;

    void* nouns = FUN_00b3d300();
    GameObjectRef* data = (GameObjectRef*)TCS(void*, (void*, void*, void*, void*, void*, void*),
                                            FUN_00b21340)(
        nouns, (void*)g_00cd7d10, (void*)g_00d3d420, (void*)g_00ae72d0,
        (void*)g_00b1e500, (void*)0x18c6de8);
    PointerList* objects = &data->mObjects;
    if (objects->mpBegin == objects->mpEnd)
        return 0.0f;

    PointerList* list = (PointerList*)TCS(void*, (void*), FUN_00c420d0)(self);
    void** it = list->mpBegin;
    void** end = list->mpEnd;
    while (it != end) {
        void* obj = *it;
        void* vehicle = 0;
        if (obj)
            vehicle = ((FnPtrInt)((void**)*(void***)obj)[0xb8 / 4])(obj, 0x137e8e0);
        if (vehicle) {
            if (stimuli)
                TCS(void*, (void*), FUN_00d997e0)(stimuli);
            cVehiclePartB* part = (cVehiclePartB*)(cVehicleLayout*)vehicle;
            *(void**)((char*)stimuli + 4) = part;
            *found = 1;
            return 1.0f;
        }
        ++it;
    }
    return 0.0f;
}

// @ 0x00dba580
cHealOther* cHealOther::Assign(const cHealOther* other)
{
    bool argNeg = TagIsNegative(other->mTag);
    if (argNeg) {
        if (!TagIsNegative(mTag)) {
            ((void (__thiscall*)(cHealOtherData_s00db_a2f0*, int))((void**)mData.mpVtable)[0])(&mData, 0);
            mTag = other->mTag;
            return this;
        }
    }
    if (!argNeg) {
        if (TagIsNegative(mTag))
            mData.Copy(&other->mData);
        else
            mData = other->mData;
    }
    mTag = other->mTag;
    return this;
}

// ---- items of slice s00dbab60 begin (local stubs)
extern uint8_t  DAT_01581374;
extern int      FUN_00d00780(float v);
extern void     FUN_00b3d2c0(float v);
extern float    SP_normalized_safe(float* a, float* b, float lo, float hi);
extern void cSPCreatureBase_PlayAnimation(void* self, uint32_t clip);
extern void cSPCreatureBase_InterruptAnimation(void* self, uint32_t clip);
extern void cSPCreatureBase_MoveToPointAtSpeed(void* self, void* dst, float speed);
extern void cSPCreatureBase_MoveToPointAndFacingAtSpeed(void* self, int mode, void* dst, float speed, int a, int b);
extern void cSPCreatureBase_SetSprinting(void* self, int on);
extern void cSPCreatureBase_Attack(void* self, void* target);
extern void cSPCreatureBase_PlayIdleAnimation(void* self);
extern uint32_t FUN_00d998d0_s00db_ab60(void* a, uint32_t id);
extern uint32_t FUN_00bc2240(uint32_t id, void* a, void* b, void* c);
extern void     FUN_00bc23d0(void* p, void* a, void* b, void* c);
extern uint32_t FUN_00da6270_s00db_ab60(void* a, int b);                  // 0x00da6270 anim helper
// ---- items of slice s00dbab60 end

// @ 0x00dbaa40
Action* PickAction(PickContext* ctx)
{
    Node* primary = 0;
    Node* secondary = 0;

    NodeList* nodes = ctx->vtable->GetNodes(ctx);
    Node** it = nodes->begin;
    Node** end = nodes->end;
    for (; it != end; ++it) {
        Node* node = *it;
        if ((1 << node->vtable->GetKind(node)) & 0x3fe) {
            if (node->action.GetState() != 2) {
                if (ctx->table.Find(node->vtable->GetKind(node))->IsValid()) {
                    if (node->Classify() == 1)
                        primary = node;
                    else
                        secondary = node;
                }
            }
        }
    }

    if (primary == 0)
        primary = secondary;

    Action* result = primary != 0 ? &primary->action : 0;
    if (primary == 0) {
        if (ctx->vtable->GetCurrent(ctx)->action.GetState() != 2) {
            Node* current = ctx->vtable->GetCurrent(ctx);
            if (current != 0)
                return &current->action;
            return 0;
        }
    }
    return result;
}

// @ 0x00dbab60
uint32_t FUN_00dbab60(void* param_1, void* arg0, void* arg1, void* arg2, void* arg3, void* arg4, int arg5, int arg6, void* arg7)
{
    (void)arg1; (void)arg2; (void)arg3; (void)arg4; (void)arg5; (void)arg6; (void)arg7;

    if (arg0 == 0)
        return FUN_00da6270_s00db_ab60(param_1, 0xf);

    // actor validation: a specific "tribe" component id (0x4f396a66)
    if (arg0 != 0 && FUN_00d998d0_s00db_ab60(arg0, 0x4f396a66) != 0)
        goto active;

    if (*(int*)arg1 < 4 || DAT_01581374 != 0) {
        FUN_00b3d2c0(0.0f);
        int n = (int)FUN_00d00780(0.0f);
        if (n > 1)
            goto active;
    }
    // distance/score test against the blackboard target (squared distance
    // compared with 1.0f) -> return 0 when out of range
    {
        float dx = 0.0f;
        if (1.0f < dx * dx)
            return 0;
    }

active:
    // score-based selection: best target gives the animation/route
    if (arg0 != 0) {
        // if ((cVar3 != 0) && (param_1 == pcVar9)) { cTribeModeStrategy::Instance();
        //     FUN_00bc2240/FUN_00bc23d0 ... }
    }

    switch (*(int*)arg1) {
    case 0:  goto out;
    case 1:  SP_normalized_safe(0, 0, 1.0f, 2.0f);
             cSPCreatureBase_MoveToPointAndFacingAtSpeed(param_1, 2, 0, 0.0f, 0, 0);
             return 1;
    case 2:  // walk to the current goal
             cSPCreatureBase_MoveToPointAtSpeed(param_1, 0, 0.0f);
             return 1;
    case 3:  cSPCreatureBase_SetSprinting(param_1, 1);
             return 1;
    case 4:  cSPCreatureBase_PlayAnimation(param_1, 0);
             return 1;
    case 5:  cSPCreatureBase_InterruptAnimation(param_1, 0);
             cSPCreatureBase_PlayIdleAnimation(param_1);
             return 1;
    case 6:  cSPCreatureBase_Attack(param_1, 0);
             return 1;
    default: break;
    }
out:
    return 1;
}

// @ 0x00dbe140
void SlotVector::Reserve(uint32_t n)
{
    int const cap = (int)((char*)mpCapacity - (char*)mpBegin) / 0x250;
    if ((uint32_t)n <= (uint32_t)cap) return;
    SlotEntry* p = n ? (SlotEntry*)ea_operator_new(n * 0x250, "Simulator", 0, 0, kAllocatorFile, 0xd1) : 0;
    SlotEntry* const end = mpEnd;
    SlotEntry* const begin = mpBegin;
    FUN_00db99a0(begin, end, p);
    FUN_00da82a0(begin, end, p);
    if (mpBegin) ea_operator_delete(mpBegin);
    int const used = (int)((char*)mpEnd - (char*)begin);
    mpBegin = p;
    mpEnd = (SlotEntry*)((char*)p + used / 0x250 * 0x250);
    mpCapacity = (SlotEntry*)((char*)p + (int)n * 0x250);
}

// @ 0x00dbe200
void SlotVector::Insert(SlotEntry* pos, const SlotEntry* val)
{
    if (mpEnd != mpCapacity) {
        const SlotEntry* v = val;
        if (pos <= val && val < mpEnd) v = (const SlotEntry*)((const char*)val + 0x250);
        if (mpEnd) {
            mpEnd->mId = mpEnd[-1].mId;
            if (!(mpEnd[-1].mId >> 31)) mpEnd->mObj.CopyFrom(&mpEnd[-1].mObj);
        }
        FUN_00dba5f0(pos, mpEnd - 1, mpEnd);
        pos->AssignFrom(v);
        ++mpEnd;
        return;
    }
    int const oldCount = (int)((char*)mpEnd - (char*)mpBegin) / 0x250;
    int newCap = oldCount ? oldCount * 2 : 1;
    SlotEntry* p = newCap ? (SlotEntry*)ea_operator_new(newCap * 0x250, "Simulator", 0, 0, kAllocatorFile, 0xd1) : 0;
    SlotEntry* const begin = mpBegin;
    SlotEntry* const newPos = (SlotEntry*)FUN_00db99a0(begin, pos, p);
    FUN_00da82a0(begin, pos, p);
    if (newPos) {
        newPos->mId = val->mId;
        if (!(val->mId >> 31)) newPos->mObj.CopyFrom(&val->mObj);
    }
    SlotEntry* const oldEnd = mpEnd;
    SlotEntry* const tail = (SlotEntry*)((char*)newPos + 0x250);
    SlotEntry* const newEnd = (SlotEntry*)FUN_00db99a0(pos, oldEnd, tail);
    FUN_00da82a0(pos, oldEnd, tail);
    if (mpBegin) ea_operator_delete(mpBegin);
    mpBegin = p;
    mpEnd = newEnd;
    mpCapacity = (SlotEntry*)((uint32_t)p + newCap * 0x250);
}

// @ 0x00dbe380
void SlotVector::PushDefault()
{
    SlotEntry* const end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = end + 1;
        if (end) { end->mId = 0x80000000; return; }
    } else {
        SlotEntry tmp;
        tmp.mId = 0x80000000;
        Insert(end, &tmp);
        bool empty = (bool)((tmp.mId >> 0x1f) & 1);
        if (!empty) ((GmPayloadVirtual*)&tmp.mObj)->Destroy(0);
    }
}

// @ 0x00dbe3e0
uint32_t SlotVector::CreateSlot(const GmObj* src)
{
    uint32_t idx = mNextFree;
    if (idx == 0x3fffffff) {
        GmObj tmp;
        tmp.CopyFrom(src);
        int const count = (int)((char*)mpEnd - (char*)mpBegin) / 0x250;
        PushDefault();
        idx = count;
        if (count != 0) {
            SlotEntry* const prev = (SlotEntry*)((uint32_t)mpBegin + count * 0x250 - 0x250);
            prev->mId &= 0xbfffffff;
        }
        SlotEntry* const slot = (SlotEntry*)((uint32_t)mpBegin + count * 0x250);
        slot->mId |= 0x40000000;
        slot->mId &= 0x7fffffff;
        slot->mObj.CopyFrom(&tmp);
        tmp.Destroy();
    } else {
        SlotEntry* const e = (SlotEntry*)((uint32_t)mpBegin + idx * 0x250);
        mNextFree = e->mId & 0x3fffffff;
        e->mId &= 0x7fffffff;
        e->mObj.CopyFrom(src);
    }
    if (mLowestFree > idx) mLowestFree = idx;
    return idx;
}

// @ 0x00dbe4e0
uint32_t GroupMovementPool::CreateObject()
{
    GmObj gm;
    uint32_t const id = CreateSlot(gm.Init());
    gm.Destroy();
    return id | 0x40000000;
}

// @ 0x00dbe520
bool __cdecl FUN_00dbe520(Creature_s00db_e140* a1, int a2, int a3, int a4, unsigned flags, MoveResult* res, MoveParams* mp)
{
    (void)a2; (void)a3; (void)a4;
    if (res) res->mpObject = 0;
    Creature_s00db_e140* const self = a1;
    Creature_s00db_e140* citizen;
    if (self) {
        uint32_t const id = self->GetNounID();
        citizen = self;
        if (id != kNounCitizen) citizen = 0;
    } else {
        citizen = 0;
    }
    Vec3_s00db_e140 dest(kNoDest);
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
            if (o2) FUN_00b3d480_s00db_e140()->FUN_00acd2d0(o2);
        }
    } else if (rec && rec->mType == (uint32_t)res->mState && *(uint16_t*)((char*)rec + 0x4b) == 0x31) {
        Vec3_s00db_e140 tmp(*((Vec3Holder*)((char*)rec + 0x39))->FUN_00cce910());
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
                int const a = FUN_00b3d2b0_s00db_e140()->FUN_00ac79d0();
                int const b = sub->FUN_00cee330();
                FUN_00b3d2b0_s00db_e140()->FUN_00ac7de0(b, a);
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
            Tribe_s00db_e140* tribe = NounManager_s00db_e140()->FUN_00bfc5f0();
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
        MoveState* st = FUN_00bc9b00_s00db_e140()->FUN_00bca620(0x4eb9c78, (void*)0xdb3e90, &blk);
        if (!st) {
            st = FUN_00bc9b00_s00db_e140()->FUN_00bcb0b0(0x4eb9c78, 0x20, self->GetNounID(), kMoveName);
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

